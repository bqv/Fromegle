#include "stranger.h"

Stranger::Stranger(StrangerType t, QStringList l) : type(t),
													servers(l)
{
	active = false;
}

Stranger::~Stranger()
{
	;
}

void Stranger::begin()
{
	current = randomServer();
	socket = new QTcpSocket;
	socket->connectToHost(current, 1365);
	while(!socket->waitForConnected(1000))
	{
		qDebug() << socket->error();
		socket->connectToHost(current, 1365);
	}
	writePacket("omegleStart");
	active = true;
	start();
}

void Stranger::send(QString message)
{
	QMutexLocker locker(&mutex);
	writePacket("s", message);
}

void Stranger::disconnect()
{
	writePacket("d");
	active = false;
}

void Stranger::type()
{
	writePacket("t");
}

void Stranger::stop()
{
	writePacket("st");
}

void Stranger::run()
{
	QString data, opcode;
	while(active)
	{
		opcode = readString(socket->read(1).toUShort());
		if(opcode == "c") emit connected();
		else if(opcode == "w"); //emit waiting()?
		else if(opcode == "m") emit message(readString(socket->read(2).toUShort()));
		else if(opcode == "t") emit typing();
		else if(opcode == "st") emit stopped();
		else if(opcode == "d") break;
		else qDebug() << "Undefined opcode: " << opcode;
	}
	emit disconnected();
	socket->disconnectFromHost();
}

void Stranger::writePacket(QString opcode, QString data)
{
	socket->write((quint8)opcode.size());
	socket->write(opcode);
	if(!data.isNull())
	{
		socket->write((quint16)data.size());
		socket->write(data);
	}
}

QString Stranger::readString(qint64 length)
{
	return socket->read(length).data();
}

QString Stranger::randomServer()
{
	return servers[rand() % servers.size()];
}

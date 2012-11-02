#include "stranger.h"

Stranger::Stranger(StrangerType t, QStringList l) : s_type(t),
													servers(l)
{
	socket = new QTcpSocket;
	active = false;
}

Stranger::~Stranger()
{
	;
}

void Stranger::begin()
{
	if(socket->state() != QAbstractSocket::ConnectedState)
	{
		current = randomServer();
		socket->connectToHost(current, 1365);
		while(!socket->waitForConnected(1000))
			socket->connectToHost(current, 1365);
	}
	writePacket("omegleStart");
	active = true;
	start();
}

void Stranger::send(QString message)
{
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
	QString opcode, operand;
	while(socket->state() == QAbstractSocket::ConnectedState && active)
	{
		quint8 byte; quint16 nibble;
		socket->waitForReadyRead(-1);
		QDataStream(socket->read(1)) >> byte;
		opcode = readString(byte);
		QDataStream(socket->read(2)) >> nibble;
		operand = readString(nibble);
		if(opcode == "client_id") qDebug() << operand;
		else if(opcode == "c") emit connected();
		else if(opcode == "w") emit waiting();
		else if(opcode == "m") emit message(operand);
		else if(opcode == "t") emit typing();
		else if(opcode == "st") emit stopped();
		else if(opcode == "d") break;
		qDebug() << "Opcode: " << opcode
			<< "\nData: " << operand;
		
	}
	emit disconnected();
}

void Stranger::writePacket(QString action, QString data)
{
	QMutexLocker locker(&mutex);
	QByteArray opcode;
	QDataStream ds(&opcode, QIODevice::WriteOnly);
	ds << quint8(action.size());
	socket->write(opcode);
	socket->write(action.toAscii());
	if(!data.isNull())
	{
		QByteArray operand;
		QDataStream(&operand, QIODevice::WriteOnly) << quint16(data.size());
		socket->write(operand);
		socket->write(data.toAscii());
	}
	else socket->write(QByteArray(2, quint16(0)));
}

QString Stranger::readString(short length)
{
	if(length == 0) return QString();
	QByteArray string = socket->read(length);
	return string;
}

QString Stranger::randomServer()
{
	return servers[rand() % servers.size()];
}

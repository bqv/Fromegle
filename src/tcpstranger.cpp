#include "tcpstranger.h"

TCPStranger::TCPStranger(QStringList l) : s_type(TCP),
										  servers(l),
										  thread()
{
	connect(&thread, SIGNAL(started()), this, SLOT(run()));
	this->moveToThread(&thread);
	socket = new QTcpSocket;
	active = false;
}

TCPStranger::~TCPStranger()
{
	;
}

void TCPStranger::begin()
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
	thread.start();
}

void TCPStranger::send(QString message)
{
	writePacket("s", message);
}

void TCPStranger::disconnect()
{
	writePacket("d");
	active = false;
}

void TCPStranger::type()
{
	writePacket("t");
}

void TCPStranger::stop()
{
	writePacket("st");
}

void TCPStranger::run()
{
	QString opcode, operand;
	quint8 byte; quint16 nibble;
	while(socket->state() == QAbstractSocket::ConnectedState && active)
	{
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
		else if(opcode == "d") active = false;
		else qDebug() << "Opcode: " << opcode
			<< "\nData: " << operand;
	}
	emit disconnected();
	thread.terminate();
}

void TCPStranger::writePacket(QString action, QString data)
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

QString TCPStranger::readString(short length)
{
	if(length == 0) return QString();
	QByteArray string = socket->read(length);
	return string;
}

QString TCPStranger::randomServer()
{
	return servers[rand() % servers.size()];
}

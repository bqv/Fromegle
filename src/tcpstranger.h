#ifndef _TCPSTRANGER_H_
#define _TCPSTRANGER_H_

#include <QDataStream>
#include <QTcpSocket>
#include <QByteArray>

#include "stranger.h"

class TCPStranger : public Stranger
{
	Q_OBJECT

	public:
		TCPStranger(QStringList = QStringList());
		~TCPStranger();
	
	public slots:
		void begin();
		void send(QString);
		void disconnect();
		void type();
		void stop();

	signals:
		void connected();
		void waiting();
		void message(QString);
		void disconnected();
		void typing();
		void stopped();

	private slots:
		void run();

	private:
		void writePacket(QString, QString = QString());
		QString readString(short);
		QString randomServer();

	private:
		mutable QMutex mutex;
		const Type s_type;
		QStringList servers;
		QString current;
		T thread;
		QTcpSocket *socket;
		bool active;
};

#endif

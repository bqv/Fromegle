#ifndef _STRANGER_H_
#define _STRANGER_H_

#include <QMutexLocker>
#include <QStringList>
#include <QTcpSocket>
#include <QVariant>
#include <QObject>
#include <QString>
#include <cstdlib>
#include <QDebug>
#include <QMutex>
#include <QList>

#include "json.h"
#include "thread.h"

class Stranger : public QThread
{
	Q_OBJECT

	public:
		enum StrangerType { Text, Spy, Question, Video };
		Stranger(StrangerType = Text, QStringList = QStringList());
		~Stranger();
	
	public slots:
		void begin();
		void send(QString);
		void disconnect();
		void type();
		void stop();

	signals:
		void connected();
		void message(QString);
		void disconnected();
		void typing();
		void stopped();

	private:
		void run();
		void writePacket(QString, QString = QString());
		QString readString(qint64);
		QString randomServer();

	private:
		mutable QMutex mutex;
		const StrangerType type;
		QStringList servers;
		QString current;
		QTcpSocket *socket;
		bool active;
};

#endif

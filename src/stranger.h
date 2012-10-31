#ifndef _STRANGER_H_
#define _STRANGER_H_

#include <QStringList>
#include <QVariant>
#include <QObject>
#include <QString>
#include <cstdlib>
#include <QDebug>
#include <QList>

#include "connection.h"
#include "json.h"
#include "thread.h"

class Stranger : public QObject
{
	Q_OBJECT

	public:
		enum StrangerType { Text, Spy, Question, Video };
		Stranger(StrangerType = Text, QStringList = QStringList());
		~Stranger();
		void setOther(Stranger*);
		QString getID();

	signals:
		void recieved(QString);
		void sent(QString);
		void disconnected();
		void connected();

	public slots:
		void send(QString);
		void disconnect();
		void reconnect();

	private slots:
		void run();

	private:
		void parse(QStringList);
		QString randomServer();

	private:
		const StrangerType type;
		Stranger *other;
		QStringList servers;
		QString current;
		QString id;
		bool active;
		T thread;
		Connection *conn;
};

#endif

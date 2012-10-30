#ifndef _STRANGER_H_
#define _STRANGER_H_

#include <QStringList>
#include <QVariant>
#include <iostream>
#include <QObject>
#include <QString>
#include <cstdlib>
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

	signals:
		void recieved(QString);
		void sent(QString);

	public slots:
		void inject(QString);

	private slots:
		void run();

	private:
		void parse(QStringList);
		void send(QString);
		QString randomServer();

	private:
		const StrangerType type;
		const Stranger *other;
		QStringList servers;
		QString id;
		bool active;
		T thread;
		Connection *conn;
};

#endif

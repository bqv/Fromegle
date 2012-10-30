#ifndef _POLL_H_
#define _POLL_H_

#include <QStringList>
#include <QVariant>
#include <QString>

#include "connection.h"
#include "json.h"
#include "thread.h"

class PollThread : public QObject
{
	Q_OBJECT

	public:
		PollThread();
		~PollThread();
	
	public slots:
		void work();
		void stop();
	
	signals:
		void count(int);
		void queuetimes(double, double);
		void timestamp(double);
		void servers(QStringList);
		void error(QString);

	private:
		void parse(QByteArray);
		bool active;
		T thread;
		Connection *conn;
};

#endif

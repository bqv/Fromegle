#ifndef _POLL_H_
#define _POLL_H_

#include <QStringList>
#include <QString>
#include <QThread>

#include "connection.h"
#include "json.h"

class T: public QThread {
	public:
		static void sleep(int s)
		{ QThread::sleep(s); }
		static void msleep(int ms)
		{ QThread::msleep(ms); }
		static void usleep(int us)
		{ QThread::usleep(us); }
};

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
		void count(long);
		void servers(QStringList);
		void error(QString);

	private:
		void parse(QByteArray);
		bool active;
		T thread;
		Connection *conn;
};

#endif

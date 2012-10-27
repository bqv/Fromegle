#ifndef _POLL_H_
#define _POLL_H_

#include <QString>
#include <QThread>

#include "connection.h"

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
		void parse();
	
	public slots:
		void work();
		void stop();
	
	signals:
		void error(QString);

	private:
		bool active;
		T thread;
		Connection *conn;
};

#endif

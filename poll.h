#ifndef _POLL_H_
#define _POLL_H_

#include "connection.h"

class PollThread : public QThread
{
	Q_OBJECT

	public:
		PollThread(QObject *parent = 0);
		~PollThread();
	
	protected:
		void run();

	private:
		bool active;
		Connection conn;
};

#endif

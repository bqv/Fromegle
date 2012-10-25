#ifndef _POLL_H_
#define _POLL_H_

#include <QString>
#include <QThread>

#include "connection.h"

class PollThread : public QThread
{
	Q_OBJECT

	public:
		PollThread();
		~PollThread();
	
	protected:
		void run();

	private:
		bool active;
		Connection *conn;
};

#endif

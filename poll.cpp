#include "poll.h"

PollThread::PollThread() : QThread(),
						   active(true),
						   conn()
{
	start();
}

PollThread::~PollThread()
{
	active = false;
	wait();
}

void PollThread::run()
{
	while(active)
	{
		usleep(30000);
		conn->get("/status");
	}
}

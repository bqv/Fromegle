#include "poll.h"

PollThread::PollThread(QObject *parent) : QThread(parent),
										  active(true)
{
	conn = new Connection(new QString("www.omegle.com"));
	start();
}

PollThread::~PollThread()
{
	active = false;
	wait();
}

void PollThread::run()
{
	;
}

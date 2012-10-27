#include "poll.h"

PollThread::PollThread() : QObject(),
						   active(true),
						   thread()
{
	connect(&thread, SIGNAL(started()), this, SLOT(work()));
	this->moveToThread(&thread);
	thread.start();
}

PollThread::~PollThread()
{
	;
}

void PollThread::parse(QByteArray json)
{
	std::cout << json.data() << "\033[38;3;1;255m%\033[0m" << std::endl;
}

void PollThread::work()
{
	conn = new Connection("www.omegle.com");
	while(active)
	{
		QByteArray data = conn->get("/status").data();
		if(data.isEmpty() || data.endsWith("null")) emit error("Bad response from status");
		else parse(data);
		thread.sleep(30);
	}
}

void PollThread::stop()
{
	active = false;
	thread.quit();
}

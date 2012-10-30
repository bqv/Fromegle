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
	QVariantMap dataset = JSON(json.data()).getSerial().toMap();
	emit count(dataset.value("count").toInt());
	emit queuetimes(dataset.value("spyeeQueueTime").toDouble(), dataset.value("spyQueueTime").toDouble());
	emit timestamp(dataset.value("timestamp").toDouble());
	emit servers(dataset.value("servers").toStringList());
}

void PollThread::work()
{
	conn = new Connection("www.omegle.com");
	while(active)
	{
		QByteArray data = conn->get("/status").data();
		if(data.isEmpty() || data.endsWith("null"))
		{
			emit error("Bad response from status");
			continue;
		}
		else parse(data);
		thread.sleep(10);
	}
}

void PollThread::stop()
{
	active = false;
	thread.quit();
}

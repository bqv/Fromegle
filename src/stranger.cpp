#include "stranger.h"

Stranger::Stranger(StrangerType t, QStringList l) : type(t),
													servers(l),
													thread()
{
	connect(&thread, SIGNAL(started()), this, SLOT(run()));
	this->moveToThread(&thread);
	thread.start();
}

Stranger::~Stranger()
{
	;
}

void Stranger::inject(QString message)
{
	message.clear();
}

void Stranger::run()
{
	conn = new Connection(randomServer());
	QByteArray data = conn->get("/start").data();
	while(data.isEmpty() || data.endsWith("null"))
	{
		QByteArray data = conn->get("/start").data();
	}
	data.chop(1);
	id = data.mid(1).data();
	std::cout << id.toStdString() << std::endl;
	while(active)
	{
		conn->addParam("id", id);
		data = conn->post("/events").data();
		if(!(data.isEmpty() || data.endsWith("null")))
			parse(JSON(data.data()).getSerial()
					.toList()[0].toStringList());
		thread.msleep(100);
	}
}

void Stranger::parse(QStringList response)
{
	if(response[0] == "gotMessage")
			emit recieved(response[1]);
}

void Stranger::setOther(Stranger *otherStranger)
{
	other = otherStranger;
}

QString Stranger::randomServer()
{
	return servers[rand() % servers.size()];
}

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
	thread.quit();
}

QString Stranger::getID()
{
	return id;
}

void Stranger::send(QString message)
{
	Connection *tconn = new Connection(current);
	QString msg = QUrl::toPercentEncoding(message);
	tconn->addParam("id", id);
	tconn->addParam("msg", msg);
	QString response = tconn->post("/send").data();
	if(response == "win")
		emit sent(message);
}

void Stranger::disconnect()
{
	Connection *tconn = new Connection(current);
	tconn->addParam("id", id);
	QString response = tconn->post("/disconnect").data();
	active = false;
}

void Stranger::typestart()
{
	Connection *tconn = new Connection(current);
	tconn->addParam("id", id);
	QString response = tconn->post("/typing").data();
	active = false;
}

void Stranger::typestop()
{
	Connection *tconn = new Connection(current);
	tconn->addParam("id", id);
	QString response = tconn->post("/stoppedtyping").data();
	active = false;
}

void Stranger::run()
{
	current = randomServer();
	conn = new Connection(current);
	QByteArray data = conn->get("/start").data();
	while(data.isEmpty() || data.endsWith("null"))
	{
		QByteArray data = conn->get("/start").data();
	}
	id = JSON(data.data()).getSerial().toString();
	while(active)
	{
		conn->addParam("id", id);
		data = conn->post("/events").data();
		if(data.isEmpty() || data.endsWith("null"))
			continue;
		qDebug() << data;
		QVariantList events = JSON(data.data()).getSerial().toList();
		QVariantList::Iterator it = events.begin();
		while(it != events.end())
		{
			QStringList event = it->toStringList();
			parse(event);
			++it;
		}
		thread.msleep(100);
	}
}

void Stranger::parse(QStringList event)
{
	QString type = event[0];
	if(type == "gotMessage")
	{
		QString data = event[1];
		emit recieved(data);
	}
	else if(type == "typing")
	{
		emit typing();
	}
	else if(type == "stoppedTyping")
	{
		emit stopped();
	}
	else if(type == "connected")
	{
		emit connected();
	}
	else if(type == "strangerDisconnected")
	{
		emit disconnected();
		active = false;
	}
}

QString Stranger::randomServer()
{
	return servers[rand() % servers.size()];
}

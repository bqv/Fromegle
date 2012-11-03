#include "httpstranger.h"

HTTPStranger::HTTPStranger(QStringList l) : s_type(HTTP),
											servers(l),
											thread()
{
	connect(&thread, SIGNAL(started()), this, SLOT(run()));
	this->moveToThread(&thread);
}

HTTPStranger::~HTTPStranger()
{
	;
}

void HTTPStranger::begin()
{
	thread.start();
}

void HTTPStranger::send(QString message)
{
	Connection *tconn = new Connection(current);
	QString msg = QUrl::toPercentEncoding(message);
	tconn->addParam("id", id);
	tconn->addParam("msg", msg);
	tconn->post("/send").data();
}

void HTTPStranger::disconnect()
{
	Connection *tconn = new Connection(current);
	tconn->addParam("id", id);
	QString response = tconn->post("/disconnect").data();
	active = false;
}

void HTTPStranger::type()
{
	Connection *tconn = new Connection(current);
	tconn->addParam("id", id);
	QString response = tconn->post("/typing").data();
}

void HTTPStranger::stop()
{
	Connection *tconn = new Connection(current);
	tconn->addParam("id", id);
	QString response = tconn->post("/stoppedtyping").data();
}

void HTTPStranger::run()
{
	qDebug() << "HAJIMASHOU";
	current = randomServer();
	conn = new Connection(current);
	QByteArray data = conn->get("/start").data();
	while(data.isEmpty() || data.endsWith("null"))
	{
		QByteArray data = conn->get("/start").data();
	}
	id = JSON(data.data()).getSerial().toString();
	qDebug() << id;
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

void HTTPStranger::parse(QStringList event)
{
	QString type = event[0];
	if(type == "gotMessage")
	{
		QString data = event[1];
		emit message(data);
	}
	else if(type == "typing")
		emit typing();
	else if(type == "stoppedTyping")
		emit stopped();
	else if(type == "connected")
		emit connected();
	else if(type == "waiting")
		emit waiting();
	else if(type == "strangerDisconnected")
	{
		emit disconnected();
		active = false;
	}
}

QString HTTPStranger::randomServer()
{
	return servers[rand() % servers.size()];
}

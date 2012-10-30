#include "connection.h"

Connection::Connection(QString url) : params(0),
									  loop()
{
	data = new kvpair[5];
	server = url;
}

Connection::Connection() : params(0)
{
	data = new kvpair[5];
	server = *(new QString("www.omegle.com"));
}

Connection::~Connection()
{
	;
}

Connection* Connection::addParam(QString key, QString value)
{
//	if(params >= sizeof(*data)/sizeof(kvpair))
//	{
//		std::cout << "FIXME: kvpair data[] too small. Index out of bounds." << std::endl;
//		return NULL;
//	}
	data[params].value = value;
	data[params++].key = key;
	return this;
}

QByteArray Connection::get(QString location)
{
	loc = location;
	sendReq(false);
	params = 0;
	
	loop.exec();

	return response;
}

QByteArray Connection::post(QString location)
{
	loc = location;
	sendReq(true);
	params = 0;

	loop.exec();

	return response;
}

void Connection::httpDone()
{
	response = reply->readAll();
	loop.quit();
}

QByteArray* Connection::compileData()
{
	QByteArray *payld = new QByteArray();
	for(int i=0; i < params; i++)
	{
		payld->append(data[i].key);
		payld->append("=");
		payld->append(data[i].value);
	}
	return payld;
}

void Connection::sendReq(bool post)
{
	QByteArray *payld = compileData();
	if(post)
	{
		QUrl url = QString("http://").append(server).append(loc);
		QNetworkRequest req = QNetworkRequest(url);
		req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
		reply = qnam.post(req, *payld);
	}
	else
	{
		QUrl url = QString("http://").append(server).append(loc)
			.append("?").append(*payld);
		reply = qnam.get(QNetworkRequest(url));
	}
	connect(reply, SIGNAL(finished()), this, SLOT(httpDone()));
}

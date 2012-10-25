#include "connection.h"

Connection::Connection(QString url) : params(0)
{
	data = new kvpair[5];
	server = url;
}

Connection::~Connection()
{
	;
}

bool Connection::addParam(QString key, QString value)
{
	if(params >= sizeof(*data)/sizeof(kvpair))
	{
		std::cout << "FIXME: kvpair data[] too small. Index out of bounds." << std::endl;
		return false;
	}
	data[params].value = value;
	data[params++].key = key;
	return true;
}

QByteArray Connection::get(QString location)
{
	loc = location;
	sendReq(false);
	
	while(!done);

	return response;
}

QByteArray Connection::post(QString location)
{
	loc = location;
	sendReq(true);
	params = 0;

	while(!done);

	return response;
}

void Connection::httpDone()
{
	response = reply->readAll();
	done = true;
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
	QUrl url = (new QString(server))->append(loc);
	if(post)
	{
		QByteArray *payld = compileData();
		reply = qnam.post(QNetworkRequest(url), *payld);
		delete payld;
	}
	else reply = qnam.get(QNetworkRequest(url));

	connect(reply, SIGNAL(finished()), this, SLOT(httpDone()));
}

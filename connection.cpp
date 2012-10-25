#include "connection.h"

Connection::Connection(QString url) : params(0)
{
	server = url;
}

Connection::~Connection()
{
	;
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
	QUrl url = server.append(loc);
	if(post)
	{
		QByteArray *payld = compileData();
		reply = qnam.post(QNetworkRequest(url), *payld);
		delete payld;
	}
	else reply = qnam.get(QNetworkRequest(url));
	connect(reply, SIGNAL(finished()),
			this, SLOT(httpDone()));
	connect(reply, SIGNAL(readyRead()),
			this, SLOT(httpRead()));
	params = 0;
}

void Connection::httpRead()
{
	;
}

void Connection::httpDone()
{
	;
}

#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>
#include <QObject>
#include <QString>
#include <QUrl>

struct kvpair {
	QString key;
	QString value;
};

class Connection : public QObject
{
	Q_OBJECT
	public:
		Connection(QString url);
		~Connection();
		void addParam();
		void get(QString location);
		void post(QString location);
		void getEvent();


	private slots:
		void httpRead();
		void httpDone();

	private:
		QNetworkAccessManager qnam;
		QNetworkReply *reply;
		QString server;
		QString loc;
		kvpair data[5];
		int params;

		void sendReq(bool post);
		QByteArray* compileData();
};

#endif

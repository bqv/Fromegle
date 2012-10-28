#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <iostream>
#include <QObject>
#include <QThread>
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
		Connection(QString);
		Connection();
		~Connection();

		Connection* addParam(QString, QString);
		QByteArray get(QString);
		QByteArray post(QString);

	private slots:
		void httpDone();

	private:
		QNetworkAccessManager qnam;
		unsigned short params;
		QNetworkReply *reply;
		QByteArray response;
		QEventLoop loop;
		QString server;
		kvpair *data;
		QString loc;

		void sendReq(bool);
		QByteArray* compileData();
};

#endif

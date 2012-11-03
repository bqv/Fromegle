#ifndef _HTTPSTRANGER_H_
#define _HTTPSTRANGER_H_

#include <QVariant>
#include <QList>

#include "connection.h"
#include "json.h"
#include "stranger.h"

class HTTPStranger : public Stranger
{
	Q_OBJECT

	public:
		HTTPStranger(QStringList = QStringList());
		~HTTPStranger();

	public slots:
		void begin();
		void send(QString);
		void disconnect();
		void type();
		void stop();

	signals:
		void connected();
		void waiting();
		void message(QString);
		void disconnected();
		void typing();
		void stopped();

	private slots:
		void run();

	private:
		void parse(QStringList);
		QString randomServer();

	private:
		mutable QMutex mutex;
		const Type s_type;
		QStringList servers;
		QString current;
		QString id;
		bool active;
		T thread;
		Connection *conn;
};

#endif

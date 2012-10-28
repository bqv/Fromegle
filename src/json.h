#ifndef _JSON_H_
#define _JSON_H_

#include <QJson/Serializer>
#include <QJson/Parser>
#include <QVariant>
#include <iostream>
#include <QObject>
#include <QString>

class JSON : public QObject
{
	Q_OBJECT
		
	public:
		JSON(char jsondata[] = "");
		JSON(QByteArray = "");
		JSON(QVariant = new QVariantMap);
		~JSON();

	public:
		QVariant getSerial() const;
		QByteArray getJson() const;
		bool ok() const;

	private:
		QByteArray json;
		QVariant serial;
		bool success;
};

#endif

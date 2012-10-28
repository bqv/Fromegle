#ifndef _JSON_H_
#define _JSON_H_

#include <iostream>
#include <QObject>
#include <QString>

class JSON : public QObject
{
	Q_OBJECT
		
	public:
		JSON(QString = "");
		~JSON();

	public:

	private:
		QString json;
};

#endif

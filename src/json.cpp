#include <json.h>

JSON::JSON(char jsondata[]) : QObject(),
							  json(jsondata)
{
	QJson::Parser parser;
	serial = parser.parse (json, &success);
}

JSON::JSON(QByteArray jsondata) : QObject(),
								  json(jsondata)
{
	QJson::Parser parser;
	serial = parser.parse (json, &success);
}

JSON::JSON(QVariant serialdata) : QObject(),
								  serial(serialdata)
{
	QJson::Serializer serializer;
	json = serializer.serialize(serial);
}

JSON::~JSON()
{
	;
}

QVariant JSON::getSerial() const
{
	return serial;
}

QByteArray JSON::getJson() const
{
	if(success) return json;
	else return "";
}

bool JSON::ok() const
{
	return success;
}

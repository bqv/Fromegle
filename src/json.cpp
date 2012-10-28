#include <json.h>

JSON::JSON(QString jsondata) : QObject(),
							   json(jsondata)
{
	;
}

JSON::~JSON()
{
	;
}

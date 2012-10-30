#include "stranger.h"

Stranger::Stranger(StrangerType t) : type(t)
{
	;
}

Stranger::~Stranger()
{
	;
}

void Stranger::setOther(Stranger *otherStranger)
{
	other = otherStranger;
}

void Stranger::inject(QString message)
{
	//send to other
}


#include "MessageDetail.h"


MessageDetail::MessageDetail()
{
}


MessageDetail::~MessageDetail()
{
}

void MessageDetail::setMess(const string fromUsr, const string toUsr, const string mess, const string time){
	this->fromUsr = fromUsr;
	this->toUsr = toUsr;
	this->mess = mess;
	this->time = time;
}

const string MessageDetail::getToUsr() const{
	return toUsr;
}

const string MessageDetail::getFromUsr() const{
	return fromUsr;
}

const string MessageDetail::getMess() const{
	return mess;
}

const string MessageDetail::getTime() const{
	return time;
}
#include "stdafx.h"
#include "ControllerStrategy.h"


ControllerStrategy::ControllerStrategy()
{
}


ControllerStrategy::~ControllerStrategy()
{
}

void ControllerStrategy::setJsonStringRequest(const string jsonString)
{
	this->jsonStringRequest = jsonString;
}


void ControllerStrategy::setController(Controller * controller)
{
	//delete this->controller;
	this->controller = controller;
	controller->setRequest(this->jsonStringRequest);
}

string ControllerStrategy::getControllerResponse()
{
	Document jsonDoc;
	jsonDoc.Parse(this->jsonStringRequest.c_str());
	int type = jsonDoc["type"].GetInt();
	switch (type)
	{
	case JSON_LOGIN:
	case JSON_LOGOUT:
	case JSON_REGIST:
		setController(new ControllerAccount);
		break;
	case JSON_RECV_MESSAGE:
	case JSON_SEND_MESSAGE:
	case JSON_LIST_MESSAGE :
		setController(new ControllerMessage);
		break;
	case JSON_ADD_FRIEND:
	case JSON_DEL_FRIEND:
	case JSON_LIST_FRIEND:
		setController(new ControllerFriend);
		break;
	}
	return this->controller->getResponse();
}
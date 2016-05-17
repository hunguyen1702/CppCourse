#pragma once

#include "ControllerAccount.h"
#include "ControllerFriend.h"
#include "ControllerMessage.h"

class ControllerStrategy
{
private:
	string jsonStringRequest;
	Controller * controller;
public:
	ControllerStrategy();
	~ControllerStrategy();

	void setJsonStringRequest(const string);
	void setController(Controller *);
	string getControllerResponse();
	
};


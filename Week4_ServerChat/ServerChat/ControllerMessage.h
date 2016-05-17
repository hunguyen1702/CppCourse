#pragma once

#include "Controller.h"

class ControllerMessage : public Controller
{
private:
	RepositoryMessage repMess;

	void modifyGetMessResponse(Document &, const list<Message>);

	int setSendMessResponse();
	int setGetMessResponse();
public:
	~ControllerMessage();

	string getResponse();
};


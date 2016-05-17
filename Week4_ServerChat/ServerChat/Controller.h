#pragma once

#include "RepositoryAccount.h"
#include "RepositoryFriend.h"
#include "RepositoryMessage.h"
#include "Definition.h"

class Controller
{
protected:
	string clientRequest;
	string serverResponse;
	void setResponse(const Document &);

public:
	Controller();
	~Controller();
	
	int getType();
	void setRequest(const string);
	virtual string getResponse();
};
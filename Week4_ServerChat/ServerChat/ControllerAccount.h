#pragma once

#include "Controller.h"
#include "RepositoryAccount.h"

class ControllerAccount : public Controller
{
private:
	RepositoryAccount repAcc;
	
	void modifyLoginResponse(Document &, const bool);

	int setLoginResponse();
	int setLogoutResponse();
	int setRegisterResponse();

public:
	~ControllerAccount();

	string getResponse();
};


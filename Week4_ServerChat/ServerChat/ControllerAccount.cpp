#include "stdafx.h"
#include "ControllerAccount.h"

ControllerAccount::~ControllerAccount()
{
}

string ControllerAccount::getResponse()
{
	int typeResquest = getType();
	switch (typeResquest)
	{
	case JSON_LOGIN:
		setLoginResponse();
		break;
	case JSON_LOGOUT:
		setLogoutResponse();
		break;
	case JSON_REGIST:
		setRegisterResponse();
		break;
	}
	return this->serverResponse;
}

void ControllerAccount::modifyLoginResponse(Document & jsonDoc, const bool status)
{
	jsonDoc.RemoveMember("LoginInfo");
	jsonDoc.AddMember("isLogin", status, jsonDoc.GetAllocator());
}

int ControllerAccount::setLoginResponse()
{
	Document jsonDoc;
	jsonDoc.Parse(this->clientRequest.c_str());

	repAcc.setJsonString(this->clientRequest);
	
	if (repAcc.checkAuthentication() != 1)
	{
		modifyLoginResponse(jsonDoc, false);
		setResponse(jsonDoc);
		return -1;
	}

	if (repAcc.isOnline() != 0)
	{
		modifyLoginResponse(jsonDoc, false);
		setResponse(jsonDoc);
		return -2;
	}

	if (!repAcc.updateStatus(true))
	{
		modifyLoginResponse(jsonDoc, false);
		setResponse(jsonDoc);
		return -3;
	}

	modifyLoginResponse(jsonDoc, true);

	setResponse(jsonDoc);

	return 1;
}

int ControllerAccount::setLogoutResponse()
{
	Document jsonDoc;
	jsonDoc.Parse(this->clientRequest.c_str());

	repAcc.setJsonString(this->clientRequest);

	if (!repAcc.updateStatus(false))
	{
		jsonDoc.RemoveMember("Logout");
		jsonDoc.AddMember("isLogout", false, jsonDoc.GetAllocator());
		setResponse(jsonDoc);
		return -1;
	}

	jsonDoc.RemoveMember("Logout");
	jsonDoc.AddMember("isLogout", true, jsonDoc.GetAllocator());
	setResponse(jsonDoc);
	return 1;
}

int ControllerAccount::setRegisterResponse()
{
	Document jsonDoc;
	jsonDoc.Parse(this->clientRequest.c_str());

	repAcc.setJsonString(this->clientRequest);

	if (!repAcc.createAccount())
	{
		jsonDoc.RemoveMember("Register");
		jsonDoc.AddMember("isCreated", false, jsonDoc.GetAllocator());
		setResponse(jsonDoc);
		return -1;
	}

	jsonDoc.RemoveMember("Register");
	jsonDoc.AddMember("isCreated", true, jsonDoc.GetAllocator());
	setResponse(jsonDoc);
	return 1;
}
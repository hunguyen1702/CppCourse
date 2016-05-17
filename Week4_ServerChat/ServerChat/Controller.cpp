#include "stdafx.h"
#include "Controller.h"


Controller::Controller()
{
}


Controller::~Controller()
{
}

int Controller::getType()
{
	Document jsonDoc;
	jsonDoc.Parse(this->clientRequest.c_str());
	return jsonDoc["type"].GetInt();
}

void Controller::setRequest(const string request)
{
	this->clientRequest = request;
}

void Controller::setResponse(const Document & jsonDoc)
{
	StringBuffer sbuffer;
	PrettyWriter<StringBuffer> pwriter(sbuffer);
	jsonDoc.Accept(pwriter);
	this->serverResponse = sbuffer.GetString();
}

string Controller::getResponse(){ return this->serverResponse; }

#include "stdafx.h"
#include "Message.h"


Message::Message(const string sender,
	const string receiver,
	const string content) : sender(sender), receiver(receiver), content(content)
{
}

Message::Message(const string jsonString)
{
	Document jsonDoc;
	jsonDoc.Parse(jsonString.c_str());
	if (jsonDoc.HasMember("MessageDetail"))
	{
		this->sender = jsonDoc["MessageDetail"]["sender"].GetString();
		this->receiver = jsonDoc["MessageDetail"]["receiver"].GetString();
		this->content = jsonDoc["MessageDetail"]["content"].GetString();
	}
	if (jsonDoc.HasMember("GetListMess"))
	{
		this->receiver = jsonDoc["GetListMess"]["requestUser"].GetString();
	}
}


Message::~Message()
{
}

string Message::getSender(){
	return this->sender;
}

string Message::getReceiver(){
	return this->receiver;
}

string Message::getContent(){
	return this->content;
}
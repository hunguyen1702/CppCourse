#include "stdafx.h"
#include "ControllerMessage.h"


ControllerMessage::~ControllerMessage()
{
}

string ControllerMessage::getResponse()
{
	int typeResquest = getType();
	switch (typeResquest)
	{
	case JSON_RECV_MESSAGE:
		setSendMessResponse();
		break;
	case JSON_LIST_MESSAGE:
		setGetMessResponse();
		break;
	}
	return this->serverResponse;
}

int ControllerMessage::setSendMessResponse()
{
	Document jsonDoc;
	jsonDoc.Parse(this->clientRequest.c_str());

	repMess.setJsonString(this->clientRequest);

	if (!repMess.sendMess(false))
	{
		jsonDoc.RemoveMember("MessageDetail");
		jsonDoc.AddMember("isSend", false, jsonDoc.GetAllocator());
	}
	jsonDoc.RemoveMember("MessageDetail");
	jsonDoc.AddMember("isSend", true, jsonDoc.GetAllocator());
	setResponse(jsonDoc);
	return 1;
}

int ControllerMessage::setGetMessResponse()
{
	Document jsonDoc;
	jsonDoc.Parse(this->clientRequest.c_str());

	repMess.setJsonString(this->clientRequest);

	list<Message> messList;

	repMess.getMess(15, messList);

	modifyGetMessResponse(jsonDoc, messList);
	setResponse(jsonDoc);

	return 1;	
}

void ControllerMessage::modifyGetMessResponse(Document & jsonDoc, const list<Message> messList)
{
	jsonDoc.RemoveMember("GetListMess");

	Value messArr(kArrayType);
	for (Message mess : messList)
	{
		Value messObj(kObjectType);
		Value sender; Value receiver; Value content;
		sender.SetString(mess.getSender().c_str(), jsonDoc.GetAllocator());
		receiver.SetString(mess.getReceiver().c_str(), jsonDoc.GetAllocator());
		content.SetString(mess.getContent().c_str(), jsonDoc.GetAllocator());

		messObj.AddMember("sender", sender, jsonDoc.GetAllocator());
		messObj.AddMember("receiver", receiver, jsonDoc.GetAllocator());
		messObj.AddMember("content", content, jsonDoc.GetAllocator());

		messArr.PushBack(messObj, jsonDoc.GetAllocator());
	}

	jsonDoc.AddMember("MessageList", messArr, jsonDoc.GetAllocator());
}

#include "stdafx.h"
#include "ControllerFriend.h"


ControllerFriend::~ControllerFriend()
{
}

string ControllerFriend::getResponse()
{
	int typeResquest = getType();
	switch (typeResquest)
	{
	case JSON_ADD_FRIEND:
		setAddFrResponse();
		break;
	case JSON_DEL_FRIEND:
		setDelFrResponse();
		break;
	case JSON_LIST_FRIEND:
		setListFrResponse();
		break;
	}
	return this->serverResponse;
}

int ControllerFriend::setAddFrResponse()
{
	Document jsonDoc;
	jsonDoc.Parse(this->clientRequest.c_str());
	
	repFriend.setJsonString(this->clientRequest);
	
	if (!repFriend.addFriend())
	{
		jsonDoc.RemoveMember("AddFriend");
		jsonDoc.AddMember("isAdd", false, jsonDoc.GetAllocator());
		setResponse(jsonDoc);
		return -1;
	}
	jsonDoc.RemoveMember("AddFriend");
	jsonDoc.AddMember("isAdd", true, jsonDoc.GetAllocator());
	setResponse(jsonDoc);
	return 1;
}

int ControllerFriend::setDelFrResponse()
{
	Document jsonDoc;
	jsonDoc.Parse(this->clientRequest.c_str());

	repFriend.setJsonString(this->clientRequest);

	if (!repFriend.delFriend())
	{
		jsonDoc.RemoveMember("DelFriend");
		jsonDoc.AddMember("isDel", false, jsonDoc.GetAllocator());
		setResponse(jsonDoc);
		return -1;
	}
	jsonDoc.RemoveMember("DelFriend");
	jsonDoc.AddMember("isDel", true, jsonDoc.GetAllocator());
	setResponse(jsonDoc);
	return 1;
}

int ControllerFriend::setListFrResponse()
{
	Document jsonDoc;
	jsonDoc.Parse(this->clientRequest.c_str());

	repFriend.setJsonString(this->clientRequest);

	list<string> friendList;

	repFriend.getFriendList(friendList);

	modifyListFrResponse(jsonDoc, friendList);
	setResponse(jsonDoc);

	return 1;
}

void ControllerFriend::modifyListFrResponse(Document & jsonDoc, const list<string> friendList)
{
	jsonDoc.RemoveMember("GetFriendList");
	Value friendArr(kArrayType);
	for (auto usr : friendList){
		Value usernameValue;
		usernameValue.SetString(usr.c_str(), jsonDoc.GetAllocator());
		friendArr.PushBack(usernameValue, jsonDoc.GetAllocator());
	}
	jsonDoc.AddMember("FriendList", friendArr, jsonDoc.GetAllocator());
}
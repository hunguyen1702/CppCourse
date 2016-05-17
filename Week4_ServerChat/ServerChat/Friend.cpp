#include "stdafx.h"
#include "Friend.h"


Friend::Friend()
{
}

Friend::Friend(const string jsonString)
{
	Document jsonDoc;
	jsonDoc.Parse(jsonString.c_str());
	if (jsonDoc.HasMember("AddFriend"))
	{
		this->user = jsonDoc["AddFriend"]["requestUser"].GetString();
		this->friends = jsonDoc["AddFriend"]["addUser"].GetString();
	}
	if (jsonDoc.HasMember("DelFriend"))
	{
		this->user = jsonDoc["DelFriend"]["requestUser"].GetString();
		this->friends = jsonDoc["DelFriend"]["delUser"].GetString();
	}
	if (jsonDoc.HasMember("GetFriendList"))
	{
		this->user = jsonDoc["GetFriendList"]["requestUser"].GetString();
	}
}

Friend::Friend(string user, string friends) : user(user), friends(friends)
{
}

Friend::~Friend()
{
}

void Friend::setFriend(const string usr, const string fr){
	this->user = usr;
	this->friends = fr;
}

string Friend::getUser(){
	return this->user;
}

string Friend::getFriend(){
	return this->friends;
}

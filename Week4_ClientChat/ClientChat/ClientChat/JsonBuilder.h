#pragma once
#include <string>
#include"rapidjson\document.h"
#include"rapidjson\stringbuffer.h"
#include"rapidjson\prettywriter.h"

using namespace std;


class JsonBuilder
{
public:
	JsonBuilder();
	~JsonBuilder();
	string buildRegistJson(CString username, CString password);
	string buildAddFriendJson(CString username);
	string buildMessageJson(CString from, CString to, CString content);
	string buildGetFriendListRequestJson(CString username);
};


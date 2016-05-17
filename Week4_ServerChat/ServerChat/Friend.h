#pragma once

#include <string>
#include"rapidjson\document.h"
#include"rapidjson\stringbuffer.h"
#include"rapidjson\prettywriter.h"

using namespace std;
using namespace rapidjson;

class Friend
{
private:
	string user;
	string friends;
public:
	Friend();
	Friend(const string);
	Friend(const string, const string);
	~Friend();

	void setFriend(const string, const string);
	string getUser();
	string getFriend();
};


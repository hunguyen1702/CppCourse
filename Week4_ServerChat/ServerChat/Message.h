#pragma once

#include <string>
#include"rapidjson\document.h"
#include"rapidjson\stringbuffer.h"
#include"rapidjson\prettywriter.h"

using namespace std;
using namespace rapidjson;

class Message
{
private:
	string sender;
	string receiver;
	string content;
public:
	Message(const string,
				const string,
				const string);
	Message(const string);
	~Message();

	string getSender();
	string getReceiver();
	string getContent();
};


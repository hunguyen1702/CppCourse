#pragma once
#include <string>

using namespace std;

class MessageDetail
{
private:
	string toUsr, fromUsr, mess, time;
public:
	const string getToUsr() const;
	const string getFromUsr() const;
	const string getMess() const;
	const string getTime() const;
	void setMess(const string, const string, const string, const string);
	MessageDetail();
	~MessageDetail();
};


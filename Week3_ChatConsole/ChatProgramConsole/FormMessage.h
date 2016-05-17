#pragma once

#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <conio.h>
#include "MessageDetail.h"
#include "MessageAccessor.h"

using namespace std;

class FormMessage
{
private:
	MessageAccessor accessor;
	string username;
	vector<MessageDetail> listMess;
	void getSystemTime(string & curTime);
public:
	FormMessage();
	~FormMessage();
	void setUsername(const string);
	void listMessView();
	void readMessView(int num);
	void briefMessView();
	void sendMessView();
};


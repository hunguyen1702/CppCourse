#pragma once

#include <cstdio>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "MessageDetail.h"
#include "FriendAccessor.h"

using namespace std;

class MessageAccessor
{
private:
	//add a ifstream to load data
	ifstream reader;
	//File's line format: [receiver]|[sender]|[time]|[message]  
	const string _MESS_DB = "FILE\\AllMessages.txt";
public:
	//set ifstream to the beginning of the AllMessages.txt file
	void setBeginning();
	//get all mess from file into vector of MessageDetail
	int getAllMess(const string &, vector<MessageDetail> &);
	//overloading func above to get [number] message eachtime
	int getMess(const string &, vector<MessageDetail> &, int);
	//send a message ~ write message info to AllMessage.txt file
	int sendMess(const MessageDetail & mess);
	//delete a message ~ delete a line in AllMessage.txt file
	int delMess(const string &, vector<MessageDetail> &, int);
	MessageAccessor();
	~MessageAccessor();
};


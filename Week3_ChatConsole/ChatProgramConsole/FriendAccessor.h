#pragma once

#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "AccountAccessor.h"

using namespace std;

// inherit from AcountAccessor to have checkExist function
class FriendAccessor
{
private:
	//File FriendList format: [my account]|[friend account]
	const string _FRIEND_LIST = "FILE\\FriendList.txt";
	//File BlockList format: [my account]|[block account]
	const string _BLOCK_LIST = "FILE\\BlockList.txt";
	//check if user input their own username
	int checkWrongInput(const string &, const string &);
public:
	//check if that account has been added already
	int checkAddYet(const string &, const string &);
	//check if that account has been blocked already
	int checkBlockYet(const string &, const string &);
	//block an account ~ write a line to BlockList.txt
	int blockAccount(const string &, const string &);
	//add an account ~ write a line to FriendList.txt
	int addAccount(const string &, const string &);
	//unfriend an account ~ delete a line from FriendList.txt
	int unfriend(const string &, const string &);
	//unblock an account ~ delete a line from BlockList.txt
	int unblock(const string &, const string &);
	//get all friend's account name of an account
	int getFriendList(const string &, vector<string> &);
	//get all block's account name of an account
	int getBlockList(const string &, vector<string> &);
	FriendAccessor();
	~FriendAccessor();
};


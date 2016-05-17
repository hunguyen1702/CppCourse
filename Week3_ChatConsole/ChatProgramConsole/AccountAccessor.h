#pragma once

#include <string>
#include "AccountInfo.h"
#include <fstream>
#include <iostream>

using namespace std;

class AccountAccessor
{
private:
	//File AccountInfo format: [username]|[password]|[age]|[name]|[sex]|[address]
	const string _ACC_INFO = "FILE\\AccountInfo.txt";
	//File OnlineUser format: [username]
	const string _ONL_USR = "FILE\\OnlineUser.txt";
	//check if that usr has been login already
	int checkLogin(const string & usr);
	//check if username & password were entered by user are correct
	int checkAuthentication(const LoginInfo &);
public:
	//check if that username has been used yet
	int checkExist(const string & usr);
	//get all info by username into object
	int getUserInfo(const string & usr, AccountInfo & accInfo);
	//create new user, information from object
	int createUser(const AccountInfo & info);
	//write username into AccountOnline.txt
	int userLogin(const LoginInfo &);
	//delete username from AccountOnline.txt
	int userLogout(const string & usr);
	AccountAccessor();
	~AccountAccessor();
};
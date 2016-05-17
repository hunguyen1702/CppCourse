#pragma once

#include <string>
#include"rapidjson\document.h"
#include"rapidjson\stringbuffer.h"
#include"rapidjson\prettywriter.h"

using namespace std;
using namespace rapidjson;

class Account
{
private:
	string username;
	string password;
	string fullname;
	string mail;
	string address;
	int age;
	int sex;
public:
	Account(const string, const string);
	Account(const string);
	Account();
	~Account();

	string getUsername();
	string getPassword();
	void setAccount(string username,
		string fullname,
		string mail,
		string address,
		int age,
		int sex);
	string getFullname();
	string getAddress();
	string getMail();
	int getAge();
	int getSex();
};


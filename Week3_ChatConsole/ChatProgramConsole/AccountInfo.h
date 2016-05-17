#pragma once

#include <string>

using namespace std;
class AccountInfo
{
private:
	string username, password, fullname, addr;
	int sex, age;
public:
	void setInfo(string const usr, string pwd, int const age,
		string const fname, int sex, string addr);
	const string & getUsername () const;
	const string & getPassword () const;
	const string & getFullname () const;
	const string & getAddr () const;
	int getSex() const;
	int getAge() const;
	AccountInfo();
	~AccountInfo();
};

struct LoginInfo
{
	string username;
	string password;
	void setInfo(const string usr, const string pas){
		this->username = usr;
		this->password = pas;
	}
	LoginInfo(){}
	~LoginInfo(){}
};


#include "AccountInfo.h"

AccountInfo::AccountInfo(){};

AccountInfo::~AccountInfo()
{
}

void AccountInfo::setInfo(string const usr, string pwd, int const age,
	string const fname, int sex, string addr) {
	this->username = usr;
	this->password = pwd;
	this->age = age;
	this->fullname = fname;
	this->sex = sex;
	this->addr = addr;
}

const string & AccountInfo::getUsername() const {
	return this->username;
}

const string & AccountInfo::getPassword() const {
	return this->password;
}

const string & AccountInfo::getFullname() const {
	return this->fullname;
}

const string & AccountInfo::getAddr() const {
	return this->addr;
}

int AccountInfo::getSex() const {
	return this->sex;
}

int AccountInfo::getAge() const {
	return this->age;
}
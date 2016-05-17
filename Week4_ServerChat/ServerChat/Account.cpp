#include "stdafx.h"
#include "Account.h"


Account::Account(const string username, 
					const string password) : username(username),
											password(password)
{
}

Account::Account(const string jsonString)
{
	Document jsonDoc;
	jsonDoc.Parse(jsonString.c_str());
	if (jsonDoc.HasMember("LoginInfo"))
	{
		this->username = jsonDoc["LoginInfo"]["username"].GetString();
		this->password = jsonDoc["LoginInfo"]["password"].GetString();
	}
	if (jsonDoc.HasMember("Register"))
	{
		this->username = jsonDoc["Register"]["username"].GetString();
		this->password = jsonDoc["Register"]["password"].GetString();
		//this->fullname = jsonDoc["Register"]["fullname"].GetString();
		this->mail = jsonDoc["Register"]["mail"].GetString();
		//this->address = jsonDoc["Register"]["address"].GetString();
		//this->age = jsonDoc["Register"]["age"].GetInt();
		//this->sex = jsonDoc["Register"]["sex"].GetInt();
	}
	if (jsonDoc.HasMember("Logout"))
	{
		this->username = jsonDoc["Logout"]["username"].GetString();
	}
}

Account::Account()
{
}

Account::~Account()
{
}

void Account::setAccount(string username,
	string fullname,
	string mail,
	string address,
	int age,
	int sex)
{
	this->username = username;
	this->fullname = fullname;
	this->mail = mail;
	this->address = address;
	this->age = age;
	this->sex = sex;
}
string Account::getUsername(){
	return this->username;
}

string Account::getPassword(){
	return this->password;
}

string Account::getFullname(){
	return this->fullname;
}

string Account::getAddress(){
	return this->address;
}

string Account::getMail(){
	return this->mail;
}

int Account::getAge(){
	return this->age;
}

int Account::getSex(){
	return this->sex;
}
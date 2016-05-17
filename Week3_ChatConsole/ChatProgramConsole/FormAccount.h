#pragma once

#include <string>
#include <cstdio>
#include <iostream>
#include <conio.h>
#include <cctype>
#include "AccountAccessor.h"

using namespace std;

class FormAccount
{
private:
	AccountAccessor accessor;
	//check password & username length
	int checkLength(string const &, string const);
	//check age is input by user when regist
	int checkAge(int const &);
	//check password & re-password match
	int checkPwdMatch(string const &, std::string const &);
	//check space in username
	int checkSpace(string const &);
public:
	//constructor
	FormAccount();
	~FormAccount();
	//view to choose login or regist
	void listAccView(string &);
	//login view
	void loginView(string &);
	//register view
	void registView();
	//account information view
	void infoView(string const &);
	//logout from account view
	int logout(string const &);
};


#pragma once

#include <cstdio>
#include <string>
#include "FormAccount.h"
#include "FormFriends.h"
#include "FormMessage.h"

using namespace std;

class FormMain
{
private:
	string username;
	FormAccount * formAccount;
	FormFriends * formFriends;
	FormMessage * formMessage;
public:
	void setUsername(const string);
	void accountView();
	void runProgram();
	FormMain();
	~FormMain();
};


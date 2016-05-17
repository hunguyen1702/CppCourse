#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <conio.h>
#include "FriendAccessor.h"

using namespace std;

class FormFriends
{
private:
	string username;
	FriendAccessor accessor;
public:
	FormFriends();
	~FormFriends();
	void setUsername(const string);
	void listFriendView();
	void listBlockView();
	void menuFriendView();
	void addFriendView();
	void blockView();
	void unfriendView();
	void unblockView();
};
#pragma once

#include "Repository.h"
#include "Friend.h"

class RepositoryFriend : public Repository
{
private:
	int checkAdd();
public:
	~RepositoryFriend();

	int getFriendList(list<string> &);
	bool addFriend();
	bool delFriend();
};


#pragma once

#include "Repository.h"
#include "Account.h"
#include "assert.h"

class RepositoryAccount : public Repository
{
public:
	~RepositoryAccount();

	int isOnline();
	int checkAuthentication();
	bool updateStatus(const bool status);
	bool createAccount();
	int getAccountInfo(Account &);
};


#pragma once

#include "Repository.h"
#include "Message.h"

class RepositoryMessage : public Repository
{
public:
	~RepositoryMessage();

	bool sendMess(const bool);
	int getAllMess(list<Message> &);
	int getMess(int, list<Message> &);
};


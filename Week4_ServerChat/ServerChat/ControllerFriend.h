#pragma once

#include "Controller.h"

class ControllerFriend : public Controller
{
private:
	RepositoryFriend repFriend;

	void modifyListFrResponse(Document &, const list<string>);

	int setAddFrResponse();
	int setDelFrResponse();
	int setListFrResponse();
public:
	~ControllerFriend();

	string getResponse();
};


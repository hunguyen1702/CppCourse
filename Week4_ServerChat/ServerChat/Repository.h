#pragma once

#include "sqlite3.h"
#include "Definition.h"
#include <iostream>
#include <string>
#include <sstream>
#include <list>

using namespace std;

class Repository
{
protected:
	sqlite3 * dbAccess;
	string jsonString;
	int result;
	int rows, cols;
	char ** resultSet;
	char * errorMesg;
	
	int excuteGetTable(const string);
public:
	void setJsonString(const string);
	Repository();
	~Repository();
};


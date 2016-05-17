#include "stdafx.h"
#include "Repository.h"

Repository::Repository()
{
	result = sqlite3_open(CHAT_DATABASE, &this->dbAccess);
	if (result)
	{
		//cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(this->dbAccess) << endl << endl;
		sqlite3_close(this->dbAccess);
		this->~Repository();
		return;
	}
	//cout << "Opened Database..." << endl << endl;
}


Repository::~Repository()
{
	sqlite3_close(this->dbAccess);
}

void Repository::setJsonString(const string jsonString){
	this->jsonString = jsonString;
}

int Repository::excuteGetTable(const string query){
	result = sqlite3_get_table(this->dbAccess, query.c_str(), &resultSet, &rows, &cols, &errorMesg);
	if (result)
	{
		//cerr << "Error when excuting SQL query error: " << sqlite3_errmsg(dbAccess) << endl << endl;
		sqlite3_free_table(resultSet);
		sqlite3_free(errorMesg);
		return -1;
	}
	if (rows == 0) { 
		sqlite3_free_table(resultSet);
		sqlite3_free(errorMesg);
		return 0; 
	}
	if (rows > 0) { return 1; }
}
#include "stdafx.h"
#include "RepositoryFriend.h"

RepositoryFriend::~RepositoryFriend()
{
}

int RepositoryFriend::checkAdd(){
	ostringstream selectQuery;

	Friend fr(this->jsonString);

	selectQuery << "SELECT * FROM " << TBL_FRIENDS
		<< " WHERE " << FRIENDS_USER << "='" << fr.getUser() << "' AND "
		<< FRIENDS_FR << "='" << fr.getFriend() << "';";
	//cout << selectQuery.str().c_str() << endl;
	sqlite3_free_table(resultSet);
	return excuteGetTable(selectQuery.str());
}

int RepositoryFriend::getFriendList(list<string> & friendList){
	ostringstream selectQuery;

	Friend fr(this->jsonString);

	selectQuery << "SELECT "<< FRIENDS_FR <<" FROM " << TBL_FRIENDS
		<< " WHERE " << FRIENDS_USER << "='" << fr.getUser() << "';";
	//cout << selectQuery.str().c_str() << endl;
	
	int i = excuteGetTable(selectQuery.str());
	if (i == 1)
	{
		for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
		{
			friendList.push_back(resultSet[rowCtr]);
		}
		friendList.sort();
		return i;
	}
	return i;
}

bool RepositoryFriend::addFriend(){
	int i = checkAdd();
	if (i == 1) return false;

	ostringstream insertQuery;

	Friend fr(this->jsonString);

	insertQuery << "INSERT INTO " << TBL_FRIENDS << "(" << FRIENDS_USER << "," << FRIENDS_FR << ")"
		<< " VALUES ('" << fr.getUser() << "','" << fr.getFriend() << "');" << endl;
	insertQuery << "INSERT INTO " << TBL_FRIENDS << "(" << FRIENDS_USER << "," << FRIENDS_FR << ")"
		<< " VALUES ('" << fr.getFriend() << "','" << fr.getUser() << "');";
	//cout << insertQuery.str().c_str() << endl;


	result = sqlite3_exec(dbAccess, insertQuery.str().c_str(), NULL, NULL, &errorMesg);
	if (result){
		//cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(dbAccess) << endl << endl;
		sqlite3_free(errorMesg);
		return false;
	}
	sqlite3_free(errorMesg);
	return true;
}

bool RepositoryFriend::delFriend(){
	ostringstream insertQuery;

	Friend fr(this->jsonString);

	insertQuery << "DELETE FROM " << TBL_FRIENDS << " WHERE " << FRIENDS_USER << "='" << fr.getUser() 
		<< "' AND " << FRIENDS_FR << "='" << fr.getFriend() << "';";
	//cout << insertQuery.str().c_str() << endl;

	result = sqlite3_exec(dbAccess, insertQuery.str().c_str(), NULL, NULL, &errorMesg);
	if (result){
		//cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(dbAccess) << endl << endl;
		sqlite3_free(errorMesg);
		return true;
	}
	sqlite3_free(errorMesg);
	return false;
}
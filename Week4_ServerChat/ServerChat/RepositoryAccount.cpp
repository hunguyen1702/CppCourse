#include "stdafx.h"
#include "RepositoryAccount.h"

RepositoryAccount::~RepositoryAccount()
{
}

int RepositoryAccount::isOnline(){
	ostringstream selectQuery;

	Account account(this->jsonString);

	selectQuery << "SELECT " << USERS_ISONLINE << " FROM " << TBL_USERS
		<< " WHERE " << USERS_USERNAME << "='" << account.getUsername() << "';";
	//cout << selectQuery.str().c_str() << endl;
	int i = excuteGetTable(selectQuery.str());
	if (i == 1)
	{
		int isOnl = atoi(resultSet[cols]);
		sqlite3_free_table(this->resultSet);
		return isOnl;
	}
	//cerr << "error occured!!!: " << i << endl;
	return -1;
}

int RepositoryAccount::checkAuthentication(){
	ostringstream selectQuery;

	Account account(this->jsonString);

	selectQuery << "SELECT * FROM " << TBL_USERS
		<< " WHERE " << USERS_USERNAME << "='" << account.getUsername() 
		<< "' AND " << USERS_PASSWORD << "='" << account.getPassword() << "';";
	//cout << selectQuery.str().c_str() << endl;
	int i = excuteGetTable(selectQuery.str());
	if (i == 1){
		for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
		{
			if (!account.getUsername().compare(resultSet[rowCtr * cols]) && !account.getPassword().compare(resultSet[rowCtr * cols + 1]))
			{
				sqlite3_free_table(resultSet);
			}
		}
	}
	return i;
}

bool RepositoryAccount::updateStatus(bool status){
	ostringstream updateQuery;

	Account account(this->jsonString);

	updateQuery << "UPDATE " << TBL_USERS << " SET " << USERS_ISONLINE << "=" << status
		<< " WHERE " << USERS_USERNAME << "='" << account.getUsername() << "';";
	//cout << updateQuery.str().c_str() << endl;

	result = sqlite3_exec(dbAccess, updateQuery.str().c_str(), NULL, NULL, &errorMesg);
	if (result){
		//cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(dbAccess) << endl << endl;
		sqlite3_free(errorMesg);
		return false;
	}
	sqlite3_free(errorMesg);
	return true;
}

bool RepositoryAccount::createAccount(){
	ostringstream insertQuery;

	Account account(this->jsonString);

	int i = getAccountInfo(account);
	if (i == 1)
	{
		cerr << "this account is already exist" << endl;
		return false;
	}

	insertQuery << "INSERT INTO " << TBL_USERS << "(" << USERS_USERNAME << "," << USERS_PASSWORD << "," << USERS_MAIL << ") " 
		<< " VALUES ('" << account.getUsername() << "','" << account.getPassword() << "','" << account.getMail() << "');";
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

int RepositoryAccount::getAccountInfo(Account & acc){
	ostringstream selectQuery;

	Account account(this->jsonString);

	selectQuery << "SELECT * FROM " << TBL_USERS
		<< " WHERE " << USERS_USERNAME << "='" << account.getUsername() << "';";
	//cout << selectQuery.str().c_str() << endl;

	int i = excuteGetTable(selectQuery.str());
	if (i == 1)
	{
		//cout << resultSet[cols + 5] << endl;
		//cout << resultSet[cols + 6] << endl;
		acc.setAccount(resultSet[cols], resultSet[cols + 2], resultSet[cols + 3],
			resultSet[cols + 4], atoi(resultSet[cols + 5]), atoi(resultSet[cols + 6]));
	}
	return i;
}
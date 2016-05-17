#include "stdafx.h"
#include "RepositoryMessage.h"


RepositoryMessage::~RepositoryMessage()
{
}

bool RepositoryMessage::sendMess(bool wasRead)
{
	ostringstream insertQuery;

	Message mess(this->jsonString);

	insertQuery << "INSERT INTO " << TBL_MESSAGES << "(" << MESSAGES_SENDER << "," << MESSAGES_RECEIVER 
		<< "," << MESSAGES_CONTENT << "," << MESSAGES_WAS_READ << ") VALUES ('" 
		<< mess.getSender() << "','" << mess.getReceiver() 
		<< "','" << mess.getContent() << "'," << wasRead << ");";
	
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

int RepositoryMessage::getAllMess(list<Message> & messageList)
{
	ostringstream selectQuery;

	Message mess(this->jsonString);

	selectQuery << "SELECT * FROM " << TBL_MESSAGES
		<< " WHERE " << MESSAGES_RECEIVER << "='" << mess.getReceiver() << "';";
	//cout << selectQuery.str().c_str() << endl;

	int i = excuteGetTable(selectQuery.str());
	if (i == 1)
	{
		for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
		{
			Message mess(resultSet[rowCtr * cols + 1], resultSet[rowCtr * cols + 2], resultSet[rowCtr * cols + 3]);
			//messageList.insert(messageList.begin(), mess);
			messageList.push_back(mess);
		}
	}
	return i;
}

int RepositoryMessage::getMess(int limit, list<Message> & messageList)
{
	ostringstream selectQuery;

	Message mess(this->jsonString);

	selectQuery << "SELECT * FROM " << TBL_MESSAGES
		<< " WHERE " << MESSAGES_RECEIVER << "='" << mess.getReceiver() 
		<< "' OR " << MESSAGES_SENDER << "='" << mess.getReceiver() << "' ORDER BY " << MESSAGES_ID << " DESC LIMIT " << limit << ";";
	//cout << selectQuery.str().c_str() << endl;

	int i = excuteGetTable(selectQuery.str());
	if (i == 1)
	{
		for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
		{
			Message mess(resultSet[rowCtr * cols + 1], resultSet[rowCtr * cols + 2], resultSet[rowCtr * cols + 3]);
			messageList.insert(messageList.begin(), mess);
			//messageList.push_back(mess);
		}
	}

	return i;
}

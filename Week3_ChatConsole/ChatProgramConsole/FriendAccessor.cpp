#include "FriendAccessor.h"


FriendAccessor::FriendAccessor()
{
}


FriendAccessor::~FriendAccessor()
{
}

int FriendAccessor::checkWrongInput(const string & usr, const string & input){
	if (!usr.compare(input)) {
		cerr << "\t YOU HAVE INPUT YOUR OWN ACCOUNT!!!" << endl;
		return 1;
	}
	return 0;
}

int FriendAccessor::checkBlockYet(const string & usr, const string & block){
	//0: FILE ERROR
	//1: HAS NOT BEEN BLOCKED
	//-1: HAS BEEN BLOCKED
	string _usr, _block;
	ifstream infile;
	infile.open(_BLOCK_LIST, ios::in);
	if (!infile)
	{
		//cerr << "CHECK BLOCK USER ERROR!!!" << endl;
		infile.close();
		return 0;
	}
	while (getline(infile, _usr, '|'))
	{
		if (!_usr.compare(usr))
		{
			getline(infile, _block, '|');
			if (!_block.compare(block))
			{
				//cerr << "THIS ACCOUNT HAS BEEN BLOCKED!!!" << endl;
				infile.close();
				return -1;
			}
		}
		getline(infile, _usr);
	}
	infile.close();
	return 1;
}

int FriendAccessor::checkAddYet(const string & usr, const string & addAcc){
	//0: FILE ERROR
	//1: HAS NOT BEEN ADDED
	//-1: HAS BEEN ADDED
	string _usr, _addAcc;
	ifstream infile;
	infile.open(_FRIEND_LIST, ios::in);
	if (!infile)
	{
		//cerr << "CHECK FRIEND ERROR!!!" << endl;
		infile.close();
		return 0;
	}
	while (getline(infile, _usr, '|'))
	{
		if (!_usr.compare(usr))
		{
			getline(infile, _addAcc, '|');
			if (!_addAcc.compare(addAcc))
			{
				//cerr << "THIS ACCOUNT HAS BEEN ADDED!!!" << endl;
				infile.close();
				return -1;
			}
		}
		getline(infile, _usr);
	}
	//cout << "THIS ACCOUNT HAS NOT BEEN ADDED" << endl;
	infile.close();
	return 1;
}

int FriendAccessor::blockAccount(const string & usr, const string & block){
	if (checkWrongInput(usr, block)) return 0;
	AccountAccessor acc; int i;
	if ((i = acc.checkExist(block)) != -1){
		(i == 1) ? cerr << "INVALID USERNAME" << endl
			: cerr << "FILE ACCOUNT INFO ERROR" << endl;
		return 0;
	}
	if ((i = checkBlockYet(usr, block)) != 1){
		(i == -1) ? cerr << "YOU HAVE BLOCK THIS ACCOUNT ALREADY" << endl
			: cerr << "FILE ACCOUNT INFO ERROR" << endl;
		return 0;
	}
	if ((i = checkAddYet(usr, block)) == -1) {
		unfriend(usr, block);
	}
	ofstream outfile;
	outfile.open(_BLOCK_LIST, ios::app);
	if (!outfile){
		cerr << "WRITE BLOCK TO FILE ERROR!!!" << endl;
		outfile.close();
		return 0;
	}
	//write to file
	outfile << usr << '|' << block << '|' << endl;
	outfile << block << '|' << usr << '|' << endl;
	cout << "BLOCK SUCCESSFUL!!!" << endl;
	outfile.close();
	return 1;
}

int FriendAccessor::addAccount(const string & usr, const string & addAcc){
	if (checkWrongInput(usr, addAcc)) return 0;
	AccountAccessor acc; int i;
	if ((i = acc.checkExist(addAcc)) != -1){
		(i == 1) ? cerr << "\t INVALID USERNAME" << endl
			: cerr << "\t FILE ACCOUNT INFO ERROR" << endl;
		return 0;
	}
	if ((i = checkAddYet(usr, addAcc)) != 1){
		(i == -1) ? cerr << "\t YOU HAVE ADDED THIS ACCOUNT ALREADY" << endl
			: cerr << "\t FILE ACCOUNT INFO ERROR" << endl;
		return 0;
	}
	if ((i == checkBlockYet(usr, addAcc)) != 1){
		(i == -1) ? cerr << "\t YOU HAVE BLOCKED THIS ACCOUNT ALREADY" << endl
			: cerr << "\t FILE ACCOUNT INFO ERROR" << endl;
		return 0;
	}
	ofstream outfile;
	outfile.open(_FRIEND_LIST, ios::app);
	if (!outfile){
		cerr << "\t WRITE BLOCK TO FILE ERROR!!!" << endl;
		outfile.close();
		return 0;
	}
	//write to file
	outfile << usr << '|' << addAcc << '|' << endl;
	outfile << addAcc << '|' << usr << '|' << endl;
	cout << "\t ADD SUCCESSFUL!!!" << endl;
	outfile.close();
	return 1;
}

int FriendAccessor::unfriend(const string & usr, const string & unfriend){
	string _usr, _unfriend, line;
	ifstream infile;
	ofstream outfile;
	int i;
	if ((i = checkAddYet(usr, unfriend)) != -1){
		(i == 1) ? cerr << "YOU HAVE NOT ADDED THIS ACCOUNT" << endl
			: cerr << "FILE ACCOUNT INFO ERROR" << endl;
		return 0;
	}
	infile.open(_FRIEND_LIST, ios::in);
	outfile.open("temp.unfr", ios::out);
	if ((!infile) || (!outfile)){
		cerr << "UNFRIEND ERROR!!!" << endl;
		return 0;
	}
	//copy all line from file OnlineUsers.txt to temp except argument string
	while (getline(infile, line)){
		istringstream data(line);
		getline(data, _usr, '|');
		getline(data, _unfriend, '|');
		if ((!_usr.compare(usr)) && (!_unfriend.compare(unfriend))) continue;
		if ((!_usr.compare(unfriend)) && (!_unfriend.compare(usr))) continue;
		outfile << _usr << '|' << _unfriend << '|' << endl;
	}
	outfile.close();
	infile.close();
	//remove old file & rename "temp" to "OnlineUser.txt"
	remove(_FRIEND_LIST.c_str());
	rename("temp.unfr", _FRIEND_LIST.c_str());
	cout << "UNFRIEND SUCCESSFUL!!!" << endl;
	return 1;
}

int FriendAccessor::unblock(const string & usr, const string & unBlock){
	string _usr, _unblock, line;
	ifstream infile;
	ofstream outfile;
	int i;
	if ((i = checkBlockYet(usr, unBlock)) != -1){
		(i == 1) ? cerr << "YOU HAVE NOT BLOCKED THIS ACCOUNT" << endl
			: cerr << "FILE ACCOUNT INFO ERROR" << endl;
		return 0;
	}
	infile.open(_BLOCK_LIST, ios::in);
	outfile.open("temp.unblk", ios::out);
	if ((!infile) || (!outfile)){
		cerr << "UNBLOCK ERROR!!!" << endl;
		return 0;
	}
	//copy all line from file OnlineUsers.txt to temp except argument string
	while (getline(infile, line)){
		istringstream data(line);
		getline(data, _usr, '|');
		getline(data, _unblock, '|');
		if ((!_usr.compare(usr)) && (!_unblock.compare(unBlock))) continue;
		if ((!_usr.compare(unBlock)) && (!_unblock.compare(usr))) continue;
		outfile << _usr << '|' << _unblock << '|' << endl;
	}
	outfile.close();
	infile.close();
	//remove old file & rename "temp" to "OnlineUser.txt"
	remove(_BLOCK_LIST.c_str());
	rename("temp.unblk", _BLOCK_LIST.c_str());
	cout << "UNBLOCK SUCCESSFUL!!!" << endl;
	return 1;
}

int FriendAccessor::getFriendList(const string & usr, vector<string> & listFriend){
	string _usr, _friend;
	ifstream infile;
	infile.open(_FRIEND_LIST, ios::in);
	if (!infile)
	{
		cout << "CAN NOT ACCESS DB" << endl;
		infile.close();
		return 0;
	}
	//read each line
	while (getline(infile, _usr, '|')){
		if (!_usr.compare(usr))
		{
			getline(infile, _friend, '|');
			listFriend.insert(listFriend.begin(), _friend);
		}
		getline(infile, _usr);
	}
	infile.close();
	return 1;
}

int FriendAccessor::getBlockList(const string & usr, vector<string> & listBlock){
	string _usr, _block;
	ifstream infile;
	infile.open(_BLOCK_LIST, ios::in);
	if (!infile)
	{
		cout << "CAN NOT ACCESS DB" << endl;
		infile.close();
		return 0;
	}
	//read each line
	while (getline(infile, _usr, '|')){
		if (!_usr.compare(usr))
		{
			getline(infile, _block, '|');
			listBlock.insert(listBlock.begin(), _block);
		}
		getline(infile, _usr);
	}
	infile.close();
	return 1;
}
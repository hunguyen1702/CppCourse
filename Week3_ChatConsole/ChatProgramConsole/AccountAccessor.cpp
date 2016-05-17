#include "AccountAccessor.h"

//constructor
AccountAccessor::AccountAccessor()
{
}


AccountAccessor::~AccountAccessor()
{
}

int AccountAccessor::checkLogin(const string & usr){ 
	//0: ERROR
	//1: CAN LOGIN

	string line;
	//open file AccountOnline.txt to check if usr name has login already
	ifstream infile;
	infile.open(_ONL_USR, ios::in);
	if (!infile)
	{
		cerr << "FILE ONLINE ERROR" << endl;
		infile.close();
		return 0;
	}
	//read to the end of file
	while (getline(infile,line))
	{
		//if meet match print error & return
		if (!line.compare(usr)){ 
			cerr << "USER IS ONLINE!!!" << endl;
			infile.close();
			return 0;
		}
	}
	//if eof return 1 -> can login
	infile.close();
	return 1;
}

int AccountAccessor::checkExist(const string & usr){
	//0: ERROR
	//1: USERNAME HASN'T BEEN USE 
	//-1: USRNAME HAS BEEN USE
	string line;
	ifstream infile;
	infile.open(_ACC_INFO, ios::in);
	if (!infile)
	{
		//cerr << "FILE ACCOUNT INFO ERROR" << endl;
		infile.close();
		return 0;
	}
	//read all line & get first word of line until meet match username
	while (getline(infile, line, '|'))
	{
		//compare to argument
		if (!line.compare(usr))
		{
			//cerr << "USERNAME HAS BEEN USED" << endl;
			infile.close();
			return -1;
		}
		//if not match read the next line
		getline(infile, line);
	}
	//if eof & can't find username then return 1 -> can create that username
	infile.close();
	return 1;
}

int AccountAccessor::checkAuthentication(const LoginInfo & info){
	//0: ERROR
	//1: SUCCESS 
	string usr, pass;
	ifstream infile;
	infile.open(_ACC_INFO, ios::in);
	if (!infile)
	{
		cerr << "FILE ACCOUNT INFO ERROR!!!" << endl;
		infile.close();
		return 0;
	}
	//read all line & get first word of line until meet match username
	while (getline(infile, usr, '|'))
	{
		//compare to argument
		if (!usr.compare(info.username))
		{
			getline(infile, pass, '|');
			if (!pass.compare(info.password)){
				infile.close();
				return 1;
			}
		}
		//if not match read the next line
		getline(infile, usr);
	}
	//if eof & can't find username then return 0 -> can't login
	cerr << "WRONG USERNAME OR PASSWORD!!!" << endl;
	infile.close();
	return 0;
}

int AccountAccessor::createUser(const AccountInfo & info){
	//0: ERROR
	//1: SUCCESS 
	//open file to write
	ofstream outfile;
	outfile.open(_ACC_INFO, ios::app);
	if (!outfile){
		cerr << "WRITE INFO TO FILE ERROR!!!" << endl;
		outfile.close();
		return 0;
	}
	//write user info into AccountInfo.txt
	outfile << info.getUsername() << "|";
	outfile << info.getPassword() << "|";
	outfile << info.getAge() << "|";
	outfile << info.getFullname() << "|";
	outfile << info.getSex() << "|";
	outfile << info.getAddr() << "|" << endl;
	////////////////////////////
	cout << "REGIST SUCCESSFUL!!!" << endl;
	outfile.close();
	return 1;
}

int AccountAccessor::userLogin(const LoginInfo & info){
	//0: ERROR
	//1: SUCCESS 
	
	//1st check if that account has login
	if (!checkAuthentication(info)) return 0;
	if (!checkLogin(info.username)) return 0;

	//open file AccountOnline.txt to write new username
	ofstream outfile;
	outfile.open(_ONL_USR, ios::app);
	if (!outfile){
		cerr << "WRITE INFO TO FILE ERROR!!!" << endl;
		outfile.close();
		return 0;
	}
	//write username into OnlineAccount.txt
	outfile << info.username << endl;
	///////////////////////////////////////
	cout << "LOGIN SUCCESSFUL!!!" << endl;
	outfile.close();
	return 1;
}

int AccountAccessor::userLogout(const string & usr){
	//0: ERROR
	//1: SUCCESS 

	string username;
	ifstream infile;
	ofstream outfile;
	infile.open(_ONL_USR, ios::in);
	outfile.open("temp.acc", ios::out);
	if ((!infile) || (!outfile)){
		cerr << "LOGOUT ERROR!!!" << endl;
		return 0;
	}
	//copy all line from file OnlineUsers.txt to temp except argument string
	while (getline(infile, username)){
		if (!username.compare(usr)) continue;
		outfile << username << endl;
	}
	outfile.close();
	infile.close();
	//remove old file & rename "temp" to "OnlineUser.txt"
	remove(_ONL_USR.c_str());
	rename("temp.acc", _ONL_USR.c_str());
	cout << "LOGOUT SUCCESSFUL!!!" << endl;
	return 1;
}

int AccountAccessor::getUserInfo(const string & usrname, AccountInfo & accInfo){
	//0: ERROR
	//1: SUCCESS 

	string _user, _pass, _fname, _addr, _age, _sex;
	int age, sex;
	//open file AccountOnline.txt to check if usr name has login already
	ifstream infile;
	infile.open(_ACC_INFO, ios::in);
	if (!infile)
	{
		cerr << "GET USER INFO ERROR!!!" << endl;
		infile.close();
		return 0;
	}
	//read first string represent for username delimit by '|'
	while (getline(infile, _user, '|'))
	{
		//if user name match then get all info
		if (!_user.compare(usrname)){
			getline(infile, _pass, '|');
			getline(infile, _age, '|');
			age = stoi(_age); // convert string to int
			getline(infile, _fname, '|');
			getline(infile, _sex, '|');
			sex = stoi(_sex); // convert string to int
			getline(infile, _addr, '|');
			accInfo.setInfo(_user, _pass, age, _fname, sex, _addr);
			break;
		}
		//if username not match move to next line
		getline(infile, _user);
	}
	return 1;
}
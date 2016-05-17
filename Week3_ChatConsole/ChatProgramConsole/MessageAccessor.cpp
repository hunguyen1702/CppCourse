#include "MessageAccessor.h"

MessageAccessor::MessageAccessor()
{
	reader.open(_MESS_DB, ios::in);
}


MessageAccessor::~MessageAccessor()
{
	reader.close();
}

void MessageAccessor::setBeginning(){
	reader.clear();
	reader.seekg(0, ios::beg);
}

int MessageAccessor::getAllMess(const string & toUsr, vector<MessageDetail> & listMess){
	string receiver, sender, mess, time;
	//each time refresh & get all message return the stream to the beginning of file
	setBeginning();
	listMess.clear();
	if (!reader)
	{
		cerr << "CAN NOT ACCESS DB" << endl;
		return 0;
	}
	//read each line
	while (getline(reader, receiver, '|')){
		//check the receiver if match with current user
		if (!receiver.compare(toUsr))
		{
			//if match create a new obj to store info & push to vector
			getline(reader, sender, '|');
			getline(reader, time, '|');
			getline(reader, mess, '|');
			MessageDetail _mDetail;
			_mDetail.setMess(sender, toUsr, mess, time);
			listMess.insert(listMess.begin(),_mDetail);
		}
		//if not match read the next line
		getline(reader, receiver);
	}
	return 1;
}

int MessageAccessor::getMess(const string & toUsr, vector<MessageDetail> & listMess, int limit){
	string receiver, sender, mess, time;
	if (!reader)
	{
		cout << "CAN NOT ACCESS DB" << endl;
		return 0;
	}
	//read each line
	while (getline(reader, receiver, '|')){
		if (limit == 0)
		{
			break;
		}
		//check the receiver if match with current user
		if (!receiver.compare(toUsr))
		{
			//if match create a new obj to store info & push to vector
			getline(reader, sender, '|');
			getline(reader, time, '|');
			getline(reader, mess, '|');
			MessageDetail _mDetail;
			_mDetail.setMess(sender, toUsr, mess, time);
			listMess.insert(listMess.begin(), _mDetail);
			limit--;
		}
		//if not match read the next line
		getline(reader, receiver);
	}
	return 1;
}

int MessageAccessor::sendMess(const MessageDetail & mess){
	FriendAccessor frAcc; int i;
	if ((i = frAcc.checkBlockYet(mess.getFromUsr(), mess.getFromUsr())) != 1)
	{
		(i == -1) ? cerr << "YOU HAVE BLOCK THIS ACCOUNT" << endl
			: cerr << "FILE BLOCK LIST ERROR" << endl;
		return 0;
	}
	if ((i = frAcc.checkBlockYet(mess.getToUsr(), mess.getFromUsr())) != 1)
	{
		(i == -1) ? cerr << "THIS USER HAS BLOCKED YOU" << endl
			: cerr << "FILE BLOCK LIST ERROR" << endl;
		return 0;
	}
	if ((i = frAcc.checkAddYet(mess.getFromUsr(), mess.getToUsr())) != -1)
	{
		(i == 1) ? cerr << "YOU HAVEN\'T ADDED THIS ACCOUNT AS YOUR FRIEND" << endl
			: cerr << "FILE FRIEND LIST ERROR" << endl;
		return 0;
	}
	ofstream outfile;
	outfile.open(_MESS_DB, ios::app);
	if (!outfile){
		cerr << "WRITE MESSAGE TO FILE ERROR!!!" << endl;
		outfile.close();
		return 0;
	}
	//write message info into AllMessages.txt
	outfile << mess.getToUsr() << "|";
	outfile << mess.getFromUsr() << "|";
	outfile << mess.getTime() << "|";
	outfile << mess.getMess() << "|" << endl;
	////////////////////////////
	cout << "SEND MESSAGE SUCCESSFUL!!!" << endl;
	outfile.close();
	return 1;
}

int MessageAccessor::delMess(const string & toUsr, vector<MessageDetail> & listMess, int num){
	string receiver, sender, mess;
	string _sender, _mess;
	string line;
	
	_sender = listMess.at(num).getFromUsr();
	_mess = listMess.at(num).getMess();

	ifstream infile;
	ofstream outfile;
	infile.open(_MESS_DB, ios::in);
	outfile.open("temp.mess", ios::out);
	if ((!infile) || (!outfile)){
		cerr << "DELETE MESSAGE ERROR!!!" << endl;
		return 0;
	}
	//copy all line from file AllMessages.txt to temp except argument string
	while (getline(infile, line)){
		istringstream data(line);
		getline(data, receiver, '|');
		getline(data, sender, '|');
		getline(data, mess, '|');
		if (( !receiver.compare(toUsr) ) && ( !sender.compare(_sender) ) && ( !mess.compare(_mess) )) continue;
		outfile << receiver << '|';
		outfile << sender << '|';
		outfile << mess << '|' << endl;
	}
	outfile.close();
	infile.close();
	//remove old file & rename "temp.mess" to "AllMessages.txt"
	remove(_MESS_DB.c_str());
	rename("temp.mess", _MESS_DB.c_str());
	cout << "DELETE MESSAGE SUCCESSFUL!!!" << endl;
	return 1;
}
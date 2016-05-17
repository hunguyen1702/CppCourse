#include "FormMessage.h"

FormMessage::FormMessage()
{
}


FormMessage::~FormMessage()
{
}

void FormMessage::getSystemTime(string & curTime){
	string temp;
	time_t timer;
	time(&timer);
	temp = string(ctime(&timer));
	temp.erase(temp.length() - 1);
	curTime = temp;
}

void FormMessage::setUsername(const string usr){
	this->username = usr;
}

//fisrt View of module message
void FormMessage::listMessView(){
	int choice = 0;
	while (choice != 3)
	{
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Message\n", this->username.c_str());
		printf("\t|----------------------------|\n");
		printf("\t|1. Read messages            |\n");
		printf("\t|2. Send messages            |\n");
		printf("\t|3. Back to previous menu    |\n");
		printf("\t------------------------------\n");
		printf("\tPlease choose: ");
		cin >> choice; cin.ignore();
		switch (choice)
		{
		case 1:
			this->briefMessView();
			break;
		case 2:
			this->sendMessView();
			break;
		case 3:
			//return to previous menu
			break;
		default:
			while (cin.get() != '\n')
			{
				cin.clear();
				cin.ignore();
			}
			cout << "\t INVALID CHOICE" << endl;
			break;
		}
	}
}
//using to read detail all text of message
void FormMessage::readMessView(int num){
	system("cls");
	printf("\t------------------------------\n");
	printf("\t|Chat Program > %s > Message > Read Message > %ld\n", this->username.c_str(), num);
	printf("\t------------------------------\n");
	cout << "\t|From: " << listMess.at(num - 1).getFromUsr() << " at " << listMess.at(num - 1).getTime() << endl;
	cout << "\t|Message:" << endl;
	cout << "\t|\t" << listMess.at(num - 1).getMess() << endl;
	printf("\t------------------------------\n");
	system("pause");
}
//using to view brief info of all mess
void FormMessage::briefMessView(){
	int i = 1, iChoice;
	while (true)
	{
		i = 1; iChoice = 0;
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Message > Read Message\n", this->username.c_str());
		printf("\t------------------------------\n");
		if (!accessor.getAllMess(this->username, this->listMess))
		{
			_getch(); break;
		}

		for (auto mess : listMess)
		{
			string briefMess = mess.getMess().substr(0, 10);
			cout << "\t|" << i++ << ". " << mess.getFromUsr() << " at " 
				<< mess.getTime() << " " << briefMess << "...<Read more>" << endl;
		}
		printf("\t------------------------------\n");
		printf("\t|<Press 'b' to return previous menu>\n");
		printf("\t|<Press enter to more function>\n");
		printf("\t------------------------------\n");
		if (toupper(_getch()) == 'B')
		{
			break;
		}
		printf("\t------------------------------\n");
		printf("\t|<Press message number to see detail of that message>\n");
		printf("\t------------------------------\n");
		printf("\t|Please choose: ");
		cin >> iChoice;
		if ((iChoice > listMess.size()) || (iChoice < 1))
		{
			while (cin.get() != '\n')
			{
				cin.clear();
				cin.ignore();
			}
			cout << "INVALID CHOICE!!!" << endl;
			continue;
		}
		readMessView(iChoice);
	}
}
//using to send an message
void FormMessage::sendMessView(){
	MessageDetail messDetail;
	string receiver, mess, time;
	while (true)
	{
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Message > Send Message\n", this->username.c_str());
		printf("\t------------------------------\n");
		printf("\t|Press any key to continue, 'b' to back to previous menu\n");
		if (toupper(_getch()) == 'B')
		{
			break;
		}
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Message > Send Message\n", this->username.c_str());
		printf("\t------------------------------\n");
		printf("\t|To:\t");
		getline(cin, receiver, '\n');
		printf("\t|Mess:\t");
		getline(cin, mess, '\n');
		getSystemTime(time);
		messDetail.setMess(this->username, receiver, mess, time);
		if (accessor.sendMess(messDetail)){
			_getch(); break;
		}
		_getch();
	}
}

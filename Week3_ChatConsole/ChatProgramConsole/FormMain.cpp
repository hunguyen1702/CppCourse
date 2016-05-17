#include "FormMain.h"


FormMain::FormMain()
{
	formAccount = new FormAccount;
	formFriends = new FormFriends;
	formMessage = new FormMessage;
}


FormMain::~FormMain()
{
	delete(formAccount);
	delete(formFriends);
	delete(formMessage);

}

void FormMain::setUsername(const string usr){
	this->username = usr;
	formFriends->setUsername(usr);
	formMessage->setUsername(usr);
}

void FormMain::accountView(){
	int choice;
	while (true)
	{
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s\n", this->username.c_str());
		printf("\t|----------------------------|\n");
		printf("\t|1. Messages                 |\n");
		printf("\t|2. Friends                  |\n");
		printf("\t|3. Account Information      |\n");
		printf("\t|4. Logout                   |\n");
		printf("\t------------------------------\n");
		printf("\tPlease choose: ");
		cin >> choice; cin.ignore();
		switch (choice)
		{
		case 1:
			formMessage->listMessView();
			break;
		case 2:
			formFriends->menuFriendView();
			break;
		case 3:
			formAccount->infoView(this->username);
			break;
		case 4:
			//Logout & comeback to login view
			formAccount->logout(this->username);
			return;
		default:
			while (cin.get() != '\n')
			{
				cin.clear();
				cin.ignore();
			}
			cout << "INVALID CHOICE" << endl;
			break;
		}
	}
}

void FormMain::runProgram(){
	string usr;
	while (true)
	{
		system("cls");
		formAccount->listAccView(usr);
		if (usr.empty()) return;
		this->setUsername(usr);
		this->accountView();
		usr.clear();
	}
}
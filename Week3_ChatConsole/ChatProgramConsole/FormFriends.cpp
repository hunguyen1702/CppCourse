#include "FormFriends.h"


FormFriends::FormFriends()
{
}


FormFriends::~FormFriends()
{
}

void FormFriends::setUsername(const string usr){
	this->username = usr;
}

void FormFriends::menuFriendView(){
	int choice = 0;
	while (choice != 7)
	{
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Friend\n", this->username.c_str());
		printf("\t|----------------------------|\n");
		printf("\t|1. Friend List              |\n");
		printf("\t|2. Block List               |\n");
		printf("\t|3. Add Friend               |\n");
		printf("\t|4. Block                    |\n");
		printf("\t|5. Unfriend                 |\n");
		printf("\t|6. UnBlock                  |\n");
		printf("\t|7. Back to previous         |\n");
		printf("\t------------------------------\n");
		printf("\tPlease choose: ");
		cin >> choice; cin.ignore();
		switch (choice)
		{
		case 1:
			this->listFriendView();
			break;
		case 2:
			this->listBlockView();
			break;
		case 3:
			this->addFriendView();
			break;
		case 4:
			this->blockView();
			break;
		case 5:
			this->unfriendView();
			break;
		case 6:
			this->unblockView();
			break;
		case 7:
			//return to previous menu
			break;
		default:
			while (cin.get() != '\n')
			{
				cin.clear();
				cin.ignore();
			}
			cout << "\t INVALID CHOICE!!!" << endl;
			break;
		}
	}
}

void FormFriends::listFriendView(){
	vector<string> listFriend;
	this->accessor.getFriendList(this->username, listFriend);
	int i = 1;
	system("cls");
	printf("\t------------------------------\n");
	printf("\t|Chat Program > %s > Friend > Friend List\n", this->username.c_str());
	printf("\t|----------------------------|\n");
	if (listFriend.size() == 0){
		printf("\t|You have no friend\n");
	} else {
		for (auto fr : listFriend)
			printf("\t|%ld.\t%s\n", i++, fr.c_str());
	}
	printf("\t|----------------------------|\n");

	_getch();
}

void FormFriends::listBlockView(){
	vector<string> listBlock;
	this->accessor.getBlockList(this->username, listBlock);
	int i = 1;
	system("cls");
	printf("\t------------------------------\n");
	printf("\t|Chat Program > %s > Friend > Block List\n", this->username.c_str());
	printf("\t|----------------------------|\n");
	if (listBlock.size() == 0){
		printf("\t|You have blocked no account yet\n");
	}
	else {
		for (auto fr : listBlock)
			printf("\t|%ld.\t%s\n", i++, fr.c_str());
	}
	printf("\t|----------------------------|\n");
	_getch();
}

void FormFriends::addFriendView(){
	string usr;
	while (true)
	{
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Friend > Add Friend\n", this->username.c_str());
		printf("\t------------------------------\n");
		printf("\t|Press any key to continue, 'b' to back to previous menu\n");
		if (toupper(_getch()) == 'B')
		{
			break;
		}
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Friend > Add Friend\n", this->username.c_str());
		printf("\t------------------------------\n");
		printf("\t|Enter an username:\t");
		getline(cin, usr, '\n');
		if (accessor.addAccount(this->username, usr)){
			_getch(); break;
		}
		_getch();
	}
}

void FormFriends::blockView(){
	string usr;
	while (true)
	{
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Friend > Block\n", this->username.c_str());
		printf("\t------------------------------\n");
		printf("\t|Press any key to continue, 'b' to back to previous menu\n");
		if (toupper(_getch()) == 'B')
		{
			break;
		}
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Friend > Block\n", this->username.c_str());
		printf("\t------------------------------\n");
		printf("\t|Enter an username:\t");
		getline(cin, usr, '\n');
		if (accessor.blockAccount(this->username, usr)){
			_getch(); break;
		}
		_getch();
	}
}

void FormFriends::unfriendView(){
	string usr;
	while (true)
	{
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Friend >  Unfriend\n", this->username.c_str());
		printf("\t------------------------------\n");
		printf("\t|Press any key to continue, 'b' to back to previous menu\n");
		if (toupper(_getch()) == 'B')
		{
			break;
		}
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Friend > Unfriend\n", this->username.c_str());
		printf("\t------------------------------\n");
		printf("\t|Enter an username:\t");
		getline(cin, usr, '\n');
		if (accessor.unfriend(this->username, usr)){
			_getch(); break;
		}
		_getch();
	}
}

void FormFriends::unblockView(){
	string usr;
	while (true)
	{
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Friend >  Unblock\n", this->username.c_str());
		printf("\t------------------------------\n");
		printf("\t|Press any key to continue, 'b' to back to previous menu\n");
		if (toupper(_getch()) == 'B')
		{
			break;
		}
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > %s > Friend > Unblock\n", this->username.c_str());
		printf("\t------------------------------\n");
		printf("\t|Enter an username:\t");
		getline(cin, usr, '\n');
		if (accessor.unblock(this->username, usr)){
			_getch(); break;
		}
		_getch();
	}
}
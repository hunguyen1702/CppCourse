#include "FormAccount.h"




FormAccount::FormAccount()
{
}


FormAccount::~FormAccount()
{
}

int FormAccount::checkAge(int const & age){
	if (age < 10){
		cout << "\t YOU MUST BE AT LEAST 10 YEARS OLD TO USE THIS PROGRAM" << endl;
		return 0;
	}
	return 1;
}

int FormAccount::checkLength(string const & text, string const field){
	if (text.length() < 6){
		cout << "\t " << field << " MUST AT LEAST 6 CHARACTERS!!!" << endl;
		return 0;
	}
	return 1;
}

int FormAccount::checkPwdMatch(string const & pwd, string const & rpwd){
	if (pwd.compare(rpwd) != 0){
		cout << "\t PASSWORD DON\'T MATCH" << endl;
		return 0;
	}
	return 1;
}

int FormAccount::checkSpace(string const & usr){
	if (usr.find(" ") != string::npos){
		cout << "\t USERNAME CONTAINS SPACE!!!" << endl;
		return 0;
	}
	return 1;
}

void FormAccount::listAccView(string & username){
	int choice;
	do 
	{
		printf("\t------------------------------\n");
		printf("\t|Chat Program                |\n");
		printf("\t|----------------------------|\n");
		printf("\t|1. Login                    |\n");
		printf("\t|2. Register                 |\n");
		printf("\t|3. Quit                     |\n");
		printf("\t------------------------------\n");
		printf("\tPlease choose: ");
		cin >> choice;
		cin.clear();
		cin.ignore();
		switch (choice)
		{
		case 1:
			loginView(username);
			if (!username.empty()) return;
			break;
		case 2:
			registView();
			break;
		case 3:
			//return to main & exit program
			return;
		default:
			cout << "\t INVALID CHOICE" << endl;
			break;
		}
		system("cls");
	} while (true);
}

void FormAccount::loginView(string & username){
	string usr, pwd;
	LoginInfo info;
	system("cls");
	while (true){
		printf("\t------------------------------\n");
		printf("\t|Chat Program > Login        |\n");
		printf("\t|----------------------------|\n");
		printf("\t|Press any key to continue, 'b' to back to previous menu\n");
		if (toupper(_getch()) == 'B')
		{
			break;
		}
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > Login        |\n");
		printf("\t|----------------------------|\n");
		printf("\t|Username:\t");
		getline(cin, usr, '\n');
		printf("\t|Password:\t");
		getline(cin, pwd, '\n');
		printf("\t------------------------------\n");
		info.setInfo(usr, pwd);
		if (accessor.userLogin(info)) break;
		_getch(); system("cls");
		usr.clear();
	}
	username = usr;
	system("pause");
}

void FormAccount::registView(){
	string usr, pwd, rpwd, fname, addr;
	int age, sex, i;
	AccountInfo info;
	while (true)
	{
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > Register     |\n");
		printf("\t|----------------------------|\n");
		printf("\t|Press any key to continue, 'b' to back to previous menu\n");
		if (toupper(_getch()) == 'B')
		{
			break;
		}
		system("cls");
		printf("\t------------------------------\n");
		printf("\t|Chat Program > Register     |\n");
		printf("\t|----------------------------|\n");
		printf("\t|Username:\t");
		getline(cin, usr, '\n');
		//if (!checkLength(usr, "USERNAME")){
		//	_getch(); continue;
		//}
		if (!checkSpace(usr))
		{
			_getch(); continue;
		}
		if ((i = accessor.checkExist(usr) != 1))
		{
			(i == 0) ? cerr << "\t FILE INFO ERROR" << endl : cerr << "\t THIS USERNAME IS EXIST OR INVALID USERNAME" << endl;
			_getch(); continue;
		}
		printf("\t|Password:\t");
		getline(cin, pwd, '\n');
		//if (!checkLength(pwd, "PASSWORD")){
		//	_getch(); continue;
		//}
		printf("\t|Re-password:\t");
		getline(cin, rpwd, '\n');
		//if (!checkPwdMatch(pwd,rpwd))
		//{
		//	_getch(); continue;
		//}
		printf("\t|Age:\t");
		cin >> age;
		cin.clear();
		cin.ignore();
		//if (!checkAge(age))
		//{
		//	_getch(); continue;
		//}
		printf("\t|Fullname:\t");
		getline(cin, fname, '\n');
		//if (!checkLength(fname, "FULL NAME")){
		//	_getch(); continue;
		//}
		printf("\t|Sex:\t1. Male\t2. Female\n \t| Choose:\t");
		cin >> sex;
		cin.clear();
		cin.ignore();
		switch (sex)
		{
		case 1:
			break;
		case 2:
			sex = 0;
			break;
		default:
			while (cin.get() != '\n')
			{
				cin.clear();
				cin.ignore();
			}
			cerr << "\t INVALID CHOICE. SET TO MALE" << endl;
			sex = 1;
			//continue;
		}
		printf("\t|Address:\t");
		getline(cin, addr, '\n');
		printf("\t------------------------------\n");
		info.setInfo(usr, pwd, age, fname, sex, addr);
		if (accessor.createUser(info)) break;
	}
	system("pause");
}

void FormAccount::infoView(string const & usr){
	AccountInfo info;
	accessor.getUserInfo(usr, info);
	system("cls");
	printf("\t-----------------------------------\n");
	printf("\t|Chat Program > Account Information\n");
	printf("\t|----------------------------------\n");
	printf("\t|1. Username: %s\n", info.getUsername().c_str());
	printf("\t|2. Fullname: %s\n", info.getFullname().c_str());
	printf("\t|3. Sex     : %s\n", (info.getSex()) ? "Male" : "Female");
	printf("\t|4. Age     : %ld\n", info.getAge());
	printf("\t|5. Address : %s\n", info.getAddr().c_str());
	printf("\t-----------------------------------\n");
	system("pause");
}

int FormAccount::logout(const string & usr){
	return (accessor.userLogout(usr)) ? 1 : 0;
}
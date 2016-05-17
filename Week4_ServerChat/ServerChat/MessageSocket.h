#pragma once

#include <winsock2.h>
#include <windows.h>
#include "ControllerStrategy.h"

struct Connection
{
	SOCKET clientSocket;
	string username = ANONYMOUS;
	LPVOID mPointer;
};

class MessageSocket
{
private:
	WSADATA socketData;
	SOCKET serverSocket;
	struct sockaddr_in serverInfo;
	bool serverStatus = true;
	ControllerStrategy controllerStrategy;

	list<Connection> listConnection;
	
	void initInfo();
	void listenConnection();
	void acceptConnection();

	void sendMessageTo(const string);
	bool isSendMessageRequest(string &);

	bool isLoginRequest(const string, const string);
	void addToList(Connection &, const string);
	void closeConnection(Connection);
	void logOut(string username);

	static DWORD WINAPI connectionThread(LPVOID arg);
	CEdit * ec_serverStatus;
public:
	MessageSocket(CEdit *);
	~MessageSocket();
		
	void printLogToDlg(CString);
	void setServerStatus(const bool);
	void startService();
	void check();
};
#include "stdafx.h"
#include "MessageSocket.h"

MessageSocket::MessageSocket(CEdit * ec_serverStatus)
{
	int result = WSAStartup(MAKEWORD(2, 2), &this->socketData);
	if (result)
	{
		//cout << "Cannot initialize winsock2 error code: " << WSAGetLastError() << endl;
		return;
	}
	//printf("Initialize winsock2 successful...\n");
	this->serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->serverSocket == INVALID_SOCKET)
	{
		//cout << "Cannot create new Socket error code: " << WSAGetLastError() << endl;
		return;
	}
	this->ec_serverStatus = ec_serverStatus;
	//cout << "Create new Socket successful... " << endl;
}


MessageSocket::~MessageSocket()
{
	for (auto con: this->listConnection){
		this->closeConnection(con);
	}
	closesocket(serverSocket);
	WSACleanup();
}

void MessageSocket::initInfo(){
	this->serverInfo.sin_family = AF_INET;
	this->serverInfo.sin_port = htons(DEFAULT_PORT);
	this->serverInfo.sin_addr.s_addr = ADDR_ANY;
}

void MessageSocket::listenConnection(){
	int result = bind(serverSocket, (sockaddr *)&this->serverInfo, sizeof(this->serverInfo));
	if (result)
	{
		//cout << "Binding address error code: " << WSAGetLastError() << endl;
		return;
	}
	//cout << "Binding address successful...\n" << endl;
	
	result = listen(serverSocket, SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		//cout << "Listen failed with error: " << WSAGetLastError() << endl;
		return;
	}
	//cout << "Listening to connections...\n" << endl;
}

void MessageSocket::acceptConnection(){
	while (this->serverStatus)
	{
		SOCKET clientSocket = accept(serverSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
		{
			//cout << "An error occurred when accepting connection " << WSAGetLastError() << endl;
			continue;
		}
		Connection con;
		con.clientSocket = clientSocket;
		con.mPointer = this;
		HANDLE clientThread = CreateThread(NULL, 0, connectionThread, (LPDWORD)&con, 0, NULL);
	}
}


DWORD WINAPI MessageSocket::connectionThread(LPVOID arg){
	char recvBuffer[BUFFER_LENGTH];
	//char sendBuffer[BUFFER_LENGTH];

	Connection * con = (Connection*)arg;
	Connection connect = *con;
	MessageSocket * mPointer = (MessageSocket*)connect.mPointer;
	CString msg;
	while (1)
	{
		//int result = recv(connect.clientSocket, recvBuffer, sizeof(recvBuffer), 0);
		int result = recv(connect.clientSocket, recvBuffer, 1024, 0);
 		if (result == 0 || WSAGetLastError() == 10054) 
		{

			cout << "Connection is closing" << endl;
			mPointer->closeConnection(connect);
			mPointer->logOut(connect.username);
			msg.Format(_T("%s has logged out..."), connect.username);
			mPointer->printLogToDlg(msg);
			//mPointer->check();
			break;
		}
		else
		{
			//cout << recvBuffer << endl;
			string recvBuf(recvBuffer);
			mPointer->controllerStrategy.setJsonStringRequest(recvBuf);
			
			string recvString = recvBuffer;
			string sendString = mPointer->controllerStrategy.getControllerResponse();

			//strcpy_s(sendBuffer, sendString.c_str());

			if (mPointer->isLoginRequest(recvString, sendString))
			{
				mPointer->addToList(connect, recvString);
				msg.Format(_T("%s has logged in..."), connect.username);
				mPointer->printLogToDlg(msg);
			}

			mPointer->check();

			if (mPointer->isSendMessageRequest(recvString))
			{
				mPointer->sendMessageTo(recvString);
				send(connect.clientSocket, sendString.c_str(), sendString.length(), 0);
				continue;
			}

			//send(con->clientSocket, sendBuffer, sizeof(sendBuffer), 0);
			send(connect.clientSocket, sendString.c_str(), sendString.length(), 0);
			cout << recvString << endl;
			cout << sendString << endl << endl;
		}
	}
	return 1;
}

void MessageSocket::sendMessageTo(const string jsonString)
{
	Document jsonDoc;
	jsonDoc.Parse(jsonString.c_str());
	for (Connection con : this->listConnection)
	{
		if (!con.username.compare(jsonDoc["MessageDetail"]["receiver"].GetString()))
		{
			//char sendBuffer[BUFFER_LENGTH];
			//strcpy_s(sendBuffer, jsonString.c_str());
			//int result = send(con->clientSocket, sendBuffer, sizeof(sendBuffer), 0);
			int result = send(con.clientSocket, jsonString.c_str(), jsonString.length(), 0);
			if (result < 0)
			{
				//cout << "Error occurred when sending message to other client " << WSAGetLastError() << endl;
			}
			//cout << jsonString << endl;
			//cout << con.username << endl;
		}
	}
}

bool MessageSocket::isSendMessageRequest(string & jsonString)
{
	Document jsonDoc;
	jsonDoc.Parse(jsonString.c_str());
	if (jsonDoc["type"].GetInt() == JSON_RECV_MESSAGE)
	{
		jsonDoc["type"].SetInt(JSON_SEND_MESSAGE);
		
		StringBuffer sbuffer;
		PrettyWriter<StringBuffer> pWriter(sbuffer);
		jsonDoc.Accept(pWriter);

		jsonString = sbuffer.GetString();
		return true;
	}
	return false;
}

bool MessageSocket::isLoginRequest(const string jsonRequest, const string jsonResponse)
{
	Document jsonDocReq, jsonDocRes;
	jsonDocReq.Parse(jsonRequest.c_str());
	jsonDocRes.Parse(jsonResponse.c_str());
	if (jsonDocReq["type"].GetInt() == JSON_LOGIN)
	{
		if (jsonDocRes["isLogin"].GetBool())
		{
			return true;
		}
	}
	return false;
}

void MessageSocket::addToList(Connection & con, const string jsonString)
{
	Document jsonDoc;
	jsonDoc.Parse(jsonString.c_str());
	con.username = jsonDoc["LoginInfo"]["username"].GetString();
	this->listConnection.push_back(con);
}

void MessageSocket::setServerStatus(const bool status)
{
	this->serverStatus = status;
}

void MessageSocket::startService()
{
	initInfo();
	listenConnection();
	acceptConnection();
}

void MessageSocket::check()
{
	for (auto con : listConnection)
	{
		//cout << con.username << endl;
	}
}

void MessageSocket::closeConnection(Connection connection)
{
	closesocket(connection.clientSocket);
	for (list<Connection>::iterator it = listConnection.begin(); it != listConnection.end();)
	{
		if (!it->username.compare(connection.username))
		{
			it = listConnection.erase(it);
			//cout << "socket has been closed" << endl;
		}
		else 
		{
			it++;
		}
	}
}

void MessageSocket::logOut(string username)
{
	Document jsonDoc;
	jsonDoc.Parse(FORCE_LOGOUT);
	Value & user = jsonDoc["Logout"]["username"];
	user.SetString(username.c_str(), jsonDoc.GetAllocator());
	
	StringBuffer sbuffer;
	PrettyWriter<StringBuffer> pWriter(sbuffer);
	jsonDoc.Accept(pWriter);
	//cout << sbuffer.GetString();
	controllerStrategy.setJsonStringRequest(sbuffer.GetString());
	controllerStrategy.getControllerResponse();
}


void MessageSocket::printLogToDlg(CString msg)
{
	this->ec_serverStatus->SetWindowText(msg);
}
// RegisterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientChat.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"

// RegisterDlg dialog

IMPLEMENT_DYNAMIC(RegisterDlg, CDialogEx)

RegisterDlg::RegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(RegisterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

RegisterDlg::~RegisterDlg()
{
}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &RegisterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// RegisterDlg message handlers
BOOL RegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	HICON appIcon = (HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDR_MAINFRAME),
		IMAGE_ICON, 128, 128,
		LR_DEFAULTCOLOR);
	((CStatic*)GetDlgItem(PC_APP_ICON))->SetIcon(appIcon);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void RegisterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR RegisterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void RegisterDlg::OnClose()
{
	GetOwner()->ShowWindow(TRUE);
	CDialogEx::OnClose();
}


void RegisterDlg::OnBnClickedOk()
{
	//get information from interface
	CIPAddressCtrl *ia_host = (CIPAddressCtrl *)GetDlgItem(IA_HOST);
	CString address;
	ia_host->GetWindowText(address);
	CStringA m_address(address);
	const size_t addr_size = (m_address.GetLength() + 1);
	char *addr_str = new char[addr_size];
	strcpy_s(addr_str, addr_size, m_address);

	CEdit * c_edit = (CEdit*)GetDlgItem(EC_USERNAME);
	CString username;
	c_edit->GetWindowText(username);

	c_edit = (CEdit*)GetDlgItem(EC_PASSWORD);
	CString password;

	c_edit->GetWindowText(password);

	c_edit = (CEdit*)GetDlgItem(EC_RE_PASSWORD);
	CString repassword;
	c_edit->GetWindowText(repassword);

	//if (username.IsEmpty() || password.IsEmpty() || repassword.IsEmpty() || m_address.IsEmpty())
	//{
	//	AfxMessageBox(_T("You have to fill all field"), MB_OK | MB_ICONSTOP);
	//	return;
	//}

	//init a socket to connect to server
	WSADATA socketData;
	SOCKET clientSocket;
	int result = WSAStartup(MAKEWORD(2, 2), &socketData);
	clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(12345);
	serverInfo.sin_addr.s_addr = inet_addr(addr_str);
	//////////////////////////////////////////////////////////////////////////
	serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
	//////////////////////////////////////////////////////////////////////////
	result = connect(clientSocket, (sockaddr *)&serverInfo, sizeof(serverInfo));
	if (result == SOCKET_ERROR)
	{
		closesocket(clientSocket);
		clientSocket = INVALID_SOCKET;
		WSACleanup();
	}
	else
	{
		CString registerReq;
		//////////////////////////////////////////////////////////////////////////
		username = "hung";
		password = "hung";
		//////////////////////////////////////////////////////////////////////////
		//registerReq.Format(_T("{\"type\":3, \"Register\":{\"username\":\"%s\", \"password\":\"%s\", \"mail\":\"\"}"), username, password);
		//CT2CA convString(registerReq);
		//string regReq(convString);
		Document jsonDoc;
		jsonDoc.SetObject();
		StringConverter str;
		Value num(3);
		Value user(kStringType);
		string a = str.convert(username);
		user.SetString(a.c_str(), a.length(), jsonDoc.GetAllocator());
		Value password("hung");
		Value mail("hung");
		Value reg;
		reg.SetObject();
		reg.AddMember("username", user, jsonDoc.GetAllocator());
		reg.AddMember("password", password, jsonDoc.GetAllocator());
		reg.AddMember("mail", mail, jsonDoc.GetAllocator());
		jsonDoc.AddMember("type", num, jsonDoc.GetAllocator());
		jsonDoc.AddMember("Register", reg, jsonDoc.GetAllocator());

		StringBuffer strbuf;
		Writer<StringBuffer> writer(strbuf);
		jsonDoc.Accept(writer);

		
		string regReq;

		char recvBuffer[1024];
		//send(clientSocket, regReq.c_str(), regReq.length(), 0);
		send(clientSocket, strbuf.GetString(), 1024, 0);
		//recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
		recv(clientSocket, recvBuffer, 1024, 0);
		return;
	}
	CDialogEx::OnOK();
}

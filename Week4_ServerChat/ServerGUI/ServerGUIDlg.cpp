
// ServerGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServerGUI.h"
#include "ServerGUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerGUIDlg dialog



CServerGUIDlg::CServerGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerGUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerGUIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_START_SERVER, &CServerGUIDlg::OnBnClickedStartServer)
END_MESSAGE_MAP()


// CServerGUIDlg message handlers

BOOL CServerGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CButton *pButton = (CButton *)GetDlgItem(BTN_START_SERVER);
	if (pButton && pButton->GetSafeHwnd())
	{
		pButton->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
			MAKEINTRESOURCE(ID_START),
			IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR));
	}
	serverStatus = false;
	ms = new MessageSocket((CEdit*) GetDlgItem(EC_SERVER_STATUS));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerGUIDlg::OnPaint()
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
HCURSOR CServerGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerGUIDlg::OnBnClickedStartServer()
{
	CButton *btn_startButton = (CButton *)GetDlgItem(BTN_START_SERVER);
	if (serverStatus){
		CEdit *ce_serverStatus = (CEdit *)GetDlgItem(EC_SERVER_STATUS);
		int nLength = ce_serverStatus->GetWindowTextLength();
		ce_serverStatus->SetSel(nLength, nLength);
		TerminateThread(clientThread, 0);
		CloseHandle(clientThread);
		ce_serverStatus->ReplaceSel(_T("\r\nServer is stopped..."));
		if (btn_startButton && btn_startButton->GetSafeHwnd())
		{
			btn_startButton->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
				MAKEINTRESOURCE(ID_START),
				IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR));
		}
		serverStatus = false;
	}
	else
	{
		CEdit *ce_serverStatus = (CEdit *)GetDlgItem(EC_SERVER_STATUS);
		CString startupStatus;
		startupStatus.Format(_T("[%s] Server is Starting up...\r\n\r\n"), this->timeBuilder());
		ce_serverStatus->SetWindowText(startupStatus);

		clientThread = CreateThread(NULL, 0, connectionThread, (LPDWORD) this, 0, NULL);

		startupStatus.Format(_T("Server is running...\r\n\r\n"));
		int nLength = ce_serverStatus->GetWindowTextLength();
		ce_serverStatus->SetSel(nLength, nLength);
		ce_serverStatus->ReplaceSel(startupStatus);
		if (btn_startButton && btn_startButton->GetSafeHwnd())
		{
			btn_startButton->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
				MAKEINTRESOURCE(ID_STOP),
				IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR));
		}
		serverStatus = true;
	}
	
}

CString CServerGUIDlg::timeBuilder()
{
	time_t now = time(0);
	char datetime[100];
	ctime_s(datetime, 100, &now);
	CString dt(datetime);
	return dt;
}

DWORD WINAPI CServerGUIDlg::connectionThread(LPVOID arg)
{
	CServerGUIDlg * dlgPointer = (CServerGUIDlg*)arg;
	dlgPointer->ms->startService();
	return 1;
}



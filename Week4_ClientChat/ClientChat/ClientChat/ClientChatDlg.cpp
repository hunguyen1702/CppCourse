
// ClientChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientChat.h"
#include "ClientChatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientChatDlg dialog



CClientChatDlg::CClientChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientChatDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientChatDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_REGISTER, &CClientChatDlg::OnBnClickedRegister)
	ON_BN_CLICKED(BTN_LOGIN, &CClientChatDlg::OnBnClickedLogin)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CClientChatDlg message handlers

BOOL CClientChatDlg::OnInitDialog()
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
	//sAppIcon->SetIcon(appIcon);
	//GetOwner()->ShowWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientChatDlg::OnPaint()
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
HCURSOR CClientChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CClientChatDlg::OnBnClickedRegister()
{
	ShowWindow(FALSE);
	RegisterDlg regist(this);
	regist.DoModal();
}


void CClientChatDlg::OnBnClickedLogin()
{
	GetOwner()->ShowWindow(TRUE);
	
	EndDialog(0);
}


void CClientChatDlg::OnClose()
{
	ASSERT(AfxGetMainWnd() != NULL);
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
	CDialogEx::OnClose();
}

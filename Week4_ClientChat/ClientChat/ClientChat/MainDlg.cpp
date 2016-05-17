// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientChat.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// MainDlg dialog

IMPLEMENT_DYNAMIC(MainDlg, CDialogEx)

MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(MainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

MainDlg::~MainDlg()
{
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// MainDlg message handlers
BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CButton *pButton = (CButton *)GetDlgItem(BTN_SEND);
	if (pButton && pButton->GetSafeHwnd())
	{
		pButton->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
			MAKEINTRESOURCE(IDI_SEND),
			IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR));
	}

	pButton = (CButton *)GetDlgItem(BTN_LOGOUT);
	if (pButton && pButton->GetSafeHwnd())
	{
		pButton->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
			MAKEINTRESOURCE(IDI_LOGOUT),
			IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR));
	}

	pButton = (CButton *)GetDlgItem(BTN_ADD);
	if (pButton && pButton->GetSafeHwnd())
	{
		pButton->SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance,
			MAKEINTRESOURCE(IDI_ADD),
			IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR));
	}

	ShowWindow(FALSE);
	CClientChatDlg clientChatDlg(this);
	clientChatDlg.DoModal();

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void MainDlg::OnPaint()
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
HCURSOR MainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void MainDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
}

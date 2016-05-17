
// ServerGUIDlg.h : header file
//

#pragma once
#include <ctime>
#include "../ServerChat/MessageSocket.h"

// CServerGUIDlg dialog
class CServerGUIDlg : public CDialogEx
{
// Construction
public:
	CServerGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SERVERGUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartServer();
private:
	bool serverStatus;
	CString timeBuilder();
	MessageSocket * ms;
	static DWORD WINAPI connectionThread(LPVOID arg);
	HANDLE clientThread;
};

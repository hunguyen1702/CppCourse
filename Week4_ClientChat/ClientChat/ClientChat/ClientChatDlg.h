
// ClientChatDlg.h : header file
//

#pragma once
#include "RegisterDlg.h"

// CClientChatDlg dialog
class CClientChatDlg : public CDialogEx
{
// Construction
public:
	CClientChatDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENTCHAT_DIALOG };

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

	afx_msg void OnBnClickedRegister();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnClose();
};

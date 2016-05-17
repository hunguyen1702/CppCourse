#pragma once
#include"rapidjson\document.h"
#include"rapidjson\stringbuffer.h"
#include"rapidjson\prettywriter.h"
#include <string>
#include "StringConverter.h"
// RegisterDlg dialog

using namespace std;
using namespace rapidjson;

class RegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterDlg)

public:
	RegisterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~RegisterDlg();

// Dialog Data
	enum { IDD = IDD_REGISTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//DECLARE_MESSAGE_MAP()

	// Implementation
	
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
};

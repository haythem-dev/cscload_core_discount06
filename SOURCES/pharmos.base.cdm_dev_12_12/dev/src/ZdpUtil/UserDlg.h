#if !defined(AFX_USERDLG_H__6DE7F422_6ECB_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_USERDLG_H__6DE7F422_6ECB_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UserDlg.h : header file
//

#include <phxlib/hSrvCon.h>

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog

class CUserDlg : public CDialog
{
// Construction
public:
	CUserDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserDlg)
	enum { IDD = IDD_USER };
	CEdit	m_cPasswd;
	CEdit	m_cUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	~CUserDlg();  

	void InitUserName( CString cName );

	CString SetUserName();
	CString SetPassword();
	CString SetEk();
	CString SetAllgRechte();
	bool    SetSuperSuperUser();

	void Get_Db ( ChSrvCon *Db );

protected:
	// Generated message map functions
	//{{AFX_MSG(CUserDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool GetSuperSuperUser( CString UserName, CString Password );
	void GetPasswd();

// Data
private:
	int m_anzahl;
	CString m_OldUserName;
	CString m_TruePassword;
//	struct T_PASSWD m_passwd;

	CString  m_USERNAME;
	CString  m_PASSWORD;
	CString  m_EK;
	CString  m_ALLG_RECHTE;
	bool     m_bSuperSuperUser;

	ChSrvCon *m_Db;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__6DE7F422_6ECB_11D2_92F8_0060973B18D8__INCLUDED_)

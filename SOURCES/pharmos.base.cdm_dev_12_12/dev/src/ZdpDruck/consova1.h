#if !defined(AFX_CONSOVA1_H__6DE7F421_6ECB_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_CONSOVA1_H__6DE7F421_6ECB_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConSoVa1.h : header file
//

#include <hConnect.h>

/////////////////////////////////////////////////////////////////////////////
// CConSoVa1 

class CConSoVa1 : public CCmdTarget
{

public:
	CConSoVa1();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations

protected:
	virtual void DoThingsBeforeCloseDatabase();

public:
	bool TryDefaultConnect( CString ServerNickName );
	int  TryDialogConnect(  );

	CString GetServerHandler( );
	CString GetServerName();
	CString GetDbaseName();
	CString GetUserName( );
	char*   GetRefToAnwender( );
//	CString GetFilialName( );
	bool	IsConnected();


// Implementation
public:
	~CConSoVa1();

private:
	bool TryConnect( CString ServerName, CString DbaseName );
	bool FindServerName( CString xxxPipeSrv, CString& ServerName,
					     CString& errmld );
	bool GetPasswdInfo( );


private:
	ChConnect m_Db;
	bool m_bConnected;
	CString m_DbaseName;
	CString m_DefaultDbaseName;
	CString m_ServerName;
	CString m_ServerHandler;
	CString m_UserName;
	CString m_Password;
	CString m_Ek;
	CString m_AllgRechte;
//	CString m_FilialName;
//	short   m_FilialNr;
	char    m_Anwender[8+1];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSOVA1_H__6DE7F421_6ECB_11D2_92F8_0060973B18D8__INCLUDED_)

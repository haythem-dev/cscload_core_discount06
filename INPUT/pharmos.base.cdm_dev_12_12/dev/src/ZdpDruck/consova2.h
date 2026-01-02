#if !defined(AFX_CONSOVA2_H__6DE7F421_6ECB_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_CONSOVA2_H__6DE7F421_6ECB_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConSoVa2.h : header file
//

#include <hSrvCon.h>

#include "FeldBreite.h"

/////////////////////////////////////////////////////////////////////////////
// CConSoVa2 

class CConSoVa2 : public CCmdTarget
{

public:
	CConSoVa2();           // protected constructor used by dynamic creation

// Attributes
public:
	void SetDefaultDbaseName( CString DefaultDbaseName );
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
	bool    IsSyncronized();
	bool	IsConnected();
	bool	IsStandardEngine();
	bool    IsSuperSuperUser();
	bool    DarfRechtePflegen();
	bool    DarfSubSuperAnlegen( );
	bool    DarfMenuPflegen( short Region, int MenuNr );
	bool	DarfMenuAendern( short Region, int MenuNr );
	bool    ReadUserRights( CString& cErrmld );
	CStringArray* GetLoginRechte();
	CUIntArray*   GetLoginRegion();


// Implementation
public:
	~CConSoVa2();

private:
	bool TryConnect( CString ServerName, CString DbaseName );
	bool FindServerName( CString xxxPipeSrv, CString& ServerName,
					     CString& errmld );
	bool GetPasswdInfo( );
	void InitSuperUserRights();

private:
	ChSrvCon m_Db;
	bool m_bConnected;
	bool m_bSynchronized;
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
	char    m_Anwender[L_ANWENDER+1];
	bool	m_bStandardEngine;
	bool    m_bSuperSuperUser;
	bool	m_bSubSuper;
    CStringArray	m_RegioRechte;
    CUIntArray		m_Region;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSOVA2_H__6DE7F421_6ECB_11D2_92F8_0060973B18D8__INCLUDED_)

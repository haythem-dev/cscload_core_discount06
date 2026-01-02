// ConSoVa1.pp : implementation file
//

#include "stdafx.h"
#include "EkAdm.h"

#include "ConSoVa1.h"
#include "ServerDlg.h"
#include "UserDlg.h"


#define MIT_ALTER_PFLEGE

#ifdef MIT_ALTER_PFLEGE
#include <wpx_dbas.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConSoVa1

CConSoVa1::CConSoVa1()
{
	m_bConnected = false;
	m_DefaultDbaseName = "phosix";
}

CConSoVa1::~CConSoVa1()
{
	// Close Datenbank
	CString errmld;
	m_Db.CloseConnectToDb( errmld );
}


///////////////////////////////////////////////////////////////////7
// Verbindung zum Server

bool CConSoVa1::FindServerName( CString xxxPipeSrv, CString& ServerName,
				  			    CString& errmld )
{

	char *default_str;
	char lpComputerName[ 41 ];
	char lpServer[41];

	DWORD dwLen;

	errmld = _T("");
/*
	dwLen = sizeof( lpComputerName ) - 1;
    if (! GetComputerName( lpComputerName, &dwLen ) )
	{
		ServerName = _T("");
		errmld = _T( "cannot get computername" );
		return false;
	}
*/
	default_str = "sonicht";

	strcpy( lpComputerName, (LPCTSTR) xxxPipeSrv );

	dwLen = GetPrivateProfileString("server", // points to section name 
									lpComputerName, // points to key name 
									default_str,    // points to default string 
									lpServer, // points to destination buffer 
									40, // size of destination buffer 
									"wws.ini" // points to initialization filename 
									); 
	ServerName = _T("");
	if ( strcmp( lpServer, default_str ) == 0 )
	{
		errmld  = xxxPipeSrv;
		errmld += _T("\nnot in section\n[server]\nof\nwws.ini" );
		return false;
	}

	//	Severname in der Form //server.srv
	ServerName = lpServer;
	// \\ wegmachen
	ServerName = ServerName.Right( ServerName.GetLength() - 2 );
	// .srv wegmachen
	ServerName = ServerName.Left( ServerName.GetLength() - 4 );

	return true;
}


bool CConSoVa1::GetPasswdInfo( )
{
//  Connect
//	if ( !OpenConnectToDb( ) ) return false;

// UhrenSynchronisation
// SyncPcDateTime  ( );

// Passwort
	CUserDlg userDlg;
    if ( userDlg.DoModal() != IDOK )
	{
		m_UserName = "";
		return false;
	}

	m_UserName = userDlg.SetUserName();
	m_UserName.TrimRight();
	m_Password = userDlg.SetPassword();
	m_Ek = userDlg.SetEk();
	m_AllgRechte = userDlg.SetAllgRechte();

	char *user;
    user = _tcsdup( m_UserName ); 
	strcpy( m_Anwender, user );
	free (user);

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// load user spezific customized Toolbar
	((CMainFrame*)AfxGetMainWnd())->LoadToolBarState( m_Anwender );
*/

	return true;
}


// virtual
void CConSoVa1::DoThingsBeforeCloseDatabase()
{
}

bool CConSoVa1::TryConnect( CString ServerName, CString DbaseName )
{
	BOOL bOk;
	CString errmld;
	CString DbEnv;

	DbEnv = "";		// keine Environmentvariable definiert

	m_bConnected = false;
	m_ServerName = ServerName;
	m_DbaseName  = DbaseName;

//	BeginWaitAction();
	BeginWaitCursor();
	// Connect
	bOk = m_Db.OpenConnectToDb( m_ServerName, m_DbaseName, DbEnv, errmld);
	if ( !bOk )
	{
//		EndWaitAction();
		EndWaitCursor();
		AfxMessageBox( errmld );
		return false;
	}


	// Filiale
//	bOk = m_Db.ReadFiliale( &m_FilialNr, m_FilialName, errmld ) == 0;

//	EndWaitAction();
	EndWaitCursor();

	if ( !bOk )
	{
		AfxMessageBox( errmld );
		if ( !m_Db.CloseConnectToDb( errmld ) )
			AfxMessageBox( errmld );
		return false;
	}

	// Passwd
	if ( !GetPasswdInfo() )
	{
		if ( !m_Db.CloseConnectToDb( errmld ) )
			AfxMessageBox( errmld );
		return false;
	}


	// PflegeServer oeffnen
#ifdef MIT_ALTER_PFLEGE
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
	char errstr[ 80 ];
	if ( OpenPflege( m_Anwender ,errstr ) != 0 )
	{
		AfxMessageBox( errstr );
		if ( !m_Db.CloseConnectToDb( errmld ) )
			AfxMessageBox( errmld );
		return false;
	}
#endif

	// OpenPflege in den Views
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ChPflegeView* TempView;
	int i;
	for ( i = 0; i < MAX_VIEWS; i++ )
	{
		if ( m_AllViews[i].iViewNr != VIEW_NO   &&
			 m_AllViews[i].iViewNr != VIEW_LEER    )
		{
			TempView = ( ChPflegeView* )m_AllViews[i].cView;
			TempView->InitPflegeDocument( m_Anwender );
		}
	}
*/ 

/*
	// Datum+Zeit synchronisieren unter Windows 95
    OSVERSIONINFO OSVer;
    OSVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&OSVer); 
    if (OSVer.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ) // Win32 on Windows 95. 
		SyncPcDateTime( );
*/
	m_bConnected = true;

	return true;
}


bool CConSoVa1::TryDefaultConnect( CString ServerNickName )
{
	CString errmld;
	CString ServerName;
	CString DbaseName;
	
	DbaseName = m_DefaultDbaseName;
	// Default Server
	if ( !FindServerName( ServerNickName, ServerName, errmld ) )
	{
		m_bConnected = false;
		AfxMessageBox( errmld );
		return false;
	}
	return TryConnect( ServerName, DbaseName );
}

int CConSoVa1::TryDialogConnect( ) 
{
	CString ServerName;
	CString DbaseName;
	CServerDlg Dlg;
    if ( Dlg.DoModal() != IDOK ) return -1;

  	ServerName = Dlg.GetServerName();


	if ( ServerName.IsEmpty() ) return -1;

	if ( m_bConnected )
	{
		DoThingsBeforeCloseDatabase();
/*
		// ReleasePflege in den Views
		ChPflegeView* TempView;
		int i;
		for ( i = 0; i < MAX_VIEWS; i++ )
		{
			if ( m_AllViews[i].iViewNr != VIEW_NO   &&
				 m_AllViews[i].iViewNr != VIEW_LEER    )
			{
				TempView = ( ChPflegeView* )m_AllViews[i].cView;
				TempView->ReleasePflegeDocument( );
			}
		}
*/


		CString errmld;

#ifdef MIT_ALTER_PFLEGE
		// Close Pflege, Datenbank
		char errstr[ 80 ];
		ClosePflege( errstr );
#endif
		// Close Datenbank
		m_Db.CloseConnectToDb( errmld );
	}

//	m_ServerName = ServerName;

	DbaseName = Dlg.GetDatabaseName();
	if ( DbaseName.IsEmpty() )
		DbaseName = m_DefaultDbaseName;

	if ( TryConnect( ServerName, DbaseName) ) 
		return 0;
	else
		return 1;

/*
	SetView( VIEW_LEER, TRUE );

	m_bPflege = FALSE;
*/	
}

CString CConSoVa1::GetServerHandler( )
{
	return m_ServerHandler;
}

CString CConSoVa1::GetServerName( )
{
	return m_ServerName;
}

CString CConSoVa1::GetDbaseName( )
{
	return m_DbaseName;
}

CString CConSoVa1::GetUserName( )
{
	return m_UserName;
}

char* CConSoVa1::GetRefToAnwender( )
{
	return m_Anwender;
}

/*
CString CConSoVa1::GetFilialName( )
{
	return m_FilialName;
}
*/

bool CConSoVa1::IsConnected( )
{
	return m_bConnected;
}
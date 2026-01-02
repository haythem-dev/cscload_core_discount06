// ConSoVa2.pp : implementation file
//

#include "stdafx.h"
#include "ZdpDruck.h"

#include "ConSoVa2.h"
#include "ServerDlg.h"
#include "UserDlg.h"
#include "MenuNumbers.h"
#include <UnixSys.h>

//#define MIT_ALTER_PFLEGE

#ifdef MIT_ALTER_PFLEGE
#include <wpp_dbas.h>	// wpx_dbas.h 
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConSoVa2

CConSoVa2::CConSoVa2()
{
	m_bConnected = false;
	m_bSynchronized = false;
//	m_DefaultDbaseName = "phosix";
	m_DefaultDbaseName = "regioek";
}

CConSoVa2::~CConSoVa2()
{
	// Close Datenbank
	CString errmld;
	m_Db.CloseConnectToDb( errmld );
}

void CConSoVa2::SetDefaultDbaseName( CString DefaultDbaseName )
{
	m_DefaultDbaseName = DefaultDbaseName;
}

///////////////////////////////////////////////////////////////////7
// Verbindung zum Server

bool CConSoVa2::FindServerName( CString xxxPipeSrv, CString& ServerName,
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


bool CConSoVa2::GetPasswdInfo( )
{
//  Connect
//	if ( !OpenConnectToDb( ) ) return false;

// UhrenSynchronisation
// SyncPcDateTime  ( );

// Passwort
	long s;
	long s1;
	int  ret;
	CString cErrmld;

	m_bSubSuper = false;

	s = m_Db.ChangeToPhosix( cErrmld );
	if ( s != 0 )
	{
		AfxMessageBox( cErrmld );
		return false;
	}

	CUserDlg userDlg;
	userDlg.Get_Db ( &m_Db );
    ret = userDlg.DoModal();

	if ( ret == IDOK )
	{
		s1 = m_Db.ReadUserrights( userDlg.SetUserName(), 
		 		 				  THIS_PRORGAM_NUMBER,
								  m_bSubSuper,
								  m_RegioRechte,
								  m_Region,	
								  cErrmld );
		if ( s1 != 0 )
			AfxMessageBox( cErrmld );
	}

	s = m_Db.ChangeToOriginalDatabase( cErrmld );
	if ( s != 0 )
		AfxMessageBox( cErrmld );

	if ( ret != IDOK || s != 0 || s1 != 0 )
	{
		m_UserName = "";
		return false;
	}

	m_UserName = userDlg.SetUserName();
	m_UserName.TrimRight();
	m_Password = userDlg.SetPassword();
	m_Ek = userDlg.SetEk();
	m_AllgRechte = userDlg.SetAllgRechte();
	m_bSuperSuperUser = userDlg.SetSuperSuperUser();

	if ( m_bSuperSuperUser )
		InitSuperUserRights();

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

void CConSoVa2::InitSuperUserRights()
{
	int i;
	CString Rechte;
	Rechte.Empty();
	for ( i = 0; i < MNR_MAX_MENUS; i++ )
		Rechte += "2";
	m_RegioRechte.RemoveAll( );
	m_Region.RemoveAll( );

	for ( i = 1; i <= MAX_REGION; i++ )
	{
//		m_Region.Add( i );
		m_Region.Add( REGION_ZDP );     // !!!!!!ZZZZZZZ  REGION_ZDP  ZZZZZZZZZ
		m_RegioRechte.Add( Rechte );
	}		
}

bool CConSoVa2::ReadUserRights( CString& cErrmld )
{
	if ( IsSuperSuperUser() ) 
		return true;

	long s;
	long s1;

	s1 = 0;
	s = m_Db.ChangeToPhosix( cErrmld );
	if ( s == 0 )
	{
		s1 = m_Db.ReadUserrights( m_UserName, 
	 			 				  THIS_PRORGAM_NUMBER, 
								  m_bSubSuper,
								  m_RegioRechte,
								  m_Region,	
								  cErrmld );
		s = m_Db.ChangeToOriginalDatabase( cErrmld );
	}

	return s == 0 && s1 == 0;
}

////////////////////////////////////////////////////
// virtual

void CConSoVa2::DoThingsBeforeCloseDatabase()
{
}

bool CConSoVa2::TryConnect( CString ServerName, CString DbaseName )
{
	BOOL bOk;
	CString errmld;
	CString DbEnv;

	DbEnv = "";		// keine Environmentvariable definiert

	m_bConnected = false;
	m_bSynchronized = false;
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

	// Datum+Zeit synchronisieren unter Windows 95
/*
    OSVERSIONINFO OSVer;
    OSVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&OSVer); 
    if (OSVer.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ) // Win32 on Windows 95.
	{
		if ( SyncPcDateTime( ) == 0 )
				m_bSynchronized = true;
	}
*/
	PhoTodayFromServer( 1 );	 // liest auf jeden die Zeit Fall vom server

	m_bStandardEngine = m_Db.IsStandardEngine();

	m_bConnected = true;

	return true;
}


bool CConSoVa2::TryDefaultConnect( CString ServerNickName )
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

int CConSoVa2::TryDialogConnect( ) 
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
	{
		SetDefaultDbaseName( DbaseName );   // !!!!!!!!!!!!!!!!!!!!
		return 0;
	}
	else
		return 1;

/*
	SetView( VIEW_LEER, TRUE );

	m_bPflege = FALSE;
*/	
}


bool CConSoVa2::IsSyncronized()
{
	return m_bSynchronized;
}

CString CConSoVa2::GetServerHandler( )
{
	return m_ServerHandler;
}

CString CConSoVa2::GetServerName( )
{
	return m_ServerName;
}

CString CConSoVa2::GetDbaseName( )
{
	return m_DbaseName;
}

CString CConSoVa2::GetUserName( )
{
	return m_UserName;
}

char* CConSoVa2::GetRefToAnwender( )
{
	return m_Anwender;
}

/*
CString CConSoVa2::GetFilialName( )
{
	return m_FilialName;
}
*/

bool CConSoVa2::IsConnected( )
{
	return m_bConnected;
}

bool CConSoVa2::IsStandardEngine()
{
	return m_bStandardEngine;
}

bool CConSoVa2::IsSuperSuperUser()
{
	return m_bSuperSuperUser;
}

/*
bool CConSoVa2::DarfRechtePflegen()
{
	return	m_AllgRechte.GetAt(AR_ANL_USER)  == '1' ||
			m_AllgRechte.GetAt(AR_ANL_SUPER) == '1'    ;
}
*/

bool CConSoVa2::DarfRechtePflegen()
{
	return	m_AllgRechte.GetAt(AR_ANL_SUPER) == '1' ||  m_bSubSuper;
}

bool CConSoVa2::DarfSubSuperAnlegen( )
{
	return	m_AllgRechte.GetAt(AR_ANL_SUPER) == '1';
}

bool CConSoVa2::DarfMenuPflegen( short Region, int MenuNr ) 
{
	int i;
	i = 0;
	while ( i < m_Region.GetSize() )
	{
		if ( (short) m_Region.GetAt( i ) == Region )
		{
			CString cRecht;
			cRecht = m_RegioRechte.GetAt( i );
			if ( MenuNr < cRecht.GetLength() )
				return cRecht.GetAt( MenuNr ) == '1' ||
				       cRecht.GetAt( MenuNr ) == '2'    ;		
			else
				return false;
		}
		i++;
	}
	return false;
}

bool CConSoVa2::DarfMenuAendern( short Region, int MenuNr )
{
	int i;
	i = 0;
	while ( i < m_Region.GetSize() )
	{
		if ( (short) m_Region.GetAt( i ) == Region )
		{
			CString cRecht;
			cRecht = m_RegioRechte.GetAt( i );
			if ( MenuNr < cRecht.GetLength() )
				return cRecht.GetAt( MenuNr ) == '2';
			else
				return false;
		}
		i++;
	}
	return false;
}



CStringArray* CConSoVa2::GetLoginRechte()
{
	return &m_RegioRechte;
}

CUIntArray* CConSoVa2::GetLoginRegion()
{
	return &m_Region;	
}
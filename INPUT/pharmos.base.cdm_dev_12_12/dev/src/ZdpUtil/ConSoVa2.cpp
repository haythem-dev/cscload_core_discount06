// ConSoVa2.pp : implementation file
//

#include "stdafx.h"
#include "ZdpUtil.h"
#include "MainFrm.h"	// Anmeldeprozedur

#include "ConSoVa2.h"
#include "ServerDlg.h"
#include "UserDlg.h"
#include <eklibs/wunxlocs/UnixSys.h>
#include <libscsvoodoo/libscsvoodoo.h>

#define MIT_ALTER_PFLEGE

#ifdef MIT_ALTER_PFLEGE
#include <eklibs/wdbups/wpp_dbas.h>
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
	m_DefaultDbaseName = "";
	m_nThisProgramNumber = 0;
	m_nMaxMenus = 0;
	m_ServerName = "";
	m_ServerProgram = "";
	m_DbaseName = "";
	m_UadmRegionNo = 0;
	m_UserName = "";
	m_Password = "";
}

CConSoVa2::~CConSoVa2()
{
	// Close
	CloseConnection();
}

// old process for passwd and userrights table
void CConSoVa2::InitValues( int ProgramNumber, int MaxMenus, char *Database )
{
	m_nThisProgramNumber = ProgramNumber;
	m_nMaxMenus = MaxMenus;
	m_DefaultDbaseName = Database;
}

// new process for UADM
void CConSoVa2::Initialize(int maxMenus, CString userName)
{
	m_nMaxMenus = maxMenus;
	m_UserName = userName;
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
	m_bCustomToolbar = false;

	s = m_Db.ChangeToPhosix( cErrmld );
	if ( s != 0 )
	{
		AfxMessageBox( cErrmld );
		return false;
	}

	((CMainFrame*)AfxGetMainWnd())->SetDefaultView( );    // Anmeldeprozedur

	CUserDlg userDlg;
	CString cUser;
	userDlg.Get_Db ( &m_Db );

	m_RegistryProfile.ReadLastUserName(cUser);
	userDlg.InitUserName( cUser );

    ret = (int)userDlg.DoModal();

	s1 = 0;
	if ( ret == IDOK )
	{
		m_bSuperSuperUser = userDlg.SetSuperSuperUser();
		if ( !m_bSuperSuperUser )
		{
			s1 = m_Db.ReadUserrights( userDlg.SetUserName(), 
		 			 				  m_nThisProgramNumber,
									  m_bSubSuper,
									  m_bCustomToolbar,
									  m_RegioRechte,
									  m_Region,	
									  cErrmld );
			if ( s1 != 0 )
				AfxMessageBox( cErrmld );
		}
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

	if ( m_bSuperSuperUser )
	{
		s1 = InitSuperUserRights( cErrmld );
		if ( s1 != 0 )
		{
			m_UserName = "";
			AfxMessageBox( cErrmld );
			return false;
		}
	}

	m_RegistryProfile.WriteLastUserName(m_UserName);
	
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

long CConSoVa2::InitSuperUserRights( CString& cErrmld )
{
	int i;
	CString Rechte;

	Rechte.Empty();
	for ( i = 0; i < m_nMaxMenus; i++ )
		Rechte += "2";

	m_RegioRechte.RemoveAll( );
	m_Region.RemoveAll( );

	if ( m_Db.ReadRegiones( m_Region, cErrmld ) != 0 )
		return -1;

	for ( i = 0; i < m_Region.GetSize(); i++ )
		m_RegioRechte.Add( Rechte );	
	return 0;
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
	 			 				  m_nThisProgramNumber, 
								  m_bSubSuper,
								  m_bCustomToolbar,
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

CString CConSoVa2::GetServerProgram()
{
	return m_ServerProgram;
}

const short CConSoVa2::GetUADMRegionNo()
{
	return m_UadmRegionNo;
}

bool CConSoVa2::OpenConnection(CString strServerName, CString strService, CString strDatabase, int intPort, int intRegionBranch)
{
	if ((strServerName.IsEmpty() == TRUE) || (strDatabase.IsEmpty() == TRUE))
	{
		return false;
	}
	if (strServerName == m_ServerName)
	{
		// same server is already connected
		return true;
	}

	if (m_ServerName.IsEmpty() == FALSE)
	{
		// close previous connection
		CloseConnection();
		m_ServerName = "";
	}
	strServerName.MakeLower();

	if (strService.IsEmpty() == TRUE)
	{
		CString ServerProgram;
		ServerProgram.Format("zdputiluiserv_%s%s.bin", GetCountry(ISO3166, strDatabase), GetSubModule(Suffix, strDatabase));
		ServerProgram.MakeLower();
		m_ServerProgram = ServerProgram;
	}
	else
	{
		strService.MakeLower();
		m_ServerProgram = strService;
	}
	long lStatus = 0;
	int  handle = 0;
	if (intPort == 0)
	{
		lStatus = ::ViaEshuOpen(&handle, strServerName, m_ServerProgram);
	}
	else
	{
		lStatus = ::ViaEshuOpenEx(&handle, strServerName, m_ServerProgram, intPort);
	}
	if (lStatus == 0)
	{
		m_ServerName = strServerName;
		CString strPort;
		strPort.Format(" %ld", intPort);
		CString strErrMld = "";
		if (m_Db.OpenConnectToDbViaEshu(m_ServerName + strPort, m_ServerProgram, strDatabase, "", strErrMld) == FALSE)
		{
			return false;
		}
		m_DbaseName = strDatabase;
		m_UadmRegionNo = (short)intRegionBranch;
		PhoTodayFromServer(1);	 // liest auf jeden die Zeit Fall vom server
		m_bStandardEngine = m_Db.IsStandardEngine();

		char* user;
		user = _tcsdup(m_UserName);
		strcpy(m_Anwender, user);
		free(user);

		// fill the general permissions for compatibility but without rights, permissions cannot be managed directly anymore in ZDPUtil
		// they must be set in UADM
		m_AllgRechte = "000000";
		// set the region
		m_Region.RemoveAll();
		m_Region.Add(intRegionBranch);
		// done
		m_bConnected = true;
		return true;
	}
	return false;
}

bool CConSoVa2::TryConnect( CString ServerName, CString DbaseName, CString ServerProgram )
{
	BOOL bOk;

	CString errmld;
	CString DbEnv;

	DbEnv = "";		// keine Environmentvariable definiert

	m_bConnected = false;
	m_bSynchronized = false;
	m_ServerName = ServerName;
	m_DbaseName  = DbaseName;

	m_RegistryProfile.WriteLastServerDbNames(m_ServerName, m_DbaseName);
	((CMainFrame*)AfxGetMainWnd())->SetConnectinfoToView();	

	unsigned int uiPort = 0;

	if (DbaseName == "zpps1de" || DbaseName == "ide21") 
		uiPort = 10303;
	else if (DbaseName == "zpps2at" || DbaseName == "iat21") 
		uiPort = 10313;
	else if (DbaseName == "zpps2pat" || DbaseName == "iat21pre")
		uiPort = 10413;
	else if (DbaseName == "zpps2hr" || DbaseName == "ihr21") 
		uiPort = 10323;
	else if (DbaseName == "zpps1ch" || DbaseName == "ich21")
		uiPort = 10333;
	else if (DbaseName == "zpps1pch" || DbaseName == "ich21pre") 
		uiPort = 10343;
	else if (DbaseName == "zpps2fr" || DbaseName == "ifr21") 
		uiPort = 10353;
	else if (DbaseName == "zpps2pfr" || DbaseName == "ifr21pre")
		uiPort = 10363;
	else if (DbaseName == "zpps2bg" || DbaseName == "ibg21") 
		uiPort = 10393;
	else if (DbaseName == "zpps2rs" || DbaseName == "irs21")
		uiPort = 10403;

	// mit UnixFoundation wurden die Portnummern um 50000 erhöht !
	if (DbaseName.GetAt(0) == 'i')
		uiPort += 50000;

	CString port;
	port.Format(" %ld", uiPort);	
	
	CString SrvProg;
	SrvProg.Format("zdputiluiserv_%s%s.bin", 
						GetCountry( ISO3166, DbaseName ), GetSubModule( Suffix, DbaseName ));
	SrvProg.MakeLower();
	ServerProgram = SrvProg;

	((CZdpUtilApp*) AfxGetApp())->SetServerProgramName(ServerProgram);	
	
//	BeginWaitAction();
	BeginWaitCursor();

	// Connect

	bOk = m_Db.OpenConnectToDbViaEshu( m_ServerName + port, ServerProgram, m_DbaseName, DbEnv, errmld);

	EndWaitCursor();

	if ( !bOk )
	{
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

bool CConSoVa2::TryDefaultConnect( CString ServerNickName, char *ServerProgram )
{
	CString ServerName;
	CString DbaseName;
	m_RegistryProfile.ReadLastServerDbNames(ServerName, DbaseName);
	
 	if ( ServerName.IsEmpty() || DbaseName.IsEmpty() )
	{
		CString errmld;
		if ( FindServerName( ServerNickName, ServerName, errmld ) )		// einmalig Werte aus WWS.INI
		{
			DbaseName = m_DefaultDbaseName;
			if ( TryConnect( ServerName, DbaseName, ServerProgram ) ) 
			{
				return true;
			}
			return false;
		}
		else
			return TryDialogConnect( ServerProgram ) == 0;
	}
	else
		return TryConnect( ServerName, DbaseName, ServerProgram );

}

void CConSoVa2::CloseConnection( ) 
{
	if (m_bConnected == true)
	{
		DoThingsBeforeCloseDatabase();

		CString errmld;

#ifdef MIT_ALTER_PFLEGE
		// Close Pflege, Datenbank
		char errstr[ 80 ];
		ClosePflege( errstr );
#endif
		// Close Datenbank
		m_Db.CloseConnectToDb( errmld );
		// close voodoo server connection
		::NmpClose();

		m_bConnected = false;
		m_bSynchronized = false;
		m_ServerName = "";
		m_DbaseName  = "";
		m_ServerProgram = "";
		m_UadmRegionNo = 0;
		m_UserName = "";
		m_Password = "";
	}
}

int CConSoVa2::TryDialogConnect( char *ServerProgram )  
{
	CString ServerName;
	CString DbaseName;
	CServerDlg Dlg;

	m_RegistryProfile.ReadLastServerDbNames(ServerName, DbaseName);

	Dlg.SetDbaseName ( m_DbaseName );
	Dlg.SetServerName( m_ServerName );

    if ( Dlg.DoModal() != IDOK ) return -1;

  	ServerName = Dlg.GetServerName();

//	if ( ServerName.IsEmpty() ) return -1;

	if ( m_bConnected )
	{
		DoThingsBeforeCloseDatabase();
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

	DbaseName = Dlg.GetDbaseName();

	if ( TryConnect( ServerName, DbaseName, ServerProgram ) ) 
	{
		return 0;
	}
	else
		return 1;
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


bool CConSoVa2::DarfToolbarAendernPflegen( )
{
	return	m_AllgRechte.GetAt(AR_ANL_SUPER) == '1';
}

bool CConSoVa2::DarfToolbarAendern( )
{
	return	m_bCustomToolbar;
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

void CConSoVa2::SetLoginRechte(CString strRights)
{
	m_RegioRechte.RemoveAll();
	m_RegioRechte.Add(strRights);
}

CStringArray* CConSoVa2::GetLoginRechte()
{
	return &m_RegioRechte;
}

CUIntArray* CConSoVa2::GetLoginRegion()
{
	return &m_Region;	
}
// ZdpDruck.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Shlobj.h" 
#include "ZdpDruck.h"
#include <phxlib/CountryQuery.h>
#include "MainFrm.h"
#include "ZdpDruckDoc.h"
#include "ZdpDruckView.h"
#include "GetBranches.h"
#include "MenuNumbers.h"
#include "LineprotDlg.h"

#include "ConSoVa3.h"
#include "UADMLoginManager.h"
//#include <uduprot.h>
#include <libscsvoodoo/libscsvoodoo.h>  

// fuer Knoedel
#include <eklibs/hamfcs/hBmpButton.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEFAULT_SERVERMODE 0

#include "../cdm_version.h"

#define ZDPDRUCK_VERSION "1.107"
static char* SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - " ZDPDRUCK_VERSION ": ZDPDruck 11.11.2025";

/*******************************************************************************************/
/*!
\mainpage Central Data Maintenance (CDM) - ZDPDruck.exe
\page page2 ZDPDruck.exe
________________________________________________________________________________________
\version          16.238 - 1.107
\date             11.11.2025
\internal
- TA: CPR0002057 - All - integration into UADM and use of new login and password policy
\endinternal
\customer
\de
- CPR0002057 - All - Integration in UADM und Nutzung des neuen Logins und Password Policy
\en
- CPR0002057 - All - integration into UADM and use of new login and password policy
\endcustomer
________________________________________________________________________________________
\version          16.148
\date             23.04.2021
\internal
- WH: CPR - 201083 - DE - Erweiterung des Kennzeichens für Arzneimittelbezug, added 2 new entries AmbLiefView.cpp for validation
\endinternal
\customer
\de
- CPR - 201083 - DE - Erweiterung des Kennzeichens für Arzneimittelbezug
\en
- CPR - 201083 - DE - Enhancement of selectable medicine relation
\endcustomer
________________________________________________________________________________________
\version	6.46
\date		22.01.2019
\internal
 - TH: CPR-170976 neuer Werte P für liefer.arzneimittelbezug
\endinternal
________________________________________________________________________________________
\version	6.45
\date		08.06.2018
\internal
 - TH: CPR-170976 neue Werte T + M + H + V für liefer.arzneimittelbezug
\endinternal

________________________________________________________________________________________
\version	6.44
\date		30.10.2015
\internal
- TH: SR-15055892 = Liste NEM-Wechsel-Artikel; art=4 (statt art=1)
\endinternal

________________________________________________________________________________________
\version	6.43
\date		15.05.2015
\internal
- TH: I-15008077 = Handling aep_alt = 0
\endinternal

________________________________________________________________________________________
\version	6.42
\date		20.04.2015
\internal
- TH: SR-15016331 = neues Feld zartikel.preissenkung bei Preiserhöhungen / Preissenkungen
\endinternal

________________________________________________________________________________________
\version	6.41
\date		08.04.2015
\internal
- TH: SR-15014334 = Preiserhöhungen / Preissenkungen erweitert
\endinternal

________________________________________________________________________________________
\version	6.40
\date		19.02.2015
\internal
- TH: CR-14D132 = BugFix
\endinternal

________________________________________________________________________________________
\version	6.39
\date		10.02.2015
\internal
- TH: CR-14D132 = Hersteller für LogIndex
\endinternal

*/

// 6.04  28.01.2002 : Druck Preiserhoehung
// 6.05  15.05.2002 : Neue Pipe: ZdpDruckPipeSrv
// 6.06  15.05.2002 : Gedenktext Knoedel entfernt
// 6.07  06.12.2002 : Preiserhoehung mit Abverkauf
// 6.08  09.12.2002 : Preiserhoehung mit Abverkauf Fehler lt. Mail Heidicker behoben
// 6.09  18.02.2003 : Preiserhoehung mit Abverkauf Fehler bei Ausgabe in Textdatei behoben
// 6.10  31.03.2003 : Preiserhoehung mit Abverkauf HAGEDA STUMPF
// 6.11  29.04.2003 : GH - Aenderungen  ( CGhaenView )
// 6.12  11.05.2004 : auf variable DB umstellen, auf eshu umstellen, neues Logo
// 6.13: 01.07.2004 : Anmeldeprozedur aendern 
// 6.14  24.11.2004 : K.Hinz Neue Liste Arzneimittelbezug
// 6.15  14.12.2004 : K.Hinz Bereinigen Abbruch Preiserhöhung mit Abverkauf
// 6.16	 01.06.2005 : K.Hinz Neue Auswertung 'Liste wesentliche Preisänderungen'
// 6.17  23.06.2005 : K.Hinz InKonsView Nahrungstest von = 'K' auf <> ' ' geändert
// 6.18  15.07.2005 : K.Hinz Galdat Neuanlagen ohne Artikelstammsatz
//                           Galdat Änderungen und Differenz zu Zartikel AH oder Ersatz PZN  
// 6.19  08.09.2005 : K.Hinz Galdat Neuanlagen um Herstellername ergänzt
// 6.20  25.10.2005 : K.Hinz Artikel mit Änderung Kz Elektroschrott
//                           Artikelneuaufnahmen mit Kennzeichen Elektroschrott 
// 6.21	 21.11.2005 : K.Hinz Galdat Neuaufnahmen Sortieren nach Hersteller
//                           Galdat Löschungen Sortieren nach Artikelname
// 6.22	 18.01.2006	: K.Hinz Neue Felder für NEMArtikel Liste
// 6.23  08.11.2006 : K.Hinz Hersteller nach Hersteller-Code
// 6.24  18.09.2007 : K.Hinz Preisaenderungen mir Abverkauf ( Regionen ausgebaut)
// 6.25  21.07.2008 : K.Hinz Anpassungen Anmeldung wegen NUMA
// 6.26  12.08.2008 : K.Hinz NEM-Artikel lesen auf Client umgestellt
// 6.27  14.01.2009 : K.Hinz Auswertungen Preiserhöhungen neue Felder apothekenpfl und rezeptpfl
// 6.28  19.08.2010 : K.Hinz Neuer Port für DB zpps2pat  
// 6.29  30.08.2011 : K.Hinz Anpassung AMB-Lieferanten ungleich A,B,C
// 6.30	 24.07.2012 : T.Hörath Vorbereitung UnixFoundation
// 6.31	 19.03.2013 : T.Hörath AIX ports
// 6.32	 15.11.2013 : T.Hörath PZN 8
// 6.33	 07.02.2014 : T.Hörath Ausdruck Artikel mit NEM-Änderung angepasst
// 6.34	 24.06.2014 : T.Hörath Änderung von Galdat auf LogIndex
// 6.35	 15.07.2014 : T.Hörath VS 2010.
// 6.36  12.08.2014 : T.Hörath ini- file replaced by registry
// 6.37  19.08.2014 : T.Hörath SetRegistryKey("ZDP") for storing of customized toolbar
// 6.38  05.09.2014 : T.Hörath BugFix IKS-Code bei LogIndex- Neuaufnahmen
// 6.39  10.02.2015 : T.Hörath CR-14D132 = Hersteller für LogIndex
// 6.40  19.02.2015 : T.Hörath CR-14D132 = BugFix
// 6.41  08.04.2015 : T.Hörath SR-15014334 = Preiserhöhungen / Preissenkungen erweitert
// 6.42  20.04.2015 : T.Hörath SR-15016331 = neues Feld zartikel.preissenkung bei Preiserhöhungen / Preissenkungen
// 6.43  15.05.2015 : T.Hörath I-15008077 = Handling aep_alt = 0
// 6.44  30.10.2015 : T.Hörath SR-15055892 = Liste NEM-Wechsel-Artikel; art=4 (statt art=1)
//------------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CEk1App, CWinApp)
	//{{AFX_MSG_MAP(CEk1App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TASCHENRECHNER, OnCalculator)
	ON_COMMAND(ID_SERVER, OnServer)
	ON_UPDATE_COMMAND_UI(ID_SERVER, OnUpdateServer)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	// benutzt von DruckView
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEk1App construction

CString GetCountry( Country_Return_Type crt, CString Database )
{
	CCountryQuery CQ;

	if (crt == KFZ)
		return CQ.CQ_GetCountryKFZ(Database);
	else
		return CQ.CQ_GetCountryISO3166(Database);
}

CString GetSubModule( SubModul_Return_Type srt, CString Database )
{
	CCountryQuery CQ;

	if (srt == Verz)
		return CQ.CQ_GetSubModuleVerz(Database);
	else
		return CQ.CQ_GetSubModuleSuffix(Database);
}

long GetWWSBinVerzeichnis( CString &cDirec, CString &errmld )
{
  long s;
	char log_path[300];
  CString SubModule;


	if ( ( s = UnxGetenv ( "WWS", log_path ) ) != 0 )
	{
		//errmld  = CResString::ex().getStrTblText(IDS_STRING629);
		//errmld += DynErrmld();
	}
	else
	{
		cDirec  = log_path;

		CString Server;
		Server = ((CEk1App*) AfxGetApp())->GetServerName();

		cDirec += _T( "/" );
		cDirec += GetCountry( ISO3166,((CEk1App*) AfxGetApp())->GetDbaseName() ).MakeLower();
		cDirec += _T( "/cdm" );
		cDirec += _T( "/" );
		SubModule = GetSubModule( Verz ,((CEk1App*) AfxGetApp())->GetDbaseName());
      
		if ( !SubModule.IsEmpty())
		{
			cDirec += SubModule;
			cDirec += _T( "/bin/" );
		}
		else 
				cDirec += _T( "bin/" );		
	}

	return s;

}

CEk1App::CEk1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_Con = NULL;
//	m_Branch = NULL;
//  m_Region = NULL;

	m_nCompressMode = COMPRESS_OFF;

	m_nClientProtocolMode = 0;
	m_strClientProtocolFile.Empty();

	m_Server[0].ServerProgram = _T("" );
	m_Server[0].ServerProgramName = _T("so_sohn" );
	m_Server[0].CompressMode = COMPRESS_OFF;
	m_Server[0].FetchMode = 0;
	m_Server[0].ServerMode = 0;

	m_Server[1].ServerProgram = _T("zdpuiserv" );
	m_Server[1].ServerProgramName = _T("zdpuiserv");
	m_Server[1].CompressMode = COMPRESS_OFF;
	m_Server[1].FetchMode = 0;
	m_Server[1].ServerMode = 0;

	m_nActualServer = 1;
	m_strINIFile = "";
	m_bConnected = false;
	m_bUADM = false;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEk1App object

CEk1App theApp;


/////////////////////////////////////////////////////////////////////////////
// CConnect Class

class CConnect : public CConSoVa3
{
public:
	 void DoThingsBeforeCloseDatabase();
};

void CConnect::DoThingsBeforeCloseDatabase()
{
	((CMainFrame*)AfxGetMainWnd())->CleanUp();	
}

/////////////////////////////////////////////////////////////////////////////
// CEk1App initialization

BOOL CEk1App::InitInstance()
{
	// Grid
	// If you are using Grid features, enable the following initialisation
	GXInit();

	// MFC OLE automation classes
//	AfxEnableControlContainer();

	// define the INI File
	char appPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, appPath, sizeof(appPath));
	PathRemoveFileSpec(appPath);

	m_strINIFile = CString(appPath);
	m_strINIFile.Append("\\");
	m_strINIFile.Append(UADM_APPLICATION_NAME);
	m_strINIFile.Append(".ini");

	verifyUADM();

//	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	LoadStdProfileSettings(0);	// do not load

	SetRegistryKey("ZDP"); // needed for adaptable toolbar

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CZdpDruckDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CZdpDruckView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
//	m_pMainWnd->ShowWindow(SW_SHOW);
//	m_pMainWnd->UpdateWindow();

	//	Maximize Window
	CMainFrame* pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
//	pMainFrame->ShowWindow( SW_SHOWMAXIMIZED );
	pMainFrame->ShowWindow( SW_SHOW );
	pMainFrame->UpdateWindow();

	//  Initialize Views
 	pMainFrame->DefineViews();
	pMainFrame->SetDefaultView( ); // Bild schneller da

	//  Create Formviews
 	pMainFrame->CreateFormViews();

	//	Connect to server and database
//	m_Con    = new CConSoVa1;
	m_Con = new CConnect();

	// new: use UADM for login instead of hardcoded old way
	if (IsUADM() == true)
	{
		doUADMLogin();
	}
	else
	{
		m_Con->InitValues(THIS_PROGRAM_NUMBER, MNR_MAX_MENUS, "phosix");

		//	m_Branch = new CGetBranches;
		//  m_Region = new CGetRegion;

		if (m_Con->TryDefaultConnect(_T("ZdpDruckPipeSrv"),
			m_Server[m_nActualServer].ServerProgram,
			m_Server[m_nActualServer].CompressMode))
		{
			if (GetServerMode() == 2)
			{
				m_Con->CloseConnection();
				return TRUE;
			}

			// load branches
	//		((CMainFrame*)AfxGetMainWnd())->LoadFilialen( m_Branch );

			// load user spezific customized Toolbar
			((CMainFrame*)AfxGetMainWnd())->LoadToolBarState(GetUserName());

			pMainFrame->SetDefaultView();
		}
	}
	return TRUE;
}

int CEk1App::ExitInstance() 
{
	//  end connection
//  delete m_Region;
//	delete m_Branch;
	delete m_Con;
	// Grid
	// If you are using Grid features, enable the following initialisation
	GXTerminate();

	return CWinApp::ExitInstance();

}	


///////////////////////////////////////////////////////////////////
// Public Functions

int CEk1App::GetServerMode()
{
	int ServerMode;
//	ServerMode = m_Con->GetServerMode();
	ServerMode = m_Server[m_nActualServer].ServerMode;
	return ServerMode;
}

CString CEk1App::GetServerProgramName( )
{
	return  m_Server[m_nActualServer].ServerProgramName;
}

CString CEk1App::GetServerProgram( )
{
	return  m_Server[m_nActualServer].ServerProgram;
}

//---------------------------------------------------------
void CEk1App::SetServerProgramName(CString name)
{
	m_Server[m_nActualServer].ServerProgramName = name;
}

int CEk1App::GetCompressMode()
{
	return m_Con->GetCompressMode();
}

void CEk1App::SetCompressMode( int nCompressMode )
{
	m_Con->SetCompressMode( nCompressMode );
}

bool CEk1App::GetBufferedMode()
{
	return m_Con->GetBufferedMode();
}

void CEk1App::SetBufferedMode( bool nBufferedMode )
{
	m_Con->SetBufferedMode( nBufferedMode );
}

bool CEk1App::IsSyncronized()
{
	return m_Con->IsSyncronized();
}

CString CEk1App::GetServerHandler( )
{
	return m_Con->GetServerHandler();
}

CString CEk1App::GetServerName( )
{
	return m_Con->GetServerName();
}

CString CEk1App::GetDbaseName( )
{
	return m_Con->GetDbaseName();
}

CString CEk1App::GetUserName( )
{
	return m_Con->GetUserName();
}

char* CEk1App::GetRefToAnwender( )
{
	return m_Con->GetRefToAnwender();
}

bool CEk1App::IsUADM()
{
	return m_bUADM;
}

bool CEk1App::IsStandardEngine()
{
	return m_Con->IsStandardEngine();
}

bool CEk1App::DarfRechtePflegen()
{
	return m_Con->DarfRechtePflegen();
}

bool CEk1App::DarfSubSuperAnlegen( )
{
	return m_Con->DarfSubSuperAnlegen( );
}

bool CEk1App::DarfMenuPflegen( int MenuNr )
{
	if (IsUADM() == true)
	{
		return m_Con->DarfMenuPflegen(m_Con->GetUADMRegionNo(), MenuNr);
	}
	// else
	// Zentrale Pflege -> Region REGION_ZDP ( 99 )
	return m_Con->DarfMenuPflegen( REGION_ZDP, MenuNr );
}

bool CEk1App::DarfMenuAendern( int MenuNr )
{
	if (IsUADM() == true)
	{
		return m_Con->DarfMenuAendern(m_Con->GetUADMRegionNo(), MenuNr);
	}
	// else
	// Zentrale Pflege -> Region REGION_ZDP ( 99 )
	return m_Con->DarfMenuAendern( REGION_ZDP, MenuNr );
}

bool CEk1App::ReadUserRights( CString& cErrmld )
{
	return m_Con->ReadUserRights( cErrmld );
}

CStringArray* CEk1App::GetLoginRechte()
{
	return m_Con->GetLoginRechte();
}

CUIntArray* CEk1App::GetLoginRegion()
{
	return m_Con->GetLoginRegion();	
}

// Branches

CString CEk1App::GetCurrentBranchName( bool mode )
{
//	return m_Branch->GetCurrentBranchName( mode );
	return "";
}

void CEk1App::SetCurrentBranch( int index )
{
//	m_Branch->SetCurrentBranch( index );
}

//short CEk1App::GetCurrentBranchNumber( )
//{
//	return m_Branch->GetCurrentBranchNumber( );
//}


bool CEk1App::IsConnected( )
{
	if ( m_Con == NULL )
		return false;
	else
		return m_Con->IsConnected();
}


////////////////////////////////////////////////////
// View wechseln

void CEk1App::ChangeToView( int nViewNr )
{
	((CMainFrame*)AfxGetMainWnd())->ChangeToView( nViewNr );
}

void CEk1App::ChangeBackToView( int nViewNr ) 
{
	((CMainFrame*)AfxGetMainWnd())->ChangeBackToView( nViewNr ) ;
}

void CEk1App::ChangeBackToView( CView *pView )
{
	((CMainFrame*)AfxGetMainWnd())->ChangeBackToView( pView ) ;
}


////////////////////////////////////////////////////
// Menu Steuerung


void CEk1App::EnableTbComboBranches( BOOL bEnable )
{
	((CMainFrame*)AfxGetMainWnd())->EnableTbComboBranches( bEnable );
}


void CEk1App::SetMenuOnOff( int nBearbeiten, int nSave, int nDelete, 
			  			    int nSearch, int nNext, int nPrev ) 
{
	((CMainFrame*)AfxGetMainWnd())->
		SetMenuOnOff( nBearbeiten, nSave, nDelete, nSearch, nNext, nPrev );
}

void CEk1App::SaveMenuState( bool& bBearbeiten, bool& bSave, bool& bDelete, 
			  				 bool& bSearch, bool& bNext, bool& bPrev ) 
{
	((CMainFrame*)AfxGetMainWnd())->
		SaveMenuState( bBearbeiten, bSave, bDelete, bSearch, bNext, bPrev );
}

void CEk1App::SetMenuState( bool bBearbeiten, bool bSave, bool bDelete, 
			  				bool bSearch, bool bNext, bool bPrev ) 
{
	((CMainFrame*)AfxGetMainWnd())->
		SetMenuState( bBearbeiten, bSave, bDelete, bSearch, bNext, bPrev );
}

void CEk1App::PushMenuState(  ) 
{	
	((CMainFrame*)AfxGetMainWnd())->PushMenuState(  );
}

void CEk1App::PopMenuState(  ) 
{	
	((CMainFrame*)AfxGetMainWnd())->PopMenuState(  );
}


void CEk1App::SetDruckState( bool bDruck )
{
	((CMainFrame*)AfxGetMainWnd())->SetDruckState( bDruck );
}

////////////////////////////////////////////////////
// Central Questions


bool CEk1App::YouWantToDo( CString Frage )
{
	if ( ((CMainFrame*)AfxGetMainWnd())->IsAutoFrage() ) return true; 
	return AfxMessageBox( Frage, MB_YESNO | MB_ICONQUESTION ) == IDYES;
}	

bool CEk1App::YouWantToStoreRecord( )
{
	if ( ((CMainFrame*)AfxGetMainWnd())->IsAutoFrage() ) return true; 
	return AfxMessageBox( "Satz speichern", MB_YESNO | MB_ICONQUESTION ) == IDYES;
}

bool CEk1App::YouWantToDeleteRecord( )
{
	if ( ((CMainFrame*)AfxGetMainWnd())->IsAutoFrage() ) return true; 
	return AfxMessageBox( "Satz loeschen", MB_YESNO | MB_ICONQUESTION ) == IDYES;
}

bool CEk1App::IsSafeToExit( )
{
	if ( ((CMainFrame*)AfxGetMainWnd())->IsSafeToExit( ) )
	{
		bool bFrage;
		if ( ((CMainFrame*)AfxGetMainWnd())->IsAutoFrage() ) 
			bFrage = true; 	
		else
			bFrage = AfxMessageBox( "Anwendung beenden",
									MB_YESNO | MB_ICONQUESTION ) == IDYES;
		if ( bFrage && IsConnected() )
			m_Con->DoThingsBeforeCloseDatabase();
		return bFrage;

	}
	else
	{
		AfxMessageBox( "Bitte zuerst Bearbeitung beenden" );
		return false;
	}
}

////////////////////////////////////////////////////
// Wait Messages	

void CEk1App::BeginWaitAction( )
{
	BeginWaitCursor();
	((CMainFrame*)AfxGetMainWnd())->GetStatusBar()->PleaseWait();
}

void CEk1App::EndWaitAction( )
{
	((CMainFrame*)AfxGetMainWnd())->GetStatusBar()->EndPleaseWait();
	EndWaitCursor();
}

////////////////////////////////////////////////////
// Other Messages

void CEk1App::MeldRecordWasDeleted( ) 
{
	AfxMessageBox( "Satz wurde zwischenzeitlich gelöscht" );
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	ChBmpButton	m_cBmpB1;
	CStatic	m_cBmpText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void BmToggle( );
	bool b_toggle;

protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnPaint();
	afx_msg void OnAboutPb();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ABOUT_PB, m_cBmpB1);
	DDX_Control(pDX, IDC_ABOUT_KNOEDEL, m_cBmpText);
	//}}AFX_DATA_MAP
}

void CAboutDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	CString cStr;
	char info[15];
	memcpy( info, &SCCSID[19], 14 );
	info[14] = '\0';
	cStr = "ZDPDruck Version ";   cStr += info;
	((CStatic *) GetDlgItem( IDC_ABOUT_VERSION ))->SetWindowText( cStr );
	memcpy( info, &SCCSID[44], 10 );
	info[10] = '\0';	
	cStr = "Last Update:  ";   cStr += info;
	((CStatic *) GetDlgItem( IDC_ABOUT_DATE ))->SetWindowText( cStr );
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ABOUT_PB, OnAboutPb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CAboutDlg::BmToggle( ) 
{
	if ( b_toggle )
	{
    	m_cBmpB1.InitBitmap(IDB_BM_KNOEDEL );	
		m_cBmpText.SetWindowText( "Knödel" );
	}
	else
	{
		m_cBmpB1.InitBitmap(IDB_BM_VOGESE );
		m_cBmpText.SetWindowText( "Vogese" );		
	}
	b_toggle = !b_toggle;
}

void CAboutDlg::OnAboutPb() 
{
	// TODO: Add your control notification handler code here
	if ( b_toggle )
		CDialog::OnCancel();	
	else
		BmToggle( ) ;		
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	b_toggle = true;
	BmToggle( ) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// App command to run the dialog
void CEk1App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CEk1App commands

/////////////////////////////////////////////////////////////////////////////
// Calculator

void CEk1App::OnCalculator() 
{
	// TODO: Add your command handler code here

	HWND hCalcWnd = ::FindWindow("SciCalc", NULL );
	if ( hCalcWnd != NULL ) 
	{
		::BringWindowToTop(hCalcWnd);			 // in Vordergrund holen
		::ShowWindow( hCalcWnd, SW_SHOWNORMAL ); // restourieren, falls minimiert
	}
	else if( WinExec("CALC.EXE",SW_SHOW) < 32 )
		AfxMessageBox("CALC.EXE not found");	
}

///////////////////////////////////////////////////////////////////////////
// Server

void CEk1App::OnServer() 
{
	if (IsUADM() == true)
	{
		doUADMLogin();
	}
	else
	{
		int s = m_Con->TryDialogConnect(m_Server[m_nActualServer].ServerProgram,
			m_Server[m_nActualServer].CompressMode);
	if ( s == 0 )
	{
		if ( GetServerMode() == 2 )
		{

				m_Con->CloseConnection();
			s = -1;

		}


		if ( s == 0 )
		{
			// load branches
//			((CMainFrame*)AfxGetMainWnd())->LoadFilialen( m_Branch );

			// load user spezific customized Toolbar
			((CMainFrame*)AfxGetMainWnd())->LoadToolBarState( GetUserName() );
		}
	}
	((CMainFrame*)AfxGetMainWnd())->SetDefaultView( ); // ?????? hier ???
	}
}

void CEk1App::OnUpdateServer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ((CMainFrame*)AfxGetMainWnd())->IsDefaultView( ) );
}

///////////////////////////////////////////////////
// Lockmode

bool CEk1App::SetLockmode()
{
	long s;

	char *sql = "SET LOCK MODE TO WAIT 5";

    s = SqlExecuteImm( sql );
	if ( s == -554 ) s = 0;  /* wenn Standard-Engine */

	if ( s != 0 )
	{
		CString cErrmld;
		cErrmld.Format( "%s\n%s\nLockmode konnte nicht gesetzt werden", sql, DynErrmld() );
		AfxMessageBox( cErrmld );
	}

	return s == 0;
}

bool CEk1App::verifyUADM()
{
	// indicator for UADM is the new ZDPUTIL.ini file
	FILE* pFile = NULL;
	if (m_strINIFile.IsEmpty() == false)
	{
		fopen_s(&pFile, m_strINIFile, "r"); // just to check if the file exists
		if (pFile != NULL)
		{
			// exists, so use the new UADM
			fclose(pFile);
			m_bUADM = true;
			return true;
		}
	}
	return false;
}

bool CEk1App::doUADMLogin()
{
	// the m_Con object is the real connection to the backend
	if (m_bConnected == true)
	{
		// reset the old connection
		m_Con->DoThingsBeforeCloseDatabase();
		m_Con->CloseConnection();
		m_bConnected = false;
		((CMainFrame*)AfxGetMainWnd())->LoadToolBarState(GetUserName());
		SetServerProgramName(m_Con->GetServerProgram());
		((CMainFrame*)AfxGetMainWnd())->SetConnectinfoToView();
		((CMainFrame*)AfxGetMainWnd())->SetDefaultView();
	}

	CString regKey("Software");
	regKey.Append("\\");
	regKey.Append("ZDP"); // instead of UADM_APPLICATION_NAME, get the registry from ZDP

	// the login manager uses the UADM server and db, which is different to the application backend server
	UADM::CUADMLoginManager loginMgr;
	if (loginMgr.initialize(m_strINIFile.GetString(), regKey.GetString(), UADM_APPLICATION_NAME, CDM_VERSION " - " ZDPDRUCK_VERSION) == true)
	{
		m_bConnected = false;
		while (m_bConnected == false)
		{
			// new login via UADM library
			if (loginMgr.loginWithDialog("", this->m_pMainWnd->m_hWnd) == false)
			{
				m_bConnected = false;
				return false;
			}
			BeginWaitCursor();
			loginMgr.getUserID();
			CString strUsername = loginMgr.getUsername().c_str();
			loginMgr.getLanguage().c_str();
			CString strEnv = loginMgr.getEnvironment().c_str();
			CString strServerName = CString(loginMgr.getServername().c_str());
			CString strService = CString(loginMgr.getServiceName().c_str());
			CString strDbaseName = CString(loginMgr.getDatabase().c_str());
			CString strCountry = loginMgr.getCountry().c_str();
			CString strRegionBranch = loginMgr.getRegionBranchNo().c_str();
			int intPortNo = loginMgr.getPortNoVal();
			m_Con->Initialize(MNR_MAX_MENUS, strUsername);
			// start the connection to the target server and DB
			m_bConnected = m_Con->OpenConnection(strServerName, strService, strDbaseName, intPortNo, loginMgr.getRegionBranchNoVal());
			if (m_bConnected == false)
			{
				m_Con->CloseConnection();

				CString strText = "";
#ifdef _DEBUG
				// for developers
				strText.Format("Cannot connect ZDPDruck Backend Voodoo service %s on server %s with port %i", m_Con->GetServerProgram(), strServerName, intPortNo);
#else
				// for business users
				strText.Format("Cannot connect ZDPDruck Backend service on %s environment for %s with region / branch %s", strEnv, strCountry, strRegionBranch);
#endif
				MessageBox(NULL, strText, "Connect Error", MB_OK);
			}
		}
		// handover permissions from uadm login manager to old zdputil connection manager
		// --------------------------------------------------
		// read userrights from UADM
		// --------------------------------------------------
		CString rightWrite = UADM_RIGHT_WRITE;
		CString rightRead = UADM_RIGHT_READ;
		CString rights = "";
		// menus starts with 1, but will be indexed with 0 in the rights string
		for (int i = 1; i <= MNR_MAX_MENUS; i++)
		{
			if (loginMgr.verifyPermission(i, rightWrite.GetString()) == true)
			{
				rights += RIGHT_WRITE;
			}
			else if (loginMgr.verifyPermission(i, rightRead.GetString()) == true)
			{
				rights += RIGHT_READ;
			}
			else
			{
				rights += RIGHT_NONE;
			}
		}
		m_Con->SetLoginRechte(rights);

		// check and set language
		//CheckLanguage();

		// load user spezific customized Toolbar
		((CMainFrame*)AfxGetMainWnd())->LoadToolBarState(GetUserName());
		SetServerProgramName(m_Con->GetServerProgram());
		((CMainFrame*)AfxGetMainWnd())->SetConnectinfoToView();
		((CMainFrame*)AfxGetMainWnd())->SetDefaultView();
		return true;
	}
	return false;
}
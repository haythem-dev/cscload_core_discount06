// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ZdpDruck.h"

#include "MainFrm.h"
#include "ViewNumbers.h"
#include "GetBranches.h"

#include "hPflegeView.h"
#include "RechteDlg.h"
#include "MenuNumbers.h"

#include "ArtblieView.h"
#include "ArthersView.h"
#include "NemwliefView.h"
#include "NemwartView.h"
#include "Art7prozView.h"
#include "ArtSperrView.h"
#include "NonemlieView.h"
#include "InkonsView.h"
#include "PerhoehView.h"
#include "PerhabvkView.h"
#include "GhaenView.h"
#include "DruckView.h"
#include "AmbliefView.h"
#include "DatacarePreisaend.h"
#include "GaldatNeuanlagenView.h"
#include "GaldatAHView.h"
#include "ElektrowartView.h"
#include "ElektroNeuanlagenView.h"
#include "HerstellerNachHerstellerCodeView.h"
#include ".\mainfrm.h"

#include <windows.h>
#include <VersionHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTTOOLBAR, OnViewCusttoolbar)
	ON_COMMAND(ID_RECORD_SEARCH, OnRecordSearch)
	ON_UPDATE_COMMAND_UI(ID_RECORD_SEARCH, OnUpdateRecordSearch)
	ON_COMMAND(ID_RECORD_NEXT, OnRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_COMMAND(ID_RECORD_PREV, OnRecordPrev)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, OnUpdateRecordPrev)
	ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
	ON_UPDATE_COMMAND_UI(ID_RECORD_DELETE, OnUpdateRecordDelete)
	ON_COMMAND(ID_RECORD_UNDO, OnRecordUndo)
	ON_UPDATE_COMMAND_UI(ID_RECORD_UNDO, OnUpdateRecordUndo)
	ON_COMMAND(ID_RECORD_NEW, OnRecordNew)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEW, OnUpdateRecordNew)
	ON_COMMAND(ID_RECORD_COPY, OnRecordCopy)
	ON_UPDATE_COMMAND_UI(ID_RECORD_COPY, OnUpdateRecordCopy)
	ON_COMMAND(ID_RECORD_CUT, OnRecordCut)
	ON_UPDATE_COMMAND_UI(ID_RECORD_CUT, OnUpdateRecordCut)
	ON_COMMAND(ID_RECORD_PASTE, OnRecordPaste)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PASTE, OnUpdateRecordPaste)
	ON_COMMAND(ID_RECORD_SAVE, OnRecordSave)
	ON_UPDATE_COMMAND_UI(ID_RECORD_SAVE, OnUpdateRecordSave)
	ON_COMMAND(ID_VIEW_MS_STANDARD, OnViewMsStandard)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MS_STANDARD, OnUpdateViewMsStandard)
	ON_COMMAND(ID_VIEW_AUTO_FRAGE, OnViewAutoFrage)
	ON_UPDATE_COMMAND_UI(ID_VIEW_AUTO_FRAGE, OnUpdateViewAutoFrage)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RECHTE, OnUpdateViewRechte)
	ON_COMMAND(ID_VIEW_RECHTE, OnViewRechte)
	ON_COMMAND(ID_ARTBLIE, OnArtblie)
	ON_UPDATE_COMMAND_UI(ID_ARTBLIE, OnUpdateArtblie)
	ON_COMMAND(ID_ARTHERS, OnArthers)
	ON_UPDATE_COMMAND_UI(ID_ARTHERS, OnUpdateArthers)
	ON_COMMAND(ID_NEMWART, OnNemwart)
	ON_UPDATE_COMMAND_UI(ID_NEMWART, OnUpdateNemwart)
	ON_COMMAND(ID_NEMWLIE, OnNemwlie)
	ON_UPDATE_COMMAND_UI(ID_NEMWLIE, OnUpdateNemwlie)
	ON_COMMAND(ID_ART7PROZ, OnArt7proz)
	ON_UPDATE_COMMAND_UI(ID_ART7PROZ, OnUpdateArt7proz)
	ON_COMMAND(ID_ARTSPERR, OnArtsperr)
	ON_UPDATE_COMMAND_UI(ID_ARTSPERR, OnUpdateArtsperr)
	ON_COMMAND(ID_NONEMLIE, OnNonemlie)
	ON_UPDATE_COMMAND_UI(ID_NONEMLIE, OnUpdateNonemlie)
	ON_COMMAND(ID_INKONS, OnInkons)
	ON_UPDATE_COMMAND_UI(ID_INKONS, OnUpdateInkons)
	ON_COMMAND(ID_PERHOEH, OnPerhoeh)
	ON_UPDATE_COMMAND_UI(ID_PERHOEH, OnUpdatePerhoeh)
	ON_COMMAND(ID_PERHABVK, OnPerhabvk)
	ON_UPDATE_COMMAND_UI(ID_PERHABVK, OnUpdatePerhabvk)
	ON_COMMAND(ID_PSENKABVK, OnPsenkabvk)
	ON_UPDATE_COMMAND_UI(ID_PSENKABVK, OnUpdatePsenkabvk)
	ON_COMMAND(ID_GHAEN, OnGhaen)
	ON_UPDATE_COMMAND_UI(ID_GHAEN, OnUpdateGhaen)
	ON_COMMAND(ID_AMBLIEF, OnAmblief)
	ON_UPDATE_COMMAND_UI(ID_AMBLIEF, OnUpdateAmblief)
	ON_COMMAND(ID_DC_PREISAEND, OnDcPreisaend)
	ON_UPDATE_COMMAND_UI(ID_DC_PREISAEND, OnUpdateDcPreisaend)
	ON_COMMAND(ID_GALDATNEU, OnGaldatNeu)
	ON_UPDATE_COMMAND_UI(ID_GALDATNEU, OnUpdateGaldatNeu)
	ON_COMMAND(ID_GALDATAH, OnGaldatAH)
	ON_UPDATE_COMMAND_UI(ID_GALDATAH, OnUpdateGaldatAH)
	ON_COMMAND(ID_HERSTELLERLISTEN_HERSTELLERCODE, OnHerstellerNachHerstellerCode)
	ON_UPDATE_COMMAND_UI(ID_HERSTELLERLISTEN_HERSTELLERCODE, OnUpdateHerstellerNachHerstellerCode)

	//}}AFX_MSG_MAP

	ON_CBN_SELCHANGE(IDS_TB_COMBO_0, OnComboChange_0)
	ON_CBN_SELCHANGE(IDS_TB_COMBO_1, OnComboChange_1)

	ON_MESSAGE( IDD_DRUCK, OnDruckMessage )


	ON_COMMAND(ID_ELEKTROWART, OnElektrowart)
	ON_UPDATE_COMMAND_UI(ID_ELEKTROWART, OnUpdateElektrowart)
	ON_COMMAND(ID_ELEKTRO_NEUAUFN, OnElektroNeuaufn)
	ON_UPDATE_COMMAND_UI(ID_ELEKTRO_NEUAUFN, OnUpdateElektroNeuaufn)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	InitViews( );

	m_msZeiger    = 0;

	m_bIsView     = false;	
	m_bPflege     = false;	
	m_bBearbeiten = false;
	m_bSave       = false;
	m_bDelete     = false;
	m_bIsDruck	  = false;

	m_bMSStandard = true;
	m_bAutoFrage  = false;

	m_TbCbFiliale = NULL;
	m_TbCbSonst   = NULL;

}

CMainFrame::~CMainFrame()
{
	ResetViews( );
}


/*
#define MIT_FILIALBOX
*/

/////////////////////////////////////////////////////////////
// Create Customizable Toolbar with Combobox

// Reihenfolge: nPosition aufsteigend 
// nPosition:   pro Position werden am Anfang 2 sonst 3 Separatoren eingefuegt
//			    bei Positionsangaben beachten

struct CTB_COMBO cb[] =
{
	{ IDS_TB_COMBO_1, 0,     130, 200 },	// 190
#ifdef MIT_FILIALBOX
	{ IDS_TB_COMBO_0, 5 + 2, 110, 200 },    // Pos 5 der urspruenglichen toolbar
#endif
};

bool CMainFrame::CreateToolBarWithCombobox()
{
	CFont font;
	// SystemFont unter Windows NT und unter Windows 95  verscheiden
    OSVERSIONINFO OSVer;
    OSVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    //GetVersionEx(&OSVer); 
    if( IsWindowsXPOrGreater())
    {
        font.Attach(::GetStockObject(DEFAULT_GUI_FONT));
    }
    else
    {
        font.Attach(::GetStockObject(DEVICE_DEFAULT_FONT));
    }
    /*
    if (OSVer.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ) // Win32 on Windows 95. 
		font.Attach(::GetStockObject(DEFAULT_GUI_FONT));
	else
		font.Attach(::GetStockObject(DEVICE_DEFAULT_FONT));
    */
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME,
								  cb, sizeof( cb )/sizeof( struct CTB_COMBO),
						  		  &font ) )
	{
		TRACE0("Failed to create toolbar\n");
		return false;      // fail to create
	}

//	LoadFilialen();

	m_TbCbSonst = m_wndToolBar.GetRefToComboBox( 0 );

/*
	m_TbCbSonst->AddString("am 24.10.2001" );
	m_TbCbSonst->AddString("in den frühen");
	m_TbCbSonst->AddString("Morgenstunden");
	m_TbCbSonst->AddString("gegen 1:30");
	m_TbCbSonst->AddString("starb Knödel");
	m_TbCbSonst->SetCurSel( 0 );
*/
	m_TbCbSonst->AddString("ZdpDruck");
	m_TbCbSonst->SetCurSel( 0 );

	return true;
}


void CMainFrame::LoadFilialen( CGetBranches* Fil )
{
#ifdef MIT_FILIALBOX
	m_TbCbFiliale = m_wndToolBar.GetRefToComboBox( 1 );

	CString cFiliale;
	CString cErr;

	m_TbCbFiliale->ResetContent( );

	if ( Fil->FirstStandortLang( cFiliale, cErr ) == 0 )
	{
		m_TbCbFiliale->AddString( cFiliale );
		while ( Fil->NextStandortLang( cFiliale ) == 0 )
			m_TbCbFiliale->AddString( cFiliale );
		m_TbCbFiliale->SetCurSel( 0 );
	}
	else
	{
		CString cMeld;
		cMeld = "Filialen nicht gelesen\n";
		cMeld += cErr;
		AfxMessageBox( cMeld );
	}
#endif
}

void CMainFrame::EnableTbComboBranches(  BOOL bEnable )
{
#ifdef MIT_FILIALBOX
	if ( m_TbCbFiliale != NULL ) 
		m_TbCbFiliale->EnableWindow( bEnable );
#endif
}


/////////////////////////////////////////////////////////////
// Create

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

#ifdef never
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
#else 
	if (!CreateToolBarWithCombobox())
		return -1;
#endif

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// Fenster zentrieren
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}


void CMainFrame::OnComboChange_0()
{
	if ( m_TbCbFiliale == NULL ) return;

	int nSel = m_TbCbFiliale->GetCurSel();
	if (nSel == CB_ERR)
		TRACE0("Combo: no selection\n");
	else
	{
		CString cs;
		m_TbCbFiliale->GetLBText(nSel, cs);
		TRACE1("Combo: selection is now '%s'\n", cs.GetBuffer(10));
		(( CEk1App *) AfxGetApp())->SetCurrentBranch( nSel );	
		if ( IsDefaultView() )
			SetDefaultView( );
	}
}


void CMainFrame::OnComboChange_1()
{
	if ( m_TbCbSonst == NULL ) return;

	int nSel = m_TbCbSonst->GetCurSel();
	if (nSel == CB_ERR)
		TRACE0("Combo: no selection\n");
	else
	{
		CString cs;
		m_TbCbSonst->GetLBText(nSel, cs);
		TRACE1("Combo: selection is now '%s'\n", cs.GetBuffer(10));
	}
}


///////////////////////////////////////////
// ToolBar

void CMainFrame::LoadToolBarState( CString cUser )
{
//	return;  // //////////////////////// nur zum Test
//	m_wndToolBar.OriginalState();
	CString s;
	s  = _T("Toolbar " );
	s += cUser;
	CString NewVersion = "Toolbar-05";
	CString OldVersion = "Toolbar-04";
	m_wndToolBar.LoadState( ( LPCTSTR ) s,
							( LPCTSTR ) NewVersion, 
							( LPCTSTR ) OldVersion, 
							TRUE );
}


void CMainFrame::CustomizeToolBar( )
{
	m_wndToolBar.GetToolBarCtrl().Customize();
}


///////////////////////////////////////////
// pointer to status bar

ChStatusBar * CMainFrame::GetStatusBar()
{
	return &m_wndStatusBar;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


//////////////////////////////////////////////////////
// Views

#define VIEW_NO		  -2
#define VIEW_DEFAULT  -1

void CMainFrame::DefineViews( )
{
	InsertView( VIEW_DEFAULT  ,"ZdpDruck",	GetActiveView() );
	InsertView( VIEW_ARTBLIE  ,"Artikelliste nach Bestelladresse",
							   new CArtblieView() );
	InsertView( VIEW_ARTHERS  ,"Artikelliste nach Hersteller",
							   new CArthersView() );
	InsertView( VIEW_NEMWART,  "Liste NEM-Wechsel Artikel",   
							   new CNemwartView( ) );
	InsertView( VIEW_NEMWLIE, "Liste NEM-Wechsel Lieferant",   
							   new CNemwliefView( ) );
	InsertView( VIEW_ART7PROZ, "Liste Neuaufnahmen mit verminderter MWST",   
							   new CArt7prozView( ) );
	InsertView( VIEW_ARTSPERR, "Liste NEM-gesperrte Artikel",   
							   new CArtsperrView( ) );
	InsertView( VIEW_NONEMLIE, "Liste Lieferant ohne NEM-Kennung",   
							   new CNonemlieView( ) );
	InsertView( VIEW_INKONS,   "Liste inkonsistenter NEM-Artikel",   
							   new CInkonsView( ) );
	InsertView( VIEW_PERHOEH,  "Liste Preiserhöhungen",   
							   new CPerhoehView( ) );
	InsertView( VIEW_PERHABVK, "Liste Preiserhöhungen mit Abverkauf",   
							   new CPerhabvkView( VIEW_PERHABVK ) );
	InsertView( VIEW_PSENKABVK, "Liste Preissenkungen mit Abverkauf",   
							   new CPerhabvkView( VIEW_PSENKABVK ) );
	InsertView( VIEW_GHAEN,   "Wechsel GH auf \"nicht über GH\"",   
							   new CGhaenView( ) );
	InsertView( VIEW_DRUCK,    "Drucken",   
							   new CDruckView( VIEW_DRUCK ) );
	InsertView( VIEW_AMBLIE, "Liste AMB-Lieferanten mit KZ ungleich A,B,C ",   
							   new CAmbliefView( ) );
	InsertView( VIEW_DCPREISAEND, "Liste wesentliche Preisaenderungen ",   
							   new CDatacarePreisaend( ) );
	InsertView( VIEW_GALDATNEU, "LogIndex Neuanlagen ohne Artikelstammsatz ",   
							   new CGaldatNeuanlagenView( ) );
	InsertView( VIEW_GALDATAH, "LogIndex Änderung und Differenz zu Zartikel (AH oder Ersatz-PZN) ",   
							   new CGaldatAHView( ) );
	InsertView( VIEW_ELEKTROWART, "Liste Elektro-Wechsel Artikel ",   
							   new CElektrowartView( ) );
	InsertView( VIEW_ELEKTRONEU, "Liste Neuanlagen Elektro-Artikel ",   
							   new CElektroNeuanlagenView( ) );
	InsertView( VIEW_HERSTELLERCODE, "Liste Hersteller nach Hersteller-Code ",   
							   new CHerstellerNachHerstellerCodeView( ) );


}

void CMainFrame::SetDefaultView()
{
	SetView( VIEW_DEFAULT, true );
	m_bPflege = false;				// !!!!!!!!!!!!!!!!!!!!!!!!
	m_bIsView = false;				// !!!!!!!!!!!!!!!!!!!!!!!!
}

bool CMainFrame::IsDefaultView()
{
	return GetActViewNr( ) == VIEW_DEFAULT; 	 
}

bool CMainFrame::IsSafeToExit( )
{
	return !m_bBearbeiten;
}

bool CMainFrame::IsAutoFrage()
{
	return m_bAutoFrage;
}

///////////////////////////////////////////////////////////////////
//	Setzten der Menues

void CMainFrame::SetMenuOnOff( int nBearbeiten, int nSave, int nDelete, 
			  				   int nSearch, int nNext, int nPrev ) 
{
	if ( nBearbeiten != 0 )
		m_bBearbeiten = nBearbeiten == 1;
	if ( nSave != 0 )
		m_bSave = nSave == 1;
	if ( nDelete != 0 )
		m_bDelete = nDelete == 1;
	if ( nSearch != 0 )
		m_bSearch = nSearch == 1;
	if ( nNext != 0 )
		m_bNext = nNext == 1;
	if ( nPrev != 0 )
		m_bPrev = nPrev == 1;
}

void CMainFrame::SaveMenuState( bool& bBearbeiten, bool& bSave, bool& bDelete, 
			  				    bool& bSearch, bool& bNext, bool& bPrev ) 
{
	bBearbeiten = m_bBearbeiten;
	bSave   = m_bSave;
	bDelete = m_bDelete;
	bSearch = m_bSearch;
	bNext   = m_bNext;
	bPrev   = m_bPrev;
}

void CMainFrame::SetMenuState( bool bBearbeiten, bool bSave, bool bDelete, 
			  				   bool bSearch, bool bNext, bool bPrev ) 
{

	m_bBearbeiten = bBearbeiten;
	m_bSave   = bSave;
	m_bDelete = bDelete;
	m_bSearch = bSearch;
	m_bNext   = bNext;
	m_bPrev	  = bPrev;
}

void CMainFrame::SetDruckState( bool bDruck )
{
	m_bIsDruck  = bDruck;
}


void CMainFrame::PushMenuState(  ) 
{
	int i;
	i = m_msZeiger;
	if ( i < MAX_MS_ANZ )
	{
		m_msbBearbeiten[i] = m_bBearbeiten;
		m_msbSave[i]   = m_bSave;
		m_msbDelete[i] = m_bDelete;
		m_msbSearch[i] = m_bSearch;
		m_msbNext[i]   = m_bNext;
		m_msbPrev[i]   = m_bPrev;
		m_msZeiger++;
	}
}

void CMainFrame::PopMenuState(  ) 
{
	int i;
	i = m_msZeiger - 1;
	if ( i >= 0 )
	{
		m_bBearbeiten = m_msbBearbeiten[i];
		m_bSave   = m_msbSave[i];
		m_bDelete = m_msbDelete[i];
		m_bSearch = m_msbSearch[i];
		m_bNext   = m_msbNext[i];
		m_bPrev   = m_msbPrev[i];
		m_msZeiger--;
	}
}

/////////////////////////////////////////////////////////////////////////7
// members

typedef struct ONE_VIEW
{
	int nViewNr;
	CString cViewTitle;
	CView*	pView;
}	tONE_VIEW;

void CMainFrame::SetConnectinfoToView()	
{
	CString cStr;
	CString cOrigStr;
	int i;
	int pos;
#ifdef CONNECT_VORNE
	for ( i = 0; i < m_nAnzViews; i++ )
	{
		cStr = m_AllViews[i].cViewTitle;
		pos = cStr.Find( "] " );
		if ( pos >= 0 )
			cOrigStr = cStr.Mid( pos + 2 );
		else
			cOrigStr = cStr;
		cStr = _T("[") + (( CEk1App *) AfxGetApp())->GetDbaseName();
		cStr.TrimRight();
		cStr += _T("@") + (( CEk1App *) AfxGetApp())->GetServerName();
		cStr += _T("] ");
		cStr += cOrigStr;
		m_AllViews[i].cViewTitle = cStr;
	}
#else
	for ( i = 0; i < m_nAnzViews; i++ )
	{
		cStr = m_AllViews[i].cViewTitle;
		pos = cStr.Find( " [" );
		if ( pos >= 0 )
			cOrigStr = cStr.Left( pos );
		else
			cOrigStr = cStr;
		cStr = _T(" [") + (( CEk1App *) AfxGetApp())->GetDbaseName();
		cStr.TrimRight();
		cStr += _T("@") + (( CEk1App *) AfxGetApp())->GetServerName();
		cStr += _T("]");
		cOrigStr += cStr;
		m_AllViews[i].cViewTitle = cOrigStr;
	}
#endif
}


void CMainFrame::InitViews( )
{
	m_AllViews = NULL;
	m_nAnzViews = 0;
}

void CMainFrame::InsertView( int nViewNr, char *cViewTitle, CView *pView )
{
	tONE_VIEW *pAllViews;
	pAllViews = new tONE_VIEW[m_nAnzViews + 1];
	if ( m_nAnzViews > 0 )
	{
		int i;
		for ( i = 0; i < m_nAnzViews; i++ )
			pAllViews[i] = m_AllViews[i];    
		delete [] m_AllViews;
	}
	m_AllViews = pAllViews;
	m_AllViews[ m_nAnzViews ].nViewNr	 = nViewNr;
	m_AllViews[ m_nAnzViews ].cViewTitle = _T( cViewTitle );
	m_AllViews[ m_nAnzViews ].pView		 = pView;
	m_nAnzViews++;
}

void CMainFrame::ResetViews( )
{
	if ( m_AllViews != NULL )
		delete [] m_AllViews;
	m_AllViews = NULL;
	m_nAnzViews = 0;
}


void CMainFrame::CreateFormViews()
{
	// Initialisierung Kontext
	CCreateContext newContext;
	newContext.m_pNewViewClass   = NULL;
	newContext.m_pNewDocTemplate = NULL;
	newContext.m_pLastView       = NULL;
	newContext.m_pCurrentFrame   = NULL;
	newContext.m_pCurrentDoc     = GetActiveDocument();

	CRect ViewRect;
	CRect MaxRect(32000, 32000, -32000, -32000);	// 32000 = grosse Zahl

	for ( int i = 1; i < m_nAnzViews; i++ )
	{
		if ( !m_AllViews[i].pView->Create( NULL, "", WS_CHILD | WS_BORDER,
										   CRect(0,0,0,0),
										   this,	// m_pMainWnd,
										   AFX_IDW_PANE_FIRST + 1,
										   &newContext ) )
			AfxMessageBox("Creation of View failed" );
		m_AllViews[i].pView->OnInitialUpdate();

		ViewRect = ( (ChPflegeView *) m_AllViews[i].pView )->GetMaxViewRect( );
		( (ChPflegeView *) m_AllViews[i].pView )->
			GetMaxRectCorners( MaxRect, ViewRect );
	}
/*
	CRect FramRect;
	this->GetWindowRect( FramRect );
	CView* p_ActiveView = GetActiveView();
	p_ActiveView->GetWindowRect( ViewRect );
	CString s;
	s.Format( "MaxVie: %d %d %d %d\nActVie: %d %d %d %d\nFrame : %d %d %d %d", 
		      MaxRect.left, MaxRect.top, MaxRect.right, MaxRect.bottom,
			  ViewRect.left, ViewRect.top, ViewRect.right, ViewRect.bottom,
			  FramRect.left, FramRect.top, FramRect.right, FramRect.bottom );
	AfxMessageBox( s );
*/
/*
	if ( MaxRect.rigth > MaxRect.left + ( ViewRect.rigth - ViewRect.left ) )

	if ( MaxRect.bottom < MaxRect.top + ( ViewRect.bottom - ViewRect.top ) )
*/
}

void CMainFrame::SetView( int nViewNr, bool bForce )
{
	CView* p_ActiveView = GetActiveView();
	CView* p_NewView;

	m_nActiveView = nViewNr;

	int i = 0;
	while ( i < m_nAnzViews && m_AllViews[i].nViewNr != nViewNr ) i++;
	if ( i == m_nAnzViews ) return;

	p_NewView = m_AllViews[i].pView;
	
	if ( p_NewView == NULL ) return;

	if ( !bForce && p_NewView == p_ActiveView ) return;

	UINT temp = ::GetWindowLong( p_ActiveView->m_hWnd, GWL_ID );
	::SetWindowLong( p_ActiveView->m_hWnd, GWL_ID,
					 ::GetWindowLong(p_NewView->m_hWnd, GWL_ID ));
	::SetWindowLong( p_NewView->m_hWnd, GWL_ID, temp );

	// aktuelle Viewgroesse
	CRect rect;
	p_ActiveView->GetWindowRect( rect );
	ScreenToClient( rect );
	p_ActiveView->ShowWindow( SW_HIDE );
	p_NewView->ShowWindow( SW_SHOW );
	SetActiveView( p_NewView );

	// Neuen View in Groesse an alten anpassen
	p_NewView->MoveWindow( rect );

	p_NewView->Invalidate();
	Invalidate();
	UpdateWindow();

	// change title
	GetActiveDocument( )->SetTitle( m_AllViews[i].cViewTitle );

}


int CMainFrame::GetActViewNr( )
{
	CView* p_ActiveView = GetActiveView();
	int i = 0;
	while ( i < m_nAnzViews && m_AllViews[i].pView != p_ActiveView ) i++;
	if ( i == m_nAnzViews ) return VIEW_NO;
	return m_AllViews[i].nViewNr;
}

int CMainFrame::GetViewNr( CView* pView )
{
	int i = 0;
	while ( i < m_nAnzViews && m_AllViews[i].pView != pView ) i++;
	if ( i == m_nAnzViews ) return VIEW_NO;
	return m_AllViews[i].nViewNr;
}


ChPflegeView* CMainFrame::GetActView( )
{
	CView* p_ActiveView = GetActiveView();
	int i = 0;
	while ( i < m_nAnzViews && m_AllViews[i].pView != p_ActiveView ) i++;
	if ( i == m_nAnzViews ) return NULL;
	if ( m_AllViews[i].nViewNr == VIEW_DEFAULT ) return NULL;
	return (ChPflegeView *) p_ActiveView;
}

ChPflegeView* CMainFrame::GetViewViaNr( int nViewNr )
{
	int i = 0;
	while ( i < m_nAnzViews && m_AllViews[i].nViewNr != nViewNr ) i++;
	if ( i == m_nAnzViews ) return NULL;
	return (ChPflegeView *) m_AllViews[i].pView;
}


void CMainFrame::ChangeToView( int nViewNr ) 
{
	if ( CloseActView() == 0 )
	{
		SetView( nViewNr );
		m_bPflege  = TRUE;
	}					
}

void CMainFrame::ChangeBackToView( int nViewNr ) 
{
	SetView( nViewNr );
	m_bPflege  = TRUE;	
}

void CMainFrame::ChangeBackToView( CView *pView ) 
{
	ChangeBackToView( GetViewNr( pView ) ) ;
}

////////////////////////////////////////////////////////////////////////
// CleanUp before Close Database

void CMainFrame::CleanUp()
{
	int i;
	for ( i = 1; i < m_nAnzViews; i++ )
	{
		( (ChPflegeView *) m_AllViews[i].pView )->CleanUp();
	}
}

////////////////////////////////////////////////////////////////////////
// Aktuellen View schliessen

int CMainFrame::CloseActView() 
{
	int status;
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL )
	{
		status = ActView->UndoSatz( );
/*
		if ( status == 0 )
		{
			HandleDataChanged( ActView );
		}
*/
	}
	else
		status = 0;
	if ( status == 0 )
	{
//		SetView( VIEW_DEFAULT );
		m_bPflege = false;
		m_bNext   = false;
		m_bPrev   = false;
	}
	m_bBearbeiten = false;
//	m_bSearch = true;			// !!!!!! anderes Verhalten
	return status;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnViewCusttoolbar() 
{
	// TODO: Add your command handler code here
	CustomizeToolBar( );
}


////////////////////////////////////////////////////////////////////////
// record search

void CMainFrame::OnRecordSearch() 
{
	int status = -1;
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL ) status = ActView->SucheSatz( );
	if ( status != -1 )		// nichts tun bei -1
	{
		m_bPrev = m_bNext = status == 1;
	}
}

void CMainFrame::OnUpdateRecordSearch(CCmdUI* pCmdUI) 
{
//	 pCmdUI->Enable( m_bIsView ); 
	 pCmdUI->Enable( m_bPflege && m_bSearch && !m_bIsDruck); 	 
}

////////////////////////////////////////////////////////////////////////
// next record

void CMainFrame::OnRecordNext() 
{
	int status = -1;
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL )	status = ActView->NextSatz( );
	if ( status != -1 )		// nichts tun bei -1
	{
		m_bNext = status == 1;
		if ( status ==1 ) m_bPrev = true;	
	}
}

void CMainFrame::OnUpdateRecordNext(CCmdUI* pCmdUI) 
{
//	 pCmdUI->Enable( m_bIsView ); 	
	 pCmdUI->Enable( m_bPflege && m_bNext); 		 
}

////////////////////////////////////////////////////////////////////////
// prev record

void CMainFrame::OnRecordPrev() 
{
	int status = -1;
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL ) status = ActView->PrevSatz( );
	if ( status != -1 )			// nichts tun bei -1
	{
		m_bPrev = status == 1;
		if ( status == 1 ) m_bNext = true;	
	}
}

void CMainFrame::OnUpdateRecordPrev(CCmdUI* pCmdUI) 
{
//	 pCmdUI->Enable( m_bIsView ); 
	 pCmdUI->Enable( m_bPflege && m_bPrev ); 		 
}

////////////////////////////////////////////////////////////////////////
// Bearbeitung abbrechen / Pflege verlassen 

void CMainFrame::OnRecordUndo() 
{
	int status = -1;
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL ) status = ActView->UndoSatz( );
	if ( status != -1 )			// nichts tun bei -1
	{
		if ( status == 0 )
		{
			SetView( VIEW_DEFAULT );
			m_bPflege = false;
		}
		if ( status != 2 )	// neu 28.08.98
		{
			m_bBearbeiten = false;
			//	m_bSearch = true;			// !!!!!! anderes Verhalten
		}
	}
}

void CMainFrame::OnUpdateRecordUndo(CCmdUI* pCmdUI) 
{
//	 pCmdUI->Enable( m_bIsView ); 
	 pCmdUI->Enable( m_bPflege ); 	 
}

////////////////////////////////////////////////////////////////////////
// Satz bearbeiten

void CMainFrame::SetBearbeiten( int status )
{
	// neu: Behelf
	bool bSuchen = false;
	if ( status >= 10 )
	{
		status -= 10;
		bSuchen = true;
	}
	//

	if ( status >= 1 )
	{
		m_bBearbeiten = true;
//		m_bSearch = false;
		m_bSearch = bSuchen; // siehe oben
	}
	if ( status == 1 )
		m_bDelete = true;
	else if ( status == 2 )
		m_bDelete = false; // ???????????
	else if ( status == 3 )
	{
		m_bSearch = true;
		m_bPrev = m_bNext = true;
	}

	m_bSave = true;
}

void CMainFrame::OnRecordNew() 
{
	int status = -1;
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL ) status = ActView->BearbeiteSatz( );
	if ( status != -1 )			// nichts tun bei -1
		SetBearbeiten( status );
}

void CMainFrame::OnUpdateRecordNew(CCmdUI* pCmdUI) 
{
//	 pCmdUI->Enable( m_bIsView ); 	
	 pCmdUI->Enable( m_bPflege && !m_bIsDruck ); 		 
}

////////////////////////////////////////////////////////////////////////
// insert / update record

void CMainFrame::OnRecordSave() 
{
	int status = -1;
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL ) status = ActView->SpeichereSatz( );
//	if ( status != -1 )			// nichts tun bei -1
//		SetBearbeiten( status );

}

int CMainFrame::GetMnrFromView( int ViewNr )
{
	int nNr;

	switch ( ViewNr )
	{
	case VIEW_ARTBLIE:
		nNr = MNR_ARTBLIE;
		break;
	case VIEW_ARTHERS:
		nNr = MNR_ARTHERS;
		break;
	case VIEW_NEMWART:
		nNr = MNR_NEMWART;
		break;
	case VIEW_NEMWLIE:
		nNr = MNR_NEMWLIE;
		break;
	case VIEW_ART7PROZ:
		nNr = MNR_ART7PROZ;
		break;
	case VIEW_ARTSPERR:
		nNr = MNR_ARTSPERR;
		break;
	case VIEW_NONEMLIE:
		nNr = MNR_NONEMLIE;
		break;
	case VIEW_INKONS:
		nNr = MNR_INKONS;
		break;
	case VIEW_PERHOEH:
		nNr = MNR_PERHOEH;
		break;
	case VIEW_PERHABVK:
		nNr = MNR_PERHABVK;
		break;
	case VIEW_GHAEN:
		nNr = MNR_GHAEN;
		break;
	case VIEW_AMBLIE:
		nNr = MNR_AMBLIE;
		break;
	case VIEW_DCPREISAEND:
		nNr = MNR_DCPREISAEND;
		break;
	case VIEW_GALDATNEU:
		nNr = MNR_GALDATNEU;
		break;
	case VIEW_GALDATAH:
		nNr = MNR_GALDATAH;
		break;
	case VIEW_ELEKTROWART:
		nNr = MNR_ELEKTROWART;
		break;
	case VIEW_ELEKTRONEU:
		nNr = MNR_ELEKTRONEU;
		break;
	case VIEW_HERSTELLERCODE:
		nNr = MNR_HERSTELLERCODE;
		break;
	default:
		nNr = -1;
		break;
	}

	return nNr;
}


bool CMainFrame::TestAendern()
{
	bool bAendern;

	if ( m_bPflege && m_bBearbeiten )
	{
		int  nNr;
		nNr = GetMnrFromView( GetActViewNr( ) );

		if ( nNr == -1)
			bAendern = true;
		else
			bAendern = (( CEk1App *) AfxGetApp())->DarfMenuAendern( nNr );
	}
	else
		bAendern = false;
	return bAendern;
}

void CMainFrame::OnUpdateRecordSave(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable( TestAendern() && m_bSave );
	pCmdUI->Enable( FALSE );  /* hier immer FALSE */	
}

////////////////////////////////////////////////////////////////////////
// delete record

void CMainFrame::OnRecordDelete() 
{
	int status = - 1;
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL ) status = ActView->LoescheSatz( );
	if ( status != -1 )			// nichts tun bei -1
	{
		if ( status >= 1 ) 
		{
			m_bBearbeiten = false;
			m_bSearch = true;
		}
		if ( status != 2 )	// 2 = loeschen mit weiterblaettern	
		{
			ActView->CloseSuche();
			m_bNext = false;
			m_bPrev = false;
		}
	}	
}

void CMainFrame::OnUpdateRecordDelete(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable( TestAendern() && m_bDelete );	 
	pCmdUI->Enable( FALSE );  /* hier immer FALSE */
}

////////////////////////////////////////////////////////////////////////
// copy record

void CMainFrame::OnRecordCopy() 
{
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL )
		ActView->CopySatz( );
}

void CMainFrame::OnUpdateRecordCopy(CCmdUI* pCmdUI) 
{
//	 pCmdUI->Enable( m_bIsView ); 
	 pCmdUI->Enable( m_bPflege ); 	
}

////////////////////////////////////////////////////////////////////////
// cat record

void CMainFrame::OnRecordCut() 
{
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL )
		ActView->CutSatz( );	 
}

void CMainFrame::OnUpdateRecordCut(CCmdUI* pCmdUI) 
{
//	 pCmdUI->Enable( m_bIsView ); 
	 pCmdUI->Enable( m_bPflege ); 	
}

////////////////////////////////////////////////////////////////////////
// paste record

void CMainFrame::OnRecordPaste() 
{
	ChPflegeView* ActView = GetActView();
	if ( ActView != NULL )
		ActView->PasteSatz( );	
}

void CMainFrame::OnUpdateRecordPaste(CCmdUI* pCmdUI) 
{
//	 pCmdUI->Enable( m_bIsView ); 
	 pCmdUI->Enable( m_bPflege ); 		 
}


///////////////////////////////////////////////
// toggle between MS-standard and hajo-special

void CMainFrame::OnViewMsStandard() 
{
	m_bMSStandard = !m_bMSStandard;

	ChPflegeView* TempView;
	int i;
	for ( i = 0; i < m_nAnzViews; i++ )
	{
		if ( m_AllViews[i].nViewNr != VIEW_NO   &&
			 m_AllViews[i].nViewNr != VIEW_DEFAULT   )
		{
			TempView = ( ChPflegeView* )m_AllViews[i].pView;
			TempView->SetMSStandard( m_bMSStandard );
		}
	}	
}

void CMainFrame::OnUpdateViewMsStandard(CCmdUI* pCmdUI) 
{
	if ( m_bMSStandard )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
	
}

///////////////////////////////////////////////
// toggle between AutoQuestion yes / no

void CMainFrame::OnViewAutoFrage() 
{
	m_bAutoFrage = !m_bAutoFrage;	
}

void CMainFrame::OnUpdateViewAutoFrage(CCmdUI* pCmdUI) 
{
	if ( m_bAutoFrage )
		pCmdUI->SetCheck( 0 );
	else
		pCmdUI->SetCheck( 1 );		
}


/////////////////////////////////////////////////////////////////////////////
// DruckView Starten + Beenden 

LRESULT CMainFrame::OnDruckMessage( WPARAM wParam, LPARAM lParam )
{
	if ( wParam == 0 )
		OnRecordNew();
	else
		OnRecordUndo();
	return 0;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// spezielle View


///////////////////////////////////////////////////////////////////////////
// Rechte


void CMainFrame::OnViewRechte() 
{
	struct sDescription sMenPunkt[] =
	{
		{  MNR_ARTBLIE,  "Artikelliste Bestelladresse" },
		{  MNR_ARTHERS,  "Artikelliste Hersteller" },
		{  MNR_GHAEN,    "Liste GH auf \"nicht über GH\"" },	
		{  MNR_NEMWART,  "Liste NEM-Wechsel Artikel" },	
		{  MNR_NEMWLIE,  "Liste NEM-Wechsel Lieferant" },	
		{  MNR_ART7PROZ, "Liste Neuauf. verm. MWST" },	
		{  MNR_ARTSPERR, "Liste NEM-gesperrte Artikel" },	
		{  MNR_NONEMLIE, "Liste Lief. ohne NEM-Kennung" },
		{  MNR_INKONS,   "Liste inkons. NEM-Artikel" },
		{  MNR_PERHOEH,  "Liste Preiserhöhungen" },
		{  MNR_PERHABVK, "Liste Preiserhöhungen regional" },
		{  MNR_PSENKABVK, "Liste Preissenkungen regional" },
		{  MNR_AMBLIE,   "Liste AMB Lieferanten mit KZ ungleich A,B,C" },
		{  MNR_DCPREISAEND, "Liste wesentliche Preisänderungen" },
		{  MNR_GALDATNEU, "Liste LogIndex Neuanlagen ohne Artikelstamm" },
		{  MNR_GALDATAH,  "Liste LogIndex Änderungen AH und Differenz zu Artikelstamm" },
		{  MNR_ELEKTROWART,  "Liste Elektro-Wechsel Artikel" },
		{  MNR_ELEKTRONEU,  "Liste Neuaufnahmen Elektroartikel nicht registriert " },
		{  MNR_HERSTELLERCODE,  "Liste Hersteller nach Hersteller-Code" },
	};

	struct sDescription sRegion[] =
	{
		{  REGION_ZDP,  " " },
	};


	CRechteDlg	dlg;
	CEk1App* theApp = (CEk1App *)AfxGetApp();

	if ( dlg.Initialize( sMenPunkt, sizeof(sMenPunkt)/sizeof(struct sDescription),
					     sRegion,   sizeof(sRegion)/sizeof(struct sDescription),
						 THIS_PROGRAM_NUMBER, 
						 theApp->DarfSubSuperAnlegen( ),
						 theApp->GetUserName(),
						 theApp->GetLoginRechte(),
						 theApp->GetLoginRegion(),	
						 theApp->IsStandardEngine(),
						 theApp->GetDbaseName( ) ) )
	{
		dlg.DoModal( );
		// Rechte neu lesen 
		CString cErrmld;
		if ( !theApp->ReadUserRights( cErrmld ) )
			AfxMessageBox( cErrmld );
	}
	else
		AfxMessageBox( "Fehler beim Allokieren" );
	
}

void CMainFrame::OnUpdateViewRechte(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) &&
					(( CEk1App *) AfxGetApp())->DarfRechtePflegen() &&
					!m_bPflege );
}


/////////////////////////////////////////////////////////////////
// Artikelliste Bestelladresse

void CMainFrame::OnArtblie() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_ARTBLIE );
		m_bPflege  = TRUE;
	}						
}

void CMainFrame::OnUpdateArtblie(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_ARTBLIE ) &&
			//		 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_ARTBLIE ); 	
	
}


///////////////////////////////////////////////////////////////////
// Artiklelliste Hersteller

void CMainFrame::OnArthers() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_ARTHERS );
		m_bPflege  = TRUE;
	}						
}

void CMainFrame::OnUpdateArthers(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_ARTHERS ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_ARTHERS ); 	
}

///////////////////////////////////////////////////////////////////
// Nemwechsel Artiklel

void CMainFrame::OnNemwart() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_NEMWART );
		m_bPflege  = TRUE;
	}		
}

void CMainFrame::OnUpdateNemwart(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_NEMWART ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_NEMWART ); 		
}

void CMainFrame::OnNemwlie() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_NEMWLIE );
		m_bPflege  = TRUE;
	}	
}

void CMainFrame::OnUpdateNemwlie(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_NEMWLIE ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_NEMWLIE );	
}

void CMainFrame::OnArt7proz() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_ART7PROZ );
		m_bPflege  = TRUE;
	}		
}

void CMainFrame::OnUpdateArt7proz(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_ART7PROZ ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_ART7PROZ );		
}

void CMainFrame::OnArtsperr() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_ARTSPERR );
		m_bPflege  = TRUE;
	}			
}

void CMainFrame::OnUpdateArtsperr(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_ARTSPERR ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_ARTSPERR );		
}

void CMainFrame::OnNonemlie() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_NONEMLIE );
		m_bPflege  = TRUE;
	}		
}

void CMainFrame::OnUpdateNonemlie(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_NONEMLIE ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_NONEMLIE );		
}

void CMainFrame::OnInkons() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_INKONS );
		m_bPflege  = TRUE;
	}			
}

void CMainFrame::OnUpdateInkons(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_INKONS ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_INKONS );	
}

void CMainFrame::OnPerhoeh() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_PERHOEH );
		m_bPflege  = TRUE;
	}	
}

void CMainFrame::OnUpdatePerhoeh(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_PERHOEH ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_PERHOEH );		
}

void CMainFrame::OnPerhabvk() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_PERHABVK );
		m_bPflege  = TRUE;
	}		
}

void CMainFrame::OnUpdatePerhabvk(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_PERHABVK ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_PERHABVK );		
}

void CMainFrame::OnPsenkabvk() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_PSENKABVK );
		m_bPflege  = TRUE;
	}	
}

void CMainFrame::OnUpdatePsenkabvk(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_PSENKABVK ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_PSENKABVK );	
}

///////////////////////////////////////////////////////////
// GH - Kennzeichen auf "nicht ueber GH 

void CMainFrame::OnGhaen() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_GHAEN );
		m_bPflege  = TRUE;
	}			
}

void CMainFrame::OnUpdateGhaen(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_GHAEN ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_GHAEN ); 	
}

void CMainFrame::OnAmblief() 
{

	if ( CloseActView() == 0 )
	{
		SetView( VIEW_AMBLIE );
		m_bPflege  = TRUE;
	}	
}

void CMainFrame::OnUpdateAmblief(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_AMBLIE ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_AMBLIE );	

}


void CMainFrame::OnDcPreisaend()
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_DCPREISAEND );
		m_bPflege  = TRUE;
	}		
}
void CMainFrame::OnUpdateDcPreisaend(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->DarfMenuPflegen( MNR_DCPREISAEND ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_DCPREISAEND );	

}

void CMainFrame::OnGaldatNeu()
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_GALDATNEU );
		m_bPflege  = TRUE;
	}		
}
void CMainFrame::OnUpdateGaldatNeu(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->DarfMenuPflegen( MNR_GALDATNEU ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_GALDATNEU );	

}

void CMainFrame::OnGaldatAH()
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_GALDATAH );
		m_bPflege  = TRUE;
	}		
}
void CMainFrame::OnUpdateGaldatAH(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->DarfMenuPflegen( MNR_GALDATAH ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_GALDATAH );	

}
void CMainFrame::OnElektrowart()
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_ELEKTROWART );
		m_bPflege  = TRUE;
	}		
}

void CMainFrame::OnUpdateElektrowart(CCmdUI *pCmdUI)
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_ELEKTROWART ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_ELEKTROWART );			
}

void CMainFrame::OnElektroNeuaufn()
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_ELEKTRONEU );
		m_bPflege  = TRUE;
	}		
}

void CMainFrame::OnUpdateElektroNeuaufn(CCmdUI *pCmdUI)
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_ELEKTRONEU ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_ELEKTRONEU );			
}




void CMainFrame::OnHerstellerNachHerstellerCode()
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_HERSTELLERCODE );
		m_bPflege  = TRUE;
	}		

}

void CMainFrame::OnUpdateHerstellerNachHerstellerCode(CCmdUI *pCmdUI)
{
	 pCmdUI->Enable( (( CEk1App *) AfxGetApp())->IsConnected( ) && 
					 (( CEk1App *) AfxGetApp())->
								   DarfMenuPflegen( MNR_HERSTELLERCODE ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_HERSTELLERCODE );			
}

// MainFrm.cpp : Implementierung der Klasse CMainFrame
//

#include "stdafx.h"
#include "ZdpUtil.h"

#include "MainFrm.h"
#include "ViewNumbers.h"
#include "GetBranches.h"

#include "hPflegeView.h"
#include "RechteDlg.h"
#include "MenuNumbers.h"

#include "NewautidemView.h"
#include "GenfestbView.h"
#include "UpdateFromExcelView.h"
#include "ReadProtoView.h"

#include "DruckView.h"

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
	ON_COMMAND(ID_NEWAUTIDEM, OnNewautidem)
	ON_UPDATE_COMMAND_UI(ID_NEWAUTIDEM, OnUpdateNewautidem)
	ON_COMMAND(ID_UPD_ZARTIKEL, OnExcel)
	ON_UPDATE_COMMAND_UI(ID_UPD_ZARTIKEL, OnUpdateExcel)
	ON_COMMAND(ID_GENFESTB, OnGenfestb)
	ON_UPDATE_COMMAND_UI(ID_GENFESTB, OnUpdateGenfestb)
	ON_COMMAND(ID_UTILITIES_PROTOKOLL, OnReadProto)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_PROTOKOLL, OnUpdateReadProto)

	//}}AFX_MSG_MAP

	//TH - neuer View

	ON_CBN_SELCHANGE(IDS_TB_COMBO_0, OnComboChange_0)
	ON_CBN_SELCHANGE(IDS_TB_COMBO_1, OnComboChange_1)

	ON_MESSAGE( IDD_DRUCK, OnDruckMessage )

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // Statusleistenanzeige
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Konstruktion/Zerstörung

CMainFrame::CMainFrame()
{
	// ZU ERLEDIGEN: Hier Code zur Member-Initialisierung einfügen

	theApp = ((CZdpUtilApp*)AfxGetApp());

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
		font.Attach(::GetStockObject(DEVICE_DEFAULT_FONT));

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME,
								  cb, sizeof( cb )/sizeof( struct CTB_COMBO),
						  		  &font ) )
	{
		TRACE0("Failed to create toolbar\n");
		return false;      // fail to create
	}

	m_TbCbSonst = m_wndToolBar.GetRefToComboBox( 0 );

	m_TbCbSonst->AddString("ZDPUtil");
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
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.
	return TRUE;
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
		theApp->SetCurrentBranch( nSel );	
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
	CString NewVersion = "Toolbar-01";
	CString OldVersion = "Toolbar-00";
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
// CMainFrame Diagnose

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
	InsertView( VIEW_DEFAULT  , "ZDPUtil",	GetActiveView() );

	InsertView( VIEW_NEWAUTIDEM,  "Neue AUTIDEM-Artikel",   
							       new CNewautidemView( ) );
	InsertView( VIEW_GENFESTB,    "IFA-Lieferung 'Festbetrag' generieren",   
							       new CGenfestbView( ) );	
	//InsertView( VIEW_GENFESTB,    "IFA-Lieferung 'Festbetrag' generieren",   
	//						       new CGenfestbView( ) );
	InsertView( VIEW_UPD_FROM_EX,    "Update aus Excel-Datei",   
							       new CUpdateFromExcelView( ) );
	InsertView( VIEW_READ_PROTO,   "Protokoll-Dateien von Update aus Excel anzeigen",   
							       new CReadProtoView( ) );

	//TH - neuer View
	InsertView( VIEW_DRUCK,     "Drucken",   
							    new CDruckView( VIEW_DRUCK ) );
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

void CMainFrame::SetConnectinfoToView()		// Anmeldeprozedur
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
		cStr = _T("[") + theApp->GetDbaseName();
		cStr.TrimRight();
		cStr += _T("@") + theApp->GetServerName();
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
		cStr = _T(" [") + theApp->GetDbaseName();
		cStr.TrimRight();
		cStr += _T("@") + theApp->GetServerName();
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
	case VIEW_NEWAUTIDEM:
		nNr = MNR_NEWAUTIDEM;
		break;
	case VIEW_GENFESTB:
		nNr = MNR_GENFESTB;
		break;
	case VIEW_UPD_FROM_EX:
		nNr = MNR_UPD_FROM_EX;
		break;
	default:
		nNr = -1;
		break;
	}
//TH - neuer View
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
			bAendern = theApp->DarfMenuAendern( nNr );
	}
	else
		bAendern = false;
	return bAendern;
}

void CMainFrame::OnUpdateRecordSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( TestAendern() && m_bSave );
//	pCmdUI->Enable( FALSE );  /* hier immer FALSE */	
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
		{  MNR_NEWAUTIDEM,   "Neue AUTIDEM-Artikel" },
		{  MNR_GENFESTB,     "FestbetragsLieferung IFA generieren" },
		{  MNR_UPD_FROM_EX,  "Update aus Excel" },
	};
	//TH - neuer View

	struct sDescription sRegion[] =
	{
		{  REGION_ZDP,  " " },
	};


	CRechteDlg	dlg;

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
	pCmdUI->Enable( theApp->IsConnected( ) &&
					theApp->DarfRechtePflegen() &&
					!m_bPflege );
}



/////////////////////////////////////////////////////////////////
// New AutIdem

void CMainFrame::OnNewautidem() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_NEWAUTIDEM );
		m_bPflege  = TRUE;
	}	
}

void CMainFrame::OnUpdateNewautidem(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( theApp->IsConnected( ) && 
					 theApp->DarfMenuPflegen( MNR_NEWAUTIDEM  ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_NEWAUTIDEM  );		
}


/////////////////////////////////////////////////////////////////
// Festbetraege generieren

void CMainFrame::OnGenfestb() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_GENFESTB );
		m_bPflege  = TRUE;
	}	
}

void CMainFrame::OnUpdateGenfestb(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( theApp->IsConnected( ) && 
					 theApp->DarfMenuPflegen( MNR_GENFESTB  ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_GENFESTB  );			
}

/////////////////////////////////////////////////////////////////
// Update ZArtikel aus Excel

void CMainFrame::OnExcel() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_UPD_FROM_EX );
		m_bPflege  = TRUE;
	}	
}

void CMainFrame::OnUpdateExcel(CCmdUI* pCmdUI) 
{
	 pCmdUI->Enable( theApp->IsConnected( ) && 
					 theApp->DarfMenuPflegen( MNR_UPD_FROM_EX  ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_UPD_FROM_EX  );			
}

/////////////////////////////////////////////////////////////////
// zputil-Protokoll anzeigen (cdm/data/zputil/...)

void CMainFrame::OnReadProto() 
{
	if ( CloseActView() == 0 )
	{
		SetView( VIEW_READ_PROTO );
		m_bPflege  = TRUE;
	}	
}

void CMainFrame::OnUpdateReadProto(CCmdUI* pCmdUI) 
{
	// user should have the same rights for MNR_READ_PROTO as for MNR_UPD_FROM_EX
	// so no additional right has to be implemented for this menu in rights dialog

	 pCmdUI->Enable( theApp->IsConnected( ) && 
					 theApp->DarfMenuPflegen( MNR_UPD_FROM_EX  ) &&
				//	 !m_bBearbeiten &&
					 !m_bIsDruck &&
					 GetActViewNr( ) != VIEW_READ_PROTO  );			
}
//TH - neuer View

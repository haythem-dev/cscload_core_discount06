// ArtnameView.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtnameView.h"

#include "hSelectDialog.h"
#include <phxlib/DformSelCtrl.h>

#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskNum.h>
#include "FeldBreite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtnameView

IMPLEMENT_DYNCREATE(CArtnameView, CFormViewMultiLang)

CArtnameView::CArtnameView()
	: ChPflegeView(CArtnameView::IDD)
{
	//{{AFX_DATA_INIT(CArtnameView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_nLines = 0;
	m_nColumns = 0;
	m_nActualLines = 0;

	int i;
	int j;
	for ( i = 1; i < ANZ_LINES; i++ )
		for ( j = 0; j < ANZ_COLUMNS; j++ )
		{
			m_cEdit[i][j] = NULL;// created in CArtnameView::MakeDialog()
		}
}

CArtnameView::~CArtnameView()
{
	int i;
	int j;
	
	for ( i = 1; i < ANZ_LINES; i++ )
		for ( j = 0; j < ANZ_COLUMNS; j++ )
		{
			if ( m_cEdit[i][j] != NULL )
				delete m_cEdit[i][j]; // created in CArtnameView::MakeDialog()
		}
}

void CArtnameView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtnameView)
	DDX_Control(pDX, IDC_ED_ARTNAME_SEKBEZ_1, m_cSEKBEZ_1);
	DDX_Control(pDX, IDC_ED_ARTNAME_GESPERRT_1, m_cGESPERRT_1);
	DDX_Control(pDX, IDC_ED_ARTNAME_EINHEIT_1, m_cEINHEIT_1);
	DDX_Control(pDX, IDC_ED_ARTNAME_DFORM_1, m_cDFORM_1);
	DDX_Control(pDX, IDC_ED_ARTNAME_ARTIKEL_NR_1, m_cARTIKEL_NR_1);
	DDX_Control(pDX, IDC_ED_ARTNAME_ARTIKEL_CODE, m_cARTIKEL_CODE);
	DDX_Control(pDX, IDC_ED_ARTNAME_ARTIKEL_NAME_1, m_cARTIKEL_NAME_1);
	DDX_Control(pDX, IDC_ED_ARTNAME_DFORM_2, m_cDFORM_2);
	DDX_Control(pDX, IDC_ED_ARTNAME_ARTIKEL_NAME_2, m_cARTIKEL_NAME_2);
	DDX_Control(pDX, IDC_ED_ARTNAME_EINHEIT_2, m_cEINHEIT_2);
	DDX_Control(pDX, IDC_ED_ARTNAME_SUCHB, m_cSUCHB);
	DDX_Control(pDX, IDC_ST_ARTNAME_HERST_NR, m_ST_HERST_NR);
	//}}AFX_DATA_MAP
/*
	if ( m_nLines > 0 )
	{
		DDX_Control(pDX, IDC_ED_ARTNAME_EINHEIT_1,      *m_cEdit[0][0] );
		DDX_Control(pDX, IDC_ED_ARTNAME_ARTIKEL_NAME_1, *m_cEdit[0][1] );
		DDX_Control(pDX, IDC_ED_ARTNAME_DFORM_1,        *m_cEdit[0][2] );
		DDX_Control(pDX, IDC_ED_ARTNAME_SEKBEZ_1,       *m_cEdit[0][3] );
		DDX_Control(pDX, IDC_ED_ARTNAME_ARTIKEL_NR_1,   *m_cEdit[0][4] );
		DDX_Control(pDX, IDC_ED_ARTNAME_GESPERRT_1,     *m_cEdit[0][5] );
	}
*/
	int i;
	int j;
	int idc = IDC_BASE + ANZ_COLUMNS;
	for ( i = 1; i < m_nLines; i++ )
		for ( j = 0; j < m_nColumns; j++ )
			DDX_Control(pDX, idc++, *m_cEdit[i][j] );

}


BEGIN_MESSAGE_MAP(CArtnameView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CArtnameView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArtnameView diagnostics

#ifdef _DEBUG
void CArtnameView::AssertValid() const
{
	CFormViewMultiLang::AssertValid();
}

void CArtnameView::Dump(CDumpContext& dc) const
{
	CFormViewMultiLang::Dump(dc);
}
#endif //_DEBUG


////////////////////////////////////////////////
// Verknuepfung + Validierung

class CV_ARTNAME_Artikelname : public ChValBase
{
public:
	CV_ARTNAME_Artikelname( CArtnameView* pView, ChDlgEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
//		((ChDlgEdit*)m_pWnd1)->p_GetInput();
		char *pArtikelname;
		pArtikelname = (char *)(((ChDlgEdit*)m_pWnd1)->PointerToBuffer( ));
		BOOL bOk = *pArtikelname != ' ';
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_NO_SPACE_BEGIN) );
		return bOk;
	}
};

class CV_ARTNAME_Artikelname2 : public ChValBase
{
public:
	CV_ARTNAME_Artikelname2( CArtnameView* pView, ChDlgEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL )
	{
//		((ChDlgEdit*)m_pWnd1)->p_GetInput();
		char *pArtikelname;
		pArtikelname = (char *)(((ChDlgEdit*)m_pWnd1)->PointerToBuffer( ));
		/*BOOL bOk = *pArtikelname != ' ';
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_NO_SPACE_BEGIN) );
		return bOk;
		*/
		return true;
	}
};

BOOL CArtnameView::ShowDform( ChDlgEdit *pEdit, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	char *pDform;
	pDform = (char *)(pEdit->PointerToBuffer( ));
	iStat = m_RD_DFORM.IPlausi( pDform, Name, &Errmld);
	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtnameView::SucheDform( ChDlgEdit *pEdit )
{
	CDformSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_SEL_DAR), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		char *pDform;
		pDform = (char *)(pEdit->PointerToBuffer( ));
		if ( m_SelBox.PrimeKeyOfSelectedRecord( pDform ) == 0 )
		{

			pEdit->p_SetInput();
			pEdit->SetFocus();
		}
	}
	m_SelBox.CloseCursor();
}

class CV_ARTNAME_Dform : public ChValBase
{
public:
	CV_ARTNAME_Dform( CArtnameView* pView, ChDlgEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtnameView*)m_pWnd)->ShowDform( (ChDlgEdit*)m_pWnd1, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtnameView*)m_pWnd)->SucheDform( (ChDlgEdit*)m_pWnd1 );
	}
};

class CV_ARTNAME_Dform2 : public ChValBase
{
public:
	CV_ARTNAME_Dform2( CArtnameView* pView, ChDlgEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtnameView*)m_pWnd)->ShowDform( (ChDlgEdit*)m_pWnd1, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtnameView*)m_pWnd)->SucheDform( (ChDlgEdit*)m_pWnd1 );
	}
};
/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtnameView::MakeDialog( )
{
	// m_dld wird dynamisch generiert

	// Generierung zeilenweise wegen Tab Order

	m_cEdit[0][0] = &m_cEINHEIT_1;
	m_cEdit[0][1] = &m_cARTIKEL_NAME_1;
	m_cEdit[0][2] = &m_cDFORM_1;
	m_cEdit[0][3] = &m_cSEKBEZ_1;
	m_cEdit[0][4] = &m_cARTIKEL_NR_1;
	m_cEdit[0][5] = &m_cGESPERRT_1;
	m_cEdit[0][6] = &m_cEINHEIT_2;
	m_cEdit[0][7] = &m_cARTIKEL_NAME_2;
	m_cEdit[0][8] = &m_cDFORM_2;
	m_cEdit[0][9] = &m_cARTIKEL_CODE;

	ChDlgEdit *pNewWnd;
	int i;
	int j;
	int idc;
	
	idc = IDC_BASE + ANZ_COLUMNS;

	for ( i = 1; i < ANZ_LINES; i++ )
		for ( j = 0; j < ANZ_COLUMNS; j++ )
		{
			pNewWnd = new ChDlgEdit;
			m_cEdit[i][j] = pNewWnd;
			GenEditFeld( pNewWnd, idc++, m_cEdit[i-1][j] );
		}

	m_nLines   = ANZ_LINES;
	m_nColumns = ANZ_COLUMNS;

	m_cSUCHB.SetMask (ED_CHAR,
			          ED_UPPER,
			 		  50,
					  new ChMaskChar );
	m_cSUCHB.SetDialog( TRUE );


	for ( i = 0; i < ANZ_LINES; i++ )
	{
		m_cEdit[i][NR_EINHEIT]->SetMask(ED_CHAR,
							   	        ED_UPPER | ED_RIGHT,
									    m_pBuf[i]->EINHEIT,
									    L_ZARTIKEL_EINHEIT,
									    new ChMaskChar );
		m_cEdit[i][NR_EINHEIT]->SetDialog( TRUE );

		m_cEdit[i][NR_ARTIKEL_NAME]->SetMask(ED_CHAR,
									         ED_UPPER,
									         m_pBuf[i]->ARTIKEL_NAME,
									         L_ZARTIKEL_ARTIKEL_NAME,
									         new ChMaskChar,
											 new CV_ARTNAME_Artikelname( this,
																	     m_cEdit[i][NR_ARTIKEL_NAME] ) );

		m_cEdit[i][NR_ARTIKEL_NAME]->SetDialog( TRUE );

		m_cEdit[i][NR_DFORM]->SetMask(ED_CHAR,
							   	      ED_UPPER,
									  m_pBuf[i]->DARREICHFORM,
									  L_ZARTIKEL_DARREICHFORM,
									  new ChMaskChar,
									  new CV_ARTNAME_Dform( this,
									 					    m_cEdit[i][NR_DFORM] ) );

		m_cEdit[i][NR_DFORM]->SetDialog( TRUE );

		m_cEdit[i][NR_SEKBEZ]->SetMask(ED_CHAR,
							   	       ED_UPPER,
									   m_pBuf[i]->HAT_SEKBEZ,
									   1,
									   new ChMaskChar );
		m_cEdit[i][NR_SEKBEZ]->SetDialog( TRUE );

		m_cEdit[i][NR_ARTIKEL_CODE]->SetMask(	ED_CHAR,
												ED_UPPER,
												m_ARTCODE,
												L_CARTICLECODES_ARTICLE_CODE,
												new ChMaskChar);
		m_cEdit[i][NR_ARTIKEL_CODE]->SetDialog( TRUE );
		m_cEdit[i][NR_ARTIKEL_CODE]->EnableWindow( FALSE );

		m_cEdit[i][NR_ARTIKEL_NR]->SetMask(ED_LONG,
										   ED_NORMAL,
									       &m_pBuf[i]->ARTIKEL_NR,
									       L_ARTIKEL_NR,
									       new ChMaskNum );
		m_cEdit[i][NR_ARTIKEL_NR]->SetDialog( TRUE );
		m_cEdit[i][NR_ARTIKEL_NR]->EnableWindow( FALSE );

		m_cEdit[i][NR_GESPERRT]->SetMask(ED_CHAR,
							   	       ED_UPPER,
									   m_pBuf[i]->ARTIKEL_GESPERRT,
									   L_ZARTIKEL_ARTIKEL_GESPERRT,
									   new ChMaskChar );
		m_cEdit[i][NR_GESPERRT]->SetDialog( TRUE );
		m_cEdit[i][NR_GESPERRT]->EnableWindow( FALSE );
		
		m_cEdit[i][NR_EINHEIT2]->SetMask(ED_CHAR,
							   	        ED_UPPER | ED_RIGHT,
									    m_pBuf[i]->PACKAGINGUNIT,
									    L_CARTICLELANG_PACKAGINGUNIT,
									    new ChMaskChar );
		m_cEdit[i][NR_EINHEIT2]->SetDialog( TRUE );

		m_cEdit[i][NR_ARTIKEL_NAME2]->SetMask(ED_CHAR,
									         ED_UPPER,
									         m_pBuf[i]->ARTICLENAME,
									         L_CARTICLELANG_ARTICLENAME,
									         new ChMaskChar,
											 new CV_ARTNAME_Artikelname2( this,
																	     m_cEdit[i][NR_ARTIKEL_NAME2] ) );

		m_cEdit[i][NR_ARTIKEL_NAME2]->SetDialog( TRUE );

		m_cEdit[i][NR_DFORM2]->SetMask(ED_CHAR,
							   	      ED_UPPER,
									  m_pBuf[i]->PHARMAFORM,
									  L_CARTICLELANG_PHARMAFORM,
									  new ChMaskChar,
									  new CV_ARTNAME_Dform2( this,
									 					    m_cEdit[i][NR_DFORM2] ) );

		m_cEdit[i][NR_DFORM2]->SetDialog( TRUE );



	}

}

//////////////////////////////////////////////////
// Pflege

void CArtnameView::InitPflege()
{

	int k;
	for ( k = 0; k < ANZ_LINES; k++ )
	{
		m_pBuf[k]	 = m_Doc.GetBuffer( k );
		m_pBufOld[k] = m_Doc.GetOldBuffer( k );
	}

	m_bPrev = FALSE;
	m_bNext = FALSE;
	
	MakeDialog();
}

// Generiert ein Editfeld nach darueberliefendem Muster

// Ermittelt den aktuellen Font und uebergibt ihn an das ControlFeld

void CArtnameView::GenFont( CWnd *pWnd )
{
	CWnd* m_pWndParent = this;
	CFont* pDlgFont = (CFont*)m_pWndParent->GetFont();
	pWnd->SetFont(pDlgFont);
}

void CArtnameView::CalcRect( CWnd *TopMuster, CRect *NewRect )
{
//	CRect FrameRect;
//	this->GetWindowRect(FrameRect);
	CRect TopRect;
	TopMuster->GetWindowRect( TopRect );

	int nWidth,  nHeigh;
	nWidth  = TopRect.right  - TopRect.left;
	nHeigh  = TopRect.bottom - TopRect.top;
/*
	NewRect->left  = TopRect.left - FrameRect.left;
	NewRect->top   = TopRect.top + 3*nHeigh/2 - FrameRect.top;

	NewRect->right  = NewRect->left + nWidth;
	NewRect->bottom = NewRect->top  + nHeigh;
*/
	NewRect->left  = TopRect.left;
	NewRect->top   = TopRect.top + 6*nHeigh/5;

	NewRect->right  = NewRect->left + nWidth;
	NewRect->bottom = NewRect->top  + nHeigh;
	ScreenToClient( NewRect );
}


BOOL CArtnameView::GenEditFeld( CEdit *pWnd, int idc, CEdit *pWndTop )
{
	BOOL bOk;
	CRect rect;

	CalcRect( pWndTop, &rect );

	bOk = pWnd->Create( pWndTop->GetStyle(),
					    rect,					 
						this,					
						idc );			// !!!!!!!!!!!! IDC !!!!!!!!!!!!!
	if ( bOk )
	{
		GenFont ( pWnd );
		pWnd->ModifyStyleEx( 0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME );
		pWnd->ShowWindow( SW_SHOW );	
	}
	return bOk;
}

///////////////////////////////////////////
// Steuerung

void CArtnameView::SetMSStandard( BOOL bStandard )
{   
	int i;
	int j;
	for ( i = 0; i < m_nLines; i++ )
		for ( j = 0; j < m_nColumns; j++ )
			m_cEdit[i][j]->SetMSStandard( bStandard );
}

void CArtnameView::ShowFields( )
{
	int i;
	int j;
	for ( i = 0; i < m_nLines; i++ )
		for ( j = 0; j < m_nColumns; j++ ){
			m_cEdit[i][j]->p_SetInput();
			if ( j == NR_ARTIKEL_NR ){
				CString s;
				(*m_cEdit[i][j]).GetWindowText(s);
				SetArticleCodeEditCtrl( *m_cEdit[i][j], *m_cEdit[i][NR_ARTIKEL_CODE] );
			}
		}
}


void CArtnameView::DataExchangeToBuffer( )
{
	int i;
	int j;
	for ( i = 0; i < m_nLines; i++ )
		for ( j = 0; j < m_nColumns; j++ )
			m_cEdit[i][j]->p_GetInput();

}


BOOL CArtnameView::Validate( )
{

	int i;
	int j;
	SetValidation( FALSE );
	for ( i = 0; i < m_nActualLines; i++ )
		for ( j = 0; j < m_nColumns; j++ )
		{
			if ( !m_cEdit[i][j]->Validate( TRUE ) )
			{
				SetValidation( TRUE );
				m_cEdit[i][j]->SetFocus( );
				return FALSE;
			}
		}
	SetValidation( TRUE );
	return TRUE;
}


void CArtnameView::SetValidation( BOOL bValid )
{
	int i;
	int j;
	for ( i = 0; i < m_nLines; i++ )
		for ( j = 0; j < m_nColumns; j++ )
			m_cEdit[i][j]->SetValidation( bValid );
}

void CArtnameView::SetArticleCodeEditCtrl( ChDlgEdit& noEdit, ChDlgEdit& codeEdit )
{
	CArticleCodesConverter::setPreferredArticleCodeEditCtrl( noEdit, codeEdit ); 
}

void CArtnameView::EnableLines( int toLine )
{
	int i;
	int j;

	for ( i = 0; i < toLine; i++ )
	{
		for ( j = 0; j < m_nColumns; j++ )
		{
			if ( !( j == NR_ARTIKEL_NR || j == NR_GESPERRT || j == NR_ARTIKEL_CODE ) )
				m_cEdit[i][j]->EnableWindow( TRUE );

			if (!IsCountry("CH") &&
				!IsCountry("BG") &&
			   ((j == NR_EINHEIT2) || (j == NR_ARTIKEL_NAME2) || (j == NR_DFORM2))) 
				m_cEdit[i][j]->EnableWindow( FALSE );
		}
	}

	for ( i = toLine; i < m_nLines; i++ )
	{
		for ( j = 0; j < m_nColumns; j++ )
		{
			if ( !( j == NR_ARTIKEL_NR || j == NR_GESPERRT || j == NR_ARTIKEL_CODE ) ){
				m_cEdit[i][j]->EnableWindow( FALSE );
			}
			else if ( j == NR_ARTIKEL_NR ){
				m_cEdit[i][j]->ShowWindow(SW_HIDE);
			}
		}
	}

	m_nActualLines = toLine;
}


////////////////////////////////////////////////////////////
// Suchbox

int CArtnameView::CloseSuche( )
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////
// Antwort auf Bearbeitungskommandos

int CArtnameView::SucheSatz( )
{
	long s = 0;
	int suchen;
	int anz = 0;
	CString SuchBegriff;
	CString cErrmld;

	m_bPrev = FALSE;
	m_bNext = FALSE;

	m_cSUCHB.GetWindowText( SuchBegriff );
	SuchBegriff.TrimLeft();
	SuchBegriff.TrimRight();

	if (SuchBegriff.GetAt( 0 ) == '#')
	{
		int iHersteller_nr = atoi (SuchBegriff.Mid(1));
		if (!ShowHersteller (iHersteller_nr, cErrmld))
		{
			s = -1;
		}
	}
	else
	{
		m_ST_HERST_NR.SetWindowText( "" );
	}

	if ( s == 0 )
		s = m_Doc.StartSuche( SuchBegriff, &anz, cErrmld );

	if ( s == 0 )
	{
		suchen = -1;
		( ( CEkZdpApp *) AfxGetApp() )->SetMenue( 1, -1, 1, 1, -1 );;
		EnableLines( anz );
		ShowFields();
		m_cEINHEIT_1.SetFocus();
	}
	else
	{
		MsgBoxOK( cErrmld );
		suchen = 0;
		( ( CEkZdpApp *) AfxGetApp() )->SetMenue( -1, -1, 1, -1, -1 );
		EnableLines( 0 );
		ShowFields();
		m_cSUCHB.SetFocus( );
	}
	return suchen;
}

int CArtnameView::NextSatz( )
{
	long s;
	int anz;
	CString cErrmld;

	s = m_Doc.NextSuche( &anz, cErrmld );
	if ( s != 0 )
	{
		MsgBoxOK( cErrmld );
		m_bNext = FALSE;
		return 0;
	}
	if ( anz == 0 )
	{ 
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING48) );
		m_bNext = FALSE;
		return 0;
	}
	ShowFields();
	EnableLines( anz );
	m_cEINHEIT_1.SetFocus( );
	return -1;  // nichts tun
}


int CArtnameView::PrevSatz( )
{
	return -1;
}


int CArtnameView::BearbeiteSatz( )
{
	if ( GetFocus() == &m_cSUCHB )
	{
		SucheSatz( );
	}
	else
		((CDialogMultiLang*) this)->NextDlgCtrl( );  // !!!!!!!!!!!!!!!!!!!!
	return 0;
}

int CArtnameView::SpeichereSatz( )
{

	DataExchangeToBuffer( );

	if ( !Validate() ) return -1;

	if ( ! (( CEkZdpApp *)AfxGetApp())->YouWantToStoreRecord( ) ) return -1;

	CString cErrmld;
	long lStatus;
	int  ind;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.StoreRecord( &ind,cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
	if ( lStatus == 0 )
	{
		m_bChanged = TRUE;
		m_nStatus = 0;
		return -1;	// hier nichts machen
	}
	MsgBoxOK( cErrmld );
	return 0;
}
	

int CArtnameView::LoescheSatz( )
{
	return -1;
}

int CArtnameView::UndoSatz( )
{
	if ( GetFocus() == &m_cSUCHB )
	{
		SetValidation( FALSE );
		m_Doc.FreeBufferDesc( );
		CloseSuche();
		m_bPrev = FALSE;
		m_bNext = FALSE;
		return 0;
	}
	else
	{
		SetValidation( FALSE );
		m_cSUCHB.SetFocus( );
		SetValidation( TRUE );
		return 2;
	}
}

void CArtnameView::InitPflegeDocument( char* Anwender )
{
	m_Doc.InitPflegeDesc( Anwender );
}

void CArtnameView::ReleasePflegeDocument( )
{
}

/////////////////////////////////////////////////////////////////////////////
// CArtnameView message handlers

void CArtnameView::OnInitialUpdate() 
{

	CFormViewMultiLang::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	InitPflege();
	m_Doc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	m_nStatus = 0;
}


void CArtnameView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class

	CFormViewMultiLang::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
		if ( pActivateView != pDeactiveView )
		{
			SetValidation( FALSE );
			EnableLines( 0 );
			m_bChanged = FALSE;  // noch keine Aenderung
			m_nStatus = 0;
			m_Doc.InitArtnameBuffer( 0 );

			ShowFields();
			m_cSUCHB.SetFocus( );
			SetValidation( TRUE );
		}
	}
}

BOOL CArtnameView::ShowHersteller( int iHersteller_nr, CString &cErrmld )
{
	int iStat;
	CString Name;
	CString Errmld;
	CString PPE;

	iStat = m_RD_HERSTELLER.IPlausi( iHersteller_nr, Name, PPE,
									 &Errmld);

	m_ST_HERST_NR.SetWindowText( Name );

	if (iStat > 0)
		cErrmld = Errmld;

	return iStat == 0;
}

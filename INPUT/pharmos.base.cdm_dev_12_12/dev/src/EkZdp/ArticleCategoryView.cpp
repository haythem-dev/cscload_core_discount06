// ArticleCategoryView.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArticleCategoryView.h"
#include "ServerDatum.h"

#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskNum.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArticleCategoryView

IMPLEMENT_DYNCREATE(CArticleCategoryView, CFormViewMultiLang)

CArticleCategoryView::CArticleCategoryView()
	: ChPflegeView(CArticleCategoryView::IDD)
{
	//{{AFX_DATA_INIT(CArticleCategoryView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CArticleCategoryView::~CArticleCategoryView()
{
}

void CArticleCategoryView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArticleCategoryView)
	DDX_Control(pDX, IDC_ED_ARTICLECATEGORY_CATEGORYNO, m_CATEGORY_NO);
	DDX_Control(pDX, IDC_ED_ARTICLECATEGORY_NAME, m_NAME);
	DDX_Control(pDX, IDC_ED_ARTICLECATEGORY_SQL, m_SQL);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CArticleCategoryView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CArticleCategoryView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArticleCategoryView::MakeDialog()
{
	m_Pos_FirstKey = m_Pos_LastKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_CATEGORY_NO );

	m_Pos_FirstField = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_NAME );

	m_dlg.InitDialog( m_SQL );

	m_nMaxFields = m_dlg.GetFieldNumber();	
}

/////////////////////////////////////////////////////////////////////////////
// CArticleCategoryView diagnostics

#ifdef _DEBUG
void CArticleCategoryView::AssertValid() const
{
	CFormViewMultiLang::AssertValid();
}

void CArticleCategoryView::Dump(CDumpContext& dc) const
{
	CFormViewMultiLang::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////
//  Validierung

class CV_ARTICLECATEGORY_Category_no : public ChValBase
{
public:
	CV_ARTICLECATEGORY_Category_no( struct CARTICLECATEGORY* pBuf ) : ChValBase( pBuf ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		long category_no;

		category_no = ((struct CARTICLECATEGORY*)m_pBuf)->ARTCATEGORYNO;
		bOk = category_no != 0; 
		if ( !bOk && bMeldung )
			AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING1075) );

		return bOk; 
	}
};

class CV_ARTICLECATEGORY_Name : public ChValBase
{
public:
	CV_ARTICLECATEGORY_Name( struct CARTICLECATEGORY* pBuf ) : ChValBase( pBuf ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = (( struct CARTICLECATEGORY*)m_pBuf)->NAME[0] != ' ';
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING42) );
		return bOk;
	}
};

/////////////////////////////////////////////////////////////
//  Dialogfelder

void CArticleCategoryView::InitPflege()
{
	MakeDialog();

	struct CARTICLECATEGORY *m_Buf;
	m_Buf = m_Doc.GetBuffer();

	m_CATEGORY_NO.SetMask (ED_LONG,
                           ED_NORMAL,
                           &m_Buf->ARTCATEGORYNO,
                           5,
                           new ChMaskNum,
						   new CV_ARTICLECATEGORY_Category_no( m_Buf ) );

	m_NAME.SetMask		  (ED_CHAR,
                           ED_UPPER,
                           m_Buf->NAME,
                           L_CARTICLECATEGORY_NAME,
                           new ChMaskChar,
    					   new CV_ARTICLECATEGORY_Name( m_Buf ) ); 

	m_SQL.SetMask		  (ED_CHAR,
                           ED_UPPER,
                           m_Buf->SQL_STATEMENT,
                           L_CARTICLECATEGORY_SQL_STATEMENT,
                           new ChMaskChar ); 

	EnableFields( FALSE );
	SetDialog();
}

void CArticleCategoryView::DisableSpecial()
{
	// dummy
}

void CArticleCategoryView::ShowSpecial()
{
	// dummy
}

////////////////////////////////////////////////////////////
// Suchbox

ChSelectDialog* CArticleCategoryView::NewSuchDialog()
{
	return new ChSelectDialog ( CResString::ex().getStrTblText(IDS_STRING1069), &m_SelBox,
								HCD_SCROLLINFO );
							//	HCD_SCROLLINFO | HCD_BUTTONALTERN );
}

BOOL CArticleCategoryView::PrimeKeyOfSelectedRecord( )
{ 
	return m_SelBox.PrimeKeyOfSelectedRecord( &m_Doc.GetBuffer()->ARTCATEGORYNO ) == 0;
}

BOOL CArticleCategoryView::PrimeKeyOfNextRecord( )
{
	return m_SelBox.PrimeKeyOfNextRecord( &m_Doc.GetBuffer()->ARTCATEGORYNO ) == 0;
}

BOOL CArticleCategoryView::PrimeKeyOfPrevRecord( )
{
	return m_SelBox.PrimeKeyOfPrevRecord( &m_Doc.GetBuffer()->ARTCATEGORYNO ) == 0;
}

int CArticleCategoryView::CloseSuche( )
{
	m_SelBox.CloseCursor();
	return 0;
}


////////////////////////////////////////////////////////////////
// Rest kann kopiert werden
////////////////////////////////////////////////////////////////

void CArticleCategoryView::SetDialog( BOOL bDialog )
{   
 	m_dlg.SetDialog( bDialog );
}

void CArticleCategoryView::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArticleCategoryView::EnableFields( BOOL bEnab )
{
	m_dlg.EnableFields( m_Pos_FirstKey, m_Pos_LastKey, !bEnab );
	m_dlg.EnableFields( m_Pos_FirstField, m_nMaxFields - 1, bEnab );

	// SQL-Statement kann nicht vom Anwender gepflegt werden
	m_SQL.EnableWindow(false);

	DisableSpecial();
}

void CArticleCategoryView::ShowFields( )
{
	m_dlg.ShowFields();

	ShowSpecial();
}

void CArticleCategoryView::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArticleCategoryView::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

BOOL CArticleCategoryView::Validate( )
{
	int i;
	BOOL bOk = TRUE;
	SetValidation( FALSE );
	i = m_Pos_FirstField;
	while ( i < m_nMaxFields && bOk )
	{
		bOk = m_dlg.Validate( i, TRUE );
		if ( bOk ) i++;
	}
	if ( !bOk ) m_dlg.SetFocus( i );
	SetValidation( TRUE );
	return bOk;
}

BOOL CArticleCategoryView::ValidateKey( )
{
	return m_dlg.Validate( m_Pos_FirstKey, TRUE );
}

BOOL CArticleCategoryView::IsLastKeyFocus( )
{
	return GetFocus() == GetDlgItem( IDC_LAST_KEY );
}

// Steuerung

void CArticleCategoryView::GotoFirstKey()
{
	SetValidation( FALSE );	
	m_dlg.SetFocus( m_Pos_FirstKey );
}

void CArticleCategoryView::GotoFirstField()
{
	m_dlg.SetFocus( m_Pos_FirstField );
	SetValidation( TRUE );	
}

void CArticleCategoryView::KeyGetInput()
{
	m_dlg.DataExchangeToBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

void CArticleCategoryView::KeySetInput()
{
	m_dlg.DataExchangeFromBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}


////////////////////////////////////////////////////////////////////////////
// Antwort auf Bearbeitungskommandos

int CArticleCategoryView::SucheSatz( )
{
	int suchen = 0;

	ChSelectDialog *dlg = NewSuchDialog();

	if ( dlg->DoModal() == IDOK )
	{
		if ( PrimeKeyOfSelectedRecord( ) ) 
		{
			long lStatus;
			CString cErrmld;

			KeySetInput();
			((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
			lStatus = m_Doc.ReadRecord( cErrmld );
			((CEkZdpApp*) AfxGetApp())->EndWaitAction();
			if ( lStatus != 0 )
			{
				MsgBoxOK( cErrmld );
			}
			else
			{
				ShowFields();
				suchen = 1;
			}
		}
	}
	m_nStatus = 0;
	GotoFirstKey();

	delete *dlg;

	return suchen;
}

int CArticleCategoryView::NextSatz( )
{
	if ( PrimeKeyOfNextRecord( ) )
	{
		long lStatus;
		CString cErrmld;

		KeySetInput();
		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();	
		lStatus = m_Doc.ReadRecord( cErrmld );
		((CEkZdpApp*) AfxGetApp())->EndWaitAction();

		if ( !(lStatus == 0 || lStatus == 100 ) )
		{
			MsgBoxOK( cErrmld );
			return 0;
		}

		ShowFields();
		if ( lStatus == 100 )
		{
			SetValidation( FALSE );	
			((CEkZdpApp*) AfxGetApp())->MeldRecordWasDeleted( );
		}

		if ( m_nStatus == 0 )
			GotoFirstKey();
		else
			GotoFirstField();
		return 1;
	}
	else
		return 0;
}

int CArticleCategoryView::PrevSatz( )
{
	if ( PrimeKeyOfPrevRecord( ) )
	{
		long lStatus;
		CString cErrmld;

		KeySetInput();
		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		lStatus = m_Doc.ReadRecord( cErrmld );
		((CEkZdpApp*) AfxGetApp())->EndWaitAction();

		if ( !(lStatus == 0 || lStatus == 100 ) )
		{
			MsgBoxOK( cErrmld );
			return 0;
		}

		ShowFields();
		if ( lStatus == 100 )
		{
			SetValidation( FALSE );	
			((CEkZdpApp*) AfxGetApp())->MeldRecordWasDeleted( );
		}

		if ( m_nStatus == 0 )
			GotoFirstKey();
		else
			GotoFirstField();
		return 1;
	}
	else
		return 0;
}

int CArticleCategoryView::BearbeiteSatz( )
{

	if ( m_nStatus > 0 || !IsLastKeyFocus() )
	{
		((CDialogMultiLang*) this)->NextDlgCtrl( );
		return 0;
	}

	KeyGetInput();

	if ( !ValidateKey( ) )
	{
		GotoFirstKey();
	   	return 0;
	}


	CString cErrmld;
	long lStatus;
	
	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.ReadRecord( cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
	if ( !( lStatus == 0 || lStatus == 100 ) )
	{
		m_nStatus = 0;
		MsgBoxOK( cErrmld );
		return 0;
	}

	if ( lStatus == 0 )		// Satz vorhanden
		m_nStatus = 1;
	else					// Satz nicht vorhanden
		m_nStatus = 2;

	ShowFields();
	EnableFields( TRUE );
	GotoFirstField();

	if ( m_nStatus == 1 )
		return 1;
	else
		return 2;
}

int CArticleCategoryView::SpeichereSatz( )
{
    DataExchangeToBuffer( );

	if ( !Validate() ) return -1;

	if ( ! (( CEkZdpApp *)AfxGetApp())->YouWantToStoreRecord( ) ) return -1;

	CString cErrmld;
	long lStatus;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.StoreRecord( cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( lStatus == 0 )
	{
		m_bChanged = TRUE;
		m_nStatus = 0;
		EnableFields( FALSE );
		GotoFirstKey();
//		return 1;	// blaettern aus
		return 2;	// weiterblaettern
	}
	MsgBoxOK( cErrmld );
	return 0;
}

int CArticleCategoryView::LoescheSatz( )
{
	long lStatus;
	CString cErrmld;
	BOOL bFrage;

	SetValidation( FALSE ); // wegen Change focus
	bFrage = (( CEkZdpApp *)AfxGetApp())->YouWantToDeleteRecord( );
	SetValidation( TRUE );
	if ( !bFrage ) return 0;

    DataExchangeToBuffer( );

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.DeleteRecord ( cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
	if ( lStatus == 0 )
	{
		m_bChanged = TRUE;
		m_nStatus = 0;
		EnableFields( FALSE );
		GotoFirstKey();
		return 1;
	}
	MsgBoxOK( cErrmld );
	return 0;
}

int CArticleCategoryView::UndoSatz( )
{
	if ( m_nStatus == 0 )
	{
		m_Doc.FreeBufferDesc( );
		CloseSuche();
		return 0;
	}
	m_nStatus = 0;
	EnableFields( FALSE );
	GotoFirstKey();

	return 1;
}

void CArticleCategoryView::CopySatz( )
{
    DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
}

void CArticleCategoryView::CutSatz( )
{
	CString cErrmld;
    DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
	if ( m_Doc.InitRecord( cErrmld ) != 0 )
		MsgBoxOK( cErrmld );
	else
		ShowFields();
}

void CArticleCategoryView::PasteSatz( )
{
	m_Doc.RestoreBuffer();
	ShowFields();
}


void CArticleCategoryView::InitPflegeDocument( char* Anwender )
{
	m_Doc.InitPflegeDesc( Anwender );
}

void CArticleCategoryView::ReleasePflegeDocument( )
{
}

/////////////////////////////////////////////////////////////////////////////
// CArticleCategoryView message handlers

void CArticleCategoryView::OnInitialUpdate() 
{
	CFormViewMultiLang::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	InitPflege();
	m_Doc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	m_nStatus = 0;
}

void CArticleCategoryView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class

	CFormViewMultiLang::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
//		ShowFields();
		if ( pActivateView != pDeactiveView )
		{
			m_bChanged = FALSE;  // noch keine Aenderung
			m_Doc.SetTagesdatum( ::Today() );
	 		GotoFirstKey();
		}
	}
}

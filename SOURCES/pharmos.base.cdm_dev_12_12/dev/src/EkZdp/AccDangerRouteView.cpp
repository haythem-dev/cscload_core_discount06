// RablistView.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "AccDangerRouteView.h"

#include "ServerDatum.h"

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDblPos.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccDangerRouteView

IMPLEMENT_DYNCREATE(CAccDangerRouteView, CFormViewMultiLang)

CAccDangerRouteView::CAccDangerRouteView()
	: ChPflegeView(CAccDangerRouteView::IDD)
{
	//{{AFX_DATA_INIT(CAccDangerRouteView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAccDangerRouteView::~CAccDangerRouteView()
{
}

void CAccDangerRouteView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccDangerRouteView)
	DDX_Control(pDX, IDC_ED_ADR_UNNR,				m_UNNR);
	DDX_Control(pDX, IDC_ED_ADR_VERPACKUNGSGRUPPE,	m_VPGRUPPE);
	DDX_Control(pDX, IDC_ED_ADR_LQ_ADR2009,			m_LQ_ADR2009);
	DDX_Control(pDX, IDC_ED_ADR_ADR2011,			m_ADR2011);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAccDangerRouteView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CAccDangerRouteView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CAccDangerRouteView::MakeDialog()
{
	m_Pos_FirstKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_UNNR );

	m_Pos_LastKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_VPGRUPPE );

	m_Pos_FirstField = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_LQ_ADR2009 );

	m_dlg.InitDialog( m_ADR2011 );

	m_nMaxFields = m_dlg.GetFieldNumber();		
}

/////////////////////////////////////////////////////////////////////////////
// CAccDangerRouteView diagnostics

#ifdef _DEBUG
void CAccDangerRouteView::AssertValid() const
{
	CFormViewMultiLang::AssertValid();
}

void CAccDangerRouteView::Dump(CDumpContext& dc) const
{
	CFormViewMultiLang::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////
//  Validierung

/////////////////////////////////////////////////////////////
//  EndValidierung 

BOOL CAccDangerRouteView::EndValidate( int *ind )
{
	BOOL bOk = true;
	CString csErrmld, cs1, cs2;

	cs1.Format("%s", m_Doc.GetBuffer()->LQ_ADR2009);
	cs2.Format("%s", m_Doc.GetBuffer()->ADR2011);

	cs1.Trim();
	cs2.Trim();

	// mindestens ein Feld muss gefüllt sein
	if (cs1.IsEmpty() && 
	    cs2.IsEmpty())
	{
		bOk = false;
		csErrmld = CResString::ex().getStrTblText(IDS_STRING59);
	}

	if ( !bOk )
		AfxMessageBox( csErrmld );

	*ind = m_Pos_FirstField;
	return bOk;
} 

/////////////////////////////////////////////////////////////
//  Dialogfelder

void CAccDangerRouteView::InitPflege()
{
	MakeDialog();

	m_pBuf = m_Doc.GetBuffer();

	m_UNNR.SetMask				(ED_CHAR,
								 ED_UPPER,
								 m_pBuf->G_UN_NR,
								 L_CACCDANGERROUTE_G_UN_NR, 
								 new ChMaskNum );

	m_VPGRUPPE.SetMask			(ED_CHAR,
	                             ED_CLINPUT | ED_UPPER,
								 m_pBuf->VERPACKUNGSGRUPPE,
								 L_CACCDANGERROUTE_VERPACKUNGSGRUPPE, 
								 new ChMaskChar );

	m_LQ_ADR2009.SetMask		(ED_CHAR,
								 ED_CLINPUT | ED_UPPER,
								 m_pBuf->LQ_ADR2009,
								 L_CACCDANGERROUTE_LQ_ADR2009,
		                         new ChMaskChar );

	m_ADR2011.SetMask			(ED_CHAR,
								 ED_CLINPUT | ED_UPPER,
								 m_pBuf->ADR2011,
								 L_CACCDANGERROUTE_ADR2011,
		                         new ChMaskChar );

	EnableFields( FALSE );
	SetDialog();

}

void CAccDangerRouteView::DisableSpecial()
{
	// dummy
}

void CAccDangerRouteView::ShowSpecial()
{
	// dummy
}

///////////////////////////////////////////////////
// Suchbox

ChSelectDialog* CAccDangerRouteView::NewSuchDialog()
{
	return new ChSelectDialog ( CResString::ex().getStrTblText(IDS_STRING1349), &m_SelBox,
								HCD_SCROLLINFO );
							//	HCD_SCROLLINFO | HCD_BUTTONALTERN );
}

BOOL CAccDangerRouteView::PrimeKeyOfSelectedRecord( )
{
	return m_SelBox.PrimeKeyOfSelectedRecord( m_Doc.GetBuffer()->G_UN_NR, 
											  m_Doc.GetBuffer()->VERPACKUNGSGRUPPE ) == 0;
}

BOOL CAccDangerRouteView::PrimeKeyOfNextRecord( )
{
	return m_SelBox.PrimeKeyOfNextRecord( m_Doc.GetBuffer()->G_UN_NR, 
										  m_Doc.GetBuffer()->VERPACKUNGSGRUPPE ) == 0;
}

BOOL CAccDangerRouteView::PrimeKeyOfPrevRecord( )
{
	return m_SelBox.PrimeKeyOfPrevRecord( m_Doc.GetBuffer()->G_UN_NR, 
										  m_Doc.GetBuffer()->VERPACKUNGSGRUPPE ) == 0;
}

int CAccDangerRouteView::CloseSuche( )
{
	m_SelBox.CloseCursor();
	return 0;
}


////////////////////////////////////////////////////////////////
// Rest kann kopiert werden
////////////////////////////////////////////////////////////////

void CAccDangerRouteView::SetDialog( BOOL bDialog )
{   
 	m_dlg.SetDialog( bDialog );
}

void CAccDangerRouteView::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CAccDangerRouteView::EnableFields( BOOL bEnab )
{
	m_dlg.EnableFields( m_Pos_FirstKey, m_Pos_LastKey, !bEnab );
	m_dlg.EnableFields( m_Pos_FirstField, m_nMaxFields - 1, bEnab );

	DisableSpecial();
}

void CAccDangerRouteView::ShowFields( )
{
	m_dlg.ShowFields();

	ShowSpecial();
}

void CAccDangerRouteView::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CAccDangerRouteView::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

BOOL CAccDangerRouteView::Validate( )
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
	if ( bOk )
		bOk = EndValidate( &i );
	if ( !bOk ) m_dlg.SetFocus( i );
	SetValidation( TRUE );
	return bOk;
}

BOOL CAccDangerRouteView::ValidateKey( )
{
	return m_dlg.Validate( m_Pos_FirstKey, TRUE );
}
	
BOOL CAccDangerRouteView::IsLastKeyFocus( )
{
	return GetFocus() == GetDlgItem( IDC_LAST_KEY );
}

// Steuerung

void CAccDangerRouteView::GotoFirstKey()
{
	SetValidation( FALSE );		
	m_dlg.SetFocus( m_Pos_FirstKey );
}

void CAccDangerRouteView::GotoFirstField()
{
	m_dlg.SetFocus( m_Pos_FirstField );
	SetValidation( TRUE );		
}

void CAccDangerRouteView::KeyGetInput()
{
	m_dlg.DataExchangeToBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

void CAccDangerRouteView::KeySetInput()
{
	m_dlg.DataExchangeFromBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}


////////////////////////////////////////////////////////////////////////////
// Antwort auf Bearbeitungskommandos

int CAccDangerRouteView::SucheSatz( )
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

int CAccDangerRouteView::NextSatz( )
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

int CAccDangerRouteView::PrevSatz( )
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

int CAccDangerRouteView::BearbeiteSatz( )
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

int CAccDangerRouteView::SpeichereSatz( )
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
		m_bChanged = TRUE;  // jetzt Aenderung
		m_nStatus = 0;
		EnableFields( FALSE );
		GotoFirstKey();
//		return 1;	// blaettern aus
		return 2;	// weiterblaettern
	}
	MsgBoxOK( cErrmld );
	return 0;
}

int CAccDangerRouteView::LoescheSatz( )
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
		m_bChanged = TRUE;  // jetzt Aenderung
		m_nStatus = 0;
		EnableFields( FALSE );
		GotoFirstKey();
//		return 1;	// blaettern aus
		return 2;	// weiterblaettern
	}
	MsgBoxOK( cErrmld );
	return 0;
}

int CAccDangerRouteView::UndoSatz( )
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

void CAccDangerRouteView::CopySatz( )
{
    DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
}

void CAccDangerRouteView::CutSatz( )
{
	CString cErrmld;
    DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
	if ( m_Doc.InitRecord( cErrmld ) != 0 )
		MsgBoxOK( cErrmld );
	else
		ShowFields();
}

void CAccDangerRouteView::PasteSatz( )
{
	m_Doc.RestoreBuffer();
	ShowFields();
}

void CAccDangerRouteView::InitPflegeDocument( char* Anwender )
{
	m_Doc.InitPflegeDesc( Anwender );
}

void CAccDangerRouteView::ReleasePflegeDocument( )
{
}

/////////////////////////////////////////////////////////////////////////////
// CBankView message handlers

void CAccDangerRouteView::OnInitialUpdate() 
{
	CFormViewMultiLang::OnInitialUpdate();
	
	InitPflege();
	m_Doc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	m_nStatus = 0;
}

void CAccDangerRouteView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CFormViewMultiLang::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
		ShowFields();	

		if ( pActivateView != pDeactiveView )
		{
			m_bChanged = FALSE;  // noch keine Aenderung

			GotoFirstKey();
		}
	}
}

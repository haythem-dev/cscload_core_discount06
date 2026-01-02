 // ArtkatgView.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtkatgView.h"
#include "IfaFiles.h"
#include "ServerDatum.h"
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskNum.h>
// #include <wudu.h>
#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/wunxlocs/hTextDat.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtkatgView

IMPLEMENT_DYNCREATE(CArtkatgView, CFormViewMultiLang)

CArtkatgView::CArtkatgView()
	: ChPflegeView(CArtkatgView::IDD)
{
	//{{AFX_DATA_INIT(CArtkatgView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CArtkatgView::~CArtkatgView()
{
}

void CArtkatgView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtkatgView)
	DDX_Control(pDX, IDC_ED_ARTKATG_WARENGRUPPE, m_WARENGRUPPE);
	DDX_Control(pDX, IDC_ED_ARTKATG_BEZEICHNUNG, m_BEZEICHNUNG);
	DDX_Control(pDX, IDC_ED_ARTKATG_RABATTGRUPPE, m_RABATTGRUPPE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtkatgView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CArtkatgView)
//	ON_BN_CLICKED(IDC_PB_ARTKATG_LADEN, OnPbArtkatgLaden)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtkatgView::MakeDialog()
{
	m_Pos_FirstKey = m_Pos_LastKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_WARENGRUPPE  );

	m_Pos_FirstField = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_BEZEICHNUNG  );
	m_dlg.InitDialog( m_RABATTGRUPPE  );

	m_nMaxFields = m_dlg.GetFieldNumber();
}

/////////////////////////////////////////////////////////////////////////////
// CArtkatgView diagnostics

#ifdef _DEBUG
void CArtkatgView::AssertValid() const
{
	CFormViewMultiLang::AssertValid();
}

void CArtkatgView::Dump(CDumpContext& dc) const
{
	CFormViewMultiLang::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////
//  Validierung

class CV_ARTKATG_Warengruppe : public ChValBase
{
public:
	CV_ARTKATG_Warengruppe( struct ARTKATG* pBuf ) : ChValBase( pBuf ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString wgr;
		CString blk;
		BOOL bOk;

		wgr = ((struct ARTKATG*)m_pBuf)->WARENGRUPPE;
		wgr.TrimRight();
		bOk = !wgr.IsEmpty();
		if ( bOk )
		{
		   blk = wgr.SpanExcluding( " " );
		   bOk = blk == wgr;
		}

		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING41) );

		return bOk;
	}
};

class CV_ARTKATG_Bezeichnung : public ChValBase
{
public:
	CV_ARTKATG_Bezeichnung( struct ARTKATG* pBuf ) : ChValBase( pBuf ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = (( struct ARTKATG*)m_pBuf)->BEZEICHNUNG[0] != ' ';
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING42) );
		return bOk;
	}
};

class CV_ARTKATG_RabGr : public ChValBase
{
public:
	CV_ARTKATG_RabGr( struct ARTKATG* pBuf, CArtkatgView* pView ) : ChValBase( pBuf, pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = ((CArtkatgView*)m_pWnd)->CheckRabGr( ( ( struct ARTKATG*)m_pBuf)->RABATTGRUPPE);
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING653) ); 
		return bOk;
	}
};

/////////////////////////////////////////////////////////////
//  Dialogfelder

void CArtkatgView::InitPflege()
{
	CArtkatgView* pThisView = this;

	MakeDialog();

	struct ARTKATG* m_Buf;
	m_Buf = m_Doc.GetBuffer();

	m_WARENGRUPPE.SetMask   (ED_CHAR,
                             ED_CLINPUT | ED_LEADZERO,
                             m_Buf->WARENGRUPPE,
                             L_ARTKATG_WARENGRUPPE,
							 new ChMaskNum,
					         new CV_ARTKATG_Warengruppe( m_Buf ) );

	m_BEZEICHNUNG.SetMask   (ED_CHAR,
                             ED_UPPER,
                             m_Buf->BEZEICHNUNG,
                             L_ARTKATG_BEZEICHNUNG,
                             new ChMaskChar,
							 new CV_ARTKATG_Bezeichnung( m_Buf ) );
    
	m_RABATTGRUPPE.SetMask  (ED_CHAR,
                             ED_UPPER,
                             m_Buf->RABATTGRUPPE,
                             L_ARTKATG_RABATTGRUPPE,
							 new ChMaskNum, 
							 new CV_ARTKATG_RabGr( m_Buf, pThisView ) );

	EnableFields( FALSE );
	SetDialog();
}

void CArtkatgView::DisableSpecial()
{
	// dummy
}

void CArtkatgView::ShowSpecial()
{
	// dummy
}

/////////////////////////////////////////////////////////////////////
// Suchbox

ChSelectDialog* CArtkatgView::NewSuchDialog()
{
	return new ChSelectDialog ( CResString::ex().getStrTblText(IDS_STRING43), &m_SelBox,
								HCD_SCROLLINFO );
							//	HCD_SCROLLINFO | HCD_BUTTONALTERN );
}

BOOL CArtkatgView::PrimeKeyOfSelectedRecord( )
{ 
	return m_SelBox.PrimeKeyOfSelectedRecord( m_Doc.GetBuffer()->WARENGRUPPE ) == 0;
}

BOOL CArtkatgView::PrimeKeyOfNextRecord( )
{
	return m_SelBox.PrimeKeyOfNextRecord( m_Doc.GetBuffer()->WARENGRUPPE ) == 0;
}

BOOL CArtkatgView::PrimeKeyOfPrevRecord( )
{
	return m_SelBox.PrimeKeyOfPrevRecord( m_Doc.GetBuffer()->WARENGRUPPE ) == 0;
}

int CArtkatgView::CloseSuche( )
{
	m_SelBox.CloseCursor();
	return 0;
}


////////////////////////////////////////////////////////////////
// Rest kann kopiert werden
////////////////////////////////////////////////////////////////

void CArtkatgView::SetDialog( BOOL bDialog )
{   
 	m_dlg.SetDialog( bDialog );
}

void CArtkatgView::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtkatgView::EnableFields( BOOL bEnab )
{
	m_dlg.EnableFields( m_Pos_FirstKey, m_Pos_LastKey, !bEnab );
	m_dlg.EnableFields( m_Pos_FirstField, m_nMaxFields - 1, bEnab );
	DisableSpecial();
}

void CArtkatgView::ShowFields( )
{
	m_dlg.ShowFields();

	ShowSpecial();
}

void CArtkatgView::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtkatgView::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

BOOL CArtkatgView::Validate( )
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

BOOL CArtkatgView::ValidateKey( )
{
	return m_dlg.Validate( m_Pos_FirstKey, TRUE );
}

BOOL CArtkatgView::IsLastKeyFocus( )
{
	return GetFocus() == GetDlgItem( IDC_LAST_KEY );
}

// Steuerung

void CArtkatgView::GotoFirstKey()
{
	SetValidation( FALSE );	
	m_dlg.SetFocus( m_Pos_FirstKey );
}

void CArtkatgView::GotoFirstField()
{
	m_dlg.SetFocus( m_Pos_FirstField );
	SetValidation( TRUE );	
}

void CArtkatgView::KeyGetInput()
{
	m_dlg.DataExchangeToBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

void CArtkatgView::KeySetInput()
{
	m_dlg.DataExchangeFromBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}


////////////////////////////////////////////////////////////////////////////
// Antwort auf Bearbeitungskommandos

int CArtkatgView::SucheSatz( )
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

int CArtkatgView::NextSatz( )
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

int CArtkatgView::PrevSatz( )
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

int CArtkatgView::BearbeiteSatz( )
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

int CArtkatgView::SpeichereSatz( )
{
    DataExchangeToBuffer( );

	if ( !Validate() ) return -1;

	if ( ! (( CEkZdpApp *)AfxGetApp())->YouWantToStoreRecord( ) ) return -1;

	if ( m_Doc.WasChangedRabgrp())
	{
		MsgBoxOK(IDS_STRING649);
	}

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

int CArtkatgView::LoescheSatz( )
{
	int lStatus;
	CString cErrmld;
	BOOL bFrage;

	if ( ! (m_Doc.CheckDelete() == 0))
	{
		return -1;
	}

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
//		return 1;	// blaettern aus
		return 2;	// weiterblaettern
	}
	MsgBoxOK( cErrmld );
	return 0;
}

int CArtkatgView::UndoSatz( )
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

void CArtkatgView::CopySatz( )
{
	DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
}

void CArtkatgView::CutSatz( )
{
	CString cErrmld;
	DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
	if ( m_Doc.InitRecord( cErrmld ) != 0 )
		MsgBoxOK( cErrmld );
	else
		ShowFields();
}

void CArtkatgView::PasteSatz( )
{
	m_Doc.RestoreBuffer();
	ShowFields();
}


void CArtkatgView::InitPflegeDocument( char* Anwender )
{
	m_Doc.InitPflegeDesc( Anwender );
}

void CArtkatgView::ReleasePflegeDocument( )
{
}

/////////////////////////////////////////////////////////////////////////////
// CDformView message handlers

void CArtkatgView::OnInitialUpdate() 
{

	CFormViewMultiLang::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	InitPflege();
	m_Doc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	m_nStatus = 0;
}

void CArtkatgView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

BOOL CArtkatgView::CheckRabGr( char *csRabgrp )
{
	int iStat;
	CString Name;
	CString Errmld;

	if (!m_Doc.WasChangedRabgrp() || strcmp(csRabgrp, "") == 0)
		return 0;

	iStat = m_RD_RABATTGRP.IPlausi( csRabgrp, Name, &Errmld);

	return iStat <= 1; 
}

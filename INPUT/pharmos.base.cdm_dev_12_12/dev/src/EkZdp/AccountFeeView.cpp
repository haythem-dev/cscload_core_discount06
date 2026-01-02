// CAccountFeeView.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "AccountFeeView.h"

#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskDblPos.h>

#include "FeldBreite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountFeeView

IMPLEMENT_DYNCREATE(CAccountFeeView, CFormViewMultiLang)

CAccountFeeView::CAccountFeeView()
	: ChPflegeView(CAccountFeeView::IDD)
{
	//{{AFX_DATA_INIT(CAccountFeeView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAccountFeeView::~CAccountFeeView()
{
}

void CAccountFeeView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountFeeView)
	DDX_Control(pDX, IDC_ED_ACCOUNTFEE_TYPE, m_TYPE);
	DDX_Control(pDX, IDC_ED_ACCOUNTFEE_UNIT, m_UNIT);
	DDX_Control(pDX, IDC_ED_ACCOUNTFEE_ITEMSTYLE, m_ITEMSTYLE);
	DDX_Control(pDX, IDC_ED_ACCOUNTFEE_FEE, m_FEE);
	DDX_Control(pDX, IDC_ED_ACCOUNTFEE_MANUFACTURER, m_MANUFACTURER);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccountFeeView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CAccountFeeView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CAccountFeeView::MakeDialog()
{
	m_Pos_FirstKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_TYPE  );
	m_dlg.InitDialog( m_UNIT  );
	m_dlg.InitDialog( m_ITEMSTYLE );
	m_Pos_LastKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_MANUFACTURER );
	
	m_Pos_FirstField = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_FEE  );

	m_nMaxFields = m_dlg.GetFieldNumber();	
}

/////////////////////////////////////////////////////////////////////////////
// CArtnrblveView diagnostics

#ifdef _DEBUG
void CAccountFeeView::AssertValid() const
{
	CFormViewMultiLang::AssertValid();
}

void CAccountFeeView::Dump(CDumpContext& dc) const
{
	CFormViewMultiLang::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////
//  Verknuepfungen lesen

BOOL CAccountFeeView::ShowType( BOOL bMeldung )
{
	int iStat = 0;
	CString Name;
	CString Errmld;
	
	iStat = m_RD_TYPE.IPlausi( m_pBufFee->ACCOUNTTYPEID, Name, &Errmld);
	GetDlgItem( IDC_ST_ACCOUNTFEE_TYPE )->SetWindowText( Name );
	
	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;         
}

void CAccountFeeView::SucheType( )
{
	CAccountTypeSelCtrl selBox;

	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1242), &selBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( selBox.PrimeKeyOfSelectedRecord( &m_pBufFee->ACCOUNTTYPEID ) == 0 )
		{
			m_TYPE.p_SetInput();
			m_TYPE.SetFocus();
			ShowType( TRUE );
		}
	}

	selBox.CloseCursor();
}


BOOL CAccountFeeView::ShowUnit( BOOL bMeldung )
{
	int iStat = 0;
	CString Name;
	CString Errmld;
	
	iStat = m_RD_UNIT.IPlausi( m_pBufFee->ACCOUNTUNITID, Name, &Errmld);
	GetDlgItem( IDC_ST_ACCOUNTFEE_UNIT )->SetWindowText( Name );
	
	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;          
}


void CAccountFeeView::SucheUnit( )
{
	CAccountUnitSelCtrl selBox;

	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1241), &selBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( selBox.PrimeKeyOfSelectedRecord( &m_pBufFee->ACCOUNTUNITID ) == 0 )
		{
			m_UNIT.p_SetInput();
			m_UNIT.SetFocus();
			ShowUnit( TRUE );
		}
	}

	selBox.CloseCursor();
}

BOOL CAccountFeeView::ShowItemStyle( BOOL bMeldung )
{
	int iStat = 0;
	CString Name;
	CString Errmld;
	
	iStat = m_RD_ITEMSTYLE.IPlausi( m_pBufFee->ACCOUNTITEMSTYLEID, Name, &Errmld);
	GetDlgItem( IDC_ST_ACCOUNTFEE_ITEMSTYLE )->SetWindowText( Name );
	
	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;        
}

void CAccountFeeView::SucheItemStyle( )
{
	CAccountItemStyleSelCtrl selBox;

	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1243), &selBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( selBox.PrimeKeyOfSelectedRecord( &m_pBufFee->ACCOUNTITEMSTYLEID ) == 0 )
		{
			m_ITEMSTYLE.p_SetInput();
			m_ITEMSTYLE.SetFocus();
			ShowItemStyle( TRUE );
		}
	}

	selBox.CloseCursor();
}

BOOL CAccountFeeView::ShowManufacturer( BOOL bMeldung )
{
	int iStat = 0;
	CString Name;
	CString Errmld;
	CString cPPE;

	if (m_pBufFee->MANUFACTURERNO == 0)
	{
		GetDlgItem( IDC_ST_ACCOUNTFEE_MANUFACTURER )->SetWindowText( "GLOBAL" );
		return TRUE;
	}

	iStat = m_RD_HERSTEL.IPlausi( m_pBufFee->MANUFACTURERNO, Name, cPPE, &Errmld );
	GetDlgItem( IDC_ST_ACCOUNTFEE_MANUFACTURER )->SetWindowText( Name );

	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0; 
}

void CAccountFeeView::SucheManufacturer( )
{
	CHerstelSelCtrl selBox;

	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_SEL_HERST), &selBox,
						HCD_SCROLLINFO );

	if( dlg.DoModal() == IDOK )
	{
		if( selBox.PrimeKeyOfSelectedRecord( &m_pBufFee->MANUFACTURERNO ) == 0 )
		{
			m_MANUFACTURER.p_SetInput();
			m_MANUFACTURER.SetFocus();
			ShowManufacturer( TRUE );
		}

	}
}

/////////////////////////////////////////////////////////////
//  Validierung

class CV_ACCOUNTFEE_Type : public ChValBase
{
public:
	CV_ACCOUNTFEE_Type( CAccountFeeView* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		if (bMeldung) {}

		return ((CAccountFeeView*)m_pWnd)->ShowType( TRUE );
	}
	void PostProc( )
	{
		((CAccountFeeView*)m_pWnd)->ShowType( FALSE );
	}
	void NotifyProc( )
	{
		((CAccountFeeView*)m_pWnd)->SucheType( );
	}
};

class CV_ACCOUNTFEE_Unit : public ChValBase
{
public:
	CV_ACCOUNTFEE_Unit( CAccountFeeView* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		if (bMeldung) {}
		return ((CAccountFeeView*)m_pWnd)->ShowUnit( TRUE );
	}
	void PostProc( )
	{
		((CAccountFeeView*)m_pWnd)->ShowUnit( FALSE );
	}
	void NotifyProc( )
	{
		((CAccountFeeView*)m_pWnd)->SucheUnit( );
	}
};

class CV_ACCOUNTFEE_ItemStyle : public ChValBase
{
public:
	CV_ACCOUNTFEE_ItemStyle( CAccountFeeView* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		if (bMeldung) {}
		return ((CAccountFeeView*)m_pWnd)->ShowItemStyle( TRUE );
	}
	void PostProc( )
	{
		((CAccountFeeView*)m_pWnd)->ShowItemStyle( FALSE );
	}
	void NotifyProc( )
	{
		((CAccountFeeView*)m_pWnd)->SucheItemStyle( );
	}
};

class CV_ACCOUNTFEE_Manufacturer : public ChValBase
{
public:
	CV_ACCOUNTFEE_Manufacturer( CAccountFeeView* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		if (bMeldung) {}
		return ((CAccountFeeView*)m_pWnd)->ShowManufacturer( TRUE );
	}
	void PostProc( )
	{
		((CAccountFeeView*)m_pWnd)->ShowManufacturer( FALSE );
	}
	void NotifyProc( )
	{
		((CAccountFeeView*)m_pWnd)->SucheManufacturer( );
	}

};


/////////////////////////////////////////////////////////////
//  EndValidierung 

BOOL CAccountFeeView::EndValidate( int *ind, BOOL bMeldung )
{
	if (ind) {}
	if (bMeldung) {}
	return TRUE;
}


/////////////////////////////////////////////////////////////
//  Dialogfelder

void CAccountFeeView::InitPflege()
{

	MakeDialog();

	m_pBufFee = m_Doc.GetBuffer();

	CAccountFeeView* pThisView = this;


	m_TYPE.SetMask      (ED_SHORT,
                             ED_NORMAL,
							 &m_pBufFee->ACCOUNTTYPEID,
                             2,
                             new ChMaskNum,
							 new CV_ACCOUNTFEE_Type( pThisView ) );

	m_UNIT.SetMask      (ED_SHORT,
                             ED_NORMAL,
							 &m_pBufFee->ACCOUNTUNITID,
                             2,
                             new ChMaskNum,
							 new CV_ACCOUNTFEE_Unit( pThisView ) );

	m_ITEMSTYLE.SetMask  (ED_SHORT,
                             ED_NORMAL,
							 &m_pBufFee->ACCOUNTITEMSTYLEID,
                             2,
                             new ChMaskNum,
							 new CV_ACCOUNTFEE_ItemStyle( pThisView ) );

	m_MANUFACTURER.SetMask  (ED_LONG,
                             ED_NORMAL,
							 &m_pBufFee->MANUFACTURERNO,
                             6,
                             new ChMaskNum,
							 new CV_ACCOUNTFEE_Manufacturer( pThisView ) );

	m_FEE.SetMask		(ED_DBL,
                           ED_NORMAL,
						   &m_pBufFee->FEE,
                           L_CACCOUNTFEE_FEE + 1,
                           N_CACCOUNTFEE_FEE,
						   new ChMaskDblPos );

	EnableFields( FALSE );
	SetDialog();

	m_nAuswahlIndex = 0;
}


void CAccountFeeView::DisableSpecial()
{
}

void CAccountFeeView::ShowSpecial()
{
	ShowType();
	ShowUnit();
	ShowItemStyle();
	ShowManufacturer();
}

//////////////////////////////////////////////////
// Suchbox

ChSelectDialog* CAccountFeeView::NewSuchDialog()
{
	return new ChSelectDialog ( CResString::ex().getStrTblText(IDS_STRING61448), &m_SelBox,
								HCD_SCROLLINFO );
}

BOOL CAccountFeeView::PrimeKeyOfSelectedRecord( )
{ 
	return m_SelBox.PrimeKeyOfSelectedRecord( &m_pBufFee->ACCOUNTTYPEID, 
												&m_pBufFee->ACCOUNTUNITID,
												&m_pBufFee->ACCOUNTITEMSTYLEID,
												&m_pBufFee->MANUFACTURERNO) == 0;
}

int CAccountFeeView::CloseSuche( )
{
	m_SelBox.CloseCursor();
	return 0;
}

////////////////////////////////////////////////////////////////
// Rest kann kopiert werden
////////////////////////////////////////////////////////////////

void CAccountFeeView::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CAccountFeeView::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CAccountFeeView::EnableFields( BOOL bEnab )
{
	m_dlg.EnableFields( m_Pos_FirstKey, m_Pos_LastKey, !bEnab );
	m_dlg.EnableFields( m_Pos_FirstField, m_nMaxFields - 1, bEnab );

	DisableSpecial();
}

void CAccountFeeView::ShowFields( )
{
	m_dlg.ShowFields();

	ShowSpecial();
}

void CAccountFeeView::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CAccountFeeView::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

BOOL CAccountFeeView::Validate( )
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
		bOk = EndValidate( &i, TRUE );
	if ( !bOk )
		m_dlg.SetFocus( i );
	SetValidation( TRUE );
	return bOk;
}

BOOL CAccountFeeView::ValidateKey( )
{
	if ( !m_dlg.Validate( m_Pos_FirstKey, TRUE ) )
	{
		m_TYPE.SetFocus();
		return FALSE;
	}
	if ( !m_dlg.Validate( m_Pos_FirstKey + 1, TRUE ) )
	{
		m_UNIT.SetFocus();
		return FALSE;
	}
	if ( !m_dlg.Validate( m_Pos_FirstKey + 2, TRUE ) ) 
	{
		m_ITEMSTYLE.SetFocus();
		return FALSE;
	}
	if ( !m_dlg.Validate( m_Pos_LastKey, TRUE ) )
	{
		m_MANUFACTURER.SetFocus();
		return FALSE;
	}
	
	return TRUE;
}

BOOL CAccountFeeView::IsLastKeyFocus( )
{
	return GetFocus() == GetDlgItem( IDC_LAST_KEY );
}

// Steuerung

void CAccountFeeView::GotoFirstKey()
{
	SetValidation( FALSE );		
	m_dlg.SetFocus( m_Pos_FirstKey );
}

void CAccountFeeView::GotoLastKey()
{
	SetValidation( FALSE );		
	m_dlg.SetFocus( m_Pos_LastKey );
}

void CAccountFeeView::GotoKey()
{
	if ( IsLastKeyFocus( ) )
		GotoLastKey();
	else
		GotoFirstKey();
}

void CAccountFeeView::GotoFirstField()
{
	m_dlg.SetFocus( m_Pos_FirstField );
	SetValidation( TRUE );		
}

void CAccountFeeView::KeyGetInput()
{
	m_dlg.DataExchangeToBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

void CAccountFeeView::KeySetInput()
{
	m_dlg.DataExchangeFromBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

////////////////////////////////////////////////////////////////////////////
// Antwort auf Bearbeitungskommandos

int CAccountFeeView::SucheSatz( )
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
	GotoLastKey();

	delete *dlg;

	return suchen;
}

int CAccountFeeView::NextSatz( )
{
	if (m_SelBox.PrimeKeyOfNextRecord(  &m_pBufFee->ACCOUNTTYPEID, 
										&m_pBufFee->ACCOUNTUNITID,
										&m_pBufFee->ACCOUNTITEMSTYLEID,
										&m_pBufFee->MANUFACTURERNO) == 0 )
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
			GotoLastKey();
		else
			GotoFirstField();
		
		return 1;
	}
	else
		return 0;
}

int CAccountFeeView::PrevSatz( )
{
	if (m_SelBox.PrimeKeyOfPrevRecord(  &m_pBufFee->ACCOUNTTYPEID, 
										&m_pBufFee->ACCOUNTUNITID,
										&m_pBufFee->ACCOUNTITEMSTYLEID,
										&m_pBufFee->MANUFACTURERNO) == 0 )
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
			GotoLastKey();
		else
			GotoFirstField();
		
		return 1;
	}
	else
		return 0;
}

int CAccountFeeView::BearbeiteSatz( )
{

	if ( m_nStatus > 0 || !IsLastKeyFocus() )
	{
		((CDialogMultiLang*) this)->NextDlgCtrl( );
		return 0;
	}

	CString cErrmld;

	KeyGetInput();

	if ( !ValidateKey( ) )
	{
		return 0;
	}

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

int CAccountFeeView::SpeichereSatz( )
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
//		GotoFirstKey();
		GotoLastKey();
//		return 1;	// blaettern aus
		return 2;	// weiterblaettern
	}
	MsgBoxOK( cErrmld );
	return 0;
}

int CAccountFeeView::LoescheSatz( )
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
//		GotoFirstKey();
		GotoLastKey();
//		return 1;	// blaettern aus
		return 2;	// weiterblaettern
	}
	MsgBoxOK( cErrmld );
	return 0;
}

int CAccountFeeView::UndoSatz( )
{
	if ( m_nStatus == 0 )
	{
		m_Doc.FreeBufferDesc( );
		CloseSuche();
		m_RD_ITEMSTYLE.Reset();
		m_RD_UNIT.Reset();
		m_RD_TYPE.Reset();
		m_RD_HERSTEL.Reset();
		return 0;
	}
	m_nStatus = 0;
	EnableFields( FALSE );
//	GotoFirstKey();
	GotoLastKey();

	return 1;
}

void CAccountFeeView::CopySatz( )
{
	DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
}

void CAccountFeeView::CutSatz( )
{
	CString cErrmld;
	DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
	if ( m_Doc.InitRecord( cErrmld ) != 0 )
		MsgBoxOK( cErrmld );
	else
		ShowFields();
}

void CAccountFeeView::PasteSatz( )
{
	m_Doc.RestoreBuffer();
	ShowFields();
}

void CAccountFeeView::InitPflegeDocument( char* Anwender )
{
	m_Doc.InitPflegeDesc( Anwender );
}

void CAccountFeeView::ReleasePflegeDocument( )
{
}

void CAccountFeeView::OnInitialUpdate() 
{

	CFormViewMultiLang::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	InitPflege();
	m_Doc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	m_nStatus = 0;
}

void CAccountFeeView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class

	CFormViewMultiLang::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
//		ShowFields();
		if ( pActivateView != pDeactiveView )
		{
			m_bChanged = FALSE;  // noch keine Aenderung
	 		GotoFirstKey();
		}
	}
}

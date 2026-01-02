// AdrStorageClassView.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "AdrStorageClassView.h"

#include <phxlib/storageclassselctrl.h>
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
// CAdrStorageClassView

IMPLEMENT_DYNCREATE(CAdrStorageClassView, CFormViewMultiLang)

CAdrStorageClassView::CAdrStorageClassView()
	: ChPflegeView(CAdrStorageClassView::IDD)
{
	//{{AFX_DATA_INIT(CAdrStorageClassView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAdrStorageClassView::~CAdrStorageClassView()
{
}

void CAdrStorageClassView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdrStorageClassView)
	DDX_Control(pDX, IDC_ED_ADRSTORAGECLASS_KLASSE,				m_KLASSE);
	DDX_Control(pDX, IDC_ED_ADRSTORAGECLASS_UNNR,				m_UNNR);
	DDX_Control(pDX, IDC_ED_ADRSTORAGECLASS_VERPACKUNGSGRUPPE,	m_VPGRUPPE);
	DDX_Control(pDX, IDC_ED_ADRSTORAGECLASS_LAGERKLASSE,		m_LAGERKLASSE);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAdrStorageClassView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CAdrStorageClassView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CAdrStorageClassView::MakeDialog()
{
	m_Pos_FirstKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_KLASSE );
	m_dlg.InitDialog( m_UNNR );

	m_Pos_LastKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_VPGRUPPE );

	m_Pos_FirstField = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_LAGERKLASSE );

	m_nMaxFields = m_dlg.GetFieldNumber();
}

/////////////////////////////////////////////////////////////////////////////
// CAdrStorageClassView diagnostics

#ifdef _DEBUG
void CAdrStorageClassView::AssertValid() const
{
	CFormViewMultiLang::AssertValid();
}

void CAdrStorageClassView::Dump(CDumpContext& dc) const
{
	CFormViewMultiLang::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////
//  Validierung

class CV_AdrStorageClass_Lagerklasse : public ChValBase
{
public:
	CV_AdrStorageClass_Lagerklasse(CAdrStorageClassView* pView) : ChValBase(pView){};

	BOOL Validate(BOOL bMeldung)
	{
		return ((CAdrStorageClassView*)m_pWnd)->ShowStorageClass(bMeldung, bMeldung);
	}

	void NotifyProc()
	{
		((CAdrStorageClassView*)m_pWnd)->SucheStorageClass();
	}
};


/////////////////////////////////////////////////////////////
//  EndValidierung 

BOOL CAdrStorageClassView::EndValidate( int *ind )
{
	BOOL bOk = true;
	CString csErrmld, cs1, cs2, cs3;

	cs1.Format("%s", m_Doc.GetBuffer()->GG_KLASSE);
	cs2.Format("%s", m_Doc.GetBuffer()->G_UN_NR);
	cs3.Format("%s", m_Doc.GetBuffer()->VERPACKUNGSGRUPPE);

	cs1.Trim();
	cs2.Trim();
	cs3.Trim();

	// mindestens ein Feld muss gefüllt sein
	if (cs1.IsEmpty() && 
	    cs2.IsEmpty() &&
		cs3.IsEmpty() )
	{
		bOk = false;
		csErrmld = CResString::ex().getStrTblText(IDS_STRING59);
	}

	if ( !bOk )
		AfxMessageBox( csErrmld );

	*ind = m_Pos_FirstField;
	return bOk;
} 

BOOL CAdrStorageClassView::ShowStorageClass(BOOL bShow, BOOL bMeldung)
{
	int		stat;
	CString name;
	CString errmld;
	
	stat = m_RD_STORAGECLASS.IPlausi(m_pBuf->STORAGECLASSID, name, &errmld);
	
	if(bShow)
	{
		GetDlgItem(IDC_ST_ADRSTORAGECLASS_LAGERKLASSE_BESCHREIBUNG)->SetWindowText(name);
	}

	if (stat > 1 && bMeldung) 
	{
		MsgBoxOK(errmld);
	}

	return stat <= 1;
}

void CAdrStorageClassView::SucheStorageClass()
{
	CStorageClassSelCtrl m_SelBoxType;

	ChSelectDialog dlg(CResString::ex().getStrTblText(IDS_STRING81),
					   &m_SelBoxType,
					   HCD_SCROLLINFO);

	if (dlg.DoModal() == IDOK)
	{
		if (m_SelBoxType.PrimeKeyOfSelectedRecord(m_pBuf->STORAGECLASSID) == 0)
		{
			m_LAGERKLASSE.p_SetInput();
			m_LAGERKLASSE.SetFocus();

			ShowStorageClass(TRUE, TRUE);
		}
	}

	m_SelBoxType.CloseCursor();
}

/////////////////////////////////////////////////////////////
//  Dialogfelder

void CAdrStorageClassView::InitPflege()
{
	MakeDialog();

	m_pBuf = m_Doc.GetBuffer();

	m_KLASSE.SetMask			(ED_CHAR,
								 ED_CLINPUT | ED_UPPER,
								 m_pBuf->GG_KLASSE,
								 L_CADRSTORAGECLASS_GG_KLASSE,
		                         new ChMaskChar );

	m_UNNR.SetMask				(ED_CHAR,
								 ED_UPPER,
								 m_pBuf->G_UN_NR,
								 L_CADRSTORAGECLASS_G_UN_NR, 
								 new ChMaskNum );

	m_VPGRUPPE.SetMask			(ED_CHAR,
	                             ED_CLINPUT | ED_UPPER,
								 m_pBuf->VERPACKUNGSGRUPPE,
								 L_CADRSTORAGECLASS_VERPACKUNGSGRUPPE, 
								 new ChMaskChar );

	m_LAGERKLASSE.SetMask		(ED_CHAR,
								 ED_CLINPUT | ED_UPPER,
								 m_pBuf->STORAGECLASSID,
								 L_CADRSTORAGECLASS_STORAGECLASSID,
		                         new ChMaskChar,
								 new CV_AdrStorageClass_Lagerklasse(this));

	EnableFields( FALSE );
	SetDialog();

}

void CAdrStorageClassView::DisableSpecial()
{
	// dummy
}

void CAdrStorageClassView::ShowSpecial()
{
	// dummy
	ShowStorageClass(TRUE);
}

///////////////////////////////////////////////////
// Suchbox

ChSelectDialog* CAdrStorageClassView::NewSuchDialog()
{
	return new ChSelectDialog ( CResString::ex().getStrTblText(IDS_STRING1349), &m_SelBox,
								HCD_SCROLLINFO );
							//	HCD_SCROLLINFO | HCD_BUTTONALTERN );*/
}

BOOL CAdrStorageClassView::PrimeKeyOfSelectedRecord( )
{
	return m_SelBox.PrimeKeyOfSelectedRecord( m_Doc.GetBuffer()->GG_KLASSE,
											  m_Doc.GetBuffer()->G_UN_NR, 
											  m_Doc.GetBuffer()->VERPACKUNGSGRUPPE ) == 0;
}

BOOL CAdrStorageClassView::PrimeKeyOfNextRecord( )
{
	return m_SelBox.PrimeKeyOfNextRecord( m_Doc.GetBuffer()->GG_KLASSE,
										  m_Doc.GetBuffer()->G_UN_NR, 
										  m_Doc.GetBuffer()->VERPACKUNGSGRUPPE ) == 0;
}

BOOL CAdrStorageClassView::PrimeKeyOfPrevRecord( )
{
	return m_SelBox.PrimeKeyOfPrevRecord( m_Doc.GetBuffer()->GG_KLASSE,
										  m_Doc.GetBuffer()->G_UN_NR, 
										  m_Doc.GetBuffer()->VERPACKUNGSGRUPPE ) == 0;
}

int CAdrStorageClassView::CloseSuche( )
{
	m_SelBox.CloseCursor();
	return 0;
}


////////////////////////////////////////////////////////////////
// Rest kann kopiert werden
////////////////////////////////////////////////////////////////

void CAdrStorageClassView::SetDialog( BOOL bDialog )
{   
 	m_dlg.SetDialog( bDialog );
}

void CAdrStorageClassView::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CAdrStorageClassView::EnableFields( BOOL bEnab )
{
	m_dlg.EnableFields( m_Pos_FirstKey, m_Pos_LastKey, !bEnab );
	m_dlg.EnableFields( m_Pos_FirstField, m_nMaxFields - 1, bEnab );

	DisableSpecial();
}

void CAdrStorageClassView::ShowFields( )
{
	m_dlg.ShowFields();
	ShowSpecial();
}

void CAdrStorageClassView::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CAdrStorageClassView::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

BOOL CAdrStorageClassView::Validate( )
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

BOOL CAdrStorageClassView::ValidateKey( )
{
	return m_dlg.Validate( m_Pos_FirstKey, TRUE );
}
	
BOOL CAdrStorageClassView::IsLastKeyFocus( )
{
	return GetFocus() == GetDlgItem( IDC_LAST_KEY );
}

// Steuerung

void CAdrStorageClassView::GotoFirstKey()
{
	SetValidation( FALSE );		
	m_dlg.SetFocus( m_Pos_FirstKey );
}

void CAdrStorageClassView::GotoFirstField()
{
	m_dlg.SetFocus( m_Pos_FirstField );
	SetValidation( TRUE );		
}

void CAdrStorageClassView::KeyGetInput()
{
	m_dlg.DataExchangeToBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

void CAdrStorageClassView::KeySetInput()
{
	m_dlg.DataExchangeFromBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}


////////////////////////////////////////////////////////////////////////////
// Antwort auf Bearbeitungskommandos

int CAdrStorageClassView::SucheSatz( )
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

int CAdrStorageClassView::NextSatz( )
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

int CAdrStorageClassView::PrevSatz( )
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

int CAdrStorageClassView::BearbeiteSatz( )
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

int CAdrStorageClassView::SpeichereSatz( )
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

int CAdrStorageClassView::LoescheSatz( )
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

int CAdrStorageClassView::UndoSatz( )
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

void CAdrStorageClassView::CopySatz( )
{
    DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
}

void CAdrStorageClassView::CutSatz( )
{
	CString cErrmld;
    DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
	if ( m_Doc.InitRecord( cErrmld ) != 0 )
		MsgBoxOK( cErrmld );
	else
		ShowFields();
}

void CAdrStorageClassView::PasteSatz( )
{
	m_Doc.RestoreBuffer();
	ShowFields();
}

void CAdrStorageClassView::InitPflegeDocument( char* Anwender )
{
	m_Doc.InitPflegeDesc( Anwender );
}

void CAdrStorageClassView::ReleasePflegeDocument( )
{
}

/////////////////////////////////////////////////////////////////////////////
// CAdrStorageClassView message handlers

void CAdrStorageClassView::OnInitialUpdate() 
{
	CFormViewMultiLang::OnInitialUpdate();
	
	InitPflege();
	m_Doc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	m_nStatus = 0;
}

void CAdrStorageClassView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

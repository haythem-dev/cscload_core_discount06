// ArtikelPage5RS.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "EkZdp.h"
#include "ArtikelPage5RS.h"
#include "ArtikelView.h"

#include <phxlib/ZollSelCtrl.h>

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDblPos.h>

// CArtikelPage5RS-Dialogfeld

IMPLEMENT_DYNCREATE(CArtikelPage5RS, CPropertyPageMultiLang)

// CArtikelPage5RS::CArtikelPage5RS()
CArtikelPage5RS::CArtikelPage5RS() : ChPflegePage(CArtikelPage5RS::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInitialized = FALSE;
}

CArtikelPage5RS::~CArtikelPage5RS()
{
}

void CArtikelPage5RS::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage5RS)
	DDX_Control(pDX, IDC_CO_ARTIKEL_ARTICLYTYPE,		m_ARTICLETYPE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_CUSTOMSNO,			m_CUSTOMSNO);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MAXPAYMENTTARGET,	m_MAXPAYMENTTARGET);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PACK_SIZE,			m_PACK_SIZE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ZOLL_PROZ,			m_ZOLL_PROZ);
	DDX_Control(pDX, IDC_ED_ARTIKEL_JKL_CODE,			m_JKL_CODE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_REFUNDTYPE,			m_REFUNDTYPE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_PACKAGE_INSERT,		m_PACKAGE_INSERT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_CERTIFICATEFLAG,	m_CERTIFICATEFLAG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND1_RS,		m_VERTRBIND1_RS);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND2_RS,		m_VERTRBIND2_RS);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND3_RS,		m_VERTRBIND3_RS);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND4_RS,		m_VERTRBIND4_RS);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND5_RS,		m_VERTRBIND5_RS);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND6_RS,		m_VERTRBIND6_RS);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND7_RS,		m_VERTRBIND7_RS);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND8_RS,		m_VERTRBIND8_RS);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CArtikelPage5RS, CPropertyPageMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage5RS::MakeDialog()
{
	m_dlg.InitDialog( m_ARTICLETYPE );
	m_dlg.InitDialog( m_CUSTOMSNO );
	m_dlg.InitDialog( m_MAXPAYMENTTARGET );
	m_dlg.InitDialog( m_PACK_SIZE );
	m_dlg.InitDialog( m_ZOLL_PROZ );
	m_dlg.InitDialog( m_JKL_CODE );
	m_dlg.InitDialog( m_REFUNDTYPE );
	m_dlg.InitDialog( m_PACKAGE_INSERT );
	m_dlg.InitDialog( m_CERTIFICATEFLAG );
	m_dlg.InitDialog( m_VERTRBIND1_RS );
	m_dlg.InitDialog( m_VERTRBIND2_RS );
	m_dlg.InitDialog( m_VERTRBIND3_RS );
	m_dlg.InitDialog( m_VERTRBIND4_RS );
	m_dlg.InitDialog( m_VERTRBIND5_RS );
	m_dlg.InitDialog( m_VERTRBIND6_RS );
	m_dlg.InitDialog( m_VERTRBIND7_RS );
	m_dlg.InitDialog( m_VERTRBIND8_RS );
	
	m_nMaxFields = m_dlg.GetFieldNumber();
}

/////////////////////////////////////////////////////////////
//  Validierung

// Zolldaten
BOOL CArtikelPage5RS::ShowZolldaten( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	iStat = m_RD_ZOLL.IPlausi( m_pBufZartserbia->CUSTOMSNO, Name, &Errmld);
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_ZOLLINFO )->SetWindowText( Name );
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage5RS::SucheZolldaten( )
{
	CZollSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1101), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufZartserbia->CUSTOMSNO ) == 0 )
		{
			m_CUSTOMSNO.p_SetInput();
			m_CUSTOMSNO.SetFocus();
			ShowZolldaten( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

class CV_ARTIKEL_Zoll : public ChValBase
{
public:
	CV_ARTIKEL_Zoll( CArtikelPage5RS* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage5RS*)m_pWnd)->ShowZolldaten( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage5RS*)m_pWnd)->SucheZolldaten( );
	}
};

// CArtikelPage5RS-Meldungshandler

void CArtikelPage5RS::InitPflege( CWnd *pView  )
{ 
	CArtikelPage5RS* pThisView = this;
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )pView)->GetBuffer();

	m_pBufZartserbia		= &m_Buf->zartserbia;
	m_pBufJKLCode			= &m_Buf->carticlecodes[16];	// code_type = 17
	m_pBufCarticleext		= &m_Buf->carticleext;

	MakeDialog();

	m_ARTICLETYPE.SetMask		( "012345"  , &m_pBufZartserbia->ARTICLETYPE ); 

	m_CUSTOMSNO.SetMask			(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufZartserbia->CUSTOMSNO,
				                 10,
								 new ChMaskChar,
								 new CV_ARTIKEL_Zoll( pThisView ) );

	m_MAXPAYMENTTARGET.SetMask	(ED_LONG,
								ED_NORMAL,
								&m_pBufZartserbia->MAXPAYMENTTARGET,
								3,
								new ChMaskNum );

	m_PACK_SIZE.SetMask			(ED_LONG,
								 ED_NORMAL,
								 &m_pBufZartserbia->PACK_SIZE,
								 3,
								 new ChMaskNum );

	m_JKL_CODE.SetMask			(ED_CHAR,
								 ED_UPPER,
								 m_pBufJKLCode->ARTICLE_CODE,
								 7,
   								 new ChMaskChar );

	m_ZOLL_PROZ.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufZartserbia->CUSTOMS_PCT,
								L_ZARTSERBIA_CUSTOMS_PCT + 1,
								N_ZARTSERBIA_CUSTOMS_PCT,
								new ChMaskDblPos );

	m_REFUNDTYPE.SetMask		(1, 0, &m_pBufZartserbia->REFUNDTYPE );

	m_PACKAGE_INSERT.SetMask	(1, 0, &m_pBufZartserbia->PACKAGE_INSERT );

	m_CERTIFICATEFLAG.SetMask	(1, 0, &m_pBufCarticleext->CERTIFICATEFLAG );

	m_VERTRBIND1_RS.SetMask		(1, 0, &m_pBufZartserbia->DISTR_RESTR_TEND );
	m_VERTRBIND2_RS.SetMask		(1, 0, &m_pBufZartserbia->DISTR_RESTR_BETY );
	m_VERTRBIND3_RS.SetMask		(1, 0, &m_pBufZartserbia->DISTR_RESTR_BENU );
	m_VERTRBIND4_RS.SetMask		(1, 0, &m_pBufZartserbia->DISTR_RESTR_ALRG );
	m_VERTRBIND5_RS.SetMask		(1, 0, &m_pBufZartserbia->DISTR_RESTR_CAUD );
	m_VERTRBIND6_RS.SetMask		(1, 0, &m_pBufZartserbia->DISTR_RESTR_HEM );
	m_VERTRBIND7_RS.SetMask		(1, 0, &m_pBufZartserbia->DISTR_RESTR_GR7 );
	m_VERTRBIND8_RS.SetMask		(1, 0, &m_pBufZartserbia->DISTR_RESTR_GR8 );

	m_bInitialized = TRUE; 
}
void CArtikelPage5RS::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CArtikelPage5RS::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage5RS::EnableFields( BOOL bEnab )
{   
	m_dlg.EnableFields( bEnab );
}

void CArtikelPage5RS::ShowFields( )
{
	FillComboBox();

	m_dlg.ShowFields();

	ShowZolldaten( TRUE );
}

void CArtikelPage5RS::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage5RS::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

void CArtikelPage5RS::ActivateField( int nr )
{
	m_dlg.ActivateField( nr );
}

BOOL CArtikelPage5RS::Validate( BOOL bMeldung )
{
	int i = 0;
	BOOL bOk = TRUE;

	SetValidation( FALSE );

	bOk = m_dlg.Validate( &i, bMeldung );
	if ( bOk )
		bOk = EndValidate( &i, bMeldung );

	if ( !bOk && bMeldung )
		m_dlg.ActivateField( i );
	
	SetValidation( TRUE ); 

	return bOk; 
}

/////////////////////////////////////////////////////////////
//  EndValidierung 

BOOL CArtikelPage5RS::EndValidate( int *ind, BOOL)
{
	*ind = 0;

	/* PostProcs aufrufen hier !!!!! */

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLieferPage1 message handlers

BOOL CArtikelPage5RS::OnSetActive()
{
	BOOL bOk = true;
	bOk = CPropertyPageMultiLang::OnSetActive();
	if ( bOk && m_bInitialized )
	{
		ShowFields();
		((CArtikelView* )m_pView)->Set_WasActive();
		EnableFields( ((CArtikelView* )m_pView)->AreFieldsEnabled() );
		GetParent()->SendMessage( WM_USER+10 );
		SetValidation( TRUE );
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING321) );
	} 
	return bOk;
}


BOOL CArtikelPage5RS::OnKillActive()
{
	BOOL bOk = true;
	bOk = CPropertyPageMultiLang::OnKillActive();
	if ( bOk )
	{
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING322) );
		SetValidation( FALSE );
		DataExchangeToBuffer( );  //  Puffer wie Eingabe
	} 
	return bOk;
}
 
/////////////////////////////////////////////
// Verknuepfungen Ruecksetzen

void CArtikelPage5RS::ResetVkn( )
{
//	m_RD_KRANKENKASSENCODE.Reset();
}

void CArtikelPage5RS::FillComboBox()
{
	m_ARTICLETYPE.ResetContent();

	m_ARTICLETYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1095));
	m_ARTICLETYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1096));
	m_ARTICLETYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1097));
	m_ARTICLETYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1104));
	m_ARTICLETYPE.AddString(CResString::ex().getStrTblText(IDS_STRING113));
	m_ARTICLETYPE.AddString(CResString::ex().getStrTblText(IDS_STRING114));

}

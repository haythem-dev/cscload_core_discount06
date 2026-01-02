// ArtikelPage5HR.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "EkZdp.h"
#include "ArtikelPage5HR.h"
#include "hSelectDialog.h"
#include "ArtikelView.h"

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDblPos.h>
#include <eklibs/hamfcs/hMskDate.h>

#include "FeldBreite.h"

// CArtikelPage5HR-Dialogfeld

IMPLEMENT_DYNCREATE(CArtikelPage5HR, CPropertyPageMultiLang)

// CArtikelPage5HR::CArtikelPage5HR()
CArtikelPage5HR::CArtikelPage5HR() : ChPflegePage(CArtikelPage5HR::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInitialized = FALSE;
}

CArtikelPage5HR::~CArtikelPage5HR()
{
}

void CArtikelPage5HR::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage5HR)
	DDX_Control(pDX, IDC_CK_ARTIKEL_CHARGE_HR, m_CHARGE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_LIEFERBAR_AB, m_DATUM_LIEFERBAR_AB);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND1_HR, m_VERTRBIND1_HR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND2_HR, m_VERTRBIND2_HR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND3_HR, m_VERTRBIND3_HR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND4_HR, m_VERTRBIND4_HR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND5_HR, m_VERTRBIND5_HR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND6_HR, m_VERTRBIND6_HR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND7_HR, m_VERTRBIND7_HR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND8_HR, m_VERTRBIND8_HR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_CERTIFICATEFLAG_HR,	m_CERTIFICATEFLAG);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtikelPage5HR, CPropertyPageMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage5HR::MakeDialog()
{
	m_Pos_BATCHARTICLE = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_CHARGE );

	m_dlg.InitDialog(m_DATUM_LIEFERBAR_AB);

	m_dlg.InitDialog( m_VERTRBIND1_HR );
	m_dlg.InitDialog( m_VERTRBIND2_HR );
	m_dlg.InitDialog( m_VERTRBIND3_HR );
	m_dlg.InitDialog( m_VERTRBIND4_HR );
	m_dlg.InitDialog( m_VERTRBIND5_HR );
	m_dlg.InitDialog( m_VERTRBIND6_HR );
	m_dlg.InitDialog( m_VERTRBIND7_HR );
	m_dlg.InitDialog( m_VERTRBIND8_HR );

	m_dlg.InitDialog( m_CERTIFICATEFLAG );

	m_nMaxFields = m_dlg.GetFieldNumber();
}

void CArtikelPage5HR::ResetVkn( )
{

}

/**---------------------------------------------------------------------------*/
BOOL CArtikelPage5HR::EndValidate( int *, BOOL )
{
	return TRUE;
}

// CArtikelPage5HR-Meldungshandler

/**---------------------------------------------------------------------------*/
void CArtikelPage5HR::InitPflege( CWnd *pView  )
{ 
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )pView)->GetBuffer();
	m_pBufZartcroatia = &m_Buf->zartcroatia;
	m_pBufCarticleext = &m_Buf->carticleext;
	m_pBufZartikel = &m_Buf->zartikel;
	
	MakeDialog();

	m_CHARGE.SetMask ( '1', '0', m_pBufZartcroatia->BATCHARTICLE);

	m_DATUM_LIEFERBAR_AB.SetMask(ED_LDATE,
								 ED_NORMAL,
								 &m_pBufZartikel->DATUM_LIEFERBAR_AB,
								 L_LDATUM,
								 new ChMaskLDate);

	m_VERTRBIND1_HR.SetMask ( '1', '0', m_pBufZartcroatia->DISTR_RESTR_MED2A);
	m_VERTRBIND2_HR.SetMask ( '1', '0', m_pBufZartcroatia->DISTR_RESTR_MED2B3);
	m_VERTRBIND3_HR.SetMask ( '1', '0', m_pBufZartcroatia->DISTR_RESTR_HUDRUG);
	m_VERTRBIND4_HR.SetMask ( '1', '0', m_pBufZartcroatia->DISTR_RESTR_BRDRUG);
	m_VERTRBIND5_HR.SetMask ( '1', '0', m_pBufZartcroatia->DISTR_RESTR_ALCOH);
	m_VERTRBIND6_HR.SetMask ( '1', '0', m_pBufZartcroatia->DISTR_RESTR_VETMED);
	m_VERTRBIND7_HR.SetMask ( '1', '0', m_pBufZartcroatia->DISTR_RESTR_VEDRUG);
	m_VERTRBIND8_HR.SetMask ( '1', '0', m_pBufZartcroatia->DISTR_RESTR_HUDRVE);

	m_CERTIFICATEFLAG.SetMask	(1, 0, &m_pBufCarticleext->CERTIFICATEFLAG );

	m_bInitialized = TRUE; 
}

/**---------------------------------------------------------------------------*/
void CArtikelPage5HR::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CArtikelPage5HR::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage5HR::EnableFields( BOOL bEnab )
{   
	m_dlg.EnableFields( bEnab );

	// auch deaktiviert wg. Automatik Verfalldatum
	m_CHARGE.EnableWindow(false);
}

void CArtikelPage5HR::ShowFields( )
{
	m_dlg.ShowFields();
}

void CArtikelPage5HR::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage5HR::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}


void CArtikelPage5HR::ActivateField( int nr )
{
	m_dlg.ActivateField( nr );
}


BOOL CArtikelPage5HR::Validate( BOOL bMeldung )
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

/////////////////////////////////////////////////////////////////////////////
// CLieferPage1 message handlers

BOOL CArtikelPage5HR::OnSetActive()
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
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING319) );
	} 
	return bOk;
}

BOOL CArtikelPage5HR::OnKillActive()
{
	BOOL bOk = true;
	bOk = CPropertyPageMultiLang::OnKillActive();
	if ( bOk )
	{
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING320) );
		SetValidation( FALSE );
		DataExchangeToBuffer( );  //  Puffer wie Eingabe
	} 
	return bOk;
}
  
void CArtikelPage5HR::Set_ExchangeRate( )
{
}

void CArtikelPage5HR::Set_BatchArticle( )
{
	m_dlg.DataExchangeFromBuffer( m_Pos_BATCHARTICLE );
}

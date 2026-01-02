// ArtikelPage5A.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "EkZdp.h"
#include "ArtikelPage5A.h"
#include "hSelectDialog.h"
#include "ArtikelView.h"

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDblPos.h>


// CArtikelPage5A-Dialogfeld

IMPLEMENT_DYNCREATE(CArtikelPage5A, CPropertyPageMultiLang)

// CArtikelPage5A::CArtikelPage5A()
CArtikelPage5A::CArtikelPage5A() : ChPflegePage(CArtikelPage5A::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInitialized = FALSE;
}

CArtikelPage5A::~CArtikelPage5A()
{
}

void CArtikelPage5A::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage5A)
	DDX_Control(pDX, IDC_CK_ARTIKEL_WECHSELARTIKEL, m_WECHSELARTIKEL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_BUENDELPACKUNG, m_BUENDELPACKUNG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_WAFO, m_WAFO);
	DDX_Control(pDX, IDC_CK_ARTIKEL_DBESORGER, m_DBESORGER);
	DDX_Control(pDX, IDC_CK_ARTIKEL_CHARGE, m_CHARGE);
	DDX_Control(pDX, IDC_CB_ARTIKEL_OELHV_OEKOKZ, m_OELHV_OEKOKZ);
	DDX_Control(pDX, IDC_ED_ARTIKEL_OELHV_GRUPPE, m_OELHV_GRUPPE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_OELHV_SORT, m_OELHV_SORT);
	DDX_Control(pDX, IDC_CB_ARTIKEL_HV_BOX, m_HV_BOX);
	DDX_Control(pDX, IDC_CB_ARTIKEL_MEDPROD_ABGVO, m_MEDPROD_ABGVO);
	DDX_Control(pDX, IDC_CB_ARTIKEL_MEDPROD_KLASSE, m_MEDPROD_KLASSE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_PLPL, m_VERTRBIND_PLPL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_S1S5, m_VERTRBIND_S1S5);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_VPL, m_VERTRBIND_VPL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_SP, m_VERTRBIND_SP);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_NEUFORM, m_VERTRBIND_NEUFORM);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_BEIERSDORF, m_VERTRBIND_BEIERSDORF);
	DDX_Control(pDX, IDC_CB_ARTIKEL_VERTRBIND_COMPTANT, m_VERTRBIND_COMPTANT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SG_SUBSTANZ, m_SG_SUBSTANZ);
	DDX_Control(pDX, IDC_CK_ARTIKEL_DROGENAGS_KAT1, m_DROGENAGS_KAT1);
	DDX_Control(pDX, IDC_CK_ARTIKEL_DROGENAGS_KAT2, m_DROGENAGS_KAT2);
	DDX_Control(pDX, IDC_CK_ARTIKEL_DROGENAGS_KAT3, m_DROGENAGS_KAT3);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NLH, m_NLH);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NGH, m_NGH);
	DDX_Control(pDX, IDC_ED_ARTIKEL_RUECK_MON_VOR_VERF, m_RUECK_MON_VOR_VERF);
	DDX_Control(pDX, IDC_ED_ARTIKEL_INGREDIENT_QTY, m_INGREDIENT_QTY);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GH_LAGERUNG_VERBOTEN, m_GH_LAGERUNG_VERBOTEN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtikelPage5A, CPropertyPageMultiLang)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_DBESORGER, OnPbDBesorger)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage5A::MakeDialog()
{
	m_dlg.InitDialog( m_WECHSELARTIKEL );
	m_dlg.InitDialog( m_BUENDELPACKUNG );
	m_dlg.InitDialog( m_WAFO );
	m_dlg.InitDialog( m_DBESORGER );
	m_dlg.InitDialog( m_CHARGE );
	m_dlg.InitDialog( m_OELHV_GRUPPE );
	m_dlg.InitDialog( m_OELHV_OEKOKZ );
	m_dlg.InitDialog( m_OELHV_SORT );
	m_dlg.InitDialog( m_HV_BOX );
	m_dlg.InitDialog( m_MEDPROD_ABGVO );
	m_dlg.InitDialog( m_MEDPROD_KLASSE );
	m_dlg.InitDialog( m_VERTRBIND_PLPL );
	m_dlg.InitDialog( m_VERTRBIND_S1S5 );
	m_dlg.InitDialog( m_VERTRBIND_VPL );
	m_dlg.InitDialog( m_VERTRBIND_SP );
	m_dlg.InitDialog( m_VERTRBIND_NEUFORM );
	m_dlg.InitDialog( m_VERTRBIND_BEIERSDORF );
	m_dlg.InitDialog( m_VERTRBIND_COMPTANT );
	m_dlg.InitDialog( m_SG_SUBSTANZ );
	m_dlg.InitDialog( m_GH_LAGERUNG_VERBOTEN );
	m_dlg.InitDialog( m_DROGENAGS_KAT1 );
	m_dlg.InitDialog( m_DROGENAGS_KAT2 );
	m_dlg.InitDialog( m_DROGENAGS_KAT3 );
	m_dlg.InitDialog( m_NLH );
	m_dlg.InitDialog( m_NGH );
	m_dlg.InitDialog( m_RUECK_MON_VOR_VERF );
	m_dlg.InitDialog( m_INGREDIENT_QTY );

	m_nMaxFields = m_dlg.GetFieldNumber();
}

/* void CArtikelPage5A::ResetVkn( )
{

} */

/**---------------------------------------------------------------------------*/
BOOL CArtikelPage5A::EndValidate( int *, BOOL )
{
	return TRUE;
}

// CArtikelPage5A-Meldungshandler

/**---------------------------------------------------------------------------*/
void CArtikelPage5A::InitPflege( CWnd *pView  )
{ 
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )pView)->GetBuffer();
	m_pBufZartaustria = &m_Buf->zartaustria;

	MakeDialog();

	m_WECHSELARTIKEL.SetMask ( '1', '0', m_pBufZartaustria->WECHSELARTIKEL);
	m_BUENDELPACKUNG.SetMask ( '1', '0', m_pBufZartaustria->BUENDELPACKUNG);
	m_WAFO.SetMask ( '1', '0', m_pBufZartaustria->NACHLIEFERUNG);
	m_CHARGE.SetMask ( '1', '0', m_pBufZartaustria->CHARGENARTIKEL);
	m_DBESORGER.SetMask( 1, 0, &m_pBufZartaustria->DEUTSCHLANDBESORGER);

	strcpy( m_cOekoKz, CResString::ex().getStrTblText(IDS_STRING316) );
	m_OELHV_OEKOKZ.SetMask ( m_cOekoKz, 2, m_pBufZartaustria->OELHV_OEKOKZ );

	m_OELHV_GRUPPE.SetMask 		(ED_CHAR,
								 ED_CLINPUT,
			                     m_pBufZartaustria->OELHV_GRUPPE,
				                 6,
                                 new ChMaskNum);

	m_OELHV_SORT.SetMask 		(ED_CHAR,
								 ED_CLINPUT,
			                     m_pBufZartaustria->OELHV_SORT,
				                 4,
                                 new ChMaskNum);

	m_HV_BOX.SetMask ( _strdup(CResString::ex().getStrTblText(IDS_STRING317)) , m_pBufZartaustria->HV_BOX );

	m_MEDPROD_ABGVO.SetMask  (" 1234", m_pBufZartaustria->MEDPROD_ABG_VERORD);
	m_MEDPROD_KLASSE.SetMask (" 12345678ABCDEFGHIJKOPQRSTUV", m_pBufZartaustria->MEDPROD_KLASSE);

	m_VERTRBIND_PLPL.SetMask		( '1', '0', m_pBufZartaustria->VERTRBIND_PLPL);
	m_VERTRBIND_S1S5.SetMask		( '1', '0', m_pBufZartaustria->VERTRBIND_S1S5);
	m_VERTRBIND_VPL.SetMask			( '1', '0', m_pBufZartaustria->VERTRBIND_VPL);
	m_VERTRBIND_SP.SetMask			( '1', '0', m_pBufZartaustria->VERTRBIND_SP);
	m_VERTRBIND_NEUFORM.SetMask		( '1', '0', m_pBufZartaustria->VERTRBIND_NEUFORM);
	m_VERTRBIND_BEIERSDORF.SetMask	( '1', '0', m_pBufZartaustria->VERTRBIND_BDORF);

	m_VERTRBIND_COMPTANT.SetMask(" AB", m_pBufZartaustria->VERTRBIND_COMPTANT, 0 );   

	m_SG_SUBSTANZ.SetMask			( '1', '0', m_pBufZartaustria->SG_SUBSTANZ);
	m_DROGENAGS_KAT1.SetMask		( '1', '0', m_pBufZartaustria->DROGENAGS_KAT1);
	m_DROGENAGS_KAT2.SetMask		( '1', '0', m_pBufZartaustria->DROGENAGS_KAT2);
	m_DROGENAGS_KAT3.SetMask		( '1', '0', m_pBufZartaustria->DROGENAGS_KAT3);

	m_NLH.SetMask ( '1', '0', m_pBufZartaustria->NICHT_LIEFERBAR);
	m_NGH.SetMask ( '1', '0', m_pBufZartaustria->NICHT_GELIEFERT);

	m_RUECK_MON_VOR_VERF.SetMask(ED_CHAR,
								 ED_LEADZERO,
			                     m_pBufZartaustria->RUECK_MON_VOR_VERF,
				                 1,
                                 new ChMaskNum);

	m_INGREDIENT_QTY.SetMask (ED_DBL,
                              ED_NORMAL,
							  &m_pBufZartaustria->INGREDIENTQTY,
                              L_ZARTAUSTRIA_INGREDIENTQTY + 1,
                              N_ZARTAUSTRIA_INGREDIENTQTY,
                              new ChMaskDblPos );

	m_GH_LAGERUNG_VERBOTEN.SetMask			( 1, 0, &m_pBufZartaustria->GH_LAGERUNG_VERBOTEN);
	
	m_bInitialized = TRUE; 
}

/**---------------------------------------------------------------------------*/
void CArtikelPage5A::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CArtikelPage5A::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage5A::EnableFields( BOOL bEnab )
{   
	m_dlg.EnableFields( bEnab );

	// Chargenartikel wird ab sofort für alle in ArtikelPage2 gepflegt
	m_CHARGE.EnableWindow(false);

	// diese Felder werden nicht mehr verwendet
	m_OELHV_GRUPPE.EnableWindow(false);
	m_OELHV_OEKOKZ.EnableWindow(false);
	m_OELHV_SORT.EnableWindow(false);
}

void CArtikelPage5A::ShowFields( )
{
	FillComboBox();

	m_dlg.ShowFields();

	OnPbDBesorger();
}

void CArtikelPage5A::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage5A::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

void CArtikelPage5A::ActivateField( int nr )
{
	m_dlg.ActivateField( nr );
}

BOOL CArtikelPage5A::Validate( BOOL bMeldung )
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
// CArtikelPage5A message handlers

BOOL CArtikelPage5A::OnSetActive()
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


BOOL CArtikelPage5A::OnKillActive()
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
  
void CArtikelPage5A::FillComboBox()
{
	m_OELHV_OEKOKZ.ResetContent();
	m_HV_BOX.ResetContent();
	m_VERTRBIND_COMPTANT.ResetContent();
	m_MEDPROD_ABGVO.ResetContent();
	m_MEDPROD_KLASSE.ResetContent();

	m_OELHV_OEKOKZ.AddString(" ");
	m_OELHV_OEKOKZ.AddString(CResString::ex().getStrTblText(IDS_STRING10052));
	m_OELHV_OEKOKZ.AddString(CResString::ex().getStrTblText(IDS_STRING10053));

	m_HV_BOX.AddString(CResString::ex().getStrTblText(IDS_STRING10054));
	m_HV_BOX.AddString(CResString::ex().getStrTblText(IDS_STRING10055));
	m_HV_BOX.AddString(CResString::ex().getStrTblText(IDS_STRING10056));
	m_HV_BOX.AddString(CResString::ex().getStrTblText(IDS_STRING10057));
	m_HV_BOX.AddString(CResString::ex().getStrTblText(IDS_STRING10058));

	m_VERTRBIND_COMPTANT.AddString(CResString::ex().getStrTblText(IDS_STRING10059));
	m_VERTRBIND_COMPTANT.AddString(CResString::ex().getStrTblText(IDS_STRING10060));
	m_VERTRBIND_COMPTANT.AddString(CResString::ex().getStrTblText(IDS_STRING10061));

	m_MEDPROD_ABGVO.AddString(" ");
	m_MEDPROD_ABGVO.AddString(CResString::ex().getStrTblText(IDS_STRING1333));
	m_MEDPROD_ABGVO.AddString(CResString::ex().getStrTblText(IDS_STRING1334));
	m_MEDPROD_ABGVO.AddString(CResString::ex().getStrTblText(IDS_STRING1335));
	m_MEDPROD_ABGVO.AddString(CResString::ex().getStrTblText(IDS_STRING1336));
	
	m_MEDPROD_KLASSE.AddString(" ");
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_ART5A_MEDPROD_KL_1));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_ART5A_MEDPROD_KL_2));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_ART5A_MEDPROD_KL_3));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_ART5A_MEDPROD_KL_4));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_ART5A_MEDPROD_KL_5));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_ART5A_MEDPROD_KL_6));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_ART5A_MEDPROD_KL_7));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_ART5A_MEDPROD_KL_8));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1337));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1338));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1339));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1340));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1341));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1342));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1343));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1344));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1345));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1346));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1523));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1524));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1525));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1526));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1527));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1528));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1529));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1530));
	m_MEDPROD_KLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1531));
}

void CArtikelPage5A::OnPbDBesorger() 
{
	// as there is no read-only possibility for CheckBoxes and control should not be disabled --> workaround:
	m_DBESORGER.SetCheck(((CArtikelView* )m_pView)->m_Doc.GetBuffer()->zartaustria.DEUTSCHLANDBESORGER);
}

// ArtikelPage5D.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "EkZdp.h"
#include "ArtikelPage5D.h"
#include "hSelectDialog.h"
#include "ArtikelView.h"

#include <phxlib/AtxSelCtrl.h> 

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDblPos.h>
#include <eklibs/hamfcs/hMskDate.h>

#include "FeldBreite.h"

#include <phxlib/cppeartcategorySelCtrl.h>

// CArtikelPage5D-Dialogfeld

IMPLEMENT_DYNCREATE(CArtikelPage5D, CPropertyPageMultiLang)

// CArtikelPage5D::CArtikelPage5D()
CArtikelPage5D::CArtikelPage5D() : ChPflegePage(CArtikelPage5D::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInitialized = FALSE;
}

CArtikelPage5D::~CArtikelPage5D()
{
}

void CArtikelPage5D::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage5D)
	DDX_Control(pDX, IDC_CK_ARTIKEL_ISFESTB,			m_ISFESTB);
	DDX_Control(pDX, IDC_CK_ARTIKEL_AUTIDEM,			m_AUTIDEM);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ANBABSCHL,			m_ANBABSCHL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_BSSICHG,			m_BSSICHG);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATBSSICHG,			m_DATBSSICHG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ZULASS_GENER,		m_ZULASS_GENER);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ABSCHLAG_130,		m_ABSCHLAG_130);
	DDX_Control(pDX, IDC_CK_ARTIKEL_PREISEMPFEHLUNG,	m_PREISEMPFEHLUNG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_INDIKATOR,			m_INDIKATOR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NIEDRIGSPANNE,		m_NIEDRIGSPANNE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ELAC,				m_ELAC);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NATURALRABATT,		m_NATURALRABATT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_PERF,				m_PERF);
	DDX_Control(pDX, IDC_CK_ARTIKEL_LABORARTIKEL,		m_LABORARTIKEL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SICHTWAHL,			m_SICHTWAHL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_PRISMAEDISK,		m_PRISMAEDISK);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PERSONALRABATT,		m_PERSONALRABATT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRISMAEWOCHE,		m_PRISMAEWOCHE);
	DDX_Control(pDX, IDC_CB_ARTIKEL_MVDAARTIKEL,		m_MVDAARTIKEL);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_LIEFERBAR_AB, m_DATUM_LIEFERBAR_AB );
	DDX_Control(pDX, IDC_ED_ARTIKEL_ZULASSUNGSNUMMER,	m_ZULASSUNGSNUMMER);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PPN,				m_PPN);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ABSCHLAG_130A2,		m_ABSCHLAG_130A2);
	DDX_Control(pDX, IDC_CK_ARTIKEL_PILOT_SECURPH,		m_PILOT_SECURPH);
	DDX_Control(pDX, IDC_CK_ARTIKEL_AUSNAHME_52B,		m_AUSNAHME_52B);	
	DDX_Control(pDX, IDC_CK_ARTIKEL_TREZEP,				m_TREZEP);
	DDX_Control(pDX, IDC_CB_ARTIKEL_AMG47,				m_AMG47);
	DDX_Control(pDX, IDC_CK_ARTIKEL_AMG59,				m_AMG59);
	DDX_Control(pDX, IDC_CK_ARTIKEL_AMG_AUSNAHMEREG2,	m_AMG_AUSNAHMEREG);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ALC_STRENGTH,		m_ALC_STRENGTH);
	DDX_Control(pDX, IDC_ED_ARTIKEL_VINTAGE,			m_VINTAGE);		
	DDX_Control(pDX, IDC_CK_ARTIKEL_IS_HI_ARTICLE,		m_ISHIART);
	DDX_Control(pDX, IDC_CK_ARTIKEL_CMI,				m_CMI);
	DDX_Control(pDX, IDC_CK_ORPHANDRUG	,				m_ORPHANDRUG);
	DDX_Control(pDX, IDC_CB_AUSNAHMEABSCHLAGPFLICHT	,	m_AUSNAHMEABSCHLAGPFLICHT);
	DDX_Control(pDX, IDC_CK_BEDINGTEZULASSUNG	,		m_BEDINGTEZULASSUNG);
	DDX_Control(pDX, IDC_ED_A00ZINNR ,					m_ZULASSUNGSINHABERNR);
	DDX_Control(pDX, IDC_CB_AMNOGVERFAHREN	,			m_AMNOGVERFAHREN);
	DDX_Control(pDX, IDC_ED_A00OEVNR	,				m_OERTLICHERVERTRETERNR);
	DDX_Control(pDX, IDC_CK_ZULASSUNGAUSNAHMEFAELLE	,	m_ZULASSUNGAUSNAHMEFAELLE);
	DDX_Control(pDX, IDC_CB_AM_KINDER	,				m_AM_KINDER);
	DDX_Control(pDX, IDC_CB_AM_KRIT_WIRKSTOFF	,		m_AM_KRIT_WIRKSTOFF);
	DDX_Control(pDX, IDC_CK_ALTERSGERECHTE_DFORM	,	m_ALTERSGERECHTE_DFORM);
	DDX_Control(pDX, IDC_CK_AUFGEHOBENER_FESTBETRAG	,	m_AUFGEHOBENER_FESTBETRAG);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtikelPage5D, CPropertyPageMultiLang)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_IS_HI_ARTICLE, OnPbHiArticle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage5D::MakeDialog()
{
	m_dlg.InitDialog( m_ANBABSCHL );

	m_Pos_ARTIKEL_BSSICHG = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_BSSICHG );

	m_dlg.InitDialog( m_AUTIDEM );
	m_dlg.InitDialog( m_ISFESTB );
	m_dlg.InitDialog( m_DATBSSICHG );

	m_dlg.InitDialog( m_ZULASS_GENER );
	m_dlg.InitDialog( m_ABSCHLAG_130 );

	m_dlg.InitDialog( m_PREISEMPFEHLUNG );
	m_dlg.InitDialog( m_INDIKATOR );
	m_dlg.InitDialog( m_NIEDRIGSPANNE );
	m_dlg.InitDialog( m_ELAC );
	m_dlg.InitDialog( m_NATURALRABATT );
	m_dlg.InitDialog( m_PERF );
	m_dlg.InitDialog( m_LABORARTIKEL );
	m_dlg.InitDialog( m_SICHTWAHL );
	m_dlg.InitDialog( m_PRISMAEDISK );

	m_dlg.InitDialog( m_PERSONALRABATT );
	m_dlg.InitDialog( m_PRISMAEWOCHE );
	m_dlg.InitDialog( m_ALC_STRENGTH );
	m_dlg.InitDialog( m_VINTAGE );
		
	m_dlg.InitDialog( m_MVDAARTIKEL );
	m_dlg.InitDialog( m_DATUM_LIEFERBAR_AB );
	m_dlg.InitDialog( m_ZULASSUNGSNUMMER );
	
	m_dlg.InitDialog( m_PPN );
	m_dlg.InitDialog( m_ABSCHLAG_130A2 );
	m_dlg.InitDialog( m_PILOT_SECURPH );
	m_dlg.InitDialog( m_AUSNAHME_52B );

	m_dlg.InitDialog( m_TREZEP );
	m_dlg.InitDialog( m_AMG47 );
	m_dlg.InitDialog( m_AMG59 );
	m_dlg.InitDialog( m_AMG_AUSNAHMEREG );
	m_dlg.InitDialog( m_ISHIART );
	m_dlg.InitDialog( m_CMI );
	m_dlg.InitDialog (m_ORPHANDRUG );
	m_dlg.InitDialog (m_AUSNAHMEABSCHLAGPFLICHT);
	m_dlg.InitDialog (m_BEDINGTEZULASSUNG);
	m_dlg.InitDialog (m_ZULASSUNGSINHABERNR);
	m_dlg.InitDialog (m_AMNOGVERFAHREN);
	m_dlg.InitDialog (m_OERTLICHERVERTRETERNR);
	m_dlg.InitDialog (m_ZULASSUNGAUSNAHMEFAELLE);
	m_dlg.InitDialog (m_AM_KINDER);
	m_dlg.InitDialog (m_AM_KRIT_WIRKSTOFF);
	m_dlg.InitDialog (m_ALTERSGERECHTE_DFORM);
	m_dlg.InitDialog (m_AUFGEHOBENER_FESTBETRAG);

	m_nMaxFields = m_dlg.GetFieldNumber();
}

void CArtikelPage5D::ResetVkn( )
{
	m_RD_PPEARTCATEGORY.Reset();
}

/**---------------------------------------------------------------------------*/
BOOL CArtikelPage5D::EndValidate( int *, BOOL )
{
	return TRUE;
}

class CV_ARTIKEL_PrismaEWoche : public ChValBase
{
public:
	CV_ARTIKEL_PrismaEWoche( CArtikelPage5D* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage5D*)m_pWnd)->ShowPrismaEWoche( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage5D*)m_pWnd)->SuchePrismaEWoche( );
	}
};

// CArtikelPage5D-Meldungshandler

/**---------------------------------------------------------------------------*/
void CArtikelPage5D::InitPflege( CWnd *pView  )
{ 
	CArtikelPage5D* pThisView = this;
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )pView)->GetBuffer();
	m_pBufZartikel		= &m_Buf->zartikel;
	m_pBufZulassungsnr	= &m_Buf->carticlecodes[6];	// code_type = 7
	m_pBufCarticleext	= &m_Buf->carticleext;

	MakeDialog();

	m_BSSICHG.SetMask		('1', '0', m_pBufZartikel->BSSICHG );
	m_ANBABSCHL.SetMask		('1', '0', m_pBufZartikel->ANBIETERABSCHLAG );
	m_AUTIDEM.SetMask		('1', '0', m_pBufZartikel->AUTIDEMARTIKEL );
	m_ISFESTB.SetMask		('1', '0', m_pBufZartikel->FESTBETRARTIKEL );

	m_DATBSSICHG.SetMask	(ED_LDATE,
							 ED_NORMAL,
							 &m_pBufZartikel->DATUM_ABSCHLAG,
							 L_LDATUM,
							 new ChMaskLDate);

	m_ZULASS_GENER.SetMask		('1', '0', m_pBufZartikel->ZULASS_GENER );
	m_ABSCHLAG_130.SetMask		('1', '0', m_pBufZartikel->ABSCHLAG_130 );

	m_PREISEMPFEHLUNG.SetMask	('1', '0', m_pBufZartikel->PREISEMPFEHLUNG );
	m_INDIKATOR.SetMask	 		('1', '0', m_pBufZartikel->INDIKATOR );
	m_NIEDRIGSPANNE.SetMask		('1', '0', m_pBufZartikel->NIEDRSPANNE_SONST );
	m_ELAC.SetMask				('1', '0', m_pBufZartikel->NIEDRSPANNE_ELAC );
	m_NATURALRABATT.SetMask		('1', '0', m_pBufZartikel->NATURALRABATT);
	m_PERF.SetMask				('1', '0', m_pBufZartikel->PERF );
	m_LABORARTIKEL.SetMask		('1', '0', m_pBufZartikel->LABORARTIKEL );
	m_SICHTWAHL.SetMask			('1', '0', m_pBufZartikel->SICHTWAHL );
	m_PRISMAEDISK.SetMask		('1', '0', m_pBufZartikel->PRISMAEDISK );

	m_PERSONALRABATT.SetMask	(ED_DBL,
								 ED_NORMAL,
								 &m_pBufZartikel->PERSONALRABATT,
								 L_ZARTIKEL_PERSONALRABATT + 1,
								 N_ZARTIKEL_PERSONALRABATT,
								 new ChMaskDblPos );

	m_PRISMAEWOCHE.SetMask		(ED_LONG,
								 ED_CLINPUT,
								 &m_pBufZartikel->PRISMAEWOCHE,
								 2,
								 new ChMaskNum,
								 new CV_ARTIKEL_PrismaEWoche( pThisView ));

	m_ALC_STRENGTH.SetMask		(ED_DBL,
								 ED_NORMAL,
								 &m_pBufCarticleext->ALCOHOLIC_STRENGTH,
								 L_CARTICLEEXT_ALCOHOLIC_STRENGTH + 1,
								 N_CARTICLEEXT_ALCOHOLIC_STRENGTH,
								 new ChMaskDblPos );

	m_VINTAGE.SetMask			(ED_LONG,
								 ED_CLINPUT,
								 &m_pBufCarticleext->VINTAGE,
								 4,
								 new ChMaskNum);

	m_MVDAARTIKEL.SetMask		("012345689", m_pBufZartikel->MVDAARTIKEL, 0 );

	m_DATUM_LIEFERBAR_AB.SetMask	(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufZartikel->DATUM_LIEFERBAR_AB,
                             L_LDATUM,
                             new ChMaskLDate);

	m_ZULASSUNGSNUMMER.SetMask	(ED_CHAR,
							 ED_UPPER,
			                 m_pBufZulassungsnr->ARTICLE_CODE,
				             L_CARTICLECODES_ARTICLE_CODE,
   						     new ChMaskChar );

	m_PPN.SetMask			(ED_CHAR,
							 ED_UPPER,
			                 m_pBufZartikel->PPN,
				             L_ZARTIKEL_PPN,
   						     new ChMaskChar );

	m_ABSCHLAG_130A2.SetMask	(ED_DBL,
								 ED_NORMAL,
								 &m_pBufZartikel->ABSCHLAG_130A2,
								 L_ZARTIKEL_ABSCHLAG_130A2 + 1,
								 N_ZARTIKEL_ABSCHLAG_130A2,
								 new ChMaskDblPos );

	m_PILOT_SECURPH.SetMask		( 1, 0, &m_pBufZartikel->PILOT_SECURPHARM );
	m_AUSNAHME_52B.SetMask		( 1, 0, &m_pBufZartikel->AUSNAHME_52B );
			  	    
	m_TREZEP.SetMask			('1', '0', m_pBufZartikel->TREZEPTARZNEI );

	//m_AMG47.SetMask				('1', '0', m_pBufZartikel->AMG_47 );
	m_AMG47.SetMask				("0123", m_pBufZartikel->AMG_47, 0 );
	m_AMG59.SetMask				( 1,  0, &m_pBufCarticleext->ANIMALDRUG_PROOFOBLIGATION_FLAG );
	m_AMG_AUSNAHMEREG.SetMask	('1', '0', m_pBufZartikel->AMG_AUSNAHMEREG );
	m_CMI.SetMask				( 1, 0, &m_pBufZartikel->CMI_FLAG );
	m_ORPHANDRUG.SetMask( 1, 0, &m_pBufZartikel->ORPHANDRUG);
	m_AUSNAHMEABSCHLAGPFLICHT.SetMask("012345", &m_pBufZartikel->AUSNAHMEABSCHLAGSPFLICHT);
	m_BEDINGTEZULASSUNG.SetMask( 1, 0, &m_pBufZartikel->BEDINGTEZULASSUNG);
	m_ZULASSUNGSINHABERNR.SetMask( 
									ED_LONG, 
									ED_NORMAL, 
									&m_pBufZartikel->ZULASSUNGSINHABERNR,
									5,
									0,
									new ChMaskNum
								 );
	m_AMNOGVERFAHREN.SetMask( "0123", &m_pBufZartikel->AMNOGVERFAHREN);
	m_OERTLICHERVERTRETERNR.SetMask(
										ED_LONG,
										ED_NORMAL,
										&m_pBufZartikel->OERTLICHEVERTRETERNR,
										5,
										0,
										new ChMaskNum
									);
	m_ZULASSUNGAUSNAHMEFAELLE.SetMask( 1, 0, &m_pBufZartikel->ZULASSUNGAUSNAHMEFAELLE);
	m_AM_KINDER.SetMask( "012", &m_pBufZartikel->AM_KINDER);
	m_AM_KRIT_WIRKSTOFF.SetMask( "012", &m_pBufZartikel->AM_VERSKRIT_WIRKSTOFF);
	m_ALTERSGERECHTE_DFORM.SetMask(1, 0, &m_pBufZartikel->AM_DARREICH_ALTERSGER);
	m_AUFGEHOBENER_FESTBETRAG.SetMask(1, 0, &m_pBufZartikel->AM_FESTBETR_AUFGEH);

	m_bInitialized = TRUE; 
}

/**---------------------------------------------------------------------------*/
void CArtikelPage5D::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CArtikelPage5D::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage5D::EnableFields( BOOL bEnab )
{   
	m_dlg.EnableFields( bEnab );

	// generell nicht mehr verwendet
	m_ABSCHLAG_130.EnableWindow(false);
	m_SICHTWAHL.EnableWindow(false);
	
	// generell nicht mehr verwendet
	m_PERSONALRABATT.EnableWindow(false);

	// generell nicht mehr verwendet
	m_PERF.EnableWindow(false);

	// bssichg: 23.12.2003 entfaellt wieder, da neues Gesetz
	// BSSICHG immer disnabled
	
	// bssichg: 15.11.2010 wieder pflegbar machen (Mail von Hr. Peetz)
	// m_dlg.EnableFields( m_Pos_ARTIKEL_BSSICHG, FALSE );
}

void CArtikelPage5D::OnPbHiArticle() 
{
	// as there is no read-only possibility for CheckBoxes and control should not be disabled --> workaround:
	m_ISHIART.SetCheck(((CArtikelView* )m_pView)->m_isHealthInsuranceArticle);
}

void CArtikelPage5D::ShowFields( )
{
	FillComboBox();

	m_dlg.ShowFields();

	ShowPrismaEWoche( TRUE );

	OnPbHiArticle();
}

BOOL CArtikelPage5D::ShowPrismaEWoche( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	iStat = m_RD_PPEARTCATEGORY.IPlausi( (short)m_pBufZartikel->PRISMAEWOCHE, Name,
										 &Errmld);
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_PRISMAEWOCHE )->SetWindowText( Name );

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

void CArtikelPage5D::SuchePrismaEWoche( )
{
	CppeArtCategorySelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1310), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( (short*)&m_pBufZartikel->PRISMAEWOCHE ) == 0 )
		{
			m_PRISMAEWOCHE.p_SetInput();
			m_PRISMAEWOCHE.SetFocus();
			ShowPrismaEWoche( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

void CArtikelPage5D::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage5D::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}


void CArtikelPage5D::ActivateField( int nr )
{
	m_dlg.ActivateField( nr );
}


BOOL CArtikelPage5D::Validate( BOOL bMeldung )
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

BOOL CArtikelPage5D::OnSetActive()
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


BOOL CArtikelPage5D::OnKillActive()
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
  
void CArtikelPage5D::FillComboBox()
{
	m_MVDAARTIKEL.ResetContent();

	m_MVDAARTIKEL.AddString("0");
	m_MVDAARTIKEL.AddString("1");
	m_MVDAARTIKEL.AddString("2");
	m_MVDAARTIKEL.AddString("3");
	m_MVDAARTIKEL.AddString("4");
	m_MVDAARTIKEL.AddString("5");
	m_MVDAARTIKEL.AddString("6");
	m_MVDAARTIKEL.AddString("8");
	m_MVDAARTIKEL.AddString("9");

	m_AMG47.ResetContent();

	m_AMG47.AddString("0 - nein");
	m_AMG47.AddString("1 - Abs. 6 Nr. 1 TAMG");
	m_AMG47.AddString("2 - Abs. 6 Nr. 2 TAMG");
	m_AMG47.AddString("3 - Abs. 6 Nr. 1 und 2 TAMG");

	m_AUSNAHMEABSCHLAGPFLICHT.ResetContent();

	m_AUSNAHMEABSCHLAGPFLICHT.AddString("       keine Angabe");
	m_AUSNAHMEABSCHLAGPFLICHT.AddString("00 - kein Impfstoff");
	m_AUSNAHMEABSCHLAGPFLICHT.AddString("01 - Impfstoff abschlagspfl.");
	m_AUSNAHMEABSCHLAGPFLICHT.AddString("02 - Impfstoff nicht abschlagspfl.");
	m_AUSNAHMEABSCHLAGPFLICHT.AddString("03 - Impfstoff abschlagspfl., Abschlag nicht ermittelbar");
	m_AUSNAHMEABSCHLAGPFLICHT.AddString("04 - Impfstoff nicht abschlagspfl., da Vertrieb nur in DTL");

	m_AMNOGVERFAHREN.ResetContent();

	m_AMNOGVERFAHREN.AddString("       keine Angabe");
	m_AMNOGVERFAHREN.AddString("00 - nein");
	m_AMNOGVERFAHREN.AddString("01 - ja, befindet sich im Bewertungsverfahren");
	m_AMNOGVERFAHREN.AddString("02 - ja, Bewertungsverfahren ist abgeschlossen");

	m_AM_KINDER.ResetContent();

	m_AM_KINDER.AddString("00 = Nein");
	m_AM_KINDER.AddString("01 = Ja Festbetrag aufgehoben");
	m_AM_KINDER.AddString("02 = Ja vormals kein Festbetrag");

	m_AM_KRIT_WIRKSTOFF.ResetContent();

	m_AM_KRIT_WIRKSTOFF.AddString("00 = Nein");
	m_AM_KRIT_WIRKSTOFF.AddString("01 = Ja Festbetrag aufgehoben");
	m_AM_KRIT_WIRKSTOFF.AddString("02 = Ja vormals kein Festbetrag");
}

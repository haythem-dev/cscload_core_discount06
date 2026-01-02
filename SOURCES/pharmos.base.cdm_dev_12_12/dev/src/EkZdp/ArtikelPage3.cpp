// ArtikelPage3.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtikelPage3.h"

#include "hSelectDialog.h"
#include "ArtikelView.h"

#include <phxlib/ArtkatgSelCtrl.h>
#include <phxlib/ZdkwgrSelCtrl.h>
#include <phxlib/ZdktgrSelCtrl.h>
#include <phxlib/ZdkbtmSelCtrl.h>
#include <phxlib/SaisonwgSelCtrl.h>
#include <phxlib/ZdkwirSelCtrl.h>
#include <phxlib/ZrabgrpSelCtrl.h>
#include <phxlib/CspecarticletypesSelCtrl.h>
#include <phxlib/AtcSelCtrl.h> 

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDate.h>
#include <phxlib/PhxUtil.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtikelPage3 property page

IMPLEMENT_DYNCREATE(CArtikelPage3, CPropertyPageMultiLang)

CArtikelPage3::CArtikelPage3() : ChPflegePage(CArtikelPage3::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage3)
	//}}AFX_DATA_INIT

	m_bInitialized = FALSE;
    m_csAlleSaisonwgs.SetSize(3);	// Anzahl Saison-Warengruppen
}

CArtikelPage3::~CArtikelPage3()
{
}

void CArtikelPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage3)
	DDX_Control(pDX, IDC_ED_ARTIKEL_IMSWGR,				m_IMSWGR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EIGENEWGR,			m_EIGENEWGR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_SAISONWGR,			m_SAISONWGR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_SAISONWGR2,			m_SAISONWGR2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_SAISONWGR3,			m_SAISONWGR3);
	DDX_Control(pDX, IDC_ED_ARTIKEL_THERAPIEGRUPPE,		m_THERAPIEGRUPPE );
	DDX_Control(pDX, IDC_ED_ARTIKEL_BTMGRUPPE,			m_BTMGRUPPE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_WIRKSTOFF_NR,		m_WIRKSTOFF_NR);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PRODUKTART,			m_PRODUKTART);
	DDX_Control(pDX, IDC_ED_ARTIKEL_RABATTGRP,			m_RABATTGRP);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PRODUKTART,			m_PRODUKTART);
	DDX_Control(pDX, IDC_ED_ARTIKEL_SPECARTTYP,			m_SPECARTTYP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ABDACODE,			m_ABDACODE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_KATALOG,			m_KATALOG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SORTIMENT_1,		m_SORTIMENT_1);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SORTIMENT_2,		m_SORTIMENT_2);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SORTIMENT_3,		m_SORTIMENT_3);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SORTIMENT_4,		m_SORTIMENT_4);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SORTIMENT_5,		m_SORTIMENT_5);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ARZNEIMITTEL,		m_ARZNEIMITTEL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_MEDIZINPROD,		m_MEDIZINPRODUKT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_CEKENN,				m_CE_KENNZEICHEN);
	DDX_Control(pDX, IDC_CK_ARTIKEL_HILVSMV,			m_HILFSMV);
	DDX_Control(pDX, IDC_CK_ARTIKEL_IMPSTOFF,			m_IMPFSTOFF);
	DDX_Control(pDX, IDC_CK_ARTIKEL_REZARZNEI,			m_REZEPTURARZNEI);
	DDX_Control(pDX, IDC_CK_ARTIKEL_HIGH_THERAPEUTIC_VAL,m_HIGH_THERAPEUTIC_VAL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_MEDIZINISCHE_GASE,	m_MEDIZINISCHE_GASE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_HOMOEO,				m_HOMOEO);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ANTHRO,				m_ANTHRO);
	DDX_Control(pDX, IDC_CK_ARTIKEL_PHYTO,				m_PHYTO);
	DDX_Control(pDX, IDC_CK_ARTIKEL_STERIL,				m_STERIL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_KOSMETIKUM,			m_KOSMETIKUM);
	DDX_Control(pDX, IDC_CK_ARTIKEL_BIOSIEGEL,			m_BIOSIEGEL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ANTIBIOTIKUM,		m_ANTIBIOTIKUM);
	DDX_Control(pDX, IDC_CB_ARTIKEL_KONTRAZEPT,			m_KONTRAZEPTIVUM);
	DDX_Control(pDX, IDC_CB_ARTIKEL_BIOTECH_ARZNEI,		m_BIOTECH_ARZNEI);	
	DDX_Control(pDX, IDC_CB_ARTIKEL_PSYCHOTROP,			m_PSYCHOTROP);
	DDX_Control(pDX, IDC_CB_ARTIKEL_ABGABEBEST_IFA,		m_ABGABEBEST_IFA);
	DDX_Control(pDX, IDC_CB_ARTIKEL_NEGATIVLISTE,		m_NEGATIVLISTE);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PRIVATSORTIMENT,	m_PRIVATSORTIMENT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_CODE_ATC,			m_CODE_ATC);
	DDX_Control(pDX, IDC_ED_ARTIKEL_CODE_ATC_SUFFIX_HR, m_CODE_ATC_SUFFIX_HR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_CODE_OEKO,			m_CODE_OEKO);
	DDX_Control(pDX, IDC_ED_ARTIKEL_FMD_AB_VERFALL,		m_DATUM_FMDPFLICHT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_MP31,				m_BT_MP31);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERB31,				m_BT_VERB31);
	DDX_Control(pDX, IDC_CB_ARTIKEL_MPKLASSE,			m_MPKLASSE);
	DDX_Control(pDX, IDC_CB_ARTIKEL_FMD,				m_FMD);
	DDX_Control(pDX, IDC_CB_ARTIKEL_INVITROKLASSE,		m_INVITROKLASSE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_WIRKSTOFF3,			m_WIRKSTOFF);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SERNUMTRAC,			m_SER_NUM_TRACK);
	DDX_Control(pDX, IDC_CB_NOVELFOOD         ,			m_NOVELFOOD);
	DDX_Control(pDX, IDC_CK_WUNDPRODUKT       ,			m_WUNDPRODUKT);
	DDX_Control(pDX, IDC_CB_NEUARTIGETHERAPIEN,			m_NEUARTIGETHERAPIEN);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CArtikelPage3, CPropertyPageMultiLang)
	//{{AFX_MSG_MAP(CArtikelPage3)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_SORTIMENT_1, OnCkArtikelSortiment_1)
	ON_CBN_SELCHANGE(IDC_CB_ARTIKEL_PSYCHOTROP, OnSelchangeCbPSYCHOTROP)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_MP31, OnPbIsMP31)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_VERB31, OnPbIsVERB31)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage3::MakeDialog()
{
	m_dlg.InitDialog( m_IMSWGR );
	m_dlg.InitDialog( m_EIGENEWGR );
	m_dlg.InitDialog( m_SAISONWGR );
	m_dlg.InitDialog( m_SAISONWGR2 );
	m_dlg.InitDialog( m_SAISONWGR3 );
	m_dlg.InitDialog( m_THERAPIEGRUPPE );
	m_dlg.InitDialog( m_BTMGRUPPE );
	m_dlg.InitDialog( m_WIRKSTOFF_NR );

	m_Pos_PRODUKTART = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_PRODUKTART );

	m_Pos_RABATTGRUPPE = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_RABATTGRP );

	m_dlg.InitDialog( m_SPECARTTYP );

	m_dlg.InitDialog( m_ABDACODE );
	m_dlg.InitDialog( m_KATALOG );
	m_dlg.InitDialog( m_DATUM_FMDPFLICHT );

	m_dlg.InitDialog( m_SORTIMENT_1 );
	m_dlg.InitDialog( m_SORTIMENT_2 );
	m_dlg.InitDialog( m_SORTIMENT_3 );
	m_dlg.InitDialog( m_SORTIMENT_4 );
	m_dlg.InitDialog( m_SORTIMENT_5 );

	m_dlg.InitDialog( m_ARZNEIMITTEL );
	m_dlg.InitDialog( m_MEDIZINPRODUKT );
	m_dlg.InitDialog( m_CE_KENNZEICHEN );
	m_dlg.InitDialog( m_HILFSMV );
	m_dlg.InitDialog( m_IMPFSTOFF );
	m_dlg.InitDialog( m_REZEPTURARZNEI );
	m_dlg.InitDialog( m_HIGH_THERAPEUTIC_VAL );
	m_dlg.InitDialog( m_MEDIZINISCHE_GASE );
	m_dlg.InitDialog( m_HOMOEO );
	m_dlg.InitDialog( m_ANTHRO );
	m_dlg.InitDialog( m_PHYTO );
	m_dlg.InitDialog( m_FMD );
	m_dlg.InitDialog( m_STERIL );
	m_dlg.InitDialog( m_KOSMETIKUM );
	m_dlg.InitDialog( m_BIOSIEGEL );
	m_dlg.InitDialog( m_ANTIBIOTIKUM );

	m_dlg.InitDialog( m_KONTRAZEPTIVUM );
	m_dlg.InitDialog( m_BIOTECH_ARZNEI );

	m_Pos_PSYCHOTROP = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_PSYCHOTROP );

	m_dlg.InitDialog( m_ABGABEBEST_IFA );
	m_dlg.InitDialog( m_NEGATIVLISTE );
	m_dlg.InitDialog( m_PRIVATSORTIMENT );

	m_dlg.InitDialog( m_CODE_ATC );
	m_dlg.InitDialog( m_CODE_ATC_SUFFIX_HR );
	m_dlg.InitDialog( m_CODE_OEKO );

	m_dlg.InitDialog( m_BT_MP31 );
	m_dlg.InitDialog( m_BT_VERB31 );
	//m_dlg.InitDialog( m_MPKLASSE );
	//m_dlg.InitDialog( m_INVITROKLASSE );
	m_dlg.InitDialog( m_WIRKSTOFF );
	m_dlg.InitDialog( m_SER_NUM_TRACK );
	m_dlg.InitDialog( m_NOVELFOOD );
	m_dlg.InitDialog( m_NEUARTIGETHERAPIEN );
	m_dlg.InitDialog( m_WUNDPRODUKT );

	m_nMaxFields = m_dlg.GetFieldNumber();
}

/////////////////////////////////////////////
// Verknuepfungen zuruecksetzen

void CArtikelPage3::ResetVkn( )
{
	m_RD_IMSWGR.Reset();
	m_RD_SAISONWGR.Reset();
	m_RD_SAISONWGR2.Reset();
	m_RD_SAISONWGR3.Reset();
	m_RD_THERAPIEGRUPPE.Reset();
	m_RD_BTMGRUPPE.Reset();
	m_RD_EIGENEWGR.Reset();
	m_RD_WIRKSTOFF.Reset();
	m_RD_RABATTGRP.Reset();
	m_RD_SPECARTTYP.Reset();
	m_RD_ATC.Reset();
}

/////////////////////////////////////////////////////////////
//  Verknuepfungen lesen

// ImsWgr

BOOL CArtikelPage3::TestImsWgr( BOOL bMeldung )
{
	BOOL bOk = m_pBufImswg->WARENGRUPPE[4] != '0';
	if ( !bOk && bMeldung )
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING287) );
	return bOk;
}

BOOL CArtikelPage3::ShowImsWgr( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Rabgrp;
	CString Errmld;

	iStat = m_RD_IMSWGR.IPlausi( m_pBufImswg->WARENGRUPPE, Name, Rabgrp, &Errmld);

	if (iStat == 0 && !Rabgrp.IsEmpty())
	{
		Name.Append("                    RG");
		Name += Rabgrp;
	}

	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_IMSWGR )->SetWindowText( Name );

	// Font aendern (in den mehrzeiligen Statics kleiner, um etwas Platz auf dem Dialog zu schaffen)
	// nur, wenn die Seite auch schon aktiv war, sonst schmiert das Programm ab
	if (((CArtikelView* )m_pView)->WasPageActive(2) == TRUE)
	{
		CEkZdpApp* pApp = (CEkZdpApp*) AfxGetApp();
		m_pSmallFont = pApp->GetSmallFont();
		GetDlgItem( IDC_ST_ARTIKEL_IMSWGR )->SetFont( m_pSmallFont );
	}

	/* in Deutschland automatischer Update auf Rabattgruppe bei Änderung IMS-Warengruppe
	if (IsCountry("D") && strncmp(m_pBufRabattgruppe->WARENGRUPPE, Rabgrp, 3) != 0)
	{
		strcpy (m_pBufRabattgruppe->WARENGRUPPE, Rabgrp);
		m_dlg.DataExchangeFromBuffer( m_Pos_RABATTGRUPPE );
		ShowRabGr(bShow, bMeldung);
	}*/

	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage3::SucheImsWgr( )
{
	CArtkatgSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING288), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufImswg->WARENGRUPPE ) == 0 )
		{
			m_IMSWGR.p_SetInput();
			m_IMSWGR.SetFocus();
			ShowImsWgr( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// Skontofaehig aus eigener Wgr uebernehmen
void CArtikelPage3::SetSkontofaehig( )
{
	if ( !m_EIGENEWGR.WasCharPressed( ) ) 
		return;

	if ( m_nSkontofaehig == -1 ) 
		return;

	// für Wholesale Schweiz soll Skontofähigkeit nicht aus der Warengruppe übernommen, sondern auf Artikelebene gepflegt werden
	if (IsCountry("CH") &&
		!IsPrewhole())
		return;

	if ( m_nSkontofaehig == 1 )
		m_pBufZartikel->SKONTOFAEHIG[0] = '1';
	else
		m_pBufZartikel->SKONTOFAEHIG[0] = '0';

	// auf Seite 1 im Dialogfeld aktivieren
	CArtikelPage1 *pP1;
	pP1 = (CArtikelPage1 *)((CArtikelView*)m_pView)->GetPage(0);
	pP1->Set_Skontofaehig();

/*
	// wenn auf Seite 0 ( CArtikelPage1 )
	if ( ((CArtikelView*)m_pView)->GetActivePageIndex( ) == 0 )
	{
		CArtikelPage1 *pP1;
		pP1 = (CArtikelPage1 *)((CArtikelView*)m_pView)->GetPage(0);
		pP1->ShowFields();
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING289) );
	}
*/
}
// Taxpflichtig aus eigener Wgr uebernehmen

void CArtikelPage3::SetTaxpfl( )
{
	// nur in Österreich !!!
	if (!IsCountry("A")) return;

	if ( !m_EIGENEWGR.WasCharPressed( ) ) return;

	if ( m_nTaxpflichtig == '-' ) return;

	m_pBufZartikel->TAXPFL[0] = m_nTaxpflichtig;

	// auf Seite 1 im Dialogfeld aktivieren
	CArtikelPage1 *pP1;
	pP1 = (CArtikelPage1 *)((CArtikelView*)m_pView)->GetPage(0);
	pP1->Set_Taxpfl();
}

//  eigene WGR

BOOL CArtikelPage3::TestEigeneWgr( BOOL bMeldung )
{
	BOOL bOk = m_pBufEigenewg->WARENGRUPPE[4] != '0';
	if ( !bOk && bMeldung )
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING287) );
	return bOk;
}

BOOL CArtikelPage3::ShowEigeneWgr( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Skontof;
	CString Taxgrp;
	CString Errmld;

	if (IsCountry("A"))
	{
		iStat = m_RD_EIGENEWGR.IPlausiAustria( m_pBufEigenewg->WARENGRUPPE,
												Name, Skontof, Taxgrp, &Errmld);
	}
	else if (IsCountry("CH"))
	{
		iStat = m_RD_EIGENEWGR.IPlausiCH( m_pBufEigenewg->WARENGRUPPE,
										Name, Skontof, &Errmld);
	}
	else
	{
		iStat = m_RD_EIGENEWGR.IPlausi( m_pBufEigenewg->WARENGRUPPE,
										Name, Skontof, &Errmld);
	}

	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_EIGENEWGR )->SetWindowText( Name );

	// Font aendern (in den mehrzeiligen Statics kleiner, um etwas Platz auf dem Dialog zu schaffen)
	// nur, wenn die Seite auch schon aktiv war, sonst schmiert das Programm ab
	if (((CArtikelView* )m_pView)->WasPageActive(2) == TRUE)
	{
		CEkZdpApp* pApp = (CEkZdpApp*) AfxGetApp();
		m_pSmallFont = pApp->GetSmallFont();
		GetDlgItem( IDC_ST_ARTIKEL_EIGENEWGR )->SetFont( m_pSmallFont );
	}

	if ( (iStat > 1 || (iStat == 1 && IsCountry("F") && !IsPrewhole())) && bMeldung && m_bEigeneWgrMeldung ) MsgBoxOK( Errmld );

	if ( iStat == 0 )
	{
		if ( Skontof.GetAt(0) == 'J' )
			m_nSkontofaehig = 1;
		else
			m_nSkontofaehig = 0;

		if (IsCountry("A"))
		{
			m_nTaxpflichtig = Taxgrp.GetAt(0);
		}
	}
	else if ( iStat == 1 )   // WgrNr = 0
	{
		m_nSkontofaehig = 0;
		m_nTaxpflichtig = '0';
	}
	else
	{
		m_nSkontofaehig = -1;
		m_nTaxpflichtig = '-';
	}

	if ( !m_bEigeneWgrMeldung ) return TRUE; // dadurch wird PostProc() durchlaufen
	
	if (IsCountry("F") && !IsPrewhole())
	{
		return iStat <= 0;
	}

	return iStat <= 1;
}

void CArtikelPage3::SucheEigeneWgr( )
{
	CZdkwgrSelCtrl m_SelBox;

	m_SelBox.SetCountry(GetCountry());

	if (IsCountry("CH"))
	{
		m_SelBox.SetCorWgrArtCH(true); // dadurch werden bei der Auswahl nur 
	}									// Warengruppen mit "10xxx" angeblendet (Schweiz!)

	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_SEL_WRGRP), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufEigenewg->WARENGRUPPE ) == 0 )
		{
			m_EIGENEWGR.p_SetInput();
			m_EIGENEWGR.SetFocus();
			// in BG ist die Warengruppe nur 2-stellig; in CRdZdkwgr::ReadName werden aber 5 Stellen erwartet!
			sprintf(m_pBufEigenewg->WARENGRUPPE, "%-5s", m_pBufEigenewg->WARENGRUPPE);
			ShowEigeneWgr( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// SaisonWgr
BOOL CArtikelPage3::ShowSaisonWgr( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name, AlleNamen;
	CString Errmld;
	iStat = m_RD_SAISONWGR.IPlausi( m_pBufSaisonwg->WARENGRUPPE, Name,
										 &Errmld);
	if ( bShow )	// neu
		MakeSaisonwgString( Name, 0);

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

void CArtikelPage3::SucheSaisonWgr( )
{
	CSaisonwgSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING291), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufSaisonwg->WARENGRUPPE ) == 0 )
		{
			m_SAISONWGR.p_SetInput();
			m_SAISONWGR.SetFocus();
			ShowSaisonWgr( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// SaisonWgr2
BOOL CArtikelPage3::ShowSaisonWgr2( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name, AlleNamen;
	CString Errmld;
	iStat = m_RD_SAISONWGR2.IPlausi( m_pBufSaisonwg2->WARENGRUPPE, Name,
										 &Errmld);
	if ( bShow )	// neu
		MakeSaisonwgString( Name, 1);

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

void CArtikelPage3::SucheSaisonWgr2( )
{
	CSaisonwgSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING291), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufSaisonwg2->WARENGRUPPE ) == 0 )
		{
			m_SAISONWGR2.p_SetInput();
			m_SAISONWGR2.SetFocus();
			ShowSaisonWgr2( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// SaisonWgr3
BOOL CArtikelPage3::ShowSaisonWgr3( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name, AlleNamen;
	CString Errmld;
	iStat = m_RD_SAISONWGR3.IPlausi( m_pBufSaisonwg3->WARENGRUPPE, Name,
										 &Errmld);
	if ( bShow )	// neu
		MakeSaisonwgString( Name, 2);

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

void CArtikelPage3::SucheSaisonWgr3( )
{
	CSaisonwgSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING291), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufSaisonwg3->WARENGRUPPE ) == 0 )
		{
			m_SAISONWGR3.p_SetInput();
			m_SAISONWGR3.SetFocus();
			ShowSaisonWgr3( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// Therapiegruppe

BOOL CArtikelPage3::ShowTherapieGr( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	iStat = m_RD_THERAPIEGRUPPE.IPlausi( m_pBufTherapie->WARENGRUPPE, Name,
										 &Errmld);
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_THERAPIEGRUPPE )->SetWindowText( Name );
	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage3::SucheTherapieGr( )
{
	CZdktgrSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING292), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufTherapie->WARENGRUPPE ) == 0 )
		{
			m_THERAPIEGRUPPE.p_SetInput();
			m_THERAPIEGRUPPE.SetFocus();
			ShowTherapieGr( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// BTM-Gruppe
BOOL CArtikelPage3::ShowBtmGr( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	iStat = m_RD_BTMGRUPPE.IPlausi( m_pBufBtmgruppe->WARENGRUPPE, Name, &Errmld);

	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_BTMGRUPPE )->SetWindowText( Name );

	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );

	if ( iStat <= 1)
	{
		// BTM-Faktor auf Seite 1 neu berechnen
		CArtikelPage1 *pP1;
		pP1 = (CArtikelPage1 *)((CArtikelView*)m_pView)->GetPage(0);
		pP1->ChangeBtm_Faktor();
	}

	return iStat <= 1;
}

void CArtikelPage3::SucheBtmGr( )
{
	CZdkbtmSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING293), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufBtmgruppe->WARENGRUPPE ) == 0 )
		{
			m_BTMGRUPPE.p_SetInput();
			m_BTMGRUPPE.SetFocus();
			ShowBtmGr( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// Wirkstoff
BOOL CArtikelPage3::ShowWirkstoff( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	iStat = m_RD_WIRKSTOFF.IPlausi( m_pBufWirkstoff->WARENGRUPPE, Name, m_INGREDIENT_TYPE, &Errmld);
	
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_WIRKSTOFF_NR )->SetWindowText( Name );
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );
	
	if ( iStat == 1 ) 
		m_INGREDIENT_TYPE = ""; // Typ- Member zurücksetzen, wenn kein Wirkstoff angegeben!

	return iStat <= 1;
}

void CArtikelPage3::SucheWirkstoff( )
{
	CZdkwirSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING294), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufWirkstoff->WARENGRUPPE ) == 0 )
		{
			m_WIRKSTOFF_NR.p_SetInput();
			m_WIRKSTOFF_NR.SetFocus();
			ShowWirkstoff( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// Rabattgruppe
BOOL CArtikelPage3::ShowRabGr( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	iStat = m_RD_RABATTGRP.IPlausi( m_pBufRabattgruppe->WARENGRUPPE, Name, &Errmld);
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_RABATTGRP )->SetWindowText( Name );
	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage3::SucheRabGr( )
{
	CZrabgrpSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING10005), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufRabattgruppe->WARENGRUPPE ) == 0 )
		{
			m_RABATTGRP.p_SetInput();
			m_RABATTGRP.SetFocus();
			ShowRabGr( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// Spezial-Artikel-Typ
BOOL CArtikelPage3::ShowSpecArtTyp( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	iStat = m_RD_SPECARTTYP.IPlausi( m_pBufSpecarticletype->WARENGRUPPE, Name, &Errmld);
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_SPECARTTYP )->SetWindowText( Name );

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld ); 

	return iStat <= 1;
}

void CArtikelPage3::SucheSpecArtTyp( )
{
	CSpecArticleTypesSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1425), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufSpecarticletype->WARENGRUPPE ) == 0 )
		{
			m_SPECARTTYP.p_SetInput();
			m_SPECARTTYP.SetFocus();
			ShowSpecArtTyp( TRUE );
		}
	}
	m_SelBox.CloseCursor(); 
}

BOOL CArtikelPage3::TestAtcCode( BOOL bMeldung )
{
	if (strncmp (m_CODE_ATC_PREFIX, "       ", 7) == 0)
		return true;

	BOOL bOk = m_CODE_ATC_PREFIX[6] != ' ';
	if ( !bOk && bMeldung )
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1291) );
	return bOk;
}

BOOL CArtikelPage3::ShowAtcCode( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	// 12P044 für HR das Suffix füllen !?
	strncpy(m_CODE_ATC_PREFIX, m_pBufAtc->ARTICLE_CODE, 7);		// 1-7
	m_CODE_ATC_PREFIX[7] = '\0';
	m_CODE_ATC.p_SetInput();
	strncpy(m_CODE_ATC_SUFFIX, m_pBufAtc->ARTICLE_CODE + 8, 3); // 9-11 (8 = leer)
	m_CODE_ATC_SUFFIX[3] = '\0';
	m_CODE_ATC_SUFFIX_HR.p_SetInput();

	iStat = m_RD_ATC.IPlausi( m_CODE_ATC_PREFIX, Name, &Errmld);
	
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_CODE_ATC )->SetWindowText( Name );

	// Font aendern (in den mehrzeiligen Statics kleiner, um etwas Platz auf dem Dialog zu schaffen)
	// nur, wenn die Seite auch schon aktiv war, sonst schmiert das Programm ab
	if (((CArtikelView* )m_pView)->WasPageActive(2) == TRUE)
	{
		CEkZdpApp* pApp = (CEkZdpApp*) AfxGetApp();
		m_pSmallFont = pApp->GetSmallFont();
		GetDlgItem( IDC_ST_ARTIKEL_CODE_ATC )->SetFont( m_pSmallFont );
	}

	if ( iStat > 1 && bMeldung ) 
	{
		MsgBoxOK( Errmld );
	}

	return iStat <= 1;
}

void CArtikelPage3::SucheAtcCode( )
{
	CAtcSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1288), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_CODE_ATC_PREFIX ) == 0 )
		{
			m_CODE_ATC.p_SetInput();
			m_CODE_ATC.SetFocus();
			ComposeAtcCode();
			ShowAtcCode( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

/////////////////////////////////////////////////////////////
//  Validierung

class CV_ARTIKEL_ImsWgr : public ChValBase
{
public:
	CV_ARTIKEL_ImsWgr( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage3*)m_pWnd)->ShowImsWgr( bMeldung, bMeldung );
		if ( bOk ) bOk = ((CArtikelPage3*)m_pWnd)->TestImsWgr( bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheImsWgr( );
	}
};

class CV_ARTIKEL_EigeneWgr : public ChValBase
{
public:
	CV_ARTIKEL_EigeneWgr( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage3*)m_pWnd)->ShowEigeneWgr( bMeldung, bMeldung );
//		if ( bOk ) bOk = ((CArtikelPage3*)m_pWnd)->TestEigeneWgr( bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheEigeneWgr( );
	}
	void PostProc( )
	{
		 ((CArtikelPage3*)m_pWnd)->SetSkontofaehig( );
		 ((CArtikelPage3*)m_pWnd)->SetTaxpfl( );
	}
};

class CV_ARTIKEL_SaisonWgr : public ChValBase
{
public:
	CV_ARTIKEL_SaisonWgr( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage3*)m_pWnd)->ShowSaisonWgr( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheSaisonWgr( );
	}
};

class CV_ARTIKEL_SaisonWgr2 : public ChValBase
{
public:
	CV_ARTIKEL_SaisonWgr2( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage3*)m_pWnd)->ShowSaisonWgr2( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheSaisonWgr2( );
	}
};

class CV_ARTIKEL_SaisonWgr3 : public ChValBase
{
public:
	CV_ARTIKEL_SaisonWgr3( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage3*)m_pWnd)->ShowSaisonWgr3( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheSaisonWgr3( );
	}
};

class CV_ARTIKEL_TherapieGr : public ChValBase
{
public:
	CV_ARTIKEL_TherapieGr( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage3*)m_pWnd)->ShowTherapieGr( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheTherapieGr( );
	}
};

class CV_ARTIKEL_BtmGr : public ChValBase
{
public:
	CV_ARTIKEL_BtmGr( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage3*)m_pWnd)->ShowBtmGr( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheBtmGr( );
	}
};

class CV_ARTIKEL_Wirkstoff : public ChValBase
{
public:
	CV_ARTIKEL_Wirkstoff( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtikelPage3*)m_pWnd)->ShowWirkstoff( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheWirkstoff( );
	}
};

class CV_ARTIKEL_RabGr : public ChValBase
{
public:
	CV_ARTIKEL_RabGr( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage3*)m_pWnd)->ShowRabGr( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheRabGr( );
	}
};

class CV_ARTIKEL_SpArtTyp : public ChValBase
{
public:
	CV_ARTIKEL_SpArtTyp( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage3*)m_pWnd)->ShowSpecArtTyp( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheSpecArtTyp( );
	}
};

class CV_ARTIKEL_AbdaCode : public ChValBase
{
public:
	CV_ARTIKEL_AbdaCode( struct ZARTWG* pBuf, CArtikelPage3* pView ) 
		: ChValBase( pBuf, pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = TRUE;

		if (IsCountry("BG"))
		{
			CString Code;

			Code = ((struct ZARTWG*)m_pBuf)->WARENGRUPPE;
			Code.Trim();

			bOk = Code.IsEmpty() == false;
		}

		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1197) );
		
		return bOk;
	}
};

class CV_ARTIKEL_Code_Atc : public ChValBase
{
public:
	CV_ARTIKEL_Code_Atc( CArtikelPage3* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		PostProc();
		
		BOOL bOk;
		bOk = ((CArtikelPage3*)m_pWnd)->ShowAtcCode( bMeldung, bMeldung );

// SR-15020316: ATC-Code muss nicht immer 7-stellig (auf unterster Ebene) sein
//		if ( bOk ) 
//			bOk = ((CArtikelPage3*)m_pWnd)->TestAtcCode( bMeldung );

		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage3*)m_pWnd)->SucheAtcCode( );
	}
	void PostProc( )
	{
		// 12P044 Suffix HR
		((CArtikelPage3*)m_pWnd)->ComposeAtcCode();
	}
};

void CArtikelPage3::ComposeAtcCode()
{
	// nicht ausführen, wenn Werte auf dieser Page für diesen Artikel vorher nicht angezeigt wurden!
	// (sonst werden die Werte des vorher bearbeiteten Artikels eingesetzt !)
	if (((CArtikelView* )m_pView)->WasPageActive(2) == FALSE)
		return;

	// 12P044 Suffix HR
	m_CODE_ATC.p_GetInput();
	m_CODE_ATC_SUFFIX_HR.p_GetInput();
	strncpy(m_pBufAtc->ARTICLE_CODE, m_CODE_ATC_PREFIX, 7);	// 1-7
	m_pBufAtc->ARTICLE_CODE[7] = ' ';							// 8
	strncpy(m_pBufAtc->ARTICLE_CODE + 8, m_CODE_ATC_SUFFIX, 3);	// 9-11	
}

/////////////////////////////////////////////////////////////
//  EndValidierung 

BOOL CArtikelPage3::EndValidate( int *ind, BOOL bMeldung )
{
	*ind = 0;

	/* PostProcs aufrufen hier !!!!! */
	
	// Wirkstoff mit Typ = B neu gesetzt und btm != 1
	// --> psychotrop = J / bestell_nicht_ausl = 1 setzen
	if ( IsCountry("D") &&
		 strcmp(m_pBufWirkstoff->WARENGRUPPE, ((CArtikelView* )m_pView)->GetOldBuffer()->zartwg[13].WARENGRUPPE) != 0	&& // Wirkstoff geändert
		 m_INGREDIENT_TYPE == "B" && *m_pBufZartikel->BTM != '1' )
	{
		*m_pBufZartikel->PSYCHOTROP = 'J';
		*m_pBufZartikel->BESTELL_NICHT_AUSL = '1';	
	}

	// Wirkstoff mit Typ = B 
	// --> psychotrop = J oder btm = 1 ?
	if ( IsCountry("D") && m_INGREDIENT_TYPE == "B" )
	{
		if ( *m_pBufZartikel->PSYCHOTROP != 'J' && *m_pBufZartikel->BTM != '1' )
		{
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1427) );
			*ind = m_Pos_PSYCHOTROP;
			return FALSE;
		}
	}	

	if ( GetFocus() == &m_EIGENEWGR ) 
	{
		SetSkontofaehig( );
		SetTaxpfl( );
	}

	// Produktart und Wirkstoff ( wenn Wirkstoff, dann auch Produktart )
	if (IsCountry("D"))
	{
		if ( strcmp( m_pBufWirkstoff->WARENGRUPPE, "     " ) != 0 &&
			 strcmp( m_pBufWirkstoff->WARENGRUPPE, "00000" ) != 0 &&
			*m_pBufZartikel->PRODUKTART == '0' )
		{
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING295) );
			*ind = m_Pos_PRODUKTART;
			return FALSE;
		}
	}

	// in Bulgarien führende Nullen aus ABDA-Code entfernen
	if (IsCountry("BG"))
	{
		int i = 0;

		while (m_pBufAbdacode->WARENGRUPPE[i] == '0')
			sprintf(m_pBufAbdacode->WARENGRUPPE, "%-4s ", m_pBufAbdacode->WARENGRUPPE+1);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////
//  Dialogfelder 

void CArtikelPage3::InitPflege( CWnd *pView  )
{
	CArtikelPage3* pThisView = this;
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )pView)->GetBuffer();
	struct PFL_ARTIKEL *m_OldBuf = ((CArtikelView* )pView)->GetOldBuffer();

	m_pBufZartikel			= &m_Buf->zartikel;
	m_pBufImswg				= &m_Buf->zartwg[0];	// art = 1
	m_pBufEigenewg			= &m_Buf->zartwg[1];	// art = 2
	m_pBufTherapie			= &m_Buf->zartwg[2];	// art = 3
	m_pBufAbdacode			= &m_Buf->zartwg[3];	// art = 4
	m_pBufSaisonwg			= &m_Buf->zartwg[4];	// art = 5
	m_pBufSaisonwg2			= &m_Buf->zartwg[9];	// art = A
	m_pBufSaisonwg3			= &m_Buf->zartwg[15];	// art = G
	m_pBufBtmgruppe			= &m_Buf->zartwg[5];	// art = 6
	m_pBufRabattgruppe		= &m_Buf->zartwg[8];	// art = 9
	m_pBufSpecarticletype	= &m_Buf->zartwg[12];	// art = D
	m_pBufWirkstoff			= &m_Buf->zartwg[13];	// art = E
	m_pBufZartcroatia		= &m_Buf->zartcroatia;
	m_pBufZartswitzerland	= &m_Buf->zartswitzerland;
	m_pBufCarticleext		= &m_Buf->carticleext;

	m_pBufOldZartikel		= &m_OldBuf->zartikel;  

	m_pBufAtc = &m_Buf->carticlecodes[1];		// code_type = 2
	m_pBufOeko = &m_Buf->carticlecodes[17];		// code_type = 18

	MakeDialog();

	m_IMSWGR.SetMask			(ED_CHAR,
		                         ED_NORMAL,
			                     m_pBufImswg->WARENGRUPPE,
				                 5,
								 new ChMaskNum,
								 new CV_ARTIKEL_ImsWgr( pThisView ) );

	m_EIGENEWGR.SetMask			(ED_CHAR,
		                         ED_NORMAL,
			                     m_pBufEigenewg->WARENGRUPPE,
				                 5,
								 new ChMaskNum,
								 new CV_ARTIKEL_EigeneWgr( pThisView ) );

	m_SAISONWGR.SetMask			(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufSaisonwg->WARENGRUPPE,
				                 2,
								 new ChMaskChar,
								 new CV_ARTIKEL_SaisonWgr( pThisView ) );

	m_SAISONWGR2.SetMask		(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufSaisonwg2->WARENGRUPPE,
				                 2,
								 new ChMaskChar,
								 new CV_ARTIKEL_SaisonWgr2( pThisView ) );

	m_SAISONWGR3.SetMask		(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufSaisonwg3->WARENGRUPPE,
				                 2,
								 new ChMaskChar,
								 new CV_ARTIKEL_SaisonWgr3( pThisView ) );

	m_THERAPIEGRUPPE.SetMask	(ED_CHAR,
		                         ED_NORMAL,
			                     m_pBufTherapie->WARENGRUPPE,
				                 5,
								 new ChMaskNum,
								 new CV_ARTIKEL_TherapieGr( pThisView ) );

	m_BTMGRUPPE.SetMask			(ED_CHAR,
		                         ED_UPPER | ED_CLINPUT | ED_LEADZERO,
			                     m_pBufBtmgruppe->WARENGRUPPE,
				                 5,
								 new ChMaskChar,
								 new CV_ARTIKEL_BtmGr( pThisView ) );

	m_WIRKSTOFF_NR.SetMask		(ED_CHAR,
		                         ED_UPPER | ED_CLINPUT | ED_LEADZERO,
								 //m_pBufZartikel->WIRKSTOFF_NR,
								 m_pBufWirkstoff->WARENGRUPPE,
				                 L_ZDKWIR_WIR_BEREICH,
								 new ChMaskNum,
								 new CV_ARTIKEL_Wirkstoff( pThisView ) );

	if (IsCountry("D"))
	{
		m_PRODUKTART.SetMask("0123456789F", m_pBufZartikel->PRODUKTART, 0);
	}
	else if (IsCountry("CH"))
	{
		m_PRODUKTART.SetMask("0123456789ABCDE", m_pBufZartikel->PRODUKTART, 0);
	}
	else
	{
		m_PRODUKTART.SetMask("0123456789", m_pBufZartikel->PRODUKTART, 0);
	}


	m_RABATTGRP.SetMask			(ED_CHAR,
		                         ED_UPPER,
								 m_pBufRabattgruppe->WARENGRUPPE,
				                 3,
								 new ChMaskNum,
								 new CV_ARTIKEL_RabGr( pThisView ) );

	m_SPECARTTYP.SetMask		(ED_CHAR,
		                         ED_UPPER,
								 m_pBufSpecarticletype->WARENGRUPPE,
				                 3,
								 new ChMaskNum,
								 new CV_ARTIKEL_SpArtTyp( pThisView ) );

	m_ABDACODE.SetMask			(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufAbdacode->WARENGRUPPE,
				                 5,
								 new ChMaskChar,
								 new CV_ARTIKEL_AbdaCode( m_pBufAbdacode, pThisView ) );

	m_KATALOG.SetMask			(ED_CHAR,
								 ED_CLINPUT | ED_UPPER,
								 m_pBufZartikel->KATALOG,
								 L_ZARTIKEL_KATALOG,
								 new ChMaskChar );

	m_DATUM_FMDPFLICHT.SetMask	(ED_LDATE,
								 ED_NORMAL,
								 &m_pBufZartikel->DATUM_FMDPFLICHT,
								 L_LDATUM,
								new ChMaskLDate );

	m_SORTIMENT_1.SetMask		('1', '0', m_pBufZartikel->SORTIMENT_1 );
	m_SORTIMENT_2.SetMask		('1', '0', m_pBufZartikel->SORTIMENT_2 );
	m_SORTIMENT_3.SetMask		('1', '0', m_pBufZartikel->SORTIMENT_3 );
	m_SORTIMENT_4.SetMask		('1', '0', m_pBufZartikel->SORTIMENT_4 );
	m_SORTIMENT_5.SetMask		('1', '0', m_pBufZartikel->SORTIMENT_5 );

	m_ARZNEIMITTEL.SetMask		('1', '0', m_pBufZartikel->ARZNEIMITTEL );
	m_MEDIZINPRODUKT.SetMask	('1', '0', m_pBufZartikel->MEDIZINPRODUKT );
	m_CE_KENNZEICHEN.SetMask	('1', '0', m_pBufZartikel->CE_KENNZEICHEN );
	m_HILFSMV.SetMask			('1', '0', m_pBufZartikel->HILFSM_VERBRAUCH );
	m_IMPFSTOFF.SetMask			('1', '0', m_pBufZartikel->IMPFSTOFF );
	m_REZEPTURARZNEI.SetMask	('1', '0', m_pBufZartikel->REZEPTURARZNEI );
	m_MEDIZINISCHE_GASE.SetMask	('1', '0', m_pBufZartikel->MEDIZINISCHE_GASE );
	m_HOMOEO.SetMask			('1', '0', m_pBufZartikel->HOMOEOPATHIKUM );
	m_ANTHRO.SetMask			('1', '0', m_pBufZartikel->ANTHROPOSOPHIKUM );
	m_PHYTO.SetMask				('1', '0', m_pBufZartikel->PHYTOPHARMAKON );

	m_FMD.SetMask				( "012", &m_pBufZartikel->FMD_RELEVANT );
	m_STERIL.SetMask			( 1, 0, &m_pBufZartikel->STERIL );
	m_KOSMETIKUM.SetMask		( 1, 0, &m_pBufZartikel->KOSMETIKUM );
	m_BIOSIEGEL.SetMask			( 1, 0, &m_pBufZartikel->BIOSIEGEL );
	m_ANTIBIOTIKUM.SetMask		( 1, 0, &m_pBufZartikel->ANTIBIOTIKUM );
	m_HIGH_THERAPEUTIC_VAL.SetMask(1,0, &m_pBufCarticleext->HIGH_THERAPEUTIC_VALUE );

	m_KONTRAZEPTIVUM.SetMask	("012",    m_pBufZartikel->KONTRAZEPTIVUM, 0 ); 
	m_BIOTECH_ARZNEI.SetMask	("0123",    &m_pBufZartikel->BIOTECH_ARZNEI ); 
	m_ABGABEBEST_IFA.SetMask	(" 6789", m_pBufZartikel->ABGABEBEST_IFA, 0);
	m_NEGATIVLISTE.SetMask		("012", m_pBufZartikel->NEGATIVLISTE, 0 );

	// Abfragen schon hier und nicht erst im Translation, weil sonst landesspezifische Feldinhalte nicht definiert sind und ggfs. Werte automatisch zurückgesetzt werden
	if (IsCountry("F"))
		m_PSYCHOTROP.SetMask("NPE",    m_pBufZartikel->PSYCHOTROP, 0 );	
	else if (IsCountry("A"))
		m_PSYCHOTROP.SetMask("NPT",    m_pBufZartikel->PSYCHOTROP, 0 ); 
	else if (IsCountry("CH"))
		m_PSYCHOTROP.SetMask("NBCDEF", m_pBufZartikel->PSYCHOTROP, 0 ); 
	else
		m_PSYCHOTROP.SetMask("NJ",     m_pBufZartikel->PSYCHOTROP, 0 );	

	if (IsCountry("CH"))
		m_PRIVATSORTIMENT.SetMask("NZ",		 m_pBufZartikel->PRIVATSORTIMENT, 0 ); 
	else
		m_PRIVATSORTIMENT.SetMask("NLZBVDS", m_pBufZartikel->PRIVATSORTIMENT, 0 );

	m_CODE_ATC.SetMask			(ED_CHAR,
		                         ED_UPPER,
			                     //m_pBufAtc->ARTICLE_CODE,
								 m_CODE_ATC_PREFIX,
				                 7,
								 new ChMaskChar,
								 new CV_ARTIKEL_Code_Atc( pThisView ) );

	m_CODE_ATC_SUFFIX_HR.SetMask (ED_CHAR,
		                         ED_UPPER,
			                     m_CODE_ATC_SUFFIX,
				                 3,
								 new ChMaskChar,
								 new CV_ARTIKEL_Code_Atc( pThisView ));
	
	m_CODE_OEKO.SetMask			(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufOeko->ARTICLE_CODE,
				                 11,
								 new ChMaskChar);

	m_WIRKSTOFF.SetMask			( 1, 0, &m_pBufZartikel->WIRKSTOFF );

	m_SER_NUM_TRACK.SetMask		( 1, 0, &m_pBufZartikel->SERIAL_NUMBER_TRACKING );
	m_NEUARTIGETHERAPIEN.SetMask( "01234569", &m_pBufZartikel->NEUARTIGETHERAPIE);
	m_NOVELFOOD.SetMask			( "01234", &m_pBufZartikel->NOVELFOOD );
	m_WUNDPRODUKT.SetMask		( 1, 0, &m_pBufZartikel->WUNDPRODUKT );

	m_bInitialized = TRUE;
  	 
	// Meldung bei EigegeWgr erlauben
	m_bEigeneWgrMeldung = TRUE;
}

/////////////////////////////////////////////////////////////
// ChPflegePage functions 

void CArtikelPage3::SetDialog( BOOL bDialog )
{   
 	m_dlg.SetDialog( bDialog );
}

void CArtikelPage3::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage3::EnableFields( BOOL bEnab )
{   
	m_dlg.EnableFields( bEnab );

	// generell nicht mehr verwendet --> im Rahmen von LogIndex für CH wieder aktiviert
	if (!IsCountry("CH") || IsPrewhole())
		m_CE_KENNZEICHEN.EnableWindow(false);

	// bestimmte Felder ausblenden
	if (!IsCountry("D"))
	{
		if (!IsCountry("F"))
		{
			m_IMSWGR.EnableWindow(false);
		}

		m_THERAPIEGRUPPE.EnableWindow(false);
		m_BTMGRUPPE.EnableWindow(false);
		m_ABGABEBEST_IFA.EnableWindow(false);
		m_CODE_OEKO.EnableWindow(false); 
	}

	if (IsCountry("A"))
	{
		m_MEDIZINPRODUKT.EnableWindow(false);
	}

	if (IsCountry("CH"))
	{
		m_WIRKSTOFF_NR.EnableWindow(false);
		m_RABATTGRP.EnableWindow(false);
		m_NEGATIVLISTE.EnableWindow(false);		
	}

	if (IsCountry("HR"))
	{
		m_PRIVATSORTIMENT.EnableWindow(false);
		m_WIRKSTOFF_NR.EnableWindow(false);
		m_PRODUKTART.EnableWindow(false);
		m_RABATTGRP.EnableWindow(false);
		m_ABDACODE.EnableWindow(false);
		m_KATALOG.EnableWindow(false);
		m_SORTIMENT_1.EnableWindow(false);
//		m_SORTIMENT_2.EnableWindow(false);
//		m_SORTIMENT_3.EnableWindow(false);
		m_SORTIMENT_4.EnableWindow(false);
		m_SORTIMENT_5.EnableWindow(false);
//		m_ARZNEIMITTEL.EnableWindow(false);
		m_MEDIZINPRODUKT.EnableWindow(false);
		m_CE_KENNZEICHEN.EnableWindow(false);
		m_HILFSMV.EnableWindow(false);
		m_IMPFSTOFF.EnableWindow(false);
		m_REZEPTURARZNEI.EnableWindow(false);
		m_HIGH_THERAPEUTIC_VAL.EnableWindow(false);
//		m_MEDIZINISCHE_GASE.EnableWindow(false);
//		m_HOMOEO.EnableWindow(false);
		m_ANTHRO.EnableWindow(false);
		m_PHYTO.EnableWindow(false);
		m_STERIL.EnableWindow(false);
		m_KOSMETIKUM.EnableWindow(false);
		m_BIOSIEGEL.EnableWindow(false);
		m_KONTRAZEPTIVUM.EnableWindow(false);
		m_BIOTECH_ARZNEI.EnableWindow(false);
		m_PSYCHOTROP.EnableWindow(false);
		m_NEGATIVLISTE.EnableWindow(false);
		m_ANTIBIOTIKUM.EnableWindow(false);
	}
	else
	{
		m_CODE_ATC_SUFFIX_HR.EnableWindow(false); // only for Croatia
	}

	if (IsCountry("F") && !IsPrewhole() && !IsIvrylab() )
	{
		m_RABATTGRP.EnableWindow(false);
	}

	// do not display MPKLASSE for countries other than Germany and Switzerland
	if (!(IsCountry("D") || IsCountry("CH")))
	{
		m_MPKLASSE.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ST_ARTIKEL_MPKLASSE)->ShowWindow(SW_HIDE);
	}
	else
	{
		// but even for Germany and Switzerland MPKLASSE is read only
		// show value from zifaoart / clioart only, no editing allowed
		m_MPKLASSE.EnableWindow(false);
	}

    if (!IsCountry("D"))
	{
		m_BT_MP31.ShowWindow(SW_HIDE);
		m_BT_VERB31.ShowWindow(SW_HIDE);
		GetDlgItem( IDC_CK_ARTIKEL_MP31 )->ShowWindow(SW_HIDE);
		GetDlgItem( IDC_CK_ARTIKEL_VERB31 )->ShowWindow(SW_HIDE);

		m_INVITROKLASSE.ShowWindow(SW_HIDE);
		GetDlgItem( IDC_ST_ARTIKEL_INVITROKLASSE )->ShowWindow(SW_HIDE);

		if (!IsCountry("CH") && !IsCountry("F") && !IsCountry("A"))
		{
			GetDlgItem( IDC_CK_ARTIKEL_SERNUMTRAC )->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		// Read only, da der Wert von A00UDIDI nicht geändert werden kann.
		m_SER_NUM_TRACK.EnableWindow(false);
		
		// nur Anzeige aus zifaoart = keine Bearbeitungsmöglichkeit
		m_INVITROKLASSE.EnableWindow(false);
	}

	m_FMD.EnableWindow(false); //read-only, as calculated every night automatically!
}

void CArtikelPage3::OnPbIsMP31() 
{
	// as there is no read-only possibility for CheckBoxes and control should not be disabled --> workaround:
	m_BT_MP31.SetCheck( strcmp(((CArtikelView* )m_pView)->m_Doc.GetIfaOartBuffer()->A02MP31, "01") == 0  );
}

void CArtikelPage3::OnPbIsVERB31() 
{
	// as there is no read-only possibility for CheckBoxes and control should not be disabled --> workaround:
	m_BT_VERB31.SetCheck( strcmp(((CArtikelView* )m_pView)->m_Doc.GetIfaOartBuffer()->A02VERB31, "01") == 0  );
}

void CArtikelPage3::ShowFields()
{
	FillComboBox();

	// Übersetzung erst hier, weil beim Aufruf von TranslatePages im View noch nicht sichtbar
	Translation();

	m_dlg.ShowFields();

	ShowImsWgr(TRUE);
	ShowEigeneWgr(TRUE);
	ShowSaisonWgr(TRUE);
	ShowSaisonWgr2(TRUE);
	ShowSaisonWgr3(TRUE);
	ShowTherapieGr(TRUE);
	ShowBtmGr(TRUE);
	ShowWirkstoff(TRUE);
	ShowRabGr(TRUE);
	ShowSpecArtTyp(TRUE);
	ShowAtcCode(TRUE);

	if (IsCountry("D"))
	{
		OnPbIsMP31();
		OnPbIsVERB31();

		if (strcmp(((CArtikelView*)m_pView)->m_Doc.GetIfaOartBuffer()->A02MPKLASS, "01") == 0)
			m_MPKLASSE.SetCurSel(1);
		else if (strcmp(((CArtikelView*)m_pView)->m_Doc.GetIfaOartBuffer()->A02MPKLASS, "02") == 0)
			m_MPKLASSE.SetCurSel(2);
		else if (strcmp(((CArtikelView*)m_pView)->m_Doc.GetIfaOartBuffer()->A02MPKLASS, "03") == 0)
			m_MPKLASSE.SetCurSel(3);
		else if (strcmp(((CArtikelView*)m_pView)->m_Doc.GetIfaOartBuffer()->A02MPKLASS, "04") == 0)
			m_MPKLASSE.SetCurSel(4);
		else
			m_MPKLASSE.SetCurSel(0);

		if (strcmp(((CArtikelView*)m_pView)->m_Doc.GetIfaOartBuffer()->A02INVITRO, "01") == 0)
			m_INVITROKLASSE.SetCurSel(1);
		else if (strcmp(((CArtikelView*)m_pView)->m_Doc.GetIfaOartBuffer()->A02INVITRO, "02") == 0)
			m_INVITROKLASSE.SetCurSel(2);
		else if (strcmp(((CArtikelView*)m_pView)->m_Doc.GetIfaOartBuffer()->A02INVITRO, "03") == 0)
			m_INVITROKLASSE.SetCurSel(3);
		else if (strcmp(((CArtikelView*)m_pView)->m_Doc.GetIfaOartBuffer()->A02INVITRO, "04") == 0)
			m_INVITROKLASSE.SetCurSel(4);
		else
			m_INVITROKLASSE.SetCurSel(0);
	}
	else if (IsCountry("CH"))
	{
		CString mdclass(((CArtikelView*)m_pView)->m_Doc.GetClioart()->MDCLASS);

		// values of mdclass have differing lengths --> trim spaces
		mdclass = mdclass.Trim();
        if (mdclass == "I")
			m_MPKLASSE.SetCurSel(1);
		else if (mdclass == "IM")
			m_MPKLASSE.SetCurSel(2);
		else if (mdclass == "IR")
			m_MPKLASSE.SetCurSel(3);
		else if (mdclass == "IS")
			m_MPKLASSE.SetCurSel(4);
		else if (mdclass == "IIA")
			m_MPKLASSE.SetCurSel(5);
		else if (mdclass == "IIB")
			m_MPKLASSE.SetCurSel(6);
		else if (mdclass == "III")
			m_MPKLASSE.SetCurSel(7);
		else if (mdclass == "IVD")
			m_MPKLASSE.SetCurSel(8);
		else if (mdclass == "A")
			m_MPKLASSE.SetCurSel(9);
		else if (mdclass == "B")
			m_MPKLASSE.SetCurSel(10);
		else if (mdclass == "C")
			m_MPKLASSE.SetCurSel(11);
		else if (mdclass == "D")
			m_MPKLASSE.SetCurSel(12);
		else
			m_MPKLASSE.SetCurSel(0);
	}
}

void CArtikelPage3::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage3::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}


void CArtikelPage3::ActivateField( int nr )
{
    m_dlg.ActivateField( nr );
}


BOOL CArtikelPage3::Validate( BOOL bMeldung )
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
// CLieferPage3 message handlers

BOOL CArtikelPage3::OnSetActive()
{
	BOOL bOk;
	bOk = CPropertyPageMultiLang::OnSetActive();
	if ( bOk && m_bInitialized )
	{
		((CArtikelView* )m_pView)->Set_WasActive();

		// hinter Set_WasActive() verschoben, da die Verkleinerung der Schriftgröße nur durchgeführt wird, wenn die Seite als aktiv gekennzeichnet ist
		ShowFields();

		EnableFields( ((CArtikelView* )m_pView)->AreFieldsEnabled() );
		GetParent()->SendMessage( WM_USER+10 );
		SetValidation( TRUE );

//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING298) );
	}
	return bOk;
}


BOOL CArtikelPage3::OnKillActive()
{
	BOOL bOk;
	bOk = CPropertyPageMultiLang::OnKillActive();
	if ( bOk )
	{
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING299) );

		if ( GetFocus() == &m_EIGENEWGR ) 
		{
			m_bEigeneWgrMeldung = FALSE;
			ChPflegePage::NextDlgCtrl();	// neu, wegen Skontofaehig Seite 1 
			m_bEigeneWgrMeldung = TRUE;
		}

/*
		if ( GetFocus() == &m_EIGENEWGR ) 
		{
			m_EIGENEWGR.Validate( FALSE );			
			ShowEigeneWgr( FALSE, FALSE );
			SetSkontofaehig( );
		}
*/

		SetValidation( FALSE );
		DataExchangeToBuffer( );  //  Puffer wie Eingabe
/*
		if ( GetFocus() == &m_EIGENEWGR ) 
		{
			ShowEigeneWgr( FALSE, FALSE );
			SetSkontofaehig( );
		}
*/
	}
	return bOk;
}

void CArtikelPage3::Translation() 
{
	if (IsCountry("A"))
	{
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_1)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING300));
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_2)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING301));
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_3)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING302));
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_4)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING303));
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_5)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING304));
	} 
	else if (IsCountry("CH"))
	{
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_1)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING305));
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_2)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING306));
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_3)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING996));
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_4)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING1379));
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_4)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING61470));
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_5)->SetWindowText("S&5 (strategischer Artikel)");
	} 
	else if (IsCountry("F"))
	{
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_1)->SetWindowText( "S&1 (microfiche article)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_2)->SetWindowText( "S&2 (retrocession)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_3)->SetWindowText( "S&3 (produit export)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_4)->SetWindowText( "S&4 (option short)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_5)->SetWindowText( "S&5 (option direct)" );
	} 
	else if (IsCountry("HR"))
	{
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_1)->SetWindowText( "A&1 (Euro-Artikl)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_2)->SetWindowText( "A&2 (Bez trosarine)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_3)->SetWindowText( "A&3 (bez dostave u IMS)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_4)->SetWindowText( "A&4 (not used)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_5)->SetWindowText( "A&5 (not used)" );
	} 
	else if (IsCountry("BG"))
	{
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_1)->SetWindowText( "A&1 (Krankenhausprodukt)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_2)->SetWindowText( "A&2 (Exklusiv-Artikel)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_3)->SetWindowText( "A&3 (Billig-Artikel)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_4)->SetWindowText( "A&4 (not used)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_5)->SetWindowText( "A&5 (not used)" );
	}
	else if (!IsCountry("D"))	// Default für Länder, in denen noch gar kein Feld belegt ist
	{
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_1)->SetWindowText( "A&1 (not used)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_2)->SetWindowText( "A&2 (not used)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_3)->SetWindowText( "A&3 (not used)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_4)->SetWindowText( "A&4 (not used)" );
		GetDlgItem(IDC_CK_ARTIKEL_SORTIMENT_5)->SetWindowText( "A&5 (not used)" );
	}
	
	if (IsCountry("F"))
	{
//		m_PSYCHOTROP.SetMask("NPE",    m_pBufZartikel->PSYCHOTROP, 0  );		<-- passiert schon im InitPflege
		m_PSYCHOTROP.ResetContent();
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING10062));
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING10072));
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING887));
	} 
	else if (IsCountry("CH"))
	{
		m_PSYCHOTROP.ResetContent();
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING10062));
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING1354));
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING1355));
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING1356));
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING1357));
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING1358));
	} 
	// die österreichischen Werte waren mal der Default --> jetzt hier statt in FillComboBox
	// else if (!IsCountry("A"))
	else if (IsCountry("A"))
	{
//		m_PSYCHOTROP.SetMask("NJ",    m_pBufZartikel->PSYCHOTROP, 0  );			<-- passiert schon im InitPflege
		m_PSYCHOTROP.ResetContent();
/*		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING308));
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING309)); */
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING10062));
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING10072));
		m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING10073)); 
	}

	if (IsCountry("CH"))
	{
//		m_PRIVATSORTIMENT.SetMask("NZ", m_pBufZartikel->PRIVATSORTIMENT, 0 ); 	<-- passiert schon im InitPflege
		m_PRIVATSORTIMENT.ResetContent();
		m_PRIVATSORTIMENT.AddString(CResString::ex().getStrTblText(IDS_STRING311));
		m_PRIVATSORTIMENT.AddString(CResString::ex().getStrTblText(IDS_STRING312));
	}
}   

void CArtikelPage3::FillComboBox()
{
	m_KONTRAZEPTIVUM.ResetContent();
	m_BIOTECH_ARZNEI.ResetContent();
	m_PSYCHOTROP.ResetContent();
	m_PRODUKTART.ResetContent();
	m_PRIVATSORTIMENT.ResetContent();
	m_ABGABEBEST_IFA.ResetContent();
	m_NEGATIVLISTE.ResetContent();
	m_MPKLASSE.ResetContent();
	m_INVITROKLASSE.ResetContent();
	m_FMD.ResetContent();
	m_NEUARTIGETHERAPIEN.ResetContent();
	m_NOVELFOOD.ResetContent();

	// Änderungen müssen auch im PriceValidDelayView nachgezogen werden
	m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10059));
	m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10063));//Original
	m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10064));
	m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10065));
	m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10066));
	m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10067));
	m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10068));
	m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10069));
	m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10070));
	m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10071));
	if (IsCountry("D"))
	{
		m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING_PRODART_MARKETINGBED));
	}
	else if (IsCountry("CH"))
	{
		m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10406));
		m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10407));
		m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10408));
		m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10409));
		m_PRODUKTART.AddString(CResString::ex().getStrTblText(IDS_STRING10414));
	}
	/* die österreichischen Werte waren mal der Default --> geändert auf J/N analog InitPflege
	m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING10062));
	m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING10072));
	m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING10073)); */
	m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING308));
	m_PSYCHOTROP.AddString(CResString::ex().getStrTblText(IDS_STRING309));

	m_KONTRAZEPTIVUM.AddString(CResString::ex().getStrTblText(IDS_STRING10062));
	m_KONTRAZEPTIVUM.AddString(CResString::ex().getStrTblText(IDS_STRING10074));
	m_KONTRAZEPTIVUM.AddString(CResString::ex().getStrTblText(IDS_STRING10075));

	m_BIOTECH_ARZNEI.AddString(CResString::ex().getStrTblText(IDS_STRING269));
	m_BIOTECH_ARZNEI.AddString(CResString::ex().getStrTblText(IDS_STRING1451));
	m_BIOTECH_ARZNEI.AddString(CResString::ex().getStrTblText(IDS_STRING1452));
	m_BIOTECH_ARZNEI.AddString(CResString::ex().getStrTblText(IDS_STRING1453));

	m_PRIVATSORTIMENT.AddString(CResString::ex().getStrTblText(IDS_STRING10076));
	m_PRIVATSORTIMENT.AddString(CResString::ex().getStrTblText(IDS_STRING10077));
	m_PRIVATSORTIMENT.AddString(CResString::ex().getStrTblText(IDS_STRING10078));
	m_PRIVATSORTIMENT.AddString(CResString::ex().getStrTblText(IDS_STRING10079));
	m_PRIVATSORTIMENT.AddString(CResString::ex().getStrTblText(IDS_STRING10080));
	m_PRIVATSORTIMENT.AddString(CResString::ex().getStrTblText(IDS_STRING10081));
	m_PRIVATSORTIMENT.AddString(CResString::ex().getStrTblText(IDS_STRING10082));

	m_ABGABEBEST_IFA.AddString(" ");
	m_ABGABEBEST_IFA.AddString(CResString::ex().getStrTblText(IDS_STRING10112));
	m_ABGABEBEST_IFA.AddString(CResString::ex().getStrTblText(IDS_STRING10113));
	m_ABGABEBEST_IFA.AddString(CResString::ex().getStrTblText(IDS_STRING10114));
	m_ABGABEBEST_IFA.AddString(CResString::ex().getStrTblText(IDS_STRING10115));

	m_NEGATIVLISTE.AddString(CResString::ex().getStrTblText(IDS_STRING1271));	//nein
	m_NEGATIVLISTE.AddString(CResString::ex().getStrTblText(IDS_STRING1270));	//ja
	m_NEGATIVLISTE.AddString(CResString::ex().getStrTblText(IDS_STRING10102));	//eingeschränkt

	if (IsCountry("CH"))
	{ 
		m_MPKLASSE.AddString("");
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_I));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_IM));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_IR));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_IS));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_IIA));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_IIB));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_III));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_IVD));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_A));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_B));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_C));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING_MPCLASS_IF_D));
	}
	else
	{
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING10302));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1498));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1499));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1487));
		m_MPKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1488));
	}

	m_INVITROKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING10302));
	m_INVITROKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1489));
	m_INVITROKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1490));
	m_INVITROKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1491));
	m_INVITROKLASSE.AddString(CResString::ex().getStrTblText(IDS_STRING1492));

	m_FMD.AddString(CResString::ex().getStrTblText(IDS_STRING1271));	//nein
	m_FMD.AddString(CResString::ex().getStrTblText(IDS_STRING1480));	//ja, gesetzlich
	m_FMD.AddString(CResString::ex().getStrTblText(IDS_STRING1481));	//ja, freiwillig

	m_NEUARTIGETHERAPIEN.AddString("      keine Angabe");
	m_NEUARTIGETHERAPIEN.AddString(" 0 - nein");
	m_NEUARTIGETHERAPIEN.AddString(" 1 - ja, Gentherapeutikum");
	m_NEUARTIGETHERAPIEN.AddString(" 2 - ja, somat. Zelltherap.");
	m_NEUARTIGETHERAPIEN.AddString(" 3 - ja, Tumorimpfstoff");
	m_NEUARTIGETHERAPIEN.AddString(" 4 - ja, Biotech. b. Gewebepr.");
	m_NEUARTIGETHERAPIEN.AddString(" 5 - ja, kombiniertes ATMP");
	m_NEUARTIGETHERAPIEN.AddString("99 - ja, sonstiges ATMP");

	m_NOVELFOOD.AddString("      keine Angabe");
	m_NOVELFOOD.AddString("00 - nicht betr., kein Lebensm. = nein");
	m_NOVELFOOD.AddString("01 - kein Novel - Food = nein");
	m_NOVELFOOD.AddString("02 - Novel - Food unklar");
	m_NOVELFOOD.AddString("03 - Novel - Food EU - VO");
}

void CArtikelPage3::OnCkArtikelSortiment_1() 
{
	double dFaktor;

	m_SORTIMENT_1.p_GetInput();

	// Spezialverarbeitung nur für Kroatien, wenn Feld aktiviert wurde
	if (!IsCountry("HR") || m_pBufZartikel->SORTIMENT_1[0] != '1')
		return;

	// wenn Feld nur versehentlich ausgeschaltet und direkt wieder eingeschaltet wurde
	if (m_pBufOldZartikel->SORTIMENT_1[0] == '1')
		return;

	// wenn schon ein Umrechnungsfaktor eingetragen, fragen, ob neu lesen (YES) oder diesen verwenden (NO)
	// 28.01.10: keine Frage mehr stellen, sondern immer neu lesen
/*	if ( m_pBufZartcroatia->EXCHANGE_RATE > 0)
	{
		if ( MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING10265) ) != IDYES )
		{
			return;
		}
	} */

	// Versuch, Faktor aus rfiliale zu lesen 
	dFaktor = ((CArtikelView* )m_pView)->m_Doc.ReadUmrechnungsfaktor();

	if (dFaktor <= 0.0)
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING10266) );
		m_pBufZartikel->SORTIMENT_1[0] = '0';
		m_SORTIMENT_1.p_SetInput();
	}
	else
	{
		m_pBufZartcroatia->EXCHANGE_RATE = dFaktor;
		m_pBufZartcroatia->DATE_EXCHANGE_CALC = 0;

		// aktivieren auf Seite 5 
		CArtikelPage5HR *pP5HR;
		pP5HR = (CArtikelPage5HR *)((CArtikelView*)m_pView)->GetPage(4);
		pP5HR->Set_ExchangeRate();
	}
}

void CArtikelPage3::OnSelchangeCbPSYCHOTROP()
{
	if ( !IsCountry("CH") ) 
		return;

	m_dlg.DataExchangeToBuffer( m_Pos_PSYCHOTROP );

	/* Psychotrop hat jetzt in der Schweiz die Werte B-F statt J
	if ( strcmp ( m_pBufZartikel->PSYCHOTROP, "J") == 0 ) */
	if ( strcmp ( m_pBufZartikel->PSYCHOTROP, "N") != 0 ) 
	{
		m_pBufZartswitzerland->VERTRBIND_INLAND[0] = '1';

		// auf Seite 5CH im Dialogfeld aktivieren, wenn diese schon aktiv ist
		if ( ( (CArtikelView* )m_pView)->WasPageActive(4) )
		{
			CArtikelPage5CH *pP5;
			pP5 = (CArtikelPage5CH *)((CArtikelView*)m_pView)->GetPage(4);
			pP5->Set_Vertrbind_Inland();
		}
	}
	else
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING943) );
}

void CArtikelPage3::MakeSaisonwgString(CString Name, short Index)
{
	CString csAlleNamen;

	m_csAlleSaisonwgs[Index] = Name;

	csAlleNamen.Format("%s\n%s\n%s", m_csAlleSaisonwgs[0], m_csAlleSaisonwgs[1], m_csAlleSaisonwgs[2]);

	GetDlgItem( IDC_ST_ARTIKEL_SAISONWGR )->SetWindowText( csAlleNamen );

	// Font aendern (in den mehrzeiligen Statics kleiner, um etwas Platz auf dem Dialog zu schaffen)
	// nur, wenn die Seite auch schon aktiv war, sonst schmiert das Programm ab
	if (((CArtikelView* )m_pView)->WasPageActive(2) == TRUE ) 
	{
		CEkZdpApp* pApp = (CEkZdpApp*) AfxGetApp();
		m_pSmallFont = pApp->GetSmallFont();
		GetDlgItem( IDC_ST_ARTIKEL_SAISONWGR )->SetFont( m_pSmallFont );
	}
}
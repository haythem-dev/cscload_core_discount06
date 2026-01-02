// ArtikelPage2.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtikelPage2.h"
#include "ArtikelView.h"

#include "bssichg.h"

#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskDblPos.h>
#include <phxlib/PhxUtil.h>
#include "EtartDef.h"
#include "ServerDatum.h"

#include <phxlib/HerstelSelCtrl.h>
#include <phxlib/CcurrencySelCtrl.h>
#include <phxlib/CdeposittypesSelCtrl.h>
#include <phxlib/AtxSelCtrl.h> 

#include "FeldBreite.h"

#include <libscsvoodoo/libscsvoodoo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtikelPage2 property page

IMPLEMENT_DYNCREATE(CArtikelPage2, CPropertyPageMultiLang)

CArtikelPage2::CArtikelPage2() : ChPflegePage(CArtikelPage2::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage2)
	//}}AFX_DATA_INIT

	m_bInitialized = FALSE;
}

CArtikelPage2::~CArtikelPage2()
{
}

void CArtikelPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage2)
	DDX_Control(pDX, IDC_CK_ARTIKEL_EKORIGINALHS,			m_EKORIGINALHS);
	DDX_Control(pDX, IDC_CK_ARTIKEL_BESTELL_NUR_OZEK,		m_BESTELL_NUR_OZEK);
	DDX_Control(pDX, IDC_CO_BESTELL_NICHT_AUSL,				m_BESTELL_NICHT_AUSL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_FAELSCH_GEFAHR,			m_FAELSCH_GEFAHR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_KURZERVERFALL,			m_KURZERVERFALL);
	DDX_Control(pDX, IDC_CO_ARTIKEL_ZENTPPELIST,			m_ZENTRALPPELIST);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EAR_NUMMER,				m_EAR_NUMMER);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MELDENR,				m_MELDENR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_IS_WARENNUMMER,			m_IS_WARENNUMMER);
	DDX_Control(pDX, IDC_CO_ARTIKEL_PREISSENK,				m_PREISSENK);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_PREISSENKUNG,		m_DATUM_PREISSENKUNG);
	DDX_Control(pDX, IDC_CO_ARTIKEL_NAHR_TEST,				m_NAHR_TEST);
	DDX_Control(pDX, IDC_CO_ARTIKEL_NAHR_ERG,				m_NAHR_ERG);
	DDX_Control(pDX, IDC_CO_ARTIKEL_ELEKTROSCHROTT,			m_ELEKTROSCHROTT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_LAENGE,					m_LAENGE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_BREITE,					m_BREITE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_HOEHE,					m_HOEHE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GEWICHT,				m_GEWICHT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_VOLUMEN,				m_VOLUMEN);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_MWE,				m_DATUM_MWE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_BESTANDSBUCHUNG,		m_BESTANDSBUCHUNG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_MELDEPFL,				m_MELDEPFL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NICHT_UEBER_DAFUE,		m_NICHT_UEBER_DAFUE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NICHT_UEBER_XML,		m_NICHT_UEBER_XML);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ZENTR_EKSPERRE,			m_ZENTR_EKSPERRE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERBUNDSPERRE,			m_VERBUNDSPERRE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_FIXEDREGIONAL,			m_FIXEDREGIONAL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_BESTELLSPERRE,			m_BESTELLSPERRE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ARTIKEL_GELOESCHT,		m_ARTIKEL_GELOESCHT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_NR_ORIG,		m_ARTIKEL_NR_ORIG );
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_CODE_ORIG,		m_ARTIKEL_CODE_ORIG );
	DDX_Control(pDX, IDC_ED_ARTIKEL_STD_MENGE,				m_STD_MENGE);
	DDX_Control(pDX, IDC_CO_ARTIKEL_RUNDUNG_STD_MG,			m_RUNDUNG_STD_MGE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_KONSIG_PARTNER_NR ,		m_KONSIG_PARTNER_NR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_CHARGENARTIKEL,			m_CHARGENARTIKEL);
	DDX_Control(pDX, IDC_ED_ARTIKEL_FREMDWAEHRUNGSCODE ,	m_FREMDWAEHRUNGSCODE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_UMRECH_FAKTOR,			m_UMRECH_FAKTOR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PACK_GROESSE_FAKTOR,	m_PACKGROESSE_FAKTOR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_UMRECH,			m_DATUM_UMRECH);
	DDX_Control(pDX, IDC_CO_ARTIKEL_BATTERIEGESETZ,			m_BATTERIEGESETZ);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NEM_PHAGROPRUEFUNG,		m_NEM_PHAGROPRUEFUNG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NEM_ZERTIFIKAT,			m_NEM_ZERTIFIKAT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_KONTINGENT_PPE,			m_KONTINGENT_PPE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_KONTINGENT_HERST,		m_KONTINGENT_HERST);
	DDX_Control(pDX, IDC_CK_ARTIKEL_KONTINGENT_MENGENSTEUERUNG, m_KONTINGENT_MENGENSTEUERUNG);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PFANDTYP,				m_PFANDTYP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_TEXTKEY,				m_ATXKEY);
	DDX_Control(pDX, IDC_CK_ARTIKEL_APO_AUTO_KNAPP,			m_APO_AUTO_KNAPP);
	DDX_Control(pDX, IDC_CK_ARTIKEL_APO_AUTO_ROWA,			m_APO_AUTO_ROWA);
	DDX_Control(pDX, IDC_CO_BEZUGSSPERRE,					m_BEZUGSSPERRE);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CArtikelPage2, CPropertyPageMultiLang)
	//{{AFX_MSG_MAP(CArtikelPage2)
	ON_CBN_SELCHANGE(IDC_CO_ARTIKEL_PREISSENK,	OnSelchangeCbArtikelPreissenk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage2::MakeDialog()
{
	// Vertauscht wegen VPE_Pharmos disabled
	m_dlg.InitDialog( m_BESTANDSBUCHUNG );

//	m_dlg.InitDialog( m_BESTANDSBUCHUNG );
	m_dlg.InitDialog( m_MELDEPFL );

	m_dlg.InitDialog( m_NICHT_UEBER_DAFUE );
	m_dlg.InitDialog( m_NICHT_UEBER_XML );

	m_Pos_ZENTR_EKSPERRE = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ZENTR_EKSPERRE );

	m_Pos_VERBUNDSPERRE = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_VERBUNDSPERRE );
	m_dlg.InitDialog( m_FIXEDREGIONAL );

	m_dlg.InitDialog( m_BESTELLSPERRE );

	m_dlg.InitDialog( m_ARTIKEL_GELOESCHT );

	m_dlg.InitDialog( m_LAENGE  );
	m_dlg.InitDialog( m_BREITE );
	m_dlg.InitDialog( m_HOEHE  );
	m_dlg.InitDialog( m_GEWICHT );

	m_Pos_VOLUMEN = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_VOLUMEN );

	m_Pos_DATUM_MWE = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_DATUM_MWE  );

	m_dlg.InitDialog( m_PACKGROESSE_FAKTOR	);

	m_dlg.InitDialog( m_NAHR_TEST );

	m_Pos_NAHRUNGSERGAENZUNG = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_NAHR_ERG );

	m_Pos_ELEKTROSCHROTT = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ELEKTROSCHROTT );

	m_dlg.InitDialog( m_PREISSENK );

	m_Pos_DATUM_PREISSENKUNG = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_DATUM_PREISSENKUNG );

	m_Pos_ZENTRALPPELIST = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ZENTRALPPELIST );
	m_dlg.InitDialog( m_KONTINGENT_PPE );
	m_dlg.InitDialog( m_KONTINGENT_HERST );

	m_dlg.InitDialog(m_KONTINGENT_MENGENSTEUERUNG);

	m_Pos_EAR_NUMMER = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_EAR_NUMMER );
	m_dlg.InitDialog( m_MELDENR );
	m_dlg.InitDialog( m_IS_WARENNUMMER );

	m_dlg.InitDialog( m_EKORIGINALHS );
	m_dlg.InitDialog( m_BESTELL_NUR_OZEK );

	m_Pos_BESTELL_NICHT_AUSL = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_BESTELL_NICHT_AUSL );

	m_dlg.InitDialog( m_FAELSCH_GEFAHR );
	m_dlg.InitDialog( m_KURZERVERFALL );

	m_Pos_ARTIKEL_NR_ORIG = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ARTIKEL_CODE_ORIG );
	m_dlg.InitDialog( m_ARTIKEL_NR_ORIG );
	
	m_dlg.InitDialog( m_STD_MENGE );
	m_dlg.InitDialog( m_RUNDUNG_STD_MGE );

	m_dlg.InitDialog( m_KONSIG_PARTNER_NR );

	m_Pos_CHARGENARTIKEL = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_CHARGENARTIKEL );

	m_dlg.InitDialog( m_FREMDWAEHRUNGSCODE );
	m_dlg.InitDialog( m_UMRECH_FAKTOR );
	m_dlg.InitDialog( m_DATUM_UMRECH );

	m_dlg.InitDialog( m_BATTERIEGESETZ );

	m_dlg.InitDialog( m_NEM_PHAGROPRUEFUNG );
	m_dlg.InitDialog( m_NEM_ZERTIFIKAT );

	m_dlg.InitDialog( m_PFANDTYP );
	m_dlg.InitDialog( m_ATXKEY );

	m_dlg.InitDialog( m_APO_AUTO_KNAPP );
	m_dlg.InitDialog( m_APO_AUTO_ROWA );
		
	m_nMaxFields = m_dlg.GetFieldNumber();
}

/////////////////////////////////////////////
// Verknuepfungen Ruecksetzen

void CArtikelPage2::ResetVkn( )
{
	m_RD_ORIGINALARTIKEL.Reset();
	m_RD_WAEHRUNG.Reset();
	m_RD_PFANDTYP.Reset();
	m_RD_ARTTEXT.Reset();
}

/////////////////////////////////////////////////////////////
//  Verknuepfungen lesen

BOOL CArtikelPage2::TestEarnr( BOOL bMeldung )
{
	BOOL bOk = true;
	CString csEar;
	CString csFehlerText;
	int i;
	int iFehler = 0;

	csEar = m_pBufEarnr->ARTICLE_CODE;
	csEar.TrimRight();

	// leer ist ok
	if (csEar.IsEmpty())
	{
		return true;
	}

	/* nicht ausführen, wenn Werte auf dieser Page für diesen Artikel vorher nicht angezeigt wurden!
	   (sonst werden die Werte des vorher bearbeiteten Artikels eingesetzt !) */
	if (((CArtikelView* )m_pView)->WasPageActive(1) == TRUE)
		m_ELEKTROSCHROTT.p_GetInput();

	if (m_pBufZartikel->ELEKTROSCHROTT[0] != 'R') 
	{
		bOk = false;
		iFehler = 1;
	}
	else if (csEar.GetLength() != 10)
	{
		bOk = false;
		iFehler = 2;
	}
	else if (m_pBufEarnr->ARTICLE_CODE[0] != 'D' || 
			 m_pBufEarnr->ARTICLE_CODE[1] != 'E')
	{
		bOk = false;
		iFehler = 3;
	}
	else
	{
		for (i = 2; i <= 9; i++)
		{
			if ( !isdigit( (unsigned char)csEar.GetAt( i ) ) )
			{
				bOk = false;
				iFehler = 4;
				break;
			}
		}
	}

	if ( !bOk && bMeldung )
	{
		switch (iFehler)
		{
			case 1: csFehlerText = CResString::ex().getStrTblText(IDS_STRING275);
			break;

			case 2: csFehlerText = CResString::ex().getStrTblText(IDS_STRING276);
			break;

			case 3: csFehlerText = CResString::ex().getStrTblText(IDS_STRING277);
			break;

			case 4: csFehlerText = CResString::ex().getStrTblText(IDS_STRING278);
			break;
		}
        
		MsgBoxOK( csFehlerText );
	}

	return bOk;
}

BOOL CArtikelPage2::ShowOriginalArtikel( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	// folgende Konstellation vermeiden: 
	// - Originalartikel wird gesetzt, ist aber noch nicht vorhanden
	// - Originalartikel wird neu angelegt
	// - Fehlermeldung kommt immer noch, weil m_lKey unveraendert und daher kein neues Lesen
	if (m_RD_ORIGINALARTIKEL.ShowLastKey() == m_pBufZartikel->ARTIKEL_NR)
	{
		m_RD_ORIGINALARTIKEL.Reset();
	}

	iStat = m_RD_ORIGINALARTIKEL.IPlausi( m_pBufZartikel->ARTIKEL_NR_ORIG, Name, &Errmld);
	if ( TRUE == bShow ){	// neu
		GetDlgItem( IDC_ST_ARTIKEL_ARTIKEL_NR_ORIG )->SetWindowText( Name );
		SetArticleCodeEditCtrl();
	}
	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage2::SetArticleCodeEditCtrl()
{
	CString no;
	CString code;
	CString cErrmld;
	m_ARTIKEL_NR_ORIG.GetWindowText(no);
	code = CArticleCodesConverter::getPreferredCodeByNo( atol(no), cErrmld );
	strcpy(m_ORIGINAL_ARTCODE, code);
	m_ARTIKEL_CODE_ORIG.p_SetInput();
}

void CArtikelPage2::SucheOriginalArtikel( )
{
	CZartikelSelCtrl m_SelBox;
	m_SelBox.SetPflegeProgNeuheit( NH_NEUHEIT_PHARMOS );
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_AUSWAHL_OPZN), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

//	dlg.RestoreAuswahlIndex( m_nAuswahlIndex );
//	dlg.RestoreAuswahlIndex2( m_nAuswahlIndex2 );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_pBufZartikel->ARTIKEL_NR_ORIG ) == 0 )
		{
			m_ARTIKEL_NR_ORIG.p_SetInput();
			//m_ARTIKEL_NR_ORIG.SetFocus();
			m_ARTIKEL_CODE_ORIG.SetFocus();
			ShowOriginalArtikel( TRUE );
		}
	}
	m_SelBox.CloseCursor();

//	m_nAuswahlIndex = dlg.GetAuswahlIndex( );
//	m_nAuswahlIndex2 = dlg.GetAuswahlIndex2( );
}

// Konsignationspartner

BOOL CArtikelPage2::ShowKonsigPartner( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	CString PPE;
	CString cZentralppeList;
	iStat = m_RD_KONSIG_PARTNER.IPlausi( m_pBufZartikel->KONSIG_PARTNER_NR, Name, PPE, cZentralppeList,
									 &Errmld);
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_KONSIG_PARTNER_NR )->SetWindowText( Name );

	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;

}

void CArtikelPage2::SucheKonsigPartner( )
{
	CHerstelSelCtrl m_SelBox( IM_NUMBER_S );
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_SEL_HERST), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_pBufZartikel->KONSIG_PARTNER_NR ) == 0 )
		{
			m_KONSIG_PARTNER_NR.p_SetInput();
			m_KONSIG_PARTNER_NR.SetFocus();
			ShowKonsigPartner( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

BOOL CArtikelPage2::ShowFremdwaehrung( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	short Hauswaehrung = 0;

	iStat = m_RD_WAEHRUNG.IPlausi( m_pBufCartforeigncurr->CURRENCYCODE, Name, Hauswaehrung, &Errmld);

	// Eingabe von Hauswährung nicht erlaubt
	if (Hauswaehrung == 1)
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1110) );
		return false;
	}

	if ( bShow )
		GetDlgItem( IDC_ST_ARTIKEL_FREMDWAEHRUNG )->SetWindowText( Name );

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

void CArtikelPage2::SucheFremdwaehrung( )
{
	CCcurrencySelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1013), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
//		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_pBuf->currencyId ) == 0 )
		if ( m_SelBox.CodeOfSelectedRecord( m_pBufCartforeigncurr->CURRENCYCODE ) == 0 )
		{
			m_FREMDWAEHRUNGSCODE.p_SetInput();
			m_FREMDWAEHRUNGSCODE.SetFocus();
			ShowFremdwaehrung( TRUE );
		}
	}

	m_SelBox.CloseCursor();
}

// Pfand-Typ
BOOL CArtikelPage2::ShowPfandTyp( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	double Wert = 0.0;
	CString Anzeige;
	CString Errmld;
	iStat = m_RD_PFANDTYP.IPlausi( m_pBufPfandTyp->WARENGRUPPE, Wert, &Errmld);

	if ( bShow )	// neu
	{
		Anzeige.Format("%.2f", Wert);
		GetDlgItem( IDC_ST_ARTIKEL_PFANDWERT )->SetWindowText( Anzeige );
	}

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

void CArtikelPage2::SuchePfandTyp( )
{
	CCdeposittypesSelCtrl	m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1328), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufPfandTyp->WARENGRUPPE ) == 0 )
		{
			m_PFANDTYP.p_SetInput();
			m_PFANDTYP.SetFocus();
			ShowPfandTyp( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

/**---------------------------------------------------------------------------*/
BOOL CArtikelPage2::ShowArtText( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString NameLang;
	CString Errmld;
	iStat = m_RD_ARTTEXT.IPlausi( m_pBufArtText->WARENGRUPPE, Name, NameLang, &Errmld);
	if ( bShow )	// neu
	{
		if (IsCountry("A") ||
			NameLang.GetLength() == 0)
			GetDlgItem( IDC_ST_ARTIKEL_TEXT )->SetWindowText( Name );
		else
			GetDlgItem( IDC_ST_ARTIKEL_TEXT )->SetWindowText( NameLang );
	}
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/**---------------------------------------------------------------------------*/
void CArtikelPage2::SucheArtText( )
{
	CAtxSelCtrl m_SelBox;

    ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING315), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufArtText->WARENGRUPPE ) == 0 )
		{
			m_ATXKEY.p_SetInput();
			m_ATXKEY.SetFocus();
			ShowArtText( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

/////////////////////////////////////////////////////////////
//  Validierung

class CV_ARTIKEL_Earnr : public ChValBase
{
public:
	CV_ARTIKEL_Earnr( CArtikelPage2* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage2*)m_pWnd)->TestEarnr( bMeldung );
		return bOk;
	}
};

class CV_ARTIKEL_Volumen : public ChValBase
{
public:
	CV_ARTIKEL_Volumen( CArtikelPage2* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL )
	{
		int iVolume;
		iVolume = ((CArtikelPage2*)m_pWnd)->CalculateVolume ( );

		((CArtikelPage2*)m_pWnd)->SetVolume(iVolume);
		((CArtikelPage2*)m_pWnd)->m_VOLUMEN.p_SetInput( );

		((CArtikelPage2*)m_pWnd)->CheckMeasureWeightChange();

		return true;
	}
};

class CV_ARTIKEL_OriginalArtikel : public ChValBase
{
public:
	CV_ARTIKEL_OriginalArtikel( struct ZARTIKEL *pBuf, CArtikelPage2* pView ) 
		: ChValBase( pBuf, pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		CArtikelPage2* parent = ((CArtikelPage2*)m_pWnd);

		CString cErrmld;

		if ( FALSE == parent->SetArticleNoEditCtrl( cErrmld ) ){
			return FALSE;
		}
		
		bOk = parent->ShowOriginalArtikel( bMeldung, bMeldung );
		if ( bOk )
		{
			if ( (( struct ZARTIKEL*)m_pBuf)->ARTIKEL_NR_ORIG == 
				 (( struct ZARTIKEL*)m_pBuf)->ARTIKEL_NR			)
			{
				if ( bMeldung )
					MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_DIFF_OPZN)) );
				bOk = FALSE;
			}
		}
		return bOk;

	}
	void NotifyProc( )
	{
		((CArtikelPage2*)m_pWnd)->SucheOriginalArtikel( );
	}
/*	void PostProc( )
	{
		CString cErrmld;
		CArtikelPage2* parent = ((CArtikelPage2*)m_pWnd);
		
		parent->SetArticleNoEditCtrl( cErrmld );
	}
*/
};

class CV_ARTIKEL_Konsig_Partner : public ChValBase
{
public:
	CV_ARTIKEL_Konsig_Partner( CArtikelPage2* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtikelPage2*)m_pWnd)->ShowKonsigPartner( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtikelPage2*)m_pWnd)->SucheKonsigPartner( );
	}
};

class CV_ARTIKEL_Fremdwaehrung : public ChValBase
{
public:
	CV_ARTIKEL_Fremdwaehrung( CArtikelPage2* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage2*)m_pWnd)->ShowFremdwaehrung( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage2*)m_pWnd)->SucheFremdwaehrung( );
	}
};

class CV_ARTIKEL_PfandTyp : public ChValBase
{
public:
	CV_ARTIKEL_PfandTyp( CArtikelPage2* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage2*)m_pWnd)->ShowPfandTyp( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage2*)m_pWnd)->SuchePfandTyp( );
	}
};

/**---------------------------------------------------------------------------*/
class CV_ARTIKEL_Atx : public ChValBase
{
public:
	CV_ARTIKEL_Atx( CArtikelPage2* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage2*)m_pWnd)->ShowArtText( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage2*)m_pWnd)->SucheArtText( );
	}
};

/////////////////////////////////////////////////////////////
//  EndValidierung 

BOOL CArtikelPage2::EndValidate( int *ind, BOOL bMeldung )
{
	*ind = 0;

	if ( *m_pBufZartikel->ZENTRALPPELIST != '0' && *m_pBufZartikel->ZENTRALPPELIST != '8' )
	{
		// BTM und ZENTRALPPELIST
		if ( *m_pBufZartikel->BTM == '1' )
		{
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING279) );
			*ind = m_Pos_ZENTRALPPELIST;
			return FALSE;
		}

		// KUEHLARTIKEL und ZENTRALPPELIST
		if ( *m_pBufZartikel->KUEHLARTIKEL == '4' || *m_pBufZartikel->KUEHLARTIKEL == '1' )
		{
			if ( bMeldung )
				MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING280));
			*ind = m_Pos_ZENTRALPPELIST;
			return FALSE;
		}

		// TIERARZNEI und ZENTRALPPELIST
		if ( *m_pBufZartikel->TIERARZNEI == '1' )
		{
			if ( bMeldung )
				MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING1305));
			*ind = m_Pos_ZENTRALPPELIST;
			return FALSE;
		}

		// TFG und ZENTRALPPELIST
		if ( *m_pBufZartikel->TFG == '1' || *m_pBufZartikel->TFG == '2' )
		{
			if ( bMeldung )
				MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING1306));
			*ind = m_Pos_ZENTRALPPELIST;
			return FALSE;
		}

		// MELDEPFL und ZENTRALPPELIST
		if ( *m_pBufZartikel->MELDEPFL == '1' )
		{
			if ( bMeldung )
				MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING1307));
			*ind = m_Pos_ZENTRALPPELIST;
			return FALSE;
		}
	}

	// Elektroschrott und zentr. Einkaufssperre (NEM-Sperre nicht mehr lt. Hr. Peetz)
	if ( *m_pBufZartikel->ELEKTROSCHROTT == 'J' &&
	   ( *m_pBufZartikel->ZENTR_EKSPERRE != '1' ) )
//	     *m_pBufZartikel->NAHRUNGSERGAENZUNG != 'G' ) )
	{
		if ( bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING281) );

		*ind = m_Pos_ELEKTROSCHROTT;
		return FALSE;
	} 

	// Nachfrage zu bestell_nicht_ausl und nahrungstest / biozid_verord / batteriegesetz:
	// muss aber nicht zwingend korrigiert werden !
	// nur für D !
	if (	IsCountry("D") &&
		( *m_pBufZartikel->NAHRUNGSTEST != ' ' || *m_pBufZartikel->BIOZID_VERORD == '1' || (*m_pBufZartikel->BATTERIEGESETZ != 'N' && *m_pBufZartikel->BATTERIEGESETZ != '0') || *m_pBufZartikel->PSYCHOTROP == 'J' ) &&
		   *m_pBufZartikel->BESTELL_NICHT_AUSL == '0' )
	{
		if ( bMeldung )
		{
			if (MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING1251), 
								MB_ICONQUESTION | MB_DEFBUTTON1 ) == IDYES )
			{
				*ind = m_Pos_BESTELL_NICHT_AUSL;
				return FALSE;
			}
		}
		else
		{
			*ind = m_Pos_BESTELL_NICHT_AUSL;
			return FALSE;
		}
	}

	if (	IsCountry("D") && m_pBufZartikel->KOSMETIKUM == 1 && *m_pBufZartikel->BESTELL_NICHT_AUSL == '0' )
	{
		if ( bMeldung == FALSE || MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING1362), MB_ICONQUESTION | MB_DEFBUTTON1 ) == IDYES)
		{
			*ind = m_Pos_BESTELL_NICHT_AUSL;
			return FALSE;
		}
	}

	if(IsCountry("D"))
	{
		CString strEar;
		if(m_pBufEarnr != NULL)
		{
			strEar = m_pBufEarnr->ARTICLE_CODE;
			strEar = strEar.Trim();
		}

		if(*m_pBufZartikel->ELEKTROSCHROTT == 'R' && strEar.GetLength() == 0)
		{
			if(bMeldung)
			{
				MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING10410) );
			}
			
			*ind = m_Pos_EAR_NUMMER;
			return FALSE;
		}

		if (m_pBufZartikel->VERBUNDSPERRE == 1 && m_pBufCibt->ISFIXEDREGIONAL == 1)
		{
			if(bMeldung)
			{
				MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING10412) );
			}

			*ind = m_Pos_VERBUNDSPERRE;
			return FALSE;
		}
		
		
		if (m_pBufZartikel->CMI_FLAG == 1)
		{
			if (m_pBufZartikel->APO_AUTO_FAEHIG_KNAPP == 1 || m_pBufZartikel->APO_AUTO_FAEHIG_ROWA == 1)
			{
				if(bMeldung)
				{
					MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING_APO_CMI_CONFLICT) );
				}
				return FALSE;
			}
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////
//  Dialogfelder

void CArtikelPage2::InitPflege( CWnd *pView  )
{
	CArtikelPage2* pThisView = this;
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )pView)->GetBuffer();
	m_pBufZartikel			= &m_Buf->zartikel;
	m_pBufEarnr				= &m_Buf->carticlecodes[0];	// code_type = 1
	m_pBufISWarennr			= &m_Buf->carticlecodes[5];	// code_type = 6
	m_pBufCartforeigncurr	= &m_Buf->cartforeigncurr;
	m_pBufPfandTyp			= &m_Buf->zartwg[11];		// art = 'C'
	m_pBufArtText			= &m_Buf->zartwg[6];		// art = 7
	m_pBufCarticleext		= &m_Buf->carticleext;
	m_pBufCibt				= &m_Buf->cibt;

	MakeDialog();

	m_LAENGE.SetMask		(ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartikel->LAENGE,
                             6,
							 new ChMaskNum, 
							 new CV_ARTIKEL_Volumen( pThisView ));

	m_BREITE.SetMask		(ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartikel->BREITE,
                             6,
							 new ChMaskNum, 
							 new CV_ARTIKEL_Volumen( pThisView ));

	m_HOEHE.SetMask			(ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartikel->HOEHE,
                             6,
							 new ChMaskNum, 
							 new CV_ARTIKEL_Volumen( pThisView ));

	m_GEWICHT.SetMask		(ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartikel->GEWICHT,
                             8,
							 new ChMaskNum, 
							 // auch Volumenklasse wg. zurücksetzen MWE-Datum
							 new CV_ARTIKEL_Volumen( pThisView ));

	m_VOLUMEN.SetMask		(ED_LONG,
                             ED_NORMAL,
							 &m_Buf->iVolumen,
                             8,
							 new ChMaskNum );

	m_DATUM_MWE.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufZartikel->DATUM_MWE,
                             L_LDATUM,
                             new ChMaskLDate);

	m_MELDEPFL.SetMask			('1', '0', m_pBufZartikel->MELDEPFL );

	m_NICHT_UEBER_DAFUE.SetMask	('1', '0', m_pBufZartikel->NICHT_UEBER_DAFUE );
	m_NICHT_UEBER_XML.SetMask	('1', '0', m_pBufZartikel->NICHT_UEBER_XML );

	m_BESTANDSBUCHUNG.SetMask	('1', '0', m_pBufZartikel->BESTANDSBUCHUNG );

	m_ZENTR_EKSPERRE.SetMask	('1', '0', m_pBufZartikel->ZENTR_EKSPERRE );

	m_VERBUNDSPERRE.SetMask		( 1, 0, &m_pBufZartikel->VERBUNDSPERRE );

	m_FIXEDREGIONAL.SetMask		( 1, 0, &m_pBufCibt->ISFIXEDREGIONAL );

	m_BESTELLSPERRE.SetMask		('1', '0', m_pBufZartikel->BESTELLSPERRE );
	m_ARTIKEL_GELOESCHT.SetMask	('1', '0', m_pBufZartikel->ARTIKEL_GELOESCHT );

	m_NAHR_TEST.SetMask			( _strdup(CResString::ex().getStrTblText(IDS_STRING283)) , m_pBufZartikel->NAHRUNGSTEST );
	m_NAHR_ERG.SetMask			( _strdup(CResString::ex().getStrTblText(IDS_STRING284)) , m_pBufZartikel->NAHRUNGSERGAENZUNG ); 
	m_ELEKTROSCHROTT.SetMask	( "NJRI", m_pBufZartikel->ELEKTROSCHROTT ); 

	m_EAR_NUMMER.SetMask	(ED_CHAR,
							 ED_UPPER,
			                 m_pBufEarnr->ARTICLE_CODE,
				             L_CARTICLECODES_ARTICLE_CODE,
   						     new ChMaskChar,
							 new CV_ARTIKEL_Earnr( pThisView ));

	m_MELDENR.SetMask		(ED_CHAR,
							 ED_UPPER,
							 m_pBufZartikel->BATTREG,
							 L_ZARTIKEL_BATTREG,
							 new ChMaskChar);

	m_PREISSENK.SetMask		( "0123459"  , m_pBufZartikel->PREISSENKUNG ); 

	m_IS_WARENNUMMER.SetMask(ED_CHAR,
							 ED_UPPER,
			                 m_pBufISWarennr->ARTICLE_CODE,
				             L_CARTICLECODES_ARTICLE_CODE,
   						     new ChMaskChar);
			  	    
	m_DATUM_PREISSENKUNG.SetMask	(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufZartikel->DATUM_PREISSENKUNG,
                             L_LDATUM,
                             new ChMaskLDate);

	// Abfragen schon hier und nicht erst im Translation, weil sonst landesspezifische Feldinhalte nicht definiert sind und ggfs. Werte automatisch zurückgesetzt werden
	if (IsCountry("CH"))
		m_ZENTRALPPELIST.SetMask  ( "01289",  m_pBufZartikel->ZENTRALPPELIST ); 
	else if (IsCountry("D"))
		m_ZENTRALPPELIST.SetMask  ( "018", m_pBufZartikel->ZENTRALPPELIST ); 
	else
		m_ZENTRALPPELIST.SetMask  ( "0",    m_pBufZartikel->ZENTRALPPELIST ); 

	m_KONTINGENT_PPE.SetMask  ('1', '0',  m_pBufZartikel->KONTINGENT_PPE );
	m_KONTINGENT_HERST.SetMask  (1, 0,  &m_pBufZartikel->HERST_KONTINGENT );

	m_KONTINGENT_MENGENSTEUERUNG.SetMask(1, 0, &m_pBufZartikel->KONTINGENT_MENGENSTEUERUNG);

	m_EKORIGINALHS.SetMask  ('1', '0', m_pBufZartikel->EKORIGINALHS );

	m_BESTELL_NUR_OZEK.SetMask  ('1', '0', m_pBufZartikel->BESTELL_NUR_OZEK );
	m_BESTELL_NICHT_AUSL.SetMask( "012"  , m_pBufZartikel->BESTELL_NICHT_AUSL ); 

	m_FAELSCH_GEFAHR.SetMask	('1', '0', m_pBufZartikel->FAELSCH_GEFAHR );
	m_KURZERVERFALL.SetMask		( 1, 0, &m_pBufCarticleext->SHORTEXPIRYFLAG );

	m_ARTIKEL_CODE_ORIG.SetMask (ED_CHAR,
								ED_UPPER,
								m_ORIGINAL_ARTCODE,
								L_CARTICLECODES_ARTICLE_CODE,
								new ChMaskChar,
								new CV_ARTIKEL_OriginalArtikel( m_pBufZartikel,
																pThisView ) );
	m_ARTIKEL_NR_ORIG.SetMask (ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartikel->ARTIKEL_NR_ORIG,
                             L_ARTIKEL_NR,
							 new ChMaskNum,
							 new CV_ARTIKEL_OriginalArtikel( m_pBufZartikel,
														 pThisView ) );
	m_STD_MENGE.SetMask		(ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartikel->STD_MENGE,
                             6,
							 new ChMaskNum );

	m_RUNDUNG_STD_MGE.SetMask	( "012"  , m_pBufZartikel->RUNDUNG_STD_MGE ); 

	m_KONSIG_PARTNER_NR.SetMask	(ED_LONG,
						     ED_NORMAL,
							 &m_pBufZartikel->KONSIG_PARTNER_NR,
							 L_HERSTELLER_NR,
							 new ChMaskNum,
							 new CV_ARTIKEL_Konsig_Partner( pThisView ) );

	m_CHARGENARTIKEL.SetMask ( '1', '0', m_pBufZartikel->CHARGENARTIKEL);

	m_FREMDWAEHRUNGSCODE.SetMask	(ED_CHAR,
						     ED_UPPER,
							 m_pBufCartforeigncurr->CURRENCYCODE,
							 L_CARTFOREIGNCURR_CURRENCYCODE,
							 new ChMaskChar, 
							 new CV_ARTIKEL_Fremdwaehrung( pThisView ) );

	m_UMRECH_FAKTOR.SetMask		(ED_DBL,
								 ED_NORMAL,
								 &m_pBufCartforeigncurr->EXCHANGE_RATE,
								 L_CARTFOREIGNCURR_EXCHANGE_RATE + 1,
								 N_CARTFOREIGNCURR_EXCHANGE_RATE,
								 new ChMaskDblPos );

	m_PACKGROESSE_FAKTOR.SetMask(ED_DBL,
								 ED_NORMAL,
								 &m_pBufZartikel->PACKGROESSE_FAKTOR,
								 L_ZARTIKEL_PACKGROESSE_FAKTOR + 1,
								 N_ZARTIKEL_PACKGROESSE_FAKTOR,
								 new ChMaskDblPos );

	m_DATUM_UMRECH.SetMask		(ED_LDATE,
								 ED_NORMAL,
								 &m_pBufCartforeigncurr->DATE_EXCHANGE_CALC,
								 L_LDATUM,
								 new ChMaskLDate);

	m_BATTERIEGESETZ.SetMask( "NJLXYZ", m_pBufZartikel->BATTERIEGESETZ ); 

	m_NEM_PHAGROPRUEFUNG.SetMask('1', '0', m_pBufZartikel->NEM_PHAGROPRUEFUNG );

	m_NEM_ZERTIFIKAT.SetMask	('1', '0', m_pBufZartikel->NEM_ZERTIFIKAT );

	m_PFANDTYP.SetMask			(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufPfandTyp->WARENGRUPPE,
				                 5,
								 new ChMaskNum,
								 new CV_ARTIKEL_PfandTyp( pThisView ) );

	m_ATXKEY.SetMask   (ED_CHAR,
                        ED_CLINPUT,
						m_pBufArtText->WARENGRUPPE,
                        L_CARTICLETEXT_TEXTNO,
					    new ChMaskNum,
						new CV_ARTIKEL_Atx( pThisView ) );

	m_APO_AUTO_KNAPP.SetMask	(1, 0, &m_pBufZartikel->APO_AUTO_FAEHIG_KNAPP );
	m_APO_AUTO_ROWA.SetMask		(1, 0, &m_pBufZartikel->APO_AUTO_FAEHIG_ROWA );
	
	m_bInitialized = TRUE;
}
    
/////////////////////////////////////////////////////////////
// ChPflegePage functions 
 
void CArtikelPage2::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CArtikelPage2::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage2::EnableFields( BOOL bEnab )
{   
	m_dlg.EnableFields( bEnab );

	// Volumen und MWE-Datum immer disabled
	m_dlg.EnableFields(m_Pos_VOLUMEN, FALSE );
	m_dlg.EnableFields(m_Pos_DATUM_MWE, FALSE );

	// Umrechnungsfaktor und -datum immer disabled
	m_UMRECH_FAKTOR.EnableWindow(false);
	m_DATUM_UMRECH.EnableWindow(false);

	// Datum Preissenkung immer disabled
	m_dlg.EnableFields(m_Pos_DATUM_PREISSENKUNG, FALSE );

	if ( !IsCountry("D") )
	{
		m_FIXEDREGIONAL.EnableWindow(false);
	}

	if (IsCountry("CH"))
	{
		m_NAHR_ERG.EnableWindow(false);
		m_NAHR_TEST.EnableWindow(false);
		m_ELEKTROSCHROTT.EnableWindow(false);
		m_EAR_NUMMER.EnableWindow(false);
		m_BATTERIEGESETZ.EnableWindow(false);
		m_NEM_PHAGROPRUEFUNG.EnableWindow(false);
		m_NEM_ZERTIFIKAT.EnableWindow(false);
		m_FREMDWAEHRUNGSCODE.EnableWindow(false);
		m_PACKGROESSE_FAKTOR.EnableWindow(false);
		m_KONTINGENT_PPE.EnableWindow(false);
		m_STD_MENGE.EnableWindow(false);
		m_PFANDTYP.EnableWindow(false);
		m_RUNDUNG_STD_MGE.EnableWindow(false);
	}

	if (IsCountry("HR"))
	{
		m_NAHR_ERG.EnableWindow(false);
		m_NAHR_TEST.EnableWindow(false);
		m_ELEKTROSCHROTT.EnableWindow(false);
		m_EAR_NUMMER.EnableWindow(false);
// 		m_IS_WARENNUMMER.EnableWindow(false);
		m_EKORIGINALHS.EnableWindow(false);
		m_BESTELL_NUR_OZEK.EnableWindow(false);
		m_BESTELL_NICHT_AUSL.EnableWindow(false);
		m_BESTELLSPERRE.EnableWindow(false);
		m_PREISSENK.EnableWindow(false);
		m_ZENTRALPPELIST.EnableWindow(false);
		m_ARTIKEL_NR_ORIG.EnableWindow(false);

/* RR 13.02.18: Maße und Gewicht in Kroatien pflegbar
		m_LAENGE.EnableWindow(false);
		m_BREITE.EnableWindow(false);
		m_HOEHE.EnableWindow(false);
		m_GEWICHT.EnableWindow(false); */
		
		m_MELDEPFL.EnableWindow(false);
//		m_BESTANDSBUCHUNG.EnableWindow(false);
		m_STD_MENGE.EnableWindow(false);
		m_RUNDUNG_STD_MGE.EnableWindow(false);
		m_BATTERIEGESETZ.EnableWindow(false);
		m_NEM_PHAGROPRUEFUNG.EnableWindow(false);
		m_NEM_ZERTIFIKAT.EnableWindow(false);
		m_FREMDWAEHRUNGSCODE.EnableWindow(false);
	} 

	/* mit FMD / BatchTracking sollte dieses Kennzeichen auch pflegbar sein !
	// Chargenfeld wird automatisch gefüllt in HR und in D bei Nicht-Konsignationsartikeln
	if ((IsCountry("D") && m_pBufZartikel->KONSIG_PARTNER_NR == 0) || 
		 IsCountry("HR"))
		m_CHARGENARTIKEL.EnableWindow(false);
	*/

	DisableSpecial();

	m_BEZUGSSPERRE.EnableWindow(bEnab);

	if (!IsCountry("D"))
	{
		m_KONTINGENT_MENGENSTEUERUNG.EnableWindow(false);
	}
}

void CArtikelPage2::DisableSpecial()
{
	m_ARTIKEL_NR_ORIG.EnableWindow(false); // Eingabe nur noch in Artikel-Code-Feld
	m_ARTIKEL_NR_ORIG.ShowWindow(SW_HIDE);

	if (!IsCountry("D"))
	{
		m_MELDENR.ShowWindow(SW_HIDE);
		GetDlgItem( IDC_ST_ARTIKEL_MELDENR )->ShowWindow(SW_HIDE);
	}
}

void CArtikelPage2::ShowFields( )
{
	FillComboBox();
	Translation();

	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )m_pView)->GetBuffer();
	m_Buf->iVolumen = CalculateVolume();

	m_dlg.ShowFields();	

	ShowOriginalArtikel( TRUE );
	ShowKonsigPartner( TRUE );
	ShowFremdwaehrung( TRUE );
	ShowPfandTyp( TRUE );
	ShowArtText( TRUE );

	SetBatteriegesetz();

	ShowBezugssperre(  );
}


void CArtikelPage2::ShowBezugssperre()
{
	short bezugsSperre = m_pBufZartikel->BEZUGSSPERRE;

	if (bezugsSperre == 1 || bezugsSperre == 3 || bezugsSperre == 5 || bezugsSperre == 7)
		m_BEZUGSSPERRE.SetCheck(0, TRUE);
	else
		m_BEZUGSSPERRE.SetCheck(0, FALSE);

	if (bezugsSperre == 2 || bezugsSperre == 3 || bezugsSperre == 6 || bezugsSperre == 7)
		m_BEZUGSSPERRE.SetCheck(1, TRUE);
	else
		m_BEZUGSSPERRE.SetCheck(1, FALSE);

	if (bezugsSperre == 4 || bezugsSperre == 5 || bezugsSperre == 6 || bezugsSperre == 7)
		m_BEZUGSSPERRE.SetCheck(2, TRUE);
	else
		m_BEZUGSSPERRE.SetCheck(2, FALSE);
}

void CArtikelPage2::SetBatteriegesetz()
{
	if(m_pBufZartikel->BATTERIEGESETZ[0] == '0')
	{
		m_BATTERIEGESETZ.SetCurSel(0);
	}

	if(m_pBufZartikel->BATTERIEGESETZ[0] == '1')
	{
		m_BATTERIEGESETZ.SetCurSel(1);
	}
}

void CArtikelPage2::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage2::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();

	CalcBezugssperre();
}

void CArtikelPage2::CalcBezugssperre()
{
	BOOL isOrigHerstBlocked = m_BEZUGSSPERRE.GetCheck(0);
	BOOL isZwhBlocked		= m_BEZUGSSPERRE.GetCheck(1);
	BOOL isApothekeBlocked	= m_BEZUGSSPERRE.GetCheck(2);

	short bezugsSperre = 0;
	
	if (isOrigHerstBlocked)
	{
		if (isZwhBlocked)
		{
			if (isApothekeBlocked)
				bezugsSperre = 7;
			else
				bezugsSperre = 3;
		}
		else
		{
			if (isApothekeBlocked)
				bezugsSperre = 5;
			else
				bezugsSperre = 1;
		}
	}
	else
	{
		if (isZwhBlocked)
		{
			if (isApothekeBlocked)
				bezugsSperre = 6;
			else
				bezugsSperre = 2;
		}
		else
		{
			if (isApothekeBlocked)
				bezugsSperre = 4;
			else
				bezugsSperre = 0;
		}
	}

	m_pBufZartikel->BEZUGSSPERRE = bezugsSperre;
}


void CArtikelPage2::ActivateField( int nr )
{
    m_dlg.ActivateField( nr );
}


BOOL CArtikelPage2::Validate( BOOL bMeldung )
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

BOOL CArtikelPage2::OnSetActive()
{
	BOOL bOk;
	bOk = CPropertyPageMultiLang::OnSetActive();
	if ( bOk && m_bInitialized )
	{
		ShowFields();
		((CArtikelView* )m_pView)->Set_WasActive();
		EnableFields( ((CArtikelView* )m_pView)->AreFieldsEnabled() );
		GetParent()->SendMessage( WM_USER+10 );
		SetValidation( TRUE );
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING286) );
	}
	return bOk;
}

BOOL CArtikelPage2::OnKillActive()
{
	BOOL bOk;
	bOk = CPropertyPageMultiLang::OnKillActive();
	if ( bOk )
	{
		SetValidation( FALSE );
		DataExchangeToBuffer( );  //  Puffer wie Eingabe
	}
	return bOk;
}

void CArtikelPage2::Set_Elektroschrott( )
{
	m_dlg.DataExchangeFromBuffer( m_Pos_ELEKTROSCHROTT );
	m_dlg.DataExchangeFromBuffer( m_Pos_ZENTR_EKSPERRE );

	// muss nicht mehr gesetzt werden
	// m_dlg.DataExchangeFromBuffer( m_Pos_NAHRUNGSERGAENZUNG );
}

BOOL CArtikelPage2::SetArticleNoEditCtrl( CString& cErrmld )
{
	// nicht ausführen, wenn Werte auf dieser Page für diesen Artikel vorher nicht angezeigt wurden!
	// (sonst werden die Werte des vorher bearbeiteten Artikels eingesetzt !)
	if (((CArtikelView* )m_pView)->WasPageActive(1) == FALSE)
		return TRUE;
		
	m_ARTIKEL_CODE_ORIG.p_GetInput();

	CString code;
	code.Format("%s", m_ORIGINAL_ARTCODE);
	code.Trim();

	if ( code.IsEmpty() ){
		m_ARTIKEL_NR_ORIG.SetWindowText("");
		m_ARTIKEL_NR_ORIG.p_GetInput();
		return TRUE;
	}

	if ( 0 > CArticleCodesConverter::setArticleNoEditCtrl(code, m_ARTIKEL_NR_ORIG, cErrmld )){
		m_ARTIKEL_NR_ORIG.SetWindowText("");
		m_ARTIKEL_NR_ORIG.p_GetInput();
		ShowOriginalArtikel(TRUE);
		MsgBoxOK( cErrmld );
		//m_ERSATZ_CODE.SetFocus(); -> focus zwar auf feld, aber cursor wird unsichtbar - warum?
		return FALSE;
	}

	m_ARTIKEL_NR_ORIG.p_GetInput();

	return TRUE;
}

void CArtikelPage2::FillComboBox()
{
	m_ZENTRALPPELIST.ResetContent();
	m_NAHR_TEST.ResetContent();
	m_NAHR_ERG.ResetContent();
	m_ELEKTROSCHROTT.ResetContent();
	m_PREISSENK.ResetContent();
	m_RUNDUNG_STD_MGE.ResetContent();
	m_BESTELL_NICHT_AUSL.ResetContent();
	m_BATTERIEGESETZ.ResetContent();

	m_ZENTRALPPELIST.AddString(CResString::ex().getStrTblText(IDS_STRING10033));
	m_ZENTRALPPELIST.AddString(CResString::ex().getStrTblText(IDS_STRING10034));
	m_ZENTRALPPELIST.AddString(CResString::ex().getStrTblText(IDS_STRING10086));
	
	m_PREISSENK.AddString(CResString::ex().getStrTblText(IDS_STRING10087));
	m_PREISSENK.AddString(CResString::ex().getStrTblText(IDS_STRING10088));
	m_PREISSENK.AddString(CResString::ex().getStrTblText(IDS_STRING10089));
	m_PREISSENK.AddString(CResString::ex().getStrTblText(IDS_STRING10090));
	m_PREISSENK.AddString(CResString::ex().getStrTblText(IDS_STRING10091));
	m_PREISSENK.AddString(CResString::ex().getStrTblText(IDS_STRING10092));
	m_PREISSENK.AddString(CResString::ex().getStrTblText(IDS_STRING934));

	m_BESTELL_NICHT_AUSL.AddString(CResString::ex().getStrTblText(IDS_STRING1330));
	m_BESTELL_NICHT_AUSL.AddString(CResString::ex().getStrTblText(IDS_STRING1331));
	m_BESTELL_NICHT_AUSL.AddString(CResString::ex().getStrTblText(IDS_STRING1332));

	m_NAHR_TEST.AddString(CResString::ex().getStrTblText(IDS_STRING10093));
	m_NAHR_TEST.AddString(CResString::ex().getStrTblText(IDS_STRING10094));
	m_NAHR_TEST.AddString(CResString::ex().getStrTblText(IDS_STRING10095));
	m_NAHR_TEST.AddString(CResString::ex().getStrTblText(IDS_STRING10096));
	m_NAHR_TEST.AddString(CResString::ex().getStrTblText(IDS_STRING10097));
	m_NAHR_TEST.AddString(CResString::ex().getStrTblText(IDS_STRING10098));
	m_NAHR_TEST.AddString(CResString::ex().getStrTblText(IDS_STRING10099));
	m_NAHR_TEST.AddString(CResString::ex().getStrTblText(IDS_STRING10100));

	m_NAHR_ERG.AddString(CResString::ex().getStrTblText(IDS_STRING10101));
	m_NAHR_ERG.AddString(CResString::ex().getStrTblText(IDS_STRING10013));
	m_NAHR_ERG.AddString(CResString::ex().getStrTblText(IDS_STRING10014));
	m_NAHR_ERG.AddString(CResString::ex().getStrTblText(IDS_STRING10015));
	m_NAHR_ERG.AddString(CResString::ex().getStrTblText(IDS_STRING10016));

	m_ELEKTROSCHROTT.AddString(CResString::ex().getStrTblText(IDS_STRING10083));
	m_ELEKTROSCHROTT.AddString(CResString::ex().getStrTblText(IDS_STRING10084));
	m_ELEKTROSCHROTT.AddString(CResString::ex().getStrTblText(IDS_STRING10085));
	m_ELEKTROSCHROTT.AddString(CResString::ex().getStrTblText(IDS_STRING285));

	m_BATTERIEGESETZ.AddString(CResString::ex().getStrTblText(IDS_STRING61460));
	m_BATTERIEGESETZ.AddString(CResString::ex().getStrTblText(IDS_STRING61461));
	m_BATTERIEGESETZ.AddString(CResString::ex().getStrTblText(IDS_STRING61462));
	m_BATTERIEGESETZ.AddString(CResString::ex().getStrTblText(IDS_STRING61463));
	m_BATTERIEGESETZ.AddString(CResString::ex().getStrTblText(IDS_STRING61464));
	m_BATTERIEGESETZ.AddString(CResString::ex().getStrTblText(IDS_STRING61465));

	m_RUNDUNG_STD_MGE.AddString(CResString::ex().getStrTblText(IDS_STRING938));
	m_RUNDUNG_STD_MGE.AddString(CResString::ex().getStrTblText(IDS_STRING939));
	m_RUNDUNG_STD_MGE.AddString(CResString::ex().getStrTblText(IDS_STRING940));

	m_BEZUGSSPERRE.ResetContent();
	m_BEZUGSSPERRE.AddString(CResString::ex().getStrTblText(IDS_STRING1471));
	m_BEZUGSSPERRE.AddString(CResString::ex().getStrTblText(IDS_STRING1472));
	m_BEZUGSSPERRE.AddString(CResString::ex().getStrTblText(IDS_STRING1473));
}

long CArtikelPage2::CalculateVolume( )
{
	long iVolume;

// umgestellt wg. Feldüberlauf
//	iVolume = ((m_pBufZartikel->LAENGE * m_pBufZartikel->BREITE * m_pBufZartikel->HOEHE) + 500) / 1000; 
	double d1 = m_pBufZartikel->LAENGE / 10.0;
	double d2 = m_pBufZartikel->BREITE / 10.0;
	double d3 = m_pBufZartikel->HOEHE / 10.0;

	iVolume = (int)((d1 * d2 * d3) + 0.5); 

	if (iVolume > 99999)
	{
		iVolume = 99999;
	}

	return iVolume;
}

void CArtikelPage2::SetVolume( long iVolume )
{
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )m_pView)->GetBuffer();
	m_Buf->iVolumen = iVolume;
}

void CArtikelPage2::CheckMeasureWeightChange( )
{
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )m_pView)->GetBuffer();
	struct PFL_ARTIKEL *m_OldBuf = ((CArtikelView* )m_pView)->GetOldBuffer();

	if (m_Buf->zartikel.LAENGE  != m_OldBuf->zartikel.LAENGE || 
		m_Buf->zartikel.BREITE  != m_OldBuf->zartikel.BREITE || 
		m_Buf->zartikel.HOEHE   != m_OldBuf->zartikel.HOEHE || 
		m_Buf->zartikel.GEWICHT != m_OldBuf->zartikel.GEWICHT)
	{
		m_Buf->zartikel.DATUM_MWE = 0;
		m_DATUM_MWE.p_SetInput( );
	}
}

void CArtikelPage2::OnSelchangeCbArtikelPreissenk()
{
	m_PREISSENK.p_GetInput();

	if (m_pBufZartikel->PREISSENKUNG[0] == '0' ||
	    m_pBufZartikel->PREISSENKUNG[0] == '3')
		m_pBufZartikel->DATUM_PREISSENKUNG = 0;
	else
		m_pBufZartikel->DATUM_PREISSENKUNG = ::Today();

	m_DATUM_PREISSENKUNG.p_SetInput();
}

void CArtikelPage2::Set_Chargenartikel( )
{
	m_dlg.DataExchangeFromBuffer( m_Pos_CHARGENARTIKEL );
}

void CArtikelPage2::Translation() 
{
	if (IsCountry("CH"))
	{
//		m_ZENTRALPPELIST.SetMask  ( "01289", m_pBufZartikel->ZENTRALPPELIST ); 		<-- passiert schon im InitPflege
		m_ZENTRALPPELIST.ResetContent();
		m_ZENTRALPPELIST.AddString(CResString::ex().getStrTblText(IDS_STRING10033));
		m_ZENTRALPPELIST.AddString(CResString::ex().getStrTblText(IDS_STRING1105));
		m_ZENTRALPPELIST.AddString(CResString::ex().getStrTblText(IDS_STRING1106));
		m_ZENTRALPPELIST.AddString(CResString::ex().getStrTblText(IDS_STRING10086));
		m_ZENTRALPPELIST.AddString(CResString::ex().getStrTblText(IDS_STRING10037));
	}
	else if (!IsCountry("D"))
	{
//		m_ZENTRALPPELIST.SetMask  ( "0", m_pBufZartikel->ZENTRALPPELIST ); 		<-- passiert schon im InitPflege
		m_ZENTRALPPELIST.ResetContent();
		m_ZENTRALPPELIST.AddString(CResString::ex().getStrTblText(IDS_STRING10033));
	}
}

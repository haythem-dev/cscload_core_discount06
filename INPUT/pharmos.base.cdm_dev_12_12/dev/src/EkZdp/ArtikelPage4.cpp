// ArtikelPage4.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtikelPage4.h"
#include "ArtikelView.h"
#include "CopyArtSdbDlg.h"

#include <phxlib/CaccdangerrouteSelCtrl.h>
#include <phxlib/storageclassselctrl.h>
#include <phxlib/hazardnoteselctrl.h>

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskInt.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskUmlaut.h>
#include <eklibs/hamfcs/hMskDblPos.h>
#include <eklibs/hamfcs/hMskDate.h>

#include "ServerDatum.h"

#include <libscsvoodoo/libscsvoodoo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtikelPage4 property page

IMPLEMENT_DYNCREATE(CArtikelPage4, CPropertyPageMultiLang)

CArtikelPage4::CArtikelPage4() : ChPflegePage(CArtikelPage4::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInitialized = FALSE;
}

CArtikelPage4::~CArtikelPage4()
{
}

void CArtikelPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage4)
	DDX_Control(pDX, IDC_LC_ARTIKEL_GHS_HAZARDNOTES,	m_cHAZARDNOTEBOX);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ZYTOSTATIKA,		m_ZYTOSTATIKA);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SIDABLATT,			m_SIDABLATT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_BIOZID_VERORD,		m_BIOZID_VERORD);
	DDX_Control(pDX, IDC_CK_ARTIKEL_EXPLOSION,			m_EXPLOSION);
	DDX_Control(pDX, IDC_CO_ARTIKEL_PFLSCHUTZ_VERORD,	m_PFLSCHUTZ_VERORD);
	DDX_Control(pDX, IDC_ED_ARTIKEL_BIOZID_REGNR1,		m_BIOZID_REGNR1);
	DDX_Control(pDX, IDC_ED_ARTIKEL_BIOZID_REGNR2,		m_BIOZID_REGNR2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PFL_ZULNR,			m_PFL_ZULNR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_PFL_ZUL_ENDE, m_DATUM_PFL_ZUL_ENDE );
	DDX_Control(pDX, IDC_ED_ARTIKEL_GG_KLASSE,			m_GG_KLASSE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GG_BUCHSTABE,		m_GG_BUCHSTABE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GG_ZIFFER,			m_GG_ZIFFER);
	DDX_Control(pDX, IDC_ED_ARTIKEL_G_WASSER,			m_G_WASSER);
	DDX_Control(pDX, IDC_ED_ARTIKEL_G_VCI,				m_G_VCI);
	DDX_Control(pDX, IDC_ED_ARTIKEL_G_VBF,				m_G_VBF);
	DDX_Control(pDX, IDC_ED_ARTIKEL_G_UN_NR,			m_G_UN_NR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_G_VGRP,				m_G_VGRP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_G_TECH_NAME,		m_G_TECH_NAME);
	DDX_Control(pDX, IDC_ED_ARTIKEL_G_DICHTE,			m_G_DICHTE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_SDS_LINK,		m_SDS_LINK);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_EXPLOSION,		m_GS_EXPLOSION);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_HOCHENTZ,		m_GS_HOCHENTZ);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_VORSLAGERN,		m_GS_VORSLAGERN);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_LICHTGESCH,		m_GS_LICHTGESCH);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_UMWELT,			m_GS_UMWELT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_SVORSLAGERN,		m_GS_SVORSLAGERN);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_REIZEND,			m_GS_REIZEND);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_AETZEND,			m_GS_AETZEND);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_SEHRGIFTIG,		m_GS_SEHRGIFTIG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_LEICHTENTZ,		m_GS_LEICHTENTZ);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_GIFTIG,			m_GS_GIFTIG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_GESUNDHSCH,		m_GS_GESUNDHSCH);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GS_BRAND,			m_GS_BRAND);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GHS_PICT_01,		m_GHS_PICT_01);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GHS_PICT_02,		m_GHS_PICT_02);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GHS_PICT_03,		m_GHS_PICT_03);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GHS_PICT_04,		m_GHS_PICT_04);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GHS_PICT_05,		m_GHS_PICT_05);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GHS_PICT_06,		m_GHS_PICT_06);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GHS_PICT_07,		m_GHS_PICT_07);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GHS_PICT_08,		m_GHS_PICT_08);
	DDX_Control(pDX, IDC_CK_ARTIKEL_GHS_PICT_09,		m_GHS_PICT_09);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_SICH_HINW,		m_GHS_SICH_HINW);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_GEFAHR_HINW,	m_GHS_GEFAHR_HINW);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_EU_GEFAHR_HINW, m_GHS_EU_GEFAHR_HINW);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_AEDAT,			m_GHS_AEDAT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_VERSION,		m_GHS_VERSION);
	DDX_Control(pDX, IDC_CB_ARTIKEL_GHS_SIGNAL,			m_GHS_SIGNAL);
	DDX_Control(pDX, IDC_CB_ARTIKEL_STOREROOM,			m_STOREROOM);
	DDX_Control(pDX, IDC_CB_ARTIKEL_LAGEEMPF,			m_LAGEEMPF);

	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_PRUEFDAT,		m_GHS_PRUEFDAT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_CALC_STORCLASS,	m_CALC_STORAGECLASS);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_SDSSTATUS,		m_SDSSTATUS);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NO_SDS_ACC_PROV,	m_NO_SDS_ACC_PROV);
	DDX_Control(pDX, IDC_CK_ARTIKEL_MARK_NOT_OBLIGATORY,m_MARK_NOT_OBLIGATORY);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_FLASHPOINT,		m_FLASHPOINT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GHS_HAZARDNOTE,		m_HAZARDNOTE);
	DDX_Control(pDX, IDC_PB_ARTIKEL_GHS_PRUEF,			m_BT_SetPruefDat);	
	DDX_Control(pDX, IDC_PB_ARTIKEL_GHS_HAZARDNOTE_ADD,	m_BT_AddHazardNote);	
	DDX_Control(pDX, IDC_PB_ARTIKEL_GHS_HAZARDNOTE_DELETE,	m_BT_DelHazardNote);		
	DDX_Control(pDX, IDC_PB_ARTIKEL_SDB_COPY,			m_BT_CopySafetyDataSheet);	
	DDX_Control(pDX, IDC_CK_ARTIKEL_IS_CMR,				m_BT_CMR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_TEMP_BEACHT,		m_BT_LAGERTEMP);

	DDX_Control(pDX, IDC_TEXT_GS,                       m_TEXT_GS);

	DDX_Control(pDX, IDC_CB_ARTIKEL_ICPE_CODE, m_ICPE_CODE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_CERTIFICATE_EXP_DATE,		m_CERTIFICATE_EXP_DATE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DECLA_CONFORMITY_EXP_DATE,	m_DECL_CONFORMITY_DATE);

	//}}AFX_DATA_MAP

	if (IsCountry("CH"))
	{
		m_GS_EXPLOSION.ShowWindow(false);
		m_GS_REIZEND.ShowWindow(false);
		m_GS_AETZEND.ShowWindow(false);
		m_GS_SEHRGIFTIG.ShowWindow(false);
		m_GS_LEICHTENTZ.ShowWindow(false);
		m_GS_GIFTIG.ShowWindow(false);
		m_GS_HOCHENTZ.ShowWindow(false);
		m_GS_GESUNDHSCH.ShowWindow(false);
		m_GS_BRAND.ShowWindow(false);
		m_GS_UMWELT.ShowWindow(false);

		m_TEXT_GS.ShowWindow(false);
	}
	if (IsCountry("F") == FALSE)
	{
		GetDlgItem(IDC_ST_ARTIKEL_ICPE_CODE)->ShowWindow(false);
		m_ICPE_CODE.ShowWindow(false);
		GetDlgItem(IDC_ST_ARTIKEL_CERTIFICATE_EXP_DATE)->ShowWindow(false);
		m_CERTIFICATE_EXP_DATE.ShowWindow(false);
		GetDlgItem(IDC_ST_ARTIKEL_DECLA_CONFORMITY_EXP_DATE)->ShowWindow(false);
		m_DECL_CONFORMITY_DATE.ShowWindow(false);
	}
}


BEGIN_MESSAGE_MAP(CArtikelPage4, CPropertyPageMultiLang)
	//{{AFX_MSG_MAP(CArtikelPage4)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_GHS_PRUEF, OnPbSetPruefDat)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_GHS_HAZARDNOTE_ADD, OnPbAddHazardNote)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_GHS_HAZARDNOTE_DELETE, OnPbDelHazardNote)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_SDB_COPY, OnPbCopySafetyDataSheet)	
	ON_BN_CLICKED(IDC_CK_ARTIKEL_IS_CMR, OnPbIsCMR)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_CB_ARTIKEL_ICPE_CODE, &CArtikelPage4::OnSelChangeICPE_Code)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage4::OnPbSetPruefDat()
{
	m_pBufSafteyDataSheet->DATE_CHECKED = ::Today();
	m_GHS_PRUEFDAT.p_SetInput();
}

void CArtikelPage4::OnPbDelHazardNote()
{
	int pos = m_cHAZARDNOTEBOX.GetNextItem(-1, LVNI_SELECTED);

	if (pos < 0)
		return;

	CString str;
	char m_HAZARDNOTE_TO_DEL[L_CHAZARDNOTE_HAZARDNOTEID + 1];
	str = m_cHAZARDNOTEBOX.GetItemText(pos, 0);
	strcpy(m_HAZARDNOTE_TO_DEL, str.Trim());	
	
	((CArtikelView* )m_pView)->m_Doc.SetHazardNoteIdToProcess(m_HAZARDNOTE_TO_DEL);
	((CArtikelView* )m_pView)->m_Doc.DeleteRecord_chazardnote2article(str);

	// Lagerklassenermittlung aufrufen
	CalculateStorageClass();

	// direkt in DB gelöscht --> nachladen Box
	((CArtikelView* )m_pView)->m_Doc.ReadRecord_chazardnote2article(str);
	CopyHazardNotesToGuiList();

	((CArtikelView* )m_pView)->GetBuffer()->csafetydatasheet.DATE_CHANGED = Today();
	m_GHS_AEDAT.p_SetInput();
}

void CArtikelPage4::OnPbAddHazardNote()
{
	CString str;
	m_HAZARDNOTE.p_GetInput();
	str = m_HAZARDNOTE_TO_ADD;

	if (str.Trim().IsEmpty())
		return;

	((CArtikelView* )m_pView)->m_Doc.SetHazardNoteIdToProcess(m_HAZARDNOTE_TO_ADD);
	((CArtikelView* )m_pView)->m_Doc.StoreRecord_chazardnote2article(str);

	// Lagerklassenermittlung aufrufen
	CalculateStorageClass();

	// direkt in DB geschrieben --> nachladen Box
	((CArtikelView* )m_pView)->m_Doc.ReadRecord_chazardnote2article(str);
	CopyHazardNotesToGuiList();
	strcpy(m_HAZARDNOTE_TO_ADD, "");
	m_HAZARDNOTE.p_SetInput();

	((CArtikelView* )m_pView)->GetBuffer()->csafetydatasheet.DATE_CHANGED = Today();
	m_GHS_AEDAT.p_SetInput();
}

void CArtikelPage4::OnPbCopySafetyDataSheet()
{
	// todo RR : add copy logic here ...
	CCopyArtSdbDlg dlg (&((CArtikelView*)m_pView)->m_Doc);
	dlg.DoModal();

}

void CArtikelPage4::MakeDialog()
{
	// RR 20.07.15: hierher verschoben, damit im ActivateField() der Cursor auch wieder auf diesem Feld platziert wird
	m_dlg.InitDialog( m_GHS_VERSION );

	m_dlg.InitDialog( m_G_TECH_NAME );
	m_dlg.InitDialog( m_GG_KLASSE );
	m_dlg.InitDialog( m_GG_BUCHSTABE );
	m_dlg.InitDialog( m_GG_ZIFFER );

	m_dlg.InitDialog( m_G_WASSER );
	m_dlg.InitDialog( m_G_VCI );
	m_dlg.InitDialog( m_G_VBF );
	m_dlg.InitDialog( m_G_UN_NR );
	m_dlg.InitDialog( m_G_VGRP );

	m_dlg.InitDialog( m_G_DICHTE );
	m_dlg.InitDialog( m_GS_EXPLOSION );
	m_dlg.InitDialog( m_GS_HOCHENTZ );
	m_dlg.InitDialog( m_GS_VORSLAGERN );
	m_dlg.InitDialog( m_GS_LICHTGESCH );
	m_dlg.InitDialog( m_GS_UMWELT );
	m_dlg.InitDialog( m_GS_SVORSLAGERN );
	m_dlg.InitDialog( m_GS_REIZEND );
	m_dlg.InitDialog( m_GS_AETZEND );
	m_dlg.InitDialog( m_GS_SEHRGIFTIG );
	m_dlg.InitDialog( m_GS_LEICHTENTZ );
	m_dlg.InitDialog( m_GS_GIFTIG );
	m_dlg.InitDialog( m_GS_GESUNDHSCH );
	m_dlg.InitDialog( m_GS_BRAND );

	m_dlg.InitDialog( m_GHS_PICT_01 );
	m_dlg.InitDialog( m_GHS_PICT_02 );
	m_dlg.InitDialog( m_GHS_PICT_03 );
	m_dlg.InitDialog( m_GHS_PICT_04 );
	m_dlg.InitDialog( m_GHS_PICT_05 );
	m_dlg.InitDialog( m_GHS_PICT_06 );
	m_dlg.InitDialog( m_GHS_PICT_07 );
	m_dlg.InitDialog( m_GHS_PICT_08 );
	m_dlg.InitDialog( m_GHS_PICT_09 );
	m_dlg.InitDialog( m_GHS_SICH_HINW );
	m_dlg.InitDialog( m_GHS_GEFAHR_HINW );
	m_dlg.InitDialog( m_GHS_EU_GEFAHR_HINW );
	m_dlg.InitDialog( m_GHS_AEDAT );
	m_dlg.InitDialog( m_GHS_PRUEFDAT );
	m_dlg.InitDialog( m_CALC_STORAGECLASS );
	m_dlg.InitDialog( m_SDSSTATUS);
	m_dlg.InitDialog( m_NO_SDS_ACC_PROV);
	m_dlg.InitDialog( m_MARK_NOT_OBLIGATORY);
	m_dlg.InitDialog( m_FLASHPOINT);
	m_dlg.InitDialog( m_HAZARDNOTE);
	m_dlg.InitDialog( m_GHS_SIGNAL );
	m_dlg.InitDialog( m_STOREROOM );
	m_dlg.InitDialog( m_LAGEEMPF );
	m_dlg.InitDialog( m_SDS_LINK );

	m_dlg.InitDialog( m_ZYTOSTATIKA );
	m_dlg.InitDialog( m_SIDABLATT );
	m_dlg.InitDialog( m_BIOZID_VERORD );
	m_dlg.InitDialog( m_EXPLOSION );
	m_dlg.InitDialog( m_PFLSCHUTZ_VERORD );

	m_dlg.InitDialog( m_BIOZID_REGNR1 );
	m_dlg.InitDialog( m_BIOZID_REGNR2 );
	m_dlg.InitDialog( m_PFL_ZULNR );
	m_dlg.InitDialog( m_DATUM_PFL_ZUL_ENDE );

	m_dlg.InitDialog( m_BT_SetPruefDat );
	m_dlg.InitDialog( m_BT_AddHazardNote );
	m_dlg.InitDialog( m_BT_DelHazardNote );
	m_dlg.InitDialog( m_BT_CopySafetyDataSheet );
	m_dlg.InitDialog( m_BT_CMR );
	m_dlg.InitDialog( m_BT_LAGERTEMP );
	m_dlg.InitDialog( m_ICPE_CODE );
	m_dlg.InitDialog( m_CERTIFICATE_EXP_DATE );
	m_dlg.InitDialog( m_DECL_CONFORMITY_DATE );

	m_nMaxFields = m_dlg.GetFieldNumber();
}

/////////////////////////////////////////////
// Verknuepfungen Ruecksetzen

void CArtikelPage4::ResetVkn( )
{
	m_RD_ADR_INFO.Reset();
}

BOOL CArtikelPage4::ShowADRInfo( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString ADR2009;
	CString ADR2011;
	CString Info;
	CString Errmld;

	iStat = m_RD_ADR_INFO.IPlausi( m_pBufZartikel->G_UN_NR, m_pBufZartikel->VERPACKUNGSGRUPPE, ADR2009, ADR2011, &Errmld);

	if (iStat == 0)
		Info.Format("%s   (ADR2009)\n%s   (ADR2015)", ADR2009, ADR2011);

	if ( bShow )
		GetDlgItem( IDC_ST_ARTIKEL_ADR_INFO2 )->SetWindowText( Info );

	// außerhalb Deutschland kein Fehler, wenn Stammtabelle nicht vorhanden
	if (iStat > 1 && !IsCountry("D"))
		return TRUE;

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );
	
	return iStat <= 1;
}

void CArtikelPage4::SucheADRInfo( )
{
	CCaccdangerrouteSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1349), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufZartikel->G_UN_NR, m_pBufZartikel->VERPACKUNGSGRUPPE ) == 0 )
		{
			m_G_UN_NR.p_SetInput();
			m_G_VGRP.p_SetInput();
			m_G_VGRP.SetFocus();
			ShowADRInfo( TRUE );
		}
	}

	m_SelBox.CloseCursor();
}

/////////////////////////////////////////////////////////////
//  Validierung

class CV_ARTIKEL_ADR_Info : public ChValBase
{
public:
	CV_ARTIKEL_ADR_Info( CArtikelPage4* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;

		// auch hier Lagerklassenermittlung aufrufen
		((CArtikelPage4*)m_pWnd)->CalculateStorageClass();

		bOk = ((CArtikelPage4*)m_pWnd)->ShowADRInfo( bMeldung, bMeldung );

		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage4*)m_pWnd)->SucheADRInfo( );
	}
};

// eigene Klasse für Aufruf aus dem Feld UNNR, weil es sowohl beim Löschen als auch bei der Eingabe vorkommen kann, dass die 
// Kombination nicht existiert, weil noch die dazugehörige VPG eingegeben / gelöscht werden muss, somit hier keine Plausi-Prüfung
class CV_ARTIKEL_ADR_Info_UNNR : public ChValBase
{
public:
	CV_ARTIKEL_ADR_Info_UNNR( CArtikelPage4* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		// auch hier Lagerklassenermittlung aufrufen
		((CArtikelPage4*)m_pWnd)->CalculateStorageClass();

		// Show-Funktion trotzdem aufrufen, damit Anwender sofort sieht, dass Kombination ungültig
		((CArtikelPage4*)m_pWnd)->ShowADRInfo( bMeldung, FALSE );

		// check in caccdangerroute, ob es die Un-Nr überhaupt gibt - wenn nein, dann return false !!!
		return ((CArtikelPage4*)m_pWnd)->CheckUnNr(bMeldung);
	}
	void NotifyProc( )
	{
		((CArtikelPage4*)m_pWnd)->SucheADRInfo( );
	}
};

// eigene Klasse für GG-Klasse, weil auch hier bei einer Änderung die Phoenix-Lagerklasse neu berechnet werden soll
class CV_GG_Klasse : public ChValBase
{
public:
	CV_GG_Klasse( CArtikelPage4* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL )
	{
		((CArtikelPage4*)m_pWnd)->CalculateStorageClass();
		return TRUE;
	}
};

class CV_StorageClass : public ChValBase
{
public:
	CV_StorageClass(CArtikelPage4* pView) : ChValBase(pView){};

	BOOL Validate(BOOL bMeldung)
	{
		// auch hier Lagerklassenermittlung aufrufen
		((CArtikelPage4*)m_pWnd)->CalculateStorageClass();

		return ((CArtikelPage4*)m_pWnd)->ShowStorageClass(bMeldung, bMeldung);
	}

	void NotifyProc()
	{
		((CArtikelPage4*)m_pWnd)->SucheStorageClass();
	}
};

BOOL CArtikelPage4::ShowStorageClass(BOOL bShow, BOOL bMeldung)
{
	int		stat;
	CString name;
	short	sStoreRoom = 0;
	CString errmld;
	
	stat = m_RD_STORAGECLASS.IPlausi(m_pBufZartikel->G_VCI, name, sStoreRoom, &errmld);
	
	if(bShow)
		GetDlgItem(IDC_ST_GHS_LGK)->SetWindowText(name);

	// Font aendern (kleiner, um etwas Platz auf dem Dialog zu schaffen)
	// nur, wenn die Seite auch schon aktiv war, sonst schmiert das Programm ab
	if (((CArtikelView* )m_pView)->WasPageActive(3) == TRUE)
	{
		CEkZdpApp* pApp = (CEkZdpApp*) AfxGetApp();
		m_pSmallFont = pApp->GetSmallFont();
		GetDlgItem( IDC_ST_GHS_LGK )->SetFont( m_pSmallFont );

		// außerdem Gefahrstoffraum setzen, bei Löschung aus berechneter Lagerklasse
		if (stat == 0)
			SetStoreRoom(sStoreRoom);
		else if (stat == 1)
			ShowCalcStorageClass (TRUE);
	}

	if (stat > 1 && bMeldung) 
	{
		MsgBoxOK(errmld);
	}

	return stat <= 1;
}

void CArtikelPage4::SucheStorageClass()
{
	CStorageClassSelCtrl m_SelBoxType;

	ChSelectDialog dlg(CResString::ex().getStrTblText(IDS_STRING81),
					   &m_SelBoxType,
					   HCD_SCROLLINFO);

	if (dlg.DoModal() == IDOK)
	{
		if (m_SelBoxType.PrimeKeyOfSelectedRecord(m_pBufZartikel->G_VCI) == 0)
		{
			m_G_VCI.p_SetInput();
			m_G_VCI.SetFocus();

			ShowStorageClass(TRUE, TRUE);
		}
	}

	m_SelBoxType.CloseCursor();
}

BOOL CArtikelPage4::ShowCalcStorageClass(BOOL bShow, BOOL bMeldung)
{
	int		stat;
	CString name;
	short	sStoreRoom = 0;
	CString errmld;

	CRdCStorageClass		m_RD_CALCSTORAGECLASS;
	
	stat = m_RD_CALCSTORAGECLASS.IPlausi(m_pBufSafteyDataSheet->CALCSTORAGECLASSID, name, sStoreRoom, &errmld);
	
	if(bShow)
		GetDlgItem(IDC_ST_GHS_CALC_STORCLASS)->SetWindowText(name);

	// Font aendern (kleiner, um etwas Platz auf dem Dialog zu schaffen)
	// nur, wenn die Seite auch schon aktiv war, sonst schmiert das Programm ab
	if (((CArtikelView* )m_pView)->WasPageActive(3) == TRUE)
	{
		CEkZdpApp* pApp = (CEkZdpApp*) AfxGetApp();
		m_pSmallFont = pApp->GetSmallFont();
		GetDlgItem( IDC_ST_GHS_CALC_STORCLASS )->SetFont( m_pSmallFont );

		// wenn keine SDB-Lagerklasse eingetragen ist, dann Gefahrstoffraum aus der berechneten versorgen
		if ( strncmp(((CArtikelView* )m_pView)->GetBuffer()->zartikel.G_VCI, "    ", L_ZARTIKEL_G_VCI) == 0 &&
			stat <= 1 )
			SetStoreRoom(sStoreRoom);
	}

	if (0 != stat && bMeldung) 
	{
		MsgBoxOK(errmld);
	}

	return stat == 0;
}

class CV_HazardNote : public ChValBase
{
public:
	CV_HazardNote(CArtikelPage4* pView) : ChValBase(pView){};

	BOOL Validate(BOOL bMeldung)
	{
		return ((CArtikelPage4*)m_pWnd)->ShowHazardNote(bMeldung, bMeldung);
	}

	void NotifyProc()
	{
		((CArtikelPage4*)m_pWnd)->SucheHazardNote();
	}
};

BOOL CArtikelPage4::ShowHazardNote(BOOL bShow, BOOL bMeldung)
{
	int		stat;
	CString name;
	CString errmld;

	stat = m_RD_HAZARDNOTE.IPlausi(m_HAZARDNOTE_TO_ADD, name, &errmld);
	
	if(bShow)
	{
	//	GetDlgItem(IDC_ST_GHS_LGK)->SetWindowText(name);
	}

	if (stat > 1 && bMeldung) 
	{
		MsgBoxOK(errmld);
	}

	return stat <= 1;
}

void CArtikelPage4::SucheHazardNote()
{
	CHazardNoteSelCtrl m_SelBoxType;

	ChSelectDialog dlg(CResString::ex().getStrTblText(IDS_STRING86),
					   &m_SelBoxType,
					   HCD_SCROLLINFO);

	if (dlg.DoModal() == IDOK)
	{
		if (m_SelBoxType.PrimeKeyOfSelectedRecord(m_HAZARDNOTE_TO_ADD) == 0)
		{
			m_HAZARDNOTE.p_SetInput();
			m_HAZARDNOTE.SetFocus();

			// ShowHazardNote(TRUE, TRUE);
		}
	}

	m_SelBoxType.CloseCursor();
}

/////////////////////////////////////////////////////////////
//  EndValidierung 

BOOL CArtikelPage4::EndValidate( int *, BOOL )
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CArtikelPage4 message handlers

/////////////////////////////////////////////////////////////
//  Dialogfelder

void CArtikelPage4::InitPflege( CWnd *pView  )
{
	CArtikelPage4* pThisView = this;
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )pView)->GetBuffer();
	m_pBufZartikel = &m_Buf->zartikel;
	m_pBufBiozid_Regnr1 = &m_Buf->carticlecodes[3];	// code_type = 4
	m_pBufBiozid_Regnr2 = &m_Buf->carticlecodes[4];	// code_type = 5
	m_pBufPfl_Zulnr = &m_Buf->carticlecodes[2];	// code_type = 3
	m_pBufSafteyDataSheet = &m_Buf->csafetydatasheet;

	MakeDialog();

	m_GG_KLASSE.SetMask		(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufZartikel->GG_KLASSE,
				             L_ZARTIKEL_GG_KLASSE,
						     new ChMaskChar,
							 new CV_GG_Klasse(this));

	m_GG_BUCHSTABE.SetMask	(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufZartikel->GG_BUCHSTABE,
				             L_ZARTIKEL_GG_BUCHSTABE,
							 new ChMaskChar );
	
	m_GG_ZIFFER.SetMask		(ED_CHAR,
		                     ED_NORMAL,
			                 m_pBufZartikel->GG_ZIFFER,
				             L_ZARTIKEL_GG_ZIFFER,
							 new ChMaskNum );

	m_G_WASSER.SetMask		(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufZartikel->G_WASSER,
				             L_ZARTIKEL_G_WASSER,
						     new ChMaskNum );

	m_G_VCI.SetMask			(ED_CHAR,
		                     ED_NORMAL,				// Gross+Klein
			                 m_pBufZartikel->G_VCI,
				             L_ZARTIKEL_G_VCI,
						     new ChMaskChar,
							 new CV_StorageClass(this));

	m_G_VBF.SetMask			(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufZartikel->G_VBF,
				             L_ZARTIKEL_G_VBF,
						     new ChMaskChar );

	m_G_UN_NR.SetMask		(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufZartikel->G_UN_NR,
				             L_ZARTIKEL_G_UN_NR,
						     new ChMaskNum, 
							 new CV_ARTIKEL_ADR_Info_UNNR( pThisView ) );

	m_G_VGRP.SetMask		(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufZartikel->VERPACKUNGSGRUPPE,
				             L_ZARTIKEL_VERPACKUNGSGRUPPE,
						     new ChMaskChar,
							 new CV_ARTIKEL_ADR_Info( pThisView ) );

	m_G_TECH_NAME.SetMask	(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufZartikel->G_TECH_NAME,
				             L_ZARTIKEL_G_TECH_NAME,
						     new ChMaskChar );

	m_G_DICHTE.SetMask		(ED_DBL,
		                     ED_UPPER,
			                 &m_pBufZartikel->G_DICHTE,
				             L_ZARTIKEL_G_DICHTE + 1,
							 N_ZARTIKEL_G_DICHTE,
						     new ChMaskDblPos );

	m_GS_EXPLOSION.SetMask	( '1', '0', m_pBufZartikel->GS_EXPLOSION);
	m_GS_HOCHENTZ.SetMask	( '1', '0', m_pBufZartikel->GS_HOCHENTZ);
	m_GS_VORSLAGERN.SetMask	( '1', '0', m_pBufZartikel->GS_VORSLAGERN);
	m_GS_LICHTGESCH.SetMask	( '1', '0', m_pBufZartikel->GS_LICHTGESCH);
	m_GS_UMWELT.SetMask		( '1', '0', m_pBufZartikel->GS_UMWELT);
	m_GS_SVORSLAGERN.SetMask( '1', '0', m_pBufZartikel->GS_SVORSLAGERN);
	m_GS_REIZEND.SetMask	( '1', '0', m_pBufZartikel->GS_REIZEND);
	m_GS_AETZEND.SetMask	( '1', '0', m_pBufZartikel->GS_AETZEND);
	m_GS_SEHRGIFTIG.SetMask	( '1', '0', m_pBufZartikel->GS_SEHRGIFTIG);
	m_GS_LEICHTENTZ.SetMask	( '1', '0', m_pBufZartikel->GS_LEICHTENTZ);
	m_GS_GIFTIG.SetMask		( '1', '0', m_pBufZartikel->GS_GIFTIG);
	m_GS_GESUNDHSCH.SetMask	( '1', '0', m_pBufZartikel->GS_GESUNDHSCH);
	m_GS_BRAND.SetMask		( '1', '0', m_pBufZartikel->GS_BRAND);

	m_GHS_AEDAT.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufSafteyDataSheet->DATE_CHANGED,
                             L_LDATUM,
                             new ChMaskLDate );

	m_GHS_PRUEFDAT.SetMask	(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufSafteyDataSheet->DATE_CHECKED,
                             L_LDATUM,
                             new ChMaskLDate );

	m_SDSSTATUS.SetMask		(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufSafteyDataSheet->SDSSTATUS,
				             L_CSAFETYDATASHEET_SDSSTATUS,
						     new ChMaskChar );

	m_SDS_LINK.SetMask		(ED_CHAR,
		                     ED_NORMAL,
			                 m_pBufSafteyDataSheet->SDS_LINK,
				             L_CSAFETYDATASHEET_SDS_LINK,
						     new ChMaskUmlaut );

	m_CALC_STORAGECLASS.SetMask(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufSafteyDataSheet->CALCSTORAGECLASSID,
				             L_CSAFETYDATASHEET_CALCSTORAGECLASSID,
						     new ChMaskChar);

	m_FLASHPOINT.SetMask	(ED_LONG, 
                             ED_NORMAL,
                             &m_pBufSafteyDataSheet->FLASHPOINT,
                             4,
							 new ChMaskInt); // auch "-" !!!

	m_GHS_VERSION.SetMask	(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufSafteyDataSheet->SDS_VERSION,
				             L_CSAFETYDATASHEET_SDS_VERSION,
						     new ChMaskChar );

	m_GHS_SICH_HINW.SetMask	(ED_CHAR,
		                     ED_NORMAL,
			                 m_pBufSafteyDataSheet->PRECAUTION_STATM,
				             L_CSAFETYDATASHEET_PRECAUTION_STATM,
						     new ChMaskChar );

	m_GHS_GEFAHR_HINW.SetMask	(ED_CHAR,
		                     ED_NORMAL,
			                 m_pBufSafteyDataSheet->HAZARD_STATM,
				             L_CSAFETYDATASHEET_HAZARD_STATM,
						     new ChMaskChar );

	m_GHS_EU_GEFAHR_HINW.SetMask	(ED_CHAR,
		                     ED_NORMAL,
			                 m_pBufSafteyDataSheet->EU_HAZARD_STATM,
				             L_CSAFETYDATASHEET_EU_HAZARD_STATM,
						     new ChMaskChar );

	m_GHS_PICT_01.SetMask	( 1, 0, &m_pBufSafteyDataSheet->PICTOGRAM01_FLAG);
	m_GHS_PICT_02.SetMask	( 1, 0, &m_pBufSafteyDataSheet->PICTOGRAM02_FLAG);
	m_GHS_PICT_03.SetMask	( 1, 0, &m_pBufSafteyDataSheet->PICTOGRAM03_FLAG);
	m_GHS_PICT_04.SetMask	( 1, 0, &m_pBufSafteyDataSheet->PICTOGRAM04_FLAG);
	m_GHS_PICT_05.SetMask	( 1, 0, &m_pBufSafteyDataSheet->PICTOGRAM05_FLAG);
	m_GHS_PICT_06.SetMask	( 1, 0, &m_pBufSafteyDataSheet->PICTOGRAM06_FLAG);
	m_GHS_PICT_07.SetMask	( 1, 0, &m_pBufSafteyDataSheet->PICTOGRAM07_FLAG);
	m_GHS_PICT_08.SetMask	( 1, 0, &m_pBufSafteyDataSheet->PICTOGRAM08_FLAG);
	m_GHS_PICT_09.SetMask	( 1, 0, &m_pBufSafteyDataSheet->PICTOGRAM09_FLAG);

	m_NO_SDS_ACC_PROV.SetMask		( 1, 0, &m_pBufSafteyDataSheet->NOSDSACCORDINGPROVIDERFLAG);
	m_MARK_NOT_OBLIGATORY.SetMask	( 1, 0, &m_pBufSafteyDataSheet->MARKINGNOTOBLIGATORYFLAG);

	if (IsCountry("CH"))
	{
		m_GHS_SIGNAL.SetMask	( "01234", &m_pBufSafteyDataSheet->SIGNALWORD );
	}
	else
	{
		m_GHS_SIGNAL.SetMask	( "012", &m_pBufSafteyDataSheet->SIGNALWORD );
	}

	m_STOREROOM.SetMask		( "0123", &m_pBufSafteyDataSheet->DANGERGOODSTOREROOM);
	m_LAGEEMPF.SetMask		( "012", &m_pBufZartikel->LAGEEMPF ); 

	m_ZYTOSTATIKA.SetMask	( '1', '0', m_pBufZartikel->ZYTOSTATIKA);
	m_BT_LAGERTEMP.SetMask	(  1 ,  0 , &m_pBufZartikel->LAGTEMP_BEACHTEN);
	m_SIDABLATT.SetMask		( '1', '0', m_pBufZartikel->SIDABLATT);
	m_BIOZID_VERORD.SetMask	( '1', '0', m_pBufZartikel->BIOZID_VERORD);

	m_EXPLOSION.SetMask		( 1, 0, &m_pBufZartikel->EXPLOSIVGRUNDSTOFF);

	m_PFLSCHUTZ_VERORD.SetMask  ( "NJRES", m_pBufZartikel->PFLSCHUTZ_VERORD ); 

	m_BIOZID_REGNR1.SetMask		(ED_CHAR,
								 ED_UPPER,
			                     m_pBufBiozid_Regnr1->ARTICLE_CODE,
				                 15,
                                 new ChMaskChar);

	m_BIOZID_REGNR2.SetMask		(ED_CHAR,
								 ED_UPPER,
			                     m_pBufBiozid_Regnr2->ARTICLE_CODE,
				                 15,
                                 new ChMaskChar);

	m_PFL_ZULNR.SetMask			(ED_CHAR,
								 ED_UPPER,
			                     m_pBufPfl_Zulnr->ARTICLE_CODE,
				                 15,
                                 new ChMaskChar);

	m_DATUM_PFL_ZUL_ENDE.SetMask (ED_LDATE,
								ED_NORMAL,
								&m_pBufZartikel->DATUM_PFL_ZUL_ENDE,
								L_LDATUM,
								new ChMaskLDate);

	m_HAZARDNOTE.SetMask	(ED_CHAR,
                             ED_NORMAL,
							 m_HAZARDNOTE_TO_ADD,
                             L_CHAZARDNOTE_HAZARDNOTEID,
                             new ChMaskChar,
							 new CV_HazardNote(this));

	m_CERTIFICATE_EXP_DATE.SetMask(ED_LDATE,
								   ED_NORMAL,
								   &m_pBufSafteyDataSheet->CERTIFICATE_EXPIRED_DATE,
								   L_LDATUM,
								   new ChMaskLDate);

	m_DECL_CONFORMITY_DATE.SetMask(ED_LDATE,
								   ED_NORMAL,
								   &m_pBufSafteyDataSheet->CONFORMITY_EXPIRED_DATE,
								   L_LDATUM,
								   new ChMaskLDate);

	m_bInitialized = TRUE;
}

/////////////////////////////////////////////////////////////
// ChPflegePage functions 

void CArtikelPage4::NextDlgCtrl()
{
	if ( GetFocus() == GetDlgItem( IDC_PB_ARTIKEL_GHS_HAZARDNOTE_ADD ))
	{
		OnPbAddHazardNote();
		m_HAZARDNOTE.SetFocus();
		return;
	}
	else if ( GetFocus() == GetDlgItem( IDC_PB_ARTIKEL_GHS_HAZARDNOTE_DELETE ) )
	{
		OnPbDelHazardNote();
		m_cHAZARDNOTEBOX.SetFocus();
		return;
	}
	else if ( GetFocus() == GetDlgItem( IDC_PB_ARTIKEL_GHS_PRUEF ) )
	{
		OnPbSetPruefDat();
	}
	else if ( GetFocus() == GetDlgItem( IDC_PB_ARTIKEL_SDB_COPY ) )
	{
		OnPbCopySafetyDataSheet();
	}

	ChPflegePage::NextDlgCtrl();
}
 
void CArtikelPage4::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CArtikelPage4::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage4::EnableFields( BOOL bEnab )
{   
	m_dlg.EnableFields( bEnab );

	// in Kroatien alle Felder deaktivieren, bis auf giftig und Zytostatika
	if (IsCountry("HR"))
	{
		m_dlg.EnableFields(0, m_nMaxFields - 1, FALSE );
		m_GS_GIFTIG.EnableWindow(true);
		m_ZYTOSTATIKA.EnableWindow(true);
		m_GS_LEICHTENTZ.EnableWindow(true);
	}

	m_GHS_AEDAT.EnableWindow(false);
	m_GHS_PRUEFDAT.EnableWindow(false);
	m_CALC_STORAGECLASS.EnableWindow(false);
	m_STOREROOM.EnableWindow(false);

	m_cHAZARDNOTEBOX.EnableWindow(bEnab);

	if (!IsCountry("D"))
	{
		m_BT_CMR.ShowWindow(SW_HIDE);
		GetDlgItem( IDC_CK_ARTIKEL_IS_CMR )->ShowWindow(SW_HIDE);
		GetDlgItem( IDC_CK_ARTIKEL_TEMP_BEACHT )->ShowWindow(SW_HIDE);
	}
}

void CArtikelPage4::OnPbIsCMR() 
{
	// as there is no read-only possibility for CheckBoxes and control should not be disabled --> workaround:
	m_BT_CMR.SetCheck( strcmp(((CArtikelView* )m_pView)->m_Doc.GetIfaOartBuffer()->A02CMR, "01") == 0  );
}

void CArtikelPage4::ShowFields( )
{
	FillComboBox();

	m_dlg.ShowFields();

	// invisible / unused / depricated with new SafetyDataSheet- Logic 06/2015:
	GetDlgItem( IDC_STATIC_G )->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_STATIC_H )->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_ED_ARTIKEL_GHS_GEFAHR_HINW)->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_ED_ARTIKEL_GHS_SICH_HINW)->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_STATIC_P)->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_STATIC_Z)->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_STATIC_B)->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_STATIC_D)->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_STATIC_K)->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_ED_ARTIKEL_GG_ZIFFER)->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_ED_ARTIKEL_GG_BUCHSTABE)->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_ED_ARTIKEL_G_DICHTE)->ShowWindow(SW_HIDE);
	GetDlgItem( IDC_ED_ARTIKEL_G_VBF)->ShowWindow(SW_HIDE);

	ShowADRInfo( TRUE );
	ShowStorageClass(TRUE);
	ShowCalcStorageClass(TRUE);
	
	// reset local member to avoid copying from last transaction
	strcpy(m_HAZARDNOTE_TO_ADD, "");
	m_HAZARDNOTE.p_SetInput();

	InitHazardNoteBox();
	CopyHazardNotesToGuiList();

	m_BT_SetPruefDat.SetMask	( IDB_BM_SEKBEZ, new CBitmap, NULL );
	m_BT_DelHazardNote.SetMask	( IDB_BM_DELETE, new CBitmap, NULL ); 
	m_BT_AddHazardNote.SetMask	( IDB_ARROW_LEFT, new CBitmap, NULL );

	if (IsCountry("D"))
		OnPbIsCMR();

	if (IsCountry("F"))
	{
		// set the current one
		SetHazardClassification();
	}
}

// --------------------------------------------------------------------- //
bool CArtikelPage4::FillHazardNoteBuffer( int i, CStringArray &s )
{
	CString errMld;
	
	s.SetSize( NUM_OF_HAZARDNOTES_COLUMNS );

	if (((CArtikelView* )m_pView)->GetBuffer()->chazardnotes[i].ARTICLENO <= 0 )
		return false;
	
	s[0] = ((CArtikelView* )m_pView)->GetBuffer()->chazardnotes[i].HAZARDNOTEID;
	s[0].TrimRight();

	// lesen hazardnotedesc in Spalte 1
	m_RD_HAZARDNOTE.IPlausi(((CArtikelView* )m_pView)->GetBuffer()->chazardnotes[i].HAZARDNOTEID, s[1] , &errMld);
	
	return true;
}

// --------------------------------------------------------------------- //
void CArtikelPage4::FillHazardNoteBox( CStringArray &s )
{
	int iSubItem;
	int col = 1;
	int index;

	index = m_cHAZARDNOTEBOX.GetItemCount();

	if ( m_cHAZARDNOTEBOX.InsertItem( index, s[0] ) == -1 ) 
		return;

	for (iSubItem = 1; iSubItem < NUM_OF_HAZARDNOTES_COLUMNS; iSubItem++)
	{
		if (m_Columns[iSubItem].isVisible == false)
			continue;
		
		m_cHAZARDNOTEBOX.SetItemText(index, col, s[iSubItem].GetBuffer(130));
		s[iSubItem].ReleaseBuffer(-1);
		col++;
	}
}

// --------------------------------------------------------------------- //
BOOL CArtikelPage4::InitHazardNoteBox()
{
	short j = NUM_OF_HAZARDNOTES_COLUMNS;
	
	while (j > 0)
	{
		--j;
		m_cHAZARDNOTEBOX.DeleteColumn(j);
	}

	
	m_Columns[NUM_OF_HAZARDNOTES_COLUMNS].Index = -1;
	strcpy(m_Columns[NUM_OF_HAZARDNOTES_COLUMNS].Columns, "");
	m_Columns[NUM_OF_HAZARDNOTES_COLUMNS].Width = 0;
	m_Columns[NUM_OF_HAZARDNOTES_COLUMNS].Align = 0;
	m_Columns[NUM_OF_HAZARDNOTES_COLUMNS].isVisible = false;

	m_Columns[0].Index = 0;
	strcpy(m_Columns[0].Columns, CResString::ex().getStrTblText(IDS_STRING87)); 
	m_Columns[0].Width = 50;
	m_Columns[0].Align = LVCFMT_LEFT;
	m_Columns[0].isVisible = true;
	
	m_Columns[1].Index = 1;
	strcpy(m_Columns[1].Columns, CResString::ex().getStrTblText(IDS_STRING88)); 
	m_Columns[1].Width = 150;
	m_Columns[1].Align = LVCFMT_LEFT;
	m_Columns[1].isVisible = true;

	LV_COLUMN lvC;

	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for ( COLUMNS_TYPES* pType = m_Columns; pType->Index != -1; pType++ )
	{
		if (pType->isVisible == false)
			continue;
		
		lvC.iSubItem	= pType->Index;
		lvC.pszText 	= LPTSTR(pType->Columns);
		lvC.fmt			= pType->Align;
		lvC.cx			= pType->Width;

		if ( m_cHAZARDNOTEBOX.InsertColumn( pType->Index, &lvC ) == -1 )
		{
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING327) );
			return FALSE;
		}
	}
	m_cHAZARDNOTEBOX.SetFullRowSel( TRUE );		// !!!!!!!!!!!!!!!!!!

	return TRUE;
}

void CArtikelPage4::CopyHazardNotesToGuiList()
{
	CStringArray s;
	m_cHAZARDNOTEBOX.DeleteAllItems();

	for ( int i = 0; i < NUMBER_OF_HAZARDNOTES; i++ )
	{
		if (false == FillHazardNoteBuffer( i, s ))
			break;

		FillHazardNoteBox( s );
	}	
}

struct CHAZARDCLASSIFICATION* CArtikelPage4::GetHazardClassification(long classID, CString classType)
{
	return ((CArtikelView*)m_pView)->m_Doc.GetHazardClassification(classID, classType);
}

void CArtikelPage4::FillHazardClassification()
{
	// load the entries, fill the combo
	m_pBufHazardClassification = GetHazardClassification(m_pBufSafteyDataSheet->ICPE_CLASSIFICATION_ID, "ICPE");
	// takes care of filling dynamically the combobox with long id and description
	m_ICPE_CODE.ResetContent();
	short index = 0;
	bool fnd = true;
	while ((index < NUMBER_OF_HAZARDCLASSIFICATIONS) && (fnd == true))
	{
		CHAZARDCLASSIFICATION* pItem = ((CArtikelView*)m_pView)->m_Doc.GetHazardClassification(index);
		if (pItem != NULL)
		{
			CString sEntry = "";
			sEntry.Format("%ld - %s", pItem->CLASSIFICATION_ID, pItem->DESIGNATION);
			sEntry.Trim();
			m_ICPE_CODE.AddString(sEntry);
		}
		else
		{
			fnd = false;
		}
		index++;
	}
}

void CArtikelPage4::SetHazardClassification()
{
	if ((m_pBufHazardClassification != NULL) && (m_ICPE_CODE.GetCount() > 0))
	{
		int index = 0;
		bool fnd = false;

		CString sID;
		sID.Format("%ld ", m_pBufHazardClassification->CLASSIFICATION_ID);

		while ((index < m_ICPE_CODE.GetCount()) && (fnd == false))
		{
			CString sEntry;
			m_ICPE_CODE.GetLBText(index, sEntry);
			if (sEntry.Left(sID.GetLength()).CompareNoCase(sID) == 0)
			{
				fnd = true;
				m_ICPE_CODE.SetCurSel(index);
				m_ICPE_CODE.UpdateWindow();
			}
			index++;
		}
	}
}

void CArtikelPage4::OnSelChangeICPE_Code()
{
	int index = m_ICPE_CODE.GetCurSel();
	if (index >= 0)
	{
		CString sEntry;
		m_ICPE_CODE.GetLBText(index, sEntry);
		CString sClassID = sEntry.Left(sEntry.Find(" - "));
		long lClassID = atol(sClassID);
		m_pBufSafteyDataSheet->ICPE_CLASSIFICATION_ID = lClassID;
		m_pBufHazardClassification = GetHazardClassification(m_pBufSafteyDataSheet->ICPE_CLASSIFICATION_ID, "ICPE");
	}
}

void CArtikelPage4::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage4::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

void CArtikelPage4::ActivateField( int nr )
{
    m_dlg.ActivateField( nr );
}

BOOL CArtikelPage4::Validate( BOOL bMeldung )
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

BOOL CArtikelPage4::OnSetActive()
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
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING313) );
	}
	return bOk;
}

BOOL CArtikelPage4::OnKillActive()
{
	BOOL bOk;
	bOk = CPropertyPageMultiLang::OnKillActive();
	if ( bOk )
	{
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING314) );
		SetValidation( FALSE );
		DataExchangeToBuffer( );  //  Puffer wie Eingabe
	}
	return bOk;
}

void CArtikelPage4::FillComboBox()
{
	m_PFLSCHUTZ_VERORD.ResetContent();
	m_PFLSCHUTZ_VERORD.AddString(CResString::ex().getStrTblText(IDS_STRING308));
	m_PFLSCHUTZ_VERORD.AddString(CResString::ex().getStrTblText(IDS_STRING309));
	m_PFLSCHUTZ_VERORD.AddString(CResString::ex().getStrTblText(IDS_STRING1020));
	m_PFLSCHUTZ_VERORD.AddString(CResString::ex().getStrTblText(IDS_STRING1021));
	m_PFLSCHUTZ_VERORD.AddString(CResString::ex().getStrTblText(IDS_STRING1022));
		
	m_GHS_SIGNAL.ResetContent();
	m_GHS_SIGNAL.AddString(CResString::ex().getStrTblText(IDS_STRING1233));
	m_GHS_SIGNAL.AddString(CResString::ex().getStrTblText(IDS_STRING1234));
	m_GHS_SIGNAL.AddString(CResString::ex().getStrTblText(IDS_STRING1235));

	if (IsCountry("CH"))
	{
		m_GHS_SIGNAL.AddString(CResString::ex().getStrTblText(IDS_MANUELL3));
		m_GHS_SIGNAL.AddString(CResString::ex().getStrTblText(IDS_NOSIGNALWORD));
	}

	m_LAGEEMPF.ResetContent();
	m_LAGEEMPF.AddString(CResString::ex().getStrTblText(IDS_STRING1233));
	m_LAGEEMPF.AddString(CResString::ex().getStrTblText(IDS_STRING1395));
	m_LAGEEMPF.AddString(CResString::ex().getStrTblText(IDS_STRING1396));

	m_STOREROOM.ResetContent();
	m_STOREROOM.AddString(CResString::ex().getStrTblText(IDS_STRING121));
	m_STOREROOM.AddString(CResString::ex().getStrTblText(IDS_STRING122));
	m_STOREROOM.AddString(CResString::ex().getStrTblText(IDS_STRING123));
	m_STOREROOM.AddString(CResString::ex().getStrTblText(IDS_STRING124));

	if (IsCountry("F"))
	{
		FillHazardClassification();
	}
}

void CArtikelPage4::CalculateStorageClass()
{
	// keine Verarbeitung, wenn Seite noch gar nicht aktiv war (Aufruf aus Validate der VCI-Lagerklasse), weil sonst Abbruch
	if (!((CArtikelView* )m_pView)->WasPageActive(3))
		return;

	// SDB-LGK in Puffer wegen Vergleich im Doc
	m_G_VCI.p_SetInput();

	// Gefahrstofffelder in Puffer wegen Alternativ-Ermittlung Lagerklasse
	m_GG_KLASSE.p_SetInput();
	m_G_VGRP.p_SetInput();
	m_G_UN_NR.p_SetInput();

	strncpy (m_pBufSafteyDataSheet->CALCSTORAGECLASSID, ((CArtikelView* )m_pView)->m_Doc.GetCalcstorageclassid(), L_CSAFETYDATASHEET_CALCSTORAGECLASSID);
	m_CALC_STORAGECLASS.p_SetInput();
	ShowCalcStorageClass(TRUE);
}

bool CArtikelPage4::CheckUnNr(BOOL bMeldung )
{
	if (((CArtikelView* )m_pView)->WasPageActive(3) == FALSE)
		return true;
	
	double dCount;
	CString sql = "";
	CString unNr;
	
	m_G_UN_NR.p_GetInput();
	unNr = m_pBufZartikel->G_UN_NR;
	unNr.Trim();

	if (!IsCountry("D") || unNr.IsEmpty() )
		return true;

	sql.Format( "select count(*) from CACCDANGERROUTE where G_UN_NR = '%s'", unNr );

	SqlRead(sql, &dCount, NULL);

	if (dCount > 0.0)
		return true;
	else 
	{
		if (bMeldung)
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1454) );

		return false;
	}
}

void CArtikelPage4::SetStoreRoom( short sStoreRoom )
{
	((CArtikelView* )m_pView)->GetBuffer()->csafetydatasheet.DANGERGOODSTOREROOM = sStoreRoom;

	m_STOREROOM.p_SetInput();
}
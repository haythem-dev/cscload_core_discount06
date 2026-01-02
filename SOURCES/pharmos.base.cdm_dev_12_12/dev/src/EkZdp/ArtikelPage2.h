#if !defined(AFX_ARTIKELPAGE2_H__BD2F47C2_7180_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ARTIKELPAGE2_H__BD2F47C2_7180_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtikelPage2.h : header file
//

#include "hPflegePage.h"
#include "ArticleCodesConverter.h"

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
#include "CheckComboBox.h"

#include <phxlib/RdZartikel.h>
#include <phxlib/RdHerstel.h>
#include <phxlib/RdCcurrency.h>
#include <phxlib/RdCdeposittypes.h>
#include <phxlib/RdAtx.h>

#include <voodoo_table_header/zartikel.h>

/////////////////////////////////////////////////////////////////////////////
// CArtikelPage2 dialog

class CArtikelPage2 : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage2)

// Construction
public:
	CArtikelPage2();
	~CArtikelPage2();

// Dialog Data
	//{{AFX_DATA(CArtikelPage2)
	enum { IDD = IDD_ARTIKEL_2 };
	ChDlgButton		m_EKORIGINALHS;
	ChDlgButton		m_BESTELL_NUR_OZEK;
	ChDlgComboBox	m_BESTELL_NICHT_AUSL;
	ChDlgButton		m_FAELSCH_GEFAHR;
	ChDlgButton		m_KURZERVERFALL;
	ChDlgComboBox	m_ZENTRALPPELIST;
	ChDlgEdit		m_EAR_NUMMER;
	ChDlgEdit		m_MELDENR;
	ChDlgEdit		m_IS_WARENNUMMER;
	ChDlgComboBox	m_PREISSENK;
	ChDlgEdit		m_DATUM_PREISSENKUNG;
	ChDlgComboBox	m_NAHR_TEST;
	ChDlgComboBox	m_NAHR_ERG;
	ChDlgComboBox	m_ELEKTROSCHROTT;
	ChDlgEdit		m_LAENGE;
	ChDlgEdit		m_BREITE;
	ChDlgEdit		m_HOEHE;
	ChDlgEdit		m_GEWICHT;
	ChDlgEdit		m_VOLUMEN;
	ChDlgEdit		m_DATUM_MWE;
	ChDlgButton		m_MELDEPFL;
	ChDlgButton		m_NICHT_UEBER_DAFUE;
	ChDlgButton		m_NICHT_UEBER_XML;
	ChDlgButton		m_BESTANDSBUCHUNG;
	ChDlgButton		m_ZENTR_EKSPERRE;
	ChDlgButton		m_VERBUNDSPERRE;
	ChDlgButton		m_FIXEDREGIONAL;
	ChDlgButton		m_BESTELLSPERRE;
	ChDlgButton		m_ARTIKEL_GELOESCHT;
	ChDlgEdit		m_ARTIKEL_NR_ORIG;
	ChDlgEdit		m_ARTIKEL_CODE_ORIG;
	ChDlgEdit		m_STD_MENGE;
	ChDlgComboBox	m_RUNDUNG_STD_MGE;
	ChDlgEdit		m_KONSIG_PARTNER_NR;
	ChDlgButton		m_CHARGENARTIKEL;
	ChDlgEdit		m_FREMDWAEHRUNGSCODE;
	ChDlgEdit		m_UMRECH_FAKTOR;
	ChDlgEdit		m_PACKGROESSE_FAKTOR;
	ChDlgEdit		m_DATUM_UMRECH;
	ChDlgComboBox	m_BATTERIEGESETZ;
	ChDlgButton		m_NEM_ZERTIFIKAT;
	ChDlgButton		m_NEM_PHAGROPRUEFUNG;
	ChDlgButton		m_KONTINGENT_PPE;
	ChDlgButton		m_KONTINGENT_HERST;
	ChDlgButton		m_KONTINGENT_MENGENSTEUERUNG;
	ChDlgEdit		m_PFANDTYP;
	ChDlgEdit		m_ATXKEY;
	ChDlgButton		m_APO_AUTO_KNAPP;
	ChDlgButton		m_APO_AUTO_ROWA;
	CCheckComboBox	m_BEZUGSSPERRE;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CArtikelPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:
	void InitPflege( CWnd *pView  );
	void EnableFields( BOOL bEnable );
	void ShowFields( );
	void SetDialog( BOOL bDialog = TRUE );
	void DataExchangeToBuffer( );
	void SetValidation( BOOL bValid );
	BOOL Validate( BOOL bMeldung );
	BOOL EndValidate( int *ind, BOOL bMeldung );
	void ActivateField( int nr );
	void SetMSStandard( BOOL bStandard );
	void Set_Elektroschrott( );
    BOOL TestEarnr( BOOL bMeldung );
	long CalculateVolume();
	void SetVolume( long iVolume);
	void CheckMeasureWeightChange( );

	BOOL ShowOriginalArtikel( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheOriginalArtikel();

	BOOL ShowKonsigPartner( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheKonsigPartner();

	BOOL ShowFremdwaehrung( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheFremdwaehrung();

	BOOL ShowPfandTyp( BOOL bShow, BOOL bMeldung = FALSE );
	void SuchePfandTyp();

	BOOL ShowArtText( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheArtText();

	BOOL SetArticleNoEditCtrl( CString& cErrmld );

	void ResetVkn( );

	void Set_Chargenartikel( );

	void Translation();

private:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive( );
	void SetArticleCodeEditCtrl();
	void DisableSpecial();
	void InitDlgDaten( );
	void MakeDialog( );
	void FillComboBox();
	void SetBatteriegesetz();
	void CalcBezugssperre();
	void ShowBezugssperre();

private:
	// Dialogdaten

	ChDlg m_dlg;	

	UINT m_nStatus;
	int  m_nMaxFields;

	int  m_Pos_ZENTRALPPELIST;
	int  m_Pos_ELEKTROSCHROTT;
	int  m_Pos_BESTELL_NICHT_AUSL;
	int  m_Pos_ZENTR_EKSPERRE;
	int  m_Pos_VERBUNDSPERRE;
	int  m_Pos_NAHRUNGSERGAENZUNG;
	int  m_Pos_VOLUMEN;
	int  m_Pos_DATUM_MWE;
	int  m_Pos_ARTIKEL_NR_ORIG;
	int  m_Pos_DATUM_PREISSENKUNG;
	int  m_Pos_CHARGENARTIKEL;
	int  m_Pos_EAR_NUMMER;

	CWnd *m_pView;
	struct ZARTIKEL			*m_pBufZartikel;
	struct CARTICLECODES	*m_pBufEarnr;
	struct CARTICLECODES	*m_pBufISWarennr;
	struct CARTFOREIGNCURR	*m_pBufCartforeigncurr;
	struct ZARTWG			*m_pBufPfandTyp;
	struct ZARTWG			*m_pBufArtText;
	struct CARTICLEEXT		*m_pBufCarticleext;
	struct CIBT				*m_pBufCibt;

	BOOL m_bInitialized;

	CRdZartikel			m_RD_ORIGINALARTIKEL;
	CRdHerstel			m_RD_KONSIG_PARTNER;
	CRdCcurrency		m_RD_WAEHRUNG;
	CRdCdeposittypes	m_RD_PFANDTYP;
	CRdAtx				m_RD_ARTTEXT;

	char m_ORIGINAL_ARTCODE[L_CARTICLECODES_ARTICLE_CODE + 1];

protected:
	// Generated message map functions
	//{{AFX_MSG(CArtikelPage2)
	afx_msg void OnSelchangeCbArtikelPreissenk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTIKELPAGE2_H__BD2F47C2_7180_11D1_92F8_0060973B18D8__INCLUDED_)

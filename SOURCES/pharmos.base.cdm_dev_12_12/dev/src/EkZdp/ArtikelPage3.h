#if !defined(AFX_ARTIKELPAGE3_H__BD2F47C3_7180_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ARTIKELPAGE3_H__BD2F47C3_7180_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtikelPage3.h : header file
//

#include "hPflegePage.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgCombobox.h>
#include <eklibs/hamfcs/hDlgButton.h>

#include <phxlib/RdArtkatg.h>
#include <phxlib/RdSaisonwg.h>
#include <phxlib/RdZdktgr.h>
#include <phxlib/RdZdkwgr.h>
#include <phxlib/RdZdkbtm.h>
#include <phxlib/RdZdkwir.h>
#include <phxlib/RdZrabgrp.h>
#include <phxlib/RdCspecarticletypes.h>
#include <phxlib/RdAtc.h>

#include <voodoo_table_header/zartikel.h>

/////////////////////////////////////////////////////////////////////////////
// CArtikelPage3 dialog

class CArtikelPage3 : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage3)

// Construction
public:
	CArtikelPage3();
	~CArtikelPage3();

// Dialog Data
	//{{AFX_DATA(CArtikelPage3)
	enum { IDD = IDD_ARTIKEL_3 };
	ChDlgEdit		m_IMSWGR;
	ChDlgEdit		m_EIGENEWGR;
	ChDlgEdit		m_SAISONWGR;
	ChDlgEdit		m_SAISONWGR2;
	ChDlgEdit		m_SAISONWGR3;
	ChDlgEdit		m_THERAPIEGRUPPE;
	ChDlgEdit		m_BTMGRUPPE;
	ChDlgEdit		m_WIRKSTOFF_NR;
	ChDlgComboBox	m_PRODUKTART;
	ChDlgEdit		m_RABATTGRP;
	ChDlgEdit		m_SPECARTTYP;
	ChDlgEdit		m_ABDACODE;
	ChDlgEdit		m_KATALOG;
	ChDlgEdit		m_DATUM_FMDPFLICHT;
	ChDlgButton		m_SORTIMENT_1;
	ChDlgButton		m_SORTIMENT_2;
	ChDlgButton		m_SORTIMENT_3;
	ChDlgButton		m_SORTIMENT_4;
	ChDlgButton		m_SORTIMENT_5;
	ChDlgButton		m_ARZNEIMITTEL;
	ChDlgButton		m_MEDIZINPRODUKT;
	ChDlgButton		m_CE_KENNZEICHEN;
	ChDlgButton		m_HILFSMV;
	ChDlgButton		m_IMPFSTOFF;
	ChDlgButton		m_REZEPTURARZNEI;
	ChDlgButton		m_HIGH_THERAPEUTIC_VAL;
	ChDlgButton		m_MEDIZINISCHE_GASE;
	ChDlgButton		m_HOMOEO;
	ChDlgButton		m_ANTHRO;
	ChDlgButton		m_PHYTO;
	ChDlgComboBox	m_FMD;
	ChDlgButton		m_STERIL;
	ChDlgButton		m_KOSMETIKUM;
	ChDlgButton		m_BIOSIEGEL;
	ChDlgButton		m_ANTIBIOTIKUM;
	ChDlgComboBox	m_KONTRAZEPTIVUM;
	ChDlgComboBox	m_BIOTECH_ARZNEI;
	ChDlgComboBox	m_PSYCHOTROP;
	ChDlgComboBox	m_ABGABEBEST_IFA;
	ChDlgComboBox	m_NEGATIVLISTE;
	ChDlgComboBox	m_PRIVATSORTIMENT;
	ChDlgEdit		m_CODE_ATC;
	ChDlgEdit		m_CODE_ATC_SUFFIX_HR;
	ChDlgEdit		m_CODE_OEKO;
	ChDlgButton		m_BT_MP31;
	ChDlgButton		m_BT_VERB31;
	ChDlgComboBox	m_MPKLASSE;
	ChDlgComboBox	m_INVITROKLASSE;
	ChDlgButton		m_WIRKSTOFF;
	ChDlgButton		m_SER_NUM_TRACK;
	ChDlgComboBox   m_NOVELFOOD;
	ChDlgButton     m_WUNDPRODUKT;
	ChDlgComboBox   m_NEUARTIGETHERAPIEN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CArtikelPage3)
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

	BOOL TestAtcCode( BOOL bMeldung );
	BOOL ShowAtcCode( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheAtcCode();
	void ComposeAtcCode();

    BOOL TestImsWgr( BOOL bMeldung );
	BOOL ShowImsWgr( BOOL bShow, BOOL bMeldung = FALSE );

    BOOL TestEigeneWgr( BOOL bMeldung );
	BOOL ShowEigeneWgr( BOOL bShow, BOOL bMeldung = FALSE );

	BOOL ShowSaisonWgr( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowSaisonWgr2( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowSaisonWgr3( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowTherapieGr( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowBtmGr( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowWirkstoff( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowRabGr( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowSpecArtTyp( BOOL bShow, BOOL bMeldung = FALSE );

	void SucheImsWgr();
	void SucheEigeneWgr();
	void SucheSaisonWgr();
	void SucheSaisonWgr2();
	void SucheSaisonWgr3();
	void SucheTherapieGr();
	void SucheBtmGr();
	void SucheWirkstoff();
	void SucheRabGr();
	void SucheSpecArtTyp();

	void ResetVkn( );

	void MakeSaisonwgString(CString Name, short Index);

	void SetSkontofaehig( );
	void SetTaxpfl( );

	void Translation();

	struct CARTICLECODES	*m_pBufAtc;
	char m_CODE_ATC_SUFFIX	[3 + 1];
	char m_CODE_ATC_PREFIX	[7 + 1];

	struct CARTICLECODES	*m_pBufOeko;

private:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive( );
	void InitDlgDaten( );
	void MakeDialog( );
	void FillComboBox();

private:
	// Dialogdaten

	ChDlg m_dlg;	

	int	 m_Pos_PRODUKTART;
	int	 m_Pos_PSYCHOTROP;
	int	 m_Pos_RABATTGRUPPE;

	UINT m_nStatus;
	int  m_nMaxFields;

	CWnd *m_pView;
	struct ZARTIKEL			*m_pBufZartikel;
	struct ZARTWG			*m_pBufImswg;
	struct ZARTWG			*m_pBufEigenewg;
	struct ZARTWG			*m_pBufTherapie;
	struct ZARTWG			*m_pBufAbdacode;
	struct ZARTWG			*m_pBufSaisonwg;
	struct ZARTWG			*m_pBufSaisonwg2;
	struct ZARTWG			*m_pBufSaisonwg3;
	struct ZARTWG			*m_pBufBtmgruppe;
	struct ZARTWG			*m_pBufRabattgruppe;
	struct ZARTWG			*m_pBufSpecarticletype;
	struct ZARTWG			*m_pBufWirkstoff;
	struct ZARTCROATIA		*m_pBufZartcroatia;
	struct ZARTSWITZERLAND	*m_pBufZartswitzerland;
	struct CARTICLEEXT		*m_pBufCarticleext;

	struct ZARTIKEL			*m_pBufOldZartikel; 

	// Aenderung Skontofaehig abhaengig von EigeneWgr
	BOOL m_bEigeneWgrMeldung;
	int  m_nSkontofaehig;
	char m_nTaxpflichtig;

	CStringArray m_csAlleSaisonwgs;

	BOOL m_bInitialized;

	CRdArtkatg				m_RD_IMSWGR;
	CRdSaisonwg				m_RD_SAISONWGR;
	CRdSaisonwg				m_RD_SAISONWGR2;
	CRdSaisonwg				m_RD_SAISONWGR3;
	CRdZdktgr				m_RD_THERAPIEGRUPPE;
	CRdZdkwgr				m_RD_EIGENEWGR;
	CRdZdkbtm				m_RD_BTMGRUPPE;
	CRdZdkwir				m_RD_WIRKSTOFF;
	CRdZrabgrp				m_RD_RABATTGRP;
	CRdCSpecArticleTypes	m_RD_SPECARTTYP;
	CRdAtc					m_RD_ATC;

	CString					m_INGREDIENT_TYPE;
	
	CFont* m_pSmallFont;

protected:
	// Generated message map functions
	//{{AFX_MSG(CArtikelPage3)
	afx_msg void OnCkArtikelSortiment_1();
	afx_msg void OnSelchangeCbPSYCHOTROP();
	afx_msg void OnPbIsMP31();
	afx_msg void OnPbIsVERB31();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTIKELPAGE3_H__BD2F47C3_7180_11D1_92F8_0060973B18D8__INCLUDED_)

#if !defined(AFX_ARTIKELPAGE4_H__B8C02E81_B9A5_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ARTIKELPAGE4_H__B8C02E81_B9A5_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtikelPage4.h : header file
//

#include "hPflegePage.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>

#include <phxlib/RdCaccdangerroute.h>

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/csafetydatasheet.h>
#include <voodoo_table_header/chazardnote.h>

#include <phxlib/rdcstorageclass.h>
#include <phxlib/rdchazardnote.h>

/////////////////////////////////////////////////////////////////////////////
// CArtikelPage4 dialog

// RK: This page has copy functionality. Do not forget to adjust it by field extension.

class CArtikelPage4 : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage4)

// Construction
public:
	CArtikelPage4();
	~CArtikelPage4();

// Dialog Data
	//{{AFX_DATA(CArtikelPage4)
	enum { IDD = IDD_ARTIKEL_4 };
	CListCtrlEx		m_cHAZARDNOTEBOX;
	ChDlgButton		m_ZYTOSTATIKA;
	ChDlgButton		m_BT_LAGERTEMP;
	ChDlgButton		m_SIDABLATT;
	ChDlgButton		m_BIOZID_VERORD;
	ChDlgButton		m_EXPLOSION;
	ChDlgComboBox	m_PFLSCHUTZ_VERORD;
	ChDlgEdit		m_BIOZID_REGNR1;
	ChDlgEdit		m_BIOZID_REGNR2;
	ChDlgEdit		m_PFL_ZULNR;
	ChDlgEdit		m_DATUM_PFL_ZUL_ENDE;
	ChDlgEdit		m_GG_KLASSE;
	ChDlgEdit		m_GG_BUCHSTABE;
	ChDlgEdit		m_GG_ZIFFER;
	ChDlgEdit		m_G_WASSER;
	ChDlgEdit		m_G_VCI;
	ChDlgEdit		m_G_VBF;
	ChDlgEdit		m_G_UN_NR;
	ChDlgEdit		m_G_VGRP;
	ChDlgEdit		m_G_TECH_NAME;
	ChDlgEdit		m_G_DICHTE;
	ChDlgEdit		m_SDS_LINK;
	ChDlgEdit		m_TEXT_GS;
	ChDlgButton		m_GS_EXPLOSION;
	ChDlgButton		m_GS_HOCHENTZ;
	ChDlgButton		m_GS_VORSLAGERN;
	ChDlgButton		m_GS_LICHTGESCH;
	ChDlgButton		m_GS_UMWELT;
	ChDlgButton		m_GS_SVORSLAGERN;
	ChDlgButton		m_GS_REIZEND;
	ChDlgButton		m_GS_AETZEND;
	ChDlgButton		m_GS_SEHRGIFTIG;
	ChDlgButton		m_GS_LEICHTENTZ;
	ChDlgButton		m_GS_GIFTIG;
	ChDlgButton		m_GS_GESUNDHSCH;
	ChDlgButton		m_GS_BRAND;
	ChDlgButton		m_GHS_PICT_01;
	ChDlgButton		m_GHS_PICT_02;
	ChDlgButton		m_GHS_PICT_03;
	ChDlgButton		m_GHS_PICT_04;
	ChDlgButton		m_GHS_PICT_05;
	ChDlgButton		m_GHS_PICT_06;
	ChDlgButton		m_GHS_PICT_07;
	ChDlgButton		m_GHS_PICT_08;
	ChDlgButton		m_GHS_PICT_09;
	ChDlgEdit		m_GHS_SICH_HINW;
	ChDlgEdit		m_GHS_GEFAHR_HINW;
	ChDlgEdit		m_GHS_EU_GEFAHR_HINW;
	ChDlgEdit		m_GHS_AEDAT;
	ChDlgEdit		m_GHS_VERSION;
	ChDlgComboBox	m_GHS_SIGNAL;
	ChDlgComboBox	m_STOREROOM;
	ChDlgComboBox	m_LAGEEMPF;

	ChDlgEdit		m_GHS_PRUEFDAT;
	ChDlgEdit		m_CALC_STORAGECLASS;
	ChDlgEdit		m_SDSSTATUS;
	ChDlgButton		m_NO_SDS_ACC_PROV;
	ChDlgButton		m_MARK_NOT_OBLIGATORY;
	ChDlgEdit		m_FLASHPOINT;
	ChDlgEdit		m_HAZARDNOTE;

	ChDlgButton		m_BT_SetPruefDat;
	ChDlgButton		m_BT_AddHazardNote;
	ChDlgButton		m_BT_CopySafetyDataSheet;
	ChDlgButton		m_BT_DelHazardNote;
	ChDlgButton		m_BT_CMR;

	ChDlgComboBox	m_ICPE_CODE;
	ChDlgEdit		m_CERTIFICATE_EXP_DATE;
	ChDlgEdit		m_DECL_CONFORMITY_DATE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CArtikelPage4)
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

	BOOL ShowADRInfo( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheADRInfo();

	void SucheStorageClass();
	BOOL ShowStorageClass(BOOL bShow, BOOL bMeldung = FALSE);
	void CalculateStorageClass();
	bool CheckUnNr(BOOL bMeldung);

	void SucheHazardNote();
	BOOL ShowHazardNote(BOOL bShow, BOOL bMeldung = FALSE);

	void NextDlgCtrl();   // wegen der pushbuttons

	void ResetVkn( );

private:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive( );
	void InitDlgDaten( );
	void MakeDialog( );
	void FillComboBox();
	void SetStoreRoom( short sStoreRoom );

	BOOL ShowCalcStorageClass(BOOL bShow, BOOL bMeldung = FALSE);

private:
	// Dialogdaten

	ChDlg m_dlg;	

	UINT m_nStatus;
	int  m_nMaxFields;

	CWnd *m_pView;
	struct ZARTIKEL* m_pBufZartikel;
	struct CARTICLECODES* m_pBufBiozid_Regnr1;
	struct CARTICLECODES* m_pBufBiozid_Regnr2;
	struct CARTICLECODES* m_pBufPfl_Zulnr;
	struct CSAFETYDATASHEET* m_pBufSafteyDataSheet;
	struct CHAZARDCLASSIFICATION* m_pBufHazardClassification;

	BOOL m_bInitialized;

	CRdCaccdangerroute		m_RD_ADR_INFO;
	CRdCStorageClass		m_RD_STORAGECLASS;
	CRdCHazardNote			m_RD_HAZARDNOTE;

	CFont* m_pSmallFont;

	char m_HAZARDNOTE_TO_ADD[L_CHAZARDNOTE_HAZARDNOTEID + 1];
	void CopyHazardNotesToGuiList();
	void FillHazardNoteBox(  CStringArray &s );
	bool FillHazardNoteBuffer( int i, CStringArray &s );
	BOOL InitHazardNoteBox();
	struct CHAZARDNOTE	*m_pBufHazardNote;
	struct CHAZARDCLASSIFICATION* GetHazardClassification(long classID, CString classType);
	void FillHazardClassification();
	void SetHazardClassification();

	struct COLUMNS_TYPES
	{
		int Index;
		char Columns[100];
		int Width;
		int Align;
		bool isVisible;
	};

	#define NUM_OF_HAZARDNOTES_COLUMNS	2
	struct COLUMNS_TYPES m_Columns[NUM_OF_HAZARDNOTES_COLUMNS + 1];

protected:
	// Generated message map functions
	//{{AFX_MSG(CArtikelPage4)
	afx_msg void OnPbSetPruefDat();
	afx_msg void OnPbAddHazardNote();
	afx_msg void OnPbDelHazardNote();
	afx_msg void OnPbCopySafetyDataSheet();
	afx_msg void OnPbIsCMR();
	afx_msg void OnSelChangeICPE_Code();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTIKELPAGE4_H__B8C02E81_B9A5_11D1_92F8_0060973B18D8__INCLUDED_)

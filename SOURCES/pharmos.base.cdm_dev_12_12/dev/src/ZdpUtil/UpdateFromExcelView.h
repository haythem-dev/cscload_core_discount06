#if !defined __UPDATE_FROM_EXCEL_VIEW_H__
#define __UPDATE_FROM_EXCEL_VIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "hPflegeView.h"
#include "PflFelder.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
#include <eklibs/hamfcs/hColStatic.h>

#include <phxlib/RdHerstel.h>
#include <phxlib/RdBliefer.h>

#include <phxlib/RdArtkatg.h>
#include <phxlib/RdSaisonwg.h>
#include <phxlib/RdZdktgr.h>
#include <phxlib/RdZdkwgr.h>
#include <phxlib/RdZdkbtm.h>
#include <phxlib/RdZrabgrp.h>
#include <phxlib/RdCarticlecategory.h>
#include <phxlib/RdCpromotions.h>

#include <phxlib/RdZartikel.h>
#include <phxlib/RdCdiscgrp.h>
#include <phxlib/RdCpharmgrp.h>

#include <phxlib/RdEphmra.h>
#include <phxlib/RdAtc.h>
#include <phxlib/RdLpprCode.h>
#include <phxlib/RdCReimbursementPct.h>
#include <phxlib/RdCppeArtCategory.h>
#include <phxlib/RdCintrastatcountry.h>


/*------------------------------------------------------------------------*/
class CUpdateFromExcelView : public ChPflegeView
{
public:
	CUpdateFromExcelView();  
	virtual ~CUpdateFromExcelView();

	DECLARE_DYNCREATE(CUpdateFromExcelView)

	//{{AFX_DATA(CUpdateFromExcelView)
	enum { IDD = IDD_UPDFROMEXCEL };
	CEdit		m_ed_PznCol;
	CButton		m_bt_ZArtikel;
	CButton		m_bt_ZArtWg;
	CButton		m_bt_ZArtPreis;
	CButton		m_bt_CDiscount;
	ChColStatic		m_st_RestVal;
	ChColStatic		m_st_CkRestNeg;
	ChColStatic		m_st_StatCsvVal;
	ChColStatic		m_st_CkStatVal;
	ChColStatic		m_st_Column;
	CEdit			m_ed_Muster;
	CButton			m_ck_Muster;
	CComboBox		m_cb_Muster;
	//}}AFX_DATA
	
	void CkStatValClicked ();
	void CkRestNegClicked ();
	
	//-- cdiscount --
	BOOL TestPZN			( CString csPZN, BOOL bMeldung );
	BOOL TestDiscountGroup	( CString csDiscGrp, BOOL bMeldung );
	BOOL TestPharmacyGroup	( CString csPharmGrp, BOOL bMeldung );
	BOOL TestPct			( CString & csPct, BOOL bMeldung );
	BOOL TestDiscountCustomer(CString csCustomer, BOOL bMeldung );	
	BOOL TestDiscountManufacturer(CString csManufacturer, BOOL bMeldung );	
	BOOL TestArtCategory	(CString csArtCatNo, BOOL bMeldung );
	BOOL TestPromo			(CString csPromoNo, BOOL bMeldung );
			
	//-- zartikel --
	BOOL TestAwl1( CString csAwl1, BOOL bMeldung );
	BOOL TestDatumAh( CString csDat, BOOL bMeldung );
	BOOL TestArtNrOrig( CString & csArtNr, BOOL bMeldung );
	BOOL TestManufacturer(CString csManufacturer, BOOL bMeldung );	
	BOOL TestPrismaEWoche(CString csPrimaEWoche, BOOL bMeldung);
    	
	//-- zartwg --
	BOOL TestWgArt1( CString csWgr, BOOL bMeldung );
	BOOL TestWgArt2( CString csWgr, BOOL bMeldung );
	BOOL TestWgArt3( CString csWgr, BOOL bMeldung );
	BOOL TestWgArt4( CString csWgr, BOOL bMeldung );
	BOOL TestWgArt5( CString csWgr, BOOL bMeldung );
	BOOL TestWgArt6( CString csWgr, BOOL bMeldung );
	BOOL TestWgArt7( CString csWgr, BOOL bMeldung );
	BOOL TestWgArt8( CString csWgr, BOOL bMeldung );
	BOOL TestWgArt9( CString csWgr, BOOL bMeldung );
	BOOL TestWgArtA( CString csWgr, BOOL bMeldung );
	BOOL TestWgArtG( CString csWgr, BOOL bMeldung );
	
	//-- zartpreis --
	BOOL TestGueltab( CString csDat, BOOL bMeldung );
	BOOL TestPrice	( CString csDat, BOOL bMeldung, int nValNumber );


	//-- cdiscount --
	BOOL TestDiscBaseQty( CString csBaseQty, BOOL bMeldung );
	BOOL TestDiscDateTo( CString csDat, BOOL bMeldung );
	BOOL TestDiscDateFrom( CString csDat, BOOL bMeldung );

	//-- artve --
	BOOL TestArtVeVPE( CString csVPE, BOOL bMeldung );

	//-- carticlecodes
	BOOL TestArtCode( CString code, BOOL bMeldung );

	//-- zartfrance --
	BOOL TestReimbPct( CString pct, BOOL bMeldung );
	BOOL TestCodeLppr( CString lppr, BOOL bMeldung );

	//-- cgibatchentry --
	BOOL TestCompanyCode( CString csDat, BOOL bMeldung );

	//-- zchargenrr --
	BOOL TestCharge( CString batch, BOOL bMeldung );

	//-- zchargenrr --
	BOOL TestCountry( CString country, BOOL bMeldung );

	//-- ean --
	BOOL TestEan( CString ean, BOOL bMeldung );

	//-- Nachlieferung --
	BOOL TestNachl(CString csNachlieferung, BOOL bMeldung);
	BOOL TestKontMengenSteuerung(CString csFlag, BOOL bMeldung);

	//-- Bliesort --
	BOOL TestBeslaNo(CString csBeslaNo, BOOL bMeldung);

	enum EUpdTable
	{
		UPD_ZARTIKEL = 1,
		UPD_ZARTPREIS = 2,
		UPD_ZARTWG = 3,
		UPD_CDISCOUNT = 4,
		UPD_CDISCOUNT_FLEXIBLE = 5,
		UPD_CDISCOUNT_STOP = 6,
		UPD_ARTVE = 7,
		UPD_CDISCGRPMEM = 8,
		UPD_ZARTFRANCE = 9,
		UPD_CARTICLECODES = 10,
		UPD_CARTCOMPACK = 11,
		UPD_CGIBATCHENTRY = 12,
		UPD_ZARTSWITZERLAND = 13,
		UPD_CARTICLEEXT = 14,
		UPD_ZCHARGENRR = 15,
		UPD_ZARTSERBIA = 16,
		UPD_ZARTAUSTRIA = 17,
		UPD_CIMEXBLOCK = 18,
		UPD_CIBT = 19,
		UPD_EAN = 20,
		UPD_KONTMENGENST = 21,
		UPD_ZARTWG_5AG = 22,
		UPD_BLIESORT = 23,
		UPD_BASELISTARTICLES = 24,
		UPD_ARTMEDACTOR = 25,
		UPD_MEDICALACTOR = 26,

		NONE = -1
	};
	
private:
	void InitPflege();
	bool IsDigit( CString cS );
	BOOL EndValidate( );
	void InitVariables();
	bool ExtractFromCsv( CString &cErrmld, char *ColumnHeaderPzn, long *nAnz );
	bool ExtractFromTxt( CString &cErrmld, long *nAnz );
	bool CallUnxBatch( CString &cErrmld, short testMode );
	void ShowPZNField(bool bShow);

	EUpdTable m_eUpdTable;
		
	ChDlg m_dlg;
	int m_Pos_Top;	

	bool m_Reset_CDiscount_DateTo;

	// Edit Valdidate
	CRdHerstel	m_RD_AWL1;
	CRdBliefer	m_RD_AWL1_FR;
		
	CRdArtkatg	m_RD_IMSWGR;
	CRdSaisonwg	m_RD_SAISONWGR;
	CRdSaisonwg	m_RD_SAISONWGR2;
	CRdSaisonwg	m_RD_SAISONWGR3;
	CRdZdktgr	m_RD_THERAPIEGRUPPE;
	CRdZdkwgr   m_RD_EIGENEWGR;
	CRdZdkbtm   m_RD_BTMGRUPPE;
	CRdZrabgrp	m_RD_RABATTGRP;
	
	CRdZartikel		 m_RD_ZARTIKEL;
	CRdCdiscgrp		 m_RD_CDISCGRP;
	CRdCpharmgrp	 m_RD_CPHARMGRP;
	CRdHerstel		 m_RD_HERSTELLER;
	CRdCarticlecategory		m_RD_CARTCAT;
	CRdCpromotions	 m_RD_CPROMOTIONS;

	CRdEphmra			m_RD_EPHMRA;
	CRdAtc				m_RD_ATC;
	CRdLpprCode			m_RD_LPPRCODE;
	RdCreimbursementPct m_RD_REIMBPCT;
	CRdCintrastatcountry		 m_RD_COUNTRY;

	CRdCppeArtCategory m_RD_CPPEARTCATEGORY;

	CRdBliefer m_RD_BLIEFER;

	// Farben
	COLORREF m_clrHeaderFarbe;

	CZdpUtilApp* theApp;
	bool m_bComeBack;
	bool m_bDoResize;

	CString m_UnxDirectory;

	CPflFelder m_PflFeldDlg;

	struct PFL_FELD *m_PflFelder [ ANZ_FELDER_UPD ];
	int    m_nAnzF; 

	// 3 feste Spalten-Typen
	ChDlgEdit*		m_ed_UpdCol		[ ANZ_FELDER_UPD ];
	ChDlgButton*	m_ck_StaticVal	[ ANZ_FELDER_UPD ];
	ChDlgButton*	m_ck_NegRest	[ ANZ_FELDER_UPD ];

#define CK_CLICKED 1
#define DELIMITER  "|"
#define DELIMITER_CHAR  '|'

	int m_nAnzRows;
	int				m_i_CkStatVal   [ ANZ_FELDER_UPD ];
	int				m_i_CkNegRest   [ ANZ_FELDER_UPD ];
	
	// CsvColumn / Festwert: CK, Combo, Edit
	ChDlgEdit*		m_ed_StatVal [ ANZ_FELDER_UPD ];
	ChDlgButton*	m_bt_StatVal [ ANZ_FELDER_UPD ];
	ChDlgComboBox*	m_cb_StatVal [ ANZ_FELDER_UPD ];

	// NegWert
	ChDlgEdit*		m_ed_NegVal [ ANZ_FELDER_UPD ];
	ChDlgButton*	m_bt_NegVal [ ANZ_FELDER_UPD ];
	ChDlgComboBox*	m_cb_NegVal [ ANZ_FELDER_UPD ];


	enum { IDC_OFFSET_EDIT    = 2000,	
		   IDC_OFFSET_BUTTON  = IDC_OFFSET_EDIT    + ANZ_FELDER_UPD, 
		   IDC_OFFSET_COMBO   = IDC_OFFSET_BUTTON  + ANZ_FELDER_UPD };

	void GenMaske( );
	void HideControls();
	void GenTabelle( );
	void GenFelder( );
	BOOL GenEditFeld( int iLine, CWnd *pWndAbove, bool bEdNegVal = false, bool bCsvCol = false );
	BOOL GenButtonFeld( int iLine, CWnd *pWndAbove, bool bEdNegVal = false );
	BOOL GenComboBoxFeld( int iLine, CWnd *pWndAbove, bool bEdNegVal = false );
	
	BOOL GenCkStatVal( CWnd *pWndAbove );
	BOOL GenCkRestNeg( CWnd *pWndAbove );
	BOOL GenColNameFeld( CWnd *pWndAbove );
	
	void GenFont(  CWnd *pWnd );
	void FillCombo( CComboBox *pWnd, char *str );
	int  AnzComboDaten( char *str );
	
	void GotoTop();

	ChMaskBase*  NewMask( int nMaskNumber );
	ChValBase*   NewValidate( int nValNumber,
							  CUpdateFromExcelView *pThisView, ChDlgEdit* pWnd );
	
	bool GetCtrlValues();
	bool CreateHeaderLines( CString &csHeaderLines );
	bool Create_ZArtWG_5AG_Lines( CString& cItem );

	bool checkLineValidity( CString &csLine, CString &cErrmld );
	void detectColsForLineValidityCheck();
	short m_PosOfDiscountSpec;
	short m_PosOfMonthlyDiscountFlag;
	short m_PosOfDiscDateFrom;
	short m_PosOfDiscDateTo;

public:

	struct sLine {
		CString csUpdateCol;
		bool bTakeCsvCol;
		CString csCsvCol_StatVal;
		bool bNegRest;
		CString csNegVal;
	};

	struct sLine *ST_LineVal [ ANZ_FELDER_UPD ];


	int BearbeiteSatz();
	int UndoSatz();
	int SpeichereSatz( );
	bool GetInfoFromCallingView( CString& cStr, int nAction );


	//{{AFX_VIRTUAL(CUpdateFromExcelView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

protected:
	
	//{{AFX_MSG(CUpdateFromExcelView)
	afx_msg void OnBtZArtikel();
	afx_msg void OnBtZArtPreis();
	afx_msg void OnBtArtVe();
	afx_msg void OnBtCibt();
	afx_msg void OnBtZArtWg();
	afx_msg void OnBtCDiscount();
	afx_msg void OnBtCDiscountFlexible();
	afx_msg void OnBtCDiscountEnd();
	afx_msg void OnBtCDiscGrpMem();
	afx_msg	void OnBtCArtComPack();
	afx_msg void OnBtCountry();
	afx_msg void OnBtCodes();
	afx_msg void OnBtCGiBatchEntry();
	afx_msg void OnBnClickedBtCarticleext();
	afx_msg void OnBnClickedBtZChargenRR();
	afx_msg void OnBtCimexblock();
	afx_msg void OnBtEAN();
	afx_msg void OnBtSubsequentDelivery();
	afx_msg void OnBtZArtWg5AG();
	afx_msg void OnBtBliesort();
	afx_msg void OnBtBaselist();
	afx_msg void OnBtCartmedactor();
	afx_msg void OnBtCmedicalactor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#endif

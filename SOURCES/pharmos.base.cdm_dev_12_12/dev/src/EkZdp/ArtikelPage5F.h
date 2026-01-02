#include "hPflegePage.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
//#include <hDlgMultiComboBox.h>
#include "CheckComboBox.h"

#include <phxlib/RdLpprCode.h>
#include <phxlib/RdZrabgrp.h>
#include <phxlib/RdCReimbursementPct.h>
#include <phxlib/RdEphmra.h>

#define NUMBER_OF_PREWHOLECUSTOMERGROUP 100

#pragma once


// CArtikelPage5F-Dialogfeld

class CArtikelPage5F : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage5F)

	friend class CRefundFrance;

public:
	CArtikelPage5F();
	virtual ~CArtikelPage5F();

// Dialog Data
	//{{AFX_DATA(CArtikelPage4)
	enum { IDD = IDD_ARTIKEL_5F };
	ChDlgEdit		m_UEBEREINH;
	ChDlgEdit		m_MGEUNTER;
	ChDlgComboBox	m_ERST_TYP;
	ChDlgEdit		m_ERST_PROZ;
	ChDlgEdit		m_ERST_WERT;
	ChDlgEdit		m_ERST_BASIS;
	ChDlgEdit		m_CODE_LPPR;
	ChDlgButton		m_VERTRBIND_EXPORT;
	ChDlgButton		m_RES_HOSP;
	ChDlgButton		m_NOEDI;
	ChDlgButton		m_VERTRBIND_LEGALL;
	ChDlgButton		m_VERTRBIND_BREIZH;
	ChDlgButton		m_VERTRBIND_HOSPITAL;
	ChDlgEdit		m_RABATTGRP_SP;
	ChDlgComboBox	m_CODE_BLOQUAGE;
	ChDlgEdit		m_CODE_EPHMRA;
	ChDlgEdit		m_RF_DATUM;
	ChDlgComboBox	m_RF_ERST_TYP;
	ChDlgEdit		m_RF_ERST_PROZ;
	ChDlgEdit		m_RF_ERST_WERT;
	ChDlgEdit		m_RF_ERST_BASIS;
	ChDlgEdit		m_RF_CODE_LPPR;
	ChDlgButton		m_PB_REFUND;
	ChDlgButton		m_NACHLIEFERUNG;
	ChDlgButton		m_CONSIGNED;
	CCheckComboBox  m_CUSTOMERGROUP;
	ChDlgComboBox   m_MAIN_CUSTOMERGROUP;
	//}}AFX_DATA

public:
	void InitPflege( CWnd *pView  );
	void EnableFields( BOOL bEnable );
	void EnableRfType( BOOL bFocus );
	void ShowFields( );
	void SetDialog( BOOL bDialog = TRUE );
	void DataExchangeToBuffer( );
	void SetValidation( BOOL bValid );
	BOOL Validate( BOOL bMeldung );
	BOOL EndValidate( int *ind, BOOL bMeldung );
	void ActivateField( int nr );
	void SetMSStandard( BOOL bStandard );

	BOOL ShowLpprCode( short sWhichRefund, BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowReimbPct( short sWhichRefund, BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowRabGr_Sp( BOOL bShow, BOOL bMeldung = FALSE );

	BOOL TestEphmraCode( BOOL bMeldung );
	BOOL ShowEphmraCode( BOOL bShow, BOOL bMeldung = FALSE );

	void SucheReimbPct( short sWhichRefund );
	void SucheLpprCode( short sWhichRefund );
	void SucheRabGr_Sp();
	void SucheEphmraCode();
	
	void ResetVkn( );
	void ChangeRefundValues( short sWhichRefund );
	BOOL TestRfDatum( );

	void NextDlgCtrl();   // wegen der pushbuttons

private:
	virtual BOOL OnSetActive( );
	virtual BOOL OnKillActive( );
	void InitDlgDaten( );
	void MakeDialog( );
	void FillComboBox( );
	void ShowRefundFields( BOOL bEnab, CString csRefundCode );
	void ShowNewRefundFields( BOOL bEnab, CString csRefundCode );
	CString GetActiveRefundFields( char Reimbursement_type );
	
	struct PREWHOLE_CUSTOMERGROUP* m_pBufPrewholeCustomerGroup;
	struct PREWHOLE_CUSTOMERGROUP* GetMainCustomerGroup(long classID, CString classType);
	void FillMainCustomerGroup();
	void SetMainCustomerGroup();
	void ShowCustomerGroup();
	void FillCustmerGroup();

private:
	// Dialogdaten

	ChDlg m_dlg;	

	UINT m_nStatus;
	int  m_nMaxFields;
	int  m_Pos_ERST_WERT;
	int  m_Pos_ERST_PROZ;
	int  m_Pos_ERST_BASIS;
	int  m_Pos_CODE_LPPR;
	int  m_Pos_RF_ERST_WERT;
	int  m_Pos_RF_ERST_PROZ;
	int  m_Pos_RF_ERST_BASIS;
	int  m_Pos_RF_CODE_LPPR;
	int	 m_Pos_RABATTGRUPPE_SP;

	CWnd *m_pView;
	struct ZARTFRANCE		*m_pBufZartfrance;
	struct CARTICLECODES	*m_pBufEphmra;
	struct CARTREFUNDFRANCE	*m_pBufCartrefundfrance;
	
	BOOL m_bInitialized;
	BOOL isOldChecked[NUMBER_OF_PREWHOLECUSTOMERGROUP] = {};

	CRdLpprCode			m_RD_LPPRCODE;
	CRdZrabgrp			m_RD_RABATTGRP;
	RdCreimbursementPct m_RD_REIMBPCT;
	CRdEphmra			m_RD_EPHMRA;

	double m_REIMB_PCT;
	double m_RF_REIMB_PCT;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	//{{AFX_MSG(CArtikelPage5F)
	afx_msg void OnSelchangeCbTyp();
	afx_msg void OnSelchangeCbRfTyp();
	afx_msg void OnPbRefund();
	afx_msg void OnSelChangeMainCustomerGroup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

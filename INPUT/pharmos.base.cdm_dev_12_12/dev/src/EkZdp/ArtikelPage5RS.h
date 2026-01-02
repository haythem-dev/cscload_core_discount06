#include "hPflegePage.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>

#include <phxlib/RdZoll.h>

//#include <hDlgMultiComboBox.h>

#pragma once


// CArtikelPage5RS-Dialogfeld

class CArtikelPage5RS : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage5RS)

public:
	CArtikelPage5RS();
	virtual ~CArtikelPage5RS();

// Dialog Data
	//{{AFX_DATA(CArtikelPage4)
	enum { IDD = IDD_ARTIKEL_5RS };
	ChDlgComboBox	m_ARTICLETYPE;
	ChDlgEdit		m_CUSTOMSNO;
	ChDlgEdit		m_MAXPAYMENTTARGET;
	ChDlgEdit		m_PACK_SIZE;
	ChDlgEdit		m_ZOLL_PROZ;
	ChDlgEdit		m_JKL_CODE;
	ChDlgButton		m_REFUNDTYPE;
	ChDlgButton		m_PACKAGE_INSERT;
	ChDlgButton		m_CERTIFICATEFLAG;
	ChDlgButton		m_VERTRBIND1_RS;
	ChDlgButton		m_VERTRBIND2_RS;
	ChDlgButton		m_VERTRBIND3_RS;
	ChDlgButton		m_VERTRBIND4_RS;
	ChDlgButton		m_VERTRBIND5_RS;
	ChDlgButton		m_VERTRBIND6_RS;
	ChDlgButton		m_VERTRBIND7_RS;
	ChDlgButton		m_VERTRBIND8_RS;
	//}}AFX_DATA

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
	void ResetVkn( );
	void Set_Artikel_Name( );
	void Translation();

	BOOL ShowZolldaten( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheZolldaten();

private:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive( );
	void InitDlgDaten( );
	void MakeDialog( );
	void FillComboBox();

private:
	// Dialogdaten

	ChDlg m_dlg;	

	UINT m_nStatus;
	int  m_nMaxFields;
	int  m_Pos_ARTIKEL_NAME;

	CWnd *m_pView;
	struct ZARTSERBIA		*m_pBufZartserbia;
	struct CARTICLECODES	*m_pBufJKLCode;

	CRdZoll	m_RD_ZOLL;

	BOOL m_bInitialized;

	struct CARTICLEEXT	*m_pBufCarticleext;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
};

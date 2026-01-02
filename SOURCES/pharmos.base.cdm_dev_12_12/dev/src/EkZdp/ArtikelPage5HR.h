#include "hPflegePage.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
//#include <hDlgMultiComboBox.h>

#pragma once


// CArtikelPage5HR-Dialogfeld

class CArtikelPage5HR : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage5HR)

public:
	CArtikelPage5HR();
	virtual ~CArtikelPage5HR();

// Dialog Data
	//{{AFX_DATA(CArtikelPage4)
	enum { IDD = IDD_ARTIKEL_5HR };
	ChDlgButton		m_CHARGE;
	ChDlgEdit		m_DATUM_LIEFERBAR_AB;
	ChDlgButton		m_VERTRBIND1_HR;
	ChDlgButton		m_VERTRBIND2_HR;
	ChDlgButton		m_VERTRBIND3_HR;
	ChDlgButton		m_VERTRBIND4_HR;
	ChDlgButton		m_VERTRBIND5_HR;
	ChDlgButton		m_VERTRBIND6_HR;
	ChDlgButton		m_VERTRBIND7_HR;
	ChDlgButton		m_VERTRBIND8_HR;
	ChDlgButton		m_CERTIFICATEFLAG;
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

	void Set_ExchangeRate( );
	void Set_BatchArticle( );

private:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive( );
	void InitDlgDaten( );
	void MakeDialog( );

private:
	// Dialogdaten

	ChDlg m_dlg;	

	UINT m_nStatus;
	int  m_nMaxFields;

	int  m_Pos_BATCHARTICLE;

	CWnd *m_pView;
	
	struct ZARTCROATIA	*m_pBufZartcroatia;

	struct CARTICLEEXT	*m_pBufCarticleext;
	struct ZARTIKEL	    *m_pBufZartikel;

	BOOL m_bInitialized;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdArtikelUmrechFaktor();
};

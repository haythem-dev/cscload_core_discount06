#include "hPflegePage.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
//#include <hDlgMultiComboBox.h>

#include <phxlib/RdAtx.h>

#pragma once


// CArtikelPage5A-Dialogfeld

class CArtikelPage5A : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage5A)

public:
	CArtikelPage5A();
	virtual ~CArtikelPage5A();

// Dialog Data
	//{{AFX_DATA(CArtikelPage4)
	enum { IDD = IDD_ARTIKEL_5A };
	ChDlgButton		m_WECHSELARTIKEL;
	ChDlgButton		m_BUENDELPACKUNG;
	ChDlgButton		m_WAFO;
	ChDlgButton		m_DBESORGER;
	ChDlgButton		m_CHARGE;
	ChDlgComboBox	m_OELHV_OEKOKZ;
	ChDlgEdit		m_OELHV_GRUPPE;
	ChDlgEdit		m_OELHV_SORT;
	ChDlgComboBox	m_HV_BOX;
	ChDlgComboBox	m_MEDPROD_ABGVO;
	ChDlgComboBox	m_MEDPROD_KLASSE;
	ChDlgButton		m_VERTRBIND_PLPL;
	ChDlgButton		m_VERTRBIND_S1S5;
	ChDlgButton		m_VERTRBIND_VPL;
	ChDlgButton		m_VERTRBIND_SP;
	ChDlgButton		m_VERTRBIND_NEUFORM;
	ChDlgButton		m_VERTRBIND_BEIERSDORF;
	ChDlgComboBox	m_VERTRBIND_COMPTANT;
	ChDlgButton		m_SG_SUBSTANZ;
	ChDlgButton		m_GH_LAGERUNG_VERBOTEN;
	ChDlgButton		m_DROGENAGS_KAT1;
	ChDlgButton		m_DROGENAGS_KAT2;
	ChDlgButton		m_DROGENAGS_KAT3;
	ChDlgButton		m_NLH;
	ChDlgButton		m_NGH;
	ChDlgEdit		m_RUECK_MON_VOR_VERF;
	ChDlgEdit		m_INGREDIENT_QTY;
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

	BOOL ShowArtText( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheArtText();

//	void ResetVkn( );

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

	CWnd *m_pView;
	struct ZARTAUSTRIA	*m_pBufZartaustria;
	
	BOOL m_bInitialized;

	#define MAX_OEKOKZ 10
	char m_cOekoKz[2*MAX_OEKOKZ + 1]; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	afx_msg void OnPbDBesorger();

	DECLARE_MESSAGE_MAP()
};

#include "hPflegePage.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
//#include <hDlgMultiComboBox.h>
#include <phxlib/RdDform.h>
#include <phxlib/rdassortment.h>

#pragma once


// CArtikelPage5CH-Dialogfeld

class CArtikelPage5CH : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage5CH)

public:
	CArtikelPage5CH();
	virtual ~CArtikelPage5CH();

// Dialog Data
	//{{AFX_DATA(CArtikelPage4)
	enum { IDD = IDD_ARTIKEL_5CH };
	ChDlgEdit	m_ARTIKEL_NAME_D;
	ChDlgEdit	m_EINHEIT_D;
	ChDlgEdit	m_DARREICHFORM_D;
	ChDlgEdit	m_ARTIKEL_NAME_F;
	ChDlgEdit	m_EINHEIT_F;
	ChDlgEdit	m_DARREICHFORM_F;
	ChDlgEdit	m_ARTIKEL_LANGNAME_D;
	ChDlgEdit	m_ARTIKEL_LANGNAME_F;
	ChDlgEdit	m_IKS_CODE;
	ChDlgEdit	m_SWISSMEDIC_REGNR;
	ChDlgEdit	m_SWISSMEDIC_ZUSATZ;
	ChDlgEdit	m_WARNPROZVORPLM;
	ChDlgEdit	m_ANTIBIOTIKA_FNR;
	ChDlgEdit	m_ZOLLPOS_NR;
	ChDlgEdit	m_BAGDOSSIER;
	ChDlgEdit	m_MIGCD;
	ChDlgEdit	m_PFLICHTLAGERMENGE;
	ChDlgButton m_BUENDELPACKUNG;
	ChDlgButton	m_VERTRBIND_NUR_APO;
	ChDlgButton	m_VERTRBIND_NUR_SPIT;
	ChDlgButton	m_VERTRBIND_KUENZLE;
	ChDlgButton	m_VERTRBIND_INLAND;
	ChDlgButton	m_VERTRBIND_KANTONAL;
	ChDlgButton	m_VERTRBIND_PREWHOLE;
	ChDlgButton	m_VERTRBIND_LISTE_C;
	ChDlgButton	m_VERTRBIND_LISTE_D;
	CStatic		m_ST_SPR_ZEIL1;
	CStatic		m_ST_SPR_ZEIL2;
	CStatic		m_ST_SPR_ZEIL3;
	CStatic		m_ST_SPR_ZEIL4;
	ChDlgEdit	m_CODE_ASSORTMENT;
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
	BOOL ShowDform_D( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheDform_D();
	BOOL ShowDform_F( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheDform_F();
	void ResetVkn( );
	void Set_Artikel_Name( );
	void SetRezeptpfl( );
	void SetVertriebsbind( );
	void Set_Vertrbind_Inland( );
	void Translation();

	BOOL TestAssortmentCode( BOOL bMeldung );
	BOOL ShowAssortmentCode( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheAssortmentCode();	

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
	int  m_Pos_ARTIKEL_NAME;
	int  m_Pos_VERTRBIND_LISTE_D;
	int  m_Pos_VERTRBIND_LISTE_C;
	int  m_Pos_VERTRBIND_INLAND;

	CWnd *m_pView;
	struct ZARTSWITZERLAND	*m_pBufZartswitzerland;
	struct ZARTIKEL			*m_pBufZartikel;   
	struct CARTICLELANG		*m_pBufCarticlelang;  
	struct CARTICLECODES	*m_pBufAssortment;	

	CRdAssortment			m_RD_ASSORTMENT;
	
	BOOL m_bInitialized;

	CRdDform	m_RD_DFORM_D;
	CRdDform	m_RD_DFORM_F;

	CFont* m_pConstantFont;
	CFont* m_pSmallFont;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
};

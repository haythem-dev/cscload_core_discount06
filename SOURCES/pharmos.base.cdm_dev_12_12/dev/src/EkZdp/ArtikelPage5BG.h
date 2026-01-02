#include "hPflegePage.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
#include <phxlib/RdDform.h>

#pragma once


// CArtikelPage5BG-Dialogfeld

class CArtikelPage5BG : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage5BG)

public:
	CArtikelPage5BG();
	virtual ~CArtikelPage5BG();

// Dialog Data
	//{{AFX_DATA(CArtikelPage4)
	enum { IDD = IDD_ARTIKEL_5BG };
	ChDlgEdit		m_ARTIKEL_NAME_BG;
	ChDlgEdit		m_EINHEIT_BG;
	ChDlgEdit		m_DARREICHFORM_BG;
	ChDlgEdit		m_ARTIKEL_NAME_EN;
	ChDlgEdit		m_EINHEIT_EN;
	ChDlgEdit		m_DARREICHFORM_EN;
	ChDlgEdit		m_ARTIKEL_LANGNAME_BG;
	ChDlgEdit		m_ARTIKEL_LANGNAME_EN;
	CStatic			m_ST_SPR_ZEIL1;
	CStatic			m_ST_SPR_ZEIL2;
	CStatic			m_ST_SPR_ZEIL3;
	CStatic			m_ST_SPR_ZEIL4;
	ChDlgEdit		m_KRANKENKASSENCODE;
	ChDlgEdit		m_RECHNUNGSRABATT;
	ChDlgEdit		m_NATURALRABATT;
	ChDlgEdit		m_GEPNA;
	ChDlgEdit		m_JAEHRL_RECHNUNGSRABATT;
	ChDlgEdit		m_JAEHRL_NATURALSRABATT;
	ChDlgEdit		m_KUNDENRABATTREDUKTION;
	ChDlgEdit		m_KRANKENKASSENERSTATTUNG;
	ChDlgEdit		m_GUTSCHRIFTSPREIS;
	ChDlgComboBox	m_ZENTRALLAGER;
	ChDlgComboBox	m_PREISGRUPPE;
	ChDlgButton		m_AUFKLEBER;
	ChDlgButton		m_LISTE5;
	ChDlgButton		m_NICHT_AN_DROG;
	ChDlgButton		m_NICHT_AN_GH;
	ChDlgButton		m_EXPENSIVE;
	ChDlgEdit		m_KRANKENKASSENKOMPENSATION;
	ChDlgEdit		m_FREIVERKAUFKOMPENSATION;
	ChDlgEdit		m_SKONTO_HERSTELLER;
	ChDlgEdit		m_YEARLY_BONUS_PCT;
	ChDlgEdit		m_OTHER_REBATES_PCT;
	ChDlgEdit		m_GEPNANA;
	//}}AFX_DATA

public:
	void InitPflege( CWnd *pView  );
	void EnableFields( BOOL bEnable );
	void DisableSpecial();
	void ShowFields( );
	void SetDialog( BOOL bDialog = TRUE );
	void DataExchangeToBuffer( );
	void SetValidation( BOOL bValid );
	BOOL Validate( BOOL bMeldung );
	BOOL EndValidate( int *ind, BOOL bMeldung );
	void ActivateField( int nr );
	void SetMSStandard( BOOL bStandard );
	BOOL ShowDform_BG( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheDform_BG();
	void CalcGepna();
	void CalcGepnana();
	BOOL ShowDform_EN( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheDform_EN();
	void ResetVkn( );
	void Set_Artikel_Name( );

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
	int  m_Pos_PREISGRUPPE;

	CWnd *m_pView;
	struct ZARTBULGARIA		*m_pBufZartbulgaria;
	struct ZARTIKEL			*m_pBufZartikel;   
	struct CARTICLELANG		*m_pBufCarticlelang;   
	struct ZARTWG			*m_pBufKrankenkassencode;
	struct CARTICLECODES	*m_pBufMinistryProductCode;	

	BOOL m_bInitialized;

	CRdDform	m_RD_DFORM_BG;
	CRdDform	m_RD_DFORM_EN;

	CFont* m_pConstantFont;

	double m_GepnaVal;
	double m_GepnanaVal;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
};

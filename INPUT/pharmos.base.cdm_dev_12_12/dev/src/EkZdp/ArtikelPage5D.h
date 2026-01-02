#include "hPflegePage.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>

#include <phxlib/Rdcppeartcategory.h>
//#include <hDlgMultiComboBox.h>

#pragma once


// CArtikelPage5D-Dialogfeld

class CArtikelPage5D : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage5D)

public:
	CArtikelPage5D();
	virtual ~CArtikelPage5D();

// Dialog Data
	//{{AFX_DATA(CArtikelPage4)
	enum { IDD = IDD_ARTIKEL_5D };
	ChDlgButton		m_ISFESTB;
	ChDlgButton		m_AUTIDEM;
	ChDlgButton		m_ANBABSCHL;
	ChDlgButton		m_BSSICHG;
	ChDlgEdit		m_DATBSSICHG;
	ChDlgButton		m_ZULASS_GENER;
	ChDlgButton		m_ABSCHLAG_130;
	ChDlgButton		m_PREISEMPFEHLUNG;
	ChDlgButton		m_INDIKATOR;
	ChDlgButton		m_NIEDRIGSPANNE;
	ChDlgButton		m_ELAC;
	ChDlgButton		m_NATURALRABATT;
	ChDlgButton		m_PERF;
	ChDlgButton		m_LABORARTIKEL;
	ChDlgButton		m_SICHTWAHL;
	ChDlgButton		m_PRISMAEDISK;
	ChDlgEdit		m_PERSONALRABATT;
	ChDlgEdit		m_PRISMAEWOCHE;
	ChDlgEdit		m_ALC_STRENGTH;
	ChDlgEdit		m_VINTAGE;
	ChDlgComboBox	m_MVDAARTIKEL;
	ChDlgEdit		m_DATUM_LIEFERBAR_AB;
	ChDlgEdit		m_ZULASSUNGSNUMMER;
	ChDlgEdit		m_PPN;
	ChDlgEdit		m_ABSCHLAG_130A2;
	ChDlgButton		m_PILOT_SECURPH;
	ChDlgButton		m_AUSNAHME_52B;
	ChDlgButton		m_TREZEP;
	ChDlgComboBox   m_AMG47;
	ChDlgButton		m_AMG59;
	ChDlgButton		m_AMG_AUSNAHMEREG;
	ChDlgButton		m_ISHIART;
	ChDlgButton		m_CMI;
	ChDlgButton		m_ORPHANDRUG;
	ChDlgComboBox	m_AUSNAHMEABSCHLAGPFLICHT;
	ChDlgButton		m_BEDINGTEZULASSUNG;
	ChDlgEdit		m_ZULASSUNGSINHABERNR;
	ChDlgComboBox	m_AMNOGVERFAHREN;
	ChDlgEdit		m_OERTLICHERVERTRETERNR;
	ChDlgButton		m_ZULASSUNGAUSNAHMEFAELLE;
	ChDlgComboBox	m_AM_KINDER;
	ChDlgComboBox	m_AM_KRIT_WIRKSTOFF;
	ChDlgButton		m_ALTERSGERECHTE_DFORM;
	ChDlgButton		m_AUFGEHOBENER_FESTBETRAG;

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

	BOOL ShowPrismaEWoche( BOOL bShow, BOOL bMeldung = FALSE);
	void SuchePrismaEWoche();
	

	void ResetVkn( );

private:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive( );
	void InitDlgDaten( );
	void MakeDialog( );
	void FillComboBox();

private:
	// Dialogdaten

	ChDlg m_dlg;	

	int  m_Pos_ARTIKEL_BSSICHG;

	UINT m_nStatus;
	int  m_nMaxFields;

	CWnd *m_pView;
	struct ZARTIKEL			*m_pBufZartikel;
	struct CARTICLECODES	*m_pBufZulassungsnr;

	CRdCppeArtCategory m_RD_PPEARTCATEGORY;
	
	BOOL m_bInitialized;

	struct CARTICLEEXT	*m_pBufCarticleext;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	afx_msg void OnPbHiArticle();
	DECLARE_MESSAGE_MAP()
};

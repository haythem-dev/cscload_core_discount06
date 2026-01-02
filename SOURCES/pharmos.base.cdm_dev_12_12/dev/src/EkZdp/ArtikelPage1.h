#if !defined(AFX_ARTIKELPAGE1_H__BD2F47C1_7180_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ARTIKELPAGE1_H__BD2F47C1_7180_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtikelPage1.h : header file
//
#include "hPflegePage.h"
#include "ArticleCodesConverter.h"

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
//#include <hDlgMultiComboBox.h>
#include "CheckComboBox.h"

#include <phxlib/RdZartikel.h>
#include <phxlib/RdHerstel.h>
#include <phxlib/RdBliefer.h>
#include <phxlib/RdDform.h>
#include <phxlib/cmedicalactorselctrl.h>
#include <phxlib/rdmedicalactor.h>

//#include <voodoo_table_header/zartikel.h>

#include <phxlib/LsTaxtab.h>

/////////////////////////////////////////////////////////////////////////////
// CArtikelPage1 dialog

class CArtikelPage1 : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage1)

	friend class CArtikelPrices;

// Construction
public:
	CArtikelPage1();
	~CArtikelPage1();

// Dialog Data
	//{{AFX_DATA(CArtikelPage1)
	enum { IDD = IDD_ARTIKEL_1 };
	ChDlgEdit		m_ARTIKEL_NR_HERST;
	ChDlgEdit		m_HERST_PROZENT;
	ChDlgButton		m_ARTIKEL_GESPERRT;
	ChDlgButton		m_RETOURENSPERRE;
	ChDlgComboBox	m_SONDERGROSSO;
	ChDlgComboBox	m_PREISTYP;
	ChDlgComboBox	m_TFG;
	ChDlgEdit		m_FESTBREGEL;
	ChDlgEdit		m_FESTBSTUFE;
	ChDlgEdit		m_AWL2;
	ChDlgEdit		m_AWL1;
	ChDlgComboBox	m_AWL_AKTIV;
	ChDlgButton		m_ERSATZ_NR_AKTIV;
	ChDlgEdit		m_FESTBETRAG2;
	ChDlgEdit		m_FESTBETRAG1;
	ChDlgEdit		m_DATUM_FESTBETRAG2;
	ChDlgEdit		m_DATUM_FESTBETRAG1;
	ChDlgComboBox	m_MWST4;
	ChDlgComboBox	m_MWST3;
	ChDlgComboBox	m_MWST2;
	ChDlgComboBox	m_MWST1;
	ChDlgComboBox	m_DISC_DED_YET1;
	ChDlgComboBox	m_DISC_DED_YET2;
	ChDlgComboBox	m_DISC_DED_YET3;
	ChDlgComboBox	m_DISC_DED_YET4;
	ChDlgEdit		m_GUELAB1;
	ChDlgEdit		m_GUELAB2;
	ChDlgEdit		m_GUELAB3;
	ChDlgEdit		m_GUELAB4;
	ChDlgEdit		m_GROSSO1;
	ChDlgEdit		m_GROSSO2;
	ChDlgEdit		m_GROSSO3;
	ChDlgEdit		m_GROSSO4;
	ChDlgEdit		m_ArtikelPreis2_1;
	ChDlgEdit		m_ArtikelPreis2_2;
	ChDlgEdit		m_ArtikelPreis2_3;
	ChDlgEdit		m_ArtikelPreis2_4;
	ChDlgEdit		m_AVP1;
	ChDlgEdit		m_AVP2;
	ChDlgEdit		m_AVP3;
	ChDlgEdit		m_AVP4;
	ChDlgEdit		m_EAVP1;
	ChDlgEdit		m_EAVP2;
	ChDlgEdit		m_EAVP3;
	ChDlgEdit		m_EAVP4;
	ChDlgEdit		m_MAXAVP1;
	ChDlgEdit		m_MAXAVP2;
	ChDlgEdit		m_MAXAVP3;
	ChDlgEdit		m_MAXAVP4;
	ChDlgEdit		m_HPROZ1;
	ChDlgEdit		m_HPROZ2;
	ChDlgEdit		m_HPROZ3;
	ChDlgEdit		m_HPROZ4;
	ChDlgComboBox	m_PRICEMODEL1;
	ChDlgComboBox	m_PRICEMODEL2;
	ChDlgComboBox	m_PRICEMODEL3;
	ChDlgComboBox	m_PRICEMODEL4;
	ChDlgEdit		m_ZUZAHLUNG_IFA;
	ChDlgComboBox	m_RABATTFAEHIG;
	ChDlgButton		m_TAXPRUEFGROSSO;
	ChDlgButton		m_SOMMER_KK;
	ChDlgButton		m_PREIS0ARTIKEL;
	ChDlgEdit		m_ARTIKEL_NAME;
	ChDlgEdit		m_EINHEIT;
	ChDlgEdit		m_DARREICHFORM;
	ChDlgEdit		m_BTM_FAKTOR;
	ChDlgEdit		m_ARTIKEL_LANGNAME;
	ChDlgEdit		m_ERSATZ_NR;
	ChDlgEdit		m_ERSATZ_CODE;
	ChDlgEdit		m_HERSTELLER_NR;
	ChDlgEdit		m_LAUFZEITMONATE;
	ChDlgEdit		m_WARNTAGEVORVERF;
	ChDlgComboBox	m_TAXPFL;		// Taxe OTCX_RX
	ChDlgButton		m_REZEPTPFL;
	ChDlgButton		m_APOTHEKENPFL;
	ChDlgButton		m_NETTOARTIKEL;
	ChDlgButton		m_BTM;
	ChDlgButton		m_TIERARZNEI;
	ChDlgButton		m_NICHTUEBERGH;
	ChDlgButton		m_NURKVA;
	ChDlgButton		m_KLINIKPACK;
	ChDlgButton		m_VERTRBIND_IFA;
	ChDlgComboBox	m_KUEHLARTIKEL;
	ChDlgComboBox	m_VERTRBIND;
	ChDlgComboBox	m_MEDCANGES;
	ChDlgComboBox	m_VERFALL;
	ChDlgEdit		m_DATUM_AH;
	ChDlgEdit		m_DATUM_RR;
	ChDlgEdit		m_DATUM_AV;
	ChDlgButton		m_PB_SEKBEZ;
	ChDlgButton		m_PB_PRICES;
	ChDlgEdit		m_EAN_NR;
	ChDlgButton     m_EAN_NICHT_VORHANDEN;
	ChDlgButton		m_SKONTOFAEHIG;
	ChDlgEdit		m_GTIN;
	ChDlgEdit		m_NTIN;
	ChDlgEdit		m_MEDACTOR_F0;
	ChDlgEdit		m_MEDACTOR_F1;
	ChDlgEdit		m_MEDACTOR_F2;
	ChDlgEdit		m_MEDACTOR_F3;
	CCheckComboBox	m_MEDACTOR_0;
	CCheckComboBox	m_MEDACTOR_1;
	CCheckComboBox	m_MEDACTOR_2;
	CCheckComboBox	m_MEDACTOR_3;
	//}}AFX_DATA

	ChDlgEdit* m_MEDACTORS[4];

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CArtikelPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitPflege( CWnd *pView  );
	void EnableFields( BOOL bEnable );
	void DisableSpecial();
	void Enable_AVP_Croatia( );
	void ShowFields( );
	void SetDialog( BOOL bDialog = TRUE );
	void DataExchangeToBuffer( );
	void SetValidation( BOOL bValid );
	BOOL Validate( BOOL bMeldung );
	BOOL EndValidate( int *ind, BOOL bMeldung );
	void ActivateField( int nr );
	void SetMSStandard( BOOL bStandard );
	BOOL SetArticleNoEditCtrl( CString& cErrmld );
	void SetArticleCodeEditCtrl();

	BOOL ShowKettArtikel( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowHersteller( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowDform( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowAwl1( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowAwl1_Fr( BOOL bShow, BOOL bMeldung = FALSE );
	BOOL ShowMedicalActor_OneToOne(int i, BOOL bShow, BOOL bMeldung = FALSE);

	void ZeigePharmosSekbez( );
	void ZeigePrices( );
	void ZeigeLangname( );
	void ZeigeTiermedizinBezeichnung();

	void SucheKettArtikel();
	void SucheHersteller();
	void SucheAwl1();
	void SucheAwl1_Fr();
	void SucheAwl2();
	void SucheDform();
	void SearchMedicalActor_OneToOne(int i);

	void ResetVkn( );

	void LesePharmosSekbez( );
	BOOL Test_Set_ZZ( int mode );
	void Set_RetourenSperre( );
	void Set_Taxe_AEP( int nr );
	void Set_Taxe_AVP( int nr );
	void Set_Grosso_From_LBP ( int nr );
	void Set_Abzug_130 ( int nr );
	void Set_DefaultPreisDatum( int nr );
	void Set_Herst_Prozent( );
	void Set_Single_VAT_Rate( int nr );
	CString Set_Langname_Fr( );
	BOOL TestPreisDatum( int nr );
	void Set_Taxpfl( );
	void Set_Skontofaehig( );
	void Set_Rezeptpfl( );
	void SetArtikelname_Frz( );
	void Set_Elektroschrott( );
	void Set_AWL_aktiv( );

	void CalculatePercent( int nr );
	double CalculateBtm_Faktor( );

	void ChangeBtm_Faktor( );
	void ChangeArtikelName( );
	void ChangeArtikelName_D( );
	void ChangeArtikelName_A( );
	void ChangeArtikelName_CH( );
	void ChangeArtikelName_F( );
	void ChangeArtikelName_HR( );
	void ChangeArtikelName_Rest( );
	void SetChargenartikel_D();

	void NextDlgCtrl();   // wegen der pushbuttons

	bool AenderungsHinweis( CString &cMeld );

	void Translation();

	char m_ERSATZ_ARTCODE[L_CARTICLECODES_ARTICLE_CODE + 1];

private:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive( );
	void InitDlgDaten( );
	void MakeDialog( );
	void FillComboBox();
	void FillCoolLevels();
	void ReadMedicalActor();
	void FillMedicalActor_OneToN();
	void SetMedicalActor_OneToN();
	void SetMedicalActor_OneToOne();
	void StoreMedicalActor_OneToN();
	void StoreMedicalActor_OneToOne();

	char maskCoolLevel[ 11 ];

	// Preispruefung
	BOOL Test_NichtTaxartikelGesperrt( int i, int *ind, CString &Meldung );
	BOOL Test_NichtTaxartikel( int i, int *ind, CString &Meldung );
	BOOL Test_Taxartikel( int i, int *ind, CString &Meldung );
	BOOL Test_PreisAufNull( int i, int *ind, CString &Meldung );
	BOOL Test_Preis( int i, int *ind, CString &cErrMeldung );
	BOOL Test_MaxAep_MaxAvp( int i, int *ind, CString &cErrMeldung );

	bool NeuGleichAlt( char neu, char alt );
	bool MWST_NeuGleichAlt( char neu, char alt );
	bool TAXE_NeuGleichAlt( char neu, char alt );  // OTCX_RX

	// Kettartikel
	BOOL IsKettArtikelGesperrt( );

	bool m_PricesOnPage1;

private:
	// Dialogdaten

	ChDlg m_dlg;	

	int  m_nMaxFields;
	int  m_Pos_TAXPFL;
	int  m_Pos_ERSATZ_NR;
	int  m_Pos_DATUM_AH;
	int  m_Pos_REZEPTPFL;
	int	 m_Pos_NICHTUEBERGH;
	int	 m_Pos_ARTIKEL_GESPERRT;
	int	 m_Pos_RABATTFAEHIG;
	int  m_Pos_AWL_AKTIV;
	int  m_Pos_SKONTOFAEHIG;
	int  m_Pos_ARTIKEL_NR_HERST;
	int  m_Pos_EINHEIT;
	int  m_Pos_HERST_PROZENT;

	int	 m_Pos_FirstPreisField;
	int	 m_Pos_LastPreisField;

	#define NUMBER_OF_PRICE_ON_PAGE1 4 
	#define NUMBER_OF_CODES 26

	int  m_Pos_PREIS[NUMBER_OF_PRICE_ON_PAGE1];	 
	BOOL m_bPreisEnabled[NUMBER_OF_PRICE_ON_PAGE1];	 
	std::vector<BOOL> isOldChecked;
	
	enum
	{ 
		OFFS_GUELAB = 0,
		OFFS_GROSSO = 1,
		OFFS_AEP    = 2,
		OFFS_AVP    = 3,
		OFFS_EAVP   = 4,
		OFFS_MAXAVP = 5,
		OFFS_DISC_DED_YET = 6,
		OFFS_MWST   = 7,
		OFFS_HPROZ  = 8 
	};

	UINT m_nStatus;

	CWnd *m_pView;
	struct PFL_ARTIKEL	*m_pBuf;
	struct ZARTIKEL		*m_pBufZartikel;   
	struct EAN			*m_pBufEan;
	struct ZARTFEB2		*m_pBufZartfeb2;
	struct ZARTPREIS	*m_pBufArtpreis[ NUMBER_OF_PRICE_ON_PAGE1 ];
	struct CARTICLELANG *m_pBufCarticlelang;
	struct ZARTCROATIA	*m_pBufZartcroatia;
	struct ZARTWG		*m_pBufVertriebsClub;

	char MEDACTOR_F0[25] = {'\0'};
	char MEDACTOR_F1[25] = {'\0'};
	char MEDACTOR_F2[25] = {'\0'};
	char MEDACTOR_F3[25] = {'\0'};
	char* medactors[4] = {'\0'};

	struct PFL_ARTIKEL  *m_pBufOld;
	struct ZARTIKEL		*m_pBufOldZartikel; 
	struct ZARTPREIS	*m_pBufOldArtpreis[ NUMBER_OF_PRICE_ON_PAGE1 ];

	short m_sANRH_ZWING_EINZIG;
	char* m_gTIN;
	char* m_nTIN;
	// Taxtabelle
	CLsTaxtab *m_pTaxTb;

	// pointer to old ARTIKEL_GESPERRT
	char	*m_pOLD_ARTIKEL_GESPERRT ;

	BOOL m_bInitialized;

	CRdZartikel	m_RD_KETTARTIKEL;
	CRdHerstel	m_RD_HERSTELLER;
	CRdHerstel	m_RD_AWL1;
	CRdBliefer	m_RD_AWL1_FR;
	CRdDform	m_RD_DFORM;
	CRdMedicalactor	m_RD_MEDICALACTOR;

	enum { MAX_SEKBEZ = 10 };
	char m_NrSEKBEZ[2];
	char m_MaskSEKBEZ[MAX_SEKBEZ + 1];
	long m_OldArtikelnr;

	// Sekbez
	BOOL   m_bSekbezGelesen;
	int	   m_nNrOfSekbez;
	BOOL   ReadSekbez( );

	CFont* m_pConstantFont;

//	short m_nPREISTYP;

	int m_nAuswahlIndex;
	int m_nAuswahlIndex2;

//	afx_msg void OnCkArtikelTaxpfl(); // Taxe OTCX_RX
protected:
	// Generated message map functions
	//{{AFX_MSG(CArtikelPage1)
	afx_msg void OnPbArtikelSekbez();
	afx_msg void OnPbArtikelPrices();
	afx_msg void OnCkArtikelNettoartikel();
	afx_msg void OnCkArtikelRezeptpfl();
	afx_msg void OnCkArtikelApothekenpfl();
	afx_msg void OnCkArtikelNurkva();
	afx_msg void OnCkArtikelNichtuebergh();
	afx_msg void OnCkArtikelBtm();
	afx_msg void OnCkArtikelTierarznei();
	afx_msg void OnSelchangeCbArtikelTfg();
	afx_msg void OnCkEanNichtVorhanden();
	afx_msg void OnSelchangeCkArtikelTaxpfl();
	afx_msg void OnSelchangeCbArtikelMwst1();
	afx_msg void OnSelchangeCbArtikelVerfall();
	afx_msg void OnSelchangeCbArtikelPreistyp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTIKELPAGE1_H__BD2F47C1_7180_11D1_92F8_0060973B18D8__INCLUDED_)

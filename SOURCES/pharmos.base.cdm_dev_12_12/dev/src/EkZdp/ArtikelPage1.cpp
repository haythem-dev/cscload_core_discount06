// ArtikelPage1.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtikelPage1.h"
#include "ArtikelView.h"  // wegen SetHeaderInfo()

#include "hSelectDialog.h"
#include <phxlib/DformSelCtrl.h>
#include <phxlib/BlieferSelCtrl.h>
#include <phxlib/HerstelSelCtrl.h>
#include <phxlib/ZartikelSelCtrl.h>
#include <phxlib/FetchSekbez.h>

#include "ArtikelSekbez.h"
#include "ArtikelPrices.h"

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskDbl.h>
#include <eklibs/hamfcs/hMskDblPos.h>

#include <hdatum/phodate.h>
#include <phxlib/PhxUtil.h>
#include <phxlib/EanTest.h>
#include <voodoo_table_header/clicompany.h>
#include <voodoo_table_header/ccoollevel.h>
#include <vector>

#include <libscsvoodoo/libscsvoodoo.h>

#include "FeldBreite.h"
#include "ServerDatum.h"
#include "StellerUpdate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtikelPage1 property page

IMPLEMENT_DYNCREATE(CArtikelPage1, CPropertyPageMultiLang)

CArtikelPage1::CArtikelPage1() 
: ChPflegePage(CArtikelPage1::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage1)
	//}}AFX_DATA_INIT

	m_OldArtikelnr = 0;
	m_bInitialized = FALSE;
//	m_nPREISTYP = 0;

	m_MEDACTORS[0] = &m_MEDACTOR_F0;
	m_MEDACTORS[1] = &m_MEDACTOR_F1;
	m_MEDACTORS[2] = &m_MEDACTOR_F2;
	m_MEDACTORS[3] = &m_MEDACTOR_F3;
	medactors[0] = MEDACTOR_F0;
	medactors[1] = MEDACTOR_F1;
	medactors[2] = MEDACTOR_F2;
	medactors[3] = MEDACTOR_F3;

	// mit dem neuen Preispflege- Subdialog sind grundsätzlich alle Preisfelder auf ArtikelPage1 disabled
	// m_bPreisEnabled[] aber unverändert lassen, da auf Preise in der Zukunft auch weiterhin etliche Checks auf Page1 durchgeführt werden!
	m_PricesOnPage1 = true;
}

CArtikelPage1::~CArtikelPage1()
{
}

void CArtikelPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage1)
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_NR_HERST, m_ARTIKEL_NR_HERST);
	DDX_Control(pDX, IDC_ED_ARTIKEL_HERST_PROZENT, m_HERST_PROZENT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ARTIKEL_GESPERRT, m_ARTIKEL_GESPERRT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_RETOURENSPERRE, m_RETOURENSPERRE);
	DDX_Control(pDX, IDC_CB_ARTIKEL_SONDERGROSSO, m_SONDERGROSSO);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PREISTYP, m_PREISTYP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_FESTBREGEL, m_FESTBREGEL);
	DDX_Control(pDX, IDC_ED_ARTIKEL_FESTBSTUFE, m_FESTBSTUFE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_AWL2, m_AWL2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_AWL1, m_AWL1);
	DDX_Control(pDX, IDC_CB_ARTIKEL_AWL_AKTIV, m_AWL_AKTIV);
	DDX_Control(pDX, IDC_CK_ARTIKEL_ERSATZ_NR_AKTIV, m_ERSATZ_NR_AKTIV);
	DDX_Control(pDX, IDC_ED_ARTIKEL_FESTBETRAG2, m_FESTBETRAG2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_FESTBETRAG1, m_FESTBETRAG1);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_FESTBETRAG2, m_DATUM_FESTBETRAG2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_FESTBETRAG1, m_DATUM_FESTBETRAG1);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GUELAB1, m_GUELAB1);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GUELAB2, m_GUELAB2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GUELAB3, m_GUELAB3);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GUELAB4, m_GUELAB4);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GROSSO1, m_GROSSO1);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GROSSO2, m_GROSSO2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GROSSO3, m_GROSSO3);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GROSSO4, m_GROSSO4);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PREIS2_1, m_ArtikelPreis2_1); // default AEP
	DDX_Control(pDX, IDC_ED_ARTIKEL_PREIS2_2, m_ArtikelPreis2_2); // default AEP
	DDX_Control(pDX, IDC_ED_ARTIKEL_PREIS2_3, m_ArtikelPreis2_3); // default AEP
	DDX_Control(pDX, IDC_ED_ARTIKEL_PREIS2_4, m_ArtikelPreis2_4); // default AEP
	DDX_Control(pDX, IDC_ED_ARTIKEL_AVP1, m_AVP1);
	DDX_Control(pDX, IDC_ED_ARTIKEL_AVP2, m_AVP2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_AVP3, m_AVP3);
	DDX_Control(pDX, IDC_ED_ARTIKEL_AVP4, m_AVP4);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EAVP1, m_EAVP1);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EAVP2, m_EAVP2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EAVP3, m_EAVP3);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EAVP4, m_EAVP4);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MAXAVP1, m_MAXAVP1);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MAXAVP2, m_MAXAVP2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MAXAVP3, m_MAXAVP3);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MAXAVP4, m_MAXAVP4);
	DDX_Control(pDX, IDC_CB_ARTIKEL_DISC_DED_YET1, m_DISC_DED_YET1);
	DDX_Control(pDX, IDC_CB_ARTIKEL_DISC_DED_YET2, m_DISC_DED_YET2);
	DDX_Control(pDX, IDC_CB_ARTIKEL_DISC_DED_YET3, m_DISC_DED_YET3);
	DDX_Control(pDX, IDC_CB_ARTIKEL_DISC_DED_YET4, m_DISC_DED_YET4);
	DDX_Control(pDX, IDC_CB_ARTIKEL_MWST1, m_MWST1);
	DDX_Control(pDX, IDC_CB_ARTIKEL_MWST2, m_MWST2);
	DDX_Control(pDX, IDC_CB_ARTIKEL_MWST3, m_MWST3);
	DDX_Control(pDX, IDC_CB_ARTIKEL_MWST4, m_MWST4);
	DDX_Control(pDX, IDC_ED_ARTIKEL_HPROZ1, m_HPROZ1);
	DDX_Control(pDX, IDC_ED_ARTIKEL_HPROZ2, m_HPROZ2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_HPROZ3, m_HPROZ3);
	DDX_Control(pDX, IDC_ED_ARTIKEL_HPROZ4, m_HPROZ4);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PRICEMODEL1, m_PRICEMODEL1);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PRICEMODEL2, m_PRICEMODEL2);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PRICEMODEL3, m_PRICEMODEL3);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PRICEMODEL4, m_PRICEMODEL4);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ZUZAHLUNG_IFA, m_ZUZAHLUNG_IFA);
	DDX_Control(pDX, IDC_CB_ARTIKEL_RABATTFAEHIG, m_RABATTFAEHIG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_TAXPRUEFGROSSO, m_TAXPRUEFGROSSO);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SOMMER_KK, m_SOMMER_KK);
	DDX_Control(pDX, IDC_CK_ARTIKEL_PREIS0ARTIKEL, m_PREIS0ARTIKEL);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_NAME, m_ARTIKEL_NAME);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EINHEIT,	  m_EINHEIT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DARREICHFORM, m_DARREICHFORM);
	DDX_Control(pDX, IDC_ED_ARTIKEL_BTM_FAKTOR, m_BTM_FAKTOR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_LANGNAME, m_ARTIKEL_LANGNAME);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ERSATZ_NR,	  m_ERSATZ_NR );
	DDX_Control(pDX, IDC_ED_ARTIKEL_ERSATZ_CODE,  m_ERSATZ_CODE );
	DDX_Control(pDX, IDC_ED_ARTIKEL_HERSTELLER_NR , m_HERSTELLER_NR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_LAUFZEITMONATE, m_LAUFZEITMONATE );
	DDX_Control(pDX, IDC_ED_ARTIKEL_WARNTAGEVORVERF, m_WARNTAGEVORVERF );
	DDX_Control(pDX, IDC_CK_ARTIKEL_TAXPFL,       m_TAXPFL );
	DDX_Control(pDX, IDC_CK_ARTIKEL_REZEPTPFL,    m_REZEPTPFL );
	DDX_Control(pDX, IDC_CK_ARTIKEL_APOTHEKENPFL, m_APOTHEKENPFL );
	DDX_Control(pDX, IDC_CK_ARTIKEL_NETTOARTIKEL, m_NETTOARTIKEL );
	DDX_Control(pDX, IDC_CK_ARTIKEL_BTM,		  m_BTM );
	DDX_Control(pDX, IDC_CK_ARTIKEL_TIERARZNEI,   m_TIERARZNEI );
	DDX_Control(pDX, IDC_CK_ARTIKEL_NICHTUEBERGH, m_NICHTUEBERGH );
	DDX_Control(pDX, IDC_CK_ARTIKEL_NURKVA,       m_NURKVA );
	DDX_Control(pDX, IDC_CK_ARTIKEL_KLINIKPACK,   m_KLINIKPACK );
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_IFA,m_VERTRBIND_IFA );
	DDX_Control(pDX, IDC_CB_ARTIKEL_KUEHLARTIKEL, m_KUEHLARTIKEL );
	DDX_Control(pDX, IDC_CB_ARTIKEL_VERTRBIND,	  m_VERTRBIND );
	DDX_Control(pDX, IDC_CB_ARTIKEL_MEDCANGES,	  m_MEDCANGES );
	DDX_Control(pDX, IDC_CB_ARTIKEL_VERFALL,      m_VERFALL );
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_AH,     m_DATUM_AH );
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_RR,     m_DATUM_RR );
	DDX_Control(pDX, IDC_ED_ARTIKEL_DATUM_AV,     m_DATUM_AV );
	DDX_Control(pDX, IDC_PB_ARTIKEL_SEKBEZ, m_PB_SEKBEZ);
	DDX_Control(pDX, IDC_PB_ARTIKEL_PRICES, m_PB_PRICES);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EAN_NR, m_EAN_NR);
	DDX_Control(pDX, IDC_CK_ARTIKEL_EAN_NICHT_VORHANDEN, m_EAN_NICHT_VORHANDEN);
	DDX_Control(pDX, IDC_CK_ARTIKEL_SKONTOFAEHIG, m_SKONTOFAEHIG);
	DDX_Control(pDX, IDC_CB_ARTIKEL_TFG, m_TFG);
	DDX_Control(pDX, IDC_ED_ARTIKEL_NTIN, m_NTIN);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GTIN, m_GTIN);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MEDACTOR_F0, m_MEDACTOR_F0);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MEDACTOR_F1, m_MEDACTOR_F1);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MEDACTOR_F2, m_MEDACTOR_F2);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MEDACTOR_F3, m_MEDACTOR_F3);
	DDX_Control(pDX, IDC_CO_ARTIKEL_MEDACTOR_0, m_MEDACTOR_0);
	DDX_Control(pDX, IDC_CO_ARTIKEL_MEDACTOR_1, m_MEDACTOR_1);
	DDX_Control(pDX, IDC_CO_ARTIKEL_MEDACTOR_2, m_MEDACTOR_2);
	DDX_Control(pDX, IDC_CO_ARTIKEL_MEDACTOR_3, m_MEDACTOR_3);
	//}}AFX_DATA_MAP
	
	int medActorParam = ((CEkZdpApp*)AfxGetApp())->GetMedActorParameter();
	if (medActorParam == MedActor_Parameter::NotSet)
	{
		GetDlgItem(IDC_ST_ARTIKEL_MEDACTOR_0)->ShowWindow(false);
		GetDlgItem(IDC_ST_ARTIKEL_MEDACTOR_1)->ShowWindow(false);
		GetDlgItem(IDC_ST_ARTIKEL_MEDACTOR_2)->ShowWindow(false);
		GetDlgItem(IDC_ST_ARTIKEL_MEDACTOR_3)->ShowWindow(false);

	}	
	if (medActorParam != MedActor_Parameter::OneToOne)
	{
		m_MEDACTOR_F0.ShowWindow(false);
		m_MEDACTOR_F1.ShowWindow(false);
		m_MEDACTOR_F2.ShowWindow(false);
		m_MEDACTOR_F3.ShowWindow(false);
		GetDlgItem(IDC_ST_ARTIKEL_MEDACTOR_F0)->ShowWindow(false);
		GetDlgItem(IDC_ST_ARTIKEL_MEDACTOR_F1)->ShowWindow(false);
		GetDlgItem(IDC_ST_ARTIKEL_MEDACTOR_F2)->ShowWindow(false);
		GetDlgItem(IDC_ST_ARTIKEL_MEDACTOR_F3)->ShowWindow(false);
		GetDlgItem(IDC_ST_ART_MEDACTOR_F0_QUESTION)->ShowWindow(false);
		GetDlgItem(IDC_ST_ART_MEDACTOR_F1_QUESTION)->ShowWindow(false);
		GetDlgItem(IDC_ST_ART_MEDACTOR_F2_QUESTION)->ShowWindow(false);
		GetDlgItem(IDC_ST_ART_MEDACTOR_F3_QUESTION)->ShowWindow(false);
	}	
	if (medActorParam != MedActor_Parameter::OneToN)
	{
		m_MEDACTOR_0.ShowWindow(false);
		m_MEDACTOR_1.ShowWindow(false);
		m_MEDACTOR_2.ShowWindow(false);
		m_MEDACTOR_3.ShowWindow(false);
	}
}

//	ON_BN_CLICKED(IDC_CK_ARTIKEL_TAXPFL, OnCkArtikelTaxpfl) // Taxe OTCX_RX
BEGIN_MESSAGE_MAP(CArtikelPage1, CPropertyPageMultiLang)
	//{{AFX_MSG_MAP(CArtikelPage1)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_SEKBEZ, OnPbArtikelSekbez)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_PRICES, OnPbArtikelPrices)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_NETTOARTIKEL, OnCkArtikelNettoartikel)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_REZEPTPFL, OnCkArtikelRezeptpfl)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_APOTHEKENPFL, OnCkArtikelApothekenpfl)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_NURKVA, OnCkArtikelNurkva)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_NICHTUEBERGH, OnCkArtikelNichtuebergh)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_BTM, OnCkArtikelBtm)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_TIERARZNEI, OnCkArtikelTierarznei)
	ON_BN_CLICKED(IDC_CK_ARTIKEL_EAN_NICHT_VORHANDEN, OnCkEanNichtVorhanden)
	ON_CBN_SELCHANGE(IDC_CK_ARTIKEL_TAXPFL, OnSelchangeCkArtikelTaxpfl)
	ON_CBN_SELCHANGE(IDC_CB_ARTIKEL_MWST1, OnSelchangeCbArtikelMwst1)
	ON_CBN_SELCHANGE(IDC_CB_ARTIKEL_VERFALL, OnSelchangeCbArtikelVerfall)
	ON_CBN_SELCHANGE(IDC_CB_ARTIKEL_PREISTYP, OnSelchangeCbArtikelPreistyp)
	ON_CBN_SELCHANGE(IDC_CB_ARTIKEL_TFG, OnSelchangeCbArtikelTfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage1::MakeDialog()
{
	m_dlg.InitDialog( m_ARTIKEL_NAME );

	m_Pos_EINHEIT = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_EINHEIT );

//	m_Pos_DARREICHFORM = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_DARREICHFORM );
	m_dlg.InitDialog( m_BTM_FAKTOR );
	m_dlg.InitDialog( m_ARTIKEL_LANGNAME );

	m_dlg.InitDialog( m_PB_SEKBEZ );
	m_dlg.InitDialog( m_PB_PRICES );
	//m_PB_PRICES.ShowWindow(!m_PricesOnPage1);
		
	m_dlg.InitDialog( m_EAN_NICHT_VORHANDEN );
	m_dlg.InitDialog( m_EAN_NR );

	m_Pos_ERSATZ_NR = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ERSATZ_NR );
	m_dlg.InitDialog( m_ERSATZ_CODE );

	m_dlg.InitDialog( m_ERSATZ_NR_AKTIV);
	m_dlg.InitDialog( m_HERSTELLER_NR );

	m_Pos_ARTIKEL_NR_HERST = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ARTIKEL_NR_HERST );

	m_dlg.InitDialog( m_LAUFZEITMONATE );
	m_dlg.InitDialog( m_WARNTAGEVORVERF );

	m_dlg.InitDialog( m_TAXPRUEFGROSSO  );
	m_dlg.InitDialog( m_SONDERGROSSO );
	m_dlg.InitDialog( m_PREISTYP );

	m_Pos_TAXPFL = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_TAXPFL  );

	m_dlg.InitDialog( m_PREIS0ARTIKEL  );

	m_Pos_REZEPTPFL = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_REZEPTPFL  );
	m_dlg.InitDialog( m_APOTHEKENPFL  );
	m_dlg.InitDialog( m_NETTOARTIKEL );
	m_dlg.InitDialog( m_BTM );
	m_dlg.InitDialog(m_TFG);
	m_dlg.InitDialog( m_TIERARZNEI );

	m_Pos_NICHTUEBERGH = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_NICHTUEBERGH );
	m_dlg.InitDialog( m_NURKVA );
	m_dlg.InitDialog( m_KLINIKPACK );
	m_dlg.InitDialog( m_SOMMER_KK );

	m_dlg.InitDialog( m_KUEHLARTIKEL );

	m_dlg.InitDialog( m_VERTRBIND_IFA );
	m_dlg.InitDialog( m_VERTRBIND );
	m_dlg.InitDialog( m_MEDCANGES );
	m_dlg.InitDialog( m_VERFALL   );

	m_Pos_RABATTFAEHIG = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_RABATTFAEHIG );

	m_Pos_DATUM_AH = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_DATUM_AH );
	m_dlg.InitDialog( m_DATUM_RR );

	m_dlg.InitDialog( m_DATUM_AV );

	m_dlg.InitDialog( m_ZUZAHLUNG_IFA );

	// Preise : in dieser Reihenfolge !!!!!!
	m_Pos_PREIS[0]  = m_dlg.GetFieldNumber();
	m_Pos_FirstPreisField = m_Pos_PREIS[0];
	m_dlg.InitDialog( m_GUELAB1 );
	m_dlg.InitDialog( m_GROSSO1 );
	m_dlg.InitDialog( m_ArtikelPreis2_1 ); // default AEP
	m_dlg.InitDialog( m_AVP1 );
	m_dlg.InitDialog( m_EAVP1 );
	m_dlg.InitDialog( m_MAXAVP1 );
	m_dlg.InitDialog( m_DISC_DED_YET1 );
	m_dlg.InitDialog( m_MWST1 );
	m_dlg.InitDialog( m_HPROZ1 );
	m_dlg.InitDialog( m_PRICEMODEL1 );

	m_Pos_PREIS[1]  = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_GUELAB2 );
	m_dlg.InitDialog( m_GROSSO2 );
	m_dlg.InitDialog(m_ArtikelPreis2_2 ); // default AEP
	m_dlg.InitDialog( m_AVP2 );
	m_dlg.InitDialog( m_EAVP2 );
	m_dlg.InitDialog( m_MAXAVP2 );
	m_dlg.InitDialog( m_DISC_DED_YET2 );
	m_dlg.InitDialog( m_MWST2 );
	m_dlg.InitDialog( m_HPROZ2 );
	m_dlg.InitDialog( m_PRICEMODEL2 );

	m_Pos_PREIS[2]  = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_GUELAB3 );
	m_dlg.InitDialog( m_GROSSO3 );
	m_dlg.InitDialog(m_ArtikelPreis2_3 ); // default AEP
	m_dlg.InitDialog( m_AVP3 );
	m_dlg.InitDialog( m_EAVP3 );
	m_dlg.InitDialog( m_MAXAVP3 );
	m_dlg.InitDialog( m_DISC_DED_YET3 );
	m_dlg.InitDialog( m_MWST3 );
	m_dlg.InitDialog( m_HPROZ3 );
	m_dlg.InitDialog( m_PRICEMODEL3 );

	m_Pos_PREIS[3]  = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_GUELAB4 );
	m_dlg.InitDialog( m_GROSSO4 );
	m_dlg.InitDialog(m_ArtikelPreis2_4 ); // default AEP
	m_dlg.InitDialog( m_AVP4 );
	m_dlg.InitDialog( m_EAVP4 );
	m_dlg.InitDialog( m_MAXAVP4 );
	m_dlg.InitDialog( m_DISC_DED_YET4 );
	m_dlg.InitDialog( m_MWST4 );
	m_Pos_LastPreisField = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_HPROZ4 );
	m_dlg.InitDialog( m_PRICEMODEL4 );

	m_Pos_HERST_PROZENT = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_HERST_PROZENT );

	m_dlg.InitDialog( m_FESTBETRAG2 );
	m_dlg.InitDialog( m_FESTBETRAG1 );
	m_dlg.InitDialog( m_DATUM_FESTBETRAG2 );
	m_dlg.InitDialog( m_DATUM_FESTBETRAG1 );
	m_dlg.InitDialog( m_FESTBREGEL );
	m_dlg.InitDialog( m_FESTBSTUFE );

	m_dlg.InitDialog( m_AWL2 );
	m_dlg.InitDialog( m_AWL1 );

	m_Pos_AWL_AKTIV = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_AWL_AKTIV );

	m_Pos_SKONTOFAEHIG = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_SKONTOFAEHIG );

	m_dlg.InitDialog( m_RETOURENSPERRE );

	m_Pos_ARTIKEL_GESPERRT = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ARTIKEL_GESPERRT );

	m_nMaxFields = m_dlg.GetFieldNumber();

	m_dlg.InitDialog( m_GTIN );
	m_dlg.InitDialog( m_NTIN );

	m_dlg.InitDialog(m_MEDACTOR_F0);
	m_dlg.InitDialog(m_MEDACTOR_F1);
	m_dlg.InitDialog(m_MEDACTOR_F2);
	m_dlg.InitDialog(m_MEDACTOR_F3);

	if (IsCountry("CH")) 
	{
		//if (IsAGP() == TRUE) // only to differentiate between prewhole and wholesale
		if (IsPrewhole() == FALSE)
		{
			// Beschriftung "AGP" statt "AEP"
			GetDlgItem(IDC_ARTIKEL_PREIS2)->SetWindowText(CResString::ex().getStrTblText(IDS_AGP));
		}
		// Beschriftung "LBP" statt "EAVP"
		GetDlgItem( IDC_EAVP_LBP )->SetWindowText( CResString::ex().getStrTblText(IDS_STRING1254) );
	}
	else if (IsCountry("F")) // Beschriftung "MaxAep" statt "EAVP"
	{
		GetDlgItem( IDC_EAVP_LBP )->SetWindowText( CResString::ex().getStrTblText(IDS_STRING1276) );
	}
	else if (IsCountry("D")) // Beschriftung "UVP" statt "EAVP"
	{
		GetDlgItem( IDC_EAVP_LBP )->SetWindowText( CResString::ex().getStrTblText(IDS_STRING1352) );
	}

	if (IsCountry("D")) // Beschriftung "Erstattbetrag" statt "maxAVP"
	{
		GetDlgItem( IDC_MAXAVP_ERSTATTB )->SetWindowText( CResString::ex().getStrTblText(IDS_STRING1325) );
	}
}

/////////////////////////////////////////////////////////////
//  Sekundaerbezeichnung PHARMOS

void CArtikelPage1::ZeigePharmosSekbez( )
{	
	GetDlgItem( IDC_ST_ARTIKEL_PHARMOS_SEKBEZ )->
				SetWindowText( m_pBuf->cPharmosSekbez );
}

void CArtikelPage1::ZeigeTiermedizinBezeichnung()
{
	static CString initialLabel = "";
	if (initialLabel.GetLength() == 0)
	{
		GetDlgItem(IDC_CK_ARTIKEL_TIERARZNEI)->GetWindowTextA(initialLabel);
	}
	CString currentLabel = initialLabel;
	if (strcmp(((CArtikelView*)m_pView)->m_Doc.GetIfaOartBuffer()->A02TIERAM, "02") == 0)
    {
	    currentLabel.Append(" (VMTP)");
	}
	GetDlgItem(IDC_CK_ARTIKEL_TIERARZNEI)->SetWindowText(currentLabel);
}

/////////////////////////////////////////////////////////////
//  Langname anzeigen (nach automatischer Generierung Frankreich)

void CArtikelPage1::ZeigeLangname( )
{	
	m_ARTIKEL_LANGNAME.p_SetInput();
}

/////////////////////////////////////////////
// Verknuepfungen Ruecksetzen

void CArtikelPage1::ResetVkn( )
{
	m_RD_DFORM.Reset();
	m_RD_KETTARTIKEL.Reset();
	m_RD_HERSTELLER.Reset();
	m_RD_AWL1.Reset();
	m_RD_AWL1_FR.Reset();
	m_RD_MEDICALACTOR.Reset();
}

/////////////////////////////////////////////////////////////
//  Verknuepfungen lesen

// DFORM

BOOL CArtikelPage1::ShowDform( BOOL , BOOL bMeldung)
{
	int iStat;
	CString Name;
	CString Errmld;
	iStat = m_RD_DFORM.IPlausi( m_pBufZartikel->DARREICHFORM, Name, &Errmld);
//	if ( bShow )	// neu
//		GetDlgItem( IDC_ST_ARTIKEL_DARREICHFORM )->SetWindowText( Name );
	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage1::SucheDform( )
{
	CDformSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_SEL_DAR), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufZartikel->DARREICHFORM ) == 0 )
		{

			m_DARREICHFORM.p_SetInput();
			m_DARREICHFORM.SetFocus();
/*
			m_dlg.ShowFields( m_Pos_DARREICHFORM );
			m_dlg.SetFocus( m_Pos_DARREICHFORM );
*/
//			ShowDform();
		}
	}
	m_SelBox.CloseCursor();
}

// Kettartikel

BOOL CArtikelPage1::IsKettArtikelGesperrt( )
{
	BOOL bOk;
	int  iStat;
	CString Name;
	CString Gesperrt;
	CString Errmld;
	// Kettartikel immer neu lesen 
	m_RD_KETTARTIKEL.Reset();
	iStat = m_RD_KETTARTIKEL.IPlausi( m_pBufZartikel->ERSATZ_NR, 
									  Name, Gesperrt, &Errmld);
	if ( iStat == 0 )
		bOk = Gesperrt.GetAt( 0 ) == '1';
	else
		bOk = FALSE;
	return bOk;
}

BOOL CArtikelPage1::ShowKettArtikel( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	// folgende Konstellation vermeiden: 
	// - Kettartikel wird gesetzt, ist aber noch nicht vorhanden
	// - Kettartikel wird neu angelegt
	// - Fehlermeldung kommt immer noch, weil m_lKey unveraendert und daher kein neues Lesen
	if (m_RD_KETTARTIKEL.ShowLastKey() == m_pBufZartikel->ARTIKEL_NR)
	{
		m_RD_KETTARTIKEL.Reset();
	}

	CString cErrmld;

	iStat = m_RD_KETTARTIKEL.IPlausi( m_pBufZartikel->ERSATZ_NR, Name, &Errmld);
	if ( bShow ){	// neu
		GetDlgItem( IDC_ST_ARTIKEL_ERSATZ_NR )->SetWindowText( Name );
		SetArticleCodeEditCtrl();
	}
	
	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage1::SetArticleCodeEditCtrl()
{
	CString no;
	CString code;
	CString cErrmld;
	m_ERSATZ_NR.GetWindowText(no);
	code = CArticleCodesConverter::getPreferredCodeByNo( atol(no), cErrmld );
	strcpy(m_ERSATZ_ARTCODE, code);
	m_ERSATZ_CODE.p_SetInput();
}

void CArtikelPage1::SucheKettArtikel( )
{
	CZartikelSelCtrl m_SelBox;
	m_SelBox.SetPflegeProgNeuheit( NH_NEUHEIT_PHARMOS );
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_AUSWAHL_EPZN), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	dlg.RestoreAuswahlIndex( m_nAuswahlIndex );
	dlg.RestoreAuswahlIndex2( m_nAuswahlIndex2 );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_pBufZartikel->ERSATZ_NR ) == 0 )
		{
			m_ERSATZ_NR.p_SetInput();
			ShowKettArtikel( TRUE );

			CArticleCodesConverter::setArticleCodeEditCtrl( m_SelBox, m_ERSATZ_ARTCODE );
			m_ERSATZ_CODE.p_SetInput();
			//m_ERSATZ_CODE.SetFocus();
		}
	}
	m_SelBox.CloseCursor();

	m_nAuswahlIndex = dlg.GetAuswahlIndex( );
	m_nAuswahlIndex2 = dlg.GetAuswahlIndex2( );
}

// Hersteller

BOOL CArtikelPage1::ShowHersteller( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	long KONSIG_PARTNER;
	CString cZentralppeList;
	short BUSINESSTYPENO;
	short VERTRIEBSCLUBNR;
	CString cVertriebsclub;
	iStat = m_RD_HERSTELLER.IPlausi( m_pBufZartikel->HERSTELLER_NR, Name, KONSIG_PARTNER, cZentralppeList,
									 BUSINESSTYPENO, m_sANRH_ZWING_EINZIG, VERTRIEBSCLUBNR, &Errmld);

	if (iStat == 1 && IsCountry("CH") && ((CArtikelView* )m_pView)->IsNeuanlage())
	{
		char nams[ L_CLICOMPANY_NAMS + 1 ] = {0};
		if (((CArtikelView* )m_pView)->m_Doc.GetClioart()->COMPNO > 0)
		{
			// Hersteller nicht gesetzt bzw. geändert --> Name zu LogIndex- Company aus clicompany anzeigen (cliart.compno --> clicompany.prtno --> clicompany.nams)
			CString sql;
			sql.Format( "select NAMS from CLICOMPANY where PRTNO=%ld", ((CArtikelView* )m_pView)->m_Doc.GetClioart()->COMPNO );	

			SqlRead( sql, nams, NULL );
			Name = nams;
		}
	}

	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_HERSTELLER_NR )->SetWindowText( Name );
/*
	if ( iStat > 1 && bMeldung ) AfxMessageBox( Errmld );
	return iStat <= 1;
*/
	// 0 nicht zulassen
	if ( iStat > 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	// Business-Typ immer aus Hersteller übernehmen (Neuanlage & Änderung)
	m_pBufZartikel->BUSINESSTYPENO = BUSINESSTYPENO;

	// Vertriebs-Club aus Hersteller übernehmen oder Wert löschen
	if (VERTRIEBSCLUBNR == 0)
		strncpy (m_pBufVertriebsClub->WARENGRUPPE, "     ", L_ZARTWG_WARENGRUPPE);
	else
	{
		cVertriebsclub.Format("%.5d", VERTRIEBSCLUBNR);
		strncpy (m_pBufVertriebsClub->WARENGRUPPE, cVertriebsclub, L_ZARTWG_WARENGRUPPE);
	}

	// 16.07.2003
	if ( ((CArtikelView* )m_pView)->IsNeuanlage() )
	{
		if (*m_pBufZartikel->ZENTRALPPELIST == '0') // Okt. 2013 --> Übernahme aus Hersteller nur, wenn Wert nicht vorher schon auf Page3 gesetzt wurde !
		{
			if ( iStat == 0 && !cZentralppeList.IsEmpty() )
				*m_pBufZartikel->ZENTRALPPELIST = cZentralppeList.GetAt( 0 );
		}

		if ( iStat == 0 && KONSIG_PARTNER > 0 )
			m_pBufZartikel->KONSIG_PARTNER_NR = KONSIG_PARTNER;
		else
			m_pBufZartikel->KONSIG_PARTNER_NR = 0; // CR-269: herstel.konsig_partner_nr --> zartikel.konsig_partner_nr
	}
	else
	{
		if ( iStat == 0 && !cZentralppeList.IsEmpty() ) 
		{
			if ( m_pBufZartikel->HERSTELLER_NR != m_pBufOldZartikel->HERSTELLER_NR && 
				 *m_pBufOldZartikel->ZENTRALPPELIST != '8' )
				*m_pBufZartikel->ZENTRALPPELIST = cZentralppeList.GetAt( 0 );
		}
	}
		
	return iStat == 0;
}


void CArtikelPage1::SucheHersteller( )
{
	CHerstelSelCtrl m_SelBox( IM_NUMBER_S );
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_SEL_HERST), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_pBufZartikel->HERSTELLER_NR ) == 0 )
		{
			m_HERSTELLER_NR.p_SetInput();
			m_HERSTELLER_NR.SetFocus();
			ShowHersteller( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// Ausweichlieferant = Hersteller

BOOL CArtikelPage1::ShowAwl1( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	CString PPE;

	iStat = m_RD_AWL1.IPlausi( m_pBufZartikel->AWL1, Name, PPE, &Errmld);
	if ( bShow )
	{
		if ( iStat == 0 )
		{
			if ( PPE.GetAt(0) == '1' )
				Name += CResString::ex().getStrTblText(IDS_STRING997);
		}
		else if (IsCountry("CH") && !IsPrewhole() && ((CArtikelView* )m_pView)->IsNeuanlage())
		{
			char nams[ L_CLICOMPANY_NAMS + 1 ] = {0};
			if (((CArtikelView* )m_pView)->m_Doc.GetClioart()->SUPPLNO > 0)
			{
				// AWL nicht gesetzt bzw. geändert --> Name zu LogIndex- Company aus clicompany anzeigen (cliart.supplno --> clicompany.prtno --> clicompany.nams)
				CString sql;
				sql.Format( "select NAMS from CLICOMPANY where PRTNO=%ld", ((CArtikelView* )m_pView)->m_Doc.GetClioart()->SUPPLNO );	

				SqlRead( sql, nams, NULL );
				Name = nams;
			}
		}
		GetDlgItem( IDC_ST_ARTIKEL_AWL1 )->SetWindowText( Name );
	}
	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage1::SucheAwl1( )
{
//	CBlieferSelCtrl m_SelBox;
	CHerstelSelCtrl m_SelBox( IM_NUMBER_S );
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_AUSWAHL_LIEF1), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_pBufZartikel->AWL1 ) == 0 )
		{
			m_AWL1.p_SetInput();
			m_AWL1.SetFocus();
			ShowAwl1( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

BOOL CArtikelPage1::ShowAwl1_Fr( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	iStat = m_RD_AWL1_FR.IPlausi( m_pBufZartikel->AWL1, Name, &Errmld);
	if ( bShow )
	{
		GetDlgItem( IDC_ST_ARTIKEL_AWL1 )->SetWindowText( Name );
	}

	// AWL1 soll in Frankreich Mussfeld sein
	if ( ( iStat > 1 || (iStat == 1 && IsCountry("F") && !IsPrewhole())) && bMeldung ) MsgBoxOK( Errmld );

	if (IsCountry("F") && !IsPrewhole())
	{
		return iStat <= 0;
	}

	return iStat <= 1;
}

void CArtikelPage1::SucheAwl1_Fr( )
{
	CBlieferSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_AUSWAHL_LIEF1), &m_SelBox,
						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_pBufZartikel->AWL1 ) == 0 )
		{
			m_AWL1.p_SetInput();
			m_AWL1.SetFocus();
			ShowAwl1_Fr( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

void CArtikelPage1::SucheAwl2( )
{
//	CBlieferSelCtrl m_SelBox;
	CHerstelSelCtrl m_SelBox( IM_NUMBER_S );
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_AUSWAHL_LIEF2), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_pBufZartikel->AWL2 ) == 0 )
		{
			m_AWL2.p_SetInput();
			m_AWL2.SetFocus();
//			ShowErstlieferant( TRUE );
//			ShowHersteller( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

BOOL CArtikelPage1::ShowMedicalActor_OneToOne(int i, BOOL bShow, BOOL bMeldung)
{
	int iStat;
	CString Name;
	CString Errmld;

	UINT ctrlIDs[] =
	{
		IDC_ST_ARTIKEL_MEDACTOR_F0,
		IDC_ST_ARTIKEL_MEDACTOR_F1,
		IDC_ST_ARTIKEL_MEDACTOR_F2,
		IDC_ST_ARTIKEL_MEDACTOR_F3
	};

	BOOL allValid = TRUE;

	Name.Empty();
	Errmld.Empty();
	iStat = m_RD_MEDICALACTOR.IPlausi(medactors[i], i, Name, &Errmld);

	if (bShow)
	{
		GetDlgItem(ctrlIDs[i])->SetWindowText(Name);
	}

	if (iStat > 1 && bMeldung)
	{
		allValid = FALSE;
		MsgBoxOK(Errmld);
	}

	return allValid;
}

void CArtikelPage1::SearchMedicalActor_OneToOne(int i)
{
	CCMedicalactorSelCtrl m_SelBox;
	m_SelBox.GetMedicalactor_type(i);

	ChSelectDialog dlg(CResString::ex().getStrTblText(IDS_SEL_MEDICALACTOR), &m_SelBox,
					   HCD_SCROLLINFO | HCD_BUTTONALTERN);

	if (dlg.DoModal() == IDOK)
	{
		if (m_SelBox.PrimeKeyOfSelectedRecord(medactors[i]) == 0)
		{
			m_MEDACTORS[i]->p_SetInput();
			m_MEDACTORS[i]->SetFocus();
			ShowMedicalActor_OneToOne(i, TRUE);
		}
	}
	m_SelBox.CloseCursor();
}

/////////////////////////////////////////////////////////////
//  Validierung

class CV_ARTIKEL_Name : public ChValBase
{
public:
	CV_ARTIKEL_Name( struct ZARTIKEL *pBuf, CArtikelView* pView ) 
		: ChValBase( pBuf, pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = (( struct ZARTIKEL*)m_pBuf)->ARTIKEL_NAME[0] != ' ';
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_NO_SPACE_BEGIN) );
		return bOk;
	}
	void PostProc( )
	{
		((CArtikelView*)m_pWnd)->SetHeaderInfo();
	}
};

class CV_ARTIKEL_Einheit : public ChValBase
{
public:
	CV_ARTIKEL_Einheit( CArtikelPage1* pView, CArtikelView* pView1 )
		: ChValBase( pView, pView1 ){};

	BOOL Validate( BOOL )
	{
		((CArtikelPage1*)m_pWnd)->ChangeBtm_Faktor();
		return true;
	}

	void PostProc( )
	{
		((CArtikelView*)m_pWnd1)->SetHeaderInfo();
	}
};

class CV_ARTIKEL_Dform : public ChValBase
{
public:
	CV_ARTIKEL_Dform( CArtikelPage1* pView, CArtikelView* pView1 )
		: ChValBase( pView, pView1 ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtikelPage1*)m_pWnd)->ShowDform( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtikelPage1*)m_pWnd)->SucheDform( );
	}
	void PostProc( )
	{
		((CArtikelView*)m_pWnd1)->SetHeaderInfo();
	}
};


class CV_ARTIKEL_KettArtikel : public ChValBase
{
public:
	CV_ARTIKEL_KettArtikel( struct ZARTIKEL *pBuf, CArtikelPage1* pView ) 
		: ChValBase( pBuf, pView ){};
	BOOL Validate( BOOL bMeldung )
	{
/*
		int n_ziff = TestPruefZiffer7 ( ((struct ZARTIKEL*)m_pBuf)->ERSATZ_NR );
		if ( n_ziff == 1 ) return TRUE;		// KettNr = 0
		if ( n_ziff == 0 )					// falsche Pruefziffer
		{
			if ( bMeldung )
				AfxMessageBox( _T(CResString::ex().getStrTblText(IDS_PZN_INCORRECT)) );
			return FALSE;
		}

		if ( (( struct ZARTIKEL*)m_pBuf)->ERSATZ_NR == 
			 (( struct ZARTIKEL*)m_pBuf)->ARTIKEL_NR			)
		{
			if ( bMeldung )
				AfxMessageBox( _T(CResString::ex().getStrTblText(IDS_DIFF_KETTART)) );
			return FALSE;
		}

		return ((CArtikelPage1*)m_pWnd)->ShowKettArtikel( bMeldung, bMeldung );
*/
		BOOL bOk;
		CString cErrmld;
		CArtikelPage1* parent = ((CArtikelPage1*)m_pWnd);
		
		if ( FALSE == parent->SetArticleNoEditCtrl( cErrmld ) ){
			return FALSE;
		}
		
		bOk = parent->ShowKettArtikel( bMeldung, bMeldung );

		if ( bOk )
		{
			if ( (( struct ZARTIKEL*)m_pBuf)->ERSATZ_NR == 
				 (( struct ZARTIKEL*)m_pBuf)->ARTIKEL_NR			)
			{
				if ( bMeldung )
					MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_DIFF_EPZN)) );
				bOk = FALSE;
			}
		}
		return bOk;

	}
	void NotifyProc( )
	{
		((CArtikelPage1*)m_pWnd)->SucheKettArtikel( );
	}
/*	void PostProc( )
	{
		CString cErrmld;
		CArtikelPage1* parent = ((CArtikelPage1*)m_pWnd);
		
		parent->SetArticleNoEditCtrl( cErrmld );
	}
*/
};

class CV_ARTIKEL_Festbregel : public ChValBase
{
public:
	CV_ARTIKEL_Festbregel( struct ZARTIKEL *pBuf ) 
		: ChValBase( pBuf ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		char* ze = (( struct ZARTIKEL*)m_pBuf)->FESTBREGEL;
		bOk = ( *ze == ' ' || *ze >= '0' && *ze <= '8' ) && 
		      ( strcmp( &ze[1], "  " ) == 0 );
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_FESTBREGEL) );
		return bOk;
	}
};


class CV_ARTIKEL_EanNr : public ChValBase
{
public:
	CV_ARTIKEL_EanNr( struct EAN *pBuf ) 
		: ChValBase( pBuf ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		int  i;
		char* ean = (( struct EAN*)m_pBuf)->EAN_NR;
		i = 0;
		while ( ean[i] && ean[i] == ' ' ) i++;
		bOk = ean[i] == '\0';
		if ( bOk ) return bOk;

		i = 0;
		while ( ean[i] &&  ean[i] == '0'  ) i++;
		bOk = ean[i] != '\0';
		if ( bOk )
		{
			i = 0;
			while ( ean[i] && ean[i] >= '0' && ean[i] <= '9' ) i++;
			bOk = ean[i] == '\0';
		}

		if ( !bOk )
		{
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_LEER_EAN) );
		}
		else
		{
			bOk = TestEan13PruefZiffer ( ean ) == 2;
			if ( !bOk )
			{
				if ( bMeldung )
				{
					CString s;
					i = GetEan13PruefZiffer ( ean );
					if ( i >= 0 )
						s.Format( CResString::ex().getStrTblText(IDS_CORRECT_NUMBER), i );
					else
						s = CResString::ex().getStrTblText(IDS_BAD_EAN);
					MsgBoxOK( s );
				}
			}
		}
		return bOk;
	}
};

class CV_ARTIKEL_Hersteller : public ChValBase
{
public:
	CV_ARTIKEL_Hersteller( CArtikelPage1* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtikelPage1*)m_pWnd)->ShowHersteller( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtikelPage1*)m_pWnd)->SucheHersteller( );
	}
	void PostProc( )
	{
		((CArtikelPage1*)m_pWnd)->Set_Elektroschrott( );
	}
};

class CV_ARTIKEL_Awl1 : public ChValBase
{
public:
	CV_ARTIKEL_Awl1( CArtikelPage1* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtikelPage1*)m_pWnd)->ShowAwl1( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtikelPage1*)m_pWnd)->SucheAwl1( );
	}
};

class CV_ARTIKEL_Awl1_Fr : public ChValBase
{
public:
	CV_ARTIKEL_Awl1_Fr( CArtikelPage1* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = ((CArtikelPage1*)m_pWnd)->ShowAwl1_Fr( bMeldung, bMeldung );

		((CArtikelPage1*)m_pWnd)->Set_AWL_aktiv( );

		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage1*)m_pWnd)->SucheAwl1_Fr( );
	}
};

class CV_ARTIKEL_Awl2 : public ChValBase
{
public:
	CV_ARTIKEL_Awl2( CArtikelPage1* pView ) : ChValBase( pView ){};
	void NotifyProc( )
	{
		((CArtikelPage1*)m_pWnd)->SucheAwl2( );
	}
};

class CV_ARTIKEL_MEDICALACTOR : public ChValBase
{
public:
	CV_ARTIKEL_MEDICALACTOR(CArtikelPage1* pView, int i) : ChValBase(pView), m_i(i) {};
	BOOL Validate(BOOL bMeldung)
	{
		BOOL bOk = ((CArtikelPage1*)m_pWnd)->ShowMedicalActor_OneToOne(m_i, bMeldung, bMeldung);
		return bOk;
	}
	void NotifyProc()
	{
		((CArtikelPage1*)m_pWnd)->SearchMedicalActor_OneToOne(m_i);
	}
private:
	int m_i;
};

// Datum-AH

void CArtikelPage1::Set_RetourenSperre( )
{
	// aendern nur wenn Char pressed (in Österreich aber immer)
	if ( !m_DATUM_AH.WasCharPressed( ) && !(IsCountry("A"))) return;

	// darf nur aufgerufen werden, wenn die Seite schonmal aktiv war (sonst stehen da noch 
	// die Werte des vorher aufgerufenen Artikels drin und das AH-Datum wird überklatscht)
	if (((CArtikelView* )m_pView)->WasPageActive(0))
	{
		m_dlg.DataExchangeToBuffer( m_Pos_DATUM_AH );
	}

	if ( m_pBufZartikel->DATUM_AH == 0 )
	{
		if (!((CArtikelView* )m_pView)->m_Doc.CheckAutIdemSperre())
		{
            m_pBufZartikel->RETOURENSPERRE[0] = '0'; 
		}
	}
	else
		m_pBufZartikel->RETOURENSPERRE[0] = '1'; 

/*
	// wenn auf Seite 1 ( CArtikelPage2 )
	if ( ((CArtikelView*)m_pView)->GetActivePageIndex( ) == 1 )
	{
		CArtikelPage2 *pP2;
		pP2 = (CArtikelPage2 *)((CArtikelView*)m_pView)->GetPage(1);
		pP2->ShowFields();
	}
*/
	// wenn auf gleicher Seite
	m_RETOURENSPERRE.p_SetInput();
}

class CV_ARTIKEL_DatumAh : public ChValBase
{
public:
	CV_ARTIKEL_DatumAh( CArtikelPage1* pView ) : ChValBase( pView ){};
	void PostProc( )
	{
		((CArtikelPage1* )m_pWnd)->Set_RetourenSperre( );
		((CArtikelPage1* )m_pWnd)->ChangeArtikelName( );
	}
};

void CArtikelPage1::ChangeArtikelName( )
{
	if (IsCountry("D"))
	{
		ChangeArtikelName_D( );
	}
	else if (IsCountry("A"))
	{
		ChangeArtikelName_A( );
	}
	else if (IsCountry("CH"))
	{
		ChangeArtikelName_CH( );
	}
	else if (IsCountry("F"))
	{
		ChangeArtikelName_F( );
	}
	else if (IsCountry("HR"))
	{
		ChangeArtikelName_HR( );
	}
	else 
	{
		ChangeArtikelName_Rest( );
	}

	m_ARTIKEL_NAME.p_SetInput();
	m_ARTIKEL_LANGNAME.p_SetInput();

	// headerinfo
	((CArtikelView*)m_pView)->SetHeaderInfo();
}

void CArtikelPage1::ChangeArtikelName_D( )
{
	char str[12];
	if ( m_pBufZartikel->DATUM_AH != 0 )
	{
		::ConvFromPhoDate( str, m_pBufZartikel->DATUM_AH, "mmjj" );
		memcpy( &m_pBufZartikel->ARTIKEL_NAME[26], str, 4 );
	}
	else
	{
		::IFA_Zuzahlung_to_ZZ( m_pBufZartikel->ZUZAHLUNG_IFA, str );
		memset( &m_pBufZartikel->ARTIKEL_NAME[26], ' ', 2 );
		memcpy( &m_pBufZartikel->ARTIKEL_NAME[28], str, 2 );

		if ( m_pBufZartikel->BTM[0] == '1' )
		{
			memcpy( &m_pBufZartikel->ARTIKEL_NAME[26], CResString::ex().getStrTblText(IDS_STRING797), 2 );
		}
	}
}

void CArtikelPage1::ChangeArtikelName_A( )
{
	char str[12];
	if ( m_pBufZartikel->DATUM_AH != 0 )
	{
		// in Österreich sollte ein Blank vor dem AH-Datum stehen (analog Pharmos)
		::ConvFromPhoDate( str, m_pBufZartikel->DATUM_AH, " mmjj" );
		memcpy( &m_pBufZartikel->ARTIKEL_NAME[25], str, 5 );
	}
	else
	{
		// prüfen, ob AH-Datum gelöscht wurde
		if ( m_pBufOldZartikel->DATUM_AH != 0 )
		{	
			memset( &m_pBufZartikel->ARTIKEL_NAME[26], ' ', 4 );
		}
	}
}

void CArtikelPage1::ChangeArtikelName_CH( )
{
	char str[12];

	// in CH den Namen nur ändern, wenn AH- Datum kleiner "heute" = wenn AH in der Zukunft, wird der Name erst am entsprechenden Tag durch zpdailyclosing verändert.
	if ( m_pBufZartikel->DATUM_AH != 0 && m_pBufZartikel->DATUM_AH <= ::Today() ) 
	{
		::ConvFromPhoDate( str, m_pBufZartikel->DATUM_AH, "mmjj" );
		memcpy( &m_pBufZartikel->ARTIKEL_NAME[26], str, 4 );
		memcpy( &m_pBufCarticlelang->ARTICLENAME[26], str, 4 );
	}
	else
	{
		// prüfen, ob AH-Datum gelöscht wurde
		if ( m_pBufOldZartikel->DATUM_AH != 0 )
		{	
			memset( &m_pBufZartikel->ARTIKEL_NAME[26], ' ', 4 );
			memset( &m_pBufCarticlelang->ARTICLENAME[26], ' ', 4 );
		}

		// nur in der Schweiz "KK" an Stelle 29-30 bei Kuehlkettenartikeln */
		if ( m_pBufZartikel->KUEHLARTIKEL[0] == '4' )
		{
			memcpy( &m_pBufZartikel->ARTIKEL_NAME[28], "KK", 2 );
			memcpy( &m_pBufCarticlelang->ARTICLENAME[28], "KK", 2 );
		}

		// nur in der Schweiz "PS" an Stelle 29-30 bei Psychotropen */
		if ( m_pBufZartikel->PSYCHOTROP[0] != ' ' && m_pBufZartikel->PSYCHOTROP[0] != 'N' )
		{
			memcpy( &m_pBufZartikel->ARTIKEL_NAME[28], "PS", 2 );
			memcpy( &m_pBufCarticlelang->ARTICLENAME[28], "PS", 2 );
		}

		// "BM" nur in D an Stelle 27-28, sonst 29-30 */
		if ( m_pBufZartikel->BTM[0] == '1' )
		{
			memcpy( &m_pBufZartikel->ARTIKEL_NAME[28], CResString::ex().getStrTblText(IDS_STRING797), 2 );
			memcpy( &m_pBufCarticlelang->ARTICLENAME[28], CResString::ex().getStrTblText(IDS_STRING797), 2 );
		}
	}

	/* Artikelbezeichnung auf Seite 5 aktivieren */
	SetArtikelname_Frz();
}

void CArtikelPage1::ChangeArtikelName_F( )
{
	char str[12];
	int i;
	CString cs;

	if ( m_pBufZartikel->DATUM_AH != 0 )
	{
		::ConvFromPhoDate( str, m_pBufZartikel->DATUM_AH, "mmjj" );
		memcpy( &m_pBufZartikel->ARTIKEL_NAME[26], str, 4 );
	}
	else
	{
		// prüfen, ob AH-Datum gelöscht wurde
		if ( m_pBufOldZartikel->DATUM_AH != 0 )
		{	
			memset( &m_pBufZartikel->ARTIKEL_NAME[26], ' ', 4 );
		}

		if ( m_pBufZartikel->BTM[0] == '1' )
		{
			memcpy( &m_pBufZartikel->ARTIKEL_NAME[28], "ST", 2 );
		}
		else
		{
			if ( m_pBufZartikel->TIERARZNEI[0] == '1' )
			{
				cs = m_pBufZartikel->ARTIKEL_NAME;

				// nur, wenn das (V) nicht schon drin
				if (strstr(cs, "(V)") == NULL)
				{
					cs.Trim();
					i = static_cast<int>(strlen(cs));

					if (i < 26)
						memcpy( &m_pBufZartikel->ARTIKEL_NAME[i], " (V)", 4 );
					else
						memcpy( &m_pBufZartikel->ARTIKEL_NAME[26], " (V)", 4 );
				}

				cs = m_pBufZartikel->ARTIKEL_LANGNAME;

				// nur, wenn das (V) nicht schon drin
				if (strstr(cs, "(V)") == NULL)
				{
					cs.Trim();
					i = static_cast<int>(strlen(cs));

					if (i < 46)
						memcpy( &m_pBufZartikel->ARTIKEL_LANGNAME[i], " (V)", 4 );
					else
						memcpy( &m_pBufZartikel->ARTIKEL_LANGNAME[46], " (V)", 4 );
				}
			}
			else if (m_pBufZartikel->PSYCHOTROP[0] == 'P')
			{
				cs = m_pBufZartikel->ARTIKEL_NAME;

				// nur, wenn das (P) nicht schon drin
				if (strstr(cs, "(P)") == NULL)
				{
					cs.Trim();
					i = static_cast<int>(strlen(cs));

					if (i < 26)
						memcpy( &m_pBufZartikel->ARTIKEL_NAME[i], " (P)", 4 );
					else
						memcpy( &m_pBufZartikel->ARTIKEL_NAME[26], " (P)", 4 );
				}

				cs = m_pBufZartikel->ARTIKEL_LANGNAME;

				// nur, wenn das (P) nicht schon drin
				if (strstr(cs, "(P)") == NULL)
				{
					cs.Trim();
					i = static_cast<int>(strlen(cs));

					if (i < 46)
						memcpy( &m_pBufZartikel->ARTIKEL_LANGNAME[i], " (P)", 4 );
					else
						memcpy( &m_pBufZartikel->ARTIKEL_LANGNAME[46], " (P)", 4 );
				}
			}
		}
	}
}

void CArtikelPage1::ChangeArtikelName_HR( )
{
	char str[12];
	if ( m_pBufZartikel->DATUM_AH != 0 )
	{
		::ConvFromPhoDate( str, m_pBufZartikel->DATUM_AH, "mmjj" );
		memcpy( &m_pBufZartikel->ARTIKEL_NAME[26], str, 4 );
	}
	else
	{
		// prüfen, ob AH-Datum gelöscht wurde
		if ( m_pBufOldZartikel->DATUM_AH != 0 )
		{	
			memset( &m_pBufZartikel->ARTIKEL_NAME[26], ' ', 4 );
		}
	}
}

void CArtikelPage1::ChangeArtikelName_Rest( )
{
	char str[12];
	if ( m_pBufZartikel->DATUM_AH != 0 )
	{
		::ConvFromPhoDate( str, m_pBufZartikel->DATUM_AH, "mmjj" );
		memcpy( &m_pBufZartikel->ARTIKEL_NAME[26], str, 4 );
	}
	else
	{
		// prüfen, ob AH-Datum gelöscht wurde
		if ( m_pBufOldZartikel->DATUM_AH != 0 )
		{	
			memset( &m_pBufZartikel->ARTIKEL_NAME[26], ' ', 4 );
		}

		if ( m_pBufZartikel->BTM[0] == '1' )
		{
			memcpy( &m_pBufZartikel->ARTIKEL_NAME[28], CResString::ex().getStrTblText(IDS_STRING797), 2 );
		}
	}
}

// Zuzahlung

BOOL CArtikelPage1::Test_Set_ZZ( BOOL mode )
{
	BOOL bOk;
	char ZZ[3];

	bOk = ::IFA_Zuzahlung_to_ZZ( m_pBufZartikel->ZUZAHLUNG_IFA, ZZ );

	if ( mode )
		GetDlgItem( IDC_ST_ARTIKEL_ZZ )->SetWindowText( ZZ );

	return bOk;
}


class CV_ARTIKEL_Zuzahlung : public ChValBase
{
public:
	CV_ARTIKEL_Zuzahlung( CArtikelPage1* pView ) 
		: ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = ((CArtikelPage1* )m_pWnd)->Test_Set_ZZ( bMeldung );
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_ZUZALUNG) );
		return bOk;
	}
	void PostProc( )
	{
		((CArtikelPage1* )m_pWnd)->ChangeArtikelName();
	}
};

// Preis

BOOL CArtikelPage1::TestPreisDatum( int nr )
{
	BOOL bOk;
	bOk = TRUE; 
	if ( nr < 3 )
	{
		if ( m_bPreisEnabled[nr] )
		{
//			m_dlg.DataExchangeToBuffer( m_Pos_PREIS[nr] + OFFS_GUELAB );
			if ( m_pBufArtpreis[nr]->DATUMGUELTIGAB > 0 )
			{
//				m_dlg.DataExchangeToBuffer( m_Pos_PREIS[nr+1] + OFFS_GUELAB );
				bOk = m_pBufArtpreis[nr]->DATUMGUELTIGAB > 
					  m_pBufArtpreis[nr+1]->DATUMGUELTIGAB;

				if (bOk)
					bOk = m_pBufArtpreis[nr]->DATUMGUELTIGAB > ::Today();
			}
		}
	}
	return bOk;
}

void CArtikelPage1::Set_Single_VAT_Rate( int nr )
{
	double dMwstProz[5];
	CString	CsMwst;
	int	iAnzMwst = 0;
	int iAktSel = 0;
	long lDatum = 0;

	// Mwst-Prozentsätze aus der Taxtab-Klasse holen, hier mit Preisdatum, falls gefüllt (jeweilige Landes-Reihenfolge beachten !!)
	if (m_pBufArtpreis[nr]->DATUMGUELTIGAB == 0)
		lDatum = AddDayToPhoDate( ::Today(), 1 );
    else
		lDatum = m_pBufArtpreis[nr]->DATUMGUELTIGAB;

	if (IsCountry("F"))
		iAnzMwst = m_pTaxTb->GetAllVatRates( lDatum, &dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[4], &dMwstProz[3]);
	else if (IsCountry("HR"))
        iAnzMwst = m_pTaxTb->GetAllVatRates( lDatum, &dMwstProz[0], &dMwstProz[2], &dMwstProz[1], &dMwstProz[3], &dMwstProz[4]);
	else if (IsCountry("RS"))
	{
		iAnzMwst = m_pTaxTb->GetAllVatRates( lDatum, &dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[3], &dMwstProz[4]);
		iAnzMwst++;		// <--- damit auch hier der Wert 0,0% noch angezeigt wird
	}
	else if(IsCountry("A")) // 3RD-VAT
	{
		iAnzMwst = m_pTaxTb->GetAllVatRates( lDatum, &dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[3], &dMwstProz[4]);
		iAnzMwst++;
	}
	else  
		return;

	if (nr == 0)
	{
		iAktSel = m_MWST1.GetCurSel();
		m_MWST1.ResetContent();

		for (int i = 0; i < iAnzMwst; i++)
		{
			CsMwst.Format("%.1f %%", dMwstProz[i]);
			m_MWST1.AddString(CsMwst);
		}

		m_MWST1.SetCurSel(iAktSel);
	}
	else if (nr == 1)
	{
		iAktSel = m_MWST2.GetCurSel();
		m_MWST2.ResetContent();

		for (int i = 0; i < iAnzMwst; i++)
		{
			CsMwst.Format("%.1f %%", dMwstProz[i]);
			m_MWST2.AddString(CsMwst);
		}

		m_MWST2.SetCurSel(iAktSel);
	}
	else if (nr == 2)
	{
		iAktSel = m_MWST3.GetCurSel();
		m_MWST3.ResetContent();

		for (int i = 0; i < iAnzMwst; i++)
		{
			CsMwst.Format("%.1f %%", dMwstProz[i]);
			m_MWST3.AddString(CsMwst);
		}

		m_MWST3.SetCurSel(iAktSel);
	}
	else if (nr == 3)
	{
		iAktSel = m_MWST4.GetCurSel();
		m_MWST4.ResetContent();

		for (int i = 0; i < iAnzMwst; i++)
		{
			CsMwst.Format("%.1f %%", dMwstProz[i]);
			m_MWST4.AddString(CsMwst);
		}

		m_MWST4.SetCurSel(iAktSel);
	}
}

class CV_ARTIKEL_PreisDatum : public ChValBase
{
public:
	CV_ARTIKEL_PreisDatum( int nNr, CArtikelPage1* pView ) 
		: ChValBase( nNr, pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = ((CArtikelPage1* )m_pWnd)->TestPreisDatum( m_nNr );
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_PREISDATUM) );
		return bOk;
	}
	void PostProc( )
	{
		((CArtikelPage1*)m_pWnd)->Set_Single_VAT_Rate(m_nNr);

		// Ergänzung 18.11.13: konsequenterweise auch AVP neu berechnen, weil es theoretisch passieren kann, dass erst GEP und AEP erfasst werden (dann wird AVP berechnet),
		// anschließend wird erst das Datum eingegeben und die Mwst ändert sich dadurch
		((CArtikelPage1*)m_pWnd)->Set_Taxe_AVP(m_nNr);
	}
};

// Taxe

void CArtikelPage1::Set_Taxe_AEP( int nr )
{
	m_dlg.DataExchangeToBuffer( m_Pos_TAXPFL );

	m_TAXPRUEFGROSSO.p_GetInput();
	m_NICHTUEBERGH.p_GetInput();

	if ( m_pBufZartikel->TAXPFL[0] == '0' )
		return;

	if ( m_pBufArtpreis[nr]->GROSSO == 0.0 )
		return;

	if ( m_pBufZartikel->TAXPRUEFGROSSO[0] == '1' ) 
		return;

	if (IsCountry("A"))
	{
		m_pTaxTb->CalcAekAustria( m_pBufArtpreis[nr]->GROSSO, &m_pBufArtpreis[nr]->AEP, 
						m_pBufArtpreis[nr]->DATUMGUELTIGAB, m_pBufZartikel->TAXPFL[0] );	
	}
	else if (IsCountry("F"))
	{
		m_pTaxTb->CalcAekFrance( m_pBufArtpreis[nr]->GROSSO, &m_pBufArtpreis[nr]->AEP, 
						m_pBufArtpreis[nr]->DATUMGUELTIGAB, m_pBufZartikel->TAXPFL[0] );	
	}
	else if (IsCountry("BG"))
	{
		m_pTaxTb->CalcAekBulgaria( m_pBufArtpreis[nr]->GROSSO, &m_pBufArtpreis[nr]->AEP, 
						m_pBufArtpreis[nr]->DATUMGUELTIGAB, m_pBufZartikel->TAXPFL[0],
						m_pBufArtpreis[nr]->PREIS_TYP );
	}
	else
	{
		m_pTaxTb->CalcAek( m_pBufArtpreis[nr]->GROSSO, &m_pBufArtpreis[nr]->AEP, 
				m_pBufArtpreis[nr]->DATUMGUELTIGAB, m_pBufZartikel->TAXPFL[0] );			// OTCX_RX
	}

	m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[nr] + OFFS_AEP );
	Set_Taxe_AVP( nr );
}

void CArtikelPage1::Set_Abzug_130( int )
{
	return;
	
	/* ab 01.04.2014 wird Erstattbetrag von IFA nicht mehr versorgt, das Abzugs- KZ soll aber trotzdem auf "ja" gestellt werden können!
	if (m_pBufArtpreis[nr]->ERSTATTBETRAG <= 0.0)
	{
		m_pBufArtpreis[nr]->DISC_DEDUCED_YET = 0;
		m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[nr] + OFFS_DISC_DED_YET );
	}*/
}

void CArtikelPage1::Set_Grosso_From_LBP( int nr )
{
	double newGrosso = m_pBufArtpreis[nr]->LIEFERBASISPREIS - ( m_pBufArtpreis[nr]->LIEFERBASISPREIS * m_pBufZartikel->HERST_PROZENT / 100 );

	if ( (newGrosso <= m_pBufArtpreis[nr]->AVP || m_pBufArtpreis[nr]->AVP == 0) && m_pBufZartikel->HERST_PROZENT != 0 && m_pBufArtpreis[nr]->LIEFERBASISPREIS > 0 )
	{
		m_pBufArtpreis[nr]->GROSSO = newGrosso;
		m_pBufArtpreis[nr]->HERST_PROZENT = m_pBufZartikel->HERST_PROZENT; 
		m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[nr] + OFFS_GROSSO );
		m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[nr] + OFFS_HPROZ );
	}
}

void CArtikelPage1::Set_Taxe_AVP( int nr )
{
	m_ARTIKEL_GESPERRT.p_GetInput();
	m_dlg.DataExchangeToBuffer( m_Pos_TAXPFL );
	m_dlg.DataExchangeToBuffer( m_Pos_HERST_PROZENT );
	m_dlg.DataExchangeToBuffer( m_Pos_PREIS[nr] + OFFS_MWST );

	if ( m_pBufZartikel->TAXPFL[0] == '0' && !IsCountry("HR"))		// in Kroatien gibt es kein Taxkennzeichen
		return;

	if (IsCountry("BG") && m_pBufArtpreis[nr]->PREIS_TYP == 1)		// in Bulgarien keine Berechnung für Krankenkasse
		return;

	int mwst = 0;

	// 5 Mwst-Sätze in Frankreich
	if (IsCountry("F"))
	{
		if ( m_pBufArtpreis[nr]->KE_MWST[0] == '4' )
			mwst = TAXTAB_FR_MWST_4;
		else if ( m_pBufArtpreis[nr]->KE_MWST[0] == '3' )
			mwst = TAXTAB_FR_MWST_3;
		else if ( m_pBufArtpreis[nr]->KE_MWST[0] == '2' )	
			mwst = TAXTAB_FR_MWST_2;
		else if ( m_pBufArtpreis[nr]->KE_MWST[0] == '1' )	
			mwst = TAXTAB_FR_MWST_1;
		else												
			mwst = TAXTAB_FR_MWST_0;
	}
	// 3 Mwst-Sätze in Kroatien
	else if (IsCountry("HR"))
	{
		if ( m_pBufArtpreis[nr]->KE_MWST[0] == '2' )
			mwst = TAXTAB_HR_MWST_2;
		else if ( m_pBufArtpreis[nr]->KE_MWST[0] == '1' )	
			mwst = TAXTAB_HR_MWST_1;
		else												
			mwst = TAXTAB_HR_MWST_0;
	}
	else  if(IsCountry("A"))
	{
		if ( m_pBufArtpreis[nr]->KE_MWST[0] == '1' )		// Vermindert
			mwst = TAXTAB_AT_VERMM;
		else if ( m_pBufArtpreis[nr]->KE_MWST[0] == '0' )	// Voll
			mwst = TAXTAB_AT_VOLL;
		else if( m_pBufArtpreis[nr]->KE_MWST[0] == '2' ) // 3RD
			mwst = TAXTAB_AT_3RD;
	}
	else
	{
		if ( m_pBufArtpreis[nr]->KE_MWST[0] == '1' )		// Vermindert
			mwst = TAXTAB_IS_VERMMWST;
		else if ( m_pBufArtpreis[nr]->KE_MWST[0] == '0' )	// Voll
			mwst = TAXTAB_IS_VOLLMWST;
		else												// Ohne
			mwst = TAXTAB_IS_OHNEMWST;
	}

	if (IsCountry("A"))
	{
		m_pTaxTb->CalcAvkAustriaMwst( m_pBufArtpreis[nr]->AEP, &m_pBufArtpreis[nr]->AVP, 
							mwst, m_pBufArtpreis[nr]->DATUMGUELTIGAB, 
							m_pBufZartikel->TAXPFL[0], m_pBufZartikel->BTM[0] );
	}
	else if (IsCountry("F"))
	{
		m_pTaxTb->CalcAvkFranceMwst( m_pBufArtpreis[nr]->GROSSO, m_pBufArtpreis[nr]->AEP, &m_pBufArtpreis[nr]->AVP, 
							mwst, m_pBufArtpreis[nr]->DATUMGUELTIGAB, 
							m_pBufZartikel->TAXPFL[0] );
	}
	else if (IsCountry("HR") && m_pBufZartikel->HERST_PROZENT > 0)
	{
		m_pTaxTb->CalcAvkCroatiaMwst( m_pBufArtpreis[nr]->AEP, &m_pBufArtpreis[nr]->AVP, 
							mwst, m_pBufArtpreis[nr]->DATUMGUELTIGAB, 
							m_pBufZartikel->HERST_PROZENT );
	}
	else if (IsCountry("BG"))
	{
		m_pTaxTb->CalcAvkBulgariaMwst( m_pBufArtpreis[nr]->GROSSO, &m_pBufArtpreis[nr]->AVP, 
							mwst, m_pBufArtpreis[nr]->DATUMGUELTIGAB, 
							m_pBufZartikel->TAXPFL[0], m_pBufArtpreis[nr]->PREIS_TYP );
	}
	else
	{
		m_pTaxTb->CalcAvkMwst( m_pBufArtpreis[nr]->AEP, &m_pBufArtpreis[nr]->AVP, 
							mwst, m_pBufArtpreis[nr]->DATUMGUELTIGAB,
							m_pBufZartikel->TAXPFL[0] );			// OTCX_RX
	}

	m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[nr] + OFFS_AVP );
}
	
void CArtikelPage1::Set_DefaultPreisDatum( int nr )
{
	//  nur bei der 1. Preiszeile !!!!!
	if ( nr != 0 ) 
		return;

	// Neu 2021: da der AEP in der CH nicht genutzt wird, wird anstelle der AGP eingeblendet, daher ist die Focus Betrachtung obsolet
	// in der Schweiz ist der AEP ausgeblendet, daher steht der Focus gleich auf dem AVP
	// offen bleibt trotzdem, was diese Abfrage für einen Sinn hat
	//if (IsCountry("CH"))
	//{
	//	if ( GetFocus() != &m_AVP1 ) return;
	//}
	//else
	//{
	//	if ( GetFocus() != &m_AEP1 ) return;
	//}

	m_dlg.DataExchangeToBuffer( m_Pos_PREIS[nr] + OFFS_GUELAB );
	if ( m_pBufArtpreis[nr]->DATUMGUELTIGAB <= 0 )
	{
//		m_pBufArtpreis[nr]->DATUMGUELTIGAB = ::Today();	
		// Tagesdatum + 1:  neu am 17.01.2001
		m_pBufArtpreis[nr]->DATUMGUELTIGAB = AddDayToPhoDate( ::Today(), 1 );
		m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[nr] + OFFS_GUELAB );

		// Mwst-Satz anhand des automatisch vorgeblendeten Datums füllen
		Set_Single_VAT_Rate(nr);
	}
}

class CV_ARTIKEL_Taxe_AEP : public ChValBase
{
public:
	CV_ARTIKEL_Taxe_AEP( int nNr, CArtikelPage1* pView ) 
		: ChValBase( nNr, pView ){};
	void PostProc( )
	{
		// wegen EURO-Taxtabelle: zuerst Datum, dann Taxe 
		((CArtikelPage1* )m_pWnd)->Set_DefaultPreisDatum( m_nNr );
		((CArtikelPage1* )m_pWnd)->Set_Taxe_AEP( m_nNr );
		((CArtikelPage1* )m_pWnd)->CalculatePercent( m_nNr );
	}
};

class CV_ARTIKEL_Taxe_AVP : public ChValBase
{
public:
	CV_ARTIKEL_Taxe_AVP( int nNr, CArtikelPage1* pView ) 
		: ChValBase( nNr, pView ){};
	void PostProc( )
	{
		((CArtikelPage1* )m_pWnd)->Set_Taxe_AVP( m_nNr );
		((CArtikelPage1* )m_pWnd)->CalculatePercent( m_nNr );
	}
};

class CV_ARTIKEL_Proz_LBP : public ChValBase
{
public:
	CV_ARTIKEL_Proz_LBP( int nNr, CArtikelPage1* pView ) 
		: ChValBase( nNr, pView ){};
	void PostProc( )
	{
		((CArtikelPage1* )m_pWnd)->Set_Grosso_From_LBP( m_nNr );
	}
};

class CV_ARTIKEL_Erstatt_Abzug : public ChValBase
{
public:
	CV_ARTIKEL_Erstatt_Abzug( int nNr, CArtikelPage1* pView ) 
		: ChValBase( nNr, pView ){};
	void PostProc( )
	{
		((CArtikelPage1* )m_pWnd)->Set_Abzug_130( m_nNr );
	}
	BOOL Validate( BOOL )
	{
		((CArtikelPage1* )m_pWnd)->Set_Abzug_130( m_nNr );
		return TRUE;
	}
};

void CArtikelPage1::Set_Herst_Prozent( )
{
	if (IsCountry("CH")) // herst_prozent hier für CH nicht setzen!
		return;

	int i;
//	m_HERST_PROZENT.p_GetInput();	// weg am 12.12.2000
	for ( i = 0; i < NUMBER_OF_PRICE_ON_PAGE1 ; i++ )
	{
		// in Frankreich immer nur den ersten Prozentsatz updaten
		if ( m_bPreisEnabled[i] && (!(IsCountry("F") && i > 0)))
		{
			m_pBufArtpreis[i]->HERST_PROZENT = m_pBufZartikel->HERST_PROZENT; 
			m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[i] + OFFS_HPROZ );
		} 
	}
}

class CV_ARTIKEL_Herst_Prozent : public ChValBase
{
public:
	CV_ARTIKEL_Herst_Prozent( CArtikelPage1* pView ) 
		: ChValBase( pView ){};
	void PostProc( )
	{
		((CArtikelPage1* )m_pWnd)->Set_Herst_Prozent( );

		if (IsCountry("HR"))
		{
			((CArtikelPage1* )m_pWnd)->Enable_AVP_Croatia( );
		}
	}
};

/////////////////////////////////////////////////////////////
//  Preispruefung

BOOL CArtikelPage1::Test_NichtTaxartikelGesperrt( int i, int *ind, CString &Meldung )
{
	*ind = m_Pos_PREIS[i] + OFFS_GROSSO;

	// GEP = 0, AEP = 0, AVP >= 0
	if ( m_pBufArtpreis[i]->GROSSO == 0.0 &&
		 m_pBufArtpreis[i]->AEP    == 0.0 &&
		 m_pBufArtpreis[i]->AVP    >= 0.0    )  return TRUE;

	// GEP = 0, AEP >= 0, AVP = 0
	if ( m_pBufArtpreis[i]->GROSSO == 0.0 &&
		 m_pBufArtpreis[i]->AEP    >= 0.0 &&
		 m_pBufArtpreis[i]->AVP    == 0.0    )  return TRUE;

	// GEP = 0, AEP > 0, AVP > AEP
	if ( m_pBufArtpreis[i]->GROSSO == 0.0 &&
		 m_pBufArtpreis[i]->AEP    >  0.0 &&
		 m_pBufArtpreis[i]->AVP    >  m_pBufArtpreis[i]->AEP )  return TRUE;

	// in der Schweiz gibt es keinen AEP
	if (IsCountry("CH"))
	{
		// GEP > 0, AVP = 0
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AVP		== 0.0 )  return TRUE;

		// GEP > 0, AVP > GEP
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AVP		>  m_pBufArtpreis[i]->GROSSO )  return TRUE;
	}
	else if (IsCountry("F"))
	{
		// GEP > 0, AEP >= GEP, AVP = 0
		if (m_pBufArtpreis[i]->GROSSO > 0.0 &&
			m_pBufArtpreis[i]->AEP >= m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP == 0.0)  return TRUE;
		// GEP > 0, AEP >= GEP, AVP > AEP
		if (m_pBufArtpreis[i]->GROSSO > 0.0 &&
			m_pBufArtpreis[i]->AEP >= m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP > m_pBufArtpreis[i]->AEP)  return TRUE;
	}
	else
	{
		// GEP > 0, AEP >= GEP (muss lt. Hr. Peetz so sein), AVP = 0
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		>= m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		== 0.0    )  return TRUE;

		// GEP > 0, AEP > GEP, AVP > AEP
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		>  m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		>  m_pBufArtpreis[i]->AEP   )  return TRUE;
	}

	// in Kroatien & Bulgarien & Deutschland ist auch GEP = AEP ok
	if (IsCountry("HR") || IsCountry("BG") || IsCountry("D"))
	{
		// GEP > 0, AEP = GEP, AVP = 0
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		== m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		== 0.0 )  return TRUE;

		// GEP > 0, AEP = GEP, AVP > AEP
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		== m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		>  m_pBufArtpreis[i]->AEP )  return TRUE;
	}

	// in Serbien ist auch GEP > AEP ok (pervers !!)
	if (IsCountry("RS"))
	{
		// GEP > 0, AEP <= GEP, AVP = 0
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		<= m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		== 0.0 )  return TRUE;

		// GEP > 0, AEP <= GEP, AVP > AEP
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		<= m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		>  m_pBufArtpreis[i]->AEP )  return TRUE;
	}

	// in Kroatien ist auch AEP = AVP ok
	if (IsCountry("HR"))
	{
		// GEP = 0, AEP > 0, AVP = AEP
		if ( m_pBufArtpreis[i]->GROSSO	== 0.0 &&
			m_pBufArtpreis[i]->AEP		>  0.0 &&
			m_pBufArtpreis[i]->AVP		== m_pBufArtpreis[i]->AEP )  return TRUE;

		// GEP > 0, AEP > GEP, AVP = AEP
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		>  m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		== m_pBufArtpreis[i]->AEP )  return TRUE;
	}

	Meldung = CResString::ex().getStrTblText(IDS_PRICE_ERR); 

	return FALSE;
}

BOOL CArtikelPage1::Test_NichtTaxartikel( int i, int *ind, CString &Meldung )
{
	*ind = m_Pos_PREIS[i] + OFFS_GROSSO;

	// in der Schweiz gibt es keinen AEP
	if (IsCountry("CH"))
	{
		// GEP > 0, AVP > GEP
		if ( m_pBufArtpreis[i]->GROSSO >  0.0 &&
			m_pBufArtpreis[i]->AVP    >  m_pBufArtpreis[i]->GROSSO )  return TRUE;

		// GEP > 0, AVP = 0
		if ( m_pBufArtpreis[i]->GROSSO >  0.0 &&
			m_pBufArtpreis[i]->AVP    == 0.0   )  return TRUE;
	}
	// In france the aep can also be equal or greater than grosso (CPR-221009)
	else if (IsCountry("F"))
	{
		// GEP > 0, AEP >= GEP, AVP > AEP
		if (m_pBufArtpreis[i]->GROSSO > 0.0 &&
			m_pBufArtpreis[i]->AEP >= m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP > m_pBufArtpreis[i]->AEP)  return TRUE;
		// GEP > 0, AEP >= GEP, AVP = 0
		if ( m_pBufArtpreis[i]->GROSSO >  0.0 &&
			m_pBufArtpreis[i]->AEP    >= m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP    == 0.0 )  return TRUE;
	}
	else
	{
		// GEP > 0, AEP > GEP, AVP > AEP
		if ( m_pBufArtpreis[i]->GROSSO >  0.0 &&
			m_pBufArtpreis[i]->AEP    >  m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP    >  m_pBufArtpreis[i]->AEP   )  return TRUE;

		// GEP > 0, AEP > GEP, AVP = 0
		if ( m_pBufArtpreis[i]->GROSSO >  0.0 &&
			m_pBufArtpreis[i]->AEP    >  m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP    == 0.0   )  return TRUE;
	}

	if ( m_pBufZartikel->PREIS0ARTIKEL[0] == '1' )
	{
		// ab Mail Peetz vom 16.07.2003 gilt: 
		// PREIS0ARTIKEL wenn Grosso = 0, AVP = 0 ( vorher zusaetzlich AEP = 0 )
		if ( m_pBufArtpreis[i]->GROSSO == 0.0 &&
//			 m_pBufArtpreis[i]->AEP    == 0.0 &&      
			 m_pBufArtpreis[i]->AVP    == 0.0    )
			 return TRUE;
	}

	if ( m_pBufZartikel->NICHTUEBERGH[0] == '1' )
	{
		// GEP = 0, AEP > 0, AVP = 0
		if ( m_pBufArtpreis[i]->GROSSO == 0.0 &&
			 m_pBufArtpreis[i]->AEP    >  0.0 &&
			 m_pBufArtpreis[i]->AVP    == 0.0    )
			 return TRUE;

		// GEP = 0, AEP > 0, AVP > AEP
		if ( m_pBufArtpreis[i]->GROSSO == 0.0 &&
			 m_pBufArtpreis[i]->AEP    > 0.0 &&
			 m_pBufArtpreis[i]->AVP    > m_pBufArtpreis[i]->AEP )
			 return TRUE;

		if (IsCountry("D")) // IFA liefert für alle Artikel mit bisher Grosso = 0 ab 2011 Grosso = AEP
		{
			// GEP > 0, AEP >= GEP, AVP > AEP
			if ( m_pBufArtpreis[i]->GROSSO >  0.0 &&
				m_pBufArtpreis[i]->AEP    >=  m_pBufArtpreis[i]->GROSSO &&
				m_pBufArtpreis[i]->AVP    >  m_pBufArtpreis[i]->AEP   )  return TRUE;

			// GEP > 0, AEP >= GEP, AVP = 0
			if ( m_pBufArtpreis[i]->GROSSO >  0.0 &&
				m_pBufArtpreis[i]->AEP    >=  m_pBufArtpreis[i]->GROSSO &&
				m_pBufArtpreis[i]->AVP    == 0.0   )  return TRUE;
		}
	}

	// in Kroatien & Bulgarien ist auch GEP = AEP ok
	if (IsCountry("HR") || IsCountry("BG"))
	{
		// GEP > 0, AEP = GEP, AVP = 0
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		== m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		== 0.0 )  return TRUE;

		// GEP > 0, AEP = GEP, AVP > AEP
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		== m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		>  m_pBufArtpreis[i]->AEP )  return TRUE;
	}

	// in Serbien ist auch GEP > AEP ok (pervers !!)
	if (IsCountry("RS"))
	{
		// GEP > 0, AEP <= GEP, AVP = 0
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		<= m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		== 0.0 )  return TRUE;

		// GEP > 0, AEP <= GEP, AVP > AEP
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		<= m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		>  m_pBufArtpreis[i]->AEP )  return TRUE;
	}

	// in Kroatien ist auch AEP = AVP ok
	if (IsCountry("HR"))
	{
		// GEP > 0, AEP > GEP, AVP = AEP
		if ( m_pBufArtpreis[i]->GROSSO	>  0.0 &&
			m_pBufArtpreis[i]->AEP		>  m_pBufArtpreis[i]->GROSSO &&
			m_pBufArtpreis[i]->AVP		== m_pBufArtpreis[i]->AEP )  return TRUE;
	}

	Meldung = CResString::ex().getStrTblText(IDS_PRICE_ERR); 

	return FALSE;
}

BOOL CArtikelPage1::Test_Taxartikel( int i, int *ind, CString &Meldung )
{
	double aep;
	double avp;
	double diff;
	int mwst = 0;
	bool bAepNachTaxe;

	bAepNachTaxe = true;
	if ( m_pBufArtpreis[i]->GROSSO == 0.0 )
	{
		if ( m_pBufZartikel->NICHTUEBERGH[0] != '1' )
		{
			Meldung = CResString::ex().getStrTblText(IDS_GEP_NOT_0);
			*ind = m_Pos_PREIS[i] + OFFS_GROSSO;
			return FALSE;
		}
		bAepNachTaxe = false;
	}
	
	/* ab 2011: keine AEP- Taxprüfung für NGH- Artikel oder Artikel mit GEP == AEP (wird so von IFA geliefert!)
	if ( (m_pBufArtpreis[i]->GROSSO == m_pBufArtpreis[i]->AEP ||
		 m_pBufZartikel->NICHTUEBERGH[0] == '1') &&
		 IsCountry("D") )
		bAepNachTaxe = false;*/

	//ab 2011: keine AEP- Taxprüfung für NGH- Artikel 
	if ( m_pBufZartikel->NICHTUEBERGH[0] == '1' &&
		 IsCountry("D") )
		bAepNachTaxe = false;

	if ( m_pBufArtpreis[i]->AEP == 0.0 )
	{
		Meldung = CResString::ex().getStrTblText(IDS_AEP_NOT_0);
		*ind = m_Pos_PREIS[i] + OFFS_AEP;
		return FALSE;
	}

	if ( (m_pBufArtpreis[i]->GROSSO > m_pBufArtpreis[i]->AEP ||
		 m_pBufArtpreis[i]->GROSSO == m_pBufArtpreis[i]->AEP && !IsCountry("D"))) 
	{
		Meldung = CResString::ex().getStrTblText(IDS_AEP_OVER_GEP);
		*ind = m_Pos_PREIS[i] + OFFS_AEP;
		return FALSE;
	}

	if ( m_pBufZartikel->TAXPRUEFGROSSO[0] == '1' )
		 bAepNachTaxe = false;

	if ( bAepNachTaxe )
	{
		if (IsCountry("A"))
		{
			m_pTaxTb->CalcAekAustria( m_pBufArtpreis[i]->GROSSO, &aep, m_pBufArtpreis[i]->DATUMGUELTIGAB,
							m_pBufZartikel->TAXPFL[0] );
		}
		else if (IsCountry("F"))
		{
			m_pTaxTb->CalcAekFrance( m_pBufArtpreis[i]->GROSSO, &aep, m_pBufArtpreis[i]->DATUMGUELTIGAB,
							m_pBufZartikel->TAXPFL[0] );
		}
		else if (IsCountry("BG"))
		{
			m_pTaxTb->CalcAekBulgaria( m_pBufArtpreis[i]->GROSSO, &aep, m_pBufArtpreis[i]->DATUMGUELTIGAB,
							m_pBufZartikel->TAXPFL[0], m_pBufArtpreis[i]->PREIS_TYP );
		}
		else
		{
			m_pTaxTb->CalcAek( m_pBufArtpreis[i]->GROSSO, &aep, m_pBufArtpreis[i]->DATUMGUELTIGAB,
							m_pBufZartikel->TAXPFL[0] );			// OTCX_RX
		}

		diff = m_pBufArtpreis[i]->AEP - aep;
		if ( diff < -0.005 || diff > 0.005 )
		{
			Meldung = CResString::ex().getStrTblText(IDS_AEP_TAX_ERR);
			*ind = m_Pos_PREIS[i] + OFFS_AEP;
			return FALSE;
		}
	}

	// 4 Mwst-Sätze in Frankreich
	if (IsCountry("F"))
	{
		if ( m_pBufArtpreis[i]->KE_MWST[0] == '3' )		
			mwst = TAXTAB_FR_MWST_3;
		else if ( m_pBufArtpreis[i]->KE_MWST[0] == '2' )	
			mwst = TAXTAB_FR_MWST_2;
		else if ( m_pBufArtpreis[i]->KE_MWST[0] == '1' )	
			mwst = TAXTAB_FR_MWST_1;
		else if ( m_pBufArtpreis[i]->KE_MWST[0] == '4' )	
			mwst = TAXTAB_FR_MWST_4;
		else												
			mwst = TAXTAB_FR_MWST_0;
	}
	else if(IsCountry("A"))
	{
		if ( m_pBufArtpreis[i]->KE_MWST[0] == '1' )			// Vermindert
			mwst = TAXTAB_AT_VERMM;
		else if ( m_pBufArtpreis[i]->KE_MWST[0] == '0' )	// Voll
			mwst = TAXTAB_AT_VOLL;
		else if ( m_pBufArtpreis[i]->KE_MWST[0] == '2' )	// 3RD-VAT
			mwst = TAXTAB_AT_3RD;
	}
	else
	{
		if ( m_pBufArtpreis[i]->KE_MWST[0] == '1' )			// Vermindert
			mwst = TAXTAB_IS_VERMMWST;
		else if ( m_pBufArtpreis[i]->KE_MWST[0] == '0' )	// Voll
			mwst = TAXTAB_IS_VOLLMWST;
		else if ( m_pBufArtpreis[i]->KE_MWST[0] == '2' )	// ohne
			mwst = TAXTAB_IS_OHNEMWST;
	}

	if (IsCountry("A"))
	{
		m_pTaxTb->CalcAvkAustriaMwst( m_pBufArtpreis[i]->AEP, &avp, mwst, m_pBufArtpreis[i]->DATUMGUELTIGAB,
									m_pBufZartikel->TAXPFL[0], m_pBufZartikel->BTM[0] );	
	}
	else if (IsCountry("F"))
	{
		m_pTaxTb->CalcAvkFranceMwst( m_pBufArtpreis[i]->GROSSO, m_pBufArtpreis[i]->AEP, &avp, mwst, m_pBufArtpreis[i]->DATUMGUELTIGAB,
									m_pBufZartikel->TAXPFL[0] );	
	}
	else if (IsCountry("BG"))
	{
		m_pTaxTb->CalcAvkBulgariaMwst( m_pBufArtpreis[i]->GROSSO, &avp, mwst, m_pBufArtpreis[i]->DATUMGUELTIGAB,
									m_pBufZartikel->TAXPFL[0], m_pBufArtpreis[i]->PREIS_TYP );
	}
	else
	{
		m_pTaxTb->CalcAvkMwst( m_pBufArtpreis[i]->AEP, &avp, mwst, m_pBufArtpreis[i]->DATUMGUELTIGAB,
							m_pBufZartikel->TAXPFL[0] );			// OTCX_RX
	}

	// keine Taxtabelle für AVP und Preistyp 1 in Bulgarien hinterlegt, also auch keine Prüfung des AVPs
	if (IsCountry("BG") && m_pBufArtpreis[i]->PREIS_TYP == 1)
		return TRUE;

	diff = m_pBufArtpreis[i]->AVP - avp;
	if ( diff < -0.005 || diff > 0.005 )
	{
		Meldung = CResString::ex().getStrTblText(IDS_AVP_TAX_ERR);
		*ind = m_Pos_PREIS[i] + OFFS_AVP;
		return FALSE;
	}

	return TRUE;
}

BOOL CArtikelPage1::Test_PreisAufNull( int i, int *ind, CString &Meldung )
{
	// wenn Preis0Artikel geaendert auf Preis0Artikel = ja
	// dann muss ein neuer Preis eingegeben werden
	if ( ! NeuGleichAlt( *m_pBufZartikel->PREIS0ARTIKEL,
						 *m_pBufOldZartikel->PREIS0ARTIKEL ) &&
		 *m_pBufZartikel->PREIS0ARTIKEL == '1' )
	{
		// ab Mail Peetz vom 16.07.2003 gilt: 
		// PREIS0ARTIKEL wenn Grosso = 0, AVP = 0 ( vorher zusaetzlich AEP = 0 )
		if ( m_pBufArtpreis[i]->GROSSO > 0.0 ||
//			 m_pBufArtpreis[i]->AEP    > 0.0 ||
			 m_pBufArtpreis[i]->AVP    > 0.0    )
		{
//			Meldung = CResString::ex().getStrTblText(IDS_FREE_ART1);
			Meldung = CResString::ex().getStrTblText(IDS_FREE_ART2);
			*ind = m_Pos_PREIS[i] + OFFS_GROSSO;
			return FALSE;
		}

		// auch bei PREIS0ARTIKEL muss zumindest ein zartpreis-Satz mit Datum vorhanden sein
		if ( m_pBufArtpreis[i]->DATUMGUELTIGAB == 0 )
		{
			Meldung = CResString::ex().getStrTblText(IDS_STRING10002);
			*ind = m_Pos_PREIS[i] + OFFS_GROSSO;
			return FALSE;
		}

		return TRUE;
	}

	// Normalfall
	// neu ab 24.11.98: wenn ueber GH, dann darf Grosso auf Null gehen
	if ( *m_pBufZartikel->NICHTUEBERGH == '0' )
	{
		if ( m_pBufArtpreis[i]->GROSSO	  == 0.0 && 
			 m_pBufArtpreis[i+1]->GROSSO   > 0.0 &&
	// Ergänzung 13.01.05: GEP = 0 ist ok, wenn Preis0Artikel gesetzt ist
			 *m_pBufZartikel->PREIS0ARTIKEL == '0' )
		{
			Meldung = CResString::ex().getStrTblText(IDS_GEP_CHANGE);
			*ind = m_Pos_PREIS[i] + OFFS_GROSSO;
			return FALSE;
		}
	}

	// bei Amedis gibt's keinen AEP, also darf der auch 0 sein
	// 05.07.11 Mr Ponudic: "Please enable setting price to 0 for Croatia"
	// 02.05.17 Hellmich-Scheuch: "auch in AT erlauben"
	if (!IsCountry("CH") && !IsCountry("HR") && !IsCountry("A"))
	{
		if ( m_pBufArtpreis[i]->AEP  == 0.0 && 
			 m_pBufArtpreis[i+1]->AEP > 0.0 &&
			/* Ergänzung: nur, wenn auch tatsächlich ein neuer Preis eingegeben wurde (in Österreich kam die
						  Meldung mal, weil ein am Vortag mit 0,00 eingegebener AEP noch pflegbar war) */
			 m_pBufOldArtpreis[i]->DATUMGUELTIGAB == 0 )
		{
			Meldung = CResString::ex().getStrTblText(IDS_AEP_CHANGE);
			*ind = m_Pos_PREIS[i] + OFFS_AEP;
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CArtikelPage1::Test_MaxAep_MaxAvp( int i, int *ind, CString &Meldung )
{
	if ( m_pBufArtpreis[i]->AEP > m_pBufArtpreis[i]->MAXAEP && m_pBufArtpreis[i]->MAXAEP > 0.0	)	 
	{
		Meldung = CResString::ex().getStrTblText(IDS_AEP_OVER_MAXAEP);
		*ind = m_Pos_PREIS[i] + OFFS_EAVP; // da steht in FR der MaxAep
		return FALSE;
	}

	if ( m_pBufArtpreis[i]->AVP > m_pBufArtpreis[i]->MAXAVP && m_pBufArtpreis[i]->MAXAVP > 0.0 )
	{
		Meldung = CResString::ex().getStrTblText(IDS_AVP_OVER_MAXAVP);
		*ind = m_Pos_PREIS[i] + OFFS_MAXAVP;
		return FALSE;
	}

	return TRUE;
}

BOOL CArtikelPage1::Test_Preis( int i, int *ind, CString &cErrMeldung )
{
	BOOL bOk;

//	if ( m_pBufZartikel->TAXPFL[0] == '1' )
	if ( m_pBufZartikel->TAXPFL[0] != '0' && !IsCountry("F"))		// OTCX_RX - keine Prüfung in FR!
	{
		bOk = Test_Taxartikel( i, ind, cErrMeldung );
	}
	else		// NichtTaxartikel
	{
		if ( m_pBufZartikel->ARTIKEL_GESPERRT[0] == '1' )
			bOk = Test_NichtTaxartikelGesperrt( i, ind, cErrMeldung );
		else	
			bOk = Test_NichtTaxartikel( i, ind, cErrMeldung );
	}

	if ( bOk && i < NUMBER_OF_PRICE_ON_PAGE1 - 1 )
		bOk = Test_PreisAufNull( i, ind, cErrMeldung );

	if ( bOk )
		bOk = Test_MaxAep_MaxAvp( i, ind, cErrMeldung );

	return bOk;
}


/////////////////////////////////////////////////////////////
//  EndValidierung 

BOOL CArtikelPage1::EndValidate( int *ind, BOOL bMeldung )
{
	CString cErrMeldung;

	/* PostProcs aufrufen hier !!!!! */
	if ( (GetFocus() == &m_DATUM_AH)  || (IsCountry("A") && m_pBufZartikel->DATUM_AH > 0) ) 
		Set_RetourenSperre();

	ChangeArtikelName( );
	Set_Herst_Prozent( );

	*ind = 0;

	// Taxpflichtig- / Nettoartikel ( gegenseitiger Ausschluss )
//	if ( *m_pBufZartikel->TAXPFL       == '1' &&
	if ( *m_pBufZartikel->TAXPFL       != '0' &&	// OTCX_RX
		 *m_pBufZartikel->NETTOARTIKEL == '1' )
	{
		if ( bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_TAX_NO_SET) );

		*ind = m_Pos_TAXPFL;
		return FALSE;
	}

	CString Artikel_Nr_Herst;

	// in Ris Orangis muss die Artikelnr. des Herstellers immer gefüllt und eindeutig sein
/* 	CEkZdpApp *theApp = ( CEkZdpApp *) AfxGetApp();
	CString Database, Artikel_Nr_Herst;

	Database = ((CEkZdpApp*) AfxGetApp())->GetDbaseName();

	if (Database == "pps1pfr") */

	// auch für Prewhole Österreich (bei gleicher Herstellernummer)
	
	// neu 07/2014: da nun auch für die Schweiz benötigt, steuerbar über Hersteller-Flag in allen Ländern
/*	if ((IsCountry("F") || IsCountry("A")) && IsPrewhole() && !IsIvrylab())
	{
		if (m_pBufZartikel->HERSTELLER_NR == 11729) */
	if (m_sANRH_ZWING_EINZIG == 1)
	{
		Artikel_Nr_Herst = *m_pBufZartikel->ARTIKEL_NR_HERST;
		Artikel_Nr_Herst.TrimLeft();
		Artikel_Nr_Herst.TrimRight();

		if (Artikel_Nr_Herst.IsEmpty())
		{
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING10003) );
			*ind = m_Pos_ARTIKEL_NR_HERST;
			return FALSE;
		}
		else
		{
			long pzn = ((CArtikelView* )m_pView)->m_Doc.CheckArtikelNrHerstExisting();

			if (pzn > 0)
			{
				if ( bMeldung )
				{
					cErrMeldung.Format(CResString::ex().getStrTblText(IDS_STRING10282), pzn);
					MsgBoxOK( cErrMeldung );
				}

				*ind = m_Pos_ARTIKEL_NR_HERST;
				return FALSE;
			}
		}
	}

	// Rezept- / Apothekenpflichtig ( gegenseitiger Ausschluss )
	if ( *m_pBufZartikel->REZEPTPFL    == '1' &&
		 *m_pBufZartikel->APOTHEKENPFL == '1'     )
	{
		// überall außer D gleichzeitig erlaubt
		if (IsCountry("D"))
		{
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_REZAPO_NO_SET) );

			*ind = m_Pos_REZEPTPFL;
			return FALSE;
		}
	}

	// Abhaengigkeiten: Nur KVA, nicht ueber GH (Peetz)
	//  nuGH nKVA
	//  nein nein
	//  ja   nein
	//	ja	 ja
	if ( *m_pBufZartikel->NURKVA       == '1' &&
		 *m_pBufZartikel->NICHTUEBERGH == '0'    )
	{
		if ( bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_NURKVA_SET) );

		*ind = m_Pos_NICHTUEBERGH;
		return FALSE;
	}

	// Kett-Artikel
	if ( *m_pBufZartikel->ERSATZ_NR_AKTIV == '1' )
	{	
		// aktiv
		if(  m_pBufZartikel->ERSATZ_NR == 0 )
		{
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_EPZN_SET) );
			*ind = m_Pos_ERSATZ_NR;
			return FALSE;
		}
		
		// Kett-Artikel gesperrt
		else if ( IsKettArtikelGesperrt( ) )
		{
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_EPZN_SET2) );
			*ind = m_Pos_ERSATZ_NR;
			return FALSE;
		}
	}

	// AWL1, Aktivkennzeichen 
	if ( m_pBufZartikel->AWL1 == 0 &&
		 *m_pBufZartikel->AWL_AKTIV != 'N' )
	{
		if ( bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_AWL1_SET) );

		*ind = m_Pos_AWL_AKTIV;
		return FALSE;
	}

	// bei BTM-Artikeln darf im numerischen Teil der Einheit kein ',' oder 'X' sein
	if (*m_pBufZartikel->BTM == '1')
	{
		CString csEinheit;
		int iIndex = 0;
		csEinheit.Format("%s", m_pBufZartikel->EINHEIT);

		// Index des letzten numerischen Zeichens ermitteln
		int j;

		for (char c = '0'; c <= '9'; c++)
		{
			j = csEinheit.ReverseFind(c);
		
			if (j > iIndex)
			{
				iIndex = j;
			}
		}

		csEinheit.Format("%s",csEinheit.Left(iIndex + 1));

		if (csEinheit.Find(',') != -1)
		{
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING10208) );

			*ind = m_Pos_EINHEIT;
			return FALSE;
		}
	}

	// in D und CH darf das AH-Datum bei einem Steller-Artikel nicht gelöscht werden, wenn Elemente noch AH sind
	if ((IsCountry("CH") || IsCountry("D")) && 
		 m_pBufZartikel->STELLER[0] == 'S' &&
		 m_pBufOld->zartikel.DATUM_AH > 0 &&
		 m_pBuf->zartikel.DATUM_AH == 0)
	{
		long l;
        CStellerUpdate StellUpd;

		l = StellUpd.StellerArtikelAHLoeschung (m_pBufZartikel, cErrMeldung );

		if (l > 0)
			cErrMeldung.Format(CResString::ex().getStrTblText(IDS_STRING10281), l);

		if (l != 0)
		{
			if ( bMeldung )
				MsgBoxOK( cErrMeldung );

			*ind = m_Pos_DATUM_AH;
			return FALSE;
		}
	}

	// Preise
	int i;
	int AnzEnabled;	
	char cMWST;

	AnzEnabled = 0;
	for ( i = 0; i < NUMBER_OF_PRICE_ON_PAGE1; i++ )
		if ( m_bPreisEnabled[i] ) AnzEnabled++;

	// bei Neuanlagen muss zwingend ein Preissatz mit Datum "morgen" existieren, sonst Probleme im KSC ( I-14015316 )
	if ( ((CArtikelView* )m_pView)->IsNeuanlage() )
	{
		i = 0;
		
		while ( i < NUMBER_OF_PRICE_ON_PAGE1 )
		{
			if (m_pBufArtpreis[i]->DATUMGUELTIGAB == AddDayToPhoDate( ::Today(), 1 ))
				break; // Preissatz mit Datum morgen gefunden

			i++;
		}

		if (i == NUMBER_OF_PRICE_ON_PAGE1) // kein Preissatz mit Datum morgen gefunden
		{
		
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING71) );	

			*ind = m_Pos_PREIS[0] + OFFS_GUELAB;
			return FALSE;
		}
	}

	// wenn mwst-kennz geaendert, dann muss ein Preisdatum eingegeben sein
	i = 0;
	while ( i < NUMBER_OF_PRICE_ON_PAGE1 && m_bPreisEnabled[i] )
	{
		if ( !MWST_NeuGleichAlt( *m_pBufArtpreis[i]->KE_MWST,
								 *m_pBufOldArtpreis[i]->KE_MWST ) &&
			 m_pBufArtpreis[i]->DATUMGUELTIGAB == 0 )
		{
			if ( !bMeldung )
			{
				if (MsgBoxYesNo( CResString::ex().getStrTblText(IDS_TAKE_PRICE) ) == IDYES)
				{
					cMWST = m_pBufArtpreis[i]->KE_MWST[0];
					*m_pBufArtpreis[i] = *m_pBufArtpreis[i+1];
					m_pBufArtpreis[i]->KE_MWST[0] = cMWST;
					m_pBufArtpreis[i]->DATUMGUELTIGAB = AddDayToPhoDate( ::Today(), 1 );

					// ggfs. AVP neu berechnen
					Set_Taxe_AVP(i);

					m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[i] + OFFS_GUELAB, m_Pos_PREIS[i] + OFFS_HPROZ );
				}
				else
				{
					*ind = m_Pos_PREIS[0] + OFFS_GUELAB;
					return FALSE;
				}
			}
			else
			{
				MsgBoxOK( CResString::ex().getStrTblText(IDS_ENTER_PRICE) );	
				*ind = m_Pos_PREIS[0] + OFFS_GUELAB;
				return FALSE;
			}
		}

		 i++;
	}

	// wenn Taxkennzeichen geaendert auf Taxartikel = ja
	// dann muss ein neuer Preis eingegeben werden
//	if ( ! NeuGleichAlt( *m_pBufZartikel->TAXPFL,
//						 *m_pBufOldZartikel->TAXPFL ) &&
//		  *m_pBufZartikel->TAXPFL == '1' )


	if ( ! TAXE_NeuGleichAlt( *m_pBufZartikel->TAXPFL,				// OTCX_RX
						      *m_pBufOldZartikel->TAXPFL ) &&
		  *m_pBufZartikel->TAXPFL != '0' )
	{
		i = 0;
		while ( i < NUMBER_OF_PRICE_ON_PAGE1 &&
				m_bPreisEnabled[i]  &&
				m_pBufArtpreis[i]->DATUMGUELTIGAB == 0 ) i++;
		if ( i == AnzEnabled ) 
		{
			if ( bMeldung )
			{
//				AfxMessageBox( CResString::ex().getStrTblText(IDS_CHANGE_TAX_JA) );

				if (IsCountry("A"))
				{
					if ( *m_pBufZartikel->TAXPFL == '1' )	
					MsgBoxOK( CResString::ex().getStrTblText(IDS_CHANGE_TAX_CH) );	

					if ( *m_pBufZartikel->TAXPFL == '2' )	
					MsgBoxOK( CResString::ex().getStrTblText(IDS_CHANGE_TAX_VT) );	

					if ( *m_pBufZartikel->TAXPFL == '3' )	
					MsgBoxOK( CResString::ex().getStrTblText(IDS_CHANGE_TAX_HO) );	

					if ( *m_pBufZartikel->TAXPFL == '4' )	
					MsgBoxOK( CResString::ex().getStrTblText(IDS_CHANGE_TAX_KF) );	
				}
				else
				{
					if ( *m_pBufZartikel->TAXPFL == '1' )				// OTCX_RX
						MsgBoxOK( CResString::ex().getStrTblText(IDS_CHANGE_TAX_OTCX) );	
					//else if ( *m_pBufZartikel->TAXPFL == '3' )
					//	MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1237) );
					else
						MsgBoxOK( CResString::ex().getStrTblText(IDS_CHANGE_TAX_RX) );	
				}
			}

			*ind = m_Pos_PREIS[0] + OFFS_GUELAB;
			return FALSE;
		}
	}
	// wenn Preis0Artikel geaendert auf Preis0Artikel = nein
	// dann muss ein neuer Preis eingegeben werden
	if ( ! NeuGleichAlt( *m_pBufZartikel->PREIS0ARTIKEL,
						 *m_pBufOldZartikel->PREIS0ARTIKEL ) &&
		  *m_pBufZartikel->PREIS0ARTIKEL == '0' )
	{
		i = 0;
		while ( i < NUMBER_OF_PRICE_ON_PAGE1 &&
				m_bPreisEnabled[i]  &&
				m_pBufArtpreis[i]->DATUMGUELTIGAB == 0 ) i++;
		if ( i == AnzEnabled ) 
		{
			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING255) );	
			*ind = m_Pos_PREIS[0] + OFFS_GUELAB;
			return FALSE;
		}
	}

	// PreisTest
	for ( i = 0; i < NUMBER_OF_PRICE_ON_PAGE1; i++ )
	{
		if ( m_bPreisEnabled[i] && m_pBufArtpreis[i]->DATUMGUELTIGAB > 0 )
		{	
			if ( !Test_Preis( i, ind, cErrMeldung ) )
			{
				if ( bMeldung )
					MsgBoxOK( cErrMeldung );
				return FALSE;
			}
		}
	}

	// PreisTest wenn Artikel entsperrt wird (Deutschland) oder alle anderen Länder generell
	if (( m_pOLD_ARTIKEL_GESPERRT[0] == '1' || !IsCountry("D") ) &&
		  m_pBufZartikel->ARTIKEL_GESPERRT[0] == '0')
	{
		i = 0;
		while ( i < NUMBER_OF_PRICE_ON_PAGE1 &&
				m_bPreisEnabled[i]  &&
				m_pBufArtpreis[i]->DATUMGUELTIGAB == 0 ) i++;
		if ( i > 0 && i == AnzEnabled && i < NUMBER_OF_PRICE_ON_PAGE1 ) 
		{
			if ( !Test_Preis( i, ind, cErrMeldung ) )
			{
				*ind = m_Pos_PREIS[i-1] + OFFS_GUELAB;
				if ( bMeldung )
				{
					CString Meld;
					Meld  = cErrMeldung;
					Meld += CResString::ex().getStrTblText(IDS_STRING258);
					Meld += CResString::ex().getStrTblText(IDS_STRING259);
					MsgBoxOK( Meld );
				}

				return FALSE;
			}
		}
	}
	if (((CEkZdpApp*)AfxGetApp())->GetMedActorParameter() == MedActor_Parameter::OneToOne)
	{
		StoreMedicalActor_OneToOne();
	}
	if (((CEkZdpApp*)AfxGetApp())->GetMedActorParameter() == MedActor_Parameter::OneToN)
	{
		StoreMedicalActor_OneToN();
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////
// folgendes Problem
// die MWST-Felder werden automatisch auf den Defaultwert korrigiert,
// wenn sie falsch sind.
// falsche Feldinhalte muessen daher beruecksichtigt werden
// OTCX_RX

bool CArtikelPage1::TAXE_NeuGleichAlt( char neu, char alt )
{
	if (IsCountry("A"))
	{
		if ( !( alt == '0' || alt == '1' || alt == '2' || alt == '3' || alt == '4' ) ) alt = '0';
		if ( !( neu == '0' || neu == '1' || neu == '2' || neu == '3' || neu == '4' ) ) neu = '0';
	}
	else
	{
		if ( !( alt == '0' || alt == '1' || alt == '2' || alt == '3' ) ) alt = '0';
		if ( !( neu == '0' || neu == '1' || neu == '2' || neu == '3' ) ) neu = '0';
	}

	return alt == neu;
}

/////////////////////////////////////////////////////////////////////
// folgendes Problem
// die MWST-Felder werden automatisch auf den Defaultwert korrigiert,
// wenn sie falsch sind.
// falsche Feldinhalte muessen daher beruecksichtigt werden

bool CArtikelPage1::MWST_NeuGleichAlt( char neu, char alt )
{
	if (IsCountry("F"))
	{
		if ( !( alt == '0' || alt == '1' || alt == '2' || alt == '3' ) ) alt = '0';
		if ( !( neu == '0' || neu == '1' || neu == '2' || neu == '3' ) ) neu = '0';
	}
	else if (IsCountry("HR"))
	{
		if ( !( alt == '0' || alt == '1' ) ) alt = '0';
		if ( !( neu == '0' || neu == '1' ) ) neu = '0';
	}
	else
	{
		if ( !( alt == '0' || alt == '1' || alt == '2' ) ) alt = '0';
		if ( !( neu == '0' || neu == '1' || neu == '2' ) ) neu = '0';
	}

	return alt == neu;
}

/////////////////////////////////////////////////////////////////////
// folgendes Problem
// die Checkbox-Felder werden automatisch auf den Defaultwert korrigiert,
// wenn sie falsch sind.
// falsche Feldinhalte muessen daher beruecksichtigt werden

bool CArtikelPage1::NeuGleichAlt( char neu, char alt )
{
	if ( !( alt == '0' || alt == '1') ) alt = '0';
	if ( !( neu == '0' || neu == '1') ) neu = '0';
	return alt == neu;
}

bool CArtikelPage1::AenderungsHinweis( CString &cMeld )
{
	// wenn Preise (Preisdatum !!!) geaendert, dann kein weiterer Test

	int i;
	i = 0;
	while ( i < NUMBER_OF_PRICE_ON_PAGE1 && 
		    m_pBufArtpreis[i]->DATUMGUELTIGAB == 
			m_pBufOldArtpreis[i]->DATUMGUELTIGAB                &&
			::DoCompare( m_pBufArtpreis[i]->GROSSO,
			 			 m_pBufOldArtpreis[i]->GROSSO, 2 ) == 0 &&
			::DoCompare( m_pBufArtpreis[i]->AEP,
			 			 m_pBufOldArtpreis[i]->AEP, 2 )    == 0 &&
			::DoCompare( m_pBufArtpreis[i]->AVP,
			 			 m_pBufOldArtpreis[i]->AVP, 2 )    == 0    ) i++; 
	if ( i < NUMBER_OF_PRICE_ON_PAGE1 ) return false;

	// Hinweis wenn Taxkennzeichen geaendert
//	if ( ! NeuGleichAlt( *m_pBufZartikel->TAXPFL,
//						 *m_pBufOldZartikel->TAXPFL  ) )
	if ( ! TAXE_NeuGleichAlt( *m_pBufZartikel->TAXPFL,				// OTCX_RX
						      *m_pBufOldZartikel->TAXPFL  ) )
	{
		cMeld = CResString::ex().getStrTblText(IDS_STRING260); 
		return true;
	}
	// Hinweis wenn Preis0Artikel geaendert
	else if ( ! NeuGleichAlt( *m_pBufZartikel->PREIS0ARTIKEL,
							  *m_pBufOldZartikel->PREIS0ARTIKEL  ) )
	{
		cMeld = CResString::ex().getStrTblText(IDS_STRING261); 
		return true;
	}
	// Hinweis wenn TaxPruefGrosso geaendert
	else if ( ! NeuGleichAlt( *m_pBufZartikel->TAXPRUEFGROSSO,
							  *m_pBufOldZartikel->TAXPRUEFGROSSO  ) )
	{
		cMeld = CResString::ex().getStrTblText(IDS_STRING262); 
		return true;
	}
	// Hinweis wenn nicht ueber GH
	else if ( ! NeuGleichAlt( *m_pBufZartikel->NICHTUEBERGH,
							  *m_pBufOldZartikel->NICHTUEBERGH  ) ) 
	{
		// nicht in der Schweiz gewünscht 
		if (!IsCountry("CH"))
		{
			cMeld = CResString::ex().getStrTblText(IDS_STRING263); 
			return true;
		}
	}

	// Rezeptpflichtig / Rabattfaehig 
	// ( Rezeptpflichtig = nein -> Rabattfaehig != 00
	if (IsCountry("D"))
	{
		if ( *m_pBufZartikel->REZEPTPFL == '0'	&&	// OTCX_RX
			strcmp( m_pBufZartikel->RABATTFAEHIG, "00" ) != 0 )
		{
			cMeld = CResString::ex().getStrTblText(IDS_STRING264);
			return true;
		}
	}

	return false;
}

/////////////////////////////////////////////////////////////
//  Dialogfelder

void CArtikelPage1::InitPflege( CWnd *pView  )
{
	int i;
	CArtikelPage1* pThisView = this;
	m_pView = pView;

	// Adressen des aktuellen Inhaltes
	m_pBuf				= ((CArtikelView* )pView)->GetBuffer();
	m_pBufZartikel		= &m_pBuf->zartikel;  
	m_pBufEan			= &m_pBuf->ean;
	m_pBufZartfeb2		= &m_pBuf->zartfeb2;
	m_pBufCarticlelang  = &m_pBuf->carticlelang;
	m_pBufZartcroatia	= &m_pBuf->zartcroatia;
	m_pBufVertriebsClub = &m_pBuf->zartwg[14];		// art = 'F'

	for ( i = 0; i < NUMBER_OF_PRICE_ON_PAGE1 ; i++ )
		m_pBufArtpreis[i] = &m_pBuf->artpreis[i];

	// Adressen des alten Inhaltes 
	m_pBufOld         = ((CArtikelView* )pView)->GetOldBuffer();
	m_pBufOldZartikel = &m_pBufOld->zartikel; 
	for ( i = 0; i < NUMBER_OF_PRICE_ON_PAGE1 ; i++ )
		m_pBufOldArtpreis[i] = &m_pBufOld->artpreis[i];
	
	// Adresse des alten Inhaltes von ARTIKEL_GESPERRT
	m_pOLD_ARTIKEL_GESPERRT = m_pBufOldZartikel->ARTIKEL_GESPERRT;

	// Init Preistyp
	m_pBuf->sPreistyp = 0;

	// Taxtabelle
	m_pTaxTb = ((CArtikelView* )pView)->m_pTaxTb;

	MakeDialog();

	m_ARTIKEL_NAME.SetMask	(ED_CHAR,
                             ED_UPPER,
                             m_pBufZartikel->ARTIKEL_NAME,
                             L_ZARTIKEL_ARTIKEL_NAME,
							 new ChMaskChar,
							 new CV_ARTIKEL_Name( m_pBufZartikel,
												  (CArtikelView *)m_pView ) );

	m_EINHEIT.SetMask		(ED_CHAR,
                             ED_UPPER | ED_RIGHT,
                             m_pBufZartikel->EINHEIT,
                             L_ZARTIKEL_EINHEIT,
							 new ChMaskChar,
			  	        	 new CV_ARTIKEL_Einheit( pThisView, 
													(CArtikelView *)m_pView ) );

//  Hintergrund gelb ( Test )
//	m_EINHEIT.SetColor( -1,  RGB( 255, 255, 0 ), -1, -1, -1, -1 );

	// in der Schweiz keine Prüfung der Darreichform auf Seite 1 (passiert auf Seite 5)
	if (IsCountry("CH"))
	{
		m_DARREICHFORM.SetMask	(ED_CHAR,
								ED_UPPER,
								m_pBufZartikel->DARREICHFORM,
								L_ZARTIKEL_DARREICHFORM,
								new ChMaskChar );
	}
	else
	{
		m_DARREICHFORM.SetMask	(ED_CHAR,
								ED_UPPER,
								m_pBufZartikel->DARREICHFORM,
								L_ZARTIKEL_DARREICHFORM,
								new ChMaskChar,
								new CV_ARTIKEL_Dform( pThisView, 
													(CArtikelView *)m_pView ) );
	}
							 
	m_BTM_FAKTOR.SetMask	 (ED_DBL,
                              ED_NORMAL,
                              &m_pBufZartikel->BTM_FAKTOR,
                              L_ZARTIKEL_BTM_FAKTOR + 1,
                              N_ZARTIKEL_BTM_FAKTOR,
                              new ChMaskDblPos );

	// bei PWSAT dürfen auch kleine Buchstaben in Artikel-Langname eingegeben werden
	if (IsCountry("A") && IsPrewhole())
	{
		m_ARTIKEL_LANGNAME.SetMask(ED_CHAR,
								ED_NORMAL,
								m_pBufZartikel->ARTIKEL_LANGNAME,
								L_ZARTIKEL_ARTIKEL_LANGNAME,
								new ChMaskChar );
	}
	else
	{
		m_ARTIKEL_LANGNAME.SetMask(ED_CHAR,
								ED_UPPER,
								m_pBufZartikel->ARTIKEL_LANGNAME,
								L_ZARTIKEL_ARTIKEL_LANGNAME,
								new ChMaskChar );
	}
			  	    
	m_ERSATZ_CODE.SetMask(ED_CHAR,
						 ED_UPPER,
						 m_ERSATZ_ARTCODE,
						 L_CARTICLECODES_ARTICLE_CODE,
						 new ChMaskChar,
						 new CV_ARTIKEL_KettArtikel( m_pBufZartikel,
														 pThisView ) );

	m_ERSATZ_NR.SetMask		(ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartikel->ERSATZ_NR,
                             L_ARTIKEL_NR,
							 new ChMaskNum,
							 new CV_ARTIKEL_KettArtikel( m_pBufZartikel,
														 pThisView ) );

	m_HERSTELLER_NR.SetMask	(ED_LONG,
						     ED_NORMAL,
							 &m_pBufZartikel->HERSTELLER_NR,
							 L_HERSTELLER_NR,
							 new ChMaskNum,
							 new CV_ARTIKEL_Hersteller( pThisView ) );

	m_PB_SEKBEZ.SetMask		( IDB_BM_SEKBEZ, new CBitmap, NULL );
	m_PB_PRICES.SetMask		( IDB_BM_COINS, new CBitmap, NULL );

	m_EAN_NR.SetMask		(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufEan->EAN_NR,
				             L_EAN_EAN_NR,
						     new ChMaskNum,
							 new CV_ARTIKEL_EanNr( m_pBufEan ));

	m_LAUFZEITMONATE.SetMask(ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartikel->LAUFZEITMONATE,
                             3,
							 new ChMaskNum );

	m_WARNTAGEVORVERF.SetMask(ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartikel->WARNTAGEVORVERF,
                             3,
							 new ChMaskNum );

	m_ARTIKEL_NR_HERST.SetMask(ED_CHAR,
		                       ED_UPPER,
			                   m_pBufZartikel->ARTIKEL_NR_HERST,
				               L_ZARTIKEL_ARTIKEL_NR_HERST,
							   new ChMaskChar );
			  	    
	m_RABATTFAEHIG.SetMask	("000102030411121314" , 2,
							 m_pBufZartikel->RABATTFAEHIG, 0 );   

	m_ZUZAHLUNG_IFA.SetMask(ED_CHAR,
		                    ED_NORMAL,
			                m_pBufZartikel->ZUZAHLUNG_IFA,
				            L_ZARTIKEL_ZUZAHLUNG_IFA,
						    new ChMaskNum,
							new CV_ARTIKEL_Zuzahlung( pThisView ) );

	m_ERSATZ_NR_AKTIV.SetMask('1', '0', m_pBufZartikel->ERSATZ_NR_AKTIV );
	m_EAN_NICHT_VORHANDEN.SetMask('1', '0', m_pBufZartikel->EAN_NICHTVORHANDEN );
	m_TAXPFL.SetMask		("012",    m_pBufZartikel->TAXPFL, 0  );	// Taxe OTCX_RX
	m_REZEPTPFL.SetMask		('1', '0', m_pBufZartikel->REZEPTPFL   );
	m_APOTHEKENPFL.SetMask	('1', '0', m_pBufZartikel->APOTHEKENPFL  );
	m_BTM.SetMask			('1', '0', m_pBufZartikel->BTM  );
	m_TIERARZNEI.SetMask	('1', '0', m_pBufZartikel->TIERARZNEI  );
	m_NETTOARTIKEL.SetMask	('1', '0', m_pBufZartikel->NETTOARTIKEL  );
	m_NICHTUEBERGH.SetMask	('1', '0', m_pBufZartikel->NICHTUEBERGH );
	m_KLINIKPACK.SetMask	('1', '0', m_pBufZartikel->KLINIKPACKUNG  );
	m_NURKVA.SetMask		('1', '0', m_pBufZartikel->NURKVA  );

	m_VERTRBIND_IFA.SetMask	('1', '0', m_pBufZartikel->VERTRBIND_IFA );

	m_SKONTOFAEHIG.SetMask	('1', '0', m_pBufZartikel->SKONTOFAEHIG );
	m_RETOURENSPERRE.SetMask('1', '0', m_pBufZartikel->RETOURENSPERRE );

	m_KUEHLARTIKEL.SetMask	("03214",		m_pBufZartikel->KUEHLARTIKEL, 0 ); // default value - overwritten if any entry found in ccoollevel

//	m_VERFALL.SetMask		("0123",		m_pBufZartikel->VERFALL, 0 );   
	m_VERFALL.SetMask		("012",			m_pBufZartikel->VERFALL, 0 );   

	m_MEDCANGES.SetMask		("012",			&m_pBufZartikel->MED_CANNABIS_GES);

	m_VERTRBIND.SetMask		(" ABCDEFG",	m_pBufZartikel->VERTRBIND, 0 );   
	m_SONDERGROSSO.SetMask  (" SPREA",		m_pBufZartikel->SONDERGROSSO, 0 );

	// TEST-BG auf anderer DB: Preistyp generell 0/1
	if (IsCountry("BG"))
		m_PREISTYP.SetMask		("01",			&m_pBuf->sPreistyp ); 
	else
		m_PREISTYP.SetMask		("0",			&m_pBuf->sPreistyp ); 

	m_DATUM_AH.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufZartikel->DATUM_AH,
                             L_LDATUM,
                             new ChMaskLDate,
							 new CV_ARTIKEL_DatumAh( pThisView ) );

	m_DATUM_RR.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufZartikel->DATUM_RR,
                             L_LDATUM,
                             new ChMaskLDate);

	m_DATUM_AV.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufZartikel->DATUM_AV,
                             L_LDATUM,
                             new ChMaskLDate);

	m_TAXPRUEFGROSSO.SetMask  ('1', '0', m_pBufZartikel->TAXPRUEFGROSSO );
	m_PREIS0ARTIKEL.SetMask   ('1', '0', m_pBufZartikel->PREIS0ARTIKEL  );
	m_SOMMER_KK.SetMask       ('1', '0', m_pBufZartikel->SOMMER_KK      );
	m_ARTIKEL_GESPERRT.SetMask('1', '0', m_pBufZartikel->ARTIKEL_GESPERRT );

	m_GUELAB1.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufArtpreis[0]->DATUMGUELTIGAB,
                             L_LDATUM,
                             new ChMaskLDate,
							 new CV_ARTIKEL_PreisDatum( 0, pThisView ) );

	m_GUELAB2.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufArtpreis[1]->DATUMGUELTIGAB,
                             L_LDATUM,
                             new ChMaskLDate,
							 new CV_ARTIKEL_PreisDatum( 1, pThisView ) );

	m_GUELAB3.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufArtpreis[2]->DATUMGUELTIGAB,
                             L_LDATUM,
                             new ChMaskLDate,
							 new CV_ARTIKEL_PreisDatum( 2, pThisView ) );

	m_GUELAB4.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufArtpreis[3]->DATUMGUELTIGAB,
                             L_LDATUM,
                             new ChMaskLDate);
							 // CV_ARTIKEL_PreisDatum fehlt hier !!!!!!!!!!
							 // 5. Preis lesen !!!!!!!

	m_GROSSO1.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[0]->GROSSO,
                             L_ZARTPREIS_GROSSO + 1,
                             N_ZARTPREIS_GROSSO,
                             new ChMaskDblPos,
							 new CV_ARTIKEL_Taxe_AEP( 0, pThisView ) );

	m_GROSSO2.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[1]->GROSSO,
                             L_ZARTPREIS_GROSSO + 1,
                             N_ZARTPREIS_GROSSO,
                             new ChMaskDblPos,
							 new CV_ARTIKEL_Taxe_AEP( 1, pThisView ) );

	m_GROSSO3.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[2]->GROSSO,
                             L_ZARTPREIS_GROSSO + 1,
                             N_ZARTPREIS_GROSSO,
                             new ChMaskDblPos,
							 new CV_ARTIKEL_Taxe_AEP( 2, pThisView ) );

	m_GROSSO4.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[3]->GROSSO,
                             L_ZARTPREIS_GROSSO + 1,
                             N_ZARTPREIS_GROSSO,
                             new ChMaskDblPos,
							 new CV_ARTIKEL_Taxe_AEP( 3, pThisView ) );

	//if ((IsCountry("CH") == TRUE) && (IsAGP() == TRUE)) // only to differentiate between prewhole and wholesale
	if ((IsCountry("CH") == TRUE) && (IsPrewhole() == FALSE))
	{
		m_ArtikelPreis2_1.SetMask(ED_DBL,
			ED_NORMAL,
			&m_pBufArtpreis[0]->AGP,
			L_ZARTPREIS_AGP + 1,
			N_ZARTPREIS_AGP,
			new ChMaskDblPos);

		m_ArtikelPreis2_2.SetMask(ED_DBL,
			ED_NORMAL,
			&m_pBufArtpreis[1]->AGP,
			L_ZARTPREIS_AGP + 1,
			N_ZARTPREIS_AGP,
			new ChMaskDblPos);

		m_ArtikelPreis2_3.SetMask(ED_DBL,
			ED_NORMAL,
			&m_pBufArtpreis[2]->AGP,
			L_ZARTPREIS_AGP + 1,
			N_ZARTPREIS_AGP,
			new ChMaskDblPos);

		m_ArtikelPreis2_4.SetMask(ED_DBL,
			ED_NORMAL,
			&m_pBufArtpreis[3]->AGP,
			L_ZARTPREIS_AGP + 1,
			N_ZARTPREIS_AGP,
			new ChMaskDblPos);
	}
	else
	{
		m_ArtikelPreis2_1.SetMask(ED_DBL,
			ED_NORMAL,
			&m_pBufArtpreis[0]->AEP,
			L_ZARTPREIS_AEP + 1,
			N_ZARTPREIS_AEP,
			new ChMaskDblPos,
			new CV_ARTIKEL_Taxe_AVP(0, pThisView));

		m_ArtikelPreis2_2.SetMask(ED_DBL,
			ED_NORMAL,
			&m_pBufArtpreis[1]->AEP,
			L_ZARTPREIS_AEP + 1,
			N_ZARTPREIS_AEP,
			new ChMaskDblPos,
			new CV_ARTIKEL_Taxe_AVP(1, pThisView));

		m_ArtikelPreis2_3.SetMask(ED_DBL,
			ED_NORMAL,
			&m_pBufArtpreis[2]->AEP,
			L_ZARTPREIS_AEP + 1,
			N_ZARTPREIS_AEP,
			new ChMaskDblPos,
			new CV_ARTIKEL_Taxe_AVP(2, pThisView));

		m_ArtikelPreis2_4.SetMask(ED_DBL,
			ED_NORMAL,
			&m_pBufArtpreis[3]->AEP,
			L_ZARTPREIS_AEP + 1,
			N_ZARTPREIS_AEP,
			new ChMaskDblPos,
			new CV_ARTIKEL_Taxe_AVP(3, pThisView));
	}
	if (IsCountry("CH"))
	{
		m_EAVP1.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[0]->LIEFERBASISPREIS,
								L_ZARTPREIS_LIEFERBASISPREIS + 1,
								N_ZARTPREIS_LIEFERBASISPREIS,
								new ChMaskDblPos,
								new CV_ARTIKEL_Proz_LBP( 0, pThisView ));

		m_EAVP2.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[1]->LIEFERBASISPREIS,
								L_ZARTPREIS_LIEFERBASISPREIS + 1,
								N_ZARTPREIS_LIEFERBASISPREIS,
								new ChMaskDblPos,
								new CV_ARTIKEL_Proz_LBP( 1, pThisView ));

		m_EAVP3.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[2]->LIEFERBASISPREIS,
								L_ZARTPREIS_LIEFERBASISPREIS + 1,
								N_ZARTPREIS_LIEFERBASISPREIS,
								new ChMaskDblPos,
								new CV_ARTIKEL_Proz_LBP( 2, pThisView ));

		m_EAVP4.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[3]->LIEFERBASISPREIS,
								L_ZARTPREIS_LIEFERBASISPREIS + 1,
								N_ZARTPREIS_LIEFERBASISPREIS,
								new ChMaskDblPos,
								new CV_ARTIKEL_Proz_LBP( 3, pThisView ));
	}
	else if (IsCountry("F"))
	{
		m_EAVP1.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[0]->MAXAEP,
								L_ZARTPREIS_MAXAEP + 1,
								N_ZARTPREIS_MAXAEP,
								new ChMaskDblPos );

		m_EAVP2.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[1]->MAXAEP,
								L_ZARTPREIS_MAXAEP + 1,
								N_ZARTPREIS_MAXAEP,
								new ChMaskDblPos );

		m_EAVP3.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[2]->MAXAEP,
								L_ZARTPREIS_MAXAEP + 1,
								N_ZARTPREIS_MAXAEP,
								new ChMaskDblPos );

		m_EAVP4.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[3]->MAXAEP,
								L_ZARTPREIS_MAXAEP + 1,
								N_ZARTPREIS_MAXAEP,
								new ChMaskDblPos );
	}
	else
	{
		m_EAVP1.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[0]->EAVP,
								L_ZARTPREIS_EAVP + 1,
								N_ZARTPREIS_EAVP,
								new ChMaskDblPos );

		m_EAVP2.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[1]->EAVP,
								L_ZARTPREIS_EAVP + 1,
								N_ZARTPREIS_EAVP,
								new ChMaskDblPos );

		m_EAVP3.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[2]->EAVP,
								L_ZARTPREIS_EAVP + 1,
								N_ZARTPREIS_EAVP,
								new ChMaskDblPos );

		m_EAVP4.SetMask		    (ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[3]->EAVP,
								L_ZARTPREIS_EAVP + 1,
								N_ZARTPREIS_EAVP,
								new ChMaskDblPos );
	}

	if (IsCountry("D"))
	{
		m_MAXAVP1.SetMask		(ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[0]->ERSTATTBETRAG,
								L_ZARTPREIS_ERSTATTBETRAG + 1,
								N_ZARTPREIS_ERSTATTBETRAG,
								new ChMaskDblPos,
								new CV_ARTIKEL_Erstatt_Abzug( 0, pThisView ));

		m_MAXAVP2.SetMask		(ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[1]->ERSTATTBETRAG,
								L_ZARTPREIS_ERSTATTBETRAG + 1,
								N_ZARTPREIS_ERSTATTBETRAG,
								new ChMaskDblPos,
								new CV_ARTIKEL_Erstatt_Abzug( 1, pThisView ));

		m_MAXAVP3.SetMask		(ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[2]->ERSTATTBETRAG,
								L_ZARTPREIS_ERSTATTBETRAG + 1,
								N_ZARTPREIS_ERSTATTBETRAG,
								new ChMaskDblPos,
								new CV_ARTIKEL_Erstatt_Abzug( 2, pThisView ));

		m_MAXAVP4.SetMask		(ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[3]->ERSTATTBETRAG,
								L_ZARTPREIS_ERSTATTBETRAG + 1,
								N_ZARTPREIS_ERSTATTBETRAG,
								new ChMaskDblPos,
								new CV_ARTIKEL_Erstatt_Abzug( 3, pThisView ));
	}
	else
	{
		m_MAXAVP1.SetMask		(ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[0]->MAXAVP,
								L_ZARTPREIS_MAXAVP + 1,
								N_ZARTPREIS_MAXAVP,
								new ChMaskDblPos );

		m_MAXAVP2.SetMask		(ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[1]->MAXAVP,
								L_ZARTPREIS_MAXAVP + 1,
								N_ZARTPREIS_MAXAVP,
								new ChMaskDblPos );

		m_MAXAVP3.SetMask		(ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[2]->MAXAVP,
								L_ZARTPREIS_MAXAVP + 1,
								N_ZARTPREIS_MAXAVP,
								new ChMaskDblPos );

		m_MAXAVP4.SetMask		(ED_DBL,
								ED_NORMAL,
								&m_pBufArtpreis[3]->MAXAVP,
								L_ZARTPREIS_MAXAVP + 1,
								N_ZARTPREIS_MAXAVP,
								new ChMaskDblPos );
	}

	m_AVP1.SetMask		    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[0]->AVP,
                             L_ZARTPREIS_AVP + 1,
                             N_ZARTPREIS_AVP,
                             new ChMaskDblPos );

	m_AVP2.SetMask		    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[1]->AVP,
                             L_ZARTPREIS_AVP + 1,
                             N_ZARTPREIS_AVP,
                             new ChMaskDblPos );

	m_AVP3.SetMask		    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[2]->AVP,
                             L_ZARTPREIS_AVP + 1,
                             N_ZARTPREIS_AVP,
                             new ChMaskDblPos );

	m_AVP4.SetMask		    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[3]->AVP,
                             L_ZARTPREIS_AVP + 1,
                             N_ZARTPREIS_AVP,
                             new ChMaskDblPos );

	m_HPROZ1.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[0]->HERST_PROZENT,
                             L_ZARTPREIS_HERST_PROZENT + 2,
                             N_ZARTPREIS_HERST_PROZENT,
                             new ChMaskDbl );

	m_HPROZ2.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[1]->HERST_PROZENT,
                             L_ZARTPREIS_HERST_PROZENT + 2,
                             N_ZARTPREIS_HERST_PROZENT,
                             new ChMaskDbl );

	m_HPROZ3.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[2]->HERST_PROZENT,
                             L_ZARTPREIS_HERST_PROZENT + 2,
                             N_ZARTPREIS_HERST_PROZENT,
                             new ChMaskDbl );

	m_HPROZ4.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtpreis[3]->HERST_PROZENT,
                             L_ZARTPREIS_HERST_PROZENT + 2,
                             N_ZARTPREIS_HERST_PROZENT,
                             new ChMaskDbl );

	m_HERST_PROZENT.SetMask (ED_DBL,
                             ED_NORMAL,
                             &m_pBufZartikel->HERST_PROZENT,
                             L_ZARTIKEL_HERST_PROZENT + 2,
                             N_ZARTIKEL_HERST_PROZENT,
                             new ChMaskDbl,
							 new CV_ARTIKEL_Herst_Prozent( pThisView ) );

	m_TFG.SetMask("012", m_pBufZartikel->TFG, 0);

	m_DISC_DED_YET1.SetMask("0123", 1, &m_pBufArtpreis[0]->DISC_DEDUCED_YET, 0);
	m_DISC_DED_YET2.SetMask("0123", 1, &m_pBufArtpreis[1]->DISC_DEDUCED_YET, 0);
	m_DISC_DED_YET3.SetMask("0123", 1, &m_pBufArtpreis[2]->DISC_DEDUCED_YET, 0);
	m_DISC_DED_YET4.SetMask("0123", 1, &m_pBufArtpreis[3]->DISC_DEDUCED_YET, 0);
	
	m_MWST1.SetMask("012", m_pBufArtpreis[0]->KE_MWST, 0);
	m_MWST2.SetMask("012", m_pBufArtpreis[1]->KE_MWST, 0);
	m_MWST3.SetMask("012", m_pBufArtpreis[2]->KE_MWST, 0);
	m_MWST4.SetMask("012", m_pBufArtpreis[3]->KE_MWST, 0);

	m_PRICEMODEL1.SetMask("0123", &m_pBufArtpreis[0]->PRICEMODEL);
	m_PRICEMODEL2.SetMask("0123", &m_pBufArtpreis[1]->PRICEMODEL);
	m_PRICEMODEL3.SetMask("0123", &m_pBufArtpreis[2]->PRICEMODEL);
	m_PRICEMODEL4.SetMask("0123", &m_pBufArtpreis[3]->PRICEMODEL);

	m_FESTBETRAG1.SetMask	 (ED_DBL,
                              ED_NORMAL,
                              &m_pBufZartikel->FESTBETRAG1,
                              L_ZARTIKEL_FESTBETRAG1 + 1,
                              N_ZARTIKEL_FESTBETRAG1,
                              new ChMaskDblPos );

	m_DATUM_FESTBETRAG1.SetMask(ED_LDATE,
						        ED_NORMAL,
							    &m_pBufZartikel->DATUM_FESTBETRAG1,
								L_LDATUM,
								new ChMaskLDate);

	// jetzt in eigener datei
	m_FESTBETRAG2.SetMask	 (ED_DBL,
                              ED_NORMAL,
                              &m_pBufZartfeb2->FESTBETRAG2,
                              L_ZARTFEB2_FESTBETRAG2 + 1,
                              N_ZARTFEB2_FESTBETRAG2,
                              new ChMaskDblPos );

	m_DATUM_FESTBETRAG2.SetMask(ED_LDATE,
						        ED_NORMAL,
							    &m_pBufZartfeb2->DATUM_FESTBETRAG2,
								L_LDATUM,
								new ChMaskLDate);

	m_FESTBREGEL.SetMask		(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufZartikel->FESTBREGEL,
				                 L_ZARTIKEL_FESTBREGEL,
								 new ChMaskChar,
								 new CV_ARTIKEL_Festbregel( m_pBufZartikel ));

	m_FESTBSTUFE.SetMask		(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufZartikel->STUFE_FESTBETRAG1,
				                 L_ZARTIKEL_STUFE_FESTBETRAG1,
								 new ChMaskChar);

	m_AWL_AKTIV.SetMask ("NJZ", m_pBufZartikel->AWL_AKTIV, 0);

	// in Frankreich muss AWL1 mit Bliefer verknüpft sein, solange dort noch kein Pharmos aktiv ist
	if (IsCountry("F"))
	{
		m_AWL1.SetMask			(ED_LONG,
								ED_NORMAL,
								&m_pBufZartikel->AWL1,
								5,
								new ChMaskNum,
								new CV_ARTIKEL_Awl1_Fr( pThisView ) );
	}
	else
	{
		m_AWL1.SetMask			(ED_LONG,
								ED_NORMAL,
								&m_pBufZartikel->AWL1,
								5,
								new ChMaskNum,
								new CV_ARTIKEL_Awl1( pThisView ) );
	}

	m_AWL2.SetMask			(ED_LONG,
							 ED_NORMAL,
							 &m_pBufZartikel->AWL2,
							 5,
							 new ChMaskNum,
							 new CV_ARTIKEL_Awl2( pThisView ) );

	m_NTIN.SetMask(
					ED_CHAR,
					ED_NORMAL,
					m_pBuf->carticlecodes[21].ARTICLE_CODE,
					25,
					new ChMaskChar
				  );

	m_GTIN.SetMask(
					ED_CHAR,
					ED_NORMAL,
		            m_pBuf->carticlecodes[25].ARTICLE_CODE,
					25,
					new ChMaskChar
				 );

	for (i = 0; i < 4; ++i)
	{
		m_MEDACTORS[i]->SetMask(ED_CHAR,
								ED_NORMAL,
								medactors[i],
								L_CARTMEDACTOR_MEDICALACTOR_ID + 1,
								new ChMaskChar,
								new CV_ARTIKEL_MEDICALACTOR(pThisView, i));
	}
	m_bInitialized = TRUE;

	// Font aendern
//	CArtikelView* pArtView = (CArtikelView* ) pView;
	CEkZdpApp* pApp = (CEkZdpApp*) AfxGetApp();
	m_pConstantFont = pApp->GetConstantFont();
	m_ARTIKEL_NAME.SetFont( m_pConstantFont );

	m_nAuswahlIndex = 0;
	
	if (IsCountry("CH"))
		m_nAuswahlIndex2 = 2;
	else
		m_nAuswahlIndex2 = 0;

	if(IsCountry("A"))
	{
		m_PricesOnPage1 = false;	 // 3RD-VAT
	}
	else
	{
		m_PricesOnPage1 = true;
	}

}
    
/////////////////////////////////////////////////////////////
// ChPflegePage functions 

void CArtikelPage1::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CArtikelPage1::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage1::EnableFields( BOOL bEnab )
{   
	if ( bEnab )
	{
		// neu
		m_dlg.EnableFields( 0, m_Pos_FirstPreisField - 1, bEnab);

		// neu
		m_dlg.EnableFields( m_Pos_LastPreisField + 1, m_nMaxFields - 1, bEnab);

		long tagesdatum;
		int  i;
		tagesdatum = ::Today();

		m_dlg.EnableFields( m_Pos_PREIS[0], m_Pos_PREIS[0]+OFFS_MWST, m_PricesOnPage1 );
		m_bPreisEnabled[0] = TRUE;

		for ( i = 1; i < NUMBER_OF_PRICE_ON_PAGE1 ; i++ )
		{
			if ( m_pBufArtpreis[i]->DATUMGUELTIGAB <= tagesdatum )
			{
				m_dlg.EnableFields( m_Pos_PREIS[i], m_Pos_PREIS[i]+OFFS_MWST, FALSE );
				m_bPreisEnabled[i] = FALSE;
			}
			else
			{
				m_dlg.EnableFields( m_Pos_PREIS[i], m_Pos_PREIS[i]+OFFS_MWST, m_PricesOnPage1 ); 
				m_bPreisEnabled[i] = TRUE;

				// bei noch pflegbarem Preis Mwst-Satz anhand des Preisdatums füllen, falls > 0
				Set_Single_VAT_Rate(i);
			}
			
			// Neu 04.08.2021: der AEP wird in der Schweiz als AGP genutzt, daher bleiben die Felder aktiviert
			// in der Schweiz WHS den AEP generell deaktivieren
			// if (IsCountry("CH") && !IsPrewhole())
			// {
			// 	m_AEP1.EnableWindow(false);
			// 	m_AEP2.EnableWindow(false);
			// 	m_AEP3.EnableWindow(false);
			//  m_AEP4.EnableWindow(false);
			// }
			m_GTIN.EnableWindow(true);
			m_NTIN.EnableWindow(true);
			// EAVP überall außer in Deutschland deaktivieren
			// 07.04.11 in CH steht hier anstelle EAVP der LBP (Lieferantenbasispreis)
			// 02.11.11 in F  steht hier anstelle EAVP der MAXAEP
			if (!IsCountry("D") && !IsCountry("CH") && !IsCountry("F"))
			{
				m_EAVP1.EnableWindow(false);
				m_EAVP2.EnableWindow(false);
				m_EAVP3.EnableWindow(false);
				m_EAVP4.EnableWindow(false);
			}

			if (!IsCountry("D"))
			{
				m_DISC_DED_YET1.EnableWindow(false);
				m_DISC_DED_YET2.EnableWindow(false);
				m_DISC_DED_YET3.EnableWindow(false);
				m_DISC_DED_YET4.EnableWindow(false);
			}

			// Preistyp überall außer in Bulgarien deaktivieren
			if (!IsCountry("BG"))
			{
				// TEST-BG auf anderer DB: Preistyp nicht deaktivieren
				m_PREISTYP.EnableWindow(false);
			}

			// MAXAVP überall außer in Bulgarien + Frankreich deaktivieren
			// In D steht an dieser Stelle ab 2013 der Erstattungsbetrag
			if (!IsCountry("BG") && !IsCountry("F") && !IsCountry("D"))
			{
				m_MAXAVP1.EnableWindow(false);
				m_MAXAVP2.EnableWindow(false);
				m_MAXAVP3.EnableWindow(false);
				m_MAXAVP4.EnableWindow(false);
			}
		}

		m_PRICEMODEL1.EnableWindow(false);
		m_PRICEMODEL2.EnableWindow(false);
		m_PRICEMODEL3.EnableWindow(false);
		m_PRICEMODEL4.EnableWindow(false);

		if (IsCountry("D"))
		{
			m_PRICEMODEL1.EnableWindow(true);

			if ( TRUE == m_bPreisEnabled[1] )
				m_PRICEMODEL2.EnableWindow(true);

			if ( TRUE == m_bPreisEnabled[2] )
				m_PRICEMODEL3.EnableWindow(true);

			if ( TRUE == m_bPreisEnabled[3] )
				m_PRICEMODEL4.EnableWindow(true);
		}

		for ( i = 0; i < NUMBER_OF_PRICE_ON_PAGE1 ; i++ )
			m_dlg.EnableFields( m_Pos_PREIS[i]+OFFS_HPROZ, FALSE ); 

		OnCkEanNichtVorhanden();
	}
	else
	{
		m_dlg.EnableFields( bEnab );	// neu
	}

	// Sekbez nur einmal lesen
	m_bSekbezGelesen = !bEnab;

	// Entsperrter Artikel kann nicht wieder gesperrt werden
//	if ( bEnab && m_pBufZartikel->ARTIKEL_GESPERRT[0] != '1' )
	if ( bEnab && m_pOLD_ARTIKEL_GESPERRT[0] != '1' && (IsCountry("D") || IsCountry("F") || (IsCountry("A") && !IsPrewhole())) )
		m_dlg.EnableFields( m_Pos_ARTIKEL_GESPERRT, FALSE );

	// BTM-Faktor ist immer unsichtbar
	m_BTM_FAKTOR.EnableWindow(false);

	// Länderspezifisches Deaktivieren von Feldern
	if (!IsCountry("D"))
	{
		m_ZUZAHLUNG_IFA.EnableWindow(false);
		m_VERTRBIND.EnableWindow(false);
		m_MEDCANGES.EnableWindow(false);
		m_VERTRBIND_IFA.EnableWindow(false);
	}

	if (IsCountry("CH"))
	{
		m_ARTIKEL_NAME.EnableWindow(false);
		m_EINHEIT.EnableWindow(false);
		m_DARREICHFORM.EnableWindow(false);
		m_ARTIKEL_LANGNAME.EnableWindow(false);
		m_APOTHEKENPFL.EnableWindow(false);
		m_SOMMER_KK.EnableWindow(false);
		// m_TFG.EnableWindow(false); <-- für BatchTracking wieder relevant
		m_NURKVA.EnableWindow(false);
		// m_SKONTOFAEHIG.EnableWindow(false); <-- ab 10/2014 soll das Feld bewusst gepflegt werden
		m_RETOURENSPERRE.EnableWindow(false);
		m_NETTOARTIKEL.EnableWindow(false);
		// m_PREIS0ARTIKEL.EnableWindow(false); Version 7.62
		m_TAXPRUEFGROSSO.EnableWindow(false);
		m_SONDERGROSSO.EnableWindow(false);
		m_TAXPFL.EnableWindow(false);
		m_FESTBREGEL.EnableWindow(false);
		m_FESTBSTUFE.EnableWindow(false);
		m_FESTBETRAG1.EnableWindow(false);
		m_FESTBETRAG2.EnableWindow(false);
		m_DATUM_FESTBETRAG1.EnableWindow(false);
		m_DATUM_FESTBETRAG2.EnableWindow(false); 
	}

	if (IsCountry("HR"))
	{
		//m_AWL1.EnableWindow(false);
		//m_AWL2.EnableWindow(false);
		//m_AWL_AKTIV.EnableWindow(false);
		m_TFG.EnableWindow(false);
		m_KLINIKPACK.EnableWindow(false);
		m_NICHTUEBERGH.EnableWindow(false);
		m_NURKVA.EnableWindow(false);
		m_TAXPRUEFGROSSO.EnableWindow(false);
		m_RABATTFAEHIG.EnableWindow(false);
		m_DATUM_AV.EnableWindow(false);
		m_SONDERGROSSO.EnableWindow(false);
		m_TAXPFL.EnableWindow(false);
		m_FESTBETRAG1.EnableWindow(false);
		m_FESTBETRAG2.EnableWindow(false);
		m_FESTBREGEL.EnableWindow(false);
		m_FESTBSTUFE.EnableWindow(false);
		m_DATUM_FESTBETRAG1.EnableWindow(false);
		m_DATUM_FESTBETRAG2.EnableWindow(false);
		m_SOMMER_KK.EnableWindow(false);
		// m_APOTHEKENPFL.EnableWindow(false); <-- SR-24059598: no longer deactivated in HR
		// m_REZEPTPFL.EnableWindow(false); --> reactivated due to FMD
		m_NETTOARTIKEL.EnableWindow(false);
		m_SKONTOFAEHIG.EnableWindow(false);

		if (bEnab)
		{
			Enable_AVP_Croatia();
		}
	}

	if (((CEkZdpApp*)AfxGetApp())->GetMedActorParameter() == MedActor_Parameter::OneToOne)
	{
		m_MEDACTOR_F0.EnableWindow(bEnab);
		m_MEDACTOR_F1.EnableWindow(bEnab);
		m_MEDACTOR_F2.EnableWindow(bEnab);
		m_MEDACTOR_F3.EnableWindow(bEnab);
	}
	if (((CEkZdpApp*)AfxGetApp())->GetMedActorParameter() == MedActor_Parameter::OneToN)
	{
		m_MEDACTOR_0.EnableWindow(bEnab);
		m_MEDACTOR_1.EnableWindow(bEnab);
		m_MEDACTOR_2.EnableWindow(bEnab);
		m_MEDACTOR_3.EnableWindow(bEnab);
	}
	DisableSpecial();
}

void CArtikelPage1::DisableSpecial()
{
	m_ERSATZ_NR.EnableWindow(false); // Eingabe nur noch in Artikel-Code-Feld
	m_ERSATZ_NR.ShowWindow(SW_HIDE);
}

void CArtikelPage1::Enable_AVP_Croatia( )
{   
	if (m_pBufZartikel->HERST_PROZENT > 0)
	{
		m_AVP1.EnableWindow( false );
		m_AVP2.EnableWindow( false );
		m_AVP3.EnableWindow( false );
		m_AVP4.EnableWindow( false );

		// wenn Prozentsatz sich geändert hat und kein neuer Preis eingegeben, fragen, ob Preise neu gerechnet werden sollen
		if (m_pBufOldZartikel->HERST_PROZENT != m_pBufZartikel->HERST_PROZENT &&
			!m_bPreisEnabled[1])
		{
			// wenn kein neuer Preis eingegeben, fragen, ob der alte übernommen werden soll
			if ( m_pBufArtpreis[0]->DATUMGUELTIGAB == 0 )
			{
				if (MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING10267) ) == IDYES)
				{
					*m_pBufArtpreis[0] = *m_pBufArtpreis[1];
					m_pBufArtpreis[0]->DATUMGUELTIGAB = AddDayToPhoDate( ::Today(), 1 );

					// ggfs. AVP neu berechnen
					Set_Taxe_AVP(0);

					m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[0] + OFFS_GUELAB, m_Pos_PREIS[0] + OFFS_HPROZ );
				}
			}
			else
			// ansonsten direkt AVP neu berechnen
			{
				// ggfs. AVP neu berechnen
				Set_Taxe_AVP(0);

				m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[0] + OFFS_GUELAB, m_Pos_PREIS[0] + OFFS_HPROZ );
			}
		}
	}
	else
	{
		m_AVP1.EnableWindow( m_PricesOnPage1 );

		if (m_bPreisEnabled[1])
		{
			m_AVP2.EnableWindow( m_PricesOnPage1 );
		}

		if (m_bPreisEnabled[2])
		{
			m_AVP3.EnableWindow( m_PricesOnPage1 );
		}

		if (m_bPreisEnabled[3])
		{
			m_AVP4.EnableWindow( m_PricesOnPage1 );
		}
	}
}

void CArtikelPage1::ShowFields( )
{
/*
	if ( m_OldArtikelnr != m_pBufZartikel->ARTIKEL_NR )
	{
		LeseSekbez( FALSE );	
		m_OldArtikelnr = m_pBufZartikel->ARTIKEL_NR;
	}
*/
	FillComboBox();
	Translation();

	m_dlg.ShowFields();

	ShowKettArtikel( TRUE );
	ShowHersteller( TRUE );

	if (IsCountry("F"))
	{
		ShowAwl1_Fr( TRUE );
	}
	else
	{
		ShowAwl1( TRUE );
	}

	Test_Set_ZZ( TRUE );
	ZeigePharmosSekbez( );
	ZeigeTiermedizinBezeichnung();


	if (((CEkZdpApp*)AfxGetApp())->GetMedActorParameter() == MedActor_Parameter::OneToOne) 
	{
		SetMedicalActor_OneToOne();
		for (int i = 0; i < 4; ++i)
		{
			ShowMedicalActor_OneToOne(i, TRUE);
		}
	}
	if (((CEkZdpApp*)AfxGetApp())->GetMedActorParameter() == MedActor_Parameter::OneToN)
	{
		SetMedicalActor_OneToN();
	}
}

void CArtikelPage1::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage1::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

void CArtikelPage1::ActivateField( int nr )
{
    m_dlg.ActivateField( nr );
}

	
BOOL CArtikelPage1::Validate( BOOL bMeldung )
{
	int i = 0;
	BOOL bOk = TRUE;

	SetValidation( FALSE );

	bOk = m_dlg.Validate( &i, bMeldung );
	if ( bOk )
		bOk = EndValidate( &i, bMeldung );

	if ( !bOk && bMeldung )
		m_dlg.ActivateField( i );
	
	SetValidation( TRUE );

	return bOk;
}

/////////////////////////////////////////////////////////////////////////////
// CLieferPage1 message handlers

BOOL CArtikelPage1::OnSetActive()
{
	BOOL bOk;
	bOk = CPropertyPageMultiLang::OnSetActive();
	if ( bOk && m_bInitialized )
	{
		ShowFields();
		((CArtikelView* )m_pView)->Set_WasActive();
		EnableFields( ((CArtikelView* )m_pView)->AreFieldsEnabled() );
		GetParent()->SendMessage( WM_USER+10 );
		SetValidation( TRUE );
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING265) );
	}
	return bOk;
}


BOOL CArtikelPage1::OnKillActive()
{
	BOOL bOk;
	bOk = CPropertyPageMultiLang::OnKillActive();
	if ( bOk )
	{
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING266) );
//		SetValidation( FALSE );

/*  Test, ob hier nicht generell NextDlgCtrl() ausgefuehrt werden soll
		if ( GetFocus() == &m_AWL1 ) 
		{
			m_bAwl1Meldung = FALSE;
			ChPflegePage::NextDlgCtrl();	// neu, wegen PPE_Kennz Seite 3 
			m_bAwl1Meldung = TRUE;
		}
*/
		SetValidation( FALSE );

		DataExchangeToBuffer( );  //  Puffer wie Eingabe
		// headerinfo
		((CArtikelView*)(GetParent()->GetParent()))->SetHeaderInfo();
	}
	return bOk;
}
          
void CArtikelPage1::NextDlgCtrl()
{
	if ( GetFocus() == GetDlgItem( IDC_PB_ARTIKEL_SEKBEZ ) )
	{
		OnPbArtikelSekbez();
	}
	else if ( GetFocus() == GetDlgItem( IDC_PB_ARTIKEL_PRICES ) )
	{
		OnPbArtikelPrices();
	}
	ChPflegePage::NextDlgCtrl();

	if ( GetFocus() == GetDlgItem( IDC_PB_ARTIKEL_SEKBEZ ) || GetFocus() == GetDlgItem( IDC_PB_ARTIKEL_PRICES ) )
		ChPflegePage::NextDlgCtrl();
}


///////////////////////////////////////////////////////
// Taxpfl<-> Nettoartikel : gegenseitiger Ausschluss
// wenn auf nicht taxpfl gesetzt dann Rabattfaehigkeit auf 01
//	 ( wenn nicht 11 )

void CArtikelPage1::OnSelchangeCkArtikelTaxpfl() 
{
	if ( m_TAXPFL.GetCurSel( ) != 0 )
	{
		m_NETTOARTIKEL.SetCheck( 0 );
	}
/*
	else	// Rabattfaehigkeit auf 01
	{
		m_RABATTFAEHIG.p_GetInput();
		if ( !( strcmp( m_pBufZartikel->RABATTFAEHIG, "01" ) == 0 ||
		        strcmp( m_pBufZartikel->RABATTFAEHIG, "11" ) == 0    ) )
		{
			strcpy( m_pBufZartikel->RABATTFAEHIG, "01");
			m_RABATTFAEHIG.p_SetInput();
		}
	}
*/
}

void CArtikelPage1::OnCkArtikelNettoartikel() 
{
	// TODO: Add your control notification handler code here
	if ( m_NETTOARTIKEL.GetCheck() )
	{
		m_TAXPFL.SetCurSel( 0 );	// Taxe OTCX_RX
//		OnSelchangeCkArtikelTaxpfl();		// Peetz 17.07 
	}
}


///////////////////////////////////////////////////////
// Rezeptpflichtig<->Apothekenpflichtig : gegenseitiger Ausschluss

void CArtikelPage1::OnCkArtikelRezeptpfl() 
{
	if ( m_REZEPTPFL.GetCheck() )
	{
		// nur in D nicht gleichzeitig erlaubt
		if (IsCountry("D"))
			m_APOTHEKENPFL.SetCheck( 0 );

		// RF 01 nur in Deutschland setzen
		if (IsCountry("D"))
		{
			// Rabattfaehigkeit auf 01, wenn nicht bereits 11
			m_RABATTFAEHIG.p_GetInput();
			if ( !( strcmp( m_pBufZartikel->RABATTFAEHIG, "01" ) == 0 ||
					strcmp( m_pBufZartikel->RABATTFAEHIG, "11" ) == 0    ) )
			{
				strcpy( m_pBufZartikel->RABATTFAEHIG, "01");
				m_RABATTFAEHIG.p_SetInput();
			}
		}
	}
}

void CArtikelPage1::OnCkArtikelApothekenpfl() 
{
	if ( m_APOTHEKENPFL.GetCheck() )
	{
		// nur in D nicht gleichzeitig erlaubt
		if (IsCountry("D"))
			m_REZEPTPFL.SetCheck( 0 );
	}	
}

///////////////////////////////////////////////////////
// Rezeptpflichtig<->Apothekenpflichtig :
//	NURKVA ja -> NICHTUEBERHG ja
//	NICHTUEBERGH nein -> NURKVA nein


void CArtikelPage1::OnCkArtikelNurkva() 
{
	// TODO: Add your control notification handler code here
	if ( m_NURKVA.GetCheck() )
	{
		m_NICHTUEBERGH.SetCheck( 1 );
	}		
}

void CArtikelPage1::OnCkArtikelNichtuebergh() 
{
	// TODO: Add your control notification handler code here
	if ( !m_NICHTUEBERGH.GetCheck() )
	{
		m_NURKVA.SetCheck( 0 );
	}	
}

//////////////////////////////////////////////////////////
// Wenn BTM = ja, dann BM an Stelle 27/28 des Artikels

void CArtikelPage1::OnCkArtikelBtm() 
{
	// TODO: Add your control notification handler code here
	m_BTM.p_GetInput();
	ChangeArtikelName();		
	ChangeBtm_Faktor();
}


//////////////////////////////////////
// Preise

void CArtikelPage1::ZeigePrices( )
{	
	m_dlg.ShowFields(m_Pos_FirstPreisField, m_Pos_FirstPreisField + (( OFFS_HPROZ + 1 ) * NUMBER_OF_PRICE_ON_PAGE1 ) ); 	
	m_PREISTYP.p_SetInput();
	m_HERST_PROZENT.p_SetInput();
	EnableFields(true);
}

void CArtikelPage1::OnPbArtikelPrices() 
{
	m_TAXPRUEFGROSSO.p_GetInput();
	m_NICHTUEBERGH.p_GetInput();
	m_TAXPFL.p_GetInput();
	m_HERST_PROZENT.p_GetInput();
	m_PREIS0ARTIKEL.p_GetInput();
	m_ARTIKEL_GESPERRT.p_GetInput();
	m_BTM.p_GetInput();

	CArtikelPrices dlg(	((CArtikelView* )m_pView)->m_Doc.GetBuffer()->artpreis, (CArtikelView* )m_pView );
	
	dlg.DoModal();

	ZeigePrices( );
}

//////////////////////////////////////
// Sekundaerbezeichnung
BOOL CArtikelPage1::ReadSekbez(  )
{
	long s;
	CString Errmld;

	m_nNrOfSekbez = 0;
	s = ((CArtikelView* )m_pView)->m_Doc.ReadRecord_Sekbez( Errmld ); 
	if ( s == 0 || s == 100 )
		m_nNrOfSekbez = ((CArtikelView* )m_pView)->m_Doc.GetNrOfSekbez();
	else
		MsgBoxOK( Errmld );

	return ( s == 0 || s == 100 );
}

void CArtikelPage1::OnPbArtikelSekbez() 
{
	// TODO: Add your control notification handler code here

	if ( !m_bSekbezGelesen )
	{
		m_bSekbezGelesen = ReadSekbez();
	}
	if ( m_bSekbezGelesen )
	{
		CArtikelSekbez dlg(	((CArtikelView* )m_pView)->m_Doc.GetSekbezBuffer(),
							m_nNrOfSekbez );
		dlg.DoModal();
		m_nNrOfSekbez = dlg.GetNewNrOfSekbez();
		((CArtikelView* )m_pView)->m_Doc.SetNewNrOfSekbez( m_nNrOfSekbez );

		m_pBuf->cPharmosSekbez = dlg.GetPharmosSekbez();
		ZeigePharmosSekbez( );
	}
}

void CArtikelPage1::Translation() 
{
	double dMwstProz[5];
	CString	CsMwst;
	int	iAnzMwst = 0;

	if (IsCountry("A"))
	{
		GetDlgItem(IDC_CK_ARTIKEL_BTM)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING267));
		GetDlgItem(IDC_CK_ARTIKEL_TIERARZNEI)->SetWindowText(CResString::ex().getStrTblText(IDS_STRING268));
		m_TAXPFL.SetMask ("01234",    m_pBufZartikel->TAXPFL, 0  );	
		m_TAXPFL.ResetContent();
		m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING269));
		m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING270));
		m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING271));
		m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING272));
		m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING273));
	}

	if (IsCountry("CH") || IsCountry("HR") || IsCountry("RS"))
	{
		m_TAXPFL.SetMask ("0", m_pBufZartikel->TAXPFL, 0  );	
		m_TAXPFL.ResetContent();
		m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING269));
	}

	if (IsCountry("F") || IsCountry("BG"))
	{
		m_TAXPFL.SetMask ("01",    m_pBufZartikel->TAXPFL, 0  );	
		m_TAXPFL.ResetContent();
		m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING269));
		m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING274));
	}

	if (IsCountry("F"))
	{
		// Reihenfolge 01243 bewusst, damit die Sätze in der richtigen Reihenfolge angezeigt werden
		m_MWST1.SetMask("01243", m_pBufArtpreis[0]->KE_MWST, 0);
		m_MWST2.SetMask("01243", m_pBufArtpreis[1]->KE_MWST, 0);
		m_MWST3.SetMask("01243", m_pBufArtpreis[2]->KE_MWST, 0);
		m_MWST4.SetMask("01243", m_pBufArtpreis[3]->KE_MWST, 0);

		m_MWST1.ResetContent();
		m_MWST2.ResetContent();
		m_MWST3.ResetContent();
		m_MWST4.ResetContent();

		// Mwst-Prozentsätze aus der Taxtab-Klasse holen (jeweilige Landes-Reihenfolge beachten !!)
		iAnzMwst = m_pTaxTb->GetAllVatRates( AddDayToPhoDate( ::Today(), 1 ), &dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[4], &dMwstProz[3]);
	}

	if (IsCountry("A"))  // 3RD-VAT
	{
		// Reihenfolge 012 bewusst, damit die Sätze in der richtigen Reihenfolge angezeigt werden
		m_MWST1.SetMask("0123", m_pBufArtpreis[0]->KE_MWST, 0);
		m_MWST2.SetMask("0123", m_pBufArtpreis[1]->KE_MWST, 0);
		m_MWST3.SetMask("0123", m_pBufArtpreis[2]->KE_MWST, 0);
		m_MWST4.SetMask("0123", m_pBufArtpreis[3]->KE_MWST, 0);

		m_MWST1.ResetContent();
		m_MWST2.ResetContent();
		m_MWST3.ResetContent();
		m_MWST4.ResetContent();

		// Mwst-Prozentsätze aus der Taxtab-Klasse holen (jeweilige Landes-Reihenfolge beachten !!)
		iAnzMwst = m_pTaxTb->GetAllVatRates( AddDayToPhoDate( ::Today(), 1 ), &dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[4], &dMwstProz[3]);

		iAnzMwst++;
	}

	if (IsCountry("HR"))
	{
		// Reihenfolge 021 bewusst, damit die Sätze in der richtigen Reihenfolge angezeigt werden
		m_MWST1.SetMask("021", m_pBufArtpreis[0]->KE_MWST, 0);
		m_MWST2.SetMask("021", m_pBufArtpreis[1]->KE_MWST, 0);
		m_MWST3.SetMask("021", m_pBufArtpreis[2]->KE_MWST, 0);
		m_MWST4.SetMask("021", m_pBufArtpreis[3]->KE_MWST, 0);

		m_MWST1.ResetContent();
		m_MWST2.ResetContent();
		m_MWST3.ResetContent();
		m_MWST4.ResetContent();

		// Mwst-Prozentsätze aus der Taxtab-Klasse holen (jeweilige Landes-Reihenfolge beachten !!)
		iAnzMwst = m_pTaxTb->GetAllVatRates( AddDayToPhoDate( ::Today(), 1 ), &dMwstProz[0], &dMwstProz[2], &dMwstProz[1], &dMwstProz[3], &dMwstProz[4]);
	}

	if (IsCountry("RS"))
	{
		m_MWST1.ResetContent();
		m_MWST2.ResetContent();
		m_MWST3.ResetContent();
		m_MWST4.ResetContent();

		// Mwst-Prozentsätze aus der Taxtab-Klasse holen (jeweilige Landes-Reihenfolge beachten !!)
		iAnzMwst = m_pTaxTb->GetAllVatRates( AddDayToPhoDate( ::Today(), 1 ), &dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[3], &dMwstProz[4]);

		// Wert um 1 erhöhen, damit die 0% auch angezeigt werden (Hajo würde schreiben: "Trick !!!")
		iAnzMwst++;
	}

	// eingelesene Mwst-Saetze in Combo-Box stellen // 3RD-VAT
	if (IsCountry("F") || 
		IsCountry("HR") || 
		IsCountry("RS") ||
		IsCountry("A"))
	{
		for (int i = 0; i < iAnzMwst; i++)
		{
			CsMwst.Format("%.1f %%", dMwstProz[i]);
			m_MWST1.AddString(CsMwst);
			m_MWST2.AddString(CsMwst);
			m_MWST3.AddString(CsMwst);
			m_MWST4.AddString(CsMwst);
		}
	}

    if (IsCountry("RS"))
	{
		m_RABATTFAEHIG.SetMask	("0001" , 2, m_pBufZartikel->RABATTFAEHIG, 0 );   
		m_RABATTFAEHIG.ResetContent();
		m_RABATTFAEHIG.AddString(CResString::ex().getStrTblText(IDS_STRING1122));
		m_RABATTFAEHIG.AddString(CResString::ex().getStrTblText(IDS_STRING1123));
	}

	if (!IsCountry("D"))
	{
		m_ZUZAHLUNG_IFA.SetMask(ED_CHAR,
		                ED_NORMAL,
			            m_pBufZartikel->ZUZAHLUNG_IFA,
				        L_ZARTIKEL_ZUZAHLUNG_IFA,
						new ChMaskNum );
	}
}

void CArtikelPage1::Set_Taxpfl( )
{
	m_dlg.DataExchangeFromBuffer( m_Pos_TAXPFL );
}

void CArtikelPage1::Set_Skontofaehig( )
{
	m_dlg.DataExchangeFromBuffer( m_Pos_SKONTOFAEHIG );
}

void CArtikelPage1::Set_Rezeptpfl( )
{
	m_dlg.DataExchangeFromBuffer( m_Pos_REZEPTPFL );
}

// frz. Artikelbezeichnung in Page5CH ändern
void CArtikelPage1::SetArtikelname_Frz( )
{
	// nur in der Schweiz !!!
	if (!IsCountry("CH")) return;

	// auf Seite 5 im Dialogfeld aktivieren
	CArtikelPage5CH *pP5;
	pP5 = (CArtikelPage5CH *)((CArtikelView*)m_pView)->GetPage(4);
	pP5->Set_Artikel_Name();
}

// Elektroschrott zuruecksetzen bei Hersteller-Wechsel
void CArtikelPage1::Set_Elektroschrott( )
{
	// nur, wenn Hersteller tatsächlich geändert
	if ( m_pBufOldZartikel->HERSTELLER_NR == m_pBufZartikel->HERSTELLER_NR ) 
		return;

	// nur, wenn Elektroschrott = ja, registriert und Feld nicht geändert
	if ( m_pBufZartikel->ELEKTROSCHROTT[0] != 'R' ||  
		 m_pBufOldZartikel->ELEKTROSCHROTT[0] != 'R' ) 
		return;

	m_pBufZartikel->ELEKTROSCHROTT[0] = 'J';
	m_pBufZartikel->ZENTR_EKSPERRE[0] = '1';

	// lt. Hr. Peetz nun doch nicht setzen
	// m_pBufZartikel->NAHRUNGSERGAENZUNG[0] = 'G';

	// auf Seite 2 im Dialogfeld aktivieren
	CArtikelPage2 *pP2;
	pP2 = (CArtikelPage2 *)((CArtikelView*)m_pView)->GetPage(1);
	pP2->Set_Elektroschrott();
}

CString CArtikelPage1::Set_Langname_Fr( )
{
	CString cs, cs2, cs3;

	// Änderung nur, wenn Abez, Einh, oder Drfo geändert
	if ((strncmp(m_pBuf->zartikel.ARTIKEL_NAME, m_pBufOld->zartikel.ARTIKEL_NAME, L_ZARTIKEL_ARTIKEL_NAME) == 0) &&
		(strncmp(m_pBuf->zartikel.EINHEIT, m_pBufOld->zartikel.EINHEIT, L_ZARTIKEL_EINHEIT) == 0) &&
		(strncmp(m_pBuf->zartikel.DARREICHFORM, m_pBufOld->zartikel.DARREICHFORM, L_ZARTIKEL_DARREICHFORM) == 0))
	{
		return "";
	}

	cs.Format("%s", m_pBuf->zartikel.ARTIKEL_NAME);
	cs.Trim();
	cs2 = cs;
	cs3.Format("%s", m_pBuf->zartikel.EINHEIT);
	cs3.Trim();
	cs.Format("%s %s", cs2, cs3);
	cs.Trim();
	cs2 = cs;
	cs.Format("%s %s", cs2, m_pBuf->zartikel.DARREICHFORM);

	strcpy (m_pBuf->zartikel.ARTIKEL_LANGNAME, cs);
	
	return cs;
}

void CArtikelPage1::FillComboBox()
{
	m_SONDERGROSSO.ResetContent();
	m_PREISTYP.ResetContent();
	m_AWL_AKTIV.ResetContent();
	m_DISC_DED_YET1.ResetContent();
	m_DISC_DED_YET2.ResetContent();
	m_DISC_DED_YET3.ResetContent();
	m_DISC_DED_YET4.ResetContent();	
	m_MWST1.ResetContent();
	m_MWST2.ResetContent();
	m_MWST3.ResetContent();
	m_MWST4.ResetContent();
	m_PRICEMODEL1.ResetContent();
	m_PRICEMODEL2.ResetContent();
	m_PRICEMODEL3.ResetContent();
	m_PRICEMODEL4.ResetContent();
	m_RABATTFAEHIG.ResetContent();
	m_TAXPFL.ResetContent();
	m_VERTRBIND.ResetContent();
	m_MEDCANGES.ResetContent();
	m_VERFALL.ResetContent();
	m_TFG.ResetContent();

	m_SONDERGROSSO.AddString(CResString::ex().getStrTblText(IDS_STRING10062));
	m_SONDERGROSSO.AddString(CResString::ex().getStrTblText(IDS_STRING10314));
	m_SONDERGROSSO.AddString(CResString::ex().getStrTblText(IDS_STRING10315));
	m_SONDERGROSSO.AddString(CResString::ex().getStrTblText(IDS_STRING10316));
	m_SONDERGROSSO.AddString(CResString::ex().getStrTblText(IDS_STRING10317));
	m_SONDERGROSSO.AddString(CResString::ex().getStrTblText(IDS_STRING10318));
	m_TFG.AddString(CResString::ex().getStrTblText(IDS_STRING1511));	//nein
	m_TFG.AddString(CResString::ex().getStrTblText(IDS_STRING1512));	//ja, Blutprodukt
	m_TFG.AddString(CResString::ex().getStrTblText(IDS_STRING1513));	//ja, Arzn. b. Hämophilie

// TEST-BG auf anderer DB: generell die beiden bulgarischen Texte
	if (IsCountry("BG"))
	{
		m_PREISTYP.AddString(CResString::ex().getStrTblText(IDS_STRING500));
		m_PREISTYP.AddString(CResString::ex().getStrTblText(IDS_STRING501));
	}
	else
		m_PREISTYP.AddString(CResString::ex().getStrTblText(IDS_STANDARD));

	m_AWL_AKTIV.AddString("N");
	m_AWL_AKTIV.AddString("J");
	m_AWL_AKTIV.AddString("Z");

	m_DISC_DED_YET1.AddString(CResString::ex().getStrTblText(IDS_NO)); 
	m_DISC_DED_YET1.AddString(CResString::ex().getStrTblText(IDS_YES)); 
	m_DISC_DED_YET1.AddString(CResString::ex().getStrTblText(IDS_STRING_FORTGELTEND));
	m_DISC_DED_YET1.AddString(CResString::ex().getStrTblText(IDS_STRING_ANTIB));

	m_DISC_DED_YET2.AddString(CResString::ex().getStrTblText(IDS_NO)); 
	m_DISC_DED_YET2.AddString(CResString::ex().getStrTblText(IDS_YES)); 
	m_DISC_DED_YET2.AddString(CResString::ex().getStrTblText(IDS_STRING_FORTGELTEND));
	m_DISC_DED_YET2.AddString(CResString::ex().getStrTblText(IDS_STRING_ANTIB));

	m_DISC_DED_YET3.AddString(CResString::ex().getStrTblText(IDS_NO)); 
	m_DISC_DED_YET3.AddString(CResString::ex().getStrTblText(IDS_YES)); 
	m_DISC_DED_YET3.AddString(CResString::ex().getStrTblText(IDS_STRING_FORTGELTEND));
	m_DISC_DED_YET3.AddString(CResString::ex().getStrTblText(IDS_STRING_ANTIB));

	m_DISC_DED_YET4.AddString(CResString::ex().getStrTblText(IDS_NO)); 
	m_DISC_DED_YET4.AddString(CResString::ex().getStrTblText(IDS_YES)); 
	m_DISC_DED_YET4.AddString(CResString::ex().getStrTblText(IDS_STRING_FORTGELTEND));
	m_DISC_DED_YET4.AddString(CResString::ex().getStrTblText(IDS_STRING_ANTIB));

	m_MWST1.AddString(CResString::ex().getStrTblText(IDS_STRING10103));
	m_MWST1.AddString(CResString::ex().getStrTblText(IDS_STRING10104));
	m_MWST1.AddString(CResString::ex().getStrTblText(IDS_STRING10105));

	m_MWST2.AddString(CResString::ex().getStrTblText(IDS_STRING10103));
	m_MWST2.AddString(CResString::ex().getStrTblText(IDS_STRING10104));
	m_MWST2.AddString(CResString::ex().getStrTblText(IDS_STRING10105));

	m_MWST3.AddString(CResString::ex().getStrTblText(IDS_STRING10103));
	m_MWST3.AddString(CResString::ex().getStrTblText(IDS_STRING10104));
	m_MWST3.AddString(CResString::ex().getStrTblText(IDS_STRING10105));

	m_MWST4.AddString(CResString::ex().getStrTblText(IDS_STRING10103));
	m_MWST4.AddString(CResString::ex().getStrTblText(IDS_STRING10104));
	m_MWST4.AddString(CResString::ex().getStrTblText(IDS_STRING10105));

	m_PRICEMODEL1.AddString("00");
	m_PRICEMODEL1.AddString("01");
	m_PRICEMODEL1.AddString("02");
	m_PRICEMODEL1.AddString("03");

	m_PRICEMODEL2.AddString("00");
	m_PRICEMODEL2.AddString("01");
	m_PRICEMODEL2.AddString("02");
	m_PRICEMODEL2.AddString("03");

	m_PRICEMODEL3.AddString("00");
	m_PRICEMODEL3.AddString("01");
	m_PRICEMODEL3.AddString("02");
	m_PRICEMODEL3.AddString("03");

	m_PRICEMODEL4.AddString("00");
	m_PRICEMODEL4.AddString("01");
	m_PRICEMODEL4.AddString("02");
	m_PRICEMODEL4.AddString("03");

	m_RABATTFAEHIG.AddString("00");
	m_RABATTFAEHIG.AddString("01");
	m_RABATTFAEHIG.AddString("02");
	m_RABATTFAEHIG.AddString("03");
	m_RABATTFAEHIG.AddString("04");
	m_RABATTFAEHIG.AddString("11");
	m_RABATTFAEHIG.AddString("12");
	m_RABATTFAEHIG.AddString("13");
	m_RABATTFAEHIG.AddString("14");

	m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING10116));
	m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING10117));
	m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING10118));
	//m_TAXPFL.AddString(CResString::ex().getStrTblText(IDS_STRING1236)); // Ausnahme RX für AMNOG 2011

	m_VERTRBIND.AddString(CResString::ex().getStrTblText(IDS_STRING10059)); // keine
	m_VERTRBIND.AddString(CResString::ex().getStrTblText(IDS_STRING10120)); // Eucerin			- ART-VBA
	m_VERTRBIND.AddString(CResString::ex().getStrTblText(IDS_STRING10121)); // Vichy			- ART-VB1
	m_VERTRBIND.AddString(CResString::ex().getStrTblText(IDS_STRING10122)); // ELAC-Eigenmarken - ART-VB2
	m_VERTRBIND.AddString(CResString::ex().getStrTblText(IDS_STRING10123)); // MVDA-Eigenmarken - ART-VB3
	m_VERTRBIND.AddString(CResString::ex().getStrTblText(IDS_STRING10124)); // PHA Pet Health	- ART-VB4
	m_VERTRBIND.AddString(CResString::ex().getStrTblText(IDS_STRING1323));  // La Roche P.		- ART-VBB
	m_VERTRBIND.AddString(CResString::ex().getStrTblText(IDS_STRING1324));  // Ales Groupe		- ART-VBC

	m_VERFALL.AddString(CResString::ex().getStrTblText(IDS_STRING10062));
	m_VERFALL.AddString(CResString::ex().getStrTblText(IDS_STRING10125));
	m_VERFALL.AddString(CResString::ex().getStrTblText(IDS_STRING10126));

	m_MEDCANGES.AddString(CResString::ex().getStrTblText(IDS_STRING14424));
	m_MEDCANGES.AddString(CResString::ex().getStrTblText(IDS_STRING14425));
	m_MEDCANGES.AddString(CResString::ex().getStrTblText(IDS_STRING14426));

// wird weder gesetzt noch ins Pharmos übertragen
//	m_VERFALL.AddString(CResString::ex().getStrTblText(IDS_STRING10127));

	FillCoolLevels();

	if (((CEkZdpApp*)AfxGetApp())->GetMedActorParameter() == MedActor_Parameter::OneToN)
	{
		FillMedicalActor_OneToN();
	}
}

void CArtikelPage1::FillCoolLevels( )
{
	long s;
	int  fd;
	char shortcut[ L_CCOOLLEVEL_COOLLEVELNAME + 1 ] = {0};
	char id		 [ L_CCOOLLEVEL_COOLLEVELID   + 1 ] = {0};
	CString mask;
	
	std::vector<CString> coolLevels;

	s = SqlOpenCs( &fd, "select COOLLEVELID, COOLLEVELNAME from CCOOLLEVEL order by ORDINALNO" );	
	if ( s == 0 )
	{
		while (SqlFetch( fd, 1, id, shortcut, NULL ) == 0)
		{
			coolLevels.push_back(shortcut);
			mask.Append(id);
		}
	}
	SqlCloseCs( fd );
	
	if (!coolLevels.empty())
	{
		// wenn mind. 1 Satz in ccoollevel
		sprintf(maskCoolLevel, "%s", mask.Trim().GetString());
		m_KUEHLARTIKEL.SetMask(maskCoolLevel, m_pBufZartikel->KUEHLARTIKEL, 0); // alle coollevelid´s aus ccoollevel !!!
		
		m_KUEHLARTIKEL.ResetContent();

		// Schleife über alle ccoollevel- Zeilen
		std::vector<CString>::iterator it;
		it = coolLevels.begin();

		while (it != coolLevels.end())
		{
			m_KUEHLARTIKEL.AddString(it->Trim());	
			++it;
		}
	}
	else
	{
		m_KUEHLARTIKEL.ResetContent();

		// --> corresponding to InitPflege : m_KUEHLARTIKEL.SetMask	("03214", m_pBufZartikel->KUEHLARTIKEL, 0 ); 
		m_KUEHLARTIKEL.AddString(CResString::ex().getStrTblText(IDS_STRING1272)); //nein
		m_KUEHLARTIKEL.AddString(CResString::ex().getStrTblText(IDS_STRING1273)); //25
		m_KUEHLARTIKEL.AddString(CResString::ex().getStrTblText(IDS_STRING1274)); //20
		m_KUEHLARTIKEL.AddString(CResString::ex().getStrTblText(IDS_STRING1275)); //8
		m_KUEHLARTIKEL.AddString(CResString::ex().getStrTblText(IDS_STRING10119));//Kette
		if (IsCountry("A"))
		{
			m_KUEHLARTIKEL.AddString(CResString::ex().getStrTblText(IDS_STRING614712));//-25 -15
			m_KUEHLARTIKEL.AddString(CResString::ex().getStrTblText(IDS_STRING614713));//-80 -60
		}
	}
}

void CArtikelPage1::CalculatePercent( int nr)
{
	double dProz;

	//  nur in Frankreich Großhandel !!!!!
	if (!IsCountry("F") || IsPrewhole() )
	{
		return;
	}

	//  nur bei der 1. Preiszeile !!!!!
	if ( nr != 0 ) 
	{
		return;
	}

	// beide Preise müssen gefüllt sein
	if ( (m_pBufArtpreis[nr]->GROSSO <= 0.0) || (m_pBufArtpreis[nr]->AEP <= 0.0) )
	{
		return;
	}

	dProz = 100 * (1.0 - (m_pBufArtpreis[nr]->GROSSO / m_pBufArtpreis[nr]->AEP));
	m_pBufZartikel->HERST_PROZENT = dProz;
	m_HERST_PROZENT.p_SetInput();

	// auch das entsprechende zartpreis-Feld versorgen
	Set_Herst_Prozent();

	// m_pBufArtpreis[nr]->HERST_PROZENT = dProz;
	// m_HPROZ1.p_SetInput();
}

void CArtikelPage1::ChangeBtm_Faktor( )
{
	// nur, wenn überhaupt BTM-Artikel
	if (m_pBufZartikel->BTM[0] != '1')
	{
		m_pBufZartikel->BTM_FAKTOR = 0;
	}
	else
	{
		m_pBufZartikel->BTM_FAKTOR = CalculateBtm_Faktor( );
	}

	m_BTM_FAKTOR.p_SetInput();
}
	
double CArtikelPage1::CalculateBtm_Faktor( )
{
	CString csBtmEinheit, csArtEinheit, csMenge, csEinheit;
	double dFaktor = 0.0, dMenge1, dMenge2;
	int i;

	// erstmal zdkbtm mit der BTM-Gruppe des Artikels lesen
	if (m_pBuf->zartwg[5].ART[0] == ' ')
	{
		return dFaktor;
	}

	// Versuch, Einheit aus BTM-Gruppe zu lesen 
	csBtmEinheit = ((CArtikelView* )m_pView)->m_Doc.ReadBtmEinheit();
	csBtmEinheit.Trim();

	if (csBtmEinheit.IsEmpty())
	{
		return dFaktor;
	}

	// Einheit aus zartikel in Menge und Einheit zerlegen
	csArtEinheit = m_pBufZartikel->EINHEIT;
	
	i = csArtEinheit.ReverseFind(' ');
	csMenge = csArtEinheit.Left(i);
	csMenge.Trim();

	csEinheit = csArtEinheit.Right(8 - i);

	// Menge richtig berechnen, wenn Faktor darin ("X")
	i = csMenge.Find('X');

	if (i != -1)
	{
		dMenge1 = atof (csMenge.Left(i));
		dMenge2 = atof (csMenge.Right(csMenge.GetLength() - i - 1));

		csMenge.Format("%f", dMenge1 * dMenge2);
	}

	// wenn die Einheiten gleich sind, kann Menge 1:1 übernommen werden
	if (csEinheit == csBtmEinheit)
	{
		dFaktor = atof (csMenge);
	}
	else if (csBtmEinheit == "GR" && csEinheit == "KG")
	{
		dFaktor = atof (csMenge) * 1000.0;
	}
	else if (csBtmEinheit == "GR" && csEinheit == "MG")
	{
		dFaktor = atof (csMenge) / 1000.0;
	}

	return dFaktor;
}

void CArtikelPage1::OnSelchangeCbArtikelMwst1()
{
	char cMWST;

	// wenn Mwst-Satz sich geändert hat und kein neuer Preis eingegeben, fragen, ob Preise neu gerechnet werden sollen
	if ( !m_bPreisEnabled[1] )
	{
		// wenn kein neuer Preis eingegeben, fragen, ob der alte übernommen werden soll
		if ( m_pBufArtpreis[0]->DATUMGUELTIGAB == 0 )
		{
			if (MsgBoxYesNo( CResString::ex().getStrTblText(IDS_TAKE_PRICE) ) == IDYES)
			{
				cMWST = m_pBufArtpreis[0]->KE_MWST[0];
				*m_pBufArtpreis[0] = *m_pBufArtpreis[1];
				m_pBufArtpreis[0]->KE_MWST[0] = cMWST;
				m_pBufArtpreis[0]->DATUMGUELTIGAB = AddDayToPhoDate( ::Today(), 1 );

				// ggfs. AVP neu berechnen
				Set_Taxe_AVP(0);

				m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[0] + OFFS_GUELAB, m_Pos_PREIS[0] + OFFS_HPROZ );
			}
		}
		else
		// ansonsten direkt AVP neu berechnen
		{
			Set_Taxe_AVP(0);

			m_dlg.DataExchangeFromBuffer( m_Pos_PREIS[0] + OFFS_GUELAB, m_Pos_PREIS[0] + OFFS_HPROZ );
		}
	}
}

void CArtikelPage1::OnSelchangeCbArtikelVerfall()
{
	// nur in Kroatien automatisch Chargen-Kennzeichen in Abhängigkeit von Verfall setzen
	if (!IsCountry("HR"))
		return;

	m_VERFALL.p_GetInput();

	// kann theoretisch auch den Wert 2 annehmen, daher keine direkte Zuweisung
	if (m_pBufZartikel->VERFALL[0] == '1')
	{
        m_pBufZartcroatia->BATCHARTICLE[0] = '1';
		m_pBufZartikel->CHARGENARTIKEL[0] = '1';
	}
	/* das Chargen- KZ darf mit FMD / BatchTracking nicht mehr automatisch zurückgesetzt werden!
	else
	{
        m_pBufZartcroatia->BATCHARTICLE[0] = '0';
		m_pBufZartikel->CHARGENARTIKEL[0] = '0';
	}
	*/

	// auf Seite 5HR im Dialogfeld aktivieren, wenn diese schon aktiv ist
	if ( ( (CArtikelView* )m_pView)->WasPageActive(4) )
	{
		CArtikelPage5HR *pP5HR;
		pP5HR = (CArtikelPage5HR *)((CArtikelView*)m_pView)->GetPage(4);
		pP5HR->Set_BatchArticle();
	}

	// für Kroatien auf Seite 2 im Dialogfeld aktivieren, wenn diese schon aktiv ist
	if (IsCountry("HR"))
	{
		if ( ( (CArtikelView* )m_pView)->WasPageActive(1) )
		{
			CArtikelPage2 *pP2;
			pP2 = (CArtikelPage2 *)((CArtikelView*)m_pView)->GetPage(1);
			pP2->Set_Chargenartikel();
		}
	}
}

void CArtikelPage1::OnCkArtikelTierarznei() 
{
	m_TIERARZNEI.p_GetInput();

	// SR-24128659: if tierarznei is set, set also vertrbind='G'
	if (m_pBufZartikel->TIERARZNEI[0] == '1') {
		m_pBufZartikel->VERTRBIND[0] = 'G';
	}
	else if (m_pBufZartikel->VERTRBIND[0] == 'G') {
		m_pBufZartikel->VERTRBIND[0] = ' ';
	}
	m_VERTRBIND.p_SetInput();

	SetChargenartikel_D();
}

void CArtikelPage1::OnSelchangeCbArtikelTfg()
{
	m_TFG.p_GetInput();
	SetChargenartikel_D();
}

void CArtikelPage1::OnCkEanNichtVorhanden()
{
	if (m_EAN_NICHT_VORHANDEN.GetCheck())
		m_EAN_NR.EnableWindow(false);
	else
		m_EAN_NR.EnableWindow(true);
}

void CArtikelPage1::SetChargenartikel_D() 
{
	// nur in Deutschland automatisch Chargen-Kennzeichen in Abhängigkeit von Tierarznei / TFG setzen
	if (!IsCountry("D") && !IsCountry("CH"))
		return;

	// kein automatisches Setzen bei Konsignationsartikeln --> geschieht individuell
	if (m_pBufZartikel->KONSIG_PARTNER_NR > 0)
		return;

	if (m_pBufZartikel->TIERARZNEI[0] == '1' ||
		m_pBufZartikel->TFG[0] == '1' || m_pBufZartikel->TFG[0] == '2')
		m_pBufZartikel->CHARGENARTIKEL[0] = '1';
	
	/* das Chargen- KZ darf mit FMD / BatchTracking nicht mehr automatisch zurückgesetzt werden!
	else
		m_pBufZartikel->CHARGENARTIKEL[0] = '0';
	*/

	// Seite 2 im Dialogfeld aktivieren, wenn diese schon aktiv ist
	if ( ( (CArtikelView* )m_pView)->WasPageActive(1) )
	{
		CArtikelPage2 *pP2;
		pP2 = (CArtikelPage2 *)((CArtikelView*)m_pView)->GetPage(1);
		pP2->Set_Chargenartikel();
	}
}

void CArtikelPage1::OnSelchangeCbArtikelPreistyp()
{
	CString cErrmld;
	long lStatus;

	// Preise neu lesen und anzeigen
	m_PREISTYP.p_GetInput();

	lStatus = ((CArtikelView* )m_pView)->m_Doc.ReadRecord_Artpreis( cErrmld );

	if ( !( lStatus == 0 || lStatus == 100 ) ) 
	{
		MsgBoxOK(cErrmld);
		return;
	}

	m_dlg.ShowFields(m_Pos_FirstPreisField, m_Pos_FirstPreisField + (( OFFS_HPROZ + 1 ) * NUMBER_OF_PRICE_ON_PAGE1 ) );
}

BOOL CArtikelPage1::SetArticleNoEditCtrl( CString& cErrmld )
{
	// nicht ausführen, wenn Werte auf dieser Page für diesen Artikel vorher nicht angezeigt wurden!
	// (sonst werden die Werte des vorher bearbeiteten Artikels eingesetzt !)
	if (((CArtikelView* )m_pView)->WasPageActive(0) == FALSE)
		return TRUE;
	
	m_ERSATZ_CODE.p_GetInput();

	CString code;
	code.Format("%s", m_ERSATZ_ARTCODE);
	code.Trim();

	if ( code.IsEmpty() ){
		m_ERSATZ_NR.SetWindowText("");
		m_ERSATZ_NR.p_GetInput();
		return TRUE;
	}

	if ( 0 > CArticleCodesConverter::setArticleNoEditCtrl(code, m_ERSATZ_NR, cErrmld )){
		m_ERSATZ_NR.SetWindowText("");
		m_ERSATZ_NR.p_GetInput();
		ShowKettArtikel(TRUE);
		MsgBoxOK( cErrmld );
		//m_ERSATZ_CODE.SetFocus(); -> focus zwar auf feld, aber cursor wird unsichtbar - warum?
		return FALSE;
	}

	m_ERSATZ_NR.p_GetInput();

	return TRUE;
}

// für Prewhole Ivrylab AWL-aktiv automatisch umsetzen bei Änderung AWL1
void CArtikelPage1::Set_AWL_aktiv( )
{
	// nur für Frankreich, Ivrylab & Prewhole
	if (!IsCountry("F") || 
		!IsPrewhole() ||
		!IsIvrylab())
		return;

	m_AWL1.p_GetInput();

	if (m_pBufZartikel->AWL1 > 0)
		m_pBufZartikel->AWL_AKTIV[0] = 'J';
	else
		m_pBufZartikel->AWL_AKTIV[0] = 'N';

	m_AWL_AKTIV.p_SetInput();
}

void CArtikelPage1::ReadMedicalActor()
{
	return ((CArtikelView*)m_pView)->m_Doc.ReadMedicalActor();
}

void CArtikelPage1::FillMedicalActor_OneToN()
{
	ReadMedicalActor();

	m_MEDACTOR_0.ResetContent();
	m_MEDACTOR_1.ResetContent();
	m_MEDACTOR_2.ResetContent();
	m_MEDACTOR_3.ResetContent();

	size_t count = ((CArtikelView*)m_pView)->m_Doc.m_medicalActors.size();
	for (size_t i = 1; i < count; ++i)
	{
		CMEDICALACTOR* pItem = ((CArtikelView*)m_pView)->m_Doc.m_medicalActors[i];
		if (!pItem) continue;

		CString medicalactor_id = pItem->MEDICALACTOR_ID;
		CString name = pItem->NAME;
		medicalactor_id.Trim();
		name.Trim();

		CString sEntry = medicalactor_id + " - " + name;

		switch (pItem->MEDICALACTOR_TYPE)
		{
		case 0:
			m_MEDACTOR_0.AddString(sEntry);
			break;
		case 1:
			m_MEDACTOR_1.AddString(sEntry);
			break;
		case 2:
			m_MEDACTOR_2.AddString(sEntry);
			break;
		case 3:
			m_MEDACTOR_3.AddString(sEntry);
			break;
		}
	}
}

void CArtikelPage1::SetMedicalActor_OneToN()
{
	CString cErrmld;
	long lStatus;
	short lastmedicaltype = 0;
	short index_next = 0;

	((CEkZdpApp*)AfxGetApp())->BeginWaitAction();

	std::vector<CMEDICALACTOR*>& actors = ((CArtikelView*)m_pView)->m_Doc.m_medicalActors;
	isOldChecked.assign(actors.size(), FALSE);

	for (size_t index = 0; index < actors.size(); ++index)
	{
		CMEDICALACTOR* pItem = actors[index];
		if (!pItem) continue;

		lStatus = ((CArtikelView*)m_pView)->m_Doc.ReadRecord_CArtMedActor_OneToN(cErrmld, pItem->MEDICALACTOR_ID, pItem->MEDICALACTOR_TYPE);

		if (pItem->MEDICALACTOR_TYPE != lastmedicaltype)
		{
			index_next = 1;
		}

		if (lStatus == 100)
		{
			m_MEDACTOR_0.SetCheck(static_cast<int>(index) - 1, FALSE);
			if (!index_next)
			{
				m_MEDACTOR_1.SetCheck(index_next - 1, FALSE);
				m_MEDACTOR_2.SetCheck(index_next - 1, FALSE);
				m_MEDACTOR_3.SetCheck(index_next - 1, FALSE);
			}
		}
		if (lStatus == 0)
		{
			switch (pItem->MEDICALACTOR_TYPE)
			{
			case 0:
				m_MEDACTOR_0.SetCheck(static_cast<int>(index) - 1, TRUE);
				break;
			case 1:
				m_MEDACTOR_1.SetCheck(index_next - 1, TRUE);
				break;
			case 2:
				m_MEDACTOR_2.SetCheck(index_next - 1, TRUE);
				break;
			case 3:
				m_MEDACTOR_3.SetCheck(index_next - 1, TRUE);
				break;
			}
			if (index > 0)
				isOldChecked[static_cast<int>(index) - 1] = 1;
		}

		lastmedicaltype = pItem->MEDICALACTOR_TYPE;
		index_next++;
	}
	((CEkZdpApp*)AfxGetApp())->EndWaitAction();
}

void CArtikelPage1::SetMedicalActor_OneToOne()
{
	CString cErrmld;
	long lStatus;
	char medicalactor_id[21] = { '\0' };

	((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
	for (short i = 0; i < 4; ++i)
	{
		lStatus = ((CArtikelView*)m_pView)->m_Doc.ReadRecord_CArtMedActor_OneToOne(cErrmld, medicalactor_id, i);

		m_MEDACTORS[i]->SetInput(medicalactor_id);
		strncpy(medactors[i], medicalactor_id, 20);

		medicalactor_id[0] = '\0';
	}
	((CArtikelView*)m_pView)->m_Doc.Buf_Restored = FALSE;
	((CEkZdpApp*)AfxGetApp())->EndWaitAction();
}

/* Stores the 4 Medical Actor types with multiple values (1:n) */
void CArtikelPage1::StoreMedicalActor_OneToN()
{
	CString cErrmld;
	short index = 1, index_next = 1;
	long lStatus;
	short lastmedicaltype = 0;
	BOOL isChecked = false;

	size_t count = ((CArtikelView*)m_pView)->m_Doc.m_medicalActors.size();

	((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
	for (size_t i = 1; i < count; ++i)
	{
		CMEDICALACTOR* pItem = ((CArtikelView*)m_pView)->m_Doc.GetMedicalActor(index);

		if (pItem != NULL)
		{
			if (pItem->MEDICALACTOR_TYPE != lastmedicaltype)
			{
				index_next = 1;
			}
			switch (pItem->MEDICALACTOR_TYPE)
			{
			case 0:
				isChecked = m_MEDACTOR_0.GetCheck(index - 1);
				break;
			case 1:
				isChecked = m_MEDACTOR_1.GetCheck(index_next - 1);
				break;
			case 2:
				isChecked = m_MEDACTOR_2.GetCheck(index_next - 1);
				break;
			case 3:
				isChecked = m_MEDACTOR_3.GetCheck(index_next - 1);
				break;
			}

			if (isChecked != isOldChecked[index - 1])
			{
				if (isChecked)
				{
					lStatus = ((CArtikelView*)m_pView)->m_Doc.InsertRecord_CArtMedActor(cErrmld, pItem->MEDICALACTOR_ID, pItem->MEDICALACTOR_TYPE);
					isOldChecked[index - 1] = 1;
				}
				else
				{
					lStatus = ((CArtikelView*)m_pView)->m_Doc.DeleteRecord_CArtMedActor(cErrmld, pItem->MEDICALACTOR_ID, pItem->MEDICALACTOR_TYPE);
					isOldChecked[index - 1] = 0;
				}
			}
			lastmedicaltype = pItem->MEDICALACTOR_TYPE;
		}
		index++;
		index_next++;
	}				
	((CEkZdpApp*)AfxGetApp())->EndWaitAction();
}

/* Stores the 4 Medical Actor types with single value (1:1) */
void CArtikelPage1::StoreMedicalActor_OneToOne()
{
	CString cErrmld;
	long lStatus;
	char medicalactor_id[21] = { '\0' };

	((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
	for (short i = 0; i < 4; ++i)
	{
		m_MEDACTORS[i]->GetInput(medicalactor_id);

		lStatus = ((CArtikelView*)m_pView)->m_Doc.StoreRecord_CArtMedActor(cErrmld, medicalactor_id, i);
	}
	((CEkZdpApp*)AfxGetApp())->EndWaitAction();
}
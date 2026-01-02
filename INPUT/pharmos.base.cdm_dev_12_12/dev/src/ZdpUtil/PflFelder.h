#if !defined __PFLFELDER_H__
#define __PFLFELDER_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/carticleext.h>
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/artve.h>
#include <voodoo_table_header/zartwg.h>
#include <voodoo_table_header/cdiscount.h>
#include <voodoo_table_header/cdiscgrpmem.h>
#include <voodoo_table_header/cartcompack.h>
#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/zartfrance.h>
#include <voodoo_table_header/zartswitzerland.h>
#include <voodoo_table_header/zartserbia.h>
#include <voodoo_table_header/zartaustria.h>
#include <voodoo_table_header/cgibatchentry.h>
#include <voodoo_table_header/zchargenrueckruf.h>
#include <voodoo_table_header/cimexblock.h>
#include <voodoo_table_header/cibt.h>
#include <voodoo_table_header/ean.h>
#include <voodoo_table_header/csubsequentdeliverybrancharticleconfig.h>
#include <voodoo_table_header/bliesort.h>
#include <voodoo_table_header/cbaselistarticles.h>
#include <voodoo_table_header/cartmedactor.h>
#include <voodoo_table_header/cmedicalactor.h>
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>

/*------------------------------------------------------------------------*/
#define A_EDIT   0
#define A_BUTTON 1
#define A_COMBO  2

/*------------------------------------------------------------------------*/
struct PFL_FELD
{
	short  iAktiv;
	short  iArt;
	void  *pRef1;
	void  *pRef2;
	char  *cName;
	char  *cUpdColumn;
};

/*------------------------------------------------------------------------*/
typedef struct Edit_Mask
{
	UINT   nType;
	UINT   nStyle;
	int    nTextLen;
	int    nNachKomma;
	int	   nNrMask;	
	int    nNrVal;
} EDIT_MASK;

/* struct for saison warengruppe */
struct ZARTWG_5AG {
	long    ARTIKEL_NR;
	char    ART[2];
	char    WARENGRUPPE_5[L_ZARTWG_WARENGRUPPE + 1];
	char    WARENGRUPPE_A[L_ZARTWG_WARENGRUPPE + 1];
	char    WARENGRUPPE_G[L_ZARTWG_WARENGRUPPE + 1];
};


#define VAL_NO			   -1

//-- zartikel ---
#define VAL_AWL1			1
#define VAL_ART_NR_HERST	2
#define VAL_ART_DATUMAH		3
#define VAL_HNR				4
#define VAL_ART_NR_ORIG		5
#define VAL_PRISMAEWOCHE	6
#define VAL_HERSTEL_PROZ	7
#define VAL_DATUM_LIEFERBAR_AB 8
#define VAL_G_UN_NR			9
#define VAL_DARREICHFORM    10

//-- zartwg + zartwg_5ag ---
#define VAL_WG_ART_1		11
#define VAL_WG_ART_2		12
#define VAL_WG_ART_3		13
#define VAL_WG_ART_4		14
#define VAL_WG_ART_5		15
#define VAL_WG_ART_6		16
#define VAL_WG_ART_7		17
#define VAL_WG_ART_8		18
#define VAL_WG_ART_9		19

#define VAL_WG_ART_A		20
#define VAL_WG_ART_G		21

#define DIFF_ART_VAL_ZARTWG	10


//-- zartpreis ---
#define VAL_PREIS_GUELTIGAB	30
#define VAL_PREIS_GROSSO	31
#define VAL_PREIS_AEP		32
#define VAL_PREIS_AVP		33
#define VAL_PREIS_LBP		34
#define VAL_PREIS_MAXAEP	35
#define VAL_PREIS_MAXAVP	36
#define VAL_PREIS_PHARMACY_BASEPRICE 37
#define VAL_PUBLICATIONNUMBER 38
#define VAL_PREIS_EAVP		39

//-- cdiscount ---
#define VAL_DISC_BASE_QTY	40
#define VAL_DISC_DATEFROM	41
#define VAL_DISC_DATETO		42
#define VAL_DISC_DISC_QTY	43
#define VAL_DISC_FIXED_PRICE 44
#define VAL_DISC_VALUE_PCT	45
#define VAL_DISC_SURCHARGE_PCT 46
#define VAL_DISC_REFUND_PCT 47
#define VAL_DISC_PHARM_GRP	48
#define VAL_DISC_PHARM_GRP_EXCL	49
#define VAL_DISC_CUSTOMER	50
#define VAL_DISC_MANUFACTURER	51
#define VAL_DISC_RPG		52
#define VAL_DISC_STOP_HNR	53
#define VAL_DISC_ARTCAT		54
#define VAL_DISC_PHARM_GRP_EXCL2	55
#define VAL_DISC_PHARM_GRP_EXCL3	56

//-- artve ---
#define VAL_VPE1	60
#define VAL_VPE2	61
#define VAL_VPE3	62
#define VAL_VPE4	63
#define VAL_ORIG_KART 64

//-- zartfrance ---
#define VAL_ART_CODE_LPPR				70
#define VAL_ART_REIMBURSEMENT_PERC		71
#define VAL_ART_TFR_BASE_PRICE			72
#define VAL_DISTR_RESTR_EXPORT			73

//-- carticlecodes ---
#define VAL_ART_CODE					80

//-- cgibatchentry
#define	VAL_BATCHENTRY_COMPANYCODE		90
#define VAL_BATCHENTRY_DATE				91

//-- zartswitzerland ---
#define VAL_ART_PFLICHTLAGERMENGE	100
#define VAL_ART_WARNPROZVORPLM		101
#define VAL_IKS_CODE				102
#define VAL_MIGCD					103

//-- carticleext ---
#define VAL_ART_ALCOHOLIC_STRENGTH		110

//-- zchargenrueckruf ---
#define VAL_CHARGE				120
#define VAL_FRAGE_NEUER_WE		121
#define VAL_DATETO_GI			122
#define VAL_DATETO_CUSTRETURNS	123


//-- cimexblock ---
#define VAL_IMEX_COUNTRY		130

//-- ean ---
#define VAL_EAN					140

//-- Nachlieferung ---
#define VAL_NACHL				150
#define VAL_KONTMENGENST		151
#define VAL_BRANCH				160

//-- bliesort
#define VAL_BESLA_NO			161

//-- baselist
#define VAL_BASELIST_ID			162

//-- cartmedactor
#define VAL_CARTMEDACTOR_ID		170

//-- cmedicalactor
#define VAL_CMEDICALACTOR_ID			180
#define VAL_CMEDICALACTOR_MATCHCODE		181
#define VAL_CMEDICALACTOR_NAME			182
#define VAL_CMEDICALACTOR_STREET_NR		183
#define VAL_CMEDICALACTOR_STREET_NAME	184
#define VAL_CMEDICALACTOR_CITY_NAME		185
#define VAL_CMEDICALACTOR_COUNTRY_CODE	186
#define VAL_CMEDICALACTOR_EMAIL			187

/*------------------------------------------------------------------------*/
typedef struct Combo_Mask
{
	char* cTexte;
	char* cWerte;
	int   nDefaultPos;
	int   nBufLen;
} COMBO_MASK;


/*------------------------------------------------------------------------*/
class CPflFelder : public CDialogMultiLang
{
public:
	CPflFelder(CWnd* pParent = NULL);   // standard constructor

	int  GetFeldInfo( struct PFL_FELD *F[] );
	void InitPflege( int iMode );

// Dialog Data
	//{{AFX_DATA(CPflFelder)
	enum { IDD = IDD_PFLFELDER };
	ChDlgButton	m_F_00;
	ChDlgButton	m_F_01;
	ChDlgButton	m_F_02;
	ChDlgButton	m_F_03;
	ChDlgButton	m_F_04;
	ChDlgButton	m_F_05;
	ChDlgButton	m_F_06;
	ChDlgButton	m_F_07;
	ChDlgButton	m_F_08;
	ChDlgButton	m_F_09;
	ChDlgButton	m_F_10;
	ChDlgButton	m_F_11;
	ChDlgButton	m_F_12;
	ChDlgButton	m_F_13;
	ChDlgButton	m_F_14;
	ChDlgButton	m_F_15;
	ChDlgButton	m_F_16;
	ChDlgButton	m_F_17;
	ChDlgButton	m_F_18;
	ChDlgButton	m_F_19;
	ChDlgButton	m_F_20;
	ChDlgButton	m_F_21;
	ChDlgButton	m_F_22;
	ChDlgButton	m_F_23;
	ChDlgButton	m_F_24;
	ChDlgButton	m_F_25;
	ChDlgButton	m_F_26;
	ChDlgButton	m_F_27;
	ChDlgButton	m_F_28;
	ChDlgButton	m_F_29;
	ChDlgButton	m_F_30;
	ChDlgButton	m_F_31;
	ChDlgButton	m_F_32;
	ChDlgButton	m_F_33;
	ChDlgButton	m_F_34;
	ChDlgButton	m_F_35;
	ChDlgButton	m_F_36;
	ChDlgButton	m_F_37;
	ChDlgButton	m_F_38;
	ChDlgButton	m_F_39;
	ChDlgButton	m_F_40;
	ChDlgButton	m_F_41;
	ChDlgButton	m_F_42;
	ChDlgButton	m_F_43;
	ChDlgButton	m_F_44;
	ChDlgButton	m_F_45;
	ChDlgButton	m_F_46;
	ChDlgButton	m_F_47;
	ChDlgButton	m_F_48;
	ChDlgButton	m_F_49;
	ChDlgButton	m_F_50;
	ChDlgButton	m_F_51;
	ChDlgButton	m_F_52;
	ChDlgButton	m_F_53;
	ChDlgButton	m_F_54;
	ChDlgButton	m_F_55;
	ChDlgButton	m_F_56;
	ChDlgButton	m_F_57;
	ChDlgButton	m_F_58;
	ChDlgButton	m_F_59;
	ChDlgButton	m_F_60;
	ChDlgButton	m_F_61;
	ChDlgButton	m_F_62;
	ChDlgButton	m_F_63;
	ChDlgButton	m_F_64;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CPflFelder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL



private:
	void MakeDialog();
	void InitCountrySpecificValidations();
	void InitTexte(  );
	void AusgabeTexte( );
	int  TestAnzahl( );
	void ShowCheckboxes();

	ChDlg m_dlg;

	int m_UpdMode;

	int m_Pos_FirstField;
	int m_nMaxFields;
	int m_Pos_First_Feld;
	int m_Pos_Last_Feld;

#define ANZ_MAX_FELDER	65 
#define EMPTY_STRING	""
#define ANZ_FELDER_UPD	10
#define ANZ_FELDER_UPD_CDISCOUNT_FIX_FR		22
#define ANZ_FELDER_UPD_CDISCOUNT_FIX_BG		27

	struct PFL_FELD FELDER[ANZ_MAX_FELDER];

protected:
	//{{AFX_MSG(CPflFelder)
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 

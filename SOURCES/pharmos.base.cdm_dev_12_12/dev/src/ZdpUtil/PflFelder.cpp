
#include "stdafx.h"
#include "zdputil.h"
#include "FeldBreite.h"
#include "UpdateFromExcelView.h"
#include "PflFelder.h"

#include <libscsvoodoo/libscsvoodoo.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*------------------------------------------------------------------------*/
CPflFelder::CPflFelder(CWnd* pParent /*=NULL*/)
	: CDialogMultiLang(CPflFelder::IDD, pParent)
{
}

/*------------------------------------------------------------------------*/
void CPflFelder::DoDataExchange(CDataExchange* pDX)
{
	CDialogMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPflFelder)
	DDX_Control(pDX, IDC_CK_PFLFELD_00, m_F_00);
	DDX_Control(pDX, IDC_CK_PFLFELD_01, m_F_01);
	DDX_Control(pDX, IDC_CK_PFLFELD_02, m_F_02);
	DDX_Control(pDX, IDC_CK_PFLFELD_03, m_F_03);
	DDX_Control(pDX, IDC_CK_PFLFELD_04, m_F_04);
	DDX_Control(pDX, IDC_CK_PFLFELD_05, m_F_05);
	DDX_Control(pDX, IDC_CK_PFLFELD_06, m_F_06);
	DDX_Control(pDX, IDC_CK_PFLFELD_07, m_F_07);
	DDX_Control(pDX, IDC_CK_PFLFELD_08, m_F_08);
	DDX_Control(pDX, IDC_CK_PFLFELD_09, m_F_09);
	DDX_Control(pDX, IDC_CK_PFLFELD_10, m_F_10);
	DDX_Control(pDX, IDC_CK_PFLFELD_11, m_F_11);
	DDX_Control(pDX, IDC_CK_PFLFELD_12, m_F_12);
	DDX_Control(pDX, IDC_CK_PFLFELD_13, m_F_13);
	DDX_Control(pDX, IDC_CK_PFLFELD_14, m_F_14);
	DDX_Control(pDX, IDC_CK_PFLFELD_15, m_F_15);
	DDX_Control(pDX, IDC_CK_PFLFELD_16, m_F_16);
	DDX_Control(pDX, IDC_CK_PFLFELD_17, m_F_17);
	DDX_Control(pDX, IDC_CK_PFLFELD_18, m_F_18);
	DDX_Control(pDX, IDC_CK_PFLFELD_19, m_F_19);
	DDX_Control(pDX, IDC_CK_PFLFELD_20, m_F_20);
	DDX_Control(pDX, IDC_CK_PFLFELD_21, m_F_21);
	DDX_Control(pDX, IDC_CK_PFLFELD_22, m_F_22);
	DDX_Control(pDX, IDC_CK_PFLFELD_23, m_F_23);
	DDX_Control(pDX, IDC_CK_PFLFELD_24, m_F_24);
	DDX_Control(pDX, IDC_CK_PFLFELD_25, m_F_25);
	DDX_Control(pDX, IDC_CK_PFLFELD_26, m_F_26);
	DDX_Control(pDX, IDC_CK_PFLFELD_27, m_F_27);
	DDX_Control(pDX, IDC_CK_PFLFELD_28, m_F_28);
	DDX_Control(pDX, IDC_CK_PFLFELD_29, m_F_29);
	DDX_Control(pDX, IDC_CK_PFLFELD_30, m_F_30);
	DDX_Control(pDX, IDC_CK_PFLFELD_31, m_F_31);
	DDX_Control(pDX, IDC_CK_PFLFELD_32, m_F_32);
	DDX_Control(pDX, IDC_CK_PFLFELD_33, m_F_33);
	DDX_Control(pDX, IDC_CK_PFLFELD_34, m_F_34);
	DDX_Control(pDX, IDC_CK_PFLFELD_35, m_F_35);
	DDX_Control(pDX, IDC_CK_PFLFELD_36, m_F_36);
	DDX_Control(pDX, IDC_CK_PFLFELD_37, m_F_37);
	DDX_Control(pDX, IDC_CK_PFLFELD_38, m_F_38);
	DDX_Control(pDX, IDC_CK_PFLFELD_39, m_F_39);
	DDX_Control(pDX, IDC_CK_PFLFELD_40, m_F_40);
	DDX_Control(pDX, IDC_CK_PFLFELD_41, m_F_41);
	DDX_Control(pDX, IDC_CK_PFLFELD_42, m_F_42);
	DDX_Control(pDX, IDC_CK_PFLFELD_43, m_F_43);
	DDX_Control(pDX, IDC_CK_PFLFELD_44, m_F_44);
	DDX_Control(pDX, IDC_CK_PFLFELD_45, m_F_45);
	DDX_Control(pDX, IDC_CK_PFLFELD_46, m_F_46);
	DDX_Control(pDX, IDC_CK_PFLFELD_47, m_F_47);
	DDX_Control(pDX, IDC_CK_PFLFELD_48, m_F_48);
	DDX_Control(pDX, IDC_CK_PFLFELD_49, m_F_49);
	DDX_Control(pDX, IDC_CK_PFLFELD_50, m_F_50);
	DDX_Control(pDX, IDC_CK_PFLFELD_51, m_F_51);
	DDX_Control(pDX, IDC_CK_PFLFELD_52, m_F_52);
	DDX_Control(pDX, IDC_CK_PFLFELD_53, m_F_53);
	DDX_Control(pDX, IDC_CK_PFLFELD_54, m_F_54);
	DDX_Control(pDX, IDC_CK_PFLFELD_55, m_F_55);
	DDX_Control(pDX, IDC_CK_PFLFELD_56, m_F_56);
	DDX_Control(pDX, IDC_CK_PFLFELD_57, m_F_57);
	DDX_Control(pDX, IDC_CK_PFLFELD_58, m_F_58);
	DDX_Control(pDX, IDC_CK_PFLFELD_59, m_F_59);
	DDX_Control(pDX, IDC_CK_PFLFELD_60, m_F_60);
	DDX_Control(pDX, IDC_CK_PFLFELD_61, m_F_61);
	DDX_Control(pDX, IDC_CK_PFLFELD_62, m_F_62);
	DDX_Control(pDX, IDC_CK_PFLFELD_63, m_F_63);
	DDX_Control(pDX, IDC_CK_PFLFELD_64, m_F_64);
	//}}AFX_DATA_MAP
}

/*------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CPflFelder, CDialogMultiLang)
	//{{AFX_MSG_MAP(CPflFelder)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*------------------------------------------------------------------------*/
void CPflFelder::MakeDialog()
{
	m_Pos_First_Feld = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_F_00 );
	m_dlg.InitDialog( m_F_01 );
	m_dlg.InitDialog( m_F_02 );
	m_dlg.InitDialog( m_F_03 );
	m_dlg.InitDialog( m_F_04 );
	m_dlg.InitDialog( m_F_05 );
	m_dlg.InitDialog( m_F_06 );
	m_dlg.InitDialog( m_F_07 );
	m_dlg.InitDialog( m_F_08 );
	m_dlg.InitDialog( m_F_09 );
	m_dlg.InitDialog( m_F_10 );
	m_dlg.InitDialog( m_F_11 );
	m_dlg.InitDialog( m_F_12 );
	m_dlg.InitDialog( m_F_13 );
	m_dlg.InitDialog( m_F_14 );
	m_dlg.InitDialog( m_F_15 );
	m_dlg.InitDialog( m_F_16 );
	m_dlg.InitDialog( m_F_17 );
	m_dlg.InitDialog( m_F_18 );
	m_dlg.InitDialog( m_F_19 );
	m_dlg.InitDialog( m_F_20 );
	m_dlg.InitDialog( m_F_21 );
	m_dlg.InitDialog( m_F_22 );
	m_dlg.InitDialog( m_F_23 );
	m_dlg.InitDialog( m_F_24 );
	m_dlg.InitDialog( m_F_25 );
	m_dlg.InitDialog( m_F_26 );
	m_dlg.InitDialog( m_F_27 );
	m_dlg.InitDialog( m_F_28 );
	m_dlg.InitDialog( m_F_29 );
	m_dlg.InitDialog( m_F_30 );
	m_dlg.InitDialog( m_F_31 );
	m_dlg.InitDialog( m_F_32 );
	m_dlg.InitDialog( m_F_33 );
	m_dlg.InitDialog( m_F_34 );
	m_dlg.InitDialog( m_F_35 );
	m_dlg.InitDialog( m_F_36 );
	m_dlg.InitDialog( m_F_37 );
	m_dlg.InitDialog( m_F_38 );
	m_dlg.InitDialog( m_F_39 );
	m_dlg.InitDialog( m_F_40 );
	m_dlg.InitDialog( m_F_41 );
	m_dlg.InitDialog( m_F_42 );
	m_dlg.InitDialog( m_F_43 );
	m_dlg.InitDialog( m_F_44 );
	m_dlg.InitDialog( m_F_45 );
	m_dlg.InitDialog( m_F_46 );
	m_dlg.InitDialog( m_F_47 );
	m_dlg.InitDialog( m_F_48 );
	m_dlg.InitDialog( m_F_49 );
	m_dlg.InitDialog( m_F_50 );
	m_dlg.InitDialog( m_F_51 );
	m_dlg.InitDialog( m_F_52 );
	m_dlg.InitDialog( m_F_53 );
	m_dlg.InitDialog( m_F_54 );
	m_dlg.InitDialog( m_F_55 );
	m_dlg.InitDialog( m_F_56 );
	m_dlg.InitDialog( m_F_57 );
	m_dlg.InitDialog( m_F_58 );
	m_dlg.InitDialog( m_F_59 );
	m_dlg.InitDialog( m_F_60 );
	m_dlg.InitDialog( m_F_61 );
	m_dlg.InitDialog( m_F_62 );
	m_dlg.InitDialog( m_F_63 );

	// muss immer VOR dem letzten InitDialog stehen
	m_Pos_Last_Feld = m_dlg.GetFieldNumber();

	m_dlg.InitDialog( m_F_64 );

	m_nMaxFields = m_dlg.GetFieldNumber();	
}

/*------------------------------------------------------------------------*/
void CPflFelder::InitPflege( int iMode )
{
	MakeDialog();
	m_UpdMode = iMode;
	InitTexte( );

	m_F_00.SetMask( 1, 0, &FELDER[0].iAktiv );
	m_F_01.SetMask( 1, 0, &FELDER[1].iAktiv );
	m_F_02.SetMask( 1, 0, &FELDER[2].iAktiv );
	m_F_03.SetMask( 1, 0, &FELDER[3].iAktiv );
	m_F_04.SetMask( 1, 0, &FELDER[4].iAktiv );
	m_F_05.SetMask( 1, 0, &FELDER[5].iAktiv );
	m_F_06.SetMask( 1, 0, &FELDER[6].iAktiv );
	m_F_07.SetMask( 1, 0, &FELDER[7].iAktiv );
	m_F_08.SetMask( 1, 0, &FELDER[8].iAktiv );
	m_F_09.SetMask( 1, 0, &FELDER[9].iAktiv );
	m_F_10.SetMask( 1, 0, &FELDER[10].iAktiv );
	m_F_11.SetMask( 1, 0, &FELDER[11].iAktiv );
	m_F_12.SetMask( 1, 0, &FELDER[12].iAktiv );
	m_F_13.SetMask( 1, 0, &FELDER[13].iAktiv );
	m_F_14.SetMask( 1, 0, &FELDER[14].iAktiv );
	m_F_15.SetMask( 1, 0, &FELDER[15].iAktiv );
	m_F_16.SetMask( 1, 0, &FELDER[16].iAktiv );
	m_F_17.SetMask( 1, 0, &FELDER[17].iAktiv );
	m_F_18.SetMask( 1, 0, &FELDER[18].iAktiv );
	m_F_19.SetMask( 1, 0, &FELDER[19].iAktiv );
	m_F_20.SetMask( 1, 0, &FELDER[20].iAktiv );
	m_F_21.SetMask( 1, 0, &FELDER[21].iAktiv );
	m_F_22.SetMask( 1, 0, &FELDER[22].iAktiv );
	m_F_23.SetMask( 1, 0, &FELDER[23].iAktiv );
	m_F_24.SetMask( 1, 0, &FELDER[24].iAktiv );
	m_F_25.SetMask( 1, 0, &FELDER[25].iAktiv );
	m_F_26.SetMask( 1, 0, &FELDER[26].iAktiv );
	m_F_27.SetMask( 1, 0, &FELDER[27].iAktiv );
	m_F_28.SetMask( 1, 0, &FELDER[28].iAktiv );
	m_F_29.SetMask( 1, 0, &FELDER[29].iAktiv );
	m_F_30.SetMask( 1, 0, &FELDER[30].iAktiv );
	m_F_31.SetMask( 1, 0, &FELDER[31].iAktiv );
	m_F_32.SetMask( 1, 0, &FELDER[32].iAktiv );
	m_F_33.SetMask( 1, 0, &FELDER[33].iAktiv );
	m_F_34.SetMask( 1, 0, &FELDER[34].iAktiv );
	m_F_35.SetMask( 1, 0, &FELDER[35].iAktiv );
	m_F_36.SetMask( 1, 0, &FELDER[36].iAktiv );
	m_F_37.SetMask( 1, 0, &FELDER[37].iAktiv );
	m_F_38.SetMask( 1, 0, &FELDER[38].iAktiv );
	m_F_39.SetMask( 1, 0, &FELDER[39].iAktiv );
	m_F_40.SetMask( 1, 0, &FELDER[40].iAktiv );
	m_F_41.SetMask( 1, 0, &FELDER[41].iAktiv );
	m_F_42.SetMask( 1, 0, &FELDER[42].iAktiv );
	m_F_43.SetMask( 1, 0, &FELDER[43].iAktiv );
	m_F_44.SetMask( 1, 0, &FELDER[44].iAktiv );
	m_F_45.SetMask( 1, 0, &FELDER[45].iAktiv );
	m_F_46.SetMask( 1, 0, &FELDER[46].iAktiv );
	m_F_47.SetMask( 1, 0, &FELDER[47].iAktiv );
	m_F_48.SetMask( 1, 0, &FELDER[48].iAktiv );
	m_F_49.SetMask( 1, 0, &FELDER[49].iAktiv );
	m_F_50.SetMask( 1, 0, &FELDER[50].iAktiv );
	m_F_51.SetMask( 1, 0, &FELDER[51].iAktiv );
	m_F_52.SetMask( 1, 0, &FELDER[52].iAktiv );
	m_F_53.SetMask( 1, 0, &FELDER[53].iAktiv );
	m_F_54.SetMask( 1, 0, &FELDER[54].iAktiv );
	m_F_55.SetMask( 1, 0, &FELDER[55].iAktiv );
	m_F_56.SetMask( 1, 0, &FELDER[56].iAktiv );
	m_F_57.SetMask( 1, 0, &FELDER[57].iAktiv );
	m_F_58.SetMask( 1, 0, &FELDER[58].iAktiv );
	m_F_59.SetMask( 1, 0, &FELDER[59].iAktiv );
	m_F_60.SetMask( 1, 0, &FELDER[60].iAktiv );
	m_F_61.SetMask( 1, 0, &FELDER[61].iAktiv );
	m_F_62.SetMask( 1, 0, &FELDER[62].iAktiv );
	m_F_63.SetMask( 1, 0, &FELDER[63].iAktiv );
	m_F_64.SetMask( 1, 0, &FELDER[64].iAktiv );
}

/*-------------------------- ZCHARGENRUECKRUF ----------------------------------------------*/
static ZCHARGENRUECKRUF *pZchargenrr;

static COMBO_MASK C_RUECKRUF_KZ =
{
	{ "A\nB\nC\nD\n" },
	{ "ABCD" },
	0,
	1
};

static COMBO_MASK C_EINSCHRAENKUNGEN =
{
	{ "00\n01\n02\n03\n04\n" },
	{ "0001020304" },
	0,
	2
};

static COMBO_MASK C_ANTWORT_NWE_RR =
{
	{ "0\n1\n" },
	{ "01" },
	0,
	1
};

static EDIT_MASK E_CHARGE = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZCHARGENRUECKRUF_CHARGE, 
	0, 
	NR_MASKCHAR, 
	VAL_CHARGE
};

static EDIT_MASK E_FRAGE_NEUER_WE = 
{
	ED_CHAR, 
	ED_NORMAL,  
	L_ZCHARGENRUECKRUF_FRAGE_NEUER_WE, 
	0, 
	NR_MASKCHAR, 
	VAL_FRAGE_NEUER_WE
};

static EDIT_MASK E_DATETO_GI = 
{
	ED_LDATE, 
	ED_NORMAL,  
	L_LDATUM, 
	0, 
	NR_MASKLDATE, 
	VAL_DATETO_GI
};

static EDIT_MASK E_DATETO_CUSTRETURNS = 
{
	ED_LDATE, 
	ED_NORMAL,  
	L_LDATUM, 
	0, 
	NR_MASKLDATE, 
	VAL_DATETO_CUSTRETURNS
};

static struct PFL_FELD FELDER_ZCHARGENRR[] = 
{
	{ 0, A_EDIT,  &E_CHARGE,			&pZchargenrr->CHARGE,			"Charge"	,						"CHARGE" },
	{ 0, A_COMBO, &C_RUECKRUF_KZ,		&pZchargenrr->RUECKRUF_KZ,		"Rückruf-KZ",						"RUECKRUF_KZ" },
	{ 0, A_COMBO, &C_EINSCHRAENKUNGEN,	&pZchargenrr->EINSCHRAENKUNGEN,	"Einschränkung",					"EINSCHRAENKUNGEN" },
	{ 0, A_COMBO, &C_ANTWORT_NWE_RR,	&pZchargenrr->ANTWORT_NWE_RR,	"RR bei Antwort (0=nein)"		,	"ANTWORT_NWE_RR"  },
	{ 0, A_EDIT,  &E_FRAGE_NEUER_WE,	&pZchargenrr->FRAGE_NEUER_WE,	"Frage GI"	,						"FRAGE_NEUER_WE" },
	{ 0, A_EDIT,  &E_DATETO_GI,			&pZchargenrr->DATETO_GI,		"Datum GI"			,				"DATETO_GI" },
	{ 0, A_EDIT,  &E_DATETO_CUSTRETURNS,&pZchargenrr->DATETO_CUSTRETURNS,"Datum Retouren",					"DATETO_CUSTRETURNS" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- ZARTIKEL ----------------------------------------------*/
static ZARTIKEL *pZart;

static COMBO_MASK C_NAHRUNGSERGAENZUNG =
{
	{ "N\nV\nB\nG\n" },
	{ "NVBG" },
	0,
	1
};

static COMBO_MASK C_NAHRUNGSTEST =
{
	{ " \nK\nZ\nL\n*\nD\nU\nF\n" },
	{ " KZL*DUF" },
	0,
	1
};

static COMBO_MASK C_PREISSENKUNG =
{
	{ "0\n1\n2\n3\n4\n5\n" },
	{ "012345" },
	0,
	1
};

static COMBO_MASK C_AWL_AKTIV =
{
	{ "N\nJ\nZ\n" },
	{ "NJZ" },
	0,
	1
};

static EDIT_MASK E_AWL1 = 
{
	ED_LONG, 
	ED_NORMAL,  
	L_HERSTELLER_NR, 
	0, 
	NR_MASKNUM, 
	VAL_AWL1
};

static EDIT_MASK E_HNR = 
{
	ED_LONG, 
	ED_NORMAL,  
	L_HERSTELLER_NR, 
	0, 
	NR_MASKNUM, 
	VAL_HNR
};

static EDIT_MASK E_ART_NR_HERST = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTIKEL_ARTIKEL_NR_HERST, 
	0, 
	NR_MASKCHAR, 
	VAL_ART_NR_HERST
};

static EDIT_MASK E_ART_NR_ORIG = 
{
	ED_LONG, 
	ED_UPPER,  
	L_CARTICLECODES_ARTICLE_CODE, 
	0, 
	NR_MASKNUM, 
	VAL_ART_NR_ORIG
};

static EDIT_MASK E_ART_DATUM_AH = 
{
	ED_LDATE, 
	ED_NORMAL,  
	L_LDATUM, 
	0, 
	NR_MASKLDATE, 
	VAL_ART_DATUMAH
};

static COMBO_MASK C_KUEHL =
{
	{ "0\n3\n2\n1\n4\n" },
	{ "03214" },
	0,
	1
};

static COMBO_MASK C_VERFALL =
{
	{ "0\n1\n2\n" },
	{ "012" },
	0,
	1
};

static COMBO_MASK C_PRODUKTART =
{
	{ "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n" },
	{ "0123456789" },
	0,
	1
};

// country specific valid values for Germany
static COMBO_MASK C_PRODUKTART_DE =
{
	{ "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\nF\n" },
	{ "0123456789F" },
	0,
	1
};

// country specific valid values for Switzerland
static COMBO_MASK C_PRODUKTART_CH = 
{
	{ "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\nA\nB\nC\nD\nE\n" },
	{ "0123456789ABCDE" },
	0,
	1
};

static COMBO_MASK C_NEGATIVLISTE =
{
	{ "0\n1\n2\n" },
	{ "012" },
	0,
	1
};

static COMBO_MASK C_ZENTRALPPELIST =
{
	{ "0\n1\n2\n8\n9\n" },
	{ "01289" },
	0,
	1
};

static COMBO_MASK C_BESTELL_NICHT_AUSL =
{
	{ "0\n1\n2\n" },
	{ "012" },
	0,
	1
};

static EDIT_MASK E_PRISMAEWOCHE = 
{
	ED_LONG, 
	ED_UPPER,  
	L_PRISMAEWOCHE, 
	0, 
	NR_MASKNUM, 
	VAL_PRISMAEWOCHE
};

static COMBO_MASK C_MVDAARTIKEL =
{
	{ "0\n1\n2\n3\n4\n5\n6\n8\n9\n" },
	{ "012345689" },
	0,
	1
};

static COMBO_MASK C_LAGEEMPF =
{
	{ "0\n1\n2\n" },
	{ "012" },
	0,
	1
};

static EDIT_MASK E_HERSTEL_PROZ = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ZARTPREIS_HERST_PROZENT + 2,
	N_ZARTPREIS_HERST_PROZENT,
	NR_MASKDBL,
	VAL_HERSTEL_PROZ
};

static COMBO_MASK C_BEZUGSSPERRE =
{
	{ "0\n1\n2\n3\n4\n5\n6\n7\n" },
	{ "01234567" },
	0,
	1
};

static EDIT_MASK E_G_UN_NR =
{
	ED_CHAR,
	ED_UPPER,
	4,
	0,
	NR_MASKNUM,
	VAL_G_UN_NR
};

static EDIT_MASK E_DATUM_LIEFERBAR_AB =
{
	ED_LONG,
	ED_UPPER,
	10,
	0,
	NR_MASKNUM,
	VAL_DATUM_LIEFERBAR_AB
};

static EDIT_MASK E_LAENGE =
{
	ED_LONG,
	ED_NORMAL,
	6,
	0,
	NR_MASKNUM,
	VAL_NO
};

static EDIT_MASK E_BREITE =
{
	ED_LONG,
	ED_NORMAL,
	6,
	0,
	NR_MASKNUM,
	VAL_NO
};

static EDIT_MASK E_HOEHE =
{
	ED_LONG,
	ED_NORMAL,
	6,
	0,
	NR_MASKNUM,
	VAL_NO
};

static EDIT_MASK E_GEWICHT =
{
	ED_LONG,
	ED_NORMAL,
	6,
	0,
	NR_MASKNUM,
	VAL_NO
};

static EDIT_MASK E_ART_DATUM_MWE =
{
	ED_LDATE,
	ED_NORMAL,
	L_LDATUM,
	0,
	NR_MASKLDATE,
	VAL_ART_DATUMAH
};

static EDIT_MASK E_NACHLIEFERUNG =
{
	ED_LONG,
	ED_NORMAL,
	6,
	0,
	NR_MASKNUM,
	VAL_KONTMENGENST
};

static EDIT_MASK E_ERSATZ_NR =
{
	ED_LONG,
	ED_NORMAL,
	10,
	0,
	NR_MASKNUM,
	VAL_NO
};

static EDIT_MASK E_DARREICHFORM =
{
	ED_CHAR,
	ED_UPPER,
	L_ZARTIKEL_DARREICHFORM,
	0,
	NR_MASKCHAR,
	VAL_DARREICHFORM
};

static EDIT_MASK E_KONSIG_P_NR =
{
	ED_LONG,
	ED_NORMAL,
	10,
	0,
	NR_MASKNUM,
	VAL_NO
};

static struct PFL_FELD FELDER_ZART[] = 
{
	{ 0, A_BUTTON,	NULL,					&pZart->EKORIGINALHS,				"Einkauf nur beim Originalhersteller",	"EKORIGINALHS" },
	{ 0, A_BUTTON,	NULL,					&pZart->ZENTR_EKSPERRE,				"Einkauf gesperrt",						"ZENTR_EKSPERRE" },
	{ 0, A_BUTTON,	NULL,					&pZart->NIEDRSPANNE_ELAC,			"Prisma – keine Rabattierung",			"NIEDRSPANNE_ELAC" },
	{ 0, A_BUTTON,	NULL,					&pZart->NIEDRSPANNE_SONST,			"Basis-Art. (Niedrigsp.)",				"NIEDRSPANNE_SONST" },
	{ 0, A_COMBO,	&C_NAHRUNGSERGAENZUNG,	&pZart->NAHRUNGSERGAENZUNG,			"Nahrungsergänzung",					"NAHRUNGSERGAENZUNG" },
	{ 0, A_COMBO,	&C_NAHRUNGSTEST,		&pZart->NAHRUNGSTEST,				"NEM-Artikel",							"NAHRUNGSTEST" },
	{ 0, A_COMBO,	&C_PREISSENKUNG,		&pZart->PREISSENKUNG,				"Preissenkung",							"PREISSENKUNG"  },
	{ 0, A_EDIT,	&E_AWL1,				&pZart->AWL1,						"Ausweichlieferant",					"AWL1" },
	{ 0, A_COMBO,	&C_AWL_AKTIV,			&pZart->AWL_AKTIV,					"AWL aktiv",							"AWL_AKTIV" },
	{ 0, A_EDIT,	&E_ART_NR_HERST,		&pZart->ARTIKEL_NR_HERST,			"Art.Nr. Herst.",						"ARTIKEL_NR_HERST" },
	{ 0, A_EDIT,	&E_ART_DATUM_AH,		&pZart->DATUM_AH,					"AH-Datum",								"DATUM_AH" },
	{ 0, A_BUTTON,	NULL,					&pZart->SORTIMENT_1,				"Sondersortiment 1",					"SORTIMENT_1" },
	{ 0, A_BUTTON,	NULL,					&pZart->SORTIMENT_2,				"Sondersortiment 2",					"SORTIMENT_2" },
	{ 0, A_BUTTON,	NULL,					&pZart->SORTIMENT_3,				"Sondersortiment 3",					"SORTIMENT_3" },
	{ 0, A_BUTTON,	NULL,					&pZart->SORTIMENT_4,				"Sondersortiment 4",					"SORTIMENT_4" },
	{ 0, A_BUTTON,	NULL,					&pZart->SORTIMENT_5,				"Sondersortiment 5",					"SORTIMENT_5" },
	{ 0, A_EDIT,	&E_HNR,					&pZart->HERSTELLER_NR,				"Hersteller",							"HERSTELLER_NR" },
	{ 0, A_COMBO,	&C_KUEHL,				&pZart->KUEHLARTIKEL,				"Kühlartikel",							"KUEHLARTIKEL" },
	{ 0, A_COMBO,	&C_VERFALL,				&pZart->VERFALL,					"Verfallkennz",							"VERFALL" },
	{ 0, A_EDIT,	&E_ART_NR_ORIG,			&pZart->ARTIKEL_NR_ORIG,			"Original-ArtNr.",						"ARTIKEL_NR_ORIG" },
	// country specific definition(s) for PRODUKTART set in InitCountrySpecificValidations()
	{ 0, A_COMBO,	&C_PRODUKTART,			&pZart->PRODUKTART,					"Produktart",							"PRODUKTART" },
	{ 0, A_COMBO,	&C_NEGATIVLISTE,		&pZart->NEGATIVLISTE,				"Negativliste",							"NEGATIVLISTE" },
	{ 0, A_BUTTON,	NULL,					&pZart->SKONTOFAEHIG,				"Skontofähig",							"SKONTOFAEHIG" },
	{ 0, A_BUTTON,	NULL,					&pZart->PREIS0ARTIKEL,				"Preis 0 Artikel",						"PREIS0ARTIKEL" },
	{ 0, A_BUTTON,	NULL,					&pZart->VERBUNDSPERRE,				"Verbundsperre",						"VERBUNDSPERRE" },
	{ 0, A_COMBO,	&C_ZENTRALPPELIST,		&pZart->ZENTRALPPELIST,				"PPE-Stammlager",						"ZENTRALPPELIST" },
	{ 0, A_BUTTON,	NULL,					&pZart->FAELSCH_GEFAHR,				"Fälschungsgefahr",						"FAELSCH_GEFAHR" },
	{ 0, A_BUTTON,	NULL,					&pZart->RETOURENSPERRE,				"Retourensperre",						"RETOURENSPERRE" },
	{ 0, A_BUTTON,	NULL,					&pZart->BESTELL_NUR_OZEK,			"ZWH-Einkauf nur über OZEK",			"BESTELL_NUR_OZEK" },
	{ 0, A_COMBO,	&C_BESTELL_NICHT_AUSL,	&pZart->BESTELL_NICHT_AUSL,			"EK Ausland",							"BESTELL_NICHT_AUSL" },
	{ 0, A_EDIT,	&E_PRISMAEWOCHE,		&pZart->PRISMAEWOCHE,				"Prisma-E-Woche",						"PRISMAEWOCHE" },
	{ 0, A_COMBO,	&C_MVDAARTIKEL,			&pZart->MVDAARTIKEL,				"MVDA-Artikel",							"MVDAARTIKEL" },
	{ 0, A_EDIT,	&E_HERSTEL_PROZ,		&pZart->HERST_PROZENT,				"Hersteller Prozent",					"HERST_PROZENT" },
	{ 0, A_BUTTON,	NULL,					&pZart->ARTIKEL_GESPERRT,			"Artikel gesperrt",						"ARTIKEL_GESPERRT" },
	{ 0, A_BUTTON,	NULL,					&pZart->ARTIKEL_GELOESCHT,			"Löschkennzeichen",						"ARTIKEL_GELOESCHT" },
	{ 0, A_BUTTON,	NULL,					&pZart->NICHT_UEBER_XML,			"nicht über XML",						"NICHT_UEBER_XML" },
	{ 0, A_COMBO,	&C_BEZUGSSPERRE,		&pZart->BEZUGSSPERRE,				"Bezugssperre",							"BEZUGSSPERRE" },
	{ 0, A_BUTTON,	NULL,					&pZart->NEM_PHAGROPRUEFUNG,			"NEM-Phagroprüfung",					"NEM_PHAGROPRUEFUNG" },
	{ 0, A_BUTTON,	NULL,					&pZart->NEM_ZERTIFIKAT,				"NEM-Zertifikat",						"NEM_ZERTIFIKAT" },
	{ 0, A_BUTTON,	NULL,					&pZart->APO_AUTO_FAEHIG_KNAPP,		"Apo-Auto KNAPP",						"APO_AUTO_FAEHIG_KNAPP" },
	{ 0, A_BUTTON,	NULL,					&pZart->APO_AUTO_FAEHIG_ROWA,		"Apo-Auto ROWA",						"APO_AUTO_FAEHIG_ROWA" },
	{ 0, A_BUTTON,	NULL,					&pZart->CHARGENARTIKEL,				"Chargenartikel",						"CHARGENARTIKEL" },
	{ 0, A_EDIT,	&E_G_UN_NR,				&pZart->G_UN_NR,					"UN-Nummer",							"G_UN_NR" },
	{ 0, A_EDIT,	&E_DATUM_LIEFERBAR_AB,	&pZart->DATUM_LIEFERBAR_AB,			"Datum Lieferbar ab",					"DATUM_LIEFERBAR_AB" },
	{ 0, A_BUTTON,	NULL,					&pZart->BESTELLSPERRE,				"Einkauf nicht möglich"	,				"BESTELLSPERRE" },
	{ 0, A_BUTTON,	NULL,					&pZart->CMI_FLAG,					"DG (Direktgeschäft/CMI)",				"CMI_FLAG" },
	{ 0, A_EDIT,	&E_LAENGE,				&pZart->LAENGE,						"Länge",								"LAENGE" },
	{ 0, A_EDIT,	&E_HOEHE,				&pZart->HOEHE,						"Höhe",									"HOEHE" },
	{ 0, A_EDIT,	&E_BREITE,				&pZart->BREITE,						"Breite",								"BREITE" },
	{ 0, A_EDIT,	&E_GEWICHT,				&pZart->GEWICHT,					"Gewicht",								"GEWICHT" },
	{ 0, A_EDIT,	&E_ART_DATUM_MWE,		&pZart->DATUM_MWE,					"MWE-Datum",							"DATUM_MWE" },
	{ 0, A_BUTTON,	NULL,					&pZart->KONTINGENT_MENGENSTEUERUNG,	"Kontingent-Mengenst.",					"KONTINGENT_MENGENSTEUERUNG" },
	{ 0, A_EDIT,	&E_DARREICHFORM,		&pZart->DARREICHFORM,				"Darreichform",							"DARREICHFORM" },
	{ 0, A_BUTTON,	NULL,					&pZart->KONTINGENT_PPE,				"Kontingent_PPE",						"KONTINGENT_PPE" },
	{ 0, A_COMBO,	&C_LAGEEMPF,			&pZart->LAGEEMPF,					"Lageempf",								"LAGEEMPF" },
	{ 0, A_EDIT,	&E_ERSATZ_NR,			&pZart->ERSATZ_NR,					"Ersatz_Nr",							"ERSATZ_NR" },
	{ 0, A_BUTTON,	NULL,					&pZart->ERSATZ_NR_AKTIV,			"Ersatz_Nr_Aktiv",						"ERSATZ_NR_AKTIV" },
	{ 0, A_EDIT,	&E_KONSIG_P_NR,			&pZart->KONSIG_PARTNER_NR,			"Konsignment Partner Nr",				"KONSIG_PARTNER_NR" },
	{ 0, A_BUTTON,	NULL,					NULL,								EMPTY_STRING,							EMPTY_STRING },
	{ 0, A_BUTTON,	NULL,					NULL,								EMPTY_STRING,							EMPTY_STRING },
	{ 0, A_BUTTON,	NULL,					NULL,								EMPTY_STRING,							EMPTY_STRING },
	{ 0, A_BUTTON,	NULL,					NULL,								EMPTY_STRING,							EMPTY_STRING },
	{ 0, A_BUTTON,	NULL,					NULL,								EMPTY_STRING,							EMPTY_STRING },
	{ 0, A_BUTTON,	NULL,					NULL,								EMPTY_STRING,							EMPTY_STRING },
	{ 0, A_BUTTON,	NULL,					NULL,								EMPTY_STRING,							EMPTY_STRING }
};

/*-------------------------- ZARTSERBIA ----------------------------------------------*/
static ZARTSERBIA *pArtSerbia;

static struct PFL_FELD FELDER_ZARTSERBIA[] =
{
	{ 0, A_BUTTON, NULL,				&pArtSerbia->DISTR_RESTR_TEND,	"TEND (Distr.Restr.)"	, "DISTR_RESTR_TEND" },
	{ 0, A_BUTTON, NULL,				&pArtSerbia->DISTR_RESTR_BETY,	"BETY (Distr.Restr.)"	, "DISTR_RESTR_BETY" },
	{ 0, A_BUTTON, NULL,				&pArtSerbia->DISTR_RESTR_BENU,	"BENU (Distr.Restr.)"	, "DISTR_RESTR_BENU" },
	{ 0, A_BUTTON, NULL,				&pArtSerbia->DISTR_RESTR_ALRG,	"ALRG (Distr.Restr.)"	, "DISTR_RESTR_ALRG" },
	{ 0, A_BUTTON, NULL,				&pArtSerbia->DISTR_RESTR_CAUD,	"CAUD (Distr.Restr.)"	, "DISTR_RESTR_CAUD" },
	{ 0, A_BUTTON, NULL,				&pArtSerbia->DISTR_RESTR_HEM,	"HEM (Distr.Restr.)"	, "DISTR_RESTR_HEM" },
	{ 0, A_BUTTON, NULL,				&pArtSerbia->DISTR_RESTR_GR7,	"NARC (Distr.Restr.)"	, "DISTR_RESTR_GR7" },
	{ 0, A_BUTTON, NULL,				&pArtSerbia->DISTR_RESTR_GR8,	"GR8 (Distr.Restr.)"	, "DISTR_RESTR_GR8" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- ZARTAUSTRIA ----------------------------------------------*/
static ZARTAUSTRIA *pArtAustria;

static struct PFL_FELD FELDER_ZARTAUSTRIA[] =
{
	{ 0, A_BUTTON, NULL,				&pArtAustria->NACHLIEFERUNG,	"Wafo-Artikel"	, "NACHLIEFERUNG" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};



/*-------------------------- ZARTSWITZERLAND ----------------------------------------------*/
static ZARTSWITZERLAND *pArtSwitzerland;

static EDIT_MASK E_PFLICHTLAGERMENGE = 
{
	ED_LONG, 
	ED_NORMAL,  
	6, 
	0, 
	NR_MASKNUM, 
	VAL_ART_PFLICHTLAGERMENGE
};

static EDIT_MASK E_WARNPROZVORPLM = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ZARTSWITZERLAND_WARNPROZVORPLM + 1,
	N_ZARTSWITZERLAND_WARNPROZVORPLM,
	NR_MASKDBLPOS,
	VAL_ART_WARNPROZVORPLM
};

static EDIT_MASK E_IKS_CODE = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTSWITZERLAND_IKS_CODE,
	0,
	NR_MASKCHAR,
	VAL_IKS_CODE
};

static EDIT_MASK E_MIGCD = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTSWITZERLAND_MIGCD,
	0,
	NR_MASKCHAR,
	VAL_MIGCD
};

static struct PFL_FELD FELDER_ZARTSWITZERLAND[] =
{
	{ 0, A_EDIT,  &E_WARNPROZVORPLM,	&pArtSwitzerland->WARNPROZVORPLM,			"Warnung % vor PflLagMg"	,	"WARNPROZVORPLM" },
	{ 0, A_EDIT,  &E_PFLICHTLAGERMENGE, &pArtSwitzerland->PFLICHTLAGERMENGE,		"Pflichtlagermenge"			,	"PFLICHTLAGERMENGE" },
	{ 0, A_EDIT,  &E_IKS_CODE,			&pArtSwitzerland->IKS_CODE,					"IKS/Swissmedicliste",			"IKS_CODE" },
	{ 0, A_EDIT,  &E_MIGCD,				&pArtSwitzerland->MIGCD,					"Mig CD",						"MIGCD" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- CIMEXBLOCK ----------------------------------------------*/
static CIMEXBLOCK *pCImexBlock;

static COMBO_MASK C_IMEX_MODE =
{
	{ "0\n1\n" },
	{ "01" },
	0,
	1
};

static EDIT_MASK E_COUNTRY_IFACODE = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_CIMEXBLOCK_COUNTRY_IFACODE, 
	0, 
	NR_MASKCHAR, 
	VAL_IMEX_COUNTRY
};

static struct PFL_FELD FELDER_CIMEXBLOCK[] =
{
	{ 0, A_EDIT,  &E_COUNTRY_IFACODE,	&pCImexBlock->COUNTRY_IFACODE,	"Land"	,						"COUNTRY_IFACODE" },
	{ 0, A_COMBO, &C_IMEX_MODE,			&pCImexBlock->IMEX_MODE,		"Import(0) / Export(1)"		,	"IMEX_MODE"  },
	{ 0, A_BUTTON, NULL,				NULL						,	"Sperre (0=entfernen/1=setzen)", "BLOCK_FLAG" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- ZARTFRANCE ----------------------------------------------*/
static ZARTFRANCE *pArtFrance;

static COMBO_MASK C_REIMBURSEMENT_TYPE =
{
	{ "0\n1\n2\n3\n" },
	{ "0123" },
	0,
	1
};

static EDIT_MASK E_CODE_LPPR = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTFRANCE_CODE_LPPR, 
	0, 
	NR_MASKCHAR, 
	VAL_ART_CODE_LPPR
};

static EDIT_MASK E_REIMBURSEMENT_PERC = 
{
	ED_LONG, 
	ED_NORMAL,  
	3, 
	0, 
	NR_MASKNUM, 
	VAL_ART_REIMBURSEMENT_PERC
};

static EDIT_MASK E_TFR_BASE_PRICE = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ZARTFRANCE_TFR_BASE_PRICE + 1,
	N_ZARTFRANCE_TFR_BASE_PRICE,
	NR_MASKDBLPOS,
	VAL_ART_TFR_BASE_PRICE
};

static EDIT_MASK E_DISTRRESTREXPORT =
{
	ED_SHORT,
	ED_NORMAL,
	1,
	0,
	NR_MASKNUM,
	VAL_DISTR_RESTR_EXPORT
};

static COMBO_MASK C_CODE_BLOQUAGE =
{
	{ "0\n2\n3\n4\n8\n9\nC\nH\nS\n" },
	{ "023489CHS" },
	0,
	1
};

static struct PFL_FELD FELDER_ZARTFRANCE[] =
{
	{ 0, A_COMBO, &C_CODE_BLOQUAGE,		&pArtFrance->CODE_BLOQUAGE,		"Code Bloquage"			,	"CODE_BLOQUAGE"  },
	{ 0, A_COMBO, &C_REIMBURSEMENT_TYPE,&pArtFrance->REIMBURSEMENT_TYPE,"Erstattungs-Typ"		,	"REIMBURSEMENT_TYPE"  },
	// CR-16A023 { 0, A_EDIT,  &E_CODE_LPPR,			&pArtFrance->CODE_LPPR,			"LPPR-Code"				,	"CODE_LPPR" },
	{ 0, A_EDIT,  &E_REIMBURSEMENT_PERC,&pArtFrance->REIMBURSEMENT_PERC,"Erstattungs-Prozent"	,	"REIMBURSEMENT_PERC" },
	{ 0, A_EDIT,  &E_TFR_BASE_PRICE,	&pArtFrance->TFR_BASE_PRICE,	"Erstattungs-Basispreis",	"TFR_BASE_PRICE" },
	{ 0, A_EDIT,  &E_DISTRRESTREXPORT,	&pArtFrance->DISTR_RESTR_EXPORT,	"Export interdit"   ,	"DISTR_RESTR_EXPORT" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- CARTICLECODES ----------------------------------------------*/
static CARTICLECODES *pCodes;

static EDIT_MASK E_ARTICLECODE = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_CARTICLECODES_ARTICLE_CODE, 
	0, 
	NR_MASKCHAR, 
	VAL_ART_CODE
};

static COMBO_MASK C_CODETYPE =
{
	{ "02\n06\n14\n25\n26\n27\n" },
	{ "020614252627" },
	0,
	2
};

static struct PFL_FELD FELDER_CARTICLECODES[] =
{
	{ 0, A_COMBO, &C_CODETYPE,			&pCodes->CODE_TYPE,		"Typ(2=Atc,6=Intra,14=Ephm,25=SAP,26=GTIN14)",	"CODE_TYPE"  },
	{ 0, A_EDIT,  &E_ARTICLECODE,		&pCodes->ARTICLE_CODE,	"Code"						,	"ARTICLE_CODE" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- ARTVE ----------------------------------------------*/
static ARTVE *pArtVe;

static EDIT_MASK E_VPE1 = 
{
	ED_LONG, 
	ED_CLINPUT,  
	L_VERPACKEINHEIT, 
	0, 
	NR_MASKNUM, 
	VAL_VPE1
};

static EDIT_MASK E_VPE2 = 
{
	ED_LONG, 
	ED_CLINPUT,  
	L_VERPACKEINHEIT, 
	0, 
	NR_MASKNUM, 
	VAL_VPE2
};

static EDIT_MASK E_VPE3 = 
{
	ED_LONG, 
	ED_CLINPUT,  
	L_VERPACKEINHEIT, 
	0, 
	NR_MASKNUM, 
	VAL_VPE3
};

static EDIT_MASK E_VPE4 = 
{
	ED_LONG, 
	ED_CLINPUT,  
	L_VERPACKEINHEIT, 
	0, 
	NR_MASKNUM, 
	VAL_VPE4
};

static EDIT_MASK E_ORIG_KART = 
{
	ED_LONG, 
	ED_CLINPUT,  
	L_VERPACKEINHEIT, 
	0, 
	NR_MASKNUM, 
	VAL_ORIG_KART
};

static struct PFL_FELD FELDER_ARTVE[] =
{
	{ 0, A_EDIT,   &E_VPE1,		&pArtVe->VERPACKEINHEIT1,"Verpack-Einheit-1",  "VERPACKEINHEIT1" },
	{ 0, A_EDIT,   &E_VPE2,		&pArtVe->VERPACKEINHEIT2,"Verpack-Einheit-2",  "VERPACKEINHEIT2" },
	{ 0, A_EDIT,   &E_VPE3,		&pArtVe->VERPACKEINHEIT3,"Verpack-Einheit-3",  "VERPACKEINHEIT3" },
	{ 0, A_EDIT,   &E_VPE4,		&pArtVe->VERPACKEINHEIT4,"Verpack-Einheit-4",  "VERPACKEINHEIT4" },
	{ 0, A_EDIT,   &E_ORIG_KART,&pArtVe->ORIGINALKARTON ,"Einheiten pro Originalkarton",  "ORIGINALKARTON" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- ZARTPREIS ----------------------------------------------*/
static ZARTPREIS *pZPreis;

/* TH if ( IsCountry("F") )
{
	static COMBO_MASK C_KE_MWST =
	{
		{ "0\n1\n2\n3\n" },
		{ "0123" },
		0,
		1
	};
}
else if ( IsCountry("HR") )
{
	static COMBO_MASK C_KE_MWST =
	{
		{ "0\n1\n" },
		{ "01" },
		0,
		1
	};
}
else
{*/
	static COMBO_MASK C_KE_MWST =
	{
		{ "0\n1\n \n" },
		{ "01 " },
		0,
		1
	};
//}


static EDIT_MASK E_GUELTIGAB = 
{
	ED_LDATE, 
	ED_NORMAL,  
	L_LDATUM, 
	0, 
	NR_MASKLDATE, 
	VAL_PREIS_GUELTIGAB
};

static EDIT_MASK E_GROSSO = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ZARTPREIS_GROSSO + 1,
	N_ZARTPREIS_GROSSO,
	NR_MASKDBLPOS,
	VAL_PREIS_GROSSO
};

static EDIT_MASK E_AEP = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ZARTPREIS_AEP + 1,
	N_ZARTPREIS_AEP,
	NR_MASKDBLPOS,
	VAL_PREIS_AEP
};

static EDIT_MASK E_AVP = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ZARTPREIS_AVP + 1,
	N_ZARTPREIS_AVP,
	NR_MASKDBLPOS,
	VAL_PREIS_AVP
};

static EDIT_MASK E_MAX_AEP = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ZARTPREIS_MAXAEP + 1,
	N_ZARTPREIS_MAXAEP,
	NR_MASKDBLPOS,
	VAL_PREIS_MAXAEP
};

static EDIT_MASK E_MAX_AVP = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ZARTPREIS_MAXAVP + 1,
	N_ZARTPREIS_MAXAVP,
	NR_MASKDBLPOS,
	VAL_PREIS_MAXAVP
};

static EDIT_MASK E_LBP = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ZARTPREIS_LIEFERBASISPREIS + 1,
	N_ZARTPREIS_LIEFERBASISPREIS,
	NR_MASKDBLPOS,
	VAL_PREIS_LBP
};

static EDIT_MASK E_AEP_ORIG = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ZARTPREIS_PHARMACY_BASEPRICE + 1,
	N_ZARTPREIS_PHARMACY_BASEPRICE,
	NR_MASKDBLPOS,
	VAL_PREIS_PHARMACY_BASEPRICE
};

static EDIT_MASK E_PUBL_NR = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTPREIS_PUBLICATIONNUMBER, 
	0, 
	NR_MASKCHAR, 
	VAL_PUBLICATIONNUMBER
};

static EDIT_MASK E_UVP =
{
	ED_DBL,
	ED_NORMAL,
	L_ZARTPREIS_EAVP + 1,
	N_ZARTPREIS_EAVP,
	NR_MASKDBLPOS,
	VAL_PREIS_EAVP
};

static struct PFL_FELD FELDER_ZPREIS[] =
{
	{ 0, A_EDIT,   &E_GUELTIGAB,		&pZPreis->DATUMGUELTIGAB,		"Datum gültig ab"	,	"DATUMGUELTIGAB" },
	{ 0, A_EDIT,   &E_GROSSO,			&pZPreis->GROSSO,				"Grosso"			,	"GROSSO" },
	{ 0, A_EDIT,   &E_AEP,				&pZPreis->AEP,					"Aep"				,	"AEP"  },
	{ 0, A_EDIT,   &E_AVP,				&pZPreis->AVP,					"Avp"				,	"AVP"  },
	{ 0, A_EDIT,   &E_LBP,				&pZPreis->LIEFERBASISPREIS,		"Lbp / Grosso original","LBP"  },
	{ 0, A_EDIT,   &E_AEP_ORIG,			&pZPreis->PHARMACY_BASEPRICE,	"Aep original"		,	"PHARMACY_BASEPRICE"  },
	{ 0, A_EDIT,   &E_MAX_AEP,			&pZPreis->MAXAEP,				"MaxAep"			,	"MAXAEP"  },
	{ 0, A_EDIT,   &E_MAX_AVP,			&pZPreis->MAXAVP,				"MaxAvp"			,	"MAXAVP"  },
	{ 0, A_EDIT,   &E_PUBL_NR,			&pZPreis->PUBLICATIONNUMBER,	"Publikationsnummer",	"PUBLICATIONNUMBER" },
	{ 0, A_EDIT,   &E_UVP,				&pZPreis->EAVP,					"Uvp"				,	"EAVP"  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- ZARTWG ----------------------------------------------*/
static ZARTWG *pZartwg;

static EDIT_MASK E_ART_1 = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_1
};

static EDIT_MASK E_ART_2 = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_2
};

static EDIT_MASK E_ART_3 = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_3
};

static EDIT_MASK E_ART_4 = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_4
};

static EDIT_MASK E_ART_5 = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_5
};

static EDIT_MASK E_ART_6 = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_6
};

static EDIT_MASK E_ART_7 = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_7
};

static EDIT_MASK E_ART_8 = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_8
};

static EDIT_MASK E_ART_9 = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_9
};

static EDIT_MASK E_ART_A = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_A
};

static EDIT_MASK E_ART_G = 
{
	ED_CHAR, 
	ED_UPPER,  
	L_ZARTWG_WARENGRUPPE, 
	0, 
	NR_MASKCHAR, 
	VAL_WG_ART_G
};

static struct PFL_FELD FELDER_ZARTWG[] =
{
	{ 0, A_EDIT,   &E_ART_1,			&pZartwg->WARENGRUPPE,	"IMS-Warengruppe (1)","WARENGRUPPE" },
	{ 0, A_EDIT,   &E_ART_2,			&pZartwg->WARENGRUPPE,	"Warengruppe (2)"	, "WARENGRUPPE" },
	{ 0, A_EDIT,   &E_ART_3,			&pZartwg->WARENGRUPPE,	"Therapiegruppe (3)", "WARENGRUPPE" },
	{ 0, A_EDIT,   &E_ART_4,			&pZartwg->WARENGRUPPE,	"ABDA-Code (4)"		, "WARENGRUPPE" },
	{ 0, A_EDIT,   &E_ART_5,			&pZartwg->WARENGRUPPE,	"Saison-Warengruppe (5)", "WARENGRUPPE" },
	{ 0, A_EDIT,   &E_ART_6,			&pZartwg->WARENGRUPPE,	"BTM-Gruppe (6)"	, "WARENGRUPPE" },
	{ 0, A_EDIT,   &E_ART_7,			&pZartwg->WARENGRUPPE,	"Artikeltexte (7)"	, "WARENGRUPPE" },
	{ 0, A_EDIT,   &E_ART_8,			&pZartwg->WARENGRUPPE,	"UW-MD (8)"			, "WARENGRUPPE" },
	{ 0, A_EDIT,   &E_ART_9,			&pZartwg->WARENGRUPPE,	"Rabattgruppe (9)"	, "WARENGRUPPE" },
	{ 0, A_EDIT,   &E_ART_A,			&pZartwg->WARENGRUPPE,	"2.Saisonart (A)"	, "WARENGRUPPE" },
	{ 0, A_EDIT,   &E_ART_G,			&pZartwg->WARENGRUPPE,	"3.Saisonart (G)"	, "WARENGRUPPE" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- ZARTWG_5AG -------------------------------------------*/
static ZARTWG_5AG* pZartwg_5AG;

static struct PFL_FELD FELDER_ZARTWG_5AG[] =
{
	{ 0, A_EDIT,	&E_ART_5,			&pZartwg_5AG->WARENGRUPPE_5,	"Warengruppe (5)",	"WARENGRUPPE" },
	{ 0, A_EDIT,	&E_ART_A,			&pZartwg_5AG->WARENGRUPPE_A,	"Warengruppe (A)",	"WARENGRUPPE" },
	{ 0, A_EDIT,	&E_ART_G,			&pZartwg_5AG->WARENGRUPPE_G,	"Warengruppe (G)",	"WARENGRUPPE" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- CDISCOUNT ----------------------------------------------*/
static CDISCOUNT *pCDiscount;

static EDIT_MASK E_BASE_QTY = 
{
	ED_LONG, 
	ED_NORMAL,  
	6, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_BASE_QTY
};

static COMBO_MASK C_RAB_ART =
{
	{ "0\n1\n2\n3\n4\n5\n6\n7\n" },
	{ "01234567" },
	0,
	1
};

static COMBO_MASK C_RAB_SPEZ =
{
	{ "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n" },
	{ "00010203040506070809101112" },
	0,
	2
};

static EDIT_MASK E_DISC_GUELTIG_VON = 
{
	ED_LDATE, 
	ED_NORMAL,  
	L_LDATUM, 
	0, 
	NR_MASKLDATE, 
	VAL_DISC_DATEFROM
};

static EDIT_MASK E_DISC_GUELTIG_BIS = 
{
	ED_LDATE, 
	ED_NORMAL,  
	L_LDATUM, 
	0, 
	NR_MASKLDATE, 
	VAL_DISC_DATETO
};

static EDIT_MASK E_DISC_QTY = 
{
	ED_SHORT, 
	ED_NORMAL,  
	8, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_DISC_QTY
};

static EDIT_MASK E_FIXED_PRICE = 
{
	ED_DBL,
	ED_NORMAL,  
	L_CDISCOUNT_FIXEDPRICE + 1, 
	N_CDISCOUNT_FIXEDPRICE, 
	NR_MASKDBLPOS, 
	VAL_DISC_FIXED_PRICE
};

static EDIT_MASK E_DISC_VALUE_PCT = 
{
	ED_DBL,
	ED_NORMAL,  
	L_CDISCOUNT_DISCOUNTVALUEPCT + 1, 
	N_CDISCOUNT_DISCOUNTVALUEPCT, 
	NR_MASKDBLPOS, 
	VAL_DISC_VALUE_PCT
};

static EDIT_MASK E_DISC_SURCHARGE_PCT = 
{
	ED_DBL,
	ED_NORMAL,  
	L_CDISCOUNT_SURCHARGEPCT + 1, 
	N_CDISCOUNT_SURCHARGEPCT, 
	NR_MASKDBLPOS, 
	VAL_DISC_SURCHARGE_PCT
};

static EDIT_MASK E_DISC_REFUND_PCT = 
{
	ED_DBL,
	ED_NORMAL,  
	L_CDISCOUNT_REFUNDPCT + 1, 
	N_CDISCOUNT_REFUNDPCT, 
	NR_MASKDBLPOS, 
	VAL_DISC_REFUND_PCT
};

static EDIT_MASK E_DISC_PHARM_GRP = 
{
	ED_CHAR, 
	ED_LEADZERO,  
	L_CDISCOUNT_PHARMACYGROUPID, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_PHARM_GRP
};

static EDIT_MASK E_DISC_PHARM_GRP_EXCL = 
{
	ED_CHAR, 
	ED_LEADZERO,  
	L_CDISCOUNT_PHARMGRPEXCLUDED, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_PHARM_GRP_EXCL
};

static EDIT_MASK E_DISC_PHARM_GRP_EXCL2 = 
{
	ED_CHAR, 
	ED_LEADZERO,  
	L_CDISCOUNT_PHARMGRPEXCL_2, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_PHARM_GRP_EXCL2
};

static EDIT_MASK E_DISC_PHARM_GRP_EXCL3 = 
{
	ED_CHAR, 
	ED_LEADZERO,  
	L_CDISCOUNT_PHARMGRPEXCL_3, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_PHARM_GRP_EXCL3
};

static EDIT_MASK E_DISC_CUSTOMER = 
{
	ED_LONG, 
	ED_NORMAL,  
	7,
	0,
	NR_MASKNUM, 
	VAL_DISC_CUSTOMER
};

static EDIT_MASK E_DISC_MANUFACTURER = 
{
	ED_LONG, 
	ED_NORMAL,  
	5, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_MANUFACTURER
};

static EDIT_MASK E_DISC_RPG = 
{
	ED_LONG, 
	ED_NORMAL,  
	5, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_RPG
};

static COMBO_MASK C_RAB_PAYM_TARGET =
{
	{ "0\n1\n2\n3\n4\n5\n6\n" },
	{ "0123456" },
	0,
	1
};

static COMBO_MASK C_RAB_MONTHLYDISCOUNT =
{
	{ "0\n1\n2\n" },
	{ "012" },
	0,
	1
};

static EDIT_MASK E_DISC_PROMO_NO =
{
	ED_SHORT,
	ED_NORMAL,
	5,
	0,
	NR_MASKNUM,
	VAL_NO
};

static EDIT_MASK E_DISCOUNTARTICLE =
{
	ED_LONG,
	ED_NORMAL,
	10,
	0,
	NR_MASKNUM,
	VAL_NO
};

static COMBO_MASK C_DISCOUNTCALCFROM =
{
	{ "GEP\nAGP\n" },
	{ "GEPAGP" },
	0,
	3
};

static COMBO_MASK C_DISCOUNTAPPLYTO =
{
	{ "GEP\nAGP\n" },
	{ "GEPAGP" },
	0,
	3
};

static struct PFL_FELD FELDER_CDISCOUNT[] =
{
	{ 0, A_EDIT,   &E_BASE_QTY,			&pCDiscount->BASEQTY,			"Basismenge"							, "BASEQTY" },
	{ 0, A_EDIT,   &E_DISC_GUELTIG_VON,	&pCDiscount->DATEFROM,			"gültig von"							, "DATEFROM" },
	{ 0, A_EDIT,   &E_DISC_GUELTIG_BIS,	&pCDiscount->DATETO,			"gültig bis"							, "DATETO" },
	{ 0, A_COMBO,  &C_RAB_ART,			&pCDiscount->DISCOUNTTYPE,		"Rabatt-Art"							, "DISCOUNTTYPE" },
	{ 0, A_COMBO,  &C_RAB_SPEZ,			&pCDiscount->DISCOUNTSPEC,		"Rabatt-Spezifikation"					, "DISCOUNTSPEC" },
	{ 0, A_BUTTON, NULL,				&pCDiscount->INTERNALDISCOUNT,	"interner Rabatt (nicht Hersteller)"	, "INTERNALDISCOUNT" },
	{ 0, A_EDIT,   &E_DISC_QTY,			&pCDiscount->DISCOUNTQTY,		"Rabatt-Menge"							, "DISCOUNTQTY" },
	{ 0, A_EDIT,   &E_FIXED_PRICE,		&pCDiscount->FIXEDPRICE,		"fester Preis"							, "FIXEDPRICE" },
	{ 0, A_EDIT,   &E_DISC_VALUE_PCT,	&pCDiscount->DISCOUNTVALUEPCT,	"Rabatt-Prozent vom Wert"				, "DISCOUNTVALUEPCT" },
	{ 0, A_EDIT,   &E_DISC_SURCHARGE_PCT,&pCDiscount->SURCHARGEPCT,		"Logistik-Aufschlag %"					, "SURCHARGEPCT" },
	{ 0, A_EDIT,   &E_DISC_REFUND_PCT,	&pCDiscount->REFUNDPCT,			"Hersteller-Erstattung %"				, "REFUNDPCT" },
	{ 0, A_EDIT,   &E_DISC_PHARM_GRP,	&pCDiscount->PHARMACYGROUPID,	"Einkaufsgruppe"						, "PHARMACYGROUPID" },
	{ 0, A_EDIT,   &E_DISC_PHARM_GRP_EXCL,&pCDiscount->PHARMGRPEXCLUDED,"ausgeschl. EK-Gruppe 1"				, "PHARMGRPEXCLUDED" },
	{ 0, A_EDIT,   &E_DISC_PHARM_GRP_EXCL2,&pCDiscount->PHARMGRPEXCL_2,	"ausgeschl. EK-Gruppe 2"				, "PHARMGRPEXCL_2" },
	{ 0, A_EDIT,   &E_DISC_PHARM_GRP_EXCL3,&pCDiscount->PHARMGRPEXCL_3,	"ausgeschl. EK-Gruppe 3"				, "PHARMGRPEXCL_3" },
	{ 0, A_EDIT,   &E_DISC_CUSTOMER,	&pCDiscount->CUSTOMERNO,		"Kunde / IDF"							, "CUSTOMERNO" },
	{ 0, A_EDIT,   &E_DISC_MANUFACTURER,&pCDiscount->MANUFACTURERNO,	"Herstellernr."							, "MANUFACTURERNO"  },
	{ 0, A_EDIT,   &E_DISC_RPG,			&pCDiscount->DISCOUNTGRPNO,		"RPG"									, "DISCOUNTGRPNO"  },
	{ 0, A_COMBO,  &C_RAB_PAYM_TARGET,	&pCDiscount->PAYMENTTARGETNO,	"Zahlungszielnr."						, "PAYMENTTARGETNO"  },
	{ 0, A_COMBO,  &C_RAB_MONTHLYDISCOUNT,&pCDiscount->MONTHLYDISCOUNT,	"Monatsrabatt"							, "MONTHLYDISCOUNT" },
	{ 0, A_EDIT,   &E_DISC_PROMO_NO,	&pCDiscount->PROMOTION_NO,		"Promotionen"							, "PROMOTION_NO"  },
	{ 0, A_EDIT,   &E_DISCOUNTARTICLE,	&pCDiscount->DISCOUNTARTICLE,	"Naturalrabatt-ArtNr"				    , "DISCOUNTARTICLE"},
	{ 0, A_COMBO,  &C_DISCOUNTCALCFROM,	&pCDiscount->DISCOUNTCALCFROM,	"Rabatt angewendet auf:"				, "DISCOUNTCALCFROM"},
	{ 0, A_COMBO,  &C_DISCOUNTAPPLYTO,	&pCDiscount->DISCOUNTAPPLYTO,	"Rabatt berechnet von:"					, "DISCOUNTAPPLYTO"},
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- CDISCGRPMEM ----------------------------------------------*/
static CDISCGRPMEM *pCDiscGrpMem;

static struct PFL_FELD FELDER_CDISCGRPMEM[] =
{
	{ 0, A_EDIT,   &E_DISC_RPG,			&pCDiscGrpMem->DISCOUNTGRPNO,	"Gruppennummer"							, "DISCOUNTGRPNO" },
	{ 0, A_EDIT,   &E_DISC_MANUFACTURER,&pCDiscGrpMem->MANUFACTURERNO,	"Herstellernr."							, "MANUFACTURERNO"  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- CARTCOMPACK ----------------------------------------------*/
static CARTCOMPACK *pCArtComPack;

static struct PFL_FELD FELDER_CARTCOMPACK[] =
{
	{ 0, A_EDIT,   &E_ART_NR_ORIG,		&pCArtComPack->ARTICLE_NO_PACK,	"ArtNr Display"	, "ARTICLE_NO_PACK" },
	{ 0, A_EDIT,   &E_BASE_QTY,			&pCArtComPack->QUANTITY,		"Menge"			, "QUANTITY"  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};




/*-------------------------- CDISCOUNT STOP ----------------------------------------------*/
/*
static CDISCOUNT *pCDiscountStop;

static EDIT_MASK E_BASE_QTY = 
{
	ED_LONG, 
	ED_NORMAL,  
	6, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_BASE_QTY
};

static EDIT_MASK E_DISC_PHARM_GRP = 
{
	ED_CHAR, 
	ED_LEADZERO,  
	L_CDISCOUNT_PHARMACYGROUPID, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_PHARM_GRP
};
*/

static EDIT_MASK E_DISC_STOP_HNR = 
{
	ED_LONG, 
	ED_NORMAL,  
	5, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_STOP_HNR
};

static EDIT_MASK E_DISC_ARTCATNO = 
{
	ED_LONG, 
	ED_NORMAL,  
	5, 
	0, 
	NR_MASKNUM, 
	VAL_DISC_ARTCAT
};

static struct PFL_FELD FELDER_CDISCOUNT_STOP[] = //Achtung: in zputil werden aktuell nur 10 Where- Kriterien unterstützt!
{
	{ 0, A_EDIT,   &E_BASE_QTY,			&pCDiscount->BASEQTY,			"Basismenge"							, "BASEQTY" },
	{ 0, A_EDIT,   &E_DISC_PHARM_GRP,	&pCDiscount->PHARMACYGROUPID,	"Einkaufsgruppe"						, "PHARMACYGROUPID" },
	{ 0, A_EDIT,   &E_DISC_GUELTIG_BIS,	&pCDiscount->DATETO,			"gültig bis"							, "DATETO" },
	{ 0, A_EDIT,   &E_DISC_CUSTOMER,	&pCDiscount->CUSTOMERNO,		"Kunde / IDF"							, "CUSTOMERNO" },
	{ 0, A_EDIT,   &E_DISC_STOP_HNR,	&pCDiscount->MANUFACTURERNO,	"Artikel mit dieser HNR im Artikelstamm", "HERSTELLER_NR" },
	{ 0, A_COMBO,  &C_RAB_SPEZ,			&pCDiscount->DISCOUNTSPEC,		"Rabatt-Spezifikation"					, "DISCOUNTSPEC" },
	{ 0, A_EDIT,   &E_DISC_MANUFACTURER,&pCDiscount->MANUFACTURERNO,	"Herstellernr."							, "MANUFACTURERNO"  },
	{ 0, A_EDIT,   &E_DISC_RPG,			&pCDiscount->DISCOUNTGRPNO,		"RPG"									, "DISCOUNTGRPNO"  },
	{ 0, A_EDIT,   &E_DISC_ARTCATNO,	&pCDiscount->ARTCATEGORYNO,		"Artikelgruppe"							, "ARTCATEGORYNO"  },
	{ 0, A_COMBO,  &C_RAB_MONTHLYDISCOUNT,&pCDiscount->MONTHLYDISCOUNT,	"Monatsrabatt"							, "MONTHLYDISCOUNT" },
	{ 0, A_EDIT,   &E_DISC_VALUE_PCT,	&pCDiscount->DISCOUNTVALUEPCT,	"Rabatt-Prozent vom Wert"				, "DISCOUNTVALUEPCT" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};



/*-------------------------- CGIBATCHENTRY ----------------------------------------------*/
static CGIBATCHENTRY *pCGiBatchEntry;

static EDIT_MASK E_BATCHENTRY_COMPANYCODE = 
{
	ED_SHORT, 
	ED_NORMAL,  
	3, 
	0, 
	NR_MASKNUM, 
	VAL_BATCHENTRY_COMPANYCODE
};

static EDIT_MASK E_BATCHENTRY_DATEFROM = 
{
	ED_LDATE, 
	ED_NORMAL,  
	L_LDATUM, 
	0, 
	NR_MASKLDATE, 
	VAL_BATCHENTRY_DATE
};

static EDIT_MASK E_BATCHENTRY_DATETO = 
{
	ED_LDATE, 
	ED_NORMAL,  
	L_LDATUM, 
	0, 
	NR_MASKLDATE, 
	VAL_BATCHENTRY_DATE
};

static struct PFL_FELD FELDER_BATCHENTRY[] =
{
	{ 0, A_EDIT,   &E_BATCHENTRY_COMPANYCODE,	&pCGiBatchEntry->COMPANY_CODE,		"Firmencode"							, "COMPANY_CODE" },
	{ 0, A_EDIT,   &E_BATCHENTRY_DATEFROM,		&pCGiBatchEntry->DATEFROM,			"gültig von"							, "DATEFROM" },
	{ 0, A_EDIT,   &E_BATCHENTRY_DATETO,		&pCGiBatchEntry->DATETO,			"gültig bis"							, "DATETO" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING  },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- CARTICLEEXT ----------------------------------------------*/
static CARTICLEEXT *pArtExt;

static EDIT_MASK E_ALCOHOLIC_STRENGTH = 
{
	ED_DBL, 
	ED_NORMAL,  
	L_ALCOHOLIC_STRENGTH + 1, 
	N_ALCOHOLIC_STRENGTH, 
	NR_MASKDBLPOS, 
	VAL_ART_ALCOHOLIC_STRENGTH
};

static EDIT_MASK E_VINTAGE = 
{
	ED_LONG, 
	ED_CLINPUT,  
	L_VINTAGE, 
	0, 
	NR_MASKNUM, 
	VAL_NO
};

static struct PFL_FELD FELDER_CARTEXT[] = 
{
	{ 0, A_EDIT, &E_ALCOHOLIC_STRENGTH,	&pArtExt->ALCOHOLIC_STRENGTH, "Alkoholgehalt"	,"ALCOHOLIC_STRENGTH" },
	{ 0, A_EDIT, &E_VINTAGE,			&pArtExt->VINTAGE,		"Jahrgang"		,		"VINTAGE" },
	{ 0, A_BUTTON, NULL,				&pArtExt->HIGH_THERAPEUTIC_VALUE,	"hoher Therapiewert"	, "HIGH_THERAPEUTIC_VALUE" },
	{ 0, A_BUTTON, NULL,				&pArtExt->SHORTEXPIRYFLAG,		"nur mit kurzem Verfall lieferbar"	,  "SHORTEXPIRYFLAG" },
	//{ 0, A_BUTTON, NULL,				&pArtExt->ANIMALDRUG_PROOFOBLIGATION_FLAG,	"AMG §59c (Stoffe TierAM)"	, "ANIMALDRUG_PROOFOBLIGATION_FLAG" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- CIBT ----------------------------------------------*/
static CIBT *pCibt;

static struct PFL_FELD FELDER_CIBT[] =
{
	{ 0, A_BUTTON, NULL,				&pCibt->ISFIXEDREGIONAL, "festver. Regionalhausartikel"	,"ISFIXEDREGIONAL" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- EAN -----------------------------------------------*/
static EAN *pEAN;

static EDIT_MASK E_EAN_NR =
{
	ED_CHAR,
	ED_NORMAL,
	L_EAN_NR,
	0,
	NR_MASKNUM,
	VAL_EAN
};

static struct PFL_FELD FELDER_EAN[] =
{
	{ 0, A_EDIT, &E_EAN_NR,				&pEAN->EAN_NR,			"EAN-Nr."			,  "EAN_NR" },
	{ 0, A_BUTTON, NULL,				NULL,					"EAN-Nr. löschen"	,  "EAN_NR" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*-------------------------- Nachlieferung -----------------------------------------------*/

static CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG *pSubseqConfig;


static COMBO_MASK E_BRANCHNO =
{
// 	{ "0\n5\n6\n8\n9\n21\n31\n33\n40\n44\n46\n51\n52\n53\n54\n56\n57\n58\n59\n70\n78\n81\n82\n" },
// 	{ "0005060809213133404446515253545657585970788182" },
	{ "0\n5\n6\n8\n" },
	{ "00050608" },
	0,
	2
};


static COMBO_MASK E_NACHL_NR =
{
	{ "0\n1\n8\n9\n" },
	{ "0189" },
	0,
	1
};

static EDIT_MASK E_USER =
{
	ED_CHAR,
	ED_SHORT,
	L_NACHL_NR,
	0,
	NR_MASKNUM,
	VAL_NACHL
};


static struct PFL_FELD FELDER_NACHLIEFERUNG[] =
{
	{ 0, A_COMBO, &E_BRANCHNO,			&pSubseqConfig->LASTCHANGEUSER,			"Filialnr."			,  "BRANCHNO" },
	{ 0, A_COMBO,  &E_NACHL_NR,			&pSubseqConfig->SUBSEQUENTDELIVERY,			"Nachlieferung"			,  "SUBSEQUENTDELIVERY" },
	{ 0, A_EDIT, &E_NACHL_NR,			&pSubseqConfig->LASTCHANGEUSER,			"User"			,  "LASTCHANGEUSER" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*----------------------------- Bliesort -------------------------------------------------*/

static BLIESORT* pBliesort;

static EDIT_MASK E_BESLA_NR =
{
	ED_LONG,
	ED_NORMAL,
	10,
	0,
	NR_MASKNUM,
	VAL_BESLA_NO
};

static struct PFL_FELD FELDER_BLIESORT[] =
{
	{ 0, A_EDIT,	&E_BESLA_NR,		&pBliesort->BESLA_NR,	"Besla-Nummer."		,  "BESLA_NR" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*----------------------------- Baselist -------------------------------------------------*/

static CBASELISTARTICLES *pBaselist;

static EDIT_MASK E_BASELIST_ID =
{
	ED_CHAR,
	ED_UPPER,
	L_CBASELISTARTICLES_BASELIST_ID,
	0,
	NR_MASKCHAR,
	VAL_BASELIST_ID
};

static struct PFL_FELD FELDER_BASELIST[] =
{
	{ 0, A_EDIT,	&E_BASELIST_ID,		&pBaselist->BASELIST_ID,"Baselist ID (A to Z)"		,"BASELIST_ID" },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*----------------------------- Cartmedactor -------------------------------------------------*/

static CARTMEDACTOR* pCartmedactor;

static EDIT_MASK E_CARTMEDACTOR_ID =
{
	ED_CHAR,
	ED_UPPER,
	L_CARTMEDACTOR_MEDICALACTOR_ID,
	0,
	NR_MASKCHAR,
	VAL_CARTMEDACTOR_ID
};

static COMBO_MASK C_CARTMEDACTOR_TYPE =
{
	{ "0\n1\n2\n3\n" },
	{ "0123" },
	0,
	1
};

static struct PFL_FELD FELDER_ARTMEDACTOR[] =
{
	{ 0, A_EDIT, &E_CARTMEDACTOR_ID,	&pCartmedactor->MEDICALACTOR_ID,	"Medical Actor id ",	"MEDICALACTOR_ID"},
	{ 0, A_COMBO, &C_CARTMEDACTOR_TYPE, &pCartmedactor->MEDICALACTOR_TYPE,	"Medical Actor Type ",	"MEDICALACTOR_TYPE"},
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*----------------------------- Cmedicalactor -------------------------------------------------*/

static CMEDICALACTOR* pCmedicalactor;

static EDIT_MASK E_CMEDICALACTOR_ID =
{
	ED_CHAR,
	ED_UPPER,
	L_CMEDICALACTOR_MEDICALACTOR_ID,
	0,
	NR_MASKCHAR,
	VAL_CMEDICALACTOR_ID
};

static COMBO_MASK C_CMEDICALACTOR_TYPE =
{
	{ "0\n1\n2\n3\n" },
	{ "0123" },
	0,
	1
};
static COMBO_MASK C_CMEDICALACTOR_ACTIVE =
{
	{ "0\n1\n" },
	{ "01" },
	0,
	1
};

static EDIT_MASK E_CMEDICALACTOR_MATCHCODE =
{
	ED_CHAR,
	ED_UPPER,
	L_CMEDICALACTOR_MATCHCODE,
	0,
	NR_MASKCHAR,
	VAL_CMEDICALACTOR_MATCHCODE
};

static EDIT_MASK E_CMEDICALACTOR_NAME =
{
	ED_CHAR,
	ED_UPPER,
	L_CMEDICALACTOR_NAME,
	0,
	NR_MASKCHAR,
	VAL_CMEDICALACTOR_NAME
};

static EDIT_MASK E_CMEDICALACTOR_STREET_NR =
{
	ED_CHAR,
	ED_UPPER,
	L_CMEDICALACTOR_STREET_NR,
	0,
	NR_MASKCHAR,
	VAL_CMEDICALACTOR_STREET_NR
};

static EDIT_MASK E_CMEDICALACTOR_STREET_NAME =
{
	ED_CHAR,
	ED_UPPER,
	L_CMEDICALACTOR_STREET_NAME,
	0,
	NR_MASKCHAR,
	VAL_CMEDICALACTOR_STREET_NAME
};

static EDIT_MASK E_CMEDICALACTOR_CITY_NAME =
{
	ED_CHAR,
	ED_UPPER,
	L_CMEDICALACTOR_CITY_NAME,
	0,
	NR_MASKCHAR,
	VAL_CMEDICALACTOR_CITY_NAME
};

static EDIT_MASK E_CMEDICALACTOR_COUNTRY_CODE =
{
	ED_CHAR,
	ED_UPPER,
	L_CMEDICALACTOR_COUNTRY_CODE,
	0,
	NR_MASKCHAR,
	VAL_CMEDICALACTOR_COUNTRY_CODE
};

static EDIT_MASK E_CMEDICALACTOR_EMAIL =
{
	ED_CHAR,
	ED_NORMAL,
	L_CMEDICALACTOR_EMAIL,
	0,
	NR_MASKCHAR,
	VAL_CMEDICALACTOR_EMAIL
};

static struct PFL_FELD FELDER_MEDICALACTOR[] =
{
	{ 0, A_EDIT, &E_CMEDICALACTOR_ID,			&pCmedicalactor->MEDICALACTOR_ID,	"Medical Actor ID ",			"MEDICALACTOR_ID"},
	{ 0, A_COMBO, &C_CMEDICALACTOR_TYPE,		&pCmedicalactor->MEDICALACTOR_TYPE, "Medical Actor Type ",			"MEDICALACTOR_TYPE"},
	{ 0, A_COMBO, &C_CMEDICALACTOR_ACTIVE,		&pCmedicalactor->ACTIVE,			"Medical Actor ACTIVE ",		"ACTIVE"},
	{ 0, A_EDIT, &E_CMEDICALACTOR_MATCHCODE,	&pCmedicalactor->MATCHCODE,			"Medical Actor MATCHCODE ",		"MATCHCODE"},
	{ 0, A_EDIT, &E_CMEDICALACTOR_NAME,			&pCmedicalactor->NAME,				"Medical Actor NAME ",			"NAME"},
	{ 0, A_EDIT, &E_CMEDICALACTOR_STREET_NR,	&pCmedicalactor->STREET_NR,			"Medical Actor STREET_NR ",		"STREET_NR"},
	{ 0, A_EDIT, &E_CMEDICALACTOR_STREET_NAME,	&pCmedicalactor->STREET_NAME,		"Medical Actor STREET_NAME ",	"STREET_NAME"},
	{ 0, A_EDIT, &E_CMEDICALACTOR_CITY_NAME,	&pCmedicalactor->CITY_NAME,			"Medical Actor CITY_NAME ",		"CITY_NAME"},
	{ 0, A_EDIT, &E_CMEDICALACTOR_COUNTRY_CODE,	&pCmedicalactor->COUNTRY_CODE,		"Medical Actor COUNTRY_CODE ",	"COUNTRY_CODE"},
	{ 0, A_EDIT, &E_CMEDICALACTOR_EMAIL,		&pCmedicalactor->EMAIL,				"Medical Actor EMAIL ",			"EMAIL"},
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING },
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*----------------------------- Dummy -------------------------------------------------*/
static struct PFL_FELD DUMMY[] =
{
	{ 0, A_BUTTON, NULL,				NULL,					EMPTY_STRING		,  EMPTY_STRING }
};

/*------------------------------------------------------------------------*/
void CPflFelder::InitCountrySpecificValidations()
{
	int i;

	// country specific validation currently only for ZARTIKEL.PRODUKTART
	if (m_UpdMode == CUpdateFromExcelView::UPD_ZARTIKEL)
	{
		for (i = 0; i < ANZ_MAX_FELDER; i++)
		{
			if (strcmp(FELDER[i].cUpdColumn, "PRODUKTART") == 0)
			{
				if (IsCountry("D"))
				{
					FELDER[i].pRef1 = &C_PRODUKTART_DE;
				}
				else if (IsCountry("CH"))
				{
					FELDER[i].pRef1 = &C_PRODUKTART_CH;
				}
			}
		}
	}
}

/*------------------------------------------------------------------------*/
void CPflFelder::InitTexte( )
{
	int i;

	if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTIKEL )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_ZART[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTWG )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_ZARTWG[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CIMEXBLOCK )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_CIMEXBLOCK[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTPREIS )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_ZPREIS[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CDISCOUNT_FLEXIBLE )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
		{
			if (( !(IsCountry("CH")) ) // DISCOUNTCALCFROM and DISCOUNTAPPLYTO only in CH
				 &&	(( strcmp(FELDER_CDISCOUNT[i].cUpdColumn, "DISCOUNTCALCFROM") == 0 )
				  || ( strcmp(FELDER_CDISCOUNT[i].cUpdColumn, "DISCOUNTAPPLYTO")  == 0 )))
			{
				FELDER[i] = DUMMY[0];
			}
			else
			{
			FELDER[i] = FELDER_CDISCOUNT[i];
	}
		}
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CDISCOUNT_STOP )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_CDISCOUNT_STOP[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ARTVE )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_ARTVE[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CDISCGRPMEM )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_CDISCGRPMEM[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTFRANCE )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_ZARTFRANCE[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTSWITZERLAND )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_ZARTSWITZERLAND[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTSERBIA )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_ZARTSERBIA[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTAUSTRIA )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_ZARTAUSTRIA[i];
	}	
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CARTICLECODES )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_CARTICLECODES[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CARTCOMPACK )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_CARTCOMPACK[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CGIBATCHENTRY )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_BATCHENTRY[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CARTICLEEXT )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_CARTEXT[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ZCHARGENRR )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_ZCHARGENRR[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CIBT )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_CIBT[i];
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_EAN )
	{
		for ( i = 0; i < ANZ_MAX_FELDER; i++ )
			FELDER[i] = FELDER_EAN[i];
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_KONTMENGENST)
	{
		CString sql = "select to_char(Count(*)) from filiale where filialnr <> 0";
		char TempBuf[256];
		long lStatus = SqlRead(sql, TempBuf, NULL);
		static CString csResult1, csResult2;
		csResult1.Empty();
		csResult2.Empty();

		bool bOK = true;
		if (lStatus == 0)
		{
			int iNbrRecs = atoi(TempBuf);

			for (int iIdx = 0; iIdx < iNbrRecs; iIdx++)
			{
				sql.Format("Select skip %i first 1 to_char(Filialnr) From Filiale where filialnr <> 0", iIdx);
				lStatus = SqlRead(sql, TempBuf, NULL);

				if (lStatus == 0)
				{
					CString csTemp;
					csTemp.Format("%i\n", atoi(TempBuf));
					csResult1 += csTemp;
					csTemp.Format("%2.2i", atoi(TempBuf));
					csResult2 += csTemp;
				}
				else
				{
					bOK = false;
					break;
				}
			}

			if (bOK)
			{
				E_BRANCHNO.cTexte = (char*)csResult1.GetString();
				E_BRANCHNO.cWerte = (char*)csResult2.GetString();
			}
		}

		for (i = 0; i < ANZ_MAX_FELDER; i++)
			FELDER[i] = FELDER_NACHLIEFERUNG[i];
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_ZARTWG_5AG)
	{
		for (i = 0; i < ANZ_MAX_FELDER; i++)
			FELDER[i] = FELDER_ZARTWG_5AG[i];
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_BLIESORT)
	{
		for (i = 0; i < ANZ_MAX_FELDER; i++)
			FELDER[i] = FELDER_BLIESORT[i];
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_BASELISTARTICLES)
	{
		for (i = 0; i < ANZ_MAX_FELDER; i++)
			FELDER[i] = FELDER_BASELIST[i];
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_ARTMEDACTOR)
	{
		for (i = 0; i < ANZ_MAX_FELDER; i++)
			FELDER[i] = FELDER_ARTMEDACTOR[i];
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_MEDICALACTOR)
	{
		for (i = 0; i < ANZ_MAX_FELDER; i++)
			FELDER[i] = FELDER_MEDICALACTOR[i];
	}
	// some field validations are country specific
	// --> do necessary initialization here
	InitCountrySpecificValidations();
}

/*------------------------------------------------------------------------*/
void CPflFelder::AusgabeTexte( )
{
	int i;
	int k;

	k = 0;
	for ( i = m_Pos_First_Feld; i <= m_Pos_Last_Feld; i++ )
	{
		m_dlg.SetCntrlText( i, FELDER[k++].cName );
	}

	// Datum gültig ab muss für ZArtPreis-Updates immer angegeben werden!
	if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTPREIS )
	{
		m_F_00.SetCheck(BST_CHECKED);
		m_F_00.EnableWindow(false);
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_CDISCOUNT_FLEXIBLE || 
			 m_UpdMode == CUpdateFromExcelView::UPD_CGIBATCHENTRY	)
	{
		m_F_00.SetCheck(BST_CHECKED);
		m_F_00.EnableWindow(false);
	
		m_F_01.SetCheck(BST_CHECKED);
		m_F_01.EnableWindow(false);
	
		m_F_02.SetCheck(BST_CHECKED);
		m_F_02.EnableWindow(false);
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_CDISCGRPMEM)
	{
		m_F_00.SetCheck(BST_CHECKED);
		m_F_00.EnableWindow(false);
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_CARTICLECODES)
	{
		m_F_00.SetCheck(BST_CHECKED);
		m_F_00.EnableWindow(false);
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_CARTCOMPACK)
	{
		m_F_00.SetCheck(BST_CHECKED);
		m_F_00.EnableWindow(false);
	}	
	else if (m_UpdMode == CUpdateFromExcelView::UPD_ZCHARGENRR)
	{
		m_F_00.SetCheck(BST_CHECKED);
		m_F_00.EnableWindow(false);
	}	
	else if (m_UpdMode == CUpdateFromExcelView::UPD_CIMEXBLOCK)
	{
		m_F_00.SetCheck(BST_CHECKED);
		m_F_00.EnableWindow(false);

		m_F_01.SetCheck(BST_CHECKED);
		m_F_01.EnableWindow(false);
	
		m_F_02.SetCheck(BST_CHECKED);
		m_F_02.EnableWindow(false);
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_ZARTIKEL)
	{
		// automatische Aktivierung des Feldes 'MWE-Datum' in CPflFelder::GetFeldInfo()
		m_F_50.EnableWindow(false);
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_KONTMENGENST)
	{
		m_F_00.SetCheck(BST_CHECKED); // branchno
		m_F_00.EnableWindow(false);

		m_F_02.SetCheck(BST_CHECKED); // lastchangeuser
		m_F_02.EnableWindow(false);
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_ZARTWG_5AG)
	{
		m_F_00.SetCheck(BST_CHECKED); // Warengruppe
		m_F_00.EnableWindow(false);

		m_F_01.SetCheck(BST_CHECKED); // Warengruppe
		m_F_01.EnableWindow(false);

		m_F_02.SetCheck(BST_CHECKED); // Warengruppe
		m_F_02.EnableWindow(false);
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_ARTMEDACTOR)
	{
		m_F_00.SetCheck(BST_CHECKED);
		m_F_00.EnableWindow(false);
		m_F_01.SetCheck(BST_CHECKED);
		m_F_01.EnableWindow(false);
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_MEDICALACTOR)
	{
		m_F_00.SetCheck(BST_CHECKED);
		m_F_00.EnableWindow(false);
		m_F_01.SetCheck(BST_CHECKED);
		m_F_01.EnableWindow(false);
		m_F_02.SetCheck(BST_CHECKED);
		m_F_02.EnableWindow(false);
		m_F_03.SetCheck(BST_CHECKED);
		m_F_03.EnableWindow(false);
		m_F_04.SetCheck(BST_CHECKED);
		m_F_04.EnableWindow(false);
	}
}

/*------------------------------------------------------------------------*/
int CPflFelder::TestAnzahl( )
{
	int i;
	int k;
	int anz;

	anz = 0;

	k = 0;
	for ( i = m_Pos_First_Feld; i <= m_Pos_Last_Feld; i++ )
	{
		if ( FELDER[k++].iAktiv ) 
			anz++;
	}
	return anz;
}


/*------------------------------------------------------------------------*/
int CPflFelder::GetFeldInfo( struct PFL_FELD *F[] )
{
	int anz;
	int i;
	int k;

	anz = TestAnzahl( );
	if ( anz > ANZ_FELDER_UPD )
	{
		MsgBoxOK( "Bitte maximal 10 Felder anklicken" );
		return -1;
	}
	
	if (m_UpdMode == CUpdateFromExcelView::UPD_EAN)
	{
		if ( FELDER[0].iAktiv && FELDER[1].iAktiv )
		{
			MsgBoxOK("Die Felder 'EAN-Nr.' und 'EAN-Nr. löschen' können nicht gleichzeitig ausgewählt werden!");
			return 0;
		}
	}
	else if (m_UpdMode == CUpdateFromExcelView::UPD_KONTMENGENST)
	{
		if (anz < 3)
		{
			MsgBoxOK("Das Feld <Nachlieferung> ist nicht ausgewählt");
			return 0;
		}
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTIKEL )
	{
		if ( FELDER[46].iAktiv || FELDER[47].iAktiv || FELDER[48].iAktiv || FELDER[49].iAktiv )
		{	// aktiviere Feld 'MWE-Datum', wenn Länge, Breite, Höhe oder Gewicht gesetzt sind
			// MWE-Datum (zartikel.datum_mwe) soll dann automatisch auf das Tagesdatum gesetzt werden,
			// --> wird in CUpdateFromExcelView::OnBtZArtikel() gemacht
			// Hintergrund: Maße und Gewichte werden nur zum Warehouse übertragen, wenn datum_mwe gesetzt ist

			FELDER[50].iAktiv = 1;
		}
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTPREIS )
	{
		if ( anz == 1 )
		{
			MsgBoxOK( "Es wurden außer <datumgueltigab> keine Felder ausgewählt" );
			return 0;
		}
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CARTICLECODES )
	{
		if ( anz == 1 )
		{
			MsgBoxOK( "Es wurden außer <Code-Typ> keine Felder ausgewählt" );
			return 0;
		}
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_ZCHARGENRR )
	{
		if ( anz == 1 )
		{
			MsgBoxOK( "Es wurden außer <Charge> keine Felder ausgewählt" );
			return 0;
		}
	}
	else if ( m_UpdMode == CUpdateFromExcelView::UPD_CDISCOUNT_FLEXIBLE )
	{
		if ( anz == 3 )
		{
			MsgBoxOK( "Es wurden außer <gueltigvon>, <gueltigbis> und <basismenge> keine Felder ausgewählt" );
			return 0;
		}

		if ( FELDER[15].iAktiv && (FELDER[12].iAktiv || FELDER[11].iAktiv || FELDER[13].iAktiv || FELDER[14].iAktiv) )
		{
			MsgBoxOK( "Eingabe von Einkaufsgruppen nicht zulässig, wenn IDF angegeben wird" );
			return 0;
		}
	}
	else
	{
		if ( anz == 0 && m_UpdMode != CUpdateFromExcelView::UPD_CDISCOUNT_STOP )
		{
			MsgBoxOK( "Es wurden keine Felder ausgewählt" );
			return 0;
		}
	}

	anz = 0; 
	k = 0;
	for ( i = m_Pos_First_Feld; i <= m_Pos_Last_Feld; i++ )
	{
		if ( FELDER[k].iAktiv ) 
			F[anz++] = &FELDER[k]; 
		k++;
	}
	return anz;
}


/*------------------------------------------------------------------------*/
void CPflFelder::OnPaint() 
{
	CPaintDC dc(this); 

	AusgabeTexte( );
}

/*------------------------------------------------------------------------*/
void CPflFelder::OnOK() 
{
	
	m_dlg.DataExchangeToBuffer();

	
	if ( m_UpdMode == CUpdateFromExcelView::UPD_ZARTWG )
	{
		if ( TestAnzahl( ) > 1 )
		{
			MsgBoxOK( "Bitte nur 1 Feld auswählen für ZArtWg" );
			return;
		}
	}
	else
	{
		if ( TestAnzahl( ) > ANZ_FELDER_UPD )
		{
			MsgBoxOK( "Bitte Maximal 10 Felder anklicken" );
			return;
		}
	}

	CDialogMultiLang::OnOK();
}


/*------------------------------------------------------------------------*/
void CPflFelder::ShowCheckboxes() 
{
	if ( strcmp( FELDER[0].cName, EMPTY_STRING) == 0 )
		m_F_00.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[1].cName, EMPTY_STRING) == 0 )
		m_F_01.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[2].cName, EMPTY_STRING) == 0 )
		m_F_02.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[3].cName, EMPTY_STRING) == 0 )
		m_F_03.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[4].cName, EMPTY_STRING) == 0 )
		m_F_04.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[5].cName, EMPTY_STRING) == 0 )
		m_F_05.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[6].cName, EMPTY_STRING) == 0 )
		m_F_06.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[7].cName, EMPTY_STRING) == 0 )
		m_F_07.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[8].cName, EMPTY_STRING) == 0 )
		m_F_08.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[9].cName, EMPTY_STRING) == 0 )
		m_F_09.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[10].cName, EMPTY_STRING) == 0 )
		m_F_10.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[11].cName, EMPTY_STRING) == 0 )
		m_F_11.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[12].cName, EMPTY_STRING) == 0 )
		m_F_12.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[13].cName, EMPTY_STRING) == 0 )
		m_F_13.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[14].cName, EMPTY_STRING) == 0 )
		m_F_14.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[15].cName, EMPTY_STRING) == 0 )
		m_F_15.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[16].cName, EMPTY_STRING) == 0 )
		m_F_16.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[17].cName, EMPTY_STRING) == 0 )
		m_F_17.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[18].cName, EMPTY_STRING) == 0 )
		m_F_18.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[19].cName, EMPTY_STRING) == 0 )
		m_F_19.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[20].cName, EMPTY_STRING) == 0 )
		m_F_20.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[21].cName, EMPTY_STRING) == 0 )
		m_F_21.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[22].cName, EMPTY_STRING) == 0 )
		m_F_22.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[23].cName, EMPTY_STRING) == 0 )
		m_F_23.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[24].cName, EMPTY_STRING) == 0 )
		m_F_24.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[25].cName, EMPTY_STRING) == 0 )
		m_F_25.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[26].cName, EMPTY_STRING) == 0 )
		m_F_26.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[27].cName, EMPTY_STRING) == 0 )
		m_F_27.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[28].cName, EMPTY_STRING) == 0 )
		m_F_28.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[29].cName, EMPTY_STRING) == 0 )
		m_F_29.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[30].cName, EMPTY_STRING) == 0 )
		m_F_30.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[31].cName, EMPTY_STRING) == 0 )
		m_F_31.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[32].cName, EMPTY_STRING) == 0 )
		m_F_32.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[33].cName, EMPTY_STRING) == 0 )
		m_F_33.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[34].cName, EMPTY_STRING) == 0 )
		m_F_34.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[35].cName, EMPTY_STRING) == 0 )
		m_F_35.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[36].cName, EMPTY_STRING) == 0 )
		m_F_36.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[37].cName, EMPTY_STRING) == 0 )
		m_F_37.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[38].cName, EMPTY_STRING) == 0 )
		m_F_38.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[39].cName, EMPTY_STRING) == 0 )
		m_F_39.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[40].cName, EMPTY_STRING) == 0 )
		m_F_40.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[41].cName, EMPTY_STRING) == 0 )
		m_F_41.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[42].cName, EMPTY_STRING) == 0 )
		m_F_42.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[43].cName, EMPTY_STRING) == 0 )
		m_F_43.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[44].cName, EMPTY_STRING) == 0 )
		m_F_44.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[45].cName, EMPTY_STRING) == 0 )
		m_F_45.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[46].cName, EMPTY_STRING) == 0 )
		m_F_46.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[47].cName, EMPTY_STRING) == 0 )
		m_F_47.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[48].cName, EMPTY_STRING) == 0 )
		m_F_48.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[49].cName, EMPTY_STRING) == 0 )
		m_F_49.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[50].cName, EMPTY_STRING) == 0 )
		m_F_50.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[51].cName, EMPTY_STRING) == 0 )
		m_F_51.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[52].cName, EMPTY_STRING) == 0 )
		m_F_52.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[53].cName, EMPTY_STRING) == 0 )
		m_F_53.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[54].cName, EMPTY_STRING) == 0 )
		m_F_54.ShowWindow( SW_HIDE );

	if ( strcmp( FELDER[55].cName, EMPTY_STRING) == 0 )
		m_F_55.ShowWindow(SW_HIDE);

	if ( strcmp( FELDER[56].cName, EMPTY_STRING) == 0 )
		m_F_56.ShowWindow(SW_HIDE);

	if ( strcmp( FELDER[57].cName, EMPTY_STRING) == 0 )
		m_F_57.ShowWindow(SW_HIDE);

	if ( strcmp( FELDER[58].cName, EMPTY_STRING) == 0 )
		m_F_58.ShowWindow(SW_HIDE);

	if ( strcmp( FELDER[59].cName, EMPTY_STRING) == 0 )
		m_F_59.ShowWindow(SW_HIDE);

	if ( strcmp( FELDER[60].cName, EMPTY_STRING) == 0 )
		m_F_60.ShowWindow(SW_HIDE);

	if ( strcmp( FELDER[61].cName, EMPTY_STRING) == 0 )
		m_F_61.ShowWindow(SW_HIDE);

	if ( strcmp( FELDER[62].cName, EMPTY_STRING) == 0 )
		m_F_62.ShowWindow(SW_HIDE);

	if ( strcmp( FELDER[63].cName, EMPTY_STRING) == 0 )
		m_F_63.ShowWindow(SW_HIDE);

	if ( strcmp( FELDER[64].cName, EMPTY_STRING) == 0 )
		m_F_64.ShowWindow(SW_HIDE);
}	

/*------------------------------------------------------------------------*/
BOOL CPflFelder::OnInitDialog() 
{
	CDialogMultiLang::OnInitDialog();

	ShowCheckboxes();
	
	m_dlg.DataExchangeFromBuffer();	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

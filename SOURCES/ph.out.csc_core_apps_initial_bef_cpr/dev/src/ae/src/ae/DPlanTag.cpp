/*************************************************************************/
/*                                                                       */
/*  Quelle  : dplantag.cpp                                               */
/*  Autor   : A.Schmidt-Rehschuh                                         */
/*  erstellt: 18.12.96                                                   */
/*  Aufgabe : Darstellung Tagesanrufplan; Online Pflege; Protokoll-      */
/*            anzeige; Anruf auslösen                                    */
/*  Klassen : CDPlanTag   : Rufplananzeige über Auswahl                  */
/*            CDPlanTagUpd: Neuanlage/Änderung einzelner Ruf             */
/*            CDPlanTagPrt: Protokollanzeige einzelner Ruf               */
/*            CDPlanTagLoe: Auswahl Löschgrund (für Protokoll)           */
/*            CDPlanTagRuf: Direkte Anzeige des aktuellen Rufes          */
/*                                                                       */
/*************************************************************************/


/*** INCLUDE **************************************************************/

#include "stdafx.h"
#include "DPlanTag.h"
#include "aarufpl.h"
#include "DKndWahl.h"
#include <kndsel.h>
#include "DKndInf.h"
#include "DAufInf.h"
#include "DKritik.h"
#include "AeFView.h"
#include "GetNextPhoneCall.h"
#include <statistics.h>
#include "DAufAuswahl.h"
#include "MainFrm.h"

/*** DEFINE ***************************************************************/
#define MAXIMUM_POOLID      99

enum E_TIME { HHMMSS = 1, HHMM, MMSS, HH, MM, SS, HHMMO };
#define SET_DATE        ddmmyyyy - 1
#define ZEILEN          12              /*  Anzahl Zeilen in Listbox*/

#define P_EILRUFZEIT       20
#define P_NORMRUFZEIT      40
#define P_VORRUFZEIT       50
#define P_NACHRUFZEIT      30
#define P_GESPERRT         -1
#define P_FALSCHERUFNR     01
#define P_ERFOLGLOSERRUF   02
#define P_HEUTEKEINRUF     03
#define P_FREITEXT         04
#define P_FALSCHERREINRUFZ 99

#define P_PHONETISCH       "PH"
#define P_PARALELL         "DP"
#define P_SERIELL          "DS"
#define P_MSERIELL         "DA"

#define PLUS  '+'
#define MINUS '-'

#define VK_PLUS        187
#define NU_PLUS        107
#define VK_MINUS       189
#define NU_MINUS       109

#define S_INSERT       "insert"
#define S_UPDATE       "update"
#define S_DELETE       "delete"


#define F_INSERT       0
#define F_UPDATE       1
#define F_DELCALL      2
#define F_UPDCALL      3
#define F_GETGRASP     4
#define F_SELWITHSET   5
#define F_SELECT       6
#define F_SELFIRST     7
#define F_SELNEXT      8
#define F_SELPREVIOUS  9
#define F_SELCLOSE    10

#define F_SETGRASP     -9
#define F_UNSET        -8
#define F_SET          -7
#define F_DELDPOINT    -1
#define NEW            -1
#define S_VER          0
#define S_LOE          1

#define ST_UB           0
#define ST_AN           1
#define ST_DE           2
#define ST_EN           3
#define ST_KA           4
#define ST_LO           5
#define ST_VS           6
#define ST_OB           7
#define ST_OS           98   /* alle offenen nicht gesperrten! */
#define ST_GS           99
#define L_MAX_TIME_MOVE 15
#define MAX_TIME_MOVE    4

#define DAFUE_PARALELL  "DP"
#define M_QUESTIONYES   MB_ICONQUESTION |MB_DEFBUTTON1

enum COLUMNS
{
    P_KST = 0, P_ST, P_PR, P_RUFZEIT, P_APOTHEKE, P_APO_NAME,
    P_KURZWAHL, P_TEL_NR, P_URZEIT, P_TOURZEIT, P_ANRUFART, P_RR,
    P_LFDAKTION, P_BEMERKUNG, P_IDFNR, P_STLOESCH, P_FILIALE,
    P_POOL, P_INFO
};

enum FIELDS
{
    F_KST = 0, F_ZEIT, F_URZEIT, F_RUFZEIT, F_STAT,
    F_STAT_RUF, F_STAT_VER, F_STAT_LOE, F_UNAME, F_BEMERKUNG
};


/*** MACRO ****************************************************************/

#define NUM_COLUMNS(x) sizeof( x ) / ( ( 3 * sizeof( int ) ) + sizeof( char * ) )

/*** STRUCTUR *************************************************************/

/*** GLOBALE  *************************************************************/

static COLUMNS_TYPES Columns[] =
{
    P_KST,       "",  20, LVCFMT_LEFT,
    P_ST,        "",  28, LVCFMT_LEFT,
    P_PR,        "",  28, LVCFMT_LEFT,
    P_RUFZEIT,   "",  50, LVCFMT_CENTER,
    P_APOTHEKE,  "", 130, LVCFMT_LEFT,
    P_APO_NAME,  "", 112, LVCFMT_LEFT,
    P_KURZWAHL,  "",  60, LVCFMT_CENTER,
    P_TEL_NR,    "",  81, LVCFMT_CENTER,
    P_URZEIT,    "",   0, LVCFMT_CENTER,
    P_TOURZEIT,  "",  50, LVCFMT_CENTER,
    P_ANRUFART,  "",  28, LVCFMT_LEFT,
    P_RR       , "",  28, LVCFMT_CENTER,
    P_LFDAKTION, "",   0, 0,
    P_BEMERKUNG, "",   0, 0,
    P_IDFNR    , "",   0, 0,
    P_STLOESCH , "",   0, 0,
    P_FILIALE  , "",  30, LVCFMT_LEFT,
    P_POOL,      "",  40, LVCFMT_LEFT,
    P_INFO,      "", 140, LVCFMT_LEFT,
    -1,          "",   0, 0
};

/*** DECLARATION **********************************************************/

static CString Time(int format);
static void AddMinute(char* time, int skip, int min);
static void AddMinute2Time(char* time, int skip);
static void DelDoublPoint(char* str, int* adr);
static int  CheckStr2Char(char* str, int ch);
static int  CheckStr2Num(char* str);
static void TimeEditSetting(CEdit* edit);
static int  CallServer(int skip, CRUFPTAG* d);
static CString Status(int skip, int choice);
static void SetTime(CStatic* settime, int setting);
static CString Text(CString prio);
static CString PrioPosition(int stat);
static CString& Date(CString& date, int format);
static CString Date(int format);
static long TimeCalculator(long t1, long t2, short sType = 0);

//int GetNext( long date );

/*** CDPlanTag-KLASSE *****************************************************/

CDPlanTag::CDPlanTag(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPlanTag::IDD, pParent)
    , m_CPool(_T("")), CPageBrowser(ZEILEN)
{
    m_CIdf = _T("");
    m_CStringAuswahl = _T("");
    m_CCall = _T("");
    m_bCall         = false;    //Aufruf über Auswahl Rufplan
    m_bNoParaCalls  = false;    //Es werden alle Anrufarten standardm. angezeigt
    m_VzNr          = 0;

    Columns[P_KST].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[P_ST].Columns = CResString::ex().getStrTblText(AETXT_SHORT_ST);
    Columns[P_PR].Columns = CResString::ex().getStrTblText(AETXT_SHORT_PR);
    Columns[P_RUFZEIT].Columns = CResString::ex().getStrTblText(IDS_CALLTIME);
    Columns[P_APOTHEKE].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[P_APO_NAME].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[P_KURZWAHL].Columns = CResString::ex().getStrTblText(AETXT_KURZWAHL);
    Columns[P_TEL_NR].Columns = CResString::ex().getStrTblText(AETXT_TEL_NR);
    Columns[P_URZEIT].Columns = CResString::ex().getStrTblText(IDS_URZEIT);
    Columns[P_TOURZEIT].Columns = CResString::ex().getStrTblText(AETXT_TOURZEIT);
    Columns[P_ANRUFART].Columns = CResString::ex().getStrTblText(AETXT_AT);
    Columns[P_RR].Columns = CResString::ex().getStrTblText(AETXT_RR);
    Columns[P_FILIALE].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns[P_POOL].Columns = CResString::ex().getStrTblText(AETXT_TEXT_POOL);
    Columns[P_INFO].Columns = CResString::ex().getStrTblText(AETXT_CALLINFO);
}


void CDPlanTag::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_DATUM, m_CEditDatum);
    DDX_Control(pDX, IDC_EDIT_RUFZEITAB, m_CEditRufzeitab);
    DDX_Control(pDX, IDC_STATIC_AUSWAHL, m_CStaticAuswahl);
    DDX_Control(pDX, IDC_RADIO10, m_CRadioAlle);
    DDX_Control(pDX, IDC_EDIT_IDF, m_EditIdf);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_IDF, m_CIdf);
    DDX_Text(pDX, IDC_STATIC_AUSWAHL, m_CStringAuswahl);
    DDX_Text(pDX, IDC_STATIC_DIRECT, m_CCall);
    DDX_Control(pDX, IDC_EDIT_POOL, m_CEditPool);
    DDX_Text(pDX, IDC_EDIT_POOL, m_CPool);
}


BEGIN_MESSAGE_MAP(CDPlanTag, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnButtonKnd)
    ON_EN_CHANGE(IDC_EDIT_IDF, OnChangeEditIdf)
    ON_EN_CHANGE(IDC_EDIT_RUFZEITAB, OnChangeEditRufzeitab)
    ON_BN_CLICKED(IDC_BUTTON_AENDERN, OnButtonAendern)
    ON_BN_CLICKED(IDC_BUTTON_HINZUFUEGEN, OnButtonHinzufuegen)
    ON_BN_CLICKED(IDC_BUTTON_LOESCHEN, OnButtonLoeschen)
    ON_BN_CLICKED(IDC_BUTTON_HISTORIE, OnButtonHistorie)
    ON_BN_CLICKED(IDC_BUTTON_ANRUFEN, OnButtonAnrufen)
    ON_EN_CHANGE(IDC_EDIT_DATUM, OnChangeEditDatum)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_EN_CHANGE(IDC_EDIT_POOL, OnEnChangeEditPool)
END_MESSAGE_MAP()

/*** CDPlanTagUpd-KLASSE **************************************************/

CDPlanTagUpd::CDPlanTagUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPlanTagUpd::IDD, pParent)
    , m_CPool(_T(""))
{
    m_CApo = _T("");
    m_CDatum = _T("");
    m_CName = _T("");
    m_COrt = _T("");
    m_CPlz = _T("");
    m_CTelnr = _T("");
    m_CEditrr_nr = _T("");
    m_CKurzwahl = _T("");
    m_CIdfnr = _T("");
    m_CStringAuswahl = _T("");
    m_CAnrufzeit = _T("");
    m_CBoolRr = FALSE;
    m_CPrio = _T("");
    m_CBemerkung = _T("");
    m_CAnrufart = _T("");
}

void CDPlanTagUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADIO14, m_CRadioAnrufart);
    DDX_Control(pDX, IDC_STATIC_ANRUFART, m_CStaticAnrufart);
    DDX_Control(pDX, IDC_EDIT_BEMERKUNG, m_CEditBemerkung);
    DDX_Control(pDX, IDC_STATIC_PRIO, m_CStaticPrio);
    DDX_Control(pDX, IDC_STATIC_AUSWAHL, m_CStaticAuswahl);
    DDX_Control(pDX, IDC_EDIT_ANRUFZEIT, m_EditAnrufzeit);
    DDX_Control(pDX, IDC_RADIO10, m_CRadio10);
    DDX_Control(pDX, IDC_EDIT_RR_NR, m_EditRr_nr);
    DDX_Control(pDX, IDC_STATIC_KURZWAHL, m_CStaticKurzwahl);
    DDX_Control(pDX, IDC_STATIC_KNDKLASSE, m_CStaticKndklasse);
    DDX_Control(pDX, IDC_STATIC_NAME, m_CStaticName);
    DDX_Control(pDX, IDC_STATIC_TELNR, m_CStaticTelnr);
    DDX_Control(pDX, IDC_STATIC_PLZ, m_CStaticPlz);
    DDX_Control(pDX, IDC_STATIC_ORT, m_CStaticOrt);
    DDX_Control(pDX, IDC_STATIC_DATUM, m_CStaticDatum);
    DDX_Control(pDX, IDC_STATIC_APO, m_CStaticApo);
    DDX_Control(pDX, IDC_CHECK_RR, m_CBrr);
    DDX_Text(pDX, IDC_STATIC_APO, m_CApo);
    DDX_Text(pDX, IDC_STATIC_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_STATIC_NAME, m_CName);
    DDX_Text(pDX, IDC_STATIC_ORT, m_COrt);
    DDX_Text(pDX, IDC_STATIC_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_STATIC_TELNR, m_CTelnr);
    DDX_Text(pDX, IDC_EDIT_RR_NR, m_CEditrr_nr);
    DDX_Text(pDX, IDC_STATIC_KURZWAHL, m_CKurzwahl);
    DDX_Text(pDX, IDC_STATIC_IDFNR, m_CIdfnr);
    DDX_Text(pDX, IDC_STATIC_AUSWAHL, m_CStringAuswahl);
    DDX_Text(pDX, IDC_EDIT_ANRUFZEIT, m_CAnrufzeit);
    DDX_Check(pDX, IDC_CHECK_RR, m_CBoolRr);
    DDX_Text(pDX, IDC_STATIC_PRIO, m_CPrio);
    DDX_Text(pDX, IDC_EDIT_BEMERKUNG, m_CBemerkung);
    DDX_Text(pDX, IDC_STATIC_ANRUFART, m_CAnrufart);
    DDX_Control(pDX, IDC_EDIT_POOL, m_CEditPool);
    DDX_Text(pDX, IDC_EDIT_POOL, m_CPool);
}


BEGIN_MESSAGE_MAP(CDPlanTagUpd, CDialogMultiLang)
    ON_BN_CLICKED(IDC_CHECK_RR, OnCheckRr)
    ON_EN_CHANGE(IDC_EDIT_ANRUFZEIT, OnChangeEditAnrufzeit)
    ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_EN_CHANGE(IDC_EDIT_POOL, OnEnChangeEditPool)
END_MESSAGE_MAP()

/*** CDPLANTAGPRT *********************************************************/

CDPlanTagPrt::CDPlanTagPrt(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPlanTagPrt::IDD, pParent)
{
    m_CIdfnr = _T("");
    m_CRufzeit = _T("");
    m_iIsLocked = 0;
    m_CDlgText = CResString::ex().getStrTblText(AETXT_TAGPLAN_EREIGNISSE);
}


void CDPlanTagPrt::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Control(pDX, IDC_STATIC_PLZ, m_CStaticPlz);
    DDX_Control(pDX, IDC_STATIC_ORT, m_CStaticOrt);
    DDX_Control(pDX, IDC_STATIC_NAME, m_CStaticName);
    DDX_Control(pDX, IDC_STATIC_DATUM, m_CStaticDatum);
    DDX_Control(pDX, IDC_STATIC_APO, m_CStaticApo);
    DDX_Text(pDX, IDC_STATIC_IDF, m_CIdfnr);
    DDX_Text(pDX, IDC_STATIC_RUFZEIT, m_CRufzeit);
}


BEGIN_MESSAGE_MAP(CDPlanTagPrt, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_ENTSPERREN, OnButtonEntsperren)
END_MESSAGE_MAP()

/*** CDPLANTAGLOE *********************************************************/

CDPlanTagLoe::CDPlanTagLoe(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPlanTagLoe::IDD, pParent)
{
    m_CBemerkung = _T("");
    m_iChoice = 0;
}


void CDPlanTagLoe::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADIO10, m_CRadio10);
    DDX_Control(pDX, IDC_EDIT1, m_CEditBemerkung);
    DDX_Text(pDX, IDC_EDIT1, m_CBemerkung);
}


BEGIN_MESSAGE_MAP(CDPlanTagLoe, CDialogMultiLang)
    ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
    ON_BN_CLICKED(IDC_RADIO11, OnRadio11)
    ON_BN_CLICKED(IDC_RADIO12, OnRadio12)
    ON_BN_CLICKED(IDC_RADIO13, OnRadio13)
    ON_BN_CLICKED(IDC_RADIO14, OnRadio14)
END_MESSAGE_MAP()

/*** CDPLANTAGRUF *********************************************************/

CDPlanTagRuf::CDPlanTagRuf(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPlanTagRuf::IDD, pParent)
{
    m_CAktrufzeit = _T("");
    m_CApo = _T("");
    m_CBemerkung = _T("");
    m_CDatum = _T("");
    m_CKndklasse = _T("");
    m_CKurzwahl = _T("");
    m_CName = _T("");
    m_Cort = _T("");
    m_CPlz = _T("");
    m_CPrio = _T("");
    m_CRr = _T("");
    m_CRrnr = _T("");
    m_CRufart = _T("");
    m_CRufzeit = _T("");
    m_CTelnr = _T("");
    m_CZeit = _T("");
    m_CIdfnr = _T("");
    m_CApobelegt = FALSE;
    m_CAnrufart = _T("");
    m_CZuerledigen = _T("");
    m_CBearbeitet = _T("");
    m_CGeloescht = _T("");
    m_bNotFound     = FALSE;    //wenn keine Sätze gefunden
}


void CDPlanTagRuf::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PARAAUFTRAGOEFFNEN, m_CParaauftrag);
    DDX_Control(pDX, IDC_LIST_TOUR, m_CListTour);
    DDX_Control(pDX, IDC_STATIC_ANRUFART, m_CStaticAnrufart);
    DDX_Control(pDX, IDC_STATIC_RUFZEIT, m_CStaticRufzeit);
    DDX_Control(pDX, IDC_STATIC_IDFNR, m_CStaticIdfnr);
    DDX_Control(pDX, IDC_STATIC_ZEIT, m_CStaticZeit);
    DDX_Control(pDX, IDC_STATIC_TELNR, m_CStaticTelnr);
    DDX_Control(pDX, IDC_STATIC_RUFART, m_CStaticRufart);
    DDX_Control(pDX, IDC_STATIC_RRNR, m_CStaticRrnr);
    DDX_Control(pDX, IDC_STATIC_RR, m_CStaticRr);
    DDX_Control(pDX, IDC_STATIC_PRIO, m_CStaticPrio);
    DDX_Control(pDX, IDC_STATIC_PLZ, m_CStaticPlz);
    DDX_Control(pDX, IDC_STATIC_ORT, m_CStaticOrt);
    DDX_Control(pDX, IDC_STATIC_NAME, m_CStaticName);
    DDX_Control(pDX, IDC_STATIC_KURZWAHL, m_CStaticKurzwahl);
    DDX_Control(pDX, IDC_STATIC_KNDKLASSE, m_CStaticKndklasse);
    DDX_Control(pDX, IDC_STATIC_DATUM, m_CStaticDatum);
    DDX_Control(pDX, IDC_STATIC_BEMERKUNG, m_CStaticBemerkung);
    DDX_Control(pDX, IDC_STATIC_APO, m_CStaticApo);
    DDX_Control(pDX, IDC_STATIC_AKTRUFZEIT, m_CStaticAktrufzeit);
    DDX_Text(pDX, IDC_STATIC_AKTRUFZEIT, m_CAktrufzeit);
    DDX_Text(pDX, IDC_STATIC_APO, m_CApo);
    DDX_Text(pDX, IDC_STATIC_BEMERKUNG, m_CBemerkung);
    DDX_Text(pDX, IDC_STATIC_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_STATIC_KNDKLASSE, m_CKndklasse);
    DDX_Text(pDX, IDC_STATIC_KURZWAHL, m_CKurzwahl);
    DDX_Text(pDX, IDC_STATIC_NAME, m_CName);
    DDX_Text(pDX, IDC_STATIC_ORT, m_Cort);
    DDX_Text(pDX, IDC_STATIC_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_STATIC_PRIO, m_CPrio);
    DDX_Text(pDX, IDC_STATIC_RR, m_CRr);
    DDX_Text(pDX, IDC_STATIC_RRNR, m_CRrnr);
    DDX_Text(pDX, IDC_STATIC_RUFART, m_CRufart);
    DDX_Text(pDX, IDC_STATIC_RUFZEIT, m_CRufzeit);
    DDX_Text(pDX, IDC_STATIC_TELNR, m_CTelnr);
    DDX_Text(pDX, IDC_STATIC_ZEIT, m_CZeit);
    DDX_Text(pDX, IDC_STATIC_IDFNR, m_CIdfnr);
    DDX_Text(pDX, IDC_STATIC_ANRUFART, m_CAnrufart);
    DDX_Text(pDX, IDC_STATIC_ZUBEARBEITEN, m_CZuerledigen);
    DDX_Text(pDX, IDC_STATIC_BEARBEITET, m_CBearbeitet);
    DDX_Text(pDX, IDC_STATIC_GELOESCHT, m_CGeloescht);
}


BEGIN_MESSAGE_MAP(CDPlanTagRuf, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_AENDERN, OnButtonAendern)
    ON_BN_CLICKED(IDC_BUTTON_HISTORIE, OnButtonHistorie)
    ON_BN_CLICKED(IDC_BUTTON_HINZUFUEGEN, OnButtonHinzufuegen)
    ON_BN_CLICKED(IDC_BUTTON_KEINAUFTRAG, OnButtonKeinauftrag)
    ON_BN_CLICKED(IDC_BUTTON_KNDINF, OnButtonKndinf)
    ON_BN_CLICKED(IDC_BUTTON_KNDKONTAKT, OnButtonKndkontakt)
    ON_BN_CLICKED(IDC_BUTTON_LOESCHEN, OnButtonLoeschen)
    ON_BN_CLICKED(IDC_BUTTON_AUFTRAGVERSCHIEBEN, OnButtonAuftragverschieben)
    ON_BN_CLICKED(IDC_PARAAUFTRAGOEFFNEN, OnParaauftragoeffnen)
    ON_WM_CTLCOLOR()
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/*** CDPLANTAGVER *********************************************************/

CDPlanTagVer::CDPlanTagVer(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPlanTagVer::IDD, pParent)
{
    m_CAktanrufzeit = _T("");
    m_CBemerkung = _T("");
    m_CRufzeit = _T("");
    m_CIdfnr = _T("");
    m_CNeuerufzeit = _T("");
}


void CDPlanTagVer::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_NEUERUFZEIT, m_CEditNeuerufzeit);
    DDX_Control(pDX, IDC_STATIC_RUFZEIT, m_CStaticRufzeit);
    DDX_Control(pDX, IDC_EDIT_BEMERKUNG, m_CEditBemerkung);
    DDX_Control(pDX, IDC_STATIC_AKTRUFZEIT, m_CStaticAktanrufzeit);
    DDX_Text(pDX, IDC_STATIC_AKTRUFZEIT, m_CAktanrufzeit);
    DDX_Text(pDX, IDC_EDIT_BEMERKUNG, m_CBemerkung);
    DDX_Text(pDX, IDC_STATIC_RUFZEIT, m_CRufzeit);
    DDX_Text(pDX, IDC_STATIC_IDFNR, m_CIdfnr);
    DDX_Text(pDX, IDC_EDIT_NEUERUFZEIT, m_CNeuerufzeit);
}


BEGIN_MESSAGE_MAP(CDPlanTagVer, CDialogMultiLang)
    ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
    ON_BN_CLICKED(IDC_RADIO11, OnRadio11)
    ON_BN_CLICKED(IDC_RADIO12, OnRadio12)
    ON_BN_CLICKED(IDC_RADIO13, OnRadio13)
    ON_BN_CLICKED(IDC_RADIO14, OnRadio14)
    ON_EN_CHANGE(IDC_EDIT_NEUERUFZEIT, OnChangeEditNeuerufzeit)
END_MESSAGE_MAP()

/*************************************************************************/
/*** FUNKTIONEN **********************************************************/
/*************************************************************************/

/*** CDPlanTag-ON-INIT-DIALOG *********************************************/

BOOL CDPlanTag::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    if (AeGetApp()->IsRS() || AeGetApp()->IsBG())
    {
        AeGetApp()->PoolNr = GetAeUser().GetPoolID();
    }
    m_CPool.Format("%d", AeGetApp()->PoolNr());
    m_CEditPool.SetWindowText(m_CPool);

    if (!m_bCall)
    {
        GetDlgItem(IDC_BUTTON_ANRUFEN)->EnableWindow(FALSE);
    }

    m_CEditRufzeitab.SetWindowText("00:00");
    m_CRadioAlle.SetCheck(TRUE);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    AllgSetColumnWidthUser(m_ListCtl, "CDPlanTag", KEY_PATH, NUM_COLUMNS(Columns));

    if (m_CIdf.GetLength())
    {
        if (!GetPage() && m_bCall)
            CDialogMultiLang::OnCancel();  // wegen nachverarbeitung von AA
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
}

void CDPlanTag::OnDestroy()
{
    AllgWriteColumnWidthUser(m_ListCtl, "CDPlanTag", KEY_PATH, NUM_COLUMNS(Columns));
    CloseCursor();
    CDialogMultiLang::OnDestroy();
    //return CDialogMultiLang::DestroyWindow();
}

/*** CDPlanTag-GET-PAGE ***************************************************/

bool CDPlanTag::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    CRUFPTAG rufptag;
    CTOURZEIT tour;
    CDPlanTagUpd rufptagupd;
    int  newRow = 0;
    int  adr = F_DELDPOINT;         /* doppelpunkt entfernen */
    char* timeStr;
    char rufzeit[7];
    CStringArray output;

    output.SetSize(NUM_COLUMNS(Columns));

    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        GetDlgItem(IDC_EDIT_IDF)->GetWindowText(m_CIdf);
        m_CEditRufzeitab.GetWindowText(rufzeit, 6);
        DelDoublPoint(rufzeit, &adr);
        CString date = Date(yyyymmdd);

        rufptag.s.PRIORITAET = m_bCall ? 1 : 0;  /* dirty read */
        rufptag.s.DATUM   = atol(date);
        rufptag.s.RUFZEIT = atol(rufzeit);
        rufptag.s.STATUS  = static_cast<short>(GetStatusSelect(&newRow));
        strcpy_s(rufptag.s.ANRUFART, m_bNoParaCalls ? DAFUE_PARALELL : "  ");

        if (m_CIdf.IsEmpty())
            rufptag.s.IDFNR = NO_CUSTOMER;          /* alle holen */
        else if (atoi(m_CIdf) == NO_CUSTOMER)
        {
            // Bitte ändern
            CheckRadioButton(IDC_RADIO10, IDC_RADIO16, IDC_RADIO12);
            rufptag.s.PRIORITAET = 1;  /* commited read */
            rufptag.s.STATUS = static_cast<short>(GetStatusSelect(&newRow));
            rufptag.s.IDFNR  = NO_CUSTOMER;
            GetDlgItem(IDC_EDIT_IDF)->SetWindowText("");
        }
        else
           rufptag.s.IDFNR = atol(m_CIdf);
    }
    if (AeGetApp()->IsKundeHome())
        rufptag.s.FILIALNR = AeGetApp()->VzNr();
    else if (AeGetApp()->IsAnrufPlanEigen())
        rufptag.s.FILIALNR = AeGetApp()->VzNr();
    else
        rufptag.s.FILIALNR = 0;
    rufptag.s.REGIONNR = AeGetApp()->VzNr();
    if ((rufptag.s.IDFNR > 0) && (m_VzNr != 0))
    {
        rufptag.s.FILIALNR = m_VzNr;
    }
    m_CEditPool.GetWindowText(m_CPool);
    AeGetApp()->PoolNr = static_cast<short>(atoi(m_CPool));
    rufptag.s.POOLID = static_cast<short>(atoi(m_CPool));

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, rufptag.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    for (int i = 0; i < ZEILEN; i++)
    {
        rufptag.s.UID = m_bCall ? 1 : 0;    // alle oder < aktuelle zeit
        CallServer(F_SELECT, &rufptag);
        m_bCursorOpen = true;               //Datenbankcurser offen
        rufptag.s.FETCH_REL = 1;            //normaler Fetch
        if (rufptag.rc == SRV_SQLNOTFOUND)
        {
            if (m_bFirstDataset)      //kein Satz gefunden
            {
                CloseCursor();
                if (newRow && (rufptag.s.IDFNR > 0))
                {
                    rufptagupd.m_CIdfnr.Format("%ld", rufptag.s.IDFNR);
                    rufptagupd.m_CStringAuswahl = S_INSERT;
                    rufptagupd.m_sVzNr = rufptag.s.FILIALNR;
                    rufptagupd.m_CPool = m_CPool;
                    if (rufptagupd.DoModal() == IDOK)
                        SetListbox(NEW, &rufptagupd);
                }
                else if (rufptag.s.POOLID != 0)
                {
                    if (AeGetApp()->IsRS() || AeGetApp()->IsBG())
                    {
                        return false;
                    }
                    rufptag.s.POOLID = 0;
                    --i;
                    continue;
                }
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl Positionen letzte Seite
            break;
        }

        if ((newRow == 2) && (rufptag.s.LFDAKTION > 0) && (rufptag.s.STATUS != ST_VS) && (rufptag.s.STATUS != ST_OB))
           continue;    // wegen outer selection der tabellen gibt es null-felder!

        m_bFirstDataset = false;

        //Feststellen nächste Tourzeit
        tour.SetIdfnr(rufptag.s.IDFNR);
        tour.SetVertriebszentrumnr(rufptag.s.FILIALNR);
        tour.SelNextTour();
        output[P_TOURZEIT].Format("%2.2s:%2.2s", tour.s.TOURID, tour.s.TOURID + 2);

        output[P_KST] = kb.Next();              //Buchstabenanzeige
        output[P_ST].Format("%s", EventPosition(rufptag.s.STATUS));
        output[P_PR].Format("%s", PrioPosition(rufptag.s.PRIORITAET));
        timeStr = AllgZeit2CharHHMM(rufptag.s.RUFZEIT);
        output[P_URZEIT].Format("%s", timeStr);
        AllgEntfSpaces(rufptag.s.NAMEAPO);
        AllgEntfSpaces(rufptag.s.NAMEINHABER);
        output[P_APOTHEKE].Format("%s", rufptag.s.NAMEAPO);
        if (AeGetApp()->IsHR())
        {
            output[P_APOTHEKE] += " ";
            output[P_APOTHEKE] += rufptag.s.NAMEINHABER;
        }
        AllgEntfSpaces(rufptag.s.ORT);
        output[P_APO_NAME].Format("%s", rufptag.s.ORT);
        AllgEntfSpaces(rufptag.s.ANRUFART);
        output[P_ANRUFART].Format("%s", rufptag.s.ANRUFART);
        AllgEntfSpaces(rufptag.s.TELKURZWAHL);
        output[P_KURZWAHL].Format("%s", rufptag.s.TELKURZWAHL);
        AllgEntfSpaces(rufptag.s.TELNR);

        if (rufptag.s.TELRUECKRUFNR[0] != ' ')
        {
            AllgEntfSpaces(rufptag.s.TELRUECKRUFNR);
            output[P_TEL_NR].Format("%s", rufptag.s.TELRUECKRUFNR);
        }
        else
            output[P_TEL_NR].Format("%s", rufptag.s.TELNR);

        if (rufptag.s.RUFZEITGEAENDERT != 0)
            timeStr = AllgZeit2CharHHMM(rufptag.s.RUFZEITGEAENDERT);
        output[P_RUFZEIT].Format("%s", timeStr);
        output[P_RR] = (rufptag.s.STAGRUECKRUF[0] == '1') ? "J" : "N";

        output[P_LFDAKTION].Format("%d", rufptag.s.LFDAKTION);
        AllgEntfSpaces(rufptag.s.BEMERKUNG);
        output[P_BEMERKUNG].Format("%s", rufptag.s.BEMERKUNG);
        output[P_IDFNR].Format("%ld", rufptag.s.IDFNR);
        output[P_STLOESCH].Format("%d", rufptag.s.LOESCHGRUND);
        output[P_FILIALE].Format("%d", rufptag.s.FILIALNR);
        output[P_POOL].Format("%d", rufptag.s.POOLID);
        AllgEntfSpaces(rufptag.s.CALLINFO);
        output[P_INFO].Format("%s", rufptag.s.CALLINFO);

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS(Columns), output))
        {
            return false;
        }
    } //Ende der for()-Schleife

    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return true;
}

/*** CDPlanTag-GET-STATUS-SELECT ******************************************/

int CDPlanTag::GetStatusSelect(int* newRow)
{
    int stat = 0;

    switch (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO17))
    {
    case IDC_RADIO10: stat = ST_UB; *newRow = 1; break;
    case IDC_RADIO11: stat = ST_OB; *newRow = 2; break;
    case IDC_RADIO12: stat = ST_VS; *newRow = 2; break;
    case IDC_RADIO13: stat = ST_KA; *newRow = 0; break;
    case IDC_RADIO14: stat = ST_LO; *newRow = 0; break;
    case IDC_RADIO15: stat = ST_DE; *newRow = 0; break;
    case IDC_RADIO16: stat = ST_EN; *newRow = 0; break;
    case IDC_RADIO17: stat = ST_GS; *newRow = 0; break;
    default: *newRow = 0;
    }

    return stat;
}

/*** CDPlanTag-CLOSE-CURSOR ***********************************************/

void CDPlanTag::CloseCursor()
{
    if (!m_bCursorOpen)
        return;

    CRUFPTAG rufptag;
    CallServer(F_SELCLOSE, &rufptag);

    ResetCursor();
    Reset();
}

/*** CDPlanTag-ON-ChangeEditDatum *****************************************/

void CDPlanTag::OnChangeEditDatum()
{
    AllgDatumKontr(&m_CEditDatum, ALGF_FORM_DATUM_TTMMJJ);
}

/*** CDPlanTag-ON-OK ******************************************************/

void CDPlanTag::OnOK()
{
    CString date;
    m_CEditDatum.GetWindowText(date);
    UpdateData();

    if (atol(date) > 0)
    {
        GetDlgItem(IDC_BUTTON_ANRUFEN)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_LOESCHEN)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_AENDERN)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_HINZUFUEGEN)->EnableWindow(FALSE);
    }
    else
    {
        if (m_bCall)
            GetDlgItem(IDC_BUTTON_ANRUFEN)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_LOESCHEN)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_AENDERN)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_HINZUFUEGEN)->EnableWindow(TRUE);
    }

    Date(date, SET_DATE);
    if ((GetFocus() == GetDlgItem(IDC_EDIT_IDF))
        || (GetFocus() == GetDlgItem(IDC_EDIT_POOL))
        || (GetFocus() == GetDlgItem(IDC_EDIT_DATUM))
        || (GetFocus() == GetDlgItem(IDC_EDIT_RUFZEITAB))
        || (GetFocus() == GetDlgItem(IDC_RADIO10))
        || (GetFocus() == GetDlgItem(IDC_RADIO11))
        || (GetFocus() == GetDlgItem(IDC_RADIO12))
        || (GetFocus() == GetDlgItem(IDC_RADIO13))
        || (GetFocus() == GetDlgItem(IDC_RADIO14))
        || (GetFocus() == GetDlgItem(IDC_RADIO15))
        || (GetFocus() == GetDlgItem(IDC_RADIO16))
        || (GetFocus() == GetDlgItem(IDC_RADIO17)))
    {
        CallGetPage();
    }
    else  // ( GetFocus() == GetDlgItem( IDC_LIST1 ) )
    {
        if (m_bCall && GetDlgItem(IDC_BUTTON_ANRUFEN)->IsWindowEnabled())
            OnButtonAnrufen();
        else
            OnButtonHistorie();
    }
}

/*** CDPlanTag-CALL-GET-PAGE **********************************************/

void CDPlanTag::CallGetPage()
{
    SetItemCountOfCurrentPage(ZEILEN);
    m_bFirstDataset = true;
    m_ListCtl.DeleteAllItems();
    CloseCursor();
    GetPage();
}

/*** CDPlanTag-ON-BUTTON-AENDERN ******************************************/

void CDPlanTag::OnButtonAendern()
{
    if (CheckDeleted())
    {
        GetDlgItem(IDC_EDIT_IDF)->SetFocus();
        return;
    }

    SelectEintrag(F_UPDCALL);
    UpdateData();

    CallGetPage(); // neu selektieren!
}

/*** CDPlanTag-ON-BUTTON-ANRUFEN ******************************************/

void CDPlanTag::OnButtonAnrufen()
{
    CDPlanTagRuf dlgPlanTagRuf;
    int rc;

    if (CheckDeleted())
    {
        GetDlgItem(IDC_EDIT_IDF)->SetFocus();
        return;
    }
    else if (GetIdfNrOfListBox(dlgPlanTagRuf.m_CIdfnr, dlgPlanTagRuf.m_sVzNr) > -1)
    {
        //SetRufPlanKndInfo( &d, m_ListCtl.GetNextItem( -1, LVNI_SELECTED ) );
        CloseCursor();
        if (CheckAndSetGrasp(F_SET) != 0)
        {
            MsgBoxOK(IDS_CALL_ACT, MB_ICONINFORMATION);
            return;
        }

        GetAktRufZeitOfListBox(dlgPlanTagRuf.m_CAktrufzeit);
        GetRufZeitOfListBox(dlgPlanTagRuf.m_CRufzeit);
        dlgPlanTagRuf.m_CPool = m_CPool;
        rc = dlgPlanTagRuf.DoModal();
        CheckAndSetGrasp(F_UNSET);

        if (m_bCall)
        {
            m_CIdf = dlgPlanTagRuf.m_CIdfnr;   // wenn von ausserhalb gerufen!!!!!
            m_VzNr = dlgPlanTagRuf.m_sVzNr;
            UpdateData(FALSE);
            if (rc == IDCANCEL)
                CDialogMultiLang::OnCancel();
            else
                CDialogMultiLang::OnOK();
            return;
        }
        //MsgBoxOK( "Wieder zurueck" );
        GetPage();    // refresh on listbox
    }
}

/*** CDPlanTag-ON-BUTTON-HISTORIE *****************************************/

void CDPlanTag::OnButtonHistorie()
{
    CDPlanTagPrt plantagprt;

    if (GetIdfNrOfListBox(plantagprt.m_CIdfnr, plantagprt.m_sVzNr) > -1)
    {
        GetRufZeitOfListBox(plantagprt.m_CRufzeit);
        plantagprt.m_iIsLocked = GetLockOfListBox();
        if (plantagprt.DoModal())
        {
            CallGetPage();
        }
    }
}

/*** CDPlanTag-ON-BUTTON-HINZUFUEGEN **************************************/

void CDPlanTag::OnButtonHinzufuegen()
{
    CDPlanTagUpd rufptagupd;

    if (GetIdfNrOfListBox(rufptagupd.m_CIdfnr, rufptagupd.m_sVzNr) == -1)
    {
        GetDlgItem(IDC_EDIT_IDF)->GetWindowText(rufptagupd.m_CIdfnr);
        rufptagupd.m_sVzNr = m_VzNr;
    }
    rufptagupd.m_CStringAuswahl = S_INSERT;
    m_CEditPool.GetWindowText(m_CPool);
    AeGetApp()->PoolNr = static_cast<short>(atoi(m_CPool));
    rufptagupd.m_CPool = m_CPool;
    if (rufptagupd.DoModal() == IDOK)
    {
        SetListbox(NEW, &rufptagupd);
        CallGetPage();
    }
    else
        GetDlgItem(IDC_EDIT_IDF)->SetFocus();
}

/*** CDPlanTag-ON-BUTTON-LOESCHEN *****************************************/

void CDPlanTag::OnButtonLoeschen()
{
    CDPlanTagLoe del;

    if (CheckDeleted())
    {
        GetDlgItem(IDC_EDIT_IDF)->SetFocus();
        return;
    }
    if (MsgBoxYesNo(IDP_SOLL_DEL_SATZ) == IDYES)
    {
        if (del.DoModal() == IDCANCEL)
            return;
        if (del.m_CBemerkung.IsEmpty())
            del.m_CBemerkung = CResString::ex().getStrTblText(AETXT_MANUELL_LOESCH);

        CString str;
        str.Format("%d", del.m_iChoice);
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            m_ListCtl.SetItemText(pos, P_BEMERKUNG, del.m_CBemerkung);
            m_ListCtl.SetItemText(pos, P_STLOESCH, str);
            m_ListCtl.SetItemText(pos, P_ST, "LO");
            SelectEintrag(F_DELCALL);
            CallGetPage();
        }
    }
}

/*** CDPlanTag-SELECT-EINTRAG *********************************************/

void CDPlanTag::SelectEintrag(int call)
{
    CDPlanTagUpd plantagupd;

    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (CheckAndSetGrasp(F_SET) != 0)
        {
            MsgBoxOK(IDS_CALL_ACT, MB_ICONINFORMATION);
            return;
        }

        plantagupd.m_CStringAuswahl = S_UPDATE;
        GetIdfNrOfListBox(plantagupd.m_CIdfnr, plantagupd.m_sVzNr);
        plantagupd.m_CAnrufzeit = m_ListCtl.GetItemText(pos, P_URZEIT) == m_ListCtl.GetItemText(pos, P_RUFZEIT)
            ? m_ListCtl.GetItemText(pos, P_URZEIT)
            : m_ListCtl.GetItemText(pos, P_RUFZEIT);

        plantagupd.m_CEditrr_nr = m_ListCtl.GetItemText(pos, P_TEL_NR);
        plantagupd.m_CPrio = m_ListCtl.GetItemText(pos, P_PR);
        plantagupd.m_CBemerkung = (call == F_UPDCALL) ? "" : m_ListCtl.GetItemText(pos, P_BEMERKUNG);
        plantagupd.m_CAnrufart = m_ListCtl.GetItemText(pos, P_ANRUFART);
        plantagupd.m_CPool = m_ListCtl.GetItemText(pos, P_POOL);
        plantagupd.m_CBoolRr = (m_ListCtl.GetItemText(pos, P_RR) == "J") ? TRUE : FALSE;

        if (call == F_DELCALL)
        {
            SetListbox(pos, &plantagupd);
            return;
        }

        if (plantagupd.DoModal() == IDOK)
            SetListbox(pos, &plantagupd);
        else
        {
            CheckAndSetGrasp(F_UNSET);
            GetDlgItem(IDC_EDIT_IDF)->SetFocus();
        }
    }
}

/*** CDPlanTag-CHECK-AND-SET-GRASP ****************************************/

int CDPlanTag::CheckAndSetGrasp(int skip)
{
    CRUFPTAG db;
    CString  buf;

    CString date = Date(yyyymmdd);
    db.s.IDFNR   = GetIdfNrOfListBox(buf, m_VzNr);
    db.s.FILIALNR = m_VzNr;
    db.s.REGIONNR = AeGetApp()->VzNr();
    db.s.RUFZEIT = GetRufZeitOfListBox(buf);
    db.s.DATUM   = atol(date);

    if (skip == F_UNSET)
    {
        return CallServer(F_UNSET, &db);
    }

    int rc = CallServer(F_GETGRASP, &db);
    if (rc == 0)
    {
        rc = CallServer(F_SETGRASP, &db);
    }

    return rc;
}


/*** CDPlanTag-SET-LIST-BOX ***********************************************/

void CDPlanTag::SetListbox(int rowid, class CDPlanTagUpd* d)
{
    CString  letter;
    CString  status;
    CString  lfdaktion;
    char     time[10];
    int adr = F_DELDPOINT;
    CRUFPTAG db;

    if (rowid == NEW)
    {
        status = "OB";
        //letter = ( rowid = m_ListCtl.GetItemCount() ) + AeGetApp()->Letter_A();
        rowid = m_ListCtl.GetItemCount();
        letter.Format("%ld", rowid + AeGetApp()->Letter_A());

        if (m_ListCtl.InsertItem(rowid, letter) < 0)
        {
            MsgBoxOK(IDS_ERROR_LISTBOX);
            return;
        }

        m_ListCtl.SetItemText(rowid, P_URZEIT, d->m_CAnrufzeit);
        m_ListCtl.SetItemText(rowid, P_APO_NAME, d->m_COrt);
        m_ListCtl.SetItemText(rowid, P_APOTHEKE, d->m_CApo);
        m_ListCtl.SetItemText(rowid, P_KURZWAHL, d->m_CKurzwahl);
        m_ListCtl.SetItemText(rowid, P_LFDAKTION, "0");
        m_ListCtl.SetItemText(rowid, P_IDFNR, d->m_CIdfnr);
        m_ListCtl.SetItemText(rowid, P_STLOESCH, "0");
        CString fili;
        fili.Format("%d", d->m_sVzNr);
        m_ListCtl.SetItemText(rowid, P_FILIALE, fili);
    }
    else
    {
        if ((status = m_ListCtl.GetItemText(rowid, P_ST)) == "OB")
        {
            if (m_ListCtl.GetItemText(rowid, P_URZEIT) == d->m_CAnrufzeit)
                ;   /* kann nicht auf != abfragen */
            else
                status = "VS";
        }
    }

    m_ListCtl.SetItemText(rowid, P_ST, status);
    m_ListCtl.SetItemText(rowid, P_PR, PrioPosition(d->CheckPrio()));
    m_ListCtl.SetItemText(rowid, P_ANRUFART, d->m_CAnrufart);
    m_ListCtl.SetItemText(rowid, P_RUFZEIT, d->m_CAnrufzeit);
    m_ListCtl.SetItemText(rowid, P_RR, (d->m_CBoolRr == TRUE) ? "J" : "N");
    m_ListCtl.SetItemText(rowid, P_BEMERKUNG, d->m_CBemerkung);
    m_ListCtl.SetItemText(rowid, P_POOL, d->m_CPool);

    m_ListCtl.SetItemText(rowid, P_TEL_NR, d->m_CEditrr_nr.IsEmpty() ? d->m_CTelnr : d->m_CEditrr_nr);

    CString date = Date(yyyymmdd);
    strcpy(time, m_ListCtl.GetItemText(rowid, P_URZEIT));
    DelDoublPoint(time, &adr);

    db.s.IDFNR = atol(d->m_CIdfnr);
    db.s.POOLID = static_cast<short>(atoi(d->m_CPool));
    db.s.FILIALNR = static_cast<short>(atoi(m_ListCtl.GetItemText(rowid, P_FILIALE)));
    db.s.DATUM = atol(date);
    db.s.RUFZEIT = atol(time);
    db.s.LFDAKTION = static_cast<short>(atoi(m_ListCtl.GetItemText(rowid, P_LFDAKTION)) + 1);
    lfdaktion.Format("%d", db.s.LFDAKTION);
    m_ListCtl.SetItemText(rowid, P_LFDAKTION, lfdaktion);
    db.s.PRIORITAET = static_cast<short>(d->CheckPrio());
    //db.s.POOLID = 0;
    strcpy(db.s.MANUELL, "M");
    strcpy(db.s.STAGRUECKRUF, d->m_CBoolRr == TRUE ? "1" : "0");
    strcpy(db.s.TELRUECKRUFNR, d->m_CBoolRr == TRUE ? d->m_CEditrr_nr : " ");
    db.s.STATUS = static_cast<short>(EventStatus(status));

    int rc = atoi(m_ListCtl.GetItemText(rowid, P_STLOESCH));
    if (rc < 0)
    {
        rc = 0;
    }

    db.s.LOESCHGRUND = static_cast<short>(rc);

    strcpy(time, d->m_CAnrufzeit);
    adr = F_DELDPOINT;
    DelDoublPoint(time, &adr);
    db.s.RUFZEITGEAENDERT = atol(time);
    db.s.UID = (long)GetAeUser().GetUID();
    strcpy(db.s.ANRUFART, m_ListCtl.GetItemText(rowid, P_ANRUFART)); // 27.01.97

    if ((d->m_CStringAuswahl == S_INSERT) && d->m_CBemerkung.IsEmpty())
        strcpy(db.s.BEMERKUNG, (char*)CResString::ex().getStrTblText(IDS_MANUAL).GetString());
    else if ((d->m_CStringAuswahl == S_UPDATE) && d->m_CBemerkung.IsEmpty())
        strcpy(db.s.BEMERKUNG, (char*)CResString::ex().getStrTblText(IDS_MANUAL_CHANGED).GetString());
    else if (d->m_CBemerkung.IsEmpty())
    {
        MsgBoxOK(IDS_BEM_LEER);
        strcpy(db.s.BEMERKUNG, " ");
    }
    else
        strcpy(db.s.BEMERKUNG, d->m_CBemerkung);

    db.s.FETCH_REL = 0;
    if (CallServer(d->m_CStringAuswahl == S_INSERT ? F_INSERT : F_UPDATE, &db) == 1)
    {
        MsgBoxOK(IDS_SATZ_VORH);
        m_ListCtl.DeleteAllItems();
    }
}


/*** CDPlanTag-CheckDeleted() ***************************************/

int CDPlanTag::CheckDeleted()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString csStat = m_ListCtl.GetItemText(pos, P_ST);
        if (csStat == "OB" || csStat == "VS")
            return 0;

        if (csStat == "GS") csStat = CResString::ex().getStrTblText(IDS_INACTIV_ENTRY);
        else if (csStat == "LO") csStat = CResString::ex().getStrTblText(IDS_ENTRY_DELETED);
        else if (csStat == "KA") csStat = CResString::ex().getStrTblText(IDS_NO_AUFTR);
        else if (csStat == "AN") csStat = CResString::ex().getStrTblText(IDS_AUFTR_IN_WORK);
        else if (csStat == "DE") csStat = CResString::ex().getStrTblText(IDS_END_DAFU);
        else if (csStat == "EN") csStat = CResString::ex().getStrTblText(IDS_AUFTR_DONE);
        else csStat = CResString::ex().getStrTblText(IDS_UNKNOWN);

        MsgBoxOK(csStat, MB_ICONINFORMATION);
    }
    else
    {
        MsgBoxOK(IDS_NO_ENTRY, MB_ICONINFORMATION);
    }

    return 1;
}

/*** CDPlanTag-SET-RUFPLAN-KND-INFO ***************************************/

void CDPlanTag::SetRufPlanKndInfo(CDPlanTagRuf* d, int pos)
{
    d->m_CRufart = m_ListCtl.GetItemText(pos, P_PR);
    d->m_CRr = m_ListCtl.GetItemText(pos, P_RR);
    d->m_CRrnr = (d->m_CRr == "J") ? m_ListCtl.GetItemText(pos, P_TEL_NR) : " ";
    d->m_CAktrufzeit = m_ListCtl.GetItemText(pos, P_RUFZEIT);
    d->m_CRufzeit = m_ListCtl.GetItemText(pos, P_URZEIT);
    d->m_CPrio = Text(m_ListCtl.GetItemText(pos, P_PR));
    d->m_CBemerkung = m_ListCtl.GetItemText(pos, P_BEMERKUNG);
    d->m_CPool = m_CPool;
}

/*** CDPlanTag-ON-HOOK-FKT ************************************************/
/* Bearbeitung von Tastaturereignissen auf dem gesammten Dialog           */
/* (unabhängig vom ausgewählten Bedienelement)                            */
/**************************************************************************/

LRESULT CDPlanTag::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    LRESULT res = CPageBrowser::OnHookNextPrev(lpMsg);
    if (res != 0L)
    {
        return res;
    }

    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        CKndInf dlgKndInf;
        CString filler;
        short sVzNo;

        dlgKndInf.SetIdfNr(GetIdfNrOfListBox(filler, sVzNo));
        dlgKndInf.SetKndVz(sVzNo);
        dlgKndInf.DoModal();
        return 1L;
    }
    if (((LPMSG)lpMsg)->wParam == VK_F6)
    {
        CString kndNr;
        short sVzNo;
        GetIdfNrOfListBox(kndNr, sVzNo);

        if (AeGetApp()->IsNewF6())
        {
            CDAufAuswahl dlgAufAuswahl;
            dlgAufAuswahl.m_KndNr = kndNr;
            dlgAufAuswahl.DoModal();
        }
        else
        {
            CDAufInf dlgAufInf;
            dlgAufInf.m_KndNr = kndNr;
            dlgAufInf.DoModal();
        }
        return 1L;
    }

    return 0L;
}

/*** CDPlanTag-ON-DBLCLK-LIST1 ********************************************/

void CDPlanTag::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag(F_UPDCALL);
    *pResult = 0L;
}

/*** CDPlanTag-ON-KEY-DOWN-LIST1 ******************************************/

void CDPlanTag::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

/*** CDPlanTag-ON-BUTTON-KND **********************************************/

void CDPlanTag::OnButtonKnd()
{
    CDKndWahl kunde;
    if (kunde.DoModal() != IDOK)
    {
        return;
    }

    CString str;
    str.Format("%ld", kunde.GetKndNr());
    GetDlgItem(IDC_EDIT_IDF)->SetWindowText(str);
    m_VzNr = kunde.GetKndVz();
    CloseCursor();
    GetPage();
}


/*** CDPlanTag-ON-CHANGE-EDIT-IDF *****************************************/

void CDPlanTag::OnChangeEditIdf()
{
    AllgWertKontr(&m_EditIdf, MAXIMUM_IDF);
}

/*** CDPlanTag-ON-CHANGE-EDIT-RUFZEITAB ***********************************/

void CDPlanTag::OnChangeEditRufzeitab()
{
    TimeEditSetting(&m_CEditRufzeitab);
}

void CDPlanTag::OnEnChangeEditPool()
{
    AllgWertKontr(&m_CEditPool, MAXIMUM_POOLID);
}

/********* EIGENE FUNKTIONEN **********************************************/
/*** CDPlanTag-EVENT-POSITION *********************************************/

CString CDPlanTag::EventPosition(int stat)
{
    switch (stat)
    {
    case -1:
        return "GS";
    case  0:
    case  7:
    default:
        return "OB";
    case  1:
        return "AN";
    case  2:
        return "DE";
    case  3:
        return "EN";
    case  4:
        return "KA";
    case  5:
        return "LO";
    case  6:
        return "VS";
    }
}

/*** CDPlanTag-EVENT-STATUS ***********************************************/

int CDPlanTag::EventStatus(CString stat)
{
    int rc;

    if (stat == "OB")
        rc = 7;
    else if (stat == "AN")
        rc = 1;
    else if (stat == "DE")
        rc = 2;
    else if (stat == "EN")
        rc = 3;
    else if (stat == "KA")
        rc = 4;
    else if (stat == "LO")
        rc = 5;
    else if (stat == "VS")
        rc = 6;
    else
        rc = 7;

    return rc;
}

/*** CDPlanTag-GET-POS-OF-LIST-BOX ****************************************/

long CDPlanTag::GetIdfNrOfListBox(CString& idfNr, short& VzNo)
{
    idfNr = "-1";

    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        idfNr = m_ListCtl.GetItemText(pos, P_IDFNR);
        VzNo = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, P_FILIALE)));
    }

    return atol(idfNr);
}

/*** CDPlanTag-GET-RUF-ZEIT-OF-LIST-BOX ************************************/

long CDPlanTag::GetRufZeitOfListBox(CString& rufzeit)
{
    char buf[7];
    int adr = F_DELDPOINT;

    rufzeit = "-1";

    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        rufzeit = m_ListCtl.GetItemText(pos, P_URZEIT);
        sprintf(buf, "%5.5s", rufzeit.GetString());
        DelDoublPoint(buf, &adr);
        rufzeit = buf;
    }

    return atol(buf);
}

/*** CDPlanTag-GET-AKT-RUF-ZEIT-OF-LIST-BOX ********************************/

long CDPlanTag::GetAktRufZeitOfListBox(CString& aktrufzeit)
{
    char buf[7];
    int adr = F_DELDPOINT;

    aktrufzeit = "-1";

    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        aktrufzeit = m_ListCtl.GetItemText(pos, P_RUFZEIT);
        sprintf(buf, "%5.5s", aktrufzeit.GetString());
        DelDoublPoint(buf, &adr);
        aktrufzeit = buf;
    }

    return atol(buf);
}

/*** CDPlanTag-GET-LOCK-OF-LIST-BOX ***************************************/

int CDPlanTag::GetLockOfListBox()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        return m_ListCtl.GetItemText(pos, P_ST) == "GS" ? 1 : 0;
    }

    return 0;
}

/**************************************************************************/
/** CDPlanTagUpd **********************************************************/
/**************************************************************************/

/*** CDPlanTag-EVENT-POSITION *********************************************/

void CDPlanTagUpd::OnOK()
{
    UpdateData();

    int rc;
    if (m_CStringAuswahl == S_INSERT)
    {
        rc = MsgBoxYesNo(IDP_SOLL_NEUER_ANRUF, M_QUESTIONYES);
    }
    else
    {
        rc = MsgBoxYesNo(IDP_SOLL_ANRUF_AEND);
    }

    if (rc == IDYES)
    {
        CheckPrio(TRUE);
        SetAnrufArt();

        if (m_CStringAuswahl == S_INSERT && m_CBemerkung.IsEmpty())
        {
            m_CBemerkung = CResString::ex().getStrTblText(IDS_MANUAL);
            m_CEditBemerkung.SetWindowText(m_CBemerkung);
        }
        else if (m_CStringAuswahl == S_UPDATE && m_CBemerkung.IsEmpty())
        {
            m_CBemerkung = CResString::ex().getStrTblText(IDS_MANUAL_CHANGED);
            m_CEditBemerkung.SetWindowText(m_CBemerkung);
        }

        CDialogMultiLang::OnOK();
    }
    else
        OnCancel();
}

/*** CDPlanTag-ON-INIT-DIALOG *********************************************/

BOOL CDPlanTagUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    if (SelectKunde(atol(m_CIdfnr), m_sVzNr) == SRV_SQLNOTFOUND)
    {
        CDialogMultiLang::OnCancel();
        return IDCANCEL;
    }
    GetDlgItem(IDC_STATIC_AUSWAHL)->SetWindowText(m_CStringAuswahl);
    GetDlgItem(IDC_STATIC_ANRUFART)->SetWindowText(m_CAnrufart);
    GetDlgItem(IDC_STATIC_PRIO)->SetWindowText(m_CPrio);
    GetDlgItem(IDC_STATIC_IDFNR)->SetWindowText(m_CIdfnr);

    return TRUE;  // return TRUE unless you set the focus to a control
}

/*** CDPlanTag-ON-CHECK-RR ************************************************/

void CDPlanTagUpd::OnCheckRr()
{
    if (IsDlgButtonChecked(IDC_CHECK_RR))
    {
        m_EditRr_nr.EnableWindow();
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_RR_NR));
    }
    else
    {
        m_EditRr_nr.SetWindowText(" ");
        m_EditRr_nr.EnableWindow(FALSE);
    }
}


/*** CDPlanTagUpd-ON-RADIO-2 (PLUS) ***************************************/

void CDPlanTagUpd::OnRadio1()
{
    char time[6];

    m_EditAnrufzeit.GetWindowText(time, 6);
    AddMinute2Time(time, PLUS);
    m_EditAnrufzeit.SetWindowText(time);
}

/*** CDPlanTagUpd-ON-RADIO-2 (MINUS) **************************************/

void CDPlanTagUpd::OnRadio2()
{
    char time[6];

    m_EditAnrufzeit.GetWindowText(time, 6);
    AddMinute2Time(time, MINUS);
    m_EditAnrufzeit.SetWindowText(time);
}

/*** CDPlanTagUpd-ON-CHANGE-EDIT-ANRUF-ZEIT *******************************/

void CDPlanTagUpd::OnChangeEditAnrufzeit()
{
    TimeEditSetting(&m_EditAnrufzeit);
}

/*** CDPlanTagUpd-ON-CANCEL ***********************************************/

void CDPlanTagUpd::OnCancel()
{
    CDialogMultiLang::OnCancel();
}


/********* EIGENE FUNKTIONEN **********************************************/
/*** CDPlanTagUpd-EVENT-POSITION ******************************************/

int CDPlanTagUpd::SelectKunde(long lIdfNr, short sVzNr)
{
    CKNDINF kndinf;
    kndinf.s.IDFNR = lIdfNr;
    kndinf.s.KUNDENNR = lIdfNr;
    kndinf.s.VERTRIEBSZENTRUMNR = sVzNr;
    kndinf.Server(AakundeSel_knd_info); // schreibt TXT_KEIN_KUNDE_IDF "kein kunde mit dieser ...
    if (kndinf.rc != SRV_OK)
        return SRV_SQLNOTFOUND;

    AllgEntfSpaces(kndinf.s.NAMEAPO);
    AllgEntfSpaces(kndinf.s.NAMEINHABER);
    AllgEntfSpaces(kndinf.s.POSTLEITZAHL);
    AllgEntfSpaces(kndinf.s.ORT);
    AllgEntfSpaces(kndinf.s.TELNR);
    AllgEntfSpaces(kndinf.s.TELKURZWAHL);
    AllgEntfSpaces(kndinf.s.KZKDKLASSE);

    m_CStaticApo.SetWindowText(kndinf.s.NAMEAPO);
    m_CStaticName.SetWindowText(kndinf.s.NAMEINHABER);
    m_CStaticPlz.SetWindowText(kndinf.s.POSTLEITZAHL);
    m_CStaticOrt.SetWindowText(kndinf.s.ORT);
    m_CStaticTelnr.SetWindowText(kndinf.s.TELNR);
    m_CStaticKurzwahl.SetWindowText(kndinf.s.TELKURZWAHL);
    m_CStaticKndklasse.SetWindowText(kndinf.s.KZKDKLASSE);

    CString date = Date(ddmmyyyy);
    m_CStaticDatum.SetWindowText(date);

    if (m_CStringAuswahl == S_INSERT)
    {
        CString time = Time(HHMM);
        m_EditAnrufzeit.SetWindowText(time);
        m_CBrr.SetCheck(FALSE);
        m_CRadio10.SetCheck(TRUE);
        m_CRadioAnrufart.SetCheck(TRUE);
        m_EditRr_nr.EnableWindow();
        m_EditRr_nr.SetWindowText(kndinf.s.TELNR);
        m_EditRr_nr.EnableWindow(FALSE);
    }
    else
        SetRadioButton();

    return SRV_OK;
}

/*** CDPlanTagUpd-SET-RADIO-BUTTON ****************************************/

void CDPlanTagUpd::SetRadioButton()
{
    CString str;
    m_CStaticPrio.GetWindowText(str);

    if (str == "OR")
        m_CRadio10.SetCheck(TRUE);
    else if (str == "NS")
        CheckRadioButton(IDC_RADIO10, IDC_RADIO13, IDC_RADIO13);
    else if (str == "EI")
        CheckRadioButton(IDC_RADIO10, IDC_RADIO13, IDC_RADIO11);
    else if (str == "NV")
        CheckRadioButton(IDC_RADIO10, IDC_RADIO13, IDC_RADIO12);
    else if (str == "UB")
        m_CRadio10.SetCheck(TRUE);

    m_CStaticAnrufart.GetWindowText(str);
    if (str == P_PHONETISCH)
        m_CRadioAnrufart.SetCheck(TRUE);
    else if (str == P_PARALELL)
        CheckRadioButton(IDC_RADIO14, IDC_RADIO17, IDC_RADIO15);
    else if (str == P_SERIELL)
        CheckRadioButton(IDC_RADIO14, IDC_RADIO17, IDC_RADIO16);
    else if (str == P_MSERIELL)
        CheckRadioButton(IDC_RADIO14, IDC_RADIO17, IDC_RADIO17);
}

/*** CDPlanTag-ON-HOOK-FKT ************************************************/
/* Bearbeitung von Tastaturereignissen auf dem gesammten Dialog           */
/* (unabhängig vom ausgewählten Bedienelement)                            */
/**************************************************************************/

LRESULT CDPlanTagUpd::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (GetFocus() == GetDlgItem(IDC_EDIT_ANRUFZEIT))
    {
        int ch = (int)((LPMSG)lpMsg)->wParam;

        switch (ch)
        {
        case VK_PLUS:
        case NU_PLUS:
            OnRadio1();
            return 1L;
        case VK_MINUS:
        case NU_MINUS:
            OnRadio2();
            return 1L;
        default:
            break;
        }
    }
    return 0;
}

/*** CDPLANTAGUPD CHECK-PRIO **********************************************/

int CDPlanTagUpd::CheckPrio(BOOL bFromWindow)
{
    static int prio;

    if (!bFromWindow)
        return prio;

    switch (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO13))
    {
    case IDC_RADIO10:
        prio = P_NORMRUFZEIT;
        break;
    case IDC_RADIO11:
        prio = P_EILRUFZEIT;
        break;
    case IDC_RADIO12:
        prio = P_VORRUFZEIT;
        break;
    case IDC_RADIO13:
        prio = P_NACHRUFZEIT;
        break;
    default:
        break;
    }

    return prio;
}

/*** CDPLANTAGUPD SET-ANRUF-ART *******************************************/

void CDPlanTagUpd::SetAnrufArt()
{
    switch (GetCheckedRadioButton(IDC_RADIO14, IDC_RADIO16))
    {
    case IDC_RADIO14:
        m_CStaticAnrufart.SetWindowText(P_PHONETISCH);
        break;
    case IDC_RADIO15:
        m_CStaticAnrufart.SetWindowText(P_PARALELL);
        break;
    case IDC_RADIO16:
        m_CStaticAnrufart.SetWindowText(P_SERIELL);
        break;
    case IDC_RADIO17:
        m_CStaticAnrufart.SetWindowText(P_MSERIELL);
        break;
    default:
        break;
    }

    m_CStaticAnrufart.GetWindowText(m_CAnrufart);
}

void CDPlanTagUpd::OnEnChangeEditPool()
{
    AllgWertKontr(&m_CEditPool, MAXIMUM_POOLID);
}

/***************************************************************************/
/*** CDPLANTAGPRT **********************************************************/
/***************************************************************************/

/*** DDPlanTagPrt ON-INIT-DIALOG *******************************************/

BOOL CDPlanTagPrt::OnInitDialog()
{
    CRUFPTAGINF  rufinf;
    CDPlanTag    pLan;
    CStringArray output;

    COLUMNS_TYPES Fields[] = {
        F_KST,       CResString::ex().getStrTblText(AETXT_KB),       20, LVCFMT_LEFT,
        F_ZEIT,      CResString::ex().getStrTblText(IDS_TIME),       60, LVCFMT_CENTER,
        F_URZEIT,    CResString::ex().getStrTblText(IDS_URZEIT),     41, LVCFMT_CENTER,
        F_RUFZEIT,   CResString::ex().getStrTblText(IDS_CALLTIME),   50, LVCFMT_CENTER,
        F_STAT,      CResString::ex().getStrTblText(AETXT_SHORT_ST), 28, LVCFMT_LEFT,
        F_STAT_RUF,  CResString::ex().getStrTblText(AETXT_RUF),      36, LVCFMT_LEFT,
        F_STAT_VER,  CResString::ex().getStrTblText(AETXT_VER),      36, LVCFMT_LEFT,
        F_STAT_LOE,  CResString::ex().getStrTblText(AETXT_LOE),      36, LVCFMT_LEFT,
        F_UNAME,     CResString::ex().getStrTblText(IDS_ANWENDER),   60, LVCFMT_LEFT,
        F_BEMERKUNG, CResString::ex().getStrTblText(IDS_BEMERK),    400, LVCFMT_LEFT,
        -1,          "",                                              0, 0
    };

    SetWindowText(m_CDlgText);
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    if (!CListCtrlHelper::AddColumns(Fields, m_ListCtl))
    {
        return FALSE;
    }

    output.SetSize(NUM_COLUMNS(Fields));

    CString date = Date(yyyymmdd);
    rufinf.s.DATUM   = atol(date);
    rufinf.s.RUFZEIT = atol(m_CRufzeit);
    rufinf.s.IDFNR   = atol(m_CIdfnr);
    rufinf.s.FILIALNR = m_sVzNr;

    BeginWaitCursor();

    rufinf.rc = SRV_OK;
    rufinf.s.FETCH_REL = 1;
    rufinf.Server(AaplanSel_tag_plan_inf);

    int pos = 0;
    CLetterMan kb;
    while (rufinf.rc == SRV_OK)
    {
        output[F_KST] = kb.Next();
        output[F_ZEIT].Format("%s", AllgZeit2CharHHMMSS(rufinf.s.ZEIT));
        output[F_URZEIT].Format("%s", AllgZeit2CharHHMM(rufinf.s.RUFZEIT));
        output[F_RUFZEIT].Format("%s", AllgZeit2CharHHMM(rufinf.s.RUFZEITGEAENDERT));
        output[F_STAT].Format("%s", pLan.EventPosition(rufinf.s.STATUS));
        output[F_STAT_RUF].Format("%s", pLan.EventPosition(rufinf.s.STATUSANRUFSATZ));
        output[F_STAT_VER].Format("%s", Status(rufinf.s.STATUSVERBINDUNG, S_VER));
        output[F_STAT_LOE].Format("%s", Status(rufinf.s.LOESCHGRUND, S_LOE));
        output[F_UNAME].Format("%s", rufinf.s.USERNAME);
        output[F_BEMERKUNG].Format("%s", rufinf.s.BEMERKUNG);

        if (!CListCtrlHelper::GetAppendItem(m_ListCtl, NUM_COLUMNS(Fields), output, pos))
        {
            break;
        }

        rufinf.Server(AaplanSel_tag_plan_inf);
    }

    rufinf.s.FETCH_REL = 0;
    rufinf.Server(AaplanSel_tag_plan_inf);
    EndWaitCursor();

    if (pos > 0)
    {
        GotoDlgCtrl(GetDlgItem(IDC_LIST1));
        CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
    }

    SelectKunde(atol(m_CIdfnr), m_sVzNr);

    if (!GetAeUser().UpdEntsperr() || !m_iIsLocked)
    {
        GetDlgItem(IDC_BUTTON_ENTSPERREN)->EnableWindow(FALSE);
    }

    return TRUE;
}

/*** DDPlanTagPrt SELECT-KUNDE *********************************************/

int CDPlanTagPrt::SelectKunde(long IdfNr, short sVzNr)
{
    CKNDINF kndinf;
    kndinf.s.IDFNR = IdfNr;
    kndinf.s.KUNDENNR = IdfNr;
    kndinf.s.VERTRIEBSZENTRUMNR = sVzNr;
    kndinf.Server(AakundeSel_knd_info);
    if (kndinf.rc != SRV_OK)
        return SRV_SQLNOTFOUND;

    AllgEntfSpaces(kndinf.s.NAMEAPO);
    AllgEntfSpaces(kndinf.s.NAMEINHABER);
    AllgEntfSpaces(kndinf.s.POSTLEITZAHL);
    AllgEntfSpaces(kndinf.s.ORT);

    m_CStaticApo.SetWindowText(kndinf.s.NAMEAPO);
    m_CStaticName.SetWindowText(kndinf.s.NAMEINHABER);
    m_CStaticPlz.SetWindowText(kndinf.s.POSTLEITZAHL);
    m_CStaticOrt.SetWindowText(kndinf.s.ORT);

    CString date = Date(ddmmyyyy);
    m_CStaticDatum.SetWindowText(date);

    return SRV_OK;
}

/*** DDPlanTagPrt ON-BUTTON-ENTSPERREN *************************************/

void CDPlanTagPrt::OnButtonEntsperren()
{
    if (MsgBoxYesNo(IDP_SOLL_ENTSPERR) == IDYES)
    {
        CString date = Date(yyyymmdd);
        CRUFPTAG db;
        db.s.IDFNR   = atol(m_CIdfnr);
        db.s.FILIALNR = m_sVzNr;
        db.s.RUFZEIT = atol(m_CRufzeit);
        db.s.DATUM   = atol(date);

        if (CallServer(F_GETGRASP, &db) && !CallServer(F_UNSET, &db))
        {
            m_iIsLocked = 0;
            CDialogMultiLang::OnOK();
        }
    }
}

/*** DDPlanTagPrt ON-OK (SCHLIESSEN) ***************************************/

void CDPlanTagPrt::OnOK()
{
    CDialogMultiLang::OnCancel();
}

/***************************************************************************/
/*** CD-PLAN-TAG-LOE *******************************************************/
/***************************************************************************/

/*** CDPlanTagLoe ON-INIT-DIALOG *******************************************/

BOOL CDPlanTagLoe::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    m_CRadio10.SetCheck(TRUE);

    return TRUE;

}

/*** CDPlanTagLoe ON-OK ****************************************************/

void CDPlanTagLoe::OnOK()
{
    UpdateData();
    if (!CheckDeleteStat())
    {
        MsgBoxOK(IDS_NOTHING_SELECTED, MB_ICONINFORMATION);
        GetDlgItem(IDC_EDIT1)->SetFocus();
        return;
    }

    CDialogMultiLang::OnOK();
}



/*** CDPlanTagLoe CHECK-RADIO-BUTTON ***************************************/

int CDPlanTagLoe::CheckDeleteStat()
{
    int prio;

    switch (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14))
    {
    case IDC_RADIO10:
    default:
        prio = P_FREITEXT;
        break;
    case IDC_RADIO11:
        prio = P_FALSCHERUFNR;
        break;
    case IDC_RADIO12:
        prio = P_ERFOLGLOSERRUF;
        break;
    case IDC_RADIO13:
        prio = P_HEUTEKEINRUF;
        break;
    case IDC_RADIO14:
        prio = P_FALSCHERREINRUFZ;
        break;
    }

    if ((prio == P_FREITEXT) && m_CBemerkung.IsEmpty())
        prio = 0;

    m_iChoice = prio;
    return prio;
}

/*** CDPlanTagLoe ON-RADIO-10 **********************************************/

void CDPlanTagLoe::OnRadio10()
{
    if (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO10)
        CheckSetRadio();
}

/*** CDPlanTagLoe ON-RADIO-11 **********************************************/

void CDPlanTagLoe::OnRadio11()
{
    if (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO11)
        CheckSetRadio();
}

/*** CDPlanTagLoe ON-RADIO-12 **********************************************/

void CDPlanTagLoe::OnRadio12()
{
    if (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO12)
        CheckSetRadio();
}

/*** CDPlanTagLoe ON-RADIO-13 **********************************************/

void CDPlanTagLoe::OnRadio13()
{
    if (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO13)
        CheckSetRadio();
}

/*** CDPlanTagLoe ON-RADIO-14 **********************************************/

void CDPlanTagLoe::OnRadio14()
{
    if (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO14)
        CheckSetRadio();
}

/*** CDPlanTagVer CHECK-SET-RADIO ******************************************/

int CDPlanTagLoe::CheckSetRadio()
{
    int rc = 0;

    m_CEditBemerkung.EnableWindow(FALSE);

    switch (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14))
    {
    case IDC_RADIO10:
        m_CEditBemerkung.EnableWindow(TRUE);
        m_CEditBemerkung.SetWindowText("");
        m_CEditBemerkung.SetFocus();
        break;
    case IDC_RADIO11:
        m_CEditBemerkung.SetWindowText(CResString::ex().getStrTblText(IDS_CALL_WITHOUT_SUCCESS));
        break;
    case IDC_RADIO12:
        m_CEditBemerkung.SetWindowText(CResString::ex().getStrTblText(IDS_WRONG_NUMBER));
        break;
    case IDC_RADIO13:
        m_CEditBemerkung.SetWindowText(CResString::ex().getStrTblText(IDS_WRONG_CALL));
        break;
    case IDC_RADIO14:
        m_CEditBemerkung.SetWindowText(CResString::ex().getStrTblText(IDS_NO_CALL_TODAY));
        break;
    default:
        rc = 1;
        break;
    }

    return rc;
}

/***************************************************************************/
/*** CD-PLAN-TAG-RUF *******************************************************/
/***************************************************************************/

/*** CDPlanTagRuf ON-INIT-DIALOG *******************************************/

BOOL CDPlanTagRuf::OnInitDialog()
{
    CRUFPTAGSUM  rufptagsum;
    CRUFPTAGTOUR rufptagtour;
    char rufzeit[20];
    int adr = F_DELDPOINT;
    CString csTour;
    CString csAnrufart;

    CString date = Date(yyyymmdd);
    rufptagsum.s.DATUM = atol(date);
    rufptagsum.s.FILIALNR = m_sVzNr;
    rufptagsum.Server(AaplanSel_count);
    if (rufptagsum.rc == SRV_OK)
    {
        m_CZuerledigen.Format("%ld", rufptagsum.s.SUMMEOFFEN);
        m_CBearbeitet.Format("%ld", rufptagsum.s.SUMMEERLEDIGT);
        m_CGeloescht.Format("%ld", rufptagsum.s.SUMMEGELOESCHT);
    }

    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    rufptagtour.s.FETCH_REL = 1;
    rufptagtour.s.IDFNR = atol(m_CIdfnr);
    rufptagtour.s.VERTRIEBSZENTRUMNR = m_sVzNr;
    rufptagtour.s.DATUMKOMMI = atol(date);
    strcpy_s(rufptagtour.s.TOURID, Time(HHMMO).GetString());

    rufptagtour.Server(AaplanSel_tour);
    while (rufptagtour.rc == SRV_OK)
    {
        csTour.Format("%2.2s:%2.2s - %2s", rufptagtour.s.TOURID,
                                           rufptagtour.s.TOURID + 2,
                                           rufptagtour.s.TOURID + 4);
        m_CListTour.AddString(csTour);
        rufptagtour.Server(AaplanSel_tour);
    }
    /* close cursor */
    rufptagtour.s.FETCH_REL = 0;
    rufptagtour.Server(AaplanSel_tour);

    m_CListTour.SetCurSel(0);

    strcpy_s(rufzeit, m_CAktrufzeit.IsEmpty() ? m_CRufzeit : m_CAktrufzeit);
    DelDoublPoint(rufzeit, &adr);
    if (   (SelectKunde(atol(m_CIdfnr)) == SRV_SQLNOTFOUND)
        || (SelectAnruf(atol(m_CIdfnr), atol(rufzeit)) == SRV_SQLNOTFOUND) )
    {
        m_bNotFound = TRUE;
        CDialogMultiLang::OnCancel();
        return IDCANCEL;
    }


    m_CStaticAnrufart.GetWindowText(csAnrufart);
    if (csAnrufart == P_PARALELL)
    {
        SetDefID(IDC_PARAAUFTRAGOEFFNEN);
        GetDlgItem(IDC_PARAAUFTRAGOEFFNEN)->SetFocus();
    }
    GetDlgItem(IDC_STATIC_IDFNR)->SetWindowText(m_CIdfnr);

    return FALSE;  // return TRUE unless you set the focus to a control
}

/*** CDPlanTagRuf-ON-BUTTON-AENDERN ***************************************/

void CDPlanTagRuf::OnButtonAendern()
{
    CDPlanTagUpd plantagupd;
    CString rr;
    CString csSave;
    char szOldTime[6];

    plantagupd.m_CStringAuswahl = S_UPDATE;
    m_CStaticIdfnr.GetWindowText(plantagupd.m_CIdfnr);
    m_CStaticAktrufzeit.GetWindowText(plantagupd.m_CAnrufzeit);
    m_CStaticRrnr.GetWindowText(plantagupd.m_CEditrr_nr);
    m_CStaticRufart.GetWindowText(plantagupd.m_CPrio);
    m_CStaticBemerkung.GetWindowText(plantagupd.m_CBemerkung);
    csSave = plantagupd.m_CBemerkung;
    m_CStaticAnrufart.GetWindowText(plantagupd.m_CAnrufart);
    plantagupd.m_sVzNr = m_sVzNr;
    plantagupd.m_CPool = m_CPool;

    m_CStaticRr.GetWindowText(rr);
    plantagupd.m_CBoolRr = (rr == "J") ? TRUE : FALSE;

    strcpy_s(szOldTime, plantagupd.m_CAnrufzeit);
    int adr = F_DELDPOINT;
    DelDoublPoint(szOldTime, &adr);

    if (plantagupd.DoModal() == IDOK)
    {
        if (plantagupd.m_CBoolRr == TRUE)
        {
            m_CStaticRrnr.SetWindowText(plantagupd.m_CEditrr_nr);
            m_CStaticRr.SetWindowText("J");
        }

        m_CStaticAktrufzeit.SetWindowText(plantagupd.m_CAnrufzeit);
        m_CStaticRufart.SetWindowText(PrioPosition(plantagupd.CheckPrio()));
        if (plantagupd.m_CBemerkung == csSave)
            plantagupd.m_CBemerkung = CResString::ex().getStrTblText(IDS_MANUAL_CHANGED);
        m_CStaticBemerkung.SetWindowText(plantagupd.m_CBemerkung);
        m_CStaticAnrufart.SetWindowText(plantagupd.m_CAnrufart);

        UpdateData();
        if (UpdateServer(m_CAktrufzeit == m_CRufzeit ? ST_OB : ST_VS, plantagupd.CheckPrio(), szOldTime) == ST_VS)
            CDialogMultiLang::OnCancel(); // anruf wurde verschoben!
    }
}

/*** CDPlanTagRuf-ON-BUTTON-HISTORIE **************************************/

void CDPlanTagRuf::OnButtonHistorie()
{
    int adr = F_DELDPOINT;
    char buf[20];

    strcpy(buf, m_CRufzeit);
    DelDoublPoint(buf, &adr);

    CDPlanTagPrt plantagprt;
    plantagprt.m_CIdfnr = m_CIdfnr;
    plantagprt.m_sVzNr = m_sVzNr;
    plantagprt.m_CRufzeit = buf;
    plantagprt.DoModal();
}

/*** CDPlanTagRuf-ON-BUTTON-HINZUFUEGEN ***********************************/

void CDPlanTagRuf::OnButtonHinzufuegen()
{
    CDPlanTagUpd plantagupd;

    plantagupd.m_CStringAuswahl = S_INSERT;
    m_CStaticIdfnr.GetWindowText(plantagupd.m_CIdfnr);
    m_CStaticAktrufzeit.GetWindowText(plantagupd.m_CAnrufzeit);
    m_CStaticRrnr.GetWindowText(plantagupd.m_CEditrr_nr);
    m_CStaticRufart.GetWindowText(plantagupd.m_CPrio);
    m_CStaticBemerkung.GetWindowText(plantagupd.m_CBemerkung);
    plantagupd.m_CBoolRr = (m_CRr == "J") ? TRUE : FALSE;
    plantagupd.m_sVzNr = m_sVzNr;
    plantagupd.m_CPool = m_CPool;

    if (plantagupd.DoModal() == IDOK)
    {
        UpdateData();
        InsertServer(&plantagupd);
    }
}

/*** CDPlanTagRuf-ON-BUTTON-KEIN-AUFTRAG **********************************/

void CDPlanTagRuf::OnButtonKeinauftrag()
{

    if (   (MsgBoxYesNo(IDP_SOLL_DEL_SATZ) == IDYES)
        && (DeleteServer(ST_KA, 0, CResString::ex().getStrTblText(AETXT_KEIN_AUFTRAG)) == SRV_OK) )
    {
        CDialogMultiLang::OnCancel();
    }
}

/*** CDPlanTagRuf-ON-BUTTON-KNDINF ****************************************/

void CDPlanTagRuf::OnButtonKndinf()
{
    CKndInf kndinf;
    kndinf.SetIdfNr(atol(m_CIdfnr));
    kndinf.SetKndVz(m_sVzNr);
    kndinf.DoModal();
}

/*** CDPlanTagRuf-ON-BUTTON-KND-KONTAKT ***********************************/

void CDPlanTagRuf::OnButtonKndkontakt()
{
    CDKritik dlgKritik;
    dlgKritik.m_CIdf = m_CIdfnr;
    dlgKritik.SetKndVz(m_sVzNr);
    dlgKritik.DoModal();
}

/*** CDPlanTagRuf-ON-BUTTON-LÖSCHEN ***************************************/

void CDPlanTagRuf::OnButtonLoeschen()
{
    if (MsgBoxYesNo(IDP_SOLL_DEL_SATZ) == IDNO)
    {
        return;
    }

    CDPlanTagLoe del;
    if (del.DoModal() == IDCANCEL)
        return;

    if (del.m_CBemerkung.IsEmpty())
        del.m_CBemerkung = CResString::ex().getStrTblText(AETXT_MANUELL_LOESCH);
    if (DeleteServer(ST_LO, del.m_iChoice, del.m_CBemerkung) == SRV_OK)
        CDialogMultiLang::OnCancel();
}

/*** CDPlanTagRuf-ON-OK (Anrufen) *****************************************/

void CDPlanTagRuf::OnOK()
{
    int adr = F_DELDPOINT;

    char AktRufzeit[7];
    m_CStaticAktrufzeit.GetWindowText(AktRufzeit, 6);
    DelDoublPoint(AktRufzeit, &adr);

    char Rufzeit[7];
    m_CStaticRufzeit.GetWindowText(Rufzeit, 6);
    adr = F_DELDPOINT;
    DelDoublPoint(Rufzeit, &adr);

    long lTimeWarn = atol(AktRufzeit);
    long lTimeCurrent = GetServerTime();
    if (lTimeCurrent == 0)
    {
        lTimeCurrent = atol(AktRufzeit);
    }

    long lCallTime = atol(Rufzeit);
    if (lTimeWarn + 10 < lTimeCurrent)
    {
        CheckCallTime(lCallTime, lTimeCurrent, lTimeWarn, IDS_CALL_TOO_LATE);
    }
    else if (lCallTime + 10 < lTimeWarn)
    {
        CheckCallTime(lCallTime, lTimeWarn, lCallTime, IDS_CALL_DELAYED);
    }
    else if (lTimeWarn > lTimeCurrent + 10)
    {
        CheckCallTime(lCallTime, lTimeWarn, lTimeCurrent, IDS_CALL_EARLY);
    }
    else if (lTimeWarn + 10 < lCallTime)
    {
        CheckCallTime(lCallTime, lCallTime, lTimeWarn, IDS_CALL_EARLIER);
    }

    m_CStaticBemerkung.SetWindowText(CResString::ex().getStrTblText(IDS_NEW_ORDER)); // für historie
    if (UpdateServer(ST_EN, 0, AktRufzeit) < 0)        // Anruf erledigt
    {
        CDialogMultiLang::OnCancel();
        return;
    }

    CDialogMultiLang::OnOK();
}

void CDPlanTagRuf::CheckCallTime(long callTime, long timeLeft, long timeRight, UINT uiStringId)
{
    long lTimeErr = TimeCalculator(timeLeft, timeRight);
    CString csText;
    csText.Format(CResString::ex().getStrTblText(uiStringId), lTimeErr);
    ShowRecord(callTime, (LPCTSTR)csText);
}

/*** CDPlanTagRuf-ON-OK (Anrufen) *****************************************/

void CDPlanTagRuf::ShowRecord(long lUrzeit, const char* spText)
{
    CDPlanTagPrt plantagprt;
    plantagprt.m_CIdfnr = m_CIdfnr;
    plantagprt.m_sVzNr = m_sVzNr;
    plantagprt.m_CRufzeit.Format("%ld", lUrzeit);
    plantagprt.m_iIsLocked = false;
    plantagprt.m_CDlgText = spText;
    plantagprt.DoModal();
}


/*** CDPlanTagRuf-ON-OK (Anrufen) *****************************************/

long CDPlanTagRuf::GetServerTime()
{
    CTM  cServerTime;
    long lTime = 0;

    cServerTime.Server(AafilGetdatetime);
    if (cServerTime.rc == SRV_OK)
    {
        char szConvert[7];
        int adr = F_DELDPOINT;

        ppGTimeLongToCharHHMM(cServerTime.s.ZEIT, szConvert);
        DelDoublPoint(szConvert, &adr);
        lTime = atol(szConvert);
    }
    return lTime;
}

/*** CDPlanTagRuf-ONPARAAUFTRAGOEFFNEN ************************************/

void CDPlanTagRuf::OnParaauftragoeffnen()
{
    if (((CAeFView*)AeGetApp()->m_pViewEing)->OpenParaOrder(atol(m_CIdfnr), m_sVzNr))
    {
        UpdateServer(ST_EN, 0, "");   // Anruf erledigt
        CDialogMultiLang::OnCancel();
    }
}

/*** CDPlanTagRuf-DELETE-SERVER *******************************************/

int CDPlanTagRuf::DeleteServer(int Stat, int delStat, CString Bemerkung)
{
    CRUFPTAG rufptag;
    int adr = F_DELDPOINT;
    char rufzeit[7];

    CString date = Date(yyyymmdd);
    m_CStaticAktrufzeit.GetWindowText(rufzeit, 6);
    DelDoublPoint(rufzeit, &adr);

    rufptag.s.DATUM   = atol(date);
    rufptag.s.IDFNR   = atol(m_CIdfnr);
    rufptag.s.FILIALNR = m_sVzNr;
    rufptag.s.RUFZEIT = atol(rufzeit);
    rufptag.s.STATUS  = 99;     /* Abfrage mit Sperre */

    if (CallServer(F_SELWITHSET, &rufptag) == SRV_SQLNOTFOUND)
    {
        MsgBoxOK(IDS_ERR_FATAL);
        return ERROR;
    }

    m_CStaticAktrufzeit.GetWindowText(rufzeit, 6);
    adr = F_DELDPOINT;
    DelDoublPoint(rufzeit, &adr);
    rufptag.s.RUFZEITGEAENDERT = atol(rufzeit);
    rufptag.s.STATUS = static_cast<short>(Stat);          // LO-geloescht!
    rufptag.s.STATUSVERBINDUNG = 0;
    ++rufptag.s.LFDAKTION;
    rufptag.s.LOESCHGRUND = static_cast<short>(delStat);
    rufptag.s.UID = (long)GetAeUser().GetUID();
    strcpy(rufptag.s.BEMERKUNG, Bemerkung);

    rufptag.s.FETCH_REL = 0;
    if (CallServer(F_UPDATE, &rufptag) != SRV_OK)
        return ERROR;

    return SRV_OK;
}

/*** CDPlanTagRuf-UPDATE-SERVER *******************************************/

int CDPlanTagRuf::UpdateServer(int Stat, int Prio, CString csOldTime)
{
    CRUFPTAG rufptag;
    CString  rr = "";
    CString  Bemerkung;
    int adr = F_DELDPOINT;
    char rufzeit[7];

    CString date = Date(yyyymmdd);
    m_CStaticRufzeit.GetWindowText(rufzeit, 6);
    DelDoublPoint(rufzeit, &adr);

    if (csOldTime.IsEmpty())
        csOldTime = "2400";
    rufptag.s.DATUM   = atol(date);
    rufptag.s.IDFNR   = atol(m_CIdfnr);
    rufptag.s.FILIALNR = m_sVzNr;
    rufptag.s.RUFZEIT = atol(csOldTime) < atol(rufzeit) ? atol(csOldTime) : atol(rufzeit);
    rufptag.s.STATUS  = 99;         /* Abfrage mit Sperre */

    if (CallServer(F_SELWITHSET, &rufptag) == SRV_SQLNOTFOUND)
    {
        MsgBoxOK(IDS_ERR_FATAL);
        return ERROR;
    }

    m_CStaticAktrufzeit.GetWindowText(rufzeit, 6);
    adr = F_DELDPOINT;
    DelDoublPoint(rufzeit, &adr);
    rufptag.s.RUFZEITGEAENDERT = atol(rufzeit);
    rufptag.s.STATUS = static_cast<short>(Stat);          // LO-geloescht!
    rufptag.s.PRIORITAET = static_cast<short>(Prio);

    if (rufptag.s.STATUSVERBINDUNG < 0)
    {
        rufptag.s.STATUSVERBINDUNG = 0;
    }
    ++rufptag.s.LFDAKTION;
    rufptag.s.LOESCHGRUND = 0;

    m_CStaticRr.GetWindowText(rr);
    rufptag.s.STAGRUECKRUF[0] = (rr == "J") ? '1' : '0';
    m_CStaticRrnr.GetWindowText(rufptag.s.TELRUECKRUFNR, sizeof(rufptag.s.TELRUECKRUFNR));

    rufptag.s.UID = (long)GetAeUser().GetUID();
    m_CStaticBemerkung.GetWindowText(Bemerkung);
    strcpy(rufptag.s.BEMERKUNG, Bemerkung);
    m_CStaticAnrufart.GetWindowText(rufptag.s.ANRUFART, sizeof(rufptag.s.ANRUFART));

    rufptag.s.FETCH_REL = 1;
    if (CallServer(F_UPDATE, &rufptag) != SRV_OK)
        return ERROR;

    return Stat;
}

/*** CDPlanTagRuf-INSERT-SERVER *******************************************/

int CDPlanTagRuf::InsertServer(CDPlanTagUpd* d)
{
    CRUFPTAG rufptag;
    CString  rr;
    CString  Bemerkung;
    int adr = F_DELDPOINT;
    char rufzeit[7];

    CString date = Date(yyyymmdd);
    strcpy(rufzeit, d->m_CAnrufzeit);
    DelDoublPoint(rufzeit, &adr);

    rufptag.s.DATUM   = atol(date);
    rufptag.s.IDFNR   = atol(m_CIdfnr);
    rufptag.s.FILIALNR = m_sVzNr;
    rufptag.s.RUFZEIT = atol(rufzeit);
    rufptag.s.LFDAKTION = 1;
    rufptag.s.POOLID = 0;
    rufptag.s.LOESCHGRUND = 0;
    rufptag.s.RUFZEITGEAENDERT = atol(rufzeit);   // wegen eindeutiger abfrage beim lesenden zugriff!
    rufptag.s.STATUSVERBINDUNG = 0;
    rufptag.s.STATUS = ST_OB;
    rufptag.s.PRIORITAET = static_cast<short>(d->CheckPrio());
    strcpy(rufptag.s.MANUELL, "M");
    strcpy(rufptag.s.STAGRUECKRUF, d->m_CBoolRr == TRUE ? "1" : "0");
    strcpy(rufptag.s.TELRUECKRUFNR, d->m_CBoolRr == TRUE ? d->m_CEditrr_nr : " ");
    if (d->m_CBemerkung.IsEmpty())
        strcpy(rufptag.s.BEMERKUNG, (char*)CResString::ex().getStrTblText(IDS_MANUAL).GetString());
    else
        strcpy(rufptag.s.BEMERKUNG, d->m_CBemerkung);
    strcpy(rufptag.s.ANRUFART, d->m_CAnrufart);
    rufptag.s.UID = (long)GetAeUser().GetUID();

    int rc = CallServer(F_INSERT, &rufptag);
    if (rc < SRV_OK)
    {
        EndWaitCursor();
        return ERROR;
    }
    else if (rc == SRV_SQLNOTFOUND)
        MsgBoxOK(IDP_DOPPELT);

    return SRV_OK;
}

/*** CDPlanTagRuf-ON-BUTTON-AUFTRAG-VERSCHIEBEN ***************************/

void CDPlanTagRuf::OnButtonAuftragverschieben()
{
    CDPlanTagVer dlgPlanTagVer;
    m_CStaticAktrufzeit.GetWindowText(dlgPlanTagVer.m_CAktanrufzeit);
    m_CStaticRufzeit.GetWindowText(dlgPlanTagVer.m_CRufzeit);
    m_CStaticIdfnr.GetWindowText(dlgPlanTagVer.m_CIdfnr);
    dlgPlanTagVer.m_sVzNr = m_sVzNr;
    if (dlgPlanTagVer.DoModal() == IDOK)
    {
        CDialogMultiLang::OnCancel();
        //CDialogMultiLang::EndDialog( TRUE );
    }
}

/*** CDPlanTagRuf-SELECT-KUNDE ********************************************/

int CDPlanTagRuf::SelectKunde(long IdfNr)
{
    CKNDINF kndinf;
    kndinf.s.IDFNR = IdfNr;
    kndinf.s.VERTRIEBSZENTRUMNR = m_sVzNr;
    kndinf.s.KUNDENNR = IdfNr;
    kndinf.Server(AakundeSel_knd_info);
    if (kndinf.rc != SRV_OK)
        return SRV_SQLNOTFOUND;

    AllgEntfSpaces(kndinf.s.NAMEAPO);
    AllgEntfSpaces(kndinf.s.NAMEINHABER);
    AllgEntfSpaces(kndinf.s.POSTLEITZAHL);
    AllgEntfSpaces(kndinf.s.ORT);
    AllgEntfSpaces(kndinf.s.TELNR);
    AllgEntfSpaces(kndinf.s.TELKURZWAHL);
    AllgEntfSpaces(kndinf.s.KZKDKLASSE);

    m_CStaticApo.SetWindowText(kndinf.s.NAMEAPO);
    m_CStaticName.SetWindowText(kndinf.s.NAMEINHABER);
    m_CStaticPlz.SetWindowText(kndinf.s.POSTLEITZAHL);
    m_CStaticOrt.SetWindowText(kndinf.s.ORT);
    m_CStaticTelnr.SetWindowText(kndinf.s.TELNR);
    m_CStaticKurzwahl.SetWindowText(kndinf.s.TELKURZWAHL);
    m_CStaticKndklasse.SetWindowText(kndinf.s.KZKDKLASSE);

    CString date = Date(ddmmyyyy);
    m_CStaticDatum.SetWindowText(date);

    SetTime(&m_CStaticZeit, HHMMSS);
    //Time(time, HHMMSS);
    //m_CStaticZeit.SetWindowText(time);

    return SRV_OK;
}

/*** CDPlanTagRuf-SELECT-KUNDE ********************************************/

int CDPlanTagRuf::SelectAnruf(long IdfNr, long RufZeit)
{
    CString date = Date(yyyymmdd);

    CRUFPTAG rufptag;
    rufptag.s.DATUM   = atol(date);
    rufptag.s.IDFNR   = IdfNr;
    rufptag.s.RUFZEIT = RufZeit;
    rufptag.s.FILIALNR = m_sVzNr;
    rufptag.s.STATUS  = 99;     /* Abfrage mit Sperre */

    if ((CallServer(F_SELWITHSET, &rufptag) == SRV_SQLNOTFOUND) && (CallServer(F_SELWITHSET, &rufptag) == SRV_SQLNOTFOUND))
    {
        MsgBoxOK(IDS_NO_CALL);
        return SRV_SQLNOTFOUND;
    }

    SetRufPlanData(&rufptag);

    return SRV_OK;
}

/*** CDPlanTagRuf-SET-RUF-PLAN-DATA ***************************************/

void CDPlanTagRuf::SetRufPlanData(CRUFPTAG* d)
{
    m_CStaticAnrufart.SetWindowText(d->s.ANRUFART);
    m_CStaticRufart.SetWindowText(PrioPosition(d->s.PRIORITAET));
    m_CStaticPrio.SetWindowText(Text(m_CRufart));
    m_CStaticRr.SetWindowText(d->s.STAGRUECKRUF[0] == '0' ? "N" : "J");
    m_CStaticRrnr.SetWindowText(m_CRr == "J" ? d->s.TELRUECKRUFNR : " ");
    m_CStaticRufzeit.SetWindowText(AllgZeit2CharHHMM(d->s.RUFZEIT));
    m_CStaticAktrufzeit.SetWindowText(AllgZeit2CharHHMM(d->s.RUFZEITGEAENDERT == 0 ? d->s.RUFZEIT : d->s.RUFZEITGEAENDERT));

    AllgEntfSpaces(d->s.BEMERKUNG);
    m_CStaticBemerkung.SetWindowText(d->s.BEMERKUNG);
}

/*** CDPlanTag-ON-HOOK-FKT ************************************************/
/* Bearbeitung von Tastaturereignissen auf dem gesammten Dialog           */
/* (unabhängig vom ausgewählten Bedienelement)                            */
/**************************************************************************/

LRESULT CDPlanTagRuf::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        CKndInf dlgKndInf;
        dlgKndInf.SetIdfNr(atol(m_CIdfnr));
        dlgKndInf.SetKndVz(m_sVzNr);
        dlgKndInf.DoModal();
        return 1L;
    }

    return 0L;
}

/***************************************************************************/
/*** CD-PLAN-TAG-VER *******************************************************/
/***************************************************************************/

/*** CDPlanTagVer ON-INIT-DIALOG *******************************************/

BOOL CDPlanTagVer::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    m_scAktrufzeit = m_CAktanrufzeit;
    SetTimeToNewTime(MAX_TIME_MOVE);
    CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO11);
    CheckSetRadio(); // aktuelle Rufzeit vorab +2 min !!!!

    GetDlgItem(IDC_STATIC_IDFNR)->SetWindowText(m_CIdfnr);
    return TRUE;
}

/*** CDPlanTagVer ON-OK ****************************************************/

void CDPlanTagVer::OnOK()
{
    UpdateData();

    if (m_CBemerkung.IsEmpty())
    {
        MsgBoxOK(IDS_NO_ENTRY, MB_ICONINFORMATION);
        m_CEditBemerkung.SetFocus();
        return;
    }

    int iMin = CheckMaxTimeMovement();
    if ((iMin > L_MAX_TIME_MOVE) && (MsgBoxYesNo(IDP_SOLL_VERSCHIEBEN) == IDNO))
    {
        GetDlgItem(IDC_EDIT_NEUERUFZEIT)->SetFocus();
        return;
    }

    if (iMin > 0)
    {
        char szTime[7];
        m_CEditNeuerufzeit.GetWindowText(szTime, 6);
        m_CStaticAktanrufzeit.SetWindowText(szTime);
    }

    char szOldTime[7];
    strcpy(szOldTime, m_scAktrufzeit);
    int adr = F_DELDPOINT;
    DelDoublPoint(szOldTime, &adr);

    UpdateServer(szOldTime);
    CDialogMultiLang::OnOK();
}

/*** CDPlanTagVer CHECK-MAX-TIME-MOVEMENT **********************************/

int CDPlanTagVer::CheckMaxTimeMovement()
{
    char szTimenew[10];
    char szTimeold[10];
    int  iDblp = F_DELDPOINT;
    int iNew;
    int iOld;

    if (m_CNeuerufzeit.IsEmpty())
        return 0;

    m_CEditNeuerufzeit.GetWindowText(szTimenew, 6);
    m_CStaticAktanrufzeit.GetWindowText(szTimeold, 6);
    DelDoublPoint(szTimeold, &iDblp);
    iDblp = F_DELDPOINT;
    DelDoublPoint(szTimenew, &iDblp);

    iNew = (((atoi(szTimenew) / 100) % 100) * 60) + atoi(szTimenew) % 100;
    iOld = (((atoi(szTimeold) / 100) % 100) * 60) + atoi(szTimeold) % 100;

    return (iNew - iOld);
}

/*** CDPlanTagVer ON-CHANGE-EDIT-NEUERUFZEIT *******************************/

void CDPlanTagVer::OnChangeEditNeuerufzeit()
{
    TimeEditSetting(&m_CEditNeuerufzeit); // maximal 15 minuten verschieben!!!!!!!!!!!!!!!!!!!!!
}

/*** CDPlanTagVer ON-RADIO-10 **********************************************/

void CDPlanTagVer::OnRadio10()
{
    if (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO10)
        CheckSetRadio();
}

/*** CDPlanTagVer ON-RADIO-10 **********************************************/

void CDPlanTagVer::OnRadio11()
{
    if (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO11)
        CheckSetRadio();
}

/*** CDPlanTagVer ON-RADIO-10 **********************************************/

void CDPlanTagVer::OnRadio12()
{
    if (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO12)
        CheckSetRadio();
}

/*** CDPlanTagVer ON-RADIO-10 **********************************************/

void CDPlanTagVer::OnRadio13()
{
    if (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO13)
        CheckSetRadio();
}

/*** CDPlanTagVer ON-RADIO-10 **********************************************/

void CDPlanTagVer::OnRadio14()
{
    if (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO14)
        CheckSetRadio();
}

/*** CDPlanTagVer NO-RADIO-SET *********************************************/

int CDPlanTagVer::NoRadioSet()
{
    return (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14) == IDC_RADIO10) ? 1 : 0;
}

/*** CDPlanTagVer SET-TIME-TO-NEW-TIME *************************************/

int CDPlanTagVer::SetTimeToNewTime(int iMin)
{
    char time[7];

    m_CStaticAktanrufzeit.GetWindowText(time, 6);
    AddMinute(time, PLUS, iMin);
    m_CStaticAktanrufzeit.SetWindowText(time);

    return iMin;
}

/*** CDPlanTagVer CHECK-SET-RADIO ******************************************/

int CDPlanTagVer::CheckSetRadio()
{
    int rc = 1;

    m_CEditBemerkung.EnableWindow(FALSE);
    switch (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14))
    {
    case IDC_RADIO10:
        m_CEditBemerkung.EnableWindow(TRUE);
        m_CEditBemerkung.SetWindowText("");
        m_CEditBemerkung.SetFocus();
        break;
    case IDC_RADIO11:
        m_CEditBemerkung.SetWindowText(CResString::ex().getStrTblText(IDS_NO_CURR_PHARM));
        break;
    case IDC_RADIO12:
        m_CEditBemerkung.SetWindowText(CResString::ex().getStrTblText(IDS_NO_ANSWER));
        break;
    case IDC_RADIO13:
        m_CEditBemerkung.SetWindowText(CResString::ex().getStrTblText(IDS_NO_CURR_TEL));
        break;
    case IDC_RADIO14:
        m_CEditBemerkung.SetWindowText(CResString::ex().getStrTblText(IDS_NO_ANSWER_TEL));
        break;
    default:
        rc = 0;
        break;
    }

    return rc;
}

/*** CDPlanTagVer GET-STATUS-VERBINDUNG ************************************/

int CDPlanTagVer::GetStatusVerbindung()
{
    int rc;

    switch (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO14))
    {
    case IDC_RADIO10: rc = 0; break;
    case IDC_RADIO11: rc = 2; break;
    case IDC_RADIO12: rc = 3; break;
    case IDC_RADIO13: rc = 4; break;
    case IDC_RADIO14: rc = 5; break;
    default: rc = 0;
    }

    return rc;
}

/*** CDPlanTagVer CHECK-SET-RADIO ******************************************/

int CDPlanTagVer::UpdateServer(CString csOldTime)
{
    int adr = F_DELDPOINT;
    char rufzeit[7];

    CString date = Date(yyyymmdd);
    m_CStaticRufzeit.GetWindowText(rufzeit, 6);
    DelDoublPoint(rufzeit, &adr);

    CRUFPTAG rufptag;
    rufptag.s.DATUM   = atol(date);
    rufptag.s.IDFNR   = atol(m_CIdfnr);
    rufptag.s.FILIALNR = m_sVzNr;
    rufptag.s.RUFZEIT = atol(csOldTime) < atol(rufzeit) ? atol(csOldTime) : atol(rufzeit);
    rufptag.s.STATUS  = 99;     /* Abfrage mit Sperre */

    if (CallServer(F_SELWITHSET, &rufptag) == SRV_SQLNOTFOUND)
    {
        MsgBoxOK(IDS_ERR_FATAL);
        return ERROR;
    }

    m_CStaticAktanrufzeit.GetWindowText(rufzeit, 6);
    adr = F_DELDPOINT;
    DelDoublPoint(rufzeit, &adr);
    rufptag.s.RUFZEITGEAENDERT = atol(rufzeit);
    rufptag.s.STATUS = ST_VS;   // VS-verschoben!
    rufptag.s.STATUSVERBINDUNG = static_cast<short>(GetStatusVerbindung());
    ++rufptag.s.LFDAKTION;
    rufptag.s.LOESCHGRUND = 0;
    rufptag.s.UID = (long)GetAeUser().GetUID();
    m_CEditBemerkung.GetWindowText(rufptag.s.BEMERKUNG, sizeof(rufptag.s.BEMERKUNG));

    rufptag.s.FETCH_REL = 1;
    if (CallServer(F_UPDATE, &rufptag) != SRV_OK)
        return ERROR;

    return SRV_OK;
}

/**************************************************************************/
/*** ALLGEMEIN ************************************************************/
/**************************************************************************/

/*** SET-TIME *************************************************************/

static void SetTime(CStatic* settime, int setting)
{
    CString time = Time(setting);
    settime->SetWindowText(time);
}

/*** TIME *****************************************************************/

static CString Time(int format)
{
    char *frm;

    switch (format)
    {
    case HHMMSS: frm = "%02d:%02d:%02d"; break;
    case HHMM  : frm = "%02d:%02d"; break;
    case MMSS  : frm = "%0s%02d:%02d"; break;
    case HH    : frm = "%02d"; break;
    case MM    : frm = "%0s%02d"; break;
    case SS    : frm = "%0s%0s%02d"; break;
    case HHMMO : frm = "%02d%02d"; break;
    default    : return "";
    }

    CString time;
    CTime t = CTime::GetCurrentTime();
    CTM cServerTime;
    cServerTime.Server(AafilGetdatetime);
    if (cServerTime.rc != SRV_OK)
    {
        time.Format(frm, t.GetHour(), t.GetMinute(), t.GetSecond());
    }
    else
    {
        time.Format(frm, cServerTime.s.ZEIT / 10000,
                         cServerTime.s.ZEIT / 100 % 100,
                         cServerTime.s.ZEIT % 100);
    }

    return time;
}

/*** DATE *****************************************************************/

static CString& Date(CString& date, int format)
{
    int  rc = 0;
    int  iDay;
    int  iMonth;
    int  iYear;
    char *frm;
    static long lDate = 0;


    if (format == SET_DATE)
    {
        lDate = atol(date);
        if ((lDate < 1011990) || (lDate > 31130000))
            lDate = 0;
        return date;
    }

    switch (format)
    {
    case yyyymmdd: frm = "%04d%02d%02d"; rc = 1; break;
    case ddmmyyyy: frm = "%02d.%02d.%04d"; break;
    case ddmmyy  : frm = "%02d.%02d.%02d"; break;
    case ddmm    : frm = "%02d.%02d"; break;
    case dd      : frm = "%02d"; break;
    case mm      : frm = "%0s%02d"; break;
    case yy      : frm = "%0s%0s%02d"; break;
    default      : return date;
    }

    CTM cServerTime;
    cServerTime.Server(AafilGetdatetime);
    CTime t = CTime::GetCurrentTime();

    if (lDate != 0L)   // not the current date
    {
        iDay   = lDate / 1000000;
        iMonth = lDate / 10000 % 100;
        iYear  = lDate % 10000;
    }
    else if (cServerTime.rc != SRV_OK) //only if server doesn't work
    {
        iDay   = t.GetDay();
        iMonth = t.GetMonth();
        iYear  = t.GetYear();
    }
    else //here we get the current server-date!!!!!
    {
        iDay   = cServerTime.s.DATUM % 100;
        iMonth = cServerTime.s.DATUM / 100 % 100;
        iYear  = cServerTime.s.DATUM / 10000;
    }

    if (rc != 0)
        date.Format(frm, iYear, iMonth, iDay);
    else
        date.Format(frm, iDay, iMonth, iYear);

    return date;
}

static CString Date(int format)
{
    CString date;
    return Date(date, format);
}

/*** ADD-MINUTE ************************************************************/

static void AddMinute(char* time, int skip, int min)
{
    for (int i = 0; i < min; i++)
        AddMinute2Time(time, skip);
}

/*** ADD-MINUTE-2-TIME *****************************************************/

static void AddMinute2Time(char* time, int skip)
{
    AllgEntfSpaces(time);
    if (time[2] != ':')
    {
        MsgBoxOK(time);
        return;
    }

    int hour = atoi(time);
    int min = atoi(time + 3);

    switch (skip)
    {
    case PLUS:
        if (++min > 59)
        {
            min = 0;
            if (++hour > 23)
                hour = 0;
        }
        break;
    case MINUS:
        if (--min < 0)
        {
            min = 59;
            if (--hour < 0)
                hour = 23;
        }
        break;
    }

    sprintf(time, "%02d:%02d", hour, min);
}

/*** DEL-DOUBLE-POINT ******************************************************/

static void DelDoublPoint(char* str, int* adr)
{
    if (*adr == F_DELDPOINT)
    {
        AllgEntfSpaces(str);
        int len = (int)strlen(str);
        for (int i = 0; i < len; i++)
        {
            if (str[i] == ':')
            {
                *adr = i;
                break;
            }
        }

        if (*adr == F_DELDPOINT)
            return;

        int i;
        for (i = *adr; str[i] != '\0'; i++)
            str[i] = str[i + 1];
        str[i - 1] = '\0';
    }
    else
    {
        int len = (int)strlen(str);
        str[len + 1] = '\0';
        for (int i = len; i > *adr; i--)
            str[i] = str[i - 1];
        str[*adr] = ':';
    }
}

/*** CHECK-STR-2-CHAR ******************************************************/

static int CheckStr2Char(char* str, int ch)
{
    int len = (int)strlen(str);
    for (int i = 0; len < len; i++)
        if (str[i] == ch)
            return 1;

    return 0;
}

/*** CHECK-STR-2-CHAR ******************************************************/

static int CheckStr2Num(char* str)
{
    int len = (int)strlen(str);
    for (int i = 0; i < len; i++)
        if ((str[i] < '0' || str[i] > '9') && str[i] != ':')
            return 0;

    return 1;
}


/*** TIME-EDIT-SETTING *****************************************************/

static void TimeEditSetting(CEdit* edit)
{
    char time[10];
    edit->GetWindowText(time, 9);
    AllgEntfSpaces(time);
    if (CheckStr2Char(time, ':'))
        return;
    if (!CheckStr2Num(time))
    {
        edit->SetWindowText("");
        edit->SetFocus();
        return;
    }
    if (strlen(time) > 5)
    {
        time[1] = '\0';
        edit->SetWindowText(time);
        edit->SetFocus();
        edit->SetSel(1, 1);
        return;
    }
    if (strlen(time) == 4)
    {
        int ptr = 2;
        DelDoublPoint(time, &ptr);
        edit->SetWindowText(time);
    }
}

/*** TIME-EDIT-SETTING *****************************************************/

static int CallServer(int skip, CRUFPTAG* d)
{
    //CCmdTarget curs;
    int rc;

    AfxGetApp()->DoWaitCursor(1); // 1->>display the hourglass cursor
    d->s.REGIONNR = AeGetApp()->VzNr();

    if (skip == F_INSERT)
    {
        d->Server(AaplanIns_tag_plan);
        rc = d->rc;
    }
    else if (skip == F_UPDATE)
    {
        d->Server(AaplanUpd_tag_plan);
        rc = d->rc;
    }
    else if (skip == F_GETGRASP)
    {
        d->Server(AaplanUni_tag_plan);
        rc = d->rc;
    }
    else if (skip == F_SETGRASP)
    {
        d->s.FETCH_REL = F_SETGRASP;
        d->Server(AaplanUpd_tag_plan);
        rc = d->rc;
    }
    else if (skip == F_UNSET)
    {
        d->s.FETCH_REL = F_UNSET;
        d->Server(AaplanUpd_tag_plan);
        rc = d->rc;
    }
    else if (skip == F_SELWITHSET)
    {
        d->s.FETCH_REL = 1;
        d->Server(AaplanSel_tag_plan);
        rc = d->rc;  // wegen notfound!
        d->s.FETCH_REL = 0;
        d->Server(AaplanSel_tag_plan);
    }
    else if (skip == F_SELECT)
    {
        d->Server(AaplanSel_tag_plan);
        rc = d->rc;  // wegen notfound!
    }
    else if (skip == F_SELFIRST)
    {
        d->s.FETCH_REL = 1;
        d->s.UID = 1;
        d->Server(AaplanSel_tag_plan);
        rc = d->rc;  // wegen notfound!
    }
    else if (skip == F_SELNEXT)
    {
        d->s.FETCH_REL = 1;
        d->Server(AaplanSel_tag_plan);
        rc = d->rc;  // wegen notfound!
    }
    else if (skip == F_SELPREVIOUS)
    {
        d->s.FETCH_REL--;
        d->Server(AaplanSel_tag_plan);
        rc = d->rc;  // wegen notfound!
    }
    else if (skip == F_SELCLOSE)
    {
        d->s.FETCH_REL = 0;
        d->Server(AaplanSel_tag_plan);
        rc = d->rc;  // wegen notfound!
    }
    else
        rc = 1;

    AfxGetApp()->DoWaitCursor(-1); // 1->>display the hourglass cursor

    return rc;
}

/*** TIME-EDIT-SETTING *****************************************************/

static CString Status(int skip, int choice)
{
    if (choice == S_VER)
    {
        switch (skip)
        {
        case 0:
        default:
            return "KS";
        case 1:
            return "AG";
        case 2:
            return "AB";
        case 3:
            return "AN";
        case 4:
            return "PB";
        case 5:
            return "PN";
        }
    }

    if (choice == S_LOE)
    {
        switch (skip)
        {
        case  0:
        default:
            return "KS";
        case  1:
            return "FR";
        case  2:
            return "ER";
        case  3:
            return "KR";
        case 99:
            return "FZ";
        }
    }

    return "??";
}

/*** TIME-CALCULATOR *******************************************************/

static long TimeCalculator(long t1, long t2, short sType)
{
    if (sType == 0)
    {
        return ((((t1/100)%100)*60)+(t1%100)) - ((((t2/100)%100)*60)+(t2%100));
    }
    if (sType == 1)
    {
        return ((((t1/100)%100)*60)+(t1%100)) + ((((t2/100)%100)*60)+(t2%100));
    }
    return 0;
}

/*** TEXT ******************************************************************/

static CString Text(CString prio)
{
    if (prio == "EI")
        return "Eilauftrag";
    if (prio == "NS")
        return CResString::ex().getStrTblText(AETXT_RUF_NICHT_NACH);
    if (prio == "OR")
        return CResString::ex().getStrTblText(AETXT_RUF_PUENKTLICH);
    if (prio == "NV")
        return CResString::ex().getStrTblText(AETXT_RUF_NICHT_VOR);

    return CResString::ex().getStrTblText(AETXT_RUF_OHNE);
}

/*** PRIO-POSITION *********************************************************/

static CString PrioPosition(int stat)
{
    switch (stat)
    {
    case  P_EILRUFZEIT:
        return "EI\0";
    case  P_NACHRUFZEIT:
        return "NS\0";
    case  P_NORMRUFZEIT:
        return "OR\0";
    case  P_VORRUFZEIT:
        return "NV\0";
    default:
        return "UB\0";
    }
}


/***************************************************************************/
/*** SCHNITTSTELLE ZUM TAGESANRUFPLAN **************************************/
/***************************************************************************/

/***GetNextPhopneCall-GET-NEXT-CALL ****************************************/

long GetNextPhoneCall::GetNextCall(long date)
{
    CRUFPTAG     rufptag;
    CDPlanTagRuf dlgPlanTagRuf;
    int rc = SRV_OK;
    rufptag.s.DATUM = date;
    rufptag.s.IDFNR = -1;
    rufptag.s.FILIALNR = (AeGetApp()->IsKundeHome() || AeGetApp()->IsAnrufPlanEigen()) ? AeGetApp()->VzNr() : 0;
    rufptag.s.REGIONNR = AeGetApp()->VzNr();
    rufptag.s.RUFZEIT = 0;
    rufptag.s.STATUS  = ST_OB;
    rufptag.s.PRIORITAET = 1; /* committed read */
    strcpy(rufptag.s.ANRUFART, m_bNoParaCalls ? DAFUE_PARALELL : "  ");

    m_bCancel = FALSE;
    while (rc == SRV_OK)
    {
        rc = CallServer(F_SELFIRST, &rufptag);
        if (rc != SRV_OK)
            continue;

        if (rufptag.s.STATUS < 0 && rufptag.s.LFDAKTION > 0)
        {
            rc = CallServer(F_SELNEXT, &rufptag);
            continue;
        }

        rc = CallServer(F_SELCLOSE, &rufptag);
        if ((rc = CallServer(F_SETGRASP, &rufptag)) != SRV_OK)
            continue;

        dlgPlanTagRuf.m_CIdfnr.Format("%ld", rufptag.s.IDFNR);
        dlgPlanTagRuf.m_CRufzeit.Format("%ld", rufptag.s.RUFZEIT);
        dlgPlanTagRuf.m_sVzNr = rufptag.s.FILIALNR;

        if (rufptag.s.RUFZEITGEAENDERT)
            dlgPlanTagRuf.m_CAktrufzeit.Format("%ld", rufptag.s.RUFZEITGEAENDERT);
        else
            dlgPlanTagRuf.m_CAktrufzeit = "";

        if (dlgPlanTagRuf.DoModal() == IDCANCEL)
        {
            m_bCancel = TRUE;
            rc = 2;
        }

        rc = 2; // Steuerung übernimmt aufrufendes Programm
        if (CallServer(F_UNSET, &rufptag) != SRV_OK)
        {
            MsgBoxOK(IDS_CALL_NOT_FREE);
            break;
        }
    }

    CallServer(F_SELCLOSE, &rufptag);
    if (rc == SRV_SQLNOTFOUND)
    {
        m_bCancel = FALSE;
        return NO_CUSTOMER;
    }
    if (dlgPlanTagRuf.m_bNotFound == TRUE)
    {
        m_bCancel = FALSE;
        return NO_CUSTOMER;
    }
    if (m_bCancel)
    {
        return NO_CUSTOMER;
    }

    m_VzNr = rufptag.s.FILIALNR;
    return rufptag.s.IDFNR;
}

/***GetNextPhopneCall-GET-CALL-SEL *****************************************/

long GetNextPhoneCall::GetCallSel()
{
    CDPlanTag dlgPlanTag;
    dlgPlanTag.m_CIdf.Format("%d", NO_CUSTOMER);
    dlgPlanTag.m_bCall = true;
    dlgPlanTag.m_bNoParaCalls = m_bNoParaCalls;

    m_bCancel = FALSE;
    if (dlgPlanTag.DoModal() == IDCANCEL)
        m_bCancel = TRUE;

    if (m_bCancel)
        return NO_CUSTOMER;

    m_VzNr = dlgPlanTag.m_VzNr;
    return(atol(dlgPlanTag.m_CIdf));
}

/***GetNextPhopneCall-GET-CALL-SEL *****************************************/

long GetNextPhoneCall::IsNextCall(long date)
{
    CRUFPTAG rufptag;

    rufptag.s.DATUM = date;
    rufptag.s.IDFNR = -1;
    if (AeGetApp()->IsKundeHome())
        rufptag.s.FILIALNR = AeGetApp()->VzNr();
    else if (AeGetApp()->IsAnrufPlanEigen())
        rufptag.s.FILIALNR = AeGetApp()->VzNr();
    else rufptag.s.FILIALNR = 0;
    rufptag.s.REGIONNR = AeGetApp()->VzNr();
    rufptag.s.RUFZEIT = 0;
    rufptag.s.STATUS  = ST_OB;
    rufptag.s.PRIORITAET = 1; // committed read
    strcpy(rufptag.s.ANRUFART, m_bNoParaCalls ? DAFUE_PARALELL : "  ");

    if (CallServer(F_SELFIRST, &rufptag) != SRV_OK)
    {
        //nase kaerger
        CallServer(F_SELCLOSE, &rufptag);
        return (long)NO_CUSTOMER;
    }

    CallServer(F_SELCLOSE, &rufptag);

    m_VzNr = rufptag.s.FILIALNR;
    return rufptag.s.IDFNR;
}

HBRUSH CDPlanTagRuf::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_STATIC_BEMERKUNG)
        pDC->SetTextColor(RGB(200, 0, 0));

    return hbr;
}

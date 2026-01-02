// aefview.cpp : implementation file
//
#include "stdafx.h"
#include "MainFrm.h"
#include "DCountDown.h"
#include "AeFView.h"
#include "AeDoc.h"
#include "DOffAuftr.h"
#include "DAufDef.h"
#include "MAufDef.h"
#include "DAufBear.h"
#include "DAufFrText.h"
#include "DKndWahl.h"
#include "DKritik.h"
#include "DUpdNachl.h"
#include <kndsel.h>
#include "DKndInf.h"
#include "DArtInf.h"
#include "DAufEnd.h"
#include "DBePosBearb.h"
#include "DPlanTag.h"
#include "DAufInf.h"
#include "zeitart.h"
#include "DAufTxt.h"
#include "DBestSB.h"
#include "DAltArt.h"
#include "DAuftrEreign.h"
#include "DCheckOpenCallOrOrder.h"
#include "DInfoListe.h"
#include "DProtNachLief.h"
#include "DVerbBestaet.h"
#include "DNachlBearb.h"
#include "GetNextPhoneCall.h"
#include <verbundcheck.h>
#include "PriceType.h"

#include <callback.h>
#include "DCallbackItem.h"
#include "DCallbackFetch.h"
#include "DVbBuchen.h"
#include <artikel.h>
#include "DReimport.h"
#include "ProCenter.h"
#include "DHPCallin.h"
#include "DConnect.h"
#include "DUmsHercode.h"
#include <customer.h>
#include "DTelNr.h"
#include <filinf.h>
#include "DDelayedCst.h"
#include <callplanmaintenance.h>
#include "DWirkGruppe.h"
#include "DTenderOrder.h"
#include "DAufwerte.h"
#include "DBTMLicense.h"
#include "DViewPos.h"
#include "DViewRabs.h"
#include "DViewKnd.h"
#include "DKritikAnz.h"
#include <serviceorder.h>
#include "DServiceOrder.h"
#include <promo.h>
#include "DPromotionen.h"
#include "DProductPromo.h"
#include "DShowRanges.h"
#include <orders.h>
#include "DShowProforma.h"
#include "DNewCallback.h"
#include "DViewCstBranchInfo.h"
#include "DShowRebates.h"
#include "ArtNotFound.h"
#include "DCstTours.h"
#include "DAufAuswahl.h"
#include <auftragsart.h>
#include "AeFView.h"

#define AEST_ALARM          1       //Timeridentifikation for Beep
#define AEST_ALARM_ZEIT     1500    //1,5 Sekunden
#define AEST_WAKETOUR       2       //Timeridentifikation for Tourabschnluss

#define ZEILEN 10

//Definitionen Lieferbereitschaft
#define LIEFBER_OK                0
#define LIEFBER_VERBUND           1
#define LIEFBER_NO                2
#define LIEFBER_KUEHL             3
#define LIEFBER_CHARGE            4
#define LIEFBER_BTM               5
#define LIEFBER_PRIVAT            6
#define LIEFBER_QUOTA            10
#define LIEFBER_KUEHL_U8         11
#define LIEFBER_PSYCHO           12
#define LIEFBER_QUOTA_DEF        13
#define LIEFBER_QUOTA_VB         14
#define LIEFBER_L5               15  // Definitionen Liste5
#define LIEFBER_PSYCHO_KK        16
#define LIEFBER_PSYCHO_K08       17
#define LIEFBER_CHARGE_KUEHL     18
#define LIEFBER_PROD_QUOTA       19
#define LIEFBER_CHARGE_KUEHL08   20
#define LIEFBER_KUEHL20          21
#define LIEFBER_DEGETTER         22
#define LIEFBER_TFG              23
#define LIEFBER_MDR              24
#define LIEFBER_MITTEL           25
#define LIEFBER_ULTRA            26

//Definitionen Positionsart
#define POS_FV      7
#define POS_KK      8
#define POS_EH      9

static COLUMNS_TYPES Columns[] =
{
    COL_FVIEW_KB,           "", 30,     LVCFMT_LEFT,
    COL_FVIEW_BESTAND,      "", 30,     LVCFMT_RIGHT,
    COL_FVIEW_EINHEIT,      "", 70,     LVCFMT_RIGHT,
    COL_FVIEW_ARTIKELNAME,  "", 210,    LVCFMT_LEFT,
    COL_FVIEW_DAF,          "", 43,     LVCFMT_CENTER,
    COL_FVIEW_PREIS,        "", 55,     LVCFMT_RIGHT,
    COL_FVIEW_KB2,          "", 20,     LVCFMT_CENTER,
    COL_FVIEW_VERFALL,      "", 41,     LVCFMT_RIGHT,
    COL_FVIEW_KENNZEICHEN,  "", 41,     LVCFMT_CENTER,
    COL_FVIEW_ARTICLE_CODE, "", 54,     LVCFMT_LEFT,
    COL_FVIEW_HERSTELL,     "", 60,     LVCFMT_LEFT,
    COL_FVIEW_TEXT,         "", 180,    LVCFMT_LEFT,
    COL_FVIEW_APOPFLICHT,   "", 0,      LVCFMT_LEFT,
    COL_FVIEW_TEXTKEY,      "", 0,      LVCFMT_LEFT,
    COL_FVIEW_OPIAT,        "", 0,      LVCFMT_LEFT,
    COL_FVIEW_KKCODE,       "", 0,      LVCFMT_LEFT,
    COL_FVIEW_PREISGR4,     "", 0,      LVCFMT_LEFT,
    COL_FVIEW_TAXLEVEL,     "", 0,      LVCFMT_LEFT,
    COL_FVIEW_LEER,         "", 0,      LVCFMT_LEFT,
    COL_FVIEW_GROSSO,       "", 0,      LVCFMT_LEFT,
    COL_FVIEW_CODE_TYPE,    "", 0,      LVCFMT_LEFT,
    COL_FVIEW_PZN,          "", 0,      LVCFMT_RIGHT,
    COL_FVIEW_GROSSONA,     "", 0,      LVCFMT_LEFT,
    COL_FVIEW_SUPPLINFO,    "", 180,    LVCFMT_LEFT,
    COL_FVIEW_SUPPLPROG,    "", 40,     LVCFMT_LEFT,
    COL_FVIEW_SUPPLLIEF,    "", 40,     LVCFMT_LEFT,
    COL_FVIEW_PRODQUOTA,    "", 0,      LVCFMT_LEFT,
    -1, "", 0,      0
};

static COLUMNS_TYPES Columns_VB[] =
{
    COL_VB_FVIEW_VZ,        "", 30,     LVCFMT_LEFT,
    COL_VB_FVIEW_VON1,      "", 40,     LVCFMT_RIGHT,
    COL_VB_FVIEW_BIS1,      "", 40,     LVCFMT_RIGHT,
    COL_VB_FVIEW_VON2,      "", 40,     LVCFMT_RIGHT,
    COL_VB_FVIEW_BIS2,      "", 40,     LVCFMT_RIGHT,
    -1, "", 0,      0
};

/////////////////////////////////////////////////////////////////////////////
// CAeFView

IMPLEMENT_DYNCREATE(CAeFView, CFormViewMultiLang)

CAeFView::CAeFView()
    : CFormViewMultiLang(CAeFView::IDD), CPageBrowser(ZEILEN)
{
    m_CArtNr = _T("");
    m_CMenge = _T("");
    m_CDarr = _T("");
    m_CMatchCode = _T("");
    m_CBemerkung = _T("");
    m_CNatRab = _T("");
    m_CZusatz = _T("");
    m_CPackGr = _T("");
    m_BuchStat = -1;
    m_CKndText = _T("");
    m_CNormPackung = _T("");
    m_CTel = _T("");
    m_CHC = _T("");
    m_BuchStat = 0;          //Buchungsart normal einstellen
    m_ABemerkung = _T("");   //Auftragsbemerkung
    m_Tour = _T("");         //aktuelle Tour
    m_lDeliveryDate = 0;     //Lieferdatum
    m_Valuta = 0;            //Valutamonate
    m_lDatumValuta = 0;      //Valutadatum
    m_lBatchschreiben = 0;
    m_bBuchungErfolgt = TRUE;
    m_ArtNrAlt = 0;
    m_bKndSchwerpunk3 = false; //kein Arbeitskreis aktuell
    m_bKndSchwerpunk5 = false; //kein Diabetes
    m_bKndMussKopfBem = false; //Auftragskopfbemerkung nicht erzwingen
    m_lKdauftragNr = 0;
    m_lNoDoubleArtNr = 0; //nicht pruefen doppelte Eingabe
    m_lTenderNo = 0;         //Tendrnummer
    m_sServType = 0;         //Servicetype Nummer
    m_dCstDiscount = 0;
    m_pDlgDown = new CDCountDown(this);
    m_pDlgRab = new CDViewRabs(this);
    m_pDlgKnd = new CDViewKnd(this);
    m_pDlgKritik = new CDKritikAnz(this);
    m_pDlgBranchInfo = new CDViewCstBranchInfo(this);
    m_sFVRabkonto = 0;
    m_sKKRabkonto = 0;
    m_bNoRabattKonto = FALSE;
    m_iImport = 0;          //Kennz. für Importartikel

    Columns[COL_FVIEW_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_FVIEW_BESTAND].Columns = CResString::ex().getStrTblText(AETXT_KURZ_BESTAND);
    Columns[COL_FVIEW_EINHEIT].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[COL_FVIEW_ARTIKELNAME].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns[COL_FVIEW_DAF].Columns = CResString::ex().getStrTblText(AETXT_DAF);
    Columns[COL_FVIEW_PREIS].Columns = CResString::ex().getStrTblText(AETXT_AEP);
    Columns[COL_FVIEW_KB2].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_FVIEW_VERFALL].Columns = CResString::ex().getStrTblText(AETXT_KURZ_VERFALL);
    Columns[COL_FVIEW_KENNZEICHEN].Columns = CResString::ex().getStrTblText(AETXT_KZ_KENNZEICHEN);
    Columns[COL_FVIEW_ARTICLE_CODE].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[COL_FVIEW_PZN].Columns = CResString::ex().getStrTblText(AETXT_ARTIKEL_NR);
    Columns[COL_FVIEW_HERSTELL].Columns = CResString::ex().getStrTblText(AETXT_HERSTEL);
    Columns[COL_FVIEW_SUPPLINFO].Columns = CResString::ex().getStrTblText(AETXT_SUPPLINFO);
    Columns[COL_FVIEW_SUPPLPROG].Columns = CResString::ex().getStrTblText(AETXT_PROG);
    Columns[COL_FVIEW_SUPPLLIEF].Columns = CResString::ex().getStrTblText(AETXT_LIEF);
    Columns[COL_FVIEW_PRODQUOTA].Columns = CResString::ex().getStrTblText(AETXT_PROD_QUOTA);
    if (AeGetApp()->IsAnzRabatte())
    {
        Columns[COL_FVIEW_TEXT].Columns = CResString::ex().getStrTblText(AETXT_RABATT);
    }
    else
    {
        Columns[COL_FVIEW_TEXT].Columns = CResString::ex().getStrTblText(AETXT_TEXT);
    }
    if (AeGetApp()->IsBG())
    {
        Columns[COL_FVIEW_KKCODE].Columns = CResString::ex().getStrTblText(AETXT_KK_CODE);
    }
    else if (!AeGetApp()->IsRS())
    {
        Columns_VB[COL_VB_FVIEW_VZ].Columns = CResString::ex().getStrTblText(AETXT_VZ);
        Columns_VB[COL_VB_FVIEW_VON1].Columns = CResString::ex().getStrTblText(AETXT_VON);
        Columns_VB[COL_VB_FVIEW_BIS1].Columns = CResString::ex().getStrTblText(AETXT_BIS);
        Columns_VB[COL_VB_FVIEW_VON2].Columns = CResString::ex().getStrTblText(AETXT_VON);
        Columns_VB[COL_VB_FVIEW_BIS2].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    }

}

CAeFView::~CAeFView()
{
    delete m_pDlgDown;  // löscht Fenster, falls nicht bereits geschehen
    delete m_pDlgRab;   // löscht Fenster, falls nicht bereits geschehen
    delete m_pDlgKnd;   // löscht Fenster, falls nicht bereits geschehen
    delete m_pDlgKritik;    // löscht Fenster, falls nicht bereits geschehen
    delete m_pDlgBranchInfo;    // löscht Fenster, falls nicht bereits geschehen

}

void CAeFView::DoDataExchange(CDataExchange* pDX)
{
    CFormViewMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_TEL, m_cs_Tel);
    DDX_Control(pDX, IDC_STATIC_RABATTWERT, m_cs_Rabattwert);
    DDX_Control(pDX, IDC_STATIC_RABATTWERT2, m_cs_Rabattwert2);
    DDX_Control(pDX, IDC_EDIT_NORMPACKUNG, m_EditNormPackung);
    DDX_Control(pDX, IDC_COMBO_BUCH_STAT, m_ComboBuchStat);
    DDX_Control(pDX, IDC_EDIT_ZUSATZ, m_EditZusatz);
    DDX_Control(pDX, IDC_EDIT_PACK_GR, m_EditPackGr);
    DDX_Control(pDX, IDC_EDIT_NATRAB, m_EditNatRab);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_EditMenge);
    DDX_Control(pDX, IDC_EDIT_DARREICHUNG, m_EditDarr);
    DDX_Control(pDX, IDC_EDIT_BEZEI, m_EditMatchCode);
    DDX_Control(pDX, IDC_EDIT_BEMERKUNG, m_EditBemerkung);
    DDX_Control(pDX, IDC_EDIT_ARTNR, m_EditArtNr);
    DDX_Control(pDX, IDC_EDIT_HC, m_EditHC);
    DDX_Control(pDX, IDC_LISTCTRL_ART, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_ARTNR, m_CArtNr);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_CMenge);
    DDX_Text(pDX, IDC_EDIT_DARREICHUNG, m_CDarr);
    DDX_Text(pDX, IDC_EDIT_BEZEI, m_CMatchCode);
    DDX_Text(pDX, IDC_EDIT_BEMERKUNG, m_CBemerkung);
    DDX_Text(pDX, IDC_EDIT_NATRAB, m_CNatRab);
    DDX_Text(pDX, IDC_EDIT_ZUSATZ, m_CZusatz);
    DDX_Text(pDX, IDC_EDIT_PACK_GR, m_CPackGr);
    DDX_Text(pDX, IDC_EDIT_HC, m_CHC);
    DDX_CBIndex(pDX, IDC_COMBO_BUCH_STAT, m_BuchStat);
    DDX_Text(pDX, IDC_STATIC_KNDTEXT, m_CKndText);
    DDX_Text(pDX, IDC_EDIT_NORMPACKUNG, m_CNormPackung);
    DDX_Text(pDX, IDC_STATIC_TEL, m_CTel);
    DDX_Control(pDX, IDC_COMBO_FREE_PRICE, m_CoboxFreePrice);
    DDX_Control(pDX, IDC_COMBO_TYP, m_ComboTyp);
    DDX_Control(pDX, IDC_STATIC_ORIGINAL_VZ, m_cs_VZ);
    DDX_Control(pDX, IDC_EDIT_FREE_PRICE, m_EditPreis);
    DDX_Text(pDX, IDC_EDIT_FREE_PRICE, m_CPreis);
    DDX_Control(pDX, IDC_LIST_VB_ZEITEN, m_List_VB);
}


BEGIN_MESSAGE_MAP(CAeFView, CFormViewMultiLang)
    ON_WM_CONTEXTMENU()
    ON_WM_CREATE()
    ON_NOTIFY(LVN_KEYDOWN, IDC_LISTCTRL_ART, OnKeydownListctrlArt)
    ON_COMMAND(ID_KUNDE_OFFENE_AUFTRGE, OnKundeOffeneAuftrge)
    ON_UPDATE_COMMAND_UI(ID_KUNDE_OFFENE_AUFTRGE, OnUpdateKundeOffeneAuftrge)
    ON_COMMAND(ID_KUNDE_ANRUFEN, OnKundeAnrufen)
    ON_UPDATE_COMMAND_UI(ID_KUNDE_ANRUFEN, OnUpdateKundeAnrufen)
    ON_COMMAND(ID_AUFTR_DEF, OnAuftrDef)
    ON_UPDATE_COMMAND_UI(ID_AUFTR_DEF, OnUpdateAuftrDef)
    ON_COMMAND(ID_INF_ART, OnInfArt)
    ON_UPDATE_COMMAND_UI(ID_INF_ART, OnUpdateInfArt)
    ON_COMMAND(ID_AUFTR_BEARB, OnAuftrBearb)
    ON_UPDATE_COMMAND_UI(ID_AUFTR_BEARB, OnUpdateAuftrBearb)
    ON_COMMAND(ID_INF_KUNDE, OnInfKunde)
    ON_UPDATE_COMMAND_UI(ID_INF_KUNDE, OnUpdateInfKunde)
    ON_COMMAND(ID_AUF_FREITEXT, OnAufFreitext)
    ON_UPDATE_COMMAND_UI(ID_AUF_FREITEXT, OnUpdateAufFreitext)
    ON_COMMAND(ID_AUFTRAG_SAVE, OnAuftragSave)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_SAVE, OnUpdateAuftragSave)
    ON_COMMAND(IDOK, OnOk)
    ON_COMMAND(ID_PRIOR, OnPrior)
    ON_COMMAND(ID_NEXT, OnNext)
    ON_EN_CHANGE(IDC_EDIT_ARTNR, OnChangeEditArtnr)
    ON_EN_CHANGE(IDC_EDIT_BEMERKUNG, OnChangeEditBemerkung)
    ON_EN_CHANGE(IDC_EDIT_BEZEI, OnChangeEditBezei)
    ON_EN_CHANGE(IDC_EDIT_DARREICHUNG, OnChangeEditDarreichung)
    ON_EN_CHANGE(IDC_EDIT_MENGE, OnChangeEditMenge)
    ON_EN_CHANGE(IDC_EDIT_NATRAB, OnChangeEditNatrab)
    ON_EN_CHANGE(IDC_EDIT_PACK_GR, OnChangeEditPackGr)
    ON_EN_CHANGE(IDC_EDIT_ZUSATZ, OnChangeEditZusatz)
    ON_COMMAND(ID_KUNDE_KND_WAHL, OnKundeKndWahl)
    ON_UPDATE_COMMAND_UI(ID_KUNDE_KND_WAHL, OnUpdateKundeKndWahl)
    ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL_ART, OnDblclkListctrlArt)
    ON_COMMAND(ID_INF_AUF, OnInfAuf)
    ON_COMMAND(ID_AE_KOPF_FUSS, OnAeKopfFuss)
    ON_UPDATE_COMMAND_UI(ID_AE_KOPF_FUSS, OnUpdateAeKopfFuss)
    ON_COMMAND(ID_BEARB_DEFNACHBEA, OnBearbDefnachbea)
    ON_UPDATE_COMMAND_UI(ID_BEARB_DEFNACHBEA, OnUpdateBearbDefnachbea)
    ON_COMMAND(ID_AUFTRAG_DAFZURCKGESTELLTEAUFTRGE, OnAuftragDafzurckgestellteauftrge)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_DAFZURCKGESTELLTEAUFTRGE, OnUpdateAuftragDafzurckgestellteauftrge)
    ON_COMMAND(ID_INFORMATIONEN_AUFTRAGSEREIGNISSE, OnInformationenAuftragsereignisse)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_AUFTRAGSEREIGNISSE, OnUpdateInformationenAuftragsereignisse)
    ON_COMMAND(ID_INFORMATIONEN_INFOLISTE, OnInformationenInfoliste)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_INFOLISTE, OnUpdateInformationenInfoliste)
    ON_COMMAND(ID_INFORMATIONEN_KUNDENKONTAKTE, OnInformationenKundenkontakte)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_KUNDENKONTAKTE, OnUpdateInformationenKundenkontakte)
    ON_EN_CHANGE(IDC_EDIT_NORMPACKUNG, OnChangeEditNormpackung)
    ON_COMMAND(ID_KUNDE_KUNDE_AUS_PLAN, OnKundeKundeAusPlan)
    ON_UPDATE_COMMAND_UI(ID_KUNDE_KUNDE_AUS_PLAN, OnUpdateKundeKundeAusPlan)
    ON_UPDATE_COMMAND_UI(ID_INF_AUF, OnUpdateInfAuf)
    ON_COMMAND(ID_INFORMATIONEN_TAGESANRUFPLAN, OnInformationenTagesanrufplan)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_TAGESANRUFPLAN, OnUpdateInformationenTagesanrufplan)
    ON_COMMAND(ID_BEARBEITEN_DAFUEPOSITIONENLSCHEN, OnBearbeitenDafuepositionenlschen)
    ON_UPDATE_COMMAND_UI(ID_BEARBEITEN_DAFUEPOSITIONENLSCHEN, OnUpdateBearbeitenDafuepositionenlschen)
    ON_COMMAND(ID_VERWALTUNG_STANDARDAUFTRAGSART, OnVerwaltungStandardauftragsart)
    ON_UPDATE_COMMAND_UI(ID_VERWALTUNG_STANDARDAUFTRAGSART, OnUpdateVerwaltungStandardauftragsart)
    ON_COMMAND(ID_BEARBEITEN_KUNDENNDERN, OnBearbeitenKundenndern)
    ON_UPDATE_COMMAND_UI(ID_BEARBEITEN_KUNDENNDERN, OnUpdateBearbeitenKundenndern)
    ON_COMMAND(ID_BEARBEITEN_NACHLIEFERPOSITIONEN, OnBearbeitenNachlieferpositionen)
    ON_UPDATE_COMMAND_UI(ID_BEARBEITEN_NACHLIEFERPOSITIONEN, OnUpdateBearbeitenNachlieferpositionen)
    ON_COMMAND(ID_PROT_NACHLIFBEARB, OnProtNachlifbearb)
    ON_UPDATE_COMMAND_UI(ID_PROT_NACHLIFBEARB, OnUpdateProtNachlifbearb)
    ON_COMMAND(ID_EXTRAS_VERBUND_ZEIGEN, OnExtrasVerbundZeigen)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_VERBUND_ZEIGEN, OnUpdateExtrasVerbundZeigen)
    ON_COMMAND(ID_INFORMATIONEN_CALLBACK, OnInformationenCallback)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_CALLBACK, OnUpdateInformationenCallback)
    ON_COMMAND(ID_INFORMATIONEN_CALLBACK_DO, OnInformationenCallbackDo)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_CALLBACK_DO, OnUpdateInformationenCallbackDo)
    ON_COMMAND(ID_AUFTRAG_VERBUND, OnAuftragVerbund)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_VERBUND, OnUpdateAuftragVerbund)
    ON_COMMAND(ID_AUFTRAG_DEFEKTE, OnAuftragDefekte)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_DEFEKTE, OnUpdateAuftragDefekte)
    ON_WM_CTLCOLOR()
    ON_COMMAND(ID_EXTRAS_NICHT_DEFEKT, OnExtrasNichtDefekt)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_NICHT_DEFEKT, OnUpdateExtrasNichtDefekt)
    ON_WM_TIMER()
    ON_COMMAND(ID_HIPATH_CALL, OnHipathCall)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_CALL, OnUpdateHipathCall)
    ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
    ON_MESSAGE(WM_HELPHITTEST, OnHelpHitTest)
    ON_MESSAGE(WM_PHONERING, OnPhoneRing2)
    ON_EN_CHANGE(IDC_EDIT_HC, OnEnChangeEditHc)
    ON_COMMAND(ID_INFORMATIONEN_UMSATZ, OnInformationenUmsatz)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_UMSATZ, OnUpdateInformationenUmsatz)
    ON_COMMAND(ID_HIPATH_INS_TELNR, OnHipathInsTelnr)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_INS_TELNR, OnUpdateHipathInsTelnr)
    ON_COMMAND(ID_PFLEGE_TELEFONNR, OnPflegeTelefonnr)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_TELEFONNR, OnUpdatePflegeTelefonnr)
    ON_MESSAGE(WM_RENEW, OnReNew)
    ON_MESSAGE(WM_CONSULT, OnPhoneConsult)
    ON_EN_CHANGE(IDC_EDIT_FREE_PRICE, OnEnChangeEditPreis)
    ON_NOTIFY(NM_CLICK, IDC_LISTCTRL_ART, OnNMClickListctrlArt)
    ON_COMMAND(ID_PFLEGE_DD_EINZEL, OnPflegeDdEinzel)
    ON_COMMAND(ID_BEARBEITEN_WIRKSTOFF, OnBearbeitenWirkstoff)
    ON_UPDATE_COMMAND_UI(ID_BEARBEITEN_WIRKSTOFF, OnUpdateBearbeitenWirkstoff)
    ON_COMMAND(ID_BEARB_OCCASION, OnBearbOccasion)
    ON_UPDATE_COMMAND_UI(ID_BEARB_OCCASION, OnUpdateBearbOccasion)
    ON_COMMAND(ID_AUFTRAG_WERTE, OnAuftragWerte)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_WERTE, OnUpdateAuftragWerte)
    ON_COMMAND(ID_AUFTRAG_BTM_LICENSE, OnBTMLicense)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_BTM_LICENSE, OnUpdateBTMLicense)
    ON_MESSAGE(WM_GOODBYEDOWN, OnGoodbyeDown)
    ON_CBN_SELCHANGE(IDC_COMBO_TYP, OnCbnSelchangeComboTyp)
    ON_MESSAGE(WM_GOODBYERAB, OnGoodbyeRab)
    ON_COMMAND(ID_AUFTRAG_PROMO, OnPromotionen)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_PROMO, OnUpdatePromotionen)
    ON_COMMAND(IDCANCEL, OnCancel)
    ON_COMMAND(ID_BEARB_RAB_DEFEKTE, OnBearbRabDefs)
    ON_COMMAND(ID_INFORMATIONEN_RANGE, OnInformationenRange)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_RANGE, OnUpdateInformationenRange)
    ON_COMMAND(ID_Menu33049, OnMenu33049)
    ON_UPDATE_COMMAND_UI(ID_Menu33049, OnUpdateMenu33049)
    ON_MESSAGE(WM_GOODBYEBINFO, OnGoodbyeBInfo)
    ON_COMMAND(ID_AUFTRAG_NL_BEARB, &CAeFView::OnAuftragNlBearb)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_NL_BEARB, &CAeFView::OnUpdateAuftragNlBearb)
    ON_BN_CLICKED(IDC_RADIO_IMPORT0, &CAeFView::OnBnClickedRadioImport)
    ON_BN_CLICKED(IDC_RADIO_IMPORT1, &CAeFView::OnBnClickedRadioImport)
    ON_BN_CLICKED(IDC_RADIO_IMPORT2, &CAeFView::OnBnClickedRadioImport)
    ON_COMMAND(ID_VIEW_NO_CRITICS, &CAeFView::OnViewNoCritics)
    ON_UPDATE_COMMAND_UI(ID_VIEW_NO_CRITICS, &CAeFView::OnUpdateViewNoCritics)
    ON_COMMAND(ID_VIEW_NO_BRANCHINFO, &CAeFView::OnViewNoBranchinfo)
    ON_UPDATE_COMMAND_UI(ID_VIEW_NO_BRANCHINFO, &CAeFView::OnUpdateViewNoBranchinfo)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAeFView diagnostics

#ifdef _DEBUG
void CAeFView::AssertValid() const
{
    CFormViewMultiLang::AssertValid();
}

void CAeFView::Dump(CDumpContext& dc) const
{
    CFormViewMultiLang::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAeFView message handlers

int CAeFView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFormViewMultiLang::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}

void CAeFView::OnInitialUpdate()
{
    if (AeGetApp()->IsBG() || AeGetApp()->IsSchrift())
    {
        scgui::CResizeManager::ex().setIsActive(true);
        //vergrößert um maximal 200%, aber innerhalb der Auflösung
        scgui::CResizeManager::ex().setWindowZoomPerc(200);
        CFormViewMultiLang::OnInitialUpdate();
        scgui::CResizeManager::ex().setIsActive(false);
    }
    else
    {
        CFormViewMultiLang::OnInitialUpdate();
    }

    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES;
    //  dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    m_ListCtl.ModifyStyle(LVS_SHOWSELALWAYS, 0);

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_OK);
    idResources.push_back(IDI_ICON_VERBUND);
    idResources.push_back(IDI_ICON_NO);
    idResources.push_back(IDI_ICON_KUEHL);
    idResources.push_back(IDI_ICON_CHARGE);
    idResources.push_back(IDI_ICON_BTM);
    idResources.push_back(IDI_ICON_PRIVAT);
    idResources.push_back(IDI_ICON_FV);
    idResources.push_back(IDI_ICON_KK);
    idResources.push_back(IDI_ICON_EH);
    idResources.push_back(IDI_ICON_QUOTA);
    idResources.push_back(IDI_ICON_KUEHL_U8);
    idResources.push_back(IDI_ICON_PTS);
    idResources.push_back(IDI_ICON_QUOTA1);
    idResources.push_back(IDI_ICON_QUOTA2);
    idResources.push_back(IDI_ICON_L5);
    idResources.push_back(IDI_ICON_PTS_KK);
    idResources.push_back(IDI_ICON_PTS_K08);
    idResources.push_back(IDI_ICON_CHARGE_KUEHL);
    idResources.push_back(IDI_ICON_PRODQUOTA);
    idResources.push_back(IDI_ICON_CHARGE_KUEHL08);
    idResources.push_back(IDI_ICON_K20);
    idResources.push_back(IDI_ICON_DE_BESORGER);
    idResources.push_back(IDI_ICON_TFG);
    idResources.push_back(IDI_ICON_MDR);
    idResources.push_back(IDI_ICON_MITTEL);
    idResources.push_back(IDI_ICON_ULTRA);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    if (AeGetApp()->IsBG())
    {
        m_ListCtl.SetColumnWidth(COL_FVIEW_KKCODE, 40);
    }

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return;
    }

    if (!AeGetApp()->IsBG() && !AeGetApp()->IsRS())
    {
        // Add the columns.
        if (!CListCtrlHelper::AddColumns(Columns_VB, m_List_VB))
        {
            return;
        }
    }

    /* Create the ToolTip control.
    m_tooltip.Create(this);
    m_tooltip.Activate(TRUE);

    // TODO: Use one of the following forms to add controls:
    m_tooltip.AddTool(GetDlgItem(IDC_EDIT_BEZEI), "Tip für Matchcode!");
    m_tooltip.AddTool(GetDlgItem(IDC_EDIT_ZUSATZ), "Tip für Zusatz");
    int i = EnableToolTips(TRUE);*/
    m_bKz_Nur_Liefber = FALSE;

    CFont* pobjCFont;
    CFont  objCFont;
    CFont  objCFontVZ;
    CFont  objCFontRW;
    CFont  objCFontRW2;
    LOGFONT lf;

    pobjCFont = m_cs_Tel.GetFont();
    pobjCFont->GetLogFont(&lf);
    lf.lfWeight *= 2;
    objCFont.CreateFontIndirect(&lf);

    m_cs_Tel.SetFont(&objCFont);

    pobjCFont = m_cs_VZ.GetFont();
    pobjCFont->GetLogFont(&lf);
    lf.lfWeight *= 2;
    objCFontVZ.CreateFontIndirect(&lf);

    m_cs_VZ.SetFont(&objCFontVZ);

    pobjCFont = m_cs_Rabattwert.GetFont();
    pobjCFont->GetLogFont(&lf);
    lf.lfWeight *= 2;
    objCFontRW.CreateFontIndirect(&lf);
    m_cs_Rabattwert.SetFont(&objCFontRW);

    pobjCFont = m_cs_Rabattwert2.GetFont();
    pobjCFont->GetLogFont(&lf);
    lf.lfWeight *= 2;
    objCFontRW2.CreateFontIndirect(&lf);
    m_cs_Rabattwert2.SetFont(&objCFontRW2);


    m_ComboBuchStat.ResetContent();
    m_ComboBuchStat.AddString(CResString::ex().getStrTblText(AETEXT_NORMAL));
    m_ComboBuchStat.AddString(CResString::ex().getStrTblText(AETEXT_ZUGESAGT));
    m_ComboBuchStat.SetCurSel(0);

    if (AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_WERT_NETTO)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_WERT_NETTO)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_NETTOWERT)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NETTOWERT)->ShowWindow(SW_SHOW);
    }

    if (AeGetApp()->IsBG())
    {
        GetDlgItem(IDC_STATIC_PROFORMA_RAB)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_PROFORMA_RAB)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RECHWERT_RAB)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_RECHWERT_RAB)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PROFORMA)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_PROFORMA)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RECHWERT)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_RECHWERT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VB_ZEITEN2)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_VB_ZEITEN2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_LIST_VB_ZEITEN)->EnableWindow(FALSE);
        GetDlgItem(IDC_LIST_VB_ZEITEN)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_TYP)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_TYP)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_TYP)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_TYP)->ShowWindow(SW_SHOW);
        m_ComboTyp.ResetContent();
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_FREIVERKAUF));
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_KRANKENKASSE));
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_MITUNDOHNE));
        m_ComboTyp.SetCurSel(0);
        GetDlgItem(IDC_STATIC_AW)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_AW)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_LIF_WERT)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_LIF_WERT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_DZW)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_DZW)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_AUFW)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_AUFW)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_LW)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_LW)->ShowWindow(SW_SHOW);
    }
    else if (!AeGetApp()->IsRS())
    {
        GetDlgItem(IDC_STATIC_VB_ZEITEN2)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_VB_ZEITEN2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_LIST_VB_ZEITEN)->EnableWindow(TRUE);
        GetDlgItem(IDC_LIST_VB_ZEITEN)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PROFORMA)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_PROFORMA)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PROFORMA)->SetWindowText(CResString::ex().getStrTblText(AETXT_VB_ZEITEN));
    }
    AllgSetColumnWidthUser(m_ListCtl, "CAefview", KEY_PATH, NUM_FVIEW_COLUMNS);

    HKEY hKey;
    char szBuffer[50];
    DWORD len = sizeof(szBuffer) - 1;
    if (RegOpenKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        if (RegQueryValueEx(hKey, KEY_NAME_VBANZEIGE, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            m_bKz_Verbund_Moegl = (szBuffer[0] == '1') ? true : false;
        }
        else
        {
            m_bKz_Verbund_Moegl = false;
        }
        RegCloseKey(hKey);
    }
}

void CAeFView::InitOrder()
{
    m_iImport = 0;          //Kennz. für Importartikel

    GetDlgItem(IDC_COMBO_FREE_PRICE)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_FREE_PRICE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_PREIS)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_PREIS)->ShowWindow(SW_HIDE);
    if (AeGetApp()->IsBG())
    {
        m_plPromo = new vector<promostruct>;
    }
    else
    {
        if (AeGetApp()->IsRS())
        {
            GetDlgItem(IDC_STATIC_PROFORMA)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_PROFORMA)->ShowWindow(SW_HIDE);
        }
        GetDlgItem(IDC_STATIC_PROFORMA_RAB)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_PROFORMA_RAB)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RECHWERT)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_RECHWERT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RECHWERT_RAB)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_RECHWERT_RAB)->ShowWindow(SW_HIDE);
    }
    GetDlgItem(IDC_STATIC_RABATT_WERT)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_RABATT_WERT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_RABATTWERT)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_RABATTWERT)->ShowWindow(SW_HIDE);
    m_CoboxFreePrice.ResetContent();
    SetTimer(AEST_ALARM, AEST_ALARM_ZEIT, NULL);
    m_TimeCount = 0;
    CloseCursor();
    GetDocument()->SetModifiedFlag();
    ((CAeDoc*)GetDocument())->m_bAllItemsInList = true;
    m_EditMenge.SetFocus();
    m_bBuchungErfolgt = TRUE;
    m_iDefNachPos = 0;
    m_bDafueKz = false;
    m_bDefSelVerbund    = FALSE;
    m_bDefSelDfDef      = FALSE;
    m_bDefSelPhonDef    = FALSE;
    m_bDefSelDfFrText   = FALSE;
    m_bDefSelPhonFrText = FALSE;
    m_bPara = false;
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_lActDatum = zeit.s.DATUM;
}

void CAeFView::InitOrderHead(CAUFTRAG& auftrag, BOOL bNewOrder)
{
    CAUFTRAGSART aart;
    char error_msg[81];
    aart.SetBranchno(auftrag.s.VERTRIEBSZENTRUMNR);
    aart.SetKdauftragart(auftrag.s.KDAUFTRAGART);

    int rc = ::ServerNr(PIPE_AE_SRV, AasrvSelCscOrderType, (void *)&aart.s, AUFTRAGSART_BES, AUFTRAGSART_ANZ, error_msg);
    if (rc < 0)
    {
        FehlerBehandlung(rc, error_msg);
        AeGetApp()->IsOTfixBatch = false;
        AeGetApp()->IsOTwishBatch = false;
        AeGetApp()->IsOTforbiduserchangeBatch = false;
    }
    else
    {
        AeGetApp()->IsOTfixBatch = (aart.GetAllowfixedbatch() == 1);
        AeGetApp()->IsOTwishBatch = (aart.GetAllowdesiredbatch() == 1);
        AeGetApp()->IsOTforbiduserchangeBatch = (aart.GetForbiduserchange() == 1);
    }
    //Initialisierung von Membervariablen
    m_PaymentType = auftrag.s.PAYMENTTYPE;
    GetDlgItem(IDC_STATIC_PAYMENTTYPE)->ShowWindow((auftrag.s.PAYMENTTYPE[0] == 'C') ? SW_SHOW : SW_HIDE);

    m_bNoMorePos = FALSE;
    if (bNewOrder )
    {
        m_cZuGrund = "                ";
        m_Valuta = 0;
        m_lDatumValuta = 0;
        m_lTenderNo = 0;
        m_sServType = 0;
        m_lBatchschreiben = 0;
        m_ABemerkung = _T("");   //Auftragsbemerkung
        m_lKdauftragNr = 0;
        m_lDatumDD = auftrag.s.DATUMAUSLIEFERUNG;
        AeGetApp()->RODateFrom = 0;
        m_bNoRabattKonto = FALSE;
    }
    else
    {
        AllgEntfSpaces(auftrag.s.BEMERKUNGEN);
        m_ABemerkung    = auftrag.s.BEMERKUNGEN;
        m_cZuGrund      = auftrag.s.ZUGRUND;
        m_Valuta        = auftrag.s.VALUTAMONATE;
        m_lDatumValuta  = auftrag.s.DATUMVALUTA;
        m_lBatchschreiben = auftrag.s.BATCHSCHREIBEN;
        m_lDatumDD      = auftrag.s.DATUMAUSLIEFERUNG;
        m_lTenderNo     = auftrag.s.TENDERNO;
        m_sServType = 0;
        if (AeGetApp()->IsBG())
        {
            if (auftrag.s.NORABATTKONTO[0] == '1')
                m_bNoRabattKonto = TRUE;
            if (auftrag.s.KDAUFTRAGART[0] == 'S')  //Service-Auftragsart
            {
                CSERVICEORDER serv;
                serv.SetOrder_type(auftrag.s.KDAUFTRAGART);
                if (!serv.SelType())
                {
                    m_sServType = serv.GetServicetypeno();
                }
            }
            else if (!strncmp(auftrag.s.KDAUFTRAGART, "RO", 2))
            {
                AeGetApp()->RODateFrom = 1; // ungleich 0 fuer aufdef
            }
        }
        if (auftrag.s.NOMOREPOS[0] == '1')
        {
            m_bNoMorePos = TRUE;
        }
    }
    m_lAnzDefekt = auftrag.s.ANZDEFEKTUB;

    CKNDINF kndinf;
    kndinf.s.KUNDENNR = auftrag.s.KUNDENNR;
    kndinf.s.VERTRIEBSZENTRUMNR = auftrag.s.VERTRIEBSZENTRUMNR;
    kndinf.Server(AakundeSel_knd_info);
    if (kndinf.rc < SRV_OK)
    {
        AeGetApp()->KndKlasse1 = 0;
        AeGetApp()->KndGruppe = 0;
    }
    else
    {
        AeGetApp()->KndKlasse1 = AeGetApp()->IsBG() ? kndinf.s.ETARTKLASSE1 : 65535; //alles - nur in BG klassifiziert

        if (AeGetApp()->IsHR())
        {
            if (kndinf.s.SKDSCHWERPUNKT2[0] == '1')
            {
                GetDlgItem(IDC_STATIC_ERACUN)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_ERACUN)->EnableWindow(TRUE);
            }
            else
            {
                GetDlgItem(IDC_STATIC_ERACUN)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_STATIC_ERACUN)->EnableWindow(FALSE);
            }
        }
        int klasse = 0;
        int type = atoi(kndinf.s.KDGRUPPE);
        switch (type)
        {
        case 8:
        case 9:
        case 13:
        case 17:
            klasse = 1;
            break;
        case 12:
        case 15:
            klasse = 2;
            break;
        default:
            break;
        }
        AeGetApp()->KndGruppe = klasse;
        m_OrgFilNr = kndinf.s.ORIGINALFILIALNR;
        if (m_OrgFilNr == 0)
            m_OrgFilNr = kndinf.s.VERTRIEBSZENTRUMNR;
    }

    AllgEntfSpaces(auftrag.s.TOURID);
    if (strlen(auftrag.s.TOURID) == 0)   //keine Standardtour vorgegeben
    {
        m_Tour = "";
        m_lDeliveryDate = 0;
    }
    else
    {
        m_Tour = auftrag.s.TOURID;
        m_lDeliveryDate = auftrag.s.DELIVERYDATE;
    }
    AllgEntfSpaces(auftrag.s.KZSPRACHE);
    CString cSprache = auftrag.s.KZSPRACHE;
    AeGetApp()->KzSprache = cSprache;
    AeGetApp()->IsGiveProdQuota = (kndinf.s.SKDGIVEPRODQUOTA[0] == '1');
    m_IdfNr = auftrag.s.IDFNR;
    m_KndNr = auftrag.s.KUNDENNR;
    m_VzNr  = auftrag.s.VERTRIEBSZENTRUMNR;
    CPARAUFBEARB paraufbearb;
    paraufbearb.s.FILIALNR = m_VzNr;
    BeginWaitCursor();
    paraufbearb.Server(AafilSelaufbearb);
    EndWaitCursor();
    AeGetApp()->UseTourManagerCst = paraufbearb.s.USETOURMANAGER;
    AeGetApp()->IsAutoBuchungNachlieferung = (paraufbearb.s.AUTOMNACHLIEF[0] == '1');
    AeGetApp()->IsCool20 = (paraufbearb.s.SCOOL20 == 1);
    AeGetApp()->IsBTMextra = (paraufbearb.s.BTM_EXTRA[0] == '1');
    AeGetApp()->IsNoValuta = (paraufbearb.s.SNOCHANGEVAL[0] == '1');
    AeGetApp()->IsKumPos = (paraufbearb.s.SKUMPOS[0] == '1');
    AeGetApp()->IsPrintCode = (paraufbearb.s.SANZPRINTCODE[0] == '1');
    AeGetApp()->IsIBTdirect = (paraufbearb.s.SCLOSEIBTATONCE == 1);
    AeGetApp()->IsNewCallback = (paraufbearb.s.SWNEWCALLBACK == 1);
    BOOL bDispoImportCst = (paraufbearb.s.SDISPOIMPORT == 1) ? TRUE : FALSE;
    int nDispoImportCstCmdShow = bDispoImportCst ? SW_SHOW : SW_HIDE;
    if (bDispoImportCst)
    {
        CheckRadioButton(IDC_RADIO_IMPORT1, IDC_RADIO_IMPORT2, IDC_RADIO_IMPORT0);
    }
    AeGetApp()->IsDispoImportCst = bDispoImportCst ? true : false;
    GetDlgItem(IDC_STATIC_FILTER)->EnableWindow(bDispoImportCst);
    GetDlgItem(IDC_STATIC_FILTER)->ShowWindow(nDispoImportCstCmdShow);
    GetDlgItem(IDC_STATIC_FILTER)->EnableWindow(bDispoImportCst);
    GetDlgItem(IDC_RADIO_IMPORT2)->ShowWindow(nDispoImportCstCmdShow);
    GetDlgItem(IDC_RADIO_IMPORT2)->EnableWindow(bDispoImportCst);
    GetDlgItem(IDC_RADIO_IMPORT1)->ShowWindow(nDispoImportCstCmdShow);
    GetDlgItem(IDC_RADIO_IMPORT1)->EnableWindow(bDispoImportCst);
    GetDlgItem(IDC_RADIO_IMPORT0)->ShowWindow(nDispoImportCstCmdShow);
    GetDlgItem(IDC_RADIO_IMPORT0)->EnableWindow(bDispoImportCst);
    AeGetApp()->IsStopCrema = (paraufbearb.s.SSTOPCREMA == 1);
    AeGetApp()->IsNLevelIBTCst = (paraufbearb.s.NLEVELIBT == 1);
    AeGetApp()->IsNlSofort = (paraufbearb.s.SCLOSERESTDELIVERYATONCE == 1);
    AeGetApp()->IsDispoSofort = (paraufbearb.s.SCLOSEDISPOATONCE == 1);
    AeGetApp()->TimeNoBTM = paraufbearb.s.TIME_NO_BTM;
    AeGetApp()->MaxPosEil = paraufbearb.s.MAXPOSEIL;
    AeGetApp()->PosZu = paraufbearb.s.ANZPOSZU;
    AeGetApp()->PriceRange = paraufbearb.s.RANGEPRICEPCT;
    AeGetApp()->DurchlaufZeit = paraufbearb.s.DURCHLAUFNORMAL;
    AeGetApp()->Verspaetung = paraufbearb.s.TOURVERSPAETUNG;
    AeGetApp()->Wake1 = paraufbearb.s.WAKETIME1;
    AeGetApp()->Wake2 = paraufbearb.s.WAKETIME2;

    if (m_OrgFilNr == m_VzNr && !AeGetApp()->IsFR())
    {
        CCUSTOMERDOUBLES doubles;
        doubles.SetVertriebszentrumnr(m_VzNr);
        doubles.SetKundennr(m_KndNr);
        if (!doubles.SelDouble())
        {
            ppString nameVZ;
            GetDlgItem(IDC_STATIC_ORIGINAL_VZ)->SetWindowText(doubles.GetName(nameVZ));
            GetDlgItem(IDC_STATIC_ORIG)->SetWindowText(CResString::ex().getStrTblText(AETXT_ALTERNATIVFILIALE));
            GetDlgItem(IDC_STATIC_ORIG)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_ORIGINAL_VZ)->ShowWindow(SW_SHOW);
        }
        else
        {
            GetDlgItem(IDC_STATIC_ORIG)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_STATIC_ORIGINAL_VZ)->ShowWindow(SW_HIDE);
        }
    }
    else
    {
        CFILINF fili;
        fili.s.FILIALNR = m_OrgFilNr;
        BeginWaitCursor();
        fili.Server( AafilGet_filiale );
        EndWaitCursor();
        AllgEntfSpaces(fili.s.NAME);
        GetDlgItem(IDC_STATIC_ORIG)->SetWindowText(CResString::ex().getStrTblText(AETXT_STAMMFILIALE));
        GetDlgItem(IDC_STATIC_ORIGINAL_VZ)->SetWindowText(fili.s.NAME);
        GetDlgItem( IDC_STATIC_ORIG )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_STATIC_ORIGINAL_VZ )->ShowWindow(SW_SHOW);
    }

    if (AeGetApp()->UseTourManagerCst() == 2)
    {
        CDELAYEDDELIVERYCSTSPECIAL Cst;
        Cst.SetBranchno(m_VzNr);
        if (!Cst.SelUni())
        {
            AeGetApp()->IsKndDD = true;
            AeGetApp()->ZeitDD = Cst.GetTime();
        }
        else
        {
            AeGetApp()->IsKndDD = false;
            AeGetApp()->ZeitDD = 9999;    //zur Sicherheit auf Utopia
        }
        GetDlgItem(IDC_STATIC_DD)->ShowWindow(AeGetApp()->IsKndDD() ? SW_SHOW : SW_HIDE);
    }
    else
    {
        CDELAYEDCST Cst;
        Cst.SetBranchno(m_VzNr);
        Cst.SetCustomerno(m_KndNr);
        if (!Cst.SelDay())
        {
            AeGetApp()->IsKndDD = true;
            AeGetApp()->ZeitDD = Cst.GetTime();
        }
        else
        {
            AeGetApp()->IsKndDD = false;
            AeGetApp()->ZeitDD = 9999;    //zur Sicherheit auf Utopia
        }
        GetDlgItem(IDC_STATIC_DD)->ShowWindow(AeGetApp()->IsKndDD() ? SW_SHOW : SW_HIDE);
    }

    AeGetApp()->KndNLTyp = auftrag.s.NACHLIEFERTYP[0];
    AeGetApp()->KndEilSperre = auftrag.s.EILSPERRE[0];
    AeGetApp()->IsKndKasse = (auftrag.s.KZKDKK[0] == '1');
    AeGetApp()->IsKndRetail = (auftrag.s.SKDRETAILPERMIT[0] == '1');

    if (AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_WERT_NETTO)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_WERT_NETTO)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_NETTOWERT)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NETTOWERT)->ShowWindow(SW_SHOW);
    }

    if (AeGetApp()->IsBG())
    {
        CCSTBULGARIA bulg;
        bulg.SetKundennr(auftrag.s.KUNDENNR);
        bulg.SetVertriebszentrumnr(auftrag.s.VERTRIEBSZENTRUMNR);
        if (!bulg.SelCst())
        {
            AeGetApp()->MainCstNo = bulg.GetMaincstno();
            AeGetApp()->Rebatemethfreesale = bulg.GetRebatemethfreesale();
            AeGetApp()->Rebatemethhealthf = bulg.GetRebatemethhealthf();
        }
        else
        {
            AeGetApp()->MainCstNo = 0;
            AeGetApp()->Rebatemethfreesale = 0;
            AeGetApp()->Rebatemethhealthf = 0;
        }
        m_ComboTyp.ResetContent();
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_FREIVERKAUF));
        m_ComboTyp.SetCurSel(0);
        GetDlgItem( IDC_STATIC_EXCLUSIVE )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_EDIT_EXCLUSIVE )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_STATIC_GESAMT )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_EDIT_GESAMT )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_STATIC_AUFWERTE )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_AUFWERTE )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_STATIC_NETTO )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_NETTO )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_STATIC_MWST )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_MWST )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_STATIC_BRUTTO )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_BRUTTO )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_STATIC_FV )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_FV )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_EDIT_FV_NETTO )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_EDIT_FV_TAX )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_EDIT_FV_BRUTTO )->ShowWindow(SW_SHOW);

        BOOL bKK = (auftrag.s.KZKDKK[0] == '1') ? TRUE : FALSE;
        int nKKCmdShow = bKK ? SW_SHOW : SW_HIDE;
        if (bKK)
        {
            m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_KRANKENKASSE));
        }
        GetDlgItem(IDC_STATIC_KK)->EnableWindow(bKK);
        GetDlgItem(IDC_STATIC_KK)->ShowWindow(nKKCmdShow);
        GetDlgItem(IDC_EDIT_KK_NETTO)->ShowWindow(nKKCmdShow);
        GetDlgItem(IDC_EDIT_KK_TAX)->ShowWindow(nKKCmdShow);
        GetDlgItem(IDC_EDIT_KK_BRUTTO)->ShowWindow(nKKCmdShow);

        BOOL bEH = (auftrag.s.SKDRETAILPERMIT[0] == '1') ? TRUE : FALSE;
        int nEHCmdShow = bEH ? SW_SHOW : SW_HIDE;
        if (bEH)
        {
            m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
            m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_MITUNDOHNE));
        }
        GetDlgItem(IDC_STATIC_EH)->EnableWindow(bEH);
        GetDlgItem(IDC_STATIC_EH)->ShowWindow(nEHCmdShow);
        GetDlgItem(IDC_EDIT_EH_NETTO)->ShowWindow(nEHCmdShow);
        GetDlgItem(IDC_EDIT_EH_TAX)->ShowWindow(nEHCmdShow);
        GetDlgItem(IDC_EDIT_EH_BRUTTO)->ShowWindow(nEHCmdShow);

        CString cAArt;
        cAArt = auftrag.s.KDAUFTRAGART;
        if (GetOrderType().IsOnlyEH(AeGetApp()->VzNr_Kunde(), cAArt))
        {
            m_ComboTyp.ResetContent();
            GetDlgItem(IDC_STATIC_KK)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_KK)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_KK_NETTO)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_KK_TAX)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_KK_BRUTTO)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_STATIC_EH)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_EH)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_EH_NETTO)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_EH_TAX)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_EH_BRUTTO)->ShowWindow(SW_SHOW);

            BOOL bEinzelhandelApo = GetAeUser().IsEinzelhandelApo() ? TRUE : FALSE;
            int nEinzelhandelApoCmdShow = bEinzelhandelApo ? SW_SHOW : SW_HIDE;
            if (bEinzelhandelApo)
            {
                m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_FREIVERKAUF));
                m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
                m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_MITUNDOHNE));
            }
            else
            {
                m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
            }
            GetDlgItem(IDC_STATIC_FV)->EnableWindow(bEinzelhandelApo);
            GetDlgItem(IDC_STATIC_FV)->ShowWindow(nEinzelhandelApoCmdShow);
            GetDlgItem(IDC_EDIT_FV_NETTO)->ShowWindow(nEinzelhandelApoCmdShow);
            GetDlgItem(IDC_EDIT_FV_TAX)->ShowWindow(nEinzelhandelApoCmdShow);
            GetDlgItem(IDC_EDIT_FV_BRUTTO)->ShowWindow(nEinzelhandelApoCmdShow);

            m_ComboTyp.SetCurSel(m_ComboTyp.FindString(-1,CResString::ex().getStrTblText(AETXT_EINZELHANDEL)));
        }

        if (cAArt == "RO") //bei RO kein EH
        {
            GetDlgItem(IDC_STATIC_EH)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_EH)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_EH_NETTO)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_EH_TAX)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_EH_BRUTTO)->ShowWindow(SW_HIDE);
            int ind = m_ComboTyp.FindString(-1,CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
            if (ind != CB_ERR)  //Eintrag gefunden
                m_ComboTyp.DeleteString(ind);
            ind = m_ComboTyp.FindString(-1,CResString::ex().getStrTblText(AETXT_MITUNDOHNE));
            if (ind != CB_ERR)  //Eintrag gefunden
                m_ComboTyp.DeleteString(ind);
        }
        CCSTREBATETYPE rtyp;
        rtyp.SetVertriebszentrumnr(m_VzNr);
        rtyp.SetKundennr(m_KndNr);
        rtyp.SelRebateType();
        m_sFVRabkonto = rtyp.GetRebatemethfreesale();
        m_sKKRabkonto = rtyp.GetRebatemethhealthf();
    }

    //Kopfinformationen Ausgeben
    m_lKdauftragNr = auftrag.s.KDAUFTRAGNR;
    AusgAufKopf(auftrag.s.IDFNR, auftrag.s.KDAUFTRAGNR, auftrag.s.ANZPOS, auftrag.s.WERTAUFTRAG, auftrag.s.WERTLIEFERUNG, auftrag.s.WERTZEILEN,
        auftrag.s.BALANCE, auftrag.s.BALANCE2, auftrag.s.WERTNETTO, auftrag.s.WERTRABATT);
    AusgAufWerteBG(auftrag.s.WERTNETTO_FV, auftrag.s.WERTTAX_FV, auftrag.s.WERTNETTO_KK, auftrag.s.WERTTAX_KK, auftrag.s.WERTNETTO_EH,
        auftrag.s.WERTTAX_EH, auftrag.s.WERTEXCLUSIVE);
    AusgAKBArt(auftrag.s.KDAUFTRAGART, auftrag.s.BUCHART, auftrag.s.KOART, auftrag.s.SUB_ORDER_TYPE, auftrag.s.BALANCE, auftrag.s.BALANCE2);

    AeGetApp()->SetView(VIEW_EING);

    if ((AeGetApp()->IsDE() || AeGetApp()->IsCH() || AeGetApp()->IsAT()))
    {
        ShowKritikView();
    }

    if (!AeGetApp()->IsBG())
    {
        ShowBranchView();
    }

    if (AeGetApp()->IsBG())
    {
        CWnd* pActive = GetActiveWindow();
        if (m_pDlgKnd->GetSafeHwnd() == 0)
        {
            m_pDlgKnd->m_sFilialnr = m_VzNr;
            m_pDlgKnd->m_lKndNr = m_KndNr;
            m_pDlgKnd->Create();    // Dialogfeld anzeigen
        }
        if (pActive != NULL)
        {
            pActive->SetActiveWindow();
        }
    }

    if (!AeGetApp()->IsBG() && !AeGetApp()->IsRS())
    {
        CStringArray s;
        s.SetSize(NUM_VB_FVIEW_COLUMNS);
        m_List_VB.DeleteAllItems();
        CZEITARTV av;
        av.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr_Kunde();
        CString zeitschluessel;
        av.s.FETCH_REL = 1;             //normaler Fetch

        BeginWaitCursor();

        for (;;)
        {
            av.Server(AafilSel_zeit_heute);
            av.s.FETCH_REL = 1;         //normaler Fetch
            if (av.rc == SRV_SQLNOTFOUND)
            {
                break;
            }
            //Ausgabe in die Listbox
            AllgEntfSpaces(av.s.ZEITSCHLUESSEL);
            s[COL_VB_FVIEW_VZ] = av.s.ZEITSCHLUESSEL;
            if (zeitschluessel != av.s.ZEITSCHLUESSEL)
            {
                zeitschluessel = av.s.ZEITSCHLUESSEL;
                s[COL_VB_FVIEW_VON1] = HHmmStringFromTimeLong(av.s.ZEITBEGIN);
                CString test = s[COL_VB_FVIEW_VON1];
                s[COL_VB_FVIEW_BIS1] = HHmmStringFromTimeLong(av.s.ZEITENDE);
                test = s[COL_VB_FVIEW_BIS1];
                s[COL_VB_FVIEW_VON2].Empty();
                s[COL_VB_FVIEW_BIS2].Empty();

                if (!CListCtrlHelper::AppendItem(m_List_VB, NUM_VB_FVIEW_COLUMNS, s))
                {
                    EndWaitCursor();
                    return;
                }
            }
            else
            {
                s[COL_VB_FVIEW_VON2] = HHmmStringFromTimeLong(av.s.ZEITBEGIN);
                CString test = s[COL_VB_FVIEW_VON2];
                s[COL_VB_FVIEW_BIS2] = HHmmStringFromTimeLong(av.s.ZEITENDE);
                test = s[COL_VB_FVIEW_BIS2];
                CListCtrlHelper::SetItemTexts(m_List_VB, NUM_VB_FVIEW_COLUMNS, s, 0, COL_VB_FVIEW_VON2);
            }
        }
        av.s.FETCH_REL = 0;
        av.Server(AafilSel_zeit_heute);
        EndWaitCursor();
    }

    //moeglichkeiten der automatischen Nachlieferung pruefen
    if (   AeGetApp()->IsAutoBuchungNachlieferung()
        && strcmp(auftrag.s.KDAUFTRAGART, "SV")
        && strcmp(auftrag.s.KDAUFTRAGART, "UW")
        && !AeGetApp()->IsNoNewLines() )
    {
        if (AeGetApp()->IsNoNewLines())
            return;
        CDNachlBearb dlgNachlBearb;
        CString cstr;
        GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->GetWindowText(dlgNachlBearb.m_VerbundZeitenKnd);
        GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cstr);
        dlgNachlBearb.m_lAuftrNr = atol(cstr);
        dlgNachlBearb.ptrDoc     = (CAeDoc*)GetDocument();
        dlgNachlBearb.ptrFView   = this;
        dlgNachlBearb.m_lKndNr   = m_KndNr;
        dlgNachlBearb.m_IdfNr    = m_IdfNr;
        dlgNachlBearb.m_VzNr     = m_VzNr;
        dlgNachlBearb.m_AArt     = auftrag.s.KDAUFTRAGART;
        dlgNachlBearb.DoModal();
    }

    if (AeGetApp()->IsBG())
    {
        if (GetOrderType().IsNatraAufArt(m_VzNr, auftrag.s.KDAUFTRAGART))
        {
            AeGetApp()->IsNatraEingabe = true;
        }
        else
        {
            AeGetApp()->IsNatraEingabe = false;
        }
        AeGetApp()->IsAuftNoPromo = GetOrderType().IsAufArtNoPromo(m_VzNr, auftrag.s.KDAUFTRAGART);
    }
    if (AeGetApp()->m_ProCenter.IsHiPathCalled() && !AeGetApp()->m_ProCenter.IsDirectCall()) //Direktanruf nicht protokollieren
    {
        AeGetApp()->m_OECustomerCalls.SetCscorderno(m_lKdauftragNr);
        AeGetApp()->m_OECustomerCalls.Update();
    }
}

BOOL CAeFView::NewOrder(long KndNr, short VZ)
{
    CString woher = "CAeFView::NewOrder";
    m_bKz_Nur_Liefber = FALSE;
    if (((CAeDoc*)GetDocument())->IsModified() && !AuftragSave())
    {
        return FALSE;
    }
    AeGetApp()->IsNoChangeCustomer = false;
    AeGetApp()->IsMSV3 = false;
    AeGetApp()->IsCMI = false;
    AeGetApp()->IsNoNewLines = false;
    GetDlgItem(IDC_STATIC_SUBORDER)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_SUBORDER_TYPE)->ShowWindow(SW_HIDE);
    AeGetApp()->AnzKopfFuss = 0;
    AeGetApp()->ActEKGrp = "";
    ClearView();
    if (!GetAeUser().IsAeUser())
        return FALSE;

    CAUFIE tm;
    tm.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    tm.Server(AafilIs_new_order_possi);
    if (!tm.s.ANZ_IE) //RZ hat Erfassung neuer Auftraege gesperrt
    {
        MsgBoxOK(AETXT_NEW_ORDER_NOT_POSS);
        return FALSE;
    }
    if (AeGetApp()->IsPF())  //keine neuen Auftraege fuer Prewhole Frankreich Kunden
    {
        CPREWHOLECST pcst;
        pcst.SetVertriebszentrumnr(VZ);
        pcst.SetKundennr(KndNr);
        if (!pcst.IsPrewholeCst())
        {
            MsgBoxOK(AETXT_NO_NEW_ORDER_PREWHOLE);
            return FALSE;
        }
    }

    AeGetApp()->VzNr_Kunde = VZ;
    CAUFTRAG auftrag;
    auftrag.s.KUNDENNR = KndNr;
    m_KndNr = KndNr;
    auftrag.s.VERTRIEBSZENTRUMNR = VZ;
    m_VzNr = VZ;
    BeginWaitCursor();
    auftrag.Server(AasrvNeworder, PIPE_AE_SRV);
    EndWaitCursor();
    if (auftrag.rc < SRV_OK)
        return FALSE;
    AeGetApp()->IsReOpen = false;
    m_IVC = 0L;
    m_lDatumBTM = 0L;
    m_CBTMLicense.Empty();
    // Wenn nicht wegen HiPath-Anruf eroeffnet, dann Pause an Hipath melden
    //if (!AeGetApp()->IsHiPathOpen())
    AeGetApp()->m_ProCenter.SetUserAtWork(woher, TRUE);
    // Wenn nicht wegen HiPath-Anruf eroeffnet, dann Pause an Hipath melden
    if (!AeGetApp()->m_ProCenter.IsHiPathOpen())
        AeGetApp()->m_ProCenter.SetHiPathOtherWork(TRUE);

    if (auftrag.s.FEHLER == -2) //Warnung beim Öffnen
    {
        MsgBoxOK(auftrag.s.BEMERKUNGEN);
        auftrag.s.BEMERKUNGEN[0] = '\0';
        auftrag.s.FEHLER = 0;
        GetDlgItem(IDC_STATIC_ZLN)->SetWindowText("0");
        m_PaymentType = "Z";
        OnABKArtDef(FALSE, FALSE, FALSE, TRUE);
    }
    InitOrder();
    m_EditMenge.SetFocus();
    InitOrderHead(auftrag, TRUE);  //Membervariablen und Kopfinformationen aktualisieren

    // Test Tourzeit
    if ((m_lDatumDD > 0) && !AeGetApp()->IsPF()) //in Prewhole Frankreich wird immer verzoegert
    {
        MsgBoxOK(IDP_NO_TOURID);
    }
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    long acttime = zeit.s.ZEIT/100;
    long acttimetour;
    AllgAddTimeSpan(zeit.s.ZEIT, AeGetApp()->DurchlaufZeit()*60, &acttimetour);
    acttimetour = acttimetour/100;  //Ohne Sekunden
    long tourtime = atol(auftrag.s.TOURID)/100;
    if (acttime < tourtime && tourtime < acttimetour)
    {
        MsgBoxOK(IDP_TOUR_VORBEI);
    }

    SetTimerTour(tourtime * 100); //Ronnie

    // StandardAuftragsBuchungsart für den Kunden
    CString cAArt;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
    CString cBArt;
    GetDlgItem(IDC_STATIC_BA)->GetWindowText(cBArt);
    CString cKArt;
    GetDlgItem(IDC_STATIC_KA)->GetWindowText(cKArt);
    GetDlgItem(IDC_STATIC_SUBORDER)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_SUBORDER_TYPE)->ShowWindow(SW_HIDE);

    if (cAArt != "NO" || cBArt != "0" || cKArt != "0") //keine Standardauftragsart
    {
        if (cAArt != m_KStdAufArt || cBArt != m_KStdBuArt || cKArt != m_KStdKoArt)
        {
            //NO00 fuer Kunden vermutlich verboten
            MsgBoxOK(IDS_KEINE_STD_AART);
            OnABKArtDef();
            if (m_lTenderNo > 0)
            {
                CDTenderOrder dlgTenderOrder;
                dlgTenderOrder.ptrDoc = (CAeDoc*)GetDocument();
                dlgTenderOrder.m_lKndNr = m_IdfNr;
                dlgTenderOrder.m_lTenderNo = m_lTenderNo;
                dlgTenderOrder.DoModal();
            }
            else if (m_sServType > 0)
            {
                CDServiceOrder dlgServiceOrder;
                dlgServiceOrder.m_ptrDoc = (CAeDoc*)GetDocument();
                dlgServiceOrder.m_lKndNr = m_IdfNr;
                dlgServiceOrder.m_sServType = m_sServType;
                dlgServiceOrder.DoModal();
            }
            else if (cAArt == "MP")
            {
                CDProductPromo dlgProductPromo;
                dlgProductPromo.m_ptrDoc = (CAeDoc*)GetDocument();
                dlgProductPromo.m_lCustomerno = m_IdfNr;
                dlgProductPromo.m_sBranchno = m_VzNr;
                dlgProductPromo.DoModal();
            }
        }
        else
        {
            //Kunde hat Standardauftragsart
            if (GetOrderType().IsMustSubOrder(AeGetApp()->VzNr(), m_KStdAufArt))
            {
                OnABKArtDef(TRUE);
            }
            else
            {
                CString str = m_KStdAufArt + m_KStdKoArt + m_KStdBuArt;
                CString cstr;
                cstr.Format(CResString::ex().getStrTblText(IDP_INFO_STD_KOMB_AKB_ART), str.GetString());
                MsgBoxOK(cstr);
            }
        }
    }
    // StandardAuftragsBuchungsart für den Arbeitsplatz
    else if (AeGetApp()->IsStdAKBArt())
    {
        AusgAKBArt(AeGetApp()->StdAuftArt(), AeGetApp()->StdBuchArt(), AeGetApp()->StdKommArt());
        OnABKArtDef(TRUE);
    }
    if (m_bKndMussKopfBem) // Auftragskopfbemerkung erzwingen
    {
        OnABKArtDef(FALSE, TRUE);
    }
    if (AeGetApp()->IsMatchCode())
    {
        SetFocusFullSelection(m_EditMatchCode);
    }
    CString text;
    text.Format("OrderNo %d", auftrag.s.KDAUFTRAGNR);
    AeGetApp()->m_AeLogging.WriteLine(1, "aefview.cpp", "NewOrder", text);
    return TRUE;
}

BOOL CAeFView::OpenOrder(long AuftrNr)
{
    CString woher = "CAeFView::OpenOrder";

    m_bKz_Nur_Liefber = FALSE;
    if (((CAeDoc*)GetDocument())->IsModified() && !AuftragSave())
    {
        return FALSE;
    }

    AeGetApp()->IsNoNewLines = false;
    AeGetApp()->IsNoChangeCustomer = false;
    if (AeGetApp()->IsMSV3())
    {
        if (!GetAeUser().IsMSV3bearb() && !GetAeUser().IsMSV3bearbNo())
        {
            MsgBoxOK(AETXT_NO_MSV3);
            return FALSE;
        }
        CCHECKORDERLABEL label;
        label.SetKdauftragnr(AuftrNr);
        label.SelLabelType();
        if (label.GetOrderlabeltyp() == 2 && !GetAeUser().IsMSV3bearb())
        {
            MsgBoxOK(AETXT_NO_MSV3);
            return FALSE;
        }
        if (label.GetOrderlabeltyp() == 2)
        {
            AeGetApp()->IsNoNewLines = true;
        }
    }

    //Check if is CMI order (AA = DG) and user is able to change CMI orders
    if (!GetAeUser().IsAbleToChangeCMIOrder() && AeGetApp()->IsCMI()) //TODO DZ
    {
        MsgBoxOK(AETXT_NO_CMI);
        return FALSE;
    }

    AeGetApp()->AnzKopfFuss = 0;
    ClearView();
    ((CAeDoc *)GetDocument())->DelPosListe();           //Loeschen der Positionsliste
    if (!GetAeUser().IsAeUser())
        return FALSE;
    CAUFTRAG auftrag;
    auftrag.s.KDAUFTRAGNR = AuftrNr;
    BeginWaitCursor();
    auftrag.Server(AasrvOpenorder, PIPE_AE_SRV);
    if (auftrag.rc < SRV_OK)
    {
        EndWaitCursor();
        return FALSE;
    }

    AeGetApp()->IsReOpen = true;

    m_IVC = auftrag.s.RELATIONNO;
    m_lDatumBTM = auftrag.s.DATUMBTM;
    AllgEntfSpaces(auftrag.s.BTMFORMULARNR);
    m_CBTMLicense = auftrag.s.BTMFORMULARNR;
    AeGetApp()->m_ProCenter.SetUserAtWork(woher, TRUE);
    if (!AeGetApp()->m_ProCenter.IsHiPathOpen())
        AeGetApp()->m_ProCenter.SetHiPathOtherWork(TRUE);
    AeGetApp()->VzNr_Kunde = auftrag.s.VERTRIEBSZENTRUMNR;
    CKNDSEL kndsel;
    kndsel.s.KUNDENNR = auftrag.s.KUNDENNR;
    kndsel.s.VERTRIEBSZENTRUMNR = auftrag.s.VERTRIEBSZENTRUMNR;
    kndsel.s.SKDKUNDEAEGESPERRT[0] = '1';
    kndsel.s.SKDKUNDEAEGESPERRT[1] = '\0';
    kndsel.Server(AakundeSel_kndnr);
    if ((kndsel.rc < SRV_OK) || (kndsel.s.ORIGINALFILIALNR == 0))
    {
        SetOrgFilNr(kndsel.s.VERTRIEBSZENTRUMNR);
    }
    else
    {
        SetOrgFilNr(kndsel.s.ORIGINALFILIALNR);
    }

    InitOrder();
    if (auftrag.s.DAFUEART[0] == 'P')
        m_bPara = true;
    if (auftrag.s.FEHLER == -2) //Warnung beim Öffnen
    {
        MsgBoxOK(auftrag.s.BEMERKUNGEN);  //Bemerkung für Fehlermeldung verwendet
        auftrag.s.FEHLER = 0;
        auftrag.Server(AasrvGetOrderInfo, PIPE_AE_SRV); //Bemerkung aktualisieren
    }
    if (auftrag.s.ZUGRUND[ZU_KREDITLIMIT] == '1')
        MsgBoxOK(AETXT_KREDITLIMIT);
    else if (auftrag.s.ZUGRUND[ZU_INTERNET] == '1')
        MsgBoxOK(AETXT_INTERNET);
    else if (auftrag.s.ZUGRUND[ZU_BTM] == '1')
        MsgBoxOK(AETXT_BTM_AUF);
    else if (auftrag.s.ZUGRUND[ZU_OV] == '1')
        MsgBoxOK(AETXT_OV_AUF);
    else if (auftrag.s.ZUGRUND[ZU_HIGH_VALUE] == '1')
        MsgBoxOK(AETXT_HV_AUF);

    FillPosList();      //Positionen holen
    if (AeGetApp()->IsIBTdirect())
    {
        CAUFTRAG checkvb;
        checkvb.s.KDAUFTRAGNR = AuftrNr;
        checkvb.s.VERTRIEBSZENTRUMNR = auftrag.s.VERTRIEBSZENTRUMNR;
        checkvb.Server(AasrvIBTOrderPosDone, PIPE_AE_SRV);
        AeGetApp()->IsNoChangeCustomer = (checkvb.rc != SRV_OK);
    }
    if (auftrag.s.BATCHSCHREIBEN == 1) //keine Kundenänderung bei Verbundauftrag
    {
        AeGetApp()->IsNoChangeCustomer = true;
    }

    EndWaitCursor();

    //Maske anzeigen
    m_EditMenge.SetFocus();

    InitOrderHead(auftrag);   //Membervariablen und Kopfinformationen aktualisieren

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    long acttime = zeit.s.ZEIT/100;
    long acttimetour;
    AllgAddTimeSpan(zeit.s.ZEIT, AeGetApp()->DurchlaufZeit()*60, &acttimetour);
    acttimetour = acttimetour / 100;  //Ohne Sekunden
    long tourtime = atol(auftrag.s.TOURID) / 100;

    SetTimerTour(tourtime * 100); //Ronnie

    //DAFUE-Nachbearbeitung
    if (m_bDafueKz || auftrag.s.STATUS == ORD_DAFUE_FEHLER || auftrag.s.STATUS == ORD_DAFUE_RR || auftrag.s.KZDEFOFLOW[0] == '1')
    {
        m_bDefSelDfFrText = TRUE;
        if (m_bPara || AeGetApp()->IsAnzeigeAlleDef())
        {
            m_bDefSelDfDef = TRUE;
            m_bDefSelVerbund = TRUE;
        }
        if (auftrag.s.STATUS == ORD_DAFUE_RR)
        {
            MsgBoxOK(IDP_BITTE_RUECKRUF);
        }
        if (acttime < tourtime && tourtime < acttimetour)
        {
            MsgBoxOK(IDP_TOUR_VORBEI);
        }

        if (auftrag.s.KZDEFOFLOW[0] == '1')
        {
            MsgBoxOK(IDS_DEF_WERT_UEBERS,MB_ICONINFORMATION);
            m_bDefSelDfDef = TRUE; //Defekte werden mit angezeigt
        }
        CDAufTxt dlgAufTxt;
        dlgAufTxt.m_bSeraNachBearb = TRUE;
        dlgAufTxt.DoModal();
        if (m_bDefekte)
            OnBearbDefnachbea();
    }
    else
    {
        if (acttime < tourtime && tourtime < acttimetour)
        {
            MsgBoxOK(IDP_TOUR_VORBEI);
        }
        CDAufTxt dlgAufTxt;
        dlgAufTxt.UpdateLists(false);
    }
    GetDlgItem(IDC_STATIC_KOPF_FUSS)->ShowWindow(AeGetApp()->AnzKopfFuss() == 0 ? SW_HIDE : SW_SHOW);

    if (AeGetApp()->IsMatchCode())
    {
        SetFocusFullSelection(m_EditMatchCode);
    }
    CString cAufart;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAufart);
    CAUFPOSBUCH aufposbuch;
    for (;;)
    {
        aufposbuch.Server(AasrvSelpos, PIPE_AE_SRV);
        if (aufposbuch.rc != SRV_OK)
            break;
        ((CAeDoc*)GetDocument())->AddPosition(aufposbuch.s);
    }
    ((CAeDoc*)GetDocument())->m_bAllItemsInList = true;
    if (m_lTenderNo > 0)
    {
        CDTenderOrder dlgTenderOrder;
        dlgTenderOrder.ptrDoc = (CAeDoc*)GetDocument();
        dlgTenderOrder.m_lKndNr = m_KndNr;
        dlgTenderOrder.m_lTenderNo = m_lTenderNo;
        dlgTenderOrder.DoModal();
    }
    else if (m_sServType > 0)
    {
        CDServiceOrder dlgServiceOrder;
        dlgServiceOrder.m_ptrDoc = (CAeDoc*)GetDocument();
        dlgServiceOrder.m_lKndNr = m_KndNr;
        dlgServiceOrder.m_sServType = m_sServType;
        dlgServiceOrder.DoModal();
    }
    else if (cAufart == "MP")
    {
        CDProductPromo dlgProductPromo;
        dlgProductPromo.m_ptrDoc = (CAeDoc*)GetDocument();
        dlgProductPromo.m_lCustomerno = m_IdfNr;
        dlgProductPromo.m_sBranchno = m_VzNr;
        dlgProductPromo.DoModal();
    }
    else
    {
        ((CAeDoc*)GetDocument())->DelPosListe();           //Loeschen der Positionsliste
    }
    if (AeGetApp()->IsBG())  //in BG check promotions
    {
        if (m_cZuGrund.GetAt(ZU_NO_CICS) == '1')
        {
            AeGetApp()->ClearZUGrund(ZU_NO_CICS);
            m_cZuGrund.SetAt(ZU_NO_CICS, '0');
        }
        m_cZuGrund = auftrag.s.ZUGRUND;
        if (m_cZuGrund.GetAt(ZU_WAHL_STELLER) == '1')
        {
            MsgBoxOK(AETXT_STELLER_WAHL);
        }
        OnBearbBulgaria(m_cZuGrund);
    }
    CCHECKDFREASON dfreason;
    dfreason.SetKdauftragnr(AuftrNr);
    if (!dfreason.SelEvent())
    {
        if (dfreason.GetEventcode() != 0)
        {
            ppString reason;
            if (dfreason.GetEventcode() == 1) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_1);
            else if (dfreason.GetEventcode() == 2) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_2);
            else if (dfreason.GetEventcode() == 3) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_3);
            else if (dfreason.GetEventcode() == 4) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_4);
            else if (dfreason.GetEventcode() == 5) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_5);
            else if (dfreason.GetEventcode() == 6) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_6);
            else if (dfreason.GetEventcode() == 7) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_7);
            else if (dfreason.GetEventcode() == 8) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_8);
            else if (dfreason.GetEventcode() == 9) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_9);
            else if (dfreason.GetEventcode() == 10) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_10);
            else if (dfreason.GetEventcode() == 11) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_11);
            else if (dfreason.GetEventcode() == 12) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_12);
            else if (dfreason.GetEventcode() == 13) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_13);
            else if (dfreason.GetEventcode() == 14) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_14);
            else if (dfreason.GetEventcode() == 15) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_15);
            else if (dfreason.GetEventcode() == 16) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_16);
            else if (dfreason.GetEventcode() == 17) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_17);
            else if (dfreason.GetEventcode() == 18) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_18);
            else if (dfreason.GetEventcode() == 19) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_19);
            else if (dfreason.GetEventcode() == 20) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_20);
            else if (dfreason.GetEventcode() == 21) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_21);
            else if (dfreason.GetEventcode() == 22) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_22);
            else if (dfreason.GetEventcode() == 23) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_23);
            else if (dfreason.GetEventcode() == 24) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_24);
            else if (dfreason.GetEventcode() == 25) reason = CResString::ex().getStrTblText(AETXT_EVENTREASON_25);
            else reason = CResString::ex().getStrTblText(IDS_UNKNOWN);
            MsgBoxOK(reason);
        }
    }
    if (m_bNoMorePos)
    {
        MsgBoxOK(AETXT_NO_NEW_POS);
    }
    CString text;
    text.Format("OrderNo %d", auftrag.s.KDAUFTRAGNR);
    AeGetApp()->m_AeLogging.WriteLine(1, "aefview.cpp", "OpenOrder", text);

    return TRUE;
}

void CAeFView::FillPosList()
{
    CAUFPOSBUCH aufposbuch;

    BeginWaitCursor();
    ((CAeDoc*)GetDocument())->DelPosListe();            //Loeschen der Positionsliste
    m_bDafueKz = false;
    m_bDefekte = false;

    int fkt_nr = AeGetApp()->IsBG() || AeGetApp()->IsRS() ? AasrvSelpos : AasrvSeldeforalphapos;

    for (;;)
    {
        aufposbuch.Server(fkt_nr, PIPE_AE_SRV);
        if (aufposbuch.rc != SRV_OK)
            break;
        if (aufposbuch.s.DAFUEART[0] == ITEM_ART_PARA)
            m_bPara = true;
        if (aufposbuch.s.KZNACHBEARB[0] == '1')
            m_bDafueKz = true;

        if (   ((aufposbuch.s.KZFREITEXT[0] == '1') && (m_sServType == 0))
            || (aufposbuch.s.KZLIMITCHK[0] == '1')
            || (aufposbuch.s.KZDEFEKT[0] == '1') )
        {
            m_bDefekte = true;
        }

        ((CAeDoc*)GetDocument())->AddPosition(aufposbuch.s);
    }
    ((CAeDoc*)GetDocument())->m_bAllItemsInList = false;
    EndWaitCursor();
}

void CAeFView::AusgAKBArt
(
    CString cAArt,
    CString cBArt,
    CString cKArt,
    CString cSubOrder,
    double  dBalance,
    double  /*dBalance2*/
)
{
    GetDlgItem(IDC_STATIC_AA)->SetWindowText(cAArt);
    GetDlgItem(IDC_STATIC_BA)->SetWindowText(cBArt);
    GetDlgItem(IDC_STATIC_KA)->SetWindowText(cKArt);
    GetDlgItem(IDC_STATIC_SUBORDER_TYPE)->SetWindowText(cSubOrder);
    cSubOrder.Trim();
    int nSubOrderCmdShow = cSubOrder.IsEmpty() ? SW_HIDE : SW_SHOW;
    GetDlgItem(IDC_STATIC_SUBORDER)->ShowWindow(nSubOrderCmdShow);
    GetDlgItem(IDC_STATIC_SUBORDER_TYPE)->ShowWindow(nSubOrderCmdShow);

    BOOL bPrice;

    if (GetOrderType().IsFreePrice(m_VzNr, cAArt))
    {
        bPrice = TRUE;
    }
    else if (AeGetApp()->IsRS())
    {
        bPrice = GetAeUser().IsFreePrice() ? TRUE : FALSE;
    }
    else
    {
        bPrice = FALSE;
    }

    int nPriceCmdShow;
    DWORD dwPriceRemove;
    DWORD dwPriceAdd;
    if (bPrice)
    {
        nPriceCmdShow = SW_SHOW;
        dwPriceRemove = 0;
        dwPriceAdd = LVS_SHOWSELALWAYS;
    }
    else
    {
        nPriceCmdShow = SW_HIDE;
        dwPriceRemove = LVS_SHOWSELALWAYS;
        dwPriceAdd = 0;
    }
    GetDlgItem(IDC_COMBO_FREE_PRICE)->EnableWindow(bPrice);
    GetDlgItem(IDC_COMBO_FREE_PRICE)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_PREIS)->EnableWindow(bPrice);
    GetDlgItem(IDC_STATIC_PREIS)->ShowWindow(SW_SHOW);
    m_ListCtl.ModifyStyle(dwPriceRemove, dwPriceAdd);

    BOOL bAArtRO = (cAArt == "RO") ? TRUE : FALSE;
    int nROCmdShow = bAArtRO ? SW_SHOW : SW_HIDE;
    if (bAArtRO)
    {
        char text[81];
        sprintf(text, "%.2f", dBalance);
        GetDlgItem(IDC_STATIC_RABATTWERT)->SetWindowText(text);
    }
    else
    {
        GetDlgItem( IDC_STATIC_RABATTWERT2 )->EnableWindow(FALSE);
        GetDlgItem( IDC_STATIC_RABATTWERT2 )->ShowWindow(SW_HIDE);
    }
    GetDlgItem(IDC_STATIC_RABATT_WERT)->EnableWindow(bAArtRO);
    GetDlgItem(IDC_STATIC_RABATT_WERT)->ShowWindow(nROCmdShow);
    GetDlgItem(IDC_STATIC_RABATTWERT)->EnableWindow(bAArtRO);
    GetDlgItem(IDC_STATIC_RABATTWERT)->ShowWindow(nROCmdShow);

    Invalidate();
    UpdateWindow();
}

void CAeFView::AusgAufKopf
(
    long    /*KndNr*/,
    long    AufNr,
    long    AnzPos,
    double  WertAuftr,
    double  WertLif,
    double  WertZln,
    double  dBalance,
    double  dBalance2,
    double  dRechwert,
    double  dRechwertRab
)
{
    CString cstr;
    char text[81];
    m_bKz_Kunde_Verbund = false;

    CKNDINF kndinf;
    kndinf.s.IDFNR               = m_IdfNr;
    kndinf.s.KUNDENNR            = m_KndNr;
    kndinf.s.VERTRIEBSZENTRUMNR  = m_VzNr;
    CKNDSCHALTER kndschalter;
    kndschalter.s.IDFNR               = m_IdfNr;
    kndschalter.s.KUNDENNR            = m_KndNr;
    kndschalter.s.VERTRIEBSZENTRUMNR  = m_VzNr;
    BeginWaitCursor();
    kndinf.Server(AakundeSel_knd_info);
    kndschalter.Server(AakundeSel_kndschalter);
    CTM zeit;
    zeit.Server(AafilGetdatetime);

    AeGetApp()->SetFilialNrActual(kndinf.s.FILIALNR);
    if ((kndinf.s.FILIALNR != AeGetApp()->VzNr()) && (AeGetApp()->VzNr() == 51))
    {
        AeGetApp()->FilialNr = AeGetApp()->VzNr(); // speziell fuer Nahverbund MA/NH
    }

    if (   AeGetApp()->IsBTMextra()
        && (zeit.s.ZEIT > AeGetApp()->TimeNoBTM() * 100)
        && (AeGetApp()->TimeNoBTM() != 0)
        && (kndinf.s.FILIALNR != AeGetApp()->FilialNr()) )
    {
        AeGetApp()->IsKundeKeineBTM = true;
    }
    else
    {
        AeGetApp()->IsKundeKeineBTM = false;
    }

    if (kndinf.s.VERBUNDKUNDE[0] == '1' || kndinf.s.VERBUNDKUNDE[0] == '3' || kndinf.s.VERBUNDKUNDE[0] == '4')
        m_bKz_Kunde_Verbund = true;
    if (!m_bKz_Kunde_Verbund)
        GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->SetWindowText(CResString::ex().getStrTblText(AETXT_KZ_NEIN));

    else if (kndschalter.s.SKDVERBUNDGANZ[0] == '1')
        GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->SetWindowText(CResString::ex().getStrTblText(AETXT_KZ_JA));
    else
    {
        CZEITARTV zeitartv;
        sprintf(zeitartv.s.ZEITSCHLUESSEL, "%ld", kndinf.s.IDFNR);
        zeitartv.s.VERTRIEBSZENTRUMNR = m_VzNr;
        zeitartv.s.FETCH_REL = 1;  // normaler Fetch
        cstr.Empty();
        for (int i = 0; i < 2; i++)
        {
            zeitartv.Server(AafilSel_verbund);
            if (zeitartv.rc != SRV_OK)
                break;
            if (i > 0)
                cstr += " / ";
            ppGTimeLongToCharHHMM(zeitartv.s.ZEITBEGIN, text);
            cstr += text;
            cstr += '-';
            ppGTimeLongToCharHHMM(zeitartv.s.ZEITENDE, text);
            cstr += text;
        }
        GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->SetWindowText(cstr);
        cstr.Empty();
        zeitartv.s.FETCH_REL = 0;  // Schliessen cursor
        zeitartv.Server(AafilSel_verbund);
    }
    EndWaitCursor();

    m_KStdAufArt.Format("%2.2s",kndinf.s.STDAUFKOBUART);
    m_KStdKoArt     = kndinf.s.STDAUFKOBUART[2];
    m_KStdBuArt     = kndinf.s.STDAUFKOBUART[3];
    m_bKndMussKopfBem   = kndschalter.s.SKDMUSSKOPF[0]        == '1' ? true : false;
    m_bKndSchwerpunk3   = kndschalter.s.SKDSCHWERPUNKT3[0]    == '1' ? true : false;
    m_bKndSchwerpunk5   = kndschalter.s.SKDSCHWERPUNKT5[0]    == '1' ? true : false;

    sprintf(text, "%ld", kndinf.s.IDFNR);
    GetDlgItem(IDC_STATIC_IDF_NR)->SetWindowText(text);
    GetDlgItem(IDC_STATIC_WERTIG)->SetWindowText(kndinf.s.KZKDKLASSE);
    GetDlgItem(IDC_STATIC_INHABER)->SetWindowText(kndinf.s.NAMEINHABER);
    GetDlgItem(IDC_STATIC_APOTHEKE)->SetWindowText(kndinf.s.NAMEAPO);
    AllgEntfFirstSpaces(kndinf.s.POSTLEITZAHL);
    GetDlgItem(IDC_STATIC_PLZ)->SetWindowText(kndinf.s.POSTLEITZAHL);
    AllgEntfSpaces(kndinf.s.KUNDETEXT);
    GetDlgItem(IDC_STATIC_KNDTEXT)->SetWindowText(kndinf.s.KUNDETEXT);
    GetDlgItem(IDC_STATIC_ORT)->SetWindowText(kndinf.s.ORT);
    GetDlgItem(IDC_STATIC_TEL)->SetWindowText(kndinf.s.TELNR);
    AllgEntfSpaces(kndinf.s.TELNRDAFUE);
    if (strlen(kndinf.s.TELNRDAFUE) == 0)
    {
        GetDlgItem(IDC_STATIC_TEL_DAFUE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_TEL_DAFUE_NR)->ShowWindow(SW_HIDE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_TEL_DAFUE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_TEL_DAFUE_NR)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_TEL_DAFUE_NR)->SetWindowText(kndinf.s.TELNRDAFUE);
    }
    GetDlgItem(IDC_STATIC_KOPF_FUSS)->ShowWindow((AeGetApp()->AnzKopfFuss() == 0) ? SW_HIDE : SW_SHOW);
    cstr.Format("%s  /  %d", kndinf.s.TELKURZWAHL, kndinf.s.FILIALNR);
    GetDlgItem(IDC_STATIC_TEL_KW)->SetWindowText(cstr);
    if      (!strcmp(kndinf.s.DAFUESYSTEM,"01")) cstr = CResString::ex().getStrTblText(AETXT_PARA);
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"02")) cstr = CResString::ex().getStrTblText(AETXT_SERA);
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"00")) cstr = CResString::ex().getStrTblText(AETXT_PHON);
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"03")) cstr = CResString::ex().getStrTblText(AETXT_MSV3);
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"04")) cstr = CResString::ex().getStrTblText(AETXT_XML);
    else                                    cstr = kndinf.s.DAFUESYSTEM;
    GetDlgItem(IDC_STATIC_DAFUE_TYP)->SetWindowText(cstr);
    GetDlgItem(IDC_STATIC_AA)->SetWindowText("NO");
    GetDlgItem(IDC_STATIC_BA)->SetWindowText("0");
    GetDlgItem(IDC_STATIC_KA)->SetWindowText("0");
    sprintf(text, "%ld", AufNr);
    GetDlgItem(IDC_STATIC_AUFTR_NR)->SetWindowText(text);
    CString tour;
    if (atol(m_Tour))
    {
        char str[81];
        strncpy(str, m_Tour, 2);
        str[2] = '\0';
        tour = str;
        tour += ":";
        strncpy(str, m_Tour.Right(4), 2);
        str[2] = '\0';
        tour += str;
        tour += " / ";
        strncpy(str, m_Tour.Right(2), 2);
        str[2] = '\0';
        tour += str;
    }
    else
        tour = "";
    GetDlgItem(IDC_STATIC_TOUR)->SetWindowText(tour);
    AusgAufWerte(AnzPos, WertAuftr, WertLif, WertZln, dBalance, dBalance2, dRechwert, dRechwertRab);
}

void CAeFView::AusgAufWerte     //Ausgabe der Auftragswerte
(
    long    AnzPos,
    double  WertAuftr,
    double  WertLif,
    double  WertZln,
    double  dBalance,
    double  dBalance2,
    double  dRechwert,
    double  dRechwertRab
)
{
    char text[81];

    sprintf(text, "%ld", AnzPos);
    GetDlgItem(IDC_STATIC_ZLN)->SetWindowText(text);
    sprintf(text, "%.2f", WertAuftr);
    GetDlgItem(IDC_STATIC_AW)->SetWindowText(text);
    sprintf(text, "%.2f", WertLif);
    GetDlgItem(IDC_STATIC_LIF_WERT)->SetWindowText(text);
    sprintf(text, "%.2f", WertZln);
    GetDlgItem(IDC_STATIC_DZW)->SetWindowText(text);
    sprintf(text, "%.2f", dBalance);
    GetDlgItem(IDC_STATIC_RABATTWERT)->SetWindowText(text);
    sprintf(text, "%.2f", dBalance2);
    GetDlgItem(IDC_STATIC_RABATTWERT2)->SetWindowText(text);
    sprintf(text, "%.2f", dRechwert);
    GetDlgItem(IDC_STATIC_RECHWERT)->SetWindowText(text);
    if (AeGetApp()->IsHR())
    {
        sprintf(text, "%.2f", dRechwert);
        GetDlgItem(IDC_STATIC_NETTOWERT)->SetWindowText(text);
    }
    sprintf(text, "%.2f", dRechwertRab);
    GetDlgItem(IDC_STATIC_RECHWERT_RAB)->SetWindowText(text);
}

void CAeFView::AusgAufWerteBG       //Ausgabe der Auftragswerte
(
    double  dWertNettoFV,
    double  dWertTaxFV,
    double  dWertNettoKK,
    double  dWertTaxKK,
    double  dWertNettoEH,
    double  dWertTaxEH,
    double  dWertExclusive
)
{
    double gesamt;
    char text[81];

    sprintf(text, "%.2f", dWertNettoFV);
    GetDlgItem(IDC_EDIT_FV_NETTO)->SetWindowText(text);
    sprintf(text, "%.2f", dWertTaxFV);
    GetDlgItem(IDC_EDIT_FV_TAX)->SetWindowText(text);
    sprintf(text, "%.2f", dWertNettoFV + dWertTaxFV);
    GetDlgItem(IDC_EDIT_FV_BRUTTO)->SetWindowText(text);

    sprintf(text, "%.2f", dWertNettoKK);
    GetDlgItem(IDC_EDIT_KK_NETTO)->SetWindowText(text);
    sprintf(text, "%.2f", dWertTaxKK);
    GetDlgItem(IDC_EDIT_KK_TAX)->SetWindowText(text);
    sprintf(text, "%.2f", dWertNettoKK + dWertTaxKK);
    GetDlgItem(IDC_EDIT_KK_BRUTTO)->SetWindowText(text);

    sprintf(text, "%.2f", dWertNettoEH);
    GetDlgItem(IDC_EDIT_EH_NETTO)->SetWindowText(text);
    sprintf(text, "%.2f", dWertTaxEH);
    GetDlgItem(IDC_EDIT_EH_TAX)->SetWindowText(text);
    sprintf(text, "%.2f", dWertNettoEH + dWertTaxEH);
    GetDlgItem(IDC_EDIT_EH_BRUTTO)->SetWindowText(text);

    gesamt = (m_sFVRabkonto && !m_bNoRabattKonto) ? dWertNettoFV + dWertTaxFV : dWertNettoFV;
    gesamt += (m_sKKRabkonto && !m_bNoRabattKonto) ? dWertNettoKK + dWertTaxKK : dWertNettoKK;
    gesamt += dWertNettoEH;
    sprintf(text, "%.2f", gesamt);
    GetDlgItem(IDC_EDIT_GESAMT)->SetWindowText(text);

    sprintf(text, "%.2f", dWertExclusive);
    GetDlgItem(IDC_EDIT_EXCLUSIVE)->SetWindowText(text);
}

void CAeFView::ClearView()
{
    ClearInput();

    //Anzeige letzte Zeile
    GetDlgItem(IDC_STATIC_MENGE)->SetWindowText("");
    GetDlgItem(IDC_STATIC_EINH)->SetWindowText("");
    GetDlgItem(IDC_STATIC_BEZEI)->SetWindowText("");
    GetDlgItem(IDC_STATIC_NATRAB)->SetWindowText("");
    GetDlgItem(IDC_STATIC_ABGEB)->SetWindowText("");
    GetDlgItem(IDC_STATIC_DARR)->SetWindowText("");
    ArtAnschrAusg("", "", "", "");
    m_ListCtl.DeleteAllItems();
}

void CAeFView::ClearInput()
{
    m_EditZusatz.SetWindowText("");
    m_EditNormPackung.SetWindowText("");
    m_EditPackGr.SetWindowText("");
    m_EditNatRab.SetWindowText("");
    m_EditMenge.SetWindowText("");
    m_EditDarr.SetWindowText("");
    m_EditMatchCode.SetWindowText("");
    m_EditBemerkung.SetWindowText("");
    m_EditArtNr.SetWindowText("");
    m_EditHC.SetWindowText("");
}

void CAeFView::OnKeydownListctrlArt(NMHDR* pNMHDR, LRESULT* pResult)
{
    int pos;
    OnKeydownList(pNMHDR, pResult, m_ListCtl, pos, false);

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (pLVKeyDow->wVKey == VK_UP)
    {
        if (pos >= 0)
        {
            --pos;
            if (pos < 0) pos = 0;
            CString CStr = m_ListCtl.GetItemText(pos, COL_FVIEW_PZN);
            CString price(m_ListCtl.GetItemText(pos, COL_FVIEW_PREIS));
            FillFreePrice(atol(CStr), price);
        }
        return;                                     //Message wird weitergeleitet
    }
    if (pLVKeyDow->wVKey == VK_DOWN)
    {
        if (pos >= 0)
        {
            CListCtrlHelper::StepDownLinePosition(pos, m_ListCtl.GetItemCount());
            CString CStr = m_ListCtl.GetItemText(pos, COL_FVIEW_PZN);
            CString price(m_ListCtl.GetItemText(pos, COL_FVIEW_PREIS));
            FillFreePrice(atol(CStr), price);
        }
        return;                                     //Message wird weitergeleitet
    }
    if (CLetterMan::InRange(pLVKeyDow->wVKey, m_ListCtl.GetItemCount()))
    {
        int pos = pLVKeyDow->wVKey - AeGetApp()->Letter_A();
        MarkListPos(pos);
        if ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000)
        {
            CString cstr;
            CDArtInf dlgArtInf(SelListPos(cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr));
            dlgArtInf.SetOrgFilialNr(m_OrgFilNr);
            dlgArtInf.SetKndNr(m_KndNr);
            dlgArtInf.m_CBemerkungKond.Empty();

            if (m_bKndSchwerpunk3)
                dlgArtInf.m_CBemerkungKond = CResString::ex().getStrTblText(AETXT_ARB_KREIS_AKTUELL);
            else
                dlgArtInf.m_bNoPriceGroup2 = TRUE;

            if (m_bKndSchwerpunk5)
            {
                if (!dlgArtInf.m_CBemerkungKond.IsEmpty())
                {
                    dlgArtInf.m_CBemerkungKond += " / ";
                }
                dlgArtInf.m_CBemerkungKond += CResString::ex().getStrTblText(AETXT_DIABETES);
            }
            else dlgArtInf.m_bNoPriceGroup3 = TRUE;
            dlgArtInf.DoModal();
        }
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == 'N')
    {
        m_ComboBuchStat.SetCurSel(0);
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == AeGetApp()->Letter_Z())
    {
        m_ComboBuchStat.SetCurSel(1);
        *pResult = 1L;
        return;
    }
    if (   (pLVKeyDow->wVKey >= '0' && pLVKeyDow->wVKey <= '9')
        || ( pLVKeyDow->wVKey >= VK_NUMPAD0 && pLVKeyDow->wVKey <= VK_NUMPAD9) )
    {
        if (AeGetApp()->IsBG())
        {
            if (   pLVKeyDow->wVKey == '0'
                || pLVKeyDow->wVKey == VK_NUMPAD0)
            {
                m_ComboTyp.SetCurSel(0);
                SetPrices();
            }
            else if (   pLVKeyDow->wVKey == '1'
                     || pLVKeyDow->wVKey == VK_NUMPAD1)
            {
                if (!AeGetApp()->IsKndKasse())
                {
                    MsgBoxOK(AETXT_NO_KK_CODE_KND);
                }
                else
                {
                    int selpos;
                    selpos = m_ComboTyp.FindString(-1, "1");
                    m_ComboTyp.SetCurSel(selpos);
                    SetPrices();
                }
            }
            else if (   pLVKeyDow->wVKey == '2'
                     || pLVKeyDow->wVKey == VK_NUMPAD2)
            {
                if (!AeGetApp()->IsKndRetail())
                {
                    MsgBoxOK(AETXT_NO_RETAIL_KND);
                }
                else
                {
                    int selpos = m_ComboTyp.FindString(-1, "2");
                    m_ComboTyp.SetCurSel(selpos);
                    SetPrices();
                }
            }
            else if (   pLVKeyDow->wVKey == '3'
                     || pLVKeyDow->wVKey == VK_NUMPAD3)
            {
                if (!AeGetApp()->IsKndRetail())
                {
                    MsgBoxOK(AETXT_NO_RETAIL_KND);
                }
                else
                {
                    int selpos = m_ComboTyp.FindString(-1, "3");
                    m_ComboTyp.SetCurSel(selpos);
                    SetPrices();
                }
            }
            *pResult = 1L;
            return;
        }

        SetTextWithFocusNoSelection(m_EditMenge, (char)pLVKeyDow->wVKey); //erster Buchstabe im Feld Bezeichner
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == 188) //188 = Komma
    {
        if (AeGetApp()->IsMatchCode())
        {
            SetFocusFullSelection(m_EditMatchCode);
        }
        else
        {
            SetFocusFullSelection(m_EditMenge);
        }
        *pResult = 1L;
        return;
    }

    *pResult = 0L;
}

void CAeFView::OnChangeEditMenge()
{
    CString str;
    m_EditMenge.GetWindowText(str);
    if (str.IsEmpty())                                  //Feld ist leer
        return;
    char chN = str[str.GetLength() - 1];                     //letztes Zeichen lesen
    if (chN != '-' && chN != '+' && chN != '*' && chN != ',' && isdigit((int)chN))
    {
        AllgWertKontr(&m_EditMenge, MAXIMUM_BUCH_MENGE);
        return;
    }                                                   //Kein Ende der Eingabe
    str = str.Left(str.GetLength() - 1);                //letztes Zeichen löschen
    m_EditMenge.SetWindowText(str);                     //String zurückschreiben
    if (chN == '-' || chN == ',' || chN == '.')
    {
        m_EditZusatz.SetWindowText("");
        m_EditNormPackung.SetWindowText("");
        m_EditPackGr.SetWindowText("");
        m_EditNatRab.SetWindowText("");
        m_EditDarr.SetWindowText("");
        if (!AeGetApp()->IsMatchCode())
        {
            m_EditMatchCode.SetWindowText("");
            m_EditHC.SetWindowText("");
        }
        m_EditBemerkung.SetWindowText("");
        m_EditArtNr.SetWindowText("");
        m_ComboBuchStat.SetCurSel(0);
        if (chN == '.')
        {
            SetFocusFullSelection(m_EditNormPackung);
        }
        else if (chN == '-')
        {
            SetFocusFullSelection(m_EditArtNr);
        }
        else
        {
            SetFocusFullSelection(m_EditPackGr);
        }

    }
    else if (chN == '*' && m_ListCtl.GetItemCount() > 0)
    {
        MarkListPos(0);
        m_ListCtl.SetFocus();
    }
    else if (CLetterMan::InRange(chN, m_ListCtl.GetItemCount()))
    {
        int pos = chN - AeGetApp()->Letter_A();
        MarkListPos(pos);
        m_ListCtl.SetFocus();
    }
    else if (chN == '+')
    {
        SetFocusFullSelection(m_EditNatRab);
    }
}

void CAeFView::OnChangeEditNatrab()
{
    CString str;
    m_EditNatRab.GetWindowText(str);
    if (str.IsEmpty())                                  //Feld ist leer
        return;
    char chN = str[str.GetLength() - 1];                     //letztes Zeichen lesen
    if (chN != '-' && chN != '+' && chN != '*' && chN != ',' && isdigit((int)chN))
    {
        AllgWertKontr(&m_EditNatRab, MAXIMUM_NR_MENGE);
        return;
    }                                                   //Kein Ende der Eingabe
    str = str.Left(str.GetLength() - 1);                //letztes Zeichen löschen
    m_EditNatRab.SetWindowText(str);                    //String zurückschreiben
    if (chN == '-' || chN == ',' || chN == '.')
    {
        m_EditZusatz.SetWindowText("");
        m_EditNormPackung.SetWindowText("");
        m_EditPackGr.SetWindowText("");
        m_EditDarr.SetWindowText("");
        if (!AeGetApp()->IsMatchCode())
        {
            m_EditMatchCode.SetWindowText("");
            m_EditHC.SetWindowText("");
        }
        m_EditBemerkung.SetWindowText("");
        m_EditArtNr.SetWindowText("");
        m_ComboBuchStat.SetCurSel(0);
        if (chN == '.')
        {
            SetFocusFullSelection(m_EditNormPackung);
        }
        else
        {
            SetFocusFullSelection(m_EditPackGr);
        }
    }
    else if (chN == '*' && m_ListCtl.GetItemCount() > 0)
    {
        MarkListPos(0);
        m_ListCtl.SetFocus();
    }
    else if (CLetterMan::InRange(chN, m_ListCtl.GetItemCount()))
    {
        int pos = chN - AeGetApp()->Letter_A();
        MarkListPos(pos);
        m_ListCtl.SetFocus();
    }
}

void CAeFView::OnChangeEditPackGr()
{
    CString str;
    m_EditPackGr.GetWindowText(str);                    //Einheit lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (isdigit((int)chN))
    {
        AllgWertKontr(&m_EditPackGr, 32000);    //NASE
        return;
    }                                                   //Kein Ende der Eingabe
    str.GetBufferSetLength(str.GetLength() - 1);        //letztes Zeichen löschen
    m_EditPackGr.SetWindowText(str);                    //String zurückschreiben
    if (chN == '.')
    {
        SetFocusFullSelection(m_EditNormPackung);
        return;
    }
    if (chN == ',' && !AeGetApp()->IsKommaNoTab())
    {
        if (!AeGetApp()->IsMatchCode())
        {
            SetFocusFullSelection(m_EditMatchCode);
            return;
        }

        SetFocusFullSelection(m_EditDarr);
        return;
    }
    if (!AeGetApp()->IsMatchCode())
    {
        SetTextWithFocusNoSelection(m_EditMatchCode, chN); //erster Buchstabe im Feld Bezeichner
    }
}

void CAeFView::OnChangeEditNormpackung()
{
    CString str;
    m_EditNormPackung.GetWindowText(str);                  //Einheit lesen
    if (str.IsEmpty() || str == "N1" || str == "N2" || str == "N3")
        return;                                                  //Feld ist leer
    if (str == "1")
    {
        m_EditNormPackung.SetWindowText("N1");
        SetFocusFullSelection(m_EditMatchCode);
        return;
    }
    if (str == "2")
    {
        m_EditNormPackung.SetWindowText("N2");
        SetFocusFullSelection(m_EditMatchCode);
        return;
    }
    if (str == "3")
    {
        m_EditNormPackung.SetWindowText("N3");
        SetFocusFullSelection(m_EditMatchCode);
        return;
    }
    char chN = str[str.GetLength() - 1];             //letztes Zeichen lesen
    str.GetBufferSetLength(str.GetLength() - 1);     //letztes Zeichen löschen
    if (str.IsEmpty() || str == "N1" || str == "N2" || str == "N3")
        m_EditNormPackung.SetWindowText(str);                     //String zurückschreiben
    else
    {
        MsgBoxOK(IDP_UNG_EING_NORMP);
        m_EditNormPackung.SetWindowText("");
        return;
    }
    if (chN == ',' && !AeGetApp()->IsKommaNoTab())
    {
        if (!AeGetApp()->IsMatchCode())
        {
            SetFocusFullSelection(m_EditMatchCode);
            return;
        }
    
        SetFocusFullSelection(m_EditDarr);
        return;
    }
    if (!AeGetApp()->IsMatchCode())
    {
        SetTextWithFocusNoSelection(m_EditMatchCode, chN); //erster Buchstabe im Feld Bezeichner
    }
}

void CAeFView::OnChangeEditBezei()
{
    CString str;
    m_EditMatchCode.GetWindowText(str);                 //Einheit lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen

    //  Da auch Matchcode Zahlen enthalten kann
    //  und auch Artikelcode Alphas enthalten kann
    //  ist die folgende Abfrage nicht mehr sinnvoll
    if (str.GetLength() == 1 && isdigit((int)chN))
    {
        str.GetBufferSetLength(str.GetLength() - 1);    //letztes Zeichen löschen
        m_EditMatchCode.SetWindowText(str);             //String zurückschreiben
        SetTextWithFocusNoSelection(m_EditArtNr, chN);  //erster Buchstabe im Feld Bezeichner
        return;
    }                                                    //Kein Ende der Eingabe
    if (AeGetApp()->IsBG())  // In BG auch Eingabe KK-Code
    {
        if ((str.GetLength() == 3) && (str.GetAt(2) >= '0' && str.GetAt(2) <= '9'))
        {
            m_EditMatchCode.SetWindowText("\0");            //String löschen
            SetTextWithFocusNoSelection(m_EditArtNr, str);  //String aus Bezeichner nach Artikelcode
            return;
        }
    }

    if (chN == ',' && !AeGetApp()->IsKommaNoTab())
    {
        str.GetBufferSetLength(str.GetLength() - 1);  //letztes Zeichen löschen
        m_EditMatchCode.SetWindowText(str);           //String zurückschreiben
        if (AeGetApp()->IsMatchCode())
        {
            m_EditZusatz.SetWindowText("");
            m_EditNormPackung.SetWindowText("");
            m_EditPackGr.SetWindowText("");
            m_EditNatRab.SetWindowText("");
            m_EditDarr.SetWindowText("");
            SetFocusFullSelection(m_EditHC);
            return;
        }

        SetFocusFullSelection(m_EditDarr);
        return;
    }
    if (chN == '.')
    {
        str.GetBufferSetLength(str.GetLength() - 1);  //letztes Zeichen löschen
        m_EditMatchCode.SetWindowText(str);           //String zurückschreiben
        SetFocusFullSelection(m_EditZusatz);
        return;
    }
    m_EditHC.SetWindowText("");
    AllgLaengeKontr(&m_EditMatchCode, L_ARTSEL_ARTIKEL_MC,AeGetApp()->Modus());
}

void CAeFView::OnChangeEditZusatz()
{
    CString str;
    m_EditZusatz.GetWindowText(str);
    if (str.IsEmpty())                                  //Feld ist leer
        return;
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (chN == ',' && !AeGetApp()->IsKommaNoTab())
    {
        str = str.Left(str.GetLength() - 1);            //letztes Zeichen löschen
        m_EditZusatz.SetWindowText(str);                //String zurückschreiben
        SetFocusFullSelection(m_EditDarr);
        return;
    }
    AllgLaengeKontr(&m_EditZusatz, L_ARTSEL_ARTIKEL_NAME - 1, AeGetApp()->Modus());
}

void CAeFView::OnChangeEditDarreichung()
{
    CString str;
    m_EditDarr.GetWindowText(str);                      //Einheit lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (chN == ',' && !AeGetApp()->IsKommaNoTab())
    {
        str.GetBufferSetLength(str.GetLength() - 1);    //letztes Zeichen löschen
        m_EditDarr.SetWindowText(str);                  //String zurückschreiben
        SetFocusFullSelection(m_EditBemerkung);
        return;
    }
    AllgLaengeKontr(&m_EditDarr, L_ARTSEL_DARREICHFORM, AeGetApp()->Modus());
}

void CAeFView::OnChangeEditArtnr()
{
    CString str;
    m_EditArtNr.GetWindowText(str);
    if (str.IsEmpty())                                  //Feld ist leer
        return;
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (chN == '-')
    {
        m_EditArtNr.SetWindowText("");
        return;
    }

    if (isdigit((int)chN))
    {
        AllgLaengeKontr(&m_EditArtNr, 25, AeGetApp()->Modus());
        return;
    }
    else
    {
        m_EditArtNr.SetWindowText("");
        SetTextWithFocusNoSelection(m_EditMatchCode, str);
    }
}

void CAeFView::OnChangeEditBemerkung()
{
    if (   GetDlgItem( IDC_COMBO_FREE_PRICE )->IsWindowEnabled()
        || GetDlgItem( IDC_EDIT_FREE_PRICE )->IsWindowEnabled() )
    {
        CString str;
        m_EditBemerkung.GetWindowText(str);                 //Einheit lesen
        if (str.IsEmpty())
            return;                                         //Feld ist leer
        char chN = str[0];                                  //erstes Zeichen lesen
        if (chN == ',' && !AeGetApp()->IsKommaNoTab())
        {
            str.GetBufferSetLength(str.GetLength() - 1);    //letztes Zeichen löschen
            m_EditBemerkung.SetWindowText(str);             //String zurückschreiben
            SetFocusFullSelection(m_EditPreis);
            return;
        }
    }
    if (AeGetApp()->IsRS() && !AllgCheckPrintableSign(&m_EditBemerkung))
    {
        return;
    }
    AllgLaengeKontr(&m_EditBemerkung, MAXIMUM_POS_BEM, AeGetApp()->Modus());
}

void CAeFView::OnOk()
{
    if (GetFocus() == GetDlgItem(IDC_LISTCTRL_ART))
    {
        BucheListPos();
        return;
    }
    //for DropDownList
    if (GetFocus() == GetDlgItem(IDC_COMBO_FREE_PRICE))
    {
        BucheListPos();
        return;
    }
    //for DropDown
    //Abfragen 1. Child
    if (GetFocus() == GetDlgItem(IDC_COMBO_FREE_PRICE)->GetWindow(GW_CHILD))
    {
        BucheListPos();
        return;
    }
    //und Abfragen 2. Child
    //mehr Child hat eine ComboBox nicht
    if (GetFocus() == GetDlgItem(IDC_COMBO_FREE_PRICE)->GetWindow(GW_HWNDNEXT))
    {
        BucheListPos();
        return;
    }
    if (GetFocus() == GetDlgItem(IDC_EDIT_FREE_PRICE))
    {
        BucheListPos();
        return;
    }
    if (GetFocus() == GetDlgItem(IDC_EDIT_MENGE))
    {
        if (m_bCursorOpen)
            GetPage();
        return;
    }

    UpdateData();
    if (atol(m_CMenge) > WARN_BUCH_MENGE)
    {
        MsgBoxOK(IDP_WARN_MENGE);
    }
    if (!m_bBuchungErfolgt)    //verhindern, daß umbeabsichtigt neu angeschrieben wird
    {
        if (MsgBoxYesNo(IDP_NOCH_NICHT_GEB, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDNO)
        {
            SetFocusNoSelection(m_EditMenge);
            return;
        }
    }
    if (m_CArtNr.GetLength() > 0)
    {
        for (int i = 0; i < m_CArtNr.GetLength(); i++)
        {
            if (m_CArtNr.GetAt(i) == '0')
            {
                m_CArtNr = m_CArtNr.Right(m_CArtNr.GetLength() - 1);
                --i;
            }
            else
            {
                break;
            }
        }
        SelectArtikelNr(m_CArtNr);
        if (GetAeUser().DirektPZN() && m_ListCtl.GetItemCount() > 0)
        {
            MarkListPos(0);
            BucheListPos();
        }
        return;
    }

    // Überprüfung der Matchcode-Eingabe
    char str[81];
    AllgStrCopy(str, m_CMatchCode, 80);
    AllgEntfSpaces(str);
    if (!AeGetApp()->IsFR() && !AeGetApp()->IsHR())
    {
        AllgEntfFirstSpaces(str);   //auch keine führenden Blanks
    }
    int laenge = strlen(str);
    if (laenge < 3)
    {
        if (!AeGetApp()->IsRS() && !AeGetApp()->IsBG())
        {
            MsgBoxOK(IDP_MIND_DREI_ZEICHEN);
            SetFocusFullSelection(m_EditMatchCode);
            return;
        }
    }
    if (laenge > 3) laenge = 3;
    for (int i = 0; i < laenge; i++)
    {
        if (m_CMatchCode.GetAt(i) == '%')
        {
            MsgBoxOK(IDP_NO_PROZENT);
            SetFocusFullSelection(m_EditMatchCode);
            return;
        }
    }
    for (int i = 0; i < laenge; i++)
    {
        if (m_CMatchCode.GetAt(i) == '_')
        {
            MsgBoxOK(IDP_NO_UNDERLINE);
            SetFocusFullSelection(m_EditMatchCode);
            return;
        }
    }
    m_bBuchungErfolgt = FALSE;
    CloseCursor();
    GetPage();
    if (AeGetApp()->IsBG())
    {
        MarkListPos(0);
        m_ListCtl.SetFocus();
    }
    else
    {
        SetFocusNoSelection(m_EditMenge);
    }
}

void CAeFView::OnPrior()
{
    if (m_bCursorOpen)
        GetPage(PRIOR_PG);
}

void CAeFView::OnNext()
{
    if (m_bCursorOpen)
        GetPage();
}

void CAeFView::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CARTAESEL artaesel;
    artaesel.s.FETCH_REL = 0;
    BeginWaitCursor();
    artaesel.Server(AatartAa_select);
    EndWaitCursor();
    m_ListCtl.DeleteAllItems();
    ResetCursor();
    Reset();
}

bool CAeFView::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    static CARTAESEL artaesel;

    AllgStrCopy(artaesel.s.PHARMACYGROUPID, AeGetApp()->ActEKGrp(), L_ARTAESEL_PHARMACYGROUPID);
    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "aefview.cpp", "GetPage", "Start Aufbau Listbox");
        artaesel.s.IMPORTARTICLE = m_iImport;
        artaesel.s.ARTIKEL_NR = 0; //mit Artikel_nr wird an anderer Stelle verarbeitet
        artaesel.s.BESTAND = m_bKz_Nur_Liefber ? 1 : 0; // nur nicht defekte anzeigen
        CString cAArt;
        GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
        artaesel.s.ETARTKLASSE1 = AeGetApp()->KndKlasse1();
        artaesel.s.POSITIVLISTE[0] = (cAArt == "PL") ? '1' : ' ';
        artaesel.s.CODEBLOCAGE[0] = AeGetApp()->IsPrintCode() ? '1' : '0';
        strcpy(artaesel.s.ARTIKEL_MC, m_CMatchCode);
        if (m_nFunktion != AatartAa_sel_index)
            AllgEntfAllSpaces(artaesel.s.ARTIKEL_MC);
        artaesel.s.PACKGROESSE = atol(m_CPackGr);
        artaesel.s.FILIALNR = AeGetApp()->FilialNrActual();
        if (!m_CZusatz.IsEmpty())
        {
            int start = 0;
            int end;
            for (;start < m_CZusatz.GetLength();)
            {   //bei nur einem Zeichen vor % space vorsetzen
                if ((end = m_CZusatz.Find('%', start)) == -1)
                    break;
                if ((end - start) == 1)
                    m_CZusatz.Insert(start, " ");
                start = end + 1;
            }
            end = m_CZusatz.GetLength();
            if ((end - start) == 1)
                m_CZusatz.Insert(start, " ");
        }
        AllgStrCopy(artaesel.s.ARTIKEL_NAME, m_CZusatz, L_ARTAESEL_ARTIKEL_NAME);
        AllgStrCopy(artaesel.s.DARREICHFORM, m_CDarr, L_ARTAESEL_DARREICHFORM);
        AllgStrCopy(artaesel.s.NORMPACKUNG, m_CNormPackung, L_ARTAESEL_NORMPACKUNG);
        AllgStrCopy(artaesel.s.HERSTELLER_CODE, m_CHC, L_ARTAESEL_HERSTELLER_CODE);
        if (AeGetApp()->IsBG())
        {
            artaesel.s.HEALTHFUNDCODE[0] = (GetPriceTypeFromCB() == 1) ? '0' : ' ';
            artaesel.s.HEALTHFUNDCODE[1] = '\0';
        }
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, artaesel.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();

    CLetterMan kb;
    static BOOL bOhneDarr = FALSE;
    static BOOL bOhneEinh = FALSE;
    static BOOL bOhneZusatz = FALSE;
    static BOOL bVerkuerzen = FALSE;

    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        artaesel.Server(AatartAa_select);
        m_bCursorOpen = true;      //Datenbankcurser offen
        artaesel.s.FETCH_REL = 1;         //normaler Fetch
        if (artaesel.rc == SRV_SQLNOTFOUND)
        {
            if (m_bFirstDataset)     //kein Satz gefunden
            {
                CloseCursor();
                EndWaitCursor();
                if (!m_CNormPackung.IsEmpty() && bOhneEinh != TRUE)
                {
                    m_CPackGr = "";
                    m_CNormPackung = "";
                    bOhneEinh = TRUE;
                }
                else if (!m_CDarr.IsEmpty() && bOhneDarr != TRUE)
                {
                    m_CDarr = "";
                    m_EditPackGr.GetWindowText(m_CPackGr);
                    m_EditNormPackung.GetWindowText(m_CNormPackung);
                    bOhneDarr = TRUE;
                }
                else if (!m_CZusatz.IsEmpty() && bOhneZusatz != TRUE)
                {
                    m_CZusatz = "";
                    m_EditDarr.GetWindowText(m_CDarr);      //alte Darreichform wieder herstellen
                    m_EditNormPackung.GetWindowText(m_CNormPackung);
                    m_EditPackGr.GetWindowText(m_CPackGr);
                    m_EditHC.GetWindowText(m_CHC);
                    bOhneZusatz = TRUE;
                }
                else if (m_CMatchCode.GetLength() > 3
                    && m_CMatchCode.GetAt(m_CMatchCode.GetLength()) != '%'  //Nicht bei Artikelindex
                    && m_CMatchCode.GetAt(m_CMatchCode.GetLength()) != '*') //und nicht bei Lieferantenartikelnr
                {
                    CString cstr = m_CMatchCode.Left(m_CMatchCode.GetLength() - 1);   //schrittweises verkuerzen bis laenge 3
                    m_CMatchCode = cstr;
                    m_EditZusatz.GetWindowText(m_CZusatz);  //alte Artikelzusatz wieder herstellen
                    m_EditDarr.GetWindowText(m_CDarr);      //alte Darreichform wieder herstellen
                    m_EditNormPackung.GetWindowText(m_CNormPackung);
                    m_EditHC.GetWindowText(m_CHC);
                    m_EditPackGr.GetWindowText(m_CPackGr);  //alte Packungsgroesse wieder herstellen
                    bVerkuerzen = TRUE;
                }
                else
                {
                    bOhneDarr = FALSE;
                    bOhneEinh = FALSE;
                    bOhneZusatz = FALSE;
                    bVerkuerzen = FALSE;
                    m_bBuchungErfolgt = TRUE;
                    CArtNotFound fehler;
                    m_EditMatchCode.GetWindowText(fehler.m_cBezeichnung);
                    fehler.m_cFehltext = CResString::ex().getStrTblText(IDP_KEIN_ARTIKEL);
                    fehler.m_bAufnahme = TRUE;
                    CString cstr;
                    m_EditMenge.GetWindowText(cstr);
                    int menge = atol(cstr);
                    fehler.DoModal();
                    cstr.Format("%d", fehler.m_lArtNo);
                    if (fehler.m_lArtNo > 0)
                        ArtAnschreiben(menge, cstr, "", "");
                    return false;
                }
                return GetPage();
            }
            SetItemCountOfCurrentPage(i); //Anzahl Artikel letzte Seite
            break;
        }
        if (m_bFirstDataset) //Sonderbehandlung kontrollieren
        {
            if (bVerkuerzen) //!!!Reihenfolge entgegengesetzt dem Setzen!!!
            {
                CArtNotFound fehler;
                m_EditMatchCode.GetWindowText(fehler.m_cBezeichnung);
                fehler.m_cFehltext = CResString::ex().getStrTblText(IDP_OHNE_LANGMATCH_ANS);
                fehler.m_bNoShort = TRUE;
                fehler.m_bAufnahme = TRUE;
                CString cstr;
                m_EditMenge.GetWindowText(cstr);
                int menge = atol(cstr);
                if (AeGetApp()->IsAuswahlKurz()) // || MsgBoxYesNo(IDP_OHNE_LANGMATCH_ANS,MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDYES)
                {
                    m_EditMatchCode.SetWindowText(m_CMatchCode);
                }
                else if (fehler.DoModal() == IDOK)
                {
                    cstr.Format("%d", fehler.m_lArtNo);
                    if (fehler.m_lArtNo > 0)
                        ArtAnschreiben(menge, cstr, "", "");
                    else m_EditMatchCode.SetWindowText(m_CMatchCode);
                }
                else
                {
                    cstr.Format("%d", fehler.m_lArtNo);
                    if (fehler.m_lArtNo > 0)
                    {
                        ArtAnschreiben(menge, cstr, "", "");
                    }
                    m_bBuchungErfolgt = TRUE;
                    CloseCursor();
                    bOhneDarr = FALSE;
                    bOhneEinh = FALSE;
                    bOhneZusatz = FALSE;
                    bVerkuerzen = FALSE;
                    return false;
                }
            }
            else if (bOhneZusatz)    //!!!Reihenfolge entgegengesetzt dem Setzen!!!
            {
                if (AeGetApp()->IsAuswahlKurz())
                {
                    m_EditZusatz.SetWindowText("");
                }
                else if (MsgBoxYesNo(IDP_OHNE_ZUSATZ, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDYES)
                {
                    m_EditZusatz.SetWindowText("");
                }
                else
                {
                    m_bBuchungErfolgt = TRUE;
                    CloseCursor();
                    bOhneDarr = FALSE;
                    bOhneEinh = FALSE;
                    bOhneZusatz = FALSE;
                    bVerkuerzen = FALSE;
                    return false;
                }
            }
            else if (bOhneDarr)  //!!!Reihenfolge entgegengesetzt dem Setzen!!!
            {
                if (AeGetApp()->IsAuswahlKurz())
                {
                    m_EditDarr.SetWindowText("");
                }
                else if (MsgBoxYesNo(IDP_OHNE_DARREICHFORM_ANS, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDYES)
                {
                    m_EditDarr.SetWindowText("");
                }
                else
                {
                    m_bBuchungErfolgt = TRUE;
                    CloseCursor();
                    bOhneDarr = FALSE;
                    bOhneEinh = FALSE;
                    bOhneZusatz = FALSE;
                    bVerkuerzen = FALSE;
                    return false;
                }
            }
            else if (bOhneEinh)
            {
                if (AeGetApp()->IsAuswahlKurz())
                {
                    m_EditPackGr.SetWindowText("");
                    m_EditNormPackung.SetWindowText("");
                }
                else if (MsgBoxYesNo(IDP_OHNE_EINHEIT_ANS, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDYES)
                {
                    m_EditPackGr.SetWindowText("");
                    m_EditNormPackung.SetWindowText("");
                }
                else
                {
                    m_bBuchungErfolgt = TRUE;
                    CloseCursor();
                    bOhneDarr = FALSE;
                    bOhneEinh = FALSE;
                    bOhneZusatz = FALSE;
                    bVerkuerzen = FALSE;
                    return false;
                }
            }
            bOhneDarr   = FALSE;
            bOhneEinh   = FALSE;
            bOhneZusatz = FALSE;
            bVerkuerzen = FALSE;
        }
        if (m_bFirstDataset)  //Erstmaliger Aufruf
        {
            AeGetApp()->m_AeLogging.WriteLine(2, "aefview.cpp", "GetPage", "Einträge für Listbox gefunden");
        }
        m_bFirstDataset = false;
        AusgListPos(artaesel, kb.Next());
    } //Ende der for()-Schleife
    if (AeGetApp()->IsBG())
    {
        SetPrices();
    }
    EndWaitCursor();
    MarkListPos(0);
    return true;
}

void CAeFView::AusgListPos(CARTAESEL& artaesel, char* kb)
{
    CStringArray s;
    s.SetSize(NUM_FVIEW_COLUMNS);

    CARTIKELRESERVE reserv;
    reserv.SetBranchno(m_VzNr);
    reserv.SetArticleno(artaesel.s.ARTIKEL_NR);
    reserv.SetCustomerno(m_KndNr);
    if (!reserv.SelArtKnd())
    {
        artaesel.s.BESTAND += reserv.GetReservedqty();
    }

    int nLieferbereitschaft = GetLieferbereitschaft(artaesel.s.BESTAND, artaesel.s.ARTIKEL_NR, m_bKz_Verbund_Moegl && m_bKz_Kunde_Verbund);

    s[COL_FVIEW_KB] = kb;
    CString cstr;
    cstr.Format("%ld", artaesel.s.BESTAND);
    s[COL_FVIEW_BESTAND] = cstr;
    AllgEntfFirstSpaces(artaesel.s.EINHEIT);
    AllgEntfSpaces(artaesel.s.EINHEIT);
    s[COL_FVIEW_EINHEIT] = artaesel.s.EINHEIT;
    if (AeGetApp()->IsBG())
    {
        AllgEntfSpaces(artaesel.s.ARTIKEL_LANGNAME);
        s[COL_FVIEW_ARTIKELNAME] = artaesel.s.ARTIKEL_LANGNAME;
    }
    else
    {
        AllgEntfSpaces(artaesel.s.ARTIKEL_NAME);
        s[COL_FVIEW_ARTIKELNAME] = artaesel.s.ARTIKEL_NAME;
    }
    AllgEntfSpaces(artaesel.s.DARREICHFORM);
    s[COL_FVIEW_DAF] = artaesel.s.DARREICHFORM;
    if (AeGetApp()->IsBG())
    {
        double dTax;
        char cStd;
        AeGetApp()->GetTaxRates(artaesel.s.TAXLEVEL, cStd, dTax);
        if (AeGetApp()->KndGruppe() > 0)
        {
            artaesel.s.PREISEKAPO = artaesel.s.PREISEKGROSSO * (100 + dTax) / 100;
        }
        else
        {
            artaesel.s.PREISEKAPO = artaesel.s.PREISEKAPO * (100 + dTax) / 100;
        }
        artaesel.s.PREISEKGROSSONA = artaesel.s.PREISEKGROSSONA * (100 + dTax) / 100;
    }
    cstr.Format("%0.2f", artaesel.s.PREISEKGROSSONA);
    s[COL_FVIEW_GROSSONA] = cstr;
    cstr.Format("%0.2f", artaesel.s.PREISEKAPO);
    s[COL_FVIEW_PREIS] = cstr;
    s[COL_FVIEW_KB2] = kb;
    cstr.Format("%02d/%02d", artaesel.s.DATUMVERFALL % 100, artaesel.s.DATUMVERFALL / 100);
    s[COL_FVIEW_VERFALL] = cstr;
    GetArtKennz(&artaesel.s, cstr);
    s[COL_FVIEW_KENNZEICHEN] = cstr;
    cstr.Format("%ld", artaesel.s.ARTIKEL_NR);
    s[COL_FVIEW_PZN] = cstr;
    AllgEntfSpaces(artaesel.s.HERSTELLER_CODE);
    s[COL_FVIEW_HERSTELL] = artaesel.s.HERSTELLER_CODE;
    if (AeGetApp()->IsAnzRabatte())
    {
        s[COL_FVIEW_TEXT].Empty();
        CDISCOUNTANZ Discount;      //neue Rabatte
        Discount.SetBranchno(m_VzNr);
        Discount.SetArticleno(artaesel.s.ARTIKEL_NR);
        Discount.SetCustomerno(m_KndNr);
        CString rabatte;
        for (;;)
        {
            if (Discount.SelListGrp() != SRV_OK)
                break;
            rabatte.Empty();
            if (Discount.GetDiscountqty() > 0)
            {
                rabatte.Format("%d/%d ", Discount.GetBaseqty(), Discount.GetDiscountqty());
            }
            else if (Discount.GetDiscountvaluepct() > 0)
            {
                rabatte.Format("%d/%.2lf%% ", Discount.GetBaseqty(), Discount.GetDiscountvaluepct());
            }
            else if (Discount.GetDiscountqtypct() > 0)
            {
                rabatte.Format("%d/%.2lf%% ", Discount.GetBaseqty(), Discount.GetDiscountqtypct());
            }
            else if (Discount.GetFixedprice() > 0)
            {
                rabatte.Format("%d/%.2lf ", Discount.GetBaseqty(), Discount.GetFixedprice());
            }
            s[COL_FVIEW_TEXT] += rabatte;
        }
    }
    else
    {
        AllgEntfSpaces(artaesel.s.TEXT);
        s[COL_FVIEW_TEXT] = artaesel.s.TEXT;
    }
    s[COL_FVIEW_APOPFLICHT] = AllgBitleisteN((Bitleiste)artaesel.s.ETARTKLASSE1, 5) ? "1" : "0"; // APO-Plicht
    cstr.Format("%ld", artaesel.s.TEXTKEY_HOSPITAL);
    if ((AeGetApp()->IsDE() || AeGetApp()->IsCH()) && (artaesel.s.TEXTKEY_HOSPITAL > 0))
    {
        s[COL_FVIEW_TEXT] = CResString::ex().getStrTblText(AETXT_HINWEIS_F11);
    }
    s[COL_FVIEW_TEXTKEY] = cstr;
    s[COL_FVIEW_OPIAT] = AllgBitleisteN((Bitleiste)artaesel.s.ETARTKLASSE1, 6) ? "1" : "0"; // opiat
    AllgEntfSpaces(artaesel.s.HEALTHFUNDCODE);
    s[COL_FVIEW_KKCODE] = artaesel.s.HEALTHFUNDCODE;
    s[COL_FVIEW_PREISGR4] = AllgBitleisteN((Bitleiste)artaesel.s.ETARTKLASSE1, 8) ? "1" : "0"; // Preisgruppe 4
    s[COL_FVIEW_TAXLEVEL].Format("%d", artaesel.s.TAXLEVEL);
    if (AeGetApp()->IsBG() && artaesel.s.BESTAND > 0)
    {
        if (!s[COL_FVIEW_KKCODE].IsEmpty())
        {
            nLieferbereitschaft = AeGetApp()->IsKndKasse() ? POS_KK : POS_FV;
        }
        else if (s[COL_FVIEW_PREISGR4] == "0")
        {
            nLieferbereitschaft = AeGetApp()->IsKndRetail() ? POS_EH : POS_FV;
        }
        else
        {
            nLieferbereitschaft = POS_FV;
        }
    }
    cstr.Format("%0.2f", artaesel.s.PREISEKGROSSO);
    s[COL_FVIEW_GROSSO] = cstr;
    cstr.Format("%d", artaesel.s.CODE_TYPE);
    s[COL_FVIEW_CODE_TYPE] = cstr;
    s[COL_FVIEW_ARTICLE_CODE] = artaesel.s.ARTICLE_CODE;
    s[COL_FVIEW_SUPPLINFO].Empty();
    s[COL_FVIEW_SUPPLPROG].Empty();
    s[COL_FVIEW_SUPPLLIEF].Empty();
    cstr.Format("%d", artaesel.s.PRODUSERQUOTA);
    s[COL_FVIEW_PRODQUOTA] = cstr;

    if (AeGetApp()->IsAT() || AeGetApp()->IsDE())
    {
        CSUPPLINFO suppl;
        suppl.SetArticleno(artaesel.s.ARTIKEL_NR);
        if (!suppl.SelSuppInfo())
        {
            ppString Info;
            AllgEntfSpaces(suppl.s.AVAILABILITYINFO);
            cstr.Format("%s", suppl.GetAvailabilityinfo(Info));
            s[COL_FVIEW_SUPPLINFO] = cstr;
            if (suppl.GetProglieferdatum() < 30000000)
            {
                s[COL_FVIEW_SUPPLPROG] = DDMMYYYYStringFromDateLong(suppl.GetProglieferdatum());
            }
            if (suppl.GetLieferdatum() < 30000000)
            {
                s[COL_FVIEW_SUPPLLIEF] = DDMMYYYYStringFromDateLong(suppl.GetLieferdatum());
            }
        }
    }

    int index;
    if (!CListCtrlHelper::GetAppendImageItem(m_ListCtl, NUM_FVIEW_COLUMNS, s, nLieferbereitschaft, index))
    {
        EndWaitCursor();
        return;
    }

    // Icon auf Spalte setzen
    if (artaesel.s.PRODUSERQUOTA == 1)
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_BESTAND, LIEFBER_PROD_QUOTA);
    }
    if (AeGetApp()->IsBG())
    {
        CCHECKLISTE5ZENTRAL cl5z;
        cl5z.SetArtikel_nr(artaesel.s.ARTIKEL_NR);
        if (!cl5z.IsListe5())
        {
            CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_PREIS, LIEFBER_L5);
        }
        else
        {
            CCHECKLISTE5 cl5;
            cl5.SetBranchno(m_VzNr);
            cl5.SetArticleno(artaesel.s.ARTIKEL_NR);
            cl5.SetCustomerno(m_KndNr);
            if (!cl5.IsListe5())
            {
                CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_PREIS, LIEFBER_L5);
            }
        }
    }
    if (artaesel.s.IMPORTARTICLE == 1)
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_DEGETTER);
    }
    else if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTKLASSE1, 6))  // opiat
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_BTM);
    }
    else if (artaesel.s.FROZEN == 1)  // Kühl -25 bis -15
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_MITTEL);
    }
    else if (artaesel.s.FROZEN == 2)  // Kühl -80 bis -60
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_ULTRA);
    }
    else if (   artaesel.s.KZPSYCHOSTOFFE[0] == 'J'
             || artaesel.s.KZPSYCHOSTOFFE[0] == 'B'
             || artaesel.s.KZPSYCHOSTOFFE[0] == 'C'
             || artaesel.s.KZPSYCHOSTOFFE[0] == 'D'
             || artaesel.s.KZPSYCHOSTOFFE[0] == 'E'
             || artaesel.s.KZPSYCHOSTOFFE[0] == 'F'
             || artaesel.s.KZPSYCHOSTOFFE[0] == 'P'
             || artaesel.s.KZPSYCHOSTOFFE[0] == 'T' )  // psychotrop
    {
        int iImage = LIEFBER_PSYCHO;
        if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1,10))  // Kuehlkette
        {
            iImage = LIEFBER_PSYCHO_KK;
        }
        else if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1,8))
        {
            iImage = LIEFBER_PSYCHO_K08;
        }
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, iImage);
    }
    else if (   artaesel.s.CHARGENARTIKEL[0] == '1'       // Chargenartikel
             && !AeGetApp()->IsBG()
             && !AeGetApp()->IsFR() )
    {
        if (   AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 10)   // Kuehlkette
            || AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 8) )  // Kuehl unter 8 Grad
        {
            CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_CHARGE_KUEHL);
        }
        else
        {
            CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_CHARGE);
        }
    }
    else if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 10))  // Kuehlkette
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_KUEHL);
    }
    else if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 8))
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_KUEHL_U8);
    }
    else if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 9) && AeGetApp()->IsCool20())  // Kuehl unter 20 Grad
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_KUEHL20);
    }
    else if (artaesel.s.PRISOART[0] > '0')  // Privatsortiment
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_PRIVAT);
    }
    else if (artaesel.s.TFG[0] > '0')  // Transfusionsgesetz
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_TFG);
    }
    else if (artaesel.s.MEDIZINPRODUKT[0] == '1')  // Medizinprodukt
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_FVIEW_ARTIKELNAME, LIEFBER_MDR);
    }
}

void CAeFView::GetArtKennz(ARTAESEL* artaesel, CString& cArtKZ)
{
    //nase
    //ist noch einmal in aasrv.cpp definiert !!!!!!
    CString cstr;
    cArtKZ = "";
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER1, 0))     cstr += "9";        // Sekundaerbezeichner
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER1, 1))     cstr += "E";        // Nachfolgeartikel
    if (artaesel->PRISOART[0] != '0')
    {
        if      (artaesel->PRISOART[0] == '1')       cstr += "SL";
        else if (artaesel->PRISOART[0] == '2')       cstr += "SZ";
        else if (artaesel->PRISOART[0] == '3')       cstr += "SB";
    }
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER1, 3))     cstr += "A";        // ausser Handel
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER1, 4))     cstr += "AV";       // Auslaufartikel
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER1, 13))    cstr += "G";        // nicht ueber Grosshandel
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER1, 12))    cstr += "H";        // vom Hersteller nicht geliefert
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER1, 11))    cstr += "L";        // vom Hersteller nicht lieferbar
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER1, 6))     cstr += "P";        // Netto
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER3, 7))     cstr += "N";        // Natra
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER4, 1))     cstr += "R";        // Reimport
    if (AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER4, 14))    cstr += "T";        // Nahrungsmittel gesperrt
    if (!AllgBitleisteN((Bitleiste)artaesel->ETARTSCHALTER2, 15) && artaesel->BESTAND == 0)
    {
        if (artaesel->WAFOTYP[0] > '0')
            cstr += "W";        // Artikel darf als NL erfasst werden
        cstr += "F";            // Artikel wird nicht gefuehrt
    }
    cArtKZ = cstr;
}

void CAeFView::BucheListPos()
{
    CString ArtName;
    CString ArtEinh;
    CString Kz;
    CString Darr;
    CString AEP;
    CString TAX;
    CString TEXTKEY;
    CString Opi;
    CString KKCode;
    CString Einzelhandel;
    CString Bestand;
    CString Taxlevel;
    CString Charge;
    CString Grosso;
    CString Codetype;
    CString Artcode;
    CString GrossoNA;
    CString ProdQuota;
    CString FixBatch = "0";
    long n = SelListPos(ArtName, ArtEinh, Kz, Darr, AEP, TAX, TEXTKEY, Opi, KKCode, Einzelhandel, Bestand, Taxlevel, Grosso, Codetype, Artcode, GrossoNA, ProdQuota);
    if (n != -1) //Ermittlung Artikeldaten
    {
        m_ArtNr = n;                            //Artikel-Nr. entspr. Selektion setzen
        if ((atoi(ProdQuota)) == 1)
        {
            if (!AeGetApp()->IsGiveProdQuota())
            {
                MsgBoxOK(AETXT_NO_PRODQUOTA);
                return;
            }
            else
            {
                if (MsgBoxYesNo(AETXT_BOOK_PRODQUOTA) != IDYES) return;
            }
        }

        BucheListPosBG(ArtName, AEP, Opi, KKCode, Einzelhandel, Bestand, Taxlevel, Charge, GrossoNA, FixBatch);

        PosBuchen(ArtName, ArtEinh, Kz, Darr, AEP, TAX, TEXTKEY, Opi, KKCode, Einzelhandel, Charge,
            Grosso, Codetype, Artcode, FixBatch);  //selektierten Artikel verbuchen
        if (AeGetApp()->IsRS())
        {
            m_CPreis.Empty();
            m_EditPreis.SetWindowText(m_CPreis);  //Preis loeschen
        }
        if (AeGetApp()->IsMatchCode())
        {
            SetFocusFullSelection(m_EditMatchCode);
        }
        else
        {
            m_EditMenge.SetFocus();                 //nach jeder Buchung auf Menge pos.
        }
    }
}

void CAeFView::BucheListPosBG(CString csArtName, CString csAEP, CString csOpi, CString csKKCode, CString csEinzelhandel,
    CString csBestand, CString csTaxlevel, CString csCharge, CString csGrossoNA, CString csFixBatch)
{
    if (!AeGetApp()->IsBG())
    {
        return;
    }

    if ((atof(csAEP)) == 0.0)
    {
        MsgBoxOK(AETXT_NO_VALID_PRICE);
        return;
    }
    m_dCstDiscount = 0.0;
    CWnd* pActive = GetActiveWindow();

    short sPreistyp = GetPriceTypeFromCB();

    if (m_pDlgRab->GetSafeHwnd() == 0)
    {
        m_pDlgRab->m_sPreistyp = sPreistyp;
        if (m_pDlgRab->m_sPreistyp == 3)
            m_pDlgRab->m_sPreistyp = 0;
        m_pDlgRab->m_sFilialnr = AeGetApp()->FilialNrActual();
        m_pDlgRab->m_lKndNr = m_KndNr;
        m_pDlgRab->m_ArtikelNr = m_ArtNr;
        m_pDlgRab->Create();    // Dialogfeld anzeigen
    }
    CDViewPos posbg;
    posbg.m_sPreistyp = sPreistyp;
    posbg.m_csARTIKELNAME = csArtName;
    posbg.m_csPZN.Format("%d", m_ArtNr);
    posbg.m_csAEP = csAEP;
    if (atof(csAEP) > 0.0)
    {
        double dTax;
        char cStd;
        AeGetApp()->GetTaxRates(atoi(csTaxlevel), cStd, dTax);
        double aep = (atof(csAEP) * 100 / (100 + dTax));
        CString hilfe;
        hilfe.Format("%0.2lf", aep);
        aep = atof(hilfe);
        double grosso = (atof(csGrossoNA) * 100 / (100 + dTax));
        hilfe.Format("%0.2lf", grosso);
        grosso = atof(hilfe);
        double spanne = ((aep - grosso) / (aep)) * 100;
        posbg.m_csSpanne.Format("%0.2lf", spanne);
    }
    else
    {
        posbg.m_csSpanne = "0.00";
    }
    posbg.m_csOpi = csOpi;
    posbg.m_csKKCode = csKKCode;
    posbg.m_csEinzelhandel = csEinzelhandel;
    posbg.m_csBestand = csBestand;
    posbg.m_CBTMLicense = m_CBTMLicense;
    posbg.m_lDatumBTM = m_lDatumBTM;
    posbg.m_csTaxlevel = csTaxlevel;
    CString cAArt;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
    posbg.m_cAArt = cAArt;
    if (cAArt == "RO")
        posbg.m_csRabatt.Empty();
    else
        posbg.m_csRabatt.Format("%0.2lf", m_dCstDiscount);

    if (posbg.DoModal() != IDOK)
    {
        m_pDlgRab->DestroyWindow(); // kein Problem, falls Fenster schon gelöscht
        if (pActive != NULL)
        {
            pActive->SetActiveWindow();
        }
        return;
    }
    m_bIgnore = posbg.m_bIgnore;
    if (pActive != NULL)
    {
        pActive->SetActiveWindow();
    }
    m_pDlgRab->DestroyWindow(); // kein Problem, falls Fenster schon gelöscht
    csCharge = posbg.m_csCharge;
    m_CMenge = posbg.m_csMENGE;
    m_CNatRab = posbg.m_csNatra;
    m_CBTMLicense = posbg.m_CBTMLicense;
    m_lDatumBTM = posbg.m_lDatumBTM;
    char huelse[2];
    sprintf(huelse, "%d", posbg.m_sPreistyp);
    int selpos = m_ComboTyp.FindString(-1, huelse);
    m_ComboTyp.SetCurSel(selpos);
    if (sPreistyp != posbg.m_sPreistyp)
    {
        SetPrices();
    }
    m_dCstDiscount = atof(posbg.m_csRabatt);
    GetDlgItem(IDC_EDIT_MENGE)->SetWindowText(m_CMenge);
    GetDlgItem(IDC_EDIT_NATRAB)->SetWindowText(m_CNatRab);
    if (!csCharge.IsEmpty() && AeGetApp()->IsOTfixBatch())
    {
        csFixBatch = "1";
    }
}

//Aktualisierung der Bestandsinformation nach einer Buchung
void CAeFView::UpdateLieferbereitschaft(long bestand)
{
    CString cBestand;
    cBestand.Format("%ld", bestand);
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        UpdateLieferbereitschaft(bestand, cBestand, pos, m_bKz_Verbund_Moegl && m_bKz_Kunde_Verbund);
    }
}

void CAeFView::UpdateLieferbereitschaft(long lBestand, const CString& cBestand, int posListCtl, bool bCheckVerbund)
{
    //Überprüfen vorhandene Kontigentierung
    m_ListCtl.SetItemText(posListCtl, COL_FVIEW_BESTAND, cBestand);

    long larticleno = atol(m_ListCtl.GetItemText(posListCtl, COL_FVIEW_PZN));

    int nLieferbereitschaft = GetLieferbereitschaft(lBestand, larticleno, bCheckVerbund);

    if (lBestand == 0L)
    {
        CListCtrlHelper::SetImageItemSelected(m_ListCtl, posListCtl, nLieferbereitschaft);
    }
}

int CAeFView::GetLieferbereitschaft(long& lBestand, long larticleno, bool bCheckVerbund)
{
    //Überprüfen vorhandene Kontigentierung
    long lRest;
    bool bCheck = CheckKontigent(larticleno, lBestand, lRest) ? true : false;
    int nLieferbereitschaft;
    if (lBestand > 0L)
    {
        nLieferbereitschaft = bCheck ? LIEFBER_OK : LIEFBER_QUOTA;
    }
    else
    {
        nLieferbereitschaft = bCheck ? LIEFBER_NO : LIEFBER_QUOTA_DEF;

        if (bCheckVerbund)
        {
            bool bSuccess;
            if (AeGetApp()->IsNLevelIBTCst())
            {
                CAUFALTLAGORT ibt;
                ibt.s.ARTIKEL_NR = larticleno;
                ibt.s.FILIALNR = m_VzNr;
                ibt.Server(AasrvCheckIBTStockLevel);
                bSuccess = (ibt.rc == SRV_OK);
            }
            else
            {
                CVERBUNDMOEGL vbm;
                vbm.s.ARTIKEL_NR = larticleno;
                vbm.s.FILIALNR = m_VzNr;
                (AeGetApp()->UseTourManagerCst() > 0) ? vbm.SelVbBestandTM() : vbm.SelVbBestandNeu();
                bSuccess = (vbm.rc == SRV_OK && vbm.GetBestand() > 0);
            }
            if (bSuccess)
            {
                if (bCheck)
                {
                    nLieferbereitschaft = LIEFBER_VERBUND;
                }
                else
                {
                    nLieferbereitschaft = (lRest > 0) ? LIEFBER_QUOTA_VB : LIEFBER_QUOTA_DEF;
                }
            }
            else if (!bCheck)
            {
                nLieferbereitschaft = LIEFBER_QUOTA_DEF;
            }
        }
    }
    return nLieferbereitschaft;
}

void CAeFView::MarkListPos(int pos)
{
    if (GetDlgItem( IDC_COMBO_FREE_PRICE )->IsWindowEnabled())
    {
        CString cstr;
        cstr = m_ListCtl.GetItemText(pos, COL_FVIEW_PZN);
        CString price(m_ListCtl.GetItemText(pos, COL_FVIEW_PREIS));
        FillFreePrice(atol(cstr), price);
    }
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, pos);
}

long CAeFView::SelListPos(CString& ArtName, CString& ArtEinh, CString& Kz, CString& Darr, CString& AEP, CString& TAX,
    CString& TEXTKEY, CString& Opi, CString& KKCode, CString& Einzelhandel, CString& Bestand, CString& Taxlevel,
    CString& Grosso, CString& Codetype, CString& Artcode, CString& GrossoNA, CString& ProdQuota)
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        char s[81];
        sprintf(s, "%ld", pos);
        CString cstr = m_ListCtl.GetItemText(pos, COL_FVIEW_PZN);
        ArtName = m_ListCtl.GetItemText(pos, COL_FVIEW_ARTIKELNAME);
        ArtEinh = m_ListCtl.GetItemText(pos, COL_FVIEW_EINHEIT);
        Kz      = m_ListCtl.GetItemText(pos, COL_FVIEW_KENNZEICHEN);
        Darr    = m_ListCtl.GetItemText(pos, COL_FVIEW_DAF);
        AEP     = m_ListCtl.GetItemText(pos, COL_FVIEW_PREIS);
        TAX     = m_ListCtl.GetItemText(pos, COL_FVIEW_APOPFLICHT);
        TEXTKEY = m_ListCtl.GetItemText(pos, COL_FVIEW_TEXTKEY);
        Opi     = m_ListCtl.GetItemText(pos, COL_FVIEW_OPIAT);
        KKCode  = m_ListCtl.GetItemText(pos, COL_FVIEW_KKCODE);
        Einzelhandel = m_ListCtl.GetItemText(pos, COL_FVIEW_PREISGR4);
        Taxlevel = m_ListCtl.GetItemText(pos, COL_FVIEW_TAXLEVEL);
        Bestand = m_ListCtl.GetItemText(pos, COL_FVIEW_BESTAND);
        Grosso  = m_ListCtl.GetItemText(pos, COL_FVIEW_GROSSO);
        Codetype = m_ListCtl.GetItemText(pos, COL_FVIEW_CODE_TYPE);
        Artcode = m_ListCtl.GetItemText(pos, COL_FVIEW_ARTICLE_CODE);
        GrossoNA = m_ListCtl.GetItemText(pos, COL_FVIEW_GROSSONA);
        ProdQuota = m_ListCtl.GetItemText(pos, COL_FVIEW_PRODQUOTA);

        return atol(cstr);
    }
    return -1L;
}

void CAeFView::SelectArtikelNr(CString ArtNr)
{
    CARTAESEL artaesel;
    strcpy(artaesel.s.ARTICLE_CODE, ArtNr);
    BeginWaitCursor();
    artaesel.Server(AatartSel_NoByCode);
    if (artaesel.rc == SRV_SQLNOTFOUND)
    {
        MsgBoxOK(IDP_PZN_UNBEKANNT);
        return;
    }
    CString cAArt;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
    artaesel.s.FILIALNR = AeGetApp()->FilialNrActual();
    artaesel.s.ETARTKLASSE1 = AeGetApp()->KndKlasse1();
    AllgStrCopy(artaesel.s.PHARMACYGROUPID, AeGetApp()->ActEKGrp(), L_ARTAESEL_PHARMACYGROUPID);
    artaesel.s.CODEBLOCAGE[0] = AeGetApp()->IsPrintCode() ? '1' : '0';
    artaesel.s.POSITIVLISTE[0] = (cAArt == "PL") ? '1' : ' ';
    CloseCursor();
    artaesel.s.FETCH_REL = 1;
    artaesel.s.IMPORTARTICLE = m_iImport;
    artaesel.Server(AatartAa_select);
    m_bCursorOpen = true;   //Datenbankcurser offen

    //Überprüfen vorhandene Kontigentierung
    //Check ob Auftragart ohne Kontingentierung
    if (GetOrderType().IsQuota(AeGetApp()->VzNr(), cAArt))
    {
        CARTIKELQUOTA quota;
        quota.SetBranchno(m_OrgFilNr == 0 ? m_VzNr : m_OrgFilNr);
        quota.SetArticleno(artaesel.s.ARTIKEL_NR);
        quota.SetCustomerno(m_KndNr);
        quota.SetQuotainheritance(CharToShort(AeGetApp()->QuotaInheritance()));

        if (!quota.CheckQuota() )
        {
            long lQuota = quota.GetQuota();
            long lKumqty = quota.GetKumqty();
            long lRest = lQuota - lKumqty;
            if (lRest >= 0)
            {
                if (lRest < artaesel.s.BESTAND)
                    artaesel.s.BESTAND = lRest;
            }
            else
            {
                artaesel.s.BESTAND = 0;
            }
        }
        quota.CloseCursor();
    }
    EndWaitCursor();
    CloseCursor();
    m_ListCtl.DeleteAllItems();
    if (artaesel.rc == SRV_OK)
    {
        m_bBuchungErfolgt = FALSE;
        CLetterMan kb;
        AusgListPos(artaesel, kb.Next());
        if (AeGetApp()->IsBG())
        {
            SetPrices();
        }
        MarkListPos(0);
        if (AeGetApp()->IsBG())
        {
            m_ListCtl.SetFocus();
        }
        else
        {
            SetFocusNoSelection(m_EditMenge);
        }
    }
    else
    {
        SetFocusFullSelection(m_EditArtNr);
    }
}

void CAeFView::PosBuchen(CString ArtName,
                         CString ArtEinh,
                         CString Kz,
                         CString Darr,
                         CString AEP,
                         CString TAX,
                         CString TEXTKEY,
                         CString Opi,
                         CString KKCode,
                         CString Einzelhandel,
                         CString Charge,
                         CString Grosso,
                         CString Codetype,
                         CString Artcode,
                         CString FixBatch)
{
    CString cAArt;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
    if (   GetOrderType().IsNoVideoAufArt(AeGetApp()->VzNr_Kunde(), cAArt)
        || m_lBatchschreiben == 1
        || m_bNoMorePos
        || AeGetApp()->IsNoNewLines() )
    {
        MsgBoxOK(AETXT_NO_NEW_POS);
        return;
    }

    if (AeGetApp()->IsBG() && (Opi == "1") && m_CBTMLicense.IsEmpty())
    {
        OnBTMLicense();
        if (m_CBTMLicense.IsEmpty())
            return;
    }
    double dPreis = 0;
    bool bPreisbuch = false;
    char str[81];

    UpdateData();

    short sPreistyp = 0;
    if (AeGetApp()->IsBG())
    {
        sPreistyp = GetPriceTypeFromCB();
        if (sPreistyp == 1 && KKCode.IsEmpty())
        {
            MsgBoxOK(AETXT_NO_KK_CODE);
            return;
        }
        else
        {
            sPreistyp = CPriceType::CorrectPriceType3(sPreistyp, Opi, Einzelhandel);
        }
    }
    if (!AeGetApp()->IsHR() && !AeGetApp()->IsRS() && !AeGetApp()->IsBG())
    {
        if ((atol(m_CMenge) * atol(AEP)) >= 100000)
        {
            MsgBoxOK(IDP_WARN_HOHER_WERT);
            m_lNoDoubleArtNr = m_ArtNr;
            return;
        }
    }
    else
    {
        if ((atol(m_CMenge) * atol(AEP)) >= 10000000)
        {
            MsgBoxOK(IDP_WARN_HOHER_WERT);
            m_lNoDoubleArtNr = m_ArtNr;
            return;
        }
        if (AeGetApp()->IsRS() && ((atol(m_CMenge) * atol(Grosso)) >= 10000000))
        {
            MsgBoxOK(IDP_WARN_HOHER_WERT);
            m_lNoDoubleArtNr = m_ArtNr;
            return;
        }
    }

    short sKey = static_cast<short>(atoi(TEXTKEY));
    if (sKey > 0)
    {
        CARTIKELTEXT text;
        text.SetBranchno(0);    //wird vielleicht mal angepasst
        text.SetTextkey(sKey);
        if (text.Select() != 0)
        {
            AllgEntfSpaces(text.s.TEXT);
            AllgEntfSpaces(text.s.TEXTHOSPITAL);
            CString cText = text.s.TEXTHOSPITAL;
            if (cText.IsEmpty()) cText = text.s.TEXT;
            if (!cText.IsEmpty())
            {
                CString cTitle = CResString::ex().getStrTblText(AETXT_GELESEN);
                for (;;)
                {
                    if (MsgBoxYesNo(cText, MB_ICONEXCLAMATION | MB_DEFBUTTON2, cTitle) == IDYES)
                        break;
                }
            }
        }
    }

    if (GetDlgItem(IDC_COMBO_FREE_PRICE)->IsWindowEnabled())
    {
        double aep = atof(AEP);
        CString cPreis;
        m_CoboxFreePrice.GetWindowText(cPreis);
        cPreis.Replace(',', '.');
        if (cPreis.Find('%', 0) == -1)
        {
            dPreis = atof(cPreis);
        }
        else
        {
            dPreis = aep * ((100 - (atof(cPreis))) / 100);
        }
        if (dPreis != aep)
            bPreisbuch = true;

    }
    else if (GetDlgItem(IDC_EDIT_FREE_PRICE)->IsWindowEnabled())
    {
        if (!m_CPreis.IsEmpty())
        {
            CString cPreis = m_CPreis;
            AllgCStrCharToChar(cPreis, ',', '.');
            double aep = atof(AEP);
            dPreis = atof(cPreis);
            if (dPreis > aep)
            {
                aep += (aep * AeGetApp()->PriceRange() / 100);
                if (dPreis > aep)
                {
                    CString cstr;
                    cstr.Format(CResString::ex().getStrTblText(IDS_PRICE_OUT), m_CPreis.GetString(), AEP.GetString());
                    if (MsgBoxYesNo(cstr, MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO)
                    {
                        SetFocusFullSelection(m_EditPreis);
                        return;
                    }
                }
            }
            else
            {
                aep -= (aep * AeGetApp()->PriceRange() / 100);
                if (dPreis < aep)
                {
                    CString cstr;
                    cstr.Format(CResString::ex().getStrTblText(IDS_PRICE_OUT), m_CPreis.GetString(), AEP.GetString());
                    if (MsgBoxYesNo(cstr, MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO)
                    {
                        SetFocusFullSelection(m_EditPreis);
                        return;
                    }
                }
            }
            bPreisbuch = true;
            m_CPreis.Empty();
        }
    }

    //keine Menge eingegeben
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
    CString cKArt;
    GetDlgItem(IDC_STATIC_KA)->GetWindowText(cKArt);
    CString cBArt;
    GetDlgItem(IDC_STATIC_BA)->GetWindowText(cBArt);

    // bei SV22 und Zusammenführung gleiche PZN EingabeMenge auf min. 1 setzen
    if (   AeGetApp()->IsPosZusammen() && cAArt == "SV" && cKArt == "2" && cBArt == "2"
        && (m_CMenge.IsEmpty() || (atol(m_CMenge) == 0)) )
    {
        m_CMenge = "1";
    }
    if (   (m_CMenge.IsEmpty() || atol(m_CMenge) == 0L)
        && !(GetOrderType().IsNatraAufArt(AeGetApp()->VzNr_Kunde(), cAArt) && atol(m_CNatRab)) )
    {
        MsgBoxOK(IDP_MENGE_EINGEBEN);
        m_EditMenge.SetFocus();
        return;
    }

    if ((atol(m_CNatRab) > atol(m_CMenge)) && (MsgBoxYesNo(IDP_NATRA_MENGE) != IDYES))
    {
        return;
    }

    if (AeGetApp()->IsKundeKeineBTM())
    {
        CARTAESEL artaesel;
        artaesel.s.FILIALNR = AeGetApp()->FilialNrActual();
        artaesel.s.ARTIKEL_NR = m_ArtNr;
        sprintf(artaesel.s.ARTICLE_CODE, "%d", m_ArtNr);
        artaesel.s.ETARTKLASSE1 = AeGetApp()->KndKlasse1();
        artaesel.s.CODEBLOCAGE[0] = AeGetApp()->IsPrintCode() ? '1' : '0';
        BeginWaitCursor();
        artaesel.Server(AatartAa_sel_artnr);
        EndWaitCursor();
        if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTKLASSE1, 6) && (MsgBoxYesNo(IDP_SOLL_BTM_BUCH) != IDYES))
        {
            return;
        }
    }
    //Sekundaerbezeichner
    if (!Kz.IsEmpty() && Kz.Find('9') >= 0)
    {
        CARTAESEL artaesel;
        artaesel.s.ARTIKEL_NR = m_ArtNr;
        sprintf(artaesel.s.ARTICLE_CODE, "%d", m_ArtNr);
        artaesel.s.FILIALNR = AeGetApp()->FilialNrActual();
        artaesel.s.ETARTKLASSE1 = AeGetApp()->KndKlasse1();
        artaesel.s.CODEBLOCAGE[0] = AeGetApp()->IsPrintCode() ? '1' : '0';
        BeginWaitCursor();
        artaesel.Server(AatartAa_sel_artnr);
        EndWaitCursor();
        CDBestSB dlgBestSB;
        dlgBestSB.m_ArtName     = artaesel.s.ARTIKEL_NAME;
        AllgEntfFirstSpaces(artaesel.s.EINHEIT);
        dlgBestSB.m_ArtEinheit  = artaesel.s.EINHEIT;
        dlgBestSB.m_CDarreichform = artaesel.s.DARREICHFORM;
        dlgBestSB.m_ArtNr.Format("%ld", m_ArtNr);
        ArtName = artaesel.s.ARTIKEL_NAME;
        if (dlgBestSB.DoModal() != IDOK)
            return;
    }

    //Buchungsvariablen initialisieren
    long lMengeBestellt    = atol( m_CMenge );
    long lMengeBestelltOrg = lMengeBestellt;
    long lMengeAbbuchung   = lMengeBestellt;
    long lMengeRest = 0;
    m_NatRab = atol(m_CNatRab);
    m_NatRabBestellt = m_NatRab;
    m_PosStat = m_BuchStat == 0 ? ITEM_STAT_NORMAL : ITEM_STAT_ZUGESAGT;

    //Normaleinstellung nach Buchung
    m_EditMenge.SetWindowText("");
    m_EditNatRab.SetWindowText("");
    m_EditBemerkung.SetWindowText("");
    m_ComboBuchStat.SetCurSel(0);

    CDBePosBearb dlgBePosBearb;
    dlgBePosBearb.SetKndMussKopfBem(m_bKndMussKopfBem);
    dlgBePosBearb.m_KndNr           = m_KndNr;
    dlgBePosBearb.m_IdfNr           = m_IdfNr;

    bool bKeinSekBez = true;
    bool bChangePos = false;
    CAUFPOSBUCH aufposbuch;

    int iCountVB = 0; //wenn mehr als 1 VB-Filiale und eine nicht erreichbar
    // bei SV22 und Zusammenführung gleiche PZN Menge evtl. kummulieren
    // BB (11.06.2007): independent on the type of order, the user will be asked
    //                  if the current article should be cumulate with the same existing one
    CAeDoc* ptrDoc = (CAeDoc*)GetDocument();
    AUFPOSBUCH* ptrPos = ptrDoc->GetPosListe(); //Zeiger auf Beginn der Liste
    if (   (   (AeGetApp()->IsPosZusammen() && cAArt== "SV" && cKArt== "2" && cBArt== "2")
            || AeGetApp()->IsKumPos() )
        || AeGetApp()->IsRS()
        || AeGetApp()->IsBG() )
    {
        for (int i = 0; ; i++)
        {
            ptrPos = ptrDoc->GetListPosition(i);
            if (ptrPos == NULL)
                break;
            if (AllgBitleisteN((Bitleiste)ptrPos->ETPOSSCHALTER2, 11))   //Natraposition duerfen nicht geaendert werden
            {
                continue;
            }
            if (ptrPos->ARTIKEL_NR == m_ArtNr)
            {
                if (AeGetApp()->IsBG())
                {
                    if (ptrPos->PREIS_TYP != sPreistyp)
                        continue;
                    CString abcd = ptrPos->CHARGENNR;
                    abcd.TrimRight();
                    if (Charge != abcd)
                        continue;
                }
                // bei zu hohem Wert keine Zusammenfuehrung
                else if (((ptrPos->MENGEBESTELLT + lMengeBestellt) * atol(AEP)) >= 100000)
                    break;

                if (AeGetApp()->IsRS() || AeGetApp()->IsBG())
                {
                    if (((ptrPos->MENGEBESTELLT + lMengeBestellt) * atol(AEP)) >= 10000000)
                        break;
                    else if (AeGetApp()->IsRS())
                    {
                        if (((ptrPos->MENGEBESTELLT + lMengeBestellt) * atol(Grosso)) >= 10000000)
                            break;
                    }
                }

                // question of cumulation
                if (AeGetApp()->IsDE() && AeGetApp()->IsPosZusammen())
                {
                }
                else
                {
                    if (MsgBoxYesNo(AETXT_CUMULATE_ARTICLE) == IDNO)
                    {
                        if (AeGetApp()->IsRS() || AeGetApp()->IsBG())
                        {
                            return;
                        }
                        break;
                    }
                }
                m_NatRab = aufposbuch.s.MENGENATRA = 0;
                lMengeBestellt = aufposbuch.s.MENGEBESTELLT = ptrPos->MENGEBESTELLT + lMengeBestellt;
                lMengeAbbuchung = aufposbuch.s.MENGEBESTAETIGT = ptrPos->MENGEABGEBUCHT + lMengeAbbuchung;
                m_ArtNr = aufposbuch.s.ARTIKEL_NR = ptrPos->ARTIKEL_NR;
                aufposbuch.s.POSNR = ptrPos->POSNR;
                aufposbuch.s.STATUS = ptrPos->STATUS;
                m_PosStat = ptrPos->STATUS;
                strcpy(aufposbuch.s.BEMERKUNG, (LPCTSTR)m_CBemerkung);
                bChangePos = true;
                break;
            }
        }
    }

    bool bAltArt = false;
    bool bWarnArtBereitsGebucht = false;

    for (;;)
    {
        //doppelte Artikelbuchung verhinderrn  (in RS und BG bereits geprüft)
        if (AeGetApp()->IsRS() || AeGetApp()->IsBG())
        {
        }
        else if (m_ArtNrAlt == m_ArtNr && !bWarnArtBereitsGebucht)
        {
            if (m_lNoDoubleArtNr != m_ArtNr)
            {
                m_lNoDoubleArtNr = 0;
                bWarnArtBereitsGebucht = true;
                if (MsgBoxYesNo(IDP_DOPP_ART_BUCH) != IDYES)
                    return;
            }
        }

        //Versorgung Übergabestruktur
        aufposbuch.s.DISCOUNTVALUEPCT  = 0.0;  //nur bei TargetPromo
        aufposbuch.s.MENGENATRA        = m_NatRab;
        aufposbuch.s.MENGEBESTELLTNATRA = m_NatRabBestellt;
        aufposbuch.s.MENGEBESTELLT     = lMengeBestellt;
        aufposbuch.s.MENGEBESTAETIGT   = lMengeAbbuchung;
        aufposbuch.s.ARTIKEL_NR        = m_ArtNr;
        aufposbuch.s.STATUS = (AeGetApp()->IsBG() && m_bIgnore) ? ITEM_STAT_IGNORE_PRICELIMIT : m_PosStat;
        aufposbuch.s.PREIS_TYP         = sPreistyp;
        aufposbuch.s.DISCOUNTVALPCTMAN = m_dCstDiscount;
        strcpy(aufposbuch.s.BEMERKUNG, (LPCTSTR)m_CBemerkung);
        strcpy(aufposbuch.s.CHARGENNR, (LPCTSTR)Charge);
        aufposbuch.s.FIXBATCH = static_cast<short>(atoi(FixBatch));
        aufposbuch.s.CODE_TYPE = static_cast<short>(atoi(Codetype));
        strcpy(aufposbuch.s.ARTICLE_CODE, Artcode);
        if (bPreisbuch)
        {
            aufposbuch.s.PREISEKAPOFREE = dPreis;
        }

        //Buchungsversuch
        BeginWaitCursor();
        int fkt_nr = bChangePos ? AasrvChangepos : AasrvWritepos;
        aufposbuch.Server(fkt_nr, PIPE_AE_SRV);
        EndWaitCursor();
        if (aufposbuch.rc < SRV_OK)                            // Fehler
        {
            return;
        }
        CDVerbBestaet dlgVerbBestaet; //verbundmenge buchen
        if (aufposbuch.s.STATUS == ITEM_STAT_REVERSE)          // Reverse Substitution
        {
            CARTAESEL artaesel;
            artaesel.s.ARTIKEL_NR = aufposbuch.s.ARTIKEL_NR;
            sprintf(artaesel.s.ARTICLE_CODE, "%d", m_ArtNr);
            artaesel.s.FILIALNR = AeGetApp()->FilialNrActual();
            artaesel.s.ETARTKLASSE1 = AeGetApp()->KndKlasse1();
            artaesel.s.CODEBLOCAGE[0] = AeGetApp()->IsPrintCode() ? '1' : '0';
            BeginWaitCursor();
            artaesel.Server(AatartAa_sel_artnr);
            EndWaitCursor();
            CString revtext;
            revtext.Format(AETXT_REVERSE_SUBSTITUTION, Artcode.GetString(), ArtName.GetString(), artaesel.s.ARTICLE_CODE, artaesel.s.ARTIKEL_NAME);
            if (MsgBoxYesNo(revtext) == IDYES)
            {
                ArtName = artaesel.s.ARTIKEL_NAME;
                AllgEntfFirstSpaces(artaesel.s.EINHEIT);
                ArtEinh = artaesel.s.EINHEIT;
                AllgEntfFirstSpaces(artaesel.s.ARTICLE_CODE);
                Artcode = artaesel.s.ARTICLE_CODE;
                Darr = artaesel.s.DARREICHFORM;
                m_ArtNr = artaesel.s.ARTIKEL_NR;
                continue;
            }
            return;
        }
        if (aufposbuch.s.STATUS == ITEM_STAT_ROEXHAUSTED )           //Rabattauftragswert ueberschritten
        {
            return;
        }

        if (aufposbuch.s.STATUS == ITEM_STAT_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE)             //zugelassener Preis überschritten
        {
            if (MsgBoxYesNo(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_1), MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDYES)
            {
                aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
                continue;
            }
            return;
        }

        if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE)             //zugelassener Preis überschritten
        {
            if (MsgBoxYesNo(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_2), MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDYES)
            {
                aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
                continue;
            }
            return;
        }

        if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION_06)             //zugelassener Preis überschritten
        {
            if (MsgBoxYesNo(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_3), MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDYES)
            {
                aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
                continue;
            }
            return;
        }

        if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_MWP_EXCEEDANCE)            //zugelassener Preis überschritten
        {
            MsgBoxOK(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_0));
            aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
            continue;
        }

        if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION)            //zugelassener Preis überschritten
        {
            MsgBoxOK(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_4));
            m_bIgnore = TRUE;
            aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
        }
        else if (aufposbuch.s.STATUS == ITEM_STAT_KREDITLIMIT )           //Kreditlimit ueberschritten
        {
            if (AeGetApp()->IsBG() )
            {
                if (MsgBoxYesNo(IDP_CHANGE_CO) == IDYES)
                {
                    m_PaymentType.SetAt(0, 'C');
                    CAUFTRAG auftrag;
                    auftrag.s.PAYMENTTYPE[0] = 'C';
                    auftrag.Server(AasrvSetOrderToCash, PIPE_AE_SRV);
                    auftrag.s.VALUTAMONATE = 0L;
                    auftrag.Server(AasrvChangeValuta, PIPE_AE_SRV);
                    continue; //Position erneut buchen
                }
                return;
            }
        }
        else if (iCountVB > 1 && aufposbuch.s.STATUS == ITEM_STAT_VERBUND_NICHT_MOEGLICH)      //Verfügbare Menge reichte nicht aus
        {
            CString cstr;
            cstr.Format(CResString::ex().getStrTblText(IDP_AUX_NOT_POSSIBLE), ppString((long)dlgVerbBestaet.GetActiveVBFiliale()).c_str());
            MsgBoxOK(cstr);
            dlgVerbBestaet.SetIsActive(false);
            if (dlgVerbBestaet.DoModal() == IDOK)
            {
               --iCountVB;
               aufposbuch.s.FILIALNR1 = dlgVerbBestaet.m_VerbFiliale;
               continue; //Position erneut buchen
            }

            if (dlgBePosBearb.DoModal() == IDOK)
            {
                lMengeAbbuchung = dlgBePosBearb.m_Menge;
                m_PosStat       = dlgBePosBearb.GetPosStat();
                m_CBemerkung    = dlgBePosBearb.m_CBemerkung;
                aufposbuch.s.FILIALNR1 = dlgBePosBearb.GetVerbFiliale();
                lMengeRest = lMengeBestellt - dlgBePosBearb.GetBestMenge();    //Ronnie
                lMengeBestellt  = dlgBePosBearb.GetBestMenge();
                continue; //Position erneut buchen
            }
            return;
        }
        else if (aufposbuch.s.STATUS == ITEM_STAT_VERBUND_NICHT_MOEGLICH)
        {
            MsgBoxOK(IDP_AUX_BAD_STATE);
            return;
        }
        else if (   aufposbuch.s.STATUS == ITEM_STAT_KEINE_MENGE    //Verfügbare Menge reichte nicht aus
                 || aufposbuch.s.STATUS == ITEM_STAT_NACHLIEFUPD    //Verfügbare Menge reichte nicht aus wg. Kontigent
                 || (   AeGetApp()->IsNLevelIBTCst()
                     && lMengeBestelltOrg != lMengeBestellt
                     && lMengeRest > 0 ) )
        {
            if (   AeGetApp()->IsNLevelIBTCst()
                && lMengeBestelltOrg != lMengeBestellt
                && lMengeRest > 0 )
            {
                lMengeBestellt = lMengeRest;        //VB vorgaukeln
                aufposbuch.s.MENGE = lMengeBestellt - 1;  //ueber Defektmaske
                AusgAufWerte(aufposbuch.s.ANZPOS, aufposbuch.s.WERTAUFTRAG, aufposbuch.s.WERTLIEFERUNG, aufposbuch.s.WERTZEILEN, aufposbuch.s.BALANCE, aufposbuch.s.BALANCE2, aufposbuch.s.WERTNETTO, aufposbuch.s.WERTRABATT);
            }

            GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->GetWindowText(dlgBePosBearb.m_VerbundZeitKnd);
            if (bAltArt || (!Kz.IsEmpty() && Kz.Find('E') >= 0))    //Ersatzartikel ist vorhanden
            {
                CDAltArt daa;
                daa.m_bKndSchwerpunk3 = m_bKndSchwerpunk3;
                daa.m_bKndSchwerpunk5 = m_bKndSchwerpunk5;
                daa.m_CArtNameOrg = ArtName;
                daa.m_CArtEinhOrg = ArtEinh;
                daa.m_CArtDarrOrg = Darr;
                daa.m_CArtNrOrg.Format("%ld", m_ArtNr);
                aufposbuch.s.MENGE = 0; //eventuelle Verbundmoeglichkeit loeschen
                bKeinSekBez = false;
                CARTALT alt;
                alt.s.ARTIKEL_NR = m_ArtNr;
                BeginWaitCursor();
                alt.Server(AatartSel_art_altern);
                EndWaitCursor();
                if (alt.rc != SRV_OK)
                    return;
                CARTAESEL art;
                art.s.ARTIKEL_NR = alt.s.ARTIKEL_NR_ALTERN;
                sprintf(art.s.ARTICLE_CODE, "%d", alt.s.ARTIKEL_NR_ALTERN);
                art.s.FILIALNR = AeGetApp()->FilialNrActual();
                art.s.ETARTKLASSE1 = AeGetApp()->KndKlasse1();
                art.s.CODEBLOCAGE[0] = AeGetApp()->IsPrintCode() ? '1' : '0';
                BeginWaitCursor();
                art.Server(AatartAa_sel_artnr);
                EndWaitCursor();
                if (alt.rc != SRV_OK)
                    return;
                daa.m_AltArtBest.Format("%ld", art.s.BESTAND);
                daa.m_AngArtBest.Format("%ld", aufposbuch.s.BESTAND);
                AllgEntfFirstSpaces(art.s.EINHEIT);
                daa.m_ArtEinheit    = art.s.EINHEIT;
                daa.m_ArtName       = art.s.ARTIKEL_NAME;
                daa.m_CDarreichform = art.s.DARREICHFORM;
                daa.m_ArtNr.Format("%ld", art.s.ARTIKEL_NR);
                daa.m_KundenNr      = m_KndNr;
                daa.m_CArtCodeOrg   = Artcode;
                CARTAESEL code;
                code.s.ARTIKEL_NR = alt.s.ARTIKEL_NR_ALTERN;
                code.Server(AatartSel_Preferred);
                AllgEntfSpaces(code.s.ARTICLE_CODE);
                daa.m_CArtCodeAltern = code.s.ARTICLE_CODE;
                if (AllgBitleisteN((Bitleiste)art.s.ETARTSCHALTER1, 6))
                    daa.m_bNetto  = TRUE;
                if (AllgBitleisteN((Bitleiste)art.s.ETARTSCHALTER3, 7))
                    daa.m_bNatra  = TRUE;
                if (daa.DoModal() == IDOK)
                {
                    if (daa.m_bOrigArt)
                    {
                        bAltArt = false;
                        Kz = "";
                        continue;
                    }
                    bAltArt = AllgBitleisteN((Bitleiste)art.s.ETARTSCHALTER1, 1) ? true : false;     // true:Nachfolgeartikel
                    Kz = "";
                    ArtName = art.s.ARTIKEL_NAME;
                    ArtEinh = art.s.EINHEIT;
                    m_ArtNr = art.s.ARTIKEL_NR;
                    Darr    = art.s.DARREICHFORM;
                    code.s.ARTIKEL_NR = m_ArtNr;
                    code.Server(AatartSel_Preferred);
                    AllgEntfSpaces(code.s.ARTICLE_CODE);
                    Artcode = code.s.ARTICLE_CODE;
                    continue;
                }
            }

            GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->GetWindowText(dlgVerbBestaet.m_VerbundZeitenKnd);
            if (m_NatRab)
                sprintf(str, "%d + %d", lMengeBestellt, m_NatRab);
            else
                sprintf(str, "%d", lMengeBestellt);
            dlgBePosBearb.SetBestMengeStr("%d", lMengeBestellt);
            dlgVerbBestaet.m_CBestMenge      = str;

            dlgVerbBestaet.m_CArtName        = dlgBePosBearb.m_CArtName      = ArtName;
            dlgVerbBestaet.m_CArtEinh        = dlgBePosBearb.m_CArtEinh      = ArtEinh;
            dlgVerbBestaet.m_CArtCode        = dlgBePosBearb.m_CArtCode      = Artcode;
            dlgVerbBestaet.m_CArtNr                              = _ltoa(m_ArtNr, str, 10);
            dlgBePosBearb.SetArtNr(dlgVerbBestaet.m_CArtNr);
            dlgVerbBestaet.m_CBestand                            = _ltoa(aufposbuch.s.BESTAND, str, 10);
            dlgBePosBearb.SetBestand(dlgVerbBestaet.m_CBestand);
            dlgVerbBestaet.m_VerbMenge                           = aufposbuch.s.MENGE;
            dlgBePosBearb.SetVerbMenge(dlgVerbBestaet.m_VerbMenge);
            dlgVerbBestaet.m_VerbFiliale                         = aufposbuch.s.FILIALNR1;
            dlgBePosBearb.SetVerbFiliale(dlgVerbBestaet.m_VerbFiliale);
            dlgVerbBestaet.m_CDarreichform   = dlgBePosBearb.m_CDarreichform = Darr;
            if (aufposbuch.s.BESTAND > lMengeBestellt)
            {
                dlgBePosBearb.m_LiefMenge = lMengeBestellt;
                if (m_NatRab)   //muss eigentlich sein, wenn die Menge nicht ausreicht
                {
                    dlgBePosBearb.m_LiefMengeNatra = aufposbuch.s.BESTAND - dlgBePosBearb.m_LiefMenge;
                }
            }
            else
            {
                dlgBePosBearb.m_LiefMenge = aufposbuch.s.BESTAND;
            }
            dlgBePosBearb.m_LiefMenge  = aufposbuch.s.BESTAND;
            dlgBePosBearb.SetBestMenge(lMengeBestellt);
            dlgBePosBearb.m_CBemerkung = m_CBemerkung;
            dlgBePosBearb.SetPosStat(m_PosStat);

            //aufposbuch.s.MENGE ist die moegliche Verbundmenge
            if (aufposbuch.s.MENGE > 0 && aufposbuch.s.MENGE + aufposbuch.s.BESTAND >= lMengeBestellt)
            {
                if (dlgVerbBestaet.DoModal() == IDOK)
                {
                    iCountVB = dlgVerbBestaet.GetCount();
                    aufposbuch.s.FILIALNR1 = dlgVerbBestaet.m_VerbFiliale;
                    continue; //Position erneut buchen
                }
            }

            if (!bChangePos) //bei Positions-Aenderungen keine Reimporte
            {
                CDReimport reimp;
                reimp.m_lPZN = m_ArtNr;
                if (reimp.DoModal() == IDOK)
                {
                    bKeinSekBez = false;
                    Kz = "";
                    ArtName = reimp.m_CArtikelName;
                    ArtEinh = reimp.m_CEinheit;
                    m_ArtNr = reimp.m_lPZN;
                    Darr    = reimp.m_CDarfor;
                    aufposbuch.s.FILIALNR1 = 0;
                    CARTAESEL code2;
                    code2.s.ARTIKEL_NR = m_ArtNr;
                    code2.Server(AatartSel_Preferred);
                    AllgEntfSpaces(code2.s.ARTICLE_CODE);
                    Artcode = code2.s.ARTICLE_CODE;
                    continue; //Position erneut buchen
                }
            }

            dlgBePosBearb.SetKndMussKopfBem(m_bKndMussKopfBem);
            dlgBePosBearb.m_KndNr           = m_KndNr;
            dlgBePosBearb.m_IdfNr           = m_IdfNr;
            dlgBePosBearb.SetBestMengeNatra("%d", m_NatRabBestellt);
            if (dlgBePosBearb.DoModal() == IDOK)
            {
                lMengeAbbuchung = dlgBePosBearb.m_Menge;
                m_PosStat       = dlgBePosBearb.GetPosStat();
                m_CBemerkung    = dlgBePosBearb.m_CBemerkung;
                aufposbuch.s.FILIALNR1 = dlgBePosBearb.GetVerbFiliale();
                m_NatRab        = dlgBePosBearb.m_LiefMengeNatra;
                if ((dlgBePosBearb.m_LiefMenge) <= (lMengeBestellt + atol(dlgBePosBearb.GetBestMengeNatra())))
                {
                    lMengeRest = (lMengeBestellt + m_NatRabBestellt) - dlgBePosBearb.m_LiefMenge;   //Ronnie
                    lMengeBestellt = dlgBePosBearb.GetBestMenge();
                    lMengeAbbuchung = dlgBePosBearb.m_LiefMenge - dlgBePosBearb.m_LiefMengeNatra;
                }
                if (dlgBePosBearb.GetMengeVerbund() == 0)
                    lMengeRest = 0;    //Bei Defektbuchung kein Rest, Dsipo oder Nachliefern
                continue; //Position erneut buchen
            }

            return;
        }
        break;
    } //Ende der for (;;)
    if (aufposbuch.s.STATUS == ITEM_STAT_VERBUND_REICHT_NICHT)   //Verfügbare Verbundmenge reichte nicht aus
    {
        CString str;
        str.Format(CResString::ex().getStrTblText(IDS_MENGE), aufposbuch.s.MENGEBESTELLT, aufposbuch.s.MENGEBESTAETIGT, aufposbuch.s.MENGE);
        CString cstr;
        cstr.Format(CResString::ex().getStrTblText(IDP_VB_MENGE_WENIG), str.GetString());
        MsgBoxOK(cstr);
    }
    else if (aufposbuch.s.STATUS == ITEM_STAT_NOREBATE)
    {
        MsgBoxOK(AETXT_NO_STOCK_RAB);
    }

    m_ArtNrAlt        = m_ArtNr;                    //Doppelbuchungen verhindern
    m_bBuchungErfolgt = TRUE;                       //Buchungsstatus setzen
    long lRest;
    CheckKontigent(m_ArtNr, aufposbuch.s.BESTAND, lRest);
    if (bKeinSekBez)
        UpdateLieferbereitschaft(aufposbuch.s.BESTAND);     //Bestand in der Listbox koorigieren
    if (bChangePos)
    {
        ptrDoc->UpdPosition(ptrPos->POSNR, aufposbuch.s);  //Positionsliste aktualisieren
    }
    else
    {
        ((CAeDoc*)GetDocument())->AddPosition(aufposbuch.s);  //Positionsliste erstellen
    }
    AusgAufWerte(aufposbuch.s.ANZPOS, aufposbuch.s.WERTAUFTRAG, aufposbuch.s.WERTLIEFERUNG, aufposbuch.s.WERTZEILEN, aufposbuch.s.BALANCE, aufposbuch.s.BALANCE2, aufposbuch.s.WERTNETTO, aufposbuch.s.WERTRABATT);
    AusgAufWerteBG(aufposbuch.s.WERTNETTO_FV, aufposbuch.s.WERTTAX_FV, aufposbuch.s.WERTNETTO_KK, aufposbuch.s.WERTTAX_KK, aufposbuch.s.WERTNETTO_EH, aufposbuch.s.WERTTAX_EH, aufposbuch.s.WERTEXCLUSIVE);
    if (AeGetApp()->IsBG())
    {
        m_pDlgKnd->SetAndShowCreditLimitValue1(aufposbuch.s.WERTKL1);
        m_pDlgKnd->SetAndShowCreditLimitValue2(aufposbuch.s.WERTKL);
    }
    if (aufposbuch.s.HIGHERCOND)
    {
        CDShowRebates rebate;
        rebate.SetArtNr(aufposbuch.s.ARTIKEL_NR);
        rebate.SetKndNr(m_KndNr);
        rebate.SetFilialNr(m_VzNr);
        rebate.m_cNumber = aufposbuch.s.ARTICLE_CODE;
        rebate.m_cAEP.Format("%0.2lf", aufposbuch.s.PREISEKAPO);
        rebate.m_cMenge.Format("%d", aufposbuch.s.MENGEBESTAETIGT);
        rebate.m_cName = aufposbuch.s.ARTIKEL_NAME;
        rebate.DoModal();
    }
    //gebuchte Zeile ausgeben
    GetDlgItem(IDC_STATIC_MENGE)->SetWindowText(_ltoa(aufposbuch.s.MENGEBESTELLT, str, 10));
    GetDlgItem(IDC_STATIC_EINH)->SetWindowText(aufposbuch.s.EINHEIT);
    GetDlgItem(IDC_STATIC_BEZEI)->SetWindowText(aufposbuch.s.ARTIKEL_NAME);
    GetDlgItem(IDC_STATIC_NATRAB)->SetWindowText(_ltoa(aufposbuch.s.MENGENATRA, str, 10));
    GetDlgItem(IDC_STATIC_ABGEB)->SetWindowText(_ltoa(aufposbuch.s.MENGEABGEBUCHT + aufposbuch.s.MENGENATRA, str, 10));
    GetDlgItem(IDC_STATIC_DARR)->SetWindowText(aufposbuch.s.DARREICHFORM);
    int poscount = 0;
    for (poscount = 0;; poscount++)
    {
        ptrPos = ptrDoc->GetListPosition(poscount);
        if (ptrPos == NULL)
            break;
    }
    for (;;)
    {
        if (poscount < aufposbuch.s.ANZPOS)
        {
            ++poscount;
            BeginWaitCursor();
            aufposbuch.s.POSNR = poscount;
            aufposbuch.Server(AasrvInfposnr, PIPE_AE_SRV);
            ((CAeDoc*)GetDocument())->AddPosition(aufposbuch.s);  //Positionsliste erstellen
            EndWaitCursor();
        }
        else
        {
            break;
        }
    }
    if (m_lActDatum >= m_lDatumDD && !m_Tour.IsEmpty() && m_lDeliveryDate > 0 && aufposbuch.s.MENGEBESTAETIGT > 0)
    {
        AllgEntfSpaces(aufposbuch.s.TOURID);
        if (aufposbuch.s.TOURID[0] != '\0')
        {
            if (m_Tour != aufposbuch.s.TOURID || aufposbuch.s.DELIVERYDATE > m_lDeliveryDate)    //Bei abweichender Tour oder abweichendem Datum Lieferzeit anzeigen
            {
                char cDatum[10];
                char cZeit[10];
                CString tourtext;
                tourtext.Format(CResString::ex().getStrTblText(AETXT_DELIVERYTIMES),
                    AllgDatumLong2CharTTMMJJJJ(aufposbuch.s.DELIVERYDATE, cDatum),
                    AllgZeitLong2CharHHMM(aufposbuch.s.DELIVERYTIME * 100, cZeit));
                MsgBoxOK(tourtext);
            }
        }
    }
}

void CAeFView::OnDblclkListctrlArt(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    BucheListPos();
    *pResult = 0L;
}

void CAeFView::OnInfAuf()
{
    if (AeGetApp()->IsNewF6())
    {
        CDAufAuswahl dlgAufAuswahl;
        dlgAufAuswahl.m_KndNr.Format("%d", m_KndNr);
        dlgAufAuswahl.m_lKndNr = m_KndNr;
        dlgAufAuswahl.m_IdfNr  = m_IdfNr;
        dlgAufAuswahl.m_VzNr   = m_VzNr;
        if (dlgAufAuswahl.DoModal() == IDOK)
        {
            OpenOrder(dlgAufAuswahl.GetAufNr());
        }
        // Ronny hier Auftragswerte vom offenen Auftrag abrufen
        else
        {
            CAUFTRAG auf;
            auf.Server(AasrvGetOrderInfo, PIPE_AE_SRV);
        }
    }
    else
    {
        CDAufInf dlgAufInf;
        dlgAufInf.m_KndNr.Format("%d", m_KndNr);
        dlgAufInf.m_lKndNr = m_KndNr;
        dlgAufInf.m_IdfNr  = m_IdfNr;
        dlgAufInf.m_VzNr   = m_VzNr;
        if (dlgAufInf.DoModal() == IDOK)
        {
            OpenOrder(dlgAufInf.GetAufNr());
        }
        // Ronny hier Auftragswerte vom offenen Auftrag abrufen
        else
        {
            CAUFTRAG auf;
            auf.Server(AasrvGetOrderInfo, PIPE_AE_SRV);
        }
    }
}

void CAeFView::OnUpdateInfAuf(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeFView::OnKundeOffeneAuftrge()
{
    CDCheckOpenCallOrOrder dlgCheckOpenCallOrOrder;
    if (AuftragSave() && (dlgCheckOpenCallOrOrder.DoModal() == IDOK))
    {
        AeGetApp()->IsDispoImportCst = AeGetApp()->IsDispoImport();
        if (dlgCheckOpenCallOrOrder.GetOrderNr())
            OpenOrder(dlgCheckOpenCallOrOrder.GetOrderNr());
        else if (dlgCheckOpenCallOrOrder.GetCustomerNr())
        {
            ((CAeFView*)AeGetApp()->m_pViewEing)->SetOrgFilNr(dlgCheckOpenCallOrOrder.GetVZNr());
            m_OrgFilNr = dlgCheckOpenCallOrOrder.GetVZNr();
            NewOrder(dlgCheckOpenCallOrOrder.GetCustomerNr(), dlgCheckOpenCallOrOrder.GetVZNr());
        }
    }
}

void CAeFView::OnUpdateKundeOffeneAuftrge(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser() || !GetAeUser().Planteil())
        pCmdUI->Enable(FALSE);
}

void CAeFView::OnKundeKundeAusPlan()
{
    if (AuftragSave())
    {
        GetNextPhoneCall getNextPhoneCall;
        if (AeGetApp()->IsNoParaCall())
            getNextPhoneCall.NoParaCalls();
        if (getNextPhoneCall.GetCall() != NO_CUSTOMER)
            NewOrder(getNextPhoneCall.GetKndNum(), getNextPhoneCall.GetKndVZ());
    }
}

void CAeFView::OnUpdateKundeKundeAusPlan(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser() || !GetAeUser().Planteil())
        pCmdUI->Enable(FALSE);
}

void CAeFView::OnAuftragDafzurckgestellteauftrge()
{
    if (AuftragSave())
    {
        CDOffAuftr dlgOffAuftr;
        dlgOffAuftr.m_RegionNr = AeGetApp()->VzNr();
        dlgOffAuftr.m_VzNr = AeGetApp()->VzNr();
        if (dlgOffAuftr.DoModal() == IDOK)
        {
            OpenOrder(dlgOffAuftr.GetAufNr());
        }
    }
}

void CAeFView::OnUpdateAuftragDafzurckgestellteauftrge(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser() || !GetAeUser().Planteil())
        pCmdUI->Enable(FALSE);
}

void CAeFView::OnKundeAnrufen()
{
    MsgBoxOK(IDP_NO_IMPLEMENT);
}

void CAeFView::OnUpdateKundeAnrufen(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnAuftrDef()
{
    OnABKArtDef();
    CString Aufart;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(Aufart);
    if (m_lTenderNo > 0)
    {
        CDTenderOrder dlgTenderOrder;
        dlgTenderOrder.ptrDoc = (CAeDoc*)GetDocument();
        dlgTenderOrder.m_lKndNr = m_IdfNr;
        dlgTenderOrder.m_lTenderNo = m_lTenderNo;
        dlgTenderOrder.DoModal();
    }
    else if (m_sServType > 0)
    {
        CDServiceOrder dlgServiceOrder;
        dlgServiceOrder.m_ptrDoc = (CAeDoc*)GetDocument();
        dlgServiceOrder.m_lKndNr = m_IdfNr;
        dlgServiceOrder.m_sServType = m_sServType;
        dlgServiceOrder.DoModal();
    }
    else if (Aufart == "MP")
    {
        CDProductPromo dlgProductPromo;
        dlgProductPromo.m_ptrDoc = (CAeDoc*)GetDocument();
        dlgProductPromo.m_lCustomerno = m_IdfNr;
        dlgProductPromo.m_sBranchno = m_VzNr;
        dlgProductPromo.DoModal();
    }
}

void CAeFView::OnABKArtDef(BOOL bAendErzwingen, BOOL bBemerkungEingeben, BOOL bPseudoGebucht, BOOL bShowCashOrder)
{
    // Check number of items
    CString csNumberOfItem;
    GetDlgItem(IDC_STATIC_ZLN)->GetWindowText(csNumberOfItem);

    CDAufTxt cAufTxt;
    bool bGebucht = !atol(csNumberOfItem.GetString()) && (((CAeDoc*)GetDocument())->GetListPosition(0) == NULL) &&
        !cAufTxt.UpdateLists(false) && !bPseudoGebucht ? false : true;

    bool bCashOrder = (m_PaymentType.GetAt(0) == 'C') ? true : false;
    if (bCashOrder)
    {
        m_Valuta = 0L;
        m_lDatumValuta = 0L;
    }

    CMAufDef aufDef((CAeDoc*)GetDocument());
    CDAufDef dlgAufDef(aufDef);

    aufDef.SetGebucht(bGebucht); //schneller select zeigt evtl. keine dafuepos an

    aufDef.SetNeuSetzen(bAendErzwingen ? true : false);
    aufDef.SetBemerkungEing(bBemerkungEingeben ? true : false);

    CString Aufalt;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(Aufalt);
    CString AArt;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(AArt);
    aufDef.SetAArt(AArt);
    CString BuchArt;
    GetDlgItem(IDC_STATIC_BA)->GetWindowText(BuchArt);
    aufDef.SetBuchArt(BuchArt);
    CString KommArt;
    GetDlgItem(IDC_STATIC_KA)->GetWindowText(KommArt);
    aufDef.SetKommArt(KommArt);
    CString SubType;
    GetDlgItem(IDC_STATIC_SUBORDER_TYPE)->GetWindowText(SubType);
    aufDef.SetSubType(SubType);
    aufDef.SetValuta(m_Valuta);
    aufDef.SetDatumValuta(m_lDatumValuta);
    aufDef.SetBatchschreiben(m_lBatchschreiben);
    aufDef.SetABemerkung(m_ABemerkung);
    aufDef.SetKndNr(m_KndNr);
    aufDef.SetIdfNr(m_IdfNr);
    aufDef.SetVzNr(m_VzNr);
    aufDef.SetTour(m_Tour);
    aufDef.SetDeliveryDate(m_lDeliveryDate);
    aufDef.SetDatumDelayedDelivery(m_lDatumDD);
    aufDef.SetTenderNo(m_lTenderNo);
    aufDef.SetServType(m_sServType);
    aufDef.SetZuGrund(m_cZuGrund);
    aufDef.SetIVC(m_IVC);
    aufDef.SetCashOrder(bCashOrder);
    aufDef.SetMitRab((m_sFVRabkonto || m_sKKRabkonto) ? true : false);
    aufDef.SetNoRabattKonto(m_bNoRabattKonto ? true : false);
    aufDef.SetShowCashOrder(bShowCashOrder ? true : false);

    if (dlgAufDef.DoModal() != IDOK)
    {
        return;
    }

    m_PaymentType.SetAt(0, aufDef.GetCashOrder() ? 'C' : 'Z');
    GetDlgItem(IDC_STATIC_PAYMENTTYPE)->ShowWindow(aufDef.GetCashOrder() ? SW_SHOW : SW_HIDE);

    m_lDatumDD      = aufDef.GetDatumDelayedDelivery();
    FillPosList();          //Positionsliste aktualisieren
    m_Valuta        = aufDef.GetValuta();
    m_lDatumValuta  = aufDef.GetDatumValuta();
    m_ABemerkung    = aufDef.GetABemerkung();
    m_Tour          = aufDef.GetTour();
    m_lDeliveryDate = aufDef.GetDeliveryDate();
    m_lTenderNo     = aufDef.GetTenderNo();
    m_sServType     = aufDef.GetServType();
    m_cZuGrund      = aufDef.GetZuGrund();
    m_IVC           = aufDef.GetIVC();
    m_bNoRabattKonto = aufDef.GetNoRabattKonto() ? TRUE : FALSE;
    AusgAKBArt(
        aufDef.GetAArt(),
        aufDef.GetBuchArt(),
        aufDef.GetKommArt(),
        aufDef.GetSubType(),
        aufDef.GetBalance(),
        aufDef.GetBalance2() );
    AusgTour();

    long tourtime = atol(m_Tour) / 100;
    SetTimerTour(tourtime * 100); //Ronnie

    // wenn noch nichts gebucht und
    // bereits Daten fuer Anzeige gelesen und
    // neue Auftragsart PL -> dann neu Einlesen
    if (Aufalt != aufDef.GetAArt())
    {
        char error_msg[81];
        CAUFTRAGSART aart;
        aart.SetBranchno(m_VzNr);
        aart.SetKdauftragart(aufDef.GetAArt());

        int rc = ::ServerNr(PIPE_AE_SRV, AasrvSelCscOrderType, (void *)&aart.s, AUFTRAGSART_BES, AUFTRAGSART_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            AeGetApp()->IsOTfixBatch = false;
            AeGetApp()->IsOTwishBatch = false;
            AeGetApp()->IsOTforbiduserchangeBatch = false;
        }
        else
        {
            AeGetApp()->IsOTfixBatch = (aart.GetAllowfixedbatch() == 1);
            AeGetApp()->IsOTwishBatch = (aart.GetAllowdesiredbatch() == 1);
            AeGetApp()->IsOTforbiduserchangeBatch = (aart.GetForbiduserchange() == 1);
        }

        if (AeGetApp()->IsBG())
        {
            GetDlgItem( IDC_STATIC_GESAMT )->ShowWindow(SW_SHOW);
            GetDlgItem( IDC_EDIT_GESAMT )->ShowWindow(SW_SHOW);
            if (GetOrderType().IsOnlyEH(AeGetApp()->VzNr_Kunde(), aufDef.GetAArt()))
            {
                m_ComboTyp.ResetContent();
                GetDlgItem(IDC_STATIC_KK)->EnableWindow(FALSE);
                GetDlgItem(IDC_STATIC_KK)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_EDIT_KK_NETTO)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_EDIT_KK_TAX)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_EDIT_KK_BRUTTO)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_STATIC_EH)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_EH)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_EH_NETTO)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_EH_TAX)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_EH_BRUTTO)->ShowWindow(SW_SHOW);
                BOOL bIsEinzelhandelApo = GetAeUser().IsEinzelhandelApo();
                int nFVCmdShow;
                if (bIsEinzelhandelApo)
                {
                    nFVCmdShow = SW_SHOW;
                    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_FREIVERKAUF));
                    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
                    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_MITUNDOHNE));
                }
                else
                {
                    nFVCmdShow = SW_HIDE;
                    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
                }
                GetDlgItem(IDC_STATIC_FV)->EnableWindow(bIsEinzelhandelApo);
                GetDlgItem(IDC_STATIC_FV)->ShowWindow(nFVCmdShow);
                GetDlgItem(IDC_EDIT_FV_NETTO)->ShowWindow(nFVCmdShow);
                GetDlgItem(IDC_EDIT_FV_TAX)->ShowWindow(nFVCmdShow);
                GetDlgItem(IDC_EDIT_FV_BRUTTO)->ShowWindow(nFVCmdShow);
                m_ComboTyp.SetCurSel(m_ComboTyp.FindString(-1, CResString::ex().getStrTblText(AETXT_EINZELHANDEL)));
            }
            if (aufDef.GetAArt() == "RO") //bei RO kein EH
            {
                GetDlgItem(IDC_STATIC_EH)->EnableWindow(FALSE);
                GetDlgItem(IDC_STATIC_EH)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_EDIT_EH_NETTO)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_EDIT_EH_TAX)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_EDIT_EH_BRUTTO)->ShowWindow(SW_HIDE);
                int ind = m_ComboTyp.FindString(-1, CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
                if (ind != CB_ERR)  //Eintrag gefunden
                    m_ComboTyp.DeleteString(ind);
                ind = m_ComboTyp.FindString(-1, CResString::ex().getStrTblText(AETXT_MITUNDOHNE));
                if (ind != CB_ERR)  //Eintrag gefunden
                    m_ComboTyp.DeleteString(ind);
            }
            if (aufDef.GetAArt() == "CO") //bei CO aktualisieren KL
            {
                m_pDlgKnd->UpdateCreditLimitValues();
            }
        }
        if (!bGebucht && m_bCursorOpen && (aufDef.GetAArt() == "PL"))
        {
            CloseCursor();
            GetPage();
        }
    }
    else if (AeGetApp()->IsBG() && bShowCashOrder)
    {
        m_pDlgKnd->UpdateCreditLimitValues();
    }
    if (aufDef.GetAnzDef() != 0)   //nase
    {
        MsgBoxOK(IDD_DEF_BEIM_UMBUCHEN);
        CDAufBear ab;
        ab.m_bKndSchwerpunk3 = m_bKndSchwerpunk3;
        ab.m_bKndSchwerpunk5 = m_bKndSchwerpunk5;
        GetDlgItem(IDC_STATIC_AA)->GetWindowText(ab.m_CAufArt);
        GetDlgItem(IDC_STATIC_TEL)->GetWindowText(ab.m_CTelNr);
        GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->GetWindowText(ab.m_VerbundZeitenKnd);
        GetDlgItem(IDC_STATIC_TEL_KW)->GetWindowText(ab.m_CKurzWahl);
        ab.m_bDefektAnzeige    = TRUE;
        ab.m_bDefSelVerbund    = FALSE;
        ab.m_bDefSelDfDef      = TRUE;
        ab.m_bDefSelPhonDef    = TRUE;;
        ab.m_bDefSelDfFrText   = FALSE;
        ab.m_bDefSelPhonFrText = FALSE;
        ab.m_iDefNachPos = 0;
        ab.m_bDafueKz = m_bDafueKz;
        ab.ptrDoc = (CAeDoc*)GetDocument();
        CString orderno;
        GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(orderno);
        ab.m_lAuftrNr = atol(orderno);
        ab.m_IdfNr    = m_IdfNr;
        ab.m_VzNr     = m_VzNr;
        ab.m_lKndNr   = m_KndNr;
        ab.m_bKndMussKopfBem   = m_bKndMussKopfBem;
        ab.m_bKz_Kunde_Verbund = m_bKz_Kunde_Verbund;
        ab.m_OrgFilNr = m_OrgFilNr;
        ab.DoModal();
        m_bDafueKz = ab.m_bDafueKz;
        if (ab.m_bArtAnschreiben)
            ArtAnschreiben(ab.m_lMenge, ab.m_CArtName, ab.m_CArtEinh, ab.m_CArtDarr);
        else if (ab.m_bArtUebernehmen)
        {
            orderno.Format("%d", ab.m_lMenge);
            ArtAnschrAusg(orderno, ab.m_CArtName, ab.m_CArtEinh, ab.m_CArtDarr);
        }
    }
}

void CAeFView::AusgTour()
{
    CString tour;
    if (atol(m_Tour))
    {
        char str[81];
        strncpy(str,m_Tour,2);
        str[2] = '\0';
        tour = str;
        tour += ":";
        strncpy(str, m_Tour.Right(4), 2);
        str[2] = '\0';
        tour += str;
        tour += " / ";
        strncpy(str, m_Tour.Right(2), 2);
        str[2] = '\0';
        tour += str;
    }
    else
        tour = "";
    GetDlgItem(IDC_STATIC_TOUR)->SetWindowText(tour);
}

void CAeFView::OnUpdateAuftrDef(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnInfArt()
{
    CString KKCode;
    CString cstr;
    m_EditMenge.GetWindowText(cstr);
    int menge = atol(cstr);
    CDArtInf dlgArtInf;
    dlgArtInf.SetOrgFilialNr(m_OrgFilNr);
    dlgArtInf.SetKndNr(m_KndNr);
    dlgArtInf.m_bAufnahme = TRUE;
    dlgArtInf.m_CBemerkungKond.Empty();
    if (m_bKndSchwerpunk3)
        dlgArtInf.m_CBemerkungKond = CResString::ex().getStrTblText(AETXT_ARB_KREIS_AKTUELL);
    else
        dlgArtInf.m_bNoPriceGroup2 = TRUE;
    if (m_bKndSchwerpunk5)
    {
        if (!dlgArtInf.m_CBemerkungKond.IsEmpty())
        {
            dlgArtInf.m_CBemerkungKond += " / ";
        }
        dlgArtInf.m_CBemerkungKond += CResString::ex().getStrTblText(AETXT_DIABETES);
    }
    else
        dlgArtInf.m_bNoPriceGroup3 = TRUE;
    if (GetFocus() == GetDlgItem(IDC_LISTCTRL_ART))
    {
        CString cstr;
        dlgArtInf.SetArtNr(SelListPos(cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr, KKCode, cstr, cstr, cstr, cstr, cstr, cstr, cstr, cstr));
    }
    short sPreistyp = 0;
    if (AeGetApp()->IsBG())
    {
        sPreistyp = GetPriceTypeFromCB();
        if (sPreistyp == 1 && KKCode.IsEmpty())
        {
            MsgBoxOK(AETXT_NO_KK_CODE);
            return;
        }
    }
    dlgArtInf.m_sPreistyp = sPreistyp;
    dlgArtInf.DoModal();
    long artnr = dlgArtInf.GetArtNr();
    cstr.Format("%d", artnr);
    if (dlgArtInf.m_bAufnahme && (artnr > 0))
    {
        ArtAnschreiben(menge, cstr, "", "");
    }
}

void CAeFView::OnUpdateInfArt(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnAuftrBearb()
{
    CDAufBear dlgAufBear;
    CString cstr;
    dlgAufBear.ptrDoc = (CAeDoc*)GetDocument();
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(dlgAufBear.m_CAufArt);
    GetDlgItem(IDC_STATIC_TEL)->GetWindowText(dlgAufBear.m_CTelNr);
    GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->GetWindowText(dlgAufBear.m_VerbundZeitenKnd);
    GetDlgItem(IDC_STATIC_TEL_KW)->GetWindowText(dlgAufBear.m_CKurzWahl);
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cstr);
    dlgAufBear.m_lAuftrNr = atol(cstr);
    dlgAufBear.m_IdfNr    = m_IdfNr;
    dlgAufBear.m_VzNr     = m_VzNr;
    dlgAufBear.m_lKndNr   = m_KndNr;
    dlgAufBear.m_bDafueKz = m_bDafueKz;
    dlgAufBear.m_bKndMussKopfBem   = m_bKndMussKopfBem;
    dlgAufBear.m_bKz_Kunde_Verbund = m_bKz_Kunde_Verbund;
    dlgAufBear.m_OrgFilNr = m_OrgFilNr;
    dlgAufBear.m_Tour = m_Tour; // Tour auf Auftragskopfebene
    dlgAufBear.m_lDeliveryDate = m_lDeliveryDate;
    dlgAufBear.DoModal();
    m_bDafueKz = dlgAufBear.m_bDafueKz;
    if (dlgAufBear.m_bArtAnschreiben)
        ArtAnschreiben(dlgAufBear.m_lMenge, dlgAufBear.m_CArtName, dlgAufBear.m_CArtEinh, dlgAufBear.m_CArtDarr);
    else if (dlgAufBear.m_bArtUebernehmen)
    {
        cstr.Format("%d", dlgAufBear.m_lMenge);
        ArtAnschrAusg(cstr, dlgAufBear.m_CArtName, dlgAufBear.m_CArtEinh, dlgAufBear.m_CArtDarr);
    }
}

void CAeFView::OnUpdateAuftrBearb(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnBearbDefnachbea()
{
    CDAufBear dlgAufBear;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(dlgAufBear.m_CAufArt);
    GetDlgItem(IDC_STATIC_TEL)->GetWindowText(dlgAufBear.m_CTelNr);
    GetDlgItem(IDC_STATIC_TEL_KW)->GetWindowText(dlgAufBear.m_CKurzWahl);
    GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->GetWindowText(dlgAufBear.m_VerbundZeitenKnd);
    dlgAufBear.m_bDefektAnzeige   = TRUE;
    dlgAufBear.m_bDefSelVerbund = m_bDefSelVerbund;
    dlgAufBear.m_bDefSelDfDef     = m_bDefSelDfDef;
    dlgAufBear.m_bDefSelPhonDef   = m_bDefSelPhonDef;
    dlgAufBear.m_bDefSelDfFrText  = m_bDefSelDfFrText;
    dlgAufBear.m_bDefSelPhonFrText= m_bDefSelPhonFrText;
    dlgAufBear.m_bDafueKz         = m_bDafueKz;
    dlgAufBear.m_iDefNachPos = m_iDefNachPos;
    dlgAufBear.ptrDoc = (CAeDoc *)GetDocument();
    CString cstr;
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cstr);
    dlgAufBear.m_lAuftrNr = atol(cstr);
    dlgAufBear.m_IdfNr    = m_IdfNr;
    dlgAufBear.m_VzNr     = m_VzNr;
    dlgAufBear.m_lKndNr   = m_KndNr;
    dlgAufBear.m_bKndMussKopfBem   = m_bKndMussKopfBem;
    dlgAufBear.m_bKz_Kunde_Verbund = m_bKz_Kunde_Verbund;
    dlgAufBear.m_OrgFilNr = m_OrgFilNr;
    dlgAufBear.DoModal();
    m_bDefSelVerbund  = dlgAufBear.m_bDefSelVerbund;
    m_bDefSelDfDef    = dlgAufBear.m_bDefSelDfDef;
    m_bDefSelPhonDef  = dlgAufBear.m_bDefSelPhonDef;
    m_bDefSelDfFrText = dlgAufBear.m_bDefSelDfFrText;
    m_bDefSelPhonFrText = dlgAufBear.m_bDefSelPhonFrText;
    m_iDefNachPos = dlgAufBear.m_iDefNachPos;
    m_bDafueKz   = dlgAufBear.m_bDafueKz;
    if (dlgAufBear.m_bArtAnschreiben)
        ArtAnschreiben(dlgAufBear.m_lMenge, dlgAufBear.m_CArtName, dlgAufBear.m_CArtEinh, dlgAufBear.m_CArtDarr);
    else if (dlgAufBear.m_bArtUebernehmen)
    {
        cstr.Format("%d", dlgAufBear.m_lMenge);
        ArtAnschrAusg(cstr, dlgAufBear.m_CArtName, dlgAufBear.m_CArtEinh, dlgAufBear.m_CArtDarr);
    }
}

//Anzeige letzte automatische Buchung
void CAeFView::ArtAnschrAusg(CString Menge, CString ArtName, CString ArtEinh, CString ArtDarr)
{
    GetDlgItem(IDC_STATIC_AUT_MENGE)->SetWindowText(Menge);
    GetDlgItem(IDC_STATIC_AUT_EINH)->SetWindowText(ArtEinh);
    GetDlgItem(IDC_STATIC_AUT_BEZEI)->SetWindowText(ArtName);
    GetDlgItem(IDC_STATIC_AUT_DARR)->SetWindowText(ArtDarr);
}

void CAeFView::ArtAnschreiben(long Menge, CString ArtName, CString ArtEinh, CString ArtDarr)
{
    CString name;
    for (int i = 0; i < ArtName.GetLength(); i++)
        if (ArtName.GetAt(i) != ' ' )
            name += ArtName.GetAt(i);
    CString cstr;
    cstr.Format("%d", Menge);
    ArtAnschrAusg(cstr, ArtName, ArtEinh, ArtDarr);
    m_EditMenge.SetWindowText(cstr);
    m_EditZusatz.SetWindowText("");
    long ArtNr = atol(ArtName);
    if (ArtNr > 0)
    {
        cstr.Format("%d", ArtNr);
        m_EditArtNr.SetWindowText(cstr);
        m_EditPackGr.SetWindowText("");
        m_EditDarr.SetWindowText("");
        m_EditMatchCode.SetWindowText("");
        m_EditArtNr.SetFocus();
    }
    else
    {
        m_EditArtNr.SetWindowText("");
        m_EditPackGr.SetWindowText(ArtEinh);
        m_EditDarr.SetWindowText(ArtDarr);
        m_EditMatchCode.SetWindowText(name.Left(8));
        m_EditMatchCode.SetFocus();
    }
    OnOk();
}

void CAeFView::OnUpdateBearbDefnachbea(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnInfKunde()
{
    //Ausgabe der Kundeninformationen
    CKndInf dlgKndInf;
    dlgKndInf.SetIdfNr(m_IdfNr);
    dlgKndInf.SetKndNr(m_KndNr);
    dlgKndInf.SetKndVz(m_VzNr);
    dlgKndInf.DoModal();
}

void CAeFView::OnUpdateInfKunde(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnAufFreitext()
{
    CDAufFrText dlgAufFrText;
    dlgAufFrText.ptrDoc = (CAeDoc*)GetDocument();
    dlgAufFrText.DoModal();
}

void CAeFView::OnUpdateAufFreitext(CCmdUI* pCmdUI)
{
    if (AeGetApp()->IsPF())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeFView::OnAuftragSave()
{
    AuftragSave();
}

BOOL CAeFView::AuftragSave()
{
    CDAufEnd dlgAufEnd;
    if (m_bDafueKz)
    {
        if (MsgBoxYesNo(IDP_DEF_OFFEN,MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDYES)
        {
            OnBearbDefnachbea();
            return FALSE;
        }
        dlgAufEnd.m_bStdDafueZur = true;
    }

    CDOffAuftr dlgOffAuftr;
    dlgOffAuftr.m_RegionNr = AeGetApp()->VzNr();
    dlgOffAuftr.m_VzNr = AeGetApp()->VzNr();
    dlgOffAuftr.m_bDafue = FALSE;

    // Check number of items
    CString csNumberOfItem;
    GetDlgItem(IDC_STATIC_ZLN)->GetWindowText(csNumberOfItem);

    CDAufTxt dlgAufTxt;
    if (!atol((LPCTSTR)csNumberOfItem) && ((CAeDoc*)GetDocument())->GetListPosition(0) == NULL && !dlgAufTxt.UpdateLists(false))
    {
        dlgAufEnd.m_bKeinAuftrag = true; //schneller select zeigt evtl. keine dafuepos an
    }
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(dlgAufEnd.m_AArt);
    GetDlgItem(IDC_STATIC_BA)->GetWindowText(dlgAufEnd.m_BuchArt);
    GetDlgItem(IDC_STATIC_KA)->GetWindowText(dlgAufEnd.m_KommArt);
    GetDlgItem(IDC_STATIC_SUBORDER_TYPE)->GetWindowText(dlgAufEnd.m_SubType);
    CString buffer;
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(buffer);
    dlgAufEnd.m_lAufnr = atol(buffer);
    dlgAufEnd.m_CBemerkung = m_ABemerkung;
    dlgAufEnd.m_cZuGrund   = m_cZuGrund;
    dlgAufEnd.m_Tour       = m_Tour;
    dlgAufEnd.m_IdfNr      = m_IdfNr;
    dlgAufEnd.m_VzNr       = m_VzNr;
    dlgAufEnd.m_KndNr      = m_KndNr;
    dlgAufEnd.m_lDatumDD   = m_lDatumDD;
    dlgAufEnd.ptrDoc       = (CAeDoc*)GetDocument();
    if (m_sFVRabkonto || m_sKKRabkonto)
        dlgAufEnd.m_bMitRab = true;
    if (m_bNoRabattKonto)
        dlgAufEnd.m_bNoRabattKonto = m_bNoRabattKonto;
    if (dlgAufEnd.DoModal() == IDOK)
    {
        AeGetApp()->m_AeLogging.WriteLine(1, "aefview.cpp", "AuftragSave", "Order closed");
        if (AeGetApp()->IsBG())
        {
            if (dlgAufEnd.m_cZuGrund.GetAt(ZU_NO_QTY_NR) == '1' || dlgAufEnd.m_cZuGrund.GetAt(ZU_WAHL_STELLER) == '1')
            {
                m_cZuGrund = dlgAufEnd.m_cZuGrund;
                OnBearbBulgaria(m_cZuGrund);
                return FALSE;
            }
            delete m_plPromo;
            m_plPromo = NULL;
        }
        DeleteKritikView();
        DeleteBranchView();
        m_pDlgKnd->DestroyWindow();     // kein Problem, falls Fenster schon gelöscht
        m_pDlgDown->DestroyWindow();    // kein Problem, falls Fenster schon gelöscht
        AeGetApp()->IsTOOpen = false;
        KillTimer(AEST_ALARM);
        KillTimer(AEST_WAKETOUR);
        m_bDafueKz = false;
        GetDocument()->SetModifiedFlag(FALSE);
        m_ArtNrAlt = 0;
        ((CAeDoc*)GetDocument())->DelPosListe();           //Loeschen der Positionsliste
        EndWaitCursor();
        if (dlgAufEnd.GetStatus() == ORD_WEITERER_AUFTRAG)
        {
            NewOrder(m_KndNr, m_VzNr);
            return FALSE;
        }
        AeGetApp()->SetView(VIEW_LEER);
        if (AeGetApp()->IsNoVA10())
            return TRUE;
        if (AeGetApp()->IsBG())
        {   //  In BG kein check auf offene Auftraege bei folgenden Auftragsarten
            if ( (dlgAufEnd.m_AArt != "MP") ||
                 (dlgAufEnd.m_AArt != "TO") ||
                 (dlgAufEnd.m_AArt != "S1") ||
                 (dlgAufEnd.m_AArt != "S2") ||
                 (dlgAufEnd.m_AArt != "S3") ||
                 (dlgAufEnd.m_AArt != "S4") ||
                 (dlgAufEnd.m_AArt != "S5") )
            {
                return TRUE;
            }
        }
        if (dlgOffAuftr.DoModIfZROrdKnd(m_KndNr, m_VzNr) == IDOK)
        {
            OpenOrder(dlgOffAuftr.GetAufNr());
            return FALSE;   //offener Auftrag wurde gewaehlt
        }
        AeGetApp()->IsNewCallback = AeGetApp()->IsNewCallbackHome();

        return TRUE;
    }
    m_ABemerkung = dlgAufEnd.m_CBemerkung;
    m_Tour       = dlgAufEnd.m_Tour;
    AusgAKBArt(dlgAufEnd.m_AArt, dlgAufEnd.m_BuchArt, dlgAufEnd.m_KommArt, dlgAufEnd.m_SubType);
    AusgTour();
    return FALSE;
}

void CAeFView::OnUpdateAuftragSave(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnKundeKndWahl()
{
    if (AuftragSave())
    {
        CDOffAuftr dlgOffAuftr;
        dlgOffAuftr.m_RegionNr = AeGetApp()->VzNr();
        dlgOffAuftr.m_VzNr = AeGetApp()->VzNr();
        dlgOffAuftr.m_bDafue = FALSE;
        if (AeGetApp()->m_ProCenter.GetHiPathKndNr() == 0)
        {
            if (dlgOffAuftr.DoModIfZROrdGer() == IDOK)
            {
                OpenOrder(dlgOffAuftr.GetAufNr());
                return; //offener Auftrag wurde gewaehlt
            }
            CDKndWahl dlgKndWahl;
            if (dlgKndWahl.DoModal()== IDOK)
            {
                if (dlgOffAuftr.DoModIfZROrdKnd(dlgKndWahl.GetKndNr(), dlgKndWahl.GetKndVz()) == IDOK)
                {
                    OpenOrder(dlgOffAuftr.GetAufNr());
                    return; //offener Auftrag wurde gewaehlt
                }

                if (AeGetApp()->IsDayNight() && !dlgKndWahl.IsAktiv() && (MsgBoxYesNo(IDP_OPEN_KND_AUFT) == IDNO))
                {
                    return;
                }

                m_OrgFilNr = dlgKndWahl.GetKndOrgFiliale();
                NewOrder(dlgKndWahl.GetKndNr(), dlgKndWahl.GetKndVz());
            }
        }
        else
        {
            if (dlgOffAuftr.DoModIfZROrdKnd(AeGetApp()->m_ProCenter.GetHiPathKndNr(), AeGetApp()->m_ProCenter.GetHiPathVzNr()) == IDOK)
            {
                OpenOrder(dlgOffAuftr.GetAufNr());
                return; //offener Auftrag wurde gewaehlt
            }
            NewOrder(AeGetApp()->m_ProCenter.GetHiPathKndNr(), AeGetApp()->m_ProCenter.GetHiPathVzNr());
        }
    }
}

void CAeFView::OnUpdateKundeKndWahl(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser()) pCmdUI->Enable(FALSE);
}

void CAeFView::OnAeKopfFuss()
{
    CDAufTxt dlgAufTxt;
    dlgAufTxt.DoModal();
    int nCmdShow = (AeGetApp()->AnzKopfFuss() == 0) ? SW_HIDE : SW_SHOW;
    GetDlgItem(IDC_STATIC_KOPF_FUSS)->ShowWindow(nCmdShow);
}

void CAeFView::OnUpdateAeKopfFuss(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnContextMenu(CWnd*, CPoint point)
{
    // CG: This function was added by the Pop-up Menu component

    CMenu menu;
    VERIFY(menu.LoadMenu(CG_IDR_POPUP_AE_FVIEW));

    CMenu* pPopup = menu.GetSubMenu(0);
    ASSERT(pPopup != NULL);

    CWnd* pWndPopupOwner = this;
    while (pWndPopupOwner->GetStyle() & WS_CHILD)
        pWndPopupOwner = pWndPopupOwner->GetParent();

    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
}

BOOL CAeFView::PreTranslateMessage(MSG* pMsg)
{
    // CG: This block was added by the Pop-up Menu component
    {
        // Shift+F10: show pop-up menu.
        if (   (   (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)      // If we hit a key and
                && (pMsg->wParam == VK_F10) && ((GetKeyState(VK_SHIFT) & ~1) != 0) )    // it's Shift+F10 OR
            || (pMsg->message == WM_CONTEXTMENU) )                                      // Natural keyboard key
        {
            CRect rect;
            GetClientRect(rect);
            ClientToScreen(rect);

            CPoint point = rect.TopLeft();
            point.Offset(5, 5);
            OnContextMenu(NULL, point);

            return TRUE;
        }
    }

    return CFormViewMultiLang::PreTranslateMessage(pMsg);
}

LRESULT CAeFView::OnCommandHelp(WPARAM /*wParam*/, LPARAM lParam)
{
    if (lParam == 0)
    {
        lParam = HID_BASE_RESOURCE + IDR_MENU_KD_WAHL;
    }
    AfxGetApp()->WinHelp(lParam);
    return TRUE;
}

LRESULT CAeFView::OnHelpHitTest(WPARAM /*wParam*/, LPARAM lParam)
{
//  if (LOWORD(lParam) > 10) { MessageBeep(MB_OK); }//nase Spaßanwendung
    CPoint hit (LOWORD(lParam), HIWORD(lParam));
    CRect rect;
    m_EditMenge.GetWindowRect(rect);
    ScreenToClient(rect);
    rect.NormalizeRect();
    if (rect.PtInRect(hit))
    {
        return HID_BASE_RESOURCE + IDC_EDIT_MENGE;
    }
    else
    {
        m_EditNatRab.GetWindowRect(rect);
        ScreenToClient(rect);
        rect.NormalizeRect();
        if (rect.PtInRect(hit))
        {
            return HID_BASE_RESOURCE + IDC_EDIT_NATRAB;
        }
    }

    return HID_BASE_RESOURCE + IDR_MENU_KD_WAHL;
}

void CAeFView::OnInformationenAuftragsereignisse()
{
    CString cstr;
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cstr);
    CDAuftrEreign dlgAuftrEreign;
    dlgAuftrEreign.m_AuftragsNr = atol(cstr);
    dlgAuftrEreign.DoModal();
}

void CAeFView::OnUpdateInformationenAuftragsereignisse(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnInformationenInfoliste()
{
    CString cstr;
    m_EditMenge.GetWindowText(cstr);
    int menge = atol(cstr);
    CDInfoListe dlgInfoListe;
    dlgInfoListe.m_bAufnahme = TRUE;
    dlgInfoListe.DoModal();
    if (dlgInfoListe.m_ArtNr > 0)
    {
        cstr.Format("%d", dlgInfoListe.m_ArtNr);
        ArtAnschreiben(menge, cstr, "", "");
    }
    else if (dlgInfoListe.m_Name.GetLength() > 2)
    {
        ArtAnschreiben(menge, dlgInfoListe.m_Name, "", "");
    }
}

void CAeFView::OnUpdateInformationenInfoliste(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnInformationenKundenkontakte()
{
    CDKritik dlgKritik;
    dlgKritik.m_CIdf.Format("%ld", m_IdfNr);
    dlgKritik.SetKndVz(m_VzNr);
    dlgKritik.DoModal();
}

void CAeFView::OnUpdateInformationenKundenkontakte(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnInformationenTagesanrufplan()
{
    CDPlanTag dlgPlanTag;
    dlgPlanTag.m_CIdf.Format("%ld", m_IdfNr);
    dlgPlanTag.DoModal();
}

void CAeFView::OnUpdateInformationenTagesanrufplan(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeFView::OnBearbeitenDafuepositionenlschen()
{
    if (MsgBoxYesNo(IDP_SOLL_DAFUE_LOESCH) == IDYES)
    {
        CString buffer;
        GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(buffer);
        CAUFEREIG aufereig;
        aufereig.s.KDAUFTRAGNR = atol(buffer);
        aufereig.s.PERSONALNR = GetAeUser().GetUID();
        aufereig.s.EREIGNISART = 100;
        strcpy(aufereig.s.GERAETNAME, (char*)CResString::ex().getStrTblText(AETXT_LOEDAFUE).GetString());
        aufereig.Server(AaauftIns_auft_ereig);
        CAUFTRAG auftrag;
        auftrag.s.STATUS = ORD_STORNO_DAFUE;
        auftrag.Server(AasrvCloseorder, PIPE_AE_SRV); //Auftrag wird nicht geschlossen, sondern nur Dafue storniert
        auftrag.Server(AasrvGetOrderInfo, PIPE_AE_SRV);
        FillPosList();          //Positionsliste aktualisieren
        InitOrderHead(auftrag); //Membervariablen und Kopfinformationen aktualisieren
    }
}

void CAeFView::OnUpdateBearbeitenDafuepositionenlschen(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(FALSE);
}

BOOL CAeFView::OpenParaOrder(long KundenNr, short VzNr)
{   // open para order
    if (((CAeDoc *)GetDocument())->IsModified() && !AuftragSave())
    {
        return FALSE;
    }
    CDOffAuftr dlgOffAuftr;
    dlgOffAuftr.m_RegionNr = AeGetApp()->VzNr();
    dlgOffAuftr.m_VzNr = AeGetApp()->VzNr();
    if (KundenNr < 0)
    {
        CDKndWahl dlgKndWahl;
        if (dlgKndWahl.DoModal() != IDOK)
            return FALSE;
        KundenNr = dlgKndWahl.GetKndNr();
        VzNr = dlgKndWahl.GetKndVz();
    }
    if (dlgOffAuftr.DoModIfZROrdKnd(KundenNr, VzNr) == IDOK)
    {
        OpenOrder(dlgOffAuftr.GetAufNr());
        return TRUE;    //offener Auftrag wurde gewaehlt
    }
    return FALSE;
}

void CAeFView::OnVerwaltungStandardauftragsart()
{
    if (MsgBoxYesNo(IDP_CHG_KIND_OF_ST_ORDER) != IDYES)
        return;

    CString buffer;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(buffer);
    AeGetApp()->StdAuftArt = buffer;
    CString cStd = buffer;
    GetDlgItem(IDC_STATIC_KA)->GetWindowText(buffer);
    AeGetApp()->StdKommArt = buffer;
    cStd += buffer;
    GetDlgItem(IDC_STATIC_BA)->GetWindowText(buffer);
    AeGetApp()->StdBuchArt = buffer;
    cStd += buffer;
    AeGetApp()->IsStdAKBArt = true;
    char szBuffer[30];
    strcpy(szBuffer, cStd);
    HKEY hKey;
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_STDAKBART, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }
}

void CAeFView::OnUpdateVerwaltungStandardauftragsart(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeFView::OnBearbeitenKundenndern()
{
    if (AeGetApp()->IsBG())
    {
        // Check number of items
        CString csNumberOfItem;
        GetDlgItem(IDC_STATIC_ZLN)->GetWindowText(csNumberOfItem);

        if (atol((LPCTSTR)csNumberOfItem) || !((CAeDoc*)GetDocument())->GetListPosition(0) == NULL)
        {
            MsgBoxOK(AETXT_NO_CHANGE);
            return;
        }
    }
    if (MsgBoxYesNo(IDP_KND_AENDERN_AUFTR) != IDYES)
        return;

    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
        return;

    CAUFTRAG auftrag;
    auftrag.s.IDFNR = dlgKndWahl.GetIdfNr();
    auftrag.s.KUNDENNR = dlgKndWahl.GetKndNr();
    auftrag.s.VERTRIEBSZENTRUMNR = dlgKndWahl.GetKndVz();
    m_OrgFilNr = dlgKndWahl.GetKndOrgFiliale();
    BeginWaitCursor();
    CString buffer;
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(buffer);
    CAUFEREIG aufereig;
    aufereig.s.KDAUFTRAGNR = atol(buffer);
    aufereig.s.PERSONALNR = GetAeUser().GetUID();
    aufereig.s.EREIGNISART = 101;
    strcpy(aufereig.s.GERAETNAME, (char*)CResString::ex().getStrTblText(AETXT_AENKUNDE).GetString());
    aufereig.Server(AaauftIns_auft_ereig);
    if (dlgKndWahl.GetKndVz() == m_VzNr)
    {
        auftrag.s.VERTRIEBSZENTRUMNR = 0;
    }
    auftrag.Server(AasrvChangeCustomer, PIPE_AE_SRV);
    EndWaitCursor();
    if (auftrag.rc < SRV_OK)
        return;
    FillPosList();       //Positionen holen
    InitOrderHead(auftrag);    //Membervariablen und Kopfinformationen aktualisieren
    if (AeGetApp()->IsBG())
    {
        m_pDlgKnd->m_sFilialnr = AeGetApp()->FilialNrActual();
        m_pDlgKnd->m_lKndNr = m_KndNr;
        m_pDlgKnd->InitalWerte();
    }

    //Alle Sonderfälle anzeigen
    m_bDefSelVerbund    = TRUE;
    m_bDefSelDfDef      = TRUE;
    m_bDefSelPhonDef    = TRUE;
    m_bDefSelDfFrText   = TRUE;
    m_bDefSelPhonFrText = TRUE;
    OnBearbDefnachbea();
}

void CAeFView::OnUpdateBearbeitenKundenndern(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
        pCmdUI->Enable(FALSE);
    if (AeGetApp()->IsNoChangeCustomer())
        pCmdUI->Enable(FALSE);
    if (AeGetApp()->IsBG())
    {
        CString cAArt;
        GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
        CString csNumberOfItem;
        GetDlgItem(IDC_STATIC_ZLN)->GetWindowText(csNumberOfItem);
        if (cAArt == "RO" || cAArt.GetAt(1) == 'T')
            pCmdUI->Enable(FALSE);
        if (atoi(csNumberOfItem) > 0)
            pCmdUI->Enable(FALSE);
    }
}

void CAeFView::OnBearbeitenNachlieferpositionen()
{
    CDUpdNachl dlgUpdNachl;
    dlgUpdNachl.m_lKndNr = m_KndNr;
    dlgUpdNachl.m_lIdfNr = m_IdfNr;
    dlgUpdNachl.DoModal();
}

void CAeFView::OnUpdateBearbeitenNachlieferpositionen(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnProtNachlifbearb()
{
    CDProtNachLief dlgProtNachLief;
    dlgProtNachLief.m_CIdfNr.Format("%ld", m_IdfNr);
    dlgProtNachLief.DoModal();
}

void CAeFView::OnUpdateProtNachlifbearb(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::InitVerbundMoegl()               // Verbund moeglich anzeigen
{
    int maxpos = m_ListCtl.GetItemCount();
    BeginWaitCursor();
    for (int pos = 0; pos < maxpos; pos++)
    {
        //Überprüfen vorhandene Kontigentierung
        CString cBestand = m_ListCtl.GetItemText(pos, COL_FVIEW_BESTAND);
        long bestand = atol(cBestand);

        UpdateLieferbereitschaft(bestand, cBestand, pos, true);
    }

    EndWaitCursor();
}

void CAeFView::OnExtrasVerbundZeigen()
{
    if (AeGetApp()->m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_VERBUND_ZEIGEN, MF_BYCOMMAND) == MF_CHECKED)
    {
        m_bKz_Verbund_Moegl = false;    //check war vorher !!!
    }
    else
    {
        m_bKz_Verbund_Moegl = true;
        InitVerbundMoegl();
    }
    char szBuffer[50];
    strcpy(szBuffer, m_bKz_Verbund_Moegl ? "1" : "0");
    HKEY hKey;
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_VBANZEIGE, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }
}

void CAeFView::OnUpdateExtrasVerbundZeigen(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
        pCmdUI->Enable(FALSE);
    pCmdUI->SetCheck(m_bKz_Verbund_Moegl ? 1 : 0);
}

void CAeFView::OnInformationenCallback()
{
    if (!AeGetApp()->IsNewCallback())
    {
        CDCallbackItem dlgCallbackItem;
        dlgCallbackItem.m_lIdf = m_IdfNr;
        dlgCallbackItem.m_sVz = m_VzNr;
        dlgCallbackItem.DoModal();
    }
    else
    {
        CDNewCallback dlgNewCallback;
        dlgNewCallback.m_lIdf = m_IdfNr;
        dlgNewCallback.m_sBranchno = m_VzNr;
        dlgNewCallback.DoModal();
    }
}

void CAeFView::OnUpdateInformationenCallback(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnInformationenCallbackDo()
{
    CDCallbackFetch dlgCallbackFetch;
    dlgCallbackFetch.DoModal();
}

void CAeFView::OnUpdateInformationenCallbackDo(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnAuftragVerbund()
{
    CDVbBuchen dlgVbBuchen;
    InitVbBuchenDlg(dlgVbBuchen);
    dlgVbBuchen.DoModal();
}

void CAeFView::OnUpdateAuftragVerbund(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeFView::OnAuftragDefekte()
{
    CDVbBuchen dlgVbBuchen;
    InitVbBuchenDlg(dlgVbBuchen);
    dlgVbBuchen.m_ifunktion = 1;  // Erstellen Auftrag aus Defekten
    dlgVbBuchen.DoModal();
}

void CAeFView::InitVbBuchenDlg(CDVbBuchen& dlgVbBuchen)
{
    dlgVbBuchen.m_bKndMussKopfBem = m_bKndMussKopfBem;
    CString buffer;
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(buffer);
    dlgVbBuchen.m_lAuftrNr = atol(buffer);
    dlgVbBuchen.m_lKndNr = m_KndNr;
    dlgVbBuchen.m_IdfNr = m_IdfNr;
    dlgVbBuchen.m_VzNr = m_VzNr;
    dlgVbBuchen.m_bGiveProdQuota = AeGetApp()->IsGiveProdQuota();
}

void CAeFView::OnUpdateAuftragDefekte(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
        pCmdUI->Enable(FALSE);
}

HBRUSH CAeFView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CFormViewMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_KNDTEXT)
        pDC->SetTextColor(RGB(200, 0, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_ERACUN)
        pDC->SetTextColor(RGB(200, 0, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_PAYMENTTYPE)
        pDC->SetTextColor(RGB(200, 0, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_RABATTWERT)
        pDC->SetTextColor(RGB(49, 170, 96));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_RABATTWERT2)
        pDC->SetTextColor(RGB(49, 170, 96));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEL_KW)
        pDC->SetTextColor(RGB(0, 0, 200));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_DD)
        pDC->SetTextColor(RGB(0, 0, 200));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_KOPF_FUSS)
    {
        pDC->SetTextColor(RGB(0, 0, 0));
        pDC->SetBkColor(RGB(255, 255, 0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_ORIGINAL_VZ)
        pDC->SetTextColor(RGB(0, 0, 200));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_RECHWERT)
        pDC->SetTextColor(RGB(0, 0, 200));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_RECHWERT_RAB)
        pDC->SetTextColor(RGB(0, 200, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_FV_BRUTTO)
    {
        if (m_sFVRabkonto && !m_bNoRabattKonto)
            pDC->SetTextColor(RGB(0, 0, 200));
        else
            pDC->SetTextColor(RGB(0, 0, 0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_FV_NETTO)
    {
        if (!m_sFVRabkonto || m_bNoRabattKonto)
            pDC->SetTextColor(RGB(0, 0, 200));
        else
            pDC->SetTextColor(RGB(0, 0, 0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_KK_BRUTTO)
    {
        if (m_sKKRabkonto && !m_bNoRabattKonto)
            pDC->SetTextColor(RGB(0, 0, 200));
        else
            pDC->SetTextColor(RGB(0, 0, 0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_KK_NETTO)
    {
        if (!m_sKKRabkonto || m_bNoRabattKonto)
            pDC->SetTextColor(RGB(0, 0, 200));
        else
            pDC->SetTextColor(RGB(0, 0, 0));
    }
    return hbr;
}

void CAeFView::OnExtrasNichtDefekt()
{
    m_bKz_Nur_Liefber = (AeGetApp()->m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_NICHT_DEFEKT, MF_BYCOMMAND) == MF_CHECKED)
        ? FALSE : TRUE; //check war vorher !!!

    if (m_bCursorOpen)   //Datenbankcurser offen
    {
        CloseCursor();
        GetPage();
    }
}

void CAeFView::OnUpdateExtrasNichtDefekt(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(m_bKz_Nur_Liefber ? 1 : 0);
    }
}

void CAeFView::OnTimer(UINT nIDEvent)
{
    if (nIDEvent == AEST_ALARM)
    {
        if (!AeGetApp()->IsOffAufMeld())
        {
            ++m_TimeCount;
            if (m_TimeCount > 400)   // nach 10 Minuten ohne Eingabe
                Beep(1000, 1000);
        }
    }
    else if (nIDEvent == AEST_WAKETOUR)
    {
        KillTimer(AEST_WAKETOUR);
        if (m_lWake2 > 0)
        {
            m_lWake1 = m_lWake2;
            m_lWake2 = 0;
            SetTimer(AEST_WAKETOUR, m_lWake1 , NULL);
            ShowTourCountdown(m_lResttime, IDB_BITMAP_INFO);
            m_lResttime = AeGetApp()->Wake2();
            m_pDlgDown->m_id = IDB_BITMAP_INFO;
        }
        else if (AeGetApp()->Wake2() > 0)
        {
            ShowTourCountdown(m_lResttime, IDB_BITMAP_WARNUNG);
            m_pDlgDown->m_id = IDB_BITMAP_WARNUNG;
            m_pDlgDown->SetBitmap(IDB_BITMAP_WARNUNG);
        }
        else
        {
            ShowTourCountdown(m_lResttime, IDB_BITMAP_INFO);
            m_pDlgDown->m_id = IDB_BITMAP_INFO;
        }
    }

    CFormViewMultiLang::OnTimer(nIDEvent);
}

void CAeFView::ResetContent()
{
    m_EditMatchCode.SetWindowText("");
    m_ComboBuchStat.SetCurSel(0);
    m_EditNormPackung.SetWindowText("");
    m_EditZusatz.SetWindowText("");
    m_EditPackGr.SetWindowText("");
    m_EditNatRab.SetWindowText("");
    m_EditMenge.SetWindowText("");
    m_EditDarr.SetWindowText("");
    m_EditMatchCode.SetWindowText("");
    m_EditBemerkung.SetWindowText("");
    m_EditArtNr.SetWindowText("");
    SetFocusFullSelection(m_EditMenge);
}

LRESULT CAeFView::OnPhoneRing2(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    CDHPCallin call;
    long lKdnr = 0;
    CKNDINF kndinf;
    kndinf.s.VERTRIEBSZENTRUMNR = 0;
    CString cCaption = AeGetApp()->Caption();
    AeGetApp()->m_ProCenter.SetHiPathMesBoxActiv(TRUE);
    if (cCaption.IsEmpty() || !IsDigit(cCaption))
    {
        call.m_csCaption.Empty();
        if (AeGetApp()->TelNr().IsEmpty())
        {
            strcpy(kndinf.s.NAMEAPO, CResString::ex().getStrTblText(AETXT_NO_NUMBER));
        }
        else
        {
            strcpy(kndinf.s.NAMEAPO, AeGetApp()->TelNr());
        }
        strcpy(kndinf.s.ORT, cCaption);
    }
    else
    {
        CMREGION reg;
        reg.s.REGIONNR = AeGetApp()->VzNr();
        reg.s.REGIONTEILNR = atoi(cCaption.Left(2));
        reg.s.REGIONENTYP = 1;

        if (reg.SelRegion())
        {
            CString Fehlmeld;
            Fehlmeld.Format("%s\n%s", CResString::ex().getStrTblText(AETXT_NO_REGION).GetString(), cCaption.GetString());
            MsgBoxOK(Fehlmeld);
            AeGetApp()->m_ProCenter.SetHiPathMesBoxActiv(FALSE);
            return TRUE;
        }
        kndinf.s.VERTRIEBSZENTRUMNR = static_cast<short>(atoi(cCaption.Left(2)));
        kndinf.s.KUNDENNR = atol(cCaption.Mid(2, 7));
        CCUSTOMERDOUBLES doubles;
        doubles.SetKundennr(kndinf.s.KUNDENNR);
        doubles.SetVertriebszentrumnr(kndinf.s.VERTRIEBSZENTRUMNR);
        kndinf.Server(AakundeSel_knd_info_hipath);
        if (kndinf.rc != SRV_OK)
        {
            if (AeGetApp()->TelNr().IsEmpty())
            {
                strcpy(kndinf.s.NAMEAPO, CResString::ex().getStrTblText(AETXT_NO_NUMBER));
            }
            strcpy(kndinf.s.NAMEAPO, AeGetApp()->TelNr());
        }
        else
        {
            lKdnr = kndinf.s.KUNDENNR;
            call.m_csCaption = CResString::ex().getStrTblText(AETXT_PROCENTER);
            if (kndinf.s.ORIGINALFILIALNR == 0 && !AeGetApp()->IsFR())
            {
                SetOrgFilNr(kndinf.s.VERTRIEBSZENTRUMNR);
                if (!doubles.SelDouble())
                {
                    ppString nameVZ;
                    call.m_csOtherBranch.Format("%s %s", CResString::ex().getStrTblText(AETXT_ALTERNATIVFILIALE).GetString(), doubles.GetName(nameVZ));
                }
            }
            else
            {
                SetOrgFilNr(kndinf.s.ORIGINALFILIALNR);
            }
        }
    }
    call.m_csApo = kndinf.s.NAMEAPO;
    call.m_csOrt = kndinf.s.ORT;
    if (lKdnr == 0) //Wenn Kunde nicht umgeschlüsselt ist, dann wenigstens Filiale des Users reinschreiben
    {
        AeGetApp()->m_OECustomerCalls.SetBranchno(AeGetApp()->VzNr());
    }
    else
    {
        AeGetApp()->m_OECustomerCalls.SetBranchno(kndinf.s.VERTRIEBSZENTRUMNR);
    }
    AeGetApp()->m_OECustomerCalls.SetCustomerno(lKdnr);
    AeGetApp()->m_OECustomerCalls.SetCscorderno(0);
    if (call.DoModal() == IDOK)
    {
        if (!AeGetApp()->m_ProCenter.IsDirectCall()) //Direktanruf nicht protokollieren
        {
            AeGetApp()->m_OECustomerCalls.SetCalleffect(1);
            AeGetApp()->m_OECustomerCalls.Insert();
        }
        AeGetApp()->m_ProCenter.SetHiPathCalled(TRUE);
        if (AeGetApp()->m_ProCenter.IsHiPathMesBoxActiv())
        {
            AeGetApp()->m_ProCenter.SetHiPathMesBoxActiv(FALSE);
            AeGetApp()->m_ProCenter.AnswerCall();
        }
        AeGetApp()->m_ProCenter.SetHiPathCallActiv(TRUE);
        if (lKdnr != 0)
        {
            AeGetApp()->m_ProCenter.SetHiPathKndNr(lKdnr);
            AeGetApp()->m_ProCenter.SetHiPathVzNr(kndinf.s.VERTRIEBSZENTRUMNR);
            AeGetApp()->ApothekeName = kndinf.s.NAMEAPO;
            AeGetApp()->Ort = kndinf.s.ORT;
            ((CFrameWndMultiLang*)AeGetApp()->m_pMainWnd)->GetActiveView()->Invalidate();
            ((CFrameWndMultiLang*)AeGetApp()->m_pMainWnd)->GetActiveView()->UpdateWindow();
        }
    }
    else
    {
        if (!AeGetApp()->m_ProCenter.IsDirectCall()) //Direktanruf nicht protokollieren
        {
            AeGetApp()->m_OECustomerCalls.SetCalleffect(0);
            AeGetApp()->m_OECustomerCalls.Insert();
        }
        AeGetApp()->m_ProCenter.SetHiPathCalled(FALSE);
        AeGetApp()->m_ProCenter.SetHiPathMesBoxActiv(FALSE);
    }

    return TRUE;
}

void CAeFView::OnHipathCall()
{
    CString sTelNr;
    GetDlgItem(IDC_STATIC_TEL)->GetWindowText(sTelNr);
    if (AeGetApp()->VzNr() != AeGetApp()->VzNr_Kunde())
    {
        if (sTelNr.GetAt(0) == '0')
        {
            sTelNr = '0' + sTelNr;
        }
        else
        {
            CFILINF filinf;
            filinf.s.FILIALNR = AeGetApp()->VzNr_Kunde();
            filinf.Server(AafilGet_filiale);
            AllgEntfSpaces(filinf.s.VORWAHL);
            const CString cVorwahl = filinf.s.VORWAHL;
            sTelNr = cVorwahl + sTelNr;
            sTelNr = '0' + sTelNr;
        }
    }
    else
    {
        sTelNr = '0' + sTelNr;
    }
    sTelNr.TrimRight();

    AeGetApp()->m_ProCenter.MakeCall(sTelNr);
}

void CAeFView::OnUpdateHipathCall(CCmdUI* pCmdUI)
{
    if ( AeGetApp()->m_ProCenter.IsHiPathLogon() &&
         !AeGetApp()->m_ProCenter.IsHiPathOpen() &&
         !AeGetApp()->m_ProCenter.IsHiPathCallActiv() )
        pCmdUI->Enable(TRUE);
    else
        pCmdUI->Enable(FALSE);
}

void CAeFView::OnEnChangeEditHc()
{
    CString str;
    m_EditHC.GetWindowText(str);
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[ str.GetLength( ) -1 ];              //letztes Zeichen lesen
    if (chN == ',')
    {
        str.GetBufferSetLength(str.GetLength( ) - 1);   //letztes Zeichen löschen
        m_EditHC.SetWindowText(str);                    //String zurückschreiben
        SetFocusFullSelection(m_EditMenge);
    }
}

void CAeFView::OnInformationenUmsatz()
{
    CString buffer;
    CDUmsHercode dlgUmsHercode;
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(buffer);
    dlgUmsHercode.m_lAufnr = atol(buffer);
    dlgUmsHercode.DoModal();
}

void CAeFView::OnUpdateInformationenUmsatz(CCmdUI* /*pCmdUI*/)
{
}

void CAeFView::OnHipathInsTelnr()
{
    const CString sTelNr = AeGetApp()->TelNr();

    if (sTelNr.IsEmpty() || (sTelNr.GetLength() < 4))
    {
        return;
    }

    CCUSTPHON phon;
    phon.SetTelnr(sTelNr);

    phon.SetVertriebszentrumnr((m_OrgFilNr == 0) ? m_VzNr : m_OrgFilNr);

    phon.SetKundennr(m_IdfNr);

    if (phon.Insert() == 0)
    {
        MsgBoxOK(AETXT_NEW_TELN);
    }
}

void CAeFView::OnUpdateHipathInsTelnr(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(AeGetApp()->m_ProCenter.IsHiPathCallActiv() ? TRUE : FALSE);
}

void CAeFView::OnPflegeTelefonnr()
{
    CDTelNr dlgTelNr;
    dlgTelNr.m_CKundennr.Format("%ld", m_IdfNr);
    dlgTelNr.m_CVZ.Format("%d", m_VzNr);
    dlgTelNr.DoModal();
}

void CAeFView::OnUpdatePflegeTelefonnr(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
        pCmdUI->Enable(FALSE);
}

LRESULT CAeFView::OnReNew(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    Invalidate();
    UpdateWindow();
    return 0L;
}

BOOL CAeFView::IsDigit(CString Caption)
{
    int len = Caption.GetLength();
    if (len > 9)
        len = 9;
    for (int i = 0; i < len; i++)
    {
        if (Caption.GetAt(i) < '0' || Caption.GetAt(i) > '9')
            return FALSE;
    }
    return TRUE;
}

//Überprüfen vorhandene Kontigentierung
bool CAeFView::CheckKontigent(long lArtikelnr, long& lBestand, long& lRest)
{
    bool bRet = true;
    lRest = 0L;

    //Check ob Auftragart ohne Kontingentierung
    CString cAArt;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
    if (GetOrderType().IsQuota(AeGetApp()->VzNr(), cAArt))
    {
        CARTIKELQUOTA quota;
        quota.SetBranchno((m_OrgFilNr == 0) ? m_VzNr : m_OrgFilNr);
        quota.SetArticleno(lArtikelnr);
        quota.SetCustomerno(m_KndNr);
        quota.SetQuotainheritance(CharToShort(AeGetApp()->QuotaInheritance()));
        if (quota.CheckQuota() == SRV_OK)
        {
            long lQuota = quota.GetQuota();
            long lKumqty = quota.GetKumqty();
            lRest = lQuota-lKumqty;
            if (lRest >= 0)
            {
                if (lRest < lBestand)
                    lBestand = lRest;
            }
            else
            {
                lBestand = 0L;
            }
            bRet = false;
        }
        quota.CloseCursor();
    }

    return bRet;
}

LRESULT CAeFView::OnPhoneConsult(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    CDConnect connect;
    connect.DoModal();

    return TRUE;
}

void CAeFView::OnEnChangeEditPreis()
{
    CString str;
    m_EditPreis.GetWindowText(str);                     //Preis lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (CLetterMan::InRange(chN, m_ListCtl.GetItemCount()))
    {
        str.GetBufferSetLength(str.GetLength() - 1);    //letztes Zeichen löschen
        m_EditPreis.SetWindowText(str);                 //String zurückschreiben
        int pos = chN - AeGetApp()->Letter_A();
        MarkListPos(pos);
        m_ListCtl.SetFocus();
        return;
    }
    AllgWedDezimalKontr(&m_EditPreis, MAXIMUM_PREIS_STELLEN,MAXIMUM_NACHKOMMA);
}

void CAeFView::FillFreePrice(long lArtikel_nr, CString& Aep)
{
    CString cAArt;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
    if (!GetOrderType().IsFreePrice(m_VzNr, cAArt))
        return;

    m_CoboxFreePrice.ResetContent();
    CPRICEHIST hist;
    hist.SetArtikel_nr(lArtikel_nr);
    for (;;)
    {
        if (hist.Sel())
            break;
        CString cstr;
        cstr.Format("%.2lf",hist.GetAep());
        m_CoboxFreePrice.AddString(cstr);
    }
    if (m_CoboxFreePrice.SelectString(-1, Aep) == CB_ERR)
        m_CoboxFreePrice.SetCurSel(m_CoboxFreePrice.GetCount() - 1);
}

void CAeFView::OnNMClickListctrlArt(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString cstr = m_ListCtl.GetItemText(pos, COL_FVIEW_PZN);

        CString csPreis(m_ListCtl.GetItemText(pos, COL_FVIEW_PREIS));

        FillFreePrice(atol(cstr), csPreis);
    }
    *pResult = 0L;
}

void CAeFView::OnPflegeDdEinzel()
{
    if (AeGetApp()->UseTourManagerCst() == 2)
    {
        CDCstTours dlgCstTours;
        dlgCstTours.m_cIDF.Format("%d", m_KndNr);
        GetDlgItem(IDC_STATIC_APOTHEKE)->GetWindowText(dlgCstTours.m_cName);
        GetDlgItem(IDC_STATIC_ORT)->GetWindowText(dlgCstTours.m_cOrt);
        dlgCstTours.m_VzNr = m_VzNr;
        dlgCstTours.m_lKndNr = m_KndNr;
        dlgCstTours.m_bAnsicht = TRUE;
        dlgCstTours.DoModal();
    }
    else
    {
        CDDelayedCst dlgDelayedCst;
        dlgDelayedCst.m_sVzNr = m_VzNr;
        dlgDelayedCst.m_lKndNr = m_KndNr;
        dlgDelayedCst.DoModal();
    }
}

void CAeFView::OnBearbeitenWirkstoff()
{
    if (GetFocus() != GetDlgItem(IDC_LISTCTRL_ART))
    {
        return;
    }
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDWirkGruppe dlgWirkGruppe;
        dlgWirkGruppe.m_ifunktion = 0;
        dlgWirkGruppe.m_lArtikelNr = atol(m_ListCtl.GetItemText(pos, COL_FVIEW_PZN));
        dlgWirkGruppe.m_sVzNr = m_VzNr;
        dlgWirkGruppe.m_lKndNr = m_KndNr;
        dlgWirkGruppe.DoModal();
    }
}

void CAeFView::OnUpdateBearbeitenWirkstoff(CCmdUI* pCmdUI)
{
    if (!AeGetApp()->IsBG())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeFView::OnBearbOccasion()
{
    CDWirkGruppe dlgWirkGruppe;
    dlgWirkGruppe.m_ifunktion = 1;
    dlgWirkGruppe.m_sVzNr = m_VzNr;
    dlgWirkGruppe.m_lKndNr = m_KndNr;
    dlgWirkGruppe.DoModal();
}

void CAeFView::OnUpdateBearbOccasion(CCmdUI* pCmdUI)
{
    if (!AeGetApp()->IsRS())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeFView::SetTimerTour(long tourtime)
{
    KillTimer(AEST_WAKETOUR);

    if (AeGetApp()->Wake1() == 0)
        return;

    BeginWaitCursor();
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    m_pDlgDown->DestroyWindow();    // kein Problem, falls Fenster schon gelöscht
    if (m_lDatumDD > zeit.s.DATUM)
    {
        return;
    }
    if (tourtime == 0)
        return;
    int tag = 1;
    if (tourtime / 10000 >= 24)
    {
        tourtime -= 240000;
        tag = 2;
    }
    CTime tour = CTimeFromTimeLong(2000, 1, tag, tourtime);
    int restzeit = AeGetApp()->DurchlaufZeit() - AeGetApp()->Verspaetung();
    int hour = restzeit / 60;
    int min = restzeit % 60;
    CTimeSpan durchlauf(0, hour, min, 0);
    tour -= durchlauf;
    CTime tour2 = tour;
    CTime tourRest = tour;
    CTimeSpan warn1(0, AeGetApp()->Wake1() / 60, AeGetApp()->Wake1() % 60, 0);
    CTimeSpan warn2(0, AeGetApp()->Wake2() / 60, AeGetApp()->Wake2() % 60, 0);
    tour -= warn1;
    tour2 -= warn2;
    BeginWaitCursor();
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    CTime acttime = CTimeFromTimeLong(2000, 1, 1, zeit.s.ZEIT);
    if (acttime > tourRest)
        return;

    CTimeSpan diff = CTimeSpanFromTimeLong(zeit.s.ZEIT);

    if ((acttime >= tour2) || (acttime > tour))
    {
        m_lResttime = GetTotalSeconds(tourRest) - GetTotalSeconds(acttime);
        m_lWake1 = 1L;
    }
    if (acttime < tour2)
    {
        if (acttime <= tour)
        {
            tour -= diff;
            m_lWake1 = GetTotalSeconds(tour) * 1000L;
            m_lResttime = (AeGetApp()->Wake1() + AeGetApp()->Wake2()) * 60L;
        }
        if (AeGetApp()->Wake2() == 0)
        {
            m_lWake2 = 0L;
        }
        else if (m_lWake1 > 1L)
        {
            m_lWake2 = ((AeGetApp()->Wake1() - AeGetApp()->Wake2()) * 1000L * 60L);
        }
        else
        {
            tour2 -= diff;
            m_lWake2 = GetTotalSeconds(tour2) * 1000L;
        }
    }
    else
    {
        m_lWake2 = 0L;
        if (AeGetApp()->Wake2() == 0)
        {
            return;
        }
        tour2 -= diff;
    }
    SetTimer(AEST_WAKETOUR, m_lWake1, NULL);
}

void CAeFView::OnAuftragWerte()
{
    CDAufWerte dlgAufWerte;
    dlgAufWerte.DoModal();
}

void CAeFView::OnUpdateAuftragWerte(CCmdUI* pCmdUI)
{
    if (!AeGetApp()->IsRS() && !AeGetApp()->IsHR())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeFView::ShowTourCountdown(long contdowntime, const UINT id)
{
    CWnd* pActive = GetActiveWindow();

    // Dialogfeld erstellen, sofern nicht vorhanden
    if (m_pDlgDown->GetSafeHwnd() == 0)
    {
        m_pDlgDown->m_id = id;
        m_pDlgDown->m_lCountDown = contdowntime;
        m_pDlgDown->Create();   // Dialogfeld anzeigen
    }
    if (pActive != NULL)
    {
        pActive->SetActiveWindow();
    }
}

LRESULT CAeFView::OnGoodbyeDown(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    m_pDlgDown->DestroyWindow();    // kein Problem, falls Fenster schon gelöscht
    return 0L;
}

void CAeFView::SaveListColumns()
{
    AllgWriteColumnWidthUser(m_ListCtl, "CAefview", KEY_PATH, NUM_FVIEW_COLUMNS);
}

void CAeFView::OnBTMLicense()
{
    CDBTMLicense dlgBTMLicense;
    dlgBTMLicense.m_lDatum = m_lDatumBTM;
    dlgBTMLicense.m_CBTMLicense = m_CBTMLicense;
    if (dlgBTMLicense.DoModal() == IDOK)
    {
        m_lDatumBTM = dlgBTMLicense.m_lDatum;
        m_CBTMLicense = dlgBTMLicense.m_CBTMLicense;
    }
}

void CAeFView::OnUpdateBTMLicense(CCmdUI* pCmdUI)
{
    if (!AeGetApp()->IsBG())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeFView::OnPromotionen()
{
    CAeDoc* ptrDoc = (CAeDoc*)GetDocument();

    CDPromotionen dlgPromotionen;
    dlgPromotionen.m_ptrDoc = ptrDoc;
    dlgPromotionen.m_lKundennr = m_KndNr;
    dlgPromotionen.m_sVznr = m_VzNr;
    dlgPromotionen.DoModal();
}

void CAeFView::OnUpdatePromotionen(CCmdUI* pCmdUI)
{
    if (!AeGetApp()->IsBG() || AeGetApp()->IsAuftNoPromo())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeFView::OnCbnSelchangeComboTyp()
{
    if (m_bCursorOpen)
    {
        CloseCursor();
        GetPage();
        SetPrices();
    }
}

LRESULT CAeFView::OnGoodbyeRab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    CWnd* pActive = GetActiveWindow();
    m_pDlgRab->DestroyWindow(); // kein Problem, falls Fenster schon gelöscht
    if (pActive != NULL)
    {
        pActive->SetActiveWindow();
    }
    return 0L;
}

LRESULT CAeFView::OnGoodbyeBInfo(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    m_pDlgBranchInfo->DestroyWindow();  // kein Problem, falls Fenster schon gelöscht
    return 0L;
}

LRESULT CAeFView::OnGoodbyeBKritik(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    m_pDlgKritik->DestroyWindow();  // kein Problem, falls Fenster schon gelöscht
    return 0L;
}

void CAeFView::SetPrices()
{
    if (!AeGetApp()->IsBG())
        return;
    CPREISANZTYP typ;
    typ.SetPreis_typ(GetPriceTypeFromCB());
    if (typ.GetPreis_typ() == 3)
        typ.SetPreis_typ(0);
    int max = m_ListCtl.GetItemCount();
    for (int i = 0 ; i < max; i++)
    {
        typ.SetArtikel_nr(atol(m_ListCtl.GetItemText(i, COL_FVIEW_PZN)));
        if (!typ.SelPreis())
        {
            double dTax;
            char cStd;
            AeGetApp()->GetTaxRates(atoi(m_ListCtl.GetItemText(i, COL_FVIEW_TAXLEVEL)), cStd, dTax);
            double price = (AeGetApp()->KndGruppe() > 0) ? typ.GetPreisekgrosso() : typ.GetPreisekapo();
            CString cPreis;
            cPreis.Format("%0.2lf", (price * (100 + dTax) / 100));
            m_ListCtl.SetItemText(i, COL_FVIEW_PREIS, cPreis);
        }
    }
}

void CAeFView::OnCancel()
{
    if (AeGetApp()->IsBG() && (GetFocus() == GetDlgItem(IDC_LISTCTRL_ART)))
    {
        m_EditArtNr.SetWindowText("");
        SetTextWithFocusNoSelection(m_EditMatchCode, '\0');
    }
}

void CAeFView::OnBearbRabDefs()
{
    CDAufBear dlgAufBear;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(dlgAufBear.m_CAufArt);
    GetDlgItem(IDC_STATIC_TEL)->GetWindowText(dlgAufBear.m_CTelNr);
    GetDlgItem(IDC_STATIC_TEL_KW)->GetWindowText(dlgAufBear.m_CKurzWahl);
    GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->GetWindowText(dlgAufBear.m_VerbundZeitenKnd);
    dlgAufBear.m_bNatraDefs = true;
    dlgAufBear.ptrDoc = (CAeDoc*)GetDocument();
    CString cstr;
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cstr);
    dlgAufBear.m_lAuftrNr = atol(cstr);
    dlgAufBear.m_IdfNr  = m_IdfNr;
    dlgAufBear.m_VzNr   = m_VzNr;
    dlgAufBear.m_lKndNr = m_KndNr;
    dlgAufBear.m_bKndMussKopfBem   = m_bKndMussKopfBem;
    dlgAufBear.m_bKz_Kunde_Verbund = m_bKz_Kunde_Verbund;
    dlgAufBear.m_OrgFilNr = m_OrgFilNr;
    dlgAufBear.DoModal();
}

void CAeFView::OnBearbBulgaria(CString cZuGrund)
{
    if (cZuGrund.GetAt(ZU_WAHL_STELLER) == '1')
    {
        CPROMOTIONEN promotionen;
        promotionen.SetBranchno(m_VzNr);
        if (!m_plPromo )
        {
            m_plPromo = new vector<promostruct>;
        }
        int first = 0;
        for (;;)
        {
            CAUFPOSBUCH aufposbuch;
            aufposbuch.Server(AasrvSelpos, PIPE_AE_SRV);
            if (aufposbuch.rc != SRV_OK)
                break;
            ((CAeDoc*)GetDocument())->AddPosition(aufposbuch.s);
            if (aufposbuch.s.PROMOTION_NO > 0)
            {
                promostruct tmpPromo;
                tmpPromo.CUSTOMERNO = aufposbuch.s.CUSTOMERNO;
                tmpPromo.PROMOTION_NO = aufposbuch.s.PROMOTION_NO;
                tmpPromo.BASE_VALUE = aufposbuch.s.BASE_VALUE;
                tmpPromo.BASEQTY = aufposbuch.s.BASEQTY;
                tmpPromo.DISCOUNTGRPNO = aufposbuch.s.DISCOUNTGRPNO;
                strncpy(tmpPromo.PHARMACYGROUPID, aufposbuch.s.PHARMACYGROUPID, 4);
                if (first == 0)
                {
                    first = 1;
                    m_plPromo->insert(m_plPromo->end(), tmpPromo);
                }
                else
                {
                    int doit = 1;
                    for (m_itPromo = m_plPromo->begin(); m_itPromo < m_plPromo->end(); m_itPromo++)
                    {
                        if (   m_itPromo->PROMOTION_NO == aufposbuch.s.PROMOTION_NO
                            && m_itPromo->BASEQTY == aufposbuch.s.BASEQTY
                            && m_itPromo->CUSTOMERNO == aufposbuch.s.CUSTOMERNO
                            && m_itPromo->BASE_VALUE == aufposbuch.s.BASE_VALUE
                            && !strncmp(m_itPromo->PHARMACYGROUPID, aufposbuch.s.PHARMACYGROUPID, 3)
                            && m_itPromo->DISCOUNTGRPNO == aufposbuch.s.DISCOUNTGRPNO)
                        {
                            doit = 0;   //bereits in Liste
                            break;
                        }
                    }
                    if (doit == 1)
                    {
                        m_plPromo->insert(m_plPromo->end(), tmpPromo);
                    }
                }
            }
        }
        ((CAeDoc*)GetDocument())->m_bAllItemsInList = true;
        //now check wether it is with Steller type 4
        for (m_itPromo = m_plPromo->begin(); m_itPromo < m_plPromo->end(); m_itPromo++)
        {
            promotionen.SetPromotion_no(m_itPromo->PROMOTION_NO);
            promotionen.SetBaseqty(m_itPromo->BASEQTY);
            promotionen.SetBase_value(m_itPromo->BASE_VALUE);
            promotionen.SetCustomerno(m_itPromo->CUSTOMERNO);
            promotionen.SetPharmacygroupid(m_itPromo->PHARMACYGROUPID);
            promotionen.SetDiscountgrpno(m_itPromo->DISCOUNTGRPNO);
            if (promotionen.SelPromoNo() || (promotionen.GetDiscountarticle() == 0))
            {
                m_plPromo->erase(m_itPromo);
                --m_itPromo;
            }
            else
            {
                CARTINF artinf;
                artinf.s.ARTIKEL_NR = promotionen.GetDiscountarticle();
                artinf.s.FILIALNR = m_VzNr;
                artinf.Server(AatartInf_art_nr);
                if (artinf.rc < SRV_OK)
                    break;
                if (artinf.s.STELLER[0] == 'S')
                {
                    CSTELLERTYP typ;
                    typ.SetArticle_no_pack(artinf.s.ARTIKEL_NR);
                    if (typ.SelTyp())
                    {
                        m_plPromo->erase(m_itPromo);
                        --m_itPromo;
                        continue;
                    }
                    if (typ.GetCompack_type() != 4)
                    {
                        m_plPromo->erase(m_itPromo);
                        --m_itPromo;
                    }
                    else    //pruefen ob Steller bereits frueher bearbeitet
                    {
                        CAeDoc* ptrDoc = (CAeDoc*)GetDocument();
                        AUFPOSBUCH* ptrPos = ptrDoc->GetPosListe(); //Zeiger auf Beginn der Liste
                        for (int i = 0; ; i++)
                        {
                            ptrPos = ptrDoc->GetListPosition(i);
                            if (ptrPos == NULL)
                                break;
                            if ((ptrPos->PROMOTYP != 2) || (m_itPromo->PROMOTION_NO == ptrPos->PROMOTION_NO))
                                continue;
                            if (   m_itPromo->PROMOTION_NO == ptrPos->PROMOTION_NO
                                && m_itPromo->BASEQTY == ptrPos->BASEQTY
                                && m_itPromo->CUSTOMERNO == ptrPos->CUSTOMERNO
                                && m_itPromo->BASE_VALUE == ptrPos->BASE_VALUE
                                && !strncmp(m_itPromo->PHARMACYGROUPID, ptrPos->PHARMACYGROUPID, 4)
                                && m_itPromo->DISCOUNTGRPNO == ptrPos->DISCOUNTGRPNO)
                            {
                                if (ptrPos->MENGEBESTELLT > 0)
                                {
                                    m_plPromo->erase(m_itPromo);
                                    --m_itPromo;
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    m_plPromo->erase(m_itPromo);
                    --m_itPromo;
                }
            }
        }
        // Nur noch Steller typ 4
        while (!m_plPromo->empty())
        {
            for (m_itPromo = m_plPromo->begin(); m_itPromo < m_plPromo->end(); m_itPromo++)
            {
                CAeDoc* ptrDoc = (CAeDoc*)GetDocument();
                ptrDoc = (CAeDoc*)GetDocument();
                CDPromotionen Promo;
                Promo.m_sPromoNo = m_itPromo->PROMOTION_NO;
                Promo.m_lKundennr = m_IdfNr;
                Promo.m_sVznr = m_VzNr;
                Promo.m_ptrDoc = ptrDoc;
                Promo.m_lMinMeng = m_itPromo->BASEQTY;
                Promo.m_dMinValue = m_itPromo->BASE_VALUE;
                Promo.m_cEKG = m_itPromo->PHARMACYGROUPID;
                Promo.m_lDISCGRP = m_itPromo->DISCOUNTGRPNO;
                Promo.m_lCustomerno = m_itPromo->CUSTOMERNO;
                if (Promo.DoModal()== IDOK)
                {
                    m_plPromo->erase(m_itPromo);
                }
            }
            if (!m_plPromo->empty())
            {
                if (MsgBoxYesNo(AETXT_WEITERE_STELLER,MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDYES)
                    break;
            }
        }
        if (m_plPromo->empty())
        {
            AeGetApp()->ClearZUGrund(ZU_WAHL_STELLER);
            m_cZuGrund.SetAt(ZU_WAHL_STELLER, '0');
        }
    }
    if (cZuGrund.GetAt(ZU_NO_QTY_NR) == '1')
    {
        OnBearbRabDefs();
    }
}

void CAeFView::OnInformationenRange()
{
    CDShowRanges ranges;
    ranges.DoModal();
}

void CAeFView::OnUpdateInformationenRange(CCmdUI* pCmdUI)
{
    if (!AeGetApp()->IsHR() && !AeGetApp()->IsFR() && !AeGetApp()->IsBG() && !AeGetApp()->IsPF() && !AeGetApp()->IsCH())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeFView::OnMenu33049()
{
    CDShowProforma dlgShowProforma;
    dlgShowProforma.DoModal();
}

void CAeFView::OnUpdateMenu33049(CCmdUI* pCmdUI)
{
    if (!AeGetApp()->IsBG())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeFView::OnAuftrBearbCode(CString cArtCode)
{
    CDAufBear dlgAufBear;
    dlgAufBear.ptrDoc = (CAeDoc*)GetDocument();
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(dlgAufBear.m_CAufArt);
    GetDlgItem(IDC_STATIC_TEL)->GetWindowText(dlgAufBear.m_CTelNr);
    GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->GetWindowText(dlgAufBear.m_VerbundZeitenKnd);
    GetDlgItem(IDC_STATIC_TEL_KW)->GetWindowText(dlgAufBear.m_CKurzWahl);
    CString cstr;
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cstr);
    dlgAufBear.m_lAuftrNr = atol(cstr);
    dlgAufBear.m_IdfNr    = m_IdfNr;
    dlgAufBear.m_VzNr     = m_VzNr;
    dlgAufBear.m_lKndNr   = m_KndNr;
    dlgAufBear.m_bDafueKz = m_bDafueKz;
    dlgAufBear.m_bKndMussKopfBem   = m_bKndMussKopfBem;
    dlgAufBear.m_bKz_Kunde_Verbund = m_bKz_Kunde_Verbund;
    dlgAufBear.m_CArticleCode = cArtCode;
    dlgAufBear.m_OrgFilNr = m_OrgFilNr;
    dlgAufBear.DoModal();
    m_bDafueKz = dlgAufBear.m_bDafueKz;
    if (dlgAufBear.m_bArtAnschreiben)
        ArtAnschreiben(dlgAufBear.m_lMenge, dlgAufBear.m_CArtName, dlgAufBear.m_CArtEinh, dlgAufBear.m_CArtDarr);
    else if (dlgAufBear.m_bArtUebernehmen)
    {
        cstr.Format("%d", dlgAufBear.m_lMenge);
        ArtAnschrAusg(cstr, dlgAufBear.m_CArtName, dlgAufBear.m_CArtEinh, dlgAufBear.m_CArtDarr);
    }
}

void CAeFView::ChangeColumnText()
{
    LV_COLUMN lvC;
    char buffer[80];
    lvC.mask = LVCF_TEXT;
    if (AeGetApp()->IsAnzRabatte())
    {
        strcpy(buffer, (char*)CResString::ex().getStrTblText(AETXT_RABATT).GetString());
    }
    else
    {
        strcpy(buffer, (char*)CResString::ex().getStrTblText(AETXT_TEXT).GetString());
    }
    m_ListCtl.GetColumn(COL_FVIEW_TEXT, &lvC);
    lvC.pszText = buffer;
    m_ListCtl.SetColumn(COL_FVIEW_TEXT, &lvC);
}

void CAeFView::OnAuftragNlBearb()
{
    CDNachlBearb dlgNachlBearb;
    CString cstr;
    GetDlgItem(IDC_STATIC_VERBUND_ZEIT)->GetWindowText(dlgNachlBearb.m_VerbundZeitenKnd);
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cstr);
    dlgNachlBearb.m_lAuftrNr = atol(cstr);
    dlgNachlBearb.ptrDoc = (CAeDoc*)GetDocument();
    dlgNachlBearb.ptrFView = this;
    dlgNachlBearb.m_lKndNr = m_KndNr;
    dlgNachlBearb.m_IdfNr = m_IdfNr;
    dlgNachlBearb.m_VzNr = m_VzNr;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(dlgNachlBearb.m_AArt);
    if (!dlgNachlBearb.DoModal())
    {
        MsgBoxOK(AETXT_NO_RESTDEL_TODO);
    }
}

void CAeFView::OnUpdateAuftragNlBearb(CCmdUI *pCmdUI)
{
    CString AufArt;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(AufArt);
    if ((AufArt != "SV") && (AufArt != "UW") && !AeGetApp()->IsNoNewLines())
    {
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeFView::OnBnClickedRadioImport()
{
    switch (GetCheckedRadioButton(IDC_RADIO_IMPORT1, IDC_RADIO_IMPORT2))
    {
    case IDC_RADIO_IMPORT0:
        m_iImport = 0;
        break;
    case IDC_RADIO_IMPORT1:
        m_iImport = 1;
        break;
    default:
        m_iImport = 2;
        break;
    }
}

void CAeFView::ShowKritikView()
{
    if (!AeGetApp()->IsShowCritics())
        return;
    CWnd* pActive = GetActiveWindow();
    if (m_pDlgKritik->GetSafeHwnd() == 0)
    {
        m_pDlgKritik->m_sBranchno = m_VzNr;
        m_pDlgKritik->m_lCustomerno = m_KndNr;
        m_pDlgKritik->Create(); // Dialogfeld anzeigen
    }
    if (pActive != NULL)
    {
        pActive->SetActiveWindow();
    }
}

void CAeFView::ShowBranchView()
{
    if (!AeGetApp()->IsShowBranchInfo())
        return;
    CWnd* pActive = GetActiveWindow();
    if (m_pDlgBranchInfo->GetSafeHwnd() == 0)
    {
        m_pDlgBranchInfo->m_sBranchNo = m_VzNr;
        m_pDlgBranchInfo->Create(); // Dialogfeld anzeigen
    }
    if (pActive != NULL)
    {
        pActive->SetActiveWindow();
    }
}

void CAeFView::DeleteKritikView()
{
    m_pDlgKritik->DestroyWindow();  // kein Problem, falls Fenster schon gelöscht
}

void CAeFView::DeleteBranchView()
{
    m_pDlgBranchInfo->DestroyWindow();  // kein Problem, falls Fenster schon gelöscht
}

void CAeFView::OnViewNoCritics()
{
    if (AeGetApp()->m_pMainWnd->GetMenu()->GetMenuState(ID_VIEW_NO_CRITICS, MF_BYCOMMAND) == MF_CHECKED)
    {
        AeGetApp()->IsShowCritics = false;
        DeleteKritikView();
    }
    else
    {
        AeGetApp()->IsShowCritics = true;
        ShowKritikView();
    }
}

void CAeFView::OnUpdateViewNoCritics(CCmdUI *pCmdUI)
{
    if (!(AeGetApp()->IsDE() && !AeGetApp()->IsCH() && !AeGetApp()->IsAT()))
    {
        pCmdUI->Enable(FALSE);
    }
    else
    {
        pCmdUI->SetCheck(AeGetApp()->IsShowCritics() ? 1 : 0);
    }
}

void CAeFView::OnViewNoBranchinfo()
{
    if (AeGetApp()->m_pMainWnd->GetMenu()->GetMenuState(ID_VIEW_NO_BRANCHINFO, MF_BYCOMMAND) == MF_CHECKED)
    {
        AeGetApp()->IsShowBranchInfo = false;
        DeleteBranchView();
    }
    else
    {
        AeGetApp()->IsShowBranchInfo = true;
        ShowBranchView();
    }
}

void CAeFView::OnUpdateViewNoBranchinfo(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(FALSE);
}

short CAeFView::GetPriceTypeFromCB()
{
    int selpos = m_ComboTyp.GetCurSel();
    CString chPreistyp;
    m_ComboTyp.GetLBText(selpos, chPreistyp);
    return CharToShort(chPreistyp.GetAt(0));
}

void CAeFView::SetTextWithFocusNoSelection(CEdit& edit, char c)
{
    char s[2];
    s[0] = c;
    s[1] = '\0';
    SetTextWithFocusNoSelection(edit, s);
}

void CAeFView::SetTextWithFocusNoSelection(CEdit& edit, const CString& str)
{
    edit.SetWindowText(str);
    SetFocusNoSelection(edit);
}

void CAeFView::SetFocusNoSelection(CEdit& edit)
{
    edit.SetFocus();
    edit.SetSel(0, -1, FALSE);
    edit.SetSel(-1, 0, FALSE);  // Clear selection
}

void CAeFView::SetFocusFullSelection(CEdit& edit)
{
    edit.SetFocus();
    edit.SetSel(0, -1, FALSE);  // Full selection
}

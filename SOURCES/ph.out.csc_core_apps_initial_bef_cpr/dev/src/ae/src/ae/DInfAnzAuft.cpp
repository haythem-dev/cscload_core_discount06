// DInfAnzAuft.cpp : implementation file
//

#include "stdafx.h"
#include "AeDoc.h"
#include <kndsel.h>
#include "DKndInf.h"
#include <orders.h>
#include "DArtInf.h"
#include "zeitart.h"
#include "DAufTxt.h"
#include "DAuftrEreign.h"
#include "DDruckAuftrag.h"
#include "DAeAnzFrText.h"
#include <artsel.h>
#include "DInfAnzAuft.h"    // als letzter include
#include <verbundcheck.h>
#include "DWannauswahl.h"
#include "DSeralog.h"
#include "MainFrm.h"
#include <auftraginfo.h>
#include <artikel.h>
#include "DNewCallback.h"
#include "DHPMakeCall.h"
#include <taufartk.h>

#define PROD_QUOTA       3
#define LIEFBER_BTM      4
#define LIEFBER_KUEHL    5
#define LIEFBER_KUEHL_U8 6
#define LIEFBER_COOL20   7

//Definition der Tabellenbreite und der Ueberschriften


/////////////////////////////////////////////////////////////////////////////
// CDInfAnzAuft dialog

CDInfAnzAuft::CDInfAnzAuft(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDInfAnzAuft::IDD, pParent)
{
    m_bCall = false;
    m_bNurDef = FALSE;
    m_TenderNo = 0;
    m_Datum = 0;
    m_LAuftNr = 0;
    m_sFVRabkonto = 0;
    m_sKKRabkonto = 0;
    m_bSelProforma = FALSE;
    m_cRechnr = _T("");
    m_cIVCnr = _T("");
    m_ListCtl = new CAufInfListCtrl;
    assert(m_ListCtl);
}

CDInfAnzAuft::~CDInfAnzAuft()
{
    delete m_ListCtl;
    m_ListCtl = 0;
}

void CDInfAnzAuft::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1_INVOICE, m_ListInvoice);
    DDX_Control(pDX, IDC_CHECK_NUR_DEF, m_CBNurDef);
    DDX_Control(pDX, IDC_LIST_AUFTRAG, *m_ListCtl);
    DDX_Check(pDX, IDC_CHECK_NUR_DEF, m_bNurDef);
}


BEGIN_MESSAGE_MAP(CDInfAnzAuft, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_KOPF_FUSS, OnButtonKopfFuss)
    ON_BN_CLICKED(IDC_BUTTON_KOPF_FUSS2, OnButtonKopfFuss2)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_BN_CLICKED(IDC_CHECK_NUR_DEF, OnCheckNurDef)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK_LIEF, OnButtonDruckLief)
    ON_BN_CLICKED(IDC_BUTTON_VB_BUCH, OnButtonVbBuch)
    ON_BN_CLICKED(IDC_BUTTON_DEFBUCH, OnButtonDefbuch)
    ON_BN_CLICKED(IDC_BUTTON_SERALOG, OnButtonSeralog)
    ON_BN_CLICKED(IDC_BUTTON_AUF_NEU, OnButtonAufNeu)
    ON_WM_CTLCOLOR()
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_AUFTRAG, OnLvnColumnclickListAuftrag)
    ON_BN_CLICKED(IDC_BUTTON_AUF_NEU_ALLE, OnBnClickedButtonAufNeuAlle)
    ON_BN_CLICKED(IDC_BUTTON_AUF_CALLBACK, OnBnClickedButtonAufCallback)
    ON_BN_CLICKED(IDC_BUTTON_CREMA_STORNO, OnBnClickedButtonCremaStorno)
    ON_BN_CLICKED(IDC_BUTTON_CREMA_CLOSE, &CDInfAnzAuft::OnBnClickedButtonCremaClose)
    ON_BN_CLICKED(IDC_BUTTON_CALL, OnButtonCall)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDInfAnzAuft message handlers

BOOL CDInfAnzAuft::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_ListCtl->init();
    if (AeGetApp()->IsBG())
    {
        m_ListCtl->SetExtendedStyle(m_ListCtl->GetExtendedStyle() | LVS_EX_GRIDLINES);        // Grid
    }
    m_ListCtl->SetFocus();
    CenterWindow();

    DWORD dwOldBits = m_ListCtl->GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES;
    m_ListCtl->SetExtendedStyle(dwOldBits);

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_OK_YELLOW);
    idResources.push_back(IDI_ICON_LAGER_DEFEKT);
    idResources.push_back(IDI_ICON2);
    idResources.push_back(IDI_ICON_PRODQUOTA);
    idResources.push_back(IDI_ICON_BTM);
    idResources.push_back(IDI_ICON_KUEHL);
    idResources.push_back(IDI_ICON_KUEHL_U8);
    idResources.push_back(IDI_ICON_K20);
    CListCtrlHelper::CreateAndSetImageList(*m_ListCtl, m_ImageSmall, idResources);

    AllgSetColumnWidthUser(*m_ListCtl, "CDInfAnzAuft", KEY_PATH, COL_ANZ_LIST);

    if (!AeGetApp()->IsNewCallback())
    {
        GetDlgItem(IDC_BUTTON_AUF_CALLBACK)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_AUF_CALLBACK)->EnableWindow(FALSE);
    }
    if (AeGetApp()->m_ProCenter.IsHiPathLogon())
    {
        GetDlgItem(IDC_BUTTON_CALL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_CALL)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_ANRUFEN));
    }

    if (AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_WERT_NETTO)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_WERT_NETTO)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_NETTOWERT)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NETTOWERT)->ShowWindow(SW_SHOW);
    }

    //Ausgabe Kopf
    AusgKopf();

    CPARAUFBEARB paraufbearb;
    BeginWaitCursor();
    paraufbearb.s.FILIALNR = m_VzNr;
    paraufbearb.Server(AafilSelaufbearb);
    EndWaitCursor();
    AeGetApp()->IsAutoBuchungNachlieferung = (paraufbearb.s.AUTOMNACHLIEF[0] == '1');
    AeGetApp()->IsCool20 = (paraufbearb.s.SCOOL20 == 1);
    AeGetApp()->IsBTMextra = (paraufbearb.s.BTM_EXTRA[0] == '1');
    AeGetApp()->IsNoValuta = (paraufbearb.s.SNOCHANGEVAL[0] == '1');
    AeGetApp()->IsKumPos = (paraufbearb.s.SKUMPOS[0] == '1');
    AeGetApp()->IsPrintCode = (paraufbearb.s.SANZPRINTCODE[0] == '1');
    AeGetApp()->IsIBTdirect = (paraufbearb.s.SCLOSEIBTATONCE == 1);
    AeGetApp()->IsNewCallback = (paraufbearb.s.SWNEWCALLBACK == 1);
    AeGetApp()->IsStopCrema = (paraufbearb.s.SSTOPCREMA == 1);
    AeGetApp()->IsNLevelIBTCst = (paraufbearb.s.NLEVELIBT == 1);
    AeGetApp()->IsNlSofort = (paraufbearb.s.SCLOSERESTDELIVERYATONCE == 1);
    AeGetApp()->IsDispoSofort = (paraufbearb.s.SCLOSEDISPOATONCE == 1);

    //Einlesen Positionen in verkettete Liste class list
    ReadPos();

    //Listbox fuellen
    AusgPos();

    //Entscheidung ob Kopf- und Fußzeilen
    IfKopfOrFussZln();

    if (AeGetApp()->IsBG())
    {
        GetDlgItem(IDC_STATIC_DRIVER)->ShowWindow(SW_SHOW);
        ppString name;
        CDRIVER driver;
        driver.SetKdauftragnr(m_AuftrNr);
        if (m_Datum == 0)
        {
            if (!driver.SelAct())
            {
                driver.GetDrivername(name);
            }
        }
        else
        {
            driver.SetDatum(m_Datum);
            if (!driver.SelOld())
            {
                driver.GetDrivername(name);
            }
        }
        GetDlgItem(IDC_STATIC_DRIVER)->SetWindowText(name);
        CCSTREBATETYPE rtyp;
        rtyp.SetVertriebszentrumnr(m_VzNr);
        rtyp.SetKundennr(m_KndNr);
        rtyp.SelRebateType();
        m_sFVRabkonto = rtyp.GetRebatemethfreesale();
        m_sKKRabkonto = rtyp.GetRebatemethhealthf();

        CString cAA;
        GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAA);
        if (cAA == "RO")
        {
            GetDlgItem(IDC_BUTTON_VB_BUCH)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_VB_BUCH)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_BUTTON_DEFBUCH)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_DEFBUCH)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_BUTTON_AUF_NEU)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_AUF_NEU)->ShowWindow(SW_HIDE);
        }
    }

    return FALSE;   // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDInfAnzAuft::IfKopfOrFussZln()
{
    CAUFTEXTE auftexte;
    auftexte.s.BEMERKUNGSART = AUF_TEXT_KOPF_INFO;
    auftexte.s.FETCH_REL = 1;
    int nKopf;
    for (nKopf = 0; ; nKopf++)
    {
        if (m_Datum == 0)
            auftexte.Server(AasrvSelKopfZlnAuf, PIPE_AE_SRV);
        else
            auftexte.Server(AaauftSel_alt_kopf);
        if (auftexte.rc != SRV_OK)
            break;
    }
    // Schliessen Cursor
    if (m_Datum != 0)
    {
        auftexte.s.FETCH_REL = 0;
        auftexte.Server(AaauftSel_alt_kopf);
    }
    auftexte.s.BEMERKUNGSART = AUF_TEXT_FUSS_INFO;
    auftexte.s.FETCH_REL = 1;
    int nFuss;
    for (nFuss = 0; ; nFuss++)
    {
        if (m_Datum == 0)
            auftexte.Server(AasrvSelKopfZlnAuf, PIPE_AE_SRV);
        else
            auftexte.Server(AaauftSel_alt_kopf);
        if (auftexte.rc != SRV_OK)
            break;
    }
    // Schliessen Cursor
    if (m_Datum != 0)
    {
        auftexte.s.FETCH_REL = 0;
        auftexte.Server(AaauftSel_alt_kopf);
    }
    if (nKopf == 0 && nFuss == 0)
        GetDlgItem(IDC_BUTTON_KOPF_FUSS)->EnableWindow(FALSE);
}

void CDInfAnzAuft::AusgKopf()
{
    CAUFTRAG auftrag;
    CKNDINF kndinf;
    CAUFLAGER auflager;
    CINVOICENOS invoicenos;
    CINVOICENOSOLD invoicenosold;
    CAUFEREIG aufereig;
    CString cstr;
    char text[81];

    BeginWaitCursor();
    auftrag.s.STATUS = ORD_ZUM_LESEN_OEFFNEN;
    auftrag.s.KDAUFTRAGNR = m_AuftrNr;
    auftrag.s.ANZPOS = m_Datum;
    if (m_Datum == 0)
    {
        auftrag.Server(AasrvOpenInfoorder, PIPE_AE_SRV);
        if (auftrag.s.ZUGRUND[ZU_KREDITLIMIT] == '1')
        {
            if (GetAeUser().IsStornoCremaOrder())
            {
                if (auftrag.s.STATUS == ORD_ZURUECKGESTELLT || auftrag.s.STATUS == ORD_DAFUE_FEHLER)
                {
                    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->EnableWindow(TRUE);
                    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->ShowWindow(SW_SHOW);
                }
            }
            if (GetAeUser().Is2ndLevel())
            {
                if (auftrag.s.STATUS == ORD_ZURUECKGESTELLT || auftrag.s.STATUS == ORD_DAFUE_FEHLER)
                {
                    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->EnableWindow(TRUE);
                    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->ShowWindow(SW_SHOW);
                }
            }
        }
    }
    else
    {
        auftrag.Server(AaauftSel_alt_auft);
    }
    if (auftrag.rc < SRV_OK)
    {
        EndWaitCursor();
        OnOK();
        return ;
    }
    if (m_Datum == 0)
    {
        ppString text2;
        invoicenos.SetCscorderno(m_AuftrNr);
        for (;;)
        {
            if (invoicenos.SelList() != SRV_OK)
                break;
            GetDlgItem(IDC_STATIC_RECHNR2)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_RECHNR2)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_LIST1_INVOICE)->EnableWindow(TRUE);
            GetDlgItem(IDC_LIST1_INVOICE)->ShowWindow(SW_SHOW);
            invoicenos.GetRemarktext(text2);
            m_ListInvoice.AddString(text2);
        }
    }
    else
    {
        ppString text2;
        invoicenosold.SetCscorderno(m_AuftrNr);
        invoicenosold.SetDatum(m_Datum);
        for (;;)
        {
            if (invoicenosold.SelList() != SRV_OK)
                break;
            GetDlgItem(IDC_STATIC_RECHNR2)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_RECHNR2)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_LIST1_INVOICE)->EnableWindow(TRUE);
            GetDlgItem(IDC_LIST1_INVOICE)->ShowWindow(SW_SHOW);
            invoicenosold.GetRemarktext(text2);
            m_ListInvoice.AddString(text2);
        }
    }
    m_TenderNo = auftrag.s.TENDERNO;
    kndinf.s.IDFNR = auftrag.s.IDFNR;
    kndinf.s.KUNDENNR = auftrag.s.KUNDENNR;
    kndinf.s.VERTRIEBSZENTRUMNR = auftrag.s.VERTRIEBSZENTRUMNR;
    kndinf.Server(AakundeSel_knd_info);
    m_lEtartklasse1 = kndinf.s.ETARTKLASSE1;
    aufereig.s.KDAUFTRAGNR= auftrag.s.KDAUFTRAGNR;
    aufereig.s.DATUM = m_Datum;
    aufereig.s.FETCH_REL  = 1;   //normaler Fetch
    aufereig.Server( AaauftAusg_auft_ereig );
    AllgDatumLong2CharTTMMJJJJ(aufereig.s.DATUM, text);
    GetDlgItem(IDC_STATIC_DATUM)->SetWindowText(text);
    m_lDatumAuftrag = aufereig.s.DATUM;
    aufereig.s.DATUM = m_Datum;
    aufereig.s.FETCH_REL  = 0;   //close Cursor
    aufereig.Server( AaauftAusg_auft_ereig );

    // --> lesen für Anzeige auftragartkd.orderlabelcount
    CAUFTRAGARTKD customerOrderType;
    customerOrderType.SetIdfnr(kndinf.s.IDFNR);
    customerOrderType.SetVertriebszentrumnr(kndinf.s.VERTRIEBSZENTRUMNR);
    customerOrderType.SetKdauftragart(auftrag.s.KDAUFTRAGART);

    if (   AeGetApp()->IsMSV3()
        && ::ServerNr(PIPE_AE_SRV, AasrvGetCustOrderType, (void*)&customerOrderType.s, AUFTRAGARTKD_BES, AUFTRAGARTKD_ANZ, text) == 0 )
    {
        sprintf(text, "%d", customerOrderType.GetOrderlabelcount());
        GetDlgItem(IDC_STATIC_ORDERLABELCOUNT)->SetWindowText(text);
        GetDlgItem(IDC_STATIC_ORDERLABELCOUNT)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_ORDERLABCNT)->ShowWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_ORDERLABELCOUNT)->SetWindowText("");
        GetDlgItem(IDC_STATIC_ORDERLABELCOUNT)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_ORDERLABCNT)->ShowWindow(FALSE);
    }

    EndWaitCursor();
    m_KndNr = kndinf.s.KUNDENNR;
    m_IdfNr = kndinf.s.IDFNR;
    m_VzNr = kndinf.s.VERTRIEBSZENTRUMNR;
    if (m_LAuftNr == 0)
    {
        auflager.s.KDAUFTRAGNR = m_AuftrNr;
        auflager.s.AUFTRAGNRKO = m_Datum;
        auflager.Server(AaauftSel_lauftnr);
        if (auflager.rc == SRV_OK)
            m_LAuftNr = auflager.s.AUFTRAGNRKO;
    }
    if (m_LAuftNr != 0)
    {
        sprintf(text, "%ld", m_LAuftNr);
        GetDlgItem(IDC_STATIC_LAUFTNUM)->SetWindowText(text);
        GetDlgItem(IDC_STATIC_LAUFTNR)->ShowWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_LAUFTNUM)->SetWindowText("");
        GetDlgItem(IDC_STATIC_LAUFTNUM)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_LAUFTNR)->ShowWindow(FALSE);
    }
    sprintf(text, "%ld", m_VzNr);
    GetDlgItem(IDC_STATIC_BRANCHNO2)->SetWindowText(text);
    sprintf(text, "%ld", kndinf.s.IDFNR);
    GetDlgItem(IDC_STATIC_IDF_NR)->SetWindowText(text);
    GetDlgItem(IDC_STATIC_WERTIG)->SetWindowText(kndinf.s.KZKDKLASSE);
    GetDlgItem(IDC_STATIC_INHABER)->SetWindowText(kndinf.s.NAMEINHABER);
    GetDlgItem(IDC_STATIC_APOTHEKE)->SetWindowText(kndinf.s.NAMEAPO);
    AllgEntfFirstSpaces(kndinf.s.POSTLEITZAHL);
    GetDlgItem(IDC_STATIC_PLZ)->SetWindowText(kndinf.s.POSTLEITZAHL);
    AllgEntfSpaces(kndinf.s.KUNDETEXT);
    GetDlgItem(IDC_STATIC_KNDTEXT)->SetWindowText(kndinf.s.KUNDETEXT);
    AllgEntfSpaces(auftrag.s.BEMERKUNGEN);
    GetDlgItem(IDC_STATIC_AUFTRBEM)->SetWindowText(auftrag.s.BEMERKUNGEN);
    GetDlgItem(IDC_STATIC_ORT)->SetWindowText(kndinf.s.ORT);
    GetDlgItem(IDC_STATIC_TEL)->SetWindowText(kndinf.s.TELNR);
    GetDlgItem(IDC_STATIC_TEL_KW)->SetWindowText(kndinf.s.TELKURZWAHL);
    if      (!strcmp(kndinf.s.DAFUESYSTEM,"01")) cstr = "PARA";
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"02")) cstr = "SERA";
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"00")) cstr = "PHON";
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"03")) cstr = "MSV3";
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"04")) cstr = "XML";
    else                                    cstr = kndinf.s.DAFUESYSTEM;
    GetDlgItem(IDC_STATIC_DAFUE_TYP)->SetWindowText(cstr);
    sprintf(text, "%ld", auftrag.s.ANZPOS);
    GetDlgItem(IDC_STATIC_ZLN)->SetWindowText(text);
    sprintf(text, "%.2f", auftrag.s.WERTAUFTRAG);
    GetDlgItem(IDC_STATIC_AW)->SetWindowText(text);
    sprintf(text, "%.2f", auftrag.s.WERTLIEFERUNG);
    GetDlgItem(IDC_STATIC_LIF_WERT)->SetWindowText(text);
    sprintf(text, "%.2f", auftrag.s.WERTZEILEN);
    GetDlgItem(IDC_STATIC_DZW)->SetWindowText(text);
    if (AeGetApp()->IsHR())
    {
        sprintf(text, "%.2f", auftrag.s.WERTZEILEN);
        GetDlgItem(IDC_STATIC_NETTOWERT)->SetWindowText(text);
    }
    GetDlgItem(IDC_STATIC_AA)->SetWindowText(auftrag.s.KDAUFTRAGART);
    GetDlgItem(IDC_STATIC_BA)->SetWindowText(auftrag.s.BUCHART);
    GetDlgItem(IDC_STATIC_KA)->SetWindowText(auftrag.s.KOART);
    sprintf(text, "%ld", auftrag.s.KDAUFTRAGNR);
    GetDlgItem(IDC_STATIC_AUFTR_NR)->SetWindowText(text);
    sprintf(text, "%ld", auftrag.s.KDAUFTRAGNRFILIALE);
    GetDlgItem(IDC_STATIC_AUFTR_NR_VSE)->SetWindowText(text);
    sprintf(text, "%ld", auftrag.s.VALUTAMONATE);
    GetDlgItem(IDC_STATIC_VALUTA)->SetWindowText(text);
    GetDlgItem(IDC_STATIC_RECHNR)->SetWindowText(m_cRechnr);
    AllgDatumLong2CharTTMMJJJJ(auftrag.s.DATUMVALUTA,text);
    GetDlgItem(IDC_STATIC_VALUTA_DATUM)->SetWindowText(text);
    if (m_bNoOpen)
    {
        GetDlgItem(IDC_STATIC_SPERRE)->EnableWindow(true);
        GetDlgItem(IDC_STATIC_SPERRE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_SPERRE)->SetWindowText(CResString::ex().getStrTblText(IDP_NO_OPEN_IV));
    }
    m_lTour = atol(auftrag.s.TOURID);
    CString tour;
    if (m_lTour)
    {
        CString cstr;
        char str[81];
        cstr = auftrag.s.TOURID;
        strncpy(str, cstr, 2);
        str[2]='\0';
        tour  = str;
        tour += ":";
        strncpy(str, cstr.Right(4), 2);
        str[2]='\0';
        tour += str;
        tour += " / ";
        strncpy(str, cstr.Right(2), 2);
        str[2]='\0';
        tour += str;
    }
    else
        tour = "";
    GetDlgItem(IDC_STATIC_TOUR)->SetWindowText(tour);

    if (AeGetApp()->IsBG())
    {
        if (auftrag.s.PAYMENTTYPE[0] == 'C' || (auftrag.s.PAYMENTTYPE[0] == ' ' && auftrag.s.PAYMENTDATE == 0))
        {
            GetDlgItem(IDC_STATIC_ZA)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_ZA)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZA)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZA)->SetWindowText(CResString::ex().getStrTblText(AETXT_CASH));
        }
        else if (auftrag.s.PAYMENTTYPE[0] == 'Z' || (auftrag.s.PAYMENTTYPE[0] == '0' && auftrag.s.PAYMENTDATE > 0))
        {
            GetDlgItem(IDC_STATIC_ZA)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZA)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZA)->SetWindowText(CResString::ex().getStrTblText(AETXT_ZAHLUNG));
            GetDlgItem(IDC_STATIC_ZZ)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_ZZ)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZZ)->ShowWindow(SW_SHOW);
            AllgDatumLong2CharTTMMJJJJ(auftrag.s.PAYMENTDATE, text);
            GetDlgItem(IDC_EDIT_ZZ)->SetWindowText(text);
        }

        GetDlgItem(IDC_STATIC_AUFWERTE)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_AUFWERTE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_NETTO)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NETTO)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_MWST)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_MWST)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_BRUTTO)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_BRUTTO)->ShowWindow(SW_SHOW);
        if (auftrag.s.WERTNETTO_FV > 0)
        {
            GetDlgItem(IDC_STATIC_FV)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_FV)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_FV_NETTO)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_FV_TAX)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_FV_BRUTTO)->ShowWindow(SW_SHOW);
            sprintf(text, "%.2f", auftrag.s.WERTNETTO_FV);
            GetDlgItem(IDC_EDIT_FV_NETTO)->SetWindowText(text);
            sprintf(text, "%.2f", auftrag.s.WERTTAX_FV);
            GetDlgItem(IDC_EDIT_FV_TAX)->SetWindowText(text);
            sprintf(text, "%.2f", auftrag.s.WERTNETTO_FV + auftrag.s.WERTTAX_FV);
            GetDlgItem(IDC_EDIT_FV_BRUTTO)->SetWindowText(text);
        }
        else
        {
            GetDlgItem(IDC_STATIC_FV)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_FV)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_FV_NETTO)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_FV_TAX)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_FV_BRUTTO)->ShowWindow(SW_HIDE);
        }
        if (auftrag.s.WERTNETTO_KK > 0)
        {
            GetDlgItem(IDC_STATIC_KK)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_KK)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_KK_NETTO)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_KK_TAX)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_KK_BRUTTO)->ShowWindow(SW_SHOW);
            sprintf(text, "%.2f", auftrag.s.WERTNETTO_KK);
            GetDlgItem(IDC_EDIT_KK_NETTO)->SetWindowText(text);
            sprintf(text, "%.2f", auftrag.s.WERTTAX_KK);
            GetDlgItem(IDC_EDIT_KK_TAX)->SetWindowText(text);
            sprintf(text, "%.2f", auftrag.s.WERTNETTO_KK + auftrag.s.WERTTAX_KK);
            GetDlgItem(IDC_EDIT_KK_BRUTTO)->SetWindowText(text);
        }
        else
        {
            GetDlgItem(IDC_STATIC_KK)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_KK)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_KK_NETTO)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_KK_TAX)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_KK_BRUTTO)->ShowWindow(SW_HIDE);
        }
        if (auftrag.s.WERTNETTO_EH > 0)
        {
            GetDlgItem(IDC_STATIC_EH)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_EH)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_EH_NETTO)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_EH_TAX)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_EH_BRUTTO)->ShowWindow(SW_SHOW);
            sprintf(text, "%.2f", auftrag.s.WERTNETTO_EH);
            GetDlgItem(IDC_EDIT_EH_NETTO)->SetWindowText(text);
            sprintf(text, "%.2f", auftrag.s.WERTTAX_EH);
            GetDlgItem(IDC_EDIT_EH_TAX)->SetWindowText(text);
            sprintf(text, "%.2f", auftrag.s.WERTNETTO_EH + auftrag.s.WERTTAX_EH);
            GetDlgItem(IDC_EDIT_EH_BRUTTO)->SetWindowText(text);
        }
        else
        {
            GetDlgItem(IDC_STATIC_EH)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_EH)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_EH_NETTO)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_EH_TAX)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_EH_BRUTTO)->ShowWindow(SW_HIDE);
        }
    }
    if (AeGetApp()->IsRS())
    {
        if (strncmp(auftrag.s.KDAUFTRAGART, "PF", 2))
        {
            ppString invoiceNumberPro;
            long lDateProforma = 0L;
            bool bSelProLink = false;
            if (m_Datum == 0)
            {
                CPROLINKACT proact;
                proact.SetKdauftragnr(auftrag.s.KDAUFTRAGNR);
                if (proact.SelProLink() == 0)
                {
                    proact.GetInvoicenumberpro(invoiceNumberPro);
                    lDateProforma = proact.GetDateproforma();
                    bSelProLink = true;
                }
            }
            else
            {
                CPROLINK pro;
                pro.SetDatum(m_Datum);
                pro.SetKdauftragnr(auftrag.s.KDAUFTRAGNR);
                if (pro.SelProLink() == 0)
                {
                    pro.GetInvoicenumberpro(invoiceNumberPro);
                    lDateProforma = pro.GetDateproforma();
                    bSelProLink = true;
                }
            }
            if (bSelProLink)
            {
                CString ctext;
                ctext.Format("%s / %s", invoiceNumberPro, DDMMYYYYStringFromDateLong(lDateProforma));
                GetDlgItem(IDC_STATIC_PROFORMANR)->SetWindowText(ctext);
                GetDlgItem(IDC_STATIC_PROFORMA)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_PROFORMA)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_PROFORMANR)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_PROFORMANR)->ShowWindow(SW_SHOW);
            }
        }
    }
    if (!m_cIVCnr.IsEmpty())
    {
        if (AeGetApp()->IsFR())
            GetDlgItem(IDC_STATIC_IVC)->SetWindowText(CResString::ex().getStrTblText(AETXT_ORGINVOICE));
        GetDlgItem(IDC_STATIC_IVCNR)->SetWindowText(m_cIVCnr);
        GetDlgItem(IDC_STATIC_IVC)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_IVC)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_IVCNR)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_IVCNR)->ShowWindow(SW_SHOW);
    }
}

void CDInfAnzAuft::ReadPos()
{
    m_lAuf.clear();
    CAUFPOSBUCH aufposbuch;
    BeginWaitCursor();
    for (int i = 1; ; i++)
    {
        aufposbuch.s.MENGE = 0; //nase wird demnächst im server korrekt versorgt
        aufposbuch.s.FILIALNR1 = 0; //vorformatieren auf 0
        if (m_Datum == 0)
            aufposbuch.Server(AasrvSelposInfAuf, PIPE_AE_SRV);
        else
        {
            aufposbuch.s.FETCH_REL = 1;
            aufposbuch.Server(AaauftSel_alt_pos);
        }
        if (aufposbuch.rc != SRV_OK)
        {
            if (m_Datum != 0)
            {
                aufposbuch.s.FETCH_REL = 0;
                aufposbuch.Server(AaauftSel_alt_pos);
            }
            break;
        }
        if (AeGetApp()->IsBG())
        {
            double dTax;
            char cStd;
            AeGetApp()->GetTaxRates(aufposbuch.s.TAXLEVEL, cStd, dTax);
            aufposbuch.s.PREISFAKTUR = aufposbuch.s.PREISFAKTUR * (100 + dTax) / 100;
        }
        m_lAuf.insert(m_lAuf.end(), aufposbuch.s);
    }
    EndWaitCursor();
}

void CDInfAnzAuft::AusgPos()
{
    CString cstr;
    CString cPQ;
    CString cpreis;
    CString cpromonr;
    CString cpromoname;
    CString cpromotyp;
    ppString spromoname;

    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;

    char str[81];
    int VSEStatus;      //VSE-Fehlerstatus
    long lRest;
    CPROMOANZ promoanz;
    CVERBUNDMOEGL vbm;
    CAUFALTLAGORT ibt;
    CARTPSYCHO psy;
    CARTIKELQUOTA quota;
    BeginWaitCursor();
    m_bVbKunde = IsVbKunde();
    m_ListCtl->DeleteAllItems();
    for (vector <AUFPOSBUCH>::iterator it = m_lAuf.begin(); it != m_lAuf.end(); it++)
    {
        if (m_CBNurDef.GetCheck() != FALSE)
        {
            if (it->ARTIKEL_NR != 0 && (it->MENGEABGEBUCHT+it->MENGENATRA) >= it->MENGEBESTELLT)
                continue;
        }
        int pos = m_ListCtl->GetItemCount();

        // wichtig für Sort
        lvi.lParam = (LPARAM)pos;

        VSEStatus = 0;
        if (it->SENDESTATUS == 2)       // Defekte von VSE
        {
            VSEStatus = 1;
        }
        else if (it->SENDESTATUS == 7)  // Defekte von VSE
        {
            VSEStatus = 2;
        }
        // wichtig für Sort
        if (m_ListCtl->InsertItem(&lvi) == -1)
            return;
        CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_AMGE, VSEStatus);

        m_ListCtl->SetItemText(lvi.iItem, COL_AMGE, _ltoa(it->MENGEBESTELLT, str, 10));
        m_ListCtl->SetItemText(lvi.iItem, COL_BMGE, _ltoa(it->MENGEGELIEFERT + it->MENGE, str, 10));
        m_ListCtl->SetItemText(lvi.iItem, COL_NRME, _ltoa(it->MENGENATRA, str, 10));
        m_ListCtl->SetItemText(lvi.iItem, COL_VERBME, _ltoa(it->MENGE, str, 10)); //Verbundmenge
        if (it->KZAUFGENOMMEN[0] == '1')
            m_ListCtl->SetItemText(lvi.iItem, COL_UMGESCHL, CResString::ex().getStrTblText(AETXT_KZ_JA));
        AllgEntfSpaces(it->EINHEIT);
        m_ListCtl->SetItemText(lvi.iItem, COL_EINHEIT, it->EINHEIT);
        if      (it->STATUS == ITEM_STAT_ZUGESAGT)      cstr = "ZU";
        else if (it->STATUS == ITEM_STAT_DISPO)         cstr = "DI";
        else if (it->STATUS == ITEM_STAT_NACHLIEFERN)   cstr = "NL";
        else if (it->KZINFOTEXT[0] == '1')              cstr = "IT";
        else                                            cstr = "";
        m_ListCtl->SetItemText(lvi.iItem, COL_FU, cstr);
        if (AeGetApp()->IsBG())
        {
            AllgEntfSpaces(it->ARTIKEL_LANGNAME);
            m_ListCtl->SetItemText(lvi.iItem, COL_ARTIKELNAME, it->ARTIKEL_LANGNAME);
        }
        else
        {
            AllgEntfSpaces(it->ARTIKEL_NAME);
            m_ListCtl->SetItemText(lvi.iItem, COL_ARTIKELNAME, it->ARTIKEL_NAME);
        }
        if (AllgBitleisteN((Bitleiste)it->ETARTKLASSE1, 6))  // opiat
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_ARTIKELNAME, LIEFBER_BTM);
        }
        else if (AllgBitleisteN((Bitleiste)it->ETARTSCHALTER1, 10))  // Kuehlkette
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_ARTIKELNAME, LIEFBER_KUEHL);
        }
        else if (AllgBitleisteN((Bitleiste)it->ETARTSCHALTER1, 8))   // Kuehl unter 8 Grad
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_ARTIKELNAME, LIEFBER_KUEHL_U8);
        }
        else if (AllgBitleisteN((Bitleiste)it->ETARTSCHALTER1, 9) && AeGetApp()->IsCool20())  // Kuehl unter 20 Grad
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_ARTIKELNAME, LIEFBER_COOL20);
        }
        AllgEntfSpaces(it->DARREICHFORM);
        m_ListCtl->SetItemText(lvi.iItem, COL_DAF, it->DARREICHFORM);
        m_ListCtl->SetItemText(lvi.iItem, COL_PA,  it->POSART);
        m_ListCtl->SetItemText(lvi.iItem, COL_PNR, _ltoa(it->POSNR, str, 10));
        if (   AllgBitleisteN((Bitleiste)it->ETPOSSCHALTER2, 10)    // gesplittet in anderen Auftrag
            || AllgBitleisteN((Bitleiste)it->ETPOSSCHALTER2, 7) )   // Verzoegert (z.B. Kuehlartikel)
        {
            m_ListCtl->SetItemText(lvi.iItem, COL_ETPOS, "1");
        }

        if (it->ARTIKEL_NR != 0)
        {
            psy.SetArtikel_nr(it->ARTIKEL_NR);
            if (!psy.SelArticle())
            {
                if (AllgBitleisteN((Bitleiste)psy.GetEtartklasse1(), 6))  // opiat
                {
                    m_ListCtl->SetItemText(lvi.iItem, COL_CONT, CResString::ex().getStrTblText(AETXT_BTM));
                }
                else if (   psy.GetKzpsychostoffe() == 'J'
                         || psy.GetKzpsychostoffe() == 'P'
                         || psy.GetKzpsychostoffe() == 'T' )  // psychotrop
                {
                    m_ListCtl->SetItemText(lvi.iItem, COL_CONT, CResString::ex().getStrTblText(AETXT_PTS));
                }
                else if (AllgBitleisteN((Bitleiste)it->ETARTSCHALTER2, 6))    //Containerartikel nase
                {
                    m_ListCtl->SetItemText(lvi.iItem, COL_CONT, CResString::ex().getStrTblText(AETXT_CONT));
                }
                else
                {
                    m_ListCtl->SetItemText(lvi.iItem, COL_CONT, _ltoa((long)(it->LAGERBEREICHNR), str, 10));
                }
            }
        }
        else
        {
            if (AllgBitleisteN((Bitleiste)it->ETARTSCHALTER2, 6)) //Containerartikel nase
                m_ListCtl->SetItemText(lvi.iItem, COL_CONT, CResString::ex().getStrTblText(AETXT_CONT));
            else
                m_ListCtl->SetItemText(lvi.iItem, COL_CONT, _ltoa((long)(it->LAGERBEREICHNR), str, 10));
        }

        if (it->ARTIKEL_NR == -1)
        {
            m_ListCtl->SetItemText(lvi.iItem, COL_PZN," ");
        }
        else
        {
            if (it->ARTICLE_CODE[0] == ' ')  // wenn articlecode noch nicht versorgt, dann artikelnr
            {
                m_ListCtl->SetItemText(lvi.iItem, COL_ARTICLECODE, _ltoa((it->ARTIKEL_NR), str, 10));
            }
            else
            {
                AllgEntfSpaces(it->ARTICLE_CODE);
                m_ListCtl->SetItemText(lvi.iItem, COL_ARTICLECODE, it->ARTICLE_CODE);
            }
            m_ListCtl->SetItemText(lvi.iItem, COL_PZN, _ltoa((it->ARTIKEL_NR), str, 10));
        }
        cstr = "";
        cPQ = "";
        if (it->ARTIKEL_NR > 0 && strlen(it->ARTIKEL_NAME) > 0)
        {
            GetArtKennz(it->ARTIKEL_NR, cstr, cPQ);
        }
        m_ListCtl->SetItemText(lvi.iItem, COL_KENNZEICHEN, cstr);
        m_ListCtl->SetItemText(lvi.iItem, COL_PRODQUOTA,   cPQ);
        if ((atoi(cPQ)) == 1)
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, lvi.iItem, COL_BMGE, PROD_QUOTA);
        }

        cpreis.Format("%0.2f", AeGetApp()->IsBG() ? it->PREISFAKTUR : it->PREISEKAPO);
        m_ListCtl->SetItemText(lvi.iItem, COL_PREIS, cpreis);
        cpreis.Format("%0.2f", it->PREISEKAPOFREE);
        m_ListCtl->SetItemText(lvi.iItem, COL_PREISFREE, cpreis);

        AllgEntfSpaces(it->BEMERKUNG);
        m_ListCtl->SetItemText(lvi.iItem, COL_BEMERK, it->BEMERKUNG);
        cstr.Format("%.2lf", it->PREISVKAPO);
        m_ListCtl->SetItemText(lvi.iItem, COL_AVP, cstr);
        if (it->DISCOUNTVALPCTMAN > 0.00)
        {
            cstr.Format("%.2lf", it->DISCOUNTVALPCTMAN);
            m_ListCtl->SetItemText(lvi.iItem, COL_PCTMAN, cstr);
        }
        else
        {
            cstr.Format("%.2lf", it->DISCOUNTVALUEPCT);
        }
        m_ListCtl->SetItemText(lvi.iItem, COL_PCT, cstr);
        cstr.Format("%d", it->PREIS_TYP);
        m_ListCtl->SetItemText(lvi.iItem, COL_PREISTYP, cstr);

        if (it->PROMOTION_NO > 0)
        {
            if (it->PROMOTYP == 1)
            {
                m_ListCtl->setItemColor(lvi.iItem, RGB(0, 0, 0), RGB(255, 85, 0));
            }
            else if (it->PROMOTYP == 2)
            {
                m_ListCtl->setItemColor(lvi.iItem, RGB(0, 0, 0), RGB(255, 00, 0));
            }
            else
            {
                m_ListCtl->setItemColor(lvi.iItem, RGB(0, 0, 0), RGB(255, 80, 80));
            }
            cpromotyp.Format("%d", it->PROMOTYP);
            cpromonr.Format("%d", it->PROMOTION_NO);
            promoanz.SetPromotion_no(it->PROMOTION_NO);
            if (!promoanz.SelPromo())
                cpromoname = promoanz.GetName(spromoname);
            else
                cpromoname.Empty();
        }
        else
        {
            cpromotyp.Empty();
            cpromonr.Empty();
            cpromoname.Empty();
        }
        m_ListCtl->SetItemText(lvi.iItem, COL_PROMONO, cpromonr);
        m_ListCtl->SetItemText(lvi.iItem, COL_PROMONAME, cpromoname);
        m_ListCtl->SetItemText(lvi.iItem, COL_PROMOTYP, cpromotyp);

        if (it->FILIALNR1)
        {
            if (it->IBTTYPEID > 0)   //NLevel-Verbund
            {
                if (it->IBTTYPEID == 1)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_NATIONAL));
                }
                else if (it->IBTTYPEID == 2)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_REGIONAL));
                }
                else if (it->IBTTYPEID == 3)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_LOKAL));
                }
                else // (it->IBTTYPEID == 4)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_SPEZIAL));
                }
            }
            else
            {
                if (it->IBTTYPE == 0)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_LOKAL));
                }
                else if (it->IBTTYPE == 1)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_PRIVATSORTIMENT));
                }
                else if (it->IBTTYPE == 2)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_VETO));
                }
                else if (it->IBTTYPE == 3)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_REGIONAL));
                }
                else if (it->IBTTYPE == 4)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_TAGVERBUND));
                }
                else // (it->IBTTYPE == 5)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_NATIONAL));
                }
            }

            AddDeliveryDateTimeToList(pos, it);

            m_ListCtl->SetItemText(lvi.iItem, COL_VERBUNDFIL, _ltoa((it->FILIALNR1), str, 10));
        }
        else
        {
            m_ListCtl->SetItemText(lvi.iItem, COL_VERBUNDFIL, "");

            if (   (   AllgBitleisteN((Bitleiste)it->ETPOSSCHALTER2, 10)    // gesplittet in anderen Auftrag
                    || AllgBitleisteN((Bitleiste)it->ETPOSSCHALTER2, 7) )   // Verzoegert (z.B. Kuehlartikel)
                && ((m_lTour != atol(it->TOURID)) || (it->DELIVERYDATE > m_lDatumAuftrag)) )  // Bei abweichender Tour oder abweichendem Datum Lieferzeit anzeigen
            {
                AddDeliveryDateTimeToList(pos, it);
            }
        }
        m_ListCtl->SetItemText(lvi.iItem, COL_VERBUND, "");
        if (   (it->ARTIKEL_NR != 0)
            && ((it->MENGEABGEBUCHT+it->MENGENATRA) < it->MENGEBESTELLT)
            && !AllgBitleisteN((Bitleiste)it->ETPOSSCHALTER2, 10)   //bei gesplitteten Positionen nicht Anzeigen Verbund möglich
            && m_bVbKunde)
        {
            lRest = 1;
            quota.SetBranchno(m_VzNr);
            quota.SetArticleno(it->ARTIKEL_NR);
            quota.SetCustomerno(m_KndNr);
            short sQuotaInheritance = CharToShort(AeGetApp()->QuotaInheritance());
            quota.SetQuotainheritance(sQuotaInheritance);
            if (!quota.CheckQuota())
            {
                lRest = quota.GetQuota();
            }
            quota.CloseCursor();
            if (lRest > 0)
            {
                if (AeGetApp()->IsNLevelIBTCst())
                {
                    ibt.s.ARTIKEL_NR = it->ARTIKEL_NR;
                    ibt.s.FILIALNR = m_VzNr;
                    ibt.Server(AasrvCheckIBTStockLevel);
                    if (ibt.rc == SRV_OK)
                    {
                        m_ListCtl->SetItemText(lvi.iItem, COL_VERBUND, CResString::ex().getStrTblText(AETXT_KZ_JA));
                        m_ListCtl->SetItemText(lvi.iItem, COL_FILI, _itoa(ibt.s.FILIALNR, str, 10));
                    }
                }
                else
                {
                    vbm.s.ARTIKEL_NR = it->ARTIKEL_NR;
                    vbm.s.FILIALNR = m_VzNr;
                    vbm.SelVbBestandNeu();
                    if ((vbm.rc == SRV_OK) && (vbm.s.BESTAND > 0))
                    {
                        m_ListCtl->SetItemText(lvi.iItem, COL_VERBUND, CResString::ex().getStrTblText(AETXT_KZ_JA));
                        m_ListCtl->SetItemText(lvi.iItem, COL_FILI, _itoa(vbm.s.FILIALNR, str, 10));
                    }
                    //vbm.CloseCursor();
                }
                if (AeGetApp()->IsPrintCode())
                {
                    ppString text;
                    CCODEBLOCAGEINFO code;
                    code.SetFilialnr(m_VzNr);
                    code.SetArtikel_nr(it->ARTIKEL_NR);
                    if (!code.SelText())
                    {
                        code.GetPrintcode(text);
                        CString cBemtext = m_ListCtl->GetItemText(lvi.iItem, COL_BEMERK);
                        CString cVolltext = text;
                        cVolltext += " / ";
                        cVolltext += cBemtext;
                        m_ListCtl->SetItemText(lvi.iItem, COL_BEMERK, cVolltext);
                    }
                }
            }
        }
        // wichtig für Sort
        ++lvi.iItem;
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(*m_ListCtl, 0);
    EndWaitCursor();
}

void CDInfAnzAuft::AddDeliveryDateTimeToList(int pos, vector<AUFPOSBUCH>::iterator& it)
{
    if ((atol(it->TOURID) != 0) || (it->DELIVERYDATE != 0))
    {
        CString str;
        str = DDMMYYYYStringFromDateLong(it->DELIVERYDATE);
        m_ListCtl->SetItemText(pos, COL_DELIVERYDATE, str);
        str = HHmmStringFromTimeLong(it->DELIVERYTIME);
        m_ListCtl->SetItemText(pos, COL_DELIVERYTIME, str);
    }
}

void CDInfAnzAuft::OnButtonKopfFuss()
{
    CDAufTxt dlgAufTxt;
    dlgAufTxt.m_ldatum = m_Datum;
    dlgAufTxt.m_bInfoOrder = TRUE;
    dlgAufTxt.DoModal();
}

LRESULT CDInfAnzAuft::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        //Ausgabe der Kundeninformationen
        CKndInf kndInf;
        kndInf.SetIdfNr(m_IdfNr);
        kndInf.SetKndNr(m_KndNr);
        kndInf.SetKndVz(m_VzNr);
        kndInf.DoModal();
        return 1L;
    }
    else if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        long lArtNr = 0L;
        int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString cstr;
            cstr = m_ListCtl->GetItemText(pos, COL_PZN);
            lArtNr = atol(cstr);
            if (lArtNr == 0L)
            {
                CDAeAnzFrText dlgAeAnzFrText;
                cstr = m_ListCtl->GetItemText(pos, COL_PNR);
                dlgAeAnzFrText.m_posnr = atol(cstr);
                dlgAeAnzFrText.m_datum = m_Datum;
                dlgAeAnzFrText.m_auftragnr = m_AuftrNr;
                dlgAeAnzFrText.DoModal();
                return 1L;
            }
        }
        CDArtInf dlgArtInf;
        if (lArtNr != 0L)
            dlgArtInf.SetArtNr(lArtNr);
        dlgArtInf.SetKndNr(m_KndNr);
        dlgArtInf.SetFilialNr(m_VzNr);
        dlgArtInf.DoModal();
        return 1L;
    }
    return 0L;
}

void CDInfAnzAuft::OnButtonKopfFuss2()
{
    CString cstr;
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cstr);
    CDAuftrEreign dlgAuftrEreign;
    dlgAuftrEreign.m_AuftragsNr = atol(cstr);
    dlgAuftrEreign.m_Datum = m_Datum;
    dlgAuftrEreign.DoModal();
}

void CDInfAnzAuft::OnButtonDruck()
{
    char underline[111];
    int pos, maxpos;
    CString IDF_Nr;
    CString Wertig;
    CString Inhaber;
    CString Apotheke;
    CString PLZ;
    CString Kndtext;
    CString Ort;
    CString Tel;
    CString Tel_KW;
    CString Dafue_Typ;
    CString Zln;
    CString AW;
    CString Lif_Wert;
    CString Dzw;
    CString AA;
    CString BA;
    CString KA;
    CString Auftr_Nr;
    CString Tour;
    CString liste;
    CString Str;
    CString Rech_Nr;
    CString Lauft_Nr;
    CString Datum;
    CString Bemerk;
    CString Vsenr;
    CString Verbund;
    CDruckAuftrag druckAuftrag;
    memset(underline, '-', 110);
    underline[110] = '\0';
    GetDlgItem(IDC_STATIC_DATUM)->GetWindowText(Datum);
    GetDlgItem(IDC_STATIC_IDF_NR)->GetWindowText(IDF_Nr);
    GetDlgItem(IDC_STATIC_WERTIG)->GetWindowText(Wertig);
    GetDlgItem(IDC_STATIC_INHABER)->GetWindowText(Inhaber);
    GetDlgItem(IDC_STATIC_APOTHEKE)->GetWindowText(Apotheke);
    GetDlgItem(IDC_STATIC_PLZ)->GetWindowText(PLZ);
    GetDlgItem(IDC_STATIC_KNDTEXT)->GetWindowText(Kndtext);
    GetDlgItem(IDC_STATIC_ORT)->GetWindowText(Ort);
    GetDlgItem(IDC_STATIC_TEL)->GetWindowText(Tel);
    GetDlgItem(IDC_STATIC_TEL_KW)->GetWindowText(Tel_KW);
    GetDlgItem(IDC_STATIC_DAFUE_TYP)->GetWindowText(Dafue_Typ);
    GetDlgItem(IDC_STATIC_ZLN)->GetWindowText(Zln);
    GetDlgItem(IDC_STATIC_AW)->GetWindowText(AW);
    GetDlgItem(IDC_STATIC_LIF_WERT)->GetWindowText(Lif_Wert);
    GetDlgItem(IDC_STATIC_DZW)->GetWindowText(Dzw);
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(AA);
    GetDlgItem(IDC_STATIC_BA)->GetWindowText(BA);
    GetDlgItem(IDC_STATIC_KA)->GetWindowText(KA);
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(Auftr_Nr);
    GetDlgItem(IDC_STATIC_RECHNR)->GetWindowText(Rech_Nr);
    GetDlgItem(IDC_STATIC_TOUR)->GetWindowText(Tour);
    GetDlgItem(IDC_STATIC_LAUFTNR)->GetWindowText(Lauft_Nr);
    GetDlgItem(IDC_STATIC_AUFTRBEM)->GetWindowText(Bemerk);
    GetDlgItem(IDC_STATIC_AUFTR_NR_VSE)->GetWindowText(Vsenr);

    liste.Format("%-15.15s %07.7s % 27.27s %-16.16s %-14.14s %-8.8s %-10.10s %-2.2s",
                    CResString::ex().getStrTblText(AETXT_KUNDEN_NR).GetString(), IDF_Nr.GetString(),
                    CResString::ex().getStrTblText(AETXT_TELEFON).GetString(), Tel.GetString(),
                    CResString::ex().getStrTblText(AETXT_ZEILEN).GetString(), Zln.GetString(),
                    CResString::ex().getStrTblText(AETXT_A_ART).GetString(), AA.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-26.26s % 8.8s %-16.16s %-14.14s %-8.8s %-10.10s %-2.2s",
                    CResString::ex().getStrTblText(AETXT_INHABER).GetString(), Inhaber.GetString(),
                    CResString::ex().getStrTblText(AETXT_KURZWAHL).GetString(), Tel_KW.GetString(),
                    CResString::ex().getStrTblText(AETXT_AUF_WERT).GetString(), AW.GetString(),
                    CResString::ex().getStrTblText(AETXT_KOM_ART).GetString(), KA.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-26.26s % 4.4s-%-3.3s %-16.16s %-14.14s %-8.8s %-10.10s %-2.2s",
                    CResString::ex().getStrTblText(AETXT_APOTHEKENNAME).GetString(), Apotheke.GetString(),
                    CResString::ex().getStrTblText(AETXT_ZEILEN_DAFUE).GetString(), CResString::ex().getStrTblText(AETXT_ART).GetString(), Dafue_Typ.GetString(),
                    CResString::ex().getStrTblText(AETXT_LIF_WERT).GetString(), Lif_Wert.GetString(),
                    CResString::ex().getStrTblText(AETXT_BUCH_ART).GetString(), BA.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-8.8s %-6.6s %-26.26s % 8.8s %-16.16s %-14.14s %-8.8s %-4s: %-10.10s",
                    CResString::ex().getStrTblText(AETXT_PLZ_ORT).GetString(), PLZ.GetString(), Ort.GetString(),
                    CResString::ex().getStrTblText(AETXT_AUF_NR).GetString(), Auftr_Nr.GetString(),
                    CResString::ex().getStrTblText(AETXT_D_ZEILEN_WERT).GetString(), Dzw.GetString(),
                    CResString::ex().getStrTblText(AETXT_TOUR).GetString(), Tour.GetString());
    druckAuftrag.AddKopfZeile(liste);

    if (m_LAuftNr != 0)
    {
        liste.Format("                                           %-8.8s %-16.16s %-14.14s %-8.8s %-11.11s %ld",
                    CResString::ex().getStrTblText(AETXT_AUF_NR_VSE).GetString(), Vsenr.GetString(),
                    CResString::ex().getStrTblText(AETXT_RECHNR).GetString(), Rech_Nr.GetString(),
                    Lauft_Nr.GetString(), m_LAuftNr);
    }
    else
    {
        liste.Format("                                           %-8.8s %-16.16s %-14.14s %-8.8s",
                    CResString::ex().getStrTblText(AETXT_AUF_NR_VSE).GetString(), Vsenr.GetString(),
                    CResString::ex().getStrTblText(AETXT_RECHNR).GetString(), Rech_Nr.GetString());
    }
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-52.52s",
                    CResString::ex().getStrTblText(AETXT_PHONIE_INFO).GetString(), Kndtext.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-52.52s",
                    CResString::ex().getStrTblText(IDS_BEMERK).GetString(), Bemerk.GetString());
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    liste.Format("% 4.4s % 4.4s % 4.4s % 4.4s %-9.9s % 4.4s %-24.24s % 4.4s % 2.2s % 4.4s %13.13s %-9.9s VB %-60.60s",
            CResString::ex().getStrTblText(AETXT_AMGE).GetString(),
            CResString::ex().getStrTblText(AETXT_BMGE).GetString(),
            CResString::ex().getStrTblText(AETXT_NRME).GetString(),
            CResString::ex().getStrTblText(AETXT_VERBME).GetString(),
            CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
            CResString::ex().getStrTblText(AETXT_FU).GetString(),
            CResString::ex().getStrTblText(AETXT_ARTIKELNAME).GetString(),
            CResString::ex().getStrTblText(AETXT_DAF).GetString(),
            CResString::ex().getStrTblText(AETXT_PA).GetString(),
            CResString::ex().getStrTblText(AETXT_PNR).GetString(),
            CResString::ex().getStrTblText(AETXT_ARTICLE_CODE).GetString(),
            CResString::ex().getStrTblText(AETXT_PREIS).GetString(),
            CResString::ex().getStrTblText(IDS_BEMERK).GetString());
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);
    liste = CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    liste += "                                        ";
    liste += CResString::ex().getStrTblText(AETXT_DATUM);
    liste += ": ";
    liste += Datum;
    druckAuftrag.AddFussZeile(liste);
    maxpos = m_ListCtl->GetItemCount();
    for (pos = 0; pos < maxpos; pos++)
    {
        Verbund = m_ListCtl->GetItemText(pos, COL_VERBUND);
        if (Verbund.IsEmpty()) Verbund = m_ListCtl->GetItemText(pos, COL_VERBUNDFIL);
        liste.Format("% 4.4s % 4.4s % 4.4s % 4.4s %-9.9s % 4.4s %-24.24s % 4.4s % 2.2s % 4.4s %13.13s % 9.9s %-2.2s %-60.60s",
            m_ListCtl->GetItemText(pos, COL_AMGE).GetString(),
            m_ListCtl->GetItemText(pos, COL_BMGE).GetString(),
            m_ListCtl->GetItemText(pos, COL_NRME).GetString(),
            m_ListCtl->GetItemText(pos, COL_VERBME).GetString(),
            m_ListCtl->GetItemText(pos, COL_EINHEIT).GetString(),
            m_ListCtl->GetItemText(pos, COL_FU).GetString(),
            m_ListCtl->GetItemText(pos, COL_ARTIKELNAME).GetString(),
            m_ListCtl->GetItemText(pos, COL_DAF).GetString(),
            m_ListCtl->GetItemText(pos, COL_PA).GetString(),
            m_ListCtl->GetItemText(pos, COL_PNR).GetString(),
            m_ListCtl->GetItemText(pos, COL_ARTICLECODE).GetString(),
            m_ListCtl->GetItemText(pos, COL_PREIS).GetString(),
            Verbund.GetString(),
            m_ListCtl->GetItemText(pos, COL_BEMERK).GetString());
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(2);
    druckAuftrag.DelAllData();
}

void CDInfAnzAuft::OnOK()
{
    int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString CStr;
        CStr  = m_ListCtl->GetItemText(pos, COL_PZN);
        long lArtNr = atol (CStr);
        if (lArtNr == 0)
        {
            CDAeAnzFrText dlgAeAnzFrText;
            CStr  = m_ListCtl->GetItemText(pos, COL_PNR);
            dlgAeAnzFrText.m_posnr = atol (CStr);
            dlgAeAnzFrText.m_datum = m_Datum;
            dlgAeAnzFrText.m_auftragnr = m_AuftrNr;
            dlgAeAnzFrText.DoModal();
        }
        else
        {
            CDArtInf dlgArtInf;
            dlgArtInf.SetArtNr(lArtNr);
            dlgArtInf.SetKndNr(m_KndNr);
            dlgArtInf.DoModal();
        }
    }
}

void CDInfAnzAuft::OnCheckNurDef()
{

    //Listbox neu fuellen je nach Schalter
    AusgPos();
}

void CDInfAnzAuft::GetArtKennz(long artikelnr, CString& ArtKZ, CString& ProdQuota)
{
    //nase
    //ist noch einmal in aasrv.cpp definiert !!!!!!
    CString cstr;
    ArtKZ = "";
    CARTAESEL artaesel;
    artaesel.s.ARTIKEL_NR = artikelnr;
    artaesel.s.FILIALNR = AeGetApp()->FilialNrActual();
    artaesel.s.ETARTKLASSE1 = 65535;   //alles - select wird nur fuer KK-Code gebraucht
    artaesel.s.CODEBLOCAGE[0] = AeGetApp()->IsPrintCode() ? '1' : '0';
    artaesel.Server(AatartAa_sel_artnr);

    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1,0)) cstr += "9";       // Sekundaerbezeichner
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1,1)) cstr += "E";       // Nachfolgeartikel
    if (artaesel.s.PRISOART[0] != '0')
    {
        if      (artaesel.s.PRISOART[0] == '1')  cstr += "SL";
        else if (artaesel.s.PRISOART[0] == '2')  cstr += "SZ";
        else if (artaesel.s.PRISOART[0] == '3')  cstr += "SB";
    }
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1,3))    cstr += "A";        // ausser Handel
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1,4))    cstr += "AV";       // Auslaufartikel
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1,13))   cstr += "G";        // nicht ueber Grosshandel
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1,12))   cstr += "H";        // vom Hersteller nicht geliefert
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1,11))   cstr += "L";        // vom Hersteller nicht lieferbar
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1,6))    cstr += "P";        // Netto
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER3,7))    cstr += "N";        // Natra
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER4,1))    cstr += "R";        // Reimport
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER4,14))   cstr += "T";        // Nahrungsmittel gesperrt
    if (!AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER2,15) && artaesel.s.BESTAND==0)
    {
        if (artaesel.s.WAFOTYP[0] > '0')
            cstr += "W";    // Artikel darf als NL erfasst werden
        cstr += "F";        // Artikel wird nicht gefuehrt
    }
    ArtKZ = cstr;
    ProdQuota.Format("%d", artaesel.s.PRODUSERQUOTA);
}

void CDInfAnzAuft::OnButtonDruckLief()
{
    CDWannauswahl dlgWannauswahl;
    dlgWannauswahl.m_lAuf = &m_lAuf;
    dlgWannauswahl.m_datum = m_Datum;
    GetDlgItem(IDC_STATIC_DATUM)->GetWindowText(dlgWannauswahl.m_Datum);
    GetDlgItem(IDC_STATIC_IDF_NR)->GetWindowText(dlgWannauswahl.m_IDF_Nr);
    GetDlgItem(IDC_STATIC_WERTIG)->GetWindowText(dlgWannauswahl.m_Wertig);
    GetDlgItem(IDC_STATIC_INHABER)->GetWindowText(dlgWannauswahl.m_Inhaber);
    GetDlgItem(IDC_STATIC_APOTHEKE)->GetWindowText(dlgWannauswahl.m_Apotheke);
    GetDlgItem(IDC_STATIC_PLZ)->GetWindowText(dlgWannauswahl.m_PLZ);
    GetDlgItem(IDC_STATIC_KNDTEXT)->GetWindowText(dlgWannauswahl.m_Kndtext);
    GetDlgItem(IDC_STATIC_ORT)->GetWindowText(dlgWannauswahl.m_Ort);
    GetDlgItem(IDC_STATIC_TEL)->GetWindowText(dlgWannauswahl.m_Tel);
    GetDlgItem(IDC_STATIC_TEL_KW)->GetWindowText(dlgWannauswahl.m_Tel_KW);
    GetDlgItem(IDC_STATIC_DAFUE_TYP)->GetWindowText(dlgWannauswahl.m_Dafue_Typ);
    GetDlgItem(IDC_STATIC_ZLN)->GetWindowText(dlgWannauswahl.m_Zln);
    GetDlgItem(IDC_STATIC_AW)->GetWindowText(dlgWannauswahl.m_AW);
    GetDlgItem(IDC_STATIC_LIF_WERT)->GetWindowText(dlgWannauswahl.m_Lif_Wert);
    GetDlgItem(IDC_STATIC_DZW)->GetWindowText(dlgWannauswahl.m_Dzw);
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(dlgWannauswahl.m_AA);
    GetDlgItem(IDC_STATIC_BA)->GetWindowText(dlgWannauswahl.m_BA);
    GetDlgItem(IDC_STATIC_KA)->GetWindowText(dlgWannauswahl.m_KA);
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(dlgWannauswahl.m_Auftr_Nr);
    GetDlgItem(IDC_STATIC_RECHNR)->GetWindowText(dlgWannauswahl.m_Rech_Nr);
    GetDlgItem(IDC_STATIC_TOUR)->GetWindowText(dlgWannauswahl.m_Tour);
    GetDlgItem(IDC_STATIC_LAUFTNUM)->GetWindowText(dlgWannauswahl.m_LA_Nr);
    GetDlgItem(IDC_STATIC_LAUFTNR)->GetWindowText(dlgWannauswahl.m_Lauft_Nr);
    GetDlgItem(IDC_STATIC_AUFTRBEM)->GetWindowText(dlgWannauswahl.m_Bemerk);
    GetDlgItem(IDC_STATIC_AUFTR_NR_VSE)->GetWindowText(dlgWannauswahl.m_Vsenr);
    dlgWannauswahl.DoModal();
}

void CDInfAnzAuft::OnButtonVbBuch()
{
    CDVbBuchen dlgVbBuchen;
    dlgVbBuchen.m_pl.clear();
    for (int pos = 0; pos < m_ListCtl->GetItemCount(); pos++)
    {
        if (m_ListCtl->GetItemText(pos, COL_VERBUND) == CResString::ex().getStrTblText(AETXT_KZ_JA))
        {
            InitVbArtikel(dlgVbBuchen.m_pl, pos);
        }
    }
    InitVbBuchenDlg(dlgVbBuchen);
    if (dlgVbBuchen.DoModal() == IDOK)
        CDialogMultiLang::OnOK();
}

void CDInfAnzAuft::InitVbArtikel(vector<CDVbBuchen::VbArtikel>& destlist, int pos, bool bUseAmgeAsBmge /*=false*/)
{
    struct CDVbBuchen::VbArtikel VB;
    VB.MengeBestellt = m_ListCtl->GetItemText(pos, COL_AMGE);
    VB.BestMenge = m_ListCtl->GetItemText(pos, bUseAmgeAsBmge ? COL_AMGE : COL_BMGE); // bUseAmgeAsBmge==true: erneuter Versuch der Menge
    VB.NatraMenge = m_ListCtl->GetItemText(pos, COL_NRME);
    VB.VerbMenge = m_ListCtl->GetItemText(pos, COL_VERBME);
    VB.ArtEinh = m_ListCtl->GetItemText(pos, COL_EINHEIT);
    VB.ArtName = m_ListCtl->GetItemText(pos, COL_ARTIKELNAME);
    VB.ArtNr = m_ListCtl->GetItemText(pos, COL_PZN);
    VB.VerbFiliale = m_ListCtl->GetItemText(pos, COL_FILI);
    VB.Darreichform = m_ListCtl->GetItemText(pos, COL_DAF);
    VB.Bemerkung = m_ListCtl->GetItemText(pos, COL_BEMERK);
    VB.Kennzeichen = m_ListCtl->GetItemText(pos, COL_KENNZEICHEN);
    VB.LagerBereich = m_ListCtl->GetItemText(pos, COL_CONT);
    VB.Preistyp = m_ListCtl->GetItemText(pos, COL_PREISTYP);
    VB.Prodquota = m_ListCtl->GetItemText(pos, COL_PRODQUOTA);
    VB.PreisFree = m_ListCtl->GetItemText(pos, COL_PREISFREE);
    VB.PctMan = m_ListCtl->GetItemText(pos, COL_PCTMAN);
    destlist.insert(destlist.end(), VB);
}

void CDInfAnzAuft::InitVbBuchenDlg(CDVbBuchen& dlgVbBuchen)
{
    dlgVbBuchen.m_lKndNr = m_KndNr;
    dlgVbBuchen.m_IdfNr = m_IdfNr;
    dlgVbBuchen.m_VzNr = m_VzNr;
    dlgVbBuchen.m_bVersorgt = true;
    dlgVbBuchen.m_TenderNo = m_TenderNo;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(dlgVbBuchen.m_cAufArt);

    CKNDSCHALTER kndschalter;
    kndschalter.s.IDFNR = m_IdfNr;
    kndschalter.s.KUNDENNR = m_KndNr;
    kndschalter.s.VERTRIEBSZENTRUMNR = m_VzNr;
    kndschalter.Server(AakundeSel_kndschalter);

    dlgVbBuchen.m_bKndMussKopfBem = kndschalter.s.SKDMUSSKOPF[0] == '1' ? true : false;
}

void CDInfAnzAuft::OnButtonDefbuch()
{
    CDVbBuchen dlgVbBuchen;
    dlgVbBuchen.m_pl.clear();
    for (int pos = 0;pos < m_ListCtl->GetItemCount();pos++)
    {
        if (   (atoi(m_ListCtl->GetItemText(pos, COL_BMGE)) < atoi(m_ListCtl->GetItemText(pos, 0)))
            && (atoi(m_ListCtl->GetItemText(pos, COL_ETPOS)) != 1) )
        {
            InitVbArtikel(dlgVbBuchen.m_pl, pos);
        }
    }
    InitVbBuchenDlg(dlgVbBuchen);
    dlgVbBuchen.m_ifunktion = 1;
    if (dlgVbBuchen.DoModal() == IDOK)
        CDialogMultiLang::OnOK();
}

void CDInfAnzAuft::OnButtonSeralog()
{
    CDSeralog dlgSeralog;
    dlgSeralog.m_CIdf.Format("%ld", m_IdfNr);
    GetDlgItem(IDC_STATIC_DATUM)->GetWindowText(dlgSeralog.m_CDatum);
    dlgSeralog.m_CDatum.Remove('.');
    CString cstr;
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cstr);
    CAUFEREIG aufereig;
    aufereig.s.KDAUFTRAGNR = atol(cstr);
    aufereig.s.DATUM=m_Datum;
    aufereig.s.FETCH_REL = 1;     //normaler Fetch
    aufereig.Server(AaauftAusg_auft_ereig);
    if (aufereig.rc == SRV_OK)
    {
        if (aufereig.s.ZEIT > 23999999)
            aufereig.s.ZEIT /= 100000;
        else if (aufereig.s.ZEIT > 239999)
            aufereig.s.ZEIT /= 10000;
        long lSerazeit = aufereig.s.ZEIT - 1;
        if (lSerazeit < 0)
            lSerazeit = 0;
        else if ((lSerazeit % 100) > 59)
        {
            lSerazeit = lSerazeit - 40;
        }
        dlgSeralog.m_CZeit.Format("%04d", lSerazeit);
    }
    aufereig.s.FETCH_REL = 0;     //close Cursor
    aufereig.s.DATUM = m_Datum;
    aufereig.Server(AaauftAusg_auft_ereig);
    dlgSeralog.m_ShowImmediately = 1;
    dlgSeralog.DoModal();
}

void CDInfAnzAuft::OnButtonAufNeu()
{
    int ipro = 0;
    CString cAArt;
    GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
    if (AeGetApp()->IsRS() && (cAArt == "PF"))
    {
        CString cANr;
        GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cANr);
        if (m_Datum == 0 && !m_bSelProforma)
        {
            CPROLINKACT proact;
            proact.SetKdauftragnr(atol(cANr));
            if (!proact.SelProLink())
                ipro = 1;
        }
        else
        {
            CPROLINK pro;
            pro.SetKdauftragnr(atol(cANr));
            pro.SetDatum(m_Datum);
            if (!pro.SelProLink())
                ipro = 1;
        }
    }
    if (ipro == 1)
    {
        if (MsgBoxYesNo(AETXT_PRO_DONE, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDNO)
        {
            return;
        }
    }

    CDVbBuchen dlgVbBuchen;
    dlgVbBuchen.m_pl.clear();
    for (int pos = 0; pos < m_ListCtl->GetItemCount(); pos++)
    {
        if (atol(m_ListCtl->GetItemText(pos, COL_BMGE)) == 0)
            continue;
        InitVbArtikel(dlgVbBuchen.m_pl, pos);
    }
    InitVbBuchenDlg(dlgVbBuchen);
    dlgVbBuchen.m_ifunktion = 2;
    if (cAArt == "PF")
    {
        CString cstr;
        GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cstr);
        AeGetApp()->ProAufnr = atol(cstr);
        AeGetApp()->ProDatum = m_Datum;
        GetDlgItem(IDC_STATIC_RECHNR)->GetWindowText(cstr);
        AeGetApp()->ProInvoiceno = cstr;
    }
    if (dlgVbBuchen.DoModal() == IDOK)
    {
        CDialogMultiLang::OnOK();
    }
    else
    {
        AeGetApp()->ProAufnr = 0;
        AeGetApp()->ProDatum = 0;
        AeGetApp()->ProInvoiceno = "";
    }
}

HBRUSH CDInfAnzAuft::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);
    if (pWnd->GetDlgCtrlID() == IDC_EDIT_FV_BRUTTO)
    {
        if (m_sFVRabkonto)
            pDC->SetTextColor(RGB(0,0,200));
        else
            pDC->SetTextColor(RGB(0,0,0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_FV_NETTO)
    {
        if (!m_sFVRabkonto)
            pDC->SetTextColor(RGB(0,0,200));
        else
            pDC->SetTextColor(RGB(0,0,0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_KK_BRUTTO)
    {
        if (m_sKKRabkonto)
            pDC->SetTextColor(RGB(0,0,200));
        else
            pDC->SetTextColor(RGB(0,0,0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_KK_NETTO)
    {
        if (!m_sKKRabkonto)
            pDC->SetTextColor(RGB(0,0,200));
        else
            pDC->SetTextColor(RGB(0,0,0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_SPERRE)
    {
        pDC->SetTextColor(RGB(255,0,0));
    }
    return hbr;
}

BOOL CDInfAnzAuft::DestroyWindow()
{
    AllgWriteColumnWidthUser(*m_ListCtl, "CDInfAnzAuft", KEY_PATH, COL_ANZ_LIST);

    return CDialogMultiLang::DestroyWindow();
}

// CompareListe ist eine stand alone Funktion
/////////////////////////////////////////////////////////////////////////////
// CompareListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
/////////////////////////////////////////////////////////////////////////////
int CALLBACK CompareInfAnzListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    if (s->GetAt(lParam1) == s->GetAt(lParam2))
        return 0;
    else if (s->GetAt(lParam1) > s->GetAt(lParam2))
        return 1;
    else
        return -1;
}

int CALLBACK CompareInfAnzListeDouble(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    double feld1 = atof(s->GetAt(lParam1));
    double feld2 = atof(s->GetAt(lParam2));
    if (feld1 == feld2)
        return 0;
    else if (feld1 > feld2)
        return 1;
    else
        return -1;
}

int CALLBACK CompareInfAnzListeLong(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    long feld1 = atol(s->GetAt(lParam1));
    long feld2 = atol(s->GetAt(lParam2));
    if (feld1 == feld2)
        return 0;
    else if (feld1 > feld2)
        return 1;
    else
        return -1;
}

void CDInfAnzAuft::OnLvnColumnclickListAuftrag(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int col = pNMListView->iSubItem;
    int max = m_ListCtl->GetItemCount();
    CStringArray s;
    s.SetSize(max);
    int index;
    for (index = 0; index < max; index++)
    {
        //StringArray an der ursprünglichen Position setzen
        LV_ITEM lvi; //Wegen Sort
        lvi.iItem = index;
        lvi.mask = LVIF_PARAM;      //muss gesetzt sein, um lParam abzuholen
        m_ListCtl->GetItem(&lvi);   //Ursprungadresse steht in lParam
        s[(int)lvi.lParam] = m_ListCtl->GetItemText(index, col);
    }
    if (col == COL_PREIS || col == COL_AVP || col == COL_PCT)
        m_ListCtl->SortItems(CompareInfAnzListeDouble, (LPARAM)&s);
    else if (col == COL_AMGE || col == COL_BMGE || col == COL_NRME || col == COL_VERBME || col == COL_PNR || col == COL_PZN)
        m_ListCtl->SortItems(CompareInfAnzListeLong, (LPARAM)&s);
    else
        m_ListCtl->SortItems(CompareInfAnzListe, (LPARAM)&s);

    for (index = 0; index < max; index++)
    {
        if (atoi(m_ListCtl->GetItemText(index, COL_PROMONO)) > 0)
        {
            if (atoi(m_ListCtl->GetItemText(index, COL_PROMOTYP)) == 1)
            {
                m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(255, 85, 0));
            }
            else if (atoi(m_ListCtl->GetItemText(index, COL_PROMOTYP)) == 2)
            {
                m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(255, 00, 0));
            }
            else
            {
                m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(255, 80, 80));
            }
        }
        else
        {
            m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(255, 255, 255));
        }
    }
    *pResult = 0L;
}

void CDInfAnzAuft::OnBnClickedButtonAufNeuAlle()
{
    CDVbBuchen dlgVbBuchen;
    dlgVbBuchen.m_pl.clear();
    for (int pos = 0; pos < m_ListCtl->GetItemCount(); pos++)
    {
        InitVbArtikel(dlgVbBuchen.m_pl, pos, true);
    }
    InitVbBuchenDlg(dlgVbBuchen);
    dlgVbBuchen.m_ifunktion = 2;
    if (dlgVbBuchen.DoModal() == IDOK)
    {
        CDialogMultiLang::OnOK();
    }
    else
    {
        AeGetApp()->ProAufnr = 0;
        AeGetApp()->ProDatum = 0;
        AeGetApp()->ProInvoiceno = "";
    }
}

bool CDInfAnzAuft::IsVbKunde()
{
    CKNDSCHALTER kndschalter;
    kndschalter.s.IDFNR = m_IdfNr;
    kndschalter.s.KUNDENNR = m_KndNr;
    kndschalter.s.VERTRIEBSZENTRUMNR = m_VzNr;
    kndschalter.Server(AakundeSel_kndschalter);
    if (kndschalter.s.SKDVERBUNDGANZ[0] == '1')
        return true;

    CZEITARTV zeitartv;
    sprintf(zeitartv.s.ZEITSCHLUESSEL, "%ld", m_KndNr);
    zeitartv.s.VERTRIEBSZENTRUMNR = m_VzNr;
    zeitartv.s.FETCH_REL = 1;  // normaler Fetch
    zeitartv.Server(AafilSel_verbund);
    bool bRes = (zeitartv.rc == SRV_OK) ? true : false;
    zeitartv.s.FETCH_REL = 0;  // Schliessen cursor
    zeitartv.Server(AafilSel_verbund);
    return bRes;
}

void CDInfAnzAuft::OnBnClickedButtonAufCallback()
{
    CString cText;
    CString cDatum;
    CString cTour;
    CString cAufnr;
    CString cVSE;
    CString cInvoice;
    GetDlgItem(IDC_STATIC_DATUM)->GetWindowText(cDatum);
    GetDlgItem(IDC_STATIC_TOUR)->GetWindowText(cTour);
    GetDlgItem(IDC_STATIC_AUFTR_NR)->GetWindowText(cAufnr);
    GetDlgItem(IDC_STATIC_AUFTR_NR_VSE)->GetWindowText(cVSE);
    GetDlgItem(IDC_STATIC_RECHNR)->GetWindowText(cInvoice);
    if (m_Datum > 0)
        cDatum = DDMMYYYYStringFromDateLong(m_Datum);    //Fakturdatum

    cText.Format("%s %s\r\n%s %s\r\n%s %s\r\n%s %s\r\n%s %s\r\n",
        CResString::ex().getStrTblText(AETXT_DATUM).GetString(),
        cDatum.GetString(),
        CResString::ex().getStrTblText(IDS_TOUR).GetString(),
        cTour.GetString(),
        CResString::ex().getStrTblText(AETXT_AUFTRZ).GetString(),
        cAufnr.GetString(),
        CResString::ex().getStrTblText(AETXT_AUF_NR_VSE).GetString(),
        cVSE.GetString(),
        CResString::ex().getStrTblText(AETXT_RECHNUNG_NR).GetString(),
        cInvoice.GetString());
    CDNewCallback dlgNewCallback;
    dlgNewCallback.m_lIdf = m_IdfNr;
    dlgNewCallback.m_sBranchno = m_VzNr;
    dlgNewCallback.m_CGrund = cText;
    dlgNewCallback.DoModal();
}

void CDInfAnzAuft::OnBnClickedButtonCremaStorno()
{
    CAUFTRAG auftrag;
    auftrag.s.KDAUFTRAGNR = m_AuftrNr;
    BeginWaitCursor();
    auftrag.Server(AasrvOpenorder, PIPE_AE_SRV);
    if (auftrag.rc < SRV_OK)
    {
        EndWaitCursor();
        return;
    }
    auftrag.Server(AasrvCancelorderDebtLimit, PIPE_AE_SRV);
    EndWaitCursor();
    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->ShowWindow(SW_HIDE);
}

void CDInfAnzAuft::OnBnClickedButtonCremaClose()
{
    CAUFTRAG auftrag;
    auftrag.s.KDAUFTRAGNR = m_AuftrNr;
    BeginWaitCursor();
    auftrag.Server(AasrvOpenorder, PIPE_AE_SRV);
    if (auftrag.rc < SRV_OK)
    {
        EndWaitCursor();
        return;
    }
    auftrag.Server(AasrvCloseorderDebtLimit, PIPE_AE_SRV);
    EndWaitCursor();
    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->ShowWindow(SW_HIDE);
}

void CDInfAnzAuft::OnButtonCall()
{
    if (m_bCall)
    {
        AeGetApp()->m_ProCenter.DisconnectCall();
        GetDlgItem(IDC_BUTTON_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_ANRUFEN));
        m_bCall = false;
    }
    else
    {
        CString cTelNr;
        GetDlgItem(IDC_STATIC_TEL)->GetWindowText(cTelNr);
        if (cTelNr.IsEmpty())
        {
            CDHPMakeCall dlgHPMakeCall;
            if (dlgHPMakeCall.DoModal() == IDOK)
            {
                cTelNr = dlgHPMakeCall.m_csTelNr;
            }
            else
                return;
        }
        cTelNr = '0' + cTelNr;
        cTelNr.TrimRight();
        AeGetApp()->m_ProCenter.MakeCall(cTelNr);
        GetDlgItem(IDC_BUTTON_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_AUFLEGEN));
        m_bCall = true;
    }
}

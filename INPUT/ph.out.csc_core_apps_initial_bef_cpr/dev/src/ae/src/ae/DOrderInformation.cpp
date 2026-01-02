// DOrderInformation.cpp : implementation file
//

#include "stdafx.h"
#include "DOrderInformation.h"
#include "AeDoc.h"
#include <kndsel.h>
#include "DKndInf.h"
#include <orders.h>
#include "DArtInf.h"
#include "zeitart.h"
#include "DAufTxt.h"
#include <artsel.h>
#include <verbundcheck.h>
#include "DVbBuchen.h"
#include "DSeralog.h"
#include "MainFrm.h"
#include "DAeAnzFrText.h"
#include <auftraginfo.h>
#include <artikel.h>
#include <deliveryadvicedocument.h>
#include <taufartk.h>


// CDOrderInformation dialog

CDOrderInformation::CDOrderInformation(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(IDD_AE_ORDER_INFORMATION, pParent)
{
    m_TenderNo = 0;
    m_Datum = 0;
    m_LAuftNr = 0;
    m_sFVRabkonto = 0;
    m_sKKRabkonto = 0;
    m_bSelProforma = FALSE;
    m_cRechnr = _T("");
    m_cIVCnr = _T("");
    ZuGrund = _T("");
    m_ActDatum = 0;
    Status = 0;
    m_sBatchAdvice = 0;
}

CDOrderInformation::~CDOrderInformation()
{
}

void CDOrderInformation::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_AART, m_CTabCtrlOrderInformation);
    DDX_Control(pDX, IDC_LIST1_INVOICE, m_ListInvoice);
    DDX_Control(pDX, IDC_STATIC_SAP_REFERENCE_NO, m_SapReferenceNo);
    DDX_Control(pDX, IDC_STATIC_SAP_REFERENCE_NO_VALUE, m_SapReferenceNoValue);
}


BEGIN_MESSAGE_MAP(CDOrderInformation, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_RECHNUNG, &CDOrderInformation::OnBnClickedButtonRechnung)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_LBN_DBLCLK(IDC_LIST1_INVOICE, &CDOrderInformation::OnLbnDblclkList1Invoice)
    ON_BN_CLICKED(IDC_BUTTON_BATCH, &CDOrderInformation::OnBnClickedButtonBatch)
END_MESSAGE_MAP()


// CDOrderInformation message handlers

BOOL CDOrderInformation::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    //Ausgabe Kopf
    AusgKopf();

    InitByParAufBearb();

    InitPage1();
    InitPage2();

    if (m_ListInvoice.GetCount() > 0)
    {
        int index;
        index = m_ListInvoice.SelectString(-1, m_cRechnr);
        //if (index != LB_ERR) m_ListInvoice.SetCurSel(index);
        //m_ListInvoice.SetCurSel(0);
        //GetDlgItem(IDC_LIST1_INVOICE)->SetFocus();
    }

    if (!GetAeUser().IsAnzRech())
    {
        GetDlgItem(IDC_BUTTON_RECHNUNG)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_RECHNUNG)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_BATCH)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_BATCH)->ShowWindow(SW_HIDE);
    }

    m_CTabCtrlOrderInformation.SetCurSel(0);
    m_CTabCtrlOrderInformation.GetCurrentPage()->OnSetActive();
    m_CTabCtrlOrderInformation.GetCurrentPage()->SetFocus();
    //m_PageDOrderInformation1.OnSetActive();
    //m_PageDOrderInformation1.SetFocus();
    //m_PageDOrderInformation1.MarkListPos(0);

    if (AeGetApp()->UseSapReferenceNo())
    {
        m_SapReferenceNo.ShowWindow(SW_SHOW);
        m_SapReferenceNoValue.ShowWindow(SW_SHOW);
    }

    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

void CDOrderInformation::AusgKopf()
{
    BeginWaitCursor();

    CAUFTRAG auftrag;
    if (!ReadOrder(auftrag))
    {
        EndWaitCursor();
        OnOK();
        return;
    }

    InitInvoice();

    CKNDINF kndinf;
    ReadCustomerInfo(kndinf, auftrag);

    SetDate(auftrag);

    SetOrderLabelCount(kndinf, auftrag);

    EndWaitCursor();

    SetStockOrderNo();

    SetCustomerInfoValues(kndinf.s);

    SetOrderValues(auftrag.s);

    SetInvoice();

    SetTour(auftrag.s.TOURID);
}

bool CDOrderInformation::ReadOrder(CAUFTRAG& auftrag)
{
    auftrag.s.STATUS = ORD_ZUM_LESEN_OEFFNEN;
    auftrag.s.KDAUFTRAGNR = m_AuftrNr;
    auftrag.s.ANZPOS = m_Datum;
    if (m_Datum == 0)
    {
        auftrag.Server(AasrvOpenInfoorder, PIPE_AE_SRV);
        ZuGrund = auftrag.s.ZUGRUND;
        Status = auftrag.s.STATUS;
    }
    else
    {
        auftrag.Server(AaauftSel_alt_auft);
    }
    m_TenderNo = auftrag.s.TENDERNO;

    return (auftrag.rc < SRV_OK) ? false : true;
}

void CDOrderInformation::InitInvoice()
{
    CINVOICENOS invoice;
    CINVOICENOSOLD invoiceold;
    if (m_Datum == 0)
    {
        invoice.SetCscorderno(m_AuftrNr);
    }
    else
    {
        invoiceold.SetCscorderno(m_AuftrNr);
        invoiceold.SetDatum(m_Datum);
    }

    for (;;)
    {
        if (m_Datum == 0)
        {
            if (invoice.SelList() != SRV_OK) break;
        }
        else
        {
            if (invoiceold.SelList() != SRV_OK) break;
        }
        GetDlgItem(IDC_STATIC_RECHNR2)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_RECHNR2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_LIST1_INVOICE)->EnableWindow(TRUE);
        GetDlgItem(IDC_LIST1_INVOICE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_RECHNUNG)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_RECHNUNG)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_BATCH)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_BATCH)->ShowWindow(SW_SHOW);
        ppString text2;
        if (m_Datum == 0)
        {
            invoice.GetRemarktext(text2);
        }
        else
        {
            invoiceold.GetRemarktext(text2);
        }
        CString hilfe = text2;
        hilfe.TrimLeft('0');
        m_ListInvoice.AddString(hilfe);
    }
}

void CDOrderInformation::ReadCustomerInfo(CKNDINF& kndinf, const CAUFTRAG& auftrag)
{
    kndinf.s.IDFNR = auftrag.s.IDFNR;
    kndinf.s.KUNDENNR = auftrag.s.KUNDENNR;
    kndinf.s.VERTRIEBSZENTRUMNR = auftrag.s.VERTRIEBSZENTRUMNR;
    kndinf.Server(AakundeSel_knd_info);

    m_lEtartklasse1 = kndinf.s.ETARTKLASSE1;
    m_KndNr = kndinf.s.KUNDENNR;
    m_IdfNr = kndinf.s.IDFNR;
    m_VzNr = kndinf.s.VERTRIEBSZENTRUMNR;
}

void CDOrderInformation::SetDate(const CAUFTRAG& auftrag)
{
    CAUFEREIG aufereig;
    aufereig.s.KDAUFTRAGNR = auftrag.s.KDAUFTRAGNR;
    aufereig.s.DATUM = m_Datum;
    aufereig.s.FETCH_REL = 1;                //normaler Fetch
    aufereig.Server(AaauftAusg_auft_ereig);

    char text[81];
    AllgDatumLong2CharTTMMJJJJ(aufereig.s.DATUM, text);
    Datum = text;
    //m_lDatumAuftrag = aufereig.s.DATUM;

    aufereig.s.DATUM = m_Datum;
    aufereig.s.FETCH_REL = 0;        //close Cursor
    aufereig.Server(AaauftAusg_auft_ereig);
}

void CDOrderInformation::SetOrderLabelCount(const CKNDINF& kndinf, const CAUFTRAG& auftrag)
{
    // --> lesen für Anzeige auftragartkd.orderlabelcount
    CAUFTRAGARTKD customerOrderType;
    customerOrderType.SetIdfnr(kndinf.s.IDFNR);
    customerOrderType.SetVertriebszentrumnr(kndinf.s.VERTRIEBSZENTRUMNR);
    customerOrderType.SetKdauftragart(auftrag.s.KDAUFTRAGART);

    char text[81];
    if (AeGetApp()->IsMSV3() &&
        ::ServerNr(PIPE_AE_SRV, AasrvGetCustOrderType, (void*)&customerOrderType.s, AUFTRAGARTKD_BES, AUFTRAGARTKD_ANZ, text) == 0)
    {
        OrderLabelCount.Format("%d", customerOrderType.GetOrderlabelcount());
    }
}

void CDOrderInformation::SetStockOrderNo()
{
    if (m_LAuftNr == 0)
    {
        CAUFLAGER auflager;
        auflager.s.KDAUFTRAGNR = m_AuftrNr;
        auflager.s.AUFTRAGNRKO = m_Datum;
        auflager.Server(AaauftSel_lauftnr);
        if (auflager.rc == SRV_OK)
        {
            m_LAuftNr = auflager.s.AUFTRAGNRKO;
        }
    }
    if (m_LAuftNr != 0)
    {
        char text[81];
        sprintf(text, "%ld", m_LAuftNr);
        GetDlgItem(IDC_STATIC_LAUFTNUM)->SetWindowText(text);
        GetDlgItem(IDC_STATIC_LAUFTNR)->ShowWindow(TRUE);
        Lauft_Nr = text;
    }
    else
    {
        GetDlgItem(IDC_STATIC_LAUFTNUM)->SetWindowText("");
        GetDlgItem(IDC_STATIC_LAUFTNUM)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_LAUFTNR)->ShowWindow(FALSE);
        Lauft_Nr.Empty();
    }
}

void CDOrderInformation::SetCustomerInfoValues(const KNDINF& kndinf)
{
    char text[81];
    sprintf(text, "%ld", kndinf.VERTRIEBSZENTRUMNR);
    GetDlgItem(IDC_STATIC_BRANCHNO2)->SetWindowText(text);
    sprintf(text, "%ld", kndinf.IDFNR);
    GetDlgItem(IDC_STATIC_IDF_NR)->SetWindowText(text);
    IDF_Nr = text;
    GetDlgItem(IDC_STATIC_WERTIG)->SetWindowText(kndinf.KZKDKLASSE);
    Wertig = kndinf.KZKDKLASSE;
    GetDlgItem(IDC_STATIC_INHABER)->SetWindowText(kndinf.NAMEINHABER);
    Inhaber = kndinf.NAMEINHABER;
    GetDlgItem(IDC_STATIC_APOTHEKE)->SetWindowText(kndinf.NAMEAPO);
    Apotheke = kndinf.NAMEAPO;
    PLZ = kndinf.POSTLEITZAHL;
    PLZ.TrimLeft();
    GetDlgItem(IDC_STATIC_PLZ)->SetWindowText(PLZ);
    Kndtext = kndinf.KUNDETEXT;
    Kndtext.TrimRight();
    GetDlgItem(IDC_STATIC_ORT)->SetWindowText(kndinf.ORT);
    Ort = kndinf.ORT;
    GetDlgItem(IDC_STATIC_TEL)->SetWindowText(kndinf.TELNR);
    Tel = kndinf.TELNR;
    GetDlgItem(IDC_STATIC_TEL_KW)->SetWindowText(kndinf.TELKURZWAHL);
    Tel_KW = kndinf.TELKURZWAHL;

    CString cstr;
    if (!strcmp(kndinf.DAFUESYSTEM, "01")) cstr = "PARA";
    else if (!strcmp(kndinf.DAFUESYSTEM, "02")) cstr = "SERA";
    else if (!strcmp(kndinf.DAFUESYSTEM, "00")) cstr = "PHON";
    else if (!strcmp(kndinf.DAFUESYSTEM, "03")) cstr = "MSV3";
    else if (!strcmp(kndinf.DAFUESYSTEM, "04")) cstr = "XML";
    else                                   cstr = kndinf.DAFUESYSTEM;
    GetDlgItem(IDC_STATIC_DAFUE_TYP)->SetWindowText(cstr);
    Dafue_Typ = cstr;
}

void CDOrderInformation::SetOrderValues(const AUFTRAG& auftrag)
{
    Bemerk = auftrag.BEMERKUNGEN;
    Bemerk.TrimRight();

    char text[81];
    sprintf(text, "%ld", auftrag.ANZPOS);
    Zln = text;
    sprintf(text, "%.2f", auftrag.WERTAUFTRAG);
    AW = text;
    sprintf(text, "%.2f", auftrag.WERTLIEFERUNG);
    Lif_Wert = text;
    sprintf(text, "%.2f", auftrag.WERTZEILEN);
    Dzw = text;
    sprintf(text, "%.2f", auftrag.WERTNETTO);
    Net_Wert = text;
    GetDlgItem(IDC_STATIC_AA)->SetWindowText(auftrag.KDAUFTRAGART);
    AA = auftrag.KDAUFTRAGART;
    GetDlgItem(IDC_STATIC_BA)->SetWindowText(auftrag.BUCHART);
    BA = auftrag.BUCHART;
    GetDlgItem(IDC_STATIC_KA)->SetWindowText(auftrag.KOART);
    KA = auftrag.KOART;
    sprintf(text, "%ld", auftrag.KDAUFTRAGNR);
    GetDlgItem(IDC_STATIC_AUFTR_NR)->SetWindowText(text);
    Auftr_Nr = text;
    sprintf(text, "%ld", auftrag.KDAUFTRAGNRFILIALE);
    GetDlgItem(IDC_STATIC_AUFTR_NR_VSE)->SetWindowText(text);
    Vsenr = text;
    if (auftrag.VALUTAMONATE > 0)
    {
        sprintf(text, "%ld", auftrag.VALUTAMONATE);
        ValutaMon = text;
        AllgDatumLong2CharTTMMJJJJ(auftrag.DATUMVALUTA, text);
        ValutaDatum = text;
    }
    m_SapReferenceNoValue.SetWindowText(auftrag.SAP_REFERENCENO);

    SetOrderValuesBG(auftrag);
    SetOrderValuesRS(auftrag);
}

void CDOrderInformation::SetOrderValuesBG(const AUFTRAG& auftrag)
{
    if (!AeGetApp()->IsBG())
    {
        return;
    }

    char text[81];
    Paymenttype = auftrag.PAYMENTTYPE;
    AllgDatumLong2CharTTMMJJJJ(auftrag.PAYMENTDATE, text);
    Paymentdate = text;
    sprintf(text, "%.2f", auftrag.WERTNETTO_FV);
    WertNettoFV = text;
    sprintf(text, "%.2f", auftrag.WERTTAX_FV);
    WertTaxFV = text;
    sprintf(text, "%.2f", auftrag.WERTNETTO_FV + auftrag.WERTTAX_FV);
    WertBruttoFV = text;
    sprintf(text, "%.2f", auftrag.WERTNETTO_KK);
    WertNettoKK = text;
    sprintf(text, "%.2f", auftrag.WERTTAX_KK);
    WertTaxKK = text;
    sprintf(text, "%.2f", auftrag.WERTNETTO_KK + auftrag.WERTTAX_KK);
    WertBruttoKK = text;
    sprintf(text, "%.2f", auftrag.WERTNETTO_EH);
    WertNettoEH = text;
    sprintf(text, "%.2f", auftrag.WERTTAX_EH);
    WertTaxEH = text;
    sprintf(text, "%.2f", auftrag.WERTNETTO_EH + auftrag.WERTTAX_EH);
    WertBruttoEH = text;
}

void CDOrderInformation::SetOrderValuesRS(const AUFTRAG& auftrag)
{
    if (!AeGetApp()->IsRS())
    {
        return;
    }

    if (strncmp(auftrag.KDAUFTRAGART, "PF", 2))
    {
        CString ctext;
        if (m_Datum != 0)
        {
            ppString text1;
            CPROLINK prolink;
            prolink.SetDatum(m_Datum);
            prolink.SetKdauftragnr(auftrag.KDAUFTRAGNR);
            if (!prolink.SelProLink())
            {
                ctext.Format("%s / %s",
                    prolink.GetInvoicenumberpro(text1),
                    DDMMYYYYStringFromDateLong(prolink.GetDateproforma()));
            }
        }
        else
        {
            ppString text1;
            CPROLINKACT prolinkact;
            prolinkact.SetKdauftragnr(auftrag.KDAUFTRAGNR);
            if (!prolinkact.SelProLink())
            {
                ctext.Format("%s / %s",
                    prolinkact.GetInvoicenumberpro(text1),
                    DDMMYYYYStringFromDateLong(prolinkact.GetDateproforma()));
            }
        }
        PFDatum = ctext;
    }
}

void CDOrderInformation::SetInvoice()
{
    GetDlgItem(IDC_STATIC_RECHNR)->SetWindowText(m_cRechnr);
    Rech_Nr = m_cRechnr;
    Rech_Nr_Save = Rech_Nr;

    if (m_bNoOpen)
    {
        GetDlgItem(IDC_STATIC_SPERRE)->EnableWindow(true);
        GetDlgItem(IDC_STATIC_SPERRE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_SPERRE)->SetWindowText(CResString::ex().getStrTblText(IDP_NO_OPEN_IV));
    }
}

void CDOrderInformation::SetTour(CString tourId)
{
    m_lTour = atol(tourId);
    if (m_lTour != 0)
    {
        char str[3];
        strncpy(str, tourId, 2);
        str[2] = '\0';
        Tour = str;
        Tour += ":";
        strncpy(str, tourId.Right(4), 2);
        str[2] = '\0';
        Tour += str;
        Tour += " / ";
        strncpy(str, tourId.Right(2), 2);
        str[2] = '\0';
        Tour += str;
    }
    else
    {
        Tour = "";
    }
}

void CDOrderInformation::InitByParAufBearb()
{
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
}

void CDOrderInformation::InitPage1()
{
    m_PageDOrderInformation1.IDF_Nr = IDF_Nr;
    m_PageDOrderInformation1.Wertig = Wertig;
    m_PageDOrderInformation1.Inhaber = Inhaber;
    m_PageDOrderInformation1.Apotheke = Apotheke;
    m_PageDOrderInformation1.PLZ = PLZ;
    m_PageDOrderInformation1.Kndtext = Kndtext;
    m_PageDOrderInformation1.Ort = Ort;
    m_PageDOrderInformation1.Tel = Tel;
    m_PageDOrderInformation1.Tel_KW = Tel_KW;
    m_PageDOrderInformation1.Dafue_Typ = Dafue_Typ;
    m_PageDOrderInformation1.Zln = Zln;
    m_PageDOrderInformation1.AW = AW;
    m_PageDOrderInformation1.Lif_Wert = Lif_Wert;
    m_PageDOrderInformation1.Dzw = Dzw;
    m_PageDOrderInformation1.Net_Wert = Net_Wert;
    m_PageDOrderInformation1.AA = AA;
    m_PageDOrderInformation1.BA = BA;
    m_PageDOrderInformation1.KA = KA;
    m_PageDOrderInformation1.Auftr_Nr = Auftr_Nr;
    m_PageDOrderInformation1.Tour = Tour;
    m_PageDOrderInformation1.m_lTour = m_lTour;
    m_PageDOrderInformation1.Rech_Nr = Rech_Nr;
    m_PageDOrderInformation1.Lauft_Nr = Lauft_Nr;
    m_PageDOrderInformation1.Datum = Datum;
    m_PageDOrderInformation1.Bemerk = Bemerk;
    m_PageDOrderInformation1.Vsenr = Vsenr;
    m_PageDOrderInformation1.m_AuftrNr = m_AuftrNr;
    m_PageDOrderInformation1.m_Datum = m_Datum;
    m_PageDOrderInformation1.m_IdfNr = m_IdfNr;
    m_PageDOrderInformation1.m_KndNr = m_KndNr;
    m_PageDOrderInformation1.m_VzNr = m_VzNr;
    m_PageDOrderInformation1.m_lEtartklasse1 = m_lEtartklasse1;
    m_PageDOrderInformation1.m_cIVCnr = m_cIVCnr;
    m_PageDOrderInformation1.ValutaMon = ValutaMon;
    m_PageDOrderInformation1.ValutaDatum = ValutaDatum;
    m_PageDOrderInformation1.Paymenttype = Paymenttype;
    m_PageDOrderInformation1.Paymentdate = Paymentdate;
    m_PageDOrderInformation1.WertNettoFV = WertNettoFV;
    m_PageDOrderInformation1.WertTaxFV = WertTaxFV;
    m_PageDOrderInformation1.WertBruttoFV = WertBruttoFV;
    m_PageDOrderInformation1.WertNettoKK = WertNettoKK;
    m_PageDOrderInformation1.WertTaxKK = WertTaxKK;
    m_PageDOrderInformation1.WertBruttoKK = WertBruttoKK;
    m_PageDOrderInformation1.WertNettoEH = WertNettoEH;
    m_PageDOrderInformation1.WertTaxEH = WertTaxEH;
    m_PageDOrderInformation1.WertBruttoEH = WertBruttoEH;
    m_PageDOrderInformation1.PFDatum = PFDatum;
    m_PageDOrderInformation1.OrderLabel = OrderLabel;
    m_PageDOrderInformation1.OrderLabelCount = OrderLabelCount;
    m_PageDOrderInformation1.m_lDatumAuftrag = m_lDatumAuftrag;
    m_PageDOrderInformation1.m_ActDatum = m_ActDatum;
    m_PageDOrderInformation1.ZuGrund = ZuGrund;
    m_PageDOrderInformation1.Status = Status;

    m_CTabCtrlOrderInformation.AddPage(&m_PageDOrderInformation1);
}

void CDOrderInformation::InitPage2()
{
    m_PageDOrderInformation2.m_KndNr = m_KndNr;
    m_PageDOrderInformation2.m_VzNr = m_VzNr;
    m_PageDOrderInformation2.m_lDatumAuftrag = m_lDatumAuftrag;
    m_PageDOrderInformation2.Rech_Nr = Rech_Nr;
    m_PageDOrderInformation2.m_ActDatum = m_ActDatum;

    InitBatchAndAddPage2();
}

void CDOrderInformation::InitBatchAndAddPage2()
{
    GetDlgItem(IDC_STATIC_BATCH_STATUS)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_BATCH_STATUS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_BATCH_ST)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_BATCH_ST)->ShowWindow(SW_HIDE);

    if (Rech_Nr.IsEmpty() || (atol(Rech_Nr) <= 0)) //macht keinen Sinn, wenn keine Rechnungsnummer da ist
    {
        return;
    }

    m_CTabCtrlOrderInformation.AddPage(&m_PageDOrderInformation2);

    // Are these controls ever used ???
    // IDC_STATIC_BATCH_STATUS, IDC_STATIC_BATCH_ST

    GetDlgItem(IDC_BUTTON_BATCH)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_BATCH)->ShowWindow(SW_HIDE);
    if (m_PageDOrderInformation2.m_bNoData)
    {
        GetDlgItem(IDC_STATIC_BATCH_STATUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_BATCH_STATUS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_BATCH_ST)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_BATCH_ST)->ShowWindow(SW_HIDE);
    }
    else
    {
        m_sBatchAdvice = m_PageDOrderInformation2.m_sBatchAdvice;
        if (m_sBatchAdvice == 0)
        {
            GetDlgItem(IDC_STATIC_BATCH_ST)->SetWindowText(CResString::ex().getStrTblText(AETXT_BATCH_STATUS_0));
        }
        else if (m_sBatchAdvice == 1)
        {
            GetDlgItem(IDC_STATIC_BATCH_ST)->SetWindowText(CResString::ex().getStrTblText(AETXT_BATCH_STATUS_1));
        }
        else if (m_sBatchAdvice == 2)
        {
            GetDlgItem(IDC_STATIC_BATCH_ST)->SetWindowText(CResString::ex().getStrTblText(AETXT_BATCH_STATUS_2));
        }
        else if (m_sBatchAdvice == 3)
        {
            GetDlgItem(IDC_STATIC_BATCH_ST)->SetWindowText(CResString::ex().getStrTblText(AETXT_BATCH_STATUS_3));
        }
        else if (m_sBatchAdvice == 4)
        {
            GetDlgItem(IDC_STATIC_BATCH_ST)->SetWindowText(CResString::ex().getStrTblText(AETXT_BATCH_STATUS_4));
            GetDlgItem(IDC_BUTTON_BATCH)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_BATCH)->ShowWindow(SW_SHOW);
        }
        else
        {
            GetDlgItem(IDC_STATIC_BATCH_ST)->SetWindowText(CResString::ex().getStrTblText(AETXT_BATCH_STATUS_X));
        }
    }


    if (!AeGetApp()->m_pAeUser->IsAnzLief() || m_PageDOrderInformation2.m_bNoData)
    {
        m_CTabCtrlOrderInformation.DeleteItem(1);
    }
}

void CDOrderInformation::OnBnClickedButtonRechnung()
{
    int pos = m_ListInvoice.GetCurSel();
    if (pos == LB_ERR)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
        return;
    }
    int rc;
    char error_msg[81];
    CString str;
    m_ListInvoice.GetText(pos, str);

    CDELIVERYADVICEDOCUMENT doc;

    doc.SetBranchno(m_VzNr);
    doc.SetCustomerno(m_KndNr);
    doc.SetDeliveryadviceno(str);
    doc.SetDeliveryadvicedate(m_lDatumAuftrag);

    rc = ::ServerNr(PIPE_AE_SRV, AasrvGetDocumentLink, (void *)&doc.s, DELIVERYADVICEDOCUMENT_BES, DELIVERYADVICEDOCUMENT_ANZ, error_msg);
    if (rc < SRV_OK)
    {
        FehlerBehandlung(rc, error_msg);
        return;
    }
    if (rc == SRV_SQLNOTFOUND)
    {
        MsgBoxOK(IDS_NO_ENTRY);
        return;
    }
    ppString link;
    doc.GetDocumentlink(link);
    ShellExecute(0, NULL, link, NULL, NULL, SW_SHOWDEFAULT);
    AeGetApp()->m_AeLogging.WriteLine(1, "CDOrderInformation.cpp", "OnBnClickedButtonRechnung", "Internet started");
}

LRESULT CDOrderInformation::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    CString xx;
    xx.Format("%d\n", ((LPMSG)lpMsg)->wParam);
    TRACE(xx);
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
        CDArtInf dlgArtInf;
        long ArtNr = 0;
        if (m_CTabCtrlOrderInformation.GetCurrentPage()->GetID() == m_PageDOrderInformation1.GetID())
        {
            int pos = m_PageDOrderInformation1.m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
            if (pos >= 0)
            {
                CString CStr;
                CStr = m_PageDOrderInformation1.m_ListCtl->GetItemText(pos, COL_PZN);
                ArtNr = atol(CStr);
                if (ArtNr == 0)
                {
                    CDAeAnzFrText dlgAeAnzFrText;
                    CStr = m_PageDOrderInformation1.m_ListCtl->GetItemText(pos, COL_PNR);
                    dlgAeAnzFrText.m_posnr = atol(CStr);
                    dlgAeAnzFrText.m_datum = m_Datum;
                    dlgAeAnzFrText.m_auftragnr = m_AuftrNr;
                    dlgAeAnzFrText.DoModal();
                    return 1L;
                }
            }
        }
        else
        {
            int pos = m_PageDOrderInformation2.m_CListLief.GetNextItem(-1, LVNI_SELECTED);
            if (pos >= 0)
            {
                CString CStr;
                CStr = m_PageDOrderInformation2.m_CListLief.GetItemText(pos, COL_LS_PZN);
                ArtNr = atol(CStr);
                if (ArtNr == 0)
                {
                    MsgBoxOK(IDS_BEMERK);
                    return 1L;
                }
            }

        }
        if (ArtNr != 0) dlgArtInf.SetArtNr(ArtNr);
        dlgArtInf.SetKndNr(m_KndNr);
        dlgArtInf.SetFilialNr(m_VzNr);
        dlgArtInf.DoModal();
        return 1L;
    }
    else if (((LPMSG)lpMsg)->wParam == VK_NEXT)
    {
        if (m_CTabCtrlOrderInformation.GetCurrentPage()->GetID() == m_PageDOrderInformation1.GetID())
        {
        }
        else
        {
            m_PageDOrderInformation2.m_CTabCtrlOrderInformation2.GetCurrentPage()->OnSetActive();
            m_PageDOrderInformation2.m_CTabCtrlOrderInformation2.GetCurrentPage()->SetFocus();
            return 1L;  //Message wird nicht weitergeleitet

        }
    }
    else if (((LPMSG)lpMsg)->wParam == VK_PRIOR)
    {
        if (m_CTabCtrlOrderInformation.GetCurrentPage()->GetID() == m_PageDOrderInformation1.GetID())
        {
        }
        else
        {
            CListCtrlHelper::SetFocusSelectedFocusedVisible(m_PageDOrderInformation2.m_CListLief, 0);
            return 1L;
        }
    }

    return 0L;
}

void CDOrderInformation::OnLbnDblclkList1Invoice()
{
    CString str;
    int pos = m_ListInvoice.GetCurSel();
    if (pos >= 0)
    {
        m_ListInvoice.GetText(pos, str);
        if (str != Rech_Nr_Save)
        {
            Rech_Nr_Save = str;
            m_PageDOrderInformation2.Rech_Nr = str;
            m_PageDOrderInformation2.AlterInvoice();
        }
    }
}


void CDOrderInformation::OnBnClickedButtonBatch()
{
    int pos = m_ListInvoice.GetCurSel();
    if (pos == LB_ERR)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
        return;
    }
    int rc;
    char error_msg[81];
    CString str;
    m_ListInvoice.GetText(pos, str);

    CDELIVERYADVICEDOCUMENT doc;

    doc.SetBranchno(m_VzNr);
    doc.SetCustomerno(m_KndNr);
    doc.SetDeliveryadviceno(str);
    doc.SetDeliveryadvicedate(m_lDatumAuftrag);

    rc = ::ServerNr(PIPE_AE_SRV, AasrvGetBatchAdviceLink, (void *)&doc.s, DELIVERYADVICEDOCUMENT_BES, DELIVERYADVICEDOCUMENT_ANZ, error_msg);
    if (rc < SRV_OK)
    {
        FehlerBehandlung(rc, error_msg);
        return;
    }
    if (rc == SRV_SQLNOTFOUND)
    {
        MsgBoxOK(IDS_NO_ENTRY);
        return;
    }
    ppString link;
    doc.GetDocumentlink(link);
    ShellExecute(0, NULL, link, NULL, NULL, SW_SHOWDEFAULT);
}

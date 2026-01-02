// DOrderInformation2.cpp : implementation file
//

#include "stdafx.h"
#include "DOrderInformation2.h"
#include <deliveryadvicehead.h>
#include <deliveryadviceline.h>
#include <deliveryadvicevattotals.h>
#include <kndsel.h>
#include "DKndInf.h"
#include "DArtInf.h"

//Definition der Tabellenbreite und der Ueberschriften Steuern
static COLUMNS_TYPES SpaltenVat[] =
{
    0,  "",  0, LVCFMT_LEFT,
    1,  "", 45, LVCFMT_RIGHT,
    2,  "", 70, LVCFMT_RIGHT,
    3,  "", 70, LVCFMT_RIGHT,
    -1, "",  0, 0
};

#define NUM_SPALT_VAT 4


//Definition der Tabellenbreite und der Ueberschriften Zeilen
static COLUMNS_TYPES SpaltenLief[] =
{
    COL_LS_AMGE,          "",  40, LVCFMT_LEFT,
    COL_LS_BMGE,          "",  35, LVCFMT_RIGHT,
    COL_LS_NRME,          "",  35, LVCFMT_RIGHT,
    COL_LS_RMME,          "",  45, LVCFMT_RIGHT,
    COL_LS_NLME,          "",  35, LVCFMT_RIGHT,
    COL_LS_EINHEIT,       "",  55, LVCFMT_LEFT,
    COL_LS_ARTIKELNAME,   "", 240, LVCFMT_LEFT,
    COL_LS_DAF,           "",  40, LVCFMT_LEFT,
    COL_LS_PNR_VSE,       "",  40, LVCFMT_RIGHT,
    COL_LS_PNR_CSC,       "",  45, LVCFMT_RIGHT,
    COL_LS_PNR_LIEF,      "",  40, LVCFMT_RIGHT,
    COL_LS_ARTICLECODE,   "",  70, LVCFMT_RIGHT,
    COL_LS_PZN,           "",  65, LVCFMT_RIGHT,
    COL_LS_INVOICE_PREIS, "",  50, LVCFMT_RIGHT,
    COL_LS_TAX_PCT,       "",  50, LVCFMT_RIGHT,
    COL_LS_BASE_PREIS,    "",  40, LVCFMT_RIGHT,
    COL_LS_LOGIST,        "",  50, LVCFMT_RIGHT,
    COL_LS_MIN_LOGIST,    "",  90, LVCFMT_RIGHT,
    COL_LS_REFERENCE,     "", 200, LVCFMT_LEFT,
    COL_LS_TYPE,          "",   0, LVCFMT_LEFT,
    COL_LS_COUNT,         "",   0, LVCFMT_LEFT,
    -1,                   "",   0, 0
};

// CDOrderInformation2 dialog

IMPLEMENT_DYNAMIC(CDOrderInformation2, CPropertyPage)

CDOrderInformation2::CDOrderInformation2()
    : CTabPageMultiLang(IDD_AE_ORDER_INFORMATION2)
{
    m_bNoData = TRUE;
    m_ActDatum = 0;
    m_init = FALSE;
}

CDOrderInformation2::~CDOrderInformation2()
{
}

void CDOrderInformation2::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_DETAILS, m_CTabCtrlOrderInformation2);
    DDX_Control(pDX, IDC_LIST_TAX, m_CListVat);
    DDX_Control(pDX, IDC_LIST_LIEFERPOS, m_CListLief);
}


BEGIN_MESSAGE_MAP(CDOrderInformation2, CTabPageMultiLang)
    ON_NOTIFY(NM_CLICK, IDC_LIST_LIEFERPOS, &CDOrderInformation2::OnNMClickListLieferpos)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LIEFERPOS, &CDOrderInformation2::OnLvnItemchangedListLieferpos)
END_MESSAGE_MAP()


// CDOrderInformation2 message handlers

//--- GetTabTitle ------------------------------------------------------------//

LPCTSTR CDOrderInformation2::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_LIEFERSCHEIN_INFO);
    return _T(m_csTitle);
}


BOOL CDOrderInformation2::OnSetActive()
{
    if (!m_init)
    {
        m_CTabCtrlOrderInformation2.AddPage(&m_PageDOrderInformationDetails1);
        m_CTabCtrlOrderInformation2.AddPage(&m_PageDOrderInformationDetails2);
        m_CTabCtrlOrderInformation2.AddPage(&m_PageDOrderInformationDetails3);
        m_CTabCtrlOrderInformation2.AddPage(&m_PageDOrderInformationDetails4);
        m_CTabCtrlOrderInformation2.AddPage(&m_PageDOrderInformationDetails5);
        m_PageDOrderInformationDetails1.m_listpos = 0;
        m_PageDOrderInformationDetails2.m_listpos = 0;
        m_PageDOrderInformationDetails3.m_listpos = 0;
        m_PageDOrderInformationDetails4.m_listpos = 0;
        m_PageDOrderInformationDetails5.m_listpos = 0;
        m_PageDOrderInformationDetails1.FillList();
        m_PageDOrderInformationDetails2.FillList();
        m_PageDOrderInformationDetails3.FillList();
        m_PageDOrderInformationDetails4.FillList();
        m_PageDOrderInformationDetails5.FillList();

        m_init = TRUE;
    }
    return CTabPageMultiLang::OnSetActive();
}


BOOL CDOrderInformation2::OnInitDialog()
{
    CTabPageMultiLang::OnInitDialog();

    DWORD dwOldBits = m_CListLief.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_CListLief.SetExtendedStyle(dwOldBits);

    m_CListLief.ModifyStyle(LVS_SHOWSELALWAYS, 0);

    //SpaltenVat[0].Columns = CResString::ex().getStrTblText(AETXT_DAT_WE);
    SpaltenVat[1].Columns = CResString::ex().getStrTblText(AETXT_MWST);
    SpaltenVat[2].Columns = CResString::ex().getStrTblText(AETXT_WERT_NETTO);
    SpaltenVat[3].Columns = CResString::ex().getStrTblText(AETXT_WERT_TAX);

    SpaltenLief[COL_LS_AMGE].Columns = CResString::ex().getStrTblText(AETXT_AMGE);
    SpaltenLief[COL_LS_BMGE].Columns = CResString::ex().getStrTblText(AETXT_BMGE);
    SpaltenLief[COL_LS_NRME].Columns = CResString::ex().getStrTblText(AETXT_NRME);
    SpaltenLief[COL_LS_RMME].Columns = CResString::ex().getStrTblText(AETXT_QTY_INVOICED);
    SpaltenLief[COL_LS_NLME].Columns = CResString::ex().getStrTblText(AETXT_KZ_NACHL);
    SpaltenLief[COL_LS_EINHEIT].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    SpaltenLief[COL_LS_ARTIKELNAME].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    SpaltenLief[COL_LS_DAF].Columns = CResString::ex().getStrTblText(AETXT_DAF);
    SpaltenLief[COL_LS_PNR_VSE].Columns = CResString::ex().getStrTblText(AETXT_PNR_VSE);
    SpaltenLief[COL_LS_PNR_CSC].Columns = CResString::ex().getStrTblText(AETXT_PNR_CSC);
    SpaltenLief[COL_LS_PNR_LIEF].Columns = CResString::ex().getStrTblText(AETXT_PNR_LIEF);
    SpaltenLief[COL_LS_ARTICLECODE].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    SpaltenLief[COL_LS_PZN].Columns = CResString::ex().getStrTblText(AETXT_ARTIKEL_NR);
    SpaltenLief[COL_LS_INVOICE_PREIS].Columns = CResString::ex().getStrTblText(AETXT_PREIS);
    SpaltenLief[COL_LS_TAX_PCT].Columns = CResString::ex().getStrTblText(AETXT_MWST);
    SpaltenLief[COL_LS_BASE_PREIS].Columns = CResString::ex().getStrTblText(AETXT_AGP);
    SpaltenLief[COL_LS_LOGIST].Columns = CResString::ex().getStrTblText(AETXT_LOG);
    SpaltenLief[COL_LS_MIN_LOGIST].Columns = CResString::ex().getStrTblText(AETXT_LOG_MIN);
    SpaltenLief[COL_LS_REFERENCE].Columns = CResString::ex().getStrTblText(AETXT_REFERENCE);
    SpaltenLief[COL_LS_TYPE].Columns = CResString::ex().getStrTblText(AETXT_POSTYP);

    if (   !CListCtrlHelper::AddColumns(SpaltenVat, m_CListVat)
        || !CListCtrlHelper::AddColumns(SpaltenLief, m_CListLief) )
    {
        return FALSE;
    }

    //AusgKopf();
    if (AusgKopf() > 0) return FALSE;

    AusgPosListe();

    /*m_CTabCtrlOrderInformation2.AddPage(&m_PageDOrderInformationDetails1);
    m_CTabCtrlOrderInformation2.AddPage(&m_PageDOrderInformationDetails2);
    m_CTabCtrlOrderInformation2.AddPage(&m_PageDOrderInformationDetails3);
    m_CTabCtrlOrderInformation2.AddPage(&m_PageDOrderInformationDetails4);
    m_CTabCtrlOrderInformation2.AddPage(&m_PageDOrderInformationDetails5);
    */
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDOrderInformation2::AusgPosListe()
{
    int rc;
    char error_msg[81];
    //Lieferscheinlistbox füllen
    int count = 0;
    CStringArray s;
    ppString text;
    s.SetSize(COL_LS_ANZ_LIST);
    CDELIVERYADVICELINE line;
    m_CListLief.DeleteAllItems();
    BeginWaitCursor();
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvSelDeliveryAdviceLine, (void*)&line.s, DELIVERYADVICELINE_BES, DELIVERYADVICELINE_ANZ, error_msg);
        if (rc < SRV_OK)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
        if (rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        s[COL_LS_AMGE].Format("%d", line.GetQty_ordered());
        s[COL_LS_BMGE].Format("%d", line.GetQty_confirmed());
        s[COL_LS_NRME].Format("%d", line.GetQty_rebateinkind());
        s[COL_LS_RMME].Format("%d", line.GetQty_invoiced());
        if (line.GetLinetype() == 2)    //Nachliefeung
        {
            s[COL_LS_NLME].Format("%d", line.GetQty_ordered() - line.GetQty_confirmed());
        }
        else
        {
            s[COL_LS_NLME].Empty();
        }
        s[COL_LS_EINHEIT] = line.GetArticleunit(text);
        s[COL_LS_ARTIKELNAME] = line.GetDaarticlename(text);
        s[COL_LS_DAF] = line.GetPharmaceuticalform(text);
        s[COL_LS_PNR_VSE].Format("%d", line.GetPharmosorderposno());
        s[COL_LS_PNR_CSC].Format("%d", line.GetCscorderposno());
        s[COL_LS_PNR_LIEF].Format("%d", line.GetDeliveryadviceposno());
        s[COL_LS_ARTICLECODE] = line.GetArticle_code(text);
        s[COL_LS_PZN].Format("%d", line.GetArticleno());
        s[COL_LS_INVOICE_PREIS].Format("%0.2lf", line.GetDainvoicedprice());
        s[COL_LS_TAX_PCT].Format("%0.2lf", line.GetVatpercentage());
        s[COL_LS_BASE_PREIS].Format("%0.2lf", line.GetDabaseprice());
        s[COL_LS_LOGIST].Format("%0.2lf", line.GetLogisticservicecost());
        s[COL_LS_MIN_LOGIST].Format("%0.2lf", line.GetMinlogisticservicecostvalue());
        s[COL_LS_REFERENCE] = line.GetLinereference(text);
        s[COL_LS_TYPE].Format("%d", line.GetLinetype());
        s[COL_LS_COUNT].Format("%d", count);

        if (!CListCtrlHelper::AppendItem(m_CListLief, COL_LS_ANZ_LIST, s))
        {
            EndWaitCursor();
            return;
        }
        count++;
    }
    EndWaitCursor();
    //CListCtrlHelper::SetFocusSelectedFocused(m_CListLief, 0);
}

int CDOrderInformation2::AusgKopf()
{
    int rc;
    char error_msg[81];
    //char buffer[81];
    ppString hilfe;
    CString text;
    //text.Format("%0.10d", atol(Rech_Nr));

    //text = "0000000000" + Rech_Nr;
    //text = text.Right(10);

    CDELIVERYADVICEHEAD head;

    head.SetBranchno(m_VzNr);
    head.SetCustomerno(m_KndNr);
    //head.SetDeliveryadviceno(text);
    head.SetDeliveryadviceno(Rech_Nr);
    head.SetDeliveryadvicedate(m_lDatumAuftrag);

    rc = ::ServerNr(PIPE_AE_SRV, AasrvSelDeliveryAdviceHead, (void *)&head.s, DELIVERYADVICEHEAD_BES, DELIVERYADVICEHEAD_ANZ, error_msg);
    if (rc < SRV_OK)
    {
        FehlerBehandlung(rc, error_msg);
        return 1;
    }
    if (rc == SRV_SQLNOTFOUND)
    {
        //MsgBoxOK(AETXT_KEIN_LIEFERSCHEIN_DATA);
        return 1;
    }
    m_bNoData = FALSE;
    m_sBatchAdvice = head.GetBatchcorrectionadvice();
    //AllgDatumLong2CharTTMMJJJJ(m_lDatumAuftrag, buffer);
    text.Format("%d", head.GetCscorderno());
    GetDlgItem(IDC_STATIC_AUFTR_NR)->SetWindowText(text);
    text.Format("%d", head.GetPharmosorderno());
    GetDlgItem(IDC_STATIC_AUFTR_NR_VSE)->SetWindowText(text);
    GetDlgItem(IDC_STATIC_RECHNR)->SetWindowText(head.GetDeliveryadviceno(hilfe));
    if (head.GetCompleted() == '1')
    {
        GetDlgItem(IDC_STATIC_COMPLETED_WERT)->SetWindowText(CResString::ex().getStrTblText(AETXT_JA));
    }
    else
    {
        GetDlgItem(IDC_STATIC_COMPLETED_WERT)->SetWindowText(CResString::ex().getStrTblText(AETXT_NEIN));
    }
    text.Format("%d", head.GetRequested());
    GetDlgItem(IDC_STATIC_ASKED_WERT)->SetWindowText(text);
    if (head.GetConfirmed() == 1)
    {
        GetDlgItem(IDC_STATIC_CONFIRMED_WERT)->SetWindowText(CResString::ex().getStrTblText(AETXT_JA));
    }
    else
    {
        GetDlgItem(IDC_STATIC_CONFIRMED_WERT)->SetWindowText(CResString::ex().getStrTblText(AETXT_NEIN));
    }
    if (head.GetCancelled() == 1)
    {
        GetDlgItem(IDC_STATIC_CANCELED_WERT)->SetWindowText(CResString::ex().getStrTblText(AETXT_JA));
    }
    else
    {
        GetDlgItem(IDC_STATIC_CANCELED_WERT)->SetWindowText(CResString::ex().getStrTblText(AETXT_NEIN));
    }
    head.GetContractid(hilfe);
    if (false == hilfe.empty())
    {
        GetDlgItem(IDC_STATIC_CONTRACTID_WERT)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_CONTRACTID_WERT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_CONTRACT_ID)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_CONTRACT_ID)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_CONTRACTID_WERT)->SetWindowText(hilfe);
    }
    else
    {
        GetDlgItem(IDC_STATIC_CONTRACTID_WERT)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_CONTRACTID_WERT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_CONTRACT_ID)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_CONTRACT_ID)->ShowWindow(SW_HIDE);
    }

    //SteuerListe füllen
    m_CListVat.DeleteAllItems();
    CStringArray s;
    s.SetSize(NUM_SPALT_VAT);
    CDELIVERYADVICEVATTOTALS vat;
    BeginWaitCursor();
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvSelDeliveryAdviceVATTotals, (void *)&vat.s, DELIVERYADVICEVATTOTALS_BES, DELIVERYADVICEVATTOTALS_ANZ, error_msg);
        if (rc < SRV_OK)
        {
            FehlerBehandlung(rc, error_msg);
            return 1;
        }
        if (rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        s[0] = vat.GetDavat();
        s[1].Format("%0.2lf", vat.GetVatpercentage());
        s[2].Format("%0.2lf", vat.GetNetvalue());
        s[3].Format("%0.2lf", vat.GetVatvalue());

        if (!CListCtrlHelper::AppendItem(m_CListVat, NUM_SPALT_VAT, s))
        {
            EndWaitCursor();
            return 1;
        }
    }
    EndWaitCursor();
    return 0;
}

void CDOrderInformation2::AlterInvoice()
{
    if (AusgKopf() > 0)
        return;
    AusgPosListe();
    m_PageDOrderInformationDetails1.m_listpos = 0;
    m_PageDOrderInformationDetails2.m_listpos = 0;
    m_PageDOrderInformationDetails3.m_listpos = 0;
    m_PageDOrderInformationDetails4.m_listpos = 0;
    m_PageDOrderInformationDetails5.m_listpos = 0;
    m_PageDOrderInformationDetails1.FillList();
    m_PageDOrderInformationDetails2.FillList();
    m_PageDOrderInformationDetails3.FillList();
    m_PageDOrderInformationDetails4.FillList();
    m_PageDOrderInformationDetails5.FillList();
}

void CDOrderInformation2::OnNMClickListLieferpos(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    int pos = m_CListLief.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        int count = atoi(m_CListLief.GetItemText(pos, COL_LS_COUNT));
        if (m_PageDOrderInformationDetails1.m_listpos != count)
        {
            m_PageDOrderInformationDetails1.m_listpos = count;
            m_PageDOrderInformationDetails2.m_listpos = count;
            m_PageDOrderInformationDetails3.m_listpos = count;
            m_PageDOrderInformationDetails4.m_listpos = count;
            m_PageDOrderInformationDetails5.m_listpos = count;
            m_PageDOrderInformationDetails1.FillList();
            m_PageDOrderInformationDetails2.FillList();
            m_PageDOrderInformationDetails3.FillList();
            m_PageDOrderInformationDetails4.FillList();
            m_PageDOrderInformationDetails5.FillList();
        }
    }
    *pResult = 0L;
}

void CDOrderInformation2::OnLvnItemchangedListLieferpos(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    int pos = m_CListLief.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        int count = atoi(m_CListLief.GetItemText(pos, COL_LS_COUNT));
        if (m_PageDOrderInformationDetails1.m_listpos != count)
        {
            m_PageDOrderInformationDetails1.m_listpos = count;
            m_PageDOrderInformationDetails2.m_listpos = count;
            m_PageDOrderInformationDetails3.m_listpos = count;
            m_PageDOrderInformationDetails4.m_listpos = count;
            m_PageDOrderInformationDetails5.m_listpos = count;
            m_PageDOrderInformationDetails1.FillList();
            m_PageDOrderInformationDetails2.FillList();
            m_PageDOrderInformationDetails3.FillList();
            m_PageDOrderInformationDetails4.FillList();
            m_PageDOrderInformationDetails5.FillList();
        }
    }
    *pResult = 0L;
}

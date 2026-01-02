// DTenderWahl.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <tender.h>
#include "DTenderWahl.h"
#include "DArtDef.h"


//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_RIGHT,
    1,  "",  70, LVCFMT_RIGHT,
    2,  "",  90, LVCFMT_LEFT,
    3,  "", 100, LVCFMT_LEFT,
    4,  "",  70, LVCFMT_LEFT,
    5,  "",  70, LVCFMT_RIGHT,
    -1, "",   0, 0
};


// CDTenderWahl-Dialogfeld

IMPLEMENT_DYNAMIC(CDTenderWahl, CDialog)
CDTenderWahl::CDTenderWahl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDTenderWahl::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TENDER_NO);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_ART);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_TENDER_CONTRACT);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_VON);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    m_sVz = 0;
    m_lKnd = 0;
    m_lTenderNo = 0;
    m_iStaat = 0;
}

CDTenderWahl::~CDTenderWahl()
{
}

void CDTenderWahl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDTenderWahl, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_PZN, OnBnClickedButtonPzn)
    ON_BN_CLICKED(IDC_BUTTON_ALLE, OnBnClickedButtonAlle)
END_MESSAGE_MAP()


// CDTenderWahl-Meldungshandler

BOOL CDTenderWahl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    DWORD dwOldBits = m_List1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_List1.SetExtendedStyle(dwOldBits);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }
    if (!AeGetApp()->IsRS())
    {
        GetDlgItem(IDC_BUTTON_PZN)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_PZN)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_ALLE)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_ALLE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_AUSWAHL)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_AUSWAHL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PZN)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_PZN)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_NAME)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_NAME)->ShowWindow(SW_HIDE);
    }
    if (GetPageAlle() == 0)  //Keine Tender vorhanden
    {
        CDialogMultiLang::OnCancel();
        return TRUE;
    }

    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);

    return TRUE;
}

void CDTenderWahl::OnOK()
{
    UpdateData();

    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
        return;
    }
    m_lTenderNo = atol(m_List1.GetItemText(pos, 1));
    m_cContract = m_List1.GetItemText(pos, 3);
    CDialogMultiLang::OnOK();
}

void CDTenderWahl::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnOK();
    *pResult = 0L;
}

void CDTenderWahl::OnBnClickedButtonPzn()
{
    CDArtDef dlgArtDef;
    if (dlgArtDef.DoModal() == IDOK)
    {
        CString cPZN;
        m_ArtikelNr = dlgArtDef.GetArtNr();
        cPZN.Format("%d", m_ArtikelNr);
        GetDlgItem(IDC_STATIC_PZN)->SetWindowText(cPZN);
        GetDlgItem(IDC_STATIC_NAME)->SetWindowText(dlgArtDef.GetArtName());
        GetDlgItem(IDC_STATIC_AUSWAHL)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_AUSWAHL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PZN)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_PZN)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_NAME)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NAME)->ShowWindow(SW_SHOW);
    }
    else
    {
        return;
    }

    CTENDERINFO info;
    //Variablen
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    ppString contract;
    char dateStr[81];
    int count = 0;

    //Anfangsinitialisierung durchfuehren
    m_List1.DeleteAllItems();

    info.SetBranchno(m_sVz);
    info.SetCustomerno(m_lKnd);
    info.SetArticleno(m_ArtikelNr);
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (info.SelListPos() != SRV_OK)
            break;
        count++;
        s[0] = kb.Next();
        s[1].Format("%d", info.GetTenderno());
        s[2] = CResString::ex().getStrTblText(info.GetTendertype() == 2 ? AETXT_STAAT : AETXT_KRANKENHAUS);
        info.GetContractno(contract);
        s[3] = contract;
        s[4] = AllgDatumLong2CharTTMMJJJJ(info.GetDatefrom(), dateStr);
        s[5] = AllgDatumLong2CharTTMMJJJJ(info.GetDateto(), dateStr);

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    EndWaitCursor();
    if (count == 0)
    {
        MsgBoxOK(AETXT_NO_TENDER);
    }
    else
    {
        GotoDlgCtrl(GetDlgItem(IDC_LIST1));
        CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);
    }
}

void CDTenderWahl::OnBnClickedButtonAlle()
{
    GetPageAlle();  //Kann hier keine 0 zurückgeben, da bereits in Initdialog erledigt
}

int CDTenderWahl::GetPageAlle()
{
    CTENDERINFO info;
    //Variablen
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    ppString contract;
    char dateStr[81];
    int count = 0;

    //Anfangsinitialisierung durchfuehren
    m_List1.DeleteAllItems();

    info.SetBranchno(m_sVz);
    info.SetCustomerno(m_lKnd);
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (AeGetApp()->IsBG() && m_iStaat == 1)
        {
            if (info.SelListStaat() != SRV_OK)
                break;
        }
        else if (AeGetApp()->IsRS())
        {
            if (info.SelListChain() != SRV_OK)
                break;
        }
        else
        {
            if (info.SelList() != SRV_OK)
                break;
        }
        ++count;
        s[0] = kb.Next();
        s[1].Format("%d", info.GetTenderno());
        s[2] = CResString::ex().getStrTblText(info.GetTendertype() == 2 ? AETXT_STAAT : AETXT_KRANKENHAUS);
        info.GetContractno(contract);
        s[3] = contract;
        s[4] = AllgDatumLong2CharTTMMJJJJ(info.GetDatefrom(), dateStr);
        s[5] = AllgDatumLong2CharTTMMJJJJ(info.GetDateto(), dateStr);

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    EndWaitCursor();
    if (AeGetApp()->IsRS())
    {
        GetDlgItem(IDC_STATIC_AUSWAHL)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_AUSWAHL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PZN)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_PZN)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_NAME)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_NAME)->ShowWindow(SW_HIDE);
    }
    return count;
}

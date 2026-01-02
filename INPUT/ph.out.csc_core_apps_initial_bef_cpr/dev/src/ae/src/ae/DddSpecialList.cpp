// DddSpecialList.cpp : implementation file
//

#include "stdafx.h"
#include "DddSpecialList.h"
#include <customer.h>
#include "DddSpecialUpd.h"

//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB          0
#define COL_VALID_FROM  1
#define COL_WD          2
#define COL_TIME_FROM   3
#define COL_WD_DD       4
#define COL_BTM         5
#define COL_KK          6
#define COL_K08         7
#define COL_K20         8
#define NUM_COLUMNS     9

static COLUMNS_TYPES Columns[] =
{
    COL_KB,         "",  35, LVCFMT_LEFT,
    COL_VALID_FROM, "",  70, LVCFMT_LEFT,
    COL_WD,         "", 120, LVCFMT_LEFT,
    COL_TIME_FROM,  "",  65, LVCFMT_LEFT,
    COL_WD_DD,      "", 120, LVCFMT_LEFT,
    COL_BTM,        "",  46, LVCFMT_LEFT,
    COL_KK,         "",  46, LVCFMT_LEFT,
    COL_K08,        "",  46, LVCFMT_RIGHT,
    COL_K20,        "",  46, LVCFMT_LEFT,
    -1,             "",   0, 0
};

// CDddSpecialList dialog

IMPLEMENT_DYNAMIC(CDddSpecialList, CDialog)

CDddSpecialList::CDddSpecialList(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDddSpecialList::IDD, pParent)
{

    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_VALID_FROM].Columns = CResString::ex().getStrTblText(AETXT_VALID_AM);
    Columns[COL_WD].Columns = CResString::ex().getStrTblText(AETXT_TAG);
    Columns[COL_TIME_FROM].Columns = CResString::ex().getStrTblText(AETXT_TIME_FROM);
    Columns[COL_WD_DD].Columns = CResString::ex().getStrTblText(AETXT_TAG_DELAY);
    Columns[COL_BTM].Columns = CResString::ex().getStrTblText(AETXT_BTM);
    Columns[COL_KK].Columns = CResString::ex().getStrTblText(AETXT_KK);
    Columns[COL_K08].Columns = CResString::ex().getStrTblText(AETXT_K08);
    Columns[COL_K20].Columns = CResString::ex().getStrTblText(AETXT_K20);

}

CDddSpecialList::~CDddSpecialList()
{
}

void CDddSpecialList::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDddSpecialList, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_INS, &CDddSpecialList::OnBnClickedButtonIns)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CDddSpecialList::OnBnClickedButtonDel)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDddSpecialList::OnNMDblclkList1)
END_MESSAGE_MAP()


// CDddSpecialList message handlers

BOOL CDddSpecialList::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }

    m_DayList.Add(CResString::ex().getStrTblText(IDS_SUNDAY));
    m_DayList.Add(CResString::ex().getStrTblText(IDS_MONDAY));
    m_DayList.Add(CResString::ex().getStrTblText(IDS_TUESDAY));
    m_DayList.Add(CResString::ex().getStrTblText(IDS_WEDNESDAY));
    m_DayList.Add(CResString::ex().getStrTblText(IDS_THURSDAY));
    m_DayList.Add(CResString::ex().getStrTblText(IDS_FRIDAY));
    m_DayList.Add(CResString::ex().getStrTblText(IDS_SATURDAY));

    CenterWindow();
    GetPage();
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDddSpecialList::OnOK()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDddSpecialUpd upd;
        upd.m_iFunction = CDddSpecialUpd::DDupdate;
        upd.m_lFrom = atol(m_List1.GetItemText(pos, COL_VALID_FROM).Right(4)) * 10000 + atol(m_List1.GetItemText(pos, COL_VALID_FROM).Mid(3, 2)) * 100
            + atol(m_List1.GetItemText(pos, COL_VALID_FROM).Left(2));
        for (upd.m_iWD = 0; upd.m_iWD < 7; upd.m_iWD++)
        {
            if (m_DayList.GetAt(upd.m_iWD) == m_List1.GetItemText(pos, COL_WD))
                break;
        }
        upd.m_Zeit = atol(m_List1.GetItemText(pos, COL_TIME_FROM).Left(2)) * 100 + atol(m_List1.GetItemText(pos, COL_TIME_FROM).Right(2));
        for (upd.m_iWDDD = 0; upd.m_iWDDD < 7; upd.m_iWDDD++)
        {
            if (m_DayList.GetAt(upd.m_iWDDD) == m_List1.GetItemText(pos, COL_WD_DD))
                break;
        }
        upd.m_bBTM = (m_List1.GetItemText(pos, COL_BTM) == CResString::ex().getStrTblText(AETXT_JA));
        upd.m_bKK = (m_List1.GetItemText(pos, COL_KK) == CResString::ex().getStrTblText(AETXT_JA));
        upd.m_bK08 = (m_List1.GetItemText(pos, COL_K08) == CResString::ex().getStrTblText(AETXT_JA));
        upd.m_bK20 = (m_List1.GetItemText(pos, COL_K20) == CResString::ex().getStrTblText(AETXT_JA));
        if (upd.DoModal() == IDOK)
            GetPage();
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDddSpecialList::GetPage()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    CDELAYEDDELIVERYCSTSPECIAL m_Cst;
    m_Cst.SetBranchno(AeGetApp()->VzNr());

    m_List1.DeleteAllItems();
    CLetterMan kb;
    for (;;)
    {
        if (m_Cst.Sel())
            break;

        s[COL_KB] = kb.Next();
        s[COL_VALID_FROM] = DDMMYYYYStringFromDateLong(m_Cst.GetDatefrom());
        s[COL_WD] = m_DayList.GetAt(m_Cst.GetWeekday());
        s[COL_TIME_FROM].Format("%02d:%02d", m_Cst.GetTime() / 100, m_Cst.GetTime() % 100);
        s[COL_WD_DD] = m_DayList.GetAt(m_Cst.GetDelayedweekday());
        s[COL_BTM] = CResString::ex().getStrTblText((m_Cst.GetNarcotic() == '1') ? AETXT_JA : AETXT_NEIN);
        s[COL_KK] = CResString::ex().getStrTblText((m_Cst.GetColdchain() == '1') ? AETXT_JA : AETXT_NEIN);
        s[COL_K08] = CResString::ex().getStrTblText((m_Cst.GetCool08() == '1') ? AETXT_JA : AETXT_NEIN);
        s[COL_K20] = CResString::ex().getStrTblText((m_Cst.GetCool20() == '1') ? AETXT_JA : AETXT_NEIN);

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
}

void CDddSpecialList::OnBnClickedButtonIns()
{
    CDddSpecialUpd upd;
    upd.m_iFunction = CDddSpecialUpd::DDinsert;
    if (upd.DoModal() == IDOK)
        GetPage();
}

void CDddSpecialList::OnBnClickedButtonDel()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        short iDay;
        CDELAYEDDELIVERYCSTSPECIAL m_Cst;
        m_Cst.SetBranchno(AeGetApp()->VzNr());
        m_Cst.SetCustomerno(0);
        m_Cst.SetDatefrom(atol(m_List1.GetItemText(pos, COL_VALID_FROM).Right(4)) * 10000 + atol(m_List1.GetItemText(pos, COL_VALID_FROM).Mid(3, 2)) * 100
            + atol(m_List1.GetItemText(pos, COL_VALID_FROM).Left(2)));
        for (iDay = 0; iDay < 7; iDay++)
        {
            if (m_DayList.GetAt(iDay) == m_List1.GetItemText(pos, COL_WD))
            {
                m_Cst.SetWeekday(iDay);
                break;
            }
        }
        if (!m_Cst.Delete())
            GetPage();
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDddSpecialList::OnNMDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnOK();

    *pResult = 0L;
}

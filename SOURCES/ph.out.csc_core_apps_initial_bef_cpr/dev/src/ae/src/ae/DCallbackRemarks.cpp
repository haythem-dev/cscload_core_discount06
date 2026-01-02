// DCallbackRemarks.cpp : implementation file
//

#include "stdafx.h"
#include "DCallbackRemarks.h"
#include <callback.h>


//Definition der Tabellenbreite und der Ueberschriften

#define COL_NO          0
#define COL_CBHEADER    1
#define COL_CBTEXT      2
#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    COL_NO,       "",   0, LVCFMT_LEFT,
    COL_CBHEADER, "", 250, LVCFMT_LEFT,
    COL_CBTEXT,   "", 750, LVCFMT_LEFT,
    -1,           "",   0, 0
};

// CDCallbackRemarks dialog

IMPLEMENT_DYNAMIC(CDCallbackRemarks, CDialog)

CDCallbackRemarks::CDCallbackRemarks(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCallbackRemarks::IDD, pParent)
{

    Columns[COL_NO].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
    Columns[COL_CBHEADER].Columns = CResString::ex().getStrTblText(AETXT_CB_HEADER);
    Columns[COL_CBTEXT].Columns = CResString::ex().getStrTblText(IDS_BEMERK);
}

CDCallbackRemarks::~CDCallbackRemarks()
{
}

void CDCallbackRemarks::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDCallbackRemarks, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_UPD, &CDCallbackRemarks::OnBnClickedButtonUpd)
    ON_BN_CLICKED(IDC_BUTTON_INS, &CDCallbackRemarks::OnBnClickedButtonIns)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CDCallbackRemarks::OnBnClickedButtonDel)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDCallbackRemarks::OnNMDblclkList1)
END_MESSAGE_MAP()


// CDCallbackRemarks message handlers


void CDCallbackRemarks::OnBnClickedButtonUpd()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        MsgBoxOK( IDP_KEIN_SATZ_SEL );
        return;
    }
    CDCallbackRemarksUpd upd;
    upd.m_lRemarkNo = atol(m_List1.GetItemText(pos, COL_NO));
    upd.m_cCBHeader = m_List1.GetItemText(pos, COL_CBHEADER);
    upd.m_cCBText = m_List1.GetItemText(pos, COL_CBTEXT);
    if (upd.DoModal() == IDOK)
        GetPage();
}

void CDCallbackRemarks::OnBnClickedButtonIns()
{
    CDCallbackRemarksUpd ins;
    if (ins.DoModal() == IDOK)
        GetPage();
}

void CDCallbackRemarks::OnBnClickedButtonDel()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        MsgBoxOK( IDP_KEIN_SATZ_SEL );
        return;
    }
    else
    {
        if (MsgBoxYesNo(IDP_SOLL_DEL_SATZ) != IDYES)
            return;
    }
    CCALLBACKREMARKS remarks;
    remarks.SetRemarkno(atol(m_List1.GetItemText(pos, COL_NO)));
    remarks.DeleteRemark();
    GetPage();
}


void CDCallbackRemarks::OnNMDblclkList1(NMHDR * /*pNMHDR*/, LRESULT *pResult)
{
    OnBnClickedButtonUpd();

    *pResult = 0L;
}

BOOL CDCallbackRemarks::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    DWORD dwOldBits = m_List1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_List1.SetExtendedStyle(dwOldBits);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }

    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCallbackRemarks::GetPage()
{
    CStringArray s;
    ppString text;
    s.SetSize(NUM_COLUMNS);
    CCALLBACKREMARKS remarks;
    m_List1.DeleteAllItems();
    BeginWaitCursor();
    for (;;)
    {
        if (remarks.SelList() != SRV_OK) break;
        s[COL_NO].Format("%d", remarks.GetRemarkno());
        s[COL_CBHEADER] = remarks.GetCallbackremarkheader(text);
        s[COL_CBTEXT] = remarks.GetCallbackremarktext(text);

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);
}

// CDCallbackRemarksUpd dialog

IMPLEMENT_DYNAMIC(CDCallbackRemarksUpd, CDialog)

CDCallbackRemarksUpd::CDCallbackRemarksUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCallbackRemarksUpd::IDD, pParent)
    , m_cCBHeader(_T(""))
    , m_cCBText(_T(""))
{
    m_lRemarkNo = 0;
}

CDCallbackRemarksUpd::~CDCallbackRemarksUpd()
{
}

void CDCallbackRemarksUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_CB_HEADER, m_cCBHeader);
    DDX_Text(pDX, IDC_EDIT_CB_TEXT, m_cCBText);
}


BEGIN_MESSAGE_MAP(CDCallbackRemarksUpd, CDialogMultiLang)
END_MESSAGE_MAP()


// CDCallbackRemarksUpd message handlers


void CDCallbackRemarksUpd::OnOK()
{
    UpdateData(TRUE);
    CCALLBACKREMARKS remarks;
    remarks.SetRemarkno(m_lRemarkNo);
    remarks.SetCallbackremarkheader(m_cCBHeader);
    remarks.SetCallbackremarktext(m_cCBText);
    if (m_lRemarkNo == 0)
        remarks.Insert();
    else
        remarks.Update();

    CDialogMultiLang::OnOK();
}

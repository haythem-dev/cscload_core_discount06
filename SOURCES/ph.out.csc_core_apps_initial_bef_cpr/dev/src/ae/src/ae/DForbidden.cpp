// DForbidden.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <controlling.h>
#include "DForbidden.h"
#include "DForbiddenUpd.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     4

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_LEFT,
    1,  "", 180, LVCFMT_LEFT,
    2,  "",  80, LVCFMT_LEFT,
    3,  "",  80, LVCFMT_LEFT,
    -1, "",   0, 0
};

// CDForbidden-Dialogfeld

IMPLEMENT_DYNAMIC(CDForbidden, CDialog)
CDForbidden::CDForbidden(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDForbidden::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_WORT);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_ERLAUBT_VON);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ERLAUBT_BIS);
}

CDForbidden::~CDForbidden()
{
}

void CDForbidden::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDForbidden, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnBnClickedButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnBnClickedButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
    ON_NOTIFY(HDN_ITEMDBLCLICK, 0, OnHdnItemdblclickList1)
END_MESSAGE_MAP()


// CDForbidden-Meldungshandler

BOOL CDForbidden::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDForbidden::GetPage()
{
    CFORBIDDENWORDS forbiddenwords;
    forbiddenwords.SetBranchno(AeGetApp()->VzNr());
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    char str[81];
    ppString text;
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    for (;;)
    {
        if (forbiddenwords.SelWordList()) break;
        s[0] = kb.Next();
        s[1] = forbiddenwords.GetForbiddenword(text);
        s[2] = AllgDatumLong2CharTTMMJJJJ(forbiddenwords.GetDatefrom(), str);
        s[3] = AllgDatumLong2CharTTMMJJJJ(forbiddenwords.GetDateto(), str);

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    forbiddenwords.CloseCursor();
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
}

void CDForbidden::OnBnClickedButtonInsert()
{
    CDForbiddenUpd upd;
    if (upd.DoModal() == IDOK)
        GetPage();
}

void CDForbidden::OnBnClickedButtonUpdate()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDForbiddenUpd upd;
        CString datum;
        upd.m_CWord = m_ListCtl.GetItemText(pos, 1);
        datum = m_ListCtl.GetItemText(pos, 2);
        upd.m_lDateFrom = atol(datum.Left(2))
            + atol(datum.Mid(3,2))*100
            + atol(datum.Right(4))*10000;
        datum = m_ListCtl.GetItemText(pos, 3);
        upd.m_lDateTo = atol(datum.Left(2))
            + atol(datum.Mid(3,2))*100
            + atol(datum.Right(4))*10000;
        if (upd.DoModal() == IDOK)
            GetPage();
    }
}

void CDForbidden::OnBnClickedButtonDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            CFORBIDDENWORDS forbiddenwords;
            forbiddenwords.SetBranchno(AeGetApp()->VzNr());
            forbiddenwords.SetForbiddenword(m_ListCtl.GetItemText(pos, 1));
            if (forbiddenwords.DeleteWord() == 0)
                GetPage();
        }
    }
}

void CDForbidden::OnHdnItemdblclickList1(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    OnBnClickedButtonUpdate();
    *pResult = 0L;
}

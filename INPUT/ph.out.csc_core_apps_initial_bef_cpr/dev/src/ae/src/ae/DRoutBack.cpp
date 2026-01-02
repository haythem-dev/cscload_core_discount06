// DRoutBack.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <filialpartner.h>
#include "DRoutBack.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 120, LVCFMT_LEFT,
    2,  "", 120, LVCFMT_LEFT,
    -1, "",   0, 0
};


// CDRoutBack-Dialogfeld

IMPLEMENT_DYNAMIC(CDRoutBack, CDialog)
CDRoutBack::CDRoutBack(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDRoutBack::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_ABTEILUNG);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_TELEFON_NR);
}

CDRoutBack::~CDRoutBack()
{
}

void CDRoutBack::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDRoutBack, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_BLIND, OnBnClickedButtonBlind)
END_MESSAGE_MAP()


// CDRoutBack-Meldungshandler

BOOL CDRoutBack::OnInitDialog()
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

void CDRoutBack::GetPage()
{
    ppString cDepartement;
    ppString cPhoneno;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    m_BackRouting.SetBranchno(AeGetApp()->m_ProCenter.GetHiPathVzNr());
    CLetterMan kb;
    for (;;)
    {
        if (m_BackRouting.SelList() != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1].Format("%s", m_BackRouting.GetDepartement(cDepartement));
        s[2].Format("%s", m_BackRouting.GetPhoneno(cPhoneno));

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_BackRouting.CloseCursor();
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
}

void CDRoutBack::OnBnClickedOk()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        AeGetApp()->IsBackrouting = true;
        AeGetApp()->m_ProCenter.Consult(m_ListCtl.GetItemText(pos, 2));
        CDialogMultiLang::OnOK();
    }
}

void CDRoutBack::OnNMDblclkList1(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    OnBnClickedOk();
    *pResult = 0L;
}

void CDRoutBack::OnBnClickedButtonBlind()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        AeGetApp()->m_ProCenter.BlindTransfer(m_ListCtl.GetItemText(pos, 2));
        OnOK();
    }
}

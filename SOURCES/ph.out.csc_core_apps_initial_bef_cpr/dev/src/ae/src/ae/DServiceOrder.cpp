// DServiceOrder.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "AeFView.h"
#include "AeDoc.h"
#include <serviceorder.h>
#include "DServicePos.h"
#include "DServiceZinsen.h"
#include "DServiceOrder.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_RIGHT,
    1,  "", 200, LVCFMT_LEFT,
    2,  "",   0, LVCFMT_RIGHT,
    -1, "",   0, 0
};

// CDServiceOrder-Dialogfeld

IMPLEMENT_DYNAMIC(CDServiceOrder, CDialog)
CDServiceOrder::CDServiceOrder(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDServiceOrder::IDD, pParent)
{
    m_sServType = 0;
    m_lKndNr = 0;
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
}

CDServiceOrder::~CDServiceOrder()
{
}

void CDServiceOrder::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDServiceOrder, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_ENDE, OnButtonEnde)
    ON_BN_CLICKED(IDC_BUTTON_BEARB, OnButtonBearb)
    ON_MESSAGE(WM_CLOSE_SERVICE, OnCloseDialog)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


// CDServiceOrder-Meldungshandler

BOOL CDServiceOrder::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    CSERVICEMEMBER member;

    DWORD dwOldBits = m_List1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_List1.SetExtendedStyle(dwOldBits);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }
    //Variablen
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    ppString name;

    //Anfangsinitialisierung durchfuehren
    m_List1.DeleteAllItems();

    member.SetServicetypeno(m_sServType);
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (member.SelList() != SRV_OK)
            break;
        s[0] = kb.Next();
        member.GetName(name);
        s[1] = name;
        s[2].Format("%d", member.GetService_no());

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);

    return TRUE;
}

void CDServiceOrder::OnOK()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
        return;
    }

    CDServiceZinsen zinsdlg;
    CDServicePos posdlg;
    if (m_sServType == 6)
    {
        zinsdlg.m_ptrDoc = m_ptrDoc;
        zinsdlg.m_csName = m_List1.GetItemText(pos, 1);
        zinsdlg.m_sServiceNo = static_cast<short>(atoi(m_List1.GetItemText(pos, 2)));
        zinsdlg.DoModal();
    }
    else
    {
        posdlg.m_ptrDoc = m_ptrDoc;
        posdlg.m_csName = m_List1.GetItemText(pos, 1);
        posdlg.m_sServiceNo = static_cast<short>(atoi(m_List1.GetItemText(pos, 2)));
        posdlg.DoModal();
    }
}

void CDServiceOrder::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnOK();
    *pResult = 0L;
}

void CDServiceOrder::OnButtonEnde()
{
    if (!((CAeFView*)AeGetApp()->m_pViewEing)->AuftragSave())
    {
        return;
    }
    CDialogMultiLang::OnOK();
}

void CDServiceOrder::OnButtonBearb()
{
    ((CAeFView*)AeGetApp()->m_pViewEing)->OnAuftrBearb();
}

void CDServiceOrder::OnCancel()
{
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDServiceOrder::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F2)
    {
        OnButtonBearb();
        return 1L;
    }
    else if (((LPMSG)lpMsg)->wParam == VK_F4)
    {
        OnButtonEnde();
        return 1L;
    }
    return 0L;
}

LRESULT CDServiceOrder::OnCloseDialog(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    CDialogMultiLang::OnOK();
    return 0L;
}

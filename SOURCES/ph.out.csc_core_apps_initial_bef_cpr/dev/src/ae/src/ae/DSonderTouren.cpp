// DSonderTouren.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <touren.h>
#include "DSonderTouren.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 80, LVCFMT_LEFT,
    2,  "", 40, LVCFMT_LEFT,
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDSonderTouren


CDSonderTouren::CDSonderTouren(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSonderTouren::IDD, pParent)
{
    m_CAArt = _T("");
    m_CTourId = _T("");

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
}


void CDSonderTouren::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Control(pDX, IDC_TOURID, m_edit_TourId);
    DDX_Control(pDX, IDC_AART, m_edit_AArt);
    DDX_Text(pDX, IDC_AART, m_CAArt);
    DDX_Text(pDX, IDC_TOURID, m_CTourId);
}


BEGIN_MESSAGE_MAP(CDSonderTouren, CDialogMultiLang)
    ON_EN_CHANGE(IDC_AART, OnChangeAart)
    ON_EN_CHANGE(IDC_TOURID, OnChangeTourid)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDSonderTouren

BOOL CDSonderTouren::OnInitDialog()
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
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDSonderTouren::OnChangeAart()
{
    AllgLaengeKontr(&m_edit_AArt, L_SONDERTOUREN_KDAUFTRAGART,AeGetApp()->Modus());
    GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_INSERT)->EnableWindow();
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow();
}

void CDSonderTouren::OnChangeTourid()
{
    AllgLaengeKontr(&m_edit_TourId, L_SONDERTOUREN_TOURID,AeGetApp()->Modus());
    GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_INSERT)->EnableWindow();
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
}

void CDSonderTouren::OnButtonDelete()
{
    UpdateData();
    m_Touren.SetTourid(m_CTourId);
    m_Touren.SetFilialnr(GetVzNr());
    m_Touren.SetKdauftragart(m_CAArt);
    MsgBoxOK(m_Touren.Delete() == 0 ? IDP_DELETED : IDP_NOT_DELETED);
    GetPage();
}

void CDSonderTouren::OnButtonInsert()
{
    UpdateData();
    m_Touren.SetTourid(m_CTourId);
    if (m_CTourId.IsEmpty())
    {
        MsgBoxOK(IDP_NOT_INSERTED);
        return;
    }
    m_Touren.SetFilialnr(GetVzNr());
    m_Touren.SetKdauftragart(m_CAArt);
    MsgBoxOK(m_Touren.Insert() == 0 ? IDP_INSERTED : IDP_NOT_INSERTED);
    GetPage();
}

void CDSonderTouren::OnButtonUpdate()
{
    UpdateData();
    m_Touren.SetTourid(m_CTourId);
    m_Touren.SetFilialnr(GetVzNr());
    m_Touren.SetKdauftragart(m_CAArt);
    MsgBoxOK(m_Touren.Update() == 0 ? IDP_UPDATED : IDP_NOT_UPDATED);
    GetPage();
}

void CDSonderTouren::GetPage()
{
    CString str;
    ppString text;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_Touren.SetFilialnr(GetVzNr());
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_Touren.SelList() != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1] = m_Touren.GetTourid(text);
        s[2] = m_Touren.GetKdauftragart(text);

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
    m_Touren.CloseCursor();
    EndWaitCursor();
    GetWerte();
}

void CDSonderTouren::OnClickList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    GetWerte();
    *pResult = 0L;
}

void CDSonderTouren::GetWerte()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_CAArt = m_ListCtl.GetItemText(pos, 2);
        m_CTourId = m_ListCtl.GetItemText(pos, 1);
    }
    UpdateData(FALSE);
    GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow();
    GetDlgItem(IDC_BUTTON_INSERT)->EnableWindow();
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow();
}

void CDSonderTouren::OnItemchangedList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    GetWerte();

    *pResult = 0L;
}

// DAeMailUser.cpp : implementation file
//

#include "stdafx.h"
#include <mailsystem.h>
#include "DAeMailUser.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 300, LVCFMT_LEFT,
    2,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDAeMailUser dialog


CDAeMailUser::CDAeMailUser(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeMailUser::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_GRUPPE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
}


void CDAeMailUser::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDAeMailUser, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAeMailUser message handlers

BOOL CDAeMailUser::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    GetPage();

    return FALSE;
    //return TRUE;  // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDAeMailUser::GetPage( int /*nKzUpDown*/ )
{
    //Variablen
    ppString name;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    m_ListCtl.DeleteAllItems();
    m_mg.SetGroupno(AeGetApp()->VzNr()); //Zweckentfremdet für Filialnr, da im View nicht vorhanden
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0;; i++)
    {
        if (AeGetApp()->IsMailVzEigen()) m_mg.SelMailGroupVz();
        else m_mg.SelMailGroup();
        if (m_mg.rc != SRV_OK)
            break;
        s[0] = kb.Next();
        m_mg.GetGroupname(name);
        s[1] = name.c_str();
        s[2].Format("%d", m_mg.GetGroupno());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    } //Ende der for()-Schleife
    m_mg.CloseCursor();
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return TRUE;
}

void CDAeMailUser::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDAeMailUser::OnOK()
{
    CDialogMultiLang::OnOK();
}

void CDAeMailUser::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDAeMailUserUpd dlgAeMailUserUpd;
        dlgAeMailUserUpd.m_CGroupNo = m_ListCtl.GetItemText(pos, 2);
        dlgAeMailUserUpd.m_CGroupName = m_ListCtl.GetItemText(pos, 1);
        if (dlgAeMailUserUpd.DoModal() == IDOK)
            GetPage();
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDAeMailUser::OnHookFkt( WPARAM /*wParam*/, LPARAM /*lpMsg*/ )
{
    return 0;
}

void CDAeMailUser::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDAeMailUser::OnButtonDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_mg.SetGroupno(atol(m_ListCtl.GetItemText(pos, 2)));
        m_mg.DeleteMailGroup();
        if (m_mg.rc == SRV_OK)
            GetPage();
    }
}

void CDAeMailUser::OnButtonNew()
{
    CDAeMailUserUpd dlgAeMailUserUpd;
    if (dlgAeMailUserUpd.DoModal() == IDOK)
        GetPage();
}

void CDAeMailUser::OnButtonUpdate()
{
    SelectEintrag();
}

void CDAeMailUser::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

/////////////////////////////////////////////////////////////////////////////
// CDAeMailUserUpd dialog

//Definition der Tabellenbreite und der Ueberschriften

static COLUMNS_TYPES Columns1[] =
{
    0,  "", 80, LVCFMT_LEFT,
    1,  "", 30, LVCFMT_LEFT,
    2,  "",  0, LVCFMT_LEFT,
    -1, "",  0, 0
};


CDAeMailUserUpd::CDAeMailUserUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeMailUserUpd::IDD, pParent)
{
    m_CGroupName = _T("");

    Columns1[0].Columns = CResString::ex().getStrTblText(IDS_ANWENDER);
    Columns1[1].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    Columns1[2].Columns = CResString::ex().getStrTblText(AETXT_KURZ_TOUR_ID);
}


void CDAeMailUserUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST2, m_List2);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Control(pDX, IDC_EDIT_GROUP_NAME, m_edit_GroupName);
    DDX_Text(pDX, IDC_EDIT_GROUP_NAME, m_CGroupName);
}


BEGIN_MESSAGE_MAP(CDAeMailUserUpd, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEF, OnButtonDef)
    ON_BN_CLICKED(IDC_BUTTON_UNDEF, OnButtonUndef)
    ON_EN_CHANGE(IDC_EDIT_GROUP_NAME, OnChangeEditGroupName)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAeMailUserUpd message handlers

BOOL CDAeMailUserUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CString anwender;
    long lGroupno;
    ppString hilfe;
    //Variablen
    ppString name;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    // Add the columns.
    if (   !CListCtrlHelper::AddColumns(Columns1, m_List1)
        || !CListCtrlHelper::AddColumns(Columns1, m_List2) )
    {
        return FALSE;
    }

    //Anfangsinitialisierung durchfuehren
    m_List1.DeleteAllItems();
    m_List2.DeleteAllItems();
    BeginWaitCursor();
    lGroupno = (atol(m_CGroupNo));
    m_mdef.SetGroupno(lGroupno);
    m_mdef.SetFilialnr(AeGetApp()->VzNr());
    for (;;)
    {
        if (AeGetApp()->IsMailVzEigen())
            m_mdef.SelAllUserVz();
        else
            m_mdef.SelAllUser();
        if (m_mdef.rc != SRV_OK)
            break;
        m_mdef.GetUsername(name);
        s[0] = name.c_str();
        s[1].Format("%d", m_mdef.GetFilialnr());
        s[2].Format("%ld", m_mdef.GetUid());
        CListCtrl& listCtrl = (m_mdef.GetGroupno() != lGroupno) || (lGroupno == 0) ? m_List2 : m_List1;

        if (!CListCtrlHelper::AppendItem(listCtrl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    } //Ende der for()-Schleife
    m_mdef.CloseCursor();
    EndWaitCursor();
    if (m_List1.GetItemCount() == 0)
    {
        GetDlgItem(IDC_BUTTON_UNDEF)->EnableWindow(FALSE);
    }
    if (m_List2.GetItemCount() == 0)
    {
        GetDlgItem(IDC_BUTTON_DEF)->EnableWindow(FALSE);
        GotoDlgCtrl(GetDlgItem(IDC_LIST1));
        CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);
    }
    else
    {
        GotoDlgCtrl(GetDlgItem(IDC_LIST2));
        CListCtrlHelper::SetItemStateSelectedFocused(m_List2, 0);
    }

    return FALSE;
    //return TRUE;  // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAeMailUserUpd::OnButtonDef()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    int pos2 = m_List2.GetNextItem(-1, LVNI_SELECTED);
    if (pos2 < 0) return;
    s[2] = m_List2.GetItemText(pos2, 2);
    s[1] = m_List2.GetItemText(pos2, 1);
    s[0] = m_List2.GetItemText(pos2, 0);

    if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
    {
        return;
    }

    m_List2.DeleteItem(pos2);
    if (m_List2.GetItemCount() == 0)
    {
        GetDlgItem(IDC_BUTTON_DEF)->EnableWindow(FALSE);
        GotoDlgCtrl(GetDlgItem(IDC_LIST1));
        CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);
    }
    else
    {
        if (pos2 > m_List2.GetItemCount() - 1) pos2--;
        GotoDlgCtrl(GetDlgItem(IDC_LIST2));
        CListCtrlHelper::SetItemStateSelectedFocused(m_List2, pos2);
    }
    GetDlgItem(IDC_BUTTON_UNDEF)->EnableWindow();
}

void CDAeMailUserUpd::OnButtonUndef()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    int pos1 = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos1 < 0) return;
    s[2] = m_List1.GetItemText(pos1, 2);
    s[1] = m_List1.GetItemText(pos1, 1);
    s[0] = m_List1.GetItemText(pos1, 0);

    if (!CListCtrlHelper::AppendItem(m_List2, NUM_COLUMNS, s))
    {
        return;
    }

    m_List1.DeleteItem(pos1);
    if (m_List1.GetItemCount() == 0)
    {
        GetDlgItem(IDC_BUTTON_UNDEF)->EnableWindow(FALSE);
        GotoDlgCtrl(GetDlgItem(IDC_LIST2));
        CListCtrlHelper::SetItemStateSelectedFocused(m_List2, 0);
    }
    else
    {
        if (pos1 > m_List1.GetItemCount() - 1) pos1--;
        GotoDlgCtrl(GetDlgItem(IDC_LIST1));
        CListCtrlHelper::SetItemStateSelectedFocused(m_List1, pos1);
    }
    GetDlgItem(IDC_BUTTON_DEF)->EnableWindow();
}

void CDAeMailUserUpd::OnChangeEditGroupName()
{
    AllgLaengeKontr(&m_edit_GroupName, L_MAILGROUP_GROUPNAME,AeGetApp()->Modus());
}

void CDAeMailUserUpd::OnOK()
{
    UpdateData();
    int pos1;
    long groupno;
    if (m_CGroupName.IsEmpty())
    {
        MsgBoxOK(IDP_MAIL_GOUP_NAME);
        m_edit_GroupName.SetFocus();
        m_edit_GroupName.SetSel(0, -1, FALSE);
        return;
    }
    m_mgroup.SetGroupname(m_CGroupName);
    if (m_CGroupNo.IsEmpty()) // neue Gruppe
    {
        m_mgroup.Insert();
        if (m_mgroup.rc != SRV_OK)
            return;

        m_CGroupNo.Format("%ld",m_mgroup.GetGroupno());
    }
    else
    {
        m_mgroup.SetGroupno(atol(m_CGroupNo));
        m_mgroup.UpdateMailGroup();
        if (m_mgroup.rc != SRV_OK)
            return;
    }
    groupno = atol(m_CGroupNo);
    m_muser.SetGroupno(groupno);
    m_muser.SetFilialnr(AeGetApp()->VzNr());
    if (AeGetApp()->IsMailVzEigen())
        m_muser.DeleteAllVz();
    else
        m_muser.DeleteAll();
    for (pos1 = 0; pos1 < m_List1.GetItemCount(); pos1++)
    {
        m_muser.SetGroupno(groupno);
        m_muser.SetUid(atol(m_List1.GetItemText(pos1, 2)));
        m_muser.SetFilialnr(static_cast<short>(atoi(m_List1.GetItemText(pos1, 1))));
        m_muser.Insert();
    }
    CDialogMultiLang::OnOK();
}

void CDAeMailUserUpd::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnButtonUndef();

    *pResult = 0L;
}

void CDAeMailUserUpd::OnDblclkList2(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnButtonDef();

    *pResult = 0L;
}

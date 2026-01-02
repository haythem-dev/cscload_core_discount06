//---------------------------------------------------------------------------------------------//
// DAeCollOrderGrp.cpp : Implementierungsdatei
//---------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------//
// include section
//---------------------------------------------------------------------------------------------//
#include "stdafx.h"
#include "DAeSammelAuft.h"
#include "DAeCollOrderGrp.h"
#include <collectivorders.h>
#include <sstream>
#include <iomanip>
#include "CustomerGroups.h"
#include "DSammelKnd.h"

//---------------------------------------------------------------------------------------------//
// static initialization section
//---------------------------------------------------------------------------------------------//
COLUMNS_TYPES CDAeCollOrderGrp::Columns[] =
{
    0,  "",  40, LVCFMT_LEFT,
    1,  "",  60, LVCFMT_RIGHT,
    2,  "", 140, LVCFMT_LEFT,
    3,  "", 140, LVCFMT_LEFT,
    -1, "",   0, 0
};

//---------------------------------------------------------------------------------------------//
// c'tor
//---------------------------------------------------------------------------------------------//
IMPLEMENT_DYNAMIC(CDAeCollOrderGrp, CDialog)

CDAeCollOrderGrp::CDAeCollOrderGrp(CWnd* pParent /*=NULL*/)
: CDialogMultiLang(CDAeCollOrderGrp::IDD, pParent), m_pCDAeSammelAuft( 0 )
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ORT);
}

//---------------------------------------------------------------------------------------------//
// d'tor
//---------------------------------------------------------------------------------------------//
CDAeCollOrderGrp::~CDAeCollOrderGrp()
{
}

//---------------------------------------------------------------------------------------------//
// DoDataExchange
//---------------------------------------------------------------------------------------------//
void CDAeCollOrderGrp::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CBO_EXISTING_CUSTGRPS, m_Combo_KundenGruppe);
    DDX_Control(pDX, IDC_LIST_ADMIN_CUSTOMER, m_lstNewCustomers);
    DDX_Control(pDX, IDC_ED_NEW_CUSTGRP, m_edNewCustGrp);
    DDX_Control(pDX, IDC_LIST_ADMIN_CUSTOMER, m_lstNewCustomers);
}

//---------------------------------------------------------------------------------------------//
// MESSAGE MAP
//---------------------------------------------------------------------------------------------//
BEGIN_MESSAGE_MAP(CDAeCollOrderGrp, CDialogMultiLang)
    ON_BN_CLICKED(ID_BT_SAVE, OnBnClickedBtSave)
    ON_BN_CLICKED(ID_BT_DELETE, OnBnClickedBtDelete)
    ON_BN_CLICKED(ID_BT_CANCEL, OnBnClickedBtCancel)
    ON_CBN_SELCHANGE(IDC_CBO_EXISTING_CUSTGRPS, OnCbnSelchangeCboExistingCustgrps)
    ON_BN_CLICKED(IDC_BT_NEW_CUSTOMER, OnBnClickedBtNewCustomer)
    ON_BN_CLICKED(IDC_BT_DELETE_COMPLETE, OnBnClickedBtDeleteComplete)
    ON_BN_CLICKED(IDC_BT_NEWLOAD, OnBnClickedBtNewload)
    ON_CBN_EDITCHANGE(IDC_CBO_EXISTING_CUSTGRPS, OnCbnEditchangeCboExistingCustgrps)
END_MESSAGE_MAP()

//---------------------------------------------------------------------------------------------//
// OnInitDialog()
//---------------------------------------------------------------------------------------------//
BOOL CDAeCollOrderGrp::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    m_edNewCustGrp.SetLimitText(30);
    m_Combo_KundenGruppe.LimitText(30);

    GetDlgItem(IDC_FR_NEW_CUSTGRP)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_ST_NEW_CUSTGRP)->ShowWindow(SW_HIDE);
    m_edNewCustGrp.ShowWindow(SW_HIDE);

    // add the columns to the listctrl
    if (!CListCtrlHelper::AddColumns(CDAeCollOrderGrp::Columns, m_lstNewCustomers))
    {
        return FALSE;
    }

    // loads all dc specific customer groups for collective orders
    if (NULL != m_pCDAeSammelAuft)
    {
        m_pCDAeSammelAuft->showCollOrderGrp(&m_Combo_KundenGruppe, true);
    }
    DWORD dwOldBits = m_lstNewCustomers.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_lstNewCustomers.SetExtendedStyle(dwOldBits);

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_AKTIV);
    idResources.push_back(IDI_ICON_NO);
    CListCtrlHelper::CreateAndSetImageList(m_lstNewCustomers, m_ImageSmall, idResources);

    m_Combo_KundenGruppe.SetFocus();

    // switch on/off the right to create customer groups for collective orders
    const BOOL IsAdminCustGrps = GetAeUser().IsAdminCustGrps();

    GetDlgItem(IDC_CBO_EXISTING_CUSTGRPS)->EnableWindow(IsAdminCustGrps);
    GetDlgItem(IDC_ED_NEW_CUSTGRP)->EnableWindow(IsAdminCustGrps);
    GetDlgItem(IDC_LIST_ADMIN_CUSTOMER)->EnableWindow(IsAdminCustGrps);
    GetDlgItem(ID_BT_DELETE)->EnableWindow(IsAdminCustGrps);
    GetDlgItem(IDC_BT_NEWLOAD)->EnableWindow(IsAdminCustGrps);
    GetDlgItem(IDC_BT_NEW_CUSTOMER)->EnableWindow(IsAdminCustGrps);
    GetDlgItem(ID_BT_SAVE)->EnableWindow(IsAdminCustGrps);
    GetDlgItem(IDC_BT_DELETE_COMPLETE)->EnableWindow(IsAdminCustGrps);
    GetDlgItem(ID_BT_CANCEL)->EnableWindow(IsAdminCustGrps);

    if (!IsAdminCustGrps)
    {
        MsgBoxOK(AETXT_NORIGHT4CUSTGRPADMIN);
    }

    m_Combo_KundenGruppe.SetCurSel(m_idx);
    OnCbnSelchangeCboExistingCustgrps();

    return FALSE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

//---------------------------------------------------------------------------------------------//
// existsGroup()
//---------------------------------------------------------------------------------------------//
int CDAeCollOrderGrp::existsGroup(const CString& str)
{
    return m_Combo_KundenGruppe.FindStringExact(0, str);
}

//---------------------------------------------------------------------------------------------//
// OnBnClickedBtDelete()
//---------------------------------------------------------------------------------------------//
void CDAeCollOrderGrp::OnBnClickedBtDelete()
{
    int pos = m_lstNewCustomers.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        int iKb = atoi(m_lstNewCustomers.GetItemText(pos, 0));
        m_lstNewCustomers.DeleteItem(pos);
        int max = m_lstNewCustomers.GetItemCount();
        for (; pos < max; pos++)
        {
            CString cKb;
            cKb.Format("%d", iKb);
            m_lstNewCustomers.SetItemText(pos, 0, cKb);
            ++iKb;
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

//---------------------------------------------------------------------------------------------//
// OnBnClickedBtCancel()
//---------------------------------------------------------------------------------------------//
bool CDAeCollOrderGrp::hasToBeSaved()
{
    bool save = false;
    CString strWnd;
    m_Combo_KundenGruppe.GetWindowText(strWnd);
    if (!strWnd.IsEmpty())
    {
        // check if the customer group exists standing in the combo box right now!
        ppString ppStr = strWnd;
        const long GrpID = CustomerGroups::Ex()->findOutGrpID(ppStr);
        if (0 > GrpID)
        {
            // check if there is at least one customer assigned to the new group
            if (1 <= m_lstNewCustomers.GetItemCount())
            {
                if (IDYES == MsgBoxYesNo(AETXT_CHANGES_SAVE_CUSTGRP))
                {
                    // the new customer group has to be saved
                    save = true;
                }
            }
        }
    }

    return save;
}

//---------------------------------------------------------------------------------------------//
// OnBnClickedBtCancel()
//---------------------------------------------------------------------------------------------//
void CDAeCollOrderGrp::OnBnClickedBtCancel()
{
    if (hasToBeSaved())
    {
        OnBnClickedBtSave();
    }
    CDialogMultiLang::OnOK();
}

//---------------------------------------------------------------------------------------------//
// OnBnClickedBtNewCustomer()
//---------------------------------------------------------------------------------------------//
void CDAeCollOrderGrp::OnBnClickedBtNewCustomer()
{
    CDSammelKnd knd;
    knd.m_Title = CResString::ex().getStrTblText(AETXT_CUST_4_CUSTGRP);
    knd.m_pListCtl = &m_lstNewCustomers;
    knd.m_sListCount = NUM_COLUMNS;
    knd.m_EnableAeGesperrt = true;
    knd.DoModal();

    if (m_lstNewCustomers.GetItemCount() > 0)
    {
        CListCtrlHelper::SetFocusSelectedFocused(m_lstNewCustomers, m_lstNewCustomers.GetItemCount() - 1);
    }
}

//---------------------------------------------------------------------------------------------//
// OnBnClickedBtDeleteComplete()
//---------------------------------------------------------------------------------------------//
void CDAeCollOrderGrp::OnBnClickedBtDeleteComplete()
{
    CString str;
    if (MsgBoxYesNo(IDP_LOESCHEN_JA) != IDYES)
        return;
    m_Combo_KundenGruppe.GetWindowText(str);
    if (str.IsEmpty())
        return;

    ppString ppStr = str;
    CustomerGroups::Ex()->setGroupName(ppStr);
    if (!CustomerGroups::Ex()->erase())
    {
        MsgBoxOK(CustomerGroups::Ex()->strError.c_str());
        return;
    }

    m_Combo_KundenGruppe.SetCurSel(0);
    newLoad();
    OnCbnSelchangeCboExistingCustgrps();
}

//---------------------------------------------------------------------------------------------//
// OnBnClickedBtSave()
//---------------------------------------------------------------------------------------------//
void CDAeCollOrderGrp::OnBnClickedBtSave()
{
    CString str;
    m_Combo_KundenGruppe.GetWindowText(str);
    const CString strComp = "[" + CResString::ex().getStrTblText( AETXT_BITTE_AUSWAEHLEN ) + "]";
    if (str.IsEmpty() || str == strComp)
    {
        MsgBoxOK(AETXT_NO_OR_NO_VALID_CUSTGRPSTATED);
        return;
    }

    ppString ppStr = str;
    CustomerGroups::Ex()->setGroupName(ppStr);
    // all members (customers) have to be picked
    vector<long> custNos;
    const int cnt = m_lstNewCustomers.GetItemCount();

    for (int i = 0; i < cnt; ++i)
    {
        custNos.push_back(atol(m_lstNewCustomers.GetItemText(i, 1)));
    }
    CustomerGroups::Ex()->setMembers(custNos);

    if (!CustomerGroups::Ex()->save())
    {
        MsgBoxOK(CustomerGroups::Ex()->strError.c_str());
        m_Combo_KundenGruppe.SetFocus();
        return;
    }

    newLoad();

    int i = existsGroup(str);
    if (0 <= i)
    {
        m_Combo_KundenGruppe.SetCurSel(i);
        OnCbnSelchangeCboExistingCustgrps();
    }
    else
    {
        m_Combo_KundenGruppe.SetCurSel(0);
    }
}

//---------------------------------------------------------------------------------------------//
// newLoad()
//---------------------------------------------------------------------------------------------//
void CDAeCollOrderGrp::newLoad()
{
    // buffer the currently selected customer group to display this group after loading newly
    CString strWnd;
    m_Combo_KundenGruppe.GetWindowText(strWnd);

    // loads all dc specific customer groups for collective orders
    m_edNewCustGrp.SetWindowText("");
    m_lstNewCustomers.DeleteAllItems();
    if (0 != m_pCDAeSammelAuft)
    {
        m_pCDAeSammelAuft->showCollOrderGrp(&m_Combo_KundenGruppe, true);
    }

    // display the last selected customer group
    m_Combo_KundenGruppe.SelectString(0, strWnd);
    OnCbnSelchangeCboExistingCustgrps();
    m_Combo_KundenGruppe.SetFocus();
}

//---------------------------------------------------------------------------------------------//
// OnBnClickedBtnewLoad()
//---------------------------------------------------------------------------------------------//
void CDAeCollOrderGrp::OnBnClickedBtNewload()
{
    if (hasToBeSaved())
    {
        OnBnClickedBtSave();
    }
    newLoad();
}

//---------------------------------------------------------------------------------------------//
// OnCbnEditchangeCboExistingCustgrps()
//---------------------------------------------------------------------------------------------//
void CDAeCollOrderGrp::OnCbnEditchangeCboExistingCustgrps()
{
    CString str;
    m_Combo_KundenGruppe.GetWindowText(str);
    if (str.IsEmpty())
        return;

    char c = str[str.GetLength() - 1];
    if (!(c == ' ' || '0' <= c && c <= '9' || AeGetApp()->Letter_a() <= c && c <= AeGetApp()->Letter_z() || AeGetApp()->Letter_A() <= c && c <= AeGetApp()->Letter_Z()))
    {
        m_Combo_KundenGruppe.SetWindowText(str.Mid(0, str.GetLength()));
    }

    int idx = existsGroup(str);
    if (0 > idx)
    {
        m_lstNewCustomers.DeleteAllItems();
    }
    else
    {
        m_Combo_KundenGruppe.SetCurSel(idx);
        OnCbnSelchangeCboExistingCustgrps();
    }
    m_Combo_KundenGruppe.SetEditSel(-1, 0);
}

//---------------------------------------------------------------------------------------------//
// OnCbnSelchangeCboExistingCustgrps()
//---------------------------------------------------------------------------------------------//
void CDAeCollOrderGrp::OnCbnSelchangeCboExistingCustgrps()
{
    // 1. first store the newly selected index
    m_idx = m_Combo_KundenGruppe.GetCurSel();
    if (m_idx == CB_ERR)
        return;

    CString strWnd;
    m_Combo_KundenGruppe.GetLBText(m_idx, strWnd);

    // 2. perhaps something to save, namely the 'old' string standing in the combobox before changing.
    if (hasToBeSaved())
    {
        OnBnClickedBtSave();
    }

    m_lstNewCustomers.DeleteAllItems();
    const CString strComp = "[" + CResString::ex().getStrTblText( AETXT_BITTE_AUSWAEHLEN ) + "]";
    if (strComp == strWnd)
    {
        // if the first entry representing no real customer group is selected,
        // no customer group members have to be displayed.
        m_Combo_KundenGruppe.SetCurSel(m_Combo_KundenGruppe.FindString(0, strWnd));
        m_Combo_KundenGruppe.SetWindowText(strWnd);
        return;
    }

    LV_ITEM _item;
    _item.mask = LVIF_IMAGE;
    _item.iSubItem = 0;

    m_Combo_KundenGruppe.SetCurSel(m_Combo_KundenGruppe.FindString(0, strWnd));
    m_Combo_KundenGruppe.SetWindowText(strWnd);
    m_idx = m_Combo_KundenGruppe.GetCurSel();

    int iKb = 1;
    ppString str2;
    const int grpID = m_Combo_KundenGruppe.GetItemData(m_idx);

    CustomerGroups::T_MEMBERS::iterator it = CustomerGroups::Ex()->getMembers(m_Combo_KundenGruppe.GetItemData(m_idx)).begin();
    for (int i = 0; it != CustomerGroups::Ex()->getMembers(grpID).end(); ++it, ++i, ++iKb)
    {
        str2.format("%d", iKb);
        _item.iItem = i;
        m_lstNewCustomers.InsertItem(i, str2.c_str(), it->SKDKUNDEAEGESPERRT[0] - '0');
        str2.format("%ld", it->IDFNR);
        m_lstNewCustomers.SetItemText(i, 1, str2.c_str());
        m_lstNewCustomers.SetItemText(i, 2, it->NAMEAPO);
        m_lstNewCustomers.SetItemText(i, 3, it->ORT);
    }
}

//---------------------------------------------------------------------------------------------//
// PreTranslateMessage( MSG* pMsg )
//---------------------------------------------------------------------------------------------//
BOOL CDAeCollOrderGrp::PreTranslateMessage(MSG* pMsg)
{
    if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
    {
        CWnd* wnd = GetFocus();
        //  Focus blinking in the combo box
        CComboBox* p = (CComboBox*)GetDlgItem(IDC_CBO_EXISTING_CUSTGRPS);

        if (wnd->GetParent() == p)
        {
            CString strWnd;
            p->GetWindowText(strWnd);
            const CString strComp = "[" + CResString::ex().getStrTblText(AETXT_BITTE_AUSWAEHLEN) + "]";
            if (strComp != strWnd)
            {
                OnBnClickedBtNewCustomer();
            }
            return true;
        }

        if (wnd == GetDlgItem(IDC_LIST_ADMIN_CUSTOMER))
        {
            if (IDYES == MsgBoxYesNo(AETXT_CHANGES_SAVE_CUSTGRP))
            {
                OnBnClickedBtSave();
            }
            return true;
        }
    }

    //  be a good citizen - call the base class
    return CDialogMultiLang::PreTranslateMessage(pMsg);
}

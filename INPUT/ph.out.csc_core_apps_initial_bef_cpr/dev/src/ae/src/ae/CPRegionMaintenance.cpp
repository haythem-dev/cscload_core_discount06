
//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPRegionMaintenance.cpp
   Author: A.Schmidt-Rehschuh
   made  : 29.08.2000

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "CPRegionMaintenance.h"
#include "ppSaleCenter.h"
#include "DKontrPwd.h"

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_LEFT,
    1,  "",  50, LVCFMT_CENTER,
    2,  "", 170, LVCFMT_CENTER,
    -1, "",   0, 0
};

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CCPRegionMaintenance::CCPRegionMaintenance(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CCPRegionMaintenance::IDD, pParent), CPageBrowser(0)
{
    m_bCursorOpen = true;
    m_bIsNotfound = true;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KB);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TEIL_NR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNER);
}

//--- DoDataExchange ---------------------------------------------------------//

void CCPRegionMaintenance::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_REGION, m_ListCtl);
    DDX_Control(pDX, IDC_COMBO_REGIONPARTNO, m_CComboBoxRegionPartNo);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CCPRegionMaintenance, CDialogMultiLang)
    ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
    ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
    ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_REGION, OnKeydownListRegion)
    ON_NOTIFY(NM_CLICK, IDC_LIST_REGION, OnClickListRegion)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CCPRegionMaintenance message handlers (ClassWizard) --------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CCPRegionMaintenance::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    if (!CheckPassword())
    {
        CDialogMultiLang::EndDialog(0);
        return TRUE;
    }
    else if (!SetListHeader())
    {
        CDialogMultiLang::OnCancel();
        return FALSE;
    }

    FillComboBox();
    CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
    CString csBuf;
    csBuf.Format("%d", AeGetApp()->FilialNr());
    GetDlgItem(IDC_EDIT_REGIONNO)->SetWindowText(csBuf);
    GetDlgItem(IDC_EDIT_REGIONNO)->EnableWindow(FALSE);
    GetData(); //get data currently
    return TRUE;
}

//--- (ClassWizard)OnRadio1 --------------------------------------------------//

void CCPRegionMaintenance::OnRadio1()
{
    CString csBuf;
    csBuf = CResString::ex().getStrTblText(ID_REGION_SALECENTER);
    SetWindowText(csBuf);
    GetData();
}

//--- (ClassWizard)OnRadio2 --------------------------------------------------//

void CCPRegionMaintenance::OnRadio2()
{
    CString csBuf;
    csBuf = CResString::ex().getStrTblText(ID_REGION_KSC);
    SetWindowText(csBuf);
    GetData();
}

//--- (ClassWizard)OnRadio3 --------------------------------------------------//

void CCPRegionMaintenance::OnRadio3()
{
    CString csBuf;
    csBuf = CResString::ex().getStrTblText(ID_REGION_DEVICE);
    SetWindowText(csBuf);
    GetData();
}

//--- (ClassWizard)OnButtonNew -----------------------------------------------//

void CCPRegionMaintenance::OnButtonNew()
{
    CString csBuf;
    GetDlgItem(IDC_COMBO_REGIONPARTNO)->GetWindowText(csBuf);
    if (atoi(csBuf) == 0)
    {
       MsgBoxOK(IDP_REGION_REGIONNO);
       GotoDlgCtrl(GetDlgItem(IDC_COMBO_REGIONPARTNO));
       return;
    }

    m_Region.SetRegionTeilNr(static_cast<short>(atoi(csBuf)) );
    if (!m_Region.Insert())
    {
        MsgBoxOK(m_Region.GetErrorMsg());
        return;
    }

    GetData();
    return;
}

//--- (ClassWizard)OnButtonDelete --------------------------------------------//

void CCPRegionMaintenance::OnButtonDelete()
{
    if (GetPosition())
    {
        if (m_Region.GetRegionTeilNr() == m_Region.GetRegionNr())
        {
            MsgBoxOK(IDP_REGION_NO_DELETE);
            return;
        }
        else if (!m_Region.Delete())
        {
            MsgBoxOK(m_Region.GetErrorMsg());
            return;
        }
        m_ListCtl.DeleteItem(m_iPos);
    }
}

//--- (ClassWizard)OnKeydownListRegion ---------------------------------------//

void CCPRegionMaintenance::OnKeydownListRegion(NMHDR* pNMHDR, LRESULT* pResult)
{
    int pos;
    OnKeydownList(pNMHDR, pResult, m_ListCtl, pos);

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (pLVKeyDow->wVKey == VK_DOWN)
    {
        CListCtrlHelper::StepDownLinePosition(pos, m_Region.GetCountPerPage());
    }
    else if (pLVKeyDow->wVKey == VK_UP)
    {
        --pos;
    }

    if (pos >= 0)
    {
        if (!m_Region.SetElement(pos))
        {
            return;
        }
        SetComboData();
    }
}

//--- (ClassWizard)OnClickListRegion -----------------------------------------//

void CCPRegionMaintenance::OnClickListRegion(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    if (GetPosition(false))
        SetComboData();

    *pResult = 0L;
}

//----------------------------------------------------------------------------//
//--- private methodes -------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- FillComboBox -----------------------------------------------------------//

void CCPRegionMaintenance::FillComboBox()
{
    ppSaleCenter SaleCenter;
    SaleCenter.SetCountPerPage(MAXIMUM_FILIALNR);
    if (SaleCenter.StartBrowse())
    {
        CString csBuf;
        SaleCenter.SetNextPage();
        while (SaleCenter.GetNext())
        {
            csBuf.Format("%02d %s", SaleCenter.GetFilialNr(), SaleCenter.GetName());
            m_CComboBoxRegionPartNo.AddString(csBuf);
        }
        m_CComboBoxRegionPartNo.AddString(" ");
    }
}

//---- SetListHeader --------------------------------------------------------//

bool CCPRegionMaintenance::SetListHeader()
{
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return false;
    }

    m_nColumnsCount = 3;
    m_Region.SetCountPerPage(m_ListCtl.GetCountPerPage());
    return true;
}

//---- GetPage --------------------------------------------------------------//

bool CCPRegionMaintenance::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    if (nKzUpDown == PRIOR_PG)
    {
        if (!m_Region.SetPreviousPage())
            return false;
    }
    else if (!m_Region.SetNextPage())
        return false;

    m_ListCtl.DeleteAllItems();
    while (m_Region.GetNext())
    {
        if (!SetValueIntoList())
        {
            EndWaitCursor();
            return false;
        }
    }
    if (m_ListCtl.GetItemCount() > 0)
    {
        CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
        m_Region.SetElement(0);
        GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(TRUE);
        GotoDlgCtrl(GetDlgItem(IDC_LIST_REGION));
        m_bIsNotfound = false;
    }
    else
    {
        m_bIsNotfound = true;
        GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
    }
    SetComboData();
    return true;
}

//---- GetPosition -----------------------------------------------------------//

bool CCPRegionMaintenance::GetPosition(const bool bShowErrorMsg)
{
    if (m_ListCtl.GetItemCount() == 0)
    {
       m_iPos = 0;
       return true;
    }
    else if ((m_iPos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED)) >= 0)
    {
        if (!m_Region.SetElement(m_iPos))
        {
            if (bShowErrorMsg)
                MsgBoxOK(m_Region.GetErrorMsg());
          return false;
       }
       return true;
    }
    return false;
}

//---- SetValueIntoList ------------------------------------------------------//

bool CCPRegionMaintenance::SetValueIntoList(const char& chSelector)
{
    CStringArray s;
    s.SetSize(m_nColumnsCount);
    int index = m_ListCtl.GetItemCount();

    s[0].Format("%c", chSelector + index);
    s[1].Format("%d", m_Region.GetRegionTeilNr());
    s[2].Format("%s", m_Region.GetName());

    if (!CListCtrlHelper::InsertItem(m_ListCtl, m_nColumnsCount, s, index))
    {
        return false;
    }
    m_ListCtl.SetFocus();
    return true;
}

//---- GetData ---------------------------------------------------------------//

void CCPRegionMaintenance::GetData()
{
    CString csBuf;

    GetDlgItem(IDC_EDIT_REGIONNO)->GetWindowText(csBuf);
    m_Region.SetRegionNr(static_cast<short>(atoi(csBuf)));

    switch (GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3))
    {
    case IDC_RADIO1:
        m_Region.SetRegionenTyp(ppRegion::r_salecenter);
        break;
    case IDC_RADIO2:
        m_Region.SetRegionenTyp(ppRegion::r_ksc);
        break;
    case IDC_RADIO3:
        m_Region.SetRegionenTyp(ppRegion::r_modem);
        break;
    default:
        return;
    }

    if (m_Region.StartBrowse())
        GetPage();
}

//--- CheckPassword ----------------------------------------------------------//

bool CCPRegionMaintenance::CheckPassword()
{
#ifndef _DEBUG
    CDKontrPwd dlgPassWord;
    CAeUser& currentAeUser = GetAeUser();

    dlgPassWord.m_Pwd = currentAeUser.GetPasswd();
    if (dlgPassWord.DoModal() != IDOK)
        return false;
#endif
    return true;
}

//--- SetComboData -----------------------------------------------------------//

void CCPRegionMaintenance::SetComboData()
{
    CString csBuf;
    if (m_bIsNotfound)
        csBuf = " ";
    else
       csBuf.Format( "%02d %s", m_Region.GetRegionTeilNr(), m_Region.GetName());
    m_CComboBoxRegionPartNo.SetCurSel(m_CComboBoxRegionPartNo.FindString(-1, csBuf));
}

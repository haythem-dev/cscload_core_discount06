
//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPPACallPlanDay.cpp
   Author: A.Schmidt-Rehschuh
   made  : 17.04.2000

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "CPPACallPlanDay.h"
#include "CPCallPlanChangeData.h"
#include "CPCallPlanMaintenance.h"

static COLUMNS_TYPES Columns[] =
{
    0,  "KB",          30, LVCFMT_LEFT,
    1,  "Rufzeit",     60, LVCFMT_LEFT,
    2,  "Protokoll",   90, LVCFMT_LEFT,
    3,  "Priorität",   70, LVCFMT_LEFT,
    4,  "PoolNr",      70, LVCFMT_LEFT,
    5,  "ModemPoolNr",  0, LVCFMT_LEFT,
    6,  "Einstellung", 80, LVCFMT_LEFT,
    7,  "Notdienst",   90, LVCFMT_LEFT,
    -1, "",             0, 0
};

void CCPPACallPlanDay::Initialize()
{
    if (m_bIsActive)
        m_ListCtl.DeleteAllItems();
}

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CCPPACallPlanDay::CCPPACallPlanDay(CCPCallPlanMaintenance* pWnd,
                                   const ppCustomerDisplay* pCustomer,
                                   const CPARAUFBEARB* psrvAufParameter,
                                   const ppDayType::t_day d)
    : CTabPage(IDD), CPageBrowser(0)
    , c_strTitle(ppDayType(d, 1).GetWeekDay())
    , m_CustomerPlan(pCustomer, ppDayType(d, 1))
{
    m_bIsActive = false;
    m_sSaleCenterNo = -1;
    m_lCustomerNo = -1;
    m_nColumnsCount = 0;
    m_pCustomer = pCustomer;
    m_iPos = 0;
    m_pParent = pWnd;
    m_eDay = d;
    m_psrvAufParameter = psrvAufParameter;
}

//--- DoDataExchange ---------------------------------------------------------//

void CCPPACallPlanDay::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_CALLPLANDAY, m_ListCtl);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CCPPACallPlanDay, CPropertyPage)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CALLPLANDAY, OnKeydownListCallplanday)
    ON_NOTIFY(NM_CLICK, IDC_LIST_CALLPLANDAY, OnClickListCallplanday)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CCPPACallPlanDay message handlers (ClassWizard) ------------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CCPPACallPlanDay::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    SetListHeader();
    return FALSE;
}

//--- (ClassWizard)OnSetActive -----------------------------------------------//

BOOL CCPPACallPlanDay::OnSetActive()
{
    //generell neu lesen (startbrowse/getpage)
    m_sSaleCenterNo = -1;
    m_lCustomerNo = -1;

    if (IsCustomerChanged())
    {
       m_CustomerPlan.StartBrowse();
       GetPage();
    }

    m_bIsActive = true;
    return CPropertyPage::OnSetActive();
}


//--- (ClassWizard)OnOK ------------------------------------------------------//

void CCPPACallPlanDay::OnOK()
{
}

//--- (ClassWizard)OnClickListCallplanday ------------------------------------//

void CCPPACallPlanDay::OnClickListCallplanday(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    if (GetPosition(false))
        SetButton();
    *pResult = 0L;
}

//--- (ClassWizard)OnKeydownListCallplanday ----------------------------------//

void CCPPACallPlanDay::OnKeydownListCallplanday(NMHDR* pNMHDR, LRESULT* pResult)
{
    int pos;
    if (OnKeydownList(pNMHDR, pResult, m_ListCtl, pos))
    {
        return;
    }

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (pLVKeyDow->wVKey == VK_DOWN)
    {
        CListCtrlHelper::StepDownLinePosition(pos, m_CustomerPlan.GetCountPerPage());
    }
    else if (pLVKeyDow->wVKey == VK_UP)
    {
        --pos;
    }

    if (pos >= 0)
    {
        if (!m_CustomerPlan.SetElement(pos))
        {
            return;
        }
        SetButton();
    }
}

//----------------------------------------------------------------------------//
//--- private methodes (overloaded to CTabPage) ------------------------------//
//----------------------------------------------------------------------------//

//--- GetTabTitle ------------------------------------------------------------//

LPCTSTR CCPPACallPlanDay::GetTabTitle()
{
    return _T(c_strTitle.c_str());
}

//--- UpdateServer ------------------------------------------------------------//

bool CCPPACallPlanDay::UpdateServer()
{
    if (!GetPosition())
    {
       return false;
    }

    CCPCallPlanChangeData dlgCallPlanChangeData(&m_CustomerPlan, m_eDay);
    dlgCallPlanChangeData.SetStockRunningTimeExpress(static_cast<short>(m_psrvAufParameter->s.DURCHLAUFEILBOTE));
    dlgCallPlanChangeData.SetStockRunningTime(static_cast<short>(m_psrvAufParameter->s.DURCHLAUFNORMAL));

    if (dlgCallPlanChangeData.DoModal() == IDOK)
    {
        UpdateIntoList();
        SetButton();
        GotoDlgCtrl(GetDlgItem(IDC_LIST_CALLPLANDAY));
        return true;
    }

    GotoDlgCtrl(GetDlgItem(IDC_LIST_CALLPLANDAY));
    return false;
}

//--- InsertServer ------------------------------------------------------------//

bool CCPPACallPlanDay::InsertServer()
{
    CCPCallPlanChangeData dlgCallPlanChangeData(&m_CustomerPlan, m_eDay);
    dlgCallPlanChangeData.SetStockRunningTimeExpress(static_cast<short>(m_psrvAufParameter->s.DURCHLAUFEILBOTE));
    dlgCallPlanChangeData.SetStockRunningTime(static_cast<short>(m_psrvAufParameter->s.DURCHLAUFNORMAL));
    dlgCallPlanChangeData.SetIsInsert();
    if (dlgCallPlanChangeData.DoModal() == IDOK)
    {
       SetValueIntoList();
       SetButton();
       SetFirstListPos();
       return true;
    }
    GotoDlgCtrl(GetDlgItem(IDC_LIST_CALLPLANDAY));
    return false;
}

//--- DeleteServer ------------------------------------------------------------//

bool CCPPACallPlanDay::DeleteServer()
{
    if (!GetPosition())
    {
       return false;
    }

    CCPCallPlanChangeData dlgCallPlanChangeData(&m_CustomerPlan, m_eDay);
    dlgCallPlanChangeData.SetStockRunningTimeExpress(static_cast<short>(m_psrvAufParameter->s.DURCHLAUFEILBOTE));
    dlgCallPlanChangeData.SetStockRunningTime(static_cast<short>(m_psrvAufParameter->s.DURCHLAUFNORMAL));
    dlgCallPlanChangeData.SetIsDelete();
    if (dlgCallPlanChangeData.DoModal() == IDOK)
    {
        //gelöschte Zeile aus Listbox entfernen, danach m_iPos reduzieren
        m_ListCtl.DeleteItem(m_iPos);
        --m_iPos;
        SetButton();
        SetFirstListPos();
        return true;
    }

    GotoDlgCtrl(GetDlgItem(IDC_LIST_CALLPLANDAY));
    return false;
}

//--- OtherServer ------------------------------------------------------------//

bool CCPPACallPlanDay::OtherServer()
{
    bool bReturn = false;

    if (!GetPosition())
    {
       return false;
    }

    CCPCallPlanChangeData dlgCallPlanChangeData(&m_CustomerPlan, m_eDay);
    dlgCallPlanChangeData.SetStockRunningTimeExpress(static_cast<short>(m_psrvAufParameter->s.DURCHLAUFEILBOTE));
    dlgCallPlanChangeData.SetStockRunningTime(static_cast<short>(m_psrvAufParameter->s.DURCHLAUFNORMAL));
    dlgCallPlanChangeData.SetIsDisable();
    if (dlgCallPlanChangeData.DoModal() == IDOK)
    {
       UpdateIntoList();
       bReturn = true;
    }

    SetButton();
    GotoDlgCtrl(GetDlgItem(IDC_LIST_CALLPLANDAY));
    return bReturn;
}

//--- OtherServer ------------------------------------------------------------//

const int CCPPACallPlanDay::GetCountItem() const
{
    return m_ListCtl.GetItemCount();
}


//----------------------------------------------------------------------------//
//--- private methodes -------------------------------------------------------//
//----------------------------------------------------------------------------//

//---- SetListHeader --------------------------------------------------------//

bool CCPPACallPlanDay::SetListHeader()
{
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return false;
    }
    m_nColumnsCount = 8;
    m_CustomerPlan.SetCountPerPage(m_ListCtl.GetCountPerPage());
    return true;
}

//---- GetPage --------------------------------------------------------------//

bool CCPPACallPlanDay::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    if (nKzUpDown == PRIOR_PG)
    {
        if (!m_CustomerPlan.SetPreviousPage())
            return false;
    }
    else if (!m_CustomerPlan.SetNextPage())
        return false;

    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    while (m_CustomerPlan.GetNext())
    {
        if (!SetValueIntoList())
        {
            EndWaitCursor();
            return false;
        }
    }
    EndWaitCursor();
    SetFirstListPos();
    SetButton();
    return true;
}

//---- SetValueIntoList ------------------------------------------------------//

bool CCPPACallPlanDay::SetValueIntoList(const char& chSelector)
{
    CStringArray s;
    s.SetSize(m_nColumnsCount);
    int index = m_ListCtl.GetItemCount();
    s[0].Format("%c",  chSelector + index);
    s[1].Format("%ld", m_CustomerPlan.GetUrRufzeit());
    s[2].Format("%s",  m_CustomerPlan.GetRufProtokollText());
    s[3].Format("%d",  m_CustomerPlan.GetRufSteuerung());
    s[4].Format("%ld", m_CustomerPlan.GetPoolNr());
    s[5].Format("%ld", m_CustomerPlan.GetModemPoolNr());
    s[6].Format("%c",  m_CustomerPlan.GetRufEinstellung() ? 'A' : 'M');
    s[7].Format("%s",  m_CustomerPlan.GetAnrufTyp());

    if (!CListCtrlHelper::AppendItem(m_ListCtl, m_nColumnsCount, s))
    {
        return false;
    }
    m_ListCtl.SetFocus();
    return true;
}

//--- IsCustomerChanged ------------------------------------------------------//

bool CCPPACallPlanDay::IsCustomerChanged()
{
    if ( m_pCustomer->GetKundenNr() == m_lCustomerNo &&
         m_pCustomer->GetVertriebsZentrumNr() == m_sSaleCenterNo )
        return false;

   m_lCustomerNo = m_pCustomer->GetKundenNr();
   m_sSaleCenterNo = m_pCustomer->GetVertriebsZentrumNr();
   return true;
}

//---- GetPosition -----------------------------------------------------------//

bool CCPPACallPlanDay::GetPosition(const bool bWithMsg)
{
    m_iPos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (m_iPos >= 0)
    {
        if (!m_CustomerPlan.SetElement(m_iPos))
        {
            if (bWithMsg)
                AfxMessageBox(m_CustomerPlan.GetErrorMsg());
            return false;
        }
        return true;
    }
    return false;
}

//---- MakeEditable ----------------------------------------------------------//

void CCPPACallPlanDay::MakeEditable()
{
}

//---- UpdateIntoList --------------------------------------------------------//

void CCPPACallPlanDay::UpdateIntoList()
{
    CStringArray s;
    s.SetSize(m_nColumnsCount);

    s[1].Format( "%ld", m_CustomerPlan.GetUrRufzeit() );
    s[2].Format( "%s",  m_CustomerPlan.GetRufProtokollText() );
    s[3].Format( "%d",  m_CustomerPlan.GetRufSteuerung() );
    s[4].Format( "%ld", m_CustomerPlan.GetPoolNr() );
    s[5].Format( "%ld", m_CustomerPlan.GetModemPoolNr() );
    s[6].Format( "%c",  m_CustomerPlan.GetRufEinstellung() ? 'A' : 'M');
    s[7].Format( "%s",  m_CustomerPlan.GetAnrufTyp() );

    CListCtrlHelper::SetItemTexts(m_ListCtl, m_nColumnsCount, s, m_iPos);
    m_ListCtl.SetFocus();
}

//---- SetButton -------------------------------------------------------------//

void CCPPACallPlanDay::SetButton()
{
    BOOL bEnable;

    if (m_ListCtl.GetItemCount() <= 0)
    {
        bEnable = FALSE;
        m_pParent->GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(bEnable);
        m_pParent->GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(bEnable);
        m_pParent->GetDlgItem(IDC_BUTTON_DISABLE)->EnableWindow(bEnable);
        m_pParent->GetDlgItem(IDC_BUTTON_PRINT)->EnableWindow(bEnable);
        m_pParent->GetDlgItem(IDC_BUTTON_DISABLEALL)->EnableWindow(bEnable);
        return;
    }

    m_pParent->GetDlgItem(IDC_BUTTON_DISABLEALL)->EnableWindow(TRUE);
    m_pParent->GetDlgItem(IDC_BUTTON_PRINT)->EnableWindow(TRUE);

    CString csTxt;
    if (m_CustomerPlan.GetCallDisabled())
    {
        csTxt.LoadString(IDP_CALLPLAN_UNLOCK);
        bEnable = FALSE;
    }
    else
    {
        csTxt.LoadString(IDP_CALLPLAN_LOCK);
        bEnable = TRUE;
    }
    m_pParent->GetDlgItem(IDC_BUTTON_DISABLE)->SetWindowText(csTxt);
    m_pParent->GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(bEnable);
    m_pParent->GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(bEnable);
    m_pParent->GetDlgItem(IDC_BUTTON_DISABLE)->EnableWindow(m_pParent->GetAllDisabled() ? FALSE : TRUE);
}

//---- SetFirstListPos -------------------------------------------------------//

void CCPPACallPlanDay::SetFirstListPos()
{
    if (m_ListCtl.GetItemCount() > 0)
    {
        CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
        m_CustomerPlan.SetElement(0);
        GotoDlgCtrl(GetDlgItem(IDC_LIST_CALLPLANDAY));
    }
}
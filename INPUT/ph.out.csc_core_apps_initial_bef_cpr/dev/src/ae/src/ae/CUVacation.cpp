// CUVacation.cpp: Implementierungsdatei
//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include <customer.h>
#include "CUVacation.h"
#include "NMDProgress.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCUVacation

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

CCUVacation::CCUVacation(const short VzNr, const long KdNr)
    : CTabPage(IDD)

{
    m_bIsActive = false;
    m_sSaleCenterNo = VzNr;
    m_lCustomerNo = KdNr;
    m_bModified = true;
    m_List1 = new CVacationListCtrl;
    assert(m_List1);
}

CCUVacation::~CCUVacation()
{
    delete m_List1;
    m_List1 = 0;
}

//--- DoDataExchange ---------------------------------------------------------//

void CCUVacation::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, *m_List1);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CCUVacation, CPropertyPage)
    ON_WM_DESTROY()
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CCUVacation message handlers (ClassWizard) --------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CCUVacation::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    m_List1->init();
    m_List1->SetExtendedStyle(m_List1->GetExtendedStyle()
                              | LVS_EX_FULLROWSELECT
                              | LVS_EX_GRIDLINES );        // Grid

    m_CustomerVacation.SetCountPerPage(200);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

//--- (ClassWizard)OnSetActive -----------------------------------------------//

BOOL CCUVacation::OnSetActive()
{
    if (m_bModified)
    {
        m_bModified = false;
        m_CustomerVacation.SetVertriebsZentrumNr(m_sSaleCenterNo);
        m_CustomerVacation.SetKundennr(m_lCustomerNo);
        m_CustomerVacation.StartBrowse();
        GetPage();
    }

    m_bIsActive = true;
    return CPropertyPage::OnSetActive();
}

//--- (ClassWizard)OnOK ------------------------------------------------------//

void CCUVacation::OnOK()
{
    CString str;

#ifdef _DEBUG
    ATLTRACE("CCUServicePlan::OnOK - raw pos is <%d>\n", m_List1->GetNextItem(-1, LVNI_SELECTED) );
    ATLTRACE("CCUServicePlan::OnOK - item count is <%d>\n", m_List1->GetItemCount());
#endif

    //TODO: only the last row is checked -> as it is in old code
    int pos = m_List1->GetNextItem(-1, LVNI_SELECTED);
    if (pos == (m_List1->GetItemCount() - 1))
    {
#ifdef _DEBUG
        ATLTRACE("CCUServicePlan::OnOK - pos is <%d>\n", pos);
#endif

        str = m_List1->GetItemText(pos, COL_VA_VON);

        if (str.IsEmpty())
        {
            return;
        }

        str = m_List1->GetItemText(pos, COL_VA_VON);

        if (str.IsEmpty())
        {
            m_List1->SetItemText(pos, COL_VA_BIS, m_List1->GetItemText(pos, COL_VA_VON));
        }

        m_List1->addRow();
    }
#ifdef _DEBUG
    else
    {
        ATLTRACE("CCUServicePlan::OnOK - nothing to do\n");
    }
#endif

    CPropertyPage::OnOK();
}

//----------------------------------------------------------------------------//
//--- private methodes (overloaded to CTabPage) ------------------------------//
//----------------------------------------------------------------------------//

//--- GetTabTitle ------------------------------------------------------------//

LPCTSTR CCUVacation::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_URLAUB);
    return _T(m_csTitle);
//  return _T((char *)CResString::ex().getStrTblText(AETXT_URLAUB).GetString());
}

//----------------------------------------------------------------------------//
//--- private methodes -------------------------------------------------------//
//----------------------------------------------------------------------------//

//---- GetPage --------------------------------------------------------------//

bool CCUVacation::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    if (nKzUpDown == PRIOR_PG)
    {
        if (!m_CustomerVacation.SetPreviousPage())
        {
            return false;
        }
    }
    else if (!m_CustomerVacation.SetNextPage())
    {
        return false;
    }

    BeginWaitCursor();
    m_List1->DeleteAllItems();

    m_List1->addRow();

    while (m_CustomerVacation.GetNext())
    {
        if (!SetValueIntoList())
        {
            EndWaitCursor();
            return false;
        }
    }

    EndWaitCursor();
    return TRUE;
}

//---- SetValueIntoList ------------------------------------------------------//

bool CCUVacation::SetValueIntoList()
{
    int pos = m_List1->GetItemCount() - 1; //immer eine Leerzeile

    CString str;
    str = DDMMYYYYStringFromDateLong(m_CustomerVacation.GetDatumgueltigab());
    m_List1->SetItemText(pos, COL_VA_VON, str);
    str = DDMMYYYYStringFromDateLong(m_CustomerVacation.GetDatumgueltigbis());
    m_List1->SetItemText(pos, COL_VA_BIS, str);

    return true;
}

//---- IsChanged ----------------------------------------------------------//

bool CCUVacation::IsChanged()
{
    if (m_bIsActive != true)
    {
        return false;
    }

    long idx = m_List1->GetItemCount() - 1;
    int i = 0;

    for (; i < idx; i++)
    {
        if (!m_CustomerVacation.SetElement(i))
        {
            return true;
        }

        if (m_CustomerVacation.GetDatumgueltigab() !=
                String2longdate(m_List1->GetItemText(i, COL_VA_VON)))
        {
            return true;
        }

        if (m_CustomerVacation.GetDatumgueltigbis() !=
                String2longdate(m_List1->GetItemText(i, COL_VA_BIS)))
        {
            return true;
        }
    }

    if (m_CustomerVacation.SetElement(i))
    {
        return true;
    }

    return false;
}

//---- String2longdate -------------------------------------------------------//

long CCUVacation::String2longdate(const CString& cDate)
{
    return atol(cDate.Left(2)) + atol(cDate.Mid(3, 2)) * 100 + atol(cDate.Right(4)) * 10000;
}

//---- UpdateServer ----------------------------------------------------------//

bool CCUVacation::UpdateServer()
{
    long ldatumvon;
    long ldatumbis;
    int schritt;
    int start = 5;
    CString str1;
    CString str2;
    long idx = m_List1->GetItemCount();

    if (0 == idx)
    {
        schritt = (100 - start) / 2;
    }
    else
    {
        schritt = (100 - start) / idx / 2;
    }

    CNMDProgress dlgProgress;
    dlgProgress.SetText(CResString::ex().getStrTblText(IDS_DATA_SAVING));

    if (dlgProgress.GetSafeHwnd() == 0)
    {
        dlgProgress.Create();
    }

    if (dlgProgress.GetSafeHwnd() != 0)
    {
        dlgProgress.SetProgress(start);
    }

    for (;;)
    {
        if (!m_CustomerVacation.SetElement(0))
        {
            break;
        }

        m_CustomerVacation.Delete();

        if (dlgProgress.GetSafeHwnd() != 0)
        {
            dlgProgress.SetProgress(start += schritt);
        }
    }

    for (int i = 0; i < idx; i++)
    {
        str1 = m_List1->GetItemText(i, COL_VA_VON);

        if (str1.IsEmpty())
        {
            continue;
        }

        ldatumvon = String2longdate(str1);
        str2 = m_List1->GetItemText(i, COL_VA_BIS);

        if (str2.IsEmpty())
        {
            str2 = str1;
            m_List1->SetItemText(i, COL_VA_BIS, str2);
        }

        ldatumbis = String2longdate(str2);
        m_CustomerVacation.SetVertriebsZentrumNr(m_sSaleCenterNo);
        m_CustomerVacation.SetKundennr(m_lCustomerNo);
        m_CustomerVacation.SetDatumgueltigab(ldatumvon);
        m_CustomerVacation.SetDatumgueltigbis(ldatumbis);
        m_CustomerVacation.Insert();

        if (dlgProgress.GetSafeHwnd() != 0)
        {
            dlgProgress.SetProgress(start += schritt);
        }
    }

    if (dlgProgress.GetSafeHwnd() != 0)
    {
        dlgProgress.SetProgress(100);
    }

    m_CustomerVacation.Restore();   // Seite neu
    Sleep(500);

    if (dlgProgress.GetSafeHwnd() != 0)
    {
        dlgProgress.DestroyWindow();
    }

    return true;
}

//---- Delete ----------------------------------------------------------//

bool CCUVacation::DeleteServer()
{
    int pos = m_List1->GetNextItem(-1, LVNI_SELECTED);
    m_List1->DeleteItem(pos);

    return true;
}

void CCUVacation::OnDestroy()
{
    CPropertyPage::OnDestroy();
}

void CCUVacation::ChangeCustomer(const short VzNr, const long KdNr)
{
    SetSaleCenterNo(VzNr);
    SetCustomerNo(KdNr);
    m_bModified = true;
    OnSetActive();
}

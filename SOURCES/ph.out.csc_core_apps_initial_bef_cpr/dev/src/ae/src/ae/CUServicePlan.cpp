// CUServicePlan.cpp: Implementierungsdatei
//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include <customer.h>
#include "CUServicePlan.h"
#include "NMDProgress.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCUServicePlan

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

CCUServicePlan::CCUServicePlan(const short VzNr, const long KdNr)
    : CTabPage(IDD)

{
    m_bIsActive = false;
    m_sSaleCenterNo = VzNr;
    m_lCustomerNo = KdNr;
    m_bModified = true;
    m_List1 = new CServiceListCtrl;
    assert(m_List1);
}

CCUServicePlan::~CCUServicePlan()
{
    delete m_List1;
    m_List1 = NULL;
}


//--- DoDataExchange ---------------------------------------------------------//

void CCUServicePlan::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, *m_List1);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CCUServicePlan, CPropertyPage)
    ON_WM_DESTROY()
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CCUServicePlan message handlers (ClassWizard) --------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CCUServicePlan::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    m_List1->init();
    m_List1->SetExtendedStyle(m_List1->GetExtendedStyle()
                              | LVS_EX_FULLROWSELECT
                              | LVS_EX_GRIDLINES );        // Grid
    m_CustomerEmergency.SetCountPerPage(200);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//--- (ClassWizard)OnSetActive -----------------------------------------------//

BOOL CCUServicePlan::OnSetActive()
{
    if (m_bModified)
    {
        m_bModified = false;
        m_CustomerEmergency.SetVertriebsZentrumNr(m_sSaleCenterNo);
        m_CustomerEmergency.SetKundennr(m_lCustomerNo);
        m_CustomerEmergency.StartBrowse();
        GetPage();
    }

    m_bIsActive = true;
    return CPropertyPage::OnSetActive();
}

//--- (ClassWizard)OnOK ------------------------------------------------------//

void CCUServicePlan::OnOK()
{
    CString str;
    int pos = 0;

#ifdef _DEBUG
    ATLTRACE("CCUServicePlan::OnOK - raw pos is <%d>\n", m_List1->GetNextItem(-1, LVNI_SELECTED) );
    ATLTRACE("CCUServicePlan::OnOK - item count is <%d>\n", m_List1->GetItemCount());
#endif
    CString woher;
    char text[80];
    woher = "CCUServicePlan::OnOK";
    sprintf(text, "pos = %d count = %d", m_List1->GetNextItem(-1, LVNI_SELECTED), m_List1->GetItemCount() - 1);
    AeGetApp()->m_AeTrace.WriteTrace(woher, "CCUServicePlan", text );

    // only the last row is checked -> as it is in old code
    if ((pos = m_List1->GetNextItem(-1, LVNI_SELECTED)) == (m_List1->GetItemCount() - 1))
    {
#ifdef _DEBUG
        ATLTRACE("CCUServicePlan::OnOK - pos is <%d>\n", pos);
#endif

        str = m_List1->GetItemText(pos, COL_SP_DATUM);

        if (str.IsEmpty())
        {
            return;
        }

        str = m_List1->GetItemText(pos, COL_SP_VON);

        if (str.IsEmpty())
        {
            m_List1->SetItemText(pos, COL_SP_VON, "00:00"); //keine Eingabe -> default: 08:30
        }

        str = m_List1->GetItemText(pos, COL_SP_BIS);

        if (str.IsEmpty())
        {
            m_List1->SetItemText(pos, COL_SP_BIS, "23:59"); //keine Eingabe -> default: 08:30
        }

        str = m_List1->GetItemText(pos, COL_SP_BTM);

        if (str.IsEmpty())
        {
            m_List1->SetItemText(pos, COL_SP_BTM, CResString::ex().getStrTblText(AETXT_KZ_JA).Left(1)); //keine Eingabe -> default: ja
        }

        str = m_List1->GetItemText(pos, COL_SP_KK);

        if (str.IsEmpty())
        {
            m_List1->SetItemText(pos, COL_SP_KK, CResString::ex().getStrTblText(AETXT_KZ_JA).Left(1));  //keine Eingabe -> default: ja
        }

        str = m_List1->GetItemText(pos, COL_SP_K08);

        if (str.IsEmpty())
        {
            m_List1->SetItemText(pos, COL_SP_K08, CResString::ex().getStrTblText(AETXT_KZ_JA).Left(1)); //keine Eingabe -> default: ja
        }

        str = m_List1->GetItemText(pos, COL_SP_K20);

        if (str.IsEmpty())
        {
            m_List1->SetItemText(pos, COL_SP_K20, CResString::ex().getStrTblText(AETXT_KZ_JA).Left(1)); //keine Eingabe -> default: ja
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

LPCTSTR CCUServicePlan::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_NOTDIENSTPLAN);
    return _T(m_csTitle);
}
//---- GetPage --------------------------------------------------------------//

bool CCUServicePlan::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    if (nKzUpDown == PRIOR_PG)
    {
        if (!m_CustomerEmergency.SetPreviousPage())
        {
            return false;
        }
    }
    else if (!m_CustomerEmergency.SetNextPage())
    {
        return false;
    }

    BeginWaitCursor();

    m_List1->DeleteAllItems();
    m_List1->addRow();

    while (m_CustomerEmergency.GetNext())
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

bool CCUServicePlan::SetValueIntoList()
{
    int pos = m_List1->GetItemCount() - 1; //immer eine Leerzeile

    CString str;
    str = DDMMYYYYStringFromDateLong(m_CustomerEmergency.GetDatum());
    m_List1->SetItemText(pos, COL_SP_DATUM, str);
    str = HHmmStringFromTimeLong(m_CustomerEmergency.GetUhrzeitvon());
    m_List1->SetItemText(pos, COL_SP_VON, str);
    str = HHmmStringFromTimeLong(m_CustomerEmergency.GetUhrzeitbis());
    m_List1->SetItemText(pos, COL_SP_BIS, str);

    str = CResString::ex().getStrTblText((m_CustomerEmergency.GetIsbtm() == 1) ? AETXT_KZ_JA : AETXT_KZ_NEIN).Left(1);
    m_List1->SetItemText(pos, COL_SP_BTM, str);
    str = CResString::ex().getStrTblText((m_CustomerEmergency.GetIskk() == 1) ? AETXT_KZ_JA : AETXT_KZ_NEIN).Left(1);
    m_List1->SetItemText(pos, COL_SP_KK, str);
    str = CResString::ex().getStrTblText((m_CustomerEmergency.GetIsk08() == 1) ? AETXT_KZ_JA : AETXT_KZ_NEIN).Left(1);
    m_List1->SetItemText(pos, COL_SP_K08, str);
    str = CResString::ex().getStrTblText((m_CustomerEmergency.GetIsk20() == 1) ? AETXT_KZ_JA : AETXT_KZ_NEIN).Left(1);
    m_List1->SetItemText(pos, COL_SP_K20, str);

    m_List1->SetItemText(pos, COL_SP_BEMERK, m_CustomerEmergency.GetBemerkungen());

    m_List1->addRow();

    return true;
}

//---- IsChanged ----------------------------------------------------------//

bool CCUServicePlan::IsChanged()
{
    if (m_bIsActive != true)
    {
        return false;
    }

    long idx = m_List1->GetItemCount() - 1;
    int i = 0;

    for (; i < idx; i++)
    {
        if (!m_CustomerEmergency.SetElement(i))
        {
            return true;
        }

        if (m_CustomerEmergency.GetDatum() != String2longdate(m_List1->GetItemText(i, COL_SP_DATUM)))
        {
            return true;
        }

        if (m_CustomerEmergency.GetUhrzeitvon() != String2longtime(m_List1->GetItemText(i, COL_SP_VON)))
        {
            return true;
        }

        if (m_CustomerEmergency.GetUhrzeitbis() != String2longtime(m_List1->GetItemText(i, COL_SP_BIS)))
        {
            return true;
        }

        if (m_CustomerEmergency.GetIsbtm() != YesNo2short(m_List1->GetItemText(i, COL_SP_BTM)))
        {
            return true;
        }

        if (m_CustomerEmergency.GetIskk() != YesNo2short(m_List1->GetItemText(i, COL_SP_KK)))
        {
            return true;
        }

        if (m_CustomerEmergency.GetIsk08() != YesNo2short(m_List1->GetItemText(i, COL_SP_K08)))
        {
            return true;
        }

        if (m_CustomerEmergency.GetIsk20() != YesNo2short(m_List1->GetItemText(i, COL_SP_K20)))
        {
            return true;
        }

        if (m_CustomerEmergency.GetBemerkungen() != m_List1->GetItemText(i, COL_SP_BEMERK))
        {
            return true;
        }
    }

    if (m_CustomerEmergency.SetElement(i))
    {
        return true;
    }

    return false;
}

//---- String2longdate -------------------------------------------------------//

long CCUServicePlan::String2longdate(const CString& cDate)
{
    return atol(cDate.Left(2)) + atol(cDate.Mid(3, 2)) * 100 + atol(cDate.Right(4)) * 10000;
}

//---- String2longtime -------------------------------------------------------//

long CCUServicePlan::String2longtime(const CString& cTime)
{
    return atol(cTime.Left(2)) * 10000 + atol(cTime.Right(2)) * 100;
}

//---- YesNo2short -------------------------------------------------------//

short CCUServicePlan::YesNo2short(const CString& cYesNo)
{
    return (cYesNo == CResString::ex().getStrTblText(AETXT_KZ_JA).Left(1)) ? 1 : 0;
}
//---- UpdateServer ----------------------------------------------------------//

bool CCUServicePlan::UpdateServer()
{
    long ldatum;
    long lzeitvon;
    long lzeitbis;
    int schritt;
    int start = 5;
    CString str;
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
    dlgProgress.SetText("Daten werden gespeichert");

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
        if (!m_CustomerEmergency.SetElement(0))
        {
            break;
        }

        m_CustomerEmergency.Delete();

        if (dlgProgress.GetSafeHwnd() != 0)
        {
            dlgProgress.SetProgress(start += schritt);
        }
    }

    for (int i = 0; i < idx; i++)
    {
        str = m_List1->GetItemText(i, COL_SP_DATUM);

        if (str.IsEmpty())
        {
            continue;
        }

        ldatum = String2longdate(str);
        str = m_List1->GetItemText(i, COL_SP_VON);

        if (str.IsEmpty())
        {
            str = "08:30";
            m_List1->SetItemText(i, COL_SP_VON, str);
        }

        lzeitvon = String2longtime(str);
        str = m_List1->GetItemText(i, COL_SP_BIS);

        if (str.IsEmpty())
        {
            str = "08:30";
            m_List1->SetItemText(i, COL_SP_BIS, str);;
        }

        lzeitbis = String2longtime(str);
        m_CustomerEmergency.SetVertriebsZentrumNr(m_sSaleCenterNo);
        m_CustomerEmergency.SetKundennr(m_lCustomerNo);
        m_CustomerEmergency.SetDatum(ldatum);
        m_CustomerEmergency.SetUhrzeitvon(lzeitvon);
        m_CustomerEmergency.SetUhrzeitbis(lzeitbis);
        m_CustomerEmergency.SetIsbtm(YesNo2short(m_List1->GetItemText(i, COL_SP_BTM)));
        m_CustomerEmergency.SetIskk(YesNo2short(m_List1->GetItemText(i, COL_SP_KK)));
        m_CustomerEmergency.SetIsk08(YesNo2short(m_List1->GetItemText(i, COL_SP_K08)));
        m_CustomerEmergency.SetIsk20(YesNo2short(m_List1->GetItemText(i, COL_SP_K20)));
        m_CustomerEmergency.SetBemerkungen(m_List1->GetItemText(i, COL_SP_BEMERK));
        m_CustomerEmergency.Insert();

        if (dlgProgress.GetSafeHwnd() != 0)
        {
            dlgProgress.SetProgress(start += schritt);
        }
    }

    if (dlgProgress.GetSafeHwnd() != 0)
    {
        dlgProgress.SetProgress(100);
    }

    m_CustomerEmergency.Restore();  // Seite neu
    Sleep(500);

    if (dlgProgress.GetSafeHwnd() != 0)
    {
        dlgProgress.DestroyWindow();
    }

    return true;
}

//---- Delete ----------------------------------------------------------//

bool CCUServicePlan::DeleteServer()
{
    for (;;)
    {
        int pos = m_List1->GetNextItem(-1, LVNI_SELECTED);
        if (pos < 0)
            break;
        m_List1->DeleteItem(pos);
    }

    return true;
}

void CCUServicePlan::OnDestroy()
{
    CPropertyPage::OnDestroy();
}

void CCUServicePlan::ChangeCustomer(const short VzNr, const long KdNr)
{
    SetSaleCenterNo(VzNr);
    SetCustomerNo(KdNr);
    m_bModified = true;
    OnSetActive();
}

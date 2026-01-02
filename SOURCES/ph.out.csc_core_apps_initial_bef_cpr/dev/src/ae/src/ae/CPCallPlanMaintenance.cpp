
//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPCallPlanMaintenance.cpp
   Author: A.Schmidt-Rehschuh
   made  : 17.04.2000

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "CPCallPlanMaintenance.h"
#include "DKndWahl.h"
#include <kndsel.h>
#include "DKndInf.h"
#include "ppPrint.h"
#include "DParAufBearb.h"

//----------------------------------------------------------------------------//
//--- public methodes --------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- GetAllDisabled ---------------------------------------------------------//

const bool CCPCallPlanMaintenance::GetAllDisabled() const
{
    return m_pCallPlan->IsAllCallsAreDisabled();
}

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CCPCallPlanMaintenance::CCPCallPlanMaintenance(ppCustomerDisplay* pCustomer,
                                               CWnd* pParent)
    : CDialogMultiLang(CCPCallPlanMaintenance::IDD, pParent)
{
    m_pCustomer = pCustomer;
    m_bIsVkMenu = false;

    m_psrvAufParameter = new CPARAUFBEARB;
    m_pCallPlan = new ppCustomerCallPlan(pCustomer);
    m_pPageCallPlanMonday = new CCPPACallPlanDay(this, pCustomer, m_psrvAufParameter, ppDayType::d_monday);
    m_pPageCallPlanTuesday = new CCPPACallPlanDay(this, pCustomer, m_psrvAufParameter, ppDayType::d_tuesday);
    m_pPageCallPlanWednesday = new CCPPACallPlanDay(this, pCustomer, m_psrvAufParameter, ppDayType::d_wednesday);
    m_pPageCallPlanThursday = new CCPPACallPlanDay(this, pCustomer, m_psrvAufParameter, ppDayType::d_thursday);
    m_pPageCallPlanFriday = new CCPPACallPlanDay(this, pCustomer, m_psrvAufParameter, ppDayType::d_friday);
    m_pPageCallPlanSaturday = new CCPPACallPlanDay(this, pCustomer, m_psrvAufParameter, ppDayType::d_saturday);
    m_pPageCallPlanSunday = new CCPPACallPlanDay(this, pCustomer, m_psrvAufParameter, ppDayType::d_sunday);
}

//--- deconstructor ----------------------------------------------------------//

CCPCallPlanMaintenance::~CCPCallPlanMaintenance()
{
    if (m_pPageCallPlanMonday)
        delete m_pPageCallPlanMonday;
    if (m_pPageCallPlanTuesday)
        delete m_pPageCallPlanTuesday;
    if (m_pPageCallPlanWednesday)
        delete m_pPageCallPlanWednesday;
    if (m_pPageCallPlanThursday)
        delete m_pPageCallPlanThursday;
    if (m_pPageCallPlanFriday)
        delete m_pPageCallPlanFriday;
    if (m_pPageCallPlanSaturday)
        delete m_pPageCallPlanSaturday;
    if (m_pPageCallPlanSunday)
        delete m_pPageCallPlanSunday;
    if (m_pCallPlan)
        delete m_pCallPlan;
    if (m_psrvAufParameter)
        delete m_psrvAufParameter;
}

//--- DoDataExchange ---------------------------------------------------------//

void CCPCallPlanMaintenance::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_DELETEALL, m_CButtonDeleteAll);
    DDX_Control(pDX, IDC_TAB_CALLPLAN, m_CTabCtrlCallPlan);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CCPCallPlanMaintenance, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_CUSTOMER, OnButtonCustomer)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
    ON_BN_CLICKED(IDC_BUTTON_DISABLE, OnButtonDisable)
    ON_BN_CLICKED(IDC_BUTTON_DELETEALL, OnButtonDeleteall)
    ON_BN_CLICKED(IDC_BUTTON_DISABLEALL, OnButtonDisableall)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CCPCallPlanMaintenance message handlers (ClassWizard) ------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CCPCallPlanMaintenance::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    if (m_pCustomer->GetVertriebsZentrumNr() == 0 ||
        m_pCustomer->GetKundenNr() == 0)
    {
        if (!GetCustomer())
        {
            CDialogMultiLang::OnCancel();
            return FALSE;
        }
    }
    else
        SetHeader();

    m_psrvAufParameter->s.FILIALNR = m_pCustomer->GetVertriebsZentrumNr();
    m_psrvAufParameter->Server( AafilSelaufbearb );

    // von hier gehts pro Tag ab in den CPPACallPlanDay.cpp-OnInitDialog

    m_CTabCtrlCallPlan.AddPage(m_pPageCallPlanMonday);
    m_CTabCtrlCallPlan.AddPage(m_pPageCallPlanTuesday);
    m_CTabCtrlCallPlan.AddPage(m_pPageCallPlanWednesday);
    m_CTabCtrlCallPlan.AddPage(m_pPageCallPlanThursday);
    m_CTabCtrlCallPlan.AddPage(m_pPageCallPlanFriday);
    m_CTabCtrlCallPlan.AddPage(m_pPageCallPlanSaturday);
    m_CTabCtrlCallPlan.AddPage(m_pPageCallPlanSunday);

    // *** this should be done in order to be able to use the shortcut keys
    m_CTabCtrlCallPlan.GetCurrentPage()->OnSetActive();
    m_CTabCtrlCallPlan.GetCurrentPage()->SetFocus();

    if (m_pCallPlan->IsAllCallsAreDisabled() && m_CTabCtrlCallPlan.GetCurrentPage()->GetCountItem() > 0)
        SetButton(false);
    return TRUE;
}

//--- (ClassWizard)OnOK ------------------------------------------------------//

void CCPCallPlanMaintenance::OnOK()
{
    CDialogMultiLang::OnOK();
}

//--- (ClassWizard)OnCancel --------------------------------------------------//

void CCPCallPlanMaintenance::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

//--- (ClassWizard)OnButtonCustomer ------------------------------------------//

void CCPCallPlanMaintenance::OnButtonCustomer()
{
    GetCustomer();
    m_CTabCtrlCallPlan.GetCurrentPage()->OnSetActive();
}

//--- (ClassWizard)OnButtonUpdate --------------------------------------------//

void CCPCallPlanMaintenance::OnButtonUpdate()
{
    m_CTabCtrlCallPlan.GetCurrentPage()->UpdateServer();
}

//--- (ClassWizard)OnButtonInsert --------------------------------------------//

void CCPCallPlanMaintenance::OnButtonInsert()
{
    if (m_CTabCtrlCallPlan.GetCurrentPage()->InsertServer())
        m_pCallPlan->SetAllCallsAreDisabled(false);
}

//--- (ClassWizard)OnButtonDelete --------------------------------------------//

void CCPCallPlanMaintenance::OnButtonDelete()
{
    m_CTabCtrlCallPlan.GetCurrentPage()->DeleteServer();
}

//--- (ClassWizard)OnButtonDelete --------------------------------------------//

void CCPCallPlanMaintenance::OnButtonDisable()
{
    m_CTabCtrlCallPlan.GetCurrentPage()->OtherServer();
}

//--- (ClassWizard)OnButtonPrint --------------------------------------------//

void CCPCallPlanMaintenance::OnButtonPrint()
{
    CPrintDialog dlgPrinter(false);
    if (dlgPrinter.DoModal() == IDOK)
    {
        PrintCallPlan(CDC::FromHandle(dlgPrinter.GetPrinterDC()));
    }
}

//--- (ClassWizard)OnButtonDeleteall (only showed if customer disabled! ------//

void CCPCallPlanMaintenance::OnButtonDeleteall()
{
    if (MsgBoxYesNo(IDP_MASTERPLAN_DELETEALL) != IDYES)
        return;

    if (!m_pCallPlan->DestroyCompletly())
    {
        MsgBoxOK(m_pCallPlan->GetErrorMsg());
        return;
    }

    m_CTabCtrlCallPlan.GetCurrentPage()->Initialize();
}

//--- (ClassWizard)OnButtonDisableall ----------------------------------------//

void CCPCallPlanMaintenance::OnButtonDisableall()
{
    UINT nText = m_pCallPlan->IsAllCallsAreDisabled() ? IDP_MASTERPLAN_ENABLEALL : IDP_MASTERPLAN_DISABLEALL;

    if (MsgBoxYesNo(nText) != IDYES)
        return;

    if (!m_pCallPlan->EnableCompletly(m_pCallPlan->IsAllCallsAreDisabled()))
    {
        MsgBoxOK(m_pCallPlan->GetErrorMsg());
        return;
    }

    m_CTabCtrlCallPlan.GetCurrentPage()->OnSetActive();
    SetButton(m_pCallPlan->IsAllCallsAreDisabled() ? false : true);
}

//----------------------------------------------------------------------------//
//--- private methodes -------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- OnHookFkt --------------------------------------------------------------//

LRESULT CCPCallPlanMaintenance::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    int iLetter = (int)((LPMSG)lpMsg)->wParam;

    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        CKndInf dlgCustomerInfo;
        dlgCustomerInfo.SetKndNr(m_pCustomer->GetKundenNr());
        dlgCustomerInfo.SetKndVz(m_pCustomer->GetVertriebsZentrumNr());
        dlgCustomerInfo.DoModal();
        return 1L;
    }
    else if (iLetter == KEY_ALT)
    {
        m_bIsVkMenu = true;
        return 0L;
    }

    if ((iLetter == KEY_AE || iLetter == KEY_U) && m_bIsVkMenu)
    {
        m_CTabCtrlCallPlan.GetCurrentPage()->UpdateServer();
        m_bIsVkMenu = false;
        return 1L;
    }
    else if (iLetter == KEY_N && m_bIsVkMenu)
    {
        m_CTabCtrlCallPlan.GetCurrentPage()->InsertServer();
        m_bIsVkMenu = false;
        return 1L;
    }
    else if (iLetter == KEY_K && m_bIsVkMenu)
    {
        GetCustomer();
        m_CTabCtrlCallPlan.GetCurrentPage()->OnSetActive();
        m_bIsVkMenu = false;
        return 1L;
    }
    else if ((iLetter == KEY_L) && m_bIsVkMenu)
    {
        m_CTabCtrlCallPlan.GetCurrentPage()->DeleteServer();
        m_bIsVkMenu = false;
        return 1L;
    }
    else if (iLetter == KEY_A && m_bIsVkMenu)
    {
        OnCancel();
        m_bIsVkMenu = false;
        return 1L;
    }
    else if (iLetter == KEY_E && m_bIsVkMenu)
    {
        OnButtonDeleteall();
        m_bIsVkMenu = false;
        return 1L;
    }
    else if (iLetter == KEY_S && m_bIsVkMenu)
    {
        m_CTabCtrlCallPlan.GetCurrentPage()->OtherServer();
        m_bIsVkMenu = false;
        return 1L;
    }
    else if (iLetter == KEY_R && m_bIsVkMenu)
    {
        OnButtonDisableall();
        m_bIsVkMenu = false;
        return 1L;
    }

    return 0;
}

//--- SetHeader --------------------------------------------------------------//

void CCPCallPlanMaintenance::SetHeader()
{
    GetDlgItem(IDC_OUT_CUSTOMERNAME)->SetWindowText(m_pCustomer->GetNameInhaber());
    GetDlgItem(IDC_OUT_ZIPCODE)->SetWindowText(m_pCustomer->GetPostleitZahl());
    GetDlgItem(IDC_OUT_CITY)->SetWindowText(m_pCustomer->GetOrt());
    GetDlgItem(IDC_OUT_CUSTOMERID)->SetWindowText(ppString(m_pCustomer->GetIdfNr()).c_str());
    GetDlgItem(IDC_OUT_PHARMACY)->SetWindowText(m_pCustomer->GetNameApo());
    GetDlgItem(IDC_OUT_STREET)->SetWindowText(m_pCustomer->GetStrasse());
    GetDlgItem(IDC_OUT_SALECENTER)->SetWindowText(ppString((long)m_pCustomer->GetVertriebsZentrumNr()).c_str());
    if (m_pCustomer->GetSkdKundeAeGesperrt())
    {
        CString csHeader;
        csHeader = CResString::ex().getStrTblText(IDP_MASTERPLAN_HEADER1);
        SetWindowText(csHeader);
    }
    else
    {
        m_CButtonDeleteAll.ShowWindow(SW_HIDE);
        CString csHeader;
        csHeader = CResString::ex().getStrTblText(IDP_MASTERPLAN_HEADER);
        SetWindowText(csHeader);
    }
}

//--- GetCustomer ------------------------------------------------------------//

bool CCPCallPlanMaintenance::GetCustomer()
{
    CDKndWahl dlgKndWahl;
    dlgKndWahl.SetEnableAeGesperrt(TRUE);  // Checkbutton muß enabled werden und wird gesetzt!

    if (dlgKndWahl.DoModal() != IDOK)
        return false;

    m_pCustomer->SetVertriebsZentrumNr(dlgKndWahl.GetKndVz());
    m_pCustomer->SetKundenNr(dlgKndWahl.GetKndNr());

    if (!m_pCustomer->GetUni())
        return false;
    else if (!m_pCallPlan->CheckAllDisabled())
        MsgBoxOK(m_pCallPlan->GetErrorMsg());

    SetHeader();
    return true;
}

//--- Print ------------------------------------------------------------------//

bool CCPCallPlanMaintenance::PrintCallPlan(CDC* dc)
{
    ppCustomerCallPlan CustomerPlan(m_pCustomer);
    CustomerPlan.SetCountPerPage(100);
    if (!CustomerPlan.StartBrowse())
        return false;
    else if (!CustomerPlan.SetNextPage(ppCustomerCallPlan::c_print))
        return false;

    ppPrint p(dc, "Courier", "");

    ppString strAdress = CResString::ex().getStrTblText(IDS_MISTER);

    p.PrintHeader();
    p.Print(CResString::ex().getStrTblText(IDS_CALLPLAN_PH) + AeGetApp()->FilialName(), 3);

    switch(m_pCustomer->GetAnredeKz())
    {
        case ppCustomerDisplay::t_mister:
            strAdress = CResString::ex().getStrTblText(IDS_MISTER);
            break;
        case ppCustomerDisplay::t_miss:
            strAdress = CResString::ex().getStrTblText(IDS_FRAEULEIN);
            break;
        case ppCustomerDisplay::t_mrs:
            strAdress = CResString::ex().getStrTblText(IDS_MRS);
            break;
        case ppCustomerDisplay::t_company:
            strAdress = CResString::ex().getStrTblText(IDS_COMPANY);
            break;
    }

    p.Print(strAdress + " " + m_pCustomer->GetNameInhaber());
    CString csAdress;
    csAdress.Format("%ld %s", m_pCustomer->GetIdfNr(), m_pCustomer->GetNameApo());
    p.Print(csAdress, 2);
    csAdress = m_pCustomer->GetPostleitZahl();
    csAdress += " ";
    csAdress += m_pCustomer->GetOrt();
    p.Print(csAdress);
    p.SetLine(p.GetLine());

    short sDay = -1;
    int iPosCol = 0;
    BeginWaitCursor();
    while (CustomerPlan.GetNext(ppCustomerCallPlan::c_print))
    {
        ppTime time(CustomerPlan.GetUrRufzeit());
        if (sDay != CustomerPlan.GetTagNr())
        {
            p.SetLine(p.GetLine() + 2);
            sDay = CustomerPlan.GetTagNr();
            ppDayType day((const ppDayType::t_day)CustomerPlan.GetTagNr());

            p.Print(day);

            iPosCol = 0;

            p.Print((const char*)time, 0);
            continue;
        }

        iPosCol += 15;

        iPosCol = p.PrintColumnStatic( (const char*)time, iPosCol);
    }

    p.EndPrint();
    EndWaitCursor();
    return true;
}

//--- SetButton --------------------------------------------------------------//

void CCPCallPlanMaintenance::SetButton(const bool bEnable)
{
    CString csTxt;
    if (bEnable)
    {
        csTxt = CResString::ex().getStrTblText(IDP_CALLPLAN_LOCKALL);
    }
    else
    {
        csTxt = CResString::ex().getStrTblText(IDP_CALLPLAN_UNLOCKALL);
    }
    //csTxt.LoadString(bEnable ? IDP_CALLPLAN_LOCKALL : IDP_CALLPLAN_UNLOCKALL );
    GetDlgItem(IDC_BUTTON_DISABLEALL)->SetWindowText(csTxt);
    GetDlgItem(IDC_BUTTON_PRINT)->EnableWindow(bEnable);
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(bEnable);
    GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(bEnable);
    GetDlgItem(IDC_BUTTON_INSERT)->EnableWindow(bEnable);
    GetDlgItem(IDC_BUTTON_DISABLE)->EnableWindow(bEnable);
    return;
}



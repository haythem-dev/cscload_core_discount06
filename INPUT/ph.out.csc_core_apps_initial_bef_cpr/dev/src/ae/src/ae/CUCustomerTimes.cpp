// CUCustomerTimes.cpp: Implementierungsdatei
//
//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include <kndsel.h>
#include "DKndWahl.h"
#include "DKndInf.h"
#include <customer.h>
#include "CUCustomerTimes.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCUCustomerTimes


//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CCUCustomerTimes::CCUCustomerTimes(const short VZ,
                                   const long Knd,
                                   CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CCUCustomerTimes::IDD, pParent)
{
    m_sSaleCenterNo = VZ;
    m_lCustomerNo = Knd;
    m_bIsVkMenu = false;
}

//--- DoDataExchange ---------------------------------------------------------//

void CCUCustomerTimes::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_TIME, m_CTabCtrlCustomerTime);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CCUCustomerTimes, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CCUCustomerTimes message handlers (ClassWizard) -------------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CCUCustomerTimes::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    if (m_lCustomerNo == -1 || m_sSaleCenterNo == -1)
    {
        //Definition Kunde
        CDKndWahl dlgKndWahl;
        dlgKndWahl.SetEnableAeGesperrt();    // Checkbutton muﬂ enabled werden
        if (dlgKndWahl.DoModal() == IDOK)
        {
            m_lCustomerNo = dlgKndWahl.GetKndNr();
            m_sSaleCenterNo = dlgKndWahl.GetKndVz();
        }
        else
        {
            CDialogMultiLang::OnCancel();
            return IDCANCEL;
        }
        m_PageCustomerTimeEmergencyService.SetSaleCenterNo(m_sSaleCenterNo);
        m_PageCustomerTimeEmergencyService.SetCustomerNo(m_lCustomerNo);
        m_PageCustomerTimeVacation.SetSaleCenterNo(m_sSaleCenterNo);
        m_PageCustomerTimeVacation.SetCustomerNo(m_lCustomerNo);
    }
    SetHeader();
    //add pages
    m_CTabCtrlCustomerTime.AddPage(&m_PageCustomerTimeEmergencyService);
    m_CTabCtrlCustomerTime.AddPage(&m_PageCustomerTimeVacation);

    // *** this should be done in order to be able to use the shortcut keys
    m_CTabCtrlCustomerTime.GetCurrentPage()->OnSetActive();
    m_CTabCtrlCustomerTime.GetCurrentPage()->SetFocus();

    return FALSE;
}

//--- (ClassWizard)OnInitDialog ----------------------------------------------//


void CCUCustomerTimes::OnButtonSave()
{
    m_CTabCtrlCustomerTime.GetCurrentPage()->UpdateServer();
}

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

void CCUCustomerTimes::OnCancel()
{
    if (AreChanged())
        return;
    CDialogMultiLang::OnCancel();
}

//--- Testen, ob Seiten geaendert ----------------------------------------------//

bool CCUCustomerTimes::AreChanged()
{
    CTabPage* pTabPage;
    for (int i = 0; (pTabPage = m_CTabCtrlCustomerTime.GetPage(i)) != NULL; i++)
    {
        if (pTabPage->IsChanged())
        {
            CString str;
            str.Format(CResString::ex().getStrTblText(IDS_CHANGED_NOT_SAVED), pTabPage->GetTabTitle());
            if (MsgBoxYesNo(str) != IDYES)
                return true;
        }
    }
    return false;
}

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

void CCUCustomerTimes::OnOK()
{
    CWnd* pWnd = GetFocus();
    if (pWnd == GetDlgItem(IDC_TAB_TIME) || pWnd == GetDlgItem(IDOK))
    {
        m_CTabCtrlCustomerTime.GetCurrentPage()->UpdateServer();
    }
}

//----------------------------------------------------------------------------//
//--- private methodes -------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- OnHookFkt --------------------------------------------------------------//

LRESULT CCUCustomerTimes::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    int iLetter = (int)((LPMSG)lpMsg)->wParam;

    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        //Ausgabe der Kundeninformationen
        CKndInf dlgKndInf;
        dlgKndInf.SetIdfNr(m_lCustomerNo);
        dlgKndInf.SetKndVz(m_sSaleCenterNo);
        dlgKndInf.DoModal();
        return 1L;
    }
    if (((LPMSG)lpMsg)->wParam == VK_RETURN)
    {
        return 0L;
    }
    if (iLetter == KEY_ALT)
    {
        m_bIsVkMenu = true;
        return 0L;
    }

    if (iLetter == KEY_S && m_bIsVkMenu)
    {
        m_CTabCtrlCustomerTime.GetCurrentPage()->UpdateServer();
        m_bIsVkMenu = false;
        return 1L;
    }
    if (iLetter == KEY_L && m_bIsVkMenu)
    {
        m_CTabCtrlCustomerTime.GetCurrentPage()->DeleteServer();
        m_bIsVkMenu = false;
        return 1L;
    }
    if (iLetter == KEY_W && m_bIsVkMenu)
    {
        OnButtonChange();
        m_bIsVkMenu = false;
        return 1L;
    }

    return 0L;
}

//--- SetLanguagesString -----------------------------------------------------//

void CCUCustomerTimes::SetHeader()
{
    CKNDINF kndinf;
    char text[81];
    kndinf.s.KUNDENNR            = m_lCustomerNo;
    kndinf.s.VERTRIEBSZENTRUMNR  = m_sSaleCenterNo;
    BeginWaitCursor();
    kndinf.Server(AakundeSel_knd_info);
    EndWaitCursor();
    GetDlgItem(IDC_OUT_CUSTOMERNAME)->SetWindowText(kndinf.s.NAMEINHABER);
    AllgEntfFirstSpaces(kndinf.s.POSTLEITZAHL);
    GetDlgItem(IDC_OUT_ZIPCODE)->SetWindowText(kndinf.s.POSTLEITZAHL);
    sprintf(text, "%ld", kndinf.s.IDFNR);
    GetDlgItem(IDC_OUT_CUSTOMERID)->SetWindowText(text);
    GetDlgItem(IDC_OUT_PHARMACY)->SetWindowText(kndinf.s.NAMEAPO);
    GetDlgItem(IDC_OUT_STREET)->SetWindowText(kndinf.s.STRASSE);
    GetDlgItem(IDC_OUT_CITY)->SetWindowText(kndinf.s.ORT);
    GetDlgItem(IDC_OUT_TEL)->SetWindowText(kndinf.s.TELNR);
    sprintf(text, "%ld", kndinf.s.VERTRIEBSZENTRUMNR);
    GetDlgItem(IDC_OUT_SALECENTER)->SetWindowText(text);
}

void CCUCustomerTimes::OnButtonDelete()
{
    m_CTabCtrlCustomerTime.GetCurrentPage()->DeleteServer();
}

void CCUCustomerTimes::OnButtonChange()
{
    if (AreChanged())
        return;
    CDKndWahl dlgKndWahl;
    dlgKndWahl.SetEnableAeGesperrt();    // Checkbutton muﬂ enabled werden
    if (dlgKndWahl.DoModal() == IDOK)
    {
        m_lCustomerNo = dlgKndWahl.GetKndNr();
        m_sSaleCenterNo = dlgKndWahl.GetKndVz();
    }
    else
        return;
    SetHeader();
    m_PageCustomerTimeEmergencyService.ChangeCustomer(m_sSaleCenterNo, m_lCustomerNo);
    m_PageCustomerTimeVacation.ChangeCustomer(m_sSaleCenterNo, m_lCustomerNo);
}

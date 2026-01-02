
//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPCustomerTelN.cpp
   Author: A.Schmidt-Rehschuh
   made  : 09.04.2000

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "CPCustomerTelNo.h"
#include "ppCustomerDisplay.h"
#include "DKndWahl.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CCPCustomerTelNo::CCPCustomerTelNo(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CCPCustomerTelNo::IDD, pParent)
{
    m_pCustomer = new ppCustomerDisplay(AeGetApp()->ErrorPath());
}

//--- deconstructor ----------------------------------------------------------//

CCPCustomerTelNo::~CCPCustomerTelNo()
{
    if (m_pCustomer)
        delete m_pCustomer;
}

//--- DoDataExchange ---------------------------------------------------------//

void CCPCustomerTelNo::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CCPCustomerTelNo, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_RESTORE, OnButtonRestore)
    ON_BN_CLICKED(IDC_BUTTON_CUSTOMER, OnButtonCustomer)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CCPCustomerTelNo message handlers (ClassWizard) ------------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CCPCustomerTelNo::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    if (!GetCustomer())
    {
        CDialogMultiLang::OnCancel();
        return FALSE;
    }

    SetHeader();
    OnButtonRestore();
    return TRUE;
}

//--- (ClassWizard)OnOK ------------------------------------------------------//

void CCPCustomerTelNo::OnOK()
{
    CString csValue;
    GetDlgItem(IDC_EDIT_SHORTNO)->GetWindowText(csValue);
    m_pCustomer->SetTelKurzwahl(csValue);
    GetDlgItem(IDC_EDIT_TELNO)->GetWindowText(csValue);
    m_pCustomer->SetTelnr(csValue);
    GetDlgItem(IDC_EDIT_SERANO)->GetWindowText(csValue);
    m_pCustomer->SetTelnrDafue(csValue);

    if (!m_pCustomer->Update())
    {
        MsgBoxOK(m_pCustomer->GetErrorMsg());
    }
    else
    {
        MsgBoxOK(IDP_CUSTOMER_CHANGED);
    }

    GetDlgItem(IDC_BUTTON_RESTORE)->EnableWindow(FALSE);
}

//--- (ClassWizard)OnButtonRestore -------------------------------------------//

void CCPCustomerTelNo::OnButtonRestore()
{
    m_pCustomer->Restore();
    GetDlgItem(IDC_EDIT_SHORTNO)->SetWindowText(m_pCustomer->GetTelKurzwahl());
    GetDlgItem(IDC_EDIT_TELNO)->SetWindowText(m_pCustomer->GetTelnr());
    GetDlgItem(IDC_EDIT_SERANO)->SetWindowText(m_pCustomer->GetTelnrDafue());
    GetDlgItem(IDC_EDIT_SERANO)->SetFocus();
}

//--- (ClassWizard)OnButtonRestore -------------------------------------------//

void CCPCustomerTelNo::OnButtonCustomer()
{
    if (GetCustomer())
    {
        GetDlgItem(IDC_BUTTON_RESTORE)->EnableWindow(TRUE);
        SetHeader();
        OnButtonRestore();
    }
}

//----------------------------------------------------------------------------//
//--- protected methodes -----------------------------------------------------//
//----------------------------------------------------------------------------//

//--- SetHeader --------------------------------------------------------------//

void CCPCustomerTelNo::SetHeader()
{
    GetDlgItem(IDC_STATIC_DATE)->SetWindowText(AeGetApp()->GetCurrentDate());
    GetDlgItem(IDC_STATIC_TIME)->SetWindowText(AeGetApp()->GetCurrentTime());

    GetDlgItem(IDC_STATIC_NAME)->SetWindowText(m_pCustomer->GetNameInhaber());
    GetDlgItem(IDC_STATIC_ZIPCODE)->SetWindowText(m_pCustomer->GetPostleitZahl());
    GetDlgItem(IDC_STATIC_CITY)->SetWindowText(m_pCustomer->GetOrt());
    GetDlgItem(IDC_STATIC_CUSTOMERNO)->SetWindowText(ppString(m_pCustomer->GetIdfNr()).c_str());
    GetDlgItem(IDC_STATIC_PHARMACY)->SetWindowText(m_pCustomer->GetNameApo());
    GetDlgItem(IDC_STATIC_SALECENTER)->SetWindowText(ppString((long)m_pCustomer->GetVertriebsZentrumNr()).c_str());
}
//--- GetCustomer ------------------------------------------------------------//

bool CCPCustomerTelNo::GetCustomer()
{
    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
        return false;

    m_pCustomer->SetVertriebsZentrumNr(dlgKndWahl.GetKndVz());
    m_pCustomer->SetKundenNr(dlgKndWahl.GetKndNr());

    if (!m_pCustomer->GetUni())
        return false;
    return true;
}

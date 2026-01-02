
//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPCustomerProperties.cpp
   Author: A.Schmidt-Rehschuh
   made  : 09.04.2000

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "CPCustomerProperties.h"
#include "ppCustomerDisplay.h"
#include "DKndWahl.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CCPCustomerProperties::CCPCustomerProperties(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CCPCustomerProperties::IDD, pParent)
{
    m_pCustomer = new ppCustomerDisplay(AeGetApp()->ErrorPath());
}

//--- deconstructor ----------------------------------------------------------//

CCPCustomerProperties::~CCPCustomerProperties()
{
    if (m_pCustomer)
        delete m_pCustomer;
}

//--- DoDataExchange ---------------------------------------------------------//

void CCPCustomerProperties::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_CALLGENERAL, m_CButtonCallGeneral);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CCPCustomerProperties, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_CUSTOMER, OnButtonCustomer)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CCPCustomerProperties message handlers (ClassWizard) -------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CCPCustomerProperties::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    if (!GetCustomer())
    {
        CDialogMultiLang::OnCancel();
        return FALSE;
    }

    SetHeader();
    MakeEditable();
    return TRUE;
}

//--- (ClassWizard)OnButtonCustomer ------------------------------------------//

void CCPCustomerProperties::OnButtonCustomer()
{
    if (GetCustomer())
    {
        SetHeader();
        MakeEditable();
    }
}

//--- (ClassWizard)OnOK ------------------------------------------------------//

void CCPCustomerProperties::OnOK()
{
    m_pCustomer->SetSkdAnrufGenerell(m_CButtonCallGeneral.GetCheck());

    if (!m_pCustomer->UpdPropetries())
        MsgBoxOK(m_pCustomer->GetErrorMsg());
    else
       MsgBoxOK(IDP_CUSTOMER_CHANGED);
}

//----------------------------------------------------------------------------//
//--- protected methodes -----------------------------------------------------//
//----------------------------------------------------------------------------//

//--- SetHeader --------------------------------------------------------------//

void CCPCustomerProperties::SetHeader()
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

bool CCPCustomerProperties::GetCustomer()
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

//--- GetCustomer ------------------------------------------------------------//

void CCPCustomerProperties::MakeEditable()
{
    m_CButtonCallGeneral.SetCheck(m_pCustomer->GetSkdAnrufGenerell());
}

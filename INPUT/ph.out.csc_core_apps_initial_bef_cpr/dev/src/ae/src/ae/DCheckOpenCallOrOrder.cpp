// DCheckOpenCallOrOrder.cpp : implementation file
//

#include "stdafx.h"
#include "DOffAuftr.h"
#include "GetNextPhoneCall.h"
#include "DCheckOpenCallOrOrder.h"

#define AEOPORD_NO_TASKS    1       //Timeridentifikation
#define AEOPORD_AKT_ZEIT    60000   //eine Minute

/////////////////////////////////////////////////////////////////////////////
// CDCheckOpenCallOrOrder dialog


CDCheckOpenCallOrOrder::CDCheckOpenCallOrOrder(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCheckOpenCallOrOrder::IDD, pParent)
{
    m_CText = _T("");
    m_OrderNr    = 0;
    m_CustomerNr = 0;
    m_VZNr       = 0;
    m_bCancel    = false;
}

void CDCheckOpenCallOrOrder::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_BALKEN, m_StaticBalken);
    DDX_Control(pDX, IDC_STATIC_TEXT, m_StaticText);
    DDX_Text(pDX, IDC_STATIC_TEXT, m_CText);
}

BEGIN_MESSAGE_MAP(CDCheckOpenCallOrOrder, CDialogMultiLang)
    ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCheckOpenCallOrOrder message handlers

void CDCheckOpenCallOrOrder::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

void CDCheckOpenCallOrOrder::OnOK()
{
    if (Order())
    {
        CDialogMultiLang::OnOK();
        return;
    }
    if (m_bCancel)
    {
        CDialogMultiLang::OnCancel();
        return;
    }
    SetOrderIsPossible(FALSE);
}

BOOL CDCheckOpenCallOrOrder::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    if (Order())
    {
        CDialogMultiLang::OnOK();
        return TRUE;
    }
    if (m_bCancel)
    {
        CDialogMultiLang::OnCancel();
        return TRUE;
    }
    SetOrderIsPossible(FALSE);
    SetTimer(AEOPORD_NO_TASKS, AEOPORD_AKT_ZEIT , NULL);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//sind offene Auftraege/Rufe vorhanden (ohne Dialog)
BOOL CDCheckOpenCallOrOrder::IsOrder()
{
    m_OrderNr    = 0;
    m_CustomerNr = 0;

    if (AeGetApp()->IsAnrufPlan())
    {
        return IsCallOrder() || IsOpenOrder() ? TRUE : FALSE;
    }

    return IsOpenOrder() || IsCallOrder() ? TRUE : FALSE;
}

//Versuch Auftraege/Rufe zu bearbeiten
BOOL CDCheckOpenCallOrOrder::Order()
{
    m_OrderNr    = 0;
    m_CustomerNr = 0;

    if (AeGetApp()->IsAnrufPlan())
    {
        return CallOrder() || OpenOrder() ? TRUE : FALSE;
    }

    return OpenOrder() || CallOrder() ? TRUE : FALSE;
}


BOOL CDCheckOpenCallOrOrder::IsOpenOrder()
{
    CDOffAuftr dlgOffAuftr;
    dlgOffAuftr.m_VzNr = AeGetApp()->VzNr();
    dlgOffAuftr.m_RegionNr = AeGetApp()->VzNr();
    dlgOffAuftr.GetNextOpenOrder();

    return dlgOffAuftr.GetAufNr() ? TRUE : FALSE;
}

BOOL CDCheckOpenCallOrOrder::OpenOrder()
{
    if (m_bCancel)
        return FALSE;

    CDOffAuftr dlgOffAuftr;
    dlgOffAuftr.m_VzNr = AeGetApp()->VzNr();
    dlgOffAuftr.m_RegionNr = AeGetApp()->VzNr();
    dlgOffAuftr.GetNextOpenOrder();
    if (!dlgOffAuftr.GetAufNr())
    {
        return FALSE;
    }
    if (!AeGetApp()->IsFastOpenOrder())
    {
        dlgOffAuftr.m_Geraet = AeGetApp()->Geraet();
        if (dlgOffAuftr.DoModal() != IDOK)
        {
            m_bCancel = TRUE;
            return FALSE;
        }
    }
    if (dlgOffAuftr.GetAufNr())
    {
        m_OrderNr = dlgOffAuftr.GetAufNr();
        return TRUE;
    }

    return FALSE;
}

BOOL CDCheckOpenCallOrOrder::IsCallOrder()
{
    GetNextPhoneCall getNextPhoneCall;
    if (AeGetApp()->IsNoParaCall())
        getNextPhoneCall.NoParaCalls();

    return getNextPhoneCall.IsNextCall() == NO_CUSTOMER ? FALSE : TRUE;
}

BOOL CDCheckOpenCallOrOrder::CallOrder()
{
    if (m_bCancel || !IsCallOrder())
    {
        return FALSE;
    }

    GetNextPhoneCall getNextPhoneCall;
    if (AeGetApp()->IsNoParaCall())
    {
        getNextPhoneCall.NoParaCalls();
    }
    if (getNextPhoneCall.GetCall() != NO_CUSTOMER)
    {
        m_CustomerNr = getNextPhoneCall.GetKndNum();
        m_VZNr = getNextPhoneCall.GetKndVZ();
        return TRUE;
    }

    if (getNextPhoneCall.IsCancel())
    {
        m_bCancel = TRUE;
    }
    return FALSE;
}

void CDCheckOpenCallOrOrder::SetOrderIsPossible(BOOL bIsPossible)
{
    if (bIsPossible)
    {
        GetDlgItem(IDC_STATIC_BALKEN)->ShowWindow(SW_SHOW);
        GetDlgItem(IDOK)->EnableWindow();
        GetDlgItem(IDC_STATIC_TEXT_STATUS)->SetWindowText(CResString::ex().getStrTblText(AETXT_NEW_ORDERS));
        GetDlgItem(IDOK)->SetFocus();
    }
    else
    {
        GetDlgItem(IDC_STATIC_BALKEN)->ShowWindow(SW_HIDE);
        GetDlgItem(IDCANCEL)->SetFocus();
        GetDlgItem(IDOK)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_TEXT_STATUS)->SetWindowText(CResString::ex().getStrTblText(AETXT_NO_NEW_ORDERS));
    }
}

void CDCheckOpenCallOrOrder::OnTimer(UINT nIDEvent)
{
    if (IsOrder())
    {
        SetOrderIsPossible();
    }
    else
    {
        SetOrderIsPossible(FALSE);
    }

    CDialogMultiLang::OnTimer(nIDEvent);
}

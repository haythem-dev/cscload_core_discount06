// DConnect.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DConnect.h"

// CDConnect-Dialogfeld

IMPLEMENT_DYNAMIC(CDConnect, CDialog)
CDConnect::CDConnect(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDConnect::IDD, pParent)
{
}

CDConnect::~CDConnect()
{
}

void CDConnect::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDConnect, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_BACK, OnBnClickedButtonBack)
END_MESSAGE_MAP()


// CDConnect-Meldungshandler

BOOL CDConnect::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    AeGetApp()->ConnectWnd = GetSafeHwnd();

    GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
    GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDConnect::OnBnClickedOk()
{
    TRACE("CDConnect::OnBnClickedOk\n");
    AeGetApp()->m_AeTrace.WriteTrace("", "", "CDConnect::OnBnClickedOk\n");

    AeGetApp()->m_ProCenter.Transfer();
    CDialogMultiLang::OnOK();
}

void CDConnect::OnBnClickedButtonBack()
{
    TRACE("CDConnect::OnBnClickedButtonBack\n");
    AeGetApp()->m_AeTrace.WriteTrace("", "", "CDConnect::OnBnClickedButtonBack\n");

    AeGetApp()->m_ProCenter.ReconnectCall();
    CDialogMultiLang::OnOK();
}

BOOL CDConnect::DestroyWindow()
{
    AeGetApp()->ConnectWnd = NULL;

    return CDialogMultiLang::DestroyWindow();
}

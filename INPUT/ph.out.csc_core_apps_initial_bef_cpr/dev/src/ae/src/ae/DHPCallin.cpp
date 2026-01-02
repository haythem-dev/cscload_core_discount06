// DHPCallin.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DHPCallin.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDHPCallin


CDHPCallin::CDHPCallin(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDHPCallin::IDD, pParent)
    , m_csCaption(_T(""))
    , m_csOtherBranch(_T(""))
{
    m_csApo = _T("");
    m_csOrt = _T("");
}

void CDHPCallin::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_STATIC_APO, m_csApo);
    DDX_Text(pDX, IDC_STATIC_ORT, m_csOrt);
    DDX_Text(pDX, IDC_STATIC_CAPTION, m_csCaption);
    DDX_Text(pDX, IDC_STATIC_OTHER_BRANCH, m_csOtherBranch);
}


BEGIN_MESSAGE_MAP(CDHPCallin, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDHPCallin

void CDHPCallin::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

void CDHPCallin::OnOK()
{
    AeGetApp()->m_ProCenter.SetHiPathCallActiv(TRUE);
    AeGetApp()->m_ProCenter.SetHiPathOpen(TRUE);
    CDialogMultiLang::OnOK();
}

BOOL CDHPCallin::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    AeGetApp()->CallinWnd = GetSafeHwnd();

    GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
    GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

    if (!m_csOtherBranch.IsEmpty())
    {
        GetDlgItem(IDC_STATIC_OTHER_BRANCH)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_OTHER_BRANCH)->ShowWindow(SW_SHOW);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

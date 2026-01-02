// DCallbackReason.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <callback.h>
#include "DCallbackReason.h"
#include <callbackmaillink.h>


// CDCallbackReason-Dialogfeld

IMPLEMENT_DYNAMIC(CDCallbackReason, CDialog)
CDCallbackReason::CDCallbackReason(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCallbackReason::IDD, pParent)
{
    m_Mailadr = _T("");
    m_Reason = _T("") ;
    m_sPartnerNo = 0;
    m_ReasonNo = 0;
    m_new = FALSE;
    m_sVzNr = 0;
    m_bOnlyMail = FALSE;
    m_ShowOnlyMailChk = true;
}

CDCallbackReason::~CDCallbackReason()
{
}

void CDCallbackReason::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_REASON, m_Reason);
    DDX_Text(pDX, IDC_EDIT_MAIL, m_Mailadr);
    DDX_Check(pDX, IDC_CHECK_ONLY_MAIL, m_bOnlyMail);
}


BEGIN_MESSAGE_MAP(CDCallbackReason, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_MAIL, OnChangeEditMail)
END_MESSAGE_MAP()


// CDCallbackReason-Meldungshandler

BOOL CDCallbackReason::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    if (!m_new)
    {
        GetDlgItem(IDC_EDIT_REASON)->EnableWindow(FALSE);
    }
    short branchNoMail = m_sVzNr;   //zu bearbeitende Filiale
    CCALLBACKMAILLINK callbackMailLink;
    callbackMailLink.SetBranchno(branchNoMail);
    callbackMailLink.Server(AasrvCallbackGetMailLink);
    if (callbackMailLink.GetEnabled() == 1)
    {
        m_ShowOnlyMailChk = false;
        GetDlgItem(IDC_CHECK_ONLY_MAIL)->ShowWindow(SW_HIDE);
    }
    else if (!m_bMainMailAdr && m_Mailadr.IsEmpty())
    {
        GetDlgItem(IDC_CHECK_ONLY_MAIL)->EnableWindow(FALSE);
        m_bOnlyMail = FALSE;
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCallbackReason::OnOK()
{
    UpdateData();
    CCALLBACKREASONS Callbackreasons;
    Callbackreasons.SetBranchno(m_sVzNr);
    Callbackreasons.SetCallbackdivisionno(m_sPartnerNo);
    Callbackreasons.SetCallbackreason(m_Reason);
    Callbackreasons.SetMailinglist(m_Mailadr);
    Callbackreasons.SetReasonno(m_ReasonNo);
    if (m_ShowOnlyMailChk)
    {
        if (m_bOnlyMail && (m_bMainMailAdr || !m_Mailadr.IsEmpty()))
            Callbackreasons.SetSwonlymail(1);
        else
            Callbackreasons.SetSwonlymail(0);
    }
    if (m_new)
    {
        Callbackreasons.InsertWithNewNo();
    }
    else
    {
        Callbackreasons.Update();
    }
    CDialogMultiLang::OnOK();
}

void CDCallbackReason::OnChangeEditMail()
{
   CString CBuf;
   GetDlgItem(IDC_EDIT_MAIL)->GetWindowText(CBuf);
   GetDlgItem(IDC_CHECK_ONLY_MAIL)->EnableWindow(CBuf.IsEmpty() ? FALSE : TRUE);
}

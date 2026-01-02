// DBenKennAend.cpp : implementation file
//

#include "stdafx.h"
#include "DBenKennAend.h"

extern "C" void pwd_crypt( char *orig, char *crypt, int clng );

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBenKennAend dialog


CDBenKennAend::CDBenKennAend(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDBenKennAend::IDD, pParent)
{
    m_CPwdOld = _T("");
    m_CPwdNew1 = _T("");
    m_CPwdNew2 = _T("");
}


void CDBenKennAend::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_PWDNEU2, m_EditPwdNew2);
    DDX_Control(pDX, IDC_EDIT_PWDNEU, m_EditPwdNew1);
    DDX_Text(pDX, IDC_EDIT_PWDALT, m_CPwdOld);
    DDX_Text(pDX, IDC_EDIT_PWDNEU, m_CPwdNew1);
    DDX_Text(pDX, IDC_EDIT_PWDNEU2, m_CPwdNew2);
}


BEGIN_MESSAGE_MAP(CDBenKennAend, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_PWDNEU, OnChangeEditPwdneu)
    ON_EN_CHANGE(IDC_EDIT_PWDNEU2, OnChangeEditPwdneu2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBenKennAend message handlers

BOOL CDBenKennAend::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    if (m_CPwdOld.GetLength() > 0)
    {
        GetDlgItem(IDC_EDIT_PWDNEU)->SetFocus();
        return FALSE;
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDBenKennAend::OnOK()
{
    char p[L_AEPWD_PASSWORD + 1], char_pwd[L_AEPWD_PASSWORD + 1];
    UpdateData();
    CString CPwdOld = GetAeUser().GetPasswd();
    memset(char_pwd, ' ', L_AEPWD_PASSWORD);
    memcpy(char_pwd, m_CPwdOld, m_CPwdOld.GetLength() > L_AEPWD_PASSWORD ? L_AEPWD_PASSWORD : m_CPwdOld.GetLength());
    char_pwd[L_AEPWD_PASSWORD] = '\0';
    pwd_crypt(char_pwd, p, L_AEPWD_PASSWORD);
    AllgEntfSpaces(p);
    m_CPwdOld = p;
    if (m_CPwdOld != CPwdOld)
    {
        MsgBoxOK(IDP_WRONG_PWD);
        GetDlgItem(IDC_EDIT_PWDALT)->SetFocus();
        return;
    }
    if (m_CPwdNew1 != m_CPwdNew2)
    {
        MsgBoxOK(IDP_KEIN_GL_PWD);
        GetDlgItem(IDC_EDIT_PWDNEU)->SetFocus();
        return;
    }
    if (m_CPwdNew1 == "xxxxxxxx")
    {
        MsgBoxOK(IDP_KEIN_GUELT_PWD);
        GetDlgItem(IDC_EDIT_PWDNEU)->SetFocus();
        return;
    }
    if (m_CPwdNew1.GetLength() < 6)
    {
        MsgBoxOK(IDP_MIND_SECHS_ZEICH);
        GetDlgItem(IDC_EDIT_PWDNEU)->SetFocus();
        return;
    }
    memset(char_pwd, ' ', L_AEPWD_PASSWORD);
    memcpy(char_pwd, m_CPwdNew1, m_CPwdNew1.GetLength() > L_AEPWD_PASSWORD ? L_AEPWD_PASSWORD : m_CPwdNew1.GetLength());
    char_pwd[L_AEPWD_PASSWORD] = '\0';
    pwd_crypt(char_pwd, p, L_AEPWD_PASSWORD);
    AllgEntfSpaces(p);
    BeginWaitCursor();
    GetAeUser().SetPasswd(p);
    EndWaitCursor();
    CDialogMultiLang::OnOK();
}

void CDBenKennAend::OnChangeEditPwdneu()
{
    AllgLaengeKontr(&m_EditPwdNew1, L_AEPWD_PASSWORD,AeGetApp()->Modus());
}

void CDBenKennAend::OnChangeEditPwdneu2()
{
    AllgLaengeKontr(&m_EditPwdNew2, L_AEPWD_PASSWORD,AeGetApp()->Modus());
}

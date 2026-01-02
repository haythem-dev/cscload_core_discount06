// DKontrPwd.cpp : implementation file
//

#include "stdafx.h"
#include <filinf.h>
#include "DKontrPwd.h"

extern "C" void pwd_crypt( char *orig, char *crypt, int clng );

/////////////////////////////////////////////////////////////////////////////
// CDKontrPwd dialog


CDKontrPwd::CDKontrPwd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDKontrPwd::IDD, pParent)
{
    m_Pwd = "";
}


void CDKontrPwd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_PWD, m_EditPwd);
}


BEGIN_MESSAGE_MAP(CDKontrPwd, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDKontrPwd message handlers

BOOL CDKontrPwd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDKontrPwd::OnOK()
{
    CString Pwd;
    char p[L_AEPWD_PASSWORD + 1], char_pwd[L_AEPWD_PASSWORD + 1];
    GetDlgItem(IDC_EDIT_PWD)->GetWindowText(Pwd);
    memset(char_pwd, ' ', L_AEPWD_PASSWORD);
    memcpy(char_pwd, Pwd, Pwd.GetLength() > L_AEPWD_PASSWORD ? L_AEPWD_PASSWORD : Pwd.GetLength());
    char_pwd[L_AEPWD_PASSWORD] = '\0';
    pwd_crypt(char_pwd, p, L_AEPWD_PASSWORD);
    AllgEntfSpaces(p);
    if (strcmp(p, m_Pwd) != 0)
    {
        MsgBoxOK(IDP_UNGUELT_PWD);
        GotoDlgCtrl(&m_EditPwd);
        return;
    }

    CDialogMultiLang::OnOK();
}

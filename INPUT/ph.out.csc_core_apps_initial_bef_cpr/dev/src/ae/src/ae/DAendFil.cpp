// DAendFil.cpp : implementation file
//

#include "stdafx.h"
#include "DAendFil.h"

/////////////////////////////////////////////////////////////////////////////
// CDAendFil dialog


CDAendFil::CDAendFil(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAendFil::IDD, pParent)
{
}

void CDAendFil::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_FILIALEN, m_ListBox);
}


BEGIN_MESSAGE_MAP(CDAendFil, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAendFil message handlers

BOOL CDAendFil::OnInitDialog()
{
    CString Server, ServerName, CStrSrv, CStrSrvName;

    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    int anz = AeGetApp()->GetProfileInt("AeServer", "NumberOfServers", 0);

    //Ueberpruefung, ob ein Servereintrag existiert
    if (anz < 1)
    {
        MsgBoxOK(IDP_KEIN_AAPSRV_DEF);
        CDialogMultiLang::OnOK();  //alter server ist noch aktiv
        return FALSE;
    }

    for (int i = 1; i <= anz; i++)
    {
        CStrSrv.Format("Server%d", i);
        CStrSrvName.Format("ServerName%d", i);
        Server = AeGetApp()->GetProfileString("AeServer", CStrSrv);
        ServerName = AeGetApp()->GetProfileString("AeServer", CStrSrvName);
        if (Server.IsEmpty() || ServerName.IsEmpty())
        {
            MsgBoxOK(IDP_KEIN_AAPSRV_DEF);
            CDialogMultiLang::OnOK();   //alter server ist noch aktiv
            return FALSE;
        }
        m_ListBox.AddString(ServerName);
    }
    m_ListBox.SetCurSel(0);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAendFil::OnOK()
{
    CString CStrSrv,CStrBranch;

    CStrSrv.Format("Server%d", m_ListBox.GetCurSel() + 1);
    CString Server = AeGetApp()->GetProfileString("AeServer", CStrSrv);
    CStrBranch.Format("Branch%d", m_ListBox.GetCurSel() + 1);
    short FilialNr = static_cast<short>(atoi(AeGetApp()->GetProfileString("AeServer", CStrBranch)));
    if (Server.IsEmpty())
    {
        MsgBoxOK(IDP_KEIN_AAPSRV_DEF);
        return ;
    }
    if (AeGetApp()->ChangeBranch(Server, FilialNr) < 0)
    {
        GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
        return;
    }
    CDialogMultiLang::OnOK();
}

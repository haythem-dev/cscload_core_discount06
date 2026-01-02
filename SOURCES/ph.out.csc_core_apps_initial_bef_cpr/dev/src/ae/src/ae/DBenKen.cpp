// dbenken.cpp : implementation file
//

#include "stdafx.h"
#include "MainFrm.h"
#include "DBenKen.h"
#include <filinf.h>
#include <pxverbund_version.h>
#include "aeconnection.h"

extern "C" void pwd_crypt( char *orig, char *crypt, int clng );

/////////////////////////////////////////////////////////////////////////////
// CDBenKen dialog

CDBenKen::CDBenKen(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDBenKen::IDD, pParent)
    , m_CLang(_T(""))
{
    m_edit_kennung = "";
    m_edit_pwd = "";
    m_CFili = _T("");
    m_FilialNr = 0;
    mbServerOpen = FALSE;
}

void CDBenKen::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_FILI, m_ComboFili);
    DDX_Control(pDX, IDC_EDIT_PWD, m_EditPwd);
    DDX_Control(pDX, IDC_EDIT_KENNUNG, m_EditKennung);
    DDX_Text(pDX, IDC_EDIT_KENNUNG, m_edit_kennung);
    DDV_MaxChars(pDX, m_edit_kennung, 8);
    DDX_Text(pDX, IDC_EDIT_PWD, m_edit_pwd);
    DDV_MaxChars(pDX, m_edit_pwd, 8);
    DDX_CBString(pDX, IDC_COMBO_FILI, m_CFili);
    DDX_Control(pDX, IDC_COMBO_LANG, m_ComboLang);
    DDX_CBString(pDX, IDC_COMBO_LANG, m_CLang);
}

BEGIN_MESSAGE_MAP(CDBenKen, CDialogMultiLang)
    ON_BN_CLICKED(ID_ENDE, OnClickedEnde)
    ON_CBN_SELCHANGE(IDC_COMBO_FILI, OnSelchangeComboFili)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBenKen message handlers

void CDBenKen::OnOK()
{
    UpdateData(TRUE);
    if (GetFocus() == GetDlgItem(IDC_EDIT_KENNUNG))
    {
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_PWD));
        return;
    }

    CString CStrSrv, CStrSrvName, CStrBranch, CStrPortnr;

    CStrSrv.Format("Server%d", m_ComboFili.GetCurSel() + 1);
    CStrSrvName.Format("ServerName%d", m_ComboFili.GetCurSel() + 1);
    CStrBranch.Format("Branch%d", m_ComboFili.GetCurSel() + 1);
    CStrPortnr.Format("Portnr%d", m_ComboFili.GetCurSel() + 1);
    m_Server = AeGetApp()->GetProfileString("AeServer", CStrSrv);
    m_ServerName = AeGetApp()->GetProfileString("AeServer", CStrSrvName);
    m_VzNr = static_cast<short>(atoi(AeGetApp()->GetProfileString("AeServer", CStrBranch)));
    m_FilialNr = static_cast<short>(atoi(AeGetApp()->GetProfileString("AeServer", CStrBranch)));
    m_PortNr = atol(AeGetApp()->GetProfileString("AeServer", CStrPortnr));
    AeGetApp()->PortNr = m_PortNr;
    if (m_Server.IsEmpty())
    {
        MsgBoxOK(IDP_KEIN_AAPSRV_DEF);
        return;
    }

    if (!mbServerOpen) //Verbindung zum Server aufbauen
    {
        char error_msg[81] = { 0 };

        if (OpenAEConnection(m_Server, m_PortNr, error_msg) != 0)
        {
            MsgBoxOK(IDP_KEIN_AA_VERB);
            CDialogMultiLang::OnCancel();
            return;
        }
        if (!AeGetApp()->VersionsPruefung())
        {
            CDialogMultiLang::OnCancel();
            return;
        }

        mbServerOpen = TRUE;
    }


    CAEPWD  pwd;
    UpdateData();
    pwd.s.FILIALNR = m_FilialNr;
    AllgStrCopy(pwd.s.USERNAME, m_edit_kennung, L_AEPWD_USERNAME);
    BeginWaitCursor();
    pwd.Server(AafilReadpasswd);
    EndWaitCursor();
    AllgEntfSpaces(pwd.s.PASSWORD);
    if (pwd.rc != SRV_OK)
    {
        MsgBoxOK(IDP_UNGUELT_USER);
        GotoDlgCtrl(&m_EditKennung);
        return;
    }
    char p[L_AEPWD_PASSWORD + 1], char_pwd[L_AEPWD_PASSWORD + 1];
    AllgEntfSpaces(pwd.s.PASSWORD);
    AllgEntfSpaces(pwd.s.USERNAME);
    AllgEntfSpaces(pwd.s.TERMID);
    AllgEntfSpaces(pwd.s.AGENTID);
    memset(char_pwd, ' ', L_AEPWD_PASSWORD);
    memcpy(char_pwd, m_edit_pwd, m_edit_pwd.GetLength() > L_AEPWD_PASSWORD ? L_AEPWD_PASSWORD : m_edit_pwd.GetLength());
    char_pwd[L_AEPWD_PASSWORD] = '\0';
    pwd_crypt(char_pwd, p, L_AEPWD_PASSWORD);
    AllgEntfSpaces(p);
    if (strcmp(p, pwd.s.PASSWORD) != 0)
    {
        MsgBoxOK(IDP_UNGUELT_PWD);
        GotoDlgCtrl(&m_EditPwd);
        return;
    }
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {   // Werte setzen
        RegSetValueEx(hKey, KEY_NAME_USER, 0, REG_SZ,
            (BYTE*)(LPCSTR)m_edit_kennung, m_edit_kennung.GetLength());
        RegCloseKey(hKey);
    }
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {   // Werte setzen
        RegSetValueEx(hKey, KEY_NAME_BRANCH, 0, REG_SZ,
            (BYTE*)(LPCSTR)m_Server, m_Server.GetLength());
        RegCloseKey(hKey);
    }
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {   // Werte setzen
        RegSetValueEx(hKey, KEY_NAME_BRANCHNAME, 0, REG_SZ,
            (BYTE*)(LPCSTR)m_ServerName, m_ServerName.GetLength());
        RegCloseKey(hKey);
    }
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {   // Werte setzen
        RegSetValueEx(hKey, KEY_NAME_LANGUAGE, 0, REG_SZ,
            (BYTE*)(LPCSTR)m_CLang, m_CLang.GetLength());
        RegCloseKey(hKey);
    }
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {   // Werte setzen
        CString Portnr;
        Portnr.Format("%d", m_PortNr);
        RegSetValueEx(hKey, KEY_NAME_PORTNR, 0, REG_SZ,
            (BYTE*)(LPCSTR)Portnr, Portnr.GetLength());
        RegCloseKey(hKey);
    }
#ifdef _DEBUG
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {   // Werte setzen
        RegSetValueEx(hKey, KEY_NAME_PASSWD, 0, REG_SZ,
            (BYTE*)(LPCSTR)m_edit_pwd, m_edit_pwd.GetLength());
        RegCloseKey(hKey);
    }
#endif
    m_AeUser = pwd.s;
    AeGetApp()->Language = m_CLang;
    CDialogMultiLang::OnOK();
}

void CDBenKen::OnClickedEnde()
{
    OnOK();
}

BOOL CDBenKen::OnInitDialog()
{
    int anz;
    int anzsprachen;
    CString Server, ServerName, CStrSrv, CStrSrvName, CStrSprache, Sprache;
    CDialogMultiLang::OnInitDialog();

    GetDlgItem(IDC_STATIC_VERSION_NO)->SetWindowText(CSC_CORE_APPLICATIONS_VERSION);

    char szBuffer[50];
    DWORD  len = sizeof(szBuffer);
    if (RegOpenKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        if (RegQueryValueEx(hKey, KEY_NAME_USER, 0, NULL, (BYTE*)szBuffer,
            &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len - 1] = '\0';
            m_edit_kennung = szBuffer;
        }
        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_BRANCH, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len - 1] = '\0';
            m_Server = szBuffer;
        }
        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_BRANCHNAME, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len - 1] = '\0';
            m_ServerName = szBuffer;
        }
        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_LANGUAGE, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len - 1] = '\0';
            m_Language = szBuffer;
        }
        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_PORTNR, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len - 1] = '\0';
            m_PortNr = atol(szBuffer);
        }
#ifdef _DEBUG
        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_PASSWD, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte setzen
            szBuffer[len - 1] = '\0';
            m_edit_pwd = szBuffer;
        }
#endif
        RegCloseKey(hKey);
    }
    anz = AeGetApp()->GetProfileInt("AeServer", "NumberOfServers", 0);

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
        m_ComboFili.AddString(ServerName);
        if (m_ServerName.IsEmpty())
        {
            if (Server == m_Server)
                m_ComboFili.SetCurSel(i - 1);
        }
        else
        {
            if (ServerName == m_ServerName)
                m_ComboFili.SetCurSel(i - 1);
        }
    }
    anzsprachen = AeGetApp()->GetProfileInt("AeServer", "AnzSprachen", 0);
    for (int i = 1; i <= anzsprachen; i++)
    {
        CStrSprache.Format("Sprache%d", i);
        Sprache = AeGetApp()->GetProfileString("AeServer", CStrSprache);
        AeGetApp()->SetSprachen(Sprache);
        m_ComboLang.AddString(Sprache);
        if (m_Language.IsEmpty())
        {
            m_Language = Sprache;
            m_ComboLang.SetCurSel(0);
        }
        else
        {
            if (Sprache == m_Language)
                m_ComboLang.SetCurSel(i - 1);
        }
    }
    AeGetApp()->Modus = m_Language == "BG" ? 1 : 0;

    UpdateData(FALSE);
    CenterWindow();

#ifdef _NEWHIPATH
    GetDlgItem(IDC_STATIC_PROCENTER)->SetWindowText("New Procenter");
#endif

    if (!m_edit_kennung.IsEmpty())
    {
        GetDlgItem(IDC_EDIT_PWD)->SetFocus();
        return FALSE;
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDBenKen::OnSelchangeComboFili()
{
    if (mbServerOpen) //Verbindung zum Server schliessen
    {
        char error_msg[81];
        CloseServer(error_msg);
        mbServerOpen = FALSE;
    }
}


HBRUSH CDBenKen::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);
#ifdef _NEWHIPATH
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_PROCENTER)
        pDC->SetTextColor(RGB(0, 200, 0));
#endif
    return hbr;
}

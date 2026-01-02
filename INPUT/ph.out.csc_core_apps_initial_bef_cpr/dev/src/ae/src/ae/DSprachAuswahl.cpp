// DSprachAuswahl.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MainFrm.h"
#include "DSprachAuswahl.h"


// CDSprachAuswahl-Dialogfeld

IMPLEMENT_DYNAMIC(CDSprachAuswahl, CDialog)
CDSprachAuswahl::CDSprachAuswahl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSprachAuswahl::IDD, pParent)
    , m_CSprache(_T(""))
{
}

CDSprachAuswahl::~CDSprachAuswahl()
{
}

void CDSprachAuswahl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_SPRACHE, m_Combo_Sprache);
    DDX_CBString(pDX, IDC_COMBO_SPRACHE, m_CSprache);
}


BEGIN_MESSAGE_MAP(CDSprachAuswahl, CDialogMultiLang)
END_MESSAGE_MAP()


// CDSprachAuswahl-Meldungshandler

BOOL CDSprachAuswahl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CString Sprache = AeGetApp()->Language();
    for (int i = 0; i < AeGetApp()->GetAnzSprachen(); i++)
    {
        m_Combo_Sprache.AddString(AeGetApp()->GetSprachen(i));
    }
    m_Combo_Sprache.SelectString(-1, Sprache);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDSprachAuswahl::OnOK()
{
    UpdateData();

    if (m_CSprache != AeGetApp()->Language())
    {
        AeGetApp()->ReadLanguage(m_CSprache);
        HKEY hKey;
        if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
        {
            // Werte setzen
            RegSetValueEx(hKey, KEY_NAME_LANGUAGE, 0, REG_SZ, (BYTE*)(LPCSTR)m_CSprache, m_CSprache.GetLength());
            RegCloseKey(hKey);
        }
        AeGetApp()->Language = m_CSprache;
    }
    CDialogMultiLang::OnOK();
}

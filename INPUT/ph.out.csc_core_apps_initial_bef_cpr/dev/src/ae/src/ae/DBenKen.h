#pragma once
// dbenken.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBenKen dialog

class CDBenKen : public CDialogMultiLang
{
// Construction
public:
    AEPWD m_AeUser;
    CDBenKen(CWnd* pParent = NULL); // standard constructor
    CString m_Server;
    CString m_ServerName;
    CString m_Language;
    short m_FilialNr;
    short m_VzNr;
    long  m_PortNr;

    enum { IDD = IDD_BEN_KENNUNG };
    CComboBox m_ComboFili;
    CEdit m_EditPwd;
    CEdit m_EditKennung;
    CString m_edit_kennung;
    CString m_edit_pwd;
    CString m_CFili;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    BOOL mbServerOpen;
    HKEY hKey;

    virtual void OnOK();
    afx_msg void OnClickedEnde();
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeComboFili();
    DECLARE_MESSAGE_MAP()

public:
    CComboBox m_ComboLang;
    CString m_CLang;
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

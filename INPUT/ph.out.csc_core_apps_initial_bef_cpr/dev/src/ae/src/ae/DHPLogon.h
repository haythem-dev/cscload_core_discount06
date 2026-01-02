#pragma once

// DHPLogon.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDHPLogon

class CDHPLogon : public CDialogMultiLang
{
// Konstruktion
public:
    CDHPLogon(CWnd* pParent = NULL);   // Standardkonstruktor

    enum { IDD = IDD_HP_LOGON };
    CEdit m_edit_Passwd;
    CEdit m_edit_NST;
    CEdit m_edit_HPBRANCH;
    CEdit m_edit_ID;
    CString m_csID;
    CString m_csNST;
    CString m_csHPBRANCH;
    CString m_csPasswd;
    CButton m_CBHiPath;
    CButton m_CBLync;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditHPBranch();
    afx_msg void OnBnClickedCheckHipath();
    afx_msg void OnBnClickedCheckLync();
    DECLARE_MESSAGE_MAP()
};

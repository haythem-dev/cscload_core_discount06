#pragma once

// DSonderFahrt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDSonderFahrt dialog

class CDSonderFahrt : public CDialogMultiLang
{
// Construction
public:
    CDSonderFahrt(CWnd* pParent = NULL);   // standard constructor
    void NoPrefix();

    enum { IDD = IDD_AE_SONDER_FAHRT };
    CEdit   m_EditSonst;
    CString m_CSonst;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CString m_CText;

    afx_msg void OnChangeEditSonst();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnRadio31();
    afx_msg void OnRadio32();
    afx_msg void OnRadio33();
    afx_msg void OnRadio34();
    afx_msg void OnRadio35();
    afx_msg void OnRadio39();
    afx_msg void OnRadio40();
    afx_msg void OnRadio41();
    afx_msg void OnRadio42();
    afx_msg void OnRadio36();
    afx_msg void OnRadio37();
    afx_msg void OnRadio38();
    afx_msg void OnRadio43();
    afx_msg void OnRadio45();
    afx_msg void OnRadio46();
    afx_msg void OnRadio47();
    afx_msg void OnRadio99();
    DECLARE_MESSAGE_MAP()
};

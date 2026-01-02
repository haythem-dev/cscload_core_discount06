#pragma once

// CExtraFahrt.h : header file
//
#include <eilbotendruck.h>

/////////////////////////////////////////////////////////////////////////////
// CExtraFahrt dialog

class CDExtraFahrt : public CDialogMultiLang
{
// Construction
public:
    CDExtraFahrt(CWnd* pParent = NULL);   // standard constructor
    void NoPrefix();

    enum { IDD = IDD_AE_EXTRA_TOUR };
    CEdit   m_EditSonst;
    CString m_CSonst;
    CString m_AArt;
    CEXTRATOURREASONS m_extrareasons;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CString m_CText;
    CWnd* m_ButtonTab1[15];

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditSonst();
    afx_msg void OnRadio31();
    afx_msg void OnRadio32();
    afx_msg void OnRadio33();
    afx_msg void OnRadio34();
    afx_msg void OnRadio35();
    afx_msg void OnRadio36();
    afx_msg void OnRadio37();
    afx_msg void OnRadio38();
    afx_msg void OnRadio39();
    afx_msg void OnRadio40();
    afx_msg void OnRadio41();
    afx_msg void OnRadio42();
    afx_msg void OnRadio43();
    afx_msg void OnRadio44();
    afx_msg void OnRadio45();
    DECLARE_MESSAGE_MAP()
};

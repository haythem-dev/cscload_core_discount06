#pragma once


// CDSeperateOrder-Dialogfeld

class CDSeperateOrder : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDSeperateOrder)

public:
    CDSeperateOrder(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDSeperateOrder();

    enum { IDD = IDD_AE_SEPERATE };
    CButton m_CB_1;
    CButton m_CB_2;
    CButton m_CB_3;
    CButton m_CB_4;
    CButton m_CB_5;
    CButton m_CB_99;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCheck1();
    afx_msg void OnBnClickedCheck2();
    afx_msg void OnBnClickedCheck3();
    afx_msg void OnBnClickedCheck4();
    afx_msg void OnBnClickedCheck5();
    afx_msg void OnBnClickedCheck99();
    DECLARE_MESSAGE_MAP()

    bool m_bChanged;
    bool m_bExist;
    CSEPORDER m_Sep;
};

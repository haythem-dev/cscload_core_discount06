#pragma once


// CDDelayedCst-Dialogfeld

class CDDelayedCst : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDDelayedCst)

public:
    CDDelayedCst(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDDelayedCst();

    enum { IDD = IDD_AE_DELAYED_CST };
    short m_sVzNr;
    short m_sBranchno;
    long m_lKndNr;
    CEdit m_Edit_KdNr;
    CString m_CKdNr;
    CListCtrl m_ListCtl;
    CDELAYEDCST m_Cst;
    CStringArray m_Tagtab;
    CString m_CMC;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    afx_msg void OnEnChangeEditKdnr();
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButtonIns();
    afx_msg void OnBnClickedButtonUpd();
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnBnClickedOk();

    DECLARE_MESSAGE_MAP()

    void GetPage();     // List-Box mit Eintraegen versorgen
};

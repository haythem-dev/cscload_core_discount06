#pragma once


// CDDelayedArt-Dialogfeld

class CDDelayedArt : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDDelayedArt)

public:
    CDDelayedArt(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDDelayedArt();

    enum { IDD = IDD_AE_DELAYED_ART };
    CButton m_CB_1;
    CButton m_CB_2;
    CButton m_CB_3;
    CButton m_CB_4;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCheck1();
    afx_msg void OnBnClickedCheck2();
    afx_msg void OnBnClickedCheck3();
    afx_msg void OnBnClickedCheck4();
    DECLARE_MESSAGE_MAP()

protected:
    bool m_bChanged;
    bool m_bExist;
    CDELAYEDART m_Art;
};

#pragma once


// CDOffenAuft-Dialogfeld

class CDOffenAuft : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDOffenAuft)

public:
    CDOffenAuft(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDOffenAuft();

// Dialogfelddaten
    enum { IDD = IDD_AE_OFFEN_AUFT };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()

public:
    CEdit m_edit_AArt;
    CString m_cAArt;
    CListCtrl m_ListCtl;
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonDruck();
    afx_msg void OnEnChangeEditAart();
    afx_msg void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
};

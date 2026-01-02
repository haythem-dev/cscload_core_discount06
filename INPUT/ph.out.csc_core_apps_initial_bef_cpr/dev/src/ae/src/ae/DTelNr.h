#pragma once


// CDTelNr-Dialogfeld

class CDTelNr : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDTelNr)

public:
    CDTelNr(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDTelNr();

    enum { IDD = IDD_AE_TELNR };
    CEdit m_edit_Kundennr;
    CString m_CKundennr;
    CEdit m_edit_VZ;
    CString m_CVZ;
    CListCtrl m_ListCtl;
    CEdit m_edit_Telnr;
    CString m_CTelnr;
    long m_lKdnr;
    short m_sVznr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    afx_msg void OnBnClickedButtonIns();
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnBnClickedButtonKndWahl();
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangeEditKundennr();
    afx_msg void OnEnChangeEditVz();
    afx_msg void OnEnChangeEditTelnr();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

private:
    BOOL GetPage(int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    CCUSTPHON m_CustPhon;
};

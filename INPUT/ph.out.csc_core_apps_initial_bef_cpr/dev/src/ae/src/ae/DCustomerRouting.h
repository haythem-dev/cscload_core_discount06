#pragma once


// CDCustomerRouting-Dialogfeld

class CDCustomerRouting : public CDialogMultiLang, CPageBrowser
{
    DECLARE_DYNAMIC(CDCustomerRouting)

public:
    CDCustomerRouting(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDCustomerRouting();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual void OnOK();
    virtual BOOL OnInitDialog();

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);      // List-Box mit Eintraegen versorgen

    afx_msg void OnEnChangeEditIdf();
    afx_msg void OnEnChangeEditVz();
    afx_msg void OnBnClickedButtonDruck();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedButtonKnd();
    afx_msg void OnBnClickedButtonBearb();
    afx_msg void OnBnClickedButtonNeu();
    afx_msg void OnBnClickedButtonDel();

    enum { IDD = IDD_AE_CUSTOMER_ROUTING };

    DECLARE_MESSAGE_MAP()

private:
    CCUSTROUT m_Routing;
    CStringArray m_Tagtab;
    CEdit m_Edit_IDF;
    CString m_CIDF;
    CString m_CMC;
    CEdit m_Edit_VZ;
    CString m_CVZ;
    CListCtrl m_ListCtl;
    long SelListPos();                          // ArtikelNr des ausgewählten Art. best.
    void CloseCursor();                         // DB-Cursor schliessen
    int m_iAnzZeilen;
    long m_lKdnr;
    short m_sVznr;
};

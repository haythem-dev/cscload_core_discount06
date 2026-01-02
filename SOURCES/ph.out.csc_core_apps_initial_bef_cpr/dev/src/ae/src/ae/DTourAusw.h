// DTourAusw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDTourAusw dialog

class CDTourAusw : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDTourAusw(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_TOURUEBERSICHT };
    CEdit m_EditTour;
    CEdit m_EditBezeichnung;
    CEdit m_EditBhf;
    CEdit m_EditZeit;
    CListCtrl m_ListCtl;
    CString m_CZeit;
    CString m_CBhf;
    CString m_CBezeichnung;
    CString m_CTour;

// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    void SelectTour();
    void CloseCursor();                     // DB-Cursor schliessen

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnChangeEditAbzeit();
    afx_msg void OnChangeEditBahnhof();
    afx_msg void OnChangeEditBezeichnung();
    afx_msg void OnChangeEditTour();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};

// DProtNachLief.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDProtNachLief : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDProtNachLief(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_PROT_AEND_NL };
    CEdit m_EditArtNr;
    CEdit m_EditIdfNr;
    CListCtrl m_ListCtl;
    CString m_CIdfNr;
    CString m_CArtNr;

// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    void SelectEintrag();
    void CloseCursor();                     // DB-Cursor schliessen

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonArtnr();
    afx_msg void OnButtonKnd();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};

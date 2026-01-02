// DAnzAeUser.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDAnzAeUser : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDAnzAeUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_ANZ_AE_USER };
    CListCtrl m_ListCtl;
    short m_FilialNr;

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
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
};

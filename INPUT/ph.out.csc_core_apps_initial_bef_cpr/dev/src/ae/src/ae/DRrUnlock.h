// DRrUnlock.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDRrUnlock : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDRrUnlock(CWnd* pParent = NULL);   // standard constructor
    CCALLBACKITEMS m_item;
    CCALLBACKTODO m_todo;
    CCALLBACKTODONEW m_todonew;

// Dialog Data
    enum { IDD = IDD_AE_RR_LOCKED };
    CListCtrl m_ListCtl;

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
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonUnlock();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};

// DUpdTime.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDUpdTime : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDUpdTime(CWnd* pParent = NULL);   // standard constructor

    void SetVzNr(const short sVz) { m_sVzNr = sVz; }
    const short GetVzNr() const { return m_sVzNr; }

// Dialog Data
    enum { IDD = IDD_AE_CALLBACK_TIMES };
    CEdit m_EditTime;
    CEdit m_EditName;
    CListCtrl m_ListCtl;
    CString m_CName;
    CString m_CTime;
    long m_lPartnerNo;  // Partnernumer


// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    void SelectEintrag();
    void CloseCursor();                     // DB-Cursor schliessen
    CStringArray m_saDay;
    CCALLBACKTIME m_Callbacktime;
    short m_sVzNr;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonNewtime();
    afx_msg void OnChangeEditName();
    afx_msg void OnChangeEditTime();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};

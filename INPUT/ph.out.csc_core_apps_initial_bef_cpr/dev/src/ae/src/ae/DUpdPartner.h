// DUpdPartner.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDUpdPartner : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDUpdPartner(CWnd* pParent = NULL);   // standard constructor

    void SetVzNr(const short sVz) { m_sVzNr = sVz; }
    const short GetVzNr() const { return m_sVzNr; }

    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    void SelectEintrag();
    void CloseCursor();                     // DB-Cursor schliessen
    CCALLBACKPARTNER m_Partner;
    short m_sVzNr;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonChange();
    afx_msg void OnButtonDelete();
    afx_msg void OnButtonNew();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    enum { IDD = IDD_AE_CALLBACK_PARTNER };

    DECLARE_MESSAGE_MAP()
};

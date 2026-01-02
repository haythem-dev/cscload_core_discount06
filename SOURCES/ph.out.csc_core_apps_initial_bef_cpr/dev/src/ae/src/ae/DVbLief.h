// DVbLief.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDVbLief : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDVbLief(CWnd* pParent = NULL);   // standard constructor

    CEdit m_EditHaus;
    CEdit m_EditDatum;
    CListCtrl m_ListCtl;
    CString m_CDatum;
    CString m_CHaus;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    void CloseCursor();                     // DB-Cursor schliessen
    long m_lKumMenge;                       // kumulierte Menge
    long m_lKumZeilen;                      // kumulierte Zeilenzahl

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnButtonDruck();
    afx_msg void OnChangeEditDatum();
    afx_msg void OnChangeEditHaus();

    enum { IDD = IDD_AE_VBLIEF };

    DECLARE_MESSAGE_MAP()
};

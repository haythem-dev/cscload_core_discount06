// DSeralog.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDSeralog : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDSeralog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_SERALOG };
    CEdit m_EditZeit;
    CEdit m_EditDatum;
    CEdit m_EditTid;
    CEdit m_EditIdf;
    CListCtrl m_ListCtl;
    CString m_CTid;
    CString m_CDatum;
    CString m_CZeit;
    CString m_CIdf;
    int m_ShowImmediately;
    short m_sVzNr;

// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);      // List-Box mit Eintraegen versorgen
    void SelectEintrag();
    void CloseCursor();                         // DB-Cursor schliessen
    CString datum;                              // zu verarb. Datum
    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonKnd();
    afx_msg void OnChangeEditIdf();
    afx_msg void OnChangeEditTid();
    afx_msg void OnChangeEditDatum();
    afx_msg void OnChangeEditZeit();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDSeralogAuftr dialog

class CDSeralogAuftr : public CDialogMultiLang
{
// Construction
public:
    CDSeralogAuftr(CWnd* pParent = NULL);   // standard constructor

    char m_Filename[30+1];           // Seralog-Dateiname
    short m_sVzNr;

// Dialog Data
    enum { IDD = IDD_AE_SERALOG_AUFTR };
    CEdit   m_LBAuftr;
    CStatic m_StaticStrasse;
    CStatic m_StaticOrt;
    CStatic m_StaticName;
    CStatic m_StaticApo;
    CString m_CApo;
    CString m_CDatum;
    CString m_CName;
    CString m_COrt;
    CString m_CStrasse;
    CString m_CUhr;
    CString m_CAuftr;
    CString m_CTid;
    CString m_CIdf;
    CString m_CListAuftr;

// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    void SetSpace2Sign(char* input);            // ersetzen space durch Sonderzeichen
    CString LinePartition(char* buffer);        // Aufteilen Block in einzelne Satzarten
    // Generated message map functions
    virtual void OnCancel();
    afx_msg void OnButtonDruck();
    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

    DECLARE_MESSAGE_MAP()
};

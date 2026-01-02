// DNachlBearb.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDNachlBearb : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDNachlBearb(CWnd* pParent = NULL); // standard constructor
    CAeDoc* ptrDoc;                     // Zeiger auf das Dokument
    CAeFView* ptrFView;                 // Zeiger auf den View
    CImageList m_ImageSmall;
    CString m_VerbundZeitenKnd;         // Infofeld Verbundzeiten des Kunden
    short m_VzNr;
    long m_lKndNr;
    long m_IdfNr;
    long m_lAuftrNr;
    CString m_AArt;

    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    BOOL InsList(char* kb, struct NACHLART* nachlart, class CStringArray& s);      // List-Box mit Eintraegen versorgen
    void MarkListPosChar(int Letter);
    void MarkListPos(int pos);
    void SelectEintrag();
    void UpdBearbkz(int pos);
    void CloseCursor();                     // DB-Cursor schliessen
    int  selectpos;                         // letzte selection merken

    struct satzadr
    {
        long kdauftragnr;
        long posnr;
        long datum;
        short postyp;
        double preisekaponetto;
        struct satzadr* nextpos;
    };

    struct nachladr
    {
        long artikel_nr;
        struct satzadr* satzpos;
        struct nachladr* folgpos;
    };

    struct nachladr* startpos;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonUpd();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    enum { IDD = IDD_AE_NACHL_BEARB };

    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CDNachlArtAen dialog

class CDNachlArtAen : public CDialogMultiLang
{
// Construction
public:
    CDNachlArtAen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_NACHLART_AEN };
    CEdit   m_EditMenge;
    CString m_CMenge;
    CString m_CBestand;
    CString m_CName;
    CString m_CPzn;
    CString m_CMengeAlt;
    CString m_CDarr;
    CString m_CEinheit;
    CString m_CType;
    CString m_CCode;

// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    // Generated message map functions
    virtual void OnOK();

    DECLARE_MESSAGE_MAP()
};

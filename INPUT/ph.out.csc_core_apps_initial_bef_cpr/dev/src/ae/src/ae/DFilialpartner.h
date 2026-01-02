// DFilialpartner.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDFilialpartner : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDFilialpartner(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_FILIAL_PARTNER };
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
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonDelete();
    afx_msg void OnButtonNew();
    afx_msg void OnButtonUpdate();
    afx_msg void OnButtonEigen();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );

    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CDFilialpartnerUpd dialog

class CDFilialpartnerUpd : public CDialogMultiLang
{
// Construction
public:
    CDFilialpartnerUpd(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_FILIAL_PARTNER_UPD };
    CEdit   m_EditRechner;
    CStatic m_StaticZeiten;
    CEdit   m_EditVon;
    CEdit   m_EditFilialNr;
    CEdit   m_EditFilialName;
    CEdit   m_EditBis;
    CEdit   m_EditBGA;
    CString m_CBGA;
    CString m_CBis;
    CString m_CFilialNr;
    CString m_CVon;
    CString m_CFilialName;
    CString m_CStaticZeiten;
    CString m_CRechner;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnChangeEditBga();
    afx_msg void OnChangeEditBisz();
    afx_msg void OnChangeEditFiliName();
    afx_msg void OnChangeEditFiliNr();
    afx_msg void OnChangeEditVon();
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditRechner();
    DECLARE_MESSAGE_MAP()
};

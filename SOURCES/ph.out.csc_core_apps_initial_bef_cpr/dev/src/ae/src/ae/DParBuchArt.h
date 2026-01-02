// DParBuchArt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDParBuchArt dialog

class CDParBuchArt : public CDialogMultiLang
{
// Construction
public:
    CDParBuchArt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_PAR_BUCHART };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void ReadDataInListBox();
    void AddPosToList(CString BArt, long BMeth, CString BText);

    afx_msg void OnButtonNeu();
    afx_msg void OnButtonUpd();
    afx_msg void OnButtonDel();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDParBuchArtUpd dialog

class CDParBuchArtUpd : public CDialogMultiLang
{
// Construction
public:
    BOOL m_bUpdate;                         // Schalter ob Update oder Insert
    CDParBuchArtUpd(CWnd* pParent = NULL);  // standard constructor

    enum { IDD = IDD_AE_PAR_BUCHART_UPD };
    CEdit m_EditBuchMeth;
    CEdit m_EditBuchArt;
    CEdit m_EditBezeichnung;
    CString m_CBuchArt;
    CString m_CBezeichnung;
    long m_lBuchMeth;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditBezeichnung();
    afx_msg void OnChangeEditBuchart();
    afx_msg void OnChangeEditBuchmeth();
    DECLARE_MESSAGE_MAP()
};

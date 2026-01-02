// DParKomArt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDParKomArt dialog

class CDParKomArt : public CDialogMultiLang
{
// Construction
public:
    CDParKomArt(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PAR_KOMART };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void ReadDataInListBox();
    void AddPosToList(CString KArt, long KMeth, CString KText);

    afx_msg void OnButtonDel();
    afx_msg void OnButtonNeu();
    afx_msg void OnButtonUpd();
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDParKomArtUpd dialog

class CDParKomArtUpd : public CDialogMultiLang
{
// Construction
public:
    BOOL m_bUpdate;                         // Schalter ob Update oder Insert
    CDParKomArtUpd(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PAR_KOMART_UPD };
    CEdit   m_EditKomMeth;
    CEdit   m_EditKomArt;
    CEdit   m_EditBezeichnung;
    CString m_CBezeichnung;
    CString m_CKomArt;
    long    m_lKomMeth;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditBezeichnung();
    afx_msg void OnChangeEditKommart();
    afx_msg void OnChangeEditKommmeth();
    DECLARE_MESSAGE_MAP()
};

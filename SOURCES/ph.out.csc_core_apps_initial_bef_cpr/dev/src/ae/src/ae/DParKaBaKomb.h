// DParKaBaKomb.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDParKaBaKomb dialog

class CDParKaBaKomb : public CDialogMultiLang
{
// Construction
public:
    CDParKaBaKomb(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PAR_KABAKOMB };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void ReadDataInListBox();
    void AddPosToList(CString AArt, CString BArt, CString KArt, CString CStd, CString Tour, CString Zuschlag );

    afx_msg void OnButtonDel();
    afx_msg void OnButtonNeu();
    afx_msg void OnButtonUpd();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDParKaBaKombUpd dialog

class CDParKaBaKombUpd : public CDialogMultiLang
{
// Construction
public:
    CDParKaBaKombUpd(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PAR_KABAKOMB_UPD };
    CEdit   m_EditTour;
    CButton m_CBStd;
    CButton m_CBZuschlag;
    CEdit   m_EditKA;
    CEdit   m_EditBA;
    CEdit   m_EditAA;
    CString m_CAA;
    CString m_CBA;
    CString m_CKA;
    BOOL    m_bStd;
    BOOL    m_bZuschlag;
    CString m_CTour;
    BOOL    m_bUpd;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditAa();
    afx_msg void OnChangeEditBa();
    afx_msg void OnChangeEditKa();
    afx_msg void OnChangeEditTour();
    DECLARE_MESSAGE_MAP()
};

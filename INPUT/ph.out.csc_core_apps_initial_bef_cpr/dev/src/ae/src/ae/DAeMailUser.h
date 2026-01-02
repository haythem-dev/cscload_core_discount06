// DAeMailUser.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDAeMailUser : public CDialogMultiLang
{
// Construction
public:
    CDAeMailUser(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_MAIL_USER };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    BOOL        GetPage(int nKzUpDown = NEXT_PG);   // List-Box mit Eintraegen versorgen
    void        SelectEintrag();
    CMAILGROUP  m_mg;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonDelete();
    afx_msg void OnButtonNew();
    afx_msg void OnButtonUpdate();
    virtual void OnCancel();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CDAeMailUserUpd dialog

class CDAeMailUserUpd : public CDialogMultiLang
{
// Construction
public:
    CDAeMailUserUpd(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_DIALOG_MAIL_USER_UPD };
    CListCtrl m_List2;
    CListCtrl m_List1;
    CEdit   m_edit_GroupName;
    CString m_CGroupName;
    CString m_CGroupNo;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CMAILDEFINEDUSER m_mdef;
    CMAILGROUP m_mgroup;
    CMAILUSERS m_muser;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonDef();
    afx_msg void OnButtonUndef();
    afx_msg void OnChangeEditGroupName();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
};

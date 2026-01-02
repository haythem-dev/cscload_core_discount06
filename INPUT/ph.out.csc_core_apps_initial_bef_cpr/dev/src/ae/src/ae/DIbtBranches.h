#pragma once


// CDIbtBranches dialog

class CDIbtBranches : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDIbtBranches)

public:
    CDIbtBranches(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDIbtBranches();

    enum { IDD = IDD_AE_IBTBRANCHES };
    CListCtrl m_ListCtl;
    bool m_bNLevelIBT;

protected:
    void GetPage( );    // List-Box mit Eintraegen versorgen
    void SelectEintrag();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedInsert();
    afx_msg void OnBnClickedDelete();

    DECLARE_MESSAGE_MAP()
};


// CDIbtBranchesUpd dialog

class CDIbtBranchesUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDIbtBranchesUpd)

public:
    CDIbtBranchesUpd(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDIbtBranchesUpd();

    enum { IDD = IDD_AE_IBTBRANCHES_UPD };
    bool m_bUpdate;
    CListCtrl* m_pListCtl;
    CComboBox m_Combo_Folge;
    CString m_cVBFil;
    CComboBox m_Combo_Type;
    BOOL m_bDay;
    short m_sType;
    short m_sIBT_Type;
    short m_sFolge;
    short m_sAssorment;
    CString m_cBGA;
    BOOL m_bActiv;
    CEdit m_edit_vbfil;
    CEdit m_edit_BGA;
    CComboBox m_Combo_IBT_Type;
    CComboBox m_Combo_Assortment;
    bool m_bNLevelIBT;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnEnChangeEditVbFiliale();
    afx_msg void OnEnChangeEditBga();
    DECLARE_MESSAGE_MAP()
};

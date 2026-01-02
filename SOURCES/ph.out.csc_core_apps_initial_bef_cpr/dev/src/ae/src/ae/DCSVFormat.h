#pragma once


// CDCSVFormat dialog

class CDCSVFormat : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCSVFormat)

public:
    CDCSVFormat(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDCSVFormat();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_CSV_FORMATS };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnNMDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void ReadDataInListBox();

private:
    CListCtrl m_List1;
};


// CDCSVFormatUpd dialog

class CDCSVFormatUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCSVFormatUpd)

public:
    CDCSVFormatUpd(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDCSVFormatUpd();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_CSV_FORMATS_UPD };
#endif

    short m_sStart;
    bool m_update;
    CListCtrl m_List1;
    CEdit m_edit_Name;
    CString m_CName;
    CComboBox m_combo_Start;
    CButton m_cb_Postpone;
    CString m_CID;
    BOOL m_bPostpone;
    CString m_CPos;
    CComboBox m_combo_Inhalt;
    CStringArray m_array_Inhalt;
    CButton m_check_Grouping;
    BOOL m_bGrouping;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonPlus();
    afx_msg void OnBnClickedButtonMinus();
    afx_msg void OnEnChangeEditName();
    afx_msg void OnBnClickedButtonIns();
    afx_msg void OnBnClickedButtonAbbruch();
    afx_msg void OnBnClickedButtonSave();
    DECLARE_MESSAGE_MAP()
};

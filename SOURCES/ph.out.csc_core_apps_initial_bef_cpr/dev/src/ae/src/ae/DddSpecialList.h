#pragma once


// CDddSpecialList dialog

class CDddSpecialList : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDddSpecialList)

public:
    CDddSpecialList(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDddSpecialList();

// Dialog Data
    enum { IDD = IDD_AE_DD_SPECIAL_LIST };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

public:
    CStringArray m_DayList;
    void GetPage();
    CListCtrl m_List1;
    afx_msg void OnBnClickedButtonIns();
    afx_msg void OnBnClickedButtonDel();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
};

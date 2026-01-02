#pragma once

// DMailControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMailControl dialog

class CDMailControl : public CDialogMultiLang
{
// Construction
public:
    CDMailControl(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_MAIL_CONTROL };
    CEdit m_Edit_Datum;
    CListCtrl m_List1;
    CString m_CDatum;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CTM zeit;
    CMAILMESSAGE m_mes;
    void SelectEintrag();

    afx_msg void OnButtonAnzeige();
    afx_msg void OnChangeEditDatum();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDMailControlUsers dialog

class CDMailControlUsers : public CDialogMultiLang
{
// Construction
public:
    CDMailControlUsers(CWnd* pParent = NULL);   // standard constructor
    int m_iCount;

    enum { IDD = IDD_AE_MAIL_CONTROL_USERS };
    CListCtrl m_List2;
    CString m_CText;
    CString m_CNo;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CMAILDEFINEDUSER m_def;

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonDel();
    DECLARE_MESSAGE_MAP()
};

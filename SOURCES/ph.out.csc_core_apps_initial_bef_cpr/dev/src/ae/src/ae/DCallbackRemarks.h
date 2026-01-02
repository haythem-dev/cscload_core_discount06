#pragma once


// CDCallbackRemarks dialog

class CDCallbackRemarks : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCallbackRemarks)

public:
    CDCallbackRemarks(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDCallbackRemarks();

    enum { IDD = IDD_AE_CALLBACK_REMARKS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    void GetPage();                 // Fuellen der Listbox

    DECLARE_MESSAGE_MAP()

public:
    CListCtrl m_List1;
    afx_msg void OnBnClickedButtonUpd();
    afx_msg void OnBnClickedButtonIns();
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
};

// CDCallbackRemarksUpd dialog

class CDCallbackRemarksUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCallbackRemarksUpd)

public:
    CDCallbackRemarksUpd(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDCallbackRemarksUpd();

    enum { IDD = IDD_AE_CALLBACKREMARKS_UPD };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

public:
    CString m_cCBHeader;
    CString m_cCBText;
    long m_lRemarkNo;
    virtual void OnOK();
};

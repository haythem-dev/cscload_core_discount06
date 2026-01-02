#pragma once


// CDBranchInfo-Dialogfeld

class CDBranchInfo : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDBranchInfo)

public:
    CDBranchInfo(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDBranchInfo();

    enum { IDD = IDD_AE_BRANCHINFO };
    CEdit m_edit_Info;
    CEdit m_edit_Info2;
    CString m_CInfo;
    CString m_CInfo2;
    CBRANCHINFO m_Info;
    BOOL m_bupdate;
    BOOL m_bupdate2;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnEnChangeEditInfo();
    afx_msg void OnEnChangeEditInfo2();
    DECLARE_MESSAGE_MAP()
};

#pragma once


// CDViewCstBranchInfo-Dialogfeld

class CDViewCstBranchInfo : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDViewCstBranchInfo)

public:
    CDViewCstBranchInfo(CWnd* pParent = NULL);   // Standardkonstruktor
    CDViewCstBranchInfo(CView* pWview);
    BOOL Create();
    virtual ~CDViewCstBranchInfo();

    enum { IDD = IDD_AE_VIEW_CST_BRANCH_INFO };
    CEdit m_LBInfo;
    short m_sBranchNo;

protected:
    void RepositionWindow();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );

    DECLARE_MESSAGE_MAP()

private:
    CView* m_pView;
};

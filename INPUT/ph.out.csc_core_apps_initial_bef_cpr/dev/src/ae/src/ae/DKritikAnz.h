#pragma once


// CDKritikAnz dialog

class CDKritikAnz : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDKritikAnz)

public:
    CDKritikAnz(CWnd* pParent = NULL);   // standard constructor
    CDKritikAnz(CView* pWview);
    BOOL Create();
    void RepositionWindow();
    virtual ~CDKritikAnz();
    CImageList m_ImageSmall;
    short m_sBranchno;
    long m_lCustomerno;

// Dialog Data
    enum { IDD = IDD_AE_KRITIK_ANZ };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnDestroy();
    virtual void OnCancel();

    DECLARE_MESSAGE_MAP()

public:
    CListCtrl m_List1;
    virtual BOOL OnInitDialog();

private:
    CView* m_pView;
};

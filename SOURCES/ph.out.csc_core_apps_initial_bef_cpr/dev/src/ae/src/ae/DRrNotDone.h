#pragma once

// DRrNotDone.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDRrNotDone dialog

class CDRrNotDone : public CDialogMultiLang
{
// Construction
public:
    CDRrNotDone(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_RR_NOT_DONE };
    CListCtrl m_ListCtl;
    CImageList m_ImageSmall;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

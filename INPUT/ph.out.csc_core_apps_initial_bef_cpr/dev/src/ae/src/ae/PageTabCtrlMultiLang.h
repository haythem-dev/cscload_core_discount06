// PageTabCtrlMultiLang.h : header file
//
#ifndef _PAGETABCTRLMULTILANG_H
#define _PAGETABCTRLMULTILANG_H

#include "TabPageMultiLang.h"

/////////////////////////////////////////////////////////////////////////////
// CPageTabCtrlMultiLang window

class CPageTabCtrlMultiLang : public CTabCtrl
{
// Construction
public:
    CPageTabCtrlMultiLang();
// Attributes
public:
    CObArray m_PageArray;
    int m_nCurPage;
    bool m_bCalled;

protected:
    bool m_bInit;

// Overrides
    // ClassWizard generated virtual function overrides
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
public:
    virtual ~CPageTabCtrlMultiLang();
    void AddPage(CTabPageMultiLang* pPageP);
    virtual BOOL AddItem(TC_ITEM* pTabCtrlItemP);

    void SetWarningtext( const CString& csIsActiv ) { m_csIsActiv = csIsActiv; }
    CTabPageMultiLang* GetCurrentPage() {return m_pCurrentPage;};
    CTabPageMultiLang* GetPage(const int& nIndex);

   // Generated message map functions
protected:
    bool ChangePage(int nPageTo, int nPageFrom);
    bool IsChanged();
    afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
    void FindSizeOfTabWindow(CWnd* pWndP, LPRECT pRectP);
    CTabPageMultiLang* m_pCurrentPage;
    DECLARE_MESSAGE_MAP()

protected:
    CString m_csIsActiv;
};

#endif

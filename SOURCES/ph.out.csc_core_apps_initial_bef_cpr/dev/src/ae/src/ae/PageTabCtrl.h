// PageTabCtrl.h : header file
//
#ifndef _PAGETABCTRL_H
#define _PAGETABCTRL_H

#include "TabPage.h"

/////////////////////////////////////////////////////////////////////////////
// CPageTabCtrl window

class CPageTabCtrl : public CTabCtrl
{
// Construction
public:
    CPageTabCtrl();
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
    virtual ~CPageTabCtrl();
    void AddPage(CTabPage* pPageP); 
    virtual BOOL AddItem(TC_ITEM* pTabCtrlItemP);

    void SetWarningtext( const CString& csIsActiv ) { m_csIsActiv = csIsActiv; }
    CTabPage* GetCurrentPage() {return m_pCurrentPage;}; 
    CTabPage* GetPage(const int& nIndex); 

   // Generated message map functions
protected:
    bool ChangePage(int nPageTo, int nPageFrom);
    bool IsChanged();
    afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
    void FindSizeOfTabWindow(CWnd* pWndP, LPRECT pRectP);
    CTabPage* m_pCurrentPage;
    DECLARE_MESSAGE_MAP()

protected:
    CString m_csIsActiv;
};

#endif

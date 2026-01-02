// CTabPage.cpp : implementation file
//

#include "stdafx.h"
#include "TabPage.h"

/////////////////////////////////////////////////////////////////////////////
// CTabPage property page

//IMPLEMENT_DYNCREATE(CTabPage, CPropertyPage)

CTabPage::CTabPage(int nIDP) : CPropertyPage(nIDP)
{
    IDD = nIDP;
    m_bModified = false;
    m_bEnabled = true;
    m_csTitle = "";
    m_bIsChanged = false; 
}

CTabPage::~CTabPage()
{
}

void CTabPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabPage, CPropertyPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabPage message handlers

BOOL CTabPage::PreTranslateMessage(MSG* pMsg) 
{
    CWnd* pCtrl = GetFocus();
    if (pMsg->message == WM_KEYDOWN && pCtrl)
    {
        if (pMsg->wParam == VK_TAB && GetKeyState(VK_LCONTROL) >= 0)
        {
            BOOL bPrevious = FALSE;
            if (GetKeyState(VK_SHIFT) < 0)
                bPrevious = TRUE;
            CWnd* pWnd = GetNextDlgTabItem(pCtrl,bPrevious);
            pWnd->SetFocus();
            ((CEdit*)pWnd)->SetSel(0,-1);
            return TRUE;
        }
        else if (GetKeyState(VK_RETURN) < 0)
        {
            return PreTranslateInput(pMsg);
        }
    }
    else
    {
        if (GetKeyState(VK_MENU) < 0 || GetKeyState(VK_RETURN) < 0)
        {
            return PreTranslateInput(pMsg);
        }
    }
    return CWnd::PreTranslateMessage(pMsg);
}

void CTabPage::SetTabTitle(CString cs)
{
    m_csTitle = cs;
}

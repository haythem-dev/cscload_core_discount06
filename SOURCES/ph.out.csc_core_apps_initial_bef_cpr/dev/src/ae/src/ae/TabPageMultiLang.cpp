// CTabPageMultiLang.cpp : implementation file
//

#include "stdafx.h"
#include "TabPageMultiLang.h"

/////////////////////////////////////////////////////////////////////////////
// CTabPageMultiLang property page

//IMPLEMENT_DYNCREATE(CTabPage, CPropertyPageMultilang)

CTabPageMultiLang::CTabPageMultiLang(int nIDP) : CPropertyPageMultiLang(nIDP)
{
    IDD = nIDP;
    m_bModified = false;
    m_bEnabled = true;
    m_csTitle = "";
    m_bIsChanged = false; 
}

CTabPageMultiLang::~CTabPageMultiLang()
{
}

void CTabPageMultiLang::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTabPageMultiLang, CPropertyPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabPage message handlers

BOOL CTabPageMultiLang::PreTranslateMessage(MSG* pMsg)
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

void CTabPageMultiLang::SetTabTitle(CString cs)
{
    m_csTitle = cs;
}

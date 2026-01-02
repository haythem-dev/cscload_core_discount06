// PageTabCtrl.cpp : implementation file
//
#include "stdafx.h"
#include "PageTabCtrl.h"
#include "TabPage.h"

/////////////////////////////////////////////////////////////////////////////
// CPageTabCtrl

CPageTabCtrl::CPageTabCtrl()
{
    m_pCurrentPage= NULL;
    m_bCalled = false;
    m_bInit = false;
    m_nCurPage = 0;
    m_csIsActiv = "In der Maske %s wurde geändert und nicht gespeichert! Wollen sie den Dialog wirklich verlasen?";
}

CPageTabCtrl::~CPageTabCtrl()
{
}

BEGIN_MESSAGE_MAP(CPageTabCtrl, CTabCtrl)
    ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
END_MESSAGE_MAP()

BOOL CPageTabCtrl::PreTranslateMessage(MSG* pMsg)
{
    int nCurSel;
    if (pMsg->message == WM_KEYDOWN)
    {
        if (GetKeyState(VK_LCONTROL) < 0 && GetKeyState(VK_TAB) < 0)
        {
            if (GetKeyState(VK_SHIFT) >= 0)
            {
               nCurSel = m_nCurPage = GetCurSel();
               if (!IsChanged())
               {
                  if (nCurSel < GetItemCount()-1)
                     ++nCurSel;
                  else
                     nCurSel = 0;
               }
            }
            else
            {
                nCurSel = m_nCurPage = GetCurSel();
                if (nCurSel > 0)
                    --nCurSel;
                else
                    nCurSel = GetItemCount()-1;
            }
            SetCurSel(nCurSel);
            ChangePage(nCurSel,m_nCurPage);
            GetCurrentPage()->SetFocus();
            return TRUE;
        }
        else if (GetKeyState(VK_TAB) < 0)
        {
            GetCurrentPage()->SetFocus();
            return TRUE;
        }
    }
    else if (GetKeyState(VK_MENU) < 0 || GetKeyState(VK_RETURN) < 0)
        return GetCurrentPage()->PreTranslateMessage(pMsg);
    else if (!m_bInit)
    {
        m_bInit = true;
        GetCurrentPage()->SetFocus();
    }

    return CTabCtrl::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CPageTabCtrl message handlers

void CPageTabCtrl::AddPage(CTabPage* pPage)
{
    ASSERT(pPage != NULL);
    ASSERT(pPage->GetID() !=0);  // did you forget to overload this
    CString zTitle;

    m_PageArray.Add(pPage);

    pPage->Create(pPage->GetID(), this);
    if (!m_bCalled)
    {
        pPage->ShowWindow(TRUE);
        m_bCalled = true;
    }

    // here is the standard (useless) way to insert items
    TC_ITEM TabCtrlItem;
    TabCtrlItem.mask = TCIF_TEXT;
    TabCtrlItem.pszText = (TCHAR*)pPage->GetTabTitle();
    AddItem(&TabCtrlItem);

    // you must reposition the window below the tab mark
    CRect rect;
    FindSizeOfTabWindow(pPage,rect);
    pPage->MoveWindow(rect);

    m_pCurrentPage = (CTabPage*)m_PageArray[0];
}

bool CPageTabCtrl::ChangePage(int nPageTo, int nPageFrom)
{
    if (nPageFrom < 0)
    {
        nPageFrom = 0;
        m_pCurrentPage = (CTabPage*)m_PageArray[nPageFrom];
        m_pCurrentPage->SetActiveWindow();
    }
    if (nPageTo != -1)
    {
        CTabPage* pPageTo = (CTabPage*)m_PageArray[nPageTo];
        if (pPageTo->m_bEnabled)
        {
            // Hide the current window and then change to the current window.
            m_pCurrentPage->ShowWindow(FALSE);
            m_pCurrentPage = (CTabPage*)m_PageArray[nPageTo];
            m_pCurrentPage->ShowWindow(TRUE);
            NMHDR* pNMHDR = new NMHDR;
            pNMHDR->hwndFrom = m_pCurrentPage->GetSafeHwnd();
            pNMHDR->code = PSN_SETACTIVE;
            ((CTabPage*)m_pCurrentPage)->SendMessage(WM_NOTIFY,0,(LPARAM)pNMHDR);
            delete pNMHDR;
            m_pCurrentPage->SetFocus();
        }
        else
        {
            SetCurSel(nPageFrom);
            m_nCurPage = nPageFrom;
            pPageTo->EnableWindow(FALSE);
            return false;
        }
    }
    return true;
}

void CPageTabCtrl::OnSelchange(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    ASSERT(m_pCurrentPage != NULL);

    UINT nNewId = GetCurSel();

    if (IsChanged())
    {
        nNewId = m_nCurPage;
        SetCurSel(m_nCurPage);
    }

    if (ChangePage(nNewId, m_nCurPage))
    {
        m_nCurPage = GetCurSel();
        *pResult = 0L;
    }
}

void CPageTabCtrl::FindSizeOfTabWindow(CWnd* pWndP, LPRECT pRectP)
{
    ASSERT(pWndP  != NULL);
    ASSERT(pRectP != NULL);

    // Get the size of the page
    pWndP->GetClientRect(pRectP);

    // This returns the rect of the tab button NOT the tab ctl
    CRect rcTab;
    GetItemRect(0, rcTab);
    int nTabHeight = 3;
    if (GetStyle() & TCS_MULTILINE)
        nTabHeight = rcTab.bottom - rcTab.top;

    // tweak a little here tweak a little there
    pRectP->top    += rcTab.bottom + nTabHeight;
    pRectP->left   += 2;
    pRectP->bottom += -2;
    pRectP->right  += -2;
}

BOOL CPageTabCtrl::AddItem(TC_ITEM* pTabCtrlItemP)
{
    // God only knows why this function was not part of CTabCtl!!!
    ASSERT(pTabCtrlItemP);

    static int IS = 0;
    INT nNextTab = IS++; // returns one more than the index
    return InsertItem(nNextTab, pTabCtrlItemP);
}

CTabPage* CPageTabCtrl::GetPage(const int& nIndex)
{
    if (nIndex >= GetItemCount())
        return NULL;

    return (CTabPage*)m_PageArray[nIndex];
}

bool CPageTabCtrl::IsChanged()
{
    if (GetPage(m_nCurPage)->IsChanged())       //check changes before leaving!
    {
       CString csText;
       csText.Format(m_csIsActiv, GetPage(m_nCurPage)->GetTabTitle());
       if (MsgBoxYesNo(csText) != IDYES)
       {
          GetPage(m_nCurPage)->SetIsActive(); //back into page
          return true;
       }
       else
       {
          GetPage(m_nCurPage)->SetData(); //undo/restore changes
       }
    }
    GetPage(m_nCurPage)->SetIsActive(false);
    return false;
}

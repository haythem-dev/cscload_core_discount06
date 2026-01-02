#include "StdAfx.h"
#include "PageBrowser.h"

CPageBrowser::CPageBrowser(int nLineCapacityOfPage)
    : m_nLineCapacityOfPage(nLineCapacityOfPage), m_nCurrentPage(0)
{
    m_bCursorOpen = false;  //Datenbankcurser geschlossen
    m_bFirstDataset = true;   //noch kein Satz aufgerufen

    Reset();
}

CPageBrowser::~CPageBrowser()
{
}

void CPageBrowser::Init(int nLineCapacityOfPage)
{
    m_nLineCapacityOfPage = nLineCapacityOfPage;
    Reset();
}

void CPageBrowser::Reset()
{
    m_nItemCountOfCurrentPage = m_nLineCapacityOfPage;
    m_nPageBeforeReset = m_nCurrentPage;
    m_nCurrentPage = 0;
}

void CPageBrowser::ResetCursor()
{
    m_bCursorOpen = false;
    m_bFirstDataset = true;
}

void CPageBrowser::SetItemCountOfCurrentPage(int nItemCountOfCurrentPage)
{
    m_nItemCountOfCurrentPage = nItemCountOfCurrentPage;
}

bool CPageBrowser::GetFetchPositionOnPageSwitch(int nKzUpDown, int& nFetchPosition)
{
    long lFetchPosition;
    bool res = GetFetchPositionOnPageSwitch(nKzUpDown, lFetchPosition);
    nFetchPosition = static_cast<int>(lFetchPosition);
    return res;
}

bool CPageBrowser::GetFetchPositionOnPageSwitch(int nKzUpDown, long& lFetchPosition)
{
    if (nKzUpDown == PRIOR_PG)
    {
        if (m_nCurrentPage <= 1)
        {
            return false;           // Page 1
        }
        lFetchPosition = -(m_nLineCapacityOfPage + m_nItemCountOfCurrentPage - 1);
        --m_nCurrentPage;           // Switch to previous page
    }
    else // nKzUpDown == NEXT_PG
    {
        if (m_nItemCountOfCurrentPage != m_nLineCapacityOfPage)
        {
            return false;
        }
        lFetchPosition = 1;
        ++m_nCurrentPage;           // Switch to next page
    }

    m_nItemCountOfCurrentPage = m_nLineCapacityOfPage;     // Initialization

    return true;
}

long CPageBrowser::GetFetchStartPosition() const
{
    return 1 - GetFetchBasePosition();
}

long CPageBrowser::GetFetchPosition(int nDataSetCounter) const
{
    return GetFetchBasePosition() - nDataSetCounter;
}

long CPageBrowser::GetFetchBasePosition() const
{
    return (m_nCurrentPage - 1) * m_nLineCapacityOfPage + m_nItemCountOfCurrentPage;
}

int CPageBrowser::GetPageBeforeReset() const
{
    return m_nPageBeforeReset;
}

void CPageBrowser::RestorePageBeforeReset()
{
    m_nCurrentPage = m_nPageBeforeReset;
    m_nItemCountOfCurrentPage = m_nLineCapacityOfPage;     // Initialization

}

void CPageBrowser::SetCurrentPage(int nCurrentPage)
{
    m_nCurrentPage = nCurrentPage;
    m_nItemCountOfCurrentPage = m_nLineCapacityOfPage;     // Initialization

}

bool CPageBrowser::GetPage(const int /*nKzUpDown=NEXT_PG*/)
{
    return false;
}

// return: true=event handled
bool CPageBrowser::OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult, CListCtrl& listCtrl, bool bTestInRange /*=true*/, bool bTestNextPrev /*=true*/)
{
    int pos;
    return OnKeydownList(pNMHDR, pResult, listCtrl, pos, bTestInRange, bTestNextPrev);
}

// pos: position after pressing a letter (A-Z) or Up and Down key
// return: true=event handled
bool CPageBrowser::OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult, CListCtrl& listCtrl, int& pos, bool bTestInRange /*=true*/, bool bTestNextPrev /*=true*/)
{
    pos = -1;
    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

    // Immediately return on Alt (Menu) or Control key is pressed
    if (   ((GetKeyState(VK_MENU) & 0x8000) == 0x8000)
        || ((GetKeyState(VK_CONTROL) & 0x8000) == 0x8000) )
    {
        *pResult = 0L;
        return true;
    }

    if (bTestNextPrev && OnHookNextPrev((unsigned int)pLVKeyDow->wVKey))
    {
        *pResult = 1L;
        return true;        //Message wird nicht weitergeleitet
    }

    if (bTestInRange && CLetterMan::InRange(pLVKeyDow->wVKey, listCtrl.GetItemCount()))
    {
        pos = pLVKeyDow->wVKey - AeGetApp()->Letter_A();
        CListCtrlHelper::SetItemStateSelectedFocused(listCtrl, pos);
        *pResult = 0L;
        return true;
    }

    if ((pLVKeyDow->wVKey == VK_UP) || (pLVKeyDow->wVKey == VK_DOWN))
    {
        pos = listCtrl.GetNextItem(-1, LVNI_SELECTED);
        *pResult = 0L;
        return true;
    }

    *pResult = 0L;
    return false;
}

// return: 1L=event handled, 0L=event not handled
LRESULT CPageBrowser::OnHookNextPrev(LPARAM lpMsg)
{
    if (OnHookNextPrev(((LPMSG)lpMsg)->wParam))
    {
        return 1L;      //Message wird nicht weitergeleitet
    }
    return 0L;
}

// return: true=event handled
bool CPageBrowser::OnHookNextPrev(unsigned int key)
{
    if (key == VK_NEXT)
    {
        if (m_bCursorOpen)
        {
            GetPage();
        }
        return true;
    }
    else if (key == VK_PRIOR)
    {
        if (m_bCursorOpen)
        {
            GetPage(PRIOR_PG);
        }
        return true;
    }
    return false;
}

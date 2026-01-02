/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "TourListctrl.h"
#include <assert.h>

//Constructor
CListItemData::CListItemData()
{
    Reset();
}

//Get which item/row
int CListItemData::GetItem() const
{
    return m_item;
}

//Get which subitem/column
int CListItemData::GetSubItem() const
{
    return m_subitem;
}

//Is item selected?
bool CListItemData::IsSelected() const
{
    return m_isSelected;
}

//Is item hot?
bool CListItemData::IsHot() const
{
    return m_isHot;
}

//Constructor
CTourListCtrl::CTourListCtrl()
{
}

//Destructor
CTourListCtrl::~CTourListCtrl()
{
}

BEGIN_MESSAGE_MAP(CTourListCtrl, CListCtrl)
    ON_WM_PAINT()
    ON_WM_KEYDOWN()
    ON_WM_MOUSEWHEEL()
    ON_WM_VSCROLL()
    ON_WM_HSCROLL()
    ON_WM_MOUSEMOVE()
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
    ON_WM_CHAR()
    ON_NOTIFY_REFLECT_EX(NM_CLICK, OnClickEx)
END_MESSAGE_MAP()

//Reset settings.
void CListItemData::Reset()
{
    m_item = m_subitem = 0;
    m_isSelected = false;
    m_isHot = false;
    m_noSelection = false;

    m_button.m_draw = false;
    m_button.m_style = DFCS_BUTTONCHECK;
    m_button.m_noSelection = true;
    m_button.m_center = false;
}

//Custom draw
void CTourListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
    NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

    // If this is the beginning of the control's paint cycle, request
    // notifications for each item.

    if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
    {
        *pResult = CDRF_NOTIFYITEMDRAW;
    }
    else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
    {
        // This is the pre-paint stage for an item.  We need to make another
        // request to be notified during the post-paint stage.
        *pResult = CDRF_NOTIFYSUBITEMDRAW;
    }
    else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
    {
        CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);

        DrawItem(static_cast<int> (pLVCD->nmcd.dwItemSpec), pLVCD->iSubItem, pDC);

        *pResult = CDRF_SKIPDEFAULT;    // We've painted everything.
    }
}

bool CTourListCtrl::init()
{
    InsertColumn(COL_KB,   CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE), LVCFMT_LEFT,  30);
    InsertColumn(COL_TOUR, CResString::ex().getStrTblText(AETXT_TOUR),          LVCFMT_LEFT,  60);
    InsertColumn(COL_AUTO, CResString::ex().getStrTblText(AETXT_AUTO_ZUORD),    LVCFMT_LEFT, 130);
    InsertColumn(COL_BTM,  CResString::ex().getStrTblText(AETXT_BTM),           LVCFMT_LEFT,  40);
    InsertColumn(COL_KK,   CResString::ex().getStrTblText(AETXT_KK),            LVCFMT_LEFT,  40);
    InsertColumn(COL_K08,  CResString::ex().getStrTblText(AETXT_K08),           LVCFMT_LEFT,  40);
    InsertColumn(COL_K20,  CResString::ex().getStrTblText(AETXT_K20),           LVCFMT_LEFT,  40);

    return TRUE;
}

void CTourListCtrl::refreshItem(const int /*iItem*/)
{
}

bool CTourListCtrl::isColNumber(const int iCol) const
{
    if (iCol == 0)          // erste Spalte kann nicht durch EditSubLabel editiert werden;
        return false;       // dies wird durch ListCtrl selbst unterstützt

    return false;
}

bool CTourListCtrl::isColEditable(const int iCol) const
{
    if (iCol == 0)          // erste Spalte kann nicht durch EditSubLabel editiert werden;
        return false;       // dies wird durch ListCtrl selbst unterstützt

    return false;
}

UINT CTourListCtrl::getLimitText(const int iCol) const
{
    if (iCol == 0)      // erste Spalte kann nicht durch EditSubLabel editiert werden;
        return 0;       // dies wird durch ListCtrl selbst unterstützt

    return 0;
}

bool CTourListCtrl::setSubItem(const int /*iItem*/, const int iSubItem, CString& csText)
{
    if (iSubItem == 0)      // erste Spalte kann nicht durch EditSubLabel editiert werden;
        return false;       // dies wird durch ListCtrl selbst unterstützt

    csText.MakeUpper();

    return true;
}

BOOL CTourListCtrl::PreTranslateMessage(MSG* pMsg)
{
    switch (pMsg->wParam)
    {
    case VK_RETURN:
        this->SetFocus();
        ::PostMessage(AeGetApp()->PromoWnd(), WM_COMMAND, IDOK, 0);
        return TRUE;

    default:
        break;
    }

    return CListCtrl::PreTranslateMessage(pMsg);
}

//Is item selected?
bool CTourListCtrl::IsSelected(const int item, const int subitem)
{
    if (GetItemState(item, LVIS_SELECTED))
    {
        if ( subitem == 0 ||    //First column or...
             FullRowSelect() )  //full row select?
        {
            // has focus?
            if (m_hWnd != ::GetFocus())
            {
                return GetStyle() & LVS_SHOWSELALWAYS ? true : false;
            }

            return true;
        }
    }

    return false;
}

//Is full row selection enabled?
bool CTourListCtrl::FullRowSelect()
{
    return (GetExtendedStyle() & LVS_EX_FULLROWSELECT) != 0;
}

//Make items inside visible area
bool CTourListCtrl::MakeInside(int& top, int &bottom)
{
    int min = GetTopIndex(), max = min + GetCountPerPage();

    if (max >= GetItemCount())
        max = GetItemCount() - 1;

    //Is both outside visible area?
    if (top < min && bottom < min)
        return false;
    if (top > max && bottom > max)
        return false;

    if (top < min)
        top = min;

    if (bottom > max)
        bottom = max;

    return true;
}

//Get text rect
//Return false if none
bool CTourListCtrl::GetTextRect(const int item, const int subitem, CRect& rect)
{
    CListItemData& data = GetItemData(item, subitem);

    return GetTextRect(data, rect);
}

//Get text rect
//Return false if none
bool CTourListCtrl::GetTextRect(CListItemData& id, CRect& rect)
{
    GetSubItemRect(id.GetItem(), id.GetSubItem(), LVIR_BOUNDS, rect);

    CRect temp;

    return true;
}

//Draw an item in pDC
void CTourListCtrl::DrawItem(int item, int subitem, CDC* pDC)
{
    CListItemData id = GetItemData(item, subitem);
    //Draw button?
    if (id.m_button.m_draw)
        DrawButton(id, pDC);

    DrawText(id, pDC);
}

//Draw text
void CTourListCtrl::DrawText(CListItemData& id, CDC* pDC)
{
    ASSERT(pDC);

    CRect rect, fulltextrect;

    GetTextRect(id, rect);

    fulltextrect = rect;

    CString text = id.m_text;
    //If we don't do this, character after & will be underlined.
    text.Replace(_T("&"), _T("&&"));

    pDC->DrawText(text, &rect, DT_LEFT);
}


//Draw button (check box/radio button)
void CTourListCtrl::DrawButton(CListItemData& id, CDC* pDC)
{
    ASSERT(pDC);

    CRect chkboxrect;

    GetCheckboxRect(id, chkboxrect, false);
    GetCheckboxRect(id, chkboxrect, true);

    pDC->DrawFrameControl(&chkboxrect, DFC_BUTTON, id.m_button.m_style );
}


//Get check box rect
//Return false if none
bool CTourListCtrl::GetCheckboxRect(const int item, const int subitem, CRect& rect, bool checkOnly)
{
    CListItemData& data = GetItemData(item, subitem);

    return GetCheckboxRect(data, rect, checkOnly);
}

//Redraw check boxes
void CTourListCtrl::RedrawCheckBoxs(const int top, const int bottom, const int column, BOOL erase)
{
    RedrawSubitems(top, bottom, column, 1, erase);
}

//Redraw items in a column
void CTourListCtrl::RedrawSubitems(const int top, const int bottom, const int column, BOOL erase)
{
    RedrawSubitems(top, bottom, column, 0, erase);
}

//Redraw text/progressbar in a column
void CTourListCtrl::RedrawText(const int top, const int bottom, const int column, BOOL erase)
{
    RedrawSubitems(top, bottom, column, 2, erase);
}


//Redraw some of a subitem
void CTourListCtrl::RedrawSubitems(int top, int bottom, int column, int part, BOOL erase)
{
    if (GetItemCount() <= 0)
        return;

    if (!MakeInside(top, bottom))
        //No need to redraw items.
        return;

    CRect rect_top, rect_bottom;

    if (part == 0) //Redraw subitem completely
    {
        GetSubItemRect(top, column, LVIR_BOUNDS, rect_top);
        GetSubItemRect(bottom, column, LVIR_BOUNDS, rect_bottom);
    }
    else if (part == 1) //Redraw check boxs
    {
        GetCheckboxRect(top, column, rect_top, true);
        GetCheckboxRect(bottom, column, rect_bottom, true);
    }
    else //Redraw text/progressbar
    {
        GetTextRect(top, column, rect_top);
        GetTextRect(bottom, column, rect_bottom);
    }

    //Mix them
    rect_top.UnionRect(&rect_top, &rect_bottom);

    InvalidateRect(&rect_top, erase);
}

//Get check box rect
//Return false if none
bool CTourListCtrl::GetCheckboxRect(CListItemData& id, CRect& rect, bool checkOnly)
{
#ifdef QUICKLIST_NOBUTTON
    UNREFERENCED_PARAMETER(id);
    UNREFERENCED_PARAMETER(rect);

    return false;
#else
    if (!id.m_button.m_draw)
        return false;

    CRect full;
    GetSubItemRect(id.GetItem(), id.GetSubItem(), LVIR_BOUNDS, full);

    rect = full;

    int checkWidth = full.Height();

    if (id.m_button.m_center)
    {
        rect.left = full.CenterPoint().x - (checkWidth)/2;
        rect.right = full.CenterPoint().x + (checkWidth+1)/2;
    }
    else
        rect.right = rect.left + checkWidth;    // width = height

    if (!checkOnly)
        rect.left = full.left;

    return true;
#endif
}

//Get information about an item
CListItemData& CTourListCtrl::GetItemData(const int item, const int subitem)
{
    ASSERT(item >= 0);
    ASSERT(item < GetItemCount());
    ASSERT(subitem >= 0);

    //Static, so we doesn't new to create a new every time
    CListItemData& id = m_lastget;
    id.Reset();

    id.m_item = item;
    id.m_subitem = subitem;
    id.m_isSelected = IsSelected(item, subitem); //GetItemState(item, LVIS_SELECTED)!=0;
    id.m_isHot = (GetHotItem() == id.m_item);

    ::SendMessage(GetParent()->GetSafeHwnd(), WM_QUICKLIST_GETLISTITEMDATA, (WPARAM)GetSafeHwnd(), (LPARAM)&id);

    return id;
}

//On click
BOOL CTourListCtrl::OnClickEx(NMHDR* pNMHDR, LRESULT* pResult)
{
    NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    //Try to change navigation column when user clicks on an item
    CListHitInfo clickinfo;
    clickinfo.m_item = clickinfo.m_subitem = -1;
    clickinfo.m_onButton = clickinfo.m_onImage = false;

    if (HitTest(pNMListView->ptAction, clickinfo))
    {

        ::SendMessage(GetParent()->GetSafeHwnd(), WM_QUICKLIST_CLICK, (WPARAM)GetSafeHwnd(), (LPARAM)&clickinfo);
    }

    *pResult = 0L;

    return FALSE;
}

//Test where a point is on an item
bool CTourListCtrl::HitTest(const POINT& point, CListHitInfo &info)
{
    return HitTest(point, info.m_item, info.m_subitem, &info.m_onButton);
}

//Test where a point is on an item
bool CTourListCtrl::HitTest(const POINT& point, int& item, int& subitem, bool* onCheck)
{
    LVHITTESTINFO test;
    test.pt = point;
    test.flags=0;
    test.iItem = test.iSubItem = -1;

    if (ListView_SubItemHitTest(m_hWnd, &test) == -1)
        return false;

    item = test.iItem;
    subitem = test.iSubItem;

    //Make check box hit test?
    if (onCheck != NULL)
    {
        CRect checkrect;

        //Has check box?
        if (GetCheckboxRect(test.iItem, test.iSubItem, checkrect, true))
        {
            *onCheck = checkrect.PtInRect(point) ? true : false;
        }
        else
            *onCheck = false;
    }

    return true;
}

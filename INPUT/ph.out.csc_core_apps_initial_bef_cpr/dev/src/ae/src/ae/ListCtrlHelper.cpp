#include "StdAfx.h"
#include "ListCtrlHelper.h"

#define SMALL_BITMAP_WIDTH  16
#define SMALL_BITMAP_HEIGHT 16


/*static*/
bool CListCtrlHelper::AddColumns(COLUMNS_TYPES* pTypeInit, CListCtrl& listCtrl)
{
    LV_COLUMN lvC;      // List View Column structure
    lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

    for (COLUMNS_TYPES* pType = pTypeInit; pType->Index != -1; pType++) // Add the columns.
    {
        lvC.iSubItem = pType->Index;
        lvC.pszText = (char*)pType->Columns.GetString();
        lvC.fmt = pType->Align;
        lvC.cx = pType->Width;

        if (listCtrl.InsertColumn(pType->Index, &lvC) == -1)
        {
            return false;
        }
    }
    return true;
}

/*static*/
bool CListCtrlHelper::AppendItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int startColumn /*= 1*/)
{
    int index;
    return GetAppendItem(listCtrl, columnCount, s, index, startColumn);
}

/*static*/
bool CListCtrlHelper::GetAppendItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int& index, int startColumn /*= 1*/)
{
    index = listCtrl.GetItemCount();
    return InsertItem(listCtrl, columnCount, s, index, startColumn);
}

/*static*/
bool CListCtrlHelper::InsertItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int index, int startColumn /*= 1*/)
{
    if (listCtrl.InsertItem(index, s[0]) == -1)
    {
        return false;
    }
    CListCtrlHelper::SetItemTexts(listCtrl, columnCount, s, index, startColumn);
    return true;
}

bool CListCtrlHelper::InsertItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, LV_ITEM& lvi, int startColumn /*= 0*/)
{
    if (listCtrl.InsertItem(&lvi) == -1)
    {
        return false;
    }
    // iSubItem mit 0 wg. sort
    CListCtrlHelper::SetItemTexts(listCtrl, columnCount, s, lvi.iItem, startColumn);
    return true;
}

/*static*/
bool CListCtrlHelper::AppendImageItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int nImage)
{
    int index;
    return GetAppendImageItem(listCtrl, columnCount, s, nImage, index);
}

/*static*/
bool CListCtrlHelper::GetAppendImageItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int nImage, int& index)
{
    index = listCtrl.GetItemCount();
    return InsertImageItem(listCtrl, columnCount, s, nImage, index);
}

/*static*/
bool CListCtrlHelper::InsertImageItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int nImage, int index)
{
    if (listCtrl.InsertItem(index, s[0], nImage) == -1)
    {
        return false;
    }
    CListCtrlHelper::SetItemTexts(listCtrl, columnCount, s, index);
    return true;
}

/*static*/
void CListCtrlHelper::SetItemTexts(CListCtrl& listCtrl, int columnCount, CStringArray& s, int index, int startColumn /*= 1*/)
{
    for (int iSubItem = startColumn; iSubItem < columnCount; iSubItem++)
    {
        listCtrl.SetItemText(index, iSubItem, s[iSubItem].GetBuffer(30));
    }
}

/*static*/
void CListCtrlHelper::SetImageItem(CListCtrl& listCtrl, int index, int column, int nImage)
{
    listCtrl.SetItem(index, column, LVIF_IMAGE, NULL, nImage, LVIS_STATEIMAGEMASK, LVIF_IMAGE, 0L);
}

/*static*/
void CListCtrlHelper::SetImageItemSelected(CListCtrl& listCtrl, int index, int nImage)
{
    listCtrl.SetItem(index, 0, LVIF_IMAGE, NULL, nImage, LVIS_SELECTED, LVIS_SELECTED, 0L);
}

/*static*/
bool CListCtrlHelper::GetListPositionByChar(CListCtrl& listCtrl, int letter, int& position)
{
    int firstPos = listCtrl.GetTopIndex();
    CString sFirstLetter = listCtrl.GetItemText(firstPos, 0);
    int nFirstLetter = (int)sFirstLetter.GetAt(0);
    int maxPos = listCtrl.GetItemCount();

    position = firstPos + letter - nFirstLetter;  //ausgewählte Position
    if (letter < nFirstLetter)
    {
        position += (int)AeGetApp()->Letter_Z() - (int)AeGetApp()->Letter_A() + 1;
    }
    if (position > maxPos)
    {
        position = -1;
        return false;
    }
    return true;
}

/*static*/
void CListCtrlHelper::SetFocusSelectedFocusedVisible(CListCtrl& listCtrl, int index)
{
    SetFocusSelectedFocused(listCtrl, index);
    listCtrl.EnsureVisible(index, 0);
}

/*static*/
void CListCtrlHelper::SetFocusSelectedFocused(CListCtrl& listCtrl, int index)
{
    SetItemStateSelectedFocused(listCtrl, index);
    listCtrl.SetFocus();
}

/*static*/
void CListCtrlHelper::SetFocusSelected(CListCtrl& listCtrl, int index)
{
    SetItemStateSelected(listCtrl, index);
    listCtrl.SetFocus();
}

/*static*/
void CListCtrlHelper::SetItemStateSelectedFocused(CListCtrl& listCtrl, int index)
{
    listCtrl.SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
}

/*static*/
void CListCtrlHelper::SetItemStateSelected(CListCtrl& listCtrl, int index)
{
    listCtrl.SetItem(index, 0, LVIF_STATE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED, 0L);
}

/*static*/
void CListCtrlHelper::SetItemStateClear(CListCtrl& listCtrl, int index)
{
    listCtrl.SetItemState(index, 0, LVIS_SELECTED | LVIS_FOCUSED);
}

/*static*/
void CListCtrlHelper::StepDownLinePosition(int nPosition, int nListItemCount)
{
    ++nPosition;
    if (nPosition > nListItemCount - 1)
    {
        nPosition = nListItemCount - 1;
    }
}

/*static*/
int CListCtrlHelper::GetImage(CListCtrl& listCtrl, int nPosition)
{
    LV_ITEM it;
    it.mask = LVIF_IMAGE;
    it.iItem = nPosition;
    it.iSubItem = 0;
    listCtrl.GetItem(&it);

    return it.iImage;
}

/*static*/
void CListCtrlHelper::CreateAndSetImageList(CListCtrl& listCtrl, CImageList& imageSmall, const std::vector<UINT>& idResources)
{
    if (imageSmall.GetSafeHandle() == NULL)
    {
        imageSmall.Create(SMALL_BITMAP_WIDTH,
            SMALL_BITMAP_HEIGHT,
            FALSE,  // list does not include masks
            idResources.size(),
            0); // list won't grow

        for (std::vector<UINT>::const_iterator iter = idResources.cbegin(); iter != idResources.cend(); ++iter)
        {
            HICON hIcon = AfxGetApp()->LoadIcon(*iter);
            ASSERT(hIcon != NULL);
            imageSmall.Add(hIcon);
        }
    }

    listCtrl.SetImageList(&imageSmall, LVSIL_SMALL);
}

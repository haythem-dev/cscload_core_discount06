#pragma once

#include <vector>

class CListCtrlHelper
{
public:
    static bool AddColumns(COLUMNS_TYPES* pTypeInit, CListCtrl& listCtrl);

    static bool AppendItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int startColumn = 1);

    static bool GetAppendItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int& index, int startColumn = 1);

    static bool InsertItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int index, int startColumn = 1);

    static bool InsertItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, LV_ITEM& lvi, int startColumn = 0);

    static bool AppendImageItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int nImage);

    static bool GetAppendImageItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int nImage, int& index);

    static bool InsertImageItem(CListCtrl& listCtrl, int columnCount, CStringArray& s, int nImage, int index);

    static void SetItemTexts(CListCtrl& listCtrl, int columnCount, CStringArray& s, int index, int startColumn = 1);

    static void SetImageItem(CListCtrl& listCtrl, int index, int column, int nImage);
    static void SetImageItemSelected(CListCtrl& listCtrl, int index, int nImage);

    static bool GetListPositionByChar(CListCtrl& listCtrl, int letter, int& position);

    static void SetFocusSelectedFocusedVisible(CListCtrl& listCtrl, int index);
    static void SetFocusSelectedFocused(CListCtrl& listCtrl, int index);
    static void SetFocusSelected(CListCtrl& listCtrl, int index);

    static void SetItemStateSelectedFocused(CListCtrl& listCtrl, int index);
    static void SetItemStateSelected(CListCtrl& listCtrl, int index);
    static void SetItemStateClear(CListCtrl& listCtrl, int index);

    static void StepDownLinePosition(int nPosition, int nListItemCount);

    static int GetImage(CListCtrl& listCtrl, int nPosition);

    static void CreateAndSetImageList(CListCtrl& listCtrl, CImageList& imageSmall, const std::vector<UINT>& idResources);
};

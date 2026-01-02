#pragma once

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_KB          0
#define COL_TOUR        1
#define COL_AUTO        2
#define COL_BTM         3
#define COL_KK          4
#define COL_K08         5
#define COL_K20         6

//This is when user click on the list
//WPARAM: Handle to list    LPARAM: Pointer to CListHitInfo
#define WM_QUICKLIST_CLICK              (WM_USER + 1981)
//This message is sent then the list needs data
//WPARAM: Handle to list    LPARAM: Pointer to CListItemData
#define WM_QUICKLIST_GETLISTITEMDATA    (WM_USER + 1979)


class CTourListCtrl;

//This structure is used to get information about an item.
class CListItemData
{
public:
    CListItemData();

    //Some obvius functions
    int GetItem() const;
    int GetSubItem() const;
    bool IsSelected() const;
    bool IsHot() const;
    bool m_noSelection;

    //The item text
    CString m_text;

    //Information about the button
    struct CListButton
    {
        //The style to use to draw the control.
        //Default value: DFCS_BUTTONCHECK
        //Use DFCS_CHECKED to draw the check mark.
        //Use DFCS_BUTTONRADIO for radio button, DFCS_BUTTONPUSH
        //for push button.
        //See CDC::DrawFrameControl for details.
        int m_style;

        //If you want to draw a button, set this to true
        //Default value: false
        bool m_draw;

        //Center the check box is the column. Useful if no text
        //Default value: false
        bool m_center;

        //Set this to true if you don't want to draw selection
        //mark under the control.
        //Default value: true
        bool m_noSelection;

    } m_button;

private:
    friend CTourListCtrl;

    void Reset();
    int m_item;
    int m_subitem;
    bool m_isSelected;
    bool m_isHot;
};

class CListHitInfo
{
public:
    int m_item;
    int m_subitem;
    bool m_onImage;
    bool m_onButton;
};

class CTourListCtrl : public CListCtrl
{
public:
    CTourListCtrl();
    virtual ~CTourListCtrl();

    virtual bool init();
    virtual void refreshItem(const int iItem);

    //Draw functions
    void DrawItem(int item, int subitem, CDC* pDC);

    void DrawButton(CListItemData& id, CDC* pDC);

    void DrawText(CListItemData& id, CDC* pDC);

    bool GetTextRect(const int item, const int subitem, CRect& rect);
    bool GetTextRect(CListItemData& id, CRect& rect);

    //Redraw text/progressbar in a column
    void RedrawText(const int topitem, const int bottomitem, const int column, BOOL erase = FALSE);

    //Redraw check boxs images in a column
    void RedrawCheckBoxs(const int topitem, const int bottomitem, const int column, BOOL erase = FALSE);

    //Redraw subitems in a column
    void RedrawSubitems(const int topitem, const int bottomitem, const int column, BOOL erase = FALSE);

    //Redraw subitems in a column
    void RedrawSubitems(int topitem, int bottomitem, int column, int part, BOOL erase);

    //Get the rect of specific items
    bool GetCheckboxRect(const int item, const int subitem, CRect& rect, bool checkOnly);
    bool GetCheckboxRect(CListItemData& id, CRect& rect, bool checkOnly);

    //Make sure that top and bottom is inside visible area
    //Return false in everything is outside visible area
    bool MakeInside(int& top, int &bottom);

    //Return true if an item is selected. NOTE: subitems (>0) is never selected if not full row selection is activated.
    bool IsSelected(const int item, const int subitem);

    //Return true if point is on an item. "item" and "subitem" shows which item the point is on.
    //If you want to now if the point is on a check box and/or image use the last two parameters.
    bool HitTest(const POINT& point, CListHitInfo &info);
    bool HitTest(const POINT& point, int& item, int& subitem, bool* onCheck=NULL);

    //Return true if full row select is activated
    bool FullRowSelect();

    //Returns information about a specific item (calling parent to get information)
    virtual CListItemData& GetItemData(const int item, const int subitem);

    //Used by GetItemData. Don't use this directly
    CListItemData m_lastget;

private:
    virtual bool isColEditable(const int iCol) const;
    virtual bool isColNumber(const int iCol) const;
    virtual UINT getLimitText(const int iCol) const;
    virtual bool setSubItem(const int iItem, const int iSubItem, CString& csText);

protected:
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg BOOL OnClickEx(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

    struct CListButton
    {
        //The style to use to draw the control.
        //Default value: DFCS_BUTTONCHECK
        //Use DFCS_CHECKED to draw the check mark.
        //Use DFCS_BUTTONRADIO for radio button, DFCS_BUTTONPUSH
        //for push button.
        //See CDC::DrawFrameControl for details.
        int m_style;

        //If you want to draw a button, set this to true
        //Default value: false
        bool m_draw;

        //Center the check box is the column. Useful if no text
        //Default value: false
        bool m_center;

        //Set this to true if you don't want to draw selection
        //mark under the control.
        //Default value: true
        bool m_noSelection;

    } m_button;
};

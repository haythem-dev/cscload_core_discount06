#pragma once

class CPageBrowser
{
private:
    int m_nLineCapacityOfPage;
    int m_nItemCountOfCurrentPage;
    int m_nCurrentPage;
    int m_nPageBeforeReset;

protected:
    bool m_bFirstDataset;   // Kennzeichen erster Satz
    bool m_bCursorOpen;     // Datenbankcursor geoeffnet

protected:
    CPageBrowser(int nLineCapacityOfPage);
    ~CPageBrowser();

    void Init(int nLineCapacityOfPage);

    void Reset();

    void ResetCursor();

    void SetItemCountOfCurrentPage(int nItemCountOfCurrentPage);

    bool GetFetchPositionOnPageSwitch(int nKzUpDown, int& nFetchPosition);
    bool GetFetchPositionOnPageSwitch(int nKzUpDown, long& lFetchPosition);

    long GetFetchStartPosition() const;

    long GetFetchPosition(int nDataSetCounter) const;

    int GetPageBeforeReset() const;

    void RestorePageBeforeReset();

    void SetCurrentPage(int nCurrentPage);

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);

    // pos: position after pressing a letter (A-Z) or Up and Down key
    // return: true=event handled
    bool OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult, CListCtrl& listCtrl, int& pos, bool bTestInRange = true, bool bTestNextPrev = true);

    // return: true=event handled
    bool OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult, CListCtrl& listCtrl, bool bTestInRange = true, bool bTestNextPrev = true);

    LRESULT OnHookNextPrev(LPARAM lpMsg);

private:
    long GetFetchBasePosition() const;

    bool OnHookNextPrev(unsigned int key);
};

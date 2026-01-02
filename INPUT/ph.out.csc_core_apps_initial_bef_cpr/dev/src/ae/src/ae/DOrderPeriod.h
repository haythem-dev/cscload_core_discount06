#pragma once
#include <afxstr.h>
#include <auftraginfo.h>
#include <string.h>
#include <orders.h>

class CDOrderPeriod : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDOrderPeriod)

public:
    CDOrderPeriod(short branchNo, long idfNo, CWnd* pParent = NULL);
    virtual ~CDOrderPeriod();

    enum { IDD = IDD_AE_ORDER_PERIOD };

    enum SORT_PARAMS { Empty = 0, Tourid = 1, Day = 2, FromTime = 3 };

    CString SORT_PARAMS_STRING[4];

    //GUI Elements
    CStatic lblIdfNo;
    CStatic lblTourID;
    CStatic lblSortPara1;
    CStatic lblSortPara2;
    CStatic lblSortPara3;
    CStatic lblDayOfWeek;
    CStatic lblHintUserChange;

    CEdit txtIdfNo;

    CComboBox cmbTourID;
    CComboBox cmbSortPara1;
    CComboBox cmbSortPara2;
    CComboBox cmbSortPara3;
    CComboBox cmbDayOfWeek;

    CButton btnSelect;
    CButton btnInsertData;
    CButton btnCancel;
    CButton btnChangeData;
    CButton btnResetSort;
    CButton btnDeleteData;

    CButton gbcSearch;
    CButton gbcSort;

    CListCtrl lstOrderPeriod;

    //GUI listeners
    DECLARE_MESSAGE_MAP()
    afx_msg void OnIdfInputFinished();
    afx_msg void OnCmbSortPara1Choosen();
    afx_msg void OnCmbSortPara2Choosen();
    afx_msg void OnBtnClickedCancel();
    afx_msg void OnBtnClickedInsert();
    afx_msg void OnBtnClickedDelete();
    afx_msg void OnBtnClickedUpdate();
    afx_msg void OnBtnClickedSelect();
    afx_msg void OnBtnClickedResetComboBoxes();
    afx_msg void OnLvnKeydownListOrderPeriod(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnListNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDblClickList(NMHDR* pNMHDR, LRESULT* pResult);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

private:
    bool cursorEnd;
    bool collectiveOrder;
    short _branchNo;
    long _idfNo;

    //Show how many lines in the list
    static const int ZEILEN=14;

    //how many columns are shown in the list
    static const int NUM_COLUMNS=12;

    //Names and index of the columns
    enum columnIndex
    {
        COL_DAY_OF_WEEK = 0,
        COL_TIME_FROM = 1,
        COL_TIME_TILL = 2,
        COL_TIME_MAIN = 3,
        COL_TOURID= 4,
        COL_CLOSE_TIME_1 = 5,
        COL_CLOSE_TIME_2 = 6,
        COL_CLOSE_TIME_3 = 7,
        COL_HIDDEN_ID = 8,
        COL_HIDDEN_ID_TIME = 9,
        COL_HIDDEN_WEEKDAY_INT = 10,
        COL_HIDDEN_IDF = 11
    };

    //Shows how many elements are currently fetched. It's positioned on the entry that is to be read next.
    int fetchCount;

    //DB Accessors
    CORDERPERIOD orderPeriod;//SelTourData - vz; opt: custNo, tourid

    //functions
    BOOL OnInitDialog();
    void OnDestroy();
    std::string GetDayOfWeekForSelection(int selectedValue);
    bool InitComboBoxes();
    void GetDataAndFillGui();
    bool prepareSQL();
    void fillTable();
    bool CheckRowPeriodMisMatch(int itemIndex);
    int getSearchParamNumber(CString selectedValue);
    void ResetSortComboBoxes();
    int GetWeekdayCount(int opID);
};

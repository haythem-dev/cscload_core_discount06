#pragma once
#include <afxstr.h>
#include <auftraginfo.h>

class CDCollectiveOrdersDE : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCollectiveOrdersDE)

public:
    CDCollectiveOrdersDE(CWnd* pParent = NULL);
    virtual ~CDCollectiveOrdersDE();

    enum { IDD = IDD_AE_COLLECTIVE_ORDERS_DE };

    //GUI ELements
    CListCtrl listCollOrders;
    CButton btnSelect;
    CButton btnSelCount;
    CEdit txtOrderNo;
    CEdit txtIdfNo;
    CEdit txtOrderCloseNumber;
    CStatic lblRowCount;
    CStatic lblRowCountValue;
    CStatic lblOpenCO;
    CStatic lblSearch;
    CStatic lblOrderNo;
    CStatic lblIDFNo;
    CStatic lblMaskType;
    CStatic lblOrderCloseNumber;
    CButton btnCloseOrder;
    CButton btnCancel;

    //GUI listeners
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedBtnSelect();
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedBtnCancel();
    afx_msg void OnBnClickedBtnCloseorder();
    afx_msg void OnBnClickedButtonGetCount();

    virtual BOOL OnInitDialog();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

private:
    bool cursorEnd;
    bool collectiveOrder;

    //Show how many lines in the list
    static const int ZEILEN=14;

    //how many columns are shown in the list
    static const int NUM_COLUMNS=7;

    //Names and index of the columns
    enum columnIndex
    {
        COL_KURZ_AUFTR_NR = 0,
        COL_IDF_NR = 1,
        COL_TOUR = 2,
        COL_A_ART = 3,
        COL_APOTHEKE = 4,
        COL_ORT = 5,
        COL_VZ = 6,
    };

    //Shows how many elements are currently fetched. It's positioned on the entry that is to be read next.
    int fetchCount;

    //struct used for sql reads
    CCOLLECTIVEORDERS collOrder;
    CCOLLECTIVEORDERS collOrderCount;

    /* Closes Order at KSC Server*/
    bool CloseOrderKSC(long orderNo);

    /* THis functions gets a count of all the input data and returns this value */
    int perfCountSQL();

    /* This function handles the cursor and list entries, before it calls the prepareSQL and fillTable functions */
    void getDataAndFillGui();

    /* Loops over the lines to be shown and calls the prepared sql, then adds the data into the list */
    void fillTable();

    /* Performs some checks on the input data before preparing the SQL */
    bool prepareSQL(CCOLLECTIVEORDERS& co);

    bool CloseOrders();
    void CloseOrdersList();
public:
    afx_msg void OnBnClickedButtonMarkAll();
};

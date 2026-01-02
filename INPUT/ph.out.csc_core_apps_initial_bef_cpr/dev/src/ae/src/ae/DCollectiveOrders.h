#pragma once

#include <afxstr.h>
#include <auftraginfo.h>


// CDCollectiveOrders-Dialogfeld

class CDCollectiveOrders : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCollectiveOrders)

public:
    CDCollectiveOrders(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDCollectiveOrders();

// Dialogfelddaten
    enum { IDD = IDD_AE_COLLECTIV_ORDERS };

    //GUI ELements
    CComboBox cmbSort;
    CComboBox cmbMaskType;
    CComboBox cmbVIP;
    CListCtrl listCollOrders;
    CButton btnSelect;
    CEdit txtOrderNo;
    CEdit txtIdfNo;
    CEdit txtCustClass;
    CEdit txtRepresentative;
    CEdit txtCreaDate;
    CEdit txtDeliveryDate;
    CEdit txtRegion;
    CEdit txtArticleNo;
    CEdit txtWholesaleBranch;
    CStatic lblOpenCO;
    CStatic lblSearch;
    CStatic lblOrderNo;
    CStatic lblIDFNo;
    CStatic lblCustClass;
    CStatic lblRepresentative;
    CStatic lblCreationDate;
    CStatic lblDeliveryDate;
    CStatic lblRegion;
    CStatic lblSort;
    CStatic lblFormat;
    CStatic lblVIP;
    CStatic lblMaskType;
    CStatic lblArticleNo;
    CStatic lblWholesaleBranch;
    CButton btnCloseOrder;
    CButton btnCancel;

    //GUI listeners
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedBtnSelect();
    afx_msg void OnMaskTypeChoose();
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedBtnCancel();
    afx_msg void OnBnClickedBtnCloseorder();
    afx_msg void OnLvnKeydownListCollOrder(NMHDR* pNMHDR, LRESULT* pResult);

    virtual BOOL OnInitDialog();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

private:
    bool cursorEnd;
    bool collectiveOrder;

    //Show how many lines in the list
    static const int ZEILEN = 11;

    //how many columns are shown in the list
    static const int NUM_COLUMNS = 17;

    //Names and index of the columns
    enum columnIndex
    {
        COL_KENNBUCHSTABE = 0,
        COL_ZUGRUND = 1,
        COL_KZ_PATA = 2,
        COL_KURZ_AUFTR_NR = 3,
        COL_IDF_NR = 4,
        COL_TOUR = 5,
        COL_A_ART = 6,
        COL_DFU = 7,
        COL_PH = 8,
        COL_APOTHEKE = 9,
        COL_ORT = 10,
        COL_ABC = 11,
        COL_ENDE = 12,
        COL_KZ_ANZ_ALPHA_TXT = 13,
        COL_TRM = 14,
        COL_VZ = 15,
        COL_ZG_WERT = 16,
    };

    //Shows how many elements are currently fetched. It's positioned on the entry that is to be read next.
    int fetchCount;

    //struct used for sql reads
    CCOLLECTIVEORDERS collOrder;

    /* This function handles the cursor and list entries, before it calls the prepareSQL and fillTable functions */
    void getDataAndFillGui();

    /* Loops over the lines to be shown and calls the prepared sql, then adds the data into the list */
    void fillTable();

    /* Performs some checks on the input data before preparing the SQL */
    bool prepareSQL();

public:
    afx_msg void OnBnClickedButtonMarkAll();
};

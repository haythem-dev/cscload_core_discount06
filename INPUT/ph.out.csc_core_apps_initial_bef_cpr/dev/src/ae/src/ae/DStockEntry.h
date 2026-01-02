#pragma once

#include <atlcomtime.h>


// CDStockEntry-Dialogfeld

class CDStockEntry : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDStockEntry)

public:
    CDStockEntry(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDStockEntry();

// Dialogfelddaten
    enum { IDD = IDD_AE_STOCKENTRY };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()

public:
    CDateTimeCtrl m_DT_Datum;
    COleDateTime m_date_Datum;
    CEdit m_edit_Vz;
    CString m_cVZ;
    CListCtrl m_ListCtl;

private:
    CSTOCKENTRY m_StockEntry;
    void GetPage();             // List-Box mit Eintraegen versorgen
    void RepositionWindow();

public:
    afx_msg void OnEnChangeEditVz();
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonDruck();
};

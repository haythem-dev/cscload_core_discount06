#pragma once
#include <eilbotendruck.h>


// CDExtraTourReasons dialog

class CDExtraTourReasons : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDExtraTourReasons)

public:
    CDExtraTourReasons(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDExtraTourReasons();

    enum { IDD = IDD_AE_EXTRA_TOUR_REASON };
    CEdit m_EditReason;
    CString m_Reason;
    CComboBox m_AArt;
    CEXTRATOURREASONS m_extrareasons;
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonDelete();
    DECLARE_MESSAGE_MAP()

    void GetPage();     // List-Box mit Eintraegen versorgen
};

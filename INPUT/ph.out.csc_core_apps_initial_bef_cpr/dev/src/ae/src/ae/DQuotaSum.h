#pragma once

#include "NMDProgress.h"


// CDQuotaSum-Dialogfeld

class CDQuotaSum : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDQuotaSum)

public:
    CDQuotaSum(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDQuotaSum();

    enum { IDD = IDD_AE_QUOTA_SUM };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonDruck();
    afx_msg void OnBnClickedButtonDetails();
    afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

    int m_iDetails;
    CListCtrl m_ListCtl;

private:
    int m_iCountlist;
    int m_iCol;
    int m_iOrder;
    CNMDProgress m_dlgProgress;
};

#pragma once


class CRangeListCtrl;

// CDShowRanges-Dialogfeld

class CDShowRanges : public CDialogMultiLang, CPageBrowser
{
    DECLARE_DYNAMIC(CDShowRanges)

public:
    CDShowRanges(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDShowRanges();

// Dialogfelddaten
    enum { IDD = IDD_AE_SHOW_RANGES };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual void OnOK();
    CRangeListCtrl* m_ListCtl;

    DECLARE_MESSAGE_MAP()

public:
    virtual BOOL OnInitDialog();

    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult);
};

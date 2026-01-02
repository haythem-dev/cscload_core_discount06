#pragma once

#include "DPromoBuch.h"

// CDPromotionen-Dialogfeld

class CDPromotionen : public CDialogMultiLang, CPageBrowser
{
    DECLARE_DYNAMIC(CDPromotionen)

public:
    CDPromotionen(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDPromotionen();

// Dialogfelddaten
    enum { IDD = IDD_AE_PROMOTIONEN };
    CListCtrl m_List1;
    CListCtrl m_List2;
    CListCtrl m_List3;
    long m_lKundennr;
    long m_lCustomerno;
    short m_sVznr;
    short m_sPromoNo;
    CAeDoc* m_ptrDoc;                   // Zeiger auf das Dokument
    long m_lMinMeng;
    double m_dMinValue;
    CString m_cEKG;
    long m_lDISCGRP;
    CDPromoBuch m_buch;
    CString m_csSuch;
    virtual void GetMembers(int pos);
    virtual void GetRabs(int pos);
    void SuchePromoNo(int no);
    void SetzeWerte(int pos);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnDblclkList1();
    //afx_msg void OnSelChangeList1();
    afx_msg void OnSelChangeList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonSuche();

    DECLARE_MESSAGE_MAP()

private:
    void HandleSearchResult(int pos);
};

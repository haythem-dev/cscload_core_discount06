#pragma once

// DReimport.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDReimport

class CDReimport : public CDialogMultiLang, CPageBrowser
{
// Konstruktion
public:
    CDReimport(CWnd* pParent = NULL);   // Standardkonstruktor

    long m_lPZN;
    CString m_CArtikelName;
    CString m_CEinheit;
    CString m_CDarfor;

    enum { IDD = IDD_REIMPORT };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    CREIMPORT m_CReimp;

    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
};

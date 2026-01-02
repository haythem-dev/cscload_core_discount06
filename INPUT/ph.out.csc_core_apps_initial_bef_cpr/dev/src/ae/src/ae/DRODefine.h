#pragma once

#include <customer.h>

class CROListCtrl;


// CDRODefine-Dialogfeld

class CDRODefine : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDRODefine)

public:
    CDRODefine(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDRODefine();

// Dialogfelddaten
    enum { IDD = IDD_AE_RO_DEFINE };
    CROListCtrl* m_List1;
    CString m_cVon;
    CString m_cBis;
    vector<cstdiscaccS> m_pldisc; // pointer to class list
    vector <cstdiscaccS>::iterator m_itdisc;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    void CalcSumme();
    afx_msg void OnButtonDone();
    afx_msg void OnItemchangedListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnCalcSumme(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()

protected:
    double m_dSumme;
    double m_dGut;
    bool m_bFertig;
};

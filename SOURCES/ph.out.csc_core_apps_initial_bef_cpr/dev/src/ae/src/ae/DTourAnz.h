#pragma once

// DTourAnz.h : Header-Datei
//
#include <customer.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDTourAnz

class CDTourAnz : public CDialogMultiLang
{
// Konstruktion
public:
    CDTourAnz(CWnd* pParent = NULL);   // Standardkonstruktor
    void SetVzNr(const short sVzNr) { m_sSaleCenterNo = sVzNr; }
    short GetVzNr() { return m_sSaleCenterNo; }
    void SetKundenNr(const long lKundenNr) { m_lCustomerNo = lKundenNr; }
    long GetKundenNr() { return m_lCustomerNo; }

    enum { IDD = IDD_AE_TOUREN };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnButtonUpdate();
    afx_msg void OnButtonChange();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

    //members
    long m_lCustomerNo;
    short m_sSaleCenterNo;
    CTOURPFLEGE m_Touren;

    //methodes
    void SetHeader();
    void GetPage();
    bool SelKunde();
};

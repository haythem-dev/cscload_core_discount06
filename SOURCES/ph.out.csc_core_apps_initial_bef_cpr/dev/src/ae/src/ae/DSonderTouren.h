#pragma once

// DSonderTouren.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDSonderTouren

class CDSonderTouren : public CDialogMultiLang
{
// Konstruktion
public:
    CDSonderTouren(CWnd* pParent = NULL);   // Standardkonstruktor
    void SetVzNr(const short sVzNr) { m_sSaleCenterNo = sVzNr; }
    short GetVzNr() { return m_sSaleCenterNo; }

    enum { IDD = IDD_AE_SONDER_TOUR };
    CListCtrl m_ListCtl;
    CEdit m_edit_TourId;
    CEdit m_edit_AArt;
    CString m_CAArt;
    CString m_CTourId;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    afx_msg void OnChangeAart();
    afx_msg void OnChangeTourid();
    afx_msg void OnButtonDelete();
    afx_msg void OnButtonInsert();
    virtual BOOL OnInitDialog();
    afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonUpdate();
    afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

    //members
    long m_lCustomerNo;
    short m_sSaleCenterNo;
    CSONDERTOUREN m_Touren;

    //methodes
    void GetPage();
    void GetWerte();
};

#pragma once


// CDTenderWahl-Dialogfeld

class CDTenderWahl : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDTenderWahl)

public:
    CDTenderWahl(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDTenderWahl();

    enum { IDD = IDD_AE_TENDER_AUSWAHL };
    CListCtrl m_List1;
    short m_sVz;
    long m_lKnd;
    long m_lTenderNo;
    long m_ArtikelNr;
    int m_iStaat;   //1 = Staatstender Bulgarien
    CString m_cContract;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonPzn();
    afx_msg void OnBnClickedButtonAlle();
    int GetPageAlle();

    DECLARE_MESSAGE_MAP()
};

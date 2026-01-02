#pragma once


// CDHerstWahl-Dialogfeld

class CDHerstWahl : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDHerstWahl)

public:
    CDHerstWahl(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDHerstWahl();

    enum { IDD = IDD_AE_WAHL_HERST };
    CListCtrl m_ListCtl;

    long GetHerstNr() { return m_hersteller_nr; }
    void SetHerstName(CString s) { m_hersteller_name = s; }

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    afx_msg void OnBnClickedOk();
    afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

private:
    long m_hersteller_nr;
    CString m_hersteller_name;
};

#pragma once


// CDCountrCodes-Dialogfeld

class CDCountrCodes : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCountrCodes)

public:
    CDCountrCodes(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDCountrCodes();

    enum { IDD = IDD_AE_COUNTRY_CODE };
    CListCtrl m_ListCtl;
    CCCODE m_CountryCode;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

private:
    void FillList();
};

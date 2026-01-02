#pragma once


// CDStellerAnz-Dialogfeld

class CDStellerAnz : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDStellerAnz)

public:
    CDStellerAnz(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDStellerAnz();

    enum { IDD = IDD_AE_STELLER_ANZ };
    CListCtrl m_List1;
    long m_lArtikelNr;
    short m_sVzNr;
    bool m_bNosteller;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );

    DECLARE_MESSAGE_MAP()
};

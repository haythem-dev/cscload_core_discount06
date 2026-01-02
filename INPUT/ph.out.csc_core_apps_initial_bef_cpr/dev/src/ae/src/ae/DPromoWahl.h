#pragma once


// CDPromoWahl-Dialogfeld

class CDPromoWahl : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDPromoWahl)

public:
    CDPromoWahl(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDPromoWahl();

// Dialogfelddaten
    enum { IDD = IDD_AE_PROMO_WAHL };
    CString m_promo;
    short m_sPromoNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    CListCtrl m_List1;
    afx_msg void OnBnClickedOk();
    DECLARE_MESSAGE_MAP()
};

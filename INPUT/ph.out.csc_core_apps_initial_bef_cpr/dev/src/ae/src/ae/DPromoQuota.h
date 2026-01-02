#pragma once
#include <promoinfo.h>


// CDPromoQuota-Dialogfeld

class CDPromoQuota : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDPromoQuota)

public:
    CDPromoQuota(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDPromoQuota();

// Dialogfelddaten
    enum { IDD = IDD_AE_PROMOQUOTA };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()
public:
    CString m_cKndNr;
    CString m_cPromoNr;
    afx_msg void OnBnClickedButtonKunde();
    afx_msg void OnBnClickedButtonPromo();
    afx_msg void OnBnClickedButtonAll();
    afx_msg void OnBnClickedButtonAnzKnd();
    afx_msg void OnBnClickedButtonAnzPromo();
    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangeEditIdf();
    afx_msg void OnEnChangeEditPromono();
    CEdit m_edit_IDF;
    CEdit m_edit_PromoNo;
    CString m_CMC;
    CString m_CPromo;
    long m_lKunde;
    short m_sPromo;
    CListCtrl m_List1;
    CPROMOQUOTAANZ m_Promoanz;
    CPROMOQUOTACSTANZ m_Promoanzcst;
    void FillList();    // List-Box mit Eintraegen versorgen
    CLetterMan m_kb;
    CStringArray m_s;
};

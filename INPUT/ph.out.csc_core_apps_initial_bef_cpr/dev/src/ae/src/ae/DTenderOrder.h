#pragma once

#include "TListctrl.h"

// CDTenderOrder-Dialogfeld

class CDTenderOrder : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDTenderOrder)

public:
    CDTenderOrder(CWnd* pParent = NULL);    // Standardkonstruktor
    CAeDoc *ptrDoc;                         // Zeiger auf das Dokument
    virtual ~CDTenderOrder();

// Dialogfelddaten
    enum { IDD = IDD_AE_TENDER_ORDER };
    CTListCtrl m_List1;
    long m_lTenderNo;
    double m_dPct;
    CString m_CMenge;
    CEdit   m_EditMenge;
    long m_lKndNr;
    CString m_CSuch;
    CString m_Charge;
    CEdit   m_EditSuch;
    bool    m_bChain;
    BOOL    m_bIgnore;      // trotz Preislimitüberschreitung buchen BG

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnChangeEditMenge();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonSave();
    afx_msg void OnButtonBearb();
    afx_msg void OnButtonSuch();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );

    DECLARE_MESSAGE_MAP()

    COLORREF fgb;
    COLORREF bgg;

    bool Auswahl(int pos);
    double GetBrutto(double preis,double tax);

// Members
protected:
    struct SaveArtikel
    {
        long ArtNo;
        long Menge;
    };

    vector<SaveArtikel> m_pl; // pointer to class list
    vector <SaveArtikel>::iterator m_it;
};

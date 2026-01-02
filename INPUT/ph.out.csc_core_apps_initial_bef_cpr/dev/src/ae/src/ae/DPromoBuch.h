#pragma once
#include "DPromotionen.h"

class CDPromotionen;
class CPMListCtrl;
class CPRListCtrl;

// CDPromoBuch-Dialogfeld

class CDPromoBuch : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDPromoBuch)

public:
    CDPromoBuch(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDPromoBuch();

    enum { IDD = IDD_AE_PROMO_BUCHEN };
    CListCtrl *m_pListPromo;
    CListCtrl *m_pListMember;
    CListCtrl *m_pListRabatte;
    CPMListCtrl *m_List1;
    CPRListCtrl *m_List2;
    CString m_cPromotion;
    CString m_cMinMeng;
    CString m_cMinValue;
    CString m_cAufWert;
    CString m_cEKG;
    CString m_cDISCGRP;
    CString m_cAddDisc;
    CComboBox m_ComboTyp;
    CComboBox m_ComboFaktor;
    short m_sSpec;
    short m_sPromono;
    short m_sPreistyp;
    double m_dPct;
    long m_lManu;
    long m_lDiscGrp;
    short m_sVznr;
    short m_sAnzList;
    CAeDoc* m_ptrDoc;           // Zeiger auf das Dokument
    CDPromotionen* m_pFather;
    CString m_csSuch;
    CEdit m_editSuch;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnDblclkList1();
    afx_msg void OnDblclkList2();
    afx_msg void OnItemchangedListCtrl   (NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnItemchangedListCtrl2   (NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCbnSelchangeComboTyp();
    afx_msg void OnCbnSelchangeComboFaktor();
    afx_msg LRESULT OnSetItem(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnSetItem2(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnSetSuch(WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedButtonBestTA();
    afx_msg void OnNMSetfocusList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnLvnItemActivateList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonSuche();
    DECLARE_MESSAGE_MAP()

    int     FillDialog();
    double  GetNetPrice(double preis,double discount);
    void    SetPrices();
    int     PosBuchen();
    double  GetBrutto(double preis,double tax);
    void    SetZeilenWert(int pos);
    bool    CheckInput(int pos);
    bool    CheckRabInput(int pos);
    bool    CalcAufWert();
    int     CheckMultiple();
    int     ChangeFaktor(int iFaktor);
    void    GetMembers();
    int     CheckBestTA();
    COLORREF bg;
    COLORREF fg;
    COLORREF bg2;
    COLORREF fg2;
    COLORREF bgg;
    COLORREF fgb;
    COLORREF bgy;

protected:
    int  m_iItem;
    int  m_iItem_old;
    int  m_iItem2;
    int  m_iItem2_old;
    bool m_bSteller;
    int  m_iStellerTyp;
    long m_lMinQty;
    double m_dMinValue;
    int  m_iFaktor;
    bool m_bReturn;
    bool m_bScale;
    struct sTobook
    {
        long PZN;
        long MENGE;
    };
    vector<sTobook>* m_plTobook; // pointer to class list
    int iAnzPl;
};

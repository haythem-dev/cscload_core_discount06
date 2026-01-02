#pragma once

#include "PPListctrl.h"

// CDProductPromo-Dialogfeld

class CDProductPromo : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDProductPromo)

public:
    CDProductPromo(CWnd* pParent = NULL);
    virtual ~CDProductPromo();

    enum { IDD = IDD_AE_PRODUKT_PROMO };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnItemchangedListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnCancel();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnSetItem(WPARAM wParam, LPARAM lParam);
    afx_msg void OnButtonBuchen();
    afx_msg void OnButtonEnde();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnEnChangeEditSuch();
    afx_msg void OnBnClickedButtonSuch();
    afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);

    DECLARE_MESSAGE_MAP()
    double  GetNetPrice(double preis, double discount);
    double  GetBrutto(double preis, double tax);
    bool    CheckInput(int pos);
    bool    CalcAufWert();
    int     PosBuchen(CAUFPOSBUCH* aufposbuch, bool bChange);
    void    SortList1(int col);

public:
    CAeDoc* m_ptrDoc;       // Zeiger auf das Dokument
    long m_lCustomerno;
    short m_sBranchno;

private:
    CPPListCtrl m_List1;
    CString m_cAufWert;
    int     m_iItem;
    CEdit   m_EditSuch;
    CString m_CSuch;
};

#pragma once

#include <artikel.h>
#include <customer.h>

#define Natra 0
#define Netto 1
#define Other 2

// CDShowRebates dialog

class CDShowRebates : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDShowRebates)

public:
    CDShowRebates(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDShowRebates();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    enum { IDD = IDD_AE_SHOW_REBATES };

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

public:
    int m_Typ;
    CString m_cName;
    CString m_cNumber;
    CString m_cAEP;
    CString m_cMenge;
    CListCtrl m_List1;
    void InitListNatra();
    void InitListNetto();
    void InitListOther();
    void FillListNatra();
    void FillListNetto();
    void FillListOther();
    void SetArtNr(long ArtikelNr) { m_ArtikelNr = ArtikelNr; }
    void SetKndNr(long KndNr) { m_lKndNr = KndNr; }
    void SetFilialNr(short FilialNr) { m_FilialNr = FilialNr; }
    void SetOrgFilialNr(short OrgFilialNr) { m_OrgFilialNr = OrgFilialNr; }
    short GetOrgFilialNr() { return m_OrgFilialNr; }
    short GetFilialNr() { return m_FilialNr; }
    long GetArtNr() { return m_ArtikelNr; }

    CDISCOUNTANZ m_Discount;        //neue Rabatte
    vector<discountanzS> m_pldisc;  // pointer to class list
    vector <discountanzS>::iterator m_itdisc;
    vector<paytermS> m_plpay; // pointer to class list

protected:
    long m_ArtikelNr;
    long m_lKndNr;
    short m_FilialNr;
    short m_OrgFilialNr;
    int m_iBasis;
};

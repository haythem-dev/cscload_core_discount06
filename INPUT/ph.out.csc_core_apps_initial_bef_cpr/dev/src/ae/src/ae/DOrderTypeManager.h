#pragma once
#include "PageTabCtrlMultiLang.h"
#include "ppDataTypes.h"
#include "TabPageMultiLang.h"

class CDOrderTypeManager;
class CDOrderTypeManager1;
class CDOrderTypeManager2;
class CDOrderTypeManager3;
class CDOrderTypeManager4;
class CDOrderTypeManager5;
class CDOrderTypeManager6;


// CDOrderTypeManager1 dialog

class CDOrderTypeManager1 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderTypeManager1)

public:
    CDOrderTypeManager1();
    virtual ~CDOrderTypeManager1();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDERTYPE_MANAGER1 };
#endif

    CDOrderTypeManager* m_pFather;

    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditBezeichnung();
    afx_msg void OnBnClickedCheckImmerGuelt();
    afx_msg void OnBnClickedCheckBild();
    afx_msg void OnBnClickedCheckstockreservation();
    afx_msg void OnBnClickedCheckDafue();
    afx_msg void OnBnClickedCheckStandard();
    DECLARE_MESSAGE_MAP()

    virtual int GetID() { return IDD; }
    virtual LPCTSTR GetTabTitle();
    virtual void SetIsActive(const bool isActive = true) { m_bIsActive = isActive; }
};


// CDOrderTypeManager2 dialog

class CDOrderTypeManager2 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderTypeManager2)

public:
    CDOrderTypeManager2();
    virtual ~CDOrderTypeManager2();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDERTYPE_MANAGER2 };
#endif

    CDOrderTypeManager* m_pFather;

    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnBnClickedCheckAufNachl();

    afx_msg void OnBnClickedCheckAufCons();
    afx_msg void OnBnClickedCheckAufDeferOrder();
    afx_msg void OnBnClickedCheckAufNopart();
    afx_msg void OnBnClickedCheckAufNodd();
    DECLARE_MESSAGE_MAP()

    virtual int GetID() { return IDD; }
    virtual LPCTSTR GetTabTitle();
    virtual void SetIsActive(const bool isActive = true) { m_bIsActive = isActive; }
public:
    afx_msg void OnBnClickedCheckAufNoquota();
};


// CDOrderTypeManager3 dialog

class CDOrderTypeManager3 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderTypeManager3)

public:
    CDOrderTypeManager3();
    virtual ~CDOrderTypeManager3();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDERTYPE_MANAGER3 };
#endif

    CDOrderTypeManager* m_pFather;
    CButton m_natra;
    CButton m_netto;

    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnBnClickedCheckHand();
    afx_msg void OnBnClickedCheckDiscount();
    afx_msg void OnBnClickedCheckMuss();
    afx_msg void OnBnClickedCheckFreePrice();
    afx_msg void OnBnClickedCheckAufOnlyeh();
    afx_msg void OnBnClickedCheckAufNoPromo();
    afx_msg void OnBnClickedCheckNatra();
    afx_msg void OnBnClickedCheckNetto();
    DECLARE_MESSAGE_MAP()

    virtual int GetID() { return IDD; }
    virtual LPCTSTR GetTabTitle();
    virtual void SetIsActive(const bool isActive = true) { m_bIsActive = isActive; }
};


// CDOrderTypeManager4 dialog

class CDOrderTypeManager4 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderTypeManager4)

public:
    CDOrderTypeManager4();
    virtual ~CDOrderTypeManager4();

    CListCtrl m_ListCtl;

    virtual BOOL OnSetActive();

    BOOL CheckExist(int Reservtyp, int Prio);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDERTYPE_MANAGER4 };
#endif

    CDOrderTypeManager* m_pFather;
    CString m_CKBst;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonPlus();
    afx_msg void OnBnClickedButtonMinus();
    afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

    virtual int GetID() { return IDD; }
    virtual LPCTSTR GetTabTitle();
    virtual void SetIsActive(const bool isActive = true) { m_bIsActive = isActive; }
    void ReadDataInListBox();
};


// CDOrderTypeManager5 dialog

class CDOrderTypeManager5 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderTypeManager5)

public:
    CDOrderTypeManager5();
    virtual ~CDOrderTypeManager5();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDERTYPE_MANAGER5 };
#endif

    CDOrderTypeManager* m_pFather;

    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnBnClickedCheckAllowDesiredBatch();
    afx_msg void OnBnClickedCheckAllowFixedBatch();
    afx_msg void OnBnClickedCheckForbidUserChange();
    DECLARE_MESSAGE_MAP()

    virtual int GetID() { return IDD; }
    virtual LPCTSTR GetTabTitle();
    virtual void SetIsActive(const bool isActive = true) { m_bIsActive = isActive; }
};


// CDOrderTypeManager6 dialog

class CDOrderTypeManager6 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderTypeManager6)

public:
    CDOrderTypeManager6();
    virtual ~CDOrderTypeManager6();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDERTYPE_MANAGER6 };
#endif

    CDOrderTypeManager* m_pFather;
    CButton m_mitkennung;
    CButton m_mitivc;
    CButton m_mitorginvoice;

    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnBnClickedCheckAufMitKennung();
    afx_msg void OnBnClickedCheckAufMitIvc();
    afx_msg void OnBnClickedCheckAufMitOrginvoice();
    afx_msg void OnBnClickedCheckMustHeadline();
    DECLARE_MESSAGE_MAP()

    virtual int GetID() { return IDD; }
    virtual LPCTSTR GetTabTitle();
    virtual void SetIsActive(const bool isActive = true) { m_bIsActive = isActive; }
};

// CDOrderTypeManager dialog

class CDOrderTypeManager : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDOrderTypeManager)

public:
    CDOrderTypeManager(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDOrderTypeManager();

    enum { IDD = IDD_AE_ORDERTYPE_MANAGER };
    CPageTabCtrlMultiLang m_CTabCtrlOrderTypeManager;

    CDOrderTypeManager1 m_PageDOrderTypeManager1;
    CDOrderTypeManager2 m_PageDOrderTypeManager2;
    CDOrderTypeManager3 m_PageDOrderTypeManager3;
    CDOrderTypeManager4 m_PageDOrderTypeManager4;
    CDOrderTypeManager5 m_PageDOrderTypeManager5;
    CDOrderTypeManager6 m_PageDOrderTypeManager6;

    short m_sSaleCenterNo;
    CEdit m_EditKBst;
    CString m_CKBst;
    CEdit m_EditBezeichnung;
    CEdit m_EditTyp;
    CString m_CBezeichnung;

    BOOL m_bUpdate;     // Schalter ob Update oder Insert
    BOOL m_bGlobal;
    BOOL m_bNatra;
    BOOL m_bNetto;
    BOOL m_bBild;
    BOOL m_bDafue;
    BOOL m_bHand;
    BOOL m_bDiscount;
    BOOL m_bStandard;
    BOOL m_bsaveStandard;
    BOOL m_bMuss;
    BOOL m_bFreePrice;
    BOOL m_bAufCons;
    BOOL m_bAufNachl;
    BOOL m_bNoQuota;
    BOOL m_bDeferOrder;
    BOOL m_bNoPart;
    BOOL m_bNoDD;
    BOOL m_bOnlyEH;
    BOOL m_bIVC;
    BOOL m_bOrgInvoice;
    BOOL m_bNoPromo;
    BOOL m_bDefaultKennung;
    BOOL m_bAllowDesired;
    BOOL m_bAllowFixed;
    BOOL m_bForbidChange;
    BOOL m_bConsultationNeeded;
    BOOL m_bNoLinefee;
    BOOL m_bNoPackagefee;
    BOOL m_bMustHeadline;
    BOOL m_bStockreservation;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    virtual void OnOK();
    afx_msg void OnChangeEditKbst();
    DECLARE_MESSAGE_MAP()

    bool AreChanged();
};

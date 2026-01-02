#pragma once


// CDCstBranchInfoUpd-Dialogfeld

class CDCstBranchInfoUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCstBranchInfoUpd)

public:
    CDCstBranchInfoUpd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDCstBranchInfoUpd();
    CListCtrl m_ListCtl;

// Dialogfelddaten
    enum { IDD = IDD_AE_CST_BRANCH_INFO_UPD };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonInsert();
    afx_msg void OnButtonUpdate();
    afx_msg void OnButtonDelete();
    void GetPage();     // List-Box mit Eintraegen versorgen

    short m_sBranchNo;
    CCSTBRANCHINFO m_Info;

    DECLARE_MESSAGE_MAP()
};


// CDCstBranchInfoDetails-Dialogfeld

class CDCstBranchInfoDetails : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCstBranchInfoDetails)

public:
    CDCstBranchInfoDetails(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDCstBranchInfoDetails();
    CDateTimeCtrl m_DT_ZeitBis;
    CDateTimeCtrl m_DT_DatumBis;
    CTime   m_CT_DatumBis;
    CTime   m_CT_ZeitBis;
    CEdit   m_Edit_InfoText;
    CString m_InfoText;
    long    m_lDateTo;
    long    m_lTimeTo;
    bool    m_bNew;

// Dialogfelddaten
    enum { IDD = IDD_AE_CST_BRANCH_INFO_DETAILS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditInfotext();
    virtual void OnOK();

    DECLARE_MESSAGE_MAP()

    long m_lActDate;
};

//---------------------------------------------------------------------------------------------------//
// include guard
//---------------------------------------------------------------------------------------------------//
#pragma once

//---------------------------------------------------------------------------------------------------//
// forward declaration
//---------------------------------------------------------------------------------------------------//
class CDAeSammelAuft;


//---------------------------------------------------------------------------------------------------//
// CDAeCollOrderGrp-Dialogfeld
//---------------------------------------------------------------------------------------------------//
class CDAeCollOrderGrp : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDAeCollOrderGrp)

public:
    static const int NUM_COLUMNS = 4;
    static COLUMNS_TYPES Columns[];

public:
    CDAeCollOrderGrp(CWnd* pParent = NULL);   // Standardkonstruktor

    virtual ~CDAeCollOrderGrp();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    // Dialogfelddaten
    enum { IDD = IDD_ADMIN_COLLGRP };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()

public:
    // members
    CDAeSammelAuft* m_pCDAeSammelAuft;
    CComboBox m_Combo_KundenGruppe;
    CEdit m_edNewCustGrp;
    CListCtrl m_lstNewCustomers;
    CImageList m_ImageSmall;
    int m_idx;

    // methods
    afx_msg void OnCbnEditchangeCboExistingCustgrps();
    afx_msg void OnEnChangeEdNewCustgrp();
    afx_msg void OnBnClickedBtSave();
    afx_msg void OnBnClickedBtDelete();
    afx_msg void OnBnClickedBtCancel();
    afx_msg void OnCbnSelchangeCboExistingCustgrps();
    afx_msg void OnBnClickedBtNewCustomer();
    afx_msg void OnBnClickedBtDeleteComplete();
    afx_msg void OnBnClickedBtNewload();
    virtual BOOL OnInitDialog();

private:
    // members
    //CString m_curCustGrp;

    // methods
    int existsGroup(const CString&);
    bool hasToBeSaved();
    void newLoad();
};

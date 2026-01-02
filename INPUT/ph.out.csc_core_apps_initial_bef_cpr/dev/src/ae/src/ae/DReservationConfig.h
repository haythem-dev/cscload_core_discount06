#pragma once

class CDOrderTypeManager4;

// CDReservationConfig dialog

class CDReservationConfig : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDReservationConfig)

public:
    CDReservationConfig(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDReservationConfig();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_RESERVATION_CONFIG };
#endif

    int m_iConfigID;
    CEdit m_edit_Bez;
    CString m_cBez;
    CString m_cAArt;
    CComboBox m_combo_ResTyp;
    CComboBox m_combo_Priority;
    CListCtrl m_ListCtl;
    CDOrderTypeManager4* m_pFather;
    BOOL m_bOnlyRes;
    BOOL m_bFreeFirst;
    short m_sMitEKG;
    short m_sPriority;
    int m_iReserveType;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnBnClickedCheckOnlyRes();
    afx_msg void OnBnClickedButtonPlus();
    afx_msg void OnBnClickedButtonMinus();
    afx_msg void OnEnChangeEditBez();
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnCbnSelchangeComboResTyp();
    DECLARE_MESSAGE_MAP()

    void LeseEKG();
};


// CDNewEKG dialog

class CDNewEKG : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDNewEKG)

public:
    CDNewEKG(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDNewEKG();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_NEW_EKG };
#endif

    CEdit m_edit_EKG;
    CListCtrl* m_pListCtl;
    CString m_cEKG;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnEnChangeEditEkg();
    DECLARE_MESSAGE_MAP()
};

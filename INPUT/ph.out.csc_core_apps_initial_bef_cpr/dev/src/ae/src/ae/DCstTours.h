#pragma once

class CTourListCtrl;
// CDCstTours dialog

class CTourData
{
public:

    CTourData() {};

    CString m_kb;
    CString m_tourid;
    CString m_auto;
    CString m_BTM;
    CString m_KK;
    CString m_K08;
    CString m_K20;

    bool m_check1;  //BTM
    bool m_check2;  //KK
    bool m_check3;  //K08
    bool m_check4;  //K20
};

class CDCstTours : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCstTours)

public:
    void UpdateList();
    CDCstTours(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDCstTours();

    vector<CTourData> m_data;

    enum { IDD = IDD_AE_DCSTTOURS };
    CTourListCtrl* m_List1;
    long m_lKndNr;
    short m_VzNr;
    long m_lActDate;
    int m_iUpdateKZ[100];
    CString m_cIDF;
    CString m_cName;
    CString m_cOrt;
    BOOL m_check1;
    BOOL m_check2;
    BOOL m_check3;
    BOOL m_noSel1;
    BOOL m_noSel2;
    BOOL m_noSel3;
    BOOL m_noCheckSel;
    BOOL m_bUpdated;
    BOOL m_bAnsicht;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    BOOL GetPage();         // List-Box mit Eintraegen versorgen
    void GetSpecials();     // Spezielle Einträge für den aktuellen Tag

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnListClick(WPARAM wParam, LPARAM lParam);
    afx_msg void OnButtonNewCst();
    afx_msg void OnButtonChange();
    afx_msg LRESULT OnGetListItem(WPARAM wParam, LPARAM lParam);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    virtual void OnCancel();
    DECLARE_MESSAGE_MAP()

public:
    bool AuswahlKunde();
};


// CDCstTourUpd dialog

class CDCstTourUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCstTourUpd)

public:
    CDCstTourUpd(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDCstTourUpd();

    enum { IDD = IDD_AE_DCSTTOURUPD };
    long m_lActDate;
    BOOL m_bBTM;
    BOOL m_bKK;
    BOOL m_bK08;
    BOOL m_bK20;
    BOOL m_bAktiv;
    BOOL m_bAuto;
    CString m_cVz;
    CString m_cKnd;
    CString m_cTour;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};

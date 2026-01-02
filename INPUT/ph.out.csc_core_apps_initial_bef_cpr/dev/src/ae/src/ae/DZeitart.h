#pragma once

// DZeitart.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDZeitart : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDZeitart(CWnd* pParent = NULL);   // standard constructor

    CEdit m_Edit_Zeitkey;
    CListCtrl m_ListCtl;
    CString m_CZeitkey;
    CStringArray m_Tagtab;
    CComboBox m_Combo_Zeitart;
    CString m_CZeitart;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    void SelectEintrag();
    void CloseCursor();                     // DB-Cursor schliessen
    int  m_Filiale;                         // eigene Filialnr
    short m_Vz;                             // eigenes Vertriebszentrum
    long m_Lfd;                             // Satznr

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDelete();
    afx_msg void OnChangeEditZeitkey();
    afx_msg void OnNeu();
    afx_msg void OnUpdate();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnCbnSelchangeComboZeitart();

    enum { IDD = IDD_AE_ZEITART };

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDUpdZeitart dialog

class CDUpdZeitart : public CDialogMultiLang
{
// Construction
public:
    CDUpdZeitart(CWnd* pParent = NULL);   // standard constructor

    CEdit m_EditZusatz;
    CEdit m_EditKey;
    CEdit m_EditEndss;
    CEdit m_EditEndmm;
    CEdit m_EditEndhh;
    CEdit m_EditAnfss;
    CEdit m_EditAnfmm;
    CEdit m_EditAnfhh;
    int m_iAnfhh;
    int m_iAnfmm;
    int m_iAnfss;
    int m_iEndhh;
    int m_iEndmm;
    int m_iEndss;
    CString m_CKey;
    CString m_CZusatz;
    CStringArray* m_pTagtab;
    int m_iTag;
    int m_iZeitart;
    CComboBox m_Combo_Zeitart;
    CString m_CZeitart;
    CComboBox m_Combo_Tag;
    CString m_CTag;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditAnfHh();
    afx_msg void OnChangeEditAnfMm();
    afx_msg void OnChangeEditAnfSs();
    afx_msg void OnChangeEditEndHh();
    afx_msg void OnChangeEditEndMm();
    afx_msg void OnChangeEditEndSs();
    virtual void OnOK();
    afx_msg void OnChangeEditKey();
    afx_msg void OnChangeEditZusatz();

    enum { IDD = IDD_AE_UPD_ZEITART };

    DECLARE_MESSAGE_MAP()
};

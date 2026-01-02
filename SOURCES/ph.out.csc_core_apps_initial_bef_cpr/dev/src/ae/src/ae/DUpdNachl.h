#pragma once
// DUpdNachl.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#include <nachlief.h>

class CDUpdNachl : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDUpdNachl(CWnd* pParent = NULL);   // standard constructor

    CButton m_CBHome;
    CButton m_CBNgf;
    CButton m_CBFolge;
    CButton m_CBBestell;
    CButton m_CBAh;
    CButton m_CBDatum;
    CEdit   m_EditPzn;
    CEdit   m_EditDatum;
    CEdit   m_EditIdf;
    CButton m_CBNachl;
    CButton m_CBDispo;
    CListCtrl m_ListCtl;
    BOOL    m_bDispo;
    BOOL    m_bNachl;
    CString m_CDatum;
    CString m_CIdf;
    CString m_CPzn;
    BOOL    m_bDatum;
    BOOL    m_bAh;
    BOOL    m_bBestell;
    BOOL    m_bFolge;
    BOOL    m_bNgf;
    long m_lIdfNr;
    long m_lKndNr;
    long m_lArtNr;
    CString m_AArt;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    void SelectEintrag();
    void CloseCursor();                     // DB-Cursor schliessen
    BOOL m_bDeleted;                        // Satz wurde geloescht
    short m_SelKz;                          // Selectkriterien
    CNACHLIEF m_nachl;
    CButton m_CBQuota;
    BOOL m_bQuota;
    CComboBox m_Cobox_Auf;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonKnd();
    afx_msg void OnCheckDispo();
    afx_msg void OnCheckNachl();
    afx_msg void OnChangeEditDatum();
    afx_msg void OnChangeEditIdf();
    afx_msg void OnButtonArtikel();
    afx_msg void OnButtonDruck();
    afx_msg void OnCheckAh();
    afx_msg void OnCheckBestell();
    afx_msg void OnCheckFolge();
    afx_msg void OnButtonDruckList();
    afx_msg void OnButtonDruckVb();
    afx_msg void OnCheckNgf();
    afx_msg void OnCheckVz2();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedButtonDruckLief();
    afx_msg void OnBnClickedCheckQuota();
    afx_msg void OnCbnSelchangeComboAufart();

    enum { IDD = IDD_AE_UPD_NACHL };

    DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CDNachlAen dialog

class CDNachlAen : public CDialogMultiLang
{
// Construction
public:
    CDNachlAen(CWnd* pParent = NULL);   // standard constructor

    CButton m_CBFolge;
    CButton m_CBCancel;
    CButton m_CBDel;
    CButton m_CBUpd;
    CEdit   m_EditMenge;
    CString m_CMenge;
    CString m_CAuftrNr;
    CString m_CIdfNr;
    CString m_CPZN;
    CString m_CTyp;
    CString m_CFolge;
    CString m_CFMenge;
    long m_Posnr;
    long m_Datum;
    long m_lMengeAlt;
    long m_lFolgeNr;
    BOOL m_bUpdated;
    BOOL m_bDeleted;
    BOOL m_bFolge;
    short m_VzNr;
    CString m_AArt;
    CString m_CArtCode;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnButtonDel();
    afx_msg void OnButtonUpd();
    afx_msg void OnChangeEditMenge();
    virtual void OnCancel();
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonFolge();

    enum { IDD = IDD_AE_NACHL_AEN };

    DECLARE_MESSAGE_MAP()

private:
    void InsertNachliefProt(short sAendTyp);
};

/////////////////////////////////////////////////////////////////////////////
// CNachlDruck dialog

class CNachlDruck : public CDialogMultiLang
{
// Construction
public:
    CNachlDruck(CWnd* pParent = NULL);   // standard constructor

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK();
    virtual BOOL OnInitDialog();

    enum { IDD = IDD_AE_DRUCK_NACHL };

    DECLARE_MESSAGE_MAP()
};

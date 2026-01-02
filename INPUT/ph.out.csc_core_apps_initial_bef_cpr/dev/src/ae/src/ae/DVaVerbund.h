#pragma once


// CDVaVerbund-Dialogfeld

class CDVaVerbund : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDVaVerbund)

public:
    CDVaVerbund(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDVaVerbund();

    enum { IDD = IDD_AE_VA_VERBUND };
    CEdit m_edit_KundenNr;
    CString m_CKundenNr;
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    afx_msg void OnEnChangeEditKundennr();
    afx_msg void OnBnClickedButtonKunde();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonUpdate();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnHdnItemdblclickList1(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

private:
    long m_lKunde;
    CString m_CMC;
    CSHIPAUXNO m_ShipAux;

    void GetPage();     // List-Box mit Eintraegen versorgen
};


// CDVaVerbundUpd-Dialogfeld

class CDVaVerbundUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDVaVerbundUpd)

public:
    CDVaVerbundUpd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDVaVerbundUpd();

    int m_iFunktion;
    CString m_CBGA;
    CStringArray m_Filialen;
    CString m_csFiliale;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    void CloseCursor();         // DB-Cursor schliessen
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangeEditBga();
    afx_msg void OnCbnSelchangeComboFiliale();

    enum { IDD = IDD_AE_VA_UPDATE };

    DECLARE_MESSAGE_MAP()

private:
    bool m_bErsterSatz;         // Kennzeichen erster Satz
    bool m_bCursorOpen;         // Datenbankcursor geoeffnet

    CComboBox m_combo_Filiale;
    CEdit m_edit_BGA;
};

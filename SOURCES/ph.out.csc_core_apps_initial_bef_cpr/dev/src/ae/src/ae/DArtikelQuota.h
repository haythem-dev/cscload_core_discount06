#pragma once

#include <atltime.h>

// CDArtikelQuota-Dialogfeld

class CDArtikelQuota : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDArtikelQuota)

public:
    CDArtikelQuota(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDArtikelQuota();

// Dialogfelddaten
    enum { IDD = IDD_AE_ARTIKELQUOTA };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonUpdate();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnBnClickedButtonKnd();
    afx_msg void OnBnClickedButtonArt();
    afx_msg void OnEnChangeEditKunde();
    afx_msg void OnEnChangeEditArtkelnr();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedButtonDelAllKnd();
    afx_msg void OnBnClickedButtonDelAllArt();
    afx_msg void OnBnClickedButtonCopy();
    afx_msg void OnEnChangeEditKunde2();
    afx_msg void OnBnClickedButtonCopy2();
    afx_msg void OnBnClickedButtonDruck();
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedButtonAllNobatch();
    afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);

    void GetPage();     // List-Box mit Eintraegen versorgen

    CString m_cArtikel;
    CString m_cKunde;
    CString m_cMenge;
    CListCtrl m_ListCtl;
    CEdit m_edit_Kunde;
    CEdit m_edit_Artikel;
    CEdit m_edit_Menge;
    CARTIKELQUOTA m_ArtikelQuota;
    CARTICLEQUOTAEKG m_QuotaEKG;
    CString m_cEKG;
    int m_lKndNr;
    int m_lArtNr;
    bool m_bDafue;
    bool m_bEKG;
    CComboBox m_combo_Zeit;
    CString m_cZeit;
    CEdit m_edit_Kunde2;
    CString m_CKunde2;
    CButton m_CB_NoBatch;
    BOOL m_bNoBatch;

private:
    long m_lKunde;
    long m_lKunde2;
    long m_lArtikel;
    CString m_CMC;
    CString m_CArt;

private:
    static CString GetHeaderLineTitlesEKG();
    static CString GetHeaderLineTitles();
    static CString GetBottomLine(CString date);

    static CString GetTimeRangeHeader(char validity);

    CString GetPositionLine(int pos);
    void SetValidity(int timeRange);
};


// CDArtikelQuotaUpd-Dialogfeld

class CDArtikelQuotaUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDArtikelQuotaUpd)

public:
    CDArtikelQuotaUpd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDArtikelQuotaUpd();

// Dialogfelddaten
    enum { IDD = IDD_AE_ARTIKELQUOTA_UPD };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()
public:
    long m_lDatumvon;
    long m_lDatumbis;
    bool m_bUpdate;
    bool m_bEKG;
    int m_iZeitraum;
    CString m_CKunde;
    CString m_CArtikel;
    CString m_CMenge;
    CComboBox m_combo_Zeit;
    CString m_CZeit;
    CDateTimeCtrl m_DT_Von;
    CTime m_CT_Von;
    CDateTimeCtrl m_DT_Bis;
    CTime m_CT_Bis;
    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangeEditKunde();
    afx_msg void OnEnChangeEditArtkelnr();
    afx_msg void OnBnClickedButtonKnd();
    afx_msg void OnBnClickedButtonArt();
    afx_msg void OnBnClickedOk();
    CEdit m_edit_artikelnr;

private:
    long m_lKunde;
    long m_lArtikel;
    CString m_CMC;
    CString m_CArt;

public:
    CEdit m_edit_Kunde;
    CEdit m_edit_Menge;
    BOOL m_bNoBatch;
};

#pragma once

#include <atlcomtime.h>
#include <atltime.h>


// CDQuotaKlasse-Dialogfeld

class CDQuotaKlasse : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDQuotaKlasse)

public:
    CDQuotaKlasse(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDQuotaKlasse();

// Dialogfelddaten
    enum { IDD = IDD_AE_QUOTA_KLASSE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()

public:
    int m_iFunktion;    // 0 = nach kundenklasse      1 = nach EKG
    CEdit m_edit_Artikelnr;
    CString m_cArtikelnr;
    CEdit m_edit_Klasse;
    CString m_cKlasse;
    CEdit m_edit_Menge;
    CString m_cMenge;
    afx_msg void OnBnClickedButtonArtnr();
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangeEditArtnr();
    afx_msg void OnEnChangeEditKlasse();
    afx_msg void OnEnChangeEditMenge();
    CARTIKELQUOTAPF m_Quota;
    CString m_cZeit;
    CComboBox m_combo_Zeit;
    afx_msg void OnBnClickedButtonUpd();
    short m_sFunktion;
    void UpdateInsert();
    afx_msg void OnBnClickedRadio1();
    bool m_bDafue;
    CDateTimeCtrl m_CT_Von;
    CDateTimeCtrl m_CT_Bis;
    CTime m_DT_Von;
    CTime m_DT_Bis;

private:
    long m_lKunde;
    long m_lArtikel;
    CString m_CMC;
    CString m_CArt;

public:
    BOOL m_bNoBatch;
    afx_msg void OnBnClickedButtonDel();
};

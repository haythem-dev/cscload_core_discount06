#pragma once


// CDSammelAufDef-Dialogfeld

class CDSammelAufDef : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDSammelAufDef)

public:
    CDSammelAufDef(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDSammelAufDef();

// Dialogfelddaten
    enum { IDD = IDD_AE_SAMMEL_AUF_DEF };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()

public:
    CComboBox m_Combo_AArt;
    virtual BOOL OnInitDialog();
    CEdit m_edit_Bemerkung;
    CString m_CBemerkung;
    afx_msg void OnEnChangeEditBemerkung();
    CSpinButtonCtrl m_CSpinValuta;
    afx_msg void OnBnClickedOk();
    CString m_CKoArt;
    CString m_CBuArt;
    CString m_CAufArt;
    long m_lValuta;
    long m_lActDatum;
    CString m_CValuta;
    afx_msg void OnBnClickedCheckValuta();
    CEdit m_edit_Valuta;
    afx_msg void OnEnChangeEditValMon2();
    void SetValutaDatum();

private:
    bool ValutaInDays();
    CString GetBookingType();
    CString GetKommiType();
};

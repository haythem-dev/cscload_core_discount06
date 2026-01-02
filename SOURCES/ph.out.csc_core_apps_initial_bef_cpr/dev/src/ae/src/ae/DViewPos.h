#pragma once


// CDViewPos-Dialogfeld

class CDViewPos : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDViewPos)

public:
    CDViewPos(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDViewPos();

    enum { IDD = IDD_AE_VIEW_POS };
    CListCtrl m_List1;
    CEdit m_Edit_PZN;
    CEdit m_Edit_ARTIKELNAME;
    CEdit m_Edit_MENGE;
    CEdit m_Edit_AEP;
    CEdit m_Edit_AVP;
    CEdit m_Edit_RABATT;
    CEdit m_Edit_BESTAND;
    CEdit m_Edit_PREIS_RAB;
    CEdit m_Edit_WERT_POS;
    CEdit m_Edit_SPANNE;
    CComboBox m_ComboTyp;
    CString m_csPZN;
    CString m_csARTIKELNAME;
    CString m_csMENGE;
    CString m_csAEP;
    CString m_csAVP;
    CString m_csOpi;
    CString m_csKKCode;
    CString m_csEinzelhandel;
    CString m_csBestand;
    CString m_csRabPreis;
    CString m_csWertPos;
    CString m_csRabatt;
    CString m_CBTMLicense;
    CString m_cAArt;
    CString m_csTaxlevel;
    CString m_csSpanne;
    long m_lDatumBTM;
    CString m_csCharge;
    BOOL    m_bIgnore;
    CEdit m_Edit_Natra;
    CString m_csNatra;

    short m_sPreistyp;

protected:
    CString m_csSaveRabatt;

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    afx_msg void OnCbnSelchangeComboTyp();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnButtonCalc();
    afx_msg void OnButtonBuchen();

    DECLARE_MESSAGE_MAP()

private:
    void GetBTMLicense();
    bool ValidateRebateInput();
    void UpdateRebateFromCstDiscount();
};

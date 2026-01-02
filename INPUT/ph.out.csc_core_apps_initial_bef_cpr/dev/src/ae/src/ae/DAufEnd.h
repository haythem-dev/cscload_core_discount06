#pragma once
// daufend.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAufEnd dialog

#include <atltime.h>

class CDAufEnd : public CDialogMultiLang
{
// Construction
public:
    CDAufEnd(CWnd* pParent = NULL);     // standard constructor
    CAeDoc *ptrDoc;                     // Zeiger auf das Dokument
    int GetStatus() { return m_Status; } // gibt Status zurueck
    bool m_bKeinAuftrag;                // Schalter zum ermöglichen der Aktion kein Auftrag
    bool m_bStdDafueZur;                // Schalter Standard auf Dafue-Zurueckstellen
    CString m_AArt;                     // Auftragsart
    CString m_SubType;                  // Sub-Auftragsart
    CString m_BuchArt;                  // Buchungsart
    CString m_KommArt;                  // Kommiart
    CString m_cZuGrund;                 // Rückstellgründe
    CString m_Tour;                     // eingestellte Tour
    long    m_IdfNr;                    // Idf-Nr des aktuellen Kunden
    long    m_KndNr;                    // Kunden-Nr des aktuellen Kunden
    short   m_VzNr;                     // Vz-Nr des aktuellen Kunden
    long    m_lDatumDD;                 // Datum verzögerte Auslieferung
    long    m_lActDatum;                // akuelles Datum für verzögerte Auslieferung
    short   m_sWeekday;                 // aktueller Wochentag
    CStringArray m_Tagtab;
    bool    m_bSonder;
    bool    m_bMixExist;
    bool    m_bMixShown;
    bool    m_bAnzSonder;
    int     m_iCombo;
    bool    m_bMitRab;                  // Kunde hat Rabattkonto
    long    m_lAufnr;                   // Aktueller Auftrag
    int     m_bNoDD;                    // Auftrag mit oder ohne DD

    enum { IDD = IDD_AE_AUFTR_ENDE };
    CButton m_CBPrint;
    CComboBox m_CoboxTour;
    CEdit   m_EditBemerkung;
    CStatic m_StaticMin;
    CEdit   m_EditMin;
    CSpinButtonCtrl m_CSpinMin;
    CString m_CBemerkung;
    CDateTimeCtrl m_DT_DD;
    CTime m_CT_DD;
    CButton m_CB_DD_Ohne;
    BOOL m_bDDOhne;
    CComboBox m_CoboxFutur;
    CComboBox m_CoboxNakt;
    CStatic m_cs_Sonder;
    CComboBox m_CoboxMix;
    BOOL m_bNoRabattKonto;
    BOOL m_bSaveNoRabattKonto;
    CComboBox m_combo_price_fv;
    CComboBox m_combo_price_kk;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void ShowAkt();
    void ShowSonder();
    void ShowFutur();
    void ShowMix();
    void InsTouren();
    void HoleWochenTouren();
    void LadeWochenTouren(short sWeekday);
    void SetTour();
    void SetTourFutur();
    void SetKommArt(char cKommArt);
    void CheckTourDD();
    void TourToString(CString &Tour, CString &STour, long Fahrzeit, char cKA, short sWeekday);
    void StringToTour(char *tour, CString &STour);
    int m_Status;
    bool m_bManuell;
    CStringArray m_aWochentouren;       // Wochentouren

    virtual BOOL OnInitDialog();
    afx_msg void OnCheckNewCall();
    virtual void OnOK();
    afx_msg void OnChangeEditBemerkung();
    afx_msg void OnRadioTour();
    afx_msg void OnRadioSchl();
    afx_msg void OnRadio12();
    afx_msg void OnSelchangeComboTour();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    afx_msg void OnCheckColFV();
    afx_msg void OnCheckAEPFV();
    afx_msg void OnCheckAVPFV();
    afx_msg void OnCheckColKK();
    afx_msg void OnCheckAEPKK();
    afx_msg void OnCheckAVPKK();
    afx_msg void OnCbnSelchangeComboNakt();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnDtnDatetimechangeDatetimepickerDd(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnCbnSelchangeComboMix();
    afx_msg void OnBnClickedButtonSonder();
    afx_msg void OnBnClickedButtonRechwert();
    afx_msg void OnCbnSelchangeComboPriceFv();
    afx_msg void OnCbnSelchangeComboPriceKk();
    DECLARE_MESSAGE_MAP()

// Data
protected:
    short m_snrcol_fv;
    short m_srabaep_fv;
    short m_srabavp_fv;
    short m_sprice_fv;
    short m_smail_fv;
    short m_snrcol_kk;
    short m_srabaep_kk;
    short m_srabavp_kk;
    short m_sprice_kk;
    short m_smail_kk;
    CButton m_CB_nrcol_fv;
    CButton m_CB_rabaep_fv;
    CButton m_CB_rabavp_fv;
    CButton m_CB_mail_fv;
    CButton m_CB_nrcol_kk;
    CButton m_CB_rabaep_kk;
    CButton m_CB_rabavp_kk;
    CButton m_CB_mail_kk;
};

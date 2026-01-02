#pragma once


// CDChangeTour dialog

class CDChangeTour : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDChangeTour)

public:
    CDChangeTour(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDChangeTour();
    CAUFTRAG* m_pAuftrag;
    enum { IDD = IDD_AE_CHANGE_TOUR };

    // Dialog Data
    CComboBox   m_CoboxTour;
    CComboBox   m_CoboxNakt;
    CComboBox   m_CoboxFutur;
    CComboBox   m_CoboxMix;
    BOOL        m_bDD;
    CDateTimeCtrl m_DT_DD;
    CTime       m_CT_DD;
    CStatic     m_cs_SonderTour;
    CStringArray m_Tagtab;
    long        m_lDatumDD;                 // Datum verzögerte Auslieferung
    long        m_lDatum;                   // aktuelles Datum
    long        m_lActDatum;                // akuelles Datum für verzögerte Auslieferung
    short       m_sWeekday;                 // aktueller Wochentag
    CString     m_saveTour;                 // voreingestellte Tour
    CString     m_AArt;                     // Auftragsart
    bool        m_bSonder;
    bool        m_bMixExist;
    bool        m_bMixShown;
    bool        m_bAnzSonder;
    CStringArray m_aWochentouren;           // Wochentouren
    int         m_iCombo;                   // Kennzeichen, welche Touren angezeigt werden
    CString     m_Tour;                     // eingestellte Tour
    char        m_cKA[1];                   // neue KommiArt

protected:
    void ShowAkt();
    void ShowSonder();
    void ShowFutur();
    void ShowMix();

    void InsTouren(CString& AArt);
    void VersorgeTouren(CString& AArt);
    void HoleWochenTouren(CString& AArt);
    void LadeWochenTouren(short sWeekday);
    void SetTour();
    void SetTourFutur();
    void SetValuta(int mon);
    void TourToString(CString& Tour, CString& STour, long Fahrzeit, char KA, short sWeekday);   // Tour ins Ausgabeformat umwandeln
    void StringToTour(char* str, CString& STour);       // Ausgabeformat in Tour umwandeln

    // Generated message map functions
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnSelchangeComboTour();
    afx_msg void OnCbnSelchangeComboTourNakt();
    afx_msg void OnBnClickedCheckDd();
    afx_msg void OnDtnDatetimechangeDatetimepickerDd(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedButtonSonder();
    afx_msg void OnCbnSelchangeComboMix();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    DECLARE_MESSAGE_MAP()
};

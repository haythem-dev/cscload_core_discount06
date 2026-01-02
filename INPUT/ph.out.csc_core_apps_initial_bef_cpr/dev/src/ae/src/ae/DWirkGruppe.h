#pragma once


// CDWirkGruppe-Dialogfeld

class CDWirkGruppe : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDWirkGruppe)

public:
    CDWirkGruppe(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDWirkGruppe();

    enum { IDD = IDD_AE_WIRK_GRUPPE };
    CListCtrl m_List1;
    CImageList m_ImageSmall;
    int m_ifunktion;
    long m_lArtikelNr;
    long m_lKndNr;
    short m_sVzNr;
    CString m_CMenge;
    CEdit m_EditMenge;
    CComboBox m_ComboTyp;
    CLetterMan m_kb;
    CStringArray s;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditMenge();
    afx_msg void OnCbnSelchangeComboTyp();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    BOOL Fillist();

    DECLARE_MESSAGE_MAP()

//  lokale Daten
    CARTICLEAGENTGROUP m_group;
//  Angebotsliste
    struct Angebote
    {
        long ArtikelNr;
        double dPct;
    };

    vector<Angebote> m_pl; // pointer to class list
    vector <Angebote>::iterator m_it;
};

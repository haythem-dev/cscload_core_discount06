#pragma once
// dkndwahl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDKndWahl dialog

class CDKndWahl : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    CDKndWahl(CWnd* pParent = NULL);    // standard constructor

    BOOL IsAktiv() { return m_bAktiv; }     // Liefert ob Kunde bei Tag-Nachthaus aktiv ist
    long GetKndNr() { return m_KndNr; }     // Liefert Kundennummer (-1 ungueltige Nummer)
    long GetIdfNr() { return m_IdfNr; }     // Liefert IDF-nummer (-1 ungueltige Nummer)
    BOOL GetKzAeGesperrt() { return m_KzAeGesperrt; }                   // Liefert KzAeGeperrt
    const short GetKndFiliale() const { return m_KndFiliale; }          //Nr. der Filiale des Kunden
    const short GetKndOrgFiliale() const { return m_KndOrgFiliale; }    //Nr. der Filiale des Kunden
    const short GetKndVz() const { return m_KndVz; }                    //Nr. des VZ des Kunden
    void SetHeader(const ppString& strHeader) { m_strHeader = strHeader; }
    void SetKndVz(const short sVz) { m_KndVz = sVz; }
    void SetEnableAeGesperrt(const BOOL bActivateAeGesperrt = FALSE) { m_EnableAeGesperrt = 1; m_bActivateAeGesperrt = bActivateAeGesperrt; }
    void SetDeActivateKundeHome(const BOOL bDeActivateKundeHome = FALSE) { m_IsKundeHome = true; m_bDeActivateKundeHome = bDeActivateKundeHome; }
    void SetDisableAeGesperrt() { m_EnableAeGesperrt = 0; }

public:
    CImageList m_ImageSmall;

    enum { IDD = IDD_AE_KD_WAHL };
    CButton m_CBGesperrt;
    CButton m_CBHome;
    CEdit   m_cOrt;
    CEdit   m_cMatchCode;
    CEdit   m_cInhaber;
    CEdit   m_cKndNr;
    CListCtrl m_ListCtl;
    CString m_apo;
    CString m_inhaber;
    CString m_ort;
    CString m_CKndNr;
    CEdit m_EditName;
    CString m_CName;
    CString m_CApotheke;
    CString m_COrt;

protected:
    CToolTipCtrl m_tooltip;

    void SetOnAeGesperrt() { m_AeGesperrt[0] = '1'; }
    void SetOffAeGesperrt() { m_AeGesperrt[0] = '0'; }

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    void CloseCursor();                     // DB-Cursor schliessen
    void OnInfKunde( );                     // Kundeinformationen
    int  SelectKunde();                     // Ermittlung der markierten IDF-nummer
    void DropListSelect();                  // Selektion in Listbox aufheben
    int  m_nFunktion;                       // Funktion, mit der selektiert wird
    long m_IdfNr;                           // Ergebnis der Selektion (-1 ungueltige Nr.)
    long m_KndNr;                           // Ergebnis der Selektion (-1 ungueltige Nr.)
    short m_KndFiliale;                     // Filiale des Kunden
    short m_KndOrgFiliale;                  // Original-Filiale des Kunden
    short m_KndVz;                          // VZ des Kunden
    char m_AeGesperrt[1];                   // Kundekennzeichen ae gesperrt
    BOOL m_EnableAeGesperrt;                // Anzeige auch gesp.. enablen
    BOOL m_bActivateAeGesperrt;             // Setzt den Checkbutton von gesp. Kunden
    BOOL m_KzAeGesperrt;                    // Kz Kunde Ae gesperrt
    ppString m_strHeader;
    bool m_IsKundeHome;
    BOOL m_bAktiv;                          // Kz Kunde Ae gesperrt
    BOOL m_bDeActivateKundeHome;            // Setzt den Checkbutton von gesp. Kunden

    // Generated message map functions
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnDestroy();
    afx_msg void OnChangeEditApotheke();
    afx_msg void OnChangeEditInhaber();
    afx_msg void OnChangeEditKdNr();
    afx_msg void OnChangeEditOrt();
    afx_msg void OnKeydownListctrlKunde(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkListctrlKunde(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRclickListctrlKunde(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnCheckHome();
    afx_msg void OnCheckGesperrt();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnEnChangeEditName();
    DECLARE_MESSAGE_MAP()
};

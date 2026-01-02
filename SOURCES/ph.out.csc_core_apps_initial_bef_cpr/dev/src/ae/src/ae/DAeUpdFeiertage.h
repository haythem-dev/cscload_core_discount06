#pragma once

// DAeUpdFeiertage.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDAeUpdFeiertage

class CDAeUpdFeiertage : public CDialogMultiLang
{
// Konstruktion
public:
    CDAeUpdFeiertage(CWnd* pParent = NULL);   // Standardkonstruktor
    short m_sModus;
    short m_sVzNr;
    short m_sDatum;

// Dialogfelddaten
    enum { IDD = IDD_AE_UPD_FEIERTAG };
    CComboBox m_Combo_Modus;
    CEdit   m_edit_Name;
    CEdit   m_edit_VonJahr;
    CEdit   m_edit_BisJahr;
    CTime   m_Datum;
    CString m_csBisJahr;
    CString m_csVonJahr;
    CString m_csName;

// Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:
    //members
    CTime m_Ostern;
    CTM m_zeit;

    //methodes

    // Generierte Nachrichtenzuordnungsfunktionen
    virtual void OnOK();
    afx_msg void OnChangeEditVonJahr();
    afx_msg void OnChangeEditBisJahr();
    afx_msg void OnChangeEditName();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

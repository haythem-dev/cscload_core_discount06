#pragma once

// DAeAnzFeiertage.h : Header-Datei
//
#include <statistics.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDAeAnzFeiertage

class CDAeAnzFeiertage : public CDialogMultiLang
{
// Konstruktion
public:
    CDAeAnzFeiertage(CWnd* pParent = NULL);   // Standardkonstruktor
    void SetVzNr(const short sVzNr) { m_sVzNr = sVzNr; }
    short GetVzNr()                 { return m_sVzNr; }

// Dialogfelddaten
    enum { IDD = IDD_AE_ANZ_FEIETAG };
    CListCtrl m_ListCtl;


// Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    //methodes

// Implementierung
protected:
    // Generierte Nachrichtenzuordnungsfunktionen
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonDruck();
    afx_msg void OnButtonDelete();
    afx_msg void OnButtonInsert();
    afx_msg void OnButtonUpdate();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

    //members
    short m_sVzNr;
    CFEIERTAG m_Feiertag;
    CTime m_Ostern;
    long m_iYear;

    //methodes
    void GetPage();
};

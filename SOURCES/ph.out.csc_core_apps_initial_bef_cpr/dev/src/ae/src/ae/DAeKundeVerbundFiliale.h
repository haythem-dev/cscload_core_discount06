#pragma once

// DAeKundeVerbundFiliale.h : Header-Datei
//
#include <customer.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDAeKundeVerbundFiliale

class CDAeKundeVerbundFiliale : public CDialogMultiLang
{
// Konstruktion
public:
    CDAeKundeVerbundFiliale(CWnd* pParent = NULL);   // Standardkonstruktor
    void SetVzNr(const short sVzNr) { m_sSaleCenterNo = sVzNr; }
    short GetVzNr()                 { return m_sSaleCenterNo; }
    void SetKundenNr(const long lKundenNr) { m_lCustomerNo = lKundenNr; }
    long GetKundenNr()              { return m_lCustomerNo; }

// Dialogfelddaten
    enum { IDD = IDD_AE_KUNDE_VERBUNDFILIALE };
    CListCtrl m_ListCtl;


// Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonChange();
    afx_msg void OnButtonUpdate();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnOK();
    afx_msg void OnButtonDelete();
    afx_msg void OnButtonInsert();
    DECLARE_MESSAGE_MAP()

    //members
    long m_lCustomerNo;
    short m_sSaleCenterNo;
    CKUNDEVERBUNDFILIALE m_DkVbFil;

    //methodes
    void SetHeader();
    void GetPage();
    bool SelKunde();
};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDAeKundeVerbundFilialeUpd

class CDAeKundeVerbundFilialeUpd : public CDialogMultiLang
{
// Konstruktion
public:
    CDAeKundeVerbundFilialeUpd(CWnd* pParent = NULL);   // Standardkonstruktor
    void SetFunktion(const short sFunktion) { m_sFunktion = sFunktion; }
    short GetFunktion()                     { return m_sFunktion; }
    void SetKundenNr(const long lKundenNr)  { m_lCustomerNo = lKundenNr; }
    long GetKundenNr()                      { return m_lCustomerNo; }
    void SetVbFiliale(const short sVbFiliale) { m_sVbFiliale = sVbFiliale; }
    short GetVbFiliale()                    { return m_sVbFiliale; }
    void SetFolge(const short sFolge) { m_sFolge = sFolge; }
    short GetFolge()                        { return m_sFolge; }

    enum { IDD = IDD_AE_KUNDE_VERBUNDFILIALE_UPD };
    CEdit m_edit_VbFiliale;
    CEdit m_edit_KdNr;
    CEdit m_edit_Folge;
    CString m_cStaticKunde;
    CString m_cHeader;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditFolge();
    afx_msg void OnChangeEditKdnr();
    afx_msg void OnChangeEditVbFiliale();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()

    //members
    long m_lCustomerNo;
    short m_sFunktion;
    short m_sFolge;
    short m_sVbFiliale;
};

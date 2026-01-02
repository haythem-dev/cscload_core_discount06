#pragma once

// DArtikelkonto.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDArtikelkonto

class CDArtikelkonto : public CDialogMultiLang
{
// Konstruktion
public:
    CDArtikelkonto(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
    enum { IDD = IDD_AE_ARTIKELKONTO };
    CEdit m_Edit_IdfNr;
    CListCtrl m_ListCtl;
    CDateTimeCtrl m_DT_ZeitVon;
    CDateTimeCtrl m_DT_ZeitBis;
    CDateTimeCtrl m_DT_DatumVon;
    CDateTimeCtrl m_DT_DatumBis;
    CEdit m_Edit_Filiale;
    CEdit m_Edit_ArtikelNr;
    CString m_CArtikelNr;
    CString m_CFiliale;
    CTime m_CT_DatumBis;
    CTime m_CT_DatumVon;
    CTime m_CT_ZeitBis;
    CTime m_CT_ZeitVon;
    CString m_CIdfNr;


// Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditArtikelNr();
    afx_msg void OnChangeEditFiliale();
    virtual void OnOK();
    afx_msg void OnDruck();
    afx_msg void OnChangeEditIdfNr();
    afx_msg void OnButtonArtikel();
    afx_msg void OnButtonKunde();
    afx_msg void OnButtonAufAnz();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
    void RepositionWindow();

    DECLARE_MESSAGE_MAP()

// Data
protected:
    long m_lActDate;

private:
    static CString GetHeaderLineTitlesBG();
    static CString GetHeaderLineTitles();
    static CString GetBottomLine(CString date);

    long GetDateFromItem(int pos);

    CString GetPositionLineBG(int pos);
    CString GetPositionLine(int pos);
};

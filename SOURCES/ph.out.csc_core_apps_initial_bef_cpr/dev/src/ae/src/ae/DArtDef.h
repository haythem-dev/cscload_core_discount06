#pragma once
// dartdef.h : header file
//
#include <artikel.h>
#include <artsel.h>

/////////////////////////////////////////////////////////////////////////////
// CDArtDef dialog

class CDArtDef : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDArtDef(CWnd* pParent = NULL); // standard constructor
    long GetArtNr() { return m_ArtikelNr; }
    CString GetArtName() { return m_ArtikelName; }
    CString GetArticleCode() { return m_cArticleCode; }
    BOOL m_bAufnahme;               //aus eröffnetem Auftrag
// Dialog Data
    enum { IDD = IDD_AE_ART_DEF };
    CEdit m_EditHerstnr;
    CEdit m_EditNormpackung;
    CEdit m_EditZusatz;
    CEdit m_EditArtNr;
    CEdit m_EditMatchCode;
    CEdit m_EditPackGr;
    CEdit m_EditDarr;
    CListCtrl m_ListCtl;
    CString m_CDarr;
    CString m_CPackGr;
    CString m_CMatchCode;
    CString m_CArtNr;
    CString m_CZusatz;
    CString m_CNormpackung;
    CString m_CHerstnr;
    short   m_sImport;
    CImageList m_ImageSmall;

// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
private:
    long m_ArtikelNr;
    long m_HerstNr;
    CString m_cArticleCode;
    CARTINFBG m_infbg;
    CString m_ArtikelName;
    CLetterMan m_kb;

protected:
    // Generated message map functions
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditDarr();
    afx_msg void OnChangeEditEinheit();
    afx_msg void OnChangeEditName();
    afx_msg void OnChangeEditPzn();
    afx_msg void OnChangeEditZusatz();
    afx_msg void OnKeydownListctrlArt(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDestroy();
    afx_msg void OnChangeEditNormpackung();
    afx_msg void OnChangeEditHerstnr();
    afx_msg void OnButtonCopy();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()

    virtual bool GetPage(const int nKzUpDown = NEXT_PG); // List-Box mit Eintraegen versorgen
    void CloseCursor();                         // DB-Cursor schliessen
    long SelListPos();                          // ArtikelNr des ausgewählten Art. best.
    long WaehleListPos();                       // Ermittlung der markierten Artikelnummer
    void SelectArtikelNr(CString ArtNr);        // Kontrolle gültige Artikelnummer
    void SelectHerstnr(CString Herstnr);        // Kontrolle gültige Hersteller-Artikelnummer
    void SelectHerstname(CString Herstname);    // Kontrolle gültige Hersteller-Name
    void PosBuchen();                           // Buchung einer Position
    void ClearView();                           // Löschen der Feldinhalte und Listbox
    void ClearInput();                          // Löschen der Eingabefelder
    void DropListSelect();                      // Selektion in Listbox aufheben
    int  m_nFunktion;                           // Funktion, mit der selektiert wird
    BOOL FillList(CARTSEL artsel);              // List-Box füllen

public:
    CButton m_CBNurAktF11;
    afx_msg void OnBnClickedCheck3();
    CEdit m_EditHerstName;
    CString m_CHerstname;
    afx_msg void OnEnChangeEditHerstname();
    afx_msg void OnBnClickedRadioImport();
};

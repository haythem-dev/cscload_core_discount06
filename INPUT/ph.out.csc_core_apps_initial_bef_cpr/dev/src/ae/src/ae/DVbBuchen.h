// DVbBuchen.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
using namespace std;

class CDVbBuchen : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDVbBuchen(CWnd* pParent = NULL);   // standard constructor
    CImageList m_ImageSmall;
    long m_lKndNr;
    long m_IdfNr;
    long m_TenderNo;
    short m_VzNr;
    long m_lFilialNr;
    long m_lAuftrNr;
    bool m_bVersorgt;
    bool m_bNoCO;
    CString m_cAufArt;
    int  m_ifunktion;   // 0 = Verbund buchen
                        // 1 = Defekte buchen
    bool m_bKndMussKopfBem;     // Auftragskopfbemerkung erzwingen
    bool m_bGiveProdQuota;      // darf Herstellerkontingent beziehen
    struct VbArtikel
    {
        CString MengeBestellt;
        CString BestMenge;
        CString NatraMenge;
        CString VerbMenge;
        CString ArtEinh;
        CString ArtName;
        CString ArtNr;
        CString VerbFiliale;
        CString Darreichform;
        CString Bemerkung;
        CString Kennzeichen;
        CString LagerBereich;
        CString Preistyp;
        CString Prodquota;
        CString PreisFree;
        CString PctMan;
    };

    vector<VbArtikel> m_pl; // pointer to class list
    vector <VbArtikel>::iterator m_it;

    CStatic m_CStaticListe;
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);    // List-Box mit Eintraegen versorgen
    void SelectEintrag();
    void SetMarked(int pos); //Markieren Artikel für Buchung
    void DelMarked(int pos); //Entfernen Markierung
    void Buchen(int pos);    //Markierte Artikel im Verbund buchen

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnOK();
    afx_msg void OnButtonMark();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );

    enum { IDD = IDD_AE_VB_BUCHEN };

    DECLARE_MESSAGE_MAP()
};

#pragma once

// AeKndNachl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAeKndNachl dialog

class CAeKndNachl : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CAeKndNachl(CWnd* pParent = NULL);      // standard constructor
    CAeDoc* ptrDoc;                         // Zeiger auf das Dokument
    CAeFView* ptrFView;                     // Zeiger auf den View
    CImageList m_ImageSmall;
    CString m_VerbundZeitenKnd;             // Infofeld Verbundzeiten des Kunden
    long m_lKndNr;

    CEdit m_EditPzn;
    CListCtrl m_ListCtl;
    CString m_CPzn;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    BOOL InsList(char* kb, struct NACHLIEF* nachlief, class CStringArray& s);  // List-Box mit Eintraegen versorgen
    void MarkListPosChar(int Letter);
    void MarkListPos(int pos);
    void SelectEintrag();
    void UpdBearbkz(int pos);
    void CloseCursor();                     // DB-Cursor schliessen
    int  selectpos;                         // letzte selection merken
    int  m_funktion;                        // Servernummer

    struct satzadr
    {
        long kdauftragnr;
        long posnr;
        long datum;
        short postyp;
        struct satzadr* nextpos;
    };

    struct nachladr
    {
        long idfnr;
        struct satzadr* satzpos;
        struct nachladr* folgpos;
    };

    struct nachladr *startpos;


    // Generated message map functions
    afx_msg void OnChangeEditPzn();
    virtual void OnOK();
    afx_msg void OnButtonUpd();
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonSel();
    afx_msg void OnButtonArtikel();
    afx_msg void OnButtonBegrenzt();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );

    enum { IDD = IDD_AE_KND_NACHL };

    DECLARE_MESSAGE_MAP()
};

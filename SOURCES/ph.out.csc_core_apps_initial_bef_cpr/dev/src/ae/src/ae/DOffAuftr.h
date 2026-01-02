#pragma once
// doffauft.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDOffAuftr dialog

class CDOffAuftr : public CDialogMultiLang, CPageBrowser
{
public:
    CDOffAuftr(CWnd* pParent = NULL);       // standard constructor
    int DoModIfZROrdKnd(long KndNr,short VzNr); // zeigt offene Aufträge eines Kunden falls vorhanden
    int DoModIfZROrdGer();                  // zeigt offene Aufträge eines Geraetes falls vorhanden
    long GetNextOpenOrder();                // Rückgabe der nächsten offenen Auftragsnummer (ohne Dialog)
    long GetAufNr() { return m_AufNr; }     // Rückgabe der Auftragsnummer
    long m_KndNr;
    long m_IdfNr;
    short m_VzNr;
    short m_RegionNr;

    CStatic m_StaticAArt;
    CComboBox m_ComboAArt;
    CButton m_CheckVz;
    CButton m_CheckDafue;
    CComboBox m_ComboSort;
    CEdit   m_EditGeraet;
    CListCtrl m_ListCtl;
    CString m_Geraet;
    int     m_SortArt;
    BOOL    m_bDafue;
    BOOL    m_bVz;
    CButton m_CB_Alle;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);
    void AusgAuftraege(long KndNr, short VzNr, CString Geraet, int nKzUpDown = NEXT_PG);
    void CloseCursor();                     // DB-Cursor schliessen
    void MarkListPosChar(int Letter);       // Markierung einer Position in der Listbox (Buchstabe)
    long GetAuftrNr();                      // liefert AufNr
    void SetAuftrNr();                      // setzt AufNr und OnOK
    CString GetSortfield();
    long m_AufNr;                           // Auftragsnummer
    CString m_cSortfield;                   // Sortierfeld

    virtual BOOL OnInitDialog();
    afx_msg void OnDblclkListAuftrag(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownListAuftrag(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnOK();
    afx_msg void OnChangeEditGeraet();
    virtual void OnCancel();
    afx_msg void OnSelchangeComboSort();
    afx_msg void OnCheckDafue();
    afx_msg void OnDestroy();
    afx_msg void OnCheckVz();
    afx_msg void OnSelchangeComboAart();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedCheckAlle();
    virtual BOOL DestroyWindow();

    enum { IDD = IDD_AE_OFF_AUFT };

    DECLARE_MESSAGE_MAP()
};

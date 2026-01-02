#pragma once


// CFCOrders dialog

class CFCOrders : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CFCOrders)

public:
    CFCOrders(CWnd* pParent = NULL);   // standard constructor
    virtual ~CFCOrders();
    long GetAufNr() { return m_AufNr; }     // Rückgabe der Auftrtagsnummer

// Dialog Data
    enum { IDD = IDD_AE_FC_ORDERS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    void SetAuftrNr();                  // setzt AufNr und OnOK

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedButtonOffen();
    afx_msg void OnBnClickedButtonToComplete();
    afx_msg void OnBnClickedButtonToClose();
    afx_msg void OnDblclkListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
    CListCtrl m_ListCtl;

protected:
    int  m_nFunktion;       // Funktion, mit der selektiert wird
    bool m_bCursorOpen;     // Datenbankcursor geoeffnet
    long m_AufNr;           // Auftragsnummer
    void CloseCursor();     // DB-Cursor schliessen
    void GetPage();         // List-Box mit Eintraegen versorgen
};

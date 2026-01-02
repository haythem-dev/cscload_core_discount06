// DCallbackFetch.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#include "CallbackStatusManager.h"

class CDCallbackFetch : public CDialogMultiLang, CPageBrowser
{
public:
    CDCallbackFetch(CWnd* pParent = NULL);   // standard constructor

protected:
    // Dialog Data
    enum { IDD = IDD_AE_RR_HOLEN };
    CListCtrl    m_ListCtl2;
    CListCtrl    m_ListCtl;
    CImageList   m_ImageSmall;
    CComboBox    m_ComboStatus;
    CComboBox    m_ComboDivision;
    CComboBox    m_ComboReason;

    CCALLBACKTODO    m_todo;
    CCALLBACKTODONEW m_todonew;
    CCallbackStatusManager m_CallbackStatusManager;

    // Overrides
        // ClassWizard generated virtual function overrides
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    BOOL GetFuture();                       // List-Box für spätere Rückrufe mit Eintraegen versorgen
    BOOL GetWished();                       // List-Box für von Kunden gewünschten Terminen mit Eintraegen versorgen
    void SelectEintrag();
    void CloseCursor();                     // DB-Cursor schliessen
    void InitComboboxDivisison();

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnCbnSelchangeComboDivision();
    afx_msg void OnSelect();
    DECLARE_MESSAGE_MAP()
};

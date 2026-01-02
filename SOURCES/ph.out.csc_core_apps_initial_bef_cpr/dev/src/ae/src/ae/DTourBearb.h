// DTourBearb.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDTourBearb dialog

class CDTourBearb : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDTourBearb(CWnd* pParent = NULL);   // standard constructor
    CString m_Tour;

// Dialog Data
    enum { IDD = IDD_AE_TOURANZEIGE };
    CListCtrl m_ListCtl;

// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    void Ausgabe();
    void AusgabeKopf();
    void AusgabeAuftraege();
    long GetAuftrNr(CString &Status);           // liefert AufNr und Status
    void MarkListPosChar(int Letter);
    void Aenderung(int AenderungsArt);

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnOK();
    afx_msg void OnButtonFolge();
    afx_msg void OnButtonSowanne();
    afx_msg void OnButtonTour();
    afx_msg void OnButtonPrint();

    DECLARE_MESSAGE_MAP()
};

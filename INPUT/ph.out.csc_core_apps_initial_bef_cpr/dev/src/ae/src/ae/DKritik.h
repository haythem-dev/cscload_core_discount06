// DKritik.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CDKritik : public CDialogMultiLang, CPageBrowser
{
    // Construction
public:
    CDKritik(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_KRITIK };
    CButton m_CB_Vz;
    CDateTimeCtrl m_DT_Von;
    CDateTimeCtrl m_DT_Bis;
    CEdit m_EditTitel;
    CEdit m_EditIdf;
    CListCtrl m_ListCtl;
    CString m_CIdf;
    CString m_CTitel;
    CTime m_CTime_Bis;
    CTime m_CTime_Von;
    BOOL m_bVZ;
    CImageList m_ImageSmall;

    CComboBox    m_ComboStatus;
    CComboBox    m_ComboDivision;
    CComboBox    m_ComboReason;

    void SetKndVz(const short sVz) { m_KndVz = sVz; }
    const short GetKndVz() const { return m_KndVz; }    //Nr. des VZ des Kunden

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // List-Box mit Eintraegen versorgen
    void SelectEintrag();
    void CloseCursor();                     // DB-Cursor schliessen

    void InitComboboxDivisison();

    long m_Funktion;                        // Funktion, mit der selektiert wird
    bool m_IsKundeHome;
    short m_KndVz;                          // VZ des Kunden

    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnChangeEditIdf();
    afx_msg void OnChangeEditTitel();
    afx_msg void OnButtonKnd();
    afx_msg void OnButtonNeu();
    afx_msg void OnCheckVz();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnCbnSelchangeComboDivision();

    DECLARE_MESSAGE_MAP()
};

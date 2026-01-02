// DParNachart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDParNachart dialog

class CDParNachart : public CDialogMultiLang
{
// Construction
public:
    CDParNachart(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_PAR_NACHART };
    CListCtrl m_ListCtl;
    short m_FilialNr;


// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    void ReadDataInListBox();
    void AddPosToList(int Filiale, CString Formk, CString Lb, CString Na);

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonDel();
    afx_msg void OnButtonNeu();
    afx_msg void OnButtonUpd();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDParNachartUpd dialog

class CDParNachartUpd : public CDialogMultiLang
{
// Construction
public:
    BOOL m_bUpdate;                         // Schalter ob Update oder Insert
    CDParNachartUpd(CWnd* pParent = NULL);  // standard constructor

    enum { IDD = IDD_AE_PAR_NACHART_UPD };
    CEdit m_EditNa;
    CEdit m_EditLbnr;
    CEdit m_EditFormk;
    CEdit m_EditFiliale;
    int   m_iFiliale;
    CString m_CFormk;
    CString m_CLbnr;
    CString m_CNa;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditFormk();
    afx_msg void OnChangeEditLbnr();
    afx_msg void OnChangeEditNa();
    virtual void OnOK();

    DECLARE_MESSAGE_MAP()
};

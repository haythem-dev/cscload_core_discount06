// dauftxt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAufTxt dialog

class CDAufTxt : public CDialogMultiLang
{
// Construction
public:
    CDAufTxt(CWnd* pParent = NULL);   // standard constructor
    int UpdateLists(bool bWithOutput = true);   //Ausgabe in die Listboxen
    BOOL m_bInfoOrder;
    BOOL m_bSeraNachBearb;
    long m_ldatum;

    enum { IDD = IDD_AE_KOPF_FUSS };
    CComboBox m_ComboFuss;
    CComboBox m_ComboKopf;
    CListBox m_ListKopf;
    CListBox m_ListFuss;
    CString m_CKopf;
    CString m_CFuss;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonDel();
    afx_msg void OnButtonDelFuss();
    afx_msg void OnButtonDelKopf();
    afx_msg void OnButtonInsFuss();
    afx_msg void OnButtonInsKopf();
    afx_msg void OnEditchangeComboFuss();
    afx_msg void OnEditchangeComboKopf();
    afx_msg void OnDblclkListFuss();
    afx_msg void OnDblclkListKopf();
    DECLARE_MESSAGE_MAP()
};

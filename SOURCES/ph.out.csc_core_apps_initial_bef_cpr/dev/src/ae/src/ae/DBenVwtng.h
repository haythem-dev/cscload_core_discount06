// DBenVwtng.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBenVwtng dialog

class CDBenVwtng : public CDialogMultiLang
{
// Construction
public:
    CDBenVwtng(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_BEN_VWTNG };
    CEdit m_EditKennung;
    CString m_CKennung;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CAeUser m_User;     //User, der bearbeitet wird

    virtual BOOL OnInitDialog();
    afx_msg void OnBenLoesch();
    afx_msg void OnBenNeu();
    afx_msg void OnBenPwd();
    afx_msg void OnRechteAa();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnChangeKennung();
    DECLARE_MESSAGE_MAP()
};

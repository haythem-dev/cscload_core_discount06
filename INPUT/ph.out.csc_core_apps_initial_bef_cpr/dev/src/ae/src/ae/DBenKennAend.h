// DBenKennAend.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBenKennAend dialog

class CDBenKennAend : public CDialogMultiLang
{
// Construction
public:
    CDBenKennAend(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_KENNWORT };
    CEdit m_EditPwdNew2;
    CEdit m_EditPwdNew1;
    CString m_CPwdOld;
    CString m_CPwdNew1;
    CString m_CPwdNew2;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditPwdneu();
    afx_msg void OnChangeEditPwdneu2();
    DECLARE_MESSAGE_MAP()
};

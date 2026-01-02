// DKontrPwd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDKontrPwd dialog

class CDKontrPwd : public CDialogMultiLang
{
// Construction
public:
    CDKontrPwd(CWnd* pParent = NULL);   // standard constructor
    CString m_Pwd;                      // Password das überprüft werden soll

    enum { IDD = IDD_AE_PWD_EING };
    CEdit m_EditPwd;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

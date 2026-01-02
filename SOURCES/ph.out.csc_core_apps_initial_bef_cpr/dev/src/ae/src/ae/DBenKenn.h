// dbenkenn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBenKenn dialog

class CDBenKenn : public CDialogMultiLang
{
// Construction
public:
    CDBenKenn(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_BEN_KENNUNG };
    CString m_edit_kennung;
    CString m_edit_pwd;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnEnde();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};

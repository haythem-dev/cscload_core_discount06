// DInfoUpdZ.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDInfoUpdZ dialog

class CDInfoUpdZ : public CDialogMultiLang
{
// Construction
public:
    CDInfoUpdZ(CWnd* pParent = NULL);   // standard constructor

    int m_SatznrZentral;

    enum { IDD = IDD_INFOUPD_ZNTR };
    CEdit m_EditInfoZentral;
    CString m_CInfoZentral;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDInfoUpd dialog
class CDInfoUpd : public CDialogMultiLang
{
// Construction
public:
    CDInfoUpd(CWnd* pParent = NULL);   // standard constructor

    int m_SatznrLokal;

    enum { IDD = IDD_INFOUPD };
    CEdit m_EditInfoLokal;
    CString m_CInfoLokal;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

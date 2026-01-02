// DAendFil.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAendFil dialog

class CDAendFil : public CDialogMultiLang
{
// Construction
public:
    CDAendFil(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_AEND_FILIALE };
    CListBox m_ListBox;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};

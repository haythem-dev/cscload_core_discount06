// DAuftrEreign.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAuftrEreign dialog

class CDAuftrEreign : public CDialogMultiLang
{
// Construction
public:
    CDAuftrEreign(CWnd* pParent = NULL);   // standard constructor
    long m_AuftragsNr;
    long m_Datum;

    enum { IDD = IDD_AE_AUFTR_EREIGN };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

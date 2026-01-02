// dbestsb.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBestSB dialog

class CDBestSB : public CDialogMultiLang
{
// Construction
public:
    CDBestSB(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_SEKBEZ_BEST };
    CString m_ArtName;
    CString m_ArtEinheit;
    CString m_ArtNr;
    CString m_CDarreichform;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

// Entsperr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntsperr dialog

class CEntsperr : public CDialogMultiLang
{
// Construction
public:
    CEntsperr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_AUFTR_ENTSP };
    CEdit m_EditAuftrNr;
    CString m_CAuftrNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditAuftrNr();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};

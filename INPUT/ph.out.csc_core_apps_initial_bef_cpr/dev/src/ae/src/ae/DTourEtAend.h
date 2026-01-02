// DTourEtAend.h : header file
//

#define ETAA_TOUR           1
#define ETAA_SONDERWANNE    2
#define ETAA_TOURFOLGE      3

/////////////////////////////////////////////////////////////////////////////
// CDTourEtAend dialog

class CDTourEtAend : public CDialogMultiLang
{
// Construction
public:
    CDTourEtAend(CWnd* pParent = NULL);   // standard constructor
    int m_iAendArt;
    CString m_CTour;

    enum { IDD = IDD_AE_TOURUPD };
    CString m_CAuftrNr;
    CString m_CKndOrt;
    CString m_CKndName;
    CString m_Eingabe;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

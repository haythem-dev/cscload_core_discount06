// DKritikErf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDKritikErf dialog

class CDKritikErf : public CDialogMultiLang
{
// Construction
public:
    CDKritikErf(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_KRITIK_AUFN };
    CString m_CIdf;
    CString m_CKundenName;
    CString m_CPlz;
    CString m_COrt;
    CString m_CTelefon;
    CString m_CApotheke;
    CString m_CStrasse;
    CString m_CKurzwahl;

    void SetKndVz(const short sVz) { m_KndVz = sVz; }
    const short GetKndVz() const { return m_KndVz; }    //Nr. des VZ des Kunden

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()

    short m_KndVz;
};

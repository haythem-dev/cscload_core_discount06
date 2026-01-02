// DAufFrText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAufFrText dialog

class CDAufFrText : public CDialogMultiLang
{
// Construction
public:
    CDAufFrText(CWnd* pParent = NULL);  // standard constructor
    long PosNr;                         //Positionsnummer -1 == Neuerfassung
    CAeDoc* ptrDoc;                     //Zeiger auf das Dokument
    CString m_cAArt;

    enum { IDD = IDD_AE_FREITEXT };
    CComboBox m_ComboWg;
    CEdit m_EditPorto;
    CEdit m_EditText;
    CEdit m_EditGEP;
    CEdit m_EditDrabProz;
    CEdit m_EditDrabDM;
    CEdit m_EditDarreichform;
    CEdit m_EditBezeichnung;
    CEdit m_EditAEP;
    CEdit m_EditEinheit;
    CEdit m_EditMenge;
    CString m_CEinheit;
    long m_lMenge;
    CString m_CBezeichnung;
    CString m_CDarreichform;
    CString m_CText;
    CString m_dAEP;
    CString m_dDrabProz;
    CString m_dDrabDM;
    CString m_dGEP;
    CString m_CPorto;
    CString m_CApoDiNl;
    CComboBox m_ComboTax;
    CComboBox m_ComboPriso;

private:
    int m_iStd;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void InitMitWert();
    void InitOhneWert();

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditAep();
    afx_msg void OnChangeEditBezei();
    afx_msg void OnChangeEditDarr();
    afx_msg void OnChangeEditDrabDm();
    afx_msg void OnChangeEditDrabProz();
    afx_msg void OnChangeEditEinheit();
    afx_msg void OnChangeEditGep();
    afx_msg void OnChangeEditMenge();
    afx_msg void OnChangeEditText();
    afx_msg void OnRadioFakturieren();
    afx_msg void OnButtonGeloescht();
    afx_msg void OnChangeEditPorto();
    afx_msg void OnButtonSchliessen();
    afx_msg void OnButtonDisponieren();
    afx_msg void OnButtonAufnehmen();
    afx_msg void OnButtonInfotext();
    DECLARE_MESSAGE_MAP()
};

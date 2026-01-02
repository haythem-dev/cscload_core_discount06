// DParAufBearbErg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDParAufBearbErg dialog

class CDParAufBearbErg : public CDialogMultiLang
{
// Construction
public:
    CDParAufBearbErg(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PAR_AUFBEARB_ERG };
    CEdit   m_EditVb5;
    CEdit   m_EditVb4;
    CEdit   m_EditVb3;
    CEdit   m_EditVb2;
    CEdit   m_EditVb1;
    CButton m_CBNein;
    CButton m_CBJa;
    CEdit   m_EditZusAa;
    CEdit   m_EditMaxPos;
    CEdit   m_EditMaxKun;
    CEdit   m_EditKippZeit;
    CEdit   m_EditFiliale;
    CEdit   m_EditEndZeit;
    long    m_lEndZeit;
    int     m_iFiliale;
    int     m_iKippZeit;
    int     m_iMaxKun;
    int     m_iMaxPos;
    CString m_CZusAa;
    BOOL    m_bNein;
    BOOL    m_bJa;
    CString m_CVb1;
    CString m_CVb2;
    CString m_CVb3;
    CString m_CVb4;
    CString m_CVb5;
    short   m_FilialNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditEndzeit();
    afx_msg void OnChangeEditKippzeit();
    afx_msg void OnChangeEditMaxkun();
    afx_msg void OnChangeEditMaxpos();
    afx_msg void OnChangeEditZusaa();
    virtual void OnOK();
    afx_msg void OnCheckJa();
    afx_msg void OnCheckNein();
    afx_msg void OnChangeEditVb1();
    afx_msg void OnChangeEditVb2();
    afx_msg void OnChangeEditVb3();
    afx_msg void OnChangeEditVb4();
    afx_msg void OnChangeEditVb5();
    DECLARE_MESSAGE_MAP()
};

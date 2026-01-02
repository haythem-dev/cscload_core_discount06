// DAutrStat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAutrStat dialog

class CDAutrStat : public CDialogMultiLang
{
// Construction
public:
    CDAutrStat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_AUFTR_STAT };
    CEdit m_EditVzNr;
    CEdit m_EditDatum;
    CListCtrl m_ListCtl;
    CEdit m_EditUhrVonMin;
    CEdit m_EditUhrVon;
    CEdit m_EditUhrBisMin;
    CEdit m_EditUhrBis;
    CEdit m_EditIntervall;
    int m_iIntervall;
    int m_iUhrBis;
    int m_iUhrBisMin;
    int m_iUhrVon;
    int m_iUhrVonMin;
    CString m_CDatum;
    CString m_CVzNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    int m_ddatum;

    afx_msg void OnChangeEditIntervall();
    afx_msg void OnChangeEditUhrBis();
    afx_msg void OnChangeEditUhrBisMin();
    afx_msg void OnChangeEditUhrVon();
    afx_msg void OnChangeEditUhrVonMin();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnDruck();
    afx_msg void OnChangeEditDatum();
    afx_msg void OnChangeEditVz();
    DECLARE_MESSAGE_MAP()
};

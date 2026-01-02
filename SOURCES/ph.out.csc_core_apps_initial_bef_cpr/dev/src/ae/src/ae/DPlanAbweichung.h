// DPlanAbweichung.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDPlanAbweichung dialog

class CDPlanAbweichung : public CDialogMultiLang
{
// Construction
public:
    CDPlanAbweichung(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PLANVERSCHIEBUNG };
    CStatic m_CStaticSera;
    CStatic m_CStaticPhon;
    CStatic m_CStaticPara;
    CString m_CStringPhon;
    CString m_CStringPara;
    CString m_CStringSera;
    CString m_CStringDatumZeit;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonPara();
    afx_msg void OnButtonPhon();
    afx_msg void OnButtonSera();
    DECLARE_MESSAGE_MAP()

    int ServerCall(int iFunction, rufArt eArt, int iMinute);
    int CheckServerCall(rufArt eArt, int iFunction, int iSql);

    short m_sSaleCenterNo;

private:
    bool UpdateZeiteingabe(CString& cstMinute, rufArt eArt);
};


/////////////////////////////////////////////////////////////////////////////
// CDZeiteingabe dialog

class CDZeiteingabe : public CDialogMultiLang
{
// Construction
public:
    int m_iMinute;
    int m_iMinuteOld;
    CDZeiteingabe(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PLANZEITEINGABE };
    CEdit   m_CEditMinute;
    CString m_CStringEditMinute;
    CString m_CStringDatumZeit;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditMinute();
    virtual void OnCancel();
    DECLARE_MESSAGE_MAP()
};

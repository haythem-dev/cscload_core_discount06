#pragma once


// CDEncloserTimes-Dialogfeld

class CDEncloserTimes : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDEncloserTimes)

public:
    CDEncloserTimes(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDEncloserTimes();

    enum { IDD = IDD_AE_ENCLOSER_TIMES };
    CEdit m_edit_KndNr;
    CString m_cKndNr;
    CEdit m_edit_KndNr2;
    CString m_cKndNr2;
    CListCtrl m_List1;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonKnd();
    afx_msg void OnBnClickedButtonCopy();
    afx_msg void OnBnClickedButtonCopy2();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonUpd();
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnEnChangeEditKndnr();
    afx_msg void OnEnChangeEditKunde2();
    DECLARE_MESSAGE_MAP()

    void GetPage();     // List-Box mit Eintraegen versorgen

private:
    long m_lKunde;
    long m_lKunde2;
    CString m_CMC;
    CENCLOSERTIMES m_EncTimes;
};


// CDEncloserUpd-Dialogfeld

class CDEncloserUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDEncloserUpd)

public:
    CDEncloserUpd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDEncloserUpd();

    enum { IDD = IDD_AE_ENCLOSER_TIMS_UPD };
    CString m_cDiff;
    CString m_cMax;
    bool m_bUpdate;
    CEdit m_edit_Diff;
    CEdit m_edit_Max;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    DECLARE_MESSAGE_MAP()
};

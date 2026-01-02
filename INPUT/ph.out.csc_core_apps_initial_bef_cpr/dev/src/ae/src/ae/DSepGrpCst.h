#pragma once


// CDSepGrpCst-Dialogfeld

class CDSepGrpCst : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDSepGrpCst)

public:
    CDSepGrpCst(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDSepGrpCst();

    enum { IDD = IDD_AE_SEPERAT_GRP_CST };
    CStringArray m_Gruppen;
    CString m_cKndNr;
    CString m_cApo;
    CString m_cOrt;
    CListCtrl m_ListCtl;
    short m_sVzNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    void GetPage();
    CCSTSEPORDER m_SepOrder;

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnBnClickedButtonKnd();
    DECLARE_MESSAGE_MAP()
};

#pragma once


// CDBTMLicense-Dialogfeld

class CDBTMLicense : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDBTMLicense)

public:
    CDBTMLicense(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDBTMLicense();

// Dialogfelddaten
    enum { IDD = IDD_AE_BTM_LICENSE };
    CDateTimeCtrl m_DT_Datum;
    CTime   m_CT_Datum;
    CEdit   m_Edit_BTM_License;
    CString m_CBTMLicense;
    long    m_lDatum;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditBTMLicense();

    DECLARE_MESSAGE_MAP()
};

#pragma once

class CKCListCtrl;

// CDKommiChange-Dialogfeld

class CDKommiChange : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDKommiChange)

public:
    CDKommiChange(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDKommiChange();

// Dialogfelddaten
    enum { IDD = IDD_AE_KOMMI_CHANGE };
    CKCListCtrl* m_List1;
    CDateTimeCtrl m_DT_Datum;
    CTime   m_CT_Datum;
    CButton m_CheckAlle;
    CButton m_CheckDatum;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonRefresh();
    afx_msg void OnButtonUpdate();
    afx_msg void OnCheckDatum();
    afx_msg void OnButtonAuftrag();
    afx_msg void OnItemchangedListCtrl  (NMHDR *pNMHDR, LRESULT *pResult);

    DECLARE_MESSAGE_MAP()

    void GetPage();

// Data
protected:
    long m_SelDate;
};

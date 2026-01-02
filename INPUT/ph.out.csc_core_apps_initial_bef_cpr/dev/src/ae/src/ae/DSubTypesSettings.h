#pragma once


// CDSubTypesSettingsUpd-Dialogfeld

class CDSubTypesSettingsUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDSubTypesSettingsUpd)

public:
    CDSubTypesSettingsUpd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDSubTypesSettingsUpd();

// Dialogfelddaten
    enum { IDD = IDD_AE_SUBTYPESETTINGS_UPD };
    CComboBox m_ComboOrigin;
    short m_sBranchNo;
    BOOL m_bInsert;
    BOOL m_bAktiv;
    BOOL m_bMerge;
    CString m_csEndeZeit;
    CString m_csDuration;
    CString m_csOrigin;
    CEdit m_editEndeZeit;
    CEdit m_editDuration;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    afx_msg void OnEnChangeEditEndezeit();
    afx_msg void OnEnChangeEditDuration();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

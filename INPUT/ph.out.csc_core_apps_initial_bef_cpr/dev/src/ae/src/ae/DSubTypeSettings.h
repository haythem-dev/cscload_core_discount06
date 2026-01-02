#pragma once


// CDSubTypeSettings-Dialogfeld

class CDSubTypeSettings : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDSubTypeSettings)

public:
    CDSubTypeSettings(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDSubTypeSettings();

    enum { IDD = IDD_AE_SUBTYPESETTINGS };
    CListCtrl m_ListCtl;
    short m_sBranchNo;

    void GetPage();     // List-Box mit Eintraegen versorgen

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    CORIGINTYPESETTINGSPF m_OriginTypeSettings;

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonDelete();
    DECLARE_MESSAGE_MAP()
};

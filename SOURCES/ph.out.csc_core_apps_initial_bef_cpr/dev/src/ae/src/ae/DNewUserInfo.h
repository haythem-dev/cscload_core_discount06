#pragma once


// CDNewUserInfo-Dialogfeld

class CDNewUserInfo : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDNewUserInfo)

public:
    CDNewUserInfo(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDNewUserInfo();

// Dialogfelddaten
    enum { IDD = IDD_AE_NEW_USER_INFO };
    CDateTimeCtrl m_DT_ZeitVon;
    CDateTimeCtrl m_DT_Datum;
    CTime   m_CT_ZeitVon;
    CTime   m_CT_Datum;
    CButton m_CBTip;
    CEdit   m_Edit_Text;
    CString m_CText;
    CEdit   m_Edit_Dauer;
    CString m_CDauer;
    CButton m_CB_Alle;
    BOOL m_bAlle;
    long m_lActDate;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditText();
    afx_msg void OnChangeEditDauer();

    DECLARE_MESSAGE_MAP()
};

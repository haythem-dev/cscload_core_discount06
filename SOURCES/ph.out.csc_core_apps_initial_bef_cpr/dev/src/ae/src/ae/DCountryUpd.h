#pragma once


// CDCountryUpd-Dialogfeld

class CDCountryUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCountryUpd)

public:
    CDCountryUpd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDCountryUpd();

    enum { IDD = IDD_AE_COUNTRY_UPD };
    CEdit m_edit_Code;
    CString m_CCode;
    CEdit m_edit_Sera;
    CString m_CSera;
    CEdit m_edit_Print;
    CString m_CPrint;
    CEdit m_edit_XMLCode;
    CString m_CXMLCode;
    CEdit m_edit_XMLText;
    CString m_CXMLText;
    CCCODE* m_CountryCode;
    CButton m_CB_Aktiv;
    CButton m_CB_VB;
    BOOL m_bAktiv;
    BOOL m_bVB;

    short m_sFunktion;      //0 = Update, 1 = Insert

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangeEditCode();
    afx_msg void OnEnChangeEditSera();
    afx_msg void OnEnChangeEditPrint();
    afx_msg void OnEnChangeEditXmlCode();
    afx_msg void OnEnChangeEditXmlText();
    afx_msg void OnBnClickedOk();
    DECLARE_MESSAGE_MAP()
};

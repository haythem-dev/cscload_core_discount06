#pragma once


// CDSprachAuswahl-Dialogfeld

class CDSprachAuswahl : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDSprachAuswahl)

public:
    CDSprachAuswahl(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDSprachAuswahl();

    enum { IDD = IDD_AE_DSPRACHE };
    CComboBox m_Combo_Sprache;
    CString m_CSprache;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};

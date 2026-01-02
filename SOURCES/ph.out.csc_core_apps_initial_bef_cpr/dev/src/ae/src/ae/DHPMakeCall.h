#pragma once

// DHPMakeCall.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDHPMakeCall

class CDHPMakeCall : public CDialogMultiLang
{
// Konstruktion
public:
    CDHPMakeCall(CWnd* pParent = NULL);   // Standardkonstruktor

    enum { IDD = IDD_HP_MAKECALL };
    CEdit m_edit_TelNr;
    CString m_csTelNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};

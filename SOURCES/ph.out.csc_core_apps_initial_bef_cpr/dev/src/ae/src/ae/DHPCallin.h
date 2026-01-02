#pragma once

// DHPCallin.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDHPCallin

class CDHPCallin : public CDialogMultiLang
{
// Konstruktion
public:
    CDHPCallin(CWnd* pParent = NULL);   // Standardkonstruktor

    enum { IDD = IDD_HIPATH_CALLIN };
    CString m_csApo;
    CString m_csOrt;
    CString m_csCaption;
    CString m_csOtherBranch;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};

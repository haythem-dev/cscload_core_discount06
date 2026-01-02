#pragma once

// DTourUpd.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDTourUpd

class CDTourUpd : public CDialogMultiLang
{
// Konstruktion
public:
    CDTourUpd(CWnd* pParent = NULL);   // Standardkonstruktor

    short m_sKA;
    short m_sVz;

    enum { IDD = IDD_AE_TOUR_UPD };
    CComboBox m_Combo_KA;
    CString m_csBemerkung;
    CString m_csFolge;
    CString m_csTour;
    CString m_csZeit;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};

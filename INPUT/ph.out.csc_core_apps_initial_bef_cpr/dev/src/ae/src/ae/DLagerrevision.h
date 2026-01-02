#pragma once

// DLagerrevision.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDLagerrevision

class CDLagerrevision : public CDialogMultiLang
{
// Konstruktion
public:
    CDLagerrevision(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
    enum { IDD = IDD_AE_LAGERREVISION };
    CListCtrl m_ListCtl;
    CEdit m_Edit_Filiale;
    CEdit m_Edit_Artikel_nr;
    CDateTimeCtrl m_DT_Datum;
    CTime m_CTime_Datum;
    CString m_CArtikel_nr;
    CString m_CFiliale;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnDruck();
    afx_msg void OnChangeEditArtikelNr();
    afx_msg void OnChangeEditFiliale();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};

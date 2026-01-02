#pragma once

// DChooseFiliale.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDChooseFiliale

class CDChooseFiliale : public CDialogMultiLang
{
// Konstruktion
public:
    CDChooseFiliale(CWnd* pParent = NULL);   // Standardkonstruktor

    enum { IDD = IDD_AE_CHOOSE_FILIALE };
    CListCtrl m_ListCtl;
    short m_FilialNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};

#pragma once
// AltFil.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#include "EditTime.h"

class CAltFil : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CAltFil(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_ALTFIL };
    CListCtrl m_ListCtl;
    short     m_FilialNr;           // eigene Filialnr


// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);      // List-Box mit Eintraegen versorgen
    void SelectEintrag();
    void CloseCursor();             // DB-Cursor schliessen

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDelete();
    afx_msg void OnNeu();
    afx_msg void OnUpdate();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CUpdAltfil dialog

class CUpdAltfil : public CDialogMultiLang
{
// Construction
public:
    CUpdAltfil(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_UPD_ALTFIL };
    CEditTime m_EditTourzeitTag;
    CEditTime m_EditTourzeit;
    CEdit m_EditBgaTag;
    CEdit m_EditKdnr;
    CEdit m_EditFolge;
    CEdit m_EditFilnr;
    BOOL m_bAb;
    CString m_CFilnr;
    CString m_CFolge;
    CString m_CKdnr;
    CString m_CBgaTag;
    CString m_CZeit;
    CString m_CZeitTag;
    short m_sTyp;

// Overrides
    // ClassWizard generated virtual function overrides
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:

    // Generated message map functions
    afx_msg void OnChangeEditFilnr();
    afx_msg void OnChangeEditFolge();
    afx_msg void OnChangeEditKdnr();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditBgaTag();

    DECLARE_MESSAGE_MAP()

public:
    CEditTime m_EditFahrzeit;
    CString m_CFahrzeit;
    CComboBox m_ComboTyp;
    afx_msg void OnCbnSelchangeComboTyp();
};

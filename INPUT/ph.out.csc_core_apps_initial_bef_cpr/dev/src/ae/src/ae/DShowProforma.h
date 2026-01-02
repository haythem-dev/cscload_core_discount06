#pragma once

#include "solistctrl.h"

// CDShowProforma-Dialogfeld

class CDShowProforma : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDShowProforma)

public:
    CDShowProforma(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDShowProforma();

    enum { IDD = IDD_AE_SHOW_PROFORMA };
    long m_lKndNr;
    CImageList m_ImageSmall;
    CSOListCtrl* m_ListFV;
    CSOListCtrl* m_ListKK;
    CSOListCtrl* m_ListEH;
    CString m_CBruttoFV;
    CString m_CRabFV;
    CString m_CBruttoKK;
    CString m_CBruttoEH;
    CString m_CRabKK;
    CString m_CRabEH;
    CString m_CNettoKK;
    CString m_CNettoFV;
    CString m_CNettoEH;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    void FillList(int pos, AUFPOSBUCH* ptrPos, CSOListCtrl* ListCtl, char* kb);
    bool m_bFV;
    bool m_bKK;
    bool m_bEH;
    void SetColumnWidthUser(char* name, char* keypath, int anz);
    void WriteColumnWidthUser(char* name, char* keypath, int anz);
    void ChangeColumnWidth();
    void RepositionWindow();
    int  m_Spalten[COL_ANZ_LIST];
    bool m_ChangeCol;
    bool m_NoChangeCol;
    int  m_anzFV;
    int  m_anzKK;
    int  m_anzEH;

    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    afx_msg void OnHdnItemchangedListFv(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
};

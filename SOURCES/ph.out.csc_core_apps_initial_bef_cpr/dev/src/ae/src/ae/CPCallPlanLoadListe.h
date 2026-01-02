#pragma once

// CPCallPlanLoadListe.h : Header-Datei
//
#include "ppCallPlanLoad.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCPCallPlanLoadListe

class CCPCallPlanLoadListe : public CDialogMultiLang
{
// Konstruktion
public:
    CCPCallPlanLoadListe(CWnd* pParent = NULL);   // Standardkonstruktor

    enum { IDD = IDD_CP_CALLPLANLOAD_LISTE };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonDelete();
    afx_msg void OnButtonDruck();
    afx_msg void OnButtonInsert();
    afx_msg void OnButtonUpdate();
    afx_msg void OnOk();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

public: //methodes
    void SetVzNr(const short sVzNr) { m_sVzNr = sVzNr; }
    short GetVzNr()                 { return m_sVzNr; }

protected: //members
    short           m_sVzNr;
    ppCallPlanLoad  m_srvCallPlanLoad;
    CLetterMan m_kb;

protected: //methodes
    bool GetPage();
    bool SetValueIntoList(int pos);
};

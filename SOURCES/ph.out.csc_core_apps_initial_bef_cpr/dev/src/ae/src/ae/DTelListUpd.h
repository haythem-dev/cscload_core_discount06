#pragma once

// DTelListUpd.h : Header-Datei
//
#include "koplist.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDTelListUpd

class CDTelListUpd : public CDialogMultiLang
{
// Konstruktion
public:
    CDTelListUpd(CWnd* pParent = NULL);   // Standardkonstruktor

    enum { IDD = IDD_AE_TELLIST_UPD };
    CButton m_ZURUECK;
    CButton m_WEITER;
    CButton m_UPDATE;
    CButton m_NEW;
    CButton m_DELETE;
    CEdit m_edit_PZN;
    CEdit m_edit_Name;
    CEdit m_edit_Hinweis;
    CEdit m_edit_Bemerkung;
    CEdit m_edit_Alternativ;
    CEdit m_edit_LIEFERINFO;
    CButton m_CHK_LIEFER_BLOCKED;
    CButton m_CHK_LIEFER_QUALIFIED;
    CString m_csAlternativ;
    CString m_csBemerkung;
    CString m_csHinweis;
    CString m_csName;
    CString m_csPZN;
    CKOPLIST m_a;
    CString m_ArtCode;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    void GetLieferInfo(long beslaNr);
    void ShowLieferInfoControls();
    void ShowLieferInfoControls(BOOL fShow);

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonNew();
    afx_msg void OnButtonUpdate();
    afx_msg void OnButtonWeiter();
    afx_msg void OnButtonZurueck();
    afx_msg void OnChangeEditAlternativ();
    afx_msg void OnChangeEditBemerkung();
    afx_msg void OnChangeEditHinweis();
    afx_msg void OnChangeEditName();
    afx_msg void OnChangeEditPzn();
    virtual void OnOK();
    afx_msg void OnButtonDelete();
    afx_msg void OnKillfocusEditName();
    afx_msg void OnKillfocusEditPZN();
    afx_msg void OnDestroy();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()

private:
    bool UpdateTelList(int func);
    bool LoadTelList(bool bNext);
};

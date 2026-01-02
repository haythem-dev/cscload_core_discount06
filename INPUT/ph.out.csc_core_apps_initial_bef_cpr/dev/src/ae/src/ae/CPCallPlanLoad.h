#pragma once

// CPCallPlanLoad.h : Header-Datei
//
#include "ppCallPlanLoad.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCPCallPlanLoad

class CCPCallPlanLoad : public CDialogMultiLang
{
// Konstruktion
public:
    CCPCallPlanLoad(CWnd* pParent
                                 , ppCallPlanLoad* psrvCallPlanLoad
                                 ,const int iFunktion);

public:
    const bool IsChanged() const { return m_bIsChanged; }

    enum { IDD = IDD_CP_CALLPLANLOAD };
    CDateTimeCtrl m_DateCtl_Date;
    CEdit m_EditTourid;
    CEdit m_EditZeitBis;
    CEdit m_EditZeitVon;
    CComboBox m_CComboBoxNdl;
    CComboBox m_CComboBoxCountry;
    CComboBox m_CComboBoxDay;
    CString m_csTimeTo;
    CString m_csTimeFrom;
    CTime m_CTDate;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnChangeEditZeitbis();
    afx_msg void OnChangeEditZeitvon();
    afx_msg void OnChangeEditTourid();
    afx_msg void OnButtonReset();
    afx_msg void OnDatetimechangeDate(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

protected: //methodes
    void InitializeCombos();
    void MakeEditable();
    void InitEditable();
    bool GetDataFromScreen();
    void UpdateDay();

protected:
    ppCallPlanLoad* m_psrvCallPlanLoad;
    long            m_lDate;
    int             m_iInsert;
    int             m_iFunktion;
    int             m_iZeitVon;
    int             m_iZeitBis;
    int             m_iTourid;
    bool            m_bIsChanged;
};

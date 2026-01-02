#pragma once

#include <atltime.h>


class CDDelayedCstAll : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDDelayedCstAll)

public:
    CDDelayedCstAll(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDDelayedCstAll();

// Dialogfelddaten
    enum { IDD = IDD_AE_DD_CST_ALL };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()

public:
    CComboBox m_combo_Tag;
    CString m_CTag;
    CDateTimeCtrl m_DT_Zeit;
    CTime m_CT_Zeit;
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonAktiv();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnBnClickedButtonDeak();
    virtual BOOL OnInitDialog();
    CDELAYEDCST m_Cst;
    //CComboBox m_Combo_Tour;
    //CString m_CTour;
    CButton m_CB_BTM;
    BOOL m_bBTM;
    CButton m_CB_KK;
    BOOL m_bKK;
    CButton m_CB_K08;
    BOOL m_bK08;
    CButton m_CB_K20;
    BOOL m_bK20;
};

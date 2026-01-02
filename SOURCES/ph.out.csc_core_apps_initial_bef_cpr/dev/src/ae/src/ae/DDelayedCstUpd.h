#pragma once
#include <atltime.h>


// CDDelayedCstUpd-Dialogfeld

class CDDelayedCstUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDDelayedCstUpd)

public:
    CDDelayedCstUpd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDDelayedCstUpd();

    enum { IDD = IDD_AE_DELAYEDCST_UPD };
    CComboBox m_combo_WTag;
    CString m_CWTag;
    CComboBox m_combo_Tour;
    CString m_CTour;
    CButton m_CB_Aktiv;
    BOOL m_bAktiv;
    short m_sVzNr;
    long m_lKdNr;
    CString m_Tag;                  // Wochentag
    CDELAYEDCST m_Cst;
    CString m_CDDTag;               // Wochentag auf den zurückgestellt wird
    CString m_CDDTour;              // Tour auf die zurückgestellt wird
    CStringArray* m_pTagtab;

    CString m_CTest;
    CComboBox m_combo_TourMax;
    CString m_CTourMax;
    CButton m_CB_BTM;
    BOOL m_bBTM;
    CButton m_CB_KK;
    BOOL m_bKK;
    CButton m_CB_K08;
    BOOL m_bK08;
    CButton m_CB_K20;
    BOOL m_bK20;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnCbnSelchangeComboWtag();
    DECLARE_MESSAGE_MAP()

    void SetTag();
};

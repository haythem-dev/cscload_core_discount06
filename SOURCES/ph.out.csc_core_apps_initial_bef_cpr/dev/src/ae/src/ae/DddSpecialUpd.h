#pragma once


#include <atltime.h>

// CDddSpecialUpd dialog

class CDddSpecialUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDddSpecialUpd)

public:
    CDddSpecialUpd(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDddSpecialUpd();

// Dialog Data
    enum { IDD = IDD_AE_DD_SPECIAL };

    enum functiontypes { DDupdate = 0, DDinsert };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

public:
    long m_iWD;
    long m_iWDDD;
    long m_Zeit;
    long m_lFrom;
    long m_lTo;
    int m_iFunction;
    long m_lActDate;
    CComboBox m_combo_Tag;
    CComboBox m_combo_Tag_DD;
    CString m_CTag;
    CString m_CTagDD;
    CDateTimeCtrl m_DT_Zeit;
    CTime m_CT_Zeit;
    CDateTimeCtrl m_DTfrom;
    CTime m_From;
    CButton m_CB_BTM;
    BOOL m_bBTM;
    CButton m_CB_KK;
    BOOL m_bKK;
    CButton m_CB_K08;
    BOOL m_bK08;
    CButton m_CB_K20;
    BOOL m_bK20;
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
    afx_msg void OnDtnDatetimechangeDatetimepickerDatefrom(NMHDR *pNMHDR, LRESULT *pResult);
};

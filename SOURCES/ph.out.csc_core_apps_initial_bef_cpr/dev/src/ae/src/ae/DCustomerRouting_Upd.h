#pragma once
#include <atltime.h>


// CDCustomerRouting_Upd-Dialogfeld

class CDCustomerRouting_Upd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCustomerRouting_Upd)

public:
    CDCustomerRouting_Upd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDCustomerRouting_Upd();

    enum { IDD = IDD_AE_CUSTOMERROUTING_UPD };

    enum i_typ { UPDATE = 0,INSERT = 1 };

    int m_iTag;
    CStringArray* m_pTagtab;
    CDateTimeCtrl m_DateTime_Von;
    CDateTimeCtrl m_DateTime_Bis;
    CEdit m_Edit_VZ2;
    CString m_CVz2;
    CString m_CVz;
    CString m_CApo;
    CString m_COrt;
    CComboBox m_Combo_Tag;
    CString m_CTag;
    CTime m_CT_Von;
    CTime m_CT_Bis;

    int m_ifunktion;    // 0 = update, 1 = insert
    short m_sVznr;
    long m_lKundennr;
    CString m_CTagalt;
    long m_Zeitalt;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangeEditVz2();
    afx_msg void OnBnClickedOk();
    DECLARE_MESSAGE_MAP()
};

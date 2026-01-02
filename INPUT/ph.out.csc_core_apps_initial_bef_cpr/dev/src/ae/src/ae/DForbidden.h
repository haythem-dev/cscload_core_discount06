#pragma once


// CDForbidden-Dialogfeld

class CDForbidden : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDForbidden)

public:
    CDForbidden(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDForbidden();

    enum { IDD = IDD_AE_FORBIDDEN };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    void GetPage();     // Fuellen der Listbox

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonUpdate();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnHdnItemdblclickList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
};

#pragma once


// CDServiceOrder-Dialogfeld

class CDServiceOrder : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDServiceOrder)

public:
    CDServiceOrder(CWnd* pParent = NULL);   // Standardkonstruktor
    CAeDoc* m_ptrDoc;                       // Zeiger auf das Dokument
    virtual ~CDServiceOrder();

    enum { IDD = IDD_AE_SERVICE_ORDER };
    CListCtrl m_List1;
    short m_sServType;
    long m_lKndNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg LRESULT OnCloseDialog(WPARAM wParam, LPARAM lParam);
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonEnde();
    afx_msg void OnButtonBearb();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );

    DECLARE_MESSAGE_MAP()
};

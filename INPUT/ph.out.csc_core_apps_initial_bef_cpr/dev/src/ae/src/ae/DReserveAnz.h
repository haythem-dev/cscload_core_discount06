#pragma once


// CDReserveAnz-Dialogfeld

class CDReserveAnz : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDReserveAnz)

public:
    CDReserveAnz(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDReserveAnz();

    enum { IDD = IDD_AE_RESERVE_ANZ };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();

    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    afx_msg void OnBnClickedButtonDruck();
    DECLARE_MESSAGE_MAP()

    CListCtrl m_ListCtl;
};

#pragma once


// CDRoutBack-Dialogfeld

class CDRoutBack : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDRoutBack)

public:
    CDRoutBack(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDRoutBack();

    enum { IDD = IDD_AE_ROUTBACK };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonBlind();
    DECLARE_MESSAGE_MAP()

private:
    CListCtrl m_ListCtl;
    CBACKROUT m_BackRouting;

    void GetPage();     // List-Box mit Eintraegen versorgen
};

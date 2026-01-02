#pragma once


// CDBackRouting-Dialogfeld

class CDBackRouting : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDBackRouting)

public:
    CDBackRouting(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDBackRouting();

    enum { IDD = IDD_AE_BACKROUTING };

    CListCtrl m_ListCtl;
    CEdit m_exit_Abteilung;
    CString m_cAbteilung;
    CEdit m_edit_TelNr;
    CString m_cTelNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangeEditAbteilung();
    afx_msg void OnEnChangeEditTelnr();
    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonDelete();
    DECLARE_MESSAGE_MAP()

private:
    CBACKROUT m_BackRouting;
    void GetPage();     // List-Box mit Eintraegen versorgen
};

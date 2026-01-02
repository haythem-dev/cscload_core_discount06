#pragma once


// CDSammelArt-Dialogfeld

class CDSammelArt : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDSammelArt)

public:
    CDSammelArt(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDSammelArt();

    enum { IDD = IDD_SAMMEL_ART };
    CEdit m_edit_Menge;
    CString m_CMenge;
    CEdit m_edit_PZN;
    CString m_CPZN;
    CString m_CArtNr;
    CListCtrl* m_pListCtl;
    short m_sListCount;
    CString m_CArt;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonArt();
    afx_msg void OnEnChangeEditMenge();
    afx_msg void OnEnChangeEditPzn();
    DECLARE_MESSAGE_MAP()
};

#pragma once


// CDSammelKnd-Dialogfeld

class CDSammelKnd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDSammelKnd)

public:
    CDSammelKnd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDSammelKnd();

// Dialogfelddaten
    enum { IDD = IDD_SAMMEL_KND };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()
public:
    // methods
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonKnd();
    afx_msg void OnEnChangeEditIdf();
    virtual BOOL DestroyWindow();

    // members
    bool        m_EnableAeGesperrt;
    CEdit       m_edit_IDF;
    CListCtrl*  m_pListCtl;
    short       m_sListCount;
    CString     m_CIdf;
    bool        m_bKundeHome;

    CString     m_CMC;
    CString     m_CArt;
    CString     m_Title;
};

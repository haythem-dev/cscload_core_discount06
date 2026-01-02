#pragma once


// CDBeilage-Dialogfeld

class CDBeilage : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDBeilage)

public:
    CDBeilage(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDBeilage();

    enum { IDD = IDD_AE_BEILAGE };
    CString m_cArtikel;
    CString m_cText;
    CEdit m_edit_Artikel;
    CEdit m_edit_Text;
    CARTINSERT m_Beilage;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonUpdate();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnEnChangeEditArtkelnr();
    DECLARE_MESSAGE_MAP()

private:
    int m_lArtNr;
};

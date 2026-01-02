#pragma once


// CDAeArtVerbundFiliale-Dialogfeld

class CDAeArtVerbundFiliale : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDAeArtVerbundFiliale)

public:
    CDAeArtVerbundFiliale(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDAeArtVerbundFiliale();

    enum { IDD = IDD_AE_ART_VERBUNDFILIALE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()

public:
    CListCtrl m_ListCtl;
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonUpdate();
    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnBnClickedButtonChange();
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);

    //members
    long m_lArticleNo;
    CString m_cArticleCode;
    CATICLEAUX m_DkVbFil;

    //methodes
    void SetHeader();
    void GetPage();
    bool SelArtikel();
    void SetArtikelNr(const long lArtikelNr) { m_lArticleNo = lArtikelNr; }
    long GetArtikelNr() { return m_lArticleNo; }
    void SetArticleCode(const CString cArticleCode) { m_cArticleCode = cArticleCode; }
    CString GetArticleCode() { return m_cArticleCode; }
};

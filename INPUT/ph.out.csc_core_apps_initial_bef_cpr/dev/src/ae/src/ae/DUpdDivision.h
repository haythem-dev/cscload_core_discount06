#pragma once


// CDUpdDivision-Dialogfeld

class CDUpdDivision : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDUpdDivision)

public:
    CDUpdDivision(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDUpdDivision();

    void SetVzNr(const short sVz) { m_sVzNr = sVz; }
    const short GetVzNr() const { return m_sVzNr; }

    enum { IDD = IDD_AE_CALLBACKDIVISION };

protected:
    CListCtrl m_ListCtl;
    CCALLBACKDIVISION m_Partner;
    short m_sVzNr;
    long m_lStartNoCallback;
    long m_lEndNoCallback;

    BOOL GetPage( int nKzUpDown = NEXT_PG );    // List-Box mit Eintraegen versorgen
    void SelectEintrag();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonChange();
    afx_msg void OnButtonDelete();
    afx_msg void OnButtonNew();
    DECLARE_MESSAGE_MAP()
};

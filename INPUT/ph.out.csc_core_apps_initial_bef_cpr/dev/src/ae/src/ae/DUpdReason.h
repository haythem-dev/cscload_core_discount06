#pragma once


// CDUpdReason-Dialogfeld

class CDUpdReason : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDUpdReason)

public:
    CDUpdReason(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDUpdReason();

    void SetVzNr(const short sVz) { m_sVzNr = sVz; }
    const short GetVzNr() const { return m_sVzNr; }
    CListCtrl m_ListCtl;
    CString m_CName;
    CString m_CMail;
    short m_sPartnerNo;         // Partnernumer
    bool m_new;                 // Kennz. ob insert oder update

    enum { IDD = IDD_AE_CALLBACK_REASON };

protected:
    CCALLBACKREASONS m_Callbackreasons;
    short m_sVzNr;

    BOOL GetPage(int nKzUpDown = NEXT_PG);      // List-Box mit Eintraegen versorgen
    void SelectEintrag();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonNewreason();
    afx_msg void OnButtonDelreason();
    DECLARE_MESSAGE_MAP()
};

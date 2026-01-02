#pragma once


// CDDealerUmsatz-Dialogfeld

class CDDealerUmsatz : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDDealerUmsatz)

public:
    CDDealerUmsatz(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDDealerUmsatz();

// Dialogfelddaten
    enum { IDD = IDD_AE_DEALER_UMSATZ };
    CDateTimeCtrl m_DT_DatumVon;
    CDateTimeCtrl m_DT_DatumBis;
    CTime m_CT_DatumBis;
    CTime m_CT_DatumVon;
    CListCtrl m_List1;
    CListCtrl m_List2;
    CString m_CName;
    CString m_CUID;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();

    DECLARE_MESSAGE_MAP()
    void GetPage();
};

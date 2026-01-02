#pragma once


// CDRabattOrder-Dialogfeld

class CDRabattOrder : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDRabattOrder)

public:
    CDRabattOrder(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDRabattOrder();

// Dialogfelddaten
    enum { IDD = IDD_AE_RABATT_ORDER };
    CDateTimeCtrl m_DT_DatumVon;
    CDateTimeCtrl m_DT_DatumBis;
    CTime   m_CT_DatumBis;
    CTime   m_CT_DatumVon;
    CButton m_CheckKette;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnCheckKette();

    DECLARE_MESSAGE_MAP()
};

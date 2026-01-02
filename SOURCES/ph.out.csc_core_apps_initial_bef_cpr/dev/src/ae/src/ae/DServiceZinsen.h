#pragma once


// CDServiceZinsen-Dialogfeld

class CDServiceZinsen : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDServiceZinsen)

public:
    CDServiceZinsen(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDServiceZinsen();

// Dialogfelddaten
    enum { IDD = IDD_AE_SERVICE_ZINSEN };
    CComboBox m_ComboTax;
    CDateTimeCtrl m_DT_From;
    CDateTimeCtrl m_DT_To;
    CTime   m_CT_From;
    CTime   m_CT_To;
    CEdit   m_Edit_Price;
    CString m_csPrice;
    CString m_csName;
    short m_sServiceNo;
    long m_PosNr;
    CAeDoc* m_ptrDoc;           //Zeiger auf das Dokument
    int m_iTax;                 //Taxlevel

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnButtonBuchen();

    DECLARE_MESSAGE_MAP()

// Data
protected:
    long m_lActDate;
};

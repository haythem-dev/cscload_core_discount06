#pragma once


// CDServicePos-Dialogfeld

class CDServicePos : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDServicePos)

public:
    CDServicePos(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDServicePos();

    enum { IDD = IDD_AE_SERVICE_POS };
    CEdit m_Edit_Qty;
    CEdit m_Edit_Price;
    CComboBox m_ComboTax;
    CString m_csQty;
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
};

#pragma once

#include "PageTabCtrlMultiLang.h"
#include "ppDataTypes.h"
#include "TabPageMultiLang.h"
#include "DOrderInformation1.h"
#include "DOrderInformation2.h"

class CDOrderInformation;
class CDOrderInformation1;
class CDOrderInformation2;
class CKNDINF;
struct KNDINF;


// CDOrderInfromation dialog

class CDOrderInformation : public CDialogMultiLang
{
    //DECLARE_DYNAMIC(CDOrderInformation)

public:
    CDOrderInformation(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDOrderInformation();

    long m_AuftrNr;
    long m_LAuftNr;
    long m_TenderNo;
    long m_Datum;                               // Datum bei älteren Aufträgen
    bool m_bSelProforma;
    bool m_bNoOpen;
    long m_lDatumAuftrag;                       // Datum des Auftrags
    long m_lTour;                               // Tour des Auftrags
    CString m_cRechnr;
    CString m_cIVCnr;
    CListBox m_ListInvoice;
    long m_ActDatum;                            // aktuelles Datum
    long Status;
    short m_sBatchAdvice;                       // Status Chargenbeleg


#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDER_INFORMATION };
#endif
    CPageTabCtrlMultiLang m_CTabCtrlOrderInformation;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedButtonRechnung();
    afx_msg void OnLbnDblclkList1Invoice();
    afx_msg void OnBnClickedButtonBatch();

    DECLARE_MESSAGE_MAP()

// Implementation
protected:
    void AusgKopf();
    long m_KndNr;
    long m_IdfNr;
    long m_lEtartklasse1;
    short m_VzNr;
    short m_sFVRabkonto;                // Kennz. Rabattkonto FV
    short m_sKKRabkonto;                // Kennz. Rabattkonto KK
    bool m_bVbKunde;

public:
    CDOrderInformation1 m_PageDOrderInformation1;
    CDOrderInformation2 m_PageDOrderInformation2;

    CString IDF_Nr;
    CString Wertig;
    CString Inhaber;
    CString Apotheke;
    CString PLZ;
    CString Kndtext;
    CString Ort;
    CString Tel;
    CString Tel_KW;
    CString Dafue_Typ;
    CString Zln;
    CString AW;
    CString Lif_Wert;
    CString Dzw;
    CString Net_Wert;
    CString AA;
    CString BA;
    CString KA;
    CString Auftr_Nr;
    CString Tour;
    CString Rech_Nr;
    CString Lauft_Nr;
    CString Datum;
    CString Bemerk;
    CString Vsenr;
    CString Verbund;
    CString ValutaMon;
    CString ValutaDatum;
    CString Paymenttype;
    CString Paymentdate;
    CString WertNettoFV;
    CString WertTaxFV;
    CString WertBruttoFV;
    CString WertNettoKK;
    CString WertTaxKK;
    CString WertBruttoKK;
    CString WertNettoEH;
    CString WertTaxEH;
    CString WertBruttoEH;
    CString PFDatum;
    CString OrderLabel;
    CString OrderLabelCount;
    CString Rech_Nr_Save;
    CString ZuGrund;
    CStatic m_SapReferenceNo;
    CStatic m_SapReferenceNoValue;

private:
    bool ReadOrder(CAUFTRAG& auftrag);
    void InitInvoice();
    void ReadCustomerInfo(CKNDINF& kndinf, const CAUFTRAG& auftrag);
    void SetDate(const CAUFTRAG& auftrag);
    void SetOrderLabelCount(const CKNDINF& kndinf, const CAUFTRAG& auftrag);
    void SetStockOrderNo();
    void SetCustomerInfoValues(const KNDINF& kndinf);
    void SetOrderValues(const AUFTRAG& auftrag);
    void SetOrderValuesBG(const AUFTRAG& auftrag);
    void SetOrderValuesRS(const AUFTRAG& auftrag);
    void SetInvoice();
    void SetTour(CString tourId);
    void InitByParAufBearb();
    void InitPage1();
    void InitPage2();
    void InitBatchAndAddPage2();
};

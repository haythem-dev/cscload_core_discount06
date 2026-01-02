#pragma once

#include "PageTabCtrlMultiLang.h"
#include "ppDataTypes.h"
#include "TabPageMultiLang.h"
#include "DVbBuchen.h"
#include "AufInflistctrl.h"

// CDOrderInformation1 dialog

class CDOrderInformation1 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderInformation1)

public:
    CDOrderInformation1();
    virtual ~CDOrderInformation1();

    CButton m_CBNurDef;
    CString m_cRechnr;
    CString m_cIVCnr;
    vector<AUFPOSBUCH> m_lAuf;
    CImageList m_ImageSmall;
    CAufInfListCtrl* m_ListCtl;

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDER_INFORMATION1 };
#endif
    BOOL m_bNurDef;
    long m_AuftrNr;
    long m_LAuftNr;
    long m_TenderNo;
    long m_Datum;                               // Datum bei älteren Aufträgen
    bool m_bSelProforma;
    bool m_bNoOpen;
    long m_lDatumAuftrag;                       // Datum des Auftrags
    long m_lTour;                               // Tour des Auftrags
    long m_KndNr;
    long m_IdfNr;
    long m_lEtartklasse1;
    short m_VzNr;
    long m_ActDatum;                            // aktuelles Datum
    long Status;
    bool m_bCall;

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
    CString ZuGrund;

    virtual int GetID() { return IDD; }

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    void AusgKopf();
    void AusgPos();
    void ReadPos();
    void IfKopfOrFussZln();
    void GetArtKennz(long artikelnr, CString &ArtKZ, CString &ProdQuota);
    bool IsVbKunde();
    short m_sFVRabkonto;                        // Kennz. Rabattkonto FV
    short m_sKKRabkonto;                        // Kennz. Rabattkonto KK
    bool m_bVbKunde;
    virtual LPCTSTR GetTabTitle();

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonKopfFuss();
    afx_msg void OnButtonEreignis();
    afx_msg void OnButtonDruck();
    virtual void OnOK();
    afx_msg void OnCheckNurDef();
    afx_msg void OnButtonVbBuch();
    afx_msg void OnButtonDefbuch();
    afx_msg void OnButtonSeralog();
    afx_msg void OnButtonAufNeu();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    virtual BOOL DestroyWindow();
    afx_msg void OnLvnColumnclickListAuftrag(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonAufNeuAlle();
    afx_msg void OnBnClickedButtonAufCallback();
    afx_msg void OnBnClickedButtonCremaStorno();
    afx_msg void OnBnClickedButtonCremaClose();
    afx_msg void OnButtonCall();
    virtual BOOL OnSetActive();
    afx_msg void OnBnClickedButtonLief();
    afx_msg void OnBnClickedButtonDruck2();

    DECLARE_MESSAGE_MAP()

private:
    void AddDeliveryDateTimeToList(int pos, vector<AUFPOSBUCH>::iterator& it);

    void InitVbArtikel(vector<CDVbBuchen::VbArtikel>& m_pl, int pos, bool bUseAmgeAsBmge = false);
    void InitVbBuchenDlg(CDVbBuchen& dlgVbBuchen);
};

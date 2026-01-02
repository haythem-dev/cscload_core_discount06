#pragma once
#include "PageTabCtrlMultiLang.h"
#include "ppDataTypes.h"
#include "TabPageMultiLang.h"
#include "DOrderInformationDetails1.h"
#include "DOrderInformationDetails2.h"
#include "DOrderInformationDetails3.h"
#include "DOrderInformationDetails4.h"
#include "DOrderInformationDetails5.h"

class CDOrderInformation2;
class CDOrderInformationDetails1;
class CDOrderInformationDetails2;
class CDOrderInformationDetails3;
class CDOrderInformationDetails4;
class CDOrderInformationDetails5;


/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_LS_AMGE             0
#define COL_LS_BMGE             1
#define COL_LS_NRME             2
#define COL_LS_RMME             3
#define COL_LS_NLME             4
#define COL_LS_EINHEIT          5
#define COL_LS_ARTIKELNAME      6
#define COL_LS_DAF              7
#define COL_LS_PNR_VSE          8
#define COL_LS_PNR_CSC          9
#define COL_LS_PNR_LIEF         10
#define COL_LS_ARTICLECODE      11
#define COL_LS_PZN              12
#define COL_LS_INVOICE_PREIS    13
#define COL_LS_TAX_PCT          14
#define COL_LS_BASE_PREIS       15
#define COL_LS_LOGIST           16
#define COL_LS_MIN_LOGIST       17
#define COL_LS_REFERENCE        18
#define COL_LS_TYPE             19
#define COL_LS_COUNT            20
#define COL_LS_ANZ_LIST         21

// CDOrderInformation2 dialog

class CDOrderInformation2 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderInformation2)

public:
    CDOrderInformation2();
    virtual ~CDOrderInformation2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDER_INFORMATION2 };
#endif
    CPageTabCtrlMultiLang m_CTabCtrlOrderInformation2;
    long m_KndNr;
    short m_VzNr;
    CString Rech_Nr;
    long m_lDatumAuftrag;       // Datum des Auftrags
    bool m_bNoData;
    long m_ActDatum;            // aktuelles Datum
    short m_sBatchAdvice;       // Status Chargenbeleg
    BOOL m_init;

    CDOrderInformationDetails1 m_PageDOrderInformationDetails1;
    CDOrderInformationDetails2 m_PageDOrderInformationDetails2;
    CDOrderInformationDetails3 m_PageDOrderInformationDetails3;
    CDOrderInformationDetails4 m_PageDOrderInformationDetails4;
    CDOrderInformationDetails5 m_PageDOrderInformationDetails5;
    CListCtrl m_CListVat;
    CListCtrl m_CListLief;

    void AlterInvoice();

protected:
    void AusgPosListe();
    int AusgKopf();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual LPCTSTR GetTabTitle();
    virtual int GetID() { return IDD; }
    virtual BOOL OnSetActive();

    virtual BOOL OnInitDialog();
    afx_msg void OnNMClickListLieferpos(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnLvnItemchangedListLieferpos(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
};

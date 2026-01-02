#pragma once

// DInfAnzAuft.h : header file
//
#include "AufInflistctrl.h"
#include "DVbBuchen.h"

/////////////////////////////////////////////////////////////////////////////
// CDInfAnzAuft dialog
#include <vector>
using namespace std;

class CAufInfListCtrl;

class CDInfAnzAuft : public CDialogMultiLang
{
public:
    CDInfAnzAuft(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDInfAnzAuft();
    long m_AuftrNr;
    long m_LAuftNr;
    long m_TenderNo;
    long m_Datum;                           // Datum bei älteren Aufträgen
    bool m_bSelProforma;
    bool m_bNoOpen;
    long m_lDatumAuftrag;                   // Datum des Auftrags
    long m_lTour;                           // Tour des Auftrags
    bool m_bCall;

    CString m_cRechnr;
    CString m_cIVCnr;
    vector <AUFPOSBUCH> m_lAuf;
    CImageList m_ImageSmall;

    enum { IDD = IDD_AE_AUFT_ANZ };
    CButton m_CBNurDef;
    CListBox m_ListInvoice;
    CAufInfListCtrl* m_ListCtl;
    BOOL m_bNurDef;


protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void AusgKopf();
    void AusgPos();
    void ReadPos();
    void IfKopfOrFussZln();
    void GetArtKennz(long artikelnr, CString& ArtKZ, CString& ProdQuota);
    bool IsVbKunde();
    long m_KndNr;
    long m_IdfNr;
    long m_lEtartklasse1;
    short m_VzNr;
    short m_sFVRabkonto;                        // Kennz. Rabattkonto FV
    short m_sKKRabkonto;                        // Kennz. Rabattkonto KK
    bool m_bVbKunde;

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonKopfFuss();
    afx_msg void OnButtonKopfFuss2();
    afx_msg void OnButtonDruck();
    virtual void OnOK();
    afx_msg void OnCheckNurDef();
    afx_msg void OnButtonDruckLief();
    afx_msg void OnButtonVbBuch();
    afx_msg void OnButtonDefbuch();
    afx_msg void OnButtonSeralog();
    afx_msg void OnButtonAufNeu();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()

public:
    virtual BOOL DestroyWindow();
    afx_msg void OnLvnColumnclickListAuftrag(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonAufNeuAlle();
    afx_msg void OnBnClickedButtonAufCallback();
    afx_msg void OnBnClickedButtonCremaStorno();
    afx_msg void OnBnClickedButtonCremaClose();
    afx_msg void OnButtonCall();

private:
    void AddDeliveryDateTimeToList(int pos, vector<AUFPOSBUCH>::iterator& it);

    void InitVbArtikel(vector<CDVbBuchen::VbArtikel>& destlist, int pos, bool bUseAmgeAsBmge = false);
    void InitVbBuchenDlg(CDVbBuchen& dlgVbBuchen);
};

#pragma once
// daufdef.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAufDef dialog

#include <atltime.h>
#include "DAufDefImpl.h"

class CAeDoc;
class CMAufDef;


class CDAufDef : public CDialogMultiLang
{
private:
    enum TourType
    {
        Akt,    // IDC_COMBO_TOUR
        Sonder, // IDC_COMBO_TOUR_NAKT
        Futur,  // IDC_COMBO_FUTUR
        Mix     // IDC_COMBO_MIX
    };

private:
    CMAufDef& _model;

    long m_lAutoValuta;                 // Valutamonate auto
    short m_sValutaTage;                // Valutatage automatisch (KROATIEN)
    long m_lIVCInitial;                 // zuvor eingegebene IVC-Nummer
    CString m_OrgInvoice;               // Original-Rechnungs-Nummer
    CString m_OrgInvoice_old;           // zuvor eingegebene riginal-Rechnungs-Nummer
    CString m_saveTour;                 // voreingestellte Tour
    long m_lValutaInitial;              // alte Valuta
    long m_lActDatum;                   // akuelles Datum für verzögerte Auslieferung
    short m_sWeekday;                   // aktueller Wochentag
    CStringArray m_Tagtab;
    bool m_bSonder;                     // Set Sonder combobox if Mix combobox inactive
    bool m_bMixExist;
    bool m_bMixShown;                   // Mix combobox active?
    bool m_bAnzSonder;
    TourType m_TourType;                // Current tour combobox type
    CString m_AArtWished;               // neu eingestellte Auftragsart
    bool m_bCancel;                                     // Schalter ob Cancel moeglich
    bool m_bKommiArtManuell;                            // Schalter ob manuell KA geaendert
    CStringArray m_aAArten;                             // Auftragsarten
    bool m_bNoRabattKontoInitial;
    bool m_bCashOrderInitial;
    CStringArray m_aWochentouren;                       // Wochentouren
    boost::shared_ptr<CDAufDefImpl> _impl;
    bool m_bValutaWhenCheckCashOrder;

// Dialog Data
protected:
    enum { IDD = IDD_AE_DEF_ORDER };
    CEdit   m_EditBemerkung;
    CEdit   m_EditIVC;
    CEdit   m_EditOrgInvoice;
    CButton m_CheckValuta;
    CButton m_NoRebateAccount;
    CComboBox   m_CoboxTour;
    CSpinButtonCtrl m_CspinMonate;
    CStatic m_cs_ValutaMonate;
    CStatic m_cs_ValutaAuto;
    CStatic m_cs_ValutaDatum;
    CEdit   m_EditValuta;
    CComboBox   m_CoboxAufArt;
    BOOL m_bDelayedDelivery;
    CDateTimeCtrl m_DT_DelayedDelivery;
    CTime m_CT_DelayedDelivery;
    CComboBox m_CoboxNakt;
    CComboBox m_CoboxFutur;
    CStatic m_cs_SonderTour;
    CComboBox m_Cobox_SubOrder;
    CComboBox m_CoboxMix;
    CString m_IVC;
    CString m_ABemerkung;               // Auftragsbemerkung
    BOOL m_bNoRabattKonto;
    BOOL m_bCashOrder;

// Construction
public:
    CDAufDef(CMAufDef& model, CWnd* pParent = NULL);     // standard constructor

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void SetAuftArt();
    void SetBuchArt( char cBuchArt );
    void SetKommArt( char cKommArt );
    void ShowAkt();
    void ShowSonder();
    void ShowFutur();
    void ShowMix();

    void InitTourCombos(CString& AArt);
    void VersorgeTouren(CString &AArt, bool initial = false);
    void ReadWeektours(CString& AArt);
    void InitFuturCombo(short sWeekday);
    int  HoleSubOrder(CString &AArt);
    void SetTourCombo();
    void ShowAndSelectTourFutur();
    void SetValuta(int mon);
    CString TourToString(const CString& tour, long fahrzeit, char cKA, short sWeekday);   // Tour ins Ausgabeformat umwandeln
    void StringToTour(char* tour, const CString& formattedTour); // Ausgabeformat in Tour umwandeln
    void DisableCancel();
    void CalculateAndSetValutaDatum();

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnCheckValuta();
    afx_msg void OnChangeEditBemerkung();
    afx_msg void OnChangeEditIVC();
    afx_msg void OnChangeEditOrgInvoice();
    afx_msg void OnChangeEditValMon2();
    afx_msg void OnSelchangeComboAufArt();
    afx_msg void OnRadioKomArt();
    afx_msg void OnSelchangeComboTour();
    afx_msg void OnSelchangeComboSonder();
    afx_msg void OnSelchangeComboMix();
    afx_msg void OnDatechangeDelayedDelivery(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnCheckDelayedDelivery();
    afx_msg void OnBnClickedButtonSonder();
    afx_msg void OnCheckCashOrder();
    DECLARE_MESSAGE_MAP()

private:
    bool IsValutaPossible();
    void ShowAndEnableWindow(int nID1, int nID2, bool show);
    void ShowAndEnableWindow(int nID, bool show);
    bool SetFuturCurSel(CString weekday, int iChar);
    void GetCurrentValutaDate(long& year, long& month, long& day);
    void CalculateYearChange(long& year, long& month);
    bool GetTour(CComboBox& combo, CString& tour);
    CString FormatTour17(CString tour);
    void SetKommArt42(CString tour);
    bool ValutaInDays();
    CTime ConvertDate(long date, int addHours = 0);
    long ConvertDate(CTime cDate);
    void GetDate(const long date, long& year, long& month, long& day);
    long GetDate(const long year, const long month, const long day);
    void SetTourComboOnRadioKomArt();
    void SetTourComboOnDelayedDeliveryDate();
    void InitFuturComboOnDelayedDeliveryDate();
    void InitFuturComboForWholeWeek();

    void ShowAktAndResetSelection();
    int ShowSonderAndResetSelection();
    void ShowFuturAndResetSelection();
    void ShowMixAndResetSelection();
    bool ShowSonderOnEmptyAkt();

    void UpdateTourOnSonder();
    void UpdateTourOnMix();
    void UpdateOnChangeAufArt();
    void UpdateValuta(bool bValutaChecked);
    void EnableValutaControls(bool bValutaChecked);
    void UpdateTourComboOnDelayedDelivery();

    // Begin OnInitDialog
    void RememberInitialValues();
    void FillDayTable();
    void InitDate();
    void GetOrderTypes();
    bool IsBatch();
    void AddOrderType(AUFARTES& aufartes);
    void InitEilBeipackRadio();
    void InitSonderTourFont();
    // End OnInitDialog

    // Begin OnOK
    //
    // Begin WriteOrder
    bool WriteOrder(CAUFTRAG& auftrag);
    bool SetRemarks(AUFTRAG& auftrag);
    bool SetOrderType(AUFTRAG& auftrag);
    void SetCommiType(AUFTRAG& auftrag);
    void SetBookingType(AUFTRAG& auftrag);
    void SetSubOrderType(AUFTRAG& auftrag);
    void SetValuesOnChangeOrder(AUFTRAG& auftrag);
    // End WriteOrder

    bool WriteCashRebate(CAUFTRAG& auftrag);
    bool WriteOrderRemark(CAUFTRAG& auftrag);
    void WriteIVCVoucherNo(CAUFTRAG& auftrag);
    void WriteOriginalInvoiceNo(CAUFTRAG& auftrag);
    bool WriteValuta(CAUFTRAG& auftrag);
    long GetDatumValuta();
    void WriteDelayedDelivery(CAUFTRAG& auftrag);
    bool WriteTour(CAUFTRAG& auftrag);
    bool WriteCashOrder(CAUFTRAG& auftrag);
    // End OnOK
};

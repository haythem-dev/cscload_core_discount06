#pragma once
// aefview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAeFView form view
class CDCountDown;
class CDKritikAnz;
class CDVbBuchen;
class CDViewRabs;
class CDViewKnd;
class CDViewCstBranchInfo;

#include <artsel.h>

//Definition der Tabellenbreite und der Ueberschriften
#define COL_FVIEW_KB            0
#define COL_FVIEW_BESTAND       1
#define COL_FVIEW_EINHEIT       2
#define COL_FVIEW_ARTIKELNAME   3
#define COL_FVIEW_DAF           4
#define COL_FVIEW_PREIS         5
#define COL_FVIEW_KB2           6
#define COL_FVIEW_VERFALL       7
#define COL_FVIEW_KENNZEICHEN   8
#define COL_FVIEW_ARTICLE_CODE  9
#define COL_FVIEW_HERSTELL      10
#define COL_FVIEW_TEXT          11
#define COL_FVIEW_APOPFLICHT    12
#define COL_FVIEW_TEXTKEY       13
#define COL_FVIEW_OPIAT         14
#define COL_FVIEW_KKCODE        15
#define COL_FVIEW_PREISGR4      16
#define COL_FVIEW_TAXLEVEL      17
#define COL_FVIEW_LEER          18
#define COL_FVIEW_GROSSO        19
#define COL_FVIEW_CODE_TYPE     20
#define COL_FVIEW_PZN           21
#define COL_FVIEW_GROSSONA      22
#define COL_FVIEW_SUPPLINFO     23
#define COL_FVIEW_SUPPLPROG     24
#define COL_FVIEW_SUPPLLIEF     25
#define COL_FVIEW_PRODQUOTA     26
#define NUM_FVIEW_COLUMNS       27

#define COL_VB_FVIEW_VZ         0
#define COL_VB_FVIEW_VON1       1
#define COL_VB_FVIEW_BIS1       2
#define COL_VB_FVIEW_VON2       3
#define COL_VB_FVIEW_BIS2       4
#define NUM_VB_FVIEW_COLUMNS    5

 typedef struct RI_PROMOTIONEN {
         short PROMOTION_NO;
         long BASEQTY;
         double BASE_VALUE;
         char PHARMACYGROUPID[4];
         long DISCOUNTGRPNO;
         long CUSTOMERNO;
        } promostruct;

class CAeFView : public CFormViewMultiLang, CPageBrowser
{
protected:
    afx_msg void OnContextMenu(CWnd*, CPoint point);
    afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnReNew(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnGoodbyeRab(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnGoodbyeBInfo(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnGoodbyeBKritik(WPARAM wParam, LPARAM lParam);

    DECLARE_DYNCREATE(CAeFView)

private:
    CDCountDown* m_pDlgDown;

// Form Data
//  CToolTipCtrl m_tooltip;
public:
    CAeFView();

    enum { IDD = IDR_MAINFRAME };
    CStatic m_cs_Tel;
    CStatic m_cs_Rabattwert;
    CStatic m_cs_Rabattwert2;
    CEdit   m_EditNormPackung;
    CComboBox   m_ComboBuchStat;
    CEdit   m_EditZusatz;
    CEdit   m_EditPackGr;
    CEdit   m_EditNatRab;
    CEdit   m_EditMenge;
    CEdit   m_EditDarr;
    CEdit   m_EditMatchCode;
    CEdit   m_EditBemerkung;
    CEdit   m_EditArtNr;
    CEdit   m_EditHC;
    CListCtrl   m_ListCtl;
    CString m_CArtNr;
    CString m_CMenge;
    CString m_CDarr;
    CString m_CMatchCode;
    CString m_CBemerkung;
    CString m_CNatRab;
    CString m_CZusatz;
    CString m_CPackGr;
    CString m_CHC;
    int     m_BuchStat;
    CString m_CKndText;
    CString m_CNormPackung;
    CString m_CTel;
    CString m_CPreis;
    CEdit   m_EditPreis;
    CComboBox   m_CoboxFreePrice;
    CImageList m_ImageSmall;
    CStatic m_cs_VZ;
    CComboBox   m_ComboTyp;
    CListCtrl   m_List_VB;
    CString     m_PaymentType;      // Zahlungsart des Auftrags
    long    m_IVC;                  // IVC-Nummer
    short       m_iImport;          //Kennz. für Importartikel

// Attributes
public:
    double m_dCstDiscount;
    CDKritikAnz* m_pDlgKritik;
    CDViewKnd* m_pDlgKnd;
    CDViewRabs* m_pDlgRab;
    CDViewCstBranchInfo* m_pDlgBranchInfo;

// members
public:
    int m_iAnzPromo;                //Anzahl vorhandener Promotionen im Auftrag

    vector<promostruct> *m_plPromo; // pointer to class list
    vector <promostruct>::iterator m_itPromo;

// Operations
public:
    void SaveListColumns();
    void ChangeColumnText();                            // Aendern Ueberschrift in Textspalte
    BOOL NewOrder(long KndNr,short VZ); //öffnet einen neuen Auftrag anhand einer Kundennummer
    BOOL OpenOrder(long AuftrNr);   //vorhandenen Auftrag öffnen
    BOOL AuftragSave();
    BOOL OpenParaOrder(long KundenNr = -1,short VzNr = 0);
    void ResetTimeCount()   { m_TimeCount = 0; }    //wenn etwas eingegeben wird Zaehler wieder auf 0 setzen
    void ResetContent();    //loeschen Eingabe
    void FillFreePrice(long lArtikel_nr,CString &Aep);  //Fuellen Combo mit alten Preisen
    BOOL IsDigit(CString Caption);  //überpüfen String numersich
    bool CheckKontigent(long lArtikelnr, long& lBestand, long& lRest);    //Überprüfen vorhandene Kontigentierung
    void SetOrgFilNr(const short sVz) { m_OrgFilNr = sVz;   }
    short GetOrgFilNr() { return m_OrgFilNr;    }
    long GetDefekte() { return m_lAnzDefekt; }
    long GetTenderno() { return m_lTenderNo; }
    void SetTenderno(const long TenderNo) { m_lTenderNo = TenderNo; }
    short GetServType() { return m_sServType; }
    void SetTimerTour(long tourtime);   //Setzen Timer fuer Tourabschlusswarnung
    void ShowTourCountdown(long contdowntime,const UINT id);    //Aktivieren countdown-View
    void OnABKArtDef(BOOL bAendErzwingen = FALSE, BOOL bBemerkungEingeben = FALSE, BOOL bPseudoGebucht = FALSE, BOOL bShowCashOrder = TRUE);    //Aenderung Auftrags-, Kommi- und Buchungsart

    void ShowKritikView();
    void ShowBranchView();
    void DeleteKritikView();
    void DeleteBranchView();

    const long& GetKdauftragNr() const { return m_lKdauftragNr; }
    const long& GetKundenNr() const { return    m_KndNr; }

    void CAeFView::AusgAufWerte     //Ausgabe der Auftragswerte
    (
        long    AnzPos      = 0,
        double  WertAuftr   = 0.0,
        double  WertLif     = 0.0,
        double  WertZln     = 0.0,
        double  dBalance    = 0.0,
        double  dBalance2   = 0.0,
        double  dRechwert   = 0.0,
        double  dRechwertRab = 0.0
    );

    void CAeFView::AusgAufWerteBG       //Ausgabe der Auftragswerte
    (
        double  dWertNettoFV    = 0.0,
        double  dWertTaxFV      = 0.0,
        double  dWertNettoKK    = 0.0,
        double  dWertTaxKK      = 0.0,
        double  dWertNettoEH    = 0.0,
        double  dWertTaxEH      = 0.0,
        double  dWertExclusive  = 0.0
    );

protected:
    long m_lKdauftragNr;

protected:
    virtual ~CAeFView();
    void AusgAufKopf        //Ausgabe der Kopfinformationen
    (
        long    KndNr,
        long    AufNr       = 0,
        long    AnzPos      = 0,
        double  WertAuftr   = 0.0,
        double  WertLif     = 0.0,
        double  WertZln     = 0.0,
        double  dBalance    = 0.0,
        double  dBalance2   = 0.0,
        double  dRechwert   = 0.0,
        double  dRechwertRab = 0.0
    );

    void CAeFView::AusgAKBArt
    (
        CString AArt = "NO",
        CString BArt = "0",
        CString KArt = "0",
        CString SubOrder = "",
        double dBalance = 0.0,
        double dBalance2 = 0.0
    );

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);    // List-Box mit Eintraegen versorgen
    void        SetPrices( );                               // List-Box mit Preisen nach Preistyp versorgen
    void        CloseCursor();                              // DB-Cursor schliessen
    long        SelListPos(CString& ArtName, CString& ArtEinh, CString& Kz, CString& Darr, CString& AEP, CString& TAX, CString& TEXTKEY, CString& Opi, CString& KKCode, CString& Einzelhandel, CString& Bestand, CString& Taxlevel, CString& Grosso, CString& Codetype, CString& Artcode, CString& GrossoNA, CString& ProdQuota);// ArtikelNr des ausgewählten Art. best.
    void        BucheListPos();                             // Ermittlung der markierten Artikelnummer
    void        SelectArtikelNr(CString ArtNr);             // Kontrlolle gültige Artikelnummer
    void        AusgListPos(CARTAESEL & artaesel, char *kb);// Ausgabe einer Listboxzeile
    void        AusgTour();                                 // Tour formatiert ausgeben
    void        PosBuchen(CString ArtName,
                            CString ArtEinh,
                            CString Kz,
                            CString Darr,
                            CString AEP,
                            CString TAX,
                            CString TEXTKEY,
                            CString Opi,
                            CString KKCode,
                            CString Einzelhandel,
                            CString Charge,
                            CString Grosso,
                            CString Codetype,
                            CString Artcode,
                            CString FixBatch
                            );// Buchung einer Position
    void        ArtAnschrAusg(CString Menge,CString ArtName, CString ArtEinh, CString ArtDarr); //Artikel anschreiben protokollieren
    void        ArtAnschreiben(long Menge,CString ArtName, CString ArtEinh, CString ArtDarr);   //Artikel anschreiben
    void        GetArtKennz(ARTAESEL* artaesel, CString& ArtKZ); // Liefert das für die Ausgabe erf. Artikelkennzeichen
    void        InitOrderHead(CAUFTRAG & auftrag, BOOL bNewOrder = FALSE); //Init head and members
    void        ClearView();                                // Löschen der Feldinhalte und Listbox
    void        ClearInput();                               // Löschen der Eingabefelder
    void        UpdateLieferbereitschaft(long bestand);     // Eintrag auf ohne Bestand setzen
    void        MarkListPos(int pos);                       // Markiert eine  Position
    void        InitOrder();                                // Initialisierung bei Öffnung eines Auftrags
    void        FillPosList();                              // Fuellen der Positionsliste
    void        InitVerbundMoegl();                         // Verbund moeglich anzeigen
    int         m_nFunktion;                                // Funktion, mit der selektiert wird
    BOOL        m_bBuchungErfolgt;                          // verhindert das Vergessen von Buchungen
    BOOL        m_bIgnore;                                  // trotz Preislimitüberschreitung buchen BG
    long        m_KndNr;                                    // Nr des aktuellen Kunden
    long        m_IdfNr;                                    // IDF-Nr des aktuellen Kunden
    long        m_ArtNr;                                    // zu buchender Artikel
    long        m_ArtNrAlt;                                 // zuletzt gebuchter Artikel
    long        m_Menge;                                    // Menge
    long        m_NatRab;                                   // Naturalrabatt
    long        m_NatRabBestellt;                           // Naturalrabatt bestellt
    long        m_PosStat;                                  // Positionsstatus (zugesagt, dispo...)
    long        m_Valuta;                                   // Valutamonate
    long        m_lDatumValuta;                             // Valutadatum
    long        m_lBatchschreiben;
    CString     m_cZuGrund;                                 // Rückstellgründe
    CString     m_ABemerkung;                               // Auftragsbemerkung
    CString     m_Tour;                                     // aktuelle Tour
    long        m_lDeliveryDate;                            // Lieferdatum
    int         m_iDefNachPos;                              // aktuelle Position in der Defektnachbearbeitungsliste
    BOOL        m_bDefSelVerbund;       // Defektanzeige Auswahlschalter Verbundartikel
    BOOL        m_bDefSelDfDef;                             // Defektanzeige Auswahlschalter
    BOOL        m_bDefSelPhonDef;                           // Defektanzeige Auswahlschalter
    BOOL        m_bDefSelDfFrText;                          // Defektanzeige Auswahlschalter
    BOOL        m_bDefSelPhonFrText;                        // Defektanzeige Auswahlschalter
    bool        m_bPara;                                    // Auftrag mit PARA-Positionen
    bool        m_bKndSchwerpunk3;                          // Arbeitskreis aktuell
    bool        m_bKndSchwerpunk5;                          // Diabetes
    bool        m_bKndMussKopfBem;                          // Auftragskopfbemerkung erzwingen
    CString     m_KStdAufArt;                               // Standartauftragsart des Kunden
    CString     m_KStdKoArt;                                // Standartkommiart des Kunden
    CString     m_KStdBuArt;                                // Standartbuchungsart des Kunden
    bool        m_bDafueKz;                                 // Kennz. Dafue-defekte abarbeiten
    bool        m_bDefekte;                                 // Kennz. Dafue-defekte vorhanden
    bool        m_bKz_Verbund_Moegl;                        // Kennz. Verbund moeglich anzeigen
    bool        m_bKz_Kunde_Verbund;                        // Kennz. Kunde kann Verbund
    short       m_VzNr;                                     // Nr des aktuellen VZ des Kunden
    BOOL        m_bKz_Nur_Liefber;                          // Kennz. nur nicht defekt anzeigen
    long        m_TimeCount;                                // Zaehler fuer Timerdurchlaeufe
    long        m_lDatumDD;                                 // Datum verzögerte Auslieferung
    short       m_OrgFilNr;                                 // Nr der Stamm-Filiale des Kunden
    BOOL        m_lNoDoubleArtNr;                           // Kennz. nicht prüfen bereits eingegeben
    long        m_lAnzDefekt;                               // Anzahl Defektzeilen im Auftrag
    long        m_lTenderNo;                                // Tendernummer bei Tenderauftrag
    long        m_lResttime;                                // verbleibende Zeit vor Tour
    long        m_lWake1;                                   // Weckzeit1 vor Tour
    long        m_lWake2;                                   // Weckzeit2 vor Tour
    long        m_lDatumBTM;                                // Datum BTM
    CString     m_CBTMLicense;                              // BTM Formular-Nr.
    short       m_sServType;                                // Servicetype Nummer
    short       m_sFVRabkonto;                              // Kennz. Rabattkonto FV
    short       m_sKKRabkonto;                              // Kennz. Rabattkonto KK
    BOOL        m_bNoRabattKonto;                           // Kunde will ohne Rabattkonto
    BOOL        m_bNoMorePos;                               // Keine Eingabe weiterer Positionen erlaubt
    long        m_lActDatum;                                // aktuelles Datum

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual void OnInitialUpdate();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnKeydownListctrlArt(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKundeOffeneAuftrge();
    afx_msg void OnUpdateKundeOffeneAuftrge(CCmdUI* pCmdUI);
    afx_msg void OnKundeAnrufen();
    afx_msg void OnUpdateKundeAnrufen(CCmdUI* pCmdUI);
    afx_msg void OnAuftrDef();
    afx_msg void OnUpdateAuftrDef(CCmdUI* pCmdUI);
    afx_msg void OnInfArt();
    afx_msg void OnUpdateInfArt(CCmdUI* pCmdUI);
    afx_msg void OnUpdateAuftrBearb(CCmdUI* pCmdUI);
    afx_msg void OnInfKunde();
    afx_msg void OnUpdateInfKunde(CCmdUI* pCmdUI);
    afx_msg void OnAufFreitext();
    afx_msg void OnUpdateAufFreitext(CCmdUI* pCmdUI);
    afx_msg void OnAuftragSave();
    afx_msg void OnUpdateAuftragSave(CCmdUI* pCmdUI);
    afx_msg void OnOk();
    afx_msg void OnPrior();
    afx_msg void OnNext();
    afx_msg void OnChangeEditArtnr();
    afx_msg void OnChangeEditBemerkung();
    afx_msg void OnChangeEditBezei();
    afx_msg void OnChangeEditDarreichung();
    afx_msg void OnChangeEditMenge();
    afx_msg void OnChangeEditNatrab();
    afx_msg void OnChangeEditPackGr();
    afx_msg void OnChangeEditZusatz();
    afx_msg void OnKundeKndWahl();
    afx_msg void OnUpdateKundeKndWahl(CCmdUI* pCmdUI);
    afx_msg void OnDblclkListctrlArt(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnInfAuf();
    afx_msg void OnAeKopfFuss();
    afx_msg void OnUpdateAeKopfFuss(CCmdUI* pCmdUI);
    afx_msg void OnBearbDefnachbea();
    afx_msg void OnUpdateBearbDefnachbea(CCmdUI* pCmdUI);
    afx_msg void OnAuftragDafzurckgestellteauftrge();
    afx_msg void OnUpdateAuftragDafzurckgestellteauftrge(CCmdUI* pCmdUI);
    afx_msg void OnInformationenAuftragsereignisse();
    afx_msg void OnUpdateInformationenAuftragsereignisse(CCmdUI* pCmdUI);
    afx_msg void OnInformationenInfoliste();
    afx_msg void OnUpdateInformationenInfoliste(CCmdUI* pCmdUI);
    afx_msg void OnInformationenKundenkontakte();
    afx_msg void OnUpdateInformationenKundenkontakte(CCmdUI* pCmdUI);
    afx_msg void OnChangeEditNormpackung();
    afx_msg void OnKundeKundeAusPlan();
    afx_msg void OnUpdateKundeKundeAusPlan(CCmdUI* pCmdUI);
    afx_msg void OnUpdateInfAuf(CCmdUI* pCmdUI);
    afx_msg void OnInformationenTagesanrufplan();
    afx_msg void OnUpdateInformationenTagesanrufplan(CCmdUI* pCmdUI);
    afx_msg void OnBearbeitenDafuepositionenlschen();
    afx_msg void OnUpdateBearbeitenDafuepositionenlschen(CCmdUI* pCmdUI);
    afx_msg void OnVerwaltungStandardauftragsart();
    afx_msg void OnUpdateVerwaltungStandardauftragsart(CCmdUI* pCmdUI);
    afx_msg void OnBearbeitenKundenndern();
    afx_msg void OnUpdateBearbeitenKundenndern(CCmdUI* pCmdUI);
    afx_msg void OnBearbeitenNachlieferpositionen();
    afx_msg void OnUpdateBearbeitenNachlieferpositionen(CCmdUI* pCmdUI);
    afx_msg void OnProtNachlifbearb();
    afx_msg void OnUpdateProtNachlifbearb(CCmdUI* pCmdUI);
    afx_msg void OnExtrasVerbundZeigen();
    afx_msg void OnUpdateExtrasVerbundZeigen(CCmdUI* pCmdUI);
    afx_msg void OnInformationenCallback();
    afx_msg void OnUpdateInformationenCallback(CCmdUI* pCmdUI);
    afx_msg void OnInformationenCallbackDo();
    afx_msg void OnUpdateInformationenCallbackDo(CCmdUI* pCmdUI);
    afx_msg void OnAuftragVerbund();
    afx_msg void OnUpdateAuftragVerbund(CCmdUI* pCmdUI);
    afx_msg void OnAuftragDefekte();
    afx_msg void OnUpdateAuftragDefekte(CCmdUI* pCmdUI);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnExtrasNichtDefekt();
    afx_msg void OnUpdateExtrasNichtDefekt(CCmdUI* pCmdUI);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnHipathCall();
    afx_msg void OnUpdateHipathCall(CCmdUI* pCmdUI);
    virtual void OnCancel();
    DECLARE_MESSAGE_MAP()
public:
    void OnAuftrBearbCode(CString ArtCode);
    afx_msg void OnAuftrBearb();
    afx_msg void OnEnChangeEditHc();
    afx_msg void OnInformationenUmsatz();
    afx_msg void OnUpdateInformationenUmsatz(CCmdUI *pCmdUI);
    afx_msg void OnHipathInsTelnr();
    afx_msg void OnUpdateHipathInsTelnr(CCmdUI *pCmdUI);
    afx_msg void OnPflegeTelefonnr();
    afx_msg void OnUpdatePflegeTelefonnr(CCmdUI *pCmdUI);
    afx_msg void OnEnChangeEditPreis();
    afx_msg void OnNMClickListctrlArt(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnPflegeDdEinzel();
    afx_msg void OnBearbeitenWirkstoff();
    afx_msg void OnUpdateBearbeitenWirkstoff(CCmdUI* pCmdUI);
    afx_msg void OnBearbOccasion();
    afx_msg void OnUpdateBearbOccasion(CCmdUI* pCmdUI);
    afx_msg void OnAuftragWerte();
    afx_msg void OnUpdateAuftragWerte(CCmdUI* pCmdUI);
    afx_msg void OnBTMLicense();
    afx_msg void OnUpdateBTMLicense(CCmdUI* pCmdUI);
    afx_msg LRESULT OnGoodbyeDown(WPARAM wParam, LPARAM lParam);
    afx_msg void OnCbnSelchangeComboTyp();
    afx_msg void OnPromotionen();
    afx_msg void OnUpdatePromotionen(CCmdUI* pCmdUI);
    afx_msg void OnBearbRabDefs();
    afx_msg void OnBearbBulgaria(CString cZuGrund);
    afx_msg void OnInformationenRange();
    afx_msg void OnUpdateInformationenRange(CCmdUI *pCmdUI);
    afx_msg void OnMenu33049();
    afx_msg void OnUpdateMenu33049(CCmdUI *pCmdUI);
    afx_msg void OnAuftragNlBearb();
    afx_msg void OnUpdateAuftragNlBearb(CCmdUI *pCmdUI);
    afx_msg void OnBnClickedRadioImport();
    afx_msg void OnViewNoCritics();
    afx_msg void OnUpdateViewNoCritics(CCmdUI *pCmdUI);
    afx_msg void OnViewNoBranchinfo();
    afx_msg void OnUpdateViewNoBranchinfo(CCmdUI *pCmdUI);
    afx_msg LRESULT OnPhoneRing2(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnPhoneConsult(WPARAM wParam, LPARAM lParam);

private:
    void UpdateLieferbereitschaft(long lBestand, const CString& cBestand, int posListCtl, bool bCheckVerbund);
    int GetLieferbereitschaft(long& lBestand, long larticleno, bool bCheckVerbund);

    void BucheListPosBG(CString csArtName, CString csAEP, CString csOpi, CString csKKCode, CString csEinzelhandel,
        CString csBestand, CString csTaxlevel, CString csCharge, CString csGrossoNA, CString csFixBatch);

    short GetPriceTypeFromCB();

    void SetTextWithFocusNoSelection(CEdit& edit, char c);
    void SetTextWithFocusNoSelection(CEdit& edit, const CString& str);
    void SetFocusNoSelection(CEdit& edit);
    void SetFocusFullSelection(CEdit& edit);

    void InitVbBuchenDlg(CDVbBuchen& dlgVbBuchen);
};

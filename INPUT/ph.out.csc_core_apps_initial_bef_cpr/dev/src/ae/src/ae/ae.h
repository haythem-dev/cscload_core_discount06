#pragma once
// ae.h : main header file for the AE application
//

#include "AeDoc.h"
#include "AeUser.h"
#include "aaclasses.h"
#include <auftragsart.h>
#include "AE_i.h"
#include "ProCenter.h"
#include "AeTrace.h"
#include "AeLogging.h"
#include <statistics.h>
#include "Country.h"
#include "OrderType.h"
#include "AeAppPresenter.h"
#include "AeAppProperty.h"

typedef PropTemp<HWND> HWNDProp;

/////////////////////////////////////////////////////////////////////////////
// CAeApp:
// See ae.cpp for the implementation of this class
//
#define WM_GOODBYE      WM_USER + 5
#define WM_GOODBYEMAIL  WM_USER + 6
#define WM_KILLTIMER    WM_USER + 7
#define WM_ACTTIMER     WM_USER + 8
#define WM_PHONERING    WM_USER + 10
#define WM_RENEW        WM_USER + 12
#define WM_HIPATHUSER   WM_USER + 14
#define WM_CONSULT      WM_USER + 15
#define WM_GOODBYEDOWN  WM_USER + 16
#define WM_GOODBYERAB   WM_USER + 17
#define WM_GOODBYEKND   WM_USER + 18
#define WM_SETITEM      WM_USER + 19
#define WM_SETITEM2     WM_USER + 20
#define WM_CALCRO       WM_USER + 21
#define WM_CLOSE_SERVICE    WM_USER + 22
#define WM_SETSUCH      WM_USER + 23
#define WM_GOODBYEBINFO WM_USER + 24
#define WM_GOODBYEBKRITIK   WM_USER + 25

#define KEY_ALT     18
#define KEY_AE      222
#define KEY_A       'A'
#define KEY_E       'E'
#define KEY_K       'K'
#define KEY_L       'L'
#define KEY_N       'N'
#define KEY_R       'R'
#define KEY_S       'S'
#define KEY_U       'U'
#define KEY_W       'W'

#define VIEW_LEER   0
#define VIEW_EING   1
#define VIEW_BEARB  2
#define MAXIMUM_IDF             9999999
#define MAXIMUM_RECHNUNGS_NR    9999999999
#define MAXIMUM_LENG_RECHNUNGS_NR   10
#define MAXIMUM_ART_NR          9999999
#define MAXIMUM_AUFTRAG_NR      9999999
#define MAXIMUM_BUCH_MENGE      9999
#define MAXIMUM_NR_MENGE        99999
#define MAXIMUM_ANZ_POS         99999
#define MAXIMUM_POS_BEM         30
#define MAXIMUM_AUFT_BEM        240
#define MAXIMUM_MON_VALUTA      12
#define MAXIMUM_ANZ_TOUR        6
#define MAXIMUM_KOMMIARTTYP     99
#define MAXIMUM_FILIALNR        99
#define MAXIMUM_HOUR            23
#define MAXIMUM_MIN             60
#define MAXIMUM_END_ZEIT        2400
#define MAXIMUM_ZEIT            9999
#define MAXIMUM_FILIALE         99
#define WARN_BUCH_MENGE         999
#define MAXIMUM_ZUSAMMENZEIT    360
#define MAXIMUM_PREIS_STELLEN   9
#define MAXIMUM_NACHKOMMA       2

//--- prekompiler-anweisung -------------------------------------------------//
class ppTime;
class ppDate;
class ppCallPlanParameter;

class CAeApp : public CWinAppMultiLang
{
public:
    AeApp::ShortProp VzNr;                  //aktuelles VZ

    BoolProp IsCool20;                      //auch Kuehlartikel unter 20 Grad anzeigen
    BoolProp IsNoParaCall;                  //keine Para-Rufe
    BoolProp IsFastOpenOrder;               //Zurückgestellten Auftrag sofort (ohne Auswahl) öffnen
    BoolProp IsAnrufPlan;                   //Arbeitsplatz arbeitet Anrufplan ab
    BoolProp IsAnrufPlanEigen;              //Arbeitsplatz arbeitet nur eigenen Anrufplan ab
    BoolProp IsStdAKBArt;
    BoolProp IsAutoBuchungNachlieferung;    //Automatische Buchung von Nachlieferpositionen
    BoolProp IsKundeIDF;                    //Kundeeingabe über IDF
    BoolProp IsKundeHome;                   //nur Kunden aus eigenem VZ
    BoolProp IsBTMextra;                    //keine BTMs
    BoolProp IsKundeKeineBTM;               //Kunde bekommt keine BTMs
    BoolProp IsRRMeld;                      //offene Rückrufe melden
    BoolProp IsRRNotDone;                   //überfälige Rückrufe melden
    BoolProp IsNoBeep;                      //kein Signal in Statusmaske
    BoolProp IsPosZusammen;                 //Gleiche Positionen kummulieren
    BoolProp IsOffAufMeld;                  //Nicht melden Auftrag offen
    BoolProp IsAuswahlKurz;                 //automatisches Verkuerzen Artikelanschreiben
    BoolProp IsAnzeigeAlle;                 //Anzeigen alle Positionen
    BoolProp IsAnzeigeAlleDef;              //Anzeigen alle Defekte
    BoolProp IsMailVzEigen;                 //Mail nur eigenes VZ
    BoolProp IsSofort;                      //Sofort abschliessen in F4-Maske bei MD setzen
    BoolProp IsExitPostProcEnabled;         //Nachbeabeiten ende erlaubt
    BoolProp IsMatchCode;
    BoolProp IsBackrouting;                 //Backrouting gewünscht
    BoolProp IsAlleVz;                      //alle Aufträge aus der Region anzeigen
    BoolProp IsNurDafue;                    //Nur Dafue zurückgestellte Aufträge
    BoolProp IsKndDD;                       //Kunde hat verzögerte Auslieferung
    AeApp::BoolProp IsDayNight;             //Tag-/Nachthaus aktiv
    BoolProp IsNewDiscount;                 //Neue Rabatte aktiv
    BoolProp IsNoValuta;                    //keine Eingabe von Valuta erlaubt
    BoolProp IsKumPos;                      //Kumulieren gleiche PZNs
    BoolProp IsPrintCode;                   //Anzeigen Printcode lt. codeblocage
    AeApp::BoolProp IsKLClose;              //Abschliessen Auftraege mit Kreditlimit
    BoolProp IsAnzRabatte;                  //Anzeigen Rabatte statt Artikeltext
    BoolProp IsNoVA10;                      //Übergehen VA10 nach Auftragsabschluss
    BoolProp IsKndKasse;                    //Kunde fuer Krankenkassenauftraege zugelassen
    BoolProp IsKndRetail;                   //Kunde fuer Einzelhandelsauftraege zugelassen
    BoolProp IsTOOpen;                      //Tender-Auftrag offen
    BoolProp IsTOStaat;                     //Staats-Tender
    AeApp::BoolProp IsNewFax;               //Neuer Faxserver
    AeApp::BoolProp IsNewSuivra;            //New Suivra
    BoolProp IsReOpen;                      //Kein neuer Auftrag
    BoolProp IsNurAktF11;                   //Nur aktive Artikel in F11
    BoolProp IsNoBatch;                     //Keine Batch-Auftraege anzeigen
    BoolProp IsSchrift;                     //Schriftvergrösserung in F9 und F2
    BoolProp IsNoPromo;                     //Kein Promofenster anzeigen
    BoolProp IsNoKippzeit;                  //keine Meldung Kippzeit ueberschritten
    BoolProp IsFirstLetter;                 //Infoliste ab 1. Zeichen
    AeApp::BoolProp IsCrema;                //mit neuem Kreditmanagement
    BoolProp IsNatraEingabe;                //Auftrag erlaubt Natraeingabe
    BoolProp IsAuftNoPromo;                 //Auftrag ohne Standardrabatte
    BoolProp IsMSV3;                        //Auftrag ist MSV3-Auftrag
    BoolProp IsCMI;                         //Auftrag ist CMI-Auftrag
    BoolProp IsNoNewLines;                  //keine neuen Positionen erlaubt
    AeApp::BoolProp IsCollOrders;           //mit CollectivOrders
    AeApp::BoolProp IsLogging;              //mit Logging Procenteraufrufe
    BoolProp IsIBTdirect;                   //Direktabschluss Verbund
    BoolProp IsGiveProdQuota;               //Kunde darf Herstellekontingent beziehen
    BoolProp IsNewCallback;                 //Neue Rückrufmaske mit eMail-Versand
    AeApp::BoolProp IsNewCallbackHome;      //Neue Rückrufmaske mit eMail-Versand eigenes VZ
    BoolProp IsNoChangeCustomer;            //Kunde aendern nicht erlaubt
    AeApp::BoolProp IsNLevelIBT;            //N-Level Verbund
    BoolProp IsStopCrema;                   //Crema in der Filiale des aktuellen Kunden gestoppt
    BoolProp IsNLevelIBTCst;                //N-Level Verbund in der Filiale des Kunden
    BoolProp IsNlSofort;                    //NL-Bearbeitung sobald Auftrag zurückgestellt ist
    BoolProp IsDispoSofort;                 //Dispo-Bearbeitung sobald Auftrag zurückgestellt ist
    AeApp::BoolProp IsNewF6;                //Neue F6-Maske
    BoolProp IsKommaNoTab;                  //Komma nicht als Tab
    BoolProp IsOTfixBatch;                  //Auftragsart mit Fixer Charge
    BoolProp IsOTwishBatch;                 //Auftragsart mit Wunsch Charge
    BoolProp IsOTforbiduserchangeBatch;     //Auftragsart Charge nicht aenderbar von User
    AeApp::BoolProp IsDispoImport;          //Filiale mit Importartikel-Bearbeitung
    BoolProp IsDispoImportCst;              //Filiale des Kunden mit Importartikel-Bearbeitung
    BoolProp IsShowCritics;                 //Nicht Anzeigen Kritiksätze
    BoolProp IsShowBranchInfo;              //Nicht Anzeigen Filialinformation
    AeApp::BoolProp IsConcernWording;       // concern (Anliegen) or callback (Rueckruf)
    AeApp::BoolProp UseSapReferenceNo;

    AeApp::CStringProp VzOrt;
    AeApp::CStringProp VzTelnr;
    AeApp::CStringProp VzFaxnr;
    AeApp::CStringProp VzPLZ;
    AeApp::CStringProp VzStrasse;
    AeApp::CStringProp Region;              //Name der Region des KSCs
    IntProp            OrderSort;           //Sortierung bei Ausgabe offene Auftraege setzen
    CStringProp        StdAuftArt;
    CStringProp        StdKommArt;
    CStringProp        StdBuchArt;
    ShortProp          FilialNr;            //Nr. der akt. Filiale
    AeApp::ShortProp   FilialNrActual;      //aktuelle Filiale für den Auftrag
    AeApp::CStringProp FilialName;          //Name der Filiale
    AeApp::CStringProp Vorwahl;
    AeApp::LongProp    BGANR_EK;            //BGA-Nummer fuer Verbund
    LongProp           TimeNoBTM;           //Zeit ab wann keine BTM mehr
    AeApp::ShortProp   LagerortLen;         //Länge des anzudruckenden Lagerorts
    ShortProp          VzNr_Kunde;          //aktuelles VZ des Kunden
    CStringProp        SelectedAArt;        //in F9-Maske selectierte Auftragsart
    LongProp           DurchlaufZeit;       //Lagerdurchlaufzeit
    LongProp           Verspaetung;         //Tourverspaetung
    IntProp            AnzKopfFuss;         //Anzahl vorhandene Kopf-/Fusszeilen
    CStringProp        TelNr;               //Telefonnr. Reinruf
    CStringProp        ApothekeName;        //Apothekenname des reinrufenden Kunden
    CStringProp        Ort;                 //dito Ort
    CStringProp        ProCenterName;
    CStringProp        ProCenterLocation;
    CStringProp        Balance1;
    CStringProp        Balance2;
    LongProp           PortNr;              //verkürzte Portnr z.B. 6000 aus KSC.INI
    CStringProp        Language;            //ausgewählte Sprache
    CStringProp        Caption;             //Catption von Hicom
    ShortProp          PoolNr;              //Poolnummer
    LongProp           ZeitDD;              //Zeit letzte Tour ohne verzögerte Auslieferung
    CStringProp        Geraet;              //ausgewähltes Terminal in F9
    LongProp           MaxPosEil;           //Maximale Anzahl Postitionen für Eilauftrag
    LongProp           PosZu;               //Anzahl Postitionen ab dem Auftrag zurückgestellt wird
    AeApp::CStringProp FaxAdresse;          //Share fuer Faxausgabe
    AeApp::CStringProp FaxLand;             //Landesvorwahl fuer Faxausgabe
    DoubleProp         PriceRange;          //Prozentuale Abweichung vom AE bei freier Preiseingabe
    CStringProp        ActEKGrp;            //EK-Gruppe des ausgewaehlten Subordertype
    IntProp            Modus;               //Modus für Umwandlung Umlaute
    AeApp::CharProp    Letter_A;            //erster Buchstabe im Alphabeth Grossbuchstabe
    AeApp::CharProp    Letter_Z;            //letzter Buchstabe im Alphabeth Grossbuchstabe
    AeApp::CharProp    Letter_a;            //erster Buchstabe im Alphabeth Kleinbuchstabe
    AeApp::CharProp    Letter_z;            //letzter Buchstabe im Alphabeth Kleinbuchstabe
    ShortProp          Wake1;
    ShortProp          Wake2;
    CStringProp        KzSprache;           //Sprachkennzeichen des Kunden
    LongProp           MainCstNo;           //Kettennr bei Rabattkonto
    ShortProp          Rebatemethfreesale;  //Rabattkonto FV
    ShortProp          Rebatemethhealthf;   //Rabattkonto KK
    LongProp           RODateFrom;          //Rabattauftrag Von-Datum
    LongProp           KndKlasse1;          //etartklasse1 des Kunden
    LongProp           KndGruppe;           //Preistypen der Kundengruppe
    AeApp::CStringProp FaxUser;             //Username für Samba-share Faxausgabe
    AeApp::CStringProp FaxPWD;              //Pwd für Samba-share Faxausgabe
    LongProp           ProAufnr;            //Auftragnr des Proformaauftrags
    LongProp           ProDatum;            //Datum des Proformaauftrags
    LongProp           RequeueCount;        //Nummer des Anrufs aus Procenter
    AeApp::ShortProp   UseTourManager;      //Neue Tourlogik
    ShortProp          UseTourManagerCst;   //Neue Tourlogik in der Filiale des Kunden
    ShortProp          ProcenterBranchno;   //Filialnr der Filiale der NST
    DoubleProp         FixZuschlag;         //fixer Zuschlag bei Taxspannenberechnung
    DoubleProp         ProzentZuschlag;     //prozentualer Zuschlag bei Taxspannenberechnung
    DoubleProp         Begrenzung;          //Maximaler Wert des prozentualen Zuschlags bei Taxspannenberechnung
    AeApp::CStringProp ImportUser;          //Username für Samba-share csvordreimport
    AeApp::CStringProp ImportPWD;           //Pwd für Samba-share
    AeApp::CStringProp ImportAdresse;       //Ziel-Verzeichnis fuer FTP
    AeApp::CStringProp ImportServer;        //Remote-Server fuer FTP
    AeApp::CStringProp InputEncoding;
    AeApp::CStringProp OutputEncoding;
    ShortProp          TelefonieTyp;        //Art des Contactventers 0 = HiPath / 1 = Lync
    AeApp::LongProp    StartNoCallback;     //Startnummer der Rückrufpartner
    CStringProp        ProInvoiceno;        //Rechnungsnr des Proformaauftrags
    CharProp           KndNLTyp;            //Nachliefertyp des Kunden
    CharProp           KndEilSperre;        //Eilbotensperre des Kunden
    AeApp::CharProp    QuotaInheritance;    //Kunde mit Kontingentvererbung

    HWNDProp    PromoWnd;             //Pointer zum Eingabedialog Promotionen
    HWNDProp    CallinWnd;            //Pointer zum Anzeigefenster welcher Kunde anruft
    HWNDProp    ConnectWnd;           //Pointer zum Anzeigefenster ob weiterleiten oder nicht

    AeApp::ppStringProp ErrorPath;             //path für ppError-Errormsg

protected:
    ppCallPlanParameter* m_pCallParameter;

private:
    bool        m_bAsOpen;                  //Nordat-Server offen
    bool        m_bTrace;                   //Procenter Trace
    CStringProp Rechner;                    //Rechner, auf dem aktuell gearbeitet wird
    ppTime*     m_pCurrentTime;             //aktuelle Serverzeit
    ppDate*     m_pCurrentDate;             //aktuelles Serverdatum
    CStringArray    m_Sprachen;             //zur Verfügung stehende Sprachen
    CStringArray    m_ForbiddenWords;       //nicht erlaubte Wörter in kdauftrag.bemerkung
    bool        m_bIsCBStatusUsed;          //is new callback status used in current country

    CCountry    _country;
    COrderType  _orderType;
    CAeAppPresenter _presenter;


public:
    CAeApp();
    ~CAeApp();

    CView*          m_pViewLeer;
    CView*          m_pViewEing;
    CView*          m_pViewBearb;
    CAeDoc*         m_Doc;
    CAeUser*        m_pAeUser;              //Benutzerprofil
    CKombiAKBArt    m_KombiAKBArt;          //Kombinationen Auftrags, Kommi- und Buchungsart
    CVBFILIALEN     m_vbfil;                // Verbundzeiten der Filialen
    CNLEVELIBTBRANCHES m_ibtfil;            // Verbundzeiten der Filialen
    CStringArray    m_Auftragarten;         // Liste der vorhandenen Auftragarten

    CProCenter m_ProCenter;
    CAeLogging m_AeLogging;
    CAeTrace m_AeTrace;
    COECUSTOMERCALLS m_OECustomerCalls;

    void SetView(int nView);             //aktuellen View setzen
    void SetFilialNrActual(short fili);
    void SetSprachen(CString s)             { m_Sprachen.Add(s); }
    void SetForbiddenWords(CString s)       { m_ForbiddenWords.Add(s); }

    CString GetSprachen(int i)              { return m_Sprachen.GetAt(i); }
    int     GetAnzSprachen()                { return m_Sprachen.GetCount(); }
    CString GetForbiddenWords(int i)        { return m_ForbiddenWords.GetAt(i); }
    int     GetAnzForbiddenWords()          { return m_ForbiddenWords.GetCount(); }

    bool    IsAT()                          { return _country.IsAT(); }
    bool    IsBA()                          { return _country.IsBA(); }
    bool    IsBG()                          { return _country.IsBG(); }
    bool    IsCH()                          { return _country.IsCH(); }
    bool    IsDE()                          { return _country.IsDE(); }
    bool    IsFR()                          { return _country.IsFR(); }
    bool    IsHR()                          { return _country.IsHR(); }
    bool    IsRS()                          { return _country.IsRS(); }
    bool    IsPF()                          { return _country.IsPF(); }
    bool    IsMK()                          { return _country.IsMK(); }

    BOOL    VersionsPruefung();             //Prueft Versionsstand mit aktuellem Server
    int     OpenAsSession(CString strRechner); //Oeffnen ServerSession
    void    CloseAsSession();               //Schliessen ServerSession
    int     ChangeBranch(CString Server,short FilialNr);    //Oeffnen ServerSession in anderer Filiale
    virtual void DoWaitCursor(int nCode);
    const std::vector<Filiale>& HoleFilialen();
    void    ReadLanguage(CString Language);
    bool    IsKABAKomb(short sVZ, CString cAufArt, CString cKA, CString cBA);   //Kombination erlaubt ?
    int     GetKoArtenListeVZ(short sVZ, int index, CString& KoArt);
        //liefert einen Eintrag der Kommiarten-Liste
        //aus der entsprechenden Filiale
        //z.B.: "0 Normale kommisionierung"
    void    GetBranchName(short sVZ, CString& BranchName);
    void    GetRemarkTypes(short sRemarktype, CString& RemarkName);
    int     GetBuArtenListeVZ(short sVZ, int index, CString& BuArt);
        //liefert einen Eintrag der Buchunsarten-Liste
        //aus der entsprechenden Filiale
        //z.B.: "0 Bestand abb.,Bedarf kumul."

        //liefert einen Eintrag der TaxRates-Liste
    int     GetTaxRates(int index, char& cStd, double& TaxRate);
    void    ClearZUGrund(int ZUGrund);

    COrderType& GetOrderType() { return _orderType; }

    const ppTime& GetCurrentTime();
    const ppDate& GetCurrentDate();

    const CCountry& GetCountry() const;
    bool IsCBStatusUsed() { return m_bIsCBStatusUsed; }

    void InitOtherViews();

protected:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL InitInstance();
    virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
    virtual int ExitInstance();

    afx_msg void OnAppAbout();
    afx_msg void OnDeleteReservation();
    afx_msg void OnKundeKndWahl();
    afx_msg void OnUpdateKundeKndWahl(CCmdUI* pCmdUI);
    afx_msg void OnInfKunde();
    afx_msg void OnUpdateInfKunde(CCmdUI* pCmdUI);
    afx_msg void OnUpdateInfArt(CCmdUI* pCmdUI);
    afx_msg void OnInfAuf();
    afx_msg void OnUpdateInfAuf(CCmdUI* pCmdUI);
    afx_msg void OnKundeKundeAusPlan();
    afx_msg void OnUpdateKundeKundeAusPlan(CCmdUI* pCmdUI);
    afx_msg void OnUpdateKundeOffeneAuftrge(CCmdUI* pCmdUI);
    afx_msg void OnKundeOffeneAuftrge();
    afx_msg void OnInfArt();
    afx_msg void OnKombAuftBuchArt();
    afx_msg void OnUpdateKombAuftBuchArt(CCmdUI* pCmdUI);
    afx_msg void OnDefBuchart();
    afx_msg void OnUpdateDefBuchart(CCmdUI* pCmdUI);
    afx_msg void OnDefKommiarten();
    afx_msg void OnUpdateDefKommiarten(CCmdUI* pCmdUI);
    afx_msg void OnDefKondgrp();
    afx_msg void OnUpdateDefKondgrp(CCmdUI* pCmdUI);
    afx_msg void OnDefAuftrart();
    afx_msg void OnUpdateDefAuftrart(CCmdUI* pCmdUI);
    afx_msg void OnParAufbearb();
    afx_msg void OnUpdateParAufbearb(CCmdUI* pCmdUI);
    afx_msg void OnParAufbearberg();
    afx_msg void OnUpdateParAufbearberg(CCmdUI* pCmdUI);
    afx_msg void OnParKobehtyp();
    afx_msg void OnUpdateParKobehtyp(CCmdUI* pCmdUI);
    afx_msg void OnParKommi();
    afx_msg void OnUpdateParKommi(CCmdUI* pCmdUI);
    afx_msg void OnParNachrart();
    afx_msg void OnUpdateParNachrart(CCmdUI* pCmdUI);
    afx_msg void OnHilsprogKennwort();
    afx_msg void OnUpdateHilsprogKennwort(CCmdUI* pCmdUI);
    afx_msg void OnHilfsprTaschenrechner();
    afx_msg void OnUpdateHilfsprTaschenrechner(CCmdUI* pCmdUI);
    afx_msg void OnHilfsprogrammeBenverw();
    afx_msg void OnUpdateHilfsprogrammeBenverw(CCmdUI* pCmdUI);
    afx_msg void OnFastOpenOrder();
    afx_msg void OnUpdateFastOpenOrder(CCmdUI* pCmdUI);
    afx_msg void OnSortzurorderAuftragsnr();
    afx_msg void OnUpdateSortzurorderAuftragsnr(CCmdUI* pCmdUI);
    afx_msg void OnSortzurorderAposchlz();
    afx_msg void OnUpdateSortzurorderAposchlz(CCmdUI* pCmdUI);
    afx_msg void OnSortzurorderIdf();
    afx_msg void OnUpdateSortzurorderIdf(CCmdUI* pCmdUI);
    afx_msg void OnSortzurorderTour();
    afx_msg void OnUpdateSortzurorderTour(CCmdUI* pCmdUI);
    afx_msg void OnExtrasAnrufplanzuerstabarbeiten();
    afx_msg void OnUpdateExtrasAnrufplanzuerstabarbeiten(CCmdUI* pCmdUI);
    afx_msg void OnAuftragDafzurckgestellteauftrge();
    afx_msg void OnUpdateAuftragDafzurckgestellteauftrge(CCmdUI* pCmdUI);
    afx_msg void OnInformationenInfoliste();
    afx_msg void OnUpdateInformationenInfoliste(CCmdUI* pCmdUI);
    afx_msg void OnInformationenStatusauftragsverarbeitung();
    afx_msg void OnUpdateInformationenStatusauftragsverarbeitung(CCmdUI* pCmdUI);
    afx_msg void OnAuftragStatistik();
    afx_msg void OnInformationenTouren();
    afx_msg void OnUpdateInformationenTouren(CCmdUI* pCmdUI);
    afx_msg void OnInformationenTagesanrufplan();
    afx_msg void OnUpdateInformationenTagesanrufplan(CCmdUI* pCmdUI);
    afx_msg void OnInfoUpd();
    afx_msg void OnUpdateInfoUpd(CCmdUI* pCmdUI);
    afx_msg void OnAltfilUpd();
    afx_msg void OnUpdateAltfilUpd(CCmdUI* pCmdUI);
    afx_msg void OnZeitartUpd();
    afx_msg void OnUpdateZeitartUpd(CCmdUI* pCmdUI);
    afx_msg void OnInformationenSeralog();
    afx_msg void OnUpdateInformationenSeralog(CCmdUI* pCmdUI);
    afx_msg void OnExtrasKeineparaanrufe();
    afx_msg void OnUpdateExtrasKeineparaanrufe(CCmdUI* pCmdUI);
    afx_msg void OnAeAuftrEntsp();
    afx_msg void OnUpdateAeAuftrEntsp(CCmdUI* pCmdUI);
    afx_msg void OnBearbeitenNachlieferpositionen();
    afx_msg void OnUpdateBearbeitenNachlieferpositionen(CCmdUI* pCmdUI);
    afx_msg void OnAuftragFfnenparaauftrag();
    afx_msg void OnUpdateAuftragFfnenparaauftrag(CCmdUI* pCmdUI);
    afx_msg void OnVerwaltungAnzeigebenutzerliste();
    afx_msg void OnUpdateVerwaltungAnzeigebenutzerliste(CCmdUI* pCmdUI);
    afx_msg void OnVerwaltungRufzeitenabweichungendefinieren();
    afx_msg void OnUpdateVerwaltungRufzeitenabweichungendefinieren(CCmdUI* pCmdUI);
    afx_msg void OnBearbeitenLagerendkontrolle();
    afx_msg void OnUpdateBearbeitenLagerendkontrolle(CCmdUI* pCmdUI);
    afx_msg void OnBearbeitenNachlieferpositionenKnd();
    afx_msg void OnUpdateBearbeitenNachlieferpositionenKnd(CCmdUI* pCmdUI);
    afx_msg void OnProtNachlifbearb();
    afx_msg void OnUpdateProtNachlifbearb(CCmdUI* pCmdUI);
    afx_msg void OnParAuftrendzeit();
    afx_msg void OnUpdateParAuftrendzeit(CCmdUI* pCmdUI);
    afx_msg void OnKndAuftragart();
    afx_msg void OnUpdateKndAuftragart(CCmdUI* pCmdUI);
    afx_msg void OnUpdateAuftragStatistik(CCmdUI* pCmdUI);
    afx_msg void OnExtrasKundeIdf();
    afx_msg void OnUpdateExtrasKundeIdf(CCmdUI* pCmdUI);
    afx_msg void OnExtrasPznDirekt();
    afx_msg void OnUpdateExtrasPznDirekt(CCmdUI* pCmdUI);
    afx_msg void OnVerwaltungCallback();
    afx_msg void OnUpdateVerwaltungCallback(CCmdUI* pCmdUI);
    afx_msg void OnExtrasAttachPartner();
    afx_msg void OnUpdateExtrasAttachPartner(CCmdUI* pCmdUI);
    afx_msg void OnVerwaltungFilialpartner();
    afx_msg void OnUpdateVerwaltungFilialpartner(CCmdUI* pCmdUI);
    afx_msg void OnExtrasRrMeld();
    afx_msg void OnUpdateExtrasRrMeld(CCmdUI* pCmdUI);
    afx_msg void OnAeRrEntsp();
    afx_msg void OnUpdateAeRrEntsp(CCmdUI* pCmdUI);
    afx_msg void OnExtrasRrNotDone();
    afx_msg void OnUpdateExtrasRrNotDone(CCmdUI* pCmdUI);
    afx_msg void OnExtrasNoBeep();
    afx_msg void OnUpdateExtrasNoBeep(CCmdUI* pCmdUI);
    afx_msg void OnAnrufplanMasterplanPflege();
    afx_msg void OnUpdateAnrufplanMasterplanPflege(CCmdUI* pCmdUI);
    afx_msg void OnRufadminAbweichung();
    afx_msg void OnUpdateRufadminAbweichung(CCmdUI* pCmdUI);
    afx_msg void OnRufadminUebernahme();
    afx_msg void OnUpdateRufadminUebernahme(CCmdUI* pCmdUI);
    afx_msg void OnAnrufplanverwaltungRegionenfestlegen();
    afx_msg void OnUpdateAnrufplanverwaltungRegionenfestlegen(CCmdUI* pCmdUI);
    afx_msg void OnAuswertMaster();
    afx_msg void OnUpdateAuswertMaster(CCmdUI* pCmdUI);
    afx_msg void OnAnrufplanverwaltungLokaleeinstellungen();
    afx_msg void OnUpdateAnrufplanverwaltungLokaleeinstellungen(CCmdUI* pCmdUI);
    afx_msg void OnAnrufplanverwaltungKundendatenDafenummerndern();
    afx_msg void OnUpdateAnrufplanverwaltungKundendatenDafenummerndern(CCmdUI* pCmdUI);
    afx_msg void OnAnrufplanverwaltungKundendatenKundeneigenschaften();
    afx_msg void OnUpdateAnrufplanverwaltungKundendatenKundeneigenschaften(CCmdUI* pCmdUI);
    afx_msg void OnInformationenNotdienst();
    afx_msg void OnUpdateInformationenNotdienst(CCmdUI* pCmdUI);
    afx_msg void OnExtrasPosZusammen();
    afx_msg void OnUpdateExtrasPosZusammen(CCmdUI* pCmdUI);
    afx_msg void OnExtrasNichtMeldAuftragOffen();
    afx_msg void OnUpdateExtrasNichtMeldAuftragOffen(CCmdUI* pCmdUI);
    afx_msg void OnInformationenLagerrevision();
    afx_msg void OnUpdateInformationenLagerrevision(CCmdUI* pCmdUI);
    afx_msg void OnInformationenArtikelkonto();
    afx_msg void OnUpdateInformationenArtikelkonto(CCmdUI* pCmdUI);
    afx_msg void OnExtrasAuswahlKurz();
    afx_msg void OnUpdateExtrasAuswahlKurz(CCmdUI* pCmdUI);
    afx_msg void OnExtrasAnzeigeAllePos();
    afx_msg void OnUpdateExtrasAnzeigeAllePos(CCmdUI* pCmdUI);
    afx_msg void OnSortzurorderAart();
    afx_msg void OnUpdateSortzurorderAart(CCmdUI* pCmdUI);
    afx_msg void OnExtrasAnzeigeAlleDef();
    afx_msg void OnUpdateExtrasAnzeigeAlleDef(CCmdUI* pCmdUI);
    afx_msg void OnExtrasVerarbRegio();
    afx_msg void OnUpdateExtrasVerarbRegio(CCmdUI* pCmdUI);
    afx_msg void OnPflegeSonderTouren();
    afx_msg void OnUpdatePflegeSonderTouren(CCmdUI* pCmdUI);
    afx_msg void OnMailVz();
    afx_msg void OnUpdateMailVz(CCmdUI* pCmdUI);
    afx_msg void OnExtrasSofort();
    afx_msg void OnUpdateExtrasSofort(CCmdUI* pCmdUI);
    afx_msg void OnInfoUpdZent();
    afx_msg void OnUpdateInfoUpdZent(CCmdUI* pCmdUI);
    afx_msg void OnHipathLogoff();
    afx_msg void OnUpdateHipathLogoff(CCmdUI* pCmdUI);
    afx_msg void OnHipathLogon();
    afx_msg void OnUpdateHipathLogon(CCmdUI* pCmdUI);
    afx_msg void OnHipathPauseStart();
    afx_msg void OnUpdateHipathPauseStart(CCmdUI* pCmdUI);
    afx_msg void OnHipathPauseStop();
    afx_msg void OnUpdateHipathPauseStop(CCmdUI* pCmdUI);
    afx_msg void OnHipathCall();
    afx_msg void OnUpdateHipathCall(CCmdUI* pCmdUI);
    afx_msg void OnHipathCallEnd();
    afx_msg void OnUpdateHipathCallEnd(CCmdUI* pCmdUI);
    afx_msg void OnHipathTrace();
    afx_msg void OnUpdateHipathTrace(CCmdUI* pCmdUI);
    afx_msg void OnHipathDel();
    afx_msg void OnUpdateHipathDel(CCmdUI* pCmdUI);
    afx_msg void OnHipathRoutback();
    afx_msg void OnUpdateHipathRoutback(CCmdUI* pCmdUI);
    afx_msg void OnExtrasMatchcode();
    afx_msg void OnUpdateExtrasMatchcode(CCmdUI* pCmdUI);
    afx_msg void OnPflegeKundenrufweiterleitungpflegen();
    afx_msg void OnUpdatePflegeKundenrufweiterleitungpflegen(CCmdUI* pCmdUI);
    afx_msg void OnInformationenStockentry();
    afx_msg void OnUpdateInformationenStockentry(CCmdUI* pCmdUI);
    afx_msg void OnPflegeBackrouting();
    afx_msg void OnUpdatePflegeBackrouting(CCmdUI* pCmdUI);
    afx_msg void OnExtrasNureigenerufe();
    afx_msg void OnUpdateExtrasNureigenerufe(CCmdUI* pCmdUI);
    afx_msg void OnSortzurorderKdklasse();
    afx_msg void OnUpdateSortzurorderKdklasse(CCmdUI* pCmdUI);
    afx_msg void OnKundeAuftragseingangsPruefung();
    afx_msg void OnUpdateKundeAuftragseingangsPruefung(CCmdUI* pCmdUI);
    afx_msg void OnSortzurorderPos();
    afx_msg void OnUpdateSortzurorderPos(CCmdUI* pCmdUI);
    afx_msg void OnSortzurorderBranchno();
    afx_msg void OnUpdateSortzurorderBranchno(CCmdUI* pCmdUI);
    afx_msg void OnExtrasRabatt();
    afx_msg void OnUpdateExtrasRabatt(CCmdUI* pCmdUI);
    afx_msg void OnExtrasUebergehenva10();
    afx_msg void OnUpdateExtrasUebergehenva10(CCmdUI* pCmdUI);
    afx_msg void OnInformationenDealerUmsatz();
    afx_msg void OnUpdateInformationenDealerUmsatz(CCmdUI* pCmdUI);
    afx_msg void OnExtrasNuraktiveartikelinf11();
    afx_msg void OnUpdateExtrasNuraktiveartikelinf11(CCmdUI* pCmdUI);
    afx_msg void OnExtrasNobatch();
    afx_msg void OnUpdateExtrasNobatch(CCmdUI* pCmdUI);
    afx_msg void OnExtrasNoPromo();
    afx_msg void OnUpdateExtrasNoPromo(CCmdUI* pCmdUI);
    afx_msg void OnExtrasNoKippzeit();
    afx_msg void OnUpdateExtrasNoKippzeit(CCmdUI* pCmdUI);
    afx_msg void OnIbtbranchUpd();
    afx_msg void OnUpdateIbtbranchUpd(CCmdUI* pCmdUI);
    afx_msg void OnExtrasInfolisteFirstletter();
    afx_msg void OnUpdateExtrasInfolisteFirstletter(CCmdUI* pCmdUI);
    afx_msg void OnAuftragFcOrders();
    afx_msg void OnUpdateAuftragFcOrders(CCmdUI* pCmdUI);
    afx_msg void OnExtrasKommaNoTab();
    afx_msg void OnUpdateExtrasKommaNoTab(CCmdUI* pCmdUI);
    afx_msg void OnPflegeCsvimportparam();
    afx_msg void OnUpdatePflegeCsvimportparam(CCmdUI* pCmdUI);
    afx_msg void OnUpdatePflegeDeleteReservation(CCmdUI* pCmdUI);

    DECLARE_MESSAGE_MAP()

    void InitServerClasses();
    void ExitServerClasses();
};

extern CAeApp theApp;

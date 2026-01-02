#ifndef PXITMDEF_INC
#define PXITMDEF_INC

/*----------------------------------------------------------------------------*/
/*  Define order item flags.                                                  */
/*  Bits are numbered from left to right, Bytes too.                          */
/*----------------------------------------------------------------------------*/
// To ensure UNIPHARM/PHARMOS compatibility, the bits and there position are defined in the same order.


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// kdauftragpos.etposschalter1 / ET1
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define     bDafue                       0  // bitand(etposschalter1, 32768 ) as P1SADA        -- <X'8000'> DAFUE
//#define     bTextsatz                  1  // bitand(etposschalter1, 16384 ) as P1SATX        -- <X'4000'> TEXTSATZ
#define     bItemCancelled               2  // bitand(etposschalter1,  8192 ) as P1SAST        -- <X'2000'> STORNIERT
//#define   bBTXPosition                 3  // bitand(etposschalter1,  4096 ) as P1SABTX       -- <X'1000'> BTX POSITION
#define     bSeriellUebertragen          4  // bitand(etposschalter1,  2048 ) as P1SASER       -- <X'0800'> SERIELL UEBERTRAGEN
#define     bFreierPreis                 5  // bitand(etposschalter1,  1024 ) as P1FRPREIS     -- <X'0400'> FREIE PREISEINGABE
//#define   b???                         6  // bitand(etposschalter1,   512 ) as P1_6_NOTUSED  -- <X'0200'> frei
//#define   b???                         7  // bitand(etposschalter1,   256 ) as P1_7_NOTUSED  -- <X'0100'> frei
#define     bTextAuftragsKopf            8  // bitand(etposschalter1,   128 ) as P1SATX1       -- <X'0080'> AUFTRAGSKOPFTEXT
//#define   bTextMitWert                 9  // bitand(etposschalter1,    64 ) as P1SATX2       -- <X'0040'> TEXT MIT WERT
#define     bTextOhneWert               10  // bitand(etposschalter1,    32 ) as P1SATX3       -- <X'0020'> TEXT OHNE WERT
//#define   bTextZusatzTextFolgt        11  // bitand(etposschalter1,    16 ) as P1SATX4       -- <X'0010'> ZUSATZ FOLGT
//#define   bTextZusatzText             12  // bitand(etposschalter1,     8 ) as P1SATX5       -- <X'0008'> ZUSATZ ZU V. POS.
//#define   bTextAuftragsFuss           13  // bitand(etposschalter1,     4 ) as P1SATX6       -- <X'0004'> AUFTRAGSFUSSTEXT
//#define   b???                        14  // bitand(etposschalter1,     2 ) as P1_14_NOTUSED -- <X'0002'> frei
#define     bTextDategAlpha             15  // bitand(etposschalter1,     1 ) as P1SATX8       -- <X'0001'> ALPHATEXT

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// kdauftragpos.etposschalter2 / ET2
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define     bDisponieren                16  // bitand(etposschalter2, 32768 ) as P1BKAD        -- <X'8000'> ART. DISPONIEREN
#define     bZugesagt                   17  // bitand(etposschalter2, 16384 ) as P1BKAZ        -- <X'4000'> ART. ZUGESAGT
#define     bNachliefern                18  // bitand(etposschalter2,  8192 ) as P1BKAN        -- <X'2000'> ART. NACHLIEFERN
//#define   bLagerDefekt                19  // bitand(etposschalter2,  4096 ) as P1BKDE        -- <X'1000'> LAGERDEFEKT
#define     bUeberMenge                 20  // bitand(etposschalter2,  2048 ) as P1BKUM        -- <X'0800'> UEBERMENGE
#define     bNachFrageBuchung           21  // bitand(etposschalter2,  1024 ) as P1NFBU        -- <X'0400'> NACHFRAGEBUCHUNG
#define     bDefektPosition             22  // bitand(etposschalter2,   512 ) as P1DEFPOS      -- <X'0200'> DEF. POS. A-SPLITT
#define     bDelayedDelivered           23  // bitand(etposschalter2,   256 ) as P1VZA         -- <X'0100'> VERZOEGERTE AUSL.
#define     bAusweichArtikelGebucht     24  // bitand(etposschalter2,   128 ) as P1BKAA        -- <X'0080'> AUSWEICHARTIKEL GEB
//#define   bBestandsDifferenz          25  // bitand(etposschalter2,    64 ) as P1BDIFF       -- <X'0040'> BESTANDSDIFF. KSC-VSE
#define     bSeparatePosition           26  // bitand(etposschalter2,    32 ) as P1SPLITP      -- <X'0020'> SPLITTPOS. (Splitt Position z,B BTM,KK04 etc)
#define     bSperreRabattManuell        27  // bitand(etposschalter2,    16 ) as P1SPRABM      -- <X'0010'> SPERRE RABATTA. MAN (Position darf Manual nicht bearbeitet werden)
#define     bInhibitTransferBem         28  // bitand(etposschalter2,     8 ) as P1NIDRU       -- <X'0008'> POS. NICHT DRUCKEN (Positionsbemerkungen nicht nach Pharmos übertragen)
#define     bPartialIBTQantity          29  // bitand(etposschalter2,     4 ) as P1TEILVB      -- <X'0004'> TEILVERBUND (Position mit Teilverbund)
#define     bStellerKopf                30  // bitand(etposschalter2,     2 ) as P1STKOPF      -- <X'0002'> STELLERKOPF (Steller Pseudo Artikel(Kopf der Stückliste))
#define     bStellerMitglied            31  // bitand(etposschalter2,     1 ) as P1STMITG      -- <X'0001'> STELLERMITGLIED (Steller Artikel)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// kdauftragpos.etposschalter3 / ET3
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   bMengeFehler                32  // bitand(etposschalter3, 32768 ) as P1DMERR       -- <X'8000'> GENERELL, WENN FEHL (Bei Fehler generell gesetzt)
//#define   bMengeFehlt                 33  // bitand(etposschalter3, 16384 ) as P1DMFE        -- <X'4000'> MENGE: FEHLT
//#define   bMengeNichtNumerisch        34  // bitand(etposschalter3,  8192 ) as P1DMUZ        -- <X'2000'> MENGE : ZEICH UNGUEL
//#define   bMengePruefZifferFalsch     35  // bitand(etposschalter3,  4096 ) as P1DMPZ        -- <X'1000'> MENGE : PZ.FALSCH
//#define   bMengeNichtPlausibel        36  // bitand(etposschalter3,  2048 ) as P1DMNP        -- <X'0800'> MENGE : NICHT PLAUSI
//#define   bMengeDoppelt               37  // bitand(etposschalter3,  1024 ) as P1DMDP        -- <X'0400'> MENGE : DOPPELT
//#define   bMengeNichtVerfuegbar       38  // bitand(etposschalter3,   512 ) as P1DMBU        -- <X'0200'> BESTAND UNTERSCHRIT (Bestand unterschritten)
//#define   bMengeAuswArtikelGebucht    39  // bitand(etposschalter3,   256 ) as P1DMAA        -- <X'0100'> AUSWEICHART.GEB. (stattdessen Ausweichartikel gebucht)
//#define   bPZNFehler                  40  // bitand(etposschalter3,   128 ) as P1DAERR       -- <X'0080'> GENERELL, WENN FEHL.
//#define   bPZNFehlt                   41  // bitand(etposschalter3,    64 ) as P1DAFE        -- <X'0040'> ART : FEHLT
//#define   bPZNNichtNumerisch          42  // bitand(etposschalter3,    32 ) as P1DAUZ        -- <X'0020'> ART : ZEICHEN UNGUEL
//#define   bPZNPruefZifferFalsch       43  // bitand(etposschalter3,    16 ) as P1DAPZ        -- <X'0010'> ART : PZ.FALSCH
#define     bMengenKontigentDefekt      44  // bitand(etposschalter3,     8 ) as P1DMMKD       -- <X'0008'> MENGENKONTIG.DEF. (defekt weil Mengenkontigent ausgeschöpft)
//#define   bPZNDoppelt                 45  // bitand(etposschalter3,     4 ) as P1DADP        -- <X'0004'> DOPPELT
#define     bKeinBestandsDefekt         46  // bitand(etposschalter3,     2 ) as P1DKBEST      -- <X'0002'> KEIN BESTANDSDEFEKT
#define     bNichtNachPharmos           47  // bitand(etposschalter3,     1 ) as P1NAPH        -- <X'0001'> NICHT ALT - PHARMOS

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// kdauftragpos.etposschalter4 / ET4
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define     bToCommission               48  // bitand(etposschalter4, 32768 ) as P1PKO          -- <X'8000'> POS.AN KOMMISSION. (Kommissionieren?)
#define     bToCustomerService          49  // bitand(etposschalter4, 16384 ) as P1PKD          -- <X'4000'> POS. AN KUNDENDIENST (AnKundendienst?)
//#define   bRuecktaktVerarbeitet       50  // bitand(etposschalter4,  8192 ) as P1PRV          -- <X'2000'> RUECKTAKT VERARB. (RuecktaktVerarbeitet?)
#define     bToDisposal                 51  // bitand(etposschalter4,  4096 ) as P1PDI          -- <X'1000'> POSITION AN DISPOAB (AnDispo?)
#define     bKuehlboxPosition           52  // bitand(etposschalter4,  2048 ) as P1KBOX         -- <X'0800'> KUEHLBOX POS. (KuehlboxPosition)
//#define   bMitAbschlag                53  // bitand(etposschalter4,  1024 ) as P1PAB          -- <X'0400'> POSITION MIT ABSCHLAG (MitAbschlag? -> vergewaltigt: BTM-Beleg gedruckt im PVK085)
//#define   bMitPoolAbrechnung          54  // bitand(etposschalter4,   512 ) as P1PPOOL        -- <X'0200'> POS. POOLABRECHNUNG (MitPoolAbrechnung?)
//#define   bKundendienstGedruckt       55  // bitand(etposschalter4,   256 ) as P1PDRU         -- <X'0100'> POS. KUNDEND. GEDR. (KundendienstGedruckt?)
//#define   bTeamAbrechnung             56  // bitand(etposschalter4,   128 ) as P1PTEAM        -- <X'0080'> POS. AS-ABGERECHNET (TeamAbrechnung?)
#define     bMengenErhoehung            57  // bitand(etposschalter4,    64 ) as P1PMERH        -- <X'0040'> POS. MENGENERH. (Automatische Mengenerhoehung NN/NR)
#define     bAuxPosted                  58  // bitand(etposschalter4,    32 ) as P1PVBGB        -- <X'0020'> POS. VERBUND GEBUCHT (Position im Verbund gebucht)
//#define   bVerbundVerarbeiten         59  // bitand(etposschalter4,    16 ) as P1PVBVER       -- <X'0010'> POS. VERRBUND VERARB (Position im Verbund verarbeiten)
#define     bAuxPostPossible            60  // bitand(etposschalter4,     8 ) as P1PVBMGL       -- <X'0008'> POS. VERBUND MOEGL. (Verbundbuchung moeglich)
//#define   bVerbundDafueBuchen         61  // bitand(etposschalter4,     4 ) as P1PVBDBU       -- <X'0004'> POS. VERBUND DAFUE (Position Verbund Dafue Buchen)
#define     bVerbundAuftragsPosition    62  // bitand(etposschalter4,     2 ) as P1PVBAUF       -- <X'0002'> POS. IN VERBUNDAUFTRAG (Verbundauftragsposition)
#define     bAbverkaufsErhoehung        63  // bitand(etposschalter4,     1 ) as P1PABVKE       -- <X'0001'> POS. MIT ABVERK.-ERHOEHUNG  (Position mit abverkaufserhoehung)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// kdauftragpos.etposschalter5 / ET5
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   bVerbundArtikelBestNull     64  // bitand(etposschalter5, 32768 ) as P1VBBNU        -- <X'8000'> VB - ART.BESTAND 0 (Verbundartikel Bestand auf 0)
//#define   bVerbundZweiterVersuch      65  // bitand(etposschalter5, 16384 ) as P1VBZWEI       -- <X'4000'> VB - ZWEITER VERSUCH (Verbund Buchen zweiter Versuch)
//#define   bVerbundDefekt              66  // bitand(etposschalter5,  8192 ) as P1VBDEF        -- <X'2000'> VB - DEFEKT (Verbund defekt)
//#define   bVerbundDefektLager         67  // bitand(etposschalter5,  4096 ) as P1VBDEFL       -- <X'1000'> VB - DEFEKT LAGER (Verbund defekt im Lager)
//#define   bVerbundSamstagsVersorgt    68  // bitand(etposschalter5,  2048 ) as P1DSABV        -- <X'0800'> DSABV SAMST.VERS. (Verbund Samstags Versorgt)
//#define   bArtikelAnfrage             69  // bitand(etposschalter5,  1024 ) as P1ANFRA        -- <X'0400'> ARTIKELANFRAGE(AA) (Artikel Anfrage)
//#define   bTestPosition               70  // bitand(etposschalter5,   512 ) as P1TESTP        -- <X'0200'> TESTPOSITION (Test Position)
//#define   bHochPreisArtikel           71  // bitand(etposschalter5,   256 ) as P1HOPRP        -- <X'0100'> POS.HOCHPREISART. (Hochpreisartikel)
//#define   bNachLieferungGebucht       72  // bitand(etposschalter5,   128 ) as P1NLGB         -- <X'0080'> POS.NACHL.GEB. (Nachlieferung gebucht)
#define     bNachLieferungVerarbeitet   73  // bitand(etposschalter5,    64 ) as P1NLVER        -- <X'0040'> POS.NACHL.VERARB (Nachlieferung verarbeitet)
//#define   bKuehlArtikelContainer      74  // bitand(etposschalter5,    32 ) as P1KUCONT       -- <X'0020'> KUEHLART.CONTAINE (Kuehlartikel Container)
//#define   bEntfernteBTMBuchung        75  // bitand(etposschalter5,    16 ) as P1BTMEF        -- <X'0010'> ENTFERNTE BTM.BUCH (Entfernte BTM Buchung)
//#define   bContainerSplit             76  // bitand(etposschalter5,     8 ) as P1CONTS        -- <X'0008'> CONTAINER - SPLITT (ContainerSplit)
#define     bSubReimportArtikel         77  // bitand(etposschalter5,     4 ) as P1SUBR         -- <X'0004'> SUBST.REIMPORT (Substitution Reimport Artikel)
//#define   bAutomatischGebucht         78  // bitand(etposschalter5,     2 ) as P1AUTOPOS      -- <X'0002'> AUTOM.GEB.POS. (Automatisch gebuchte Position)
//#define   bBuendelKennzeichen         79  // bitand(etposschalter5,     1 ) as P1BUEKZ        -- <X'0001'> BUENDELKZ.PHOSIX (Buendelkennzeichen)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// kdauftragpos.etposschalter6 / ET6
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   bDiabetesAccount            80  // bitand(etposschalter6, 32768 ) as P1PDS          -- <X'8000'> POS.DIABETESSTF. (Diabetes Position)
//#define   bOmgAbrechnung              81  // bitand(etposschalter6, 16384 ) as P1POMG         -- <X'4000'> POS.OMG - ABRECH. (Omg Position)
#define     bMidasAbrechnung            82  // bitand(etposschalter6,  8192 ) as P1PMIDAS       -- <X'2000'> POS.MIDAS - ABR. (Midas Position)
#define     bNaturalRabattIntern        83  // bitand(etposschalter6,  4096 ) as P1NRINT        -- <X'1000'> NATRA INTERN (Interne Natural Rabatt)
//#define   bKeinNettoPreis             84  // bitand(etposschalter6,  2048 ) as P1NONN         -- <X'0800'> KEIN NN - PREIS ERL. (Kein Netto Preis)
#define     bNeuerPreisKsc              85  // bitand(etposschalter6,  1024 ) as P1NPKSC        -- <X'0400'> NEUER PREIS KSC (Neuer Preis KSC)
//#define   bNeuerPreisUpdate           86  // bitand(etposschalter6,   512 ) as P1NPUPD        -- <X'0200'> NEUER PREIS UPDATE (Neuer Preis Update)
//#define   bNettoAbrechnung            87  // bitand(etposschalter6,   256 ) as P1NETTABR      -- <X'0100'> NETTOABRECHNUNG (Netto Abrechnung)
//#define   bSonderPreis                88  // bitand(etposschalter6,   128 ) as P1SOPREIS      -- <X'0080'> SONDERPREIS (Sonderpreis)
//#define   bSticker                    89  // bitand(etposschalter6,    64 ) as P1STICKER      -- <X'0040'> STICKER FRANCE (Sticker Frankreich)
//#define   bWarenkorbRabatt            90  // bitand(etposschalter6,    32 ) as P1WAKORB       -- <X'0020'> WARENKORBRABATT (Warenkorbrabatt)
#define     bArtikelUmgeschluesselt     91  // bitand(etposschalter6,    16 ) as P1AUMG         -- <X'0010'> ARTIKEL UNGESCHL. (Artikel wurde umgeschlüsselt(Alphatext))
#define     bInfoBelegDrucken           92  // bitand(etposschalter6,     8 ) as P1INFOB        -- <X'0008'> INFOBELEG DRUCKEN (Info-Beleg drucken)
#define     bCustPurchase               93  // bitand(etposschalter6,     4 ) as P1KDISPO       -- <X'0004'> KUNDE WUENSCHT DI (disponieren vom Kunden gewünscht)
#define     bCustRestDelivery           94  // bitand(etposschalter6,     2 ) as P1KNACHL       -- <X'0002'> KUNDE WUENSCHT NL (nachliefern vom Kunden gewünscht)
#define     bManualMaintenance          95  // bitand(etposschalter6,     1 ) as P1MANBE        -- <X'0001'> MANUELL BEARB.(PH) (Position manuel bearbeiten)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// kdauftragpos.etposschalter7 / ET7
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   bChargenSplitt              96  // bitand(etposschalter7, 32768 ) as P1CSP          -- <X'8000'> CHARGENSPLIT FR (Chargen Splitt)
//#define   bClub                       97  // bitand(etposschalter7, 16384 ) as P1CLUB         -- <X'4000'> CLUB(SANDOZ / TAD) (Club (Sandoz/Tad))
//#define   bNewSuivraStammhaus         98  // bitand(etposschalter7,  8192 ) as P1NSS          -- <X'2000'> NEW SUIVRA STAMMH. (New Suivra Stammhaus)
//#define   bNewSuivraVerbundHaus       99  // bitand(etposschalter7,  4096 ) as P1NSV          -- <X'1000'> NEW SUIVRA VB - HAUS (New Suivra Verbundhaus)
//#define   bContainerGedruckt          100 // bitand(etposschalter7,  2048 ) as P1CODRKZ       -- <X'0800'> Container gedruckt (Container gedruckt)
#define     bTHWertAusKsc               101 // bitand(etposschalter7,  1024 ) as P1THKSC        -- <X'0400'> TH - WERT AUS KSC (THwert Aus KSC (BG))
//#define   bBigInvoicing               102 // bitand(etposschalter7,   512 ) as P1GRFAK        -- <X'0200'> GROSSOFAKTUR(D) (GrossFaktur(D))
//#define   bDynRetLagerort             103 // bitand(etposschalter7,   256 ) as P1DYNAU        -- <X'0100'> DYN.RET.LAGERORT  S (Dyn Ret Lagerort S ???)
#define     bDayNightMergePosition      104 // bitand(etposschalter7,   128 ) as P1DNMPO        -- <X'0080'> DAY / NIGHT - MERGE FR (Day Night Merge Position (FR internal use))
//#define   bElacPriceCalculated        105 // bitand(etposschalter7,    64 ) as P1PELAC        -- <X'0040'> ELAC - PREIS GERECHN. (ELAC-PREIS GERECHN. (not used in KSC))
//#define   bMDEAutoBundle              106 // bitand(etposschalter7,    32 ) as P1MDEAUTO      -- <X'0020'> MDE AUTOBUENDEL (MDE AUTOBUENDEL (not used in KSC))
#define     bFixedInvoicePrice          107 // bitand(etposschalter7,    16 ) as P1FAPKSC       -- <X'0010'> VERBINDL.FAP KSC (fixed invoice price (FR Ivrylab CACIC))
#define     bProduserQuotaDefect        108 // bitand(etposschalter7,     8 ) as P1HKONTDEF     -- <X'0008'> HERST - KONT - DEFEKT (Herstellerkontingent defekt(AT))
//#define   b???                        109 // bitand(etposschalter7,     4 ) as P1SIEMENSB     -- <X'0004'> BUENDEL SIEMENSAUT
//#define   b???                        110 // bitand(etposschalter7,     2 ) as P1DIA          -- <X'0002'> DIABETES GERECHNET
//#define   b???                        111 // bitand(etposschalter7,     1 ) as P1MIDFAK       -- <X'0001'> MIDAS - PREIS FAKTUR

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// kdauftragpos.etposschalter8 / ET8
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   b???                        112 // bitand(etposschalter8, 32768 ) as P1FIXCHA       -- <X'8000'> CHARGE IN P1VORCHA
//#define   b???                        113 // bitand(etposschalter8, 16384 ) as P1CEENDK       -- <X'4000'> CHARGENERFASSUNG
//#define   bFMDDispensed               114 // bitand(etposschalter8,  8192 ) as P1FMDDIS       -- <X'2000'> FMD "DISPENSED" (Kunde und Artikel FMD relevant!!! Wird in PDX041 gesetzt nicht im KSC!)
//#define   b???                        115 // bitand(etposschalter8,  4096 ) as P1FREI4        -- <X'1000'> FREI 4
//#define   b???                        116 // bitand(etposschalter8,  2048 ) as P1FREI5        -- <X'0800'> FREI 5
//#define   b???                        117 // bitand(etposschalter8,  1024 ) as P1FREI6        -- <X'0400'> FREI 6
//#define   b???                        118 // bitand(etposschalter8,   512 ) as P1FREI7        -- <X'0200'> FREI 7
//#define   b???                        119 // bitand(etposschalter8,   256 ) as P1FREI8        -- <X'0100'> FREI 8
//#define   b???                        120 // bitand(etposschalter8,   128 ) as P1FREI9        -- <X'0080'> FREI 9
//#define   b???                        121 // bitand(etposschalter8,    64 ) as P1FREI10       -- <X'0040'> FREI 10
//#define   b???                        122 // bitand(etposschalter8,    32 ) as P1FREI11       -- <X'0020'> FREI 11
#define     bPriceLimitExceeded         123 // bitand(etposschalter8,    16 ) as P1FREI12       -- <X'0010'> FREI 12 (Price limit exceeded - BG)
#define     bLongTermLack               124 // bitand(etposschalter8,     8 ) as P1FREI13       -- <X'0008'> FREI 13 (Dauerdefekt)
#define     bItemClosed                 125 // bitand(etposschalter8,     4 ) as P1FREI14       -- <X'0004'> FREI 14 (mark position as completely booked).
#define     bCancelItem                 126 // bitand(etposschalter8,     2 ) as P1FREI15       -- <X'0002'> FREI 15 (internal use for pos reordering during order cancel)
#define     bCancelAndDeleteItem        127 // bitand(etposschalter8,     1 ) as P1FREI16       -- <X'0001'> FREI 16 (internal use for pos reordering during order cancel)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//#define cPXITMFLG_MAPWIDTH       128    // max number of bits in this bit map 4 Bytes currently not used

#endif // PXITMDEF_INC

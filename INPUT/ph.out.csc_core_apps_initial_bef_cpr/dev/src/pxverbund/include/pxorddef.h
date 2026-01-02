#ifndef PXORDDEF_INC
#define PXORDDEF_INC

/*----------------------------------------------------------------------------*/
/*  Misc. constants and flags.                                                */
/*----------------------------------------------------------------------------*/
// Function code flags for CountItems():
#define bCOUNT_ITEMTYPE              1  // count items matching type lparm
#define bCOUNT_QSTATE                2  // count items matching quantity state
#define bCOUNT_ARTSTATE              4  // dto., but article state
#define bCOUNT_DCT_ERRORS            8  // count items having DCT errors
#define bCOUNT_OPIATES              16  // no. of opiates
#define bCOUNT_COOLERS              32  // items requiring cooler boxes
#define bCOUNT_TO_COMMISSION        64  // no. of items to pick in stock
#define bCOUNT_ITEM_FLAG           128  // no. of items having flag 'lparm' set
#define bCOUNT_TARGET_PROMOTION    256  // no. of items having promotitionno>0 and promotype = 1

/*----------------------------------------------------------------------------*/
/*  Misc. constants for DelayedDelivery Orders                                */
/*----------------------------------------------------------------------------*/
#define cDCTSequenceNumDDELMax      34

/*----------------------------------------------------------------------------*/
/*  UNIPHARM/PHARMOS compatibility:                                           */
/*  Define order flag positions.                                              */
/*  Bits are numbered from left to right, Bytes too.                          */
/*----------------------------------------------------------------------------*/

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// kdauftrag.etauftragschalter1 / A1ET1
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define     uErfassungZurueckGestellt       0       // bitand(etauftragschalter1, 32768 ) as A1ERFZ    -- <X'8000'> Erf.zurueckgestellt
#define     uErfassungAbgeschlossen         1       // bitand(etauftragschalter1, 16384 ) as A1ERFA    -- <X'4000'> Erf.abgeschlossen
#define     uKommiBegonnen                  2       // bitand(etauftragschalter1,  8192 ) as A1KOMB    -- <X'2000'> Kommi begonnen
#define     uKommiBeendet                   3       // bitand(etauftragschalter1,  4096 ) as A1KOMA    -- <X'1000'> Kommi abgeschl.
#define     uFakturierbar                   4       // bitand(etauftragschalter1,  2048 ) as A1FKTB    -- <X'0800'> Kann FAKTURIERT w.
#define     uFakturiert                     5       // bitand(etauftragschalter1,  1024 ) as A1FKTA    -- <X'0400'> wurde fakturiert
#define     uStorniert                      6       // bitand(etauftragschalter1,   512 ) as A1ASTO    -- <X'0200'> Auftrag storniert
#define     uNichtAenderbar                 7       // bitand(etauftragschalter1,   256 ) as A1ANMA    -- <X'0100'> Auftrag nicht aen
#define     uTurnOverOrigin                 8       // bitand(etauftragschalter1,   128 ) as A1AVH     -- <X'0080'> AUFTR.V.HERST. (FR)
#define     bRouteCheck                     9       // bitand(etauftragschalter1,    64 ) as A1TURPR   -- <X'0040'> TOUR PRUEFEN
#define     bQuantityLimitCheck             10      // bitand(etauftragschalter1,    32 ) as A1KWRR    -- <X'0020'> Kunde wuenscht R
//#define   uKeinePositionAnhaengen         11      // bitand(etauftragschalter1,    16 ) as A1NIAN    -- <X'0010'> Keine Pos.anhae
#define     uKeinUpdateValutadatum          12      // bitand(etauftragschalter1,     8 ) as A1KUVA    -- <X'0008'> KEIN UPD.VALUTA
//#define   uKeinAckAufDS99                 13      // bitand(etauftragschalter1,     4 ) as A1KADS99  -- <X'0004'> STEUERUNG DAFUE
//#define   uSerbienTagesSam                14      // bitand(etauftragschalter1,     2 ) as A1TSRA    -- <X'0002'> SERBIEN: TAGESSAM
#define     uBulgariaListFive               15      // bitand(etauftragschalter1,     1 ) as A1LISTE5  -- <X'0001'> BULGARIEN : LISTE5

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// kdauftrag.etauftragschalter2 / A1ET2
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   uAuftragInQ1                    16      // bitand(etauftragschalter2, 32768 ) as A1Q1      -- <X'8000'> Auftrag in Q1
//#define   uAuftragInQ2                    17      // bitand(etauftragschalter2, 16384 ) as A1Q2      -- <X'4000'> Auftrag in Q2
//#define   uAuftragInQ3                    18      // bitand(etauftragschalter2,  8192 ) as A1Q3      -- <X'2000'> Auftrag in Q3
//#define   uAuftragInQ4                    19      // bitand(etauftragschalter2,  4096 ) as A1Q4      -- <X'1000'> Auftrag in Q4
//#define   uAuftragInQ8                    20      // bitand(etauftragschalter2,  2048 ) as A1Q8      -- <X'0800'> AUFTRAG IN Q8
#define     uVerzoegerAusgeliefert          21      // bitand(etauftragschalter2,  1024 ) as A1VERZA   -- <X'0400'> VERZOEGERTE AUSL.
#define     uAuftragVomXML                  22      // bitand(etauftragschalter2,   512 ) as A1AVXML   -- <X'0200'> XML - AUFTRAG
//#define   uAlterIDFAmedis                 23      // bitand(etauftragschalter2,   256 ) as A1AAIDF   -- <X'0100'> Amedis Alt - IDF
//#define   uAuftragVonUMK                  24      // bitand(etauftragschalter2,   128 ) as A1DSUMK   -- <X'0080'> Auftrag von UMK
//#define   uUMKOnline                      25      // bitand(etauftragschalter2,    64 ) as A1DSONL   -- <X'0040'> Online, Off:UMK - D    // Off: UMK Disc
//#define   uUMKSeriell                     26      // bitand(etauftragschalter2,    32 ) as A1DSSR    -- <X'0020'> Seriell, Off;para      // Off: parallel
//#define   uZurueckstellenDAFUE            27      // bitand(etauftragschalter2,    16 ) as A1DSZU    -- <X'0010'> Zurueckst.weg.         // Zurueckstellen wg. Dafue-Ereignis
#define     bCorruptLimitCheck              28      // bitand(etauftragschalter2,     8 ) as A1DFWUB   -- <X'0008'> DEFEKTWERT - !BER      // #define uDefektLimitCheck            28 // Defektwert ueberschritten
//#define   uDafueReinRuf                   29      // bitand(etauftragschalter2,     4 ) as A1DFRF    -- <X'0004'> DAFUE - REINRUF        // Dafue Reinruf
//#define   uDafueAbbruch99                 30      // bitand(etauftragschalter2,     2 ) as A1DFCAN   -- <X'0002'> DAFUE - ABBR.99        // Dafue Abbruch nach 99
#define     uDoppelteBestellung             31      // bitand(etauftragschalter2,     1 ) as A1DFABN   -- <X'0001'> AMEDIS DOPP.BE         // Amedis doppelte Bestellung

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// kdauftrag.etauftragschalter3 / A1ET3
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   uDAFUEAbbruch                   32      // bitand(etauftragschalter3, 32768 ) as A1DAE     -- <X'8000'> Dafue - Abbruch
//#define   uKuehlBoxBuchen                 33      // bitand(etauftragschalter3, 16384 ) as A1KBOX    -- <X'4000'> Kuehlbox buchen
#define     uKuehlBoxDisabled               34      // bitand(etauftragschalter3,  8192 ) as A1KBOXD   -- <X'2000'> Kuehlbox disabled
#define     uBTMErwerbScheinBuchen          35      // bitand(etauftragschalter3,  4096 ) as A1BTMB    -- <X'1000'> BTM - Erwerbs.buche
//#define   uKeinLagerAuftrag               36      // bitand(etauftragschalter3,  2048 ) as A1KRL1    -- <X'0800'> kein Lagerauftrag
//#define   uAuftragInLagerEbene1           37      // bitand(etauftragschalter3,  1024 ) as A1LE1     -- <X'0400'> Auftrag in LE 1
//#define   uAuftragInLagerEbene2           38      // bitand(etauftragschalter3,   512 ) as A1LE2     -- <X'0200'> Auftrag in LE 2
//#define   uAuftragInLagerEbene3           39      // bitand(etauftragschalter3,   256 ) as A1LE3     -- <X'0100'> Auftrag in LE 3
//#define   uAuftragInLagerEbene4           40      // bitand(etauftragschalter3,   128 ) as A1LE4     -- <X'0080'> Auftrag in LE 4
//#define   uAuftragInLagerEbene5           41      // bitand(etauftragschalter3,    64 ) as A1LE5     -- <X'0040'> Auftrag in LE 5
//#define   uAuftragInLagerEbene6           42      // bitand(etauftragschalter3,    32 ) as A1LE6     -- <X'0020'> Auftrag in LE 6
//#define   uAuftragInLagerEbene7           43      // bitand(etauftragschalter3,    16 ) as A1LE7     -- <X'0010'> Auftrag in LE 7
//#define   uAuftragInLagerEbene8           44      // bitand(etauftragschalter3,     8 ) as A1LE8     -- <X'0008'> AUFTRAG IN LE 8
#define     uAuftragSHWithC                 45      // bitand(etauftragschalter3,     4 ) as A1SHA     -- <X'0004'> STAMMHAUS
#define     uAuftragSHWithS                 46      // bitand(etauftragschalter3,     2 ) as A1CLE     -- <X'0002'> CLEARING
#define     uAuftragGetrennt                47      // bitand(etauftragschalter3,     1 ) as A1AUFSEP  -- <X'0001'> AUFTR.SEPARIERT

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// kdauftrag.etauftragschalter4 / A1ET4
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   uEintragQ4Notwendig             48      // bitand(etauftragschalter4, 32768 ) as A1Q4N     -- <X'8000'> Auftrag muss in Q4
#define     bAuxPositions                   49      // bitand(etauftragschalter4, 16384 ) as A1VBWA    -- <X'4000'> Auftr.mit Verbund.
//#define   uAutomatPositionVorhanden       50      // bitand(etauftragschalter4,  8192 ) as A1AUWA    -- <X'2000'> Auftrag mit Autom.
#define     uMitWerbung                     51      // bitand(etauftragschalter4,  4096 ) as A1MWERB   -- <X'1000'> Auftrag mit Werbef
#define     uMitNachlieferung               52      // bitand(etauftragschalter4,  2048 ) as A1NLPOS   -- <X'0800'> Auftrag mit NL - Pos
//#define   uMitNachAuslieferung            53      // bitand(etauftragschalter4,  1024 ) as A1NLAUS   -- <X'0400'> Auftrag mit NL - Aus
#define     bImmediatePrint                 54      // bitand(etauftragschalter4,   512 ) as A1SODRU   -- <X'0200'> Sofortdruck Sonde
#define     uMitGefahrenGut                 55      // bitand(etauftragschalter4,   256 ) as A1GEFGUT  -- <X'0100'> Auftrag mit Gefah
#define     uMitZytostatika                 56      // bitand(etauftragschalter4,   128 ) as A1ZYTOS   -- <X'0080'> Auftrag mit Zytos
//#define   uQ2InStockLevel1                57      // bitand(etauftragschalter4,    64 ) as A1Q2LE1   -- <X'0040'> AUFTRAG IN Q2 LE1
//#define   uQ2InStockLevel2                58      // bitand(etauftragschalter4,    32 ) as A1Q2LE2   -- <X'0020'> AUFTRAG IN Q2 LE2
//#define   uQ2InStockLevel3                59      // bitand(etauftragschalter4,    16 ) as A1Q2LE3   -- <X'0010'> AUFTRAG IN Q2 LE3
//#define   uQ2InStockLevel4                60      // bitand(etauftragschalter4,     8 ) as A1Q2LE4   -- <X'0008'> AUFTRAG IN Q2 LE48
//#define   uQ2InStockLevel5                61      // bitand(etauftragschalter4,     4 ) as A1Q2LE5   -- <X'0004'> AUFTRAG IN Q2 LE5
//#define   uRabateArtikelSelection         62      // bitand(etauftragschalter4,     2 ) as A1NAAUSW  -- <X'0002'> NR - ARTIKEL AUSWAHL
//#define   uA1ET4_Bit63_UNUSED             63      // bitand(etauftragschalter4,     1 ) as A1FREI    -- <X'0001'> FREI

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// kdauftrag.etauftragschalter5 / A1ET5
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define     uStammhausNewSuivra             64      // bitand(etauftragschalter5, 32768 ) as A1SHNS    -- <X'8000'> STAMMHAUS NEW SUIVRA
#define     uVerbundhausNewSuivra           65      // bitand(etauftragschalter5, 16384 ) as A1VHNS    -- <X'4000'> VB - HAUS NEW SUIVRA
//#define   uGefahrenGutBelegDruck          66      // bitand(etauftragschalter5,  8192 ) as A1GGFDR   -- <X'2000'> GEFAHRGUTBELEGDRUCK
#define     bDoNotConnectDKRAK              67      // bitand(etauftragschalter5,  4096 ) as A1KRAKV   -- <X'1000'> KEINE DKRAK - VERBIND.
#define     bEncloserSplitt                 68      // bitand(etauftragschalter5,  2048 ) as A1BEIFSA  -- <X'0800'> BEIFUEGESPLITTAUFTR.
#define     bNoRebateAccount                69      // bitand(etauftragschalter5,  1024 ) as A1KRABKO  -- <X'0400'> KEIN RABATTKONTO BG
#define     bSepDefectOrder                 70      // bitand(etauftragschalter5,   512 ) as A1DEFAUF  -- <X'0200'> DEFEKTAUFTRAG(YSI)
//#define   uA1ET5_Bit71_UNUSED             71      // bitand(etauftragschalter5,   256 ) as A1KKOMMI  -- <X'0100'> KEINE KOMMI(PVA420)
//#define   uA1ET5_Bit72_UNUSED             72      // bitand(etauftragschalter5,   128 ) as A1FREI9   -- <X'0080'>  FREI 9
//#define   uA1ET5_Bit73_UNUSED             73      // bitand(etauftragschalter5,    64 ) as A1FREI10  -- <X'0040'>  FREI 10
//#define   uA1ET5_Bit74_UNUSED             74      // bitand(etauftragschalter5,    32 ) as A1FREI11  -- <X'0020'>  FREI 11
//#define   uA1ET5_Bit75_UNUSED             75      // bitand(etauftragschalter5,    16 ) as A1FREI12  -- <X'0010'>  FREI 12
//#define   uA1ET5_Bit76_UNUSED             76      // bitand(etauftragschalter5,     8 ) as A1FREI13  -- <X'0008'>  FREI 13
//#define   uA1ET5_Bit77_UNUSED             77      // bitand(etauftragschalter5,     4 ) as A1FREI14  -- <X'0004'>  FREI 14
//#define   uA1ET5_Bit78_UNUSED             78      // bitand(etauftragschalter5,     2 ) as A1FREI15  -- <X'0002'>  FREI 15
//#define   uA1ET5_Bit79_UNUSED             79      // bitand(etauftragschalter5,     1 ) as A1FREI16  -- <X'0001'>  FREI 16

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// kdauftrag.etauftragschalter6 / A1ET6
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   uA1ET6_Bit80_UNUSED             80      // bitand(etauftragschalter6, 32768 ) as A1FREI1   -- <X'8000'> FREI 1
//#define   uA1ET6_Bit81_UNUSED             81      // bitand(etauftragschalter6, 16384 ) as A1FREI2   -- <X'4000'> FREI 2
//#define   uA1ET6_Bit82_UNUSED             82      // bitand(etauftragschalter6,  8192 ) as A1FREI3   -- <X'2000'> FREI 3
//#define   uA1ET6_Bit83_UNUSED             83      // bitand(etauftragschalter6,  4096 ) as A1FREI4   -- <X'1000'> FREI 4
//#define   uA1ET6_Bit84_UNUSED             84      // bitand(etauftragschalter6,  2048 ) as A1FREI5   -- <X'0800'> FREI 5
//#define   uA1ET6_Bit85_UNUSED             85      // bitand(etauftragschalter6,  1024 ) as A1FREI6   -- <X'0400'> FREI 6
//#define   uA1ET6_Bit86_UNUSED             86      // bitand(etauftragschalter6,   512 ) as A1FREI7   -- <X'0200'> FREI 7
//#define   uA1ET6_Bit87_UNUSED             87      // bitand(etauftragschalter6,   256 ) as A1FREI8   -- <X'0100'> FREI 8
//#define   uA1ET6_Bit88_UNUSED             88      // bitand(etauftragschalter6,   128 ) as A1FREI9   -- <X'0080'> FREI 9
//#define   uA1ET6_Bit89_UNUSED             89      // bitand(etauftragschalter6,    64 ) as A1FREI10  -- <X'0040'> FREI 10
//#define   uA1ET6_Bit90_UNUSED             90      // bitand(etauftragschalter6,    32 ) as A1FREI11  -- <X'0020'> FREI 11
//#define   uA1ET6_Bit91_UNUSED             91      // bitand(etauftragschalter6,    16 ) as A1FREI12  -- <X'0010'> FREI 12
//#define   uA1ET6_Bit92_UNUSED             92      // bitand(etauftragschalter6,     8 ) as A1FREI13  -- <X'0008'> FREI 13
//#define   uA1ET6_Bit93_UNUSED             93      // bitand(etauftragschalter6,     4 ) as A1FREI14  -- <X'0004'> FREI 14
//#define   uA1ET6_Bit94_UNUSED             94      // bitand(etauftragschalter6,     2 ) as A1FREI15  -- <X'0002'> FREI 15
//#define   uA1ET6_Bit95_UNUSED             95      // bitand(etauftragschalter6,     1 ) as A1FREI16  -- <X'0001'> FREI 16

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


#define cPXORDFLG_MAPWIDTH                  96      // max number of bits in this bit map
#define cCOLLECTIVORDER22                   "CV22"  // Collecttiv order CV22

namespace Order
{
    enum OrderCloseOptions
    {
        CLOSE_DEFAULT,                   // 0 = Normal closehandling
        CLOSE_NOTFORCONSOLIDATION        // 1 = Order is not for consolidation
    };

    enum States
    {
        // State definitions:
        LeaveAsIs = 0,    // 0 Caution: do NEVER change this value!!
        EntryInProgress = 1,    // 1 Order entry currently on progress
        UpdateInProgress = 2,    // 2 Order update in progress
        EntryDeferred = 3,    // 3 Order entry deferred
        EntryClosed = 4,    // 4 Order entry closed
        ShipmentInProgress = 5,    // 5
        ShipmentClosed = 6,    // 6
        Invoiceable = 7,    // 7 Order ready to invoice
        Invoiced = 8,    // 8 Invoicing done
        Cancelled = 9,    // 9 Entire order is cancelled
        Protected = 10,   //10 Order is protected against changes
        CustomerService = 11,   //11 Scheduled for customer service
        ProblemClearance = 12,   //12 Scheduled for manual problem clearance
        CallBack = 13,   //13 Scheduled for customer call back
        DCParallel = 14,   //14 Received from a parallel DC terminal
        Consolidation = 15,   //15 Orderconsolidation
        OrderSendStart = 10,   // 10 Order in transmission (OrderEvent)
        OrderSendEnd = 11,   // 11 Order Send End        (OrderEvent)
        cStateLast = 16,
        ChangedCst = 101,  // Customer changed
        ChangedTourId = 102,  // Tourid changed
        ChangedCommiType = 103,  // CommiType changed
        EntryClosedKL = 104,  // Closed inspite of creditlimit
        ChangedOrderType = 105,  // OrderType changed
        ChangedToDefaultMSV3OrderLabel = 106,  // Changed to default MSV3 order label
        CancelledKL = 109,  // Cancelled because of creditlimit
        OrderCreation = 110,   // Initial order creation
        OrderSendCancel = 111,  // 111 Order Send Cancel    (OrderEvent)

        // Define negations for queries:
        NOT_EntryInProgress = ~EntryInProgress,
        NOT_UpdateInProgress = ~UpdateInProgress,
        NOT_EntryDeferred = ~EntryDeferred,
        NOT_EntryClosed = ~EntryClosed,
        NOT_ShipmentInProgress = ~ShipmentInProgress,
        NOT_ShipmentClosed = ~ShipmentClosed,
        NOT_Invoiceable = ~Invoiceable,
        NOT_Invoiced = ~Invoiced,
        NOT_Cancelled = ~Cancelled,
        NOT_Protected = ~Protected,
        NOT_CustomerService = ~CustomerService,
        NOT_ProblemClearance = ~ProblemClearance,
        NOT_CallBack = ~CallBack,
        NOT_DCParallel = ~DCParallel,
        NOT_Consolidation = ~Consolidation
    };

    enum CloseArgs
    {
        // Additional Closearguments
        cClose_Nohandle = 0,             // 0 do not effekt normal close
        cClose_UnConditional,            // 1 close the order if State = EntryClosed
        cClose_SeparatedOrder            // 2 close the order in Background
    };

    enum CancelArgs
    {
        // Additional Closearguments
        cCancel_Nohandle = 0,             // 0 do not effekt normal cancel
        cCancel_UnConditional             // 1 cancel the order,just for authorized users
    };

    enum CloseType
    {
        CLOSE,
        CANCEL
    };

    enum ApprovalType
    {
        NOT_DEFINED = 0,
        CREDIT,
        CASH

    };

    enum RCEntryDeffered
    {
        // Additional Closearguments
        CreditLimitOnTop,                // Customer's creditlimit reached
        InternetOrderEntry,              // Orderentry via Internet
        BackRouting,                     // Order backrouting Callcenter
        DDNotClose,                      // Order is Delayed Delivery
        SeparateArtGroup,                // Separated Article Group
        DoNotAppend,                     // Do not append positions
        OverDriveCondition,              // OverDriveCondition not reached(Swiss)
        RebateArtSelection,              // RebateArticleSelection(BG)
        NoRebateQty,                     // NoRebateQty for discountarticle(BG)
        NoCics,                          // No Cics available for using tcaccess(BG)
        NullDocument,                    // Order with no WertAuftrag(BG)
        HighValuePosition,               // High Value on position level(RS)
        ManufacturerInventory,           // Deffered for manufacturer inventory (Ivrylab)
        KonsigPartnerInventory,          // Deffered for konsignartion partner inventory (Ivrylab)
        // Define negations for queries:

        NOT_CreditLimitOnTop = ~CreditLimitOnTop,
        NOT_InternetOrderEntry = ~InternetOrderEntry,
        NOT_BackRouting = ~BackRouting,
        NOT_DDNotClose = ~DDNotClose,
        NOT_SeparateArtGroup = ~SeparateArtGroup,
        NOT_DoNotAppend = ~DoNotAppend,
        NOT_OverDriveCondition = ~OverDriveCondition,
        NOT_RebateArtSelection = ~RebateArtSelection,
        NOT_NoRebateQty = ~NoRebateQty,
        NOT_NoCics = ~NoCics,
        NOT_NullDocument = ~NullDocument,
        NOT_HighValuePosition = ~HighValuePosition,
        NOT_ManufacturerInventory = ~ManufacturerInventory,
        NOT_KonsigPartnerInventory = ~KonsigPartnerInventory,
        cRCEntryDefferedLast = 16
    };

    struct SumItemsProperties
    {
        int coolerq;        // no. of items requiring coolers
        int postrestdel;    // postable restdelivery positions
        int todisposalq;    // items to disposal
        int toserviceq;     // items to Customer Service branch
        int auxposq;        // items with aux.positions
        int freightage;     // Freightage article
        int zytosq;         // no. of zytostatika
        int danggood;       // count of dangerous articles
        int commiq;         // items to be commissioned
        int k04;            // no. of KuehlKetten Artikel
        int k08;            // no. of Gekuehlt08  Artikel
        int k20;            // no. of Gekuehlt20  Artikel
        int opiateq;        // no. of opiates
        int reshospital;    // no. of reserve hospital positions
        int positivlistq;   // positiv list article
        int psychoq;        // Psychotrop
        int healthfundq;    // article with pricetype = healthfund(KK BG)
        int retailq;        // article with pricetype = retail(EV BG)
        int prisoq;         // Privatsortiment

        SumItemsProperties()
        {
            coolerq = 0;
            postrestdel = 0;
            todisposalq = 0;
            toserviceq = 0;
            auxposq = 0;
            freightage = 0;
            zytosq = 0;
            danggood = 0;
            commiq = 0;
            k04 = 0;
            k08 = 0;
            k20 = 0;
            opiateq = 0;
            reshospital = 0;
            positivlistq = 0;
            psychoq = 0;
            healthfundq = 0;
            retailq = 0;
            prisoq = 0;
        }
    };
}

#endif

#ifndef __AASRV_H
#define __AASRV_H

#define ORD_UNBEKANNT           -1
#define ORD_ERFASST             0
#define ORD_ZURUECKGESTELLT     1
#define ORD_ZURUECKGEST_DAFUE   2
#define ORD_KEIN_AUFTRAG        3
#define ORD_WEITERER_AUFTRAG    4
#define ORD_STORNIERT           5
#define ORD_STORNO_DAFUE        6

#define ORD_DAFUE_FEHLER        7
#define ORD_KOMMI_ENDE          8
#define ORD_FAKTUR_ENDE         9
#define ORD_IN_KOMMI            10
#define ORD_BEREIT_ZUR_FAKTUR   11
#define ORD_IN_ERFASSUNG        12
#define ORD_IN_AENDERUNG        13

#define ORD_ZUM_LESEN_OEFFNEN   14
#define ORD_DAFUE_RR            15    /* DAFUE Fehler und Rückruf   */

#define ORD_ZU_INTERNET         16    /* zurueckstellen Internetauftrag */
#define ORD_ZU_CLEAR_INTERNET   17    /* zurueckstellen und clearen Internetflag    */
#define ORD_ZU_DD_OHNE          18    /* zurueckstellen ohne automatischen Abschluss    */
#define ORD_ZU_CLEAR_DD_OHNE    19    /* zurueckstellen mit automatischen Abschluss */
#define ORD_UNBEDINGT           99    /* Unbedingt abschliessen(Kreditlimit)    */
#define ORD_STORNO_UNBEDINGT    98    /* Unbedingt stornieren(Kreditlimit)  */
#define ORD_DELAYED_DELIVERY    97    /* Unbedingt stornieren(Kreditlimit)  */
//TODO DO NOT CHECK IN, JUST FOR BUILD purposes because the checkin from ronni doesnt build
#define ORD_DELAYED_KL          96    /* zurueckgestellt wg. Kreditlimit    */
#define ORD_ERFASST_NO_COND     95    /* sofort abschliessen    */

#define ZU_KREDITLIMIT          0
#define ZU_INTERNET             1
#define ZU_BACKROUTING          2
#define ZU_DD_OHNE              3
#define ZU_BTM                  4
#define ZU_NOT_APPEND           5
#define ZU_OV                   6
#define ZU_WAHL_STELLER         7
#define ZU_NO_QTY_NR            8
#define ZU_NO_CICS              9
#define ZU_NULL_DOKU            10
#define ZU_HIGH_VALUE           11
#define ZU_INVENTUR_HERST       12
#define ZU_INVENTUR_KONSIG      13

#define ITEM_STAT_VERBUND_REICHT_NICHT      -3
#define ITEM_STAT_VERBUND_NICHT_MOEGLICH    -2
#define ITEM_STAT_KEINE_MENGE               -1
#define ITEM_STAT_NORMAL                     0  /* Reihenfolge im Dialog verankert */
#define ITEM_STAT_ZUGESAGT                   1  /* Reihenfolge im Dialog verankert */
#define ITEM_STAT_DISPO                      2  /* Reihenfolge im Dialog verankert */
#define ITEM_STAT_NACHLIEFERN                3  /* Reihenfolge im Dialog verankert */
#define ITEM_STAT_NACHFRAGE                  4
#define ITEM_STAT_NACHLIEFUPD                5  /* Nachlieferposition updaten */
#define ITEM_STAT_KREDITLIMIT                6  /* Kreditlimit ueberschritten */
#define ITEM_STAT_NOREBATE                   7  /* Rabattartikel nicht gebucht */
#define ITEM_STAT_ROEXHAUSTED                8  /* Rabattauftragswert ueberschritten */
#define ITEM_STAT_REVERSE                    9  /* Reverse Substitution */
#define ITEM_STAT_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE   10  /* BG: Price checks: The product price is not compliant to the NHIF, RefP and MWP */
#define ITEM_STAT_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE               11  /* BG: Price checks: The product price is not compliant to the RefP and MWP */
#define ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION_06                           12  /* BG: Price checks: The registered price of the product has been deleted Customergoup 06 */
#define ITEM_STAT_LIMIT_MWP_EXCEEDANCE                                      13  /* BG: Price checks: The product price is higher than the MWP */
#define ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION                              14  /* BG: Price checks: The registered price of the product has been deleted. */
#define ITEM_STAT_IGNORE_PRICELIMIT                                         15  /* BG: Price checks: Book position without limit check */



#define ITEM_ART_SERA           'S'
#define ITEM_ART_PARA           'P'
#define ITEM_ART_DAFUE          'D'
#define ITEM_ART_NO_DAFUE       ' '

#define ITEM_APO_DISPO          'D'   /* Apotheke wollte Dispo */
#define ITEM_APO_NACHL          'N'   /* Apotheke wollte Nachlieferung */
#define ITEM_APO_NO_DI_OR_NL    ' '

#define SORT_ORDER_ORDNUMBER    0     /* Auftragssortierung nach Auftragsnummer  */
#define SORT_ORDER_IDF          1     /* Auftragssortierung nach IDF-Nummer  */
#define SORT_ORDER_TOUR         2     /* Auftragssortierung nach Tour    */
#define SORT_ORDER_APO_ENDE     3     /* Auftragssortierung nach Apothekenschließzeit */
#define SORT_ORDER_AART         4     /* Auftragssortierung nach Auftragsart */
#define SORT_ORDER_KDKLASSE     5     /* Auftragssortierung nach Kundenklasse */
#define SORT_ORDER_ANZPOS       6     /* Auftragssortierung nach Anzahl Postitionen */
#define SORT_ORDER_BRANCHNO     7     /* Auftragssortierung nach Filialen */

#define ITEM_ARTNR_FREITEXT     -1    /* Item ist ein Freitext       */

#define MAX_ERROR_MSG_AE        81

#define AUF_TEXT_KOPF           1     /* Auftragskopftext */
#define AUF_TEXT_KOPF_INFO      2     /* Auftragskopftext Infoorder */
#define AUF_TEXT_FUSS           3     /* Auftragsfusstext */
#define AUF_TEXT_FUSS_INFO      4     /* Auftragsfusstext Infoorder */

#define PLAN_GESPERRT          -1
typedef enum { F_PHON = 4, F_PARA, F_SERA, F_MSERA } rufArt;    /* für kontrolle anrufplan */

#endif // __AASRV_H
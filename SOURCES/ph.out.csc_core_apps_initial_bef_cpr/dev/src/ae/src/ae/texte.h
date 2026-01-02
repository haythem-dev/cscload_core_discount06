#ifndef __TEXTE_H_
#define __TEXTE_H_

#define __LANG_   LANG_GER

/* ALLGFKTN.CPP */
#define TXT_WARNUNG_DBLPKT      "Warnung: "
#define TXT_FEHLER_DBLPKT       "Fehler: "
#define TXT_NUR_ZIFFERN_ERL     "Nur Ziffern erlaubt!"
#define TXT_PROGRAMMABBRUCH     "Programmabbruch: "
#define TXT_KEIN_PIPE_SRV_DEF   "Kein %sPipeSrv in we.ini definiert"
#define TXT_KEIN_PIPE_RES_SRV_D "Kein %sResPipeSrv in we.ini definiert"
#define TXT_KEIN_VERB_AUFB      "Verbindungsaufbau zum Server nicht möglich!"
#define TXT_MAX_ANZ_ZEICHEN     "Die maximale Anzahl möglicher Zeichen wurde erreicht!"
#define TXT_MAX_VOR_NACH_KOMMA  "Eingabe: maximal %d Vor- und %d Nachkommastellen"
#define TXT_FEHL_DATUM          "Ungültiger Datumswert oder falsches Format!"
#define TXT_FEHL_ZEIT           "Ungültige Uhrzeit oder falsches Format!"

/* ALLG.C */
#define TXT_EING_WERT_ERF       "Eingabewert erforderlich!"
#define TXT_EING_UNTERLAUF      "Eingabefehler: Unterlauf"
#define TXT_EING_UEBERLAUF      "Eingabefehler: Ueberlauf"
#define TXT_EING_WERT_MIN       "Minimaler Eingabewert:"
#define TXT_EING_WERT_MAX       "Maximale Eingabewert:"
#define TXT_EING_FALSCH         "Falsche Eingabe!"
#define TXT_WERT_ZU_KLEIN       "Wert ist zu klein!"
#define TXT_KEIN_WERT_EINGEG    "Kein Wert eingegeben!"
#define TXT_NICHT_KONVB_ZEICH   "Nicht konvertierbares Zeichen!"
#define TXT_DM                  "€"

/* AAKUNDE.CPP */
#define TXT_KEIN_KUNDE_IDF      "Kein Kunde mit dieser IDF-Nummer vorhanden!"

/* AATART.CPP */
#define TXT_KEIN_ART_PZN        "Kein Artikel gefunden mit dieser PZN vorhanden!"
#define TXT_KEIN_ALT_ART        "Kein Ausweichartikel gefunden!"

/* AASRV.CPP */
#define TXT_KEINE_TXT_POS       "Position ist keine Textposition!"
#define TXT_KEINE_POS           "Position wurde nicht gefunden!"
#define TXT_AUFTR_NICHT_OFFEN   "Auftrag konnte nicht geoeffnet werden!"
#define TXT_KEINE_ASPIPE_VERB   "Verbindungsaufbau zum AS-Server nicht möglich!"
#define TXT_SYSTEM_ERROR        "System-Fehler!"

/* AAFIL.CPP */
#define TXT_DOPP_WERT           "Wert bereits auf der Datenbank vorhanden"
#define TXT_LOESCH_NICHT_MOEGL  "Loeschen nicht moeglich, wird in anderen Tabellen verwendet!"

/* AATOUR.CPP */
#define TXT_TOUR_NICHT_VORH     "Die Tour ist nicht vorhanden!"

/****************************************************************************/
/* PROJECT WE ***************************************************************/
/****************************************************************************/

/* WE.CPP */
#define TXT_NEG_UID            "Falsche Benutzeridentifikation!"
#define PPGCHECKDATE_ERROR_TEXT "Falsches Datumsformat!"


/****************************************************************************/
/* PROJECT IMEX**************************************************************/
/****************************************************************************/

/* AUSDRUCK - EXPORTKUNDEN(Vz 99 - KdGrp 1) */
/* Zahlungsbedingungen */
#define TXT_ZAHLBED                     "Zahlungsbedingung:"

/* Lieferbedingungen */
#define TXT_LIEFERBED                   "Lieferbedingung:"
#define TXT_EX1 ""
#define TXT_EXW    ""

/* Eigentumsvorbehalt */
#define TXT_EIGENTUMSVORBEHALT          "Eigentumsvorbehalt:" \
#define TXT_EIGENTUMSVORBEHALT_TEXT     "Die Ware bleibt bis zur Erfüllung sämtlicher Forderungen aus der Geschäftsverbindung\n" \
                                        "Eigentum von PHOENIX."


/* Reklamationen */
#define TXT_REKLAMATIONEN               "Reklamationen:"
#define TXT_REKLAMATIONEN_TEXT          "Alle Beanstandungen, insbesondere Mängelrügen, müssen PHOENIX unverzüglich, \n" \
                                        "spätestens jedoch innerhalb von sechs Tagen nach Empfang der Ware bei offenen \n" \
                                        "Mängeln bzw. bei verdeckten Mängeln innerhalb von 6 Tagen nach Entdeckung\n" \
                                        "des Mangels, schriftlich unter Ausschluss des UN-Kaufrechtes"
/* Anwendbares Recht */
#define TXT_ANWENDBARES_RECHT           "Anwendbares Recht:"
#define TXT_ANWENDBARES_RECHT_TEXT      "Es gilt deutsches Recht unter Ausschluss des UN-Kaufrechtes"

/* Gerichtsstand */
#define TXT_GERICHTSSTAND               "Gerichtsstand:"
#define TXT_HANAU                       "Hanau"

/***************************/
/* MODUL: AUFTRAGS-STORNO  */
/***************************/
#define TXT_AUFTRAGSSTORNIERUNG             "AUFTRAGSSTORNIERUNG"
#define TXT_STORNAUFTRAGENTHAELTBESTAUFPOS  "Dieser stornierte Auftrag enthält bestellte Auftragspositionen."
#define TXT_ARTIKELNR                       "Artikel-Nr.: "
#define TXT_BERUECKSICHTIGTINBESTELLUNG     "wurde berücksichtigt in Bestellung Nr.: "

/* Kühlartikel */
#define TXT_KUEHLART_0              ""
#define TXT_KUEHLART_1              "Kühlkette"
#define TXT_KUEHLART_2              "bis 8 Grad Celsius"
#define TXT_KUEHLART_3              "bis 20 Grad Celsius"
#define TXT_KUEHLART_4              "bis 25 Grad Celsius"

/* Leferantenarten */
#define TXT_LIEFERANTENART_0        "Lieferant"
#define TXT_LIEFERANTENART_1        "Spedition"



#endif /* __TEXTE_H_ */

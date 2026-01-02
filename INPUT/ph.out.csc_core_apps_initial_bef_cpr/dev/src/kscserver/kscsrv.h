#define ORD_UNBEKANNT			-1
#define ORD_ERFASST				0
#define ORD_ZURUECKGESTELLT		1
#define ORD_ZURUECKGEST_DAFUE	2
#define	ORD_KEIN_AUFTRAG		3
#define ORD_WEITERER_AUFTRAG	4
#define	ORD_STORNIERT			5
#define ORD_STORNO_DAFUE		6

#define ORD_DAFUE_FEHLER		7
#define ORD_KOMMI_ENDE			8
#define ORD_FAKTUR_ENDE			9
#define ORD_IN_KOMMI			10
#define ORD_BEREIT_ZUR_FAKTUR	11
#define ORD_IN_ERFASSUNG		12
#define ORD_IN_AENDERUNG		13

#define ORD_ZUM_LESEN_OEFFNEN   14
#define ORD_DAFUE_RR			15	  /* DAFUE Fehler und Rückruf	*/

#define ORD_ZU_INTERNET			16	  /* zurueckstellen Internetauftrag	*/
#define ORD_ZU_CLEAR_INTERNET	17	  /* zurueckstellen und clearen Internetflag	*/
#define ORD_ZU_DD_OHNE			18	  /* zurueckstellen ohne automatischen Abschluss	*/
#define ORD_ZU_CLEAR_DD_OHNE	19	  /* zurueckstellen mit automatischen Abschluss	*/
#define ORD_UNBEDINGT			99	  /* Unbedingt abschliessen(Kreditlimit)	*/
#define ORD_STORNO_UNBEDINGT	98	  /* Unbedingt stornieren(Kreditlimit)	*/
#define ORD_DELAYED_DELIVERY	97	  /* Unbedingt stornieren(Kreditlimit)	*/

#define ZU_KREDITLIMIT			0
#define ZU_INTERNET				1
#define ZU_BACKROUTING			2
#define ZU_DD_OHNE				3

#define ITEM_STAT_VERBUND_REICHT_NICHT  -3
#define ITEM_STAT_VERBUND_NICHT_MOEGLICH  -2
#define ITEM_STAT_KEINE_MENGE	-1
#define ITEM_STAT_NORMAL		0	  /* Reihenfolge im Dialog verankert */
#define ITEM_STAT_ZUGESAGT      1	  /* Reihenfolge im Dialog verankert */
#define ITEM_STAT_DISPO 		2	  /* Reihenfolge im Dialog verankert */
#define ITEM_STAT_NACHLIEFERN	3	  /* Reihenfolge im Dialog verankert */
#define ITEM_STAT_NACHFRAGE	    4	

#define ITEM_ART_SERA			'S'	
#define ITEM_ART_PARA			'P'	
#define ITEM_ART_DAFUE			'D'	
#define ITEM_ART_NO_DAFUE		' '	

#define ITEM_APO_DISPO			'D'	  /* Apotheke wollte Dispo */		
#define ITEM_APO_NACHL			'N'	  /* Apotheke wollte Nachlieferung */
#define ITEM_APO_NO_DI_OR_NL	' '	

#define SORT_ORDER_ORDNUMBER	0	  /* Auftragssortierung nach Auftragsnummer	 */
#define SORT_ORDER_IDF			1	  /* Auftragssortierung nach IDF-Nummer	 */
#define SORT_ORDER_TOUR			2	  /* Auftragssortierung nach Tour	 */
#define SORT_ORDER_APO_ENDE		3	  /* Auftragssortierung nach Apothekenschließzeit */
#define SORT_ORDER_AART			4	  /* Auftragssortierung nach Auftragsart */

#define ITEM_ARTNR_FREITEXT	    -1	  /* Item ist ein Freitext		 */

#define MAX_ERROR_MSG_AE		81
 
#define AUF_TEXT_KOPF			1	  /* Auftragskopftext */
#define AUF_TEXT_KOPF_INFO		2	  /* Auftragskopftext Infoorder */
#define AUF_TEXT_FUSS			3	  /* Auftragsfusstext */
#define AUF_TEXT_FUSS_INFO		4	  /* Auftragsfusstext Infoorder */

#define PLAN_GESPERRT          -1
typedef enum { F_PHON = 4, F_PARA, F_SERA, F_MSERA } rufArt;	/* für kontrolle anrufplan */

#define RC_FATAL_ERR      -1    /* schwerwiegende Fehler werden in die Log-Datei eingetragen */
#define RC_WARNING_1      -2    /* Warnung */
#define RC_NO_NEW_REQUEST -5    /* Keine neuen Aufträge */
#define RC_SQLNOTFOUND     1    /* SQLNOTFOUND */
#define RC_FETCH_BROKEN    2    /* FETCH wurde unterbrochen (max.Anzahl) */
#define RC_WARNING_2       3    /* Warnung */
#define RC_WARNING_3       4    /* Warnung */
#define RC_WARNING_4       5    /* Warnung */
#define RC_WARNING_5       6    /* Warnung */
#define RC_OK              0    /* normales Ergebnis (select bzw. fetch usw.) */

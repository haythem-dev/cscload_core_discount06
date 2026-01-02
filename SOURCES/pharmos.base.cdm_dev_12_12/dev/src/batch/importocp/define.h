/*****************************************************************************/
/*   Hauptmodule: lorbas                                                     */
/*   Header     : define.h                                                   */
/*   Autor      : A. Schmidt-Rehschuh (644)                                  */
/*   Sprache    : C                                                          */
/*   erzeugt    : manuell                                                    */
/*                                                                           */
/*   Aufgabe    : Standard Defines fuer Lorbas-Projekt                       */
/*****************************************************************************/

#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

/*** DEFINE - ERRNO.H ********************************************************/
#include <errno.h>

/*** TYPEDEF- EIGENE DATENTYPEN **********************************************/
#ifndef Bitleiste
  typedef unsigned short Bitleiste;
#endif


/*** DEFINE - STANDARD *******************************************************/
#define DELIMITER			'@'
#ifndef TRUE
#define TRUE				1
#endif
#ifndef FALSE
#define FALSE				0
#endif
#define YES                1                      /* Anweisung ausfuehren  */
#define NO                 0                      /* Anweisung nicht ausf. */
#define ERROR             -1                      /* Returncode: Fehler    */
#define OK                 0                      /* Anweisung pruefen     */
#define ENDE              -3                      /* verarbeitungsenden    */
#define LEER              " "                     /* Initialiesierung      */
#define LOESCHEN          -4                      /* Schalter loeschen     */
#define JA_NEIN            2                      /* Vektorleiste Ein/Aus  */
#define KEIN_UPDATE       -9                      /* es erfolgt kein update*/

#define F_READ                         0                                              /* Funktionsparamater für*/
#define F_WRITE                        1                                              /* xvsam                 */
#define F_UPDATE                   2
#define F_DELETE                       3

/*** DEFINE - SQLSTANDARD ****************************************************/
#define DATENBANK         "phosix"
#define DATABASE          "phosix"
#define SQLNOTFOUND       100
#define SQLGESPERRT       -243
#define SQLDOUBLE         -239
#define SQLCODE_OPEN      1                        /* wegen returncode sqlmsg*/
#define SQLERRM           sqlca.sqlerrm
#define SQLCODE           sqlca.sqlcode            /* Sql-Fehler             */
#define SQLISAM           sqlca.sqlerrd[1]         /* Sql-Cisam-Fehler       */
#define SQLUPD            sqlca.sqlerrd[2]         /* Anzahl erfolgeter Upd  */
#define SQLROWCOUNT       sqlca.sqlerrd[3]         /* update/insert row count */
#define NOT_FOUND		SQLCODE == SQLNOTFOUND
#define SQLBEGIN          "begin"
#define SQLCOMMIT         "commit"
#define SQLROLLBACK       "rollback"


/******************************************************************************/
/* DEBUG - DEFINES */
/******************************************************************************/
/* #define DEBUGPRINTF(level, msg) printf msg */
#ifndef NDEBUG
	#define DEBUGPRINTF(level, msg)		printf msg
#else 
    #define DEBUGPRINTF(level, msg)		((void)0)
#endif



/*** DEFINE - DEBUGGER *******************************************************/
#define DEBUG_SECTION        if ( debug_enabled == YES ) {
#define END_DEBUG_SECTION    }
#define DEBG                 debug_enabled
extern void pri( char *, char *, int, int, int );
#ifdef _XCICS
#define DEBUG_PRINT(w,x,y,z) DEBUG_SECTION \
			  pri( w,x,y,z, errno ); \
			  END_DEBUG_SECTION
#else
#define DEBUG_PRINT(w,x,y,z) DEBUG_SECTION \
			  fprintf( stderr, "D-%s: %s Sql:%d Isam:%d " \
				   "error:%d\n", \
				   w,x,y,z, errno ); \
			  END_DEBUG_SECTION
#endif
/*#define PRINT_STRUCTUR(x,y)  printf( "Strukt %s:\n",x); printf( "%s\b\n", y );*/
#define PRINT_STRUCTUR(x)    fprintf( stderr, "Strukt %s:\n", (char *)&x);


/*** DEFINE - MAKROS *********************************************************/
#define PRINT_MSG( x, y )    fprintf( stderr,"%s: %s -> %d\n", x, y, SQLCODE );
#define BEGIN_LOOP(x)        for( ; x == 0 ; ) {
#define END_LOOP(x)          if ( x != 0 ) break; }
#define SET_QANZ(x,y)        sprintf( c_anz, "%-*d", x, y );


/*** DEFINE - DATUM/UHRZEIT **************************************************/
 #define HOLE_DATUM_ZEIT          0
 #define HOLE_DATUM               1
 #define HOLE_UHRZEIT             2
 #define MIT_SEKUNDE              0
 #define OHNE_SEKUNDE             1
 #define MIT_JAHRESZAHL           1
 #define OHNE_JAHRESZAHL          0


/*** DEFINE - BITLEISTE ******************************************************/
 #define BIT_AKTIV            "32768"
 #define BIT_NICHT_AKTIV      "16384"


/*** DEFINE - SATZAUSLEGUNG **************************************************/
 #define PACKED               'P'                    /* Wert packen          */
 #define CHARAC               'C'                    /* String normal        */
 #define STRINO               'S'                    /* String rechtb. mit 0 */
 #define BINAER               'B'                    /* Binaerstream         */
 #define LONGST               'L'                    /* Numerischerwert (bin)*/
 #define HALBWO               'H'                    /* Halbwort (2-Byte)    */
 #define VOLLWO               'V'                    /* Vollwort (4-Byte)    */
 #define BITMST               'T'                    /* Halbwort (2-Byte)    */
 #define EBCDIC               'E'                    /* Ebcdic               */
 #define NUMERC               'N'                    /* Ebcdic               */
 #define L_HALBWORT            5                     /* Max-Laenge Shortwert */

/*** CHAR-ZEICHEN ************************************************************/

 #define MINUS                '-'
 #define PLUS                 '+'
 #define KOMMA                ','
 #define PUNKT                '.'
 #define STR_ENDE             '\0'
 #define BLANC                ' '
 #define ZAHL_NULL            '0'
 #define WERT_NULL            "0"
 #define WERT_EINS            "1"
 #define JA                   'J'
 #define NEIN                 'N'
 #define EIN                  '1'                   /* Vektorleiste Ein/Aus  */
 #define AUS                  '0'                   /* Vektorleiste Ein/Aus  */
 #define DEL                  'D'                   /* Vektorleiste Ein/Aus  */
 #define STR_NULL             "+0000000000000000"

/*** LOG-FILE ****************************************************************/
 
 #define FEHLER               'F'
 #define HINWEIS              'H'
 #define WARNUNG              'W'

/*** MAXIMALE ****************************************************************/

 #define MAX_DECIMAL                21
 #define MAX_KODURCHLAEUFE           5         /* Festgesetzt durch A1-Array */
 #define MAX_KDBETRIEBSENDE          7         /* Festgesetzt durch K1-Array */
 #define MAX_KDAUFTRAGART           10         /* Festgesetzt durch K1-Array */
 #define MAX_TOURPLANTAG            12         /* Festgesetzt durch K1-Array */
 #define MAX_FKWARTESCHLANGE        24         /* Festgesetzt durch Q3-Array */
 #define MAX_L1KOEINHEIT            24         /* Festgesetzt durch L1-Array */
 #define MAX_A3BESTAND              24         /* Festgesetzt durch A3-Array */
 #define MAX_VERBUNDPARTNER          5         /* Festgesetzt durch 10-Array */
 #define MAX_VERBUNDFILIALEN        24         /* Festgesetzt durch 11-Array */
 #define MAX_TOURKDAUFTRAG         100         /* Festgesetzt durch T1-SATZ  */
 #define MAX_ANZEIGE_DS              1         /* wenn BS voll in Anwendumg  */
 #define MAX_AREA_UEBERSCHREITUNG   10         /* Altlast, wegen Returncode  */
 #define MAX_MERKER                100         /* Kopf-Fuss-Saetze (posit.)  */

/*** STANDARDS DURCH PRZ/PHOENIX *********************************************/

 #define STANDARD_VOLUMEN   500                /* wenn kein Volumen bekannt  */
 #define TEXT_POSNR          10                /* Multiplikator, wegen Textz.*/

/*** LAENGEN *****************************************************************/

 #define L_TEXT               81
 #define L_INTEGER            11
 #define L_SHORT               6
 #define L_DATE                9
 #define L_FUNKTION            8
 #define L_SATZART             6
 #define L_ARTIKEL_NR          7
 #define L_MATCHCODE          15
 #define L_NUMERIC             7
 #define L_BITLEISTE          16

/*** DEFINE- TAGESTYPEN ******************************************************/

 #define L_TAGESTYP          2
 #define TYP_MONTAG          "MO"
 #define TYP_DIENSTAG        "DI"
 #define TYP_MITTWOCH        "MI"
 #define TYP_DONNERSTAG      "DO"
 #define TYP_FREITAG         "FR"
 #define TYP_SAMSTAG         "SA"
 #define TYP_SONNTAG         "SO"

/*** DEFINE- ZEITARTENTABELLE ************************************************/
 
 #define ZEITART_VERBUND  "1"
 #define ZEITART_FILIALE  "2"
 #define ZEITART_LADENSCHLUSS "99"

/*** DEFINE- AUFTRAGSTATI ****************************************************/

 #define HOLE                            0
 #define SCHREIBE                        1
 #define TSTATUS                         2
 #define INIT                            3
 #define AUFTRAG_IN_Q4                  11
 #define AUFTRAG_NICHT_AENDERBAR        10
 #define KZ_AUFTRAG_STORNIERT_TAG       '8'
 #define KZ_AUFTRAG_NICHT_AENDERBAR     '7'
 #define AUFTRAG_STORNIERT               9
 #define KZ_AUFTRAG_STORNIERT           '6'
 #define AUFTRAG_FAKTURIERT              8
 #define KZ_AUFTRAG_FAKTURIERT          '5'
 #define AUFTRAG_FAKTUR_BEREIT           7
 #define KZ_AUFTRAG_FAKTUR_BEREIT       '4'
 #define KOMMI_ABGESCHLOSSEN             6
 #define KZ_KOMMI_ABGESCHLOSSEN         '3'
 #define KOMMI_BEGONNEN                  5
 #define KZ_KOMMI_BEGONNEN              '2'
 #define ERFASSUNG_ABGESCHLOSSEN         4
 #define KZ_ERFASSUNG_ABGESCHLOSSEN     '1'
 #define AUFTRAG_ZURUECKGESTELLT         2
/* #define KZ_AUFTRAG_ZURUECKGESTELLT     '0'  */
 #define ERFASSUNG_BEGONNEN              1
 #define KZ_ERFASSUNG_BEGONNEN          '0'

/*** DEFINE - EILKENNZEICHEN (KDAUFTRAG) *************************************/

 #define EILIG                          '1'
 #define EILIG_MIT_PRUEFUNG             '3'
 #define EILIG_OHNE_PRUEFUNG            '6'
 #define NORMAL                         '0'

/*** DEFINE - POSTYP (Nachlieferungsposition) ********************************/

 #define TYP_VERBUND     "1"
 #define TYP_BATCH       "4"

/*** DEFINE - BITLEITE -TEXTE (P1-ET1) ***************************************/

 #define BIT_TEXTSATZ          2 - 1           /* reiner Textsatz auf Pos.   */
 #define BIT_KOPFTEXT          9 - 1           /* Kopftext                   */
 #define BIT_TEXTSATZMITWERT  10 - 1           /* Text mit Wert              */
 #define BIT_TEXTSATZOHNEWERT 11 - 1           /* Text ohne Wert             */
 #define BIT_ZUSATZTEXTFOLGT  12 - 1           /* Es folgt ein Zusatztext    */
 #define BIT_ZUSATZTEXT       13 - 1           /* es ist der Zusatztext      */
 #define BIT_FUSSTEXT         14 - 1           /* Fusstext                   */
 #define BIT_OPIAT			   7 - 1           /* Opiate-Bit				 */
 #define ZUSATZTEXT           9999             /* nicht vorhandene pos erzeug*/

/*** DEFINE - KENNZAHLEN (LfdNr) *********************************************/

 #define AA_KENNZAHL                     1
 #define Q3_KENNZAHL                     2
 #define L1_KENNZAHL                     3

/*** DEFINE - FEHLERNUMMER-CODE **********************************************/

 #define START_OUT_OF_AREA    SQLCODE_OPEN + 2
 #define END_OUT_OF_AREA      SQLCODE_OPEN + 3
 #define START_LORBAS_ERROR   200

 typedef enum {
	      M_KEIN_PAGE = START_LORBAS_ERROR,    /* 152,    2 */
	      M_FUNKTION_UNBEKANNT,                /* 152,    7 */
	      M_PARAMETER_UNBEKANNT,               /*  97,    8 */
	      M_SCHLUESSEL_NICHT_GEFUNDEN,         /*   1,   12 */
	      M_SCHLUESSEL_OHNE_INDEX,             /*  99,   13 */
	      M_KEINE_BITMAP,                      /*  98,   14 */
	      M_AREA_ERROR,                        /*  99,   15 */
	      M_FALSCHE_LAENGE,                    /*  99,   18 */
	      M_ENTER_NICHT_ERLAUBT,               /* 152,   20 */
	      M_ARGUMENT_UNBEKANNT,                /* 152,   22 */
	      M_ENTER_AKTIV,                       /* 152,   23 */
	      M_SYSTEM_ERROR,                      /*   2,   24 */
	      M_TABELLENNR_ERROR,                  /* 152,   51 */
	      M_KEIN_EINTRAG,                      /*  99,   34 */
	      M_NICHT_AKTIV,                       /*   1,   55 */
	      M_ENDE_ERREICHT,                     /*   2,   27 */
	      M_AERA_BELEGT,                       /*   2,   40 */
	      M_AREA_NICHT_BELEGT,                 /* 152,   41 */
	      M_AREA_UNGUELTIG,                    /* 152,   43 */
	      M_IMPART_ERROR,                      /*   3,   46 */
	      M_INIT_AKTIV,                        /*   3,   47 */
	      M_KOMPONENTEN_ERROR,                 /* 152,   73 */
	      M_KEINE_SATZSPERRE,                  /*  03,   74 */
	      M_GELOESCHT,                         /*   1,   75 */
	      M_SATZ_GESPERRT,                     /*   3,   76 */
	      M_DATUM_ERROR,                       /*  99,   91 */
	      M_DEPART_ERROR,                      /*  99,   92 */
	      M_SHUTDOWN                           /*  96,   97 */
	      } M_ERROR;

#endif
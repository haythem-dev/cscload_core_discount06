/* ---------------------------------------------------------------------- *
 *   Aufgabe        : Rabattgruppe für Frankreich automatisch berechnen   *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 18.01.2007                                          *
 *   Autor          : Raab	                                              *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.4.3 : zpcalcrg 25/05/2020 Rolf Raab";
}

/*!
\page page7 zpcalcrg - Rabattgruppe für Frankreich automatisch berechnen
________________________________________________________________________________________
\version	1.4.3
\date		25.05.20
\internal
- RR: Spannengrenze für Cluster 3 von 15 auf 16 % geändert (SR-20059526)
\endinternal
\~german   
Spannengrenze für Cluster 3 von 15 auf 16 % geändert (SR-20059526)
\~english 
(change only relevant for Germany)
\~
________________________________________________________________________________________
\version	1.4.2
\date		09.10.19
\internal
- RR: Preisgrenze für Rabattgruppe Frankreich von 1.600,- auf 1.500,- geändert (SR-19100074)
\endinternal
\~german   
Änderung nur relevant für Frankreich
\~english 
price border for rebate groups 84/85 and 94/95 changed from 1.600,- to 1.500,- (SR-19100074)
\~
________________________________________________________________________________________
\version	1.4.1
\date		22.03.17
\internal
- RR: Spannencluster Deutschland auf Basis kalkppe.aktionsgrosso2 statt aktionsgrosso1 rechnen
\endinternal
\~german   
Spannencluster Deutschland auf Basis Aktionsgrosso2 statt Aktionsgrosso1 rechnen
\~english 
(change only relevant for Germany)
\~
________________________________________________________________________________________
\version	1.4.0
\date		08.03.17
\internal
- RR: Rabattgruppenberechnung Frankreich komplett überarbeitet aufgrund neuer Vorgaben
\endinternal
\~german   
Rabattgruppenberechnung Frankreich komplett überarbeitet aufgrund neuer Vorgaben
\~english 
new design of rebate group calculation for France due to new specifications
\~
________________________________________________________________________________________
\version	1.3.1
\date		14.03.16
\internal
- RR: wieder mal neue Preisgruppengrenzen
\endinternal
\~german   
neue Preisgruppengrenzen Frankreich
\~english 
new price borders for rebate group calculation France
\~
________________________________________________________________________________________
\version	1.3.0
\date		18.03.13
\internal
- TH: AIX build.
\endinternal
________________________________________________________________________________________
\version	1.2.1
\date		10.12.12
\internal
- RR: Rabattgruppe 030 nicht mehr vergeben
\endinternal
________________________________________________________________________________________
\version	1.2.0
\date		19.07.12
\internal
- RR: komplett neue Berechnungsmimik (calculate) für Frankreich (TOP14-Projekt)
\endinternal
_______________________________________________________________________________________
\version	1.1.2
\date		27.12.11
\internal
- RR: nochmal Anpassung in der Änderung zum 01.01.12
\endinternal
________________________________________________________________________________________
\version	1.1.1
\date		05.12.11
\internal
- RR: neue Preisspannen in Frankreich (aktiv ab 01.01.12)
\endinternal

*/

/* 1.0.1   05.06.07 : RR: wenn kein zartpreis gefunden, behandeln wie GEP < 22,90; */
/*						  Gruppe 34 endgültig raus (dafür gibts kein Feld) */
/* 1.0.2   06.06.07 : RR: Subfamily 07 am Ende der Berechnung wie 01 behandeln */
/* 1.0.3   25.06.07 : RR: keine Fehlermeldung, wenn kein Satz gefunden (1. Fetch RC = 100) */
/* 1.0.4   16.04.08 : RR: Partenariat über cdiscount abfragen statt zartikel.sortiment_2 */
/* 1.0.5   07.07.08 : RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						  Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.0.6   25.07.08 : RR: Aufteilung Gruppen 31 & 32 auf 31, 32, 34 & 35 (neue Preisgrenze) */
/* 1.0.7   17.02.10 : RR: Produktart 4 wie 2 behandeln (Generikum) */
/* 1.1.0   20.10.11 : RR: neuer Modus 2 fuer Berechnung Spannencluster */
/* 1.1.1   05.12.11 : RR: neue Preisspannen in Frankreich (aktiv ab 01.01.12) */
/* 1.1.2   27.12.11 : RR: nochmal Anpassung in der Änderung zum 01.01.12 */
/* 1.2.0   19.07.12 : RR: komplett neue Berechnungsmimik (calculate) für Frankreich (TOP14-Projekt) */
/* 1.2.1   10.12.12 : RR: Rabattgruppe 030 nicht mehr vergeben */
/* 1.3.0   18.03.13 : TH: AIX build */
/* 1.4.0   03.09.20 : WH: Produktart 5 wie 4 und 2 behandeln */


long CalcRgLoop ( char *db, char *cDatumVon, char *cDatumBis, char *cArtNr, char *buf );
long SC_CalcScLoop ( char *db, char *cDatumVon, char *cDatumBis, char *cArtNr, char *buf );

/* ------------------------------------------------------------------- */
#define SQL_SETISOLA_ERROR   (-554)
void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

/* ------------------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld )
{
   long s;

   char base[50];
   strcpy( base, "database " );
   strcat( base, db );

   s = SqlExecuteImm( base );
   if ( s != 0 )
   {
      strcpy( errmld, base );
      strcat( errmld, ": " );
      strcat( errmld, DynErrmld() );
      return s;
   }

   s = SqlExecuteImm("set isolation to dirty read" );
   if ( s == SQL_SETISOLA_ERROR ) s = 0;
   if ( s != 0 )
   {
     strcpy( errmld, "set isolation: " );
     strcat( errmld, DynErrmld() );
     CloseBase( );
     return s;
   }

   s = SqlExecuteImm( "SET LOCK MODE TO WAIT 10" );
   if ( s == SQL_SETISOLA_ERROR ) s = 0;
   if ( s != 0 )
   {
     strcat( errmld, "set lock mode: ");
     strcat( errmld, DynErrmld() );
     CloseBase( );
     return s;
   }
   return 0;
}

/* ---------------- Programm-Ausahl ----------------- */
static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

/* ---------------------------------------------------------------------- */
static void LadeUsage( char *buf )
{
	strcat( buf, "- zpcalcrg 1 database datum_von datum_bis [pzn] \n" \
                 "	Neuberechnung Rabattgruppen fuer alle Artikel im angegebenen Datumsbereich\n"\
                 "	datum_von: Beginn des aus zapflege zu selektierenden Zeitraums, Format JHJJMMTT\n"\
                 "	datum_bis: Ende des aus zapflege zu selektierenden Zeitraums, Format JHJJMMTT\n"\
			     "  wird eine PZN angegeben, erfolgt die Berechnung nur fuer diesen Artikel, sonst fuer alle\n"\
			     "  sind beide Datumsfelder gleich 0, erfolgt die Berechnung unabhaengig von zapflege\n"\
	             "- zpcalcrg 2 database datum1 datum2 [pzn] \n" \
                 "	Neuberechnung Spannencluster & Uebernahme Aktionsgrosso fuer alle Artikel, bei \n"\
                 "	denen sich der Aktionsgrosso geaendert hat (Vergleich zartikel - kalkppe) oder \n"\
                 "	im angegebenen Zeitraum eine AEP-Aenderung stattgefunden hat \n"\
                 "	datum1: Untergrenze fuer Ermittlung des aktuellen Preises, Format JHJJMMTT\n"\
                 "	datum2: Obergrenze fuer Ermittlung des aktuellen Preises, Format JHJJMMTT\n"\
			     "  wird eine PZN angegeben, erfolgt die Berechnung nur fuer diesen Artikel, sonst fuer alle\n"\
			     "  ist datum1 = 19000101, erfolgt eine Urladung und es wird keine zapflege geschrieben\n"\
			);
	// User: direkt im Programm vergeben
}

/* ---------------------------------------------------------------------- */
void ProgUsage( char *buf )
{
   Usage( buf );
   LadeUsage( buf );
}

/* ---------------------------------------------------------------------- */
long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   switch ( *argv[0] )
   {
	case '1': 
        if ( argc == 4 )
        {
           s = CalcRgLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
		else if ( argc == 5 )
		{
		   s = CalcRgLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

	case '2': 
        if ( argc == 4 )
        {
           s = SC_CalcScLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
		else if ( argc == 5 )
		{
		   s = SC_CalcScLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

    default:
        s = 1;
        strcpy( buf, "Programm-Teil: " );
        strcat( buf, argv[0] );
        strcat( buf, " nicht vorhanden" );
        break;
     }
   return s;
}

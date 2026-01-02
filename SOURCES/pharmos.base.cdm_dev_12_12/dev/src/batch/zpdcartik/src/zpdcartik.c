/* ---------------------------------------------------------------------- *
 *   Aufgabe        : Datacare Artikel     laden                          *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 26.01.2005                                          *
 *   Autor          : Hörath                                              *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.3.4.1 : zpdcartik 25.02.21 Walid Haddad";
}

/*!
\page page11 zpdcartik - Datacare Artikel laden
___________________________________________________________________________________
\version	1.3.6
\date		25.02.2021
\internal
- WH: CPR-210023 0% Mwst (AT)
- WH: CPR-201327 Kühlkennzeichnung COVID 19 Impfstoffe (AT)
\endinternal
___________________________________________________________________________________
\version	1.3.5
\date		05.05.2020
\internal
- WH: CPR-200362 neuer Wert für vertrbind_sp
\endinternal
___________________________________________________________________________________
\version	1.3.4.1
\date		03.07.2019
\internal
- TH: SR-19068900 neuer Wert "W" für DC_ARTIKELGRUPPE
\endinternal
___________________________________________________________________________________
\version	1.3.4.0
\date		04.04.2019
\internal
- TH: CPR-190326 neuer Wert "L" für DC_ARTIKELGRUPPE
\endinternal
___________________________________________________________________________________
\version	1.3.3.1
\date		17.04.2018
\internal
- TH: Bugfix bei Berechnung PL_FAELSCHSICHER
- TH: keine Berechnung von PL_THERAPIEGRP mehr - wird nicht übernommen / angezeigt!
\endinternal
___________________________________________________________________________________
\version	1.3.3.0
\date		09.01.2018
\internal
- TH: SR-18002614 Psychotrop
- TH: BatchTracking ==> DC_FAELSCHSICHER
\endinternal
___________________________________________________________________________________
\version	1.3.2.0
\date		01.03.2016
\internal
- TH: CR-15D146 Antibiotikum
\endinternal
___________________________________________________________________________________
\version	1.3.1.0
\date		03.12.2015
\internal
- TH: zwingender Fehler bei Änderung Mwst auf 13%
\endinternal
___________________________________________________________________________________
\version	1.3.0.1
\date		11.11.2015
\internal
- TH: Korrektur Stelle Biosiegel
\endinternal
_______________________________________________________________________________________
\version	1.3.0.0
\date		06.11.2015
\internal
- TH: 3. Mwst
\endinternal
_______________________________________________________________________________________
\version	1.2.2.1
\date		17.09.2015
\internal
- DZ: CR-15D107 Erweiterung um Biosiegel
\endinternal
_______________________________________________________________________________________
\version	1.2.2.0
\date		07.05.2015
\internal
- TH: CR-SA0131 = Handling Hochpreis
\endinternal
_______________________________________________________________________________________
\version	1.2.1.5
\date		02.12.2014
\internal
- TH: SR-14030569 = bei hochpreisigen Artikel die Warengruppe nicht überschreiben
\endinternal
______________________________________________________________________________________
\version	1.2.1.4
\date		10.04.2014
\internal
- TH: wandeln mit neuer zartikel/zartpreis-Struktur
\endinternal

*/

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include <hdatum/phodate.h>

#include "g_dcartik.h"


/*  1.0.0.0 26/01/2005 
	1.0.0.1 04/03/2005 Aenderung Taxberechnung
	1.0.1.0 18/03/2005 Anpassung an Anforderungen aus Test Österreich
	1.0.1.1 05/04/2005 Fehlerbeseitigung bei Preistest; 
					   Oeko-KZ nicht mehr auf Plausi prüfen
    1.0.1.2 25/04/2005 Änderungstest auf Artikeltext ( nicht Kurztext )
					   ZWING7 erweitert um Box=N + TAX=2 --> korrekt
	1.0.1.3 23/05/2005 nach Update / Insert / Delete auf zdcoart --> 
					   in Protokoll-Tabellen schreiben
	1.0.1.4 24/05/2005 Neuer gültiger Wert "N" für DC-Artikelgruppe
	1.0.1.5 19/07/2005 Zwing. Fehler 3 nur wenn adopt_abez_from_dc == '1'
	1.0.1.6 31/08/2005 DC_ARTIKELKZ -> neuer gültiger Wert 'S'
	1.0.2.0 21/01/2008 DC_TAXKZ -> neuer gültiger Wert 'E'
	1.0.2.1 25/11/2008 zurücksetzen iArtText15Changed +  ab 01.01.2009 Suchtgiftzuschlag 55 Cent
	1.0.2.2 17/12/2008 RR: Korrektur Rundungsfehler in kf_rund.c 
	1.1.0.0 23/12/2009 TH: neue Datacare- Struktur
	1.1.0.1 04/01/2010 TH: neue Automatismen zum Füllen der Warengruppe
	1.1.0.2 28/04/2011 TH: bei Neuanlagen wird zartpreis.datumgueltigab auf den nächsten Tag gesetzt.
	1.1.1.0 20/12/2011 TH: ab 2012 wird der Suchtgiftzuschlag schon VOR der Berechnung der Mwst addiert
	1.1.1.1 25/07/2012 TH: voodoo table header
	1.2.0.0 18/03/2013 TH: AIX build
	1.2.1.0 09/04/2013 TH: CR-Logistics, 13D020 
	1.2.1.1 02/07/2013 TH: DC_ARTIKELGRUPPE statt ARTIKELKZ zum automatischen Setzen von Warengruppe 02200 heranziehen 
	1.2.1.2 05/02/2014 TH: CR-12D099 zdcart.dc_ean_nr
	1.2.1.3 11/03/2014 TH: Erweiterung zartikel
	1.2.1.4 10.04.2014 TH: wandeln mit neuer zartikel/zartpreis-Struktur
	1.2.1.5 02.12.2014 TH: SR-14030569 = bei hochpreisigen Artikel die Warengruppe nicht überschreiben
	1.2.2.0 07.05.2015 TH: CR-SA0131 = Handling Hochpreis
	1.2.2.1 17.09.2015 DZ: CR-15D107 Erweiterung um Biosiegel
	1.3.0.0 06.11.2015 TH: 3. Mwst 
	1.3.0.1 11.11.2015 TH: Korrektur Stelle Biosiegel
*/




/* ------------------------------------------------------------------- */
/* name of std - function !!! --> link errors
void round( double *wert, int stellen )
{
   if ( stellen >= 0 )
   {

      int i;
      double rund = 1.0;
      double result;
      double rest;

      for ( i = 0; i < stellen; i++ ) rund *= 10.0;

      i = 1;
      result = *wert;
      if ( result < 0.0 )
      {
         result = -result;
         i = -1;
      }

      rest = modf( result*rund + 0.5, &result );

      // so laeuft das auch unter UNIX hajo richtig 
      if ( rest >= 0.99999999999 ) result += 1.0;

      result /= rund;
      if ( i == 1 )
        *wert = result;
      else
        *wert = -result;
   }
}
*/

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

/* ------------------------------------------------------------------- */
void UpdateStatistics( const char * const relation )
{
   char sql[100];
   strcpy( sql, "update statistics for table " );
   strcat( sql, relation );
   SqlExecuteImm( sql );
}

/* ---------------- Programm-Ausahl ----------------- */
static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

/* ---------------------------------------------------------------------- */
static void LadeUsage( char *buf )
{
  strcat( buf, "1. zpdcartik 1 database ili-Verzeichnis \n" \
               "   laedt die datacare-datei in die Relation zdcart\n"\
               "   ili-Verzeichnis: Pfadname, unter dem datacare.txt liegt\n" );
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
        if ( argc == 3 )
        {
           s = GenDCArtNeu( argv[1], argv[2], buf );
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

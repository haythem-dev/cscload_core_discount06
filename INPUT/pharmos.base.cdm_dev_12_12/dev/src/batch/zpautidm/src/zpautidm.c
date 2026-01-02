/* ---------------------------------------------------------------------- *
 *                            ZPAUTIDM.C                                  *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : AUT IDEM Artikel auf 3                              *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 29.05.02                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.2.0 zpautidm : 19.03.2013 : Rolf Raab ";
}

/*!
\page page5 zpautidm

________________________________________________________________________________________
\version	1.2.0
\date		19.03.2013
\internal
- TH: AIX build
\endinternal
________________________________________________________________________________________
\version	1.1.6
\date		25.07.2012
\internal
- TH: voodoo table header
\endinternal
________________________________________________________________________________________
\version	1.1.5
\date		15.05.2012
\internal
- TH: PZN 8
\endinternal
________________________________________________________________________________________
\version	1.1.4
\date		08.07.08
\internal
- RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, Ausgabe Log auch bei Aufruf aus Windows (EkZdp).
\endinternal
________________________________________________________________________________________
\version	1.1.3
\date		04.01.06
\internal
- RR: direkter Aufruf von OpenBufferDescProj im GetBufferDesc_Zartikel (weil sonst immer mit 'select *' gelesen wird und das Probleme geben kann.
\endinternal

*/




/* 1.0.0  29.05.02    Aut Idem Artikel aus PZN-Datei kennzeichen   */
/* 1.0.1  09.07.02    Aut Idem Artikel Retourensperre ruecksetzen  */
/* 1.0.2  16.07.02    Aut Idem: anstatt F in logfile W  */
/* 1.0.3  04.09.02    SetAutidemArtikel ( ZdpUtil )  */
/* 1.0.4  13.12.02    Feld BSSICHG in ZARTIKEL  */
/* 1.0.5  24.01.03    Felder ANBIETERABSCHLAG, AUTIDEMARTIKEL, */
/*                    FESTBETRARTIKEL, DATUM_ABSCHLAG in ZARTIKEL  */
/* 1.0.6  06.03.03    Neue Felder  REZEPTURARZNEI MEDIZINPRODUKT IMPFSTOFF CE_KENNZEICHEN  */
/*                    ARZNEIMITTEL KONTRAZEPTIVUM in ZARTIKEL ( - ) */
/* 1.0.7  13.06.03    Feld ZENTRALPPELIST in ZARTIKEL  */
/* 1.0.8  01/08/03    neues Feld EKORIGINALHS */
/* 1.0.9  08.11.03    Umstellung auf variable Datenbank  */
/* 1.1.0  13.11.03    Neues Feld HILFSM_VERBRAUCH in zartikel */
/* 1.1.1  06.04.05	  TH: wandeln mit neuer zartikel-Struktur (psychotrop) */
/* 1.1.2  01.12.05	  RR: wandeln mit neuer zartikel-Struktur */
/* 1.1.3  04.01.06	  RR: direkter Aufruf von OpenBufferDescProj im GetBufferDesc_Zartikel */
/*					      (weil sonst immer mit 'select *' gelesen wird und das Probleme geben kann */
/* 1.1.4  08.07.08	  RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						  Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.1.5  15.05.2012  TH: PZN 8 */
/* 1.1.6  25.07.2012  TH: voodoo table header */
/* 1.2.0  19.03.2013  TH: AIX build */




/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>

/* ----- Prototype --------- */

void InitAutidemUsage( char *buf );
long InitAutidemArtikel( char *db, char *cmode, char *user, char *cdatei, char *ccount, char *buf );
long InitAutidemArtikelOhne( char *db, char *cmode, char *user, char *cdatei, char *ccount, char *buf );
long SetAutidemArtikel( char *db, char *user, char *cdatei, char *ccount, char *buf );

void AutidemRetSperreUsage( char *buf );
long AutidemRetSperre( char *db, char *ctage, char *user, char *buf );

/* ----- Eroeffnung --------- */

/* --- SET ISOLATION-Fehler bei SE -------------------------------------- */

#define SQL_SETISOLA_ERROR   (-554)

void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

long OpenBase( char *db, char *errmld )
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


void ProgUsage( char *buf )
{
   Usage( buf );
   InitAutidemUsage( buf );
   AutidemRetSperreUsage( buf );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   switch ( *argv[0] )
   {
	  case '0':
        if ( argc == 4 ) 
           s = SetAutidemArtikel ( argv[1], argv[2], argv[3], NULL, buf );
		else if ( argc == 5 ) 
		   s = SetAutidemArtikel ( argv[1], argv[2], argv[3], argv[4], buf );
        else
        {
          s = 1;
          Usage( buf );
          InitAutidemUsage( buf );
        }
        break;
      case '1':
        if ( argc == 5 ) 
           s = InitAutidemArtikel ( argv[1], argv[2], argv[3], argv[4], NULL, buf );
		else if ( argc == 6 ) 
		   s = InitAutidemArtikel ( argv[1], argv[2], argv[3], argv[4], argv[5], buf );
        else
        {
          s = 1;
          Usage( buf );
          InitAutidemUsage( buf );
        }
        break;
      case '2':
        if ( argc == 5 ) 
           s = InitAutidemArtikelOhne ( argv[1], argv[2], argv[3], argv[4], NULL, buf );
		else if ( argc == 6 ) 
		   s = InitAutidemArtikelOhne ( argv[1], argv[2], argv[3], argv[4], argv[5], buf );
        else
        {
          s = 1;
          Usage( buf );
          InitAutidemUsage( buf );
        }
        break;
      case '3':
        if ( argc == 3 ) 
		   s = AutidemRetSperre( argv[1], argv[2], "ZPAUTIDM", buf );
        else
        {
          s = 1;
          Usage( buf );
          AutidemRetSperreUsage( buf );
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


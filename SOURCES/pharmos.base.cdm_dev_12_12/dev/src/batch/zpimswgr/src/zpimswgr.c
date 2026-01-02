
/* ---------------------------------------------------------------------- *
 *                            ZPIMSWGR. C                                 *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : IMS Warengruppen laden                              *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 24.09.98                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 4.2.0 : zpimswgr 15/03/2013 : Rolf Raab";
}

/*!
\page page21 zpimswgr - IMS Warengruppen laden
___________________________________________________________________________
\version	4.2.0
\date		15.03.2013
\internal
- TH: AIX build
\endinternal
___________________________________________________________________________
\version	4.1.5
\date		15.05.2012
\internal
- TH: PZN 8
\endinternal
___________________________________________________________________________
\version	4.1.4
\date		08.07.2008
\internal
- RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, Ausgabe Log auch bei Aufruf aus Windows (EkZdp).
\endinternal

*/

/* 4.0.1  10.08.2000 */
/* 4.0.2  10.04.2002 Umstellung auf wpp-Pflege */
/* 4.0.3  23.12.2002 BSSICHG */
/* 4.0.4  24.01.2003 BSSICHG abschalten wegen IFA-Pflege (ABSCHLAG, AUTIDEMARTIKEL, */
/*                   FESTBETRARTIKEL, DATUM_ABSCHLAG in ZARTIKEL)  */
/*					 BSSICHG kann wieder eingeschaltet werden mit  */
/*                   #define MIT_BSSICHG in g_imsart.c und u_imsart.c */
/* 4.0.5  06.03.2003 Neue Felder  REZEPTURARZNEI MEDIZINPRODUKT IMPFSTOFF CE_KENNZEICHEN */
/*                   ARZNEIMITTEL KONTRAZEPTIVUM in ZARTIKEL ( - ) */
/* 4.0.6  13.06.2003 Feld ZENTRALPPELIST in ZARTIKEL  */
/* 4.0.7  01.08.2003 neues Feld EKORIGINALHS */
/* 4.0.8  31.10.2003 Umstellung auf variable Datenbank  */
/* 4.0.9  13.11.2003 Neues Feld HILFSM_VERBRAUCH in zartikel */
/* 4.1.0  06.04.2005 TH: wandeln mit neuer zartikel-Struktur (psychotrop) */
/* 4.1.1  13.04.2005 KH: zgrppflege mit versorgen */
/* 4.1.2  24.02.2006 RR: Rabattgruppe (zartwg; art = 9) mit versorgen */
/* 4.1.3  27.02.2006 RR: Rabattgruppe bei artkatg-Update berücksichtigen */
/* 4.1.4  08.07.2008 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						 Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 4.1.5  15.05.2012 TH: PZN 8 */
/* 4.2.0  15.03.2013 TH: AIX build */


/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>


/* ----- Prototype --------- */

long GenImsWgr( char *db, char *datei, char *errmld );
long GenImsArt( char *db, char *datei, char *errmld );

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

#ifdef AAA

/* ------- Dateinamen testen -------------- */
/* --- Muster: adr9807.dat --- */

static int IsNum( char *str, int lng )
{
  while ( --lng >= 0 )
    if ( !isdigit( str[lng] ) ) return 0;
  return 1;
}


int TestDateiname( char *file, long *ifadatum, char *errmld )
{
  char datstr[9];
  char numstr[3];
  char *datei;

  int i;
  i = strlen( file ) - 1;
  while ( i >= 0 && file[i] != '/' ) i--;
  i++;

  datei = &file[i];

  *ifadatum = 0;

  if ( strlen( datei )                != 11 ||
       memcmp( datei, "adr", 3 )      !=  0 ||
       memcmp( &datei[7], ".dat", 4 ) !=  0 ||
       !IsNum( &datei[3], 4 )
     )
    {
      strcpy( errmld, "Dateiname im Format\nadrjjnn.dat\n" \
                      "jj=Jahr, nn=Nummer" );
      return 0;
    }

  memcpy( &datstr[2], &datei[3], 2 );
  if ( datei[3] == '9' )
    memcpy( datstr, "19", 2 );
   else
    memcpy( datstr, "20", 2 );
  datstr[4] = '\0';

  memcpy( numstr, &datei[5], 2 );
  numstr[2] = '\0';

  *ifadatum = atol( datstr )*100 + atol( numstr );

  return 1;
}

#endif

/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

static void GenImsWgrUsage( char *buf )
{
  strcat( buf, "1. IMS-Warengruppen laden:\n" \
               "   zpimswgr 1 database imswgrdatei\n" \
               "   laedt die imswgrdatei in die Relation artkatg\n" );
}

static void GenImsArtUsage( char *buf )
{
  strcat( buf, "2. IMS-Warengruppen-Schluessel laden:\n" \
               "   zpimswgr 2 database imsartikeldatei\n" \
               "   laedt die imsartikeldatei in die Relation zartwg\n" );
}


void ProgUsage( char *buf )
{
   Usage( buf );
   GenImsWgrUsage( buf );
   GenImsArtUsage( buf );
}


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
           s = GenImsWgr( argv[1], argv[2], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          GenImsWgrUsage( buf );
        }
        break;

      case '2':
        if ( argc == 3 )
        {
          s = GenImsArt( argv[1], argv[2], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          GenImsArtUsage( buf );
        }
        break;
/*
      case '3':
        if ( argc == 3 )
        {
          s = UpdateHerstel( argv[1], argv[2], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          UpdateUsage( buf );
        }
        break;
*/
      default:
        s = 1;
        strcpy( buf, "Programm-Teil: " );
        strcat( buf, argv[0] );
        strcat( buf, " nicht vorhanden" );
        break;
     }
   return s;
}


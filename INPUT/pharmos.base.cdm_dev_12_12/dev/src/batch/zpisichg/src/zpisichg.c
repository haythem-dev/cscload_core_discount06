/* ---------------------------------------------------------------------- *
 *                            ZPISICHG. C                                 *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Ifa BSSichG Abschlaege laden                        *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 30.03.00                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.3.0 zpisichg : 15/03/2013 : Rolf Raab";

/*!
\page page22 zpisichg - Ifa BSSichG Abschläge laden
___________________________________________________________________________
\version	1.3.0
\date		15.03.2013
\internal
- TH: AIX build
\endinternal
___________________________________________________________________________
\version	1.2.4
\date		25.07.2012
\internal
- TH: voodoo_table_header
\endinternal
___________________________________________________________________________
\version	1.2.3
\date		07.07.2008
\internal
- RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, Ausgabe Log auch bei Aufruf aus Windows (EkZdp).
\endinternal

*/

/* 1.1.0 27.01.2003 : 1. Version */
/* 1.1.1 28.02.2003 : Neues Protokoll bss_prot ( vorher abs_prot ) */
/* 1.1.2 07.03.2003 : Felder REZEPTURARZNEI MEDIZINPRODUKT IMPFSTOFF CE_KENNZEICHEN ARZNEIMITTEL */
/*					  KONTRAZEPTIVUM in ZARTIKEL ( - ) */
/*                    PREISSENKUNG lt. Heidicker in absladen.c */
/* 1.1.3 13.06.2003 : Feld ZENTRALPPELIST in ZARTIKEL  */
/* 1.1.4 01.08.2003 : neues Feld EKORIGINALHS */
/* 1.1.5 07.11.2003 : Umstellung auf variable Datenbank  */
/* 1.1.6 13.11.2003 : Neues Feld HILFSM_VERBRAUCH in zartikel */
/* 1.1.7 16.12.2003 : ifa.C02AUTIDEM wird nicht mehr nach zartikel.AUTIDEMARTIKEL übernommen */
/* 1.1.8 15.01.2004 : Umstellung auf zifaoabschlag ( IFA-Produkt 20127 ) */
/* 1.1.9 10.03.2004 : AUTIDEMARTIKEL durch FESTBETRARTIKEL ersetzen (absladen.c) */
/* 1.2.0 31.01.2005 : RR: C02***BPR (Basispreise) eliminiert (g_ifaoabs.c), Umstellung auf IFA-Produkt 20140 */
/* 1.2.1 06.04.2005 : TH: wandeln mit neuer zartikel-Struktur (psychotrop) */
/* 1.2.2 03.04.2006 : RR: Basispreise (als C05***BPR) wieder mit rein (g_ifaoabs.c), Umstellung auf IFA-Produkt 20153 */
/* 1.2.3 07.07.2008 : RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						  Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.2.4 25.07.2012 : TH: voodoo_table_header */
/* 1.3.0 15.03.2013 : TH: AIX build */



/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>


/* ----- Prototype --------- */

long GenIfaSichgNeu   ( char *db, char *ili_file, char *idd_file, int b_proto, char *errmld );
long UrLoadIfaSichgNeu( char *db, char *ili_direc, char *idd_direc, char *errmld );

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

   s = SqlExecuteImm( "SET LOCK MODE TO WAIT 20" );
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


void UpdateStatistics( char *relation )
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

static void GenUsage( char *buf )
{
  strcat( buf, "1. zpisichg 1 database ili-Verzeichnis [idd-Verzeichnis]\n" \
               "   laedt die ifadatei in die Relation zartikel + zifaoabschlag\n"\
               "   ili-Verzeichnis: Pfadname des ili-Verzeichnisses\n" \
               "   idd-Verzeichnis: Pfadname des idd-Verzeichnisses\n" );
}

static void GenProtoUsage( char *buf )
{
  strcat( buf, "2. zpisichg 2 database ili-Verzeichnis [idd-Verzeichnis]\n" \
               "   laedt die ifadatei in die Relation zartikel + zifaoabschlag mit Protokol\n"\
               "   ili-Verzeichnis: Pfadname des ili-Verzeichnisses\n" \
               "   idd-Verzeichnis: Pfadname des idd-Verzeichnisses\n" );
}

static void LadeUsage( char *buf )
{
  strcat( buf, "3. zpisichg 3 database ili-Verzeichnis [idd-Verzeichnis]\n" \
               "   Urladen der ifadatei in die Relation zifaoabschlag\n"\
               "   ili-Verzeichnis: Pfadname des ili-Verzeichnisses\n" \
               "   idd-Verzeichnis: Pfadname des idd-Verzeichnisses\n" );
}

void ProgUsage( char *buf )
{
   Usage( buf );
   GenUsage( buf );
   GenProtoUsage( buf );
   LadeUsage( buf );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   switch ( *argv[0] )
    {
      case '1':
        if ( argc == 3 )
        {
           s = GenIfaSichgNeu( argv[1], argv[2], ".", 0, buf );
        }
        else if ( argc == 4 )
        {
           s = GenIfaSichgNeu( argv[1], argv[2], argv[3], 0, buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          GenUsage( buf );
        }
        break;

      case '2':
        if ( argc == 3 )
        {
           s = GenIfaSichgNeu( argv[1], argv[2], ".", 1, buf );
        }
        else if ( argc == 4 )
        {
           s = GenIfaSichgNeu( argv[1], argv[2], argv[3], 1, buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          GenProtoUsage( buf );
        }
        break;

      case '3':
        if ( argc == 3 )
        {
           s = UrLoadIfaSichgNeu( argv[1], argv[2], ".", buf );
        }
        else if ( argc == 4 )
        {
           s = UrLoadIfaSichgNeu( argv[1], argv[2], argv[3], buf );
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

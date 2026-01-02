
/* ---------------------------------------------------------------------- *
 *                            ZPIHERST. C                                 *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Ifa Hersteller nach zifaher laden                   *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 24.09.98                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 2.1.3 zpiherst : 06.11.2018 : Rolf Raab";

/*!
\page page20 zpiherst - Ifa Hersteller nach zifaher laden
___________________________________________________________________________
\version	2.1.3
\date		06.11.2018
\internal
- TH: CPR-180813 IFA 20219
\endinternal
___________________________________________________________________________
\version	2.1.2
\date		12.05.15
\internal
- TH: Erweiterung herstel
\endinternal
___________________________________________________________________________
\version	2.1.1
\date		11.03.14
\internal
- TH: Erweiterung herstel
\endinternal
___________________________________________________________________________
\version	2.1.0
\date		15.03.13
\internal
- TH: AIX build
\endinternal
___________________________________________________________________________
\version	2.0.8
\date		25.07.12
\internal
- TH: voodoo table header
\endinternal
___________________________________________________________________________
\version	2.0.7
\date		24.05.11
\internal
- TH: Blank statt "/" als Trennzeichen zwischen Vorwahl und Nummer bei Tel. + Fax
\endinternal

*/

/* 1.0.8  29/03/01: Druck Stern (*) im Protokol wenn Feld nicht gepflegt */
/* 1.0.9  05/04/01: Druck Stern (*) im Protokol wenn Feld gepflegt, Inhalt blank  */
/* 1.1.0  24/05/02: HERSTEL: HERSTELL_VERGUETET, ERSTATTUNGSTAGE */ 
/* 1.1.1  13/06/03: neues Feld ZENTRALPPELIST */
/* 1.1.2  06.11.03  Umstellung auf variable Datenbank  */
/* 1.1.3  17.11.04  RR: wandeln mit neuer herstel-Struktur */
/* 1.1.4  09.05.05  TH: Bei Neuanlage o. Änderung von herstel-Satz schreiben in zgrppflege*/
/* 1.2.0  03.04.06  TH: neue Felder B00HERSTER, B00GHERLAU */
/* 1.2.1  20.04.06  RR: datum_anlage bei Neuanlage füllen */
/* 1.2.2  07.07.08  RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 2.0.0  01.03.10  TH: Umstellung IFA- Produkte von 20165 auf 20171. */
/* 2.0.1  27.04.10  TH: Anpassung Protokoll. */
/* 2.0.2  17.06.10  RR: 2. Trim in IfaToHersteller */
/* 2.0.3  24.08.10  TH: keine "'" bei Schreiben in zifaher erlaubt. */
/* 2.0.4  21.12.10  TH: Konvertierung von Umlauten. */
/* 2.0.5  18.01.11  TH: Korrektur bei Konvertierung von Umlauten. */
/* 2.0.6  02.05.11  TH: Init 5 neue herstel- Felder bei Neuanlagen. */
/* 2.0.7  24.05.11  TH: Blank statt "/" als Trennzeichen zwischen Vorwahl und Nummer bei Tel. + Fax */
/* 2.0.8  25.07.12  TH: voodoo table header */
/* 2.1.0  15.03.13  TH: AIX build */
/* 2.1.1  11.03.14  TH: Erweiterung herstel */
/* 2.1.2  12.05.15  TH: Erweiterung herstel */


/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>


/* ----- Prototype --------- */

long GenIfaHerNeu ( char *db, char *datei, char *idd_file, char *buf );
long DeleteIfaHer ( char *db, long datum, char *buf );
long UpdateHerstel( char *db, long datum, char *mode, char *buf );
long GenIfaProtok ( char* ili_direc, char *idd_direc, char *errmld );


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

static void LadeUsage( char *buf )
{
  strcat( buf, "1. Ifa-Hersteller laden:\n" \
               "   zpiherst 1 database ili-Verzeichnis [idd-Verzeichnis]\n" \
               "   laedt die ifadatei in die Relation zifaher\n" \
               "   ili-Verzeichnis: Pfadname des ili-Verzeichnisses\n" \
               "   idd-Verzeichnis: Pfadname des idd-Verzeichnisses\n" );
}

static void DeleteUsage( char *buf )
{
  strcat( buf, "2. Ifa-Hersteller loeschen:\n"\
               "   zpiherst 2 database ifadatum (jjjjmmtt) \n" \
               "   loescht die ifadatei aus der Relation zifaher\n" );
}

static void UpdateUsage( char *buf )
{
  strcat( buf, "3. Ifa-Hersteller uebertragen:\n"\
               "   zpiherst 3 database ifadatum mode\n" \
               "   uebertraegt zifaher nach herstel\n" );
}

static void IfaProtokUsage( char *buf )
{
  strcat( buf, "4. Ifa-Hersteller Protokoll:\n" \
               "   zpiherst 4 ili-Verzeichnis [idd-Verzeichnis]\n" \
               "   ili-Verzeichnis: Pfadname des ili-Verzeichnisses\n" \
               "   idd-Verzeichnis: Pfadname des idd-Verzeichnisses\n" );
}

void ProgUsage( char *buf )
{
   Usage( buf );
   LadeUsage( buf );
   DeleteUsage( buf );
   UpdateUsage( buf );
   IfaProtokUsage( buf );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   switch ( *argv[0] )
    {
      case '1':
        if ( argc == 3 )
        {
           s = GenIfaHerNeu( argv[1], argv[2], ".",  buf );
           if ( s == 0 )
           {
              char meld[200];
              GenIfaProtok( argv[2], ".", meld );
              strcat( buf, "\n" );
              strcat( buf, meld );
           }
        }
        else if ( argc == 4 )
        {
           s = GenIfaHerNeu( argv[1], argv[2], argv[3], buf );
           if ( s == 0 )
           {
              char meld[200];
              GenIfaProtok( argv[2], argv[3], meld );
              strcat( buf, "\n" );
              strcat( buf, meld );
           }
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

      case '2':
        if ( argc == 3 )
        {
          s = DeleteIfaHer( argv[1], atol( argv[2] ) , buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          DeleteUsage( buf );
        }
        break;
      case '3':
        if ( argc == 4 )
        {
          s = UpdateHerstel( argv[1], atol( argv[2] ) , argv[3], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          UpdateUsage( buf );
        }
        break;

      case '4':
        if ( argc == 2 )
        {
           s = GenIfaProtok( argv[1], ".",  buf );
        }
        else if ( argc == 3 )
        {
           s = GenIfaProtok( argv[1], argv[2], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          IfaProtokUsage( buf );
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



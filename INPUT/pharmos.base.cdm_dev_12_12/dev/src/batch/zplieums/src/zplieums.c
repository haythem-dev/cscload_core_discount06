/* ---------------------------------------------------------------------- *
 *                            ZPLIEUMS. C                                 *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Tausch von Lieferanten_nummern                      *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 26.07.99                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.2.0 : zplieums 15/03/13 : Hajo Schmitt";

/*!
\page page27 zplieums - Tausch von Lieferanten_nummern
___________________________________________________________________________
\version	1.2.0
\date		15.03.2013
\internal
- TH: AIX build
\endinternal
___________________________________________________________________________
\version	1.1.4
\date		25.07.2012
\internal
- TH: voodoo table header
\endinternal
___________________________________________________________________________
\version	1.1.3
\date		05.09.2011
\internal
- HS: Umstellen auf CDC_ALONE
\endinternal
___________________________________________________________________________
\version	1.1.2
\date		08.07.2008
\internal
- RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, Ausgabe Log auch bei Aufruf aus Windows (EkZdp).
\endinternal

*/

/* 1.0.3 29/10/99 neues Feld BESTELLADRESSEPPE in bliefer */
/* 1.0.4 19/04/01 neues Feld MANDATSLAGER in bliefer */
/* 1.0.5 23/05/01 neues Feld NAHRUNGSERGAENZUNG in liefer */
/* 1.0.6 05/11/01 neues Feld ISO_WCODE in liefer, neues Feld FILIALNRMANDAT_LAG in bliefer */
/* 1.0.7 07.11.03 Umstellung auf variable Datenbank  */
/* 1.0.8 20.03.04 neues Feld SAP_LANTNEU in liefer */
/* 1.0.9 17.08.04 RR: neue Tabelle zliefsapr3 */
/* 1.1.0 17.11.04 RR: wandeln mit neuer liefer-Struktur */
/* 1.1.1 19.01.06 RR: alle select * auf Projektionen umgestellt,
/* 					  direkter Aufruf von OpenBufferDescProj in GetBufferDesc_xxx */
/*				      (weil sonst immer mit 'select *' gelesen wird und das Probleme geben kann */
/* 1.1.2 08.07.08 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
					  Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.1.3 05.09.11 HS: Umstellen auf CDC_ALONE */
/* 1.1.4 25.07.12 TH: voodoo table header */
/* 1.2.0 15.03.13 TH: AIX build */


/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>


/* ----- Prototype --------- */

/* ------------ Tausch Hersteller ----------- */

long LieUmsLoop ( char *db, char *user, int anz, char* LantNr[], char *buf  );
void LieUmsUsage( char *buf );

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
   LieUmsUsage ( buf );
}

long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   switch ( *argv[0] )
    {
      case '1':
/*
        if ( argc > 2 && (argc-2)%2 == 0 )
        {
          int anz;
          anz = (argc - 1 )/2;
          s = LieUmsLoop( argv[1], (argc-2)/2, &argv[2], buf );
        }
*/
        if ( argc > 3 && (argc-3)%2 == 0 )
        {
          int anz;
          anz = (argc - 2 )/2;
          s = LieUmsLoop( argv[1], argv[2], (argc-3)/2, &argv[3], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LieUmsUsage( buf );
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


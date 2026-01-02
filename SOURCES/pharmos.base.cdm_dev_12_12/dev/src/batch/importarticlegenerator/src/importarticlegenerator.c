/* ---------------------------------------------------------------------- *
 *   Aufgabe        : Import Artikel (D-Besorger) laden                   *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 23.03.2018                                          *
 *   Autor          : Thomas Hörath                                       *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.0.3.2 : importarticlegenerator 27/03/2019 Thomas Hoerath";

/*!
\page page41 importarticlegenerator - Import Artikel (D-Besorger) laden
___________________________________________________________________________
\version	1.0.3.2
\date		27.03.2019
\internal
- TH: init zartikel.chargenartikel bei Neuanlagen in DE & AT
- TH: in AT ist der internen Nummernkreis künftig ohne Prüfziffer
\endinternal
___________________________________________________________________________
\version	1.0.3.1
\date		15.03.2019
\internal
- TH: INC-19011969 = EAN soll grundsätzlich nicht mehr aus D übernommen werden.
\endinternal
___________________________________________________________________________
\version	1.0.3.0
\date		25.01.2019
\internal
- TH: Übernahme NTIN aus D
\endinternal
___________________________________________________________________________
\version	1.0.2.0
\date		08.01.2019
\internal
- TH: I-18059449 --> zgrppflege (20) für Hersteller-Neuanlagen/ -Änderungen
- TH: SQL-Fehler "-346" abgefangen bei Update EAN
\endinternal
___________________________________________________________________________
\version	1.0.1.0
\date		13.07.2018
\internal
- TH: bugfix tages_datum
\endinternal
___________________________________________________________________________
\version	1.0.0.0
\date		23.03.2018
\internal
- TH: first shot
\endinternal

*/

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

#include "g_impartik.h"


/* ------------------------------------------------------------------- */
#define SQL_SETISOLA_ERROR (-554)
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

/* ---------------------------------------------------------------------- */
void ProgUsage( char *buf )
{
  strcpy( buf, "usage:\n" );
  strcat( buf, "1. importarticlegenerator mode dbimp dbexp countryimp countryexp datefrom \n"
			   "   mode 1:	 laedt Daten für D-Besorger\n"
               "   dbimp: usually 'iat21'\n"
			   "   dbexp: usually 'ide21@ide_tcp'\n"
			   "   countryimp: usually 'A'\n"
			   "   countryexp: usually 'D'\n"
			   "   datefrom: date of last run = look for manufacturer changes in this period (dd.mm.yyyy)\n");
}

/* ---------------------------------------------------------------------- */
long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   switch ( *argv[0] )
    {
      case '1':
        if ( argc == 6 )
        {
           s = GenImport( argv[1], argv[2], argv[3], argv[4], argv[5], buf );
		}
        else
        {
          s = 1;
          ProgUsage( buf );
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

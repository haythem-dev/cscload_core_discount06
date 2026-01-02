/* ---------------------------------------------------------------------- *
 *                            ZPDEFPA.C                                   *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : AUT IDEM Artikel auf 3                              *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 29.05.02                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.1.0 zpdefpa : 18.03.13 : Rolf Raab ";

/*!
\page page13 zpdefpa - AUT IDEM Artikel auf 3
_______________________________________________________________________________________
\version	1.1.0
\date		18.03.13
\internal
- AIX build
\endinternal
_______________________________________________________________________________________
\version	1.0.2
\date		07.07.08
\internal
- RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, Ausgabe Log auch bei Aufruf aus Windows (EkZdp).
\endinternal
_______________________________________________________________________________________
\version	1.0.1
\date		08.11.03
\internal
- Umstellung auf variable Datenbank
\endinternal

*/

/* 1.0.1 08.11.03 Umstellung auf variable Datenbank  */
/* 1.0.2 07.07.08 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						 Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.1.0 18.03.13 AIX build  */


/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>

/* ----- Prototype --------- */

long GenDefpaIfanr   ( char *db, char *datei, long *ifanr, int anz, char *errmld );
long GenDefpaZeitraum( char *db, char *datei, long datumvon, long datumbis, char *errmld );

void GenDefpaUsage( char *buf );

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

static int OnlyZiffern( char *str )
{
	do
	{
		if ( !isdigit( *str ) ) return 0;
		str++;
	}	while ( *str );
	return 1;
}


static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

void ProgUsage( char *buf )
{
   Usage( buf );
   GenDefpaUsage( buf );
}

#define MAX_IFANR 50

long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   switch ( *argv[0] )
   {
      case '1':
        if ( argc > 3 ) 
		{
		   int i;
           long ifanr[MAX_IFANR];
		   if ( argc < MAX_IFANR + 3 )
		   {
			    int ok;
				ok = 1;
			    i  = 3;
				while ( i < argc && ok )
				{
					ok = OnlyZiffern( argv[i] );
					if ( ok )
					{
						ifanr[i-3] = atoi( argv[i] ); 
						i++;
					}
				}
				if ( ok )
					s = GenDefpaIfanr ( argv[1], argv[2], ifanr, i-3, buf );
				else
				{
					s = 1;
					strcpy( buf, "IfaNummern numerisch\n" );
				}
		   }
		   else
		   {
			   s = 1;
			   sprintf( buf, "nur %d IfaNummern erlaubt\n", MAX_IFANR );
		   }
		}
        else
        {
          s = 1;
          Usage( buf );
          GenDefpaUsage( buf );
        }
        break;
      case '2':
        if ( argc == 5 ) 
		{
			if ( OnlyZiffern( argv[3] ) && OnlyZiffern( argv[4] ) )
				s = GenDefpaZeitraum ( argv[1], argv[2], atol(argv[3]), atol(argv[4]), buf );
			else
				strcpy( buf, "Datum numerisch\n" );
		}
        else
        {
          s = 1;
          Usage( buf );
          GenDefpaUsage( buf );
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


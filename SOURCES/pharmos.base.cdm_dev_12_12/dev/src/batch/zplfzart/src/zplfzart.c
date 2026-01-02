/* ---------------------------------------------------------------------- *
 *   Aufgabe        : MWE-Maße und Gewichte in zartikel laden             *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 19.09.2007                                          *
 *   Autor          : Rolf Raab                                           *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.2.3 : zplfzart 05/04/2015 Rolf Raab";
}

/*!
\page page25 zplfzart - MWE-Maße und Gewichte in zartikel laden
___________________________________________________________________________
\version	1.2.3
\date		05.04.2020
\internal
- KT: I-22003715: test for valid PZN in MWELieferung() (g_lfzartik.c) not for CH (ich21 and ich21pre)
\endinternal
___________________________________________________________________________
\version	1.2.2
\date		24.09.2015
\internal
- TH: CR-15D080
\endinternal
___________________________________________________________________________
\version	1.2.1
\date		16.07.2015
\internal
- TH: kompilieren mit neuer zartikel-Struktur
\endinternal
___________________________________________________________________________
\version	1.2.0
\date		18.12.2014
\internal
- TH: modes 3 + 4 für CR-14P036
\endinternal
___________________________________________________________________________
\version	1.1.4
\date		10.04.2014
\internal
- TH: wandeln mit neuer zartikel/zartpreis-Struktur
\endinternal
___________________________________________________________________________
\version	1.1.3
\date		11.03.2014
\internal
- TH: kompilieren mit neuer zartikel-Struktur
\endinternal
___________________________________________________________________________
\version	1.1.2
\date		02.12.2013
\internal
- TH: kompilieren mit neuer zartswitzerland-Struktur
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

#include "g_lfzartik.h"
#include "g_lfean.h"
#include "g_lfhealthinsurance.h"
#include "g_lfatc.h"

/* 1.0.1  08.07.2008 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						 Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.0.2  04.08.2008 RR: neue Funktion laden der Tabelle ean aus EAN-Datei */
/* 1.0.3  16.09.2008 RR: in zapflege immer mit Datum des Folgetags schreiben */
/* 1.0.4  24.11.2009 RR: kompilieren mit neuer zartikel-Struktur */
/* 1.0.5  14.04.2010 RR: kompilieren mit neuer zartikel-Struktur */
/* 1.0.6  12.10.2011 RR: kompilieren mit neuer zartikel-Struktur */
/* 1.0.7  22.05.2012 RR: kompilieren mit neuer zartikel-Struktur */
/* 1.0.8  25.07.2012 TH: voodoo table header */
/* 1.0.9  10.09.2012 RR: kompilieren mit neuer zartikel-Struktur */
/* 1.1.0  15.03.2013 TH: AIX build */
/* 1.1.1  28.03.2013 TH: kompilieren mit neuer zartikel-Struktur */
/* 1.1.2  02.12.2013 TH: kompilieren mit neuer zartswitzerland-Struktur */
/* 1.1.3  11.03.2014 TH: kompilieren mit neuer zartikel-Struktur */
/* 1.1.4  10.04.2014 TH: wandeln mit neuer zartikel/zartpreis-Struktur */
/* 1.2.0  18.12.2014 TH: modes 3 + 4 für CR-14P036 */
/* 1.2.1  16.07.2015 TH: kompilieren mit neuer zartikel-Struktur */
/* 1.2.2  24.09.2015 TH: CR-15D080 */


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
  strcat( buf, "zplfzart 1 database Verzeichnis \n" \
               "           laedt die Maße und Gewichte aus der MWE-Datei in zartikel\n" \
			   "         2 database Verzeichnis \n" \
               "           laedt die EAN-PZN-Kombinationen aus der EAN-Datei in ean\n" \
			   "         3 database Verzeichnis_der_Krankenkassen-Datei_von_ABDA \n" \
               "           laedt die Krankenkassendaten in chealthinsurance und chealthinsurancearticles\n" \
			   "         4 database Verzeichnis_der_ATC-Datei_von_ABDA \n" \
               "           laedt die ABDA-ATC-Codes in carticlecodes (code_type=2)\n");
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
           s = Load_MWE_Daten( argv[1], argv[2], buf );
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
           s = Load_EAN_Daten( argv[1], argv[2], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

		case '3':
		if ( argc == 3 )
        {
           s = Load_HealthInsurance_Daten( argv[1], argv[2], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

		case '4':
		if ( argc == 3 )
        {
           s = Load_AbdaATC_Daten( argv[1], argv[2], buf );
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

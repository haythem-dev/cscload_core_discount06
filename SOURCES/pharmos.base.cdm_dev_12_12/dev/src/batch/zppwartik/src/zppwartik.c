/* ---------------------------------------------------------------------- *
 *   Aufgabe        : PreWhole Artikel (Teva) laden                       *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 28.12.2012                                          *
 *   Autor          : Thomas Hörath                                       *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.1.2.7 : zppwartik 06/04/2017 Thomas Hoerath";
}

/*!
\page page32 zppwartik - PreWhole Artikel (Teva) laden
___________________________________________________________________________
\version	1.1.2.7
\date		06.04.2017
\internal
- TH: Änderung Temperaturvorschrift bei Ratiopharm
\endinternal
___________________________________________________________________________
\version	1.1.2.6
\date		16.07.2015
\internal
- TH: wandeln mit neuer zartikel-Struktur
\endinternal
___________________________________________________________________________
\version	1.1.2.5
\date		29.06.2015
\internal
- TH: SR-15025045: Umlaute auch im Langnamen entfernen
\endinternal
___________________________________________________________________________
\version	1.1.2.4
\date		24.07.2014
\internal
- TH: zpznpflege "39" auch bei impliziter Umbuchung der Pseudo- PZN (Nachfolger) bei Löschung der Original-PZN (Vorgänger).
\endinternal
___________________________________________________________________________
\version	1.1.2.3
\date		23.05.2014
\internal
- TH: zpznpflege "33" für artikel_langname (P-14000013)
\endinternal
___________________________________________________________________________
\version	1.1.2.2
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
#include <libscsvoodoo.h>
#include <phodate.h>

#include "g_pwartik.h"

/*
	1.0.0.0 07/01/2013 TH	first issue
	1.1.0.0 13/03/2013 TH	AIX build
	1.1.0.1 21/03/2013 TH	SA 3A
	1.1.1.0 09/04/2013 TH	copy zartaustria
	1.1.1.1 04.06.2013 TH   Erweiterung zartpreis
	1.1.1.2 11.03.2014 TH   Erweiterung zartikel
	1.1.2.0 19.03.2014 TH   Init´s zartikel
	1.1.2.1 03.04.2014 TH   Update zartpreis
	1.1.2.2 10.04.2014 TH   wandeln mit neuer zartikel/zartpreis-Struktur
	1.1.2.3 23.05.2014 TH   zpznpflege "33" für artikel_langname (P-14000013)
	1.1.2.4 24.07.2014 TH   zpznpflege "39" auch bei impliziter Umbuchung der Pseudo- PZN (Nachfolger) bei Löschung der Original-PZN (Vorgänger)
	1.1.2.5 29.06.2015 TH   SR-15025045: Umlaute auch im Langnamen entfernen
	1.1.2.6 16.07.2015 TH   wandeln mit neuer zartikel-Struktur
*/



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
  strcat( buf, "1. zppwartik mode database datei \n"
			   "   mode 1:	 laedt die Daten der teva-datei in die Relationen zartikel/zartpreis\n"
               "   database: usually 'iat21pre'\n"
               "   datei: Pfad und Dateiname --> Angabe MASTER_OUT- Datei von Ratiopharm.\n" );
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
           s = GenPwArtik( argv[1], argv[2], buf );
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

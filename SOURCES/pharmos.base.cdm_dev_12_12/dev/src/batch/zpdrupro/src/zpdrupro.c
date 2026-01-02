
/* ---------------------------------------------------------------------- *
 *                            ZPDRUPRO. C                                 *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Druck Protokoll                                     *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 07.10.98                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 2.1.0 zpdrupro : 18/03/2013 : Hajo Schmitt";

/*!
\page page14 zpdrupro - Druck Protokoll
______________________________________________________________
\version	2.1.0
\date		18.03.2013
\internal
- TH: AIX build
\endinternal
___________________________________________________________________________
\version	2.0.9
\date		14.11.2012
\internal
- TH: Key bei Artikel- Protokollen auf PZN 8 umgestellt
\endinternal
___________________________________________________________________________
\version	2.0.8
\date		25.07.2012
\internal
- TH: voodoo table header
\endinternal
___________________________________________________________________________
\version	2.0.7
\date		07.07.2008
\internal
- RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, Ausgabe Log auch bei Aufruf aus Windows (EkZdp).
\endinternal

*/

/* 2.0.2 03.11.2003 Umstellung auf variable Datenbank  */
/* 2.0.3 22.04.2005 RR: Fehlerkorrektur in get_keysel */
/* 2.0.4 25.04.2005 TH: Datum in Historien-File-Name */
/* 2.0.5 30.08.2005 TH: PZN + MC als Schlüsselbegriff bei Artikelprotokoll;
						zartwg.art = '7' -> Feldbezeichnung = "Artikeltext";
						bei Aufruf 'ohne IFA' auch Änderungen von User 'dc' ausschließen;
						bei relation auch carticlelang + zartswitzerlang lesen.*/
/* 2.0.6 24.10.2005 TH: Korrektur bei Aufruf "Show_Preis" -> diffsqld eingesetzt, so dass 
						Preisänderungen gedruckt werden!*/
/* 2.0.7 07.07.2008 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 2.0.8 25.07.2012 TH: voodoo table header */
/* 2.0.9 14.11.2012 TH: Key bei Artikel- Protokollen auf PZN 8 umgestellt */
/* 2.1.0 18.03.2013 TH: AIX build */


/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* ----- Prototype --------- */

long ArtikelProtokol  ( char *db, char *param, char *von_datum, char *bis_datum,
                        char *buf );
long RelationProtokol ( char *db, char *relation, char *param,
                        char *von_datum, char *bis_datum, char *buf );

/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

static void ArtikelUsage( char *buf )
{
  strcat( buf, "1. zpdrupro 1 database -[ips] [von_datum [bis_datum]]\n" \
               "   Druck Artikel-Protokoll von_datum bis_datum\n" );
}

static void RelationUsage( char *buf )
{
  strcat( buf, "2. zpdrupro 2 database relation -[ips] [von_datum [bis_datum]]\n" \
               "   Druck Protokoll der relation von_datum bis_datum\n" );
}

static void AllesUsage( char *buf )
{
  strcat( buf, "   i: 0 -> ohne IFA (default)\n" \
               "      1 -> mit  IFA\n" \
               "   p: 1 -> Aenderungen (default)\n" \
               "      2 -> Neuaufnahmen\n" \
               "      4 -> Loeschungen\n" \
               "      3,5,6,7 -> Kombinationen aus 1,2,4\n" \
               "   s: 0 -> Sort ProtokolNr (default)\n" \
               "      1 -> Sort PrimeKey\n" \
               "   von_datum leer, bis_datum leer -> heute\n" \
               "   bis_datum leer                 -> von_datum\n" );

}

void ProgUsage( char *buf )
{
  ArtikelUsage ( buf );
  RelationUsage( buf );
  AllesUsage   ( buf );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   switch ( *argv[0] )
    {
      case '1':
        if ( argc == 3 )
           s = ArtikelProtokol( argv[1], argv[2], NULL, NULL, buf );
        else if ( argc == 4 )
           s = ArtikelProtokol( argv[1], argv[2], argv[3], NULL, buf );
        else if ( argc == 5 )
           s = ArtikelProtokol( argv[1], argv[2], argv[3], argv[4], buf );
        else
        {
          s = 1;
          Usage( buf );
          ArtikelUsage( buf );
          AllesUsage  ( buf );
        }
        break;

      case '2':
        if ( argc == 4 )
          s = RelationProtokol( argv[1], argv[2], argv[3], NULL, NULL, buf );
        else if ( argc == 5 )
          s = RelationProtokol( argv[1], argv[2], argv[3], argv[4], NULL, buf );
        else if ( argc == 6 )
          s = RelationProtokol( argv[1], argv[2], argv[3], argv[4], argv[5], buf );
        else
        {
          s = 1;
          Usage( buf );
          RelationUsage( buf );
          AllesUsage   ( buf );
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




/* ---------------------------------------------------------------------- *
 *                            ZPISICLF.c                                   *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Ifa verwalten                                       *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 07.07.00                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.2.0 zpisiclf : 15.03.2013 : Rolf Raab";

/*!
\page page23 zpisiclf - Ifa verwalten
___________________________________________________________________________
\version	1.2.0
\date		15.03.2013
\internal
- TH: AIX build
\endinternal
___________________________________________________________________________
\version	1.1.1
\date		07.07.2008
\internal
- RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, Ausgabe Log auch bei Aufruf aus Windows (EkZdp)
\endinternal

*/

/* 1.1.1  07.07.2008 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						 Ausgabe Log auch bei Aufruf aus Windows (EkZdp)
   1.2.0  15.03.2013 TH: AIX build */


/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* ----- Prototype --------- */

long GetIfaVerz( char *SatzartMode, char *buf, int gepackt );
long CreateIfaVerz( char* QuellDirec, char *buf, int WithCopy );

/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

static void GetIfaVerzUsage( char *buf )
{
  strcat( buf, "1. Ifabssig-Verzeichnisse lesen:\n" \
               "   zpisiclf 1 [mode] [p]\n" \
               "     gibt die Ifabssig-Verzeichnisse aus\n" \
               "     ohne mode: alle Verzeichnisse\n" \
               "     mode = 0:  alle Verz. mit BSSichGStatus = unbearbeitet\n" \
               "     mode = 9:  alle Verz. mit Unterverzeichnis 'protokol'\n" \
               "     p       :  wenn mit p, dann Ausgabe gepackt\n" );
}

static void CreateIfaVerzUsage( char *buf )
{
  strcat( buf, "2. Ifabssig-Verzeichnis erstellen:\n"\
               "   zpisiclf 2 [Quellverzeichnis] [c]\n" \
/*             "     erstellt im Verzeichnis $WWS/daten/Ifabssig\n"  \ */
               "     erstellt im Verzeichnis $WWS/de/cdm/data/ifa_bssichg\n"  \
               "     ein neues IFA-Verzeichnis der Form lf000000\n" \
               "     Quellverzeichnis: Verzeichnis der IFA-Dateien\n"\
/*			   "              default: $WWS/daten/Ifabssig/fdakt\n" \ */
               "              default: $WWS/de/cdm/data/ifa_bssig/lfakt\n" \
               "     c: Kopieren der Ifa-Dateien aus dem Quellverzeichnis\n" \
               "        in das neue IfaVerzeichnis\n" );
}


void ProgUsage( char *buf )
{
   Usage( buf );
   GetIfaVerzUsage( buf );
   CreateIfaVerzUsage( buf );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   switch ( *argv[0] )
    {
      case '1':
        if ( argc == 1 )
        {
           s = GetIfaVerz ( NULL, buf, 0 );
        }
        else if ( argc == 2 && strcmp( argv[1], "p" ) == 0 )
        {
           s = GetIfaVerz ( NULL, buf, 1 );
        }
        else if ( argc == 2 )
        {
           s = GetIfaVerz ( argv[1], buf, 0 );
        }
        else if ( argc == 3 && strcmp ( argv[2], "p" ) == 0 )
        {
           s = GetIfaVerz ( argv[1], buf, 1 );
        }
        else
        {
          s = 1;
          Usage( buf );
          GetIfaVerzUsage( buf );
        }
        break;

      case '2':
        if ( argc == 1 )
        {
          s = CreateIfaVerz( NULL, buf, 0 );
        }
        else if ( argc == 2 && strcmp( argv[1], "c" ) == 0 )
        {
          s = CreateIfaVerz( NULL, buf, 1 );
        }
        else if ( argc == 2 )
        {
          s = CreateIfaVerz( argv[1], buf, 0 );
        }
        else if ( argc == 3 && strcmp( argv[2], "c" ) == 0 )
        {
          s = CreateIfaVerz( argv[1], buf, 1 );
        }
        else
        {
          s = 1;
          Usage( buf );
          CreateIfaVerzUsage( buf );
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



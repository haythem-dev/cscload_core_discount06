
/* ---------------------------------------------------------------------- *
 *                            ZPIFESTB. C                                 *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Ifa Festbetrage laden                               *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 30.03.00                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.4.3 zpifestb : 02/06/2014 : Rolf Raab";

/*!
\page page18 zpifestb - Ifa verwFestbeträge laden
___________________________________________________________________________
\version	1.4.3
\date		02.06.2014
\internal
- RR: Wirkstoffgruppe aus zartwg holen statt zartikel
\endinternal
___________________________________________________________________________
\version	1.4.2
\date		11.03.2014
\internal
- TH: wandeln mit neuer zartikel-Struktur
\endinternal
___________________________________________________________________________
\version	1.4.1
\date		18.10.2013
\internal
- TH: C00FBSTUFE nur in zartikel.stufe_festbetrag1 schreiben, wenn auch ein Wert von IFA geliefert wird.
\endinternal
___________________________________________________________________________
\version	1.4.0
\date		15.03.2013
\internal
- TH: AIX build
\endinternal
___________________________________________________________________________
\version	1.3.4
\date		14.11.2012
\internal
- TH: PZN 8 für Protokoll ZPIFAFEB
\endinternal

*/

/* 1.1.1 21.12.2000 V_PROTO_VERTEIL bei zartikel und zartpreis ( vorher V_PROTOKOL ) */
/* 1.1.2 06.07.2001 neue Felder in zartikel NAHRUNGSTEST, NAHRUNGSERGAENZUNG */
/* 1.1.3 31.10.2001 auf neue definifa.idd umstellen;  C00FBDM -> C00FBDM in g_ifestb.c */
/* 1.1.4 24.05.2002 ZARTIKEL: PREISSENKUNG,  --- wpp_ --- */ 
/* 1.1.5 13.12.2002 Feld BSSICHG in ZARTIKEL */
/* 1.1.6 24.01.2003 Felder ANBIETERABSCHLAG, AUTIDEMARTIKEL, */
/*                  FESTBETRARTIKEL, DATUM_ABSCHLAG in ZARTIKEL  */
/* 1.1.7 06.03.2003 Neue Felder  REZEPTURARZNEI MEDIZINPRODUKT IMPFSTOFF CE_KENNZEICHEN */
/*                  ARZNEIMITTEL KONTRAZEPTIVUM in ZARTIKEL ( - ) */
/* 1.1.8 13.06.2003 Feld ZENTRALPPELIST in ZARTIKEL  */
/* 1.1.9 01/08/2003 neues Feld EKORIGINALHS */
/* 1.2.0 06.11.2003 Umstellung auf variable Datenbank  */
/* 1.2.1 13.11.2003 Neues Feld HILFSM_VERBRAUCH in zartikel */
/* 1.2.2 06.04.2005 TH: wandeln mit neuer zartikel-Struktur (psychotrop) */
/* 1.2.3 07.11.2006 RR: Änderungen zum Online-Debuggen */
/* 1.2.4 08.11.2006 RR: zapflege nur noch schreiben, wenn Preis sich tatsächlich ändert */
/* 1.2.5 04.07.2008 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						 Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.3.0 27.04.2011 TH: IFA 20174 - neues Feld C00FBSTUFE --> zartikel.STUFE_FESTBETRAG1 */
/* 1.3.1 15.05.2012 TH: PZN 8 */
/* 1.3.2 22.05.2012 TH: wandeln mit neuer zartikel-Struktur */
/* 1.3.3 25.07.2012 TH: voodoo table header */
/* 1.3.4 14.11.2012 TH: PZN 8 für Protokoll ZPIFAFEB */
/* 1.4.0 15.03.2013 TH: AIX build */
/* 1.4.1 18.10.2013 TH: C00FBSTUFE nur in zartikel.stufe_festbetrag1 schreiben, wenn auch ein Wert von IFA geliefert wird.*/
/* 1.4.2 11.03.2014 TH: wandeln mit neuer zartikel-Struktur */
/* 1.4.3 02.06.2014 RR: Wirkstoffgruppe aus zartwg holen statt zartikel */


/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>


/* ----- Prototype --------- */

long GenIfaFebNeu ( char *db, char *mode, char *ili_direc, char *idd_direc, char *buf );
long DeleteIfaFeb ( char *db, char *buf );
long SetBearbStat ( char *verz, char *buf );

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
       memcmp( datei, "feb", 3 )      !=  0 ||
       memcmp( &datei[7], ".dat", 4 ) !=  0 ||
       !IsNum( &datei[3], 4 )
     )
    {
      strcpy( errmld, "Dateiname im Format\nfebjjnn.dat\n" \
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

/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

static void LadeUsage( char *buf )
{
  strcat( buf, "1. zpifestb 1 database mode ili-Verzeichnis [idd-Verzeichnis]\n" \
               "   mode = 0: Laden   aller   Festbetraege in zartikel\n" \
               "   mode = 1: Laden   aller   Festbetraege in zartfeb\n"  \
               "   mode = 2: Laden der neuen Festbetraege in zartikel\n" \
               "   mode = 3: Laden der neuen Festbetraege in zartfeb\n"  \
               "   ili-Verzeichnis: Pfadname des ili-Verzeichnisses\n" \
               "   idd-Verzeichnis: Pfadname des idd-Verzeichnisses\n" );
}

static void DeleteUsage( char *buf )
{
  strcat( buf, "2. zpifestb 2 database\n" \
               "   loescht die Festbetraege aus der Relation zartfeb\n" );
}


static void SetBearbStatUsage( char *buf )
{
  strcat( buf, "3. zpifestb 3 ili-Verzeichnis\n" \
               "   setzt den Status fuer Festbetrag\n"\
               "   im ili-Verzeichnis auf 'bearbeitet'" );
}


void ProgUsage( char *buf )
{
   Usage( buf );
   LadeUsage( buf );
   DeleteUsage( buf );
   SetBearbStatUsage( buf );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   switch ( *argv[0] )
    {
      case '1':
        if ( argc == 4 )
        {
           s = GenIfaFebNeu( argv[1], argv[2], argv[3], ".", buf );
        }
        else if ( argc == 5 )
        {
           s = GenIfaFebNeu( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

      case '2':
        if ( argc == 2 )
        {
          s = DeleteIfaFeb( argv[1], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          DeleteUsage( buf );
        }
        break;

      case '3':
        if ( argc == 2 )
        {
          s = SetBearbStat( argv[1], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          SetBearbStatUsage( buf );
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



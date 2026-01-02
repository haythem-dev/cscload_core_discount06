
/* ---------------------------------------------------------------------- *
 *                       F E B _ P R O T . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Protokoll Uebernahme Festbetraege                            *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  20.10.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- includes --------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <phodate.h>
#include <phozeit.h>

#include "wr_prot.h"

#include "feb_prot.h"

/* --- page length / number ------------------- */

#define MAX_ZEILE 60

static long zeile = MAX_ZEILE;
static long seite = 1;

static long anz_gesamt;
static long anz_wegfall;
static long anz_noaen;
static long anz_null;
static char f_mode;
static char *f_alle;

/* --- page header ------------------------------ */

static char* u0 =
   "ZPIFESTB: PROTOKOLL AENDERUNG FESTBETRAG-";
static char* u1 =
   " IN ZARTIKEL";

static char* z0 =
   "  PZN       EINHEIT ARTIKELBEZEICHNUNG             DFO";
static char* z1 =
   "        AVP VGL   FEST-NEU   FEST-ALT";

/* --- Druck-output ------------------------------------- */

static void WriteZeile( char *buf )
{
   WriteFile( buf, "\n" );
   zeile++;
}

static void WriteLeerZeile( )
{
   WriteFile( "", "\n" );
   zeile++;
}

static void WriteVorschub()
{
   WriteFile( "", "\f" );
/* zeile = 0; */
}

/* --- members ------------------------------------- */

static void feb_Kopf_0( char *buf )
{

   char dat_str[20];
   long zeit;
   ConvFromPhoDate( dat_str, GetPhoDate(), "tt.mm.jjjj" );
   zeit = GetPhoTime( );

   sprintf( buf,
            "%s%c%s%s  DATUM: %s UHRZEIT: %.2ld:%.2ld:%.2ld SEITE: %ld",
            u0,
            f_mode,
            f_alle,
            u1,
            dat_str,
            zeit/10000,
            (zeit/100)%100,
            zeit%100,
            seite++ );
}

static void feb_Kopf_1( char *buf )
{
   sprintf( buf,
            "%s%s",
            z0,
            z1 );
}

static void feb_kopf( char *buf )
{
   if ( zeile >= MAX_ZEILE )
   {
      if ( seite > 1 )
         WriteVorschub( );
      zeile = 0;
      feb_Kopf_0( buf );
      WriteZeile( buf );
      feb_Kopf_1( buf );
      WriteZeile( buf );
      WriteLeerZeile( );
   }
}

static void feb_Zeile( struct FEB_PROT *info, char *buf  )
{
   char vgl;
   char *w_str;
/* int  i; */

   if ( info->AVP < -0.05 )    /* neu 22.10.2000: kein Preissatz vorhanden */
   {
       info->AVP = 0.0;
       vgl = '?';
   }
   else if ( info->AVP < info->FEST_NEU )
     vgl = '-';
   else if ( info->AVP > info->FEST_NEU )
     vgl = '+';
   else
     vgl = '=';

   w_str = "                       ";

/* neue, einfachere & übersichtlichere Konstruktion im Rahmen der Umstellung auf zartwg; Hintergrund: bei Festpreis-Artikeln muss zwingend ein Wirkstoff eingetragen sein
   i = 0;
   while ( info->WIRKSTOFF_NR[i] && info->WIRKSTOFF_NR[i] == ' ' ) i++;
   if ( info->WIRKSTOFF_NR[i] ) */
   if (atoi(info->WIRKSTOFF_NR))
      w_str = "";
   else
      w_str = "WIRKSTOFF FEHLT";

   sprintf( buf,
            " %.8ld %.9s %s %s %10.2f  %c  %10.2f %10.2f  %s",
            info->ARTIKEL_CODE,
            info->EINHEIT,
            info->ARTIKEL_NAME,
            info->DARREICHFORM,
            info->AVP,
            vgl,
            info->FEST_NEU,
            info->FEST_ALT,
            w_str
           );

   if ( info->FEST_NEU == 0.0 )
     anz_null++;
   if ( info->FEST_NEU == info->FEST_ALT )
     anz_noaen++;
}

/* --- Schnittstelle ------------------------------------ */

long feb_OpenProtokol( char *datei, int mit_protokol, char *mode, char *errmld )
{
   anz_gesamt  = 0;
   anz_wegfall = 0;
   anz_noaen   = 0;
   anz_null    = 0;
   if ( *mode == '0' || *mode == '2' )
     f_mode = '1';       /* Festbetrag-1 */
   else
     f_mode = '2';       /* Festbetrag-2 */

   if ( *mode == '0' || *mode == '1' )
     f_alle = " (ALLE)";       /* alle Festbetraege */
   else
     f_alle = " (NEUE)";       /* neue Festbetraege */

   return OpenFile( datei, "ifa", mit_protokol, 1, errmld );
}

void feb_CloseProtokol( int ok, long anz_gelesen, char *errmld )
{
   char buf[300];

   if ( ok )
   {
      if ( zeile >= MAX_ZEILE - 6 )
         zeile = MAX_ZEILE;
   }
   else
   {
      if ( zeile >= MAX_ZEILE - 8 )
         zeile = MAX_ZEILE;
   }

   feb_kopf( buf );

   WriteLeerZeile( );

   sprintf( buf, "*** GELESEN     %5.1ld", anz_gelesen );
   WriteZeile( buf );

   sprintf( buf, "*** N. GEFUNDEN %5.1ld", anz_gelesen - anz_gesamt );
   WriteZeile( buf );

   sprintf( buf, "*** GESCHRIEBEN %5.1ld", anz_gesamt );
   WriteZeile( buf );

   sprintf( buf, "FESTPREIS NULL  %5.1ld", anz_null );
   WriteZeile( buf );
   sprintf( buf, "KEINE AENDERUNG %5.1ld", anz_noaen );
   WriteZeile( buf );
   sprintf( buf, "LOESCHUNGEN     %5.1ld", anz_wegfall );
   WriteZeile( buf );

   if ( !ok )
   {
     WriteLeerZeile( );
     WriteZeile( errmld );
   }

   CloseFile( );
}

long feb_Protokol( struct FEB_PROT *info, char *errmld )
{
  char buf[300];
  feb_kopf( buf );
  feb_Zeile( info, buf  );
  WriteZeile( buf );
  WriteLeerZeile( );
  if ( FlushFile() != 0 )
  {
     strcpy( errmld, "Fehler beim Schreiben in die Protokolldatei" );
     return -1;
  }
  anz_gesamt++;
  if ( info->WEGFALL )
    anz_wegfall++;
  return 0;
}


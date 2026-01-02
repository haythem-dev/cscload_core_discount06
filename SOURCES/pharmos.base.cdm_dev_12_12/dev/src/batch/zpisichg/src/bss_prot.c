/* ---------------------------------------------------------------------- *
 *                       B S S _ P R O T . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Protokoll Uebernahme BSSIG                                   *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  28.02.2003                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- includes --------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <phodate.h>
#include <phozeit.h>

#include "bss_prot.h"

#include "wr_prot.h"

/* --- page length / number ------------------- */

#define MAX_ZEILE 60

static long zeile = MAX_ZEILE;
static long seite = 1;

static long anz_gesamt;
static long anz_null;
static long anz_eins;


/* --- page header ------------------------------ */

/* Andruck der PZN, Einheit, Name, Darreichungsform, GH-Abschlag alt, GH-Abschlag neu */

static char* u0 =
   "PROGRAMM ZPISICHG: PROTOKOLL UEBERNAHME BSSIG-AENDERUNGEN IN ZARTIKEL";

static char* z0 =
   "    PZN       EINHEIT ARTIKELBEZEICHNUNG             DFO BSSIG-ALT BSSIG-NEU";

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

static void bss_Kopf_0( char *buf )
{

   char dat_str[20];
   long zeit;
   ConvFromPhoDate( dat_str, GetPhoDate(), "tt.mm.jjjj" );
   zeit = GetPhoTime( );

   sprintf( buf,
            "%s  DATUM: %s  UHRZEIT: %.2ld:%.2ld:%.2ld  SEITE: %ld",
            u0,
            dat_str,
            zeit/10000,
            (zeit/100)%100,
            zeit%100,
            seite++ );
}

static void bss_Kopf_1( char *buf )
{
   sprintf( buf,
            "%s",
            z0   );
}

static void bss_kopf( char *buf )
{
   if ( zeile >= MAX_ZEILE )
   {
      if ( seite > 1 )
         WriteVorschub( );
      zeile = 0;
      bss_Kopf_0( buf );
      WriteZeile( buf );
      bss_Kopf_1( buf );
      WriteZeile( buf );
      WriteLeerZeile( );
   }
}

static void bss_zeile( struct ZARTIKEL *art, char *bssig_old, char *buf  )
{
   sprintf( buf,
            "    %.7ld %.9s %s %s      %s          %s",
            art->ARTIKEL_NR,
            art->EINHEIT,
            art->ARTIKEL_NAME,
            art->DARREICHFORM,
			bssig_old,
			art->BSSICHG
           );
}

/* --- Schnittstelle ------------------------------------ */

long bss_OpenProtokol( char *datei, int mit_protokol, char *errmld )
{
   anz_gesamt = 0;
   anz_null   = 0;
   anz_eins   = 0;
 
   return OpenFile( datei, "bss", mit_protokol, 1, errmld );
}


void bss_CloseProtokol( int ok, char *errmld )
{
   char buf[300];

   bss_kopf( buf );

   WriteLeerZeile( );

   sprintf( buf, "%5.1ld ARTIKEL-SAETZE VERARBEITET", anz_gesamt );
   WriteZeile( buf );
   sprintf( buf, "%5.1ld BSSIG-KENNZEICHEN AUF 1", anz_eins );
   WriteZeile( buf );
   sprintf( buf, "%5.1ld BSSIG-KENNZEICHEN AUF 0", anz_null );
   WriteZeile( buf );

   if ( !ok )
   {
     WriteLeerZeile( );
     WriteZeile( errmld );
   }

   CloseFile( );
}


long bss_Protokol( struct ZARTIKEL *art, char *bssig_old, char *errmld )
{
  char buf[300];
  bss_kopf( buf );
  bss_zeile( art, bssig_old, buf );
  WriteZeile( buf );
  if ( FlushFile() != 0 )
  {
     strcpy( errmld, "Fehler beim Schreiben in die Protokolldatei" );
     return -1;
  }
  anz_gesamt++;
  if ( *art->BSSICHG == '0' )
	anz_null++;
  else
	anz_eins++;
  return 0;
}






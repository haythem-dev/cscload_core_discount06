
/* --- includes --------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <hdatum/phodate.h>
#include <hdatum/phozeit.h>

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/zartswitzerland.h>
#include <voodoo_table_header/ean.h>
#include "wr_prot.h"

/* --- Prototype aus art_gen ------------------------ */



/* --- page length / number ------------------- */

#define MAX_ZEILE 60

static long zeile = MAX_ZEILE;
static long seite = 1;

static long anz_gesamt;
static long anz_neu;
static long anz_aen;
static long anz_loe;

/* --- page header ------------------------------ */

static char* u0 =
   "PROGRAMM ZPLIGNART: PROTOKOLL UEBERNAHME LOGINDEX-AENDERUNGEN IN ZARTIKEL";

static char* z0 =
   "    PZN       EINHEIT ARTIKELBEZEICHNUNG             DFO                                ";
static char* z1 =
   "    EAN                 GEP       AVP              AH-DATUM   LAUFZ  R B A R P KK M ";

static char z_rest_def[20]  =  ". . . . . .  ."; /* 7 */

struct Z_REST
{
   char    REZEPTPFL             [2];
   char    BTM                   [2];
   char    AH_KENNZ              [2];
   char    RR_KENNZ              [2];
   char    PSYCHOTROP            [2];
   char    KUEHLKETTE            [3];
   char    MWST                  [2];
   char    end_byte;
};


/* --- Druck-output ------------------------------------- */


static void WriteZeile( char *spBuf )
{
   WriteFile( spBuf, "\n" );
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
}

/* --- members ------------------------------------- */

static void li_Kopf_0( char *spBuf )
{

   char dat_str[20];
   long zeit;
   ConvFromPhoDate( dat_str, GetPhoDate(), "tt.mm.jjjj" );
   zeit = GetPhoTime( );

   sprintf( spBuf,
            "%s  DATUM: %s  UHRZEIT: %.2ld:%.2ld:%.2ld  SEITE: %ld",
            u0,
            dat_str,
            zeit/10000,
            (zeit/100)%100,
            zeit%100,
            seite++ );
}

static void li_Kopf_1( char *spBuf )
{
   sprintf( spBuf,
            "%s",
            z0 );
}

static void li_Kopf_2( char *spBuf )
{
   sprintf( spBuf,
            "%s",
            z1);
}

static void li_kopf( char *spBuf )
{
   if ( zeile >= MAX_ZEILE )
   {
      if ( seite > 1 )
         WriteVorschub( );
      zeile = 0;
      li_Kopf_0( spBuf );
      WriteZeile( spBuf );
      li_Kopf_1( spBuf );
      WriteZeile( spBuf );
      li_Kopf_2( spBuf );
      WriteZeile( spBuf );
      WriteLeerZeile( );
   }
}

static void li_Zeile_1( struct ZARTIKEL *art, struct ZARTSWITZERLAND *spSwitz, char *spBuf  )
{
   sprintf( spBuf,
            "    %.7ld %.9s %s %s",
            art->ARTIKEL_NR,
            art->EINHEIT,
            art->ARTIKEL_NAME,
            art->DARREICHFORM
           );
}

static void li_Zeile_loe( char *spBuf  )
{
   sprintf( spBuf,
            "LOE                   LI -LOESCHUNG" );
}


static void li_Zeile_2( struct ZARTIKEL *art, struct ZARTPREIS *preis,  struct ZARTSWITZERLAND *spSwitz, struct EAN *ean,
                         char *mode, char *spBuf  )
{
   char z_preis[50];
   char z_datum[12];
   char z_lz[10];
   struct Z_REST z_rest;
   
   sprintf( z_preis,
            "%s %9.2f %9.2f",
			ean->EAN_NR,
            preis->GROSSO,
            preis->AVP
           );
   
   strcpy( ( char *)&z_rest, z_rest_def );

   if ( *art->REZEPTPFL      == '1' ) *z_rest.REZEPTPFL      = 'J';
   if ( *art->BTM            == '1' ) *z_rest.BTM            = 'J';
   if (  art->DATUM_AH		  > 0 )   *z_rest.AH_KENNZ       = 'J';
   if (  art->DATUM_RR		  > 0 )   *z_rest.RR_KENNZ       = 'J';

   *z_rest.PSYCHOTROP       = *art->PSYCHOTROP;
   
   switch ( *art->KUEHLARTIKEL )
   {
      case '4':
        *z_rest.KUEHLKETTE = 'J';
        break;
	  default:
		  break;
   }

   if ( *preis->KE_MWST == '1' )     *z_rest.MWST = 'J';

   z_rest.end_byte = '\0';

   ConvFromPhoDate( z_datum, art->DATUM_AH, "tt.mm.jjjj" );

   if ( art->LAUFZEITMONATE == 0 )
     strcpy( z_lz, "   " );
   else
     sprintf( z_lz, "%3.1ld", art->LAUFZEITMONATE );


   sprintf( spBuf,
            "%s %s              %10.10s %5.5s  %s",
            mode,
			z_preis,
            z_datum,
            z_lz,
            (char*) &z_rest);
}


/* --- Schnittstelle ------------------------------------ */

long LI_OpenProtokol( long nr, char *verzeichnis, char *errmld )
{
   char *datei;
   long s;
   anz_gesamt = 0;
   anz_neu    = 0;
   anz_aen    = 0;
   anz_loe    = 0;

   /* nr in der Form jjjjmmtt: 19421128 */

   datei = malloc( strlen( verzeichnis ) + 12 );
   if ( datei == NULL )
   {
      strcpy( errmld, "malloc-Fehler bei logindex_OpenProtokol" );
      return -1;
   }
   sprintf( datei, "%s/a%.6ld", verzeichnis, nr%1000000 );
   s = OpenFile( datei, "li", 1, 1, errmld );
   free( datei );
   return s;
}

void LI_CloseProtokol( int ok, char *errmld )
{
   char buf[300];

   li_kopf( buf );

   WriteLeerZeile( );

   sprintf( buf, "%5.1ld ARTIKEL-SAETZE VERARBEITET", anz_gesamt );
   WriteZeile( buf );
   sprintf( buf, "%5.1ld ARTIKEL-SAETZE GEAENDERT", anz_aen );
   WriteZeile( buf );
   sprintf( buf, "%5.1ld ARTIKEL-SAETZE NEU ANGELEGT", anz_neu );
   WriteZeile( buf );
   sprintf( buf, "%5.1ld ARTIKEL-SAETZE GELOESCHT", anz_loe );
   WriteZeile( buf );

   if ( !ok )
   {
     WriteLeerZeile( );
     WriteZeile( errmld );
   }

   CloseFile( );
}

long LI_ProtokolLoe( struct ZARTIKEL *altart, struct ZARTSWITZERLAND *spAltSwitz, char *errmld )
{
  char buf[300];
  li_kopf( buf );
  li_Zeile_1( altart, spAltSwitz, buf  );
  WriteZeile( buf );
  li_Zeile_loe( buf  );
  WriteZeile( buf );
  WriteLeerZeile( );
  if ( FlushFile() != 0 )
  {
     strcpy( errmld, "Fehler beim Schreiben in die Protokolldatei" );
     return -1;
  }
  anz_gesamt++;
  anz_loe++;
  return 0;
}


long LI_ProtokolNeu( struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis, struct ZARTSWITZERLAND *spNeuSwitz, struct EAN *spNeuEan, char *errmld )
{
  char buf[300];
  li_kopf( buf );
  li_Zeile_1( neuart, spNeuSwitz,buf  );
  WriteZeile( buf );
  li_Zeile_2( neuart, neupreis, spNeuSwitz, spNeuEan, "NEU", buf );
  WriteZeile( buf );
  WriteLeerZeile( );
  if ( FlushFile() != 0 )
  {
     strcpy( errmld, "Fehler beim Schreiben in die Protokolldatei" );
     return -1;
  }
  anz_gesamt++;
  anz_neu++;
  return 0;
}

long LI_ProtokolAen( struct ZARTIKEL *altart, struct ZARTPREIS *altpreis, struct ZARTSWITZERLAND *spAltSwitz, struct EAN *spAltEan,
                      struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis, struct ZARTSWITZERLAND *spNeuSwitz, struct EAN *spNeuEan, char *errmld )
{
  int  geaendert;
  char buf[300];
  char buf_alt[300];
  char buf_neu[300];
  li_kopf( buf );
  li_Zeile_1( altart, spAltSwitz, buf  );
  WriteZeile( buf );
  li_Zeile_2( altart, altpreis,spAltSwitz,spAltEan, "ALT", buf_alt );
  li_Zeile_2( neuart, neupreis,spNeuSwitz,spNeuEan, "NEU", buf_neu );
  geaendert = strcmp( &buf_alt[3], &buf_neu[3] ) != 0;
  if ( !geaendert ) buf_alt[3] = '=';
  WriteZeile( buf_alt );
  WriteZeile( buf_neu );
  WriteLeerZeile( );
  if ( FlushFile() != 0 )
  {
     strcpy( errmld, "Fehler beim Schreiben in die Protokolldatei" );
     return -1;
  }
  if ( geaendert )
      anz_aen++;
  anz_gesamt++;
  return 0;
}


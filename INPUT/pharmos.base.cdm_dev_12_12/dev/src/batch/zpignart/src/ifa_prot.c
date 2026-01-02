
/* ---------------------------------------------------------------------- *
 *                       I F A _ P R O T . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Protokoll Uebernahme IFA                                     *
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

#include <zartikel.h>
#include <zartprei.h>
#include "wr_prot.h"

/* --- Prototype aus art_gen ------------------------ */

int IFA_Zuzahlung_to_ZZ( char *Zuzahlung, char *ZZ );

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
   "PROGRAMM ZPIFAGEN: PROTOKOLL UEBERNAHME IFA-AENDERUNGEN IN ZARTIKEL";

static char* z0 =
   "    PZN       EINHEIT ARTIKELBEZEICHNUNG             DFO                    ";
static char* z1 =
   "                        GEP       AEP       AVP              AH-DATUM  LZ ZZ";
static char* z2 =
   "                                                                            ";

static char* y0 = "N R A T O T V A R R N K K K K N K H V C M";
static char* y1 = "E P P P P A B H S R A 0 2 2 K G L D D N W";
static char* y2 = "G                     8 0 5              ";
static char* y3 = "IFA A-V:    N         0 0 0 0     N N N  ";

#define y3_k08 22
#define y3_k20 24
#define y3_k25 26
#define y3_kk  28

#define y3_hd  34
#define y3_vd  36
#define y3_cn  38

#define y3_vb  12

static char* z_rest_def = ". . . . . . . . . . . . . . . . . . . . .";

struct Z_REST
{
   char    NEGATIVLISTE          [2];
   char    REZEPTPFL             [2];
   char    APOTHEKENPFL          [2];
   char    TAXPFL                [2];
   char    BTM                   [2];
   char    TIERARZNEI            [2];
   char    VERTRBIND_IFA         [2];
   char    AH_KENNZ              [2];
   char    RETOURENSPERRE        [2];
   char    RR_KENNZ              [2];
   char    NETTOARTIKEL          [2];
   char    KUEHL08               [2];
   char    KUEHL20               [2];
   char    KUEHL25               [2];
   char    KUEHLKETTE            [2];
   char    NICHTUEBERGH          [2];
   char    KLINIKPACKUNG         [2];
   char    HERST_DATUM           [2];
   char    VERFALL_DATUM         [2];
   char    CHARGENNR             [2];
   char    MWST                  [2];
   char    end_byte;
};

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

static void ifa_Kopf_0( char *buf )
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

static void ifa_Kopf_1( char *buf )
{
   sprintf( buf,
            "%s   %s",
            z0,
            y0 );
}

static void ifa_Kopf_2( char *buf )
{
   sprintf( buf,
            "%s   %s",
            z1,
            y1 );
}

static void ifa_Kopf_3( char *buf )
{
   sprintf( buf,
            "%s   %s",
            z2,
            y2 );
}

static void ifa_kopf( char *buf )
{
   if ( zeile >= MAX_ZEILE )
   {
      if ( seite > 1 )
         WriteVorschub( );
      zeile = 0;
      ifa_Kopf_0( buf );
      WriteZeile( buf );
      ifa_Kopf_1( buf );
      WriteZeile( buf );
      ifa_Kopf_2( buf );
      WriteZeile( buf );
      ifa_Kopf_3( buf );
      WriteZeile( buf );
      WriteLeerZeile( );
   }
}

static void ifa_Zeile_1( struct ZARTIKEL *art, char *buf, long pzn8  )
{
   sprintf( buf,
            "   %.8ld %.9s %s %s",
            pzn8,
            art->EINHEIT,
            art->ARTIKEL_NAME,
            art->DARREICHFORM
           );
}

static void ifa_Zeile_loe( char *buf  )
{
   sprintf( buf,
            "LOE                   IFA-LOESCHUNG" );
}


static void ifa_Zeile_2( struct ZARTIKEL *art, struct ZARTPREIS *preis,
                         char *mode, char *buf  )
{
   char z_preis[50];
   char z_datum[12];
   char z_lz[10];
   char z_zz[10];
   struct Z_REST z_rest;

   sprintf( z_preis,
            "%9.2f %9.2f %9.2f",
            preis->GROSSO,
            preis->AEP,
            preis->AVP
           );

/*
   memcpy( ( char *)&z_rest, z_rest_def, sizeof( struct Z_REST ) );
*/
   strcpy( ( char *)&z_rest, z_rest_def );
   if ( *art->NEGATIVLISTE   == '1' ) *z_rest.NEGATIVLISTE   = 'J';
   if ( *art->REZEPTPFL      == '1' ) *z_rest.REZEPTPFL      = 'J';
   if ( *art->APOTHEKENPFL   == '1' ) *z_rest.APOTHEKENPFL   = 'J';
/* if ( *art->TAXPFL         == '1' ) *z_rest.TAXPFL         = 'J';  */
   if ( *art->TAXPFL         != '0' ) *z_rest.TAXPFL         = 'J';
   if ( *art->BTM            == '1' ) *z_rest.BTM            = 'J';
   if ( *art->TIERARZNEI     == '1' ) *z_rest.TIERARZNEI     = 'J';
   if ( *art->VERTRBIND_IFA  == '1' ) *z_rest.VERTRBIND_IFA  = 'J';
   if (  art->DATUM_AH > 0 )          *z_rest.AH_KENNZ       = 'J';
   if ( *art->RETOURENSPERRE == '1' ) *z_rest.RETOURENSPERRE = 'J';
   if ( art->DATUM_RR > 0 )           *z_rest.RR_KENNZ       = 'J';
   if ( *art->NETTOARTIKEL   == '1' ) *z_rest.NETTOARTIKEL   = 'J';
   switch ( *art->KUEHLARTIKEL )
   {
      case '1':
        *z_rest.KUEHL08 = 'J';
        break;
      case '2':
        *z_rest.KUEHL20 = 'J';
        break;
      case '3':
        *z_rest.KUEHL25 = 'J';
        break;
      case '4':
        *z_rest.KUEHLKETTE = 'J';
        break;
   }

   if ( *art->NICHTUEBERGH   == '1' ) *z_rest.NICHTUEBERGH   = 'J';
   if ( *art->KLINIKPACKUNG  == '1' ) *z_rest.KLINIKPACKUNG  = 'J';
   if ( *art->VERFALL == '1' )
        *z_rest.VERFALL_DATUM  = 'J';
   else if ( *art->VERFALL == '2' )
        *z_rest.HERST_DATUM  = 'J';
   else if ( *art->VERFALL == '3' )
        *z_rest. CHARGENNR   = 'J';

   if ( *preis->KE_MWST == '0' || *preis->KE_MWST == '1'  )
        *z_rest.MWST = *preis->KE_MWST;

   z_rest.end_byte = '\0';

   ConvFromPhoDate( z_datum, art->DATUM_AH, "tt.mm.jjjj" );

   if ( art->LAUFZEITMONATE == 0 )
     strcpy( z_lz, "   " );
   else
     sprintf( z_lz, "%3.1ld", art->LAUFZEITMONATE );

   IFA_Zuzahlung_to_ZZ( art->ZUZAHLUNG_IFA, z_zz );

   sprintf( buf,
            "%s               %s            %s %s %s   %s",
            mode,
            z_preis,
            z_datum,
            z_lz,
            z_zz,
            (char*) &z_rest );
}

static int ifa_Zeile_3( struct ZARTIKEL *art,
                        char lagerung, char verfall, char vertrbind,
                        char *buf  )
{
   char y3[50] = {" "};

   y3[y3_k08] = ' ';
   y3[y3_k20] = ' ';
   y3[y3_k25] = ' ';
   y3[y3_kk ] = ' ';

   y3[y3_hd ] = ' ';
   y3[y3_vd ] = ' ';
   y3[y3_cn ] = ' ';

   y3[y3_vb ] = ' ';

   if ( verfall == '0' )
   {
      if ( *art->VERFALL == '1' )
         y3[y3_vd ] = 'N';
      else if ( *art->VERFALL == '2' )
         y3[y3_hd ] = 'N';
      else if ( *art->VERFALL == '3' )
         y3[y3_cn ] = 'N';
   }

   if ( lagerung == '0' )
   {
      if ( *art->KUEHLARTIKEL == '1' )
        y3[y3_k08] = 'N';
      else if ( *art->KUEHLARTIKEL == '2' )
        y3[y3_k20] = 'N';
      else if ( *art->KUEHLARTIKEL == '3' )
        y3[y3_k25] = 'N';
      else if ( *art->KUEHLARTIKEL == '4' )
        y3[y3_kk ] = 'N';
   }

   if ( vertrbind == '0' )
   {
      if ( *art->VERTRBIND_IFA == '1' )
         y3[y3_vb ] = 'N';
   }

   if ( y3[y3_k08] == ' ' && y3[y3_k20] == ' ' && y3[y3_k25] == ' ' &&
        y3[y3_kk ] == ' ' && y3[y3_hd ] == ' ' && y3[y3_vd ] == ' ' &&
        y3[y3_vb ] == ' ' )
      return 0;

   sprintf( buf,
            "%s   %s",
            z2,
            y3
           );

   return 1;
}


/* --- Schnittstelle ------------------------------------ */

long ifa_OpenProtokol( long nr, char *verzeichnis, char *errmld )
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
      strcpy( errmld, "malloc-Fehler bei ifa_OpenProtokol" );
      return -1;
   }
   sprintf( datei, "%s/a%.6ld", verzeichnis, nr%1000000 );
   s = OpenFile( datei, "ifa", 1, 1, errmld );
   free( datei );
   return s;
}

void ifa_CloseProtokol( int ok, char *errmld )
{
   char buf[300];

   ifa_kopf( buf );

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

long ifa_ProtokolLoe( struct ZARTIKEL *altart, char *errmld, long pzn8 )
{
  char buf[300];
  ifa_kopf( buf );
  ifa_Zeile_1( altart, buf, pzn8  );
  WriteZeile( buf );
  ifa_Zeile_loe( buf  );
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


long ifa_ProtokolNeu( struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis,
                      char *errmld, long pzn8 )
{
  char buf[300];
  ifa_kopf( buf );
  ifa_Zeile_1( neuart, buf, pzn8  );
  WriteZeile( buf );
  ifa_Zeile_2( neuart, neupreis, "NEU", buf );
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

long ifa_ProtokolAen( struct ZARTIKEL *altart, struct ZARTPREIS *altpreis,
                      struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis,
                      char lagerung, char verfall, char vertrbind,
                      char *errmld, long pzn8 )
{
  int  geaendert;
  char buf[300];
  char buf_alt[300];
  char buf_neu[300];
  ifa_kopf( buf );
  ifa_Zeile_1( altart, buf, pzn8  );
  WriteZeile( buf );
  ifa_Zeile_2( altart, altpreis, "ALT", buf_alt );
  ifa_Zeile_2( neuart, neupreis, "NEU", buf_neu );
  geaendert = strcmp( &buf_alt[3], &buf_neu[3] ) != 0;
  if ( !geaendert ) buf_alt[3] = '=';
  WriteZeile( buf_alt );
  WriteZeile( buf_neu );
  if ( ifa_Zeile_3( neuart, lagerung, verfall, vertrbind, buf  ) )
     WriteZeile( buf );
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


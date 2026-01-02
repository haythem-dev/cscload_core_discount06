
/* --- includes --------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <hdatum/phodate.h>
#include <hdatum/phozeit.h>

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/zartwg.h>
#include <voodoo_table_header/zartaustria.h>

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
   "PROGRAMM ZPDCGNART: PROTOKOLL UEBERNAHME DATACARE-AENDERUNGEN IN ZARTIKEL";

static char* z0 =
   "    PZN       EINHEIT ARTIKELBEZEICHNUNG             DFO                                ";
static char* z1 =
   "                        GEP       AEP       AVP              AH-DATUM   LZ         LI-CO";
static char* z2 =
   "                                                                                        ";

static char* y0 = "R A T O T V A A R K K K N M N + + 1 V B"; 
static char* y1 = "P P P P A B L H R 0 2 K G W E   + 5 + O";
static char* y2 = "                  8 0                 X";
static char* y3 = "IFA A-V:    N         0 0 0 0     N N N  ";

#define y3_k08 22
#define y3_k20 24
#define y3_k25 26
#define y3_kk  28
#define y3_km15 30
#define y3_km60 32

#define y3_hd  34
#define y3_vd  36
#define y3_cn  38

#define y3_vb  12

static char* z_rest_def  =  ". . . . . . . . . . . . . . ."; /* 15*/
static char* z_rest_def_austria = ". . . . ."; /* 5 */

struct Z_REST_AUSTRIA
{
    char    VERTRBIND_PL	   [2];
    char    VERTRBIND_PLPL     [2];
    char    VERTRBIND_S1S5     [2];
    char    VERTRBIND_VPL      [2];
    char    HV_BOX             [2];
    char    end_byte;
};

struct Z_REST
{
   char    REZEPTPFL             [2];
   char    APOTHEKENPFL          [2];
   char    TAXPFL                [2];
   char    BTM                   [2];
   char    TIERARZNEI            [2];
   char    VERTRBIND_IFA         [2];
   char	   AV_KENNZ				 [2]; /* wird als AL gedruckt */
   char    AH_KENNZ              [2];
   char    RR_KENNZ              [2];
   char    KUEHL08               [2];
   char    KUEHL20               [2];
   char    KUEHLKETTE            [2];
   char    NICHTUEBERGH          [2];
   char    MWST                  [2];
   char	   NAHRUNGSTEST			 [2];
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
/* zeile = 0; */
}

static char GetJN(char cChar)
{
	char c;

	c = cChar;
	switch (c)
	{
	case '0':
		c = 'N';
		break;
	case '1':
		c = 'J';
		break;
	default:
		c = '.';
	}
	return c;
}
/* --- members ------------------------------------- */

static void dc_Kopf_0( char *spBuf )
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

static void dc_Kopf_1( char *spBuf )
{
   sprintf( spBuf,
            "%s  %s",
            z0,
            y0 );
}

static void dc_Kopf_2( char *spBuf )
{
   sprintf( spBuf,
            "%s  %s",
            z1,
            y1 );
}

static void dc_Kopf_3( char *spBuf )
{
   sprintf( spBuf,
            "%s  %s",
            z2,
            y2 );
}

static void dc_kopf( char *spBuf )
{
   if ( zeile >= MAX_ZEILE )
   {
      if ( seite > 1 )
         WriteVorschub( );
      zeile = 0;
      dc_Kopf_0( spBuf );
      WriteZeile( spBuf );
      dc_Kopf_1( spBuf );
      WriteZeile( spBuf );
      dc_Kopf_2( spBuf );
      WriteZeile( spBuf );
      dc_Kopf_3( spBuf );
      WriteZeile( spBuf );
      WriteLeerZeile( );
   }
}

static void dc_Zeile_1( struct ZARTIKEL *art, struct ZARTAUSTRIA *spAustria, char *spBuf  )
{
   sprintf( spBuf,
            "    %.7ld %.9s %s %s",
            art->ARTIKEL_NR,
            art->EINHEIT,
            art->ARTIKEL_NAME,
            art->DARREICHFORM
           );
}

static void dc_Zeile_loe( char *spBuf  )
{
   sprintf( spBuf,
            "LOE                   IFA-LOESCHUNG" );
}


static void dc_Zeile_2( struct ZARTIKEL *art, struct ZARTPREIS *preis,  struct ZARTAUSTRIA *spAustria, struct ZARTWG *spWgr,
                         char *mode, char *spBuf  )
{
   char z_preis[50];
   char z_datum[12];
   char z_lz[10];
   struct Z_REST z_rest;
   struct Z_REST_AUSTRIA z_rest_austria;

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
   if ( *art->REZEPTPFL      == '1' ) *z_rest.REZEPTPFL      = 'J';
   if ( *art->APOTHEKENPFL   == '1' ) *z_rest.APOTHEKENPFL   = 'J';
   if ( *art->TAXPFL         != '0' ) *z_rest.TAXPFL         = 'J';
   if ( *art->BTM            == '1' ) *z_rest.BTM            = 'J';
   if ( *art->TIERARZNEI     == '1' ) *z_rest.TIERARZNEI     = 'J';
   if ( *art->VERTRBIND_IFA  == '1' ) *z_rest.VERTRBIND_IFA  = 'J';
   if (  art->DATUM_AH > 0 )          *z_rest.AH_KENNZ       = 'J';
   if (  art->DATUM_AV > 0 )          *z_rest.AV_KENNZ       = 'J';
   if ( art->DATUM_RR > 0 )           *z_rest.RR_KENNZ       = 'J';
   switch ( *art->KUEHLARTIKEL )
   {
      case '1':
        *z_rest.KUEHL08 = 'J';
        break;
      case '2':
        *z_rest.KUEHL20 = 'J';
        break;
      case '3':
        break;
      case '4':
        *z_rest.KUEHLKETTE = 'J';
        break;
   }

   if ( *art->NICHTUEBERGH   == '1' ) *z_rest.NICHTUEBERGH   = 'J';


   //if ( *preis->KE_MWST == '1' )     *z_rest.MWST = 'J';
   *z_rest.MWST   = *preis->KE_MWST;

   /*if ( *art->NAHRUNGSTEST   == 'K' ) *z_rest.NAHRUNGSTEST   = 'K'; */

   *z_rest.NAHRUNGSTEST   = *art->NAHRUNGSTEST;
   z_rest.end_byte = '\0';

   ConvFromPhoDate( z_datum, art->DATUM_AH, "tt.mm.jjjj" );

   if ( art->LAUFZEITMONATE == 0 )
     strcpy( z_lz, "   " );
   else
     sprintf( z_lz, "%3.1ld", art->LAUFZEITMONATE );


   strcpy( ( char *)&z_rest_austria, z_rest_def_austria );

   if ( *spAustria->VERTRBIND_VPL    == '1' ) *z_rest_austria.VERTRBIND_VPL    = 'J';
   if ( *spAustria->VERTRBIND_PLPL   == '1' ) *z_rest_austria.VERTRBIND_PLPL   = 'J';
   if ( *spAustria->VERTRBIND_S1S5   == '1' ) *z_rest_austria.VERTRBIND_S1S5   = 'J';
   if ( *spAustria->VERTRBIND_PLPL   == '1' ) *z_rest_austria.VERTRBIND_PLPL   = 'J';

   *z_rest_austria.HV_BOX = *spAustria->HV_BOX;
   z_rest_austria.end_byte = '\0';


   sprintf( spBuf,
            "%s               %s              %10.10s %10.10s %5.5s  %s %s",
            mode,
            z_preis,
            z_datum,
            z_lz,
			spWgr->WARENGRUPPE,
            &z_rest,
			&z_rest_austria);
}

static int dc_Zeile_3( struct ZARTIKEL *art, struct ZARTAUSTRIA *spAustria,
                        char lagerung, char verfall, char vertrbind,
                        char *spBuf  )
{
   y3[y3_km60] = ' ';
   y3[y3_km15] = ' ';
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
	  else if (*art->KUEHLARTIKEL == '5')
		y3[y3_km15] = 'N';
	  else if (*art->KUEHLARTIKEL == '6')
	   y3[y3_km60] = 'N';
   }

   if ( vertrbind == '0' )
   {
      if ( *art->VERTRBIND_IFA == '1' )
         y3[y3_vb ] = 'N';
   }

   if ( y3[y3_k08] == ' ' && y3[y3_k20] == ' ' && y3[y3_k25] == ' ' &&
        y3[y3_kk ] == ' ' && y3[y3_km15] == ' ' && y3[y3_km60] == ' ' && y3[y3_hd ] == ' ' && y3[y3_vd ] == ' ' &&
        y3[y3_vb ] == ' ' )
      return 0;

   sprintf( spBuf,
            "%s   %s",
            z2,
            y3
           );

   return 1;
}


/* --- Schnittstelle ------------------------------------ */

long DC_OpenProtokol( long nr, char *verzeichnis, char *errmld )
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
      strcpy( errmld, "malloc-Fehler bei datacare_OpenProtokol" );
      return -1;
   }
   sprintf( datei, "%s/a%.6ld", verzeichnis, nr%1000000 );
   s = OpenFile( datei, "dc", 1, 1, errmld );
   free( datei );
   return s;
}

void DC_CloseProtokol( int ok, char *errmld )
{
   char buf[300];

   dc_kopf( buf );

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

long DC_ProtokolLoe( struct ZARTIKEL *altart, struct ZARTAUSTRIA *spAltAustria, char *errmld )
{
  char buf[300];
  dc_kopf( buf );
  dc_Zeile_1( altart, spAltAustria, buf  );
  WriteZeile( buf );
  dc_Zeile_loe( buf  );
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


long DC_ProtokolNeu( struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis, struct ZARTAUSTRIA *spNeuAustria, struct ZARTWG *spNeuWgr,
                      char *errmld )
{
  char buf[300];
  dc_kopf( buf );
  dc_Zeile_1( neuart, spNeuAustria,buf  );
  WriteZeile( buf );
  dc_Zeile_2( neuart, neupreis, spNeuAustria,spNeuWgr,"NEU", buf );
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

long DC_ProtokolAen( struct ZARTIKEL *altart, struct ZARTPREIS *altpreis, struct ZARTAUSTRIA *spAltAustria, struct ZARTWG * spAltWgr,
                      struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis, struct ZARTAUSTRIA *spNeuAustria,struct ZARTWG * spNeuWgr,
                      char *errmld )
{
  int  geaendert;
  char buf[300];
  char buf_alt[300];
  char buf_neu[300];
  dc_kopf( buf );
  dc_Zeile_1( altart, spAltAustria, buf  );
  WriteZeile( buf );
  dc_Zeile_2( altart, altpreis,spAltAustria, spAltWgr,"ALT", buf_alt );
  dc_Zeile_2( neuart, neupreis,spNeuAustria,spNeuWgr, "NEU", buf_neu );
  geaendert = strcmp( &buf_alt[3], &buf_neu[3] ) != 0;
  if ( !geaendert ) buf_alt[3] = '=';
  WriteZeile( buf_alt );
  WriteZeile( buf_neu );
/*  if ( dc_Zeile_3( neuart, lagerung, verfall, vertrbind, buf  ) )
     WriteZeile( buf ); */
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


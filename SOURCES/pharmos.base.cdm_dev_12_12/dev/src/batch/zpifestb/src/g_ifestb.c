/* ---------------------------------------------------------------------- *
 *                         g_ifestb.c                                     *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die IFA  Festbetraege                           *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 16.03.00                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <phodate.h>

#include <wpp_dbas.h>

#include "feb_prot.h"

#include "ifa_satz.h"
#include "ifa_info.h"
#include <ifa_stat.h>

#include <libscsvoodoo.h>

#define TEST_MODE 0
#define FILL_MODE 1

static long tagesdatum;
static char *lade_mode;
static long anz_ok;

/* --------  user -------------- */

static char *user = "IFA-FEB ";

/* -------- Kennung fuer Festbetrag --------------- */

static char *SatzartPhx = "PFESTBET";

/* --- Prototype  ------------------------------------------------------- */

void CloseBase( void );
long OpenBase ( char *db, char *errmld );
int  TestDateiname( char *file, long *ifadatum, char *errmld );

long FebLadenInit( long tagesdatum, char *mode, char *errmld );
long FebLaden( char *mode, int wegfall, long artikel_nr, long datum,
               long festbetrag, char febstufe, long tagesdatum, char *errmld, long code );
long FebLadenClose( char *mode );

long DeleteAll_Zartfeb2( long tagesdatum, char *errmld );


/* ---------------------------------------------------------------------- *
 * Funktion         : I f a B e a r b e i t e                             *
 * ---------------------------------------------------------------------- */

static char *GetWert( sSatzArt *pSart, char* feld, char *errmld )
{
   char *wert;
   wert = GetWertFromSatzArtViaFeldName( pSart, feld );
   if ( wert == NULL )
      sprintf( errmld, "kein Wert fuer Feld %s", feld );
   return wert;
}

/* ------------------------------------------------------------------- */
long sel_ArtNoByCode	( const long code, char *errmld)
{
    long artNo;
	char sql[150];

	sprintf( sql, "SELECT articleno FROM carticlecodes WHERE article_code ='%ld' "
					"AND code_type IN (SELECT code_type FROM ccodetypes WHERE artnr_substitute = 1)", code);
  
	if ( SqlRead( sql, &artNo, NULL ) != 0 )
	{
		artNo = -1;
		strcpy( errmld, "carticlecodes (Suche nach Code): " );
		strcat( errmld, DynErrmld() );
	}

	return artNo;
}

static int  FillFebSatz( sSatzArt *pSart, int mode, char *errmld )
{
   char *wert;
   int  s;
   char satzart;
   long datum;
   long artikel_nr;
   long code;
   long festbetrag;
   int  wegfall;
   char febstufe;
   
   s = 0;

   if ( ( wert = GetWert( pSart, "C00SSATZ", errmld ) ) == NULL ) return 1;
   satzart = *wert;
   wegfall = satzart == '2';

   if ( ( wert = GetWert( pSart, "C00GDAT", errmld ) ) == NULL ) return 1;
   datum = atol( wert );  /* jjjjmmtt */

   if ( ( wert = GetWert( pSart, "C00PZNFB", errmld ) ) == NULL ) return 1;

   code = atol( wert );
   
   if ( mode == FILL_MODE )
   {
		artikel_nr = sel_ArtNoByCode(atol( wert ), errmld); // Umwandlung PZN 8
		
		if (artikel_nr <= 0)
			return 1;
   }
   else
		artikel_nr = atol( wert ); // im Testmode ist noch keine DB-Verbindung zum Lesen AC offen!

							/*   "C00FBDM"   */
   if ( ( wert = GetWert( pSart, "C00FB", errmld ) ) == NULL ) return 1;

   if ( wegfall )
      festbetrag = 0;
   else
   {
      if ( *wert == '\0' ) return 0;   /* keine Aenderung des Festbetrages */
      festbetrag = atol( wert );
   }

   if ( ( wert = GetWert( pSart, "C00FBSTUFE", errmld ) ) == NULL ) return 1;
   febstufe = *wert;

   if ( mode == FILL_MODE )
   {
      if ( FebLaden( lade_mode, wegfall, artikel_nr, datum, festbetrag, febstufe,
                     tagesdatum, errmld, code ) == 0 )
         anz_ok++;
      else
          s = 1;
   }
   else
   {
#ifdef MSDOS
      printf( "%c %8.0ld %8.0ld %10.0ld\n",
              satzart, artikel_nr, datum, festbetrag  );
#endif
   }

   return s;
}


static long GenFebNeu( char *datei, char *satzart, int mode,
                       char *idd_file, char *errmld )
{
   sSatzDesc sD;

   sD.satzart = satzart;
   sD.mode = mode;
   sD.Fill = &FillFebSatz;
   return GenIfaSatz( datei, &sD, idd_file, errmld );
}

static void ExtractPfad( char *str )
{
  int i;
  int found;
  found = 0;
  i = strlen( str ) - 1;

  while ( i >= 0 && !found )
  {
     found = str[i] == ':' || str[i] == '\\' || str[i] == '/';
     if ( !found ) i--;
  }
  str[i+1] = '\0';
}


static long GenAll( char *datei[], char *pfad, char *satzart, int mode,
                    char *idd_file, char *errmld  )
{
   int  i;
   long s;

   i = 0;
   s = 0;
   while ( s == 0 && datei[i] != NULL )
   {
      ExtractPfad( pfad );
      strcat( pfad, datei[i] );
      s = GenFebNeu( pfad, satzart, mode, idd_file, errmld );
      i++;
   }
   return s;
}

#define ANZ_DATEI 10

static long GenFestb( char *db, char* ili_file, char *idd_file, char *satzart,
                      char *prot_file, char *errmld )
{
   long s;
   int i;
   long datum;
   char *datei[ANZ_DATEI];
   char datstr[15];

   s = IfaLieferung( ili_file, satzart, datei, ANZ_DATEI, &datum, idd_file,
                     errmld );

   sprintf( datstr, "f%6.6ld", datum%1000000 );
   strcat ( prot_file, datstr );

   tagesdatum = GetPhoDate();

   if ( s == 0 )
   {
      s = GenAll( datei, ili_file, satzart, TEST_MODE, idd_file, errmld );
      if ( s == 0 )
      {
        s = 1;
        if ( OpenBase( db, errmld ) == 0 )
        {
          if (  OpenPflege( user, errmld ) == 0 )
          {
            if ( FebLadenInit( tagesdatum, lade_mode, errmld ) == 0 )
            {
              if ( feb_OpenProtokol( prot_file, 1, lade_mode, errmld ) == 0 )
              {
                anz_ok = 0;
                s = GenAll( datei, ili_file, satzart, FILL_MODE, idd_file, errmld );
                feb_CloseProtokol( s == 0, anz_ok, errmld );
              }
              FebLadenClose( lade_mode );
            }
          }
           CloseBase( );
        }
      }
   }

   for ( i = 0; i < ANZ_DATEI; i++ )
     if ( datei[i] != NULL )
       free( datei[i] );

   return s;
}

#define FILE_LEN 20

long GenIfaFebNeu( char *db, char *lmode, char* ili_direc, char *idd_direc, char *errmld )
{
    long s;
    char satzart[31];
    char *idd_file;
    char *ili_file;
    char *prot_file;

    if ( !( *lmode == '0' || *lmode == '1' || *lmode == '2' || *lmode == '3' ) )
    {
       strcpy( errmld, "mode = 0 oder mode = 1 oder mode = 2 oder mode = 3" );
       return 1;
    }

    lade_mode = lmode;

    idd_file = malloc( strlen( idd_direc ) + FILE_LEN + 1 );
    if ( idd_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler GenIfaFebNeu" );
       return 1;
    }

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( ili_file == NULL )
    {
       free( idd_file );
       strcpy( errmld, "malloc-Fehler GenIfaFebNeu" );
       return 1;
    }

    strcpy( idd_file, idd_direc );
    strcat( idd_file, "/defprod.ifa" );
    if ( IfaSatzName( idd_file, SatzartPhx, satzart, errmld ) != 0 )
    {
       free( ili_file );
       free( idd_file );
       return 1;
    }

    prot_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( prot_file == NULL )
    {
       free( ili_file );
       free( idd_file );
       return 1;
    }

    strcpy( idd_file, idd_direc );
    strcat( idd_file, "/definifa.idd" );
    strcpy( ili_file, ili_direc );
    strcat( ili_file, "/liefer.ili" );
    strcpy( prot_file, ili_direc );
    strcat( prot_file, "/" );
    s = GenFestb( db, ili_file, idd_file, satzart, prot_file, errmld );

    free( prot_file );
    free( ili_file );
    free( idd_file );

    if ( s == 0 )
       strcpy( errmld, "Laden der FEB-Datei erfolgreich" );
    return 1;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : loeschen                                            *
 * ---------------------------------------------------------------------- */

long DeleteIfaFeb( char *db, char *errmld )
{
    long status;
    long tagesdatum;

    tagesdatum = GetPhoDate();

    status = OpenBase( db, errmld );
    if ( status == 0 )
    {
       status = OpenPflege( user, errmld );
       if ( status == 0 )
       {
          status = DeleteAll_Zartfeb2( tagesdatum, errmld );
       }
       CloseBase( );
    }

    if ( status != 0 )
      return 1;
/*
    strcpy( errmld, "Loeschen der FEB-Eintraege erfolgreich" );
*/
    return 0;
}


/* ---------------------------------------------------------------------- *
 * Funktion         : Status auf 'bearbeitet' setzen                      *
 * ---------------------------------------------------------------------- */

long SetBearbStat ( char *verz, char *errmld )
{
   int s;
   s = WriteIfaStatus ( SatzartPhx, verz, errmld  );
   if ( s == 0 )
   {
      strcpy( errmld, "Vorgang erfolgreich\n" );
      strcat( errmld, "Status Festbetrag = 'bearbeitet'" );
      return 0;
   }
   else
      return 1;
}



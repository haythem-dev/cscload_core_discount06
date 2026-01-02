/* ---------------------------------------------------------------------- *
 *                         a_iherst.c                                     *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Protokoll fuer DKLIF                                 *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 04.02.00                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */


#define TEST_MODE 0
#define FILL_MODE 1

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <phodate.h>
#include <phozeit.h>

#include "wr_prot.h"

#include "ifa_satz.h"
#include "ifa_info.h"
#include "ifa_stat.h"


static char *SatzartPhx = "PHERSTEL";
static char strich[200];

static long ifadatumnr;
static long satznr;

/* --- page length / number ------------------- */

#define MAX_ZEILE  59

static long zeile = MAX_ZEILE;
static long seite = 1;

/* --- page header ------------------------------ */

static char* u0 =
   "ZPIHERST: PROTOKOLL IFA-AENDERUNG HERSTELLER";

static char* z0 =
   "FIRMA NAME                                                                               SA LKZ  DATUM        ";

/* ------------------------------------------------------------------ */

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


static void str_lcpy( char *s1, char *s2, int lng1 )
{
   int lng2;
   lng2 = strlen( s2 );
   if ( lng2 < lng1 )
   {
      while ( lng2-- > 0 ) { *s1++ = *s2++; lng1--; }
      while ( lng1-- > 0 ) *s1++ = ' ';
   }
   else
      while ( lng1-- > 0 ) *s1++ = *s2++;
   *s1 = '\0';
}

static void her_Kopf_0( char *buf )
{

   char dat_str[20];
   long zeit;
   ConvFromPhoDate( dat_str, GetPhoDate(), "tt.mm.jjjj" );
   zeit = GetPhoTime( );

   sprintf( buf,
            "%s     DATUM: %s UHRZEIT: %.2ld:%.2ld:%.2ld SEITE: %ld",
            u0,
            dat_str,
            zeit/10000,
            (zeit/100)%100,
            zeit%100,
            seite++ );
}

static void her_Kopf_1( char *buf )
{
   sprintf( buf,"%s",z0 );
}

static void her_kopf( char *buf )
{
   if ( zeile >= MAX_ZEILE )
   {
      if ( seite > 1 )
         WriteVorschub( );
      zeile = 0;
      her_Kopf_0( buf );
      WriteZeile( buf );
      WriteLeerZeile( );
      her_Kopf_1( buf );
      WriteZeile( buf );
      
      strcpy( strich, buf );
      memset( strich, '-', strlen(z0) + 15 );

   }
}


static void insleer( char *zeile, int lng )
{
   int l1;
   l1 = strlen( zeile );
   memset( &zeile[l1], ' ', lng );
   zeile[l1 + lng] = '\0';
}

 /* neu 05.04.2001 */
static int testblank( char *str )
{
	if ( *str == '\0' ) 
		return 0;
	while ( *str && *str == ' ' ) str++;
	return *str == '\0';
}


static void inswert( char *zeile, char *wert, int lng )
{
   char druwert[100];
   str_lcpy( druwert, wert, lng );
   /* neu 29.03.2001 */
   /*
   if ( *wert == '\0' ) 
	   *druwert= '*';
   */
   /* neu 05.04.2001 */
   if ( *wert != '\0' && testblank( druwert ) )
	   *druwert= '*';

   strcat( zeile, druwert );
}

static void Upper (unsigned char *s)
{
	int i;
	for (i = 0; i < (int) strlen( (char *) s); i++)
	{
		/* ä/ö/ü/ß nicht möglich -> muss vorher umgewandelt werden */
		if ((s[i] >= 97 && s[i] <= 122))
		{
			s[i]-=32;
		}
	}
}

static char *GetWert( sSatzArt *pSart, char* feld, char *errmld )
{
   char *wert;
   wert = GetWertFromSatzArtViaFeldName( pSart, feld );
   
   if ( wert == NULL )
      sprintf( errmld, "kein Wert fuer Feld %s", feld );
   else
	   Upper(wert);
   
   return wert;
}

static int IfaFill( char *zeile1, char *zeile2, char *zeile3,
				   char *zeile4, char *zeile5, char *zeile6, char *zeile7, 
                    sSatzArt *pSart, char *errmld )
{
   char dat_str[14];
   char *wert;

   *zeile1 = '\0';
   *zeile2 = '\0';
   *zeile3 = '\0';
	*zeile4 = '\0';
	*zeile5 = '\0';
	*zeile6 = '\0';
	*zeile7 = '\0';

   /* zeile 1 */
   if ( ( wert = GetWert( pSart, "B00ADRNR", errmld ) ) == NULL ) return 1;
   inswert( zeile1, wert, 5 );
   insleer( zeile1, 2 );
   if ( ( wert = GetWert( pSart, "B00NAME1", errmld ) ) == NULL ) return 1;
   inswert( zeile1, wert, 80 );
   insleer( zeile1, 3 );
   if ( ( wert = GetWert( pSart, "B00SSATZ", errmld ) ) == NULL ) return 1;
   inswert( zeile1, wert, 1 );
   insleer( zeile1, 1 );
   if ( ( wert = GetWert( pSart, "B00LKZ", errmld ) ) == NULL ) return 1; 
   inswert( zeile1, wert, 1 );
   insleer( zeile1, 1 );
   if ( ( wert = GetWert( pSart, "B00GDAT", errmld ) ) == NULL ) return 1;
   ConvFromPhoDate( dat_str, atol(wert), "tt.mm.jjjj" );
   inswert( zeile1, dat_str, 10 );

   /* zeile 2 */
   insleer( zeile2, 7 );
   if ( ( wert = GetWert( pSart, "B00NAME2", errmld ) ) == NULL ) return 1;
   inswert( zeile2, wert, 40 );
   if ( ( wert = GetWert( pSart, "B00NAME3", errmld ) ) == NULL ) return 1;
   inswert( zeile2, wert, 40 );
   
   /* zeile 3 */
   inswert( zeile3, "STRASSE ", 8 );
   if ( ( wert = GetWert( pSart, "B00STR", errmld ) ) == NULL ) return 1;
   inswert( zeile3, wert, 40 );
   insleer( zeile3, 2 );
   inswert( zeile3, "HAUSNR VON/BIS ", 15 );
   if ( ( wert = GetWert( pSart, "B00HNRV", errmld ) ) == NULL ) return 1;
   inswert( zeile3, wert, 4 );
   insleer( zeile3, 1 );
   if ( ( wert = GetWert( pSart, "B00HNRVZ", errmld ) ) == NULL ) return 1;
   inswert( zeile3, wert, 4 );
   inswert( zeile3, " / ", 3 );
   if ( ( wert = GetWert( pSart, "B00HNRB", errmld ) ) == NULL ) return 1;
   inswert( zeile3, wert, 4 );
   insleer( zeile3, 1 );
   if ( ( wert = GetWert( pSart, "B00HNRBZ", errmld ) ) == NULL ) return 1;
   inswert( zeile3, wert, 4 );
   
   /* zeile 4 */
   if ( ( wert = GetWert( pSart, "B00LAND", errmld ) ) == NULL ) return 1;
   inswert( zeile4, wert, 3 );
   insleer( zeile4, 1 );
   if ( ( wert = GetWert( pSart, "B00PLZZU1", errmld ) ) == NULL ) return 1;
   inswert( zeile4, wert, 10 );
   insleer( zeile4, 1 );
   if ( ( wert = GetWert( pSart, "B00ORTZU", errmld ) ) == NULL ) return 1;
   inswert( zeile4, wert, 40 );
   inswert( zeile4, " WWW ", 5 );
   if ( ( wert = GetWert( pSart, "B00HOMEPAG", errmld ) ) == NULL ) return 1;
   inswert( zeile4, wert, 60 );
  
   /* zeile 5 */
   inswert( zeile5, "POSTF   ", 8 );
   if ( ( wert = GetWert( pSart, "B00PLZPF1", errmld ) ) == NULL ) return 1;
   inswert( zeile5, wert, 10 );
   insleer( zeile5, 1 );
   if ( ( wert = GetWert( pSart, "B00ORTPF", errmld ) ) == NULL ) return 1;
   inswert( zeile5, wert, 40 );
   inswert( zeile5, "  POSTFACH ", 11 );
   if ( ( wert = GetWert( pSart, "B00PF1", errmld ) ) == NULL ) return 1;
   inswert( zeile5, wert, 10 );
   inswert( zeile5, "  PLZ GROSSKUNDE ", 17 );
   if ( ( wert = GetWert( pSart, "B00PLZGK1", errmld ) ) == NULL ) return 1;
   inswert( zeile5, wert, 10 );  
   
   /* zeile 6 */
   inswert( zeile6, "TEL1    ", 8 );
   if ( ( wert = GetWert( pSart, "B00TEL1", errmld ) ) == NULL ) return 1;
   inswert( zeile6, wert, 24 );
   inswert( zeile6, "   TEL2 ", 8 );
   if ( ( wert = GetWert( pSart, "B00TEL2", errmld ) ) == NULL ) return 1;
   inswert( zeile6, wert, 24 );
   inswert( zeile6, "   FAX1 ", 8 );
   if ( ( wert = GetWert( pSart, "B00FAX1", errmld ) ) == NULL ) return 1;
   inswert( zeile6, wert, 24 );
   inswert( zeile6, "   FAX2 ", 8 );
   if ( ( wert = GetWert( pSart, "B00FAX2", errmld ) ) == NULL ) return 1;
   inswert( zeile6, wert, 24 );
   
   /* zeile 7 */
   inswert( zeile7, "EMAIL ", 6 );
   if ( ( wert = GetWert( pSart, "B00EMAIL", errmld ) ) == NULL ) return 1;
   inswert( zeile7, wert, 60 );
   inswert( zeile7, "/", 1 );
   if ( ( wert = GetWert( pSart, "B00EMAIL2", errmld ) ) == NULL ) return 1;
   inswert( zeile7, wert, 60 );
   
   return 0;
}

static int  FillHerstelSatz( sSatzArt *pSart, int mode, char *errmld )
{
   int  s;

   char zeile0[200];
   char zeile1[200];
   char zeile2[200];
   char zeile3[200];
   char zeile4[200];
   char zeile5[200];
   char zeile6[200];
   char zeile7[200];

   s = IfaFill( zeile1, zeile2, zeile3, zeile4, zeile5, zeile6, zeile7, pSart, errmld );
   if ( mode != FILL_MODE )
   {
      if ( s == 0 )
        return 0;
      else
        return 1;
   }

   if ( s != 0 )
   {
      WriteLeerZeile( );
      WriteZeile( errmld );
      return 1;
   }

   satznr++;

   her_kopf  ( zeile0 );
   WriteZeile( strich );
   WriteZeile( zeile1 );
   WriteZeile( zeile2 );
   WriteZeile( zeile3 ); 
   WriteZeile( zeile4 );
   WriteZeile( zeile5 );
   WriteZeile( zeile6 );
   WriteZeile( zeile7 );
   
   return 0;
}

static long GenHerstelProt( char *datei, char *satzart, int mode,
                            char *idd_file, char *errmld )
{
   sSatzDesc sD;

   sD.satzart = satzart;
   sD.mode = mode;
   sD.Fill = &FillHerstelSatz;
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

   satznr = 0;   /* !!!!!! globale Variable */

   i = 0;
   s = 0;
   while ( s == 0 && datei[i] != NULL )
   {
      ExtractPfad( pfad );
      strcat( pfad, datei[i] );
      s = GenHerstelProt( pfad, satzart, mode, idd_file, errmld );
      i++;
   }
   return s;
}

#define ANZ_DATEI 10

static long GenHersProtok( char* ili_file, char *idd_file, char *prt_file,
                           char *satzart, char *errmld )
{
   long s;
   int i;
   long datum;
   char *datei[ANZ_DATEI];
   char nr[20];

   s = IfaLieferung( ili_file, satzart, datei, ANZ_DATEI, &datum, idd_file,
                     errmld );

   ifadatumnr = datum;   /* !!!!!! globale Variable */


   sprintf( nr, "h%6.6ld", ifadatumnr%1000000 );
   strcat( prt_file, nr );

   if ( s == 0 )
   {
      s = GenAll( datei, ili_file, satzart, TEST_MODE, idd_file, errmld );
      if ( s == 0 )
      {
         s = OpenFile( prt_file, "ifa", 1, 0, errmld );
         if ( s == 0 )
         {
            s = GenAll( datei, ili_file, satzart, FILL_MODE, idd_file, errmld );
            CloseFile( );
         }
      }
   }

   for ( i = 0; i < ANZ_DATEI; i++ )
     if ( datei[i] != NULL )
       free( datei[i] );

   return s;
}



#define FILE_LEN 20

long GenIfaProtok( char* ili_direc, char *idd_direc, char *errmld )
{
    char satzart[31];
    char *idd_file;
    char *ili_file;
    char *prt_file;

    idd_file = malloc( strlen( idd_direc ) + FILE_LEN + 1 );
    if ( idd_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler GenIfaProtok" );
       return 1;
    }

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( ili_file == NULL )
    {
       free( idd_file );
       strcpy( errmld, "malloc-Fehler GenIfaProtok" );
       return 1;
    }

    prt_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( prt_file == NULL )
    {
       free( ili_file );
       free( idd_file );
       strcpy( errmld, "malloc-Fehler GenIfaProtok" );
       return 1;
    }

    strcpy( idd_file, idd_direc );
    strcat( idd_file, "/defprod.ifa" );
    if ( IfaSatzName( idd_file, SatzartPhx, satzart, errmld ) != 0 )
    {
       free( ili_file );
       free( idd_file );
       free( prt_file );
       return 1;
    }

    strcpy( idd_file, idd_direc );
    strcat( idd_file, "/definifa.idd" );
    strcpy( ili_file, ili_direc );
    strcat( ili_file, "/liefer.ili" );
    strcpy( prt_file, ili_direc );
    strcat( prt_file, "/" );
    if ( GenHersProtok( ili_file, idd_file, prt_file, satzart, errmld ) != 0 )
    {
       free( ili_file );
       free( idd_file );
       free( prt_file );
       return 1;
    }

    free( ili_file );
    free( idd_file );
    free( prt_file );

    sprintf( errmld, "IFA-Protokoll erzeugt (%ld Hersteller)", satznr );

    return 0;
}



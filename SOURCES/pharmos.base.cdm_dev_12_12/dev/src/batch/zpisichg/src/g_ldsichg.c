/* ---------------------------------------------------------------------- *
 *                            G_LDSICHG.C                                 *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die IFA-Abschlagsdatei ein und integriert       *
 *                  die Saetze in den lokalen UPDATE-POOL                 *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 13.01.03                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

#include "ifa_satz.h"
#include "ifa_info.h"
#include <ifa_stat.h>

#if defined(MSDOS) || defined(WIN32)
#else
#include <unistd.h> /* unlink */
#endif

#include "zifaoabschlag.h"

#include "g_ifoabs.h"

/* --- Prototype  ------------------------------------------------------- */

long OpenBase( char *db, char *errmld );
void CloseBase( void );
void UpdateStatistics( char *relation );

/* -------- Kennung fuer BSSichG --------------- */

static char *SatzartPhx = "PBSSICHG";

/* ------------------- Gloable Variable ------------------------- */

#define TEST_MODE    0
#define FILL_MODE    1

static struct ZIFAOABSCHLAG ifa;

static long ifadatumnr;
static long satznr;

static long anz_upd;
static long anz_del;
static long anz_ins;

static int InsertMode;


static char *log_file;

/* --- Testversion ------------------------------------------------------ */
/*
#define TEST
*/

#if defined(MSDOS) || defined(WIN32)
#define ABBRUCH_NO_ERROR  -4711
#define MAX_TEST_SATZ      100
#endif

/* --- Return-Puffer ---------------------------------------------------- */

static char ret_buf[300];

/* --- lokale Variablen ------------------------------------------------- */

static long tages_datum;


/* ---------------------------------------------------------------------- */


static long IfaBearbeiteUpdMode( sSatzArt *pSart,
                                 long Pzn, char Ssatz, char *errmld )
{

   long status;

   status = SqlBeginWork();
   if ( status == 0 )
   {
      status = IfaOabschlagAendere( pSart, &ifa, 
									tages_datum, Pzn, Ssatz,
		                            &anz_upd, &anz_del, &anz_ins,
				                    errmld );
      if ( status == 2 )    /* hier status = 2 nicht relevant */
          status = 0;
      SqlCommitWork();
   }
   else
   {
      strcpy( errmld, "zifaoabschlag: " );
      strcat( errmld, DynErrmld() );
   }
   return status;
}


static long IfaBearbeiteInsMode( sSatzArt *pSart,
                                 long Pzn, char Ssatz, char *errmld )
{
   long status;

   if (!( Ssatz == '0' || Ssatz == '1' ) ) /* nur vollstaendige Saetze aufnehmen */
       return 0;

   ifa.C02PZNABS = Pzn;
   if ( IfaOabschlagFill( &ifa, pSart, tages_datum, errmld ) != 0 ) return 1;
   ifa.DATUM_ANLAGE = tages_datum;
   ifa.DATUM_AENDER = 0;
   status = InsertIfaOabschlag( &ifa, errmld );
   if ( status == 0 )
      anz_ins++;
   return status;
}

static long IfaBearbeite( sSatzArt *pSart,
                          long Pzn, char Ssatz, char *errmld )
{
    if ( InsertMode )
       return IfaBearbeiteInsMode( pSart, Pzn, Ssatz, errmld );
    else
       return IfaBearbeiteUpdMode( pSart, Pzn, Ssatz, errmld );
}

static int FillArtikelSatz( sSatzArt *pSart, int mode, char *errmld )
{
   int  s;
   char Ssatz;
   long Pzn;

   /* --- PZN --- */
   if ( GetIfaPzn( &Pzn, pSart, errmld ) != 0 ) return 1;

   /* --- StatusIndikator --- */
   if ( GetIfaStatus( &Ssatz, pSart, errmld ) != 0 ) return 1;

   if ( mode == FILL_MODE )         /* Artikel ohne PZN_Neu */
   {
      s = 0;
      if ( IsPruefzifferOk( Pzn ) )      /* nur Saetze mit gueltiger PZN aufnehmen */           
      { 
          long status;     
          status = IfaBearbeite( pSart, Pzn, Ssatz, errmld );
          if ( status != 0 ) s = 1;
          satznr++;
      }
   }
   else
   {
      char *ErrStr;

      ifa.C02PZNABS = Pzn;
      s = IfaOabschlagFill( &ifa, pSart, tages_datum, errmld );  /* zum Testen */
      if ( s != 0 ) return 1;
      satznr++;

      ErrStr = NULL;
/*
      if ( ( ErrStr = GetIfaOartPlausiErr(  ) ) != NULL )
      {
         FILE *fp;
         fp = fopen(log_file, "a");
         if ( fp != NULL )
         {
           fprintf( fp, "%7.0ld %7.0ld :: %s\n",
                    satznr, ifa.A00PZN, ErrStr );
           fclose(fp);
         }
      }
*/

#if defined(MSDOS) || defined(WIN32)
      if ( ErrStr == NULL )
/*       printf( "%7.0ld %7.0ld\n", satznr, ifa.A00PZN );   */
         printf( "%7.0ld %7.0ld :: %s\n", satznr, ifa.C02PZNABS, GetRefToIfaOabschlagPlausi() ); 
      else
         printf( "%7.0ld %7.0ld :: %s\n", satznr, ifa.C02PZNABS, ErrStr ); 
#endif
   }

#if defined(MSDOS) || defined(WIN32)
   /* !!!!! zum testen : Abbruch nach x Saetzen !!!!!!!!!!!!!!!*/
/* if ( mode == FILL_MODE ) */
    if ( satznr == MAX_TEST_SATZ )
    {
       if ( s == 0 ) s = ABBRUCH_NO_ERROR;    /* !!!!!!!!!!!!!!!!!!!!! */
    }
#endif

   return s;
}



static long GenArtikelNeu( char *datei, char *satzart, int mode,
                           char *idd_file, char *errmld )
{
   sSatzDesc sD;

   sD.satzart = satzart;
   sD.mode = mode;
   sD.Fill = &FillArtikelSatz;
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

/* !!!!! zum testen : kein Fillmode !!!!!!!!!!!!!!!*/
/*  if ( mode == FILL_MODE ) return 0; */

   i = 0;
   s = 0;
   while ( s == 0 && datei[i] != NULL )
   {
      ExtractPfad( pfad );
      strcat( pfad, datei[i] );
      s = GenArtikelNeu( pfad, satzart, mode, idd_file, errmld );
      i++;
   }


   /* !!!!! zum testen : Abbruch nach x Saetzen !!!!!!!!!!!!!!! */
   /* !!!!! siehe in FillArtikelSatz() !!!!!!!!!!!!!! */
#if defined(MSDOS) || defined(WIN32)
   if ( s == ABBRUCH_NO_ERROR ) s = 0;
#endif

   return s;
}

#define ANZ_DATEI 10

static long GenArtikel( char *db, char* ili_file, char *idd_file, char *satzart,
                        char *errmld )
{
   long s;
   int i;
   long datum;
   char *datei[ANZ_DATEI];

   s = IfaLieferung( ili_file, satzart, datei, ANZ_DATEI, &datum, idd_file,
                     errmld );

   ifadatumnr  = datum;          /* !!!!!! globale Variable */
   tages_datum = GetPhoDate();   /* !!!!!! globale Variable */

   if ( s == 0 )
   {
      satznr = 0;   /* !!!!!! globale Variable */
      s = GenAll( datei, ili_file, satzart, TEST_MODE, idd_file, errmld );
      if ( s == 0 )
      {
         s = 1;
         if ( OpenBase( db, errmld ) == 0 )
         {
            if ( Open_IfaOabschlag_FDs( errmld ) == 0 )
            {
               satznr  = 0;           /* !!!!!! globale Variable */
               anz_upd = 0;
               anz_del = 0;
               anz_ins = 0;
               InsertMode = TestIfaOabschlagInsertMode( errmld );

               if ( InsertMode != -1 )
                  s = GenAll( datei, ili_file, satzart, FILL_MODE,
                              idd_file, errmld );
            }
            Close_IfaOabschlag_FDs( );

            UpdateStatistics( "zifaoabschlag" );

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

long UrLoadIfaSichgNeu( char *db, char *ili_direc, char *idd_direc, char *errmld )
{
    char meld[100];
    char satzart[31];
    char *idd_file;
    char *ili_file;

    idd_file = malloc( strlen( idd_direc ) + FILE_LEN + 1 );
    if ( idd_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler GenIfaArtNeu: idd_file" );
       return 1;
    }

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( ili_file == NULL )
    {
       free( idd_file );
       strcpy( errmld, "malloc-Fehler GenIfaArtNeu: ili_file" );
       return 1;
    }

    log_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( log_file == NULL )
    {
       free( ili_file );
       free( idd_file );
       strcpy( errmld, "malloc-Fehler GenIfaArtNeu: log_file" );
       return 1;
    }
 

    strcpy( idd_file, idd_direc );
    strcat( idd_file, "/defprod.ifa" );
    if ( IfaSatzName( idd_file, SatzartPhx, satzart, errmld ) != 0 )
    {
       free( log_file ); 
       free( ili_file );
       free( idd_file );
       return 1;
    }

    strcpy( idd_file, idd_direc );
    strcat( idd_file, "/definifa.idd" );
    strcpy( ili_file, ili_direc );
    strcat( ili_file, "/liefer.ili" );
    strcpy( log_file, ili_direc );
    strcat( log_file, "/ifa.log" );

#ifdef WIN32
    _unlink( log_file );    /* alten log-file loeshen */
#else
    unlink( log_file );     /* alten log-file loeshen */
#endif

    if ( GenArtikel( db, ili_file, idd_file, satzart, errmld ) != 0 )
    {
       free( log_file ); 
       free( ili_file );
       free( idd_file );
       return 1;
    }

    free( ili_file );
    free( idd_file );
    sprintf( errmld, "Ifa-Artikel\n" \
                     "%7ld bearbeitet\n" \
                     "%7ld eingefuegt\n" \
                     "%7ld geaendert\n" \
                     "%7ld geloescht\n",
                     satznr,
                     anz_ins,
                     anz_upd,
                     anz_del  );


    /* als bearbeitet kennzeichnen */
    if ( WriteIfaStatus( SatzartPhx, ili_direc, meld  ) != 0 )
    {
       strcat( errmld, "\nStatus 'bearbeitet' wurde nicht gesetzt" );
    }


    return 0;
}



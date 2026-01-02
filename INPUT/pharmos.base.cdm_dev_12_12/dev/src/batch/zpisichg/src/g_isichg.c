/* ---------------------------------------------------------------------- *
 *                            G_ISICHG.C                                  *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die IFA-Abschlagsdatei ein und integriert       *
 *                  die Saetze in den lokalen UPDATE-POOL                 *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 23.01.03                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

#include <wpp_prot.h>
#include <wpp_dbas.h>
#include <zapflege.h>
/* --------------------------- */


#include "ifa_satz.h"
#include "ifa_info.h"
#include "ifa_stat.h"

#include "absladen.h"

#include "g_ifoabs.h"

#include "lifestyl.h"

#ifdef ABS_PROT_ALT
#include "abs_prot.h"
#else
#include "bss_prot.h"
#endif


/* --- Prototype  ------------------------------------------------------- */

long OpenBase( char *db, char *errmld );
void CloseBase( void );
void UpdateStatistics( char *relation );

/* --------  user -------------- */

static char *user = "IFA-ABS ";

/* -------- Kennung fuer BSSichG --------------- */

static char *SatzartPhx = "PBSSICHG";

/* ------------------- Gloable Variable ------------------------ */


#if defined(MSDOS) || defined(WIN32)
#define ABBRUCH_NO_ERROR  -4711
#define MAX_TEST_SATZ      100
#endif


#define TEST_MODE  0
#define FILL_MODE  1



static long tages_datum;
static long satznr;

static long anz_upd;
static long anz_del;
static long anz_ins;


static struct ZIFAOABSCHLAG oifa;

/* ------------------- Funktionen ------------------------ */


static long IfaBearbeite( sSatzArt *pSart,
                          long artikel_nr, char satzart, int mode, char *errmld )
{

	long status;

	int complete;

	status = SqlBeginWork();
	if ( status == 0 )
	{
		status = IfaOabschlagAendere( pSart, &oifa,
									  tages_datum, artikel_nr, satzart, 
									  &anz_upd, &anz_del, &anz_ins,
									  errmld );
		complete = 1;
		if ( status == 2 )    /* hier status = 2  relevant !!!!!!!!!!!!!!!!!!!!!!!!!! */
		{
			complete = 0;
			status = 0;
		}
		if ( status == 0 )
		{
			int wegfall;

			wegfall = satzart == '2';

			status = AbschlagLaden( artikel_nr, tages_datum, wegfall, &oifa,
									user, errmld );
		}
		if ( status == 0 )
			SqlCommitWork();
		else
			SqlRollbackWork();
   }
   else 
   {
      strcpy( errmld, "zifaoabschlag: " );
      strcat( errmld, DynErrmld() );
   }
   return status;
}

static int  FillAbschlagSatz( sSatzArt *pSart, int mode, char *errmld )
{
	int  s;
	char satzart;

	long artikel_nr;

	int  wegfall;

	s = 0;

    /* --- PZN --- */
    if ( GetIfaPzn( &artikel_nr, pSart, errmld ) != 0 ) return 1;

    /* --- StatusIndikator --- */
    if ( GetIfaStatus( &satzart, pSart, errmld ) != 0 ) return 1;

	wegfall = satzart == '2';

	if ( mode == FILL_MODE )
	{
		long status;
		satznr++;
		status = IfaBearbeite( pSart, artikel_nr, satzart, mode, errmld );
		if ( status != 0 ) s = 1;
	}
	else
	{
		char *ErrStr;
		oifa.C02PZNABS = artikel_nr;
		s = IfaOabschlagFill( &oifa, pSart, tages_datum, errmld );  /* zum Testen */
		if ( s != 0 ) return 1;
		satznr++;

		ErrStr = NULL;

#if defined(MSDOS) || defined(WIN32)
		{
			printf( "%c %7.0ld\n", satzart, artikel_nr );
		}
#endif
	}

#if defined(MSDOS) || defined(WIN32)
   /* !!!!! zum testen : Abbruch nach x Saetzen !!!!!!!!!!!!!!!*/
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
   sD.Fill = &FillAbschlagSatz;
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
/* if ( mode == FILL_MODE_1 || mode == FILL_MODE_2 ) return 0; */

   i = 0;
   s = 0;
   while ( s == 0 && datei[i] != NULL )
   {
      ExtractPfad( pfad );
      strcat( pfad, datei[i] );
      s = GenArtikelNeu( pfad, satzart, mode, idd_file, errmld );
      i++;
   }

#if defined(MSDOS) || defined(WIN32)
   /* !!!!! zum testen : Abbruch nach x Saetzen !!!!!!!!!!!!!!! */
   /* !!!!! siehe in FillArtikelSatz() !!!!!!!!!!!!!! */
   if ( s == ABBRUCH_NO_ERROR ) s = 0;
#endif

   return s;
}

#define ANZ_DATEI 10

static long GenAbschlag( char *db, char* ili_file, char *idd_file, char *satzart,
                         char *prot_file, char *errmld )
{
	long s;
	int i;
	int b_proto;
	long datum;
	char *datei[ANZ_DATEI];

	s = IfaLieferung( ili_file, satzart, datei, ANZ_DATEI, &datum, idd_file,
                      errmld );

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
				if (  OpenPflege( user, errmld ) == 0 )
				{
#ifdef VOR_12_01_2004
					if ( GetLifeStyle( errmld ) == 0 )
#endif
					{
						if ( Open_All_FDs( errmld ) == 0 )
						{
							if ( prot_file == NULL )
								b_proto = 0;
							else
							{
								char datstr[15];
								sprintf( datstr, "b%6.6ld", datum%1000000 );
								strcat ( prot_file, datstr );
								b_proto = 1;
							}
#ifdef VOR_12_01_2004
#ifdef ABS_PROT_ALT
							if ( Abs_OpenProtokol( prot_file, b_proto, errmld ) == 0 )   
#else
							if ( bss_OpenProtokol( prot_file, b_proto, errmld ) == 0 )
#endif
#endif
							{
								satznr = 0;
								s = GenAll( datei, ili_file, satzart, FILL_MODE,
											idd_file, errmld );
#ifdef VOR_12_01_2004
#ifdef ABS_PROT_ALT
								Abs_CloseProtokol(  );  
#else
								bss_CloseProtokol( );
#endif
#endif
							}
						}
						Close_All_FDs( );
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

long GenIfaSichgNeu( char *db, char *ili_direc, char *idd_direc, int b_proto, char *errmld )
{
	long s;
    char meld[100];
    char satzart[31];
    char *idd_file;
    char *ili_file;
    char *prot_file;

    idd_file = malloc( strlen( idd_direc ) + FILE_LEN + 1 );
    if ( idd_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler GenIfaSichgNeu: idd_file" );
       return 1;
    }

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( ili_file == NULL )
    {
       free( idd_file );
       strcpy( errmld, "malloc-Fehler GenIfaSichgNeu: ili_file" );
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
	if ( b_proto )
	{
		strcpy( prot_file, ili_direc );
	    strcat( prot_file, "/" );
		s = GenAbschlag( db, ili_file, idd_file, satzart, prot_file, errmld );
		free( prot_file );
	}
	else
		s = GenAbschlag( db, ili_file, idd_file, satzart, NULL, errmld );
    free( ili_file );
    free( idd_file );

	if ( s == 0 )
	{
		sprintf( errmld, "%ld Abschlags-Saetze erfolgreich geladen",
						 satznr );

		/* als bearbeitet kennzeichnen */
		if ( WriteIfaStatus( SatzartPhx, ili_direc, meld  ) != 0 )
		{
			strcat( errmld, "\nStatus 'bearbeitet' wurde nicht gesetzt" );
		}
	}
	return s;

}


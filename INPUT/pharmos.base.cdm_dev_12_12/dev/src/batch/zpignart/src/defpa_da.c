/* ---------------------------------------------------------------------- *
 *                       D E F P A _ D A T . C                            *
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
#if !defined(WIN32)
	#include <unistd.h>
#endif
#include <libscsvoodoo.h>

/*
DEFPA
======================================================================
Artikelnummer                          : PZN        :  0001,007,CH
Datum(JHJJMMTT)                        : DATE       :  0008,008,CH
Preis-Alt                              : AEPA       :  0016,007,CH,2
Preis-Neu                              : AEPN       :  0023,007,CH,2
Preis-Alt                              : GEPA       :  0030,007,CH,2
Preis-Neu                              : GEPN       :  0037,007,CH,2
Abrechnungsart                         : AART       :  0044,001,CH
Abrechnungstage                        : ATAG       :  0045,002,CH
*/


#define PROJ_LESE_ARTAUTIDEM \
       "PZN," \
       "DATUM," \
       "GEP_ALT," \
       "AEP_ALT," \
       "GEP_NEU," \
       "AEP_NEU," \
       "ERSTATTUNGSTAGE," \
       "FESTBETRAGSREGEL" 

struct lese_artautidem 
{
	long   PZN;
	long   DATUM;
	double GEP_ALT;
	double AEP_ALT;
	double GEP_NEU;
	double AEP_NEU;
	short  ERSTATTUNGSTAGE;
	char   FESTBETRAGSREGEL[2];
};


static FILE *fdDruck = (FILE*)0;

static char *datei = NULL;

/* --- Schnittstelle ------------------------------------ */


static long defpa_OpenFile( char *datei, char *errmld )
{
   fdDruck = fopen( datei, "w" );
   if ( fdDruck == (FILE *)0 )
   {
      strcpy( errmld, "defpa_OpenFile kann nicht geoeffnet werden" );
      return -1;
   }
   return 0;
}

static void defpa_CloseFile( )
{
   if ( fdDruck != (FILE *)0 )
      fclose( fdDruck );
   fdDruck = (FILE *)0;
}       

static void defpa_WriteFile( struct lese_artautidem *autidem )
{
/*
      fprintf( fdDruck, "%07ld%08ld%07.2f%07.2f%07.2f%07.2f%s%02d\n", 
		  	            autidem->PZN,
						autidem->DATUM,
						autidem->AEP_ALT,
						autidem->AEP_NEU,
						autidem->GEP_ALT,
						autidem->GEP_NEU,
						autidem->FESTBETRAGSREGEL,
						autidem->ERSTATTUNGSTAGE      );
*/
      fprintf( fdDruck, "%07ld%08ld%07ld%07ld%07ld%07ld%s%02d\n", 
		  	            autidem->PZN,
						autidem->DATUM,
						(long) ( autidem->AEP_ALT * 100 + 0.1 ),
						(long) ( autidem->AEP_NEU * 100 + 0.1 ),
						(long) ( autidem->GEP_ALT * 100 + 0.1 ),
						(long) ( autidem->GEP_NEU * 100 + 0.1 ),
						autidem->FESTBETRAGSREGEL,
						autidem->ERSTATTUNGSTAGE      );
}

static long Autidm_LeseLoop( long ifanr, char *errmld )
{
	struct lese_artautidem autidem;

	int  fd;
	long s;
	char sql[300];

    sprintf( sql, "select %s from artautidem where ifanr=%ld",
		           PROJ_LESE_ARTAUTIDEM,
		           ifanr );

	s = SqlOpenCs( &fd, sql );
	if ( s != 0 )
	{
		sprintf( errmld, "Autidm_LeseLoop: %s", DynErrmld() );
		return s;
	}
	s = SqlFetch( fd, 1, &autidem, NULL );
	if ( s == 100 )
		return s;

	while ( s == 0 )
	{
		defpa_WriteFile( &autidem );
		s = SqlFetch( fd, 1, &autidem, NULL );
	}

	if ( s == 100 )
		return 0;

	sprintf( errmld, "Autidm_LeseLoop: %s", DynErrmld() );
	return s;
}



long GenDefpa( long ifanr, char *datei, char *errmld )
{
	long s;
	s = defpa_OpenFile( datei, errmld );
	if ( s != 0 )
		return s;

	s = Autidm_LeseLoop( ifanr, errmld );

	defpa_CloseFile( );

	if ( s != 0 )
	{
#ifdef WIN32
		_unlink( datei );
#else
		unlink( datei );
#endif	
	}
	return s;
}

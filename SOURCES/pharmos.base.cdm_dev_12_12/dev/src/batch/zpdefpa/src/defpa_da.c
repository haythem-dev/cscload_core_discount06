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
#include <libscsvoodoo.h>
#include <phodate.h>

#if defined(MSDOS) || defined(WIN32)
 
#else
#include <unistd.h>
#endif

/* ----------------- Prototype ------------------------ */

void CloseBase(  );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void GenDefpaUsage( char *buf )
{
strcat( buf, "1. Defpa Datei generieren unter Angabe der IFANR\n"\
             "   zpdefpa 1 database dateiname ifanr { ifanr }\n" );
strcat( buf, "2. Defpa Datei generieren unter Angabe des Zeitraumes\n"\
             "   zpdefpa 2 database dateiname datumvon datumbis\n" );
}

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


static void UnLink( char *datei )
{
#if defined(MSDOS) || defined(WIN32)
    _unlink( datei );
#else
    unlink( datei );
#endif
}


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

static long Autidm_LeseLoop( char *datei, char *sql, char *errmld )
{
    struct lese_artautidem autidem;

    int  fd;
    long s;
    long anzahl;

    anzahl = 0;

/*  printf( "%s\n", sql );  */

    s = SqlOpenCs( &fd, sql );
    if ( s != 0 )
    {
        sprintf( errmld, "Autidm_LeseLoop: %s", DynErrmld() );
        return s;
    }
    s = SqlFetch( fd, 1, &autidem, NULL );
    if ( s == 100 )
    {
        sprintf( errmld, "kein Satz vorhanden\n" );
        return s;
    }

    while ( s == 0 )
    {
        defpa_WriteFile( &autidem );
        anzahl++;
        s = SqlFetch( fd, 1, &autidem, NULL );
    }

    if ( s == 100 )
    {
        if ( anzahl == 1 )
            sprintf( errmld, "%s mit %ld Satz erzeugt", datei, anzahl );
        else
            sprintf( errmld, "%s mit %ld Saetzen erzeugt", datei, anzahl );
        return 0;
    }

    sprintf( errmld, "Autidm_LeseLoop: %s", DynErrmld() );
    return s;
}

long GenDefpaIfanr( char *db, char *datei, long *ifanr, int anz, char *errmld )
{
    long s;
    char sql[1000];
    char cNr[20];
    int  i;

    s = OpenBase( db, errmld );
    if ( s != 0 )
        return s;

    s = defpa_OpenFile( datei, errmld );
    if ( s != 0 )
    {
        CloseBase();
        return s;
    }

    sprintf( sql, "select %s from ARTAUTIDEM where ERSTATTUNGSTAGE>0 and " \
                  "IFANR in (",
                  PROJ_LESE_ARTAUTIDEM );

    for ( i = 0; i < anz; i++ )
    {
        sprintf( cNr, "%ld", ifanr[i] );
        strcat( sql, cNr );
        if ( i == anz - 1 )
            strcat( sql, ")" );
        else
            strcat( sql, "," );
    }
	strcat( sql, " order by PZN,DATUM" );


    s = Autidm_LeseLoop( datei, sql, errmld );

    defpa_CloseFile( );

    CloseBase();

    if ( s != 0 )
        UnLink( datei );

    return s;
}

long GenDefpaZeitraum( char *db, char *datei, long datumvon, long datumbis, char *errmld )
{
    long s;
    char sql[300];

    if ( datumvon < 20000101 || !TestPhoDate( datumvon ) )
    {
        strcpy( errmld, "datumvon in der Form JJJJMMTT\n" );
        return 1;
    }
    if ( datumbis < 20000101 || !TestPhoDate( datumbis ) )
    {
        strcpy( errmld, "datumbis in der Form JJJJMMTT\n" );
        return 1;
    }   
    if ( datumvon > datumbis )
    {
        strcpy( errmld, "datumvon <= datumbis\n" );
        return 1;
    }   

    s = OpenBase( db, errmld );
    if ( s != 0 )
        return s;

    s = defpa_OpenFile( datei, errmld );
    if ( s != 0 )
    {
        CloseBase();
        return s;
    }

    sprintf( sql, "select %s from ARTAUTIDEM where ERSTATTUNGSTAGE>0 and " \
                  "DATUM>=%ld and DATUM<=%ld order by PZN,DATUM",
                   PROJ_LESE_ARTAUTIDEM,
                   datumvon,
                   datumbis );

    s = Autidm_LeseLoop( datei, sql, errmld );

    defpa_CloseFile( );

    CloseBase();

    if ( s != 0 )
        UnLink( datei );

    return s;
}


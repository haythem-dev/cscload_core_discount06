/* ---------------------------------------------------------------------- *
 *                         g_ifalf.c                                      *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Verwaltet die Ifa                                     *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 04.02.00                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#if defined(MSDOS) || defined(WIN32)
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#endif
#include <errno.h>

#include <libscsvoodoo.h>

#include "ifa_info.h"
#include "ifa_stat.h"

#define PROTOKOL "9"

static char *Satzart[] = { { "PARTIKEL" },
                           { "PHERSTEL" },
                           { "PFESTBET" },
                           { "PKLINIKB" }
                         };

#define ANZ_SATZART ( sizeof( Satzart ) / sizeof ( char* ) )


static char *GetSatzart( char *SatzartMode )
{
   char *SatzartPhx;
   if ( strcmp( SatzartMode, "0" ) == 0 )
      SatzartPhx = Satzart[0];
   else if ( strcmp( SatzartMode, "1" ) == 0 )
      SatzartPhx = Satzart[1];
   else if ( strcmp( SatzartMode, "2" ) == 0 )
      SatzartPhx = Satzart[2];
   else if ( strcmp( SatzartMode, "3" ) == 0 )
      SatzartPhx = Satzart[3];
   else
   {
      int i;
      int found;
      SatzartPhx = SatzartMode;
      i = 0;
      found = 0;
      while ( i < ANZ_SATZART && !found )
        found = strcmp( SatzartPhx, Satzart[i++] ) == 0;
      if ( !found ) SatzartPhx = NULL;
   }
   return SatzartPhx;
}

static long GetIfaDateiVerz( char *buf )
{
	long s = 0;

#if !defined(WIN32)
	char *buf2; 

/*	strcpy (buf, getexecname());
	buf2 = dirname (buf); */

	buf2 = getcwd(buf, 813);

	strcpy (buf, buf2); 
	strcat (buf, "/../data/ifa/"); 
#endif

/* if ( ( s = UnxGetenv ( "WWS", buf ) ) != 0 )
   {
      strcpy( buf, "$WWS unbekannt\n" );
      strcat( buf, DynErrmld() );
   }
   else
   {
      strcat( buf, "/daten/ifaneud/" );
   } */

   return s;
}

static char *ExtractDateiName( char *name )
{
   int pos;
   pos = strlen( name ) - 1;
   while ( pos >= 0 && name[pos] != '/' ) pos--;
   pos++;
   return &name[pos];
}


static int IsNumber( char *str )
{
   while ( *str && isdigit( *str ) ) str++;
   return *str == '\0';
}

static int TestDateiMuster( char *cName )
{
   /* lf000410  */
   return  strlen( cName ) == 8 &&
           memcmp( cName, "lf", 2 ) == 0 &&
           IsNumber( &cName[2] );
}


#if defined(MSDOS) || defined(WIN32)
static long IsVerzeichnis( char *TestProtokol, int index )
{
   memcpy( TestProtokol, "test -d ", index );
   return  UnxHsystem( TestProtokol );
}

#else
static long IsVerzeichnis( char *TestProtokol, int index )
{
   struct stat buf;
   int  status;
   status = stat( &TestProtokol[index], &buf);
   if (status == -1) return 1;
   if ((buf.st_mode & S_IFMT) != S_IFDIR) return 1;
   return 0;
}
#endif


static long GetIfaDatei( char *buf, char *SatzartPhx, char* pfad, int pos,
                         int gepackt )
{
   long s;
   int  mode;
   int  index;
   int  index1;
   char datei[300];
   char TestProtokol[500];
   char errmld[100];
   char *cName;
   char log[80];
   int  leer;
   int  is;

   strcpy( TestProtokol, "        " );      /* "test -d " */
   index1 = strlen( TestProtokol );
   strcat( TestProtokol, buf );
   index  = strlen( TestProtokol );

   mode = DIR_SUBDIR;
   s = UnxDirEntry( buf, datei, &mode );

   is = 0;
   leer = 1;

   sprintf(log, "Test 1: s = %d, mode = %d, is = %d, leer = %d, SatzartPhx = %s", s, mode, is, leer, SatzartPhx);
/*    printf("\n%s", log); */

   if ( s == 0 )
   {

      if ( !gepackt )
         *buf = '\0';

      while ( s == 0 )
      {
         cName = ExtractDateiName( datei );

         if ( TestDateiMuster( cName ) )
         {
             is = 1;
             if ( SatzartPhx != NULL )
             {
                if ( strcmp( SatzartPhx, PROTOKOL ) == 0 )
                {
                   strcpy( &TestProtokol[index], cName );
                   strcat( TestProtokol, "/protokol" );
                   is = IsVerzeichnis( TestProtokol, index1 ) == 0;
                }
                else
                {
                   strcpy( &pfad[pos], cName );
                   is = ReadIfaStatus( SatzartPhx, pfad, errmld );
                }
             }
             if ( is == 1 )     /* SatzartPhx nicht bearbeitet */
             {
                if ( gepackt )
                   strcat( buf, &cName[2] );
                else
                {
                   strcat( buf, cName );
                   strcat( buf, "\n"  );
                }
                leer = 0;
             }
             else if ( is == -1 )
             {
                leer = 1;
                s = 1;
             }
         }

         if ( is != -1 )
            s = UnxDirEntry( NULL, datei, &mode );
      }
   }

   sprintf(log, "Test 2: s = %d, mode = %d, is = %d, leer = %d, SatzartPhx = %s", s, mode, is, leer, SatzartPhx);
/*    printf("\n%s", log); */

   if ( leer )
   {
      s = -1;

	  if ( mode == DIR_ERROR )
      {
		 s = 1;

         if ( SatzartPhx == NULL )
            strcpy( buf, "Keine IFA-Verzeichnisse der Form lf000000 vorhanden" );
         else
         {
            if ( strcmp( SatzartPhx, PROTOKOL ) == 0 )
               strcpy( buf, "Keine Protokolle vorhanden" );
            else
            {
               strcpy( buf, "Keine IFA-Aenderungen fuer '" );
               strcat( buf, SatzartPhx );
               strcat( buf, "' vorhanden " );
            }
         }
      }
      else if ( is == -1 )
         strcpy( buf, errmld );
      else
         strcpy( buf, DynErrmld() );
   }
   else
      s = 0;

   return s;
}

/* ---------------------------------------------------------------------- *
 *                  Ifaverzeichnisse ermitteln                            *
 * ---------------------------------------------------------------------- */

long GetIfaVerz( char *SatzartMode, char *buf, int gepackt )
{
   char *SatzartPhx;
   char *pfad;
   int  pos;
   long s;

   pos  = 0;
   pfad = NULL;
   SatzartPhx = NULL;

   if (  GetIfaDateiVerz( buf ) != 0 )
      return 1;

   if ( SatzartMode != NULL )
   {
      char *muster;
      muster = "lf010299";

      if ( strcmp( SatzartMode, PROTOKOL ) != 0 )
      {
         SatzartPhx = GetSatzart( SatzartMode );
         if ( SatzartPhx == NULL )
         {
            strcpy( buf, "Parameter 'mode' falsch" );
            return 1;
         }
      }
      else
      {
         SatzartPhx =  SatzartMode;
      }

      pos = strlen( buf );
      pfad = malloc( pos + strlen( muster ) + 1 );
      if ( pfad == NULL )
      {
         strcpy( buf, "malloc-Fehler bei GetIfaVerz" );
         return 1;
      }
      strcpy( pfad, buf );
      strcat( pfad, muster );
   }

   s =  GetIfaDatei( buf, SatzartPhx, pfad, pos, gepackt );

   if ( pfad != NULL )
      free( pfad );

   if ( s == 1 )
      return 2;
   else if ( s != 0 )
      return 1;
   else
	  return 0;
}


/* ---------------------------------------------------------------------- *
 *                  Ifaverzeichnis erstellen                              *
 * ---------------------------------------------------------------------- */

static void MarkLiefer( char *ili_file, char *idd_file, int pos, char *buf )
{
    long datum;
    int  s;
    int  i;
    int  ili_pos;
    char IfaSatzart[ANZ_SATZART][10];
    int  status[ANZ_SATZART];
    char errmld[150];
    char *datei[1];

    strcpy( &idd_file[pos], "idd/defprod.ifa" );

    i = 0;
    while ( i < ANZ_SATZART )
    {
       s = IfaSatzName ( idd_file, Satzart[i], IfaSatzart[i], errmld );
       if ( s != 0 )
          strcpy( IfaSatzart[i], "*" );
       i++;
    }

    strcpy( &idd_file[pos], "idd/definifa.idd" );
    ili_pos = strlen( ili_file );
    strcat( ili_file, "/liefer.ili" );
    i = 0;
    while ( i < ANZ_SATZART )
    {
       status[i]  = IfaLieferung( ili_file, IfaSatzart[i], datei, 1, &datum,
                                  idd_file, errmld );
       if ( datei[0] != NULL ) free( datei[0] );
       i++;
    }
/*
    printf( "%s\n%s\n", idd_file, ili_file );
    for ( i = 0; i < ANZ_SATZART; i++ )
      printf( "%s  %s: %d\n", Satzart[i], IfaSatzart[i], status[i] );
*/

    s = 0;
    for ( i = 0; i < ANZ_SATZART; i++ )
       if ( status[i] != 0 ) s++;

    if ( s == 0 ) return;


    ili_file[ili_pos] = '\0';   /* ili-Verzeichnis */

    strcat( buf, "\nFolgende Satzart" );
    if ( s > 1 )
       strcat( buf, "en sind" );
    else
       strcat( buf, " ist" );
    strcat( buf, " nicht in der Lieferung:\n" );
    for ( i = 0; i < ANZ_SATZART; i++ )
    {
       if ( status[i] != 0 )
       {
          WriteIfaStatus( Satzart[i], ili_file, errmld  );
          strcat( buf, IfaSatzart[i] );
          s--;
          if ( s > 0 )
            strcat( buf, "  " );
       }
    }
}

static int MoveFile( char *mvbefehl, char *QuellVerz, char *QuellDatei,
                     char *ZielVerz, char *errmld )
{
   strcpy( mvbefehl, "mv -f " );
   strcat( mvbefehl, QuellVerz );
   strcat( mvbefehl, "/" );
   strcat( mvbefehl, QuellDatei );
   strcat( mvbefehl, " " );
   strcat( mvbefehl, ZielVerz );
/*
   printf( "%s\n", mvbefehl );
*/
   if ( system( mvbefehl ) >= 0 )
      return 0;
   sprintf( errmld,
            "Fehler beim umkopieren von %s\nerrno=%d",
            QuellDatei, errno );

   return 1;
}


#define FILE_LEN 30

long CreateIfaVerz( char* QuellDirec, char *buf, int WithCopy )
{
    char *idd_file;
    char *ili_file;
    char *mvbefehl;
    char *QuellVerz;
    long datum;
    long s;
    int  pos;

    if (  GetIfaDateiVerz( buf ) != 0 )
       return 1;

    pos = strlen( buf );
    idd_file = malloc( pos + FILE_LEN + 1 );
    if ( idd_file == NULL )
    {
       strcpy( buf, "malloc-Fehler CreateIfaVerz idd_file" );
       return 1;
    }
    strcpy( idd_file, buf );
    strcat( idd_file, "idd/definifa.idd" );  /* idd_direc endet mit '/' */

    if ( QuellDirec != NULL )
       QuellVerz = malloc( strlen( QuellDirec ) + 1 );
    else
       QuellVerz = malloc( pos + FILE_LEN + 1 );
    if ( QuellVerz == NULL )
    {
       free( idd_file );
       strcpy( buf, "malloc-Fehler CreateIfaVerz QuellVerz" );
       return 1;
    }
    if ( QuellDirec != NULL )
       strcpy( QuellVerz, QuellDirec );
    else
    {
       strcpy( QuellVerz, buf );
       strcat( QuellVerz, "lfakt" );
    }

    if ( pos > (int) strlen( QuellVerz ) )
      ili_file = malloc( pos + FILE_LEN + 1 );
    else
      ili_file = malloc( strlen( QuellVerz ) + FILE_LEN + 1 );
    if ( ili_file == NULL )
    {
       free( QuellVerz );
       free( idd_file );
       strcpy( buf, "malloc-Fehler CreateIfaVerz ili_file" );
       return 1;
    }
    strcpy( ili_file, QuellVerz );
    strcat( ili_file, "/liefer.ili" );

    if ( WithCopy )
    {
       mvbefehl = malloc( strlen( ili_file ) + strlen( idd_file ) + 50 );
       if ( mvbefehl == NULL )
       {
          free( idd_file );
          free( QuellVerz );
          free( ili_file );
          strcpy( buf, "malloc-Fehler CreateIfaVerz mvbefehl" );
          return 1;
       }
    }

    s = IfaLieferDatum( &datum, ili_file, idd_file, buf );

    s = 1; /* suppose: false */

    if ( datum > 0 )
    {
       char NewDirec[20];
       sprintf( NewDirec, "%ld", datum );
       if ( strlen( NewDirec ) != 8 )
       {
          strcat( buf, ": IFA-Datum falsches Format" );
       }
       else
       {
          int  status;
          strcpy( ili_file, idd_file );
          memcpy( NewDirec, "lf", 2 );
          strcpy( &ili_file[pos], NewDirec );
#ifdef WIN32
          status = _mkdir ( ili_file );
#elif MSDOS
          status = mkdir ( ili_file );
#else
          status = mkdir ( ili_file, S_IRWXU | S_IRWXG | S_IRWXO );
#endif
          if ( status != 0 )
          {
             if ( errno != EEXIST )
                sprintf( buf,
                    "Verzeichnis\n%s\nkann nicht eingerichet werden\nerrno=%d",
                     ili_file, errno );
             else
                sprintf( buf,
                         "Verzeichnis\n%s\nbereits vorhanden\nerrno=%d",
                         ili_file, errno );

          }
          else if ( WithCopy )
          {
             int  syserr;
             status = MoveFile( mvbefehl, QuellVerz, "liefer.ili",
                                ili_file, buf );
             if ( status == 0 )
             {
                status = MoveFile( mvbefehl, QuellVerz, "liefd*.ild",
                                   ili_file, buf );
                if ( status != 0 )
                {
                   /* alles rueckgaengig machen */
                   char errmld[200];
                   if ( MoveFile( mvbefehl, ili_file, "liefer.ili",
                                  QuellVerz, errmld ) != 0 )
                   {
                      strcat( buf,
                              "\nliefer.ili kann nicht rueckgemoved werden" );
                      syserr = 1;
                   }
                }
             }
             if ( status != 0 )
             {
                strcpy( mvbefehl, "rmdir " );
                strcat( mvbefehl, ili_file );
                if ( system( mvbefehl ) < 0 )
                {
                   sprintf( buf, "\n%s kann nicht geloescht werden",
                            NewDirec );
                   syserr = 1;
                }
             }
             if ( status != 0 )
             {
                if ( syserr == 1 )
                   strcat( buf, "bitte Systemgruppe benachrichtigen" );
             }
             else
                s = 0;
          }
          else
             s = 0;
       }
    }

    if ( s == 0 )
    {
       if ( WithCopy )
       {
          sprintf( buf, "Erfolgreiche Uebernahme der IFA-Daten nach\n%s",
                        ili_file );
          MarkLiefer( ili_file, idd_file, pos, buf );
       }
       else
          sprintf( buf, "Folgendes IFA-Verzeichnis wurde angelegt:\n%s",
                        ili_file );
    }

    if ( WithCopy )
       free( mvbefehl );
    free( idd_file );
    free( QuellVerz );
    free( ili_file );

    return s;

}



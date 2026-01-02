/* ---------------------------------------------------------------------- *
 *                         g_datacarelf.c                                 *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Verwaltet die Datacare                                *
 * ---------------------------------------------------------------------- *
 * Autor          : K.Hinz (Kopie von g_ifaalf.c)                         *
 * erstellt am    : 26.01.05                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#if defined(_WIN32)
#include <direct.h>
#include <sys/stat.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#endif
#include <errno.h>

#include <libscsvoodoo/libscsvoodoo.h>

#include "ifa_info.h"
#include "ifa_stat.h"

#define PROTOKOL "9"

static char *Satzart[] = { { "PARTIKEL" }
                         };

#define ANZ_SATZART ( sizeof( Satzart ) / sizeof ( char* ) )


static char *GetSatzart( char *SatzartMode )
{
   char *SatzartPhx;
   if ( strcmp( SatzartMode, "0" ) == 0 )
      SatzartPhx = Satzart[0];
/*   else if ( strcmp( SatzartMode, "1" ) == 0 )
      SatzartPhx = Satzart[1];
   else if ( strcmp( SatzartMode, "2" ) == 0 )
      SatzartPhx = Satzart[2]; */
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

static long GetDatacareDateiVerz( char *buf )
{
	long s = 0;

#if !defined(_WIN32)
	char *buf2; 

/*	strcpy (buf, getexecname());
	buf2 = dirname (buf); */

	buf2 = getcwd(buf, 813);

	strcpy (buf, buf2); 
	strcat (buf, "/../data/datacare/"); 
#endif

/*   if ( ( s = UnxGetenv ( "WSS", buf ) ) != 0 )
   {
      strcpy( buf, "$WSS unbekannt\n" );
      strcat( buf, DynErrmld() );
   }
   else
   {
      strcat( buf, "/daten/datacareneud/" );
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
   return  strlen( cName ) == 8 &&
           memcmp( cName, "lf", 2 ) == 0 &&
           IsNumber( &cName[2] );
}


#if defined(_WIN32)
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


static long GetDatacareDatei( char *buf, char *SatzartPhx, char* pfad, int pos,
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
                   //is = ReadDatacareStatus( SatzartPhx, pfad, errmld );
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

   if ( leer )
   {
      if ( mode == DIR_ERROR )
      {
         if ( SatzartPhx == NULL )
            strcpy( buf,
                    "Keine Datacare-Verzeichnisse der Form lf000000 vorhanden" );
         else
         {
            if ( strcmp( SatzartPhx, PROTOKOL ) == 0 )
               strcpy( buf, "Keine Protokolle vorhanden" );
            else
            {
               strcpy( buf, "Keine Datacare-Aenderungen fuer '" );
               strcat( buf, SatzartPhx );
               strcat( buf, "' vorhanden " );
            }
         }
      }
      else if ( is == -1 )
         strcpy( buf, errmld );
      else
         strcpy( buf, DynErrmld() );
      s = -1;
   }
   else
      s = 0;
   return s;
}

/* ---------------------------------------------------------------------- *
 *                  Datacareverzeichnisse ermitteln                       *
 * ---------------------------------------------------------------------- */

long GetDatacareVerz( char *SatzartMode, char *buf, int gepackt )
{
   char *SatzartPhx;
   char *pfad;
   int  pos;
   long s;

   pos  = 0;
   pfad = NULL;
   SatzartPhx = NULL;

   if (  GetDatacareDateiVerz( buf ) != 0 )
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
         strcpy( buf, "malloc-Fehler bei GetDatacareVerz" );
         return 1;
      }
      strcpy( pfad, buf );
      strcat( pfad, muster );
   }

   s =  GetDatacareDatei( buf, SatzartPhx, pfad, pos, gepackt );

   if ( pfad != NULL )
      free( pfad );

   if ( s != 0 )
      return 1;
   return 0;
}



static int MoveFile( char *mvbefehl, char *QuellVerz, char *QuellDatei,
                     char *ZielVerz, char *errmld )
{
#ifdef _WIN32
   strcpy( mvbefehl, "move " );      
#else
   strcpy( mvbefehl, "mv -f " );      
#endif

   strcat( mvbefehl, QuellVerz );
   strcat( mvbefehl, "/" );
   strcat( mvbefehl, QuellDatei );
   strcat( mvbefehl, " " );
   strcat( mvbefehl, ZielVerz );

   if ( system( mvbefehl ) >= 0 )
      return 0;
   sprintf( errmld,
            "Fehler beim umkopieren von %s\nerrno=%d",
            QuellDatei, errno );

   return 1;
}


#define FILE_LEN 30

long CreateDatacareVerz( char* QuellDirec, char *buf, int WithCopy )
{
    char *source_file;
    char *mvbefehl;
    char *QuellVerz;
    long datum;
    long s;
    int  pos;

    if (  GetDatacareDateiVerz( buf ) != 0 )
       return 1;

    pos = strlen( buf );


    if ( QuellDirec != NULL )
       QuellVerz = malloc( strlen( QuellDirec ) + 1 );
    else
       QuellVerz = malloc( pos + FILE_LEN + 1 );
    if ( QuellVerz == NULL )
    {
       strcpy( buf, "malloc-Fehler CreateDatacareVerz QuellVerz" );
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
      source_file = malloc( pos + FILE_LEN + 1 );
    else
      source_file = malloc( strlen( QuellVerz ) + FILE_LEN + 1 );
    if ( source_file == NULL )
    {
       free( QuellVerz );
       strcpy( buf, "malloc-Fehler CreateDatacareVerz source_file" );
       return 1;
    }
    strcpy( source_file, QuellVerz );
    strcat( source_file, "/datacare.txt" );

    if ( WithCopy )
    {
       mvbefehl = malloc( strlen( source_file ) * 2 + 50 );
       if ( mvbefehl == NULL )
       {
          free( QuellVerz );
          free( source_file );
          strcpy( buf, "malloc-Fehler CreateDatacareVerz mvbefehl" );
          return 1;
       }
    }

	/* Datacare liefert keine liefer.ili -> fester Dateiname datacare.txt*/
    s = DatacareLieferDatum( &datum, source_file, buf ); 


    s = 1; /* suppose: false */

    if ( datum > 0 )
    {
       char NewDirec[20];
       sprintf( NewDirec, "%ld", datum );
       if ( strlen( NewDirec ) != 8 )
       {
          strcat( buf, ": Datacare-Datum falsches Format" );
       }
       else
       {
          int  status;

          memcpy( NewDirec, "lf", 2 );
          strcpy( &source_file[pos], NewDirec );
#ifdef _WIN32
          status = _mkdir ( source_file );
#else
          status = mkdir ( source_file, S_IRWXU | S_IRWXG | S_IRWXO );
#endif
          if ( status != 0 )
          {
             if ( errno != EEXIST )
                sprintf( buf,
                    "Verzeichnis\n%s\nkann nicht eingerichet werden\nerrno=%d",
                     source_file, errno );
             else
                sprintf( buf,
                         "Verzeichnis\n%s\nbereits vorhanden\nerrno=%d",
                         source_file, errno );

          }
          else if ( WithCopy )
          {
             int  syserr;
             status = MoveFile( mvbefehl, QuellVerz, "datacare.txt",
                                source_file, buf );
             if ( status != 0 )
             {
                strcpy( mvbefehl, "rmdir " );
                strcat( mvbefehl, source_file );
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
          sprintf( buf, "Erfolgreiche Uebernahme der Datacare-Daten nach\n%s",
                        source_file );
       }
       else
          sprintf( buf, "Folgendes Datacare-Verzeichnis wurde angelegt:\n%s",
                        source_file );
    }

    if ( WithCopy )
       free( mvbefehl );
    free( QuellVerz );
    free( source_file );

    return s;

}



/* ---------------------------------------------------------------------- *
 *                         wr_prot.c                                      *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Protokoll allgemein                                   *
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

#include <phodate.h>
#include <phozeit.h>

#if defined(MSDOS) || defined(WIN32)
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <errno.h>

/* --- Druck-output ------------------------------------- */

static FILE *fdDruck;

long OpenFile( char *datei, char *suffix, int mit_protokol, int expand,
               char *errmld )
{
   int  ok;
   int  i;
   int  ze_pos;
   int  lng;
   char teil;
   char *FileName;
   char *VerzName;
   char ze;

   char *Protokol = "protokol";

   /* ohne Protokoll */
   if ( !mit_protokol )
   {
     fdDruck = (FILE *)0;
     return 0;
   }

   /* datei:  Verzeichnis/datei */
   /* datei:  Verzeichnis/protokol/datei */
   /* dateiname extrahieren */
   i = strlen( datei ) - 1;
   while ( i >= 0 && datei[i] != '/' ) i--;
   i++;

   lng = strlen( &datei[i] ) + 5;
   FileName = malloc( lng );
   if ( FileName == NULL )
   {
      strcpy ( errmld, "Protokoll: Fehler beim Allokieren des Dateinamens" );
      return -1;
   }
   strcpy( FileName, &datei[i] );

   ze_pos = i;
   ze = datei[ze_pos];
   datei[ze_pos] = '\0';
   VerzName = malloc( strlen( datei ) + lng + 12 );
   if ( VerzName == NULL )
   {
      datei[ze_pos] = ze;
      strcpy ( errmld, "Protokoll: Fehler beim Allokieren des Verz.-Namens" );
      free ( FileName );
      return -1;
   }

   /* Verzeichnis "protokol" anlegen ( wenn noch nicht vorhanden */
   sprintf( VerzName, "%s%s", datei, Protokol );

#ifdef WIN32
   ok = _mkdir ( VerzName );
   if ( ok != 0 )
   {
     if ( errno == EACCES )
        ok = 0;
   }
#elif MSDOS
   ok = mkdir ( VerzName );
   if ( ok != 0 )
   {
     if ( errno == EACCES )
        ok = 0;
   }
#else
   ok = mkdir ( VerzName, S_IRWXU | S_IRWXG | S_IRWXO  );
#endif
   if ( ok != 0 )
   {
     if ( errno != EEXIST )
     {
       sprintf( errmld,
                "Verzeichnis\n%s\nkann nicht eingerichet werden\nerrno=%d",
                VerzName, errno );
       free ( FileName );
       free ( VerzName );
       return -1;
     }
   }

   /* .dat extrahieren */
   i = 0;
   while ( FileName[i] && FileName[i] != '.' ) i++;
   FileName[i] = '\0';

   if ( expand )
   {
      ok = 0;
      teil = 'z';
      while ( !ok && teil >= 'a' )
      {
         sprintf( VerzName, "%s%s/%s%c.%s",
                            datei, Protokol, FileName, teil, suffix );
         fdDruck = fopen( VerzName, "r" );
         if ( fdDruck == (FILE *)0 )
         {
           teil--;
         }
         else
         {
           fclose( fdDruck );
           ok = 1;
         }
      }

      teil++;

      if ( teil > 'z' )
      {
         datei[ze_pos] = ze;
         strcpy ( errmld, "Keine freie Nummer fuer Protokolldatei" );
         free ( FileName );
         free ( VerzName );
         return -1;
      }

      sprintf( VerzName, "%s%s/%s%c.%s",
                         datei, Protokol, FileName, teil, suffix );
   }
   else
      sprintf( VerzName, "%s%s/%s.%s", datei, Protokol, FileName, suffix );

   datei[ze_pos] = ze;

   fdDruck = fopen( VerzName, "w" );
   if ( fdDruck == (FILE *)0 )
   {
      sprintf( errmld,
               "Protokolldatei\n%s\nkann nicht geoeffnet werden",
               VerzName );
      free ( FileName );
      free ( VerzName );
      return -1;
   }
   free ( FileName );
   free ( VerzName );
   return 0;
}

long FlushFile( )
{
   if ( fdDruck == (FILE *)0 ) return 0;

   if ( fflush( fdDruck ) == 0 )
     return 0;
   else
     return -1;
}

void CloseFile( )
{
   if ( fdDruck != (FILE *)0 )
      fclose( fdDruck );
   fdDruck = (FILE *)0;
}

void WriteFile( char *buf, char *abschluss )
{
   if ( fdDruck != (FILE *)0 )
      fprintf( fdDruck, "%s%s", buf, abschluss );
}



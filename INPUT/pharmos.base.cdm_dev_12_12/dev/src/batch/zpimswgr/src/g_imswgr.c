
/* ---------------------------------------------------------------------- *
 *                            G _ I F A H E R . C                         *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die IFA-Herstellerdatei ein und integriert      *
 *                  die Saetze in den lokalen UPDATE-POOL                 *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 21.05.98                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

#include <wpp_dbas.h>

#include <artkatg.h>
#include "asciidat.h"

#ifndef MSDOS
#include <sys/types.h>
#include <sys/stat.h>
#endif

/* --- Prototype  ------------------------------------------------------- */

void CloseBase( void );
long OpenBase( char *db, char *errmld );
int  TestDateiname( char *file, long *ifadatum, char *errmld );

long Loesche_From_Artkatg( char *temp_name, char *errmld );
long Insert_From_Temp( char *temp_name, char *errmld );

/* --------  user -------------- */

static char *user = "IMS-ADG ";

/* --- Testversion ------------------------------------------------------ */
/*
#define TEST
*/

static char *temp_name = "hajo_ims_temp";

/* weil Struktur der TempTable nicht mehr ARTKATG entspricht */
static struct TEMPTABLE  {
       char    WARENGRUPPE  [6];
       char    BEZEICHNUNG  [31];
};

struct  TEMPTABLE  ims;

/* ---------------------------------------------------------------------- *
 * Funktion         : MV Befehl         generieren                        *
 * ---------------------------------------------------------------------- */

#ifndef MSDOS

static char *GenMvBefehl( char *datei, char *errmld )
{
    char *AltverzName;
    char *mvbefehl;
    char verz[50];
    int  lng;
    int  i;
    int  ind;
    char ze;
    int  status;
    struct stat buf;

    AltverzName = "altdaten";
    lng = strlen( datei );
    mvbefehl = malloc( 2*lng + strlen( AltverzName ) + 15 ) ;
    if ( mvbefehl == NULL )
    {
        sprintf( errmld, "malloc-Fehler beim Versuch,\n" \
                         "den Namen fuer %s zu allokieren", AltverzName );
        return NULL;
    }

    strcpy( mvbefehl, "mv -f " );
    strcat( mvbefehl, datei );
    strcat( mvbefehl, " " );
    strcat( mvbefehl, datei );

    i = strlen( mvbefehl ) - 1;
    while( i >= 0 && !(mvbefehl[i] == '/' || mvbefehl[i] == ' ') ) i--;
    ze = mvbefehl[i];
    mvbefehl[i] = '\0';
    ind = i;

    if ( ze == ' ' )
      strcpy( verz, "." );
    else
    {
      while ( i >= 0 && mvbefehl[i] != ' ' ) i--;
      i++;
      strcpy( verz, &mvbefehl[i] );
    }

    i = ind;
    mvbefehl[i] = ze;
    if ( ze == '/' || ze == ' ' ) i++;
    strcpy( &mvbefehl[i], AltverzName );
    i = strlen( mvbefehl ) - 1;
    while ( i >= 0 && mvbefehl[i] != ' ' ) i--;
    i++;

    status =  stat( &mvbefehl[i], &buf  );

    if ( status != 0 || ( buf.st_mode & S_IFMT) != S_IFDIR )
    {
      if ( strcmp( verz, "." ) == 0 )
         sprintf( errmld, "Das Unterverzeichnis %s\n"\
                          "im aktuellen Verzeichnis fehlt",
                           AltverzName  );
       else
          sprintf( errmld, "Das Unterverzeichnis %s\n"
                          "im Verzeichnis %s fehlt",
                           AltverzName, verz );

      free( mvbefehl );
      return NULL;
    }

    return mvbefehl;
}

#endif

/* ---------------------------------------------------------------------- *
 * Funktion         : I M S Einfuegen                                     *
 * ---------------------------------------------------------------------- */

static long CreateTemp( char *errmld )
{
   long s;
   char sql[320];
   sprintf( sql, "create temp table %s ("         \
                 "WARENGRUPPE CHAR(%d) NOT NULL," \
                 "BEZEICHNUNG CHAR(%d) NOT NULL) with no log" ,
                 temp_name,
                 L_ARTKATG_WARENGRUPPE,
                 L_ARTKATG_BEZEICHNUNG );
   s = SqlExecuteImm( sql );
   if ( s != 0 )
      strcpy( errmld, DynErrmld() );
   return s;
}

static long CreateTempIndex( char *errmld )
{
   long s;
   char sql[300];
   sprintf( sql, "create unique index I_%s on %s(WARENGRUPPE)",
                 temp_name,
                 temp_name );
   s = SqlExecuteImm( sql );
   if ( s != 0 )
      strcpy( errmld, DynErrmld() );
   return s;
}

static long PrepInsertTemp( int *fd, char *errmld )
{
   long s;
   s = SqlPrepareInsert ( fd, temp_name, "*" );
   if ( s != 0 )
     strcpy( errmld, DynErrmld() );
   return s;
}

static long ExecInsertTemp( int fd, struct TEMPTABLE *ims, char *errmld )
{
   long s;
   s = SqlExecutePrepare( fd, ims, NULL );
   if ( s != 0 )
   {
     strcpy( errmld, DynErrmld() );
     return s;
   }
   if ( SqlRowsProcessed() != 1 )
   {
     strcpy( errmld, "Keine Spalte eingefuegt" );
     return 1;
   }
   return 0;
}

static void fill_ims( char *zeile, struct TEMPTABLE *ims )
{
   int lng;
   memcpy( ims->WARENGRUPPE, zeile, 5 );
   ims->WARENGRUPPE[5] = '\0';
   zeile = &zeile[6];
   lng = strlen( zeile );
   if ( lng > L_ARTKATG_BEZEICHNUNG )
     lng = L_ARTKATG_BEZEICHNUNG;
   memset( ims->BEZEICHNUNG, ' ', L_ARTKATG_BEZEICHNUNG );
   memcpy( ims->BEZEICHNUNG, zeile, lng );
}

static int insert_imsdatei_into_temp( char *datei, int fd_IMS, char *errmld )
{
    int fd_temp;
    int status;
    long l_status;
    char zeile[200];
    char errtxt[80];

    status = AscRewind( fd_IMS );
    if ( status != RDA_OK )
    {
       sprintf( errmld, "Fehler %d beim Rewind der Datei\n%s", status, datei );
       AscClose( fd_IMS );
       return 1;
    }

    if ( CreateTemp( errtxt ) != 0 )
    {
       sprintf( errmld, "Fehler bei Create Temp\n%s", errtxt  );
       AscClose( fd_IMS );
       return 1;
    }

    if ( CreateTempIndex( errtxt ) != 0 )
    {
       sprintf( errmld, "Fehler bei Create Temp Index\n%s", errtxt  );
       AscClose( fd_IMS );
       return 1;
    }

    if ( PrepInsertTemp( &fd_temp, errmld ) != 0 )
    {
       sprintf( errmld, "Fehler bei Prepare Insert Temp\n%s", errtxt  );
       AscClose( fd_IMS );
       return 1;
    }

    l_status = 0;
    while ( status == RDA_OK && l_status == 0 )
    {
      status = AscRead( zeile, fd_IMS );
      if ( status == 0 )
      {
        if ( strlen( zeile ) > 0 )
        {
          fill_ims( zeile, &ims );
          l_status = ExecInsertTemp( fd_temp, &ims, errtxt );
          if ( l_status != 0 )
          {
            sprintf( errmld, "Fehler bei Insert Temp\n%s", errtxt  );
          }
/*
          else
            printf( "%s %s\n", ims.WARENGRUPPE, ims.BEZEICHNUNG );
*/
        }
      }
   }

   SqlFreePrepare( fd_temp );
   AscClose( fd_IMS );
   return 0;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : I M S T e s t e n                                   *
 * ---------------------------------------------------------------------- */

static int  TestZeile( char *zeile )
{
  int i;
  i = 0;
  while ( i < 5 && ( zeile[i] >= '0' || zeile[i] <= '9' ) ) i++;
  return  i == 5 && zeile[i] == ' ';
}

static long test_imsdatei( char *datei, int *fd, char *errmld )
{
    int  fd_IMS;                                     /* File-Descriptor */
    int  ok;
    int  lng;
    int  status;
    char zeile[200];

    status = AscOpenRd( datei, &fd_IMS, 1024, &AscNormFkt );

    if ( status != RDA_OK )
    {
       sprintf( errmld, "Fehler %d beim Oeffnen der Datei\n%s",
                        status, datei );
       return 1;
    }
    ok = 1;
    while ( status == RDA_OK && ok )
    {
      status = AscRead( zeile, fd_IMS );
      if ( status == 0 )
      {
         lng = strlen( zeile );
         if ( lng  > 0 )
         {
            ok = lng  >= 7;
            if ( ok )
              ok = TestZeile( zeile );
/*
            if ( ok ) printf( "%s\n", zeile );
*/
         }
      }
    }

    if ( !ok )
    {
       AscClose( fd_IMS );
       *fd = -1;
       sprintf( errmld, "Die Datei\n%s\nhat falsches Format",
                        datei );
       return 1;
    }
    *fd = fd_IMS;
    return 0;
}

long GenImsWgr( char *db, char *datei, char *errmld )
{
   long status;
   long mvstatus;
   int  fd_IMS;
#ifndef MSDOS
    char *mvbefehl;
#endif

   status = test_imsdatei( datei, &fd_IMS, errmld );
   if ( status != 0 ) return 1;

#ifndef MSDOS
    mvbefehl = GenMvBefehl( datei, errmld );
    if ( mvbefehl == NULL ) return 1;
#endif

    mvstatus = 0;

    status = OpenBase( db, errmld );
    if ( status == 0 )
    {
       status = OpenPflege( user, errmld );
       if ( status == 0 )
       {
          status = insert_imsdatei_into_temp( datei, fd_IMS, errmld );
          if ( status == 0 )
          {
            status = Loesche_From_Artkatg( temp_name, errmld );

            if ( status == 0 )
               status = Insert_From_Temp( temp_name, errmld );

          }
       }
       CloseBase( );
    }

#ifndef MSDOS
    if ( status == 0 )
    {

       if ( UnxHsystem ( mvbefehl ) != 0 )
       {
          mvstatus = 2;
          strcpy( errmld, DynErrmld() );
       }
    }
    free( mvbefehl );
#endif

    if ( status != 0 )
      return 1;
    if ( mvstatus != 0 )
      return mvstatus;

    status = 0;
    strcpy( errmld, "Laden der IMS-Datei erfolgreich" );

    return status;
}


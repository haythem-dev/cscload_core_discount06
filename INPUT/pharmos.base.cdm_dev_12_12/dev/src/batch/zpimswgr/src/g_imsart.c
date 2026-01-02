/* ---------------------------------------------------------------------- *
 *                            G _ I M S A R T . C                         *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die IMS-DAtei mit der Verknuepfung ARTIKEL-WGR  *
 *                  ein                                                   *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 25.09.99                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/*
#define TEST
*/

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

#include <wpp_dbas.h>

#include "asciidat.h"

#ifdef MIT_BSSICHG		/* 24.01.2003 */
#include "u_bssg.h"		/* 23.21.2002 BSSICHG */
#endif

#ifndef MSDOS
#include <sys/types.h>
#include <sys/stat.h>
#endif

/* --- Prototype  ------------------------------------------------------- */

void CloseBase( void );
long OpenBase( char *db, char *errmld );
int  TestDateiname( char *file, long *ifadatum, char *errmld );

long Loesche_From_Zartwg( char *temp_name, char *errmld,
                          long *anz_loe, long *anz_loe_9 );
long Insert_From_ImsTemp( char *temp_name, char *errmld,
                          long *anz_ins, long *anz_upd, 
						  long *anz_ins_9, long *anz_upd_9, long *anz_loe_9 );

/* --------  user -------------- */

static char *user = "IMS-KEY ";

/* --- Testversion ------------------------------------------------------ */
/*
#define TEST
*/

static char *temp_name = "hajo_iwg_temp";

struct  IMS_TEMP {
   long ARTIKEL_NR;
   long IMSWGR_NR;
   };

static struct IMS_TEMP ims;

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

/* ---------- Nur Saetze uebernehmen wenn Artikel in Zartikel -------- */

static long DeclReadZart( int *fd, char *errmld )
{
   long s;
   char *sql;
   sql = "select ARTIKEL_NR from ZARTIKEL where ARTIKEL_NR=?";
   s = SqlDeclareCsWh( fd, sql, "ZARTIKEL.ARTIKEL_NR", NULL  );
   if ( s != 0 )
      sprintf( errmld, "DeclReadZart: %s", DynErrmld() );
   return s;
}

static long ReadZart( int fd, long artikel_nr, char *errmld )
{
   long s;
   long art_nr;
   s = SqlReadDeclCs( fd, &art_nr, NULL, &artikel_nr, NULL );
   if ( s != 0 )
      sprintf( errmld, "ReadTemp: %s", DynErrmld() );
   return s;
}


static long CreateTemp( char *errmld )
{
   long s;
   char sql[320];
   sprintf( sql, "create temp table %s ("         \
                 "ARTIKEL_NR INTEGER NOT NULL," \
                 "IMSWGR_NR INTEGER NOT NULL) with no log" ,
                 temp_name );
   s = SqlExecuteImm( sql );
   if ( s != 0 )
      strcpy( errmld, DynErrmld() );
   return s;
}

static long CreateTempIndex( char *errmld )
{
   long s;
   char sql[300];
   sprintf( sql, "create unique index I_%s on %s(ARTIKEL_NR)",
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

static long ExecInsertTemp( int fd, struct IMS_TEMP *ims, char *errmld )
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

/* ------------------------------------------------------------------- */
long sel_ArtNoByCode	( const long code )
{
    long artNo;
	char sql[150];

	sprintf( sql, "SELECT articleno FROM carticlecodes WHERE article_code ='%ld' "
					"AND code_type IN (SELECT code_type FROM ccodetypes WHERE artnr_substitute = 1)", code);
  
	if ( SqlRead( sql, &artNo, NULL ) != 0 )
	{
		artNo = -1;
	}

	return artNo;
}

static void fill_ims( char *zeile, struct IMS_TEMP *ims )
{
   char str[15];
   memcpy( str, zeile, 12 );   /* ARTIKEL_NR */ 
   str[12] = '\0';
   zeile = &zeile[12];
   ims->ARTIKEL_NR = sel_ArtNoByCode( atol(str) );
   memcpy( str, zeile, 5 );   /* IMSWGR_NR */
   str[5] = '\0';
   ims->IMSWGR_NR = atol( str );
}

static int insert_imsdatei_into_temp( char *datei, int fd_IMS, char *errmld )
{
    int fd_temp;
    int fd_zart;
    int status;
    long l_status;
    long s;
    char zeile[200];
    char errtxt[80];

    status = AscRewind( fd_IMS );
    if ( status != RDA_OK )
    {
       sprintf( errmld, "Fehler %d beim Rewind der Datei\n%s", status, datei );
       AscClose( fd_IMS );
       return 1;
    }

    /* 1. Zeile ueberlesen */
    status = AscRead( zeile, fd_IMS );
    if ( status != RDA_OK )
    {
       sprintf( errmld, "Fehler %d beim Ueberlesen des 1. Satzes der Datei\n%s", status, datei );
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
    if ( DeclReadZart( &fd_zart, errmld ) != 0 )
    {
       sprintf( errmld, "Fehler bei Declare Read ZARTIKEL\n%s", errtxt  );
       SqlFreePrepare( fd_temp );
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
          s = ReadZart( fd_zart, ims.ARTIKEL_NR, errtxt );
          if ( s == 0 )
          {
             l_status = ExecInsertTemp( fd_temp, &ims, errtxt );
             if ( l_status != 0 )
             {
               sprintf( errmld, "Fehler bei Insert Temp\n%s", errtxt  );
             }
             else
             {
#ifdef TEST
               printf( "%.7ld %.5ld\n", ims->ARTIKEL_NR, ims->IMSWGR_NR );
#endif
             }
          }
          else if ( s != 100 )
          {
             l_status = s;
             sprintf( errmld, "Fehler bei Read Zartikel\n%s", errtxt  );
          }
        }
      }
    }

    SqlCloseCs( fd_zart );
    SqlFreePrepare( fd_temp );
    AscClose( fd_IMS );
    if ( l_status == 0 )
       return 0;
    else
       return 1;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : I M S T e s t e n                                   *
 * ---------------------------------------------------------------------- */

static int  TestZeile( char *zeile )
{
  int i;
  i = 0;
  while ( i < 17 && ( zeile[i] >= '0' || zeile[i] <= '9' ) ) i++;
  return  i == 17;
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


    /* 1. Zeile lesen */
    /* Format-Beispiel */
    /* GWF0799D */
    status = AscRead( zeile, fd_IMS );


    /* restliche Zeilen */
    /* Format-Beispiel */
    /* 000000119824150144MM25MZG  */

    if ( status == RDA_OK )
    {
       lng = strlen( zeile );
       ok = lng == 8;
       if ( ok )
         ok = memcmp( zeile, "GWF", 3 ) == 0;
    }
    else
       ok = 0;   /* wegen Fehlermeldung */

    while ( status == RDA_OK && ok )
    {
      status = AscRead( zeile, fd_IMS );
      if ( status == 0 )
      {
         lng = strlen( zeile );
         if ( lng  > 0 )
         {
            ok = lng  == 25;
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

long GenImsArt( char *db, char *datei, char *errmld )
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

#ifdef MIT_BSSICHG		/* 24.01.2003 */
	   /* 23.21.2002 BSSICHG */
   	   if ( status == 0 )
		  status = OpenBSSichG( user, errmld );
	   /* */
#endif

       if ( status == 0 )
       {
          status = insert_imsdatei_into_temp( datei, fd_IMS, errmld );
          if ( status == 0 )
          {
            long anz_loe;
            long anz_loe_9;
            long anz_ins;
            long anz_ins_9;
            long anz_upd;
            long anz_upd_9;
            anz_loe = 0;
            anz_loe_9 = 0;
            anz_ins = 0;
            anz_ins_9 = 0;
            anz_upd = 0;
            anz_upd_9 = 0;

			status = Loesche_From_Zartwg( temp_name, errmld,
                                          &anz_loe, &anz_loe_9 );

            if ( status == 0 )
               status = Insert_From_ImsTemp( temp_name, errmld,
                                             &anz_ins, &anz_upd, 
											 &anz_ins_9, &anz_upd_9, &anz_loe_9 );
            if ( status == 0 )
            {
               sprintf( errmld,
                        "Laden der IMS-Datei Artikel<->Wgr erfolgreich\n" \
                        "geloescht : %ld\neingefuegt: %ld\ngeaendert : %ld\n" \
						"Art 9 gel.: %ld\nArt 9 ein.: %ld\nArt 9 gea.: %ld",
                        anz_loe, anz_ins, anz_upd, anz_loe_9, anz_ins_9, anz_upd_9 );
            }
          }
       }
#ifdef MIT_BSSICHG		/* 24.01.2003 */
	   CloseBSSichG(); /* 23.21.2002 BSSICHG */
#endif
       CloseBase( );
    }

#ifndef MSDOS
    if ( status == 0 )
    {

       if ( UnxHsystem ( mvbefehl ) != 0 )
       {
          mvstatus = 2;
          strcat( errmld, "\n\n" );
          strcat( errmld, DynErrmld() );
       }
    }
    free( mvbefehl );
#endif

    if ( status != 0 )
      return 1;
    if ( mvstatus != 0 )
      return mvstatus;

    status = 0;
/*
    strcpy( errmld, "Laden der IMS-Datei Artikel<->Wgr erfolgreich" );
*/
    return status;
}


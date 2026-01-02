/* --- includes --------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <hdatum/phodate.h>
#include <hdatum/phozeit.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include "art_prot.h"

#include "wr_prot.h"

#include "znb_gen_li.h"

#include <voodoo_table_header/ean.h>		/* wegen UNIX und EAN benutzt in zart_gen.h */
#include "zart_gen.h"

/* --- page length / number ------------------- */

#define MAX_ZEILE 60

static long zeile = MAX_ZEILE;
static long seite = 1;

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( const char* const db, char *errmld );

/* ----------------- Usage ------------------------ */

void Cliart_Protokol_Usage ( char *spBuf, char *prog )
{
   strcat( spBuf, "- " );
   strcat( spBuf, prog );
   strcat( spBuf, " 3 database logindexdatum [Verzeichnis] \n" \
                "  LI-Artikel Protokoll\n" );
}

/* --- page header ------------------------------ */

static char u0[200];

static void GenU0( long linr, int mode  )
{
   char *str;
   char nr[20];
   sprintf( nr, "%ld", linr );
   nr[9] = '\0';
   if ( mode == 0 )
      str = "ALLE SAETZE";
   else
      str = "NEUZUGAENGE";
   sprintf( u0, "ZPLIARTIK: PROTOKOLL LOGINDEX-AENDERUNGSDIENST LI-DATEI LF%s :: %s",
                &nr[2],
                str );
}

static char* z0 =
   "HNR   GUE-DAT  PZN     EINH-LI   ARTIKELBEZEICHNUNG-LI          " \
   "DFO     GEP-LI      AVP-LI  HE-CO";

static char* z1 =
   "                       EINH-AS   ARTIKELBEZEICHNUNG-AS          " \
   "        GEP-AS      AVP-AS	";

static char strich[200];

/* --------------------------------------------------------- */

static void WriteZeile( char *spBuf )
{
   WriteFile( spBuf, "\n" );
   zeile++;
}

static void WriteLeerZeile( )
{
   WriteFile( "", "\n" );
   zeile++;
}

static void GenStrichZeile( )
{
   size_t anz;
   anz = strlen( z0 );
   memset( strich, '-', anz );
   strich[anz] = '\0';
}

static void WriteStrichZeile( )
{
   WriteFile( strich, "\n" );
   zeile++;
}

static void WriteVorschub()
{
   WriteFile( "", "\f" );
/* zeile = 0; */
}

/* --- members ------------------------------------- */


static void set_leer( char *leer, int anz )
{
    memset( leer, ' ', anz );
	leer[anz] = '\0';
}


static void art_Kopf_0( char *spBuf )
{

   char dat_str[20];
   long zeit;
   ConvFromPhoDate( dat_str, GetPhoDate(), "tt.mm.jjjj" );
   zeit = GetPhoTime( );

   sprintf( spBuf,
            "%s    DATUM: %s  UHRZEIT: %.2ld:%.2ld:%.2ld  SEITE: %ld",
            u0,
            dat_str,
            zeit/10000,
            (zeit/100)%100,
            zeit%100,
            seite++ );
}

static void art_Kopf_1( char *spBuf )
{
   sprintf( spBuf, "%s", z0 );
}
static void art_Kopf_2( char *spBuf )
{
   sprintf( spBuf, "%s", z1 );
}

static int art_Kopf( char *spBuf )
{
   if ( zeile >= MAX_ZEILE )
   {
      if ( seite > 1 )
         WriteVorschub( );
      zeile = 0;
      art_Kopf_0( spBuf );
      WriteZeile( spBuf );
      WriteLeerZeile( );
      art_Kopf_1( spBuf );
      WriteZeile( spBuf );
      art_Kopf_2( spBuf );
      WriteZeile( spBuf );
      return 1;
   }
   return 0;
}


static void art_Zeile_1( struct CLIART_PROT *cli, char *spBuf )
{
   char ArtEinheit[20];
   char datum[11];
   long l;

   l = cli->VDAT;
   sprintf( datum, "%2.2ld.%2.2ld.%2.2ld",
                   l%100, (l/100)%100, (l/10000)%100 );
   Build_EINHEIT( ArtEinheit, cli->QTYUD, cli->QTY, cli->NOPCS );

   sprintf( spBuf,
            "%.5ld %s %.7ld %s %s   %s %11.2f %11.2f %ld",
            cli->HERSTELLER_NR,
            datum,
            cli->PHAR,
			ArtEinheit,
			cli->DSCRD,
			cli->PCKTYPD,
			cli->PRICE_PEXF,
			cli->PRICE_PPUB,
			cli->COMPNO
           );
}

static void art_Zeile_2( struct ZARTIKEL_PROT  *zart, long s_zart,
                         struct ZARTPREIS_PROT *zpre, long s_zpre,
                         char *spBuf )
{
   if ( s_zart != 0 )
   {
      set_leer( zart->EINHEIT,      L_ZARTIKEL_EINHEIT );
      set_leer( zart->ARTIKEL_NAME, L_ZARTIKEL_ARTIKEL_NAME );
      set_leer( zart->DARREICHFORM, L_ZARTIKEL_DARREICHFORM );
   }

   if ( s_zpre == 0 )
   {
     sprintf( spBuf,
              "                       %s %s %s %11.2f %11.2f ",
              zart->EINHEIT,
              zart->ARTIKEL_NAME,
              zart->DARREICHFORM,
              zpre->GROSSO,
              zpre->AVP
             );
   }
   else
   {
     sprintf( spBuf,
              "                       %s %s %s",
              zart->EINHEIT,
              zart->ARTIKEL_NAME,
              zart->DARREICHFORM );
   }
}


static void art_Zeile(  struct CLIART_PROT   *cli,
                        struct ZARTIKEL_PROT  *zart, long s_zart,
                        struct ZARTPREIS_PROT *zpre, long s_zpre,
                        char *spBuf )
{
   art_Zeile_1( cli, spBuf  );
   WriteZeile( spBuf );
/* Neuaufnahmen gegebenfalls 2. Zeile drucken */
   if ( s_zart == 0 )
   {
      art_Zeile_2( zart, s_zart, zpre, s_zpre, spBuf  );
      WriteZeile( spBuf );
   }
}

/* --- Schnittstelle ------------------------------------ */

static long art_OpenProtokol( long nr, char *verzeichnis, int mode,
                              char *errmld )
{
   char *datei;
   long s;
   size_t  lng;

   zeile = MAX_ZEILE;
   seite = 1;

   GenU0( nr, mode );
   GenStrichZeile( );

   /* nr in der Form jjjjmmtt: 19421128 */
   if ( verzeichnis != NULL )
      lng = strlen( verzeichnis );
   else
      lng = 0;

   datei = malloc( lng + 12 );
   if ( datei == NULL )
   {
      strcpy( errmld, "malloc-Fehler bei art_OpenProtokol" );
      return -1;
   }
   if ( lng > 0  )
      sprintf( datei, "%s/p%.6ld", verzeichnis, nr%1000000 );
   else
      sprintf( datei, "p%.6ld", nr%1000000 );
   s = OpenFile( datei, "li", 1, 1, errmld );

   free( datei );
   return s;
}

static void art_CloseProtokol( int ok, long anz_gelesen, char *errmld )
{
   WriteLeerZeile( );       /* neu wegen Strichzeile */
   if ( !ok )
   {
     char buf[50];
     WriteLeerZeile( );
     WriteZeile( errmld );
     sprintf( buf, "%ld Saetze wuren gelesen", anz_gelesen );
     WriteZeile( buf );
   }

   CloseFile( );
}

static long art_Protokol( struct CLIART_PROT   *cli,
                          struct ZARTIKEL_PROT  *zart,  long s_zart,
                          struct ZARTPREIS_PROT *zpre,  long s_zpre,
                          char *errmld )
{
   static long herst_num = -4711;
   char buf[400];
   int  mode;

   mode = art_Kopf( buf );

   if ( cli->HERSTELLER_NR != herst_num ) 
   {
      herst_num = cli->HERSTELLER_NR;
      if ( mode == 0 )
         WriteStrichZeile( );
      else
         WriteLeerZeile( );     /* bei Seitenwechsel keine Strichzeile */
   }
   else
      WriteLeerZeile( );

   art_Zeile( cli, zart, s_zart, zpre, s_zpre, buf );


   if ( FlushFile() != 0 )
   {
      strcpy( errmld, "Fehler beim Schreiben in die Protokolldatei" );
      return -1;
   }
   return 0;
}

/* -------------------------------------------------------------- */

static long DeclareZartikel( int *fd, char *proj, char *errmld )
{
    char sql[500];
    long status;

    sprintf( sql, "select %s from ZARTIKEL where ARTIKEL_NR=?", proj );
    status = SqlDeclareCs( fd, sql, "ZARTIKEL.ARTIKEL_NR", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "zartikel: " );
      strcat( errmld, DynErrmld() );
      *fd = -1;
    }
    return status;
}

static long ReadZartikel( int fd, long artikel_nr, struct ZARTIKEL_PROT *zart,
                          char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd, zart, NULL, &artikel_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      strcpy( errmld, "zartikel: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}


#ifdef VOR_EURO

static long DeclareZpreis( int *fd, char *proj, long tagesdatum, char *errmld )
{
   char sql[500];
   long status;

   sprintf( sql, "select %s from ZARTPREIS where ARTIKEL_NR=? " \
                 "and DATUMGUELTIGAB=" \
                 "(select max(DATUMGUELTIGAB) from ZARTPREIS where " \
                 "DATUMGUELTIGAB<=%ld " \
                 "and ARTIKEL_NR=?)",
                 proj,
                 tagesdatum );

   status = SqlDeclareCs( fd, sql,
                          "ZARTPREIS.ARTIKEL_NR",
                          "ZARTPREIS.ARTIKEL_NR", NULL );

   if ( status != 0 )
   {
      strcpy( errmld, "zartpreis: " );
      strcat( errmld, DynErrmld() );
      *fd = -1;
   }
   return status;
}

static long ReadZpreis( int fd, long artikel_nr, struct ZARTPREIS_PROT *zpre,
                        char *errmld )
{
   long status;
   status = SqlReadDeclCs( fd, zpre, NULL,
                               &artikel_nr, &artikel_nr, NULL );
   if ( !( status == 0 || status == 100 ))
   {
     strcpy( errmld, "zartpreis: " );
     strcat( errmld, DynErrmld() );
   }
   return status;
}

#else

static long DeclareZpreis( int *fd, char *proj, long tagesdatum, char *errmld )
{
   char sql[500];
   long status;

   sprintf( sql, "select %s from ZARTPREIS where ARTIKEL_NR=? " \
                 "and DATUMGUELTIGAB=" \
                 "(select max(DATUMGUELTIGAB) from ZARTPREIS where " \
                 "DATUMGUELTIGAB<=%ld " \
                 "and ARTIKEL_NR=?)",
                 proj,
                 tagesdatum );

   status = SqlDeclareCs( fd, sql,
                          "ZARTPREIS.ARTIKEL_NR",
                          "ZARTPREIS.ARTIKEL_NR", NULL );

   if ( status != 0 )
   {
      strcpy( errmld, "zartpreis: " );
      strcat( errmld, DynErrmld() );
      *fd = -1;
   }
   return status;
}

static long ReadZpreis( int fd, long artikel_nr,
					    struct ZARTPREIS_PROT *zpre, char *errmld )
{
   long status;
   status = SqlReadDeclCs( fd, zpre, NULL,
                               &artikel_nr, &artikel_nr, NULL );
   if ( !( status == 0 || status == 100 ))
   {
     strcpy( errmld, "zartpreis: " );
     strcat( errmld, DynErrmld() );
   }
   return status;
}

#endif

static long OpenCliart( int *fd, char *proj, long linr, char *errmld )
{
   char sql[500];
   long status;
   sprintf( sql, "select %s from CLIART where LINR=%ld order by "  \
                 "LINR,HERSTELLER_NR,DSCRD",
                  proj,
                  linr );
   status = SqlOpenCs( fd, sql );
   if ( status != 0 )
   {
      strcpy( errmld, "cliart: " );
      strcat( errmld, DynErrmld() );
      *fd = -1;
   }
   return status;
}

static long ReadCliart( int fd, struct CLIART_PROT *cli, char *errmld )
{
   long status;
   status = SqlFetch( fd, 1, cli, NULL );
   if ( status == 100 )
   {
     strcpy( errmld, "cliart: Kein Satz vorhanden" );
   }
   else if ( status != 0 )
   {
     strcpy( errmld, "cliart: " );
     strcat( errmld, DynErrmld() );
   }
   return status;
}

/* -------------------------------------------------------------- */

static long Do_All( long linr, char *verzeichnis, int mode, char *errmld )
{
   long s;
   long s1;
   long s2;
   int fd_cli;
   int fd_zpre;
   int fd_zart;

   long anz_gelesen;
   long artikel_nr;

   struct CLIART_PROT   cli;
   struct ZARTIKEL_PROT  zart;
   struct ZARTPREIS_PROT zpre;

   if ( DeclareZartikel( &fd_zart, ZARTIKEL_PROT_PROJ, errmld ) != 0 )
      return -1;
   if ( DeclareZpreis( &fd_zpre, ZARTPREIS_PROT_PROJ, GetPhoDate(),
                       errmld ) != 0 )
      return -1;

   s = OpenCliart( &fd_cli, CLIART_PROT_PROJ, linr, errmld );
   if ( s == 0 )
   {
      s = ReadCliart( fd_cli, &cli, errmld );
      if ( s == 0 )
      {
         s = art_OpenProtokol( linr, verzeichnis, mode, errmld );
         if ( s == 0 )
         {
            anz_gelesen = 0;
            do
            {
               artikel_nr = cli.PHAR;
               s1 = ReadZartikel( fd_zart, artikel_nr, &zart, errmld );
               if ( mode == 0 )
               {
                  anz_gelesen++;
				  s2 = ReadZpreis  ( fd_zpre, artikel_nr, &zpre, errmld );
                  s = art_Protokol ( &cli, &zart, s1, &zpre, s2, errmld );
               }
               else
               {
                  s2 = 100;
                  if ( s1 != 0 )
                  {
                     anz_gelesen++;
                     s = art_Protokol ( &cli, &zart, s1, &zpre, s2, errmld );
                  }
               }

               if ( s1 == 100 ) s1 = 0;
               if ( s2 == 100 ) s2 = 0;
               if ( s == 0 && s1 == 0 && s2 == 0 )
                  s = ReadCliart( fd_cli, &cli, errmld );
            }  while ( s == 0 && s1 == 0 && s2 == 0 );
            art_CloseProtokol( s == 100, anz_gelesen, errmld );
            if ( s == 100 )
            {
               sprintf( errmld, "%ld Saetze", anz_gelesen );
               s = 0;
            }
         }
      }
   }

   SqlCloseCs( fd_cli );
   SqlCloseCs( fd_zpre );
   SqlCloseCs( fd_zart );

   return s;
}

long Cliart_Protokol_Loop( char *db, char *c_lidatum, char *verzeichnis, char *spBuf )
{
   long s;
   long linr;
   char meld[300];
   linr = atol( c_lidatum );
   s = OpenBase( db, spBuf );
   if ( s == 0 )
   {
     s = Do_All( linr, verzeichnis, 0, spBuf );
     strcpy( meld, "Protokoll alle Saetze: ");
     strcat( meld, spBuf );
     if ( s == 0 )
     {
         s = Do_All( linr, verzeichnis, 1, spBuf );
         strcat( meld, "\nProtokoll Neuzugaenge: ");
         strcat( meld, spBuf );
     }
     strcpy( spBuf, meld );
     CloseBase( );
   }
   return s;
}



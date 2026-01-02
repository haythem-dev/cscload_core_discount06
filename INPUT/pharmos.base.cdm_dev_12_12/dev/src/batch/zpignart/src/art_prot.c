
/* ---------------------------------------------------------------------- *
 *                       A R T _ P R O T . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Protokoll Artikel                                            *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  23.08.2000                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- includes --------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <phodate.h>
#include <phozeit.h>
#include <libscsvoodoo.h>

#include "art_prot.h"

#include "wr_prot.h"

#include "znb_gen.h"

#include <ean.h>		/* wegen UNIX und EAN benutzt in zart_gen.h */
#include "zart_gen.h"

/* --- page length / number ------------------- */

#define MAX_ZEILE 60

static long zeile = MAX_ZEILE;
static long seite = 1;

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void Zifaart_Protokol_Usage ( char *buf, char *prog )
{
   strcat( buf, "- " );
   strcat( buf, prog );
   strcat( buf, " 3 database Ifadatum [Verzeichnis] \n" \
                "  IFA-Artikel Protokoll\n" );
}

/* --- page header ------------------------------ */

static char u0[200];

static void GenU0( long ifanr, int mode  )
{
   char *str;
   char nr[20];
   sprintf( nr, "%ld", ifanr );
   nr[9] = '\0';
   if ( mode == 0 )
      str = "ALLE SAETZE";
   else
      str = "NEUZUGAENGE";
   sprintf( u0, "ZPIGNART: PROTOKOLL IFA-AENDERUNGSDIENST IFA-DATEI LF%s :: %s",
                &nr[2],
                str );
}

static char* z0 =
   "HNR   GUE-DAT  PZN      EINH-IFA  ARTIKELBEZEICHNUNG-IFA         " \
   "DFO     GEP-IFA     AEP-IFA     AVP-PFA PZNNFIFA  MW TX AM NE TMAX";

static char* z1 =
   "                SPANNE% EINH-AS   ARTIKELBEZEICHNUNG-AS          " \
   "        GEP-AS      AEP-AS      AVP-AS  ARTNRIFA          BTM VWGH";

static char leer1[200];
static char leer2[200];
static char strich[200];

/* --------------------------------------------------------- */

static void WriteZeile( char *buf )
{
   WriteFile( buf, "\n" );
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


static void art_Kopf_0( char *buf )
{

   char dat_str[20];
   long zeit;
   ConvFromPhoDate( dat_str, GetPhoDate(), "tt.mm.jjjj" );
   zeit = GetPhoTime( );

   sprintf( buf,
            "%s    DATUM: %s  UHRZEIT: %.2ld:%.2ld:%.2ld  SEITE: %ld",
            u0,
            dat_str,
            zeit/10000,
            (zeit/100)%100,
            zeit%100,
            seite++ );
}

static void art_Kopf_1( char *buf )
{
   sprintf( buf, "%s", z0 );
}
static void art_Kopf_2( char *buf )
{
   sprintf( buf, "%s", z1 );
}

static int art_Kopf( char *buf )
{
   if ( zeile >= MAX_ZEILE )
   {
      if ( seite > 1 )
         WriteVorschub( );
      zeile = 0;
      art_Kopf_0( buf );
      WriteZeile( buf );
      WriteLeerZeile( );
      art_Kopf_1( buf );
      WriteZeile( buf );
      art_Kopf_2( buf );
      WriteZeile( buf );
/*
      WriteLeerZeile( );
*/
      return 1;
   }
   return 0;
}


static void art_Zeile_1( struct ZIFAART_PROT *zifa, char *buf )
{
   char ArtEinheit[20];
   char datum[11];
   long l;

   l = zifa->DATUMGUELTIGAB;
   sprintf( datum, "%2.2ld.%2.2ld.%2.2ld",
                   l%100, (l/100)%100, (l/10000)%100 );
   Build_EINHEIT( ArtEinheit, zifa->A00PGEINH, zifa->A00PGMENG );

   sprintf( buf,
            "%.5ld %s %.8ld %s %s     %s %11.2f %11.2f %11.2f %.8ld  %s %s %s %s %s",
            zifa->A00ANBNR,
            datum,
            zifa->A00PZN8,
			ArtEinheit,
            zifa->A00PBEZ,
            zifa->A00DARFO,
            zifa->A01GEPDM,
            zifa->A01AEPDM,
            zifa->A01AVPDM,
            zifa->A06PZNNF8,
            zifa->A01MWST,
            zifa->A01AMPV,
            zifa->A02AM,
            zifa->A02NEM,
            zifa->A05TMAX
           );
}

static void art_Zeile_2( struct ZIFAART_PROT   *zifa,
                         struct ZARTIKEL_PROT  *zart, long s_zart,
                         struct ZARTPREIS_PROT *zpre, long s_zpre,
                         char *buf )
{
   double spanne = 0.0;

   if (zifa->A01AEPDM > 0.00)
		spanne = (zifa->A01AEPDM - zifa->A01GEPDM ) / zifa->A01AEPDM * 100;

   if ( s_zart != 0 )
   {
      set_leer( zart->EINHEIT,      L_ZARTIKEL_EINHEIT );
      set_leer( zart->ARTIKEL_NAME, L_ZARTIKEL_ARTIKEL_NAME );
      set_leer( zart->DARREICHFORM, L_ZARTIKEL_DARREICHFORM );
   }

   set_leer( leer1, 15 );
   if ( zifa->NB_PLAUSI[PL_A00ANBNR] != NOVALUE_PL )
      memset( &leer1[0], '*', 3 );		/* Sterne, wenn A00ANBNR von IFA mitgeliefert */

   if ( s_zpre == 0 )
   {
     sprintf( buf,
              "%s %5.1f   %s %s %s %11.2f %11.2f %11.2f %s %s %s",
              leer1,
			  spanne,
              zart->EINHEIT,
              zart->ARTIKEL_NAME,
              zart->DARREICHFORM,
              zpre->GROSSO,
              zpre->AEP,
              zpre->AVP,
              zifa->A00ARTNR,
              zifa->A02BTM,
              zifa->A03VWGGH
             );
   }
   else
   {
     set_leer( leer2, 11 );
     sprintf( buf,
              "%s %5.1f   %s %s %s %s %s %s %s %s %s",
              leer1,
			  spanne,
              zart->EINHEIT,
              zart->ARTIKEL_NAME,
              zart->DARREICHFORM,
              leer2,
              leer2,
              leer2,
              zifa->A00ARTNR,
              zifa->A02BTM,
              zifa->A03VWGGH
             );
   }
}


static void art_Zeile(  struct ZIFAART_PROT   *zifa,
                        struct ZARTIKEL_PROT  *zart, long s_zart,
                        struct ZARTPREIS_PROT *zpre, long s_zpre,
                        char *buf )
{
   art_Zeile_1( zifa, buf  );
   WriteZeile( buf );
/* Neuaufnahmen ebenfalls 2. Zeile drucken */
/* if ( s_zart == 0 ) */
   {
      art_Zeile_2( zifa, zart, s_zart, zpre, s_zpre, buf  );
      WriteZeile( buf );
   }
}

/* --- Schnittstelle ------------------------------------ */

static long art_OpenProtokol( long nr, char *verzeichnis, int mode,
                              char *errmld )
{
   char *datei;
   long s;
   size_t lng;

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
   s = OpenFile( datei, "ifa", 1, 1, errmld );

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

static long art_Protokol( struct ZIFAART_PROT   *zifa,
                          struct ZARTIKEL_PROT  *zart,  long s_zart,
                          struct ZARTPREIS_PROT *zpre,  long s_zpre,
                          char *errmld )
{
   static long herst_num = -4711;
   char buf[400];
   memset(buf, 0, 400);
   int  mode;

   mode = art_Kopf( buf );

   if ( zifa->A00ANBNR != herst_num ) 
   {
      herst_num = zifa->A00ANBNR;
      if ( mode == 0 )
         WriteStrichZeile( );
      else
         WriteLeerZeile( );     /* bei Seitenwechsel keine Strichzeile */
   }
   else
      WriteLeerZeile( );

   art_Zeile( zifa, zart, s_zart, zpre, s_zpre, buf );


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

static long DeclareZpreis( int *fd, char *proj, long tagesdatum, char *errmld )
{
   char sql[500];
   long status;

   sprintf( sql, "select %s from ZARTPREIS where ARTIKEL_NR=? " \
                 "and DATUMGUELTIGAB=" \
                 "(select max(DATUMGUELTIGAB) from ZARTPREIS where " \
                 "DATUMGUELTIGAB<=? " \
                 "and ARTIKEL_NR=?)",
       proj);

   status = SqlDeclareCs( fd, sql,
                          "ZARTPREIS.ARTIKEL_NR",
                          "ZARTPREIS.DATUMGUELTIGAB",
                          "ZARTPREIS.ARTIKEL_NR", NULL );

   if ( status != 0 )
   {
      strcpy( errmld, "zartpreis: " );
      strcat( errmld, DynErrmld() );
      *fd = -1;
   }
   return status;
}

static long ReadZpreis( int fd, long artikel_nr, long datumgueltigab, 
					    struct ZARTPREIS_PROT *zpre, char *errmld )
{
   long status;
   status = SqlReadDeclCs( fd, zpre, NULL,
                               &artikel_nr, &datumgueltigab, &artikel_nr, NULL );
   if ( !( status == 0 || status == 100 ))
   {
     strcpy( errmld, "zartpreis: " );
     strcat( errmld, DynErrmld() );
   }
   return status;
}

static long OpenZifaart( int *fd, char *proj, long ifanr, char *errmld )
{
   char sql[500];
   long status;
   sprintf( sql, "select %s from ZIFAART where IFANR=%ld order by "  \
                 "IFANR,A00ANBNR,A00PZN",
                  proj,
                  ifanr );
   status = SqlOpenCs( fd, sql );
   if ( status != 0 )
   {
      strcpy( errmld, "zifaart: " );
      strcat( errmld, DynErrmld() );
      *fd = -1;
   }
   return status;
}

static long ReadZifaart( int fd, struct ZIFAART_PROT *zifa, char *errmld )
{
   long status;
   status = SqlFetch( fd, 1, zifa, NULL );
   if ( status == 100 )
   {
     strcpy( errmld, "zifaart: Kein Satz vorhanden" );
   }
   else if ( status != 0 )
   {
     strcpy( errmld, "zifaart: " );
     strcat( errmld, DynErrmld() );
   }
   return status;
}

/* -------------------------------------------------------------- */

static long Do_All( long ifanr, char *verzeichnis, int mode, char *errmld )
{
   long s;
   long s1;
   long s2;
   int fd_zifa;
   int fd_zpre;
   int fd_zart;

   long anz_gelesen;
   long artikel_nr;

   struct ZIFAART_PROT   zifa;
   struct ZARTIKEL_PROT  zart;
   struct ZARTPREIS_PROT zpre;

   if ( DeclareZartikel( &fd_zart, ZARTIKEL_PROT_PROJ, errmld ) != 0 )
      return -1;
   if ( DeclareZpreis( &fd_zpre, ZARTPREIS_PROT_PROJ, GetPhoDate(),
                       errmld ) != 0 )
      return -1;

   s = OpenZifaart( &fd_zifa, ZIFAART_PROT_PROJ, ifanr, errmld );
   if ( s == 0 )
   {
      s = ReadZifaart( fd_zifa, &zifa, errmld );
      if ( s == 0 )
      {
         s = art_OpenProtokol( ifanr, verzeichnis, mode, errmld );
         if ( s == 0 )
         {
            anz_gelesen = 0;
            do
            {
               artikel_nr = zifa.A00PZN;
               s1 = ReadZartikel( fd_zart, artikel_nr, &zart, errmld );
               if ( mode == 0 )
               {
                  anz_gelesen++;
                  s2 = ReadZpreis  ( fd_zpre, artikel_nr, zifa.DATUMGUELTIGAB, &zpre, errmld );
                  s = art_Protokol ( &zifa, &zart, s1, &zpre, s2, errmld );
               }
               else
               {
                  s2 = 100;
                  if ( s1 != 0 )
                  {
                     anz_gelesen++;
                     s = art_Protokol ( &zifa, &zart, s1, &zpre, s2, errmld );
                  }
               }

               if ( s1 == 100 ) s1 = 0;
               if ( s2 == 100 ) s2 = 0;
               if ( s == 0 && s1 == 0 && s2 == 0 )
                  s = ReadZifaart( fd_zifa, &zifa, errmld );
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

   SqlCloseCs( fd_zifa );
   SqlCloseCs( fd_zpre );
   SqlCloseCs( fd_zart );

   return s;
}

long Zifaart_Protokol_Loop( char *db, char *c_ifadatum, char *verzeichnis, char *buf )
{
   long s;
   long ifanr;
   char meld[300];
   ifanr = atol( c_ifadatum );
   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = Do_All( ifanr, verzeichnis, 0, buf );
     strcpy( meld, "Protokoll alle Saetze: ");
     strcat( meld, buf );
     if ( s == 0 )
     {
         s = Do_All( ifanr, verzeichnis, 1, buf );
         strcat( meld, "\nProtokoll Neuzugaenge: ");
         strcat( meld, buf );
     }
     strcpy( buf, meld );
     CloseBase( );
   }
   return s;
}



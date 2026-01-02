/* --- includes --------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <hdatum/phodate.h>
#include <hdatum/phozeit.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include "art_prot.h"
#include <voodoo_table_header/zartaustria.h>
#include <voodoo_table_header/ccomgroupprop.h>
#include <voodoo_table_header/zartwg.h>

#include "wr_prot.h"

#include "znb_gen_dc.h"

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

void Zdcart_Protokol_Usage ( char *spBuf, char *prog )
{
   strcat( spBuf, "- " );
   strcat( spBuf, prog );
   strcat( spBuf, " 3 database datacaredatum [Verzeichnis] \n" \
                "  DC-Artikel Protokoll\n" );
}

/* --- page header ------------------------------ */

static char u0[200];

static void GenU0( long dcnr, int mode  )
{
   char *str;
   char nr[20];
   sprintf( nr, "%ld", dcnr );
   nr[9] = '\0';
   if ( mode == 0 )
      str = "ALLE SAETZE";
   else
      str = "NEUZUGAENGE";
   sprintf( u0, "ZPDCARTIK: PROTOKOLL DATACARE-AENDERUNGSDIENST DC-DATEI LF%s :: %s",
                &nr[2],
                str );
}

static char* z0 =
   "HNR   GUE-DAT  PZN     EINH-DC   ARTIKELBEZEICHNUNG-DC          " \
   "DFO     GEP-DC      AEP-DC      AVP-DC  MW TAX LI-CO HE-CO";

static char* z1 =
   "                       EINH-AS   ARTIKELBEZEICHNUNG-AS          " \
   "        GEP-AS      AEP-AS      AVP-AS	";

static char leer1[200];
static char leer2[200];
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
   int anz;
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


static void art_Zeile_1( struct ZDCART_PROT *zdc, char *spBuf )
{
   char ArtEinheit[20];
   char datum[11];
   long l;

   l = zdc->DC_DATUMGUELTIGAB;
   sprintf( datum, "%2.2ld.%2.2ld.%2.2ld",
                   l%100, (l/100)%100, (l/10000)%100 );
   Build_EINHEIT( ArtEinheit, zdc->DC_EINH_EINHEIT, zdc->DC_EINH_MENGE );

   sprintf( spBuf,
            "%.5ld %s %.7ld %s %s   %s %11.2f %11.2f %11.2f  %1.1s   %1.1s %5.5s %5.5s",
            zdc->HERSTELLER_NR,
            datum,
            zdc->DC_ARTIKEL_NR,
			ArtEinheit,
            zdc->DC_ARTIKELTEXT,
            zdc->DC_DARREICHFORM,
            zdc->DC_GEP,
            zdc->DC_AEP,
            zdc->DC_AVP,
            zdc->DC_MWST_GH,
			zdc->DC_TAXKZ,
			zdc->DC_CODE_LIEFERANT,
			zdc->DC_CODE_HERSTELLER
           );
}

static void art_Zeile_2( struct ZDCART_PROT   *zdc,
                         struct ZARTIKEL_PROT  *zart, long s_zart,
                         struct ZARTPREIS_PROT *zpre, long s_zpre,
                         char *spBuf )
{
   if ( s_zart != 0 )
   {
      set_leer( zart->EINHEIT,      L_ZARTIKEL_EINHEIT );
      set_leer( zart->ARTIKEL_NAME, L_ZARTIKEL_ARTIKEL_NAME );
      set_leer( zart->DARREICHFORM, L_ZARTIKEL_DARREICHFORM );
   }

   set_leer( leer1, 23 );

   if ( s_zpre == 0 )
   {
     sprintf( spBuf,
              "%s%s %s %s %11.2f %11.2f %11.2f ",
              leer1,
              zart->EINHEIT,
              zart->ARTIKEL_NAME,
              zart->DARREICHFORM,
              zpre->GROSSO,
              zpre->AEP,
              zpre->AVP
             );
   }
   else
   {
     set_leer( leer2, 11 );
     sprintf( spBuf,
              "%s%s %s %s %s %s %s %s",
              leer1,
              zart->EINHEIT,
              zart->ARTIKEL_NAME,
              zart->DARREICHFORM,
              leer2,
              leer2,
              leer2
             );
   }
}


static void art_Zeile(  struct ZDCART_PROT   *zdc,
                        struct ZARTIKEL_PROT  *zart, long s_zart,
                        struct ZARTPREIS_PROT *zpre, long s_zpre,
                        char *spBuf )
{
   art_Zeile_1( zdc, spBuf  );
   WriteZeile( spBuf );
/* Neuaufnahmen gegebenfalls 2. Zeile drucken */
   if ( s_zart == 0 )
   {
      art_Zeile_2( zdc, zart, s_zart, zpre, s_zpre, spBuf  );
      WriteZeile( spBuf );
   }
}

/* --- Schnittstelle ------------------------------------ */

static long art_OpenProtokol( long nr, char *verzeichnis, int mode,
                              char *errmld )
{
   char *datei;
   long s;
   int  lng;

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
   s = OpenFile( datei, "dc", 1, 1, errmld );

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

static long art_Protokol( struct ZDCART_PROT   *zdc,
                          struct ZARTIKEL_PROT  *zart,  long s_zart,
                          struct ZARTPREIS_PROT *zpre,  long s_zpre,
                          char *errmld )
{
   static long herst_num = -4711;
   char buf[400];
   int  mode;

   mode = art_Kopf( buf );

   if ( zdc->HERSTELLER_NR != herst_num ) 
   {
      herst_num = zdc->HERSTELLER_NR;
      if ( mode == 0 )
         WriteStrichZeile( );
      else
         WriteLeerZeile( );     /* bei Seitenwechsel keine Strichzeile */
   }
   else
      WriteLeerZeile( );

   art_Zeile( zdc, zart, s_zart, zpre, s_zpre, buf );


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
                 "DATUMGUELTIGAB<=? " \
                 "and ARTIKEL_NR=?)",
                 proj,
                 tagesdatum );

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

#endif

static long OpenZdcart( int *fd, char *proj, long dcnr, char *errmld )
{
   char sql[500];
   long status;
   sprintf( sql, "select %s from ZDCART where DCNR=%ld order by "  \
                 "DCNR,HERSTELLER_NR,DC_ARTIKEL_NR",
                  proj,
                  dcnr );
   status = SqlOpenCs( fd, sql );
   if ( status != 0 )
   {
      strcpy( errmld, "zdcart: " );
      strcat( errmld, DynErrmld() );
      *fd = -1;
   }
   return status;
}

static long ReadZdcart( int fd, struct ZDCART_PROT *zdc, char *errmld )
{
   long status;
   status = SqlFetch( fd, 1, zdc, NULL );
   if ( status == 100 )
   {
     strcpy( errmld, "zdcart: Kein Satz vorhanden" );
   }
   else if ( status != 0 )
   {
     strcpy( errmld, "zdcart: " );
     strcat( errmld, DynErrmld() );
   }
   return status;
}

/* -------------------------------------------------------------- */

static long Do_All( long dcnr, char *verzeichnis, int mode, char *errmld )
{
   long s;
   long s1;
   long s2;
   int fd_zdc;
   int fd_zpre;
   int fd_zart;

   long anz_gelesen;
   long artikel_nr;

   struct ZDCART_PROT   zdc;
   struct ZARTIKEL_PROT  zart;
   struct ZARTPREIS_PROT zpre;

   if ( DeclareZartikel( &fd_zart, ZARTIKEL_PROT_PROJ, errmld ) != 0 )
      return -1;
   if ( DeclareZpreis( &fd_zpre, ZARTPREIS_PROT_PROJ, GetPhoDate(),
                       errmld ) != 0 )
      return -1;

   s = OpenZdcart( &fd_zdc, ZDCART_PROT_PROJ, dcnr, errmld );
   if ( s == 0 )
   {
      s = ReadZdcart( fd_zdc, &zdc, errmld );
      if ( s == 0 )
      {
         s = art_OpenProtokol( dcnr, verzeichnis, mode, errmld );
         if ( s == 0 )
         {
            anz_gelesen = 0;
            do
            {
               artikel_nr = zdc.DC_ARTIKEL_NR;
               s1 = ReadZartikel( fd_zart, artikel_nr, &zart, errmld );
               if ( mode == 0 )
               {
                  anz_gelesen++;
#ifdef VOR_EURO
                  s2 = ReadZpreis  ( fd_zpre, artikel_nr, &zpre, errmld );
#else
                  s2 = ReadZpreis  ( fd_zpre, artikel_nr, zdc.DC_DATUMGUELTIGAB, &zpre, errmld );
#endif
                  s = art_Protokol ( &zdc, &zart, s1, &zpre, s2, errmld );
               }
               else
               {
                  s2 = 100;
                  if ( s1 != 0 )
                  {
                     anz_gelesen++;
                     s = art_Protokol ( &zdc, &zart, s1, &zpre, s2, errmld );
                  }
               }

               if ( s1 == 100 ) s1 = 0;
               if ( s2 == 100 ) s2 = 0;
               if ( s == 0 && s1 == 0 && s2 == 0 )
                  s = ReadZdcart( fd_zdc, &zdc, errmld );
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

   SqlCloseCs( fd_zdc );
   SqlCloseCs( fd_zpre );
   SqlCloseCs( fd_zart );

   return s;
}

long Zdcart_Protokol_Loop( char *db, char *c_dcdatum, char *verzeichnis, char *spBuf )
{
   long s;
   long dcnr;
   char meld[300];
   dcnr = atol( c_dcdatum );
   s = OpenBase( db, spBuf );
   if ( s == 0 )
   {
     s = Do_All( dcnr, verzeichnis, 0, spBuf );
     strcpy( meld, "Protokoll alle Saetze: ");
     strcat( meld, spBuf );
     if ( s == 0 )
     {
         s = Do_All( dcnr, verzeichnis, 1, spBuf );
         strcat( meld, "\nProtokoll Neuzugaenge: ");
         strcat( meld, spBuf );
     }
     strcpy( spBuf, meld );
     CloseBase( );
   }
   return s;
}



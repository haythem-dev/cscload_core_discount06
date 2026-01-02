
/* ---------------------------------------------------------------------- *
 *                         N B R _ A R T . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   Generiert die Artikel aus IFA                                *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  28.06.1998                                                   *
 * Update :  19.05.2005 Klaus Hinz                                        *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <phodate.h>

#include "stat_ifa.h"

/* -------  Spezielle includes ----------------------------------------- */

#include <tabsqld.h>

#include <wpp_prot.h>
#include <wpp_dbas.h>
#include <wpp_dirt.h>

/* ------- Tabellen includes -----------------------------------*/

#include <zifaart.h>
#include <zartikel.h>
#include <zartprei.h>
#include <cartpriceext.h>
#include <zartwg.h>
#include <zlifestyle.h>
#include <carticlecodes.h>
#include <ean.h>
#include <artve.h>
#include <zapflege.h>
#include <zaneuhei.h>
#include <zpznpflege.h>
#include "znb_gen.h"
#include "zart_gen.h"

#include "bssg.h"

#define L_ARTIKEL_NR 7

/* ------- Prototypes --------------- */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

long Reset_PL_C_HERSTNUM_Direkt( long ifanr, char *buf );

void KaufmRunden( double *wert, int stellen );

long ifa_OpenProtokol( long nr, char *verzeichnis, char *errmld );
long ifa_ProtokolLoe( struct ZARTIKEL *altart, char *errmld, long pzn8 );
long ifa_ProtokolNeu( struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis,
                      char *errmld, long pzn8 );
long ifa_ProtokolAen( struct ZARTIKEL *altart, struct ZARTPREIS *altpreis,
                      struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis,
                      char lagerung, char verfall, char vertrbind,
                      char *errmld, long pzn8 );
void ifa_CloseProtokol( int ok, char *errmld );


/* ----------------- Usage ------------------------ */

void GenArtUsage( char *buf, char *prog )
{
   strcat( buf, "- " );
   strcat( buf, prog );
   strcat( buf, " 0 database Ifadatum  p[ProtokolVerz][datum]\n" \
                "  alle relevanten Saetze generieren\n" );
   strcat( buf, "- " );
   strcat( buf, prog );
   strcat( buf, " 1 database Ifadatum  p[ProtokolVerz][datum]\n" \
                "  nur relevante Neuaufnahmen generieren\n" );
}

/* ----------------- artautidem ------------------------------- */

long m_Autidm_InsertRecord( long pzn, long datum, 
						    double gep_alt, double aep_alt,
						    double gep_neu, double aep_neu, 
							long hersteller_nr, long ifanr, char *errmld );

long GenDefpa( long ifanr, char *datei, char *errmld );

/* ----------------- spannenkuerzung ------------------------------- */

long m_Spankuerz_InsertRecord( long pzn, long datum, 
						       double gep_alt, double aep_alt, double spanne_alt,
						       double gep_neu, double aep_neu, double spanne_neu,
							   double kuerzung, double kuerzung_rel,
							   long hersteller_nr, long datum_anlage, char *errmld );

/* --------------------- rd_herst --------------------------------- */

void CloseHerstel( );

/* --------  user -------------- */

static char *user = "IFA     ";

/* ------ Spezielle SQL-Fehler --------------- */

#define  SQL_DOUBLE_ROW   ( -239 )

#define  SQL_LOCKED_ROW   ( -250 )

#define  SQL_NOT_FOUND    (  100 )
#define  SQL_NOT_ONE_ROW  ( -284 )

#define  SQL_DOUBLE_INDEX ( -346 )


#define  NOVALUE_ERROR    ( 47114712 )
#define  NOTRANS_ERROR    ( 8154711 )

/* ---------- Primekeycondition fuer alles ----------- */

static char PrimekeyCond[100];

/* ----- Zartikel ------------------------- */

#define MAX_ZARTIKEL 3

#define NR_ART 0
#define NR_ERS 1
#define NR_EAN 2  // temporärer Artikel zum Löschen von EAN bei DUPLIKATEN

static char CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];
static int  Fd_Zartikel = -1;
static long lStatus_Zartikel[MAX_ZARTIKEL];

static struct ZARTIKEL Buf_zartikel[MAX_ZARTIKEL];
static struct ZARTIKEL BufOld_zartikel[MAX_ZARTIKEL];

void FillCmpIndikator_Zartikel ( )
{
   memset( CmpIndikator_Zartikel, '1', POSANZ_ZARTIKEL );
   CmpIndikator_Zartikel[POSANZ_ZARTIKEL] = '\0';
   CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_ANLAGE]    = '0';
   CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_AENDER]    = '0';

/* IFA-Aenderungsdatum immer eintragen, auch wenn sonst keine Aenderung
   CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_IFAAENDER] = '0';
   CmpIndikator_Zartikel[P_ZARTIKEL_BEARBEITER]      = '0';
*/

}

int GetBufferDesc_Zartikel( char * errmld )
{
   char *tabelle = "zartikel";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zartikel >= 0 ) return 0;

   FillCmpIndikator_Zartikel ( );
   lStatus = OpenBufferDescProj( &Fd_Zartikel, tabelle, PROJECTION_ZARTIKEL,
                                 CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr );
								/* !!!!!!!bis 20.12.2000   V_PROTOKOL  */
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zartikel = -1;
     return -1;
   }
   return 0;
}

void InitRestArtikel( struct ZARTIKEL *zart, char *user );

int InitRecord_Zartikel( int i )
{
   long nr;
   nr = Buf_zartikel[i].ARTIKEL_NR;
   FdInitTabBuf( Fd_Zartikel, &Buf_zartikel[i] );
   Buf_zartikel[i].ARTIKEL_NR = nr;

   InitRestArtikel( &Buf_zartikel[i], user );

   return 0;
}

void SetPrimekeyCondition_Zartikel ( int i )
{
   char format[30];
   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartikel[i].ARTIKEL_NR );

/* sprintf( PrimekeyCond, "ARTIKEL_NR=%ld", Buf_zartikel[i].ARTIKEL_NR ); */
}

long ReadRecord_Zartikel( int i, long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_zartikel[i].ARTIKEL_NR = artikel_nr;
   SetPrimekeyCondition_Zartikel ( i );
   lStatus = FdReadRecord( Fd_Zartikel, PrimekeyCond,
                           &Buf_zartikel[i], errstr );

   if ( lStatus == 0 )
   {
      BufOld_zartikel[i] = Buf_zartikel[i];  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Zartikel( i ) == 0 )
      {
        BufOld_zartikel[i] = Buf_zartikel[i];  /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_Zartikel[i] = lStatus;
   return lStatus;
}


/* Generiert Matchcode aus Artikelname */

#define MC_LNG   12
#define AR_LNG  ( 30 - 2 )    /* nicht die letzten 2 Stellen wegen N1 */

char* MakeArtikelMc( char *name )
{
   static char mc[MC_LNG + 1];
   int i;
   int j;

   i = 0;
   j = 0;
   while ( name[j] && j < AR_LNG && i < MC_LNG )
   {
     if ( name[j] != ' ' ) mc[i++] = name[j];
     j++;
   }
   while ( i < MC_LNG ) mc[i++] = ' ';
     mc[i] = '\0';
   return mc;
}


long StoreRecord_Zartikel( int i, char* cErrmld )
{
   long lStatus;
   char errmld[200];

   /* Artikel-Mc generieren */
   strcpy( Buf_zartikel[i].ARTIKEL_MC,
           MakeArtikelMc( Buf_zartikel[i].ARTIKEL_NAME ) );

   SetPrimekeyCondition_Zartikel ( i );
   if ( lStatus_Zartikel[i] == 100 )
      lStatus = FdDelayInsertRecord( Fd_Zartikel, &Buf_zartikel[i],
                                     PrimekeyCond, errmld);
   else if ( lStatus_Zartikel[i] == 0 )
      lStatus = FdDelayUpdateRecord( Fd_Zartikel, &Buf_zartikel[i],
                                     &BufOld_zartikel[i],
                                     PrimekeyCond, errmld );
   else
   {
     lStatus = lStatus_Zartikel[i];
     strcpy( cErrmld, "Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}


/* ----- Zpreis   ------------------------- */

#define NUMBER_OF_PRICE 2

static int  Fd_Zpreis = -1;

static long lStatus_Zpreis[NUMBER_OF_PRICE];

static struct ZARTPREIS Buf_zpreis[NUMBER_OF_PRICE];
static struct ZARTPREIS BufOld_zpreis[NUMBER_OF_PRICE];

static char PrimekeyCond_Zpreis[100];

int GetBufferDesc_Zpreis( char * errmld )
{
   char *tabelle = "zartpreis";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zpreis >= 0 ) return 0;

    lStatus = OpenBufferDescProj( &Fd_Zpreis, tabelle, PROJECTION_ZARTPREIS,
                                  NULL, NULL, V_PROTO_VERTEIL, errstr );
				/* !!!!!!!bis 20.12.2000   V_PROTOKOL */
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_Zpreis = -1;
      return -1;
    }
    return 0;
}

int InitRecord_Zpreis( int i )
{
     long nr;
     long datum;
     nr  = Buf_zpreis[i].ARTIKEL_NR;
     datum = Buf_zpreis[i].DATUMGUELTIGAB;
     FdInitTabBuf( Fd_Zpreis, &Buf_zpreis[i] );
     Buf_zpreis[i].DATUMGUELTIGAB = datum;
     Buf_zpreis[i].ARTIKEL_NR = nr;
     return 0;
}

void SetPrimekeyCondition_Zpreis( int i )
{
  char format[50];
  sprintf( format, "ARTIKEL_NR=%c%d.ld and DATUMGUELTIGAB=%cld",
                   '%', L_ARTIKEL_NR, '%' );
  sprintf( PrimekeyCond_Zpreis, format,
            Buf_zpreis[i].ARTIKEL_NR,
            Buf_zpreis[i].DATUMGUELTIGAB );

/*
  sprintf( PrimekeyCond_Zpreis,
           "ARTIKEL_NR=%ld and DATUMGUELTIGAB=%ld",
            Buf_zpreis[i].ARTIKEL_NR,
            Buf_zpreis[i].DATUMGUELTIGAB );
*/
}

long ReadRecord_ZpreisLast( int i, long artikel_nr, char *cErrmld )
{
   long lStatus;
   char sql[150];

   lStatus = 100;
   strcpy( cErrmld, "" );

   /* Preis-Saetze lesen  */

   sprintf( sql, "select * from ZARTPREIS where ARTIKEL_NR=%ld " \
                 "order by ARTIKEL_NR,DATUMGUELTIGAB desc",
                 artikel_nr );

   lStatus = SqlRead(  sql, &Buf_zpreis[i], NULL );

   if ( lStatus == 0 )
   {
      BufOld_zpreis[i] = Buf_zpreis[i];  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Zpreis( i  ) == 0 )
      {
        BufOld_zpreis[i] = Buf_zpreis[i];  /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, DynErrmld() );
   lStatus_Zpreis[i] = lStatus;
   return lStatus;
}

long ReadRecord_Zpreis( int i, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   SetPrimekeyCondition_Zpreis ( i );
   lStatus = FdReadRecord( Fd_Zpreis, PrimekeyCond_Zpreis,
                           &Buf_zpreis[i], errstr );

   if ( lStatus == 0 )
   {
      BufOld_zpreis[i] = Buf_zpreis[i];  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Zpreis( i ) == 0 )
      {
        BufOld_zpreis[i] = Buf_zpreis[i];  /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_Zpreis[i] = lStatus;
   return lStatus;
}


long StoreRecord_Zpreis( int i, char *cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zpreis ( i );
   if ( lStatus_Zpreis[i] == 100 )
      lStatus = FdDelayInsertRecord( Fd_Zpreis, &Buf_zpreis[i],
                                     PrimekeyCond_Zpreis, errmld );
   else if ( lStatus_Zpreis[i] == 0 )
      lStatus = FdDelayUpdateRecord( Fd_Zpreis, &Buf_zpreis[i],
                                     &BufOld_zpreis[i],
                                     PrimekeyCond_Zpreis, errmld );
   else
   {
     lStatus = lStatus_Zpreis[i];
     strcpy( errmld, "Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}

/* ----- cartpriceext   ------------------------- */

static int  Fd_CArtPriceExt = -1;

static long lStatus_CArtPriceExt;

static struct CARTPRICEEXT Buf_CArtPriceExt;
static struct CARTPRICEEXT BufOld_CArtPriceExt;

static struct CARTPRICEEXT Buf_CArtPriceExt_Current;

static char PrimekeyCond_CArtPriceExt[100];

int GetBufferDesc_CArtPriceExt( char * errmld )
{
   char *tabelle = "cartpriceext";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   
   if ( Fd_CArtPriceExt >= 0 ) 
	   return 0;

    lStatus = OpenBufferDescProj( &Fd_CArtPriceExt, tabelle, PROJECTION_CARTPRICEEXT,
                                  NULL, NULL, V_PROTO_VERTEIL, errstr );
				
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_CArtPriceExt = -1;
      return -1;
    }
    return 0;
}

int InitRecord_CArtPriceExt( )
{
     long nr;
     long datum;
     nr  = Buf_CArtPriceExt.ARTICLENO;
     datum = Buf_CArtPriceExt.DATEVALIDFROM;
     FdInitTabBuf( Fd_CArtPriceExt, &Buf_CArtPriceExt );
     Buf_CArtPriceExt.DATEVALIDFROM = datum;
     Buf_CArtPriceExt.ARTICLENO = nr;
     return 0;
}

void SetPrimekeyCondition_CArtPriceExt( )
{
  char format[50];
  sprintf( format, "ARTICLENO=%c%d.ld and DATEVALIDFROM=%cld",
                   '%', L_ARTIKEL_NR, '%' );
  sprintf( PrimekeyCond_CArtPriceExt, format,
            Buf_CArtPriceExt.ARTICLENO,
            Buf_CArtPriceExt.DATEVALIDFROM );
}

long ReadRecord_CArtPriceExt_Current( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char sql[150];

   lStatus = 100;
   strcpy( cErrmld, "" );

   /* Preis-Saetze lesen  */

   sprintf( sql, "select * from CARTPRICEEXT where ARTICLENO=%ld " \
                 "order by DATEVALIDFROM desc",
                 artikel_nr );

   lStatus = SqlRead(  sql, &Buf_CArtPriceExt_Current, NULL );

   if ( lStatus == 0 || lStatus == 100 )
   {
      strcpy( cErrmld, "" );
   }
   else
      strcpy ( cErrmld, DynErrmld() );
   
   return lStatus;
}

long ReadRecord_CArtPriceExt( char *cErrmld )
{
   long lStatus;
   char errstr[200];

   SetPrimekeyCondition_CArtPriceExt ( );
   lStatus = FdReadRecord( Fd_CArtPriceExt, PrimekeyCond_CArtPriceExt,
                           &Buf_CArtPriceExt, errstr );

   if ( lStatus == 0 )
   {
      BufOld_CArtPriceExt = Buf_CArtPriceExt;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_CArtPriceExt( ) == 0 )
      {
        BufOld_CArtPriceExt = Buf_CArtPriceExt; /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );

   lStatus_CArtPriceExt = lStatus;
   return lStatus;
}

long StoreRecord_CArtPriceExt( char *cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_CArtPriceExt ( );

   if ( lStatus_CArtPriceExt == 100 )
      lStatus = FdDelayInsertRecord( Fd_CArtPriceExt, &Buf_CArtPriceExt,
                                     PrimekeyCond_CArtPriceExt, errmld );
   else if ( lStatus_CArtPriceExt == 0 )
      lStatus = FdDelayUpdateRecord( Fd_CArtPriceExt, &Buf_CArtPriceExt,
                                     &BufOld_CArtPriceExt,
                                     PrimekeyCond_CArtPriceExt, errmld );
   else
   {
     lStatus = lStatus_CArtPriceExt;
     strcpy( errmld, "Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );

   return lStatus;
}


/* -----  Ean     ------------------------- */

static int  Fd_Zean = -1;
static long lStatus_Zean;

static struct EAN Buf_zean;
static struct EAN BufOld_zean;
static struct EAN BufEan_zean;

int GetBufferDesc_Zean( char * errmld )
{
   char *tabelle = "ean";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zean >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zean, tabelle, PROJECTION_EAN,
                                 NULL, NULL,
                             /*  V_PROTO_VERTEIL, */
                                 V_PROTOKOL,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zean = -1;
     return -1;
   }
   return 0;
}

int InitRecord_Zean( )
{
   long nr;
   nr = Buf_zean.ARTIKEL_NR;
   FdInitTabBuf( Fd_Zean, &Buf_zean );
   Buf_zean.ARTIKEL_NR = nr;
   return 0;
}

void SetPrimekeyCondition_Zean ( )
{
   char format[30];
   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zean.ARTIKEL_NR );

/* sprintf( PrimekeyCond, "ARTIKEL_NR=%ld", Buf_zean.ARTIKEL_NR ); */
}

long DeleteRecord_Zean(long artikel_nr, char* cErrmld)
{
    long lStatus = -1;
    strcpy(cErrmld, "");
    sprintf(PrimekeyCond, "ARTIKEL_NR=%ld", artikel_nr);
    lStatus = FdDelayDeleteRecord(Fd_Zean, &BufEan_zean, PrimekeyCond, cErrmld);
    return lStatus;
}

long ReadRecord_Zean( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_zean.ARTIKEL_NR = artikel_nr;

   SetPrimekeyCondition_Zean ( );
   lStatus = FdReadRecord( Fd_Zean, PrimekeyCond,
                           &Buf_zean, errstr );

   if ( lStatus == 0 )
   {
      BufOld_zean = Buf_zean;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Zean( ) == 0 )
      {
        BufOld_zean = Buf_zean;  /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_Zean = lStatus;
   return lStatus;
}

long ReadRecord_Zean2(char* ean_nr, char* cErrmld)
{
    long status = -1;
    char errstr[200];
    
    if (ean_nr != NULL)
    {
        strncpy(BufEan_zean.EAN_NR, ean_nr, 13);
        sprintf(PrimekeyCond, "EAN_NR='%s'", Buf_zean.EAN_NR);

    }
    status = FdReadRecord(Fd_Zean, PrimekeyCond,
        &BufEan_zean, errstr);

    return status;
}

long StoreRecord_Zean( char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zean ( );
   if ( lStatus_Zean == 100 )
      lStatus = FdDelayInsertRecord( Fd_Zean, &Buf_zean,
                                     PrimekeyCond, errmld);
   else if ( lStatus_Zean == 0 )
      lStatus = FdDelayUpdateRecord( Fd_Zean, &Buf_zean,
                                     &BufOld_zean,
                                     PrimekeyCond, errmld );
   else
   {
     lStatus = lStatus_Zean;
     strcpy( cErrmld, "Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}


/* -----  Artve     ------------------------- */

static int    Fd_Artve      = -1;
static long   lStatus_Artve =  0;
static struct ARTVE Buf_Artve;
static struct ARTVE BufOld_Artve;

int GetBufferDesc_Artve( char * errmld )
{
   char *tabelle = "artve";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");

   if ( Fd_Artve >= 0 )
   {
      return 0;
   }

   lStatus = OpenBufferDescProj( &Fd_Artve,
                                  tabelle,
                                  PROJECTION_ARTVE,
                                  NULL,
                                  NULL,
                                  V_PROTOKOL,
                                  errstr );
   if ( lStatus != 0 )
   {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_Artve = -1;
      return -1;
   }

   return 0;
}

int InitRecord_Artve( )
{
   long nr = Buf_Artve.ARTIKEL_NR;

   FdInitTabBuf( Fd_Artve, &Buf_Artve );

   Buf_Artve.ARTIKEL_NR = nr;

   return 0;
}

void SetPrimekeyCondition_Artve ( )
{
   char format[30];

   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_Artve.ARTIKEL_NR );
}

long ReadRecord_Artve( long artikel_nr, char *cErrmld )
{
   long lStatus = 0;
   char errstr[200];

   Buf_Artve.ARTIKEL_NR = artikel_nr;

   SetPrimekeyCondition_Artve ( );

   lStatus = FdReadRecord(  Fd_Artve,
                            PrimekeyCond,
                           &Buf_Artve,
                            errstr );

   if ( lStatus == 0 )
   {
      BufOld_Artve = Buf_Artve;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Artve( ) == 0 )
      {
         BufOld_Artve = Buf_Artve;  /* initial. sichern */
      }
      else
      {
         lStatus = -1;
      }
   }
   else
   {
      strcpy ( cErrmld, errstr );
   }

   lStatus_Artve = lStatus;

   return lStatus;
}

long StoreRecord_Artve( char* cErrmld )
{
   long lStatus = 0;
   char errmld[200];

   SetPrimekeyCondition_Artve ( );

   if ( lStatus_Artve == 100 )
   {
      lStatus = FdDelayInsertRecord(  Fd_Artve,
                                     &Buf_Artve,
                                      PrimekeyCond,
                                      errmld);
   }
   else if ( lStatus_Artve == 0 )
   {
      lStatus = FdDelayUpdateRecord(  Fd_Artve,
                                     &Buf_Artve,
                                     &BufOld_Artve,
                                      PrimekeyCond,
                                      errmld );
   }
   else
   {
     lStatus = lStatus_Artve;
     strcpy( cErrmld, "Interner Fehler" );
   }

   if ( lStatus != 0 )
   {
      strcpy( cErrmld, errmld );
   }
   else
   {
      strcpy( cErrmld, "" );
   }

   return lStatus;
}


/* -----  Zartwg  -------------------------- */

#define WG_DKART  '2'
#define WG_SAISON '5'
#define WG_SAISON2 'A'
#define WG_ABDA	  '4'
#define WG_WIRKST 'E'
#define WG_VERTRCL 'F'

static int  Fd_Zartwg = -1;

static struct ZARTWG Buf_zartwg;
static struct ZARTWG BufOld_zartwg;

static char  PrimekeyCond_Zartwg[50];

static long lStatus_Zartwg;

int GetBufferDesc_Zartwg( char* errmld )
{
   char *tabelle = "zartwg";
   long lStatus;
   char errstr[100];

   strcpy( errmld, "");
   if ( Fd_Zartwg >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zartwg, tabelle, PROJECTION_ZARTWG,
                                 NULL, NULL, V_PROTO_VERTEIL, errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zartwg = -1;
    return -1;
   }
  return 0;
}

void SetPrimekeyCondition_Zartwg( )
{
   char format[50];
   sprintf( format, "ARTIKEL_NR=%c%d.ld and ART='%cs'",
                    '%', L_ARTIKEL_NR, '%' );

   sprintf( PrimekeyCond_Zartwg, format,
            Buf_zartwg.ARTIKEL_NR,
            Buf_zartwg.ART );

/*
   sprintf( PrimekeyCond_Zartwg,
            "ARTIKEL_NR=%ld and ART='%s'",
            Buf_zartwg.ARTIKEL_NR,
            Buf_zartwg.ART );
*/
}

int InitRecord_Zartwg( )
{
   strcpy( Buf_zartwg.WARENGRUPPE, "     " );
   return 0;
}

static long ReadRecord_Zartwg( char wg_art, long artikel_nr, char *cErrmld )
{
   char errstr[200];

   Buf_zartwg.ARTIKEL_NR = artikel_nr;
   Buf_zartwg.ART[0] = wg_art;
   Buf_zartwg.ART[1] = '\0';

   SetPrimekeyCondition_Zartwg ( );
   lStatus_Zartwg = FdReadRecord( Fd_Zartwg, PrimekeyCond_Zartwg,
                           &Buf_zartwg, errstr );
   if ( lStatus_Zartwg == 0 )
   {
      BufOld_zartwg = Buf_zartwg;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus_Zartwg == 100 )
   {
      if ( InitRecord_Zartwg( ) == 0 )
      {
        BufOld_zartwg = Buf_zartwg;  /* gelesenen Satz sichern */
      }
      else
        lStatus_Zartwg = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   return lStatus_Zartwg;
}

static long StoreRecord_Zartwg( char* cErrmld )
{
   long lStatus;
   strcpy( cErrmld, "" );
   
   if ( !( lStatus_Zartwg == 0 || lStatus_Zartwg == 100 ) ) 
	   return -1;

   if ( 100  == lStatus_Zartwg)  
   {
       lStatus = FdDelayInsertRecord( Fd_Zartwg, &Buf_zartwg,
                                PrimekeyCond_Zartwg, cErrmld);
   }
   else if (  0 == lStatus_Zartwg )     
   {
       lStatus = FdDelayUpdateRecord( Fd_Zartwg, &Buf_zartwg,
                                &BufOld_zartwg,
                                PrimekeyCond_Zartwg, cErrmld );
   }
   return lStatus;
}

static long Copy_Zartwg( char wg_art, long artikel_nr, long ersatz_nr,
                         char *errmld )
{
   long s;
   s = ReadRecord_Zartwg( wg_art, ersatz_nr, errmld );
   if ( s == 0 )
   {
     char wgr_nr[10];
     strcpy( wgr_nr, Buf_zartwg.WARENGRUPPE );
     s = ReadRecord_Zartwg ( wg_art, artikel_nr, errmld );
     if ( s == 100 )
     {
       strcpy( Buf_zartwg.WARENGRUPPE, wgr_nr );
       s = FdDelayInsertRecord( Fd_Zartwg, &Buf_zartwg,
                                PrimekeyCond_Zartwg, errmld);
     }
     else if ( s == 0 )
     {
       strcpy( Buf_zartwg.WARENGRUPPE, wgr_nr );
       s = FdDelayUpdateRecord( Fd_Zartwg, &Buf_zartwg,
                                &BufOld_zartwg,
                                PrimekeyCond_Zartwg, errmld );
     }
   }
   return s;
}

/* -----  Zapflege  ------------------------- */

static int  Fd_Zapflege = -1;

static struct ZAPFLEGE Buf_zapflege;

int GetBufferDesc_Zapflege( char * errmld )
{
   char *tabelle = "zapflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zapflege >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zapflege, tabelle, PROJECTION_ZAPFLEGE,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zapflege = -1;
     return -1;
   }
   return 0;
}

long StoreRecord_Zapflege( long artikel_nr, long datum, char* cErrmld )
{
   long lStatus;

   Buf_zapflege.ARTIKEL_NR = artikel_nr;
   Buf_zapflege.DATUM      = datum;

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld",
                          Buf_zapflege.ARTIKEL_NR,
                          Buf_zapflege.DATUM );

   lStatus = FdReadRecord( Fd_Zapflege, PrimekeyCond,
                           &Buf_zapflege, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   if ( lStatus == 100 )
   {
      Buf_zapflege.ARTIKEL_NR = artikel_nr;
      Buf_zapflege.DATUM      = datum;
      lStatus = FdDelayInsertRecord( Fd_Zapflege, &Buf_zapflege,
                                     PrimekeyCond, cErrmld);
   }
   return lStatus;
}

/* -----  Zpznpflege  ------------------------- */

static int  Fd_Zpznpflege = -1;

static struct ZPZNPFLEGE Buf_zpznpflege;

int GetBufferDesc_Zpznpflege( char * errmld )
{
   char *tabelle = "zpznpflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zpznpflege >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zpznpflege, tabelle, PROJECTION_ZPZNPFLEGE,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zpznpflege = -1;
     return -1;
   }
   return 0;
}

long StoreRecord_Zpznpflege( char* dezap_sa, long artikel_nr, long datum,  char* cErrmld )
{
   long lStatus;

   Buf_zpznpflege.ARTIKEL_NR = artikel_nr;
   Buf_zpznpflege.DATUM      = datum;
   strcpy (Buf_zpznpflege.DEZAP_SA, dezap_sa);
   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld and DEZAP_SA = '%s'",
                          Buf_zpznpflege.ARTIKEL_NR,
                          Buf_zpznpflege.DATUM,Buf_zpznpflege.DEZAP_SA );

   lStatus = FdReadRecord( Fd_Zpznpflege, PrimekeyCond,
                           &Buf_zpznpflege, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   if ( lStatus == 100 )
   {
      Buf_zpznpflege.ARTIKEL_NR = artikel_nr;
      Buf_zpznpflege.DATUM      = datum;
      lStatus = FdDelayInsertRecord( Fd_Zpznpflege, &Buf_zpznpflege,
                                     PrimekeyCond, cErrmld);
   }
   return lStatus;
}


/* -----  Zaneuheit  ------------------------- */

static int  Fd_Zaneuheit = -1;

static struct ZANEUHEIT Buf_zaneuheit;

int GetBufferDesc_Zaneuheit( char * errmld )
{
   char *tabelle = "zaneuheit";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zaneuheit >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zaneuheit, tabelle, PROJECTION_ZANEUHEIT,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zaneuheit = -1;
     return -1;
   }
   return 0;
}

long StoreRecord_Zaneuheit( char *programm, struct ZARTIKEL *zart,
                            long datum, char* cErrmld )
{
   long lStatus;

   strcpy( Buf_zaneuheit.PFLEGEPROGRAMM, programm );
   Buf_zaneuheit.ARTIKEL_NR = zart->ARTIKEL_NR;

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "PFLEGEPROGRAMM='%s' and ARTIKEL_NR=%ld",
                          Buf_zaneuheit.PFLEGEPROGRAMM,
                          Buf_zaneuheit.ARTIKEL_NR );

   lStatus = FdReadRecord( Fd_Zaneuheit, PrimekeyCond,
                           &Buf_zaneuheit, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   if ( lStatus == 100 )
   {
      strcpy( Buf_zaneuheit.PFLEGEPROGRAMM, programm );
      Buf_zaneuheit.ARTIKEL_NR = zart->ARTIKEL_NR;
      Buf_zaneuheit.DATUM      = datum;
      strcpy( Buf_zaneuheit.ARTIKEL_MC, zart->ARTIKEL_MC );
      Buf_zaneuheit.HERSTELLER_NR = zart->HERSTELLER_NR;
      lStatus = FdDelayInsertRecord( Fd_Zaneuheit, &Buf_zaneuheit,
                                     PrimekeyCond, cErrmld);
   }
   return lStatus;
}


/* -----  Zlifestyle  ------------------------- */

static int  Fd_Zlifestyle = -1;

static struct ZLIFESTYLE Buf_Zlifestyle;
static struct ZLIFESTYLE BufOld_Zlifestyle;
//static char CmpIndikator_Zlifestyle[POSANZ_ZLIFESTYLE + 1];
static char PrimekeyCond_Zlifestyle[50];
static long lStatus_Zlifestyle;


int GetBufferDesc_Zlifestyle( char * errmld )
{
   char *tabelle = "zlifestyle";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zlifestyle >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zlifestyle, tabelle, PROJECTION_ZLIFESTYLE,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zlifestyle = -1;
     return -1;
   }
   return 0;
}

int InitRecord_Zlifestyle(  )
{
   long nr;
   nr = Buf_Zlifestyle.ARTIKEL_NR;
   FdInitTabBuf( Fd_Zlifestyle, &Buf_Zlifestyle );
   Buf_Zlifestyle.ARTIKEL_NR = nr;
   Buf_Zlifestyle.LIFESTYLE[0] = '0';
   Buf_Zlifestyle.LIFESTYLE[1] = '\0';
   return 0;
}


void SetPrimekeyCondition_Zlifestyle( )
{
   sprintf( PrimekeyCond_Zlifestyle,"ARTIKEL_NR=%7d ", Buf_Zlifestyle.ARTIKEL_NR);
}


long ReadRecord_Zlifestyle( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_Zlifestyle.ARTIKEL_NR = artikel_nr;

   SetPrimekeyCondition_Zlifestyle ( );
   lStatus = FdReadRecord( Fd_Zlifestyle, PrimekeyCond_Zlifestyle,
                           &Buf_Zlifestyle, errstr );
   if ( lStatus == 0 )
   {
      BufOld_Zlifestyle = Buf_Zlifestyle;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Zlifestyle( ) == 0 )
      {
        BufOld_Zlifestyle = Buf_Zlifestyle;  /* gelesenen Satz sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_Zlifestyle = lStatus;
   return lStatus;
}


long StoreRecord_Zlifestyle( char* cErrmld )
{
   long lStatus;

   strcpy( cErrmld, "" );
   
   lStatus = lStatus_Zlifestyle;


   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   /*if ( lStatus == 0) &&  /*
   /*return FdDelayDeleteRecord( Fd_Zlifestyle, Buf_Zlifestyle, PrimekeyCond_Zlifestyle, errmld );	   */ 

   
   
   if ( 100  == lStatus)  {
       lStatus = FdDelayInsertRecord( Fd_Zlifestyle, &Buf_Zlifestyle,
                                PrimekeyCond_Zlifestyle, cErrmld);
     }
     else if (  0 == lStatus )      {
       lStatus = FdDelayUpdateRecord( Fd_Zlifestyle, &Buf_Zlifestyle,
                                &BufOld_Zlifestyle,
                                PrimekeyCond_Zlifestyle, cErrmld );
     }
   return lStatus;
}

long DeleteRecord_Zlifestyle( char* cErrmld )
{
   long lStatus;

   strcpy( cErrmld, "" );
   
   lStatus = lStatus_Zlifestyle;

   if ( 0 != lStatus   ) return -1;

   
   lStatus = FdDelayDeleteRecord( Fd_Zlifestyle, &Buf_Zlifestyle, PrimekeyCond_Zlifestyle, cErrmld );	   

   return lStatus;
}


/* -----  CArticleCodes  ------------------------- */

static int  Fd_CArticleCodes = -1;

static struct CARTICLECODES Buf_CArticleCodes;
static struct CARTICLECODES BufOld_CArticleCodes;
static char PrimekeyCond_CArticleCodes[100];

#define CODETYPE_ZULREG		7
#define CODETYPE_EAR		1
#define CODETYPE_NTIN		22
#define CODETYPE_GTIN14     26

int GetBufferDesc_CArticleCodes( char * errmld )
{
   char *tabelle = "carticlecodes";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_CArticleCodes >= 0 ) 
	   return 0;

   lStatus = OpenBufferDescProj( &Fd_CArticleCodes, tabelle, PROJECTION_CARTICLECODES,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_CArticleCodes = -1;
     return -1;
   }
   return 0;
}

int InitRecord_CArticleCodes(  )
{
   long nr;
   short ct;
   nr = Buf_CArticleCodes.ARTICLENO;
   ct = Buf_CArticleCodes.CODE_TYPE;
   FdInitTabBuf( Fd_CArticleCodes, &Buf_CArticleCodes );
   Buf_CArticleCodes.ARTICLENO = nr;
   Buf_CArticleCodes.SERIAL_NUMBER = 0;
   Buf_CArticleCodes.CODE_TYPE = ct;
   return 0;
}


void SetPrimekeyCondition_CArticleCodes( )
{
	short sno = 0;

	if ( Buf_CArticleCodes.CODE_TYPE == CODETYPE_NTIN || 
         Buf_CArticleCodes.CODE_TYPE == CODETYPE_GTIN14 )
		sno = 1;

	sprintf( PrimekeyCond_CArticleCodes,"ARTICLENO=%7d AND SERIAL_NUMBER=%d AND CODE_TYPE=%d", Buf_CArticleCodes.ARTICLENO, sno, Buf_CArticleCodes.CODE_TYPE);
}


long ReadRecord_CArticleCodes( short code_type, long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_CArticleCodes.ARTICLENO = artikel_nr;
   Buf_CArticleCodes.CODE_TYPE = code_type;

   SetPrimekeyCondition_CArticleCodes ( );
   lStatus = FdReadRecord( Fd_CArticleCodes, PrimekeyCond_CArticleCodes,
                           &Buf_CArticleCodes, errstr );
   if ( lStatus == 0 )
   {
      BufOld_CArticleCodes = Buf_CArticleCodes;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_CArticleCodes( ) == 0 )
      {
        BufOld_CArticleCodes = Buf_CArticleCodes;  /* gelesenen Satz sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   
   return lStatus;
}


long UpdateRecord_CArticleCodes( char* cErrmld )
{
   long lStatus;

   strcpy( cErrmld, "" );
   
   lStatus = FdDelayUpdateRecord( Fd_CArticleCodes, &Buf_CArticleCodes,
                                &BufOld_CArticleCodes,
                                PrimekeyCond_CArticleCodes, cErrmld );
   return lStatus;
}

long InsertRecord_CArticleCodes( char* cErrmld )
{
   long lStatus;

   strcpy( cErrmld, "" );
   
   lStatus = FdDelayInsertRecord( Fd_CArticleCodes, &Buf_CArticleCodes,
                                PrimekeyCond_CArticleCodes, cErrmld);
   
   return lStatus;
}

long DeleteRecord_CArticleCodes( char* cErrmld )
{
   long lStatus;

   strcpy( cErrmld, "" );
   
   lStatus = FdDelayDeleteRecord( Fd_CArticleCodes, &Buf_CArticleCodes, PrimekeyCond_CArticleCodes, cErrmld );	   

   return lStatus;
}


/* ---------------------------------------------------------------------- *
 * Funktion         Zifa lesen                                            *
 * ---------------------------------------------------------------------- */

#define S_ZIFA ZIFAART

static char *zifa_proj = "*";

static int fd_zifa_sel = -1;
static int fd_zifa_del = -1;

static long Zifa_Select( long ifanr, long datum, char mode, char *errmld )
{
    long s;
    char sql[500];

    /* Select unabhaengig vom IFASTATUS / NBSTATUS */
    /* das bedeutet: alle Saetze im Datumsbereich werden geloescht */
    /*    nur die Saetze mit IFASTATUS = IFASTATUS_FREIGEGEBEN */
    /*                   und NBSTATUS <= '1'  werden uebernommen */
    /*    diese Auswahl geschieht vor Do_All */

    if ( mode == '0' )   /* Alle relevanten Saetze */
      sprintf( sql,
          "select %s from ZIFAART where IFANR=%ld and "  \
          "DATUMGUELTIGAB>0 and DATUMGUELTIGAB<=%ld " \
          "order by IFANR,A00PZN",
          zifa_proj,
          ifanr,
          datum );
    else                 /* alle relevanten Neuaufnahmen */
      sprintf( sql,
          "select %s from ZIFAART where IFANR=%ld and "  \
          "AENDERUNG='0' and " \
          "DATUMGUELTIGAB>0 and DATUMGUELTIGAB<=%ld " \
          "order by IFANR,A00PZN",
          zifa_proj,
          ifanr,
          datum );


/*  printf("%s\n", sql );  */

    s = SqlOpenCsWh( &fd_zifa_sel, sql );
    if ( s != 0 )
    {
      fd_zifa_sel = -1;
      sprintf( errmld, "ZIFAART: %s", DynErrmld() );
    }
    return s;
}

static long Zifa_Fetch( struct S_ZIFA *ifa, char *errmld )
{
    long s;
    s = SqlFetch( fd_zifa_sel, 1, ifa, NULL );
    if ( s != 0 )
      sprintf( errmld, "ZIFAART: %s", DynErrmld() );
    return s;
}

static long Zifa_CloseCs( char *errmld )
{
    long s;
    if ( fd_zifa_sel == -1 ) return 0;
    s = SqlCloseCs( fd_zifa_sel );
    if ( s != 0 && errmld != NULL )
       sprintf( errmld, "ZIFAART: %s", DynErrmld() );
    fd_zifa_sel = -1;
    return s;
}

static long Zifa_PrepDelete( char *errmld )
{
    long s;
    s = SqlPrepareStmnt ( &fd_zifa_del,
                          "delete from ZIFAART where IFANR=? and SATZNR=?",
                          "ZIFAART.IFANR", "ZIFAART.SATZNR", NULL );
    if ( s != 0 )
    {
      fd_zifa_del = -1;
      sprintf( errmld, "ZIFAART PrepDelete: %s", DynErrmld() );
    }
    return s;
}

static long Zifa_ExecuteDelete( struct S_ZIFA *ifa, char *errmld )
{
    long s;
    long ifanr;
    long satznr;
    ifanr  = ifa->IFANR;
    satznr = ifa->SATZNR;
    s = SqlExecutePrepare( fd_zifa_del, &ifanr, &satznr, NULL );
    if ( s != 0 )
      sprintf( errmld, "ZIFAART ExecDelete: %s", DynErrmld() );
    return s;
}

static long Zifa_FreeDelete( char *errmld )
{
    long s;
    if ( fd_zifa_del == -1 )  return 0;
    s = SqlFreePrepare( fd_zifa_del );
    if ( s != 0 && errmld != NULL )
        sprintf( errmld, "ZIFAART FreeDelete: %s", DynErrmld() );
    fd_zifa_del = -1;
    return s;
}

/* --- hier neu: pzn ueber pznnf lesen --- */

static int fd_zifa_pznnf = -1;

static long Zifa_PZNNF_Declare( long ifanr, char *errmld )
{
    long s;
    char sql[200];

    sprintf( sql,
             "select A00PZN from ZIFAART " \
             "where IFANR=%ld and A06PZNNF=?",
             ifanr );
/*  printf("%s\n", sql );  */

    s = SqlDeclareCs( &fd_zifa_pznnf, sql, "ZIFAART.A06PZNNF", NULL );
    if ( s != 0 )
    {
      fd_zifa_pznnf = -1;
      sprintf( errmld, "ZIFAART: %s", DynErrmld() );
    }
    return s;
}

static long Zifa_PZNNF_Read( long *pzn, long pznnf, char *errmld )
{
    long s;

    s = SqlReadDeclCs( fd_zifa_pznnf,
                       pzn, NULL,
                       &pznnf, NULL );
    if ( s != 0 )
      sprintf( errmld, "ZIFAART: %s", DynErrmld() );
    return s;
}

static long Zifa_PZNNF_CloseCs( char *errmld )
{
    long s;
    if ( fd_zifa_pznnf == -1 ) return 0;
    s = SqlCloseCs( fd_zifa_pznnf );
    if ( s != 0 && errmld != NULL )
       sprintf( errmld, "ZIFAART: %s", DynErrmld() );
    fd_zifa_pznnf = -1;
    return s;
}

/* --- hier neu: zifaart lesen für preissenkung */

static int fd_zifa_zifaart = -1;

static long Zifa_zifaart_Declare(  char *errmld )
{
    long s;
    char sql[2000];


    sprintf( sql,
             "select %s from ZIFAART " \
             "where A00PZN=? and DATUMGUELTIGAB=?",
              PROJECTION_ZIFAART );
/*  printf("%s\n", sql );  */

    s = SqlDeclareCs( &fd_zifa_zifaart, sql, "ZIFAART.A00PZN","ZIFAART.DATUMGUELTIGAB", NULL );
    if ( s != 0 )
    {
      fd_zifa_zifaart = -1;
      sprintf( errmld, "ZIFAART: %s", DynErrmld() );
    }
    return s;
}

static long Zifa_zifaart_Read( struct ZIFAART *zifaart, long pzn, long datumgueltigab, char *errmld )
{
    long s;

    s = SqlReadDeclCs( fd_zifa_zifaart,
                       zifaart, NULL,
                       &pzn, &datumgueltigab,NULL );
    if ( s != 0 )
      sprintf( errmld, "ZIFAART: %s", DynErrmld() );
    return s;
}

static long Zifa_zifaart_CloseCs( char *errmld )
{
    long s;
    if ( fd_zifa_zifaart == -1 ) return 0;
    s = SqlCloseCs( fd_zifa_zifaart );
    if ( s != 0 && errmld != NULL )
       sprintf( errmld, "ZIFAART: %s", DynErrmld() );
    fd_zifa_zifaart = -1;
    return s;
}



/* -------------------------------------------------------------- *
 *        Aenderungsschleife                                      *
 * -------------------------------------------------------------- */


static long StartWork( char *errmld )
  {
    long s;
    s = SqlBeginWork( );
    if ( s != 0 )
      {
        strcpy( errmld, "IFA uebertragen: " );
        strcat( errmld, DynErrmld() );
       }
    return s;
   }

static long EndWork( long status, char *errmld )
  {
    long s;
    if ( status == 0 )
      {
        s = SqlCommitWork( );
        if ( s != 0 )
          {
            strcpy( errmld, "IFA uebertragen: " );
            strcat( errmld, DynErrmld() );
           }
        return s;
       }
     else
      {
        s = SqlRollbackWork( );
        return status;
       }
   }

static long Open_All( long ifanr, char *cErrmld )
{
    if ( GetBufferDesc_Zartikel     ( cErrmld ) != 0 ) return -1;
    if ( GetBufferDesc_Zean         ( cErrmld ) != 0 ) return -1;
    if ( GetBufferDesc_Artve        ( cErrmld ) != 0 ) return -1;
    if ( GetBufferDesc_Zpreis       ( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_CArtPriceExt ( cErrmld ) != 0 ) return -1;
    if ( GetBufferDesc_Zartwg       ( cErrmld ) != 0 ) return -1;
    if ( GetBufferDesc_Zapflege     ( cErrmld ) != 0 ) return -1;
    if ( GetBufferDesc_Zpznpflege   ( cErrmld ) != 0 ) return -1;
    if ( GetBufferDesc_Zaneuheit    ( cErrmld ) != 0 ) return -1;
    if ( GetBufferDesc_Zlifestyle   ( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_CArticleCodes( cErrmld ) != 0 ) return -1;
    if ( Zifa_PZNNF_Declare  ( ifanr, cErrmld ) != 0 ) return -1;
    if ( Zifa_zifaart_Declare  (  cErrmld ) != 0 ) return -1;

    return 0;

}

static void Close_All(  )
{
   Zifa_PZNNF_CloseCs( NULL );
   Zifa_zifaart_CloseCs( NULL );
}

/* ---- testet Preisgleichheit */

static int WertVgl( double wert0, double wert1, double diff_max )
{
   double diff;
   diff = wert0 - wert1;	
   KaufmRunden( &diff, 2 );
   if ( diff >  diff_max ) return  1;
   if ( diff < -diff_max ) return -1;
   return 0;
}

/* ---- Generiert Preis , wenn Hersteller-Prozent */

static void MakePreisAusHerstProz( double herst_proz,
                                   double *grosso, double *aep )
{
   double wert;
   if ( herst_proz >= 0.005 )
   {
     if ( *aep < 0.005 )
     {
        wert = (*grosso)*herst_proz/100.0;
        KaufmRunden( &wert, 2);
        *aep = (*grosso) + wert;
     }
   }
   else if ( herst_proz <= -0.005 )
   {
  /* so wird in PHARMOS gerundet */
     if ( (*grosso) < 0.005 ||
		  WertVgl( *grosso, *aep, 0.005 ) == 0 ) // auch wenn grosso == aep
     {
        wert = (*aep)*herst_proz/100.0;
        *grosso = (*aep) + wert;
        KaufmRunden( grosso, 2);
     }
   }
}


/* ---- testet Preisgleichheit */

static int WertGleich( double wert0, double wert1 )
{
   double diff;
   diff = wert0 - wert1;
   KaufmRunden( &diff, 2 );
   if ( diff >= -0.005 && diff <= 0.005 ) return 1;
   return 0;
}

static int IsPreisGleich( struct ZARTPREIS *Buf0, struct ZARTPREIS *Buf1 )
{
   if ( !WertGleich( Buf0->GROSSO, Buf1->GROSSO ) ) return 0;
   if ( !WertGleich( Buf0->AEP   , Buf1->AEP    ) ) return 0;
   if ( !WertGleich( Buf0->AVP   , Buf1->AVP    ) ) return 0;
   if ( !WertGleich( Buf0->EAVP  , Buf1->EAVP   ) ) return 0;
   if ( !WertGleich( Buf0->ERSTATTBETRAG, Buf1->ERSTATTBETRAG   ) ) return 0;
   if ( *Buf0->KE_MWST != *Buf1->KE_MWST ) return 0;
   if ( Buf0->DISC_DEDUCED_YET != Buf1->DISC_DEDUCED_YET ) return 0;
   return 1;
}

static int IsArtPriceExtGleich( struct CARTPRICEEXT *Buf0, struct CARTPRICEEXT *Buf1 )
{
	if ( !WertGleich( Buf0->A01AEPPPU	, Buf1->A01AEPPPU ) )		return 0;
	if ( !WertGleich( Buf0->A01APU783A  , Buf1->A01APU783A    ) )	return 0;
	if ( !WertGleich( Buf0->A01AVPPPU   , Buf1->A01AVPPPU    ) )	return 0;
	if ( !WertGleich( Buf0->A01PPU		, Buf1->A01PPU   ) )		return 0;
   return 1;
}

static int IsArtPriceExtNull( struct CARTPRICEEXT *Buf0 )
{
	if ( !WertGleich( Buf0->A01AEPPPU	, 0 ) )	return 0;
	if ( !WertGleich( Buf0->A01APU783A  , 0 ) )	return 0;
	if ( !WertGleich( Buf0->A01AVPPPU   , 0 ) )	return 0;
	if ( !WertGleich( Buf0->A01PPU		, 0 ) )	return 0;
   return 1;
}

void Make_Preissenkung(struct ZIFAART* IfaBufZukunft , struct ZIFAART* IfaBufAktuell, struct ZARTIKEL* Buf )
{
	char sql[300],verguetet[2];
	int  s;
	long lGEPZukunft, lGEPAktuell,lAEPZukunft, lAEPAktuell;

	lGEPZukunft = (long)( IfaBufZukunft->GROSSO*100.0 + 0.1 );
	lAEPZukunft = (long)( IfaBufZukunft->AEP*100.0 + 0.1 );
	lGEPAktuell = (long)( IfaBufAktuell->GROSSO*100.0 + 0.1 );
	lAEPAktuell = (long)( IfaBufAktuell->AEP*100.0 + 0.1 );

	/* Preiserhöhung */    
	if ( lGEPZukunft  >  lGEPAktuell)
	{
		/* Taxprüfgrosso-Artikel */ 
		if ((strcmp( Buf->TAXPRUEFGROSSO, "1" ) == 0) &&
			( lAEPZukunft  <= lAEPAktuell ) ) 
				return ; // ifa.AEP <= AEP &&  --> keine Preiserhöhung

		strcpy(Buf->PREISSENKUNG,"9");   
		return;
	}
	/* Ende Preiserhöhung */    	

	/* Preissenkung */    

	/* Taxprüfgrosso-Artikel */ 
	if ((strcmp( Buf->TAXPRUEFGROSSO, "1" ) == 0) &&
		( lAEPZukunft  >= lAEPAktuell ) ) 
			return ; // ifa.AEP >= AEP &&  --> keine Preissenkung

    sprintf( sql, "select herstell_verguetet from herstel where hersteller_nr=%ld",
		          Buf->HERSTELLER_NR );
	s = SqlRead( sql, &verguetet, NULL );

	if ( verguetet[0] == 'N' )
		strcpy(Buf->PREISSENKUNG,"1");   
	else if ( verguetet[0] == 'J' )
		strcpy(Buf->PREISSENKUNG,"2");   
	else if ( verguetet[0] == 'B' )
		strcpy(Buf->PREISSENKUNG,"4");   
	else /*  if ( s_Herstel.HERSTELL_VERGUETET[0] == '0' ) */
		strcpy(Buf->PREISSENKUNG,"5");   

	return;
	/* Ende Preissenkung */    		
}

/* ------------------ Puefziffer ------------------------ */

int GetPruefZiffer7 ( long zahl )
{
        int i, prziff;
        if (zahl == 0) return -1;
        prziff = 0;
        for (i=7; i>=2; i--)
        {
                zahl /= 10;
                prziff += i * ( int) ( zahl % 10 );
        }
        prziff %= 11;
        if (prziff == 10) prziff = 0;
        return prziff;
}

/*
   int TestPruefZiffer7 ( long zahl )
   Testet auf korrekte  Pruefziffer
   Eingabe-Parameter: zahl   = die zu pruefende 7-stellige Zahl
   Return-Wert      : 1 = die Zahl ist null
                      2 = die Zahl hat gueltige Pruefziffer
                      0 = die Zahl hat ungueltige Pruefziffer
*/

int TestPruefZiffer7 ( long zahl )
{
        int prziff;
        prziff = GetPruefZiffer7( zahl );
        if ( prziff == -1 )
                return 1;
        else if ( prziff == (int) ( zahl % 10 ) )
                return 2;
        else
                return 0;
}


/* ----- Alles Updaten -------------- */
static long Do_All( struct S_ZIFA *ifa, long tagesdatum, char *errmld )
{
    long s;
    long s1;
	long lRetCodeZlifestyle;
    long lRetCodeCArticleCodes;
    long artikel_nr;
    long ersatz_nr;
    int  IsIfaLoeschung;
    int  IsIfaAH;
    int  ToStorePreis;
	int  ToComparePreise;   /* autidem 20.02.2002  */
    int  ToStoreZartwg;
    int  IsArtikelVorhanden;
    long HerstellerNr_Alt;
	struct ZIFAART stZifaart;
    /* CPR-240818: Flags werden fuer das Unterbinden von zartwg - Duplikaten benoetigt */
    int  ToStoreAbdaWg = 0;
    int  ToStoreSwg1 = 0;
    int  ToStoreSwg2 = 0;
    int  ToStoreWg2 = 0;

    /* Artikel */
    artikel_nr =  ifa->A00PZN;
    s = ReadRecord_Zartikel( NR_ART, artikel_nr, errmld );
    if ( !( s == 0 || s == 100 ) ) return s;
    IsArtikelVorhanden = s == 0;

    /* Rette alte Hersteller_nr */
    if ( IsArtikelVorhanden )
       HerstellerNr_Alt = Buf_zartikel[NR_ART].HERSTELLER_NR;
     else
       HerstellerNr_Alt = -1;

    /* ---- IFA-Loeschung ---- */
    IsIfaLoeschung = GetIsIfaLoeschung( ifa );

    /* ---- bei IFA-Loeschung und fehlendem Artikel ---- */
    /* ---- Artikel nicht mehr neu aufnehmen        ---- */
    if ( IsIfaLoeschung && !IsArtikelVorhanden ) return 0;

    /* ---- IFA-AH ---- */
    IsIfaAH = GetIsIfaAH( ifa );

    ToStoreZartwg = 0;
    ersatz_nr = 0;

    if ( IsIfaLoeschung  )
    {
      /* ---- nur Loeschdatum eintragen ---- */
      Buf_zartikel[NR_ART].DATUM_IFALOESCH = ifa->DATUMGUELTIGAB;
    }
    else
    {
	  /* ----- Ifa-Werte nach Artikelsatz ----- */
      IfaSatzToArtikel( ifa, &Buf_zartikel[NR_ART], IsArtikelVorhanden,
                        &ToStoreAbdaWg, &ToStoreSwg1, &ToStoreSwg2, &ToStoreWg2);

	  if (ToStoreAbdaWg > 0)
	  {
			ReadRecord_Zartwg(WG_ABDA, artikel_nr, errmld);

            /* ----------- IFA Version 20244 ---------- */
            /* Abh. von ToStoreAbdaWg anderen Wert in die Warengruppe schreiben */
            if (ToStoreAbdaWg == 1)
            {
                strcpy(Buf_zartwg.WARENGRUPPE, "BATT");
            }
            else if (ToStoreAbdaWg == 2)
            {
                strcpy(Buf_zartwg.WARENGRUPPE, "PFLSP");
            }
            else if (ToStoreAbdaWg == 3)
            {
                strcpy(Buf_zartwg.WARENGRUPPE, "SPNOV");
            }
            else if (ToStoreAbdaWg == 4)
            {
                strcpy(Buf_zartwg.WARENGRUPPE, "SDBSP");
            }
            else if (ToStoreAbdaWg == 5)
            {
                strcpy(Buf_zartwg.WARENGRUPPE, "BIOZ");
            }
            else if (ToStoreAbdaWg == 6)
            {
                strcpy(Buf_zartwg.WARENGRUPPE, "VDINT");
            }

            StoreRecord_Zartwg(errmld);
	  }

      if (ToStoreSwg1 > 0)
      {
          ReadRecord_Zartwg(WG_SAISON, artikel_nr, errmld);

          if (ToStoreSwg1 == 1)
          {
              strcpy(Buf_zartwg.WARENGRUPPE, "KL");
          }
          else if (ToStoreSwg1 == 2)
          {
              strcpy(Buf_zartwg.WARENGRUPPE, "KK");
          }
          else if (ToStoreSwg1 == 3)
          {
              strcpy(Buf_zartwg.WARENGRUPPE, "K8");
          }

          StoreRecord_Zartwg(errmld);
      }

      if (ToStoreSwg2 > 0)
      {
          ReadRecord_Zartwg(WG_SAISON2, artikel_nr, errmld);

          if (ToStoreSwg2 == 1)
          {
              strcpy(Buf_zartwg.WARENGRUPPE, "BI");
          }

          StoreRecord_Zartwg(errmld);
      }

      if (ToStoreWg2 > 0)
      {
          ReadRecord_Zartwg(WG_DKART, artikel_nr, errmld);

          if (ToStoreWg2 == 1)
          {
              strcpy(Buf_zartwg.WARENGRUPPE, "01040");
          }

          StoreRecord_Zartwg(errmld);
      }

      /* neu ab 09.03.2004 */
	  /* AUTIDEMARTIKEL durch FESTBETRARTIKEL ersetzen */
      if ( IsArtikelVorhanden )
	  {
		  // if ( *Buf_zartikel[NR_ART].FESTBETRARTIKEL == '1' )
		  if ( Buf_zartikel[NR_ART].FESTBETRAG1 > 0 )
			   *Buf_zartikel[NR_ART].PREISSENKUNG = '3';
		  else
			   *Buf_zartikel[NR_ART].PREISSENKUNG = '0'; 

		  /* neu ab 10.04.07 Setzen Datum Preissenkung */
		  if (ifa->DATUMGUELTIGAB == Buf_zartikel[NR_ART].DATUM_PREISSENKUNG)
			  Buf_zartikel[NR_ART].DATUM_PREISSENKUNG = 0;
		  
		  if (ifa->DATUMGUELTIGAB < Buf_zartikel[NR_ART].DATUM_PREISSENKUNG)
		  {
			 s = Zifa_zifaart_Read( &stZifaart, ifa->A00PZN, Buf_zartikel[NR_ART].DATUM_PREISSENKUNG ,errmld );
			 if ( 0 == s)	
			 {	 /* Preisaenderung GEP */
				 if ( 0  == WertGleich(ifa->GROSSO,stZifaart.GROSSO))
					 Make_Preissenkung(&stZifaart,ifa,&Buf_zartikel[NR_ART]);
			 }
		  }

	  }
    }

    /* bei Neuanlage nachschauen, ob ein Artikel in ZIFAART existiert */
    /* mit A06PZNNF = artikel_nr */
    /* wenn ja, dann im Artikelstamm nach diesem Artikel */
    /* schauen, und gegebenenfalls dessen Historie uebernehmen */
    if ( !IsArtikelVorhanden )
    {
       long ersatz_pzn;

	   /* IFA-Satz unvollstaendig */
	   /* tritt nur auf, wenn ArtikelSatz geloescht wurde  */
       if ( IsAnyNoValue( ifa ) ) return NOVALUE_ERROR;


       s = Zifa_PZNNF_Read( &ersatz_pzn, ifa->A00PZN, errmld );
       if ( !( s == 0 || s == 100 ) ) return s;

       if ( s == 0 )
       {
          ersatz_nr =  ersatz_pzn;
          s = ReadRecord_Zartikel( NR_ERS, ersatz_nr, errmld );
          if ( !( s == 0 || s == 100 ) ) return s;

          if ( s == 0 )
          {
             ToStoreZartwg = 1;   /* Historie Warengruppen uebernehmen */

             *Buf_zartikel[NR_ART].PRODUKTART =
                 *Buf_zartikel[NR_ERS].PRODUKTART;
             *Buf_zartikel[NR_ART].ZYTOSTATIKA =
                 *Buf_zartikel[NR_ERS].ZYTOSTATIKA;

             Buf_zartikel[NR_ART].HERST_PROZENT =
                 Buf_zartikel[NR_ERS].HERST_PROZENT;
             *Buf_zartikel[NR_ART].TIERARZNEI =
                *Buf_zartikel[NR_ERS].TIERARZNEI;
             *Buf_zartikel[NR_ART].MELDEPFL =
                *Buf_zartikel[NR_ERS].MELDEPFL;
          }
       }
	   else if ( ifa->A06PZNORIG > 0 )
	   {
		  	/* bei Neuanlage von Reimporten (A06PZNORIG > 0) nachschauen, ob ein Artikel */
			/* im Artikelstamm mit artikel_nr = A06PZNORIG existiert */
			/* und gegebenenfalls dessen Historie uebernehmen */

		  ersatz_nr =  ifa->A06PZNORIG;
          s = ReadRecord_Zartikel( NR_ERS, ersatz_nr, errmld );
          
		  if ( !( s == 0 || s == 100 ) ) 
			  return s;

		  strcpy(Buf_zartikel[NR_ART].PRODUKTART, "3"); // reimport

		  if ( s == 0 )
          {
             ToStoreZartwg = 2;   /* Historie Warengruppen uebernehmen */
			 
			 *Buf_zartikel[NR_ART].ZYTOSTATIKA =
                 *Buf_zartikel[NR_ERS].ZYTOSTATIKA;
          }
	   }
    }

	/* ----- zentralppelist 17.07.2003 ----------------- */
	/* ----- nur wenn kein Betaeubungsmittel 15.03.2004 ----- */
	/* ----- nur wenn nicht Kuehlkettet oder unter 8 Grad 5.05.2004 ----- */
    if ( !IsIfaLoeschung && *Buf_zartikel[NR_ART].BTM == '0' &&
		 !( *Buf_zartikel[NR_ART].KUEHLARTIKEL == '4' || *Buf_zartikel[NR_ART].KUEHLARTIKEL == '1' ) )
	{
	   /* prototype */
	   long LeseZentralppelist( long hersteller_nr, char *zentralppelist, char *errmld );

	   if ( !IsArtikelVorhanden || 
		     Buf_zartikel[NR_ART].HERSTELLER_NR  != HerstellerNr_Alt && 
		    *Buf_zartikel[NR_ART].ZENTRALPPELIST != '8' )
	   {
			s = LeseZentralppelist( Buf_zartikel[NR_ART].HERSTELLER_NR,
	                                Buf_zartikel[NR_ART].ZENTRALPPELIST, errmld );
		
	        if ( !( s == 0 || s == 100 ) ) return s;
	   }
	}

	/* ----- setzen zartikel.ekoriginalhs / .bestell_nur_ozek für Sortimente ----- */
	if ( !IsIfaLoeschung && 
		 ( !IsArtikelVorhanden || Buf_zartikel[NR_ART].HERSTELLER_NR  != HerstellerNr_Alt ) )
	{
		/* prototype */
	   long LeseHerstelSortimente( long hersteller_nr, char *ekoriginalhs, char *bestell_nur_ozek, 
						char *rezeptpfl, char *apothekenpfl, char *nettoartikel, short *bezugssperre, char *errmld );

		char  ekoriginalhs[2];
		char  bestell_nur_ozek[2];
		char  rezeptpfl[2];
		char  apothekenpfl[2];
		char  nettoartikel[2];
		short bezugssperre;

		s = LeseHerstelSortimente( Buf_zartikel[NR_ART].HERSTELLER_NR,
	                                ekoriginalhs, bestell_nur_ozek,
									rezeptpfl, apothekenpfl, nettoartikel, &bezugssperre, errmld );

		if ( !( s == 0 || s == 100 ) ) 
			return s;

		if ( (Buf_zartikel[NR_ART].REZEPTPFL[0]		==  rezeptpfl[0]	&& rezeptpfl[0]		== '1' ) ||
			 (Buf_zartikel[NR_ART].APOTHEKENPFL[0]	==  apothekenpfl[0]	&& apothekenpfl[0]	== '1' ) ||
			 (Buf_zartikel[NR_ART].NETTOARTIKEL[0]	==  nettoartikel[0]	&& nettoartikel[0]	== '1' )	)
		{
			if (ekoriginalhs[0] == '1')
				*Buf_zartikel[NR_ART].EKORIGINALHS = '1';
			//else
			//	*Buf_zartikel[NR_ART].EKORIGINALHS = '0';

			if (bestell_nur_ozek[0] == '1')
				*Buf_zartikel[NR_ART].BESTELL_NUR_OZEK = '1';
			//else
			//	*Buf_zartikel[NR_ART].BESTELL_NUR_OZEK = '0';

			if (bezugssperre > 0)
				Buf_zartikel[NR_ART].BEZUGSSPERRE = bezugssperre;
		}		
		/*else
		{
			*Buf_zartikel[NR_ART].EKORIGINALHS = '0';
			*Buf_zartikel[NR_ART].BESTELL_NUR_OZEK = '0';
		}*/
	}
	
	/* ----- CR-267: Übernahme herstel.konsig_partner_nr nach zartikel.konsig_partner_nr bei Artikel- Neuanlagen ----- */
	if ( !IsIfaLoeschung && !IsArtikelVorhanden )
	{
		char sql[300];
		short vertr_club = 0;

		sprintf( sql, "select konsig_partner_nr, vertriebsclubnr from herstel where hersteller_nr=%ld",
						Buf_zartikel[NR_ART].HERSTELLER_NR );

		s = SqlRead( sql, &Buf_zartikel[NR_ART].KONSIG_PARTNER_NR, &vertr_club, NULL );

		if (vertr_club > 0)
		{
			ReadRecord_Zartwg(WG_VERTRCL, artikel_nr, errmld);
			sprintf(Buf_zartwg.WARENGRUPPE, "%05d", vertr_club); 
			StoreRecord_Zartwg(errmld);	
		}
	}

   /* Chargenartikel automatisch umsetzen */
	if ( *Buf_zartikel[NR_ART].TIERARZNEI == '1' ||
		 *Buf_zartikel[NR_ART].TFG == '1' ||
		 *Buf_zartikel[NR_ART].TFG == '2')
		memcpy( Buf_zartikel[NR_ART].CHARGENARTIKEL, "1", L_ZARTIKEL_CHARGENARTIKEL );
	/* das Chargen- KZ darf mit FMD / BatchTracking nicht mehr automatisch zurückgesetzt werden!
	else
		memcpy( Buf_zartikel[NR_ART].CHARGENARTIKEL, "0", L_ZARTIKEL_CHARGENARTIKEL );
	*/

    /* ----- Zartikel speichern ----- */
    s = StoreRecord_Zartikel( NR_ART, errmld );
    if ( s != 0 ) 
		return s;

	/* ----- gegebenenfalls Historie Warengruppen uebernehmen ----- */
    if ( ToStoreZartwg > 0 )
    {
		if (ToStoreWg2 == 0)   /* CPR-240818: Nur einfuegen, wenn noch nicht oben passiert */
	    {
		   s = Copy_Zartwg(WG_DKART, artikel_nr, ersatz_nr, errmld);
		   if (!(s == 0 || s == 100)) return s;
	    }

	    s = Copy_Zartwg( WG_WIRKST, artikel_nr, ersatz_nr, errmld );
        if ( !( s == 0 || s == 100 ) ) return s;	   
       
	    if ( ToStoreZartwg == 1 )
	    {
            if (ToStoreSwg1 == 0)   /* CPR-240818: Nur einfuegen, wenn noch nicht oben passiert */
            {
                s = Copy_Zartwg(WG_SAISON, artikel_nr, ersatz_nr, errmld);
                if (!(s == 0 || s == 100)) return s;
            }

            if (ToStoreSwg2 == 0)   /* CPR-240818: Nur einfuegen, wenn noch nicht oben passiert */
            {
                s = Copy_Zartwg(WG_SAISON2, artikel_nr, ersatz_nr, errmld);
                if (!(s == 0 || s == 100)) return s;
            }
	    }
    }

	if (HasEanAValue( ifa )) 
    {
		s = ReadRecord_Zean( artikel_nr, errmld );
        if ( !( s == 0 || s == 100 ) ) return s;
        if (s == 100)
        {
            // Wird wenn die EAN übernommen wird mit 0 wieder überschrieben
            Buf_zartikel[NR_ART].EAN_NICHTVORHANDEN[0] = 1;
        }
	}

	if (HasEanAValue( ifa ) && (strcmp(Buf_zean.EAN_NR,ifa->A00EAN) != 0) && (TestEanNr( ifa->A00EAN ) == 1)) {
       if ( ifa->DATUMGUELTIGAB <= tagesdatum )
			s = StoreRecord_Zpznpflege("09", artikel_nr, tagesdatum, errmld );
	   else
			s = StoreRecord_Zpznpflege("09", artikel_nr,ifa->DATUMGUELTIGAB,errmld );
	   if ( s != 0 ) return s;
   }

	if (!IsNoValue( ifa, PL_A00NTIN ))
	{
		lRetCodeCArticleCodes = ReadRecord_CArticleCodes( CODETYPE_NTIN, artikel_nr, errmld );
        if ( !( lRetCodeCArticleCodes == 0 || lRetCodeCArticleCodes == 100 ) ) 
			return lRetCodeCArticleCodes;

		if ((strncmp(Buf_CArticleCodes.ARTICLE_CODE,ifa->A00NTIN, L_ZIFAART_A00NTIN) != 0) && (TestEanNr( ifa->A00NTIN ) == 1) && IsArtikelVorhanden) // Für Neuanlagen wird später die Satzart "34" geschrieben für code_type 11
		{
			if ( ifa->DATUMGUELTIGAB <= tagesdatum )
				s = StoreRecord_Zpznpflege("34", artikel_nr, tagesdatum, errmld );
			else
				s = StoreRecord_Zpznpflege("34", artikel_nr,ifa->DATUMGUELTIGAB,errmld );
	   
			if ( s != 0 ) return s;
		}
	}


    if ( !IsIfaLoeschung  )
    {
      /* ---- Ean ---- */
      if ( !IsIfaAH )
      {
        // EAN Änderungen sollen nur übernommen werden wenn der Artikel nicht Außerhandel ist
        // Und die Änderung der EAN zu keinem duplicate key error führt
        if ( HasEanAValue( ifa ) && TestEanNr( ifa->A00EAN ) == 1   )
        {
           if (ifa->NB_NZWING[NZ_EAN_DUPL_IGNORED] == '0' &&
               ifa->NB_ZWING[ZW_EAN_MEHRFACH] == '0')
           {
           Buf_zean.ARTIKEL_NR = artikel_nr;

		   strcpy( Buf_zean.EAN_NR, ifa->A00EAN );
               // Mann kann nicht erst einfügen den Duplicate Key Error fangen und dann versuche neu einzufügen
               // Mann muss erst prüfen ob die EAN bereits bei einem anderen Artikel verwendet wird
               // unabhängig davon ob eine EAN geändert oder neu eingefügt werden soll.
               int s1 = ReadRecord_Zean2(Buf_zean.EAN_NR, errmld);
               if (s1 == 0)
               {
                   // Es gibt einen Eintrag mit der aktuellen EAN
                   // Wen der aktuelle Eintrag zu einem gesperrten Artikel gehört, wird die neue EAN nicht gespeichert
                   // weil dieses Speichern dann zu einem Duplikat führen würde
                   if (Buf_zartikel[NR_ART].ARTIKEL_GESPERRT[0] != '1')
                   {
                       // Da der Artikel nicht gesperrt ist, ist evtl. der Artikel gesperrt bei dem die EAN aktuell gesetzt ist
                       int s2 = ReadRecord_Zartikel(NR_EAN, BufEan_zean.ARTIKEL_NR, errmld);
                       if (s2 == 0)
                       {
                           if (Buf_zartikel[NR_EAN].ARTIKEL_NR != Buf_zartikel[NR_ART].ARTIKEL_NR)
                           {
                               if (Buf_zartikel[NR_EAN].ARTIKEL_GESPERRT[0] == '1')
                               {
                                   // Die EAN des gesperrten Artikels kann gelöscht werden und die EAN damit für den nicht
                                   // gesperrten Artikel freigegeben werden
                                   int s3 = DeleteRecord_Zean(Buf_zartikel[NR_EAN].ARTIKEL_NR, errmld);
                                   if (s3 == 0)
                                   {
                                       s = StoreRecord_Zean(errmld);
                                       Buf_zartikel[NR_ART].EAN_NICHTVORHANDEN[0] = '0';
                                       Buf_zartikel[NR_EAN].EAN_NICHTVORHANDEN[0] = '2';
                                       int s4 = StoreRecord_Zartikel(NR_EAN, errmld);
                                       if (s4 == 0)
                                       {
                                           // EAN übernommen
                                       }
                                   }
                               }
                               else
                               {
                                   if (lStatus_Zean == 0)
                                   {
                                       // EAN kann wegen Duplikat nicht übernommen werden
                                       Buf_zartikel[NR_ART].EAN_NICHTVORHANDEN[0] = '2';
                                   }
                                   // Artikel hat eine EAN, die Änderung wird ignoriert
                               }
                           }
                           else
                           {
                               // Die Änderung der EAN eines bestehenden Artikels kann zu keinem 
                               // Duplikat führen
                               s = StoreRecord_Zean(errmld);
                           }
                       }
                   }
                   else
                   {
                       // EAN Änderung wird aufgrund von Duplikat nicht übernommen
                       Buf_zartikel[NR_ART].EAN_NICHTVORHANDEN[0] = '2';
                   }
               }
               else if (s1 == 100)
               {
                   // Es gibt die EAN in der EAN Tabelle noch nicht
           s = StoreRecord_Zean( errmld );
                   Buf_zartikel[NR_ART].EAN_NICHTVORHANDEN[0] = '0';
               }
           }
           else
           {
               // EAN wird wegen doppelten Werten in IFA nicht übernommen
               // Artikel verfügt bereits über eine EAN
               Buf_zartikel[NR_ART].EAN_NICHTVORHANDEN[0] = '2';
           }
           if ( s != 0 ) return s;
        }

		if (!IsNoValue( ifa, PL_A00NTIN ) && (TestEanNr( ifa->A00NTIN ) == 1))
		{
			Buf_CArticleCodes.DATE_CHANGED = tagesdatum;
			strncpy(Buf_CArticleCodes.ARTICLE_CODE, ifa->A00NTIN, L_CARTICLECODES_ARTICLE_CODE);
			Buf_CArticleCodes.SERIAL_NUMBER = 1;

			if (lRetCodeCArticleCodes == 0)
			{
				//update carticlecodes
				s = UpdateRecord_CArticleCodes( errmld);
			}
			else if (lRetCodeCArticleCodes == 100)
			{
				//insert carticlecodes
				s = InsertRecord_CArticleCodes( errmld);
			}

			if ( s != 0 ) return s;
		}
	  }

      if (!IsNoValue(ifa, PL_A00GTIN))
      {
        /* CPR-220839 GTIN14 als neuen Wert in CARTICLECODES speichern wenn > 0*/
          long gtin = atol(ifa->A00GTIN);
          if (gtin > 0)
          {
              lRetCodeCArticleCodes = ReadRecord_CArticleCodes(CODETYPE_GTIN14, artikel_nr, errmld);

              if (!(lRetCodeCArticleCodes == 0 || lRetCodeCArticleCodes == 100))
                  return lRetCodeCArticleCodes; // Fehler in SQL Abfrage

              Buf_CArticleCodes.DATE_CHANGED = tagesdatum;
              strncpy(Buf_CArticleCodes.ARTICLE_CODE, ifa->A00GTIN, L_CARTICLECODES_ARTICLE_CODE);
              Buf_CArticleCodes.SERIAL_NUMBER = 1;
              Buf_CArticleCodes.PREFERRED_FLAG = 0;

              // unabhängig vom bestehenden oder noch nicht bestehenden Artikel, kann die GTIN bereits existieren oder noch nicht
              // und wird grundsätzlich aktualisiert

              if (lRetCodeCArticleCodes == 100)
              {
                  s = InsertRecord_CArticleCodes(errmld);
              }
              else
              {
                  s = UpdateRecord_CArticleCodes(errmld);
              }
              if (s != 0) return s;
          }
      }

      /* ---- Preise ---- */
      s1 =  ReadRecord_ZpreisLast( 1, artikel_nr, errmld ); /* preis 1 */
      if ( !( s1 == 0 || s1 == 100 ) ) return -1;

      IfaSatzToPreis( ifa, &Buf_zpreis[0], IsArtikelVorhanden ); /* wg PrimeKey */
      s = ReadRecord_Zpreis( 0, errmld );              /* preis 0 */
      if ( !( s == 0 || s == 100 ) ) return -1;

	  ToComparePreise = 0;
      ToStorePreis = 0;
      if ( HasPreisAValue( ifa ) )
      {
         /* Ifa-Preise uebernehmen */
         IfaSatzToPreis( ifa, &Buf_zpreis[0], IsArtikelVorhanden );

         /* Hersteller-Prozent uebernehmen */
         Buf_zpreis[0].HERST_PROZENT = Buf_zartikel[NR_ART].HERST_PROZENT;
         MakePreisAusHerstProz( Buf_zpreis[0].HERST_PROZENT,
                                &Buf_zpreis[0].GROSSO,
                                &Buf_zpreis[0].AEP );

         if ( s1 == 0 )  /* alter Preis vorhanden */
         {
             // Neue Regeln nur auf Bestandslieferung anwenden
             if (ifa->A00SSATZ[0] == '0')
             {
                 // Wenn der neue Grosso 0 ist und der AEP = dem Bestands AEP
                 // dann wurde der Grosso möglicherweise manuell ermittelt und eingegeben
                 // Da der Grosso in dem Fall nicht 0 sein darf, übernehmen wir den Wert
                 // aus dem Bestand - sofern die AEP Werte sich nicht geändert haben.
                 if (Buf_zpreis[0].GROSSO <= 0.0005 &&
                     Buf_zpreis[0].AEP == Buf_zpreis[1].AEP)
                 {
                     Buf_zpreis[0].GROSSO = Buf_zpreis[1].GROSSO;
                     Buf_zpreis[0].AEP = Buf_zpreis[1].AEP;
                 }
                 // GROSSO und/oder AEP sind ohne Berechenbarkeit 0
                 // und können aber vom Bestand übernommen werden
                 else if (ifa->NB_NZWING[NZ_GROSSO_AEP_NULL_ART] == '1')
                 {
                     Buf_zpreis[0].GROSSO = Buf_zpreis[1].GROSSO;
                     Buf_zpreis[0].AEP = Buf_zpreis[1].AEP;
                 }
                 // AEP wird aus dem GROSO berechnet, kann also vom Bestand übernommen werden
                 else if (ifa->NB_NZWING[NZ_GR_EQ_AEP_CALC] == '1')
                 {
                     Buf_zpreis[0].GROSSO = Buf_zpreis[1].GROSSO;
                     Buf_zpreis[0].AEP = Buf_zpreis[1].AEP;
                 }
                 // AEP und GROSSO sind vertausch
                 else if (ifa->NB_NZWING[NZ_AEP_ART_GRO] == '1')
                 {
                     Buf_zpreis[0].GROSSO = Buf_zpreis[1].GROSSO;
                     Buf_zpreis[0].AEP = Buf_zpreis[1].AEP;
                 }
                 // Artikel außer Handel wg. Preisfehler wird kein Preis übernommen
                 else if (ifa->NB_NZWING[NZ_IFA_AH_NOPRICE] == '1')
                 {
                     Buf_zpreis[0].GROSSO = Buf_zpreis[1].GROSSO;
                     Buf_zpreis[0].AEP = Buf_zpreis[1].AEP;
                 }
             }

           if ( Buf_zpreis[0].DATUMGUELTIGAB < Buf_zpreis[1].DATUMGUELTIGAB )
                ToStorePreis = 0;   /* Preisdatum zu alt */
             else
			 {
                ToStorePreis = !IsPreisGleich( &Buf_zpreis[0], &Buf_zpreis[1] );
				ToComparePreise = ToStorePreis;
			 }
         }
         else
           ToStorePreis = 1;

         if ( ToStorePreis )
         {
             if (Buf_zpreis[0].DATUMGUELTIGAB < tagesdatum)
             {
                 Buf_zpreis[0].DATUMGUELTIGAB = tagesdatum; // Preisänderungen dürfen nicht in der Vergangenheit liegen
                 lStatus_Zpreis[0] = 100; // Datensatz muss neu eingefügt werden
             }

           s = StoreRecord_Zpreis( 0, errmld );
           if ( s != 0 ) return s;
         }
      }

	  /* ---- cartpriceext ---- */
      s1 =  ReadRecord_CArtPriceExt_Current( artikel_nr, errmld );
      
	  if ( !( s1 == 0 || s1 == 100 ) ) 
		  return -1;

      IfaSatzToArtPriceExt( ifa, &Buf_CArtPriceExt ); /* wg PrimeKey */
      s = ReadRecord_CArtPriceExt( errmld );       

      if ( !( s == 0 || s == 100 ) ) 
		  return -1;

	  ToStorePreis = 0;
      // Preisänderungen nur für nicht gesperrte Artikel übernehmen
      // Da auch nur für diese die Prüfungen in zpiartik beim Import durchgeführt wurden
      if ( HasArtPriceExtAValue( ifa ) )
      {
         /* Ifa-Preise uebernehmen */
         IfaSatzToArtPriceExt( ifa, &Buf_CArtPriceExt );

		 if ( s1 == 0 )  /* alter Preis vorhanden */
         {
           if ( Buf_CArtPriceExt.DATEVALIDFROM < Buf_CArtPriceExt_Current.DATEVALIDFROM )
                ToStorePreis = 0;   /* Preisdatum zu alt */
           else
				ToStorePreis = !IsArtPriceExtGleich( &Buf_CArtPriceExt, &Buf_CArtPriceExt_Current );
		 }
         else if ( !IsArtPriceExtNull(&Buf_CArtPriceExt) ) /* noch kein alter Preis vorhanden ==> nur neue PZN eintragen, wenn mind. 1 Wert > 0 */
           ToStorePreis = 1;

         if ( ToStorePreis )
         {
             if (Buf_CArtPriceExt.DATEVALIDFROM < tagesdatum)
             {
                 Buf_CArtPriceExt.DATEVALIDFROM = tagesdatum; // alte Einträge dürfen nicht geändert werden
                 lStatus_CArtPriceExt = 100; // insert neuen Eintrag erzwingen
             }

           s = StoreRecord_CArtPriceExt( errmld );
           
		   if ( s != 0 ) 
			   return s;
         }
      }

    }

	if ( !IsArtikelVorhanden && !IsIfaLoeschung && /* Neuanlage */
		 TestPruefZiffer7(artikel_nr) != 0 ) // für 8-stellige PZN´s wurde der preferred- Code (type 16) schon in zpiartik angelegt / mit Codetyp "PZN7" keine 1:1 Ersetzungen mehr anlegen, die nicht preferred sind!
	{
		FdInitTabBuf( Fd_CArticleCodes, &Buf_CArticleCodes );
		Buf_CArticleCodes.ARTICLENO = artikel_nr;
		Buf_CArticleCodes.SERIAL_NUMBER = 1;
		Buf_CArticleCodes.CODE_TYPE = 11; // Codetyp "PZN7"

		if (tagesdatum >= 20130101) 
			Buf_CArticleCodes.PREFERRED_FLAG = 0; // ab 2013 Codetyp "PZN7" nicht-preferred und nur noch übergangsweise !
		else
			Buf_CArticleCodes.PREFERRED_FLAG = 1; // bis 2013 preferred für Codetyp "PZN7" für 7-stellige PZN´s

		Buf_CArticleCodes.DATE_CHANGED = GetPhoDate();
		sprintf(Buf_CArticleCodes.ARTICLE_CODE, "%d", artikel_nr);

		sprintf( PrimekeyCond_CArticleCodes,"ARTICLENO=%7d AND SERIAL_NUMBER=1 AND CODE_TYPE=11", 
											Buf_CArticleCodes.ARTICLENO);

		s = InsertRecord_CArticleCodes( errmld );

		if ( s != 0 ) 
			return s;

		if ( ifa->DATUMGUELTIGAB <= tagesdatum )
			s = StoreRecord_Zpznpflege("34", artikel_nr, tagesdatum, errmld );
	    else
			s = StoreRecord_Zpznpflege("34", artikel_nr, ifa->DATUMGUELTIGAB, errmld );
	   
		if ( s != 0 ) 
			return s;
	}
    
    /* ---- Zapflege ---- */
    if ( ifa->DATUMGUELTIGAB <= tagesdatum )
        s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
    else
        s = StoreRecord_Zapflege( artikel_nr, ifa->DATUMGUELTIGAB, errmld );
    if ( !( s == 0 || s == 100 ) ) return s;

	/* Zlifestyle lesen */
	lRetCodeZlifestyle = ReadRecord_Zlifestyle(artikel_nr,errmld);
	if (('0' == ifa->A02LIFSTYL[1] ) && ( 0 == lRetCodeZlifestyle))
		lRetCodeZlifestyle = DeleteRecord_Zlifestyle( errmld);
	
	if ((( '1' == ifa->A02LIFSTYL[1]) || ( '2' == ifa->A02LIFSTYL[1])) && (  ifa->A02LIFSTYL[1] != Buf_Zlifestyle.LIFESTYLE[0] ))
	{
		Buf_Zlifestyle.LIFESTYLE[0] = ifa->A02LIFSTYL[1];
		Buf_Zlifestyle.LIFESTYLE[1] = '\0';
		lRetCodeZlifestyle = StoreRecord_Zlifestyle( errmld);
	}
    if ( !( lRetCodeZlifestyle == 0 || lRetCodeZlifestyle == 100 ) ) 
		return lRetCodeZlifestyle;

	/* carticlecodes (typ 7) aus Feld A02ZULREG versorgen */
	if ( !IsIfaLoeschung && !IsNoValue(ifa, PL_A02ZULREG))
	{
		lRetCodeCArticleCodes = ReadRecord_CArticleCodes(CODETYPE_ZULREG, artikel_nr,errmld);

		if ( ( lRetCodeCArticleCodes == 0 || lRetCodeCArticleCodes == 100 )  
			&& strncmp (ifa->A02ZULREG, "                         ", L_CARTICLECODES_ARTICLE_CODE) != 0 )
		{
			strncpy(Buf_CArticleCodes.ARTICLE_CODE, ifa->A02ZULREG, L_CARTICLECODES_ARTICLE_CODE);
			Buf_CArticleCodes.DATE_CHANGED = tagesdatum;
			if (lRetCodeCArticleCodes == 0)
			{
				//update carticlecodes
				lRetCodeCArticleCodes = UpdateRecord_CArticleCodes( errmld);
			}
			else if (lRetCodeCArticleCodes == 100)
			{
				//insert carticlecodes
				lRetCodeCArticleCodes = InsertRecord_CArticleCodes( errmld);
			}
		}
		else if (lRetCodeCArticleCodes == 0  && 
				strncmp (ifa->A02ZULREG, "                         ", L_CARTICLECODES_ARTICLE_CODE) == 0 )
		{
			//delete carticlecodes
			lRetCodeCArticleCodes = DeleteRecord_CArticleCodes( errmld );
		}
		
		if ( !( lRetCodeCArticleCodes == 0 || lRetCodeCArticleCodes == 100 ) ) 
			return lRetCodeCArticleCodes;
	}

	/* carticlecodes (typ 1) aus Feld A02WEEEREG versorgen */
	if ( (!IsArtikelVorhanden ||									// Neuaufnahme oder
		 (!IsIfaLoeschung && !IsNoValue(ifa, PL_A02WEEEREG))) &&	// Wertänderung
		 atoi(ifa->A02WEEEREG) > 0 )								// Code > 0
	{
		lRetCodeCArticleCodes = ReadRecord_CArticleCodes(CODETYPE_EAR, artikel_nr, errmld);

		if (lRetCodeCArticleCodes == 100) // nur eintragen, wenn noch kein code mit type=1 vorhanden ist!
		{
			sprintf( Buf_CArticleCodes.ARTICLE_CODE,"DE%s", ifa->A02WEEEREG);
			Buf_CArticleCodes.DATE_CHANGED = tagesdatum;
		
			//insert carticlecodes
			lRetCodeCArticleCodes = InsertRecord_CArticleCodes( errmld );
		}
				
		if ( lRetCodeCArticleCodes != 0 ) 
			return lRetCodeCArticleCodes;
	}
	
    /* ----- Zaneuheit ---- */
    if ( !IsArtikelVorhanden )   /* Neuheit */
    {
      /* Zaneuheit fuer PEETZ */
      s = StoreRecord_Zaneuheit( "0", &Buf_zartikel[NR_ART],
                                 tagesdatum, errmld );
      if ( !( s == 0 || s == 100 ) ) return s;

      /* Zaneuheit fuer PIERRON */
      s = StoreRecord_Zaneuheit( "1", &Buf_zartikel[NR_ART],
                                 tagesdatum, errmld );
      if ( !( s == 0 || s == 100 ) ) return s;
    }
    else if ( HerstellerNr_Alt != Buf_zartikel[NR_ART].HERSTELLER_NR )
    {
      /* Zaneuheit Herstellerwechsel fuer PIERRON */
      long SaveHerstellerNr;
      SaveHerstellerNr = Buf_zartikel[NR_ART].HERSTELLER_NR;
      Buf_zartikel[NR_ART].HERSTELLER_NR = HerstellerNr_Alt;
      s = StoreRecord_Zaneuheit( "2", &Buf_zartikel[NR_ART],
                                 tagesdatum, errmld );
      Buf_zartikel[NR_ART].HERSTELLER_NR = SaveHerstellerNr;
      if ( !( s == 0 || s == 100 ) ) return s;
    }

    /* ----- autidem 20.02.2002  ---- */
    if ( !IsIfaLoeschung && ToComparePreise )
    {
		/* Taxartikel mit Preissenkung im Grosso */
/*		if ( *Buf_zartikel[NR_ART].TAXPFL == '1' &&	 */
		if ( *Buf_zartikel[NR_ART].TAXPFL != '0' &&					
			 WertVgl( Buf_zpreis[0].GROSSO, Buf_zpreis[1].GROSSO, 0.005 ) == -1 )
		{
			s = m_Autidm_InsertRecord(  artikel_nr, Buf_zpreis[0].DATUMGUELTIGAB, 
									    Buf_zpreis[1].GROSSO, Buf_zpreis[1].AEP,
									    Buf_zpreis[0].GROSSO, Buf_zpreis[0].AEP, 
									    Buf_zartikel[NR_ART].HERSTELLER_NR, ifa->IFANR, errmld ); 
			if ( !( s == 0 || s == 100 ) ) return -1;  /* return s; */
		}
	}

    /* ----- spannenkuerzung 20.02.2002  ---- */
    if ( !IsIfaLoeschung && ToComparePreise )
    {
		/* nur bei Nicht-Taxartikel */
/*		if ( *Buf_zartikel[NR_ART].TAXPFL != '1' &&	 */	
		if ( *Buf_zartikel[NR_ART].TAXPFL == '0' &&	
			 Buf_zpreis[0].AEP > 0.005 && Buf_zpreis[1].AEP > 0.005 )
		{
			double spanne_neu;
			double spanne_alt;
			double kuerzung;
			double kuerzung_rel;

			spanne_neu = 100 * ( Buf_zpreis[0].AEP - Buf_zpreis[0].GROSSO ) / Buf_zpreis[0].AEP;
	        KaufmRunden( &spanne_neu, 2);   /* gerundet auf 2 Stellen */
			spanne_alt = 100 * ( Buf_zpreis[1].AEP - Buf_zpreis[1].GROSSO ) / Buf_zpreis[1].AEP;
			KaufmRunden( &spanne_alt, 2);   /* gerundet auf 2 Stellen */
			/* Kuerzung wenn */
			/* spanne_alt > spanne_neu */
			if ( spanne_neu > -9999.99 && spanne_alt > -9999.99  &&
			     WertVgl( spanne_alt, spanne_neu, 0.005 ) == 1  )
			{
				kuerzung = spanne_alt - spanne_neu;
				KaufmRunden( &kuerzung, 2);
				if ( WertVgl( spanne_alt, 0.0, 0.005 ) != 0 )     /* spanne_alt != 0 */
				{
					kuerzung_rel = 100 * kuerzung / spanne_alt;
					KaufmRunden( &kuerzung_rel, 2);
				}
				else
					kuerzung_rel = -999.99;

				if ( kuerzung_rel < -999.99 )
					kuerzung_rel = -999.99;
				else if ( kuerzung_rel > 999.99 )
					kuerzung_rel = 999.99;

				s = m_Spankuerz_InsertRecord(  artikel_nr, Buf_zpreis[0].DATUMGUELTIGAB, 
							 			       Buf_zpreis[1].GROSSO, Buf_zpreis[1].AEP, spanne_alt,
										       Buf_zpreis[0].GROSSO, Buf_zpreis[0].AEP, spanne_neu,
											   kuerzung, kuerzung_rel,
										       Buf_zartikel[NR_ART].HERSTELLER_NR, tagesdatum,
											   errmld ); 

				if ( !( s == 0 || s == 100 ) ) return -1;  /* return s; */
			}
		}
	}

	if ( ifa->A06PZNORIG8 > 0 )  // CPR-240818
	{
		s = ReadRecord_Artve( artikel_nr, errmld );

		if ( !( s == 0 || s == 100 ) )
		{
			return -1;
		}

		InitArtveFields( &Buf_Artve );

		if ( (s = StoreRecord_Artve( errmld )) != 0 )
		{
			return -1;
		}
	}

    /* ----- Ausfuehren ----- */
    s = FdTransactWithoutWork( errmld );

    if ( s != 0 )
    {
       long s_dirty;
       s_dirty = Dirty_Error();
       if ( s_dirty == SQL_DOUBLE_ROW || s_dirty == SQL_DOUBLE_INDEX )
       {
          sprintf( errmld, "Doppelte EAN-Nr %s bei Artikel %ld",
                   Buf_zean.EAN_NR,
                   Buf_zean.ARTIKEL_NR );
/*        printf ( "%s\n", errmld );  */
          return s_dirty;
       }
       else
       {
         char errstr[50];
         sprintf( errstr, "\nArtikel-Nr = %ld / PZN = %ld\n",
                  Buf_zartikel[NR_ART].ARTIKEL_NR, ifa->A00PZN8 );
         strcat( errmld, errstr );
       }
      return s;
    }

/*
    printf( "%ld %s %s %s\n",
            Buf_zartikel[NR_ART].ARTIKEL_NR,
            Buf_zartikel[NR_ART].ARTIKEL_NAME,
            Buf_zartikel[NR_ART].EINHEIT,
            Buf_zartikel[NR_ART].DARREICHFORM   );
*/

    /* --- Protokoll --- */

#if defined (MSDOS) || defined (WIN32)
	/* Kein Protokoll */
#else
	if ( !IsArtikelVorhanden )   
       s = ifa_ProtokolNeu( &Buf_zartikel[NR_ART], &Buf_zpreis[0], errmld, ifa->A00PZN8 );
    else
    {
      if ( !IsIfaLoeschung )
      {
         char lagerung;
         char verfall;
         char vertrbind;
         int  ToStoreSwg1;
         lagerung  = Build_KUEHLARTIKEL( ifa, IsArtikelVorhanden, &ToStoreSwg1 );
         verfall   = Build_VERFALL( ifa );
         vertrbind = Build_VERTRBIND_IFA( ifa );

         s = ifa_ProtokolAen( &BufOld_zartikel[NR_ART], &Buf_zpreis[1],
                              &Buf_zartikel[NR_ART],    &Buf_zpreis[0],
                              lagerung, verfall, vertrbind,
                              errmld, ifa->A00PZN8 );
       }
       else
         s = ifa_ProtokolLoe( &BufOld_zartikel[NR_ART], errmld, ifa->A00PZN8 );
    }
#endif
    return s;
}

static long Transfer_Loop( long ifanr, long datum, char *ProtokolVerzeichnis,
                           char *errmld )
{
    long s;
    long s1;
    long sdbl;
	long sval;
    long anz_ueb;
    long anz_loe;
    long anz_dbl;
    long anz_notrans;

    struct S_ZIFA ifa = {};

    s = Zifa_Fetch( &ifa, errmld );
    if ( s == 100 )
       strcpy( errmld, "Keine IFA-Saetze zum Uebertragen vorhanden" );
    if ( s != 0 ) return s;

    if ( ifa_OpenProtokol( ifanr, ProtokolVerzeichnis, errmld ) != 0 )
    {
       return -1;
    }

    anz_ueb = 0;
    anz_loe = 0;
    anz_dbl = 0;
    anz_notrans = 0;

    s1 = 0;
    while ( s == 0 && s1 == 0 )
    {
      s1 = StartWork( errmld );
      if ( s1 == 0 )
      {
        s1 = NOTRANS_ERROR;
        if ( *ifa.IFASTATUS == IFASTATUS_FREIGEGEBEN && *ifa.NBSTATUS <= '1' )
             s1 = Do_All( &ifa, datum, errmld );

		sval = 0;
		if ( s1 == NOVALUE_ERROR )
		{
		   sval = s1;
           s1 = 0;
		}

        sdbl = 0;
        if ( s1 == SQL_DOUBLE_ROW || s1 == SQL_DOUBLE_INDEX ) sdbl = s1;

        if ( s1 == 0 )
           s1 = Zifa_ExecuteDelete( &ifa, errmld );  /* Ifasatz Loeschen */


        s1 = EndWork( s1, errmld );

        if ( sdbl == SQL_DOUBLE_ROW || sdbl == SQL_DOUBLE_INDEX ) s1 = 0;

        if ( s1 == 0 )
        {

          if ( sdbl != 0 )
            anz_dbl++;
		  else if ( sval != 0 )
            anz_loe++;
          else if ( *ifa.IFASTATUS == IFASTATUS_FREIGEGEBEN &&
                    *ifa.NBSTATUS <= '1' )
            anz_ueb++;
          else
            anz_loe++;

          s = Zifa_Fetch( &ifa, errmld );
        }
        else if (s1 == NOTRANS_ERROR)
        {
            // Datensatz nur überspringen nicht löschen, verbleibt in IFA für weiteren Transferversuch
            anz_notrans++;
            s = Zifa_Fetch(&ifa, errmld);
            s1 = 0; // zurücksetzen
        }
      }
    }

    ifa_CloseProtokol( s1 == 0 && s == 100, errmld );

    if ( s1 != 0 )  return s1;
    if ( s == 100 )
    {
      if ( anz_dbl == 0 )
         sprintf( errmld,
                  "%ld  IFA-Saetze uebertragen\n" \
                  "%ld  IFA-Saetze geloescht\n" \
                  "%ld  IFA-Saetze wegen Fehler übersprungen\n ",
                  anz_ueb,
                  anz_loe,
                  anz_notrans);
      else
        sprintf( errmld,
                 "%ld  IFA-Saetze uebertragen\n"    \
                 "%ld  IFA-Saetze geloescht\n"      \
                 "%ld  IFA-Saetze noch vorhanden\n" \
                 "%ld  IFA-Saetze wegen Fehler übersprung\n",
                 anz_ueb,
                 anz_loe,
                 anz_dbl,
                 anz_notrans);
      return 0;
    }

    return s;
}

static long Select_Loop( long ifanr, long datum, char mode,
                         char *ProtokolVerzeichnis, char *errmld )
{
    long s;
    s = Zifa_Select( ifanr, datum, mode, errmld );
    if ( s == 0 )
    {
       s = Zifa_PrepDelete( errmld );
       if ( s == 0 )
       {
         s = Open_All( ifanr, errmld );
         if ( s == 0 )
         {
            s = Transfer_Loop( ifanr, datum, ProtokolVerzeichnis, errmld );

			/* ------ BSsichG: BeitragsSatzSicherungsGesetz 18.12.2002 */
			/* bssichg: 23.12.2003 entfaellt wieder, da neues Gesetz */
			/*
			CloseImsWgr( );
			*/
			CloseHerstel( );  /* ------ rd_herst: Hersteller lesen 17.07.2003 */
            Close_All();
         }
         Zifa_FreeDelete( NULL );
       }
       Zifa_CloseCs( NULL );
    }
    return s;
}

long GenArtLoop( char *db, char *param1, char *param2, char *param3, char *param4,
                 char *buf )
  {
    long ifanr;
    long tagesdatum;
    long s;
    char errmld[10];

    if ( *param3 != 'p' )
    {
      strcpy( buf, "p bei Protokollverzeichnis fehlt" );
      return 1;
    }

    ifanr = atol( param2 );

    if ( param4 == NULL )
      tagesdatum = GetPhoDate();
    else
    {
      if ( strlen( param4 ) != 10 ||
           ConvToPhoDate ( param4, &tagesdatum, "tt.mm.jjjj" ) == 0 )
      {
         strcpy( buf, "Datum in der Form tt.mm.jjjj" );
         return 1;
      }
   }

    s = OpenBase( db, buf );
    if ( s == 0 )
    {
       s = OpenPflege( user, buf );
       if ( s == 0 )
       {
		  /* ------ BSsichG: BeitragsSatzSicherungsGesetz 18.12.2002 */
 		  /* bssichg: 23.12.2003 entfaellt wieder, da neues Gesetz */
		  /*
		  s = GetLifeStyle( buf );  
		  */
		  if ( s == 0 )
			 s = Reset_PL_C_HERSTNUM_Direkt( ifanr, buf );
          if ( s == 0 )
             s = Select_Loop( ifanr, tagesdatum, *param1, &param3[1], buf );
          ClosePflege( errmld );

          /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
          SqlExecuteImm("update statistics medium for table zartikel" );
          SqlExecuteImm("update statistics medium for table zifaart" );

       }

       CloseBase( );
    }


    return s;
   }


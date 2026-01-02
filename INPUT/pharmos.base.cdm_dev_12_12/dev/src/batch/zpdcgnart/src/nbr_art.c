/* --- Includes                  ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <hdatum/phodate.h>
#include "znb_gen_dc.h"

/* -------  Special includes ----------------------------------------- */

#include <eklibs/sqltabs/tabsqld.h>
#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_dbas.h>
#include <eklibs/wdbups/wpp_dirt.h>

/* ------- Table definition includes -----------------------------------*/

#include <voodoo_table_header/zdcart.h>
#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartaustria.h>	
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/zartwg.h>
#include <voodoo_table_header/ean.h>
#include <voodoo_table_header/zapflege.h>
#include <voodoo_table_header/zpznpflege.h>
#include <voodoo_table_header/bliesort.h>
#include <voodoo_table_header/artnrbl.h>
#include <voodoo_table_header/ccomgroupprop.h>
#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/zaneuhei.h>

#include "znb_gen_dc.h"
#include "zart_gen.h"
#include "nbr_art.h"

#define L_ARTIKEL_NR 7

/* ----------------- Usage ------------------------ */

void GenArtUsage( char *spBuf, const char *spProg )
{
   strcat( spBuf, "- " );
   strcat( spBuf, spProg );
   strcat( spBuf, " 0 database dcdatum  p[ProtokolVerz][datum]\n" \
                "  alle relevanten Saetze generieren\n" );
   strcat( spBuf, "- " );
   strcat( spBuf, spProg );
   strcat( spBuf, " 1 database dcdatum  p[ProtokolVerz][datum]\n" \
                "  nur relevante Neuaufnahmen generieren\n" );
}
/* --------------------- rd_herst --------------------------------- */

/*void CloseHerstel( );*/

/* --------  user -------------- */

static const char* const user = "dc     "  ;

/* ------ Special SQL-errors --------------- */

#define  SQL_DOUBLE_ROW   ( -239 )
#define  SQL_LOCKED_ROW   ( -250 )
#define  SQL_NOT_FOUND    (  100 )
#define  SQL_NOT_ONE_ROW  ( -284 )
#define  SQL_DOUBLE_INDEX ( -346 )
#define  NOVALUE_ERROR    ( 47114712 )

void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

long OpenBase( const char* const spDb, char *spErrmld )
{
   long lRetCode;
   char szBase[50];
   strcpy( szBase, "database " );
   strcat( szBase, spDb );

   lRetCode = SqlExecuteImm( szBase );
   if ( lRetCode != 0 )
   {
      strcpy( spErrmld, szBase );
      strcat( spErrmld, ": " );
      strcat( spErrmld, DynErrmld() );
      return lRetCode;
   }

   lRetCode = SqlExecuteImm("set isolation to dirty read" );
   if ( SQL_SETISOLA_ERROR == lRetCode ) lRetCode = 0;
   if ( SQL_SUCCESS != lRetCode )
   {
     strcpy( spErrmld, "set isolation: " );
     strcat( spErrmld, DynErrmld() );
     CloseBase( );
     return lRetCode;
   }

   lRetCode = SqlExecuteImm( "SET LOCK MODE TO WAIT 10" );
   if (  SQL_SETISOLA_ERROR == lRetCode ) lRetCode = 0;
   if ( SQL_SUCCESS != lRetCode )
   {
     strcat( spErrmld, "set lock mode: ");
     strcat( spErrmld, DynErrmld() );
     CloseBase( );
     return lRetCode;
   }
   return 0;
}

/* ---------- Primekeycondition ----------- */

static char PrimekeyCond[100];

/* Ccomgroupprop  */
static struct CCOMGROUPPROP Buf_CComgroupProp;

static long lStatus_CComgroupProp;

int InitRecord_CComgroupProp()
{
   strcpy(Buf_CComgroupProp.ADOPT_ABEZ_FROM_DC,"1") ;
   strcpy(Buf_CComgroupProp.ADOPT_AEP_FROM_DC ,"1") ;
   strcpy(Buf_CComgroupProp.ADOPT_ANRH_FROM_DC ,"1") ;
   strcpy(Buf_CComgroupProp.ADOPT_AVP_FROM_DC ,"1") ;
   strcpy(Buf_CComgroupProp.ADOPT_DRFO_FROM_DC ,"1") ;
   strcpy(Buf_CComgroupProp.ADOPT_EINH_FROM_DC ,"1") ;
   strcpy(Buf_CComgroupProp.ADOPT_GEP_FROM_DC ,"1") ;
   strcpy(Buf_CComgroupProp.TAX_GROUP ,"0") ;
   return 0;
}

long ReadRecord_CComgroupProp( const char *spCommodity_group, char *spErrmld )
{
   long lStatus;
   int iPos;
   char szSql[1000];

   lStatus = 100;
   strcpy( spErrmld, "" );

   iPos =  sprintf( szSql, "select %s from CCOMGROUPPROP",PROJECTION_CCOMGROUPPROP);
   iPos	+= sprintf(szSql+iPos," where COMMODITY_GROUP='%s' ",spCommodity_group );

   lStatus = SqlRead( szSql, &Buf_CComgroupProp, NULL );

   if ( SQL_SUCCESS == lStatus  )
   {
      strcpy( spErrmld, "" );
   }
   else if ( SQL_NOTFOUND == lStatus  )
   {
      if ( InitRecord_CComgroupProp() == 0 )
      {}
      else 
        lStatus = -1;
   }
   else
      strcpy ( spErrmld, DynErrmld() );
   lStatus_CComgroupProp = lStatus;	
   return lStatus;
}
/* Zartikel */
#define MAX_ZARTIKEL 2

#define NR_ART 0
#define NR_ERS 1

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
}

int GetBufferDesc_Zartikel( char * spErrmld )
{
   char *spTabelle = "zartikel";
   long lStatus;
   char szErrstr[80];

   strcpy( spErrmld, "");
   if ( Fd_Zartikel >= 0 ) return 0;

   FillCmpIndikator_Zartikel ( );
   lStatus = OpenBufferDescProj( &Fd_Zartikel, spTabelle, PROJECTION_ZARTIKEL,
                                 CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, szErrstr );
   if ( lStatus != 0 )
   {
     sprintf( spErrmld, "%s: %s", spTabelle, szErrstr );
     Fd_Zartikel = -1;
     return -1;
   }
   return 0;
}

int InitRecord_Zartikel( int iIndex )
{
   long lArtNr;
   lArtNr = Buf_zartikel[iIndex].ARTIKEL_NR;
   FdInitTabBuf( Fd_Zartikel, &Buf_zartikel[iIndex] );
   InitArtikelFields( &Buf_zartikel[iIndex], user );
   Buf_zartikel[iIndex].ARTIKEL_NR = lArtNr;
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

   if ( SQL_SUCCESS == lStatus  )
   {
      BufOld_zartikel[i] = Buf_zartikel[i];  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( SQL_NOTFOUND == lStatus  )
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


/* Zartaustria */
static char CmpIndikator_Zartaustria[POSANZ_ZARTAUSTRIA + 1];
static int  Fd_Zartaustria = -1;
static long lStatus_Zartaustria[MAX_ZARTIKEL];

static struct ZARTAUSTRIA Buf_zartaustria[MAX_ZARTIKEL];
static struct ZARTAUSTRIA BufOld_zartaustria[MAX_ZARTIKEL];

void FillCmpIndikator_Zartaustria ( )
{
   memset( CmpIndikator_Zartaustria, '1', POSANZ_ZARTAUSTRIA );
   CmpIndikator_Zartaustria[POSANZ_ZARTAUSTRIA] = '\0';
}

int GetBufferDesc_Zartaustria( char * errmld )
{
   char *tabelle = "zartaustria";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zartaustria >= 0 ) return 0;

   FillCmpIndikator_Zartaustria ( );
   lStatus = OpenBufferDescProj( &Fd_Zartaustria, tabelle, PROJECTION_ZARTAUSTRIA,
                                 CmpIndikator_Zartaustria, NULL, V_PROTO_VERTEIL, errstr );

   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zartaustria = -1;
     return -1;
   }
   return 0;
}

void InitRestArtikelAustria( struct ZARTAUSTRIA *zart, const char* const user );

int InitRecord_Zartaustria( int i )
{
   long nr;
   nr = Buf_zartaustria[i].ARTIKEL_NR;
   FdInitTabBuf( Fd_Zartaustria, &Buf_zartaustria[i] );
   Buf_zartaustria[i].ARTIKEL_NR = nr;

   InitZartaustriaFields( &Buf_zartaustria[i], user );

   return 0;
}

void SetPrimekeyCondition_Zartaustria ( int i )
{
   char format[30];
   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartaustria[i].ARTIKEL_NR );

/* sprintf( PrimekeyCond, "ARTIKEL_NR=%ld", Buf_zartikel[i].ARTIKEL_NR ); */
}

long ReadRecord_Zartaustria( int i, long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_zartaustria[i].ARTIKEL_NR = artikel_nr;
   SetPrimekeyCondition_Zartaustria ( i );
   lStatus = FdReadRecord( Fd_Zartaustria, PrimekeyCond,
                           &Buf_zartaustria[i], errstr );

   if ( lStatus == 0 )
   {
      BufOld_zartaustria[i] = Buf_zartaustria[i];  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Zartaustria( i ) == 0 )
      {
        BufOld_zartaustria[i] = Buf_zartaustria[i];  /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_Zartaustria[i] = lStatus;
   return lStatus;
}
long StoreRecord_Zartaustria( int i, char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zartaustria ( i );
   if ( lStatus_Zartaustria[i] == 100 )
      lStatus = FdDelayInsertRecord( Fd_Zartaustria, &Buf_zartaustria[i],
                                     PrimekeyCond, errmld);
   else if ( lStatus_Zartaustria[i] == 0 )
      lStatus = FdDelayUpdateRecord( Fd_Zartaustria, &Buf_zartaustria[i],
                                     &BufOld_zartaustria[i],
                                     PrimekeyCond, errmld );
   else
   {
     lStatus = lStatus_Zartaustria[i];
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

   if ( SQL_SUCCESS == lStatus  )
   {
      BufOld_zpreis[i] = Buf_zpreis[i];  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( SQL_NOTFOUND == lStatus )
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

   if ( SQL_SUCCESS == lStatus )
   {
      BufOld_zpreis[i] = Buf_zpreis[i];  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( SQL_NOTFOUND == lStatus )
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


long StoreRecord_Zpreis( int iIndex, char *spErrmld )
{
   long lStatus;
   char szErrmld[200];

   SetPrimekeyCondition_Zpreis ( iIndex );
   if ( lStatus_Zpreis[iIndex] == 100 )
      lStatus = FdDelayInsertRecord( Fd_Zpreis, &Buf_zpreis[iIndex],
                                     PrimekeyCond_Zpreis, szErrmld );
   else if ( lStatus_Zpreis[iIndex] == 0 )
      lStatus = FdDelayUpdateRecord( Fd_Zpreis, &Buf_zpreis[iIndex],
                                     &BufOld_zpreis[iIndex],
                                     PrimekeyCond_Zpreis, szErrmld );
   else
   {
     lStatus = lStatus_Zpreis[iIndex];
     strcpy( szErrmld, "Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( spErrmld, szErrmld );
   else
      strcpy( spErrmld, "" );
   return lStatus;
}



/* -----  Zartwg  -------------------------- */

#define MAX_WGR  2

static int  Fd_Zartwg = -1;

static long lStatus_Zartwg[MAX_WGR];
static struct ZARTWG Buf_zartwg[MAX_WGR];
static struct ZARTWG BufOld_zartwg[MAX_WGR];

static char  PrimekeyCond_Zartwg[50];

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

void SetPrimekeyCondition_Zartwg( int iIndex)
{
   char szFormat[50];
   sprintf( szFormat, "ARTIKEL_NR=%c%d.ld and ART='%cs'",
                    '%', L_ARTIKEL_NR, '%' );

   sprintf( PrimekeyCond_Zartwg, szFormat,
            Buf_zartwg[iIndex].ARTIKEL_NR,
            Buf_zartwg[iIndex].ART );

/*
   sprintf( PrimekeyCond_Zartwg,
            "ARTIKEL_NR=%ld and ART='%s'",
            Buf_zartwg[iIndex].ARTIKEL_NR,
            Buf_zartwg[iIndex].ART );
*/
}

int InitRecord_Zartwg( int iIndex)
{
   strcpy( Buf_zartwg[iIndex].WARENGRUPPE, "     " );
   return 0;
}

long ReadRecord_Zartwg( int iIndex, long artikel_nr, char wg_art,char *spErrmld )
{
   long lStatus;
   char szErrstr[200];

   Buf_zartwg[iIndex].ARTIKEL_NR = artikel_nr;
   Buf_zartwg[iIndex].ART[0] = wg_art;

   SetPrimekeyCondition_Zartwg ( iIndex);
   lStatus = FdReadRecord( Fd_Zartwg, PrimekeyCond_Zartwg,
                           &Buf_zartwg[iIndex], szErrstr );
   if ( lStatus == 0 )
   {
      BufOld_zartwg[iIndex] = Buf_zartwg[iIndex];  /* gelesenen Satz sichern */
      strcpy( spErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Zartwg(iIndex ) == 0 )
      {
        BufOld_zartwg[iIndex] = Buf_zartwg[iIndex];  /* gelesenen Satz sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( spErrmld, szErrstr );

   // Status pro Lesevorgang merken
   lStatus_Zartwg[iIndex] = lStatus;

   return lStatus;
}

long StoreRecord_Zartwg( int iIndex, char *spErrmld )
{
   long lStatus;
   char szErrmld[200];

   SetPrimekeyCondition_Zartwg ( iIndex );
   if ( SQL_NOTFOUND == lStatus_Zartwg[iIndex]  )
      lStatus = FdDelayInsertRecord( Fd_Zartwg, &Buf_zartwg[iIndex],
                                     PrimekeyCond_Zartwg, szErrmld );
   else if ( SQL_SUCCESS == lStatus_Zartwg[iIndex] )
      lStatus = FdDelayUpdateRecord( Fd_Zartwg, &Buf_zartwg[iIndex],
                                     &BufOld_zartwg[iIndex],
                                     PrimekeyCond_Zartwg, szErrmld );
   else
   {
     lStatus = lStatus_Zartwg[iIndex];
     strcpy( szErrmld, "Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( spErrmld, szErrmld );
   else
      strcpy( spErrmld, "" );
   return lStatus;
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


/* -----  Zbliesort  ------------------------- */

static int  Fd_Bliesort = -1;

static struct BLIESORT Buf_bliesort;

int GetBufferDesc_Bliesort( char * errmld )
{
   char *tabelle = "bliesort";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Bliesort >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Bliesort, tabelle, PROJECTION_BLIESORT,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Bliesort = -1;
     return -1;
   }
   return 0;
}

long StoreRecord_Bliesort( long artikel_nr, long besla_nr, char* cErrmld )
{
   long lStatus;

   Buf_bliesort.ARTIKEL_NR = artikel_nr;
   Buf_bliesort.BESLA_NR   = besla_nr;

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and BESLA_NR=%ld",
                          Buf_bliesort.ARTIKEL_NR,
                          Buf_bliesort.BESLA_NR );

   lStatus = FdReadRecord( Fd_Bliesort, PrimekeyCond,
                           &Buf_bliesort, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   if ( lStatus == 100 )
   {
      Buf_bliesort.ARTIKEL_NR = artikel_nr;
      Buf_bliesort.BESLA_NR  = besla_nr;
      lStatus = FdDelayInsertRecord( Fd_Bliesort, &Buf_bliesort,
                                     PrimekeyCond, cErrmld);
   }
   return lStatus;
}


/* -----  Artnrbl  ------------------------- */

static int  Fd_Artnrbl = -1;

static struct ARTNRBL Buf_artnrbl;
static struct ARTNRBL BufOld_artnrbl;

int GetBufferDesc_Artnrbl( char * errmld )
{
   char *tabelle = "artnrbl";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Artnrbl >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Artnrbl, tabelle, PROJECTION_ARTNRBL,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Artnrbl = -1;
     return -1;
   }
   return 0;
}

long StoreRecord_Artnrbl( long artikel_nr, long besla_nr, char* artnrbl, int isArtikelVorhanden, char* cErrmld )
{
   long lStatus;
   char czCmpArtNrBl[L_ARTNRBL_ARTIKEL_NR_BLIEFER+1];
   memset( czCmpArtNrBl ,' ',L_ARTNRBL_ARTIKEL_NR_BLIEFER);
   czCmpArtNrBl[L_ARTNRBL_ARTIKEL_NR_BLIEFER] = '\0';

   Buf_artnrbl.ARTIKEL_NR = artikel_nr;
   Buf_artnrbl.BESLA_NR   = besla_nr;

   strcpy( cErrmld, "" );
   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and BESLA_NR=%ld",
                          Buf_artnrbl.ARTIKEL_NR,
                          Buf_artnrbl.BESLA_NR );

   lStatus = FdReadRecord( Fd_Artnrbl, PrimekeyCond, &Buf_artnrbl, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) 
	   return -1;
   
   if ( strncmp(artnrbl,czCmpArtNrBl,15) == 0) 
   {
		if (isArtikelVorhanden && strncmp(BufOld_zartikel[NR_ART].ARTIKEL_NR_HERST,czCmpArtNrBl,15) != 0 && lStatus == 0 )
		{
			// löschen artnrbl
			lStatus = FdDelayDeleteRecord(Fd_Artnrbl, &Buf_artnrbl, PrimekeyCond, cErrmld);
		}
		// else: nix zu tun
   }
   else
   {
	   BufOld_artnrbl = Buf_artnrbl;
	   strcpy(Buf_artnrbl.ARTIKEL_NR_BLIEFER,artnrbl);

	   if ( lStatus == 0 )
	   {
		// update
		   lStatus = FdDelayUpdateRecord( Fd_Artnrbl, &Buf_artnrbl, &BufOld_artnrbl, PrimekeyCond, cErrmld);
	   }
	   else
	   {
		//insert
		   lStatus = FdDelayInsertRecord( Fd_Artnrbl, &Buf_artnrbl, PrimekeyCond, cErrmld);
	   }
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


/* -----  CArticleCodes  ------------------------- */

static int  Fd_CArticleCodes = -1;

static struct CARTICLECODES Buf_CArticleCodes;
static char PrimekeyCond_CArticleCodes[100];

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

long InsertRecord_CArticleCodes( char* cErrmld )
{
   long lStatus;

   strcpy( cErrmld, "" );
   
   lStatus = FdDelayInsertRecord( Fd_CArticleCodes, &Buf_CArticleCodes,
                                PrimekeyCond_CArticleCodes, cErrmld);
   
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

/* ---------------------------------------------------------------------- *
 * Funktion         Zdcart lesen                                          *
 * ---------------------------------------------------------------------- */

#define S_ZDC ZDCART

static char *zdc_proj = "*";

static int fd_zdc_sel = -1;
static int fd_zdc_del = -1;


/* read datacare table  */
static long Zdc_Select( long dcnr, long datum, char mode, char *errmld )
{
    long s;
    char sql[500];

    /* Select unabhaengig vom dcSTATUS / NBSTATUS */
    /* das bedeutet: alle Saetze im Datumsbereich werden geloescht */
    /*    nur die Saetze mit dcSTATUS = dcSTATUS_FREIGEGEBEN */
    /*                   und NBSTATUS <= '1'  werden uebernommen */
    /*    diese Auswahl geschieht vor Do_All */

    if ( mode == '0' )   /* Alle relevanten Saetze */
      sprintf( sql,
          "select %s from ZDCART where DCNR=%ld and "  \
          "DC_DATUMGUELTIGAB>0 and DC_DATUMGUELTIGAB<=%ld " \
          "order by DCNR,DC_ARTIKEL_NR",
          zdc_proj,
          dcnr,
          datum );
    else                 /* alle relevanten Neuaufnahmen */
      sprintf( sql,
          "select %s from ZDCART where DCNR=%ld and "  \
          "ZAENDERUNG='0' and " \
          "DC_DATUMGUELTIGAB>0 and DC_DATUMGUELTIGAB<=%ld " \
          "order by DCNR,DC_ARTIKEL_NR",
          zdc_proj,
          dcnr,
          datum );

/*  printf("%s\n", sql );  */

    s = SqlOpenCsWh( &fd_zdc_sel, sql );
    if ( s != 0 )
    {
      fd_zdc_sel = -1;
      sprintf( errmld, "ZDCART: %s", DynErrmld() );
    }
    return s;
}

static long Zdc_Fetch( struct S_ZDC *dc, char *errmld )
{
    long s;
    s = SqlFetch( fd_zdc_sel, 1, dc, NULL );
    if ( s != 0 )
      sprintf( errmld, "ZDCART: %s", DynErrmld() );
    return s;
}

static long Zdc_CloseCs( char *errmld )
{
    long s;
    if ( fd_zdc_sel == -1 ) return 0;
    s = SqlCloseCs( fd_zdc_sel );
    if ( s != 0 && errmld != NULL )
       sprintf( errmld, "ZDCART: %s", DynErrmld() );
    fd_zdc_sel = -1;
    return s;
}

static long Zdc_PrepDelete( char *errmld )
{
    long s;
    s = SqlPrepareStmnt ( &fd_zdc_del,
                          "delete from ZDCART where DCNR=? and SATZNR=?",
                          "ZDCART.DCNR", "ZDCART.SATZNR", NULL );
    if ( s != 0 )
    {
      fd_zdc_del = -1;
      sprintf( errmld, "ZDCART PrepDelete: %s", DynErrmld() );
    }
    return s;
}

static long Zdc_ExecuteDelete( struct S_ZDC *dc, char *errmld )
{
    long s;
    long dcnr;
    long satznr;
    dcnr  = dc->DCNR;
    satznr = dc->SATZNR;
    s = SqlExecutePrepare( fd_zdc_del, &dcnr, &satznr, NULL );
    if ( s != 0 )
      sprintf( errmld, "ZDCART ExecDelete: %s", DynErrmld() );
    return s;
}

static long Zdc_FreeDelete( char *errmld )
{
    long s;
    if ( fd_zdc_del == -1 )  return 0;
    s = SqlFreePrepare( fd_zdc_del );
    if ( s != 0 && errmld != NULL )
        sprintf( errmld, "ZDCART FreeDelete: %s", DynErrmld() );
    fd_zdc_del = -1;
    return s;
}

static long StartWork( char *spErrmld )
  {
    long lRetCode;
    lRetCode = SqlBeginWork( );
    if ( lRetCode != 0 )
      {
        strcpy( spErrmld, "datacare uebertragen: " );
        strcat( spErrmld, DynErrmld() );
       }
    return lRetCode;
   }

static long EndWork( long lStatus, char *spErrmld )
  {
    long lRetCode;
    if ( lStatus == 0 )
      {
        lRetCode = SqlCommitWork( );
        if ( lRetCode != 0 )
          {
            strcpy( spErrmld, "datacare uebertragen: " );
            strcat( spErrmld, DynErrmld() );
           }
        return lRetCode;
       }
     else
      {
        lRetCode = SqlRollbackWork( );
        return lStatus;
       }
   }

  /* -----  Ean     ------------------------- */

static int  Fd_Zean = -1;
static struct EAN Buf_zean;

int GetBufferDesc_Zean( char * errmld )
{
   char *tabelle = "ean";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   
   if ( Fd_Zean >= 0 ) 
	   return 0;

   lStatus = OpenBufferDescProj( &Fd_Zean, tabelle, PROJECTION_EAN,
                                 NULL, NULL,
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
   FdInitTabBuf( Fd_Zean, &Buf_zean );
   return 0;
}

void SetPrimekeyCondition_Zean ( )
{
   char format[30];
   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zean.ARTIKEL_NR );
}

long StoreRecord_Zean( char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zean ( );

   lStatus = FdDelayInsertRecord( Fd_Zean, &Buf_zean,
                                     PrimekeyCond, errmld);

   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );

   return lStatus;
}

static long Open_All( long dcnr, char *cErrmld )
{
    if ( 0 != GetBufferDesc_Zartikel     ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Zartaustria  ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Zpreis       ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Zartwg       ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Zapflege     ( cErrmld )) return -1;
	if ( 0 != GetBufferDesc_Zpznpflege   ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Bliesort     ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Artnrbl		 ( cErrmld )) return -1;
	if ( 0 != GetBufferDesc_CArticleCodes( cErrmld )) return -1;
	if ( 0 != GetBufferDesc_Zean		 ( cErrmld )) return -1;
	if ( 0 != GetBufferDesc_Zaneuheit    ( cErrmld )) return -1;
	return 0;
}

static void Close_All(  )
{
}

/* ---- Generiert Preis , wenn Hersteller-Prozent */

static void MakePreisAusHerstProz( double herst_proz,
                                   double *grosso, double *aep, const struct CCOMGROUPPROP *CComBuf )
{
   double wert;
   if ( herst_proz >= 0.005 )
   {
     if (( (*aep) < 0.005 ) && ( CComBuf->ADOPT_AEP_FROM_DC[0] == '1')) 
     {
        wert = (*grosso)*herst_proz/100.0;
        KaufmRunden( &wert, 2);
        *aep = (*grosso) + wert;
     }
   }
   else if ( herst_proz <= -0.005 )
   {
#ifdef _VORHER_
  /* es wurde richtig gerundet */
     if (( (*grosso) < 0.005 ) &&  ( CComBuf->ADOPT_GEP_FROM_DC[0] == '1'))
     {
        wert = (*aep)*herst_proz/100.0;
        KaufmRunden( &wert, 2);
        *grosso = (*aep) + wert;
     }
#else
  /* so wird in PHARMOS gerundet */
     if (( (*grosso) < 0.005 ) &&  ( CComBuf->ADOPT_GEP_FROM_DC[0] == '1'))
     {
        wert = (*aep)*herst_proz/100.0;
        *grosso = (*aep) + wert;
        KaufmRunden( grosso, 2);
     }
#endif
   }
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

/* ---- testet Preisgleichheit */

static int WertGleich( double wert0, double wert1 )
{
   double diff;
   diff = wert0 - wert1;
   KaufmRunden( &diff, 2 );
   if ( diff >= -0.005 && diff <= 0.005 ) return 1;
   return 0;
}

static int IsPreisGleich( struct ZARTPREIS *spBuf0, struct ZARTPREIS *spBuf1 )
{
   if ( !WertGleich( spBuf0->GROSSO, spBuf1->GROSSO ) ) return 0;
   if ( !WertGleich( spBuf0->AEP   , spBuf1->AEP    ) ) return 0;
   if ( !WertGleich( spBuf0->AVP   , spBuf1->AVP    ) ) return 0;
   if ( !WertGleich( spBuf0->EAVP  , spBuf1->EAVP   ) ) return 0;
   if ( spBuf0->KE_MWST[0] != spBuf1->KE_MWST[0] ) return 0;
   return 1;
}

static int IsPreisUebernahmeWgr02( const struct ZARTPREIS *spBuf0, const struct ZARTPREIS *spBuf1 )
{
	long lGep;

	if ( !WertGleich( spBuf0->AEP   , spBuf1->AEP    ) ) return 1;
	if ( !WertGleich( spBuf0->AVP   , spBuf1->AVP    ) ) return 1;

	// DC-Price 0.00 or 0.01 
	lGep = (long) (( spBuf0->GROSSO + 0.005) * 100);
	if ( 2 <= lGep)
		return 1;

	// Zartpreis-Price 0.00 or 0.01 -> No Update
	lGep = (long) (( spBuf1->GROSSO + 0.005) * 100);
	if ( 1 <= lGep)
		return 0;

	return 1;
}

/* ----- Alles Updaten -------------- */

static long Do_All( struct S_ZDC *spDCBuf, long tagesdatum, char *errmld )
{
    long lRetCode;
    long s1;
    long artikel_nr;
    long ersatz_nr;
	int  IsDCDeleted;
	int  IsDCReactivated;
    int  IsDCAH;
    int  ToStorePreis;
/*	int  ToStoreZartaustria;*/
	int  ToComparePreise;  
    int  ToStoreZartwg;
    int  IsArtikelVorhanden;
	int  IsArtikelAustriaVorhanden;
	int  IsCCommGroupProp;
    long HerstellerNr_Alt;
	/* ZArtikel */
    artikel_nr =  spDCBuf->DC_ARTIKEL_NR;
    lRetCode = ReadRecord_Zartikel( NR_ART, artikel_nr, errmld );
    if ( !( lRetCode == 0 || lRetCode == 100 ) ) return lRetCode;

	IsArtikelVorhanden = lRetCode == 0;

    /* ZArtaustria */
    lRetCode = ReadRecord_Zartaustria( NR_ART, artikel_nr, errmld );
	IsArtikelAustriaVorhanden = lRetCode == 0;

	/* Zartwg */
	ReadRecord_Zartwg( 0, artikel_nr, '2',errmld );	
	ReadRecord_Zartwg( 1, artikel_nr, '4',errmld );

	/* Ccomgroupprop */  
    lRetCode = ReadRecord_CComgroupProp(spDCBuf->WARENGRUPPE , errmld );

	IsCCommGroupProp = lRetCode == 0;

    if ( IsArtikelVorhanden )
       HerstellerNr_Alt = Buf_zartikel[NR_ART].HERSTELLER_NR;
     else
       HerstellerNr_Alt = -1;

    /* ---deleted by  DC ---- */
    IsDCDeleted = GetIsDCDeleted( spDCBuf );

    /* ---reactivated by  DC ---- */
    IsDCReactivated = GetIsDCReactivated( spDCBuf );


    /* ---- bei DC-Loeschung und fehlendem Artikel ---- */
    /* ---- Artikel nicht mehr neu aufnehmen        ---- */
    if ( IsDCDeleted && !IsArtikelVorhanden ) 
		return 0;

    /* ---- DC-AH ---- */
    IsDCAH = GetIsDCAH( spDCBuf );

    ToStoreZartwg = 0;
    ersatz_nr = 0;

    if ( IsDCDeleted  )
    {
      /* ---- nur Loeschdatum eintragen ---- */
      Buf_zartikel[NR_ART].DATUM_IFALOESCH = spDCBuf->DC_DATUMGUELTIGAB;
	  Buf_zartikel[NR_ART].DATUM_AV = spDCBuf->DC_DATUMGUELTIGAB;
	  Buf_zartikel[NR_ART].DATUM_RR = spDCBuf->DC_DATUMGUELTIGAB;
	  Buf_zartikel[NR_ART].ARTIKEL_GELOESCHT[0] = '1';
    }
    else
    {
	  /* ----- DC-Werte nach Warengruppe ----- */
	  DCSatzToArtWgr2( spDCBuf, &Buf_zartwg[0] );
	  DCSatzToArtWgr4( spDCBuf, &Buf_zartwg[1] );

	  /* ----- DC-Werte nach Artikelsatz ----- */
      DCSatzToArtikel( spDCBuf, &Buf_zartikel[NR_ART], &Buf_CComgroupProp, IsArtikelVorhanden, &Buf_zartwg[1], &Buf_zartwg[0] );

	  /* ----- DC-Werte nach Artikelsatz Austria ----- */
      DCSatzToArtikelAustria( spDCBuf, &Buf_zartaustria[NR_ART],&Buf_zartikel[NR_ART], IsArtikelAustriaVorhanden );
	}
    
    /* ----- Zartikel  ----- */
    lRetCode = StoreRecord_Zartikel( NR_ART, errmld );
    if ( lRetCode != 0 ) return lRetCode;

	lRetCode = StoreRecord_Zartaustria( NR_ART, errmld );
    if ( lRetCode != 0 ) return lRetCode;

	if (strcmp(Buf_zartwg[0].WARENGRUPPE, "     " ) != 0) {
		lRetCode = StoreRecord_Zartwg(0, errmld);
		if ( lRetCode != 0 ) return lRetCode;
	}

	if (strcmp(Buf_zartwg[1].WARENGRUPPE, "     " ) != 0) {
		lRetCode = StoreRecord_Zartwg(1, errmld);
		if ( lRetCode != 0 ) return lRetCode;
	}

	if ( !IsDCDeleted  )
    {
		/* ---- Preise ---- */
		s1 =  ReadRecord_ZpreisLast( 1, artikel_nr, errmld ); /* preis 1 */
		if ( !( s1 == 0 || s1 == 100 ) ) return -1;

		Buf_zpreis[0].ARTIKEL_NR = spDCBuf->DC_ARTIKEL_NR;
		Buf_zpreis[0].DATUMGUELTIGAB = spDCBuf->DC_DATUMGUELTIGAB;	
		lRetCode = ReadRecord_Zpreis( 0, errmld );              /* preis 0 */
		if ( !( lRetCode == 0 || lRetCode == 100 ) ) return -1;

		Buf_zpreis[0] = Buf_zpreis[1];
		Buf_zpreis[0].ARTIKEL_NR = spDCBuf->DC_ARTIKEL_NR;
		Buf_zpreis[0].DATUMGUELTIGAB = spDCBuf->DC_DATUMGUELTIGAB;	

		ToComparePreise = 0;
		ToStorePreis = 0;
		// Preisänderung oder noch kein Preis vorhanden
		if ( IsPreisChanged( spDCBuf ) || (SQL_NOTFOUND == s1) )
		{
			/* DC-Preise uebernehmen */
			DCSatzToPreis( spDCBuf, &Buf_zpreis[0],&Buf_CComgroupProp, IsArtikelVorhanden );

			/* Hersteller-Prozent uebernehmen nur wenn kein Tax-Artikel*/
			if ( '0' == Buf_zartikel[NR_ART].TAXPFL[0] )
			{
				Buf_zpreis[0].HERST_PROZENT = Buf_zartikel[NR_ART].HERST_PROZENT;
				MakePreisAusHerstProz( Buf_zpreis[0].HERST_PROZENT,
                                &Buf_zpreis[0].GROSSO,
                                &Buf_zpreis[0].AEP, &Buf_CComgroupProp ); 
			}
			if ( s1 == 0 )  /* alter Preis vorhanden */
			{
				if ( Buf_zpreis[0].DATUMGUELTIGAB < Buf_zpreis[1].DATUMGUELTIGAB )
					ToStorePreis = 0;   /* Preisdatum zu alt */
				else
				{
					ToStorePreis = !IsPreisGleich( &Buf_zpreis[0], &Buf_zpreis[1] );
					ToComparePreise = ToStorePreis;
				}

				/* zartwg2 = 02*, DC-AEP = AEP, DC-AVP = AVP, DC-GEP = 0.00 oder 0.01 und GEP > 0.01 */
				if ( ToStorePreis && ( Buf_zartwg[0].WARENGRUPPE[0] == '0' ) && ( Buf_zartwg[0].WARENGRUPPE[1] == '2' ))
					ToStorePreis = IsPreisUebernahmeWgr02(&Buf_zpreis[0], &Buf_zpreis[1]);
			}
			else
				ToStorePreis = 1;

			if ( ToStorePreis )
			{
				lRetCode = StoreRecord_Zpreis( 0, errmld );
				if ( lRetCode != 0 ) return lRetCode;
			}
			else
				 Buf_zpreis[0] = Buf_zpreis[1];  /* Keine Änderungen übernommen*/
		}
		else
			Buf_zpreis[0] = Buf_zpreis[1];		/* Keine Preisänderung*/

	}

	if ( !IsArtikelVorhanden && !IsDCDeleted )   /* Neuanlage */
	{
		FdInitTabBuf( Fd_CArticleCodes, &Buf_CArticleCodes );
		Buf_CArticleCodes.ARTICLENO = artikel_nr;
		Buf_CArticleCodes.SERIAL_NUMBER = 1;
		Buf_CArticleCodes.CODE_TYPE = 11;
		Buf_CArticleCodes.PREFERRED_FLAG = 1;
		Buf_CArticleCodes.DATE_CHANGED = GetPhoDate();
		sprintf(Buf_CArticleCodes.ARTICLE_CODE, "%d", artikel_nr);

		sprintf( PrimekeyCond_CArticleCodes,"ARTICLENO=%7d AND SERIAL_NUMBER=1 AND CODE_TYPE=11", 
											Buf_CArticleCodes.ARTICLENO);

		lRetCode = InsertRecord_CArticleCodes( errmld );

		if ( lRetCode != 0 ) 
			return lRetCode;

		if ( spDCBuf->DC_DATUMGUELTIGAB <= tagesdatum )
			lRetCode = StoreRecord_Zpznpflege("34", artikel_nr, tagesdatum, errmld );
	    else
			lRetCode = StoreRecord_Zpznpflege("34", artikel_nr, spDCBuf->DC_DATUMGUELTIGAB, errmld );
	   
		if ( lRetCode != 0 ) 
			return lRetCode;
	}

	if ( !IsArtikelVorhanden && !IsDCDeleted )   /* Neuanlage --> EAN */
	{
		char leer[L_EAN_EAN_NR + 1];
		memset( leer, ' ', L_EAN_EAN_NR );
		
		if ( memcmp( spDCBuf->DC_EAN_NR, leer, L_EAN_EAN_NR  ) != 0 )
		{
			InitRecord_Zean();
			Buf_zean.ARTIKEL_NR = artikel_nr;
			strcpy(Buf_zean.EAN_NR, spDCBuf->DC_EAN_NR); 

			lRetCode = StoreRecord_Zean(errmld);

			if ( lRetCode != 0 ) 
				return lRetCode;

			lRetCode = StoreRecord_Zpznpflege("09", artikel_nr, tagesdatum, errmld );

			if ( lRetCode != 0 ) 
				return lRetCode;
		}
	}

    /* ---- Zapflege ---- */
    if ( spDCBuf->DC_DATUMGUELTIGAB <= tagesdatum )
        lRetCode = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
    else
        lRetCode = StoreRecord_Zapflege( artikel_nr, spDCBuf->DC_DATUMGUELTIGAB, errmld );
    if ( !( lRetCode == 0 || lRetCode == 100 ) ) return lRetCode;


    if ( !IsArtikelVorhanden )   /* Neuanlage */
    {
		/* Bliesort */ 
		lRetCode = StoreRecord_Bliesort(artikel_nr, Buf_zartikel[NR_ART].HERSTELLER_NR, errmld ); // TH an sich ist das falsch = darf nicht die HNR sein!

		if ( !( lRetCode == 0 || lRetCode == 100 ) ) 
			return lRetCode;
	}
	else if ( HerstellerNr_Alt != Buf_zartikel[NR_ART].HERSTELLER_NR )
    {
      // Zaneuheit Herstellerwechsel
      long SaveHerstellerNr;
      SaveHerstellerNr = Buf_zartikel[NR_ART].HERSTELLER_NR;
      Buf_zartikel[NR_ART].HERSTELLER_NR = HerstellerNr_Alt;

      lRetCode = StoreRecord_Zaneuheit( "2", &Buf_zartikel[NR_ART],tagesdatum, errmld );
      
	  Buf_zartikel[NR_ART].HERSTELLER_NR = SaveHerstellerNr;
      
	  if ( !( lRetCode == 0 || lRetCode == 100 ) ) 
			return lRetCode;
    }

	/* ArtNrBl (auch bei Änderungen!) */
	lRetCode = StoreRecord_Artnrbl(artikel_nr,Buf_zartikel[NR_ART].HERSTELLER_NR,
								Buf_zartikel[NR_ART].ARTIKEL_NR_HERST, IsArtikelVorhanden, errmld );

	if ( !( lRetCode == 0 || lRetCode == 100 ) ) 
		return lRetCode;
	
	/* ----- Ausfuehren ----- */
    lRetCode = FdTransactWithoutWork( errmld );

    if ( lRetCode != 0 )
    {
       char errstr[30];
       sprintf( errstr, "\nArtikel-Nr = %ld",
                Buf_zartikel[NR_ART].ARTIKEL_NR );
       strcat( errmld, errstr );

      return lRetCode;
    }



    /* --- Protokoll --- */
    if (( !IsArtikelVorhanden ) && (!IsDCDeleted) )  /* Neuheit und keine Loeschung*/
       lRetCode = DC_ProtokolNeu( &Buf_zartikel[NR_ART], &Buf_zpreis[0], &Buf_zartaustria[NR_ART],&Buf_zartwg[1],errmld );
    else
    {
      if ( !IsDCDeleted )
      {

         lRetCode = DC_ProtokolAen( &BufOld_zartikel[NR_ART], &Buf_zpreis[1],&BufOld_zartaustria[NR_ART],&BufOld_zartwg[1],
									&Buf_zartikel[NR_ART],    &Buf_zpreis[0],&Buf_zartaustria[NR_ART],	 &Buf_zartwg[1],
		                              errmld ); 
       }
       else

         lRetCode = DC_ProtokolLoe( &BufOld_zartikel[NR_ART], errmld ); 
    }

    return lRetCode;
}


static long Transfer_Loop( long dcnr, long datum, char *ProtokolVerzeichnis,
                           char *errmld )
{
    long lRetCode;
    long lRetCode1;
    long sdbl;
	long sval;
    long anz_ueb;
    long anz_loe;
    long anz_dbl;

    struct S_ZDC dc;

    lRetCode = Zdc_Fetch( &dc, errmld );
    if ( lRetCode == 100 )
       strcpy( errmld, "Keine dc-Saetze zum Uebertragen vorhanden" );
    if ( lRetCode != 0 ) 
		return lRetCode;

    if ( DC_OpenProtokol( dcnr, ProtokolVerzeichnis, errmld ) != 0 )
    {
       return -1;
    }

    anz_ueb = 0;
    anz_loe = 0;
    anz_dbl = 0;

    lRetCode1 = 0;
    while ( lRetCode == 0 && lRetCode1 == 0 )
    {
      lRetCode1 = StartWork( errmld );
      if ( SQL_SUCCESS == lRetCode1  )
      {

        if ( strcmp(dc.DCSTATUS,DCSTATUS_FREIGEG) == 0 && *dc.NBSTATUS <= '1' )
             lRetCode1 = Do_All( &dc, datum, errmld );

		sval = 0;
		if ( NOVALUE_ERROR == lRetCode1 )
		{
		   sval = lRetCode1;
           lRetCode1 = SQL_SUCCESS;
		}

        sdbl = 0;
        if (  SQL_DOUBLE_ROW == lRetCode1|| SQL_DOUBLE_INDEX == lRetCode1 ) 
			sdbl = lRetCode1;


        if ( SQL_SUCCESS == lRetCode1 )  
           lRetCode1 = Zdc_ExecuteDelete( &dc, errmld );  

        lRetCode1 = EndWork( lRetCode1, errmld );

        if (  SQL_DOUBLE_ROW == sdbl ||  SQL_DOUBLE_INDEX == sdbl ) 
			lRetCode1 = 0;

        if ( SQL_SUCCESS == lRetCode1 )
        {

          if ( sdbl != 0 )
            anz_dbl++;
		  else if ( sval != 0 )
            anz_loe++;
          else if ( strcmp(dc.DCSTATUS,DCSTATUS_FREIGEG) == 0 &&
                    *dc.NBSTATUS <= '1' )
            anz_ueb++;
          else
            anz_loe++;

          lRetCode = Zdc_Fetch( &dc, errmld );
        }
      }
    }

    DC_CloseProtokol( SQL_SUCCESS == lRetCode1 && SQL_NOTFOUND == lRetCode, errmld );

    if ( SQL_SUCCESS != lRetCode1  )  
		return lRetCode1;
    if ( SQL_NOTFOUND  == lRetCode )
    {
      if ( anz_dbl == 0 )
         sprintf( errmld,
                  "%ld  DC-Saetze uebertragen\n" \
                  "%ld  DC-Saetze geloescht\n"   ,
                  anz_ueb,
                  anz_loe );
      else
        sprintf( errmld,
                 "%ld  DC-Saetze uebertragen\n"    \
                 "%ld  DC-Saetze geloescht\n"      \
                 "%ld  DC-Saetze noch vorhanden\n"  ,
                 anz_ueb,
                 anz_loe,
                 anz_dbl );
      return 0;
    }

    return lRetCode;
}

static long Select_Loop( long dcnr, long datum, char mode,
                         char *ProtokolVerzeichnis, char *errmld )
{
    long s;
    s = Zdc_Select( dcnr, datum, mode, errmld );
    if ( s == 0 )
    {
       s = Zdc_PrepDelete( errmld );
       if ( s == 0 )
       {
         s = Open_All( dcnr, errmld );
         if ( s == 0 )
         {
            s = Transfer_Loop( dcnr, datum, ProtokolVerzeichnis, errmld );

            Close_All();
         }
         Zdc_FreeDelete( NULL );
       }
       Zdc_CloseCs( NULL );
    }
    return s;
}


/* loop over all datacare positions */
long GenArtLoop( char *db, char *param1, char *param2, char *param3, char *param4,
                 char *spBuf )
  {
    long lDatacareNr;
    long tagesdatum;
    long lRetCode;
    char szErrmld[10];

    if ( *param3 != 'p' )
    {
      strcpy( spBuf, "p bei Protokollverzeichnis fehlt" );
      return 1;
    }

    lDatacareNr = atol( param2 );

    if ( param4 == NULL )
      tagesdatum = GetPhoDate();
    else
    {
      if ( strlen( param4 ) != 10 ||
           ConvToPhoDate ( param4, &tagesdatum, "tt.mm.jjjj" ) == 0 )
      {
         strcpy( spBuf, "Datum in der Form tt.mm.jjjj" );
         return 1;
      }
   }

    lRetCode = OpenBase( db, spBuf );
    if ( lRetCode == 0 )
    {
       lRetCode = OpenPflege( (char*)user, spBuf );
       if ( lRetCode == 0 )
       {
		  /*if ( s == 0 )
			 s = Reset_PL_C_HERSTNUM_Direkt( dcnr, buf ); */

          if ( lRetCode == 0 )
             lRetCode = Select_Loop( lDatacareNr, tagesdatum, *param1, &param3[1], spBuf );
          ClosePflege( szErrmld );

          /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
          SqlExecuteImm("update statistics medium for table zartikel" );
          SqlExecuteImm("update statistics medium for table zartaustria" );
          SqlExecuteImm("update statistics medium for table zdcart" );

       }
       CloseBase( );
    }
    return lRetCode;
   }


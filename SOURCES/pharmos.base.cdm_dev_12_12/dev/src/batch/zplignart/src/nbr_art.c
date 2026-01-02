/* --- Includes                  ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <hdatum/phodate.h>
#include <hdatum/phozeit.h>
#include "znb_gen_li.h"

/* -------  Special includes ----------------------------------------- */

#include <eklibs/sqltabs/tabsqld.h>
#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_dbas.h>
#include <eklibs/wdbups/wpp_dirt.h>

/* ------- Table definition includes -----------------------------------*/

#include <voodoo_table_header/cliart.h>
#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartswitzerland.h>	
#include <voodoo_table_header/csafetydatasheet.h>
#include <voodoo_table_header/chazardnote2article.h>
#include <voodoo_table_header/clihsatz.h>
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/zartwg.h>
#include <voodoo_table_header/ean.h>
#include <voodoo_table_header/zapflege.h>
#include <voodoo_table_header/zpznpflege.h>
#include <voodoo_table_header/bliesort.h>
#include <voodoo_table_header/artnrbl.h>
#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/pflege.h>
#include <voodoo_table_header/carticlelang.h>
#include <voodoo_table_header/csdslang.h>

#include "znb_gen_li.h"
#include "zart_gen.h"
#include "nbr_art.h"

#define L_ARTIKEL_NR 7

/* ----------------- Usage ------------------------ */

void GenArtUsage( char *spBuf, const char *spProg )
{
   strcat( spBuf, "- " );
   strcat( spBuf, spProg );
   strcat( spBuf, " 0 database lidatum  p[ProtokolVerz][datum]\n" \
                "  alle Aenderungen ohne IKS-Code mit NbStatus <= 1 generieren + Saetze loeschen.\n" );
   strcat( spBuf, "- " );
   strcat( spBuf, spProg );
   strcat( spBuf, " 1 database lidatum  p[ProtokolVerz][datum]\n" \
                "  alle Neuaufnahmen ohne IKS-Code mit NbStatus <= 1 generieren + Saetze loeschen.\n" );
   strcat( spBuf, "- " );
   strcat( spBuf, spProg );
   strcat( spBuf, " 2 database lidatum  p[ProtokolVerz][datum]\n" \
                "  alle Aenderungen mit IKS-Code und NbStatus <= 1 generieren + Saetze loeschen.\n" );
   strcat( spBuf, "- " );
   strcat( spBuf, spProg );
   strcat( spBuf, " 4 database lidatum  p[ProtokolVerz][datum]\n" \
                "  alle Neuaufnahmen mit IKS-Code und mit NbStatus <= 1 generieren + Saetze loeschen.\n" );
   
   
}
/* --------------------- rd_herst --------------------------------- */

/*void CloseHerstel( );*/

/* --------  user -------------- */

static const char* const user = "logindex"  ;

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
static char PrimekeyCond_CArtLan[100];
static char PrimekeyCond_CSafetyDataSheet[100];
static char PrimekeyCond_Zartswitzerland[100];
static char PrimekeyCond_Zapflege[100];
static char PrimekeyCond_Zean[100];
static char PrimekeyCond_Artnrbl[100];
static char PrimekeyCond_Bliesort[100];
static char PrimekeyCond_CSdsLang[100];

/* -----  Zartwg  -------------------------- */

#define MAX_WGR  3

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
   
   if ( Fd_Zartwg >= 0 ) 
	   return 0;

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

void SetPrimekeyCondition_Zartwg( int iIndex )
{
   char szFormat[50];
   sprintf( szFormat, "ARTIKEL_NR=%c%d.ld and ART='%cs'",
                    '%', L_ARTIKEL_NR, '%' );

   sprintf( PrimekeyCond_Zartwg, szFormat,
            Buf_zartwg[iIndex].ARTIKEL_NR,
            Buf_zartwg[iIndex].ART );
}

int InitRecord_Zartwg( int iIndex )
{
   strcpy( Buf_zartwg[iIndex].WARENGRUPPE, "     " );
   return 0;
}

long ReadRecord_Zartwg( int iIndex, long artikel_nr, char wg_art, char *spErrmld )
{
   long lStatus;
   char szErrstr[200];

   Buf_zartwg[iIndex].ARTIKEL_NR = artikel_nr;
   Buf_zartwg[iIndex].ART[0] = wg_art;

   SetPrimekeyCondition_Zartwg ( iIndex );
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
   {
	   if (strcmp(Buf_zartwg[iIndex].WARENGRUPPE, "     " ) != 0)
	   {
			lStatus = FdDelayInsertRecord( Fd_Zartwg, &Buf_zartwg[iIndex], PrimekeyCond_Zartwg, szErrmld );
	   }
	   else
		   lStatus = 0; // nothing to do!
   }
   else if ( SQL_SUCCESS == lStatus_Zartwg[iIndex] )
   {
       if (strcmp(Buf_zartwg[iIndex].WARENGRUPPE, "     " ) != 0)
	   {
	   	   lStatus = FdDelayUpdateRecord( Fd_Zartwg, &Buf_zartwg[iIndex], &BufOld_zartwg[iIndex], PrimekeyCond_Zartwg, szErrmld );
	   }
	   else
	   {
		   lStatus = FdDelayDeleteRecord( Fd_Zartwg, &BufOld_zartwg[iIndex], PrimekeyCond_Zartwg, szErrmld );
	   }
   }
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

   if ( !( lStatus == 0 || lStatus == 100 ) ) 
	   return -1;

   if ( lStatus == 100 )
   {
      Buf_zpznpflege.ARTIKEL_NR = artikel_nr;
      Buf_zpznpflege.DATUM      = datum;
      lStatus = FdDelayInsertRecord( Fd_Zpznpflege, &Buf_zpznpflege,
                                     PrimekeyCond, cErrmld);
   }
   return lStatus;
}

/* Generiert Matchcode aus Artikelname */

#define MC_LNG   L_ZARTIKEL_ARTIKEL_MC
#define AR_LNG  ( L_ZARTIKEL_ARTIKEL_NAME - 4 )    /* nicht die letzten 4 Stellen */

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

/* CArticleLang */
static int  Fd_CArtLang = -1;
static long lStatus_CArtLang;

static struct CARTICLELANG Buf_CArtLang;
static struct CARTICLELANG BufOld_CArtLang;


int GetBufferDesc_CArtLang( char * spErrmld )
{
   char *spTabelle = "carticlelang";
   long lStatus;
   char szErrstr[80];

   strcpy( spErrmld, "");
   if ( Fd_CArtLang >= 0 ) 
	   return 0;

   lStatus = OpenBufferDescProj( &Fd_CArtLang, spTabelle, PROJECTION_CARTICLELANG,
                                 NULL, NULL, V_PROTO_VERTEIL, szErrstr );
   if ( lStatus != 0 )
   {
     sprintf( spErrmld, "%s: %s", spTabelle, szErrstr );
     Fd_CArtLang = -1;
     return -1;
   }
   return 0;
}

int InitRecord_CArtLang(  )
{
   long lArtNr;
   lArtNr = Buf_CArtLang.ARTICLENO;
   FdInitTabBuf( Fd_CArtLang, &Buf_CArtLang );
   Buf_CArtLang.ARTICLENO = lArtNr;
   strcpy(Buf_CArtLang.LANGID, "FR");
   return 0;
}

void SetPrimekeyCondition_CArtLang (  )
{
   char format[100];
   sprintf( format, "LANGID='FR' and ARTICLENO=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond_CArtLan, format, Buf_CArtLang.ARTICLENO );
}

long ReadRecord_CArtLang( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_CArtLang.ARTICLENO = artikel_nr;
   SetPrimekeyCondition_CArtLang ( );
   lStatus = FdReadRecord( Fd_CArtLang, PrimekeyCond_CArtLan,
                           &Buf_CArtLang, errstr );

   if ( SQL_SUCCESS == lStatus  )
   {
      BufOld_CArtLang = Buf_CArtLang;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( SQL_NOTFOUND == lStatus  )
   {
      if ( InitRecord_CArtLang( ) == 0 )
      {
        BufOld_CArtLang = Buf_CArtLang;  /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );

   lStatus_CArtLang = lStatus;
   return lStatus;
}

long StoreRecord_CArtLang( long tagesdatum, char* cErrmld )
{
   long lStatus;
   char errmld[200];

   lStatus = FdIsRecordModified( Fd_CArtLang, &Buf_CArtLang, &BufOld_CArtLang, errmld );

   if (lStatus_CArtLang == 100 || lStatus == 1)
   {
  	  StoreRecord_Zpznpflege("11", Buf_CArtLang.ARTICLENO, tagesdatum, errmld );
   }

   SetPrimekeyCondition_CArtLang (  );
   if ( lStatus_CArtLang == 100 )
   {
      /* Artikel-Mc generieren */
	  strcpy( Buf_CArtLang.ARTICLEMC, MakeArtikelMc( Buf_CArtLang.ARTICLENAME ) );

	   lStatus = FdDelayInsertRecord( Fd_CArtLang, &Buf_CArtLang,
                                     PrimekeyCond_CArtLan, errmld);
   }
   else if ( lStatus_CArtLang == 0 )
   {
      lStatus = FdDelayUpdateRecord( Fd_CArtLang, &Buf_CArtLang,
                                     &BufOld_CArtLang,
                                     PrimekeyCond_CArtLan, errmld );
   }
   else
   {
     lStatus = lStatus_CArtLang;
     strcpy( cErrmld, "Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );

   return lStatus;
}
/* Filiale */
static long lGrenze = 0;

/* Zartikel */
static char CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];
static int  Fd_Zartikel = -1;
static long lStatus_Zartikel;

static struct ZARTIKEL Buf_zartikel;
static struct ZARTIKEL BufOld_zartikel;

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

int InitRecord_Zartikel(  )
{
   long lArtNr;
   lArtNr = Buf_zartikel.ARTIKEL_NR;
   FdInitTabBuf( Fd_Zartikel, &Buf_zartikel );
   InitArtikelFields( &Buf_zartikel, user );
   Buf_zartikel.ARTIKEL_NR = lArtNr;
   return 0;
}

void SetPrimekeyCondition_Zartikel (  )
{
   char format[30];
   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartikel.ARTIKEL_NR );
}

long ReadRecord_Zartikel( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_zartikel.ARTIKEL_NR = artikel_nr;
   SetPrimekeyCondition_Zartikel ( );
   lStatus = FdReadRecord( Fd_Zartikel, PrimekeyCond,
                           &Buf_zartikel, errstr );

   if ( SQL_SUCCESS == lStatus  )
   {
      BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( SQL_NOTFOUND == lStatus  )
   {
      if ( InitRecord_Zartikel( ) == 0 )
      {
        BufOld_zartikel = Buf_zartikel;  /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_Zartikel = lStatus;
   return lStatus;
}

long StoreRecord_Zartikel( char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zartikel (  );

   strcpy(Buf_zartikel.BEARBEITER, user);

   if ( lStatus_Zartikel == 100 )
   {
      /* Artikel-Mc generieren */
	  strcpy( Buf_zartikel.ARTIKEL_MC, MakeArtikelMc( Buf_zartikel.ARTIKEL_NAME ) );

	  lStatus = FdDelayInsertRecord( Fd_Zartikel, &Buf_zartikel,
                                     PrimekeyCond, errmld);

   }
   else if ( lStatus_Zartikel == 0 )
   {
      lStatus = FdDelayUpdateRecord( Fd_Zartikel, &Buf_zartikel,
                                     &BufOld_zartikel,
                                     PrimekeyCond, errmld );
   }
   else
   {
     lStatus = lStatus_Zartikel;
     strcpy( cErrmld, "Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}

/* CSdsLang */
static char CmpIndikator_CSdsLang[POSANZ_CSDSLANG + 1];
static int  Fd_CSdsLang = -1;
static long lStatus_CSdsLang_En;
static long lStatus_CSdsLang_It;
static long lStatus_CSdsLang_Fr;

static struct CSDSLANG Buf_csdslang_En;
static struct CSDSLANG BufOld_csdslang_En;

static struct CSDSLANG Buf_csdslang_It;
static struct CSDSLANG BufOld_csdslang_It;

static struct CSDSLANG Buf_csdslang_Fr;
static struct CSDSLANG BufOld_csdslang_Fr;

void FillCmpIndikator_CSdsLang()
{
	memset(CmpIndikator_CSdsLang, '1', POSANZ_CSDSLANG);
	CmpIndikator_CSdsLang[POSANZ_CSDSLANG] = '\0';
}

int GetBufferDesc_CSdsLang(char * errmld)
{
	char *tabelle = "csdslang";
	long lStatus;
	char errstr[100];

	strcpy(errmld, "");
	if (Fd_CSdsLang >= 0)
		return 0;

	FillCmpIndikator_CSdsLang();
	lStatus = OpenBufferDescProj(&Fd_CSdsLang, tabelle, PROJECTION_CSDSLANG,
		CmpIndikator_CSdsLang, NULL, V_PROTO_VERTEIL, errstr);

	if (lStatus != 0)
	{
		sprintf(errmld, "%s: %s", tabelle, errstr);
		Fd_CSdsLang = -1;
		return -1;
	}
	return 0;
}

int InitRecord_CSdsLang(struct CSDSLANG *Buf_csdslang)
{
	long nr;
	nr = Buf_csdslang->ARTICLENO;
	FdInitTabBuf(Fd_CSdsLang, Buf_csdslang);
	Buf_csdslang->ARTICLENO = nr;
	return 0;
}

void SetPrimekeyCondition_CSdsLang(struct CSDSLANG *spBuf)
{
	sprintf(PrimekeyCond_CSdsLang, "ARTICLENO=%ld and LANGID='%s'",
		spBuf->ARTICLENO, spBuf->LANGID);
}

long ReadRecord_CSdsLang(long artikel_nr, char *cErrmld, struct CSDSLANG *Buf_csdslang, struct CSDSLANG *BufOld_csdslang, long *lStatusCSdsLang)
{
	long lStatus;
	char errstr[200];

	Buf_csdslang->ARTICLENO = artikel_nr;
	SetPrimekeyCondition_CSdsLang(Buf_csdslang);
	lStatus = FdReadRecord(Fd_CSdsLang, PrimekeyCond_CSdsLang,
		Buf_csdslang, errstr);

	if (lStatus == 0)
	{
		*BufOld_csdslang = *Buf_csdslang;  /* gelesenen Satz sichern */
		strcpy(cErrmld, "");
	}
	else if (lStatus == 100)
	{
		if (InitRecord_CSdsLang(Buf_csdslang) == 0)
		{
			*BufOld_csdslang = *Buf_csdslang;  /* initial. sichern */
		}
		else
			lStatus = -1;
	}
	else
		strcpy(cErrmld, errstr);
	*lStatusCSdsLang = lStatus;

	return lStatus;
}

long StoreRecord_CSdsLang(char* cErrmld, struct CSDSLANG *Buf_csdslang, struct CSDSLANG *BufOld_csdslang, long *lStatusCsdslang)
{
	long lStatus;
	char errmld[200];

	
	lStatus = FdIsRecordModified(Fd_CSdsLang, Buf_csdslang, BufOld_csdslang, errmld);
	if (lStatus == 0)
	{
		return lStatus;
	}

	SetPrimekeyCondition_CSdsLang(Buf_csdslang);
	if (*lStatusCsdslang == 100 && Buf_csdslang->SDS_VERSION[0] != ' ')
	{
		lStatus = FdDelayInsertRecord(Fd_CSdsLang, Buf_csdslang,
			PrimekeyCond_CSdsLang, errmld);
	}
	else if (*lStatusCsdslang == 100)
		lStatus = 0;
	else if (*lStatusCsdslang == 0)
		lStatus = FdDelayUpdateRecord(Fd_CSdsLang, Buf_csdslang,
			BufOld_csdslang,
			PrimekeyCond_CSdsLang, errmld);
	else
	{
		lStatus = *lStatusCsdslang;
		strcpy(cErrmld, "Interner Fehler");
	}
	if (lStatus != 0)
		strcpy(cErrmld, errmld);
	else
		strcpy(cErrmld, "");
	return lStatus;
}

/* CSafetyDataSheet */
static char CmpIndikator_CSafetyDataSheet[POSANZ_CSAFETYDATASHEET + 1];
static int  Fd_CSafetyDataSheet = -1;
static long lStatus_CSafetyDataSheet;

static struct CSAFETYDATASHEET Buf_csafetydatasheet;
static struct CSAFETYDATASHEET BufOld_csafetydatasheet;

void FillCmpIndikator_CSafetyDataSheet ( )
{
   memset( CmpIndikator_CSafetyDataSheet, '1', POSANZ_CSAFETYDATASHEET );
   CmpIndikator_CSafetyDataSheet[POSANZ_CSAFETYDATASHEET] = '\0';
}

int GetBufferDesc_CSafetyDataSheet( char * errmld )
{
   char *tabelle = "csafetydatasheet";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_CSafetyDataSheet >= 0 ) 
	   return 0;

   FillCmpIndikator_CSafetyDataSheet();
   lStatus = OpenBufferDescProj( &Fd_CSafetyDataSheet, tabelle, PROJECTION_CSAFETYDATASHEET,
				CmpIndikator_CSafetyDataSheet, NULL, V_PROTO_VERTEIL, errstr );

   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_CSafetyDataSheet = -1;
     return -1;
   }
   return 0;
}

int InitRecord_CSafetyDataSheet(  )
{
   long nr;
   nr = Buf_csafetydatasheet.ARTICLENO;
   FdInitTabBuf( Fd_CSafetyDataSheet, &Buf_csafetydatasheet);
   Buf_csafetydatasheet.ARTICLENO = nr;

   InitCSafetyDataSheetFields( &Buf_csafetydatasheet, user );

   return 0;
}

void SetPrimekeyCondition_CSafetyDataSheet (  )
{
   char format[30];
   sprintf( format, "ARTICLENO=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond_CSafetyDataSheet, format, Buf_csafetydatasheet.ARTICLENO );
}

long ReadRecord_CSafetyDataSheet( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_csafetydatasheet.ARTICLENO = artikel_nr;
   SetPrimekeyCondition_CSafetyDataSheet (  );
   lStatus = FdReadRecord( Fd_CSafetyDataSheet, PrimekeyCond_CSafetyDataSheet,
                           &Buf_csafetydatasheet, errstr );

   if ( lStatus == 0 )
   {
      BufOld_csafetydatasheet = Buf_csafetydatasheet;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_CSafetyDataSheet( ) == 0 )
      {
        BufOld_csafetydatasheet = Buf_csafetydatasheet;  /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_CSafetyDataSheet = lStatus;
   return lStatus;
}

long StoreRecord_CSafetyDataSheet( long tagesdatum, char* cErrmld )
{
   long lStatus;
   char errmld[200];

   lStatus = FdIsRecordModified( Fd_CSafetyDataSheet, &Buf_csafetydatasheet, &BufOld_csafetydatasheet, errmld );
   if(lStatus == 0)
   {
	   return lStatus;
   }

   Buf_csafetydatasheet.DATE_CHANGED = tagesdatum;

   SetPrimekeyCondition_CSafetyDataSheet (  );
   if ( lStatus_CSafetyDataSheet == 100 )
      lStatus = FdDelayInsertRecord( Fd_CSafetyDataSheet, &Buf_csafetydatasheet,
                                     PrimekeyCond_CSafetyDataSheet, errmld);
   else if ( lStatus_CSafetyDataSheet == 0 )
      lStatus = FdDelayUpdateRecord( Fd_CSafetyDataSheet, &Buf_csafetydatasheet,
                                     &BufOld_csafetydatasheet,
                                     PrimekeyCond_CSafetyDataSheet, errmld );
   else
   {
     lStatus = lStatus_CSafetyDataSheet;
     strcpy( cErrmld, "Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}

/* CHazardnote2article */
long TransferHazardNotes( const long art_nr, const long lidatumnr, char* cErrmld )
{
	long lStatus;
	int fdLihsatz;
	long insertedHazardNotes2article;
	long insertResult;
	char selectLihsatz[100];
	char deleteLihsatz[100];
	char deleteHazardnote2article[100];
	char hazardnoteid[L_CLIHSATZ_HAZARDNOTEID + 1];
	char* pHazardNoteId;
	short i;
	struct CHAZARDNOTE2ARTICLE hazardnote2article;

	sprintf(deleteHazardnote2article, "DELETE FROM chazardnote2article WHERE articleno = %ld", art_nr);
	SqlExecuteImm(deleteHazardnote2article);

	sprintf(selectLihsatz, "SELECT hazardnoteid FROM clihsatz WHERE LINR=%ld AND phar=%ld", lidatumnr, art_nr);
	lStatus = SqlOpenCs(  &fdLihsatz, selectLihsatz ); 

	while(0 == lStatus)
	{
		lStatus = SqlFetch(fdLihsatz, 1, hazardnoteid, NULL);

		if(0 == lStatus)
		{
			pHazardNoteId = hazardnoteid;
			i=0;

			while(isalpha(hazardnoteid[i]))
			{
				pHazardNoteId++;
				++i;
			}

			memset(&hazardnote2article, 0, sizeof(hazardnote2article));

			hazardnote2article.ARTICLENO = art_nr;
			strncpy(hazardnote2article.HAZARDNOTEID, pHazardNoteId, L_CHAZARDNOTE2ARTICLE_HAZARDNOTEID);

			insertResult = SqlInsert("chazardnote2article", &insertedHazardNotes2article, &hazardnote2article, NULL);
			if (0 == insertResult)
			{
				sprintf(deleteLihsatz, "DELETE FROM clihsatz WHERE LINR=%ld AND phar=%ld and hazardnoteid='%s'", lidatumnr, art_nr, hazardnoteid);
				SqlExecuteImm(deleteLihsatz);
			}
		}
	}

	SqlCloseCs( fdLihsatz );

	return lStatus;
}

/* Zartswitzerland */
static char CmpIndikator_Zartswitzerland[POSANZ_ZARTSWITZERLAND + 1];
static int  Fd_Zartswitzerland = -1;
static long lStatus_Zartswitzerland;

static struct ZARTSWITZERLAND Buf_zartswitzerland;
static struct ZARTSWITZERLAND BufOld_zartswitzerland;

void FillCmpIndikator_Zartswitzerland ( )
{
   memset( CmpIndikator_Zartswitzerland, '1', POSANZ_ZARTSWITZERLAND );
   CmpIndikator_Zartswitzerland[POSANZ_ZARTSWITZERLAND] = '\0';
}

int GetBufferDesc_Zartswitzerland( char * errmld )
{
   char *tabelle = "zartswitzerland";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zartswitzerland >= 0 ) 
	   return 0;

   FillCmpIndikator_Zartswitzerland ( );
   lStatus = OpenBufferDescProj( &Fd_Zartswitzerland, tabelle, PROJECTION_ZARTSWITZERLAND,
                                 CmpIndikator_Zartswitzerland, NULL, V_PROTO_VERTEIL, errstr );

   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zartswitzerland = -1;
     return -1;
   }
   return 0;
}

int InitRecord_Zartswitzerland(  )
{
   long nr;
   nr = Buf_zartswitzerland.ARTIKEL_NR;
   FdInitTabBuf( Fd_Zartswitzerland, &Buf_zartswitzerland );
   Buf_zartswitzerland.ARTIKEL_NR = nr;

   InitZartswitzerlandFields( &Buf_zartswitzerland, user );

   return 0;
}

void SetPrimekeyCondition_Zartswitzerland (  )
{
   char format[30];
   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond_Zartswitzerland, format, Buf_zartswitzerland.ARTIKEL_NR );
}

long ReadRecord_Zartswitzerland( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_zartswitzerland.ARTIKEL_NR = artikel_nr;
   SetPrimekeyCondition_Zartswitzerland (  );
   lStatus = FdReadRecord( Fd_Zartswitzerland, PrimekeyCond_Zartswitzerland,
                           &Buf_zartswitzerland, errstr );

   if ( lStatus == 0 )
   {
      BufOld_zartswitzerland = Buf_zartswitzerland;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Zartswitzerland( ) == 0 )
      {
        BufOld_zartswitzerland = Buf_zartswitzerland;  /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_Zartswitzerland = lStatus;
   return lStatus;
}

long StoreRecord_Zartswitzerland( char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zartswitzerland (  );
   if ( lStatus_Zartswitzerland == 100 )
      lStatus = FdDelayInsertRecord( Fd_Zartswitzerland, &Buf_zartswitzerland,
                                     PrimekeyCond_Zartswitzerland, errmld);
   else if ( lStatus_Zartswitzerland == 0 )
      lStatus = FdDelayUpdateRecord( Fd_Zartswitzerland, &Buf_zartswitzerland,
                                     &BufOld_zartswitzerland,
                                     PrimekeyCond_Zartswitzerland, errmld );
   else
   {
     lStatus = lStatus_Zartswitzerland;
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
}

long ReadRecord_ZpreisLast( int i, long artikel_nr, char *cErrmld )
{
   long lStatus;
   char sql[150];

   lStatus = 100;
   strcpy( cErrmld, "" );

   /* Preis-Saetze lesen  */

   sprintf( sql, "select * from ZARTPREIS where ARTIKEL_NR=%ld " \
                 "order by DATUMGUELTIGAB desc",
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



/* -----  CArticlecodes  -------------------------- */

#define MAX_CODE  4

static int					Fd_Codes		= -1;

static long					lStatus_Codes	[MAX_CODE];
static struct CARTICLECODES Buf_codes		[MAX_CODE];
static struct CARTICLECODES BufOld_codes	[MAX_CODE];

static char  PrimekeyCond_Codes[150];

int GetBufferDesc_Codes( char* errmld )
{
   char *tabelle = "carticlecodes";
   long lStatus;
   char errstr[100];

   strcpy( errmld, "");
   
   if ( Fd_Codes >= 0 ) 
	   return 0;

   lStatus = OpenBufferDescProj( &Fd_Codes, tabelle, PROJECTION_CARTICLECODES,
                                 NULL, NULL, V_PROTO_VERTEIL, errstr );
   if ( lStatus != 0 )
   {
		sprintf( errmld, "%s: %s", tabelle, errstr );
		Fd_Codes = -1;
		return -1;
   }
  return 0;
}

void SetPrimekeyCondition_Codes( int iIndex )
{
   char szFormat[50];
   sprintf( szFormat, "ARTICLENO=%c%d.ld and CODE_TYPE=%cd",
                    '%', L_ARTIKEL_NR, '%' );

   sprintf( PrimekeyCond_Codes, szFormat,
			Buf_codes[iIndex].ARTICLENO,
			Buf_codes[iIndex].CODE_TYPE );

}

int InitRecord_Codes( int iIndex )
{
	memset( Buf_codes[iIndex].ARTICLE_CODE, ' ', L_CARTICLECODES_ARTICLE_CODE );
	Buf_codes[iIndex].PREFERRED_FLAG = 0;
	Buf_codes[iIndex].SERIAL_NUMBER = 0;
	return 0;
}

long ReadGrenzeByFilialNr(short filialnr, char *errmld)
{
	char sql[150];
	long lStatus;

	sprintf(sql, "select grenze_a from filiale where filialnr = %ld", filialnr);
	lStatus = SqlRead(sql, &lGrenze, NULL);

    if (lStatus != 0 && lStatus != 100)
	{
		strcpy( errmld, "grenze_a in filiale: " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

long ReadRecord_CArticlecodes( int iIndex, long artikel_nr, short code_type, char *spErrmld )
{
   long lStatus;
   char szErrstr[200];

   Buf_codes[iIndex].ARTICLENO = artikel_nr;
   Buf_codes[iIndex].CODE_TYPE = code_type;

   SetPrimekeyCondition_Codes ( iIndex);
   lStatus = FdReadRecord( Fd_Codes, PrimekeyCond_Codes,
                           &Buf_codes[iIndex], szErrstr );
   if ( lStatus == 0 )
   {
      BufOld_codes[iIndex] = Buf_codes[iIndex];  /* gelesenen Satz sichern */
      strcpy( spErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Codes(iIndex ) == 0 )
      {
        BufOld_codes[iIndex] = Buf_codes[iIndex];  /* gelesenen Satz sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( spErrmld, szErrstr );

   // Status pro Lesevorgang merken
   lStatus_Codes[iIndex] = lStatus;

   return lStatus;
}

long StoreRecord_Codes( int iIndex, long datum, char *spErrmld )
{
   long lStatus;
   char szErrmld[200];

   Buf_codes[iIndex].DATE_CHANGED = datum;
   
   SetPrimekeyCondition_Codes ( iIndex );

   if ( SQL_NOTFOUND == lStatus_Codes[iIndex]  )
   {
      if (strcmp(Buf_codes[iIndex].ARTICLE_CODE, "                         " ) != 0)
	  {
		  lStatus = FdDelayInsertRecord( Fd_Codes, &Buf_codes[iIndex], PrimekeyCond_Codes, szErrmld );
	  }
	  else
		  lStatus = 0; // nothing to do!
   }
   else if ( SQL_SUCCESS == lStatus_Codes[iIndex] )
   {
	  if (strcmp(Buf_codes[iIndex].ARTICLE_CODE, "                         " ) != 0)
	  {
		  lStatus = FdDelayUpdateRecord( Fd_Codes, &Buf_codes[iIndex], &BufOld_codes[iIndex], PrimekeyCond_Codes, szErrmld );
	  }
	  else
	  {
		  lStatus = FdDelayDeleteRecord( Fd_Codes, &BufOld_codes[iIndex], PrimekeyCond_Codes, szErrmld );
	  }
   }
   else
   {
     lStatus = lStatus_Codes[iIndex];
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

   sprintf( PrimekeyCond_Zapflege, "ARTIKEL_NR=%ld and DATUM=%ld",
                          Buf_zapflege.ARTIKEL_NR,
                          Buf_zapflege.DATUM );

   lStatus = FdReadRecord( Fd_Zapflege, PrimekeyCond_Zapflege,
                           &Buf_zapflege, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) 
	   return -1;

   if ( lStatus == 100 )
   {
      Buf_zapflege.ARTIKEL_NR = artikel_nr;
      Buf_zapflege.DATUM      = datum;
      lStatus = FdDelayInsertRecord( Fd_Zapflege, &Buf_zapflege,
                                     PrimekeyCond_Zapflege, cErrmld);
   }
   return lStatus;
}


/* -----  Ean     ------------------------- */

static int  Fd_Zean = -1;
static long lStatus_Zean;

static struct EAN Buf_zean;
static struct EAN BufOld_zean;

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
   sprintf( PrimekeyCond_Zean, format, Buf_zean.ARTIKEL_NR );
}

long ReadRecord_Zean( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_zean.ARTIKEL_NR = artikel_nr;

   SetPrimekeyCondition_Zean ( );
   lStatus = FdReadRecord( Fd_Zean, PrimekeyCond_Zean,
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

long StoreRecord_Zean( char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zean ( );
   if ( lStatus_Zean == 100 )
      lStatus = FdDelayInsertRecord( Fd_Zean, &Buf_zean,
                                     PrimekeyCond_Zean, errmld);
   else if ( lStatus_Zean == 0 )
      lStatus = FdDelayUpdateRecord( Fd_Zean, &Buf_zean,
                                     &BufOld_zean,
                                     PrimekeyCond_Zean, errmld );
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
/* -----  Artnrbl  ------------------------- */

static int  Fd_Artnrbl = -1;

static struct ARTNRBL Buf_artnrbl;
static struct ARTNRBL Buf_artnrbl_old;

int GetBufferDesc_Artnrbl( char * errmld )
{
   char *tabelle = "artnrbl";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Artnrbl >= 0 ) 
	   return 0;

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

long StoreRecord_Artnrbl( long artikel_nr, long besla_nr, char* artnrbl, char* cErrmld )
{
   long lStatus;

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond_Artnrbl, "ARTIKEL_NR=%ld and BESLA_NR=%ld",
                          artikel_nr,
                          besla_nr );

   lStatus = FdReadRecord( Fd_Artnrbl, PrimekeyCond_Artnrbl,
                           &Buf_artnrbl_old, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) 
	   return -1;

   FdInitTabBuf( Fd_Artnrbl, &Buf_artnrbl );
   Buf_artnrbl.ARTIKEL_NR = artikel_nr;
   Buf_artnrbl.BESLA_NR  = besla_nr;
   Trim(artnrbl);
   strcpy(Buf_artnrbl.ARTIKEL_NR_BLIEFER,artnrbl);
   
   if ( lStatus == 100 )
   {
      if ( strcmp(artnrbl, "") != 0)  // insert nur, wenn auch ein Wert gesetzt ist!
	  { 
		lStatus = FdDelayInsertRecord( Fd_Artnrbl, &Buf_artnrbl,
										PrimekeyCond_Artnrbl, cErrmld);
	  }
	  else
		  lStatus = 0;
   }
   else
   {
	  if ( strcmp(artnrbl, "") != 0)
	  {
		  // update
		 lStatus = FdDelayUpdateRecord( Fd_Artnrbl, &Buf_artnrbl, &Buf_artnrbl_old,
												PrimekeyCond_Artnrbl, cErrmld);
	  }
	  else
	  {
		// löschen
		  lStatus = FdDelayDeleteRecord( Fd_Artnrbl, &Buf_artnrbl_old,
										PrimekeyCond_Artnrbl, cErrmld);
	  }
   }

   return lStatus;
}

/* -----  bliesort  ------------------------- */
/* ------------------------------------------------------------------- */
static char  PflegeTab[] = "pflege";
static void *PflDesc  = NULL;

/* ------------------------------------------------------------------- */
long InitPflegeTab( char *errmld )
{
    static int alloc_status = 0;
    static long s;
    static char smeld[80];
    if ( alloc_status == 0 )
    {
        alloc_status = 1;
        s = SqlGetTabDesc( PflegeTab, &PflDesc, DESC_DEFAULT, smeld );
    }
    if ( s != 0 )
    {
        PflDesc = NULL;
        strcpy( errmld, smeld );
    }
    return s;
}

/* ------------------------------------------------------------------- */
void ClosePflegeTab( )
{
    if ( PflDesc != NULL )
    {
        SqlFreeTabDesc ( PflDesc );
        PflDesc = NULL;
    }
}

/* ------------------------------------------------------------------- */
long InsertPflegePhysically( struct PFLEGE *Buf_Pflege )

{
	char sql[300];
	sprintf( sql, "insert into pflege " \
		          "(PFLEGE_NR, DATUM, UHRZEIT, ANWENDER, STATUS, FEHLERTEXT, FUNKTION, INFO) values " \
				  "(%ld, %ld, %ld, '%s', '%s', '%s', %d, '%s')",
				  Buf_Pflege->PFLEGE_NR,
				  Buf_Pflege->DATUM,
				  Buf_Pflege->UHRZEIT,
				  Buf_Pflege->ANWENDER,
				  Buf_Pflege->STATUS,
				  Buf_Pflege->FEHLERTEXT,
				  Buf_Pflege->FUNKTION,
				  Buf_Pflege->INFO );
	return SqlExecuteImm( sql );
}

/* ------------------------------------------------------------------- */
long Insert_Pflege( long besla_nr, long artikel_nr )
{
    long s;
    struct PFLEGE  Buf_Pflege;
	char key_select[15];
	char errmld[100];
	
    Buf_Pflege.PFLEGE_NR = 0;
    Buf_Pflege.DATUM     = GetPhoDate();
    Buf_Pflege.UHRZEIT   = GetPhoTime();
    strcpy( Buf_Pflege.ANWENDER, "zplignar" );
    strcpy( Buf_Pflege.STATUS, "0" );
    strcpy( Buf_Pflege.FEHLERTEXT, " " );
    Buf_Pflege.FUNKTION = 1;
    sprintf( Buf_Pflege.INFO, "%ld %ld", artikel_nr, besla_nr );

    strcpy( key_select, "pflege_nr=0");

    s = Insert_Protokoll( P_INSERT, V_PROTO_VERTEIL, PflDesc,
                          &Buf_Pflege, &Buf_Pflege,
                          key_select, "zplignar", "", 0, errmld );

	if ( s == 0 )
		s = InsertPflegePhysically( &Buf_Pflege );

    return s;
}

static int  Fd_Bliesort = -1;

static struct BLIESORT Buf_bliesort;
static struct BLIESORT Buf_bliesortOld;

int GetBufferDesc_Bliesort( char * errmld )
{
   char *tabelle = "bliesort";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Bliesort >= 0 ) 
	   return 0;

   lStatus = OpenBufferDescProj( &Fd_Bliesort, tabelle, PROJECTION_BLIESORT,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );

   InitPflegeTab( errmld );

   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Bliesort = -1;
     return -1;
   }
   return 0;
}

long Read_Bliesort ( long artikel_nr, long besla_nr, char* cErrmld )
{
   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond_Bliesort, "ARTIKEL_NR=%ld and BESLA_NR=%ld",
                          artikel_nr,
                          besla_nr );

   return FdReadRecord( Fd_Bliesort, PrimekeyCond_Bliesort,
                           &Buf_bliesortOld, cErrmld );
}

long StoreRecord_Bliesort( long artikel_nr, long besla_nr, long besla_nr_old, char* cErrmld )
{
   long lStatus;

   lStatus = Read_Bliesort (artikel_nr, besla_nr_old, cErrmld);

   if ( !( lStatus == 0 || lStatus == 100 ) ) 
	   return -1;

   if ( lStatus == 100 )
   {
		// nochmal lesen, ob bliesort bereits für die neue besla_nr vorhanden ist?
	    // dürfte eigentlich nicht passieren, aber sicher ist sicher !
		lStatus = Read_Bliesort (artikel_nr, besla_nr, cErrmld);
   }

   if ( !( lStatus == 0 || lStatus == 100 ) ) 
	   return -1;

   FdInitTabBuf( Fd_Bliesort, &Buf_bliesort );
   Buf_bliesort.ARTIKEL_NR = artikel_nr;
   Buf_bliesort.BESLA_NR   = besla_nr;

   if ( lStatus == 100 )
   {
   	  lStatus = FdDelayInsertRecord( Fd_Bliesort, &Buf_bliesort, PrimekeyCond_Bliesort, cErrmld);
   }
   else
   {
	  // I-18054998 --> has to be checked, as it seems, that bliesort is not updated properly ...
	   lStatus = FdDelayUpdateRecord( Fd_Bliesort, &Buf_bliesort, &Buf_bliesortOld, PrimekeyCond_Bliesort, cErrmld);
   }

   Insert_Pflege( besla_nr, artikel_nr );

   return lStatus;
}

/* ---------------------------------------------------------------------- *
 * Funktion         cliart lesen                                          *
 * ---------------------------------------------------------------------- */

#define S_CLI CLIART

static char *cli_proj = "*";

static int fd_cli_sel = -1;
static int fd_cli_del = -1;


/* read logindex table  */
static long Cli_Select( long linr, long datum, char mode, char *errmld )
{
    long s;
    char sql[500];

    /* Select unabhaengig vom liSTATUS / NBSTATUS */
    /* das bedeutet: alle Saetze im Datumsbereich werden geloescht */
    /*    nur die Saetze mit liSTATUS = liSTATUS_FREIGEGEBEN */
    /*                   und NBSTATUS <= '1'  werden uebernommen */
    /*    diese Auswahl geschieht vor Do_All */

    if ( mode == '0' )				/* Nicht-IKS-Änderungen */
	{
      sprintf( sql,
          "select %s from CLIART where LINR=%ld "  \
		  "and SMCAT not in ('A', 'B', 'C', 'D', 'E') and ZAENDERUNG != '0' "
          "order by LINR,PHAR",
          cli_proj,
          linr);
	}
    else if ( mode == '1' )        /* Nicht-IKS-Neuaufnahmen */
	{
      sprintf( sql,
          "select %s from CLIART where LINR=%ld and "  \
          "ZAENDERUNG='0' and SMCAT not in ('A', 'B', 'C', 'D', 'E') " \
          "order by LINR,PHAR",
          cli_proj,
          linr );
	}
	else if ( mode == '2' )				/* IKS- Änderungen */
	{
      sprintf( sql,
          "select %s from CLIART where LINR=%ld and "  \
		  "SMCAT in ('A', 'B', 'C', 'D', 'E') and ZAENDERUNG != '0' " \
          "order by LINR,PHAR",
          cli_proj,
          linr);
	}
	else if ( mode == '4' )        /* alle relevanten IKS- Neuaufnahmen */
	{
      sprintf( sql,
          "select %s from CLIART where LINR=%ld and "  \
          "ZAENDERUNG='0' and SMCAT in ('A', 'B', 'C', 'D', 'E') " \
          "order by LINR,PHAR",
          cli_proj,
          linr );
	}
	

    s = SqlOpenCsWh( &fd_cli_sel, sql );
    if ( s != 0 )
    {
      fd_cli_sel = -1;
      sprintf( errmld, "CLIART: %s", DynErrmld() );
    }
    return s;
}

static long Cli_Fetch( struct S_CLI *li, char *errmld )
{
    long s;
    s = SqlFetch( fd_cli_sel, 1, li, NULL );
    if ( s != 0 )
      sprintf( errmld, "CLIART: %s", DynErrmld() );
    return s;
}

static long Cli_CloseCs( char *errmld )
{
    long s;
    if ( fd_cli_sel == -1 ) return 0;
    s = SqlCloseCs( fd_cli_sel );
    if ( s != 0 && errmld != NULL )
       sprintf( errmld, "CLIART: %s", DynErrmld() );
    fd_cli_sel = -1;
    return s;
}

static long Cli_PrepDelete( char *errmld )
{
    long s;
    s = SqlPrepareStmnt ( &fd_cli_del,
                          "delete from CLIART where LINR=? and SATZNR=?",
                          "CLIART.LINR", "CLIART.SATZNR", NULL );
    if ( s != 0 )
    {
      fd_cli_del = -1;
      sprintf( errmld, "CLIART PrepDelete: %s", DynErrmld() );
    }
    return s;
}

static long Cli_ExecuteDelete( struct S_CLI *li, char *errmld )
{
    long s;
    long linr;
    long satznr;
    linr  = li->LINR;
    satznr = li->SATZNR;
    s = SqlExecutePrepare( fd_cli_del, &linr, &satznr, NULL );
    if ( s != 0 )
      sprintf( errmld, "CLIART ExecDelete: %s", DynErrmld() );
    return s;
}

static long Cli_FreeDelete( char *errmld )
{
    long s;
    if ( fd_cli_del == -1 )  return 0;
    s = SqlFreePrepare( fd_cli_del );
    if ( s != 0 && errmld != NULL )
        sprintf( errmld, "CLIART FreeDelete: %s", DynErrmld() );
    fd_cli_del = -1;
    return s;
}

static long StartWork( char *spErrmld )
  {
    long lRetCode;
    lRetCode = SqlBeginWork( );
    if ( lRetCode != 0 )
      {
        strcpy( spErrmld, "logindex uebertragen: " );
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
            strcpy( spErrmld, "logindex uebertragen: " );
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

static long Open_All( char *cErrmld )
{
    if ( 0 != GetBufferDesc_Zartikel     ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Zartswitzerland(cErrmld)) return -1;
    if ( 0 != GetBufferDesc_Zpreis       ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Codes        ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Zapflege     ( cErrmld )) return -1;
	if ( 0 != GetBufferDesc_Zpznpflege   ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Bliesort     ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_Artnrbl		 ( cErrmld )) return -1;
	if ( 0 != GetBufferDesc_CArticleCodes( cErrmld )) return -1;
	if ( 0 != GetBufferDesc_Zean         ( cErrmld )) return -1;
	if ( 0 != GetBufferDesc_CArtLang     ( cErrmld )) return -1;
	if ( 0 != GetBufferDesc_Zartwg	     ( cErrmld )) return -1;
    if ( 0 != GetBufferDesc_CSafetyDataSheet(cErrmld)) return -1;
	if ( 0 != GetBufferDesc_CSdsLang	 (cErrmld))   return -1;
	
    return 0;
}

static void Close_All(  )
{
	ClosePflegeTab( );
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

	// LI-Price 0.00 or 0.01 
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

static long Do_All( struct S_CLI *spLIBuf, long tagesdatum, char *errmld )
{
    long lRetCode;
    long s1;
    long artikel_nr;
    int  ToStorePreis;
	int  IsArtikelVorhanden;
	char stmt [100] = {0};

	/* ZArtikel */
    artikel_nr =  spLIBuf->PHAR;
    lRetCode = ReadRecord_Zartikel( artikel_nr, errmld );
    
	if ( !( lRetCode == 0 || lRetCode == 100 ) ) 
		return lRetCode;

	IsArtikelVorhanden = lRetCode == 0;

    /* ZArtSwitzerland */
    lRetCode = ReadRecord_Zartswitzerland( artikel_nr, errmld );

	/* carticlelang */
    lRetCode = ReadRecord_CArtLang( artikel_nr, errmld );

	/* CSafetyDataSheet*/
	lRetCode = ReadRecord_CSafetyDataSheet( artikel_nr, errmld );

	/* CSdsLang*/
	strcpy(Buf_csdslang_En.LANGID, "EN");
	strcpy(Buf_csdslang_It.LANGID, "IT");
	strcpy(Buf_csdslang_Fr.LANGID, "FR");
	lRetCode = ReadRecord_CSdsLang(artikel_nr, errmld, &Buf_csdslang_En, &BufOld_csdslang_En, &lStatus_CSdsLang_En);
	lRetCode = ReadRecord_CSdsLang(artikel_nr, errmld, &Buf_csdslang_It, &BufOld_csdslang_It, &lStatus_CSdsLang_It);
	lRetCode = ReadRecord_CSdsLang(artikel_nr, errmld, &Buf_csdslang_Fr, &BufOld_csdslang_Fr, &lStatus_CSdsLang_Fr);

	/* Zartwg */
	ReadRecord_Zartwg( 0, artikel_nr, '2',errmld );
	ReadRecord_Zartwg( 1, artikel_nr, '5',errmld );
	ReadRecord_Zartwg( 2, artikel_nr, 'A',errmld );


	/* ----- LI-Werte nach Warengruppe ----- */
	// --> diese Felder kommen nicht von LI und sind im Dialog immer editierbar --> auch immer übernehmen / kein Änderungs-KZ vorhanden!
	LISatzToArtWgr2( spLIBuf, &Buf_zartwg[0] );
	LISatzToArtWgr5( spLIBuf, &Buf_zartwg[1] );
	LISatzToArtWgrA( spLIBuf, &Buf_zartwg[2] );
	
	/* CArticlecodes */
	if ( !IsArtikelVorhanden || !IsNotChanged( spLIBuf, PL_ATC ))
	{
		ReadRecord_CArticlecodes( 0, artikel_nr, 2, errmld );	// ATC
		LISatzToCodeATC( spLIBuf, &Buf_codes[0] );

		lRetCode = StoreRecord_Codes(0, tagesdatum, errmld);
		if ( lRetCode != 0 ) 
			return lRetCode;
	}

	if ( !IsArtikelVorhanden || !IsNotChanged( spLIBuf, PL_BAGNO ))
	{
		ReadRecord_CArticlecodes( 1, artikel_nr, 4, errmld );	// BAGNO
		LISatzToCodeBAG( spLIBuf, &Buf_codes[1] );

		lRetCode = StoreRecord_Codes(1, tagesdatum, errmld);
		if ( lRetCode != 0 )
			return lRetCode;
	}

	if ( !IsArtikelVorhanden || !IsNotChanged( spLIBuf, PL_CDSO1 ))
	{
		ReadRecord_CArticlecodes( 2, artikel_nr, 21, errmld );	// CDSO1
		LISatzToCodeCDSO(spLIBuf, &Buf_codes[2] );

		lRetCode = StoreRecord_Codes(2, tagesdatum, errmld);
		if ( lRetCode != 0 ) 
			return lRetCode; 
	}

	if ( !IsArtikelVorhanden || !IsNotChanged( spLIBuf, PL_GTIN14 ))
	{
		ReadRecord_CArticlecodes( 3, artikel_nr, 19, errmld );	// Ersatz-Barcode
		LISatzToCodeGtin14(spLIBuf, &Buf_codes[3] );
		
		Trim(spLIBuf->GTIN14);
		if ( TestEanNr( spLIBuf->GTIN14 ) == 1 )
		{
			lRetCode = StoreRecord_Codes(3, tagesdatum, errmld);
			if ( lRetCode != 0 ) 
				return lRetCode; 
		}
	}

	/* - Grenze lesen wegen Skontofähigkeit - */
	ReadGrenzeByFilialNr(0, errmld);

	/* ----- LI-Werte nach Artikelsatz ----- */
	LISatzToArtikel( spLIBuf, &Buf_zartikel, &BufOld_zartikel, &Buf_CArtLang, IsArtikelVorhanden );

	/* ----- LI-Werte nach Artikelsatz Switz ----- */
    LISatzToArtikelSwitz( spLIBuf, &Buf_zartswitzerland, &Buf_zartikel, IsArtikelVorhanden );

	/* ----- LI-Werte nach CSafetyDataSheet ----- */
	LISatzToCSafetyDataSheet( spLIBuf, &Buf_csafetydatasheet, &Buf_zartikel, IsArtikelVorhanden );

	if ( !IsArtikelVorhanden || !IsNotChanged( spLIBuf, PL_DSCRLONGD ) )
		StoreRecord_Zpznpflege("33", artikel_nr, tagesdatum, errmld );

	// für ZdpDruck die HNR zurück in clioart schreiben
	sprintf ( stmt, "update clioart set hersteller_nr = %ld where phar = %ld",
					Buf_zartikel.HERSTELLER_NR, Buf_zartikel.ARTIKEL_NR );
	SqlExecuteImm( stmt );

	/* ---- carticlelang ---- */
	lRetCode = StoreRecord_CArtLang( tagesdatum, errmld );
    if ( lRetCode != 0 ) 
		return lRetCode;

	/* ----- ZArtSwitzerland  ----- */
    lRetCode = StoreRecord_Zartswitzerland( errmld );
    if ( lRetCode != 0 ) 
		return lRetCode;

	/* ----- CSafetyDataSheet  ----- */
    lRetCode = StoreRecord_CSafetyDataSheet(tagesdatum, errmld );
    if ( lRetCode != 0 ) 
		return lRetCode;

	/* ----- CSdsLang EN ----- */
	if (IsArtikelVorhanden == 0 || IsNotChanged(spLIBuf, PL_SDS_DATE_EN) == 0)
	{
		strcpy(Buf_csdslang_En.LANGID, "EN");
		ConvFromPhoDate(Buf_csdslang_En.SDS_VERSION, spLIBuf->SDS_DATE_EN, "tt.mm.jjjj");
		LISatzToCSdsLang(spLIBuf, &Buf_csdslang_En);
	}
	
	lRetCode = StoreRecord_CSdsLang(errmld, &Buf_csdslang_En, &BufOld_csdslang_En, &lStatus_CSdsLang_En);
	if (lRetCode != 0)
		return lRetCode;

	/* ----- CSdsLang IT ----- */
	if (IsArtikelVorhanden == 0 || IsNotChanged(spLIBuf, PL_SDS_DATE_IT) == 0)
	{
		strcpy(Buf_csdslang_It.LANGID, "IT");
		ConvFromPhoDate(Buf_csdslang_It.SDS_VERSION, spLIBuf->SDS_DATE_IT, "tt.mm.jjjj");
		LISatzToCSdsLang(spLIBuf, &Buf_csdslang_It);
	}
	
	lRetCode = StoreRecord_CSdsLang(errmld, &Buf_csdslang_It, &BufOld_csdslang_It, &lStatus_CSdsLang_It);
	if (lRetCode != 0)
		return lRetCode;

	/* ----- CSdsLang FR ----- */
	if (IsArtikelVorhanden == 0 || IsNotChanged(spLIBuf, PL_SDS_DATE_FR) == 0)
	{
		strcpy(Buf_csdslang_Fr.LANGID, "FR");
		ConvFromPhoDate(Buf_csdslang_Fr.SDS_VERSION, spLIBuf->SDS_DATE_FR, "tt.mm.jjjj");
		LISatzToCSdsLang(spLIBuf, &Buf_csdslang_Fr);
	}
	
	lRetCode = StoreRecord_CSdsLang(errmld, &Buf_csdslang_Fr, &BufOld_csdslang_Fr, &lStatus_CSdsLang_Fr);
	if (lRetCode != 0)
		return lRetCode;

	/* ----- Hazardnotes  ----- */
	lRetCode = TransferHazardNotes( artikel_nr, spLIBuf->LINR, errmld );
	if ( lRetCode != 0 && lRetCode != 100) 
		return lRetCode;

	/* ----- Zartwg  ----- */ 
	lRetCode = StoreRecord_Zartwg(0, errmld);
	if ( lRetCode != 0 ) 
		return lRetCode;

	lRetCode = StoreRecord_Zartwg(1, errmld);
	if ( lRetCode != 0 ) 
		return lRetCode;

	lRetCode = StoreRecord_Zartwg(2, errmld);
	if ( lRetCode != 0 ) 
		return lRetCode;
	
	/* ---- Preise ---- */
	s1 =  ReadRecord_ZpreisLast( 1, artikel_nr, errmld ); /* preis 1 */
	
	if ( !( s1 == 0 || s1 == 100 ) ) 
		return -1;

	if (spLIBuf->VDAT == 0)
		spLIBuf->VDAT = tagesdatum;

	Buf_zpreis[0].ARTIKEL_NR = spLIBuf->PHAR;
	Buf_zpreis[0].DATUMGUELTIGAB = spLIBuf->VDAT;
	lRetCode = ReadRecord_Zpreis( 0, errmld );              /* preis 0 */
	if ( !( lRetCode == 0 || lRetCode == 100 ) )
		return -1;

	Buf_zpreis[0] = Buf_zpreis[1];
	Buf_zpreis[0].ARTIKEL_NR = spLIBuf->PHAR;
	Buf_zpreis[0].DATUMGUELTIGAB = spLIBuf->VDAT;	

	ToStorePreis = 0;
	// Preisänderung oder noch kein Preis vorhanden
	if ( IsPreisChanged( spLIBuf, &Buf_zpreis[1] ) || (SQL_NOTFOUND == s1) )
	{
		/* LI-Preise uebernehmen */
		int preisWirdUebernommen = LISatzToPreis( spLIBuf, &Buf_zpreis[0], &Buf_zartikel, &Buf_zartswitzerland, IsArtikelVorhanden );

		if ( 0 == preisWirdUebernommen )
		{
			if ( s1 == 0 )  /* alter Preis vorhanden */
			{
				if ( Buf_zpreis[0].DATUMGUELTIGAB < Buf_zpreis[1].DATUMGUELTIGAB )
					ToStorePreis = 0;   /* Preisdatum zu alt */
				else
				{
					ToStorePreis = !IsPreisGleich( &Buf_zpreis[0], &Buf_zpreis[1] );
				}
			}
			else
				ToStorePreis = 1;
		}

		if ( ToStorePreis )
		{
			if ( Buf_zpreis[0].DATUMGUELTIGAB <= tagesdatum )
			{
				Buf_zpreis[0].DATUMGUELTIGAB = AddDayToPhoDate(tagesdatum, 1); // keine Preise in der Vergangenheit einspielen !!! 
				lStatus_Zpreis[0] = 100; // ansonsten führt zu Fehlern beim Update, wenn vorher ein Preis mit dem Datum in der Vergangenheit eingelesen wurde und nun mit dem neuen Datum upgedatet werden soll ...
			}
				
			lRetCode = StoreRecord_Zpreis( 0, errmld );
			if ( lRetCode != 0 ) 
				return lRetCode;

			// zapflege auch mit Preisdatum (in der Zukunft) schreiben -->  SR-17028701
			StoreRecord_Zapflege( artikel_nr, Buf_zpreis[0].DATUMGUELTIGAB, errmld );

			/* - Skontofähigkeit setzen wenn GEP die Grenze überschreitet - */
			if(Buf_zpreis[0].GROSSO > lGrenze)
				strcpy(Buf_zartikel.SKONTOFAEHIG, "0");
		}
		else
			Buf_zpreis[0] = Buf_zpreis[1];  /* Keine Änderungen übernommen*/
	}
	else
		Buf_zpreis[0] = Buf_zpreis[1];		/* Keine Preisänderung*/

	/* ----- Zartikel (erst nach Preisen, da herst_prozent sich dabei noch ändern kann!) ----- */
    lRetCode = StoreRecord_Zartikel( errmld );
    if ( lRetCode != 0 ) 
		return lRetCode;

	if ( !IsArtikelVorhanden )   /* Neuanlage */
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

		lRetCode = StoreRecord_Zpznpflege("34", artikel_nr, tagesdatum, errmld );
	    
		if ( lRetCode != 0 ) 
			return lRetCode;
	}

    /* ---- Zapflege ---- */
    lRetCode = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
    
	if ( !( lRetCode == 0 || lRetCode == 100 ) ) 
		return lRetCode;

	// wenn AH- Datum in der Zukunft, dann auch einen Eintrag mit diesem Datum in zapflege schreiben
	if (Buf_zartikel.DATUM_AH > tagesdatum)
		StoreRecord_Zapflege( artikel_nr, Buf_zartikel.DATUM_AH, errmld );

	/* ---- Bliesort / ArtnrBl ---- */ 
    if ( !IsArtikelVorhanden )   /* Neuanlage --> bliesort + artnrbl noch nicht vorhanden! */ 
    {
	  /* Bliesort */ 
		int beslanr;

		if (Buf_zartikel.AWL1 > 0)
			beslanr = Buf_zartikel.AWL1;
		else
			beslanr = Buf_zartikel.HERSTELLER_NR; // TH an sich ist das falsch = darf nicht die HNR sein!

		lRetCode = StoreRecord_Bliesort(artikel_nr, beslanr, Buf_zartikel.HERSTELLER_NR, errmld );
     
		if ( !( lRetCode == 0 || lRetCode == 100 ) ) 
			return lRetCode;
		  
		/* ArtNrBl */
		lRetCode = StoreRecord_Artnrbl(artikel_nr, beslanr, Buf_zartikel.ARTIKEL_NR_HERST, errmld );
			
		if ( !( lRetCode == 0 || lRetCode == 100 ) ) 
				return lRetCode;
	}
	else // Artikel- Änderung
	{
		int beslanr;

		if (Buf_zartikel.AWL1 > 0)
			beslanr = Buf_zartikel.AWL1;
		else
			beslanr = Buf_zartikel.HERSTELLER_NR;

		if ((Buf_zartikel.AWL1 != BufOld_zartikel.AWL1) ||
			(Buf_zartikel.HERSTELLER_NR != BufOld_zartikel.HERSTELLER_NR && Buf_zartikel.AWL1 == 0)  ||								// HNR geändert, AWL1 nicht gesetzt
			(strcmp(Buf_zartikel.ARTIKEL_NR_HERST, BufOld_zartikel.ARTIKEL_NR_HERST) != 0 && !IsNotChanged( spLIBuf, PL_COMPNO ) ))	// ArtNrHerst geändert
		{
			// zunächst alte Einträge löschen, wenn zartikel.hersteller_nr / awl1 geändert wurde
			if ((Buf_zartikel.AWL1 != BufOld_zartikel.AWL1) ||
				(Buf_zartikel.HERSTELLER_NR != BufOld_zartikel.HERSTELLER_NR && Buf_zartikel.AWL1 == 0) )
			{
				char sql [100] = {0};

				int beslanrOld;

				if (BufOld_zartikel.AWL1 > 0)
					beslanrOld = BufOld_zartikel.AWL1;
				else
					beslanrOld = BufOld_zartikel.HERSTELLER_NR; // TH an sich ist das falsch = darf nicht die HNR sein!
	
				sprintf ( sql, "delete from artnrbl where besla_nr = %ld and artikel_nr = %ld",
								beslanrOld, BufOld_zartikel.ARTIKEL_NR );

				SqlExecuteImm( sql );

				// Versorgung Tabelle bliesort, wenn zartikel.hersteller_nr geändert wurde 
				lRetCode = StoreRecord_Bliesort(artikel_nr, beslanr, beslanrOld, errmld );
			     
				if ( !( lRetCode == 0 || lRetCode == 100 ) ) 
					return lRetCode;
			}
		}

		lRetCode = StoreRecord_Artnrbl(artikel_nr, beslanr, Buf_zartikel.ARTIKEL_NR_HERST, errmld );
		
		if ( !( lRetCode == 0 || lRetCode == 100 ) ) 
				return lRetCode;
	}

	/* ---- EAN ---- */
    if ( !IsArtikelVorhanden || !IsNotChanged( spLIBuf, PL_BC ) ) 
	{
		lRetCode = ReadRecord_Zean( artikel_nr, errmld );
        if ( !( lRetCode == 0 || lRetCode == 100 ) ) 
			return lRetCode;

		Trim(spLIBuf->BC);
		if ( strcmp(Buf_zean.EAN_NR, spLIBuf->BC) != 0 && TestEanNr( spLIBuf->BC ) == 1 )
		{
			Buf_zean.ARTIKEL_NR = artikel_nr;

			strcpy( Buf_zean.EAN_NR, spLIBuf->BC );
			lRetCode = StoreRecord_Zean( errmld );
			
			if ( lRetCode != 0 ) 
				return lRetCode;

			//TH vorher hier auch noch einmal prüfen, ob die EAN nicht bereits einer anderen PZN zugeordnet ist !? SR-14027643

			lRetCode = StoreRecord_Zpznpflege("09", artikel_nr, tagesdatum, errmld );
	    
			if ( lRetCode != 0 ) 
				return lRetCode;
		}
	} 

	/* ----- Ausfuehren ----- */
    lRetCode = FdTransactWithoutWork( errmld );

    if ( lRetCode != 0 )
    {
       char errstr[30];
       sprintf( errstr, "\nArtikel-Nr = %ld",
                Buf_zartikel.ARTIKEL_NR );
       strcat( errmld, errstr );

      return lRetCode;
    }

    /* --- Protokoll --- */
    if ( !IsArtikelVorhanden )  /* Neuheit und keine Loeschung*/
       lRetCode = LI_ProtokolNeu( &Buf_zartikel, &Buf_zpreis[0], &Buf_zartswitzerland, &Buf_zean, errmld );
    else
    {
       lRetCode = LI_ProtokolAen( &BufOld_zartikel, &Buf_zpreis[1],  &BufOld_zartswitzerland, &BufOld_zean, 
									&Buf_zartikel,  &Buf_zpreis[0],  &Buf_zartswitzerland,  &Buf_zean, errmld ); 
      //   lRetCode = LI_ProtokolLoe( &BufOld_zartikel, errmld ); 
    }

	/* ---- Ersatz_Nr bei Vorgänger eintragen ---- */
	if ( !IsNotChanged( spLIBuf, PL_PHAR2 ) && spLIBuf->PHAR2 > 0) 
	{
		if ( 0 == ReadRecord_Zartikel( spLIBuf->PHAR2, errmld ) )
		{
			Buf_zartikel.ERSATZ_NR = spLIBuf->PHAR;
			strcpy(Buf_zartikel.ERSATZ_NR_AKTIV, "1");
			Buf_zartikel.DATUM_IFAAENDER = spLIBuf->LINR;
			Buf_zartikel.DATUM_AENDER = GetPhoDate();

			if ( 0 == StoreRecord_Zartikel( errmld ) )
			{
				StoreRecord_Zapflege( spLIBuf->PHAR2, tagesdatum, errmld );

				FdTransactWithoutWork( errmld );
			}
		}
	}

    return lRetCode;
}


static long Transfer_Loop( long linr, long datum, char *ProtokolVerzeichnis,
                           char *errmld )
{
    long lRetCode;
    long lRetCode1;
    long sdbl;
	long sval;
    long anz_ueb;
    long anz_loe;
    long anz_dbl;

    struct S_CLI li;

    lRetCode = Cli_Fetch( &li, errmld );
    if ( lRetCode == 100 )
       strcpy( errmld, "Keine li-Saetze zum Uebertragen vorhanden" );
    if ( lRetCode != 0 ) 
		return lRetCode;

// no protocol file für debugging in Windows
#ifndef _WIN32
    if ( LI_OpenProtokol( linr, ProtokolVerzeichnis, errmld ) != 0 )
    {
       return -1;
    }
#endif

    anz_ueb = 0;
    anz_loe = 0;
    anz_dbl = 0;

    lRetCode1 = 0;
    while ( lRetCode == 0 && lRetCode1 == 0 )
    {
      lRetCode1 = StartWork( errmld );
      if ( SQL_SUCCESS == lRetCode1  )
      {

        if ( strcmp(li.LISTATUS,LISTATUS_FREIGEG) == 0 && *li.NBSTATUS <= '1' )
             lRetCode1 = Do_All( &li, datum, errmld );

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
           lRetCode1 = Cli_ExecuteDelete( &li, errmld );  

        lRetCode1 = EndWork( lRetCode1, errmld );

        if (  SQL_DOUBLE_ROW == sdbl ||  SQL_DOUBLE_INDEX == sdbl ) 
			lRetCode1 = 0;

        if ( SQL_SUCCESS == lRetCode1 )
        {

          if ( sdbl != 0 )
            anz_dbl++;
		  else if ( sval != 0 )
            anz_loe++;
          else if ( strcmp(li.LISTATUS,LISTATUS_FREIGEG) == 0 &&
                    *li.NBSTATUS <= '1' )
            anz_ueb++;
          else
            anz_loe++;

          lRetCode = Cli_Fetch( &li, errmld );
        }
      }
    }

    LI_CloseProtokol( SQL_SUCCESS == lRetCode1 && SQL_NOTFOUND == lRetCode, errmld );

    if ( SQL_SUCCESS != lRetCode1  )  
		return lRetCode1;
    if ( SQL_NOTFOUND  == lRetCode )
    {
      if ( anz_dbl == 0 )
         sprintf( errmld,
                  "%ld  LI-Saetze uebertragen\n" \
                  "%ld  LI-Saetze geloescht\n"   ,
                  anz_ueb,
                  anz_loe );
      else
        sprintf( errmld,
                 "%ld  LI-Saetze uebertragen\n"    \
                 "%ld  LI-Saetze geloescht\n"      \
                 "%ld  LI-Saetze noch vorhanden\n"  ,
                 anz_ueb,
                 anz_loe,
                 anz_dbl );
      return 0;
    }

    return lRetCode;
}

static long Select_Loop( long linr, long datum, char mode,
                         char *ProtokolVerzeichnis, char *errmld )
{
    long s;
    s = Cli_Select( linr, datum, mode, errmld );
    if ( s == 0 )
    {
       s = Cli_PrepDelete( errmld );
       if ( s == 0 )
       {
         s = Open_All( errmld );
         if ( s == 0 )
         {
            s = Transfer_Loop( linr, datum, ProtokolVerzeichnis, errmld );

            Close_All();
         }
         Cli_FreeDelete( NULL );
       }
       Cli_CloseCs( NULL );
    }
    return s;
}


/* loop over all datacare positions */
long GenArtLoop( char *db, char *param1, char *param2, char *param3, char *param4,
                 char *spBuf )
  {
    long lLogIndexNr;
    long tagesdatum;
    long lRetCode;
    char szErrmld[10];

    if ( *param3 != 'p' )
    {
      strcpy( spBuf, "p bei Protokollverzeichnis fehlt" );
      return 1;
    }

    lLogIndexNr = atol( param2 );
	
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
		 if ( lRetCode == 0 )
             lRetCode = Select_Loop( lLogIndexNr, tagesdatum, *param1, &param3[1], spBuf );
          ClosePflege( szErrmld );

          /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
          SqlExecuteImm("update statistics medium for table zartikel" );
          SqlExecuteImm("update statistics medium for table zartswitzerland" );
          SqlExecuteImm("update statistics medium for table cliart" );

       }
       CloseBase( );
    }
    return lRetCode;
   }


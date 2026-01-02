/* ---------------------------------------------------------------------- *
 *                        E X C H A N G E A R T P R I C E . C             *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Preise umrechnen											  *
 * ---------------------------------------------------------------------- *
 * Autor  :  Hoerath                                                      *
 * Anfang :  27.08.2009                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hdatum/phodate.h"
#include "hdatum/phozeit.h"
#include "libscsvoodoo/libscsvoodoo.h"

#include  "wdbups/wpp_prot.h"
#include  "wdbups/wpp_dbas.h"
#include <math.h>

#include <zartprei.h>
#include <cartforeigncurr.h>
#include <zapflege.h>
#include <zartikel.h>

#include "protokol.h"

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void ExchangeArtPriceUsage( char *buf )
{
   strcat( buf, "- zpmasaen 10 Database User ProtDatei [PZN]\n" );
   strcat( buf, "  1. ohne PZN: alle Artikel-Preise mit aktuellem Umrechnungsfaktor berechnen\n" );
   strcat( buf, "  2. mit  PZN: Artikel-Preise fuer diesen Artikel mit aktuellem Umrechnungsfaktor berechnen\n" );
}


/* ----------------- Funktion ------------------------ */

static int fd_zartikel			= -1;
static int fd_zartpreis			= -1;
static int fd_cartforeigncurr	= -1;
static int fd_zapflege			= -1;

static double	exchange_ratio	= 0.0;
static double	mwst_voll_0		= 0.0;
static double	mwst_verm_1		= 0.0;

static long		tagesdatum		= -1;
static int		filial_nr		= 0;

static struct ZARTPREIS		BufPreis;
static struct ZARTPREIS		BufPreisOld;
static struct ZAPFLEGE		BufPflege;
static struct CARTFOREIGNCURR	BufForeignCurr;
static struct CARTFOREIGNCURR	BufForeignCurrOld;
static struct ZARTIKEL		BufArtikel;

/* ---------------------------------------- */
static void Init( )
{
	fd_zartpreis		= -1;
	fd_cartforeigncurr	= -1;
	fd_zapflege			= -1;
}

/* ---------------------------------------- */
static void Free( )
{
    if ( fd_zartpreis >= 0 )
        CloseOneBufferDesc( fd_zartpreis );
    fd_zartpreis = -1;

	if ( fd_cartforeigncurr >= 0 )
        CloseOneBufferDesc( fd_cartforeigncurr );
    fd_cartforeigncurr = -1;

	if ( fd_zapflege >= 0 )
        CloseOneBufferDesc( fd_zapflege );
    fd_zapflege = -1;
}

/* ---------------------------------------- */
int GetBufDesc_Zartpreis( char *cErrmld )
{
   char *tabelle = "zartpreis";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_zartpreis >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zartpreis, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zartpreis = -1;
     return -1;
   }
   return 0;
}



/* ---------------------------------------- */
int GetBufDesc_Zapflege( char *cErrmld )
{
   char *tabelle = "zapflege";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_zapflege >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zapflege, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zapflege = -1;
     return -1;
   }
   return 0;
}

/* ---------------------------------------- */
int GetBufferDesc_Cartforeigncurr( char *cErrmld )
{
   char *tabelle = "cartforeigncurr";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_cartforeigncurr >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_cartforeigncurr, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_cartforeigncurr = -1;
     return -1;
   }
   return 0;
}

/* ---------------------------------------- */
static long ReadRecord_Cartforeigncurr( long artikel_nr, char *buf )
{
	long lStatus;
	char PrimeKeyCond[40];
	
	sprintf( PrimeKeyCond, "ARTICLENO = %ld",
				artikel_nr );

	FdInitTabBuf( fd_cartforeigncurr, &BufForeignCurr );

	lStatus = FdReadRecord( fd_cartforeigncurr, PrimeKeyCond,
							  &BufForeignCurr, buf );
	
	if ( lStatus == 0 )
	{
		BufForeignCurrOld = BufForeignCurr;
	}
	
	return lStatus;
}

/* ---------------------------------------- */
static long ReadRecord_ZartPreisCurrent( long artikel_nr, char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	sprintf( PrimeKeyCond, "ARTIKEL_NR = %ld and DATUMGUELTIGAB <= %ld ORDER BY DATUMGUELTIGAB desc",
				artikel_nr, tagesdatum );

	FdInitTabBuf( fd_zartpreis, &BufPreis );

	lStatus = FdReadRecord( fd_zartpreis, PrimeKeyCond,
							  &BufPreis, buf );
	
	if ( lStatus == 0 )
	{
		BufPreisOld = BufPreis;
	}
	
	return lStatus;
}

/* ---------------------------------------- */
static long ReadRecord_ZartPreisFuture( long artikel_nr, char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	sprintf( PrimeKeyCond, "ARTIKEL_NR = %ld and DATUMGUELTIGAB > %ld ORDER BY DATUMGUELTIGAB asc",
				artikel_nr, BufPreis.DATUMGUELTIGAB );

	FdInitTabBuf( fd_zartpreis, &BufPreis );

	lStatus = FdReadRecord( fd_zartpreis, PrimeKeyCond,
							  &BufPreis, buf );
	
	if ( lStatus == 0 )
	{
		BufPreisOld = BufPreis;
	}
	
	return lStatus;
}

/*----------------------------------------------------------------------------*/
static long StoreRecord_Zapflege( char *buf )
{
	long lStatus;

	char PrimekeyCond[100];
	
	BufPflege.ARTIKEL_NR = BufPreis.ARTIKEL_NR;

	if ( BufPreis.DATUMGUELTIGAB < tagesdatum )
		BufPflege.DATUM		 = tagesdatum;
	else
		BufPflege.DATUM		 = BufPreis.DATUMGUELTIGAB;

	sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld",
									BufPflege.ARTIKEL_NR, BufPflege.DATUM );

    lStatus = FdReadRecord( fd_zapflege, PrimekeyCond,
				  			  &BufPflege, buf );

	if ( lStatus == 100 )
	{
		lStatus = FdDelayInsertRecord( fd_zapflege, &BufPflege, 
									PrimekeyCond, buf );
	}

	return lStatus;
}

/* ---------------------------------------- */
static long StoreRecord_Cartforeigncurr( char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[40];
	
	sprintf( PrimeKeyCond, "ARTICLENO=%ld",
				BufForeignCurr.ARTICLENO );
	
	lStatus = FdDelayUpdateRecord( fd_cartforeigncurr, &BufForeignCurr, &BufForeignCurrOld, 
										 PrimeKeyCond, buf);

	return lStatus;
}

/* ---------------------------------------- */
static long StoreRecord_ZartPreis( char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	sprintf( PrimeKeyCond, "ARTIKEL_NR=%ld and DATUMGUELTIGAB = %ld",
				BufPreis.ARTIKEL_NR, BufPreis.DATUMGUELTIGAB );

	lStatus = FdDelayUpdateRecord( fd_zartpreis, &BufPreis, &BufPreisOld, 
										 PrimeKeyCond, buf);

	if ( lStatus == 0 )
		return StoreRecord_Zapflege( buf );

	return lStatus;
}

/* ---------------------------------------- */
static int ReadVat( char *buf )
{
	long s;
	
	sprintf( buf,
            "select MWST_1, MWST_2 from FILIALE where FILIALNR = %d",
			filial_nr );

	s = SqlRead( buf, &mwst_voll_0, &mwst_verm_1, NULL ); 
	
	if ( s != 0 )
	{
     strcpy( buf, "FILIALE\n" );
     strcat( buf, DynErrmld() );
    }
		
	return s;
}

/* ---------------------------------------- */
static long ReadExchangeRatio( long articleno, char *buf )
{
   long s;
   
   sprintf( buf,
			//	-- Fremdwährung --> Hauswährung
			"select exchangeratevalue / fromfactor * tofactor from cexchangeratio c where "
			"fromcurrencyid = (select currencyid from ccurrency where currencycode = "
			"(select currencycode from cartforeigncurr where articleno = %ld)) and "
			"tocurrencyid = (select currencyid from ccurrency where defaultcurrencyflag = 1) and "
			"ratiodate = (select max(ratiodate) from cexchangeratio r where ratiodate <= TODAY and "
			"r.fromcurrencyid = c.fromcurrencyid and r.tocurrencyid = c.tocurrencyid) "
			" UNION "
			//  -- Hauswährung --> Fremdwährung
			"select exchangeratereversevalue / fromfactorreverse * tofactorreverse from cexchangeratio c where "
			"fromcurrencyid = (select currencyid from ccurrency where defaultcurrencyflag = 1) and "
			"tocurrencyid = (select currencyid from ccurrency where currencycode = "
			"(select currencycode from cartforeigncurr where articleno = %ld)) and "
			"ratiodate = (select max(ratiodate) from cexchangeratio r where ratiodate <= TODAY and "
			"r.fromcurrencyid = c.fromcurrencyid and r.tocurrencyid = c.tocurrencyid)",
			articleno, articleno );

   s = SqlRead( buf, &exchange_ratio, NULL ); 

   if ( s == 100 )
   {
     strcpy( buf, "Umrechnungsfaktor nicht gefunden in ccurrency / cartforeigncurr / cexchangeratio." );
   }
   else if ( s != 0 )
   {
     strcpy( buf, "cexchangeratio\n" );
     strcat( buf, DynErrmld() );
   }

   return s;
}

/* ---------------------------------------- */
static void Runden_Modf( double *wert, int stellen )
{
	if ( stellen >= 0 )
	{
		int i;
		double rund;
		double result;
		double rest;

		rund = 1.0;
		for ( i = 0; i < stellen; i++ ) rund *= 10.0;

		i = 1;
		result = *wert;
		if ( result < 0.0 )
		{
			result = -result;
			i = -1;
		}

		rest = modf( result*rund + 0.5, &result );

		/* so laeuft das auch unter UNIX hajo richtig */
		if ( rest >= 0.99999999999 ) 
			result += 1.0;

		result /= rund;
		if ( i == 1 )
			*wert = result;
		else
			*wert = -result;
	}
}

/* ---------------------------------------- */
static long CalcAndStore( char *buf )
{
	long s;
	double grosso_old = BufPreis.GROSSO;

	BufPreis.GROSSO = ( BufPreis.GROSSO	/ BufForeignCurr.EXCHANGE_RATE ) * exchange_ratio;
	Runden_Modf( &BufPreis.GROSSO, 2 );
		
	s = StoreRecord_ZartPreis ( buf );
	if ( s != 0 )
		return s;

	return s;
}

/* ---------------------------------------- */
static long CalcExchange( long artikel_nr, char *buf )
{
	long s;
		
	s = GetBufDesc_Zartpreis		( buf );
	if ( s != 0 )
		return s;
	
	s = GetBufDesc_Zapflege		( buf );
	if ( s != 0 )
		return s;
	
	s = GetBufferDesc_Cartforeigncurr	( buf );
	if ( s != 0 )
		return s;

	s = ReadRecord_Cartforeigncurr ( artikel_nr, buf );
	if ( s != 0 )
		return s;
	
	s = ReadRecord_ZartPreisCurrent ( artikel_nr, buf );
	
	if ( s == 0 )
	{
		s = CalcAndStore ( buf );

		if ( s != 0 )
			return s;
	}
	else if ( s == 100 ) //nur Preise in der Zukunft!
	{
		s = 0;
		BufPreis.DATUMGUELTIGAB = tagesdatum;
	}
	else
		return s;
	

	while ( s == 0 )
	{
		s = ReadRecord_ZartPreisFuture ( artikel_nr, buf );

		if ( s == 0 )
		{
			s = CalcAndStore ( buf );

			if ( s != 0 )
				return s;
		}
	}

	if ( s == 100 )
		s = 0;	

	// nur 1x pro Artikel !
	BufForeignCurr.EXCHANGE_RATE		= exchange_ratio;
	BufForeignCurr.DATE_EXCHANGE_CALC	= tagesdatum;
	
	s = StoreRecord_Cartforeigncurr ( buf );
	if ( s != 0 )
		return s;
	
	return s;
}

/* ---------------------------------------- */
static long ExchangeArticlePrice( long artikel_nr, char *buf )
{
   long s;

   s = SqlBeginWork();
   
   if ( s != 0 )
   {
     strcpy( buf, DynErrmld() );
     return -1;
   }

   s = CalcExchange( artikel_nr, buf );
   
   if ( s == 0 )
	   s = FdTransactWithoutWork( buf );

   if ( s == 0 )
   {
      s = SqlCommitWork();
      
	  if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork();


   return s;
}

/* ---------------------------------------- */
static long ExchangePrices( char *buf )
{
   long s;
   char z_buf[100];
   long anz = 0;
    
   sprintf( buf,
            "select %s from ZARTIKEL where ARTIKEL_NR IN "
				"(select articleno from cartforeigncurr)",
			PROJECTION_ZARTIKEL
			);

   s = SqlOpenCsWh( &fd_zartikel, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd_zartikel, 1, &BufArtikel, NULL );
   
   if ( s == 100 )
   {
     strcpy( buf, "Keine Artikel zur Umrechnung in cartforeigncurr vorhanden." );
     SqlCloseCs( fd_zartikel );
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
     strcat( buf, DynErrmld() );
     SqlCloseCs( fd_zartikel );
     return s;
   }

   s = ReadVat ( buf );
   if ( s != 0 )
	   return s;
   
   Init( );
   
   while ( s == 0 )
   {
	  s = ReadExchangeRatio( BufArtikel.ARTIKEL_NR, buf );
	  if ( s != 0 )
	    break;

	  s = ExchangeArticlePrice( BufArtikel.ARTIKEL_NR, buf );

      if ( s == 0 )
      {
         ++anz;
         s = SqlFetch( fd_zartikel, 1, &BufArtikel, NULL );
         
		 if ( s != 0 )
         {
           strcpy( buf, "ZARTIKEL\n" );
           strcat( buf, DynErrmld() );
         }
      }
   }

   Free( );

   SqlCloseCs( fd_zartikel );

   sprintf( z_buf, "\nEs wurden die Preise von %ld Artikel umgerechnet.", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Umrechnung erfolgreich. " );
   }

   strcat( buf, z_buf );
   return s;
}

/* ---------------------------------------- */
static long ExchangeSinglePrice( long artikel_nr, char *buf )
{
   long s;
   
   sprintf( buf,
            "select %s from ZARTIKEL where ARTIKEL_NR = %ld AND EXISTS "
				"(select 1 from cartforeigncurr where ARTIKEL_NR = %ld)",
			PROJECTION_ZARTIKEL,
            artikel_nr, artikel_nr );

   s = SqlRead( buf, &BufArtikel, NULL ); 

   if ( s == 100 )
   {
     strcpy( buf, "Artikel nicht vorhanden bzw. nicht für Umrechnung gekennzeichnet in cartforeigncurr. " );
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = ReadExchangeRatio( artikel_nr, buf );
   if ( s != 0 )
	   return s;

   s = ReadVat ( buf );
   if ( s != 0 )
	   return s;

   Init( );
   
   s = ExchangeArticlePrice( artikel_nr, buf );

   Free( );

   if ( s == 0 )
       strcpy( buf, "Preise des uebergebenen Artikels wurden umgerechnet." );
 
   return s;
}

/* ---------------------------------------- */
long ExchangeArtPriceLoop ( char *db, char *user, char* prot_file, char *cArtNr, char *buf )
{
	long s;
	long artikel_nr;
	char errmld[10];

	fd_prot = NULL;

	tagesdatum	= GetPhoDate();

	if ( cArtNr != NULL )
	{
		int i = 0;
       
		while ( isdigit(cArtNr[i]) )
			++i;
       
		if ( cArtNr[i] != '\0' )
		{
			strcpy( buf, "PZN nicht numerisch" );
			return 1;
		}
		artikel_nr = atol( cArtNr );
		if ( artikel_nr <= 0 )
		{
			strcpy( buf, "PZN falsch" );
			return 1;
		}
	}

	if ( strcmp(db, "zpps2hr") == 0 || strcmp(db, "ihr21") == 0 )
		filial_nr = 79;
	else if ( strcmp(db, "zpps2rs") == 0 || strcmp(db, "irs21") == 0 )
		filial_nr = 84;
	else if ( strcmp(db, "zpps2bg") == 0 || strcmp(db, "ibg21") == 0 )
		filial_nr = 22;
	else if ( strcmp(db, "zpps1de") == 0 || strcmp(db, "ide21") == 0 )
		filial_nr = 53;
	else if ( strcmp(db, "zpps1ch") == 0 || strcmp(db, "ich21") == 0 )
		filial_nr = 19;
	else if ( strcmp(db, "zpps2at") == 0 || strcmp(db, "iat21") == 0 )
		filial_nr = 69;
	else
	{
		strcpy( buf, "Usage 10 nicht für das angegebene Land!" );
		return 1;
	}

	/*
	s = OpenProtDatei( &fd_prot, prot_file, tagesdatum, GetPhoTime(), user );
	if ( s != 0 )
	{
	    sprintf( buf, "not able to open protocol-file\n%s",
                        prot_file );
		return s;
	}
	*/
	
	s = OpenBase( db, buf );
   
	if ( s == 0 )
	{
		s = OpenPflege( user, buf );
     
		if ( s == 0 )
		{
			if ( cArtNr == NULL )
				s = ExchangePrices( buf );
			else
				s = ExchangeSinglePrice( artikel_nr, buf );

			ClosePflege( errmld );
		}
     
		CloseBase( );
	}

	// CloseProtDatei ( fd_prot );
	fd_prot = NULL;

	return s;
}

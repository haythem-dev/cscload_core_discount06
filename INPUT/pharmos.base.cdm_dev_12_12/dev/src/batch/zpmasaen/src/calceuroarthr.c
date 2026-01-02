/* ---------------------------------------------------------------------- *
 *                        C A L C E U R O A R T H R . C                   *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   kroatische Preise umrechnen                                  *
 * ---------------------------------------------------------------------- *
 * Autor  :  Hoerath                                                      *
 * Anfang :  06.11.2006                                                   *
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
#include <zartcroatia.h>
#include <zapflege.h>
#include <zartikel.h>

#include "protokol.h"

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void CalcEuroArtHrUsage( char *buf )
{
   strcat( buf, "- zpmasaen 9 Database User ProtDatei [PZN]\n" );
   strcat( buf, "  1. ohne PZN: alle Euro-Artikel-Preise mit aktuellem Umrechnungsfaktor berechnen\n" );
   strcat( buf, "  2. mit  PZN: Euro-Artikel-Preise fuer diesen Artikel mit aktuellem Umrechnungsfaktor berechnen\n" );
}


/* ----------------- Funktion ------------------------ */

static int fd_zartikel			= -1;
static int fd_zartpreis			= -1;
static int fd_zartcroatia		= -1;
static int fd_zapflege			= -1;

static double	exchange_rate	= 0.0;
static double	mwst_voll_0		= 0.0;
static double	mwst_verm_1		= 0.0;

static long		tagesdatum		= -1;
static int		filial_nr		= 0;

static struct ZARTPREIS		BufPreis;
static struct ZARTPREIS		BufPreisOld;
static struct ZAPFLEGE		BufPflege;
static struct ZARTCROATIA	BufCroatia;
static struct ZARTCROATIA	BufCroatiaOld;
static struct ZARTIKEL		BufArtikel;

/* ---------------------------------------- */
static void Init( )
{
	fd_zartpreis		= -1;
	fd_zartcroatia		= -1;
	fd_zapflege			= -1;
}

/* ---------------------------------------- */
static void Free( )
{
    if ( fd_zartpreis >= 0 )
        CloseOneBufferDesc( fd_zartpreis );
    fd_zartpreis = -1;

	if ( fd_zartcroatia >= 0 )
        CloseOneBufferDesc( fd_zartcroatia );
    fd_zartcroatia = -1;

	if ( fd_zapflege >= 0 )
        CloseOneBufferDesc( fd_zapflege );
    fd_zapflege = -1;
}

/* ---------------------------------------- */
int GetBufferDesc_Zartpreis( char *cErrmld )
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
int GetBufferDesc_Zartcroatia_ce( char *cErrmld )
{
   char *tabelle = "zartcroatia";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_zartcroatia >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zartcroatia, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zartcroatia = -1;
     return -1;
   }
   return 0;
}

/* ---------------------------------------- */
int GetBufferDesc_Zapflege( char *cErrmld )
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
static long ReadRecord_ZartCroatia( long artikel_nr, char *buf )
{
	long lStatus;
	char PrimeKeyCond[40];
	
	sprintf( PrimeKeyCond, "ARTICLENO = %ld",
				artikel_nr );

	FdInitTabBuf( fd_zartcroatia, &BufCroatia );

	lStatus = FdReadRecord( fd_zartcroatia, PrimeKeyCond,
							  &BufCroatia, buf );
	
	if ( lStatus == 0 )
	{
		BufCroatiaOld = BufCroatia;
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
static long StoreRecord_ZartCroatia( char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[40];
	
	sprintf( PrimeKeyCond, "ARTICLENO=%ld",
				BufCroatia.ARTICLENO );

	
	lStatus = FdDelayUpdateRecord( fd_zartcroatia, &BufCroatia, &BufCroatiaOld, 
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
static int ReadMwst( char *buf )
{
	long s;
	
	sprintf( buf,
            "select MWST_1, MWST_2 from FILIALE where FILIALNR = %d",
			filial_nr );

	s = SqlRead( buf, &mwst_voll_0, &mwst_verm_1, NULL ); 
	
	if ( s != 0 )
		strcpy( buf, DynErrmld());
		
	return s;
}

/* ---------------------------------------- */
static long ReadQtyInStock( int filialnr, long * bestand, char *buf )
{
	long s;
	
	sprintf( buf,
            "select BESTAND from ARTIKELF where FILIALNR = %d and ARTIKEL_NR = %ld",
			filialnr, BufArtikel.ARTIKEL_NR );

	s = SqlRead( buf, bestand, NULL ); 

	if ( s == 100 )
	{
		bestand = 0;
		s = 0;
	}
	
	if ( s != 0 )
		strcpy( buf, DynErrmld());
		
	return s;
}

/* ---------------------------------------- */
static long ReadExchangeRate( char *buf )
{
   long s;
   
   sprintf( buf,
            "select WAEHRFAKTOR from RFILIALE where FILIALNR = %d",
			filial_nr );

   s = SqlRead( buf, &exchange_rate, NULL ); 

   if ( s == 100 )
   {
     strcpy( buf, "Filiale 79 nicht vorhanden, um Waehrungsfaktor zu lesen." );
   }
   else if ( s != 0 )
   {
     strcpy( buf, "RFILIALE\n" );
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
/*	double mwstproz;
	double mwstwert;
	double wert;
	double betrag;
*/

	long s;
	double grosso_old = BufPreis.GROSSO;

	BufPreis.GROSSO = ( BufPreis.GROSSO	/ BufCroatia.EXCHANGE_RATE ) * exchange_rate;
	Runden_Modf( &BufPreis.GROSSO, 2 );
		
/*	----------------------------------
	NUR GROSSO SOLL UMGERECHNET WERDEN !!!

	BufPreis.AEP	= ( BufPreis.AEP	/ BufCroatia.EXCHANGE_RATE ) * exchange_rate;
	Runden_Modf( &BufPreis.AEP, 2 );
	
	BufPreis.EAVP	= ( BufPreis.EAVP	/ BufCroatia.EXCHANGE_RATE ) * exchange_rate;
	Runden_Modf( &BufPreis.EAVP, 2 );
	
	BufPreis.HERST_PROZENT = BufArtikel.HERST_PROZENT;
	
	if ( BufArtikel.HERST_PROZENT > 0.0 )
	{
		if ( BufPreis.KE_MWST[0] == '0' )
			mwstproz = mwst_voll_0;
		else if ( BufPreis.KE_MWST[0] == '1' )
			mwstproz = mwst_verm_1;
		else
			mwstproz = 0.0;

		wert = BufPreis.AEP;
		betrag = BufArtikel.HERST_PROZENT * wert / 100.0;
		wert += betrag;
		mwstwert = wert * mwstproz / 100.0;
		wert += mwstwert;
		Runden_Modf( &wert, 2 );
		BufPreis.AVP = wert;
	}
	else
	{
		BufPreis.AVP = ( BufPreis.AVP / BufCroatia.EXCHANGE_RATE ) * exchange_rate;
		Runden_Modf( &BufPreis.AVP, 2 );
	}
	---------------------------------- */
	
	s = StoreRecord_ZartPreis ( buf );
	if ( s != 0 )
		return s;

	WriteProtZeile ( fd_prot, &BufArtikel, &BufQtyInStock, grosso_old, BufPreis.GROSSO, BufCroatia.EXCHANGE_RATE, exchange_rate, BufPreis.DATUMGUELTIGAB);

	return s;
}

/* ---------------------------------------- */
static long Calculate( long artikel_nr, char *buf )
{
	long s;
		
	s = GetBufferDesc_Zapflege		( buf );
	if ( s != 0 )
		return s;
	
	s = GetBufferDesc_Zartpreis		( buf );
	if ( s != 0 )
		return s;
	
	s = GetBufferDesc_Zartcroatia_ce	( buf );
	if ( s != 0 )
		return s;

	s = ReadRecord_ZartCroatia ( artikel_nr, buf );
	if ( s != 0 )
		return s;
	
// ---- Bestände lesen für Protokoll ----
	s = ReadQtyInStock (71, &BufQtyInStock.Qty_71, buf );
	if ( s != 0 )
		return s;

	s = ReadQtyInStock (72, &BufQtyInStock.Qty_72, buf );
	if ( s != 0 )
		return s;

	s = ReadQtyInStock (73, &BufQtyInStock.Qty_73, buf );
	if ( s != 0 )
		return s;

	s = ReadQtyInStock (74, &BufQtyInStock.Qty_74, buf );
	if ( s != 0 )
		return s;

	s = ReadQtyInStock (77, &BufQtyInStock.Qty_77, buf );
	if ( s != 0 )
		return s;

	BufQtyInStock.Qty_Sum = BufQtyInStock.Qty_71 + BufQtyInStock.Qty_72 + 
							BufQtyInStock.Qty_73 + BufQtyInStock.Qty_74 + BufQtyInStock.Qty_77;
// ----------------------------------	
	
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
	BufCroatia.EXCHANGE_RATE		= exchange_rate;
	BufCroatia.DATE_EXCHANGE_CALC	= tagesdatum;
	
	s = StoreRecord_ZartCroatia ( buf );
	if ( s != 0 )
		return s;
	
	return s;
}

/* ---------------------------------------- */
static long CalcArticlePrices( long artikel_nr, char *buf )
{
   long s;

   s = SqlBeginWork();
   
   if ( s != 0 )
   {
     strcpy( buf, DynErrmld() );
     return -1;
   }

   s = Calculate( artikel_nr, buf );
   
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
static long CalcPrices( char *buf )
{
   long s;
   char z_buf[100];
   long anz = 0;
    
   sprintf( buf,
            "select %s from ZARTIKEL where SORTIMENT_1 = '1'",
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
     strcpy( buf, "Keine Artikel mit Umrechnungs-KZ (Sortiment_1) vorhanden." );
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

   s = ReadExchangeRate( buf );
   if ( s != 0 )
	   return s;

   s = ReadMwst ( buf );
   if ( s != 0 )
	   return s;
   
   Init( );
   
   while ( s == 0 )
   {
	  s = CalcArticlePrices( BufArtikel.ARTIKEL_NR, buf );

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
static long CalcSinglePrices( long artikel_nr, char *buf )
{
   long s;
   
   sprintf( buf,
            "select %s from ZARTIKEL where ARTIKEL_NR = %ld",
			PROJECTION_ZARTIKEL,
            artikel_nr );

   s = SqlRead( buf, &BufArtikel, NULL ); 

   if ( s == 100 )
   {
     strcpy( buf, "Artikel nicht vorhanden" );
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   if ( *BufArtikel.SORTIMENT_1 != '1' )
   {
     strcpy( buf, "Artikel nicht für Umrechnung gekennzeichnet in Sortiment_1 ." );
     return 0;
   }

   s = ReadExchangeRate( buf );
   if ( s != 0 )
	   return s;

   s = ReadMwst ( buf );
   if ( s != 0 )
	   return s;

   Init( );
   
   s = CalcArticlePrices( artikel_nr, buf );

   Free( );

   if ( s == 0 )
       strcpy( buf, "Preise des uebergebenen Artikels wurden umgerechnet." );
 
   return s;
}

/* ---------------------------------------- */
long CalcEuroArtHrLoop ( char *db, char *user, char* prot_file, char *cArtNr, char *buf )
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

	if ( strcmp(db, "zpps2hr") == 0 || strcmp(db, "ihr21") == 0)
		filial_nr = 79;
	else
	{
		strcpy( buf, "Usage 9 bisher nur für Kroatien!" );
		return 1;
	}

	s = OpenProtDatei( &fd_prot, prot_file, tagesdatum, GetPhoTime(), user );
	if ( s != 0 )
	{
	    sprintf( buf, "not able to open protocol-file\n%s",
                        prot_file );
		return s;
	}

	
	s = OpenBase( db, buf );
   
	if ( s == 0 )
	{
		s = OpenPflege( user, buf );
     
		if ( s == 0 )
		{
			
			
			if ( cArtNr == NULL )
				s = CalcPrices( buf );
			else
				s = CalcSinglePrices( artikel_nr, buf );

			ClosePflege( errmld );
		}
     
		CloseBase( );
	}

	CloseProtDatei ( fd_prot );
	fd_prot = NULL;

	return s;
}

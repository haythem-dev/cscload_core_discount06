
/*
   LsTaxtab.c : implementation file
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <libscsvoodoo.h>
#include "l_taxtab.h"

#define MAX_TAX  30
#define MAX_ANZ_TAXARTEN	10

/* ---------------------------------------- */
struct TaxTb
{
  long von_dm;
  long proz;
  long betrag;
};

static struct TaxTb tax[MAX_ANZ_TAXARTEN][MAX_TAX];

static int    m_nTaxStatus  = -1;
static int    m_nAnzTax[MAX_ANZ_TAXARTEN] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/* ---------------- Taxtabelle lesen -------------------------- */

static int ReadOneTaxtab( int nr, char *cErrmld )
{
   int  k;
   int  fd;
   long rco;
   char sql[150];
   char tab_nr[2];

   tab_nr[0] = (char)(nr + '0');
   tab_nr[1] = '\0';

   sprintf( sql, "select TAX_VON_DM,TAX_PROZ,TAX_BETRAG from TAXTAB " \
                 "where TAX_ART='%s' order by TAX_VON_DM",
                 tab_nr );
   k = 0;
   rco = SqlOpenCs ( &fd, sql );
   if ( rco == 0 )
   {
       while ( rco == 0 && k < MAX_TAX )
       {
           rco = SqlFetch ( fd, 1, &tax[nr][k], NULL );
           if (rco == 0) k++;
       }
       SqlCloseCs ( fd );
   }
   if ( rco == 100 )
   {
       *cErrmld = '\0';
       m_nAnzTax[nr] = k;
       return 0;
   }
   else
   {
       strcpy( cErrmld, DynErrmld() );
       m_nAnzTax[nr] = 0;
       return 1;
   }
}


/* ---------------------------------------- */
int ReadTaxtab( char *cErrmld )
{
    int s;
    if ( m_nTaxStatus == -1 )
    {
        s = ReadOneTaxtab( 0, cErrmld );
        if ( s == 0 ) ReadOneTaxtab( 1, cErrmld );
		if ( s == 0 ) ReadOneTaxtab( 2, cErrmld );
		if ( s == 0 ) ReadOneTaxtab( 3, cErrmld );
		if ( s == 0 ) ReadOneTaxtab( 4, cErrmld );
		if ( s == 0 ) ReadOneTaxtab( 5, cErrmld );
		if ( s == 0 ) ReadOneTaxtab( 6, cErrmld );
		if ( s == 0 ) ReadOneTaxtab( 7, cErrmld );
		if ( s == 0 ) ReadOneTaxtab( 8, cErrmld );
		if ( s == 0 ) ReadOneTaxtab( 9, cErrmld );
        if ( s != 0 )
        {
            m_nAnzTax[0] = 0;
            m_nAnzTax[1] = 0;
			m_nAnzTax[2] = 0;
			m_nAnzTax[3] = 0;
			m_nAnzTax[4] = 0;
			m_nAnzTax[5] = 0;
			m_nAnzTax[6] = 0;
			m_nAnzTax[7] = 0;
			m_nAnzTax[8] = 0;
			m_nAnzTax[9] = 0;
        }
        m_nTaxStatus = s;
    }
    return m_nTaxStatus;
}


/* ---------------------------------------- */
int TestTaxtabEuro()
{
	if ( m_nAnzTax[2] > 0 && m_nAnzTax[3] > 0 )
		return 0;
	return 1;
}

/* ---------------------------------------- */
int TestTaxtabEuroRX()		/* ab 01.04.2004 zusaetlich zu der alten */
{
	if ( m_nAnzTax[8] > 0 && m_nAnzTax[6] > 0 && m_nAnzTax[7] > 0 && m_nAnzTax[1] > 0)
		return 0;
	return 1;
}


/* ------------- Taxe berechnen ----------------------- */

void KaufmRunden( double *wert, int stellen );

/* ---------------------------------------- */
static double CalcTaxe( int nr, double wert )
{
    int i;
    long lwert;

    double betrag;

    lwert = (long) ( 100.0 * wert + 0.5 );    /* !!!!!! + 0.5 */
    i = m_nAnzTax[nr] -1;
    while ( i >= 0 && lwert < tax[nr][i].von_dm ) i--;

    /* Reihenfolge wichtig */
    if ( tax[nr][i].proz != 0 )
      {
        betrag = (double)(tax[nr][i].proz)*wert/100000.0;
        KaufmRunden( &betrag, 2 );
        wert += betrag;
       }

    if ( tax[nr][i].betrag != 0 )
      {
        betrag = (double)(tax[nr][i].betrag)/100.0;
        KaufmRunden( &betrag, 2 );
        wert += betrag;
       }

    KaufmRunden( &wert, 2 );
    return wert;
}

/* ---------------------------------------- */
int CreateTaxtab( char *cErrmld )
{
   int s;
   m_nTaxStatus  = -1;

   s = ReadTaxtab( cErrmld );
   if ( s != 0 )
   {
       strcat( cErrmld, "\nTaxtabelle kann nicht gelesen werden" );
	   return s;
   }

   s = TestTaxtabEuro();
   if ( s != 0 )
   {
       strcpy( cErrmld, "Taxtabelle OTCX fuer Euro nicht vorhanden" );
	   return s;
   }

   s = TestTaxtabEuroRX();
   if ( s != 0 )
   {
	   cErrmld = "Taxtabelle RX fuer Euro nicht vorhanden";
	   return s;
   }

   return 0;
}

/* ---------------------------------------- */
int CalcAvkEuro( double aek, double *avk, double mwstproz )
{
	if ( m_nAnzTax[3] > 0 )
	{
		double mwstwert;
		double wert;
		wert = CalcTaxe( 3, aek );
		mwstwert = wert*mwstproz/100.0;
		KaufmRunden( &mwstwert, 2 );
		*avk = wert + mwstwert;
		return 1;
	}
	return 0;
}

/* ---------------------------------------- */
int CalcAvkEuroRX( double aek, double *avk, double mwstproz, int datum )
{
	int tax_nr;

	if (datum <= 20130731)
		tax_nr = 7;
	else if (datum <= 20191231)
		tax_nr = 8;  // ab 08.2013 neue Taxe für AVP´s (Notdienstpauschale)
	else if (datum <= 20211214)
		tax_nr = 9;  // ab 01.2020 neue Taxe für AVP´s (Notdienstpauschale)
	else
		tax_nr = 4;  // ab 15.12.2021 neue Taxe für AVP´s (Notdienstpauschale)

	if ( m_nAnzTax[tax_nr] > 0 )
	{
		double mwstwert;
		double wert;
		wert = CalcTaxe( tax_nr, aek );
		mwstwert = wert*mwstproz/100.0;
		KaufmRunden( &mwstwert, 2 );
		*avk = wert + mwstwert;
		return 1;

	}
	return 0;
}

/* ---------------------------------------- */
int CalcAvk( double aek, double *avk, double mwstproz, long datum, char taxmode  )
{
	if ( taxmode == '1' )
		return CalcAvkEuro( aek, avk, mwstproz );
	else
		return CalcAvkEuroRX( aek, avk, mwstproz, datum );
}

/* ---------------------------------------- */
int CalcAekEuroRX( double grosso, double *aek, long datum )
{
	int tax_nr;
	// new by CPR-230569
	if (datum <= 20230831)
	{
		tax_nr = 6;
	}
	else
	{
		tax_nr = 1; // new by CPR-230569
	}

	if ( m_nAnzTax[tax_nr] > 0 )
	{
		*aek = CalcTaxe( tax_nr, grosso );
		return 1 ;
	}	
	
	return 0;
}

/* ---------------------------------------- */
int CalcAekEuro( double grosso, double *aek )
{
	if ( m_nAnzTax[2] > 0 )
	{
		*aek = CalcTaxe( 2, grosso );
		return 1 ;
	}
	return 0;
}

/* ---------------------------------------- */
int CalcAek( double grosso, double *aek, long datum, char taxmode  )
{
	if ( taxmode == '1' )
		return CalcAekEuro( grosso, aek );
	else
		return CalcAekEuroRX( grosso, aek, datum );
}


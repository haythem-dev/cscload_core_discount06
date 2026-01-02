/* ---------------------------------------------------------------------- *
 * Aufgabe        : Taxpruefungen			                                  *
 * ---------------------------------------------------------------------- *
 * Autor          : Hoerath                                               *
 * erstellt am    : 02.02.2005                                            *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include "l_taxtab.h"

#define MAX_TAX  30
struct TaxTb
{
  long von_dm;
  long proz;
  long betrag;
  long fixpreis;
};

/*enum Countries { D , A } m_Country;*/

static struct TaxTb tax[5][MAX_TAX];

static int    m_nMwstStatus = -1;
static int    m_nTaxStatus  = -1;
static double m_dMwstProzVoll = 0.0;
static double m_dMwstProzVerm = 0.0;
static double m_dMwstProz3rd  = 0.0;
static int    m_nAnzTax[6] = { 0, 0, 0, 0, 0, 0 };

/* ---------------- Taxtabelle lesen -------------------------- */
int ReadOneTaxtab( int nr, char* cErrmld )
{
	int  k;
	int  fd;
	long rco;
	char sql[150];
	char tab_nr[2];

	tab_nr[0] = (char)(nr + '0');
	tab_nr[1] = '\0';

	sprintf( sql, "select TAX_VON_DM,TAX_PROZ,TAX_BETRAG, TAX_FIXPREIS "
				"from taxtab where tax_art='%s' "
				"order by TAX_VON_DM",
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

/* ---------------------------------------------------------------------- */
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

		if ( s != 0 )
		{
			m_nAnzTax[0] = 0;
			m_nAnzTax[1] = 0;
			m_nAnzTax[2] = 0;
			m_nAnzTax[3] = 0;
			m_nAnzTax[4] = 0;
		}
		m_nTaxStatus = s;
	}
	return m_nTaxStatus;
}

/* ---------------------------------------------------------------------- */
int TestTaxtabAustria()		
{
	if ( m_nAnzTax[0] > 0 && m_nAnzTax[1] > 0 && m_nAnzTax[2] > 0 && m_nAnzTax[3] > 0 && m_nAnzTax[4] > 0 )
		return 0;
	return 1;
}

/* ---------------------------------------------------------------------- */
double CalcTaxe( int nr, double wert )
{
	int i;
	long lwert;
	double betrag;

	lwert = (long) ( 100.0 * wert + 0.5 );   /* + 0.05 ???? */
	i = m_nAnzTax[nr] -1;
	while ( i >= 0 && lwert < tax[nr][i].von_dm ) i--;

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

	if ( tax[nr][i].fixpreis != 0 )
	{
		betrag = (double)(tax[nr][i].fixpreis)/100.0;
/*		KaufmRunden( &betrag, 2 );*/
		wert = betrag;
	}

	KaufmRunden( &wert, 2 );
	return wert;
}

/* ---------------------------------------------------------------------- */
int ReadMwst( double *mwst_voll, double *mwst_verm, double *mwst_3rd, long * grenzeHochpreis, char *cErrmld )
{
	*cErrmld = '\0';
	if ( m_nMwstStatus == -1 )
	{
		if ( SqlRead( "select MWST_1,MWST_2,MWST_3,GRENZE_A from FILIALE where filialnr = 0",
						mwst_voll, mwst_verm, mwst_3rd, grenzeHochpreis, NULL ) == 0 )
		{
			m_dMwstProzVoll = *mwst_voll;
			m_dMwstProzVerm = *mwst_verm;
			m_dMwstProz3rd  = *mwst_3rd;
			m_nMwstStatus = 0;
		}
		else
		{
			m_nMwstStatus = 1;
			strcpy( cErrmld, DynErrmld() );
		}
	}

	return m_nMwstStatus;
}

/* ---------------------------------------------------------------------- */
int CreateTaxtabAustria( long * grenzeHochpreis, char *cErrmld )
{
	int s;
	double mwst_voll;
	double mwst_verm;
	double mwst_3rd;

	/*m_Country = A;*/

	m_nTaxStatus = -1; 
	m_nMwstStatus = -1;

	s = ReadTaxtab( cErrmld );
    if ( s != 0 )
    {
       strcat( cErrmld, "\nTaxtabelle kann nicht gelesen werden" );
	   return s;
    }

	s = TestTaxtabAustria();
	if ( s != 0 )
	{
		cErrmld = "mindestens eine Taxtabelle nicht vorhanden";
		return s;
	}

	s = ReadMwst( &mwst_voll, &mwst_verm, &mwst_3rd, grenzeHochpreis, cErrmld );
	if ( s != 0 )
	{
		strcat( cErrmld, "\nMWST kann nicht gelesen werden" );
		return s;
	}

	return 0;
}

/* ---------------------------------------------------------------------- */
int CalcAekAustriaCH( double grosso, double *aek )
{
	if ( m_nAnzTax[0] > 0 )
	{
		*aek = CalcTaxe( 0, grosso );
		return 1 ;
	}
	return 0;
}

/* ---------------------------------------------------------------------- */
int CalcAekAustriaVT( double grosso, double *aek )
{
	if ( m_nAnzTax[2] > 0 )
	{
		*aek = CalcTaxe( 1, grosso );
		return 1 ;
	}
	return 0;
}

/* ---------------------------------------------------------------------- */
int CalcAekAustriaHO( double grosso, double *aek )
{
	if ( m_nAnzTax[1] > 0 )
	{
		*aek = CalcTaxe( 2, grosso );
		return 1 ;
	}
	return 0;
}

/* ---------------------------------------------------------------------- */
int CalcAekAustriaKF( double grosso, double *aek )
{
	if ( m_nAnzTax[3] > 0 )
	{
		*aek = CalcTaxe( 3, grosso );
		return 1 ;
	}
	return 0;
}

/* ---------------------------------------------------------------------- */
int CalcAekAustria( double grosso, double *aek, long datum, char taxmode  )
{
	if ( taxmode == '1' )
		return CalcAekAustriaCH( grosso, aek );

	if ( taxmode == '2' )
		return CalcAekAustriaVT( grosso, aek );

	if ( taxmode == '3' )
		return CalcAekAustriaHO( grosso, aek );

	if ( taxmode == '4' )
		return CalcAekAustriaKF( grosso, aek );

	return 0;
}

/* ---------------------------------------------------------------------- */
int CalcAvkAustriaEuro( double aek, double *avk, double mwstproz, long datum, char btm )
{
	if ( m_nAnzTax[4] > 0 )
	{
		double	mwstwert;
		double	wert;
		long	iwert;

		wert = CalcTaxe( 4, aek );

		/* dieser Wert ist erst der Kassenpreis; AVP = (KP * 1,15) + MWST*/
		wert = wert * 1.15;
		KaufmRunden( &wert, 2 );

		// ab 2012 wird der Suchtgiftzuschlag schon VOR der Berechnung der Mwst addiert
		if (datum >= 20120101)
		{
			if (btm == '1')
				wert += 0.55;
		}

		mwstwert = wert * mwstproz/100.0;
		KaufmRunden( &mwstwert, 2 );
		wert += mwstwert;

		/* AVP muss jetzt noch auf 5 cent gerundet werden*/
		iwert = (long) ( 100.0 * wert + 0.5 );   

		if (iwert%5 <= 2)
		{
			iwert = (iwert / 5) * 5;
		}
		else
		{
			iwert = ((iwert + 2) / 5) * 5;
		}

		wert = (double) iwert / 100.0;
		KaufmRunden( &wert, 2 );

		*avk = wert;

		return 1;
	}

	return 0;
}

/* ---------------------------------------------------------------------- */
int CalcAvkAustriaMwstEuro( double aek, double *avk, int mwst_art, long datum, char btm )
{
	if ( m_nAnzTax[4] > 0 && m_nMwstStatus == 0 )
	{
		double mwstproz;
		if ( mwst_art == TAXTAB_IS_VOLLMWST )
			mwstproz = m_dMwstProzVoll;
		else if ( mwst_art == TAXTAB_IS_VERMMWST )
			mwstproz = m_dMwstProzVerm;
		else if ( mwst_art == TAXTAB_IS_3RD )
			mwstproz = m_dMwstProz3rd;
		else if (mwst_art == TAXTAB_IS_KMWST)  /*0*/
			mwstproz = 0.0;
		else
			mwstproz = 0.0;

		return CalcAvkAustriaEuro( aek, avk, mwstproz, datum, btm );
	}
	return 0;
}



/* ---------------------------------------------------------------------- */
int CalcAvkAustriaMwst( double aek, double *avk, int mwst_art, long datum, char taxmode, char btm )
{
	int rc;

	rc = CalcAvkAustriaMwstEuro( aek, avk, mwst_art, datum, btm );

	// Suchtgiftzuschlag NACH Berechnung der Mwst nur noch bis Ende 2011
	if (datum < 20120101)
	{
		if (btm == '1')
		{
			// ab 01.01.2009 beträgt der Suchtgiftzuschlag nur noch 55 Cent
			if (datum >= 20090101)
				*avk += 0.55;
			else
				*avk += 0.6;
		}
	}

	return rc;
}



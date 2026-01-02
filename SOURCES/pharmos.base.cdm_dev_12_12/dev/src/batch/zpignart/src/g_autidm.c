/* ---------------------------------------------------------------------- *
 *                         G - A U T I D M . C                            *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   ARTIKELZ generieren                                          *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  20.06.2002                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo.h>


/* ----- ArtAutidem ------ */

#define PROJECTION_ARTAUTIDEM \
       "PZN," \
       "DATUM," \
       "GEP_ALT," \
       "AEP_ALT," \
       "GEP_NEU," \
       "AEP_NEU," \
       "ERSTATTUNGSTAGE," \
       "FESTBETRAGSREGEL," \
	   "IFANR"

long m_Autidm_InsertRecord( long pzn, long datum, 
						    double gep_alt, double aep_alt,
						    double gep_neu, double aep_neu, 
							long hersteller_nr, long ifanr, char *errmld )
{
	long s;
	short erstattungstage;

	char sql[300];

	char errstr[100];

	long LeseErstattungstage( long hersteller_nr, short *erstattungstage, char *errmld );

	s = LeseErstattungstage( hersteller_nr, &erstattungstage, errstr );
	if (!( s == 0 || s == 100 ) )
	{
		sprintf( errmld, "Autidem: %s", errstr );
		return s;
	}
	if ( s == 100 || erstattungstage == 0 )
		return 0;

    sprintf( sql, "delete from artautidem where pzn=%ld and datum=%ld", 
				   pzn, 
				   datum );
	s = SqlExecuteImm( sql );

    sprintf( sql, "insert into artautidem (%s) values( %ld, %ld, %f, %f, %f, %f, %d, '0', %ld )",
		           PROJECTION_ARTAUTIDEM,
				   pzn,
				   datum,
				   gep_alt, aep_alt,
				   gep_neu, aep_neu,
				   erstattungstage,
				   ifanr );
	s = SqlExecuteImm( sql );
	if ( s != 0 )
	{
		sprintf( errmld, "Autidem: %s", DynErrmld() );
	}
	return s;

}


/* ----- ZspannenKuerz ------ */

#define PROJECTION_ZSPANNENKUERZ \
       "ARTIKEL_NR," \
       "DATUMGUELTIGAB," \
       "GROSSO_ALT," \
       "AEP_ALT," \
	   "SPANNE_ALT," \
       "GROSSO_NEU," \
       "AEP_NEU," \
	   "SPANNE_NEU," \
       "KUERZUNG," \
       "KUERZUNG_REL," \
	   "HERSTELLER_NR," \
	   "DATUM_ANLAGE," \
       "VERKAUF_VORMON,"  \
	   "UMSATZ_VORMON,"  \
	   "WERTVERLUST"  


long m_Spankuerz_InsertRecord( long pzn, long datum, 
						       double gep_alt, double aep_alt, double spanne_alt,
						       double gep_neu, double aep_neu, double spanne_neu,
							   double kuerzung, double kuerzung_rel,
							   long hersteller_nr, long datum_anlage, char *errmld )
{
	long s;
	char sql[400];
    sprintf( sql, "delete from zspannenkuerz where artikel_nr=%ld and datumgueltigab=%ld", 
				   pzn, 
				   datum );
	s = SqlExecuteImm( sql );

    sprintf( sql, "insert into zspannenkuerz (%s) " \
		          "values( %ld, %ld, %f, %f, %f, %f, %f, %f, %f, %f, %ld, %ld, %ld, %f, %f )",
		           PROJECTION_ZSPANNENKUERZ,
				   pzn,
				   datum,
				   gep_alt, aep_alt, spanne_alt,
				   gep_neu, aep_neu, spanne_neu,
				   kuerzung,
				   kuerzung_rel,
				   hersteller_nr,
				   datum_anlage,
				   0,
				   0.0,
				   0.0 );

	/* VERKAUF_VORMON, UMSATZ_VORMON, WERTVERLUST mit 0 initialisiert */ 

	s = SqlExecuteImm( sql );
	if ( s != 0 )
	{
		sprintf( errmld, "zspannenkuerz: %s", DynErrmld() );
	}
	return s;

}


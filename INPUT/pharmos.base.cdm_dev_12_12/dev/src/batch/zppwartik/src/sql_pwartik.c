/* ---------------------------------------------------------------------- *
 * Aufgabe        : SQL - Funktionen für zpgalartik					      *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 13.06.2005                                            *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

#include <wpp_dbas.h>

#include "sql_pwartik.h"

#include "g_pwartik.h"

/* ------------------------------------------------------------------- */
int WriteGrpPflege(long comp_no, char * dezap_sa, long date, char * errmld)
{
	long status;
	long datum;
	char sql[500];
	char company[10];
	
	sprintf ( company, "%05ld", comp_no );

	sprintf( sql, 
		"select datum from zgrppflege where key_gruppe = '%s' "
		"and datum = %ld and dezap_sa = '%s'",
		company, date, dezap_sa );

    status = SqlRead( sql, &datum, NULL );
	
    if ( status == 100 ) 
	{
		sprintf( sql, 
			"insert into zgrppflege ( key_gruppe, datum, dezap_sa ) "
			"values ( '%s', %ld, '%s' )",
			company, date, dezap_sa );

		status = SqlExecuteImm( sql );
	}
	
	if ( status != 0 )
	{
		strcat( errmld, "\nzgrppflege (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
int WritePznPflege(long art_no, char * dezap_sa, long date, char * errmld)
{
	int status;
	long datum;
	char sql[500];
	
	sprintf( sql, 
		"select datum from zpznpflege where artikel_nr = %ld "
		"and datum = %ld and dezap_sa = '%s'",
		art_no, date, dezap_sa );
	
    status = SqlRead( sql, &datum, NULL );

    if ( status == 100 ) 
	{
		sprintf( sql, 
			"insert into zpznpflege ( artikel_nr, datum, dezap_sa ) "
			"values ( %ld, %ld, '%s' )",
			art_no, date, dezap_sa );

		status = SqlExecuteImm( sql );
	}
	
	if ( status != 0 )
	{
		strcat( errmld, "\nzpznpflege (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
int WriteZAPflege(long art_no, long date, char * errmld)
{
	int status;
	long datum;
	char sql[500];
	
	sprintf( sql, 
		"select datum from zapflege where artikel_nr = %ld "
		"and datum = %ld",
		art_no, date );
	
    status = SqlRead( sql, &datum, NULL );

    if ( status == 100 ) 
	{
		sprintf( sql, 
			"insert into zapflege ( artikel_nr, datum ) "
			"values ( %ld, %ld )",
			art_no, date );

		status = SqlExecuteImm( sql );
	}
	
	if ( status != 0 )
	{
		strcat( errmld, "\nzapflege (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
int copy_zartaustria( const long art_nr_orig, const long art_nr_neu, char *errmld)
{
	int status;
	char sql[5000];
	
	sprintf( sql, 
		"INSERT into zartaustria (ARTIKEL_NR, WECHSELARTIKEL, BUENDELPACKUNG, NACHLIEFERUNG, CHARGENARTIKEL, OELHV_GRUPPE, OELHV_OEKOKZ, OELHV_SORT, HV_BOX, "
									"VERTRBIND_PLPL, VERTRBIND_S1S5, VERTRBIND_VPL, VERTRBIND_SP, VERTRBIND_COMPTANT, VERTRBIND_NEUFORM, NICHT_LIEFERBAR, NICHT_GELIEFERT, "
									"RUECK_MON_VOR_VERF, VERTRBIND_BDORF, SG_SUBSTANZ, DROGENAGS_KAT1, DROGENAGS_KAT2, DROGENAGS_KAT3, MEDPROD_ABG_VERORD, MEDPROD_KLASSE) "
									"select '%ld', WECHSELARTIKEL, BUENDELPACKUNG, NACHLIEFERUNG, CHARGENARTIKEL, OELHV_GRUPPE, OELHV_OEKOKZ, OELHV_SORT, HV_BOX, "
									"VERTRBIND_PLPL, VERTRBIND_S1S5, VERTRBIND_VPL, VERTRBIND_SP, VERTRBIND_COMPTANT, VERTRBIND_NEUFORM, NICHT_LIEFERBAR, NICHT_GELIEFERT, "
									"RUECK_MON_VOR_VERF, VERTRBIND_BDORF, SG_SUBSTANZ, DROGENAGS_KAT1, DROGENAGS_KAT2, DROGENAGS_KAT3, MEDPROD_ABG_VERORD, MEDPROD_KLASSE "
									"from zartaustria where artikel_nr = %ld ",
		art_nr_neu, art_nr_orig );

	status = SqlExecuteImm( sql );

	if ( status != 0 )
	{
		strcat( errmld, "\nzartaustria (Copy / Insert): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
int copy_zartwg		( const long art_nr_orig, const long art_nr_neu, char *errmld)
{
	int status;
	char sql[500];
	
	sprintf( sql, 
		"INSERT into zartwg (artikel_nr, art, warengruppe) select '%ld', art, warengruppe from zartwg where artikel_nr = %ld ",
		art_nr_neu, art_nr_orig );

	status = SqlExecuteImm( sql );

	if ( status != 0 )
	{
		strcat( errmld, "\nzartwg (Copy / Insert): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
long sel_ArtNoByCode	( const long code )
{
    long artNo;
	char sql[150];

	if (code == 0)
		return code;

	sprintf( sql, "SELECT articleno FROM carticlecodes WHERE article_code ='%ld' "
					"AND code_type IN (SELECT code_type FROM ccodetypes WHERE artnr_substitute = 1)", code);
  
	if ( SqlRead( sql, &artNo, NULL ) != 0 )
	{
		artNo = -1;
	}

	return artNo;
}

/* ------------------------------------------------------------------- */
long sel_ArtNoByManArt	( char* ArtNoManufacturer )
{
    long artNo = 0;
	char sql[150];

	sprintf( sql, "SELECT artikel_nr FROM zartikel WHERE artikel_nr_herst ='%s' ", ArtNoManufacturer);
  
	if ( SqlRead( sql, &artNo, NULL ) != 0 )
	{
		artNo = -1;
	}

	return artNo;
}

/* ---------------------------------------------------------------------- */
int GetPruefZiffer ( long pzn )
{
	int i;
	long zahl, prziff;

	if ( pzn <= 0 ) 
		return 0;

    zahl = pzn;
	
	prziff = 0;
    for (i=7; i>=2; i--)
    {
        zahl /= 10;
        prziff += i * ( zahl % 10 );
    }
    prziff %= 11;

    if (prziff == 10) 
		prziff = 0;

	return prziff;
}

/* ------------------------------------------------------------------- */
long sel_NextPseudoArtNo( )
{
	long lStatus = 0;
	long lPzn = 0;
	long nextPzn = 0;
	double dCount;
	char sql[150];

	strcpy( sql, "select nr from nummerek where nr_art = 'PSDPZN' " );
	lStatus = SqlRead( sql, &lPzn, NULL );

	if (lStatus == 0)
	{
		sprintf( sql, "select count(*) + (select count(*) from carticlecodes where articleno = %ld) from zartikel where artikel_nr = %ld ", lPzn, lPzn );
		lStatus = SqlRead(sql, &dCount, NULL);

		while ( lStatus == 0 && dCount > 0.0 ) // PZN bereits vorhanden
		{
			lPzn = 10 * (((int) lPzn / 10) + 1);			
			lPzn += GetPruefZiffer( lPzn );

			sprintf( sql, "select count(*) + (select count(*) from carticlecodes where articleno = %ld) from zartikel where artikel_nr = %ld ", lPzn, lPzn );
			lStatus = SqlRead(sql, &dCount, NULL);
		}

		if ( lStatus == 0 && dCount == 0.0 ) // erste freie PZN gefunden
		{
			// nummerek schreiben
			nextPzn = 10 * (((int) lPzn / 10) + 1);			
			nextPzn += GetPruefZiffer( nextPzn );

			sprintf( sql, "update nummerek set nr = %ld where nr_art = 'PSDPZN' ", nextPzn );

			lStatus = SqlExecuteImm( sql );
		}
	}

	return lPzn;
}

/* ------------------------------------------------------------------- */
int del_preis_artwg_artaustria( const long art_nr, char *errmld )
{
	int lStatus = 0;
	char sql[150];

	sprintf( sql, "delete from zartpreis where artikel_nr = %ld ", art_nr );
	lStatus = SqlExecuteImm( sql );

	if ( lStatus == 0 )
	{
		sprintf( sql, "delete from zartwg where artikel_nr = %ld ", art_nr );
		lStatus = SqlExecuteImm( sql );
	}

	if ( lStatus == 0 )
	{
		sprintf( sql, "delete from zartaustria where artikel_nr = %ld ", art_nr );
		lStatus = SqlExecuteImm( sql );
	}

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nzartpreis / zartwg / zartaustria (Delete): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int copy_zartpreis		( const long art_nr_orig, const long art_nr_neu, char *errmld)
{
	int status;
	char sql[500];
	
	sprintf( sql, 
		"INSERT into zartpreis (artikel_nr, datumgueltigab, grosso, aep, avp, ke_mwst, herst_prozent, preis_typ, disc_deduced_yet)"
		"select '%ld', datumgueltigab, grosso, aep, avp, ke_mwst, herst_prozent, preis_typ, disc_deduced_yet from zartpreis where artikel_nr = %ld ",
		art_nr_neu, art_nr_orig );

	status = SqlExecuteImm( sql );

	if ( status != 0 )
	{
		strcat( errmld, "\nzartwg (Copy / Insert): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
int sel_zartikel	( const int *Fd_ZArtikel, const long art_nr, struct ZARTIKEL *zart, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_ZArtikel < 0 ) 
		return -1;

	sprintf ( PK, "artikel_nr=%ld", art_nr );

	lStatus = FdReadRecord( *Fd_ZArtikel, PK, zart, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldZArt = *zart;  
	}
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\nzartikel (Suche nach Artikel): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_zartikel	( const int *Fd_ZArtikel, struct ZARTIKEL *zart, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	char format[50];
	
	if ( *Fd_ZArtikel < 0 ) 
		return -1;

	sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
	sprintf ( PK, format, zart->ARTIKEL_NR );

	lStatus = FdUpdateRecord( *Fd_ZArtikel, zart, &m_BufOldZArt, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nzartikel (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		if ( strcmp ( m_BufOldZArt.ARTIKEL_LANGNAME , zart->ARTIKEL_LANGNAME ) != 0 )
			WritePznPflege( zart->ARTIKEL_NR, "33", tages_datum, errmld );

		WriteZAPflege(zart->ARTIKEL_NR, tages_datum, errmld);
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_zartikel	( const int *Fd_ZArtikel, struct ZARTIKEL *zart, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	char format[50];
	
	if ( *Fd_ZArtikel < 0 ) 
		return -1;

	sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
	sprintf ( PK, format, zart->ARTIKEL_NR );

	lStatus = FdInsertRecord( *Fd_ZArtikel, zart, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nzartikel (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		char leer[ L_ZARTIKEL_ARTIKEL_LANGNAME + 1 ];
		memset( leer, ' ', L_ZARTIKEL_ARTIKEL_LANGNAME );
				
		if ( memcmp( zart->ARTIKEL_LANGNAME, leer, L_ZARTIKEL_ARTIKEL_LANGNAME ) != 0 )
			WritePznPflege( zart->ARTIKEL_NR, "33", tages_datum, errmld );

		WriteZAPflege(zart->ARTIKEL_NR, tages_datum, errmld);
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_zartikel	( const int *Fd_ZArtikel, const long art_nr, char * errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_ZArtikel < 0 ) 
		return -1;


	sprintf ( PK, "artikel_nr=%7ld", art_nr );
	
	lStatus = FdDeleteRecord( *Fd_ZArtikel, &m_BufOldZArt, PK, errmld );

	if ( lStatus != 0 ) 
	{
		strcat( errmld, "\nzartikel (Delete einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_carticlecodes( const int *Fd_CArticleCodes, struct CARTICLECODES *codes, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	char format[50];
	
	if ( *Fd_CArticleCodes < 0 ) 
		return -1;

	sprintf( format, "ARTICLENO=%c%d.ld AND CODE_TYPE=%d", '%', L_ARTIKEL_NR, codes->CODE_TYPE );
	sprintf ( PK, format, codes->ARTICLENO );

	lStatus = FdInsertRecord( *Fd_CArticleCodes, codes, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\ncarticlecodes (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WritePznPflege(codes->ARTICLENO, "34", tages_datum, errmld);
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zartpreis	( const int *Fd_ZArtPreis, const long art_nr, struct ZARTPREIS *zpreis, char* errmld)
{
	long lStatus;
	char PK [500];
	
	if ( *Fd_ZArtPreis < 0 ) 
		return -1;

	sprintf ( PK, "artikel_nr=%ld and datumgueltigab = " 
					"(select max(DATUMGUELTIGAB) from ZARTPREIS where " 
					"DATUMGUELTIGAB<=%ld " 
					"and ARTIKEL_NR=%ld)", 
					art_nr, AddDayToPhoDate(tages_datum, 1), art_nr );

	lStatus = FdReadRecord( *Fd_ZArtPreis, PK, zpreis, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldZPreis = *zpreis; 
	}
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\nzartpreis (Suche nach Preis): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_zartpreis	( const int *Fd_ZArtPreis,struct ZARTPREIS *zpreis, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	struct ZARTPREIS zpreistemp;
	
	if ( *Fd_ZArtPreis < 0 ) 
		return -1;

	// keine Preise in der Vergangenheit einspielen !!!
	if ( zpreis->DATUMGUELTIGAB < tages_datum )
		zpreis->DATUMGUELTIGAB = tages_datum;			

	sprintf ( PK, "artikel_nr=%ld and datumgueltigab>%ld " ,
				zpreis->ARTIKEL_NR, zpreis->DATUMGUELTIGAB);

	lStatus = FdReadRecord( *Fd_ZArtPreis, PK, &zpreistemp, errmld );
	
	if ( lStatus == 100 )
	{	
		sprintf ( PK, "artikel_nr=%7ld and datumgueltigab=%ld ", zpreis->ARTIKEL_NR, zpreis->DATUMGUELTIGAB);	
		
		if ( FdReadRecord( *Fd_ZArtPreis, PK, &m_BufOldZPreis, errmld ) == 0 ) // Update zartpreis, wenn es einen Preissatz mit identischem Gültigkeitsdatum gibt
			lStatus = FdUpdateRecord( *Fd_ZArtPreis, zpreis, &m_BufOldZPreis, PK, errmld);
		else	
			lStatus = FdInsertRecord( *Fd_ZArtPreis, zpreis, PK, errmld);

		if ( lStatus != 0 )
		{
			strcat( errmld, "\nzartpreis (Insert/Update einer Zeile): \n" );
			strcat( errmld, DynErrmld() );
		}
		else
		{
			if ( zpreis->DATUMGUELTIGAB > tages_datum )
				WriteZAPflege(zpreis->ARTIKEL_NR, zpreis->DATUMGUELTIGAB, errmld);
			else
				WriteZAPflege(zpreis->ARTIKEL_NR, tages_datum, errmld);
		}
	}
	else if ( lStatus != 0 )
	{
		strcat( errmld, "\nzartpreis (Select einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		// bereits ein Preis in der Zukunft vorhanden!
		strcat( errmld, "\nPreis in der Zukunft vorhanden!\n" );
		return 99;
	}

	return lStatus;
}

/* ---------------------------------------------------------------------- *
 * Aufgabe        : SQL - Funktionen								      *
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

#include "sql_impartik.h"
#include "imp_form.h"

#include "g_impartik.h"

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
int markOutdatedArticlesAsDeleted (short month, const char *bearbeiter, char *errmld)
{
	int status;
	char sql[1000];
	char interval[100];
	char whereStmt[1000];
	char user[100];

	strcpy( sql, 
			"insert into zapflege (artikel_nr, datum) "
			"select artikel_nr, cast(to_char(current, '%Y%m%d') as integer) from zartikel where "
			"artikel_nr not in (select artikel_nr from zapflege where datum = cast(to_char(current, '%Y%m%d') as integer)) and ");

	strcpy( whereStmt, 
			"artikel_nr in (select artikel_nr from zartaustria where deutschlandbesorger = 1) "
			"and artikel_geloescht != '1' and artikel_gesperrt = '1' and TO_DATE( CASE WHEN datum_ah < 20000000 THEN '88881231' ELSE TO_CHAR(datum_ah) END, '%Y%m%d')::DATE ");
		
	sprintf(interval, "+ INTERVAL(%d) month TO month < current ", month);
	
	strcat(sql, whereStmt);
	strcat(sql, interval);
				
	status = SqlExecuteImm( sql );
		
	if ( status != 0 )
	{
		strcat( errmld, "\nzapflege (Inserts): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		strcpy( sql, "update zartikel set artikel_geloescht = '1', datum_ifaaender = cast(to_char(current, '%Y%m%d') as integer),  ");
		sprintf( user, "bearbeiter = '%s' where ", bearbeiter);

		strcat(sql, user);
		strcat(sql, whereStmt);
		strcat(sql, interval);

		status = SqlExecuteImm( sql );
		
		if ( status != 0 )
		{
			strcat( errmld, "\nzartikel (Updates): \n" );
			strcat( errmld, DynErrmld() );
		}
	}

	return status;
}

/* ------------------------------------------------------------------- */
int markExportArticleAsImportProcessed (char *dbexp, char * importCountry, long artNo, char* errmld)
{
	int status;
	char sql[1000];
	
	sprintf(sql, "update %s:cexportarticle set lastimportprocess = current where country_ifacode = '%s' and articleno = %ld", dbexp, importCountry, artNo);
	
	status = SqlExecuteImm( sql );
		
	if ( status != 0 )
	{
		strcat( errmld, "\ncexportarticle (Update): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
int openCs_export_manuf( char *dbexp, const long datefrom, char * exportCountry, char* errmld )
{
	int status;
	char sql[500];

	fd_sel_export_manuf = -1;

	sprintf( sql, 
		"select m.hersteller_nr, name, sortiername, plz, ort, strasse, hausnr_von, landeskuerzel, vorwahl, telefon_nr, vorwahl_telefax, fax_nr from %s:herstel h, Cimexmanufacturermapping  m "
		"where h.hersteller_nr = export_manufacturerno and country_ifacode = '%s' "
		"and (datum_aender > %ld or datum_ifaaender > %ld) ",
		dbexp, exportCountry, datefrom, datefrom );

	status = SqlOpenCsWh( &fd_sel_export_manuf, sql );

	if ( status != 0 )
	{
		strcat( errmld, "\ncimexmanufacturermapping (open cursor): \n" );
		strcat( errmld, DynErrmld() );
	}

	return status;
}

/* ------------------------------------------------------------------- */
int fetchNext_export_manuf( struct HERSTEL_IMPORTDATA * impdata, char* errmld )
{
	int status = 0;

	if (fd_sel_export_manuf < 0)
		return -1;

	status = SqlFetch( fd_sel_export_manuf, 1, impdata, NULL );

	if ( status != 0 && status != 100 )
	{
		strcat( errmld, "\ncimexmanufacturermapping (fetch): \n" );
		strcat( errmld, DynErrmld() );
	}

	if (status != 0)
		SqlCloseCs( fd_sel_export_manuf );

	return status;
}

/* ------------------------------------------------------------------- */
int sel_herstel	( const int *Fd_Herstel, const long hnr, struct HERSTEL *herst, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Herstel < 0 ) 
		return -1;

	sprintf ( PK, "hersteller_nr=%ld", hnr );

	lStatus = FdReadRecord( *Fd_Herstel, PK, herst, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufHerstelOld = *herst;  
	}
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\nherstel (Suche nach Hnr): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_herstel	( const int *Fd_Herstel, struct HERSTEL *herst, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	char format[50];
	
	if ( *Fd_Herstel < 0 ) 
		return -1;

	sprintf( format, "HERSTELLER_NR=%c%d.ld", '%', L_HERSTELLER_NR );
	sprintf ( PK, format, herst->HERSTELLER_NR );

	lStatus = FdUpdateRecord( *Fd_Herstel, herst, &m_BufHerstelOld, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nherstel (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WriteGrpPflege(herst->HERSTELLER_NR, "20", GetPhoDate(), errmld);
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_herstel	( const int *Fd_Herstel, struct HERSTEL *herst, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	char format[50];
	
	if ( *Fd_Herstel < 0 ) 
		return -1;

	sprintf( format, "HERSTELLER_NR=%c%d.ld", '%', L_HERSTELLER_NR );
	sprintf ( PK, format, herst->HERSTELLER_NR );

	lStatus = FdWithoutWorkInsertRecord( *Fd_Herstel, herst, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nherstel (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WriteGrpPflege(herst->HERSTELLER_NR, "20", GetPhoDate(), errmld);
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_herlief	( const int *Fd_Herlief, struct HERLIEF *herlief, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Herlief < 0 ) 
		return -1;

	sprintf ( PK, "HERSTELLER_NR=%ld AND LANT_NR=%ld", herlief->HERSTELLER_NR, herlief->LANT_NR );

	lStatus = FdWithoutWorkInsertRecord( *Fd_Herlief, herlief, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nherlief (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cimexmanufmapping	( const int *Fd_Cimexmanufacturermapping, struct CIMEXMANUFACTURERMAPPING *manufMap, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Cimexmanufacturermapping < 0 ) 
		return -1;

	sprintf ( PK, "HERSTELLER_NR=%ld AND COUNTRY_IFACODE='%s'", manufMap->HERSTELLER_NR, manufMap->COUNTRY_IFACODE );

	lStatus = FdWithoutWorkInsertRecord( *Fd_Cimexmanufacturermapping, manufMap, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nCimexmanufacturermapping (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
long sel_HnrByExportManufacturer( long manufacturerNo, char * exportCountry, char* errmld )
{
    long Hnr = -1;
	char sql[300];
	long status;

	sprintf( sql, "SELECT h.hersteller_nr FROM herstel h, Cimexmanufacturermapping m WHERE h.hersteller_nr = m.hersteller_nr and m.export_manufacturerno = %ld and m.country_ifacode = '%s'", 
					manufacturerNo, exportCountry);

	status = SqlRead( sql, &Hnr, NULL );

	if ( status != 0 && status != 100 )
	{
		strcat( errmld, "\ncimexmanufacturermapping (Select): \n" );
		strcat( errmld, DynErrmld() );
	}
	else if (status == 100)
	{
		Hnr = 0;
	}

	return Hnr;
}

/* ------------------------------------------------------------------- */
int openCs_export_article( char *dbexp, char * importCountry, char * exportCountry, char* errmld )
{
	int status;
	char sql[2000];

	fd_sel_export_article = -1;

	sprintf( sql, 
		"select e.articleno, e.exportpermissionflag, "
		"a.artikel_mc, a.artikel_name, a.laenge, a.breite, a.hoehe, a.gewicht, a.kuehlartikel, a.darreichform, a.einheit, a.arzneimittel, a.tierarznei, a.rezeptpfl, a.apothekenpfl, a.chargenartikel, a.biosiegel, "
		"h.hersteller_nr, h.name, h.sortiername, h.plz, h.ort, h.strasse, h.hausnr_von, h.landeskuerzel, h.vorwahl, h.telefon_nr, h.vorwahl_telefax, h.fax_nr, "
		"NVL(m.hersteller_nr, -1) as import_hnr, "
		"NVL(ean.ean_nr, '') as ean_nr, "
		"NVL(atc.article_code, '') as atc_code, "
		"NVL(ntin.article_code, '') as ntin_code, "
		"pzn8.article_code as pzn8 "
		"from  %s:cexportarticle e, %s:zartikel a, %s:herstel h, outer %s:ean ean, outer %s:carticlecodes atc, outer %s:carticlecodes ntin, %s:carticlecodes pzn8, outer cimexmanufacturermapping m "
		"where e.articleno = a.artikel_nr and h.hersteller_nr = a.hersteller_nr and ean.artikel_nr = a.artikel_nr and atc.articleno = a.artikel_nr and atc.code_type = 2  "
		"and ntin.articleno = a.artikel_nr and ntin.code_type = 22 and pzn8.articleno = a.artikel_nr and pzn8.code_type = 16 "
		"and m.export_manufacturerno = h.hersteller_nr and m.country_ifacode = '%s' "
		"and e.country_ifacode = '%s' and (lastpermissionchange>lastimportprocess  OR (lastarticlechange>lastimportprocess and exportpermissionflag=1)) ",
		dbexp, dbexp, dbexp, dbexp, dbexp, dbexp, dbexp, exportCountry, importCountry );

	status = SqlOpenCsWh( &fd_sel_export_article, sql );
		
	if ( status != 0 )
	{
		strcat( errmld, "\ncexportarticle (open cursor): \n" );
		strcat( errmld, DynErrmld() );
	}

	return status;
}

/* ------------------------------------------------------------------- */
int fetchNext_export_article( struct ARTICLE_IMPORTDATA * impdata, char* errmld )
{
	int status = 0;

	if (fd_sel_export_article < 0)
		return -1;

	status = SqlFetch( fd_sel_export_article, 1, impdata, NULL );
	
	if ( status != 0 && status != 100 )
	{
		strcat( errmld, "\ncexportarticle (fetch): \n" );
		strcat( errmld, DynErrmld() );
	}

	if (status != 0)
		SqlCloseCs( fd_sel_export_article );

	return status;
}

/* ------------------------------------------------------------------- */
long sel_ArtNoByManArt	( char* ArtNoManufacturer, char* errmld )
{
    long artNo = -1;
	long status;
	char sql[250];

	sprintf( sql, "SELECT z.artikel_nr FROM zartikel z, zartaustria a WHERE z.artikel_nr_herst ='%s' and z.artikel_nr = a.artikel_nr and a.deutschlandbesorger = 1", ArtNoManufacturer);
  
	status = SqlRead( sql, &artNo, NULL );

	if ( status != 0 && status != 100 )
	{
		strcat( errmld, "\nzartikel (fetch): \n" );
		strcat( errmld, DynErrmld() );
	}
	else if (status == 100)
	{
		artNo = 0;
	}

	return artNo;
}

/* ------------------------------------------------------------------- */
int sel_importParam	( const int *Fd_Cimportarticleparam, char * exportCountry, struct CIMPORTARTICLEPARAM *importParam, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Cimportarticleparam < 0 ) 
		return -1;

	sprintf ( PK, "country_ifacode='%s'", exportCountry );

	lStatus = FdReadRecord( *Fd_Cimportarticleparam, PK, importParam, errmld );
	
	if ( lStatus != 0 )
	{
		strcat( errmld, "\ncimportarticleparam (Suche): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
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

	lStatus = FdWithoutWorkUpdateRecord( *Fd_ZArtikel, zart, &m_BufOldZArt, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nzartikel (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		//if ( strcmp ( m_BufOldZArt.ARTIKEL_LANGNAME , zart->ARTIKEL_LANGNAME ) != 0 )
		//	WritePznPflege( zart->ARTIKEL_NR, "33", tages_datum, errmld );

		WriteZAPflege(zart->ARTIKEL_NR, GetPhoDate(), errmld);
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

	lStatus = FdWithoutWorkInsertRecord( *Fd_ZArtikel, zart, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nzartikel (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		/*
		char leer[ L_ZARTIKEL_ARTIKEL_LANGNAME + 1 ];
		memset( leer, ' ', L_ZARTIKEL_ARTIKEL_LANGNAME );
				
		if ( memcmp( zart->ARTIKEL_LANGNAME, leer, L_ZARTIKEL_ARTIKEL_LANGNAME ) != 0 )
			WritePznPflege( zart->ARTIKEL_NR, "33", tages_datum, errmld );
		*/

		WriteZAPflege(zart->ARTIKEL_NR, GetPhoDate(), errmld);
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
long sel_NextInternalHnr( char *errmld )
{
	long lStatus = 0;
	long lHnr = -1;
	long nextHnr = 0;
	double dCount = 0.0;
	char sql[150];
	short firstLoop = 1;

	strcpy( sql, "select nr from nummerek where nr_art = 'INTHNR' " );
	lStatus = SqlRead( sql, &lHnr, NULL );

	if (lStatus != 0)
	{
		sprintf( errmld, "Error <%ld> at reading nr_art <INTHNR> from nummerek.", lStatus );
		strcat( errmld, DynErrmld() );
		return -1;
	}

	while ( lStatus == 0 && (dCount > 0.0 || firstLoop == 1) )
	{
		if (firstLoop == 0)
			++lHnr; // HNR bereits vorhanden = nächste versuchen ...
		else
			firstLoop = 0;

		sprintf( sql, "select count(*) from herstel where hersteller_nr = %ld", lHnr );
		lStatus = SqlRead(sql, &dCount, NULL);
	}

	if ( lStatus == 0 && dCount == 0.0 ) // erste freie HNR gefunden
	{
		// nummerek schreiben
		nextHnr = lHnr + 1;

		sprintf( sql, "update nummerek set nr = %ld where nr_art = 'INTHNR' ", nextHnr );

		lStatus = SqlExecuteImm( sql );
	}

	if (lStatus != 0)
	{
		sprintf( errmld, "Error <%ld> at detecting next internal manufacturer no.", lStatus );
		strcat( errmld, DynErrmld() );
		return -1;
	}
	
	return lHnr;
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
long sel_NextInternalPzn( char *errmld )
{
	long lStatus = 0;
	long lPzn = -1;
	long nextPzn = 0;
	double dCount = 0.0;
	char sql[150];
	short firstLoop = 1;

	strcpy( sql, "select nr from nummerek where nr_art = 'INTPZN' " );
	lStatus = SqlRead( sql, &lPzn, NULL );

	if (lStatus != 0)
	{
		sprintf( errmld, "Error <%ld> at reading nr_art <INTPZN> from nummerek.", lStatus );
		strcat( errmld, DynErrmld() );
		return -1;
	}

	while ( lStatus == 0 && (dCount > 0.0 || firstLoop == 1) )
	{
		if (firstLoop == 0)
		{
			// lPzn = 10 * (((int) lPzn / 10) + 1);			
			// lPzn += GetPruefZiffer( lPzn ); // PZN bereits vorhanden = nächste versuchen ...
			lPzn = lPzn + 1;
		}
		else
			firstLoop = 0;			

		sprintf( sql, "select count(*) + (select count(*) from carticlecodes where articleno = %ld) from zartikel where artikel_nr = %ld ", lPzn, lPzn );
		lStatus = SqlRead(sql, &dCount, NULL);
	}

	if ( lStatus == 0 && dCount == 0.0 ) // erste freie PZN gefunden
	{
		// nummerek schreiben - in AT ist der internen Nummernkreis künftig ohne Prüfziffer
		// nextPzn = 10 * (((int) lPzn / 10) + 1);			
		// nextPzn += GetPruefZiffer( nextPzn );
		nextPzn = lPzn + 1;			

		sprintf( sql, "update nummerek set nr = %ld where nr_art = 'INTPZN' ", nextPzn );

		lStatus = SqlExecuteImm( sql );
	}

	if (lStatus != 0)
	{
		sprintf( errmld, "Error <%ld> at detecting next internal article no.", lStatus );
		strcat( errmld, DynErrmld() );
		return -1;
	}
	
	return lPzn;
}

/* ------------------------------------------------------------------- */
int ins_ean( const int *Fd_Ean, struct EAN *ean, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	char format[50];
	
	if ( *Fd_Ean < 0 ) 
		return -1;

	sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR);
	sprintf ( PK, format, ean->ARTIKEL_NR );

	lStatus = FdWithoutWorkInsertRecord( *Fd_Ean, ean, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nean (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_zartwg		( const int *Fd_ZArtWg, struct ZARTWG *wg, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	char format[50];
	
	if ( *Fd_ZArtWg < 0 ) 
		return -1;

	sprintf( format, "ARTIKEL_NR=%c%d.ld and art='2'", '%', L_ARTIKEL_NR);
	sprintf ( PK, format, wg->ARTIKEL_NR );

	lStatus = FdWithoutWorkInsertRecord( *Fd_ZArtWg, wg, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nzartwg (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_bliesort	( const int *Fd_Bliesort, struct BLIESORT *bliesort, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Bliesort < 0 ) 
		return -1;

	sprintf ( PK, "BESLA_NR=%ld and ARTIKEL_NR=%ld", bliesort->BESLA_NR, bliesort->ARTIKEL_NR );

	lStatus = FdWithoutWorkInsertRecord( *Fd_Bliesort, bliesort, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nbliesort (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_zartaustria	( const int *Fd_ZArtAustria, struct ZARTAUSTRIA *zaustria, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	char format[50];
	
	if ( *Fd_ZArtAustria < 0 ) 
		return -1;

	sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR);
	sprintf ( PK, format, zaustria->ARTIKEL_NR );

	lStatus = FdWithoutWorkInsertRecord( *Fd_ZArtAustria, zaustria, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nzartaustria (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_ean( const int *Fd_Ean, struct EAN *ean, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	char format[50];
	
	if ( *Fd_Ean < 0 ) 
		return -1;

	sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
	sprintf ( PK, format, ean->ARTIKEL_NR );

	lStatus = FdWithoutWorkUpdateRecord( *Fd_Ean, ean, &m_BufOldEan, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nean (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_ean( const int *Fd_Ean, const long art_nr, struct EAN *ean, char* errmld)
{
	long lStatus;
	char PK [500];
	
	if ( *Fd_Ean < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%ld", art_nr);

	lStatus = FdReadRecord( *Fd_Ean, PK, ean, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldEan = *ean; 
	}
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\nean (Suche nach PZN): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_ean( const int *Fd_Ean, const long art_nr, char* errmld)
{
	long lStatus;
	char PK [500];
	
	if ( *Fd_Ean < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%ld", 
					art_nr);

	lStatus = FdWithoutWorkDeleteRecord( *Fd_Ean, &m_BufOldEan, PK, errmld );
	
	if ( lStatus != 0 )
	{
		strcat( errmld, "\nean (Loeschen EAN): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_atccode	 ( const int *Fd_CArticleCodes, const long art_nr, struct CARTICLECODES *codes, char* errmld)
{
	long lStatus;
	char PK [500];
	
	if ( *Fd_CArticleCodes < 0 ) 
		return -1;

	sprintf ( PK, "articleno=%ld and code_type=2", 
					art_nr);

	lStatus = FdReadRecord( *Fd_CArticleCodes, PK, codes, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldCodes = *codes; 
	}
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\ncarticlecodes (Suche nach ATC-Code): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_ntincode	 ( const int *Fd_CArticleCodes, const long art_nr, struct CARTICLECODES *codes, char* errmld)
{
	long lStatus;
	char PK [500];
	
	if ( *Fd_CArticleCodes < 0 ) 
		return -1;

	sprintf ( PK, "articleno=%ld and code_type=22", 
					art_nr);

	lStatus = FdReadRecord( *Fd_CArticleCodes, PK, codes, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldCodes = *codes; 
	}
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\ncarticlecodes (Suche nach NTIN-Code): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}
/* ------------------------------------------------------------------- */
int upd_carticlecodes( const int *Fd_CArticleCodes, struct CARTICLECODES *codes, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	char format[50];
	
	if ( *Fd_CArticleCodes < 0 ) 
		return -1;

	sprintf( format, "ARTICLENO=%c%d.ld AND CODE_TYPE=%d", '%', L_ARTIKEL_NR, codes->CODE_TYPE );
	sprintf ( PK, format, codes->ARTICLENO );

	lStatus = FdWithoutWorkUpdateRecord( *Fd_CArticleCodes, codes, &m_BufOldCodes, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\ncarticlecodes (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WritePznPflege(codes->ARTICLENO, "34", GetPhoDate(), errmld);
	
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

	lStatus = FdWithoutWorkInsertRecord( *Fd_CArticleCodes, codes, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\ncarticlecodes (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WritePznPflege(codes->ARTICLENO, "34", GetPhoDate(), errmld);
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_ntincode		 ( const int *Fd_CArticleCodes, const long art_nr, char* errmld)
{
	long lStatus;
	char PK [500];
	
	if ( *Fd_CArticleCodes < 0 ) 
		return -1;

	sprintf ( PK, "articleno=%ld and code_type=22", 
					art_nr);

	lStatus = FdWithoutWorkDeleteRecord( *Fd_CArticleCodes, &m_BufOldCodes, PK, errmld );
	
	if ( lStatus != 0 )
	{
		strcat( errmld, "\ncarticlecodes (Loeschen NTIN-Code): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WritePznPflege(m_BufOldCodes.ARTICLENO, "34", GetPhoDate(), errmld);

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_atccode		 ( const int *Fd_CArticleCodes, const long art_nr, char* errmld)
{
	long lStatus;
	char PK [500];
	
	if ( *Fd_CArticleCodes < 0 ) 
		return -1;

	sprintf ( PK, "articleno=%ld and code_type=2", 
					art_nr);

	lStatus = FdWithoutWorkDeleteRecord( *Fd_CArticleCodes, &m_BufOldCodes, PK, errmld );
	
	if ( lStatus != 0 )
	{
		strcat( errmld, "\ncarticlecodes (Loeschen ATC-Code): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WritePznPflege(m_BufOldCodes.ARTICLENO, "34", GetPhoDate(), errmld);

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zartpreis	( const int *Fd_ZArtPreis, const long art_nr, const long datefrom, struct ZARTPREIS *zpreis, char* errmld)
{
	long lStatus;
	char PK [500];
	
	if ( *Fd_ZArtPreis < 0 ) 
		return -1;

	sprintf ( PK, "artikel_nr=%ld and datumgueltigab=%ld ", 
					art_nr, datefrom );

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
int save_zartpreis	( const int *Fd_ZArtPreis, struct ZARTPREIS *zpreis, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_ZArtPreis < 0 ) 
		return -1;

	// keine Preise in der Vergangenheit einspielen !!!
	if ( zpreis->DATUMGUELTIGAB <= GetPhoDate() )
		zpreis->DATUMGUELTIGAB = AddDayToPhoDate(GetPhoDate(), 1);			

	sprintf ( PK, "artikel_nr=%ld and datumgueltigab=%ld ", zpreis->ARTIKEL_NR, zpreis->DATUMGUELTIGAB);	
		
	// Update zartpreis, wenn es einen Preissatz mit identischem Gültigkeitsdatum gibt
	if (sel_zartpreis(Fd_ZArtPreis, zpreis->ARTIKEL_NR, zpreis->DATUMGUELTIGAB, &m_BufOldZPreis, errmld ) == 0)
		lStatus = FdWithoutWorkUpdateRecord( *Fd_ZArtPreis, zpreis, &m_BufOldZPreis, PK, errmld);
	else	
		lStatus = FdWithoutWorkInsertRecord( *Fd_ZArtPreis, zpreis, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nzartpreis (Insert/Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteZAPflege(zpreis->ARTIKEL_NR, zpreis->DATUMGUELTIGAB, errmld);
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int openCs_export_price( char *dbexp, const long art_nr, char* errmld )
{
	int status;
	char sql[500];

	fd_sel_export_price = -1;

	sprintf( sql, 
		"select artikel_nr, datumgueltigab, grosso, aep, avp from %s:zartpreis "
		"where artikel_nr = %ld " 
		"order by datumgueltigab desc ",
		dbexp, art_nr );

	status = SqlOpenCsWh( &fd_sel_export_price, sql );
		
	if ( status != 0 )
	{
		strcat( errmld, "\nzartpreis (open cursor): \n" );
		strcat( errmld, DynErrmld() );
	}

	return status;
}

/* ------------------------------------------------------------------- */
int closeCs_export_price(  )
{
	return SqlCloseCs( fd_sel_export_price );
}

/* ------------------------------------------------------------------- */
int fetchNext_export_price( struct PRICE_IMPORTDATA * impdata, char* errmld )
{
	int status = 0;

	if (fd_sel_export_price <= 0)
		return -1;

	status = SqlFetch( fd_sel_export_price, 1, impdata, NULL );
	
	if ( status != 0 && status != 100 )
	{
		strcat( errmld, "\nzartpreis (fetch): \n" );
		strcat( errmld, DynErrmld() );
	}

	if (status != 0)
		closeCs_export_price();

	return status;
}

/* ------------------------------------------------------ */

long StartTransaction( char *errmld )
{
   long s;
   s = SqlBeginWork( );
   if ( s != 0 )
     strcpy( errmld, DynErrmld() );
   return s;
}

long CommitTransaction( char *errmld )
{
   long s;
   s = SqlCommitWork( );
   if ( s != 0 )
     strcpy( errmld, DynErrmld() );
   return s;
}

void CancelTransaction( )
{
   SqlRollbackWork( );
}

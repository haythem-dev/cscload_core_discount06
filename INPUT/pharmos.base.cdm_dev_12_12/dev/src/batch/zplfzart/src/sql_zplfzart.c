/* ---------------------------------------------------------------------- *
 * Aufgabe        : SQL - Funktionen für zplfzart					      *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 19.09.2007                                          *
 *   Autor          : Rolf Raab                                           *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include <hdatum/phodate.h>

#include <eklibs/wdbups/wpp_dbas.h>

#include "sql_zplfzart.h"

#include "g_lfzartik.h"

#define DEZAP_SA_COM		"24"
#define DEZAP_SA_ART_NAM	"23"

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
int upd_zartikel ( const int *Fd_ZArtikel, struct ZARTIKEL *zart, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_ZArtikel < 0 ) 
		return -1;

	sprintf ( PK, "artikel_nr=%7ld", zart->ARTIKEL_NR );

	lStatus = FdUpdateRecord( *Fd_ZArtikel, zart, &m_BufOldZArt, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nzartikel (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WriteZAPflege(zart->ARTIKEL_NR, zapflege_datum, errmld);
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
struct ZARTIKEL* getOldBufZArt ()
{
	return &m_BufOldZArt;
}

/* ------------------------------------------------------------------- */
struct CHEALTHINSURANCE* getOldBufCHi ()
{
	return &m_BufOldCHi;
}

/* ------------------------------------------------------------------- */
struct CARTICLECODES* getOldBufCodes ()
{
	return &m_BufOldCodes;
}

/* ------------------------------------------------------------------- */
int sel_chealthinsurance	( const int *Fd_CHealthInsurance, const long hiid, struct CHEALTHINSURANCE *chi, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_CHealthInsurance < 0 ) 
		return -1;

	sprintf ( PK, "healthinsuranceid=%ld", hiid );

	lStatus = FdReadRecord( *Fd_CHealthInsurance, PK, chi, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldCHi = *chi;  
	}
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\nchealthinsurance (Suche nach ID): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_chealthinsurance	( const int *Fd_CHealthInsurance, struct CHEALTHINSURANCE *chi, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_CHealthInsurance < 0 ) 
		return -1;

	sprintf ( PK, "healthinsuranceid=%ld", chi->HEALTHINSURANCEID );

	lStatus = FdUpdateRecord( *Fd_CHealthInsurance, chi, &m_BufOldCHi, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nchealthinsurance (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_chealthinsurance	( const int *Fd_CHealthInsurance, struct CHEALTHINSURANCE *chi, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_CHealthInsurance < 0 ) 
		return -1;

	sprintf ( PK, "healthinsuranceid=%ld", chi->HEALTHINSURANCEID );

	lStatus = FdInsertRecord( *Fd_CHealthInsurance, chi, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nchealthinsurance (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_chealthinsurance	( const int *Fd_CHealthInsurance, struct CHEALTHINSURANCE *chi, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_CHealthInsurance < 0 ) 
		return -1;

	sprintf ( PK, "healthinsuranceid=%ld", chi->HEALTHINSURANCEID );

	lStatus = FdDeleteRecord( *Fd_CHealthInsurance, chi, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nchealthinsurance (Delete einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

int sel_chealthinsurancearticle	( const int *Fd_CHealthInsuranceArticles, const long higroup, const long articleno, struct CHEALTHINSURANCEARTICLES *chia, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_CHealthInsuranceArticles < 0 ) 
		return -1;

	sprintf ( PK, "healthinsurancegroup=%ld and articleno=%ld", higroup, articleno );

	lStatus = FdReadRecord( *Fd_CHealthInsuranceArticles, PK, chia, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcat( errmld, "\nchealthinsurancearticles (Suche): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

int ins_chealthinsurancearticle	( const int *Fd_CHealthInsuranceArticles, struct CHEALTHINSURANCEARTICLES *chia, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_CHealthInsuranceArticles < 0 ) 
		return -1;

	sprintf ( PK, "healthinsurancegroup=%ld and articleno=%7ld", chia->HEALTHINSURANCEGROUP, chia->ARTICLENO );

	lStatus = FdInsertRecord( *Fd_CHealthInsuranceArticles, chia, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nchealthinsurancearticles (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

int del_chealthinsurancearticle	( const int *Fd_CHealthInsuranceArticles, struct CHEALTHINSURANCEARTICLES *chia, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_CHealthInsuranceArticles < 0 ) 
		return -1;

	sprintf ( PK, "healthinsurancegroup=%ld and articleno=%7ld", chia->HEALTHINSURANCEGROUP, chia->ARTICLENO );

	lStatus = FdDeleteRecord( *Fd_CHealthInsuranceArticles, chia, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nchealthinsurancearticles (Delete einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
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
int  isNarcoticStillUnset ( char* atcCode, const long artNr )
{
	short narcSubFlag;
	char narcFlag[2];
	char psychoFlag[2];

	char sql[150];
	

	sprintf( sql, "select narcotic_substance_flag, btm, psychotrop from catccode, zartikel "
					"where code_atc = '%s' and artikel_nr = %ld", atcCode, artNr);
  
	if ( SqlRead( sql, &narcSubFlag, narcFlag, psychoFlag, NULL ) != 0 )
	{
		return 0;
	}

	if (narcSubFlag == 1 && *narcFlag != '1' && *psychoFlag == 'N')
		return 1;
	else
		return 0;
}


/* ------------------------------------------------------------------- */
int sel_chealthinsurancegroups	( const int *Fd_CHealthInsuranceGroups, const long higroup, const long hiid, struct CHEALTHINSURANCEGROUPS *chig, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_CHealthInsuranceGroups < 0 ) 
		return -1;

	sprintf ( PK, "healthinsurancegroup=%ld and healthinsuranceid=%ld", higroup, hiid );

	lStatus = FdReadRecord( *Fd_CHealthInsuranceGroups, PK, chig, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcat( errmld, "\nchealthinsurancegroups (Suche): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

int ins_chealthinsurancegroups	( const int *Fd_CHealthInsuranceGroups, struct CHEALTHINSURANCEGROUPS *chig, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_CHealthInsuranceGroups < 0 ) 
		return -1;

	sprintf ( PK, "healthinsurancegroup=%ld and healthinsuranceid=%ld", chig->HEALTHINSURANCEGROUP, chig->HEALTHINSURANCEID );

	lStatus = FdInsertRecord( *Fd_CHealthInsuranceGroups, chig, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nchealthinsurancegroups (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

int del_chealthinsurancegroups	( const int *Fd_CHealthInsuranceGroups, struct CHEALTHINSURANCEGROUPS *chig, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_CHealthInsuranceGroups < 0 ) 
		return -1;

	sprintf ( PK, "healthinsurancegroup=%ld and healthinsuranceid=%ld", chig->HEALTHINSURANCEGROUP, chig->HEALTHINSURANCEID );

	lStatus = FdDeleteRecord( *Fd_CHealthInsuranceGroups, chig, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nchealthinsurancegroups (Delete einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_carticlecodes	( const int *Fd_Atc, const long artnr, struct CARTICLECODES *codes, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Atc < 0 ) 
		return -1;

	sprintf ( PK, "code_type=2 and articleno=%ld", artnr );

	lStatus = FdReadRecord( *Fd_Atc, PK, codes, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldCodes = *codes;  
	}
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\ncarticlecodes (Suche nach Atc): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_carticlecodes	( const int *Fd_Atc, struct CARTICLECODES *codes, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Atc < 0 ) 
		return -1;

	sprintf ( PK, "code_type=2 and articleno=%7ld", codes->ARTICLENO );

	lStatus = FdUpdateRecord( *Fd_Atc, codes, &m_BufOldCodes, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\ncarticlecodes (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WriteZAPflege(codes->ARTICLENO, codes->DATE_CHANGED, errmld);
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_carticlecodes	( const int *Fd_Atc, struct CARTICLECODES *codes, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Atc < 0 ) 
		return -1;

	sprintf ( PK, "code_type=2 and articleno=%7ld", codes->ARTICLENO );

	lStatus = FdInsertRecord( *Fd_Atc, codes, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\ncarticlecodes (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WriteZAPflege(codes->ARTICLENO, codes->DATE_CHANGED, errmld);

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_carticlecodes	( const int *Fd_Atc, struct CARTICLECODES *codes, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Atc < 0 ) 
		return -1;

	sprintf ( PK, "code_type=2 and articleno=%7ld", codes->ARTICLENO );

	lStatus = FdDeleteRecord( *Fd_Atc, codes, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\ncarticlecodes (Delete einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	else
		WriteZAPflege(codes->ARTICLENO, codes->DATE_CHANGED, errmld);

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_ean ( const int *Fd_Ean, const char* ean, const long art_nr, struct EAN *ean_struct, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Ean < 0 ) 
		return -1;

	sprintf ( PK, "ean_nr='%s' and artikel_nr=%ld", ean, art_nr );

	lStatus = FdReadRecord( *Fd_Ean, PK, ean_struct, errmld );
	
	if ( lStatus == 0 )
		return 3;
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\nean (Suche nach EAN und PZN): \n" );
		strcat( errmld, DynErrmld() );
	}

	sprintf ( PK, "ean_nr='%s'", ean );

	lStatus = FdReadRecord( *Fd_Ean, PK, ean_struct, errmld );
	
	if ( lStatus == 0 )
		return 4;
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\nean (Suche nach EAN): \n" );
		strcat( errmld, DynErrmld() );
	}

	sprintf ( PK, "artikel_nr=%ld", art_nr );

	lStatus = FdReadRecord( *Fd_Ean, PK, ean_struct, errmld );
	
	if ( lStatus == 0 )
		return 5;
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\nean (Suche nach PZN): \n" );
		strcat( errmld, DynErrmld() );
	}

	return 0;
}

/* ------------------------------------------------------------------- */
int ins_ean ( const int *Fd_Ean, struct EAN *ean_struct, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Ean < 0 ) 
		return -1;

	sprintf ( PK, "artikel_nr=%7ld and ean_nr = '%s'", ean_struct->ARTIKEL_NR, ean_struct->EAN_NR );

	lStatus = FdInsertRecord( *Fd_Ean, ean_struct, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nean (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
/*	else
		WriteZAPflege(ean_struct->ARTIKEL_NR, tages_datum, errmld); */
	
	return lStatus;
}

/* ---------------------------------------------------------------------- *
 * Aufgabe        : SQL - Funktionen für zpdcartik					      *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 26.01.2005                                            *
 * ---------------------------------------------------------------------- */
/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include <hdatum/phodate.h>

#include <eklibs/wdbups/wpp_dbas.h>

#include <voodoo_table_header/clioart.h>
#include <voodoo_table_header/cliart.h>
#include <voodoo_table_header/clicompany.h>
#include <voodoo_table_header/cliproduct.h>
#include <voodoo_table_header/cliproductgrp.h>
#include <voodoo_table_header/cliohsatz.h>
#include <voodoo_table_header/clihsatz.h>
#include <voodoo_table_header/catccode.h>
#include <voodoo_table_header/cassortmentcode.h>

#include "g_liartik.h"
#include "subartdan.h"
#include "subartcomp.h"


static struct CLIOART	m_BufOldOart;
static struct CLIART	m_BufOldArt;
static struct CLICOMPANY m_BufOldComp;
static struct CLIPRODUCT m_BufOldProd;
static struct CLIPRODUCTGRP m_BufOldProdGrp;
static struct CASSORTMENTCODE m_BufOldAssort;
static struct CATCCODE m_BufOldAtc;

static int fd_clioart;
static int fd_cliproductgrp;
static int fd_cliohsatz;


int sel_productgrp	( const long prdno, char *errmld )
{
	char sql[100];
    int status;
    
    sprintf( sql, "select prdgrpcd from cliproductgrp where prdno=%ld",
                  prdno );

	status = SqlOpenCsWh ( &fd_cliproductgrp, sql );

    if ( status != 0 && status != 100 )
	{
		strcpy( errmld, "cliproductgrp (Suche nach Prdno - OpenCs): " );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

int fetch_next_productgrp( char* prdgrpcd, char *errmld )
{
	int status;
    
	status = SqlFetch ( fd_cliproductgrp, 1, prdgrpcd, NULL );

	if (status == 100)
	{
		SqlCloseCs ( fd_cliproductgrp );
	}
	else if (status != 0)
	{
		strcpy( errmld, "cliproductgrp (Suche nach Prdno - Fetch): " );
		strcat( errmld, DynErrmld() );
	}

	return status;
}

/* ------------------------------------------------------------------- */
int fetch_next (long *pzn, char *errmld)
{
	int status;
    
	status = SqlFetch ( fd_clioart, 1, pzn, NULL );

	if (status == 100)
	{
		SqlCloseCs ( fd_clioart );
	}
	else if (status != 0)
	{
		strcpy( errmld, "clioart (Suche nach Prdno - Fetch): " );
		strcat( errmld, DynErrmld() );
	}

	return status;
}

/* ------------------------------------------------------------------- */
int sel_phar(  const long prdno, char *errmld )
{
    char sql[100];
    int status;
    
    sprintf( sql, "select phar from clioart where prdno=%ld",
                  prdno );

	status = SqlOpenCsWh ( &fd_clioart, sql );

    if ( status != 0 && status != 100 )
	{
		strcpy( errmld, "clioart (Suche nach Prdno - OpenCs): " );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
int sel_zartpreis	( const long art_nr, const long datgueltab, 
					 // currently not needed: double *aep, double* gep, double *avp, 
					 double *lbp, char *errmld)
{
    char sql[250];
    int status;
    
    sprintf( sql, "select "
					//"p.aep, p.grosso, p.avp, "
					"p.lieferbasispreis " 
					"from zartpreis p " 
					"where p.artikel_nr=%ld and p.datumgueltigab = " 
					"(select max(DATUMGUELTIGAB) from ZARTPREIS where " 
					"DATUMGUELTIGAB<=%ld " 
					"and ARTIKEL_NR=%ld)", 
					art_nr, datgueltab, art_nr );

    status = SqlRead( sql, /*aep, gep, avp,*/ lbp, NULL );
    if ( status != 0 )
	{
		strcpy( errmld, "zartpreis (Select von Preisen): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
int sel_zartikel	( const long art_nr, long *her_nr, long *awl1, char* name, long *datum_ah, 
					char* preis0, char* gesperrt, char* privat, char* verfall, char* vb_apo, char* vb_inland, char* vb_kanton, char* vb_kuenzle, char* vb_spital, 
					char* phyto, char* homeo, char* anthro, char* tierarznei, char* med, char* impfst, char* chargenartikel, double *herst_proz, char *errmld)
{
    char sql[1500];
    int status;
    
    sprintf( sql, "select z.artikel_nr, hersteller_nr, awl1, artikel_name, datum_ah, "
					"preis0artikel, artikel_gesperrt, privatsortiment, verfall, VERTRBIND_INLAND, VERTRBIND_KANTONAL, VERTRBIND_KUENZLE, VERTRBIND_NUR_APO, VERTRBIND_NUR_SPIT, "
					"PHYTOPHARMAKON, HOMOEOPATHIKUM, ANTHROPOSOPHIKUM, TIERARZNEI, MEDIZINPRODUKT, IMPFSTOFF, CHARGENARTIKEL, HERST_PROZENT "
					"from zartikel z, zartswitzerland s where z.artikel_nr=%ld and z.artikel_nr = s.artikel_nr",
                  art_nr );

    status = SqlRead( sql, &art_nr, her_nr, awl1, name, datum_ah, preis0, gesperrt, privat, verfall, vb_inland, vb_kanton, vb_kuenzle, vb_apo, vb_spital, 
							phyto, homeo, anthro, tierarznei, med, impfst, chargenartikel, herst_proz, NULL );

    if ( status != 0 && status != 100)
	{
		strcpy( errmld, "zartikel (Suche nach Artikelnr): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
int sel_warengruppe	( const long art_nr, char* art, char* wgr, char *errmld)
{
    char sql[150];
    int status;
    
    sprintf( sql, "select warengruppe from zartwg where artikel_nr = %ld and art = '%s' ",
                  art_nr, art );

    status = SqlRead( sql, wgr, NULL );
    if ( status != 0 && status != 100)
	{
		strcpy( errmld, "zartwg (Suche nach PZN / Art): " );
		strcat( errmld, DynErrmld() );
	}
    return status;

}

/* ------------------------------------------------------------------- */
int sel_ersatz	( const long ersatz_nr, char *errmld)
{
    char sql[150];
    int status;
    
    sprintf( sql, "select artikel_nr from zartikel where artikel_nr = %ld UNION select phar from cliart where phar = %ld ",
                  ersatz_nr, ersatz_nr );

    status = SqlRead( sql, &ersatz_nr, NULL );
    if ( status != 0 && status != 100)
	{
		strcpy( errmld, "zartikel / cliart (Suche nach ErsatzNr): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
long checkGtin14Exists(  long artno, char * gtin )
{
    char sql[300];
    long status;
    double dCount;

	sprintf( sql, "select count(*) from carticlecodes where article_code = '%s' and articleno != %ld and code_type in (select code_type from ccodetypes where artnr_substitute = 1) ", 
					gtin, artno );
	    
	status = SqlRead( sql, &dCount, NULL );
    
	if ( status != 0 || dCount > 0 ) 
		return 1;
	else 
		return 0;
}

/* ------------------------------------------------------------------- */
int sel_ean_by_pzn	( const long art_nr, char* ean_nr, char *errmld)
{
    char sql[150];
    int status;
    
    sprintf( sql, "select ean_nr "
					"from ean where artikel_nr=%ld",
                  art_nr );

    status = SqlRead( sql, ean_nr, NULL );
    if ( status != 0 && status != 100)
	{
		strcpy( errmld, "ean (Suche nach Artikelnr): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
int sel_ean_by_ean	( long *art_nr, char* ean_nr, char *errmld)
{
    char sql[150];
    int status;
    
    sprintf( sql, "select artikel_nr "
					"from ean where ean_nr='%s'",
                  ean_nr );

    status = SqlRead( sql, art_nr, NULL );
    if ( status != 0 && status != 100)
	{
		strcpy( errmld, "ean (Suche nach ean): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
int read_cliproduct_into_cliartBuf( struct CLIART * li, const long prdno, char *errmld )
{
	char sql[1500];
    int status;

    sprintf( sql, "select blood, gencd, atc "
					"from cliproduct where prdno=%ld", prdno);

	status = SqlRead( sql, &li->BLOOD, li->GENCD, li->ATC, NULL );

	if ( status != 0 && status != 100)
	{
		strcpy( errmld, "cliproduct (Suche nach prdno): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
int read_clioart_into_cliartBuf	( struct CLIART * li, char *errmld )
{
	char sql[1500];
    int status;

    sprintf( sql, "select CDSO1, PRDNO, SMCAT, SMNO, CLINCD, VAT, COOL, CDBG, BG, EXP, QTY, DSCRD, DSCRF, DSCRLONGD, DSCRLONGF, QTYUD, QTYUF, PCKTYPD, PCKTYPF, NOPCS, "
					"NINCD, DEPCD, OUTSAL, STTOX, CE, SMCDAT, SIST, ESIST, BIOCID, BAGNO, BAGDOSSIER, COMPNO, BC, GTIN14, PHAR2, VDAT, PRICE_PEXF, PRICE_PPUB, MIGCD, GENCD, ATC, SUPPLNO, ARTNO1, "
					"SALECD, GRPCD, BLOOD, SDS_DATE_DE, SDS_DATE_IT, SDS_DATE_EN, SDS_DATE_FR, FMD_FLAG, G_UN_NR, "
					"MDCLASS, LAGERKLASSE, GG_KLASSCODE, GG_VERPACKCODE, CDVAL, HAZARD_STMT"
					"PICTOGRAM01_FLAG, PICTOGRAM02_FLAG, PICTOGRAM03_FLAG, PICTOGRAM04_FLAG, "
					"PICTOGRAM05_FLAG, PICTOGRAM06_FLAG, PICTOGRAM07_FLAG, PICTOGRAM08_FLAG, PICTOGRAM09_FLAG, "
					//"GS_EXPLOSION, GS_HOCHENTZ, GS_LEICHTENTZ, GS_BRAND, GS_AETZEND, GS_SEHRGIFTIG, GS_GIFTIG, GS_GESUNDHSCH, GS_REIZEND, GS_UMWELT, "
					" from clioart where phar=%ld",
                  li->PHAR );

    status = SqlRead( sql, li->CDSO1, &li->PRDNO, li->SMCAT, &li->SMNO, li->CLINCD, &li->VAT, li->COOL, li->CDBG, li->BG, &li->EXP, &li->QTY,
							li->DSCRD, li->DSCRF, li->DSCRLONGD, li->DSCRLONGF, li->QTYUD, li->QTYUF, li->PCKTYPD, li->PCKTYPF, &li->NOPCS,
							&li->NINCD, li->DEPCD, &li->OUTSAL, li->STTOX, li->CE, &li->SMCDAT, &li->SIST, &li->ESIST, &li->BIOCID, li->BAGNO, 
							&li->BAGDOSSIER, &li->COMPNO, li->BC, li->GTIN14, &li->PHAR2, &li->VDAT, &li->PRICE_PEXF, &li->PRICE_PPUB, li->MIGCD, li->GENCD, li->ATC, &li->SUPPLNO, li->ARTNO1,
							li->SALECD, li->GRPCD, &li->BLOOD, &li->SDS_DATE_DE, &li->SDS_DATE_IT, &li->SDS_DATE_EN, &li->SDS_DATE_FR, &li->FMD_FLAG, li->G_UN_NR,
							li->MDCLASS, li->LAGERKLASSE, li->GG_KLASSCODE, li->GG_VERPACKCODE, li->CDVAL, li->HAZARD_STMT,
							&li->PICTOGRAM01_FLAG, &li->PICTOGRAM02_FLAG, &li->PICTOGRAM03_FLAG, &li->PICTOGRAM04_FLAG, 
							&li->PICTOGRAM05_FLAG, &li->PICTOGRAM06_FLAG, &li->PICTOGRAM07_FLAG, &li->PICTOGRAM08_FLAG, &li->PICTOGRAM09_FLAG,
							//li->GS_EXPLOSION, li->GS_HOCHENTZ, li->GS_LEICHTENTZ, li->GS_BRAND, li->GS_AETZEND, li->GS_SEHRGIFTIG, li->GS_GIFTIG, li->GS_GESUNDHSCH, li->GS_REIZEND, li->GS_UMWELT,
							NULL );

	if ( status != 0 && status != 100)
	{
		strcpy( errmld, "clioart (Suche nach phar): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
int sel_cliart (const int *Fd_Cliart, const long art_nr, const long lidatumnr, struct CLIART *li, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Cliart < 0 ) 
		return -1;

	sprintf ( PK, "linr=%ld and phar=%ld", lidatumnr, art_nr );
	
	lStatus = FdReadRecord( *Fd_Cliart, PK, li, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldArt = *li;  // gelesenen Satz sichern
	}
	else if ( lStatus != 100 )
	{
		strcpy( errmld, "cliart (Suche nach Art): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_cassortmentcode	( const int *Fd_Cassortmentcode, char* code, struct CASSORTMENTCODE *assortcode, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Cassortmentcode < 0 ) 
		return -1;

	sprintf ( PK, "code_assortment='%s'", code );
	
	lStatus = FdReadRecord( *Fd_Cassortmentcode, PK, assortcode, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldAssort = *assortcode;  // gelesenen Satz sichern
	}
	else if ( lStatus != 100 )
	{
		strcpy( errmld, "Cassortmentcode (Suche nach Code): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_catccode	( const int *Fd_Catccode, char* code, struct CATCCODE *atccode, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Catccode < 0 ) 
		return -1;

	sprintf ( PK, "code_atc='%s'", code );
	
	lStatus = FdReadRecord( *Fd_Catccode, PK, atccode, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldAtc = *atccode;  // gelesenen Satz sichern
	}
	else if ( lStatus != 100 )
	{
		strcpy( errmld, "Catccode (Suche nach Code): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_clicompany (const int *Fd_Clicompany, const long prtno, struct CLICOMPANY *licomp, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Clicompany < 0 ) 
		return -1;

	sprintf ( PK, "prtno=%ld", prtno );
	
	lStatus = FdReadRecord( *Fd_Clicompany, PK, licomp, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldComp = *licomp;  // gelesenen Satz sichern
	}
	else if ( lStatus != 100 )
	{
		strcpy( errmld, "clicompany (Suche nach PrtNo): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_clioart		(const int *Fd_Clioart, const long art_nr, struct CLIOART *lio, char *errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Clioart < 0 ) 
		return -1;

	sprintf ( PK, "phar=%ld", art_nr );

	lStatus = FdReadRecord( *Fd_Clioart, PK, lio, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldOart = *lio;  // gelesenen Satz sichern
	}
	else if ( lStatus != 100 )
	{
		strcpy( errmld, "clioart (Suche nach OrigArt): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cliart		( const int  *Fd_Cliart, struct CLIART * li, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Cliart < 0 ) 
		return -1;

	sprintf ( PK, "linr=%ld and satznr=%ld", li->LINR, li->SATZNR );

	lStatus = FdInsertRecord( *Fd_Cliart, li, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cliart (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_catccode	( const int *Fd_Catccode, struct CATCCODE * atccode, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Catccode < 0 ) 
		return -1;

	sprintf ( PK, "code_atc='%s'", atccode->CODE_ATC );

	lStatus = FdInsertRecord( *Fd_Catccode, atccode, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "catccode (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cassortmentcode ( const int *Fd_Cassortmentcode, struct CASSORTMENTCODE * assortcode, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Cassortmentcode < 0 ) 
		return -1;

	sprintf ( PK, "code_assortment='%s'", assortcode->CODE_ASSORTMENT );

	lStatus = FdInsertRecord( *Fd_Cassortmentcode, assortcode, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "Cassortmentcode (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_clicompany		( const int  *Fd_Clicompany, struct CLICOMPANY * licomp, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Clicompany < 0 ) 
		return -1;

	sprintf ( PK, "prtno=%ld", licomp->PRTNO );

	lStatus = FdInsertRecord( *Fd_Clicompany, licomp, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "clicompany (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}


/* ------------------------------------------------------------------- */
int ins_clioart		( const int  *Fd_Clioart, struct CLIOART * lio, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Clioart < 0 ) 
		return -1;

	sprintf ( PK, "phar=%ld", lio->PHAR );

	lStatus = FdInsertRecord( *Fd_Clioart, lio, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "clioart (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_cliart		( const int  *Fd_Cliart, struct CLIART * li, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Cliart < 0 ) 
		return -1;

	sprintf ( PK, "linr=%ld and satznr=%ld", li->LINR, li->SATZNR );

	lStatus = FdUpdateRecord( *Fd_Cliart, li, &m_BufOldArt, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cliart (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_clicompany		( const int  *Fd_Clicompany, struct CLICOMPANY * licomp, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Clicompany < 0 ) 
		return -1;

	sprintf ( PK, "prtno=%ld", licomp->PRTNO );

	lStatus = FdUpdateRecord( *Fd_Clicompany, licomp, &m_BufOldComp, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "clicompany (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_clioart		( const int  *Fd_Clioart, struct CLIOART * lio, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Clioart < 0 ) 
		return -1;

	sprintf ( PK, "phar=%ld", lio->PHAR );

	lStatus = FdUpdateRecord( *Fd_Clioart, lio, &m_BufOldOart, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "clioart (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

long sel_count_cliohsatz(const long phar, long* count, char* errmld)
{
	char sql[100];
	long lStatus;
	sprintf( sql, "cliohsatz where phar=%ld", phar);

	lStatus = SqlCount(sql, count);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cliohsatz (count): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
long exists_cliohsatz(const long phar, const char* hazardnoteid, long* result, char* errmld)
{
	char sql[100];
	long lStatus;
	long count = 0;
	sprintf( sql, "cliohsatz where phar=%ld and hazardnoteid='%s'", phar, hazardnoteid);

	lStatus = SqlCount(sql, &count);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cliohsatz (count): " );
		strcat( errmld, DynErrmld() );
	}

	*result = count;

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_all_cliohsatz(const int* Fd_Cliohsatz, const long phar, char* errmld)
{
	int status;
	char sql[100];

	sprintf(sql, "DELETE FROM cliohsatz where phar=%ld", phar);

	status = SqlExecuteImm(sql);

	if (status == 100)
	{
			status = 0;
	}

	return status;
}

/* ------------------------------------------------------------------- */
long ins_cliohsatz(const int* Fd_Cliohsatz, struct CLIOHSATZ* cliohasatz, char* errmld)
{
	long lStatus;
	char PK [100];

	if(*Fd_Cliohsatz < 0)
	{
		return -1;
	}

	sprintf(PK, "phar=%ld AND hazardnoteid='%s'", cliohasatz->PHAR, cliohasatz->HAZARDNOTEID);

	lStatus = FdInsertRecord(*Fd_Cliohsatz, cliohasatz, PK, errmld);

	if(lStatus != 0)
	{
		strcpy( errmld, "cliohasatz (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_all_clihsatz(const int* Fd_Clihsatz, const long phar, const long linr, char* errmld)
{
	int status;
	char sql[100];

	sprintf(sql, "DELETE FROM clihsatz where linr=%ld AND phar=%ld", linr, phar);

	status = SqlExecuteImm(sql);

	if (status == 100)
	{
			status = 0;
	}

	return status;
}

/* ------------------------------------------------------------------- */
int ins_clihsatz(const int* Fd_Clihsatz, struct CLIHSATZ* clihasatz, char* errmld)
{
	long lStatus;
	char PK [100];

	if(*Fd_Clihsatz < 0)
	{
		return -1;
	}

	sprintf(PK, "linr=%ld AND phar=%ld AND hazardnoteid='%s'", clihasatz->LINR, clihasatz->PHAR, clihasatz->HAZARDNOTEID);

	lStatus = FdInsertRecord(*Fd_Clihsatz, clihasatz, PK, errmld);

	if(lStatus != 0)
	{
		strcpy( errmld, "clihasatz (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
long exists_hsatz(const char* hazardnoteid, long* result, char* errmld)
{
	char sql[100];
	long lStatus;
	long count = 0;
	sprintf( sql, "chazardnote where hazardnoteid='%s'", hazardnoteid);

	lStatus = SqlCount(sql, &count);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "chazardnote (count): " );
		strcat( errmld, DynErrmld() );
	}

	*result = count;

	return lStatus;
}

/* ------------------------------------------------------------------- */
int read_clio_subartdan(struct SUBARTDAN* subartdan, char *errmld)
{
	char sql[1500];
	int status;

    sprintf( sql, "select PICTOGRAM01_FLAG, PICTOGRAM02_FLAG, PICTOGRAM03_FLAG, PICTOGRAM04_FLAG, "
					"PICTOGRAM05_FLAG, PICTOGRAM06_FLAG, PICTOGRAM07_FLAG, PICTOGRAM08_FLAG, PICTOGRAM09_FLAG, "
					"GS_EXPLOSION, GS_HOCHENTZ, GS_LEICHTENTZ, GS_BRAND, GS_AETZEND, GS_SEHRGIFTIG, GS_GIFTIG, GS_GESUNDHSCH, GS_REIZEND, GS_UMWELT "
					//", SDS_DATE_DE "
					"from clioart where phar=%ld",
					subartdan->PHAR);

	status = SqlRead( sql, &subartdan->PICTOGRAM01_FLAG, &subartdan->PICTOGRAM02_FLAG, &subartdan->PICTOGRAM03_FLAG, &subartdan->PICTOGRAM04_FLAG, 
							&subartdan->PICTOGRAM05_FLAG, &subartdan->PICTOGRAM06_FLAG, &subartdan->PICTOGRAM07_FLAG, &subartdan->PICTOGRAM08_FLAG, &subartdan->PICTOGRAM09_FLAG,
							subartdan->GS_EXPLOSION, subartdan->GS_HOCHENTZ, subartdan->GS_LEICHTENTZ, subartdan->GS_BRAND, subartdan->GS_AETZEND, 
							subartdan->GS_SEHRGIFTIG, subartdan->GS_GIFTIG, subartdan->GS_GESUNDHSCH, subartdan->GS_REIZEND, subartdan->GS_UMWELT,
							// &subartdan->SDS_DATE_DE,
							NULL );

	if ( status != 0 && status != 100)
	{
		strcpy( errmld, "subartdan (from clioart): " );
		strcat( errmld, DynErrmld() );
	}

	return status;
}

/* ------------------------------------------------------------------- */
int read_clio_subartcomp(struct SUBARTCOMP* subartcomp, char *errmld)
{
	char sql[1500];
	int status;

	sprintf( sql, "select COMPNO, SUPPLNO, ARTNO1 from clioart where phar=%ld", subartcomp->PHAR);

	status = SqlRead(sql, &subartcomp->COMPNO, &subartcomp->SUPPLNO, subartcomp->ARTNO1, NULL);

	if ( status != 0 && status != 100)
	{
		strcpy( errmld, "subartcomp (from clioart): " );
		strcat( errmld, DynErrmld() );
	}

	return status;
}

/* ------------------------------------------------------------------- */
long exists_cliosatz(const long phar, long* result, char* errmld)
{
	char sql[100];
	long lStatus;
	long count = 0;
	sprintf( sql, "clioart where phar=%ld", phar);

	lStatus = SqlCount(sql, &count);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "clioart (count): " );
		strcat( errmld, DynErrmld() );
	}

	if(count > 0)
	{
		count = 1;
	}

	*result = count;

	return lStatus;
}

int sel_cliproductgrp(const int *Fd_Cliproductgrp, const long prdno, const char* prdgrpcd, struct CLIPRODUCTGRP *liproductgrp, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if(*Fd_Cliproductgrp < 0)
	{
		return -1;
	}

	sprintf(PK, "prdno=%ld and prdgrpcd='%s'", prdno, prdgrpcd);
	
	lStatus = FdReadRecord(*Fd_Cliproductgrp, PK, liproductgrp, errmld);
	
	if(lStatus == 0)
	{
		m_BufOldProdGrp = *liproductgrp;
	}
	else if ( lStatus != 100 )
	{
		strcpy( errmld, "cliproductgrp (Suche nach PrtNo): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

int ins_cliproductgrp(const int *Fd_Cliproductgrp, struct CLIPRODUCTGRP * liproductgrp, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if (*Fd_Cliproductgrp < 0)
	{
		return -1;
	}

	sprintf(PK, "prdno=%ld and prdgrpcd='%s'", liproductgrp->PRDNO, liproductgrp->PRDGRPCD);

	lStatus = FdInsertRecord( *Fd_Cliproductgrp, liproductgrp, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cliproductgrp (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_cliproductgrp(const int* Fd_Cliproductgrp, const long prdno, char* errmld)
{
	int status;
	char sql[100];

	sprintf(sql, "DELETE FROM cliproductgrp where prdno=%ld", prdno);

	status = SqlExecuteImm(sql);

	if (status == 100)
	{
		status = 0;
	}

	return status;
}

/* ------------------------------------------------------------------- */
int sel_cliproduct(const int *Fd_Cliproduct, const long prdno, struct CLIPRODUCT *liproduct, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if(*Fd_Cliproduct < 0)
	{
		return -1;
	}

	sprintf(PK, "prdno=%ld", prdno);
	
	lStatus = FdReadRecord(*Fd_Cliproduct, PK, liproduct, errmld);
	
	if(lStatus == 0)
	{
		m_BufOldProd = *liproduct;
	}
	else if ( lStatus != 100 )
	{
		strcpy( errmld, "cliproduct (Suche nach PrtNo): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cliproduct( const int  *Fd_Cliproduct, struct CLIPRODUCT * liproduct, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if (*Fd_Cliproduct < 0)
	{
		return -1;
	}

	sprintf(PK, "prdno=%ld", liproduct->PRDNO);

	lStatus = FdInsertRecord( *Fd_Cliproduct, liproduct, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cliproduct (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_cliproduct(const int *Fd_Cliproduct, struct CLIPRODUCT * liproduct, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Cliproduct < 0 ) 
		return -1;

	sprintf(PK, "prdno=%ld", liproduct->PRDNO);

	lStatus = FdUpdateRecord( *Fd_Cliproduct, liproduct, &m_BufOldProd, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cliproduct (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

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

#include <voodoo_table_header/zdcoart.h>
#include <voodoo_table_header/zdcart.h>

#include "g_dcartik.h"


static struct ZDCOART m_BufOld;

/* ------------------------------------------------------------------- */
int sel_ccomgroupprop(const char * const wrgrp, char *taxkz, char *adgep, char *adaep, char *adavp, char *adbez)
{
	char sql[200];
    int status;
    
	sprintf( sql, "select tax_group, adopt_gep_from_dc, adopt_aep_from_dc, adopt_avp_from_dc, adopt_abez_from_dc "
					"from ccomgroupprop where commodity_group='%s'",
					wrgrp );

    status = SqlRead( sql, taxkz, adgep, adaep, adavp, adbez, NULL );

    return status;
}

/* ------------------------------------------------------------------- */
int sel_herstellnr(  const long art_nr, long *her_nr, char *errmld )
{
    char sql[100];
    int status;
    
    sprintf( sql, "select hersteller_nr from zartikel where artikel_nr=%ld",
                  art_nr );

    status = SqlRead( sql, her_nr, NULL );
    if ( status != 0 )
	{
		strcpy( errmld, "zartikel (Suche nach Herstellernr): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
int sel_zartpreis	( const long art_nr, const long datgueltab, double *aep, 
					 double* gep, double *avp, double *herst_prozent, char *errmld)
{
    char sql[250];
    int status;
    
    sprintf( sql, "select p.aep, p.grosso, p.avp, p.herst_prozent " 
					"from zartpreis p " 
					"where p.artikel_nr=%ld and p.datumgueltigab = " 
					"(select max(DATUMGUELTIGAB) from ZARTPREIS where " 
					"DATUMGUELTIGAB<=%ld " 
					"and ARTIKEL_NR=%ld)", 
					art_nr, datgueltab, art_nr );

    status = SqlRead( sql, aep, gep, avp, herst_prozent, NULL );
    if ( status != 0 )
	{
		strcpy( errmld, "zartpreis (Select von Preisen): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
int sel_warengrp	( const long art_nr, char* warengrp, char *errmld)
{
    char sql[100];
    int status;
    
    sprintf( sql, "select warengruppe from zartwg where artikel_nr=%ld and art = 2",
                  art_nr );

    status = SqlRead( sql, warengrp, NULL );
    if ( status != 0 )
	{
		strcpy( errmld, "zartwg (Suche nach Warengrp): " );
		strcat( errmld, DynErrmld() );
	}

	if ( strcmp (warengrp, "     ") == 0)
		status = 100;

    return status;
}

/* ------------------------------------------------------------------- */
int sel_zdkwgr	( const char* warengrp, char * sktof, char *errmld)
{
    char sql[100];
    int status;
    
    sprintf( sql, "select wgr_sktof from zdkwgr where wgr_gruppe = '%s'",
                  warengrp );

    status = SqlRead( sql, sktof, NULL );
    
	if ( status != 0 )
	{
		strcpy( errmld, "zdkwgr (Suche nach Warengrp): " );
		strcat( errmld, DynErrmld() );
	}

	return status;
}

/* ------------------------------------------------------------------- */
int sel_zdcoart		(const int *Fd_Zdcoart, const long art_nr, struct ZDCOART *dco, char *errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Zdcoart < 0 ) 
		return -1;


	sprintf ( PK, "dc_artikel_nr=%ld", art_nr );

	lStatus = FdReadRecord( *Fd_Zdcoart, PK, dco, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOld = *dco;  // gelesenen Satz sichern
	}
	else if ( lStatus != 100 )
	{
		strcpy( errmld, "zdcoart (Suche nach OrigArt): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zartikel	( const long art_nr, long * datum_ah, char * sondergr, char * skontof, char *errmld)
{
    char sql[150];
    int status;
    
    sprintf( sql, "select artikel_nr, datum_ah, sondergrosso, skontofaehig "
				"from zartikel where artikel_nr=%ld",
                  art_nr );

    status = SqlRead( sql, &art_nr, datum_ah, sondergr, skontof, NULL );
    if ( status != 0 && status != 100)
	{
		strcpy( errmld, "zartikel (Suche nach Artikelnr): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
int ins_zdcart		( const struct ZDCART * const dc, char* errmld)
{
    int status;
	char sql[2500];
	
   
    sprintf( sql, 
		"insert into zdcart (  %s  ) values ( "
		"%ld, %ld, '%s', '%s', '%s', "

		"%ld, '%s', '%s', '%s', "
		"'%s','%s','%s', '%s', "
		"'%s','%s','%s', %f, "
		"%f, %f, %f, '%s','%s', "

		"'%s','%s', '%s','%s', "
		"'%s','%s', %d, "
		"'%s','%s', %d, %d, %d, "
		"'%s','%s','%s','%s', "
		
		"'%s','%s','%s','%s', "
		"'%s', '%s',%ld, '%s', '%s', "
		"'%s','%s', %f, '%s', "
		"'%s','%s','%s', %ld, "
		
		"%ld, %ld, %ld, '%s', "
		"'%s','%s','%s','%s', "
		"'%s','%s', "

		"%ld, '%s', '%s', '%s', '%s', "
		"'%s', '%s', '%s', '%s','%s', '%s', '%s', '%s','%s', '%s', "
		"'%s', '%s', '%s', '%s','%s', '%s', '%s', '%s','%s', '%s', "
		"'%s', '%s', '%s', '%s', '%s', %ld, %ld, %ld)",

		PROJECTION_ZDCART,
		dc->DCNR, dc->SATZNR, dc->DCSTATUS, dc->NBSTATUS, dc->ZAENDERUNG,

		dc->DC_ARTIKEL_NR, dc->DC_ARTIKELKURZTEXT, dc->DC_ARTIKELTEXT, dc->DC_EINH_MENGE,
		dc->DC_EINH_EINHEIT, dc->DC_TAXKZ, dc->DC_ARTIKELKZ, dc->DC_REZEPTZEICHEN,
		dc->DC_KASSENZEICHEN, dc->DC_KASSENZ_ZUSATZ, dc->DC_CODEIN, dc->DC_GEP,
		dc->DC_AEP, dc->DC_KKP, dc->DC_AVP, dc->DC_OHNE_PREISBESCH, dc->DC_MWST_GH,
		
		dc->DC_MWST_AP, dc->DC_CHARGE, dc->DC_VERM_REZ_GEB, dc->DC_CODE_LIEFERANT,
		dc->DC_ARTNR_LIEFERANT, dc->DC_DEFEKTUR_LISTE, dc->DC_MINDESTABNAHME, 
		dc->DC_NV_WV, dc->DC_NV_GH, dc->DC_HOEHE, dc->DC_BREITE, dc->DC_TIEFE,
		dc->DC_LAGERHINWEIS, dc->DC_GEFAHRENSYMBOL, dc->DC_KZ_ABLAUF, dc->DC_APO_PFLICHTIG,
		
		dc->DC_REGISTER_NR, dc->DC_THERAPIEGRUPPE, dc->DC_ARTIKELGRUPPE, dc->DC_MINIK_BASISS,
		dc->DC_AECODE, dc->DC_CODE_HERSTELLER, dc->DC_GEWICHT, 
		// dc->DC_OELHV_GRUPPE, dc->DC_OELHV_OEKOKZ,
		"      ", "  ",
		dc->DC_ABGABEBES, dc->DC_VERKEHRSFAEHIG, dc->DC_KKP_HAUSAPO, dc->DC_HERKUNFTSLAND,
		// dc->DC_OELHV_SORT,
		"    ",
		dc->DC_HV_BOX, dc->DC_DARREICHFORM, dc->DC_DATUM_ANLAGE,
		
		dc->DC_DATUM_AENDER, dc->DC_DATUMGUELTIGAB, dc->DC_LFD_NR, dc->DC_NEUANLEGER,
		// dc->DC_PARTNER, dc->DC_REFERENZ_NR,
		"     ", "         ",
		dc->DC_NICHTUEBERGH, dc->DC_WARENGRUPPE,
		dc->DC_ABEZ_ZEILE2, dc->DC_UN_NR,

		dc->HERSTELLER_NR, dc->WARENGRUPPE, dc->NB_DC_PLAUSI, dc->NB_DC_ZWING, dc->NB_DC_NZWING,

		dc->DC_GENERIKUM , dc->DC_ORIGINALPRODUKT, dc->DC_ARZNEIMITTEL, dc->DC_ABGRENZ_VERORD, dc->DC_SG_ZUBEREITUNG,
        dc->DC_SG_SUBSTANZ, dc->DC_DROGENAGS_KAT1, dc->DC_DROGENAGS_KAT2, dc->DC_DROGENAGS_KAT3, dc->DC_BLUTKONSERVE,

		dc->DC_RADIOAKT_ARZNEI, dc->DC_FUETTER_ARZNEI, dc->DC_ARZNEI_GEWERBE, dc->DC_DENTALARZNEI, dc->DC_MEDIZIN_GAS,
		dc->DC_KONTAKTLINSENFL, dc->DC_ALK_UNVERST, dc->DC_ALK_VERGAELLT, dc->DC_GIFT, dc->DC_ZYTOSTATIKUM,
		dc->DC_MEDPROD_ABGABEV,	dc->DC_MEDPROD_KLASSE,	dc->DC_PFLANZENSCHUTZ,	dc->DC_ARTGRP_LTVERORD,
		// dc->DC_EAN_NR
		"             ",
		dc->DC_BIOSIEGEL, dc->DC_ANTIBIOTIKUM, dc->DC_FAELSCHSICHER
		);
    
    status = SqlExecuteImm( sql );
    if ( status != 0 ) 
	{
		strcpy( errmld, "zdcart (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
    return status;

}

/* ------------------------------------------------------------------- */
int ins_zdcoart		( const int  *Fd_Zdcoart, struct ZDCOART * dc, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Zdcoart < 0 ) 
		return -1;


	sprintf ( PK, "dc_artikel_nr=%7ld", dc->DC_ARTIKEL_NR );

	lStatus = FdInsertRecord( *Fd_Zdcoart, dc, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "zdcoart (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_zdcoart		( const int  *Fd_Zdcoart, struct ZDCOART * dc, char* errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Zdcoart < 0 ) 
		return -1;


	sprintf ( PK, "dc_artikel_nr=%7ld", dc->DC_ARTIKEL_NR );

	lStatus = FdUpdateRecord( *Fd_Zdcoart, dc, &m_BufOld, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "zdcoart (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_zdcoart		( const int *Fd_Zdcoart, const long art_nr, char *errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Zdcoart < 0 ) 
		return -1;


	sprintf ( PK, "dc_artikel_nr=%7ld", art_nr );
	
	lStatus = FdDeleteRecord( *Fd_Zdcoart, &m_BufOld, 
									 PK, errmld );

	if ( lStatus != 0 ) 
	{
		strcpy( errmld, "zdcoart (Delete einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_zdcart		( const long dcnr, const long satznr, char * errmld)
{
	int status;
	char sql[200];
   
    sprintf( sql, 
		"delete from zdcart where DCNR = %ld and SATZNR = %ld",
		dcnr, satznr);
    
    status = SqlExecuteImm( sql );
    if ( status != 0 ) 
	{
		strcpy( errmld, "zdcart (Delete einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die Util-Datei ein und schreibt				  *
 *                  die Saetze in die entspr. Tabelle	                  *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 08.07.2005                                            *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <libscsvoodoo/libscsvoodoo.h>
#include <hdatum/phodate.h>
#include <hdatum/phozeit.h>

/* --------------------------- */
#include <eklibs/ifalib/ifa_stat.h>
#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_dbas.h>

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/cdiscount.h>

#include "util_form.h"
#include "sql_zputil.h"
#include "g_util.h"

/* Grosso and LBP price plausibility check parameters */
#define PLAUSI_GEP_MAX_DELTA 50.0 /* maximum permitted % in-/decrease of grosso */
#define PLAUSI_GEP_MIN       10.0 /* minimum value for grosso plausibility */
#define PLAUSI_LBP_MAX_DELTA 50.0 /* maximum permitted % in-/decrease of LBP */
#define PLAUSI_LBP_MIN       10.0 /* minimum value for LBP plausibility */

typedef struct GetPricesInfo {
  double actGEP; /* current Grosso */
  double csvGEP; /* Grosso from Upload */
  short  gotGEP; /* Upload includes Grosso */
  double actLBP; /* current LBP */
  double csvLBP; /* LBP from Upload */
  short  gotLBP; /* Upload includes LBP */
} GetPricesInfo_t;

/* --- Prototype  ------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld );
void CloseBase( void );

/* ------------------- Globale Variablen ------------------------ */
static long anz_loaded = 0;
static long anz_notfound = 0;
static long line_nr;

char * spEnd	= NULL;
char * spBegin	= NULL;

int m_eFileArt = -1;

static struct	CDISCOUNT	BufDiscount;

/* ---------------------- */
int Trim (char *s)
{
	int i;
	
	for (i = (int)strlen(s)-1; i >= 0; i--)
	{
		if (s[i] != ' ')
		{
			break;
		}
	}

	s[i+1] = '\0';

	return i;
}

/* ------------------------------------------------------------------- */
static int GetNextLineValue ( char * retvalue, char * errmld )
{
	spBegin = spEnd + 1;
	spEnd = strpbrk(spBegin, FILE_DELIMITER);

	if ( spEnd == NULL ) 
		return 1;
	
	if ( strcmp(spBegin, spEnd) == 0 ) 
		strcpy ( retvalue, "" );
	else
        strncpy(retvalue, spBegin, strlen(spBegin) - strlen(spEnd));
	
	return 0;
}

/* ------------------------------------------------------------------- */
static int SaveHeader1 (  char *zeile,  char *errmld )
{
	int i = 1;
	
	if ( m_eUpdTable == UPD_ZARTIKEL )
		strcpy ( table_name, "zartikel" );
	else if ( m_eUpdTable == UPD_ZARTPREIS )
		strcpy ( table_name, "zartpreis" );
	else if ( m_eUpdTable == UPD_ZARTWG || m_eUpdTable == UPD_ZARTWG_5AG )
		strcpy ( table_name, "zartwg" );
	else if ( m_eUpdTable == UPD_CDISCOUNT )
		return 0; // no dynamic columns for cdiscount
	else if ( m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE || m_eUpdTable == UPD_CDISCOUNT_STOP)
		strcpy ( table_name, "cdiscount" );
	else if ( m_eUpdTable == UPD_ARTVE )
		strcpy ( table_name, "artve" );
	else if ( m_eUpdTable == UPD_CDISCGRPMEM )
		strcpy ( table_name, "cdiscgrpmem" );
	else if ( m_eUpdTable == UPD_CARTCOMPACK )
		strcpy ( table_name, "cartcompack" );
	else if ( m_eUpdTable == UPD_ZARTFRANCE )
		strcpy ( table_name, "zartfrance" );
	else if ( m_eUpdTable == UPD_ZARTSWITZERLAND )
		strcpy ( table_name, "zartswitzerland" );
	else if ( m_eUpdTable == UPD_ZARTSERBIA )
		strcpy ( table_name, "zartserbia" );
	else if ( m_eUpdTable == UPD_ZARTAUSTRIA )
		strcpy ( table_name, "zartaustria" );
	else if ( m_eUpdTable == UPD_CARTICLECODES )
		strcpy ( table_name, "carticlecodes" );
	else if ( m_eUpdTable == UPD_ZCHARGENRR )
		strcpy ( table_name, "zchargenrueckruf" );
	else if ( m_eUpdTable == UPD_CARTICLEEXT )
		strcpy ( table_name, "carticleext" );
	else if ( m_eUpdTable == UPD_CGIBATCHENTRY )
		strcpy ( table_name, "cgibatchentry" );
	else if ( m_eUpdTable == UPD_CIMEXBLOCK )
		strcpy ( table_name, "cimexblock" );
	else if ( m_eUpdTable == UPD_CIBT )
		strcpy ( table_name, "cibt" );
	else if ( m_eUpdTable == UPD_EAN )
		strcpy ( table_name, "ean" );
	else if (m_eUpdTable == UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG)
		strcpy(table_name, "csubsequentdeliverybrancharticleconfig");
	else if (m_eUpdTable == UPD_BLIESORT_DIREKT )
		strcpy(table_name, "bliesort");
	else if (m_eUpdTable == UPD_CBASELIST_ARTICLES )
		strcpy(table_name, "cbaselistarticles");
	else if (m_eUpdTable == UPD_CARTMEDACTOR)
		strcpy(table_name, "cartmedactor");
	else if (m_eUpdTable == UPD_CMEDICALACTOR)
		strcpy(table_name, "cmedicalactor");
	else
	{
		strcpy ( errmld, "Update-Tabelle wird nicht unterstützt!" );
		return -1;
	}

	spEnd = strpbrk(zeile, FILE_DELIMITER);
	spBegin = zeile;

	strncpy(upd_columns[0], spBegin, strlen(spBegin) - strlen(spEnd));

	while ( GetNextLineValue ( upd_columns[i], errmld ) == 0 )
		++i;

	anz_columns = i - 1;

	return 0;
}

/* ------------------------------------------------------------------- */
static int SaveHeader2 (  char *zeile,  char *errmld )
{
	char test [20];
	int i = 0;
	
	memset(test, '\0', 20);

	spEnd = strpbrk(zeile, FILE_DELIMITER);
	spBegin = zeile;
	
	strncpy( test, spBegin, strlen(spBegin) - strlen(spEnd));

	if ( m_eUpdTable == UPD_CDISCOUNT )
	{
		if ( strcmp ( test, "RESET_DATE_TO" ) == 0 )
			m_CDisc_ResetDateTo = 1;
		else
			m_CDisc_ResetDateTo = 0;

		return 0;
	}
	
	if ( strcmp ( test, "NEG_VALUES" ) != 0 )
	{
		return -1;
	}

	while ( GetNextLineValue ( neg_values[i], errmld ) == 0 )
		++i;

	return 0;
}

/* ------------------------------------------------------------------- */
static int SaveLine (  char *zeile,  char *errmld )
{
	if ( m_eUpdTable == UPD_CDISCOUNT )
	{
		char spToken[20];
		
		spEnd = zeile - 1; //strpbrk(zeile, FILE_DELIMITER);
		spBegin = zeile;
		memset(spToken, '\0', 19);
	
		// init tab buf for cdiscount and write data from file to buffer
		FdInitTabBuf( Fd_CDiscount, &BufDiscount );

		if ( strcmp(database, "zpps2bg") == 0	|| strcmp(database, "ibg21") == 0 )
		{
			GetNextLineValue ( spToken, errmld );
			BufDiscount.ARTICLENO = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTGRPNO = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.MANUFACTURERNO = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.ARTCATEGORYNO = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.BASEQTY = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.BASE_VALUE = atof(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DATEFROM = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DATETO = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTVALUEPCT = atof(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.GROSSPROFITPCT = atof(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTQTY = atoi(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( BufDiscount.PHARMACYGROUPID, errmld );

			GetNextLineValue ( spToken, errmld );
			BufDiscount.CUSTOMERNO = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTTYPE = atoi(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTSPEC = atoi(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( BufDiscount.ADDONDISCOUNTOK, errmld );

			GetNextLineValue ( spToken, errmld );
			BufDiscount.REFUNDVALUE = atof(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( BufDiscount.NO_MULTIPLE_QTY, errmld );

			GetNextLineValue ( spToken, errmld );
			BufDiscount.PROMOTION_NO = atoi(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( BufDiscount.TURNOVERCALCIMPACT, errmld );

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTARTICLE = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( BufDiscount.PHARMGRPEXCLUDED, errmld );

			GetNextLineValue ( BufDiscount.ADDONDISCOUNT, errmld );

			GetNextLineValue ( BufDiscount.INTERNALDISCOUNT, errmld );

			GetNextLineValue ( spToken, errmld );
			BufDiscount.SURCHARGEPCT = atof(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( BufDiscount.PHARMGRPEXCL_2, errmld );

			GetNextLineValue ( BufDiscount.PHARMGRPEXCL_3, errmld );

			BufDiscount.REFUNDTYPE = 1; //  --> immer 1, nicht im File !!!

			// not in file, but key !
			BufDiscount.BASE_MULT_STD_QTY = 0;
			BufDiscount.GRPDISCOUNTTYP = 0;
			BufDiscount.PAYMENTTARGETNO = 0;

			// string-felder mit "0" / "000" belegen!?
			strcpy ( BufDiscount.PAYMENTTERMTYPE,	"0");
			strcpy ( BufDiscount.MONTHLYDISCOUNT,	"0");
		}
		else // France is Std
		{
			GetNextLineValue ( spToken, errmld );
			BufDiscount.ARTICLENO = atol(spToken);
			memset(spToken, '\0', 19);
		
			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTGRPNO = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( BufDiscount.PHARMACYGROUPID, errmld );

			GetNextLineValue ( spToken, errmld );
			BufDiscount.CUSTOMERNO = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.BASEQTY = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DATEFROM = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DATETO = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.GRPDISCOUNTTYP = atoi(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTTYPE = atoi(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTSPEC = atoi(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTQTY = atoi(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTVALUEPCT = atof(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTQTYPCT = atof(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.SURCHARGEPCT = atof(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( BufDiscount.PHARMGRPEXCLUDED, errmld );

			GetNextLineValue ( spToken, errmld );
			BufDiscount.FIXEDPRICE = atof(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( spToken, errmld );
			BufDiscount.REFUNDPCT = atof(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( BufDiscount.INTERNALDISCOUNT, errmld );

			GetNextLineValue ( spToken, errmld );
			BufDiscount.DISCOUNTARTICLE = atol(spToken);
			memset(spToken, '\0', 19);

			GetNextLineValue ( BufDiscount.MONTHLYDISCOUNT, errmld );
			GetNextLineValue ( BufDiscount.PHARMGRPEXCL_2, errmld );
			GetNextLineValue ( BufDiscount.PHARMGRPEXCL_3, errmld );

			// not in file, but key !
			BufDiscount.BASE_VALUE = 0.0;
			BufDiscount.BASE_MULT_STD_QTY = 0;
			BufDiscount.MANUFACTURERNO = 0;
			BufDiscount.ARTCATEGORYNO = 0;
			BufDiscount.PAYMENTTARGETNO = 0;
			
			// string-felder mit "0" / "000" belegen!?
			strcpy ( BufDiscount.ADDONDISCOUNTOK,	"0");	
			strcpy ( BufDiscount.PAYMENTTERMTYPE,	"0");	
			strcpy ( BufDiscount.NO_MULTIPLE_QTY,	"0");	
			strcpy ( BufDiscount.TURNOVERCALCIMPACT,"0");	
			// PHARMACYGROUPID, PHARMGRPEXCLUDED, pharmgrpexcl_2, pharmgrpexcl_3, INTERNALDISCOUNT, monthlydiscount --> bereits in File enthalten		
		}

		return 0;
	}
	else
	{
		int i = 1;
		int ii = 0;

		for ( ii; ii < ANZ_FELDER_UPD; ++ii )
			memset(upd_values[ii], '\0', MAX_INPUT_LENGTH);

		spEnd = strpbrk(zeile, FILE_DELIMITER);
		spBegin = zeile;

		strncpy( upd_values[0], spBegin, strlen(spBegin) - strlen(spEnd));

		while ( GetNextLineValue ( upd_values[i], errmld ) == 0 )
			++i;

		return 0;
	}
}

/* ------------------------------------------------------------------- */
static int GetPrices(GetPricesInfo_t* info)
{
	int cnt = anz_columns;

	if (cnt <= 1)
		return -1;

	while (cnt > 1) // col_0 = PZN, col_1 = Datum
	{
		if ( strcmp(upd_columns[cnt], "GROSSO") == 0 ) {
			info->gotGEP = 1;
			info->actGEP = BufZPreisIns.GROSSO; /* Save current Grosso */
			info->csvGEP = BufZPreisIns.GROSSO = atof(upd_values[cnt]);
		} else if ( strcmp(upd_columns[cnt], "AEP") == 0 )
			BufZPreisIns.AEP = atof(upd_values[cnt]);
		else if ( strcmp(upd_columns[cnt], "AVP") == 0 )
			BufZPreisIns.AVP = atof(upd_values[cnt]);
		else if ( strcmp(upd_columns[cnt], "LBP") == 0 ) {
			info->gotLBP = 1;
			info->actLBP = BufZPreisIns.LIEFERBASISPREIS; /* Save current LBP */
			info->csvLBP = BufZPreisIns.LIEFERBASISPREIS = atof(upd_values[cnt]);
		} else if ( strcmp(upd_columns[cnt], "MAXAEP") == 0 )
			BufZPreisIns.MAXAEP = atof(upd_values[cnt]);
		else if ( strcmp(upd_columns[cnt], "MAXAVP") == 0 )
			BufZPreisIns.MAXAVP = atof(upd_values[cnt]);
		else if ( strcmp(upd_columns[cnt], "PHARMACY_BASEPRICE") == 0 )
			BufZPreisIns.PHARMACY_BASEPRICE = atof(upd_values[cnt]);
		else if ( strcmp(upd_columns[cnt], "PUBLICATIONNUMBER") == 0 )
			strcpy(BufZPreisIns.PUBLICATIONNUMBER, upd_values[cnt]);
		else if ( strcmp(upd_columns[cnt], "EAVP") == 0 )
			BufZPreisIns.EAVP = atof(upd_values[cnt]);
		else
			return -1;

		--cnt;
	}

	// zusätzlich für FR: Berechung zartikel / zartpreis.herst_prozent
	if ( strcmp(database, "ifr21") == 0 && BufZPreisIns.GROSSO > 0 && BufZPreisIns.AEP > 0 )
	{
		BufZPreisIns.HERST_PROZENT = 100 * (1.0 - (BufZPreisIns.GROSSO  / BufZPreisIns.AEP));
	}

	// zusätzlich für CH: Berechung grosso aus lbp + zartikel.herst_prozent
	if ( strcmp(database, "ich21") == 0 || strcmp(database, "ich21pre") == 0 )
	{
		char sql[500];
		double hproz;

		sprintf( sql, "select herst_prozent from zartikel where artikel_nr = %ld ", BufZPreisIns.ARTIKEL_NR );
	
		if ( 0 == SqlRead( sql, &hproz, NULL ) )
		{
			BufZPreisIns.HERST_PROZENT	= hproz; // SR-17082862: % in CH immer (nicht nur bei Berechnung Grosso aus LBP) von zartikel auf zartpreis übernehmen

			if (BufZPreisIns.LIEFERBASISPREIS > 0 && hproz > 0.0)
			{	
				// Berechnung Grosso aus LBP
				double newGrosso = BufZPreisIns.LIEFERBASISPREIS - ( BufZPreisIns.LIEFERBASISPREIS * hproz / 100 );	

				if ( newGrosso <= BufZPreisIns.AVP || BufZPreisIns.AVP == 0 )
				{
					BufZPreisIns.GROSSO			= newGrosso;
				}
			}
		}
	}

	return 0;
}

/*
** GEP plausibility (for CH only)
*/
static short chPlausiGEP(GetPricesInfo_t* info)
{	
	char   buf[60];
	short  answer = 1;

	if  (info->actGEP == 0.0f || info->csvGEP == 0.0f) {
		/* (re-)setting the price is always permitted */
    		snprintf(buf, sizeof(buf)-1, "[%s] GEP: %4.2f -> %4.2f ? %d\n",
			upd_values[0], info->actGEP, info->csvGEP, answer);
	} else if (info->actGEP >= PLAUSI_GEP_MIN || info->csvGEP >= PLAUSI_GEP_MIN) {
		/*
		** Upload the Grosso only, if:
		** - current and new Grosso relative difference does not exceed PLAUSI_GEP_MAX_DELTA, or
		** - both prices are rather small, less than PLAUSI_GEP_MIN each
		*/
		double maxGEP = info->actGEP > info->csvGEP ? info->actGEP : info->csvGEP;
		double delta  = info->actGEP > info->csvGEP ? info->actGEP - info->csvGEP : info->csvGEP - info->actGEP;
		double pdelta = 100.0*delta/maxGEP;
	        answer = (delta > 0.0f && pdelta > PLAUSI_GEP_MAX_DELTA) ? 0 : 1; 

		snprintf(buf, sizeof(buf)-1,
			"[%s] GEP: %4.2f -> %4.2f ? %d (%4.2f / %4.2f%%)\n",
			upd_values[0], info->actGEP, info->csvGEP, answer, delta, pdelta);
	} else {
		/* Let small update pass */
    		snprintf(buf, sizeof(buf)-1, "[%s] GEP: %4.2f -> %4.2f ? %d\n",
			upd_values[0], info->actGEP, info->csvGEP, answer);
	}	

	/* write protocol for plausi traceability */
	fputs(buf, fd_prot);
	return answer;
}

/*
** LBP plausibility (for CH only)
*/
static short chPlausiLBP(GetPricesInfo_t* info)
{	
	char   buf[60];
	short  answer = 1;

	if  (info->actLBP == 0.0f || info->csvLBP == 0.0f) {
		/* (re-)setting the price is always permitted */
    		snprintf(buf, sizeof(buf)-1, "[%s] LBP: %4.2f -> %4.2f ? %d\n",
			upd_values[0], info->actLBP, info->csvLBP, answer);
	} else if (info->actLBP >= PLAUSI_LBP_MIN || info->csvLBP >= PLAUSI_LBP_MIN) {
		/*
		** Upload the LBP only, if:
		** - current and new LBP relative difference does not exceed PLAUSI_LBP_MAX_DELTA, or
		** - both prices are rather small, less than PLAUSI_LBP_MIN each
		*/
		double maxLBP = info->actLBP > info->csvLBP ? info->actLBP : info->csvLBP;
		double delta  = info->actLBP > info->csvLBP ? info->actLBP - info->csvLBP : info->csvLBP - info->actLBP;
		double pdelta = 100.0*delta/maxLBP;
	        answer = (delta > 0.0f && pdelta > PLAUSI_LBP_MAX_DELTA) ? 0 : 1; 

    		snprintf(buf, sizeof(buf)-1,
			"[%s] LBP: %4.2f -> %4.2f ? %d (%4.2f / %4.2f%%)\n",
			upd_values[0], info->actLBP, info->csvLBP, answer, delta, pdelta);
	} else {
		/* Let small update pass */
    		snprintf(buf, sizeof(buf)-1, "[%s] LBP: %4.2f -> %4.2f ? %d\n",
			upd_values[0], info->actLBP, info->csvLBP, answer);
	}	

	/* write protocol for plausi traceability */
	fputs(buf, fd_prot);
	return answer;
}

/* ------------------------------------------------------------------- */
static int LoadLineToDb( char *errmld ) 
{
	int             sqlret;
	int             Fd_CDiscountSel;
	GetPricesInfo_t getPricesInfo = {0}; /* remember if GEP and/or LBP have been uploaded */
		
	if ( m_eUpdTable == UPD_ZARTIKEL )
	{
		sqlret = sel_zartikel(&Fd_ZArtikel, upd_values[0], errmld);
	}
	else if ( m_eUpdTable == UPD_ZARTPREIS )
	{
		// Test, ob Datum >= Tagesdatum
		int dat;
		dat = atoi(upd_values[1]);
		
		if ( dat < tages_datum )
			sqlret = 0; // dadurch, dass kein Update erfogt, wird später nur der Counter (notfound) hochgezählt!
		else
			sqlret = sel_zartpreis(&Fd_ZArtPreis, upd_values[0], upd_values[1], errmld);
	}
	else if ( m_eUpdTable == UPD_ZARTWG )
	{
		sqlret = sel_zartwg(&Fd_ZArtWg, upd_values[0], upd_columns[1], errmld);
	}
	else if ( m_eUpdTable == UPD_ARTVE )
	{
		sqlret = sel_artve(&Fd_ArtVe, upd_values[0], errmld);
	}
	else if ( m_eUpdTable == UPD_CIBT )
	{
		sqlret = sel_cibt(&Fd_Cibt, upd_values[0], errmld);
	}
	else if ( m_eUpdTable == UPD_CARTCOMPACK )
	{
		if (m_CArtComPack_CurrentPackNo != atoi(upd_values[1]) )
		{
			long count = 0;
			m_CArtComPack_CurrentPackNo = atoi(upd_values[1]);

			sqlret = sel_count_ccpvalperiod(&count, errmld );

			if (sqlret == 0 && count <= 0)
			{
				// ccpvalperiod neu anlegen, wenn noch nicht vorhanden
				ins_ccpvalperiod(&Fd_CcpValPeriod, &Fd_ZArtikel, errmld);
			}
			else
			{
				// Löschen aller Zuordnungen in CArtComPack zu dieser PackNo
				del_cartcompack(&Fd_CArtComPack, &Fd_ZArtikel, errmld);
			}
		}
		sqlret = 100; // always insert afterwards
	}	
	else if ( m_eUpdTable == UPD_CDISCGRPMEM )
	{
		if ( atoi(upd_values[0]) > 0 && atoi(upd_values[2]) > 0 ) // PZN + Hersteller gesetzt = nicht erlaubt
			sqlret = 0; // dadurch, dass kein Update erfolgt, wird später nur der Counter (notfound) hochgezählt!
		else
		{
			if (m_CDiscGrpMem_CurrentGroupNo != atoi(upd_values[1]) )
			{
				long count = 0;
				m_CDiscGrpMem_CurrentGroupNo = atoi(upd_values[1]);

				sqlret = sel_count_cdiscgrp(&count, errmld );

				if (sqlret == 0 && count <= 0)
				{
					// cdiscgrp neu anlegen, wenn noch nicht vorhanden
					ins_cdiscgrp(&Fd_CDiscGrp, errmld);
				}
				else
				{
					// Löschen aller Zuordnungen in CDiscGrpMem zu dieser GrpNo
					del_cdiscgrpmem(&Fd_CDiscGrpMem, errmld);
				}
			}
			sqlret = 100; // always insert afterwards
		}
	}
	else if ( m_eUpdTable == UPD_CDISCOUNT ) 
	{
		// read cdiscount for current key 
		sqlret = sel_cdiscount(&Fd_CDiscountSel, &BufDiscount, errmld );

		if ( sqlret == 0 )
			sqlret = SqlFetch( Fd_CDiscountSel, 1, &m_BufOldCDiscount, NULL );
	}
	else if ( m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE )
	{
		// Test, ob Datum >= Tagesdatum
		int dat_from, dat_to, qty;
		dat_from = atoi(upd_values[2]);
		dat_to	 = atoi(upd_values[3]);
		qty		 = atoi(upd_values[1]);
		
		if ( /*dat_from <= tages_datum ||*/ dat_to < dat_from || qty <= 0)
			sqlret = 0; // dadurch, dass kein Update erfolgt, wird später nur der Counter (notfound) hochgezählt!
		else
			sqlret = 100; // always insert afterwards
	}
	else if ( m_eUpdTable == UPD_CDISCOUNT_STOP )
	{
		// read number of cdiscount datasets to stop
		long count = 0;
		sqlret = sel_count_cdiscount_to_stop(&count, errmld );

		if (sqlret == 0 && count <= 0)
			sqlret = 100;
		else if (count > 0)
			anz_loaded += count;
	}
	else if ( m_eUpdTable == UPD_CARTICLECODES )
	{
		sqlret = sel_carticlecodes(&Fd_CArticleCodes, upd_values[0], upd_values[1], errmld);
	}
	else if ( m_eUpdTable == UPD_ZCHARGENRR )
	{
		sqlret = sel_zchargenrr(&Fd_ZChargenRR, upd_values[0], upd_values[1], errmld);
	}
	else if ( m_eUpdTable == UPD_CARTICLEEXT )
	{
		sqlret = sel_carticleext(&Fd_CArticleExt, upd_values[0], errmld);
	}
	else if ( m_eUpdTable == UPD_ZARTFRANCE )
	{
		sqlret = sel_zartfrance(&Fd_ZArtFrance, upd_values[0], errmld);
	}
	else if ( m_eUpdTable == UPD_ZARTSWITZERLAND )
	{
		sqlret = sel_zartswitzerland(&Fd_ZArtSwitzerland, upd_values[0], errmld);
	}
	else if ( m_eUpdTable == UPD_ZARTSERBIA )
	{
		sqlret = sel_zartserbia(&Fd_ZArtSerbia, upd_values[0], errmld);
	}
	else if ( m_eUpdTable == UPD_ZARTAUSTRIA )
	{
		sqlret = sel_zartaustria(&Fd_ZArtAustria, upd_values[0], errmld);
	}
	else if ( m_eUpdTable == UPD_CIMEXBLOCK )
	{
		sqlret = sel_cimexblock(&Fd_Cimexblock, upd_values[0], upd_values[1], upd_values[2], errmld);
	}
	else if ( m_eUpdTable == UPD_CGIBATCHENTRY )
	{
		// Test, ob Datum >= Tagesdatum
		int dat_from, dat_to, comp_code;
		dat_from = atoi(upd_values[2]);
		dat_to	 = atoi(upd_values[3]);
		comp_code= atoi(upd_values[1]);
		
		if ( dat_from <= tages_datum || dat_to < dat_from || comp_code <= 0)
			sqlret = 0; // dadurch, dass kein Update erfolgt, wird später nur der Counter (notfound) hochgezählt!
		else
			sqlret = 100; // always insert afterwards
	}
	else if (m_eUpdTable == UPD_EAN)
	{
		sqlret = sel_ean(&Fd_Ean, upd_values[0], errmld);
	}
	else if (m_eUpdTable == UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG)
	{
		sqlret = sel_csubsequentdeliverybrancharticleconfig(&Fd_Csubsequentdeliverybrancharticleconfig, upd_values[0], upd_values[1], errmld);
	}
	else if (m_eUpdTable == UPD_ZARTWG_5AG)
	{
		sqlret = sel_zartwg_5ag(&Fd_ZArtWg_5ag, upd_values[0], upd_values[1], errmld);
	}
	else if (m_eUpdTable == UPD_BLIESORT_DIREKT)
	{
		sqlret = sel_bliesort_direkt(&Fd_Bliesort, upd_values[0], upd_values[1], errmld);
	}
	else if ( m_eUpdTable == UPD_CBASELIST_ARTICLES )
	{
		sqlret = sel_cbaselistarticles(&Fd_CBaseListArticles, upd_values[1], upd_values[0], errmld);
	}
	else if (m_eUpdTable == UPD_CARTMEDACTOR)
	{
		sqlret = sel_cartmedactor(&Fd_Cartmedactor, upd_values[0], upd_values[2], errmld);
	}
	else if (m_eUpdTable == UPD_CMEDICALACTOR)
	{
		sqlret = sel_cmedicalactor(&Fd_Cmedicalactor, upd_values[0], errmld);
	}
	else
		return -1;

	
	if (sqlret == 0)
	{
		/*UPDATE*/
		if ( m_eUpdTable == UPD_ZARTIKEL )
		{
			sqlret = upd_zartikel(&Fd_ZArtikel, errmld);
			
			if ( sqlret == 0 )
				++anz_loaded;
		}	
		else if ( m_eUpdTable == UPD_ZARTPREIS )
		{
			// Preis-Satz mit genau diesem Datum bereits vorhanden --> überschreiben nicht erlaubt!
			// sqlret = upd_zartpreis(&Fd_ZArtPreis, errmld);
			sqlret = 0;
			++anz_notfound;
		}
		else if ( m_eUpdTable == UPD_ZARTWG )
		{
			Trim( upd_values[1] );
			if ( strcmp(upd_values[1],"") == 0 )
			{
				sqlret = del_zartwg(&Fd_ZArtWg, upd_values[0], upd_columns[1], errmld);
			}
			else
			{
				sqlret = upd_zartwg(&Fd_ZArtWg, errmld);
			}

			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_ARTVE )
		{
			sqlret = upd_artve(&Fd_ArtVe, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_CIBT )
		{
			sqlret = upd_cibt(&Fd_Cibt, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_CARTCOMPACK )
		{
			sqlret = 0;
			++anz_notfound;
		}
		else if ( m_eUpdTable == UPD_CDISCGRPMEM )
		{
			sqlret = 0;
			++anz_notfound;
		}
		else if ( m_eUpdTable == UPD_CARTICLECODES )
		{
			sqlret = upd_carticlecodes(&Fd_CArticleCodes, errmld);
			
			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_ZCHARGENRR )
		{
			sqlret = upd_zchargenrr(&Fd_ZChargenRR, errmld);
			
			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_CARTICLEEXT )
		{
			sqlret = upd_carticleext(&Fd_CArticleExt, errmld);
			
			if ( sqlret == 0 )
				++anz_loaded;
		}	
		else if ( m_eUpdTable == UPD_ZARTFRANCE )
		{
			sqlret = upd_zartfrance(&Fd_ZArtFrance, errmld);
			
			if ( sqlret == 0 )
				++anz_loaded;
		}	
		else if ( m_eUpdTable == UPD_ZARTSWITZERLAND )
		{
			sqlret = upd_zartswitzerland(&Fd_ZArtSwitzerland, errmld);
			
			if ( sqlret == 0 )
				++anz_loaded;
		}	
		else if ( m_eUpdTable == UPD_ZARTSERBIA )
		{
			sqlret = upd_zartserbia(&Fd_ZArtSerbia, errmld);
			
			if ( sqlret == 0 )
				++anz_loaded;
		}	
		else if ( m_eUpdTable == UPD_ZARTAUSTRIA )
		{
			sqlret = upd_zartaustria(&Fd_ZArtAustria, errmld);
			
			if ( sqlret == 0 )
				++anz_loaded;
		}	
		else if ( m_eUpdTable == UPD_CDISCOUNT )
		{
			m_CDisc_AlreadyExists = 0;

			// alle bestehenden gültigen Rabatte durchsuchen, ob es bereits einen identischen gibt
			while ( sqlret == 0 )
			{
				if (	m_BufOldCDiscount.DISCOUNTQTY		!= BufDiscount.DISCOUNTQTY			||
						m_BufOldCDiscount.DISCOUNTVALUEPCT	!= BufDiscount.DISCOUNTVALUEPCT		||
						m_BufOldCDiscount.DISCOUNTQTYPCT	!= BufDiscount.DISCOUNTQTYPCT		||
						m_BufOldCDiscount.SURCHARGEPCT		!= BufDiscount.SURCHARGEPCT			||
						strcmp(m_BufOldCDiscount.PHARMGRPEXCLUDED, BufDiscount.PHARMGRPEXCLUDED)!= 0	||
						m_BufOldCDiscount.FIXEDPRICE		!= BufDiscount.FIXEDPRICE			||
						m_BufOldCDiscount.REFUNDPCT			!= BufDiscount.REFUNDPCT			||
						strcmp(m_BufOldCDiscount.INTERNALDISCOUNT,	BufDiscount.INTERNALDISCOUNT)!= 0	||
						m_BufOldCDiscount.DISCOUNTARTICLE	!= BufDiscount.DISCOUNTARTICLE		||
						strcmp(m_BufOldCDiscount.MONTHLYDISCOUNT,	BufDiscount.MONTHLYDISCOUNT)!= 0	||
						strcmp(m_BufOldCDiscount.PHARMGRPEXCL_2,	BufDiscount.PHARMGRPEXCL_2)	!= 0	||
						strcmp(m_BufOldCDiscount.PHARMGRPEXCL_3,	BufDiscount.PHARMGRPEXCL_3) != 0	||
						strcmp(m_BufOldCDiscount.NO_MULTIPLE_QTY,	BufDiscount.NO_MULTIPLE_QTY)!= 0	||
						m_BufOldCDiscount.FIXEDDISCOUNTVALUE!= BufDiscount.FIXEDDISCOUNTVALUE	||
						m_BufOldCDiscount.GROSSPROFITPCT	!= BufDiscount.GROSSPROFITPCT	||
						strcmp(m_BufOldCDiscount.ADDONDISCOUNTOK, BufDiscount.ADDONDISCOUNTOK) != 0	||
						strcmp(m_BufOldCDiscount.PAYMENTTERMTYPE, BufDiscount.PAYMENTTERMTYPE) != 0	||
						m_BufOldCDiscount.TARGETQTY			!= BufDiscount.TARGETQTY	||
						m_BufOldCDiscount.EXCEEDANCEPCT		!= BufDiscount.EXCEEDANCEPCT	||
						m_BufOldCDiscount.REFUNDTYPE		!= BufDiscount.REFUNDTYPE	||
						m_BufOldCDiscount.ARTICLE_NO_PACK	!= BufDiscount.ARTICLE_NO_PACK	||
						m_BufOldCDiscount.REFUNDVALUE		!= BufDiscount.REFUNDVALUE	||
						m_BufOldCDiscount.PROMOTION_NO		!= BufDiscount.PROMOTION_NO	||
						strcmp(m_BufOldCDiscount.TURNOVERCALCIMPACT, BufDiscount.TURNOVERCALCIMPACT) != 0	||
						m_BufOldCDiscount.MAXQTY			!= BufDiscount.MAXQTY	||
						strcmp(m_BufOldCDiscount.ADDONDISCOUNT, BufDiscount.ADDONDISCOUNT) != 0	||
						m_BufOldCDiscount.DATETO			!= BufDiscount.DATETO					) // --> Felder, die nicht im Key sind
				{
						if ( m_CDisc_ResetDateTo == 1 )
						{
							m_BufOldCDiscountUnchanged = m_BufOldCDiscount;
							m_BufOldCDiscount.DATETO = AddDayToPhoDate(BufDiscount.DATEFROM, -1);

							if ( m_BufOldCDiscount.DATETO < m_BufOldCDiscount.DATEFROM )
								m_BufOldCDiscount.DATEFROM = m_BufOldCDiscount.DATETO;
							
							sqlret = upd_cdiscount(&Fd_CDiscount, errmld);// update alten Satz
						}
				}
				else
				{
					m_CDisc_AlreadyExists = 1;

					if ( m_CDisc_ResetDateTo != 1 )
						break;
				}
					
				if ( sqlret == 0 )
					sqlret = SqlFetch( Fd_CDiscountSel, 1, &m_BufOldCDiscount, NULL );
			}

			if ( sqlret == 100 )
				sqlret = 0;	
			
			if ( sqlret == 0 && m_CDisc_AlreadyExists != 1 )
			{
				sqlret = ins_cdiscount(&Fd_CDiscount, &BufDiscount, errmld);
			
				if ( sqlret == 0 )
					++anz_loaded;
				else if (sqlret == 239)
				{
					sqlret = 0;
					++anz_notfound;
				}
			}
			else
				++anz_notfound;
			
			SqlCloseCs( Fd_CDiscountSel );
		}
		else if ( m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE )
		{
			// keine Updates auf CDiscount
			sqlret = 0;
			++anz_notfound;
		}
		else if ( m_eUpdTable == UPD_CGIBATCHENTRY )
		{
			// keine Updates auf CGiBatchEntry
			sqlret = 0;
			++anz_notfound;
		}
		else if ( m_eUpdTable == UPD_CIMEXBLOCK )
		{
			if (upd_values[3][0] == '0') // = Sperre entfernen
			{
				sqlret = del_cimexblock(&Fd_Cimexblock, upd_values[0], upd_values[1], upd_values[2], errmld);
				
				if ( sqlret == 0 )
					++anz_loaded;
			}
			else
			{
				sqlret = 0;
				++anz_notfound;	
			}

		}
		else if ( m_eUpdTable == UPD_CDISCOUNT_STOP )
		{
			sqlret = stop_cdiscount(&Fd_CDiscount, errmld);
		}
		else if (m_eUpdTable == UPD_EAN)
		{
			// keine EAN-Nr. überschreiben
			sqlret = 0;

			if ( upd_values[1][0] == '1' && upd_values[1][1] == '\0' && strcmp(upd_columns[1], "EAN_NR") == 0 )
			{ // EAN-Nr. == "1" bedeutet: EAN löschen
				sqlret = del_ean(&Fd_Ean, upd_values[0], errmld);

				if (sqlret == 0) {
					++anz_loaded;
					m_EanWrToProt = EAN_DEL;
					WriteProtZeile(fd_prot);
				}
				else {
					++anz_notfound;
					m_EanWrToProt = EAN_NO_DEL;
					WriteProtZeile(fd_prot);
				}
			}
			else {
				++anz_notfound;
				m_EanWrToProt = EAN_NO_INS;
			}
		}
		else if (m_eUpdTable == UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG)
		{
			sqlret = 0;
			sqlret = upd_csubsequentdeliverybrancharticleconfig(&Fd_Csubsequentdeliverybrancharticleconfig, errmld);
			WriteProtZeile(fd_prot);
			if (sqlret == 0)
			{
				++anz_loaded;
			}
		}
		else if (m_eUpdTable == UPD_ZARTWG_5AG)
		{
			sqlret = upd_zartwg_5ag(&Fd_ZArtWg_5ag, errmld);

			if (sqlret == 0)
				++anz_loaded;
		}
		else if (m_eUpdTable == UPD_BLIESORT_DIREKT)
		{
			sqlret = upd_bliesort_direkt(&Fd_Bliesort, &Fd_ZANeuheit, errmld);

			if (sqlret == 0)
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_CBASELIST_ARTICLES )
		{
			sqlret = upd_cbaselistarticles(&Fd_CBaseListArticles, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if (m_eUpdTable == UPD_CARTMEDACTOR)
		{
			sqlret = upd_cartmedactor(&Fd_Cartmedactor, errmld);

			if (sqlret == 0)
				++anz_loaded;
		}
		else if (m_eUpdTable == UPD_CMEDICALACTOR)
		{
			sqlret = upd_cmedicalactor(&Fd_Cmedicalactor, errmld);

			if (sqlret == 0)
				++anz_loaded;
		}
	}
	else if (sqlret == 100) // record missing, then insert if needed
	{
		if ( m_eUpdTable == UPD_ZARTIKEL )
		{
			/*kein Insert!*/
			//sprintf ( errmld, "Datensatz %ld in den Stammdaten nicht vorhanden!\nDas Laden wurde abgebrochen!", line_nr ); 
			sqlret = 0;
			++anz_notfound;
		}	
		else if ( m_eUpdTable == UPD_ZARTPREIS )
		{
			sqlret = sel_zartpreis_current(&Fd_ZArtPreis, upd_values[0], upd_values[1], errmld);

			if ( sqlret == 0 )
			{
				int priceCheckOK = 1;

				BufZPreisIns = m_BufOldZPreis; // Preissatz, von dem kopiert wird!
				
				//publicationnumber nicht kopieren!
				strcpy(BufZPreisIns.PUBLICATIONNUMBER, "");
				
				if ( GetPrices(&getPricesInfo) != 0 )
					return -1;

				if ( strcmp(database, "iat21") == 0	)  //iat21pre no longer used
				{
					// AEP > GROSSO --> ok
					if (BufZPreisIns.AEP <= BufZPreisIns.GROSSO && BufZPreisIns.AEP > 0.0)
						priceCheckOK = 0;

					// AVP > AEP
					if (BufZPreisIns.AVP <= BufZPreisIns.AEP && BufZPreisIns.AVP > 0.0)
						priceCheckOK = 0;
				}
				else if ( strcmp(database, "ich21pre") == 0 )
				{
					// AEP darf jeglichen Wert annehmen = kein Check

					// ==> AVP > GROSSO
					if (BufZPreisIns.AVP <= BufZPreisIns.GROSSO && BufZPreisIns.AVP > 0.0)
						priceCheckOK = 0;	
				}
				else if ( strcmp(database, "ich21") == 0 )
				{
					short gepOK = 1, lbpOK = 1;

					if(getPricesInfo.gotGEP) {
					  gepOK = chPlausiGEP(&getPricesInfo);
					}

					if(getPricesInfo.gotLBP) {
					  lbpOK = chPlausiLBP(&getPricesInfo);
					}

					priceCheckOK = gepOK*lbpOK;

					/*
					** if the mass upload contains a grosso,
					** but no LBP, the LBP shall not be taken
					** from the previous entry, and the grosso
					** should be taken as-is
					*/
					if(getPricesInfo.gotGEP && !getPricesInfo.gotLBP) {
					  // Reset LBP and take GROSSO from upload genuinely
					  BufZPreisIns.GROSSO = getPricesInfo.csvGEP;
					  BufZPreisIns.LIEFERBASISPREIS = 0.0;
					}

					// AEP nicht genutzt (immer 0) 
					if (BufZPreisIns.AEP != 0.0)
						priceCheckOK = 0;
					
					// ==> AVP > GROSSO
					if (BufZPreisIns.AVP <= BufZPreisIns.GROSSO && BufZPreisIns.AVP > 0.0)
						priceCheckOK = 0;	
				}
				else // DE / HR / FR / SR-25009089: also BG
				{
					// AEP >= GROSSO	
					if (BufZPreisIns.AEP < BufZPreisIns.GROSSO && BufZPreisIns.AEP > 0.0)
						priceCheckOK = 0;

					// AVP > AEP
					if (BufZPreisIns.AVP <= BufZPreisIns.AEP && BufZPreisIns.AVP > 0.0)
						priceCheckOK = 0;
				}

				if ( priceCheckOK == 0 )
				{
					// plausi check für preise fehlerhaft -> kein Fehler, aber Satz wird auch nicht geschrieben!
					sqlret = 0;
					m_ZartpreisWrToProt = ZARTPREIS_NO_INS;
					WriteProtZeile(fd_prot);
					++anz_notfound;
				}
				else
				{
					sqlret = ins_zartpreis(&Fd_ZArtPreis, errmld);
			
					if ( sqlret == 0 )
					{
						m_ZartpreisWrToProt = ZARTPREIS_INS;
						WriteProtZeile(fd_prot);
						++anz_loaded;

						// Löschen von Preisen in der Zukunft in FR
						if ( strcmp(database, "ifr21") == 0 )
						{
							del_zartpreis_future(&Fd_ZArtPreis, errmld);
							
							/* nicht mehr nötig, wird über zpdailyclosing abgewickelt:
							// bei Änderung avp --> Eintrag in Tabelle cartrefundfrance
							if (m_BufOldZPreis.AVP != BufZPreisIns.AVP)
								ins_cartrefundfrance(errmld);
							*/
						}
					}
				}
			}
			else if ( sqlret == 100 )
			{
				// -> kein Preissatz, von dem kopiert werden könnte!
				sqlret = 0;
				++anz_notfound;
			}		
		}
		else if ( m_eUpdTable == UPD_ZARTWG )
		{
			Trim( upd_values[1] );
			if ( strcmp(upd_values[1],"") != 0)
			{
				sqlret = ins_zartwg(&Fd_ZArtWg, errmld);

				if ( sqlret == 0 )
					++anz_loaded;
			}
			else
			{
				sqlret = 0;
				++anz_notfound;
			}
		}
		else if ( m_eUpdTable == UPD_ARTVE )
		{
			sqlret = ins_artve(&Fd_ArtVe, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_CIBT )
		{
			sqlret = ins_cibt(&Fd_Cibt, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_CARTCOMPACK )
		{
			sqlret = ins_cartcompack(&Fd_CArtComPack, &Fd_ZArtikel, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
			else if (sqlret == -239)
			{
				sqlret = 0;
				++anz_notfound; // cartcompack already exists
			}
		}
		else if ( m_eUpdTable == UPD_CDISCGRPMEM )
		{
			sqlret = ins_cdiscgrpmem(&Fd_CDiscGrpMem, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
			else if (sqlret == -239)
			{
				sqlret = 0;
				++anz_notfound; // discgrpmem already exists
			}
		}
		else if ( m_eUpdTable == UPD_CDISCOUNT )
		{	
			// no previous discount with identical values (except than datefrom + dateto found) 
			// --> just insert new row
			sqlret = ins_cdiscount(&Fd_CDiscount, &BufDiscount, errmld);
			
			if ( sqlret == 0 )
				++anz_loaded;
			
			SqlCloseCs( Fd_CDiscountSel );
		}
		else if ( m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE )
		{	
			// --> just insert new row
			sqlret = ins_cdiscount_flexible(&Fd_CDiscount, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
			else if (sqlret == -239)
			{
				sqlret = 0;
				++anz_notfound; // discount already exists
			}
		}
		else if ( m_eUpdTable == UPD_CDISCOUNT_STOP )
		{
			/*kein Insert!*/
			sqlret = 0;
			++anz_notfound;
		}
		else if ( m_eUpdTable == UPD_ZARTFRANCE )
		{
			/*kein Insert!*/
			sqlret = 0;
			++anz_notfound;
		}	
		else if ( m_eUpdTable == UPD_ZARTSWITZERLAND )
		{
			/*kein Insert!*/
			sqlret = 0;
			++anz_notfound;
		}	
		else if ( m_eUpdTable == UPD_ZARTSERBIA )
		{
			/*kein Insert!*/
			sqlret = 0;
			++anz_notfound;
		}	
		else if ( m_eUpdTable == UPD_ZARTAUSTRIA )
		{
			/*kein Insert!*/
			sqlret = 0;
			++anz_notfound;
		}	
		else if ( m_eUpdTable == UPD_CARTICLECODES )
		{
			sqlret = ins_carticlecodes(&Fd_CArticleCodes, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_ZCHARGENRR )
		{
			sqlret = ins_zchargenrr(&Fd_ZChargenRR, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_CARTICLEEXT )
		{
			sqlret = ins_carticleext(&Fd_CArticleExt, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_CIMEXBLOCK )
		{
			if (upd_values[3][0] == '1') // = Sperren
			{
				sqlret = ins_cimexblock(&Fd_Cimexblock, errmld);
				
				if ( sqlret == 0 )
					++anz_loaded;
			}
			else
			{
				sqlret = 0;
				++anz_notfound;	
			}
		}
		else if ( m_eUpdTable == UPD_CGIBATCHENTRY )
		{	
			// --> just insert new row
			sqlret = ins_cgibatchentry(&Fd_CGiBatchEntry, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
			else if (sqlret == -239)
			{
				sqlret = 0;
				++anz_notfound; // gibatchentry already exists
			}
		}
		else if (m_eUpdTable == UPD_EAN)
		{
			if (upd_values[1][0] == '1' && upd_values[1][1] == '\0' && strcmp(upd_columns[1], "EAN_NR") == 0)
			{ // EAN-Nr. == "1" bedeutet: EAN löschen
				m_EanWrToProt = EAN_NO_INS;
				WriteProtZeile(fd_prot);
				++anz_notfound;
				return -1; // error: EAN-Nr. = '1' should not happen here
			}

			sqlret = ins_ean(&Fd_Ean, errmld);

			if (sqlret == 0) {
				++anz_loaded;
				m_EanWrToProt = EAN_INS;
				WriteProtZeile(fd_prot);
			}
			else {
				m_EanWrToProt = EAN_NO_INS;
				WriteProtZeile(fd_prot);
				++anz_notfound;
			}
		}
		else if (m_eUpdTable == UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG)
		{
			sqlret = sel_zartikel(&Fd_ZArtikel, upd_values[0], errmld);
			if (sqlret == 0) // zartikel available
			{
				sqlret = ins_csubsequentdeliverybrancharticleconfig(&Fd_Csubsequentdeliverybrancharticleconfig, errmld);
				if (sqlret == 0)
				{
					++anz_loaded;
					WriteProtZeile(fd_prot);
				}
			}
		}
		else if (m_eUpdTable == UPD_ZARTWG_5AG)
		{
			sqlret = ins_zartwg_5ag(&Fd_ZArtWg_5ag, errmld);

			if (sqlret == 0)
				++anz_loaded;
		}
		else if (m_eUpdTable == UPD_BLIESORT_DIREKT)
		{
			sqlret = ins_bliesort_direkt(&Fd_Bliesort, &Fd_ZANeuheit, errmld);

			if (sqlret == 0)
				++anz_loaded;
		}
		else if ( m_eUpdTable == UPD_CBASELIST_ARTICLES )
		{
			sqlret = ins_cbaselistarticles(&Fd_CBaseListArticles, errmld);

			if ( sqlret == 0 )
				++anz_loaded;
		}
		else if (m_eUpdTable == UPD_CARTMEDACTOR)
		{
			sqlret = ins_cartmedactor(&Fd_Cartmedactor, errmld);

			if (sqlret == 0)
				++anz_loaded;
		}
		else if (m_eUpdTable == UPD_CMEDICALACTOR)
		{
			sqlret = ins_cmedicalactor(&Fd_Cmedicalactor, errmld);

			if (sqlret == 0)
				++anz_loaded;
		}
		else
			return -1;
	}

	return sqlret;
}

/* ------------------------------------------------------------------- */
static int UtilLieferung( char *errmld )
{
	int status;
	char zeile[MAX_BUF + 1];

	line_nr = 0;
	
	/* 1. Headerzeile */
	status = GetUtilZeile( fd_file, zeile );

	if (status == 0)
	{
		if ( SaveHeader1 ( zeile, errmld ) == 0 )
		{
			/* 2.Headerzeile */
			status = GetUtilZeile( fd_file, zeile );

			if (status == 0)
			{
				if ( SaveHeader2 ( zeile, errmld ) != 0 )
				{
					status = 3;
				}
			}
			else
				status = 3;
		}
		else 
			status = 3;
	}
	else
		status = 3;

	m_CDiscGrpMem_CurrentGroupNo = 0;

	while ( status == 0 )/*SCHLEIFE zum Lesen aller Datenzeilen aus Util-File*/
	{
		status = GetUtilZeile( fd_file, zeile );
		if (status == 0)
		{
			++line_nr;	

			if ( SaveLine( zeile, errmld ) == 0 )
			{
				if ( LoadLineToDb (errmld) != 0 )
					status = 3;
			}
			else 
				status = 3;
		}
	}

	if (status != 2) 
		strcat(errmld, "\nError on reading util-file; file not read to the end!");
	else
	{
		status = 0;/*EOF*/
		
		/* update neg_values ( vgl. nicht in temp table "zputil_temp") */
		if ( m_eUpdTable == UPD_ZARTIKEL )
		{
			status = upd_negval_zartikel(&Fd_ZArtikel, errmld);
		}
		else if ( m_eUpdTable == UPD_ZARTPREIS )
		{
			status = 0; // keine negierten Werte für zartpreis!
		}
		else if ( m_eUpdTable == UPD_ZARTWG )
		{
			status = 0; // keine negierten Werte für zartwg!
		}
		else if ( m_eUpdTable == UPD_ARTVE )
		{
			status = 0; // keine negierten Werte für artve!
		}
		else if ( m_eUpdTable == UPD_CDISCGRPMEM )
		{
			status = 0; // keine negierten Werte für cdiscgrpmem!
		}
		else if ( m_eUpdTable == UPD_CARTCOMPACK )
		{
			status = 0; // keine negierten Werte für cartcompack!
		}
		else if ( m_eUpdTable == UPD_CDISCOUNT || m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE || m_eUpdTable == UPD_CDISCOUNT_STOP )
		{
			status = 0; // keine negierten Werte für cdiscount!
		}
		else if ( m_eUpdTable == UPD_CARTICLECODES )
		{
			status = 0; // keine negierten Werte für carticlecodes!
		}
		else if ( m_eUpdTable == UPD_ZCHARGENRR )
		{
			status = 0; // keine negierten Werte für zchargenrueckruf!
		}
		else if ( m_eUpdTable == UPD_CARTICLEEXT )
		{
			status = 0; // keine negierten Werte für carticleext - hier sollen nur Datensätze drin stehen, die mind. 1 Nicht- Default- Feld haben!
		}
		else if ( m_eUpdTable == UPD_CGIBATCHENTRY )
		{
			status = 0; // keine negierten Werte für cgibatchentry!
		}
		else if ( m_eUpdTable == UPD_CIMEXBLOCK )
		{
			status = 0; // keine negierten Werte für cimexblock!
		}
		else if ( m_eUpdTable == UPD_ZARTFRANCE )
		{
			status = 0; // keine negierten Werte für zartfrance, da keine ja / nein- KZ!
			//status = upd_negval_zartfrance(&Fd_ZArtFrance, errmld);
		}
		else if ( m_eUpdTable == UPD_ZARTSWITZERLAND )
		{
			status = 0; // keine negierten Werte für zartswitzerland, da keine ja / nein- KZ!
			//status = upd_negval_zartswitzerland(&Fd_ZArtSwitzerland, errmld);
		}
		else if ( m_eUpdTable == UPD_ZARTSERBIA )
		{
			status = upd_negval_zartserbia(&Fd_ZArtSerbia, errmld);
		}
		else if ( m_eUpdTable == UPD_ZARTAUSTRIA )
		{
			status = upd_negval_zartaustria(&Fd_ZArtAustria, errmld);
		}
		else if (m_eUpdTable == UPD_CIBT)
		{
			status = 0; // keine negierten Werte für cibt!
		}
		else if (m_eUpdTable == UPD_EAN)
		{
			status = 0; // keine negierten Werte für ean!
		}
		else if (m_eUpdTable == UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG)
		{
			status = 0; // keine negierten Werte für csubsequentdeliverybrancharticleconfig !
		}
		else if (m_eUpdTable == UPD_ZARTWG_5AG)
		{
			status = 0; // keine negierten Werte für zartwg!
		}
		else if (m_eUpdTable == UPD_BLIESORT_DIREKT)
		{
			status = 0; // keine negierten Werte für bliesort!
		}
		else if (m_eUpdTable == UPD_CBASELIST_ARTICLES)
		{
			status = 0; // keine negierten Werte fuer cbaselistarticles !
		}
		else if (m_eUpdTable == UPD_CARTMEDACTOR)
		{
			status = 0; // keine negierten Werte fuer cartmedactor !
		}
		else if (m_eUpdTable == UPD_CMEDICALACTOR)
		{
			status = 0; // keine negierten Werte fuer cmedicalactor !
		}
		else
			status = -1;
	}

   CloseUtilDatei( fd_file );
   fd_file = NULL;

   CloseProtDatei ( fd_prot );
   fd_prot = NULL; 

   return status;
}

/* ------------------------------------------------------------------- */
static long GenUpdate( char *db, char* ili_file, char* prot_file, char *errmld, int iTestRun )
{
   int status;
   int bufferOpened = -1;

   	
   tages_datum = GetPhoDate();
   
   fd_file = NULL;
   fd_prot = NULL;
      
   /*öffnen des Util-Files */
   status = OpenUtilDatei( &fd_file, ili_file, errmld );
   if ( status != 0 )
   {
       sprintf(errmld, "util-file not found under path %s\n", ili_file);
	   return status;
   }

   status = OpenProtDatei( &fd_prot, prot_file, errmld );
   if ( status != 0 )
   {
       sprintf(errmld, "not able to open protocol-file\n");
	   return status;
   } 

   
    if ( OpenBase( db, errmld ) == 0 )
    {
        database = db;
		
		OpenPflege( (char*)user, errmld );
		
		Fd_ZArtikel = -1;
		Fd_ZArtPreis= -1;
		Fd_ZArtWg	= -1;
		Fd_CDiscount= -1;
		Fd_CArticleCodes = -1;
		Fd_CArticleExt = -1;
		Fd_ZArtFrance= -1;
		Fd_ZArtSwitzerland= -1;
		Fd_ZArtSerbia= -1;
		Fd_ZArtAustria = -1;
		Fd_CGiBatchEntry= -1;
		Fd_ZChargenRR = -1;
		Fd_Cimexblock = -1;
		Fd_ArtnrBl = -1;
		Fd_Bliesort = -1;
		Fd_ZANeuheit = -1;
		Fd_ArtVe = -1;
		Fd_CDiscGrpMem = -1;
		Fd_CDiscGrp = -1;
		Fd_CArtComPack = -1;
		Fd_CcpValPeriod = -1;
		Fd_Cibt = -1;
		Fd_Ean = -1;
		Fd_Csubsequentdeliverybrancharticleconfig = -1;
		Fd_ZArtWg_5ag = -1;
		Fd_CBaseListArticles = -1;
		Fd_Cmedicalactor = -1;
		Fd_Cartmedactor = -1;

		if ( m_eUpdTable == UPD_ZARTIKEL )
		{
			bufferOpened = 
				OpenBufferDesc( &Fd_ZArtikel, "zartikel", NULL, NULL, V_PROTO_VERTEIL, errmld ) + 
				OpenBufferDesc( &Fd_ArtnrBl,  "artnrbl", NULL, NULL, V_PROTO_VERTEIL, errmld ) +
				OpenBufferDesc( &Fd_Bliesort, "bliesort", NULL, NULL, V_PROTO_VERTEIL, errmld ) + 
				InitPflegeTab( errmld );			
		}
		else if ( m_eUpdTable == UPD_ZARTPREIS )
		{
			bufferOpened = OpenBufferDesc( &Fd_ZArtPreis, "zartpreis", NULL, NULL, V_PROTO_VERTEIL, errmld );
		}
		else if ( m_eUpdTable == UPD_ZARTWG )
		{
			bufferOpened = OpenBufferDesc( &Fd_ZArtWg, "zartwg", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_ARTVE )
		{
			bufferOpened = OpenBufferDesc( &Fd_ArtVe, "artve", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_CDISCGRPMEM )
		{
			bufferOpened = OpenBufferDesc( &Fd_CDiscGrpMem, "cdiscgrpmem", NULL, NULL, V_PROTO_VERTEIL, errmld ) +
							OpenBufferDesc( &Fd_CDiscGrp, "cdiscgrp", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_CARTCOMPACK )
		{
			bufferOpened = OpenBufferDesc( &Fd_CArtComPack, "cartcompack", NULL, NULL, V_PROTO_VERTEIL, errmld ) +
							OpenBufferDesc( &Fd_CcpValPeriod, "ccpvalidityperiod", NULL, NULL, V_PROTO_VERTEIL, errmld ) + 
							OpenBufferDesc( &Fd_ZArtikel, "zartikel", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_CDISCOUNT || m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE || m_eUpdTable == UPD_CDISCOUNT_STOP )
		{
			bufferOpened = OpenBufferDesc( &Fd_CDiscount, "cdiscount", NULL, NULL, V_PROTO_VERTEIL, errmld );
			// for debugging on windows
			//bufferOpened = OpenBufferDesc( &Fd_CDiscount, "cdiscount", NULL, NULL, V_OHNE, errmld );	
		}
		else if ( m_eUpdTable == UPD_ZARTFRANCE )
		{
			bufferOpened = OpenBufferDesc( &Fd_ZArtFrance, "zartfrance", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_ZARTSWITZERLAND )
		{
			bufferOpened = OpenBufferDesc( &Fd_ZArtSwitzerland, "zartswitzerland", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_ZARTSERBIA )
		{
			bufferOpened = OpenBufferDesc( &Fd_ZArtSerbia, "zartserbia", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_ZARTAUSTRIA )
		{
			bufferOpened = OpenBufferDesc( &Fd_ZArtAustria, "zartaustria", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_CARTICLECODES )
		{
			bufferOpened = OpenBufferDesc( &Fd_CArticleCodes, "carticlecodes", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_ZCHARGENRR )
		{
			bufferOpened = OpenBufferDesc( &Fd_ZChargenRR, "zchargenrueckruf", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_CARTICLEEXT )
		{
			bufferOpened = OpenBufferDesc( &Fd_CArticleExt, "carticleext", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_CGIBATCHENTRY )
		{
			bufferOpened = OpenBufferDesc( &Fd_CGiBatchEntry, "cgibatchentry", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if ( m_eUpdTable == UPD_CIMEXBLOCK )
		{
			bufferOpened = OpenBufferDesc( &Fd_Cimexblock, "cimexblock", NULL, NULL, V_PROTO_VERTEIL, errmld );	
		}
		else if (m_eUpdTable == UPD_CIBT)
		{
			bufferOpened = OpenBufferDesc(&Fd_Cibt, "cibt", NULL, NULL, V_PROTO_VERTEIL, errmld);
		}
		else if (m_eUpdTable == UPD_EAN)
		{
			bufferOpened = OpenBufferDesc(&Fd_Ean, "ean", NULL, NULL, V_PROTO_VERTEIL, errmld);
		}
		else if (m_eUpdTable == UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG)
		{
			bufferOpened = OpenBufferDesc(&Fd_Csubsequentdeliverybrancharticleconfig, "csubsequentdeliverybrancharticleconfig", NULL, NULL, V_PROTO_VERTEIL, errmld) +
				OpenBufferDesc(&Fd_ZArtikel, "zartikel", NULL, NULL, V_PROTO_VERTEIL, errmld);
		}
		else if (m_eUpdTable == UPD_ZARTWG_5AG)
		{
			bufferOpened = OpenBufferDesc(&Fd_ZArtWg_5ag, "zartwg", NULL, NULL, V_PROTO_VERTEIL, errmld);
		}
		else if (m_eUpdTable == UPD_BLIESORT_DIREKT)
		{
			bufferOpened = OpenBufferDesc(&Fd_Bliesort, "bliesort", NULL, NULL, V_PROTO_VERTEIL, errmld) +
						   OpenBufferDesc(&Fd_ZANeuheit, "zaneuheit", NULL, NULL, V_PROTO_VERTEIL, errmld);
		}
		else if (m_eUpdTable == UPD_CBASELIST_ARTICLES)
		{
			bufferOpened = OpenBufferDesc(&Fd_CBaseListArticles, "cbaselistarticles", NULL, NULL, V_PROTO_VERTEIL, errmld);
		}
		else if (m_eUpdTable == UPD_CARTMEDACTOR ||
				m_eUpdTable == UPD_CMEDICALACTOR)
		{
			bufferOpened = OpenBufferDesc(&Fd_Cartmedactor, "cartmedactor", NULL, NULL, V_PROTO_VERTEIL, errmld) +
						   OpenBufferDesc(&Fd_Cmedicalactor, "cmedicalactor", NULL, NULL, V_PROTO_VERTEIL, errmld);
		}
		else
		{
			strcpy ( errmld, "Update-Tabelle wird nicht unterstuetzt!" );
			return -1;
		}
	
		if ( bufferOpened == 0 )
		{
		  /*
		  ** - currently only tested for UPD_CDISCOUNT_STOP, because here WHERE- criteria are given (and not each line is send to DB 1:1)
		  ** - baselist article upload should also generally be undone if any validation fails
		  */
		  if (iTestRun == 1 || m_eUpdTable == UPD_CBASELIST_ARTICLES)
		  {
				SqlBeginWork();
		  }

			status = UtilLieferung ( errmld );
		}
		else
			status = 1;

		
		if ( m_eUpdTable == UPD_ZARTIKEL )
		{
			CloseOneBufferDesc(Fd_ZArtikel);
			CloseOneBufferDesc(Fd_ArtnrBl);
			CloseOneBufferDesc(Fd_Bliesort);
			ClosePflegeTab( );
		}
		else if ( m_eUpdTable == UPD_ZARTPREIS )
		{
			CloseOneBufferDesc(Fd_ZArtPreis);
		}
		else if ( m_eUpdTable == UPD_ZARTWG )
		{
			CloseOneBufferDesc(Fd_ZArtWg);
		}
		else if ( m_eUpdTable == UPD_ARTVE )
		{
			CloseOneBufferDesc(Fd_ArtVe);
		}
		else if ( m_eUpdTable == UPD_CDISCGRPMEM )
		{
			CloseOneBufferDesc(Fd_CDiscGrpMem);
			CloseOneBufferDesc(Fd_CDiscGrp);
		}
		else if ( m_eUpdTable == UPD_CARTCOMPACK )
		{
			CloseOneBufferDesc(Fd_CArtComPack);
			CloseOneBufferDesc(Fd_CcpValPeriod);
			CloseOneBufferDesc(Fd_ZArtikel);
		}
		else if ( m_eUpdTable == UPD_CDISCOUNT || m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE || m_eUpdTable == UPD_CDISCOUNT_STOP )
		{
			CloseOneBufferDesc(Fd_CDiscount);
		}
		else if ( m_eUpdTable == UPD_ZARTFRANCE )
		{
			CloseOneBufferDesc(Fd_ZArtFrance);
		}
		else if ( m_eUpdTable == UPD_ZARTSWITZERLAND )
		{
			CloseOneBufferDesc(Fd_ZArtSwitzerland);
		}
		else if ( m_eUpdTable == UPD_ZARTSERBIA )
		{
			CloseOneBufferDesc(Fd_ZArtSerbia);
		}
		else if ( m_eUpdTable == UPD_ZARTAUSTRIA )
		{
			CloseOneBufferDesc(Fd_ZArtAustria);
		}
		else if ( m_eUpdTable == UPD_CARTICLECODES )
		{
			CloseOneBufferDesc(Fd_CArticleCodes);
		}
		else if ( m_eUpdTable == UPD_ZCHARGENRR )
		{
			CloseOneBufferDesc(Fd_ZChargenRR);
		}
		else if ( m_eUpdTable == UPD_CARTICLEEXT )
		{
			CloseOneBufferDesc(Fd_CArticleExt);
		}
		else if ( m_eUpdTable == UPD_CGIBATCHENTRY )
		{
			CloseOneBufferDesc(Fd_CGiBatchEntry);
		}
		else if ( m_eUpdTable == UPD_CIMEXBLOCK )
		{
			CloseOneBufferDesc(Fd_Cimexblock);
		}
		else if (m_eUpdTable == UPD_CIBT)
		{
			CloseOneBufferDesc(Fd_Cibt);
		}
		else if (m_eUpdTable == UPD_EAN)
		{
			CloseOneBufferDesc(Fd_Ean);
		}
		else if (m_eUpdTable == UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG)
		{
			CloseOneBufferDesc(Fd_Csubsequentdeliverybrancharticleconfig);
		}
		else if (m_eUpdTable == UPD_ZARTWG_5AG)
		{
			CloseOneBufferDesc(Fd_ZArtWg_5ag);
		}
		if (m_eUpdTable == UPD_BLIESORT_DIREKT)
		{
			CloseOneBufferDesc(Fd_Bliesort);
			CloseOneBufferDesc(Fd_ZANeuheit);
		}
		else if (m_eUpdTable == UPD_CBASELIST_ARTICLES)
		{
			CloseOneBufferDesc(Fd_CBaseListArticles);
		}
		else if (m_eUpdTable == UPD_CARTMEDACTOR ||
				m_eUpdTable == UPD_CMEDICALACTOR)
		{
			CloseOneBufferDesc(Fd_Cartmedactor);
			CloseOneBufferDesc(Fd_Cmedicalactor);
		}
		CloseBase( );
    }
   return status;
}

/* ------------------------------------------------------------------- */
#define FILE_LEN 30
long GenUtil( char *db, char *ili_direc, char *errmld, int iMode, int iTestRun )
{
	char *ili_file;
	char *prot_file;
	char protfileext[25];
	
    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
	prot_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    
	if ( ili_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler GenUtil" );
       return 1;
    }

	strcpy( ili_file, ili_direc );
	
	strcpy( prot_file, ili_direc ); 
	sprintf(protfileext, "_%ld_%ld", GetPhoDate(), GetPhoTime());
	strcat ( prot_file, protfileext );	
	strcat ( prot_file, ".prot" );	

	m_eUpdTable = iMode;
    
	if ( GenUpdate( db, ili_file, prot_file, errmld, iTestRun ) != 0 )
    {
       free( ili_file );
	   free( prot_file );
       return 1;
    }

	free( ili_file );
	free( prot_file );
 	
	if (iTestRun == 1)
	{
	  if (m_eUpdTable == UPD_CBASELIST_ARTICLES)
	  {
	    baselist_article_import_summary(errmld);
	  }
	  else
	  {
		sprintf( errmld,  "%ld Datensaetze waeren betroffen.\n%ld Datensaetze wuerden nicht uebernommen.\n",
					 anz_loaded, anz_notfound);
	  }
		SqlRollbackWork();

		return 0;
	}

	if (m_eUpdTable == UPD_EAN)
	{
		sprintf( errmld,  "%ld Datensaetze erfolgreich verarbeitet.\n%ld Datensaetze nicht verarbeitet. (Ean-Nr. schon vorhanden/nicht gefunden --> siehe Protokolldatei)\n",
					 anz_loaded, anz_notfound);
	}
	else if (m_eUpdTable == UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG)
	{
		sprintf(errmld, "%ld Datensaetze erfolgreich verarbeitet.\n%ld Datensaetze nicht verarbeitet. (ArticleNo/BranchNo. schon vorhanden/nicht gefunden --> siehe Protokolldatei)\n",
			anz_loaded, anz_notfound);
	}
	else if (m_eUpdTable == UPD_CBASELIST_ARTICLES)
	{
	  baselist_article_import_summary(errmld);
	}
	else
	{
		sprintf( errmld,  "%ld Datensaetze erfolgreich geladen.\n%ld Datensaetze nicht uebernommen.\n  (nicht in den Stammdaten gefunden, Preise / Datum ungueltig, identischer Rabatt vorhanden).",
					 anz_loaded, anz_notfound);
	}

    return 0;
}

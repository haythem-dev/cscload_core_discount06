/* ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die LogIndex-Artikeldatei ein und integriert    *
 *                  die Saetze in den lokalen UPDATE-POOL                 *
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

/* --------------------------- */
#include <eklibs/ifalib/ifa_stat.h>
#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_dbas.h>

#include <voodoo_table_header/cliart.h>
#include <voodoo_table_header/clioart.h>
#include <voodoo_table_header/clicompany.h>
#include <voodoo_table_header/clihsatz.h>
#include <voodoo_table_header/cliohsatz.h>
#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/catccode.h>
#include <voodoo_table_header/cassortmentcode.h>
#include <voodoo_table_header/cliproduct.h>
#include <voodoo_table_header/cliproductgrp.h>

#include "li_form.h"
#include "g_lioart.h" 
#include "sql_zliart.h"
#include "znb_gen_li.h"
#include "check_plausi.h"
#include "zpreitst.h"
#include "g_liartik.h"
#include "pnamcode.h"
#include "subartdan.h"
#include "subartcomp.h"

/* --- Prototype  ------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld );
void CloseBase( void );

/* ------------------- Globale Variablen ------------------------ */
long satznr;
long linenr_processed;
long linenr_overread;
long linenr_invalid;
long art_aenderung;
long art_neuanlage;

long anz_upd;
long anz_ins;

static struct CLIART li;
static struct CLIOART lio;
static struct CLICOMPANY licomp;
static struct CLIHSATZ lihsaetze[100];
static struct CLIPRODUCT liprod;
static struct CLIPRODUCTGRP liprodgrp;
int hazardStatementsCounter;
short notExistingHazardnotes;
static struct CATCCODE atccode;
static struct CASSORTMENTCODE assortcode;

static char pzn_double [28] = "ARTIKEL DOPPELT IN LI-FILE";
static char pzn_error  [28] = "PZN-PRUEFZIFFER FALSCH";

/* --------  user -------------- */
static const char* const user = "logindex"  ;

/* ------------------------------------------------------------------- */
static char* tokenize(char* string, char const* delimiter)
{
	static char *source = NULL;
	char *p = 0;
	char *result = 0;
	char  cDelimiter[2];

	cDelimiter[0] = delimiter;
	cDelimiter[1] = '\0';

	if(string != NULL)
	{
		source = string;
	}

	if(source == NULL)
	{
		return NULL;
	}

	if((p = strpbrk(source, cDelimiter)) != NULL)
	{
		*p = 0;
		result = source;

		int iTest1 = delimiter;
		int iTest2 = result[strlen(result)-1];

		if ((164 == iTest1) && (194 == iTest2))  // Fall C2A4 statt nur A4
			result[strlen(result)-1] = '\0';

		source = ++p;
	}

	return result;
}

static char* GetAtPosition(const char* string, char const* delimiter, int position, char* errmld)
{
	char temp [NO_SIGNS_ELEMENT] = {0};
	char tempRecord[NO_SIGNS + 1] = {0};
	char* p = "";
	int i = 0;

	strcpy(tempRecord, string);
	p = tokenize(tempRecord, delimiter);

	while(p)
	{
		if(i == position)
		{
			if(p != NULL)
			{
				memset(temp, '\0', NO_SIGNS_ELEMENT - 1); 

				if (strlen(p) >= NO_SIGNS_ELEMENT)
					strncpy(temp, p, NO_SIGNS_ELEMENT - 1);
				else
					strcpy(temp, p);

				ConvertUmlaute ( ( unsigned char *) temp, p);  
				break;
			}
			else
			{
				p = "";
			}
		}
		else
		{
			i++;
		}

		p = tokenize(NULL, delimiter);
	}

	return p;
}

static int ConvertArticleArtToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	int i = 0;
	char* value = "";

	while(i < NO_FIELDS_ART)
	{
		value = GetAtPosition(record, FILE_DELIMITER, i, errmld);

		switch(i)
		{
			case ART_GRPCD:
				strcpy(li->GRPCD, value);
				break;
			case ART_CDSO1:
				strcpy(li->CDSO1, value);
				break;
			case ART_PRDNO:
				li->PRDNO = atoi(value);
				break;
			case ART_SMCAT:
				strcpy(li->SMCAT, value);
				break;
			case ART_SMNO:
				li->SMNO = atoi(value);
				break;
			case ART_CLINCD:
				strcpy(li->CLINCD, value);
				break;
			case ART_VAT:
				li->VAT = atoi(value);
				break;
			case ART_SALECD:
				strcpy(li->SALECD, value);
				break;
			case ART_COOL:
				strcpy(li->COOL, value);
				break;
			case ART_CDBG:
				strcpy(li->CDBG, value);
				break;
			case ART_BG:
				strcpy(li->BG, value);
				break;
			case ART_EXP:
				li->EXP = atoi(value);
				break;
			case ART_QTY:
				li->QTY = atof(value);
				break;
			case ART_DSCRD:
				strcpy(li->DSCRD, value);
				break;
			case ART_DSCRF:
				strcpy(li->DSCRF, value);
				break;
			case ART_DSCRLONGD:
				strcpy(li->DSCRLONGD, value);
				break;
			case ART_DSCRLONGF:
				strcpy(li->DSCRLONGF, value);
				break;
			case ART_QTYUD:
				strcpy(li->QTYUD, value);
				break;
			case ART_QTYUF:
				strcpy(li->QTYUF, value);
				break;
			case ART_PCKTYPD:
				strcpy(li->PCKTYPD, value);
				break;
			case ART_PCKTYPF:
				strcpy(li->PCKTYPF, value);
				break;
			case ART_DEPCD:
				strcpy(li->DEPCD, value);
				break;
			case ART_OUTSAL:
				li->OUTSAL = atoi(value);
				break;
			case ART_STTOX:
				strcpy(li->STTOX, value);
				break;
			case ART_CE:
				strcpy(li->CE, value);
				break;
			case ART_SMCDAT:
				li->SMCDAT = atoi(value);
				break;
			case ART_SIST:
				li->SIST = atoi(value);
				break;
			case ART_ESIST:
				li->ESIST = atoi(value);
				break;
			case ART_BIOCID:
				li->BIOCID = atoi(value);
				break;
			case ART_BAGNO:
				strcpy(li->BAGNO, value);
				break;
			case ART_MULT: // MULT --> NOPCS
				li->NOPCS = atoi(value);
				break;
		}

		i++;
	}

	return retcode;
}

static int ConvertArticleCompanyToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	// Nur Hersteller oder Lieferanten sind zugelassen
	value = GetAtPosition(record, FILE_DELIMITER, ARTCOMP_ROLE, errmld);
	if(strncmp(value, "H", 1) == 0)
	{
		value = GetAtPosition(record, FILE_DELIMITER, ARTCOMP_COMPNO, errmld);
		li->COMPNO = atoi(value);

		value = GetAtPosition(record, FILE_DELIMITER, ARTCOMP_ARTNO1, errmld);
		strcpy(li->ARTNO1, value);
	}
	else if(strncmp (value, "L", 1) == 0)
	{
		value = GetAtPosition(record, FILE_DELIMITER, ARTCOMP_COMPNO, errmld);
		li->SUPPLNO = atoi(value);
	}
	else
	{
		retcode = 3;
	}

	return retcode;
}

static int ConvertArticleBarcodeToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	value = GetAtPosition(record, FILE_DELIMITER, ARTBAR_BCSTAT, errmld);
	if(strncmp(value, "A", 1) != 0)
	{
		retcode = 3;
		return retcode;
	}

	// Nur CDTYP = E13 (EAN13) / E14 (GTIN14) ist zugelassen
	value = GetAtPosition(record, FILE_DELIMITER, ARTBAR_CDTYP, errmld);
	
	if(strncmp(value, "E13", 4) == 0)
	{
		value = GetAtPosition(record, FILE_DELIMITER, ARTBAR_BC, errmld);
		strcpy(li->BC, value);
		bctype_ean = 1;
	}
	else if(strncmp(value, "E14", 4) == 0)
	{
		value = GetAtPosition(record, FILE_DELIMITER, ARTBAR_BC, errmld);
		strcpy(li->GTIN14, value);
		bctype_ean = 0;
	}
	else
	{
		retcode = 3;
		return retcode;
	}	

	return retcode;
}

static int ConvertArticleChainingToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	value = GetAtPosition(record, FILE_DELIMITER, ARTCH_CHTYPE, errmld);
	if(strncmp (value, "REP", 3) != 0)
	{
		retcode = 3;
		return retcode;
	}

	value = GetAtPosition(record, FILE_DELIMITER, ARTCH_PHAR2, errmld);
	li->PHAR2 = atoi(value);

	return retcode;
}

static int ConvertArticlePriceInformationToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	value = GetAtPosition(record, FILE_DELIMITER, ARTPRI_PTYP, errmld);
	if(strncmp(value, "PEXF", 4) == 0)
	{
		value = GetAtPosition(record, FILE_DELIMITER, ARTPRI_PRICE, errmld);
		li->PRICE_PEXF = atof(value);
		pricetype_exf = 1;
	}
	else if(strncmp(value, "PPUB", 4) == 0)
	{
		value = GetAtPosition(record, FILE_DELIMITER, ARTPRI_PRICE, errmld);
		li->PRICE_PPUB = atof(value);
		pricetype_exf = 0;
	}
	else
	{
		retcode = 3;
		return retcode;
	}

	value = GetAtPosition(record, FILE_DELIMITER, ARTPRI_VDAT, errmld);
	if ( li->VDAT == 0 ||												// Gültigkeitsdatum nur übernehmen, wenn noch keines gesetzt
		(li->VDAT > atoi(value) && atoi(value) > tages_datum) ||	// oder gesetztes > geliefertes && geliefertes > heute
		(li->VDAT < atoi(value) && li->VDAT < tages_datum)		  )	// oder gesetztes < geliefertes && gesetztes < heute		
	{
		li->VDAT = atoi(value);
	}

	return retcode;
}

static int ConvertArticlePriceInformationNewToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	value = GetAtPosition(record, FILE_DELIMITER, ARTPRICE_PTYP, errmld);
	if(strncmp(value, "PEXF", 4) == 0)
	{
		value = GetAtPosition(record, FILE_DELIMITER, ARTPRICE_PRICE, errmld);
		li->PRICE_PEXF = atof(value);
		pricetype_exf = 1;
	}
	else if(strncmp(value, "PPUB", 4) == 0)
	{
		value = GetAtPosition(record, FILE_DELIMITER, ARTPRICE_PRICE, errmld);
		li->PRICE_PPUB = atof(value);
		pricetype_exf = 0;
	}
	else
	{
		retcode = 3;
		return retcode;
	}

	value = GetAtPosition(record, FILE_DELIMITER, ARTPRICE_VDAT, errmld);
	if ( li->VDAT == 0 ||												// Gültigkeitsdatum nur übernehmen, wenn noch keines gesetzt
		(li->VDAT > atoi(value) && atoi(value) > tages_datum) ||	// oder gesetztes > geliefertes && geliefertes > heute
		(li->VDAT < atoi(value) && li->VDAT < tages_datum)		  )	// oder gesetztes < geliefertes && gesetztes < heute		
	{
		li->VDAT = atoi(value);
	}

	return retcode;
}

static int ConvertArticleRelationMiGelToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	// Nur LINENO = 1 ist zugelassen
	value = GetAtPosition(record, FILE_DELIMITER, ARTMIG_LINENO, errmld);
	if(strncmp(value, "1", 1) != 0 )
	{
		retcode = 3;
		return retcode;
	}

	value = GetAtPosition(record, FILE_DELIMITER, ARTMIG_MIGCD, errmld);
	strcpy(li->MIGCD, value);

	return retcode;
}

static int ConvertArticleInsuranceCodesToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	 // Nur NINCD = 10 oder 16 ist relevant
	value = GetAtPosition(record, FILE_DELIMITER, ARTINS_NINCD, errmld);
	if(strncmp(value, "10", 2) == 0 || strncmp(value, "16", 2) == 0)
	{
		li->NINCD = atoi(value);
	}
	else
	{
		retcode = 3;
	}

	return retcode;
}


static int ConvertIndicationOfDangerToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	const char* hochentz = "F+";
	const char* leichtentz = "F";
	const char* explosion = "E";
	const char* brand = "O";
	const char* aetzend = "C";
	const char* sehrgiftig = "T+";
	const char* giftig = "T";
	const char* gesundhsch = "XN";
	const char* reizend = "XI";
	const char* umwelt = "N";

	value = GetAtPosition(record, FILE_DELIMITER, ARTDAN_CDVAL, errmld);

	if(strncmp(value, hochentz, 2) == 0)
	{
		strcpy(li->GS_HOCHENTZ, "1");
	}
	else if(strncmp(value, leichtentz, 1) == 0)
	{
		strcpy(li->GS_LEICHTENTZ, "1");
	}
	else if(strncmp(value, explosion, 1) == 0)
	{
		strcpy(li->GS_EXPLOSION, "1");
	}
	else if(strncmp(value, brand, 1) == 0)
	{
		strcpy(li->GS_BRAND, "1");
	}
	else if(strncmp(value, aetzend, 1) == 0)
	{
		strcpy(li->GS_AETZEND, "1");
	}
	else if(strncmp(value, sehrgiftig, 2) == 0)
	{
		strcpy(li->GS_SEHRGIFTIG, "1");
	}
	else if(strncmp(value, giftig, 1) == 0)
	{
		strcpy(li->GS_GIFTIG, "1");
	}
	else if(strncmp(value, gesundhsch, 2) == 0)
	{
		strcpy(li->GS_GESUNDHSCH, "1");
	}
	else if(strncmp(value, reizend, 2) == 0)
	{
		strcpy(li->GS_REIZEND, "1");
	}
	else if(strncmp(value, umwelt, 1) == 0)
	{
		strcpy(li->GS_UMWELT, "1");
	}
	else
	{
		//...
	}

	return retcode;
}

static int ConvertGhsHazardStatementToClihasatz(struct CLIHSATZ* lihsatz, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	value = GetAtPosition(record, FILE_DELIMITER, ARTDAN_CDVAL, errmld);
	strcpy(lihsatz->HAZARDNOTEID, value);

	value = GetAtPosition(record, FILE_DELIMITER, ARTDAN_PARENTKEY, errmld);
	lihsatz->PHAR = atoi(value);
	
	return retcode;
}

static int ConvertGhsIndicationOfDangerToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	const char* explodingBomb = "GHS01";
	const char* flame = "GHS02";
	const char* flameOverCircle = "GHS03";
	const char* gasCylinder = "GHS04";
	const char* corrosion = "GHS05";
	const char* skullAndCrossbones = "GHS06";
	const char* exclamationMark = "GHS07";
	const char* healthHazard = "GHS08";
	const char* environment = "GHS09";

	value = GetAtPosition(record, FILE_DELIMITER, ARTDAN_CDVAL, errmld);

	if(strncmp(value, explodingBomb, 5) == 0)
	{
		li->PICTOGRAM01_FLAG = 1;
	}
	else if(strncmp(value, flame, 5) == 0)
	{
		li->PICTOGRAM02_FLAG = 1;
	}
	else if(strncmp(value, flameOverCircle, 5) == 0)
	{
		li->PICTOGRAM03_FLAG = 1;
	}
	else if(strncmp(value, gasCylinder, 5) == 0)
	{
		li->PICTOGRAM04_FLAG = 1;
	}
	else if(strncmp(value, corrosion, 5) == 0)
	{
		li->PICTOGRAM05_FLAG = 1;
	}
	else if(strncmp(value, skullAndCrossbones, 5) == 0)
	{
		li->PICTOGRAM06_FLAG = 1;
	}
	else if(strncmp(value, exclamationMark, 5) == 0)
	{
		li->PICTOGRAM07_FLAG = 1;
	}
	else if(strncmp(value, healthHazard, 5) == 0)
	{
		li->PICTOGRAM08_FLAG = 1;
	}
	else if(strncmp(value, environment, 5) == 0)
	{
		li->PICTOGRAM09_FLAG = 1;
	}
	else
	{
		//...
	}

	return retcode;
}

static int ConvertDangerCodeToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	const char* indicationOfDanger = "16";
	const char* riskPhrase = "17";
	const char* securityPhrase = "18";
	const char* ghsHazardStatement = "24";
	const char* ghsPrecautionaryStatement = "25";
	const char* ghsIndicationOfDanger = "33";
	const char* signalWord = "67";

	struct CLIHSATZ* plihsatz, lihsatz;
	plihsatz = &lihsatz;

	value = GetAtPosition(record, FILE_DELIMITER, ARTDAN_CDTYP, errmld);

	if(strncmp(value, indicationOfDanger, 2) == 0)
	{
		retcode = ConvertIndicationOfDangerToCliart(li, record, errmld);
	}
	else if(strncmp(value, riskPhrase, 2) == 0 )
	{
		//...
	}
	else if(strncmp(value, securityPhrase, 2) == 0 )
	{
		//...
	}
	else if(strncmp(value, ghsHazardStatement, 2) == 0 )
	{
		long result = 0L;
		char* p;

		// Erstes Vorkommen von Typ 24 -> leere m_szEUHazard
		if (0 == strcmp(m_szEUHazard, "INIT"))
			memset(m_szEUHazard, 0x00, sizeof(m_szEUHazard));

		retcode = ConvertGhsHazardStatementToClihasatz(plihsatz, record, errmld);

		if (0 != strncmp(plihsatz->HAZARDNOTEID, "EUH", 3))
		{
			plihsatz->LINR = lidatumnr;

			lihsaetze[hazardStatementsCounter] = lihsatz;

			p = lihsatz.HAZARDNOTEID;

			// ignore first character, otherwise check will fail cause logIndex provides character prefix such as 'H' which is not conform to hazardnote master data.
			p++;

			exists_hsatz(p, &result, errmld);
			if(result == 0)
			{
				notExistingHazardnotes++;
			}

			ins_clihsatz(&Fd_Clihsatz, plihsatz, errmld);

			hazardStatementsCounter++;
		}
		else
		{
			char szTemp[15+1];
			memset(szTemp, 0x00, sizeof(szTemp));

			for (int j = 3; j < strlen(plihsatz->HAZARDNOTEID); j++)
				szTemp[j-3] = plihsatz->HAZARDNOTEID[j];

			if (0 == strlen(m_szEUHazard))
			{
				strcpy(m_szEUHazard, szTemp);
			}
			else
			{
				strcat(m_szEUHazard, "; ");
				strcat(m_szEUHazard, szTemp);
			}

			strcpy(li->HAZARD_STMT, m_szEUHazard);

#ifdef _DEBUG
			printf("HAZARD-Statement: (%s)\n", li->HAZARD_STMT);
#endif
		}
	}
	else if(strncmp(value, ghsPrecautionaryStatement, 2) == 0 )
	{
		//...
	}
	else if(strncmp(value, ghsIndicationOfDanger, 2) == 0 )
	{
		retcode = ConvertGhsIndicationOfDangerToCliart(li, record, errmld);
	}
	else if(strncmp(value, signalWord, 2) == 0 )
	{
		value = GetAtPosition(record, FILE_DELIMITER, ARTDAN_CDVAL, errmld);

		strcpy(li->CDVAL, value);
	}
	else
	{
		//...
	}

	return retcode;
}

static int ConvertSdsToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	value = GetAtPosition(record, FILE_DELIMITER, SDS_DE, errmld);
	if(value && strcmp(value, "") != 0)
		li->SDS_DATE_DE = atoi(value);

	value = GetAtPosition(record, FILE_DELIMITER, SDS_IT, errmld);
	if (value && strcmp(value, "") != 0)
		li->SDS_DATE_IT = atoi(value);

	value = GetAtPosition(record, FILE_DELIMITER, SDS_EN, errmld);
	if (value && strcmp(value, "") != 0)
		li->SDS_DATE_EN = atoi(value);

	value = GetAtPosition(record, FILE_DELIMITER, SDS_FR, errmld);
	if (value && strcmp(value, "") != 0)
		li->SDS_DATE_FR = atoi(value);

	/* TH SDS:
	direkte Versorgung neuer Tabelle csdslang für alle Sprachen, oder erst eine Zwischentabelle clisds (analog clihsatz) !?
	pro Sprache ein Änderungsdatum in csdslang setzen
	Änderungsdatum und sds_date in csafetydatasheet immer mit aktuellstem oder mit deutschem Wert belegen?
	sds_link ist immer http://apps.hcisolutions.ch/sds/phc/[pzn]/[language]/ --> in jedem Artikel automatisch setzen (csafetydatasheet + csdslang) oder 1 zentraler Parameter ???
	Aufruf Thrift- Service für KSC ???
	ggfs. clisds löschen am Ende von zpliartik ...
	ggfs. Übernahme clisds --> csdslang via zplignart + Anzeige im LogIndex- Dialog
	ggfs. Pflege csdslang in EkZdp !

	csdslang via zpmasaen auch löschen!
	*/

	return retcode;
}

static int ConvertReguToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	value = GetAtPosition(record, FILE_DELIMITER, REGU_REGULATION, errmld);
	if (strcmp(value, "SALE.FMD.SMVO") == 0)
		li->FMD_FLAG = 1;	

	return retcode;
}

static int ConvertArtAdrToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	int bFlag   = 0;
	char *value = "";
	char *ptr   = NULL;

	/* -------------------------------------------------------------------------------------------------------
	CPR-220802:

	UN-Datensatz bestehend aus fünf Teilschlüsseln, der den Eintrag in der ADR Tabelle eindeutig identifiziert. 
	Er hat das Format „UNNR;DESCR;KL;KC;VG":
	- UNNR: UN-Nummer (Zahl, 4 Stellen)
	- DESCR: Benennung und Beschreibung (Text, max. 500 Stellen)
	- KL: Klasse (Text, 5 Stellen)
	- KC: Klassifizierungscode (Text, 5 Stellen)
	- VG: Verpackungsgruppe (Text, 3 Stellen)

	Falls NOTADR => UN-NUmmer ist 9999.

	Schweizer Vereinbarung für Batterien:
	Falls UNNR == 3090 || 3091 || 3480 || 3481 => UN-Nummer ist leer
	Falls DESCR beinhaltet 'LITHIUM - METALL' || 'LITHIUM METALL' || 'LITHIUM - IONEN' || 'LITHIUM IONEN'
	      => UN-Nummer ist leer
	------------------------------------------------------------------------------------------------------- */

	value = GetAtPosition(record, FILE_DELIMITER, ARTADR_ADRVAL, errmld);

	if (0 == strcmp(value, "NOTADR"))
	{
		strcpy(li->G_UN_NR, "9999");
		bFlag = 1;
	}

	value = GetAtPosition(record, FILE_DELIMITER, ARTADR_UNREC, errmld);

	char szKopie[4+500+5+5+3+1];
	strcpy(szKopie, value);

	int i = 1;
	ptr = strtok(szKopie, ";");

	while(ptr != NULL)
	{
		switch (i)
		{
			case 1:

                // Fall für gesetztes NOTADR aus logindex und nicht vorheriges 9999 aus DB!
				if (0 == bFlag)
				{
					strcpy(li->G_UN_NR, ptr);
				}
				break;

			case 2:

				if ( (0 == strcmp(li->G_UN_NR, "3090"))
				  || (0 == strcmp(li->G_UN_NR, "3091"))
				  || (0 == strcmp(li->G_UN_NR, "3480"))
				  || (0 == strcmp(li->G_UN_NR, "3481"))
				  || (NULL != strstr(ptr, "LITHIUM - METALL"))
				  || (NULL != strstr(ptr, "LITHIUM METALL"))
				  || (NULL != strstr(ptr, "LITHIUM - IONEN"))
				  || (NULL != strstr(ptr, "LITHIUM IONEN")) )
				{
					strcpy(li->G_UN_NR, "");
				}
				break;

			case 3:

				strcpy(li->LAGERKLASSE, ptr);
				
				// Lagerklasse ohne evtl. '/' uebernehmen, also z,B, '10/12' => '1012'
				char szTemp[5+1];
				memset(szTemp, 0x00, sizeof(szTemp));
				int jj=0;

				for (int ii=0; ii < 5; ii++)
				{
					if (li->LAGERKLASSE[ii] != '/')
					{
						szTemp[jj] = li->LAGERKLASSE[ii];
						jj++;
					}
				}

				strcpy(li->LAGERKLASSE, szTemp);

				// Mapping der Werte Lagerklasse
				// 9   -> 1013
				// 5.1 -> 5.1A
				if (strncmp(li->LAGERKLASSE, "9", 1) == 0)
				{
					strcpy(li->LAGERKLASSE, "1013");
				}
				else if (strncmp(li->LAGERKLASSE, "5.1", 3) == 0)
				{
					strcpy(li->LAGERKLASSE, "5.1A");
				}

				break;

			case 4:

				strcpy(li->GG_KLASSCODE, ptr);
				break;

			case 5:

				strcpy(li->GG_VERPACKCODE, ptr);
				break;

			default:

				break;
		}

#ifdef _DEBUG
		printf("Subtoken %i: (%s)\n", i, ptr);
#endif

		ptr = strtok(NULL, ";");
		i++;
	}

#ifdef _DEBUG
	printf("li->G_UN_NR       : (%s)\n", li->G_UN_NR);
	printf("li->LAGERKLASSE   : (%s)\n", li->LAGERKLASSE);
	printf("li->GG_KLASSCODE  : (%s)\n", li->GG_KLASSCODE);
	printf("li->GG_VERPACKCODE: (%s)\n", li->GG_VERPACKCODE);
#endif

	return retcode;
}

static int ConvertArtSlToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	value = GetAtPosition(record, FILE_DELIMITER, ARTSL_BAGDOSSIER, errmld);
	li->BAGDOSSIER = atoi(value);

	return retcode;
}

static int WriteAllCliohsatzToDb(char* errmld)
{
	int retcode = 0;
	int i = 0;
	struct CLIOHSATZ dbcliohsatz;
	struct CLIOHSATZ* cliohsatz = &dbcliohsatz;

	for(i = 0; i < hazardStatementsCounter; i++)
	{
		cliohsatz->PHAR = lihsaetze[i].PHAR;
		strcpy(cliohsatz->HAZARDNOTEID, lihsaetze[i].HAZARDNOTEID);

		ins_cliohsatz(&Fd_Cliohsatz, cliohsatz, errmld);
	}

	return retcode;
}

static void SetPrdGrpCd(struct CLIART* li, char* value)
{
	Trim(value);

	if (strcmp(value, "PHYTO") == 0)
		li->PHYTOPHARMAKON[0] = '1';
	else if (strcmp(value, "BLOOD") == 0)
		li->BLOOD = 1;
	else if (strcmp(value, "HOM") == 0)
		li->HOMOEOPATHIKUM[0] = '1';
	else if (strcmp(value, "ANTHROPOSOPHIC") == 0)
		li->ANTHROPOSOPHIKUM[0] = '1';
	else if (strcmp(value, "VET") == 0)
		li->TIERARZNEI[0] = '1';
	else if (strcmp(value, "MD") == 0)
		li->MEDIZINPRODUKT[0] = '1';
	else if (strcmp(value, "VACC") == 0)
		li->IMPFSTOFF[0] = '1';
}

static int ConvertProductCptEntryToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	value = GetAtPosition(record, FILE_DELIMITER, PRDGRP_PRDGRPCD, errmld);

	SetPrdGrpCd(li, value);

	return retcode;
}

static int ConvertProductEntryToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;
	char* value = "";

	value = GetAtPosition(record, FILE_DELIMITER, PRD_GENCD, errmld);
	if (strstr(" GO", value) != NULL){
		strcpy(li->GENCD, value);
	}
	else {
		strcpy(li->GENCD, "");
	}
	if (strcmp(value, "S") == 0){
		strcpy(li->BIOSIM, "1");
	}

	value = GetAtPosition(record, FILE_DELIMITER, PRD_ATC, errmld);
	strcpy(li->ATC, value);

	value = GetAtPosition(record, FILE_DELIMITER, PRD_BLOOD, errmld);
	li->BLOOD = atoi(value);

	value = GetAtPosition(record, FILE_DELIMITER, PRD_MDCLASS, errmld);
	strcpy(li->MDCLASS, value);

	/* BIOSIM */
	value = GetAtPosition(record, FILE_DELIMITER, PRD_BIOSIM, errmld);
	if (strcmp(value, "S") == 0)
		strcpy(li->BIOSIM, "1");
	else
		strcpy(li->BIOSIM, "0");

	/* MDATTR */
	value = GetAtPosition(record, FILE_DELIMITER, PRD_MDATTR, errmld);

	if (0 == strcmp("IMPLANTABLE", value))
	{
		li->SERIAL_NUMBER_TRACKING = 1;
	}
	else 
	{
		li->SERIAL_NUMBER_TRACKING = 0;
	}

	return retcode;
}

static void resetPrdGrpCdFlags(struct CLIART* li)
{
	li->PHYTOPHARMAKON[0] = '0';
	li->HOMOEOPATHIKUM[0] = '0';
	li->ANTHROPOSOPHIKUM[0] = '0';
	li->TIERARZNEI[0] = '0';
	li->MEDIZINPRODUKT[0] = '0';
	li->IMPFSTOFF[0] = '0';
}

static int ConvertRecordToCliart(struct CLIART* li, const char* record, char* errmld)
{
	int retcode = 0;

	switch (m_eFileArt)
	{
		case ARTICLE_ART:
			retcode =  ConvertArticleArtToCliart(li, record, errmld);
			break;
		case ARTICLE_ARTCOMP:
			retcode = ConvertArticleCompanyToCliart(li, record, errmld);
			break;
		case ARTICLE_ARTBAR:
			retcode = ConvertArticleBarcodeToCliart(li, record, errmld);
			break;
		case ARTICLE_ARTCH:
			retcode = ConvertArticleChainingToCliart(li, record, errmld);
			break;
		case ARTICLE_ARTPRI:
			retcode = ConvertArticlePriceInformationToCliart(li, record, errmld);
			break;
		case ARTICLE_ARTPRI_NEW:
			retcode = ConvertArticlePriceInformationNewToCliart(li, record, errmld);
			break;
		case ARTICLE_ARTMIG:
			retcode = ConvertArticleRelationMiGelToCliart(li, record, errmld);
			break;
		case ARTICLE_ARTINS:
			retcode = ConvertArticleInsuranceCodesToCliart(li, record, errmld);
			break;
		case ARTICLE_ARTDAN:
			retcode = ConvertDangerCodeToCliart(li, record, errmld);
			break;
		case ARTICLE_SDS:
			retcode = ConvertSdsToCliart(li, record, errmld);
			break;
		case ARTICLE_ARTADR:
			retcode = ConvertArtAdrToCliart(li, record, errmld);
			break;
		case ARTICLE_ARTSL:
			retcode = ConvertArtSlToCliart(li, record, errmld);
			break;
		case ARTICLE_REGULATIONS:
			retcode = ConvertReguToCliart(li, record, errmld);
			break;
		case PRODUCT_PRD:
			retcode = ConvertProductEntryToCliart(li, record, errmld);
			break;
		case PRODUCT_PRD_CPT:
			retcode = ConvertProductCptEntryToCliart(li, record, errmld);
			break;
	}

	return retcode;
}

/* ------------------------------------------------------------------- */
static void InitializeNBStr()
{
	ze_lcpy( li.LISTATUS,		NB_PL_OK, L_CLIART_LISTATUS );
	ze_lcpy( li.NBSTATUS,		NB_PL_OK, L_CLIART_NBSTATUS );
	ze_lcpy( li.ZAENDERUNG,		NB_PL_OK, L_CLIART_ZAENDERUNG );
    ze_lcpy( li.NB_LI_PLAUSI,	NB_PL_OK, L_CLIART_NB_LI_PLAUSI );
	ze_lcpy( li.NB_LI_ZWING,	NB_PL_OK, L_CLIART_NB_LI_ZWING );
	ze_lcpy( li.NB_LI_NZWING,	NB_PL_OK, L_CLIART_NB_LI_NZWING );
}

/* ------------------------------------------------------------------- */
static int LoadCLIOART(char *errmld)
{
	int sqlret;

	sqlret = sel_clioart(&Fd_Clioart, li.PHAR, &lio, errmld);

	if (pzn_current != li.PHAR)
	{
		if (sqlret == 0)
			clio_exists = 1;
		else if (sqlret == 100)
			clio_exists = 0;

		pzn_current = li.PHAR;
	}

#ifdef _DEBUG
	printf("LoadCLIOART - select from clioart for article %d returns %d\n", li.PHAR, sqlret);
#endif

	if (sqlret == 0)
	{
		if ( LIOartFill( &lio, &li, tages_datum, errmld, clio_exists ) != 0 ) 
			return 1;
		
		/*update*/
		sqlret = upd_clioart(&Fd_Clioart, &lio, errmld);

#ifdef _DEBUG
		printf("LoadCLIOART: update existing entry for %d returns %d\n", lio.PHAR, sqlret);
#endif

		if (sqlret == 0)
			anz_upd++;
	}
	else if (sqlret == 100)
	{
		FdInitTabBuf( Fd_Clioart, &lio );		

		if ( LIOartFill( &lio, &li, tages_datum, errmld, clio_exists ) != 0 ) 
			return 1;
		
		lio.PHAR = li.PHAR;
		lio.HERSTELLER_NR = -1;

		/*insert*/
		sqlret = ins_clioart(&Fd_Clioart, &lio, errmld); 

#ifdef _DEBUG
		printf("LoadCLIOART: insert new entry for %d returns %d\n", lio.PHAR, sqlret);
#endif

		if (sqlret == 0)
			anz_ins++;
	}

	return sqlret;
}

/* --- EAN --------------------- */
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

int TestEanNr( char *ean )
{
  int i;

  /* keine EAN, wenn nur 0 oder blank */
  i = 0;
  while ( ean[i] && ( ean[i] == ' ' || ean[i] == '0' ) ) i++;
  if ( ean[i] == '\0' )
    return 0;

  Trim(ean);

  i = 0;
  while ( ean[i] && ean[i] >= '0' && ean[i] <= '9' ) i++;
  if ( ean[i] == '\0' )
    return  1;     /* EAN-Nr korrekt */
  else
    return -1;     /* EAN-Nr falsch */
}

/* --------- Vergleichs-Werte -------------------- */ 
static char *Smcat = " ABCDE";
static char *YesNo  = "YN";
static char *Mwst  = "012"; // transferred to PHOENIX values before
static char *YesBlank  = "Y ";
static char *YesOneBlank  = "Y1 ";
static char *Codebg = " ABC";
static char *Gencd = " GOS";
static char *NullEins = "01";
static char *Aender = " NRAL";

/* ------------------------------------------------------------------- */
static void FillLIPlausiErr( )
{
	if ( m_eFileArt == ARTICLE_ART ) // korrekt unter der Annahme, dass MsgType 10 immer als erste Nachrichtenart kommt!
	{
		SetLINumBlankErr(li.CDSO1, li.NB_LI_PLAUSI, PL_CDSO1);
		SetLINumErr		(li.PRDNO, li.NB_LI_PLAUSI, PL_PRDNO);
		SetLIErr		(li.SMCAT, Smcat, li.NB_LI_PLAUSI, PL_SMCAT);
		SetLINumErr		(li.SMNO, li.NB_LI_PLAUSI, PL_SMNO);
		SetLIErr		(li.CLINCD, YesNo, li.NB_LI_PLAUSI, PL_CLINCD);
		SetLIErrInt		(li.VAT, Mwst, li.NB_LI_PLAUSI, PL_VAT);
		SetLIErr		(li.COOL, YesOneBlank, li.NB_LI_PLAUSI, PL_COOL);
		SetLIErr		(li.CDBG, Codebg, li.NB_LI_PLAUSI, PL_CDBG);
		SetLIErr		(li.BG, YesNo, li.NB_LI_PLAUSI, PL_BG);
		SetLINumErr		(li.EXP, li.NB_LI_PLAUSI, PL_EXP);
		SetLIPreisErr	(li.QTY, li.NB_LI_PLAUSI, PL_QTY);
		SetLINumErr		(li.NOPCS, li.NB_LI_PLAUSI, PL_NOPCS);
		SetLIErr		(li.DEPCD, YesNo, li.NB_LI_PLAUSI, PL_DEPCD);
		SetLINumErr		(li.OUTSAL, li.NB_LI_PLAUSI, PL_OUTSAL);
		SetLIErr		(li.STTOX, YesNo, li.NB_LI_PLAUSI, PL_STTOX);
		SetLIErr		(li.CE, YesBlank, li.NB_LI_PLAUSI, PL_CE);
		SetLINumErr		(li.SMCDAT, li.NB_LI_PLAUSI, PL_SMCDAT);
		SetLINumErr		(li.SIST, li.NB_LI_PLAUSI, PL_SIST);
		SetLINumErr		(li.ESIST, li.NB_LI_PLAUSI, PL_ESIST);
		SetLIErrInt		(li.BIOCID, NullEins, li.NB_LI_PLAUSI, PL_BIOCID);
		SetLINumErr		(li.BAGDOSSIER, li.NB_LI_PLAUSI, PL_BAGDOSSIER);

		if ( clio_exists == 0 ) // für Neuanlagen, alle Felder editierbar machen --> explicit treatment for all fields not delivered by msgtype 010 !!!
		{
			li.NB_LI_PLAUSI[ PL_NINCD ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_COMPNO ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_SUPPLNO ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_ARTNO1 ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_BC ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_GTIN14 ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_PHAR2 ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_VDAT ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_PRICE_PEXF ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_PRICE_PPUB ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_MIGCD ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_GENCD ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_BLOOD ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_PRDGRPCD ] = NB_PL_OK; 
			li.NB_LI_PLAUSI[ PL_ATC ] = NB_PL_OK; 

			li.NB_LI_PLAUSI[ PL_PICTOGRAM01_FLAG ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM02_FLAG ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM03_FLAG ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM04_FLAG ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM05_FLAG ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM06_FLAG ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM07_FLAG ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM08_FLAG ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM09_FLAG ] = NB_PL_OK;

			li.NB_LI_PLAUSI[ PL_GS_EXPLOSION ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_GS_HOCHENTZ ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_GS_LEICHTENTZ ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_GS_BRAND ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_GS_AETZEND ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_GS_SEHRGIFTIG ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_GS_GIFTIG ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_GS_GESUNDHSCH ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_GS_REIZEND ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_GS_UMWELT ] = NB_PL_OK;

			li.NB_LI_PLAUSI[ PL_SDS_DATE_DE ] = NB_PL_OK;
			li.NB_LI_PLAUSI[ PL_HAZARDSTATEMENT ] = NB_PL_OK;

			li.NB_LI_PLAUSI[PL_FMD_FLAG] = NB_PL_OK;
			li.NB_LI_PLAUSI[PL_G_UN_NR] = NB_PL_OK;
			li.NB_LI_PLAUSI[PL_SDS_DATE_IT] = NB_PL_OK;
			li.NB_LI_PLAUSI[PL_SDS_DATE_EN] = NB_PL_OK;
			li.NB_LI_PLAUSI[PL_SDS_DATE_FR] = NB_PL_OK;
			
			li.NB_LI_PLAUSI[PL_BIOSIM] = NB_PL_OK;
		}
		else
		{
			li.NB_LI_PLAUSI[ PL_NINCD ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_COMPNO ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_SUPPLNO ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_ARTNO1 ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_BC ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_GTIN14 ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_PHAR2 ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_VDAT ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_PRICE_PEXF ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_PRICE_PPUB ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_MIGCD ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_GENCD ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_BLOOD ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_ATC ] = NB_PL_NO_VAL; 
			li.NB_LI_PLAUSI[ PL_PRDGRPCD ] = NB_PL_NO_VAL; 

			li.NB_LI_PLAUSI[ PL_PICTOGRAM01_FLAG ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM02_FLAG ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM03_FLAG ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM04_FLAG ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM05_FLAG ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM06_FLAG ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM07_FLAG ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM08_FLAG ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_PICTOGRAM09_FLAG ] = NB_PL_NO_VAL;

			li.NB_LI_PLAUSI[ PL_GS_EXPLOSION ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_GS_HOCHENTZ ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_GS_LEICHTENTZ ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_GS_BRAND ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_GS_AETZEND ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_GS_SEHRGIFTIG ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_GS_GIFTIG ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_GS_GESUNDHSCH ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_GS_REIZEND ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_GS_UMWELT ] = NB_PL_NO_VAL;

			li.NB_LI_PLAUSI[ PL_SDS_DATE_DE ] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[ PL_HAZARDSTATEMENT ] = NB_PL_NO_VAL;

			li.NB_LI_PLAUSI[PL_FMD_FLAG] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[PL_G_UN_NR] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[PL_SDS_DATE_IT] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[PL_SDS_DATE_EN] = NB_PL_NO_VAL;
			li.NB_LI_PLAUSI[PL_SDS_DATE_FR] = NB_PL_NO_VAL;
			
			li.NB_LI_PLAUSI[PL_BIOSIM] = NB_PL_NO_VAL;
		}
	}
	else if ( m_eFileArt == ARTICLE_ARTINS )
	{
		SetLINumErr		(li.NINCD, li.NB_LI_PLAUSI, PL_NINCD);
	}
	else if ( m_eFileArt == ARTICLE_ARTCOMP )
	{
		SetLINumErr		(li.COMPNO, li.NB_LI_PLAUSI, PL_COMPNO);
		SetLINumErr		(li.SUPPLNO, li.NB_LI_PLAUSI, PL_SUPPLNO);
	}
	else if ( m_eFileArt == ARTICLE_ARTBAR )
	{
		SetLITrueFalse  ( TestEanNr(li.BC) == -1, li.NB_LI_PLAUSI, PL_BC );
	}
	else if ( m_eFileArt == ARTICLE_ARTCH )
	{
		SetLINumErr		(li.PHAR2, li.NB_LI_PLAUSI, PL_PHAR2);
	}
	else if ( m_eFileArt == ARTICLE_ARTPRI )
	{
		SetLINumErr		(li.VDAT, li.NB_LI_PLAUSI, PL_VDAT);
		SetLIPreisErr	(li.PRICE_PEXF, li.NB_LI_PLAUSI, PL_PRICE_PEXF);
		SetLIPreisErr	(li.PRICE_PPUB, li.NB_LI_PLAUSI, PL_PRICE_PPUB);
	}
	else if ( m_eFileArt == ARTICLE_ARTPRI_NEW )
	{
		SetLINumErr		(li.VDAT, li.NB_LI_PLAUSI, PL_VDAT);
		SetLIPreisErr	(li.PRICE_PEXF, li.NB_LI_PLAUSI, PL_PRICE_PEXF);
		SetLIPreisErr	(li.PRICE_PPUB, li.NB_LI_PLAUSI, PL_PRICE_PPUB);
	}
	else if ( m_eFileArt == ARTICLE_ARTMIG )
	{
		// PL_MIGCD
	}
	else if ( m_eFileArt == ARTICLE_ARTDAN )
	{
		SetLINumErr		(li.PICTOGRAM01_FLAG, li.NB_LI_PLAUSI, PL_PICTOGRAM01_FLAG);
		SetLINumErr		(li.PICTOGRAM02_FLAG, li.NB_LI_PLAUSI, PL_PICTOGRAM02_FLAG);
		SetLINumErr		(li.PICTOGRAM03_FLAG, li.NB_LI_PLAUSI, PL_PICTOGRAM03_FLAG);
		SetLINumErr		(li.PICTOGRAM04_FLAG, li.NB_LI_PLAUSI, PL_PICTOGRAM04_FLAG);
		SetLINumErr		(li.PICTOGRAM05_FLAG, li.NB_LI_PLAUSI, PL_PICTOGRAM05_FLAG);
		SetLINumErr		(li.PICTOGRAM06_FLAG, li.NB_LI_PLAUSI, PL_PICTOGRAM06_FLAG);
		SetLINumErr		(li.PICTOGRAM07_FLAG, li.NB_LI_PLAUSI, PL_PICTOGRAM07_FLAG);
		SetLINumErr		(li.PICTOGRAM08_FLAG, li.NB_LI_PLAUSI, PL_PICTOGRAM08_FLAG);
		SetLINumErr		(li.PICTOGRAM09_FLAG, li.NB_LI_PLAUSI, PL_PICTOGRAM09_FLAG);

		SetLIErr		(li.GS_EXPLOSION, NullEins, li.NB_LI_PLAUSI, PL_GS_EXPLOSION);
		SetLIErr		(li.GS_HOCHENTZ, NullEins, li.NB_LI_PLAUSI, PL_GS_HOCHENTZ);
		SetLIErr		(li.GS_LEICHTENTZ, NullEins, li.NB_LI_PLAUSI, PL_GS_LEICHTENTZ);
		SetLIErr		(li.GS_BRAND, NullEins, li.NB_LI_PLAUSI, PL_GS_BRAND);
		SetLIErr		(li.GS_AETZEND, NullEins, li.NB_LI_PLAUSI, PL_GS_AETZEND);
		SetLIErr		(li.GS_SEHRGIFTIG, NullEins, li.NB_LI_PLAUSI, PL_GS_SEHRGIFTIG);
		SetLIErr		(li.GS_GIFTIG, NullEins, li.NB_LI_PLAUSI, PL_GS_GIFTIG);
		SetLIErr		(li.GS_GESUNDHSCH, NullEins, li.NB_LI_PLAUSI, PL_GS_GESUNDHSCH);
		SetLIErr		(li.GS_REIZEND, NullEins, li.NB_LI_PLAUSI, PL_GS_REIZEND);
		SetLIErr		(li.GS_UMWELT, NullEins, li.NB_LI_PLAUSI, PL_GS_UMWELT);

		//SetLINumErr		(li.SDS_DATE_DE, li.NB_LI_PLAUSI, PL_SDS_DATE_DE);
	}
	else if(m_eFileArt == ARTICLE_SDS)
	{
		SetLINumErr		(li.SDS_DATE_DE, li.NB_LI_PLAUSI, PL_SDS_DATE_DE);
		SetLINumErr		(li.SDS_DATE_IT, li.NB_LI_PLAUSI, PL_SDS_DATE_IT);
		SetLINumErr		(li.SDS_DATE_EN, li.NB_LI_PLAUSI, PL_SDS_DATE_EN);
		SetLINumErr		(li.SDS_DATE_FR, li.NB_LI_PLAUSI, PL_SDS_DATE_FR);
	}
	else if ( m_eFileArt == PRODUCT_PRD_CPT )
	{
		// nothing to do here - PL_PRDGRPCD is processed separatly
	}
	else if ( m_eFileArt == PRODUCT_PRD )
	{
		SetLIErr		(li.GENCD, Gencd, li.NB_LI_PLAUSI, PL_GENCD);
		SetLIErrInt		(li.BLOOD, NullEins, li.NB_LI_PLAUSI, PL_BLOOD);
		SetLIErr		(li.BIOSIM, NullEins, li.NB_LI_PLAUSI, PL_BIOSIM);
		// PL_ATC

		// Sonderbehandlung notwendig, wenn nur MsgType 40 (ohne 10 vorher!) kommt:
		if ( update_cliart == 0 ) // für neue Einträge in cliart
		{
			if ( clio_exists == 0 ) // für Neuanlagen, alle Felder editierbar machen --> explicit treatment for all fields not delivered by msgtype 040 !!!
			{
				li.NB_LI_PLAUSI[ PL_CDSO1 ]		= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_NINCD ]		= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_COMPNO ]	= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_SUPPLNO ]	= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_ARTNO1 ]	= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_BC ]		= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_GTIN14 ]	= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_PHAR2 ]		= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_VDAT ]		= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_PRICE_PEXF ]= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_PRICE_PPUB ]= NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_MIGCD ]		= NB_PL_OK; 

				li.NB_LI_PLAUSI[ PL_PRDNO ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_SMCAT ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_SMNO  ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_CLINCD] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_VAT   ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_COOL  ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_CDBG  ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_BG    ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_EXP   ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_QTY   ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_NOPCS ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_DEPCD ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_OUTSAL] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_STTOX ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_CE    ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_SMCDAT] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_SIST  ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_ESIST ] = NB_PL_OK; 
				li.NB_LI_PLAUSI[ PL_BIOCID] = NB_PL_OK; 
				li.NB_LI_PLAUSI[PL_BAGDOSSIER]=NB_PL_OK; 
				li.NB_LI_PLAUSI[PL_SALECD]	= NB_PL_OK; 
				li.NB_LI_PLAUSI[PL_GRPCD]	= NB_PL_OK; 

				li.NB_LI_PLAUSI[PL_PICTOGRAM01_FLAG]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_PICTOGRAM02_FLAG]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_PICTOGRAM03_FLAG]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_PICTOGRAM04_FLAG]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_PICTOGRAM05_FLAG]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_PICTOGRAM06_FLAG]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_PICTOGRAM07_FLAG]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_PICTOGRAM08_FLAG]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_PICTOGRAM09_FLAG]	=	NB_PL_OK;

				li.NB_LI_PLAUSI[PL_GS_EXPLOSION]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_GS_HOCHENTZ]		=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_GS_LEICHTENTZ]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_GS_BRAND]		=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_GS_AETZEND]		=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_GS_SEHRGIFTIG]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_GS_GIFTIG]		=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_GS_GESUNDHSCH]	=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_GS_REIZEND]		=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_GS_UMWELT]		=	NB_PL_OK;

				li.NB_LI_PLAUSI[PL_SDS_DATE_DE]		=	NB_PL_OK;
				li.NB_LI_PLAUSI[PL_HAZARDSTATEMENT]	=	NB_PL_OK;

				li.NB_LI_PLAUSI[PL_FMD_FLAG] = NB_PL_OK;
				li.NB_LI_PLAUSI[PL_G_UN_NR] = NB_PL_OK;
				li.NB_LI_PLAUSI[PL_SDS_DATE_IT] = NB_PL_OK;
				li.NB_LI_PLAUSI[PL_SDS_DATE_EN] = NB_PL_OK;
				li.NB_LI_PLAUSI[PL_SDS_DATE_FR] = NB_PL_OK;
			}
			else
			{
				li.NB_LI_PLAUSI[ PL_CDSO1 ]		= NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_NINCD ]		= NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_COMPNO ]	= NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[ PL_SUPPLNO ]	= NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_ARTNO1 ]	= NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_BC ]		= NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_GTIN14 ]	= NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[ PL_PHAR2 ]		= NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_VDAT ]		= NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_PRICE_PEXF ]= NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_PRICE_PPUB ]= NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_MIGCD ]		= NB_PL_NO_VAL; 

				li.NB_LI_PLAUSI[ PL_PRDNO ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_SMCAT ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_SMNO  ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_CLINCD] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_VAT   ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_COOL  ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_CDBG  ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_BG    ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_EXP   ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_QTY   ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_NOPCS ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_DEPCD ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_OUTSAL] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_STTOX ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_CE    ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_SMCDAT] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_SIST  ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_ESIST ] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[ PL_BIOCID] = NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[PL_BAGDOSSIER]=NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_SALECD]	= NB_PL_NO_VAL; 
				li.NB_LI_PLAUSI[PL_GRPCD]	= NB_PL_NO_VAL; 

				li.NB_LI_PLAUSI[PL_PICTOGRAM01_FLAG]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_PICTOGRAM02_FLAG]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_PICTOGRAM03_FLAG]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_PICTOGRAM04_FLAG]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_PICTOGRAM05_FLAG]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_PICTOGRAM06_FLAG]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_PICTOGRAM07_FLAG]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_PICTOGRAM08_FLAG]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_PICTOGRAM09_FLAG]	=	NB_PL_NO_VAL;

				li.NB_LI_PLAUSI[PL_GS_EXPLOSION]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_GS_HOCHENTZ]		=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_GS_LEICHTENTZ]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_GS_BRAND]		=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_GS_AETZEND]		=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_GS_SEHRGIFTIG]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_GS_GIFTIG]		=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_GS_GESUNDHSCH]	=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_GS_REIZEND]		=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_GS_UMWELT]		=	NB_PL_NO_VAL;

				li.NB_LI_PLAUSI[PL_SDS_DATE_DE]		=	NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_HAZARDSTATEMENT]	=	NB_PL_NO_VAL;

				li.NB_LI_PLAUSI[PL_FMD_FLAG] = NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_G_UN_NR] = NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_SDS_DATE_IT] = NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_SDS_DATE_EN] = NB_PL_NO_VAL;
				li.NB_LI_PLAUSI[PL_SDS_DATE_FR] = NB_PL_NO_VAL;
			}
		}
	}
}

/* ------------------------------------------------------------------- */
static void FillLIStatus(struct CLIART *li )
{
	strcpy (li->LISTATUS,  LISTATUS_FREIGEG);

  /* unvollständige Datensätze -> Sperren */
	if ( *li->DSCRD == ' ' )
	{
		strcpy (li->LISTATUS,  LISTATUS_GESPERRT);
		if ( strcmp (li->ZAENDERUNG, ZAENDERUNG_NEU) == 0 )
			strcpy (li->ZAENDERUNG, ZAENDERUNG_NEU_UNVOLLST);
		else
			strcpy (li->ZAENDERUNG, ZAENDERUNG_AEND_UNVOLLST);
	}
		
  	if ( IsLIErr( li->NB_LI_PLAUSI ))
	{
		if (IsLIErr (li->NB_LI_ZWING))
		{
			if ( IsLIErr (li->NB_LI_NZWING))
				strcpy( li->NBSTATUS,  NBSTATUS_ZW_PL_NZW );
			else
				strcpy( li->NBSTATUS,  NBSTATUS_ZWING_PL );
		}
		else
		{
			if ( IsLIErr (li->NB_LI_NZWING))
				strcpy( li->NBSTATUS,  NBSTATUS_NZW_PL );
			else
				strcpy( li->NBSTATUS,  NBSTATUS_PLAUSI );
		}
	}
	else
	{
		if (IsLIErr (li->NB_LI_ZWING))
		{
			if ( IsLIErr (li->NB_LI_NZWING))
				strcpy( li->NBSTATUS,  NBSTATUS_ZWING_NZW );
			else
				strcpy( li->NBSTATUS,  NBSTATUS_ZWING );
		}
		else
		{
			if ( IsLIErr (li->NB_LI_NZWING))
				strcpy( li->NBSTATUS,  NBSTATUS_NZWING );
			else
				strcpy( li->NBSTATUS,  NBSTATUS_NO_ERR );
		}
	}
}

/* ------------------------------------------------------------------- */
static long findHNR(  long prtno, int isSearchForAWL )
{
    char sql[300];
    long status;
    long hnr;
	double dCount;

	if (prtno > 0)
	{
		sprintf( sql, "select (select count(*) from herstel where name = (select nams from clicompany where prtno = %ld)), "
							"hersteller_nr from herstel where name = (select nams from clicompany where prtno = %ld) ", 
						prtno, prtno );
	    
		status = SqlRead( sql, &dCount, &hnr, NULL );
	}
	else 
		status = 100;
    
	if ( status != 0 || dCount > 1.0 ) 
	{
		if (isSearchForAWL == 1)
			return 0;
		else 
			return -1;
	}
	else
	{
		if (isSearchForAWL == 0) 
			SetLITrueFalse( 0, li.NB_LI_ZWING, ZW_HNR_UNSET ); // reset zwing

		return hnr; // genau ein herstel gefunden
	}
}

/* ------------------------------------------------------------------- */
static int CheckLine(char *errmld)
{
	int sqlret;
	char artikel_name [L_ZARTIKEL_ARTIKEL_NAME + 1] = {0};
	char phyto[ L_ZARTIKEL_PHYTOPHARMAKON + 1] = {0};
	char homeo[ L_ZARTIKEL_HOMOEOPATHIKUM + 1] = {0};
	char anthro[ L_ZARTIKEL_ANTHROPOSOPHIKUM + 1] = {0};
	char tierarznei[ L_ZARTIKEL_TIERARZNEI + 1] = {0};
	char med[ L_ZARTIKEL_MEDIZINPRODUKT + 1] = {0};
	char impfst[ L_ZARTIKEL_IMPFSTOFF + 1] = {0};
	char chargenartikel[ L_ZARTIKEL_CHARGENARTIKEL + 1] = {0};
	long datum_ah, hnr, awl;
	double herst_proz;
		
	datum_ah = 0;
	
	sqlret = sel_zartikel(li.PHAR, &hnr, &awl, artikel_name, &datum_ah, 
						li.PREIS0ARTIKEL, li.ARTIKEL_GESPERRT, li.PRIVATSORTIMENT, li.VERFALL, 
						li.VERTRBIND_NUR_APO, li.VERTRBIND_INLAND, li.VERTRBIND_KANTONAL, li.VERTRBIND_KUENZLE, li.VERTRBIND_NUR_SPIT, 
						phyto, homeo, anthro, tierarznei, med, impfst, chargenartikel, &herst_proz, errmld);

#ifdef _DEBUG
	printf("CheckLine: select zartikel union zartswitzerland for %d returns %d\n", li.PHAR, sqlret);
#endif

	if (update_cliart == 0) // Hnr / Awl nur vor dem ersten Durchlauf überschreiben
	// if ( m_eFileArt == ARTICLE_ART ) 
	{
		if (sqlret == 100) // Neuanlage
		{
			li.HERSTELLER_NR = -1;
			li.AWL1 = 0;
			li.HERST_PROZENT = 0.0;
			
			strcpy(li.ARTIKEL_GESPERRT,		"0"); // wird abhängig von SALECD, GROSSO in CalcKZs belegt ...
			strcpy(li.PREIS0ARTIKEL,		"0");
			strcpy(li.PRIVATSORTIMENT,		"N");
			strcpy(li.VERFALL,				"1");
			strcpy(li.VERTRBIND_INLAND,		"0");
			strcpy(li.VERTRBIND_KANTONAL,	"0");
			strcpy(li.VERTRBIND_KUENZLE,	"0");
			strcpy(li.VERTRBIND_NUR_APO,	"0");
			strcpy(li.VERTRBIND_NUR_SPIT,	"0");
		}
		else
		{
			li.HERSTELLER_NR = hnr;
			li.AWL1 = awl;
			li.HERST_PROZENT = herst_proz;
		}
	}

	if ( !( sqlret == 0 || sqlret == 100 )) 
		return sqlret;

	// keine Neuanlage von Artikeln, die es bislang nur in clioart gibt und für die nur ein neuer ATC- Code über die ProduktNummer geliefert wird!
	if ( sqlret == 100 && update_cliart == 0 && (m_eFileArt == PRODUCT_PRD || m_eFileArt == PRODUCT_PRD_CPT))
		return 0;

	/* Mwst-Code an Artikelstamm anpassen! */
	if (m_eFileArt == ARTICLE_ART && li.VAT > 0)
		li.VAT = li.VAT - 1;

	// Errechnung PL_PRDGRPCD durch Vergleich zartikel - cliart (Besonderheit BLOOD) !!!
	if (sqlret			== 100						|| 
		phyto[0]		!= li.PHYTOPHARMAKON[0]		|| 
		homeo[0]		!= li.HOMOEOPATHIKUM[0]		|| 
		anthro[0]		!= li.ANTHROPOSOPHIKUM[0]	|| 
		tierarznei[0]	!= li.TIERARZNEI[0]			|| 
		med[0]			!= li.MEDIZINPRODUKT[0]		|| 
		impfst[0]		!= li.IMPFSTOFF[0] )
		li.NB_LI_PLAUSI[ PL_PRDGRPCD ]	= NB_PL_OK;
	else 
		li.NB_LI_PLAUSI[ PL_PRDGRPCD ]	= NB_PL_NO_VAL;

	if ((m_eFileArt == PRODUCT_PRD || m_eFileArt == PRODUCT_PRD_CPT) && atoi(chargenartikel) != li.BLOOD)
		li.NB_LI_PLAUSI[ PL_BLOOD ]	= NB_PL_OK;

	if ( sqlret == 0 )   /* Aenderung */
    {
		strcpy(li.ZAENDERUNG,ZAENDERUNG_AEND); /*Änderung*/
		
		if (update_cliart == 0)
		{
			art_aenderung++;

			sel_warengruppe(li.PHAR, "2", li.WGR_PHARMOS, errmld); 
			sel_warengruppe(li.PHAR, "5", li.WGR_SAISON,  errmld); 
			sel_warengruppe(li.PHAR, "A", li.WGR_SAISON2, errmld); 

			sel_zartpreis(li.PHAR, tages_datum, &li.LIEFERBASISPREIS, errmld); 
		}

		/* --- Plausibilitaetspruefung --- */
		FillLIPlausiErr( );

		if (m_eFileArt == ARTICLE_ARTCOMP)
		{
			if ( li.NB_LI_PLAUSI[ PL_SUPPLNO ] != NB_PL_NO_VAL )
			{
				// ermitteln AWL1, wenn nicht möglich --> auf 0 setzen
				if (li.SUPPLNO == li.COMPNO)
					li.AWL1 = 0;  // Änderung auf leeren Wert
				else
					li.AWL1 = findHNR(li.SUPPLNO, 1); // ermitteln AWL1
			}

			if ( li.NB_LI_PLAUSI[ PL_COMPNO ] != NB_PL_NO_VAL )
				// ermitteln HNR, wenn nicht möglich --> auf -1 setzen
				li.HERSTELLER_NR = findHNR(li.COMPNO, 0);// ermitteln HNR

			if (li.HERSTELLER_NR == li.AWL1)
				li.AWL1 = 0;
		}
	}
    else /* Neuanlage */
    {
        strcpy(li.ZAENDERUNG,ZAENDERUNG_NEU); /*Neuanlage*/

		if (m_eFileArt == ARTICLE_ARTCOMP)
		{
			if ( li.SUPPLNO != li.COMPNO ) 
				li.AWL1 = findHNR(li.SUPPLNO, 1); // ermitteln AWL1
			else
				li.AWL1 = 0;
			
			li.HERSTELLER_NR = findHNR(li.COMPNO, 0);// ermitteln HNR

			if (li.HERSTELLER_NR == li.AWL1)
				li.AWL1 = 0;
		}
		
		if (update_cliart == 0)
			art_neuanlage++;

		/* --- Plausibilitaetspruefung --- */
		FillLIPlausiErr( );
    }

	/* Datumgueltigab bei Neuanlage = heute */
	if ( strcmp(li.ZAENDERUNG, ZAENDERUNG_NEU ) == 0)
    {
		if ( li.VDAT >= tages_datum )
          li.VDAT = AddDayToPhoDate(tages_datum, 1); // im ZDP sind nur Preise änderbar mit Datum > heute !;
    }
	
	/* Automatismen */
	CalcKZs ( &li, errmld ); 
	
	/* Fehlerstrings setzen */
	SetNZwing ( &li, errmld );
	SetZwing ( &li, errmld );
		
	/* Statusfeld fuellen */
    FillLIStatus( &li );

	/* Schreiben cliart */
	if(	(datum_ah > 0 && datum_ah < AddDayToPhoDate(tages_datum, -730) ) ||
		(
			strcmp(li.ZAENDERUNG, ZAENDERUNG_NEU ) == 0 && 
			(
			/* SR-15061064: Neuaufnahmen auch für Artikel ohne IKS	
				(*li.SMCAT != 'A' && *li.SMCAT != 'B' && *li.SMCAT != 'C' && *li.SMCAT != 'D' && *li.SMCAT != 'E') || */
				li.OUTSAL != 0
			) 
		))
	{
		// in cliart nur schreiben, wenn zartikel.datum_ah nicht mehr als 2 Jahre in Vergangenheit
		// bei Artikel- Neuanlagen update / insert nur, wenn IKS-Code A-E oder OutSal = 0
		sqlret = 0;
	}
	else
	{
		if (update_cliart == 0)
			sqlret = ins_cliart( &Fd_Cliart, &li, errmld );
		else
			sqlret = upd_cliart( &Fd_Cliart, &li, errmld );
	}

	return sqlret;
}

/* ------------------------------------------------------------------- */
static long LoadCode(  const char* record, char *errmld )
{
	int ret = 0;

	//codeType = 1 --> cassortmentcode
	//codeType = 3 --> catccode
	char* value = "";
	long codeType = 0L;

	char code[20] = {0};
	char name[100] = {0};
	memset(code, '\0', 20);
	memset(name, '\0', 100);

	value = GetAtPosition(record, FILE_DELIMITER, CD_TYP, errmld);
	codeType = atoi(value);

	value = GetAtPosition(record, FILE_DELIMITER, CD_VAL, errmld);
	strcpy(code, value);

	value = GetAtPosition(record, FILE_DELIMITER, CD_DSCRD, errmld);
	strncpy(name, value, 99);
	
	if (codeType == 1)
	{
		ret = sel_cassortmentcode( &Fd_Cassortmentcode, code, &assortcode, errmld);
	}
	else if (codeType == 3)
	{
		ret = sel_catccode( &Fd_Catccode, code, &atccode, errmld);
	}

	if (ret == 100)
	{
		if (codeType == 1)
		{
			memset(&li,	0, sizeof(assortcode) );
			FdInitTabBuf( Fd_Cassortmentcode, &assortcode );

			strcpy(assortcode.CODE_ASSORTMENT, code);
			strcpy(assortcode.NAME_ASSORTMENT, name);
			ret = ins_cassortmentcode(&Fd_Cassortmentcode, &assortcode, errmld);
		}
		else if (codeType == 3)
		{
			memset(&li,	0, sizeof(atccode) );
			FdInitTabBuf( Fd_Catccode, &assortcode );

			strcpy(atccode.CODE_ATC, code);
			strcpy(atccode.NAME_ATC, name);
			ret = ins_catccode(&Fd_Catccode, &atccode, errmld);
		}
	}

	return ret;
}

/* ------------------------------------------------------------------- */
static long LoadCompany(const char* record, char *errmld)
{
	int retcode = 0;
	char* value = "";
	long prtno = 0L;

	value = GetAtPosition(record, FILE_DELIMITER, CP_PRTNO, errmld);
	prtno = atoi(value);

	retcode = sel_clicompany(&Fd_Clicompany, prtno, &licomp, errmld);

	if(0 == retcode)
	{
		value = GetAtPosition(record, FILE_DELIMITER, CP_NAMS, errmld);
		strcpy(licomp.NAMS, value);
		retcode = upd_clicompany(&Fd_Clicompany, &licomp, errmld);
	}
	else if(100 == retcode)
	{
		memset(&li,	0, sizeof(licomp));
		FdInitTabBuf(Fd_Clicompany, &licomp);

		licomp.PRTNO = prtno;
		value = GetAtPosition(record, FILE_DELIMITER, CP_NAMS, errmld);
		strcpy(licomp.NAMS, value);

		retcode = ins_clicompany(&Fd_Clicompany, &licomp, errmld);
	}

	return retcode;
}

/* ------------------------------------------------------------------- */
static long LoadProduct(const char* record, char *errmld)
{
	int retcode = 0;
	char* value = "";
	long prdno = 0L;

	value = GetAtPosition(record, FILE_DELIMITER, PRD_PRDNO, errmld);
	prdno = atoi(value);

	retcode = sel_cliproduct(&Fd_Cliproduct, prdno, &liprod, errmld);

	if(100 == retcode)
	{
		memset(&liprod,	0, sizeof(liprod));
		FdInitTabBuf(Fd_Cliproduct, &liprod);
	}

	value = GetAtPosition(record, FILE_DELIMITER, PRD_GENCD, errmld);
	strcpy(liprod.GENCD, value);

	if (strstr(" GO", value) != NULL) {
		strcpy(liprod.GENCD, value);
	}
	else {
		strcpy(liprod.GENCD, "");
	}
	if (strcmp(value, "S") == 0) {
		strcpy(liprod.BIOSIM, "1");
	}

	value = GetAtPosition(record, FILE_DELIMITER, PRD_ATC, errmld);
	strcpy(liprod.ATC, value);

	value = GetAtPosition(record, FILE_DELIMITER, PRD_BLOOD, errmld);
	liprod.BLOOD = atoi(value);

	value = GetAtPosition(record, FILE_DELIMITER, PRD_BIOSIM, errmld);
	if (strcmp(value, "S") == 0) {
		strcpy(liprod.BIOSIM, "1");
	}
	else {
		strcpy(liprod.BIOSIM, "0");
	}

	/* MDATTR */
	value = GetAtPosition(record, FILE_DELIMITER, PRD_MDATTR, errmld);

	if (0 == strcmp("IMPLANTABLE", value))
	{
		liprod.SERIAL_NUMBER_TRACKING = 1;
	}
	else 
	{
		liprod.SERIAL_NUMBER_TRACKING = 0;
	}

	if(0 == retcode)
	{
		retcode = upd_cliproduct(&Fd_Cliproduct, &liprod, errmld);
	}
	else if(100 == retcode)
	{
		liprod.PRDNO = prdno;
		retcode = ins_cliproduct(&Fd_Cliproduct, &liprod, errmld);
	}

	return retcode;
}

/* ------------------------------------------------------------------- */
static long LoadProductGrp(const char* record, char *errmld)
{
	int retcode = 0;
	char* value = "";
	long prdno = 0L;

	value = GetAtPosition(record, FILE_DELIMITER, PRDGRP_PRDNO, errmld);
	prdno = atoi(value);

	value = GetAtPosition(record, FILE_DELIMITER, PRDGRP_PRDGRPCD, errmld);

	retcode = sel_cliproductgrp(&Fd_Cliproductgrp, prdno, value, &liprodgrp, errmld);

	if(100 == retcode)
	{
		memset(&liprodgrp,	0, sizeof(liprodgrp));
		FdInitTabBuf(Fd_Cliproductgrp, &liprodgrp);
	
		liprodgrp.PRDNO = prdno;
		strcpy(liprodgrp.PRDGRPCD, value);
		retcode = ins_cliproductgrp(&Fd_Cliproductgrp, &liprodgrp, errmld);
	}

	return retcode;
}

static int ProcessHazardStatements(long phar,  char* errmld)
{
	// do process hazard notes for phar#
	int retcode = 0;
	long count = 0;
	int i = 0;
	long exists = 0;
	int differentHazardStatements = 0;
	static struct CLIART liPrevious;

	sel_count_cliohsatz(phar, &count, errmld);

	if(count != hazardStatementsCounter)
	{
		del_all_cliohsatz(&Fd_Cliohsatz, phar, errmld);
		retcode = WriteAllCliohsatzToDb(errmld);
		differentHazardStatements = 1;
	}
	else
	{
		for(i = 0; i < hazardStatementsCounter; i++)
		{
			exists_cliohsatz(lihsaetze[i].PHAR, lihsaetze[i].HAZARDNOTEID, &exists, errmld);

			if(exists == 0)
			{
				del_all_cliohsatz(&Fd_Cliohsatz, phar, errmld);
				retcode = WriteAllCliohsatzToDb(errmld);
				differentHazardStatements = 1;
				break;
			}
		}
	}

	if(1 == differentHazardStatements)
	{
		memset(&liPrevious, 0 ,sizeof(liPrevious));
		if(sel_cliart(&Fd_Cliart, phar, lidatumnr, &liPrevious, errmld) == 0)
		{
			if(notExistingHazardnotes == 0) // all hazardnotes fit to master data
			{
				liPrevious.NB_LI_PLAUSI[PL_HAZARDSTATEMENT] = NB_PL_OK;
			}
			else
			{
				liPrevious.NB_LI_PLAUSI[PL_HAZARDSTATEMENT] = NB_PL_ERR;
			}

			// set a flag to document different hazard notes
			liPrevious.NB_LI_NZWING[NZ_CHANGE_HAZARDNOTES] = NB_PL_ERR;

			FillLIStatus( &liPrevious);

			upd_cliart(&Fd_Cliart, &liPrevious, errmld);
		}
	}

	return retcode;
}


static void GetSubDanArtFromCliart(const struct CLIART* cliart, struct SUBARTDAN* cliSubArtDan)
{
	cliSubArtDan->PHAR = cliart->PHAR;

	cliSubArtDan->PICTOGRAM01_FLAG = cliart->PICTOGRAM01_FLAG;
	cliSubArtDan->PICTOGRAM02_FLAG = cliart->PICTOGRAM02_FLAG;
	cliSubArtDan->PICTOGRAM03_FLAG = cliart->PICTOGRAM03_FLAG;
	cliSubArtDan->PICTOGRAM04_FLAG = cliart->PICTOGRAM04_FLAG;
	cliSubArtDan->PICTOGRAM05_FLAG = cliart->PICTOGRAM05_FLAG;
	cliSubArtDan->PICTOGRAM06_FLAG = cliart->PICTOGRAM06_FLAG;
	cliSubArtDan->PICTOGRAM07_FLAG = cliart->PICTOGRAM07_FLAG;
	cliSubArtDan->PICTOGRAM08_FLAG = cliart->PICTOGRAM08_FLAG;
	cliSubArtDan->PICTOGRAM09_FLAG = cliart->PICTOGRAM09_FLAG;

	strcpy(cliSubArtDan->GS_EXPLOSION, cliart->GS_EXPLOSION);
	strcpy(cliSubArtDan->GS_HOCHENTZ, cliart->GS_HOCHENTZ);
	strcpy(cliSubArtDan->GS_LEICHTENTZ, cliart->GS_LEICHTENTZ);
	strcpy(cliSubArtDan->GS_BRAND, cliart->GS_BRAND);
	strcpy(cliSubArtDan->GS_AETZEND, cliart->GS_AETZEND);
	strcpy(cliSubArtDan->GS_SEHRGIFTIG, cliart->GS_SEHRGIFTIG);
	strcpy(cliSubArtDan->GS_GIFTIG, cliart->GS_GIFTIG);
	strcpy(cliSubArtDan->GS_GESUNDHSCH, cliart->GS_GESUNDHSCH);
	strcpy(cliSubArtDan->GS_REIZEND, cliart->GS_REIZEND);
	strcpy(cliSubArtDan->GS_UMWELT, cliart->GS_UMWELT);

	//cliSubArtDan->SDS_DATE_DE = cliart->SDS_DATE_DE;
}

static void SetSubDanArtToClioart(struct CLIOART* clioart, const struct SUBARTDAN* cliSubArtDan)
{
	clioart->PHAR = cliSubArtDan->PHAR;

	clioart->PICTOGRAM01_FLAG = cliSubArtDan->PICTOGRAM01_FLAG;
	clioart->PICTOGRAM02_FLAG = cliSubArtDan->PICTOGRAM02_FLAG;
	clioart->PICTOGRAM03_FLAG = cliSubArtDan->PICTOGRAM03_FLAG;
	clioart->PICTOGRAM04_FLAG = cliSubArtDan->PICTOGRAM04_FLAG;
	clioart->PICTOGRAM05_FLAG = cliSubArtDan->PICTOGRAM05_FLAG;
	clioart->PICTOGRAM06_FLAG = cliSubArtDan->PICTOGRAM06_FLAG;
	clioart->PICTOGRAM07_FLAG = cliSubArtDan->PICTOGRAM07_FLAG;
	clioart->PICTOGRAM08_FLAG = cliSubArtDan->PICTOGRAM08_FLAG;
	clioart->PICTOGRAM09_FLAG = cliSubArtDan->PICTOGRAM09_FLAG;

	strcpy(clioart->GS_EXPLOSION, cliSubArtDan->GS_EXPLOSION);
	strcpy(clioart->GS_HOCHENTZ, cliSubArtDan->GS_HOCHENTZ);
	strcpy(clioart->GS_LEICHTENTZ, cliSubArtDan->GS_LEICHTENTZ);
	strcpy(clioart->GS_BRAND, cliSubArtDan->GS_BRAND);
	strcpy(clioart->GS_AETZEND, cliSubArtDan->GS_AETZEND);
	strcpy(clioart->GS_SEHRGIFTIG, cliSubArtDan->GS_SEHRGIFTIG);
	strcpy(clioart->GS_GIFTIG, cliSubArtDan->GS_GIFTIG);
	strcpy(clioart->GS_GESUNDHSCH, cliSubArtDan->GS_GESUNDHSCH);
	strcpy(clioart->GS_REIZEND, cliSubArtDan->GS_REIZEND);
	strcpy(clioart->GS_UMWELT, cliSubArtDan->GS_UMWELT);

	//clioart->SDS_DATE_DE = cliSubArtDan->SDS_DATE_DE;
}

static void GetSubArtCompFromCliart(const struct CLIART* cliart, struct SUBARTCOMP* cliSubArtComp)
{
	cliSubArtComp->PHAR = cliart->PHAR;

	cliSubArtComp->COMPNO = cliart->COMPNO;
	cliSubArtComp->SUPPLNO = cliart->SUPPLNO;

	strcpy(cliSubArtComp->ARTNO1, cliart->ARTNO1);
}

static void SetSubArtCompToClioart(struct CLIOART* clioart, const struct SUBARTCOMP* cliSubArtComp)
{
	clioart->PHAR = cliSubArtComp->PHAR;

	clioart->COMPNO = cliSubArtComp->COMPNO;
	clioart->SUPPLNO = cliSubArtComp->SUPPLNO;

	strcpy(clioart->ARTNO1, cliSubArtComp->ARTNO1);
}

static void SetPlausiForLongValue(long orgValue, long liValue, long existsClioart, int position, struct CLIART* cliart)
{
	if(orgValue == liValue && (existsClioart == 1 || liValue != 0))
	{
		cliart->NB_LI_PLAUSI[position] = NB_PL_NO_VAL;
	}
	else
	{
		cliart->NB_LI_PLAUSI[position] = NB_PL_OK;
	}
}

static void SetPlausiForCharValue(const char* orgValue, const char* liValue, long existsClioart, int position, struct CLIART* cliart)
{
	if(strcmp(liValue, orgValue) == 0 && (existsClioart == 1 || strcmp(liValue, "") != 0))
	{
		cliart->NB_LI_PLAUSI[position] = NB_PL_NO_VAL;
	}
	else
	{
		cliart->NB_LI_PLAUSI[position] = NB_PL_OK;
	}
}


static int ProcessDanArt(const struct SUBARTDAN* orgSubArtDan, const long linr, const long existsClioart, char* errmld)
{
	// do process danger codes for article
	int retcode = 0;
	struct SUBARTDAN cliSubArtDan;
	struct CLIART cliart;
	struct CLIOART clioart;

	if(sel_cliart(&Fd_Cliart, orgSubArtDan->PHAR, linr, &cliart, errmld) == 0)
	{
		memset(&cliSubArtDan, 0 ,sizeof(cliSubArtDan));
		GetSubDanArtFromCliart(&cliart, &cliSubArtDan);

		SetPlausiForLongValue(orgSubArtDan->PICTOGRAM01_FLAG, cliSubArtDan.PICTOGRAM01_FLAG, existsClioart, PL_PICTOGRAM01_FLAG, &cliart);
		SetPlausiForLongValue(orgSubArtDan->PICTOGRAM02_FLAG, cliSubArtDan.PICTOGRAM02_FLAG, existsClioart, PL_PICTOGRAM02_FLAG, &cliart);
		SetPlausiForLongValue(orgSubArtDan->PICTOGRAM03_FLAG, cliSubArtDan.PICTOGRAM03_FLAG, existsClioart, PL_PICTOGRAM03_FLAG, &cliart);
		SetPlausiForLongValue(orgSubArtDan->PICTOGRAM04_FLAG, cliSubArtDan.PICTOGRAM04_FLAG, existsClioart, PL_PICTOGRAM04_FLAG, &cliart);
		SetPlausiForLongValue(orgSubArtDan->PICTOGRAM05_FLAG, cliSubArtDan.PICTOGRAM05_FLAG, existsClioart, PL_PICTOGRAM05_FLAG, &cliart);
		SetPlausiForLongValue(orgSubArtDan->PICTOGRAM06_FLAG, cliSubArtDan.PICTOGRAM06_FLAG, existsClioart, PL_PICTOGRAM06_FLAG, &cliart);
		SetPlausiForLongValue(orgSubArtDan->PICTOGRAM07_FLAG, cliSubArtDan.PICTOGRAM07_FLAG, existsClioart, PL_PICTOGRAM07_FLAG, &cliart);
		SetPlausiForLongValue(orgSubArtDan->PICTOGRAM08_FLAG, cliSubArtDan.PICTOGRAM08_FLAG, existsClioart, PL_PICTOGRAM08_FLAG, &cliart);
		SetPlausiForLongValue(orgSubArtDan->PICTOGRAM09_FLAG, cliSubArtDan.PICTOGRAM09_FLAG, existsClioart, PL_PICTOGRAM09_FLAG, &cliart);

		SetPlausiForCharValue(orgSubArtDan->GS_EXPLOSION, cliSubArtDan.GS_EXPLOSION, existsClioart, PL_GS_EXPLOSION, &cliart);
		SetPlausiForCharValue(orgSubArtDan->GS_HOCHENTZ, cliSubArtDan.GS_HOCHENTZ, existsClioart, PL_GS_HOCHENTZ, &cliart);
		SetPlausiForCharValue(orgSubArtDan->GS_LEICHTENTZ, cliSubArtDan.GS_LEICHTENTZ, existsClioart, PL_GS_LEICHTENTZ, &cliart);
		SetPlausiForCharValue(orgSubArtDan->GS_BRAND, cliSubArtDan.GS_BRAND, existsClioart, PL_GS_BRAND, &cliart);
		SetPlausiForCharValue(orgSubArtDan->GS_AETZEND, cliSubArtDan.GS_AETZEND, existsClioart, PL_GS_AETZEND, &cliart);
		SetPlausiForCharValue(orgSubArtDan->GS_SEHRGIFTIG, cliSubArtDan.GS_SEHRGIFTIG, existsClioart, PL_GS_SEHRGIFTIG, &cliart);
		SetPlausiForCharValue(orgSubArtDan->GS_GIFTIG, cliSubArtDan.GS_GIFTIG, existsClioart, PL_GS_GIFTIG, &cliart);
		SetPlausiForCharValue(orgSubArtDan->GS_GESUNDHSCH, cliSubArtDan.GS_GESUNDHSCH, existsClioart, PL_GS_GESUNDHSCH, &cliart);
		SetPlausiForCharValue(orgSubArtDan->GS_REIZEND, cliSubArtDan.GS_REIZEND, existsClioart, PL_GS_REIZEND, &cliart);
		SetPlausiForCharValue(orgSubArtDan->GS_UMWELT, cliSubArtDan.GS_UMWELT, existsClioart, PL_GS_UMWELT, &cliart);

		//SetPlausiForLongValue(orgSubArtDan->SDS_DATE_DE, cliSubArtDan.SDS_DATE_DE, existsClioart, PL_SDS_DATE_DE, &cliart);

		// plausi update
		upd_cliart(&Fd_Cliart, &cliart, errmld);


		if(sel_clioart(&Fd_Clioart, cliSubArtDan.PHAR, &clioart, errmld) == 0)
		{
			SetSubDanArtToClioart(&clioart, &cliSubArtDan);
			upd_clioart(&Fd_Clioart, &clioart, errmld);
		}
	}

	return retcode;
}

static int ProcessArtComp(const struct SUBARTCOMP* orgSubArtComp, const long linr, const long existsClioart, char* errmld)
{
	// do process danger codes for article
	int retcode = 0;
	struct SUBARTCOMP cliSubArtComp;
	struct CLIART cliart;
	struct CLIOART clioart;

	if(sel_cliart(&Fd_Cliart, orgSubArtComp->PHAR, linr, &cliart, errmld) == 0)
	{
		memset(&cliSubArtComp, 0 , sizeof(cliSubArtComp));
		GetSubArtCompFromCliart(&cliart, &cliSubArtComp);

		SetPlausiForLongValue(orgSubArtComp->COMPNO, cliSubArtComp.COMPNO, existsClioart, PL_COMPNO, &cliart);
		SetPlausiForLongValue(orgSubArtComp->SUPPLNO, cliSubArtComp.SUPPLNO, existsClioart, PL_SUPPLNO, &cliart);

		SetPlausiForCharValue(orgSubArtComp->ARTNO1, cliSubArtComp.ARTNO1, existsClioart, PL_ARTNO1, &cliart);

		// plausi update
		upd_cliart(&Fd_Cliart, &cliart, errmld);

		if(sel_clioart(&Fd_Clioart, cliSubArtComp.PHAR, &clioart, errmld) == 0)
		{
			SetSubArtCompToClioart(&clioart, &cliSubArtComp);
			upd_clioart(&Fd_Clioart, &clioart, errmld);
		}
	}

	return retcode;
}


static char* GetKeyFromRecord(const char* record, char* errmld)
{
	char* result = NULL;

	result = GetAtPosition(record, FILE_DELIMITER, 1, errmld);

	return result;
}

static EMsgType GetMessageTypeFromRecord(const char* record, char* errmld)
{
	EMsgType result = UNKNOWN;
	char* msgType;

	// record is too short to contain valid information
	if(strlen(record) < 5)
	{
		return result;
	}

	msgType = GetAtPosition(record, FILE_DELIMITER, 0, errmld);
	if(strcmp(msgType, MSGTYPE_ART) == 0)
		result = ARTICLE_ART;
	else if(strcmp(msgType, MSGTYPE_ARTCOMP) == 0)
		result = ARTICLE_ARTCOMP;
	else if (strcmp(msgType, MSGTYPE_ARTBAR) == 0)
		result = ARTICLE_ARTBAR;
	else if (strcmp(msgType, MSGTYPE_ARTCH) == 0)
		result = ARTICLE_ARTCH;
	else if (strcmp(msgType, MSGTYPE_ARTPRI) == 0)
		result = ARTICLE_ARTPRI;
	else if (strcmp(msgType, MSGTYPE_ARTPRI_NEW) == 0)
		result = ARTICLE_ARTPRI_NEW;
	else if (strcmp(msgType, MSGTYPE_ARTMIG) == 0)
		result = ARTICLE_ARTMIG;
	else if (strcmp(msgType, MSGTYPE_ARTDAN) == 0)
		result = ARTICLE_ARTDAN;
	else if (strcmp(msgType, MSGTYPE_ARTINS) == 0)
		result = ARTICLE_ARTINS;
	else if (strcmp(msgType, MSGTYPE_SDS) == 0)
		result = ARTICLE_SDS;
	else if (strcmp(msgType, MSGTYPE_PRD) == 0)
		result = PRODUCT_PRD;
	else if (strcmp(msgType, MSGTYPE_PRD_CPT) == 0)
		result = PRODUCT_PRD_CPT;
	else if (strcmp(msgType, MSGTYPE_COMPANY) == 0)
		result = COMPANY;
	else if (strcmp(msgType, MSGTYPE_CODE) == 0)
		result = CODE;
	else if (strcmp(msgType, MSGTYPE_ARTSL) == 0)
		result = ARTICLE_ARTSL;
	else if (strcmp(msgType, MSGTYPE_ARTADR) == 0)
		result = ARTICLE_ARTADR;
	else if (strcmp(msgType, MSGTYPE_REGULATIONS) == 0)
		result = ARTICLE_REGULATIONS;
	return result;
}

/* ------------------------------------------------------------------- */
static int LILieferung( char *errmld )
{
	int status;
	int ret;
	int loopFetchArticlesByPrdNo;
	long phar;
	long pharPrevious;
	char zeile[NO_SIGNS + 1] = {0};
	char* key;
	long lKey = 0L;
	struct SUBARTDAN subartdan_org;
	struct SUBARTCOMP subartcomp_org;
	long existsClioart;


	phar				= 0;
	pharPrevious		= 0;
	status				= 0;
	linenr_overread		= 0;
	linenr_processed	= 0;
	linenr_invalid		= 0;
	loopFetchArticlesByPrdNo = 0;
	existsClioart = 0L;
	
	while ( status == 0 )/*SCHLEIFE zum Lesen aller Datenzeilen aus logindex.csv*/
	{
		if (loopFetchArticlesByPrdNo != 1)
		{
			// nächste Zeile aus Datei lesen + anschließend verarbeiten (nur nicht, falls es zu einer PrdNo mehrere betroffene PZN´s gibt)
			memset(zeile, '\0', NO_SIGNS);
			status = GetLiZeile( fd_file, zeile );
		}
		
		if (status == 0)
		{

#ifdef _DEBUG
			printf("%s\n", zeile);
#endif

			// set global art
			m_eFileArt = GetMessageTypeFromRecord(zeile, errmld);
			if(UNKNOWN == m_eFileArt)
			{
				linenr_overread++;
#ifdef _DEBUG
				printf("LILieferung: unknown record type (Satzart) %d - ignored\n", m_eFileArt);
#endif
				continue;
			}

			// set local key
			key = GetKeyFromRecord(zeile, errmld);
			if(key != NULL)
			{
				lKey = atoi(key);
			}
			else
			{
				linenr_overread++;
#ifdef _DEBUG
				printf("LILieferung: no PHAR key found in record - ignored\n");
#endif
				continue;
			}
			// hier abspalten für Companies
			if (m_eFileArt == COMPANY)
			{
				if(LoadCompany(zeile, errmld) == 0)
					linenr_processed++;
				else
				{
#ifdef _DEBUG
					printf("LILieferung: company data invalid - ignored\n");
#endif
					linenr_invalid++;
				}
				continue;
			}
			else if (m_eFileArt == CODE)
			{
				if (LoadCode(zeile, errmld) == 0)
					linenr_processed++;
				else
				{
#ifdef _DEBUG
					printf("LILieferung: code data invalid - ignored\n");
#endif
					linenr_invalid++;
				}
				continue;
			}
			else if (m_eFileArt == ARTICLE_REGULATIONS)
			{
				char * value = GetAtPosition(zeile, FILE_DELIMITER, REGU_REGULATION, errmld);
				if (strcmp(value, "SALE.FMD.SMVO") != 0)
				{
					linenr_processed++;
#ifdef _DEBUG
					printf("LILieferung: ARTICLE_REGULATIONS value '%s' found - no processing neccessary - record ignored\n", value);
#endif
					continue;
				}			
			}			

			else if (m_eFileArt == PRODUCT_PRD || m_eFileArt == PRODUCT_PRD_CPT) // Spezialbehandlung für Produkte --> zunächst alle zugehörigen PZN`s suchen und diese dann alle in cliart einstellen!
			{
				if (loopFetchArticlesByPrdNo != 1)
				{
					// vorab cliproduct / cliproductgrp befüllen
					if (m_eFileArt == PRODUCT_PRD)
					{
						LoadProduct(zeile, errmld);
						
						// für jeden PRD- Kopf alle cliproductgrp´s löschen - werden anschließend wieder geladen!
						del_cliproductgrp(&Fd_Cliproductgrp, lKey, errmld); // erst nach read_clioart_into_cliartBuf !!!
					}	
					else // m_eFileArt == PRODUCT_PRD_CPT
					{
						LoadProductGrp(zeile, errmld);
					}
				
					ret = sel_phar(lKey, errmld); // lesen clioart via PRDNO (spPzn)
					
					if (ret == 0)
						loopFetchArticlesByPrdNo = 1;
				}

				if (loopFetchArticlesByPrdNo == 1)
					ret = fetch_next(&phar, errmld);  // Schleife, da es zu einer prdno mehrere phar geben kann!
				
				if (ret == 100) // prdno nicht bekannt = nicht laden
				{
					loopFetchArticlesByPrdNo = 0;
#ifdef _DEBUG
					printf("LILieferung: Product for artikel %d unknown - record ignored\n",phar);
#endif
					continue;
				}
				else if (ret != 0)
					return ret;
			}
			else
			{
				phar = lKey;
			}					

			if(ARTICLE_ART == m_eFileArt)
			{
				// delete existing db-clihasatz-records if first time reading article-records
				if(0 == hazardStatementsCounter)
				{
					del_all_clihsatz(&Fd_Clihsatz, phar, lidatumnr, errmld);
				}

				if(0 == pharPrevious)
				{
					pharPrevious = phar;
				}
				else if(pharPrevious != phar)
				{
					ProcessHazardStatements(pharPrevious, errmld);
					ProcessDanArt(&subartdan_org, lidatumnr, existsClioart, errmld);
					ProcessArtComp(&subartcomp_org, lidatumnr, existsClioart, errmld);
					pharPrevious = phar;
				}

				// reset h-saetze array if 010 msgtype
				memset(&lihsaetze, 0, sizeof lihsaetze);
				hazardStatementsCounter = 0;
				notExistingHazardnotes = 0;
				// reset for EUH
				memset(m_szEUHazard, 0x00, sizeof(m_szEUHazard));
				strcpy(m_szEUHazard, "INIT");

				// reset and read original ART_DAN fields
				memset(&subartdan_org,0,sizeof(subartdan_org));
				subartdan_org.PHAR = phar;
				read_clio_subartdan(&subartdan_org, errmld);

				// reset and read original ART_COMP fields
				memset(&subartcomp_org, 0 , sizeof(subartcomp_org));
				subartcomp_org.PHAR = phar;
				read_clio_subartcomp(&subartcomp_org, errmld);

				exists_cliosatz(phar, &existsClioart, errmld);
			}

			// lesen cliart via PHAR + LINR
			ret = sel_cliart(&Fd_Cliart, phar, lidatumnr, &li, errmld);

#ifdef _DEBUG
			printf("LILieferung: select from CLIART for article=%d and linr=%d returns %d\n", phar, lidatumnr, ret);
#endif

			if ( ret == 100 ) /* neue PZN in dieser logindex- lieferung */
			{
				long prdno;
				int rc;
				char prdgrpcd[L_CLIPRODUCTGRP_PRDGRPCD + 1] = {0};

				// initialisieren der Buffer
				memset(&lio,0,sizeof(lio));
				memset(&li,	0,sizeof(li) );
				FdInitTabBuf( Fd_Cliart, &li );
				InitializeNBStr();
				update_cliart = 0;

				satznr++;
                li.SATZNR = satznr;
				li.PHAR = phar;
				li.LINR = lidatumnr;

				if (m_eFileArt == ARTICLE_ART)
					prdno = atoi(GetAtPosition(zeile, FILE_DELIMITER, ART_PRDNO, errmld));
				else // m_eFileArt == PRODUCT_PRD
					prdno = lKey;

				// clioart lesen + falls vorhanden, copy clioart to cliart !!!
				if ( 100 == read_clioart_into_cliartBuf(&li, errmld) && (m_eFileArt == ARTICLE_ART || m_eFileArt == ARTICLE_ARTPRI_NEW) )
				{
					// wenn Artikel- Neuanlage und clioart nicht vorhanden, dann hier auch cliproduct lesen und in cliart übernehmen
					read_cliproduct_into_cliartBuf(&li, prdno, errmld);
				}

				// hier immer auch alle cliproductgrp.prdgrpcd´s lesen (da nicht in clioart!) und nach cliart (tierarznei, phytopharmakon, ...) umrechnen
				rc = sel_productgrp(prdno, errmld); // lesen cliproductgrp via PRDNO 

				resetPrdGrpCdFlags(&li);
					
				while (rc == 0)
				{
					rc = fetch_next_productgrp(prdgrpcd, errmld);  // Schleife, da es zu einer prdno mehrere prdgrpcd´s geben kann!

					if (rc == 0)
						SetPrdGrpCd(&li, prdgrpcd);
				}
			}
			else if (ret == 0)/* PZN in dieser logindex- lieferung bereits vorhanden */
			{
				update_cliart = 1;

				if (m_eFileArt == PRODUCT_PRD)
					resetPrdGrpCdFlags(&li);// zurücksetzen aller cliart- Kennzeichen, die letztmalig aus cliproductgrp errechnet wurden - werden anschließend über MsgType 41 ggfs. wieder gesetzt
			}
			else
				return ret;

			ret = ConvertRecordToCliart(&li, zeile, errmld);
			// ret: 0= alles ok; 1/2= Fehler; 3= Zeile nicht laden;

			if (ret == 3)
			{
				continue;
			}
			else if (ret == 0)
			{
				if(li.PHAR <= 0 || li.PHAR > 9999999)
				{
					linenr_invalid++;
				}

				if(LoadCLIOART(errmld) == 0) // clioart in Buffer einlesen, anschließend Werte aus cliart übernehmen
				{						
					/* kopieren von lio nach li */
					CopyPlausi(li.NB_LI_PLAUSI);
						
					if (CheckLine(errmld) == 0) // weitere Felder belegen, Fehler setzen
					{
						linenr_processed++; // Insert o. Update cliart / clioart passiert in Checkline
						continue;
					}
				}
				else
				{
					linenr_invalid++;
				}
			}
		}
	}

	if (status != 2)
	{
		strcpy(errmld, "Error on reading logindex.csv; file not read to the end!");
	}
	else
	{
		// process hazard statements for last phar.
		ProcessHazardStatements(pharPrevious, errmld);
		ProcessDanArt(&subartdan_org, lidatumnr, existsClioart, errmld);
		ProcessArtComp(&subartcomp_org, lidatumnr, existsClioart, errmld);

		/*EOF*/
		printf( "logindex.csv read to the end.\nDeleting of not relevant changes ...\n" );

		// Sätze ohne relevante Änderungen löschen.
		status = SqlExecuteImm("DELETE FROM cliart "
								"WHERE nb_li_plausi = '0999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999' "
								"and listatus = 'F' and nbstatus = '0' and zaenderung = '1' " );

		status = SqlExecuteImm(	"DELETE FROM clihsatz "
								"WHERE clihsatz.linr IN "
								"(SELECT DISTINCT h.linr FROM clihsatz h LEFT OUTER JOIN cliart a ON (h.linr = a.linr AND h.phar = a.phar) WHERE a.phar IS NULL) "
								"AND clihsatz.phar IN "
								"(SELECT DISTINCT h.phar FROM clihsatz h LEFT OUTER JOIN cliart a ON (h.linr = a.linr AND h.phar = a.phar) WHERE a.phar IS NULL) ");

		// LI H-Sätze löschen, welche zu "zulöschenden" cliart Sätzen zugeordnet sind
		if (status == 100)
			status = 0;
	}
	
   CloseLiDatei( fd_file );
   fd_file = NULL;
  
   return status;
}

/* ------------------------------------------------------------------- */
static long test_linr(  long lidatum, char *errmld )
{
    char sql[50];
    long status;
    long nr;

    sprintf( sql, "select LINR from CLIART where LINR=%d",
                  (int)lidatum );

    status = SqlRead( sql, &nr, NULL );
    
	if ( status == 100 ) 
		return 0;

    if ( status == 0 )
       strcpy( errmld, "LOGINDEX-Datei bereits eingelesen" );
    else
    {
       strcpy( errmld, "cliart: " );
       strcat( errmld, DynErrmld() );
    }
    return -1;
}

/* ------------------------------------------------------------------- */
static long GenArtikel( char *db, char* ili_file, char *errmld )
{
	int status;
	char zeile[NO_SIGNS + 1];
	char dat[8];
	   	
	tages_datum = GetPhoDate();
	   
	fd_file = NULL;
	
	/*öffnen des LogIndex-Files*/
	status = OpenLiDatei( &fd_file, ili_file, errmld );
	if ( status != 0 )
	{
		sprintf(errmld, "logindex-file not found under path %s\n", ili_file);
		return status;
	}
   
    if ( OpenBase( db, errmld ) == 0 )
    {
        OpenPflege( (char*)user, errmld );
	
		/*Kopfzeile aus Li-File lesen*/
		status = GetLiZeile( fd_file, zeile ); /*Kopfzeile enthält nur das Datum der Datenlieferung*/
		if ( status != 0 )
		{
			strcpy(errmld, "no data in logindex-file\n");
			return status;
		}
		
		strncpy(dat, &zeile[DATPOS], 8);
		lidatumnr = atol( dat );
		
		if ( test_linr( lidatumnr, errmld ) == 0 )
        {
			Fd_Clioart	= -1;
			Fd_Cliart	= -1;
			Fd_Clicompany = -1;
			Fd_Cliohsatz = -1;
			Fd_Clihsatz = -1;
			Fd_Cassortmentcode = -1;
			Fd_Catccode = -1;
			Fd_Cliproduct = -1;
			Fd_Cliproductgrp = -1;

			if ( OpenBufferDesc( &Fd_Clioart, "clioart", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 && 
				 OpenBufferDesc( &Fd_Clicompany, "clicompany", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 && 
				 OpenBufferDesc( &Fd_Cliohsatz,  "cliohsatz",  NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 &&
				 OpenBufferDesc( &Fd_Clihsatz,  "clihsatz",  NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 &&
				 OpenBufferDesc( &Fd_Cliart,  "cliart",  NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 &&
				 OpenBufferDesc( &Fd_Cassortmentcode,  "cassortmentcode",  NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 &&
				 OpenBufferDesc( &Fd_Catccode,  "catccode",  NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 &&
				 OpenBufferDesc( &Fd_Cliproductgrp,  "cliproductgrp",  NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 &&
				 OpenBufferDesc( &Fd_Cliproduct,  "cliproduct",  NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0)
			{
				status = LILieferung ( errmld );
			}
			else
			{
				status = 1;
			}

			CloseOneBufferDesc(Fd_Clioart);
			CloseOneBufferDesc(Fd_Cliart);
			CloseOneBufferDesc(Fd_Clicompany);
			CloseOneBufferDesc(Fd_Cassortmentcode);
			CloseOneBufferDesc(Fd_Catccode);
			CloseOneBufferDesc(Fd_Cliohsatz);
			CloseOneBufferDesc(Fd_Clihsatz);
			CloseOneBufferDesc(Fd_Cliproduct);
			CloseOneBufferDesc(Fd_Cliproductgrp);
		}
		else
		{
			status = 1;
		}
        CloseBase( );
    }
   return status;
}

/* ------------------------------------------------------------------- */
#define FILE_LEN 30
long GenLiArtNeu( char *db, char *ili_direc, char *errmld )
{
    char meld[100];
	char *ili_file;
	
    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
	if ( ili_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler GenLiArtNeu" );
       return 1;
    }

	strcpy( ili_file, ili_direc );
    strcat( ili_file, FILENAME );
    if ( GenArtikel( db, ili_file, errmld ) != 0 )
    {
       free( ili_file );
	   return 1;
    }

    free( ili_file );
	sprintf( errmld, "%ld LINR\n" 
                     "%ld LI-Artikel erfolgreich geladen in cliart\n" 
                     "   %ld neue ZArtikel\n   %ld vorhandene ZArtikel\n" 
					 "clioart %ld updated, %ld inserted\n"
					 "   %ld ungültige Zeilen.",
                     lidatumnr,
                     satznr,
                     art_neuanlage,
                     art_aenderung,
					 anz_upd, anz_ins,
					 linenr_invalid );

    /* als bearbeitet kennzeichnen */
	if ( WriteIfaStatus( "PARTIKEL", ili_direc, meld  ) != 0 ) /*ifalib ifastat.c*/
    {
         strcat( errmld, "\nStatus 'bearbeitet' wurde nicht gesetzt" );
    }

    return 0;
}

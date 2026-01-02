/* ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die cexportarticle ein und schreibt             *
 *                  die Saetze in ZDP -Tabellen			                  *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 23.03.2018                                            *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>
#include <phozeit.h>

/* --------------------------- */
#include <wpp_prot.h>
#include <wpp_dbas.h>

#include "imp_form.h"
#include "pnamcode.h"
#include "sql_impartik.h"
#include "g_impartik.h"

#if !defined(WIN32)
#include <libgen.h>
#endif

/* --- Prototype  ------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld );
void CloseBase( void );

/* ------------------- Globale Variablen ------------------------ */
static long anz_new_manufacturers			= 0;
static long anz_upd_manufacturers			= 0;
static long anz_new_articles				= 0;
static long anz_upd_articles				= 0;
static long anz_locked_articles				= 0;

/* --------  user -------------- */
static const char* const user = "imartgen"  ;

/* ------------- Blanks am Ende eines Strings eliminieren ---------- */
 int Trim (char *s)
 {
	 int i;
	 
	 for (i = strlen(s)-1; i >= 0; i--)
	 {
		 if (s[i] != ' ')
		 {
			 break;
		 }
	 }

	 s[i+1] = '\0';
 
	 return i;
 }

 /* ------------- ALLE Blanks eines Strings eliminieren ---------- */
 int Trim_All (char *s)
 {
	 unsigned int i;
	 
	 for (i = 0; i < strlen(s)-1; i++)
	 {
		 if (s[i] == ' ')
		 {
			 s[i] = s[i+1];
		 }
	 }

	 return Trim(s);
 }

 /* ------------- Nullen am Anfang eines Strings eliminieren ---------- */
 int Trim_Leading_Zeros (char *s)
 {
	 int i;
	 
	 i = strspn(s, "0"); // Anzahl der Nullen am Anfang

	 strcpy(s, &s[i]);
	
	 return i;
 }

/* Create a new string with [substr] being replaced by [replacement] in [string]
 * Returns the new string, or NULL if out of memory.
 * The caller is responsible for freeing this new string.
*/
char * str_replace( const char *string, const char *substr, const char *replacement )
{
	char *tok = NULL;
	char *newstr = NULL;
	tok = strstr( string, substr );
	if( tok == NULL ) 
#ifdef WIN32
		return _strdup( string );
#else
		return strdup( string );
#endif

	newstr = malloc( strlen( string ) - strlen( substr ) + strlen( replacement ) + 1 );
	if( newstr == NULL ) 
		return NULL;

	memcpy( newstr, string, tok - string );
	memcpy( newstr + (tok - string), replacement, strlen( replacement ) );
	memcpy( newstr + (tok - string) + strlen( replacement ), tok + strlen( substr ), strlen( string ) - strlen( substr ) - ( tok - string ) );
	memset( newstr + strlen( string ) - strlen( substr ) + strlen( replacement ), 0, 1 );
	return newstr;
}

/* ------------------------------------------------------------------- */
static int ProcessManufacturerChanges (char* dbexp, char *countryexp, long datum_von, char *errmld )
{
	int status;
	struct HERSTEL_IMPORTDATA	impData;
	struct HERSTEL				herstel;
	char msg [1000];

	status = openCs_export_manuf(dbexp, datum_von, countryexp, errmld);

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at reading manufacturer changes - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}
	else
	{
		WriteProtZeile(fd_prot, "processing manufacturer changes ...");
	}

	while (0 == (status = fetchNext_export_manuf (&impData, errmld)))
	{
		// only updating existing manufacturers!
		if (0 == sel_herstel(&Fd_Herstel, impData.HERSTELLER_NR, &herstel, errmld))
		{
			strcpy(herstel.SORTIERNAME, impData.SORTIERNAME);
			strcpy(herstel.NAME, impData.NAME);
			strcpy(herstel.LANDESKUERZEL, impData.LANDESKUERZEL);
			strcpy(herstel.PLZ, impData.PLZ);
			strcpy(herstel.ORT, impData.ORT);
			strcpy(herstel.STRASSE, impData.STRASSE);
			strcpy(herstel.HAUSNR_VON, impData.HAUSNR_VON);
			strcpy(herstel.VORWAHL, impData.VORWAHL);
			strcpy(herstel.TELEFON_NR, impData.TELEFON_NR);
			strcpy(herstel.VORWAHL_TELEFAX, impData.VORWAHL_TELEFAX);
			strcpy(herstel.FAX_NR, impData.FAX_NR);
			
			herstel.BUSINESSTYPENO = 0;
			herstel.DATUM_IFAAENDER = PhoToday();
			strcpy(herstel.BEARBEITER, user);

			status = upd_herstel(&Fd_Herstel, &herstel, errmld);

			if (status != 0)
			{
				sprintf(msg, "Error <%ld> at updating manufacturer <%ld> - %s.", status, impData.HERSTELLER_NR, errmld);
				WriteProtZeile(fd_prot, msg);
				return status;
			}
			else
			{
				sprintf(msg, "manufacturer <%ld> has been updated.", impData.HERSTELLER_NR);
				WriteProtZeile(fd_prot, msg);
			}

			++anz_upd_manufacturers;
		}
		else
		{
			sprintf(msg, "not able to find manufacturer <%ld> - %s.", impData.HERSTELLER_NR, errmld);
			WriteProtZeile(fd_prot, msg);
		}
	}

	if (status != 100)
	{
		sprintf(msg, "Error <%ld> at fetching next manufacturer change - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
	}
	else
		status = 0;

	return status;
}

/* ------------------------------------------------------------------- */
static int ProcessManufacturerCreation (struct ARTICLE_IMPORTDATA *	impDataArticle, struct CIMPORTARTICLEPARAM *importParam, char *countryexp, char *errmld )
{
	int status;
	struct HERSTEL						herstel;
	struct HERLIEF						herlief;
	struct CIMEXMANUFACTURERMAPPING		manuMap;
	char msg [1000];

	FdInitTabBuf(Fd_Herstel, &herstel);
	FdInitTabBuf(Fd_Herlief, &herlief);
	FdInitTabBuf(Fd_Cimexmanufacturermapping, &manuMap);

	// nochmal Suchen, ob der Hersteller nicht im aktuellen Programmlauf schon angelegt wurde --> dann noch nicht im fetch enthalten ...
	if (0 < (impDataArticle->HERSTELLER_NR_IMP = sel_HnrByExportManufacturer(impDataArticle->HERSTELLER_NR_EXP, countryexp, errmld)))
		return 0;

	sprintf(msg, "export manufacturer <%ld> still unknown.", impDataArticle->HERSTELLER_NR_EXP);
	WriteProtZeile(fd_prot, msg);
	
	strcpy(herstel.SORTIERNAME, impDataArticle->SORTIERNAME);
	strcpy(herstel.NAME, impDataArticle->NAME);
	strcpy(herstel.LANDESKUERZEL, impDataArticle->LANDESKUERZEL);
	strcpy(herstel.PLZ, impDataArticle->PLZ);
	strcpy(herstel.ORT, impDataArticle->ORT);
	strcpy(herstel.STRASSE, impDataArticle->STRASSE);
	strcpy(herstel.HAUSNR_VON, impDataArticle->HAUSNR_VON);
	strcpy(herstel.VORWAHL, impDataArticle->VORWAHL);
	strcpy(herstel.TELEFON_NR, impDataArticle->TELEFON_NR);
	strcpy(herstel.VORWAHL_TELEFAX, impDataArticle->VORWAHL_TELEFAX);
	strcpy(herstel.FAX_NR, impDataArticle->FAX_NR);
			
	herstel.BUSINESSTYPENO = 0;
	strcpy(herstel.APOTHEKENPFL, "0");
	strcpy(herstel.ZENTRALPPELIST, "0");
	strcpy(herstel.NETTOARTIKEL, "0");
	strcpy(herstel.EKORIGINALHS, "0");
	strcpy(herstel.BESTELL_NUR_OZEK, "0");
	strcpy(herstel.REZEPTPFL, "0");
	herstel.DATUM_IFAAENDER = PhoToday();
	herstel.DATUM_ANLAGE = PhoToday();
	strcpy(herstel.BEARBEITER, user);

	// Neuanlage in herstel mit hersteller_nr=nummerek.INTHNR, 
	// INTHNR hochzählen	
	herstel.HERSTELLER_NR = sel_NextInternalHnr(errmld);

	if (herstel.HERSTELLER_NR > 0 && herstel.HERSTELLER_NR <= 99999)
	{
		sprintf(msg, "creating new manufacturer <%ld> for export no <%ld> ...", herstel.HERSTELLER_NR, impDataArticle->HERSTELLER_NR_EXP, errmld);
		WriteProtZeile(fd_prot, msg);

		status = ins_herstel(&Fd_Herstel, &herstel, errmld);

		if (status != 0)
		{
			sprintf(msg, "Error <%ld> at creating new manufacturer - %s.", status, errmld);
			WriteProtZeile(fd_prot, msg);
			return status;
		}

		// Eintrag in Cimexmanufacturermapping
		manuMap.HERSTELLER_NR = herstel.HERSTELLER_NR;
		manuMap.EXPORT_MANUFACTURERNO = impDataArticle->HERSTELLER_NR_EXP;
		strcpy(manuMap.COUNTRY_IFACODE, countryexp);
		status = ins_cimexmanufmapping(&Fd_Cimexmanufacturermapping, &manuMap, errmld);

		if (status != 0)
		{
			sprintf(msg, "Error <%ld> at creating new im/ex- manufacturer mapping - %s.", status, errmld);
			WriteProtZeile(fd_prot, msg);
			return status;
		}

		// die neue HNR via herlief mit Cimportarticleparam.importsupplierno verknüpfen.
		herlief.HERSTELLER_NR = herstel.HERSTELLER_NR;
		herlief.LANT_NR = importParam->SUPPLIERNO;
		status = ins_herlief(&Fd_Herlief, &herlief, errmld);

		if (status != 0)
		{
			sprintf(msg, "Error <%ld> at creating new herlief- manufacturer mapping - %s.", status, errmld);
			WriteProtZeile(fd_prot, msg);
			return status;
		}

		++anz_new_manufacturers;
	}
	else
	{
		sprintf(msg, "not able to create new manufacturer number <%ld> for export no <%ld> - %s!", herstel.HERSTELLER_NR, impDataArticle->HERSTELLER_NR_EXP, errmld);
		WriteProtZeile(fd_prot, msg);
		return -1;
	}
	
	impDataArticle->HERSTELLER_NR_IMP = herstel.HERSTELLER_NR;

	return status;
}

/* ------ attach discontinued date to article name ----- */
static void ChangeArtikelName( struct ZARTIKEL *spBuf )
{
    char szStr[12];

	if ( spBuf->DATUM_AH != 0 )
    {
      ConvFromPhoDate( szStr, spBuf->DATUM_AH, "mmjj" );
      memcpy( &spBuf->ARTIKEL_NAME[26], szStr, 4 );
    }
	else
	{
	  memcpy( &spBuf->ARTIKEL_NAME[26], "    ", 4 );
	}
}

/* ------------------------------------------------------------------- */
static int CopyArticleData(struct ZARTIKEL *zart, struct ARTICLE_IMPORTDATA	* impDataArticle, char *errmld )
{
	int status;
	struct CARTICLECODES	codes;
	struct CARTICLECODES	ntincode;
	struct EAN				ean;
	char msg[1000];

	FdInitTabBuf(Fd_CArticleCodes, &codes);
	FdInitTabBuf(Fd_Ean, &ean);
	
	strcpy(zart->ARTIKEL_MC, impDataArticle->ARTIKEL_MC);
	strcpy(zart->ARTIKEL_NAME, impDataArticle->ARTIKEL_NAME);
	zart->LAENGE = impDataArticle->LAENGE;
	zart->HOEHE = impDataArticle->HOEHE;
	zart->BREITE = impDataArticle->BREITE;
	zart->GEWICHT = impDataArticle->GEWICHT;
	strcpy(zart->KUEHLARTIKEL, impDataArticle->KUEHLARTIKEL);
	strcpy(zart->DARREICHFORM, impDataArticle->DARREICHFORM);
	strcpy(zart->EINHEIT, impDataArticle->EINHEIT);
	strcpy(zart->ARZNEIMITTEL, impDataArticle->ARZNEIMITTEL);
	strcpy(zart->TIERARZNEI, impDataArticle->TIERARZNEI);
	strcpy(zart->REZEPTPFL, impDataArticle->REZEPTPFL);
	strcpy(zart->APOTHEKENPFL, impDataArticle->APOTHEKENPFL);
	strcpy(zart->CHARGENARTIKEL, impDataArticle->CHARGENARTIKEL);
	zart->BIOSIEGEL = impDataArticle->BIOSIEGEL;
	strcpy(zart->ARTIKEL_NR_HERST, impDataArticle->PZN8);

/* INC-19011969 = EAN soll grundsätzlich nicht mehr aus D übernommen werden.

	status = sel_ean(&Fd_Ean, zart->ARTIKEL_NR, &ean, errmld);
	strcpy(ean.EAN_NR, impDataArticle->EAN_NR);
	ean.ARTIKEL_NR = zart->ARTIKEL_NR;

	if (status == 100)
	{
		if (impDataArticle->EAN_NR[0] != ' ') // keinen leeren Code schreiben!
		{
			status = ins_ean(&Fd_Ean, &ean, errmld);

			if (status == 1 && strstr(errmld, "-239" ) != NULL )
			{
				sprintf(msg, "ean <%s> not inserted as already connected to another article.", ean.EAN_NR);
				WriteProtZeile(fd_prot, msg);
				status = 0;
			}
		}
		else 
		{
			status = 0;
		}
	}
	else if (status == 0)
	{
		if (impDataArticle->EAN_NR[0] != ' ')
		{
			status = upd_ean(&Fd_Ean, &ean, errmld);

			if (status == 1 && (strstr(errmld, "-239" ) != NULL ||  strstr(errmld, "-346" ) != NULL))
			{
				sprintf(msg, "ean <%s> not updated as already connected to another article.", ean.EAN_NR);
				WriteProtZeile(fd_prot, msg);
				status = 0;
			}
		}
		else
			status = del_ean(&Fd_Ean, zart->ARTIKEL_NR, errmld);
	}
	else
	{
		sprintf(msg, "Error <%ld> at reading ean - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at proccesing ean - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}
*/

// ATC
	status = sel_atccode(&Fd_CArticleCodes, zart->ARTIKEL_NR, &codes, errmld);
	
	if (strcmp(codes.ARTICLE_CODE, impDataArticle->ATC_CODE) != 0)
	{
		strcpy(codes.ARTICLE_CODE, impDataArticle->ATC_CODE);
		codes.DATE_CHANGED = PhoToday(); // nur bei Änderung des Codes!
	}

	codes.ARTICLENO = zart->ARTIKEL_NR;

	if (status == 100)
	{
		if (impDataArticle->ATC_CODE[0] != ' ') // keinen leeren Code schreiben!
		{
			codes.ARTICLENO = zart->ARTIKEL_NR;
			codes.CODE_TYPE = 2; // ATC
			codes.PREFERRED_FLAG = 0;
			codes.SERIAL_NUMBER = 0;
			status = ins_carticlecodes(&Fd_CArticleCodes, &codes, errmld);
		}
		else 
		{
			status = 0;
		}
	}
	else if (status == 0)
	{
		if (impDataArticle->ATC_CODE[0] != ' ')
			status = upd_carticlecodes(&Fd_CArticleCodes, &codes, errmld);
		else
			status = del_atccode(&Fd_CArticleCodes, zart->ARTIKEL_NR, errmld);
	}
	else
	{
		sprintf(msg, "Error <%ld> at reading atc code - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at proccesing atc code - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}


// NTIN
	FdInitTabBuf(Fd_CArticleCodes, &ntincode);
	status = sel_ntincode(&Fd_CArticleCodes, zart->ARTIKEL_NR, &ntincode, errmld);
	
	if (strcmp(ntincode.ARTICLE_CODE, impDataArticle->NTIN_CODE) != 0)
	{
		strcpy(ntincode.ARTICLE_CODE, impDataArticle->NTIN_CODE);
		ntincode.DATE_CHANGED = PhoToday(); // nur bei Änderung des Codes!
	}

	ntincode.ARTICLENO = zart->ARTIKEL_NR;

	if (status == 100)
	{
		if (impDataArticle->NTIN_CODE[0] != ' ') // keinen leeren Code schreiben!
		{
			ntincode.ARTICLENO = zart->ARTIKEL_NR;
			ntincode.CODE_TYPE = 22; // NTIN
			ntincode.PREFERRED_FLAG = 0;
			ntincode.SERIAL_NUMBER = 1;
			status = ins_carticlecodes(&Fd_CArticleCodes, &ntincode, errmld);
		}
		else 
		{
			status = 0;
		}
	}
	else if (status == 0)
	{
		if (impDataArticle->NTIN_CODE[0] != ' ')
			status = upd_carticlecodes(&Fd_CArticleCodes, &ntincode, errmld);
		else
			status = del_ntincode(&Fd_CArticleCodes, zart->ARTIKEL_NR, errmld);
	}
	else
	{
		sprintf(msg, "Error <%ld> at reading NTIN - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at proccesing NTIN - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}
	
	return status;
}

/* Default values*/
static const char* const VALUE_ZERO = "0";
static const char* const VALUE_ONE = "1";
static const char* const VALUE_BLANK = " ";
static const char* const VALUE_NO = "N";

/* ----- default vaulues for article fields ------- */
void InitArtikelFields( struct ZARTIKEL *zart )
{
	memset(zart->ZUZAHLUNG_IFA, '0', L_ZARTIKEL_ZUZAHLUNG_IFA );
	strcpy(zart->NAHRUNGSERGAENZUNG, "N");
	strcpy(zart->ELEKTROSCHROTT, "N");
	strcpy(zart->PREISSENKUNG, "0");
	strcpy(zart->BSSICHG, "0");
	strcpy(zart->ANBIETERABSCHLAG, "0");
	strcpy(zart->AUTIDEMARTIKEL, "0");
	strcpy(zart->FESTBETRARTIKEL, "0");
	strcpy(zart->REZEPTURARZNEI, "0");
	strcpy(zart->MEDIZINPRODUKT, "0");
	strcpy(zart->IMPFSTOFF, "0");
	strcpy(zart->CE_KENNZEICHEN, "0");
	strcpy(zart->KONTRAZEPTIVUM, "0");
	strcpy(zart->BIOZID_VERORD, "0");
	strcpy(zart->ZENTRALPPELIST, "0");
	strcpy(zart->EKORIGINALHS, "0");
	strcpy(zart->BESTELL_NUR_OZEK, "0");
	strcpy(zart->HILFSM_VERBRAUCH, "0");
	strcpy(zart->HOMOEOPATHIKUM, "0");
	strcpy(zart->ANTHROPOSOPHIKUM, "0");
	strcpy(zart->PHYTOPHARMAKON, "0");
	strcpy(zart->TREZEPTARZNEI, "0");
	strcpy(zart->AMG_47, "0");
	strcpy(zart->BATTERIEGESETZ, "0");
	strcpy(zart->NEM_PHAGROPRUEFUNG, "0");
	strcpy(zart->NEM_ZERTIFIKAT, "0");
	strcpy(zart->STELLER, "0");
	strcpy(zart->PFLSCHUTZ_VERORD, "0");
	strcpy(zart->BESTELL_NICHT_AUSL, "0");
	strcpy(zart->EAN_NICHTVORHANDEN, "0");
	strcpy(zart->FAELSCH_GEFAHR, "0");
	strcpy(zart->VERFALL, "0");
	strcpy(zart->TFG, "0");
	strcpy(zart->KLINIKPACKUNG, "0");
	strcpy(zart->BTM, "0");
	strcpy(zart->VERTRBIND_IFA, "0");
	strcpy(zart->NICHTUEBERGH, "0");
	
	strcpy(zart->ERSATZ_NR_AKTIV, VALUE_ZERO);
   strcpy(zart->PRIVATSORTIMENT, VALUE_NO);
   strcpy(zart->TAXPRUEFGROSSO, VALUE_ZERO);
   strcpy(zart->SONDERGROSSO, VALUE_BLANK);
   strcpy(zart->INDIKATOR, VALUE_ZERO);
   strcpy(zart->PREIS0ARTIKEL, VALUE_ZERO);
   strcpy(zart->MELDEPFL, VALUE_ZERO);
   strcpy(zart->MVDAARTIKEL, VALUE_ZERO);
   strcpy(zart->ZYTOSTATIKA, VALUE_ZERO);
   strcpy(zart->SICHTWAHL, VALUE_ZERO);
   strcpy(zart->RETOURENSPERRE, VALUE_ONE);
   strcpy(zart->ZENTR_EKSPERRE, VALUE_ZERO);
   strcpy(zart->ARTIKEL_GELOESCHT, VALUE_ZERO);
   strcpy(zart->SOMMER_KK, VALUE_ZERO);
   strcpy(zart->PRODUKTART, VALUE_ZERO);   
   strcpy(zart->BESTELLSPERRE, VALUE_ZERO);
   strcpy(zart->KATALOG, VALUE_BLANK);
   strcpy(zart->LABORARTIKEL, VALUE_ZERO);
   strcpy(zart->VERTRBIND, VALUE_BLANK);
   strcpy(zart->NATURALRABATT, VALUE_ZERO);
   strcpy(zart->PRISMAEDISK, VALUE_ZERO);
   strcpy(zart->GS_EXPLOSION, VALUE_ZERO);
   strcpy(zart->GS_BRAND, VALUE_ZERO);
   strcpy(zart->GS_LEICHTENTZ, VALUE_ZERO);
   strcpy(zart->GS_HOCHENTZ, VALUE_ZERO);
   strcpy(zart->GS_GIFTIG, VALUE_ZERO);
   strcpy(zart->GS_SEHRGIFTIG, VALUE_ZERO);
   strcpy(zart->GS_GESUNDHSCH, VALUE_ZERO);
   strcpy(zart->GS_REIZEND, VALUE_ZERO);
   strcpy(zart->GS_AETZEND, VALUE_ZERO);
   strcpy(zart->GS_UMWELT, VALUE_ZERO);
   strcpy(zart->GS_VORSLAGERN, VALUE_ZERO);
   strcpy(zart->GS_SVORSLAGERN, VALUE_ZERO);
   strcpy(zart->AWL_AKTIV, VALUE_NO);
   strcpy(zart->SORTIMENT_1, VALUE_ZERO);
   strcpy(zart->SORTIMENT_2, VALUE_ZERO);
   strcpy(zart->SORTIMENT_3, VALUE_ZERO);
   strcpy(zart->SORTIMENT_4, VALUE_ZERO);
   strcpy(zart->SORTIMENT_5, VALUE_ZERO);
   strcpy(zart->PERF, VALUE_ZERO);
   strcpy(zart->ABGABEBEST_IFA, VALUE_BLANK);
   strcpy(zart->PSYCHOTROP,VALUE_NO);
   strcpy(zart->GS_LICHTGESCH,VALUE_ZERO);
   strcpy(zart->CHARGENARTIKEL, VALUE_ZERO);
}

/* ----- Default values for zartaustria fields ------- */
void InitZartaustriaFields( struct ZARTAUSTRIA *spZartAustria )
{
	strcpy(spZartAustria->WECHSELARTIKEL, VALUE_ZERO);
	strcpy(spZartAustria->BUENDELPACKUNG, VALUE_ZERO);
	strcpy(spZartAustria->CHARGENARTIKEL, VALUE_ZERO);
    memset( spZartAustria->OELHV_GRUPPE, ' ', L_ZARTAUSTRIA_OELHV_GRUPPE );
    memset( spZartAustria->OELHV_OEKOKZ, ' ', L_ZARTAUSTRIA_OELHV_OEKOKZ );
    memset( spZartAustria->OELHV_SORT, ' ', L_ZARTAUSTRIA_OELHV_SORT );
	strcpy(spZartAustria->HV_BOX, VALUE_ZERO);
	strcpy(spZartAustria->VERTRBIND_PLPL, VALUE_ZERO);
	strcpy(spZartAustria->VERTRBIND_S1S5, VALUE_ZERO);
	strcpy(spZartAustria->VERTRBIND_VPL, VALUE_ZERO);
	strcpy(spZartAustria->VERTRBIND_SP, VALUE_ZERO);
	strcpy(spZartAustria->VERTRBIND_COMPTANT, VALUE_BLANK);
	strcpy(spZartAustria->VERTRBIND_NEUFORM, VALUE_ZERO);
	strcpy(spZartAustria->NICHT_LIEFERBAR, VALUE_ZERO);
	strcpy(spZartAustria->NICHT_GELIEFERT, VALUE_ZERO);
}

/* ------------------------------------------------------------------- */
static int CopyDefaultValues(struct ZARTIKEL *zart, struct CIMPORTARTICLEPARAM * param, char *errmld)
{
	struct ZARTWG		wg;
	struct ZARTAUSTRIA	austria;
	struct BLIESORT		bliesort;
	int status;
	char msg[1000];

	FdInitTabBuf(Fd_ZArtWg, &wg);
	FdInitTabBuf(Fd_ZArtAustria, &austria);
	FdInitTabBuf(Fd_Bliesort, &bliesort);

	InitArtikelFields(zart);

	strcpy(zart->SKONTOFAEHIG, param->SKONTOFAEHIG);
	strcpy(zart->NETTOARTIKEL, "1");
	strcpy(zart->RABATTFAEHIG, "01");
	strcpy(zart->BESTANDSBUCHUNG, "1");
	strcpy(zart->TAXPFL, "0");

	strcpy(wg.WARENGRUPPE, param->WARENGRUPPE);
	wg.ARTIKEL_NR = zart->ARTIKEL_NR;
	strcpy(wg.ART, "2");
	status = ins_zartwg(&Fd_ZArtWg, &wg, errmld);

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at inserting zartwg - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}

	InitZartaustriaFields(&austria);
	austria.DEUTSCHLANDBESORGER = 1;
	strcpy(austria.NACHLIEFERUNG, "0"); // Wunsch von AHS am 18.05.2018!
	austria.ARTIKEL_NR = zart->ARTIKEL_NR;
	status = ins_zartaustria(&Fd_ZArtAustria, &austria, errmld);	

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at inserting zartaustria - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}

	// --> bliesort schreiben für kddispo ...
	bliesort.BESLA_NR = param->SUPPLIERNO;
	bliesort.ARTIKEL_NR = zart->ARTIKEL_NR;

	status = ins_bliesort(&Fd_Bliesort, &bliesort, errmld);

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at inserting bliesort - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}

	return status;
}

/* ------------------------------------------------------------------- */
static int CopyPriceData(struct CIMPORTARTICLEPARAM * param, struct ZARTIKEL * zart, struct PRICE_IMPORTDATA * impDataPrice, char *errmld )
{
	struct ZARTPREIS			preis;
	int status;
	char msg[1000];

	FdInitTabBuf(Fd_ZArtPreis, &preis);

	preis.AEP = impDataPrice->AEP * (100 + param->AEP_INCREASEPCT) / 100;
	preis.GROSSO = impDataPrice->GROSSO * (100 + param->GROSSO_INCREASEPCT) / 100;
	preis.ARTIKEL_NR = zart->ARTIKEL_NR;
	preis.DATUMGUELTIGAB = impDataPrice->DATUMGUELTIGAB;
	preis.AVP = impDataPrice->AVP;
	preis.PREIS_TYP = 0;

	// Arzneimittel / rezeptpfl. = 10% (verm=1), Tierarznei = 13% (2), Rest = 20% (voll=0);
	if (zart->ARZNEIMITTEL[0] == '1' || zart->REZEPTPFL[0] == '1')
		strcpy(preis.KE_MWST, "1");
	else if (zart->TIERARZNEI[0] == '1')
		strcpy(preis.KE_MWST, "2");
	else
		strcpy(preis.KE_MWST, "0");
	
	status = save_zartpreis(&Fd_ZArtPreis, &preis, errmld);

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at reading storing price - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
	}

	return status;
}

/* ------------------------------------------------------------------- */
static int ProcessPrices(char* dbexp, struct CIMPORTARTICLEPARAM * param, struct ARTICLE_IMPORTDATA * impDataArticle, struct ZARTIKEL * zart, short initialPriceNeeded, char* errmld)
{
	struct PRICE_IMPORTDATA		impDataPrice;
	int status;
	char msg[1000];

	status = openCs_export_price(dbexp, impDataArticle->ARTIKEL_NR, errmld);

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at reading export prices - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}
	else
	{
		sprintf(msg, "processing import of price data ...");
		WriteProtZeile(fd_prot, msg);
	}

	while (0 == (status = fetchNext_export_price (&impDataPrice, errmld)))
	{
		sprintf(msg, "Importing prices for article <%ld>, datevalidfrom <%ld> ...", impDataPrice.ARTIKEL_NR, impDataPrice.DATUMGUELTIGAB);
		WriteProtZeile(fd_prot, msg);

		if (impDataPrice.DATUMGUELTIGAB <= PhoToday()) // keine Preise aus der Vergangenheit übernehmen
		{
			if (initialPriceNeeded > 0) // bei Neuanlagen, den aktuell gültigen Preis übernehmen!
			{
				status = CopyPriceData(param, zart, &impDataPrice, errmld);
			}
			else
			{
				WriteProtZeile(fd_prot, "date in the past --> price not imported!");
			}

			closeCs_export_price();
			break;
		}
			
		status = CopyPriceData(param, zart, &impDataPrice, errmld);
	}

	if (status == 100)
		status = 0;

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at fetching next price - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
static int ProcessArticleImporting(char* dbexp, char *countryimp, char *countryexp, struct CIMPORTARTICLEPARAM * param, char *errmld)
{
	int status;
	char msg[1000];

	struct ARTICLE_IMPORTDATA	impDataArticle;
	struct ZARTIKEL				zart;

	struct CARTICLECODES		codes;
	long						articleno;
	short						initialPriceNeeded;

	FdInitTabBuf(Fd_ZArtikel, &zart);
	FdInitTabBuf(Fd_CArticleCodes, &codes);
	
	status = openCs_export_article(dbexp, countryimp, countryexp, errmld);

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at reading export articles - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}
	else
	{
		sprintf(msg, "processing import of article data ...");
		WriteProtZeile(fd_prot, msg);
	}

	while ( 0 == (status = fetchNext_export_article (&impDataArticle, errmld)))
	{
		Trim(impDataArticle.PZN8);
		WriteProtZeile(fd_prot, " ----------------------------------------- ");
		sprintf(msg, "Importing export article <%ld>, pzn8 <%s> ...", impDataArticle.ARTIKEL_NR, impDataArticle.PZN8);
		WriteProtZeile(fd_prot, msg);

		status = StartTransaction(errmld);
		if (status != 0)
		{
			sprintf(msg, "Error <%ld> at starting transaction - %s.", status, errmld);
			WriteProtZeile(fd_prot, msg);
			return status;
		}
		
		// 3.Schritt: Prüfen zu jedem Artikel, ob die zugehörige deutsche HNR bereits in Cimexmanufacturermapping.Export_HNR (mit country_ifacode='de') enthalten ist.
		if (impDataArticle.HERSTELLER_NR_IMP <= 0 && impDataArticle.EXPORTPERMISSIONFLAG > 0)
		{
			status = ProcessManufacturerCreation(&impDataArticle, param, countryexp, errmld);

			if (status != 0)
				return status;
		}
		
		if ( 0 > (articleno = sel_ArtNoByManArt(impDataArticle.PZN8, errmld)))
		{
			sprintf(msg, "Error <%ld> at looking for article number via export no <%s> - %s.", articleno, impDataArticle.PZN8, errmld);
			WriteProtZeile(fd_prot, msg);
			return status;
		}
		
		if (articleno > 0)
		{
			sprintf(msg, "article number <%ld> found for export no <%s>.", articleno, impDataArticle.PZN8);
			WriteProtZeile(fd_prot, msg);

			initialPriceNeeded = 0;

			// Artikel bereits vorhanden
			status = sel_zartikel(&Fd_ZArtikel, articleno, &zart, errmld);

			if (status != 0)
			{
				sprintf(msg, "Error <%ld> at reading article - %s.", status, errmld);
				WriteProtZeile(fd_prot, msg);
				return status;
			}

			if (impDataArticle.EXPORTPERMISSIONFLAG == 0)
			{
				sprintf(msg, "locking article <%ld> as no export permission anymore...", articleno);
				WriteProtZeile(fd_prot, msg);

				// Artikel sperren ==> zartikel.artikel_gesperrt=1 und zartikel.datum_ah=current und letzte 4 Stellen Artikelname!
				strcpy(zart.ARTIKEL_GESPERRT, "1");
				zart.DATUM_AH = PhoToday();
				ChangeArtikelName(&zart);
				++anz_locked_articles;
			}
			else
			{
				// 4.Schritt: ggfs. entsperren und Artikeldaten updaten
				status = CopyArticleData(&zart, &impDataArticle, errmld);

				if (status != 0)
					return status;

				if (zart.ARTIKEL_GESPERRT[0] == '1')
				{
					strcpy(zart.ARTIKEL_GESPERRT, "0");
					zart.DATUM_AH  = 0;
					ChangeArtikelName(&zart);
				}
				++anz_upd_articles;
			}
				
			// --> als hersteller_nr darf nicht die deutsche HNR, sondern muss die gemappte, interne österreichische HNR gesetzt werden!
			zart.HERSTELLER_NR = impDataArticle.HERSTELLER_NR_IMP;

			zart.DATUM_IFAAENDER = PhoToday();
			strcpy(zart.BEARBEITER, user);
			
			status = upd_zartikel(&Fd_ZArtikel, &zart, errmld);

			if (status != 0)
			{
				sprintf(msg, "Error <%ld> at updating article - %s.", status, errmld);
				WriteProtZeile(fd_prot, msg);
				return status;
			}
		}
		else if (impDataArticle.EXPORTPERMISSIONFLAG == 1)
		{
			sprintf(msg, "No already existing article found for export no <%s>.", impDataArticle.PZN8);
			WriteProtZeile(fd_prot, msg);

			initialPriceNeeded = 1;

			//Artikel- Neuanlage mit artikel_nr=nummerek.INTPZN, INTPZN hochzählen
			zart.ARTIKEL_NR = sel_NextInternalPzn(errmld);

			if (zart.ARTIKEL_NR > 0 && zart.ARTIKEL_NR <= 9999999)
			{
				sprintf(msg, "creating new article <%ld> for export no <%ld> ...", zart.ARTIKEL_NR, impDataArticle.ARTIKEL_NR, errmld);
				WriteProtZeile(fd_prot, msg);
				articleno = zart.ARTIKEL_NR;

				// 4.Schritt: Artikel mit deutschen Artikeldaten und Defaultwerten aus Cimportarticleparam neu anlegen
				FdInitTabBuf(Fd_ZArtikel, &zart);
				zart.ARTIKEL_NR = articleno;
				status = CopyArticleData(&zart, &impDataArticle, errmld);

				if (status != 0)
					return status;

				status = CopyDefaultValues(&zart, param, errmld);

				if (status != 0)
					return status;

				// --> als hersteller_nr darf nicht die deutsche HNR, sondern muss die gemappte, interne österreichische HNR gesetzt werden!
				zart.HERSTELLER_NR = impDataArticle.HERSTELLER_NR_IMP;

				zart.DATUM_ANLAGE = PhoToday();
				strcpy(zart.BEARBEITER, user);
				strcpy(zart.ARTIKEL_GESPERRT, "0");
				strcpy(zart.USER_ANLAGE, user);
			
				status = ins_zartikel(&Fd_ZArtikel, &zart, errmld);

				if (status != 0)
				{
					sprintf(msg, "Error <%ld> at inserting article - %s.", status, errmld);
					WriteProtZeile(fd_prot, msg);
					return status;
				}

				sprintf ( codes.ARTICLE_CODE, "%ld", zart.ARTIKEL_NR);
				codes.ARTICLENO = zart.ARTIKEL_NR;
				codes.DATE_CHANGED = PhoToday();
				codes.CODE_TYPE = 11; // PZN 7
				codes.PREFERRED_FLAG = 1;
				codes.SERIAL_NUMBER = 1;
				status = ins_carticlecodes(&Fd_CArticleCodes, &codes, errmld);

				if (status != 0)
				{
					sprintf(msg, "Error <%ld> at inserting article code <11> - %s.", status, errmld);
					WriteProtZeile(fd_prot, msg);
					return status;
				}

				++anz_new_articles;
			}
			else
			{
				sprintf(msg, "not able to create new article number for export no <%ld> - %s!", impDataArticle.ARTIKEL_NR, errmld);
				WriteProtZeile(fd_prot, msg);
				return -1;
			}
		}
		else
		{
			WriteProtZeile(fd_prot, "article creation skipped as export is NOT allowed!");
		}
	
		/* --> zartpreis separat pro Artikel! Übernahme aller D-Preise in der Zukunft;
		bei Neuanlagen, zusätzlich lesen des aktuellen D- Preises = datumgueltigab auf "morgen" setzen	*/
		if (articleno > 0)
			status = ProcessPrices(dbexp, param, &impDataArticle, &zart, initialPriceNeeded, errmld);

		if (status != 0)
			return status;

		status = markExportArticleAsImportProcessed(dbexp, countryimp, impDataArticle.ARTIKEL_NR, errmld );
		
		if (status != 0) 
		{
			sprintf(msg, "Error <%ld> at marking export article as imported - %s.", status, errmld);
			WriteProtZeile(fd_prot, msg);
			return status;
		}
		else
		{
			WriteProtZeile(fd_prot, "export article marked as import processed.");

			status = CommitTransaction(errmld);

			if (status != 0)
			{
				sprintf(msg, "Error <%ld> at commiting transaction - %s.", status, errmld);
				WriteProtZeile(fd_prot, msg);
				return status;
			}
		}

#ifdef WIN32
		// for testing / debugging
		if (anz_locked_articles + anz_new_articles + anz_upd_articles >= 50)
		{
			status = 100;
			break;
		}
#endif

	}

	if (status != 100)
	{
		sprintf(msg, "Error <%ld> at fetching next article - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
	}
	else
		status = 0;
	
	return status;
}

/* ------------------------------------------------------------------- */
static int ImportLieferung( char* dbexp, char *countryimp, char *countryexp, long datum_von, char *errmld )
{
	int status;
	char msg[1000];

	struct CIMPORTARTICLEPARAM	param;

// Lesen von Default- Import- Werten
	status = sel_importParam(&Fd_Cimportarticleparam, countryexp, &param, errmld);

	if (status != 0)
	{
		sprintf(msg, "Error <%ld> at reading table <cimportarticleparam> - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}
	else
	{
		sprintf(msg, "Default values read successfully from <cimportarticleparam>: Export-Country <%s>, Grosso-Pct <%lf>, Aep-Pct <%lf>, Supplier <%ld>, Wgr <%s>, Skonto <%s>, Months <%d>.", 
			param.COUNTRY_IFACODE, param.GROSSO_INCREASEPCT, param.AEP_INCREASEPCT, param.SUPPLIERNO, param.WARENGRUPPE, param.SKONTOFAEHIG, param.INACTIVEMONTHS);
		WriteProtZeile(fd_prot, msg);
	}

// 1.Schritt: Für alle Einträge in Cimexmanufacturermapping prüfen, ob im deutschen Hersteller das datum_aender oder datum_ifaaender > lastRun ist.
	status = ProcessManufacturerChanges(dbexp, countryexp, datum_von, errmld);

	if (status != 0)
		return status;
	
// 2.Schritt: Lesen aller zu übernehmenden Artikeldaten (incl. zugehörigem Hersteller) zu den Artikelnummern aus ide21@ide21_tcp:cexportarticle
	status = ProcessArticleImporting(dbexp, countryimp, countryexp, &param, errmld);

	if (status != 0)
	{
		CancelTransaction(); // transaction started for each article in "ProcessArticleImporting"
		return status;
	}

	WriteProtZeile(fd_prot, "-------------------------------------------------");
	WriteProtZeile(fd_prot, "ALL export articles processed successfully.");
	WriteProtZeile(fd_prot, "Looking for outdated articles to delete ...");
	
// 5.Schritt: für alle gesperrten D-Besorger-Artikel prüfen, ob datum_ah mehr als Cimportarticleparam.inactivemonthsbeforedeletion in der Vergangenheit. wenn ja, dann Lösch-KZ setzen.
	status = markOutdatedArticlesAsDeleted(param.INACTIVEMONTHS, user, errmld);

	if (status != 0) 
	{
		sprintf(msg, "Error <%ld> at marking outdated articles as deleted - %s.", status, errmld);
		WriteProtZeile(fd_prot, msg);
		return status;
	}
	else
	{
		sprintf(msg, "All import articles with out of sale date more than <%d> months in the past have been marked with deletion flag.", param.INACTIVEMONTHS);
		WriteProtZeile(fd_prot, msg);
	}
		
	return status;
}

/* ------------------------------------------------------------------- */
static long GenImportData( char *dbimp, char* dbexp, char *countryimp, char *countryexp, long datum_von, char* prot_file, char *errmld )
{
   int status;
   char today[9];
   char acttime[7];
   long time;
   	
   long tages_datum = GetPhoDate();
   time = GetPhoTime();
   
   fd_prot = NULL;

   strcat(prot_file, PROTNAME );
   sprintf(today, "_%ld", tages_datum);
   strcat(prot_file, today );
   sprintf(acttime, "_%06ld", time);
   strcat(prot_file, acttime );   
   strcat(prot_file, PROTEND );

   /*öffnen des Protokoll-File*/
   status = OpenProtDatei( &fd_prot, prot_file, tages_datum, time, errmld );
   if ( status != 0 )
   {
       strcat(errmld, "not able to open protocol-file\n");
	   return status;
   } 

    if ( OpenBase( dbimp, errmld ) == 0 )
    {
        OpenPflege( (char*)user, errmld );
		
		Fd_ZArtikel = -1;
		Fd_ZArtPreis= -1;
		Fd_CArticleCodes = -1;
		Fd_Herstel = -1;
		Fd_Cimexmanufacturermapping = -1;
		Fd_Cimportarticleparam = -1;
		Fd_Herlief = -1;
		Fd_Ean = -1;
		Fd_ZArtAustria = -1;
		Fd_ZArtWg = -1;
		Fd_Bliesort = -1;
		
		if ( OpenBufferDesc( &Fd_CArticleCodes, "carticlecodes", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 
			&& OpenBufferDesc( &Fd_ZArtikel, "zartikel", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0
			&& OpenBufferDesc( &Fd_Herstel, "herstel", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0
			&& OpenBufferDesc( &Fd_Cimexmanufacturermapping, "cimexmanufacturermapping", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0
			&& OpenBufferDesc( &Fd_Cimportarticleparam, "cimportarticleparam", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0
			&& OpenBufferDesc( &Fd_Herlief, "herlief", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0
			&& OpenBufferDesc( &Fd_Ean, "ean", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0
			&& OpenBufferDesc( &Fd_ZArtAustria, "zartaustria", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0
			&& OpenBufferDesc( &Fd_ZArtWg, "zartwg", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0
			&& OpenBufferDesc( &Fd_Bliesort, "bliesort", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0
			&& OpenBufferDesc( &Fd_ZArtPreis, "zartpreis", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0)
		{
			status = ImportLieferung ( dbexp, countryimp, countryexp, datum_von, errmld );
		}
		else
			status = 1;

		CloseOneBufferDesc(Fd_ZArtikel);
		CloseOneBufferDesc(Fd_Herstel);
		CloseOneBufferDesc(Fd_Herlief);
		CloseOneBufferDesc(Fd_Cimexmanufacturermapping);
		CloseOneBufferDesc(Fd_Cimportarticleparam);
		CloseOneBufferDesc(Fd_ZArtPreis);
		CloseOneBufferDesc(Fd_Ean);
		CloseOneBufferDesc(Fd_CArticleCodes);
		CloseOneBufferDesc(Fd_ZArtAustria);
		CloseOneBufferDesc(Fd_ZArtWg);
		CloseOneBufferDesc(Fd_Bliesort);

		CloseBase( );
    }
	else
		status = 1;

   return status;
}

/* ------------------------------------------------------------------- */
long GenImport( char *dbimp, char *dbexp, char *countryimp, char *countryexp, char *datefrom, char *errmld )
{
	char prot_file[500];
	int status;
	char msg[500];
	long datum_von;
	  
#if !defined(WIN32)
    char *verz2;
#endif
  
    #ifdef WIN32
		strcpy( prot_file, "C:/temp/" ); /* for debug; write protokol to file-directory */
	#else
		verz2 = getcwd(prot_file, 450);

		strcpy (prot_file, verz2); 
		strcat (prot_file, "/../log");
	#endif

	if ( ConvToPhoDate ( datefrom, &datum_von, "tt.mm.jjjj" ) != 1 )
	{
		strcpy( errmld, "Datum-von in der Form tt.mm.jjjj" );
		return 1;
	}

	status = GenImportData( dbimp, dbexp, countryimp, countryexp, datum_von, prot_file, errmld );

    sprintf( msg,	 "\n%ld Artikel geaendert\n" 
                     "%ld Artikel neu angelegt\n" 
					 "%ld Artikel gesperrt\n" 
					 "%ld Hersteller neu angelegt\n" 
					 "%ld Hersteller geaendert.",
					 anz_upd_articles, anz_new_articles, anz_locked_articles, anz_new_manufacturers, anz_upd_manufacturers);
	
	WriteProtZeile(fd_prot, msg);
	
	if ( status == 0 )
		strcpy (errmld, msg);
	else
		strcat (errmld, msg);

	CloseProtDatei ( fd_prot );

    return status;
}


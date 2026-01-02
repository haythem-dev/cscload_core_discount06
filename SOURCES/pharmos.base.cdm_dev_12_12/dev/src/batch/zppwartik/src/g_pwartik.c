/* ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die PW-Artikeldatei ein und schreibt            *
 *                  die Saetze in ZDP -Tabellen			                  *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 28.12.2012                                            *
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

#include <zartikel.h>
#include <zartprei.h>
#include <carticlecodes.h>

#include "pw_form.h"
#include "pnamcode.h"
#include "sql_pwartik.h"
#include "g_pwartik.h"

#if !defined(WIN32)
#include <libgen.h>
#endif

/* --- Prototype  ------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld );
void CloseBase( void );

/* ------------------- Globale Variablen ------------------------ */
static long anz_upd			= 0;
static long anz_ins			= 0;
static long anz_skipped		= 0;
static long anz_ins_pseudo	= 0;
static long anz_inactivated	= 0;
static long anz_switched	= 0;

static long line_nr;

struct ZARTIKEL zart;
struct CARTICLECODES zcodes;
struct ZARTPREIS zpreis;
struct RATIOPHARM ratioph;

/* --------  user -------------- */
static const char* const user = "pwartik"  ;

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
static int LineToDataBuffer (char* line, char *errmld)
{
	char TmpNumeric[21];
	memset(TmpNumeric, '\0', 20);

	memset(&ratioph,0,sizeof(ratioph));
					
	strncpy(TmpNumeric, &line[P_INTRO], L_INTRO);
#ifdef WIN32
	if ( strncmp(TmpNumeric, "MAT;", 4) != 0 ) // zum Debuggen "MAT;T" oder "MAT;P"
#else
	if ( strcmp(TmpNumeric, "MAT;P") != 0 ) 
#endif
	{
		strcat(errmld, "dataline doesn´t start with expected <MAT;P>!\n");
		return 1;
	}
	memset(TmpNumeric, '\0', 20);
	
	// hersteller_nr
	strncpy(TmpNumeric, &line[P_MANUFACTURER], L_MANUFACTURER); 
	ratioph.HERSTELLER_NR = atol( TmpNumeric );
	memset(TmpNumeric, '\0', 20);
	
	// CDATE
	strncpy(TmpNumeric, &line[P_CDATE], L_CDATE); 
	ratioph.DATUM = atol( TmpNumeric );
	memset(TmpNumeric, '\0', 20);
	
	// CFONC
	strncpy(ratioph.CHANGE_FLAG, &line[P_CFONC], L_CFONC); 
	
	// RMMG1-MATNR = zartikel.artikel_nr_herst
	strncpy(TmpNumeric, &line[P_MATNR], L_MATNR); 
	Trim_Leading_Zeros(TmpNumeric);
	strcpy(ratioph.ARTIKEL_NR_HERST, TmpNumeric);
	memset(TmpNumeric, '\0', 20);
		
	// MAKT-MAKTX = zartikel.artikel_langname / artikel_name / artikel_mc
	strncpy(ratioph.ARTIKEL_LANGNAME, &line[P_MATTEXT], L_MATTEXT); 
	
	// RM03Z-NMTAR 
	// strncpy(XXX, &line[P_MATART], L_MATART); 
	
	// MARA-MEINS --> zartikel.einheit (2.Teil)
	strncpy(ratioph.EINHEIT_2, &line[P_EINHEIT_BASIS], L_EINHEIT_BASIS); 
	
	// MARA-SPART --> zartikel.rezeptpfl / apothekenpfl / psychotrop / btm / zytostatika / medizinprodukt
	strncpy(ratioph.SPARTE, &line[P_SPARTE], L_SPARTE); 
	
	// MARA-MSTAE --> zartikel.artikel_geloescht
	strncpy(ratioph.STATUS, &line[P_STATUS], L_STATUS); 
	
	// MARA-NORMT --> zartikel.artikel_nr + article_code
	strncpy(ratioph.ARTICLE_CODE, &line[P_NORMBEZ], L_NORMBEZ); 
	
	// MVKE-VRKME --> zartikel.einheit (1.Teil)
	strncpy(ratioph.EINHEIT_1, &line[P_EINHEIT_VERKAUF], L_EINHEIT_VERKAUF); 
	
	// MARC-LADGR
	// strncpy(XXX, &line[P_LADEGRP], L_LADEGRP); 
	
	// MARA-TEMPB --> zartikel.kuehlartikel
	strncpy(ratioph.KUEHL, &line[P_TEMP], L_TEMP); 
	
	// MARA-BEHVO
	// strncpy(XXX, &line[P_BEHAELTER], L_BEHAELTER); 
	
	// MARA-RAUBE
	// strncpy(XXX, &line[P_RAUM], L_RAUM); 
	
	// KONP-KBETR --> zartpreis
	strncpy(TmpNumeric, str_replace(&line[P_PREIS], ",", "."), L_PREIS); 
	
	ratioph.PREIS = atof( TmpNumeric );
	
	return 0;
}

/* ------------------------------------------------------------------- */
static int LineToStruct (char* line, char *errmld)
{
	memset(&zpreis,0,sizeof(zpreis));
	memset(&zart,0,sizeof(zart));
	memset(&zcodes,0,sizeof(zcodes));
	
	return LineToDataBuffer( line, errmld );
}

/* ------------------------------------------------------------------- */
static void setAender( )
{
	zart.DATUM_AENDER = tages_datum;
	strcpy(zart.BEARBEITER, user);
}

/* ------------------------------------------------------------------- */
static void FillArtikelBuf(long pzn, int isNeuanlage)
{
	char name50 [80] = {0};
	int pos;
	
	if (isNeuanlage == 1)
	{
		zart.DATUM_ANLAGE = tages_datum;
		strcpy(zart.PSYCHOTROP, "N");
		strcpy(zart.KUEHLARTIKEL, "0");
		zart.ERSATZ_NR = 0;

		// additional initializations
			// also zartaustria.nachlieferung should be set to 1
			// for "Werbematerial" (Unterscheidung zu Verkaufsmaterial?) set DKART-Warengruppe = 16605
		strcpy(zart.BESTANDSBUCHUNG, "1");
		strcpy(zart.CHARGENARTIKEL,  "1");
		strcpy(zart.VERFALL,		 "1");
		strcpy(zart.SKONTOFAEHIG,	 "1");
		
		memset(zart.ZUZAHLUNG_IFA, '0', L_ZARTIKEL_ZUZAHLUNG_IFA );
		memset(zart.RABATTFAEHIG, '0', L_ZARTIKEL_RABATTFAEHIG );
		strcpy(zart.NAHRUNGSERGAENZUNG, "N");
		strcpy(zart.ELEKTROSCHROTT, "N");
		strcpy(zart.PREISSENKUNG, "0");
		strcpy(zart.BSSICHG, "0");
		strcpy(zart.ANBIETERABSCHLAG, "0");
		strcpy(zart.AUTIDEMARTIKEL, "0");
		strcpy(zart.FESTBETRARTIKEL, "0");
		strcpy(zart.REZEPTURARZNEI, "0");
		strcpy(zart.MEDIZINPRODUKT, "0");
		strcpy(zart.IMPFSTOFF, "0");
		strcpy(zart.CE_KENNZEICHEN, "0");
		strcpy(zart.ARZNEIMITTEL, "0");
		strcpy(zart.KONTRAZEPTIVUM, "0");
		strcpy(zart.BIOZID_VERORD, "0");
		strcpy(zart.ZENTRALPPELIST, "0");
		strcpy(zart.EKORIGINALHS, "0");
		strcpy(zart.BESTELL_NUR_OZEK, "0");
		strcpy(zart.HILFSM_VERBRAUCH, "0");
		strcpy(zart.HOMOEOPATHIKUM, "0");
		strcpy(zart.ANTHROPOSOPHIKUM, "0");
		strcpy(zart.PHYTOPHARMAKON, "0");
		strcpy(zart.TREZEPTARZNEI, "0");
		strcpy(zart.AMG_47, "0");
		strcpy(zart.BATTERIEGESETZ, "0");
		strcpy(zart.NEM_PHAGROPRUEFUNG, "0");
		strcpy(zart.NEM_ZERTIFIKAT, "0");
		strcpy(zart.STELLER, "0");
		strcpy(zart.PFLSCHUTZ_VERORD, "0");
		strcpy(zart.BESTELL_NICHT_AUSL, "0");
		strcpy(zart.EAN_NICHTVORHANDEN, "0");
		strcpy(zart.FAELSCH_GEFAHR, "0");
	}
	
	strcpy(zart.ARTIKEL_GESPERRT, "0");
	zart.ARTIKEL_NR = pzn;
	setAender();
	zart.HERSTELLER_NR = ratioph.HERSTELLER_NR;
	strncpy(zart.ARTIKEL_NR_HERST, ratioph.ARTIKEL_NR_HERST, L_ZARTIKEL_ARTIKEL_NR_HERST); 
	ReplaceApostroph(ratioph.ARTIKEL_LANGNAME);
	ConvertUmlaute(ratioph.ARTIKEL_LANGNAME, name50);
	
	// ratioph.ARTIKEL_LANGNAME ist nur 40-stellig; daher die letzten 10 Stellen mit Blanks auffüllen, damit anschließende Vergleiche auch valide sind!
	strncpy(zart.ARTIKEL_LANGNAME, name50, L_ZARTIKEL_ARTIKEL_LANGNAME); 

	pos = Trim(zart.ARTIKEL_LANGNAME);
	
	while (pos < L_ZARTIKEL_ARTIKEL_LANGNAME)
	{
		zart.ARTIKEL_LANGNAME[pos] = ' ';	
		++pos;
	} 
	
	Upper(name50);
	strncpy(zart.ARTIKEL_NAME, name50, L_ZARTIKEL_ARTIKEL_NAME); 
	Trim_All(name50);// ohne Leerzeichen
	strncpy(zart.ARTIKEL_MC, name50, L_ZARTIKEL_ARTIKEL_MC); 
	strcpy(zart.EINHEIT, ratioph.EINHEIT_1); 
	strcat(zart.EINHEIT, ratioph.EINHEIT_2); 
	
	if ( strcmp(ratioph.SPARTE, "01") == 0 )
		strcpy(zart.REZEPTPFL, "1");
	else if ( strcmp(ratioph.SPARTE, "02") == 0 )
		strcpy(zart.APOTHEKENPFL, "1");
	else if ( strcmp(ratioph.SPARTE, "04") == 0 )
		strcpy(zart.PSYCHOTROP, "P");
	else if ( strcmp(ratioph.SPARTE, "07") == 0 )
		strcpy(zart.BTM, "1");
	else if ( strcmp(ratioph.SPARTE, "09") == 0 )
		strcpy(zart.ZYTOSTATIKA, "1");
	else if ( strcmp(ratioph.SPARTE, "11") == 0 )
		strcpy(zart.MEDIZINPRODUKT, "1");

	if ( strcmp(ratioph.KUEHL, "02") == 0 )
		strcpy(zart.KUEHLARTIKEL, "1");
	else if ( strcmp(ratioph.KUEHL, "06") == 0 )
		strcpy(zart.KUEHLARTIKEL, "2");
	else if ( strcmp(ratioph.KUEHL, "04") == 0 )
		strcpy(zart.KUEHLARTIKEL, "3");

	if (ratioph.PREIS > 0.0)
		strcpy(zart.PREIS0ARTIKEL,   "0");
	else
		strcpy(zart.PREIS0ARTIKEL,   "1");
}

/* ------------------------------------------------------------------- */
static void FillCodesBuf(long pzn)
{
	zcodes.ARTICLENO = pzn;
	sprintf(zcodes.ARTICLE_CODE, "%ld", pzn);
	zcodes.SERIAL_NUMBER = 1;
	zcodes.DATE_CHANGED = tages_datum;
	zcodes.PREFERRED_FLAG = 1;
	zcodes.CODE_TYPE = 11;		
}

/* ------------------------------------------------------------------- */
static void FillPreisBuf(long pzn)
{
	zpreis.AEP = ratioph.PREIS; 
	zpreis.GROSSO = ratioph.PREIS;
	zpreis.ARTIKEL_NR = pzn;
	zpreis.DATUMGUELTIGAB = AddDayToPhoDate(tages_datum, 1);
	strcpy(zpreis.KE_MWST, "0");		
}

/* ------------------------------------------------------------------- */
static int Update(long pzn, char* errmld)
{
	if (sel_zartpreis(&Fd_ZArtPreis, pzn, &zpreis, errmld) != 0)
		return -1;

	if (zpreis.AEP != ratioph.PREIS)
	{
		zpreis.AEP = ratioph.PREIS;

		if (ratioph.DATUM > tages_datum) // Datum muss in der Zukunft liegen!
			zpreis.DATUMGUELTIGAB = ratioph.DATUM;
		else
			zpreis.DATUMGUELTIGAB = AddDayToPhoDate(tages_datum, 1);
		
		if (ins_zartpreis(&Fd_ZArtPreis, &zpreis, errmld) != 0)
			return -1;
	}

	if (sel_zartikel(&Fd_ZArtikel, pzn, &zart, errmld) != 0)
		return -1;

	FillArtikelBuf(pzn, 0);

	if (upd_zartikel(&Fd_ZArtikel, &zart, errmld) != 0)
		return -1;

	return 0;
}

/* ------------------------------------------------------------------- */
static int Insert(long pzn, int initBufs, char* errmld)
{
	if ( initBufs == 1 )
	{
		FdInitTabBuf( Fd_CArticleCodes, &zcodes );
		FdInitTabBuf( Fd_ZArtikel, &zart );
		FdInitTabBuf( Fd_ZArtPreis, &zpreis );
	}
	
	FillCodesBuf( pzn );
	if (ins_carticlecodes(&Fd_CArticleCodes, &zcodes, errmld) != 0)
		return -1;

	FillArtikelBuf( pzn, 1 );
	if (ins_zartikel(&Fd_ZArtikel, &zart, errmld) != 0)
		return -1;

	FillPreisBuf( pzn );
	if (ins_zartpreis(&Fd_ZArtPreis, &zpreis, errmld) != 0)
		return -1;

	return 0;
}

/* ------------------------------------------------------------------- */
static int isInactive( )
{
	return (strcmp(ratioph.STATUS, "AG") == 0) ? 1 : 0;
}

/* ------------------------------------------------------------------- */
static int isCreation( )
{
	return (strcmp(ratioph.CHANGE_FLAG, "C") == 0) ? 1 : 0;
}

/* ------------------------------------------------------------------- */
static int isModification( )
{
	return (strcmp(ratioph.CHANGE_FLAG, "M") == 0) ? 1 : 0;
}

/* ------------------------------------------------------------------- */
static void modifyArtNrHerst(  )
{
	char artnrherst [20];
	
	strcpy (artnrherst, "#");
	strcat(artnrherst, zart.ARTIKEL_NR_HERST);
	strncpy(zart.ARTIKEL_NR_HERST, artnrherst, L_ZARTIKEL_ARTIKEL_NR_HERST); 
}

/* ------------------------------------------------------------------- */
static int LoadData( char* errmld )
{
	long pzn_man;
	long pzn_code;
	
	pzn_man = sel_ArtNoByManArt(ratioph.ARTIKEL_NR_HERST);
	
// ***************************************************************************** //
	if ( pzn_man <= 0 ) // SAP-Materialnummer nicht vorhanden
	{
		if( isInactive() )
		{	// keine Anlage von inaktivem Material
			++anz_skipped;
			return 0;
		}
		
		if (atol(ratioph.ARTICLE_CODE) <= 0)
		{
			if ( !isCreation() )
			{	// Materialnummer + PZN nicht bekannt, aber Satz nicht als Anlage gekennzeichnet!
				++anz_skipped;
				return 0;
			}

			// neue Pseudo- PZN aus nummerek ermitteln
			pzn_man = sel_NextPseudoArtNo();
			
			if (pzn_man <= 0)
			{
				strcat(errmld, "Fehler beim Ermitteln einer neuen Pseudo- PZN aus nummerek.");
				return -1;
			}
			
			// Neuanlage Pseudo Artikel / Preis / Code
			if ( Insert(pzn_man, 1, errmld) != 0 )
				return -1;	

			++anz_ins_pseudo;
		}
		// ------------------------------------------------------------------------------ //
		else
		{
			pzn_code = sel_ArtNoByCode(atol(ratioph.ARTICLE_CODE));

			if ( pzn_code <= 0 ) // articlecode nicht vorhanden
			{
				if ( !isCreation() )
				{	// Materialnummer + PZN nicht bekannt, aber Satz nicht als Anlage gekennzeichnet!
					++anz_skipped;
					return 0;
				}

				pzn_code = atol(ratioph.ARTICLE_CODE);
				
				// Neuanlage echter Artikel / Preis / Code
				if ( Insert(pzn_code, 1, errmld) != 0 )
					return -1;

				++anz_ins;
			}
			else
			{
				if ( isModification() )
				{
					// Update der Materialnummer für bestehende, echte PZN
					if ( Update(pzn_code, errmld) != 0 )
						return -1;	

					++anz_upd;
				}
				else if ( isCreation() )
				{
					// Anlage einer neuen MaterialNr für bestehende PZN
					// neue Pseudo- PZN aus nummerek ermitteln
					pzn_man = sel_NextPseudoArtNo();

					// Neuanlage Pseudo Artikel / Preis / Code --> Copy von Original
					if (sel_zartpreis(&Fd_ZArtPreis, pzn_code, &zpreis, errmld) != 0)
						return -1;

					if (sel_zartikel(&Fd_ZArtikel, pzn_code, &zart, errmld) != 0)
						return -1;

					// --> bei bestehender PZN (pzn_code) die Nachfolge-PZN setzen
					setAender();
					zart.ERSATZ_NR = pzn_man;
	
					if (upd_zartikel(&Fd_ZArtikel, &zart, errmld) != 0)
						return -1;

					// --> bei neuer Pseudo-PZN die Original-PZN (pzn_code) setzen	
					zart.ARTIKEL_NR_ORIG = pzn_code;

					if ( Insert(pzn_man, 0, errmld) != 0 )
						return -1;
					
					if ( copy_zartwg(pzn_code, pzn_man, errmld) != 0 )
						return -1;	

					if ( copy_zartaustria(pzn_code, pzn_man, errmld) != 0 )
						return -1;	

					++anz_ins_pseudo;
				}
				else
				{
					// Satz nicht als Änderung oder Anlage gekennzeichnet
					++anz_skipped;
					return 0;
				}
			}
		}
	}
// ***************************************************************************** //
	else // SAP-Materialnummer bekannt
	{
		if ( !isModification() )
		{	// Materialnummer bekannt, aber Satz nicht als Änderung gekennzeichnet!
			++anz_skipped;
			return 0;
		}

		if ( isInactive() ) // Löschen
		{
			if ( sel_zartikel(&Fd_ZArtikel, pzn_man, &zart, errmld) != 0 )
				return -1;		

			// Nachfolge-Pseudo-PZN in zu löschendem Artikel hinterlegt?
			if ( zart.ERSATZ_NR > 0 )
			{
				char artNrHerst [20];

				// ja --> Umschlüsseln der Nachfolge-Pseudo-PZN auf Echt-PZN:
				pzn_code = zart.ERSATZ_NR;
								
				// Löschen Original-PZN (zartpreis, zartwg)
				if (del_zartikel(&Fd_ZArtikel, pzn_man, errmld) != 0)
					return -1;

				if (del_preis_artwg_artaustria(pzn_man, errmld) != 0)
					return -1;
				
				// Einlesen Nachfolge-PZN (Pseudo)
				if (sel_zartikel(&Fd_ZArtikel, pzn_code, &zart, errmld) != 0)
					return -1;
					
				// Nachfolge-PZN (Pseudo) inaktiv setzen
				setAender();
				strcpy(zart.ARTIKEL_GESPERRT, "1");
				strcpy(artNrHerst, zart.ARTIKEL_NR_HERST); // sichern
				modifyArtNrHerst(); 
				zart.ARTIKEL_NR_ORIG = 0;
				zart.ERSATZ_NR = pzn_man;

				if (upd_zartikel(&Fd_ZArtikel, &zart, errmld) != 0)
					return -1;

				if (WritePznPflege(pzn_code, "3A", tages_datum, errmld) != 0)
					return -1;

				if (WritePznPflege(pzn_code, "39", tages_datum, errmld) != 0)
					return -1;

				// Übernahme Nachfolge-PZN (Pseudo) --> Original-PZN (zartikel, zartpreis, zartwg)
				zart.ARTIKEL_NR = pzn_man;

				// Werte zurücksetzen
				strcpy(zart.ARTIKEL_GESPERRT, "0");
				zart.ARTIKEL_NR_ORIG = pzn_code;
				zart.ERSATZ_NR = 0;
				strcpy(zart.ARTIKEL_NR_HERST, artNrHerst); // gesicherten Wert einsetzen
					
				if (ins_zartikel(&Fd_ZArtikel, &zart, errmld) != 0)
					return -1;

				if (copy_zartwg(pzn_code, pzn_man, errmld) != 0)
					return -1;	

				if (copy_zartaustria(pzn_code, pzn_man, errmld) != 0 )
					return -1;	

				if (copy_zartpreis(pzn_code, pzn_man, errmld) != 0)
					return -1;	

				++anz_switched;
			}
			else
			{
				// nein --> Echt-PZN inaktiv setzen = Update für pzn_man:
				setAender();
				strcpy(zart.ARTIKEL_GESPERRT, "1");

				if (upd_zartikel(&Fd_ZArtikel, &zart, errmld) != 0)
					return -1;
			}

			++anz_inactivated;
		}
		// ------------------------------------------------------------------------------ //
		else // Änderung
		{
			if (atol(ratioph.ARTICLE_CODE) <= 0)
			{
				// existierende Pseudo-PZN
				// Update Artikel / Preis
				if ( Update(pzn_man, errmld) != 0 )
					return -1;

				++anz_upd;
			}
			else
			{
				pzn_code = sel_ArtNoByCode(atol(ratioph.ARTICLE_CODE));

				if ( pzn_code <= 0 ) // articlecode nicht vorhanden
				{
					// bisher nur Pseudo-PZN angelegt - jetzt Lieferung der echten PZN 
					// --> Umschlüsseln Pseudo-PZN auf Echt-PZN:
					pzn_code = atol(ratioph.ARTICLE_CODE);

					// Neuanlage Echt- Artikel / Preis / Code --> Copy von Pseudo
					if (sel_zartpreis(&Fd_ZArtPreis, pzn_man, &zpreis, errmld) != 0)
						return -1;

					if (sel_zartikel(&Fd_ZArtikel, pzn_man, &zart, errmld) != 0)
						return -1;

					// --> bei bestehender Pseudo- PZN (pzn_man) die Nachfolge-PZN setzen
					setAender();
					zart.ERSATZ_NR = pzn_code;
					strcpy(zart.ARTIKEL_GESPERRT, "1");
					
					modifyArtNrHerst(); 
		
					if (upd_zartikel(&Fd_ZArtikel, &zart, errmld) != 0)
						return -1;

					if (WritePznPflege(pzn_man, "39", tages_datum, errmld) != 0)
						return -1;

					// --> bei neuer Echt-PZN die Original-PZN (pzn_man) setzen	
					zart.ARTIKEL_NR_ORIG = pzn_man;

					if ( Insert(pzn_code, 0, errmld) != 0 )
						return -1;
					
					if ( copy_zartwg(pzn_man, pzn_code, errmld) != 0 )
						return -1;	

					if ( copy_zartaustria(pzn_man, pzn_code, errmld) != 0 )
						return -1;	

					++anz_switched;
				}
				else // pzn_code == pzn_man ODER pzn_code != pzn_man
				{
					// pzn_code != pzn_man kann vorkommen, wenn es zu einer PZN noch Ursprungs- und Nachfolge-MatNr gibt und Ursprung noch nicht inaktiv gemeldet wurde
					// Update existierenden Artikel / Preis
					if ( Update(pzn_man, errmld) != 0 )
						return -1;

					++anz_upd;
				}
			}
		}
	}
// ***************************************************************************** //

	return 0;
}

/* ------------------------------------------------------------------- */
static int PwLieferung( char *errmld )
{
	int status;
	char zeile[NO_SIGNS + 1];
	char msg[100];

	line_nr = 0;
	status = 0;
	while ( status == 0 )/*SCHLEIFE zum Lesen aller Datenzeilen*/
	{
		status = GetPwZeile( fd_file, zeile );
		line_nr++;	
			
		if (status == 0)
		{
			if ( LineToStruct( zeile, errmld ) == 0 )
			{
				if ( LoadData (errmld) != 0 )
					status = 3;
			}
			else 
				status = 3;
		}
	}

	if (status != 2) 
	{
		sprintf(msg, "Error on reading pw datafile - line <%ld>; file not read to the end!", line_nr);
		strcat(errmld, msg);
	}
	else
		status = 0;/*EOF*/
	
   ClosePwDatei( fd_file );
   fd_file = NULL;

   // CloseProtDatei ( fd_prot );
   fd_prot = NULL; 
   
   return status;
}

/* ------------------------------------------------------------------- */
static long GenArtik( char *db, char* ili_file, char* prot_file, char *errmld )
{
   int status;
   char today[9];
   char acttime[7];
   char *protday;
   long time;
   	
   tages_datum = GetPhoDate();
   time = GetPhoTime();
   
   fd_file = NULL;
   fd_prot = NULL;

   strcat(prot_file, PROTNAME );
   sprintf(today, "%ld", tages_datum);
   protday = today;
   protday = protday + 2;
   strcat(prot_file, protday );
   sprintf(acttime, "%06ld", time);
   strcat(prot_file, "_" );
   strcat(prot_file, acttime );   
   strcat(prot_file, PROTEND );
   
   /*öffnen des Daten-Files und Protokoll-File*/
   status = OpenPwDatei( &fd_file, ili_file, errmld );
   if ( status != 0 )
   {
       sprintf(errmld, "pw-file not found under path %s\n", ili_file);
	   return status;
   }
   
   // status = OpenProtDatei( &fd_prot, prot_file, tages_datum, time, errmld );
   if ( status != 0 )
   {
       strcat(errmld, "not able to open protocol-file\n");
	   return status;
   } 

    if ( OpenBase( db, errmld ) == 0 )
    {
        OpenPflege( (char*)user, errmld );
		
		Fd_ZArtikel = -1;
		Fd_ZArtPreis= -1;
		Fd_CArticleCodes = -1;

		if ( OpenBufferDesc( &Fd_CArticleCodes, "carticlecodes", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 
			&& OpenBufferDesc( &Fd_ZArtikel, "zartikel", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0
			&& OpenBufferDesc( &Fd_ZArtPreis, "zartpreis", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0)
		{
			status = PwLieferung ( errmld );
		}
		else
			status = 1;

		CloseOneBufferDesc(Fd_ZArtikel);
		CloseOneBufferDesc(Fd_ZArtPreis);
		CloseOneBufferDesc(Fd_CArticleCodes);

        CloseBase( );
    }
	else
		status = 1;

   return status;
}

/* ------------------------------------------------------------------- */
long GenPwArtik( char *db, char *ili_direc, char *errmld )
{
	char *ili_file;
	char *prot_file;
	int status;
	char msg[500];
  
#if !defined(WIN32)
    char meld[100];
	char *verz2;
#endif
  
    ili_file = malloc( strlen( ili_direc ) + 10 );
	prot_file = malloc( strlen( ili_direc ) + 50 );
    if ( ili_file == NULL || prot_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler GenPwArtik" );
       return 1;
    }

	#ifdef WIN32
		strcpy( prot_file, "C:/temp/" ); /* for debug; write protokol to file-directory */
	#else
		verz2 = getcwd(prot_file, 813);

		strcpy (prot_file, verz2); 
		strcat (prot_file, "/../data/pwartik/protokoll"); // verzeichnis vor erster Nutzung anlegen !!!
	#endif

	strcpy( ili_file, ili_direc );

	status = GenArtik( db, ili_file, prot_file, errmld );

    free( ili_file );
	free( prot_file );
    
	sprintf( msg,	 "\n%ld Datenzeilen verarbeitet\n" 
					 "%ld Artikel erfolgreich geaendert\n" 
                     "%ld Artikel erfolgreich neu angelegt\n" 
					 "%ld Pseudo-Artikel erfolgreich neu angelegt\n" 
					 "%ld Artikel erfolgreich inaktiviert\n" 
					 "%ld Artikel erfolgreich umgeschluesselt\n" 
					 "%ld Datensaetze ueberlesen.",
					 line_nr -1, anz_upd, anz_ins, anz_ins_pseudo, anz_inactivated, anz_switched, anz_skipped);

	if ( status == 0 )
		strcpy (errmld, msg);
	else
		strcat (errmld, msg);

    return status;
}


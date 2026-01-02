/* ---------------------------------------------------------------------- *
 *   Aufgabe        : Preise bei Mwst-Änderungen umrechnen                *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 29.11.2006                                          *
 *   Autor          : Hoerath                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.6.2.4 : zpcalcprice 14/09/2021 Olaf Wasmuth";
}

/*!
\page page6 zpcalcprice - Preise bei Mwst-Änderungen umrechnen

________________________________________________________________________________________
\version	1.6.2.4
\date		14.09.2021
\internal
- OW: CPR-200938 Aufnahme neuer Voodoo-Table-Header für erweiterte zartpreis Tabelle
\endinternal
________________________________________________________________________________________
\version	1.6.2.3
\date		16.06.2021
\internal
- MH: Aenderung Grosso-Berechnung gem. CPR-210586
\endinternal
________________________________________________________________________________________
\version	1.6.2.2
\date		11.05.2021
\internal
- MH: Umstellung Grosso-Berechnung auf cppediscounts
\endinternal
________________________________________________________________________________________
\version	1.6.2.1
\date		29.11.2019
\internal
- RR: durchkompiliert wegen Erweiterung zartfrance.
\endinternal
________________________________________________________________________________________
\version	1.6.2.0
\date		16.04.2018
\internal
- TH: neuer Mode 8: Berechung der Importpreise für D-Besorger AT.
\endinternal
________________________________________________________________________________________
\version	1.6.1.1
\date		22.02.2017
\internal
- TH: SR-17017244 herst_prozent für mode 6 sofort (nicht erst bei erreichen des Gültigkeitsdatums aus PPE) setzen
\endinternal
________________________________________________________________________________________
\version	1.6.1.0
\date		05.10.2016
\internal
- TH: CR-16A023 Änderung bei LPPR- Erstattung.
\endinternal
________________________________________________________________________________________
\version	1.6.0.3
\date		13.01.2016
\internal
- TH: wg INC-16000905 Änderung aus Version 1.6.0.1 zurückgenommen - wird via zpdailyclosing gelöst.
\endinternal
________________________________________________________________________________________
\version	1.6.0.2
\date		16.07.2015
\internal
- TH: Erweiterung zartikel.
\endinternal
________________________________________________________________________________________
\version	1.6.0.1
\date		07.01.2015
\internal
- TH: Berechnen von reimbursement_val bei Änderung AVP via zputil. (SR-15000393).
\endinternal
________________________________________________________________________________________
\version	1.6.0.0
\date		29.04.2014
\internal
- RR: neuer Mode 7: Übertragung Erstattungswerte Frankreich; Umstellung aller Parameter-Datumsprüfungen auf CheckDate().
\endinternal
________________________________________________________________________________________
\version	1.5.0.7
\date		10.04.2014
\internal
- TH: wandeln mit neuer zartikel/zartpreis-Struktur.
\endinternal
________________________________________________________________________________________
\version	1.5.0.6
\date		11.03.2014
\internal
- TH: Erweiterung zartikel.
\endinternal

*/


/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

/*  1.0.0.1 07/07/2008 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						   Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/*  1.0.0.2 17/12/2008 RR: Korrektur Rundungsfehler in kf_rund.c */
/*  1.1.0.0 30/07/2009 TH: neuer Mode 3: prozentuale Umrechnung von AVPs ohne Taxen. */
/*  1.2.0.0 12/10/2010 TH: neuer Mode 4: AMNOG. */
/*  1.2.0.1 12/11/2010 TH: Amnog erst ab 2012 */
/*  1.2.0.2 29/11/2010 TH: Amnog- Übergangslösung 2011 */
/*  1.2.0.3 08/11/2011 TH: Anpassungen für Amnog 2012 */
/*  1.2.0.4 25/07/2012 TH: voodoo table header */
/*  1.3.0.0 13/12/2012 TH: neuer Mode 5: Tax-Umstellung D 2013.*/
/*  1.4.0.0 14/12/2012 TH: neuer Mode 6: Berechnung Grosso = LBP - ppetotaldiscpct (für CH).*/
/*  1.4.0.1 14/12/2012 RR: keine Taxtabelle für Mode 3 lesen */
/*  1.4.0.2 09/01/2013 TH: neu kompilieren wegen Erweiterung zartpreis.*/
/*  1.5.0.0 14/03/2013 TH: AIX build + changes mode 6.*/
/*  1.5.0.1 04.06.2013 TH: Erweiterung zartpreis */
/*  1.5.0.2 03/07/2013 TH: Anpassung Mode 5: Tax-Umstellung D 08.2013.*/
/*  1.5.0.3 02/10/2013 TH: bugfix rc für mode 6, wenn keine Daten für Umrechnung vorhanden.*/
/*  1.5.0.4 31/12/2013 TH: ke_mwst=2 für mode 3 (für Kroatien).*/
/*  1.5.0.5 14/01/2014 TH: mode 6 - zartikel.herst_prozent auch versorgen, wenn lbp = 0 (SR-111533).*/
/*  1.5.0.6 11.03.2014 TH: Erweiterung zartikel */
/*  1.5.0.7 10.04.2014 TH: wandeln mit neuer zartikel/zartpreis-Struktur */
/*  1.6.0.0 29.04.2014 RR: neuer Mode 7: Übertragung Erstattungswerte Frankreich; */
/*						   Umstellung aller Parameter-Datumsprüfungen auf CheckDate() */
/*  1.6.0.1 07.01.2015 TH: Berechnen von reimbursement_val bei Änderung AVP via zputil. (SR-15000393) */
/*  1.6.0.2 16.07.2015 TH: Erweiterung zartikel */


long CalcAvpLoop ( char *db, char *cMwstKz, char *cDatumGueltAb, char *cArtNr, char *buf );
long CalcFpLoop  ( char *db, char *cMwstKz, char *cDatumFB1, char *cArtNr, char *buf );
long CalcAvpWithoutTaxLoop ( char *db, char *cMwstKz, char *cDatumGueltAb, char *cArtNr, char *buf );
long CalcAmnogLoop ( char *db, char *cTaxKz, char *cDatumGueltAb, char *cArtNr, char *buf );
long CalcAvpTaxLoop ( char *db, char *cTaxKz, char *cDatumGueltAb, char *cArtNr, char *buf );
long CalcGrossoFromLbpLoop ( char *db, char *cDateCurrent, char *cDateTo, char *cArtNr, char *buf );
long TransferNewRefundValuesLoop ( char *db, char *cDateFrom, char *cDateTo, char *cArtNr, char *buf );
long CalcImportLoop ( char *db, char *dbexport, char *cDatumGueltAb, char *cArtNr, char *buf );

/* ------------------------------------------------------------------- */
#define SQL_SETISOLA_ERROR   (-554)
void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

/* ------------------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld )
{
   long s;

   char base[50];
   strcpy( base, "database " );
   strcat( base, db );

   s = SqlExecuteImm( base );
   if ( s != 0 )
   {
      strcpy( errmld, base );
      strcat( errmld, ": " );
      strcat( errmld, DynErrmld() );
      return s;
   }

   s = SqlExecuteImm("set isolation to dirty read" );
   if ( s == SQL_SETISOLA_ERROR ) s = 0;
   if ( s != 0 )
   {
     strcpy( errmld, "set isolation: " );
     strcat( errmld, DynErrmld() );
     CloseBase( );
     return s;
   }

   s = SqlExecuteImm( "SET LOCK MODE TO WAIT 10" );
   if ( s == SQL_SETISOLA_ERROR ) s = 0;
   if ( s != 0 )
   {
     strcat( errmld, "set lock mode: ");
     strcat( errmld, DynErrmld() );
     CloseBase( );
     return s;
   }
   return 0;
}

/* ---------------- Programm-Ausahl ----------------- */
static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

/* ---------------------------------------------------------------------- */
static void LadeUsage( char *buf )
{
	strcat( buf, "- zpcalcprice 1 database mwst-kz datumgueltigab [pzn] \n"											\
				 "		Neuberechnung aller AVPs von Tax-Artikeln (taxpfl > 0).\n"									\
                 "		mwst-kz:        0 = alle Artikel mit voller Mwst.\n"										\
			     "		datumgueltigab:	Datum (dd.mm.yyyy), mit dem Preise in zartpreis eingestellt werden.\n\n"	\
			     "- zpcalcprice 2 database mwst-kz datum_festbetrag1 [pzn] \n"										\
                 "		Neuberechnung aller Festpreise zum Tagesdatum.\n"											\
                 "		mwst-kz:           0 = alle Artikel mit voller Mwst.\n"										\
			     "		datum_festbetrag1: Datum (dd.mm.yyyy), das zum Festpreis in zartikel eingestellt\n"			\
				 "		                   wird.\n\n"																\
			     "- zpcalcprice 3 database mwst-kz datumgueltigab [pzn] \n"											\
                 "		prozentuale Umrechnung von AVPs ohne Taxen (fuer Artikel, deren AVP aktuell > 0 ist)\n"		\
				 "		--> aus Herst_Prozent bzw. wg neuer Mwst.\n"												\
                 "		mwst-kz:        0 = alle Artikel mit voller Mwst.\n"										\
			     "		datumgueltigab:	Datum (dd.mm.yyyy), mit dem Preise in zartpreis eingestellt werden.\n\n"	\
			     "- zpcalcprice 4 database tax-kz datumgueltigab [pzn] \n"											\
                 "		Neuberechnung AEP aus Tax-Art 6 (Basis aktueller Grosso), AVP aus neuem AEP.\n"				\
                 "		tax-kz:         2 / 3 = alle Artikel mit Tax-Kz 2 / 3.\n"									\
			     "		datumgueltigab:	Datum (dd.mm.yyyy), mit dem Preise in zartpreis eingestellt werden.\n\n"	\
			     "- zpcalcprice 5 database tax-kz datumgueltigab [pzn] \n"											\
                 "		Neuberechnung AVPs aus AEP mit Tax-Art 8 --> Tax-Umstellung in D 08.2013 \n"				\
				 "		(nur fuer Artikel, die nicht von IFA geliefert werden!).\n"									\
                 "		tax-kz:         2 = alle Artikel mit Tax-Kz 2.\n"											\
			     "		datumgueltigab:	Datum (dd.mm.yyyy), mit dem Preise in zartpreis eingestellt werden.\n\n"	\
			     "- zpcalcprice 6 database datecurrent dateto [pzn] \n"												\
                 "		Berechnung Grosso aus LBP - cppediscounts.ppetotaldiscpct \n"								\
				 "		--> fuer CH, nur wenn LBP > 0 und Grosso <= Aep.\n"											\
                 "		datecurrent:  Datum (dd.mm.yyyy); es werden nur Artikel berechnet, \n"						\
				 "		              fuer die cppediscounts.datefrom > datecurrent ist.\n"						\
			     "		dateto:		  Datum (dd.mm.yyyy); fuer cppediscounts.datefrom <= dateto, \n"				\
				 "		              zartikel.herst_prozent versorgen.\n"											\
			     "		bei Angabe einer PZN erfolgt die Umrechnung nur fuer diesen Artikel, sonst fuer alle\n\n"	\
			     "- zpcalcprice 7 database datefrom dateto [pzn] \n"												\
                 "		Übertragung neue Erstattungswerte aus cartrefundfrance in aktuelle (zartfrance) \n"			\
				 "		sowie danach loeschen der verarbeiteten Saetze aus cartrefundfrance (Frankreich) \n"		\
                 "		datefrom: Datum (dd.mm.yyyy); Von-Datum fuer Selektion aus zapflege \n"						\
                 "		dateto:   Datum (dd.mm.yyyy); Bis-Datum fuer Selektion aus zapflege \n"						\
			     "		bei Angabe einer PZN erfolgt die Umrechnung nur fuer diesen Artikel, sonst fuer alle\n\n"	\
				 "- zpcalcprice 8 database dbexport datumgueltigab [pzn] \n"										\
                 "		Neuberechnung aller aktuellen und künftigen Preise für D-Besorger \n"						\
				 "			mit %-Aufschlag aus cimportarticleparam \n"												\
				 "		dbexport:	Datenbank, aus der die Basispreise des Exportlandes gelesen werden.\n\n"		\
			     "		datumgueltigab:	Datum (dd.mm.yyyy), mit dem Preise in zartpreis eingestellt werden.\n\n"	\
			     "		bei Angabe einer PZN erfolgt die Umrechnung nur fuer diesen Artikel, sonst fuer alle\n\n"	);
	// User: direkt im Programm vergeben
	// mwst_alt / mwst_neu: aus filiale gelesen
}

/* ---------------------------------------------------------------------- */
void ProgUsage( char *buf )
{
   Usage( buf );
   LadeUsage( buf );
}

/* ---------------------------------------------------------------------- */
long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   switch ( *argv[0] )
   {
    case '1': //AVP´s
        if ( argc == 4 )
        {
           s = CalcAvpLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
		else if ( argc == 5 )
		{
		   s = CalcAvpLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

	case '2': //Festpreise
        if ( argc == 4 )
        {
           s = CalcFpLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
		else if ( argc == 5 )
		{
		   s = CalcFpLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

	case '3': //Umrechung AVP´s ohne Taxen
        if ( argc == 4 )
        {
           s = CalcAvpWithoutTaxLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
		else if ( argc == 5 )
		{
		   s = CalcAvpWithoutTaxLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;


	case '4': // Amnog = Neuberechnung AEP aus Tax-Art 6
        if ( argc == 4 )
        {
           s = CalcAmnogLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
		else if ( argc == 5 )
		{
		   s = CalcAmnogLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

	case '5': // Neuberechnung AVP aus AEP (Wg Taxumstellung D 08.2013)
        if ( argc == 4 )
        {
           s = CalcAvpTaxLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
		else if ( argc == 5 )
		{
		   s = CalcAvpTaxLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

	case '6': // Berechnung Grosso aus LBP
        if ( argc == 4 )
        {
           s = CalcGrossoFromLbpLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
		else if ( argc == 5 )
		{
		   s = CalcGrossoFromLbpLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

	case '7': // Übertragung Erstattungswerte Frankreich
        if ( argc == 4 )
        {
           s = TransferNewRefundValuesLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
		else if ( argc == 5 )
		{
		   s = TransferNewRefundValuesLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

    case '8': //D-Besorger
        if ( argc == 4 )
        {
           s = CalcImportLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
		else if ( argc == 5 )
		{
		   s = CalcImportLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;


	default:
        s = 1;
        strcpy( buf, "Programm-Teil: " );
        strcat( buf, argv[0] );
        strcat( buf, " nicht vorhanden" );
        break;
     }

	 return s;
}

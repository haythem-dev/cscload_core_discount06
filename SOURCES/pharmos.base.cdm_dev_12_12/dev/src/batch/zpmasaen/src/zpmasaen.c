/* ---------------------------------------------------------------------- *
 *                            ZPMASAEN. C                                 *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Massenaenderungen Artikel                           *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 09.07.98                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 4.1.2 : zpmasaen 05/12/2024 R.Erkens";
}


/*!
\page page30 zpmasaen - Massenaenderungen Artikel

___________________________________________________________________________
\version	4.1.2
\date		05.12.2024
\internal
- RE: I-24104953 = Kriterium fuer Loeschung interner PZN's hinzugefuegt
\endinternal
___________________________________________________________________________
\version	4.1.1
\date		05.08.2024
\internal
- RE: CPR-220781 = Entfernen der Pflege Aufrufe im Loeschprozess
\endinternal

___________________________________________________________________________
\version	4.1.0
\date		03.07.2024
\internal
- RE: CPR-220781 = Neue Version Loeschprozess fuer Artikel (ohne eklibs)
\endinternal

___________________________________________________________________________
\version	4.0.1
\date		25.08.2021
\internal
- OW: CPR-200938 = Unterstuetzung des AGP (i.e. Amedis Grundpreis, CH)
\endinternal

___________________________________________________________________________
\version	4.0.0
\date		10.04.2018
\internal
- TH: CPR-170659 = Löschen von cimexblock + cexportarticle + cimexmanufacturermapping
\endinternal

___________________________________________________________________________
\version	3.9.9
\date		22.02.2017
\internal
- TH: CR-16D056 = Löschen von zchargenrueckruf
\endinternal
___________________________________________________________________________
\version	3.9.8
\date		17.11.2016
\internal
- TH: Löschen von cimexpermission + clppr2article
\endinternal
 \customer
	\de 
Löschen von cimexpermission + clppr2article
	\en 
deleting of cimexpermission + clppr2article
\endcustomer
___________________________________________________________________________
\version	3.9.7
\date		01.04.2016
\internal
- RR: Erweiterung Lagerortprüfung bei Setzen Sperrkennzeichen für Lauf in Deutschland
- internal change to enable the automatic setting of the blocked-flag for articles that are out of sale also in Germany
\endinternal
___________________________________________________________________________
\version	3.9.6
\date		16.07.2015
\internal
- TH: Erweiterung zartikel
\endinternal
___________________________________________________________________________
\version	3.9.5
\date		26.05.2015
\internal
- TH: ctransfercsc jeden Abend komplett löschen
\endinternal
___________________________________________________________________________
\version	3.9.4
\date		27.10.2014
\internal
- TH: Löschen von ctransfercsc
\endinternal
___________________________________________________________________________
\version	3.9.3
\date		18.07.2014
\internal
- TH: Löschen von cartpriceext
\endinternal
___________________________________________________________________________
\version	3.9.2
\date		16.07.2014
\internal
- TH: Usage 14 zum Beenden von cgibatchentry = CR-12P032.
\endinternal
___________________________________________________________________________
\version	3.9.1
\date		12.05.2014
\internal
- TH: Usage 13 zum Ändern von Artikel-KZ, abhängig von Wirkstoff(typ) = CR-13P047.
\endinternal

*/

/* 3.0.2  21.12.2000 V_PROTO_VERTEIL bei zartikel und zartpreis ( vorher V_PROTOKOL ) */
/* 3.0.3  06.07.2001 neue Felder in zartikel NAHRUNGSTEST, NAHRUNGSERGAENZUNG */
/* 3.0.4  17.07.2001 neuer Programmpunkt: Loeschkennzeichen setzen */
/* 3.0.5  29.11.2001 artve, artnrbl, bliesort loeschen + auf V_PROTO_VERTEIL UMSTELLEN ( ARTLOE.C ) */
/* 3.0.6  22.04.2002 Relation ZARTLOESCH ( artloe.c ), auf wpp_... umstellen */
/* 3.0.7  24.05.2002 ZARTIKEL: PREISSENKUNG, HERSTEL: HERSTELL_VERGUETET, ERSTATTUNGSTAGE */ 
/* 3.0.8  03.06.2002 autidem.c: ZARTIKEL: PREISSENKUNG Schnellerfassung */ 
/* 3.0.9  30.07.2002 Feld ORIGINALKARTON in ARTVE ( artloe ) */
/* 3.1.0  13.12.2002 Feld BSSICHG in ZARTIKEL  */
/* 3.1.1  24.01.2003 Felder ANBIETERABSCHLAG, AUTIDEMARTIKEL, */
/*                   FESTBETRARTIKEL, DATUM_ABSCHLAG in ZARTIKEL  */
/* 3.1.2  06.03.2003 Neue Felder  REZEPTURARZNEI MEDIZINPRODUKT IMPFSTOFF CE_KENNZEICHEN  */
/*                   ARZNEIMITTEL KONTRAZEPTIVUM in ZARTIKEL ( - ) */
/* 3.1.3  11.06.2003 SQL-Fehler 201 bei SqlOpenCs bliesort ???  Grund nicht gefunden */
/*                   Aenderung: bei Delete_Sekbez: char m_PrimekeyCond[50] -> char m_PrimekeyCond[100] */
/* 3.1.4  13.06.2003 Feld ZENTRALPPELIST in ZARTIKEL  */
/* 3.1.5  03.07.2003 Restliche Artikel loeschen  */
/* 3.1.6  01.08.2003 neues Feld EKORIGINALHS */
/* 3.1.7  31.10.2003 Umstellung auf variable Datenbank  */
/* 3.1.8  13.11.2003 Neues Feld HILFSM_VERBRAUCH in zartikel */
/* 3.1.9  18.02.2004 Pflege artpreis ausschalten (MIT_ARTPREIS_PFLEGE) */
/* 3.2.0  20.03.2004 Neues Feld EAVP in zartpreis ( EAVP mit 0 vorbesetzt ) */
/* 3.2.1  23.03.2004 Neues Feld EAVP in zartpreis ( EAVP uebergeben ) */
/* 3.2.2  17.11.2004 RR: wandeln mit neuer herstel-Struktur */
/* 3.2.3  08.12.2004 RR: neuer Parameter Landeskürzel für Artikel-Löschen (zartaustria löschen) */
/*                       außerdem Hajo-Problem vom 11.06.03 geloest (trat auf bei besla_nr = 0 im Delete_Bliesort */
/* 3.2.4  06.04.2005 TH: wandeln mit neuer zartikel-Struktur (psychotrop) */
/* 3.2.5  23.06.2005 RR: bei aut-idem (Parameter 5) auch Werte 4 und 5 für Preissenkung zulassen */
/* 3.2.6  27.06.2005 RR: ändern "select *" in "select PROJECTION_xxx" */
/* 3.2.7  29.06.2005 RR: bei Artikel-Löschung auch zchargenrueckruf und cartcompack löschen */
/* 3.2.8  30.08.2005 RR: bei Artikel-Löschung in CH auch zartswitzerland und carticlelang löschen */
/* 3.2.9  30.08.2005 RR: neue Funktion für CH: setzen Sperrkennzeichen bis AH-Datum */
/* 3.3.0  31.08.2005 RR: neuer Parameter Landeskürzel für Löschkennzeichen-Setzen (wg. Abfrage datum_ifaloesch) */
/* 3.3.1  26.01.2006 RR: artikelmgpreis rausgenommen (wird auf pps1 nicht benötigt) */
/* 3.3.2  12.09.2006 RR: neue Funktion: löschen Chargenrückrufe bis zu einem bestimmten Datum + Ausgabe logfile */
/* 3.3.3  14.09.2006 RR: Änderungen zum Online-Debuggen */
/* 3.3.4  30.10.2006 RR: Funktion Restliche Artikel loeschen (3.1.5) lauffähig gemacht */
/* 3.3.5  06.11.2006 TH: Usage 9 - Preise für Euro-Artikel in Kroatien umrechnen */
/* 3.3.6  06.11.2006 TH: Preise für Euro-Artikel in Kroatien umrechnen: nur Grosso! */
/* 3.3.7  27.11.2006 TH: Protokoll für Usage 9 */
/* 3.3.8  07.12.2006 TH: Protokoll für Usage 9 angepasst */
/* 3.3.9  12.12.2006 TH: Protokoll für Usage 9 - Artikelbestände andrucken */
/* 3.4.0  05.04.2007 RR: löschen zartcroatia und zartfrance in HR / F bei Artikellöschung sowie cdiscount */
/* 3.4.1  11.04.2007 RR: neue Funktion Rabatte löschen (bestehende Usage 8, mit neuem Parameter mode) */
/* 3.4.2  15.06.2007 RR: neuer Wert '9' für Preissenkung zulassen, versorgen datum_preissenkung, falls nötig */
/* 3.4.3  02.07.2007 RR: carticlecodes beim Artikel-Löschen mitberücksichtigen */
/* 3.4.4  21.08.2007 TH: Anpassungen an Protokoll für Usage 9 - Bestandswertdifferenzen */
/* 3.4.5  07.09.2007 TH: Anpassungen für Usage 9, so dass Msg an EkZdp gesendet wird */
/* 3.4.6  05.10.2007 RR: neue Funktion Preiserhöhungen löschen (bestehende Usage 8, mode 3) */
/* 3.4.7  30.05.2008 RR: bei Rabattlöschungen Aktionen mit PZN = 0 berücksichtigen (PrimeKey, zgrppflege */
/* 3.4.8  04.07.2008 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						 Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 3.4.9  04.09.2008 RR: eigentlich nur im chargloe.c die Fehlermeldung erweitert, um einen Abbruch in Österreich
						 nachvollziehen zu können, komischerweise läuft das Programm nach dieser Änderung plötzlich 
						 durch, daher neue Version erstellt, um überall wieder einen Stand zu haben. */
/* 3.5.0  09.09.2008 RR: Abfrage auf DB pps1hr durch zpps2hr ersetzt, 
						 bei Preisänderungen (mode 1) für die Schweiz keinen AEP abfragen, für Nicht-Deutschland keinen EAVP */
/* 3.5.1  01.12.2008 RR: kompiliert mit neuer wdbups-Version (Überlauf abgefangen bei Massenlöschung) */
/* 3.5.2  04.12.2008 RR: Fehlerkorrektur bei Euro-Umrechnung (Übergabe long* statt int* in ReadQtyInStock */
/* 3.5.3  03.06.2009 RR: bei Artikellöschung zartverk löschen + zpznpflege schreiben */
/* 3.5.4  31.08.2009 TH: Usage 10 zum Umrechnen von Preisen auf Basis ccurrency, cartforeigncurr, cexchangeratio */
/* 3.5.5  14.10.2009 RR: sql-String beim cdiscount-Löschen vergrößert (war zu klein wg. neuen Feldern) */
/* 3.5.6  07.12.2009 RR: exchange_rate in cartforeigncurr & zartcroatia von 7,5 auf 12,6 vergrößert */
/* 3.5.7  23.12.2009 RR: löschen zartbulgaria und zartserbia in BG / RS bei Artikellöschung sowie ccpvalidityperiod, 
						 Ausgabe Anzahl der gelöschten Sätze pro Tabelle */
/* 3.5.8  23.08.2010 RR: Tabelle vzartinfo in restloe.c aufgenommen */
/* 3.5.9  26.08.2010 RR: Länge des SQL-Strings für zartikel-Select in autidem.c vergrößert */
/* 3.6.0  09.02.2011 TH: neu kompiliert wegen Erweiterung von zartcroatia */
/* 3.7.0  29.11.2011 TH: Usage 11 zum Kopieren von Rabatten */
/* 3.7.1  02.12.2011 TH: bei Usage 2 wird nun auch die Tabelle csafetydatasheet gelöscht.*/
/* 3.7.2  01.03.2012 TH: Usage 12 zum Sperren von Pseudo- Artikeln in BG.*/
/* 3.7.3  25.07.2012 TH: UnixFoundation.*/
/* 3.7.4  04.10.2012 TH: Löschen carticlecodes erst bei "Restlöschen" (mode 6), nicht bei Mode 2.*/
/* 3.7.5  09.01.2013 TH: neu kompiliert wegen Erweiterung von zartpreis */
/* 3.8.0  15.03.2013 TH: AIX build */
/* 3.8.1  04.06.2013 TH: Erweiterung zartpreis */
/* 3.9.0  08.04.2014 TH: Erweiterung zartpreis / zartikel; Löschen von carticleext + cartrefundfrance */
/* 3.9.1  12.05.2014 TH: Usage 13 zum Ändern von Artikel-KZ, abhängig von Wirkstoff(typ) = CR-13P047.*/
/* 3.9.2  16.07.2014 TH: Usage 14 zum Beenden von cgibatchentry = CR-12P032.*/
/* 3.9.3  18.07.2014 TH: Löschen von cartpriceext */
/* 3.9.4  27.10.2014 TH: Löschen von ctransfercsc */
/* 3.9.5  26.05.2015 TH: ctransfercsc jeden Abend komplett löschen*/
/* 3.9.6  16.07.2015 TH: Erweiterung zartikel */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hdatum/phodate.h"
#include "libscsvoodoo/libscsvoodoo.h"
#include "zpmasaen_common.h"

/* ----- Prototype --------- */

/* ------------ Massenaenderung Preise ------------------- */

long PreisLoop(int argc, char **argv, char *buf);

void PreisUsage( char *buf );

/* ------------ Artikel mit Loeschkennzeichen loeschen ----------- */

long ArtLoeLoop ( char *db, char *user, char *lkz, char *cArtNr, char *buf );
void ArtLoeUsage( char *buf );

/* ------------ Restliche Artikel loeschen ----------- */

long RestArtLoeLoop ( char *db1, char *db2, char *cArtNr, char *buf );
void RestArtLoeUsage( char *buf );

/* ------------ Hersteller ab Loeschdatzum loeschen ----------- */

long HerLoeLoop ( char *db, char *user, char *cLoedatum, char *buf );
void HerLoeUsage( char *buf );

/* ------------ Loeschkennzeichen in Artikel setzen ----------- */

long SetLoekennLoop ( char *db, char *user, char *datumstr, char *lkz, char *buf );
void SetLoekennUsage( char *buf );

/* ------------ Autidem --------------------------------------- */

long AutidemLoop ( char *db, char *user, char *cHnr, 
                   char *autidem_alt, char *autidem_neu, 
                   char *buf );
void AutidemUsage( char *buf );

/* ------------ PznAlt nach PznNeueise ------------------- */
/*
long PznAlt2NeuLoop ( char *user, char *cPznAlt, char *cPrnNeu, char *buf );
void PznAlt2NeuUsage( char *buf );
*/

/* ------------ Sperrkennzeichen in Artikel setzen ----------- */

long SetSpekennLoop ( char *db, char *user, char *datumstr, char *buf );
void SetSpekennUsage( char *buf );

/* ------------ Artikel-Kennzeichen abhängig vom Wirkstofftyp ändern ----------- */

long UpdArticleFlagsByIngredientTypeLoop ( char *db, char *user, char *wirkstoffnr, char *ingredienttype_old, char *ingredienttype_new, char *buf );
void UpdArticleFlagsByIngredientTypeUsage( char *buf );

/* ------------ Chargen ab Anlagedatum / Rabatte bis Ablaufdatum loeschen ----------- */

long ChargLoeLoop ( char *mode, char *db, char *user, char *cLoedatum, char *buf );
void ChargLoeUsage( char *buf );

/* ------------ Preise für Euro-Artikel in Kroatien umrechnen ----------- */

long CalcEuroArtHrLoop ( char *db, char *user, char* prot_file, char *cArtNr, char *buf );
void CalcEuroArtHrUsage( char *buf );

/* ------------ Preise für Euro-Artikel in Kroatien umrechnen ----------- */

long ExchangeArtPriceLoop ( char *db, char *user, char* prot_file, char *cArtNr, char *buf );
void ExchangeArtPriceUsage( char *buf );

/* ------------ Preise für Euro-Artikel in Kroatien umrechnen ----------- */

long CopyDiscountsLoop ( char *db, char *user, char *stopdiscflag, 
						char *artBase,   char *discgrpBase,   char *manBase,   char *catBase,   char *custBase,   char *pharmgrpBase, 
						char *artTarget, char *discgrpTarget, char *manTarget, char *catTarget, char *custTarget, char *pharmgrpTarget, 
						char *buf );
void CopyDiscountsUsage( char *buf );

/* ------------ zartikel.artikel_gesperrt in BG setzen für alle Pseudo-PZN´s, die abgelaufen sind (ccpvalidityperiod.dateto für article_no_pack <= cLoedatum) ----------- */

long BlockExpiredPseudoArticles ( char *db, char *user, char *cLoedatum, char *buf );
void BlockExpiredPseudoArticlesLoeUsage( char *buf );

/* ------------ Endedatum für alle noch gültigen Einträge eines Company- Codes setzen ----------- */

long StopGiBatchEntries ( char *db, char *user, char *cEndedatum, char *companyCode, char *buf );
void StopGiBatchEntriesUsage( char *buf );

/* ----- Eroeffnung --------- */

/* --- SET ISOLATION-Fehler bei SE -------------------------------------- */

#define SQL_SETISOLA_ERROR   (-554)


static int IsolaError = 0;

int IsStandartEngine( )
{
	return IsolaError;
}

void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

long OpenBase( char *db, char *errmld )
{
   long s;
   char base[50];

   IsolaError = 0;

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
   if ( s == SQL_SETISOLA_ERROR ) 
   {
	   IsolaError = 1;
	   s = 0;
   }
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

void ProgUsage( char *buf )
{
   Usage( buf );
   PreisUsage ( buf );
   ArtLoeUsage( buf );
   HerLoeUsage( buf );
   SetLoekennUsage( buf );
   AutidemUsage( buf );
   RestArtLoeUsage( buf );
   SetSpekennUsage( buf );
   ChargLoeUsage( buf );
   CalcEuroArtHrUsage ( buf );
   ExchangeArtPriceUsage( buf );
   CopyDiscountsUsage( buf );
   BlockExpiredPseudoArticlesLoeUsage( buf );
   UpdArticleFlagsByIngredientTypeUsage( buf );
   StopGiBatchEntriesUsage( buf );
}

long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;
   int mode = atoi(argv[0]);

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   //switch ( *argv[0] )
   switch ( mode )
    {
      case 1:
        if ( argc == 13 || argc == 15 )
        {
           s = PreisLoop(argc, argv, buf);
        }
        else
        {
          s = 1;
          Usage( buf );
          PreisUsage( buf );
        }
        break;

      case 2:
        if ( argc == 4 )
        {
          s = ArtLoeLoop( argv[1], argv[2], argv[3], NULL, buf );
        }
        else if ( argc == 5 )
        {
          s = ArtLoeLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          ArtLoeUsage( buf );
        }
        break;

      case 3:
        if ( argc == 4 )
        {
          s = HerLoeLoop( argv[1], argv[2], argv[3], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          HerLoeUsage( buf );
        }
        break;

      case 4:
        if ( argc == 5 )
        {
          s = SetLoekennLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          SetLoekennUsage( buf );
        }
        break;

      case 5:
        if ( argc == 6 )
        {
           s = AutidemLoop( argv[1], argv[2], argv[3], argv[4], argv[5],
                            buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          AutidemUsage( buf );
        }
        break;

      case 6:
        if ( argc == 3 )
        {
          s = RestArtLoeLoop( argv[1], argv[2], NULL, buf );
        }
        else if ( argc == 4 )
        {
          s = RestArtLoeLoop( argv[1], argv[2], argv[3], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          RestArtLoeUsage( buf );
        }
        break;

      case 7:
        if ( argc == 4 )
        {
          s = SetSpekennLoop( argv[1], argv[2], argv[3], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          SetSpekennUsage( buf );
        }
        break;

      case 8:
        if ( argc == 5 )
        {
          s = ChargLoeLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          ChargLoeUsage( buf );
        }
        break;
	
	  case 9:
        if ( argc == 4 ) 
        {
			s = CalcEuroArtHrLoop( argv[1], argv[2], argv[3], NULL, buf );
	    }
		else if ( argc == 5 )
        {
			s = CalcEuroArtHrLoop( argv[1], argv[2], argv[3], argv[4], buf );
		}
        else
        {
          s = 1;
          Usage( buf );
          CalcEuroArtHrUsage( buf );
        }
        break;

	case 10:
        if ( argc == 4 ) 
        {
			s = ExchangeArtPriceLoop( argv[1], argv[2], argv[3], NULL, buf );
	    }
		else if ( argc == 5 )
        {
			s = ExchangeArtPriceLoop( argv[1], argv[2], argv[3], argv[4], buf );
		}
        else
        {
          s = 1;
          Usage( buf );
          ExchangeArtPriceUsage( buf );
        }
        break;

	case 11:
        if ( argc == 16 ) 
        {
			s = CopyDiscountsLoop(	argv[1], argv[2], argv[3], argv[4],
									argv[5], argv[6], argv[7], argv[8], argv[9], argv[10],
									argv[11], argv[12], argv[13], argv[14], argv[15],
									buf );
	    }
		else
        {
          s = 1;
          Usage( buf );
          CopyDiscountsUsage( buf );
        }
        break;

	case 12:
        if ( argc == 4 )
        {
          s = BlockExpiredPseudoArticles( argv[1], argv[2], argv[3], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          BlockExpiredPseudoArticlesLoeUsage( buf );
        }
        break;

	case 13:
        if ( argc == 6 )
        {
          s = UpdArticleFlagsByIngredientTypeLoop( argv[1], argv[2], argv[3], argv[4], argv[5], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          UpdArticleFlagsByIngredientTypeUsage( buf );
        }
        break;

	case 14:
        if ( argc == 5 )
        {
          s = StopGiBatchEntries( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          StopGiBatchEntriesUsage( buf );
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

/* ---------------------------------------------------------------------- *
 *   Aufgabe        : Util-File laden    		                          *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 08.07.2005                                          *
 *   Autor          : Thomas Hörath                                       *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.4.7.6 : zputil 27/01/2025 K.Tischhoefer";
}

/*!
\page page34 zputil - Util-File laden

___________________________________________________________________________
\version	1.4.7.6
\date		27.01.2025
\internal
- KT: SR-25009089 Plausi check for zartpreis for BG: now aep>=grosso (old: aep>grosso)
\endinternal
___________________________________________________________________________
\version	1.4.7.5
\date		22.04.2024
\internal
- KT: SR-23021761 Plausiprüfung: bei cmi_flag=1 darf apo_auto_faehig_rowa /_knapp nicht gesetzt werden
\endinternal
___________________________________________________________________________
\version	1.4.7.4
\date		22.11.2023
\internal
- GW: CPR-230792 Neue csv-Imports fuer Warengruppe und Lieferant (UPD_ZARTWG_5AG und UPD_BLIESORT_DIREKT)
\endinternal
___________________________________________________________________________
\version	1.4.7.3
\date		07.02.2022
\internal
- OW: CPR-210933 Hot fix, (Zurück)Setzen eines Preise ist nun erlaubt; verbessertes Protokoll
\endinternal
___________________________________________________________________________
\version	1.4.7.2
\date		26.01.2022
\internal
- OW: CPR-210933 Mass Upload fuer CH: Plausi GEP und LBP, Uebernahme GEP "as is"
\endinternal
___________________________________________________________________________
\version	1.4.7.1
\date		14.09.2021
\internal
- TA: CPR-200938 Aufnahme neuer Voodoo-Table-Header für erweiterte zartpreis Tabelle
\endinternal
___________________________________________________________________________
\version	1.4.7.0
\date		27.05.2021
\internal
- KT: CPR-210155: neuer Mode 20 für ean
\endinternal
___________________________________________________________________________
\version	1.4.6.0
\date		05.03.2021
\internal
- KT: CPR-200089: neuer Mode 19 für cibt
\endinternal
___________________________________________________________________________
\version	1.4.5.1
\date		26.06.2019
\internal
- TH:  I-19029212 AEP < GEP in RS ok.
\endinternal
___________________________________________________________________________
\version	1.4.5.0
\date		19.04.2018
\internal
- TH: CPR-170659: neuer Mode 18 für cimexblock
\endinternal
___________________________________________________________________________
\version	1.4.4.0
\date		26.02.2018
\internal
- TH: Versorgung zartaustria
\endinternal
___________________________________________________________________________
\version	1.4.3.0
\date		14.09.2017
\internal
- TH: SR-17082862: % in CH immer (nicht nur bei Berechnung Grosso aus LBP) von zartikel auf zartpreis übernehmen
\endinternal
___________________________________________________________________________
\version	1.4.2.0
\date		03.03.2017
\internal
- TH: CR-15A029: neuer Mode 16 für zartserbia
\endinternal
___________________________________________________________________________
\version	1.4.1.0
\date		22.02.2017
\internal
- TH: CR-16D056: neuer Mode 15 für zchargenrueckruf
\endinternal
___________________________________________________________________________
\version	1.4.0.1
\date		12.10.2016
\internal
- TH: CR-16D054 Monatsrabatte auch mit Startdatum in der Vergangenheit
\endinternal  
___________________________________________________________________________
\version	1.4.0.0
\date		25.05.2016
\internal
- TH: testrun in advance for stopping of discounts
\endinternal  
___________________________________________________________________________
\version	1.3.7.2
\date		13.01.2016
\internal
- TH: wg INC-16000905 Änderung aus Version 1.3.4.2 zurückgenommen - wird via zpdailyclosing gelöst.
\endinternal
___________________________________________________________________________
\version	1.3.7.1
\date		17.12.2015
\internal
- TH: SR-15069323: BugFix bei Inserts
\endinternal
___________________________________________________________________________
\version	1.3.7.0
\date		01.12.2015
\internal
- TH: CR-15D087: neuer Mode 14 für carticleext
- RK: Refactoring
\endinternal
___________________________________________________________________________
\version	1.3.6.1
\date		24.07.2015
\internal
- TH: CR-14D072: Errechnung GEP aus LBP für CH
\endinternal
___________________________________________________________________________
\version	1.3.6.0 
\date		21.04.2015
\internal
- TH: CR-14D138: Setzen zartikel.datum_ah
\endinternal
___________________________________________________________________________
\version	1.3.5.0
\date		23.02.2015
\internal
- TH: Preis-Checks überarbeitet (SR-15007903)
\endinternal
___________________________________________________________________________
\version	1.3.4.2
\date		07.01.2015
\internal
- TH: Schreiben cartrefundfrance bei Änderung AVP (SR-15000393)
\endinternal
___________________________________________________________________________
\version	1.3.4.1
\date		27.11.2014
\internal
- TH: schreiben zapflege mit datum_ah
\endinternal
___________________________________________________________________________
\version	1.3.4.0
\date		07.11.2014
\internal
- TH: mode 13 (zartswitzerland)
\endinternal

*/

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include <hdatum/phodate.h>

#include "g_util.h"


/*
	1.0.0.0 15/07/2005 TH	first issue
	1.0.1.0 10/03/2006 TH	zartwg + Vorbereitungen zartpreis (insert fehlt noch!)
	1.0.1.1 15/03/2006 TH	Fehlerbeseitung CloseOneBufferDesc
	1.0.1.2 28/07/2006 TH	delete einer warengruppe (3), wenn feld warengruppe leer!
	1.0.1.3 13/11/2006 TH	primary key für Protokol-Satz auf Standard angepasst.
	1.0.1.4 29/11/2006 TH	zapflege auch nach Löschen einer Warengruppe schreiben!
	1.0.2.0 08/01/2007 TH	zartpreis vollständig implementiert und freigeschaltet
	1.0.2.1 11/04/2007 TH	zartpreis -> plausi- checks
	1.0.2.2 06/02/2008 RR	AEP < GEP zulassen, wenn AEP = 0 (in CH gibt es keinen AEP)
	1.1.0.0 18/04/2008 TH	neuer Mode '4' für Versorgung cdiscount mit definierter (nicht dynamischer!) Struktur
	1.1.0.1 08.07.2008 RR   Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						    Ausgabe Log auch bei Aufruf aus Windows (EkZdp) 
	1.1.1.0 16.12.2008 TH   mit neuer zartpreis- Struktur kompiliert 
	1.2.0.0 30.04.2009 TH   neuer mode 5 zum Laden von cdiscount (dynamisch) 
	1.2.0.1 08.06.2009 TH   letzte Korrekturen für neuen mode 5
	1.2.1.0 09.06.2009 TH   neuer mode 6 zum Beenden von cdiscount (dynamisch) 
	1.2.1.1 30.07.2009 TH   kein Abbruch bei Mode 5 wenn Discount schon vorhanden! 
	1.2.1.2 17.08.2009 TH   protfile extension 
	1.2.1.3 18.09.2009 TH   RS + HR: AEP == GROSSO --> ok !
	1.2.1.4 04.11.2009 TH   bugfix at insert cdiscount.internaldiscount
	1.2.1.5 22.12.2009 TH   stop cdiscount with flexible date
	1.2.1.6 24.08.2010 TH   neuer mode 7 zum Laden von artve
	1.2.1.7 29.11.2010 TH   AEP == GEP auch in D
	1.2.1.8 08.04.2011 TH   neues Feld zartpreis.lieferbasispreis
	1.2.1.9 21.06.2011 TH   Versorgung artnrbl bei Einspielung zartikel.artikel_nr_herst
	1.2.2.0 06.06.2012 TH   CR-SA0111
	1.2.2.1 25.07.2012 TH   Anpassung UnixFoundation
	1.2.2.2 09.08.2012 TH   SR-081422 Datum-AH in Artikelnamen übernehmen
	1.2.2.3 05.09.2012 TH   Bugfix: Schreiben zapflege für ZArtikel- Update nicht nur in CH !
	1.2.3.0 22.10.2012 TH   neuer Mode 8 zum Laden von CDiscGrpMem
	1.2.3.1 13.11.2012 TH   Bugfix Mode 8 bei -239
	1.2.4.0 21.11.2012 TH   Mode 8 - vor Laden eines Artikels alle cdiscgrpmem für die Gruppe löschen
							neues, fixes Fileformat (BG) zum Laden von cdiscount
	1.2.4.1 14.12.2012 TH   Bugfix Mode 4: unique key bei upd_cdiscount um drei neue Felder erweitert
	1.2.5.0 05.02.2013 TH   mode 9 (zartfrance) + mode 10 (carticlecodes) für FR-Revival 3
	1.3.0.0 13.03.2013 TH   AIX build
	1.3.0.1 13.03.2013 TH   SR-093821 --> zpznpflege (11) nach Update carticlelang
	1.3.0.3 02.05.2013 TH   neue Felder / Abläufe für BG
	1.3.0.4 10.06.2013 TH   Versorgung zartikel.steller
	1.3.1.0 23.07.2013 TH   Versorgung bliesort
	1.3.1.1 01.08.2013 TH   Versorgung pflege für Übertragung bliesort an EK
	1.3.1.2 16.01.2014 TH   neue Felder pharmgrpexl_2, pharmgrpexl_3, monthlydiscount
	1.3.1.3 09.04.2014 TH   Removal of vignette: two new price fields
	1.3.2.0 28.07.2014 TH   CR-12032: neuer Mode zum Laden von cgibatchentry
	1.3.3.0 27.10.2014 TH   CR-14P005: Versorgung ctransfercsc
	1.3.4.0 07.11.2014 TH   mode 13 (zartswitzerland)
	1.3.4.1 27.11.2014 TH   schreiben zapflege mit datum_ah
	1.3.4.2 07.01.2015 TH   Schreiben cartrefundfrance bei Änderung AVP (SR-15000393)
	1.3.5.0 23.02.2015 TH   Preis-Checks überarbeitet (SR-15007903)
	1.3.6.0 21.04.2015 TH   CR-14D138: Setzen zartikel.datum_ah
	1.3.6.1 24.07.2015 TH   CR-14D072: Errechnung GEP aus LBP für CH
	*/

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

/* ------------------------------------------------------------------- */
void UpdateStatistics( const char * const relation )
{
   char sql[100];
   strcpy( sql, "update statistics for table " );
   strcat( sql, relation );
   SqlExecuteImm( sql );
}

/* ---------------- Programm-Ausahl ----------------- */
static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

/* ---------------------------------------------------------------------- */
static void LadeUsage( char *buf )
{
  strcat( buf, "1. zputil parameter zputil-Verzeichnis database testmode \n" \
	  "  laedt die zputil-datei in die durch parameter definierte Relation\n\n  parameter==...\n"
	  "    1: zartikel,             2: zartpreis,        3: zartwg,            4: cdiscount,\n"
	  "    5: cdiscount (flexible), 6: cdiscount (stop), 7: artve,             8: cdiscgrpmem,\n"
	  "    9: zartfrance,          10: carticlecodes,   11: cartcompack,      12: cgibatchentry,\n"
	  "   13: zartswitzerland,     14: carticleext,     15: zchargenrueckruf, 16: zartserbia,\n"
	  "   17: zartaustria,         18: cimexblock,      19: cibt,             20: ean,\n"
	  "   21: csubsequentdeliverybrancharticleconfig,   22: zartwg_5ag,       23: bliesort,\n"
	  "   24: cbaselistarticles,   25: cartmedactor,	26: cmedicalactor\n"
	           "   zputil-Verzeichnis: Pfad + Datei, die geladen werden soll \n"
	  "  testmode: 1 = Programm laeuft innerhalb einer Transaktion und macht am Ende ein globales Rollback \n");
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
   int mode = atoi(argv[0]);
   int test = atoi(argv[3]);

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   if (mode >= UPD_ZARTIKEL && mode < MODE_END)
   {
		if ( argc == 4 )
        {
			s = GenUtil( argv[2], argv[1], buf, mode, test );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
   }
   else
   {
		s = 1;
        strcpy( buf, "Programm-Teil: " );
        strcat( buf, argv[0] );
        strcat( buf, " nicht vorhanden" );
   }

   return s;
}

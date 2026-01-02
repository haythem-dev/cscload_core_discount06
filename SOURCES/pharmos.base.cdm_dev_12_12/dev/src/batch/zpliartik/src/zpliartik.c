/* ---------------------------------------------------------------------- *
 *   Aufgabe        : LogIndex Artikel     laden                          *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 26.08.2013                                          *
 *   Autor          : Hörath                                              *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
    // in binary embedded full version string
    return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.3.0.2 : zpliartik 15/09/2017 Thomas Hörath";
}

/*!
\page page26 zpliartik - LogIndex Artikel laden

___________________________________________________________________________
\version	1.3.0.2
\date		15.09.2017
\internal
- TH: SR-17086971 Einlesen zartikel.herst_prozent / zartpreis.lieferbasispreis und Setzen in cliart
\endinternal
___________________________________________________________________________
\version	1.3.0.1
\date		20.04.2017
\internal
- TH: SR-17035559 PRODUCT.blood --> zartikel.chargenartikel (nicht mehr zartikel.tfg!)
\endinternal
___________________________________________________________________________
\version	1.3.0.0
\date		11.01.2017
\internal
- TH: max. Länge eines Element = 1000
- CR-14D152
\endinternal
___________________________________________________________________________
\version	1.2.0.3
\date		06.09.2016
\internal
- TH: SR-16070839 GTIN14 --> carticlecodes mit code_type = 19
\endinternal
___________________________________________________________________________
\version	1.2.0.2
\date		01.08.2016
\internal
- TH: SR-16063622 Wechsel AWL1 - zwingender Fehler wird nicht mehr zurückgesetzt
\endinternal
___________________________________________________________________________
\version	1.2.0.1
\date		27.07.2016
\internal
- TH: I-16029549	
\endinternal
___________________________________________________________________________
\version	1.2.0.0
\date		08.06.2016
\internal
- TH: CR-16D039 Laden cassortmentcode + catccode; CDSO1 reaktiviert;	
\endinternal
___________________________________________________________________________
\version	1.1.2.3
\date		19.11.2015
\internal
- TH: SR-15061064 Neuaufnahmen auch für Artikel ohne IKS	
\endinternal
___________________________________________________________________________
\version	1.1.2.2
\date		09.09.2015
\internal
- TH: SR-15038819 NOPCS durch MULT ersetzt
\endinternal
___________________________________________________________________________
\version	1.1.2.1
\date		24.03.2015
\internal
- TH: SR-15012588 = keine Neuanlagen, wenn OUTSAL != 0;
\endinternal
___________________________________________________________________________
\version	1.1.2.0
\date		24.02.2015
\internal
- TH: Preisprüfung bei Neuanlagen;
\endinternal
___________________________________________________________________________
\version	1.1.1.2
\date		20.02.2015
\internal
- TH: QTY = decimal!
\endinternal
___________________________________________________________________________
\version	1.1.1.1
\date		17.02.2015
\internal
- TH: CR-14D132 = BugFixes;
\endinternal
___________________________________________________________________________
\version	1.1.1.0
\date		05.02.2015
\internal
- TH: CR-14D132 = Ladung ARTNO1 + SUPPLNO; Setzen Anlage- / Änderungsdatum; zwingende Fehler bei Änderung COMPNO (Hnr) / SUPPLNO (Awl); Ladung clicompany;
\endinternal
___________________________________________________________________________
\version	1.1.0.0
\date		08.01.2015
\internal
- TH: CR-14D133 = keine Neuanlage ohne IKS-Code; keine Änderung bei zartikel.datum_ah > 0; bei Namensänderungen auch DFO / Einheit editierbar machen.
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

#include "g_liartik.h"


/*  1.0.0.0 xx/xx/2013 
	1.0.0.1 09/01/2014	TH	DSCRD / DSCRF nur als geändert markieren (=spätere Übernahme), wenn Neuanlage oder gleichzeitig auch  DSCRLONGD / DSCRLONGF geändert.
	1.0.0.2 11/03/2014	TH	Erweiterung zartikel.
	1.0.0.3 10.04.2014  TH: wandeln mit neuer zartikel/zartpreis-Struktur
	1.0.0.4 05.09.2014  TH: EAN´s nur lesen, wenn BCSTAT = A (primär)
							zwingende Fehler bei Änderung BTM, Psychotro, Kühl, Artikelname
	1.0.0.5 20.10.2014  TH: Bugfix SR-14023927 (ZW_CHANGE_PSYCHOTROP / NZ_PZNNF_NVOR)
	1.0.0.6 02.12.2014  TH: temporary don´t use COMPNO to fill artikel_nr_herst, as ARTNO1 would be correct
	1.1.0.0 08.01.2015  TH: CR-14D133 = keine Neuanlage ohne IKS-Code; keine Änderung bei zartikel.datum_ah > 0; bei Namensänderungen auch DFO / Einheit editierbar machen.
	1.1.1.0 05.02.2015  TH: CR-14D132 = Ladung ARTNO1 + SUPPLNO; Setzen Anlage- / Änderungsdatum; zwingende Fehler bei Änderung COMPNO (Hnr) / SUPPLNO (Awl); Ladung clicompany;
	1.1.1.1 17.02.2015  TH: CR-14D132 = BugFixes;
	1.1.1.2 20.02.2015  TH: QTY = decimal!
	1.1.2.0 24.02.2015  TH: Preisprüfung bei Neuanlagen;
	1.1.2.1 24.03.2015  TH: SR-15012588 = keine Neuanlagen, wenn OUTSAL != 0;
	1.1.2.2 09.09.2015  TH: SR-15038819 NOPCS durch MULT ersetzt
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
  strcat( buf, "1. zpliartik 1 database ili-Verzeichnis \n" \
               "   laedt die logindex-datei in die Relation cliart\n"\
               "   ili-Verzeichnis: Pfadname, unter dem logindex- Datei zum Laden liegt\n" );
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
      case '1':
        if ( argc == 3 )
        {
           s = GenLiArtNeu( argv[1], argv[2], buf );
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

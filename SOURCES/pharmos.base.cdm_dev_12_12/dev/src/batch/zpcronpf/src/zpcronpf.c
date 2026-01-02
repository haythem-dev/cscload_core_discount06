/* ---------------------------------------------------------------------- *
 *                            Z P C R O N P F . C                         *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Startet das Programm tpulzentpfl                      *
 *                                                                        *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 22.02.99                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.6.2 : zpcronpf : 19.08.2025 : KT";
}

/*!
\page page8 zpcronpf - Startet das Programm tpulzentpfl u.v.m.
________________________________________________________________________________________
\version	1.6.2
\date		19.09.2025
\internal
- KT: SCTASK0068998: Protokolleinträge sollen 5 Jahre behalten werden, statt wie bisher 18 Monate
\endinternal
________________________________________________________________________________________
\version	1.6.1
\date		14.07.2021
\internal
- RR: CPR-210276: neue Aufruf zpdailyclosing 4 (vorerst nur PW-AT)
\endinternal
________________________________________________________________________________________
\version	1.6.0
\date		06.04.2020
\internal
- RR: CPR-180211: Parameterübergabe, ob Samstag, Sonntag & Feiertag als Arbeitstage zählen
- RR: CPR-191235: komplett neue Struktur der Programmaufrufe (über Tabelle parameterkd)
\endinternal
________________________________________________________________________________________
\version	1.5.0
\date		11.02.2019
\internal
- TH: Aufruf zpdailyclosing mode 3 für DE / AT / CH (DACH-BT).
\endinternal
________________________________________________________________________________________
\version	1.4.9
\date		31.03.17
\internal
- TH: Aufruf zpmasaen mode 8 1 auch für CH (Löschen zchargenrueckruf).
\~german   
für CH Aufruf automatisches Löschen Chargen- Rückrufe
\~english 
\endinternal

________________________________________________________________________________________
\version	1.4.8
\date		07.04.16
\internal
- RR: Aufruf zpmasaen mode 7 für DE (automatische Sperre für AH-Artikel im Rahmen von 3-Level-Verbund).
\~german   
für Deutschland Aufruf Programm zum automatischen Setzen des Sperrkennzeichens für Artikel, die seit mindestens vier Jahren außer Handel sind
\~english 
change only relevant for Germany
\endinternal
________________________________________________________________________________________
\version	1.4.7
\date		13.01.16
\internal
- TH: Aufruf zpdailyclosing mode 2 für FR (INC-16000905).
\endinternal
________________________________________________________________________________________
\version	1.4.6
\date		21.04.15
\internal
- TH: Aufruf zpdailyclosing für CH (CR-14D138).
\endinternal
________________________________________________________________________________________
\version	1.4.5
\date		27.10.14
\internal
- TH: Aufruf Reorg ctransfercsc für alle Länder
\endinternal
________________________________________________________________________________________
\version	1.4.4
\date		24.07.14
\internal
- RR: Aufruf Rabatt-Reorg auch in der Schweiz mit Parameter 2 Monate zurück.
\endinternal
________________________________________________________________________________________
\version	1.4.3
\date		 29.04.14
\internal
- RR: Aufruf zpcalcprice (mode 7) in WS-FR für Übertragung Erstattungswerte aus cartrefundfrance in zartfrance
\endinternal
________________________________________________________________________________________
\version	1.4.2
\date		27.09.13
\internal
- RR: beenden mit RC <> 0, wenn eines der aufgerufenen Programme abbricht (bisher wurde mit dem RC des zuletzt aufgerufenen Programms beendet).
\endinternal

*/

/* 1.0.3   12.07.02 : Aufruf von zpautidm */
/* 1.0.4   08.11.03 : Umstellung auf variable Datenbank  */
/* 1.0.5   07.05.04 : iPid  */
/* 1.0.6   12.05.04 : Aufruf tpulzentpfl ueber h_system */
/* 1.0.7   30.03.05 : RR: Aufruf tpulzentpfl mit Filenamen (länderabhängig) */
/* 1.0.8   09.05.06 : RR: neuer Aufruf tpulzpfrance für Versorgung Incogest-System */
/* 1.0.9   13.09.06 : RR: neuer Aufruf zpmasaen zum Löschen von alten Chargenrückrufen */
/* 1.1.0   02.04.07 : RR: neuer Aufruf zpprotok zum Löschen von alten Protokolleinträgen */
/* 1.1.1   11.04.07 : RR: Anpassung Aufruf zpmasaen (neuer Parameter mode), */
/* 1.1.2   11.04.07 : RR: neuer Aufruf zpmasaen zum Rabatte löschen (Österreich) */
/* 1.1.3   31.05.07 : RR: vermeiden Aufrufe mit unplausiblem Datum (Chargen + Protokoll löschen) */
/* 1.1.4   25.06.07 : RR: Aufruf zpcalcrg (berechnen Rabattgruppen Frankreich) */
/* 1.1.5   27.06.07 : RR: Aufruf zpcalcrg vor tpulzpfrance */
/* 1.1.6   08.10.07 : RR: neuer Aufruf zpmasaen zum Preiserhöhungen löschen (Deutschland) */
/* 1.1.7   04.07.08 : RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
                      Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.1.8   15.09.08 : RR: Aufruf tpulzpfrance auch für Prewhole Ivrylab (Fil. 42) */
/* 1.1.9   22.09.08 : RR: Aufruf tpulzpfrance für Prewhole Ivrylab mit anderem Dateinamen */
/* 1.2.0   29.07.09 : RR: Aufruf tpulzpbulgaria für Bulgarien */
/* 1.2.1   14.01.10 : RR: Datum um 1 reduzieren, falls Lauf nach Mitternacht (GetPhoTime) */
/* 1.2.2   19.01.10 : RR: bei Start an einem Feiertag trotzdem Verarbeitung, nur Hinweis im Logfile */
/* 1.2.3   03.03.10 : RR: für GH-FR Aufruf tpulzentpfl mit 180 Tagen Löschfrist */
/* 1.2.4   04.08.11 : RR: Samstag und Sonntag in Bulgarien nicht als Feiertag bewerten */
/* 1.2.5   27.10.11 : RR: am letzten Arbeitstag im Monat Aufruf zpcalcrg fuer Deutschland */
/* 1.2.6   27.02.12 : RR: in BG Tabelle feiertag mit Filiale 29 lesen (damit nicht EK-Feiertage ziehen) */
/* 1.2.7   01.03.12 : TH: Aufruf zpmasaen mode 12 für BG. */
/* 1.2.8   12.03.12 : RR: Aufruf tpulzpfrance auch fuer Fil. 48 (wg. Merge zpps2pfr & zpps2piv) */
/* 1.2.9   10.05.12 : RR: in BG keine Feiertage mehr lesen, jeder Tag gilt als Arbeitstag */
/* 1.3.0   12.07.12 : RR: Fehlerkorrektur in LeseFeiertage (== 22 statt = 22) */
/* 1.3.1   25.07.12 : TH: Unix Foundation */
/* 1.3.2   09.01.13 : RR: Aufruf Rabatt-Reorg auch in Kroatien mit Parameter 1 Tag zurück */
/* 1.3.3   26.02.13 : TH: Aufruf zpcalcprice (mode 6) in CH für Berechnung ExfactoryRabatte (LBP --> Grosso) aus PPE */
/* 1.4.0   18.03.13 : TH: AIX build */
/* 1.4.1   19.07.13 : ME: AIX workaround for SIGCHLD handler (Informix side effect).
                          fixed compiler warings. 
                          removed not needed link libraries */
/* 1.4.2   27.09.13 : RR: beenden mit RC <> 0, wenn eines der aufgerufenen Programme abbricht (bisher wurde mit dem RC des zuletzt aufgerufenen Programms beendet) */
/* 1.4.3   29.04.14 : RR: Aufruf zpcalcprice (mode 7) in WS-FR für Übertragung Erstattungswerte aus cartrefundfrance in zartfrance */
/* 1.4.4   24.07.14 : RR: Aufruf Rabatt-Reorg auch in der Schweiz mit Parameter 2 Monate zurück */
/* 1.4.5   27.10.14 : TH: Aufruf Reorg ctransfercsc für alle Länder */
/* 1.4.6   21.04.15 : TH: Aufruf zpdailyclosing für CH (CR-14D138). */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <libscsvoodoo.h>
#include <gregdate.h>
#include <phozeit.h>

#include "logfile.h"

#if defined (MSDOS) || defined (WIN32)
#define ON_CLIENT
#else
#include <unistd.h>
#include <signal.h>
#endif

/* #define MIT_AUTIDM */

/* ---------------------------------------------------------- */

static char *ProgName  = "zpcronpf";

static char *BearbProg = "tpulzentpfl";

/* #ifdef MIT_AUTIDM */
#define AUTIDEM_TAGE 14
static char *BearbProgAutidem = "zpautidm";
/* #endif */

/* ---------------------------------------------------------- */

#define BK_FEST     0
#define BK_OSTERN   1
#define BK_BEWEG_1  2

struct FEIERTAG_1
{
   short MODUS;
   short TAG;
   short VON_JAHR;
   short BIS_JAHR;
};

static char *proj = "MODUS,TAG,VON_JAHR,BIS_JAHR";

#define MAX_FT 150

static struct FEIERTAG_1 ft[MAX_FT];

static int anz_tage     = -2;
static int old_filialnr = -1;

static char FeierError[100];

#ifdef ON_CLIENT

static long EshuPenvOpen( HNMP *handle, char *penv )
{
	long s;

/* zum Debuggen auf denu1zdev */
	s = ViaEshuOpen( handle, "zdev1", "uiserv" ); 
	
/* zum Debuggen auf zpps1 */
/*	s = ViaEshuOpen( handle, "zpps1", "uiserv" ); */
	
/*	char *Server;
	Server = getenv( penv );

	if ( Server != (char *)NULL )
		s = ViaEshuOpen( handle, Server, "uiserv" );
	else
		s = 4711; */

	return s;
}
#endif

static int LeseFeiertage( short filialnr )
{
   int i;
   int fd;
   long s;
   char sql[150];

   old_filialnr = filialnr;

   anz_tage = -1;

	/* in Bulgarien mit Pseudo-Filialnummer 29 lesen; Hintergrund ist das Problem vom 31.12.; dieser war 
	   in der Tabelle feiertag von Filiale 22 als Feiertag eingetragen, damit wurden am 30.12. schon die 
	   Preise zum 01.01. rausgeschickt, was aber nicht gewollt war (denn so waren sie in der Faktur am 
	   31.12. schon aktiv) --> mit den Bulgaren (Julian Nedelchev) wurde vereinbart, dass sie die ZDP-
	   relevanten Feiertage in einer Pseudo-Filiale pflegen */

	/* das alles ist schon wieder hinfällig 
   if (filialnr = 22)
	   filialnr = 29; */

	/* mit der oben beschriebenen Mimik gab es Probleme, weil die Filialnummer 29 inzwischen als Pseudowert
	   für den Neubau Sofia definiert und damit der ZDP-Kalender einkaufsseitig überschrieben wurde; 
	   daraufhin war die Vorgabe von Julian Nedelchev überhaupt keine Feiertage mehr bei der Verteilung 
	   Richtung Pharmos abzufragen */

   if (filialnr == 22)
		return 0;

   sprintf( sql, "select %s from FEIERTAG where FILIALNR=%d",
                  proj,
                  filialnr );

   if ( SqlOpenCs( &fd, sql ) == 0 )
   {
      i = 0;
      s = 0;
      while ( i < MAX_FT && s == 0 )
      {
         s = SqlFetch( fd, 1, &ft[i], NULL );
         if ( s == 0 ) i++;
      }
      if ( s == 100 )
         anz_tage = i;
      else
         strcpy( FeierError, DynErrmld() );
      SqlCloseCs( fd );
   }
   else
      strcpy( FeierError, DynErrmld() );

   return anz_tage;
}

int IsFeiertag( long datum, short filialnr )
{
    long ostern;
    long vgldatum;
    int jahr, monat, tag;
    int wotag;
    int bew1_monat, bew1_woche, bew1_wochentag;
    int i;

    if ( datum <= 0 ) 
		return -1;

    GregToDmy( datum,&tag,&monat,&jahr);

    ostern = EasterSonday( jahr );

    /* neu lesen, wenn Filialnr wechselt */
    if ( old_filialnr != filialnr )
      anz_tage = -2;

    if ( anz_tage == -2 )
       LeseFeiertage( filialnr );

    /* anz_tage = 0 darf kein Fehler sein wg. Bulgarien
    if ( anz_tage <= 0 ) */
    if ( anz_tage < 0 ) 
        return -1;

    i = 0;
    while ( i < anz_tage  )
    {
       if ( ( ft[i].VON_JAHR == 0 || jahr >= ft[i].VON_JAHR ) &&
            ( ft[i].BIS_JAHR == 0 || jahr <= ft[i].BIS_JAHR )    )
          switch( ft[i].MODUS )
          {
            /* TAG = mmdd, mm = Moant, tt * Tag */
            case BK_FEST:
                 if ( tag == ft[i].TAG % 100 && monat == ft[i].TAG / 100 )
                   return 1;
                 break;
            /* TAG = relativer Abstand zu Ostern */
            case BK_OSTERN:
                 if ( datum == ostern + ft[i].TAG ) return 1;
                 break;
            /* TAG = mmwt , mm = Monat, w = Woche, t =  Wochentag-Nr */
            case BK_BEWEG_1:
                 bew1_monat      = ft->TAG / 100;
                 bew1_woche      = ft->TAG % 100;
                 bew1_wochentag  = bew1_woche % 10;
                 bew1_woche     /= 10;

                 vgldatum = DmyToGreg( 1, bew1_monat, jahr);

                 wotag =  GregDayOfWeek( vgldatum );
                 if ( wotag < ft[i].TAG )
                   vgldatum += bew1_wochentag - wotag + 7*( bew1_woche - 1 );
                 else
                   vgldatum += bew1_wochentag - wotag + 7*bew1_woche;
                 if ( datum == vgldatum ) return 1;
                 break;
          }
     i++;
    }
    return 0;
}

static int IsSonntag( long datum )
{
    if ( GregDayOfWeek( datum ) == 6 )
       return 1;
     else
       return 0;
}

static int IsSamstag( long datum )
{
    if ( GregDayOfWeek( datum ) == 5 )
       return 1;
     else
       return 0;
}

/* int IsArbeitsTag( long datum, short filialnr, char *db )
{
    int ft;
    if ( datum <= 0 ) 
		return -1;

	if ( ( IsSonntag( datum ) ||  
           IsSamstag( datum ) ) && 
		   strcmp(db, "zpps2bg") != 0 && strcmp(db, "ibg21") != 0)	/* Samstag und Sonntag sind in Bulgarien Arbeitstage 
		return 0;

    ft = IsFeiertag( datum, filialnr );

	if ( ft == -1 ) 
		return -1;
    
	if ( ft == 1 )  
		return 0;

	return 1;
} */

int IsArbeitsTagNeu( long datum, short filialnr, short IstSamstagArbeitstag, short IstSonntagArbeitstag, short IstFeiertagArbeitstag )
{
    int ft;
    if ( datum <= 0 ) 
		return -1;

	if ( IsSamstag ( datum ) &&
		 !IstSamstagArbeitstag )
		return 0;

	if ( IsSonntag ( datum ) &&
		 !IstSonntagArbeitstag )
		return 0;

    ft = IsFeiertag( datum, filialnr );

	if ( ft == -1 ) 
		return -1;
    
	if ( ft == 1 &&
		 !IstFeiertagArbeitstag )
		return 0;
		
	return 1;
}

static int SpannenclusterPruefung( long datum, long bisdatum )
{
    int tag1, mon1, jahr1;
    int tag2, mon2, jahr2;

    GregToDmy( datum, &tag1, &mon1, &jahr1 );
    GregToDmy( bisdatum, &tag2, &mon2, &jahr2 );

	/* Aufruf nur am Monatsletzten --> dann ist Monat aus bisdatum ungleich Monat aus vondatum */
	if (mon1 == mon2)
		return 0;
	else
		return 1;
}

static void OutDatum( long datum, char *datstr )
{
    int tag;
    int mon;
    int jahr;
    GregToDmy( datum, &tag, &mon, &jahr );
/*  so nicht:  tt.mm.jjjj  */
/*  sprintf( datstr, "%.2d.%.2d.%.4d", tag, mon, jahr); */

/*  sondern so: jjjjmmtt */
    sprintf( datstr, "%.4d%.2d%.2d", jahr, mon, tag );
}

static void OutDatum2( long datum, char *datstr )
{
    int tag;
    int mon;
    int jahr;
    GregToDmy( datum, &tag, &mon, &jahr );
/*  tt.mm.jjjj  */
	sprintf( datstr, "%.2d.%.2d.%.4d", tag, mon, jahr);
}

static void GenAHSperreDatum( long datum, char *datstr )
{
    int tag;
    int mon;
    int jahr;
    GregToDmy( datum, &tag, &mon, &jahr );

	/* Artikel sperren, die seit mindestens 4 Jahren außer Handel */
	jahr -= 4;

/*  hier so:  tt.mm.jjjj  */
    sprintf( datstr, "%.2d.%.2d.%.4d", tag, mon, jahr); 
}

static void GenChargenDatum( long datum, char *datstr )
{
    int tag;
    int mon;
    int jahr;
    GregToDmy( datum, &tag, &mon, &jahr );

	/* immer Chargen älter als 6 Monate löschen */
	if (mon > 6)
	{
		mon -= 6;
	}
	else
	{
		mon += 6;
		jahr -= 1;
	}

/* um z.B. Aufrufe wie 31.11.2005 zu vermeiden */
	if (mon == 2 && tag > 28)
		tag = 28;
	else if ((mon == 4 || mon == 6 || mon == 9 || mon == 11) && tag == 31)
		tag = 30;

/*  hier so:  tt.mm.jjjj  */
    sprintf( datstr, "%.2d.%.2d.%.4d", tag, mon, jahr); 
}

static void GenProtokollDatum( long datum, char *datstr )
{
    int tag;
    int mon;
    int jahr;
    GregToDmy( datum, &tag, &mon, &jahr );

	/* SCTASK0068998: Protokolleinträge sollen 5 Jahre behalten werden, statt wie bisher 18 Monate */
	jahr -= 5;

/* um z.B. Aufrufe wie 29.02.2023 zu vermeiden */
	if (mon == 2 && tag > 28)
		tag = 28;

/*  hier so:  tt.mm.jjjj  */
    sprintf( datstr, "%.2d.%.2d.%.4d", tag, mon, jahr); 
}

static void GenRabattDatum( long datum, char *datstr, short filialnr )
{
    int tag;
    int mon;
    int jahr;

	/* immer Rabatte löschen, die länger als 50 Tage abgelaufen sind; in Kroatien nur einen Tag zurück, in der Schweiz 60 Tage */
	if (filialnr == 79)
		datum -= 1;
	else if (filialnr == 69)
		datum -= 50;
	else 
		datum -= 60;

    GregToDmy( datum, &tag, &mon, &jahr );

/*  hier so:  tt.mm.jjjj  */
    sprintf( datstr, "%.2d.%.2d.%.4d", tag, mon, jahr); 
}

static void GenTransferCscDatum( long datum, char *datstr )
{
    int tag;
    int mon;
    int jahr;

	/* immer csctransfers löschen, die vor mehr als 30 Tagen eingetragen wurden */
	datum -= 30;

    GregToDmy( datum, &tag, &mon, &jahr );

/*  hier so:  jjjj-mm-tt  */
    sprintf( datstr, "%4d-%02d-%02d", jahr, mon, tag ); 
}

static void GenPreiserhoehungsDatum( long datum, char *datstr )
{
    int tag;
    int mon;
    int jahr;

	/* immer Preiserhoehungen löschen, die länger als 180 Tage abgelaufen sind */
	datum -= 180;

    GregToDmy( datum, &tag, &mon, &jahr );

/*  hier so:  tt.mm.jjjj  */
    sprintf( datstr, "%.2d.%.2d.%.4d", tag, mon, jahr); 
}

static void GenBlockExpiredPseudoArticlesDatum( long datum, char *datstr )
{
    int tag;
    int mon;
    int jahr;

	/* immer Pseudo- Artikel sperren, die seit 2 Tagen lt. ccpvalidityperiod abgelaufen sind */
	datum -= 2;

    GregToDmy( datum, &tag, &mon, &jahr );

/*  hier so:  tt.mm.jjjj  */
    sprintf( datstr, "%.2d.%.2d.%.4d", tag, mon, jahr); 
}

static void GenSpannenclusterDatum( long datum, char *datstr1, char *datstr2)
{
    int tag;
    int mon;
    int jahr;
    GregToDmy( datum, &tag, &mon, &jahr );

	/* Tag muss immer 01 sein */
	tag = 1;

	/*  hier so: jjjjmmtt */
    sprintf( datstr2, "%.4d%.2d%.2d", jahr, mon, tag );

	/* immer einen Monat zurück */
	if (mon > 1)
		mon -= 1;
	else
	{
		mon = 12;
		jahr -= 1;
	}

	/*  hier so: jjjjmmtt */
    sprintf( datstr1, "%.4d%.2d%.2d", jahr, mon, tag );
}

static void GenLogDatum( long datum, char *datstr, short filialnr )
{
    int tag;
    int mon;
    int jahr;

	GregToDmy( datum, &tag, &mon, &jahr );

/*  hier so:  tt.mm.jjjj  */
    sprintf( datstr, "%.2d.%.2d.%.4d", tag, mon, jahr); 
}

/* ---------------------------------------------------------------------- *
 *     Datenbank                                                          *
 * ---------------------------------------------------------------------- */

/* --- SET ISOLATION-Fehler bei SE -------------------------------------- */

#define SQL_SETISOLA_ERROR   (-554)

static void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

static long OpenBase( char *base, char *errmld )
{
   long s;
   char sql[50];

   strcpy( sql, "database " );
   strcat( sql, base );

   s = SqlExecuteImm( sql );
   if ( s != 0 )
   {
      strcpy( errmld, sql );
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

   return 0;
}

/* ---------------------------------------------------------------------- *
 *     Fehler-Ausgabe                                                     *
 * ---------------------------------------------------------------------- */

static int printf_mode = 1;

static void ErrOut ( int status, short fil, char *str1 )
{
    if ( fil < 0 ) 
		fil = 0;

#ifdef ON_CLIENT
    displ_logfile( status, fil, str1 );
#else
    if ( printf_mode & 1 )
       write_logfile( status, fil, ProgName, str1 );
    if ( printf_mode & 2 )
       displ_logfile( status, fil, str1 );
#endif
}

/* ---------------------------------------------------------------------- *
 *     System-Aufruf                                                      *
 * ---------------------------------------------------------------------- */

static void GenCommandString( char *Command, char *db, long heute, long bisdatum, short filialnr )
{
    char s_heute[11];
    char s_bisdatum[11];
    char filename[12];

	// Filialnummer von 53 auf 99 ändern für tpulzentpfl-Aufruf
	if (filialnr == 53)
	{
		filialnr = 99;
	}

	sprintf(filename, "dezap%2.2d.dat", filialnr);

    OutDatum( heute,    s_heute );
    OutDatum( bisdatum, s_bisdatum );
	
	/* für GH Frankreich 180 Tage halten wg. neuer RTB-Filialen 
	   (Änderungen müssen nachträglich rausgeschickt werden) 
	   --> kann nach Ende dieses Projekts wieder rausgenommen werden */
	if ( strcmp( db, "zpps2fr" ) == 0 || strcmp( db, "ifr21" ) == 0 )
		sprintf( Command, "%s -ld %s -to %s -db %s -file %s -day 180",
			     BearbProg,
				 s_heute,
				 s_bisdatum,
				 db,
				 filename );
	else
		sprintf( Command, "%s -ld %s -to %s -db %s -file %s",
			     BearbProg,
				 s_heute,
				 s_bisdatum,
				 db,
				 filename );
}

static void GenCommandStringAHSperre( char *Command, char *db, long heute )
{
    char s_datum[11];

	GenAHSperreDatum( heute, s_datum );

	sprintf( Command, "zpmasaen 7 %s zpcronpf %s", db, s_datum );
}

static void GenCommandStringChargen( char *Command, char *db, long heute )
{
    char s_datum[11];

	GenChargenDatum( heute, s_datum );

	sprintf( Command, "zpmasaen 8 1 %s zpmasaen %s", db, s_datum );
}

static void GenCommandStringProtokoll( char *Command, char *db, long heute )
{
    char s_datum[11];

	GenProtokollDatum( heute, s_datum );

	sprintf( Command, "zpprotok 1 %s %s", db, s_datum );
}

static void GenCommandStringRabatte( char *Command, char *db, long heute, short filialnr )
{
    char s_datum[11];

	GenRabattDatum( heute, s_datum, filialnr );

	sprintf( Command, "zpmasaen 8 2 %s zpcronpf %s", db, s_datum );
}

static void GenCommandStringPreiserhoehungen( char *Command, char *db, long heute )
{
    char s_datum[11];

	GenPreiserhoehungsDatum( heute, s_datum );

	sprintf( Command, "zpmasaen 8 3 %s zpcronpf %s", db, s_datum );
}

static void GenCommandStringTransferCsc( char *Command, char *db, long heute )
{
    char s_datum[11];

	GenTransferCscDatum( heute, s_datum );

	sprintf( Command, "zpmasaen 8 4 %s zpcronpf %s", db, s_datum );
}

static void GenCommandStringBlockExpiredPseudoArticles( char *Command, char *db, long heute )
{
    char s_datum[11];

	GenBlockExpiredPseudoArticlesDatum( heute, s_datum );

	sprintf( Command, "zpmasaen 12 %s zpmasaen %s", db, s_datum );
}

static void GenCommandStringIncogest( char *Command, char *db, long heute, long bisdatum, short filialnr)
{
    char s_heute[11];
    char s_bisdatum[11];
	char filename[20];

    OutDatum( heute,    s_heute );
    OutDatum( bisdatum, s_bisdatum );
	
	if (filialnr == 42)
		strcpy (filename, "dezivryfr.txt");
	else
		strcpy (filename, "dezfr.txt");

	sprintf( Command, "tpulzpfrance -ld %s -to %s -db %s -file %s",
				 s_heute,
				 s_bisdatum,
				 db,
				 filename);
}

static void GenCommandStringLibra( char *Command, char *db, long heute, long bisdatum, short filialnr)
{
    char s_heute[11];
    char s_bisdatum[11];

    if (filialnr) {}    // prevents compiler warning

    OutDatum( heute,    s_heute );
    OutDatum( bisdatum, s_bisdatum );
	
	sprintf( Command, "tpulzpbulgaria -ld %s -to %s -db %s",
				 s_heute,
				 s_bisdatum,
				 db);
}

static void GenCommandStringRabattgruppen( char *Command, char *db, long heute, long bisdatum )
{
    char s_heute[11];
    char s_bisdatum[11];

    OutDatum( heute,    s_heute );
    OutDatum( bisdatum, s_bisdatum );
	
	sprintf( Command, "zpcalcrg 1 %s %s %s",
			    db,
				s_heute,
				s_bisdatum );
}

static void GenCommandStringCalcExfactory( char *Command, char *db, long heute, long bisdatum )
{
    char s_heute[11];
    char s_bisdatum[11];

    OutDatum2( heute,    s_heute );
    OutDatum2( bisdatum, s_bisdatum );
	
	sprintf( Command, "zpcalcprice 6 %s %s %s",
			    db,
				s_heute,
				s_bisdatum );
}

static void GenCommandStringDailyClosing( char *Command, char *db, long heute, long bisdatum )
{
    char s_heute[11];
    char s_bisdatum[11];

    OutDatum2( heute,    s_heute );
    OutDatum2( bisdatum, s_bisdatum );
	
	sprintf( Command, "zpdailyclosing 1 %s %s %s %s",
			    db,
				ProgName,
				s_heute,
				s_bisdatum );
}

static void GenCommandStringDailyClosing2( char *Command, char *db, long heute, long bisdatum )
{
    char s_heute[11];
    char s_bisdatum[11];

    OutDatum2( heute,    s_heute );
    OutDatum2( bisdatum, s_bisdatum );
	
	sprintf( Command, "zpdailyclosing 2 %s %s %s %s",
			    db,
				ProgName,
				s_heute,
				s_bisdatum );
}

static void GenCommandStringDailyClosing3( char *Command, char *db)
{
    sprintf( Command, "zpdailyclosing 3 %s %s",
			    db,
				ProgName );
}

static void GenCommandStringDailyClosing4( char *Command, char *db)
{
    sprintf( Command, "zpdailyclosing 4 %s",
			    db );
}

static void GenCommandStringTransferRefund( char *Command, char *db, long heute, long bisdatum )
{
    char s_heute[11];
    char s_bisdatum[11];

    OutDatum2( heute,    s_heute );
    OutDatum2( bisdatum, s_bisdatum );
	
	sprintf( Command, "zpcalcprice 7 %s %s %s",
			    db,
				s_heute,
				s_bisdatum );
}

static void GenCommandStringSpannencluster( char *Command, char *db, long bisdatum )
{
    char s_datum1[9];
    char s_datum2[9];

	GenSpannenclusterDatum( bisdatum, s_datum1, s_datum2 );

	sprintf( Command, "zpcalcrg 2 %s %s %s", db, s_datum1, s_datum2 );
}

/* #ifdef MIT_AUTIDM */
static void GenCommandStringAutidem( char *Command, char *db )
{
    sprintf( Command, "%s 3 %s %d",
	         BearbProgAutidem,
			 db,
		     AUTIDEM_TAGE );
}

/* #ifdef ON_CLIENT

static int SystemAufrufAutidem( char *Command )
{
   return system( Command );
}

#else

static int SystemAufrufAutidem( char *Command )
{
    char str[100];
    strcpy ( str, Command );
    strcat ( str, " > /dev/null" );

    // AIX/Informix workaround:
    //   save previous signal handler and 
    //   install default handler temporarily
    void (* pPrevSigHandler)(int) = signal(SIGCHLD, SIG_DFL);
    
    int ret = system( str );

    //   restore saved signal handler
    void (* pDflSigHandler)(int) = signal(SIGCHLD, pPrevSigHandler);

    assert(SIG_DFL == pDflSigHandler);
    if (pDflSigHandler) {} // compiler warning

    return ret;
}

#endif  /* ON_CLIENT */

/* #endif  /* MIT_AUTIDM */ 

#ifdef ON_CLIENT

static int SystemAufruf( char *Command )
{
   return system( Command );
}

#else

static int SystemAufruf( char *Command )
{
    // AIX/Informix workaround:
    //   save previous signal handler and 
    //   install default handler temporarily
    void (* pPrevSigHandler)(int) = signal(SIGCHLD, SIG_DFL);

    int ret = UnxHsystem( Command );

    //   restore saved signal handler
    void (* pDflSigHandler)(int) = signal(SIGCHLD, pPrevSigHandler);

    assert(SIG_DFL == pDflSigHandler);
    if (pDflSigHandler) {} // compiler warning

    return ret;
}

#endif

/* ---------------------------------------------------------------------- *
 *     Hauptprogramm                                                      *
 * ---------------------------------------------------------------------- */

#ifndef ON_CLIENT

static char *GetProgname( char *progname )
{
   int i;
   i = strlen(progname) - 1;
   while ( i >= 0 && progname[i] != '/' ) i--;
   return &progname[i+1];
}

static int CheckProcess( char *progname, int *ipPid )
{
   FILE *infile;
   char buf[512];
   int  i;
   int  n;
   int  pos;
   int  lng;
   char *process;

   *ipPid = 0;

   i = strlen(progname) - 1;
   while ( i >= 0 && progname[i] != '/' ) i--;
   process = &progname[i+1];
   if ( ( lng = strlen(process) ) == 0 ) return 0;

   strcpy( buf, "ps -ef|grep -v grep|grep \"" );
   strcat( buf, process );
   strcat( buf, "\"" );

   if ( ( infile = (FILE *)popen( buf, "r") ) == NULL )
      return 0;

   for( i = 0; i < 512; i++ )
   {
     int ch = getc(infile);

     if (EOF == ch)
         break;
     else
         buf[i] = (char)ch;

     if ( buf[i] == '\n' )
     {
		int pid;
        buf[i] = '\0';

		/* skip leading blanks */
		n = 0;
		while ( buf[n] && buf[n] == ' ' ) n++;
		/* pos second field -> pid */
		while ( buf[n] && buf[n] != ' ' ) n++;
		while ( buf[n] && buf[n] == ' ' ) n++;
		pid = atol( &buf[n] );
		
		/* pos 8th field -> processname */
		pos = 0;
		while ( pos++ < 6 )
		{
			while ( buf[n] && buf[n] != ' ' ) n++;
			while ( buf[n] && buf[n] == ' ' ) n++;
		}

		/* scan processname without path */
		while ( buf[n] && buf[n] != ' ' ) n++;
		n--;
		while ( buf[n] != '/' && buf[n] != ' ' ) n--;
		n++;
		if ( strncmp( &buf[n], process, lng ) == 0 )
		{
			if ( getpid() != pid )
	        {
			   *ipPid = pid;
	           pclose( infile );
		       return 0;
			}
			*ipPid = pid;
        }

        i = 0;
      }
   }
   pclose (infile);
   return 1;
}

#endif

void ReturncodeAusgabe( int ret, short filialnr )
{
    char  cStr[200];

	sprintf( cStr, "Returncode: %d", ret );
	if ( ret == 0 )
		ErrOut ( S_HINWEIS, filialnr, cStr );
	else
		ErrOut ( S_FEHLER, filialnr, cStr );
}

short CheckParameterkd( char *Command, char Sonderlauf )
{
	char buf[200];
	char buf2[50];
	double dCount = 0.0;
   
	sprintf( buf, "select count(*) from PARAMETERKD where FILIALNR = 0 and PROGRAMMNAME = 'zpcronpf' "
				  "and PARAMETERNAME = '%s'", Command );

	if ( Sonderlauf != ' ' )
		sprintf( buf2, " and ZWECK = '%c'", Sonderlauf );
	else
		sprintf( buf2, " and ZWECK = ''" );

	strcat ( buf, buf2 );

	if ( SqlRead( buf, &dCount, NULL ) == 0 )
	{
		if ( dCount > 0.5 )
			return 0;
	}

	return 1;   
}

int main( int argc, char *argv[])
{
    short filialnr;
    int   ret;
    int   ret_all;
    int   i, j;
    int   test_mode = 0;
    int   TestAnz = 0;
    short Parameter_Error = 0;
    short IstSamstagArbeitstag = 0;
    short IstSonntagArbeitstag = 0;
    short IstFeiertagArbeitstag = 0;
	short AnzahlZusaetzlicheParameter;
	int   iStatus;
    long  heute;
    long  zeit;
    long  bisdatum;
    char  *dbase;
    char  cStr[200];
    char  Command[80];
	char  Sonderlauf = ' ';
    char  log_datum[11];
    char *str1;
    int lng;
    int SpannenclusterFlag;

#ifdef ON_CLIENT
    HNMP handle;
#else
    int  iPid;
#endif

	/* dummy call to prevent from optimizing version string out of binary */
	const char* version = getVersion();

    if (argc >= 3) 
	{
        dbase = argv[1];
        filialnr = atoi( argv[2] );

		/* andere Defaultbelegung für Sonder-Arbeitstage in Bulgarien */
		if (strcmp(dbase, "ibg21") == 0)
		{
			IstSamstagArbeitstag = 1;
			IstSonntagArbeitstag = 1;
		}
		
		AnzahlZusaetzlicheParameter = argc - 3;
		i = 3;

		while (AnzahlZusaetzlicheParameter > 0) 
		{
			if (argv[i][0] == 'A')
			{
				if ( argv[i][1] == '0' || argv[i][1] == '1')
					IstSamstagArbeitstag = argv[i][1] - 48;
				else 
					Parameter_Error = 1;

				if ( argv[i][2] == '0' || argv[i][2] == '1')
					IstSonntagArbeitstag = argv[i][2] - 48;
				else 
					Parameter_Error = 1;

				if ( argv[i][3] == '0' || argv[i][3] == '1')
					IstFeiertagArbeitstag = argv[i][3] - 48;
				else 
					Parameter_Error = 1;
			}
			else if (argv[i][0] == 'S')
			{
				Sonderlauf = argv[i][1];
			}
			else if (argv[i][0] == 'T')
			{
				test_mode = 1;
				/* printf_mode = 2; */
				TestAnz = atoi( &argv[i][1] );

				if ( TestAnz < 0 )
					TestAnz = 14;
				if ( TestAnz > 999 )
					TestAnz = 999;
			}
			else
				Parameter_Error = 1;

			AnzahlZusaetzlicheParameter--;
			i++;
		}
	}
	else
		Parameter_Error = 1;

	if (Parameter_Error == 1)
    {
       printf_mode = 3;
       ErrOut( S_HINWEIS, 0, "START" );
       sprintf( cStr, "usage: %s database filialnr [Annn] [Sn] [Tnnn]", ProgName );
       ErrOut( S_FEHLER,  0, cStr );
       ErrOut( S_HINWEIS, 0, "ENDE" );
       exit( 1 );
    }

	ErrOut( S_HINWEIS, filialnr, "--------------------------------------------------" );
	ErrOut( S_HINWEIS, filialnr, "START" );

	/* Anzeige Parameter im Log analog den anderen ZDP-Batchprogrammen */
	lng = 0;
	
	for ( j = 1; j < argc; j++ )
		lng += strlen( argv[j] );

	str1 = malloc( lng + argc + 1 );
	if ( str1 != NULL )
	{
		*str1 = '\0';

		for ( j = 1; j < argc; j++ )
		{
			strcat( str1, argv[j] );
			if ( j < argc - 1 )
				strcat( str1, " " );
		}
	}

	ErrOut( S_HINWEIS, filialnr, str1 );
	free ( str1 );

#ifndef ON_CLIENT
    if ( strcmp( GetProgname( argv[0] ), ProgName )  != 0 )
    {
        printf_mode = 3;
        sprintf( cStr, "Programm unter falschem Namen gestartet: %s",
                        GetProgname( argv[0] ) );

        ErrOut( S_FEHLER, filialnr, cStr );
        ErrOut( S_HINWEIS, filialnr, "ENDE" );
        exit( 1 );
    }

    iPid = -1;
    if ( !CheckProcess( ProgName, &iPid ) )
    {
        printf_mode = 3;
        sprintf( cStr, "Programm bereits aktiv, Pid = %d", iPid );
        ErrOut( S_WARNUNG, filialnr, cStr );
        ErrOut( S_HINWEIS, filialnr, "ENDE" );
        exit( 1 );
    }
#endif

#ifdef ON_CLIENT
    if ( ViaEshuOpen( &handle, "zdev21", "uiserv" ) != 0 )
      {
        printf( "%s\n", DynErrmld() );
        exit(1);
      }
#endif

    ret = 0;
    ret_all = 0;

	if ( OpenBase( dbase, cStr ) == 0 )
    {
       iStatus = LeseFeiertage( filialnr );
/* hier noch nicht wegen lesen parameterkd
	   CloseBase( ); */ 

       if ( iStatus >= 0 )
       {
          heute = GregToday();
          zeit = GetPhoTime();

		  /* Tag um 1 reduzieren, falls Joblauf zwischen Mitternacht und 06:00 */
		  if (zeit < 60000)
		  {
			 heute--;

			 sprintf(cStr, 
                     "aktuelle Zeit: %ld, Datum wurde um einen Tag reduziert", 
                     zeit );
			 ErrOut( S_WARNUNG, filialnr, cStr );
		  }

/*        if ( test_mode )
          { */
		     do
			 {
				  /* Test */
				  /* heute = 156705; <-- entspricht dem 31/10/2011 */
				  /* heute = 156887; <-- entspricht dem 30/04/2012 */
				  /* heute = 159788; <-- entspricht dem 09/04/2020 (Gründonnerstag) */
				  /* Test Ende */

				  GenLogDatum( heute, log_datum, filialnr );

				  if ( test_mode )
				  {
					  sprintf( cStr, "alle Aufrufe nur zum Test fuer Datum: %s", log_datum );
					  ErrOut ( S_HINWEIS, filialnr, cStr );
				  }

				  if ( !IsArbeitsTagNeu( heute, filialnr, IstSamstagArbeitstag, IstSonntagArbeitstag, IstFeiertagArbeitstag ) )
				  {
					  sprintf( cStr, "aktueller Tag %s ist kein Arbeitstag, Programm laeuft trotzdem weiter", log_datum );
					  ErrOut( S_WARNUNG, filialnr, cStr );
				  }

				  bisdatum = heute;
			
				  do
				  {
					  bisdatum++;
				  } while( !IsArbeitsTagNeu ( bisdatum, filialnr, IstSamstagArbeitstag, IstSonntagArbeitstag, IstFeiertagArbeitstag ) );

				  /* Aufruf zpautidm: Retourensperre aufheben */
				  if ( CheckParameterkd ("zpautidm", Sonderlauf) == 0 )
				  {
					  GenCommandStringAutidem( Command, dbase );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpmasaen (mode 8,4): alte Einträge in ctransfercsc löschen */
				  if ( CheckParameterkd ("zpmasaen 8 4", Sonderlauf) == 0 )
				  {
					  GenCommandStringTransferCsc( Command, dbase, heute );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  }
				  }
				  
				  /* Aufruf zpmasaen (mode 8,1): alte Chargenrückrufe löschen */
				  if ( CheckParameterkd ("zpmasaen 8 1", Sonderlauf) == 0 )
				  {
				  	  GenCommandStringChargen( Command, dbase, heute );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpdailyclosing (mode 3): NTIN erzeugen für alle aktiven Artikel */
				  if ( CheckParameterkd ("zpdailyclosing 3", Sonderlauf) == 0 )
				  {
					  GenCommandStringDailyClosing3( Command, dbase );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpdailyclosing (mode 4): carticlecode-Eintrag erzeugen mit Artikelnr. des Herstellers */
				  if ( CheckParameterkd ("zpdailyclosing 4", Sonderlauf) == 0 )
				  {
					  GenCommandStringDailyClosing4( Command, dbase );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpmasaen (mode 7): Sperrkennzeichen setzen für AH-Artikel */
				  if ( CheckParameterkd ("zpmasaen 7", Sonderlauf) == 0 )
				  {
					  GenCommandStringAHSperre( Command, dbase, heute );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpmasaen (mode 8,3): alte Preiserhöhungen löschen */
				  if ( CheckParameterkd ("zpmasaen 8 3", Sonderlauf) == 0 )
				  {
					  GenCommandStringPreiserhoehungen( Command, dbase, heute );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }
					 
				  SpannenclusterFlag = SpannenclusterPruefung ( heute, bisdatum );
				  if (SpannenclusterFlag > 0)
				  {
					  /* Aufruf zpcalcrg (mode 2): Neuberechnung Spannencluster */
					  if ( CheckParameterkd ("zpcalcrg 2", Sonderlauf) == 0 )
				      {
						  GenCommandStringSpannencluster( Command, dbase, bisdatum );
						  sprintf( cStr, "AUFRUF: %s", Command );
						  ErrOut ( S_HINWEIS, filialnr, cStr );

 						  if ( !test_mode )
						  {
							  ret = SystemAufruf( Command );
							  ret_all += ret;
							  ReturncodeAusgabe( ret, filialnr );
						  } 
					  }
				  }

				  /* Aufruf zpmasaen (mode 8,2): alte Rabatte löschen */
				  if ( CheckParameterkd ("zpmasaen 8 2", Sonderlauf) == 0 )
				  {
					  GenCommandStringRabatte( Command, dbase, heute, filialnr );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpcalcrg (mode 1): Übertragung Erstattungswerte aus cartrefundfrance in zartfrance */
				  if ( CheckParameterkd ("zpcalcrg 1", Sonderlauf) == 0 )				 
				  {
					  GenCommandStringRabattgruppen( Command, dbase, heute, bisdatum );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpcalcprice (mode 7): Neuberechnung Rabattgruppen */
				  if ( CheckParameterkd ("zpcalcprice 7", Sonderlauf) == 0 )				 
				  {
					  GenCommandStringTransferRefund( Command, dbase, heute, bisdatum );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpdailyclosing (mode 2): Änderung AVP / LPPR-Daten */
				  if ( CheckParameterkd ("zpdailyclosing 2", Sonderlauf) == 0 )				 
				  {
					  GenCommandStringDailyClosing2( Command, dbase, heute, bisdatum );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf tpulzpfrance: erzeugen dezfr für Incogest */
				  if ( CheckParameterkd ("tpulzpfrance", Sonderlauf) == 0 )				 
				  {				 
					  GenCommandStringIncogest( Command, dbase, heute, bisdatum, filialnr );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpmasaen (mode 12): Sperrkennzeichen setzen für abgelaufene Steller */
				  if ( CheckParameterkd ("zpmasaen 12", Sonderlauf) == 0 )				 
				  {
					  GenCommandStringBlockExpiredPseudoArticles( Command, dbase, heute );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf tpulzpbulgaria: erzeugen dezbg für Libra */
				  if ( CheckParameterkd ("tpulzpbulgaria", Sonderlauf) == 0 )				 
				  {
					  GenCommandStringLibra( Command, dbase, heute, bisdatum, filialnr );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpcalcprice (mode 6) zum Berechnen Grosso aus LBP (Exfactoryrabatte aus PPE) */
				  if ( CheckParameterkd ("zpcalcprice 6", Sonderlauf) == 0 )				 				 
				  {
					  GenCommandStringCalcExfactory( Command, dbase, heute, bisdatum );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf zpdailyclosing (mode 1) zum Setzen AH-Datum in Artikelnamen */
				  if ( CheckParameterkd ("zpdailyclosing 1", Sonderlauf) == 0 )	
				  {
					  GenCommandStringDailyClosing( Command, dbase, heute, bisdatum );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  } 
				  }

				  /* Aufruf tpulzentpfl: erzeugen DEZAP für Pharmos */
				  if ( CheckParameterkd ("tpulzentpfl", Sonderlauf) == 0 )	
				  {
					  GenCommandString( Command, dbase, heute, bisdatum, filialnr );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );

 					  if ( !test_mode )
					  {
					      ret = SystemAufruf( Command );
					      ret_all += ret;
					      ReturncodeAusgabe( ret, filialnr );
					  }
				  } 

				  /* Aufruf zpprotok: Reorganisation Protokoll-Tabellen */
				  if ( CheckParameterkd ("zpprotok", Sonderlauf) == 0 )
				  {
					  GenCommandStringProtokoll( Command, dbase, heute );
					  sprintf( cStr, "AUFRUF: %s", Command );
					  ErrOut ( S_HINWEIS, filialnr, cStr );
 					  if ( !test_mode )
					  {
						  ret = SystemAufruf( Command );
						  ret_all += ret;
						  ReturncodeAusgabe( ret, filialnr );
					  }
				  } 

                TestAnz--;
				heute++;
             }  while ( TestAnz >= 0 );
       }
       else
       {
          sprintf( cStr, "Feiertage lesen: %s", FeierError );
          ErrOut ( S_FEHLER, filialnr, cStr );
       }

	   CloseBase( ); 
    }
    else
    {
       ErrOut ( S_FEHLER, filialnr, cStr );
    }

/*     if ( !test_mode ) */
	ErrOut ( S_HINWEIS, filialnr, "ENDE" );

#ifdef ON_CLIENT
    NmpClose();
#endif

/*  return ret; */
    return ret_all;
}

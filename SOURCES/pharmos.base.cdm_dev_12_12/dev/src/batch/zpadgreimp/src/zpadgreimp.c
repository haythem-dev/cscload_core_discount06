/* ---------------------------------------------------------------------- *
 *                            zpadreimp.c                                 *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        :                                                     *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 13.03.06                                            *
 *   letztes Update :                                                     *
 *   Autor          : K.Hinz                                              *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.1.1 : zpadgreimp 02/08/2023 KT";
}

/*!
\page page4 zpadgreimp
________________________________________________________________________________________
\version	1.1.1
\date		02.08.2023
\internal
- KT: I-23043187: Fix for temporary table ttzartverk after change in table zartverk
\endinternal
________________________________________________________________________________________
\version	1.1.0
\date		19.03.2013
\internal
- TH: AIX build
\endinternal
________________________________________________________________________________________
\version	1.0.4
\date		25.07.2012
\internal
- TH: voodoo table header
\endinternal
_______________________________________________________________________________________
\version	1.0.3
\date		29.05.2012
\internal
- TH: Korrektur wegen SR-077107
\endinternal
________________________________________________________________________________________
\version	1.0.2
\date		08.07.2008
\internal
- RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, Ausgabe Log auch bei Aufruf aus Windows (EkZdp)
\endinternal

*/

/* 1.0.2  08.07.2008 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						 Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.0.3  29.05.2012 TH: Korrektur wegen SR-077107 */
/* 1.0.4  25.07.2012 TH: voodoo table header */
/* 1.1.0  19.03.2013 TH: AIX build */


/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include <libscsvoodoo.h>

#include "zpadgreimp.h"
#include "zadgoreimp.h"
#include "zreimpherst.h"
#include "zartverk.h"			/* when table zartverk was changed, also temporary table ttzartverk has to be changed */
#include "zpznpflege.h"

/* ----- Prototype --------- */
void StarteVerarbeitung(char *db, char *buf);
/* SQL-Funktionen */
long OpenBase( const char * const db, char *errmld );
void CloseBase();
long CreateTempTableZartverk( char *errmld );
long sel_zreimpherst_all(char *errmld);
int sel_zartikel	( const long art_nr, long * datum_ah, char *errmld);
long loop_aHerst(char* buf);
long loop_zadgoreimp_herst( char *errmld,const long lHersteller );
long loop_zadgoreimp_artikel( char *errmld,const long lPzn_Orig,const long lPzn_Reimp,const long lHersteller );
long ins_ttZartverk(char *errmld, const struct ZARTVERK * const stZartVerk );
long loop_ZartVerk_Delete(char *errmld);
long loop_ZartVerk_Manuell(char *errmld);
long loop_ttZartVerk(char *errmld);
long ReadTempTable( char *errmld ,long lPznBas, long lPznVerk);
long ins_ZartVerk(char *errmld, const struct ZARTVERK * const stZartVerk );
long del_ZartVerk(char *errmld, const struct ZARTVERK * const stZartVerk );
long upd_ZartVerk(char *errmld, const struct ZARTVERK * const stZartVerk ,const struct ZARTVERK * const stZartVerkAlt);
long ReadZartVerk( char *errmld , struct ZARTVERK*  pStZartVerk);
long store_Zpznpflege(char *errmld, const struct ZARTVERK * const stZartVerk );
/* ---------------- Programm-Ausahl ----------------- */

static struct ZREIMPHERST aHerst[MAX_ENTRIES];
static long lUpdates = 0;
static long lInserts = 0;
static long lDeletes = 0;
static short sModus = 0;

void ProgUsage( char *buf )
{
  strcat( buf, "1. zpadgreimp 1 database  \n" \
               "   aktualisieren zartverk auf Basis  zadgoreimp\n" \
			   "2. zpadgreimp 2 database \n"  \
			   "   Testlauf ohne Updates\n"   );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   switch ( *argv[0] )     {
	case '2':
        if ( argc != 2 )   {
          s = 1;
          ProgUsage( buf );
        }
		else {
			StarteVerarbeitung(argv[1], buf);
		}
		s = 0;
        break;

	case '1':
        if ( argc != 2 )   {
          s = 1;
          ProgUsage( buf );
        }
		else {
			sModus = WITHUPDATES;
			StarteVerarbeitung(argv[1], buf);
		}
		s = 0;
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

/* ---------------------------------------------------------------------- */
void StarteVerarbeitung(char *db, char *buf)
{
	long lRc = 0;
	long lGelesen = 0, lInserts = 0,lUpdates=0;

	if ( OpenBase( db, buf ) != 0 )
		return;

	lRc = CreateTempTableZartverk( buf );
	
	if ( 0 == lRc) 	
		/* Alle Tabelleneintraege fuer zreimpherst lesen*/
		/* und in array aHerst schreiben */
		lRc =  sel_zreimpherst_all(buf);

	if ( 0 == lRc)
		/* Temp Table ttzartverk fuellen */
		lRc = loop_aHerst(buf);

	if ( 0 == lRc)
		/* Lesen zartverk -> manuelle Eintraege in ttZartVerg schreiben */
		lRc = loop_ZartVerk_Manuell(buf);

	if ( 0 == lRc)
		/* Lesen ttzartverk -> Insert/ Update Saetze in zartverk , die nicht in zartverk stehen bzw. sich geändert haben*/
		lRc = loop_ttZartVerk(buf);

	if ( 0 == lRc)
		/* Lesen zartverk -> Loeschen Saetze, die nicht in ttzartverk stehen */
		lRc = loop_ZartVerk_Delete(buf);

	CloseBase();
}

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
   if ( s != 0 )    {
      strcpy( errmld, base );
      strcat( errmld, ": " );
      strcat( errmld, DynErrmld() );
      return s;
   }

   s = SqlExecuteImm("set isolation to dirty read" );
   if ( s == SQL_SETISOLA_ERROR ) s = 0;
   if ( s != 0 )   {
     strcpy( errmld, "set isolation: " );
     strcat( errmld, DynErrmld() );
     CloseBase( );
     return s;
   }

   s = SqlExecuteImm( "SET LOCK MODE TO WAIT 10" );
   if ( s == SQL_SETISOLA_ERROR ) s = 0;
   if ( s != 0 )    {
     strcat( errmld, "set lock mode: ");
     strcat( errmld, DynErrmld() );
     CloseBase( );
     return s;
   }
   return 0;
}
/* ---------------------------------------------------------------------- */
/* Create Temp Table ttZartverk
/* ---------------------------------------------------------------------- */
long CreateTempTableZartverk( char *errmld )
{
   long s;
   char sql[1000];
   sprintf( sql, "create temp table %s ("         \
                 "ARTIKEL_NR_BAS INTEGER NOT NULL," \
                 "ARTIKEL_NR_VERK INTEGER NOT NULL," \
                 "MANUELL CHAR(1) NOT NULL,"  \
                 "SORTIMENT CHAR(1) NOT NULL," \
                 "VERK_ART CHAR(1) NOT NULL," \
                 "PRIORITAET SMALLINT NOT NULL," \
				 "IDFNR INTEGER NOT NULL) with no log" ,
                 "ttzartverk");
   s = SqlExecuteImm( sql );
   if ( s != 0 )    {
      strcpy( errmld, DynErrmld() );
	  return s;
	}
	memset(sql,' ',1000);
    sprintf( sql, "create unique index i_ttzartverk_1 on ttzartverk (artikel_nr_bas,artikel_nr_verk)");
   s = SqlExecuteImm( sql );
   if ( s != 0 )    {
      strcpy( errmld, DynErrmld() );
   }

   return s;
}

/* ------------------------------------------------------------------- */
void UpdateStatistics( const char * const relation )
{
   char sql[100];
   strcpy( sql, "update statistics for table " );
   strcat( sql, relation );
   SqlExecuteImm( sql );
}
/* ------------------------------------------------------------------- */
long GetDate( void )
 {
   static char szTimeStr[21];
   struct tm *ptrTm;
   long lmSec;

   lmSec = time( (long *)0 );
   ptrTm = localtime( &lmSec );

   sprintf( szTimeStr, "%04d%02d%02d",ptrTm->tm_year+1900,  ptrTm->tm_mon + 1,ptrTm->tm_mday);
	return atol(szTimeStr);
 }
/* ------------------------------------------------------------------- */
int sel_zartikel	( const long art_nr, long *datum_ah,  char *errmld)
{
    char sql[150];
    int status;
	long pzn;
    
    sprintf( sql, "select artikel_nr, datum_ah from zartikel where artikel_nr=%ld",art_nr );

    status = SqlRead( sql, &pzn, datum_ah, NULL );
    if ( status != 0 && status != 100) 	{
		strcpy( errmld, "zartikel (Suche nach Artikelnr): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}
/* ---------------------------------------------------------------------- */
/* Füllen aHerst Array mit bisherigen Einträgen aus zreimpherst
/* ---------------------------------------------------------------------- */
long sel_zreimpherst_all(char *errmld)

{
	char buf[2000];
	long lRetCode;
	HDYNSQL	m_fd;
	long lAnzahl = 0;
	struct ZREIMPHERST* pHerst = &aHerst[0];
	
	sprintf(buf,"select %s from zreimpherst order by hersteller_nr_bas,prioritaet",PROJECTION_ZREIMPHERST);
	lRetCode = SqlOpenScrollCs(&m_fd, buf);

	if ( 0 != lRetCode) {
		strcpy( errmld, "zreimpherst (Open Cursor): " );
		strcat( errmld, DynErrmld() );
		return lRetCode;
	}

	while ( 0 == lRetCode ) {
		lRetCode = SqlBufferedFetch(m_fd,1 ,20, pHerst++, NULL);
		if (++lAnzahl >= MAX_ENTRIES)	{
			strcpy( errmld, "Bitte Hersteller Array redimensionieren" );
			return -1;
		}
	}
	lRetCode = SqlCloseCs(m_fd);
	return 0;
}
/* ---------------------------------------------------------------------- */
/* Schleife lesen Basishersteller
/* ---------------------------------------------------------------------- */
long loop_aHerst(char* buf)
{
	struct ZREIMPHERST* pHerst = &aHerst[0];
	long lHersteller;

	lHersteller = -1;
	while (pHerst->HERSTELLER_NR_BAS != 0) 	{
		if (pHerst->HERSTELLER_NR_BAS != lHersteller) {
			lHersteller = pHerst->HERSTELLER_NR_BAS;
			/* Verarbeitung Pro Basishersteller*/
			if (0 != loop_zadgoreimp_herst(buf,lHersteller))
				return -1;
		}
		pHerst++;
	}
	return 0;
}

/* ---------------------------------------------------------------------- */
/* Schleife lesen Reimportartikel für Basishersteller
/* ---------------------------------------------------------------------- */
long loop_zadgoreimp_herst( char *errmld,const long lHersteller )
{
	char buf[2000];
	long lRetCode;
	HDYNSQL	m_fd;
	long lAnzahl = 0;
	struct ZADGOREIMP stZadgoreimp;
	
	sprintf(buf,"select %s from zadgoreimp where hersteller_nr = %ld",PROJECTION_ZADGOREIMP,lHersteller);
	lRetCode = SqlOpenScrollCs(&m_fd, buf);

	if ( 0 != lRetCode) {
		strcpy( errmld, "zadgoreimp (Open Cursor): " );
		strcat( errmld, DynErrmld() );
		return lRetCode;
	}

	while ( 0 == lRetCode ) {
		lRetCode = SqlBufferedFetch(m_fd,1 ,20, &stZadgoreimp, NULL);
		/* Verarbeiten aller Reimportlieferanten, die diesen Artikel vertreiben */
		if (0 == lRetCode)	{
			lRetCode = loop_zadgoreimp_artikel( errmld, stZadgoreimp.ARTIKEL_NR_ORIG,stZadgoreimp.ARTIKEL_NR_REIMP, lHersteller );
		}
	}
	lRetCode = SqlCloseCs(m_fd);

	return 0;
}


/* --------------------------------------------------------------------------------------------- */
/* Schleife lesen Reimportlieferanten für Artikel und Originallieferanten ( alle Reimportlieferanten)
/* --------------------------------------------------------------------------------------------- */
long loop_zadgoreimp_artikel( char *errmld,const long lPzn_Orig,const long lPzn_Reimp,const long lHersteller )
{
	char buf[2000];
	long lRetCode, lRetCode2;
	HDYNSQL	m_fd;
	long  lPzn;
	short lPrio = 1;
	struct ZARTVERK stZartverk;
	
	/* lHersteller ist der Originalhersteller */
	struct ZREIMPHERST* pHerst = &aHerst[0];

	/* Ueberlesen nicht zutreffender Hersteller */
	while ((pHerst->HERSTELLER_NR_BAS != 0) && (pHerst->HERSTELLER_NR_BAS != lHersteller))
		pHerst++;

	
	while (pHerst->HERSTELLER_NR_BAS == lHersteller)	{
	    sprintf( buf, "select artikel_nr_reimp "
				"from zadgoreimp where artikel_nr_orig=%ld and hersteller_nr = %ld",
				lPzn_Orig, pHerst->HERSTELLER_NR_VERK );
	    lRetCode = SqlRead( buf, &lPzn, NULL );
		/* Artikel hat fuer Reimport-Hersteller einen Eintrag in zadgoreimp */	
		if ( 0 == lRetCode)	{
			stZartverk.ARTIKEL_NR_BAS = lPzn_Reimp;
			stZartverk.ARTIKEL_NR_VERK  = lPzn;
			strcpy(stZartverk.VERK_ART,pHerst->VERK_ART);
			strcpy(stZartverk.SORTIMENT,"R\0");
			stZartverk.PRIORITAET = lPrio++;
			strcpy(stZartverk.MANUELL,"0\0");
			// stZartverk.IDFNR = 0;
			ins_ttZartverk(errmld,&stZartverk); 
		}
		pHerst++;
	}

	/* Alle fehlenden manuellen Zartverk Saetze fuer diese pzn in temp table eintragen */
	memset(buf,' ',1000);
	sprintf(buf,"select %s from zartverk where artikel_nr_bas = %ld and manuell = '1'",PROJECTION_ZARTVERK,lPzn_Reimp);
	lRetCode = SqlOpenScrollCs(&m_fd, buf);
	while ( 0 == lRetCode ) {
		lRetCode = SqlBufferedFetch(m_fd,1 ,20, &stZartverk, NULL);
		if (0 == lRetCode) 	{
			sprintf( buf, "select artikel_nr_bas from ttzartverk where artikel_nr_bas=%ld and artikel_nr_verk =%ld ",lPzn_Reimp,stZartverk.ARTIKEL_NR_VERK);
		    lRetCode2 = SqlRead( buf, &lPzn, NULL );
			if ( 100 == lRetCode2) 	{
				stZartverk.PRIORITAET = lPrio++;
				lRetCode = ins_ttZartverk(errmld,&stZartverk); 
			}
		}
	}
	lRetCode = SqlCloseCs(m_fd);

	return 0;
}
/* --------------------------------------------------------------------------------------------- */
/* Satz in Temp Table eintragen
/* --------------------------------------------------------------------------------------------- */

long ins_ttZartverk(char *errmld, const struct ZARTVERK* const st)
{
	char buf[2000];
	long lRetCode;

    /* I-23043187: set IDFNR always to 0, because it is only used in FR */
	sprintf(buf,"insert into ttzartverk (%s) SELECT '%ld','%ld','%s','%s','%s', NVL(MAX(prioritaet)+1, 1), 0 FROM ttzartverk where artikel_nr_bas = %ld",PROJECTION_ZARTVERK,
		st->ARTIKEL_NR_BAS,st->ARTIKEL_NR_VERK,
		st->MANUELL,st->SORTIMENT, 	st->VERK_ART, //st->PRIORITAET --> darf nicht 1:1 aus zartverk übernommen werden, da es sonst zu Fehlern beim durchgängigen Hochzählen kommen kann!
		st->ARTIKEL_NR_BAS);

	lRetCode= SqlExecuteImm( buf );
	if ( lRetCode != 0 )    {
      strcpy( errmld, DynErrmld() );
	  return lRetCode;
	}
	return lRetCode;
}


/* --------------------------------------------------------------------------------------------- */
/* Saetze aus ZartVerk loeschen, die nicht in ttZartVerk stehen
/* --------------------------------------------------------------------------------------------- */
long loop_ZartVerk_Delete(char *errmld)
{
	long lRetCode = 0,s;
	char buf[1000];
	HDYNSQL	m_fd ;
	struct ZARTVERK stZartVerk;

	memset(buf,' ',1000);

	sprintf(buf,"select %s from zartverk where sortiment = 'R'",PROJECTION_ZARTVERK);
	lRetCode = SqlOpenCsWh(&m_fd, buf);

   while ( lRetCode == 0  )
   {
     lRetCode =  SqlFetch( m_fd, 1, &stZartVerk, NULL );

     if ( lRetCode == 0 )
     {
		s = ReadTempTable( errmld,stZartVerk.ARTIKEL_NR_BAS,stZartVerk.ARTIKEL_NR_VERK);
		if ( s == 100 )	{
			lRetCode = del_ZartVerk( errmld,&stZartVerk );
		}
		else if ( s != 0 )  {
			strcpy( errmld, DynErrmld() );
			lRetCode = s;
		}
     }
     else if ( lRetCode != 100 ) {
       strcpy( errmld, DynErrmld() );
     }
   }

   /* Schleife lesen Zartverk endet mit 100 */
   if ( 100 == lRetCode )
	   lRetCode = 0;

   if ( 0 == lRetCode)
	   if (WITHUPDATES == sModus)
		sprintf( errmld, "ZartVerk Inserts %ld Updates %ld Deletes %ld",lInserts,lUpdates,lDeletes);
	   else
		sprintf( errmld, "(Testlauf) ZartVerk Inserts %ld Updates %ld Deletes %ld",lInserts,lUpdates,lDeletes);
   SqlCloseCs( m_fd );
   return lRetCode;
}


/* --------------------------------------------------------------------------------------------- */
/* Alle manuell erfassten Saetze aus Zartverg, die noch fehlen in Temp Table uebertragen
/* --------------------------------------------------------------------------------------------- */
long loop_ZartVerk_Manuell(char *errmld)
{
	long lRetCode = 0,s;
	char buf[1000];
	HDYNSQL	m_fd ;
	struct ZARTVERK stZartVerk;

	memset(buf,' ',1000);

	sprintf(buf,"select %s from zartverk where manuell='1' and sortiment = 'R'",PROJECTION_ZARTVERK);
	lRetCode = SqlOpenCsWh(&m_fd, buf);

   while ( lRetCode == 0  )
   {
     lRetCode =  SqlFetch( m_fd, 1, &stZartVerk, NULL );

     if ( lRetCode == 0 )
     {
		s = ReadTempTable( errmld,stZartVerk.ARTIKEL_NR_BAS,stZartVerk.ARTIKEL_NR_VERK);
		if ( s == 100 )	{
			lRetCode = ins_ttZartverk(errmld, &stZartVerk);
		}
		else if ( s != 0 )  {
			strcpy( errmld, DynErrmld() );
			lRetCode = s;
		}
     }
     else if ( lRetCode != 100 ) {
       strcpy( errmld, DynErrmld() );
     }
   }

   /* Schleife lesen Zartverk endet mit 100 */
   if ( lRetCode == 100 )
	   lRetCode = 0;

   SqlCloseCs( m_fd );
   return lRetCode;
}

/* --------------------------------------------------------------------------------------------- */
/* Saetze in ZartVerk aufnehmen, die sich geändert haben bzw nicht in ttZartVerk existieren
/* --------------------------------------------------------------------------------------------- */
long loop_ttZartVerk(char *errmld)
{
	long lRetCode = 0,s;
	char buf[1000];
	HDYNSQL	m_fd ;
	struct ZARTVERK stZartVerk;
	struct ZARTVERK stZartVerkAlt;

	memset(buf,' ',1000);

	sprintf(buf,"select %s from ttzartverk ",PROJECTION_ZARTVERK);
	lRetCode = SqlOpenCsWh(&m_fd, buf);

   while ( lRetCode == 0  )
   {
     lRetCode =  SqlFetch( m_fd, 1, &stZartVerk, NULL );

     if ( lRetCode == 0 )
     {
		 stZartVerkAlt.ARTIKEL_NR_BAS = stZartVerk.ARTIKEL_NR_BAS;
		 stZartVerkAlt.ARTIKEL_NR_VERK = stZartVerk.ARTIKEL_NR_VERK;
		s = ReadZartVerk( errmld , &stZartVerkAlt);

		if ( s == 100 )	{
			lRetCode = ins_ZartVerk( errmld,&stZartVerk );
		}
		else if ( s == 0) {
			lRetCode = upd_ZartVerk( errmld,&stZartVerk,&stZartVerkAlt );
		}
		else {
			strcpy( errmld, DynErrmld() );
			lRetCode = s;
		}
     }
     else if ( lRetCode != 100 ) {
       strcpy( errmld, DynErrmld() );
     }
   }

   /* Schleife lesen Zartverk endet mit 100 */
   if ( lRetCode == 100 )
		lRetCode = 0;
   else
		strcpy( errmld, DynErrmld() );
   SqlCloseCs( m_fd );
   return lRetCode;
}



/* --------------------------------------------------------------------------------------------- */
/* Pruefen, ob Satz in Temp Table existiert                                                      */
/* --------------------------------------------------------------------------------------------- */
long ReadTempTable( char *errmld ,long lPznBas, long lPznVerk)
{
   long s,lPzn;
   char sql[500];

   sprintf( sql, "select ARTIKEL_NR_BAS from ttzartverk where ARTIKEL_NR_BAS=%ld and ARTIKEL_NR_VERK=%ld",lPznBas,lPznVerk);
   s = SqlRead( sql, &lPzn, NULL );
   if (( s != 0 ) && ( s != 100 ))
     sprintf( errmld, "ReadTempTable: %s", DynErrmld() );
   return s;
}

/* --------------------------------------------------------------------------------------------- */
/* Pruefen, ob Satz in ZartVerk existiert                                                      */
/* --------------------------------------------------------------------------------------------- */
long ReadZartVerk( char *errmld , struct ZARTVERK*  pStZartVerk)
{
   long s;
   char sql[500];

   sprintf( sql, "select %s from zartverk where ARTIKEL_NR_BAS=%ld and ARTIKEL_NR_VERK=%ld",PROJECTION_ZARTVERK,pStZartVerk->ARTIKEL_NR_BAS,pStZartVerk->ARTIKEL_NR_VERK );
   s = SqlRead( sql, pStZartVerk, NULL );
   if (( s != 0 ) && ( s != 100 ))
     sprintf( errmld, "ReadZartVerk: %s", DynErrmld() );
   return s;
}
/* --------------------------------------------------------------------------------------------- */
/* Satz aus ZartVerk loeschen
/* --------------------------------------------------------------------------------------------- */
long del_ZartVerk(char *errmld, const struct ZARTVERK * const stZartVerk )
{
	char sql[100];
	long s;

	s = store_Zpznpflege(errmld,  stZartVerk );
	if (( s != 0 ) && ( s != 100 ))
		sprintf( errmld, "ins/upd zpznpflege: %s", DynErrmld() );
	if (0 == s) {
		sprintf( sql, "delete  from zartverk where ARTIKEL_NR_BAS=%ld and ARTIKEL_NR_VERK=%ld",stZartVerk->ARTIKEL_NR_BAS,stZartVerk->ARTIKEL_NR_VERK);
		lDeletes++;
		if (WITHUPDATES == sModus)		
			s = SqlExecuteImm( sql );
		if (( s != 0 ) && ( s != 100 ))
			sprintf( errmld, "delete zartverk: %s", DynErrmld() );
	}
   return s;
}

/* --------------------------------------------------------------------------------------------- */
/* Satz in ZartVerk einfuegen
/* --------------------------------------------------------------------------------------------- */
long ins_ZartVerk(char *errmld, const struct ZARTVERK* const st)
{
	char buf[2000];
	long lRetCode;

	lRetCode = store_Zpznpflege(errmld,  st );

	if (( lRetCode != 0 ) && ( lRetCode != 100 ))
		sprintf( errmld, "insert zartverk: %s", DynErrmld() );

	if (0 == lRetCode) {
		/* I-23043187: set IDFNR always to 0, because it is only used in FR */
		sprintf(buf,"insert into zartverk (%s) values(%ld,%ld,'%s','%s','%s',%ld, 0)",PROJECTION_ZARTVERK,
		st->ARTIKEL_NR_BAS,st->ARTIKEL_NR_VERK,
		st->MANUELL,st->SORTIMENT, 	st->VERK_ART,st->PRIORITAET);
		lRetCode = 0;
		lInserts++;
		if (WITHUPDATES == sModus)		
			lRetCode= SqlExecuteImm( buf );
		if ( 0 != lRetCode )    {
			strcpy( errmld, DynErrmld() );
			}
	}
	return lRetCode;
}

/* --------------------------------------------------------------------------------------------- */
/* Satz in ZartVerk updaten
/* --------------------------------------------------------------------------------------------- */
long upd_ZartVerk(char *errmld, const struct ZARTVERK* const st,const struct ZARTVERK* const stAlt)
{
	char buf[2000];
	long lRetCode;

	/* hat sich etwas geändert ???*/
	if (( strcmp(st->MANUELL,stAlt->MANUELL) == 0)	&& 
		( st->PRIORITAET == stAlt->PRIORITAET)		&&
		(strcmp(st->SORTIMENT,stAlt->SORTIMENT) == 0) && 
		(strcmp(st->VERK_ART,stAlt->VERK_ART) == 0))
		return 0;

	lRetCode = store_Zpznpflege(errmld,  st );

	if ((0 == lRetCode) || (100 == lRetCode)) {
		sprintf(buf,"update zartverk set manuell='%s',prioritaet=%ld,sortiment='%s',verk_art='%s' where artikel_nr_bas=%ld and artikel_nr_verk=%ld",
		st->MANUELL,st->PRIORITAET,st->SORTIMENT,st->VERK_ART,st->ARTIKEL_NR_BAS,st->ARTIKEL_NR_VERK);
		lRetCode = 0;
		lUpdates++;
		if (WITHUPDATES == sModus)		
			lRetCode= SqlExecuteImm( buf );
		if ( 0 != lRetCode )    {
			strcpy( errmld, DynErrmld() );
			}
	}
	return lRetCode;
}


/* --------------------------------------------------------------------------------------------- */
/* Satz in zpznpflege schreiben
/* --------------------------------------------------------------------------------------------- */
long store_Zpznpflege(char *errmld, const struct ZARTVERK * const stZartVerk )
{
	long s,lPzn;
	char sql[100];
	struct ZPZNPFLEGE stPznflege;

	stPznflege.ARTIKEL_NR = stZartVerk->ARTIKEL_NR_BAS;
	strcpy(stPznflege.DEZAP_SA,"08");
    stPznflege.DATUM = GetDate();


   sprintf( sql, "select ARTIKEL_NR from zpznpflege where ARTIKEL_NR=%ld and DATUM=%ld and DEZAP_SA='%s'",stPznflege.ARTIKEL_NR,stPznflege.DATUM,stPznflege.DEZAP_SA);
   s = SqlRead( sql, &lPzn, NULL );
   if (( s != 0 ) && ( s != 100 ))
     sprintf( errmld, "select zpznpflege: %s", DynErrmld() );

   if ( 100 == s) {
		sprintf( sql, "insert into zpznpflege (%s) values (%ld,%ld,'%s')",PROJECTION_ZPZNPFLEGE,stPznflege.ARTIKEL_NR,stPznflege.DATUM,stPznflege.DEZAP_SA);
		s = 0;
		if (WITHUPDATES == sModus)
			s = SqlExecuteImm( sql );
		if (( s != 0 ) && ( s != 100 ))
			sprintf( errmld, "insert zpznpflege: %s", DynErrmld() );
   }

   return s;
}


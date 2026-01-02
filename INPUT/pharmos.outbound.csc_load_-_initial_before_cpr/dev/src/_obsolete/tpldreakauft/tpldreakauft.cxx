/******************************************************************************/
/*     Hauptmodul: tpldreakauft.cpp                                           */
/*         Source: tpldreakauft.cpp                                           */
/*          Autor: R. Imschweiler                                             */
/*       Erstellt: 15.11.2005                                                 */
/*        Sprache: C                                                          */
/*        Erzeugt: manuell                                                    */
/*        Aufgabe: loeschen der Kundenauftragrelationen bei Tagesabschluss    */
/*         Aufruf: tpldreakauft                                               */
/*                                                                            */
/******************************************************************************/

/*** VERSION ******************************************************************/

static char *SCCSID = "@(#)PRZ GmbH Stand: 1.0.6 $Header: /prj/df/unix/tpldreakauft/tpldreakauft.cxx 145   30.08.05 14:49 66aeimsc $";

/*** INCLUDE ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "dispoartikel.h"
#include "kdauftrag.h"
#include "kdauftragzusatz.h"
#include "kdauftragpos.h"
#include "kdauftragposrab.h"
#include "kdauftragbem.h"
#include "kdauftragereignis.h"
#include <pplib/allg.h>

/*** DEFINE *******************************************************************/

#include "libtpld/define.h"
#define MAX_TRANSAKTION     300
typedef struct timeval timeval_t; 
#define DATABASE "phosix"

/*** MACROS *******************************************************************/

#define ERROR_MSG( x )      if ( SQLCODE < 0 ) { PrintMsg( fun, x, FEHLER ); \
				 return ERROR; }
#define ERROR_MLD( x )      if ( SQLCODE < 0 ) { PrintMsg( fun, x, FEHLER ); }
#define NOT_FOUND           SQLCODE == SQLNOTFOUND

/*** GLOBALE ******************************************************************/

int debug_enabled = NO;
int HausNr = 0;
exec sql begin declare section;
	long lDatumEreignis;
	long lDatumAktuell;
	long lZeitEreignis;
	long lDatumError = 0;
exec sql end declare section;

/*** STRUCTUR *****************************************************************/

struct ZAEHLER {
	int Reaktiviert;
 }; 

typedef struct NUMMER {
	short HerkunftFiliale; 
	short FilialNr; 
	int   KdNr;
	int   Datum;
} Nummer;

/*** DECLARATION **************************************************************/

int main( int, char ** );
static int  OpenDB( char* );
static int  PrepareAll( void );
static int  Commit( char * );
static void PrintMsg( char *, char *, char );

/*** Verzögerte Auslieferung **************************************************/

static int  PrepareIncreaseNummer( );
static int  PrepareReaktiviereAuftrag( );
static int  PrepareReaktiviereKdauftrag( );
static int  PrepareReaktiviereKdauftragPos( );
static int  PrepareReaktiviereKdauftragPosRab( );
static int  PrepareReaktiviereKdauftragBem( );
static int  PrepareReaktiviereKdauftragEreignis( );
static int  PrepareReaktiviereKdispoArtikel( ); 
static int  ReaktiviereAuftrag( struct ZAEHLER *z );
static int  IncreaseNummer( long *KdauftragNr );
static int  ReaktiviereKdauftrag( kdauftragS *d );
static int  ReaktiviereKdauftragPos( long lDatum, long KdauftragNr, long KdauftragNrNeu );
static int  ReaktiviereKdauftragPosRab( long lDatum, long KdauftragNr, long KdauftragNrNeu );
static int  ReaktiviereKdauftragBem( long lDatum, long KdauftragNr, long KdauftragNrNeu );
static int  ReaktiviereKdauftragEreignis( kdauftragS *d );
static int  ReaktiviereKdispoArtikel( long lDatum, long KdauftragNr, long KdauftragNrNeu ); 

/*** MAIN *********************************************************************/

int main( int argc, char **argv )
{
	struct ZAEHLER z = { 0 };	        /* initialize */
	Nummer num;
	char error_msg[512];
	int skip;
	int i;
	int rc;
	char *schalter;
	char *spDatabase = NULL;
	int iFilialNr = 0;
	char *fun = "Main";
 
	skip = NO;
	for ( i = 1; i < argc; i++ )
	{
		if ( skip )
		{
			skip = NO;
			continue;
		}
		schalter = argv[i];
		if ( !strcmp( schalter, "-dg" ) )
			debug_enabled = YES;
		else if ( !strcmp( schalter, "-db" ) )
		{   
			spDatabase = argv[i+1];
			skip = YES;
		}
		else if ( !strcmp( schalter, "-errdate" ) )
		{   
			lDatumError = atol(argv[i+1]);
			skip = YES;
		}
		else
		{
			skip = ERROR;
			break;
		}
	}                                            
   
	if ( argc == 1 || skip == ERROR )
	{
		printf( "  usage: %s\n\t"
				" { -dg /*Debugging*/ }\n\t"
				" [ -db <Datenbankname> ]\n\t",
				argv[0] );
		return 2;
	}

	sprintf( error_msg, "gestartet fuer DB: %s", spDatabase );
	PrintMsg( fun, error_msg, HINWEIS );
	if( (rc = OpenDB(spDatabase)) != 0 ) return rc;
  
	if( (rc = ReaktiviereAuftrag( &z )) != OK )
	{
		sprintf( error_msg, "mit Fehler beendet" );
		PrintMsg( fun, error_msg, FEHLER );
		return rc;
	}
	sprintf( error_msg, "Aufträge reaktiviert: %d", z.Reaktiviert );
	PrintMsg( fun, error_msg, HINWEIS );
	PrintMsg( fun, "beendet", HINWEIS );
  
	return OK;
}
   
/***** PREPARE-ALL **********************************************************/

static int PrepareAll()
{
	int rc;
	if ((rc = PrepareReaktiviereAuftrag( )) != OK) return rc;
	if ((rc = PrepareIncreaseNummer( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftrag( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftragPos( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftragPosRab( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftragBem( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftragEreignis( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdispoArtikel( )) != OK) return rc;
	return OK;
}

/***** OEFFNEN DB **********************************************************/

int OpenDB( char* spDB )
{
	exec sql begin declare section;
	char* spDatabase = spDB;
	exec sql end declare section;
  
	char *fun = "OpenDB";
  
	if ( spDB == NULL )
	{ 
		exec sql database DATABASE;
	}
	else
	{
		exec sql database :spDatabase;
	}
	ERROR_MSG( "Fehler oeffnen DB" )

	exec sql set lock mode to wait 20;
	ERROR_MSG( "Set LockMode to Wait" )

	exec sql set isolation to dirty read;
	ERROR_MSG( "Set Isolation to Dirty Read" )
 
	return SQLCODE;
}

/***** PRINT-MSG ************************************************************/

void PrintMsg( char *fun, char *error_msg, char mld )
{
	static int fst = 1;
	FILE *fp;
	struct tm *localtime();
	struct tm *zeit;
	long hour1;
	pid_t pid;
	long time();
	char logFile[L_TEXT];

	pid = getpid();
	hour1 = time( &hour1 );
	zeit  = localtime( &hour1 );

	if (fst)
	{
		fst = 0;
		lDatumAktuell = lDatumEreignis = zeit->tm_mday + (zeit->tm_mon + 1)*100 + (zeit->tm_year+1900)*10000;
		lZeitEreignis = zeit->tm_hour*10000000 + zeit->tm_min*100000 + zeit->tm_sec*1000;
		if(zeit->tm_hour > 14) lDatumEreignis = AllgAddDate(lDatumEreignis,1,error_msg);
	}

	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) );
	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
		return;

	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d "
				"pid=%05ld %s %s %s->%d/%d\n",
				mld,
				HausNr,
				zeit->tm_mday,
				zeit->tm_mon + 1,
				(zeit->tm_year+1900)%100,
				zeit->tm_hour,
				zeit->tm_min,
				zeit->tm_sec,
				pid,
				"tpldreakauft",
				fun,
				error_msg,
				SQLCODE,
				SQLISAM );

	fclose(fp);
}

/***** COMMIT ***************************************************************/

static int Commit( char *fun )
{
	exec sql commit work;
	exec sql begin work;
	ERROR_MSG( "begin work" );
	return OK;
}

/***** REAKTIVIERE-AKDAUFTRAG ****************************************************/

static int ReaktiviereAuftrag( struct ZAEHLER *z )
{
	exec sql begin declare section;
	long datum;
	long KdauftragNrAlt;
	long KdauftragNrNeu;
	kdauftragS d;
	exec sql end declare section;

	int rc;
	int i = 0;
	char *fun = "ReaktiviereAuftrag";

	if( (rc = PrepareAll()) != 0 ) return rc;

	if ( lDatumError == 0)
	{
		exec sql open CDDakdauftrag;
	}
	else
	{
		exec sql open CDDakdauftrag using :lDatumError;
	}
	ERROR_MSG( "open CDDakdauftrag" )

	exec sql begin work;
	for( ;; )
	{
		i++;
		if ( i % 5 == 0 )
		Commit( fun );

		exec sql fetch CDDakdauftrag into :datum,:d;
		ERROR_MSG( "fetch CDDakdauftrag" )
		if ( NOT_FOUND )
			break;

		if(d.DATUMORG == 0) d.DATUMORG = datum;
		if(d.KDAUFTRAGNRORG == 0) d.KDAUFTRAGNRORG = d.KDAUFTRAGNR;
		KdauftragNrAlt = d.KDAUFTRAGNR;

		if ((rc = IncreaseNummer( &KdauftragNrNeu )) != OK) return rc;
		d.KDAUFTRAGNR = KdauftragNrNeu;

		if ((rc = ReaktiviereKdauftrag( &d )) != OK) return rc;
		if ((rc = ReaktiviereKdauftragPos( datum, KdauftragNrAlt, KdauftragNrNeu )) != OK) return rc;
		if ((rc = ReaktiviereKdauftragPosRab( datum, KdauftragNrAlt, KdauftragNrNeu )) != OK) return rc;
		if ((rc = ReaktiviereKdauftragBem( datum, KdauftragNrAlt, KdauftragNrNeu )) != OK) return rc;
		if ((rc = ReaktiviereKdauftragEreignis( &d )) != OK) return rc;
		if ((rc = ReaktiviereKdispoArtikel( datum, KdauftragNrAlt, KdauftragNrNeu )) != OK) return rc;

		exec sql execute UDDakdauftrag using :d.KDAUFTRAGNRORG, :d.DATUMORG;
		ERROR_MSG( "execute UDDakdauftrag" );
		z->Reaktiviert++;
	}
	exec sql commit work;

	return OK;
}

/***** REAKTIVIERE-KDAUFTRAG ****************************************************/

static int ReaktiviereKdauftrag( kdauftragS *d )
{
	exec sql begin declare section;
	kdauftragS *a;
	exec sql end declare section;

	int i = 0;
	char *fun = "ReaktiviereKdauftrag";

	a = d;
	exec sql execute IDDkdauftrag using KDAUFTRAG_ZEIGER(a);
	ERROR_MSG( "execute IDDkdauftrag" );

	return OK;
}

/***** INCREASE-NUMMER **********************************************/

static int IncreaseNummer( long *KdauftragNr )
{
	exec sql begin declare section;
	char str[2048];
	long aufnr;
	long wert;
	exec sql end declare section;

	char *fun = "PrepareIncreaseNummer";

	exec sql open CSelNummer;
	ERROR_MSG( "open CSelNummer" )
	exec sql fetch CSelNummer into :aufnr,:wert;
	ERROR_MSG( "fetch CSelNummer" )
	aufnr += wert;
	exec sql execute UpdNummer using :aufnr;
	ERROR_MSG( "execute UpdNummer" );
	*KdauftragNr = aufnr;
  
	return OK;
}

/***** REAKTIVIERE-KDAUFTRAGPOS ****************************************************/

static int ReaktiviereKdauftragPos( long lDatum, long KdauftragNr, long KdauftragNrNeu )
{
	exec sql begin declare section;
	kdauftragposS a;
	kdauftragposS *b;
	long datum;
	long aufnr;
	exec sql end declare section;

	b = &a;
	int i = 0;
	char *fun = "ReaktiviereKdauftragPos";

	datum = lDatum;
	aufnr = KdauftragNr;

	exec sql open CDDakdauftragpos using :datum, :aufnr;
	ERROR_MSG( "open CDDakdauftragpos" )
	for(;;)
	{
		exec sql fetch CDDakdauftragpos into :a;
		ERROR_MSG( "fetch CDDakdauftragpos" )
		if ( NOT_FOUND )
			break;
		a.KDAUFTRAGNR = KdauftragNrNeu;

#undef HINWEIS 
		exec sql execute IDDkdauftragpos using KDAUFTRAGPOS_ZEIGER(b);
		ERROR_MSG( "execute IDDkdauftragpos" );
	}

	return OK;
}

/***** REAKTIVIERE-KDAUFTRAGPOSRAB ****************************************************/

static int ReaktiviereKdauftragPosRab( long lDatum, long KdauftragNr, long KdauftragNrNeu )
{
	exec sql begin declare section;
	kdauftragposrabS a;
	kdauftragposrabS *b;
	long datum;
	long aufnr;
	exec sql end declare section;

	b = &a;
	int i = 0;
	char *fun = "ReaktiviereKdauftragPosRab";

	datum = lDatum;
	aufnr = KdauftragNr;

	exec sql open CDDakdauftragposrab using :datum, :aufnr;
	ERROR_MSG( "open CDDakdauftragposrab" )
	for(;;)
	{
		exec sql fetch CDDakdauftragposrab into :a;
		ERROR_MSG( "fetch CDDakdauftragposrab" )
		if ( NOT_FOUND )
			break;
		a.KDAUFTRAGNR = KdauftragNrNeu;

#undef HINWEIS 
		exec sql execute IDDkdauftragposrab using KDAUFTRAGPOSRAB_ZEIGER(b);
		ERROR_MSG( "execute IDDkdauftragposrab" );
	}

	return OK;
}

/***** REAKTIVIERE-KDAUFTRAGBEM ****************************************************/

static int ReaktiviereKdauftragBem( long lDatum, long KdauftragNr, long KdauftragNrNeu )
{
	exec sql begin declare section;
	kdauftragbemS a, *b;
	long datum;
	long aufnr;
	exec sql end declare section;

	int i = 0;
	char *fun = "ReaktiviereKdauftragBem";

	b = &a;
	datum = lDatum;
	aufnr = KdauftragNr;

	exec sql open CDDakdauftragbem using :datum, :aufnr;
	ERROR_MSG( "open CDDakdauftragbem" )
	for(;;)
	{
		exec sql fetch CDDakdauftragbem into :a;
		ERROR_MSG( "fetch CDDakdauftragbem" )
		if ( NOT_FOUND )
			break;
		a.KDAUFTRAGNR = KdauftragNrNeu;

		exec sql execute IDDkdauftragbem using KDAUFTRAGBEM_ZEIGER(b);
		ERROR_MSG( "execute IDDkdauftragbem" );
	}

	return OK;
}

/***** REAKTIVIERE-DISPOARTIKEL ****************************************************/

static int ReaktiviereKdispoArtikel( long lDatum, long KdauftragNr, long KdauftragNrNeu )
{
	exec sql begin declare section;
	dispoartikelS a;
	dispoartikelS *b;
	long datum;
	long aufnr;
	exec sql end declare section;

	int i = 0;
	char *fun = "ReaktiviereKdispoArtikel";

	b = &a;
	datum = lDatum;
	aufnr = KdauftragNr;

	exec sql open CDDadispoartikel using :datum, :aufnr;
	ERROR_MSG( "open CDDadispoartikel" )
	for(;;)
	{
		exec sql fetch CDDadispoartikel into :a;
		ERROR_MSG( "fetch CDDadispoartikel" )
		if ( NOT_FOUND )
			break;
		a.KDAUFTRAGNR = KdauftragNrNeu;

		exec sql execute IDDdispoartikel using DISPOARTIKEL_ZEIGER(b);
		ERROR_MSG( "execute IDDdispoartikel" );
	}

	return OK;
}

/***** REAKTIVIERE-KDAUFTRAGEREIGNIS ****************************************************/

static int ReaktiviereKdauftragEreignis( kdauftragS *d )
{
	exec sql begin declare section;
	kdauftragS *b;
	exec sql end declare section;

	int i = 0;
	char *fun = "ReaktiviereKdauftragEreignis";

	b = d;
	exec sql execute IDDkdauftragereig using
		:b->KDAUFTRAGNR,
		:lDatumEreignis,
		:lZeitEreignis,
		'12',
		'0',
		'0000',
		:b->FILIALNR;
	ERROR_MSG( "execute IDDkdauftragereig" );

	return OK;
}
   
/***** PREPARE-REAKTIVIERE-AUFTRAG **********************************************/

static int PrepareReaktiviereAuftrag( )
{
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	char *fun = "PrepareReaktiviereAuftrag";

	strcpy( str, "select " );
	strcat( str, " datum," );
	strcat( str, KDAUFTRAG_PELISTE );
	strcat( str, " from akdauftrag" );
	if (lDatumError == 0)
	{
		strcat( str, " where datumauslieferung > '0'" );
		strcat( str, " and kdauftragstat[5] != '1'" );	/* Erfasst */
		strcat( str, " and kdauftragstat[10] != '1'" );	/* Storniert */
		strcat( str, " and kzrestored != '1'" );
	}
	else
	{
		strcat( str, " where datumauslieferung = ?" );
	}
	strcat( str, " for update " );

	exec sql prepare SDDakdauftrag from :str;
	ERROR_MSG( "prepare SDDakdauftrag" );
	exec sql declare CDDakdauftrag cursor with hold for SDDakdauftrag;
	exec sql free SDDakdauftrag;

	strcpy( str, "update akdauftrag" );
	strcat( str, " set kzrestored = '1'" );
	strcat( str, ",kdauftragnrorg = ?" );
	strcat( str, ",datumorg = ?" );
	strcat( str, " where current of CDDakdauftrag" );
	exec sql prepare UDDakdauftrag from :str;
	ERROR_MSG( "prepare UDDakdauftrag" );

	return OK;
}
   
/***** PREPARE-INCREASE-NUMMER **********************************************/

static int PrepareIncreaseNummer( )
{
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	char *fun = "PrepareIncreaseNummer";

	strcpy( str, "select nummerwert,nummerinkrement " );
	strcat( str, "from nummer " );
	strcat( str, "where " );
	strcat( str, "nummertyp = '1' " );
	strcat( str, "for update" );
	exec sql prepare SelNummer from :str;
	ERROR_MSG( "prepare SelNummer" );
	exec sql declare CSelNummer cursor with hold for SelNummer;
	exec sql free SelNummer;

	strcpy( str, "update nummer " );
	strcat( str, "set nummerwert = ? " );
	strcat( str, "where current of CSelNummer" );
	exec sql prepare UpdNummer from :str;
	ERROR_MSG( "prepare UpdNummer" );
  
	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAG *********************************************/

static int PrepareReaktiviereKdauftrag( )
{
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	char *fun = "PrepareReaktiviereKdauftrag";

	strcpy( str, "insert into kdauftrag (" );
	strcat( str, KDAUFTRAG_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftrag from :str;
	ERROR_MSG( "prepare IDDkdauftrag" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAGPOS *********************************************/

static int PrepareReaktiviereKdauftragPos( )
{
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	char *fun = "PrepareReaktiviereKdauftragPos";
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOS_PELISTE );
	strcat( str, " from akdauftragpos" );
	strcat( str, " where datum = ?" );
	strcat( str, " and kdauftragnr = ?" );

	exec sql prepare SDDakdauftragpos from :str;
	ERROR_MSG( "prepare SDDakdauftragpos" );
	exec sql declare CDDakdauftragpos cursor with hold for SDDakdauftragpos;
	exec sql free SDDakdauftragpos;

	strcpy( str, "insert into kdauftragpos (" );
	strcat( str, KDAUFTRAGPOS_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftragpos from :str;
	ERROR_MSG( "prepare IDDkdauftragpos" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAGPOSRAB *********************************************/

static int PrepareReaktiviereKdauftragPosRab( )
{
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	char *fun = "PrepareReaktiviereKdauftragPosRab";
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSRAB_PELISTE );
	strcat( str, " from akdauftragposrab" );
	strcat( str, " where datum = ?" );
	strcat( str, " and kdauftragnr = ?" );

	exec sql prepare SDDakdauftragposrab from :str;
	ERROR_MSG( "prepare SDDakdauftragposrab" );
	exec sql declare CDDakdauftragposrab cursor with hold for SDDakdauftragposrab;
	exec sql free SDDakdauftragposrab;

	strcpy( str, "insert into kdauftragposrab (" );
	strcat( str, KDAUFTRAGPOSRAB_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftragposrab from :str;
	ERROR_MSG( "prepare IDDkdauftragposrab" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAGBEM *********************************************/

static int PrepareReaktiviereKdauftragBem( )
{
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	char *fun = "PrepareReaktiviereKdauftragBem";

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGBEM_PELISTE );
	strcat( str, " from akdauftragbem" );
	strcat( str, " where datum = ?" );
	strcat( str, " and kdauftragnr = ?" );

	exec sql prepare SDDakdauftragbem from :str;
	ERROR_MSG( "prepare SDDakdauftragbem" );
	exec sql declare CDDakdauftragbem cursor with hold for SDDakdauftragbem;
	exec sql free SDDakdauftragbem;

	strcpy( str, "insert into kdauftragbem (" );
	strcat( str, KDAUFTRAGBEM_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftragbem from :str;
	ERROR_MSG( "prepare IDDkdauftragbem" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-DISPOARTIKEL *********************************************/

static int PrepareReaktiviereKdispoArtikel( )
{
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	char *fun = "PrepareReaktiviereKdispoArtikel";

	strcpy( str, "select " );
	strcat( str, DISPOARTIKEL_PELISTE );
	strcat( str, " from adispoartikel" );
	strcat( str, " where datum = ?" );
	strcat( str, " and kdauftragnr = ?" );

	exec sql prepare SDDadispoartikel from :str;
	ERROR_MSG( "prepare SDDadispoartikel" );
	exec sql declare CDDadispoartikel cursor with hold for SDDadispoartikel;
	exec sql free SDDadispoartikel;

	strcpy( str, "insert into dispoartikel (" );
	strcat( str, DISPOARTIKEL_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "? " );
	strcat( str, ")" );

	exec sql prepare IDDdispoartikel from :str;
	ERROR_MSG( "prepare IDDdispoartikel" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAGEREIGNIS *********************************************/

static int PrepareReaktiviereKdauftragEreignis( )
{
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	char *fun = "PrepareReaktiviereKdauftragEreignis";

	strcpy( str, "insert into kdauftragereignis (" );
	strcat( str, KDAUFTRAGEREIGNIS_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,?,?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftragereig from :str;
	ERROR_MSG( "prepare IDDkdauftragereig" );

	return OK;
}

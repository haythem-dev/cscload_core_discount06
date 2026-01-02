/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/
#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadartcom"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

//static char *SCCSID="@(#)PRZ GmbH Stand: 1.0.2 $Header: /prj/df/unix/loadartcom/loadartcom.cxx 50    29.04.04 16:01 66aeimsc $";

/*****************************************************************************/
/* Einfuegen neuer Tabellen in das Artikelladeprogramm                       */
/*****************************************************************************/
/* 1 Tabelle im Incudefile definieren und ANZ_TABELLEN aktualisieren         */
/* 2 Eintrag in Funktion SetzeSchalterTabelle erzeugen                       */
/* 3 Implementierung und Aufruf der Initialisierungsfunktion (create table..)*/
/* 4 Implementierung und Aufruf der Ladefunktionfunktion (in Bezug auf DKART)*/
/* 5 Implementierung und Aufruf der Endefunktion (drop/create index, rename )*/
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "artcompack.h"
#include "cpvalidityperiod.h"
#include "pplib/allg.h"
#include <dirent.h>
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define NOTFOUND           sqlca.sqlcode == SQLNOTFOUND

#define OK                   0
#define NO                   0
#define YES                  1
#define ERROR               -1
#define INSERT               1
#define NOT_FOUND            1
#define FILE_NOT_FOUND       1
#define WARNING             -2
#define HINW               'H'
#define FEHL               'F'
#define RIO_EOF            110
#define RIO_NOFIND         111
#define INDATABASE         "phosix@db2_rmfuze1_tcp"
#define OUTDATABASE        "phosix"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 300                  /* nach n-saetzen commit  */


char log_file [300 + 1];
char dateiname[L_TEXT];
int zaehlerIns = 0;     /* weil ich zu faul war alex */

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
struct N_ARTCOMPACK a;
struct N_CPVALIDITYPERIOD per;
long datum;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo( char *error_msg, char mld, int rc );
int StarteLadenArtCom		( char *error_msg);
int PrepareLoadTables		( char *error_msg);
int DelArtCom				( char *error_msg);
int DelArtComPeriod			( char *error_msg);
int AfterLoadTables			( char *error_msg);
int PrepareLeseArtCom		( char *error_msg);
int PrepareLeseArtComPeriod	( char *error_msg);
int PrepareLadeArtCom		( char *error_msg);
int PrepareLadeArtComPeriod	( char *error_msg);
int LeseArtCom				( char *error_msg);
int LadeArtCom				( char *error_msg);
int LadeArtComPeriod		( char *error_msg);
int AfterLadeArtCom			( char *error_msg);
int CloseDatabase			( void );

/***** MAIN *****************************************************************/

int main( int argc, char **argv  )
{
	char  error_msg[181];
	char  *schalter;
	int   i;
	char  *fun = "Main";
	char  *LOG_FILE = "wws.log";
	char  *LOG_PATH;
	char  logpath[256 + 1];
	int   rc;
	int   status = 0;
	char  start_msg[81];

	sprintf(indatenbank,"%s",INDATABASE);
	sprintf(outdatenbank,"%s",OUTDATABASE);
     
	strcpy(start_msg, "gestartet mit:");
	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-dbin" ) )
		{
			strcat(start_msg, " -dbin");
			i++;
			sprintf( indatenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-dbout" ) )
		{
			strcat(start_msg, " -dbout");
			i++;
			sprintf( outdatenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;   
		}
		else
		{
			printf( "  usage: %s\n\t"
				" { -dbin datenbankname <Datenbankname Eingabe> }\n\t"
				" { -dbout datenbankname <Datenbankname Ausgabe> }\n\t"
				,argv[0] );
			return 1;
		}
	}

	datum = AllgGetDate();

	exec sql database :outdatenbank;
	ERROR_MSG( "Fehler oeffnen DB" )

	exec sql set lock mode to wait 20;
	ERROR_MSG( "Set LockMode to Wait" )

	exec sql set isolation to dirty read;
	ERROR_MSG( "Set Isolation to Dirty Read" )

	PrintMsg( fun, start_msg, HINW, 0 );
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	if ( ( rc = StarteLadenArtCom( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
/***** STARTE DAS LADEN DER STELLER-ARTIKEL ************************************/

int StarteLadenArtCom( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenArtCom";
   
	exec sql open Cselcartcomper using :datum,:datum;
	ERROR_MSG( "open Cselcartcomper" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch Cselcartcomper into :per;
		ERROR_MSG( "fetch Cselcartcomper" )
		if(NOTFOUND) break;

		if ( ( rc = LadeArtComPeriod( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}

		exec sql open Cselcartcom using :per.ARTICLE_NO_PACK;
		ERROR_MSG( "open Cselcartcom" )

		for ( ;; )
		{
			exec sql fetch Cselcartcom into :a;
			if(NOTFOUND) break;
	        if ( ( rc = LadeArtCom( error_msg ) ) < 0 )
			{
				PrintMsg( fun, error_msg, FEHL, ERROR );
				return ERROR;
			}
		}
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	sprintf( error_msg, "%d Saetze geladen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );

	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;
	if ( ( rc = DelArtCom( error_msg ) ) < 0 ) return rc;
	if ( ( rc = DelArtComPeriod( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLeseArtCom( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLeseArtComPeriod( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeArtComPeriod( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeArtCom( error_msg ) ) < 0 ) return rc;

	return OK;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeArtCom(error_msg)) < 0) return rc;

	return OK;
}

/*** DEL-ArtCom ************************************************/

int DelArtCom( char *error_msg )
{
	char *fun = "DelArtCom";
	int i;

	exec sql begin declare section;
	char str[2048];
	long lArticleNo;
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "article_no_pack  " );
	strcat( str, "from " );
	strcat( str, "artcompack " );
	strcat( str, "for update " );

	exec sql prepare del_artcom from :str;
	ERROR_MSG( "prepare del_artcom" )
	exec sql declare Cdelartcom cursor with hold for del_artcom;

	strcpy( str, "delete from artcompack " );
	strcat( str, "where current of Cdelartcom " );
	
	exec sql prepare delete_artcom from :str;
	ERROR_MSG( "prepare delete_artcom" )

	exec sql open Cdelartcom;
    ERROR_MSG( "open Cdelartcom" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(i=1;;i++)
	{
		if (i % M_DURCHLAUF_COMMIT == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch Cdelartcom into :lArticleNo;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Cdelartcom" )

		exec sql execute delete_artcom;
		ERROR_MSG( "execute delete_artcom" )

	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close Cdelartcom;
    ERROR_MSG( "close Cdelartcom" )

	return OK;      
}

/*** DEL-ArtCom-Period ************************************************/

int DelArtComPeriod( char *error_msg )
{
	char *fun = "DelArtComPeriod";
	int i;

	exec sql begin declare section;
	char str[2048];
	long lArticleNo;
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "article_no_pack  " );
	strcat( str, "from " );
	strcat( str, "cpvalidityperiod " );
	strcat( str, "for update " );

	exec sql prepare del_artcomper from :str;
	ERROR_MSG( "prepare del_artcomper" )
	exec sql declare Cdelartcomper cursor with hold for del_artcomper;

	strcpy( str, "delete from cpvalidityperiod " );
	strcat( str, "where current of Cdelartcomper " );
	
	exec sql prepare delete_artcomper from :str;
	ERROR_MSG( "prepare delete_artcomper" )

	exec sql open Cdelartcomper;
    ERROR_MSG( "open Cdelartcomper" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(i=1;;i++)
	{
		if (i % M_DURCHLAUF_COMMIT == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch Cdelartcomper into :lArticleNo;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Cdelartcomper" )

		exec sql execute delete_artcomper;
		ERROR_MSG( "execute delete_artcomper" )

	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close Cdelartcomper;
    ERROR_MSG( "close Cdelartcomper" )

	return OK;      
}

/*** PREPARE-LESE-STELLER ************************************************/

int PrepareLeseArtCom( char *error_msg )
{
	char *fun = "PrepareLeseArtCom";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, ARTCOMPACK_PELISTE );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":cartcompack " );
	strcat( str, "where " );
	strcat( str, "article_no_pack = ? " );

	exec sql prepare dec_cartcom from :str;
	ERROR_MSG( "prepare dec_cartcom" )
	exec sql declare Cselcartcom cursor with hold for dec_cartcom;
	
	return OK;      
}

/*** PREPARE-LESE-STELLER-PERIOD ************************************************/

int PrepareLeseArtComPeriod( char *error_msg )
{
	char *fun = "PrepareLeseArtComPeriod";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, CPVALIDITYPERIOD_PELISTE );
	strcat( str, " from " );
	strcat( str, indatenbank );
	strcat( str, ":ccpvalidityperiod " );
	strcat( str, "where " );
	strcat( str, "datefrom <= ? " );
	strcat( str, "and " );
	strcat( str, "(dateto >= ? " );
	strcat( str, "or dateto = 0) " );

	exec sql prepare dec_cartcomper from :str;
	ERROR_MSG( "prepare dec_cartcomper" )
	exec sql declare Cselcartcomper cursor with hold for dec_cartcomper;
	
	return OK;      
}

/*** PREPARE-LADE-STELLER ************************************************/

int PrepareLadeArtCom( char *error_msg )
{
	char *fun = "PrepareLadeArtCom";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into artcompack (" );
	strcat( str, ARTCOMPACK_PELISTE );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ? )" );
	   
	exec sql prepare ins_artcom from :str;
	ERROR_MSG( "prepare ins_artcom" )

	return OK;      
}

/*** PREPARE-LADE-STELLER-PERIOD ************************************************/

int PrepareLadeArtComPeriod( char *error_msg )
{
	char *fun = "PrepareLadeArtComPeriod";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into cpvalidityperiod (" );
	strcat( str, CPVALIDITYPERIOD_PELISTE );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ? )" );
	   
	exec sql prepare ins_artcomper from :str;
	ERROR_MSG( "prepare ins_artcomper" )

	return OK;      
}

/*** LADE-STELLER_PERIOD ********************************************************/

int LadeArtComPeriod( char *error_msg )
{
	char *fun = "LadeArtComPeriod";
	exec sql begin declare section;
	struct N_CPVALIDITYPERIOD *pper;
	exec sql end declare section;

	pper = &per;

	if(pper->DATETO == 0) pper->DATETO = 20991231;

	EXEC SQL EXECUTE ins_artcomper
		using
		CPVALIDITYPERIOD_ZEIGER(pper);
	ERROR_MSG( "execute ins_artcomper" )

	return OK;
}

/*** LADE-STELLER ********************************************************/

int LadeArtCom( char *error_msg )
{
	char *fun = "LadeArtCom";
	exec sql begin declare section;
	struct N_ARTCOMPACK *d;
	exec sql end declare section;

	d = &a;

	EXEC SQL EXECUTE ins_artcom
		using
		ARTCOMPACK_ZEIGER(d);
	ERROR_MSG( "execute ins_artcom" )

	return OK;
}

/***** AFTER-LADE-STELLER *********************************************/

int AfterLadeArtCom( char *error_msg )
{
	return OK;
}

/***** PRINT-MSG ************************************************************/

void PrintMsg( char *fun, char *error_msg, char mld, int rc )
{
	FILE *fp;
	struct tm *localtime();
	struct tm *zeit;
	long hour1;
	pid_t pid;
	long time();
	char logFile[L_TEXT];
    char *env;
 
	if ( rc > INSERT )
		return;
   
	pid = getpid();
	hour1 = time( &hour1 );
	zeit  = localtime( &hour1 );
   
/*	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) );	*/
	env = getenv( "LOG_PATH" );
	if ( env == NULL )
		env = ".";
	sprintf( logFile, "%s/wws.log", env );

	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
		return;
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s %s\n",
		mld,
		99,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"loadartcom",
		fun,
		error_msg );

	fclose(fp);
}

/***** CLOSE-DATABASE *******************************************************/

int CloseDatabase( void )
{
	char error_msg[L_TEXT];
	char *fun = "CloseDatabase";

	exec sql close database;
	ERROR_MSG( "Close DB" )
  
	return OK;
}
/***** ENDE *****************************************************************/

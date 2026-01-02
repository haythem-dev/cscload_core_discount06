/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadpharmgrp"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

//static char *SCCSID="@(#)PRZ GmbH Stand: 1.0.1 $Header: /prj/df/unix/loadpharmgrp/loadpharmgrp.cxx 50    29.04.04 16:01 66aeimsc $";

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "pharmgrp.h"
#include "pplib/allg.h"
#include <string.h>
#include <unistd.h>

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1],\
										sqlca.sqlerrm); \
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
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */

char log_file [300 + 1];
char dateiname[L_TEXT];
int explain = NO;
int sichern = NO;
int zaehlerIns = 0;     /* weil ich zu faul war alex */
int zaehlerUpd = 0;     /* weil ich zu faul war alex */

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
pharmgrpS source;
pharmgrpS *psource;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main						( int, char ** );
void PrintMsg					( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo				( char *error_msg, char mld, int rc );
int StarteLadenPharm			( char *error_msg);
int PrepareLoadTables			( char *error_msg);
int LoadTables					( char *error_msg);
int AfterLoadTables				( char *error_msg);
int PrepareLadePharm			( char *error_msg);
int PrepareLesePharm			( char *error_msg);
int LesePharm					( char *error_msg);
int LadePharm					( char *error_msg);
int AfterLadePharm				( char *error_msg);
int CloseDatabase				( void );

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
		else if ( !strcmp( schalter, "-ex" ) )
		{
			strcat(start_msg, " -ex");
			explain = YES;
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
				" [ -ex <Explain> ]\n\t",
				argv[0] );
			return 1;
		}
	}

	exec sql database :outdatenbank;
	ERROR_MSG( "Fehler oeffnen DB" )

	exec sql set lock mode to wait 20;
	ERROR_MSG( "Set LockMode to Wait" )

	exec sql set isolation to dirty read;
	ERROR_MSG( "Set Isolation to Dirty Read" )

	if (explain == YES)
	{
		exec sql set explain on;
		ERROR_MSG( "Set Explain On" )
	}

	PrintMsg( fun, start_msg, HINW, 0 );
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	if ( ( rc = StarteLadenPharm( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER PHARMACY-GROUPS ************************************/

int StarteLadenPharm( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenPharm";

	psource = &source;
   
	exec sql open Cselpharm;
	ERROR_MSG( "open Cselpharm" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch Cselpharm into PHARMGRP_ZEIGER(psource);
		ERROR_MSG( "fetch Cselpharm" )
		if(NOTFOUND) break;
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }

        if ( ( rc = LoadTables( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
        else if ( explain == YES )
           if ( zaehler > 5000 ) break;   /* Nur 5000 Saetze verarbeiten */

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	sprintf( error_msg, "%d Saetze gelesen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );
	sprintf( error_msg, " Saetze geaendert/eingefuegt: %d/%d", zaehlerUpd, zaehlerIns );
	PrintMsg( fun, error_msg, HINW, OK );

	fflush(stdout);

	if ( explain == YES ) return OK;
	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;
	if ( ( rc = PrepareLesePharm( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadePharm( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;

	rc = LadePharm(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadePharm(error_msg)) < 0) return rc;

	return OK;
}

/*** PREPARE-LESE-PHARMACY-GROUPS ************************************************/

int PrepareLesePharm( char *error_msg )
{
	char *fun = "PrepareLesePharm";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, PHARMGRP_PELISTE );
/*	strcat( str, "PHARMACYGROUPID, " );
	strcat( str, "GROUP_NAME, " );
	strcat( str, "GROUP_TYPE, " );
	strcat( str, "PERCENT, " );
	strcat( str, "CONTRIBUTION, " );
	strcat( str, "CUSTOMERNO, " );
	strcat( str, "OMG_OWN_CONT, " );
	strcat( str, "PRICE_BASIS_PURCH, " );
	strcat( str, "RECLAIM_OMG_DISC, " );
	strcat( str, "SPECIALGROUP, " );
	strcat( str, "SPECIALGROUPREFNO, " );
	strcat( str, "GROUPING_VIS " );
*/	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":cpharmgrp " );

	exec sql prepare dec_pharm from :str;
	ERROR_MSG( "prepare dec_pharm" )
	exec sql declare Cselpharm cursor with hold for dec_pharm;

	return OK;      
}

/*** PREPARE-LADE-PHARMACY-GROUPS ************************************************/

int PrepareLadePharm( char *error_msg )
{
	char *fun = "PrepareLadePharm";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into pharmacygroups (" );
	strcat( str, PHARMGRP_PELISTE );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) " );
	   
	exec sql prepare ins_pharmgrp from :str;
	ERROR_MSG( "prepare ins_pharmgrp" )

	strcpy(str, "update pharmacygroups set " );
	strcat( str, PHARMGRP_UPDLISTE );
	strcat( str, " where current of Cselpharmgrp" );
	   
	exec sql prepare upd_pharmgrp from :str;
	ERROR_MSG( "prepare upd_pharmgrp" )

	strcpy( str, "select " );
	strcat( str, PHARMGRP_PELISTE );
	strcat( str, " from pharmacygroups" );
	strcat( str, " where pharmacygroupid = ?" );
	strcat( str, " for update " );

	exec sql prepare dec_pharmgrp from :str;
	ERROR_MSG( "prepare dec_pharmgrp" )
	exec sql declare Cselpharmgrp cursor with hold for dec_pharmgrp;

	return OK;
}


/*** LADE-PHARMACY-GROUPS ********************************************************/

int LadePharm( char *error_msg )
{
	char *fun = "LadePharm";
	
	exec sql begin declare section;
	pharmgrpS pgr;
	exec sql end declare section;

	psource = &source;

	exec sql open Cselpharmgrp using :psource->PHARMACYGROUPID;
	ERROR_MSG( "open Cselpharmgrp" )

	for(;;)
	{
		exec sql fetch Cselpharmgrp;
	    ERROR_MSG( "fetch Cselpharmgrp" )
		if ( NOTFOUND ) break;
		EXEC SQL EXECUTE upd_pharmgrp USING PHARMGRP_ZEIGER(psource);
		ERROR_MSG( "update pharmacygroups" )
		zaehlerUpd++;
		return OK;
	}
	EXEC SQL EXECUTE ins_pharmgrp USING PHARMGRP_ZEIGER(psource);
	ERROR_MSG( "insert pharmacygroups" )
	zaehlerIns++;
	return OK;
}


/***** AFTER-LADE-PHARMACY-GROUPS *********************************************/

int AfterLadePharm( char *error_msg )
{
	int rc;
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
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.13s %s %s\n",
		mld,
		99,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"loadpharmgrp",
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

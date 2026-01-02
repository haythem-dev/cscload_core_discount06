/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadimexpermission"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

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
#include "imexpermission.h"
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
struct N_IMEXPERMISSION a,*pa;
exec sql end declare section;

/***** DECLARATION **********************************************************/

int main						( int, char ** );
void PrintMsg					( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo				( char *error_msg, char mld, int rc );
int StarteLadenImex				( char *error_msg);
int PrepareLoadTables			( char *error_msg);
int LoadTables					( char *error_msg);
int AfterLoadTables				( char *error_msg);
int PrepareLadeImex				( char *error_msg);
int PrepareLeseImex				( char *error_msg);
int LeseImex					( char *error_msg);
int LadeImex					( char *error_msg);
int DelNotUpdatedImex			( char *error_msg);
int SetNotUpdatedImex			( char *error_msg);
int AfterLadeImex				( char *error_msg);
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
   
	if ( ( rc = StarteLadenImex( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN IMEXPERMISSION ************************************/

int StarteLadenImex( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenImex";
   
	exec sql open CselImex;
	ERROR_MSG( "open CselImex" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch CselImex into
			:a.COUNTRY_IFACODE,
			:a.IMEX_MODE,
			:a.ARTICLENO;
		ERROR_MSG( "fetch CselImex" )
		if(NOTFOUND) break;
		pa = &a;
		 
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
	sprintf( error_msg, "%d/%d Saetze geaendert/eingefuegt", zaehlerUpd,zaehlerIns );
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
	if ( ( rc = SetNotUpdatedImex(error_msg)) < 0) return rc;
	if ( ( rc = PrepareLeseImex( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeImex( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;

	rc = LadeImex(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeImex(error_msg)) < 0) return rc;

	return OK;
}

/*** PREPARE-LESE-IMEXPERMISSION ************************************************/

int PrepareLeseImex( char *error_msg )
{
	char *fun = "PrepareLeseImex";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "COUNTRY_IFACODE, " );
	strcat( str, "IMEX_MODE, " );
	strcat( str, "ARTICLENO " );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":cimexpermission " );

	exec sql prepare dec_cImex from :str;
	ERROR_MSG( "prepare dec_cImex" )
	exec sql declare CselImex cursor with hold for dec_cImex;

	return OK;      
}

/*** PREPARE-LADE-IMEXPERMISSION ************************************************/

int PrepareLadeImex( char *error_msg )
{
	char *fun = "PrepareLadeImex";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into imexpermission (" );
	strcat( str, IMEXPERMISSION_PELISTE );
	strcat( str, ",updatesign " );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ? ) " );
	   
	exec sql prepare ins_Imex from :str;
	ERROR_MSG( "prepare ins_Imex" )

	strcpy(str, "update imexpermission " );
	strcat( str, " set " );
	strcat( str, IMEXPERMISSION_UPDLISTE );
	strcat( str, ", updatesign=?" );
	strcat( str, " where COUNTRY_IFACODE=?" );
	strcat( str, " and IMEX_MODE=?" );
	strcat( str, " and ARTICLENO=?" );
	   
	exec sql prepare upd_Imex from :str;
	ERROR_MSG( "prepare upd_Imex" )

	return OK;
}


/*** LADE-IMEXPERMISSION ********************************************************/

int LadeImex( char *error_msg )
{
	char *fun = "LadeImex";

	EXEC SQL EXECUTE upd_Imex using 
		:pa->COUNTRY_IFACODE,
		:pa->IMEX_MODE,
		:pa->ARTICLENO,
		'1',
		:pa->COUNTRY_IFACODE,
		:pa->IMEX_MODE,
		:pa->ARTICLENO;
	ERROR_MSG( "execute upd_Imex" )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		EXEC SQL EXECUTE ins_Imex using
		:pa->COUNTRY_IFACODE,
		:pa->IMEX_MODE,
		:pa->ARTICLENO,
		'1';
		ERROR_MSG( "execute ins_Imex" )
		zaehlerIns++;
	}
	else
	{
		zaehlerUpd++;
	}

	return OK;
}


/***** AFTER-LADE-IMEXPERMISSION *********************************************/

int AfterLadeImex( char *error_msg )
{
	int rc;
	if ( (rc = DelNotUpdatedImex(error_msg)) < 0) return rc;
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
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.17s %s %s\n",
		mld,
		99,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"loadimexpermission",
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

int SetNotUpdatedImex( char *error_msg)
{
	char *fun = "SetNotUpdatedImex";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select updatesign from imexpermission");
	strcat(str," for update");

	EXEC SQL PREPARE sel_Imexupd FROM :str;
	ERROR_MSG( "prepare sel_Imexupd" )
	exec sql declare CImexupd Cursor with hold for sel_Imexupd;
	 
	strcpy( str, "update imexpermission set updatesign = '0' " );
	strcat( str, "where current of CImexupd " );
	
	exec sql prepare set_Imex from :str;
	ERROR_MSG( "prepare set_Imex" )

	exec sql open CImexupd;
    ERROR_MSG( "open CImexupd" )

    exec sql begin work;
	ERROR_MSG( "begin Work:" )
	for(comz=0 ;;comz++ )
	{
		if (comz%200 == 0)
		{
			exec sql commit work;
			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CImexupd;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CImexupd" )
		
		exec sql execute set_Imex;
		ERROR_MSG( "execute set_Imex" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work:" )
	exec sql close CImexupd ;
    ERROR_MSG( "close CImexupd" )

	return OK;
}

int DelNotUpdatedImex( char *error_msg)
{
	char *fun = "DelNotUpdatedImex";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select updatesign from imexpermission ");
	strcat(str," where updatesign = '0'");
	strcat(str," for update");

	EXEC SQL PREPARE sel_Imex2 FROM :str;
	ERROR_MSG( "prepare sel_Imex2" )
	exec sql declare DelImex Cursor with hold for sel_Imex2;
	 
	strcpy( str, "delete from imexpermission " );
	strcat( str, "where current of DelImex " );
	
	exec sql prepare del_Imex from :str;
	ERROR_MSG( "prepare del_Imex" )

	exec sql open DelImex;
    ERROR_MSG( "open DelImex" )

    exec sql begin work;
	ERROR_MSG( "begin Work:" )
	for(comz=0 ;;comz++ )
	{
		if (comz%200 == 0)
		{
			exec sql commit work;
			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch DelImex;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch DelImex" )
		
		exec sql execute del_Imex;
		ERROR_MSG( "execute del_Imex" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work:" )
	exec sql close DelImex;
    ERROR_MSG( "close DelImex" )

	return OK;
}

/***** ENDE *****************************************************************/

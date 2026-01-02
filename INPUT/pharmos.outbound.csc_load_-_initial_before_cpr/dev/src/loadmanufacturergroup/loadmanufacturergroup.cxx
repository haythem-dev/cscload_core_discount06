/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadmanufacturergroup"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "manufacturergroup.h"
#include <dirent.h>                                     
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>
/*#include "libtpld/dadedb.h"*/

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                   sqlca.sqlcode, sqlca.sqlerrd[1],sqlca.sqlerrm ); \
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
long datum = 0;

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
manufacturergroupS a;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo( char *error_msg, char mld, int rc );
int StarteLadenManufacturerGroup	( char *error_msg);
int PrepareLoadTables				( char *error_msg);
int LoadTables						( char *error_msg);
int AfterLoadTables					( char *error_msg);
int PrepareDelManufacturerGroup		( char *error_msg);
int PrepareLadeManufacturerGroup	( char *error_msg);
int PrepareLeseManufacturerGroup	( char *error_msg);
int DelManufacturerGroup			( char *error_msg);
int LeseManufacturerGroup			( char *error_msg);
int LadeManufacturerGroup			( char *error_msg);
int AfterLadeManufacturerGroup		( char *error_msg);
int CloseDatabase( void );

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
   
	if ( ( rc = StarteLadenManufacturerGroup( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER ManufacturerGroup ************************************/

int StarteLadenManufacturerGroup( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenManufacturerGroup";

	exec sql open Cselcmanugroup;

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch Cselcmanugroup into :a;
		ERROR_MSG( "fetch Cselcmanugroup" )
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

	sprintf( error_msg, "%d Saetze geladen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );

	if ( explain == YES ) return OK;
	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;
	if ( ( rc = PrepareLeseManufacturerGroup( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeManufacturerGroup( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareDelManufacturerGroup( error_msg ) ) < 0 ) return rc;
	if ( ( rc = DelManufacturerGroup( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;

	rc = LadeManufacturerGroup(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeManufacturerGroup(error_msg)) < 0) return rc;

	return OK;
}

/*** PREPARE-LOESCHEN-MANUFACTURERGROUP ************************************************/

int PrepareDelManufacturerGroup( char *error_msg )
{
	char *fun = "PrepareDelManufacturerGroup";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, MANUFACTURERGROUP_PELISTE );
	strcat( str, " from  " );
	strcat( str, "manufacturergroup " );
	strcat( str, "for update " );

	exec sql prepare sel_manugroup from :str;
	ERROR_MSG( "prepare sel_manugroup" )
	exec sql declare Cselmanugroup cursor with hold for sel_manugroup;

	strcpy( str, "delete " );
	strcat( str, "from  " );
	strcat( str, "manufacturergroup " );
	strcat( str, "where current of Cselmanugroup " );

	exec sql prepare del_manugroup from :str;
	ERROR_MSG( "prepare del_manugroup" )
	
	return OK;      
}

/*** PREPARE-LESE-MANUFACTURERGROUP ************************************************/

int PrepareLeseManufacturerGroup( char *error_msg )
{
	char *fun = "PrepareLeseManufacturerGroup";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, MANUFACTURERGROUP_PELISTE );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":cmanufacturergroup " );

	exec sql prepare dec_cmanugroup from :str;
	ERROR_MSG( "prepare dec_cmanugroup" )
	exec sql declare Cselcmanugroup cursor with hold for dec_cmanugroup;
	
	return OK;      
}

/*** PREPARE-LADE-MANUFACTURERGROUP ************************************************/

int PrepareLadeManufacturerGroup( char *error_msg )
{
	char *fun = "PrepareLadeManufacturerGroup";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into manufacturergroup (" );
	strcat( str, MANUFACTURERGROUP_PELISTE );
	strcat( str, " ) values " );
	strcat( str, "( ?, ? )" );
	   
	exec sql prepare ins_manugroup from :str;
	ERROR_MSG( "prepare ins_manugroup" )

	return OK;      
}

/*** LOESCHEN-MANUFACTURERGROUP ************************************************/

int DelManufacturerGroup( char *error_msg )
{
	char *fun = "DelManufacturerGroup";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	exec sql open Cselmanugroup;
	ERROR_MSG( "open Cselmanugroup" )

    EXEC SQL BEGIN WORK;
	ERROR_MSG( "begin work" )
		
	for(int zaehler = 0;;)
	{
		if((++zaehler%M_DURCHLAUF_COMMIT) == 0)
		{
			EXEC SQL COMMIT WORK;
			ERROR_MSG( "commit work between" )
				
			EXEC SQL BEGIN WORK;
			ERROR_MSG( "begin work between" )
		}
		exec sql fetch Cselmanugroup into :a;
		ERROR_MSG( "fetch Cselmanugroup" )

		if(SQLCODE == 100) break;

		EXEC SQL EXECUTE del_manugroup;
		ERROR_MSG( "execute del_manugroup" )
	}
	EXEC SQL COMMIT WORK;
	ERROR_MSG( "commit work" )
	
	return OK;      
}

/*** LADE-MANUFACTURERGROUP ********************************************************/

int LadeManufacturerGroup( char *error_msg )
{
	char *fun = "LadeManufacturerGroup";

	EXEC SQL EXECUTE ins_manugroup
			using
			:a.PHARMACYGROUPID,
			:a.KONSIG_PARTNER_NR
			;
	ERROR_MSG( "execute ins_manugroup" )

	return OK;
}


/***** AFTER-LADE-MANUFACTURERGROUP *********************************************/

int AfterLadeManufacturerGroup( char *error_msg )
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
		"loadmanufacturergroup",
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

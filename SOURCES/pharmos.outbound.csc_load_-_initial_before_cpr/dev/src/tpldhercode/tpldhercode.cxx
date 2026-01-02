/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tpldhercode"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include "libtpld/define.h"
#include <time.h>
#include <signal.h>
#include <string.h>         /* hajo */
#include <memory.h>         /* hajo */
#include <unistd.h>         /* hajo */

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define NOTFOUND           sqlca.sqlcode == SQLNOTFOUND

#define OK                   0
#define NO                   0
#define YES                  1
#define ERROR               -1
#define INSERT               1
#define FILE_NOT_FOUND       1
#define WARNING             -2
#define HINW               'H'
#define FEHL               'F'
#define RIO_EOF            110
#define RIO_NOFIND         111
#define OUTDATABASE        "phosix"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */

char log_file [300 + 1];
int debug_enabled  = NO;
int urladen  = NO;
char  dateiname[L_TEXT];
int load_all = NO;
int explain = NO;
int sichern = NO;
int zaehlerIns = 0;     /* weil ich zu faul war alex */
int zaehlerUpd = 0;     /* weil ich zu faul war alex */

exec sql begin declare section;
char outdatenbank[60];
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main						( int, char ** );
void PrintMsg					( char *fun, char *error_msg, char mld, int rc );
int LadenArtikelZentral			( char *error_msg);
int PrepareLoadTables			( char *error_msg);
int AfterLoadTables				( char *error_msg);
int PrepareLadeArtikelZentral	( char *error_msg);
int PrepareHoleHerst			( char *error_msg);
int LadeArtikelZentral			( char *error_msg);
int AfterLadeArtikelZentral		( char *error_msg);
int AfterHoleHerst				( char *error_msg);
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
	char  datum_msg[81];
	int	  iTable = -1;
	long  ltag;

	sprintf(outdatenbank,"%s",OUTDATABASE);
     
	strcpy(start_msg, "gestartet mit:");
	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-dg" ) )
		{
			strcat(start_msg, " -dg");
			debug_enabled = YES;
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
				" { -dbout datenbankname <Datenbankname Ausgabe> }\n\t"
				" { -dg <Debugging> }\n\t"
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
   
	if ( ( rc = LadenArtikelZentral( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	rc = AfterLoadTables( error_msg );
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** LADEN DER ARTIKELZENTRAL-TABELLEN ************************************/

int LadenArtikelZentral( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenDerArtikelRelationen";

	exec sql begin declare section;
	char arthercode[6];
	char herhercode[6];
	long hernr;
	exec sql end declare section;

	exec sql open Cselzentral;
	ERROR_MSG( "open Cselzentral" )
   
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch Cselzentral into :hernr,:arthercode;
		ERROR_MSG( "fetch Cselzentral" )
		if(NOTFOUND) break;
		 
		if( hernr == 0)
		{
			if( !strcmp(arthercode," ") )
			{
				continue;
			}
			else
			{
				strcpy(herhercode," ");
			}
		}
		else
		{
			exec sql open Cselherst using :hernr;
			ERROR_MSG( "open Cselherst" )
			exec sql fetch Cselherst into :herhercode;
			ERROR_MSG( "fetch Cselherst" )
		}
		if (strcmp(herhercode,arthercode))
		{
			exec sql execute upd_zentral using :herhercode;
			ERROR_MSG( "upd_zentral" )
		}
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }
        if ( zaehler % 1000 == 0 )
        {
           DEBUG_SECTION
           sprintf( error_msg, "%d Saetze geladen", zaehler );
           PrintMsg( fun, error_msg, HINW, OK );
           END_DEBUG_SECTION
        }
        if ( explain == YES )
           if ( zaehler > 5000 ) break;   /* Nur 5000 Saetze verarbeiten */

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	sprintf( error_msg, "%d Saetze geladen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );

	printf("tpldhercode: %d Saetze geladen", zaehler);
	fflush(stdout);

	if ( explain == YES ) return OK;
	rc = OK;
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;
	if ( ( rc = PrepareLadeArtikelZentral( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareHoleHerst( error_msg ) ) < 0 ) return rc;

   return OK;
}


/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeArtikelZentral(error_msg)) < 0) return rc;
	if ( (rc = AfterHoleHerst(error_msg)) < 0) return rc;

	return OK;
}


/*** PREPARE-LADE-ARTIKEL-ZENTRAL ************************************************/

int PrepareLadeArtikelZentral( char *error_msg )
{
	char *fun = "PrepareLadeArtikelZentral";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "hersteller_nr, " );
	strcat( str, "hersteller_code " );
	strcat( str, " from artikelzentral for update " );

	exec sql prepare dec_artikelzent from :str;
	ERROR_MSG( "prepare dec_artikelzent" )
	exec sql declare Cselzentral cursor with hold for dec_artikelzent;
	
	strcpy( str, "update artikelzentral set " );
	strcat( str, "HERSTELLER_CODE = ? " );            
	strcat( str, "where current of Cselzentral" );
	  
	exec sql prepare upd_zentral from :str;
	ERROR_MSG( "prepare upd_zentral" )
   
	return OK;      
}

/*** PREPARE-HOLE-HERST ************************************************/

int PrepareHoleHerst( char *error_msg )
{
	char *fun = "PrepareHoleHerst";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "hersteller_code " );
	strcat( str, "from herstel " );
	strcat( str, "where hersteller_nr = ? " );

	exec sql prepare dec_herst from :str;
	ERROR_MSG( "prepare dec_herst" )
	exec sql declare Cselherst cursor with hold for dec_herst;

	return OK;      
}

/***** AFTER-LADE-ARTIKEL-ZENTRAL *********************************************/

int AfterLadeArtikelZentral( char *error_msg )
{
	return OK;
}

/***** AFTER-HOLE-HERSTELLER *********************************************/

int AfterHoleHerst( char *error_msg )
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
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.11s %s %s\n",
		mld,
		99,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"tpldhercode",
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



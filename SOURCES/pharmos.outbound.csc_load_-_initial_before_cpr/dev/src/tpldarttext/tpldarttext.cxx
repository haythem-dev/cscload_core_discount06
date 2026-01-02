/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tpldarttext"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>                                     
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>
#include <libtpld/hsystfkt.h>
#include "pplib/allg.h"

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
char  dateiname[L_TEXT];
int zaehlerIns = 0;     /* weil ich zu faul war alex */
int zaehlerUpd = 0;     /* weil ich zu faul war alex */

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
struct N_CARTICLETEXT
{
	char TEXTNO[3];
	char TEXTLINE1[31];
	char TEXTLINE2[31];
	char PR_INVOICE[2];
	char PR_PICKLIST[2];
	char SH_CALLCENTER[2];
	char PR_ORDERPROP[2];
	char LONGTEXT_FR[481];
} ca;
struct N_ARTICLETEXT
{
	short BRANCHNO;
	short TEXTKEY;
	char TEXT[241];
	char DISPLAYONSCREEN[2];
	char TEXTHOSPITAL[481];
} art;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main							( int, char ** );
void PrintMsg						( char *fun, char *error_msg, char mld, int rc );
int StarteLadenDerArtikelRelationen	( char *error_msg);
int PrepareLoadTables				( char *error_msg);
int LoadTables						( char *error_msg);
int AfterLoadTables					( char *error_msg);
int PrepareHoleArtikelText			( char *error_msg);
int PrepareLadeArtikelText			( char *error_msg);
int LadeArtikelText					( char *error_msg);
int AfterLadeArtikelText			( char *error_msg);
int CloseDatabase					( void );

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

	exec sql database :outdatenbank;
	ERROR_MSG( "Fehler oeffnen DB" )

	exec sql set lock mode to wait 20;
	ERROR_MSG( "Set LockMode to Wait" )

	exec sql set isolation to dirty read;
	ERROR_MSG( "Set Isolation to Dirty Read" )

	PrintMsg( fun, start_msg, HINW, 0 );
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	if ( ( rc = StarteLadenDerArtikelRelationen( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	sprintf( error_msg, "%d Saetze eingefuegt", zaehlerIns );
	PrintMsg( fun, error_msg, HINW, OK );
	sprintf( error_msg, "%d Saetze geaendert", zaehlerUpd );
	PrintMsg( fun, error_msg, HINW, OK );
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER ARTIKEL-TABELLEN ************************************/

int StarteLadenDerArtikelRelationen( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenDerArtikelRelationen";
   
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch Cselcarttext into :ca;
		ERROR_MSG( "fetch Cselcarttext" )
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
	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	sprintf( error_msg, "%d Saetze gelesen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );

	printf("tpldarttext: %d Saetze geladen\n", zaehler);
	fflush(stdout);

	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;
	if ( ( rc = PrepareHoleArtikelText( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeArtikelText( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;
	/* neue Tabellen schreiben */

	rc = LadeArtikelText(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeArtikelText(error_msg)) < 0) return rc;

	return OK;
}

/*** PREPARE-HOLE-ARTIKEL-TEXT ************************************************/

int PrepareHoleArtikelText( char *error_msg )
{
	char *fun = "PrepareHoleArtikelText";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "select " );
	strcat( str, "TEXTNO," );
	strcat( str, "TEXTLINE1," );
	strcat( str, "TEXTLINE2," );
	strcat( str, "PR_INVOICE," );
	strcat( str, "PR_PICKLIST," );
	strcat( str, "SH_CALLCENTER," );
	strcat( str, "PR_ORDERPROP," );
	strcat( str, "LONGTEXT_FR" );
	strcat( str, " from " );
	strcat( str, indatenbank );
	strcat( str, ":carticletext " );

	exec sql prepare sel_carttext from :str;
	ERROR_MSG( "prepare sel_carttext" )
 
	exec sql declare Cselcarttext cursor with hold for sel_carttext;
	ERROR_MSG( "declare Cselcarttext" )

	exec sql open Cselcarttext;
	ERROR_MSG( "open Cselcarttext" )
	return OK;      
}

/*** PREPARE-LADE-ARTIKEL-TEXT ************************************************/

int PrepareLadeArtikelText( char *error_msg )
{
	char *fun = "PrepareLadeArtikelText";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into articletext (" );
	strcat( str, "BRANCHNO," );
	strcat( str, "TEXTKEY," );
	strcat( str, "TEXT," );
	strcat( str, "DISPLAYONSCREEN," );
	strcat( str, "TEXTHOSPITAL" );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ? )" );
	   
	exec sql prepare ins_artikeltext from :str;
	ERROR_MSG( "prepare ins_artikeltext" )
 
	strcpy( str, "select " );
	strcat( str, "BRANCHNO," );
	strcat( str, "TEXTKEY," );
	strcat( str, "TEXT," );
	strcat( str, "DISPLAYONSCREEN," );
	strcat( str, "TEXTHOSPITAL" );
	strcat( str, " from articletext where textkey = ? for update " );

	exec sql prepare dec_artikeltext from :str;
	ERROR_MSG( "prepare dec_artikeltext" )
	exec sql declare Cupdartikeltext cursor for dec_artikeltext;
	
	strcpy( str, "update articletext set " );
	strcat( str, "TEXT = ?," );
	strcat( str, "DISPLAYONSCREEN = ?," );
	strcat( str, "TEXTHOSPITAL = ? " );
	strcat( str, "where current of Cupdartikeltext" );
	  
	exec sql prepare upd_artikeltext from :str;
	ERROR_MSG( "prepare upd_artikeltext" )
   
	return OK;      
}

/*** LADE-ARTIKEL-TEXT *********************************************************/

int LadeArtikelText(char *error_msg)
{
	int rc;
	char huelse[20];
	char *fun = "LadeArtikelText";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	art.TEXTKEY = atoi(ca.TEXTNO);
	exec sql open Cupdartikeltext using :art.TEXTKEY;
	ERROR_MSG( "open Cupdartikeltext" )
	  
	exec sql fetch Cupdartikeltext into :art;
	ERROR_MSG( "fetch Cupdartikeltext" )

	sprintf(art.TEXT,"%s%s",ca.TEXTLINE1,ca.TEXTLINE2);
	strcpy(art.DISPLAYONSCREEN,ca.SH_CALLCENTER);
	strcpy(art.TEXTHOSPITAL,ca.LONGTEXT_FR);

	if ( sqlca.sqlcode == 0 )
	{
		exec sql execute upd_artikeltext using
			:art.TEXT,
			:art.DISPLAYONSCREEN,
			:art.TEXTHOSPITAL
			;

		ERROR_MSG( "execute upd_artikeltext" )
		zaehlerUpd++;
		return 0;
	}

	EXEC SQL EXECUTE ins_artikeltext USING
			'0',
			:art.TEXTKEY,
			:art.TEXT,
			:art.DISPLAYONSCREEN,
			:art.TEXTHOSPITAL
               ;

	ERROR_MSG( "insert Artikeltext" );
	zaehlerIns++;

	return 0;
}

/***** AFTER-LADE-ARTIKEL-TEXT *********************************************/

int AfterLadeArtikelText( char *error_msg )
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
		"tpldarttext",
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

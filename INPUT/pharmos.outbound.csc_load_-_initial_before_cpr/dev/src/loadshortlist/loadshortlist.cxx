/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadshortlist"

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
#include "discountlist.h"
#include <string.h>
#include <unistd.h>

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
struct N_DISCOUNTLIST a,*pa;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main						( int, char ** );
void PrintMsg					( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo				( char *error_msg, char mld, int rc );
int StarteLadenShortList		( char *error_msg);
int PrepareLoadTables			( char *error_msg);
int LoadTables					( char *error_msg);
int AfterLoadTables				( char *error_msg);
int PrepareLadeShortList		( char *error_msg);
int PrepareLeseShortList		( char *error_msg);
int LeseShortList				( char *error_msg);
int LadeShortList				( char *error_msg);
int DelNotUpdatedShortList		( char *error_msg);
int SetNotUpdatedShortList		( char *error_msg);
int AfterLadeShortList			( char *error_msg);
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
   
	if ( ( rc = StarteLadenShortList( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER SHORT-KKONDITIONEN ************************************/

int StarteLadenShortList( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenShortList";
   
	exec sql open Cselcdisclist;
	ERROR_MSG( "open Cselcdisclist" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch Cselcdisclist into :a;
		ERROR_MSG( "fetch Cselcdisclist" )
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

	sprintf( error_msg, "%d Saetze geladen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );

	printf("loadshortlist: %d Saetze geladen\n", zaehler);
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
	if ( ( rc = SetNotUpdatedShortList(error_msg)) < 0) return rc;
	if ( ( rc = PrepareLeseShortList( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeShortList( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;

	rc = LadeShortList(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeShortList(error_msg)) < 0) return rc;

	return OK;
}

/*** PREPARE-LESE-SHORT-KONDITIONEN ************************************************/

int PrepareLeseShortList( char *error_msg )
{
	char *fun = "PrepareLeseShortList";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, DISCOUNTLIST_PELISTE );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":cdisclist " );

	exec sql prepare dec_cdiscount from :str;
	ERROR_MSG( "prepare dec_cdiscount" )
	exec sql declare Cselcdisclist cursor with hold for dec_cdiscount;

	return OK;      
}

/*** PREPARE-LADE-SHORT-KONDITIONEN ************************************************/

int PrepareLadeShortList( char *error_msg )
{
	char *fun = "PrepareLadeShortList";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into discountlist (" );
	strcat( str, DISCOUNTLIST_PELISTE );
	strcat( str, ",UPD_FLAG " );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ? ) " );
	   
	exec sql prepare ins_discountlist from :str;
	ERROR_MSG( "prepare ins_discountlist" )

	strcpy(str, "update discountlist " );
	strcat( str, " set " );
	strcat( str, DISCOUNTLIST_UPDLISTE );
	strcat( str, ", UPD_FLAG=?" );
	strcat( str, " where ORDER_TYPE=?" );
	strcat( str, " and SUB_ORDER_TYPE=?" );
	   
	exec sql prepare upd_discountlist from :str;
	ERROR_MSG( "prepare upd_discountlist" )

	return OK;
}


/*** LADE-SHORT-KONDITIONEN ********************************************************/

int LadeShortList( char *error_msg )
{
	char *fun = "LadeShortList";

	EXEC SQL EXECUTE upd_discountlist using 
		:pa,
		'1',
		:pa->ORDER_TYPE,
		:pa->SUB_ORDER_TYPE;
	ERROR_MSG( "execute upd_discountlist" )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		EXEC SQL EXECUTE ins_discountlist using :pa,'1';
		ERROR_MSG( "execute ins_discountlist" )
		zaehlerIns++;
		return OK;
	}
	zaehlerUpd++;
   
	return OK;
}


/***** AFTER-LADE-KONDITIONEN *********************************************/

int AfterLadeShortList( char *error_msg )
{
	int rc;
	if ( (rc = DelNotUpdatedShortList(error_msg)) < 0) return rc;
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
		"loadshortlist",
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

int SetNotUpdatedShortList( char *error_msg)
{
	char *fun = "SetNotUpdatedShortList";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select upd_flag from discountlist");
	strcat(str," for update");

	EXEC SQL PREPARE sel_shortupd FROM :str;
	ERROR_MSG( "prepare sel_shortupd" )
	exec sql declare CShortupd Cursor with hold for sel_shortupd;
	 
	strcpy( str, "update discountlist set upd_flag = '0' " );
	strcat( str, "where current of CShortupd " );
	
	exec sql prepare set_short from :str;
	ERROR_MSG( "prepare set_short" )

	exec sql open CShortupd;
    ERROR_MSG( "open CShortupd" )

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
		exec sql fetch CShortupd;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CShortupd" )
		
		exec sql execute set_short;
		ERROR_MSG( "execute set_short" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work:" )
	exec sql close CShortupd ;
    ERROR_MSG( "close CShortupd" )

	return OK;
}

int DelNotUpdatedShortList( char *error_msg)
{
	char *fun = "DelNotUpdatedShortList";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select upd_flag from discountlist ");
	strcat(str," where upd_flag = '0'");
	strcat(str," for update");

	EXEC SQL PREPARE sel_short2 FROM :str;
	ERROR_MSG( "prepare sel_short2" )
	exec sql declare DelShort Cursor with hold for sel_short2;
	 
	strcpy( str, "delete from discountlist " );
	strcat( str, "where current of DelShort " );
	
	exec sql prepare del_short from :str;
	ERROR_MSG( "prepare del_short" )

	exec sql open DelShort;
    ERROR_MSG( "open DelShort" )

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
		exec sql fetch DelShort;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch DelShort" )
		
		exec sql execute del_short;
		ERROR_MSG( "execute del_short" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work:" )
	exec sql close DelShort ;
    ERROR_MSG( "close DelShort" )

	return OK;
}

/***** ENDE *****************************************************************/

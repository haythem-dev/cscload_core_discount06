/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

/* ToDo Programmname */
#define PROJECTNAME	 "loadnarcgroup"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
/* ToDo Include */
#include "narcgroup.h"
#include "allg.h"
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
int zaehlerIns = 0;
int zaehlerUpd = 0;
int zaehlerDel = 0;

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
/* ToDo Structur */
narcgroupS indatensatz;
narcgroupS outdatensatz;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main						( int, char ** );
void PrintMsg					( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo				( char *error_msg, char mld, int rc );
int SetNotUpdated				( char *error_msg);
int DelNotUpdated				( char *error_msg);
int PrepareLadeDaten			( char *error_msg);
int LadeDaten					( char *error_msg);
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

	if (PrepareLadeDaten(error_msg) != OK)
		return 8;

	if (SetNotUpdated(error_msg) != OK)
		return 8;

	if ( ( rc = LadeDaten( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}

	if (DelNotUpdated(error_msg) != OK)
		return 8;

	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
/***** LADEN DER DATEN ************************************/

int LadeDaten( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "LadeDaten";
   
	exec sql open CselzData;
	ERROR_MSG( "open CselzData" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
		{
			EXEC SQL commit work;
			ERROR_MSG( "Commit Work" )
			
			EXEC SQL begin work;
			ERROR_MSG( "Begin Work" )
		}

		exec sql fetch CselzData into :indatensatz;
		ERROR_MSG("fetch CselzData")
			if (NOTFOUND) break;

		/* ToDo Indexfelder */
		exec sql open CupdloadData using :indatensatz.BTM_GRUPPE;
		ERROR_MSG("open CupdloadData")

		exec sql fetch CupdloadData into :outdatensatz;
		ERROR_MSG("fetch CupdloadData")

		if (sqlca.sqlcode == 0)
		{
			exec sql execute upd_loadData using :indatensatz;
			ERROR_MSG("execute upd_loadData")

			zaehlerUpd++;
		}
		else
		{
			exec sql execute ins_loadData using :indatensatz;
			ERROR_MSG("execute ins_loadData")

			zaehlerIns++;
		}

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG("Commit Work")

	zaehler--;

	sprintf( error_msg, "%d Saetze gelesen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );
	sprintf(error_msg, "%d Saetze geaendert", zaehlerUpd);
	PrintMsg(fun, error_msg, HINW, OK);
	sprintf( error_msg, "%d Saetze eingefuegt", zaehlerIns );
	PrintMsg( fun, error_msg, HINW, OK );

	return rc;
}

/*** KENNZEICHNEN-NICHT-BEARBEITET ************************************************/

int SetNotUpdated(char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "SetNotUpdated";

	exec sql begin declare section;
	char upd_flag[2];
	exec sql end declare section;

	exec sql open CSetNotUpdate;
	ERROR_MSG("open CSetNotUpdate")

	EXEC SQL begin work;
	ERROR_MSG("Begin Work")

	for (;; )
	{
		if (zaehler++ % M_DURCHLAUF_COMMIT == 0)
		{
			EXEC SQL commit work;
			ERROR_MSG("Commit Work")

			EXEC SQL begin work;
			ERROR_MSG("Begin Work")
		}
		exec sql fetch CSetNotUpdate into :upd_flag;
		ERROR_MSG("fetch CSetNotUpdate")

		if (NOTFOUND) break;

		exec sql execute set_notupdated;
		ERROR_MSG("set_notupdated")
	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG("Commit Work")

	return rc;
}

/*** LOESCHEN-NICHT-BEARBEITET ************************************************/

int DelNotUpdated(char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "DelNotUpdated";

	exec sql begin declare section;
	char upd_flag[2];
	exec sql end declare section;

	exec sql open CDelNotUpdate;
	ERROR_MSG("open CDelNotUpdate")

	EXEC SQL begin work;
	ERROR_MSG("Begin Work")

	for (;; )
	{
		if (zaehler++ % M_DURCHLAUF_COMMIT == 0)
		{
			EXEC SQL commit work;
			ERROR_MSG("Commit Work")

			EXEC SQL begin work;
			ERROR_MSG("Begin Work")
		}

		exec sql fetch CDelNotUpdate into :upd_flag;
		ERROR_MSG("fetch CDelNotUpdate")
		if (NOTFOUND) break;

		exec sql execute del_notupdated;
		ERROR_MSG("del_notupdated")
		zaehlerDel++;
	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG("Commit Work")

	sprintf(error_msg, "%d Saetze geloescht", zaehlerDel);
	PrintMsg(fun, error_msg, HINW, OK);

	return rc;
}

/*** PREPARE-LADE-DATEN ************************************************/

int PrepareLadeDaten( char *error_msg )
{
	char *fun = "PrepareLadeDaten";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

/*	kennzeichnen nicht geaendert	*/
	strcpy(str, "select ");
	strcat(str, "upd_flag ");
	strcat(str, "from ");
	/* ToDo Tabelle */
	strcat(str, "narcgroup ");
	strcat(str, "for update ");

	exec sql prepare dec_setnotupdated from :str;
	ERROR_MSG("prepare dec_setnotupdated")
	exec sql declare CSetNotUpdate cursor with hold for dec_setnotupdated;

	strcpy(str, "update ");
	/* ToDo Tabelle */
	strcat(str, "narcgroup ");
	strcat(str, "set upd_flag = '0' ");
	strcat(str, "where current of CSetNotUpdate ");

	exec sql prepare set_notupdated from :str;
	ERROR_MSG("prepare set_notupdated")

/*	loeschen nicht geaendert	*/
	strcpy(str, "select ");
	strcat(str, "upd_flag ");
	strcat(str, "from ");
	/* ToDo Tabelle */
	strcat(str, "narcgroup ");
	strcat(str, "where ");
	strcat(str, "upd_flag = '0' ");
	strcat(str, "for update ");

	exec sql prepare dec_delnotupdated from :str;
	ERROR_MSG("prepare dec_delnotupdated")
	exec sql declare CDelNotUpdate cursor with hold for dec_delnotupdated;

	strcpy(str, "delete from ");
	/* ToDo Tabelle */
	strcat(str, "narcgroup ");
	strcat(str, "where current of CDelNotUpdate ");

	exec sql prepare del_notupdated from :str;
	ERROR_MSG("prepare del_notupdated")

/*	zu ladende Daten	*/
	strcpy(str, "select ");
	/* ToDo Tabelle */
	strcat(str, NARCGROUP_PELISTE);
	strcat(str, " from  ");
	strcat(str, indatenbank);
	strcat(str, ":zdkbtm ");

	exec sql prepare dec_zData from :str;
	ERROR_MSG("prepare dec_zData")
	exec sql declare CselzData cursor with hold for dec_zData;

/*	vorhandene Daten	*/
	strcpy(str, "select ");
	/* ToDo Tabelle */
	strcat(str, NARCGROUP_PELISTE);
	strcat(str, " from ");
	strcat(str, "narcgroup ");
	strcat(str, "where ");
	/* ToDo Indxfelder */
	strcat(str, "btm_gruppe = ? ");
	strcat(str, "for update ");

	exec sql prepare sel_loadData from :str;
	ERROR_MSG("prepare sel_loadData")
	exec sql declare CupdloadData cursor with hold for sel_loadData;

	strcpy(str, "update narcgroup set ");
	/* ToDo Tabelle */
	strcat(str, NARCGROUP_UPDLISTE);
	strcat(str, ",upd_flag = '1' ");
	strcat(str, "where current of CupdloadData ");

	exec sql prepare upd_loadData from :str;
	ERROR_MSG("prepare upd_loadData")

	strcpy(str, "insert into narcgroup (");
	/* ToDo Tabelle */
	strcat(str, NARCGROUP_PELISTE);
	strcat(str, ",upd_flag ");
	strcat(str, " ) values ");
	/* ToDo Anzahl Felder */
	strcat(str, "( ?, ?, ?, ?, '1' )");

	exec sql prepare ins_loadData from :str;
	ERROR_MSG("prepare ins_loadData")

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
		PROJECTNAME,
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

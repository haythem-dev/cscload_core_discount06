/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadordercriteria"

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
#include "ordercriteria.h"
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
struct N_ORDERCRITERIA a,*pa;
int sBranchno = 0;
exec sql end declare section;

/***** DECLARATION **********************************************************/

int main						( int, char ** );
void PrintMsg					( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo				( char *error_msg, char mld, int rc );
int StarteLadenCriteria			( char *error_msg);
int PrepareLoadTables			( char *error_msg);
int LoadTables					( char *error_msg);
int AfterLoadTables				( char *error_msg);
int PrepareLadeCriteria			( char *error_msg);
int PrepareLeseCriteria			( char *error_msg);
int LeseCriteria				( char *error_msg);
int LadeCriteria				( char *error_msg);
int DelNotUpdatedCriteria		( char *error_msg);
int SetNotUpdatedCriteria		( char *error_msg);
int AfterLadeCriteria			( char *error_msg);
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
		else if ( !strcmp( schalter, "-vz" ) )
		{
			strcat(start_msg, " -vz");
			i++;
			sBranchno = atoi(argv[i]);
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
				" { -vz filialnr }\n\t"
				" [ -ex <Explain> ]\n\t",
				argv[0] );
			return 1;
		}
	}
	if(sBranchno == 0)
	{
		printf( "  usage: %s\n\t"
				" { -dbin datenbankname <Datenbankname Eingabe> }\n\t"
				" { -dbout datenbankname <Datenbankname Ausgabe> }\n\t"
				" { -vz filialnr }\n\t"
				" [ -ex <Explain> ]\n\t",
				argv[0] );
		return 1;
	}
	a.BRANCHNO = sBranchno;

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
   
	if ( ( rc = StarteLadenCriteria( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER AUFTRAGSKRITERIEN ************************************/

int StarteLadenCriteria( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenCriteria";
   
	exec sql open CselCriteria;
	ERROR_MSG( "open CselCriteria" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch CselCriteria into
			:a.ARTICLENO,
			:a.MANUFACTURERNO,
			:a.PHARMACYGROUPID,
			:a.CUSTOMERNO,
			:a.ORDER_TYPE,
			:a.MINORDERQTY,
			:a.MINORDERVALUE,
			:a.LIMIT_ACTION,
			:a.ACTION_RESTRICTION,
			:a.ADDONCHARGEARTNO,
			:a.ADDONCHARGEPCT;
		ERROR_MSG( "fetch CselCriteria" )
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
	if ( ( rc = SetNotUpdatedCriteria(error_msg)) < 0) return rc;
	if ( ( rc = PrepareLeseCriteria( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeCriteria( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;

	rc = LadeCriteria(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeCriteria(error_msg)) < 0) return rc;

	return OK;
}

/*** PREPARE-LESE-SHORT-KONDITIONEN ************************************************/

int PrepareLeseCriteria( char *error_msg )
{
	char *fun = "PrepareLeseCriteria";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "ARTICLENO, " );
	strcat( str, "MANUFACTURERNO, " );
	strcat( str, "PHARMACYGROUPID, " );
	strcat( str, "CUSTOMERNO, " );
	strcat( str, "ORDER_TYPE, " );
	strcat( str, "MINORDERQTY, " );
	strcat( str, "MINORDERVALUE, " );
	strcat( str, "LIMIT_ACTION, " );
	strcat( str, "ACTION_RESTRICTION, " );
	strcat( str, "ADDONCHARGEARTNO, " );
	strcat( str, "ADDONCHARGEPCT " );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":cordercriteria " );

	exec sql prepare dec_cCriteria from :str;
	ERROR_MSG( "prepare dec_cCriteria" )
	exec sql declare CselCriteria cursor with hold for dec_cCriteria;

	return OK;      
}

/*** PREPARE-LADE-SHORT-KONDITIONEN ************************************************/

int PrepareLadeCriteria( char *error_msg )
{
	char *fun = "PrepareLadeCriteria";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into ordercriteria (" );
	strcat( str, ORDERCRITERIA_PELISTE );
	strcat( str, ",upd_flag " );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) " );
	   
	exec sql prepare ins_Criteria from :str;
	ERROR_MSG( "prepare ins_Criteria" )

	strcpy(str, "update ordercriteria " );
	strcat( str, " set " );
	strcat( str, ORDERCRITERIA_UPDLISTE );
	strcat( str, ", upd_flag=?" );
	strcat( str, " where BRANCHNO=?" );
	strcat( str, " and ARTICLENO=?" );
	strcat( str, " and MANUFACTURERNO=?" );
	strcat( str, " and PHARMACYGROUPID=?" );
	strcat( str, " and CUSTOMERNO=?" );
	strcat( str, " and ORDER_TYPE=?" );
	strcat( str, " and MINORDERQTY=?" );
	strcat( str, " and MINORDERVALUE=?" );
	   
	exec sql prepare upd_Criteria from :str;
	ERROR_MSG( "prepare upd_Criteria" )

	return OK;
}


/*** LADE-SHORT-KONDITIONEN ********************************************************/

int LadeCriteria( char *error_msg )
{
	char *fun = "LadeCriteria";

	pa->BRANCHNO = sBranchno;
	EXEC SQL EXECUTE upd_Criteria using 
		:pa->BRANCHNO,
		:pa->ARTICLENO,
		:pa->MANUFACTURERNO,
		:pa->PHARMACYGROUPID,
		:pa->CUSTOMERNO,
		:pa->ORDER_TYPE,
		:pa->MINORDERQTY,
		:pa->MINORDERVALUE,
		:pa->LIMIT_ACTION,
		:pa->ACTION_RESTRICTION,
		:pa->ADDONCHARGEARTNO,
		:pa->ADDONCHARGEPCT,
		'1',
		:pa->BRANCHNO,
		:pa->ARTICLENO,
		:pa->MANUFACTURERNO,
		:pa->PHARMACYGROUPID,
		:pa->CUSTOMERNO,
		:pa->ORDER_TYPE,
		:pa->MINORDERQTY,
		:pa->MINORDERVALUE;
	ERROR_MSG( "execute upd_Criteria" )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		pa->BRANCHNO = sBranchno;
		EXEC SQL EXECUTE ins_Criteria using
		:pa->BRANCHNO,
		:pa->ARTICLENO,
		:pa->MANUFACTURERNO,
		:pa->PHARMACYGROUPID,
		:pa->CUSTOMERNO,
		:pa->ORDER_TYPE,
		:pa->MINORDERQTY,
		:pa->MINORDERVALUE,
		:pa->LIMIT_ACTION,
		:pa->ACTION_RESTRICTION,
		:pa->ADDONCHARGEARTNO,
		:pa->ADDONCHARGEPCT,
		'1';
		ERROR_MSG( "execute ins_Criteria" )
		zaehlerIns++;
	}
	else
	{
		zaehlerUpd++;
	}

	return OK;
}


/***** AFTER-LADE-KONDITIONEN *********************************************/

int AfterLadeCriteria( char *error_msg )
{
	int rc;
	if ( (rc = DelNotUpdatedCriteria(error_msg)) < 0) return rc;
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
		"loadordercriteria",
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

int SetNotUpdatedCriteria( char *error_msg)
{
	char *fun = "SetNotUpdatedCriteria";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select upd_flag from ordercriteria");
	strcat(str," where BRANCHNO = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_Criteriaupd FROM :str;
	ERROR_MSG( "prepare sel_Criteriaupd" )
	exec sql declare CCriteriaupd Cursor with hold for sel_Criteriaupd;
	 
	strcpy( str, "update ordercriteria set upd_flag = '0' " );
	strcat( str, "where current of CCriteriaupd " );
	
	exec sql prepare set_Criteria from :str;
	ERROR_MSG( "prepare set_Criteria" )

	exec sql open CCriteriaupd using :sBranchno;
    ERROR_MSG( "open CCriteriaupd" )

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
		exec sql fetch CCriteriaupd;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CCriteriaupd" )
		
		exec sql execute set_Criteria;
		ERROR_MSG( "execute set_Criteria" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work:" )
	exec sql close CCriteriaupd ;
    ERROR_MSG( "close CCriteriaupd" )

	return OK;
}

int DelNotUpdatedCriteria( char *error_msg)
{
	char *fun = "DelNotUpdatedCriteria";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select upd_flag from ordercriteria ");
	strcat(str," where upd_flag = '0'");
	strcat(str," and BRANCHNO = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_Criteria2 FROM :str;
	ERROR_MSG( "prepare sel_Criteria2" )
	exec sql declare DelCriteria Cursor with hold for sel_Criteria2;
	 
	strcpy( str, "delete from ordercriteria " );
	strcat( str, "where current of DelCriteria " );
	
	exec sql prepare del_Criteria from :str;
	ERROR_MSG( "prepare del_Criteria" )

	exec sql open DelCriteria using :sBranchno;
    ERROR_MSG( "open DelCriteria" )

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
		exec sql fetch DelCriteria;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch DelCriteria" )
		
		exec sql execute del_Criteria;
		ERROR_MSG( "execute del_Criteria" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work:" )
	exec sql close DelCriteria ;
    ERROR_MSG( "close DelCriteria" )

	return OK;
}

/***** ENDE *****************************************************************/

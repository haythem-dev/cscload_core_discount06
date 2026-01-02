/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "setarticlecategory"

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
#include "articlegrp.h"
#include "zarticlecategory.h"
#include <dirent.h>                                     
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>
#include "libtpld/dadedb.h"

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
long datum = 0;

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
zarticlecategoryS artcat;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
int StarteLadenGruppen		  ( char *error_msg);
int PrepareLoadTables         ( char *error_msg);
int SetNotUpdatedGruppen      ( char *error_msg);
int DelNotUpdatedGruppen      ( char *error_msg);
int LoadTables                ( char *error_msg);
int AfterLoadTables           ( char *error_msg);
int PrepareLadeGruppen	      ( char *error_msg);
int PrepareLeseGruppen        ( char *error_msg);
int LeseGruppen               ( char *error_msg);
int LadeGruppen               ( char *error_msg);
int AfterLadeGruppen          ( char *error_msg);
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

	exec sql database :indatenbank;
	ERROR_MSG( "Fehler oeffnen DB" )

	exec sql set lock mode to wait 20;
	ERROR_MSG( "Set LockMode to Wait" )

	exec sql set isolation to dirty read;
	ERROR_MSG( "Set Isolation to Dirty Read" )

	PrintMsg( fun, start_msg, HINW, 0 );
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	if ( ( rc = StarteLadenGruppen( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	if ( AfterLoadTables( error_msg ) != OK )
		return 10;  
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER ARTIKEL-GRUPPEN ************************************/

int StarteLadenGruppen( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenGruppen";
   
	exec sql open Cselartcat;

	for ( ;; )
	{
		exec sql fetch Cselartcat into :artcat;
		ERROR_MSG( "fetch Cselartcat" )
		if(NOTFOUND) break;
		 

        if ( ( rc = LoadTables( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
	}      /* ende for */

	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;
	if ( ( rc = SetNotUpdatedGruppen( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLeseGruppen( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeGruppen( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;

	rc = LadeGruppen(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeGruppen(error_msg)) < 0) return rc;

	return OK;
}

/*** SET-UPDFLAG ************************************************/

int SetNotUpdatedGruppen( char *error_msg )
{
	char *fun = "SetNotUpdatedGruppen";
	int i;

	exec sql begin declare section;
	char str[2048];
	char cUpd_Flag[2];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "upd_flag  " );
	strcat( str, "from " );
	strcat( str, outdatenbank );
	strcat( str, ":articlegroup " );
	strcat( str, "for update " );

	exec sql prepare set_grp from :str;
	ERROR_MSG( "prepare set_grp" )
	exec sql declare CSetGrp cursor with hold for set_grp;

	strcpy( str, "update " );
	strcat( str, outdatenbank );
	strcat( str, ":articlegroup " );
	strcat( str, "set upd_flag = '0' " );
	strcat( str, "where current of CSetGrp " );
	
	exec sql prepare upd_grp from :str;
	ERROR_MSG( "prepare upd_grp" )

	exec sql open CSetGrp;
    ERROR_MSG( "open CSetGrp" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CSetGrp into :cUpd_Flag;
		if(NOTFOUND) break;
		ERROR_MSG( "fetch CSetGrp" )

		exec sql execute upd_grp;
		ERROR_MSG( "execute upd_grp" )

	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close CSetGrp;
    ERROR_MSG( "close CSetGrp" )

	return OK;      
}

/*** DELETE-NOT-UPDATED ************************************************/

int DelNotUpdatedGruppen( char *error_msg )
{
	char *fun = "DelNotUpdatedGruppen";
	int i;

	exec sql begin declare section;
	char str[2048];
	char cUpd_Flag[2];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "upd_flag  " );
	strcat( str, "from " );
	strcat( str, outdatenbank );
	strcat( str, ":articlegroup " );
	strcat( str, "where upd_flag = '0' " );
	strcat( str, "for update " );

	exec sql prepare sel_grp from :str;
	ERROR_MSG( "prepare sel_grp" )
	exec sql declare CSelGrp cursor with hold for sel_grp;

	strcpy( str, "delete from " );
	strcat( str, outdatenbank );
	strcat( str, ":articlegroup " );
	strcat( str, "where current of CSelGrp " );
	
	exec sql prepare del_grp from :str;
	ERROR_MSG( "prepare del_grp" )

	exec sql open CSelGrp;
    ERROR_MSG( "open CSelGrp" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CSelGrp into :cUpd_Flag;
		if(NOTFOUND) break;
		ERROR_MSG( "fetch CSelGrp" )

		exec sql execute del_grp;
		ERROR_MSG( "execute del_grp" )

	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close CSelGrp;
    ERROR_MSG( "close CSelGrp" )

	return OK;      
}

/*** PREPARE-LESE-GRUPPEN ************************************************/

int PrepareLeseGruppen( char *error_msg )
{
	char *fun = "PrepareLeseGruppen";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, ZARTICLECATEGORY_PELISTE );
	strcat( str, " from  " );
	strcat( str, "carticlecategory " );

	exec sql prepare dec_artcat from :str;
	ERROR_MSG( "prepare dec_artcat" )
	exec sql declare Cselartcat cursor with hold for dec_artcat;
	
	return OK;      
}

/*** PREPARE-LADE-GRUPPEN ************************************************/

int PrepareLadeGruppen( char *error_msg )
{
	char *fun = "PrepareLadeGruppen";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	/* Select */

	strcpy(str, "select upd_flag from " );
	strcat( str, outdatenbank );
	strcat(str, ":articlegroup " );
	strcat( str, "where ARTICLENO = ? " );
	strcat( str, "and ARTCATEGORYNO = ? " );
	strcat( str, "for update " );
	   
	exec sql prepare sel_artgrp from :str;
	ERROR_MSG( "prepare sel_artgrp" )
	exec sql declare Cselartgrp cursor with hold for sel_artgrp;

	/* Update */

	strcpy( str, "update " );
	strcat( str, outdatenbank );
	strcat( str, ":articlegroup " );
	strcat( str, "set upd_flag = '1' " );
	strcat( str, "where current of Cselartgrp " );
	   
	exec sql prepare upd_artgrp from :str;
	ERROR_MSG( "prepare upd_artgrp" )

	/* Insert */

	strcpy( str, "insert into " );
	strcat( str, outdatenbank );
	strcat( str, ":articlegroup (" );
	strcat( str, ARTICLEGRP_PELISTE );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, '1' )" );
	   
	exec sql prepare ins_artgrp from :str;
	ERROR_MSG( "prepare ins_artgrp" )

	return OK;      
}

/*** LADE-GRUPPEN ********************************************************/

int LadeGruppen( char *error_msg )
{
	char *fun = "LadeGruppen";
	int  zaehler = 0;
	int i;
	int inscount;
	int updcount;

	exec sql begin declare section;
	char str[2048];
	int artikelnr;
	char cUpd_Flag[2];
	exec sql end declare section;

	inscount = 0;
	updcount = 0;

	strcpy(str, artcat.SQL_STATEMENT );
	   
	exec sql prepare sel_artzent from :str;
	ERROR_MSG( "prepare sel_artzent" )
	exec sql declare Cselartzent cursor with hold for sel_artzent;

	exec sql open Cselartzent;
	ERROR_MSG( "open Cselartzent" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for(;;)
	{
		exec sql fetch Cselartzent into :artikelnr;
		if(NOTFOUND) break;
		ERROR_MSG( "fetch Cselartzent" )

	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }
		exec sql open Cselartgrp using :artikelnr,:artcat.ARTCATEGORYNO;
		ERROR_MSG( "fetch Cselartgrp" )
		exec sql fetch Cselartgrp into :cUpd_Flag;
		if(NOTFOUND)
		{
			exec sql execute ins_artgrp using :artikelnr,:artcat.ARTCATEGORYNO;
			if(sqlca.sqlcode == -239)
			{
				sprintf(error_msg,"bereits ein Eintrag fuer PZN: %d vorhanden",artikelnr);
				PrintMsg( fun, error_msg, HINW, 0 );
				sprintf(error_msg,"Satz fuer Gruppe: '%s' nicht eingefuegt",artcat.NAME);
				PrintMsg( fun, error_msg, HINW, 0 );
			}
			else
			{
				ERROR_MSG( "execute ins_artgrp" )
			}
			inscount++;
		}
		else
		{
			exec sql execute upd_artgrp;
			ERROR_MSG( "execute upd_artgrp" )
			updcount++;
		}
	}

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	exec sql close Cselartzent;
	ERROR_MSG( "close Cselartzent" )
	exec sql free sel_artzent;
	ERROR_MSG( "free sel_artzent" )

	sprintf(error_msg,"fuer %d (%s) Saetze eingefuegt/geaendert: %d/%d"
		,artcat.ARTCATEGORYNO
		,artcat.NAME
		,inscount
		,updcount);
	PrintMsg( fun, error_msg, HINW, 0 );
	return OK;
}


/***** AFTER-LADE-GRUPPEN *********************************************/

int AfterLadeGruppen( char *error_msg )
{
	int  rc = OK;
	if ( ( rc = DelNotUpdatedGruppen( error_msg ) ) < 0 ) return rc;
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
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.18s %s %s\n",
		mld,
		99,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"setarticlecategory",
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

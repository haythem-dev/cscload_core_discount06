/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadrange"

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
#include "discountgrpmem.h"
#include "discountgrp.h"
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
struct N_DISCOUNTGRPMEM a,*pa;
struct N_DISCOUNTGRP g,*pg;
int sBranchno = 0;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main						( int, char ** );
void PrintMsg					( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo				( char *error_msg, char mld, int rc );
int StarteLadenRange			( char *error_msg);
int PrepareLoadTables			( char *error_msg);
int AfterLoadTables				( char *error_msg);
int PrepareLadeGrp				( char *error_msg);
int PrepareLeseGrp				( char *error_msg);
int PrepareLadeRange			( char *error_msg);
int PrepareLeseRange			( char *error_msg);
int LeseGrp						( char *error_msg);
int LadeGrp						( char *error_msg);
int LeseRange					( char *error_msg);
int LadeRange					( char *error_msg);
int DelNotUpdatedGrp			( char *error_msg);
int SetNotUpdatedGrp			( char *error_msg);
int DelNotUpdatedRange			( char *error_msg);
int SetNotUpdatedRange			( char *error_msg);
int AfterLadeGrp				( char *error_msg);
int AfterLadeRange				( char *error_msg);
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
   
	if ( ( rc = StarteLadenRange( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER SHORT-KKONDITIONEN ************************************/

int StarteLadenRange( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenRange";
   
	zaehlerIns = 0;
	zaehlerUpd = 0;

	exec sql open Cselcdiscgrp;
	ERROR_MSG( "open Cselcdiscgrp" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work01" )

	for ( ;; )
	{
		exec sql fetch Cselcdiscgrp into
			:g.DISCOUNTGRPNO,
			:g.DESCRIPTION,
			:g.DISCOUNTGRPTYPE,
			:g.CUSTOMERNO;
		ERROR_MSG( "fetch Cselcdiscgrp" )
		if(NOTFOUND) break;
		pg = &g;
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work01" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work02" )
        }

        if ( ( rc = LadeGrp( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
        else if ( explain == YES )
           if ( zaehler > 5000 ) break;   /* Nur 5000 Saetze verarbeiten */

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work02" )

	sprintf( error_msg, "%d grp-Saetze gelesen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );
	sprintf( error_msg, "%d/%d grp-Saetze geaendert/eingefuegt", zaehlerUpd,zaehlerIns );
	PrintMsg( fun, error_msg, HINW, OK );
   
	zaehler = 0;
	zaehlerIns = 0;
	zaehlerUpd = 0;
   
	exec sql open Cselcdiscgrpmem;
	ERROR_MSG( "open Cselcdiscgrpmem" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work11" )

	for ( ;; )
	{
		exec sql fetch Cselcdiscgrpmem into
			:a.DISCOUNTGRPNO,
			:a.ARTICLENO,
			:a.DISCOUNTCONDITION,
			:a.MANUFACTURERNO,
			:g.DISCOUNTGRPTYPE;
		ERROR_MSG( "fetch Cselcdiscgrpmem" )
		if(NOTFOUND) break;
		pa = &a;
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work11" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work12" )
        }

        if ( ( rc = LadeRange( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
        else if ( explain == YES )
           if ( zaehler > 5000 ) break;   /* Nur 5000 Saetze verarbeiten */

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work12" )

	sprintf( error_msg, "%d mem-Saetze gelesen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );
	sprintf( error_msg, "%d/%d mem-Saetze geaendert/eingefuegt", zaehlerUpd,zaehlerIns );
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
	if ( ( rc = SetNotUpdatedGrp(error_msg)) < 0) return rc;
	if ( ( rc = PrepareLeseGrp( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeGrp( error_msg ) ) < 0 ) return rc;
	if ( ( rc = SetNotUpdatedRange(error_msg)) < 0) return rc;
	if ( ( rc = PrepareLeseRange( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeRange( error_msg ) ) < 0 ) return rc;

	return OK;
}


/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeGrp(error_msg)) < 0) return rc;
	if ( (rc = AfterLadeRange(error_msg)) < 0) return rc;

	return OK;
}

/*** PREPARE-LESE-SHORT-KONDITIONEN ************************************************/

int PrepareLeseGrp( char *error_msg )
{
	char *fun = "PrepareLeseGrpRange";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "DISCOUNTGRPNO, " );
	strcat( str, "DESCRIPTION, " );
	strcat( str, "DISCOUNTGRPTYPE, " );
	strcat( str, "CUSTOMERNO " );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":cdiscgrp " );

	exec sql prepare dec_cdiscgrp from :str;
	ERROR_MSG( "prepare dec_cdiscgrp" )
	exec sql declare Cselcdiscgrp cursor with hold for dec_cdiscgrp;

	return OK;
}

/*** PREPARE-LADE-SHORT-KONDITIONEN ************************************************/

int PrepareLadeGrp( char *error_msg )
{
	char *fun = "PrepareLadeGrp";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into discountgrp (" );
	strcat( str, DISCOUNTGRP_PELISTE );
	strcat( str, ",updatesign " );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ? ) " );
	   
	exec sql prepare ins_discountgrp from :str;
	ERROR_MSG( "prepare ins_discountgrp" )

	strcpy(str, "update discountgrp " );
	strcat( str, " set " );
	strcat( str, DISCOUNTGRP_UPDLISTE );
	strcat( str, ", updatesign=?" );
	strcat( str, " where BRANCHNO=?" );
	strcat( str, " and DISCOUNTGRPNO=?" );
	   
	exec sql prepare upd_discountgrp from :str;
	ERROR_MSG( "prepare upd_discountgrp" )

	return OK;
}

/*** PREPARE-LESE-SHORT-KONDITIONEN ************************************************/

int PrepareLeseRange( char *error_msg )
{
	char *fun = "PrepareLeseRange";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "mem.DISCOUNTGRPNO, " );
	strcat( str, "mem.ARTICLENO, " );
	strcat( str, "mem.DISCOUNTCONDITION, " );
	strcat( str, "mem.MANUFACTURERNO, " );
	strcat( str, "grp.DISCOUNTGRPTYPE ");
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":cdiscgrpmem mem " );
	strcat( str, "inner join ");
	strcat( str, indatenbank);
	strcat( str, ":cdiscgrp grp ");
	strcat( str, "on mem.DISCOUNTGRPNO = grp.DISCOUNTGRPNO ");

	exec sql prepare dec_cdiscgrpmem from :str;
	ERROR_MSG( "prepare dec_cdiscgrpmem" )
	exec sql declare Cselcdiscgrpmem cursor with hold for dec_cdiscgrpmem;

	return OK;      
}

/*** PREPARE-LADE-SHORT-KONDITIONEN ************************************************/

int PrepareLadeRange( char *error_msg )
{
	char *fun = "PrepareLadeRange";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into discountgrpmem (" );
	strcat( str, DISCOUNTGRPMEM_PELISTE );
	strcat( str, ",updatesign " );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ? ) " );
	   
	exec sql prepare ins_discountgrpmem from :str;
	ERROR_MSG( "prepare ins_discountgrpmem" )

	strcpy(str, "update discountgrpmem " );
	strcat( str, " set " );
	strcat( str, DISCOUNTGRPMEM_UPDLISTE );
	strcat( str, ", updatesign=?" );
	strcat( str, " where BRANCHNO=?" );
	strcat( str, " and DISCOUNTGRPNO=?" );
	strcat( str, " and ARTICLENO=?" );
	strcat( str, " and MANUFACTURERNO=?" );
	   
	exec sql prepare upd_discountgrpmem from :str;
	ERROR_MSG( "prepare upd_discountgrpmem" )

	strcpy(str, "update artikellokal " );
	strcat( str, " set" );
	strcat( str, " kzrange = '1'" );
	strcat( str, " where FILIALNR=?" );
	strcat( str, " and ARTIKEL_NR=?" );
	   
	exec sql prepare upd_artikellokal from :str;
	ERROR_MSG( "prepare upd_artikellokal" )

	return OK;
}

/*** LADE-SHORT-KONDITIONEN ********************************************************/

int LadeGrp( char *error_msg )
{
	char *fun = "LadeGrp";

	pg->BRANCHNO = sBranchno;
	EXEC SQL EXECUTE upd_discountgrp using 
		:pg->BRANCHNO,
		:pg->DISCOUNTGRPNO,
		:pg->DESCRIPTION,
		:pg->DISCOUNTGRPTYPE,
		:pg->CUSTOMERNO,
		'1',
		:pg->BRANCHNO,
		:pg->DISCOUNTGRPNO;
	ERROR_MSG( "execute upd_discountgrp" )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		pg->BRANCHNO = sBranchno;
		EXEC SQL EXECUTE ins_discountgrp using
		:pg->BRANCHNO,
		:pg->DISCOUNTGRPNO,
		:pg->DESCRIPTION,
		:pg->DISCOUNTGRPTYPE,
		:pg->CUSTOMERNO,
		'1';
		ERROR_MSG( "execute ins_discountgrp" )
		zaehlerIns++;
	}
	else
	{
		zaehlerUpd++;
	}

	return OK;
}

/*** LADE-SHORT-KONDITIONEN ********************************************************/

int LadeRange( char *error_msg )
{
	char *fun = "LadeRange";

	pa->BRANCHNO = sBranchno;
	EXEC SQL EXECUTE upd_discountgrpmem using 
		:pa->BRANCHNO,
		:pa->DISCOUNTGRPNO,
		:pa->ARTICLENO,
		:pa->DISCOUNTCONDITION,
		:pa->MANUFACTURERNO,
		'1',
		:pa->BRANCHNO,
		:pa->DISCOUNTGRPNO,
		:pa->ARTICLENO,
		:pa->MANUFACTURERNO;
	ERROR_MSG( "execute upd_discountgrpmem" )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		pa->BRANCHNO = sBranchno;
		EXEC SQL EXECUTE ins_discountgrpmem using
		:pa->BRANCHNO,
		:pa->DISCOUNTGRPNO,
		:pa->ARTICLENO,
		:pa->DISCOUNTCONDITION,
		:pa->MANUFACTURERNO,
		'1';
		ERROR_MSG( "execute ins_discountgrpmem" )
		zaehlerIns++;
	}
	else
	{
		zaehlerUpd++;
	}

	if(pg->DISCOUNTGRPTYPE == 0)
	{
		EXEC SQL EXECUTE upd_artikellokal using 
			:pa->BRANCHNO,
			:pa->ARTICLENO;
		ERROR_MSG( "execute upd_artikellokal" )
	}
   
	return OK;
}

/***** AFTER-LADE-KONDITIONEN *********************************************/

int AfterLadeGrp( char *error_msg )
{
	int rc;
	if ( (rc = DelNotUpdatedGrp(error_msg)) < 0) return rc;
	return OK;
}

/***** AFTER-LADE-KONDITIONEN *********************************************/

int AfterLadeRange( char *error_msg )
{
	int rc;
	if ( (rc = DelNotUpdatedRange(error_msg)) < 0) return rc;
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
		"loadRange",
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

int SetNotUpdatedGrp( char *error_msg)
{
	char *fun = "SetNotUpdatedGrp";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select updatesign from discountgrp");
	strcat(str," where BRANCHNO = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_grpupd FROM :str;
	ERROR_MSG( "prepare sel_grpupd" )
	exec sql declare CGrpupd Cursor with hold for sel_grpupd;
	 
	strcpy( str, "update discountgrp set updatesign = '0' " );
	strcat( str, "where current of CGrpupd " );
	
	exec sql prepare set_grp from :str;
	ERROR_MSG( "prepare set_grp" )

	exec sql open CGrpupd using :sBranchno;
    ERROR_MSG( "open CGrpupd" )

    exec sql begin work;
	ERROR_MSG( "begin Work:" )
	for(comz=0 ;;comz++ )
	{
		if (comz%200 == 0)
		{
			exec sql commit work;
			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
			ERROR_MSG( "begin Work2:" )
		}
		exec sql fetch CGrpupd;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CGrpupd" )
		
		exec sql execute set_grp;
		ERROR_MSG( "execute set_grp" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work2:" )
	exec sql close CGrpupd ;
    ERROR_MSG( "close CGrpupd" )

	return OK;
}

int DelNotUpdatedGrp( char *error_msg)
{
	char *fun = "DelNotUpdatedGrp";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select updatesign from discountgrp ");
	strcat(str," where updatesign = '0'");
	strcat(str," and BRANCHNO = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_grp2 FROM :str;
	ERROR_MSG( "prepare sel_grp2" )
	exec sql declare DelGrp Cursor with hold for sel_grp2;
	 
	strcpy( str, "delete from discountgrp " );
	strcat( str, "where current of DelGrp " );
	
	exec sql prepare del_grp from :str;
	ERROR_MSG( "prepare del_grp" )

	exec sql open DelGrp using :sBranchno;
    ERROR_MSG( "open DelGrp" )

    exec sql begin work;
	ERROR_MSG( "begin Work:" )
	for(comz=0 ;;comz++ )
	{
		if (comz%200 == 0)
		{
			exec sql commit work;
			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
			ERROR_MSG( "begin Work2:" )
		}
		exec sql fetch DelGrp;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch DelGrp" )
		
		exec sql execute del_grp;
		ERROR_MSG( "execute del_grp" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work2:" )
	exec sql close DelGrp ;
    ERROR_MSG( "close DelGrp" )

	return OK;
}

int SetNotUpdatedRange( char *error_msg)
{
	char *fun = "SetNotUpdatedRange";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select updatesign from discountgrpmem");
	strcat(str," where BRANCHNO = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_rangeupd FROM :str;
	ERROR_MSG( "prepare sel_rangeupd" )
	exec sql declare CRangeupd Cursor with hold for sel_rangeupd;
	 
	strcpy( str, "update discountgrpmem set updatesign = '0' " );
	strcat( str, "where current of CRangeupd " );
	
	exec sql prepare set_range from :str;
	ERROR_MSG( "prepare set_range" )

	exec sql open CRangeupd using :sBranchno;
    ERROR_MSG( "open CRangeupd" )

    exec sql begin work;
	ERROR_MSG( "begin Work:" )
	for(comz=0 ;;comz++ )
	{
		if (comz%200 == 0)
		{
			exec sql commit work;
			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
			ERROR_MSG( "begin Work2:" )
		}
		exec sql fetch CRangeupd;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CRangeupd" )
		
		exec sql execute set_range;
		ERROR_MSG( "execute set_range" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work2:" )
	exec sql close CRangeupd ;
    ERROR_MSG( "close CRangeupd" )

	return OK;
}

int DelNotUpdatedRange( char *error_msg)
{
	char *fun = "DelNotUpdatedRange";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select updatesign from discountgrpmem ");
	strcat(str," where updatesign = '0'");
	strcat(str," and BRANCHNO = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_range2 FROM :str;
	ERROR_MSG( "prepare sel_range2" )
	exec sql declare DelRange Cursor with hold for sel_range2;
	 
	strcpy( str, "delete from discountgrpmem " );
	strcat( str, "where current of DelRange " );
	
	exec sql prepare del_range from :str;
	ERROR_MSG( "prepare del_range" )

	exec sql open DelRange using :sBranchno;
    ERROR_MSG( "open DelRange" )

    exec sql begin work;
	ERROR_MSG( "begin Work:" )
	for(comz=0 ;;comz++ )
	{
		if (comz%200 == 0)
		{
			exec sql commit work;
			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
			ERROR_MSG( "begin Work2:" )
		}
		exec sql fetch DelRange;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch DelRange" )
		
		exec sql execute del_range;
		ERROR_MSG( "execute del_range" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work2:" )
	exec sql close DelRange ;
    ERROR_MSG( "close DelRange" )

	return OK;
}

/***** ENDE *****************************************************************/

/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadreimport"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "artikelreimport.h"
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
long lArtikel_nr_bas;
long lArtikel_nr_verk;
char cVerk_art[2];
short sPrioritaet;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main						( int, char ** );
void PrintMsg					( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo				( char *error_msg, char mld, int rc );
int StarteLadenReimport			( char *error_msg);
int PrepareLoadTables			( char *error_msg);
int LoadTables					( char *error_msg);
int AfterLoadTables				( char *error_msg);
int PrepareLadeReimport			( char *error_msg);
int PrepareLeseReimport			( char *error_msg);
int LeseReimport				( char *error_msg);
int LadeReimport				( char *error_msg);
int AfterLadeReimport			( char *error_msg);
int CloseDatabase				( void );
int SetNotUpdatedReimport		( char *error_msg);
int DelNotUpdatedReimport		( char *error_msg);
int CheckArticle				( char *error_msg);

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
   
	if ( ( rc = StarteLadenReimport( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER REIMPORT-DATEN ************************************/

int StarteLadenReimport( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenReimport";
   
	exec sql open CselReimport;
	ERROR_MSG( "open CselReimport" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch CselReimport into
			:lArtikel_nr_bas,
			:lArtikel_nr_verk,
			:cVerk_art,
			:sPrioritaet;
		ERROR_MSG( "fetch CselReimport" )
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
	sprintf( error_msg, "%d Saetze geaendert", zaehlerUpd );
	PrintMsg( fun, error_msg, HINW, OK );
	sprintf( error_msg, "%d Saetze hinzugefuegt", zaehlerIns );
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
	if ( ( rc = PrepareLeseReimport( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeReimport( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;

	rc = LadeReimport(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeReimport(error_msg)) < 0) return rc;

	return OK;
}

/*** PREPARE-LESE-REIMPORT-NUMMEN ************************************************/

int PrepareLeseReimport( char *error_msg )
{
	char *fun = "PrepareLeseReimport";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "ARTIKEL_NR_BAS, " );
	strcat( str, "ARTIKEL_NR_VERK, " );
	strcat( str, "VERK_ART, " );
	strcat( str, "PRIORITAET " );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":zartverk " );

	exec sql prepare dec_Reimport from :str;
	ERROR_MSG( "prepare dec_Reimport" )
	exec sql declare CselReimport cursor with hold for dec_Reimport;

	return OK;      
}

/*** PREPARE-LADE-REIMPORT-NUMMERN ************************************************/

int PrepareLadeReimport( char *error_msg )
{
	int rc;
	char *fun = "PrepareLadeReimport";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	if((rc = SetNotUpdatedReimport( error_msg )) != 0) return rc;

	strcpy(str, "insert into ARTIKELREIMPORT (" );
	strcat( str, ARTIKELREIMPORT_PELISTE );
	strcat( str, " ) values " );
	strcat( str, "( 0, ?, ?, 1,	?, ? ) " );
	   
	exec sql prepare ins_artikelReimport from :str;
	ERROR_MSG( "prepare ins_artikelReimport" )

	strcpy( str, "select " );
	strcat( str, ARTIKELREIMPORT_PELISTE );
	strcat( str, " from ARTIKELREIMPORT" );
	strcat( str, " where FILIALNR = 0" );
	strcat( str, " and ARTIKEL_NR = ?" );
	strcat( str, " and ARTIKEL_NR_ALTERN = ?" );
	strcat( str, " for update " );

	exec sql prepare dec_artikelReimport from :str;
	ERROR_MSG( "prepare dec_artikelReimport" )
	exec sql declare CselartikelReimport cursor with hold for dec_artikelReimport;

	strcpy(str,"update artikelreimport set ");
 	strcat(str,"KZUPD = \"1\",");
 	strcat(str,"KZAKTIVPASSIV = ?,");
 	strcat(str,"REIHENFOLGE = ? ");
 	strcat(str,"where current of CselartikelReimport");

	EXEC SQL PREPARE upd_reimp FROM :str;
	ERROR_MSG( "prepare upd_reimp" )

	return OK;
}


/*** LADE-REIMPORT-NUMMERN ********************************************************/

int LadeReimport( char *error_msg )
{
	char *fun = "LadeReimport";

	long eanlen;
	
	exec sql begin declare section;
	struct ARTIKELREIMPORT Reimport;
	exec sql end declare section;

	if(CheckArticle( error_msg ) != OK) return OK;

	exec sql open CselartikelReimport using :lArtikel_nr_bas,:lArtikel_nr_verk;
	ERROR_MSG( "open CselartikelReimport" )

	exec sql fetch CselartikelReimport into :Reimport;
	ERROR_MSG( "fetch CselartikelReimport" )

	if ( NOTFOUND )
	{
		EXEC SQL EXECUTE ins_artikelReimport USING
			:lArtikel_nr_bas,
			:lArtikel_nr_verk,
			:cVerk_art,
			:sPrioritaet;
		ERROR_MSG( "insert artikelReimport" )
		zaehlerIns++;
	}
	else
	{
		EXEC SQL EXECUTE upd_reimp USING
			:cVerk_art,
			:sPrioritaet;
		ERROR_MSG( "update artikelReimport" )
		zaehlerUpd++;
	}
   
	return OK;
}


/***** AFTER-LADE-REIMPORT-NUMMERN *********************************************/

int AfterLadeReimport( char *error_msg )
{
	int rc;
	if ((rc = DelNotUpdatedReimport(error_msg)) != 0) return rc;
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
		"loadReimport",
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

int SetNotUpdatedReimport( char *error_msg)
{
	char *fun = "SetNotUpdatedReimport";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select kzupd from artikelreimport ");
	strcat(str," for update");

	EXEC SQL PREPARE sel_reimport FROM :str;
	ERROR_MSG( "prepare sel_reimport" )
	exec sql declare CReimport Cursor with hold for sel_reimport;
	 
	strcpy( str, "update artikelreimport set kzupd = '0' " );
	strcat( str, "where current of CReimport " );
	
	exec sql prepare set_reimport from :str;
	ERROR_MSG( "prepare set_reimport" )

	exec sql open CReimport ;
    ERROR_MSG( "open CReimport" )

    exec sql begin work;
	ERROR_MSG( "begin Work:" )
	for(comz=0 ;;comz++ )
	{
		if (comz%M_DURCHLAUF_COMMIT == 0)
		{
			exec sql commit work;
			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CReimport;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CReimport" )
		
		exec sql execute set_reimport;
		ERROR_MSG( "execute set_reimport" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work:" )
	exec sql close CReimport ;
    ERROR_MSG( "close CReimport" )

	return OK;
}

int DelNotUpdatedReimport( char *error_msg)
{
	char *fun = "DelNotUpdatedReimport";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select kzupd from artikelreimport ");
	strcat(str," where kzupd = '0'");
	strcat(str," for update");

	EXEC SQL PREPARE sel_reimport2 FROM :str;
	ERROR_MSG( "prepare sel_reimport2" )
	exec sql declare DelReimport Cursor with hold for sel_reimport2;
	 
	strcpy( str, "delete from artikelreimport " );
	strcat( str, "where current of DelReimport " );
	
	exec sql prepare del_reimport from :str;
	ERROR_MSG( "prepare del_reimport" )

	exec sql open DelReimport ;
    ERROR_MSG( "open DelReimport" )

    exec sql begin work;
	ERROR_MSG( "begin Work:" )
	for(comz=0 ;;comz++ )
	{
		if (comz%M_DURCHLAUF_COMMIT == 0)
		{
			exec sql commit work;
			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch DelReimport;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch DelReimport" )
		
		exec sql execute del_reimport;
		ERROR_MSG( "execute del_reimport" )
	}

	exec sql commit work;
	ERROR_MSG( "Commit Work:" )
	exec sql close DelReimport ;
    ERROR_MSG( "close DelReimport" )

	return OK;
}

int CheckArticle( char *error_msg)
{
	char *fun = "CheckArticle";

	EXEC SQL select artikel_nr from artikelzentral where artikel_nr = :lArtikel_nr_bas;
	if ( sqlca.sqlcode == 100 )
	{
		sprintf( error_msg, " Artikel_nr_bas.: %s aus zartverk nicht vorhanden",
				lArtikel_nr_bas);
		PrintMsg( fun, error_msg, HINW, -1 );
		return -1;
	}
	EXEC SQL select artikel_nr from artikelzentral where artikel_nr = :lArtikel_nr_verk;
	if ( sqlca.sqlcode == 100 )
	{
		sprintf( error_msg, " Artikel_nr_verk.: %s aus zartverk nicht vorhanden",
				lArtikel_nr_verk);
		PrintMsg( fun, error_msg, HINW, -1 );
		return -1;
	}
	return OK;
}

/***** ENDE *****************************************************************/

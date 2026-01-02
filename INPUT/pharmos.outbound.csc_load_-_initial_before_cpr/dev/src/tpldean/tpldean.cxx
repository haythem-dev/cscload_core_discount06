/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

static char *SCCSID="@(#)PRZ GmbH Stand: 1.0.3 $Header: /prj/df/unix/tpldean/tpldean.cxx 15    13.09.04 12:56 66aeimsc $";

#include <stdio.h>
#include <stdlib.h>
#include "artikelnummern.h"
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>                                     
#include <pplib/allg.h>

exec sql include sqlca;
exec sql include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define ERROR_MSG2(x,y)       if(sqlca.sqlcode<0) { \
                              sprintf(error_msg,"%s %d/%d bei PZN: %7.7s",x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1],y ); \
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
#define DATABASE           "pos2ch@db1_pos2_shm"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */

FILE *lokaldat;

exec sql begin declare section;
struct NUMMERN
{
	char PZN[7];
	char EAN[13];
};
exec sql end declare section;

struct NUMMERN nr;

static const int NUMMERN_LEN = sizeof(nr);
char log_file [300 + 1];
char  dateiname[L_TEXT];
int explain = NO;
static int filialnr = 99;
static int lPZN = 0;
static int ins = 0;

/***** DECLARATION **********************************************************/

int main					( int, char ** );
void PrintMsg				( char *fun, char *error_msg, char mld, int rc );
int StarteLadenDerNummern	( char *error_msg);
int PrepareLoadTables		(char *error_msg);
int LoadTables				(struct NUMMERN *nr, char *error_msg);
int AfterLoadTables			(char *error_msg);
int PrepareLadeArtikelnummern	(char *error_msg);
int LadeArtikelnummern		( struct NUMMERN *nr, char *error_msg);
int AfterLadeArtikelnummern	( char *error_msg);
int CloseDatabase			( void );

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
	char  start_msg[121];
	int   status = 0;

	exec sql begin declare section;
	char datenbank[60];
	exec sql end declare section;

	setbuf(stdout,0);

	sprintf(datenbank,"%s",DATABASE);

	strcpy(start_msg, "gestartet mit:");
	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-file" ) )
		{
			strcat(start_msg, " -file");
			i++;
			sprintf( dateiname, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
			status = 1;
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			strcat(start_msg, " -db");
			i++;
			sprintf( datenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-ex" ) )
		{
			strcat(start_msg, " -ex");
			explain = YES;
		}
		else
		{
			printf( "  usage: %s\n\t"
				" { -file dateiname <Dateiname> }\n\t"
				" { -db datenbankname <Datenbankname> }\n\t"
				" [ -ex <Explain> ]\n\t",
				argv[0] );
			return 1;
		}
	}
	if(status == 0)
	{
		printf( "  usage: %s\n\t"
			" { -file dateiname <Dateiname> }\n\t"
			" { -db datenbankname <Datenbankname> }\n\t",
			argv[0] );
		return 1;
	}
	if ( ( lokaldat = fopen( dateiname, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( "main ", "Ladedatei nicht vorhanden", FEHL, 0 );
		return -1;
	}
      

	if ( ( LOG_PATH = getenv("LOG_PATH")) == (char *)0 )
		strcpy( logpath, "." );
	else
		strcpy( logpath, LOG_PATH );
   
	sprintf( log_file, "%s/%s", logpath, LOG_FILE );

	PrintMsg( fun, start_msg, HINW, 0 );
	exec sql database :datenbank;
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
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	PrintMsg( fun, start_msg, HINW, rc );
	if ( ( rc = StarteLadenDerNummern( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	sprintf(error_msg,"Saetze bearbeitet: %d",ins);
	PrintMsg( fun, error_msg, HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER ARTIKEL-NUMMERN ************************************/

int StarteLadenDerNummern( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  idx;
	int  ende = NO;
	char huelse[20];
	char *fun = "StarteLadenDerNummern";

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	while ( !ende  )
	{
		if(fread( (struct NUMMERN*) &nr ,NUMMERN_LEN+1, 1 , lokaldat ) == 0)
			break;

	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }
            
        if ( ( rc = LoadTables( &nr, error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
        else if ( explain == YES )
           if ( zaehler > 100 ) break;   /* Nur 100 Saetze verarbeiten */

	}      /* ende while */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc;
	if ( ( rc = PrepareLadeArtikelnummern( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(struct NUMMERN *nr, char *error_msg)
{
	int rc = OK;
	/* neue Tabellen schreiben */
	if ( (rc = LadeArtikelnummern(nr, error_msg)) < 0) return rc;

	return OK;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc;
	if ( (rc = AfterLadeArtikelnummern(error_msg)) < 0) return rc;

	return OK;
}

/*** PREPARE-LADE-ARTIKELNUMMERN **************************************************/

int PrepareLadeArtikelnummern( char *error_msg )
{
	char *fun = "PrepareLadeArtikelnummern";
	int rc;
	
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;
	
	strcpy( str, "insert into artikelnummern (" );
	strcat( str, ARTIKELNUMMERN_PELISTE );          
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ? )" );

	exec sql prepare ins_nummern from :str;
	ERROR_MSG( "prepare ins_nummern" )
	
	strcpy( str, "select " );
	strcat( str, ARTIKELNUMMERN_PELISTE );
	strcat( str, " from artikelnummern" );
	strcat( str, " where ARTIKEL_NR = ?" );
	strcat( str, " for update " );

	exec sql prepare dec_artikelnummern from :str;
	ERROR_MSG( "prepare dec_artikelnummern" )
	exec sql declare Cupdartikelnummern cursor with hold for dec_artikelnummern;

	strcpy( str, "delete from artikelnummern " );
	strcat( str, "where current of Cupdartikelnummern" );

	exec sql prepare del_nummern from :str;
	ERROR_MSG( "prepare del_nummern" )

	return OK;   
}

/*** LADE-ARTIKEL-NUMMERN *********************************************************/

int LadeArtikelnummern( struct NUMMERN *nr, char *error_msg )
{
	char *fun = "LadeArtikelnummern";
	char huelse[40];
	int i;
	int rc;
	int eanlen;
	
	exec sql begin declare section;
	struct NUMMERN *a;
	struct ARTIKELNUMMERN ean;
	long lArtikel_nr;
	long lEan;
	exec sql end declare section;

	a = nr;

	sprintf(huelse,"%7.7s",a->PZN);
	lArtikel_nr = atol(huelse);
/* printf("Artikel_nr = %d\n",lArtikel_nr);fflush(stdout); */
	exec sql open Cupdartikelnummern using :lArtikel_nr;
	ERROR_MSG( "open Cupdartikelnummern" )

	sprintf(huelse,"%13.13s",a->EAN);
	AllgEntfSpaces(huelse);
	eanlen = strlen(huelse);

	for(;;)
	{
		exec sql fetch Cupdartikelnummern into :ean;
	    ERROR_MSG( "fetch Cupdartikelnummern" )

		if ( NOTFOUND ) break;
		AllgEntfSpaces(ean.EAN);
		if ( strlen(ean.EAN) == eanlen)
		{
			EXEC SQL EXECUTE del_nummern;
			ERROR_MSG( "execute del_nummern" ) 
		}
	}
	EXEC SQL EXECUTE ins_nummern USING
		:a->PZN,
		:a->EAN,
		:lArtikel_nr;
	ERROR_MSG( "insert artikelnummern" )
	ins++;

	return OK;
}

/***** AFTER-LADE-ARTIKEL-NUMMERN *********************************************/

int AfterLadeArtikelnummern( char *error_msg )
{
//	char *fun = "AfterLadeArtikelnummern";

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
   
/*	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) ); */
	env = getenv( "LOG_PATH" );
	if ( env == NULL )
		env = ".";
	sprintf( logFile, "%s/wws.log", env );

	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
		return;
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s %s\n",
		mld,
		filialnr,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"tpldean",
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


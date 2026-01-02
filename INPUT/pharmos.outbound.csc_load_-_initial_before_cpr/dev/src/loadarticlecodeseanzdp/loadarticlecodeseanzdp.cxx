/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/
#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadarticlecodeseanzdp"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "articlecodes.h"
#include <dirent.h>                                     
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>
#include "libtpld/dadedb.h"
#include "pplib/allg.h"

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
char ean[26];
long artikelnr;
char cSaveArticlecode[26];
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo( char *error_msg, char mld, int rc );
int StarteLadenArticlecodes   ( char *error_msg);
int PrepareLoadTables         ( char *error_msg);
int PrepareDelOldCodes        ( char *error_msg);
int PrepareDelCodesNotInEAN   ( char *error_msg);
int DelOldCodes               ( char *error_msg);
int DelCodesNotInEAN          ( char *error_msg);
int DelArticlecodes           ( char *error_msg);
int LoadTables                ( char *error_msg);
int AfterLoadTables           ( char *error_msg);
int PrepareDelArticlecodes    ( char *error_msg);
int PrepareLadeArticlecodes   ( char *error_msg);
int PrepareLeseArticlecodes   ( char *error_msg);
int LeseArticlecodes          ( char *error_msg);
int LadeArticlecodes          ( char *error_msg);
int AfterLadeArticlecodes     ( char *error_msg);
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
		return 7;

	if ( DelCodesNotInEAN( error_msg ) != OK )
		return 8;
   
	if ( DelOldCodes( error_msg ) != OK )
		return 9;
   
	if ( ( rc = StarteLadenArticlecodes( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 10; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER ARTIKEL-CODES AUS EAN************************************/

int StarteLadenArticlecodes( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenArticlecodes";

	strcpy(cSaveArticlecode," ");
   
	exec sql open Cselccodes;

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch Cselccodes into :ean,:artikelnr;
		ERROR_MSG( "fetch Cselccodes" )
		if(NOTFOUND) break;
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }

		AllgEntfSpaces(ean);
		if(strcmp(cSaveArticlecode,ean))
		{
			strcpy(cSaveArticlecode,ean);
	        if ( ( rc = DelArticlecodes( error_msg ) ) < 0 )
	        {
				PrintMsg( fun, error_msg, FEHL, ERROR );
				return ERROR;
			}
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
	if ( ( rc = PrepareDelArticlecodes( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLeseArticlecodes( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeArticlecodes( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareDelCodesNotInEAN( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareDelOldCodes( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;

	rc = LadeArticlecodes(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeArticlecodes(error_msg)) < 0) return rc;

	return OK;
}

/*** Prepare DEL-Articlecodes ************************************************/

int PrepareDelArticlecodes( char *error_msg )
{
	char *fun = "PrepareDelArticlecodes";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "articleno  " );
	strcat( str, "from " );
	strcat( str, "Articlecodes " );
	strcat( str, "where article_code = ? " );
	strcat( str, "and code_type = '13' " );
	strcat( str, "for update " );

	exec sql prepare del_codes from :str;
	ERROR_MSG( "prepare del_codes" )
	exec sql declare Cdelcodes cursor with hold for del_codes;

	strcpy( str, "delete from Articlecodes " );
	strcat( str, "where current of Cdelcodes " );
	
	exec sql prepare delete_codes from :str;
	ERROR_MSG( "prepare delete_codes" )

	return OK;
}

/*** Prepare DEL-Codes-Not-in-EAN ************************************************/

int PrepareDelCodesNotInEAN( char *error_msg )
{
	char *fun = "PrepareDelCodesNotInEAN";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "articleno  " );
	strcat( str, " from  " );
	strcat( str, "Articlecodes ksc " );
	strcat( str, "left join " );
	strcat( str, indatenbank );
	strcat( str, ":ean zdp " );
	strcat( str, "on zdp.ean_nr = ksc.article_code " );
	strcat( str, "where ksc.code_type = 13 " );
	strcat( str, "and zdp.artikel_nr is null " );
	strcat( str, "into temp t_notean " );

	exec sql prepare sel_codesnotean from :str;
	ERROR_MSG( "prepare sel_codesnotean" )

	exec sql execute sel_codesnotean;
	ERROR_MSG( "execute sel_codesnotean" )

	strcpy( str, "select " );
	strcat( str, "ksc.articleno  " );
	strcat( str, "from  " );
	strcat( str, "Articlecodes ksc " );
	strcat( str, "where ksc.articleno " );
	strcat( str, "in (select t.articleno " );
	strcat( str, "from t_notean t) " );
	strcat( str, "and ksc.code_type = 13 " );
	strcat( str, "for update " );

	exec sql prepare del_codesnotean from :str;
	ERROR_MSG( "prepare del_codesnotean" )
	exec sql declare Cdelcodesnotean cursor with hold for del_codesnotean;

	strcpy( str, "delete from Articlecodes " );
	strcat( str, "where current of Cdelcodesnotean " );
	
	exec sql prepare delete_codesnotean from :str;
	ERROR_MSG( "prepare delete_codesnotean" )

	return OK;
}

/*** Prepare DEL-OldCodes ************************************************/

int PrepareDelOldCodes( char *error_msg )
{
	char *fun = "PrepareDelOldCodes";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "articleno  " );
	strcat( str, "from " );
	strcat( str, "Articlecodes " );
	strcat( str, "where articleno not in (select artikel_nr from artikelzentral) " );
	strcat( str, "and code_type = '13' " );
	strcat( str, "for update " );

	exec sql prepare del_oldcodes from :str;
	ERROR_MSG( "prepare del_oldcodes" )
	exec sql declare Cdeloldcodes cursor with hold for del_oldcodes;

	strcpy( str, "delete from Articlecodes " );
	strcat( str, "where current of Cdeloldcodes " );
	
	exec sql prepare delete_oldcodes from :str;
	ERROR_MSG( "prepare delete_oldcodes" )

	return OK;
}

/*** PREPARE-LESE-Articlecodes ************************************************/

int PrepareLeseArticlecodes( char *error_msg )
{
	char *fun = "PrepareLeseArticlecodes";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "ean_nr,artikel_nr" );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":ean " );
	strcat( str, "where artikel_nr > 0 " );
	strcat( str, "order by artikel_nr " );

	exec sql prepare dec_ccodes from :str;
	ERROR_MSG( "prepare dec_ccodes" )
	exec sql declare Cselccodes cursor with hold for dec_ccodes;
	
	return OK;      
}

/*** PREPARE-LADE-Articlecodes ************************************************/

int PrepareLadeArticlecodes( char *error_msg )
{
	char *fun = "PrepareLadeArticlecodes";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into Articlecodes (" );
	strcat( str, ARTICLECODES_PELISTE );
	strcat( str, " ) values " );
	strcat( str, "( ?, '13', ?, '0' )" );
	   
	exec sql prepare ins_codes from :str;
	ERROR_MSG( "prepare ins_codes" )

	return OK;      
}

/*** Loeschen Articlecodes ********************************************************/

int DelArticlecodes( char *error_msg )
{
	char *fun = "DelArticlecodes";
	int i;

	exec sql begin declare section;
	char str[2048];
	long lArticleNo;
	exec sql end declare section;

	exec sql open Cdelcodes using :ean;
    ERROR_MSG( "open Cdelcodes" )

	for(;;)
	{
		exec sql fetch Cdelcodes into :lArticleNo;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Cdelcodes" )

		exec sql execute delete_codes;
		ERROR_MSG( "execute delete_codes" )

	}

	return OK;      
}

/*** Loeschen Articlecodes EAN not in ZDP.EAN ********************************************************/

int DelCodesNotInEAN( char *error_msg )
{
	int  zaehler = 0;
	int  rc = OK;
	char *fun = "DelCodesNotInEAN";
	int i;

	exec sql begin declare section;
	char str[2048];
	long lArticleNo;
	exec sql end declare section;

	exec sql open Cdelcodesnotean;
    ERROR_MSG( "open Cdelcodesnotean" )
          
    EXEC SQL begin work;
    ERROR_MSG( "Begin Work1" )

	for(;;)
	{
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work2" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work2" )
        }
		exec sql fetch Cdelcodesnotean into :lArticleNo;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Cdelcodesnotean" )

		exec sql execute delete_codesnotean;
		ERROR_MSG( "execute delete_codesnotean" )

	}
    EXEC SQL commit work;
    ERROR_MSG( "Commit Work1" )

	sprintf(str,"Eintraege geloescht: %d",zaehler);
	PrintMsg( fun, str, HINW, rc );

	return OK;      
}

/*** Loeschen alte Articlecodes ********************************************************/

int DelOldCodes( char *error_msg )
{
	int  zaehler = 0;
	int  rc = OK;
	char *fun = "DelOldCodes";
	int i;

	exec sql begin declare section;
	char str[2048];
	long lArticleNo;
	exec sql end declare section;

	exec sql open Cdeloldcodes;
    ERROR_MSG( "open Cdeloldcodes" )
          
    EXEC SQL begin work;
    ERROR_MSG( "Begin Work1" )

	for(;;)
	{
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work2" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work2" )
        }
		exec sql fetch Cdeloldcodes into :lArticleNo;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Cdeloldcodes" )

		exec sql execute delete_oldcodes;
		ERROR_MSG( "execute delete_oldcodes" )

	}
    EXEC SQL commit work;
    ERROR_MSG( "Commit Work1" )

	sprintf(str,"Eintraege geloescht: %d",zaehler);
	PrintMsg( fun, str, HINW, rc );

	return OK;      
}

/*** LADE-ARTICLECODES ********************************************************/

int LadeArticlecodes( char *error_msg )
{
	char *fun = "LadeArticlecodes";

	EXEC SQL EXECUTE ins_codes
		using
		:artikelnr,
		:ean
		;
	if(sqlca.sqlcode == -239 || sqlca.sqlcode == -268)
	{
/*		sprintf(error_msg,"Artikelnr: %d",artikelnr);
		PrintMsg( fun, error_msg, FEHL, -1 ); \
		sprintf(error_msg,"Artikelcode: %s",ean);
		PrintMsg( fun, error_msg, FEHL, -1 ); \
*/	}
	else
	{
		ERROR_MSG( "execute ins_codes" )
	}

	return OK;
}


/***** AFTER-LADE-Articlecodes *********************************************/

int AfterLadeArticlecodes( char *error_msg )
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
		"loadArticlecodeseanzdp",
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

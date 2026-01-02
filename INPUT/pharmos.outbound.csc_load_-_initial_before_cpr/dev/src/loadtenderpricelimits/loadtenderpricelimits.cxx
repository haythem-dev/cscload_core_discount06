/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/
#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadtenderpricelimits"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

//static char *SCCSID="@(#)PRZ GmbH Stand: 1.0.2 $Header: /prj/df/unix/loadtenderpricelimits/loadtenderpricelimits.cxx 50    29.04.04 16:01 66aeimsc $";

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
#include "nhifprices.h"
#include "registersprices.h"
#include "allg.h"
#include <dirent.h>
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm ); \
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
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 300                  /* nach n-saetzen commit  */


char log_file [300 + 1];
char dateiname[L_TEXT];
int zaehlerInsRegister = 0;		/* weil ich zu faul war Ronny */
int zaehlerInsNHIF = 0;			/* weil ich zu faul war Ronny */

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
registerspricesS regp;
nhifpricesS nhif;
long datum;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo( char *error_msg, char mld, int rc );
int StarteLadenPrices			( char *error_msg);
int PrepareLoadTables			( char *error_msg);
int DelRegistersPrices			( char *error_msg);
int DelNHIFPrices				( char *error_msg);
int AfterLoadTables				( char *error_msg);
int PrepareLeseRegistersPrices	( char *error_msg);
int PrepareLeseNHIFPrices		( char *error_msg);
int PrepareLadeRegistersPrices	( char *error_msg);
int PrepareLadeNHIFPrices		( char *error_msg);
int LeseRegistersPrices			( char *error_msg);
int LeseNHIFPrices				( char *error_msg);
int LadeRegistersPrices			( char *error_msg);
int LadeNHIFPrices				( char *error_msg);
int AfterLadeRegistersPrices	( char *error_msg);
int AfterLadeNHIFPrices			( char *error_msg);
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

	datum = AllgGetDate();

	exec sql database :outdatenbank;
	ERROR_MSG( "Fehler oeffnen DB" )

	exec sql set lock mode to wait 20;
	ERROR_MSG( "Set LockMode to Wait" )

	exec sql set isolation to dirty read;
	ERROR_MSG( "Set Isolation to Dirty Read" )

	PrintMsg( fun, start_msg, HINW, 0 );
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	if ( ( rc = StarteLadenPrices( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
/***** STARTE DAS LADEN DER PREISE ************************************/

int StarteLadenPrices( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenPrices";
	char cVerglRegister[26];
	char cVerglNHIF[26];
	cVerglRegister[0] = '\0';
	cVerglNHIF[0] = '\0';
   
	exec sql open CselRegistersPrices using :datum;
	ERROR_MSG( "open CselRegistersPrices" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work regp" )

	for ( ;; )
	{
		exec sql fetch CselRegistersPrices into
			:regp.MINISTRYPRODUCTCODE,
			:regp.DATEVALIDFROM,
			:regp.MAXWHOLESALEPRICE,
			:regp.REFERENCEPRICE;
		ERROR_MSG( "fetch CselRegistersPrices" )
		if(NOTFOUND) break;

		if (!strcmp(cVerglRegister, regp.MINISTRYPRODUCTCODE)) continue;
		if ( ( rc = LadeRegistersPrices( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
		strcpy(cVerglRegister, regp.MINISTRYPRODUCTCODE);
		zaehlerInsRegister++;

	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work regp intern" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work regp intern" )
        }

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work regp" )

	exec sql close CselRegistersPrices;
	ERROR_MSG("close CselRegistersPrices")

	sprintf( error_msg, "%d RegistersPrice-Saetze geladen", zaehlerInsRegister);
	PrintMsg( fun, error_msg, HINW, OK );

	exec sql open CselNHIFPrices using :datum;
	ERROR_MSG("open CselNHIFPrices")

	EXEC SQL begin work;
	ERROR_MSG("Begin Work NHIF")

		for (;; )
		{
			exec sql fetch CselNHIFPrices into
				:nhif.HEALTHFUNDCODEHOSPITAL,
				:nhif.DATEVALIDFROM,
				:nhif.NHIFPRICE;
			ERROR_MSG("fetch CselNHIFPrices")
				if (NOTFOUND) break;

			if (!strcmp(cVerglNHIF, nhif.HEALTHFUNDCODEHOSPITAL)) continue;
			if ((rc = LadeNHIFPrices(error_msg)) < 0)
			{
				PrintMsg(fun, error_msg, FEHL, ERROR);
				return ERROR;
			}
			strcpy(cVerglNHIF, nhif.HEALTHFUNDCODEHOSPITAL);
			zaehlerInsNHIF++;

			if (zaehler++ % M_DURCHLAUF_COMMIT == 0)
			{
				EXEC SQL commit work;
				ERROR_MSG("Commit Work NHIF intern")

				EXEC SQL begin work;
				ERROR_MSG("Begin Work NHIF intern")
			}

		}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG("Commit Work NHIF")

	exec sql close CselNHIFPrices;
	ERROR_MSG("close CselNHIFPrices")

	sprintf(error_msg, "%d NHIFPrice-Saetze geladen", zaehlerInsNHIF);
	PrintMsg(fun, error_msg, HINW, OK);

	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;

	if ( ( rc = DelRegistersPrices( error_msg ) ) < 0 ) return rc;
	if ( ( rc = DelNHIFPrices( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLeseRegistersPrices( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLeseNHIFPrices( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeRegistersPrices( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeNHIFPrices( error_msg ) ) < 0 ) return rc;

	return OK;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;

	if ( (rc = AfterLadeRegistersPrices(error_msg)) < 0) return rc;
	if ( (rc = AfterLadeNHIFPrices(error_msg)) < 0) return rc;

	return OK;
}

/*** DEL-RegistersPrices ************************************************/

int DelRegistersPrices( char *error_msg )
{
	char *fun = "DelRegistersPrices";
	int i;

	exec sql begin declare section;
	char str[2048];
	long lDatumVon;
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "DATEVALIDFROM  " );
	strcat( str, "from " );
	strcat( str, "registersprices " );
	strcat( str, "for update " );

	exec sql prepare del_registersprices from :str;
	ERROR_MSG( "prepare del_registersprices" )
	exec sql declare Cdelregistersprices cursor with hold for del_registersprices;

	strcpy( str, "delete from registersprices " );
	strcat( str, "where current of Cdelregistersprices " );
	
	exec sql prepare delete_registersprices from :str;
	ERROR_MSG( "prepare delete_registersprices" )

	exec sql open Cdelregistersprices;
    ERROR_MSG( "open Cdelregistersprices" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(i=1;;i++)
	{
		if (i % M_DURCHLAUF_COMMIT == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch Cdelregistersprices into :lDatumVon;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Cdelregistersprices" )

		exec sql execute delete_registersprices;
		ERROR_MSG( "execute delete_registersprices" )

	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close Cdelregistersprices;
    ERROR_MSG( "close Cdelregistersprices" )

	return OK;      
}

/*** DEL-NHIFPrices ************************************************/

int DelNHIFPrices( char *error_msg )
{
	char *fun = "DelNHIFPrices";
	int i;

	exec sql begin declare section;
	char str[2048];
	long lDatumVon;
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "DATEVALIDFROM  " );
	strcat( str, "from " );
	strcat( str, "nhifprices " );
	strcat( str, "for update " );

	exec sql prepare del_NHIFPrices from :str;
	ERROR_MSG( "prepare del_NHIFPrices" )
	exec sql declare CdelNHIFPrices cursor with hold for del_NHIFPrices;

	strcpy( str, "delete from nhifprices " );
	strcat( str, "where current of CdelNHIFPrices " );
	
	exec sql prepare delete_NHIFPrices from :str;
	ERROR_MSG( "prepare delete_NHIFPrices" )

	exec sql open CdelNHIFPrices;
    ERROR_MSG( "open CdelNHIFPrices" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(i=1;;i++)
	{
		if (i % M_DURCHLAUF_COMMIT == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CdelNHIFPrices into :lDatumVon;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CdelNHIFPrices" )

		exec sql execute delete_NHIFPrices;
		ERROR_MSG( "execute delete_NHIFPrices" )

	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close CdelNHIFPrices;
    ERROR_MSG( "close CdelNHIFPrices" )

	return OK;      
}

/*** PREPARE-LESE-RegistersPrices ************************************************/

int PrepareLeseRegistersPrices( char *error_msg )
{
	char *fun = "PrepareLeseRegistersPrices";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "ministryproductcode,  ");
	strcat( str, "datevalidfrom, ");
	strcat( str, "maxwholesaleprice, ");
	strcat( str, "referenceprice ");
	strcat( str, "from " );
	strcat( str, indatenbank );
	strcat( str, ":cregistersprices " );
	strcat( str, "where " );
	strcat( str, "datevalidfrom <= ? ");
	strcat( str, "order by ministryproductcode, datevalidfrom desc " );

	exec sql prepare dec_RegistersPrices from :str;
	ERROR_MSG( "prepare dec_RegistersPrices" )
	exec sql declare CselRegistersPrices cursor with hold for dec_RegistersPrices;
	
	return OK;      
}

/*** PREPARE-LESE-NHIFPrices ************************************************/

int PrepareLeseNHIFPrices( char *error_msg )
{
	char *fun = "PrepareLeseNHIFPrices";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "nhifcode, ");
	strcat( str, "datevalidfrom, ");
	strcat( str, "nhifprice ");
	strcat( str, "from " );
	strcat( str, indatenbank );
	strcat( str, ":cnhifprices " );
	strcat( str, "where " );
	strcat( str, "datevalidfrom <= ? ");
	strcat( str, "order by nhifcode, datevalidfrom desc ");

	exec sql prepare dec_NHIFPrices from :str;
	ERROR_MSG( "prepare dec_NHIFPrices" )
	exec sql declare CselNHIFPrices cursor with hold for dec_NHIFPrices;
	
	return OK;      
}

/*** PREPARE-LADE-RegistersPrices ************************************************/

int PrepareLadeRegistersPrices( char *error_msg )
{
	char *fun = "PrepareLadeRegistersPrices";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into registersprices (" );
	strcat( str, REGISTERSPRICES_PELISTE);
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ? )" );
	   
	exec sql prepare ins_RegistersPrices from :str;
	ERROR_MSG( "prepare ins_RegistersPrices" )

	return OK;      
}

/*** PREPARE-LADE-NHIFPrices ************************************************/

int PrepareLadeNHIFPrices( char *error_msg )
{
	char *fun = "PrepareLadeNHIFPrices";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into nhifprices (" );
	strcat( str, NHIFPRICES_PELISTE);
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ? )" );
	   
	exec sql prepare ins_NHIFPrices from :str;
	ERROR_MSG( "prepare ins_NHIFPrices" )

	return OK;      
}

/*** LADE-RegistersPrices ********************************************************/

int LadeRegistersPrices( char *error_msg )
{
	char *fun = "LadeRegistersPrices";

	exec sql begin declare section;
	registerspricesS *d;
	exec sql end declare section;

	d = &regp;

	EXEC SQL EXECUTE ins_RegistersPrices
		using
		REGISTERSPRICES_ZEIGER(d);
	ERROR_MSG( "execute ins_RegistersPrices" )

	return OK;
}

/*** LADE-NHIFPrices ********************************************************/

int LadeNHIFPrices( char *error_msg )
{
	char *fun = "LadeNHIFPrices";

	exec sql begin declare section;
	nhifpricesS *d;
	exec sql end declare section;

	d = &nhif;

	EXEC SQL EXECUTE ins_NHIFPrices
		using
		NHIFPRICES_ZEIGER(d);
	ERROR_MSG( "execute ins_NHIFPrices" )

	return OK;
}

/***** AFTER-LADE-RegistersPrices *********************************************/

int AfterLadeRegistersPrices( char *error_msg )
{
	return OK;
}

/***** AFTER-LADE-NHIFPrices *********************************************/

int AfterLadeNHIFPrices(char *error_msg)
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
		"loadtenderpricelimits",
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

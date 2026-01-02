/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"

#define PROJECTNAME	 "tpldvseauftrag"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "pplib/allg.h"
#include "libtpld/struct.h"
#include "kdauftragprolink.h"
#include "orderremarks.h"
#include "libtpld/define.h"
#include <dirent.h>                                     
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>
#include <libtpld/qsort.h>
#include <libtpld/hsystfkt.h>
#include <libtpld/vtcodum.h>

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
#define FILE_NOT_FOUND       1
#define WARNING             -2
#define HINW               'H'
#define FEHL               'F'
#define RIO_EOF            110
#define RIO_NOFIND         111
#define DATABASE        "phosix"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */
#define MAX_CH_ARTIKELNAME 26

FILE *vsedat;
char log_file [300 + 1];
int debug_enabled  = NO;
char  dateiname[L_TEXT];
int Serbia = NO;
int Austria = NO;
int Swiss = NO;
int Kroatia = NO;
int France = NO;
int Germany = NO;
int explain = NO;
int sichern = NO;
int zaehlerAuf = 0;     /* weil ich zu faul war alex */
int zaehlerPos = 0;     /* weil ich zu faul war alex */

/*struct O_VSEDAT {
		 char    DATUM[7];
		 char    KSCAUFNR[7];
		 char    VSEAUFNR[7];
		 char    RECHNR[7];
		 char    KSCPOSNR[5];
		 char    WANNNR[3];
       }; */

exec sql begin declare section;
long datum ;
long artikel_nr ;
char datenbank[60];
struct O_VSEDAT {
		 char    KSCAUFNR[7];
		 char    VSEAUFNR[7];
		 char    PREFIX[3];
		 char    RECHNR[7];
		 char    KSCPOSNR[5];
		 char    WANNNR[3];
		 char    DATUM[7];
		 char    ZEILENENDE[1];
			} aufdat;
/* struct O_VSEDAT aufdat; */
long kdauftragnr;
exec sql end declare section;

/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
int StarteLadenDerVSEAuftraege		( char *error_msg);
int PrepareLoadTables				( char *error_msg);
int AfterLoadTables					( char *error_msg);
int PrepareLadeAkdauftrag			( char *error_msg);
int PrepareLadeArticlepredelivery	( char *error_msg);
int PrepareLadeAkdauftragpos		( char *error_msg);
int PrepareLadeAkdauftragprolink	( char *error_msg);
int PrepareLadeAorderremarks		( char *error_msg);
int LadeAkdauftrag					( char *error_msg);
int LadeArticlepredelivery			( char *error_msg);
int LadeAkdauftragpos				( char *error_msg);
int LadeAkdauftragprolink			( char *error_msg);
int LadeAorderremarks				( char *error_msg);
int AfterLadeAkdauftrag				( char *error_msg);
int AfterLadeArticlepredelivery		( char *error_msg);
int AfterLadeAkdauftragpos			( char *error_msg);
int AfterLadeAkdauftragprolink		( char *error_msg);
int AfterLadeAorderremarks			( char *error_msg);
int CloseDatabase					( void );
int DeleteLeading0					(char *spStr);

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

	sprintf(datenbank,"%s",DATABASE);

	strcpy(start_msg, "gestartet mit:");
	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-dg" ) )
		{
			strcat(start_msg, " -dg");
			debug_enabled = YES;
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			strcat(start_msg, " -db");
			i++;
			sprintf( datenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-rs" ) )
		{
			strcat(start_msg, " -rs");
			Serbia = YES;
		}
		else if ( !strcmp( schalter, "-at" ) )
		{
			strcat(start_msg, " -at");
			Austria = YES;
		}
		else if ( !strcmp( schalter, "-ch" ) )
		{
			strcat(start_msg, " -ch");
			Swiss = YES;
		}
		else if ( !strcmp( schalter, "-hr" ) )
		{
			strcat(start_msg, " -hr");
			Kroatia = YES;
		}
		else if ( !strcmp( schalter, "-fr" ) )
		{
			strcat(start_msg, " -fr");
			France = YES;
		}
		else if ( !strcmp( schalter, "-de" ) )
		{
			strcat(start_msg, " -de");
			Germany = YES;
		}
		else if ( !strcmp( schalter, "-ex" ) )
		{
			strcat(start_msg, " -ex");
			explain = YES;
		}
		else if ( !strcmp( schalter, "-file" ) )
		{
			strcat(start_msg, " -file");
			i++;
			sprintf( dateiname, "%s", argv[i] );
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
				" { -db datenbankname <Datenbankname Ausgabe> }\n\t"
				" { -file Dateiname <Name der Datei mit den Aufträgen> }\n\t"
				" { -dg <Debugging> }\n\t"
				" [ -ex <Explain> ]\n\t",
				" [ -rs <Serbien> ]\n\t",
				argv[0] );
			return 1;
		}
	}

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
	PrintMsg( "tpldvseauftrag ", start_msg, HINW, 0 );
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  

	if ( ( vsedat = fopen( dateiname, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( "tpldvseauftrag ", "Ladedatei nicht vorhanden", FEHL, 0 );
		return -1;
	}
   
	if ( ( rc = StarteLadenDerVSEAuftraege( error_msg ) ) != 0 )
	{
		PrintMsg( "tpldvseauftrag ", "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( "tpldvseauftrag ", "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER AUFTRAEGE ************************************/

int StarteLadenDerVSEAuftraege( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenDerVSEAuftraege";
	char huelse[80];
   
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	kdauftragnr = 0;

	for ( ;; )
	{
		if(fread( (struct O_VSEDAT*) &aufdat ,sizeof(aufdat), 1 , vsedat ) == 0)
				break;
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }
        if ( zaehler % 1000 == 0 )
        {
           DEBUG_SECTION
           sprintf( error_msg, "%d Saetze geladen", zaehler );
           PrintMsg( fun, error_msg, HINW, OK );
           END_DEBUG_SECTION
        }

		sprintf(huelse,"%7.7s",aufdat.KSCAUFNR);
//		if( kdauftragnr != atol(aufdat.KSCAUFNR) )
		if( kdauftragnr != atol(huelse) )
		{
			kdauftragnr = atol(huelse);
			if ( ( rc = LadeAkdauftrag( error_msg ) ) < 0 )
			{
				PrintMsg( fun, error_msg, FEHL, ERROR );
				return ERROR;
			}
			if ( ( rc = LadeArticlepredelivery( error_msg ) ) < 0 )
			{
				PrintMsg( fun, error_msg, FEHL, ERROR );
				return ERROR;
			}
			if(Serbia == YES)
			{
				if ( ( rc = LadeAkdauftragprolink( error_msg ) ) < 0 )
				{
					PrintMsg( fun, error_msg, FEHL, ERROR );
					return ERROR;
				}
			}
		}
		if ( ( rc = LadeAorderremarks(error_msg)) < 0)
		{
			PrintMsg(fun, error_msg, FEHL, ERROR);
			return ERROR;
		}
		if ( ( rc = LadeAkdauftragpos( error_msg ) ) < 0 )
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
	sprintf( error_msg, "%d Auftraege geaendert", zaehlerAuf );
	PrintMsg( fun, error_msg, HINW, OK );
	sprintf( error_msg, "%d Positionen geaendert", zaehlerPos );
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
	if ( ( rc = PrepareLadeAkdauftrag( error_msg ) ) < 0 ) return rc;
	if(Serbia == YES)
	{
		if ( ( rc = PrepareLadeAkdauftragprolink( error_msg ) ) < 0 ) return rc;
	}
	if ( ( rc = PrepareLadeAorderremarks(error_msg)) < 0) return rc;
	if ( ( rc = PrepareLadeArticlepredelivery( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeAkdauftragpos( error_msg ) ) < 0 ) return rc;
	return OK;
}


/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeAkdauftrag(error_msg)) < 0) return rc;
	if(Serbia == YES)
	{
		if ( ( rc = AfterLadeAkdauftrag( error_msg ) ) < 0 ) return rc;
	}
	if ( (rc = AfterLadeAorderremarks(error_msg)) < 0) return rc;
	if ( (rc = AfterLadeArticlepredelivery(error_msg)) < 0) return rc;
	if ( (rc = AfterLadeAkdauftragpos(error_msg)) < 0) return rc;
	return OK;
}

/*** PREPARE-LADE-AKDAUFTRAG ************************************************/

int PrepareLadeAkdauftrag( char *error_msg )
{
	char *fun = "PrepareLadeAkdauftrag";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "update akdauftrag " );
	strcat( str, "set rechnungnr = ? " );
	strcat( str, ", invoicenumber = ? " );
	strcat( str, "where datum = ? " );
	strcat( str, "and kdauftragnr = ?" );
	   
	exec sql prepare upd_akdauftrag from :str;
	ERROR_MSG( "prepare upd_akdauftrag" )
 
	return OK;      
}

/*** PREPARE-LADE-AKDAUFTRAG-PROLINK ************************************************/

int PrepareLadeAkdauftragprolink( char *error_msg )
{
	char *fun = "PrepareLadeAkdauftragprolink";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPROLINK_PELISTE );
	strcat( str, " from akdauftragprolink " );
	strcat( str, "where datum = ? " );
	strcat( str, "and kdauftragnr = ?" );
	strcat( str, "for update " );
	   
	exec sql prepare sel_akdauftragpl from :str;
	ERROR_MSG( "prepare sel_akdauftragpl" )
	exec sql declare Cselakdauftragpl cursor with hold for sel_akdauftragpl;
 
	strcpy( str, "update akdauftragprolink " );
	strcat( str, "set invoicenumberpro = ? " );
	strcat( str, ",invoicenumber = ? " );
	strcat( str, "where current of Cselakdauftragpl " );
	   
	exec sql prepare upd_akdauftragpl from :str;
	ERROR_MSG( "prepare upd_akdauftragpl" )

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPROLINK_PELISTE );
	strcat( str, " from akdauftragprolink " );
	strcat( str, "where datum = ? " );
	strcat( str, "and kdauftragnrpro = ?" );
	strcat( str, "for update " );
	   
	exec sql prepare sel_akdauftragplpro from :str;
	ERROR_MSG( "prepare sel_akdauftragplpro" )
	exec sql declare Cselakdauftragplpro cursor with hold for sel_akdauftragplpro;
 
	strcpy( str, "update akdauftragprolink " );
	strcat( str, "set invoicenumberpro = ? " );
	strcat( str, ",invoicenumber = ? " );
	strcat( str, "where current of Cselakdauftragplpro " );
	   
	exec sql prepare upd_akdauftragplpro from :str;
	ERROR_MSG( "prepare upd_akdauftragplpro" )
 
	return OK;      
}

/*** PREPARE-LADE-ORDERREMARKS ************************************************/

int PrepareLadeAorderremarks(char *error_msg)
{
	char *fun = "PrepareLadeAorderremarks";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "select 1 from aorderremarks ");
	strcat(str, "where datum = ? ");
	strcat(str, "and CSCORDERNO = ? ");
	strcat(str, "and POSITIONNO = 0 ");
	strcat(str, "and REMARKTYPE = 4 ");
	strcat(str, "and TEXTNUMBER = 0 ");

	exec sql prepare sel_remarks from : str;
	ERROR_MSG("prepare sel_remarks")

	strcpy(str, "insert into aorderremarks (datum,");
	strcat(str, ORDERREMARKS_PELISTE);
	strcat(str, ") values (");
	strcat(str, "?,?,0,4,0,?)");

	exec sql prepare ins_remarks from : str;
	ERROR_MSG("prepare ins_remarks")

	return OK;
}

/*** PREPARE-LADE-ARTICLEPREDELIVERY ************************************************/

int PrepareLadeArticlepredelivery( char *error_msg )
{
	char *fun = "PrepareLadeArticlepredelivery";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select * from articlepredelivery " );
	strcat( str, "where date = ? " );
	strcat( str, "and orderno = ? " );
	strcat( str, "for update " );
	   
	exec sql prepare sel_apd from :str;
	ERROR_MSG( "prepare sel_apd" )
	   
	exec sql declare Cselapd cursor for sel_apd;

	strcpy( str, "update articlepredelivery " );
	strcat( str, "set invoiceno = ? " );
	strcat( str, "where current of Cselapd " );
	   
	exec sql prepare upd_apd from :str;
	ERROR_MSG( "prepare upd_apd" )
 
	return OK;      
}

/*** PREPARE-LADE-AKDAUFTRAGPOS ************************************************/

int PrepareLadeAkdauftragpos( char *error_msg )
{
	char *fun = "PrepareLadeAkdauftragpos";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "update akdauftragpos " );
	strcat( str, "set wannennr = ?, " );
	strcat( str, "kobehaeltnr = ? " );
	strcat( str, "where datum = ? " );
	strcat( str, "and kdauftragnr = ? " );
	strcat( str, "and posnr = ?" );
	   
	exec sql prepare upd_akdauftragpos from :str;
	ERROR_MSG( "prepare upd_akdauftragpos" )
 
	return OK;      
}

/*** LADE-AKDAUFTRAG *********************************************************/

int LadeAkdauftrag(char *error_msg)
{
	int rc;
	char *fun = "LadeAkdauftrag";

	exec sql begin declare section;
	long ldatum;
	char invoice[11];
	exec sql end declare section;

	if (Serbia == YES)
	{
		sprintf(invoice, "%7.7s%3.3s", aufdat.RECHNR, aufdat.PREFIX);	//in RS steht in Prefix ein Suffix
	}
	else
	{
		sprintf(invoice, "%10.10s", aufdat.PREFIX);
	}
	DeleteLeading0(invoice);

	ldatum = atol(aufdat.DATUM) + 20000000;
	exec sql execute upd_akdauftrag using
		:aufdat.RECHNR,
		:invoice,
		:ldatum,
		:aufdat.KSCAUFNR;
	ERROR_MSG( "execute upd_akdauftrag" )

	if(sqlca.sqlerrd[2] > 0)
		zaehlerAuf++;

	return 0;
}

/*** LADE-AKDAUFTRAG-PROLINK *********************************************************/

int LadeAkdauftragprolink(char *error_msg)
{
	int rc;
	char *fun = "LadeAkdauftragprolink";

	exec sql begin declare section;
	long ldatum;
	char invoice[11];
	kdauftragprolinkS pl;
	exec sql end declare section;

	if (Serbia == YES)
	{
		sprintf(invoice, "%7.7s%3.3s", aufdat.RECHNR, aufdat.PREFIX);	//in RS steht in Prefix ein Suffix
	}
	else
	{
		sprintf(invoice, "%10.10s", aufdat.PREFIX);
	}
	DeleteLeading0(invoice);

	ldatum = atol(aufdat.DATUM) + 20000000;

	exec sql open Cselakdauftragpl using
		:ldatum,
		:aufdat.KSCAUFNR;
	ERROR_MSG( "open Cselakdauftragpl" )

	exec sql fetch Cselakdauftragpl into :pl;
	ERROR_MSG( "fetch Cselakdauftragpl" )

	if ( sqlca.sqlcode == 100 )
	{
		exec sql open Cselakdauftragplpro using
			:ldatum,
			:aufdat.KSCAUFNR;
		ERROR_MSG( "open Cselakdauftragplpro" )

		exec sql fetch Cselakdauftragplpro into :pl;
		ERROR_MSG( "fetch Cselakdauftragplpro" )

		if ( sqlca.sqlcode == 100 ) return 0;

		exec sql execute upd_akdauftragplpro using
			:invoice,
			:pl.INVOICENUMBER;
		ERROR_MSG( "execute upd_akdauftragplpro" )
	}
	else
	{
		if(pl.KDAUFTRAGNR == pl.KDAUFTRAGNRPRO)	/* Proformaauftrag */
		{
			exec sql execute upd_akdauftragpl using
				:invoice,
				:pl.INVOICENUMBER;
			ERROR_MSG( "execute upd_akdauftragpl" )
		}
		else
		{
			exec sql execute upd_akdauftragpl using
				:pl.INVOICENUMBERPRO,
				:invoice;
			ERROR_MSG( "execute upd_akdauftragpl" )
	
			exec sql open Cselakdauftragplpro using
				:pl.DATEPROFORMA,
				:pl.KDAUFTRAGNRPRO;
			ERROR_MSG( "open Cselakdauftragplpro" )		
	
			exec sql fetch Cselakdauftragplpro into :pl;
			ERROR_MSG( "fetch Cselakdauftragplpro" )

			if ( sqlca.sqlcode == 100 ) return 0;

			exec sql execute upd_akdauftragplpro using
				:pl.INVOICENUMBERPRO,
				:invoice;
			ERROR_MSG( "execute upd_akdauftragplpro" )
		}
	}

	return 0;
}

/*** LADE-ORDERREMARKS *********************************************************/

int LadeAorderremarks(char *error_msg)
{
	int rc;
	char *fun = "LadeAorderremarks";

	exec sql begin declare section;
	long ldatum;
	char invoice[11];
	exec sql end declare section;

	if (Serbia == YES)
	{
		sprintf(invoice, "%7.7s%3.3s", aufdat.RECHNR, aufdat.PREFIX);	//in RS steht in Prefix ein Suffix
	}
	else
	{
		sprintf(invoice, "%10.10s", aufdat.PREFIX);
	}
	DeleteLeading0(invoice);

	ldatum = atol(aufdat.DATUM) + 20000000;
	exec sql execute sel_remarks using :ldatum, :aufdat.KSCAUFNR;

	ERROR_MSG("select Aorderremarks")
	if (sqlca.sqlcode == 0) return 0;	//Satz bereits vorhanden

	exec sql execute ins_remarks using :ldatum, :aufdat.KSCAUFNR, :invoice;

	ERROR_MSG( "insert Aorderremarks" )

	return 0;
}

/*** LADE-ARTICLEPREDELIVERY *********************************************************/

int LadeArticlepredelivery(char *error_msg)
{
	int rc;
	char *fun = "LadeArticlepredelivery";

	exec sql begin declare section;
	long ldatum;
	exec sql end declare section;

	ldatum = atol(aufdat.DATUM) + 20000000;
	exec sql open Cselapd using :ldatum, : aufdat.KSCAUFNR;
	ERROR_MSG("open Cselapd")
		for (;;)
		{
			exec sql fetch Cselapd;
			if (sqlca.sqlcode == 100) break;
			ERROR_MSG("fetch CKunde")

				exec sql execute upd_apd using
				:aufdat.RECHNR;
			ERROR_MSG("execute upd_apd")
		}

	return 0;
}

/*** LADE-AKDAUFTRAGPOS *********************************************************/

int LadeAkdauftragpos(char *error_msg)
{
	int rc;
	char *fun = "LadeAkdauftragpos";

	exec sql begin declare section;
	long ldatum;
	exec sql end declare section;

	ldatum = atol(aufdat.DATUM) + 20000000;
	exec sql execute upd_akdauftragpos using
		:aufdat.WANNNR,
		:aufdat.WANNNR,
		:ldatum,
		:aufdat.KSCAUFNR,
		:aufdat.KSCPOSNR;
	ERROR_MSG( "execute upd_akdauftragpos" )

	if(sqlca.sqlerrd[2] > 0)
		zaehlerPos++;

	return 0;
}

/***** AFTER-LADE-AKDAUFTRAG *********************************************/

int AfterLadeAkdauftrag( char *error_msg )
{
	return OK;
}

/***** AFTER-LADE-AKDAUFTRAG *********************************************/

int AfterLadeAkdauftragprolink( char *error_msg )
{
	return OK;
}

/***** AFTER-LADE-AORDERREMARKS *********************************************/

int AfterLadeAorderremarks(char *error_msg)
{
	return OK;
}

/***** AFTER-LADE-ARTICLEPREDELIVERY *********************************************/

int AfterLadeArticlepredelivery( char *error_msg )
{
	return OK;
}

/***** AFTER-LADE-AKDAUFTRAGPOS *********************************************/

int AfterLadeAkdauftragpos( char *error_msg )
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
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.14s %s %s\n",
		mld,
		99,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"tpldvseauftrag",
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


/***** Entferne fuehrende 0en *******************************************************/

int DeleteLeading0(char *spStr)
{
	int i;
	char buffer[100];
	memset(buffer, ' ', 100);
	int iEnd = strlen(spStr);
	for (i = 0; i < iEnd; i++)
	{
		if (spStr[i] != '0') break;
	}
	strncpy(buffer, spStr + i, iEnd - i);
	strncpy(spStr, buffer, iEnd);
	return i;
}

/***** ENDE *****************************************************************/



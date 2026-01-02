/*************************************************************************/
/*						                                                 */
/*	Quelle  : loadrebates.ec									         */
/*	Autor   : Ronald Imschweiler                                         */
/*	erstellt: 24.07.08                                                   */
/*	Aufgabe	: laden Rabatte in alt-Tabellen					             */
/*						                                                 */
/*************************************************************************/

/*** VERSION *************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadrebates"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/*** INCLUDE **************************************************************/

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "lddiscount.h"
#include "validdiscount.h"
#include "artnat.h"
#include "pplib/allg.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*** DEFINE ***************************************************************/

#define MAX_ENTRIES  20				  
#define YES           1
#define NO            0
#define ERROR   	 -1
#define HINW         'H'
#define FEHL         'F'
#define TIME_P        0
#define TIME_N        1
#define OK			  0
#define MAX_BYTE     MAX_ENTRIES * 513
#define NOTFOUND           sqlca.sqlcode == SQLNOTFOUND
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */

/*** STRUCTS ***************************************************************/


/*** GLOBALS ***************************************************************/

static char error_msg[81];
static char logFile[301];
exec sql begin declare section;
	char str[2048];
	long lDatum;
    short sBranchno = 0;
	lddiscountS discount;
	struct ARTIKELNATRA natra;
	validdiscountS valid;
exec sql end declare section;
int  zaehler = 1;
int  countnetto = 0;
int  countvalid = 0;
int  countnatra = 0;

/*** MACROS ***************************************************************/

#define ERROR_MSG2(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               exit (1); }

/*** DECLARATION **********************************************************/

int main( int argc, char **argv );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
int LadeKonditionen				( char *error_msg);
int PrepareLoadTables			( char *error_msg);
int DelNatra					( char *error_msg);
int DelValid					( char *error_msg);
int DelNetto					( char *error_msg);
int AfterLoadTables				( char *error_msg);
int PrepareLadeNatra		    ( char *error_msg);
int PrepareLadeValid		    ( char *error_msg);
int PrepareLadeNetto		    ( char *error_msg);
int PrepareLeseKonditionen		( char *error_msg);
int LadeNatra					( char *error_msg);
int LadeNetto					( char *error_msg);
int LadeValid					( char *error_msg);
int AfterLadeNatra				( char *error_msg);
int AfterLadeValid				( char *error_msg);
int AfterLadeNetto				( char *error_msg);
int CloseDatabase( void );

/*** FUNCTION: MAIN *******************************************************/

int main( int argc, char **argv )
{
	char *fun = "Main";
	int  i,rc;
	int  skip;  
	char *argm;
    exec sql begin declare section;
    char Database[80];
    exec sql end declare section;

	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) );
	sprintf( Database, "%s", (char *)getenv( "DATABASE" ) );

	skip = NO;
	for ( i = 1; i < argc; i++ )
	{
		argm = argv[i];
		if ( skip )
		{
			skip = NO;
			continue;
		}
		else if ( !strcmp( argm, "-vz" ) )
		{
			sBranchno = atoi( argv[i + 1] );
			skip = YES;
		}
		else if ( !strcmp( argm, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
		else
		{
			skip = ERROR;
			break;
		}
	}                                            
	 
	if ( skip == ERROR || sBranchno == 0)
	{
		printf( "  usage: %s\n\t"
			" [ -vz <Filialnr> ]\n", argv[0] );
		return ERROR;
	}
	
	EXEC SQL database :Database;
	ERROR_MSG2( "database: ");
	EXEC SQL set lock mode to wait 20;
	ERROR_MSG2( "lock: ");
	EXEC SQL set isolation to dirty read;
	ERROR_MSG2( "set iso: ");

	lDatum = AllgGetDate();
	
	sprintf( error_msg, "%s wurde gestartet", argv[0] );
	PrintMsg( fun, error_msg, HINW, -1 );
	
	if ( PrepareLoadTables( error_msg ) != OK )
		return 7;  
   
	if ( ( rc = LadeKonditionen( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 8; 
	}
	
	if ( AfterLoadTables( error_msg ) != OK )
		return 9;  
	
	sprintf( error_msg, "Saetze gelesen %d", zaehler-1 );
	PrintMsg( fun	, error_msg, HINW, -1 );
	sprintf( error_msg, "Saetze eingefuegt (Netto/Natra/Valid) %d/%d/%d",
			countnetto,
			countnatra,
			countvalid);
	PrintMsg( fun	, error_msg, HINW, -1 );
	sprintf( error_msg, "%s wurde beendet", argv[0] );
	PrintMsg( fun	, error_msg, HINW, -1 );
	
	return 0;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;
	if ( ( rc = DelNatra( error_msg ) ) < 0 ) return rc;
	if ( ( rc = DelValid( error_msg ) ) < 0 ) return rc;
	if ( ( rc = DelNetto( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLeseKonditionen( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeNatra( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeValid( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeNetto( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LadeKonditionen(char *error_msg)
{
	char *fun = "LadeKonditionen";
	int rc = OK;

	exec sql open Cseldiscount using :sBranchno,:lDatum,:lDatum;

	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch Cseldiscount into :discount;
		ERROR_MSG2( "fetch Cseldiscount" )
		if(NOTFOUND) break;
		if(discount.ARTICLENO == 0) continue;

	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG2( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG2( "Begin Work" )
        }
		if(discount.FIXEDPRICE != 0)
		{
			if ( ( rc = LadeNetto( error_msg ) ) < 0 ) return rc;
		}
		else if(discount.DISCOUNTQTY != 0)
		{
			if ( ( rc = LadeNatra( error_msg ) ) < 0 ) return rc;
		}
		else
		{
			if ( ( rc = LadeValid( error_msg ) ) < 0 ) return rc;
		}
	}

	return rc;
}

int LadeNatra( char *error_msg)
{
	char *fun = "LadeNatra";
	
	EXEC SQL EXECUTE ins_natra
		using
		:discount.ARTICLENO,
		:discount.DISCOUNTSPEC,
		:discount.DATEFROM,
		:discount.DATETO,
		:discount.DISCOUNTTYPE,
		:discount.BASEQTY,
		:discount.DISCOUNTQTY,
		:discount.BRANCHNO,
		:discount.INTERNALDISCOUNT,
		:discount.PHARMACYGROUPID,
		:discount.CUSTOMERNO
		;

	if(SQLCODE == -239)
	{
		return OK;
	}
	ERROR_MSG2( "execute ins_natra" )

	countnatra++;

	return OK;
}

int LadeValid( char *error_msg)
{
	char *fun = "LadeValid";

	if (discount.DISCOUNTSPEC != 0) return OK;	//nur Prozentrabatte

	EXEC SQL EXECUTE ins_valid
		using
		:discount.BRANCHNO,
		:discount.ARTICLENO,
		:discount.PHARMACYGROUPID,
		:discount.DATEFROM,
		:discount.DATETO,
		'2',
		:discount.BASEQTY,
		:discount.DISCOUNTVALUEPCT,
		:discount.DISCOUNTTYPE,
		:discount.DISCOUNTSPEC,
		:discount.CUSTOMERNO
		;
	if(SQLCODE == -239)
	{
		return OK;
	}
	ERROR_MSG2( "execute ins_valid" )

	countvalid++;

	return OK;
}

int LadeNetto( char *error_msg)
{
	char *fun = "LadeNetto";
	
	EXEC SQL EXECUTE ins_netto
		using
		:discount.ARTICLENO,
		:discount.DATEFROM,
		:discount.DATETO,
		:discount.DISCOUNTSPEC,
		:discount.BASEQTY,
		:discount.FIXEDPRICE,
		:discount.BRANCHNO,
		:discount.CUSTOMERNO
		;
	if(SQLCODE == -239)
	{
		return OK;
	}
	ERROR_MSG2( "execute ins_netto" )

	countnetto++;

	return OK;
}


int AfterLoadTables( char *error_msg)
{
	int rc = OK;

	if ( (rc = AfterLadeNatra(error_msg)) < 0) return rc;
	if ( (rc = AfterLadeValid(error_msg)) < 0) return rc;
	if ( (rc = AfterLadeNetto(error_msg)) < 0) return rc;

	return OK;
}

int DelNatra( char *error_msg)
{
	char *fun = "DelNatra";
	int i;

	exec sql begin declare section;
	long lArticleNo;
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "natrastaffelnr  " );
	strcat( str, "from " );
	strcat( str, "artikelnatra " );
	strcat( str, "where vertriebszentrumnr = ? " );
	strcat( str, "for update " );

	exec sql prepare del_natra from :str;
	ERROR_MSG2( "prepare del_natra" )
	exec sql declare Cdelnatra cursor with hold for del_natra;

	strcpy( str, "delete from artikelnatra " );
	strcat( str, "where current of Cdelnatra " );
	
	exec sql prepare delete_natra from :str;
	ERROR_MSG2( "prepare delete_natra" )

	exec sql open Cdelnatra using :sBranchno;
    ERROR_MSG2( "open Cdelnatra" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Cdelnatra into :lArticleNo;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Cdelnatra" )

		exec sql execute delete_natra;
		ERROR_MSG2( "execute delete_natra" )

	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Cdelnatra;
    ERROR_MSG2( "close Cdelnatra" )

	return OK;
}

int DelValid( char *error_msg)
{
	char *fun = "DelValid";
	int i;

	exec sql begin declare section;
	long lArticleNo;
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "articleno  " );
	strcat( str, "from " );
	strcat( str, "validdiscountinfo " );
	strcat( str, "where branchno = ? " );
	strcat(str, "and typeofdiscount != '3' ");
//	strcat( str, "and typeofdiscount not in ('2','3') " );
	strcat( str, "for update " );

	exec sql prepare del_valid from :str;
	ERROR_MSG2( "prepare del_valid" )
	exec sql declare Cdelvalid cursor with hold for del_valid;

	strcpy( str, "delete from validdiscountinfo " );
	strcat( str, "where current of Cdelvalid " );
	
	exec sql prepare delete_valid from :str;
	ERROR_MSG2( "prepare delete_valid" )

	exec sql open Cdelvalid using :sBranchno;
    ERROR_MSG2( "open Cdelvalid" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Cdelvalid into :lArticleNo;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Cdelvalid" )

		exec sql execute delete_valid;
		ERROR_MSG2( "execute delete_valid" )

	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Cdelvalid;
    ERROR_MSG2( "close Cdelvalid" )

	return OK;
}

int DelNetto( char *error_msg)
{
	char *fun = "DelNetto";
	int i;

	exec sql begin declare section;
	long lArticleNo;
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "artikel_nr  " );
	strcat( str, "from " );
	strcat( str, "artikelmgpreis " );
	strcat( str, "where vertriebszentrumnr = ? " );
	strcat( str, "for update " );

	exec sql prepare del_netto from :str;
	ERROR_MSG2( "prepare del_netto" )
	exec sql declare Cdelnetto cursor with hold for del_netto;

	strcpy( str, "delete from artikelmgpreis " );
	strcat( str, "where current of Cdelnetto " );
	
	exec sql prepare delete_netto from :str;
	ERROR_MSG2( "prepare delete_netto" )

	exec sql open Cdelnetto using :sBranchno;
    ERROR_MSG2( "open Cdelnetto" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Cdelnetto into :lArticleNo;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Cdelnetto" )

		exec sql execute delete_netto;
		ERROR_MSG2( "execute delete_netto" )

	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Cdelnetto;
    ERROR_MSG2( "close Cdelnetto" )

	return OK;
}

int PrepareLeseKonditionen( char *error_msg)
{
	char *fun = "PrepareLeseKonditionen";

	strcpy( str, "select " );
	strcat( str, LDDISCOUNT_PELISTE );
	strcat( str, " from  " );
	strcat( str, "discount " );
	strcat( str, "where branchno = ? " );
	strcat( str, "and datefrom <= ? " );
	strcat( str, "and dateto >= ? " );

	exec sql prepare dec_discount from :str;
	ERROR_MSG2( "prepare dec_discount" )
	exec sql declare Cseldiscount cursor with hold for dec_discount;
	
	return OK;
}

int PrepareLadeNatra( char *error_msg)
{
	char *fun = "PrepareLadeNatra";
	
	strcpy( str, "insert into artikelnatra (" );
	strcat( str, ARTIKELNATRA_PELISTE );          
	strcat( str, ",EINKAUFSGRUPPE,CUSTOMERNO " );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )" );

	exec sql prepare ins_natra from :str;
	ERROR_MSG2( "prepare ins_natra" )

	return OK;
}

int PrepareLadeValid( char *error_msg)
{
	char *fun = "PrepareLadeValid";

	strcpy( str, "insert into validdiscountinfo (" );
	strcat( str, VALIDDISCOUNT_PELISTE );          
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )" );

	exec sql prepare ins_valid from :str;
	ERROR_MSG2( "prepare ins_valid" )

	return OK;
}

int PrepareLadeNetto( char *error_msg)
{
	char *fun = "PrepareLadeNetto";

	strcpy(str,"insert into artikelmgpreis (");
	strcat(str,"ARTIKEL_NR,");          
	strcat(str,"DATUMGUELTIGAB,");          
	strcat(str,"DATUMGUELTIGBIS,");          
	strcat(str,"KONDGRUPPENNR,");          
	strcat(str,"MENGE,");          
	strcat(str,"PREISEKAPONETTO,");          
	strcat(str,"KZUPD,");          
	strcat(str,"VERTRIEBSZENTRUMNR,");          
	strcat(str,"CUSTOMERNO");          
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,?,?,\"1\",?,? )");

	EXEC SQL PREPARE ins_netto FROM :str;
	ERROR_MSG2( "prepare ins_netto" )

	return OK;
}

int AfterLadeNatra( char *error_msg)
{
	char *fun = "AfterLadeNatra";

	return OK;
}

int AfterLadeValid( char *error_msg)
{
	char *fun = "AfterLadeValid";

	return OK;
}

int AfterLadeNetto( char *error_msg)
{
	char *fun = "AfterLadeNetto";
	int rc = OK;

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
	
	pid = getpid();
	hour1 = time( &hour1 );
	zeit  = localtime( &hour1 );
	fp = fopen( logFile, "a" );
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s",
		    mld,
		    sBranchno,
		    zeit->tm_mday,
	     zeit->tm_mon + 1,
	     zeit->tm_year,
	     zeit->tm_hour,
	     zeit->tm_min,
	     zeit->tm_sec,
		    pid,
		    "loadrabates",
		    fun );
	
	fprintf(fp," %s\n", error_msg );
	fclose(fp);
}


/**************************************************************************/

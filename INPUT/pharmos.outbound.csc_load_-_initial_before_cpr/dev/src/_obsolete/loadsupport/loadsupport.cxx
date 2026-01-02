/*************************************************************************/
/*						                                                 */
/*	Quelle  : loadsupport.cxx                                            */
/*	Autor   : Ronald Imschweiler                                         */
/*	erstellt: 19.02.08                                                   */
/*	Aufgabe	: Laden Routingtabelle fuer Untersstuetzung bei Ausfall       */
/*						                                                 */
/*************************************************************************/

/*** VERSION *************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadsupport"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/*** INCLUDE **************************************************************/

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "customerrouting.h"
#include "pplib/allg.h"
#include "libtpld/dadedb.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <signal.h>
#include "libtpld/define.h"

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
#define MAX_BYTE     MAX_ENTRIES * 513

/*** STRUCTS ***************************************************************/


/*** GLOBALS ***************************************************************/

static char error_msg[81];
static char logFile[301];
int del = NO;
int count = 0;
int countcall = 0;
int countupd = 0;
exec sql begin declare section;
	char str[2048];
    short sBranchNo = 0;
    short sDestBranch = 0;
	long lCustomerNo;
	char datenbank[60];
	long lDate = 0;
	short sWeekday;
	int wert;
exec sql end declare section;

/*** MACROS ***************************************************************/

#define ERROR_MSG2(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               exit (1); }

/*** DECLARATION **********************************************************/

int main( int argc, char **argv );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo( char *error_msg, char mld, int rc );
int PrepareSetzeNotfallAktiv( char *error_msg);
int PrepareLeseDistressrouting( char *error_msg);
int PrepareLoadCustomerrouting( char *error_msg);
int PrepareActivateCustomer( char *error_msg);
int PrepareDeaktCustomerrouting( char *error_msg);
int PrepareDelRufplan( char *error_msg);
int LeseDistressrouting( char *error_msg);
int LoadCustomerrouting( char *error_msg);
int DeaktCustomerrouting( char *error_msg);
int DelRufplan( char *error_msg);

/*** FUNCTION: MAIN *******************************************************/

int main( int argc, char **argv )
{
	char *fun = "Main";
	int  i,rc;
	int  sleepTime = 30;
	time_t long_time;
	int  skip;  
	char *argm;

	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) );

	skip = NO;
	for ( i = 1; i < argc; i++ )
	{
		if ( skip )
		{
			skip = NO;
			continue;
		}
		argm = argv[i];
		if ( !strcmp( argm, "-vz" ) )
		{
			sBranchNo = atoi( argv[i + 1] );
			skip = YES;
		}
		else if ( !strcmp( argm, "-del" ) )
		{
			del = YES;
		}
		else if ( !strcmp( argm, "-db" ) )
		{
			i++;
			sprintf( datenbank, "%s", argv[i] );
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
	 
	if ( skip == ERROR || sBranchNo == 0)
	{
		printf( "  usage: %s\n\t"
			" [ -vz   <Filialnr> ]\n"
			" [ -db   <Datenbank> ]\n"
			" [ -del ]\n");
		return ERROR;
	}
	
	EXEC SQL database :datenbank;
	ERROR_MSG2( "database: ");
	EXEC SQL set lock mode to wait 20;
	ERROR_MSG2( "lock: ");
	EXEC SQL set isolation to dirty read;
	ERROR_MSG2( "set iso: ");

	lDate = AllgGetDate();
	sWeekday = AllgGetWeekDay(lDate,error_msg);
	
	if ( (rc = PrepareSetzeNotfallAktiv(error_msg)) < 0) return rc;

	EXEC SQL open Cselparameter using :sBranchNo;
	ERROR_MSG2( "open Cselparameter: ");
	EXEC SQL fetch Cselparameter into :wert;
	ERROR_MSG2( "fetch Cselparameter: ");
	if(del)
	{
		if( sqlca.sqlcode == SQLNOTFOUND )
		{
			printf( "Notfall-Konzept nicht mehr aktiv" );fflush(stdout);
			sprintf( error_msg, "Notfall-Konzept nicht mehr aktiv" );
			PrintMsg( fun, error_msg, HINW, -1 );
			return -1;
		}
		sprintf( error_msg, "%s wurde zum Deaktivieren gestartet", argv[0] );
	}
	else
	{
		if( sqlca.sqlcode != SQLNOTFOUND )
		{
			printf( "Notfall-Konzept bereits aktiv" );fflush(stdout);
			sprintf( error_msg, "Notfall-Konzept bereits aktiv" );
			PrintMsg( fun, error_msg, HINW, -1 );
			return -1;
		}
		sprintf( error_msg, "%s wurde zum Aktivieren gestartet", argv[0] );
	}
	PrintMsg( fun, error_msg, HINW, -1 );
  		
	if ( (rc = PrepareLeseDistressrouting(error_msg)) < 0) return rc;
	if ( (rc = PrepareLoadCustomerrouting(error_msg)) < 0) return rc;
	if ( (rc = PrepareActivateCustomer(error_msg)) < 0) return rc;
	if ( sBranchNo == 51 || sBranchNo == 58 )
	{
		if ( (rc = PrepareDeaktCustomerrouting(error_msg)) < 0) return rc;
		if ( (rc = DeaktCustomerrouting(error_msg)) < 0) return rc;
		sprintf( error_msg, " %d Routing-Saetze geaendert (MA/FB)", countupd);
		PrintMsg( fun, error_msg, HINW, -1 );
	}
	if(!del)
	{
		if ( (rc = PrepareDelRufplan(error_msg)) < 0) return rc;
	}
	if ( (rc = LeseDistressrouting(error_msg)) < 0) return rc;

	if(del)
	{
		EXEC SQL EXECUTE del_parameter using :sBranchNo;
		ERROR_MSG2( "del_parameter: ");
		sprintf( error_msg, " %d Routing-Saetze geloescht", count);
	}
	else
	{
		EXEC SQL EXECUTE ins_parameter using :sBranchNo;
		ERROR_MSG2( "ins_parameter: ");
		sprintf( error_msg, " %d Anruf-Saetze geloescht", countcall);
		PrintMsg( fun, error_msg, HINW, -1 );
		sprintf( error_msg, " %d Routing-Saetze eingefuegt", count);
	}
	PrintMsg( fun, error_msg, HINW, -1 );

	PrintMsg( fun, "Ende", HINW, 0 );

	return OK;
}

int PrepareSetzeNotfallAktiv( char *error_msg)
{
	char *fun = "PrepareSetzeNotfallAktiv";
	int rc;

	strcpy(str,"select wert from parameter ");
	strcat(str," where ");
	strcat(str,"FILIALNR = ? ");
	strcat(str,"and PROGRAMMNAME = \"NOTFALL\" ");

	EXEC SQL PREPARE sel_parameter FROM :str;
	ERROR_MSG2( "prepare sel_parameter" )
	exec sql declare Cselparameter cursor with hold for sel_parameter;
	ERROR_MSG2( "declare Cselparameter" )

	strcpy(str,"insert into parameter (");
	strcat(str,"FILIALNR,");
	strcat(str,"PROGRAMMNAME,");
	strcat(str,"ZWECK,");
	strcat(str,"PARAMETERNAME,");
	strcat(str,"AUSPRAEGUNG,");
	strcat(str,"WERT");
	strcat(str," ) values ( ");
	strcat(str," ?, \"NOTFALL\", ' ', ' ', ' ', '1' )");          

	EXEC SQL PREPARE ins_parameter FROM :str;
	ERROR_MSG2( "prepare ins_parameter" )

	strcpy(str,"delete from parameter");
	strcat(str," where ");
	strcat(str,"FILIALNR = ? ");
	strcat(str,"and PROGRAMMNAME = \"NOTFALL\" ");

	EXEC SQL PREPARE del_parameter FROM :str;
	ERROR_MSG2( "prepare del_parameter" )

	return OK;
}

int PrepareLeseDistressrouting( char *error_msg)
{
	char *fun = "PrepareLeseDistressrouting";
	int rc;

	strcpy(str,"select customerno,destbranchno from distressrouting ");
	strcat(str," where ");
	strcat(str,"BRANCHNO = ? ");
	strcat(str,"and DESTBRANCHNO != 0 ");	/* wegen falscher Eintraege */

	EXEC SQL PREPARE sel_distress FROM :str;
	ERROR_MSG2( "prepare sel_distress" )
	exec sql declare Cseldistress cursor with hold for sel_distress;
	ERROR_MSG2( "declare Cseldistress" )

	return OK;
}

int PrepareLoadCustomerrouting( char *error_msg)
{
	char *fun = "PrepareLoadCustomerrouting";
	int rc;

	strcpy(str,"insert into customerrouting ");
	strcat(str,"( ");
	strcat(str,CUSTOMERROUTING_PELISTE);          
	strcat(str," ) values ( ");
	strcat(str," ?, ?, ?, ?, ?, ?, ?) ");

	EXEC SQL PREPARE ins_customerrouting FROM :str;
	ERROR_MSG2( "prepare ins_customerrouting" )

	strcpy(str,"delete from customerrouting ");
	strcat(str,"where ");
	strcat(str,"BRANCHNO = ?");
	strcat(str," and ");
	strcat(str,"CUSTOMERNO = ?");
	strcat(str," and ");
	strcat(str,"DESTBRANCHNO = ?"); 
	strcat(str," and ");
	strcat(str,"WEEKDAY = ?"); 

	EXEC SQL PREPARE del_customerrouting FROM :str;
	ERROR_MSG2( "prepare del_customerrouting" )

	return OK;
}

int PrepareActivateCustomer( char *error_msg)
{
	char *fun = "PrepareActivateCustomer";
	int rc;

	strcpy(str,"update kundeschalter ");
	strcat(str,"set ");
	strcat(str,"skdkundeaegesperrt = ? ");
	strcat(str,"where ");
	strcat(str,"vertriebszentrumnr = ? ");
	strcat(str," and ");
	strcat(str,"kundennr = ?");

	EXEC SQL PREPARE upd_kundeschalter FROM :str;
	ERROR_MSG2( "prepare upd_kundeschalter" )

	return OK;
}

/* MA - FB Spezial */
int PrepareDeaktCustomerrouting( char *error_msg)
{
	char *fun = "PrepareDeaktCustomerrouting";
	int rc;

	strcpy(str,"select customerno,destbranchno from customerrouting ");
	strcat(str,"where ");
	strcat(str,"BRANCHNO = ?");
	strcat(str," and ");
	strcat(str,"WEEKDAY = ? "); 
	strcat(str,"for update"); 

	EXEC SQL PREPARE sel_customerrouting FROM :str;
	ERROR_MSG2( "prepare sel_customerrouting" )
	exec sql declare Cselrouting cursor with hold for sel_customerrouting;
	ERROR_MSG2( "declare Cselrouting" )

	strcpy(str,"select destbranchno from distressrouting ");
	strcat(str," where ");
	strcat(str,"BRANCHNO = ? ");
	strcat(str," and ");
	strcat(str,"CUSTOMERNO = ? "); 

	EXEC SQL PREPARE sel_ziel FROM :str;
	ERROR_MSG2( "prepare sel_ziel" )
	exec sql declare Cupdrouting cursor for sel_ziel;
	ERROR_MSG2( "declare Cupdrouting" )

	strcpy(str,"update customerrouting ");
	strcat(str,"set ");
	strcat(str,"DESTBRANCHNO = ? ");
	strcat(str,"where current of Cselrouting");

	EXEC SQL PREPARE upd_customerrouting FROM :str;
	ERROR_MSG2( "prepare upd_customerrouting" )

	return OK;
}

int PrepareDelRufplan( char *error_msg)
{
	char *fun = "PrepareDelRufplan";
	int rc;

	strcpy(str,"select urrufzeit from kundeanrufplantag ");
	strcat(str,"where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"KUNDENNR = ?");          
	strcat(str," and ");
	strcat(str,"DATUM = ?");          
	strcat(str," and ");
	strcat(str,"ANRUFSTATUS != 9");          
	strcat(str," for update"); 

	EXEC SQL PREPARE sel_rufplan FROM :str;
	ERROR_MSG2( "prepare sel_rufplan" )
	exec sql declare Cselrufplan cursor for sel_rufplan;
	ERROR_MSG2( "declare Cselrufplan" )

	strcpy(str,"delete from kundeanrufplantag ");
	strcat(str,"where current of Cselrufplan");

	EXEC SQL PREPARE del_kundeanrufplantag FROM :str;
	ERROR_MSG2( "prepare del_kundeanrufplantag" )

	strcpy(str,"delete from kundeanrufplanprot ");
	strcat(str,"where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"KUNDENNR = ?");          
	strcat(str," and ");
	strcat(str,"DATUM = ?");
	strcat(str," and ");
	strcat(str,"URRUFZEIT = ?");

	EXEC SQL PREPARE del_kundeanrufplanprot FROM :str;
	ERROR_MSG2( "prepare del_kundeanrufplanprot" )

	return OK;
}

int LeseDistressrouting( char *error_msg)
{
	char *fun = "LeseDistressrouting";
	int rc;

	exec sql open Cseldistress using :sBranchNo;
	ERROR_MSG2( "open Cseldistress" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work1:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work1:" )
		}
		exec sql fetch Cseldistress into :lCustomerNo,:sDestBranch;
		ERROR_MSG2( "fetch Cseldistress" )
		if( sqlca.sqlcode == SQLNOTFOUND ) break;
		if ( (rc = LoadCustomerrouting(error_msg)) < 0) return rc;
		if(!del)
		{
//			if ( (rc = DelRufplan(error_msg)) < 0) return rc;
		}
	}
	exec sql commit work;
	ERROR_MSG2( "Commit Work2:" )

	return OK;
}

int LoadCustomerrouting( char *error_msg)
{
	char *fun = "LoadCustomerrouting";
	int rc;

	exec sql begin declare section;
	long lStart;
	long lStop;
	char cSgesperrt[2];
    exec sql end declare section;

	if(del)
	{
		strcpy(cSgesperrt,"1");
		EXEC SQL EXECUTE del_customerrouting USING	:sBranchNo,
													:lCustomerNo,
													:sDestBranch,
													:sWeekday;
		ERROR_MSG2( "del_customerrouting:" )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
		}
		else
		{
			count++;
		}
	}
	else
	{
		strcpy(cSgesperrt,"0");
		lStart = 1;
		lStop = 2359;
		EXEC SQL EXECUTE ins_customerrouting USING	:lCustomerNo,
													:sBranchNo,
													:lStart,
													:lStop,
													:sDestBranch,
													' ',
													:sWeekday;
		if (sqlca.sqlcode == -239 ) return OK;  /* already exist */
		ERROR_MSG2( "ins_customerrouting:" )
		count++;
	}
	EXEC SQL EXECUTE upd_kundeschalter USING	:cSgesperrt,
												:sDestBranch,
												:lCustomerNo;
	ERROR_MSG2( "upd_kundeschalter:" )
	return OK;
}

/* MA - FB Spezial */
int DeaktCustomerrouting( char *error_msg)
{
	char *fun = "DeaktCustomerrouting";

	exec sql begin declare section;
	short sVon,sNach;
	short sZiel,sIstZiel;
	long lCustomerno;
    exec sql end declare section;

	if(sBranchNo == 51)
	{
		sVon = 58;
		sNach = 51;
	}
	else if(sBranchNo == 58)
	{
		sVon = 51;
		sNach = 58;
	}
	else
	{
		return OK;
	}

	EXEC SQL OPEN Cselrouting USING	:sVon,
									:sWeekday;
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work1:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work1:" )
		}
		EXEC SQL FETCH Cselrouting into :lCustomerno,:sIstZiel;
		ERROR_MSG2( "fetch Cselrouting" )
		if( sqlca.sqlcode == SQLNOTFOUND ) break;
		if(del)
		{
			if ( sIstZiel == sNach ) continue;
			sZiel = sNach;
		}
		else
		{
			EXEC SQL OPEN Cupdrouting using :sBranchNo,:lCustomerno;
			ERROR_MSG2( "OPEN Cupdrouting:" )
			EXEC SQL FETCH Cupdrouting into :sZiel;
			ERROR_MSG2( "FETCH Cupdrouting:" )
			if ( sIstZiel == sZiel ) continue;
		}
		EXEC SQL EXECUTE upd_customerrouting using :sZiel;
		ERROR_MSG2( "upd_customerrouting:" )
		countupd++;
	}
	exec sql commit work;
	ERROR_MSG2( "Commit Work2:" )

	return OK;
}

int DelRufplan( char *error_msg)
{
	char *fun = "DelRufplan";

	exec sql begin declare section;
	long lUrrufzeit;
    exec sql end declare section;

	EXEC SQL OPEN Cselrufplan USING	:sBranchNo,
									:lCustomerNo,
									:lDate;
	for(;;)
	{
		EXEC SQL FETCH Cselrufplan into	:lUrrufzeit;
		ERROR_MSG2( "fetch Cselrufplan" )
		if( sqlca.sqlcode == SQLNOTFOUND ) break;
		EXEC SQL EXECUTE del_kundeanrufplantag;
		ERROR_MSG2( "del_kundeanrufplantag:" )
		EXEC SQL EXECUTE del_kundeanrufplanprot USING	:sBranchNo,
													:lCustomerNo,
													:lDate,
													:lUrrufzeit;
		ERROR_MSG2( "del_kundeanrufplanprot:" )
		countcall++;
	}

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
		    sBranchNo,
		    zeit->tm_mday,
			zeit->tm_mon + 1,
			zeit->tm_year,
			zeit->tm_hour,
			zeit->tm_min,
			zeit->tm_sec,
		    pid,
		    "loadsupport",
		    fun );
	
	fprintf(fp," %s\n", error_msg );
	fclose(fp);
}

/**************************************************************************/

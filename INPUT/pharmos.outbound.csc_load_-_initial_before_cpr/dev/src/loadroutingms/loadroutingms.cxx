/*************************************************************************/
/*						                                                 */
/*	Quelle  : loadrouting.cxx                                            */
/*	Autor   : Ronald Imschweiler                                         */
/*	erstellt: 17.09.07                                                   */
/*	Aufgabe	: Laden Routingtabelle bei Tag-/Nachthaus                    */
/*						                                                 */
/*************************************************************************/

/*** VERSION *************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadroutingms"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/*** INCLUDE **************************************************************/

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "customerrouting.h"
#include "pplib/allg.h"
#include "libtpld/dadedb.h"
#include "callplanmaintenance.h"
#include "customer.h"
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
long lZeitVon;
long lZeitBis;
exec sql begin declare section;
	char str[2048];
    short sBranchNo = 0;
    short sDestBranch = 0;
	char datenbank[60];
	long lDurchlaufnormal;
	long lDurchlaufeilbote;
	long lDate = 0;
	short sWeekday;
	long lActDate = 0;
	short sActWeekday;
	long lkunde;
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
int PrepareDelHoliday( char *error_msg);
int DelHoliday( char *error_msg);
int PrepareLoadCustomerrouting( char *error_msg);
int LadeCustomerrouting(char *);

/*** FUNCTION: MAIN *******************************************************/

int main( int argc, char **argv )
{
	char *fun = "Main";
	int  i,rc;
	int  sleepTime = 30;
	time_t long_time;
	int  skip;  
	char *argm;
	mcallplanloadS srvLoad;
    tError stError;

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
		else if ( !strcmp( argm, "-dest" ) )
		{
			sDestBranch = atoi(argv[i + 1]);
			skip = YES;
		}
		else if ( !strcmp( argm, "-von" ) )
		{
			lZeitVon = atol(argv[i + 1])*100;
			skip = YES;
		}
		else if ( !strcmp( argm, "-bis" ) )
		{
			lZeitBis = atol(argv[i + 1])*100;
			skip = YES;
		}
		else if ( !strcmp( argm, "-ld" ) )
		{
			lDate = atol(argv[i + 1]);
			skip = YES;
		}
		else if ( !strcmp( argm, "-db" ) )
		{
			i++;
			sprintf( datenbank, "%s", argv[i] );
		}
		else if ( !strcmp( argm, "-version" ) )
		{
			printVersion(versioninfo);
			return OK;
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
			" [ -ld   <19970314> ]\n"
			" [ -dest <ZielFilialnr> ]\n"
			" [ -von  <Beginnzeit> ]\n"
			" [ -bis  <Endezeit> ]\n", argv[0] );
		return ERROR;
	}
	
	sprintf( error_msg, "%s wurde gestartet", argv[0] );
	PrintMsg( fun, error_msg, HINW, -1 );

	EXEC SQL database :datenbank;
	ERROR_MSG2( "database: ");
	EXEC SQL set lock mode to wait 20;
	ERROR_MSG2( "lock: ");
	EXEC SQL set isolation to dirty read;
	ERROR_MSG2( "set iso: ");

	if (lDate == 0) /* wenn keine Datumseingabe dann errechnen Datum */
	{
		srvLoad.VERTRIEBSZENTRUMNR = sBranchNo;
		srvLoad.LADEDATUM = 0;
		srvLoad.LADEKIPPZEIT = 120000;
		if ( Mcallplanload_GetInitializeData( &srvLoad, &stError, FALSE ) == IS_ERROR )
		{
			return CheckSql( fun, &stError, "%s", stError.spError );
		}
		lDate = srvLoad.LADEDATUM;
		lActDate = AllgGetDate();
		if(AllgGetTime() > 120000)
		{
			lActDate = AllgAddDate(lActDate,1,error_msg);
		}
		if(lActDate < lDate)
		{
			sActWeekday = AllgGetWeekDay(lActDate,error_msg);
			if ( (rc = PrepareDelHoliday(error_msg)) < 0) return rc;
			for(;;)
			{
				if (sActWeekday != 0) // nur Feiertage loeschen
				{
					if ( (rc = DelHoliday(error_msg)) < 0) return rc;
				}
				lActDate = AllgAddDate(lActDate,1,error_msg);
				if(lActDate >= lDate) break;
				sActWeekday = AllgGetWeekDay(lActDate,error_msg);
			}
		}
	}
	sWeekday = AllgGetWeekDay(lDate,error_msg);
  		
	if ( (rc = PrepareLoadCustomerrouting(error_msg)) < 0) return rc;
	if ( (rc = LadeCustomerrouting(error_msg)) < 0) return rc;

	PrintMsg( fun, "Ende", HINW, 0 );

	return OK;
}

int PrepareDelHoliday( char *error_msg)
{
	char *fun = "PrepareDelHoliday";
	int rc;

	strcpy(str,"select customerno from customerrouting ");
	strcat(str,"where ");
	strcat(str,"BRANCHNO = ?");          
	strcat(str," and ");          
	strcat(str,"WEEKDAY = ?");          
	strcat(str," for update");

	EXEC SQL PREPARE sel_holiday FROM :str;
	ERROR_MSG2( "prepare sel_holiday" )
	exec sql declare Cselholiday cursor with hold for sel_holiday;
	ERROR_MSG2( "declare Cselholiday" )

	strcpy(str,"delete from customerrouting ");
	strcat( str, "where current of Cselholiday " );

	EXEC SQL PREPARE del_holiday FROM :str;
	ERROR_MSG2( "prepare del_holiday" )

	return OK;
}

int DelHoliday( char *error_msg)
{
	char *fun = "DelHoliday";
	int rc;
	int i=1;

	exec sql open Cselholiday using :sBranchNo,:sActWeekday;
	ERROR_MSG2( "open Cselholiday" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Cselholiday into :lkunde;
		ERROR_MSG2( "fetch Cselholiday" )
		if( sqlca.sqlcode == SQLNOTFOUND ) break;

		EXEC SQL EXECUTE del_holiday;
		ERROR_MSG2( "del_holiday" )
	}
	exec sql commit work;
	ERROR_MSG2( "Commit Work2:" )

	exec sql close Cselholiday;
    ERROR_MSG2( "close Cselholiday" )

	return OK;
}

int PrepareLoadCustomerrouting( char *error_msg)
{
	char *fun = "PrepareLoadCustomerrouting";
	int rc;

	EXEC SQL select durchlaufeilbote 
		into :lDurchlaufeilbote
		from paraauftragbearb
		where filialnr = :sBranchNo;
	ERROR_MSG2( "sel_paraorg" )
	lDurchlaufeilbote = (lDurchlaufeilbote+1) * (-100);
	EXEC SQL select durchlaufnormal
		into :lDurchlaufnormal
		from paraauftragbearb
		where filialnr = :sDestBranch;
	ERROR_MSG2( "sel_paradest" )
	lDurchlaufnormal = (lDurchlaufnormal+1) * (-100);

	strcpy(str,"select kundennr from kunde ");
	strcat(str," where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");

	EXEC SQL PREPARE sel_kunde FROM :str;
	ERROR_MSG2( "prepare sel_kunde" )
	exec sql declare Cselkunde cursor with hold for sel_kunde;
	ERROR_MSG2( "declare Cselkunde" )

	strcpy(str,"select kundennr from kunde ");
	strcat(str," where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"KUNDENNR = ?");          

	EXEC SQL PREPARE sel_kunde_einzel FROM :str;
	ERROR_MSG2( "prepare sel_kunde_einzel" )

	strcpy(str,"select tourplantag.DATUMKOMMI,tour.TOURID from tourplantag,tour ");
	strcat(str," where ");
	strcat(str,"tourplantag.DATUMKOMMI = ?");          
	strcat(str," and ");          
	strcat(str,"tourplantag.VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"tourplantag.KUNDENNR = ?");          
	strcat(str," and ");
	strcat(str,"tourplantag.KZAUTOZUORD = '1'");
	strcat(str," and ");
	strcat(str,"tourplantag.TOURINAKTIV = '0'");
	strcat(str," and ");          
	strcat(str,"tourplantag.TOURID = tour.TOURID");          
	strcat(str," and ");          
	strcat(str,"tourplantag.DATUMKOMMI = tour.DATUMKOMMI");          
	strcat(str," and ");          
	strcat(str,"tourplantag.VERTRIEBSZENTRUMNR = tour.FILIALNR");          
	strcat(str," and ");          
	strcat(str,"tour.TOURID < ?");
	strcat(str," order by ");
	strcat(str,"tour.TOURID");
	strcat(str," desc");

	EXEC SQL PREPARE sel_tourvon FROM :str;
	ERROR_MSG2( "prepare sel_tourvon" )
	exec sql declare Cseltourvon cursor with hold for sel_tourvon;
	ERROR_MSG2( "declare Cseltourvon" )

	strcpy(str,"select tourplantag.DATUMKOMMI,tour.TOURID from tourplantag,tour ");
	strcat(str," where ");
	strcat(str,"tourplantag.DATUMKOMMI = ?");          
	strcat(str," and ");          
	strcat(str,"tourplantag.VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"tourplantag.KUNDENNR = ?");          
	strcat(str," and ");
	strcat(str,"tourplantag.KZAUTOZUORD = '1'");
	strcat(str," and ");
	strcat(str,"tourplantag.TOURINAKTIV = '0'");
	strcat(str," and ");
	strcat(str,"tourplantag.TOURID = tour.TOURID");
	strcat(str," and ");
	strcat(str,"tourplantag.DATUMKOMMI = tour.DATUMKOMMI");
	strcat(str," and ");
	strcat(str,"tourplantag.VERTRIEBSZENTRUMNR = tour.FILIALNR");
	strcat(str," and ");
	strcat(str,"tour.TOURID >= ?");
	strcat(str," order by ");
	strcat(str,"tour.TOURID");
	strcat(str," desc");

	EXEC SQL PREPARE sel_tourbis FROM :str;
	ERROR_MSG2( "prepare sel_tourbis" )
	exec sql declare Cseltourbis cursor with hold for sel_tourbis;
	ERROR_MSG2( "declare Cseltourbis" )

	strcpy(str,"update customerrouting set ");
	strcat(str,CUSTOMERROUTING_UPDLISTE);          
	strcat(str," where ");
	strcat(str,"BRANCHNO = ?");          
	strcat(str," and ");          
	strcat(str,"CUSTOMERNO = ?");          
	strcat(str," and ");          
	strcat(str,"WEEKDAY = ?");          
	strcat(str," and ");          
	strcat(str,"TIMEFROM = ?");          

	EXEC SQL PREPARE upd_customerrouting FROM :str;
	ERROR_MSG2( "prepare upd_customerrouting" )

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
	strcat(str,"WEEKDAY = ?");          

	EXEC SQL PREPARE del_customerrouting FROM :str;
	ERROR_MSG2( "prepare del_customerrouting" )

	strcpy(str,"select tourplantagwoche.TOURID from tourplantagwoche,tourplanwoche ");
	strcat(str," where ");
	strcat(str,"tourplantagwoche.WEEKDAY >= ?");          
	strcat(str," and ");          
	strcat(str,"tourplantagwoche.VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"tourplantagwoche.KUNDENNR = ?");          
	strcat(str," and ");
	strcat(str,"tourplantagwoche.TOURID = tourplanwoche.TOURID");          
	strcat(str," and ");          
	strcat(str,"tourplantagwoche.WEEKDAY = tourplanwoche.WEEKDAY");          
	strcat(str," and ");          
	strcat(str,"tourplantagwoche.VERTRIEBSZENTRUMNR = tourplanwoche.FILIALNR");          
	strcat(str," order by ");
	strcat(str,"tourplantagwoche.WEEKDAY,");
	strcat(str,"tourplantagwoche.TOURID");

	EXEC SQL PREPARE sel_tourwoche FROM :str;
	ERROR_MSG2( "prepare sel_tourwoche" )
	exec sql declare Cseltourwoche cursor with hold for sel_tourwoche;
	ERROR_MSG2( "declare Cseltourwoche" )

	return OK;
}

int LadeCustomerrouting( char *error_msg)
{
	char *fun = "LadeCustomerrouting";

	exec sql begin declare section;
	long lDatum;
	long lStart;
	long lAlle = 0;
	long lStop;
	long lCustomerNo;
	long lZeitVersandVon;
	long lZeitVersandBis;
	short sNextday;
	char cTourID[7];
    exec sql end declare section;

	exec sql open Cselkunde using :sBranchNo;
	ERROR_MSG2( "open Cselkunde" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Cselkunde into :lCustomerNo;
		ERROR_MSG2( "fetch Cselkunde" )
		if( sqlca.sqlcode == SQLNOTFOUND ) break;

		EXEC SQL EXECUTE sel_kunde_einzel USING :sDestBranch,:lCustomerNo;
		ERROR_MSG2( "sel_kunde_einzel" )
		if( sqlca.sqlcode == SQLNOTFOUND )
		{
			EXEC SQL EXECUTE del_customerrouting USING :sBranchNo,
													:lCustomerNo,
													:sWeekday;
			ERROR_MSG2( "del_customerrouting:" )
			continue;
		}

		lStart = lZeitVon;
		lStop = lZeitBis;
		/* Ueberpruefen ob Kunde ueberhaupt aktuelle Touren hat */
		exec sql open Cseltourbis using :lDate,:sDestBranch,:lCustomerNo,:lAlle;
		ERROR_MSG2( "open Cseltourbis0" )
		exec sql fetch Cseltourbis into :lDatum,:lZeitVersandBis;
		ERROR_MSG2( "fetch Cseltourbis0" )
		if( sqlca.sqlcode == SQLNOTFOUND )
		{
			/* Wenn keine Tour am aktuellen Tag im Zielhaus, */
			/* nachsehen ob keine Tour am aktuellen Tag im eigenen Haus, */
			exec sql open Cseltourvon using :lDate,:sBranchNo,:lCustomerNo,:lStart;
			ERROR_MSG2( "open Cseltourvon" )
			exec sql fetch Cseltourvon into :lDatum,:lZeitVersandVon;
			ERROR_MSG2( "fetch Cseltourvon" )
			if( sqlca.sqlcode != SQLNOTFOUND )
			{
				/* Wenn Tour am aktuellen Tag im Zielhaus, */
				EXEC SQL EXECUTE del_customerrouting USING :sBranchNo,
													:lCustomerNo,
													:sWeekday;
				ERROR_MSG2( "del_customerrouting:" )
				continue;
			}
			/* Ueberpruefen Tour am Folgetag */
			sNextday = sWeekday + 1;
			if(sNextday > 6) sNextday = 0;
			exec sql open Cseltourwoche using :sNextday,:sDestBranch,:lCustomerNo;
			ERROR_MSG2( "open Cseltourwoche" )
			exec sql fetch Cseltourwoche into :cTourID;
			ERROR_MSG2( "fetch Cseltourwoche" )
			if( sqlca.sqlcode == SQLNOTFOUND )
			{
				if(sNextday == 0)
				{
					EXEC SQL EXECUTE del_customerrouting USING :sBranchNo,
														:lCustomerNo,
														:sWeekday;
					ERROR_MSG2( "del_customerrouting:" )
					continue;
				}
				sNextday = 0;
				exec sql open Cseltourwoche using :sNextday,:sDestBranch,:lCustomerNo;
				ERROR_MSG2( "open Cseltourwoche" )
				exec sql fetch Cseltourwoche into :cTourID;
				ERROR_MSG2( "fetch Cseltourwoche" )
				if( sqlca.sqlcode == SQLNOTFOUND )
				{
					EXEC SQL EXECUTE del_customerrouting USING :sBranchNo,
														:lCustomerNo,
														:sWeekday;
					ERROR_MSG2( "del_customerrouting:" )
					continue;
				}
			}
			if(atol(cTourID) < lZeitVon)
			{
				EXEC SQL EXECUTE del_customerrouting USING :sBranchNo,
													:lCustomerNo,
													:sWeekday;
				ERROR_MSG2( "del_customerrouting:" )
				continue;
			}
			lStart = 1;
			lStop = 2359;
			EXEC SQL EXECUTE del_customerrouting USING :sBranchNo,
													:lCustomerNo,
													:sWeekday;
			ERROR_MSG2( "del_customerrouting0:" )
			EXEC SQL EXECUTE ins_customerrouting USING :lCustomerNo,
		                                      :sBranchNo,
											  :lStart,
											  :lStop,
											  :sDestBranch,
											  ' ',
											  :sWeekday;
			ERROR_MSG2( "ins_customerrouting0:" )
		}
		else
		{
			exec sql open Cseltourbis using :lDate,:sDestBranch,:lCustomerNo,:lStart;
			ERROR_MSG2( "open Cseltourbis" )
			exec sql fetch Cseltourbis into :lDatum,:lZeitVersandBis;
			ERROR_MSG2( "fetch Cseltourbis" )
			if( sqlca.sqlcode == SQLNOTFOUND )
			{
				EXEC SQL EXECUTE del_customerrouting USING :sBranchNo,
														:lCustomerNo,
														:sWeekday;
				ERROR_MSG2( "del_customerrouting:" )
				continue;
			}
			if(lZeitVersandBis > lZeitBis)
			{
				lStop = lZeitBis;
			}
			else
			{
				AllgAddTime(lZeitVersandBis,lDurchlaufnormal,&lStop);
			}
			exec sql open Cseltourvon using :lDate,:sBranchNo,:lCustomerNo,:lStart;
			ERROR_MSG2( "open Cseltourvon" )
			exec sql fetch Cseltourvon into :lDatum,:lZeitVersandVon;
			ERROR_MSG2( "fetch Cseltourvon" )
			if( sqlca.sqlcode == SQLNOTFOUND )
			{
				lStart = 100;
				lStop = 235900;
			}
			else
			{
				AllgAddTime(lZeitVersandVon,lDurchlaufeilbote,&lStart);
			}
			lStart = lStart/100;
			lStop = lStop/100;
			EXEC SQL EXECUTE del_customerrouting USING :sBranchNo,
													:lCustomerNo,
													:sWeekday;
			ERROR_MSG2( "del_customerrouting:" )
			EXEC SQL EXECUTE ins_customerrouting USING :lCustomerNo,
		                                      :sBranchNo,
											  :lStart,
											  :lStop,
											  :sDestBranch,
											  ' ',
											  :sWeekday;
			ERROR_MSG2( "ins_customerrouting:" )
		}
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )
	
	exec sql close Cselkunde;
    ERROR_MSG2( "close Cselkunde" )
	return OK;
}

/***** WriteLogInfo nur zum Aufruf von PrintMsg ******************************/

void WriteLogInfo( char *error_msg, char mld, int rc )
{
	PrintMsg( "loadrouting", error_msg, mld, rc );
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
		    "loadrouting",
		    fun );
	
	fprintf(fp," %s\n", error_msg );
	fclose(fp);
}

/**************************************************************************/

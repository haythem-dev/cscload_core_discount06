/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

/* ToDo Programmname */
#define PROJECTNAME	 "loadplannedcalls"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "pplib/allg.h"
#include <dirent.h>                                     
#include <errno.h>                                     
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
#define LEN_FILE_DATEFROM  8

char log_file[300 + 1];
char dateiname[L_TEXT];
char countrycode[3] = "";
int explain = NO;
int zaehlerDel = 0;


exec sql begin declare section;

long currentDate = 0;
char szDatabase[128];
short sBranchno = 0;
long rufzeit = 0;
int lfdaktion = 0;
int prioritaet = 40;
long lWeekDay = 0;
char spWd[3] = {0};
int poolid = 0;
char anrufart[3] = "PH";
char manuell[2] = "M";
int stagrueckruf;
char telrueckrufnr[16] = "  ";
int zugriff = 0;
char callinfo[241] = "  ";


int status = 7;
short statusanrufsatz = 0;
short statusverbindung = 0;
short loeschgrund = 0;
int uid = 0;


struct N_TOURPLANTAG structTPT;
typedef struct N_TOURPLANTAG {
	long idfnr;
	short vertriebszentrumnr;
	long datumkommi;
	char tourid[7];
	long plannedcall;
	char bemerkungen[241];
} tourPlanTag;

exec sql end declare section;


/***** DECLARATION **********************************************************/

int main(int, char**);
void PrintMsg(char* fun, char* error_msg, char mld, int rc);
void WriteLogInfo(char* error_msg, char mld, int rc);
int ReadTourPlanTag(char* error_msg);
int PrepareTagPlan(char* error_msg);
int PrepareTagPlanEreignis(char* error_msg);
int PopulateTagPlan(char* error_msg);
int PopulateTagPlanEreignis(char* error_msg);
int insertandupdateTagPlan(char* error_msg);
int ExecuteTourPlanTag(char* error_msg);

int OpenDatabase(void);
int CloseDatabase(void);
void getCurrentDate(char* datebuf, int buflen);
/***** MAIN *****************************************************************/

int main(int argc, char** argv)
{
	char  error_msg[181];
	char* schalter;
	int   skip;
	int   i;
	char* fun = "Main";
	char* LOG_FILE = "wws.log";
	char* LOG_PATH;
	char  logpath[256 + 1];
	int   rc;
	int   status = 0;
	char  start_msg[255];

	strcpy(start_msg, "gestartet mit:");
	skip = NO;

	sprintf(start_msg, "%d %s %s %s %s %s %s %s", argc, argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
    PrintMsg(fun, start_msg, HINW, 0);

	for (i = 1; i < argc; i++)
	{

		schalter = argv[i];
		if ( !strcmp( schalter, "-ld" ) )
		{
			strcat(start_msg, " -ld");
			i++;
			currentDate = atol(argv[i]); 
			sprintf(start_msg, "%s %s", start_msg, argv[i]);
			
		}
		else if ( !strcmp( schalter, "-db" ) )
		{ 
			strcat(start_msg, " -db");
			i++;
			strcpy( szDatabase, argv[i]); 
		}
		else if (!strcmp(schalter, "-branchno"))
		{
			strcat(start_msg, " -branchno");
			i++;
			sBranchno = atoi(argv[i]);
			sprintf(start_msg, "%s %s", start_msg, argv[i]);
		}
		else if (!strcmp(schalter, "-countrycode"))
		{
			strcat(start_msg, " -countrycode");
			i++;
			sprintf(countrycode, "%s", argv[i]);
			sprintf(start_msg, "%s %s", start_msg, argv[i]);
		}
		else if (!strcmp(schalter, "-version"))
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

	if ( argc == 1 )
	{
      printf("  usage: %s\n\t"
				" { -dbin datenbankname <Datenbankname Eingabe> }\n\t"
				" { -dbout datenbankname <Datenbankname Ausgabe> }\n\t"
				" { -branchno filialnr }\n\t"
				, argv[0]);
			return 1;
     }
	 
	 
	if (OpenDatabase() != OK)
	{
		PrintMsg(fun, "mit Fehler beendet OpenDatabase", FEHL, ERROR);
		return ERROR;
	}
    /*
	exec sql database : szDatabase;
	ERROR_MSG("Fehler oeffnen DB")

	exec sql set lock mode to wait 20;
	ERROR_MSG("Set LockMode to Wait")

	exec sql set isolation to dirty read;
	ERROR_MSG("Set Isolation to Dirty Read")

	PrintMsg(fun, start_msg, HINW, 0);
	*/
	if (ReadTourPlanTag(error_msg) != OK)
	{
		PrintMsg(fun, "mit Fehler beendet ReadTourPlanTag", FEHL, rc);
		return 2;
	}

	if ((rc = PrepareTagPlan(error_msg)) != 0)
	{
		PrintMsg(fun, "mit Fehler beendet PrepareTagPlan", FEHL, rc);
		return 3;
	}

	if ((rc = 	PrepareTagPlanEreignis(error_msg)) != 0)
	{
		PrintMsg(fun, "mit Fehler beendet PrepareTagPlanEreignis", FEHL, rc);
		return 4;
	}
	
	if ((rc = ExecuteTourPlanTag(error_msg)) != 0)
	{
		PrintMsg(fun, "mit Fehler beendet ExecuteTourPlanTag", FEHL, rc);
		return 5;
	}

	
	if(CloseDatabase() != OK )
	{
		PrintMsg(fun, "mit Fehler beendet CloseDatabase", FEHL, rc);
		return 6;		
	}

	PrintMsg(fun, "loadplannedcalls korrekt beendet", HINW, rc);
	
	return 0;

}


/*** Read-ReadTourPlanTag  ************************************************/
int ReadTourPlanTag(char* error_msg)
{
	char* fun = "ReadTourPlanTag";

	int  rc = OK;
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "select ");
	strcat(str, "tourplantag.idfnr, tourplantag.vertriebszentrumnr, tourplantag.datumkommi, tourplantag.tourid, tourplantag.plannedcall, tourplantag.bemerkungen ");
	strcat(str, "from tourplantag ");
	strcat(str, "inner join tourdetails on tourplantag.vertriebszentrumnr = tourdetails.branchno and tourplantag.tourid = tourdetails.tourid ");
	strcat(str, "where tourplantag.vertriebszentrumnr = ? and tourplantag.datumkommi = ? and tourplantag.plannedcall>0 and tourdetails.ispseudotour=0 ");
	
	exec sql prepare select_tourplantag from : str;
	ERROR_MSG("prepare select_tourplantag")
	exec sql declare objSelectTourPlanTag cursor with hold for select_tourplantag;

	
	PrintMsg(fun, "ReadTourPlanTag beendet", HINW, rc);

	return OK;
}

/***** START LOADING ************************************/
int PrepareTagPlan(char* error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char* fun = "PrepareTagPlan";

	exec sql begin declare section;
		char str[2048];
	exec sql end declare section;

	strcpy(str, "select ");
	strcat(str, "idfnr,filialnr,datum,rufzeit ");
	strcat(str, "from ");
	strcat(str, "tagplan where filialnr = ? and idfnr = ? and datum = ? and rufzeit = ? ");
	strcat(str, "for update ");
	
	exec sql prepare select_tagplan from : str;
	ERROR_MSG("prepare select_tagplan")
	exec sql declare objSelectTagPlan cursor with hold for select_tagplan;


	strcpy(str, "update tagplan set ");
	strcat(str, "rufzeit = ? , filialnr = ? , idfnr = ? , datum = ? ");
	strcat(str, " where current of objSelectTagPlan ");

	exec sql prepare upd_tagplan from : str;
	ERROR_MSG("prepare upd_tagplan")



	strcpy(str, "insert into tagplan (");
	strcat(str, "filialnr, ");
	strcat(str, "idfnr, ");
	strcat(str, "datum, ");
	strcat(str, "rufzeit, ");
	strcat(str, "lfdaktion, ");
	strcat(str, "prioritaet, ");
	strcat(str, "wochentag, ");
	strcat(str, "poolid, ");
	strcat(str, "anrufart, ");
	strcat(str, "manuell, ");
	strcat(str, "stagrueckruf, ");
	strcat(str, "telrueckrufnr, ");
	strcat(str, "zugriff, ");
	strcat(str, "bemerkung, ");
	strcat(str, "callinfo ");
	strcat(str, ") values ");
	strcat(str, "( ?,?,?");
	strcat(str, ",?,?,?,?,?,?,?,?,?,?,?,?");
	strcat(str, ")");

	exec sql prepare ins_tagplan from : str;
	ERROR_MSG("prepare ins_tagplan")

    PrintMsg(fun, "PrepareTagPlan beendet", HINW, rc);	
	
	return rc;
}

int PrepareTagPlanEreignis(char* error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char* fun = "PrepareTagPlanEreignis";

	exec sql begin declare section;
		char str[2048];
	exec sql end declare section;

	strcpy(str, "select ");
	strcat(str, "idfnr,filialnr,datum,rufzeit ");
	strcat(str, "from ");
	strcat(str, "tagplanereignis where filialnr = ? and idfnr = ? and datum = ? and rufzeit = ? ");
	strcat(str, "for update ");
	
	exec sql prepare select_tagplanereignis from : str;
	ERROR_MSG("prepare select_tagplanEreignis")
	exec sql declare objSelectTagPlanEreignis cursor with hold for select_tagplanereignis;


	strcpy(str, "update tagplanereignis set ");
	strcat(str, "rufzeit = ? , filialnr = ? , idfnr = ? , datum = ? ");
	strcat(str, " where current of objSelectTagPlanEreignis ");

	exec sql prepare upd_tagplanereignis from : str;
	ERROR_MSG("prepare upd_tagplanereignis")



	strcpy(str, "insert into tagplanereignis (");
	strcat(str, "datum, ");
	strcat(str, "rufzeit, ");
	strcat(str, "idfnr, ");
	strcat(str, "lfdaktion, ");
	strcat(str, "status, "); 
	strcat(str, "statusanrufsatz, "); 
	strcat(str, "statusverbindung, "); 
	strcat(str, "loeschgrund, "); 
	strcat(str, "rufzeitgeaendert, "); 
	strcat(str, "zeit, "); 
	strcat(str, "uid, "); 
	strcat(str, "bemerkung, ");
	strcat(str, "filialnr ");
	strcat(str, ") values ");
	strcat(str, "( ?,?,?");
	strcat(str, ",?,?,?,?,?,?,?,?,?,?");
	strcat(str, ")");

	exec sql prepare ins_tagplanereignis from : str;
	ERROR_MSG("prepare ins_tagplanereignis")

    PrintMsg(fun, "PrepareTagPlanereignis beendet", HINW, rc);	
	
	return rc;
}


int ExecuteTourPlanTag(char* error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	
	char* fun = "ExecuteTourPlanTag";
	
	exec sql open objSelectTourPlanTag using 
	:sBranchno, 
	:currentDate
	;
	
	ERROR_MSG("open objSelectTourPlanTag")
	
	EXEC SQL begin work;
	ERROR_MSG("Begin Work")

	for (;; )
	{

		exec sql fetch objSelectTourPlanTag into : structTPT;
		ERROR_MSG("fetch objSelectTourPlanTag")
		if (NOTFOUND) break;

		if (zaehler++ % M_DURCHLAUF_COMMIT == 0)
		{
			EXEC SQL commit work;
			ERROR_MSG("Commit Work")

			EXEC SQL begin work;
			ERROR_MSG("Begin Work")
		}

		if ((rc = PopulateTagPlan(error_msg)) < 0)
		{
			PrintMsg(fun, error_msg, FEHL, ERROR);
			return ERROR;
		}
		//else if (explain == YES)
			//if (zaehler > 5000) break;   /* Nur 5000 Saetze verarbeiten */
		
		
		if ((rc = PopulateTagPlanEreignis(error_msg)) < 0)
		{
			PrintMsg(fun, error_msg, FEHL, ERROR);
			return ERROR;
		}
		//else if (explain == YES)
			//if (zaehler > 5000) break;   /* Nur 5000 Saetze verarbeiten */

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG("Commit Work")

}

int PopulateTagPlanEreignis(char* error_msg)
{
	char* fun = "PopulateTagPlanEreignis";
	int  rc = OK;

	rufzeit = atol(structTPT.tourid)/100;
	if(structTPT.plannedcall > 0)
	{
		AllgAddTime (rufzeit*100, (structTPT.plannedcall*(-100)), &rufzeit);
		rufzeit = rufzeit/100;	
	}
	
	exec sql open objSelectTagPlanEreignis
		using
		: sBranchno,
		: structTPT.idfnr,
		: currentDate,
		: rufzeit
		;
	ERROR_MSG("open objSelectTagPlanEreignis")
	

	lfdaktion = 0;
	status = 7;
	statusanrufsatz = 0;
	statusverbindung = 0;
	loeschgrund = 0;
	uid = 0;
	
	
	exec sql fetch objSelectTagPlanEreignis;
	ERROR_MSG("fetch objSelectTagPlanEreignis")
	if (sqlca.sqlcode == 100)
	{
		//insert
			EXEC SQL EXECUTE ins_tagplanereignis 
			USING
			
				:structTPT.datumkommi, 	
				:rufzeit, 				
				:structTPT.idfnr,		
				:lfdaktion, 			
				:status, 				
				:statusanrufsatz, 		
				:statusverbindung,		
				:loeschgrund,			
				:rufzeit,		
				:rufzeit,		
				:uid,					
				:structTPT.bemerkungen, 	
				:structTPT.vertriebszentrumnr; 
			
			ERROR_MSG("Failure in execute ins_tagplanereignis");		
	}
	else
	{
		EXEC SQL EXECUTE upd_tagplanereignis
		USING
		:rufzeit,
		:structTPT.vertriebszentrumnr,
		:structTPT.idfnr,
		:currentDate
		;
		ERROR_MSG("Failure in execute upd_tagplanereignis");
	}
	return OK;
	
	
}

int PopulateTagPlan(char* error_msg)
{
	char* fun = "PopulateTagPlan";
	int  rc = OK;

	rufzeit = atol(structTPT.tourid)/100;
	if(structTPT.plannedcall > 0)
	{
		AllgAddTime (rufzeit*100, (structTPT.plannedcall*(-100)), &rufzeit);
		rufzeit = rufzeit/100;	
	}
	
	exec sql open objSelectTagPlan
		using
		: sBranchno,
		: structTPT.idfnr,
		: currentDate,
		: rufzeit
		;
	ERROR_MSG("open objSelectTagPlan")

	

	lfdaktion = 0;
	prioritaet = 40;
	lWeekDay = AllgGetWeekDay(structTPT.datumkommi,error_msg);
	sprintf(spWd, "%d ", lWeekDay);
	poolid = 0;
	stagrueckruf = 0;
	zugriff = 0;
	
	exec sql fetch objSelectTagPlan;
	ERROR_MSG("fetch objSelectTagPlan")
	if (sqlca.sqlcode == 100)
	{
		//insert
			EXEC SQL EXECUTE ins_tagplan 
			USING
				:structTPT.vertriebszentrumnr,
				:structTPT.idfnr,
				:structTPT.datumkommi,
				:rufzeit,
				:lfdaktion,
				:prioritaet , 
				:spWd,
				: poolid,
				: anrufart,
				: manuell,
				: stagrueckruf,
				: telrueckrufnr,
				: zugriff, 
				:structTPT.bemerkungen,
				: callinfo;

			ERROR_MSG("Failure in execute ins_tagplan");
			
	}
	else
	{
		EXEC SQL EXECUTE upd_tagplan
		USING
		:rufzeit,
		:structTPT.vertriebszentrumnr,
		:structTPT.idfnr,
		:currentDate
		;
		ERROR_MSG("Failure in execute upd_tagplan");
	}
	return OK;
}


/***** PRINT-MSG ************************************************************/

void PrintMsg(char* fun, char* error_msg, char mld, int rc)
{
	FILE* fp;
	struct tm* localtime();
	struct tm* zeit;
	long hour1;
	pid_t pid;
	long time();
	char logFile[L_TEXT];
	char* env;

	if (rc > INSERT)
		return;

	pid = getpid();
	hour1 = time(&hour1);
	zeit = localtime(&hour1);

	/*	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) );	*/
	env = getenv("LOG_PATH");
	if (env == NULL)
		env = ".";
	sprintf(logFile, "%s/wws.log", env);

	if ((fp = fopen(logFile, "a")) == (FILE*)0)
		return;

	fprintf(fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.13s %s %s\n",
		mld,
		99,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year + 1900) % 100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		PROJECTNAME,
		fun,
		error_msg);

	fclose(fp);
}


int OpenDatabase()
{
	char error_msg[L_TEXT];
	char* fun = "OpenDatabase";

	EXEC SQL DATABASE :szDatabase;
	ERROR_MSG("Fehler oeffnen DB")

	EXEC SQL SET LOCK MODE TO WAIT 20;
	ERROR_MSG("Set LockMode to Wait")

	EXEC SQL SET ISOLATION TO DIRTY READ;
	ERROR_MSG("Set Isolation to Dirty Read")
/*
	if (sExplain == TRUE)
	{
		EXEC SQL SET EXPLAIN ON;
		ERROR_MSG("SET EXPLAIN ON")
	}
*/
	return OK;
}

/***** CLOSE-DATABASE *******************************************************/

int CloseDatabase(void)
{
	char error_msg[L_TEXT];
	char* fun = "CloseDatabase";

	//exec sql close :szDatabase;
	EXEC SQL CLOSE database;
	ERROR_MSG("failure in Close DB")

		return OK;
}

void getCurrentDate(char* datebuf, int buflen)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(datebuf, buflen, "%Y%m%d", timeinfo);
}

/***** ENDE *****************************************************************/

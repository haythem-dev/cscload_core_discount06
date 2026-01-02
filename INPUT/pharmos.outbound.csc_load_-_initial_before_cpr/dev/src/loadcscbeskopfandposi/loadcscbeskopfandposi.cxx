/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

/* ToDo Programmname */
#define PROJECTNAME	 "loadcscbeskopfandposi"

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
char currentDate[LEN_FILE_DATEFROM + 1];

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
short sBranchno = 0;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main(int, char**);
void PrintMsg(char* fun, char* error_msg, char mld, int rc);
void WriteLogInfo(char* error_msg, char mld, int rc);
int FillBeskopfIntoCscBeskopf(char* error_msg);
int FillBesposiIntoCscBesposi(char* error_msg);
int PrepareTempTabletoReadBeskopf(char* error_msg);
int PrepareTempTableToReadBesposi(char* error_msg);
int DeleteCscBeskopf(char* error_msg);
int DeleteCscBesposi(char* error_msg);
int CleanupTempTables(char* error_msg);
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

	sprintf(indatenbank, "%s", INDATABASE);
	sprintf(outdatenbank, "%s", OUTDATABASE);

	strcpy(start_msg, "gestartet mit:");
	skip = NO;

	sprintf(start_msg, "%d %s %s %s %s %s %s %s", argc, argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
    PrintMsg(fun, start_msg, HINW, 0);

	for (i = 1; i < argc; i++)
	{

		schalter = argv[i];
		if (!strcmp(schalter, "-dbin"))
		{
			strcat(start_msg, " -dbin");
			i++;
			sprintf(indatenbank, "%s", argv[i]);
			sprintf(start_msg, "%s %s", start_msg, argv[i]);
		}
		else if (!strcmp(schalter, "-dbout"))
		{
			strcat(start_msg, " -dbout");
			i++;
			sprintf(outdatenbank, "%s", argv[i]);
			sprintf(start_msg, "%s %s", start_msg, argv[i]);
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

	//if ( argc == 1 || skip == ERROR )
	if ( argc == 1 )
	{
      printf("  usage: %s\n\t"
				" { -dbin datenbankname <Datenbankname Eingabe> }\n\t"
				" { -dbout datenbankname <Datenbankname Ausgabe> }\n\t"
				" { -branchno filialnr }\n\t"
				, argv[0]);
			return 1;
     }
	 
	// get current date to use as default value for DATEFROM
	getCurrentDate(currentDate, LEN_FILE_DATEFROM + 1);

	exec sql database : outdatenbank;
	ERROR_MSG("Fehler oeffnen DB")

	exec sql set lock mode to wait 20;
	ERROR_MSG("Set LockMode to Wait")

	exec sql set isolation to dirty read;
	ERROR_MSG("Set Isolation to Dirty Read")

	PrintMsg(fun, start_msg, HINW, 0);
	
	if (PrepareTempTabletoReadBeskopf(error_msg) != OK)
	{
		PrintMsg(fun, "mit Fehler beendet PrepareTempTabletoReadBeskopf", FEHL, rc);
		return 8;
	}

	if ((rc = FillBeskopfIntoCscBeskopf(error_msg)) != 0)
	{
		PrintMsg(fun, "mit Fehler beendet FillBeskopfIntoCscBeskopf", FEHL, rc);
		return 9;
	}
	
	if (PrepareTempTableToReadBesposi(error_msg) != OK)
	{
		PrintMsg(fun, "mit Fehler beendet PrepareTempTableToReadBesposi", FEHL, rc);
		return 8;
	}

	if ((rc = FillBesposiIntoCscBesposi(error_msg)) != 0)
	{
		PrintMsg(fun, "mit Fehler beendet FillBesposiIntoCscBesposi", FEHL, rc);
		return 9;
	}	
	
	if ((rc = DeleteCscBeskopf(error_msg)) != 0)
	{
		PrintMsg(fun, "mit Fehler beendet DeleteCscBeskopf", FEHL, rc);
		return 10;	
	}
	
	if ((rc = DeleteCscBesposi(error_msg)) != 0)
	{
		PrintMsg(fun, "mit Fehler beendet DeleteCscBesposi", FEHL, rc);
		return 10;	
	}

	CleanupTempTables(error_msg);

	PrintMsg(fun, "Besposi korrekt beendet", HINW, rc);
	
	return 0;

}

int CleanupTempTables(char* error_msg)
{
	char* fun = "CleanupTempTables";

	EXEC SQL TRUNCATE TABLE tmp_beskopf;
	ERROR_MSG("truncate table tmp_beskopf");
	
	EXEC SQL TRUNCATE TABLE tmp_besposi;
	ERROR_MSG("truncate table tmp_besposi");
	
	return 0;
}


/*** PREPARE-TempTableToRead Beskopf ************************************************/
int PrepareTempTabletoReadBeskopf(char* error_msg)
{
	char* fun = "PrepareTempTabletoReadBeskopf";

	int  rc = OK;
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	EXEC SQL CREATE TEMP TABLE tmp_beskopf(
	filialnr integer, 
	bestell_nr integer,
	bestell_art char(1), 
	besla_nr integer , 
	datum_bestell integer,
	best_wirksam char(1) , 
	status_akt char(1) , 
	status_neu char(1) , 
	bestell_summe decimal, 
	datum_we integer, 
	datum_we_soll integer,
	besla_mc char(15) ,
	datum_storno integer,
	datum_ls integer,
	freetext char(255) , 
	datum_aender integer);
	ERROR_MSG("create temp table tmp_beskopf");


	strcpy(str, "insert into tmp_beskopf select ");
	strcat(str, "filialnr, ");
	strcat(str, "bestell_nr, ");
	strcat(str, "bestell_art, ");
	strcat(str, "besla_nr, ");
	strcat(str, "datum_bestell, ");
	strcat(str, "best_wirksam, ");
	strcat(str, "status_akt, ");
	strcat(str, "status_neu, ");
	strcat(str, "bestell_summe, ");
	strcat(str, "datum_we, ");
	strcat(str, "datum_we_soll, ");
	strcat(str, "besla_mc, ");
	strcat(str, "datum_storno, ");
	strcat(str, "datum_ls, ");
	strcat(str, "freetext, ");
	strcat(str, "datum_aender ");
	strcat(str, "from  ");
	strcat(str, indatenbank);
	strcat(str, ":beskopf ");
	strcat(str, "where filialnr = ? and datum_aender >=  (select NVL(max(lastupdatedate), 0) as mydate from cscbeskopf where filialnr = ?)");
	
	EXEC SQL PREPARE insert_beskopf from : str;
	ERROR_MSG("prepare insert_beskopf")
	
	PrintMsg(fun, "PrepareTempTabletoReadBeskopf beendet", HINW, rc);

	return OK;
}

/***** START LOADING ************************************/
int FillBeskopfIntoCscBeskopf(char* error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char* fun = "FillBeskopfIntoCscBeskopf";

	exec sql begin declare section;
		char str[2048];
	exec sql end declare section;

	EXEC SQL EXECUTE insert_beskopf using :sBranchno, :sBranchno;	
	ERROR_MSG("open insert_beskopf")
	
	
	strcpy( str, "MERGE INTO cscbeskopf cbk ");
	strcat (str, "using tmp_beskopf tbk ");
	strcat (str, "on cbk.filialnr = tbk.filialnr AND cbk.bestell_nr = tbk.bestell_nr ");
	strcat (str, "WHEN MATCHED THEN ");
	strcat (str, "UPDATE SET cbk.bestell_art = tbk.bestell_art, ");
	strcat (str, "cbk.besla_nr = tbk.besla_nr, ");
	strcat (str, "cbk.datum_bestell = tbk.datum_bestell, ");
	strcat (str, "cbk.best_wirksam = tbk.best_wirksam, ");
	strcat (str, "cbk.status_akt = tbk.status_akt, ");
	strcat (str, "cbk.status_neu = tbk.status_neu, ");
	strcat (str, "cbk.bestell_summe = tbk.bestell_summe, ");
	strcat (str, "cbk.datum_we = tbk.datum_we, ");
	strcat (str, "cbk.datum_we_soll = tbk.datum_we_soll, ");
	strcat (str, "cbk.besla_mc = tbk.besla_mc, ");
	strcat (str, "cbk.datum_storno = tbk.datum_storno, ");
	strcat (str, "cbk.datum_ls = tbk.datum_ls, ");
	strcat (str, "cbk.freetext = tbk.freetext, ");
	strcat (str, "cbk.datum_aender = tbk.datum_aender, ");
	strcat (str, "cbk.lastupdatedate = ");
	strcat (str, currentDate); 
	strcat (str, " WHEN NOT MATCHED THEN  ");
	strcat (str, "INSERT (  ");
	strcat (str, "cbk.filialnr,  ");
	strcat (str, "cbk.bestell_nr,  ");
	strcat (str, "cbk.bestell_art,  ");
	strcat (str, "cbk.besla_nr,  ");
	strcat (str, "cbk.datum_bestell,  ");
	strcat (str, "cbk.best_wirksam,  ");
	strcat (str, "cbk.status_akt,  ");
	strcat (str, "cbk.status_neu,  ");
	strcat (str, "cbk.bestell_summe,  ");
	strcat (str, "cbk.datum_we,  ");
	strcat (str, "cbk.datum_we_soll,  ");
	strcat (str, "cbk.besla_mc,  ");
	strcat (str, "cbk.datum_storno,  ");
	strcat (str, "cbk.datum_ls,  ");
	strcat (str, "cbk.freetext,  ");
	strcat (str, "cbk.datum_aender,  ");
	strcat (str, "cbk.lastupdatedate) "); 
	strcat (str, "values ( tbk.filialnr,tbk.bestell_nr,tbk.bestell_art,tbk.besla_nr,tbk.datum_bestell,tbk.best_wirksam, ");
	strcat (str, "tbk.status_akt,tbk.status_neu,tbk.bestell_summe,tbk.datum_we,tbk.datum_we_soll,tbk.besla_mc, ");
	strcat (str, "tbk.datum_storno,tbk.datum_ls,tbk.freetext,tbk.datum_aender,");
	strcat(str, currentDate);
	strcat(str, ")");
	
	
	EXEC SQL PREPARE Upd_Ins_cscbeskopf from : str;	
	ERROR_MSG("PREPARE Upd_Ins_cscbeskopf")
	
	EXEC SQL EXECUTE Upd_Ins_cscbeskopf;
	ERROR_MSG("EXECUTE Upd_Ins_cscbeskopf")
	
	PrintMsg(fun, "FillBeskopfIntoCscBeskopf beendet", HINW, rc);
	
	return rc;
}

/*** PREPARE-Read Besposi ************************************************/
int PrepareTempTableToReadBesposi(char* error_msg)
{
	char* fun = "PrepareTempTableToReadBesposi";

	int  rc = OK;
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	EXEC SQL CREATE TEMP TABLE tmp_besposi(
	filialnr integer, 
	bestell_nr integer,
	artikel_nr integer ,
	article_code char(25), 
	code_type integer,
	menge_bestell integer,
	menge_ls integer, 
	best_wirksam char(1) , 
	status char(1) , 
	artikel_name char(30) , 
	datum_aender integer);
	ERROR_MSG("create temp table tmp_besposi");


	strcpy(str, "insert into tmp_besposi select ");
	strcat(str, "filialnr, ");
	strcat(str, "bestell_nr, ");
	strcat(str, "artikel_nr, ");
	strcat(str, "article_code, ");
	strcat(str, "code_type, ");
	strcat(str, "menge_bestell, ");
	strcat(str, "menge_ls, ");
	strcat(str, "best_wirksam, ");
	strcat(str, "status, ");
	strcat(str, "artikel_name, ");
	strcat(str, "datum_aender ");
	strcat(str, "from  ");
	strcat(str, indatenbank);
	strcat(str, ":besposi ");
	strcat(str, "where filialnr = ? and datum_aender >=  (select NVL(max(lastupdatedate), 0) as mydate from cscbesposi where filialnr = ?)");
	
	EXEC SQL PREPARE insert_besposi from : str;
	ERROR_MSG("PREPARE insert_besposi")
	
	PrintMsg(fun, "PrepareTempTableToReadBesposi beendet", HINW, rc);

	return OK;
}

int FillBesposiIntoCscBesposi(char* error_msg)
{
	int  rc = OK;
	char* fun = "FillBesposiIntoCscBesposi";

	exec sql begin declare section;
		char str[2048];
	exec sql end declare section;

	EXEC SQL EXECUTE insert_besposi using :sBranchno, :sBranchno;	
	ERROR_MSG("open insert_besposi")


	strcpy( str, "MERGE INTO cscbesposi cbp ");
	strcat (str, "using tmp_besposi tbp ");
	strcat (str, "on cbp.filialnr = tbp.filialnr AND cbp.bestell_nr = tbp.bestell_nr AND cbp.artikel_nr = tbp.artikel_nr ");
	strcat (str, "WHEN MATCHED THEN ");
	strcat (str, "UPDATE SET cbp.article_code = tbp.article_code, ");
	strcat (str, "cbp.code_type = tbp.code_type, ");
	strcat (str, "cbp.menge_bestell = tbp.menge_bestell, ");
	strcat (str, "cbp.menge_ls = tbp.menge_ls, ");
	strcat (str, "cbp.best_wirksam = tbp.best_wirksam, ");
	strcat (str, "cbp.status = tbp.status, ");
	strcat (str, "cbp.artikel_name = tbp.artikel_name, ");
	strcat (str, "cbp.datum_aender = tbp.datum_aender, ");
	strcat (str, "cbp.lastupdatedate = ");
	strcat (str, currentDate); 
	strcat (str, " WHEN NOT MATCHED THEN  ");
	strcat (str, "INSERT (  ");
	strcat (str, "cbp.filialnr,  ");
	strcat (str, "cbp.bestell_nr,  ");
	strcat (str, "cbp.artikel_nr,  ");
	strcat (str, "cbp.article_code,  ");
	strcat (str, "cbp.code_type,  ");
	strcat (str, "cbp.menge_bestell,  ");
	strcat (str, "cbp.menge_ls,  ");
	strcat (str, "cbp.best_wirksam,  ");
	strcat (str, "cbp.status,  ");
	strcat (str, "cbp.artikel_name,  ");
	strcat (str, "cbp.datum_aender,  ");
	strcat (str, "cbp.lastupdatedate) "); 
	strcat (str, "values ( tbp.filialnr, tbp.bestell_nr, tbp.artikel_nr, tbp.article_code, tbp.code_type, tbp.menge_bestell, ");
	strcat (str, "tbp.menge_ls, tbp.best_wirksam, tbp.status, tbp.artikel_name, tbp.datum_aender, ");
	strcat(str, currentDate);
	strcat(str, ")");

	EXEC SQL prepare Upd_Ins_cscbesposi from : str;	
	ERROR_MSG("Prepare Upd_Ins_cscbesposi")
	
	EXEC SQL EXECUTE Upd_Ins_cscbesposi;
	ERROR_MSG("EXECUTE Upd_Ins_cscbesposi")
	
	PrintMsg(fun, "FillBesposiIntoCscBesposi beendet", HINW, rc);

	return rc;
}



/*** LOESCHEN NICHT GEAENDERTE SAETZE ************************************************/

int DeleteCscBeskopf(char* error_msg)
{
	char* fun = "DeleteCscBeskopf";
	int i;
	int  rc = OK;
	//char start_msg[256];
	
	exec sql begin declare section;
	char str[2048];
	char str1[2048];
	exec sql end declare section;
	/*
	strcpy(str, "select filialnr, bestell_nr from cscbeskopf where bestell_nr in ( select  c.bestell_nr from cscbeskopf c "); strcat(str, "left outer join beskopf o on (c.filialnr = o.filialnr and c.bestell_nr = o.bestell_nr) where c.filialnr = ? "); strcat(str, "and o.bestell_nr is null) for update" );
	*/
	strcpy(str, "select filialnr, bestell_nr from cscbeskopf where bestell_nr in ( ");
	strcat(str, "select  cbk.bestell_nr from cscbeskopf cbk left outer join ");
	strcat(str, indatenbank);
	strcat(str, ":beskopf bk on (cbk.filialnr = bk.filialnr and cbk.bestell_nr = bk.bestell_nr) where cbk.filialnr = ? and bk.bestell_nr is null) and filialnr in ( ");
	strcat(str, "select  cbk.filialnr from cscbeskopf cbk left outer join ");
	strcat(str, indatenbank);
	strcat(str, ":beskopf bk on (cbk.filialnr = bk.filialnr and cbk.bestell_nr = bk.bestell_nr) where cbk.filialnr = ? and bk.bestell_nr is null) for update");
	
	
	exec sql prepare selectDel_cscbeskopf from : str;
	ERROR_MSG("prepare selectDel_cscbeskopf")
	exec sql declare objSelDelcscbeskopf cursor with hold for selectDel_cscbeskopf;

	strcpy(str1, "delete from cscbeskopf where current of objSelDelcscbeskopf");
	
	exec sql prepare delete_cscbeskopf from : str1;
	ERROR_MSG("prepare delete_cscbeskopf")

	exec sql open objSelDelcscbeskopf using : sBranchno, : sBranchno;
	ERROR_MSG("open objSelDelcscbeskopf")

	EXEC SQL begin work;
	ERROR_MSG("Begin Work0:")

		for (i = 1;; i++)
		{
			if (i % 50 == 0)
			{
				exec sql commit work;
				ERROR_MSG("Commit Work:")
				exec sql begin work;
				ERROR_MSG("begin Work:")
			}

			exec sql fetch objSelDelcscbeskopf;
			if (sqlca.sqlcode == 100) 
				break;
			ERROR_MSG("fetch objSelDelcscbeskopf")

			exec sql execute delete_cscbeskopf;
			ERROR_MSG("execute delete_cscbeskopf")
				zaehlerDel++;

		}
	EXEC SQL commit work;
	ERROR_MSG("Commit Work0:")

	exec sql close objSelDelcscbeskopf;
	ERROR_MSG("close objSelDelcscbeskopf")
	
	PrintMsg(fun, "DeleteCscBeskopf beendet", HINW, rc);

	return rc;
}

int DeleteCscBesposi(char* error_msg)
{
	char* fun = "DeleteCscBesposi";
	int i;
	int  rc = OK;
	//char start_msg[256];
	
	exec sql begin declare section;
	char str[2048];
	char str1[2048];
	exec sql end declare section;
	/*
	strcpy(str, "select filialnr, bestell_nr, artikel_nr from cscbesposi where bestell_nr in ( select  c.bestell_nr from cscbesposi c "); 
	strcat(str, "left outer join besposi o on (c.filialnr = o.filialnr and c.bestell_nr = o.bestell_nr and c.artikel_nr = o.artikel_nr) where c.filialnr = ? "); 
	strcat(str, "and o.bestell_nr is null) for update" );
	*/
	strcpy(str, "select filialnr, bestell_nr, artikel_nr from cscbesposi where bestell_nr in ( ");
	strcat(str, "select  cbp.bestell_nr from cscbesposi cbp left outer join ");
	strcat(str, indatenbank);
	strcat(str,":besposi bpo on (cbp.filialnr = bpo.filialnr and cbp.bestell_nr = bpo.bestell_nr and cbp.artikel_nr = bpo.artikel_nr) where cbp.filialnr = ? and bpo.bestell_nr is null) and artikel_nr in ( ");
	strcat(str, "select  cbp.artikel_nr from cscbesposi cbp left outer join ");
	strcat(str, indatenbank);
	strcat(str, ":besposi bpo on (cbp.filialnr = bpo.filialnr and cbp.bestell_nr = bpo.bestell_nr and cbp.artikel_nr = bpo.artikel_nr) where cbp.filialnr = ? and bpo.bestell_nr is null) and filialnr in ( ");
	strcat(str, "select  cbp.filialnr from cscbesposi cbp left outer join ");
	strcat(str, indatenbank);
	strcat(str, ":besposi bpo on (cbp.filialnr = bpo.filialnr and cbp.bestell_nr = bpo.bestell_nr and cbp.artikel_nr = bpo.artikel_nr) where cbp.filialnr = ? and bpo.bestell_nr is null) for update");
	
	exec sql prepare selectDel_cscbesposi from : str;
	ERROR_MSG("prepare selectDel_cscbesposi")
	exec sql declare objSelDelcscbesposi cursor with hold for selectDel_cscbesposi;

	strcpy(str1, "delete from cscbesposi where current of objSelDelcscbesposi");
	
	exec sql prepare delete_cscbesposi from : str1;
	ERROR_MSG("prepare delete_cscbesposi")

	exec sql open objSelDelcscbesposi using : sBranchno, : sBranchno, : sBranchno;
	ERROR_MSG("open objSelDelcscbesposi")

	EXEC SQL begin work;
	ERROR_MSG("Begin Work0:")

		for (i = 1;; i++)
		{
			if (i % 50 == 0)
			{
				exec sql commit work;
				ERROR_MSG("Commit Work:")
				exec sql begin work;
				ERROR_MSG("begin Work:")
			}

			exec sql fetch objSelDelcscbesposi;
			if (sqlca.sqlcode == 100) break;
			ERROR_MSG("fetch objSelDelcscbesposi")

			exec sql execute delete_cscbesposi;
			ERROR_MSG("execute delete_cscbesposi")
				zaehlerDel++;
		}
	EXEC SQL commit work;
	ERROR_MSG("Commit Work0:")

	exec sql close objSelDelcscbesposi;
	ERROR_MSG("close objSelDelcscbesposi")
	
	PrintMsg(fun, "DeleteCscBesposi beendet", HINW, rc);

	return rc;
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

/***** CLOSE-DATABASE *******************************************************/

int CloseDatabase(void)
{
	char error_msg[L_TEXT];
	char* fun = "CloseDatabase";

	exec sql close database;
	ERROR_MSG("Close DB")

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

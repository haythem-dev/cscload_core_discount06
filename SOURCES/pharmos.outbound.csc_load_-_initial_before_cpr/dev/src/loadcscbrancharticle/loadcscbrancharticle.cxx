/*##################################################################################
 *    main module: loadcscbrancharticle.ecc                                                             
 *         Source: loadcscbrancharticle.cxx                                                             
 *          Autor: Haythem Ben-Abdelaziz                                              
 *        Created: 12.10.2024                                                                   
 *  Last Modified: 13.01.2025                                                                    
 *       language: C                                                                            
 *      Developed: manual                                                                       
 *           Task: transfer artikelf table from inbound to cscbrancharticle table in outbound                
 *          Usage: loadcscbrancharticle.sh -branchno <brchno> -dbin <inbounddb> -dbout <outbounddb>
 *  
 *#################################################################################*/

/* INCLUDE ********************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

/* ToDo Programmname */
#define PROJECTNAME	 "loadcscbrancharticle"

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



/*** DEFINE ***************************************************************/
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
#define LEN_FILE_DATEFROM  8

/*** GLOBALS ***************************************************************/

static char error_msg[81];
char log_file[300 + 1];
char currentDate[LEN_FILE_DATEFROM + 1];

exec sql begin declare section;
char g_indatabase[60];
char g_outdatabase[60];
short g_sBranchno = 0;
exec sql end declare section;

/***** DECLARATION **********************************************************/

int main(int, char**);
void PrintMsg(char* fun, char* error_msg, char mld, int rc);
void WriteLogInfo(char* error_msg, char mld, int rc);
int FillartikelfIntoCscBranchArticle(char* error_msg);
int PrepareTempTabletoReadartikelf(char* error_msg);
int DeleteCscBranchArticle(char* error_msg);
int CleanupTempTables(char* error_msg);
int CloseDatabase(void);
void getCurrentDate(char* datebuf, int buflen);
/***** MAIN *****************************************************************/

int main(int argc, char** argv)
{
	char  error_msg[181];
	char* parameter;
	int   skip;
	int   i;
	char* fun = "Main";
	char* LOG_FILE = "loadcscbrancharticle.log";
	char* LOG_PATH;
	char  logpath[256 + 1];
	int   rc;
	int   status = 0;
	char  start_msg[255];

	sprintf(g_indatabase, "%s", INDATABASE);
	sprintf(g_outdatabase, "%s", OUTDATABASE);

	strcpy(start_msg, "started with:");
	skip = NO;

	sprintf(start_msg, "%d %s %s %s %s %s %s %s", argc, argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
    PrintMsg(fun, start_msg, HINW, 0);

	for (i = 1; i < argc; i++)
	{
		parameter = argv[i];
		if (!strcmp(parameter, "-dbin"))
		{
			strcat(start_msg, " -dbin");
			i++;
			sprintf(g_indatabase, "%s", argv[i]);
			sprintf(start_msg, "%s %s", start_msg, argv[i]);
		}
		else if (!strcmp(parameter, "-dbout"))
		{
			strcat(start_msg, " -dbout");
			i++;
			sprintf(g_outdatabase, "%s", argv[i]);
			sprintf(start_msg, "%s %s", start_msg, argv[i]);
		}
		else if (!strcmp(parameter, "-branchno"))
		{
			strcat(start_msg, " -branchno");
			i++;
			g_sBranchno = atoi(argv[i]);
			sprintf(start_msg, "%s %s", start_msg, argv[i]);
		}
		else if (!strcmp(parameter, "-version"))
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
				" { -dbin databasename <databasename input> }\n\t"
				" { -dbout databasename <databasename output> }\n\t"
				" { -branchno branchnumber }\n\t"
				, argv[0]);
			return 1;
     }
	 
	// get current date to use as default value for DATEFROM
	getCurrentDate(currentDate, LEN_FILE_DATEFROM + 1);

	exec sql database : g_outdatabase;
	ERROR_MSG("Fehler oeffnen DB")

	exec sql set lock mode to wait 20;
	ERROR_MSG("Set LockMode to Wait")

	exec sql set isolation to dirty read;
	ERROR_MSG("Set Isolation to Dirty Read")

	PrintMsg(fun, start_msg, HINW, 0);
	
	if (PrepareTempTabletoReadartikelf(error_msg) != OK)
	{
		PrintMsg(fun, "ended with error PrepareTempTabletoReadartikelf", FEHL, rc);
		return 8;
	}

	if ((rc = FillartikelfIntoCscBranchArticle(error_msg)) != 0)
	{
		PrintMsg(fun, "ended with error FillartikelfIntoCscBranchArticle", FEHL, rc);
		return 9;
	}
	
	if ((rc = DeleteCscBranchArticle(error_msg)) != 0)
	{
		PrintMsg(fun, "ended with error DeleteCscBranchArticle", FEHL, rc);
		return 10;	
	}

	CleanupTempTables(error_msg);

	PrintMsg(fun, "ended correctly", HINW, rc);
	
	return 0;
}

int CleanupTempTables(char* error_msg)
{
	char* fun = "CleanupTempTables";

	EXEC SQL TRUNCATE TABLE tmp_artikelf;
	ERROR_MSG("truncate table tmp_artikelf");
	
	return 0;
}

/*** PREPARE-TempTableToRead ArticlePrognosis ************************************************/
int PrepareTempTabletoReadartikelf(char* error_msg)
{
	char* fun = "PrepareTempTabletoReadartikelf";

	int  rc = OK;
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	EXEC SQL CREATE TEMP TABLE tmp_artikelf(
	filialnr integer, 
	artikel_nr integer,
	besla_nr integer, 
 	bestand_min integer,
	artikelaktiv char(1),
	lagerfachnr char(10),
	offene_bestmenge integer,
	datum_aender integer,
	openorderqty_noteffective integer);
	ERROR_MSG("create temp table tmp_artikelf");

	strcpy(str, "insert into tmp_artikelf select ");
	strcat(str, "filialnr, ");
	strcat(str, "artikel_nr, ");
	strcat(str, "besla_nr, ");
	strcat(str, "bestand_min, ");
	strcat(str, "artikelaktiv, ");
	strcat(str, "lagerfachnr, ");
	strcat(str, "offene_bestmenge, ");
	strcat(str, "datum_aender, ");
	strcat(str, "openorderqty_noteffective ");
	strcat(str, "from  ");
	strcat(str, g_indatabase);
	strcat(str, ":artikelf ");
	//strcat(str, "where filialnr = ? ");
	strcat(str, "where filialnr = ? and datum_aender >=  (select NVL(max(lastupdatedate), 0) as mydate from cscbrancharticle where filialnr = ?)");

	EXEC SQL PREPARE insert_artikelf from :str;
	ERROR_MSG("prepare insert_artikelf")
	
	PrintMsg(fun, "PrepareTempTabletoReadartikelf done", HINW, rc);

	return OK;
}

/***** START LOADING ************************************/
int FillartikelfIntoCscBranchArticle(char* error_msg)
{
	int  rc = OK;
	int  ende = NO;
	char* fun = "FillartikelfIntoCscBranchArticle";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	EXEC SQL EXECUTE insert_artikelf using :g_sBranchno, :g_sBranchno;	
	ERROR_MSG("open insert_artikelf")
	
	strcpy( str, "MERGE INTO cscbrancharticle cba ");
	strcat (str, "using tmp_artikelf taf ");
	strcat (str, "on cba.filialnr = taf.filialnr AND cba.artikel_nr = taf.artikel_nr ");
	strcat (str, "WHEN MATCHED THEN ");
	strcat (str, "UPDATE SET cba.besla_nr = taf.besla_nr, ");
	strcat (str, "cba.bestand_min = taf.bestand_min, ");
	strcat (str, "cba.artikelaktiv = taf.artikelaktiv, ");
	strcat (str, "cba.lagerfachnr = taf.lagerfachnr, ");
	strcat (str, "cba.offene_bestmenge = taf.offene_bestmenge, ");
	strcat (str, "cba.openorderqty_noteffective = taf.openorderqty_noteffective, ");
	strcat (str, "cba.lastupdatedate = ");
	strcat (str, currentDate); 
	strcat (str, " WHEN NOT MATCHED THEN  ");
	strcat (str, "INSERT (  ");
	strcat (str, "cba.filialnr,  ");
	strcat (str, "cba.artikel_nr,  ");
	strcat (str, "cba.besla_nr,  ");
	strcat (str, "cba.bestand_min,  ");
	strcat (str, "cba.artikelaktiv,  "); 
	strcat (str, "cba.lagerfachnr,  ");
	strcat (str, "cba.offene_bestmenge,  ");
	strcat (str, "cba.openorderqty_noteffective,  "); 
	strcat (str, "cba.lastupdatedate) "); 
	strcat (str, "values ( taf.filialnr,taf.artikel_nr,taf.besla_nr,taf.bestand_min,taf.artikelaktiv,taf.lagerfachnr,taf.offene_bestmenge,taf.openorderqty_noteffective, ");
	strcat(str, currentDate);
	strcat(str, ")");
	
	
	EXEC SQL PREPARE Upd_Ins_cscbrancharticle from :str;	
	ERROR_MSG("PREPARE Upd_Ins_cscbrancharticle")
	
	EXEC SQL EXECUTE Upd_Ins_cscbrancharticle;
	ERROR_MSG("EXECUTE Upd_Ins_cscbrancharticle")
	
	PrintMsg(fun, "FillartikelfIntoCscBranchArticle done", HINW, rc);
	
	return rc;
}


/*** LOESCHEN NICHT GEAENDERTE SAETZE ************************************************/

int DeleteCscBranchArticle(char* error_msg)
{
	char* fun = "DeleteCscBranchArticle";
	int i;
	int  rc = OK;
	//char start_msg[256];
	
	exec sql begin declare section;
	char str[2048];
	char str1[2048];
	exec sql end declare section;
	/*
	strcpy(str, "select filialnr, artikel_nr from cscbrancharticle where artikel_nr in ( select  c.artikel_nr from cscbrancharticle c "); strcat(str, "left outer join artikelf o on (c.filialnr = o.filialnr and c.artikel_nr = o.artikel_nr) where c.filialnr = ? "); strcat(str, "and o.artikel_nr is null) for update" );
	*/
	strcpy(str, "select filialnr, artikel_nr from cscbrancharticle where artikel_nr in ( ");
	strcat(str, "select  cba.artikel_nr from cscbrancharticle cba left outer join ");
	strcat(str, g_indatabase);
	strcat(str, ":artikelf af on (cba.filialnr = af.filialnr and cba.artikel_nr = af.artikel_nr) where cba.filialnr = ? and af.artikel_nr is null) and filialnr in ( ");
	strcat(str, "select  cba.filialnr from cscbrancharticle cba left outer join ");
	strcat(str, g_indatabase);
	strcat(str, ":artikelf af on (cba.filialnr = af.filialnr and cba.artikel_nr = af.artikel_nr) where cba.filialnr = ? and af.artikel_nr is null) for update");
	
	
	exec sql prepare selectDel_cscbrancharticle from :str;
	ERROR_MSG("prepare selectDel_cscbrancharticle")
	exec sql declare objSelDelcscbrancharticle cursor with hold for selectDel_cscbrancharticle;

	strcpy(str1, "delete from cscbrancharticle where current of objSelDelcscbrancharticle");
	
	exec sql prepare delete_cscbrancharticle from :str1;
	ERROR_MSG("prepare delete_cscbrancharticle")

	exec sql open objSelDelcscbrancharticle using :g_sBranchno, :g_sBranchno;
	ERROR_MSG("open objSelDelcscbrancharticle")

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

			exec sql fetch objSelDelcscbrancharticle;
			if (sqlca.sqlcode == 100) 
				break;
			ERROR_MSG("fetch objSelDelcscbrancharticle")

			exec sql execute delete_cscbrancharticle;
			ERROR_MSG("execute delete_cscbrancharticle")
		}
	EXEC SQL commit work;
	ERROR_MSG("Commit Work0:")

	exec sql close objSelDelcscbrancharticle;
	ERROR_MSG("close objSelDelcscbrancharticle")
	
	PrintMsg(fun, "DeleteCscBranchArticle done", HINW, rc);

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
	sprintf(logFile, "%s/loadcscbrancharticle.log", env);

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

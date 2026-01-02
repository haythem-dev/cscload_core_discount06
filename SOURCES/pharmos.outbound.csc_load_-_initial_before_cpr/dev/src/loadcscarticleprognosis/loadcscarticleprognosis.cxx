/*##################################################################################
 *    main module: loadcscarticleprognosis.ecc                                                             
 *         Source: loadcscarticleprognosis.cxx                                                             
 *          Autor: Haythem Ben-Abdelaziz                                              
 *        Created: 12.10.2024                                                                   
 *  Last Modified: 13.01.2025                                                                    
 *       language: C                                                                            
 *      Developed: manual                                                                       
 *           Task: transfer artprog table from inbound to cscarticleprognosis table in outbound                
 *          Usage: loadcscarticleprognosis.sh -branchno <brchno> -dbin <inbounddb> -dbout <outbounddb>
 *  
 *#################################################################################*/

/* INCLUDE ********************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

/* ToDo Programmname */
#define PROJECTNAME	 "loadcscarticleprognosis"

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
int FillArtprogIntoCscArticlePrognosis(char* error_msg);
int PrepareTempTabletoReadArtprog(char* error_msg);
int DeleteCscArticlePrognosis(char* error_msg);
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
	char* LOG_FILE = "loadcscarticleprognosis.log";
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
	
	if (PrepareTempTabletoReadArtprog(error_msg) != OK)
	{
		PrintMsg(fun, "ended with error PrepareTempTabletoReadArtprog", FEHL, rc);
		return 8;
	}

	if ((rc = FillArtprogIntoCscArticlePrognosis(error_msg)) != 0)
	{
		PrintMsg(fun, "ended with error FillArtprogIntoCscArticlePrognosis", FEHL, rc);
		return 9;
	}
	
	if ((rc = DeleteCscArticlePrognosis(error_msg)) != 0)
	{
		PrintMsg(fun, "ended with error DeleteCscArticlePrognosis", FEHL, rc);
		return 10;	
	}

	CleanupTempTables(error_msg);
	PrintMsg(fun, "ended correctly", HINW, rc);
	
	return 0;

}

int CleanupTempTables(char* error_msg)
{
	char* fun = "CleanupTempTables";

	EXEC SQL TRUNCATE TABLE tmp_artprog;
	ERROR_MSG("truncate table tmp_artprog");
	
	return 0;
}

/*** PREPARE-TempTableToRead ArticlePrognosis ************************************************/
int PrepareTempTabletoReadArtprog(char* error_msg)
{
	char* fun = "PrepareTempTabletoReadArtprog";

	int  rc = OK;
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	EXEC SQL CREATE TEMP TABLE tmp_artprog(
	filialnr integer, 
	artikel_nr integer,
	datum integer , 
 	prog_s float,
	wprog_s float);
	ERROR_MSG("create temp table tmp_artprog");

	strcpy(str, "insert into tmp_artprog select ");
	strcat(str, "filialnr, ");
	strcat(str, "artikel_nr, ");
	strcat(str, "datum, ");
	strcat(str, "prog_s, ");
	strcat(str, "wprog_s ");
	strcat(str, "from  ");
	strcat(str, g_indatabase);
	strcat(str, ":artprog ");
	//strcat(str, "where filialnr = ? ");
	strcat(str, "where filialnr = ? and datum >=  (select NVL(max(lastupdatedate), 0) as mydate from cscarticleprognosis where filialnr = ?)");

	EXEC SQL PREPARE insert_artprog from : str;
	ERROR_MSG("prepare insert_artprog")
	
	PrintMsg(fun, "PrepareTempTabletoReadArtprog done", HINW, rc);

	return OK;
}

/***** START LOADING ************************************/
int FillArtprogIntoCscArticlePrognosis(char* error_msg)
{
	int  rc = OK;
	int  ende = NO;
	char* fun = "FillArtprogIntoCscArticlePrognosis";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	EXEC SQL EXECUTE insert_artprog using :g_sBranchno, :g_sBranchno;	
	ERROR_MSG("open insert_artprog")
	
	strcpy( str, "MERGE INTO cscarticleprognosis cap ");
	strcat (str, "using tmp_artprog tap ");
	strcat (str, "on cap.filialnr = tap.filialnr AND cap.artikel_nr = tap.artikel_nr AND cap.datum = tap.datum ");
	strcat (str, "WHEN MATCHED THEN ");
	strcat (str, "UPDATE SET cap.prog_s = tap.prog_s, ");
	strcat (str, "cap.wprog_s = tap.wprog_s, ");
	strcat (str, "cap.lastupdatedate = ");
	strcat (str, currentDate); 
	strcat (str, " WHEN NOT MATCHED THEN  ");
	strcat (str, "INSERT (  ");
	strcat (str, "cap.filialnr,  ");
	strcat (str, "cap.artikel_nr,  ");
	strcat (str, "cap.datum,  ");
	strcat (str, "cap.prog_s,  ");
	strcat (str, "cap.wprog_s,  "); 
	strcat (str, "cap.lastupdatedate) "); 
	strcat (str, "values ( tap.filialnr,tap.artikel_nr,tap.datum,tap.prog_s,tap.wprog_s, ");
	strcat(str, currentDate);
	strcat(str, ")");
	
	EXEC SQL PREPARE Upd_Ins_cscarticleprognosis from :str;	
	ERROR_MSG("PREPARE Upd_Ins_cscarticleprognosis")
	
	EXEC SQL EXECUTE Upd_Ins_cscarticleprognosis;
	ERROR_MSG("EXECUTE Upd_Ins_cscarticleprognosis")
	
	PrintMsg(fun, "FillArtprogIntoCscArticlePrognosis done", HINW, rc);
	
	return rc;
}


/*** LOESCHEN NICHT GEAENDERTE SAETZE ************************************************/

int DeleteCscArticlePrognosis(char* error_msg)
{
	char* fun = "DeleteCscArticlePrognosis";
	int i;
	int  rc = OK;
	
	exec sql begin declare section;
	char str[2048];
	char str1[2048];
	exec sql end declare section;

    // Preparing the SELECT declaration with placeholders
    strcpy(str, "SELECT filialnr, datum, artikel_nr FROM cscarticleprognosis WHERE filialnr = ? AND datum IN ( ");
    strcat(str, "SELECT cap.datum FROM cscarticleprognosis cap LEFT OUTER JOIN ");
	strcat(str, g_indatabase);
    strcat(str, ":artprog ap ON (cap.filialnr = ap.filialnr AND cap.datum = ap.datum AND cap.artikel_nr = ap.artikel_nr) ");
    strcat(str, "WHERE cap.filialnr = ? AND ap.datum IS NULL) FOR UPDATE");
	
	exec sql prepare selectDel_cscarticleprognosis from :str;
	ERROR_MSG("prepare selectDel_cscarticleprognosis")
	exec sql declare objSelDelcscarticleprognosis cursor with hold for selectDel_cscarticleprognosis;

    // Prepare the DELETE declaration
    strcpy(str1, "DELETE FROM cscarticleprognosis WHERE CURRENT OF objSelDelcscarticleprognosis");
	
	exec sql prepare delete_cscarticleprognosis from :str1;
	ERROR_MSG("prepare delete_cscarticleprognosis")

    // Open the cursor with the branch number provided
	exec sql open objSelDelcscarticleprognosis using :g_sBranchno, :g_sBranchno;
	ERROR_MSG("open objSelDelcscarticleprognosis")

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

		exec sql fetch objSelDelcscarticleprognosis;
		if (sqlca.sqlcode == 100) 
			break;
		ERROR_MSG("fetch objSelDelcscarticleprognosis")

		exec sql execute delete_cscarticleprognosis;
		ERROR_MSG("execute delete_cscarticleprognosis")
	}
	EXEC SQL commit work;
	ERROR_MSG("Commit Work0:")

	exec sql close objSelDelcscarticleprognosis;
	ERROR_MSG("close objSelDelcscarticleprognosis")
	
	PrintMsg(fun, "DeleteCscArticlePrognosis done", HINW, rc);

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
	sprintf(logFile, "%s/loadcscarticleprognosis.log", env);

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

/*###########################################################################
 *    main module: loadsupplier.ecc                                                             
 *         Source: loadsupplier.cxx                                                             
 *          Autor: Haythem Ben-Abdelaziz                                              
 *        Created: 12.10.2024                                                                   
 *  Last Modified: 13.01.2025                                                                    
 *       language: C                                                                            
 *      Developed: manual                                                                       
 *           Task: transfer liefer table from inbound to supplier table in outbound                
 *          Usage: loadsupplier.sh -dbin <inbounddb> -dbout <outbounddb>
 *  
 *###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

/* ToDo Programmname */
#define PROJECTNAME	 "loadsupplier"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
/* ToDo Include */
#include "pplib/allg.h"
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
#define M_COUNT_COMMIT 140                  /* after n-rows commit  */

char log_file[300 + 1];
char filename[L_TEXT];
int counterIns = 0;
int counterUpd = 0;
int counterDel = 0;

exec sql begin declare section;
char g_indatabase[60];
char g_outdatabase[60];
/* ToDo Structur */
typedef struct N_SUPPLIER {
	int LANT_NR;
	char LANT_MC[15];
	int HERSTELLER_NR;
	char SAP_LANTNR[5];
	char ARZNEIMITTELBEZUG[2];
	int SAP_LANTNEU;
	//char UPD_FLAG[1];
} supplierS;

supplierS inrecord;
supplierS outrecord;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main(int, char**);
void PrintMsg(char* fun, char* error_msg, char mld, int rc);
void WriteLogInfo(char* error_msg, char mld, int rc);
int SetNotUpdated(char* error_msg);
int DelNotUpdated(char* error_msg);
int PrepareLoadData(char* error_msg);
int LoadData(char* error_msg);
int CloseDatabase(void);

/***** MAIN *****************************************************************/

int main(int argc, char** argv)
{
	char  error_msg[181];
	char* parameter;
	int   i;
	char* fun = "Main";
	char* LOG_FILE = "loadsupplier.log";
	char* LOG_PATH;
	char  logpath[256 + 1];
	int   rc;
	int   status = 0;
	char  start_msg[81];

	sprintf(g_indatabase, "%s", INDATABASE);
	sprintf(g_outdatabase, "%s", OUTDATABASE);

	strcpy(start_msg, "gestartet mit:");
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
		else if (!strcmp(parameter, "-version"))
		{
			printVersion(versioninfo);
			return 0;
		}
		else
		{
			printf("  usage: %s\n\t"
				" { -dbin databasename <databasename inbound> }\n\t"
				" { -dbout databasename <databasename outbound> }\n\t"
				, argv[0]);
			return 1;
		}
	}

	exec sql database : g_outdatabase;
	ERROR_MSG("Fehler oeffnen DB")

		exec sql set lock mode to wait 20;
	ERROR_MSG("Set LockMode to Wait")

		exec sql set isolation to dirty read;
	ERROR_MSG("Set Isolation to Dirty Read")

		PrintMsg(fun, start_msg, HINW, 0);

	if (PrepareLoadData(error_msg) != OK)
		return 8;

	if (SetNotUpdated(error_msg) != OK)
		return 8;

	if ((rc = LoadData(error_msg)) != 0)
	{
		PrintMsg(fun, "mit Fehler beendet", FEHL, rc);
		return 9;
	}

	if (DelNotUpdated(error_msg) != OK)
		return 8;

	PrintMsg(fun, "korrekt beendet", HINW, rc);
	return 0;
}

/***** load of the data ************************************/

int LoadData(char* error_msg)
{
	int  counter = 0;
	int  rc = OK;
	int  ende = NO;
	char* fun = "LoadData";

	exec sql open CselzData;
	ERROR_MSG("open CselzData")

		EXEC SQL begin work;
	ERROR_MSG("Begin Work")

		for (;; )
		{
			if (counter++ % M_COUNT_COMMIT == 0)
			{
				EXEC SQL commit work;
				ERROR_MSG("Commit Work")

					EXEC SQL begin work;
				ERROR_MSG("Begin Work")
			}

			exec sql fetch CselzData into : inrecord;
			ERROR_MSG("fetch CselzData")
				if (NOTFOUND) break;

			/* ToDo Indexfelder */
			exec sql open CupdloadData using :inrecord.LANT_NR;
			ERROR_MSG("open CupdloadData")

				exec sql fetch CupdloadData into : outrecord;
			ERROR_MSG("fetch CupdloadData")

				if (sqlca.sqlcode == 0)
				{
					exec sql execute upd_loadData using :inrecord;
					ERROR_MSG("execute upd_loadData")

						counterUpd++;
				}
				else
				{
					exec sql execute ins_loadData using :inrecord;
					ERROR_MSG("execute ins_loadData")

						counterIns++;
				}

		}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG("Commit Work")

		counter--;

	sprintf(error_msg, "%d Saetze gelesen", counter);
	PrintMsg(fun, error_msg, HINW, OK);
	sprintf(error_msg, "%d Saetze geaendert", counterUpd);
	PrintMsg(fun, error_msg, HINW, OK);
	sprintf(error_msg, "%d Saetze eingefuegt", counterIns);
	PrintMsg(fun, error_msg, HINW, OK);

	return rc;
}

/*** flag-not-updated ************************************************/

int SetNotUpdated(char* error_msg)
{
	int  counter = 0;
	int  rc = OK;
	int  ende = NO;
	char* fun = "SetNotUpdated";

	exec sql begin declare section;
	char upd_flag[2];
	exec sql end declare section;

	exec sql open CSetNotUpdate;
	ERROR_MSG("open CSetNotUpdate")

		EXEC SQL begin work;
	ERROR_MSG("Begin Work")

		for (;; )
		{
			if (counter++ % M_COUNT_COMMIT == 0)
			{
				EXEC SQL commit work;
				ERROR_MSG("Commit Work")

					EXEC SQL begin work;
				ERROR_MSG("Begin Work")
			}
			exec sql fetch CSetNotUpdate into : upd_flag;
			ERROR_MSG("fetch CSetNotUpdate")

				if (NOTFOUND) break;

			exec sql execute set_notupdated;
			ERROR_MSG("set_notupdated")
		}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG("Commit Work")

		return rc;
}

/*** DELETE-NOT-UPDATED ************************************************/

int DelNotUpdated(char* error_msg)
{
	int  counter = 0;
	int  rc = OK;
	int  ende = NO;
	char* fun = "DelNotUpdated";

	exec sql begin declare section;
	char upd_flag[2];
	exec sql end declare section;

	exec sql open CDelNotUpdate;
	ERROR_MSG("open CDelNotUpdate")

		EXEC SQL begin work;
	ERROR_MSG("Begin Work")

		for (;; )
		{
			if (counter++ % M_COUNT_COMMIT == 0)
			{
				EXEC SQL commit work;
				ERROR_MSG("Commit Work")

					EXEC SQL begin work;
				ERROR_MSG("Begin Work")
			}

			exec sql fetch CDelNotUpdate into : upd_flag;
			ERROR_MSG("fetch CDelNotUpdate")
				if (NOTFOUND) break;

			exec sql execute del_notupdated;
			ERROR_MSG("del_notupdated")
				counterDel++;
		}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG("Commit Work")

		sprintf(error_msg, "%d Saetze geloescht", counterDel);
	PrintMsg(fun, error_msg, HINW, OK);

	return rc;
}

/*** PREPARE-LOAD-DATA ************************************************/

int PrepareLoadData(char* error_msg)
{
	char* fun = "PrepareLoadData";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	/*	kennzeichnen nicht geaendert	*/
	strcpy(str, "select ");
	strcat(str, "upd_flag ");
	strcat(str, "from ");
	/* ToDo Tabelle */
	strcat(str, "supplier ");
	strcat(str, "for update ");

	exec sql prepare dec_setnotupdated from : str;
	ERROR_MSG("prepare dec_setnotupdated")
		exec sql declare CSetNotUpdate cursor with hold for dec_setnotupdated;

	strcpy(str, "update ");
	/* ToDo Tabelle */
	strcat(str, "supplier ");
	strcat(str, "set upd_flag = '0' ");
	strcat(str, "where current of CSetNotUpdate ");

	exec sql prepare set_notupdated from : str;
	ERROR_MSG("prepare set_notupdated")

		/*	delete not updated ones	*/
		strcpy(str, "select ");
	strcat(str, "upd_flag ");
	strcat(str, "from ");
	/* ToDo Tabelle */
	strcat(str, "supplier ");
	strcat(str, "where ");
	strcat(str, "upd_flag = '0' ");
	strcat(str, "for update ");

	exec sql prepare dec_delnotupdated from : str;
	ERROR_MSG("prepare dec_delnotupdated")
		exec sql declare CDelNotUpdate cursor with hold for dec_delnotupdated;

	strcpy(str, "delete from ");
	/* TARGET Table */
	strcat(str, "supplier ");
	strcat(str, "where current of CDelNotUpdate ");

	exec sql prepare del_notupdated from : str;
	ERROR_MSG("prepare del_notupdated")

		/*	zu ladende Daten	*/
		strcpy(str, "select ");
	/* SOURCE Table */
	strcat(str, "LANT_NR, LANT_MC, HERSTELLER_NR, SAP_LANTNR, ARZNEIMITTELBEZUG, SAP_LANTNEU");
	strcat(str, " from  ");
	strcat(str, g_indatabase);
	strcat(str, ":liefer ");

	exec sql prepare dec_zData from : str;
	ERROR_MSG("prepare dec_zData")
		exec sql declare CselzData cursor with hold for dec_zData;

	/*	existing data	*/
	strcpy(str, "select ");
	strcat(str, "LANT_NR, LANT_MC, HERSTELLER_NR, SAP_LANTNR, ARZNEIMITTELBEZUG, SAP_LANTNEU");
	strcat(str, " from ");
	strcat(str, "supplier ");
	strcat(str, "where ");
	/* Indexfields */
	strcat(str, "lant_nr = ? ");
	strcat(str, "for update ");

	exec sql prepare sel_loadData from : str;
	ERROR_MSG("prepare sel_loadData")
		exec sql declare CupdloadData cursor with hold for sel_loadData;

	strcpy(str, "update supplier set ");
	strcat(str, "LANT_NR=?, LANT_MC=?, HERSTELLER_NR=?, SAP_LANTNR=?, ARZNEIMITTELBEZUG=?, SAP_LANTNEU=?, UPD_FLAG='1'");
	//strcat(str, ",upd_flag = '1' ");
	strcat(str, "where current of CupdloadData ");

	exec sql prepare upd_loadData from : str;
	ERROR_MSG("prepare upd_loadData")

	strcpy(str, "insert into supplier (");
	strcat(str, "LANT_NR, LANT_MC, HERSTELLER_NR, SAP_LANTNR, ARZNEIMITTELBEZUG, SAP_LANTNEU, UPD_FLAG");
	//strcat(str, ",upd_flag ");
	strcat(str, " ) values ");
	strcat(str, "( ?, ?, ?, ?, ?, ?, '1' )");

	exec sql prepare ins_loadData from : str;
	ERROR_MSG("prepare ins_loadData")

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
	sprintf(logFile, "%s/loadsupplier.log", env);

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

/***** END *****************************************************************/

/*###########################################################################
 *    main module: loadcscpubatchorderpos.ecc                                                             
 *         Source: loadcscpubatchorderpos.cxx                                                             
 *          Author: Haythem Ben-Abdelaziz                                              
 *        Created: 12.10.2024                                                                   
 *  Last Modified: 13.02.2025                                                                    
 *       language: C                                                                            
 *      Developed: manual                                                                        
 *           Task: transfer pubatchorderpos table from inbound to cscpubatchorderpos table in outbound                
 *          Usage: loadcscpubatchorderpos.sh -dbin <inbounddb> -dbout <outbounddb>
 *  
 *###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "pplib/allg.h"
#include <string.h>
#include <unistd.h>
#include <pthread.h> // Include for threading

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

#define PROJECTNAME	 "loadcscpubatchorderpos"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1],\
										sqlca.sqlerrm); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               CloseDatabase(); /* Ensure database is closed on error */ \
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
typedef struct N_CSCPUBATCHORDERPOS {
	int posid;
	int branchno;
	int articleno;
	int orderproposalqty;
	int ordernobatch;
	int ordertypebatch;
	int reasonid;
	datetime orderproposaltime;
	datetime orderproposalprocessedtime;
	char orderproposaldisclaimnote[256];
	int orderproposalno;
	int purchaseorderno;
	int dateofpurchase;
	int expectedgoodsindate;
	int supplierno;
} cscpubatchorderposS;

cscpubatchorderposS inrecord;
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

// Mutex for thread-safe logging
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

/***** MAIN *****************************************************************/

int main(int argc, char** argv)
{
	char  error_msg[181];
	char* parameter;
	int   i;
	char* fun = "Main";
	char* LOG_FILE = "loadcscpubatchorderpos.log";
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

	int retry_count = 0;
	const int MAX_RETRIES = 5;
	const int RETRY_DELAY = 5; // seconds

	while (retry_count < MAX_RETRIES) {
		if (PrepareLoadData(error_msg) != OK) {
			PrintMsg(fun, "PrepareLoadData failed. Retrying...", FEHL, -1);
			retry_count++;
			sleep(RETRY_DELAY);
			continue;
		}

		if (SetNotUpdated(error_msg) != OK) {
			PrintMsg(fun, "SetNotUpdated failed. Retrying...", FEHL, -1);
			retry_count++;
			sleep(RETRY_DELAY);
			continue;
		}

		if ((rc = LoadData(error_msg)) != 0) {
			PrintMsg(fun, "LoadData encountered an error. Retrying...", FEHL, rc);
			retry_count++;
			sleep(RETRY_DELAY);
			continue;
		}

		if (DelNotUpdated(error_msg) != OK) {
			PrintMsg(fun, "DelNotUpdated failed. Retrying...", FEHL, -1);
			retry_count++;
			sleep(RETRY_DELAY);
			continue;
		}

		PrintMsg(fun, "korrekt beendet", HINW, rc);
		CloseDatabase();
		return 0;
	}

	PrintMsg(fun, "Max retries reached. Exiting...", FEHL, -1);
	CloseDatabase();
	return -1;
}

/***** load of the data ************************************/

int LoadData(char* error_msg)
{
    int  counter = 0;
    int  rc = OK;
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

        exec sql fetch CselzData into :inrecord;
        if (sqlca.sqlcode < 0) {
            sprintf(error_msg, "Error fetching data: SQLCODE = %d", sqlca.sqlcode);
            PrintMsg(fun, error_msg, FEHL, sqlca.sqlcode);
            break; // Exit the loop on error
        }
        ERROR_MSG("fetch CselzData")
        if (NOTFOUND) break;

        // Insert the record (excluding posid and upd_flag)
        exec sql execute ins_loadData using 
            :inrecord.branchno, 
            :inrecord.articleno, 
            :inrecord.orderproposalqty, 
            :inrecord.ordernobatch, 
            :inrecord.ordertypebatch, 
            :inrecord.reasonid, 
            :inrecord.orderproposaltime, 
            :inrecord.orderproposalprocessedtime, 
            :inrecord.orderproposaldisclaimnote, 
            :inrecord.orderproposalno, 
            :inrecord.purchaseorderno, 
            :inrecord.dateofpurchase, 
            :inrecord.expectedgoodsindate, 
            :inrecord.supplierno;
        if (sqlca.sqlcode < 0) {
            sprintf(error_msg, "Error inserting data: SQLCODE = %d", sqlca.sqlcode);
            PrintMsg(fun, error_msg, FEHL, sqlca.sqlcode);
            break;
        }
        counterIns++;
    }      /* ende for */

    EXEC SQL commit work;
    ERROR_MSG("Commit Work")
	
	// Close the cursor after the fetch loop
    exec sql close CselzData;
    ERROR_MSG("close CselzData")
	
    counter--;

    sprintf(error_msg, "%d Saetze gelesen", counter);
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
	
	// Close the cursor used in this function
    exec sql close CSetNotUpdate;
    ERROR_MSG("close CSetNotUpdate")
	
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
	
	// Close the cursor used in this function
    exec sql close CDelNotUpdate;
    ERROR_MSG("close CDelNotUpdate")
	
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
	strcat(str, "cscpubatchorderpos ");
	strcat(str, "for update ");

	exec sql prepare dec_setnotupdated from : str;
	ERROR_MSG("prepare dec_setnotupdated")
		exec sql declare CSetNotUpdate cursor with hold for dec_setnotupdated;

	strcpy(str, "update ");
	strcat(str, "cscpubatchorderpos ");
	strcat(str, "set upd_flag = '0' ");
	strcat(str, "where current of CSetNotUpdate ");

	exec sql prepare set_notupdated from : str;
	ERROR_MSG("prepare set_notupdated")

		/*	delete not updated ones	*/
	strcpy(str, "select ");
	strcat(str, "upd_flag ");
	strcat(str, "from ");
	strcat(str, "cscpubatchorderpos ");
	strcat(str, "where ");
	strcat(str, "upd_flag = '0' ");
	strcat(str, "for update ");

	exec sql prepare dec_delnotupdated from : str;
	ERROR_MSG("prepare dec_delnotupdated")
		exec sql declare CDelNotUpdate cursor with hold for dec_delnotupdated;

	strcpy(str, "delete from ");
	strcat(str, "cscpubatchorderpos ");
	strcat(str, "where current of CDelNotUpdate ");

	exec sql prepare del_notupdated from : str;
	ERROR_MSG("prepare del_notupdated")
	
	/*	zu ladende Daten	*/
	strcpy(str, "select ");
	/* SOURCE Table */
	strcat(str, "POSID, BRANCHNO, ARTICLENO, ORDERPROPOSALQTY, ORDERNOBATCH, ORDERTYPEBATCH, REASONID,ORDERPROPOSALTIME, ORDERPROPOSALPROCESSEDTIME, ORDERPROPOSALDISCLAIMNOTE, ORDERPROPOSALNO, PURCHASEORDERNO, DATEOFPURCHASE, EXPECTEDGOODSINDATE, SUPPLIERNO");
	strcat(str, " from  ");
	strcat(str, g_indatabase);
	strcat(str, ":pubatchorderpos ");

	exec sql prepare dec_zData from : str;
	ERROR_MSG("prepare dec_zData")
	exec sql declare CselzData cursor with hold for dec_zData;
		
	/*	existing data	*/
	strcpy(str, "select ");
	strcat(str, "POSID, BRANCHNO, ARTICLENO, ORDERPROPOSALQTY, ORDERNOBATCH, ORDERTYPEBATCH, REASONID, ORDERPROPOSALTIME, ORDERPROPOSALPROCESSEDTIME, ORDERPROPOSALDISCLAIMNOTE, ORDERPROPOSALNO, PURCHASEORDERNO, DATEOFPURCHASE, EXPECTEDGOODSINDATE, SUPPLIERNO, UPD_FLAG");
	strcat(str, " from ");
	strcat(str, "cscpubatchorderpos ");
	strcat(str, "where ");
	strcat(str, "posid = ? ");
	strcat(str, "for update ");

	exec sql prepare sel_loadData from : str;
	ERROR_MSG("prepare sel_loadData")
	exec sql declare CupdloadData cursor with hold for sel_loadData;

	strcpy(str, "update cscpubatchorderpos set ");
	strcat(str, "BRANCHNO=?, ARTICLENO=?, ORDERPROPOSALQTY=?, ORDERNOBATCH=?, ORDERTYPEBATCH=?, REASONID=?, ORDERPROPOSALTIME=?, ORDERPROPOSALPROCESSEDTIME=?, ORDERPROPOSALDISCLAIMNOTE=?, ORDERPROPOSALNO=?, PURCHASEORDERNO=?, DATEOFPURCHASE=?, EXPECTEDGOODSINDATE=?, UPD_FLAG='1'");
	//strcat(str, ",upd_flag = '1' ");
	strcat(str, "where current of CupdloadData ");

	exec sql prepare upd_loadData from : str;
	ERROR_MSG("prepare upd_loadData")

	/* Insert statement excluding posid and upd_flag */
	strcpy(str, "insert into cscpubatchorderpos (");
	strcat(str, "BRANCHNO, ARTICLENO, ORDERPROPOSALQTY, ORDERNOBATCH, ORDERTYPEBATCH, REASONID, ORDERPROPOSALTIME, ORDERPROPOSALPROCESSEDTIME, ORDERPROPOSALDISCLAIMNOTE, ORDERPROPOSALNO, PURCHASEORDERNO, DATEOFPURCHASE, EXPECTEDGOODSINDATE, SUPPLIERNO");
	strcat(str, " ) values ( ");
	strcat(str, " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )");

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

	env = getenv("LOG_PATH");
	if (env == NULL)
		env = ".";
	sprintf(logFile, "%s/loadcscpubatchorderpos.log", env);

	// Lock the mutex before writing to the log
	pthread_mutex_lock(&log_mutex);
	if ((fp = fopen(logFile, "a")) == (FILE*)0)
	{
		pthread_mutex_unlock(&log_mutex);
		return;
	}
	
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
	// Unlock the mutex after writing to the log
	pthread_mutex_unlock(&log_mutex);
}

/***** CLOSE-DATABASE *******************************************************/

int CloseDatabase(void)
{
	char error_msg[L_TEXT];
	char* fun = "CloseDatabase";

	// Close the cursor used in this function
	exec sql close database;
	ERROR_MSG("Close DB")

	return OK;
}

/***** END *****************************************************************/
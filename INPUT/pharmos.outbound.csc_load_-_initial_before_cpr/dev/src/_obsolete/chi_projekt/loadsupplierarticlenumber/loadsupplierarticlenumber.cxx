/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

/* ToDo Programmname */
#define PROJECTNAME	 "loadsupplierarticlenumber"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
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
#define INDATABASE         "iat21@zdev21_shm"
#define OUTDATABASE        "oat23chi@zdev21_shm"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */

char log_file[300 + 1];
char dateiname[L_TEXT];
int zaehlerIns = 0;
int zaehlerUpd = 0;
int zaehlerDel = 0;

EXEC SQL BEGIN DECLARE SECTION;
char indatenbank[60];
char outdatenbank[60];
typedef struct N_SUPPLIERARTICLENUMBER {
	long ARTIKEL_NR;
	long BESLA_NR;
	char ARTIKEL_NR_BLIEFER[17];
} supplierarticlenumberS;
supplierarticlenumberS indatensatz;
supplierarticlenumberS outdatensatz;
EXEC SQL END DECLARE SECTION;

/***** DECLARATION **********************************************************/

int main(int, char**);
void PrintMsg(char* fun, char* error_msg, char mld, int rc);
void WriteLogInfo(char* error_msg, char mld, int rc);
int SetNotUpdated(char* error_msg);
int DelNotUpdated(char* error_msg);
int PrepareLadeDaten(char* error_msg);
int LadeDaten(char* error_msg);
int CloseDatabase(void);

/***** MAIN *****************************************************************/

int main(int argc, char** argv)
{
	char  error_msg[181];
	char* schalter;
	int   i;
	char* fun = "Main";
	char* LOG_FILE = "wws.log";
	char* LOG_PATH;
	char  logpath[256 + 1];
	int   rc;
	int   status = 0;
	char  start_msg[81];

	sprintf(indatenbank, "%s", INDATABASE);
	sprintf(outdatenbank, "%s", OUTDATABASE);

	strcpy(start_msg, "gestartet mit:");
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
		else if (!strcmp(schalter, "-version"))
		{
			printVersion(versioninfo);
			return 0;
		}
		else
		{
			printf("  usage: %s\n\t"
				" { -dbin datenbankname <Datenbankname Eingabe> }\n\t"
				" { -dbout datenbankname <Datenbankname Ausgabe> }\n\t"
				, argv[0]);
			return 1;
		}
	}

	EXEC SQL database :outdatenbank;
	ERROR_MSG("Error while opening database")

	EXEC SQL SET LOCK MODE TO WAIT 20;
	ERROR_MSG("Set the lock mode to wait")

	EXEC SQL SET ISOLATION TO DIRTY READ;
	ERROR_MSG("Set isolation to dirty read")

	PrintMsg(fun, start_msg, HINW, 0);

	if (PrepareLadeDaten(error_msg) != OK)
		return 8;

	if (SetNotUpdated(error_msg) != OK)
		return 8;

	if ((rc = LadeDaten(error_msg)) != 0)
	{
		PrintMsg(fun, "ended with an error", FEHL, rc);
		return 9;
	}

	if (DelNotUpdated(error_msg) != OK)
		return 8;

	PrintMsg(fun, "completed correctly", HINW, rc);
	return 0;
}

/***** LADEN DER DATEN ************************************/

int LadeDaten(char* error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char* fun = "LadeDaten";

	EXEC SQL OPEN CselzData;
	ERROR_MSG("open CselzData")

	EXEC SQL BEGIN WORK;
	ERROR_MSG("Begin Work")

	for (;; )
	{
		if (zaehler++ % M_DURCHLAUF_COMMIT == 0)
		{
			EXEC SQL COMMIT WORK;
			ERROR_MSG("Commit Work")

			EXEC SQL BEGIN WORK;
			ERROR_MSG("Begin Work")
		}

		EXEC SQL FETCH CselzData INTO :indatensatz;
		ERROR_MSG("fetch CselzData")
		if (NOTFOUND) break;

		/* ToDo Indexfelder */
		EXEC SQL OPEN CupdloadData using :indatensatz.ARTIKEL_NR, :indatensatz.BESLA_NR;
		ERROR_MSG("open CupdloadData")

		EXEC SQL fetch CupdloadData into :outdatensatz;
		ERROR_MSG("fetch CupdloadData")

		if (sqlca.sqlcode == 0)
		{
			EXEC SQL EXECUTE upd_loadData using :indatensatz;
			ERROR_MSG("execute upd_loadData")
			zaehlerUpd++;
		}
		else
		{
			EXEC SQL EXECUTE ins_loadData using :indatensatz;
			ERROR_MSG("execute ins_loadData")
			zaehlerIns++;
		}
	}

	EXEC SQL COMMIT WORK;
	ERROR_MSG("Commit Work")

	zaehler--;

	sprintf(error_msg, "%d Saetze gelesen", zaehler);
	PrintMsg(fun, error_msg, HINW, OK);
	sprintf(error_msg, "%d Saetze geaendert", zaehlerUpd);
	PrintMsg(fun, error_msg, HINW, OK);
	sprintf(error_msg, "%d Saetze eingefuegt", zaehlerIns);
	PrintMsg(fun, error_msg, HINW, OK);

	return rc;
}

/*** KENNZEICHNEN-NICHT-BEARBEITET ************************************************/

int SetNotUpdated(char* error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char* fun = "SetNotUpdated";

	EXEC SQL BEGIN DECLARE SECTION;
	char upd_flag[2];
	EXEC SQL END DECLARE SECTION;

	EXEC SQL OPEN CSetNotUpdate;
	ERROR_MSG("open CSetNotUpdate")

	EXEC SQL BEGIN WORK;
	ERROR_MSG("Begin Work")

	for (;; )
	{
		if (zaehler++ % M_DURCHLAUF_COMMIT == 0)
		{
			EXEC SQL COMMIT WORK;
			ERROR_MSG("Commit Work")

			EXEC SQL BEGIN WORK;
			ERROR_MSG("Begin Work")
		}
		EXEC SQL FETCH CSetNotUpdate INTO :upd_flag;
		ERROR_MSG("fetch CSetNotUpdate")

		if (NOTFOUND) break;

		EXEC SQL EXECUTE set_notupdated;
		ERROR_MSG("set_notupdated")
	}

	EXEC SQL COMMIT WORK;
	ERROR_MSG("Commit Work")

	return rc;
}

/*** LOESCHEN-NICHT-BEARBEITET ************************************************/

int DelNotUpdated(char* error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char* fun = "DelNotUpdated";

	EXEC SQL BEGIN DECLARE SECTION;
	char upd_flag[2];
	EXEC SQL END DECLARE SECTION;

	EXEC SQL OPEN CDelNotUpdate;
	ERROR_MSG("open CDelNotUpdate")

	EXEC SQL BEGIN WORK;
	ERROR_MSG("Begin Work")

	for (;; )
	{
		if (zaehler++ % M_DURCHLAUF_COMMIT == 0)
		{
			EXEC SQL COMMIT WORK;
			ERROR_MSG("Commit Work")

			EXEC SQL BEGIN WORK;
			ERROR_MSG("Begin Work")
		}

		EXEC SQL FETCH CDelNotUpdate INTO :upd_flag;
		ERROR_MSG("fetch CDelNotUpdate")
		if (NOTFOUND) break;

		EXEC SQL EXECUTE del_notupdated;
		ERROR_MSG("del_notupdated")
		zaehlerDel++;
	}

	EXEC SQL COMMIT WORK;
	ERROR_MSG("Commit Work")

	sprintf(error_msg, "%d Saetze geloescht", zaehlerDel);
	PrintMsg(fun, error_msg, HINW, OK);

	return rc;
}

/*** PREPARE-LADE-DATEN ************************************************/

int PrepareLadeDaten(char* error_msg)
{
	char* fun = "PrepareLadeDaten";

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	/*	Kennzeichnen nicht geaendert  */
	strcpy(str, "SELECT ");
	strcat(str, "upd_flag ");
	strcat(str, "FROM ");
	strcat(str, "supplierarticlenumber ");
	strcat(str, "FOR UPDATE ");

	EXEC SQL PREPARE dec_setnotupdated FROM :str;
	ERROR_MSG("prepare dec_setnotupdated")
	EXEC SQL DECLARE CSetNotUpdate cursor WITH HOLD FOR dec_setnotupdated;

	strcpy(str, "UPDATE ");
	strcat(str, "supplierarticlenumber ");
	strcat(str, "SET upd_flag = '0' ");
	strcat(str, "WHERE CURRENT OF CSetNotUpdate ");

	EXEC SQL PREPARE set_notupdated FROM :str;
	ERROR_MSG("prepare set_notupdated")

	/*	loeschen nicht geaendert	*/
	strcpy(str, "SELECT ");
	strcat(str, "upd_flag ");
	strcat(str, "FROM ");
	strcat(str, "supplierarticlenumber ");
	strcat(str, "WHERE ");
	strcat(str, "upd_flag = '0' ");
	strcat(str, "FOR UPDATE ");

	EXEC SQL PREPARE dec_delnotupdated FROM :str;
	ERROR_MSG("prepare dec_delnotupdated")
	EXEC SQL DECLARE CDelNotUpdate cursor WITH HOLD FOR dec_delnotupdated;

	strcpy(str, "DELETE FROM ");
	strcat(str, "supplierarticlenumber ");
	strcat(str, "WHERE CURRENT OF CDelNotUpdate ");

	EXEC SQL PREPARE del_notupdated FROM :str;
	ERROR_MSG("prepare del_notupdated")

	/*	zu ladende Daten  */
	strcpy(str, "SELECT ");
	strcat(str, "ARTIKEL_NR, BESLA_NR, ARTIKEL_NR_BLIEFER ");
	strcat(str, "FROM ");
	strcat(str, indatenbank);
	strcat(str, ":artnrbl ");

	EXEC SQL PREPARE dec_zData FROM :str;
	ERROR_MSG("prepare dec_zData")
	EXEC SQL DECLARE CselzData cursor WITH HOLD FOR dec_zData;

	/*	vorhandene Daten  */
	strcpy(str, "SELECT ");
	strcat(str, "ARTIKEL_NR, BESLA_NR, ARTIKEL_NR_BLIEFER, UPD_FLAG");
	strcat(str, " FROM ");
	strcat(str, "supplierarticlenumber ");
	strcat(str, "WHERE ");
	/* ToDo Indxfelder */
	strcat(str, "artikel_nr = ? ");
	strcat(str, "and besla_nr = ? ");
	strcat(str, "FOR UPDATE ");

	EXEC SQL PREPARE sel_loadData FROM :str;
	ERROR_MSG("prepare sel_loadData")
	EXEC SQL DECLARE CupdloadData cursor WITH HOLD FOR sel_loadData;

	strcpy(str, "UPDATE supplierarticlenumber SET ");
	strcat(str, "ARTIKEL_NR=?, BESLA_NR=?, ARTIKEL_NR_BLIEFER=?, UPD_FLAG='1'");
	strcat(str, "WHERE CURRENT OF CupdloadData ");

	EXEC SQL PREPARE upd_loadData FROM :str;
	ERROR_MSG("prepare upd_loadData")

	strcpy(str, "INSERT INTO supplierarticlenumber (");
	strcat(str, "ARTIKEL_NR, BESLA_NR, ARTIKEL_NR_BLIEFER, UPD_FLAG");
	strcat(str, " ) values ( ");
	strcat(str, " ?, ?, ?, '1' )");

	EXEC SQL PREPARE ins_loadData FROM :str;
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

	EXEC SQL close database;
	ERROR_MSG("Close DB")

		return OK;
}

/***** ENDE *****************************************************************/

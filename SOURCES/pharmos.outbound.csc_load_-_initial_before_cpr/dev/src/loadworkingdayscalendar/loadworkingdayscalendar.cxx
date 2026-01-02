#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadworkingdayscalendar"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "pplib/allg.h"
#include "dkkal.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   	"loadworkingdayscalendar"
#define LOGFILE    		   	APPLICATION ".log"

#define DEBUG_SECTION      	if ( debug_enabled ) {
#define END_DEBUG_SECTION  	}

#define FALSE              	0
#define TRUE               	1

#define OK                 	0
#define ERROR              	-1
#define WARNING           	-2

#define FL_INFO            	'H'
#define FL_WARN            	'W'
#define FL_FAIL            	'F'

#define SQLCODE            	sqlca.sqlcode
#define SQL_ERRMSG(x)      	if ( sqlca.sqlcode < 0 ) { \
						   	    char msg[64]; \
                           	    sprintf(msg, \
										   "%s: %d/%d %s", \
										   x, \
                           	            sqlca.sqlcode, \
										   sqlca.sqlerrd[1], \
										   sqlca.sqlerrm ); \
                           	    LogMsg( FUN, msg, FL_FAIL); \
                           	    return -1; \
						   	}

#define TRANSACTLOOP		2000

 exec sql begin declare section;
 short sBranchno;
 exec sql end declare section;

// -------------------------------------------------------------------
struct SqlStat
{
	int ins;			// new rows
	int upd;			// updated rows
	int upd_exist;		// update already existing rows
	int del_flag;		// deleted rows because of DKKAA delete flag
	int del_missing;	// deleted rows because of missing in DKKAA
};

struct FileStat
{
	int read;			// lines read
	int proc;			// lines processed
	int skip;			// lines skipped
};

static struct SqlStat  	sqlstat  		= { 0 };
static struct FileStat 	filestat 		= { 0 };
static char   			logfile [256] 	= { 0 };
static int    			debug_enabled 	= FALSE;
static int    			bVersion	 	= FALSE;

// -------------------------------------------------------------------
int DbConnect(const char * database);
int DbDisconnect();

int StartLoadWorkingdaysCalendar(FILE * pFile, const char * const database);
int LoadWorkingdaysCalendar(struct O_DKKAL * pRecord);
int	PrepareLoadWorkingdaysCalendar();

int CheckLine(const char * const line, int len);

// -------------------------------------------------------------------
static void LogMsg( const char * const FUN, const char * const msg, char flag)
{
   	FILE *		fp	 = fopen(logfile, "a");
   	long 		secs = time	(NULL);
   	struct tm *	dt   = localtime(&secs);

   	fprintf( fp, "%c %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s:",
	    flag,
		dt->tm_mday,
        dt->tm_mon + 1,
        (dt->tm_year+1900) % 100,
        dt->tm_hour,
        dt->tm_min,
        dt->tm_sec,
	    getpid(),
	    APPLICATION,
	    FUN );

	fprintf(fp," %s\n", msg );
	fclose(fp);
}

// -------------------------------------------------------------------
static void PrintStat()
{
	const char *  const FUN      = "PrintStat";
	char                msg[256];

	sprintf(msg,"file lines:");
	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    read     : %4d", filestat.read);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    processed: %4d", filestat.proc);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    skipped  : %4d", filestat.skip);
 	LogMsg( FUN, msg, FL_INFO);

	sprintf(msg, "table rows:");
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    inserted : %4d", sqlstat.ins);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    updated  : %4d", sqlstat.upd);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    deleted  : %4d (load file delete flag)", sqlstat.del_flag);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    deleted  : %4d (missing in load file)" , sqlstat.del_missing);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    marked   : %4d (already existing rows)" , sqlstat.upd_exist);
 	LogMsg( FUN, msg, FL_INFO);
}

// -------------------------------------------------------------------
static void SetLogging()
{
	const char * const FUN = "SetLogging";
	char * envLogpath = NULL;
	char logpath [256] = { 0 };

	if ((envLogpath = getenv("LOG_PATH")) == (char *)0)
	{
		strcpy(logpath, ".");
	}
   	else
	{
	   	strcpy(logpath, envLogpath);
	}

	sprintf(logfile, "%s/%s", logpath, LOGFILE);

	DEBUG_SECTION
		char msg[256];
		sprintf(msg, "logfile: %s", logfile);
		LogMsg(FUN, msg, FL_INFO);
	END_DEBUG_SECTION
}

// -------------------------------------------------------------------
static int GetCmdLine( char * const loadpath,
					   char * const database,
					   int          argc    ,
					   char * const argv[]  )
{
	const char * const FUN = "GetCmdLine";
	int returnCode  = OK;


	for (int i = 1; i < argc; ++i)
	{
		char msg[512];
		sprintf(msg, "argument number %d: %s", i, argv[i]);
		LogMsg("CMDLINE: ", msg, FL_INFO);
	}

   	for ( int i = 1; i < argc; ++i )
   	{
		if (!strcmp(argv[i], "-dg"))
		{
			debug_enabled = TRUE;
		}
		else if ( !strcmp( argv[i], "-file" ) )
		{
			i++;

			if (i < argc)
			{
				sprintf(loadpath, "%s", argv[i]);


			}
		}
		else if ( !strcmp( argv[i], "-db" ) )
		{
			i++;

			if (i < argc)
			{
				sprintf(database, "%s", argv[i]);
			}
		}
		else if ( !strcmp( argv[i], "-branchno" ) )
		{
			i++;

			if (i < argc)
			{
				sBranchno = atoi(argv[i]);
			}
		}
		else if ( !strcmp( argv[i], "-version" ) )
		{
			printVersion(versioninfo);
			bVersion = TRUE;
			return OK;
		}
       	else
  		{
			returnCode = ERROR;
  			break;
  		}
	}

	if ( (1     == argc)	    		||
		 (ERROR == returnCode)			||
		 (sBranchno == 0)      			||
		 (0     == strlen(database))	||
		 (0     == strlen(loadpath))	   )
	{
		char msg[256];
		sprintf(msg, "  usage: %s\n"
	   				 "\t { -dg   <debugging> }\n"
					 "\t { -db   <Database Name> }\n"
					 "\t { -branchno   <Filialnr> }\n"
					 "\t { -file <Input File Name> }\n",
					 argv[0] );
		printf(msg);
		LogMsg(FUN, msg, FL_FAIL);

    	return ERROR;
	}

	char msg[256];
	sprintf(msg, "db: %s\tfile: %s", database, loadpath);
	LogMsg(FUN, msg, FL_INFO);

	return OK;
}

// -------------------------------------------------------------------
int main( int argc, char **argv  )
{
	const char * const FUN = "Main";
	char loadpath[256] 	= { 0 };
	char database[256] 	= { 0 };
	int  returnCode;

	setbuf(stdout, 0); // flush immediately

	SetLogging();

	LogMsg( FUN,
			"----------------------------------------------------------------",
			FL_INFO);
	LogMsg( FUN, "started", FL_INFO);

	returnCode = GetCmdLine(loadpath, database, argc, argv);

	if (OK != returnCode)
	{
		return returnCode;
	}

	if(bVersion)
	{
		return OK;
	}

	char msg[512];

	/* start loading from file */
	FILE * pFile = fopen(loadpath, "r");
	if (pFile == NULL)
	{
		sprintf(msg, "file \"%s\" doesn't exist", loadpath);
		LogMsg(FUN, msg, FL_FAIL);

		returnCode = ERROR;
	}

	if (OK == returnCode)
	{
		returnCode = StartLoadWorkingdaysCalendar(pFile, database);
		fclose(pFile);
	}

	PrintStat();
	sprintf(msg, "finished with exit code %d", returnCode);
   	LogMsg( FUN, msg, (returnCode == OK) ? FL_INFO: FL_FAIL);
	LogMsg( FUN,
			"----------------------------------------------------------------",
			FL_INFO);

   	return returnCode;
 }

// -------------------------------------------------------------------
int DbConnect (EXEC SQL BEGIN DECLARE SECTION;
			   PARAMETER const char * database
			   EXEC SQL END DECLARE SECTION;  )
{
	const char * const FUN = "DbConnect";

   	EXEC SQL SET LOCK MODE TO WAIT 20;
	SQL_ERRMSG("lock mode")

   	EXEC SQL DATABASE :database;
	SQL_ERRMSG("database")

   	EXEC SQL SET ISOLATION TO DIRTY READ;
	SQL_ERRMSG("set isolation")

	return OK;
}

// -------------------------------------------------------------------
int DbDisconnect ()
{
	const char * const FUN = "DbDisconnect";

	EXEC SQL CLOSE DATABASE;
	SQL_ERRMSG("close database")

	return OK;
}

// -------------------------------------------------------------------
int CheckLine (const char * const line, int len)
{
	const char * const FUN = "CheckLine";

	// check line for LF 0x0A at appropriate offset
	const char * pBufEnd = line + len;	// first byte behind line buffer

	for (const char * pBuf = line; pBuf < pBufEnd; ++pBuf)
	{
		if (0x0A == *pBuf)
		{
			long allowed = len - 5;
			long offset  = pBuf - line;

			if (offset == allowed)
			{
				return OK;
			}
			char msg[128];
				sprintf( msg, "linefeed 0x0A found at column %d; should be column %d.",
					     offset,
					allowed);
				LogMsg(FUN, msg, FL_WARN);

			return WARNING;
		}
	}

	char msg[128];
	sprintf(msg, "the line exceeded the maximum amount of %d chars and the program had to be aborted", len);
	LogMsg(FUN, msg, FL_FAIL);

	return ERROR;
}

// -------------------------------------------------------------------
int PrepareLoadWorkingdaysCalendar()
{
	const char * const FUN = "PrepareLoadWorkingdaysCalendar";
	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str, "update workingdayscalendar set ");
	strcat(str, WORKINGDAYSCALENDAR_UPDLISTE);
	strcat(str, " where ");
	strcat(str, "branchno = ?");
	strcat(str, " and ");
	strcat(str, "calendardate = ?");

	EXEC SQL PREPARE upd_workingdayscalendar FROM : str;
	SQL_ERRMSG("prepare upd_workingdayscalendar")

	return OK;
}

// -------------------------------------------------------------------
int StartLoadWorkingdaysCalendar(FILE * pFile, const char * const database)
{
	const char * const FUN = "StartLoadWorkingdaysCalendar";
	LogMsg(FUN, "entered", FL_INFO);

	int returnCode;

	returnCode = DbConnect(database);

	if (OK != returnCode)
	{
		return returnCode;
	}

	returnCode = PrepareLoadWorkingdaysCalendar();

	if (OK != returnCode)
	{
		DbDisconnect();
		return returnCode;
	}

	// the perfect linesize would be sizeof(struct O_DKKAL) + 16           15 delimiters + the linefeed. But in case of a too long line, we can still handle it for up to 3 more characters
	char line[sizeof(struct O_DKKAL) + 20] = { 0 };

	EXEC SQL begin work;
	SQL_ERRMSG("begin work")

	long fileoffs = 0;

	char msg[526];
	// for each line
	while ( NULL != fgets(line, sizeof(line), pFile) )
	{
		if ( !feof(pFile) )
		{
			fileoffs = ftell(pFile);				// save position for next loop
		}
		else
		{
			line[ftell(pFile) - fileoffs] = 0x0A; 	// end of file detected, replace because of CheckLine
		}

		returnCode = CheckLine(line, sizeof(line));

		if (OK != returnCode)
		{
			if(WARNING == returnCode)
			{
				char msg[128];
				sprintf(msg, "line %d skipped because line is too short, too long or has no linefeed", filestat.read);
				LogMsg(FUN, msg, FL_WARN);
			}
			else if (ERROR == returnCode)
			{
				char msg[128];
				sprintf(msg, "line %d exceeded the maximum amount of chars per line. The program aborted", filestat.read);
				break;
			}
		}
		else
		{
			LogMsg(FUN, line, FL_INFO);

			// iterating over the line. If the delimiter is hit, overwrite it with the next character
			int currentPosition = 0;

			for (int i = 0; line[i]; i++)
			{
				if (line[i] != ';')
				{
					line[currentPosition++] = line[i];
				}
			}

			line[currentPosition] = '\0';

			returnCode = LoadWorkingdaysCalendar((struct O_DKKAL *) line);

			if (ERROR == returnCode)
			{
				break;
			}
			else if(WARNING == returnCode)		// record is skipped
			{
				char msg[64];
				sprintf(msg, "line %4d skipped because of invalid values",
						     filestat.read);
				LogMsg(FUN, msg, FL_INFO);
			}
		}

		if ( WARNING == returnCode)
		{
			returnCode = OK; // skip results to OK
			++filestat.read;
			++filestat.skip;
		}
		else
		{
			assert(OK == returnCode);

			char msg[64];
			sprintf(msg, "%s was added", line);
			LogMsg(FUN, msg, FL_INFO);

			++filestat.read;
			++filestat.proc;
		}

		if ( filestat.proc % (TRANSACTLOOP) == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work between")

			EXEC SQL begin work;
			SQL_ERRMSG("begin work between")
		}


		memset(line, 0, sizeof(line));
	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work")

	DbDisconnect();

	return returnCode;
}

// -------------------------------------------------------------------
int LoadWorkingdaysCalendar(struct O_DKKAL * record)
{
	const char * const FUN = "LoadWorkingdaysCalendar";
	LogMsg(FUN, "Entered second part", FL_INFO);

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKAL *recordp;
	char datum[8];
	EXEC SQL END DECLARE SECTION;

	recordp = record;

	strcpy(datum, recordp->DATUMJAHR);
	strcat(datum, recordp->DATUMMONAT);
	strcat(datum, recordp->DATUMTAG);

	EXEC SQL EXECUTE upd_workingdayscalendar USING
											: recordp->FIL,
											: datum,
											: recordp->LFD,
											: recordp->KW,
											: recordp->MOZAHL,
											: recordp->JOZAHL,
											: recordp->KOZAHL,
											: recordp->AF,
											: recordp->FIL,
											: datum;

	SQL_ERRMSG("update workingdayscalendar:")

	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
	{
	    EXEC SQL insert into workingdayscalendar (WORKINGDAYSCALENDAR_LIST) values (
											: recordp->FIL,
											: datum,
											: recordp->LFD,
											: recordp->KW,
											: recordp->MOZAHL,
											: recordp->JOZAHL,
											: recordp->KOZAHL,
											: recordp->AF
											);

		SQL_ERRMSG( "insert workingdayscalendar:" )
		++sqlstat.ins;
	}
	else
	{
		++sqlstat.upd;
	}

	return OK;
}

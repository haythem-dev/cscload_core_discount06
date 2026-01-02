/* ---------------------------------------------------------------------------
 *  loaddktmd.cxx 
 *     load offene posten liste
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loaddktmd"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

#include "transmedstoppingpoints.h"
#include "dktmd.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loaddktmd"
#define LOGFILE    		   APPLICATION ".log"

#define DEBUG_SECTION      if ( debug_enabled ) {
#define END_DEBUG_SECTION  }

#define FALSE              0
#define TRUE               1

#define OK                 0
#define ERROR             -1
#define WARNING           -2

#define FL_INFO            'H'
#define FL_WARN            'W'
#define FL_FAIL            'F'

#define SQLCODE            sqlca.sqlcode
#define SQL_ERRMSG(x)      if ( sqlca.sqlcode < 0 ) { \
						       char msg[64]; \
                               sprintf(msg, \
									   "%s: %d/%d %s", \
									   x, \
                                       sqlca.sqlcode, \
									   sqlca.sqlerrd[1], \
									   sqlca.sqlerrm ); \
                               LogMsg( FUN, msg, FL_FAIL); \
                               return sqlca.sqlcode; \
						   }

#define TRANSACTLOOP	1000

// -------------------------------------------------------------------

struct SqlStat
{
	int ins;			// new rows
	int del;			// deleted rows
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

EXEC SQL BEGIN DECLARE SECTION;
short branchno;
EXEC SQL END DECLARE SECTION;
 
// -------------------------------------------------------------------

int  DbConnect			  (const char * database);
int  DbDisconnect		  ();

int  Start                (FILE * pFile, 
						   const char * const database);
int  Prepare              ();
int  Load                 (struct O_DKTMD * pRecord);
int  AfterLoad            ();

int  DelEntriesOfBranch   ();

int  CheckLine			  (const char * const line, int len);
int  IsValidString		  (const char * const str , int len);
int  IsValidNumber        (const char * const str , int len);
void MakeValidDate        (char * output , char * input );
 
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
		
	sprintf(msg,"Version 1.0.14");
	LogMsg( FUN, msg, FL_INFO);


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
	sprintf(msg, "    deleted  : %4d", sqlstat.del);
}

// -------------------------------------------------------------------
static void SetLogging()
{
	const char *  const FUN 			= "SetLogging";
	char *  			envLogpath 		= NULL;
	char    			logpath [256] 	= { 0 };
		
	if ((envLogpath = getenv("LOG_PATH")) == (char *)0)
		strcpy(logpath, ".");
   	else
	   	strcpy(logpath, envLogpath);
	
	sprintf(logfile, "%s/%s", logpath, LOGFILE);
		
	DEBUG_SECTION
		char msg[256];
		sprintf(msg, "logfile: %s", logfile);	
		LogMsg(FUN, msg, FL_INFO);
	END_DEBUG_SECTION
}

// -------------------------------------------------------------------
static int getCmdLine( char * const loadpath,
		        char * const database,
				int          argc    , 
				char * const argv[]  )
{
	const char *  const FUN = "getCmdLine";
	int	                rc  = OK;
		
   	for ( int i = 1; i < argc; ++i )
   	{
		if ( !strcmp(argv[i], "-dg" ) )
	   		debug_enabled = TRUE;
		else if ( !strcmp( argv[i], "-file" ) )
		{
			i++;

			if (i < argc)
				sprintf( loadpath, "%s", argv[i] );
		}
		else if ( !strcmp( argv[i], "-db" ) )
		{
			i++;

			if (i < argc)
				sprintf( database, "%s", argv[i] );
		}
		else if ( !strcmp( argv[i], "-branchno" ) )
		{
			i++;

			if (i < argc)
				branchno = atoi( argv[i] );
		}
		else if ( !strcmp( argv[i], "-version" ) )
		{
			printVersion(versioninfo);
			bVersion = TRUE;
			return OK;
		}
       	else
  		{
  			rc = ERROR;
  			break;
  		}
	}
	
	if ( (1     == argc)	    		|| 
		 (ERROR == rc)      			||
		 (0     == strlen(database))	||
		 (0     == strlen(loadpath))	   )
	{
		char msg[256];
		sprintf(msg, "  usage: %s\n"
	   				 "\t { -dg   <debugging> }\n"
					 "\t { -db   <Database Name> }\n"
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
	const char *  const FUN = "Main";

	setbuf(stdout, 0); // flush immediately

	SetLogging();
   	
	LogMsg( FUN, 
			"----------------------------------------------------------------", 
			FL_INFO);
	LogMsg( FUN, "started", FL_INFO);

	char loadpath[256] 	= { 0 };
	char database[256] 	= { 0 };
	int  rc;
	
	if (OK != (rc = getCmdLine(loadpath, database, argc, argv)) )
		return rc;
	if(bVersion) return OK;

	char   msg[512];

	/* start loading from file */
	FILE * pFile = fopen(loadpath, "r");
	if ( pFile == NULL )
	{
		sprintf(msg, "file \"%s\" doesn't exist", loadpath);
		LogMsg( FUN, msg, FL_FAIL);
	
		rc = ERROR;
	}

	if (OK == rc)
	{
		rc = Start(pFile, database);
		fclose(pFile);
	}
		
	PrintStat();
	sprintf(msg, "finished with exit code %d", rc);
   	LogMsg( FUN, msg, (rc == OK) ? FL_INFO: FL_FAIL);
	LogMsg( FUN, 
			"----------------------------------------------------------------", 
			FL_INFO);

   	return rc;
 }

// -------------------------------------------------------------------
int DbConnect (EXEC SQL BEGIN DECLARE SECTION;
			   PARAMETER const char * database
			   EXEC SQL END DECLARE SECTION;  )
{
	const char * const FUN = "DbConnect";
		
   	EXEC SQL DATABASE :database;
	SQL_ERRMSG("database")
	
   	EXEC SQL SET LOCK MODE TO WAIT 20;
	SQL_ERRMSG("lock mode")
		
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
int IsValidString (const char * const str, int len)
{
	for (int i = 0; i < len; ++i)
	{
		if ('\0' == str[i])	
			break;	// not valid
		else
		{
			if (' ' == str[i])
				continue;	// check next character
			else
				return TRUE;
		}
	}

	return FALSE;
}

// -------------------------------------------------------------------
int IsValidNumber (const char * const str, int len)
{
	DEBUG_SECTION
		for (int i = 0; i < len; ++i)
		{
			assert(str[i] >= '0');
			assert(str[i] <= '9');
		}
	END_DEBUG_SECTION
	
	for (int i = 0; i < len; ++i)
	{
		if ('0' != str[i])	// at minimum one digit != 0
			return TRUE;
	}

	return FALSE;
}

// --- Check valid date - if not valid set default date 01/01/1970 ---
void MakeValidDate (char * output , char * input )
{
	if(strncmp(input,"000000",6))
	{
		sprintf(output,"%2.2s/%2.2s/20%2.2s",input+2,input+4,input);
	}
	else
	{
		strcpy(output,"01/01/1970");
	}
}

// -------------------------------------------------------------------
int CheckLine (const char * const line, int len)
{
	const char * const FUN = "CheckLine";
	
	char msg[64];
	
	// check line for LF 0x0A at appropriate offset
	const char * pBufEnd = line + len;	// first byte behind line buffer

	for (const char * pBuf = line; pBuf < pBufEnd; ++pBuf)
	{
		if (0x0A == *pBuf)
		{
			long allowed = sizeof(struct O_DKTMD);
			long offset  = pBuf - line;

			if (offset >= allowed)
				return OK;

			DEBUG_SECTION
				sprintf( msg, "linefeed 0x0A found at column %d; should be column >= %d",
					     offset,
						 allowed);
				LogMsg(FUN, msg, FL_WARN); 
			END_DEBUG_SECTION

			return WARNING;
		}
	}

	sprintf(msg, "no linefeed 0x0A found in line (max. length = %d)", len);
	LogMsg(FUN, msg, FL_FAIL);

	return ERROR;
}

// -------------------------------------------------------------------
int Start(FILE * pFile, const char * const database)
{
	const char * const FUN = "Start";
	int    		 	   rc;

	if ( OK != (rc = DbConnect(database)) )
		return rc;

	if ( OK != (rc = Prepare()) )
	{
		DbDisconnect();
		return rc;	
	}
	
	char line[sizeof(struct O_DKTMD) + 2] = { 0 };	/* possibly LF */
//	char line[sizeof(struct O_DKTMD) + 3] = { 0 };	/* possibly CR + LF + '\0' */
	
	DEBUG_SECTION
		char msg[256];
		sprintf(msg, 
				"sizeof(O_DKTMD) = %d, sizeof(line) = %d", 
				sizeof(struct O_DKTMD),
				sizeof(line));	
		LogMsg(FUN, msg, FL_INFO);
	END_DEBUG_SECTION


	EXEC SQL begin work;
	SQL_ERRMSG("begin work")

	long fileoffs = 0;	

	// for each line
	while ( NULL != fgets(line, sizeof(line), pFile) )	
	{
		if ( ! feof(pFile) )
			fileoffs = ftell(pFile);				// save position for next loop
		else
			line[ftell(pFile) - fileoffs] = 0x0A; 	// end of file detected,
													// replace because of CheckLine
			
		if (OK != (rc = CheckLine(line, sizeof(line))) )
		{
			char msg[32];

			if (ERROR == rc)
			{
				sprintf(msg, "check line %d failed", filestat.read);
				LogMsg(FUN, msg, FL_FAIL);
				break;
			}
			else
			{
				if (WARNING == rc)
				{
					sprintf(msg, 
							"line %4d skipped because line is too short", 
							filestat.read);
					LogMsg(FUN, msg, FL_WARN);
				}
			}
		}

		assert(rc != ERROR);	// must not happen

		if (OK == rc)
		{
			// write into table
			rc = Load((struct O_DKTMD *)line);

			if (ERROR == rc)
				break;
			else
			{
				if (WARNING == rc)		// record is skipped
				{
					char msg[64];	
					sprintf(msg, "line %4d skipped because of invalid values", 
							     filestat.read);
					LogMsg(FUN, msg, FL_INFO); 
				}
			}
		}

		if (WARNING == rc)
		{
			rc = OK;	// skip results to OK
			++filestat.read;
			++filestat.skip;
		}
		else
		{
			assert(OK == rc);
			++filestat.read;
			++filestat.proc;
		}
		
		if ( filestat.proc % TRANSACTLOOP == 0 )
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

	if (OK == rc)
		rc = AfterLoad();

	DbDisconnect();
		
	return rc;
}

// -------------------------------------------------------------------
int Prepare()
{
	const char * const FUN = "Prepare";

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;


	/* insert */
	pStmt = "insert into transmedstoppingpoints ("
		TRANSMEDSTOPPINGPOINTS_PELISTE
				") values "
			"(?, ?, ?, ?, ?,"
			" ?, ?, ?, ?, ?,"
			" ?, ?, ? );";

	EXEC SQL PREPARE ins_load FROM :pStmt;
	SQL_ERRMSG( "prepare ins_load" );
	
	return DelEntriesOfBranch();
}

// ------------------------------------------------------------------- 
int Load (struct O_DKTMD * record)
{
	const char * const FUN = "Load";
	char huelse[81];
	long lTarget;

	// --- check valid branchno
	if ( FALSE == IsValidNumber(record->TMDFIL, sizeof(record->TMDFIL)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "TMDFIL not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- check valid customerno
	if ( FALSE == IsValidNumber(record->TMDIDF, sizeof(record->TMDIDF)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "TMDIDF not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}


	// --- convert
	EXEC SQL BEGIN DECLARE SECTION;
	transmedstoppingpointsS row = { 0 };
	EXEC SQL END DECLARE SECTION;
	
	sprintf(huelse,"%*.*s",L_DKTMD_TMDFIL,L_DKTMD_TMDFIL,record->TMDFIL);
	row.branchno   = atoi(huelse);
	sprintf(huelse,"%*.*s",L_DKTMD_TMDIDF,L_DKTMD_TMDIDF,record->TMDIDF);
	row.customerno = atol(huelse);
	sprintf(row.stoppingpoint,"%*.*s",L_DKTMD_TMDSTOP,L_DKTMD_TMDSTOP,record->TMDSTOP);
	sprintf(row.daytour,"%*.*s",L_DKTMD_TMDTTOUR,L_DKTMD_TMDTTOUR,record->TMDTTOUR);
	sprintf(row.nighttour,"%*.*s",L_DKTMD_TMDNTOUR,L_DKTMD_TMDNTOUR,record->TMDNTOUR);
	sprintf(row.defaulttour,"%*.*s",L_DKTMD_TMDTOUR,L_DKTMD_TMDTOUR,record->TMDTOUR);
	sprintf(huelse,"%*.*s",L_DKTMD_TMDSCODE,L_DKTMD_TMDSCODE,record->TMDSCODE);
	row.sendercode = atoi(huelse);
	sprintf(huelse,"%*.*s",L_DKTMD_TMDPRUEFSUMME,L_DKTMD_TMDPRUEFSUMME,record->TMDPRUEFSUMME);
	row.checksum  = atoi(huelse);

	MakeValidDate(row.creationdate,record->TMDANDAT);
	MakeValidDate(row.sendingdate,record->TMDSENDDAT);
	MakeValidDate(row.lastrecvdate,record->TMDSENDDAT);

/*	sprintf(row.creationdate,"%2.2s/%2.2s/20%2.2s",record->TMDANDAT+4,record->TMDANDAT+2,record->TMDANDAT);
	sprintf(row.sendingdate,"%2.2s/%2.2s/20%2.2s",record->TMDSENDDAT+4,record->TMDSENDDAT+2,record->TMDSENDDAT);
	sprintf(row.lastrecvdate,"%2.2s/%2.2s/20%2.2s",record->TMDLDAT+4,record->TMDLDAT+2,record->TMDLDAT);
	*/

	row.tourtype[0] = record->TMDTTYPE[0];
	row.notreachable[0] = record->TMDSTNAFB[0];

	// --- insert row

	EXEC SQL EXECUTE ins_load using :row; 
	SQL_ERRMSG("ins_load")

	++sqlstat.ins;	

	return OK;
}

// -------------------------------------------------------------------
int AfterLoad()
{
	return 0;
}

// -------------------------------------------------------------------
/* use select cursor: so number of transactions can be controlled   */
int DelEntriesOfBranch()
{
	const char * const FUN = "SetNotUpdated";

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;
	
	pStmt =	"select 1 from transmedstoppingpoints where branchno = ? for update;";

	EXEC SQL PREPARE sel_ForDelete FROM :pStmt;
	SQL_ERRMSG( "prepare sel_ForDelete" )
	EXEC SQL DECLARE CursorForDelete CURSOR WITH HOLD FOR sel_ForDelete;
	
	pStmt = "delete from transmedstoppingpoints where current of CursorForDelete;";
	
	EXEC SQL PREPARE del_OldEntries FROM :pStmt;
	SQL_ERRMSG( "prepare del_OldEntries" )

    EXEC SQL BEGIN WORK;
	SQL_ERRMSG( "begin work" )
		
	EXEC SQL OPEN CursorForDelete using :branchno;
    SQL_ERRMSG( "open CursorForDelete" )

	DEBUG_SECTION
		char msg[256];
		sprintf(msg, "SetNotUpd opened");	
		LogMsg(FUN, msg, FL_INFO);
	END_DEBUG_SECTION

	sqlstat.del = 0;

	for (;;)
	{

		EXEC SQL FETCH CursorForDelete;
		SQL_ERRMSG( "FETCH CursorForDelete" )

		if(SQLCODE == 100) break;

		EXEC SQL EXECUTE del_OldEntries;
		SQL_ERRMSG( "execute del_OldEntries" )

		sqlstat.del++;
		
		if ( sqlstat.del % TRANSACTLOOP == 0)
		{
			EXEC SQL COMMIT WORK;
			SQL_ERRMSG( "commit work between" )
				
			EXEC SQL BEGIN WORK;
			SQL_ERRMSG( "begin work between" )
		}
	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG( "commit work" )
	
	EXEC SQL CLOSE CursorForDelete;
    SQL_ERRMSG( "close CursorForDelete" )

	return OK;
}


/***** end of file *****************************************************************/


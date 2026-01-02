/* ---------------------------------------------------------------------------
 *  loaddkkaa.cxx
 *     load SAP payment terms from VSAM.DKKAA into SQL paymentterms
 *
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loaddkkaa"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "ldauftragartkd.h"
#include "pplib/allg.h"
#include "dkkaa.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loaddkkaa"
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
                               return -1; \
						   }

#define TRANSACTLOOP	2000

 exec sql begin declare section;
 long datum;
 long dbzeit;
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

int  DbConnect			  (const char * database);
int  DbDisconnect		  ();

int  StartLoadAufart      (FILE * pFile,
						   const char * const database);
int  PrepareLoadAufart    ();
int  LoadAufart           (struct O_DKKAA * pRecord);
int  AfterLoadAufart      ();

int  SetNotUpdatedAufart  ();
int  DelNotUpdatedAufart  ();
int  FetchCursor		  (const char *       cursorid,
						   const char * const msg     );

int  CheckLine			  (const char * const line, int len);
int  IsValidString		  (const char * const str , int len);
int  IsValidNumber        (const char * const str , int len);

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
				sBranchno = atoi( argv[i] );
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
		rc = StartLoadAufart(pFile, database);
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
			 struct O_DKKAA * pDummy = (struct O_DKKAA *)line;

			long allowed = (long)pDummy->FILL - (long)pDummy;
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
int StartLoadAufart(FILE * pFile, const char * const database)
{
	const char * const FUN = "StartLoadAufart";
	int    		 	   rc;

	if ( OK != (rc = DbConnect(database)) )
		return rc;

	if ( OK != (rc = PrepareLoadAufart()) )
	{
		DbDisconnect();
		return rc;
	}

	char line[sizeof(struct O_DKKAA) + 3] = { 0 };	/* possibly CR + LF + '\0' */

	EXEC SQL begin work;
	SQL_ERRMSG("begin work")

	long fileoffs = 0;

	datum = AllgGetDate();
	dbzeit = AllgGetTime();

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
			rc = LoadAufart((struct O_DKKAA *)line);

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

	if (OK == rc)
		rc = AfterLoadAufart();

	DbDisconnect();

	return rc;
}

// -------------------------------------------------------------------
int PrepareLoadAufart()
{
	const char * const FUN = "PrepareLoadAufart";

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;


	strcpy(str,"update auftragartkd set ");
	strcat(str,LDAUFTRAGARTKD_UPDLISTE);
	strcat(str," where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");
	strcat(str," and ");
	strcat(str,"KUNDENNR = ?");
	strcat(str," and ");
	strcat(str,"KDAUFTRAGART = ?");

	EXEC SQL PREPARE upd_auftragartkd FROM :str;
	SQL_ERRMSG( "prepare upd_auftragartkd" )

	return SetNotUpdatedAufart();
}

// -------------------------------------------------------------------
int LoadAufart (struct O_DKKAA * record)
{
	const char * const FUN = "LoadAufart";

	EXEC SQL BEGIN DECLARE SECTION;
	ldauftragartkdS row = { 0 };
	struct O_DKKAA *recordp;
	EXEC SQL END DECLARE SECTION;

	recordp = record;

	if(recordp->NATRA[0] == 'J' || recordp->NATRA[0] == '1') recordp->NATRA[0] = '1';
	else recordp->NATRA[0] = '0';

	if(recordp->NETTO[0] == 'J' || recordp->NETTO[0] == '1') recordp->NETTO[0] = '1';
	else recordp->NETTO[0] = '0';

	if(recordp->BANR[0] == 'J' || recordp->BANR[0] == '1') recordp->BANR[0] = '1';
	else recordp->BANR[0] = '0';

	if(recordp->VBSP[0] == 'J' || recordp->VBSP[0] == '1') recordp->VBSP[0] = '1';
	else recordp->VBSP[0] = '0';

	if(recordp->VSP[0] == 'J' || recordp->VSP[0] == '1') recordp->VSP[0] = '1';
	else recordp->VSP[0] = '0';

	if(recordp->MORAB[0] == 'J' || recordp->MORAB[0] == '1') recordp->MORAB[0] = '1';
	else recordp->MORAB[0] = '0';

	if(recordp->MSV3[0] == 'J' || recordp->MSV3[0] == '1') recordp->MSV3[0] = '1';
	else recordp->MSV3[0] = '0';

	if(recordp->TLIEF[0] == 'J' || recordp->TLIEF[0] == '1') recordp->TLIEF[0] = '1';
	else recordp->TLIEF[0] = '0';

	// --- update/insert recordp

	EXEC SQL EXECUTE upd_auftragartkd USING
											:recordp->IDF,
											:recordp->AA,
											:recordp->VMO,
											:recordp->NATRA,
											:recordp->NETTO,
											:recordp->BANR,
											'0',
											:recordp->VBSP,
											:recordp->VSP,
											:recordp->VVMO,
											'1',
											:recordp->ART,
											:recordp->STF,
											:recordp->FIL,
											:recordp->IDF,
											:datum,
											:dbzeit,
											'1',
											'I',
											:recordp->MORAB,
											:recordp->FRAUKE,
											:recordp->MSV3,
											:recordp->TLIEF,
											:recordp->AKENN,
											:recordp->FIL,
											:recordp->IDF,
											:recordp->AA;
	SQL_ERRMSG( "upd auftragartkd1:" )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
	    exec sql insert into auftragartkd (LDAUFTRAGARTKD_LISTE) values (
											:recordp->IDF,
											:recordp->AA,
											:recordp->VMO,
											:recordp->NATRA,
											:recordp->NETTO,
											:recordp->BANR,
											'0',
											:recordp->VBSP,
											:recordp->VSP,
											:recordp->VVMO,
											'1',
											:recordp->ART,
											:recordp->STF,
											:recordp->FIL,
											:recordp->IDF,
											:datum,
											:dbzeit,
											'1',
											'I',
											:recordp->MORAB,
											:recordp->FRAUKE,
											:recordp->MSV3,
											:recordp->TLIEF,
											:recordp->AKENN
											);
		SQL_ERRMSG( "insert auftragartkd1:" )
		++sqlstat.ins;
	}
	else
	{
		++sqlstat.upd;
	}
	return OK;
}

// -------------------------------------------------------------------
int AfterLoadAufart()
{
	return DelNotUpdatedAufart();
}

// -------------------------------------------------------------------
int  FetchCursor (EXEC SQL BEGIN DECLARE SECTION;
				  PARAMETER const char * cursorid,
				  EXEC SQL END DECLARE SECTION;
				  const char * const msg         )
{
	const char * const FUN = "FetchCursor";

	EXEC SQL FETCH :cursorid;
	SQL_ERRMSG( msg )

	return SQLCODE;
}

// -------------------------------------------------------------------
/* use select cursor: so number of transactions can be controlled   */
int SetNotUpdatedAufart()
{
	#define SETCURSORID		"CursorSetNotUpdated"

	const char * const FUN = "SetNotUpdatedAufart";

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	const char * pCursorId = SETCURSORID;
	EXEC SQL END DECLARE SECTION;


	pStmt =	"select 1 from auftragartkd where kzupd != '0' and vertriebszentrumnr = ? for update;";

	EXEC SQL PREPARE sel_SetNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare sel_SetNotUp" )
	EXEC SQL DECLARE :pCursorId CURSOR WITH HOLD FOR sel_SetNotUp;


	pStmt = "update auftragartkd set kzupd = '0' where current of " SETCURSORID ";";

	EXEC SQL PREPARE upd_SetNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare SetNotUp" )


	EXEC SQL OPEN :pCursorId using :sBranchno;
    SQL_ERRMSG( "open SetNotUp" )

    EXEC SQL BEGIN WORK;
	SQL_ERRMSG( "begin work" )

	while ( OK == FetchCursor(pCursorId, "fetch SetNotUp") )
	{
		EXEC SQL EXECUTE upd_SetNotUp;
		SQL_ERRMSG( "execute upd_SetNotUp" )

		++sqlstat.upd_exist;

		if ( sqlstat.upd_exist % TRANSACTLOOP == 0)
		{
			EXEC SQL COMMIT WORK;
			SQL_ERRMSG( "commit work between" )

			EXEC SQL BEGIN WORK;
			SQL_ERRMSG( "begin work between" )
		}
	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG( "commit work" )

	EXEC SQL CLOSE :pCursorId;
    SQL_ERRMSG( "close SetNotUp" )

	return OK;
}

// -------------------------------------------------------------------
/* use select cursor: so number of transactions can be controlled   */
int DelNotUpdatedAufart()
{
	#define DELCURSORID		"CursorDelNotUpdated"

	const char * const FUN = "DelNotUpdatedAufart";

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	const char * pCursorId = DELCURSORID;
	EXEC SQL END DECLARE SECTION;


	pStmt = "select 1 from auftragartkd where kzupd = '0' and vertriebszentrumnr = ? for update";

	EXEC SQL PREPARE sel_DelNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare sel_DelNotUp" )
	EXEC SQL DECLARE :pCursorId CURSOR WITH HOLD FOR sel_DelNotUp;


	pStmt = "delete from auftragartkd "
			"where current of " DELCURSORID ";";

	EXEC SQL PREPARE del_DelNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare del_DelNotUp" )


	EXEC SQL OPEN :pCursorId using :sBranchno;
    SQL_ERRMSG( "open DelNotUp" )

    EXEC SQL BEGIN WORK;
	SQL_ERRMSG( "begin work" )

	while ( OK == FetchCursor(pCursorId, "fetch DelNotUp") )
	{
		EXEC SQL EXECUTE del_DelNotUp;
		SQL_ERRMSG( "execute del_DelNotUp" )

		++sqlstat.del_missing;

		if ( sqlstat.del_missing % TRANSACTLOOP == 0)
		{
			EXEC SQL COMMIT WORK;
			SQL_ERRMSG( "commit work between" )

			EXEC SQL BEGIN WORK;
			SQL_ERRMSG( "begin work between" )
		}
	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG( "commit work" )

	EXEC SQL CLOSE :pCursorId;
    SQL_ERRMSG( "close DelNotUp" )

	return OK;
}

/***** end of file *****************************************************************/


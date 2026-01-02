/* ---------------------------------------------------------------------------
 *  loadpayterm.cxx 
 *     load SAP payment terms from VSAM.DKZBC into SQL paymentterms
 *
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadpayterm"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "payterm.h"
#include "dkzbc.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loadpayterm"
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

#define TRANSACTLOOP	2000

// -------------------------------------------------------------------

struct SqlStat
{
	int ins;			// new rows
	int upd;			// updated rows
	int upd_exist;		// update already existing rows
	int del_flag;		// deleted rows because of DKZBC delete flag
	int del_missing;	// deleted rows because of missing in DKZBC
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

int  StartLoadPayTerm     (FILE * pFile, 
						   const char * const database);
int  PrepareLoadPayTerm   ();
int  LoadPayTerm          (struct O_DKZBC * pRecord);
int  AfterLoadPayTerm     ();

int  SetNotUpdatedPayTerm ();
int  DelNotUpdatedPayTerm ();
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
		rc = StartLoadPayTerm(pFile, database);
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
			struct O_DKZBC * pDummy = (struct O_DKZBC *)line;
					
			long allowed = (long)pDummy->FILLER - (long)pDummy;
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
int StartLoadPayTerm(FILE * pFile, const char * const database)
{
	const char * const FUN = "StartLoadPayTerm";
	int    		 	   rc;

	if ( OK != (rc = DbConnect(database)) )
		return rc;

	if ( OK != (rc = PrepareLoadPayTerm()) )
	{
		DbDisconnect();
		return rc;	
	}
	
	char line[sizeof(struct O_DKZBC) + 3] = { 0 };	/* possibly CR + LF + '\0' */
	
	DEBUG_SECTION
		char msg[256];
		sprintf(msg, 
				"sizeof(O_DKZBC) = %d, O_DKZBC.TABLE items = %d, sizeof(line) = %d", 
				sizeof(struct O_DKZBC),
				L_DKZBC_TAB,
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
			rc = LoadPayTerm((struct O_DKZBC *)line);

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
		
		// 1 line can generate up to L_DKZBC_TAB inserts/updates
		if ( filestat.proc % (TRANSACTLOOP/L_DKZBC_TAB) == 0 )
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
		rc = AfterLoadPayTerm();

	DbDisconnect();
		
	return rc;
}

// -------------------------------------------------------------------
int PrepareLoadPayTerm()
{
	const char * const FUN = "PrepareLoadPayTerm";

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;


	/* cursor select */
	pStmt =	"select UPD_FLAG from paymentterms "
			"where PAYMENT_TERM = ? and PAYMENTARGET = ? "
			"for update;";

	EXEC SQL PREPARE sel_load FROM :pStmt;
	SQL_ERRMSG( "prepare sel_load" );
	exec sql declare CselLoad cursor with hold for sel_load;
	

	/* insert */
	pStmt = "insert into paymentterms "
			"(PAYMENT_TERM, PAYMENTARGET, CASHDISOUNT, UPD_FLAG) "
			"values "
			"(?, ?, ?, '1');";

	EXEC SQL PREPARE ins_load FROM :pStmt;
	SQL_ERRMSG( "prepare ins_load" );
	

	/* update */
	pStmt =  "update paymentterms "
			 "set CASHDISOUNT = ?, UPD_FLAG = '1' "
			 "where current of CselLoad;";

	EXEC SQL PREPARE upd_load FROM :pStmt;
	SQL_ERRMSG( "prepare upd_load" )
		
	/* delete */
	pStmt =  "delete from paymentterms where PAYMENT_TERM = ?;"; 

	EXEC SQL PREPARE del_load FROM :pStmt;
	SQL_ERRMSG( "prepare del_load" )
		
	return SetNotUpdatedPayTerm();
}

// ------------------------------------------------------------------- 
int LoadPayTerm (struct O_DKZBC * record)
{
	const char * const FUN = "LoadPayTerm";


	// --- check valid SAPCODE/payment term
	if ( FALSE == IsValidString(record->SAPCODE, sizeof(record->SAPCODE)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "SAPCODE not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}


	// --- convert SAPCODE to PAYMENT_TERM
	EXEC SQL BEGIN DECLARE SECTION;
	paytermS row = { 0 };
	EXEC SQL END DECLARE SECTION;
	
	strncpy(row.PAYMENT_TERM, record->SAPCODE, sizeof(record->SAPCODE));
	
	
	// --- check delete flag
	if ('J' == record->DELFLAG[0])
	{
		EXEC SQL EXECUTE del_load using :row.PAYMENT_TERM; 
		SQL_ERRMSG("del_load")
	
		sqlstat.del_flag += sqlca.sqlerrd[2];

		DEBUG_SECTION
			char msg[256];
			sprintf(msg, "delete row - key: <%*.*s>   %*s ; processed rows: %2d",
						 L_DKZBC_SAPCODE, L_DKZBC_SAPCODE, 
						 row.PAYMENT_TERM,
						 L_DKZBC_TAB_DAYS,
						 " ",
						 sqlca.sqlerrd[2]);
			LogMsg(FUN, msg, FL_INFO); 
		END_DEBUG_SECTION
			
		return OK;
	}

	
	// --- update/insert row
		
	const int PREDIGITS = L_DKZBC_TAB_CASHDISCOUNT - N_DKZBC_TAB_CASHDISCOUNT;

	char target  [sizeof(record->TABLE[0].DAYS        ) + 1] = { 0 };
	char discount[sizeof(record->TABLE[0].CASHDISCOUNT) + 2] = { 0 };
	
	discount[PREDIGITS] = '.';

	int fl_upd;						// update or insert?
	int fl_validcol = FALSE;		// at least 1 valid payment target

	for (int i = 0; i < L_DKZBC_TAB; ++i)
	{
		if ( FALSE == IsValidNumber(record->TABLE[i].DAYS, 
					                sizeof(record->TABLE[i].DAYS)) ) 
		{
			if ( FALSE == IsValidNumber(record->TABLE[i].CASHDISCOUNT, 
					                    sizeof(record->TABLE[i].CASHDISCOUNT)) ) 
				continue;	// skip record-column / row
		}

		fl_validcol = TRUE;
	
		
		strncpy(target, record->TABLE[i].DAYS, sizeof(record->TABLE[i].DAYS));
		row.PAYMENTARGET = atoi(target); 

		strncpy(discount,
				record->TABLE[i].CASHDISCOUNT,
				PREDIGITS); 
		strncpy(discount                      + PREDIGITS + 1,
				record->TABLE[i].CASHDISCOUNT + PREDIGITS    ,
				N_DKZBC_TAB_CASHDISCOUNT); 
		row.CASHDISOUNT = atof(discount);

		
		EXEC SQL open CselLoad USING :row.PAYMENT_TERM, :row.PAYMENTARGET;
		SQL_ERRMSG("open CselLoad")

		EXEC SQL fetch CselLoad into :row.UPD_FLAG;
		SQL_ERRMSG("fetch CselLoad")
		
		if ( SQLCODE == 100 )
		{
			fl_upd = FALSE;
			
			EXEC SQL EXECUTE ins_load using :row.PAYMENT_TERM, 
											:row.PAYMENTARGET, 
											:row.CASHDISOUNT;
			SQL_ERRMSG("ins_load")

			++sqlstat.ins;	
		}
		else
		{
			fl_upd = TRUE;

			if ( 0 == strcmp("1", row.UPD_FLAG) )	
			{
				char msg[256];
				sprintf(msg, "row repeatedly written: term %s, target %d",
						row.PAYMENT_TERM,
						row.PAYMENTARGET);
				LogMsg(FUN, msg, FL_WARN);
			}

			EXEC SQL EXECUTE upd_load using :row.CASHDISOUNT;
			SQL_ERRMSG("upd_load")

			++sqlstat.upd;	
		}

		DEBUG_SECTION
			char msg[256];	
			sprintf(msg,
					(0 == i) ? "%s row - key: <%-*.*s>, <%*d>; file col %2d; "
					           "value: <%*.*f>" 
							 : "%s row - key:  %-*.*s   <%*d>; file col %2d: "
							   "value: <%*.*f>",
					fl_upd ? "update" : "insert",
					L_DKZBC_SAPCODE, L_DKZBC_SAPCODE, 
					(0 == i) ? row.PAYMENT_TERM : " \"",
					L_DKZBC_TAB_DAYS, 
					row.PAYMENTARGET,
					i,
					L_DKZBC_TAB_CASHDISCOUNT + 1, N_DKZBC_TAB_CASHDISCOUNT,  
					row.CASHDISOUNT);		
			LogMsg(FUN, msg, FL_INFO); 
		END_DEBUG_SECTION
	}
	
	if (FALSE == fl_validcol)
	{
		DEBUG_SECTION
			char msg[256];
			sprintf(msg, "no valid payment targets and cash discounts "
					     "found for payment term %s",
					row.PAYMENT_TERM);
			LogMsg(FUN, msg, FL_INFO); 
		END_DEBUG_SECTION

		return WARNING;	// -> skip line	
	}
	
	return OK;
}

// -------------------------------------------------------------------
int AfterLoadPayTerm()
{
	return DelNotUpdatedPayTerm();
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
int SetNotUpdatedPayTerm()
{
	#define SETCURSORID		"CursorSetNotUpdated"
	
	const char * const FUN = "SetNotUpdatedPayTerm";

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	const char * pCursorId = SETCURSORID; 
	EXEC SQL END DECLARE SECTION;

	
	pStmt =	"select 1 from paymentterms where upd_flag != '0' for update;";

	EXEC SQL PREPARE sel_SetNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare sel_SetNotUp" )
	EXEC SQL DECLARE :pCursorId CURSOR WITH HOLD FOR sel_SetNotUp;
	
	
	pStmt = "update paymentterms set upd_flag = '0' where current of " SETCURSORID ";";
	
	EXEC SQL PREPARE upd_SetNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare SetNotUp" )

		
	EXEC SQL OPEN :pCursorId;
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
int DelNotUpdatedPayTerm()
{
	#define DELCURSORID		"CursorDelNotUpdated"
	
	const char * const FUN = "DelNotUpdatedPayTerm";

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	const char * pCursorId = DELCURSORID; 
	EXEC SQL END DECLARE SECTION;


	pStmt = "select 1 from paymentterms where upd_flag = '0' for update";

	EXEC SQL PREPARE sel_DelNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare sel_DelNotUp" )
	EXEC SQL DECLARE :pCursorId CURSOR WITH HOLD FOR sel_DelNotUp;
	

	pStmt = "delete from paymentterms "
			"where current of " DELCURSORID ";";
	
	EXEC SQL PREPARE del_DelNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare del_DelNotUp" )

		
	EXEC SQL OPEN :pCursorId;
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


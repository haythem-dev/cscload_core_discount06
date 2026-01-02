/* ---------------------------------------------------------------------------
 *  loadcstcalcavp.cxx    
 *     load VSAM file DKKWB into KSC table cstcalcavp
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadcstcalcavp"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "cstcalcavp.h"
#include "dkkwb.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loadcstcalcavp"
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
	int upd;			// updated rows
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
short sBranchNo;
char database[81];
EXEC SQL END DECLARE SECTION;
 
// -------------------------------------------------------------------

int  DbConnect			  ();
int  DbDisconnect		  ();

int  Start                (FILE * pFile); 
int  Prepare              ();
int  Load                 (struct O_DKKWB * pRecord);
int  AfterLoad            ();
int  Delete			      ();

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
				 sBranchNo = atoi(argv[i] );
		}
		else if ( !strcmp( argv[i], "-version" ) )
		{
			printVersion(versioninfo);
			bVersion = TRUE;
			return 0;
		}
       	else
  		{
  			rc = ERROR;
  			break;
  		}
	}
	
	if ( (1     == argc)	    		|| 
		 (ERROR == rc)      			||
		 (0     == sBranchNo)			||
		 (0     == strlen(database))	||
		 (0     == strlen(loadpath))	   )
	{
		char msg[256];
		sprintf(msg, "  usage: %s\n"
	   				 "\t { -dg       <debugging> }\n"
					 "\t { -file     <Input File Name> }\n"
					 "\t { -db       <Database Name> }\n"
					 "\t { -branchno <Branch No.> }\n",
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
   	
	LogMsg( FUN, "----------------------------------------------------------------", FL_INFO);
	LogMsg( FUN, "started", FL_INFO);

	char loadpath[256] 	= { 0 };
	int  rc;
	
	if (OK != (rc = getCmdLine(loadpath, argc, argv)) )
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
		rc = Start(pFile);
		fclose(pFile);
	}
		
	PrintStat();
	sprintf(msg, "finished with exit code %d", rc);
   	LogMsg( FUN, msg, (rc == OK) ? FL_INFO: FL_FAIL);
	LogMsg( FUN, "----------------------------------------------------------------", FL_INFO);

   	return rc;
 }// main

// -------------------------------------------------------------------
int DbConnect ( )
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
			struct O_DKKWB * pDummy = (struct O_DKKWB *)line;
			
			long allowed = (long)pDummy->FILLER - (long)pDummy;
			long offset  = pBuf - line;

			if (offset >= allowed)
				return OK;

			DEBUG_SECTION
				sprintf( msg, "linefeed 0x0A found at column %d; should be column >= %d",offset,allowed);
				LogMsg(FUN, msg, FL_WARN); 
			END_DEBUG_SECTION

			return WARNING;
		}
	}

	sprintf(msg, "no linefeed 0x0A found in line (max. length = %d)", len);
	LogMsg(FUN, msg, FL_FAIL);

	return ERROR;
}// CheckLine

// -------------------------------------------------------------------
int Start(FILE * pFile)
{
	const char * const FUN = "Start";
	int    		 	   rc;

	if ( OK != (rc = DbConnect()) )
		return rc;

	if ( OK != (rc = Delete()) )
	{
		DbDisconnect();
		return rc;	
	}

	if ( OK != (rc = Prepare()) )
	{
		DbDisconnect();
		return rc;	
	}
	
	char line[sizeof(struct O_DKKWB) + 3] = { 0 };	/* possibly CR + LF + '\0' */
	
	DEBUG_SECTION
		char msg[256];
		sprintf(msg, "sizeof(O_DKKWB) = %d, sizeof(line) = %d", sizeof(struct O_DKKWB),sizeof(line));	
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
			rc = Load((struct O_DKKWB *)line);

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
}// Start

// -------------------------------------------------------------------
int Prepare()
{
	const char * const FUN = "Prepare";
	int rc;

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;

	/* cursor select */
	pStmt =	"select surchargepct from cstcalcavp "
			"where BRANCHNO = ? and CUSTOMERNO = ? and ABDACODE = ? and PRICE_GROUP = ? and PREIS_TYP = ? "
			"for update;";

	EXEC SQL PREPARE sel_load FROM :pStmt;
	SQL_ERRMSG( "prepare sel_load" );
	exec sql declare CselLoad cursor with hold for sel_load;
	
	/* insert */
	pStmt = "insert into cstcalcavp ("
			"BRANCHNO,"
			"CUSTOMERNO,"
			"ABDACODE,"
			"SURCHARGE_BASIC,"
			"DEDUCTION_BASIC,"
			"SURCHARGEPCT,"
			"DEDUCTIONPCT,"
			"PRICE_GROUP,"
			"PREIS_TYP"
			" ) values (?, ?, ?, ?, ?, ?, ?, ?, ? );";

	EXEC SQL PREPARE ins_load FROM :pStmt;
	SQL_ERRMSG( "prepare ins_load" );
	

	/* update */
	pStmt =  "update cstcalcavp set "
			 "SURCHARGE_BASIC = ?, "
			 "DEDUCTION_BASIC = ?, "
			 "SURCHARGEPCT = ?, "
			 "DEDUCTIONPCT = ?, "
			 "PRICE_GROUP = ?, "
			 "PREIS_TYP = ? "
			 "where current of CselLoad;";

	EXEC SQL PREPARE upd_load FROM :pStmt;
	SQL_ERRMSG( "prepare upd_load" )
		
		
	return OK;
}// Prepare

// ------------------------------------------------------------------- 
int Load (struct O_DKKWB * record)
{
	const char * const FUN = "Load";

	// --- check valid branchno
	if ( FALSE == IsValidNumber(record->BRANCHNO, sizeof(record->BRANCHNO)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "BRANCHNO not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- check valid customerno
	if ( FALSE == IsValidNumber(record->CUSTOMERNO, sizeof(record->CUSTOMERNO)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "CUSTOMERNO not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- check valid abdaacode
	if ( FALSE == IsValidNumber(record->ABDACODE, sizeof(record->ABDACODE)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "ABDACODE not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- check valid surchargepct
/*	if ( FALSE == IsValidNumber(record->SURCHARGEPCT, sizeof(record->SURCHARGEPCT)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "SURCHARGEPCT not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- check valid deductionpct
	if ( FALSE == IsValidNumber(record->DEDUCTIONPCT, sizeof(record->DEDUCTIONPCT)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "DEDUCTIONPCT not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}
*/

	// --- convert
	EXEC SQL BEGIN DECLARE SECTION;
	struct N_CSTCALCAVP row = { 0 };
	long cstcalcavp;
	EXEC SQL END DECLARE SECTION;
	
	struct S_CSTCALCAVP buf = { 0 };

	strncpy(buf.BRANCHNO		, record->BRANCHNO		, sizeof(record->BRANCHNO  	));
	strncpy(buf.CUSTOMERNO		, record->CUSTOMERNO    , sizeof(record->CUSTOMERNO	));
	strncpy(buf.ABDACODE 		, record->ABDACODE		, sizeof(record->ABDACODE	));
	strncpy(buf.SURCHARGEPCT	, record->SURCHARGEPCT	, sizeof(record->SURCHARGEPCT	    ));
	strncpy(buf.DEDUCTIONPCT	, record->DEDUCTIONPCT	, sizeof(record->DEDUCTIONPCT	    ));
	strncpy(buf.PREIS_TYP		, record->FVKK			, sizeof(record->FVKK	    ));
	
	// 0 and 1 are vice versa in DKKWB and cstcalcavp!
	if( "0" == record->BASIS) {
		strncpy(buf.SURCHARGE_BASIC, "1", 1);
		strncpy(buf.DEDUCTION_BASIC, "1", 1);
	}
	else {
		strncpy(buf.SURCHARGE_BASIC, "0", 1);
		strncpy(buf.DEDUCTION_BASIC, "0", 1);
	}
	
	row.BRANCHNO   			= atoi(buf.BRANCHNO  	);
	row.CUSTOMERNO			= atol(buf.CUSTOMERNO	);
	if(buf.ABDACODE[0] == '0')
	{
		row.ABDACODE[0]			= buf.ABDACODE[1]	 ;
		row.ABDACODE[1]			= '\0'	 ;
	}
	else
	{
		row.ABDACODE[0]			= buf.ABDACODE[0]	 ;
		row.ABDACODE[1]			= buf.ABDACODE[1]	 ;
		row.ABDACODE[2]			= '\0'	 ;
	}
	row.SURCHARGE_BASIC   	= atoi(buf.SURCHARGE_BASIC  	);
	row.DEDUCTION_BASIC   	= atoi(buf.DEDUCTION_BASIC  	);
	row.SURCHARGEPCT   		= atof(buf.SURCHARGEPCT  	)/100;
	row.DEDUCTIONPCT   		= atof(buf.DEDUCTIONPCT  	)/100;
	row.PREIS_TYP   		= atof(buf.PREIS_TYP  	);
	row.PRICE_GROUP   		= 0;

	if(row.SURCHARGEPCT == 0  && row.DEDUCTIONPCT == 0)
	{
		LogMsg(FUN, "No pcts ", FL_WARN);
		return WARNING;	// skip record
	}
	
	// --- update/insert row
	EXEC SQL open CselLoad USING :row.BRANCHNO, 
		 						 :row.CUSTOMERNO, 
								 :row.ABDACODE,
								 :row.PRICE_GROUP,
								 :row.PREIS_TYP;
	SQL_ERRMSG("open CselLoad")

	EXEC SQL fetch CselLoad into :cstcalcavp;
	SQL_ERRMSG("fetch CselLoad")
		
	int fl_upd;						// update or insert?

	if ( 100 == SQLCODE )
	{
		fl_upd = FALSE;
		
		EXEC SQL EXECUTE ins_load using :row.BRANCHNO,
						:row.CUSTOMERNO, 
						:row.ABDACODE,
						:row.SURCHARGE_BASIC, 
						:row.DEDUCTION_BASIC, 
						:row.SURCHARGEPCT, 
						:row.DEDUCTIONPCT,
						:row.PRICE_GROUP,
						:row.PREIS_TYP;
		SQL_ERRMSG("ins_load")

		++sqlstat.ins;	
	}
	else
	{
		fl_upd = TRUE;
		EXEC SQL EXECUTE upd_load using :row.SURCHARGE_BASIC, 
						:row.DEDUCTION_BASIC, 
						:row.SURCHARGEPCT, 
						:row.DEDUCTIONPCT,
						:row.PRICE_GROUP,
						:row.PREIS_TYP;
		SQL_ERRMSG("upd_load")

		++sqlstat.upd;	
	}

	
	return OK;
}// Load

// -------------------------------------------------------------------
int AfterLoad()
{
	return OK;
} // AfterLoad

// -------------------------------------------------------------------
int Delete()
{
	const char * const FUN = "Delete";
	int rc;

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;

	/* cursor select */
	pStmt =	"select 1 from cstcalcavp "
			"where BRANCHNO = ?"
			"for update;";

	EXEC SQL PREPARE sel_notupd FROM :pStmt;
	SQL_ERRMSG( "prepare sel_notupd" );
	exec sql declare CDelNotupd cursor with hold for sel_notupd;

	/* delete */
	pStmt =  "delete from cstcalcavp "
			 "where current of CDelNotupd;";

	EXEC SQL PREPARE del_notupd FROM :pStmt;
	SQL_ERRMSG( "prepare del_notupd" )
	
	EXEC SQL open CDelNotupd USING :sBranchNo;

	EXEC SQL begin work;
	SQL_ERRMSG("begin work start")

	for(int i = 1;;i++)
	{
		if ( filestat.proc % TRANSACTLOOP == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work between")
			
			EXEC SQL begin work;
			SQL_ERRMSG("begin work between")
		}
		EXEC SQL fetch CDelNotupd;
		SQL_ERRMSG("fetch CDelNotupd")

		if(SQLCODE == 100)
			break;

		EXEC SQL EXECUTE del_notupd;
		SQL_ERRMSG("del_notupd")
	}
	EXEC SQL commit work;
	SQL_ERRMSG("commit work ende")

	return OK;
}// Delete


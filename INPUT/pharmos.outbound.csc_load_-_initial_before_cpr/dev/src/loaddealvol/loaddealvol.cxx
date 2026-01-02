/* ---------------------------------------------------------------------------
 *  loaddealvol.cxx    
 *     load dealer volume
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loaddealvol"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "pplib/allg.h"
#include "dealervolume.h"
#include "dkdum.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loaddealvol"
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
short sBranchno;
int datum;
EXEC SQL END DECLARE SECTION;
 
// -------------------------------------------------------------------

int  DbConnect			  (const char * database);
int  DbDisconnect		  ();

int  Start                (FILE * pFile, 
						   const char * const database);
int  Prepare              ();
int  Load                 (struct O_DKDUM * pRecord);
int  AfterLoad            ();

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
	sprintf(msg, "    deleted  : %4d", sqlstat.del);
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
			struct O_DKDUM * pDummy = (struct O_DKDUM *)line;
			
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
	
	char line[sizeof(struct O_DKDUM) + 3] = { 0 };	/* possibly CR + LF + '\0' */
	
	DEBUG_SECTION
		char msg[256];
		sprintf(msg, 
				"sizeof(O_DKDUM) = %d, sizeof(line) = %d", 
				sizeof(struct O_DKDUM),
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
			rc = Load((struct O_DKDUM *)line);

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


	/* cursor select */
	pStmt =	"select 1 from dealervolume "
			"where BRANCHNO = ? and UID = ? "
			  "and INVOICENO = ? and DATEINVOICE = ? "
			"for update;";

	EXEC SQL PREPARE sel_load FROM :pStmt;
	SQL_ERRMSG( "prepare sel_load" );
	exec sql declare CselLoad cursor with hold for sel_load;
	

	/* insert */
	pStmt = "insert into dealervolume "
			"(BRANCHNO, UID, INVOICENO, "
			 "ORDERNOVSE, ORDERNOKSC, "
			 "DATEINVOICE, TIMEINVOICE, "
			 "INVOICEVOLUME, "
			 "CUSTOMERNO, "
			 "VOLUME1, VOLUME2, VOLUME3, VOLUME4, "
			 "VOLUMESTATE )"
			"values "
			"(?, ?, ?, "
			 "?, ?, "
			 "?, ?, "
			 "?, "
			 "?, "
			 "?, ?, ?, ?, "
			 "?);";

	EXEC SQL PREPARE ins_load FROM :pStmt;
	SQL_ERRMSG( "prepare ins_load" );
	

	/* update */
	pStmt =  "update dealervolume "
			 "set ORDERNOVSE = ?, "
			     "ORDERNOKSC = ?, "
				 "TIMEINVOICE = ?, "
				 "INVOICEVOLUME = ?, "
				 "VOLUME1 = ?, "
				 "VOLUME2 = ?, "
				 "VOLUME3 = ?, "
				 "VOLUME4 = ?, "
				 "CUSTOMERNO = ?, "
				 "VOLUMESTATE = ? "
			 "where current of CselLoad;";

	EXEC SQL PREPARE upd_load FROM :pStmt;
	SQL_ERRMSG( "prepare upd_load" )

	/* cursor for delete select */
	pStmt =	"select 1 from dealervolume "
			"where BRANCHNO = ? "
			"and DATEINVOICE < ? "
			"for update;";

	EXEC SQL PREPARE del_load FROM :pStmt;
	SQL_ERRMSG( "prepare del_load" );
	exec sql declare CdelLoad cursor with hold for del_load;

	/* delete */
	pStmt =  "delete from dealervolume "
			 "where current of CdelLoad;";

	EXEC SQL PREPARE deleteold FROM :pStmt;
	SQL_ERRMSG( "prepare deleteold" )
		
		
	return OK;
}

// ------------------------------------------------------------------- 
int Load (struct O_DKDUM * record)
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

	// --- check valid dateinvoice
	if ( FALSE == IsValidNumber(record->DATEINVOICE, sizeof(record->DATEINVOICE)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "DATEINVOICE not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}


	// --- convert
	EXEC SQL BEGIN DECLARE SECTION;
	struct N_DEALERVOLUME row = { 0 };
	EXEC SQL END DECLARE SECTION;
	
	struct S_DEALERVOLUME buf = { 0 };

	const int PREDIGITS_0 = L_DKDUM_VOLUME_INVOICE - N_DKDUM_VOLUME_INVOICE;
	const int PREDIGITS_1 = L_DKDUM_VOLUME1        - N_DKDUM_VOLUME1;
	const int PREDIGITS_2 = L_DKDUM_VOLUME2        - N_DKDUM_VOLUME2;
	const int PREDIGITS_3 = L_DKDUM_VOLUME3        - N_DKDUM_VOLUME3;
	const int PREDIGITS_4 = L_DKDUM_VOLUME4        - N_DKDUM_VOLUME4;

	buf.INVOICEVOLUME[PREDIGITS_0] = '.';
	buf.VOLUME1      [PREDIGITS_1] = '.';
	buf.VOLUME2      [PREDIGITS_2] = '.';
	buf.VOLUME3      [PREDIGITS_3] = '.';
	buf.VOLUME4      [PREDIGITS_4] = '.';
	
	strncpy(buf.BRANCHNO  	 , record->BRANCHNO  	 , sizeof(record->BRANCHNO  	));
	strncpy(buf.UID       	 , record->UID     		 , sizeof(record->UID			));
	strncpy(buf.INVOICENO	 , record->INVOICENO	 , sizeof(record->INVOICENO		));
	strncpy(buf.ORDERNOVSE	 , record->ORDERNOPHARMOS, sizeof(record->ORDERNOPHARMOS));
	strncpy(buf.ORDERNOKSC	 , record->ORDERNOKSC    , sizeof(record->ORDERNOKSC    ));
	strncpy(buf.DATEINVOICE	 , record->DATEINVOICE	 , sizeof(record->DATEINVOICE	));
	strncpy(buf.TIMEINVOICE	 , record->TIMEINVOICE	 , sizeof(record->TIMEINVOICE	));
	strncpy(buf.CUSTOMERNO	 , record->TIMEINVOICE	 , sizeof(record->TIMEINVOICE	));
	strncpy(buf.CUSTOMERNO	 , record->CUSTOMERNO	 , sizeof(record->CUSTOMERNO	));
	strncpy(buf.VOLUMESTATE	 , record->VOLUMESTATE	 , sizeof(record->VOLUMESTATE	));
	
	strncpy(buf.INVOICEVOLUME, 
			record->VOLUME_INVOICE, 
			PREDIGITS_0);
	strncpy(buf    .INVOICEVOLUME  + PREDIGITS_0 + 1, 
			record->VOLUME_INVOICE + PREDIGITS_0    ,
			N_DKDUM_VOLUME_INVOICE);
	
	strncpy(buf.VOLUME1, 
			record->VOLUME1, 
			PREDIGITS_1);
	strncpy(buf    .VOLUME1 + PREDIGITS_1 + 1, 
			record->VOLUME1 + PREDIGITS_1    ,
			N_DKDUM_VOLUME1);
	
	strncpy(buf.VOLUME2, 
			record->VOLUME2, 
			PREDIGITS_2);
	strncpy(buf    .VOLUME2 + PREDIGITS_2 + 1, 
			record->VOLUME2 + PREDIGITS_2    ,
			N_DKDUM_VOLUME2);
	
	strncpy(buf.VOLUME3, 
			record->VOLUME3, 
			PREDIGITS_3);
	strncpy(buf    .VOLUME3 + PREDIGITS_3 + 1, 
			record->VOLUME3 + PREDIGITS_3    ,
			N_DKDUM_VOLUME3);
	
	strncpy(buf.VOLUME4, 
			record->VOLUME4, 
			PREDIGITS_4);
	strncpy(buf    .VOLUME4 + PREDIGITS_4 + 1, 
			record->VOLUME4 + PREDIGITS_4    ,
			N_DKDUM_VOLUME4);
	

	row.BRANCHNO   		= atoi(buf.BRANCHNO  	);
	row.UID				= atol(buf.UID			);
	row.INVOICENO		= atol(buf.INVOICENO    );
	row.ORDERNOVSE      = atol(buf.ORDERNOVSE	);
	row.ORDERNOKSC      = atol(buf.ORDERNOKSC	);
	row.DATEINVOICE		= atol(buf.DATEINVOICE	);
	row.TIMEINVOICE		= atol(buf.TIMEINVOICE	);
	row.INVOICEVOLUME	= atof(buf.INVOICEVOLUME);
	row.VOLUME1			= atof(buf.VOLUME1		);
	row.VOLUME2			= atof(buf.VOLUME2		);
	row.VOLUME3			= atof(buf.VOLUME3		);
	row.VOLUME4			= atof(buf.VOLUME4		);
	row.CUSTOMERNO		= atol(buf.CUSTOMERNO	);
	row.VOLUMESTATE[0]	= buf.VOLUMESTATE[0]	 ;

	sBranchno = row.BRANCHNO;
	// correct date: complete year
	row.DATEINVOICE += 20000000;
	
	
	// --- update/insert row
	EXEC SQL open CselLoad USING :row.BRANCHNO, 
		 						 :row.UID, 
								 :row.INVOICENO, 
								 :row.DATEINVOICE;
	SQL_ERRMSG("open CselLoad")

	EXEC SQL fetch CselLoad;
	SQL_ERRMSG("fetch CselLoad")
		
	int fl_upd;						// update or insert?

	if ( SQLCODE == 100 )
	{
		fl_upd = FALSE;
		
		EXEC SQL EXECUTE ins_load using :row.BRANCHNO,
			 							:row.UID, 
										:row.INVOICENO,
										:row.ORDERNOVSE, 
										:row.ORDERNOKSC, 
										:row.DATEINVOICE, 
										:row.TIMEINVOICE,
										:row.INVOICEVOLUME,
										:row.CUSTOMERNO,
										:row.VOLUME1, 
										:row.VOLUME2, 
										:row.VOLUME3, 
										:row.VOLUME4,
										:row.VOLUMESTATE;
		SQL_ERRMSG("ins_load")

		++sqlstat.ins;	
	}
	else
	{
		fl_upd = TRUE;


		EXEC SQL EXECUTE upd_load using :row.ORDERNOVSE, 
										:row.ORDERNOKSC, 
										:row.TIMEINVOICE,
										:row.INVOICEVOLUME,
										:row.VOLUME1, 
										:row.VOLUME2, 
										:row.VOLUME3, 
										:row.VOLUME4,
										:row.CUSTOMERNO,
										:row.VOLUMESTATE;
		SQL_ERRMSG("upd_load")

		++sqlstat.upd;	
	}

	DEBUG_SECTION
		char msg[256];	
		sprintf(msg,
				"%s row - key: <%*d>, <%*d>, <%*d>, <%*d>;\n"
				"    values: <%d>\n"
				"            <%d>\n"
				"            <%d>\n"
				"            <%f>\n"
				"            <%f>\n"
				"            <%f>\n"
				"            <%f>\n"
				"            <%f>", 
				fl_upd ? "update" : "insert",
				L_DKDUM_BRANCHNO   , row.BRANCHNO,
				L_DKDUM_UID        , row.UID,
				L_DKDUM_INVOICENO  , row.INVOICENO,
				L_DKDUM_DATEINVOICE, row.DATEINVOICE,
				row.ORDERNOVSE, 
				row.ORDERNOKSC, 
				row.TIMEINVOICE, 
				row.INVOICEVOLUME, 
				row.VOLUME1, 
				row.VOLUME2, 
				row.VOLUME3, 
				row.VOLUME4);
		LogMsg(FUN, msg, FL_INFO); 
	END_DEBUG_SECTION
	
	
	return OK;
}

// -------------------------------------------------------------------
int AfterLoad()
{
	const char *  const FUN      = "AfterLoad";
	char msg[256];
	datum = AllgGetDate();
	datum = AllgAddDate(datum,-90,msg);

	EXEC SQL begin work;
	SQL_ERRMSG("begin work start")

	// --- delete older row
	EXEC SQL open CdelLoad USING :sBranchno, 
		 						 :datum; 
	SQL_ERRMSG("open CdelLoad")

	for(;;)
	{
		if ( sqlstat.del % TRANSACTLOOP == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work between")
			
			EXEC SQL begin work;
			SQL_ERRMSG("begin work between")
		}
		EXEC SQL fetch CdelLoad;
		SQL_ERRMSG("fetch CdelLoad")
		if ( SQLCODE == 100 )
		{
			break;
		}
		EXEC SQL EXECUTE deleteold;
		SQL_ERRMSG("deleteold")

		++sqlstat.del;
	}

	EXEC SQL commit work;
	SQL_ERRMSG("commit work ende")

	return OK;
}


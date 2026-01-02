/* ---------------------------------------------------------------------------
 *  loadchainlimit.cxx 
 *     load debtlimit fuer Kette
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadchainlimit"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

#include "debtlimit.h"
#include "dkket.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loadchainlimit"
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

EXEC SQL BEGIN DECLARE SECTION;
short sBranchNo = 0;
EXEC SQL END DECLARE SECTION;

// -------------------------------------------------------------------

struct SqlStat
{
	int ins1;			// new rows
	int upd1;			// updated rows
	int del1;			// updated rows
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

int  Start                (FILE * pFile, 
						   const char * const database);
int  Prepare              ();
int  Load                 (struct O_DKKET * pRecord);
int  GetOrderValues		  (long vz,long maincstno,double *wertauftrag,double *wertdebit,double *wertliste5,double *wertlisteauf5);
int  AfterLoad            ();

int  DeleteList           ();
int  FetchCursor		  (const char * cursorid, 
						   const char * const msg     );

int  CheckLine			  (const char * const line, int len);
int  IsValidString		  (const char * const str , int len);
int  IsValidNumber        (const char * const str , int len);
short  GetDiffDays        (long ZielDate, long RechDate);
 
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

	sprintf(msg, "table rows:");
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    inserted K1: %4d", sqlstat.ins1);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    updated  K1: %4d", sqlstat.upd1);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "    deletet  K1: %4d", sqlstat.del1);
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
	const char * FUN = "getCmdLine";
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
				sBranchNo = atoi( argv[i] );
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
		 (0     == strlen(database))	||
		 (0     == strlen(loadpath))	||
		 (sBranchNo == 0)					)
	{
		char msg[256];
		sprintf(msg, "  usage: %s\n"
	   				 "\t { -dg   <debugging> }\n"
					 "\t { -db   <Database Name> }\n"
					 "\t { -file <Input File Name> }\n",
					 "\t { -branchno <VZ-Nummer> }\n",
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
	const char * FUN = "Main";

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
	if(bVersion) return 0;

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
			   PARAMETER const char * database;
			   EXEC SQL END DECLARE SECTION;  )
{
	const char * FUN = "DbConnect";
		
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
	const char * FUN = "DbDisconnect";
	
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
	const char * FUN = "CheckLine";
	
	char msg[64];
	
	// check line for LF 0x0A at appropriate offset
	const char * pBufEnd = line + len;	// first byte behind line buffer

	for (const char * pBuf = line; pBuf < pBufEnd; ++pBuf)
	{
		if (0x0A == *pBuf)
		{
			long allowed = sizeof(struct O_DKKET);
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
	const char * FUN = "Start";
	int    		 	   rc;

	if ( OK != (rc = DbConnect(database)) )
		return rc;

	if ( OK != (rc = Prepare()) )
	{
		DbDisconnect();
		return rc;	
	}
	
	char line[sizeof(struct O_DKKET) + 3] = { 0 };	/* possibly CR + LF + '\0' */
	
	DEBUG_SECTION
		char msg[256];
		sprintf(msg, 
				"sizeof(O_DKKET) = %d, sizeof(line) = %d", 
				sizeof(struct O_DKKET),
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
			rc = Load((struct O_DKKET *)line);

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
int Load (struct O_DKKET * record)
{
	const char * FUN = "Load";
	char huelse[81];

	// --- check valid branchno
	if ( FALSE == IsValidNumber(record->KETFIL, sizeof(record->KETFIL)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "KETFIL not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- check valid customerno
	if ( FALSE == IsValidNumber(record->KETKNR, sizeof(record->KETKNR)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "KETKNR not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- convert
	EXEC SQL BEGIN DECLARE SECTION;
	debtlimitS row = { 0 };
	int iBranch;
	int iKette;
	double dSumme;
	double dSummeday;
	double dSummeL5;
	double dSummeAufL5;
	EXEC SQL END DECLARE SECTION;
	
	sprintf(huelse,"%*.*s",L_DKKET_KETFIL,L_DKKET_KETFIL,record->KETFIL);
	iBranch   = atoi(huelse);
	sprintf(huelse,"%*.*s",L_DKKET_KETKNR,L_DKKET_KETKNR,record->KETKNR);
	iKette = atoi(huelse);
//	row.PARTNERNO = ((iBranch * 10000000) + iKette);
	row.PARTNERNO = iKette;
	sprintf(row.PARTNERNAME,"%*.*s",L_DKKET_KETNAME,L_DKKET_KETNAME,record->KETNAME);
	sprintf(huelse,"%*.*s",L_DKKET_KETKLIM1,L_DKKET_KETKLIM1,record->KETKLIM1);
	row.LIMIT = (atof(huelse)/100.0);
	if(record->KETLISTE5[0] == 'J' || record->KETLISTE5[0] == '1')
		row.LISTE5[0] = '1';
	else
		row.LISTE5[0] = '0';
	GetOrderValues(iBranch,iKette,&dSummeday,&dSumme,&dSummeL5,&dSummeAufL5);
	if(row.LISTE5[0] == '0')
	{
		row.SUM_DEBITSIDE = dSumme - dSummeL5;
		row.SUM_DAYTURNOVER = dSummeday - dSummeAufL5;
	}
	else
	{
		row.SUM_DEBITSIDE = dSumme;
		row.SUM_DAYTURNOVER = dSummeday;
	}
	row.SUM_CREDITSIDE = 0.0;
	row.SUM_MONTURNOVER = 0.0;
	row.SUM_RETURNS = 0.0;
	row.SUM_GOODSRECEIPT = 0.0;
	row.SUM_LISTE5 = 0.0;

	EXEC SQL open CselLoad1 USING :row.PARTNERNO;
	SQL_ERRMSG("open CselLoad1")

	EXEC SQL fetch CselLoad1 into :row.SUM_RETURNS;
	SQL_ERRMSG("fetch CselLoad1")
		
	if ( SQLCODE == 100 )
	{
		if(row.LIMIT > 0.0)
		{
			EXEC SQL EXECUTE ins_load1 using :row.PARTNERNO, 
										:row.LIMIT, 
										:row.SUM_DEBITSIDE,
										:row.SUM_DAYTURNOVER,
										:row.LISTE5,
										:row.SUM_LISTE5,
										:row.SUM_LISTE5;
			SQL_ERRMSG("ins_load1")
			++sqlstat.ins1;
		}
	}
	else
	{
		if(row.LIMIT > 0.0)
		{
			EXEC SQL EXECUTE upd_load1 using
				:row.PARTNERNO,
				' ',
				:row.LIMIT, 
				:row.SUM_DEBITSIDE,
				'0',
				'0',
				:row.SUM_DAYTURNOVER,
				'0',
				'0',
				'1',
				:row.LISTE5,
				:row.SUM_LISTE5,
				:row.SUM_LISTE5;
			SQL_ERRMSG("upd_load1")
			++sqlstat.upd1;
		}
		else
		{
			EXEC SQL EXECUTE del_load1;
			SQL_ERRMSG("del_load1")
			++sqlstat.del1;
		}
	}

	return OK;
}

// -------------------------------------------------------------------
int AfterLoad()
{
	return 0;
}

// -------------------------------------------------------------------
int  FetchCursor (EXEC SQL BEGIN DECLARE SECTION;
				  PARAMETER const char * cursorid;
				  EXEC SQL END DECLARE SECTION; ,
				  const char * const msg         )
{
	const char * FUN = "FetchCursor";
	
	EXEC SQL FETCH :cursorid;
	SQL_ERRMSG( msg )

	return SQLCODE;	
}

// -------------------------------------------------------------------
/* use select cursor: so number of transactions can be controlled   */
int Prepare()
{
	const char * FUN = "Prepare";

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;
	
	/* cursor select K1*/
	pStmt =	"select sum_returns from debtlimit "
			"where partnerno = ? "
			"and limittype = '1' "
			"for update;";

	EXEC SQL PREPARE sel_load1 FROM :pStmt;
	SQL_ERRMSG( "prepare sel_load1" );
	exec sql declare CselLoad1 cursor with hold for sel_load1;
	
	/* insert K1*/
	pStmt = "insert into debtlimit ("
			DEBTLIMIT_PELISTE
			") values "
			"(?, ' ', ?, ?, '0', '0', ?, '0', '0', '1', ?, ?, ?);";

	EXEC SQL PREPARE ins_load1 FROM :pStmt;
	SQL_ERRMSG( "prepare ins_load1" );
		
	/* update K1*/
	pStmt =  "update debtlimit "
			 "set "
			 DEBTLIMIT_UPDLISTE
			 " where current of CselLoad1;";

	EXEC SQL PREPARE upd_load1 FROM :pStmt;
	SQL_ERRMSG( "prepare upd_load1" )

	/* delete K1*/
	pStmt =  "delete from debtlimit "
			 " where current of CselLoad1;";

	EXEC SQL PREPARE del_load1 FROM :pStmt;
	SQL_ERRMSG( "prepare del_load1" )

	return OK;
}

// ------------------------------------------------------------------- 
int GetOrderValues(long vz,long maincstno,double *wertauftrag,double *wertdebit,double *wertliste5,double *wertlisteauf5)
{
	const char * const FUN = "GetOrderValues";
	EXEC SQL BEGIN DECLARE SECTION;
	long branchno;
	long lcstno;
	double sumauftrag;
	double sumdebit;
	double sumliste5;
	double sumaufliste5;
	EXEC SQL END DECLARE SECTION;

	branchno = vz;
	lcstno = maincstno;

	sumauftrag = 0.0;
	sumdebit = 0.0;
	sumliste5 = 0.0;
	sumaufliste5 = 0.0;

	EXEC SQL select
			sum(d.sum_debitside),
			sum(d.sum_dayturnover),
			sum(d.sum_liste5),
			sum(d.sum_orderliste5)
			into
			:sumdebit,
			:sumauftrag,
			:sumliste5,
			:sumaufliste5
			from debtlimit d,kunde k
			where k.maincstno = :lcstno
			and d.partnerno = ((k.vertriebszentrumnr*10000000) + k.kundennr)
			and d.limittype = 2;

	SQL_ERRMSG("select summen ")

	if(isnan(sumauftrag)) sumauftrag = 0.0;
	if(isnan(sumdebit)) sumdebit = 0.0;
	if(isnan(sumliste5)) sumliste5 = 0.0;
	if(isnan(sumaufliste5)) sumaufliste5 = 0.0;

	*wertauftrag = sumauftrag;
	*wertdebit = sumdebit;
	*wertliste5 = sumliste5;
	*wertlisteauf5 = sumaufliste5;

	return OK;
}

/***** end of file *****************************************************************/


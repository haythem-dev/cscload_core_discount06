/* ---------------------------------------------------------------------------
 *  loaddeblimit.cxx 
 *     load kreditlimit des Kunden
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loaddebtlimit"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

#include "debtlimit.h"
#include "dkops.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loaddebtlimit"
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
	int ins1;			// new rows
	int upd1;			// updated rows
	int del1;			// deleted rows
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
int  Load                 (struct O_DKOPS * pRecord);
int  GetOrderValues		  (long vz,long customerno,double *wertauftrag,double *wertauftrag5);
int  AfterLoad            ();

int  SetNotUpdated        ();
int  DelNotUpdated        ();
int  FetchCursor		  (const char * cursorid, 
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
	sprintf(msg, "    deletet  K2: %4d", sqlstat.del);
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
			long allowed = sizeof(struct O_DKOPS);
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
	int	rc = 0;

	if ( OK != (rc = DbConnect(database)) )
		return rc;

	if ( OK != (rc = Prepare()) )
	{
		DbDisconnect();
		return rc;	
	}
	
	char line[sizeof(struct O_DKOPS) + 3] = { 0 };	/* possibly CR + LF + '\0' */
	
	DEBUG_SECTION
		char msg[256];
		sprintf(msg, 
				"sizeof(O_DKOPS) = %d, sizeof(line) = %d", 
				sizeof(struct O_DKOPS),
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
			rc = Load((struct O_DKOPS *)line);

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
	pStmt =	"select sum_returns from debtlimit "
			"where partnerno = ? "
			"and limittype = '2' "
			"for update;";

	EXEC SQL PREPARE sel_load FROM :pStmt;
	SQL_ERRMSG( "prepare sel_load" );
	exec sql declare CselLoad cursor with hold for sel_load;
	
	/* cursor select K1*/
	pStmt =	"select sum_returns from debtlimit "
			"where partnerno = ? "
			"and limittype = '1' "
			"for update;";

	EXEC SQL PREPARE sel_load1 FROM :pStmt;
	SQL_ERRMSG( "prepare sel_load1" );
	exec sql declare CselLoad1 cursor with hold for sel_load1;
	
	/* insert */
	pStmt = "insert into debtlimit ("
			DEBTLIMIT_PELISTE
			") values "
			"(?, ' ', ?, ?, '0', '0', ?, '0', '0', '2', '0', ?, ?);";

	EXEC SQL PREPARE ins_load FROM :pStmt;
	SQL_ERRMSG( "prepare ins_load" );
	
	/* insert K1*/
	pStmt = "insert into debtlimit ("
			DEBTLIMIT_PELISTE
			") values "
			"(?, ' ', ?, ?, '0', '0', ?, '0', '0', '1', ?, ?, ?);";

	EXEC SQL PREPARE ins_load1 FROM :pStmt;
	SQL_ERRMSG( "prepare ins_load1" );

	/* update */
	pStmt =  "update debtlimit "
			 "set "
			 DEBTLIMIT_UPDLISTE
			 " where current of CselLoad;";

	EXEC SQL PREPARE upd_load FROM :pStmt;
	SQL_ERRMSG( "prepare upd_load" )
		
	/* update K1*/
	pStmt =  "update debtlimit "
			 "set "
			 DEBTLIMIT_UPDLISTE
			 " where current of CselLoad1;";

	EXEC SQL PREPARE upd_load1 FROM :pStmt;
	SQL_ERRMSG( "prepare upd_load1" )

	/* delete K2*/
	pStmt =  "delete from debtlimit "
			 " where current of CselLoad;";

	EXEC SQL PREPARE del_load FROM :pStmt;
	SQL_ERRMSG( "prepare del_load" )

	/* delete K1*/
	pStmt =  "delete from debtlimit "
			 " where current of CselLoad1;";

	EXEC SQL PREPARE del_load1 FROM :pStmt;
	SQL_ERRMSG( "prepare del_load1" )
		
	return OK;
}

// ------------------------------------------------------------------- 
int Load (struct O_DKOPS * record)
{
	const char * const FUN = "Load";
	char huelse[81];
	long lBranchno;
	long lCustomerno;
	int test;

	// --- check valid branchno
	if ( FALSE == IsValidNumber(record->BRANCHNO, sizeof(record->BRANCHNO)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "BRANCHNO not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- check valid customerno
	if ( FALSE == IsValidNumber(record->IDF, sizeof(record->IDF)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "IDF not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- convert
	EXEC SQL BEGIN DECLARE SECTION;
	struct N_DEBTLIMIT row = { 0 };
	double wertauftrag;
	double wertauftrag5;
	EXEC SQL END DECLARE SECTION;
	
	struct S_DEBTLIMIT buf = { 0 };
	
	sprintf(huelse,"%*.*s",L_DKOPS_KRED,L_DKOPS_KRED,record->KRED);
	row.LIMIT = atof(huelse)/100;
	sprintf(huelse,"%*.*s",L_DKOPS_BETRAG,L_DKOPS_BETRAG,record->BETRAG);
	row.SUM_DEBITSIDE = atof(huelse);
	sprintf(huelse,"%*.*s",L_DKOPS_BETRAGL5,L_DKOPS_BETRAGL5,record->BETRAGL5);
	row.SUM_LISTE5 = atof(huelse);

	sprintf(huelse,"%*.*s",L_DKOPS_BRANCHNO,L_DKOPS_BRANCHNO,record->BRANCHNO);
	lBranchno = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPS_IDF,L_DKOPS_IDF,record->IDF);
	lCustomerno = atol(huelse);

	row.PARTNERNO		= lBranchno*10000000 + lCustomerno;
	
	if(GetOrderValues(lBranchno,lCustomerno,&wertauftrag,&wertauftrag5) != OK)
	{
		wertauftrag = 0.0;
		wertauftrag5 = 0.0;
	}

	EXEC SQL open CselLoad USING :row.PARTNERNO;
	SQL_ERRMSG("open CselLoad")

	EXEC SQL fetch CselLoad into :row.SUM_RETURNS;
	SQL_ERRMSG("fetch CselLoad")
		
	if ( SQLCODE == 100 )
	{
		if(row.LIMIT > 0.0)
		{
			EXEC SQL EXECUTE ins_load using :row.PARTNERNO, 
										:row.LIMIT, 
										:row.SUM_DEBITSIDE,
										:wertauftrag,
										:row.SUM_LISTE5,
										:wertauftrag5;
			if( SQLCODE == -1201)
			{
				test = -1201;
			}
			SQL_ERRMSG("ins_load")
			++sqlstat.ins;	
		}
	}
	else
	{
		if(row.LIMIT > 0.0)
		{
			EXEC SQL EXECUTE upd_load using
				:row.PARTNERNO,
				' ',
				:row.LIMIT, 
				:row.SUM_DEBITSIDE,
				'0',
				'0',
				:wertauftrag,
				'0',
				'0',
				'2',
				'0',
				:row.SUM_LISTE5,
				:wertauftrag5;
			SQL_ERRMSG("upd_load")
			++sqlstat.upd;	
		}
		else
		{
			EXEC SQL EXECUTE del_load;
			SQL_ERRMSG("del_load")
			++sqlstat.del;
		}
	}

/*	K1 laden */

	sprintf(huelse,"%*.*s",L_DKOPS_KREDK1,L_DKOPS_KREDK1,record->KREDK1);
	row.LIMIT = atof(huelse)/100;
	sprintf(huelse,"%*.*s",L_DKOPS_BETRAG,L_DKOPS_BETRAG,record->BETRAG);
	row.SUM_DEBITSIDE = atof(huelse);
	sprintf(huelse,"%*.*s",L_DKOPS_BETRAGL5,L_DKOPS_BETRAGL5,record->BETRAGL5);
	row.SUM_LISTE5 = atof(huelse);
	if(record->LISTE5[0] == 'J' || record->LISTE5[0] == '1')
		row.LISTE5[0] = '1';
	else
		row.LISTE5[0] = '0';
	if(row.LISTE5[0] == '0')
	{
		row.SUM_DEBITSIDE = row.SUM_DEBITSIDE - row.SUM_LISTE5;
		row.SUM_DAYTURNOVER = wertauftrag - wertauftrag5;
	}
	else
	{
		row.SUM_DEBITSIDE = row.SUM_DEBITSIDE;
		row.SUM_DAYTURNOVER = wertauftrag;
	}

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
										:wertauftrag,
										:row.LISTE5,
										:row.SUM_LISTE5,
										:wertauftrag5;
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
				:wertauftrag,
				'0',
				'0',
				'1',
				:row.LISTE5,
				:row.SUM_LISTE5,
				:wertauftrag5;
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
int GetOrderValues(long vz,long customerno,double *wertauftrag,double *wertauftrag5)
{
	const char * const FUN = "GetOrderValues";
	EXEC SQL BEGIN DECLARE SECTION;
	long branchno;
	long lcstno;
	int fs;
	int kk;
	double wertfs;
	double wertkk;
	double wertfs5;
	double wertkk5;
	double gesamt;
	short rkfs;
	short rkkk;
	short isCREMA;
	EXEC SQL END DECLARE SECTION;

	branchno = vz;
	lcstno = customerno;
	wertfs = 0.0;
	wertkk = 0.0;
	wertfs5 = 0.0;
	wertkk5 = 0.0;
	*wertauftrag = wertfs + wertkk;
	*wertauftrag5 = wertfs5 + wertkk5;

	EXEC SQL select count(*)
		into :isCREMA
		from paraauftragbearb 
	    where filialnr = :branchno
		and screma = 1 and sstopcrema = 0;
	SQL_ERRMSG("select paraauftragbearb")
		if (SQLCODE == 100) return OK;

	EXEC SQL select rebatemethfreesale,rebatemethhealthf
		into :rkfs,:rkkk
		from kunde
		where vertriebszentrumnr = :branchno
		and kundennr = :lcstno;
	SQL_ERRMSG("select kunde")
	if(SQLCODE == 100) return OK;

	EXEC SQL select count(*)
		into :fs
		from cstpaymentterms
		where branchno = :branchno
		and customerno = :lcstno
		and preis_typ = 0;
	SQL_ERRMSG("select FV")
	EXEC SQL select count(*)
		into :kk
		from cstpaymentterms
		where branchno = :branchno
		and customerno = :lcstno
		and preis_typ = 1;
	SQL_ERRMSG("select KK")

	if(fs > 0)
	{
		if(!rkfs)
		{
			EXEC SQL select sum(w.ordvalftaxfsdisc + w.ordvalltaxfsdisc)
				into :wertfs
				from kdauftrag k,kdauftragwerte w
				where k.kdauftragart not in ('CO','RO','MP','EH')
			    and k.kdauftragnr not in (select distinct kd.kdauftragnr from kdauftrag kd where kd.kdauftragart = 'FC' and kd.kdauftragstat[13] = '1' and kd.kdauftragstat[4] = '1' and 1 == :isCREMA) /* Ignore FC orders which are not yet manually opened in AE */
				and k.kdauftragstat[9] != '1'	/* Fakturiert */
				and k.kdauftragstat[10] != '1'	/* Storniert */
				and k.paymenttype != 'C'
				and k.vertriebszentrumnr = :branchno
				and k.kundennr = :lcstno
				and k.kdauftragnr = w.kdauftragnr;
			SQL_ERRMSG("select sum FS")
			if(isnan(wertfs)) wertfs = 0.0;
			EXEC SQL select sum(w.ordvalftaxfsdisc + w.ordvalltaxfsdisc)
				into :wertfs5
				from kdauftrag k,kdauftragwerte w
				where k.kdauftragart not in ('CO','RO','MP','EH')
				and k.kdauftragnr not in (select distinct kd.kdauftragnr from kdauftrag kd where kd.kdauftragart = 'FC' and kd.kdauftragstat[13] = '1' and kd.kdauftragstat[4] = '1' and 1 == :isCREMA) /* Ignore FC orders which are not yet manually opened in AE */
				and k.kdauftragstat[9] != '1'	/* Fakturiert */
				and k.kdauftragstat[10] != '1'	/* Storniert */
				and k.paymenttype != 'C'
				and k.vertriebszentrumnr = :branchno
				and k.kundennr = :lcstno
				and k.kdauftragnr = w.kdauftragnr
				and trunc( etauftragschalter1/1)-2 *trunc( etauftragschalter1/(1*2)) != 0;
			SQL_ERRMSG("select sum FS 5")
			if(isnan(wertfs5)) wertfs5 = 0.0;
		}
		else
		{
			EXEC SQL select sum(w.ordvalftaxfs + w.ordvalltaxfs)
				into :wertfs
				from kdauftrag k,kdauftragwerte w
				where k.kdauftragart not in ('CO','RO','MP','EH')
				and k.kdauftragnr not in (select distinct kd.kdauftragnr from kdauftrag kd where kd.kdauftragart = 'FC' and kd.kdauftragstat[13] = '1' and kd.kdauftragstat[4] = '1' and 1 == :isCREMA) /* Ignore FC orders which are not yet manually opened in AE */
				and k.kdauftragstat[9] != '1'	/* Fakturiert */
				and k.kdauftragstat[10] != '1'	/* Storniert */
				and k.paymenttype != 'C'
				and k.vertriebszentrumnr = :branchno
				and k.kundennr = :lcstno
				and k.kdauftragnr = w.kdauftragnr;
			SQL_ERRMSG("select sum FS")
			if(isnan(wertfs)) wertfs = 0.0;
			EXEC SQL select sum(w.ordvalftaxfs + w.ordvalltaxfs)
				into :wertfs5
				from kdauftrag k,kdauftragwerte w
				where k.kdauftragart not in ('CO','RO','MP','EH')
				and k.kdauftragnr not in (select distinct kd.kdauftragnr from kdauftrag kd where kd.kdauftragart = 'FC' and kd.kdauftragstat[13] = '1' and kd.kdauftragstat[4] = '1' and 1 == :isCREMA) /* Ignore FC orders which are not yet manually opened in AE */
				and k.kdauftragstat[9] != '1'	/* Fakturiert */
				and k.kdauftragstat[10] != '1'	/* Storniert */
				and k.paymenttype != 'C'
				and k.vertriebszentrumnr = :branchno
				and k.kundennr = :lcstno
				and k.kdauftragnr = w.kdauftragnr
				and trunc( etauftragschalter1/1)-2 *trunc( etauftragschalter1/(1*2)) != 0;
			SQL_ERRMSG("select sum FS 5")
			if(isnan(wertfs5)) wertfs5 = 0.0;
		}
	}
	if(kk > 0)
	{
		if(!rkkk)
		{
			EXEC SQL select sum(w.ordvalftaxhfdisc + w.ordvalltaxhfdisc)
				into :wertkk
				from kdauftrag k,kdauftragwerte w
				where k.kdauftragart not in ('CO','RO','MP','EH')
				and k.kdauftragnr not in (select distinct kd.kdauftragnr from kdauftrag kd where kd.kdauftragart = 'FC' and kd.kdauftragstat[13] = '1' and kd.kdauftragstat[4] = '1' and 1 == :isCREMA) /* Ignore FC orders which are not yet manually opened in AE */
				and k.kdauftragstat[9] != '1'	/* Fakturiert */
				and k.kdauftragstat[10] != '1'	/* Storniert */
				and k.paymenttype != 'C'
				and k.vertriebszentrumnr = :branchno
				and k.kundennr = :lcstno
				and k.kdauftragnr = w.kdauftragnr;
			SQL_ERRMSG("select sum KK")
			if(isnan(wertkk) || (SQLCODE == 100)) wertkk = 0.0;
			EXEC SQL select sum(w.ordvalftaxhfdisc + w.ordvalltaxhfdisc)
				into :wertkk5
				from kdauftrag k,kdauftragwerte w
				where k.kdauftragart not in ('CO','RO','MP','EH')
				and k.kdauftragnr not in (select distinct kd.kdauftragnr from kdauftrag kd where kd.kdauftragart = 'FC' and kd.kdauftragstat[13] = '1' and kd.kdauftragstat[4] = '1' and 1 == :isCREMA) /* Ignore FC orders which are not yet manually opened in AE */
				and k.kdauftragstat[9] != '1'	/* Fakturiert */
				and k.kdauftragstat[10] != '1'	/* Storniert */
				and k.paymenttype != 'C'
				and k.vertriebszentrumnr = :branchno
				and k.kundennr = :lcstno
				and k.kdauftragnr = w.kdauftragnr
				and trunc( etauftragschalter1/1)-2 *trunc( etauftragschalter1/(1*2)) != 0;
			SQL_ERRMSG("select sum KK 5")
			if(isnan(wertkk5) || (SQLCODE == 100)) wertkk5 = 0.0;
		}
		else
		{
			EXEC SQL select sum(w.ordvalftaxhf + w.ordvalltaxhf)
				into :wertkk
				from kdauftrag k,kdauftragwerte w
				where k.kdauftragart not in ('CO','RO','MP','EH')
				and k.kdauftragnr not in (select distinct kd.kdauftragnr from kdauftrag kd where kd.kdauftragart = 'FC' and kd.kdauftragstat[13] = '1' and kd.kdauftragstat[4] = '1' and 1 == :isCREMA) /* Ignore FC orders which are not yet manually opened in AE */
				and k.kdauftragstat[9] != '1'	/* Fakturiert */
				and k.kdauftragstat[10] != '1'	/* Storniert */
				and k.paymenttype != 'C'
				and k.vertriebszentrumnr = :branchno
				and k.kundennr = :lcstno
				and k.kdauftragnr = w.kdauftragnr;
			SQL_ERRMSG("select sum KK")
			if(isnan(wertkk) || (SQLCODE == 100)) wertkk = 0.0;
			EXEC SQL select sum(w.ordvalftaxhf + w.ordvalltaxhf)
				into :wertkk5
				from kdauftrag k,kdauftragwerte w
				where k.kdauftragart not in ('CO','RO','MP','EH')
				and k.kdauftragnr not in (select distinct kd.kdauftragnr from kdauftrag kd where kd.kdauftragart = 'FC' and kd.kdauftragstat[13] = '1' and kd.kdauftragstat[4] = '1' and 1 == :isCREMA) /* Ignore FC orders which are not yet manually opened in AE */
				and k.kdauftragstat[9] != '1'	/* Fakturiert */
				and k.kdauftragstat[10] != '1'	/* Storniert */
				and k.paymenttype != 'C'
				and k.vertriebszentrumnr = :branchno
				and k.kundennr = :lcstno
				and k.kdauftragnr = w.kdauftragnr
				and trunc( etauftragschalter1/1)-2 *trunc( etauftragschalter1/(1*2)) != 0;
			SQL_ERRMSG("select sum KK 5")
			if(isnan(wertkk5) || (SQLCODE == 100)) wertkk5 = 0.0;
		}
	}
	*wertauftrag = wertfs + wertkk;
	*wertauftrag5 = wertfs5 + wertkk5;

	return OK;
}

// -------------------------------------------------------------------
int AfterLoad()
{
	return OK;
}

/***** end of file *****************************************************************/


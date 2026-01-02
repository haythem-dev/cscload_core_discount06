/* ---------------------------------------------------------------------------
 *  loaddkopo.cxx 
 *     load offene posten liste
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loaddkopo"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

#include "cstpaymentlist.h"
#include "dkopo.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loaddkopo"
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
	int upd_exist;		// update already existing rows
	int del_missing;	// deleted rows because of missing in DKOPO
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
static int				printflag = 0;
static int    			bVersion	 	= FALSE;

EXEC SQL BEGIN DECLARE SECTION;
short branchno;
char updflg[2];
EXEC SQL END DECLARE SECTION;
 
// -------------------------------------------------------------------

int  DbConnect			  (const char * database);
int  DbDisconnect		  ();

int  Start                (FILE * pFile, 
						   const char * const database);
int  Prepare              ();
int  Load                 (struct O_DKOPO * pRecord);
int  AfterLoad            ();

int  SetNotUpdated        ();
int  DelNotUpdated        ();
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
	sprintf(msg, "    updated  : %4d", sqlstat.upd);
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
			long allowed = sizeof(struct O_DKOPO);
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
	
	char line[sizeof(struct O_DKOPO) + 3] = { 0 };	/* possibly CR + LF + '\0' */
	
	DEBUG_SECTION
		char msg[256];
		sprintf(msg, 
				"sizeof(O_DKOPO) = %d, sizeof(line) = %d", 
				sizeof(struct O_DKOPO),
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
			rc = Load((struct O_DKOPO *)line);

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
	pStmt =	"select UPD_FLAG from cstpaymentlist "
			"where BRANCHNO = ? "
			"and CUSTOMERNO = ? "
			"and INVOICENUMBER = ? "
			"and SEQUENCENO = ? "
			"for update;";

	EXEC SQL PREPARE sel_load FROM :pStmt;
	SQL_ERRMSG( "prepare sel_load" );
	exec sql declare CselLoad cursor with hold for sel_load;
	

	/* insert */
	pStmt = "insert into cstpaymentlist ("
		CSTPAYMENTLIST_PELISTE
				") values "
			"(?, ?, ?, ?, ?,"
			" ?, ?, ?, ?, ?,"
			" ?, ?, ?, ?, ?,"
			" ?, ?, ?, ?, ?,"
			" ?, ?, ?, ?, ?,"
			" ?, ?, ?, ?, ?,"
			" ?, ?, ?, ?, ?,"
			" ?, ?, ?, ?, ?,"
			" ?, ?, ?, ?, ?,"
			" ?, ?, ?, ? );";

	EXEC SQL PREPARE ins_load FROM :pStmt;
	SQL_ERRMSG( "prepare ins_load" );
	

	/* update */
	pStmt =  "update cstpaymentlist "
			 "set "
			 CSTPAYMENTLIST_UPDLISTE
			 "where current of CselLoad;";

	EXEC SQL PREPARE upd_load FROM :pStmt;
	SQL_ERRMSG( "prepare upd_load" )
		

	/* cursor select */
	pStmt =	"select DRIVERID from akdauftrag "
			"where DATUM = ? "
			"and INVOICENUMBER = ? "
			"for update;";

	EXEC SQL PREPARE sel_auft FROM :pStmt;
	SQL_ERRMSG( "prepare sel_auft" );
	exec sql declare CselAuft cursor with hold for sel_auft;

	/* update */
	pStmt =  "update akdauftrag "
			 "set "
			 "DRIVERID = ? "
			 "where current of CselAuft;";

	EXEC SQL PREPARE upd_auft FROM :pStmt;
	SQL_ERRMSG( "prepare upd_auft" )
		

	return SetNotUpdated();
}

// ------------------------------------------------------------------- 
int Load (struct O_DKOPO * record)
{
	const char * const FUN = "Load";
	char huelse[81];
	double wert;
	long lTarget;

	// --- check valid branchno
	if ( FALSE == IsValidNumber(record->OPOFIL, sizeof(record->OPOFIL)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "OPOFIL not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- check valid customerno
	if ( FALSE == IsValidNumber(record->OPOKDNR, sizeof(record->OPOKDNR)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "OPOKDNR not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}


	// --- convert
	EXEC SQL BEGIN DECLARE SECTION;
	cstpaymentlistS row = { 0 };
	long lDriver;
	char cupdflag[2];
	EXEC SQL END DECLARE SECTION;
	
	sprintf(huelse,"%*.*s",L_DKOPO_OPOFIL,L_DKOPO_OPOFIL,record->OPOFIL);
	row.BRANCHNO   = atoi(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOKDNR,L_DKOPO_OPOKDNR,record->OPOKDNR);
	row.CUSTOMERNO = atol(huelse);
	sprintf(row.INVOICENUMBER,"%*.*s",L_DKOPO_OPORECHNR,L_DKOPO_OPORECHNR,record->OPORECHNR);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOLFD_NR,L_DKOPO_OPOLFD_NR,record->OPOLFD_NR);
	row.SEQUENCENO  = atoi(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOSTATUS,L_DKOPO_OPOSTATUS,record->OPOSTATUS);
	row.INVOICESTATE  = atoi(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOZEIT,L_DKOPO_OPOZEIT,record->OPOZEIT);
	row.STATETIME = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOGESBETR,L_DKOPO_OPOGESBETR,record->OPOGESBETR);
	wert    = atof(huelse);
	row.TOTALINVOICEAMOUNT    = (double)(wert/100);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOOFFBETR,L_DKOPO_OPOOFFBETR,record->OPOOFFBETR);
	wert    = atof(huelse);
	row.OPENINVOICEAMOUNT    = (double)(wert/100);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOBEZBETR,L_DKOPO_OPOBEZBETR,record->OPOBEZBETR);
	wert    = atof(huelse);
	row.PAIDINVOICEAMOUNT    = (double)(wert/100);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOKURIDF,L_DKOPO_OPOKURIDF,record->OPOKURIDF);
	row.DRIVERID = atol(huelse);
	sprintf(row.KINDOFPAYMENT,"%*.*s",L_DKOPO_OPOZART,L_DKOPO_OPOZART,record->OPOZART);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOFAELLIGKEIT,L_DKOPO_OPOFAELLIGKEIT,record->OPOFAELLIGKEIT);
	row.PAYMENTDATE = atol(huelse);
	sprintf(row.DOCUMENTDESCRIPT,"%*.*s",L_DKOPO_OPODOKUART,L_DKOPO_OPODOKUART,record->OPODOKUART);
	sprintf(row.USERIDENT,"%*.*s",L_DKOPO_OPOPERSID,L_DKOPO_OPOPERSID,record->OPOPERSID);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOREDAT,L_DKOPO_OPOREDAT,record->OPOREDAT);
	row.INVOICEDATE = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOTDATE,L_DKOPO_OPOTDATE,record->OPOTDATE);
	row.TOURDATE = atol(huelse) + 20000000; // JJMMTT ergänzen mit Jahrhundert
	sprintf(row.TOURID,"%*.*s",L_DKOPO_OPOTOUR,L_DKOPO_OPOTOUR,record->OPOTOUR);
	sprintf(row.CREDITNUMBER,"%*.*s",L_DKOPO_OPOGUTSNR,L_DKOPO_OPOGUTSNR,record->OPOGUTSNR);
	sprintf(row.PAYMENTSPEC,"%*.*s",L_DKOPO_OPOZZIEL,L_DKOPO_OPOZZIEL,record->OPOZZIEL);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOTGZIEL,L_DKOPO_OPOTGZIEL,record->OPOTGZIEL);
	row.DAYSOFPAYMENT  = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOZEDAT,L_DKOPO_OPOZEDAT,record->OPOZEDAT);
	row.PAYMENTRECEIPT = atol(huelse);
	sprintf(row.DOCTYPE,"%*.*s",L_DKOPO_OPOBTYP,L_DKOPO_OPOBTYP,record->OPOBTYP);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOUELNR,L_DKOPO_OPOUELNR,record->OPOUELNR);
	row.OVERFLOWNO = atoi(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOBELNR,L_DKOPO_OPOBELNR,record->OPOBELNR);
	row.DOCNO = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOLFDNR,L_DKOPO_OPOLFDNR,record->OPOLFDNR);
	row.SEQUENCE = atoi(huelse);
	sprintf(row.SENDTOSAP,"%*.*s",L_DKOPO_OPOFISAP,L_DKOPO_OPOFISAP,record->OPOFISAP);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOFIDAT,L_DKOPO_OPOFIDAT,record->OPOFIDAT);
	row.SAPDATE = atol(huelse) + 20000000; // JJMMTT ergänzen mit Jahrhundert
	sprintf(huelse,"%*.*s",L_DKOPO_OPOKANR,L_DKOPO_OPOKANR,record->OPOKANR);
	row.CSTORDERNO = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOBELDR,L_DKOPO_OPOBELDR,record->OPOBELDR);
	row.PAYMENTDOCNO = atoi(huelse);
	sprintf(row.DISCOUNTFLAG,"%*.*s",L_DKOPO_OPOSKOKZ,L_DKOPO_OPOSKOKZ,record->OPOSKOKZ);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOSKOBETR,L_DKOPO_OPOSKOBETR,record->OPOSKOBETR);
	wert    = atof(huelse);
	row.DISCOUNTAMOUNT    = (double)(wert/100);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOVERTEILER,L_DKOPO_OPOVERTEILER,record->OPOVERTEILER);
	row.DISTRIBUTORNO = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOVTZEIT,L_DKOPO_OPOVTZEIT,record->OPOVTZEIT);
	row.DISTRIBSCANTIME = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOKURZEIT,L_DKOPO_OPOKURZEIT,record->OPOKURZEIT);
	row.DRIVERLISTTIME = atol(huelse);
	sprintf(row.INVOICECOMPSAP,"%*.*s",L_DKOPO_OPOREAUSGL,L_DKOPO_OPOREAUSGL,record->OPOREAUSGL);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOABRTYP,L_DKOPO_OPOABRTYP,record->OPOABRTYP);
	row.PRICETYPE = atoi(huelse);
	sprintf(row.COMPLAINTSCANFLAG,"%*.*s",L_DKOPO_OPOREKSCAN,L_DKOPO_OPOREKSCAN,record->OPOREKSCAN);
	sprintf(row.LIBRADATEFLAG,"%*.*s",L_DKOPO_OPOVLKZ,L_DKOPO_OPOVLKZ,record->OPOVLKZ);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOANZKART,L_DKOPO_OPOANZKART,record->OPOANZKART);
	row.QTYCARTON = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOANZPAK,L_DKOPO_OPOANZPAK,record->OPOANZPAK);
	row.QTYPACKET = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOANZTUE,L_DKOPO_OPOANZTUE,record->OPOANZTUE);
	row.QTYBAG = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOANZBEIP,L_DKOPO_OPOANZBEIP,record->OPOANZBEIP);
	row.QTYENCLOSEDLABEL = atol(huelse);
	sprintf(row.KINDOFORDER,"%*.*s",L_DKOPO_OPOAART,L_DKOPO_OPOAART,record->OPOAART);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOENDKONTR,L_DKOPO_OPOENDKONTR,record->OPOENDKONTR);
	row.FINALCHECKUSERNO = atol(huelse);
	sprintf(huelse,"%*.*s",L_DKOPO_OPOEKZEIT,L_DKOPO_OPOEKZEIT,record->OPOEKZEIT);
	row.FINALCHECKTIME = atol(huelse);
	sprintf(row.CUSTOMERGRP,"%*.*s",L_DKOPO_OPOKGR,L_DKOPO_OPOKGR,record->OPOKGR);
	sprintf(row.NARCOTICFLAG,"%*.*s",L_DKOPO_OPOBTM,L_DKOPO_OPOBTM,record->OPOBTM);
	sprintf(row.INVOICEREBATEFLAG,"%*.*s",L_DKOPO_OPORRABAT,L_DKOPO_OPORRABAT,record->OPORRABAT);
	row.UPD_FLAG[0] = '1';

	// --- update/insert row

	EXEC SQL open CselLoad USING	:row.BRANCHNO,
									:row.CUSTOMERNO,
									:row.INVOICENUMBER,
									:row.SEQUENCENO;
	SQL_ERRMSG("open CselLoad")

	EXEC SQL fetch CselLoad into :cupdflag;
	SQL_ERRMSG("fetch CselLoad")
		
	if ( SQLCODE == 100 )
	{
		EXEC SQL EXECUTE ins_load using :row; 
		SQL_ERRMSG("ins_load")

		++sqlstat.ins;	
	}
	else
	{
		EXEC SQL EXECUTE upd_load using :row;
		SQL_ERRMSG("upd_load")

		++sqlstat.upd;	
	}
	if(row.DRIVERID > 0)
	{
		EXEC SQL open CselAuft USING	:row.INVOICEDATE,
										:row.INVOICENUMBER;
		SQL_ERRMSG("open CselAuft")

		EXEC SQL fetch CselAuft into :lDriver;
		SQL_ERRMSG("fetch CselAuft")
		if ( SQLCODE != 100 )
		{
			if(lDriver == 0)
			{
				EXEC SQL EXECUTE upd_auft using :row.DRIVERID;
				SQL_ERRMSG("upd_auft")
			}
		}
	}

	return OK;
}

// -------------------------------------------------------------------
int AfterLoad()
{
	return DelNotUpdated();
}

// -------------------------------------------------------------------
int  FetchCursor (EXEC SQL BEGIN DECLARE SECTION;
				  PARAMETER const char * cursorid,
				  EXEC SQL END DECLARE SECTION;
				  const char * const msg         )
{
	const char * const FUN = "FetchCursor";
	
	EXEC SQL FETCH :cursorid into :updflg;
	SQL_ERRMSG( msg )
	DEBUG_SECTION
		if(printflag == 1)
		{
			printflag = 0;
			char msg[256];
			sprintf(msg, "SetNotUpd fetch returned: %d",SQLCODE);	
			LogMsg(FUN, msg, FL_INFO);
		}
	END_DEBUG_SECTION

	return SQLCODE;	
}

// -------------------------------------------------------------------
/* use select cursor: so number of transactions can be controlled   */
int SetNotUpdated()
{
	#define SETCURSORID		"CursorSetNotUpdated"
	
	const char * const FUN = "SetNotUpdated";

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	const char * pCursorId = SETCURSORID;
	EXEC SQL END DECLARE SECTION;
	
	pStmt =	"select upd_flag from cstpaymentlist where upd_flag != '0' and branchno = ? for update;";

	EXEC SQL PREPARE sel_SetNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare sel_SetNotUp" )
	EXEC SQL DECLARE :pCursorId CURSOR WITH HOLD FOR sel_SetNotUp;
	
	
	pStmt = "update cstpaymentlist set upd_flag = '0' where current of " SETCURSORID ";";
	
	EXEC SQL PREPARE upd_SetNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare SetNotUp" )

    EXEC SQL BEGIN WORK;
	SQL_ERRMSG( "begin work" )
		
	EXEC SQL OPEN :pCursorId using :branchno;
    SQL_ERRMSG( "open SetNotUp" )

	DEBUG_SECTION
		char msg[256];
		sprintf(msg, "SetNotUpd opened");	
		LogMsg(FUN, msg, FL_INFO);
	END_DEBUG_SECTION

	printflag = 1;

	while ( OK == FetchCursor(pCursorId, "fetch SetNotUp") )
	{
		DEBUG_SECTION
			if(sqlstat.upd_exist == 0)
			{
				char msg[256];
				sprintf(msg, "SetNotUpd fetch");	
				LogMsg(FUN, msg, FL_INFO);
			}
		END_DEBUG_SECTION

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
int DelNotUpdated()
{
	#define DELCURSORID		"CursorDelNotUpdated"
	
	const char * const FUN = "DelNotUpdated";

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	const char * pCursorId = DELCURSORID; 
	EXEC SQL END DECLARE SECTION;


	pStmt = "select 1 from cstpaymentlist where upd_flag != '1' and branchno = ? for update";

	EXEC SQL PREPARE sel_DelNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare sel_DelNotUp" )
	EXEC SQL DECLARE :pCursorId CURSOR WITH HOLD FOR sel_DelNotUp;
	

	pStmt = "delete from cstpaymentlist "
			"where current of " DELCURSORID ";";
	
	EXEC SQL PREPARE del_DelNotUp FROM :pStmt;
	SQL_ERRMSG( "prepare del_DelNotUp" )
		
    EXEC SQL BEGIN WORK;
	SQL_ERRMSG( "begin work" )
		
	EXEC SQL OPEN :pCursorId using :branchno;
    SQL_ERRMSG( "open DelNotUp" )

	DEBUG_SECTION
		char msg[256];
		sprintf(msg, "DelNotUpd opened");	
		LogMsg(FUN, msg, FL_INFO);
	END_DEBUG_SECTION

	printflag = 1;

	while ( OK == FetchCursor(pCursorId, "fetch DelNotUp") )
	{
		DEBUG_SECTION
			if(sqlstat.del_missing == 0)
			{
				char msg[256];
				sprintf(msg, "DelNotUpd fetch");	
				LogMsg(FUN, msg, FL_INFO);
			}
		END_DEBUG_SECTION

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

// -------------------------------------------------------------------
/* Errechnen Tage Zahlungsziel   */
short GetDiffDays(long ZielDate, long RechDate)
{
	long DatZiel;
	struct tm ttZiel, *tZiel;
	tZiel = &ttZiel;
	long DatRech;
	struct tm ttRech, *tRech;
	tRech = &ttRech;

	tZiel->tm_year  = (int) ((ZielDate  / 10000L) - 1900L);
	tZiel->tm_mon   = (int) (((ZielDate / 100L) % 100L) - 1L);
	tZiel->tm_mday  = (int) (ZielDate % 100L);
	tZiel->tm_hour  = 0;
	tZiel->tm_min   = 0;
	tZiel->tm_sec   = 0;
	tZiel->tm_isdst = -1;
	if ((DatZiel = mktime(tZiel)) == -1)
	{
		return 0;
	}
	tRech->tm_year  = (int) ((RechDate  / 10000L) - 1900L);
	tRech->tm_mon   = (int) (((RechDate / 100L) % 100L) - 1L);
	tRech->tm_mday  = (int) (RechDate % 100L);
	tRech->tm_hour  = 0;
	tRech->tm_min   = 0;
	tRech->tm_sec   = 0;
	tRech->tm_isdst = -1;
	if ((DatRech = mktime(tRech)) == -1)
	{
		return 0;
	}
	DatZiel -= DatRech;
	return (DatZiel / (24L * 60L * 60L));
}

/***** end of file *****************************************************************/


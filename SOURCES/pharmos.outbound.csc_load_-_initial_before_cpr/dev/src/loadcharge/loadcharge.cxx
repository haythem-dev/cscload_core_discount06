/* ---------------------------------------------------------------------------
 *  loadcharge.cxx    
 *     load Chargen
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadcharge"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "callplanmaintenance.h"
#include "libtpld/dadedb.h"

#include "articlecharge.h"
#include "dscha.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loadcharge"
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


//statecharge
#define STATE_INWORK		'1'		//nicht Bestandswirksam
#define STATE_AKTIV			'2'
#define STATE_PACKAGEINSERT	'3'
#define STATE_SOLD			'4'
#define STATE_BATCHRECALL	'5'
#define STATE_TENDER		'7'	
#define STATE_CERTIFICAT	'8'
#define STATE_PLUSSTOCK		'9'
#define STATE_FMD			'F'
#define STATE_AUTOMAT		'S'

//Reservierungstyp:
#define RESERV_EKG				2	//nicht abverkaufswirksame einkaufsgruppenbezogene Bestandreservierung
#define RESERV_CERTIFICAT		3	//Artikelreservierung aufgrund fehlenden Zertifikats
#define RESERV_PACKAGEINSERT	4	//kein Beipackzettel
#define RESERV_BATCHRECALL		5	//Chargen Rueckruf
#define RESERV_6				6	//Reservierung aufgrund Bestandsabfrage aus articlereservation
#define RESERV_7				7	//Reservierung fuer Nachlieferung aus artikellokal
#define RESERV_8				8	//Reservierung fuer Nachlieferung aus articlereservation
#define RESERV_9				9	//Reservierung fuer Verbundlieferung aus artikellokal
#define RESERV_10				10	//Reservierung fuer Verbundlieferung aus articlereservation
#define RESERV_11				11	//Reservierung fuer offenen Auftrag aus artikellokal
#define RESERV_12				12	//Reservierung fuer offenen Auftrag aus articlereservation
#define RESERV_TENDER			13	//Reservierung für Tender
#define RESERV_AUTOMAT			14	//Reservierung für defekten Automat
#define RESERV_FMD				15	//Reservierung FMD

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
static int    			prewhole = FALSE;
static long datum = 0;
long vergartnr = 0;
static int bVersion = 0;
mcallplanloadS srvLoad;
tError stError;

EXEC SQL BEGIN DECLARE SECTION;
short sBranchNo;
char database[81];
EXEC SQL END DECLARE SECTION;
 
// -------------------------------------------------------------------

int  DbConnect					();
int  DbDisconnect				();

void WriteLogInfo				( char *error_msg, char mld, int rc );

int  Start						(FILE * pFile); 
int  Prepare					();
int  PrepareReservation			();
int  Load						(struct O_DSCHA * pRecord);
int  LoadReservation			(short sReservationType, struct N_ARTICLECHARGE *row);
int  AfterLoad					();
int  Delete						();
int  DeleteReservations			();


int  CheckLine					(const char * const line, int len);
int  IsValidString				(const char * const str , int len);
int  IsValidNumber				(const char * const str , int len);
 
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

/***** WriteLogInfo nur zum Aufruf von LogMsg ******************************/

void WriteLogInfo( char *error_msg, char mld, int rc )
{
	LogMsg( "callplanday", error_msg, mld );
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
			bVersion = 1;
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
		 (0     == sBranchNo)			||
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

	if(sBranchNo == 16 || sBranchNo == 83 || sBranchNo == 43 || sBranchNo == 48) prewhole = TRUE;	//in Prewhole keine Reservierungssynchronisierung
	
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
	LogMsg( FUN, 
			"----------------------------------------------------------------", 
			FL_INFO);

   	return rc;
 }

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
			struct O_DSCHA * pDummy = (struct O_DSCHA *)line;
			
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
int Start(FILE * pFile)
{
	const char * const FUN = "Start";
	int    		 	   rc;

	if ( OK != (rc = DbConnect()) )
		return rc;

	if( datum == 0 )
	{
		srvLoad.VERTRIEBSZENTRUMNR = sBranchNo;
		srvLoad.LADEDATUM = 0;
		srvLoad.LADEKIPPZEIT = 120000;
		if ( Mcallplanload_GetInitializeData( &srvLoad, &stError, FALSE ) == IS_ERROR )
		{
			if (SQLCODE == -206)	//wenn keine Feiertagstabelle vorhanden ist (inbound) dann aktuelles Datum
			{
				srvLoad.LADEDATUM = ppGGetDate();
			}
			else
			{
				return CheckSql(FUN, &stError, "%s", stError.spError);
			}
		}
		datum = srvLoad.LADEDATUM;
	}

	/* Tag entfernen, da im Pharmos nur Monat und Jahr */
	datum = (datum/100) * 100;

	if ( OK != (rc = Delete()) )
	{
		DbDisconnect();
		return rc;	
	}

	if (!prewhole)
	{
		if (OK != (rc = DeleteReservations()))
		{
			DbDisconnect();
			return rc;
		}
	}

	if ( OK != (rc = Prepare()) )
	{
		DbDisconnect();
		return rc;	
	}

	if (OK != (rc = PrepareReservation()))
	{
		DbDisconnect();
		return rc;
	}

	char line[sizeof(struct O_DSCHA) + 3] = { 0 };	/* possibly CR + LF + '\0' */
	
	DEBUG_SECTION
		char msg[256];
		sprintf(msg, 
				"sizeof(O_DSCHA) = %d, sizeof(line) = %d", 
				sizeof(struct O_DSCHA),
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
			rc = Load((struct O_DSCHA *)line);

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
	int rc;

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;

	/* cursor select */
	pStmt =	"select stock from articlecharge "
			"where BRANCHNO = ? and ARTICLENO = ? "
			  "and CHARGENNR = ? "
			  "and STATECHARGE = ? "
			"for update;";

	EXEC SQL PREPARE sel_load FROM :pStmt;
	SQL_ERRMSG( "prepare sel_load" );
	exec sql declare CselLoad cursor with hold for sel_load;
	

	/* insert */
	pStmt = "insert into articlecharge ("
			"BRANCHNO,"
			"ARTICLENO,"
			"EXPIRYDATE,"
			"CHARGENNR,"
			"STOCK,"
			"STATECHARGE"
			" ) values "
			"(?, ?, ?,"
			" ?, ?,"
			" ? );";

	EXEC SQL PREPARE ins_load FROM :pStmt;
	SQL_ERRMSG( "prepare ins_load" );
	

	/* update */
	pStmt =  "update articlecharge set "
			 "EXPIRYDATE = ?, "
			 "STOCK = ?, "
			 "STATECHARGE = ? "
			 "where current of CselLoad;";

	EXEC SQL PREPARE upd_load FROM :pStmt;
	SQL_ERRMSG( "prepare upd_load" )

	return OK;
}

//Ronnie
int  PrepareReservation()
{
	const char * const FUN = "PrepareReservation";
	int rc;

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;

	/* cursor select */
	pStmt = "select pharmacygroupid from articlereservation "
		"where BRANCHNO = ? "
		"and ARTICLENO = ? "
		"and RESERVTYPE = ? "
		"for update;";

	EXEC SQL PREPARE sel_Reservation FROM : pStmt;
	SQL_ERRMSG("prepare sel_Reservation");
	exec sql declare CselReservation cursor with hold for sel_Reservation;


	/* insert */
	pStmt = "insert into articlereservation ("
		"BRANCHNO,"
		"PHARMACYGROUPID,"
		"ARTICLENO,"
		"RESERVTYPE,"
		"MAXQTY,"
		"RESERVEDQTY,"
		"RESERVEPCT"
		" ) values "
		"(?, ?, ?,"
		" ?, ?,"
		" ?, ? );";

	EXEC SQL PREPARE ins_Reservation FROM : pStmt;
	SQL_ERRMSG("prepare ins_ReserveCertificate");


	/* update */
	pStmt = "update articlereservation set "
		"RESERVEDQTY = RESERVEDQTY + ? "
		"where current of CselReservation;";

	EXEC SQL PREPARE upd_Reservation FROM : pStmt;
	SQL_ERRMSG("prepare upd_Reservation")


		/* delete */
		pStmt = "delete from articlereservation "
		"where current of CselReserveCertificate;";

	EXEC SQL PREPARE del_Reservation FROM : pStmt;
	SQL_ERRMSG("prepare Reservation")

		return OK;
}


// ------------------------------------------------------------------- 
int Load (struct O_DSCHA * record)
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
	if ( FALSE == IsValidNumber(record->ARTICLENO, sizeof(record->ARTICLENO)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "ARTICLENO not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}

	// --- check valid dateinvoice
	if ( FALSE == IsValidNumber(record->EXPIRYDATE, sizeof(record->EXPIRYDATE)) )
	{
		DEBUG_SECTION
			LogMsg(FUN, "EXPIRYDATE not valid", FL_WARN);
		END_DEBUG_SECTION
			
		return WARNING;	// skip record
	}


	// --- convert
	EXEC SQL BEGIN DECLARE SECTION;
	struct N_ARTICLECHARGE row = { 0 };
	long bestand;
	EXEC SQL END DECLARE SECTION;
	
	struct S_ARTICLECHARGE buf = { 0 };

	strncpy(buf.BRANCHNO  	 , record->BRANCHNO  	, sizeof(record->BRANCHNO  	));
	strncpy(buf.ARTICLENO    , record->ARTICLENO    , sizeof(record->ARTICLENO	));
	strncpy(buf.EXPIRYDATE	 , record->EXPIRYDATE	, sizeof(record->EXPIRYDATE	));
	strncpy(buf.STOCK		 , record->STOCK		, sizeof(record->STOCK	    ));
	strncpy(buf.STATECHARGE	 , record->STATECHARGE	, sizeof(record->STATECHARGE));
	
	strncpy(row.CHARGENNR	 , record->CHARGENNR	, sizeof(record->CHARGENNR	));
	row.BRANCHNO   		= atoi(buf.BRANCHNO  	);
	row.ARTICLENO		= atol(buf.ARTICLENO	);
	row.EXPIRYDATE		= atol(buf.EXPIRYDATE   );
	row.STOCK			= atol(buf.STOCK		);
	row.STATECHARGE[0]	= buf.STATECHARGE[0]	 ;

	if (buf.STATECHARGE[0] == STATE_INWORK) return OK;	//status 1 nicht laden SR-19113183

	if(datum > row.EXPIRYDATE)
	{
		char msg[256];
		sprintf(msg, "Charge abgelaufen Artikel: %d Datum: %02d.%02d.%04d"
			, row.ARTICLENO
			, (row.EXPIRYDATE%100)
			, (row.EXPIRYDATE/100%100)
			, (row.EXPIRYDATE/10000) );
		LogMsg(FUN, msg, FL_INFO);
//		return WARNING;	// skip record
	}

	// --- update/insert row
	EXEC SQL open CselLoad USING :row.BRANCHNO, 
		 						 :row.ARTICLENO, 
								 :row.CHARGENNR,
								 :row.STATECHARGE;
	SQL_ERRMSG("open CselLoad")

	EXEC SQL fetch CselLoad into :bestand;
	SQL_ERRMSG("fetch CselLoad")
		
	int fl_upd;						// update or insert?

	if ( SQLCODE == 100 )
	{
		fl_upd = FALSE;
		
		EXEC SQL EXECUTE ins_load using :row.BRANCHNO,
			 							:row.ARTICLENO, 
										:row.EXPIRYDATE,
										:row.CHARGENNR, 
										:row.STOCK, 
										:row.STATECHARGE;
		SQL_ERRMSG("ins_load")

		++sqlstat.ins;	
	}
	else
	{
		fl_upd = TRUE;
		bestand += row.STOCK;

		EXEC SQL EXECUTE upd_load using :row.EXPIRYDATE, 
										:bestand, 
										:row.STATECHARGE;
		SQL_ERRMSG("upd_load")

		++sqlstat.upd;	
	}

	//Ronnie
	if (!prewhole)
	{
		if (row.STATECHARGE[0] == STATE_CERTIFICAT)
		{
			return LoadReservation(RESERV_CERTIFICAT, &row);
		}

		else if (row.STATECHARGE[0] == STATE_PACKAGEINSERT)
		{
			return LoadReservation(RESERV_PACKAGEINSERT, &row);
		}

		else if (row.STATECHARGE[0] == STATE_BATCHRECALL)
		{
			return LoadReservation(RESERV_BATCHRECALL, &row);
		}

		else if (row.STATECHARGE[0] == STATE_FMD)
		{
			return LoadReservation(RESERV_FMD, &row);
		}

		else if (row.STATECHARGE[0] == STATE_AUTOMAT)
		{
			return LoadReservation(RESERV_AUTOMAT, &row);
		}

		else if (row.STATECHARGE[0] == STATE_TENDER)
		{
			return LoadReservation(RESERV_TENDER, &row);
		}
	}

	
	return OK;
}

// -------------------------------------------------------------------
int AfterLoad()
{
	return OK;
}

// -------------------------------------------------------------------
int Delete()
{
	const char * const FUN = "Delete";
	int rc;

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;

	/* cursor select */
	pStmt =	"select 1 from articlecharge "
			"where BRANCHNO = ?"
			"for update;";

	EXEC SQL PREPARE sel_notupd FROM :pStmt;
	SQL_ERRMSG( "prepare sel_notupd" );
	exec sql declare CDelNotupd cursor with hold for sel_notupd;

	/* delete */
	pStmt =  "delete from articlecharge "
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
}

//Ronnie
// -------------------------------------------------------------------
int DeleteReservations()
{
	const char * const FUN = "Delete";
	int rc;

	EXEC SQL BEGIN DECLARE SECTION;
	const char * pStmt;
	EXEC SQL END DECLARE SECTION;

	/* cursor select */
	pStmt = "select 1 from articlereservation "
		"where BRANCHNO = ? "
		"and RESERVTYPE in (3,4,5,13,14,15) "
		"for update;";

	EXEC SQL PREPARE sel_reserve FROM :pStmt;
	SQL_ERRMSG("prepare sel_reserve");
	exec sql declare CDelReserve cursor with hold for sel_reserve;

	/* delete */
	pStmt = "delete from articlereservation "
		"where current of CDelReserve;";

	EXEC SQL PREPARE del_reserve FROM :pStmt;
	SQL_ERRMSG("prepare del_reserve")

	EXEC SQL open CDelReserve USING :sBranchNo;

	EXEC SQL begin work;
	SQL_ERRMSG("begin work start DeleteReservations")

	for (int i = 1;; i++)
	{
		if (filestat.proc % TRANSACTLOOP == 0)
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work between DeleteReservations")

			EXEC SQL begin work;
			SQL_ERRMSG("begin work between DeleteReservations")
		}
		EXEC SQL fetch CDelReserve;
		SQL_ERRMSG("fetch CDelReserve")

		if (SQLCODE == 100)
			break;

		EXEC SQL EXECUTE del_reserve;
		SQL_ERRMSG("del_reserve")
	}
	EXEC SQL commit work;
	SQL_ERRMSG("commit work ende DeleteReservations")

	return OK;
}

int LoadReservation(short sReservationType, struct N_ARTICLECHARGE *row)
{
	const char * const FUN = "LoadReservation";

	EXEC SQL BEGIN DECLARE SECTION;
	struct N_ARTICLECHARGE *pCharge;
	char pharmacygroupid[4];
	char pharmGroup[4] = "299";
	short sType;
	EXEC SQL END DECLARE SECTION;

	pCharge = row;
	sType = sReservationType;

	EXEC SQL open CselReservation USING :pCharge->BRANCHNO, :pCharge->ARTICLENO, :sType;
	SQL_ERRMSG("open CselReservation")

	EXEC SQL fetch CselReservation into :pharmacygroupid;
	SQL_ERRMSG("fetch CselReservation")

	if (SQLCODE != 100)
	{
		EXEC SQL EXECUTE upd_Reservation using
				:pCharge->STOCK
				;
		SQL_ERRMSG("upd_Reservation")
	}
	else
	{
		EXEC SQL EXECUTE ins_Reservation using
				:pCharge->BRANCHNO,
				:pharmGroup,
				:pCharge->ARTICLENO,
				:sType,
				'0',
				:pCharge->STOCK,
				'0.0'
				;
		SQL_ERRMSG("ins_Reservation")
	}

	return OK;
}


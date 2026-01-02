/* ---------------------------------------------------------------------------
 *  loadcstdiscacc.cxx
 *     load customer discount accounts
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadcstdiscacc"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

#include "cstdiscacc.h"
#include "dkrks.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION                "loadcstdiscacc"
#define LOGFILE                    APPLICATION

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

#define TRANSACTLOOP    1000

// -------------------------------------------------------------------

struct SqlStat
{
        int ins;                        // new rows
        int upd;                        // updated rows
        int upd_exist;          // update already existing rows
        int del_missing;        // deleted rows because of missing in DKRKS
};

struct FileStat
{
        int read;                       // lines read
        int proc;                       // lines processed
        int skip;                       // lines skipped
};

static struct SqlStat   sqlstat                 = { 0 };
static struct FileStat  filestat                = { 0 };
static char                     logfile [256]   = { 0 };
static int                      debug_enabled   = FALSE;
static int		    			bVersion	 	= FALSE;

// -------------------------------------------------------------------

int  DbConnect                    (const char * database);
int  DbDisconnect                 ();

int  Start                (FILE * pFile,
                           const char * const database,
						   long branchno);
int  Prepare              (long branchno);
int  Load                 (struct O_DKRKS * pRecord,
		                   long branchno);
int  AfterLoad            (long branchno);

int  SetNotUpdated        (long branchno);
int  DelNotUpdated        (long branchno);
int  FetchCursor                  (const char * cursorid,
                                                   const char * const msg     );

int  CheckLine                    (const char * const line, int len);
int  IsValidString                (const char * const str , int len);
int  IsValidNumber        (const char * const str , int len);
short  GetDiffDays        (long ZielDate, long RechDate);

// -------------------------------------------------------------------
static void LogMsg( const char * const FUN, const char * const msg, char flag)
{
        FILE *          fp       = fopen(logfile, "a");
        long            secs = time     (NULL);
        struct tm *     dt   = localtime(&secs);

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
        sprintf(msg, "    deleted  : %4d (missing in load file)" , sqlstat.del_missing);
        LogMsg( FUN, msg, FL_INFO);
        sprintf(msg, "    marked   : %4d (already existing rows)" , sqlstat.upd_exist);
        LogMsg( FUN, msg, FL_INFO);
}

// -------------------------------------------------------------------
static void SetLogging(long branchno)
{
        const char *  const FUN             = "SetLogging";
        char *              envLogpath      = NULL;
        char                logpath [256]   = { 0 };

        if ((envLogpath = getenv("LOG_PATH")) == (char *)0)
                strcpy(logpath, ".");
        else
                strcpy(logpath, envLogpath);

        sprintf(logfile, "%s/%s.%ld.log", 
				logpath, 
				LOGFILE,
				branchno);

        DEBUG_SECTION
                char msg[256];
                sprintf(msg, "logfile: %s", logfile);
                LogMsg(FUN, msg, FL_INFO);
        END_DEBUG_SECTION
}

// -------------------------------------------------------------------
static int getCmdLine( char * const loadpath,
		               char * const database,
					   long * const pBranchno,
					   int          argc    ,
					   char * const argv[]  )
{
        const char *  const FUN = "getCmdLine";
        int                     rc  = OK;

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
						*pBranchno = atol(argv[i]);
					
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

        if ( (1     == argc)                    ||
                 (ERROR == rc)                  ||
                 (0     == strlen(database))    ||
                 (0     == strlen(loadpath))    ||
				 (-1    == *pBranchno)             )
        {
                fprintf(stderr, "  usage: %s\n"
                                         "\t { -dg       <debugging>       }\n"
										 "\t { -branchno <branch number>   }\n"
                                         "\t { -db       <Database Name>   }\n"
                                         "\t { -file     <Input File Name> }\n",
                                         argv[0] );

			return ERROR;
        }


        return OK;
}

// -------------------------------------------------------------------
int main( int argc, char **argv  )
{
        const char *  const FUN = "Main";

        setbuf(stdout, 0); // flush immediately

        char loadpath[256]      = { 0 };
        char database[256]      = { 0 };
		long branchno           = -1;
        int  rc;

		if (OK != (rc = getCmdLine(loadpath, 
						           database, 
								   &branchno,
						           argc, argv)) )
                return rc;
		if(bVersion) return OK;
		
		
        SetLogging(branchno);

        LogMsg( FUN,
                        "----------------------------------------------------------------",
                        FL_INFO);
        LogMsg( FUN, "started", FL_INFO);


		{
			char msg[256];
			sprintf(msg, "branch: %d\tdb: %s\tfile: %s", 
					     branchno, 
						 database, 
						 loadpath);
			LogMsg( FUN, msg, FL_INFO);
		}

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
                rc = Start(pFile, database, branchno);
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
                        break;  // not valid
                else
                {
                        if (' ' == str[i])
                                continue;       // check next character
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
                if ('0' != str[i])      // at minimum one digit != 0
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
        const char * pBufEnd = line + len;      // first byte behind line buffer

        for (const char * pBuf = line; pBuf < pBufEnd; ++pBuf)
        {
                if (0x0A == *pBuf)
                {
                        long allowed = sizeof(struct O_DKRKS);
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
int Start(FILE * pFile, const char * const database, long branchno)
{
        const char * const FUN = "Start";
        int                        rc;

        if ( OK != (rc = DbConnect(database)) )
                return rc;

        if ( OK != (rc = Prepare(branchno)) )
        {
                DbDisconnect();
                return rc;
        }

        char line[sizeof(struct O_DKRKS) + 3] = { 0 };  /* possibly CR + LF + '\0' */

        DEBUG_SECTION
                char msg[256];
                sprintf(msg,
                                "sizeof(O_DKRKS) = %d, sizeof(line) = %d",
                                sizeof(struct O_DKRKS),
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
                        fileoffs = ftell(pFile);                                // save position for next loop
                else
                        line[ftell(pFile) - fileoffs] = 0x0A;   // end of file detected,
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

                assert(rc != ERROR);    // must not happen

                if (OK == rc)
                {
                        // write into table
                        rc = Load((struct O_DKRKS *)line, branchno);

                        if (ERROR == rc)
                                break;
                        else
                        {
                                if (WARNING == rc)              // record is skipped
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
                        rc = OK;        // skip results to OK
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
                rc = AfterLoad(branchno);

        DbDisconnect();

        return rc;
}

// -------------------------------------------------------------------
int Prepare(long branchno)
{
        const char * const FUN = "Prepare";

        EXEC SQL BEGIN DECLARE SECTION;
        const char * pStmt;
        EXEC SQL END DECLARE SECTION;


        /* cursor select */
        pStmt = "select UPD_FLAG from cstdiscacc "
                        "where BRANCHNO = ? "
                        "and CUSTOMERNO = ? "
                        "and DATE = ? "
                        "and INVOICENUMBER = ? "
                        "and VOUCHERTYP = ? "
                        "for update;";

        EXEC SQL PREPARE sel_load FROM :pStmt;
        SQL_ERRMSG( "prepare sel_load" );
        exec sql declare CselLoad cursor with hold for sel_load;


        /* insert */
        pStmt = "insert into cstdiscacc ("
                                "BRANCHNO,"
                                "CUSTOMERNO,"
                                "MAINCSTNO,"
                                "BALANCE,"
                                "UPD_FLAG,"
                                "KDAUFTRAGNR,"
                                "DATE,"
                                "INVOICENUMBER,"
                                "INVOICEAMOUNT,"
                                "VOUCHERTYP,"
                                "PREIS_TYP,"
                                "PRIORITY,"
                                "KDAUFTRAGNRSPLIT,"
                                "INVOICEPAID,"
                                "PAYMENTARGET,"
                                "LFDNR"
                                ") values "
                        "(?, ?, ?, ?, '1',"
                        " ?, ?, ?, ?, ?,"
                        " ?, ?, ?, ?, ?,"
                        " ? );";

        EXEC SQL PREPARE ins_load FROM :pStmt;
        SQL_ERRMSG( "prepare ins_load" );


        /* update */
        pStmt =  "update cstdiscacc "
                         "set "
                                "MAINCSTNO = ?,"
                                "BALANCE = ?,"
                                "UPD_FLAG = ?,"
                                "KDAUFTRAGNR = ?,"
                                "INVOICEAMOUNT = ?,"
                                "PREIS_TYP = ?,"
                                "PRIORITY = ?,"
                                "KDAUFTRAGNRSPLIT = ?,"
                                "INVOICEPAID = ?,"
                                "PAYMENTARGET = ?,"
                                "LFDNR = ?"
                         "where current of CselLoad;";

        EXEC SQL PREPARE upd_load FROM :pStmt;
        SQL_ERRMSG( "prepare upd_load" )

        return SetNotUpdated(branchno);
}

// -------------------------------------------------------------------
int Load (struct O_DKRKS * record, long branchno)
{
        const char * const FUN = "Load";
        char huelse[81];
        double wert;
        long lTarget;

        // --- check valid branchno

        if ( FALSE == IsValidNumber(record->BRANCHNO, sizeof(record->BRANCHNO)) )
        {
                DEBUG_SECTION
                        LogMsg(FUN, "BRANCHNO not valid", FL_WARN);
                END_DEBUG_SECTION

                return WARNING; // skip record
        }

        // --- check valid customerno
        if ( FALSE == IsValidNumber(record->CSTNO, sizeof(record->CSTNO)) )
        {
                DEBUG_SECTION
                        LogMsg(FUN, "CSTNO not valid", FL_WARN);
                END_DEBUG_SECTION

                return WARNING; // skip record
        }


        // --- convert
        EXEC SQL BEGIN DECLARE SECTION;
        struct N_CSTDISCACC row = { 0 };
        EXEC SQL END DECLARE SECTION;

        sprintf(huelse,"%*.*s",L_DKRKS_BRANCHNO,L_DKRKS_BRANCHNO,record->BRANCHNO);
        row.BRANCHNO   = atoi(huelse);

		if (branchno != row.BRANCHNO)
		{
            DEBUG_SECTION
				char msg[256];
				sprintf(msg,
						"line with branch %d not valid",
						row.BRANCHNO);
	            LogMsg(FUN, msg, FL_WARN);
            END_DEBUG_SECTION
				
			return WARNING;	// skip record
		}
		
        sprintf(huelse,"%*.*s",L_DKRKS_CSTNO,L_DKRKS_CSTNO,record->CSTNO);
        row.CUSTOMERNO = atol(huelse);
        sprintf(huelse,"%*.*s",L_DKRKS_MAINCSTNO,L_DKRKS_MAINCSTNO,record->MAINCSTNO);
        row.MAINCSTNO  = atol(huelse);
        sprintf(huelse,"%*.*s",L_DKRKS_BALANCE,L_DKRKS_BALANCE,record->BALANCE);
        wert    = atof(huelse);
        row.BALANCE    = (double)(wert/100);
        sprintf(huelse,"%*.*s",L_DKRKS_DATUM,L_DKRKS_DATUM,record->DATUM);
        row.DATE = atol(huelse) + 20000000; // JJMMTT ergänzen mit Jahrhundert
        sprintf(huelse,"%*.*s",L_DKRKS_AUFNR,L_DKRKS_AUFNR,record->AUFNR);
        row.KDAUFTRAGNR  = atol(huelse);
        sprintf(row.INVOICENUMBER,"%*.*s",L_DKRKS_BELEG_NR,L_DKRKS_BELEG_NR,record->BELEG_NR);
        sprintf(huelse,"%*.*s",L_DKRKS_BETRAG,L_DKRKS_BETRAG,record->BETRAG);
        wert    = atof(huelse);
        row.INVOICEAMOUNT    = (double)(wert/100);
        sprintf(row.VOUCHERTYP,"%*.*s",L_DKRKS_BELEG_TYP,L_DKRKS_BELEG_TYP,record->BELEG_TYP);
        sprintf(huelse,"%*.*s",L_DKRKS_PRIO,L_DKRKS_PRIO,record->PRIO);
        row.PRIORITY  = atol(huelse);
        sprintf(huelse,"%*.*s",L_DKRKS_AUFNR_TEIL,L_DKRKS_AUFNR_TEIL,record->AUFNR_TEIL);
        row.KDAUFTRAGNRSPLIT  = atol(huelse);
        row.INVOICEPAID  = 0.0; //wird zur Zeit nicht uebergeben, kommt aus DKOPO
        sprintf(huelse,"%*.*s",L_DKRKS_TARGET,L_DKRKS_TARGET,record->TARGET);
        lTarget = atol(huelse);
        sprintf(huelse,"%*.*s",L_DKRKS_LFDNR,L_DKRKS_LFDNR,record->LFDNR);
        row.LFDNR = atol(huelse);
        if(lTarget == 0)
        {
                row.PAYMENTARGET = 0;
        }
        else
        {
                row.PAYMENTARGET = GetDiffDays(lTarget + 20000000,row.DATE);
        }
        sprintf(huelse,"%*.*s",L_DKRKS_ABRTYP,L_DKRKS_ABRTYP,record->ABRTYP);
        row.PREIS_TYP  = atol(huelse);

        // --- update/insert row

        EXEC SQL open CselLoad USING    :row.BRANCHNO,
                                                                        :row.CUSTOMERNO,
                                                                        :row.DATE,
                                                                        :row.INVOICENUMBER,
                                                                        :row.VOUCHERTYP;
        SQL_ERRMSG("open CselLoad")

        EXEC SQL fetch CselLoad into :row.UPD_FLAG;
        SQL_ERRMSG("fetch CselLoad")

        if ( SQLCODE == 100 )
        {
                EXEC SQL EXECUTE ins_load using :row.BRANCHNO,
                                                                                :row.CUSTOMERNO,
                                                                                :row.MAINCSTNO,
                                                                                :row.BALANCE,
                                                                                :row.KDAUFTRAGNR,
                                                                                :row.DATE,
                                                                                :row.INVOICENUMBER,
                                                                                :row.INVOICEAMOUNT,
                                                                                :row.VOUCHERTYP,
                                                                                :row.PREIS_TYP,
                                                                                :row.PRIORITY,
                                                                                :row.KDAUFTRAGNRSPLIT,
                                                                                :row.INVOICEPAID,
                                                                                :row.PAYMENTARGET,
                                                                                :row.LFDNR;
                SQL_ERRMSG("ins_load")

                ++sqlstat.ins;
        }
        else
        {
                EXEC SQL EXECUTE upd_load using :row.MAINCSTNO,
                                                                                :row.BALANCE,
                                                                                '1',
                                                                                :row.KDAUFTRAGNR,
                                                                                :row.INVOICEAMOUNT,
                                                                                :row.PREIS_TYP,
                                                                                :row.PRIORITY,
                                                                                :row.KDAUFTRAGNRSPLIT,
                                                                                :row.INVOICEPAID,
                                                                                :row.PAYMENTARGET,
                                                                                :row.LFDNR;
                SQL_ERRMSG("upd_load")

                ++sqlstat.upd;
        }

        return OK;
}

// -------------------------------------------------------------------
int AfterLoad(long branchno)
{
      return DelNotUpdated(branchno);
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
int SetNotUpdated(long branchno)
{
        #define SETCURSORID             "CursorSetNotUpdated"

        const char * const FUN = "SetNotUpdated";

        EXEC SQL BEGIN DECLARE SECTION;
        char stmt[512];
		const char * pStmt;
        const char * pCursorId = SETCURSORID;
        EXEC SQL END DECLARE SECTION;


        sprintf(stmt,
				"select 1 from cstdiscacc "
				"where branchno = %ld and upd_flag != '0' for update;",
				branchno);

        EXEC SQL PREPARE sel_SetNotUp FROM :stmt;
        SQL_ERRMSG( "prepare sel_SetNotUp" )
        EXEC SQL DECLARE :pCursorId CURSOR WITH HOLD FOR sel_SetNotUp;


        pStmt = "update cstdiscacc set upd_flag = '0' where current of " SETCURSORID ";";

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
int DelNotUpdated(long branchno)
{
        #define DELCURSORID             "CursorDelNotUpdated"

        const char * const FUN = "DelNotUpdated";

        EXEC SQL BEGIN DECLARE SECTION;
        char stmt[512];
		const char * pStmt;
        const char * pCursorId = DELCURSORID;
        EXEC SQL END DECLARE SECTION;


        sprintf(stmt,
				"select 1 from cstdiscacc "
				"where branchno = %ld and upd_flag = '0' for update",
				branchno);

        EXEC SQL PREPARE sel_DelNotUp FROM :stmt;
        SQL_ERRMSG( "prepare sel_DelNotUp" )
        EXEC SQL DECLARE :pCursorId CURSOR WITH HOLD FOR sel_DelNotUp;


        pStmt = "delete from cstdiscacc "
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


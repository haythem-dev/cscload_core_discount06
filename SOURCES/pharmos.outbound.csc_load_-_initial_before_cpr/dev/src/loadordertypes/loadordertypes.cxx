/* ---------------------------------------------------------------------------
 *  loadordertypes.cxx 
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadordertypes"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "ordertype.h"
#include "ordertypeflags.h"
#include "ordertypeflagtype.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loadordertypes"
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

static int ins;			// new rows
static int del;			// deleted rows

static int insf;			// new rows
static int delf;			// deleted rows

static int inst;			// new rows
static int delt;			// deleted rows

static char   			logfile [256] 	= { 0 };
static int    			debug_enabled 	= FALSE;
static int    			bVersion	 	= FALSE;

EXEC SQL BEGIN DECLARE SECTION;
const char database[256];
const char indb[256];
ordertypeS ordertype;
ordertypeflagsS ordertypeflags;
ordertypeflagtypeS ordertypeflagtype;
EXEC SQL END DECLARE SECTION;


// -------------------------------------------------------------------

int  DbConnect			  ();
int  DbDisconnect		  ();

int  Start                ();
int  Prepare              ();
int  Delete               ();
 
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
		
	sprintf(msg, "ordertype:");
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "old  deleted : %4d", del);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "new  inserted : %4d", ins);
 	LogMsg( FUN, msg, FL_INFO);
		
	sprintf(msg, "ordertypeflags:");
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "old  deleted : %4d", delf);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "new  inserted : %4d", insf);
 	LogMsg( FUN, msg, FL_INFO);

	sprintf(msg, "ordertypeflagtype:");
	LogMsg(FUN, msg, FL_INFO);
	sprintf(msg, "old  deleted : %4d", delt);
	LogMsg(FUN, msg, FL_INFO);
	sprintf(msg, "new  inserted : %4d", inst);
	LogMsg(FUN, msg, FL_INFO);
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
		else if ( !strcmp( argv[i], "-dbin" ) )
		{
			i++;

			if (i < argc)
				sprintf( indb, "%s", argv[i] );
		}
		else if ( !strcmp( argv[i], "-dbout" ) )
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
		 (0     == strlen(indb))	   )
	{
		char msg[256];
		sprintf(msg, "  usage: %s\n"
	   				 "\t { -dg    <debugging> }\n"
					 "\t { -dbin  <Input-Database Name> }\n"
					 "\t { -dbout <Output-Database Name> }\n"
					 ,argv[0] );
		printf(msg);
		LogMsg(FUN, msg, FL_FAIL); 
		
    	return ERROR;
	}

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

	/* start loading data */

	if (OK != (rc = Start()) )
		return rc;
		
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
int Start()
{
	const char * const FUN = "Start";
	int	rc = 0;

	if ( OK != (rc = DbConnect()) )
		return rc;

	if ( OK != (rc = Prepare()) )
	{
		DbDisconnect();
		return rc;	
	}

	if ( OK != (rc = Delete()) )
	{
		DbDisconnect();
		return rc;	
	}

	EXEC SQL begin work;
	SQL_ERRMSG("begin work")

	EXEC SQL open Cselcordertype;
	SQL_ERRMSG("open Cselcordertype")

	// for each line
	for(ins=0;;ins++)
	{
		EXEC SQL fetch Cselcordertype into :ordertype;
		SQL_ERRMSG("fetch Cselcordertype")
		if ( SQLCODE == 100 ) break;

		EXEC SQL EXECUTE ins_ordertype using	:ordertype.CSCORDERTYPE,
												:ordertype.NAME;
		SQL_ERRMSG("ins_ordertype")

		
		if ( ins % TRANSACTLOOP == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work between")
			
			EXEC SQL begin work;
			SQL_ERRMSG("begin work between")
		}
	
	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work")

	EXEC SQL begin work;
	SQL_ERRMSG("begin work flags")

	EXEC SQL open Cselcordertypeflags;
	SQL_ERRMSG("open Cselcordertypeflags")

	// for each line
	for (insf = 0;; insf++)
	{
		EXEC SQL fetch Cselcordertypeflags into :ordertypeflags;
		SQL_ERRMSG("fetch Cselcordertypeflags")
			if (SQLCODE == 100) break;
	
		EXEC SQL EXECUTE ins_ordertypeflags using	:ordertypeflags.CSCORDERTYPE,
													:ordertypeflags.ORDERTYPEFLAGTYPE,
													:ordertypeflags.ORDERTYPEFLAG;
		SQL_ERRMSG("ins_ordertypeflags")
	
	
		if (insf % TRANSACTLOOP == 0)
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work between flags")
	
			EXEC SQL begin work;
			SQL_ERRMSG("begin work between flags")
		}
	
	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work flags")

	EXEC SQL begin work;
	SQL_ERRMSG("begin work flagtype")

	EXEC SQL open Cselcordertypeflagtype;
	SQL_ERRMSG("open Cselcordertypeflagtype")

	// for each line
	for (inst = 0;; inst++)
	{
		EXEC SQL fetch Cselcordertypeflagtype into : ordertypeflagtype;
		SQL_ERRMSG("fetch Cselcordertypeflagtype")
		if (SQLCODE == 100) break;

		EXEC SQL EXECUTE ins_ordertypeflagtype using	:ordertypeflagtype.ORDERTYPEFLAGTYPE,
														:ordertypeflagtype.DESCRIPTION,
														:ordertypeflagtype.INDEX_DKAUA;
		SQL_ERRMSG("ins_ordertypeflagtype")


		if (inst % TRANSACTLOOP == 0)
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work between flagtype")

			EXEC SQL begin work;
			SQL_ERRMSG("begin work between flagtype")
		}

	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work flagtype")

	DbDisconnect();
		
	return rc;
}

// -------------------------------------------------------------------
int Prepare()
{
	const char * const FUN = "Prepare";

	EXEC SQL BEGIN DECLARE SECTION;
	char Stmt[1024];
	EXEC SQL END DECLARE SECTION;


	/* cursor for delete ordertype */
	sprintf(Stmt,"select 1 from ordertype "
			"for update;");

	EXEC SQL PREPARE del_load_ordertype FROM :Stmt;
	SQL_ERRMSG( "prepare del_load_ordertype" );
	exec sql declare Cdelordertype cursor with hold for del_load_ordertype;

	sprintf(Stmt,"delete from ordertype "
			"where current of Cdelordertype;");
	EXEC SQL PREPARE del_ordertype FROM :Stmt;
	SQL_ERRMSG( "prepare del_ordertype" );

	/* cursor for delete ordertypeflags */
	sprintf(Stmt, "select 1 from ordertypeflags "
		"for update;");

	EXEC SQL PREPARE del_load_ordertypeflags FROM : Stmt;
	SQL_ERRMSG("prepare del_load_ordertypeflags");
	exec sql declare Cdelordertypeflags cursor with hold for del_load_ordertypeflags;

	sprintf(Stmt, "delete from ordertypeflags "
		"where current of Cdelordertypeflags;");
	EXEC SQL PREPARE del_ordertypeflags FROM : Stmt;
	SQL_ERRMSG("prepare del_ordertypeflags");

	/* cursor for delete ordertypeflagtype */
	sprintf(Stmt, "select 1 from ordertypeflagtype "
		"for update;");

	EXEC SQL PREPARE del_load_ordertypeflagtype FROM : Stmt;
	SQL_ERRMSG("prepare del_load_ordertypeflagtype");
	exec sql declare Cdelordertypeflagtype cursor with hold for del_load_ordertypeflagtype;

	sprintf(Stmt, "delete from ordertypeflagtype "
		"where current of Cdelordertypeflagtype;");
	EXEC SQL PREPARE del_ordertypeflagtype FROM : Stmt;
	SQL_ERRMSG("prepare del_ordertypeflagtype");


	/* cursor select ordertype*/
	sprintf(Stmt, "select "
		ORDERTYPE_PELISTE
		" from "
		"%s:cordertype;"
			,indb);

	EXEC SQL PREPARE sel_load_ordertype FROM :Stmt;
	SQL_ERRMSG( "prepare sel_load_ordertype" );
	exec sql declare Cselcordertype cursor with hold for sel_load_ordertype;
	
	/* insert ordertype*/
	sprintf(Stmt,"insert into ordertype ("
		ORDERTYPE_PELISTE
			") values "
			"(?, ?);");

	EXEC SQL PREPARE ins_ordertype FROM :Stmt;
	SQL_ERRMSG( "prepare ins_ordertype" );

	/* cursor select ordertypeflags*/
	sprintf(Stmt, "select "
		ORDERTYPEFLAGS_PELISTE
		" from "
		"%s:cordertypeflags;"
		, indb);

	EXEC SQL PREPARE sel_load_ordertypeflags FROM : Stmt;
	SQL_ERRMSG("prepare sel_load_ordertypeflags");
	exec sql declare Cselcordertypeflags cursor with hold for sel_load_ordertypeflags;

	/* insert ordertypeflags*/
	sprintf(Stmt, "insert into ordertypeflags ("
		ORDERTYPEFLAGS_PELISTE
		") values "
		"(?, ?, ?);");

	EXEC SQL PREPARE ins_ordertypeflags FROM : Stmt;
	SQL_ERRMSG("prepare ins_ordertypeflags");

	/* cursor select ordertypeflagtype*/
	sprintf(Stmt, "select "
		ORDERTYPEFLAGTYPE_PELISTE
		" from "
		"%s:cordertypeflagtype;"
		, indb);

	EXEC SQL PREPARE sel_load_ordertypeflagtype FROM : Stmt;
	SQL_ERRMSG("prepare sel_load_ordertypeflagtype");
	exec sql declare Cselcordertypeflagtype cursor with hold for sel_load_ordertypeflagtype;

	/* insert ordertype*/
	sprintf(Stmt, "insert into ordertypeflagtype ("
		ORDERTYPEFLAGTYPE_PELISTE
		") values "
		"(?, ?, ?);");

	EXEC SQL PREPARE ins_ordertypeflagtype FROM : Stmt;
	SQL_ERRMSG("prepare ins_ordertypeflagtype");

	
	return OK;
}

// -------------------------------------------------------------------
int Delete()
{
	const char * const FUN = "Delete";
	int	rc = 0;

// ordertype

	EXEC SQL begin work;
	SQL_ERRMSG("begin work del ordertype")

	EXEC SQL open Cdelordertype;
	SQL_ERRMSG("open Cdelordertype")

	// for each line
	for(del=0;;del++)
	{
		EXEC SQL fetch Cdelordertype into :ordertype.CSCORDERTYPE;
		SQL_ERRMSG("fetch Cdelordertype")
		if ( SQLCODE == 100 ) break;

		EXEC SQL EXECUTE del_ordertype;
		SQL_ERRMSG("del_ordertype")
		
		if ( del % TRANSACTLOOP == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work del ordertype between")
			
			EXEC SQL begin work;
			SQL_ERRMSG("begin work del ordertype between")
		}

	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work del ordertype")

	// ordertypeflags

	EXEC SQL begin work;
	SQL_ERRMSG("begin work del ordertypeflags")

	EXEC SQL open Cdelordertypeflags;
	SQL_ERRMSG("open Cdelordertypeflags")

	// for each line
	for (delf = 0;; delf++)
	{
		EXEC SQL fetch Cdelordertypeflags into :ordertypeflags.CSCORDERTYPE;
		SQL_ERRMSG("fetch Cdelordertypeflags")
		if (SQLCODE == 100) break;
		EXEC SQL EXECUTE del_ordertypeflags;
		SQL_ERRMSG("del_ordertypeflags")

		if (delf % TRANSACTLOOP == 0)
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work del ordertypeflags between")

			EXEC SQL begin work;
			SQL_ERRMSG("begin work del ordertypeflags between")
		}

	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work del ordertypeflags")

	// ordertypeflagtype

	EXEC SQL begin work;
	SQL_ERRMSG("begin work del ordertypeflagtype")

	EXEC SQL open Cdelordertypeflagtype;
	SQL_ERRMSG("open Cdelordertypeflagtype")

	// for each line
	for (delt = 0;; delt++)
	{
		EXEC SQL fetch Cdelordertypeflagtype into :ordertypeflagtype.ORDERTYPEFLAGTYPE;
		SQL_ERRMSG("fetch Cdelordertypeflagtype")
		if (SQLCODE == 100) break;

		EXEC SQL EXECUTE del_ordertypeflagtype;
		SQL_ERRMSG("del_ordertypeflagtype")

		if (del % TRANSACTLOOP == 0)
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work del ordertypeflagtype between")

			EXEC SQL begin work;
			SQL_ERRMSG("begin work del ordertypeflagtype between")
		}

	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work del ordertypeflatypes")


	return OK;
}

/***** end of file *****************************************************************/


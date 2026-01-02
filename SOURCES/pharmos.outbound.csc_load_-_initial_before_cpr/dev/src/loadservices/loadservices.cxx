/* ---------------------------------------------------------------------------
 *  loadservices.cxx 
 *     laden Serviceauftrageintraege
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadservices"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "services.h"
#include "servicetypes.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loadservices"
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

static int inst;			// new rows
static int delt;			// deleted rows

static char   			logfile [256] 	= { 0 };
static int    			debug_enabled 	= FALSE;
static int    			bVersion	 	= FALSE;

EXEC SQL BEGIN DECLARE SECTION;
const char database[256];
const char indb[256];
servicesS services;
servicetypesS types;
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
		
	sprintf(msg, "services:");
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "old  deleted : %4d", del);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "new  inserted : %4d", ins);
 	LogMsg( FUN, msg, FL_INFO);
		
	sprintf(msg, "servicetypes:");
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "old  deleted : %4d", delt);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "new  inserted : %4d", inst);
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

	EXEC SQL open Cselcservices;
	SQL_ERRMSG("open Cselcservices")

	// for each line
	for(ins=0;;ins++)
	{
		EXEC SQL fetch Cselcservices into :services;
		SQL_ERRMSG("fetch Cselcservices")
		if ( SQLCODE == 100 ) break;

		EXEC SQL EXECUTE ins_service using :services.SERVICE_NO, 
										:services.NAME, 
										:services.SERVICETYPENO;
		SQL_ERRMSG("ins_service")

		
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
	SQL_ERRMSG("begin work types")

	EXEC SQL open Cselctypes;
	SQL_ERRMSG("open Cselctypes")

	// for each line
	for(inst=0;;inst++)
	{
		EXEC SQL fetch Cselctypes into :types;
		SQL_ERRMSG("fetch Cselctypes")
		if ( SQLCODE == 100 ) break;

		EXEC SQL EXECUTE ins_type using :types.SERVICETYPENO, 
										:types.NAME, 
										:types.ORDER_TYPE;
		SQL_ERRMSG("ins_type")

		
		if ( ins % TRANSACTLOOP == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work types between")
			
			EXEC SQL begin work;
			SQL_ERRMSG("begin work types between")
		}
	
	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work types")

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


	/* cursor for delete services*/
	sprintf(Stmt,"select SERVICE_NO from services "
			"for update;");

	EXEC SQL PREPARE del_load_srvice FROM :Stmt;
	SQL_ERRMSG( "prepare del_load_srvice" );
	exec sql declare Cdelservice cursor with hold for del_load_srvice;

	sprintf(Stmt,"delete from services "
			"where current of Cdelservice;");
	EXEC SQL PREPARE del_service FROM :Stmt;
	SQL_ERRMSG( "prepare del_service" );

	/* cursor for delete servicetypes*/
	sprintf(Stmt,"select SERVICETYPENO from servicetypes "
			"for update;");

	EXEC SQL PREPARE del_load_types FROM :Stmt;
	SQL_ERRMSG( "prepare del_load_types" );
	exec sql declare Cdeltype cursor with hold for del_load_types;

	sprintf(Stmt,"delete from servicetypes "
			"where current of Cdeltype;");
	EXEC SQL PREPARE del_type FROM :Stmt;
	SQL_ERRMSG( "prepare del_types" );

	/* cursor select service*/
	sprintf(Stmt,"select "
			SERVICES_PELISTE
			" from "
			"%s:cservices "
			"for update;"
			,indb);

	EXEC SQL PREPARE sel_load_service FROM :Stmt;
	SQL_ERRMSG( "prepare sel_load_service" );
	exec sql declare Cselcservices cursor with hold for sel_load_service;
	
	/* insert service*/
	sprintf(Stmt,"insert into services ("
			SERVICES_PELISTE
			") values "
			"(?, ?, ?);");

	EXEC SQL PREPARE ins_service FROM :Stmt;
	SQL_ERRMSG( "prepare ins_service" );

	/* cursor select types*/
	sprintf(Stmt,"select "
			SERVICETYPES_PELISTE
			" from "
			"%s:cservicetypes "
			"for update;"
			,indb);

	EXEC SQL PREPARE sel_load_type FROM :Stmt;
	SQL_ERRMSG( "prepare sel_load_type" );
	exec sql declare Cselctypes cursor with hold for sel_load_type;
	
	/* insert */
	sprintf(Stmt,"insert into servicetypes ("
			SERVICETYPES_PELISTE
			") values "
			"(?, ?, ?);");

	EXEC SQL PREPARE ins_type FROM :Stmt;
	SQL_ERRMSG( "prepare ins_type" );
	
	return OK;
}

// -------------------------------------------------------------------
int Delete()
{
	const char * const FUN = "Delete";
	int	rc = 0;

// Services

	EXEC SQL begin work;
	SQL_ERRMSG("begin work service")

	EXEC SQL open Cdelservice;
	SQL_ERRMSG("open Cdelservice")

	// for each line
	for(del=0;;del++)
	{
		EXEC SQL fetch Cdelservice into :services.SERVICE_NO;
		SQL_ERRMSG("fetch Cdelservice")
		if ( SQLCODE == 100 ) break;

		EXEC SQL EXECUTE del_service;
		SQL_ERRMSG("del_service")
		
		if ( del % TRANSACTLOOP == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work service between")
			
			EXEC SQL begin work;
			SQL_ERRMSG("begin work service between")
		}

	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work service")

// Types

	EXEC SQL begin work;
	SQL_ERRMSG("begin work types")

	EXEC SQL open Cdeltype;
	SQL_ERRMSG("open Cdeltype")

	// for each line
	for(delt=0;;delt++)
	{
		EXEC SQL fetch Cdeltype into :types.SERVICETYPENO;
		SQL_ERRMSG("fetch Cdeltype")
		if ( SQLCODE == 100 ) break;

		EXEC SQL EXECUTE del_type;
		SQL_ERRMSG("del_type")
		
		if ( del % TRANSACTLOOP == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work types between")
			
			EXEC SQL begin work;
			SQL_ERRMSG("begin work types between")
		}

	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work types")

	return OK;
}

/***** end of file *****************************************************************/


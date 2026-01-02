/* ---------------------------------------------------------------------------
 *  loadpromoquota.cxx 
 *     laden PromotionQuota
 * -------------------------------------------------------------------------*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadpromotionquota"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "pplib/allg.h"
#include "promotionquota.h"

EXEC SQL include sqlca;

// -------------------------------------------------------------------

#define APPLICATION		   "loadpromoquota"
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

static int ins = 0;			// new rows
static int upd = 0;			// updated rows

static char   			logfile [256] 	= { 0 };
static int    			debug_enabled 	= FALSE;
static int    			bVersion	 	= FALSE;

EXEC SQL BEGIN DECLARE SECTION;
char database[256];
char indb[256];
promotionquotaS promo;
short sBranchNo = 0;
short sPromotion_No;
long lCustomerNo;
long lBranchQuotaQTY;
long lCustomerQuotaQTY;
long lCustomerMinQTY;
long lArticleno;
long lDateFrom;
long lDateTo;
EXEC SQL END DECLARE SECTION;


// -------------------------------------------------------------------

int  DbConnect			  ();
int  DbDisconnect		  ();

int  Start                ();
int  Prepare              ();
int  SetNotUpd            ();
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
		
	sprintf(msg, "promotionquota:");
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "old  updated : %4d", upd);
 	LogMsg( FUN, msg, FL_INFO);
	sprintf(msg, "new  inserted : %4d", ins);
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
		 (0     == strlen(indb))		||
		 (0		== sBranchNo)	)
	{
		char msg[256];
		sprintf(msg, "  usage: %s\n"
	   				 "\t { -dg    <debugging> }\n"
					 "\t { -dbin  <Input-Database Name> }\n"
					 "\t { -dbout <Output-Database Name> }\n"
					 "\t { -branchno <Vz-Nr> }\n"
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

	lDateFrom = AllgGetDate();
	lDateTo = lDateFrom;

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

	if (OK != (rc = SetNotUpd()) )
		return rc;

	EXEC SQL begin work;
	SQL_ERRMSG("begin work")

	EXEC SQL open Cselquota using :sBranchNo;
	SQL_ERRMSG("open Cselquota")

	// for each line
	for(;;)
	{
		EXEC SQL fetch Cselquota into
				:sPromotion_No,
				:lBranchQuotaQTY,
				:lCustomerQuotaQTY,
				:lArticleno,
				:lCustomerMinQTY;

		SQL_ERRMSG("fetch Cselquota")
		if ( SQLCODE == 100 ) break;

		EXEC SQL open Cseldiscount using :sPromotion_No,:lDateTo;
		SQL_ERRMSG("open Cseldiscount")

		EXEC SQL fetch Cseldiscount;
		SQL_ERRMSG("fetch Cseldiscount")
		if ( SQLCODE == 100 ) continue;

		EXEC SQL open CselPromoquota using :sBranchNo,:sPromotion_No,:lArticleno;
		SQL_ERRMSG("open CselPromoquota")

		EXEC SQL fetch CselPromoquota into :promo;
		SQL_ERRMSG("fetch CselPromoquota")

		if ( SQLCODE == 100 )
		{
			EXEC SQL EXECUTE ins_promo using :sBranchNo, 
										:sPromotion_No, 
										:lBranchQuotaQTY,
										:lCustomerQuotaQTY,
										:lArticleno,
										:lCustomerMinQTY;
			SQL_ERRMSG("ins_promo")
			ins++;
			char msg[256];
			sprintf(msg, "promotionquota geloescht fuer %d",sPromotion_No);
		 	LogMsg( FUN, msg, FL_INFO);
		}
		else
		{
/*			if(promo.BRANCHQUOTAQTY != lBranchQuotaQTY ||
				promo.CUSTOMERQUOTAQTY != lCustomerQuotaQTY) */
			{
				EXEC SQL EXECUTE upd_promoquota using 
										:lBranchQuotaQTY,
										:lCustomerQuotaQTY,
										:lArticleno,
										:lCustomerMinQTY;
				SQL_ERRMSG("upd_promoquota")
				upd++;
				if(promo.CUSTOMERQUOTAQTY != lCustomerQuotaQTY)
				{
					EXEC SQL open Cselcst using :sBranchNo,:sPromotion_No,:lArticleno;
					SQL_ERRMSG("open Cselcst")

					for(;;)
					{
						EXEC SQL fetch Cselcst into :lCustomerNo;
						SQL_ERRMSG("fetch Cselcst")
						if ( SQLCODE == 100 ) break;
	
						EXEC SQL EXECUTE upd_promoquotacst using :lCustomerQuotaQTY;
						SQL_ERRMSG("upd_promoquotacst")
					}
				}
			}
/*			else continue; */
		}
		
		if ( (ins+upd) % TRANSACTLOOP == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work between")
			
			EXEC SQL begin work;
			SQL_ERRMSG("begin work between")
		}
	
	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work")

	if (OK != (rc = Delete()) )
		return rc;

	DbDisconnect();
		
	return rc;
}

// -------------------------------------------------------------------
int SetNotUpd()
{
	const char * const FUN = "SetNotUpd";
	int count;

	EXEC SQL BEGIN DECLARE SECTION;
	char upd_flag[2];
	EXEC SQL END DECLARE SECTION;

	EXEC SQL begin work;
	SQL_ERRMSG("begin work")

	EXEC SQL open Cselupdflag using :sBranchNo;
	SQL_ERRMSG("open Cselupdflag")

	for(count = 0;;)
	{
		EXEC SQL fetch Cselupdflag into :upd_flag;
		SQL_ERRMSG("fetch Cselupdflag")
		if ( SQLCODE == 100 ) break;

		EXEC SQL EXECUTE upd_updflag;
		SQL_ERRMSG("upd_updflag")
		
		if ( (count++) % TRANSACTLOOP == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work between")
			
			EXEC SQL begin work;
			SQL_ERRMSG("begin work between")
		}
	
	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work")
	
	return OK;
}

// -------------------------------------------------------------------
int Delete()
{
	const char * const FUN = "Delete";
	int count;

	EXEC SQL BEGIN DECLARE SECTION;
	short sPromoNo;
	long lCstNo;
	long lArticleNo;
	EXEC SQL END DECLARE SECTION;

	EXEC SQL begin work;
	SQL_ERRMSG("begin work")

	EXEC SQL open Cdelupdflag using :sBranchNo;
	SQL_ERRMSG("open Cdelupdflag")

	for(count = 0;;)
	{
		EXEC SQL fetch Cdelupdflag into :sPromoNo,:lArticleNo;
		SQL_ERRMSG("fetch Cdelupdflag")
		if ( SQLCODE == 100 ) break;

		EXEC SQL EXECUTE delete_updflag;
		SQL_ERRMSG("delete_updflag")

		EXEC SQL open Cselcst using :sBranchNo,:sPromoNo,:lArticleNo;
		SQL_ERRMSG("open Cselcst")

		for(;;)
		{
			EXEC SQL fetch Cselcst into :lCstNo;
			SQL_ERRMSG("fetch Cselcst")
			if ( SQLCODE == 100 ) break;
	
			EXEC SQL EXECUTE delete_cst;
			SQL_ERRMSG("delete_cst")
		}
		char msg[256];
		sprintf(msg, "promotionquota geloescht fuer %d",sPromoNo);
	 	LogMsg( FUN, msg, FL_INFO);
		
		if ( (count++) % TRANSACTLOOP == 0 )
		{
			EXEC SQL commit work;
			SQL_ERRMSG("commit work between")
			
			EXEC SQL begin work;
			SQL_ERRMSG("begin work between")
		}
	
	}

	EXEC SQL COMMIT WORK;
	SQL_ERRMSG("commit work")
	
	return OK;
}

// -------------------------------------------------------------------
int Prepare()
{
	const char * const FUN = "Prepare";

	EXEC SQL BEGIN DECLARE SECTION;
	char Stmt[1024];
	EXEC SQL END DECLARE SECTION;

	/* cursor for update */
	sprintf(Stmt,"select "
				PROMOTIONQUOTA_PELISTE
				" from promotionquota "
				"where branchno = ? "
				"and promotion_no = ? "
				"and articleno = ? "
				"for update;");

	EXEC SQL PREPARE sel_promoquota FROM :Stmt;
	SQL_ERRMSG( "prepare sel_promoquota" );
	exec sql declare CselPromoquota cursor with hold for sel_promoquota;

	sprintf(Stmt,"update promotionquota set "
		         "BRANCHQUOTAQTY=?,"
			     "CUSTOMERQUOTAQTY=?,"
			     "ARTICLENO=?,"
			     "CUSTOMERMINQTY=?,"
			     "UPD_FLAG=1 "
				 "where current of CselPromoquota;");
	EXEC SQL PREPARE upd_promoquota FROM :Stmt;
	SQL_ERRMSG( "prepare upd_promoquota" );

	/* cursor select */
	sprintf(Stmt,"select "
		         "PROMOTION_NO,"
			     "BRANCHQUOTAQTY,"
				 "CUSTOMERQUOTAQTY,"
				 "ARTICLENO,"
				 "CUSTOMERMINQTY"
				 " from "
				 "%s:bdmpromotionquota "
				 "where BRANCHNO = ?;"
				,indb);

	EXEC SQL PREPARE sel_quota FROM :Stmt;
	SQL_ERRMSG( "prepare sel_quota" );
	exec sql declare Cselquota cursor with hold for sel_quota;

	/* check validity */
	
	sprintf(Stmt,"select "
		         "BASEQTY"
				 " from "
				 "%s:cdiscount "
				 "where PROMOTION_NO = ? "
				 "and DATETO >= ? "
				,indb);

	EXEC SQL PREPARE sel_discount FROM :Stmt;
	SQL_ERRMSG( "prepare sel_discount" );
	exec sql declare Cseldiscount cursor with hold for sel_discount;
	
	/* insert */
	sprintf(Stmt,"insert into promotionquota ("
			PROMOTIONQUOTA_PELISTE
			") values "
			"(?, ?, ?, ?, 0, 1, ?, ?);");

	EXEC SQL PREPARE ins_promo FROM :Stmt;
	SQL_ERRMSG( "prepare ins_promo" );

	/* set upd_flag */
	
	sprintf(Stmt,"select "
		         "UPD_FLAG"
				 " from "
				 "promotionquota "
				 "where BRANCHNO = ? "
 				 "for update;");

	EXEC SQL PREPARE sel_updflag FROM :Stmt;
	SQL_ERRMSG( "prepare sel_updflag" );
	exec sql declare Cselupdflag cursor with hold for sel_updflag;

	sprintf(Stmt,"update promotionquota set "
		         "UPD_FLAG = 0 "
				 "where current of Cselupdflag;");
	EXEC SQL PREPARE upd_updflag FROM :Stmt;
	SQL_ERRMSG( "prepare upd_updflag" );

	/* delete */
	
	sprintf(Stmt,"select "
		         "promotion_no,"
		         "articleno"
				 " from "
				 "promotionquota "
				 "where BRANCHNO = ? "
				 "and UPD_FLAG = 0 "
 				 "for update;");

	EXEC SQL PREPARE del_updflag FROM :Stmt;
	SQL_ERRMSG( "prepare del_updflag" );
	exec sql declare Cdelupdflag cursor with hold for del_updflag;

	sprintf(Stmt,"delete from promotionquota "
				 "where current of Cdelupdflag;");
	EXEC SQL PREPARE delete_updflag FROM :Stmt;
	SQL_ERRMSG( "prepare delete_updflag" );

	/* delete Customer*/
	
	sprintf(Stmt,"select "
		         "customerno"
				 " from "
				 "promotionquotacst "
				 "where BRANCHNO = ? "
				 "and PROMOTION_NO = ? "
				 "and ARTICLENO = ? "
 				 "for update;");

	EXEC SQL PREPARE del_cst FROM :Stmt;
	SQL_ERRMSG( "prepare del_cst" );
	exec sql declare Cselcst cursor with hold for del_cst;

	sprintf(Stmt,"delete from promotionquotacst "
				 "where current of Cselcst;");
	EXEC SQL PREPARE delete_cst FROM :Stmt;
	SQL_ERRMSG( "prepare delete_cst" );

	/* update Customer*/

	sprintf(Stmt,"update promotionquotacst set "
			     "CUSTOMERQUOTAQTY=? "
				 "where current of Cselcst;");
	EXEC SQL PREPARE upd_promoquotacst FROM :Stmt;
	SQL_ERRMSG( "prepare upd_promoquotacst" );
	
	return OK;
}

/***** end of file *****************************************************************/


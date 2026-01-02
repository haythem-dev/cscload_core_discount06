/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadbrancharticleconfig"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "ibtbrancharticleconfig.h"
#include "puibtbrancharticleconfig.h"
#include "pplib/allg.h"
#include <dirent.h>                                     
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define NOTFOUND           sqlca.sqlcode == SQLNOTFOUND

#define OK                   0
#define NO                   0
#define YES                  1
#define ERROR               -1
#define INSERT               1
#define NOT_FOUND            1
#define FILE_NOT_FOUND       1
#define WARNING             -2
#define HINW               'H'
#define FEHL               'F'
#define RIO_EOF            110
#define RIO_NOFIND         111
#define INDATABASE         "phosix@db2_rmfuze1_tcp"
#define OUTDATABASE        "phosix"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */


char log_file [300 + 1];
char dateiname[L_TEXT];
char countrycode[3] = "";
int explain = NO;
int zaehlerIns = 0;     /* weil ich zu faul war alex */
int zaehlerUpd = 0;     /* weil ich zu faul war alex */
int zaehlerDel = 0;     /* weil ich zu faul war alex */
int zaehlerUpdWafo = 0;

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
struct N_PUIBTBRANCHARTICLECONFIG a;
short sBranchno = 0;
long lDateStart;
long lDateStop;
long lTimeStart;
long lTimeStop;
long lArticleNo;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo( char *error_msg, char mld, int rc );
int StartLoadingIBTBranchArticle	( char *error_msg);
int PrepareLoadTables				( char *error_msg);
int LoadTables						( char *error_msg);
int AfterLoadTables					( char *error_msg);
int PrepareReadIBTBranchArticle		( char *error_msg);
int PrepareLoadingIBTBranchArticle	( char *error_msg);
int LoadIBTBranchArticle			( char *error_msg);
int AfterLoadingIBTBranchArticle	( char *error_msg);
int DeteteIBTBranchArticle			( char *error_msg);

/****** LOAD ARTIKELLOKAL.WAFOTYP from CDM ***********************************/
int LadeArtikelLokalWafoTyp                 ( char* error_msg);
int UpdateArticleLocalFromSubsequentDelivery( char* error_msg);
int UpdateArticleLocalFromZArticleAustria   ( char* error_msg);
int UpdateArticleLocalFromZArticleFrance    ( char* error_msg);
int UpdateArticleLocalNotUsed               ( char* error_msg);

int CloseDatabase( void );

/***** MAIN *****************************************************************/

int main( int argc, char **argv  )
{
	char  error_msg[181];
	char  *schalter;
	int   i;
	char  *fun = "Main";
	char  *LOG_FILE = "loadbrancharticleconfig.log";
	char  *LOG_PATH;
	char  logpath[256 + 1];
	int   rc;
	int   status = 0;
	char  start_msg[81];

	sprintf(indatenbank,"%s",INDATABASE);
	sprintf(outdatenbank,"%s",OUTDATABASE);
     
	strcpy(start_msg, "gestartet mit:");
	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-dbin" ) )
		{
			strcat(start_msg, " -dbin");
			i++;
			sprintf( indatenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-dbout" ) )
		{
			strcat(start_msg, " -dbout");
			i++;
			sprintf( outdatenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-branchno" ) )
		{
			strcat(start_msg, " -branchno");
			i++;
			sBranchno = atoi(argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if (!strcmp(schalter, "-countrycode"))
		{
			strcat(start_msg, " -countrycode");
			i++;
			sprintf(countrycode, "%s", argv[i]);
			sprintf(start_msg, "%s %s", start_msg, argv[i]);
		}
		else if ( !strcmp( schalter, "-ex" ) )
		{
			strcat(start_msg, " -ex");
			explain = YES;
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
		else
		{
			printf( "  usage: %s\n\t"
				" { -dbin datenbankname <Datenbankname Eingabe> }\n\t"
				" { -dbout datenbankname <Datenbankname Ausgabe> }\n\t"
				" { -branchno filialnr }\n\t"
				" [ -ex <Explain> ]\n\t",
				argv[0] );
			return 1;
		}
	}

	exec sql database :outdatenbank;
	ERROR_MSG( "Fehler oeffnen DB" )

	exec sql set lock mode to wait 20;
	ERROR_MSG( "Set LockMode to Wait" )

	exec sql set isolation to dirty read;
	ERROR_MSG( "Set Isolation to Dirty Read" )

	if (explain == YES)
	{
		exec sql set explain on;
		ERROR_MSG( "Set Explain On" )
	}

	lDateStart = AllgGetDate();
	lTimeStart = AllgGetTime();

	PrintMsg( fun, start_msg, HINW, 0 );
	if (strcmp(countrycode, "de") == 0 || strcmp(countrycode, "DE") == 0)
	{
		if (PrepareLoadTables(error_msg) != OK)
			return 8;

		if ((rc = StartLoadingIBTBranchArticle(error_msg)) != 0)
		{
			PrintMsg(fun, "mit Fehler beendet", FEHL, rc);
			return 9;
		}
		if ((rc = AfterLoadTables(error_msg)) != 0)
		{
			PrintMsg(fun, "mit Fehler beendet", FEHL, rc);
			return 10;
		}
		sprintf(start_msg, "IBTBranchArticleConfig geaendert: %d eingefuegt: %d geloescht: %d ", zaehlerUpd, zaehlerIns, zaehlerDel);
		PrintMsg(fun, start_msg, HINW, 0);
	}
	if ((rc = LadeArtikelLokalWafoTyp(error_msg)) != 0)
	{
		PrintMsg(fun, "mit Fehler beendet", FEHL, rc);
		return 11;
	}

	sprintf(start_msg, "ArtikelLokal WAFOTYP geaendert: %d", zaehlerUpdWafo);
	PrintMsg(fun, start_msg, HINW, 0);
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** START LOADING ************************************/

int StartLoadingIBTBranchArticle( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StartLoadingIBTBranchArticle";
   
	exec sql open Cselpuibtbrancharticleconfig using :sBranchno;
	ERROR_MSG( "open Cselpuibtbrancharticleconfig" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch Cselpuibtbrancharticleconfig into :a.ARTICLENO,:a.IBTROLETYPEID,:a.ASSORTMENTTYPEID,:a.RELEVANCEFLAG;
		ERROR_MSG( "fetch Cselpuibtbrancharticleconfig" )
		if(NOTFOUND) break;
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }

		if(a.RELEVANCEFLAG == 1 && a.IBTROLETYPEID == 0) a.IBTROLETYPEID = 3;

		if ( ( rc = LoadTables( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
        else if ( explain == YES )
           if ( zaehler > 5000 ) break;   /* Nur 5000 Saetze verarbeiten */

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	if ( explain == YES ) return OK;
	rc = OK;
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;

	if ( ( rc = PrepareReadIBTBranchArticle( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLoadingIBTBranchArticle( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;

	rc = LoadIBTBranchArticle(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;

	if ( (rc = AfterLoadingIBTBranchArticle(error_msg)) < 0) return rc;

	return OK;
}

/*** LOESCHEN NICHT GEAENDERTE SAETZE ************************************************/

int DeteteIBTBranchArticle( char *error_msg )
{
	char *fun = "DeteteIBTBranchArticle";
	int i;

	exec sql begin declare section;
	char str[2048];
	char cStart[20];
	char cStartText[200];
	exec sql end declare section;


//	AllgDateTimeLong2CharToMinute(lDateStart,lTimeStart,cStart);
	sprintf(cStart,"%4d-%02d-%02d %02d:%02d",lDateStart/10000,lDateStart/100%100,lDateStart%100,lTimeStart/10000,lTimeStart/100%100);

	sprintf(cStartText,"datetime(%s) year to minute",cStart);

/*	strcat( str, "and lastchangedatetime between datetime(?) year to minute and datetime(?) year to minute " );	*/

	strcpy( str, "select 1 from ibtbrancharticleconfig " );
	strcat( str, "where branchno = ? " );
	strcat( str, "and lastchangedatetime < " );
	strcat( str, cStartText );
	strcat( str, " for update " );

	exec sql prepare del_ibtbrancharticleconfig from :str;
	ERROR_MSG( "prepare del_ibtbrancharticleconfig" )
	exec sql declare Cdelibtbrancharticleconfig cursor with hold for del_ibtbrancharticleconfig;

	strcpy( str, "delete from ibtbrancharticleconfig " );
	strcat( str, "where current of Cdelibtbrancharticleconfig " );
	
	exec sql prepare delete_ibtbrancharticleconfig from :str;
	ERROR_MSG( "prepare delete_ibtbrancharticleconfig" )

	exec sql open Cdelibtbrancharticleconfig using :sBranchno;
    ERROR_MSG( "open Cdelibtbrancharticleconfig" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}

		exec sql fetch Cdelibtbrancharticleconfig;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Cdelibtbrancharticleconfig" )

		exec sql execute delete_ibtbrancharticleconfig;
		ERROR_MSG( "execute delete_ibtbrancharticleconfig" )
		zaehlerDel++;

/*		exec sql delete from ibtbrancharticleconfig
			where branchno = :sBranchno
			and lastchangedatetime between datetime(:cStart) year to minute and datetime(:cStop) year to minute;
*/
	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close Cdelibtbrancharticleconfig;
    ERROR_MSG( "close Cdelibtbrancharticleconfig" )

	return OK;      
}

/*** PREPARE-LESE-IBTBRANCHARTICLE ************************************************/

int PrepareReadIBTBranchArticle( char *error_msg )
{
	char *fun = "PrepareReadIBTBranchArticle";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "articleno, " );
	strcat( str, "ibtroletypeid, " );
	strcat( str, "assortmenttypeid, " );
	strcat( str, "relevanceflag " );
	strcat( str, "from  " );
	strcat( str, indatenbank );
	strcat( str, ":puibtbrancharticleconfig " );
	strcat( str, "where branchno = ? " );

	exec sql prepare dec_puibtbrancharticleconfig from :str;
	ERROR_MSG( "prepare dec_puibtbrancharticleconfig" )
	exec sql declare Cselpuibtbrancharticleconfig cursor with hold for dec_puibtbrancharticleconfig;
	
	return OK;      
}

/*** PREPARE-LADE-IBTBRANCHARTICLE ************************************************/

int PrepareLoadingIBTBranchArticle( char *error_msg )
{
	char *fun = "PrepareLoadingIBTBranchArticle";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "select 1 from ibtbrancharticleconfig where " );
	strcat( str,"ARTICLENO=? and ");
	strcat( str,"BRANCHNO=? and ");
	strcat( str,"IBTTYPEID=? ");
	strcat( str,"for update " );
	   
	exec sql prepare sel_ibtbrancharticleconfig from :str;
	ERROR_MSG( "prepare sel_ibtbrancharticleconfig" )
	exec sql declare CSelibtbrancharticleconfig cursor with hold for sel_ibtbrancharticleconfig;

	strcpy( str, "update ibtbrancharticleconfig " );
	strcat( str, "set lastchangedatetime = current " );
	strcat( str, ",ibtassortmenttypeid = ? " );
	strcat( str, "where current of CSelibtbrancharticleconfig " );
	
	exec sql prepare upd_ibtbrancharticleconfig from :str;
	ERROR_MSG( "prepare upd_ibtbrancharticleconfig" )

	strcpy(str, "insert into ibtbrancharticleconfig (" );
	strcat( str, "articleno, " );
	strcat( str, "branchno, " );
	strcat( str, "ibttypeid, " );
	strcat( str, "ibtassortmenttypeid, " );
	strcat( str, "lastchangedatetime " );
	strcat( str, ") values " );
	strcat( str, "( ?, ?, ?, ?, current) " );
	   
	exec sql prepare ins_ibtbrancharticleconfig from :str;
	ERROR_MSG( "prepare ins_ibtbrancharticleconfig" )

	return OK;      
}

/*** LADE-IBTBRANCHARTICLE ********************************************************/

int LoadIBTBranchArticle( char *error_msg )
{
	char *fun = "LoadIBTBranchArticle";

	exec sql open CSelibtbrancharticleconfig
		using
		:a.ARTICLENO,
		:sBranchno,
		:a.IBTROLETYPEID
		;
    ERROR_MSG( "open CSelibtbrancharticleconfig" )

	exec sql fetch CSelibtbrancharticleconfig;
	ERROR_MSG( "fetch CSelibtbrancharticleconfig" )
	if ( sqlca.sqlcode == 100 )
	{
		EXEC SQL EXECUTE ins_ibtbrancharticleconfig
			using
			:a.ARTICLENO,
			:sBranchno,
			:a.IBTROLETYPEID,
			:a.ASSORTMENTTYPEID
			;
		ERROR_MSG( "execute ins_ibtbrancharticleconfig" )
		zaehlerIns++;
	}
	else
	{
		exec sql execute upd_ibtbrancharticleconfig using :a.ASSORTMENTTYPEID;
		ERROR_MSG( "execute upd_ibtbrancharticleconfig" )
		zaehlerUpd++;
	}

	return OK;
}

/***** AFTER-LADE-IBTBRANCHARTICLE *********************************************/

int AfterLoadingIBTBranchArticle( char *error_msg )
{
	int  rc = OK;
	if ( ( rc = DeteteIBTBranchArticle( error_msg ) ) != 0 ) return rc;
	return OK;
}


/***** LOAD WAFOTYP from ZDP configs ******************************************/

int LadeArtikelLokalWafoTyp(char* error_msg)
{
	int  rc = OK;

	if (strlen(countrycode) < 2)
	{
		sprintf(error_msg, "LadeArtikelLokalWafoTyp - missing or wrong country code <%s> !!!", countrycode);
		rc = ERROR;
	}
	else if ((strcmp(countrycode, "de") == 0) || (strcmp(countrycode, "DE") == 0))
	{
		rc = UpdateArticleLocalFromSubsequentDelivery( error_msg );
	}
	else if ((strcmp(countrycode, "at") == 0) || (strcmp(countrycode, "AT") == 0))
	{
		rc = UpdateArticleLocalFromZArticleAustria( error_msg );
	}
	else if ((strcmp(countrycode, "fr") == 0) || (strcmp(countrycode, "FR") != 0))
	{
		rc = UpdateArticleLocalFromZArticleFrance(error_msg);
	}
	else if ((strcmp(countrycode, "ch") != 0 && (strcmp(countrycode, "CH") != 0)))
	{
		// for switzerland the host import will remain in tpllokalart
		rc = UpdateArticleLocalNotUsed( error_msg );
	}
	
	return rc;
}

/***** DE Update csc artikellokal wafotyp from cdm csubsequentbrancharticleconfig.subsequentdelivery ********/

int UpdateArticleLocalFromSubsequentDelivery( char* error_msg )
{
	char* fun = "UpdateArticleLocalFromSubsequentDelivery";
	int i = 0; 

	char  msg[500];

	sprintf(msg, "Start specific Germany Transfer (csubsequentdeliverybrancharticleconfig.subsequentdelivery -> artikellokal.wafo_typ) for branch %d", sBranchno);
	PrintMsg(fun, msg, HINW, 0);

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "select artikel_nr from artikellokal ");
	strcat(str, "where filialnr = ? ");
	strcat(str, "  and artikel_nr in ( select articleno from ");
	strcat(str, indatenbank);
	strcat(str, ":csubsequentdeliverybrancharticleconfig ");
	strcat(str, "    where branchno = ? )");
	strcat(str, " for update");

	exec sql prepare sel_articlelocal_sd from : str;
	ERROR_MSG("prepare sel_articllelocal_sd")
	exec sql declare CselArticleLocalSD cursor with hold for sel_articlelocal_sd;

	strcpy(str, "update artikellokal");
	strcat(str, "   set wafotyp = (select case");
	strcat(str, "                         when subsequentdelivery = 0 then '0' ");
	strcat(str, "                         when subsequentdelivery = 1 then '1' ");
	strcat(str, "                         when subsequentdelivery = 8 then '1' ");
	strcat(str, "                         when subsequentdelivery = 9 then '0' ");
	strcat(str, "                         else '0' ");
	strcat(str, "                         end ");
	strcat(str, " from ");
	strcat(str, indatenbank);
	strcat(str, ":csubsequentdeliverybrancharticleconfig ");
	strcat(str, "    where branchno = filialnr ");
	strcat(str, "      and articleno = artikel_nr ) ");
	strcat(str, "where current of CselArticleLocalSD ");

	exec sql prepare update_articlelocal_sd from : str;
	ERROR_MSG("prepare update_articlelocal_sd")

	exec sql open CselArticleLocalSD using :sBranchno, :sBranchno;
	ERROR_MSG("open CselArticleLocalSD")

	EXEC SQL begin work;
	ERROR_MSG("Begin Work0:")

	for (i = 1;;i++)
	{
		if (i % 50 == 0)
		{
			exec sql commit work;
			ERROR_MSG("Commit Work:")
			exec sql begin work;
			ERROR_MSG("begin Work:")
		}

		exec sql fetch CselArticleLocalSD;
		if (sqlca.sqlcode == 100) break;
		ERROR_MSG("fetch CselArticleLocalSD")

		exec sql execute update_articlelocal_sd;
		ERROR_MSG("execute update_articlelocal_sd")
		zaehlerUpdWafo++;
	}

	EXEC SQL commit work;
	ERROR_MSG("Commit Work0:")

	exec sql close CselArticleLocalSD;
	ERROR_MSG("close CselArticleLocalSD")

	return OK;
}


/***** AT Update csc artikellokal wafotyp from cdm zartaustria.nachlieferung ********/

int UpdateArticleLocalFromZArticleAustria(char* error_msg)
{
	char* fun = "UpdateArticleLocalFromZArticleAustria";
	int i = 0;

	char  msg[500];

	sprintf(msg, "Start specific Austria Transfer (zartaustria.nachlieferung -> artikellokal.wafo_typ) for branch %d", sBranchno);
	PrintMsg(fun, msg, HINW, 0);

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "select artikel_nr from artikellokal ");
	strcat(str, "where filialnr = ? ");
	strcat(str, "  and artikel_nr in ( select artikel_nr from ");
	strcat(str, indatenbank);
	strcat(str, ":zartaustria )");
	strcat(str, " for update");

	exec sql prepare sel_articlelocal_za from : str;
	ERROR_MSG("prepare sel_articlelocal_za")
	exec sql declare CselArticleLocalZA cursor with hold for sel_articlelocal_za;

	strcpy(str, "update artikellokal a");
	strcat(str, "   set wafotyp = ( select nachlieferung from ");
	strcat(str, indatenbank);
	strcat(str, ":zartaustria z");
	strcat(str, "    where z.artikel_nr = a.artikel_nr )");
	strcat(str, "where current of CselArticleLocalZA ");

	exec sql prepare update_articlelocal_za from : str;
	ERROR_MSG("prepare update_articlelocal_za")

	exec sql open CselArticleLocalZA using :sBranchno;
	ERROR_MSG("open CselArticleLocalZA")

	EXEC SQL begin work;
	ERROR_MSG("Begin Work0:")

	for (i = 1;;i++)
	{
		if (i % 50 == 0)
		{
			exec sql commit work;
			ERROR_MSG("Commit Work:")
			exec sql begin work;
			ERROR_MSG("begin Work:")
		}

		exec sql fetch CselArticleLocalZA;
		if (sqlca.sqlcode == 100) break;
		ERROR_MSG("fetch CselArticleLocalZA")

		exec sql execute update_articlelocal_za;
		ERROR_MSG("execute update_articlelocal_za")
			zaehlerUpdWafo++;
	}

	EXEC SQL commit work;
	ERROR_MSG("Commit Work0:")

	exec sql close CselArticleLocalZA;
	ERROR_MSG("close CselArticleLocalZA")

	return OK;
}

/***** FR Update csc artikellokal wafotyp from cdm zartfrance.nachlieferung ********/
int UpdateArticleLocalFromZArticleFrance(char* error_msg)
{
	char* fun = "UpdateArticleLocalFromZArticleFrance";
	int i = 0;
	char  msg[500];

	sprintf(msg, "Start specific France Transfer (zartfrance.nachlieferung -> artikellokal.wafo_typ) for branch %d", sBranchno);
	PrintMsg(fun, msg, HINW, 0);

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "select artikel_nr from artikellokal ");
	strcat(str, "where filialnr = ? ");
	strcat(str, "  and artikel_nr in ( select articleno from ");
	strcat(str, indatenbank);
	strcat(str, ":zartfrance )");
	strcat(str, " for update");

	exec sql prepare sel_articlelocal_zaf from : str;
	ERROR_MSG("prepare sel_articlelocal_zaf")
	exec sql declare CselArticleLocalZAF cursor with hold for sel_articlelocal_zaf;

	strcpy(str, "update artikellokal a");
	strcat(str, "   set a.wafotyp = NVL(( select z.nachlieferung from ");
	strcat(str, indatenbank);
	strcat(str, ":zartfrance z");
	strcat(str, "    where z.articleno = a.artikel_nr ),'0') ");
	strcat(str, "where current of CselArticleLocalZAF ");

	exec sql prepare update_articlelocal_zaf from : str;
	ERROR_MSG("prepare update_articlelocal_zaf")

	exec sql open CselArticleLocalZAF using :sBranchno;
	ERROR_MSG("open CselArticleLocalZAF")

	EXEC SQL begin work;
	ERROR_MSG("Begin Work0:")

	for (i = 1;; i++)
	{
		if (i % 50 == 0)
		{
			exec sql commit work;
			ERROR_MSG("Commit Work:")
				exec sql begin work;
			ERROR_MSG("begin Work:")
		}

		exec sql fetch CselArticleLocalZAF;
		if (sqlca.sqlcode == 100) break;
		ERROR_MSG("fetch CselArticleLocalZAF")

		exec sql execute update_articlelocal_zaf;
		ERROR_MSG("execute update_articlelocal_zaf")
		zaehlerUpdWafo++;
	}

	EXEC SQL commit work;
	ERROR_MSG("Commit Work0:")

	exec sql close CselArticleLocalZAF;
	ERROR_MSG("close CselArticleLocalZAF")

	return OK;
}

/***** CH Update csc artikellokal wafotyp = '0' *****/
int UpdateArticleLocalNotUsed(char* error_msg)
{
	char* fun = "UpdateArticleLocalNotUsed";
	int i = 0;

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "select artikel_nr from artikellokal ");
	strcat(str, "where filialnr = ? ");
	strcat(str, " for update");

	exec sql prepare sel_articlelocal_nu from : str;
	ERROR_MSG("prepare sel_articlelocal_nu")
	exec sql declare CselArticleLocalNU cursor with hold for sel_articlelocal_nu;

	strcpy(str, "update artikellokal a");
	strcat(str, "   set wafotyp = '0'");
	strcat(str, "where current of CselArticleLocalNU ");

	exec sql prepare update_articlelocal_nu from : str;
	ERROR_MSG("prepare update_articlelocal_nu")

	exec sql open CselArticleLocalNU using :sBranchno;
	ERROR_MSG("open CselArticleLocalNU")

	EXEC SQL begin work;
	ERROR_MSG("Begin Work0:")

	for (i = 1;;i++)
	{
		if (i % 50 == 0)
		{
			exec sql commit work;
			ERROR_MSG("Commit Work:")
			exec sql begin work;
			ERROR_MSG("begin Work:")
		}

		exec sql fetch CselArticleLocalNU;
		if (sqlca.sqlcode == 100) break;
		ERROR_MSG("fetch CselArticleLocalNU")

		exec sql execute update_articlelocal_nu;
		ERROR_MSG("execute update_articlelocal_nu")
		zaehlerUpdWafo++;
	}

	EXEC SQL commit work;
	ERROR_MSG("Commit Work0:")

	exec sql close CselArticleLocalNU;
	ERROR_MSG("close CselArticleLocalNU")

	return OK;
}

/***** PRINT-MSG ************************************************************/

void PrintMsg( char *fun, char *error_msg, char mld, int rc )
{
	FILE *fp;
	struct tm *localtime();
	struct tm *zeit;
	long hour1;
	pid_t pid;
	long time();
	char logFile[L_TEXT];
    char *env;
 
	if ( rc > INSERT )
		return;
   
	pid = getpid();
	hour1 = time( &hour1 );
	zeit  = localtime( &hour1 );
   
/*	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) );	*/
	env = getenv( "LOG_PATH" );
	if ( env == NULL )
		env = ".";
	sprintf( logFile, "%s/loadbrancharticleconfig.log", env );

	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
		return;
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.14s %s %s\n",
		mld,
		99,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		PROJECTNAME,
		fun,
		error_msg );

	fclose(fp);
}

/***** CLOSE-DATABASE *******************************************************/

int CloseDatabase( void )
{
	char error_msg[L_TEXT];
	char *fun = "CloseDatabase";

	exec sql close database;
	ERROR_MSG( "Close DB" )
  
	return OK;
}
/***** ENDE *****************************************************************/

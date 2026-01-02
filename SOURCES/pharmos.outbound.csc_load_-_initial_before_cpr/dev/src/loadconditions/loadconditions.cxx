/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadconditions"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/*****************************************************************************/
/* Einfuegen neuer Tabellen in das Artikelladeprogramm                       */
/*****************************************************************************/
/* 1 Tabelle im Incudefile definieren und ANZ_TABELLEN aktualisieren         */
/* 2 Eintrag in Funktion SetzeSchalterTabelle erzeugen                       */
/* 3 Implementierung und Aufruf der Initialisierungsfunktion (create table..)*/
/* 4 Implementierung und Aufruf der Ladefunktionfunktion (in Bezug auf DKART)*/
/* 5 Implementierung und Aufruf der Endefunktion (drop/create index, rename )*/
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "lddiscount.h"
#include "zdiscount.h"
#include "pplib/allg.h"
#include "customersurcharge.h"
#include <dirent.h>                                     
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>
#include "callplanmaintenance.h"
#include "libtpld/dadedb.h"

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
int explain = NO;
int sichern = NO;
int zaehlerIns = 0;     /* weil ich zu faul war alex */
int zaehlerUpd = 0;     /* weil ich zu faul war alex */
int zaehlerInsSur = 0;  /* weil ich zu faul war alex */
int zaehlerUpdSur = 0;  /* weil ich zu faul war alex */
long datum = 0;
mcallplanloadS srvLoad;
tError stError;

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
struct N_ZDISCOUNT a;
short sBranchno = 0;
long lDatum;
long lDatumbis;
char updsign[2];
long lArticleNo;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo( char *error_msg, char mld, int rc );
int StarteLadenKonditionen    ( char *error_msg);
int PrepareLoadTables         ( char *error_msg);
int SetNotUpdated             ( char *error_msg);
int DelNotUpdated             ( char *error_msg);
int SetNotUpdatedSur          ( char *error_msg);
int DelNotUpdatedSur          ( char *error_msg);
int LoadTables                ( char *error_msg);
int AfterLoadTables           ( char *error_msg);
int PrepareLadeKonditionen    ( char *error_msg);
int PrepareLeseKonditionen    ( char *error_msg);
int PrepareLadeSur            ( char *error_msg);
int LeseKonditionen           ( char *error_msg);
int LadeKonditionen           ( char *error_msg);
int LadeSur                   ( char *error_msg);
int AfterLadeKonditionen      ( char *error_msg);
int CloseDatabase( void );

/***** MAIN *****************************************************************/

int main( int argc, char **argv  )
{
	char  error_msg[181];
	char  *schalter;
	int   i;
	char  *fun = "Main";
	char  *LOG_FILE = "wws.log";
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
		else if ( !strcmp( schalter, "-vz" ) )
		{
			strcat(start_msg, " -vz");
			i++;
			sBranchno = atoi(argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-ex" ) )
		{
			strcat(start_msg, " -ex");
			explain = YES;
		}
		else if ( !strcmp( schalter, "-ld" ) )
		{
			strcat(start_msg, " -ld");
			i++;
			datum = atol(argv[i]);
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
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
				" { -vz filialnr }\n\t"
				" [ -ld 19970314]\n\t"
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

	if( datum == 0 )
	{
/*		srvLoad.VERTRIEBSZENTRUMNR = sBranchno;
		srvLoad.LADEDATUM = 0;
		srvLoad.LADEKIPPZEIT = 120000;
		if ( Mcallplanload_GetInitializeData( &srvLoad, &stError, FALSE ) == IS_ERROR )
		{
			return CheckSql( fun, &stError, "%s", stError.spError );
		}
        datum = srvLoad.LADEDATUM; */
		datum = AllgGetDate();
	}
/*	lDatum = datum; */
	lDatumbis = datum;
	lDatum = AllgAddDate(datum,1,error_msg);
	PrintMsg( fun, start_msg, HINW, 0 );
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	if ( ( rc = StarteLadenKonditionen( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	sprintf(start_msg,"Discount geaendert: %d eingefuegt: %d ",zaehlerUpd,zaehlerIns);
	sprintf(start_msg,"CustomerSurcharge geaendert: %d eingefuegt: %d ",zaehlerUpdSur,zaehlerInsSur);
	PrintMsg( fun, start_msg, HINW, 0 );
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER ARTIKEL-KKONDITIONEN ************************************/

int StarteLadenKonditionen( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenKonditionen";
   
	exec sql open Cselzdiscount using :lDatum,:lDatumbis;

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	for ( ;; )
	{
		exec sql fetch Cselzdiscount into :a;
		ERROR_MSG( "fetch Cselzdiscount" )
		if(NOTFOUND) break;
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }

		if (a.DISCOUNTSPEC == 11)
		{
			if ( ( rc = LadeSur( error_msg ) ) < 0 )
	        {
				PrintMsg( fun, error_msg, FEHL, ERROR );
				return ERROR;
			}
		}
        else if ( ( rc = LoadTables( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
        else if ( explain == YES )
           if ( zaehler > 5000 ) break;   /* Nur 5000 Saetze verarbeiten */

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	sprintf( error_msg, "%d Saetze geladen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );

	printf("loadconditions: %d Saetze geladen\n", zaehler);
	fflush(stdout);

	if ( explain == YES ) return OK;
	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;
	if ( ( rc = SetNotUpdated( error_msg ) ) < 0 ) return rc;
	if ( ( rc = SetNotUpdatedSur( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLeseKonditionen( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeKonditionen( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeSur( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *error_msg)
{
	char *fun = "LoadTables";
	int rc = OK;

	rc = LadeKonditionen(error_msg);

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = DelNotUpdated( error_msg ) ) < 0 ) return rc;
	if ( (rc = DelNotUpdatedSur( error_msg ) ) < 0 ) return rc;
	if ( (rc = AfterLadeKonditionen(error_msg)) < 0) return rc;

	return OK;
}

/*** KENNZEICHNEN-KONDITIONEN ************************************************/

int SetNotUpdated( char *error_msg )
{
	char *fun = "SetNotUpdated";
	int i;

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "articleno " );
	strcat( str, "from " );
	strcat( str, "discount " );
	strcat( str, "where branchno = ? " );
	strcat( str, "for update " );

	exec sql prepare set_notupdated from :str;
	ERROR_MSG( "prepare set_notupdated" )
	exec sql declare Csetnotupdated cursor with hold for set_notupdated;

	strcpy( str, "update discount " );
	strcat( str, "set updatesign = '0' " );
	strcat( str, "where current of Csetnotupdated " );
	
	exec sql prepare upd_notupdated from :str;
	ERROR_MSG( "prepare upd_notupdated" )

/*	strcpy( str, "update artikellokal " );
	strcat( str, "set moreconditions = \"0\" " );
	strcat( str, "where filialnr = ? " );
	strcat( str, "and artikel_nr = ? " );
	   
	exec sql prepare upd_lokal0 from :str;
	ERROR_MSG( "prepare upd_lokal0" )
*/

	exec sql open Csetnotupdated using :sBranchno;
    ERROR_MSG( "open Csetnotupdated" )
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
		exec sql fetch Csetnotupdated into :lArticleNo;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Csetnotupdated" )

/*		if(lArticleNo > 0)
		{
			EXEC SQL EXECUTE upd_lokal0
				using
				:sBranchno,
				:lArticleNo;
			ERROR_MSG( "execute upd_lokal0" ) 
		}
 */ 
		exec sql execute upd_notupdated;
		ERROR_MSG( "execute upd_notupdated" )

	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close Csetnotupdated;
    ERROR_MSG( "close Csetnotupdated" )

	return OK;      
}

/*** KENNZEICHNEN-SURCHARGE ************************************************/

int SetNotUpdatedSur( char *error_msg )
{
	char *fun = "SetNotUpdatedSur";
	int i;

	exec sql begin declare section;
	char str[2048];
	long customerno;
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "customerno " );
	strcat( str, "from " );
	strcat( str, "customersurcharge " );
	strcat( str, "where branchno = ? " );
	strcat( str, "for update " );

	exec sql prepare set_notupdatedsur from :str;
	ERROR_MSG( "prepare set_notupdatedsur" )
	exec sql declare Csetnotupdatedsur cursor with hold for set_notupdatedsur;

	strcpy( str, "update customersurcharge " );
	strcat( str, "set updatesign = '0' " );
	strcat( str, "where current of Csetnotupdatedsur " );
	
	exec sql prepare upd_notupdatedsur from :str;
	ERROR_MSG( "prepare upd_notupdatedsur" )

	exec sql open Csetnotupdatedsur using :sBranchno;
    ERROR_MSG( "open Csetnotupdatedsur" )
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
		exec sql fetch Csetnotupdatedsur into :customerno;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Csetnotupdatedsur" )

		exec sql execute upd_notupdatedsur;
		ERROR_MSG( "execute upd_notupdatedsur" )

	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close Csetnotupdatedsur;
    ERROR_MSG( "close Csetnotupdatedsur" )

	return OK;      
}

/*** LOESCHEN-KONDITIONEN ************************************************/

int DelNotUpdated( char *error_msg )
{
	char *fun = "DelNotUpdated";
	int i;

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "articleno  " );
	strcat( str, "from " );
	strcat( str, "discount " );
	strcat( str, "where branchno = ? " );
	strcat( str, "and updatesign = '0' " );
	strcat( str, "for update " );

	exec sql prepare del_notupdated from :str;
	ERROR_MSG( "prepare del_notupdated" )
	exec sql declare Cdelnotupdated cursor with hold for del_notupdated;

	strcpy( str, "delete from discount " );
	strcat( str, "where current of Cdelnotupdated " );
	
	exec sql prepare delete_discount from :str;
	ERROR_MSG( "prepare delete_discount" )

	exec sql open Cdelnotupdated using :sBranchno;
    ERROR_MSG( "open Cdelnotupdated" )
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
		exec sql fetch Cdelnotupdated into :lArticleNo;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Cdelnotupdated" )

		exec sql execute delete_discount;
		ERROR_MSG( "execute delete_discount" )

	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close Cdelnotupdated;
    ERROR_MSG( "close Csetnotupdated" )

	return OK;      
}

/*** LOESCHEN-SURCHARGE ************************************************/

int DelNotUpdatedSur( char *error_msg )
{
	char *fun = "DelNotUpdatedSur";
	int i;

	exec sql begin declare section;
	char str[2048];
	long customerno;
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "customerno  " );
	strcat( str, "from " );
	strcat( str, "customersurcharge " );
	strcat( str, "where branchno = ? " );
	strcat( str, "and updatesign = '0' " );
	strcat( str, "for update " );

	exec sql prepare del_notupdatedsur from :str;
	ERROR_MSG( "prepare del_notupdatedsur" )
	exec sql declare Cdelnotupdatedsur cursor with hold for del_notupdatedsur;

	strcpy( str, "delete from customersurcharge " );
	strcat( str, "where current of Cdelnotupdatedsur " );
	
	exec sql prepare delete_sur from :str;
	ERROR_MSG( "prepare delete_sur" )

	exec sql open Cdelnotupdatedsur using :sBranchno;
    ERROR_MSG( "open Cdelnotupdatedsur" )
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
		exec sql fetch Cdelnotupdatedsur into :customerno;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Cdelnotupdatedsur" )

		exec sql execute delete_sur;
		ERROR_MSG( "execute delete_sur" )

	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close Cdelnotupdatedsur;
    ERROR_MSG( "close Csetnotupdatedsur" )

	return OK;      
}

/*** PREPARE-LESE-KONDITIONEN ************************************************/

int PrepareLeseKonditionen( char *error_msg )
{
	char *fun = "PrepareLeseKonditionen";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, ZDISCOUNT_PELISTE );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":cdiscount " );
	strcat( str, "where datefrom <= ? " );
	strcat( str, "and dateto >= ? " );

	exec sql prepare dec_zdiscount from :str;
	ERROR_MSG( "prepare dec_zdiscount" )
	exec sql declare Cselzdiscount cursor with hold for dec_zdiscount;
	
	return OK;      
}

/*** PREPARE-LADE-KONDITIONEN ************************************************/

int PrepareLadeKonditionen( char *error_msg )
{
	char *fun = "PrepareLadeKonditionen";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "select updatesign from discount where ");
	strcat( str,"BRANCHNO=? and ");
	strcat( str,"ARTICLENO=? and ");
	strcat( str,"DISCOUNTGRPNO=? and ");
	strcat( str,"PHARMACYGROUPID=? and ");
	strcat( str,"CUSTOMERNO=? and ");
	strcat( str,"BASEQTY=? and ");
	strcat( str,"DATEFROM=? and ");
	strcat( str,"DATETO=? and ");
	strcat( str,"GRPDISCOUNTTYP=? and ");
	strcat( str,"DISCOUNTTYPE=? and ");
	strcat( str,"DISCOUNTSPEC=? and ");
	strcat( str,"BASE_VALUE=? and ");
	strcat( str,"BASE_MULT_STD_QTY=? and ");
	strcat( str,"MANUFACTURERNO=? and ");
	strcat( str,"ARTCATEGORYNO=? and ");
	strcat( str,"PAYMENTTARGETNO=? ");
	strcat(str, "for update ");
	
	exec sql prepare sel_discount from :str;
	ERROR_MSG( "prepare sel_discount" )
	exec sql declare CSeldiscount cursor with hold for sel_discount;

	strcpy( str, "update discount " );
	strcat(str, "set updatesign = '1'");
	strcat(str, ",DISCOUNTQTY=? ");
	strcat(str, ",DISCOUNTVALUEPCT=? ");
	strcat(str, ",DISCOUNTQTYPCT=? ");
	strcat(str, ",SURCHARGEPCT=? ");
	strcat(str, ",PHARMGRPEXCLUDED=? ");
	strcat(str, ",FIXEDPRICE=? ");
	strcat(str, ",REFUNDPCT=? ");
	strcat(str, ",INTERNALDISCOUNT=? ");
	strcat(str, ",DISCOUNTARTICLE=? ");
	strcat(str, ",PHARMGRPEXCL_2=? ");
	strcat(str, ",PHARMGRPEXCL_3=? ");
	strcat(str, ",NO_MULTIPLE_QTY=? ");
	strcat(str, ",FIXEDDISCOUNTVALUE=? ");
	strcat(str, ",GROSSPROFITPCT=? ");
	strcat(str, ",ADDONDISCOUNTOK=? ");
	strcat(str, ",PAYMENTTERMTYPE=? ");
	strcat(str, ",TARGETQTY=? ");
	strcat(str, ",EXCEEDANCEPCT=? ");
	strcat(str, ",REFUNDTYPE=? ");
	strcat(str, ",ARTICLE_NO_PACK=? ");
	strcat(str, ",REFUNDVALUE=? ");
	strcat(str, ",PROMOTION_NO=? ");
	strcat(str, ",MAXQTY=? ");
	strcat(str, ",TURNOVERCALCIMPACT=? ");
	strcat(str, ",ADDONDISCOUNT=? ");
	strcat(str, ",MONTHLYDISCOUNT=? ");
	strcat(str, ",DISCOUNTCALCFROM=? ");
	strcat(str, ",DISCOUNTAPPLYTO=? ");
	strcat(str, "where current of CSeldiscount " );
	
	exec sql prepare upd_discount from :str;
	ERROR_MSG( "prepare upd_discount" )

	strcpy(str, "insert into discount (" );
	strcat( str, LDDISCOUNT_PELISTE );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, " );
	strcat( str, "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, " );
	strcat( str, "'1', ?, ?, ?, ?, ?, ?, ?, ?, ?, " );
	strcat( str, "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?  )" );
	   
	exec sql prepare ins_discount from :str;
	ERROR_MSG( "prepare ins_discount" )

/*	strcpy( str, "update artikellokal " );
	strcat( str, "set moreconditions = \"1\" " );
	strcat( str, "where filialnr = ? " );
	strcat( str, "and artikel_nr = ? " );
	   
	exec sql prepare upd_lokal from :str;
	ERROR_MSG( "prepare upd_lokal" )
*/
	return OK;      
}

/*** PREPARE-LADE-SURCHARGE ************************************************/

int PrepareLadeSur( char *error_msg )
{
	char *fun = "PrepareLadeSur";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "select updatesign from customersurcharge where " );
	strcat( str,"BRANCHNO=? and ");
	strcat( str,"CUSTOMERNO=? and ");
	strcat( str,"MANUFACTURERNO=? ");
	strcat( str,"for update " );
	   
	exec sql prepare sel_sur from :str;
	ERROR_MSG( "prepare sel_sur" )
	exec sql declare CSelsur cursor with hold for sel_sur;

	strcpy( str, "update customersurcharge " );
	strcat( str, "set updatesign = '1' " );
	strcat( str, ",surchargepct = ? " );
	strcat( str, "where current of CSelsur " );
	
	exec sql prepare upd_sur from :str;
	ERROR_MSG( "prepare upd_sur" )

	strcpy(str, "insert into customersurcharge (" );
	strcat( str, CUSTOMERSURCHARGE_PELISTE );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, '1' ) " );
	   
	exec sql prepare ins_sur from :str;
	ERROR_MSG( "prepare ins_sur" )

	return OK;      
}

/*** LADE-KONDITIONEN ********************************************************/

int LadeKonditionen( char *error_msg )
{
	char *fun = "LadeKonditionen";

	exec sql open CSeldiscount
		using
		:sBranchno,
		:a.ARTICLENO,
		:a.DISCOUNTGRPNO,
		:a.PHARMACYGROUPID,
		:a.CUSTOMERNO,
		:a.BASEQTY,
		:a.DATEFROM,
		:a.DATETO,
		:a.GRPDISCOUNTTYP,
		:a.DISCOUNTTYPE,
		:a.DISCOUNTSPEC,
		:a.BASE_VALUE,
		:a.BASE_MULT_STD_QTY,
        :a.MANUFACTURERNO,
        :a.ARTCATEGORYNO,
        :a.PAYMENTTARGETNO
		;
    ERROR_MSG( "open CSeldiscount" )

	exec sql fetch CSeldiscount into :updsign;
	ERROR_MSG( "fetch CSeldiscount" )
	if ( sqlca.sqlcode == 100 )
	{
		EXEC SQL EXECUTE ins_discount
			using
			:sBranchno,
			:a.ARTICLENO,
			:a.DISCOUNTGRPNO,
			:a.PHARMACYGROUPID,
			:a.CUSTOMERNO,
			:a.GRPDISCOUNTTYP,
			:a.DATEFROM,
			:a.DATETO,
			:a.BASEQTY,
			:a.DISCOUNTSPEC,
			:a.DISCOUNTTYPE,
			:a.DISCOUNTQTY,
			:a.DISCOUNTVALUEPCT,
			:a.DISCOUNTQTYPCT,
			:a.SURCHARGEPCT,
			:a.PHARMGRPEXCLUDED,
			:a.FIXEDPRICE,
			:a.REFUNDPCT,
			:a.INTERNALDISCOUNT,
			:a.DISCOUNTARTICLE,
			:a.PHARMGRPEXCL_2,
			:a.PHARMGRPEXCL_3,
			:a.BASE_VALUE,
			:a.BASE_MULT_STD_QTY,
			:a.NO_MULTIPLE_QTY,
	        :a.FIXEDDISCOUNTVALUE,
	        :a.MANUFACTURERNO,
			:a.ARTCATEGORYNO,
		    :a.PAYMENTTARGETNO,
	        :a.GROSSPROFITPCT,
	        :a.ADDONDISCOUNTOK,
	        :a.PAYMENTTERMTYPE,
	        :a.TARGETQTY,
			:a.EXCEEDANCEPCT,
	        :a.REFUNDTYPE,
	        :a.ARTICLE_NO_PACK,
	        :a.REFUNDVALUE,
	        :a.PROMOTION_NO,
	        :a.MAXQTY,
	        :a.TURNOVERCALCIMPACT,
	        :a.ADDONDISCOUNT,
			:a.MONTHLYDISCOUNT,
			:a.DISCOUNTCALCFROM,
			:a.DISCOUNTAPPLYTO
			;
		ERROR_MSG( "execute ins_discount" )
		zaehlerIns++;
	}
	else
	{
		exec sql execute upd_discount
			using
			: a.DISCOUNTQTY,
			: a.DISCOUNTVALUEPCT,
			: a.DISCOUNTQTYPCT,
			: a.SURCHARGEPCT,
			: a.PHARMGRPEXCLUDED,
			: a.FIXEDPRICE,
			: a.REFUNDPCT,
			: a.INTERNALDISCOUNT,
			: a.DISCOUNTARTICLE,
			: a.PHARMGRPEXCL_2,
			: a.PHARMGRPEXCL_3,
			: a.NO_MULTIPLE_QTY,
			: a.FIXEDDISCOUNTVALUE,
			: a.GROSSPROFITPCT,
			: a.ADDONDISCOUNTOK,
			: a.PAYMENTTERMTYPE,
			: a.TARGETQTY,
			: a.EXCEEDANCEPCT,
			: a.REFUNDTYPE,
			: a.ARTICLE_NO_PACK,
			: a.REFUNDVALUE,
			: a.PROMOTION_NO,
			: a.MAXQTY,
			: a.TURNOVERCALCIMPACT,
			: a.ADDONDISCOUNT,
			: a.MONTHLYDISCOUNT,
			: a.DISCOUNTCALCFROM,
			: a.DISCOUNTAPPLYTO
			;
		ERROR_MSG( "execute upd_discount" )
		zaehlerUpd++;
	}

/*	if(a.ARTICLENO > 0)
	{
		EXEC SQL EXECUTE upd_lokal
			using
			:sBranchno,
			:a.ARTICLENO;
		ERROR_MSG( "execute upd_lokal" ) 
	}
 */ 
	return OK;
}

/*** LADE-SURCHARGE ********************************************************/

int LadeSur( char *error_msg )
{
	char *fun = "LadeSur";

	exec sql open CSelsur
		using
		:sBranchno,
		:a.CUSTOMERNO,
        :a.MANUFACTURERNO
		;
    ERROR_MSG( "open CSelsur" )

	exec sql fetch CSelsur into :updsign;
	ERROR_MSG( "fetch CSelsur" )
	if ( sqlca.sqlcode == 100 )
	{
		EXEC SQL EXECUTE ins_sur
			using
			:sBranchno,
			:a.CUSTOMERNO,
	        :a.MANUFACTURERNO,
	        :a.SURCHARGEPCT
			;
		ERROR_MSG( "execute ins_sur" )
		zaehlerInsSur++;
	}
	else
	{
		exec sql execute upd_sur
			using
	        :a.SURCHARGEPCT
			;
		ERROR_MSG( "execute upd_sur" )
		zaehlerUpdSur++;
	}

	return OK;
}


/***** AFTER-LADE-KONDITIONEN *********************************************/

int AfterLadeKonditionen( char *error_msg )
{
	return OK;
}

/***** WriteLogInfo nur zum Aufruf von PrintMsg ******************************/

void WriteLogInfo( char *error_msg, char mld, int rc )
{
	PrintMsg( "callplanday", error_msg, mld, rc );
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
	sprintf( logFile, "%s/wws.log", env );

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
		"loadconditions",
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

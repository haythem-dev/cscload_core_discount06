/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadcucosrs"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "cucosserbia.h"
#include "discount.h"
#include <dirent.h>                                     
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>
#include "pplib/allg.h"

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                   sqlca.sqlcode, sqlca.sqlerrd[1],sqlca.sqlerrm ); \
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
#define DATABASE           "phosix"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 10                  /* nach n-saetzen commit  */

typedef struct nummer
{
	long artno;
	struct nummer *folgepos;
} sNummer;

sNummer *startpos;
sNummer *newpos;
sNummer *actpos;

char log_file [300 + 1];
char dateiname[L_TEXT];
int explain = NO;
int sichern = NO;
int zaehlerIns = 0;     /* weil ich zu faul war alex */
int iAnzTargets;
double fixpreis;

exec sql begin declare section;
char datenbank[60];
cucosserbiaS a;
discountS disc;
long lKundenNr;
long datum;
short sVz;
char cPayTerm[5];
char cEKG[4];
double preis;
long acttime;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo( char *error_msg, char mld, int rc );
int StarteLadenCucos		( char *error_msg);
int PrepareLoadTables		( char *error_msg);
int DelCucos				( char *error_msg);
int AfterLoadTables			( char *error_msg);
int PrepareDelCucos			( char *error_msg);
int PrepareLadeCucos		( char *error_msg);
int PrepareLeseCucos		( char *error_msg);
int AfterLadeCucos			( char *error_msg);
int LadePayTerms			( char *error_msg);
int LadeCucosGrp			( char *error_msg);
int LadeCucosHerst			( char *error_msg);
int LadeCucosDG				( short grptype,char *error_msg);
int LadeCucosHerst			( char *error_msg);
int LadeCucosCategory		( char *error_msg);
int LadeCucosSonder			( char *error_msg);
int LadeCucosCst			( char *error_msg);
int CloseDatabase			( void );
int GetSonder				( char *error_msg );
int WriteCucos				( char *error_msg );
int WriteCucosHerst			( char *error_msg );
int FillCucosPct			( char *error_msg );
void LoeRab					();

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
	time_t long_time;

	sprintf(datenbank,"%s",DATABASE);
     
	strcpy(start_msg, "gestartet mit:");
	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-db" ) )
		{
			strcat(start_msg, " -db");
			i++;
			sprintf( datenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-branchno" ) )
		{
			strcat(start_msg, " -branchno");
			i++;
			sVz = atoi( argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
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
				" { -db datenbankname <Datenbankname Eingabe> }\n\t"
				" [ -ex <Explain> ]\n\t",
				argv[0] );
			return 1;
		}
	}

	exec sql database :datenbank;
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

	datum = AllgGetDate();
	sprintf(start_msg,"%s Datum: %d",start_msg,datum);

	PrintMsg( fun, start_msg, HINW, 0 );
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	exec sql update parameter set wert = 0
		where filialnr = :sVz
		and programmname = "LOADCUCOS";
	ERROR_MSG( "update parameter: ");
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		exec sql insert into parameter (filialnr,wert,programmname)
			values (:sVz,0,"LOADCUCOS");
	    ERROR_MSG( "insert parameter: ");
	}

	if ( ( rc = StarteLadenCucos( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	sprintf(start_msg,"%d Satze geladen",zaehlerIns);
   
	time( &long_time );
	acttime = long_time;
	exec sql update parameter set wert = :acttime
		where filialnr = :sVz
		and programmname = "LOADCUCOS";
	ERROR_MSG( "update parameter: ");

	PrintMsg( fun, start_msg, HINW, 0 );
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER CUCOS ************************************/

int StarteLadenCucos( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenCucos";

	exec sql open CselKunde using :sVz;
	ERROR_MSG( "open CselKunde" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )
	startpos = NULL;

	for ( ;; )
	{
		if(startpos != NULL)
		{
			for(actpos = startpos;;)
			{
				newpos = actpos->folgepos;
				free(actpos);
				if(newpos == NULL) break;
				actpos = newpos;
			}
			startpos = NULL;
		}
		exec sql fetch CselKunde into :lKundenNr,:cPayTerm;
		ERROR_MSG( "fetch CselKunde" )
		if(NOTFOUND) break;

		exec sql execute ins_ekg using :sVz,:lKundenNr;
		ERROR_MSG( "execute ins_ekg" )
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }

        if ( ( rc = DelCucos( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
        if ( ( rc = LadePayTerms( error_msg ) ) < 0 )	/* Zahlungsziele */
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
		/* Cascade 0 */
		a.CASCADE = 0;
        if ( ( rc = LadeCucosSonder( error_msg ) ) < 0 )	/* Ocaasionen */
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
		LoeRab();
		/* Cascade 1 */
		a.CASCADE = 1;
        if ( ( rc = LadeCucosGrp( error_msg ) ) < 0 )	/* EKG */
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
		LoeRab();
		/* Cascade 2 */
		a.CASCADE = 2;
        if ( ( rc = LadeCucosDG( 1,error_msg ) ) < 0 )	/* Hersteller DiscountGroup */
//        if ( ( rc = LadeCucosHerstDG( error_msg ) ) < 0 )	/* Hersteller discountgrp */
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
		LoeRab();
		/* Cascade 3 */
		a.CASCADE = 3;
        if ( ( rc = LadeCucosHerst( error_msg ) ) < 0 )	/* Hersteller */
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
		LoeRab();
		/* Cascade 4 */
		a.CASCADE = 4;
        if ( ( rc = LadeCucosCategory( error_msg ) ) < 0 )	/* Artikelgruppe */
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
		LoeRab();
		/* Cascade 5 */
		a.CASCADE = 5;
        if ( ( rc = LadeCucosDG( 2,error_msg ) ) < 0 )	/* DiscountGroup */
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
		LoeRab();
		/* Cascade 6 */
		a.CASCADE = 6;
        if ( ( rc = LadeCucosCst( error_msg ) ) < 0 )	/* Kunde */
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}

		exec sql open Cdelekg;
		ERROR_MSG( "open Cdelekg" )

		for(;;)
		{
			exec sql fetch Cdelekg into :cEKG;
			ERROR_MSG( "fetch Cdelekg" )
			if(NOTFOUND) break;

			exec sql execute delete_ekg;
			ERROR_MSG( "execute delete_ekg" )
		}
		
	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	sprintf( error_msg, "%d Saetze geladen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );

	if ( explain == YES ) return OK;
	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;
	if ( ( rc = PrepareDelCucos( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLeseCucos( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeCucos( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** Zahlungsziele *********************************************************/

int LadePayTerms( char *error_msg)
{
	char *fun = "LadePayTerms";
	int i;

	exec sql begin declare section;
	short sTarget ;
	exec sql end declare section;

	a.BRANCHNO = sVz;
	a.CUSTOMERNO = lKundenNr;
	exec sql open CselPayterm using :cPayTerm;
	ERROR_MSG( "open CselPayterm" )

	for ( iAnzTargets = 0;; )
	{
		exec sql fetch CselPayterm into :sTarget;
		ERROR_MSG( "fetch CselPayterm" )
		if(NOTFOUND) break;
		iAnzTargets++;
		if(iAnzTargets == 1)
			a.PAYTERM1 = sTarget;
		else if(iAnzTargets == 2)
			a.PAYTERM2 = sTarget;
		else if(iAnzTargets == 3)
			a.PAYTERM3 = sTarget;
		else if(iAnzTargets == 4)
			a.PAYTERM4 = sTarget;
		else if(iAnzTargets == 5)
			a.PAYTERM5 = sTarget;
		else if(iAnzTargets == 6)
			a.PAYTERM6 = sTarget;
	}

	return OK;
}
 
/***** Kunde/EKG *********************************************************/

int LadeCucosGrp( char *error_msg)
{
	char *fun = "LadeCucosGrp";
	int rc;
	long verglartno = -1;
	int found;
	exec sql open Cseldiscountgrp using
		:sVz,
		:lKundenNr,
		:datum,
		:datum;
	ERROR_MSG( "open Cseldiscountgrp" )

	for ( ;; )
	{
		exec sql fetch Cseldiscountgrp into :disc;
		ERROR_MSG( "fetch Cseldiscountgrp" )
		if(NOTFOUND) break;
		if(verglartno == -1)
		{
			found = 0;
			if(startpos != NULL)
			{
				for(actpos = startpos;;actpos = actpos->folgepos)
				{
					if(actpos->artno == disc.ARTICLENO)
					{
						found = 1;
						break;
					}
					if(actpos->folgepos == NULL) break;
				}
			}
			if(found) continue;
			verglartno = disc.ARTICLENO;
			newpos = (struct nummer *)malloc(sizeof(struct nummer));
			if(startpos == NULL) startpos = newpos;
			else actpos->folgepos = newpos;
			actpos = newpos;
			actpos->folgepos = NULL;
			actpos->artno = disc.ARTICLENO;
			exec sql open Cselpreis using :disc.ARTICLENO;
			ERROR_MSG( "open Cselpreis" )
			exec sql fetch Cselpreis into :a.PREISEKAPO;
			ERROR_MSG( "fetch Cselpreis" )
			if(NOTFOUND) a.PREISEKAPO = 0;
		}
		else if(verglartno != disc.ARTICLENO)
		{
			found = 0;
			if(startpos != NULL)
			{
				for(actpos = startpos;;actpos = actpos->folgepos)
				{
					if(actpos->artno == disc.ARTICLENO)
					{
						found = 1;
						break;
					}
					if(actpos->folgepos == NULL) break;
				}
			}
			if(found) continue;
			verglartno = disc.ARTICLENO;
			newpos = (struct nummer *)malloc(sizeof(struct nummer));
			if(startpos == NULL) startpos = newpos;
			else actpos->folgepos = newpos;
			actpos = newpos;
			actpos->artno = disc.ARTICLENO;
			actpos->folgepos = NULL;
/*			if(a.PREISEKAPO == 0) continue;	*/
	        if ( ( rc = WriteCucos( error_msg ) ) < 0 )
	        {
				PrintMsg( fun, error_msg, FEHL, ERROR );
				return ERROR;
			}
			exec sql open Cselpreis using :disc.ARTICLENO;
			ERROR_MSG( "open Cselpreis" )
			exec sql fetch Cselpreis into :a.PREISEKAPO;
			ERROR_MSG( "fetch Cselpreis" )
			if(NOTFOUND) a.PREISEKAPO = 0;
		}
		a.BASEQTY = disc.BASEQTY;
		a.ARTICLENO = disc.ARTICLENO;
		FillCucosPct( error_msg );
		if(disc.FIXEDPRICE > 0) preis = disc.FIXEDPRICE;
	}
	if(verglartno > 0)
	{
		if ( ( rc = WriteCucos( error_msg ) ) < 0 )
		{
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
	}

	return OK;
}
 
/***** Hersteller mit discountgrp*********************************************************/

int LadeCucosHerstDG( char *error_msg)
{
	char *fun = "LadeCucosHerstDG";
	int rc;
	int found;
	int first;
	int anfang;
	int enddata;
	int ende = 0;

	exec sql begin declare section;
	long verglherstno = -1;
	long vergldgno = -1;
	long verglartno = -1;
	exec sql end declare section;

	exec sql open Cseldiscountherstdg using
		:sVz,
		:lKundenNr,
		:datum,
		:datum;
	ERROR_MSG( "open Cseldiscountherstdg" )

	first = 1;
	for ( ;; )
	{
		exec sql fetch Cseldiscountherstdg into :disc;
		ERROR_MSG( "fetch Cseldiscountherstdg" )
		if(NOTFOUND)
		{
			if(first) break;
			ende = 1;
			disc.MANUFACTURERNO = -2;
		}
		first = 0;
		if(verglherstno == -1)
		{
			verglherstno = disc.MANUFACTURERNO;
			FillCucosPct( error_msg );
		}
		else if(verglherstno != disc.MANUFACTURERNO)
		{
			anfang = 1;
			enddata = 0;
			if(vergldgno == -1)
			{
				vergldgno = disc.DISCOUNTGRPNO;
				FillCucosPct( error_msg );
			}
			else if(vergldgno != disc.DISCOUNTGRPNO)
			{
				anfang = 1;
				enddata = 0;
				exec sql open Cseldg using :vergldgno;
				ERROR_MSG( "open Cseldg" )
				for(;;)
				{
					exec sql fetch Cseldg into :verglartno,:a.PREISEKAPO;
					ERROR_MSG( "fetch Cseldg" )
					if(NOTFOUND)
					{
						if(anfang) break;
						enddata = 1;
					}
					found = 0;
					if(startpos != NULL)
					{
						for(actpos = startpos;;actpos = actpos->folgepos)
						{
							if(actpos->artno == verglartno)
							{
								found = 1;
								break;
							}
							if(actpos->folgepos == NULL) break;
						}
					}
					if(found)
					{
						if(enddata) break;
						continue;
					}
					anfang = 0;
					newpos = (struct nummer *)malloc(sizeof(struct nummer));
					if(startpos == NULL) startpos = newpos;
					else actpos->folgepos = newpos;
					actpos = newpos;
					actpos->folgepos = NULL;
					actpos->artno = verglartno;
					a.ARTICLENO = verglartno;
					if(a.PREISEKAPO == 0)
					{
						if(enddata) break;
						continue;
					}
			        if ( ( rc = WriteCucosHerst( error_msg ) ) < 0 )
			        {
						PrintMsg( fun, error_msg, FEHL, ERROR );
						return ERROR;
					}
					if(enddata) break;
				}
				LoeRab();
			}
			verglherstno = disc.MANUFACTURERNO;
			FillCucosPct( error_msg );
			if(ende) return OK;
		}
		FillCucosPct( error_msg );
	}

	return OK;
}
 
/***** Hersteller *********************************************************/

int LadeCucosHerst( char *error_msg)
{
	char *fun = "LadeCucosHerst";
	int rc;
	int found;
	int first;
	int anfang;
	int enddata;
	int ende = 0;

	exec sql begin declare section;
	long verglherstno = -1;
	long verglartno = -1;
	exec sql end declare section;

	exec sql open Cseldiscountherst using
		:sVz,
		:lKundenNr,
		:datum,
		:datum;
	ERROR_MSG( "open Cseldiscountherst" )

	first = 1;
	for ( ;; )
	{
		exec sql fetch Cseldiscountherst into :disc;
		ERROR_MSG( "fetch Cseldiscountherst" )
		if(NOTFOUND)
		{
			if(first) break;
			ende = 1;
			disc.MANUFACTURERNO = -2;
		}
		first = 0;
		if(verglherstno == -1)
		{
			verglherstno = disc.MANUFACTURERNO;
			FillCucosPct( error_msg );
		}
		else if(verglherstno != disc.MANUFACTURERNO)
		{
			anfang = 1;
			enddata = 0;
			exec sql open Cselzentral using :verglherstno,:sVz;
			ERROR_MSG( "open Cselzentral" )
			for(;;)
			{
				exec sql fetch Cselzentral into :verglartno;
				ERROR_MSG( "open Cselzentral" )
				if(NOTFOUND)
				{
					if(anfang) break;
					enddata = 1;
				}
				found = 0;
				if(startpos != NULL)
				{
					for(actpos = startpos;;actpos = actpos->folgepos)
					{
						if(actpos->artno == verglartno)
						{
							found = 1;
							break;
						}
						if(actpos->folgepos == NULL) break;
					}
				}
				if(found)
				{
					if(enddata) break;
					continue;
				}
				anfang = 0;
				newpos = (struct nummer *)malloc(sizeof(struct nummer));
				if(startpos == NULL) startpos = newpos;
				else actpos->folgepos = newpos;
				actpos = newpos;
				actpos->folgepos = NULL;
				actpos->artno = verglartno;
				exec sql open Cselpreis using :verglartno;
				ERROR_MSG( "open Cselpreis" )
				exec sql fetch Cselpreis into :a.PREISEKAPO;
				ERROR_MSG( "fetch Cselpreis" )
				if(NOTFOUND) a.PREISEKAPO = 0;
				a.ARTICLENO = verglartno;
				if(a.PREISEKAPO == 0)
				{
					if(enddata) break;
					continue;
				}
		        if ( ( rc = WriteCucosHerst( error_msg ) ) < 0 )
		        {
					PrintMsg( fun, error_msg, FEHL, ERROR );
					return ERROR;
				}
				if(enddata) break;
			}
			LoeRab();
			verglherstno = disc.MANUFACTURERNO;
			FillCucosPct( error_msg );
			if(ende) return OK;
		}
		FillCucosPct( error_msg );
	}

	return OK;
}
 
/***** Kunde *********************************************************/

int LadeCucosCst( char *error_msg)
{
	char *fun = "LadeCucosCst";
	int rc;
	int found;
	int first;
	int anfang;
	int enddata;
	int ende = 0;

	exec sql begin declare section;
	long verglartno = -1;
	exec sql end declare section;

	exec sql open Cseldiscountcst using
		:sVz,
		:lKundenNr,
		:datum,
		:datum;
	ERROR_MSG( "open Cseldiscountcst" )

	first = 1;
	for ( ;; )
	{
		exec sql fetch Cseldiscountcst into :disc;
		ERROR_MSG( "fetch Cseldiscountcst" )
		if(NOTFOUND)
		{
			if(first) return OK;
			break;
		}
		else
		{
			FillCucosPct( error_msg );
		}
		first = 0;
	}
	exec sql open Cselzentralalle using :sVz;
	ERROR_MSG( "open Cselzentralalle" )
	for(;;)
	{
		exec sql fetch Cselzentralalle into :verglartno,:a.PREISEKAPO;
		ERROR_MSG( "fetch Cselzentralalle" )
		if(NOTFOUND)
		{
			break;
		}
		found = 0;
		if(startpos != NULL)
		{
			for(actpos = startpos;;actpos = actpos->folgepos)
			{
				if(actpos->artno == verglartno)
				{
					found = 1;
					break;
				}
				if(actpos->folgepos == NULL) break;
			}
		}
		if(found)
		{
			continue;
		}
		newpos = (struct nummer *)malloc(sizeof(struct nummer));
		if(startpos == NULL) startpos = newpos;
		else actpos->folgepos = newpos;
		actpos->folgepos = newpos;
		actpos = newpos;
		actpos->folgepos = NULL;
		actpos->artno = verglartno;
		a.ARTICLENO = verglartno;
        if ( ( rc = WriteCucosHerst( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
	}

	return OK;
}
 
/***** DiscountGroup *********************************************************/

int LadeCucosDG( short grptype,char *error_msg)
{
	char *fun = "LadeCucosDG";
	int rc;
	int found;
	int first;
	int anfang;
	int enddata;
	int ende = 0;

	exec sql begin declare section;
	long vergldgno = -1;
	long verglartno = -1;
	short dgrptype;
	exec sql end declare section;

	dgrptype = grptype;

	exec sql open Cseldiscountdg using
		:sVz,
		:dgrptype,
		:lKundenNr,
		:datum,
		:datum;
	ERROR_MSG( "open Cseldiscountdg" )

	first = 1;
	for ( ;; )
	{
		exec sql fetch Cseldiscountdg into :disc;
		ERROR_MSG( "fetch Cseldiscountdg" )
		if(NOTFOUND)
		{
			if(first) break;
			ende = 1;
			disc.DISCOUNTGRPNO = -2;
		}
		first = 0;
		if(vergldgno == -1)
		{
			vergldgno = disc.DISCOUNTGRPNO;
		}
		else if(vergldgno != disc.DISCOUNTGRPNO)
		{
			anfang = 1;
			enddata = 0;
			exec sql open Cseldg using :vergldgno,:sVz;
			ERROR_MSG( "open Cseldg" )
			for(;;)
			{
				exec sql fetch Cseldg into :verglartno;
				ERROR_MSG( "open Cseldg" )
				if(NOTFOUND)
				{
					if(anfang) break;
					enddata = 1;
				}
				found = 0;
				if(startpos != NULL)
				{
					for(actpos = startpos;;actpos = actpos->folgepos)
					{
						if(actpos->artno == verglartno)
						{
							found = 1;
							break;
						}
						if(actpos->folgepos == NULL) break;
					}
				}
				if(found)
				{
					if(enddata) break;
					continue;
				}
				anfang = 0;
				newpos = (struct nummer *)malloc(sizeof(struct nummer));
				if(startpos == NULL) startpos = newpos;
				else actpos->folgepos = newpos;
				actpos = newpos;
				actpos->folgepos = NULL;
				actpos->artno = verglartno;
				exec sql open Cselpreis using :verglartno;
				ERROR_MSG( "open Cselpreis" )
				exec sql fetch Cselpreis into :a.PREISEKAPO;
				ERROR_MSG( "fetch Cselpreis" )
				if(NOTFOUND) a.PREISEKAPO = 0;
				a.ARTICLENO = verglartno;
				if(a.PREISEKAPO == 0)
				{
					if(enddata) break;
					continue;
				}
		        if ( ( rc = WriteCucosHerst( error_msg ) ) < 0 )
		        {
					PrintMsg( fun, error_msg, FEHL, ERROR );
					return ERROR;
				}
				if(enddata) break;
			}
			LoeRab();
			vergldgno = disc.DISCOUNTGRPNO;
			FillCucosPct( error_msg );
			if(ende) return OK;
		}
		FillCucosPct( error_msg );
	}

	return OK;
}
 
/***** DiscountGroup *********************************************************/

int LadeCucosCategory( char *error_msg)
{
	char *fun = "LadeCucosCategory";
	int rc;
	int found;
	int first;
	int anfang;
	int enddata;
	int ende = 0;

	exec sql begin declare section;
	long verglcatno = -1;
	long verglartno = -1;
	exec sql end declare section;

	exec sql open Cseldiscountgroup using
		:sVz,
		:lKundenNr,
		:datum,
		:datum;
	ERROR_MSG( "open Cseldiscountgroup" )

	first = 1;
	for ( ;; )
	{
		exec sql fetch Cseldiscountgroup into :disc;
		ERROR_MSG( "fetch Cseldiscountgroup" )
		if(NOTFOUND)
		{
			if(first) break;
			ende = 1;
			disc.ARTCATEGORYNO = -2;
		}
		first = 0;
		if(verglcatno == -1)
		{
			verglcatno = disc.ARTCATEGORYNO;
			FillCucosPct( error_msg );
		}
		else if(verglcatno != disc.ARTCATEGORYNO)
		{
			anfang = 1;
			enddata = 0;
			exec sql open Cselgroup using :verglcatno,:sVz;
			ERROR_MSG( "open Cseldg" )
			for(;;)
			{
				exec sql fetch Cselgroup into :verglartno;
				ERROR_MSG( "open Cseldg" )
				if(NOTFOUND)
				{
					if(anfang) break;
					enddata = 1;
				}
				found = 0;
				if(startpos != NULL)
				{
					for(actpos = startpos;;actpos = actpos->folgepos)
					{
						if(actpos->artno == verglartno)
						{
							found = 1;
							break;
						}
						if(actpos->folgepos == NULL) break;
					}
				}
				if(found)
				{
					if(enddata) break;
					continue;
				}
				anfang = 0;
				newpos = (struct nummer *)malloc(sizeof(struct nummer));
				if(startpos == NULL) startpos = newpos;
				else actpos->folgepos = newpos;
				actpos = newpos;
				actpos->folgepos = NULL;
				actpos->artno = verglartno;
				exec sql open Cselpreis using :verglartno;
				ERROR_MSG( "open Cselpreis" )
				exec sql fetch Cselpreis into :a.PREISEKAPO;
				ERROR_MSG( "fetch Cselpreis" )
				if(NOTFOUND) a.PREISEKAPO = 0;
				a.ARTICLENO = verglartno;
				if(a.PREISEKAPO == 0)
				{
					if(enddata) break;
					continue;
				}
		        if ( ( rc = WriteCucosHerst( error_msg ) ) < 0 )
		        {
					PrintMsg( fun, error_msg, FEHL, ERROR );
					return ERROR;
				}
				if(enddata) break;
			}
			LoeRab();
			verglcatno = disc.ARTCATEGORYNO;
			FillCucosPct( error_msg );
			if(ende) return OK;
		}
		FillCucosPct( error_msg );
	}

	return OK;
}
 
/***** Sonderangebote *********************************************************/

int LadeCucosSonder( char *error_msg)
{
	char *fun = "LadeCucosSonder";
	int rc;
	int found;
	int ende = 0;
	int first = 1;

	exec sql begin declare section;
	long vergldgno = -1;
	long verglartno = -1;
	exec sql end declare section;

	exec sql open Cseldiscountsonder using
		:sVz,
		:lKundenNr,
		:datum,
		:datum;
	ERROR_MSG( "open Cseldiscountsonder" )

	for ( ;; )
	{
		exec sql fetch Cseldiscountsonder into :disc;
		ERROR_MSG( "fetch Cseldiscountsonder" )
		if(NOTFOUND)
		{
			if(first) break;
			ende = 1;
		}
		if(verglartno == -1)
		{
			found = 0;
			if(startpos != NULL)
			{
				for(actpos = startpos;;actpos = actpos->folgepos)
				{
					if(actpos->artno == disc.ARTICLENO)
					{
						found = 1;
						break;
					}
					if(actpos->folgepos == NULL) break;
				}
			}
			if(found) continue;
			newpos = (struct nummer *)malloc(sizeof(struct nummer));
			if(startpos == NULL) startpos = newpos;
			else actpos->folgepos = newpos;
			actpos = newpos;
			actpos->folgepos = NULL;
			actpos->artno = disc.ARTICLENO;
			exec sql open Cselpreis using :disc.ARTICLENO;
			ERROR_MSG( "open Cselpreis" )
			exec sql fetch Cselpreis into :a.PREISEKAPO;
			ERROR_MSG( "fetch Cselpreis" )
			if(NOTFOUND) continue;
			if(a.PREISEKAPO == 0) continue;
			verglartno = disc.ARTICLENO;
			a.ARTICLENO = disc.ARTICLENO;
			FillCucosPct( error_msg );
		}
		else if(verglartno != disc.ARTICLENO)
		{
			if(a.ARTICLENO > 0)
			{
				if ( ( rc = WriteCucos( error_msg ) ) < 0 )
				{
					PrintMsg( fun, error_msg, FEHL, ERROR );
					return ERROR;
				}
			}
			else
			{
				LoeRab();
			}
			verglartno = disc.ARTICLENO;
			found = 0;
			for(actpos = startpos;;actpos = actpos->folgepos)
			{
				if(actpos->artno == disc.ARTICLENO)
				{
					found = 1;
					break;
				}
				if(actpos->folgepos == NULL) break;
			}
			if(found) continue;
			newpos = (struct nummer *)malloc(sizeof(struct nummer));
			if(startpos == NULL) startpos = newpos;
			else actpos->folgepos = newpos;
			actpos = newpos;
			actpos->folgepos = NULL;
			actpos->artno = disc.ARTICLENO;
			exec sql open Cselpreis using :disc.ARTICLENO;
			ERROR_MSG( "open Cselpreis" )
			exec sql fetch Cselpreis into :a.PREISEKAPO;
			ERROR_MSG( "fetch Cselpreis" )
			if(NOTFOUND) continue;
			if(a.PREISEKAPO == 0) continue;
			verglartno = disc.ARTICLENO;
			a.BASEQTY = disc.BASEQTY;
			a.ARTICLENO = disc.ARTICLENO;
			FillCucosPct( error_msg );
		}
		else
		{
			FillCucosPct( error_msg );
		}
	}
	if(a.ARTICLENO > 0)
	{
		if ( ( rc = WriteCucos( error_msg ) ) < 0 )
		{
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
	}

	return OK;
}
 
/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if ( (rc = AfterLadeCucos(error_msg)) < 0) return rc;

	return OK;
}

/*** Prepare DEL-Cucos ************************************************/

int PrepareDelCucos( char *error_msg )
{
	char *fun = "PrepareDelCucos";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "customerno " );
	strcat( str, "from " );
	strcat( str, "cucosserbia " );
	strcat( str, "where branchno = ? " );
	strcat( str, "and customerno = ? " );
	strcat( str, "for update " );

	exec sql prepare del_cucos from :str;
	ERROR_MSG( "prepare del_cucos" )
	exec sql declare Cdelcucos cursor with hold for del_cucos;

	strcpy( str, "delete from cucosserbia " );
	strcat( str, "where current of Cdelcucos " );
	
	exec sql prepare delete_cucos from :str;
	ERROR_MSG( "prepare delete_cucos" )

	return OK;
}

/*** PREPARE-LESE-Cucos ************************************************/

int PrepareLeseCucos( char *error_msg )
{
	char *fun = "PrepareLesecucos";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	EXEC SQL create temp table t_ekg (
				 PharmacyGroupId char(3));

	ERROR_MSG( "create temp t_ekg" )

	strcpy( str, "insert into t_ekg " );
	strcat( str, "select " );
	strcat( str, "PharmacyGroupId " );
	strcat( str, "from " );
	strcat( str, "customerpharmacygr " );
	strcat( str, "where BranchNo = ? " );
	strcat( str, "and CustomerNo = ? " );

	exec sql prepare ins_ekg from :str;
	ERROR_MSG( "prepare ins_ekg" )

	strcpy( str, "select " );
	strcat( str, "kundennr, " );
	strcat( str, "payment_term " );
	strcat( str, "from kunde " );
	strcat( str, "where vertriebszentrumnr = ? " );
	strcat( str, "and kdgruppe not in ('09','13') " );
	strcat( str, "and mastercstno = 0 " );
	strcat( str, "and (originalfilialnr = 0 " );
	strcat( str, "or originalfilialnr = vertriebszentrumnr ) " );

	exec sql prepare dec_kunde from :str;
	ERROR_MSG( "prepare dec_kunde" )
	exec sql declare CselKunde cursor with hold for dec_kunde;

	strcpy( str, "select " );
	strcat( str, "paymentarget " );
	strcat( str, "from PAYMENTTERMS " );
	strcat( str, "where payment_term = ? " );
	strcat( str, "order by paymentarget desc " );

	exec sql prepare dec_payterm from :str;
	ERROR_MSG( "prepare dec_payterm" )
	exec sql declare CselPayterm cursor with hold for dec_payterm;

	strcpy( str, "select " );
	strcat( str, DISCOUNT_PLISTE );
	strcat( str, " from discount " );
	strcat( str, " where Discount.BranchNo = ? and " );
	strcat( str, " Discount.ArticleNo > 0 and " );
	strcat( str, " ( Discount.CustomerNo = 0 and " );
	strcat( str, " ( Discount.PharmacyGroupId = '000' or " );
	strcat( str, " (Discount.PharmacyGroupId in  " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) or " );
	strcat( str, " Discount.CustomerNo = ? ) and " );
	strcat( str, " Discount.DateFrom <= ? and " );
	strcat( str, " Discount.DateTo >= ? and " );
	strcat( str, " ( Discount.PharmGrpExcluded = '000' or " );
	strcat( str, " (Discount.PharmGrpExcluded not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_2 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_2 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_3 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_3 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg)))" );
	strcat( str, " order by Discount.Articleno,Discount.Discountvaluepct,Discount.paymenttargetno,Discount.BaseQty; " );

	exec sql prepare dec_discountgrp from :str;
	ERROR_MSG( "prepare dec_discountgrp" )
	exec sql declare Cseldiscountgrp cursor with hold for dec_discountgrp;

	strcpy( str, "select " );
	strcat( str, DISCOUNT_PLISTE );
	strcat( str, " from discount " );
	strcat( str, " where Discount.BranchNo = ? and " );
	strcat( str, " Discount.ArticleNo = 0 and " );
	strcat( str, " Discount.manufacturerno > 0 and " );
	strcat( str, " Discount.discountgrpno > 0 and " );
	strcat( str, " ( Discount.CustomerNo = 0 and " );
	strcat( str, " ( Discount.PharmacyGroupId = '000' or " );
	strcat( str, " (Discount.PharmacyGroupId in  " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) or " );
	strcat( str, " Discount.CustomerNo = ? ) and " );
	strcat( str, " Discount.DateFrom <= ? and " );
	strcat( str, " Discount.DateTo >= ? and " );
	strcat( str, " ( Discount.PharmGrpExcluded = '000' or " );
	strcat( str, " (Discount.PharmGrpExcluded not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_2 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_2 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_3 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_3 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg)))" );
	strcat( str, " order by Discount.manufacturerno,Discount.Discountvaluepct,Discount.paymenttargetno,Discount.BaseQty; " );

	exec sql prepare dec_discountherstdg from :str;
	ERROR_MSG( "prepare dec_discountherstdg" )
	exec sql declare Cseldiscountherstdg cursor with hold for dec_discountherstdg;

	strcpy( str, "select " );
	strcat( str, DISCOUNT_PLISTE );
	strcat( str, " from discount " );
	strcat( str, " where Discount.BranchNo = ? and " );
	strcat( str, " Discount.ArticleNo = 0 and " );
	strcat( str, " Discount.manufacturerno > 0 and " );
	strcat( str, " Discount.discountgrpno = 0 and " );
	strcat( str, " ( Discount.CustomerNo = 0 and " );
	strcat( str, " ( Discount.PharmacyGroupId = '000' or " );
	strcat( str, " (Discount.PharmacyGroupId in  " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) or " );
	strcat( str, " Discount.CustomerNo = ? ) and " );
	strcat( str, " Discount.DateFrom <= ? and " );
	strcat( str, " Discount.DateTo >= ? and " );
	strcat( str, " ( Discount.PharmGrpExcluded = '000' or " );
	strcat( str, " (Discount.PharmGrpExcluded not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_2 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_2 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_3 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_3 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg)))" );
	strcat( str, " order by Discount.manufacturerno,Discount.Discountvaluepct,Discount.paymenttargetno,Discount.BaseQty; " );

	exec sql prepare dec_discountherst from :str;
	ERROR_MSG( "prepare dec_discountherst" )
	exec sql declare Cseldiscountherst cursor with hold for dec_discountherst;

	strcpy( str, "select " );
	strcat( str, DISCOUNT_PLISTE );
	strcat( str, " from discount,discountgrp " );
	strcat( str, " where Discount.BranchNo = ? and " );
	strcat( str, " Discount.ArticleNo = 0 and " );
	strcat( str, " Discount.manufacturerno = 0 and " );
	strcat( str, " Discount.discountgrpno > 0 and " );
	strcat( str, " Discount.discountgrpno = Discountgrp.discountgrpno and " );
	strcat( str, " Discount.branchno = Discountgrp.branchno and " );
	strcat( str, " Discountgrp.discountgrptype = ? and " );
	strcat( str, " ( Discount.CustomerNo = 0 and " );
	strcat( str, " ( Discount.PharmacyGroupId = '000' or " );
	strcat( str, " (Discount.PharmacyGroupId in  " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) or " );
	strcat( str, " Discount.CustomerNo = ? ) and " );
	strcat( str, " Discount.DateFrom <= ? and " );
	strcat( str, " Discount.DateTo >= ? and " );
	strcat( str, " ( Discount.PharmGrpExcluded = '000' or " );
	strcat( str, " (Discount.PharmGrpExcluded not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_2 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_2 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_3 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_3 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg)))" );
	strcat( str, " order by Discount.discountgrpno,Discount.Discountvaluepct,Discount.paymenttargetno,Discount.BaseQty; " );

	exec sql prepare dec_discountdg from :str;
	ERROR_MSG( "prepare dec_discountdg" )
	exec sql declare Cseldiscountdg cursor with hold for dec_discountdg;

	strcpy( str, "select " );
	strcat( str, DISCOUNT_PLISTE );
	strcat( str, " from discount " );
	strcat( str, " where Discount.BranchNo = ? and " );
	strcat( str, " Discount.ArticleNo = 0 and " );
	strcat( str, " Discount.manufacturerno = 0 and " );
	strcat( str, " Discount.discountgrpno = 0 and " );
	strcat( str, " Discount.artcategoryno > 0 and " );
	strcat( str, " ( Discount.CustomerNo = 0 and " );
	strcat( str, " ( Discount.PharmacyGroupId = '000' or " );
	strcat( str, " (Discount.PharmacyGroupId in  " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) or " );
	strcat( str, " Discount.CustomerNo = ? ) and " );
	strcat( str, " Discount.DateFrom <= ? and " );
	strcat( str, " Discount.DateTo >= ? and " );
	strcat( str, " ( Discount.PharmGrpExcluded = '000' or " );
	strcat( str, " (Discount.PharmGrpExcluded not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_2 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_2 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_3 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_3 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg)))" );
	strcat( str, " order by Discount.artcategoryno,Discount.Discountvaluepct,Discount.paymenttargetno,Discount.BaseQty; " );

	exec sql prepare dec_discountgroup from :str;
	ERROR_MSG( "prepare dec_discountgroup" )
	exec sql declare Cseldiscountgroup cursor with hold for dec_discountgroup;

	strcpy( str, "select " );
	strcat( str, DISCOUNT_PLISTE );
	strcat( str, " from discount " );
	strcat( str, " where Discount.BranchNo = ? and " );
	strcat( str, " Discount.ArticleNo = 0 and " );
	strcat( str, " Discount.manufacturerno = 0 and " );
	strcat( str, " Discount.discountgrpno = 0 and " );
	strcat( str, " Discount.artcategoryno = 0 and " );
	strcat( str, " Discount.CustomerNo = ? and " );
	strcat( str, " Discount.DateFrom <= ? and " );
	strcat( str, " Discount.DateTo >= ? " );
	strcat( str, " order by Discount.Discountvaluepct,Discount.paymenttargetno,Discount.BaseQty; " );

	exec sql prepare dec_discountcst from :str;
	ERROR_MSG( "prepare dec_discountcst" )
	exec sql declare Cseldiscountcst cursor with hold for dec_discountcst;

	strcpy( str, "select " );
	strcat( str, DISCOUNT_PLISTE );
	strcat( str, " from discount" );
	strcat( str, " where Discount.BranchNo = ?" );
	strcat( str, " and Discount.ArticleNo = ?" );
	strcat( str, " and Discount.CustomerNo = 0" );
	strcat( str, " and Discount.DateFrom <= ?" );
	strcat( str, " and Discount.DateTo >= ?" );
	strcat( str, " order by Discount.Discountvaluepct,Discount.BaseQty;" );

	exec sql prepare dec_discountallg from :str;
	ERROR_MSG( "prepare dec_discountallg" )
	exec sql declare Cseldiscountallg cursor for dec_discountallg;

	strcpy( str, "select " );
	strcat( str, DISCOUNT_PLISTE );
	strcat( str, " from discount" );
	strcat( str, " where Discount.BranchNo = ?" );
	strcat( str, " and Discount.ArticleNo > 0" );
	strcat( str, " and Discount.DISCOUNTSPEC = 10" );
	strcat( str, " and Discount.DiscountValuepct > 0" );
	strcat( str, " and ( Discount.CustomerNo = 0 and " );
	strcat( str, " ( Discount.PharmacyGroupId = '000' or " );
	strcat( str, " (Discount.PharmacyGroupId in  " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) or " );
	strcat( str, " Discount.CustomerNo = ? ) and " );
	strcat( str, " Discount.DateFrom <= ? and " );
	strcat( str, " Discount.DateTo >= ? and " );
	strcat( str, " ( Discount.PharmGrpExcluded = '000' or " );
	strcat( str, " (Discount.PharmGrpExcluded not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_2 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_2 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg))) and" );
	strcat( str, " ( Discount.PharmGrpExcl_3 = '000' or " );
	strcat( str, " (Discount.PharmGrpExcl_3 not in " );
	strcat( str, " (select t_ekg.PharmacyGroupId from t_ekg)))" );
	strcat( str, " order by Discount.ArticleNo,Discount.Discountvaluepct,Discount.BaseQty;" );

	exec sql prepare dec_discountsonder from :str;
	ERROR_MSG( "prepare dec_discountsonder" )
	exec sql declare Cseldiscountsonder cursor for dec_discountsonder;

	strcpy( str, "select " );
	strcat( str, " preisekapo" );
	strcat( str, " from artikelpreis" );
	strcat( str, " where artikel_nr = ?" );

	exec sql prepare sel_preis from :str;
	ERROR_MSG( "prepare sel_preis" )
	exec sql declare Cselpreis cursor for sel_preis;

	strcpy( str, "select " );
	strcat( str, " z.artikel_nr,p.preisekapo" );
	strcat( str, " from artikelzentral z,artikellokal l,artikelpreis p" );
	strcat( str, " where z.hersteller_nr = ?" );
	strcat( str, " and z.artikel_nr = p.artikel_nr" );
	strcat( str, " and z.artikel_nr = l.artikel_nr" );
	strcat( str, " and l.filialnr = ?" );
	strcat( str, " and l.artikelaktiv = '1'" );
	strcat( str, " and p.preisekapo > 0" );

	exec sql prepare sel_zentral from :str;
	ERROR_MSG( "prepare sel_zentral" )
	exec sql declare Cselzentral cursor for sel_zentral;

	strcpy( str, "select " );
	strcat( str, " z.artikel_nr,p.preisekapo" );
	strcat( str, " from artikelzentral z,artikellokal l,artikelpreis p" );
	strcat( str, " where z.artikel_nr = p.artikel_nr" );
	strcat( str, " and z.artikel_nr = l.artikel_nr" );
	strcat( str, " and l.filialnr = ?" );
	strcat( str, " and l.artikelaktiv = '1'" );
	strcat( str, " and p.preisekapo > 0" );

	exec sql prepare sel_zentralalle from :str;
	ERROR_MSG( "prepare sel_zentralalle" )
	exec sql declare Cselzentralalle cursor for sel_zentralalle;

	strcpy( str, "select " );
	strcat( str, " g.articleno,p.preisekapo" );
	strcat( str, " from articlegroup g,artikellokal l,artikelpreis p" );
	strcat( str, " where g.artcategoryno = ?" );
	strcat( str, " and g.articleno = p.artikel_nr" );
	strcat( str, " and g.articleno = l.artikel_nr" );
	strcat( str, " and l.filialnr = ?" );
	strcat( str, " and l.artikelaktiv = '1'" );
	strcat( str, " and p.preisekapo > 0" );

	exec sql prepare sel_group from :str;
	ERROR_MSG( "prepare sel_group" )
	exec sql declare Cselgroup cursor for sel_group;

	strcpy( str, "select " );
	strcat( str, " d.articleno,p.preisekapo" );
	strcat( str, " from discountgrpmem d,artikellokal l,artikelpreis p" );
	strcat( str, " where d.discountgrpno = ?" );
	strcat( str, " and d.articleno = p.artikel_nr" );
	strcat( str, " and d.articleno = l.artikel_nr" );
	strcat( str, " and l.filialnr = ?" );
	strcat( str, " and l.filialnr = d.branchno" );
	strcat( str, " and l.artikelaktiv = '1'" );
	strcat( str, " and p.preisekapo > 0" );

	exec sql prepare sel_dg from :str;
	ERROR_MSG( "prepare sel_dg" )
	exec sql declare Cseldg cursor for sel_dg;

	strcpy( str, "select " );
	strcat( str, "PharmacyGroupId " );
	strcat( str, "from " );
	strcat( str, "t_ekg " );
	strcat( str, "for update " );

	exec sql prepare del_ekg from :str;
	ERROR_MSG( "prepare del_ekg" )
	exec sql declare Cdelekg cursor with hold for del_ekg;

	strcpy( str, "delete from t_ekg " );
	strcat( str, "where current of Cdelekg " );
	
	exec sql prepare delete_ekg from :str;
	ERROR_MSG( "prepare delete_ekg" )

	return OK;      
}

/*** PREPARE-LADE-Cucos ************************************************/

int PrepareLadeCucos( char *error_msg )
{
	char *fun = "PrepareLadeCucos";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into cucosserbia (" );
	strcat( str, CUCOSSERBIA_PELISTE );
	strcat( str, " ) values (" );
	strcat( str, " ?, ?, ?, ?, ?," );
	strcat( str, " ?, ?, ?, ?, ?," );
	strcat( str, " ?, ?, ?, ?, ?," );
	strcat( str, " ?, ?, ?, ?, ?," );
	strcat( str, " ?, ?, ?, ?, ?," );
	strcat( str, " ? )" );
	   
	exec sql prepare ins_cucos from :str;
	ERROR_MSG( "prepare ins_cucos" )

	return OK;      
}

/*** Loeschen Articlecodes ********************************************************/

int DelCucos( char *error_msg )
{
	char *fun = "DelCucos";
	int i;

	exec sql begin declare section;
	char str[2048];
	long lCst;
	exec sql end declare section;

	exec sql open Cdelcucos using :sVz,:lKundenNr;
    ERROR_MSG( "open Cdelcucos" )

	for(;;)
	{
		exec sql fetch Cdelcucos into :lCst;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch Cdelcucos" )

		exec sql execute delete_cucos;
		ERROR_MSG( "execute delete_cucos" )

	}
	a.BRANCHNO = lKundenNr;
	a.CUSTOMERNO = sVz;
	a.ARTICLENO = 0;
	a.PREISEKAPO = 0;
	a.BASEQTY = 0;
	a.DISCOUNTVALUEPCT = 0;
	a.DISCOUNTPRICE = 0;
	a.DISCOUNTPCT1 = 0;
	a.DISCOUNTPRICE1 = 0;
	a.PAYTERM1 = 0;
	a.DISCOUNTPCT2 = 0;
	a.DISCOUNTPRICE2 = 0;
	a.PAYTERM2 = 0;
	a.DISCOUNTPCT3 = 0;
	a.DISCOUNTPRICE3 = 0;
	a.PAYTERM3 = 0;
	a.DISCOUNTPCT4 = 0;
	a.DISCOUNTPRICE4 = 0;
	a.PAYTERM4 = 0;
	a.DISCOUNTPCT5 = 0;
	a.DISCOUNTPRICE5 = 0;
	a.PAYTERM5 = 0;
	a.DISCOUNTPCT6 = 0;
	a.DISCOUNTPRICE6 = 0;
	a.PAYTERM6 = 0;

	return OK;      
}

/***** AFTER-LADE-Cucos *********************************************/

int AfterLadeCucos( char *error_msg )
{
	return OK;
}

/***** Sonderangebote *********************************************/

int GetSonder( char *error_msg )
{
	char *fun = "GetSonder";

	exec sql open Cseldiscountallg using :sVz,:a.ARTICLENO,:datum,:datum;
	ERROR_MSG( "open Cseldiscountallg" )
	exec sql fetch Cseldiscountallg into :disc;
	ERROR_MSG( "fetch Cseldiscountallg" )
	if(NOTFOUND) return OK;
	a.DISCOUNTVALUEPCT = disc.DISCOUNTVALUEPCT;
	a.DISCOUNTPRICE = a.PREISEKAPO - ((a.PREISEKAPO * disc.DISCOUNTVALUEPCT)/(double)100);
	return OK;
}

/***** Schreiben Cucos *********************************************/

int WriteCucos( char *error_msg )
{
	char *fun = "WriteCucos";
	if(preis > 0) fixpreis = preis;
	else fixpreis = a.PREISEKAPO;
	if(		fixpreis > 0.01 && (
			a.DISCOUNTVALUEPCT	> 0 ||
			a.DISCOUNTPCT1		> 0	||	
			a.DISCOUNTPCT2		> 0	||
			a.DISCOUNTPCT3		> 0	||
			a.DISCOUNTPCT4		> 0	||
			a.DISCOUNTPCT5		> 0	||
			a.DISCOUNTPCT6	) )
	{
		a.DISCOUNTPRICE = fixpreis - ((fixpreis * a.DISCOUNTVALUEPCT)/(double)100);
		a.DISCOUNTPRICE1 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT1))/(double)100);
		a.DISCOUNTPRICE2 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT2))/(double)100);
		a.DISCOUNTPRICE3 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT3))/(double)100);
		a.DISCOUNTPRICE4 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT4))/(double)100);
		a.DISCOUNTPRICE5 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT5))/(double)100);
		a.DISCOUNTPRICE6 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT6))/(double)100);
		EXEC SQL EXECUTE ins_cucos USING
			:a.BRANCHNO,
			:a.CUSTOMERNO,
			:a.ARTICLENO,
			:a.PREISEKAPO,
			:a.BASEQTY,
			:a.DISCOUNTVALUEPCT,
			:a.DISCOUNTPRICE,
			:a.DISCOUNTPCT1,
			:a.DISCOUNTPRICE1,
			:a.PAYTERM1,
			:a.DISCOUNTPCT2,
			:a.DISCOUNTPRICE2,
			:a.PAYTERM2,
			:a.DISCOUNTPCT3,
			:a.DISCOUNTPRICE3,
			:a.PAYTERM3,
			:a.DISCOUNTPCT4,
			:a.DISCOUNTPRICE4,
			:a.PAYTERM4,
			:a.DISCOUNTPCT5,
			:a.DISCOUNTPRICE5,
			:a.PAYTERM5,
			:a.DISCOUNTPCT6,
			:a.DISCOUNTPRICE6,
			:a.PAYTERM6,
			:a.CASCADE;
		ERROR_MSG( "insert Cucos" );
		zaehlerIns++;
	}

	LoeRab();
	return OK;
}

/***** Schreiben Cucos Hersteller *********************************************/

int WriteCucosHerst( char *error_msg )
{
	char *fun = "WriteCucosHerst";
	int nix;
	if(preis > 0) fixpreis = preis;
	else fixpreis = a.PREISEKAPO;
	if(		fixpreis > 0.01 && (
			a.DISCOUNTVALUEPCT	> 0 ||
			a.DISCOUNTPCT1		> 0	||	
			a.DISCOUNTPCT2		> 0	||
			a.DISCOUNTPCT3		> 0	||
			a.DISCOUNTPCT4		> 0	||
			a.DISCOUNTPCT5		> 0	||
			a.DISCOUNTPCT6	) )
	{
		a.DISCOUNTPRICE = fixpreis - ((fixpreis * a.DISCOUNTVALUEPCT)/(double)100);
		a.DISCOUNTPRICE1 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT1))/(double)100);
		a.DISCOUNTPRICE2 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT2))/(double)100);
		a.DISCOUNTPRICE3 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT3))/(double)100);
		a.DISCOUNTPRICE4 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT4))/(double)100);
		a.DISCOUNTPRICE5 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT5))/(double)100);
		a.DISCOUNTPRICE6 = a.DISCOUNTPRICE - ((a.DISCOUNTPRICE * (a.DISCOUNTPCT6))/(double)100);
		EXEC SQL EXECUTE ins_cucos USING
			:a.BRANCHNO,
			:a.CUSTOMERNO,
			:a.ARTICLENO,
			:a.PREISEKAPO,
			:a.BASEQTY,
			:a.DISCOUNTVALUEPCT,
			:a.DISCOUNTPRICE,
			:a.DISCOUNTPCT1,
			:a.DISCOUNTPRICE1,
			:a.PAYTERM1,
			:a.DISCOUNTPCT2,
			:a.DISCOUNTPRICE2,
			:a.PAYTERM2,
			:a.DISCOUNTPCT3,
			:a.DISCOUNTPRICE3,
			:a.PAYTERM3,
			:a.DISCOUNTPCT4,
			:a.DISCOUNTPRICE4,
			:a.PAYTERM4,
			:a.DISCOUNTPCT5,
			:a.DISCOUNTPRICE5,
			:a.PAYTERM5,
			:a.DISCOUNTPCT6,
			:a.DISCOUNTPRICE6,
			:a.PAYTERM6,
			:a.CASCADE;
		if(sqlca.sqlcode == -239)
		{
			nix = 1;
		}
		
		ERROR_MSG( "insert Cucos" );
		zaehlerIns++;
	}
	a.ARTICLENO = 0;
	a.PREISEKAPO = 0;
/*	a.BASEQTY = 0;
	a.DISCOUNTVALUEPCT = 0; */
	a.DISCOUNTPRICE = 0;
	a.DISCOUNTPRICE1 = 0;
	a.DISCOUNTPRICE2 = 0;
	a.DISCOUNTPRICE3 = 0;
	a.DISCOUNTPRICE4 = 0;
	a.DISCOUNTPRICE5 = 0;
	a.DISCOUNTPRICE6 = 0;
	preis = 0;
	return OK;
}

/***** Loeschen Rabattwerte *********************************************/

void LoeRab( )
{
	a.ARTICLENO = 0;
	a.PREISEKAPO = 0;
	a.BASEQTY = 0;
	a.DISCOUNTVALUEPCT = 0;
	a.DISCOUNTPRICE = 0;
	a.DISCOUNTPCT1 = 0;
	a.DISCOUNTPRICE1 = 0;
	a.DISCOUNTPCT2 = 0;
	a.DISCOUNTPRICE2 = 0;
	a.DISCOUNTPCT3 = 0;
	a.DISCOUNTPRICE3 = 0;
	a.DISCOUNTPCT4 = 0;
	a.DISCOUNTPRICE4 = 0;
	a.DISCOUNTPCT5 = 0;
	a.DISCOUNTPRICE5 = 0;
	a.DISCOUNTPCT6 = 0;
	a.DISCOUNTPRICE6 = 0;
	preis = 0;
}

/***** Fuellen Rabattprozente *********************************************/

int FillCucosPct( char *error_msg )
{
	char *fun = "FillCucosPct";

	if(disc.PAYMENTTARGETNO > iAnzTargets) return OK;

	if(disc.PAYMENTTARGETNO == 0)
	{
		a.DISCOUNTVALUEPCT = disc.DISCOUNTVALUEPCT;
	}
	else if(disc.PAYMENTTARGETNO == 1)
	{
		a.DISCOUNTPCT1 = disc.DISCOUNTVALUEPCT;
	}
	else if(disc.PAYMENTTARGETNO == 2)
	{
		a.DISCOUNTPCT2 = disc.DISCOUNTVALUEPCT;
	}
	else if(disc.PAYMENTTARGETNO == 3)
	{
		a.DISCOUNTPCT3 = disc.DISCOUNTVALUEPCT;
	}
	else if(disc.PAYMENTTARGETNO == 4)
	{
		a.DISCOUNTPCT4 = disc.DISCOUNTVALUEPCT;
	}
	else if(disc.PAYMENTTARGETNO == 5)
	{
		a.DISCOUNTPCT5 = disc.DISCOUNTVALUEPCT;
	}
	else if(disc.PAYMENTTARGETNO == 6)
	{
		a.DISCOUNTPCT6 = disc.DISCOUNTVALUEPCT;
	}
	if(disc.FIXEDPRICE > 0) preis = disc.FIXEDPRICE;
	a.BASEQTY = disc.BASEQTY;
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
	sprintf( logFile, "%s/wws.log", env );

	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
		return;
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s %s\n",
		mld,
		99,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"loadcucosrs",
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

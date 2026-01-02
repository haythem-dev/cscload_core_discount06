/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadpricelist"

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
#include "pplib/allg.h"
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
#define DATABASE           "phosix"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define CHAR_FIELD_SEPARATOR ';'

// Längen der Felder, wie sie in der Inputdatei geliefert werden
// (weichen teilweise von den DB-Feldlängen ab)
#define LEN_FILE_BRANCHNO             2
#define LEN_FILE_PHARMACYGROUPID      3
#define LEN_FILE_ARTICLENO            8
#define LEN_FILE_DISCOUNTTYPE         2
#define LEN_FILE_DISCOUNTSPEC         2
#define LEN_FILE_DATEFROM             8
#define LEN_FILE_DATETO               8
#define LEN_FILE_QUANTITY             8
#define LEN_FILE_FIXEDPRICE          10
#define NUMBER_OF_FIELDS              9

FILE *pricelistfile;
char pricelistpfad[81];
char log_file [300 + 1];
char dateiname[L_TEXT];
int explain = NO;
int sichern = NO;
int zaehlerIns = 0;     /* weil ich zu faul war alex */
int zaehlerUpd = 0;     /* weil ich zu faul war alex */
char currentDate[LEN_FILE_DATEFROM + 1];

EXEC SQL BEGIN DECLARE SECTION;
struct s_PRICELISTREC {
	char    BRANCHNO[LEN_FILE_BRANCHNO + 1];
	char    PHARMACYGROUPID[LEN_FILE_PHARMACYGROUPID + 1];
	char    ARTICLENO[LEN_FILE_ARTICLENO + 1];
	char    DISCOUNTTYPE[LEN_FILE_DISCOUNTTYPE + 1];
	char    DISCOUNTSPEC[LEN_FILE_DISCOUNTSPEC + 1];
	char    DATEFROM[LEN_FILE_DATEFROM + 1];
	char    DATETO[LEN_FILE_DATETO + 1];
	char    QUANTITY[LEN_FILE_QUANTITY + 1];
	char    FIXEDPRICE[LEN_FILE_FIXEDPRICE + 1];
};

char datenbank[60];
long lArticleNo;
EXEC SQL END DECLARE SECTION;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
int PrepareLoadTables         (char *error_msg);
int PrepareLoadPriceList      (char *error_msg);
int StartLoadTables           (char *error_msg);
int AfterLoadTables           (char *error_msg);
int PreparePriceListRec       (struct s_PRICELISTREC * pPriceListRec, int recno);
int ResetUpdateSignDiscount   (char *branchno, char *error_msg);
int DeleteDiscountNotUpdated  (char *branchno, char *error_msg);
int CloseDatabase             ( void );
void getCurrentDate           ( char *datebuf, int buflen );

/***** MAIN *****************************************************************/

int main( int argc, char **argv  )
{
	char  error_msg[181];
	char  *schalter;
	int   i;
	char  *fun = "main";
	char  *LOG_FILE = "wws.log";
	char  *LOG_PATH;
	char  logpath[256 + 1];
	int   rc;
	int   status = 0;
	char  start_msg[81];
	bool  fError = false;

	sprintf(datenbank, "%s", DATABASE);
	strcpy(pricelistpfad, "");

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
		else if ( !strcmp( schalter, "-ex" ) )
		{
			strcat(start_msg, " -ex");
			explain = YES;
		}
		else if (!strcmp(schalter, "-file"))
		{
			strcat(start_msg, " -file");
			i++;
			if (strlen(argv[i]) >= sizeof(pricelistpfad))
			{
				printf("value for parameter -file too long\n");
				fError = true;
				break;
			}
			strcpy(pricelistpfad, argv[i]);
			sprintf(start_msg, "%s %s", start_msg, argv[i]);
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
		else
		{
			fError = true;
			break;
		}
	}

	if (!fError && strlen(pricelistpfad) == 0)
	{
		printf("keine Eingabedatei angegeben\n");
		fError = true;
	}

	if (fError)
	{
		printf("  usage: %s\n\t"
			" { -file dateiname <Name der Eingabedatei> }\n\t"
			" { -db datenbankname <Datenbankname> }\n\t"
			" [ -ex <Explain> ]\n\t",
			argv[0]);
		return 1;
	}

	// get current date to use as default value for DATEFROM
	getCurrentDate( currentDate, LEN_FILE_DATEFROM + 1);

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

	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	if ( ( rc = StartLoadTables( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}

	if ( ( rc = AfterLoadTables(error_msg) ) != 0 )
	{
		PrintMsg(fun, "mit Fehler beendet", FEHL, rc);
		return 10;
	}

	sprintf(start_msg,"Discount: %d Saetze eingefuegt", zaehlerIns);
	PrintMsg( fun, start_msg, HINW, 0 );
	PrintMsg( fun, "korrekt beendet", HINW, rc );

	return 0;   
}
 
 /***** START LADEN DER PREISLISTE ************************************/

int StartLoadTables(char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StarteLadenPreisListe";
	char rec[512];
	char prevPharmGrp[LEN_FILE_PHARMACYGROUPID + 1];
	char prevArticleNo[LEN_FILE_ARTICLENO + 1];

	EXEC SQL BEGIN DECLARE SECTION;
	struct s_PRICELISTREC* pPriceListRec;
	char branchNo[LEN_FILE_BRANCHNO + 1];
	EXEC SQL END DECLARE SECTION;

	PrintMsg(fun, "gestartet", HINW, OK);

	pPriceListRec = (struct s_PRICELISTREC*) rec;

	if ((pricelistfile = fopen(pricelistpfad, "r")) == NULL)
	{
		PrintMsg(fun, pricelistpfad, FEHL, 0);
		PrintMsg(fun, "Inputdatei kann nicht geoeffnet werden", FEHL, 0);
		return -1;
	}

	strcpy(prevPharmGrp, "");
	strcpy(prevArticleNo, "");

	for ( zaehler = 0; ; zaehler++ )
	{
		if (fread(rec, sizeof(struct s_PRICELISTREC) + 1, 1, pricelistfile) == 0)
		{
			break;
		}

		if ((rc = PreparePriceListRec(pPriceListRec, zaehler)) < 0)
		{
			return rc;
		}

		// haben wir den ersten Satz gelesen?
		if (zaehler == 0)
		{
			// --> Updatesign aller discount-Saetze fuer die Branch zuruecksetzen
			/* koennen wir erst machen, nachdem wir den ersten Satz gelesen haben 
			   und die Branch kennen (Voraussetzung: eine Branch pro Inputfile) */
			// wir merken uns die Branch des ersten Satzes
			strcpy(branchNo, pPriceListRec->BRANCHNO);
			// Updatesign fuer alle discount-Saetze der Branch zuruecksetzen
			if ((rc = ResetUpdateSignDiscount(branchNo, error_msg)) < 0)
			{
				return rc;
			}

			EXEC SQL begin work;
			ERROR_MSG("begin work(0):")
		}

		if (strcmp(pPriceListRec->BRANCHNO, branchNo) != 0)
		{
			char msg[512];
			sprintf(msg, "Satz #%d: neue Branch >%s< (vorherige Branch >%s<), mehrere Branches in Inputdatei nicht erlaubt", zaehler + 1, pPriceListRec->BRANCHNO, branchNo);
			PrintMsg(fun, msg, FEHL, OK);
			return -1;
		}

		if (   strcmp(pPriceListRec->PHARMACYGROUPID, prevPharmGrp) != 0
			|| strcmp(pPriceListRec->ARTICLENO, prevArticleNo) != 0)
		{
			// Aenderungen fuer den vorherigen Artikel committen
   		    EXEC SQL commit work;
			ERROR_MSG("commit work:")

			EXEC SQL begin work;
			ERROR_MSG("begin work:")

			// discount-Eintraege des aktuellen Artikel loeschen
			// --> werden durch die neuen Eintraege aus der Inputdatei ersetzt
			EXEC SQL EXECUTE del_discount using
				:pPriceListRec->BRANCHNO,
				:pPriceListRec->ARTICLENO,
				:pPriceListRec->PHARMACYGROUPID;
			ERROR_MSG("delete price list entries")

			strcpy(prevPharmGrp, pPriceListRec->PHARMACYGROUPID);
			strcpy(prevArticleNo, pPriceListRec->ARTICLENO);
		}

		EXEC SQL EXECUTE ins_discount using
			:pPriceListRec->BRANCHNO,
			:pPriceListRec->ARTICLENO,
			:pPriceListRec->PHARMACYGROUPID,
			:pPriceListRec->DATEFROM,
			:pPriceListRec->DATETO,
			:pPriceListRec->QUANTITY,
			:pPriceListRec->FIXEDPRICE,
			:pPriceListRec->DISCOUNTSPEC,
			:pPriceListRec->DISCOUNTTYPE;
		ERROR_MSG("insert price list entry")
		zaehlerIns++;

        if ( explain == YES && zaehler > 5000 ) break;   /* Nur 5000 Saetze verarbeiten */
	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG("commit work(0):")

	// jetzt alle discount-Eintraege der verarbeiteten Branch loeschen, deren
    // UpdateSign nicht gesetzt ist
	// --> loescht die discount-Eintraege zu Artikeln, fuer die kein neuer Preis 
	//     geliefert wurde
	if ((rc = DeleteDiscountNotUpdated(branchNo, error_msg)) < 0)
	{
		return rc;
	}

	sprintf( error_msg, "%d Saetze geladen", zaehler );
	PrintMsg( fun, error_msg, HINW, OK );

	printf("loadpricelist: %s\n", error_msg);
	fflush(stdout);

	fclose(pricelistfile);

	if ( explain == YES ) return OK;

	return rc;
}

/***** PREISLISTEN-EINTRAG AUFBEREITEN *******************************************************/

int PreparePriceListRec(struct s_PRICELISTREC* pPriceListRec, int recno)
{
	char *fun = "PreparePriceListRec";
	int rc = 0;
	char msg[80];
	int fld_len = 0;
	char *fld_name = NULL;
	char *fld_val = NULL;
	char *pch = NULL;

	// sanity check: pruefe, ob jedes Feld mit einem Feldseparator (';') abgeschlossen wird
	for (int i = 0; i < NUMBER_OF_FIELDS; i++)
	{
		switch (i)
		{
		case 0:
			fld_val = pPriceListRec->BRANCHNO;
			fld_name = "BRANCHNO";
			fld_len = LEN_FILE_BRANCHNO;
			break;
		case 1:
			fld_val = pPriceListRec->PHARMACYGROUPID;
			fld_name = "PHARMACYGROUPID";
			fld_len = LEN_FILE_PHARMACYGROUPID;
			break;
		case 2:
			fld_val = pPriceListRec->ARTICLENO;
			fld_name = "ARTICLENO";
			fld_len = LEN_FILE_ARTICLENO;
			break;
		case 3:
			fld_val = pPriceListRec->DISCOUNTTYPE;
			fld_name = "DISCOUNTTYPE";
			fld_len = LEN_FILE_DISCOUNTTYPE;
			break;
		case 4:
			fld_val = pPriceListRec->DISCOUNTSPEC;
			fld_name = "DISCOUNTSPEC";
			fld_len = LEN_FILE_DISCOUNTSPEC;
			break;
		case 5:
			fld_val = pPriceListRec->DATEFROM;
			fld_name = "DATEFROM";
			fld_len = LEN_FILE_DATEFROM;
			break;
		case 6:
			fld_val = pPriceListRec->DATETO;
			fld_name = "DATETO";
			fld_len = LEN_FILE_DATETO;
			break;
		case 7:
			fld_val = pPriceListRec->QUANTITY;
			fld_name = "QUANTITY";
			fld_len = LEN_FILE_QUANTITY;
			break;
		case 8:
			fld_val = pPriceListRec->FIXEDPRICE;
			fld_name = "FIXEDPRICE";
			fld_len = LEN_FILE_FIXEDPRICE;
			break;
		default:
			break;
		}

		if (fld_val[fld_len] == CHAR_FIELD_SEPARATOR)
		{
			// ersetze Feldseparator durch 0-Byte
			fld_val[fld_len] = '\0';
		}
		else
		{
			sprintf(msg, "Satz #%d: ungueltiger Separator nach %s", recno + 1, fld_name);
			PrintMsg(fun, msg, FEHL, 0);
			return -1;
		}
	}

	// fuer den Dezimalwert FIXEDPRICE ',' durch '.' ersetzen
	if ((pch = strchr(pPriceListRec->FIXEDPRICE, ',')) != NULL)
	{
		*pch = '.';
	}

	// check for empty value in DATEFROM
	// an empty value are 8 zeroes or 8 blanks or 7 blanks followed by one zero
	if (   strcmp(pPriceListRec->DATEFROM, "00000000") == 0
	    || strcmp(pPriceListRec->DATEFROM, "        ") == 0
	    || strcmp(pPriceListRec->DATEFROM, "       0") == 0)
	{
		// empty value is replaced by current date
		strcpy(pPriceListRec->DATEFROM, currentDate);
	}

	return 0;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;

	if ( ( rc = PrepareLoadPriceList( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadPriceListEntry(struct s_PRICELISTREC * pPriceListRec, char *error_msg)
{
	char *fun = "LoadPriceListEntry";
	int rc = OK;

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	// nothing to do

	return OK;
}

/*** PREPARE-LADE-KONDITIONEN ************************************************/

int PrepareLoadPriceList( char *error_msg )
{
	char *fun = "PrepareLoadPriceList";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "delete from discount ");
	strcat(str, "where branchno = ? ");
	strcat(str, "  and articleno = ? ");
	strcat(str, "  and pharmacygroupid = ? ");
	strcat(str, "  and updatesign = '0' ");

	exec sql prepare del_discount from : str;
	ERROR_MSG("prepare del_discount")

	strcpy(str, "insert into discount (");
	strcat(str, "BRANCHNO,");
	strcat(str, "ARTICLENO,");
	strcat(str, "PHARMACYGROUPID,");
	strcat(str, "DATEFROM,");
	strcat(str, "DATETO,");
	strcat(str, "BASEQTY,");
	strcat(str, "FIXEDPRICE,");
	strcat(str, "DISCOUNTSPEC,");
	strcat(str, "DISCOUNTTYPE,");
	strcat(str, "UPDATESIGN");
	/* the following columns need to be added because specific 
	   default values are needed for them */
	strcat(str, ", PHARMGRPEXCLUDED");
	strcat(str, ", INTERNALDISCOUNT");
	strcat(str, ", PHARMGRPEXCL_2");
	strcat(str, ", PHARMGRPEXCL_3");
	strcat(str, ", NO_MULTIPLE_QTY");
	strcat(str, ", ADDONDISCOUNTOK");
	strcat(str, ", PAYMENTTERMTYPE");
	strcat(str, ", TURNOVERCALCIMPACT");
	strcat(str, ", MONTHLYDISCOUNT");
	strcat(str, " ) values ( ");
	strcat(str, "?, ?, ?, ?, ?, ?, ?, ?, ?, '1'");
	/* constant default values for extra columns */
	strcat(str, ", '000'");      /* PHARMGRPEXCLUDED */
	strcat(str, ", '0'");        /* INTERNALDISCOUNT */
	strcat(str, ", '000'");      /* PHARMGRPEXCL_2 */
	strcat(str, ", '000'");      /* PHARMGRPEXCL_3 */
	strcat(str, ", '0'");        /* NO_MULTIPLE_QTY */
	strcat(str, ", '0'");        /* ADDONDISCOUNTOK */
	strcat(str, ", '0'");        /* PAYMENTTERMTYPE */
	strcat(str, ", '0'");        /* TURNOVERCALCIMPACT */
	strcat(str, ", '0'");        /* MONTHLYDISCOUNT */
	strcat(str, " )");

	exec sql prepare ins_discount from :str;
	ERROR_MSG( "prepare ins_discount" )

	return OK;      
}

/*** RESET-UPDATE-KENNZEICHNEN-DISCOUNT ************************************************/

int ResetUpdateSignDiscount(char *branchno, char *error_msg)
{
	char *fun = "ResetUpdateSignDiscount";
	int i;

	exec sql begin declare section;
	char str[2048];
	char *locBranch;
	exec sql end declare section;

	locBranch = branchno;

	strcpy(str, "select ");
	strcat(str, "articleno ");
	strcat(str, "from ");
	strcat(str, "discount ");
	strcat(str, "where branchno = ? ");
	strcat(str, "  and updatesign = '1' ");
	strcat(str, "for update ");

	exec sql prepare sel_updated from :str;
	ERROR_MSG("prepare sel_updated")
	exec sql declare Cselupdated cursor with hold for sel_updated;

	strcpy(str, "update discount ");
	strcat(str, "set updatesign = '0' ");
	strcat(str, "where current of Cselupdated ");

	exec sql prepare upd_updated from :str;
	ERROR_MSG("prepare upd_updated")

	exec sql open Cselupdated using :locBranch;
	ERROR_MSG("open Cselupdated")
	EXEC SQL begin work;
	ERROR_MSG("begin work(0):")

	for (i = 1;; i++)
	{
		if (i % 50 == 0)
		{
			exec sql commit work;
			ERROR_MSG("commit work:")
			exec sql begin work;
			ERROR_MSG("begin work:")
		}

		exec sql fetch Cselupdated into : lArticleNo;
		if (sqlca.sqlcode == 100) break;
		ERROR_MSG("fetch Cselupdated")

		exec sql execute upd_updated;
		ERROR_MSG("execute upd_updated")
	}

	EXEC SQL commit work;
	ERROR_MSG("commit work(0):")

	exec sql close Cselupdated;
	ERROR_MSG("close Csetnotupdated")

	return OK;
}

/*** LOESCHEN-DISCOUNT-NOT-UPDATED ************************************************/

int DeleteDiscountNotUpdated(char *branchno, char *error_msg)
{
	char *fun = "DeleteDiscountNotUpdated";
	int i;

	exec sql begin declare section;
	char str[2048];
	char *locBranchno;
	exec sql end declare section;

	locBranchno = branchno;

	strcpy(str, "select ");
	strcat(str, "articleno  ");
	strcat(str, "from ");
	strcat(str, "discount ");
	strcat(str, "where branchno = ? ");
	strcat(str, "and updatesign = '0' ");
	strcat(str, "for update ");

	exec sql prepare sel_notupdated from : str;
	ERROR_MSG("prepare sel_notupdated")
	exec sql declare Cselnotupdated cursor with hold for sel_notupdated;

	strcpy(str, "delete from discount ");
	strcat(str, "where current of Cselnotupdated ");

	exec sql prepare del_notupdated from : str;
	ERROR_MSG("prepare del_notupdated")

	exec sql open Cselnotupdated using :locBranchno;
	ERROR_MSG("open Cselnotupdated")
	EXEC SQL begin work;
	ERROR_MSG("begin work(0):")

	for (i = 1;; i++)
	{
		if (i % 50 == 0)
		{
			exec sql commit work;
			ERROR_MSG("commit work:")
			exec sql begin work;
			ERROR_MSG("begin work:")
		}
		exec sql fetch Cselnotupdated into :lArticleNo;
		if (sqlca.sqlcode == 100) break;
		ERROR_MSG("fetch Cselnotupdated")

		exec sql execute del_notupdated;
		ERROR_MSG("execute del_notupdated")
	}

	EXEC SQL commit work;
	ERROR_MSG("commit work(0):")

	exec sql close Cselnotupdated;
	ERROR_MSG("close Cselnotupdated")

	return OK;
}

/***** AFTER-LADE-KONDITIONEN *********************************************/

int AfterLadeKonditionen( char *error_msg )
{
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

void getCurrentDate ( char *datebuf, int buflen )
{
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (datebuf, buflen, "%Y%m%d", timeinfo);
}

/***** ENDE *****************************************************************/

/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tpldlokalart"

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
#include <string.h>
#include <unistd.h>
#include "tabellen.h"
#include "deakz.h"
#include "countrycodes.h"
#include "pplib/allg.h"
#include "libtpld/define.h"
#include <libtpld/qsort.h>
#include <libtpld/hsystfkt.h>
#include <libtpld/vtcodum.h>
#include <dirent.h>                                     
#include <errno.h>                                     

exec sql include sqlca;
exec sql include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define ERROR_MSG2(x,y)       if(sqlca.sqlcode<0) { \
                              sprintf(error_msg,"%s %d/%d bei PZN: %7.7s %s",x,\
							  sqlca.sqlcode, sqlca.sqlerrd[1],y,sqlca.sqlerrm ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define NOTFOUND           sqlca.sqlcode == SQLNOTFOUND

//#define OK                   0
//#define NO                   0
//#define YES                  1
//#define ERROR               -1
#define INSERT               1
//#define NOT_FOUND            1
//#define FILE_NOT_FOUND       1
//#define WARNING             -2
#define HINW               'H'
#define FEHL               'F'
//#define RIO_EOF            110
//#define RIO_NOFIND         111
//#define DATABASE           "phosix@db2_rmfuze1_shm"
//#define BLANC              ' '
//#define STR_ENDE           '\0'
//#define L_TEXT             81
//#define SQLCODE            sqlca.sqlcode
//#define SQLERRM            sqlca.sqlerrm
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */
//#define MAX_CH_ARTIKELNAME 26

FILE *lokaldat;
struct O_DEAKZ artikel;
static const int DEAKZ_LEN = sizeof(artikel);
char log_file [300 + 1];
char lagerort[9];
char  dateiname[L_TEXT];
int debug_enabled  = NO;
long datum ;
int explain = NO;
int filialnr = 99;
int bestandupdate = NO;
int sichern = NO;
int Frankreich = NO;
int Prewhole = NO;
int NoLokal = NO;
int Schweiz = NO;
int zaehlerInslokal = 0;     /* weil ich zu faul war alex */
int zaehlerUpdlokal = 0;     /* weil ich zu faul war alex */
int zaehlerDellokal = 0;     /* weil ich zu faul war alex */
int zaehlerInsort = 0;     /* weil ich zu faul war alex */
int zaehlerUpdort = 0;     /* weil ich zu faul war alex */
int zaehlerDelort = 0;     /* weil ich zu faul war alex */
long bestErr = 0;
long BestandLogAnz = 999999;
int parametertab[20];
long RestBestand = 0;
int i24 = NO;

exec sql begin declare section;
countrycodesS CCode;
exec sql end declare section;

/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
int StarteLadenDerArtikelRelationen( char *error_msg);
int PrepareLoadTables          (char *error_msg);
int LoadTables                 (struct O_DEAKZ *art, char *error_msg);
int AfterLoadTables            (char *error_msg);
int PrepareFetchCountryCodes   (char *error_msg);
int PrepareLadeArtikelLokal    (char *error_msg);
int PrepareLadeArtikelLagerort (char *error_msg);
//int PrepareLadeIBTBranchArticleConfig	   (char *error_msg);
int PrepareLesePositionen	   (char *error_msg);
int PrepareLeseZentralBusinessType	   (char *error_msg);
int LadeArtikelLokal           ( struct O_DEAKZ *art, char *error_msg);
int LadeArtikelLagerort        ( struct O_DEAKZ *art, char *error_msg);
//int LadeIBTBranchArticleConfig ( struct O_DEAKZ *art, char *error_msg);
int AfterLadeArtikelLokal      ( char *error_msg);
int AfterLadeArtikelLagerort   ( char *error_msg);
int HolePseudoLagerorte        ( char *error_msg);
int SaveFile					();
int CompressFile				();
int DeleteFiles					();
int CloseDatabase( void );
int LoadParameter          (char *error_msg);
static int PruefeNachfolgeArtikel( void );
static int PreparPruefeNachfolgeArtikel( void );
int LadeArtikelaltern( struct O_DEAKZ *art, char *error_msg );
int PrepareLadeArtikelaltern( char *error_msg );
int AfterLadeArtikelaltern   ( char *error_msg);

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
	char  start_msg[121];
	int   status = 0;

	exec sql begin declare section;
	char datenbank[60];
	exec sql end declare section;

	setbuf(stdout,0);

	sprintf(datenbank,"%s",DATABASE);

	strcpy(start_msg, "gestartet mit:");
	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-dg" ) )
		{
			strcat(start_msg, " -dg");
			debug_enabled = YES;
		}
		else if ( !strcmp( schalter, "-save" ) )
		{
			strcat(start_msg, " -save");
			sichern = YES;
		}
		else if ( !strcmp( schalter, "-file" ) )
		{
			strcat(start_msg, " -file");
			i++;
			sprintf( dateiname, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
			status = 1;
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			strcat(start_msg, " -db");
			i++;
			sprintf( datenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-berr" ) )
		{
			strcat(start_msg, " -berr");
			i++;
			BestandLogAnz = atol( argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-ex" ) )
		{
			strcat(start_msg, " -ex");
			explain = YES;
		}
		else if ( !strcmp( schalter, "-bu" ) )
		{
			strcat(start_msg, " -bu");
			bestandupdate = YES;
		}
		else if ( !strcmp( schalter, "-fr" ) )
		{
			strcat(start_msg, " -fr");
			Frankreich = YES;
		}
		else if ( !strcmp( schalter, "-nolok" ) )
		{
			strcat(start_msg, " -nolok");
			NoLokal = YES;
		}
		else if ( !strcmp( schalter, "-ch" ) )
		{
			strcat(start_msg, " -ch");
			Schweiz = YES;
		}
		else if ( !strcmp( schalter, "-pf" ) )
		{
			strcat(start_msg, " -pf");
			Prewhole = YES;
		}
		else if ( !strcmp( schalter, "-h24" ) )
		{   
			i24 = YES;
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
		else
		{
			printf( "  usage: %s\n\t"
				" { -file dateiname <Dateiname> }\n\t"
				" { -db datenbankname <Datenbankname> }\n\t"
				" { -bu <Bestandupdate> }\n\t"
				" { -berr anzahl <Bestanddifferenzen> }\n\t"
				" { -dg <Debugging> }\n\t"
				" { -save <Ladedatei sichern> }\n\t"
				" [ -ex <Explain> ]\n\t",
				argv[0] );
			return 1;
		}
	}
	if(status == 0)
	{
		printf( "  usage: %s\n\t"
			" { -file dateiname <Dateiname> }\n\t"
			" { -db datenbankname <Datenbankname> }\n\t"
			" { -bu <Bestandupdate> }\n\t"
			" { -dg <Debugging> }\n\t"
			" { -save <Ladedatei sichern> }\n\t"
			" [ -ex <Explain> ]\n\t",
			argv[0] );
		return 1;
	}
	filialnr = atoi(dateiname+strlen(dateiname)-2);
	if(filialnr == 93) filialnr = 48;
	else if(filialnr == 90) filialnr = 36; /* Test Toulon neu */
	if ( ( lokaldat = fopen( dateiname, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( "tpldlokalart ", "Ladedatei nicht vorhanden", FEHL, 0 );
		return -1;
	}
      

	if ( ( LOG_PATH = getenv("LOG_PATH")) == (char *)0 )
		strcpy( logpath, "." );
	else
		strcpy( logpath, LOG_PATH );
   
	sprintf( log_file, "%s/%s", logpath, LOG_FILE );

	PrintMsg( fun, start_msg, HINW, 0 );
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
   
	if ( ( rc = StarteLadenDerArtikelRelationen( error_msg ) ) != 0 )
	{
		sprintf(start_msg, "Fili: %d %s ",filialnr,fun);
		PrintMsg( start_msg, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	sprintf(start_msg, "Fili: %d %s ",filialnr,fun);
	PrintMsg( start_msg, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER ARTIKEL-TABELLEN ************************************/

int StarteLadenDerArtikelRelationen( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  idx;
	int  ende = NO;
	char huelse[20];
	char *fun = "StarteLadenDerArtikelRelationen";

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	while ( !ende  )
	{
		if(fread( (struct O_DEAKZ*) &artikel ,DEAKZ_LEN+1, 1 , lokaldat ) == 0)
			break;

		for(idx = 0; idx < DEAKZ_LEN; idx++)
		{
//			CheckAbdruckbar( (unsigned char*)&artikel + idx );
		}
		if ( zaehler == 0 )
		{
/*			sprintf( huelse, "%*.*s",
				L_DEAKZ_AKZFIL,
				L_DEAKZ_AKZFIL,
				artikel.AKZFIL );
			filialnr = atoi(huelse);
			*/

			HolePseudoLagerorte(error_msg);
			if ( LoadParameter( error_msg ) != OK )
				return 10;  
		}
		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }
        if ( zaehler % 1000 == 0 )
        {
           DEBUG_SECTION
           sprintf( error_msg, "%d Saetze geladen", zaehler );
           PrintMsg( fun, error_msg, HINW, OK );
           END_DEBUG_SECTION
        }
            
        if ( ( rc = LoadTables( &artikel, error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
        else if ( explain == YES )
           if ( zaehler > 100 ) break;   /* Nur 100 Saetze verarbeiten */

	}      /* ende while */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	sprintf( error_msg, "Fili: %d Artikellokal ins/upd/del: %d/%d/%d",filialnr, zaehlerInslokal, zaehlerUpdlokal, zaehlerDellokal );
	PrintMsg( fun, error_msg, HINW, OK );
	sprintf( error_msg, "Fili: %d Artikellagerort ins/upd/del: %d/%d/%d",filialnr, zaehlerInsort, zaehlerUpdort, zaehlerDelort );
	PrintMsg( fun, error_msg, HINW, OK );
   
	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc;

	if(Prewhole)
	{
		if ( ( rc = PrepareLeseZentralBusinessType( error_msg ) ) < 0 ) return rc;
	}
	if(Frankreich)
	{
		if ( ( rc = PrepareFetchCountryCodes( error_msg ) ) < 0 ) return rc;
	}
	if(NoLokal == NO)
	{
		if ( ( rc = PrepareLadeArtikelLokal( error_msg ) ) < 0 ) return rc;
	}
	if ( ( rc = PrepareLadeArtikelLagerort( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeArtikelaltern( error_msg ) ) < 0 ) return rc;
//	if ( ( rc = PrepareLadeIBTBranchArticleConfig( error_msg ) ) < 0 ) return rc;
 	if(i24 == YES)
 	{
 		if ( ( rc = PrepareLesePositionen( error_msg ) ) < 0 ) return rc;
 	}

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(struct O_DEAKZ *art, char *error_msg)
{
	int rc = OK;
	char *fun = "LoadTables";
	exec sql begin declare section;
	struct O_DEAKZ   *a;
	long lArtNr;
	exec sql end declare section;

	a = art;

	/* neue Tabellen schreiben */
	if(Prewhole)
	{
		/* In Prewhole Frankreich momentan nur businesstype 1 versorgen */
		exec sql open Cselzent using :a->AKZPZN;
		ERROR_MSG2( "open Cselzent", a->AKZPZN )
		exec sql fetch Cselzent into :lArtNr;
		ERROR_MSG2( "fetch Cselzent", a->AKZPZN )
		if ( sqlca.sqlcode == 100 ) return OK;
	}
	if(NoLokal == NO)
	{
		if ( (rc = LadeArtikelLokal(art, error_msg)) < 0) return rc;
	}
	if ( (rc = LadeArtikelLagerort(art, error_msg)) < 0) return rc;
	if ( (rc = LadeArtikelaltern(art, error_msg)) < 0) return rc;
//	if ( (rc = LadeIBTBranchArticleConfig(art, error_msg)) < 0) return rc;

	return OK;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc;
	if(NoLokal == NO)
	{
		if ( (rc = AfterLadeArtikelLokal(error_msg)) < 0) return rc;
	}
	if ( (rc = AfterLadeArtikelLagerort(error_msg)) < 0) return rc;
	if ( (rc = AfterLadeArtikelaltern(error_msg)) < 0) return rc;
	if(sichern == YES)
	{
		SaveFile();
		CompressFile();
		DeleteFiles();
	}

	return OK;
}

/*** PREPARE-FETCH-INFO-CODES ************************************************/

int PrepareFetchCountryCodes( char *error_msg )
{
	char *fun = "PrepareFetchCountryCodes";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, COUNTRYCODES_PELISTE );
	strcat( str, " from countrycodes" );
	strcat( str, " where infocode = ?" );
	strcat( str, " and branchno = ?" );

	exec sql prepare dec_countrycodes from :str;
	ERROR_MSG( "prepare dec_countrycodes" )
	exec sql declare Ccountrycodes cursor for dec_countrycodes;
	
	return OK;
}

/*** PREPARE-LESE-POSITIONEN ************************************************/

int PrepareLesePositionen( char *error_msg )
{
 	char *fun = "PrepareLesePositionen";
 
 	exec sql begin declare section;
 	char str[2048];
 	exec sql end declare section;
 
 	strcpy( str, "select " );
 	strcat( str, "nvl(sum(p.mengegeliefert),0) " );
 	strcat( str, "from kdauftrag k,kdauftragpos p " );
 	strcat( str, "where k.filialnr = ? " );
 	strcat( str, "and p.artikel_nr = ? " );
 	strcat( str, "and k.kdauftragstat[5] = '1' " );	/* erfasst */
 	strcat( str, "and k.kdauftragnr = p.kdauftragnr " );
 
 	exec sql prepare sel_pos from :str;
 	ERROR_MSG( "prepare dec_pos" )

// 	strcpy( str, "select " );
// 	strcat( str, "nvl(sum(p.mengegeliefert),0) " );
// 	strcat( str, "from kdauftrag k,kdauftragpos p " );
// 	strcat( str, "where k.filialnr = ? " );
// 	strcat( str, "and p.artikel_nr = ? " );
// 	strcat( str, "and k.kdauftragstat[9] != '1' " );	/* Fakturiert */
// 	strcat( str, "and k.kdauftragstat[10] != '1' " );	/* Storniert */
// 	strcat( str, "and k.kdauftragnr = p.kdauftragnr " );
// 	strcat( str, "and k.datumauslieferung = 0" );
// 
// 	exec sql prepare sel_pos from :str;
// 	ERROR_MSG( "prepare dec_pos" )
// 	
// 	strcpy( str, "select " );
// 	strcat( str, "nvl(sum(p.mengeabgebucht),0) " );
// 	strcat( str, "from kdverbund k,kdverbundpos p " );
// 	strcat( str, "where k.filialnr = ? " );
// 	strcat( str, "and p.artikel_nr = ? " );
// 	strcat( str, "and k.vbstatus != '5' " );	/* Fakturiert */
// 	strcat( str, "and k.vbstatus != '4' " );	/* Storniert */
// 	strcat( str, "and p.processingstatus != '2' " );	/* Verarbeitet */
// 	strcat( str, "and k.kdauftragnr = p.kdauftragnr " );
// 	strcat( str, "and k.filialnr = p.filialnr " );
// 
// 	exec sql prepare sel_vb from :str;
// 	ERROR_MSG( "prepare dec_vb" )
// 	
 	return OK;
}

/*** PREPARE-LESE-ZENTRAL_BUSINESSTYPE ************************************************/

int PrepareLeseZentralBusinessType( char *error_msg )
{
	char *fun = "PrepareLeseZentralBusinessType";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select " );
	strcat( str, "artikel_nr " );
	strcat( str, "from artikelzentral " );
	strcat( str, "where artikel_nr = ? " );
	strcat( str, "and businesstypeno = '1' " );

	exec sql prepare dec_zent from :str;
	ERROR_MSG( "prepare dec_zent" )
	exec sql declare Cselzent cursor for dec_zent;
	
	return OK;
}

/*** PREPARE-LADE-ARTIKEL-LOKAL ************************************************/

int PrepareLadeArtikelLokal( char *error_msg )
{
	char *fun = "PrepareLadeArtikelLokal";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "insert into stockentry (" );
	strcat( str, "DATE, " );
	strcat( str, "BRANCHNO, " );
	strcat( str, "ARTICLENO " );
	strcat( str, ") values " );
	strcat( str, "( ?, ?, ? )" );
   
	exec sql prepare ins_stockentry from :str;
	ERROR_MSG( "prepare ins_stockentry" )
 
	/*CPR-210210 WAFOTYP wird nicht mehr vom Host geladen mit Ausnahme in der
	*            Schweiz. Deshalb ist die Parameterliste für Insert und Update
	*/           
	strcpy(str, "insert into artikellokal (" );
	if (Schweiz)
	{
		strcat(str, ARTIKELLOKAL_PELISTE_ALL);
	}
	else
	{
		strcat(str, ARTIKELLOKAL_PELISTE);
	}
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?," );
	if (Schweiz)
	{
		strcat(str, "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )");
	}
	else
	{
		strcat(str, "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )");
	}
   
	exec sql prepare ins_artikellok from :str;
	ERROR_MSG( "prepare ins_artikellok" )
 
	strcpy( str, "select " );
	strcat( str, ARTIKELLOKAL_PELISTE_ALL );
	strcat( str, " from artikellokal" );
	strcat( str, " where artikel_nr = ?" );
	strcat( str, " and filialnr = ?" );
	strcat( str, " for update " );

	exec sql prepare dec_artikellok from :str;
	ERROR_MSG( "prepare dec_artikellok" )
	exec sql declare Cupdartikellok cursor for dec_artikellok;
	
	strcpy( str, "update artikellokal set " );
	strcat( str, "BESTAND = ?," );            
	strcat( str, "NACHFRAGE = ?," );           
	strcat( str, "ZUZAHLUNG = ?," );          
	strcat( str, "RABATTFAEHIG = ?," );           
	strcat( str, "NATRASTAFFELNR = ?," );               
	strcat( str, "PRISOART = ?," );          
	strcat( str, "ARTIKELAKTIV = ?," );          
	strcat( str, "LAGERBEREICHNR = ?," );         
	strcat( str, "STATIONNR = ?," );           
	strcat( str, "LAGERFACHNR = ?," );         
	strcat( str, "VERBUNDARTIKEL = ?," );                    
	strcat( str, "ETARTSCHALTER1 = ?," );        
	strcat( str, "ETARTSCHALTER2 = ?," );        
	strcat( str, "ETARTSCHALTER3 = ?," );        
	strcat( str, "ETARTSCHALTER4 = ?," );        
	strcat( str, "ETARTSCHALTER5 = ?," );        
	strcat( str, "VERKAUFEINHEIT = ?," );        
	strcat( str, "CONTAINERGROESSE = ?," );        
	strcat( str, "KONTIGENTMENGE = ?," );        
	strcat( str, "CHARGENARTIKEL = ?," );        
	strcat( str, "TEXTKEY = ?," );
	strcat( str, "BESTANDRESERVIERT = ?," ); 
	if (Schweiz)
	{
		strcat(str, "WAFOTYP = ?,");     // CPR-210210 WOFOTYP = CDM csubsequentdeliverybrancharticleconfig.subsequentdelivery - config from host eliminated   
	}
	strcat( str, "KZRANGE = ?," );        
	strcat( str, "MORECONDITIONS = ?," );        
	strcat( str, "BESTANDTAGESANFANG = ?," );        
	strcat( str, "CODEBLOCAGE = ?,");
	strcat( str, "BLOCKEDFORRETURNS = ? " );
	strcat( str, "where current of Cupdartikellok" );
	  
	exec sql prepare upd_artikellok from :str;
	ERROR_MSG( "prepare upd_artikellok" )
   
	strcpy( str, "delete from artikellokal " );
	strcat( str, "where current of Cupdartikellok" );
	  
	exec sql prepare del_artikellok from :str;
	ERROR_MSG( "prepare del_artikellok" )
   
	strcpy( str, "select" );
	strcat( str, " reservedqty" );
	strcat( str, " from articlereservation" );
	strcat( str, " where articleno = ?" );
	strcat( str, " and branchno = ?" );
	strcat( str, " and reservtype = 2" );
	strcat( str, " for update " );

	exec sql prepare dec_artreserv2 from :str;
	ERROR_MSG( "prepare dec_artreserv2" )
	exec sql declare Cupdartreserv2 cursor for dec_artreserv2;
	
	strcpy( str, "select" );
	strcat( str, " reservedqty" );
	strcat( str, " from articlereservation" );
	strcat( str, " where articleno = ?" );
	strcat( str, " and branchno = ?" );
	strcat( str, " and reservtype = 0" );
	strcat( str, " for update " );

	exec sql prepare dec_artreserv from :str;
	ERROR_MSG( "prepare dec_artreserv" )
	exec sql declare Cupdartreserv cursor for dec_artreserv;
	
	strcpy( str, "select" );
	strcat( str, " nvl(sum(reservedqty),0)" );
	strcat( str, " from articlereservation" );
	strcat( str, " where articleno = ?" );
	strcat( str, " and branchno = ?" );
	strcat( str, " and reservtype not in (0,2)" );

	exec sql prepare sel_artreserv from :str;
	ERROR_MSG( "prepare sel_artreserv" )
	
	strcpy( str, "update articlereservation set " );
	strcat( str, "reservedqty = ? " );            
	strcat( str, "where current of Cupdartreserv" );
	  
	exec sql prepare upd_artreserv from :str;
	ERROR_MSG( "prepare upd_artreserv" )

	strcpy( str, "select" );
	strcat( str, " nvl(sum(reservedqty),0)" );
	strcat( str, " reservedqty" );
	strcat( str, " from cststockreserved" );
	strcat( str, " where articleno = ?" );
	strcat( str, " and branchno = ?" );

	exec sql prepare sel_cststock from :str;
	ERROR_MSG( "prepare sel_cststock" )
	
	return OK;
}

/*** PREPARE-LADE-ARTIKEL-LAGERORT ***********************************************/

int PrepareLadeArtikelLagerort( char *error_msg )
{
	char *fun = "PrepareLadeArtikelLagerort";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "insert into artikellagerort ( " );
	strcat( str, ARTIKELLAGERORT_PELISTE );          
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ? )" );
   
	exec sql prepare ins_artlago from :str;
	ERROR_MSG( "prepare ins_artlago" )
   
	strcpy( str, "select " );
	strcat( str, ARTIKELLAGERORT_PELISTE );
	strcat( str, " from artikellagerort " );
	strcat( str, "where filialnr = ? and artikel_nr = ? " );
	strcat( str, "for update " );

	exec sql prepare dec_artikellag from :str;
	ERROR_MSG( "prepare dec_artikellag" )
	exec sql declare Cupdartikellag cursor for dec_artikellag;
	
	strcpy( str, "update artikellagerort set " );
	strcat( str, "LAGERBEREICHNR = ?," );          
	strcat( str, "STATIONNR = ?," );          
	strcat( str, "LAGERFACHNR = ?," );          
	strcat( str, "DATUMVERFALL = ?," );          
	strcat( str, "BESTAND = ?," );          
	strcat( str, "VERBUNDARTIKEL = ? " );          
	strcat( str, "where current of Cupdartikellag" );

	exec sql prepare upd_artlago from :str;
	ERROR_MSG( "prepare upd_artlago" )
	
	strcpy( str, "delete from artikellagerort " );
	strcat( str, "where current of Cupdartikellag" );

	exec sql prepare del_artlago from :str;
	ERROR_MSG( "prepare del_artlago" )
   
	return OK;      
}

/*** LADE-ARTIKEL-LOKAL *********************************************************/

int LadeArtikelLokal(struct O_DEAKZ *art, char *error_msg)
{
	exec sql begin declare section;
	struct O_DEAKZ   *a;
	struct ARTIKELLOKAL   i;							 /* wegen vergleich     */
	long lDatum;
	short filiale;
	long reservedbestand;
	long lVsebestand;
//	long lVBPosMenge;
	long lKDPosMenge;
	long lNeueMenge;
	long lCstMenge;
	short sBlockedForReturns;
	exec sql end declare section;

	char huelse[20];
	long lDBbestand;
	char *fun = "LadeArtikelLokal";
   
	a = art;
	filiale = filialnr;

	exec sql open Cupdartikellok using :a->AKZPZN, :filiale;
	ERROR_MSG2( "open Cupdartikellok", a->AKZPZN )
	  
	if(Frankreich)
	{
		exec sql open Ccountrycodes using :a->AKZCBL, :filiale;
		ERROR_MSG2( "open Ccountrycodes", a->AKZCBL )
		exec sql fetch Ccountrycodes into :CCode;
		ERROR_MSG2( "fetch Ccountrycodes", a->AKZCBL )
	}
	  
	exec sql fetch Cupdartikellok into :i;
	ERROR_MSG2( "fetch Cupdartikellok", a->AKZPZN )

	i.ETARTSCHALTER1 = 0;
/*	if ( a->AKZET2[0] == 'J' )   i.ETARTSCHALTER1 += 32768; */
/*	if ( a->AKZET2[1] == 'J' )   i.ETARTSCHALTER1 += 16384; */
	if ( a->AKZET2[2] == 'J' )   i.ETARTSCHALTER1 += 8192;
/*	if ( a->AKZET2[3] == 'J' )   i.ETARTSCHALTER1 += 4096; */
	if ( a->AKZET2[4] == 'J' )   i.ETARTSCHALTER1 += 2048;
/*	if ( a->AKZET2[5] == 'J' )   i.ETARTSCHALTER1 += 1024; */
	if ( a->AKZET2[6] == 'J' )   i.ETARTSCHALTER1 += 512;
	if ( a->AKZET2[7] == 'J' )   i.ETARTSCHALTER1 += 256;
	if ( a->AKZET2[8] == 'J' )   i.ETARTSCHALTER1 += 128;	/* kuehl08 */
	if ( a->AKZET2[9] == 'J' )   i.ETARTSCHALTER1 += 64;	/* kuehl20 */
	if ( a->AKZET2[10] == 'J' )   i.ETARTSCHALTER1 += 32;	/* Kuehlkette */
	if ( a->AKZET2[11] == 'J' )   i.ETARTSCHALTER1 += 16;
	if ( a->AKZET2[12] == 'J' )  i.ETARTSCHALTER1 += 8;
/*	if ( a->AKZET2[13] == 'J' )   i.ETARTSCHALTER1 += 4; */
/*	if ( a->AKZET2[14] == 'J' )   i.ETARTSCHALTER1 += 2; */
	if ( a->AKZET2[15] == 'J' )  i.ETARTSCHALTER1 += 1;
   	    
	i.ETARTSCHALTER2 = 0;
	if ( a->AKZET3[3] == 'J' )   i.ETARTSCHALTER2 += 4096;
	if ( a->AKZET3[5] == 'J' )   i.ETARTSCHALTER2 += 1024;
	if ( a->AKZET3[6] == 'J' )   i.ETARTSCHALTER2 += 512;
	if ( a->AKZET3[7] == 'J' )   i.ETARTSCHALTER2 += 256;
	if ( a->AKZET3[9] == 'J' )   i.ETARTSCHALTER2 += 64;
	if ( a->AKZET3[10] == 'J' )  i.ETARTSCHALTER2 += 32;
	if ( a->AKZET3[11] == 'J' )  i.ETARTSCHALTER2 += 16;
	if ( a->AKZET3[12] == 'J' )  i.ETARTSCHALTER2 += 8;
	if ( a->AKZET3[13] == 'J' )  i.ETARTSCHALTER2 += 4;
	if ( a->AKZET3[14] == 'J' )  i.ETARTSCHALTER2 += 2;
   	  
	if ( strncmp( a->AKZLGFNR, lagerort, 8 ) )
	{
		i.ETARTSCHALTER2 += 1;
		i.ARTIKELAKTIV[0] = '1'; /* beim urladen immer aktiv */
	}
	else
		i.ARTIKELAKTIV[0] = '2'; /* beim urladen immer aktiv */
   
	if ( a->AKZSPERR[0] == 'J' )  i.ARTIKELAKTIV[0] = '0'; 
	if ( a->AKZLOESCH[0] == 'J' )    i.ARTIKELAKTIV[0] = '0'; 

	i.ETARTSCHALTER3 = 0;
	if ( a->AKZET4[0] == 'J' )  i.ETARTSCHALTER3 += 32768;
	if ( a->AKZET4[1] == 'J' )  i.ETARTSCHALTER3 += 16384;
	if ( a->AKZET4[2] == 'J' )  i.ETARTSCHALTER3 += 8192;
	if ( a->AKZET4[3] == 'J' )  i.ETARTSCHALTER3 += 4096;
	if ( a->AKZET4[5] == 'J' )  i.ETARTSCHALTER3 += 1024;
	if ( a->AKZET4[6] == 'J' )  i.ETARTSCHALTER3 += 512;
   
	if ( strncmp( a->AKZNRTI, STR_NULL+1, L_DEAKZ_AKZNRTI ) )
		i.ETARTSCHALTER3 += 256;

	if ( a->AKZET4[8] == 'J')   i.ETARTSCHALTER3 += 128;
	if ( a->AKZET4[10] == 'J')  i.ETARTSCHALTER3 += 32;
	if ( a->AKZET4[11] == 'J')  i.ETARTSCHALTER3 += 16;
	if ( a->AKZET4[12] == 'J')  i.ETARTSCHALTER3 += 8;
	if ( a->AKZET4[13] == 'J')  i.ETARTSCHALTER3 += 4;
	if ( a->AKZET4[14] == 'J')  i.ETARTSCHALTER3 += 2;
	if ( a->AKZET4[15] == 'J')  i.ETARTSCHALTER3 += 1;
   
	i.ETARTSCHALTER4 = 0;
	if ( a->AKZA3[0]      == 'J') i.ETARTSCHALTER4 += 32768;
/*	if ( atol(a->AKZORPA) == 3 )  i->ETARTSCHALTER4 += 16384; */
/*	if ( a->AKZET5[2] == 'J')   i.ETARTSCHALTER4 += 8192; */
	if ( a->AKZAAA[0] == 'J')     i.ETARTSCHALTER4 += 4096;
/*	if ( a->AKZET5[4] == 'J')   i.ETARTSCHALTER4 += 2048; */
/*	if ( a->AKZET5[5] == 'J')   i.ETARTSCHALTER4 += 1024; */
	if ( a->AKZTFG[0] == 'J')	 i.ETARTSCHALTER4 += 512;
/*	if ( a->AKZET5[7] == 'J')   i.ETARTSCHALTER4 += 256; */
/*	if ( a->AKZET5[8] == 'J')   i.ETARTSCHALTER4 += 128; */
/*	if ( a->AKZET5[9] == 'J')   i.ETARTSCHALTER4 += 64; */
/*	if ( a->AKZET5[10] == 'J')   i.ETARTSCHALTER4 += 32; */
	if ( a->AKZFEUKL[0] == 'L' && a->AKZFEUKL[1] == ' ')   i.ETARTSCHALTER4 += 16;
	if ( a->AKZFEUKL[0] == 'F' && a->AKZFEUKL[1] == ' ')   i.ETARTSCHALTER4 += 8;
/*	if ( a->AKZET5[13] == 'J')   i.ETARTSCHALTER4 += 4; */
/*	if ( a->AKZNEKZ[0] == 'G')    i.ETARTSCHALTER4 += 2; */
	if ( a->AKZGEGU[0] == 'J')    i.ETARTSCHALTER4 += 1;
 
	i.ETARTSCHALTER5 = 0;
/*	if ( a->AKZEKS[0] == 'J' || a->AKZZEKS[0] == 'J')    i.ETARTSCHALTER5 += 32768; */
/*	if ( a->AKZZYTO[0] == 'J')    i.ETARTSCHALTER5 += 16384; */
/*	if ( a->AKZBSSG[0] == 'J')    i.ETARTSCHALTER5 += 1024; */
	if ( a->AKZVRIS[0] == 'J')    i.ETARTSCHALTER5 += 256;
	if ( a->AKZMIDAS[0] == 'J')   i.ETARTSCHALTER5 += 128;
	if ( a->AKZSHSTAT[0] == '4')  i.ETARTSCHALTER5 += 64;

	if( a->AKZVB[0] == 'J' || a->AKZVB[0] == 'G' || a->AKZVB[0] == 'T')
		i.VERBUNDARTIKEL[0] = '1';
	else if( a->AKZVB[0] == 'Z')	/* Privatsortiment */
		i.VERBUNDARTIKEL[0] = '2';
	else if( a->AKZVB[0] == 'R')	/* Veto	*/
		i.VERBUNDARTIKEL[0] = '3';
	else if( a->AKZVB[0] == 'A')	/* Regionalverbund	*/
		i.VERBUNDARTIKEL[0] = '4';
	else if( a->AKZVB[0] == 'B')	/* Nationalverbund	*/
		i.VERBUNDARTIKEL[0] = '5';
	else if( a->AKZVB[0] == 'C')	/* National + Regionalverbund	*/
		i.VERBUNDARTIKEL[0] = '6';
	else if( a->AKZVB[0] == 'D')	/* Lokal + Nationalverbund	*/
		i.VERBUNDARTIKEL[0] = '7';
	else if( a->AKZVB[0] == 'E')	/* Lokal + Regionalverbund	*/
		i.VERBUNDARTIKEL[0] = '8';
	else if( a->AKZVB[0] == 'F')	/* Lokal + Regional + Nationalverbund	*/
		i.VERBUNDARTIKEL[0] = '9';
	else if( a->AKZVB[0] == 'H')	/* Selbst kein Verbund beziehen , aber liefern */
		i.VERBUNDARTIKEL[0] = 'A';
	else
		i.VERBUNDARTIKEL[0] = '0';
	
	if( a->AKZCHARGE[0] == 'J')
		i.CHARGENARTIKEL[0] = '1';
	else
		i.CHARGENARTIKEL[0] = '0';
	
	
	if		( a->AKZPRISO[0] == 'L')	i.PRISOART[0] = '1';
	else if	( a->AKZPRISO[0] == 'Z')	i.PRISOART[0] = '2';
	else if	( a->AKZPRISO[0] == 'B')	i.PRISOART[0] = '3';
	else if	( a->AKZPRISO[0] == 'D')	i.PRISOART[0] = '4';
	else if	( a->AKZPRISO[0] == 'S')	i.PRISOART[0] = '5';
	else if	( a->AKZPRISO[0] == 'V')	i.PRISOART[0] = '6';
	else								i.PRISOART[0] = '0';   /* N */

	/* Natrastaffelnummer setzen */
	if ( strncmp( a->AKZNRTI, STR_NULL+1, L_DEAKZ_AKZNRTI ) )
	{
		sprintf( huelse, "%*.*s",
			L_DEAKZ_AKZPZN,
			L_DEAKZ_AKZPZN,
			a->AKZPZN );
		i.NATRASTAFFELNR = atoi(huelse);
	}
	else
		i.NATRASTAFFELNR = 0;
	sprintf(huelse,"%*.*s",L_DEAKZ_AKZKEYTXT,L_DEAKZ_AKZKEYTXT,a->AKZKEYTXT);
	i.TEXTKEY = atol(huelse);

	if(Frankreich)
	{
		if(CCode.ARTICLEACTIV[0] == '1') 
			i.ARTIKELAKTIV[0] = '1';
		else
			i.ARTIKELAKTIV[0] = '0';
		if(i.VERBUNDARTIKEL[0] != '0')
		{
			if(CCode.AUXDELIVERY[0] == '0')
			{
				i.VERBUNDARTIKEL[0] =  '0';
			}
		}
		if( a->AKZVB[0] == 'R')	/* Regionalverbund	*/
			i.VERBUNDARTIKEL[0] = '3';
	}

	if (a->AKZRESP[0] == '0' || a->AKZRESP[0] == 'N')	/* gesperrt für Retouren	*/
	{
		sBlockedForReturns = 0;
	}
	else
	{
		sBlockedForReturns = 1;
	}

	if (a->AKZNALI[0] == '8' || a->AKZNALI[0] == '1')
	{
		a->AKZNALI[0] = '1';
	}
	else
	{
		a->AKZNALI[0] = '0';
	}

DEBUG_SECTION
printf("#%d#\n",filiale);
printf("#%*.*s#\n",L_DEAKZ_AKZPZN,L_DEAKZ_AKZPZN,a->AKZPZN);
printf("#%d#\n",i.BESTAND);
printf("#%*.*s#\n",L_DEAKZ_AKZZUZA,L_DEAKZ_AKZZUZA,a->AKZZUZA);
printf("#%*.*s#\n",L_DEAKZ_AKZKRAB,L_DEAKZ_AKZKRAB,a->AKZKRAB);
printf("#%d#\n",i.NATRASTAFFELNR);
printf("#%1.1s#\n",i.PRISOART);
printf("#%1.1s#\n",i.ARTIKELAKTIV);
printf("#%*.*s#\n",L_DEAKZ_AKZLGNR,L_DEAKZ_AKZLGNR,a->AKZLGNR);
printf("#%*.*s#\n",L_DEAKZ_AKZSTAT,L_DEAKZ_AKZSTAT,a->AKZSTAT);
printf("#%*.*s#\n",L_DEAKZ_AKZLGFNR,L_DEAKZ_AKZLGFNR,a->AKZLGFNR);
printf("#%1.1s#\n",i.VERBUNDARTIKEL);
printf("#%*.*s#\n",L_DEAKZ_AKZBUE,L_DEAKZ_AKZBUE,a->AKZBUE);
printf("#%*.*s#\n",L_DEAKZ_AKZMINM,L_DEAKZ_AKZMINM,a->AKZMINM);
printf("#%*.*s#\n",L_DEAKZ_AKZNALI,L_DEAKZ_AKZNALI,a->AKZNALI);
END_DEBUG_SECTION
	sprintf(huelse,"%*.*s",L_DEAKZ_AKZBEST,L_DEAKZ_AKZBEST,a->AKZBEST);
	lVsebestand = atol(huelse);
	RestBestand = i.BESTAND;
	if ( sqlca.sqlcode == 0 )
	{
		if ( a->AKZSPERR[0] == 'J' )
		{
			exec sql execute del_artikellok;
			ERROR_MSG2( "execute del_artikellok", a->AKZPZN ) 
			zaehlerDellokal++;
			return 0;
		}
		if(bestandupdate == YES)
		{
			lNeueMenge = 0;
			if(i24 == YES)
			{
					exec sql execute sel_pos into :lKDPosMenge using :filiale,:a->AKZPZN;
					ERROR_MSG2( "select kdauftrag", a->AKZPZN )
					exec sql execute sel_cststock into :lCstMenge using :a->AKZPZN,:filiale;
					ERROR_MSG2( "select cstsockreserved", a->AKZPZN )
					lNeueMenge += lKDPosMenge + lCstMenge;
			}

			/* absolute Reservierung darf nicht veraendert werden. */
			exec sql open Cupdartreserv2 using :a->AKZPZN, :filiale;
			ERROR_MSG2( "open Cupdartreserv2", a->AKZPZN )
		  
			exec sql fetch Cupdartreserv2 into :reservedbestand;
			ERROR_MSG2( "fetch Cupdartreserv2", a->AKZPZN )
	
			if ( sqlca.sqlcode == 0 )
			{
				lNeueMenge += reservedbestand;
			}
			exec sql execute sel_artreserv into :reservedbestand using :a->AKZPZN, :filiale;
			ERROR_MSG2( "execute sel_artreserv", a->AKZPZN )
			if ( sqlca.sqlcode == 0 )
			{
				lNeueMenge += reservedbestand;
			}

			exec sql open Cupdartreserv using :a->AKZPZN, :filiale;
			ERROR_MSG2( "open Cupdartreserv", a->AKZPZN )
		  
			exec sql fetch Cupdartreserv into :reservedbestand;
			ERROR_MSG2( "fetch Cupdartreserv", a->AKZPZN )
	
			if ( sqlca.sqlcode == 0 )
			{
				if(lVsebestand < (reservedbestand + lNeueMenge))
				{
					int altreserved = (reservedbestand + lNeueMenge);
					reservedbestand = lVsebestand - lNeueMenge;
					if(reservedbestand < 0)
					{
						sprintf( error_msg, "BestandsFehler(reserviert/vse): %07d->%ld/%ld",
								i.ARTIKEL_NR,
								altreserved,
						/*		i.BESTANDRESERVIERT, */
								lVsebestand );
						PrintMsg( fun, error_msg, FEHL, -1 ); 	 
						reservedbestand = 0;
					}
					exec sql execute upd_artreserv using :reservedbestand;
					ERROR_MSG2( "execute upd_artreserv", a->AKZPZN ) 
				}
			}
			else
			{
				reservedbestand = 0;
			}

	
			lDBbestand = i.BESTAND + reservedbestand + lNeueMenge;
	
			if ( lVsebestand != lDBbestand )
			{
				RestBestand = lVsebestand - reservedbestand - lNeueMenge;
				if(RestBestand < 0)
				{
					sprintf( error_msg, "BestandsFehler(reserviert/vse): %07d->%ld/%ld",
							i.ARTIKEL_NR,
							i.BESTANDRESERVIERT,
							lVsebestand );
					PrintMsg( fun, error_msg, FEHL, -1 ); 	 
					RestBestand = 0;
				}

				if ( bestErr++ < BestandLogAnz )
				{
					sprintf( error_msg, "BestDiff(db/vs): %07d->%ld/%ld",
							i.ARTIKEL_NR,
							lDBbestand,
							lVsebestand );
					if ( i.ARTIKELAKTIV[0] != '0' )
						PrintMsg( fun, error_msg, FEHL, -1 ); 	 
					else PrintMsg( fun, error_msg, HINW, -1 ); 	 
				}
			}
			if(i.BESTAND == 0 && RestBestand > 0)
			{
				lDatum = AllgGetDate();
				EXEC SQL EXECUTE ins_stockentry USING
					:lDatum,
					:filiale,
					:a->AKZPZN;
				if (sqlca.sqlcode != -239)
				{
					ERROR_MSG2( "execute ins_stockentry", a->AKZPZN )
				}
			}
			i.BESTAND = RestBestand;
		}

		if (Schweiz)
		{
			exec sql execute upd_artikellok using
				:i.BESTAND,
				'0',
				:a->AKZZUZA,
				:a->AKZKRAB,
				:i.NATRASTAFFELNR,
				:i.PRISOART,
				:i.ARTIKELAKTIV,
				:a->AKZLGNR,
				:a->AKZSTAT,
				:a->AKZLGFNR,
				:i.VERBUNDARTIKEL,
				:i.ETARTSCHALTER1,
				:i.ETARTSCHALTER2,
				:i.ETARTSCHALTER3,
				:i.ETARTSCHALTER4,
				:i.ETARTSCHALTER5,
				:a->AKZBUE,
				:a->AKZMINM,
				'0',
				:i.CHARGENARTIKEL,
				:i.TEXTKEY,
				:i.BESTANDRESERVIERT,
				:a->AKZNALI, 
				'0',
				:i.MORECONDITIONS,
				:lVsebestand,
				:a->AKZCBL,
				:sBlockedForReturns
				;
		}
		else
		{
			exec sql execute upd_artikellok using
				:i.BESTAND,
				'0',
				:a->AKZZUZA,
				:a->AKZKRAB,
				:i.NATRASTAFFELNR,
				:i.PRISOART,
				:i.ARTIKELAKTIV,
				:a->AKZLGNR,
				:a->AKZSTAT,
				:a->AKZLGFNR,
				:i.VERBUNDARTIKEL,
				:i.ETARTSCHALTER1,
				:i.ETARTSCHALTER2,
				:i.ETARTSCHALTER3,
				:i.ETARTSCHALTER4,
				:i.ETARTSCHALTER5,
				:a->AKZBUE,
				:a->AKZMINM,
				'0',
				:i.CHARGENARTIKEL,
				:i.TEXTKEY,
				:i.BESTANDRESERVIERT,
				//:a->AKZNALI, CPR-210210 value received via loadbrancharticleconfig and not via host file
				'0',
				:i.MORECONDITIONS,
				:lVsebestand,
				:a->AKZCBL,
				:sBlockedForReturns
				;
		}

		ERROR_MSG2( "execute upd_artikellok", a->AKZPZN ) 
		zaehlerUpdlokal++;
		return 0;
	}

	sprintf(huelse,"%*.*s",L_DEAKZ_AKZBEST,L_DEAKZ_AKZBEST,a->AKZBEST);
	i.BESTAND = atol(huelse);

	if ( a->AKZSPERR[0] != 'J' )
	{
		if (Schweiz)
		{
			EXEC SQL EXECUTE ins_artikellok USING
				:filiale,
				:a->AKZPZN,
				:i.BESTAND,
				'0',
				:a->AKZZUZA,
				:a->AKZKRAB,
				:i.NATRASTAFFELNR,
				:i.PRISOART,
				:i.ARTIKELAKTIV,
				:a->AKZLGNR,
				:a->AKZSTAT,
				:a->AKZLGFNR,
				:i.VERBUNDARTIKEL,
				:i.ETARTSCHALTER1,
				:i.ETARTSCHALTER2,
				:i.ETARTSCHALTER3,
				:i.ETARTSCHALTER4,
				:i.ETARTSCHALTER5,
				:a->AKZBUE,
				:a->AKZMINM,
				'0',
				:i.CHARGENARTIKEL,
				:i.TEXTKEY,
				'0',
				:a->AKZNALI,
				'0',
				'0',
				:lVsebestand,
				:a->AKZCBL,
				:sBlockedForReturns
				;
		}
		else
		{
			EXEC SQL EXECUTE ins_artikellok USING
				:filiale,
				:a->AKZPZN,
				:i.BESTAND,
				'0',
				:a->AKZZUZA,
				:a->AKZKRAB,
				:i.NATRASTAFFELNR,
				:i.PRISOART,
				:i.ARTIKELAKTIV,
				:a->AKZLGNR,
				:a->AKZSTAT,
				:a->AKZLGFNR,
				:i.VERBUNDARTIKEL,
				:i.ETARTSCHALTER1,
				:i.ETARTSCHALTER2,
				:i.ETARTSCHALTER3,
				:i.ETARTSCHALTER4,
				:i.ETARTSCHALTER5,
				:a->AKZBUE,
				:a->AKZMINM,
				'0',
				:i.CHARGENARTIKEL,
				:i.TEXTKEY,
				'0',
				//:a->AKZNALI, CPR-210210 not maintained on host any further
				'0',
				'0',
				:lVsebestand,
				:a->AKZCBL,
				:sBlockedForReturns
				;
		}
		ERROR_MSG2( "insert Artikellokal", a->AKZPZN );
		zaehlerInslokal++;
	}

	return 0;
}

/*** LADE-ARTIKEL-LAGERORT ******************************************************/

int LadeArtikelLagerort( struct O_DEAKZ *art, char *error_msg )
{
	char *fun = "LadeArtikelLagerort";
	char huelse[20];
	int index;
	int fehler;

	exec sql begin declare section;
	struct O_DEAKZ   *a;
	struct ARTIKELLAGERORT   i;							 /* wegen vergleich     */
	char verbund[2];
	long etartklasse1;
	long etartschalter1;
	long etartschalter2;
	short filiale;
	exec sql end declare section;

	a = art;
	filiale = filialnr;


	if( a->AKZVB[0] == 'J' || a->AKZVB[0] == 'G' || a->AKZVB[0] == 'T')
		verbund[0] = '1';
	else if( a->AKZVB[0] == 'Z')
		verbund[0] = '1';
	else if( a->AKZVB[0] == 'R')	/* Regionalverbund	*/
		verbund[0] = '3';
	else
		verbund[0] = '0';

	exec sql select etartklasse1,etartschalter1,etartschalter2
		into :etartklasse1, :etartschalter1, :etartschalter2
		from artikelzentral
		where artikel_nr = :a->AKZPZN;
	ERROR_MSG2( "select artikelzentral", a->AKZPZN )

	if ( sqlca.sqlcode == 0 )
	{
		if (AllgBitleisteN((Bitleiste)etartklasse1,6) == 1 && parametertab[0] == 1)			verbund[0] = '0';
		else if (AllgBitleisteN((Bitleiste)etartklasse1,0) == 1 && parametertab[1] == 1)		verbund[0] = '0';
		else if (AllgBitleisteN((Bitleiste)etartklasse1,1) == 1 && parametertab[2] == 1)		verbund[0] = '0';
		else if (AllgBitleisteN((Bitleiste)etartklasse1,2) == 1 && parametertab[3] == 1)		verbund[0] = '0';
		else if (AllgBitleisteN((Bitleiste)etartschalter2,8) == 1 && parametertab[4] == 1)		verbund[0] = '0';
		else if (AllgBitleisteN((Bitleiste)etartschalter1,10) == 1 && parametertab[5] == 1)	verbund[0] = '0';
		else if (AllgBitleisteN((Bitleiste)etartschalter1,8) == 1 && parametertab[6] == 1)		verbund[0] = '0';
	}
/*	if (a->AKZET5[6] == 'J' && parametertab[7] == 1) verbund[0] = '0'; */

	/* bei Pseudolagerort auch kein verbund */
/*	if ( !strncmp( a->AKZLGFNR, lagerort, 8 ) )
	{
		verbund[0] = '0';
	}	*/
	if ( a->AKZSPERR[0] == 'J' )  verbund[0] = '0'; 
	if ( a->AKZLOESCH[0] == 'J' )    verbund[0] = '0'; 
	verbund[1] = '\0';

/*	if(Frankreich)
	{
		verbund[0] = CCode.AUXDELIVERY[0];
	}
*/
	exec sql open Cupdartikellag using :filiale, :a->AKZPZN;
	ERROR_MSG2( "open Cupdartikellag", a->AKZPZN )

DEBUG_SECTION
printf("FIL:  #%d#\n",filiale);
printf("PZN:  #%*.*s#\n",L_DEAKZ_AKZPZN,L_DEAKZ_AKZPZN,a->AKZPZN);
printf("LGNR: #%*.*s#\n",L_DEAKZ_AKZLGNR,L_DEAKZ_AKZLGNR,a->AKZLGNR);
printf("STAT: #%*.*s#\n",L_DEAKZ_AKZSTAT,L_DEAKZ_AKZSTAT,a->AKZSTAT);
printf("LGFNR:#%*.*s#\n",L_DEAKZ_AKZLGFNR,L_DEAKZ_AKZLGFNR,a->AKZLGFNR);
printf("VERF: #%*.*s#\n",L_DEAKZ_AKZVERF,L_DEAKZ_AKZVERF,a->AKZVERF);
printf("BEST: #%*.*s#\n",L_DEAKZ_AKZBEST,L_DEAKZ_AKZBEST,a->AKZBEST);
END_DEBUG_SECTION

	if(!strncmp(a->AKZVERF,"    ",4))
	{
		a->AKZVERF[0] = '0';
		a->AKZVERF[1] = '0';
		a->AKZVERF[2] = '0';
		a->AKZVERF[3] = '0';
	}
	sprintf(huelse,"%*.*s",L_DEAKZ_AKZVERF,L_DEAKZ_AKZVERF,a->AKZVERF);
	for (index = 0, fehler = 0; index < 4; index++)
	{
		if(a->AKZVERF[index] >= '0' && a->AKZVERF[index] <= '9') continue;
		fehler = 1;
		a->AKZVERF[index] = '0';
	}
	if(fehler != 0) 
	{
		sprintf( error_msg, "Fehler Verfalldatum: %s bei PZN: %7.7s",
				huelse,
				a->AKZPZN );
		PrintMsg( fun, error_msg, FEHL, -1 ); 	 
	}
	for ( ;; )
	{
		exec sql fetch Cupdartikellag into :i;
		ERROR_MSG2( "fetch Cupdartikellag", a->AKZPZN )

		i.BESTAND = RestBestand;
		if ( sqlca.sqlcode == 0 )
		{
/*			sprintf(huelse,"%*.*s",L_DEAKZ_AKZBEST,L_DEAKZ_AKZBEST,a->AKZBEST);
			if(bestandupdate == YES) i.BESTAND = atol(huelse);	*/
/*	im Artikellagerort immer Bestandsuebernahme wg. Verbund KSC	*/
/*			i.BESTAND = atol(huelse); */
			if ( a->AKZSPERR[0] == 'J' )
			{
				exec sql execute del_artlago;
				ERROR_MSG2( "execute del_artlago", a->AKZPZN ) 
				zaehlerDelort++;
				return 0;
			}

			EXEC SQL EXECUTE upd_artlago USING :a->AKZLGNR,
                                                :a->AKZSTAT,
                                                :a->AKZLGFNR,
                                                :a->AKZVERF,
                                                :i.BESTAND,
												:verbund;
			if ( sqlca.sqlcode == -346 )	  /* wenn doppelte Sätze */
			{
				exec sql delete from artikellagerort
					where current of Cupdartikellag;
				ERROR_MSG2( "delete Cupdartikellag", a->AKZPZN ) 
				continue;
			}
		  
			ERROR_MSG2( "execute upd_artlago", a->AKZPZN ) 
			zaehlerUpdort++;
			return OK;
		}
		else
			break;
	}	/* ende for */
	if ( a->AKZSPERR[0] != 'J' ) /* neue saetze nur nicht gesperrte */
	{

		EXEC SQL EXECUTE ins_artlago USING
				:filiale,
                :a->AKZPZN,
                :a->AKZLGNR,
                :a->AKZSTAT,
                :a->AKZLGFNR,
                :a->AKZVERF,
                :i.BESTAND,
				:verbund;
		ERROR_MSG2( "insert artikellagerort", a->AKZPZN )
		zaehlerInsort++;
	}
   
	return OK;
}

/***** AFTER-LADE-ARTIKEL-LOKAL *********************************************/

int AfterLadeArtikelLokal( char *error_msg )
{
	char *fun = "AfterLadeArtikelLokal";

/*	EXEC SQL UPDATE STATISTICS FOR TABLE artikellokal;
	if ( sqlca.sqlcode != 0 )
	{
		sprintf (error_msg, "upd stat artikellokal: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		PrintMsg( fun, error_msg, FEHL, ERROR );
	}
  
    DEBUG_SECTION
	PrintMsg( fun, " update statistics erfolgreich", HINW, -1 );
	END_DEBUG_SECTION
*/
	return OK;
}

/***** AFTER-LADE-ARTIKELLAGERORT *********************************************/

int AfterLadeArtikelLagerort( char *error_msg )
{
	char *fun = "AfterLadeArtikelLagerort";
   
/*	EXEC SQL UPDATE STATISTICS FOR TABLE artikellagerort;
	if ( sqlca.sqlcode != 0 )
	{
		sprintf (error_msg, "upd stat artikellagerort: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		PrintMsg( fun, error_msg, FEHL, ERROR );
	}
  
	DEBUG_SECTION
	PrintMsg( fun, " update statistics erfolgreich", HINW, -1 );
	END_DEBUG_SECTION
*/   
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
   
/*	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) ); */
	env = getenv( "LOG_PATH" );
	if ( env == NULL )
		env = ".";
	sprintf( logFile, "%s/wws.log", env );

	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
		return;
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s %s\n",
		mld,
		filialnr,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"tpldlokalart",
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

/***** HOLE-PSEUDOLAGERORTE ********************************************************/

int HolePseudoLagerorte      ( char *error_msg)
{
	char *fun = "HolePseudoLagerorte";

	exec sql begin declare section;
	int Fili;
	char Ort[8+1];
	exec sql end declare section;

	Fili = filialnr;
	 
	exec sql declare CSelOrte cursor with hold for 
			 select pseudolagerort
			   from pseudolagerorte
			   where filialnr = :Fili;
	exec sql open CSelOrte;
	ERROR_MSG( "open CSelOrte" )

	exec sql fetch CSelOrte into :Ort;
	ERROR_MSG( "fetch CSelOrte" )

	strcpy(lagerort,Ort);

	return 0;
}

int SaveFile()
{
	char szCommand[512];
	int  rc;
	char *fun = "SaveFile";
	char hilfe[81];
	char meld[81];
	char ausgabe[101];

	datum = AllgGetDate();
	
	sprintf(hilfe,"/phosix/kscsave/lokal.%02d.%08ld",filialnr,datum);

	sprintf( szCommand, "mv %s %s", dateiname, hilfe );
	sprintf(meld,"Fili: %d %s ",filialnr,fun);
	if ( (rc = h_system( szCommand )) < 0 )
	{
		sprintf( ausgabe," Ladedatei nicht unter %s gesichert; rc = %d",hilfe,rc);
		PrintMsg( meld, ausgabe, FEHL, -1 );
		return ERROR;
	}
	sprintf( ausgabe," Ladedatei unter %s gesichert",hilfe);
	PrintMsg( meld, ausgabe, HINW, -1 );
	return OK;
}

int CompressFile()
{
	char szCommand[512];
	int  rc;
	char *fun = "CompressFile";
	char hilfe[81];
	char meld[81];
	char ausgabe[101];

	datum = AllgGetDate();
	
	sprintf(hilfe,"/phosix/kscsave/lokal.%02d.%08ld",filialnr,datum);

	sprintf( szCommand, "compress %s", hilfe );
	sprintf(meld,"Fili: %d %s ",filialnr,fun);

	if ( (rc = h_system( szCommand )) < 0 )
	{
		sprintf( ausgabe," Sicherungsdatei nicht komprimiert; rc = %d",rc);
		PrintMsg( meld, ausgabe, FEHL, -1 );
	}
	return OK;
}

int DeleteFiles()
{
	char szCommand[512];
	int  rc;
	char *fun = "DeleteFiles";
	char hilfe[81];
	char hilfe2[81];
	char meld[81];
	char ausgabe[101];
	DIR *dirp;
	static struct dirent *direntp;
	int count = 0;
	int del;

	sprintf(meld,"Fili: %d %s ",filialnr,fun);
	sprintf(hilfe,"lokal.%02d",filialnr);
	if((dirp = opendir("/phosix/kscsave")) == NULL)
	{
		sprintf( ausgabe," opendir fehler; rc = %d",errno);
		PrintMsg( meld, ausgabe, FEHL, -1 );
		return 1;
	}
	SortOpen(0,19,19);
	while ( (direntp = readdir(dirp)) != NULL)           
	{
		if (strncmp(direntp->d_name,hilfe,8)) continue;
		SortPut(0,direntp->d_name);
		count++;
	}
	if (count>5)
	{
		for(del = count -5; del > 0; del--)
		{
			SortGet( 0, hilfe2 );
			sprintf(hilfe,"/phosix/kscsave/%*.*s",19,19,hilfe2);
			sprintf( szCommand, "rm %s", hilfe );

			if ( (rc = h_system( szCommand )) < 0 )
			{
				sprintf( ausgabe," Loeschen der Datei %s nicht moeglich; rc = %d",hilfe,rc);
				PrintMsg( meld, ausgabe, FEHL, -1 );
				return ERROR;
			}
			sprintf( ausgabe," Datei %s geloescht",hilfe);
			PrintMsg( meld, ausgabe, HINW, -1 );
		}
	}
	return OK;
}


/***** LOAD-PARAMETER *********************************************/

int LoadParameter( char *error_msg )
{
	char *fun = "LoadParameter";
	int i;

	exec sql begin declare section;
	char str[2048];
	int filiale;
	char name[21];
	exec sql end declare section;

	filiale = filialnr;
	strcpy(name,"TPLDLOKALART");

	for(i = 0; i < 20 ; i++ ) { parametertab[i] = 0; }
	
	strcpy( str, "select " );
	strcat( str, "parametername" );
	strcat( str, " from parameter" );
	strcat( str, " where filialnr = ?" );
	strcat( str, " and programmname = ?" );
	strcat( str, " for update " );

	exec sql prepare sel_parameter from :str;
	ERROR_MSG( "prepare sel_parameter" )
	exec sql declare CSelParameter cursor for sel_parameter;

	exec sql open CSelParameter using :filiale, :name;
	ERROR_MSG( "open CSelParameter" )
	  
	for(;;)
	{
		exec sql fetch CSelParameter into :name;
		ERROR_MSG( "fetch CSelParameter" )
		if ( NOTFOUND ) break;

		if(!strcmp(name,"OPIATE"))					parametertab[0] = 1;
		else if(!strcmp(name,"GIFT1"))				parametertab[1] = 1;
		else if(!strcmp(name,"GIFT2"))				parametertab[2] = 1;
		else if(!strcmp(name,"GIFT3"))				parametertab[3] = 1;
		else if(!strcmp(name,"FEUERGEFAERLICH"))	parametertab[4] = 1;
		else if(!strcmp(name,"KUEHLKETTE"))			parametertab[5] = 1;
		else if(!strcmp(name,"KUEHL08"))			parametertab[6] = 1;
		else if(!strcmp(name,"TFG"))				parametertab[7] = 1;
/*		else if(!strcmp(name,"GIFT1"))				parametertab[8] = 1;
		else if(!strcmp(name,"GIFT1"))				parametertab[9] = 1;
		else if(!strcmp(name,"GIFT1"))				parametertab[10] = 1;
		else if(!strcmp(name,"GIFT1"))				parametertab[11] = 1; */
	}
	return OK;
}

/***** AFTER-LADE-ARTIKELALTERN *********************************************/

int AfterLadeArtikelaltern( char *error_msg )
{
	char *fun = "AfterLadeArtikelaltern";

	/* Nochmaliges lesen der Relation artikelaltern, wegen nachfolgeartikel! */

	PreparPruefeNachfolgeArtikel();

	PruefeNachfolgeArtikel();
	/* Nochmaliges lesen der Relation artikelaltern, wegen nachfolgeartikel! */
	return OK;
}

/*** PREPARE-LADE-ARTIKELALTERN *************************************************/

int PrepareLadeArtikelaltern( char *error_msg )
{
	char *fun = "PrepareLadeArtikelaltern";

	exec sql begin declare section;
	char str[2048];
	int filiale;
	exec sql end declare section;

	filiale = filialnr;

	strcpy( str, "insert into artikelaltern (" );
	strcat( str, ARTIKELALTERN_PELISTE );          
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, \"\", ? )" );

	exec sql prepare ins_artalt from :str;
	ERROR_MSG( "prepare ins_artalt" )
  
	strcpy( str, "select " );
	strcat( str, ARTIKELALTERN_PELISTE );
	strcat( str, " from artikelaltern " );
	strcat( str, "where artikel_nr = ? " );
	strcat( str, "and filialnr = ? " );
	strcat( str, "for update " );

	exec sql prepare dec_artikelalt from :str;
	ERROR_MSG( "prepare dec_artikelalt" )
	exec sql declare Cupdartikelalt cursor for dec_artikelalt;
	
	strcpy( str, "update artikelaltern set " );
	strcat( str, "ARTIKEL_NR_ALTERN = ?" );          
	strcat( str, " where current of Cupdartikelalt" );
   
	exec sql prepare upd_artalt from :str;
	ERROR_MSG( "prepare upd_artalt" )
   
	strcpy( str, "delete from artikelaltern " );
	strcat( str, " where current of Cupdartikelalt" );
   
	exec sql prepare del_artalt from :str;
	ERROR_MSG( "prepare del_artalt" )
   
	/* step2: lesen eindeutig von artikel ob artikel vorhanden */
  
	strcpy( str, "select " );
	strcat( str, "artikel_nr " );
	strcat( str, "from artikellokal " );
	strcat( str, "where artikel_nr = ? " );
	strcat( str, "and filialnr = ? " );
/*	strcat( str, "and artikelaktiv = '1' " ); auch nicht aktive laden wegen Nachfrage */

	exec sql prepare les_artik from :str;
	ERROR_MSG( "prepare les_artik" )
	exec sql declare Clesartik Cursor with hold for les_artik;

	/* step3: lesen eindeutig von orginalartikel für update etartschalter */
  
	strcpy( str, "select " );
	strcat( str, "ETARTSCHALTER1 " );
	strcat( str, "from artikellokal " );
	strcat( str, "where artikel_nr = ? " );
	strcat( str, "and filialnr = ? " );
	strcat( str, "for update " );

	exec sql prepare les_artikorg from :str;
	ERROR_MSG( "prepare les_artikorg" )
	exec sql declare Cupdartik Cursor with hold for les_artikorg;

	strcpy( str, "update artikellokal set " );
	strcat( str, "ETARTSCHALTER1 = ?" );          
	strcat( str, " where current of Cupdartik" );
   
	exec sql prepare upd_artikorg from :str;
	ERROR_MSG( "prepare upd_artikorg" )
   
 	return OK;   
}
			
/*** LADE-ARTIKEL-ALTERN ******************************************************/

int LadeArtikelaltern( struct O_DEAKZ *art, char *error_msg )
{
	char *fun = "LadeArtikelaltern";
	char huelse[8];

	exec sql begin declare section;
	struct O_DEAKZ   *a;
	int filiale;
	long ersatznr;
	long etartschalter1;
	struct ARTIKELALTERN   folge;							 /* wegen vergleich     */
	long orgpzn;
	exec sql end declare section;

	a = art;

	filiale = filialnr;

	sprintf(huelse,"%*.*s", L_DEAKZ_AKZAANR, L_DEAKZ_AKZAANR, a->AKZAANR );
	ersatznr = atol(huelse);

	/* nur vorhandene Artikel ketten */
	exec sql open Cupdartik using
		:a->AKZPZN,
		:filiale;
	ERROR_MSG( "open Cupdartik" )

	exec sql fetch Cupdartik into :etartschalter1;
	ERROR_MSG( "fetch Cupdartik" )
	if (NOTFOUND) return OK;	/* kann eigentlich nicht sein */

	if( (etartschalter1 -= 16384) < 0) etartschalter1 += 16384;


	if ( ersatznr != 0 )
	{
		/* nur vorhandene Artikel ketten */
		exec sql open Clesartik using
			:ersatznr,
			:filiale;
		ERROR_MSG( "open Clesartik" )

		exec sql fetch Clesartik;
		ERROR_MSG( "fetch Clesartik" )

		if ( sqlca.sqlcode == 0 )
		{
			exec sql open Cupdartikelalt using
				:a->AKZPZN,
				:filiale;

			ERROR_MSG( "open Cupdartikelalt" )
	  
			exec sql fetch Cupdartikelalt into :folge;
			ERROR_MSG( "fetch Cupdartikelalt" )

			if ( sqlca.sqlcode == 0 )
			{
				exec sql execute upd_artalt using :ersatznr;
				ERROR_MSG( "execute upd_artalt" ) 
			}
			else
			{
				exec sql execute ins_artalt using :a->AKZPZN, :ersatznr, :filiale;
				ERROR_MSG( "insert artikelaltern" )
			}
			etartschalter1 += 16384;
		}
		else
		{
			exec sql open Cupdartikelalt using
				:a->AKZPZN,
				:filiale;

			ERROR_MSG( "open Cupdartikelalt" )
	  
			exec sql fetch Cupdartikelalt;
			ERROR_MSG( "fetch Cupdartikelalt" )

			if ( sqlca.sqlcode == 0 )
			{
				exec sql execute del_artalt;
				ERROR_MSG( "execute del_artalt" ) 
			}
		}
	}
	else
	{
			exec sql open Cupdartikelalt using
				:a->AKZPZN,
				:filiale;

			ERROR_MSG( "open Cupdartikelalt" )
	  
			exec sql fetch Cupdartikelalt;
			ERROR_MSG( "fetch Cupdartikelalt" )

			if ( sqlca.sqlcode == 0 )
			{
				exec sql execute del_artalt;
				ERROR_MSG( "execute del_artalt" ) 
			}
	}

	exec sql execute upd_artikorg using :etartschalter1;
	ERROR_MSG( "execute upd_artikorg" ) 

	return OK;
}

/*** PREPARE-LADE-IBTBranchArticleConfig *************************************************/

int PrepareLadeIBTBranchArticleConfig( char *error_msg )
{
	char *fun = "PrepareLadeIBTBranchArticleConfig";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

 
	strcpy( str, "select " );
	strcat( str, "ibtassortmenttypeid " );
	strcat( str, "from ibtbrancharticleconfig " );
	strcat( str, "where branchno = ? " );
	strcat( str, "and articleno = ? " );
	strcat( str, "for update " );

	exec sql prepare dec_articleibt from :str;
	ERROR_MSG( "prepare dec_articleibt" )
	exec sql declare Cupdarticleibt cursor for dec_articleibt;
	
	strcpy( str, "update ibtbrancharticleconfig set " );
	strcat( str, "ibtassortmenttypeid = ?" );          
	strcat( str, " where current of Cupdarticleibt" );
   
	exec sql prepare upd_articleibt from :str;
	ERROR_MSG( "prepare upd_articleibt" )
   
 	return OK;   
}
			
/*** LADE-ARTIKEL-IBTBranchArticleConfig ******************************************************/

int LadeIBTBranchArticleConfig( struct O_DEAKZ *art, char *error_msg )
{
	char *fun = "LadeIBTBranchArticleConfig";
	char huelse[8];

	exec sql begin declare section;
	struct O_DEAKZ   *a;
	short assortmenttypeDB;
	short assortmenttypeVSE;
	int filiale;
	exec sql end declare section;

	a = art;

	filiale = filialnr;

	if( a->AKZVB[0] == 'Z')			/* Privatsortiment */
		assortmenttypeVSE = 1;
	else if( a->AKZVB[0] == 'R')	/* Veto	*/
		assortmenttypeVSE = 2;
	else
		assortmenttypeVSE = 0;		/* General */

	exec sql open Cupdarticleibt using
		:filiale,
		:a->AKZPZN;

	for(;;)
	{
		exec sql fetch Cupdarticleibt into :assortmenttypeDB;
		ERROR_MSG( "fetch Cupdarticleibt" )
		if (NOTFOUND) break;
		if(assortmenttypeDB == assortmenttypeVSE) continue;	/* bereits korrekt gesetzt */
		exec sql execute upd_articleibt using :assortmenttypeVSE;
		ERROR_MSG( "execute upd_articleibt" ) 
	}

	return OK;
}

/***** PREPAR-PRUEFE-NACHFOLGE-ARTIKEL **************************************/

static int PreparPruefeNachfolgeArtikel( void )
{
	exec sql begin declare section;
	char str[1024];
	exec sql end declare section;

	char error_msg[81];
	char *fun = "PreparPruefeNachfolgeArtikel";
 
	/* step1: lesen sequenziell artikelaltern! */

	strcpy( str, "select " );
	strcat( str, "artikel_nr_altern, " );
	strcat( str, "artikel_nr " );
	strcat( str, "from artikelaltern " );
	strcat( str, "where filialnr = ? " );
	strcat( str, "for update" );

	exec sql prepare NachAltern1 from :str;
	ERROR_MSG( "prepare NachAltern1" )
	exec sql declare CnachAltern1 Cursor with hold for NachAltern1;
 
	/* step2: lesen eindeutig von artikel ob artikel vorhanden */
  
	strcpy( str, "select " );
	strcat( str, "etartschalter1 " );
	strcat( str, "from artikellokal " );
	strcat( str, "where artikel_nr = ? " );
	strcat( str, "and filialnr = ? " );
	strcat( str, "for update" );

	exec sql prepare NachAltern2 from :str;
	ERROR_MSG( "prepare NachAltern2" )
	exec sql declare CnachAltern2 Cursor with hold for NachAltern2;
 
	/* step4: ändern artikel etartschalter1 */
  
	strcpy( str, "update artikellokal set etartschalter1 = ? " );
	strcat( str, "where current of CnachAltern2 " );
 
	exec sql prepare EtUpdate from :str;
	ERROR_MSG( "prepare EtUpdate" )
  
	/* step5: löschen artikelaltern */
  
	strcpy( str, "delete from artikelaltern " );
	strcat( str, "where current of CnachAltern1 " );
 
	exec sql prepare EtDelete from :str;
	ERROR_MSG( "prepare EtDelete" )
  
	return OK;
}

/***** PRUEFE-NACHFOLGE-ARTIKEL *********************************************/

static int PruefeNachfolgeArtikel( void )
{
	exec sql begin declare section;
	int  bitleiste;
	int  artikelNrAltern;
	int  artikelNr;
	char error_msg[81];
	int	 filiale;
	exec sql end declare section;

	filiale = filialnr;

	struct ZAEHLER
	{
		int del;
		int upd;
	}	zaehler;

	int i = 0;
	char *fun = "PruefeNachfolgeArtikel";

	#define NACHFOLGE_ARTIKEL 1

	exec sql open CnachAltern1 using :filiale;
	ERROR_MSG( "open CnachAltern1" )

	zaehler.del = 0;
	zaehler.upd = 0;
	  
	for( ;; )
	{
		if ( i == 0 )
		{
			exec sql commit work;
			exec sql begin work;
			ERROR_MSG( "begin_work" )
		}
		/* artikelaltern */
		exec sql fetch CnachAltern1 into :artikelNrAltern, :artikelNr;
		ERROR_MSG( "fetch CnachAltern1" )
		if ( NOTFOUND ) break;

		/* artikel */
		exec sql open CnachAltern2 using :artikelNrAltern, :filiale;
		ERROR_MSG( "open CnachAltern2" )
		exec sql fetch CnachAltern2 into :bitleiste;
		ERROR_MSG( "fetch CnachAltern2" )

		if ( NOTFOUND )
		{
			printf("Artikel_nr/ArtikelNrAltern: %d/%d\n",artikelNr,artikelNrAltern);
			/* loeschen artikelaltern */
			exec sql execute EtDelete;
			ERROR_MSG( "execute EtDelete" )
			sprintf( error_msg, "ArtikelNr/Altern in Filiale %d nicht gefunden -> wurde geloescht:%d / %d",
					filiale, artikelNr, artikelNrAltern );
			PrintMsg( fun, error_msg, FEHL, ERROR ); 	
			zaehler.del++;

			exec sql open CnachAltern2 using :artikelNr, :filiale;
			ERROR_MSG( "open CnachAltern2" )
	   
			exec sql fetch CnachAltern2 into :bitleiste;
			ERROR_MSG( "fetch CnachAltern2" )
	   
			/* Bitleiste ändern */
			if ( sqlca.sqlcode != SQLNOTFOUND )
/*			if ( sqlca.sqlcode == SQLNOTFOUND )
			{
				exec sql execute EtDelete;
				ERROR_MSG( "execute EtDelete" )
				sprintf( error_msg, "ArtikelNr/Altern in Filiale %d nicht gefunden -> wurde geloescht:%d / %d",
						filiale, artikelNr, artikelNrAltern );
				PrintMsg( fun, error_msg, FEHL, ERROR ); 	
				zaehler.del++;
			}
			else
*/			{
				if ( AllgBitleisteN( bitleiste, NACHFOLGE_ARTIKEL ) )
				{
					if ( ( bitleiste -= 16384 ) < 0 )
					{
						sprintf( error_msg, "Bitleiste falsch in Filiale %d: %d->%d",
								filiale, artikelNrAltern, bitleiste );
						PrintMsg( fun, error_msg, FEHL, ERROR );
					}
				}
	   
				/* aender artikel */
				exec sql execute EtUpdate using :bitleiste;
				ERROR_MSG( "execute EtUpdate" );
   
				zaehler.upd++;
			}
		}
	}

	if ( i++ >= M_DURCHLAUF_COMMIT )
		i = 0;
  
	exec sql commit work;
	exec sql begin work;
	ERROR_MSG( "begin 1" )
  
	sprintf( error_msg, "del/upd: %d/%d", zaehler.del, zaehler.upd );
	PrintMsg( fun, error_msg, HINW, OK ); 
  
	return OK;
}


/***** ENDE *****************************************************************/


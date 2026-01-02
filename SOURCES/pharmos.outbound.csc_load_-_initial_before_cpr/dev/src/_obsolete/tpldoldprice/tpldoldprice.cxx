/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"

#define PROJECTNAME	 "tpldoldprice"

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
#include "articleoldprice.h"
#include "artpreis.h"
#include "deaky.h"
#include "libtpld/cobolbuf.h"
#include "pplib/allg.h"
#include "libtpld/struct.h"
#include "libtpld/define.h"
#include <libtpld/qsort.h>
#include <libtpld/hsystfkt.h>
#include <libtpld/vtcodum.h>
#include <dirent.h>                                     
#include <errno.h>                                     
#include <libtpld/coboltoasci.h>

exec sql include sqlca;
exec sql include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define ERROR_MSG2(x,y)       if(sqlca.sqlcode<0) { \
                              sprintf(error_msg,"%s %d/%d bei PZN: %7.7s",x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1],y ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define NOTFOUND           sqlca.sqlcode == SQLNOTFOUND

#define OK                   0
#define NO                   0
#define YES                  1
#define ERROR               -1
#define INSERT               1
#define WARNING             -2
#define HINW               'H'
#define FEHL               'F'
#define RIO_EOF            110
#define RIO_NOFIND         111
#define OUTDATABASE        "phosix"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */
#define MAX_CH_ARTIKELNAME 26

FILE *lokaldat;
char log_file [300 + 1];
char  dateiname[L_TEXT];
int debug_enabled  = NO;
int explain = NO;
int zIns = 0;
int zUpd = 0;
int zDel = 0;

exec sql begin declare section;
struct O_DEAKY a;
long artikel_nr ;
char outdatenbank[60];
double AEP;
double AVP;
double GEP;
double GEPNA;
double AGP;
short sVZ;
artpreisS actpreis;
exec sql end declare section;
static const int DEAKY_LEN = sizeof(a);


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
double dec2double      (char *huelse);   
int StarteLadenDerArtikelRelationen( char *error_msg);
int PrepareLoadTables         ( char *error_msg);
int LoadTables                ( char *error_msg);
int AfterLoadTables           ( char *error_msg);
int PrepareLadeArtikelpreis   ( char *error_msg);
int LadeArtikelpreis          ( char *error_msg);
int AfterLadeArtikelpreis     ( char *error_msg);
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
	int	  iTable = -1;
	long  ltag;

	setbuf(stdout,0);
	sprintf(outdatenbank,"%s",OUTDATABASE);
     
	strcpy(start_msg, "gestartet mit:");
	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-dg" ) )
		{
			strcat(start_msg, " -dg");
			debug_enabled = YES;
		}
		else if ( !strcmp( schalter, "-file" ) )
		{
			strcat(start_msg, " -file");
			i++;
			sprintf( dateiname, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-vz" ) )
		{
			strcat(start_msg, " -vz");
			i++;
			sVZ = atoi( argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-dbout" ) )
		{
			strcat(start_msg, " -dbout");
			i++;
			sprintf( outdatenbank, "%s", argv[i] );
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
				" { -file dateiname <Dateiname DEAKY> }\n\t"
				" { -dbout datenbankname <Datenbankname Ausgabe> }\n\t"
				" { -dg <Debugging> }\n\t"
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

	if ( ( lokaldat = fopen( dateiname, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( fun, "Ladedatei nicht vorhanden", FEHL, 0 );
		return -1;
	}
      

	if ( ( LOG_PATH = getenv("LOG_PATH")) == (char *)0 )
		strcpy( logpath, "." );
	else
		strcpy( logpath, LOG_PATH );
   
	sprintf( log_file, "%s/%s", logpath, LOG_FILE );

	PrintMsg( fun, start_msg, HINW, 0 );
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	if ( ( rc = StarteLadenDerArtikelRelationen( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	sprintf(error_msg," Alte Preise eingefuegt/geloescht/geaendert: %d/%d/%d",zIns,zDel,zUpd);
	PrintMsg( fun, error_msg, HINW, 0 );
	PrintMsg( fun, "korrekt beendet", HINW, rc );
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
		if(fread( (struct O_DEAKY*) &a ,DEAKY_LEN+1, 1 , lokaldat ) == 0)
			break;

		for(idx = 0; idx < DEAKY_LEN; idx++)
		{
			CheckAbdruckbar( (unsigned char*)&a + idx );
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

		sprintf( huelse, "%*.*s", L_DEAKY_AKYAEP, L_DEAKY_AKYAEP,a.AKYAEP );
		AEP=atof(huelse)/100;
		sprintf( huelse, "%*.*s", L_DEAKY_AKYAVP, L_DEAKY_AKYAVP,a.AKYAVP );
		AVP=atof(huelse)/100;
		sprintf( huelse, "%*.*s", L_DEAKY_AKYGEP, L_DEAKY_AKYGEP,a.AKYGEP );
		GEP=atof(huelse)/100;
		sprintf( huelse, "%*.*s", L_DEAKY_AKYGEPNA, L_DEAKY_AKYGEPNA,a.AKYGEPNA );
		GEPNA=atof(huelse)/100;
		sprintf( huelse, "%*.*s", L_DEAKY_AKYAGPCH, L_DEAKY_AKYAGPCH,a.AKYAGPCH );
		AGP=atof(huelse)/100;
            
        if ( ( rc = LoadTables( error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
        else if ( explain == YES )
           if ( zaehler > 100 ) break;   /* Nur 100 Saetze verarbeiten */

	}      /* ende while */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;
	if ( ( rc = PrepareLadeArtikelpreis( error_msg ) ) < 0 ) return rc;

   return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables( char *error_msg)
{
	int rc = OK;
	/* neue Tabellen schreiben */
	rc = LadeArtikelpreis(error_msg);

	return OK;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc;
	if ( (rc = AfterLadeArtikelpreis(error_msg)) < 0) return rc;
	return OK;
}

/*** PREPARE-LADE-ARTIKELPREIS **************************************************/

int PrepareLadeArtikelpreis( char *error_msg )
{
	char *fun = "PrepareLadeArtikelpreis";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "insert into articleoldprice (" );
	strcat( str, ARTICLEOLDPRICE_PELISTE );          
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ? )" );

	exec sql prepare ins_artpreis from :str;
	ERROR_MSG( "prepare ins_artpreis" )
   
	strcpy( str, "select " );
	strcat( str, ARTICLEOLDPRICE_PELISTE );
	strcat( str, " from articleoldprice where articleno = ?	" );
	strcat( str, "and branchno = ? for update " );

	exec sql prepare dec_artikelpreis from :str;
	ERROR_MSG( "prepare dec_artikelpreis" )
	exec sql declare Cupdartikelpreis cursor for dec_artikelpreis;
	
	strcpy( str, "update articleoldprice set " );
	strcat( str, "PREISEKAPO = ?," );
	strcat( str, "PREISEKGROSSO = ?," );
	strcat( str, "PREISEKGROSSONA = ?," );
	strcat( str, "PREISVKAPO = ?" );
	strcat( str, "where current of Cupdartikelpreis" );
      
	exec sql prepare upd_artpreis from :str;
	ERROR_MSG( "prepare upd_artpreis" )
	
	strcpy( str, "delete from articleoldprice " );
	strcat( str, "where current of Cupdartikelpreis" );
      
	exec sql prepare del_artpreis from :str;
	ERROR_MSG( "prepare del_artpreis" )
   
	strcpy( str, "select " );
	strcat( str, ARTPREIS_PELISTE );
	strcat( str, " from artikelpreis where artikel_nr = ?	" );
	strcat( str, "and datumgueltigab = ? for update " );

	exec sql prepare dec_actpreis from :str;
	ERROR_MSG( "prepare dec_actpreis" )
	exec sql declare Cupdactpreis cursor for dec_actpreis;

	return OK;   
}

/*** LADE-ARTIKEL-PREIS *********************************************************/

int LadeArtikelpreis( char *error_msg )
{
	char *fun = "LadeArtikelpreis";

	exec sql begin declare section;
	char *FestDatum = "19950906";		   /* ist immer geschrieben in Step1 */
	double grosso;
	exec sql end declare section;

	exec sql open Cupdartikelpreis using :a.AKYPZN, :sVZ ;
	ERROR_MSG( "open Cupdartikelpreis" )
	  
	exec sql fetch Cupdartikelpreis;
	ERROR_MSG( "fetch Cupdartikelpreis" )

	if ( ( grosso = GEP ) == 0 )
	{
		grosso = AEP / 1.1557;			 /* aek / taxspanne == grosso */
	}

	if ( sqlca.sqlcode == 0 )
	{
		exec sql open Cupdactpreis using :artikel_nr, :FestDatum;
		ERROR_MSG( "open Cupdactpreis" )
	  
		exec sql fetch Cupdactpreis into :actpreis;
		ERROR_MSG( "fetch Cupdactpreis" )

		if ( sqlca.sqlcode == 0 )
		{
			if( AEP == 0)
			{
				EXEC SQL EXECUTE del_artpreis;
				ERROR_MSG( "execute del_artpreis" )
				zDel++;
				return OK;
			}
			else
			{
				EXEC SQL EXECUTE upd_artpreis USING
					:AEP,
					:grosso,
					:GEPNA,
					:AVP;
				ERROR_MSG( "execute upd_artpreis" ) 
				zUpd++;
				return OK;
			}
		}
		else
		{
			if( AEP == 0)
			{
				EXEC SQL EXECUTE del_artpreis;
				ERROR_MSG( "execute del_artpreis" )
				zDel++;
				return OK;
			}
			else if( AEP == actpreis.PREISEKAPO)
			{
				EXEC SQL EXECUTE del_artpreis;
				ERROR_MSG( "execute del_artpreis" )
				zDel++;
				return OK;
			}
			else
			{
				EXEC SQL EXECUTE upd_artpreis USING
					:AEP,
					:grosso,
					:GEPNA,
					:AVP;
				ERROR_MSG( "execute upd_artpreis" ) 
				zUpd++;
				return OK;
			}
		}
	}

	exec sql open Cupdactpreis using :artikel_nr, :FestDatum;
	ERROR_MSG( "open Cupdactpreis" )
	  
	exec sql fetch Cupdactpreis into :actpreis;
	ERROR_MSG( "fetch Cupdactpreis" )

	if ( sqlca.sqlcode == 0 )
	{
		if( AEP != 0)
		{
			EXEC SQL EXECUTE ins_artpreis USING
				:sVZ,
				:a.AKYPZN,
				:AEP,
				:grosso,
				:GEPNA,
				:AVP;
			zIns++;
			ERROR_MSG( "insert artikelpreis" )
		}
	}
	else
	{
		if( AEP != 0)
		{
			if( AEP != actpreis.PREISEKAPO)
			{
				EXEC SQL EXECUTE ins_artpreis USING
					:sVZ,
					:a.AKYPZN,
					:AEP,
					:grosso,
					:GEPNA,
					:AVP;
				zIns++;
				ERROR_MSG( "insert artikelpreis" )
			}
		}
	}

	return OK;
}

/***** AFTER-LADE-ARTIKEPREIS  **********************************************/

int AfterLadeArtikelpreis( char *error_msg )
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
		"tpldoldprice",
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

/***** DEC-2-DOUBLE *********************************************************/

double dec2double (char *huelse)
{
  int i;
  
  for ( i=0; ;i++ )
    {
    if ( huelse[i] == '\0' ) break; 
    if ( huelse[i] == ',' ) huelse[i] = '.';
    }
  
  return atof( huelse );
}  

/***** ENDE *****************************************************************/

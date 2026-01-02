/********************************************************************************/
/*     Hauptmodul: delartikelkonto.cxx											*/
/*         Source: 																*/
/*          Autor: Frank Naumann												*/
/*       Erstellt: 07.08.2023													*/
/*        Sprache: C															*/
/*        Erzeugt: manuell														*/
/*        Aufgabe: loeschen der Tabelle artikelkonto							*/
/*         Aufruf: delartikelkonto -days <Anzahltage>							*/
/*																				*/
/********************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/
#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "delartikelkonto"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/********************************************************************************/
/* INCLUDE */
/********************************************************************************/
#include "libtpld/define.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include "pplib/allg.h"


/********************************************************************************/
/* DEFINE */
/********************************************************************************/
#define MAX_TRANSAKTION     300
typedef struct timeval timeval_t; 

/********************************************************************************/
/* MACROS */
/********************************************************************************/
#define ERROR_MSG( x )      if( SQLCODE < 0 ){				\
								PrintMsg( fun, x, FEHLER ); \
								return ERROR;				\
							}


/********************************************************************************/
/* MODUL-GLOBALE VARIABLEN */
/********************************************************************************/
static char* spDatabase			= NULL;
static int iNumberOfDay			= 0; 
static long delRows	= 0;
static bool bVersion = false;
static bool bNewDelete = false;
exec sql begin declare section;
long delTimestamp;
exec sql end declare section;


/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
static int	KommandoZeileEinlesen( int argc, char** argv );
static int	oeffneDB();
static int	schliesseDB();
static int	Delete();
static int	DeleteNew();
static void PrintMsg(char *fun, char *error_msg, char mld );


/********************************************************************************/
/* int main( int argc, char **argv ) */
/********************************************************************************/
int main( int argc, char* argv[] )
{
	char error_msg[512];
	char *fun = "main()";

	setbuf(stdout, 0);	

	/*****************************************************/
	/* Aufrufparameter werden ausgelesen */
	/*****************************************************/
	if( !KommandoZeileEinlesen( argc, argv ) == OK )
	{
		printf( "Aufruf: delartikelkonto -days Tage.\n"							
		 		"Beispiel: > %s -days 60 <\n"									
		 		"--> Loescht alle Datenaetze, die aelter als 60 Tage sind", argv[0] );	
		return 1;
	}
	if(bVersion)
	{
		return OK;
	}

    
	sprintf(error_msg, "gestartet mit Tagen: %d", iNumberOfDay);
	PrintMsg(fun, error_msg, HINWEIS);
	sprintf(error_msg, "delTimestamp: %ld", delTimestamp);
	PrintMsg(fun, error_msg, HINWEIS);


	/*****************************************************/
	/* Datenbank oeffnen */
	/*****************************************************/
	if( !oeffneDB() == OK )
	{
		PrintMsg( fun, "Fehler beim ÷ffnen der Datenbank!", FEHLER );
		return 2;
	} 
	
	/*****************************************************/
	/* Loeschen der Datensaetze */
	/*****************************************************/
	if (bNewDelete == true)
	{
		if (!DeleteNew() == OK)
		{
			PrintMsg(fun, "Loeschen hat NICHT geklappt!", FEHLER);
			return 3;
		}
	}
	else
	{
		if (!Delete() == OK)
		{
			PrintMsg(fun, "Loeschen hat NICHT geklappt!", FEHLER);
			return 3;
		}
	}

	/*****************************************************/
	/* Datenbank schliessen */
	/*****************************************************/
	if( !schliesseDB() == OK )
	{
		PrintMsg( fun, "Fehler beim Schlieﬂen der Datenbank!", FEHLER );
		return 4;
	} 

	
	sprintf( error_msg, "Anzahl geloeschter Datensaetze: %d", delRows );
	PrintMsg( fun, error_msg, HINWEIS );
	PrintMsg( fun, "beendet", HINWEIS );


	return OK;
}
/*********************************************************************************/
/* static int KommandoZeileEinlesen( char** argv ) */
/*********************************************************************************/
static int KommandoZeileEinlesen( int argc, char* argv[] )
{
	char error_msg[512];
	int i;
	int skip = NO;
	char *schalter;
	char *fun = "KommandoZeileEinlesen()";
			
	for( i = 1; i < argc; i++ )
	{
		if( skip )
		{
			skip = NO;
			continue;
		}
		schalter = argv[i];
		
		if( !strcmp(schalter, "-days") )
		{
			if( atoi(argv[i + 1]) != 0 ){
				iNumberOfDay = atoi( argv[i + 1] );
				skip = YES;
			}
			else
			{
				skip = ERROR;
			}
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			spDatabase = argv[i];
		}
		else if (!strcmp(schalter, "-new"))
		{
			bNewDelete = true;
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			bVersion = true;
		}
		else
		{
			skip = ERROR;
			break;
		}
	} /* ENDR FOR */                                            

	if( argc == 1 || skip == ERROR )
	{
		PrintMsg( fun, "Fehlerhafte Programmparameter", HINWEIS );
		return ERROR; /* Fehlerhafte KommandoZeile */
	}

	delTimestamp = time(NULL);
	delTimestamp -= (iNumberOfDay * 24 * 3600);
	return OK;
}

/*********************************************************************************/
/* static int oeffneDB() */
/*********************************************************************************/
static int oeffneDB()
{
	exec sql begin declare section;
		char* spDB = spDatabase;
	exec sql end declare section;
  
	char *fun = "oeffneDatenBank()";
  
	if( spDB == NULL )
	{
		exec sql database DATABASE;
		spDatabase = DATABASE;
	}
	else
	{
		exec sql database :spDB;
	}	
	ERROR_MSG( "database" );

	exec sql set lock mode to wait 20;
	ERROR_MSG( "set lock mode" );
	
	exec sql set isolation to dirty read;
	ERROR_MSG( "set isolation" );
	
	return OK;
}

/****************************************************************************/
/* static int schliesseDB()													*/
/****************************************************************************/
static int schliesseDB()
{
	char *fun = "schliessen DB";
	exec sql close database;
	ERROR_MSG( "close database" );
	
	return OK;
}

/****************************************************************************/
/* static int Delete()														*/
/****************************************************************************/
static int Delete()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*			fun = "Delete()";
	unsigned int uiTransactions = 0;

	exec sql begin declare section;
	char str[2048];
	long lfdnr;
	exec sql end declare section;

	
	/* SELECT-Cursor vorbereiten */
	strcpy( str, "SELECT lfdnr FROM artikelkonto where zeitunix < ? FOR UPDATE" );
	EXEC SQL PREPARE preSelArtikelKonto from :str;
	EXEC SQL DECLARE curSelArtikelKonto cursor with hold for preSelArtikelKonto;
	ERROR_MSG( "DECLARE curSelArtikelKonto" );
	exec sql free preSelArtikelKonto;

	/* DELETE-Cursor vorbereiten */
	strcpy( str, "DELETE FROM artikelkonto WHERE CURRENT OF curSelArtikelKonto" );
	EXEC SQL PREPARE preDelArtikelKonto from :str;
	

	/* SELECT ausfuehren */
	EXEC SQL OPEN curSelArtikelKonto using :delTimestamp;
	ERROR_MSG( "OPEN curSelArtikelKonto" );

	EXEC SQL BEGIN WORK;
	ERROR_MSG( "BEGIN WORK1" );
	for(;;)
	{
		uiTransactions++;
		/* Max. Transaktionen sind erreicht --> Commit setzen */
		if( (uiTransactions % MAX_TRANSAKTION) == 0 )
		{
			EXEC SQL COMMIT WORK;
			ERROR_MSG( "COMMIT WORK1" );
			EXEC SQL BEGIN WORK;
			ERROR_MSG( "BEGIN WORK2" );
		}
		
		EXEC SQL FETCH curSelArtikelKonto into :lfdnr;
		ERROR_MSG( "EXEC SQL FETCH curSelArtikelKonto!" );
		
		/* Keine weiteren Datensaetze im Cursor */
		if( SQLCODE == SQLNOTFOUND )
		{
			break;
		}

		EXEC SQL EXECUTE preDelArtikelKonto;
		ERROR_MSG( "EXEC SQL EXECUTE preDelArtikelKonto!" );
		delRows++;
	}
	
	EXEC SQL COMMIT WORK;	
	ERROR_MSG( "COMMIT WORK2" );
	EXEC SQL CLOSE curSelArtikelKonto;
	ERROR_MSG( "EXEC SQL CLOSE curSelArtikelKonto!" );

	return OK;
}

static int	DeleteNew()
{
	char* fun = "DeleteNew()";

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	long recordCount;
	EXEC SQL END DECLARE SECTION;

	EXEC SQL CREATE TEMP TABLE tmp(id INTEGER);
	ERROR_MSG("EXEC SQL CREATE TEMP TABLE");

	strcpy(str, "INSERT INTO tmp SELECT FIRST 1000 rowid FROM artikelkonto WHERE zeitunix < ? ");
	EXEC SQL PREPARE insertTmp from :str;

	strcpy(str, "DELETE FROM artikelkonto WHERE rowid IN (SELECT id FROM tmp) ");
	EXEC SQL PREPARE delKonto from :str;


	while (true)
	{
		EXEC SQL EXECUTE insertTmp USING :delTimestamp;
		ERROR_MSG("EXEC SQL EXECUTE insertTmp");

		EXEC SQL SELECT COUNT(*) INTO :recordCount FROM tmp;
		ERROR_MSG("SELECT COUNT(*)");

		if (recordCount == 0)
			break;
		EXEC SQL EXECUTE delKonto;
		ERROR_MSG("EXEC SQL EXECUTE delKonto");

		EXEC SQL TRUNCATE TABLE tmp;
		ERROR_MSG("EXEC SQL TRUNCATE TABLE tmp");

		delRows += recordCount;
	}

	return OK;
}


/************************************************************************************************************/
/* static void PrintMsg(char *fun, char *error_msg, char mld ) */
/************************************************************************************************************/
static void PrintMsg( char *fun, char *error_msg, char mld )
{
	FILE *fp;
	struct tm *localtime();
	struct tm *zeit;
	long hour1;
	pid_t pid;
	long time();
	char logFile[L_TEXT];
    char *env;

	pid = getpid();
	hour1 = time( &hour1 );
	zeit  = localtime( &hour1 );

	env = getenv( "LOG_PATH" );
	if ( env == NULL )
		env = ".";
	sprintf( logFile, "%s/wws.log", env );

	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
		return;

	if(	zeit->tm_year > 99 ) zeit->tm_year -= 100;

	fprintf( fp, "%c %02d.%02d.%02d %02d:%02d:%02d "
			"pid=%05ld %.11s %s %s->%d/%d\n",
			mld,
			zeit->tm_mday,
			zeit->tm_mon + 1,
			zeit->tm_year,
			zeit->tm_hour,
			zeit->tm_min,
			zeit->tm_sec,
			pid,
			"delartikelkonto",
			fun,
			error_msg, 
			SQLCODE,
			SQLISAM );

	fclose(fp);
}

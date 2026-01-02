/********************************************************************************/
/*     Hauptmodul: resetqupta.ecc												*/
/*         Source: 																*/
/*          Autor: Ronald Imschweiler											*/
/*       Erstellt: 14.03.2003													*/
/*        Sprache: C															*/
/*        Erzeugt: manuell														*/
/*        Aufgabe: Abnullen der kummulierten Mengen in articlequota				*/
/*         Aufruf: resetquota													*/
/*																				*/
/********************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "resetquota"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/********************************************************************************/
/* INCLUDE */
/********************************************************************************/
#include "libtpld/define.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <pplib/allg.h>


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
static char* spDatabase	= NULL;
static int iNumberOfDay	= 0; 
static long kumcount	= 0;

static int    			bVersion	 	= FALSE;

/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
static int	KommandoZeileEinlesen( int argc, char** argv );
static int	oeffneDB();
static int	schliesseDB();
static int	PrepareReset();
static int	Reset(char *validity);
static void PrintMsg(char *fun, char *error_msg, char mld );


/********************************************************************************/
/* int main( int argc, char **argv ) */
/********************************************************************************/
int main( int argc, char* argv[] )
{
	char error_msg[512];
	char *fun = "main()";
	char validity[1];
	long lDatum;
	long lWday;

	setbuf(stdout, 0);	

	/*****************************************************/
	/* Aufrufparameter werden ausgelesen */
	/*****************************************************/
	if( !KommandoZeileEinlesen( argc, argv ) == OK )
	{
		printf( "Aufruf: resetquota -db Datenbank\n"							
		 		"Beispiel: > %s <\n"									
		 		"--> setzt alle kummulierten Mengen auf 0", argv[0] );	
		return 1;
	}
	if(bVersion) return 0;

	sprintf( error_msg, "gestartet fuer DB: %s",spDatabase );
	PrintMsg( fun, error_msg, HINWEIS );


	/*****************************************************/
	/* Datenbank oeffnen */
	/*****************************************************/
	if( !oeffneDB() == OK )
	{
		PrintMsg( fun, "Fehler beim Öffnen der Datenbank!", FEHLER );
		return 2;
	} 

	/*****************************************************/
	/* Prepare für Loeschen der Datensaetze */
	/*****************************************************/
	if( !PrepareReset() == OK )
	{
		PrintMsg( fun, "Prepare für Loeschen kummulierte Mengen hat NICHT geklappt!", FEHLER );
		return 3;
	} 
	
	lDatum = AllgGetDate();
	lWday = AllgGetWeekDay(lDatum,error_msg);

	/*****************************************************/
	/* Loeschen der Datensaetze */
	/*****************************************************/

	validity[0] = 'T';
	if( !Reset(validity) == OK )
	{
		printf("Loeschen kummulierte Mengen mit Güligkeit %c hat NICHT geklappt!",validity[0]);
		PrintMsg( fun,error_msg, FEHLER );
		return 30;
	} 
	sprintf( error_msg, "Anzahl abgenullter Datensaetze (articlequota T): %d", kumcount );
	PrintMsg( fun, error_msg, HINWEIS );
	kumcount = 0;
	if(lWday == 0)
	{
		validity[0] = 'W';
		if( !Reset(validity) == OK )
		{
			printf("Loeschen kummulierte Mengen mit Güligkeit %c hat NICHT geklappt!",validity[0]);
			PrintMsg( fun,error_msg, FEHLER );
			return 31;
		}
		sprintf( error_msg, "Anzahl abgenullter Datensaetze (articlequota W): %d", kumcount );
		PrintMsg( fun, error_msg, HINWEIS );
		kumcount = 0;
	}

	if(lDatum%100 == 1)
	{
		validity[0] = 'M';
		if( !Reset(validity) == OK )
		{
			printf("Loeschen kummulierte Mengen mit Güligkeit %c hat NICHT geklappt!",validity[0]);
			PrintMsg( fun,error_msg, FEHLER );
			return 32;
		}
		sprintf( error_msg, "Anzahl abgenullter Datensaetze (articlequota M): %d", kumcount );
		PrintMsg( fun, error_msg, HINWEIS );
		kumcount = 0;
	}
		
	/*****************************************************/
	/* Datenbank schliessen */
	/*****************************************************/
	if( !schliesseDB() == OK )
	{
		PrintMsg( fun, "Fehler beim Schließen der Datenbank!", FEHLER );
		return 4;
	} 

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
		
		if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			spDatabase = argv[i];
		}
 		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			bVersion = TRUE;
			return 0;
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

	spDB = spDatabase;
  
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
/* static int PrepareReset()														*/
/****************************************************************************/
static int PrepareReset()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "PrepareResetReset()";
	unsigned int uiTransactions = 0;

	exec sql begin declare section;
		char	str[2048];
	exec sql end declare section;

	
	/* SELECT-Cursor vorbereiten */
	strcpy( str, "SELECT kumqty FROM articlequota where validity = ? FOR UPDATE" );
	EXEC SQL PREPARE preSelQuota from :str;
	EXEC SQL DECLARE curSelQuota cursor with hold for preSelQuota;
	ERROR_MSG( "DECLARE curSelQuota" );
	exec sql free preSelQuota;

	/* UPDATE-Cursor vorbereiten */
	strcpy( str, "update articlequota set kumqty = 0 WHERE CURRENT OF curSelQuota" );
	EXEC SQL PREPARE preUpdQuota from :str;
	
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
			"pid=%05ld %.10s %s %s->%d/%d\n",
			mld,
			zeit->tm_mday,
			zeit->tm_mon + 1,
			zeit->tm_year,
			zeit->tm_hour,
			zeit->tm_min,
			zeit->tm_sec,
			pid,
			"resetquota",
			fun,
			error_msg, 
			SQLCODE,
			SQLISAM );

	fclose(fp);
}

/****************************************************************************/
/* int Reset()														*/
/****************************************************************************/
int Reset(char *validity)
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "Reset()";
	unsigned int uiTransactions = 0;

	exec sql begin declare section;
		char	cValidity[1];
	exec sql end declare section;

	cValidity[0] = validity[0];

	/* SELECT ausfuehren */
	EXEC SQL OPEN curSelQuota using :cValidity;
	ERROR_MSG( "OPEN curSelQuota" );

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
		
		EXEC SQL FETCH curSelQuota;
		ERROR_MSG( "EXEC SQL FETCH curSelQuota!" );
		
		/* Keine weiteren Datensaetze im Cursor */
		if( SQLCODE == SQLNOTFOUND )
		{
			break;
		}

		EXEC SQL EXECUTE preUpdQuota;
		ERROR_MSG( "EXEC SQL EXECUTE preUpdQuota!" );
		kumcount++;
	}
	
	EXEC SQL COMMIT WORK;	
	ERROR_MSG( "COMMIT WORK2" );
	EXEC SQL CLOSE curSelQuota;
	ERROR_MSG( "EXEC SQL CLOSE curSelQuota!" );
	return OK;
}

/********************************************************************************/
/*     Hauptmodul: delkdkritik.ecc												*/
/*         Source: 																*/
/*          Autor: Ronald Imschweiler											*/
/*       Erstellt: 14.03.2003													*/
/*        Sprache: C															*/
/*        Erzeugt: manuell														*/
/*        Aufgabe: loeschen der Tabelle kdkritik,kdkritikpos,callbackitems		*/
/*         Aufruf: delkdkritik -delOlderThan Anzahltage							*/
/*																				*/
/********************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/
#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "delkdkritik"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

//static char *SCCSID = "@(#)PRZ GmbH Stand: 1.0.1 $Header: /prj/df/unix/delkdkritik/delkdkritik.cxx 11    2.03.04 16:24 66aeimsc $";


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
static char* spDatabase = NULL;
static int iNumberOfDay = 0;
static bool isStatusGiven = false;
static long delKritik = 0;
static long delKritikpos = 0;
static long delItems = 0;
static bool bVersion = false;
exec sql begin declare section;
long lDatum;
int statusNumber;
exec sql end declare section;


/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
static int	KommandoZeileEinlesen( int argc, char** argv );
static int	oeffneDB();
static int	schliesseDB();
static int	Delete();
static void PrintMsg( char* fun, char* error_msg, char mld );


/********************************************************************************/
/* int main( int argc, char **argv ) */
/********************************************************************************/
int main( int argc, char* argv[] )
{
	char error_msg[512];
	char* fun = "main()";

	setbuf(stdout, 0);

	/*****************************************************/
	/* Aufrufparameter werden ausgelesen */
	/*****************************************************/
	if ( !KommandoZeileEinlesen(argc, argv) == OK )
	{
		printf( "Aufruf: DelKdkritik -delolderthan Tage.\n"
			"Beispiel: > %s -delolderthan 60 <\n"
			"--> Loescht alle Datenaetze, die aelter als 60 Tage sind", argv[0] );
		return 1;
	}
	if (bVersion)
	{
		return OK;
	}


	sprintf( error_msg, "gestartet mit Tagen: %d", iNumberOfDay );
	PrintMsg( fun, error_msg, HINWEIS );


	/*****************************************************/
	/* Datenbank oeffnen */
	/*****************************************************/
	if ( !oeffneDB() == OK )
	{
		PrintMsg( fun, "Fehler beim ÷ffnen der Datenbank!", FEHLER );
		return 2;
	}

	/*****************************************************/
	/* Loeschen der Datensaetze */
	/*****************************************************/
	if ( !Delete() == OK )
	{
		PrintMsg( fun, "Loeschen hat NICHT geklappt!", FEHLER );
		return 3;
	}

	/*****************************************************/
	/* Datenbank schliessen */
	/*****************************************************/
	if ( !schliesseDB() == OK )
	{
		PrintMsg( fun, "Fehler beim Schlieﬂen der Datenbank!", FEHLER );
		return 4;
	}


	sprintf( error_msg, "Anzahl geloeschter Datensaetze (Kdkritik/Kdkritikpos/Callbackitems): %d/%d/%d", delKritik, delKritikpos, delItems );
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
	char* schalter;
	char* fun = "KommandoZeileEinlesen()";

	for ( i = 1; i < argc; i++ )
	{
		if ( skip )
		{
			skip = NO;
			continue;
		}
		schalter = argv[i];

		if ( !strcmp(schalter, "-delolderthan") )
		{
			if ( atoi(argv[i + 1]) != 0 ) {
				iNumberOfDay = atoi(argv[i + 1] );
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
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			bVersion = true;
		}
		else if (!strcmp(schalter, "-callbackstatus"))
		{
			if (atoi(argv[i + 1]) != 0) {
				statusNumber = atoi(argv[i + 1]);
				isStatusGiven = true;
				skip = YES;
			}
		}
		else
		{
			skip = ERROR;
			break;
		}
	} /* ENDR FOR */

	if ( argc == 1 || skip == ERROR )
	{
		PrintMsg( fun, "Fehlerhafte Programmparameter", HINWEIS );
		return ERROR; /* Fehlerhafte KommandoZeile */
	}

	lDatum = AllgGetDate();
	lDatum = AllgAddDate(lDatum, (iNumberOfDay * -1), error_msg);
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

	char* fun = "oeffneDatenBank()";

	if ( spDB == NULL )
	{
		exec sql database DATABASE;
		spDatabase = DATABASE;
	}
	else
	{
		exec sql database : spDB;
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
	char* fun = "schliessen DB";
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
	char	str[2048];
	long	lKritiknr;
	exec sql end declare section;

	if (isStatusGiven)
	{
		/* SELECT-Cursor vorbereiten */
		strcpy(str, "SELECT k.kritiknr FROM kdkritik k WHERE EXISTS ( SELECT 1 FROM callbackitems cbi INNER JOIN parameter p on cbi.callbackstatusid = p.parametername and p.programmname='callbackeditor' and p.zweck='statusinfo' WHERE k.kritiknr = cbi.kritiknr AND p.wert = ? ) AND k.datum < ? FOR UPDATE");
	}
	else
	{
		/* SELECT-Cursor vorbereiten */
		strcpy( str, "SELECT kritiknr FROM kdkritik where datum < ? FOR UPDATE" );
	}
	EXEC SQL PREPARE preSelKritik from : str;
	EXEC SQL DECLARE curSelKritik cursor with hold for preSelKritik;
	ERROR_MSG( "DECLARE curSelKritik" );
	exec sql free preSelKritik;

	strcpy( str, "SELECT kritiknr FROM kdkritikpos where kritiknr = ? FOR UPDATE" );
	EXEC SQL PREPARE preSelKritikpos from : str;
	EXEC SQL DECLARE curSelKritikpos cursor with hold for preSelKritikpos;
	ERROR_MSG( "DECLARE curSelKritikpos" );
	exec sql free preSelKritikpos;

	strcpy( str, "SELECT kritiknr FROM callbackitems where kritiknr = ? FOR UPDATE" );
	EXEC SQL PREPARE preSelItems from : str;
	EXEC SQL DECLARE curSelItems cursor with hold for preSelItems;
	ERROR_MSG( "DECLARE curSelItems" );
	exec sql free preSelItems;

	/* DELETE-Cursor vorbereiten */
	strcpy( str, "DELETE FROM kdkritik WHERE CURRENT OF curSelKritik" );
	EXEC SQL PREPARE preDelKritik from : str;

	strcpy( str, "DELETE FROM kdkritikpos WHERE CURRENT OF curSelKritikpos" );
	EXEC SQL PREPARE preDelKritikpos from : str;

	strcpy( str, "DELETE FROM callbackitems WHERE CURRENT OF curSelItems" );
	EXEC SQL PREPARE preDelItems from : str;


	if (isStatusGiven)
	{
		/* SELECT ausfuehren */
		EXEC SQL OPEN curSelKritik using : statusNumber, : lDatum;
		ERROR_MSG("OPEN curSelKritik");

	}
	else
	{
		/* SELECT ausfuehren */
		EXEC SQL OPEN curSelKritik using :lDatum;
		ERROR_MSG( "OPEN curSelKritik" );
	}

	EXEC SQL BEGIN WORK;
	ERROR_MSG( "BEGIN WORK1" );
	for (;;)
	{
		uiTransactions++;
		/* Max. Transaktionen sind erreicht --> Commit setzen */
		if ( ( uiTransactions % MAX_TRANSAKTION ) == 0 )
		{
			EXEC SQL COMMIT WORK;
			ERROR_MSG( "COMMIT WORK1" );
			EXEC SQL BEGIN WORK;
			ERROR_MSG( "BEGIN WORK2" );
		}
		EXEC SQL FETCH curSelKritik into : lKritiknr;
		ERROR_MSG( "EXEC SQL FETCH curSelKritik!" );

		/* Keine weiteren Datensaetze im Cursor */
		if ( SQLCODE == SQLNOTFOUND )
		{
			break;
		}

		EXEC SQL EXECUTE preDelKritik;
		ERROR_MSG( "EXEC SQL EXECUTE preDelKritik!" );
		delKritik++;

		EXEC SQL OPEN curSelKritikpos using :lKritiknr;
		ERROR_MSG( "OPEN curSelKritikpos" );
		for (;;)
		{
			EXEC SQL FETCH curSelKritikpos;
			ERROR_MSG( "EXEC SQL FETCH curSelKritikpos!" );

			if ( SQLCODE == SQLNOTFOUND )
			{
				break;
			}

			EXEC SQL EXECUTE preDelKritikpos;
			ERROR_MSG( "EXEC SQL EXECUTE preDelKritikpos!" );
			delKritikpos++;
		}
		EXEC SQL CLOSE curSelKritikpos;
		ERROR_MSG( "EXEC SQL CLOSE curSelKritikpos!" );

		EXEC SQL OPEN curSelItems using :lKritiknr;
		ERROR_MSG( "OPEN curSelItems" );
		for (;;)
		{
			EXEC SQL FETCH curSelItems;
			ERROR_MSG( "EXEC SQL FETCH curSelItems!" );

			if ( SQLCODE == SQLNOTFOUND )
			{
				break;
			}

			EXEC SQL EXECUTE preDelItems;
			ERROR_MSG( "EXEC SQL EXECUTE preDelItems!" );
			delItems++;
		}
		EXEC SQL CLOSE curSelItems;
		ERROR_MSG( "EXEC SQL CLOSE curSelItems!" );
	}

	EXEC SQL COMMIT WORK;
	ERROR_MSG( "COMMIT WORK2" );
	EXEC SQL CLOSE curSelKritik;
	ERROR_MSG( "EXEC SQL CLOSE curSelKritik!" );

	return OK;
}
/************************************************************************************************************/
/* static void PrintMsg(char *fun, char *error_msg, char mld ) */
/************************************************************************************************************/
static void PrintMsg( char* fun, char* error_msg, char mld )
{
	FILE* fp;
	struct tm* localtime();
	struct tm* zeit;
	long hour1;
	pid_t pid;
	long time();
	char logFile[L_TEXT];
	char* env;

	pid = getpid();
	hour1 = time( &hour1 );
	zeit = localtime( &hour1 );

	env = getenv( "LOG_PATH" );
	if ( env == NULL )
		env = ".";
	sprintf( logFile, "%s/wws.log", env );

	if ( ( fp = fopen( logFile, "a" ) ) == (FILE*)0 )
		return;

	if (    zeit->tm_year > 99 ) zeit->tm_year -= 100;

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
		"delkdkritik",
		fun,
		error_msg,
		SQLCODE,
		SQLISAM );

	fclose(fp);
}

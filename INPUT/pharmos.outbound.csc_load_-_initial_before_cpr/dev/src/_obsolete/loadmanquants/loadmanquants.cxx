/********************************************************************************/
/*     Hauptmodul: loadmanquants.ecc												*/
/*         Source: 																*/
/*          Autor: Ronald Imschweiler											*/
/*       Erstellt: 29.08.2006													*/
/*        Sprache: C															*/
/*        Erzeugt: manuell														*/
/*        Aufgabe: loeschen Ruf mit entsprechendem Kennzeichen in Kunde		    */
/*         Aufruf: delrufplan													*/
/*																				*/
/********************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadmanquants"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/********************************************************************************/
/* INCLUDE */
/********************************************************************************/
//#include "libtpld/define.h"
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "pplib/allg.h"


/********************************************************************************/
/* DEFINE */
/********************************************************************************/

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/* #undef NULL  */

#define DEBUG_SECTION      if ( debug_enabled ) {
#define END_DEBUG_SECTION  }
#define OK                 0
#define NO                 0
#define YES                1
#define ERROR             -1
#define INSERT             1
#define NOT_FOUND          1
#define FILE_NOT_FOUND     1
#define WARNING           -2
#define HINW             'H'
#define FEHL             'F'
#define RIO_EOF          110
#define STR_NULL         "+000000000000000"
#define STR_NULL2        "+00000,00"
#define BLANC            ' '
#define MAX_TRANSAKTION     300
#define SQLISAM         sqlca.sqlerrd[1]         /* Sql-Cisam-Fehler       */
#define L_TEXT             81

typedef struct timeval timeval_t; 
#define DATABASE       "phosix"
/********************************************************************************/
/* MACROS */
/********************************************************************************/
#define ERROR_MSG( x )      if( SQLCODE < 0 ){				\
								PrintMsg( fun, x, FEHL ); \
								return ERROR;				\
							}


/********************************************************************************/
/* MODUL-GLOBALE VARIABLEN */
/********************************************************************************/
static char* spDatabase		= NULL;
static long UpdLokalDef		= 0;
static long UpdLokalPlus	= 0;

exec sql begin declare section;
	long lDatum;
	short sVz;
exec sql end declare section;


/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
static int	KommandoZeileEinlesen( int argc, char** argv );
static int	oeffneDB();
static int	schliesseDB();
static int	PreUpdLokal();
static int	UpdLokal();
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
		printf( "Aufruf: %s -db Datenbank -vz Filialnr \n"
		 		"Beispiel: > %s -db pos1g@db1_pos1_tcp -vz 49<\n"		
				"--> Update Artikelbestaende Ratio\n", argv[0], argv[0] );fflush(stdout);
		return 1;
	}

    
	sprintf( error_msg, "gestartet mit -db %s", spDatabase );
	PrintMsg( fun, error_msg, HINW );


	/*****************************************************/
	/* Datenbank oeffnen */
	/*****************************************************/
	if( !oeffneDB() == OK )
	{
		PrintMsg( fun, "Fehler beim ÷ffnen der Datenbank!", FEHL );
		return 2;
	} 

	/*****************************************************/
	/* Formatieren der Lagerbest‰nde + codeblocage       */
	/*****************************************************/
	if( !PreUpdLokal() == OK )
	{
		PrintMsg( fun, "Formatieren der Lagerbestaende hat NICHT geklappt!", FEHL );
		return 3;
	} 

	/*****************************************************/
	/* Update der Lagerbest‰nde + codeblocage            */
	/*****************************************************/
	if( !UpdLokal() == OK )
	{
		PrintMsg( fun, "Update der Lagerbestaende hat NICHT geklappt!", FEHL );
		return 4;
	} 
		
	/*****************************************************/
	/* Datenbank schliessen */
	/*****************************************************/
	if( !schliesseDB() == OK )
	{
		PrintMsg( fun, "Fehler beim Schlieﬂen der Datenbank!", FEHL );
		return 5;
	} 

	
	sprintf( error_msg, "Anzahl geaenderter Bestaende : %d/%d", UpdLokalDef, UpdLokalPlus );
	PrintMsg( fun, error_msg, HINW );
	PrintMsg( fun, "beendet", HINW );

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
		else if ( !strcmp( schalter, "-vz" ) )
		{
			i++;
			sVz = atoi(argv[i]);
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			exit(0);
		}
		else
		{
			skip = ERROR;
			break;
		}
	} /* ENDR FOR */                                            

	if( argc == 1 || skip == ERROR )
	{
		PrintMsg( fun, "Fehlerhafte Programmparameter", HINW );
		return ERROR; /* Fehlerhafte KommandoZeile */
	}
	lDatum = AllgGetDate();

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
/* static int UpdLokal()														*/
/****************************************************************************/

static int PreUpdLokal()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "PreUpdLokal";
	unsigned int uiTransactions = 0;

	exec sql begin declare section;
		long	lBestand;
		char	str[2048];
	exec sql end declare section;

	/* SELECT-Cursor vorbereiten */
	strcpy( str, "SELECT bestand " );
	strcat( str, "FROM artikellokal " );
	strcat( str, "where filialnr = ? " );
	strcat( str, "FOR UPDATE" );
	EXEC SQL PREPARE preVorSelLokal from :str;
	EXEC SQL DECLARE curVorSelLokal cursor with hold for preVorSelLokal;
	ERROR_MSG( "DECLARE curVorSelLokal" );

	strcpy( str, "UPDATE artikellokal " );
	strcat( str, "set bestand = 10000 " );
	strcat( str, ",codeblocage = 0 " );
	strcat( str, "WHERE CURRENT OF curVorSelLokal" );
	EXEC SQL PREPARE preVorUpdLokal from :str;

	/* SELECT ausfuehren */
	EXEC SQL OPEN curVorSelLokal using :sVz ;
	ERROR_MSG( "OPEN curVorSelLokal" );
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
		
		/* Keine weiteren Datensaetze im Cursor */
		if( SQLCODE == SQLNOTFOUND )
		{
			break;
		}
		/* SELECT ausfuehren */
		EXEC SQL FETCH curVorSelLokal;
		ERROR_MSG( "EXEC SQL FETCH curVorSelLokal!" );
		if( SQLCODE == SQLNOTFOUND )
		{
			continue;
		}
		EXEC SQL EXECUTE preVorUpdLokal;
		ERROR_MSG( "EXEC SQL EXECUTE preVorUpdLokal!" );
	}

	EXEC SQL COMMIT WORK;	
	ERROR_MSG( "COMMIT WORK2" );
	
	return OK;
}

/****************************************************************************/
/* static int UpdLokal()														*/
/****************************************************************************/

static int UpdLokal()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "UpdLokal";
	unsigned int uiTransactions = 0;

	exec sql begin declare section;
		long	lArtikelnr;
		long	lBestand;
		char	cCip[14];
		char	cCodeblocage[2];
		char	str[2048];
	exec sql end declare section;

	/* SELECT-Cursor vorbereiten */
	strcpy( str, "SELECT cip,codeblocage " );
	strcat( str, "FROM manquants " );
	strcat( str, "where infotype = 'PROD' " );
	strcat( str, "FOR UPDATE" );
	EXEC SQL PREPARE preSelManquants from :str;
	EXEC SQL DECLARE curSelManquants cursor with hold for preSelManquants;
	ERROR_MSG( "DECLARE curSelManquants" );

	/* Update-Cursor vorbereiten */
	strcpy( str, "delete from manquants " );
	strcat( str, "WHERE CURRENT OF curSelManquants" );
	EXEC SQL PREPARE preDelManquants from :str;

	strcpy( str, "SELECT bestand " );
	strcat( str, "FROM artikellokal " );
	strcat( str, "where filialnr = ? " );
	strcat( str, "and artikel_nr = ? " );
	strcat( str, "FOR UPDATE" );
	EXEC SQL PREPARE preSelLokal from :str;
	EXEC SQL DECLARE curSelLokal cursor with hold for preSelLokal;
	ERROR_MSG( "DECLARE curSelLokal" );

	strcpy( str, "UPDATE artikellokal " );
	strcat( str, "set bestand = ? " );
	strcat( str, ",codeblocage = ? " );
	strcat( str, "WHERE CURRENT OF curSelLokal" );
	EXEC SQL PREPARE preUpdLokal from :str;

	strcpy( str, "SELECT artikel_nr " );
	strcat( str, "FROM artikelnummern " );
	strcat( str, "where ean = ? " );
	EXEC SQL PREPARE preSelNummer from :str;
	EXEC SQL DECLARE curSelNummer cursor with hold for preSelNummer;
	ERROR_MSG( "DECLARE curSelNummer" );

	/* SELECT ausfuehren */
	EXEC SQL OPEN curSelManquants;
	ERROR_MSG( "OPEN curSelManquants" );

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
		
		EXEC SQL FETCH curSelManquants into :cCip,:cCodeblocage;
		ERROR_MSG( "EXEC SQL FETCH curSelManquants!" );
		
		/* Keine weiteren Datensaetze im Cursor */
		if( SQLCODE == SQLNOTFOUND )
		{
			break;
		}
		/* SELECT Nummern ausfuehren */
/*		EXEC SQL OPEN curSelNummer using :cCip ;
		ERROR_MSG( "OPEN curSelNummer" );
		EXEC SQL FETCH curSelNummer into :lArtikelnr;
		ERROR_MSG( "EXEC SQL FETCH curSelNummer!" );
		if( SQLCODE == SQLNOTFOUND )
		{
			continue;
		}
*/		/* SELECT ausfuehren */
		EXEC SQL OPEN curSelLokal using :sVz,:cCip ;
		ERROR_MSG( "OPEN curSelLokal" );
		EXEC SQL FETCH curSelLokal;
		ERROR_MSG( "EXEC SQL FETCH curSelLokal!" );
		if( SQLCODE == SQLNOTFOUND )
		{
			continue;
		}
		if(cCodeblocage[0] == '0')
		{
			UpdLokalPlus++;
			lBestand = 10000;
		}
		else
		{
			UpdLokalDef++;
			lBestand = 0;
		}
		EXEC SQL EXECUTE preUpdLokal using :lBestand,:cCodeblocage;
		ERROR_MSG( "EXEC SQL EXECUTE preUpdLokal!" );

		EXEC SQL EXECUTE preDelManquants;
		ERROR_MSG( "EXEC SQL EXECUTE preDelManquants!" );
	}

	EXEC SQL COMMIT WORK;	
	ERROR_MSG( "COMMIT WORK2" );
	
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
			"pid=%05ld %.13s %s %s->%d/%d\n",
			mld,
			zeit->tm_mday,
			zeit->tm_mon + 1,
			zeit->tm_year,
			zeit->tm_hour,
			zeit->tm_min,
			zeit->tm_sec,
			pid,
			"loadmanquants",
			fun,
			error_msg, 
			SQLCODE,
			SQLISAM );

	fclose(fp);
}

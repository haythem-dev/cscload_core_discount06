/************************************************************************************************/
/*     Hauptmodul: deloldsubsequent.ecc															*/
/*         Source: 																				*/
/*          Autor: Ronald Imschweiler															*/
/*       Erstellt: 09.08.2021																	*/
/*        Sprache: C																			*/
/*        Erzeugt: manuell																		*/
/*        Aufgabe: loeschen Eintraege aus der Tabelle nachlieferpos aelter als ...  			*/
/*         Aufruf: deloldsubsequent.sh -start [-branchno NN,NN,NN...] -del NNN					*/
/*																								*/
/************************************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/
#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "deloldsubsequent"

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
#include "libtpld/qtime.h"


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
static	char*	spDatabase		= NULL;
static	long	delItems		= 0;
static	long	delReserved		= 0;
static	long	CountNumbers	= 0;
static	char	cBranchnos[2048];
static	char	cExOrderTypes[256];
static	char	cInOrderTypes[256];
static	int		iDelDays		= 90;	//Standard 3 Monate
static	bool	bVersion		= false;
static	char	cPrintDate[11];

exec sql begin declare section;
		char cDateOld[9];
exec sql end declare section;


/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
static int	KommandoZeileEinlesen( int argc, char** argv );
static int	oeffneDB();
static int	schliesseDB();
static int	Delete(char *error_msg);
static void PrintMsg(char *fun, char *error_msg, char mld );
static void transform(const char* input, char* output);

/********************************************************************************/
/* int main( int argc, char **argv ) */
/********************************************************************************/
int main( int argc, char* argv[] )
{
	char error_msg[512];
	char *fun = "main()";

	setbuf(stdout, 0);

	cBranchnos[0] = '\0';	//Standard keine Filiale

	/*****************************************************/
	/* Aufrufparameter werden ausgelesen */
	/*****************************************************/
	if( !KommandoZeileEinlesen( argc, argv ) == OK )
	{
		printf( "Aufruf: deloldsubsequent.sh -start [-branchno NN,NN,NN...] [-excludeOrderTypes OT,OT,OT...] [-includeOrderTypes OT,OT,OT...] [-del NNN]\n"							
			"Beispiel:  %s -branchno 9,31 <\n"
			"				-del 90 <\n"
		 	"--> Loescht alle Datenaetze der Filialen 9 und 31 mit Datum aelter 90 Tagen\n"
			"--> erfolgt keine Filialeingabe werden alle Filialen ausser 21 bearbeitet" , argv[0] );	
		return 1;
	}
	if(bVersion)
	{
		return OK;
	}

	if (cBranchnos[0] != '\0')
	{
		sprintf(error_msg, "gestartet fuer Eintraege der Filiale(n): %s aelter als %d Tage --> Datum %s", cBranchnos, iDelDays, cPrintDate);
	}
	else
	{
		sprintf(error_msg, "gestartet fuer Eintraege aelter als %d Tage --> Datum %s", iDelDays, cPrintDate);
	}
	PrintMsg( fun, error_msg, HINWEIS );


	/*****************************************************/
	/* Datenbank oeffnen */
	/*****************************************************/
	if( !oeffneDB() == OK )
	{
		PrintMsg( fun, "Fehler beim Oeffnen der Datenbank!", FEHLER );
		return 2;
	} 
	
	/*****************************************************/
	/* Loeschen der Datensaetze */
	/*****************************************************/
	if( !Delete(error_msg) == OK )
	{
		PrintMsg( fun, "Loeschen hat NICHT geklappt!", FEHLER );
		return 3;
	} 
		
	/*****************************************************/
	/* Datenbank schliessen */
	/*****************************************************/
	if( !schliesseDB() == OK )
	{
		PrintMsg( fun, "Fehler beim Schliessen der Datenbank!", FEHLER );
		return 4;
	} 

	
	sprintf( error_msg, "Anzahl geloeschter Datensaetze: %d davon reserviert: %d", delItems, delReserved);
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
	char cOutputOT[256];
	char cInputOT[256];
	int i;
	int skip = NO;
	char *schalter;
	char *fun = "KommandoZeileEinlesen()";
	timeval_t timev_s;
	timeStr   *time_d;

	cBranchnos[0] = '\0';
	cExOrderTypes[0] = '\0';
			
	for( i = 1; i < argc; i++ )
	{
		if( skip )
		{
			skip = NO;
			continue;
		}
		schalter = argv[i];
		
		if( !strcmp(schalter, "-branchno") )
		{
			i++;
			strcpy(cBranchnos, argv[i] );
		}
		else if (!strcmp(schalter, "-excludeOrderTypes"))
		{
			i++;
			strcpy(cExOrderTypes, argv[i]);
			strcpy(cInputOT, cExOrderTypes);
			transform(cInputOT, cOutputOT);
			strcpy(cExOrderTypes, cOutputOT);
		}
		else if (!strcmp(schalter, "-includeOrderTypes"))
		{
			i++;
			strcpy(cInOrderTypes, argv[i]);
			strcpy(cInputOT, cInOrderTypes);
			transform(cInputOT, cOutputOT);
			strcpy(cInOrderTypes, cOutputOT);
		}
		else if (!strcmp(schalter, "-del"))
		{
			i++;
			iDelDays = atoi(argv[i]);
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
		else
		{
			skip = ERROR;
			break;
		}
	} /* ENDR FOR */                                            

	if( argc == 1 || skip == ERROR)
	{
		PrintMsg( fun, "Fehlerhafte Programmparameter", HINWEIS );
		return ERROR; /* Fehlerhafte KommandoZeile */
	}
	gettimeofday(&timev_s, NULL);
	timev_s.tv_sec = timev_s.tv_sec - (24 * 60 * 60 * iDelDays);
	/*7776000 == 90 Tage in Sec         */
	time_d = (timeStr *)TimeOfDay(timev_s.tv_sec);
	sprintf(cDateOld, "%04d%02d%02d", time_d->year, time_d->mon, time_d->day);
	sprintf(cPrintDate, "%02d.%02d.%04d", time_d->day, time_d->mon, time_d->year);
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
static int Delete(char *error_msg)
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*			fun = "Delete()";
	unsigned int uiTransactions = 0;
	static	char	cArtikelNr[10];

	exec sql begin declare section;
		char	str[2048];
		short	sPosTyp;
		short	sBranchNo;
		long	lCustomerNo;
		long	lArtikelnr;
		long	lReservedQty;
		char	code[26];
	exec sql end declare section;

	
	
	/* SELECT-Cursor Nachlieferpos vorbereiten */
	strcpy(str, "SELECT postyp,vertriebszentrumnr,kundennr,artikel_nr,menge FROM nachlieferpos ");
	if (cBranchnos[0] != '\0')
	{
		strcat(str, "where vertriebszentrumnr in (");
		strcat(str, cBranchnos);
		strcat(str, ") ");
	}
	else
	{
		strcat(str, "where vertriebszentrumnr != 21 " );
	}
	/*Exclude order types from deletion*/
	if (cExOrderTypes[0] != '\0')
	{
		strcat(str, "and kdauftragart not in (");
		strcat(str, cExOrderTypes);
		strcat(str, ") ");
	}
	/*Include order types from deletion*/
	if (cInOrderTypes[0] != '\0')
	{
		strcat(str, "and kdauftragart in (");
		strcat(str, cInOrderTypes);
		strcat(str, ") ");
	}
	strcat(str, "and postyp in (3,5) ");
	strcat(str, "and datum < ");
	strcat(str, cDateOld);
	strcat(str, " FOR UPDATE");
	
	PrintMsg( fun, str, HINWEIS );
	
	EXEC SQL PREPARE preSelNachl from :str;
	EXEC SQL DECLARE curSelNachl cursor with hold for preSelNachl;
	ERROR_MSG( "DECLARE curSelNachl" );
	exec sql free preSelNachl;

	/* DELETE-Cursor Nachlieferpos  vorbereiten */
	strcpy( str, "DELETE FROM nachlieferpos WHERE CURRENT OF curSelNachl" );
	EXEC SQL PREPARE preDelNachl from :str;


	/* SELECT-Cursor CstStockReserved vorbereiten */
	strcpy(str, "SELECT reservedqty FROM cststockreserved ");
	strcat(str, "where branchno = ? ");
	strcat(str, "and customerno = ? ");
	strcat(str, "and articleno = ? ");
	strcat(str, "and reservtype = 7 ");
	strcat(str, "and reservedqty = ? ");
	strcat(str, " FOR UPDATE");
	EXEC SQL PREPARE preSelStockReserved from :str;
	EXEC SQL DECLARE curSelStockReserved cursor with hold for preSelStockReserved;
	ERROR_MSG("DECLARE curSelStockReserved");
	exec sql free preSelStockReserved;

	/* DELETE-Cursor CstStockReserved vorbereiten */
	strcpy(str, "DELETE FROM cststockreserved WHERE CURRENT OF curSelStockReserved");
	EXEC SQL PREPARE preDelStockReserved from :str;


	
	/* SELECT ausfuehren */
	EXEC SQL OPEN curSelNachl;
	ERROR_MSG( "OPEN curSelNachl" );

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
		
		EXEC SQL FETCH curSelNachl into
			:sPosTyp,
			:sBranchNo,
			:lCustomerNo,
			:lArtikelnr,
			:lReservedQty;
		ERROR_MSG( "EXEC SQL FETCH curSelNachl!" );
		
		/* Keine weiteren Datensaetze im Cursor */
		if( SQLCODE == SQLNOTFOUND )
		{
			break;
		}

		EXEC SQL EXECUTE preDelNachl;
		ERROR_MSG( "EXEC SQL EXECUTE preDelNachl!" );
		delItems++;

		if (sPosTyp == 5)
		{
			EXEC SQL OPEN curSelStockReserved using
				:sBranchNo,
				:lCustomerNo,
				:lArtikelnr,
				:lReservedQty;
			ERROR_MSG("OPEN curSelStockReserved");
			EXEC SQL FETCH curSelStockReserved into :lReservedQty;
			ERROR_MSG("EXEC SQL FETCH curSelStockReserved!");

			/* Keine weiteren Datensaetze im Cursor */
			if (SQLCODE != SQLNOTFOUND)
			{
				EXEC SQL EXECUTE preDelStockReserved;
				ERROR_MSG("EXEC SQL EXECUTE preDelStockReserved!");
				delReserved++;
			}
		}

	}
	
	EXEC SQL COMMIT WORK;	
	ERROR_MSG( "COMMIT WORK2" );
	EXEC SQL CLOSE curSelNachl;
	ERROR_MSG( "EXEC SQL CLOSE curSelNachl!" );

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
			"pid=%05ld %s %s %s->%d/%d\n",
			mld,
			zeit->tm_mday,
			zeit->tm_mon + 1,
			zeit->tm_year,
			zeit->tm_hour,
			zeit->tm_min,
			zeit->tm_sec,
			pid,
			"deloldsubsequent",
			fun,
			error_msg, 
			SQLCODE,
			SQLISAM );

	fclose(fp);
}


void transform(const char* input, char* output) {
    // Pointers to traverse the input and output strings
    const char* pInput = input;
    char* pOutput = output;
            
    // Start with a single quote
    *pOutput++ = '\'';
    
    while (*pInput) {
	// If we find a comma in the input, finish the current quoted token
	// and start a new one.
	if (*pInput == ',') {
    	    *pOutput++ = '\'';
            *pOutput++ = ',';
            *pOutput++ = ' ';
            *pOutput++ = '\'';
            pInput++; // Move past the comma in the input
        } else {
    	    // Otherwise, just copy the character over
            *pOutput++ = *pInput++;
        }
    }

    // Close the last quoted token
    *pOutput++ = '\'';
    *pOutput = '\0'; // Null-terminate the output string
}

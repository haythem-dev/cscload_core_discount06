/************************************************************************************************/
/*     Hauptmodul: delvaccinsubsequent.ecc														*/
/*         Source: 																				*/
/*          Autor: Ronald Imschweiler															*/
/*       Erstellt: 29.03.2021																	*/
/*        Sprache: C																			*/
/*        Erzeugt: manuell																		*/
/*        Aufgabe: loeschen Vaccine aus der Tabelle nachlieferpos								*/
/*         Aufruf: delvaccinsubsequent.sh -start [-branchno NN] -artno NNN,NNN,NNN....			*/
/*																								*/
/************************************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/
#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "delvaccinsubsequent"

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
#define BUFFER_LEN 2048
static	char*	spDatabase		= NULL;
static	long	delItems		= 0;
static	long	CountNumbers	= 0;
static	char	cPZNs[BUFFER_LEN];
static	char	cArtGroups[BUFFER_LEN];
static  char    cArticleNos[BUFFER_LEN];
static  short   sBranchNo = 0;
static  char    cBranchNo[3];
static	bool	bVersion		= false;


/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
static int	KommandoZeileEinlesen( int argc, char** argv );
static int	oeffneDB();
static int	schliesseDB();
static int	Delete(char *error_msg);
static void PrintMsg(char *fun, char *error_msg, char mld );


/********************************************************************************/
/* int main( int argc, char **argv ) */
/********************************************************************************/
int main( int argc, char* argv[] )
{
	char error_msg[BUFFER_LEN];
	memset(error_msg, 0, BUFFER_LEN);

	char *fun = "main()";

	setbuf(stdout, 0);	
	memset(cPZNs, 0, BUFFER_LEN);
	memset(cArticleNos, 0, BUFFER_LEN);
	memset(cArtGroups, 0, BUFFER_LEN);

	/*****************************************************/
	/* Aufrufparameter werden ausgelesen */
	/*****************************************************/
	if( !KommandoZeileEinlesen( argc, argv ) == OK )
	{
		printf("Aufruf: delvaccinsubsequent.sh -start [-branchno NN] -artno NNN,NNN,NNN -artgrp NNNNN,NNNNN,NNNNN...\n"
			"Beispiel:  %s -branchno 9 <\n"
			"			%s -artno 12,234 <\n"
			   "           %s -artgrp 05174,05175 <\n"
			   "--> Loescht alle Datenaetze der Filiale 9 mit den Artikelnummern 12 und 234 und/oder alle Datens‰tze mit Warengruppe 05174 und 05175\n", argv[0]);
		return 1;
	}
	if(bVersion)
	{
		return OK;
	}

	if (sBranchNo > 0)
	{
		if (cArtGroups[0] == '\0' && cPZNs[0] != '\0')
		sprintf(error_msg, "gestartet fuer Filiale: %d und Artikelnummern %s", sBranchNo, cPZNs);
		else if (cArtGroups[0] != '\0' && cPZNs[0] != '\0')
			sprintf(error_msg, "gestartet fuer Filiale: %d und Artikelnummern %s und Warengruppe %s", sBranchNo, cPZNs, cArtGroups);
		else if (cArtGroups[0] != '\0' && cPZNs[0] == '\0')
			sprintf(error_msg, "gestartet fuer Filiale: %d und Warengruppe %s", sBranchNo, cArtGroups);
	}
	else
	{
		if(cArtGroups[0] == '\0' && cPZNs[0] != '\0')
		sprintf(error_msg, "gestartet fuer Artikelnummern %s", cPZNs);
		else if (cArtGroups[0] != '\0' && cPZNs[0] != '\0')
			sprintf(error_msg, "gestartet fuer Artikelnummern %s und Warengruppen %s ", cPZNs, cArtGroups);
		else if (cArtGroups[0] != '\0' && cPZNs[0] == '\0')
			sprintf(error_msg, "gestartet fuer Warengruppen %s ", cArtGroups);
	}
	PrintMsg( fun, error_msg, HINWEIS );


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
		PrintMsg( fun, "Fehler beim Schlieﬂen der Datenbank!", FEHLER );
		return 4;
	} 

	
	sprintf( error_msg, "Anzahl geloeschter Datensaetze: %d", delItems );
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

	cPZNs[0] = '\0';
	cArtGroups[0] = '\0';
			
	for( i = 1; i < argc; i++ )
	{
		if( skip )
		{
			skip = NO;
			continue;
		}
		schalter = argv[i];
		
		if( strcmp(schalter, "-branchno") == 0 )
		{
			i++;
			if( i < argc && atoi(argv[i]) != 0 )
			{
				strcpy(cBranchNo, argv[i] );
				sBranchNo = atoi( argv[i] );
			}
			else
			{
				skip = ERROR;
				break;
			}
		}
		else if (strcmp(schalter, "-artno") == 0)
		{
			i++;
			if (i < argc)
			{
			strcpy(cPZNs, argv[i]);
		}
			else
			{
				skip = ERROR;
				break;
			}
		}
		else if (strcmp(schalter, "-artgrp") == 0)
		{
			i++;
			if (i < argc)
			{
				strcpy(cArtGroups, argv[i]);
			}
			else
			{
				skip = ERROR;
				break;
			}
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			if (i < argc)
			{
			spDatabase = argv[i];
		}
			else
			{
				skip = ERROR;
				break;
			}
			
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

	if( argc == 1 || skip == ERROR || (cPZNs[0] == '\0' && cArtGroups[0] == '\0'))
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
#define CODE_LEN 10
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*			fun = "Delete()";
	unsigned int uiTransactions = 0;
	static	char	cArtikelNr[CODE_LEN];	// for article no 7 digits
	static  char    artGroup[CODE_LEN];		// article group no 5 digits

	exec sql begin declare section;
		char	str[BUFFER_LEN];
		long	lArtikelnr;
		char	code[CODE_LEN];			    // for PZN only  8 digits
	exec sql end declare section;

	int ende = strlen(cPZNs);
	int start = 0;
	int first = 0;
	int len;

	// First option select artikel_nr fromd articlecodes of cPZNs have been
	// provided.

	memset(str, 0, BUFFER_LEN);
	strcpy(str, "SELECT articleno FROM articlecodes where article_code = ?");
	EXEC SQL PREPARE preSelArtcodes from :str;

	for (int count = 0;;)
	{
		// if no PCNs are specified, the first entry will be equal to '\0'
		if (cPZNs[count] == ',' || cPZNs[count] == '\0')
		{
			len = count - start;
			if (len > 0 && len < CODE_LEN)
			{
				memset(code, 0, CODE_LEN); // no number from previous copy should remain
			strncpy(code,cPZNs + start, len);
			EXEC SQL EXECUTE preSelArtcodes into :lArtikelnr using :code;
			if (SQLCODE == SQLNOTFOUND)
			{
					// Each PCN not identified will be logged
				sprintf(error_msg, "PZN nicht vorhanden: %s", code);
				PrintMsg(fun, error_msg, HINWEIS);
				if (count++ >= ende) break;
				continue;
			}
				memset(cArtikelNr, 0, CODE_LEN);
			sprintf(cArtikelNr, "%d", lArtikelnr);
			if (first == 0)
			{
				first = 1;
					memset(cArticleNos, 0, BUFFER_LEN);
				strcpy(cArticleNos, cArtikelNr);
			}
			else
			{
				strcat(cArticleNos, ",");
				strcat(cArticleNos, cArtikelNr);
			}
			}
			else if (len >= CODE_LEN)
			{
				char tmpError[len + 1];
				memset(tmpError, 0, len + 1);
				strncpy(tmpError, cPZNs + start, len);
				sprintf(error_msg, "PZN ist zu lang: %s", tmpError);
				PrintMsg(fun, error_msg, HINWEIS);
				// ignore this value but continue to increment and check end of string
			}
			start = start + len +1;
		}
		if (count++ >= ende) break;
	}


	/* Second Select article by warengruppe if cArtGroups have been provided */
	if (cArtGroups != NULL && cArtGroups[0] != '\0')
	{
		int artGrpStart = 0;
		int artGrpFirst = 0;
		int artGrpEnde = strlen(cArtGroups);

		memset(str, 0, BUFFER_LEN);
		strcpy(str, "SELECT artikel_nr FROM artikelzentral WHERE warengruppeeigen IN (");
		for (int artGrpCount = 0;;)
		{
			// if no -artgrp parameter for warengruppe are specified the first entry will be '\0'
			if (cArtGroups[artGrpCount] == ',' || cArtGroups[artGrpCount] == '\0')
			{
				len = artGrpCount - artGrpStart;
				if (len > 0)
				{
					memset(artGroup, 0, CODE_LEN);
					strncpy(artGroup, cArtGroups + artGrpStart, len);

					if (artGrpFirst == 0)
					{
						strcat(str, "'");
						artGrpFirst = 1;
					}
					else
					{
						strcat(str, ", '");
					}
					strncat(str, artGroup,len);
					strcat(str, "'");
				}
				artGrpStart = artGrpStart + len + 1;
			}
			if (artGrpCount++ >= artGrpEnde) break;
		}
		strcat(str, ")");

		EXEC SQL PREPARE preSelWarengruppe FROM :str;
		EXEC SQL DECLARE artCursor CURSOR FOR preSelWarengruppe;
		EXEC SQL OPEN artCursor;

		while (true)
		{
			EXEC SQL FETCH artCursor INTO :lArtikelnr;
			if (SQLCODE == SQLNOTFOUND)
				break;
			
			memset(cArtikelNr, 0, CODE_LEN);
			sprintf(cArtikelNr, "%d", lArtikelnr);

			if (first == 0)
			{
				first = 1;
				strcpy(cArticleNos, cArtikelNr);
			}
			else
			{
				strcat(cArticleNos, ",");
				strcat(cArticleNos, cArtikelNr);
			}
			if (strlen(cArticleNos) > BUFFER_LEN)
			{
				sprintf(error_msg, "zu viele Artikelnummern innerhalb einer Selektion. Buffer zu %d zu klein f¸r alle Artikel.", BUFFER_LEN);
				PrintMsg(fun, error_msg, HINWEIS);
				return ERROR;
			}
		}
		EXEC SQL CLOSE artCursor;
	}

	if (first == 0)
	{
		sprintf(error_msg, "keine gueltigen Artikelnummern vorhanden weder innerhalb PCNs: %s\nnoch durch Auswahl ¸ber die Warengruppe: %s", cPZNs, cArtGroups);
		PrintMsg(fun, error_msg, HINWEIS);
		return ERROR;
	}

	/* SELECT-Cursor vorbereiten */
	strcpy(str, "SELECT artikel_nr FROM nachlieferpos ");
	if (sBranchNo > 0)
	{
		strcat(str, "where vertriebszentrumnr = ");
		strcat(str, cBranchNo);
	}
	else
	{
		strcat(str, "where vertriebszentrumnr > 0 " );
	}
	strcat(str, "and artikel_nr in (");
	strcat(str, cArticleNos);
	strcat(str, ") ");
	strcat(str, "FOR UPDATE");
	EXEC SQL PREPARE preSelNachl from :str;
	EXEC SQL DECLARE curSelNachl cursor with hold for preSelNachl;
	ERROR_MSG( "DECLARE curSelNachl" );
	exec sql free preSelNachl;

	/* DELETE-Cursor vorbereiten */
	strcpy( str, "DELETE FROM nachlieferpos WHERE CURRENT OF curSelNachl" );
	EXEC SQL PREPARE preDelNachl from :str;
	
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
		
		EXEC SQL FETCH curSelNachl into :lArtikelnr;
		ERROR_MSG( "EXEC SQL FETCH curSelNachl!" );
		
		/* Keine weiteren Datensaetze im Cursor */
		if( SQLCODE == SQLNOTFOUND )
		{
			break;
		}

		EXEC SQL EXECUTE preDelNachl;
		ERROR_MSG( "EXEC SQL EXECUTE preDelNachl!" );
		delItems++;

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
			"pid=%05ld %.18s %s %s->%d/%d\n",
			mld,
			zeit->tm_mday,
			zeit->tm_mon + 1,
			zeit->tm_year,
			zeit->tm_hour,
			zeit->tm_min,
			zeit->tm_sec,
			pid,
			"delvaccinsubsequent",
			fun,
			error_msg, 
			SQLCODE,
			SQLISAM );

	fclose(fp);
}

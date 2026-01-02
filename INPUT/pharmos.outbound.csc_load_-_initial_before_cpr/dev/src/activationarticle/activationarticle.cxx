/********************************************************************************/
/*     Hauptmodul: activationarticle.ecc												*/
/*         Source: 																*/
/*          Autor: Ronald Imschweiler											*/
/*       Erstellt: 14.03.2003													*/
/*        Sprache: C															*/
/*        Erzeugt: manuell														*/
/*        Aufgabe: Abnullen der kummulierten Mengen in articlequota				*/
/*         Aufruf: activationarticle													*/
/*																				*/
/********************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "activationarticle"

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
#define MAX_TRANSAKTION		50
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
static	char*	spDatabase	= NULL;
static	int		iNumberOfDay	= 0;
static	long	kumcount		= 0;
static	int		commitcount		= MAX_TRANSAKTION;
static	short	branchno		= 0;
static	short	lockmode		= 4;

static	int		bVersion		= FALSE;

static	char	Filiale[4];

exec sql begin declare section;
char	str[2048];
exec sql end declare section;

/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
static int	KommandoZeileEinlesen( int argc, char** argv );
static int	oeffneDB();
static int	schliesseDB();
static int	PrepareActivate();
static int	PrepareActivate0();
static int	PrepareActivate1();
static int	PrepareActivate2();
static int	PrepareActivate3();
static int	Activate();
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
/*		sprintf(error_msg, "Aufruf: activationarticle.sh -branchno <BRANCHNO> -lockmode <MODE> [-commitcount <count>]\n"
			"lockmode 0: Freigeben aller gesperrten Artikel <\n"
			"lockmode 1: Sperren alle nicht apotheken-/rezeptpflichtige Artikel <\n"
			"lockmode 2: Sperren alle nicht rezeptpflichtige Artikel <\n"
			"lockmode 3: Sperren alle Artikel <\n"
		 	"Beispiel: > %s.sh -branchno 51 -lockmde 0 <\n"									
		 	"--> gibt alle gesperrten Artikel für Filiale 51 frei", argv[0] );	
		PrintMsg(fun, error_msg, HINWEIS);	*/
		return 1;
	}
	if(bVersion) return 0;

	sprintf(Filiale, "%d ", branchno);	//in diversen Prepares gebraucht

	sprintf( error_msg, "gestartet fuer DB: %s filiale %d mit Lockmode %d",spDatabase,branchno,lockmode );
	PrintMsg( fun, error_msg, HINWEIS );


	/*****************************************************/
	/* Datenbank oeffnen */
	/*****************************************************/
	if( !oeffneDB() == OK )
	{
		PrintMsg( fun, "Fehler beim Öffnen der Datenbank!", FEHLER );
		return 2;
	} 

	if (!PrepareActivate() == OK)
	{
		PrintMsg(fun, "Prepare activate Artikel", FEHLER);
		return 3;
	}
	
	/****************************************************/
	/* Aktivieren / Deaktivieren der Artikel			*/
	/****************************************************/

	if( !Activate() == OK )
	{
		printf("Fehler !");
		PrintMsg( fun,error_msg, FEHLER );
		return 30;
	} 
	sprintf( error_msg, "Anzahl geänderter Artikel : %d", kumcount );
	PrintMsg(fun, error_msg, FEHLER);

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
	int fehler = NO;
	int fehlerlockmode = NO;
	int dbin = NO;
	char *schalter;
	char *fun = "KommandoZeileEinlesen()";
			
	for( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		
		if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			spDatabase = argv[i];
			dbin = YES;
		}
		else if (!strcmp(schalter, "-branchno"))
		{
			i++;
			branchno = atoi(argv[i]);
		}
		else if (!strcmp(schalter, "-lockmode"))
		{
			i++;
			if (!strcmp(argv[i], "reactivate"))
			{
				lockmode = 0;
			}
			else if (!strcmp(argv[i], "nonrxnonotc"))
			{
				lockmode = 1;
			}
			else if (!strcmp(argv[i], "nonrx"))
			{
				lockmode = 2;
			}
			else if (!strcmp(argv[i], "all"))
			{
				lockmode = 3;
			}
			else
			{
				fehlerlockmode = ERROR;
				break;
			}
		}
		else if (!strcmp(schalter, "-commitcount"))
		{
			i++;
			commitcount = atoi(argv[i]);
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			bVersion = TRUE;
			return 0;
		}
		else
		{
			fehler = ERROR;
			break;
		}
	} /* ENDR FOR */                                            

	if( argc == 1 || fehler == ERROR || branchno == 0 || branchno > 99 || fehlerlockmode == ERROR || dbin == NO)
	{
		char fehltext[81];
		if (argc == 1)
		{
			PrintMsg(fun, "Keine Programmparameter", HINWEIS);
			return ERROR; /* Fehlerhafte KommandoZeile */
		}
		else if (branchno == 0 || branchno > 99)
		{
			sprintf(fehltext, "ungueltige Filialnr: %d", branchno);
			PrintMsg(fun, fehltext, HINWEIS);
			return ERROR; /* Fehlerhafte KommandoZeile */
		}
		else if (fehlerlockmode == ERROR)
		{
			PrintMsg(fun, "falscher lokmode (reactivate,nonrxnonotc,nonrx,all)", HINWEIS);
			return ERROR; /* Fehlerhafte KommandoZeile */
		}
		else
		{
			PrintMsg(fun, "fehlende DB", HINWEIS);
			return ERROR; /* Fehlerhafte KommandoZeile */
		}
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
/* static int PrepareActivate()														*/
/****************************************************************************/
static int PrepareActivate()
{
	char*	fun = "PrepareActivate()";

	if (lockmode == 0)
	{
		if (!PrepareActivate0() == OK)
			return ERROR;
	}
	else if (lockmode == 1)
	{
		if (!PrepareActivate1() == OK)
			return ERROR;
	}
	else if (lockmode == 2)
	{
		if (!PrepareActivate2() == OK)
			return ERROR;
	}
	else
	{
		if (!PrepareActivate3() == OK)
			return ERROR;
	}
	return OK;
}

/****************************************************/
/* Prepare für Freigeben Artikel					*/
/****************************************************/
static int PrepareActivate0()
{
	char*	fun = "PrepareActivate0()";

	/* SELECT-Cursor vorbereiten */
	strcpy(str, "SELECT artikelaktiv ");
	strcat(str, "FROM artikellokal ");
	strcat(str, "where filialnr = ");
	strcat(str, Filiale);
	strcat(str, "and artikelaktiv >= '5' ");
	strcat(str, "FOR UPDATE");
	EXEC SQL PREPARE preSelActivate0 from :str;
	EXEC SQL DECLARE curSelActivate0 cursor with hold for preSelActivate0;
	ERROR_MSG("DECLARE curSelActivate0");
	exec sql free preSelActivate0;

	/* UPDATE-Cursor vorbereiten */
	strcpy(str, "update artikellokal set artikelaktiv = artikelaktiv - 5 WHERE CURRENT OF curSelActivate0");
	EXEC SQL PREPARE preUpdActivate0 from :str;

	return OK;
}

/****************************************************************************/
/* Prepare für Sperren Artikel Freiverkauf (weder apo- noch rezeptpflichtig	*/
/****************************************************************************/
static int PrepareActivate1()
{
	char*	fun = "PrepareActivate1()";

	EXEC SQL create temp table t_artikelzentral(ARTIKEL_NR INTEGER);
	ERROR_MSG("create temp table t_artikelzentral");
	EXEC SQL insert into t_artikelzentral select artikel_nr from artikelzentral where bitand(etartklasse1, 4096) = 0 and bitand(etartklasse1, 2048) = 0;
	ERROR_MSG("insert into t_artikelzentral");
	EXEC SQL create index t_artikelzentral_1 on t_artikelzentral(ARTIKEL_NR);
	ERROR_MSG("create index t_artikelzentral_1");

	/* SELECT-Cursor vorbereiten */
	strcpy(str, "SELECT l.artikelaktiv ");
	strcat(str, "FROM artikellokal l ");
	strcat(str, "where l.filialnr = ");
	strcat(str, Filiale);
	strcat(str, "and l.artikelaktiv = '1' ");
	strcat(str, "and l.artikel_nr in(select z.artikel_nr from t_artikelzentral z)");
	strcat(str, "FOR UPDATE");
	EXEC SQL PREPARE preSelActivate1 from :str;
	EXEC SQL DECLARE curSelActivate1 cursor with hold for preSelActivate1;
	ERROR_MSG("DECLARE curSelActivate1");
	exec sql free preSelActivate1;

	/* UPDATE-Cursor vorbereiten */
	strcpy(str, "update artikellokal set artikelaktiv = artikelaktiv + 5 WHERE CURRENT OF curSelActivate1");
	EXEC SQL PREPARE preUpdActivate1 from :str;

	return OK;
}

/****************************************************************************/
/* Prepare für Sperren nonRX Artikel (nicht rezeptpflichtig)				*/
/****************************************************************************/
static int PrepareActivate2()
{
	char*	fun = "PrepareActivate2()";

	EXEC SQL create temp table t_artikelzentral(ARTIKEL_NR INTEGER);
	ERROR_MSG("create temp table t_artikelzentral");
	EXEC SQL insert into t_artikelzentral select artikel_nr from artikelzentral where bitand(etartklasse1, 4096) = 0;
	ERROR_MSG("insert into t_artikelzentral");
	EXEC SQL create index t_artikelzentral_1 on t_artikelzentral(ARTIKEL_NR);
	ERROR_MSG("create index t_artikelzentral_1");

	/* SELECT-Cursor vorbereiten */
	strcpy(str, "SELECT l.artikelaktiv ");
	strcat(str, "FROM artikellokal l ");
	strcat(str, "where l.filialnr = ");
	strcat(str, Filiale);
	strcat(str, "and l.artikelaktiv = '1' ");
	strcat(str, "and l.artikel_nr in(select z.artikel_nr from t_artikelzentral z)");
	strcat(str, "FOR UPDATE");
	EXEC SQL PREPARE preSelActivate2 from :str;
	EXEC SQL DECLARE curSelActivate2 cursor with hold for preSelActivate2;
	ERROR_MSG("DECLARE curSelActivate2");
	exec sql free preSelActivate2;

	/* UPDATE-Cursor vorbereiten */
	strcpy(str, "update artikellokal set artikelaktiv = artikelaktiv + 5 WHERE CURRENT OF curSelActivate2");
	EXEC SQL PREPARE preUpdActivate2 from :str;

	return OK;
}

/****************************************************************************/
/* Prepare für Sperren alle Artikel											*/
/****************************************************************************/
static int PrepareActivate3()
{
	char*	fun = "PrepareActivate3()";

	/* SELECT-Cursor vorbereiten */
	strcpy(str, "SELECT l.artikelaktiv ");
	strcat(str, "FROM artikellokal l ");
	strcat(str, "where l.filialnr = ");
	strcat(str, Filiale);
	strcat(str, "and l.artikelaktiv = '1' ");
	strcat(str, "FOR UPDATE");
	EXEC SQL PREPARE preSelActivate3 from :str;
	EXEC SQL DECLARE curSelActivate3 cursor with hold for preSelActivate3;
	ERROR_MSG("DECLARE curSelActivate3");
	exec sql free preSelActivate3;

	/* UPDATE-Cursor vorbereiten */
	strcpy(str, "update artikellokal set artikelaktiv = artikelaktiv + 5 WHERE CURRENT OF curSelActivate3");
	EXEC SQL PREPARE preUpdActivate3 from :str;

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
			"activationarticle",
			fun,
			error_msg, 
			SQLCODE,
			SQLISAM );

	fclose(fp);
}

/****************************************************************************/
/* int Activate()															*/
/****************************************************************************/
int Activate()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "Activate()";
	unsigned int iTransactions = 0;

	exec sql begin declare section;
		char	cartikelaktiv[1];
	exec sql end declare section;

	if (lockmode == 0)
	{
		/* SELECT ausfuehren */
		EXEC SQL OPEN curSelActivate0;
		ERROR_MSG("OPEN curSelActivate0");

		EXEC SQL BEGIN WORK;
		ERROR_MSG("BEGIN WORK1");
		for (;;)
		{
			iTransactions++;
			/* Max. Transaktionen sind erreicht --> Commit setzen */
			if ((iTransactions % commitcount) == 0)
			{
				EXEC SQL COMMIT WORK;
				ERROR_MSG("COMMIT WORK1");
				EXEC SQL BEGIN WORK;
				ERROR_MSG("BEGIN WORK2");
			}

			EXEC SQL FETCH curSelActivate0 into :cartikelaktiv;
			ERROR_MSG("EXEC SQL FETCH curSelActivate0!");

			/* Keine weiteren Datensaetze im Cursor */
			if (SQLCODE == SQLNOTFOUND)
			{
				break;
			}

			EXEC SQL EXECUTE preUpdActivate0;
			ERROR_MSG("EXEC SQL EXECUTE preUpdActivate0!");
			kumcount++;
		}

		EXEC SQL COMMIT WORK;
		ERROR_MSG("COMMIT WORK2");
		EXEC SQL CLOSE curSelActivate0;
		ERROR_MSG("EXEC SQL CLOSE curSelActivate0!");
	}

	else if (lockmode == 1)
	{
		/* SELECT ausfuehren */
		EXEC SQL OPEN curSelActivate1;
		ERROR_MSG("OPEN curSelActivate1");

		EXEC SQL BEGIN WORK;
		ERROR_MSG("BEGIN WORK1");
		for (;;)
		{
			iTransactions++;
			/* Max. Transaktionen sind erreicht --> Commit setzen */
			if ((iTransactions % commitcount) == 0)
			{
				EXEC SQL COMMIT WORK;
				ERROR_MSG("COMMIT WORK1");
				EXEC SQL BEGIN WORK;
				ERROR_MSG("BEGIN WORK2");
			}

			EXEC SQL FETCH curSelActivate1 into :cartikelaktiv;
			ERROR_MSG("EXEC SQL FETCH curSelActivate1!");

			/* Keine weiteren Datensaetze im Cursor */
			if (SQLCODE == SQLNOTFOUND)
			{
				break;
			}

			EXEC SQL EXECUTE preUpdActivate1;
			ERROR_MSG("EXEC SQL EXECUTE preUpdActivate1!");
			kumcount++;
		}

		EXEC SQL COMMIT WORK;
		ERROR_MSG("COMMIT WORK2");
		EXEC SQL CLOSE curSelActivate1;
		ERROR_MSG("EXEC SQL CLOSE curSelActivate1!");
	}

	else if (lockmode == 2)
	{
		/* SELECT ausfuehren */
		EXEC SQL OPEN curSelActivate2;
		ERROR_MSG("OPEN curSelActivate2");

		EXEC SQL BEGIN WORK;
		ERROR_MSG("BEGIN WORK1");
		for (;;)
		{
			iTransactions++;
			/* Max. Transaktionen sind erreicht --> Commit setzen */
			if ((iTransactions % commitcount) == 0)
			{
				EXEC SQL COMMIT WORK;
				ERROR_MSG("COMMIT WORK1");
				EXEC SQL BEGIN WORK;
				ERROR_MSG("BEGIN WORK2");
			}

			EXEC SQL FETCH curSelActivate2 into :cartikelaktiv;
			ERROR_MSG("EXEC SQL FETCH curSelActivate2!");

			/* Keine weiteren Datensaetze im Cursor */
			if (SQLCODE == SQLNOTFOUND)
			{
				break;
			}

			EXEC SQL EXECUTE preUpdActivate2;
			ERROR_MSG("EXEC SQL EXECUTE preUpdActivate2!");
			kumcount++;
		}

		EXEC SQL COMMIT WORK;
		ERROR_MSG("COMMIT WORK2");
		EXEC SQL CLOSE curSelActivate2;
		ERROR_MSG("EXEC SQL CLOSE curSelActivate2!");
	}

	else if (lockmode == 3)
	{
		/* SELECT ausfuehren */
		EXEC SQL OPEN curSelActivate3;
		ERROR_MSG("OPEN curSelActivate3");

		EXEC SQL BEGIN WORK;
		ERROR_MSG("BEGIN WORK1");
		for (;;)
		{
			iTransactions++;
			/* Max. Transaktionen sind erreicht --> Commit setzen */
			if ((iTransactions % commitcount) == 0)
			{
				EXEC SQL COMMIT WORK;
				ERROR_MSG("COMMIT WORK1");
				EXEC SQL BEGIN WORK;
				ERROR_MSG("BEGIN WORK2");
			}

			EXEC SQL FETCH curSelActivate3 into :cartikelaktiv;
			ERROR_MSG("EXEC SQL FETCH curSelActivate3!");

			/* Keine weiteren Datensaetze im Cursor */
			if (SQLCODE == SQLNOTFOUND)
			{
				break;
			}

			EXEC SQL EXECUTE preUpdActivate3;
			ERROR_MSG("EXEC SQL EXECUTE preUpdActivate3!");
			kumcount++;
		}

		EXEC SQL COMMIT WORK;
		ERROR_MSG("COMMIT WORK2");
		EXEC SQL CLOSE curSelActivate3;
		ERROR_MSG("EXEC SQL CLOSE curSelActivate3!");
	}

	return OK;
}

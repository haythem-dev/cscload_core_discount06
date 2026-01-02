/********************************************************************************/
/*     Hauptmodul: loademergencyrouting.ecc												*/
/*         Source: 																*/
/*          Autor: Ronald Imschweiler											*/
/*       Erstellt: 24.04.2020													*/
/*        Sprache: C															*/
/*        Erzeugt: manuell														*/
/*        Aufgabe: Eintragen Routing für Kunden einer Filiale im Notfall		*/
/*         Aufruf: loademergencyrouting											*/
/*																				*/
/********************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loademergencyrouting"

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
static	char*		spDatabase		= NULL;
static	long		savecount		= 0;
static	long		delcount		= 0;
static	long		inscount		= 0;
static	int			commitcount		= MAX_TRANSAKTION;
static	char		kzabc[10];
static	int			bActivate		= FALSE;
static	int			bVersion		= FALSE;
static	int			debug_enabled	= NO;
char	error_msg[512];

static	char		Wochentag[2];

exec sql begin declare section;
char	str[2048];
char	stringabc[30];
int		weekday = -1;
short	branchno = 0;
char	cWD[4];
char	Filiale[4];
char	SaveFiliale[4];
int		iKunde;
long	CUSTOMERNO;
short	BRANCHNO;
long	TIMEFROM;
long	TIMETO;
short	DESTBRANCHNO;
char	DAYOFWEEK[3];
short	WEEKDAY;
exec sql end declare section;

/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
static int	KommandoZeileEinlesen( int argc, char** argv );
static int	oeffneDB();
static int	schliesseDB();
static int	PrepareRouting();
static int	WriteRouting();
static int	SaveRouting();
static int	DeleteEmergencyRouting();
static int	RestoreRouting();
static int	CheckActivated();
static void PrintMsg(char *fun, char *error_msg, char mld );


/********************************************************************************/
/* int main( int argc, char **argv ) */
/********************************************************************************/
int main( int argc, char* argv[] )
{
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

	sprintf(Wochentag, "%d", weekday);	//in diversen Prepares gebraucht

	if (bActivate == YES)
	{
		sprintf(error_msg, "gestartet zum Aktivieren Notfall Routing fuer DB: %s Filiale %d mit kzabc %s, WD %s ", spDatabase, branchno, kzabc, cWD);
	}
	else
	{
		sprintf(error_msg, "gestartet zum Deaktivieren Notfall Routing fuer DB: %s Filiale %d mit kzabc %s, WD %s ", spDatabase, branchno, kzabc, cWD);
	}
	PrintMsg( fun, error_msg, HINWEIS );


	/*****************************************************/
	/* Datenbank oeffnen */
	/*****************************************************/
	if( !oeffneDB() == OK )
	{
		PrintMsg( fun, "Fehler beim Öffnen der Datenbank!", FEHLER );
		return 2;
	}

	sprintf(Filiale, "%d ", branchno);	//in diversen Prepares gebraucht
	sprintf(SaveFiliale, "%d ", branchno + 100);	//in diversen Prepares gebraucht

	if (bActivate != YES)
	{
		strcpy(kzabc, "%");	//bei Reaktivieren alle gesicherten Einträge
		if(CheckActivated() != OK)
		{
			printf(" \n!!!!!!!     NOTFALLROUTING NICHT AKTIV, KEINE REAKTIVIERUNG NOETIG\n "); fflush(stdout);
			PrintMsg(fun, "nicht aktiv, keine Reaktivierung noetig", FEHLER);
			return OK;
		}
		else
		{
			if (CUSTOMERNO == 0)	//Dummy-Satz loeschen
			{
				EXEC SQL BEGIN WORK;
				ERROR_MSG("BEGIN WORK1");
				exec sql delete from customerrouting
				where customerno = :CUSTOMERNO
				and branchno = :BRANCHNO
				and weekday = :WEEKDAY;
				ERROR_MSG("Delete Dummy-Satz");
				EXEC SQL COMMIT WORK;
				ERROR_MSG("COMMIT WORK");
			}
		}
	}
	else
	{
		if (CheckActivated() == OK)
		{
			printf(" \n!!!!!!!     NOTFALLROUTING BEREITS AKTIV! VOR ERNEUTER AKTIVIERUNG ZUERST DEAKTIVIEREN\n "); fflush(stdout);
			PrintMsg(fun, "Notfallrouting bereits aktiv", FEHLER);
			return ERROR;
		}
	}

	if (!PrepareRouting() == OK)
	{
		PrintMsg(fun, "Prepare Notfall Routing", FEHLER);
		return 3;
	}
	
	/****************************************************/
	/* Aktivieren / Deaktivieren der Artikel			*/
	/****************************************************/

	if( !WriteRouting() == OK )
	{
		printf("Fehler !");
		PrintMsg( fun,error_msg, FEHLER );
		return 30;
	} 

	if (bActivate == YES)
	{
		sprintf(error_msg, "Anzahl gesicherte Routingeintraege: %d / vorhandene geloescht %d / eingefuegt fuer Notfall Routing: %d", savecount, delcount, inscount);
	}
	else
	{
		sprintf(error_msg, "Anzahl gesicherte Routingeintraege reaktiviert: %d / geloescht fuer Notfall Routing: %d", savecount, inscount);
	}
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
	int i;
	int fehler = NO;
	int fehlerlockmode = NO;
	int dbin = NO;
	char *schalter;
	char *fun = "KommandoZeileEinlesen()";

	kzabc[0] = '\0';
			
	for( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		
		if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			spDatabase = argv[i];
			dbin = YES;
		}
		else if (!strcmp(schalter, "-dg"))
		{
			debug_enabled = YES;
		}
		else if (!strcmp(schalter, "-branchno"))
		{
			i++;
			branchno = atoi(argv[i]);
		}
		else if (!strcmp(schalter, "-kzabc"))
		{
			i++;
			strcpy(kzabc, argv[i]);
		}
		else if (!strcmp(schalter, "-commitcount"))
		{
			i++;
			commitcount = atoi(argv[i]);
		}
		else if (!strcmp(schalter, "-activate"))
		{
			i++;
			if (!strcmp(argv[i], "YES")) bActivate = TRUE;
			else bActivate = FALSE;
		}
		else if (!strcmp(schalter, "-wd"))
		{
			i++;
			strcpy(cWD, argv[i]);
			if (!strcmp(argv[i], "MO") || !strcmp(argv[i], "Mon") || !strcmp(argv[i], "1"))			weekday = 1;
			else if (!strcmp(argv[i], "DI") || !strcmp(argv[i], "Tue") || !strcmp(argv[i], "2"))	weekday = 2;
			else if (!strcmp(argv[i], "MI") || !strcmp(argv[i], "Wed") || !strcmp(argv[i], "3"))	weekday = 3;
			else if (!strcmp(argv[i], "DO") || !strcmp(argv[i], "Thu") || !strcmp(argv[i], "4"))	weekday = 4;
			else if (!strcmp(argv[i], "FR") || !strcmp(argv[i], "Fri") || !strcmp(argv[i], "5"))	weekday = 5;
			else if (!strcmp(argv[i], "SA") || !strcmp(argv[i], "Sat") || !strcmp(argv[i], "6"))	weekday = 6;
			else if (!strcmp(argv[i], "SO") || !strcmp(argv[i], "Sun") || !strcmp(argv[i], "0"))	weekday = 0;
			else
			{
				fehler = ERROR;
				break;
			}
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

	if( argc == 1 || fehler == ERROR || branchno == 0 || branchno > 99 || weekday == -1 || kzabc[0] == '\0' || dbin == NO)
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
			PrintMsg(fun, "falsches kzabc", HINWEIS);
			return ERROR; /* Fehlerhafte KommandoZeile */
		}
		else if (weekday == -1)
		{
			PrintMsg(fun, "fehlender Wochentag", HINWEIS);
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
/* static int PrepareRouting()														*/
/****************************************************************************/
static int PrepareRouting()
{
	char*	fun = "PrepareRouting()";

	/* SELECT-Cursor vorbereiten */
	strcpy(str, "SELECT k.kundennr ");
	strcat(str, "FROM kunde k ");
	strcat(str, "inner join kundeschalter s ");
	strcat(str, "on s.vertriebszentrumnr = k.vertriebszentrumnr and s.kundennr = k.kundennr ");
	strcat(str, "where k.vertriebszentrumnr = ");
	strcat(str, Filiale);
	strcat(str, "and s.skdkundeaegesperrt = '0' ");
	strcat(str, "and k.kdgruppe in ('01','02','04') ");
	for (int i = 0;; i++)
	{
		if (kzabc[i] == '\0')
		{
			strcat(str, ") ");
			break;
		}
		if (i == 0)
		{
			sprintf(stringabc, "and (kzkdklasse like '%c%%' ", kzabc[i]);
			strcat(str, stringabc);
		}
		else
		{
			sprintf(stringabc, "or kzkdklasse like '%c%%' ", kzabc[i]);
			strcat(str, stringabc);
		}
	}
	EXEC SQL PREPARE preSelKunde from :str;
	EXEC SQL DECLARE curSelKunde cursor with hold for preSelKunde;
	ERROR_MSG("DECLARE curSelKunde");
	exec sql free preSelKunde;

	/* SAVE vorbereiten */
	strcpy(str, "select ");
	strcat(str, "customerno,branchno,timefrom,timeto,destbranchno,dayofweek,weekday ");
	strcat(str, "from customerrouting ");
	strcat(str, "where branchno = ");
	strcat(str, Filiale);
	strcat(str, "and weekday = ");
	strcat(str, Wochentag);
	EXEC SQL PREPARE preSelSaveRoutingAll from :str;
	EXEC SQL DECLARE curSelSaveRoutingAll cursor with hold for preSelSaveRoutingAll;
	ERROR_MSG("DECLARE curSelSaveRoutingAll");
	exec sql free preSelSaveRoutingAll;

	strcpy(str, "select ");
	strcat(str, "customerno,branchno,timefrom,timeto,destbranchno,dayofweek,weekday ");
	strcat(str, "from customerrouting ");
	strcat(str, "where branchno = ");
	strcat(str, Filiale);
	strcat(str, "and customerno = ? ");
	strcat(str, "and weekday = ");
	strcat(str, Wochentag);
	EXEC SQL PREPARE SelSaveRouting from : str;

	strcpy(str, "delete ");
	strcat(str, "from customerrouting ");
	strcat(str, "where branchno = ");
	strcat(str, Filiale);
	strcat(str, "and customerno = ? ");
	strcat(str, "and weekday = ");
	strcat(str, Wochentag);
	EXEC SQL PREPARE DelSaveRouting from :str;

	/* UNSAVE vorbereiten */
	strcpy(str, "select ");
	strcat(str, "customerno,branchno,timefrom,timeto,destbranchno,dayofweek,weekday ");
	strcat(str, "from customerrouting ");
	strcat(str, "where branchno = ");
	strcat(str, SaveFiliale);
//	strcat(str, " and customerno = ? ");
	strcat(str, " and weekday = ");
	strcat(str, Wochentag);
	strcat(str, " for update ");
	EXEC SQL PREPARE preSelUnsaveRouting from :str;
	EXEC SQL DECLARE curSelUnsaveRouting cursor with hold for preSelUnsaveRouting;
	ERROR_MSG("DECLARE curSelUnsaveRouting");
	exec sql free preSelUnsaveRouting;

	strcpy(str, "delete ");
	strcat(str, "from customerrouting ");
	strcat(str, "where current of curSelUnsaveRouting");
//	strcat(str, SaveFiliale);
//	strcat(str, "and customerno = ? ");
//	strcat(str, "and weekday = ");
//	strcat(str, Wochentag);
	EXEC SQL PREPARE DelUnsaveRouting from :str;
	ERROR_MSG("prepare DelUnsaveRouting")

	/* INSERT vorbereiten */
	strcpy(str, "insert into customerrouting ");
	strcat(str, "(customerno,branchno,timefrom,timeto,destbranchno,dayofweek,weekday) ");
	strcat(str, "values ");
	strcat(str, "(?, ?, ?, ?, ?, ?, ? ) ");
	EXEC SQL PREPARE InsertRouting from :str;
	ERROR_MSG("prepare InsertRouting")

	/* DELETE vorbereiten */
	strcpy(str, "delete from customerrouting ");
	strcat(str, "where branchno = ");
	strcat(str, Filiale);
	strcat(str, "and customerno = ? ");
	strcat(str, "and weekday = ");
	strcat(str, Wochentag);
	exec sql prepare DeleteRouting from :str;
	ERROR_MSG("prepare DeleteRouting")

	strcpy(str, "select ");
	strcat(str, "customerno,branchno,timefrom,timeto,destbranchno,dayofweek,weekday ");
	strcat(str, "from customerrouting ");
	strcat(str, "where branchno = ");
	strcat(str, Filiale);
	strcat(str, " and weekday = ");
	strcat(str, Wochentag);
	strcat(str, " for update ");
	EXEC SQL PREPARE preDelEmergencyRouting from : str;
	EXEC SQL DECLARE curDelEmergencyRouting cursor with hold for preDelEmergencyRouting;
	ERROR_MSG("DECLARE curDelEmergencyRouting");
	exec sql free preDelEmergencyRouting;

	strcpy(str, "delete ");
	strcat(str, "from customerrouting ");
	strcat(str, "where current of curDelEmergencyRouting");
	EXEC SQL PREPARE DelEmergencyRouting from : str;
	ERROR_MSG("prepare DelEmergencyRouting")

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
/* int WriteRouting()														*/
/****************************************************************************/
static int WriteRouting()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "WriteRouting()";
	unsigned int iTransactions = 0;

	if (bActivate == YES)
	{
		if (!SaveRouting() == OK) return ERROR;

		/* SELECT ausfuehren */
		EXEC SQL OPEN curSelKunde;
		ERROR_MSG("OPEN curSelKunde");

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

			EXEC SQL FETCH curSelKunde into : iKunde;
			ERROR_MSG("EXEC SQL FETCH curSelKunde!");

			/* Keine weiteren Datensaetze im Cursor */
			if (SQLCODE == SQLNOTFOUND)
			{
				break;
			}


			if (bActivate == YES)
			{
				EXEC SQL EXECUTE SelSaveRouting
					into :CUSTOMERNO,
					:BRANCHNO,
					:TIMEFROM,
					:TIMETO,
					:DESTBRANCHNO,
					:DAYOFWEEK,
					:WEEKDAY
					using :iKunde;
				ERROR_MSG("EXEC SQL EXECUTE SelSaveRouting!");
				if (SQLCODE != SQLNOTFOUND)
				{
					EXEC SQL EXECUTE DelSaveRouting using :iKunde;
					ERROR_MSG("EXEC SQL EXECUTE DelSaveRouting!");

					delcount++;
				}

				EXEC SQL EXECUTE InsertRouting using :iKunde, : branchno, '0', '2359', '61', : cWD, : weekday;
				ERROR_MSG("EXEC SQL EXECUTE InsertRouting!");
				inscount++;
			}
		}
		EXEC SQL COMMIT WORK;
		ERROR_MSG("COMMIT WORK2");
		EXEC SQL CLOSE curSelKunde;
		ERROR_MSG("EXEC SQL CLOSE curSelKunde!");
		return OK;
	}
	else
	{
		if (!DeleteEmergencyRouting() == OK) return ERROR;
		if (!RestoreRouting() == OK) return ERROR;
	}

	return OK;
}

static int SaveRouting()
{
	char*	fun = "SaveRouting()";
	unsigned int iTransactions = 0;

	EXEC SQL OPEN curSelSaveRoutingAll;
	ERROR_MSG("OPEN curSelSaveRoutingAll");

	EXEC SQL BEGIN WORK;
	ERROR_MSG("BEGIN WORK");
	for(;;)
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

		EXEC SQL FETCH curSelSaveRoutingAll
			into :CUSTOMERNO,
				:BRANCHNO,
				:TIMEFROM,
				:TIMETO,
				:DESTBRANCHNO,
				:DAYOFWEEK,
				:WEEKDAY;

		ERROR_MSG("EXEC SQL FETCH SelSaveRoutingAll!");
		if (SQLCODE == SQLNOTFOUND) break;

		BRANCHNO += 100;
		EXEC SQL EXECUTE InsertRouting using
			:CUSTOMERNO,
			:BRANCHNO,
			:TIMEFROM,
			:TIMETO,
			:DESTBRANCHNO,
			:DAYOFWEEK,
			:WEEKDAY;
		ERROR_MSG("EXEC SQL EXECUTE InsertRouting Save!");
		if (debug_enabled == YES)
		{
			sprintf(error_msg, "Daten: %d/%d/%d/%d/%d/%s/%d",
				CUSTOMERNO,
				BRANCHNO,
				TIMEFROM,
				TIMETO,
				DESTBRANCHNO,
				DAYOFWEEK,
				WEEKDAY);
			PrintMsg(fun, error_msg, HINWEIS);
		}

		savecount++;
	}
	if (savecount == 0)	//wenn keine Einträge vorhanden ware Dummy-Satz eintragen, um Löschen des Notfallroutings sicher zu stellen 
	{
		EXEC SQL EXECUTE InsertRouting using
			'0',
			:SaveFiliale,
			'0',
			'2359',
			'0',
			:cWD,
			:weekday;
		ERROR_MSG("EXEC SQL EXECUTE InsertRouting Dummy!");
	}
	EXEC SQL COMMIT WORK;
	ERROR_MSG("COMMIT WORK3");

	return OK;
}

static int RestoreRouting()
{
	char*	fun = "RestoreRouting()";
	unsigned int iTransactions = 0;

	EXEC SQL OPEN curSelUnsaveRouting;
	ERROR_MSG("OPEN curSelUnsaveRouting");

	EXEC SQL BEGIN WORK;
	ERROR_MSG("BEGIN WORK");

	for(;;)
	{
		iTransactions++;
		/* Max. Transaktionen sind erreicht --> Commit setzen */
		if ((iTransactions % commitcount) == 0)
		{
			EXEC SQL COMMIT WORK;
			ERROR_MSG("COMMIT WORK");
			EXEC SQL BEGIN WORK;
			ERROR_MSG("BEGIN WORK1");
		}

		EXEC SQL FETCH curSelUnsaveRouting
			into :CUSTOMERNO,
			:BRANCHNO,
			:TIMEFROM,
			:TIMETO,
			:DESTBRANCHNO,
			:DAYOFWEEK,
			:WEEKDAY;
		ERROR_MSG("EXEC SQL FETCH curSelUnsaveRouting!");

		if (SQLCODE == SQLNOTFOUND)
		{
			break;
		}
		if (CUSTOMERNO != 0)
		{
			BRANCHNO -= 100;
			EXEC SQL EXECUTE InsertRouting using
				:CUSTOMERNO,
				:BRANCHNO,
				:TIMEFROM,
				:TIMETO,
				:DESTBRANCHNO,
				:DAYOFWEEK,
				:WEEKDAY;
			if (debug_enabled == YES)
			{
				sprintf(error_msg, "Daten: %d/%d/%d/%d/%d/%s/%d",
					CUSTOMERNO,
					BRANCHNO,
					TIMEFROM,
					TIMETO,
					DESTBRANCHNO,
					DAYOFWEEK,
					WEEKDAY);
				PrintMsg(fun, error_msg, HINWEIS);
			}
			if (SQLCODE == -239)	//macht nichts
			{
			}
			else
			{
				ERROR_MSG("EXEC SQL EXECUTE InsertRouting UnSave!");
			}
		}
		EXEC SQL EXECUTE DelUnsaveRouting;
		ERROR_MSG("EXEC SQL EXECUTE DelUnsaveRouting!");
		savecount++;
	}
	EXEC SQL COMMIT WORK;
	ERROR_MSG("COMMIT WORK1");
	return OK;
}


static int DeleteEmergencyRouting()
{
	char*	fun = "DeleteEmergencyRouting()";
	unsigned int iTransactions = 0;

	EXEC SQL OPEN curDelEmergencyRouting;
	ERROR_MSG("OPEN curDelEmergencyRouting");

	EXEC SQL BEGIN WORK;
	ERROR_MSG("BEGIN WORK");

	for (;;)
	{
		iTransactions++;
		/* Max. Transaktionen sind erreicht --> Commit setzen */
		if ((iTransactions % commitcount) == 0)
		{
			EXEC SQL COMMIT WORK;
			ERROR_MSG("COMMIT WORK");
			EXEC SQL BEGIN WORK;
			ERROR_MSG("BEGIN WORK1");
		}

		EXEC SQL FETCH curDelEmergencyRouting
			into :CUSTOMERNO,
			:BRANCHNO,
			:TIMEFROM,
			:TIMETO,
			:DESTBRANCHNO,
			:DAYOFWEEK,
			:WEEKDAY;
		ERROR_MSG("EXEC SQL FETCH curDelEmergencyRouting!");

		if (SQLCODE == SQLNOTFOUND)
		{
			break;
		}
		EXEC SQL EXECUTE DelEmergencyRouting;
		ERROR_MSG("EXEC SQL EXECUTE DelEmergencyRouting!");
		delcount++;
	}
	EXEC SQL COMMIT WORK;
	ERROR_MSG("COMMIT WORK1");
	return OK;
}

static int	CheckActivated()
{
	exec sql select first 1 customerno, branchno, timefrom, timeto, destbranchno, dayofweek, weekday
		into :CUSTOMERNO,
		:BRANCHNO,
		:TIMEFROM,
		:TIMETO,
		:DESTBRANCHNO,
		:DAYOFWEEK,
		:WEEKDAY
		from customerrouting
	where branchno = :SaveFiliale
	and WEEKDAY = :weekday
	order by customerno;
	if (SQLCODE == SQLNOTFOUND)
	{
		return ERROR;
	}
	return OK;
}

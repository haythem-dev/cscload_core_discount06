/********************************************************************************************/
/*     Hauptmodul: tplddb.ecc																*/
/*         Source: 																			*/
/*          Autor: Bischof Björn															*/
/*       Erstellt: 07.03.2003																*/
/*        Sprache: C																		*/
/*        Erzeugt: manuell																	*/
/*        Aufgabe:																			*/
/*         Aufruf: tplddb	-inputdb phosix@db1_rmfuze2_shm									*/
/*							-outputdb phosix@db3_rmfuze2_shm								*/ 
/*							-commitfrequenz  nnn											*/
/*							-tabellen filiale												*/
/*																							*/
/*																							*/
/********************************************************************************************/

/*******************************************************************************************/
/* VERSION */
/*******************************************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tplddb"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/*******************************************************************************************/
/* INCLUDE */
/*******************************************************************************************/
#include "libtpld/define.h"
#include <stdlib.h> 
#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

EXEC SQL include locator;
EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*******************************************************************************************/
/* MACROS */
/*******************************************************************************************/
#define ERROR_MSG( x )      if( SQLCODE < 0 ){				\
								PrintMsg( fun, x, FEHLER ); \
								return ERROR;				\
							}

/*******************************************************************************************/
/* DEFINE */
/*******************************************************************************************/
#define MAX_TRANSAKTION     300
#define SIZE_ARRAY_ELEMENT	50


/*******************************************************************************************/
/* TYPEDEF */
/*******************************************************************************************/
typedef struct timeval timeval_t; 
typedef char MyStringBuffer[SIZE_ARRAY_ELEMENT];


/*******************************************************************************************/
/* STRUKTUREN */
/*******************************************************************************************/
struct T_Zaehler {
	unsigned int uiZumLoeschenSelektiert;
	unsigned int uiGeloescht;
	unsigned int uiZumEinfuegenSelektiert;
	unsigned int uiNeuEingefuegt;
}; 

/*******************************************************************************************/
/* MODUL-GLOBALE VARIABLEN */
/*******************************************************************************************/
static char*			m_spTabelle			= NULL;
static char*			m_spInputDB			= NULL;
static char*			m_spOutputDB		= NULL;
static unsigned int		m_uiCommitFrequenz	= MAX_TRANSAKTION;
static unsigned int		m_uiTransactions	= 0;
static MyStringBuffer*	m_sparMyArray		= NULL;	
static int				m_iSize				= 0;

static int    			bVersion	 	= FALSE;



/**************************************************************************************************************************/
/* VORWAERTS-DECLARATION */
/**************************************************************************************************************************/
static int	KommandoZeileEinlesen( int argc, char** argv );
static int	oeffneDB();
#ifdef FALSCH
static int	loescheZielTabelle( const char* );
static int	insertQuellInZielTabelle( const char* );
#else
static int      loescheZielTabelle(  MyStringBuffer* );
static int      insertQuellInZielTabelle(  MyStringBuffer* );
#endif
static int	schliesseDB();
static void PrintMsg(char *fun, char *error_msg, char mld );
static void freeStringBuffer( MyStringBuffer** sparMyArray );
static void addToStrArray( MyStringBuffer** sparMyArray, int* piSize, const char* spStringToBuffer );
static struct T_Zaehler stZaehler = {0, 0, 0, 0};


/**************************************************************************************************************************/
/* int main( int argc, char **argv ) */
/**************************************************************************************************************************/
int main( int argc, char* argv[] )
{
	char error_msg[512];
	char *fun					= "TpLdDB::main()";
	MyStringBuffer* sparHelp	= 0;
	int i						= 0;

	setbuf(stdout, 0);	

	/*****************************************************/
	/* Aufrufparameter werden ausgelesen */
	/*****************************************************/
	if( KommandoZeileEinlesen(argc, argv) == ERROR ){
		return 2;
	}
	if(bVersion) return 0;

    
	sprintf( error_msg, "Begin: InputDB <%s>, OutputDB <%s> und Tabelle <%s>", m_spInputDB, m_spOutputDB, m_spTabelle );
	PrintMsg( fun, error_msg, HINWEIS );


	/*****************************************************/
	/* Datenbank oeffnen */
	/*****************************************************/
	if( oeffneDB() == ERROR /* = -1 */ ){
		return 2;
	}

	sparHelp = m_sparMyArray;
	for( i = 0; i < m_iSize; i++ ){
		stZaehler.uiZumLoeschenSelektiert	= 0;
		stZaehler.uiGeloescht				= 0;
		stZaehler.uiZumEinfuegenSelektiert	= 0;
		stZaehler.uiNeuEingefuegt			= 0;

		/*****************************************************/
		/*  loescheZielTabelle() */
		/*****************************************************/
		if( loescheZielTabelle(sparHelp) != OK ){
			return 2;
		}
		sprintf( error_msg, "DS zum Loeschen sel.: %d, in Tab.: %s ", stZaehler.uiZumLoeschenSelektiert, sparHelp );
		PrintMsg( fun, error_msg, HINWEIS );
		sprintf( error_msg, "DS geloescht: %d, in Tab.: %s", stZaehler.uiGeloescht, sparHelp );
		PrintMsg( fun, error_msg, HINWEIS );

		/*****************************************************/
		/*  insertQuellInZielTabelle() */
		/*****************************************************/
		if( insertQuellInZielTabelle(sparHelp) != OK ){
			return 2;
		}
		sprintf( error_msg, "DS zum Einfuegen sel.: %d, in Tab.: %s", stZaehler.uiZumEinfuegenSelektiert, sparHelp );
		PrintMsg( fun, error_msg, HINWEIS );
		sprintf( error_msg, "DS eingefuegt: %d, in Tab.: %s", stZaehler.uiNeuEingefuegt, sparHelp );
		PrintMsg( fun, error_msg, HINWEIS );

		sparHelp++;
	}

	freeStringBuffer(&m_sparMyArray);

	/*****************************************************/
	/* Datenbank schliessen */
	/*****************************************************/
	if( schliesseDB() == ERROR ){
		return 2;
	} 

	PrintMsg( fun, "Ende", HINWEIS );

	return OK;
}
/**************************************************************************************************************************/
/* static int loescheZielTabelle(const char* spTabelle) */
/**************************************************************************************************************************/
static int loescheZielTabelle(  MyStringBuffer* spTabelle)
{
	char *fun = "TpLdDB::loescheZielTabelle()";
	
	EXEC SQL BEGIN DECLARE SECTION;
		char	szSql[2048];
	EXEC SQL END DECLARE SECTION;

	/**************************************************************************************************/
	/* SELECT-CURSOR zum Loeschen der Zieltabelle vorbereiten */
	/**************************************************************************************************/
	sprintf( szSql, "SELECT * FROM %s:%s FOR UPDATE", m_spOutputDB, spTabelle );
	EXEC SQL PREPARE preSelZielTabelle FROM :szSql;
	EXEC SQL DECLARE curSelZielTabelle CURSOR WITH HOLD FOR preSelZielTabelle;
	EXEC SQL FREE preSelZielTabelle;

	
	/**************************************************************************************************/
	/* DELETE-CURSOR zum Loeschen der Zieltabelle vorbereiten */
	/**************************************************************************************************/
	sprintf( szSql, "DELETE FROM %s:%s WHERE CURRENT OF curSelZielTabelle", m_spOutputDB, spTabelle );
	EXEC SQL PREPARE preDelZielTabelle FROM :szSql;
	

	/**************************************************************************************************/
	/* SELECT ausfuehren */
	/**************************************************************************************************/
	EXEC SQL OPEN curSelZielTabelle;

	/**************************************************************************************************/
	/*  eigentliche Loesch-Verarbeitung*/
	/**************************************************************************************************/
	m_uiTransactions = 0;
	EXEC SQL BEGIN WORK;
	for(;;){
		m_uiTransactions++;
		/* Max. Transaktionen sind erreicht --> Commit setzen */
		if( (m_uiTransactions % m_uiCommitFrequenz) == 0 ){
			EXEC SQL COMMIT WORK;
			EXEC SQL BEGIN WORK;
		}
		
		EXEC SQL FETCH curSelZielTabelle;
		ERROR_MSG( "EXEC SQL FETCH curSelZielTabelle!" );
		/* Keine weiteren Datensaetze im Cursor */
		if( SQLCODE == SQLNOTFOUND ){
			break;
		}
		stZaehler.uiZumLoeschenSelektiert++;

		EXEC SQL EXECUTE preDelZielTabelle;
 		ERROR_MSG( "EXEC SQL EXECUTE preDelZielTabelle!" );
		stZaehler.uiGeloescht++;	
	}
	
	EXEC SQL COMMIT WORK;	
	EXEC SQL CLOSE curSelZielTabelle;
	ERROR_MSG( "EXEC SQL CLOSE curSelZielTabelle!" );
	EXEC SQL FREE preDelZielTabelle;

	return OK;
}
/**************************************************************************************************************************/
/* static int insertQuellInZielTabelle( const char* spTabelle ) */
/**************************************************************************************************************************/
static int insertQuellInZielTabelle(  MyStringBuffer* spTabelle )
{
	char *fun			= "TpLdDB::insertQuellInZielTabelle()";
	int i				= 0;
	
	EXEC SQL BEGIN DECLARE SECTION;
		char	szSql[2048];
		int		iCountCol;
		char*	sysdesc;
	EXEC SQL END DECLARE SECTION;

	/********************************************************************/
	/*  prepare Select-Statement */
	/********************************************************************/
	sprintf(szSql, "SELECT * FROM %s:%s", m_spInputDB, spTabelle);
	EXEC SQL PREPARE preSelect from :szSql;
	ERROR_MSG( "EXEC SQL PREPARE preSelect" );
	EXEC SQL DECLARE curSelect CURSOR FOR preSelect;

	EXEC SQL ALLOCATE DESCRIPTOR 'desc';
	EXEC SQL DESCRIBE preSelect USING SQL DESCRIPTOR 'desc';
	EXEC SQL GET DESCRIPTOR 'desc' :iCountCol = COUNT;

	EXEC SQL OPEN curSelect;

	/********************************************************************/
	/*  prepare Insert-Statement */
	/********************************************************************/
	sprintf(szSql, "INSERT INTO %s:%s VALUES(", m_spOutputDB, spTabelle);
	for( i = 0; i < iCountCol; i++ ){
		strcat(szSql, "?, ");
	}
	strncpy(szSql + (strlen(szSql) - 2), ")", 1); 
	EXEC SQL PREPARE preInsert from :szSql;
	ERROR_MSG( "EXEC SQL PREPARE preInsert" );
	
	
	/**************************************************************************************************/
	/*  eigentliche Einfuege-Verarbeitung*/
	/**************************************************************************************************/
	m_uiTransactions = 0;
	EXEC SQL BEGIN WORK;
	for(;;){
		m_uiTransactions++;
		/* Max. Transaktionen sind erreicht --> Commit setzen */
		if( (m_uiTransactions % m_uiCommitFrequenz) == 0 ){
			EXEC SQL COMMIT WORK;
			EXEC SQL BEGIN WORK;
		}
		sysdesc = "desc";
		EXEC SQL FETCH curSelect USING SQL DESCRIPTOR :sysdesc;
		ERROR_MSG( "EXEC SQL FETCH curSelect!" );
		
		/* Keine weiteren Datensaetze im Cursor */
		if( SQLCODE == SQLNOTFOUND ){
			break;
		}
		stZaehler.uiZumEinfuegenSelektiert++;

		EXEC SQL EXECUTE preInsert USING SQL DESCRIPTOR 'desc';
 		ERROR_MSG( "EXEC SQL EXECUTE preInsert USING SQL DESCRIPTOR 'desc'!" );
		stZaehler.uiNeuEingefuegt++;

	}
	
	EXEC SQL COMMIT WORK;	
	EXEC SQL CLOSE curSelect;
	ERROR_MSG( "EXEC SQL CLOSE curSelect!" );
	
	EXEC SQL FREE preSelect;
	EXEC SQL FREE preINSERT;
	EXEC SQL DEALLOCATE DESCRIPTOR 'desc';
	

	return OK;
}
/**************************************************************************************************************************/
/* void freeStringBuffer(MyStringBuffer** sparMyArray) */
/**************************************************************************************************************************/
static void freeStringBuffer( MyStringBuffer** sparMyArray )
{		
	/* Speicher freigeben */
	free(*sparMyArray); 
}
/**************************************************************************************************************************/
/* void addToStrArray(MyStringBuffer** sparMyArray, int* piSize, const char* spStringToBuffer) */
/**************************************************************************************************************************/
static void addToStrArray( MyStringBuffer** sparMyArray, int* piSize, const char* spStringToBuffer )
{
	MyStringBuffer* sparString;
		
	if( *sparMyArray == 0 ){
		sparString =(MyStringBuffer*)malloc(1000*sizeof(char[SIZE_ARRAY_ELEMENT]));	
		*sparMyArray = sparString;
		strcpy(sparString[0], spStringToBuffer);
		*piSize = 1;
	} else {
		sparString = *sparMyArray;

		if( (*piSize)%1000 == 0 ){
			sparString = (MyStringBuffer*)realloc( sparString, 
							(*piSize)*(sizeof(char[SIZE_ARRAY_ELEMENT])) + (1000*sizeof(char[SIZE_ARRAY_ELEMENT]) ) );
		}
		(*piSize)++;
		strcpy(sparString[(*piSize-1)], spStringToBuffer);
		*sparMyArray = sparString;
	}
}
/**************************************************************************************************************************/
/* static int KommandoZeileEinlesen( char** argv ) */
/**************************************************************************************************************************/
static int KommandoZeileEinlesen( int argc, char* argv[] )
{
	int		i, h;
	int		skip = NO;
	char*	schalter;
	
	for( i = 1; i < argc; i++ ){
		if( skip ){
			skip = NO;
			continue;
		}
		schalter = argv[i];
		if( !strcmp( schalter, "-inputdb" ) ){
			m_spInputDB = argv[i+1]; 
			skip = YES;
		} else if( !strcmp(schalter, "-outputdb") ){   
			m_spOutputDB = argv[i+1]; 
			skip = YES;
		} else if( !strcmp( schalter, "-commitfrequenz") ){   
			/* Fehler der atoi-Funktion  */
			if( atoi(argv[i+1]) == 0 ){
				m_uiCommitFrequenz = MAX_TRANSAKTION; /* = 300: Standard-Verhalten wird angenommen */
			} else {
				m_uiCommitFrequenz = atoi(argv[i+1]);
			}
			skip = YES;
		} else if( !strcmp(schalter, "-tabellen") ){
			for( h = (i + 1); h < argc; h++ ){
				/* printf( "argv[h][0]: %c\n\n", argv[h][0]); */
				if( argv[h][0] == '-' ){ /*  == 0 --> Strings identisch */
					i = h;
					skip = NO;	
					break;		
				} else {
					addToStrArray( &m_sparMyArray, &m_iSize, argv[h]);
				}
			}
			break;	/* Werden alle Tabellen eingelesen und es folgt kein Parameter ("-"), dann muss nicht weiter ueber die */
					/* Parameter-Liste iteriert werden, denn man steht dann schon am Ende  */
		} else if ( !strcmp( schalter, "-version" ) ){
			printVersion(versioninfo);
			bVersion = TRUE;
			return 0;
		}
		else {
			skip = ERROR;
			break;
		}
	}                                            

	if( argc == 1 || m_spInputDB == NULL || m_spOutputDB == NULL || skip == ERROR || m_iSize == 0 ){
		printf( "Aufruf: tplddb -inputdb <Datenbankname> \n"
				"-outputdb <datenbankname> \n"
				"-commitfrequenz <Zahl fuer Transaktionsvolumen> \n"
				" -tabellen <Tabellen1 Tabelle2 etc>\n"							
		 		"Beispiel: > tplddb -inputdb phosix@db1_rmfuze2_shm -outputdb phosix@db3_rmfuze2_shm -tabellen filiale\n"
		 		"--> Loescht alle Datenaetze in der Tabelle 'filiale' in der Datenbank 'db3'\n"
				"und ueberspielt alle Daten aus der Tabelle 'filiale' aus der Datenbank 'db1' in die 'db3'\n");
		return ERROR; /* ERROR = -1: Fehlerhafte KommandoZeile */
	}

	return OK; /* OK = 0 */
}
/**************************************************************************************************************************/
/* static int oeffneDB() */
/**************************************************************************************************************************/
static int oeffneDB()
{
	char *fun = "TpLdDB::oeffneDB()";
	
	exec sql begin declare section;
		char* spInputDB		= m_spInputDB;
	exec sql end declare section;
  
	
	exec sql database :spInputDB;
	ERROR_MSG("Fehler beim Oeffnen der DB") /* prueft sqlca.sqlcode < 0 --> ERROR (-1)*/
	
	exec sql set lock mode to wait 20;
	ERROR_MSG("Fehler: >exec sql set lock mode to wait 20<") /* prueft sqlca.sqlcode < 0 --> ERROR (-1)*/
	
	exec sql set isolation to dirty read;
	ERROR_MSG("Fehler: >exec sql set isolation to dirty read<") /* prueft sqlca.sqlcode < 0 --> ERROR (-1)*/

	return SQLCODE /* #define SQLCODE sqlca.sqlcode */;
}
/**************************************************************************************************************************/
/* static int schliesseDB() */
/**************************************************************************************************************************/
static int schliesseDB()
{
	char *fun = "TpLdDB::schliesseDB()";

	exec sql close database;
	ERROR_MSG("Fehler beim Schliessen der DB") /* prueft sqlca.sqlcode < 0 --> ERROR (-1)*/
	
	return SQLCODE /* #define SQLCODE sqlca.sqlcode */;
}
/**************************************************************************************************************************/
/* static void PrintMsg(char *fun, char *error_msg, char mld ) */
/**************************************************************************************************************************/
static void PrintMsg( char *fun, char *error_msg, char mld )
{
	FILE *fp;
	struct tm *localtime();
	struct tm *zeit;
	long hour1;
	pid_t pid;
	long time();
	char logFile[L_TEXT];

	pid = getpid();
	hour1 = time( &hour1 );
	zeit  = localtime( &hour1 );

#ifdef UNSER_UEBERFLIEGER
	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) );
	if ( ( fp = fopen( logFile, "a" ) ) == (char *)0 )
	   return;
#else
	{
	char *str;
	if ( ( str = getenv( "LOG_PATH" ) ) != NULL )
	   sprintf( logFile, "%s/wws.log", str );
	else
	   sprintf( logFile, "wws.log" );
	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
	   return;
	}
#endif

	fprintf( fp, "%c %02d.%02d.%02d %02d:%02d:%02d "
			"pid=%05ld %.6s %s %s->%d/%d\n",
			mld,
			zeit->tm_mday,
			zeit->tm_mon + 1,
			zeit->tm_year,
			zeit->tm_hour,
			zeit->tm_min,
			zeit->tm_sec,
			pid,
			"tplddb",
			fun,
			error_msg, 
			SQLCODE,
			SQLISAM );

	fclose(fp);
}

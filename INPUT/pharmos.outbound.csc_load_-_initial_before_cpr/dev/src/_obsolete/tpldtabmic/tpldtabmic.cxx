/********************************************************************************************/
/*     Hauptmodul: tpldtabmic.ecc															*/
/*         Source: 																			*/
/*          Autor: Bischof Björn															*/
/*       Erstellt: 02.04.2003																*/
/*        Sprache: C																		*/
/*        Erzeugt: manuell																	*/
/*        Aufgabe:																			*/
/*         Aufruf: tpldtabmic	-inputdb        phosix@db1_rmfuze2_shm	*/
/*				-outputdb       phosix@db3_rmfuze2_shm	*/ 
/*				-tab            akdauftrag		*/ 
/*				-fromclausel 	beskopf[, besposi]	*/
/*				-whereclausel 	filialnr = 5		*/
/********************************************************************************************/

/*******************************************************************************************/
/* VERSION */
/*******************************************************************************************/
#include "csc_load_version.h"

#define PROJECTNAME	 "tpldtabmic"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

//static char *SCCSID = "@(#)PRZ GmbH Stand: 1.0.0 $Header: /prj/df/unix/tpldtabmic.ecc 14    02.04.03 17:04 66aebisc $";


/*******************************************************************************************/
/* INCLUDE */
/*******************************************************************************************/
#include <stdlib.h> 
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include "libtpld/define.h"
#include "libtpld/qtime.h"

#include <string.h>
#include <unistd.h>

EXEC SQL include locator;
EXEC SQL include sqlca;
EXEC SQL include sqltypes;
EXEC SQL include decimal;
EXEC SQL include datetime;

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
	unsigned int uiZumEinfuegenSelektiert;
	unsigned int uiNeuEingefuegt;
}; 

/*******************************************************************************************/
/* MODUL-GLOBALE VARIABLEN       Vorsicht mit NULL  unter solars !!!!!!!!!! */
/*******************************************************************************************/
static char*                    m_spInputDB       = 0; /*  NULL;  */
static char*                    m_spOutputDB      = 0; /*  NULL;  */
static char*                    m_spTabelle       = 0; /*  NULL;  */
static char*                    m_spSelect        = 0; /*  NULL;  */
static char*                    m_spFromClausel   = 0; /*  NULL;  */
static char*                    m_spWhereClausel  = 0; /*  NULL;  */
static unsigned int             m_uiTransactions  = 0;

/**************************************************************************************************************************/
/* VORWAERTS-DECLARATION */
/**************************************************************************************************************************/
/* size_t			_msize( void *memblock ); */
static struct	T_Zaehler stZaehler = {0, 0};
static int		KommandoZeileEinlesen( int argc, char** argv );
static int		oeffneDB();
static int		fuegeQuellInZielTabelle();
static int		schliesseDB();
static void		PrintMsg(char *fun, char *error_msg, char mld );
static void		holeDatenAusDatensatz(char* DS, char* desc, int iCol);
static int		loadSelectAttributes( char* spSelectAttr );
/**************************************************************************************************************************/
/* int main( int argc, char **argv ) */
/**************************************************************************************************************************/
int main( int argc, char* argv[] )
{
	char error_msg[512];
	char *fun					= "TpLdTabMic::main()";
	MyStringBuffer* sparHelp	= 0;
	int i						= 0;

	setbuf(stdout, 0);	

	/*****************************************************/
	/* Aufrufparameter werden ausgelesen */
	/*****************************************************/
	if( KommandoZeileEinlesen(argc, argv) == ERROR ){
		return 2;
	}
	sprintf( error_msg, "Begin: InputDB <%s>, OutputDB <%s> und Tabelle <%s>", m_spInputDB, m_spOutputDB, m_spTabelle );
	PrintMsg( fun, error_msg, HINWEIS );


	/*****************************************************/
	/* Datenbank oeffnen */
	/*****************************************************/
	if( oeffneDB() == ERROR /* = -1 */ ){
		return 2;
	}

	/*****************************************************/
	/*  fuegeQuellInZielTabelle() */
	/*****************************************************/
	if( fuegeQuellInZielTabelle() != OK ){
		schliesseDB();
		return 2;
	}
	sprintf( error_msg, "DS zum Inserten sel.: %d, in Tab.: %s ", stZaehler.uiZumEinfuegenSelektiert, m_spTabelle );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "DS eingefuegt: %d, in Tab.: %s", stZaehler.uiNeuEingefuegt, m_spTabelle );
	PrintMsg( fun, error_msg, HINWEIS );


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
/* static int loadSelectAttributes( char* spSelectAttr ) */
/**************************************************************************************************************************/
static int loadSelectAttributes( char* spSelectAttr )
{
	char* fun = "TpLdTabMic::loadSelectAttributes()";
	int iRc = ERROR;
	size_t size = 0;

	#define LEN_TERM_NULL	1
	#define LEN_KOMMA		1
	#define LEN_PUNKT		1
	#define LEN_SPACE		1	
	#define KOMMA_STRING	","
	#define PUNKT_STRING	"."
	#define SPACE_STRING    " "

	EXEC SQL BEGIN DECLARE SECTION;
		char	szSql[512];
		char	szColName[128 + 1];
	EXEC SQL END DECLARE SECTION;

	/*
	if( 0 != spSelectAttr ){
		free spSelectAttr;
	}*/
	


	/* */
	sprintf( szSql, "select colname from syscolumns c , systables t where c.tabid = t.tabid and t.tabname = '%s'", m_spTabelle );
	
printf( "%s: %s\n", fun, szSql );

	/* Select-Statement praeparieren */
	EXEC SQL PREPARE preSelColNames FROM :szSql;
	ERROR_MSG("EXEC SQL PREPARE preSelColNames FROM :szSql;");
	
	/* Cursor praeparieren */
	EXEC SQL DECLARE curSelColNames CURSOR FOR preSelColNames;
	
	/* praepariertes Select-Statement freigeben */
	EXEC SQL FREE preSelColNames;
	

printf( "%s: vor dem malloc\n", fun );
	/* */
	spSelectAttr = (char*) malloc( sizeof(char) * strlen(m_spTabelle) + LEN_PUNKT/*'.'*/ + LEN_TERM_NULL/*'\0'*/);
	if( spSelectAttr == NULL ){
		PrintMsg( fun, "Fehler beim dynamische Speicherallokieren von spSelectAttr!", FEHLER );
		return iRc;
	}
	strcpy( spSelectAttr, m_spTabelle );
	strcat(spSelectAttr, PUNKT_STRING );
	spSelectAttr[size-1] = 0;
	size = strlen( spSelectAttr );


printf( "%s: %s\n", fun, spSelectAttr );

	/* Cursor oeffnen: laed ersten Datensatz */
	EXEC SQL OPEN curSelColNames;
	
	/* ueber kompletten Cursor iterieren */
printf( "%s: %s\n", fun, "vor der For" );
	for(;;){

printf( "%s: in der For %s\n", fun, spSelectAttr );
		
		EXEC SQL FETCH curSelColNames INTO :szColName;
		if( SQLCODE < 0 ){
			PrintMsg( fun, "EXEC SQL FETCH curSelColNames!", FEHLER );
			iRc = ERROR;
			break;
		}

		/* Keine weiteren Datensaetze im Cursor */
		if( SQLCODE == SQLNOTFOUND ){
			printf( "%s: SQLCODE == SQLNOTFOUND: break\n", fun );			
			break;
		}	
printf( "%s: in der For %s %s\n", fun, spSelectAttr, szColName );


		/* */
		spSelectAttr = (char*)realloc( spSelectAttr, size + strlen(szColName) + 
													 LEN_KOMMA + LEN_SPACE + strlen(m_spTabelle) +  LEN_PUNKT + LEN_TERM_NULL );
		
printf( "%s: in der For nach realloc %s\n", fun, spSelectAttr );

		if( spSelectAttr == NULL ){
			PrintMsg( fun, "Fehler beim dynamische Speicherallokieren von spSelectAttr!", FEHLER );
			EXEC SQL CLOSE curSelColNames;
			return iRc;
		}

		strcat( spSelectAttr, KOMMA_STRING );
		strcat( spSelectAttr, SPACE_STRING );
		strcat( spSelectAttr,  m_spTabelle );
		strcat( spSelectAttr,  PUNKT_STRING );
		spSelectAttr[size - 1] = 0;
		size = strlen( spSelectAttr );

printf( "%s: am Ende der for  %s\n", fun, spSelectAttr );

	}
	
	/* Fuer das letzte Attribut muss das angehaengte Komma, Leerzeichen, Punkt und Tabellenname abgeschnitten werden */
	spSelectAttr[size - (1 + LEN_KOMMA + LEN_SPACE + strlen(m_spTabelle) + LEN_PUNKT) ] = 0;

printf( "%s: nach for  komplett %s\n", fun, spSelectAttr );

	/* Cursor schliessen */
	EXEC SQL CLOSE curSelColNames;
	ERROR_MSG( "EXEC SQL CLOSE curSelColNames!" );

printf( "%s: am Ende \n", fun );

	return iRc;

}
/**************************************************************************************************************************/
/* static int fuegeQuellInZielTabelle() */
/**************************************************************************************************************************/
static int fuegeQuellInZielTabelle()
{
	char	error_msg[512];
	char	szDS[4096];
	char*	fun		= "TpLdTabMic::fuegeQuellInZielTabelle()";
	int		i		= 0;

	EXEC SQL BEGIN DECLARE SECTION;
		char	szSql[4096];
		int	iCountCol;
		char*	sysdesc;
		int	iCol	= 0;
		/* char*   spSelAttr = 0; */
	EXEC SQL END DECLARE SECTION;

	strcpy(szDS, " ");

/*
#ifndef NDEBUG
printf( "%s: %s\n", fun, spSelAttr );
#endif	
	loadSelectAttributes( spSelAttr );

#ifndef NDEBUG
printf( "%s: %s\n", fun, spSelAttr );
printf( "%s: %s\n", fun, spSelAttr );
return ERROR;
#endif
*/
	/**************************************************************************************************/
	/* SELECT-CURSOR zum Einfuegen der Zieltabelle vorbereiten */
	/**************************************************************************************************/
	if(  NULL == m_spSelect ){
		sprintf( szSql, "SELECT * FROM %s:%s WHERE %s", m_spInputDB, m_spFromClausel, m_spWhereClausel);
	} else {
		sprintf( szSql, "SELECT %s FROM %s:%s WHERE %s", m_spSelect, m_spInputDB, m_spFromClausel, m_spWhereClausel);
	}

#ifndef NDEBUG
	printf("PRESELECT szSql: %s\n", szSql );
#endif

	EXEC SQL PREPARE preSelQuellTabelle FROM :szSql;
	ERROR_MSG("EXEC SQL PREPARE preSelQuellTabelle FROM :szSql;");
	EXEC SQL DECLARE curSelQuellTabelle CURSOR WITH HOLD FOR preSelQuellTabelle;

	/**************************************************************************************************/
	/* DESCRIPTOR anlegen */
	/**************************************************************************************************/
	EXEC SQL ALLOCATE DESCRIPTOR 'desc';
	EXEC SQL DESCRIBE preSelQuellTabelle USING SQL DESCRIPTOR 'desc';
	EXEC SQL GET DESCRIPTOR 'desc' :iCountCol = COUNT;
		
	/**************************************************************************************************/
	/* SELECT ausfuehren */
	/**************************************************************************************************/
	EXEC SQL OPEN curSelQuellTabelle;
	if( SQLCODE < 0 ){
		EXEC SQL FREE preSelQuellTabelle;;
		EXEC SQL DEALLOCATE DESCRIPTOR 'desc';
		strcpy( error_msg, "FEHLER: EXEC SQL OPEN curSelQuellTabelle!");
		PrintMsg( fun, error_msg, FEHLER );
		return ERROR;
	}
	
	/********************************************************************/
	/*  prepare Insert-Statement */
	/********************************************************************/
	sprintf(szSql, "INSERT INTO %s:%s VALUES(", m_spOutputDB, m_spTabelle);
	for( i = 0; i < iCountCol; i++ ){
		strcat(szSql, "?, ");
	}
	strncpy(szSql + (strlen(szSql) - 2), ")", 1); 

#ifndef NDEBUG
	printf("PREINSERT szSql: %s\n", szSql );
#endif
	
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
		if( (m_uiTransactions % MAX_TRANSAKTION) == 0 ){
			EXEC SQL COMMIT WORK;
			EXEC SQL BEGIN WORK;
		}
		sysdesc = "desc";
		EXEC SQL FETCH curSelQuellTabelle USING SQL DESCRIPTOR :sysdesc;
		/* ERROR_MSG( "EXEC SQL FETCH curSelQuellTabelle!" ); */
		if( SQLCODE < 0 ){
			EXEC SQL FREE preSelQuellTabelle;;
			EXEC SQL FREE preINSERT;
			EXEC SQL DEALLOCATE DESCRIPTOR 'desc';
			EXEC SQL ROLLBACK WORK;	
			sprintf( error_msg, "FEHLER: EXEC SQL FETCH curSelQuellTabelle!");
			PrintMsg( fun, error_msg, FEHLER );
			return ERROR;
		}
		
		/* Keine weiteren Datensaetze im Cursor */
		if( SQLCODE == SQLNOTFOUND ){
			break;
		}
		stZaehler.uiZumEinfuegenSelektiert++;

		EXEC SQL EXECUTE preInsert USING SQL DESCRIPTOR 'desc';
 		/* ERROR_MSG( "EXEC SQL EXECUTE preInsert USING SQL DESCRIPTOR 'desc'!" ); */
		if( SQLCODE < 0 ){
			/* holeDatenAusDatensatz(szDS, sysdesc, iCountCol);
			sprintf( error_msg, "FEHLER: EXEC SQL EXECUTE preInsert USING SQL DESCRIPTOR 'desc' mit Fehler-Nr.:(SQLISAM)<%ld> "
								"bei Tabelle: <%s> und DS: <%s>", SQLISAM, m_spTabelle, szDS); 
			*/
			sprintf( error_msg, "FEHLER: EXEC SQL EXECUTE preInsert USING SQL DESCRIPTOR 'desc'!");
			PrintMsg( fun, error_msg, FEHLER );
			sprintf( error_msg, "anormales Programm-Ende!");
			PrintMsg( fun, error_msg, FEHLER );
			
			EXEC SQL FREE preSelQuellTabelle;;
			EXEC SQL FREE preINSERT;
			EXEC SQL DEALLOCATE DESCRIPTOR 'desc';
			EXEC SQL ROLLBACK WORK;	

			return ERROR;
		}
		stZaehler.uiNeuEingefuegt++;

	}
	
	EXEC SQL COMMIT WORK;	
	EXEC SQL CLOSE curSelQuellTabelle;
	ERROR_MSG( "EXEC SQL CLOSE curSelQuellTabelle!" );
	
	EXEC SQL FREE preSelQuellTabelle;;
	EXEC SQL FREE preINSERT;
	EXEC SQL DEALLOCATE DESCRIPTOR 'desc';
	
	return OK;
}
/**************************************************************************************************************************/
/*  */
/**************************************************************************************************************************/
static void holeDatenAusDatensatz(char* DS, char* desc, int iCol)
{
	EXEC SQL BEGIN DECLARE SECTION;
		char*		szDS;
		char		szX[40+1];
		char*		spDesc = desc;
		int			iCountCol;
		short		char_len, type, ind;
		int			int_data, i;
		char		name[40];
		short		short_data;
		decimal		dec_data;

		char*		char_data;
		long		date_data;
		datetime	dt_data;
	EXEC SQL END DECLARE SECTION;
	
	szDS = DS;
	strcpy(szDS, "Datensatz-Werte: ");
	strcpy(szX, " ");
	strcpy(name, " "); 
	iCountCol = iCol;

	for( i = 1; i < iCountCol; i++ ){
		exec sql get descriptor :spDesc VALUE :i :type = TYPE;
		switch( type ){
			case SQLSERIAL:
			case SQLINT:	exec sql get descriptor :spDesc VALUE :i
							:ind        = INDICATOR,
							:name       = NAME,
							:int_data   = DATA;
							if( ind == -1 ){
								strcpy(szX, "NULL");
							} else {
								sprintf(szX, "%ld", int_data);	
							}
							strcat(szX, ", ");
							strcat(szDS, szX);
							printf("Name: %s\n", name);
							break;
			case SQLSMINT:  exec sql get descriptor :spDesc VALUE :i
							:ind		= INDICATOR,
							:name       = NAME,
							:short_data = DATA;
							if( ind == -1 ){
								strcpy(szX, "NULL");
							} else {
								sprintf(szX, "%d", int_data);	
							}
							strcat(szX, ", ");
							strcat(szDS, szX);
							printf("Name: %s\n", name);
							break;
			/*
			case SQLDECIMAL:
			case SQLMONEY:	exec sql get descriptor :spDesc VALUE :i
							:ind		= INDICATOR,
							:name       = NAME,
							:dec_data	= DATA;
							if( ind == -1 ){
								sprintf(szX, "%s:NULL, ", name);
								strcat(szDS, szX);
							} else {
								if( type == SQLDECIMAL ){
									rfmtdec(&dec_data, "###,###,###.##", szX);
								} else {
									rfmtdec(&dec_data, "$$$,$$$,$$$.$$", szX);
								}
								strcat(szX, ", ");
								strcat(szDS, szX);
							}
							break;
			case SQLVCHAR:
						printf("SQLVCHAR\n");
			case SQLCHAR:   exec sql get descriptor :spDesc VALUE :i
					:char_len   = LENGTH,
					:name       = NAME;
				amount = char_len;
				if( char_data = (char*)(malloc(amount + 1)) ){
				  exec sql get descriptor :spDesc VALUE :i
					:char_data  = DATA,
					:ind        = INDICATOR;
					if( ind == -1 ){
					  printf("\n%.20s: NULL\n ", name);
					} else {
					  printf("\n%.20s: %s\n", name, char_data);
					}
				} else {
					printf("\n%.20s\n ", name);
					printf("Can't display: out of memory");
				}
				printf("SQLCHAR\n");
				break;
			*/
			default:   /* printf("\nUnexpected Data-Type: %d", type); */
						/*
						exec sql get descriptor :spDesc VALUE :i
						:ind		= INDICATOR,
						:name       = NAME;
						if( ind == -1 ){
							sprintf(szX, "%s:NULL, ", name);
						} else {
							sprintf(szX, "%s:Keine Ermittlung, ", name);
						}
						strcat(szDS, szX);
						*/
			break;
		}
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
		} else if( !strcmp(schalter, "-select") ){   
			m_spSelect = argv[i+1]; 
			skip = YES;
		} else if( !strcmp( schalter, "-tab") ){   
			m_spTabelle = argv[i+1];
			skip = YES;
		} else if( !strcmp(schalter, "-fromclausel") ){
			m_spFromClausel = argv[i+1];
			skip = YES;
		} else if( !strcmp(schalter, "-whereclausel") ){
			m_spWhereClausel = argv[i+1];
			skip = YES;
		} else if ( !strcmp( schalter, "-version" ) ){
			printVersion(versioninfo);
			return 0;
		} else {
			skip = ERROR;
			break;
		}
	}                                            


	if( argc == 1 || m_spInputDB == NULL || m_spOutputDB == NULL || m_spTabelle == NULL || 
   	                 m_spFromClausel == NULL || m_spWhereClausel == NULL || skip == ERROR ){
	printf("Aufruf: tpldtabmic\t -inputdb        <Datenbankname, von der gelesen wird> \n"
                                   "\t\t\t -outputdb       <Datenbankname, in die geschrieben wird>\n"
                                   "\t\t\t [-select        <die Attribute für den Select muessen angegeben werden, \n"
                                   "\t\t\t                 wenn mehr als eine Tabelle in der FROM-Clausel angegeben wurde>]\n"
                                   "\t\t\t -tabelle        <Tabelle, von der gelesen und auch geschrieben wird;"  
                                                          "wichtig für SELECT- und INSERT-PREPARE>\n"
                                   "\t\t\t -fromclausel    <Tabellenangabe; mehr als eine Tabelle muss angegeben werden,"
                                                          "wenn sich die WHERE-Bed auf mehr als eine Tabelle bezieht>\n"
                                   "\t\t\t -whereclausel   <SQL-WHERE-Clausel>\n"
		 		   "Beispiel:\n"
                                   "\t tpldtabmic\t\t -inputdb      pps1cg@onl_sofumi1_shm\n" 
                                          "\t\t\t\t -outputdb     pps1cch@onl_sofumi1_shm\n" 
                                          "\t\t\t\t -select      \"bestell_nr, ..., ...\" \n" 
			                  "\t\t\t\t -tabelle      besposi\n"
                                          "\t\t\t\t -fromclausel  \"beskopf, besposi\" \n"
                                          "\t\t\t\t -whereclausel \"beskopf.bestell_nr = besposi.bestell_nr" 
                                                                   "and beskopf.bestell_nr in ( 75002, 75003 )\" \n");
		return ERROR; /* ERROR = -1: Fehlerhafte KommandoZeile */
	}

printf("m_spInputDB:<%s>\n",      m_spInputDB);
printf("m_spOutputDB:<%s>\n",     m_spOutputDB);
if( m_spSelect != NULL) {
	printf("m_spSelect :<%s>\n",     m_spSelect);
}
printf("m_spTabelle:<%s>\n",      m_spTabelle);
printf("m_spFromClausel:<%s>\n",  m_spFromClausel);
printf("m_spWhereClausel:<%s>\n", m_spWhereClausel);

	return OK; /* OK = 0 */
}
/**************************************************************************************************************************/
/* static int oeffneDB() */
/**************************************************************************************************************************/
static int oeffneDB()
{
	char *fun = "TpLdTabMic::oeffneDB()";
	
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

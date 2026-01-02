/********************************************************************************/
/*     Hauptmodul: loadarticleinfo.ecc												*/
/*         Source: 																*/
/*          Autor: Ronald Imschweiler											*/
/*       Erstellt: 03.11.2009													*/
/*        Sprache: C															*/
/*        Erzeugt: manuell														*/
/*        Aufgabe: Uebernehmen Artikelinformationen aus RS + BG				    */
/*         Aufruf: loadarticleinfo.sh -start									*/
/*																				*/
/********************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadarticleinfo"

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
#include "dateiverarb.h"


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
static long readcount		= 0;
static long inscount		= 0;
static int bVersion = 0;
exec sql begin declare section;
char datenbank[60];
	char Infotext[1025];
	char Helptext[1120];
	char outtext[257];
	char Buffertext[2050];
	int seqnr;
	long articleno;
	long artnr;
exec sql end declare section;

/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
static int	KommandoZeileEinlesen( int argc, char** argv );
static int	oeffneDB();
static int	schliesseDB();
static int	PreInsInfo();
static int	InsInfo();
static int	DelInfo();
static void PrintMsg(char *fun, char *error_msg, char mld );

/********************************************************************************/
/* int main( int argc, char **argv ) */
/********************************************************************************/
int main( int argc, char* argv[] )
{
	char error_msg[512];
	char *fun = "main()";
	int len,satzlen,inspointer,startadr,testlen;

	setbuf(stdout, 0);	

	/*****************************************************/
	/* Aufrufparameter werden ausgelesen */
	/*****************************************************/
	if( !KommandoZeileEinlesen( argc, argv ) == OK )
	{
		printf( "Aufruf: %s -db Datenbank \n"
		 		"Beispiel: > %s -db pos1g@db1_pos1_tcp <\n"		
				"--> Einfuegen Artikelinformationen\n", argv[0], argv[0] );fflush(stdout);
		return 1;
	}
	if(bVersion)
	{
		return OK;
	}

	/*****************************************************/
	/* Datenbank oeffnen */
	/*****************************************************/
	if( !oeffneDB() == OK )
	{
		PrintMsg( fun, "Fehler beim ÷ffnen der Datenbank!", FEHL );
		return 2;
	} 

	sprintf( error_msg, "gestartet mit -db %s", datenbank );
	PrintMsg( fun, error_msg, HINW );

	/*****************************************************/
	/* Durchsuchen Verzeichnis nach Inputfiles        */
	/*****************************************************/
	if( !InfoGetDir() == OK )
	{
		PrintMsg( fun, "Keine Inputfiles vorhanden", HINW );
		return 0;
	} 

	/*****************************************************/
	/* Abarbeiten Inputfilelise            */
	/*****************************************************/
	
	if( !PreInsInfo() == OK )
	{
		PrintMsg( fun, "Fehler beim Declaration Einfuegen Satz!", FEHL );
		return 2;
	}

	exec sql begin work;
	ERROR_MSG( "begin Work:" )
	for(;;)
	{
		/*****************************************************/
		/* Oeffnen naechste Inputfile            */
		/*****************************************************/
		articleno = InfoGetFile();
		if( articleno < 0 )
		{
			PrintMsg( fun, "Ende Inputfileliste", HINW );
			break;
		}
		DelInfo();
		readcount++;
		Buffertext[0] = '\0';
		for(seqnr = 0;;)
		{
		/*****************************************************/
		/* Einlesen Inputfile            */
		/*****************************************************/
			if( !InfoReadFile(Infotext) == OK) break;
			satzlen = strlen(Infotext);
			testlen = satzlen;
			if(Buffertext[0] != '\0')
			{
				testlen += strlen(Buffertext);
			}
			if(testlen <= 80)
			{
				satzlen--;
				sprintf(Helptext,"%*.*s\r\n",satzlen,satzlen,Infotext);
			}
			else
			{
				if(Buffertext[0] == '\0')
				{
					startadr = 80;
				}
				else if(strlen(Buffertext) < 80)
				{
					for(inspointer = strlen(Buffertext)-2;inspointer>0;inspointer--)
					{
						if(!strncmp(Buffertext+inspointer,"\r\n",2))
						{
							inspointer += 2;
							break;
						}
					}
					if(inspointer = 0)
					{
						startadr = 80 - strlen(Buffertext);
					}
					else
					{
						startadr = (strlen(Buffertext)-inspointer);
					}
				}
				Helptext[0] = '\0';
				for(;;)
				{
					if(satzlen > startadr)
					{
						for(inspointer = startadr;inspointer > 0;inspointer--)
						{
							if(Infotext[inspointer] == ' ')
							{
								sprintf(Helptext,"%s%*.*s\r\n",Helptext,inspointer,inspointer,Infotext);
								sprintf(Infotext,"%s",Infotext+inspointer+1);
								satzlen = strlen(Infotext);
								break;
							}
						}
						if(inspointer == 0)
						{
							sprintf(Helptext,"%s%*.*s\r\n",Helptext,80,80,Infotext);
							sprintf(Infotext,"%s",Infotext+80);
							satzlen = strlen(Infotext);
						}
					}
					else
					{
						if(Infotext[satzlen-1] == '\n')
						{
							satzlen--;
							sprintf(Helptext,"%s%*.*s\r\n",Helptext,satzlen,satzlen,Infotext);
							break;
						}
						else
						{
							sprintf(Helptext,"%s%s",Helptext,Infotext);
							break;
						}
					}
					startadr = 80;
				}
			}
			len = strlen(Helptext);
			sprintf(Buffertext,"%s%*.*s",Buffertext,len,len,Helptext);
			for(;;)
			{
				if(strlen(Buffertext) > 256)
				{
					strncpy(outtext,Buffertext,256);
					sprintf(Buffertext,"%s",Buffertext+256);
					if( !InsInfo() == OK )
					{
						PrintMsg( fun, "Fehler beim Einfuegen Satz!", FEHL );
						return 3;
					}
					inscount++;
					seqnr++;
				}
				else break;
			}
		}
		if(Buffertext[0] != '\0')
		{
			sprintf(outtext,"%s",Buffertext);
			if( !InsInfo() == OK )
			{
				PrintMsg( fun, "Fehler beim Einfuegen Satz!", FEHL );
				return 3;
			}
			inscount++;
		}
		if (inscount%200 == 0)
		{
			exec sql commit work;
			ERROR_MSG( "Commit Work200:" )
			exec sql begin work;
			ERROR_MSG( "begin Work200:" )
		}
		if( !InfoClearFile() == OK )
		{
			PrintMsg( fun, "Fehler bei Umkopieren Inputfiles", HINW );
			return ERROR;
		} 
	}
	exec sql commit work;
	ERROR_MSG( "Commit Work:" )
		
	/*****************************************************/
	/* Datenbank schliessen */
	/*****************************************************/
	if( !schliesseDB() == OK )
	{
		PrintMsg( fun, "Fehler beim Schlieﬂen der Datenbank!", FEHL );
		return 5;
	} 

	
	sprintf( error_msg, "Anzahl gelesene/eingefuegter Saetze : %d/%d", readcount, inscount );
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
			sprintf( datenbank, "%s", argv[i] );
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			bVersion = 1;
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

	return OK;
}

/*********************************************************************************/
/* static int oeffneDB() */
/*********************************************************************************/
static int oeffneDB()
{
	char *fun = "oeffneDB()";
  
	exec sql database :datenbank;
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
/* static int PreInsInfo()													*/
/****************************************************************************/

static int PreInsInfo()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "PreInsInfo";

	exec sql begin declare section;
		char	str[2048];
	exec sql end declare section;

	/* SELECT-Cursor vorbereiten */
	strcpy( str, "insert into artinfotext (" );
	strcat( str, "articleno," );
	strcat( str, "sequenceno," );
	strcat( str, "artinfotype," );
	strcat( str, "infotext" );
	strcat( str, " ) values ");
	strcat(str,"( ?,?,?,? )");
	EXEC SQL PREPARE preInsInfo from :str;

	/* DELETE-Cursor vorbereiten */
	strcpy( str, "select articleno from artinfotext " );
	strcat( str, "where articleno = ? " );
	strcat( str, "for update" );
	EXEC SQL PREPARE preDelInfo from :str;
	exec sql declare CDelInfo cursor for preDelInfo;

	strcpy( str, "delete from artinfotext " );
	strcat( str, "where current of CDelInfo" );
      
	exec sql prepare del_artinfo from :str;
	ERROR_MSG( "prepare del_artinfo" )

	return OK;
}

/****************************************************************************/
/* static int InsInfo()														*/
/****************************************************************************/

static int InsInfo()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "InsInfo";

	EXEC SQL EXECUTE preInsInfo using
		:articleno,
		:seqnr,
		'0',
		:outtext;
	ERROR_MSG( "EXEC SQL EXECUTE preInsInfo!" );

	return OK;
}

/****************************************************************************/
/* static int DelInfo()														*/
/****************************************************************************/

static int DelInfo()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "DelInfo";

	exec sql open CDelInfo using :articleno;
	ERROR_MSG( "open CDelInfo" )

	for(;;)
	{
		exec sql fetch CDelInfo into :artnr;
		ERROR_MSG( "fetch CDelInfo" )
		if ( sqlca.sqlcode == 100 ) break;

		EXEC SQL EXECUTE del_artinfo;
		ERROR_MSG( "delete artinfotext" )
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
			"pid=%05ld %s %s %s->%d/%d\n",
			mld,
			zeit->tm_mday,
			zeit->tm_mon + 1,
			zeit->tm_year,
			zeit->tm_hour,
			zeit->tm_min,
			zeit->tm_sec,
			pid,
			"loadarticleinfo",
			fun,
			error_msg, 
			SQLCODE,
			SQLISAM );

	fclose(fp);
}

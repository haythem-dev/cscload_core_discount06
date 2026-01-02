/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadcustgoups"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/*****************************************************************************/
/* Einfuegen neuer Tabellen in das Artikelladeprogramm                       */
/*****************************************************************************/
/* 1 Tabelle im Incudefile definieren und ANZ_TABELLEN aktualisieren         */
/* 2 Eintrag in Funktion SetzeSchalterTabelle erzeugen                       */
/* 3 Implementierung und Aufruf der Initialisierungsfunktion (create table..)*/
/* 4 Implementierung und Aufruf der Ladefunktionfunktion (in Bezug auf DKART)*/
/* 5 Implementierung und Aufruf der Endefunktion (drop/create index, rename )*/
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "customergrpflags.h"
#include "custgrpflagtypes.h"
#include "customergroup.h"
#include <dirent.h>                                     
#include <errno.h>                                     
#include <string.h>
#include <unistd.h>

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define NOTFOUND           sqlca.sqlcode == SQLNOTFOUND

#define OK                   0
#define NO                   0
#define YES                  1
#define ERROR               -1
#define INSERT               1
#define NOT_FOUND            1
#define FILE_NOT_FOUND       1
#define WARNING             -2
#define HINW               'H'
#define FEHL               'F'
#define RIO_EOF            110
#define RIO_NOFIND         111
#define INDATABASE         "phosix@db2_rmfuze1_tcp"
#define OUTDATABASE        "phosix"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 300                  /* nach n-saetzen commit  */


char log_file [300 + 1];
char dateiname[L_TEXT];
int Germany = 0;

exec sql begin declare section;
char indatenbank[60];
char outdatenbank[60];
struct N_CUSTOMERGRPFLAGS grpflags;
struct N_CUSTOMERGRPFLAGS* pgrpflags;
struct N_CUSTGRPFLAGTYPES flagtypes;
struct N_CUSTGRPFLAGTYPES* pflagtypes;
struct N_CUSTOMERGROUP custgroup;
struct N_CUSTOMERGROUP* pcustgroup;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
void WriteLogInfo( char *error_msg, char mld, int rc );
int StartLoadTables			( char *error_msg);
int PrepareLoadTables		( char *error_msg);
int SetNotUpdated			( char *error_msg);
int SetNotUpdatedCustGrp	( char *error_msg);
int SetNotUpdatedGrpFlags	( char *error_msg);
int SetNotUpdatedFlagTypes	( char *error_msg);
int DelNotUpdated			( char *error_msg);
int DelNotUpdatedCustGrp	( char *error_msg);
int DelNotUpdatedGrpFlags	( char *error_msg);
int DelNotUpdatedFlagTypes	( char *error_msg);
int AfterLoadTables			( char *error_msg);
int PrepareReadCustGrp		( char *error_msg);
int PrepareReadGrpFlags		( char *error_msg);
int PrepareReadFlagTypes	( char *error_msg);
int PrepareLoadCustGrp		( char *error_msg);
int PrepareLoadGrpFlags		( char *error_msg);
int PrepareLoadFlagTypes	( char *error_msg);
int LoadCustGrp				( char *error_msg);
int LoadGrpFlags			( char *error_msg);
int LoadFlagTypes			( char *error_msg);
int AfterLoadCustGrp		( char *error_msg);
int AfterLoadGrpFlags		( char *error_msg);
int AfterLoadFlagTypes		( char *error_msg);
int CloseDatabase			( void );

/***** MAIN *****************************************************************/

int main( int argc, char **argv  )
{
	char  error_msg[181];
	char  *schalter;
	int   i;
	char  *fun = "Main";
	char  *LOG_FILE = "wws.log";
	char  *LOG_PATH;
	char  logpath[256 + 1];
	int   rc;
	int   status = 0;
	char  start_msg[81];

	sprintf(indatenbank,"%s",INDATABASE);
	sprintf(outdatenbank,"%s",OUTDATABASE);
     
	strcpy(start_msg, "gestartet mit:");
	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-dbin" ) )
		{
			strcat(start_msg, " -dbin");
			i++;
			sprintf( indatenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-dbout" ) )
		{
			strcat(start_msg, " -dbout");
			i++;
			sprintf( outdatenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-de" ) )
		{
			strcat(start_msg, " -de");
			Germany = 1;
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
		else
		{
			printf( "  usage: %s\n\t"
				" { -dbin datenbankname <Datenbankname Eingabe> }\n\t"
				" { -dbout datenbankname <Datenbankname Ausgabe> }\n\t"
				,argv[0] );
			return 1;
		}
	}

	exec sql database :outdatenbank;
	ERROR_MSG( "Fehler oeffnen DB" )

	exec sql set lock mode to wait 20;
	ERROR_MSG( "Set LockMode to Wait" )

	exec sql set isolation to dirty read;
	ERROR_MSG( "Set Isolation to Dirty Read" )

	PrintMsg( fun, start_msg, HINW, 0 );
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	if ( ( rc = StartLoadTables( error_msg ) ) != 0 )
	{
		PrintMsg( fun, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	PrintMsg( fun, "korrekt beendet", HINW, rc );
	return 0;   
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc = OK;

	if(!Germany)
	{
		if ( ( rc = PrepareReadCustGrp( error_msg ) ) < 0 ) return rc;
	}
	if ( ( rc = PrepareReadGrpFlags( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareReadFlagTypes( error_msg ) ) < 0 ) return rc;
	if(!Germany)
	{
		if ( ( rc = PrepareLoadCustGrp( error_msg ) ) < 0 ) return rc;
	}
	if ( ( rc = PrepareLoadGrpFlags( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLoadFlagTypes( error_msg ) ) < 0 ) return rc;

	return OK;
}

/*** PREPARE-LESE-KUNDENGRUPPEN ************************************************/

int PrepareReadCustGrp( char *error_msg )
{
	char *fun = "PrepareReadCustGrp";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select '0'," );
	strcat( str, "CUSTOMERGROUPNO," );
	strcat( str, "NAME," );
	strcat( str, "SALES_RESTR_PH," );
	strcat( str, "BLOCK_FLAG," );
	strcat( str, "BASISNATRA_FLAG," );
	strcat( str, "'1'" );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":ccustomergroup " );

	exec sql prepare dec_custgrp from :str;
	ERROR_MSG( "prepare dec_custgrp" )
	exec sql declare Cselcustgrp cursor with hold for dec_custgrp;
	
	return OK;      
}

/*** PREPARE-LESE-GRUPPEN-FLAGS ************************************************/

int PrepareReadGrpFlags( char *error_msg )
{
	char *fun = "PrepareReadGrpFlags";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select '0'," );
	strcat( str, "CUSTOMERGROUPNO," );
	strcat( str, "CUSTGRPFLAGTYPE," );
	strcat( str, "CUSTOMERGRPFLAG," );
	strcat( str, "'1'" );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":ccustomergrpflags " );

	exec sql prepare dec_grpflags from :str;
	ERROR_MSG( "prepare dec_grpflags" )
	exec sql declare Cselgrpflags cursor with hold for dec_grpflags;
	
	return OK;      
}

/*** PREPARE-LESE-FLAG-TYPES ************************************************/

int PrepareReadFlagTypes( char *error_msg )
{
	char *fun = "PrepareReadFlagTypes";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "select '0'," );
	strcat( str, "CUSTGRPFLAGTYPE," );
	strcat( str, "DESCRIPTION," );
	strcat( str, "INDEX_DKKGR," );
	strcat( str, "'1'" );
	strcat( str, " from  " );
	strcat( str, indatenbank );
	strcat( str, ":ccustgrpflagtypes " );

	exec sql prepare dec_flagtypes from :str;
	ERROR_MSG( "prepare dec_flagtypes" )
	exec sql declare Cselflagtypes cursor with hold for dec_flagtypes;
	
	return OK;      
}

/*** PREPARE-LADE-KUNDEN-GRUPPE ************************************************/

int PrepareLoadCustGrp( char *error_msg )
{
	char *fun = "PrepareLoadCustGrp";
	int  rc = OK;

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "update customergroup set " );
	strcat( str, CUSTOMERGROUP_UPDLISTE );
	strcat(str," where");
	strcat(str," BRANCHNO = ?");          
	strcat(str," and");          
	strcat(str," CUSTOMERGROUPNO = ?");          
	   
	exec sql prepare upd_custgroups from :str;
	ERROR_MSG( "prepare upd_custgroups" )

	if((rc = SetNotUpdatedCustGrp( error_msg )) != 0) return rc;

	return OK;
}

/*** PREPARE-LADE-GRUPPEN-FLAGS ************************************************/

int PrepareLoadGrpFlags( char *error_msg )
{
	char *fun = "PrepareLoadGrpFlags";
	int  rc = OK;

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "update customergrpflags set " );
	strcat( str, CUSTOMERGRPFLAGS_UPDLISTE );
	strcat(str," where");
	strcat(str," BRANCHNO = ?");          
	strcat(str," and");          
	strcat(str," CUSTOMERGROUPNO = ?");          
	strcat(str," and");          
	strcat(str," CUSTGRPFLAGTYPE = ?");          
	   
	exec sql prepare upd_grpflags from :str;
	ERROR_MSG( "prepare upd_grpflags" )

	if((rc = SetNotUpdatedGrpFlags( error_msg )) != 0) return rc;

	return OK;      
}

/*** PREPARE-LADE-FLAG-TYPES ************************************************/

int PrepareLoadFlagTypes( char *error_msg )
{
	char *fun = "PrepareLoadFlagTypes";
	int  rc = OK;

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str, "update custgrpflagtypes set " );
	strcat( str, CUSTGRPFLAGTYPES_UPDLISTE );
	strcat(str," where");
	strcat(str," BRANCHNO = ?");          
	strcat(str," and");          
	strcat(str," CUSTGRPFLAGTYPE = ?");          
	   
	exec sql prepare upd_flagtypes from :str;
	ERROR_MSG( "prepare upd_flagtypes" )

	if((rc = SetNotUpdatedFlagTypes( error_msg )) != 0) return rc;

	return OK;      
}
 
/***** SETZEN KENNZEICHEN NOCH NICHT GEAENDERT KUNDEN-GRUPPE************************************/

int SetNotUpdatedCustGrp( char *error_msg)
{
	char *fun = "SetNotUpdatedCustGrp";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str,"select upd_flag from customergroup ");
	strcat(str," for update");

	EXEC SQL PREPARE sel_updcustgrp FROM :str;
	ERROR_MSG( "prepare sel_updcustgrp" )
	exec sql declare CUpdcustgrp Cursor with hold for sel_updcustgrp;
	 
	strcpy( str, "update customergroup set upd_flag = '0' " );
	strcat( str, "where current of CUpdcustgrp " );
	
	exec sql prepare set_custgrp from :str;
	ERROR_MSG( "prepare set_custgrp" )

	exec sql open CUpdcustgrp;
    ERROR_MSG( "open CUpdcustgrp" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CUpdcustgrp;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CUpdcustgrp" )
		
		exec sql execute set_custgrp;
		ERROR_MSG( "execute set_custgrp" )
	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close CUpdcustgrp;
    ERROR_MSG( "close CUpdcustgrp" )

	return OK;
}
 
/***** SETZEN KENNZEICHEN NOCH NICHT GEAENDERT GRUPPEN-FLAGS************************************/

int SetNotUpdatedGrpFlags( char *error_msg)
{
	char *fun = "SetNotUpdatedGrpFlags";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str,"select upd_flag from customergrpflags ");
	strcat(str," for update");

	EXEC SQL PREPARE sel_updgrpflags FROM :str;
	ERROR_MSG( "prepare sel_updgrpflags" )
	exec sql declare CUpdgrpflags Cursor with hold for sel_updgrpflags;
	 
	strcpy( str, "update customergrpflags set upd_flag = '0' " );
	strcat( str, "where current of CUpdgrpflags " );
	
	exec sql prepare set_grpflags from :str;
	ERROR_MSG( "prepare set_grpflags" )

	exec sql open CUpdgrpflags;
    ERROR_MSG( "open CUpdgrpflags" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CUpdgrpflags;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CUpdgrpflags" )
		
		exec sql execute set_grpflags;
		ERROR_MSG( "execute set_grpflags" )
	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close CUpdgrpflags;
    ERROR_MSG( "close CUpdgrpflags" )

	return OK;
}
 
/***** SETZEN KENNZEICHEN NOCH NICHT GEAENDERT FLAG-TYPES************************************/

int SetNotUpdatedFlagTypes( char *error_msg)
{
	char *fun = "SetNotUpdatedFlagTypes";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str,"select upd_flag from custgrpflagtypes ");
	strcat(str," for update");

	EXEC SQL PREPARE sel_updflagtypes FROM :str;
	ERROR_MSG( "prepare sel_updflagtypes" )
	exec sql declare CUpdflagtypes Cursor with hold for sel_updflagtypes;
	 
	strcpy( str, "update custgrpflagtypes set upd_flag = '0' " );
	strcat( str, "where current of CUpdflagtypes " );
	
	exec sql prepare set_flagtypes from :str;
	ERROR_MSG( "prepare set_flagtypes" )

	exec sql open CUpdflagtypes;
    ERROR_MSG( "open CUpdflagtypes" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CUpdflagtypes;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CUpdflagtypes" )
		
		exec sql execute set_flagtypes;
		ERROR_MSG( "execute set_flagtypes" )
	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close CUpdflagtypes;
    ERROR_MSG( "close CUpdflagtypes" )

	return OK;
}
 
/***** STARTE DAS LADEN DER KUNDEN-GRUPPEN UND -FLAGS ************************************/

int StartLoadTables( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  ende = NO;
	char *fun = "StartLoadTables";
   
	if(!Germany)
	{
		if ( ( rc = LoadCustGrp( error_msg ) ) < 0 )
		{
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
	}
   
	if ( ( rc = LoadGrpFlags( error_msg ) ) < 0 )
	{
		PrintMsg( fun, error_msg, FEHL, ERROR );
		return ERROR;
	}
   
	if ( ( rc = LoadFlagTypes( error_msg ) ) < 0 )
	{
		PrintMsg( fun, error_msg, FEHL, ERROR );
		return ERROR;
	}
	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}
 
/***** LADEN DER KUNDEN-GRUPPEN ************************************/

int LoadCustGrp( char *error_msg)
{
	int  zaehler = 0;
	int  countInscustgroup = 0;
	int  countUpdcustgroup = 0;
	int  rc = OK;
	char *fun = "LoadCustGrp";

	pcustgroup = &custgroup;

	exec sql open Cselcustgrp;
	ERROR_MSG( "open Cselcustgrp" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work1" )

	for ( ;; )
	{
		exec sql fetch Cselcustgrp into :custgroup;
		ERROR_MSG( "fetch Cselcustgrp" )
		if(NOTFOUND) break;

		EXEC SQL EXECUTE upd_custgroups USING CUSTOMERGROUP_ZEIGER(pcustgroup)
											,:custgroup.BRANCHNO
											,:custgroup.CUSTOMERGROUPNO;
		ERROR_MSG( "upd  custgroups" )

		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
		    exec sql insert into customergroup (CUSTOMERGROUP_LISTE)
								values (CUSTOMERGROUP_ZEIGER(pcustgroup));
			ERROR_MSG( "ins  custgroups" )
			countInscustgroup++;
		}
		else
		{
			countUpdcustgroup++;
		}

		if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work2" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work2" )
        }

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work1" )

	sprintf( error_msg, "Rows updated/inserted %d/%d", countUpdcustgroup,countInscustgroup );
	PrintMsg( fun, error_msg, HINW, OK );

	return rc;
}
 
/***** LADEN DER GRUPPEN-FLAGS ************************************/

int LoadGrpFlags( char *error_msg)
{
	int  zaehler = 0;
	int  countInsgrpflags = 0;
	int  countUpdgrpflags = 0;
	int  rc = OK;
	char *fun = "LoadGrpFlags";

	pgrpflags = &grpflags;
   
	exec sql open Cselgrpflags;
	ERROR_MSG( "open Cselgrpflags" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work1" )

	for ( ;; )
	{
		exec sql fetch Cselgrpflags into :grpflags;
		ERROR_MSG( "fetch Cselgrpflags" )
		if(NOTFOUND) break;

		EXEC SQL EXECUTE upd_grpflags USING CUSTOMERGRPFLAGS_ZEIGER(pgrpflags)
										,:grpflags.BRANCHNO
										,:grpflags.CUSTOMERGROUPNO
										,:grpflags.CUSTGRPFLAGTYPE;
		ERROR_MSG( "upd  customergrpflags" )

		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
		    exec sql insert into customergrpflags (CUSTOMERGRPFLAGS_LISTE)
								values (CUSTOMERGRPFLAGS_ZEIGER(pgrpflags));
			ERROR_MSG( "ins  customergrpflags" )
			countInsgrpflags++;
		}
		else
		{
			countUpdgrpflags++;
		}

		if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work2" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work2" )
        }

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work1" )

	sprintf( error_msg, "Rows updated/inserted %d/%d", countUpdgrpflags,countInsgrpflags );
	PrintMsg( fun, error_msg, HINW, OK );

	return rc;
}
 
/***** LADEN DER FLAG-TYPES ************************************/

int LoadFlagTypes( char *error_msg)
{
	int  zaehler = 0;
	int  countInsflagtypes = 0;
	int  countUpdflagtypes = 0;
	int  rc = OK;
	char *fun = "LoadFlagTypes";

	pflagtypes = &flagtypes;
   
	exec sql open Cselflagtypes;
	ERROR_MSG( "open Cselflagtypes" )

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work1" )

	for ( ;; )
	{
		exec sql fetch Cselflagtypes into CUSTGRPFLAGTYPES_ZEIGER(pflagtypes);
		ERROR_MSG( "fetch Cselflagtypes" )
		if(NOTFOUND) break;

		EXEC SQL EXECUTE upd_flagtypes USING CUSTGRPFLAGTYPES_ZEIGER(pflagtypes)
										,:flagtypes.BRANCHNO
										,:flagtypes.CUSTGRPFLAGTYPE;
		ERROR_MSG( "upd  custgrpflagtypes" )

		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
		    exec sql insert into custgrpflagtypes (CUSTGRPFLAGTYPES_LISTE)
								values (CUSTGRPFLAGTYPES_ZEIGER(pflagtypes));
			ERROR_MSG( "ins  custgrpflagtypes" )
			countInsflagtypes++;
		}
		else
		{
			countUpdflagtypes++;
		}

		if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work2" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work2" )
        }

	}      /* ende for */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work1" )

	sprintf( error_msg, "Rows updated/inserted %d/%d", countUpdflagtypes,countInsflagtypes );
	PrintMsg( fun, error_msg, HINW, OK );

	return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc = OK;
	if(!Germany)
	{
		if ( (rc = AfterLoadCustGrp(error_msg)) < 0) return rc;
	}
	if ( (rc = AfterLoadGrpFlags(error_msg)) < 0) return rc;
	if ( (rc = AfterLoadFlagTypes(error_msg)) < 0) return rc;

	return OK;
}

/***** AFTER-LADE-KUNDEN-GRUPPE *********************************************/

int AfterLoadCustGrp( char *error_msg )
{
	int  rc = OK;
	if((rc = DelNotUpdatedCustGrp( error_msg )) != 0) return rc;
	return OK;
}

/***** AFTER-LADE-GRUPPEN-FLAGS *********************************************/

int AfterLoadGrpFlags( char *error_msg )
{
	int  rc = OK;
	if((rc = DelNotUpdatedGrpFlags( error_msg )) != 0) return rc;
	return OK;
}

/***** AFTER-LADE-FLAG-TYPES *********************************************/

int AfterLoadFlagTypes( char *error_msg )
{
	int  rc = OK;
	if((rc = DelNotUpdatedFlagTypes( error_msg )) != 0) return rc;
	return OK;
}
 
/***** LOESCHEN NICHT GEAENDERT KUNDEN-GRUPPE************************************/

int DelNotUpdatedCustGrp( char *error_msg)
{
	char *fun = "DelNotUpdatedCustGrp";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str,"select upd_flag from customergroup ");
	strcat(str,"where upd_flag = '0' ");
	strcat(str,"for update");

	EXEC SQL PREPARE sel_delcustgrp FROM :str;
	ERROR_MSG( "prepare sel_delcustgrp" )
	exec sql declare CDelcustgrp Cursor with hold for sel_delcustgrp;
	 
	strcpy( str, "delete from customergroup " );
	strcat( str, "where current of CUpdcustgrp " );
	
	exec sql prepare del_custgrp from :str;
	ERROR_MSG( "prepare del_custgrp" )

	exec sql open CDelcustgrp;
    ERROR_MSG( "open CDelcustgrp" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CDelcustgrp;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CDelcustgrp" )
		
		exec sql execute del_custgrp;
		ERROR_MSG( "execute del_custgrp" )
	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close CDelcustgrp;
    ERROR_MSG( "close CDelcustgrp" )

	return OK;
}
 
/***** LOESCHEN NICHT GEAENDERT GRUPPEN-FLAGS************************************/

int DelNotUpdatedGrpFlags( char *error_msg)
{
	char *fun = "DelNotUpdatedGrpFlags";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str,"select upd_flag from customergrpflags ");
	strcat(str,"where upd_flag = '0' ");
	strcat(str,"for update");

	EXEC SQL PREPARE sel_delgrpflags FROM :str;
	ERROR_MSG( "prepare sel_delgrpflags" )
	exec sql declare CDelgrpflags Cursor with hold for sel_delgrpflags;
	 
	strcpy( str, "delete from customergrpflags " );
	strcat( str, "where current of CDelgrpflags " );
	
	exec sql prepare del_grpflags from :str;
	ERROR_MSG( "prepare del_grpflags" )

	exec sql open CDelgrpflags;
    ERROR_MSG( "open CDelgrpflags" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CDelgrpflags;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CDelgrpflags" )
		
		exec sql execute del_grpflags;
		ERROR_MSG( "execute del_grpflags" )
	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close CDelgrpflags;
    ERROR_MSG( "close CDelgrpflags" )

	return OK;
}
 
/***** LOESCHEN NICHT GEAENDERT FLAG-TYPES************************************/

int DelNotUpdatedFlagTypes( char *error_msg)
{
	char *fun = "DelNotUpdatedFlagTypes";

	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy(str,"select upd_flag from custgrpflagtypes ");
	strcat(str,"where upd_flag = '0' ");
	strcat(str," for update");

	EXEC SQL PREPARE sel_delflagtypes FROM :str;
	ERROR_MSG( "prepare sel_delflagtypes" )
	exec sql declare CDelflagtypes Cursor with hold for sel_delflagtypes;
	 
	strcpy( str, "delete from custgrpflagtypes " );
	strcat( str, "where current of CDelflagtypes " );
	
	exec sql prepare del_flagtypes from :str;
	ERROR_MSG( "prepare del_flagtypes" )

	exec sql open CDelflagtypes;
    ERROR_MSG( "open CDelflagtypes" )
	EXEC SQL begin work;
	ERROR_MSG( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG( "begin Work:" )
		}
		exec sql fetch CDelflagtypes;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG( "fetch CDelflagtypes" )
		
		exec sql execute del_flagtypes;
		ERROR_MSG( "execute del_flagtypes" )
	}
	EXEC SQL commit work;
	ERROR_MSG( "Commit Work0:" )

	exec sql close CDelflagtypes;
    ERROR_MSG( "close CDelflagtypes" )

	return OK;
}

/***** PRINT-MSG ************************************************************/

void PrintMsg( char *fun, char *error_msg, char mld, int rc )
{
	FILE *fp;
	struct tm *localtime();
	struct tm *zeit;
	long hour1;
	pid_t pid;
	long time();
	char logFile[L_TEXT];
    char *env;
 
	if ( rc > INSERT )
		return;
   
	pid = getpid();
	hour1 = time( &hour1 );
	zeit  = localtime( &hour1 );
   
/*	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) );	*/
	env = getenv( "LOG_PATH" );
	if ( env == NULL )
		env = ".";
	sprintf( logFile, "%s/wws.log", env );

	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
		return;
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s %s\n",
		mld,
		99,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"loadcustgroups",
		fun,
		error_msg );

	fclose(fp);
}

/***** CLOSE-DATABASE *******************************************************/

int CloseDatabase( void )
{
	char error_msg[L_TEXT];
	char *fun = "CloseDatabase";

	exec sql close database;
	ERROR_MSG( "Close DB" )
  
	return OK;
}
/***** ENDE *****************************************************************/

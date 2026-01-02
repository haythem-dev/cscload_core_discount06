/* loadcstpharmgrp.cxx */

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadcstpharmgrp"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "customerpharmacygr.h"
#include "dkkeg.h"
#include "pplib/allg.h"
#include "errno.h"
EXEC SQL include sqlca;

/* #undef NULL */

#define P_DKKEG           "/transfer/pos/data/UCATPH1/DKKEG.P"
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
#define BLANC            ' '
#define STR_NULL         "+000000000000000"
#define SQLCODE            sqlca.sqlcode

#define DATABASE "phosix"
#define ERROR_MSG2(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                   sqlca.sqlcode, sqlca.sqlerrd[1],sqlca.sqlerrm ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return sqlca.sqlcode; }


 /***** GLOBALE **************************************************************/

 FILE *dkkegdat;
 char pfaddkkeg[81];
 char log_file [300 + 1];
 int debug_enabled   = NO;
 short haus = 0;
 char chaus[3];
	
	EXEC SQL BEGIN DECLARE SECTION;
	char datenbank[60];
	EXEC SQL END DECLARE SECTION;

 
 /***** DECLARATION **********************************************************/
 int main( int, char ** );
 void PrintMsg( char *fun, char *error_msg, char mld, int rc );
 void WriteLogInfo( char *error_msg, char mld, int rc );
 int StarteLoadCstPGrp( char *error_msg );
 int PrepareLoadCustomerPharmacyGr( char *error_msg);
 int LadeCustomerPharmacyGr(struct O_DKKEG *, char *);
 int AfterLoadCustomerPharmacyGr( char *error_msg);
 int SetNotUpdatedPharmacyGr( char *error_msg);
 int DelNotUpdatedPharmacyGr( char *error_msg);
 
 /***** MAIN *****************************************************************/

 int main( int argc, char **argv  )
 {
   char 	error_msg[81];
   char 	*schalter;
   int 		i;
   int 		skip;
   int 		datum = 0;
   int 		rc = 0;
   char 	*fun = "Main";
   int		tourtag = -1; /* Tag, der aus DKTUR geladen wird */
   char *LOG_FILE = "wws.log";
   char *LOG_PATH;
   char logpath[256+1];

	sprintf(datenbank,"%s",DATABASE);
     
   setbuf( stdout, 0 );              /* printf sofort */
   skip = NO;
   for ( i = 1; i < argc; i++ )
   {
     	if ( skip )
	  	{
	  		skip = NO;
	  		continue;
	  	}
       	schalter = argv[i];
       	if ( !strcmp( schalter, "-dg" ) )
	   		debug_enabled = YES;
		else if ( !strcmp( schalter, "-file" ) )
		{
			i++;
			sprintf( pfaddkkeg, "%s", argv[i] );
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			sprintf( datenbank, "%s", argv[i] );
		}
		else if ( !strcmp( schalter, "-vz" ) )
		{
			haus = atoi(argv[i + 1]);
			skip = YES;
		}
  		else if ( !strcmp( schalter, "-la" ) )
	   		;
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return OK;
		}
        else
	  	{
	  		skip = ERROR;
	  		break;
	  	}
  	}                                            
   if ( argc == 1 || skip == ERROR )
	      {
      printf( "  usage: %s\n\t"
	      " { -dg <Debugging> }\n\t"
		  " { -db datenbankname <Datenbankname> }\n\t"
		  " { -vz 05 <Filialnr> }\n\t"
		  " { -file dateiname <Name der Eingabedatei> }\n\t"
	      " [ -la]\n\t"
		  , argv[0] );
      return 2;
      }
	
	sprintf(chaus,"%d",haus);

   if ((LOG_PATH = getenv("LOG_PATH")) == (char *)0)
   {
	   strcpy(logpath, ".");
   }
   else
   {
	   strcpy(logpath, LOG_PATH);
   }
	sprintf(log_file, "%s/%s", logpath, LOG_FILE);

   if ( (rc = StarteLoadCstPGrp(error_msg)) != 0 )
   {
	  PrintMsg( fun, "mit Fehler beendet", FEHL, 0 );
      return rc;
   }
 
   PrintMsg( fun, "ENDE", HINW, 0 );
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

   if ( rc > INSERT )
      return;

   pid = getpid();
   hour1 = time( &hour1 );
   zeit  = localtime( &hour1 );
   fp = fopen( log_file, "a" );
   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s",
	    mld,
	    haus,
		zeit->tm_mday,
        zeit->tm_mon + 1,
        (zeit->tm_year+1900)%100,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
	    pid,
	    "loadcstpharmgrp",
	    fun );

   fprintf(fp," %s\n", error_msg );
   fclose(fp);
}

/***** STARTE DAS LADEN DER EINKAUFSGRUPPEN *************************************/

 int StarteLoadCstPGrp(char *error_msg )
{
	int zaehler, rc;
	int ind;
	char *fun = "StarteLoadCstPGrp";
	
	EXEC SQL BEGIN DECLARE SECTION;
	short int filialnr;
	EXEC SQL END DECLARE SECTION;

	char msg[80];
	char szHaus[3];
	struct O_DKKEG keg;
	static const int DKKEG_LEN = sizeof(keg);
	char satz[1000];
    int len = 100;
	
   	EXEC SQL set lock mode to wait 20;
	ERROR_MSG2("lock mode:")
   	EXEC SQL database :datenbank;
	ERROR_MSG2("database:")
   	EXEC SQL set isolation to dirty read;
	ERROR_MSG2("set isolation:")
/*   	if ((sqlca.sqlcode != 0) && (sqlca.sqlcode != -256))
    {
      	sprintf (error_msg, "set iso: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 	  	PrintMsg( fun, error_msg, FEHL, -1 );
      	return -1;
    }
*/	
	if ( haus == 0 )  /* filialnr wurde nicht über schalter -lf bekanntgegeben (standard)*/
	{
		exec sql select filialnr into :filialnr from filiale;
		ERROR_MSG2("select filiale")
		haus = filialnr;
	}

	filialnr = haus;

	sprintf( msg, "started " );
	PrintMsg( "Main", msg, HINW, 0 );

	if( (rc = PrepareLoadCustomerPharmacyGr(error_msg)) != 0 )
	{
		return rc;	
	}
	
	if ( ( dkkegdat = fopen( pfaddkkeg, "r" ) ) == NULL )
	{
		PrintMsg( fun, pfaddkkeg, FEHL, 0 );
		PrintMsg( fun, "DKKEG nicht vorhanden", FEHL, 0 );
		return -1;
	}

	EXEC SQL begin work;
	ERROR_MSG2("begin work1:")
	for(zaehler=0 ;;zaehler++ )
	{
		if (zaehler%500 == 0)
		{
			EXEC SQL commit work;
			ERROR_MSG2("commit work;")
			EXEC SQL begin work;
			ERROR_MSG2("begin work2:")
		}
		if (zaehler%1000 == 0)
		{
		   	DEBUG_SECTION
			fprintf(stderr,"%d Saetze geladen\n",zaehler);
   			END_DEBUG_SECTION
		}

		if(fread( (	struct O_DKKEG*) &keg ,DKKEG_LEN+1, 1 , dkkegdat ) == 0)
        {
		   	DEBUG_SECTION
			fprintf(stderr,"%d Saetze gelesen\n",zaehler);
   			END_DEBUG_SECTION
			break;
	 	}
	   	DEBUG_SECTION
		fprintf(stderr,"%s\n",&keg);
		END_DEBUG_SECTION
				
		/* neue Tabelle schreiben */

		if(keg.KEGAKT[0] != 'J') continue;	/* nicht aktive ueberlesen */
		
		sprintf( szHaus, "%02d", haus );
		if(strncmp(keg.KEGFIL,szHaus,L_DKKEG_KEGFIL))
		{
			if(!strncmp(szHaus,"49",L_DKKEG_KEGFIL))
			{
				if(!strncmp(keg.KEGFIL,"48",L_DKKEG_KEGFIL))
				{
					keg.KEGFIL[1] = '9';
				}
			}
			else
			{
				continue;
			}
		}
		
		if ( (rc = LadeCustomerPharmacyGr(&keg, error_msg)) < 0) return rc;
	}

	EXEC SQL commit work;
	ERROR_MSG2("commit work2:")

	sprintf(error_msg," Saetze gelesen %d",zaehler);
 	PrintMsg( fun, error_msg, HINW, -1 );

	fclose( dkkegdat);

	if( (rc = AfterLoadCustomerPharmacyGr(error_msg)) != 0 )
	{
		return rc;	
	}

	return OK;
}

int PrepareLoadCustomerPharmacyGr(char *error_msg)
{
	char *fun = "PrepareLoadCustomerPharmacyGr";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"insert into customerpharmacygr (");
	strcat(str,"BRANCHNO,");
	strcat(str,"CUSTOMERNO,");
	strcat(str,"PHARMACYGROUPID,");          
	strcat(str,"RANKING,");
	strcat(str,"UPD_FLAG");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,'0','1' )");

	EXEC SQL PREPARE ins_pharmgrp FROM :str;
	ERROR_MSG2( "prepare ins_pharmgrp " );

	strcpy(str,"select upd_flag ");
	strcat(str,"from customerpharmacygr ");          
	strcat(str,"where ");
	strcat(str,"BRANCHNO = ? ");
	strcat(str,"and CUSTOMERNO = ? ");          
	strcat(str,"and PHARMACYGROUPID = ? ");          
	strcat(str,"for update " );

	EXEC SQL PREPARE sel_pharmgrp FROM :str;
	ERROR_MSG2( "prepare sel_pharmgrp " );
	exec sql declare Cselpharmgrp cursor with hold for sel_pharmgrp;

	strcpy(str,"update customerpharmacygr set ");
	strcat(str,"RANKING = '0' ");
	strcat(str,",UPD_FLAG = '1' ");
	strcat(str,"where current of Cselpharmgrp " );

	EXEC SQL PREPARE upd_pharmgrp FROM :str;
	ERROR_MSG2( "prepare upd_pharmgrp" )

	if((rc = SetNotUpdatedPharmacyGr( error_msg )) != 0) return rc;

	return 0;
}

 
int LadeCustomerPharmacyGr(struct O_DKKEG *eg, char *error_msg)
{
	char *fun = "LadeCustomerPharmacyGr";

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKEG *a;
	char cEKG[4];
	EXEC SQL END DECLARE SECTION;

	a = eg;

	sprintf(cEKG,"%03.3s",a->KEGEGR+1);

	EXEC SQL open Cselpharmgrp USING
					:a->KEGFIL,
					:a->KEGIDF,
					:cEKG
					;
	ERROR_MSG2("open Cselpharmgrp:")

	EXEC SQL fetch Cselpharmgrp;
	ERROR_MSG2("fetch Cselpharmgrp:")
	if ( sqlca.sqlcode != 100 )
	{
		EXEC SQL EXECUTE upd_pharmgrp;
		ERROR_MSG2("upd_pharmgrp:")
	}
	else
	{
		EXEC SQL EXECUTE ins_pharmgrp using
					:a->KEGFIL,
					:a->KEGIDF,
					:cEKG
					;
		ERROR_MSG2("ins_pharmgrp:")
	}

	return OK;
}

int AfterLoadCustomerPharmacyGr( char *error_msg)
{
	int rc = 0;
	if((rc = DelNotUpdatedPharmacyGr( error_msg )) != 0) return rc;
	return OK;
}

int SetNotUpdatedPharmacyGr( char *error_msg)
{
	char *fun = "SetNotUpdatedPharmacyGr";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select upd_flag from customerpharmacygr where branchno = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_grp FROM :str;
	ERROR_MSG2( "prepare sel_grp" )
	exec sql declare CGrp Cursor with hold for sel_grp;
	 
	strcpy( str, "update customerpharmacygr set upd_flag = '0' " );
	strcat( str, "where current of CGrp " );
	
	exec sql prepare set_pharmgrp from :str;
	ERROR_MSG2( "prepare set_pharmgrp" )

	exec sql open CGrp using :filialnr;
    ERROR_MSG2( "open CGrp" )

    exec sql begin work;
	ERROR_MSG2( "begin Work:" )
	for(comz=0 ;;comz++ )
	{
		if (comz%200 == 0)
		{
			exec sql commit work;
			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch CGrp;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CGrp" )
		
		exec sql execute set_pharmgrp;
		ERROR_MSG2( "execute set_pharmgrp" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close CGrp ;
    ERROR_MSG2( "close CGrp" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze gesetzt\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int DelNotUpdatedPharmacyGr( char *error_msg)
{
	char *fun = "DelNotUpdatedPharmacyGr";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select upd_flag from customerpharmacygr");
	strcat(str," where upd_flag = '0'");
	strcat(str," and branchno = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_grp2 FROM :str;
	ERROR_MSG2( "prepare sel_grp2" )
	exec sql declare DelGrp Cursor with hold for sel_grp2;

	strcpy( str, "delete from customerpharmacygr " );
	strcat( str, "where current of DelGrp " );
	
	exec sql prepare del_grp from :str;
	ERROR_MSG2( "prepare del_grp" )

	exec sql open DelGrp using :filialnr;
    ERROR_MSG2( "open DelGrp" )

    exec sql begin work;
	ERROR_MSG2( "begin Work:" )
	for(comz=0 ;;comz++ )
	{
		if (comz%200 == 0)
		{
			exec sql commit work;
			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch DelGrp;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelGrp" )
		
		exec sql execute del_grp;
		ERROR_MSG2( "execute del_grp" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close DelGrp ;
    ERROR_MSG2( "close DelGrp" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze geloescht\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

/***** ENDE *****************************************************************/

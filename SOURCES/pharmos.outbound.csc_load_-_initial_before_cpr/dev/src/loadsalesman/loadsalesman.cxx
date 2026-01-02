/* loadsalesman.cxx */

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadsalesman"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "dkvtr.h"
#include "salesman.h"
#include "errno.h"
EXEC SQL include sqlca;

#undef NULL

#define P_DKVTR           "/transfer/ksc/data/DKVTR.P"
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

#define DATABASE "phosix"
#define ERROR_MSG2(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                   sqlca.sqlcode, sqlca.sqlerrd[1],sqlca.sqlerrm ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }


 /***** GLOBALE **************************************************************/

 FILE *dkvtrdat;
 char pfaddkvtr[81];
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
 int StartLoadSalesman(char *error_msg );
 int PrepareLoadSalesman(char *error_msg);
 int LoadSalesman(struct O_DKVTR *vtr, char *error_msg);
 int DeleteSalesman(char *error_msg);
 
 /***** MAIN *****************************************************************/

 int main( int argc, char **argv  )
 {
   char 	error_msg[81];
   char 	*schalter;
   int 		i;
   int 		skip;
   int 		datum = 0;
   char 	*fun = "Main";
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
		if ( !strcmp( schalter, "-file" ) )
		{
			i++;
			sprintf( pfaddkvtr, "%s", argv[i] );
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			sprintf( datenbank, "%s", argv[i] );
		}
		else if ( !strcmp( schalter, "-branchno" ) )
		{
			haus = atoi(argv[i + 1]);
			skip = YES;
		}
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
		  " { -db datenbankname <Datenbankname> }\n\t"
		  " { -branchno 05 <Filialnr> }\n\t"
		  " { -file dateiname <Name der Eingabedatei> }\n\t"
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

   if ( StartLoadSalesman( error_msg) != 0 )
   {
	  PrintMsg( fun, "mit Fehler beendet", FEHL, 0 );
      return 1;
   }
 
   PrintMsg( fun, "ENDE", HINW, 0 );
   return OK;
 }


/***** WriteLogInfo nur zum Aufruf von PrintMsg ******************************/

void WriteLogInfo( char *error_msg, char mld, int rc )
{
	PrintMsg( "loadroutes", error_msg, mld, rc );
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
	    "loadsalesman",
	    fun );

   fprintf(fp,"%s\n", error_msg );
   fclose(fp);
}

/***** STARTE DAS LADEN DER GVL TABELLE *************************************/

 int StartLoadSalesman( char *error_msg )
{
	int zaehler, rc;
	int ind;
	char *fun = "StartLoadSalesman";
	
	EXEC SQL BEGIN DECLARE SECTION;
	short int filialnr;
	char str[200];
	EXEC SQL END DECLARE SECTION;

	char msg[80];
	char szHaus[3];
	struct O_DKVTR vtr;
	static const int DKVTR_LEN = sizeof(vtr);
	char satz[1000];
    int len = 256;
	
   	EXEC SQL set lock mode to wait 20;
   	if (sqlca.sqlcode != 0)  /* Datenbankfehler */
    {
      	sprintf (error_msg, "lock: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 		PrintMsg( fun, error_msg, FEHL, -1 );
		return -1;
    }
   	EXEC SQL database :datenbank;
   	if (sqlca.sqlcode != 0)  /* Datenbankfehler */
    {
      	sprintf (error_msg, "database: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 	  	PrintMsg( fun, error_msg, FEHL, -1 );
      	return -1;
    }
   	EXEC SQL set isolation to dirty read;
   	if ((sqlca.sqlcode != 0) && (sqlca.sqlcode != -256))  /* Datenbankfehler */
    {
      	sprintf (error_msg, "set iso: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 	  	PrintMsg( fun, error_msg, FEHL, -1 );
      	return -1;
    }

	filialnr = haus;

	PrintMsg( "Main", "started ", HINW, 0 );

	if( (rc = DeleteSalesman(error_msg)) != 0 )
	{
		return rc;	
	}

	if( (rc = PrepareLoadSalesman(error_msg)) != 0 )
	{
		return rc;	
	}
	
	if ( ( dkvtrdat = fopen( pfaddkvtr, "r" ) ) == (char *)0 )
	{
		PrintMsg( fun, pfaddkvtr, FEHL, 0 );
		PrintMsg( fun, "DKVTR nicht vorhanden", FEHL, 0 );
		return -1;
	}

	EXEC SQL begin work;
    if (sqlca.sqlcode < 0 )
    {
    	sprintf(error_msg, "begin work1 %ld", sqlca.sqlcode);
 	  	PrintMsg( fun, error_msg, FEHL, -1 );
       	return -1;
    }
	for(zaehler=0 ;;zaehler++ )
	{
		if (zaehler%500 == 0)
		{
			EXEC SQL commit work;
    		if (sqlca.sqlcode < 0 )
    		{
    			sprintf(error_msg, "commit work %ld", sqlca.sqlcode);
 	  			PrintMsg( fun, error_msg, FEHL, -1 );
       			return -1;
    		}
			EXEC SQL begin work;
			if (sqlca.sqlcode < 0 )
    		{
    			sprintf(error_msg, "begin work2 %ld", sqlca.sqlcode);
 	  			PrintMsg( fun, error_msg, FEHL, -1 );
       			return -1;
    		}
		}
		if (zaehler%1000 == 0)
		{
		   	DEBUG_SECTION
			fprintf(stderr,"%d Saetze geladen\n",zaehler);
   			END_DEBUG_SECTION
		}

		if(fread( (	struct O_DKVTR*) &vtr ,DKVTR_LEN+1, 1 , dkvtrdat ) == 0)
        {
		   	DEBUG_SECTION
			fprintf(stderr,"%d Saetze gelesen\n",zaehler);
   			END_DEBUG_SECTION
			break;
	 	}
	   	DEBUG_SECTION
		fprintf(stderr,"%s\n",&vtr);
		END_DEBUG_SECTION
				
		/* neue Tabelle schreiben */
		
		if ( (rc = LoadSalesman(&vtr, error_msg)) < 0) return rc;
	}

	EXEC SQL commit work;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, "commit work2 %ld", sqlca.sqlcode);
		PrintMsg( fun, error_msg, FEHL, -1 );
		return -1;
	}

	sprintf(error_msg," Saetze gelesen %d",zaehler);
 	PrintMsg( fun, error_msg, HINW, -1 );

	fclose( dkvtrdat);

	return OK;
}

int PrepareLoadSalesman(char *error_msg)
{
	char *fun = "PrepareLoadSalesman";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"insert into salesman ( ");
	strcat(str, SALESMAN_PELISTE );          
	strcat(str," ) values ( ?, ?, ?, ?, ?, ?, ?, ?, ? )");

	EXEC SQL PREPARE ins_salesman FROM :str;
	ERROR_MSG2( "prepare ins_salesman " );

	return 0;
}
 
int LoadSalesman(struct O_DKVTR *vtr, char *error_msg)
{
	char *fun = "LoadSalesman";

	char huelse[80];

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKVTR *a;
	EXEC SQL END DECLARE SECTION;

	a = vtr;

	if(a->VTRKZA[0] == 'J' || a->VTRKZA[0] == '1')
		a->VTRKZA[0] = '1';
	else
		a->VTRKZA[0] = '0';

	if(a->VTRPWFAK[0] == 'J' || a->VTRPWFAK[0] == '1')
		a->VTRPWFAK[0] = '1';
	else
		a->VTRPWFAK[0] = '0';

	for(int i = 0;i < L_DKVTR_VTREMAIL;i++)
	{
		if(a->VTREMAIL[i] == ' ') break;
		if(a->VTREMAIL[i] == '§') a->VTREMAIL[i] = '@';
	}

   	EXEC SQL EXECUTE ins_salesman USING
			 :a->VTRFIL,
			 :a->VTRNUM,
			 :a->VTRNAME,
			 :a->VTRSTR,
			 :a->VTRORT,
			 :a->VTRPLZ,
			 :a->VTRKZA,
			 :a->VTRPWFAK,
			 :a->VTREMAIL;
	ERROR_MSG2( "insert Salesman:" )

	return OK;
}

int DeleteSalesman( char *error_msg)
{
	char *fun = "DeleteSalesman";

	EXEC SQL BEGIN DECLARE SECTION;
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

    exec sql begin work;
	ERROR_MSG2( "begin Work:" )

	EXEC SQL delete from salesman where branchno = :filialnr;
	ERROR_MSG2( "delete from salesman" )

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )

	return OK;
}

/***** ENDE *****************************************************************/

/* loadsctshort.cxx */

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadcstshort"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include "cstdiscountcont.h"
#include "dkksa.h"
EXEC SQL include sqlca;

#undef NULL

#define P_DKKSA           "/transfer/pos/data/UCATPH1/DKKSA.P"
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
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }


 /***** GLOBALE **************************************************************/

 FILE *dkksadat;
 char pfaddkksa[81];
 char log_file [300 + 1];
 int debug_enabled   = NO;
 int DateiNr = 0;                 /* XVSAM */
 char chaus[3];
 static int ins_z = 0;
 static int upd_z = 0;
	
	EXEC SQL BEGIN DECLARE SECTION;
	char datenbank[60];
	struct O_DKKSA ksa,*pksa;
	short haus = 0;
	EXEC SQL END DECLARE SECTION;

 
 /***** DECLARATION **********************************************************/
 int main( int, char ** );
 void PrintMsg( char *fun, char *error_msg, char mld, int rc );
 int StarteLoadShort(char *error_msg );
 int PrepareLoadShort(char *error_msg);
 int LadeShort(char *error_msg);
 int AfterLoadShort( char *error_msg);
 int DelNotUpdatedShort( char *error_msg);
 int SetNotUpdatedShort( char *error_msg);
 
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
       	if ( !strcmp( schalter, "-dg" ) )
	   		debug_enabled = YES;
		else if ( !strcmp( schalter, "-file" ) )
		{
			i++;
			sprintf( pfaddkksa, "%s", argv[i] );
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
		  , argv[0] );
      return 2;
      }
	
	sprintf(chaus,"%02d",haus);

   if ((LOG_PATH = getenv("LOG_PATH")) == (char *)0)
   {
	   strcpy(logpath, ".");
   }
   else
   {
	   strcpy(logpath, LOG_PATH);
   }
	sprintf(log_file, "%s/%s", logpath, LOG_FILE);

   if ( StarteLoadShort(error_msg) != 0 )
   {
	  PrintMsg( fun, "mit Fehler beendet", FEHL, 0 );
      return 1;
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
   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.12s %s",
	    mld,
	    haus,
		zeit->tm_mday,
        zeit->tm_mon + 1,
        (zeit->tm_year+1900)%100,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
	    pid,
	    "loadcstshort",
	    fun );

   fprintf(fp,"%s\n", error_msg );
   fclose(fp);
}

/***** STARTE DAS LADEN DER TOUREN-TABELLE *************************************/

 int StarteLoadShort(char *error_msg )
{
	int zaehler, rc;
	int ind;
	char *fun = "StarteLoadShort";
	
	EXEC SQL BEGIN DECLARE SECTION;
	char str[200];
	EXEC SQL END DECLARE SECTION;

	char msg[80];
	static const int DKKSA_LEN = sizeof(ksa);
	char satz[1000];
    int len = 100;
	
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

	PrintMsg( "Main", "gestartet", HINW, 0 );

	if( (rc = PrepareLoadShort(error_msg)) != 0 )
	{
		return rc;	
	}
	
	if ( ( dkksadat = fopen( pfaddkksa, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( fun, pfaddkksa, FEHL, 0 );
		PrintMsg( fun, "DKKSA nicht vorhanden", FEHL, 0 );
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

		if(fread( (	struct O_DKKSA*) &ksa ,DKKSA_LEN+1, 1 , dkksadat ) == 0)
        {
		   	DEBUG_SECTION
			fprintf(stderr,"%d Saetze gelesen\n",zaehler);
   			END_DEBUG_SECTION
			break;
	 	}
	   	DEBUG_SECTION
		fprintf(stderr,"%s\n",&ksa);
		END_DEBUG_SECTION
				
		/* neue Tabelle schreiben */
		
		if(strncmp(ksa.KSAFIL,chaus,L_DKKSA_KSAFIL))
		{
			continue;
		}
		
		if ( (rc = LadeShort(error_msg)) < 0) return rc;
	}

	EXEC SQL commit work;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, "commit work2 %ld", sqlca.sqlcode);
		PrintMsg( fun, error_msg, FEHL, -1 );
		return -1;
	}

	sprintf(error_msg," Saetze insert,update %d/%d",ins_z,upd_z);
 	PrintMsg( fun, error_msg, HINW, -1 );

	fclose( dkksadat);

	if( (rc = AfterLoadShort(error_msg)) != 0 )
	{
		return rc;	
	}

	return OK;
}

int PrepareLoadShort(char *error_msg)
{
	char *fun = "PrepareLoadShort";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	if ( (rc = SetNotUpdatedShort(error_msg)) < 0) return rc;

	strcpy(str,"select valuta_days ");
	strcat(str,"from cstdiscountcont ");          
	strcat(str,"where ");
	strcat(str,"BRANCHNO = ? ");          
	strcat(str,"and CUSTOMERNO = ? ");          
	strcat(str,"and ORDER_TYPE = ? ");          
	strcat(str,"and SUB_ORDER_TYPE = ? ");          
	strcat(str,"for update " );

	EXEC SQL PREPARE sel_short FROM :str;
	ERROR_MSG2( "prepare sel_short " );
	exec sql declare Cselshort cursor with hold for sel_short;

	strcpy(str,"update cstdiscountcont set ");
	strcat(str,"PAYMENT_TERM = ?, ");
	strcat(str,"VALUTA_DAYS = ?, ");
	strcat(str,"MIN_ORDER_VALUE = ?, ");
	strcat(str,"MIN_TUBES = ?, ");
	strcat(str,"LOSS_IN_DISCOUNT = ?, ");
	strcat(str,"UPD_FLAG = ? ");
	strcat(str,"where current of Cselshort " );

	EXEC SQL PREPARE upd_short FROM :str;
	ERROR_MSG2( "prepare upd_short" )

	strcpy(str,"insert into cstdiscountcont (");
	strcat( str, CSTDISCOUNTCONT_PELISTE );
	strcat( str, ",UPD_FLAG " );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) " );

	EXEC SQL PREPARE ins_short FROM :str;
	ERROR_MSG2( "prepare ins_short" )

	return 0;
}
 
int LadeShort(char *error_msg)
{
	int i;
	char *fun = "LadeShort";

	pksa = &ksa;

	for(i = 0;i < L_DKKSA_KSAABSCHL;i++)
	{
		if(pksa->KSAABSCHL[i] == ',') pksa->KSAABSCHL[i] = '.';
	}

	EXEC SQL open CselShort USING
						:pksa->KSAFIL,
						:pksa->KSAIDF,
						:pksa->KSAAART,
						:pksa->KSASAART
						;
	ERROR_MSG2( "open Cselshort" )
	EXEC SQL fetch Cselshort;
	ERROR_MSG2( "fetch Cselshort" )
	if ( sqlca.sqlcode == 100 )
	{
		EXEC SQL EXECUTE ins_short USING
			:pksa->KSAFIL,
			:pksa->KSAIDF,
			:pksa->KSAAART,
			:pksa->KSASAART,
			:pksa->KSAZBED,
			:pksa->KSAVALUTA,
			:pksa->KSAMAWERT,
			:pksa->KSAMWANNE,
			:pksa->KSAABSCHL,
			'1';
		ERROR_MSG2( "EXECUTE ins_short" )
		ins_z++;
	}
	else
	{
		EXEC SQL EXECUTE upd_short USING
			:pksa->KSAZBED,
			:pksa->KSAVALUTA,
			:pksa->KSAMAWERT,
			:pksa->KSAMWANNE,
			:pksa->KSAABSCHL,
			'1';
		ERROR_MSG2( "EXECUTE upd_short" )
		upd_z++;
	}
	return OK;
}
 
int AfterLoadShort( char *error_msg)
{
	int rc;
	if ( (rc = DelNotUpdatedShort(error_msg)) < 0) return rc;
	return OK;
}

int SetNotUpdatedShort( char *error_msg)
{
	char *fun = "SetNotUpdatedShort";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select upd_flag from cstdiscountcont where branchno = ?");
	strcat(str," and order_type != 'PM'");
	strcat(str," for update");

	EXEC SQL PREPARE sel_shortupd FROM :str;
	ERROR_MSG2( "prepare sel_shortupd" )
	exec sql declare CShortupd Cursor with hold for sel_shortupd;
	 
	strcpy( str, "update cstdiscountcont set upd_flag = '0' " );
	strcat( str, "where current of CShortupd " );
	
	exec sql prepare set_short from :str;
	ERROR_MSG2( "prepare set_short" )

	exec sql open CShortupd using :haus;
    ERROR_MSG2( "open CShortupd" )

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
		exec sql fetch CShortupd;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CShortupd" )
		
		exec sql execute set_short;
		ERROR_MSG2( "execute set_short" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close CShortupd ;
    ERROR_MSG2( "close CShortupd" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze gesetzt\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int DelNotUpdatedShort( char *error_msg)
{
	char *fun = "DelNotUpdatedShort";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select upd_flag from cstdiscountcont ");
	strcat(str," where upd_flag = '0'");
	strcat(str," and branchno = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_short2 FROM :str;
	ERROR_MSG2( "prepare sel_short2" )
	exec sql declare DelShort Cursor with hold for sel_short2;
	 
	strcpy( str, "delete from cstdiscountcont " );
	strcat( str, "where current of DelShort " );
	
	exec sql prepare del_short from :str;
	ERROR_MSG2( "prepare del_short" )

	exec sql open DelShort using :haus;
    ERROR_MSG2( "open DelShort" )

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
		exec sql fetch DelShort;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelShort" )
		
		exec sql execute del_short;
		ERROR_MSG2( "execute del_short" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close DelShort ;
    ERROR_MSG2( "close DelShort" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze geloescht\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

/***** ENDE *****************************************************************/

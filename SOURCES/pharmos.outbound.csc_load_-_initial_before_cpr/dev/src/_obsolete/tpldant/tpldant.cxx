/* tpldant.ecc */

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tpldant"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "artnetto.h"
#include "pplib/allg.h"
#include "dknas.h"
#include "libtpld/cobolbuf.h"
#include "libtpld/struct.h"
#include <string.h>
#include <unistd.h>
#include <libtpld/qsort.h>
#include <libtpld/hsystfkt.h>
#include <libtpld/vtcodum.h>

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
#define STR_NULL2        "+00000.00"
#define BLANC            ' '

#define DATABASE "phosix"
#define P_DKNAS           "/phosix1/data/UCATPH4/DKNAS.P"
#define ERROR_MSG2(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }

/*** DECLARATION * EXETRN *************************************************************/

extern int  WandelAsci( char *, char *, struct AUFB [], int );

/***** GLOBALE **************************************************************/

FILE *dknasdat;
char log_file [300 + 1];
int debug_enabled   = NO;
int DateiNr = 0;                 /* XVSAM */
int vorlauf = YES;
int nachlauf = YES;
int laden = YES;
	
	EXEC SQL BEGIN DECLARE SECTION;
	char datenbank[60];
	int haus = 0;
	EXEC SQL END DECLARE SECTION;

 
 /***** DECLARATION **********************************************************/
 int main( int, char ** );
 void PrintMsg( char *fun, char *error_msg, char mld, int rc );
 int StarteLadenNettoAktionen( char *error_msg );
 int PrepareDbOperations(char *error_msg);
 int LadeNettoAktionen(struct S_DKNAS *art, char *error_msg);
 int AfterLadeNettoAktionen(char *error_msg);
 int SetKzupd(char *error_msg);
 int DelNotUpd(char *error_msg);
 int SetzeDatumChar( char *, int );

 /***** MAIN *****************************************************************/

 int main( int argc, char **argv  )
 {
   char 	error_msg[81];
   char 	*schalter;
   int 		i;
   int 		skip;
   char 	*fun = "Main";
   char *LOG_FILE = "wws.log";
   char *LOG_PATH;
   char logpath[256+1];
    char *env;

   setbuf( stdout, 0 );              /* printf sofort */
   skip = NO;
   
   for ( i = 1; i < argc; i++ )
    {
       	schalter = argv[i];
       	if ( !strcmp( schalter, "-dg" ) )
		{
	   		debug_enabled = YES;
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			sprintf( datenbank, "%s", argv[i] );
		}
		else if ( !strcmp( schalter, "-lf" ) )
		{
			i++;
			haus = atoi(argv[i]);
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
        else
	  	{
	  		skip = ERROR;
	  		break;
	  	}
  	}                                            
   if ( haus == 0 || skip == ERROR )
      {
      printf( "  usage: %s\n\t"
	      " { -dg <Debugging> }\n\t"
		  " { -db datenbankname <Datenbankname> }\n\t"
		  " { -lf nr <Nummer der Filiale> }\n\t"
	      , argv[0] );
      exit ( 2 );
      }

   DEBUG_SECTION
   END_DEBUG_SECTION

	env = getenv( "LOG_PATH" );
	if ( env == NULL )
		env = ".";
	sprintf( log_file, "%s/wws.log", env );

   if ( StarteLadenNettoAktionen(error_msg) != 0 ) return 1;
	PrintMsg( fun, "ENDE", HINW, 0 );
   return 0;
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
	if ( ( fp = fopen( log_file, "a" ) ) == (FILE *)0 )
		return;
   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.8s %s",
	    mld,
	    haus,
	    zeit->tm_mday,
        zeit->tm_mon + 1,
        zeit->tm_year,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
	    pid,
	    "tpldant",
	    fun );

   fprintf(fp,"%s\n", error_msg );
   fclose(fp);
}

/***** STARTE DAS LADEN DER ARTIKEL-TABELLEN *************************************/

 int StarteLadenNettoAktionen( char *error_msg )
{
	int zaehler, rc;
	char *fun = "StarteLadenNettoAktionen";
	char pfaddknas[81];
	char *XVSAM;
	
	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DKNAS   art_nakt, *a;
	EXEC SQL END DECLARE SECTION;

    struct AUFB aufb[] = { DKNAS_SATZ }; 
	char satz[100];
    int len = 100;	

	a = &art_nakt;

   	
   	EXEC SQL set lock mode to wait 20;
    ERROR_MSG2( "lock: ");
   	EXEC SQL database :datenbank;
    ERROR_MSG2( "database: ");
   	EXEC SQL set isolation to dirty read;
    ERROR_MSG2( "set iso: ");

	PrintMsg( "Main", "Start", HINW, 0 );

	if( (rc = PrepareDbOperations(error_msg)) != 0 )
	{
		return rc;	
	}

	XVSAM = getenv("XVSAM");
	if (XVSAM == NULL)
	{
    	sprintf( error_msg, "XVSAM-Openfehler: %d",rc);
	  	PrintMsg( fun, error_msg, FEHL, ERROR );
   		return -1;
	}
	else
	{
		sprintf(pfaddknas, "%s/UCATPH4/DKNAS.P.dat",XVSAM);
	}
	if ( ( dknasdat = fopen( pfaddknas, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( fun, pfaddknas, FEHL, 0 );
		PrintMsg( fun, "DKNAS nicht vorhanden", FEHL, 0 );
		return -1;
	}
	
	EXEC SQL begin work;
    ERROR_MSG2( "begin work1 %ld");
	for(zaehler=0 ;;zaehler++ )
	{
		if (zaehler%500 == 0)
		{
			EXEC SQL commit work;
   			ERROR_MSG2( "commit work ");
			EXEC SQL begin work;
    		ERROR_MSG2( "begin work2 ");
		}
		if (zaehler%1000 == 0)
		{
		   	DEBUG_SECTION
			sprintf(error_msg,"%d Saetze geladen",zaehler);
 	  		PrintMsg( fun, error_msg, HINW, -1 );
   			END_DEBUG_SECTION
		}

		rc = OK;
		if(fread( satz ,len, 1 , dknasdat ) <= 0)
		{
		   	DEBUG_SECTION
			fprintf(stderr,"%d Saetze gelesen\n",zaehler);
   			END_DEBUG_SECTION
			break;
		}
	 	memset( (char *)a, BLANC, sizeof( struct S_DKNAS ) );
	 	WandelAsci( (char *)a, satz, aufb, SATZANZAHL( aufb ) );
				
		/* neue Tabelle schreiben */
		if ( (rc = LadeNettoAktionen(a, error_msg)) < 0) return rc;
	}
	
	EXEC SQL commit work;
	ERROR_MSG2( "commit work2");
	
	fclose( dknasdat);

	sprintf(error_msg,"%d Saetze geladen",zaehler);
 	PrintMsg( fun, error_msg, HINW, -1 );

	if( (rc = AfterLadeNettoAktionen( error_msg)) != 0 )
	{
		return rc;	
	}
	return OK;
}

int PrepareDbOperations(char *error_msg)
{
	char *fun = "PrepareDbOperations";
	int rc;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"insert into artikelmgpreis (");
	strcat(str,"ARTIKEL_NR,");          
	strcat(str,"DATUMGUELTIGAB,");          
	strcat(str,"DATUMGUELTIGBIS,");          
	strcat(str,"KONDGRUPPENNR,");          
	strcat(str,"MENGE,");          
	strcat(str,"PREISEKAPONETTO,");          
	strcat(str,"KZUPD,");          
	strcat(str,"VERTRIEBSZENTRUMNR");          
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,?,?,\"1\",? )");

	EXEC SQL PREPARE ins_artnetto FROM :str;
	ERROR_MSG2( "prepare ins_artnetto" )

	strcpy(str,"update artikelmgpreis set ");
	strcat(str,"DATUMGUELTIGBIS = ?,");          
	strcat(str,"PREISEKAPONETTO = ?,");          
	strcat(str,"KZUPD = \"1\"");          
	strcat(str," where ");
	strcat(str,"ARTIKEL_NR = ? and ");          
	strcat(str,"DATUMGUELTIGAB = ? and ");          
	strcat(str,"KONDGRUPPENNR = ? and ");          
	strcat(str,"MENGE = ? and ");          
	strcat(str,"VERTRIEBSZENTRUMNR = ?");          

	EXEC SQL PREPARE upd_artnetto FROM :str;
	ERROR_MSG2( "prepare upd_artnetto" )

	strcpy(str,"select kzupd from artikelmgpreis");
	strcat(str," where ");
	strcat(str,"vertriebszentrumnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_artnetto FROM :str;
    ERROR_MSG2( "prepare sel_artnetto ");
	exec sql declare Cartnetto Cursor with hold for sel_artnetto;
	 
	strcpy( str, "update artikelmgpreis set kzupd = \"0\" " );
	strcat( str, "where current of Cartnetto " );
	
	exec sql prepare set_artnetto from :str;
    ERROR_MSG2( "prepare set_artnetto ");

	strcpy(str,"select kzupd from artikelmgpreis where kzupd = \"0\" ");
	strcat(str,"and vertriebszentrumnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_artnetto2 FROM :str;
    ERROR_MSG2( "prepare sel_artnetto2 ");
	exec sql declare Cartnetto2 Cursor with hold for sel_artnetto2;

	strcpy(str,"delete from artikelmgpreis ");
	strcat( str, "where current of Cartnetto2 " );

	EXEC SQL PREPARE del_artnetto FROM :str;
    ERROR_MSG2( "prepare del_artnetto ");
	 
	if ( (rc = SetKzupd( error_msg)) < 0) return rc;
		
	return 0;
}
 
int LadeNettoAktionen(struct S_DKNAS *art, char *error_msg)
{
	char houseno[3];
	char *fun = "LadeNettoAktionen";

	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DKNAS   *a;
	long KONDGRUPPENNR;
	EXEC SQL END DECLARE SECTION;
	a = art;
	
	sprintf( houseno, "%02d\n", haus );
	if ( memcmp( a->NASFIL, houseno, L_DKNAS_NASFIL ) )
	{
		if(!strncmp(a->NASFIL,"13",L_DKNAS_NASFIL) 
			&& !strncmp(houseno,"17",L_DKNAS_NASFIL))
		{
			strncpy(a->NASFIL,houseno,L_DKNAS_NASFIL);
		}
		else
		{
			return 0;
		}
	   /* das darf zwar nicht sein: */
	   /* aber wenn mehrere filialen in der datei stehen sollten */
		
	}

	if ( a->NASLOE[0] == 'J' )
	   {
	   return 0;
	   }
	
	SetzeDatumChar(a->NASDABE, LS_DKNAS_NASDABE);
	SetzeDatumChar(a->NASDAEN, LS_DKNAS_NASDAEN);
	KONDGRUPPENNR = 1;

	DEBUG_SECTION
	printf( "[%x %x %x %x %x %x %x %x]\n", a->NASPZN[0],
									a->NASPZN[1],
									a->NASPZN[2],
									a->NASPZN[3],
									a->NASPZN[4],
									a->NASPZN[5],
									a->NASPZN[6],
									a->NASPZN[7]);
	printf( "[%*.*s]\n", LS_DKNAS_NASPZN, LS_DKNAS_NASPZN,a->NASPZN);
	printf( "[%*.*s]\n", LS_DKNAS_NASDABE, LS_DKNAS_NASDABE,a->NASDABE);
	printf( "[%*.*s]\n", LS_DKNAS_NASDAEN, LS_DKNAS_NASDAEN,a->NASDAEN);
	printf( "[%d]\n", KONDGRUPPENNR);
	printf( "[%*.*s]\n", LS_DKNAS_NASMEN1, LS_DKNAS_NASMEN1,a->NASMEN1);
	printf( "[%*.*s]\n", LS_DKNAS_NASPREI1, LS_DKNAS_NASPREI1,a->NASPREI1);
	END_DEBUG_SECTION

	if(!strncmp( a->NASPZN,"                     ", L_DKNAS_NASPZN))
	  {
       DEBUG_SECTION
	   printf( "RETURN 0;\n");
	   END_DEBUG_SECTION
	   return 0;
	  }

	if (strncmp(  a->NASPREI1 , STR_NULL2, LS_DKNAS_NASPREI1 ) ||
		strncmp(  a->NASMEN1 , STR_NULL, LS_DKNAS_NASMEN1 ))
	{
		KONDGRUPPENNR = 1;

		EXEC SQL EXECUTE upd_artnetto USING
						:a->NASDAEN,
						:a->NASPREI1,
			  			:a->NASPZN,
						:a->NASDABE,
						:KONDGRUPPENNR,
						:a->NASMEN1,
						:haus;
	    ERROR_MSG2( "upd_artnetto1 ");
   		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
     	{
			EXEC SQL EXECUTE ins_artnetto USING
				  			:a->NASPZN,
							:a->NASDABE,
							:a->NASDAEN,
							:KONDGRUPPENNR,
							:a->NASMEN1,
							:a->NASPREI1,
							:haus;
	   		if (sqlca.sqlcode == -1213)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert1: %ld %ld, PZN: %s", sqlca.sqlcode, sqlca.sqlerrd[1],a->NASPZN);
 		  		PrintMsg( fun, error_msg, FEHL, ERROR );
		 	}
   			else if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		 	{
		  		sprintf (error_msg, "insert: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 		  		PrintMsg( fun, error_msg, FEHL, ERROR );
		  		return ERROR;
     		}
		}
		if  (!strncmp(  a->NASPREI6 , STR_NULL2, LS_DKNAS_NASPREI6 ) ||
			!strncmp(  a->NASMEN6 , STR_NULL, LS_DKNAS_NASMEN6 ))
		{
		
			KONDGRUPPENNR = 2;

			EXEC SQL EXECUTE upd_artnetto USING
							:a->NASDAEN,
							:a->NASPREI1,
			  				:a->NASPZN,
							:a->NASDABE,
							:KONDGRUPPENNR,
							:a->NASMEN1,
							:haus;
			ERROR_MSG2( "upd_artnetto1 ");
   			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
     		{
				EXEC SQL EXECUTE ins_artnetto USING
					  			:a->NASPZN,
								:a->NASDABE,
								:a->NASDAEN,
								:KONDGRUPPENNR,
								:a->NASMEN1,
								:a->NASPREI1,
								:haus;
	   			if (sqlca.sqlcode == -1213)  /* Datenbankfehler */
	     		{
	      			sprintf (error_msg, "insert1: %ld %ld, PZN: %s", sqlca.sqlcode, sqlca.sqlerrd[1],a->NASPZN);
 		  			PrintMsg( fun, error_msg, FEHL, ERROR );
		 		}
   				else if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		 		{
		  			sprintf (error_msg, "insert: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 		  			PrintMsg( fun, error_msg, FEHL, ERROR );
		  			return ERROR;
     			}
			}
		}	
	}
	if (strncmp(  a->NASPREI2 , STR_NULL2, LS_DKNAS_NASPREI2 ) ||
		strncmp(  a->NASMEN2 , STR_NULL, LS_DKNAS_NASMEN2 ))
	{
		KONDGRUPPENNR = 1;
		EXEC SQL EXECUTE upd_artnetto USING
						:a->NASDAEN,
						:a->NASPREI2,
			  			:a->NASPZN,
						:a->NASDABE,
						:KONDGRUPPENNR,
						:a->NASMEN2,
						:haus;
	    ERROR_MSG2( "upd_artnetto2 ");
   		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
     	{
			EXEC SQL EXECUTE ins_artnetto USING
				  			:a->NASPZN,
							:a->NASDABE,
							:a->NASDAEN,
							:KONDGRUPPENNR,
							:a->NASMEN2,
							:a->NASPREI2,
							:haus;
	   		if (sqlca.sqlcode == -1213)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert2: %ld %ld, PZN: %s", sqlca.sqlcode, sqlca.sqlerrd[1],a->NASPZN);
	 	  		PrintMsg( fun, error_msg, FEHL, ERROR );
	     	}
	   		else if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert2: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 	  		PrintMsg( fun, error_msg, FEHL, ERROR );
	      		return ERROR;
	     	}
		}
		if (!strncmp(  a->NASPREI6 , STR_NULL2, LS_DKNAS_NASPREI6 ) ||
			!strncmp(  a->NASMEN6 , STR_NULL, LS_DKNAS_NASMEN6 ))
		{
		
			KONDGRUPPENNR = 2;

			EXEC SQL EXECUTE upd_artnetto USING
							:a->NASDAEN,
							:a->NASPREI2,
			  				:a->NASPZN,
							:a->NASDABE,
							:KONDGRUPPENNR,
							:a->NASMEN2,
							:haus;
			ERROR_MSG2( "upd_artnetto1 ");
   			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
     		{
				EXEC SQL EXECUTE ins_artnetto USING
					  			:a->NASPZN,
								:a->NASDABE,
								:a->NASDAEN,
								:KONDGRUPPENNR,
								:a->NASMEN2,
								:a->NASPREI2,
								:haus;
	   			if (sqlca.sqlcode == -1213)  /* Datenbankfehler */
	     		{
	      			sprintf (error_msg, "insert1: %ld %ld, PZN: %s", sqlca.sqlcode, sqlca.sqlerrd[1],a->NASPZN);
 		  			PrintMsg( fun, error_msg, FEHL, ERROR );
		 		}
   				else if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		 		{
		  			sprintf (error_msg, "insert: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 		  			PrintMsg( fun, error_msg, FEHL, ERROR );
		  			return ERROR;
     			}
			}
		}	
	}
	if (strncmp(  a->NASPREI3 , STR_NULL2, LS_DKNAS_NASPREI3 ) ||
		strncmp(  a->NASMEN3 , STR_NULL, LS_DKNAS_NASMEN3 ))
	{
		KONDGRUPPENNR = 1;
		EXEC SQL EXECUTE upd_artnetto USING
						:a->NASDAEN,
						:a->NASPREI3,
			  			:a->NASPZN,
						:a->NASDABE,
						:KONDGRUPPENNR,
						:a->NASMEN3,
						:haus;
	    ERROR_MSG2( "upd_artnetto3 ");
   		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
     	{
			EXEC SQL EXECUTE ins_artnetto USING
				  			:a->NASPZN,
							:a->NASDABE,
							:a->NASDAEN,
							:KONDGRUPPENNR,
							:a->NASMEN3,
							:a->NASPREI3,
							:haus;
	   		if (sqlca.sqlcode == -1213)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert3: %ld %ld, PZN: %s", sqlca.sqlcode, sqlca.sqlerrd[1],a->NASPZN);
	 	  		PrintMsg( fun, error_msg, FEHL, ERROR );
	     	}
	   		else if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert3: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 	  		PrintMsg( fun, error_msg, FEHL, ERROR );
	      		return ERROR;
	     	}
		}
		if (!strncmp(  a->NASPREI6 , STR_NULL2, LS_DKNAS_NASPREI6 ) ||
			!strncmp(  a->NASMEN6 , STR_NULL, LS_DKNAS_NASMEN6 ))
		{
		
			KONDGRUPPENNR = 2;

			EXEC SQL EXECUTE upd_artnetto USING
							:a->NASDAEN,
							:a->NASPREI3,
			  				:a->NASPZN,
							:a->NASDABE,
							:KONDGRUPPENNR,
							:a->NASMEN3,
							:haus;
			ERROR_MSG2( "upd_artnetto1 ");
   			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
     		{
				EXEC SQL EXECUTE ins_artnetto USING
					  			:a->NASPZN,
								:a->NASDABE,
								:a->NASDAEN,
								:KONDGRUPPENNR,
								:a->NASMEN3,
								:a->NASPREI3,
								:haus;
	   			if (sqlca.sqlcode == -1213)  /* Datenbankfehler */
	     		{
	      			sprintf (error_msg, "insert1: %ld %ld, PZN: %s", sqlca.sqlcode, sqlca.sqlerrd[1],a->NASPZN);
 		  			PrintMsg( fun, error_msg, FEHL, ERROR );
		 		}
   				else if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		 		{
		  			sprintf (error_msg, "insert: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 		  			PrintMsg( fun, error_msg, FEHL, ERROR );
		  			return ERROR;
     			}
			}
		}	
	}
	if (strncmp(  a->NASPREI4 , STR_NULL2, LS_DKNAS_NASPREI4 ) ||
		strncmp(  a->NASMEN4 , STR_NULL, LS_DKNAS_NASMEN4 ))
	{
		KONDGRUPPENNR = 1;
		EXEC SQL EXECUTE upd_artnetto USING
						:a->NASDAEN,
						:a->NASPREI4,
			  			:a->NASPZN,
						:a->NASDABE,
						:KONDGRUPPENNR,
						:a->NASMEN4,
						:haus;
	    ERROR_MSG2( "upd_artnetto4 ");
   		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
     	{
			EXEC SQL EXECUTE ins_artnetto USING
				  			:a->NASPZN,
							:a->NASDABE,
							:a->NASDAEN,
							:KONDGRUPPENNR,
							:a->NASMEN4,
							:a->NASPREI4,
							:haus;
	   		if (sqlca.sqlcode == -1213)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert4: %ld %ld, PZN: %s", sqlca.sqlcode, sqlca.sqlerrd[1],a->NASPZN);
	 	  		PrintMsg( fun, error_msg, FEHL, ERROR );
	     	}
	   		else if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert4: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 	  		PrintMsg( fun, error_msg, FEHL, ERROR );
	      		return ERROR;
	     	}
		}
		if (!strncmp(  a->NASPREI6 , STR_NULL2, LS_DKNAS_NASPREI6 ) ||
			!strncmp(  a->NASMEN6 , STR_NULL, LS_DKNAS_NASMEN6 ))
		{
		
			KONDGRUPPENNR = 2;

			EXEC SQL EXECUTE upd_artnetto USING
							:a->NASDAEN,
							:a->NASPREI4,
			  				:a->NASPZN,
							:a->NASDABE,
							:KONDGRUPPENNR,
							:a->NASMEN4,
							:haus;
			ERROR_MSG2( "upd_artnetto1 ");
   			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
     		{
				EXEC SQL EXECUTE ins_artnetto USING
					  			:a->NASPZN,
								:a->NASDABE,
								:a->NASDAEN,
								:KONDGRUPPENNR,
								:a->NASMEN4,
								:a->NASPREI4,
								:haus;
	   			if (sqlca.sqlcode == -1213)  /* Datenbankfehler */
	     		{
	      			sprintf (error_msg, "insert1: %ld %ld, PZN: %s", sqlca.sqlcode, sqlca.sqlerrd[1],a->NASPZN);
 		  			PrintMsg( fun, error_msg, FEHL, ERROR );
		 		}
   				else if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		 		{
		  			sprintf (error_msg, "insert: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 		  			PrintMsg( fun, error_msg, FEHL, ERROR );
		  			return ERROR;
     			}
			}
		}	
	}
	if (strncmp(  a->NASPREI5 , STR_NULL2, LS_DKNAS_NASPREI5 ) ||
		strncmp(  a->NASMEN5 , STR_NULL, LS_DKNAS_NASMEN5 ))
	{
		KONDGRUPPENNR = 3;
		EXEC SQL EXECUTE upd_artnetto USING
						:a->NASDAEN,
						:a->NASPREI5,
			  			:a->NASPZN,
						:a->NASDABE,
						:KONDGRUPPENNR,
						:a->NASMEN5,
						:haus;
	    ERROR_MSG2( "upd_artnetto5 ");
   		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
     	{
			EXEC SQL EXECUTE ins_artnetto USING
				  			:a->NASPZN,
							:a->NASDABE,
							:a->NASDAEN,
							:KONDGRUPPENNR,
							:a->NASMEN5,
							:a->NASPREI5,
							:haus;
	   		if (sqlca.sqlcode == -1213)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert5: %ld %ld, PZN: %s", sqlca.sqlcode, sqlca.sqlerrd[1],a->NASPZN);
	 	  		PrintMsg( fun, error_msg, FEHL, ERROR );
	     	}
	   		else if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert5: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 	  		PrintMsg( fun, error_msg, FEHL, ERROR );
	      		return ERROR;
	     	}
		}
	}
	if (strncmp(  a->NASPREI6 , STR_NULL2, LS_DKNAS_NASPREI6 ) ||
		strncmp(  a->NASMEN6 , STR_NULL, LS_DKNAS_NASMEN6 ))
	{
		KONDGRUPPENNR = 2;
		EXEC SQL EXECUTE upd_artnetto USING
						:a->NASDAEN,
						:a->NASPREI6,
			  			:a->NASPZN,
						:a->NASDABE,
						:KONDGRUPPENNR,
						:a->NASMEN6,
						:haus;
	    ERROR_MSG2( "upd_artnetto6 ");
   		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
     	{
			EXEC SQL EXECUTE ins_artnetto USING
				  			:a->NASPZN,
							:a->NASDABE,
							:a->NASDAEN,
							:KONDGRUPPENNR,
							:a->NASMEN6,
							:a->NASPREI6,
							:haus;
	   		if (sqlca.sqlcode == -1213)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert6: %ld %ld, PZN: %s", sqlca.sqlcode, sqlca.sqlerrd[1],a->NASPZN);
	 	  		PrintMsg( fun, error_msg, FEHL, ERROR );
	     	}
	   		else if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	     	{
	      		sprintf (error_msg, "insert6: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 	  		PrintMsg( fun, error_msg, FEHL, ERROR );
	      		return ERROR;
	     	}
		}
	}
	return OK;
}

int AfterLadeNettoAktionen        (char *error_msg)
{
	char *fun = "AfterLadeNettoAktionen";
	int rc = 0;

	if ( (rc = DelNotUpd( error_msg)) < 0) return rc;

	return OK;
}

int SetKzupd(char *error_msg)
{
	char *fun = "SetKzupd";
	int comz;
	EXEC SQL begin work;
	ERROR_MSG2( "begin work ");
	EXEC SQL open Cartnetto using :haus;
	ERROR_MSG2( "open Cartnetto ");
	for(comz=0 ;;comz++ )
	{
		if (comz%500 == 0)
		{
			EXEC SQL commit work;
   			ERROR_MSG2( "commit work ");
			EXEC SQL begin work;
    		ERROR_MSG2( "begin work2 ");
		}
		if (comz%1000 == 0)
		{
		   	DEBUG_SECTION
			sprintf(error_msg,"%d Saetze geladen",comz);
 	  		PrintMsg( fun, error_msg, HINW, -1 );
   			END_DEBUG_SECTION
		}
		EXEC SQL fetch Cartnetto;
   		if (sqlca.sqlcode == 100) break; /* NotFound */
   		ERROR_MSG2( "fetch Cartnetto ");
		EXEC SQL EXECUTE set_artnetto;
   		ERROR_MSG2( "set_artnetto ");
	}
	EXEC SQL commit work;
   	ERROR_MSG2( "commit work2 ");
	EXEC SQL close Cartnetto;
	ERROR_MSG2( "close Cartnetto ");
	return OK;
}

int DelNotUpd(char *error_msg)
{
	char *fun = "DelNotUpd";
	int comz;
	EXEC SQL begin work;
	ERROR_MSG2( "begin work ");
	EXEC SQL open Cartnetto2 using :haus;
	ERROR_MSG2( "open Cartnetto2 ");
	for(comz=0 ;;comz++ )
	{
		if (comz%500 == 0)
		{
			EXEC SQL commit work;
   			ERROR_MSG2( "commit work ");
			EXEC SQL begin work;
    		ERROR_MSG2( "begin work2 ");
		}
		if (comz%1000 == 0)
		{
		   	DEBUG_SECTION
			sprintf(error_msg,"%d Saetze geladen",comz);
 	  		PrintMsg( fun, error_msg, HINW, -1 );
   			END_DEBUG_SECTION
		}
		EXEC SQL fetch Cartnetto2;
   		if (sqlca.sqlcode == 100) break; /* NotFound */
   		ERROR_MSG2( "fetch Cartnetto2 ");
		EXEC SQL EXECUTE del_artnetto;
   		ERROR_MSG2( "del_artnetto ");
	}
	EXEC SQL commit work;
   	ERROR_MSG2( "commit work2 ");
	EXEC SQL close Cartnetto2;
	ERROR_MSG2( "close Cartnetto2 ");
	return OK;
}
 
/*** SETZTE-DATUM-CHAR ********************************************************/

 int SetzeDatumChar( char *datum, int len )
 {
 	char *fun = "SetzeDatumChar";
 	char huelse[20];
	long lDate = 0;

	if ( len < 8 )
	   return WARNING;

	if ( !strncmp( datum, "+00000000", len ) )
	{
	   strcpy( datum, "0" );
	   return OK;
	}
	else if ( !strncmp( datum, "+19000000", len ) )
	{
	   strcpy( datum, "0" );
	   return OK;
	}
	else if ( !strncmp( datum, "19000000", len ) )
	{
	   strcpy( datum, "0" );
	   return OK;
	}
	else if ( !strncmp( datum, "+20000000", len ) )
	{
	   strcpy( datum, "0" );
	   return OK;
	}
	else if ( !strncmp( datum, "20000000", len ) )
	{
	   strcpy( datum, "0" );
	   return OK;
	}

	else if ( !strcmp( datum , "0" ) )
	   return OK;
	else if ( datum[0] == '1' && datum[1] == '9' )
	   return OK;
	else
	{
	   sprintf( huelse, "%*.*s", len, len, datum );
	   lDate = atoi( huelse );
	   lDate += (lDate / 10000) < 70 ? 20000000 : 19000000;
	   sprintf( huelse, "%ld", lDate );
	   memcpy( datum, huelse, len );
	}
	return OK;
 }


/***** ENDE *****************************************************************/

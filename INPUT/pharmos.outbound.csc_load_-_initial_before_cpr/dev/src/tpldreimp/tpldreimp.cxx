/* tpldreimp.ecc */
#include "csc_load_version.h"

#define PROJECTNAME	 "tpldreimp"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

//static char *SCCSID="@(#)PRZ GmbH Stand: 1.0.6 $Header: /prj/df/unix/tpldreimp/tpldreimp.cxx 34    29.01.04 18:48 66aeimsc $";

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include "artikelreimport.h"
#include "dkris.h"
#include "libtpld/cobolbuf.h"
#include "libtpld/struct.h"

EXEC SQL include sqlca;

#undef NULL  

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
#define P_DKRIS           "/phosix1/data/UCATPH1/DKRIS.P"
#define ERROR_MSG2(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }


#define DATABASE "phosix"
	
	EXEC SQL BEGIN DECLARE SECTION;
	char datenbank[60];
	EXEC SQL END DECLARE SECTION;

/*** DECLARATION * EXETRN *************************************************************/

 extern int  WandelAsci( char *, char *, struct AUFB [], int );

 /***** GLOBALE **************************************************************/
 FILE *dkrisdat;
 char log_file [300 + 1];
 int debug_enabled   = NO;
 int DateiNr = 0;
 int vorlauf = YES;
 int nachlauf = YES;
 int laden = YES;
 int pflege = NO;
 int updcount;
 int inscount;
 int okcount;
 int haus = 99;
 
 /***** DECLARATION **********************************************************/
 int main( int, char ** );
 void PrintMsg( char *fun, char *error_msg, char mld, int rc );
 int StarteLadenReimport( char *error_msg );
 int PrepareDbOperations(char *error_msg);
 int LadeReimport(struct S_DKRIS *art, char *error_msg);
 int AfterLadeReimport(char *error_msg);
 int CheckArticle( char *PZN1, char *PZN2, char *error_msg);
 int SetNotUpdatedReimport( char *error_msg);
 int DelNotUpdatedReimport( char *error_msg);
  
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

   setbuf( stdout, 0 );              /* printf sofort */
   skip = NO;
	sprintf(datenbank,"%s",DATABASE);
   
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
		else if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			sprintf( datenbank, "%s", argv[i] );
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
   if ( skip == ERROR )
      {
      printf( "  usage: %s\n\t"
	      " { -dg <Debugging> }\n\t"
	      , argv[0] );
      exit ( 2 );
      }

   DEBUG_SECTION
   END_DEBUG_SECTION

   if ((LOG_PATH = getenv("LOG_PATH")) == (char *)0)
   {
	   strcpy(logpath, ".");
   }
   else
   {
	   strcpy(logpath, LOG_PATH);
   }
   sprintf(log_file, "%s/%s", logpath, LOG_FILE);
  		
   if ( StarteLadenReimport(error_msg) != 0 )
   {
   		PrintMsg( fun, "Mit Fehler Beendet", FEHL, 0 );
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
   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.9s %s",
	    mld,
	    haus,
	    zeit->tm_mday,
        zeit->tm_mon + 1,
        zeit->tm_year,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
	    pid,
	    "tpldreimp",
	    fun );

   fprintf(fp,"%s\n", error_msg );
   fclose(fp);
}

/***** STARTE DAS LADEN DER REIMPORTARTIKEL-TABELLE ************************/

 int StarteLadenReimport( char *error_msg )
{
	int zaehler, rc;
	char *fun = "StarteLadenReimport";
	
	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DKRIS   ris, *a;
	short int filialnr;
	EXEC SQL END DECLARE SECTION;

    struct AUFB aufb[] = { DKRIS_SATZ }; 
	char 	pfaddkris[81];
	char *XVSAM;
	char satz[350];
    int len = 350;
	
    a = &ris;
   	
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
	PrintMsg( fun, "Start", HINW, 0 );
	if( (rc = PrepareDbOperations(error_msg)) != 0 )
		{
		return rc;	
		}

	if ((XVSAM = getenv("XVSAM")) == (char *)0)
	{
		return -1;
	}
	else
	{
		sprintf(pfaddkris, "%s/UCATPH1/DKRIS.P.dat",XVSAM);
	}

	DEBUG_SECTION
	fprintf(stderr,"Pfad: %s \n",pfaddkris);
	END_DEBUG_SECTION

	if ( ( dkrisdat = fopen( pfaddkris, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( fun, pfaddkris, FEHL, 0 );
		PrintMsg( fun, "DKRIS nicht vorhanden", FEHL, 0 );
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
			sprintf(error_msg,"%d Saetze geladen",zaehler);
 	  		PrintMsg( fun, error_msg, HINW, -1 );
   			END_DEBUG_SECTION
		}

		rc = OK;
		if(fread( satz ,len, 1 , dkrisdat ) != 0)
        {
	 	if ( rc != OK )
	 	   {
   			sprintf(error_msg, " XVSAM-Lesen DKRIS %ld", rc);
  			PrintMsg( fun, error_msg, FEHL, -1 );
	    	return -1;
	    	}
	 	memset( (char *)a, BLANC, sizeof( struct S_DKRIS ) );
	 	WandelAsci( (char *)a, satz, aufb, SATZANZAHL( aufb ) );
	 	}
		else
		{
			break;
		}
				
		if(a->RISLOE[0] != 'J') /* bestehende Tabelle updaten */
		{
			if ( (rc = LadeReimport(a, error_msg)) < 0) return rc;
		}
	}
	
	EXEC SQL commit work;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, "commit work2 %ld", sqlca.sqlcode);
		PrintMsg( fun, error_msg, FEHL, -1 );
		return -1;
	}
	
	fclose( dkrisdat);
    
	sprintf(error_msg," %d DKRIS-Saetze gelesen ",zaehler);
 	PrintMsg( fun, error_msg, HINW, -1 );
	sprintf(error_msg," %d Saetze OK und %d Saetze eingefuegt",updcount,inscount);
 	PrintMsg( fun, error_msg, HINW, -1 );

	if( (rc = AfterLadeReimport( error_msg)) != 0 )
	{
		return rc;	
	}
return OK;
}

int PrepareDbOperations(char *error_msg)
{
	char *fun = "PrepareDbOperations";
	int rc = 0;
	
	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	if((rc = SetNotUpdatedReimport( error_msg )) != 0) return rc;

	strcpy(str,"update artikelreimport set ");
 	strcat(str,"KZUPD = \"1\",");
 	strcat(str,"KZAKTIVPASSIV = ?,");
 	strcat(str,"REIHENFOLGE = ? ");
 	strcat(str,"where FILIALNR = 0 ");
 	strcat(str,"and ARTIKEL_NR = ? ");
 	strcat(str,"and ARTIKEL_NR_ALTERN = ? ");


	EXEC SQL PREPARE upd_reimp FROM :str;
	ERROR_MSG2( "prepare upd_reimp" )

	strcpy(str,"insert into artikelreimport (");
	strcat(str,"FILIALNR,");
	strcat(str,"ARTIKEL_NR,");
	strcat(str,"ARTIKEL_NR_ALTERN,");
	strcat(str,"KZUPD,");
	strcat(str,"KZAKTIVPASSIV,");
 	strcat(str,"REIHENFOLGE");
	strcat(str," ) values ");
	strcat(str,"( 0,?,?,\"1\",?,? )");

	EXEC SQL PREPARE ins_reimp FROM :str;
    if (sqlca.sqlcode < 0 )
    {
       	sprintf(error_msg, "prepare ins_reimp %ld", sqlca.sqlcode);
  		PrintMsg( fun, error_msg, FEHL, -1 );
       	return -1;
    }

	return 0;

}
 
int LadeReimport(struct S_DKRIS *art, char *error_msg)
{
	char *fun = "LadeReimport";

	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DKRIS   *a;
	char cAktiv[2];
	short iReihe;
	EXEC SQL END DECLARE SECTION;
	a = art;

	cAktiv[1] = '\0';
	iReihe = 0;

	if(CheckArticle( a->RISPZN1, a->RISPZN1, error_msg) != 0) return OK;

	if ( strncmp( a->RISPZN01, STR_NULL, LS_DKRIS_RISPZN01 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN01, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART01[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN01
				;
			ERROR_MSG2( "upd reimport1:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN01,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport1" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN02, STR_NULL, LS_DKRIS_RISPZN02 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN02, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART02[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN02;
			ERROR_MSG2( "upd reimport2:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
				{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN02,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport2" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN03, STR_NULL, LS_DKRIS_RISPZN03 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN03, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART03[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN03;
			ERROR_MSG2( "upd reimport3:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN03,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport3" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN04, STR_NULL, LS_DKRIS_RISPZN04 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN04, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART04[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN04;
			ERROR_MSG2( "upd reimport2:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN04,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport4" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN05, STR_NULL, LS_DKRIS_RISPZN05 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN05, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART05[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN05;
			ERROR_MSG2( "upd reimport5:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN05,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport5" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN06, STR_NULL, LS_DKRIS_RISPZN06 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN06, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART06[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN06;
			ERROR_MSG2( "upd reimport6:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN06,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport6" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN07, STR_NULL, LS_DKRIS_RISPZN07 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN07, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART07[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN07;
			ERROR_MSG2( "upd reimport7:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN07,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport7" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN08, STR_NULL, LS_DKRIS_RISPZN08 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN08, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART08[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN08;
			ERROR_MSG2( "upd reimport8:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN08,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport8" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN09, STR_NULL, LS_DKRIS_RISPZN09 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN09, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART09[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN09;
			ERROR_MSG2( "upd reimport9:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN09,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport9" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN10, STR_NULL, LS_DKRIS_RISPZN10 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN10, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART10[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN10;
			ERROR_MSG2( "upd reimport10:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN10,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport10" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN11, STR_NULL, LS_DKRIS_RISPZN11 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN11, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART11[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN11;
			ERROR_MSG2( "upd reimport11:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN11,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport11" )
				inscount++;
			}
			else updcount++;
		}
	}
	if ( strncmp( a->RISPZN12, STR_NULL, LS_DKRIS_RISPZN12 ))
	{
		if(CheckArticle( a->RISPZN1, a->RISPZN12, error_msg) == 0)
		{
			iReihe++;
			if ( a->RISVKART12[0] == 'A')    cAktiv[0] = '1';
			else cAktiv[0] = '0';
			EXEC SQL EXECUTE upd_reimp USING
				:cAktiv,
				:iReihe,
				:a->RISPZN1,											
				:a->RISPZN12;
			ERROR_MSG2( "upd reimport12:" )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
			{
				EXEC SQL EXECUTE ins_reimp USING
					:a->RISPZN1,											
					:a->RISPZN12,
					:cAktiv,
					:iReihe;
				ERROR_MSG2( "insert reimport12" )
				inscount++;
			}
			else updcount++;
		}
	}
	return OK;
}

int AfterLadeReimport(char *error_msg)
{
	char *fun = "AfterLadeReimport";
	int rc = 0;

	if ((rc = DelNotUpdatedReimport(error_msg)) != 0) return rc;

return OK;
}

int SetNotUpdatedReimport( char *error_msg)
{
	char *fun = "SetNotUpdatedReimport";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select kzupd from artikelreimport ");
	strcat(str," for update");

	EXEC SQL PREPARE sel_reimport FROM :str;
	ERROR_MSG2( "prepare sel_reimport" )
	exec sql declare CReimport Cursor with hold for sel_reimport;
	 
	strcpy( str, "update artikelreimport set kzupd = '0' " );
	strcat( str, "where current of CReimport " );
	
	exec sql prepare set_reimport from :str;
	ERROR_MSG2( "prepare set_reimport" )

	exec sql open CReimport ;
    ERROR_MSG2( "open CReimport" )

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
		exec sql fetch CReimport;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CReimport" )
		
		exec sql execute set_reimport;
		ERROR_MSG2( "execute set_reimport" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close CReimport ;
    ERROR_MSG2( "close CReimport" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze gesetzt",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int DelNotUpdatedReimport( char *error_msg)
{
	char *fun = "DelNotUpdatedReimport";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select kzupd from artikelreimport ");
	strcat(str," where kzupd = '0'");
	strcat(str," for update");

	EXEC SQL PREPARE sel_reimport2 FROM :str;
	ERROR_MSG2( "prepare sel_reimport2" )
	exec sql declare DelReimport Cursor with hold for sel_reimport2;
	 
	strcpy( str, "delete from artikelreimport " );
	strcat( str, "where current of DelReimport " );
	
	exec sql prepare del_reimport from :str;
	ERROR_MSG2( "prepare del_reimport" )

	exec sql open DelReimport ;
    ERROR_MSG2( "open DelReimport" )

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
		exec sql fetch DelReimport;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelReimport" )
		
		exec sql execute del_reimport;
		ERROR_MSG2( "execute del_reimport" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close DelReimport ;
    ERROR_MSG2( "close DelReimport" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze geloescht",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int CheckArticle( char *PZN1, char *PZN2, char *error_msg)
{
	char *fun = "CheckArticle";

	EXEC SQL BEGIN DECLARE SECTION;
	char pzn1[LS_DKRIS_RISPZN1+1];
	char pzn2[LS_DKRIS_RISPZN01+1];
	EXEC SQL END DECLARE SECTION;

	sprintf( pzn2, "%*.*s",LS_DKRIS_RISPZN01,LS_DKRIS_RISPZN01,PZN2 );
	sprintf( pzn1, "%*.*s",LS_DKRIS_RISPZN1,LS_DKRIS_RISPZN1,PZN1 );

	DEBUG_SECTION
	printf( "PZN1 = %*.*s\n",LS_DKRIS_RISPZN1,LS_DKRIS_RISPZN1,PZN1 );
	printf( "PZN2 = %*.*s\n",LS_DKRIS_RISPZN01,LS_DKRIS_RISPZN01,PZN2 );
	printf( "pzn1 = %s\n",pzn1 );
	printf( "pzn2 = %s\n",pzn2 );
	END_DEBUG_SECTION

	EXEC SQL select artikel_nr from artikelzentral where artikel_nr = :pzn2;
	if ( sqlca.sqlcode == 100 )
	{
		sprintf( error_msg, " artikelnr.: %s aus DKRIS-Satz %s nicht vorhanden",
				pzn2,pzn1);
/*		PrintMsg( fun, error_msg, HINW, -1 );	*/
		return -1;
	}
	return OK;
}

/***** ENDE *****************************************************************/

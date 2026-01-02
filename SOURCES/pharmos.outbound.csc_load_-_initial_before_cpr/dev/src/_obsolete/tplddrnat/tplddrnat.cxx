/* tplddrnat.ecc */

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tplddrnat"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "natrastaffeln.h"
#include "drnat.h"
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

#define DEBUG_SECTION      if ( debug_sw ) {
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
#define POSITION			0

#define DATABASE "phosix"
#define P_DRNAT           "/phosix1/data/UCATPH1/DRNAT.P"
#define ERROR_MSG2(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }

/*** DECLARATION * EXETRN *************************************************************/

extern int  WandelAsci( char *, char *, struct AUFB [], int );

/***** GLOBALE **************************************************************/

FILE *drnatdat;
char log_file [300 + 1];
int debug_enabled   = NO;
int debug_sw   = NO;
	
	EXEC SQL BEGIN DECLARE SECTION;
	char datenbank[60];
	EXEC SQL END DECLARE SECTION;

 
 /***** DECLARATION **********************************************************/
 int main( int, char ** );
 void PrintMsg( char *fun, char *error_msg, char mld, int rc );
 int StarteLadenNatra( char *error_msg );
 int PrepareDbOperations(char *error_msg);
 int LadeNatra(struct S_DRNAT *art, char *error_msg);
 int AfterLadeNatra(char *error_msg);
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
	   		debug_sw = YES;
		}
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

   if ( StarteLadenNatra(error_msg) != 0 ) return 1;
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
	    99,
	    zeit->tm_mday,
        zeit->tm_mon + 1,
        zeit->tm_year,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
	    pid,
	    "tplddrnat",
	    fun );

   fprintf(fp,"%s\n", error_msg );
   fclose(fp);
}

/***** STARTE DAS LADEN DER ARTIKEL-TABELLEN *************************************/

 int StarteLadenNatra( char *error_msg )
{
	int zaehler, rc;
	char *fun = "StarteLadenNatra";
	char pfaddrnat[81];
	char *XVSAM;
	
	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DRNAT   art_nat, *a;
	EXEC SQL END DECLARE SECTION;

    struct AUFB aufb[] = { DRNAT_SATZ }; 
	char satz[100+POSITION];
    int len = 100+POSITION;	

	a = &art_nat;

   	
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
		sprintf(pfaddrnat, "%s/UCATPH1/DRNAT.P.dat",XVSAM);
	}
	if ( ( drnatdat = fopen( pfaddrnat, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( fun, pfaddrnat, FEHL, 0 );
		PrintMsg( fun, "DRNAT nicht vorhanden", FEHL, 0 );
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
		if(fread( satz ,len, 1 , drnatdat ) <= 0)
		{
		   	DEBUG_SECTION
			fprintf(stderr,"%d Saetze gelesen\n",zaehler);
   			END_DEBUG_SECTION
			break;
		}
	 	memset( (char *)a, BLANC, sizeof( struct S_DRNAT ) );
	 	WandelAsci( (char *)a, satz+POSITION, aufb, SATZANZAHL( aufb ) );
				
		/* neue Tabelle schreiben */
		if ( (rc = LadeNatra(a, error_msg)) < 0) return rc;
	}
	
	EXEC SQL commit work;
	ERROR_MSG2( "commit work2");
	
	fclose( drnatdat);

	sprintf(error_msg,"%d Saetze geladen",zaehler);
 	PrintMsg( fun, error_msg, HINW, -1 );

	if( (rc = AfterLadeNatra( error_msg)) != 0 )
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

	strcpy(str,"insert into natrastaffeln (");
	strcat(str,"NATRASTAFFELNR,");          
	strcat(str,"DATUMGUELTIGAB,");          
	strcat(str,"DATUMGUELTIGBIS,");          
	strcat(str,"NATRABASISMENGE,");          
	strcat(str,"NATRAMENGE,");          
	strcat(str,"KONDGRUPPENNR,");          
	strcat(str,"KZUPD");          
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,?,?,\"1\" )");

	EXEC SQL PREPARE ins_natra FROM :str;
	ERROR_MSG2( "prepare ins_natra" )

	strcpy(str,"update natrastaffeln set ");
	strcat(str,"DATUMGUELTIGAB = ?,");          
	strcat(str,"DATUMGUELTIGBIS = ?,");          
	strcat(str,"NATRABASISMENGE = ?,");          
	strcat(str,"NATRAMENGE = ?,");          
	strcat(str,"KZUPD = \"1\"");          
	strcat(str," where ");
	strcat(str,"NATRASTAFFELNR = ? and ");          
	strcat(str,"KONDGRUPPENNR = ? and ");          
	strcat(str,"NATRABASISMENGE = ?");          

	EXEC SQL PREPARE upd_natra FROM :str;
	ERROR_MSG2( "prepare upd_natra" )

	strcpy(str,"select kzupd from natrastaffeln for update");

	EXEC SQL PREPARE sel_natra FROM :str;
    ERROR_MSG2( "prepare sel_natra ");
	exec sql declare Cnatra Cursor with hold for sel_natra;
	 
	strcpy( str, "update natrastaffeln set kzupd = \"0\" " );
	strcat( str, "where current of Cnatra " );
	
	exec sql prepare set_natra from :str;
    ERROR_MSG2( "prepare set_natra ");

	strcpy(str,"select kzupd from natrastaffeln where kzupd = \"0\" for update");

	EXEC SQL PREPARE sel_natra2 FROM :str;
    ERROR_MSG2( "prepare sel_natra2 ");
	exec sql declare Cnatra2 Cursor with hold for sel_natra2;

	strcpy(str,"delete from natrastaffeln ");
	strcat( str, "where current of Cnatra2 " );

	EXEC SQL PREPARE del_natra FROM :str;
    ERROR_MSG2( "prepare del_natra ");
	 
	if ( (rc = SetKzupd( error_msg)) < 0) return rc;
		
	return 0;
}
 
int LadeNatra(struct S_DRNAT *art, char *error_msg)
{
	char houseno[3];
	char *fun = "LadeNatra";
	int i;

	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DRNAT   *a;
	long KONDGRUPPENNR;
	EXEC SQL END DECLARE SECTION;
	a = art;
	
	if ( a->NATLOE[0] == 'J' )
	{
		return 0;
	}
	for( i=0 ; i < L_DRNAT_NATSTF ; i++ )
	{
		if( a->NATSTF[i] < '0' || a->NATSTF[i] > '9' )
		return 0;
	}
	if ( !strncmp( a->NATSTF, STR_NULL+1, LS_DRNAT_NATSTF ) )
	{
		return 0;
	}
	
	if ( strncmp( a->NATDABE, STR_NULL, LS_DRNAT_NATDABE ) )
		SetzeDatumChar( a->NATDABE, LS_DRNAT_NATDABE );
	if ( strncmp( a->NATDAEN, STR_NULL, LS_DRNAT_NATDAEN ) )
		SetzeDatumChar(a->NATDAEN, LS_DRNAT_NATDAEN);
   DEBUG_SECTION
	   printf("Datumvon: #%*.*s#\n",L_DRNAT_NATDABE,L_DRNAT_NATDABE,a->NATDABE);
	   printf("Datumvon: #%*.*s#\n",L_DRNAT_NATDAEN,L_DRNAT_NATDAEN,a->NATDAEN);
   END_DEBUG_SECTION
	
	if ( strncmp( a->NATBAS1, STR_NULL, LS_DRNAT_NATBAS1 ) ||
		strncmp( a->NATMEN1, STR_NULL, LS_DRNAT_NATMEN1 ) )
	{
		KONDGRUPPENNR = 1;
   DEBUG_SECTION
	   printf("Basis: #%*.*s#\n",LS_DRNAT_NATBAS1,LS_DRNAT_NATBAS1,a->NATBAS1);
	   printf("Menge: #%*.*s#\n",LS_DRNAT_NATMEN1,LS_DRNAT_NATMEN1,a->NATMEN1);
	   printf("Staffel: #%*.*s#\n",L_DRNAT_NATSTF,L_DRNAT_NATSTF,a->NATSTF);
   END_DEBUG_SECTION
		EXEC SQL EXECUTE upd_natra USING
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS1,
	            :a->NATMEN1,
				:a->NATSTF,
	            :KONDGRUPPENNR,
	            :a->NATBAS1;
		ERROR_MSG2( "update artikelnatra1" )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_natra USING
	            :a->NATSTF,
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS1,
	            :a->NATMEN1,
	            :KONDGRUPPENNR;
		   ERROR_MSG2( "insert artikelnatra1" )
		}
	}
	
	if ( strncmp( a->NATBAS2, STR_NULL, LS_DRNAT_NATBAS2 ) ||
	     strncmp( a->NATMEN2, STR_NULL, LS_DRNAT_NATMEN2 ) )
	{
		KONDGRUPPENNR = 1;
		EXEC SQL EXECUTE upd_natra USING
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS2,
	            :a->NATMEN2,
				:a->NATSTF,
	            :KONDGRUPPENNR,
	            :a->NATBAS2;
		ERROR_MSG2( "update artikelnatra2" )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_natra USING
	            :a->NATSTF,
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS2,
	            :a->NATMEN2,
	            :KONDGRUPPENNR;
		   ERROR_MSG2( "insert artikelnatra2" )
		}
	}  
	if ( strncmp( a->NATBAS3, STR_NULL, LS_DRNAT_NATBAS3 ) ||
	     strncmp( a->NATMEN3, STR_NULL, LS_DRNAT_NATMEN3 ) )
	{
		KONDGRUPPENNR = 1;
		EXEC SQL EXECUTE upd_natra USING
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS3,
	            :a->NATMEN3,
				:a->NATSTF,
	            :KONDGRUPPENNR,
	            :a->NATBAS3;
		ERROR_MSG2( "update artikelnatra3" )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_natra USING
	            :a->NATSTF,
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS3,
	            :a->NATMEN3,
	            :KONDGRUPPENNR;
		   ERROR_MSG2( "insert artikelnatra3" )
		}
	}
	if ( strncmp( a->NATBAS4, STR_NULL, LS_DRNAT_NATBAS4 ) ||
	     strncmp( a->NATMEN4, STR_NULL, LS_DRNAT_NATMEN4 ) )
	{
		KONDGRUPPENNR = 1;
		EXEC SQL EXECUTE upd_natra USING
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS4,
	            :a->NATMEN4,
				:a->NATSTF,
	            :KONDGRUPPENNR,
	            :a->NATBAS4;
		ERROR_MSG2( "update artikelnatra4" )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_natra USING
	            :a->NATSTF,
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS4,
	            :a->NATMEN4,
	            :KONDGRUPPENNR;
		   ERROR_MSG2( "insert artikelnatra4" )
		}
	}
	if ( strncmp( a->NATBAS5, STR_NULL, LS_DRNAT_NATBAS5 ) ||
	     strncmp( a->NATMEN5, STR_NULL, LS_DRNAT_NATMEN5 ) )
	{
		KONDGRUPPENNR = 3;
		EXEC SQL EXECUTE upd_natra USING
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS5,
	            :a->NATMEN5,
				:a->NATSTF,
	            :KONDGRUPPENNR,
	            :a->NATBAS5;
		ERROR_MSG2( "update artikelnatra5" )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_natra USING
	            :a->NATSTF,
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS5,
	            :a->NATMEN5,
	            :KONDGRUPPENNR;
		   ERROR_MSG2( "insert artikelnatra5" )
		}
	}
	if ( strncmp( a->NATBAS6, STR_NULL, LS_DRNAT_NATBAS6 ) ||
	     strncmp( a->NATMEN6, STR_NULL, LS_DRNAT_NATMEN6 ) )
	{ 
		KONDGRUPPENNR = 2;
		EXEC SQL EXECUTE upd_natra USING
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS6,
	            :a->NATMEN6,
				:a->NATSTF,
	            :KONDGRUPPENNR,
	            :a->NATBAS6;
		ERROR_MSG2( "update artikelnatra6" )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_natra USING
	            :a->NATSTF,
	            :a->NATDABE,
	            :a->NATDAEN,
	            :a->NATBAS6,
	            :a->NATMEN6,
	            :KONDGRUPPENNR;
		   ERROR_MSG2( "insert artikelnatra6" )
		}
	}
	return OK;
}

int AfterLadeNatra(char *error_msg)
{
	char *fun = "AfterLadeNatra";
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
	EXEC SQL open Cnatra;
	ERROR_MSG2( "open Cnatra ");
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
		EXEC SQL fetch Cnatra;
   		if (sqlca.sqlcode == 100) break; /* NotFound */
   		ERROR_MSG2( "fetch Cnatra ");
		EXEC SQL EXECUTE set_natra;
   		ERROR_MSG2( "set_natra ");
	}
	EXEC SQL commit work;
   	ERROR_MSG2( "commit work2 ");
	EXEC SQL close Cnatra;
	ERROR_MSG2( "close Cnatra ");
	return OK;
}

int DelNotUpd(char *error_msg)
{
	char *fun = "DelNotUpd";
	int comz;
	EXEC SQL begin work;
	ERROR_MSG2( "begin work ");
	EXEC SQL open Cnatra2;
	ERROR_MSG2( "open Cnatra2 ");
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
		EXEC SQL fetch Cnatra2;
   		if (sqlca.sqlcode == 100) break; /* NotFound */
   		ERROR_MSG2( "fetch Cnatra2 ");
		EXEC SQL EXECUTE del_natra;
   		ERROR_MSG2( "del_natra ");
	}
	EXEC SQL commit work;
   	ERROR_MSG2( "commit work2 ");
	EXEC SQL close Cnatra2;
	ERROR_MSG2( "close Cnatra2 ");
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

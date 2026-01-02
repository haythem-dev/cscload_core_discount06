/* loadroutes.cxx */

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadroutes"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
/* #include "tour.h"
#include "tourplantag.h"
#include "routetimes.h"
#include "custroutetimes.h"
#include "custrouteweek.h" */
#include "dkktu.h"
#include "pplib/allg.h"
#include "errno.h"
#include "callplanmaintenance.h"
#include "callplanundertake.h"
#include "libtpld/dadedb.h"
/*#include "rrds.h"*/
EXEC SQL include sqlca;

#undef NULL

#define P_DKKTU           "/transfer/pos/data/UCATPH1/DKKTU.P"
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

 FILE *dkktudat;
 char pfaddkktu[81];
 char log_file [300 + 1];
 int debug_enabled   = NO;
 int DateiNr = 0;                 /* XVSAM */
 short haus = 0;
 char chaus[3];
	
	EXEC SQL BEGIN DECLARE SECTION;
	char datenbank[60];
	char nachttour[7] = {"475901"};
	long dbzeit;
	long dbdate;
	long olddate;
	long actdate;
	long futurdate;
	short oldwd;
	short actwd;
	short futurwd;
	EXEC SQL END DECLARE SECTION;

 
 /***** DECLARATION **********************************************************/
 int main( int, char ** );
 void PrintMsg( char *fun, char *error_msg, char mld, int rc );
 void WriteLogInfo( char *error_msg, char mld, int rc );
 int StarteLoadTouren(int datum,int tourtag, char *error_msg );
 int PrepareLoadTouren(char *error_msg);
 int PrepareLoadTourWoche(char *error_msg);
 int PrepareLoadTourPlan(char *error_msg);
 int PrepareLoadTourPlanWoche(char *error_msg);
 int PrepareLoadTourConsTime(char *error_msg);
 int PrepareLoadTourPlanConsTime(char *error_msg);
 int PrepareLoadPotentialTours(char *error_msg);
 int LadeTouren(struct O_DKKTU *tour, int datum,int tourtag, char *error_msg);
 int LadeTourPlan(struct O_DKKTU *tour, int datum,int tourtag, char *error_msg);
 int LadeTourPlanDatum(struct O_DKKTU *tour, int datum,int tourtag, char *error_msg);
 int LadeTourWoche(struct O_DKKTU *tour, char *error_msg);
 int LadeTourPlanWoche(struct O_DKKTU *tour, char *error_msg);
 int LadeTourConsTime(struct O_DKKTU *tour, int datum,int tourtag, char *error_msg);
 int LadeTourConsTimeDatum(struct O_DKKTU *tour, int datum,int tourtag, char *error_msg);
 int LadeTourPlanConsTime(struct O_DKKTU *tour, int datum,int tourtag, char *error_msg);
 int LadeTourPlanConsTimeDatum(struct O_DKKTU *tour, int datum,int tourtag, char *error_msg);
 int LadePotentialTours(struct O_DKKTU *tour, char *error_msg);
 int DeleteOldConsTime(char *error_msg);
 int DeleteOldPlanConsTime(char *error_msg);
 int AfterLoadTouren( char *error_msg);
 int AfterLoadTourWoche(char *error_msg);
 int AfterLoadTourPlan(char *error_msg);
 int AfterLoadTourPlanWoche(char *error_msg);
 int AfterLoadTourConsTime(char *error_msg);
 int AfterLoadTourPlanConsTime(char *error_msg);
 int AfterLoadPotentialTours(char *error_msg);
 int DelNotUpdatedTourPlan( char *error_msg);
 int SetNotUpdatedTourPlan( char *error_msg);
 int DelNotUpdatedTourPlanWoche( char *error_msg);
 int SetNotUpdatedTourPlanWoche( char *error_msg);
 int DelNotUpdatedPotentialTours( char *error_msg);
 int SetNotUpdatedPotentialTours( char *error_msg);
 int HolePseudoTour( char *error_msg);
 int PrepareSetKAtourplantag( char *error_msg);
 int SetKAtourplantag( long Idf, long datum, char *tourid, char *error_msg);
 static int GetDay( char * );
 int TourPlanWoche( struct O_DKKTU *tour, char *tag, short weekday, char *error_msg);
 int TourWoche( struct O_DKKTU *tour, char *tag, short weekday, char *error_msg);
 
 /***** MAIN *****************************************************************/

 int main( int argc, char **argv  )
 {
   char 	error_msg[81];
   char 	*schalter;
   int 		i;
   int 		skip;
   int 		datum = 0;
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
       	else if ( !strcmp( schalter, "-ld" ) )
	  	{
	  		datum = atol(argv[i + 1]);
			if(AllgGetWeekDay(datum,error_msg) <0)
    		{
 				PrintMsg( fun, error_msg, FEHL, -1 );
   				PrintMsg( fun, "ENDE", FEHL, 0 );
				return 2;
    		}
	  		skip = YES;
	  	}
		else if ( !strcmp( schalter, "-file" ) )
		{
			i++;
			sprintf( pfaddkktu, "%s", argv[i] );
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			sprintf( datenbank, "%s", argv[i] );
		}
        else if ( !strcmp( schalter, "-wd" ) )
	    {
			if ( ( tourtag = GetDay( argv[i + 1] ) ) == -1 )
				skip = ERROR;
			skip = YES;
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
			return 0;
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
	      " [ -ld 19970314]\n\t"
	      " [ -la]\n\t"
	      "	[ -wd <(MO-SO)>]\n"
		  , argv[0] );
      return 2;
      }
	
	sprintf(chaus,"%d",haus);

	DEBUG_SECTION
		fprintf(stderr,"Wochentag input: %d \n",tourtag);
		fprintf(stderr,"Datum input: %d \n",datum);
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
	dbzeit = AllgGetTime();


   if ( StarteLoadTouren(datum, tourtag, error_msg) != 0 )
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
   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.9s %s",
	    mld,
	    haus,
		zeit->tm_mday,
        zeit->tm_mon + 1,
        (zeit->tm_year+1900)%100,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
	    pid,
	    "loadroutes",
	    fun );

   fprintf(fp,"%s\n", error_msg );
   fclose(fp);
}

/***** STARTE DAS LADEN DER TOUREN-TABELLE *************************************/

 int StarteLoadTouren(int datum, int tourtag, char *error_msg )
{
	int zaehler, rc;
	int ind;
	char *fun = "StarteLoadTouren";
	
	EXEC SQL BEGIN DECLARE SECTION;
	short int filialnr;
	char cTourid[7];
	char cAart[3];
	char str[200];
	EXEC SQL END DECLARE SECTION;

	char msg[80];
	int	datum_folge;
	int tourtag_folge;
	char *XVSAM;
    tError stError;
	char szHaus[3];
	struct O_DKKTU ktu;
	static const int DKKTU_LEN = sizeof(ktu);
	mcallplanloadS srvLoad;
	mholidayS holiday;
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
	
	if ( haus == 0 )  /* filialnr wurde nicht über schalter -lf bekanntgegeben (standard)*/
	{
		exec sql select filialnr into :filialnr from filiale;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		{
			sprintf (error_msg, "select filiale: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
			PrintMsg( fun, error_msg, FEHL, -1 );
			filialnr = 0;
		}
		haus = filialnr;
	}
	holiday.FILIALNR = haus;
	if ( (rc=(retClient)Mholiday_StartBrowse(&holiday, &stError, FALSE)) == IS_ERROR )
		return rc;
	
	dbdate = olddate = AllgGetDate();
	for(;;)
	{
/*		if( AllgGetWeekDay(olddate,error_msg) == ALLG_SONNTAG)
		{
			datum_folge = AllgAddDate(olddate, 1, error_msg);
		}
*/		holiday.ANTEIL = olddate;
		if ( Mholiday_IsHoliday( &holiday, &stError, FALSE ) != IS_OK )
			break;
		olddate = AllgAddDate(olddate, 1, error_msg);
	}

	/* aktueller Tag */
	srvLoad.VERTRIEBSZENTRUMNR = haus;
	srvLoad.LADEDATUM = datum;
	srvLoad.LADEKIPPZEIT = 120000;
	if ( Mcallplanload_GetInitializeData( &srvLoad, &stError, FALSE ) == IS_ERROR )
	{
		return CheckSql( fun, &stError, "%s", stError.spError );
	}
	if(datum == 0 ) datum = srvLoad.LADEDATUM;
	actdate = srvLoad.LADEDATUM;
	if(actdate < olddate) olddate = actdate;
	if (tourtag == -1) tourtag = AllgGetWeekDay(actdate,error_msg);

	actwd = tourtag;

	DEBUG_SECTION
		fprintf(stderr,"Wochentag: %d \n",tourtag);
		fprintf(stderr,"Datum: %d \n",datum);
	END_DEBUG_SECTION

	/* folge Tag */
	datum_folge = ppGAddDate(datum, 1, error_msg);
	for(;;)
	{
/*		if( AllgGetWeekDay(datum_folge,error_msg) == ALLG_SONNTAG)
		{
			datum_folge = AllgAddDate(datum_folge, 1, error_msg);
		}
*/		holiday.ANTEIL = datum_folge;
		if ( Mholiday_IsHoliday( &holiday, &stError, FALSE ) != IS_OK )
			break;
		datum_folge = AllgAddDate(datum_folge, 1, error_msg);
	}
	tourtag_folge = AllgGetWeekDay(datum_folge,error_msg);
	futurdate = datum_folge;
	futurwd = tourtag_folge;
	oldwd = AllgGetWeekDay(olddate,error_msg);

	DEBUG_SECTION
		fprintf(stderr,"Wochentag_folge: %d \n",tourtag_folge);
		fprintf(stderr,"Datum_folge: %d \n",datum_folge);
	END_DEBUG_SECTION

	filialnr = haus;

	sprintf( msg, "started with %d (%d) / Folge %d (%d)", datum, tourtag, datum_folge, tourtag_folge );
	PrintMsg( "Main", msg, HINW, 0 );

	if( (rc = PrepareLoadTouren(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = PrepareLoadTourWoche(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = PrepareLoadTourPlan(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = PrepareLoadTourPlanWoche(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = PrepareLoadTourConsTime(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = PrepareLoadTourPlanConsTime(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = PrepareLoadPotentialTours(error_msg)) != 0 )
	{
		return rc;	
	}
	
	if ( ( dkktudat = fopen( pfaddkktu, "r" ) ) == (char *)0 )
	{
		PrintMsg( fun, pfaddkktu, FEHL, 0 );
		PrintMsg( fun, "DKKTU nicht vorhanden", FEHL, 0 );
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

		if(fread( (	struct O_DKKTU*) &ktu ,DKKTU_LEN+1, 1 , dkktudat ) == 0)
        {
		   	DEBUG_SECTION
			fprintf(stderr,"%d Saetze gelesen\n",zaehler);
   			END_DEBUG_SECTION
			break;
	 	}
	   	DEBUG_SECTION
		fprintf(stderr,"%s\n",&ktu);
		END_DEBUG_SECTION
				
		/* neue Tabelle schreiben */
		
		sprintf( szHaus, "%02d", haus );
		if(strncmp(ktu.KTUFIL,szHaus,L_DKKTU_KTUFIL))
		{
			if(!strncmp(szHaus,"49",L_DKKTU_KTUFIL))
			{
				if(!strncmp(ktu.KTUFIL,"48",L_DKKTU_KTUFIL))
				{
					ktu.KTUFIL[1] = '9';
				}
			}
			else
			{
				continue;
			}
		}
		
		if ( !strncmp(ktu.KTUIDF,"0000000",L_DKKTU_KTUIDF) )
		{
			if ( (rc = LadeTouren(&ktu, datum, tourtag, error_msg)) < 0) return rc;
			if ( (rc = LadeTourWoche(&ktu, error_msg)) < 0) return rc;
			if ( (rc = LadeTourConsTime(&ktu, datum, tourtag, error_msg)) < 0) return rc;
		}
		else
		{
			if ( (rc = LadeTourPlanConsTime(&ktu, datum, tourtag, error_msg)) < 0) return rc;
			if ( (rc = LadeTourPlan(&ktu, datum, tourtag, error_msg)) < 0) return rc;
			if ( (rc = LadeTourPlanWoche(&ktu, error_msg)) < 0) return rc;
			if ( (rc = LadePotentialTours(&ktu, error_msg)) < 0) return rc;
		}
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

	fclose( dkktudat);

	if( (rc = AfterLoadTouren(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = AfterLoadTourWoche(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = AfterLoadTourPlan(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = AfterLoadTourPlanWoche(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = AfterLoadTourConsTime(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = AfterLoadTourPlanConsTime(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = AfterLoadPotentialTours(error_msg)) != 0 )
	{
		return rc;	
	}

	return OK;
}

int PrepareLoadTouren(char *error_msg)
{
	char *fun = "PrepareLoadTouren";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select kippzeit ");
	strcat(str,"from tour ");          
	strcat(str,"where ");
	strcat(str,"FILIALNR = ? ");          
	strcat(str,"and TOURID = ? ");          
	strcat(str,"for update " );

	EXEC SQL PREPARE sel_tour FROM :str;
	ERROR_MSG2( "prepare sel_tour " );
	exec sql declare Cseltour cursor with hold for sel_tour;

	strcpy(str,"update tour set ");
	strcat(str,"KIPPZEIT = ? ");          
	strcat(str,",CHECKTIMETOTOUR = ? ");          
	strcat(str,",SCHECKORDER = ? ");
	strcat(str,",KARENZZEIT = ? ");
	strcat(str,"where current of Cseltour " );

	EXEC SQL PREPARE upd_tour FROM :str;
	ERROR_MSG2( "prepare upd_tour" )

	return 0;
}

int PrepareLoadTourWoche(char *error_msg)
{
	char *fun = "PrepareLoadTourWoche";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"update tourplanwoche set ");
	strcat(str,"KARENZZEIT = ? ");
	strcat(str,"where ");
	strcat(str,"FILIALNR = ? ");          
	strcat(str,"and TOURID = ? ");          
	strcat(str,"and WEEKDAY = ? ");          

	EXEC SQL PREPARE upd_tourwoche FROM :str;
	ERROR_MSG2( "prepare upd_tourwoche" )

	return 0;
}

int PrepareLoadTourPlan(char *error_msg)
{
	char *fun = "PrepareLoadTourPlan";
	int rc;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	if((rc = HolePseudoTour( error_msg )) != 0) return rc;
	if((rc = PrepareSetKAtourplantag( error_msg )) != 0) return rc;

	strcpy(str,"UPDATE tourplantag SET ");
	strcat(str,"IDFNR=?,");
	strcat(str,"DATUMKOMMI=?,");
	strcat(str,"TOURID=?,");
	strcat(str,"REIHENFOLGENR=?,");
	strcat(str,"FAHRTZEIT=?,");
	strcat(str,"BEMERKUNGEN=?,");
	strcat(str,"KZUPD=?,");
	strcat(str,"ISTVERBUNDTOUR=?,");
	strcat(str,"VERTRIEBSZENTRUMNR=?,");
	strcat(str,"KUNDENNR=?,");
	strcat(str,"TM_DATE=?,");
	strcat(str,"TM_TIME=?,");
	strcat(str,"LOGINID=?,");
	strcat(str,"CHANGEID=?,");
	strcat(str,"KIPPZEIT=?,");
	strcat(str,"TOURINAKTIV=?,");
	strcat(str,"KZAUTOZUORD=?,");
	strcat(str,"ISTVATOUR=?,");
	strcat(str,"KDAUFTRAGART=?");
	strcat(str,",CHECKTIMETOTOUR = ? ");
	strcat(str,",SCHECKORDER = ? ");
	strcat(str,",ISBTM = ? ");
	strcat(str,",ISKK = ? ");
	strcat(str,",ISK08 = ? ");
	strcat(str,",ISK20 = ? ");
	strcat(str,",RETURNSTOUR = ? ");
	strcat(str,",TRANSPEXCLPSYCHO = ? ");
	strcat(str," WHERE ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");
	strcat(str," AND ");
	strcat(str,"KUNDENNR = ?");
	strcat(str," AND ");
	strcat(str,"DATUMKOMMI = ?");
	strcat(str," AND ");
	strcat(str,"TOURID = ?");

	EXEC SQL PREPARE upd_tourplantag FROM :str;
	ERROR_MSG2( "prepare upd_tourplantag" )

	strcpy(str,"INSERT INTO tourplantag (");
	strcat(str,"IDFNR,");          
	strcat(str,"DATUMKOMMI,");          
	strcat(str,"TOURID,");          
	strcat(str,"REIHENFOLGENR,");          
	strcat(str,"FAHRTZEIT,");          
	strcat(str,"BEMERKUNGEN,");          
	strcat(str,"KZUPD,");          
	strcat(str,"ISTVERBUNDTOUR,");          
	strcat(str,"VERTRIEBSZENTRUMNR,");          
	strcat(str,"KUNDENNR,");          
	strcat(str,"TM_DATE,");          
	strcat(str,"TM_TIME,");          
	strcat(str,"LOGINID,");          
	strcat(str,"CHANGEID,");          
	strcat(str,"KIPPZEIT,");
	strcat(str,"TOURINAKTIV,");
	strcat(str,"KZAUTOZUORD,");
	strcat(str,"ISTVATOUR,");
	strcat(str,"KDAUFTRAGART");
	strcat(str,",CHECKTIMETOTOUR");
	strcat(str,",SCHECKORDER");
	strcat(str,",ISBTM");
	strcat(str,",ISKK");
	strcat(str,",ISK08");
	strcat(str,",ISK20");
	strcat(str,",RETURNSTOUR");
	strcat(str,",TRANSPEXCLPSYCHO");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,?,\"\",\"1\",?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,? )");

	EXEC SQL PREPARE ins_tourtag FROM :str;
    if (sqlca.sqlcode < 0 )
    {
       	sprintf(error_msg, "prepare ins_tourtag %ld", sqlca.sqlcode);
  		PrintMsg( fun, error_msg, FEHL, -1 );
       	return -1;
    }
	 
	if((rc = SetNotUpdatedTourPlan( error_msg )) != 0) return rc;

	return OK;	 
}

int PrepareLoadTourPlanWoche(char *error_msg)
{
	char *fun = "PrepareLoadTourPlanWoche";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;
	
	strcpy(str,"INSERT INTO tourplantagwoche (");
	strcat(str,"VERTRIEBSZENTRUMNR,");
	strcat(str,"KUNDENNR,");
	strcat(str,"TOURID,");          
	strcat(str,"TAGESTYP,");
	strcat(str,"KZUPD,");
	strcat(str,"WEEKDAY,");
	strcat(str,"ISTVERBUNDTOUR,");          
	strcat(str,"KDAUFTRAGART,");
	strcat(str,"FAHRTZEIT");
	strcat(str,",ISBTM");
	strcat(str,",ISKK");
	strcat(str,",ISK08");
	strcat(str,",ISK20");
	strcat(str,",RETURNSTOUR");
	strcat(str,",TRANSPEXCLPSYCHO");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,'1',?,?,?,?,?,?,?,?,?,? )");

	EXEC SQL PREPARE ins_tourplanwoche FROM :str;
	ERROR_MSG2( "prepare ins_tourplanwoche " );

	strcpy(str,"UPDATE tourplantagwoche SET ");
	strcat(str,"KZUPD = '1',");
	strcat(str,"ISTVERBUNDTOUR = ?,");
	strcat(str,"KDAUFTRAGART = ?,");
	strcat(str,"FAHRTZEIT = ?");
	strcat(str,",ISBTM = ? ");
	strcat(str,",ISKK = ? ");
	strcat(str,",ISK08 = ? ");
	strcat(str,",ISK20 = ? ");
	strcat(str,",RETURNSTOUR = ? ");
	strcat(str,",TRANSPEXCLPSYCHO = ? ");
	strcat(str," WHERE");
	strcat(str," VERTRIEBSZENTRUMNR = ?");
	strcat(str," AND KUNDENNR = ?");
	strcat(str," AND WEEKDAY = ?");
	strcat(str," AND TOURID = ?");

	EXEC SQL PREPARE upd_tourplanwoche FROM :str;
	ERROR_MSG2( "prepare upd_tourplanwoche" )

	if( (rc = SetNotUpdatedTourPlanWoche(error_msg)) != 0) return rc; 
	 
	return 0;
}

int PrepareLoadTourConsTime(char *error_msg)
{
	char *fun = "PrepareLoadTourConsTime";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"insert into tourconstime (");
	strcat(str,"FILIALNR,");
	strcat(str,"TOURID,");          
	strcat(str,"DATUMKOMMI,");
	strcat(str,"CONSTIME,");
	strcat(str,"PROCESSSTATE");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,'0' )");

	EXEC SQL PREPARE ins_tourconstime FROM :str;
	ERROR_MSG2( "prepare ins_tourconstime " );

	strcpy(str,"delete from tourconstime ");
	strcat(str,"where ");
	strcat(str,"FILIALNR = ? ");
	strcat(str,"and ");
	strcat(str,"TOURID = ?");          
	strcat(str,"and ");
	strcat(str,"DATUMKOMMI = ?");          

	EXEC SQL PREPARE del_tourconstime FROM :str;
	ERROR_MSG2( "prepare del_tourconstime " );

	return 0;
}

int PrepareLoadTourPlanConsTime(char *error_msg)
{
	char *fun = "PrepareLoadTourPlanConsTime";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;
	

	strcpy(str,"insert into tourplanconstime (");
	strcat(str,"VERTRIEBSZENTRUMNR,");
	strcat(str,"KUNDENNR,");
	strcat(str,"TOURID,");          
	strcat(str,"DATUMKOMMI,");
	strcat(str,"CONSTIME,");
	strcat(str,"PROCESSSTATE");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,?,'0' )");

	EXEC SQL PREPARE ins_tourplantime FROM :str;
	ERROR_MSG2( "prepare ins_tourplantime " );

	strcpy(str,"delete from tourplanconstime ");
	strcat(str,"where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ? ");
	strcat(str,"and ");
	strcat(str,"KUNDENNR = ? ");
	strcat(str,"and ");
	strcat(str,"TOURID = ?");          
	strcat(str,"and ");
	strcat(str,"DATUMKOMMI = ?");          

	EXEC SQL PREPARE del_tourplantime FROM :str;
	ERROR_MSG2( "prepare del_tourplantime " );

	return 0;
}

int PrepareLoadPotentialTours(char *error_msg)
{
	char *fun = "PrepareLoadPotentialTours";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;
	

	strcpy(str,"insert into potentialcustomertours (");
	strcat(str,"branchno,");
	strcat(str,"customerno,");
	strcat(str,"TOURID,");          
	strcat(str,"updatesign");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,'1' )");

	EXEC SQL PREPARE ins_potentialtours FROM :str;
	ERROR_MSG2( "prepare ins_potentialtours " );

	strcpy(str,"update potentialcustomertours ");
	strcat(str,"set updatesign = '1' ");
	strcat(str,"where ");
	strcat(str,"branchno = ? ");
	strcat(str,"and ");
	strcat(str,"customerno = ? ");
	strcat(str,"and ");
	strcat(str,"TOURID = ?");          

	EXEC SQL PREPARE upd_potentialtours FROM :str;
	ERROR_MSG2( "prepare upd_potentialtours " );

	if((rc = SetNotUpdatedPotentialTours( error_msg )) != 0) return rc;

	return 0;
}
 
int LadeTouren(struct O_DKKTU *tour, int datum,int tourtag, char *error_msg)
{
	char *fun = "LadeTouren";

	char huelse[80];

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	long ldatum;
	long kippzeit;
	short karenz;
	EXEC SQL END DECLARE SECTION;

	a= tour;
	ldatum = datum;

	sprintf(huelse,"%3.3s",a->KTUKARENZ);
	karenz = atoi(huelse);

	EXEC SQL open Cseltour USING
					:a->KTUFIL,
					:a->KTUTOUR
					;
	if (sqlca.sqlcode != 0)  /* Datenbankfehler */
   	{
		sprintf (error_msg, "open: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		PrintMsg( fun, error_msg, FEHL, ERROR );
		return ERROR;
	}

	for(;;)
	{
		EXEC SQL fetch Cseltour into :kippzeit;
		if ( sqlca.sqlcode == 100 ) break;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
			sprintf (error_msg, "fetch: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}

		if(!strncmp(a->KTUAEPR,"     ",5) || !strncmp(a->KTUAEPR,"40404",5)) memset(a->KTUAEPR,'0',5);
		if(a->KTUEPK[0] == 'J' || a->KTUEPK[0] == '1') a->KTUEPK[0] = '1';
		else  a->KTUEPK[0] = '0';
		EXEC SQL EXECUTE upd_tour USING
			:a->KTUKIPPZEIT2,
			:a->KTUAEPR,
			:a->KTUEPK,
			:karenz;

		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
			sprintf (error_msg, "update: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
	}
	return OK;
}
 
int LadeTourPlan(struct O_DKKTU *tour, int datum, int tourtag, char *error_msg)
{
	char *fun = "LadeTourPlan";
	char huelse[81];
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	char kzautozuord[2];
	char tourinaktiv[2];
	long ldatum;
	EXEC SQL END DECLARE SECTION;

	a= tour;
	ldatum = datum;

	if(olddate != actdate)
	{
		if ( (rc = LadeTourPlanDatum(a, olddate, oldwd, error_msg)) < 0) return rc;
	}
	if ( (rc = LadeTourPlanDatum(a, actdate, actwd, error_msg)) < 0) return rc;
	if ( (rc = LadeTourPlanDatum(a, futurdate, futurwd, error_msg)) < 0) return rc;

	sprintf(huelse,"%*.*s",L_DKKTU_KTUIDF,L_DKKTU_KTUIDF,a->KTUIDF);
	if ((rc = SetKAtourplantag(atol(huelse),ldatum,a->KTUTOUR,error_msg)) != 0) return rc;

	return OK;
}
 
int LadeTourPlanDatum(struct O_DKKTU *tour, int datum, int tourtag, char *error_msg)
{
	char *fun = "LadeTourPlanDatum";
	char huelse[81];
	int rc = 0;
	int test0 = 0;
	int test1 = 0;
	int test2 = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	char kzautozuord[2];
	char tourinaktiv[2];
	long ldatum;
	short isBTM;
	short isKK;
	short isK08;
	short isK20;
	short isRT;
	short isPST;	// Transportausschluss für psychotrope Stoffe
	EXEC SQL END DECLARE SECTION;

	a= tour;
	ldatum = datum;

	strcpy(kzautozuord,"1");
	strcpy(tourinaktiv,"0");

	if ( tourtag == ALLG_SONNTAG    && a->KTUSO[0] != 'J')
	{
		if (!strncmp(a->KTUTOUR,nachttour,4) || a->KTUSO[0] == 'S')
		{
			strcpy(kzautozuord,"0");
		}
		else
		{
			strcpy(tourinaktiv,"1");
		}
	}
	if ( tourtag == ALLG_MONTAG     && a->KTUMO[0] != 'J')
	{
		if (!strncmp(a->KTUTOUR,nachttour,4) || a->KTUMO[0] == 'S')
		{
			strcpy(kzautozuord,"0");
		}
		else
		{
			strcpy(tourinaktiv,"1");
		}
	}
	if ( tourtag == ALLG_DIENSTAG   && a->KTUDI[0] != 'J')
	{
		if (!strncmp(a->KTUTOUR,nachttour,4) || a->KTUDI[0] == 'S')
		{
			strcpy(kzautozuord,"0");
		}
		else
		{
			strcpy(tourinaktiv,"1");
		}
	}
	if ( tourtag == ALLG_MITTWOCH   && a->KTUMI[0] != 'J')
	{
		if (!strncmp(a->KTUTOUR,nachttour,4) || a->KTUMI[0] == 'S')
		{
			strcpy(kzautozuord,"0");
		}
		else
		{
			strcpy(tourinaktiv,"1");
		}
	}
	if ( tourtag == ALLG_DONNERSTAG && a->KTUDO[0] != 'J')
	{
		if (!strncmp(a->KTUTOUR,nachttour,4) || a->KTUDO[0] == 'S')
		{
			strcpy(kzautozuord,"0");
		}
		else
		{
			strcpy(tourinaktiv,"1");
		}
	}
	if ( tourtag == ALLG_FREITAG    && a->KTUFR[0] != 'J')
	{
		if (!strncmp(a->KTUTOUR,nachttour,4) || a->KTUFR[0] == 'S')
		{
			strcpy(kzautozuord,"0");
		}
		else
		{
			strcpy(tourinaktiv,"1");
		}
	}
	if ( tourtag == ALLG_SONNABEND  && a->KTUSA[0] != 'J')
	{
		if (!strncmp(a->KTUTOUR,nachttour,4) || a->KTUSA[0] == 'S')
		{
			strcpy(kzautozuord,"0");
		}
		else
		{
			strcpy(tourinaktiv,"1");
		}
	}

	if ( a->KTUVBTOUR[0] != 'J' &&  a->KTUVBTOUR[0] != '1' )
		a->KTUVBTOUR[0] = '0';
	else
		a->KTUVBTOUR[0] = '1';

	if ( a->KTUVBTVSA[0] != 'J' &&  a->KTUVBTVSA[0] != '1' )
		a->KTUVBTVSA[0] = '0';
	else
		a->KTUVBTVSA[0] = '1';

	if ( a->KTUGPTOUR[0] != 'J' &&  a->KTUGPTOUR[0] != '1' )
		isBTM = 0;
	else
		isBTM = 1;

	if ( a->KTUKK[0] != 'J' &&  a->KTUKK[0] != '1' )
		isKK = 0;
	else
		isKK = 1;

	if ( a->KTUK08[0] != 'J' &&  a->KTUK08[0] != '1' )
		isK08 = 0;
	else
		isK08 = 1;

	if ( a->KTUK20[0] != 'J' &&  a->KTUK20[0] != '1' )
		isK20 = 0;
	else
		isK20 = 1;

	if (a->KTURETTOUR[0] != 'J' &&  a->KTURETTOUR[0] != '1')
		isRT = 0;
	else
		isRT = 1;

	if (a->KTUPST[0] != 'J' && a->KTUPST[0] != '1')
		isPST = 0;
	else
		isPST = 1;

	if(!strncmp(a->KTUAEPR,"     ",5) || !strncmp(a->KTUAEPR,"40404",5)) memset(a->KTUAEPR,'0',5);
	if(a->KTUEPK[0] == 'J' || a->KTUEPK[0] == '1') a->KTUEPK[0] = '1';
	else  a->KTUEPK[0] = '0';

	EXEC SQL EXECUTE upd_tourplantag USING :a->KTUIDF,
								:ldatum,
								:a->KTUTOUR,
								:a->KTUTFOLGE,
								:a->KTUTDAUER2,
								' ',
								'1',
								:a->KTUVBTOUR,
                                :a->KTUFIL,
								:a->KTUIDF,
								:dbdate,
								:dbzeit,
								'1',
								'U',
								:a->KTUKIPPZEIT2,
								:tourinaktiv,
								:kzautozuord,
                                :a->KTUVBTVSA,
                                :a->KTUAART,
								:a->KTUAEPR,
								:a->KTUEPK,
								:isBTM,
								:isKK,
								:isK08,
								:isK20,
								:isRT,
								:isPST,
                                :a->KTUFIL,
								:a->KTUIDF,
								:ldatum,
								:a->KTUTOUR
								;
	if (sqlca.sqlcode < 0)
	{	
		sprintf( error_msg, "IDF: %s",a->KTUIDF);
		PrintMsg( fun, error_msg, FEHL, -1 );
	}
	ERROR_MSG2( "upd tourplantag1:" )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
   		EXEC SQL EXECUTE ins_tourtag USING
								:a->KTUIDF,
								:ldatum,
								:a->KTUTOUR,
								:a->KTUTFOLGE,
								:a->KTUTDAUER2,
								:a->KTUVBTOUR,
                                :a->KTUFIL,
								:a->KTUIDF,
								:ldatum,
								:dbzeit,
								'1',
								'I',
								:a->KTUKIPPZEIT2,
								:tourinaktiv,
								:kzautozuord,
                                :a->KTUVBTVSA,
                                :a->KTUAART,
								:a->KTUAEPR,
								:a->KTUEPK,
								:isBTM,
								:isKK,
								:isK08,
								:isK20,
								:isRT,
								:isPST
								;
		ERROR_MSG2( "insert tourplantag1:" )
	}

	return OK;
}

int LadeTourPlanWoche(struct O_DKKTU *tour, char *error_msg)
{
	char *fun = "LadeTourPlanWoche";

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	char tourtag[3];
	short sWeekday;
	EXEC SQL END DECLARE SECTION;
	a= tour;

	if ( a->KTUSO[0] == 'J')
	{
		strcpy(tourtag,"SO");
		sWeekday = 0;
		TourPlanWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUMO[0] == 'J')
	{
		strcpy(tourtag,"MO"); 
		sWeekday = 1;
		TourPlanWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUDI[0] == 'J')
	{
		strcpy(tourtag,"DI"); 
		sWeekday = 2;
		TourPlanWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUMI[0] == 'J')
	{
		strcpy(tourtag,"MI"); 
		sWeekday = 3;
		TourPlanWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUDO[0] == 'J')
	{
		strcpy(tourtag,"DO"); 
		sWeekday = 4;
		TourPlanWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUFR[0] == 'J')
	{
		strcpy(tourtag,"FR"); 
		sWeekday = 5;
		TourPlanWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUSA[0] == 'J')
	{
		strcpy(tourtag,"SA"); 
		sWeekday = 6;
		TourPlanWoche(a,tourtag, sWeekday,error_msg);
	}
	return OK;
}

int LadeTourWoche(struct O_DKKTU *tour, char *error_msg)
{
	char *fun = "LadeTourWoche";

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	char tourtag[3];
	short sWeekday;
	EXEC SQL END DECLARE SECTION;
	a= tour;

	if ( a->KTUSO[0] == 'J')
	{
		strcpy(tourtag,"SO");
		sWeekday = 0;
		TourWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUMO[0] == 'J')
	{
		strcpy(tourtag,"MO"); 
		sWeekday = 1;
		TourWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUDI[0] == 'J')
	{
		strcpy(tourtag,"DI"); 
		sWeekday = 2;
		TourWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUMI[0] == 'J')
	{
		strcpy(tourtag,"MI"); 
		sWeekday = 3;
		TourWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUDO[0] == 'J')
	{
		strcpy(tourtag,"DO"); 
		sWeekday = 4;
		TourWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUFR[0] == 'J')
	{
		strcpy(tourtag,"FR"); 
		sWeekday = 5;
		TourWoche(a,tourtag, sWeekday,error_msg);
	}

	if ( a->KTUSA[0] == 'J')
	{
		strcpy(tourtag,"SA"); 
		sWeekday = 6;
		TourWoche(a,tourtag, sWeekday,error_msg);
	}
	return OK;
}

int LadeTourConsTime(struct O_DKKTU *tour, int datum, int tourtag, char *error_msg)
{
	char *fun = "LadeTourConsTime";
	long tourzeit,conszeit,minuten;
	char huelse[81];
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	long lZeit;
	long ldatum;
	EXEC SQL END DECLARE SECTION;

	a= tour;

	if(olddate != actdate)
	{
		if ( (rc = LadeTourConsTimeDatum(a, olddate, oldwd, error_msg)) < 0) return rc;
	}
	if ( (rc = LadeTourConsTimeDatum(a, actdate, actwd, error_msg)) < 0) return rc;
	if ( (rc = LadeTourConsTimeDatum(a, futurdate, futurwd, error_msg)) < 0) return rc;

	return OK;
}

int LadeTourConsTimeDatum(struct O_DKKTU *tour, int datum, int tourtag, char *error_msg)
{
	char *fun = "LadeTourConsTimeDatum";
	long tourzeit,conszeit,minuten;
	char huelse[81];

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	long lZeit;
	long ldatum;
	EXEC SQL END DECLARE SECTION;

	a= tour;
	ldatum = datum;

	sprintf(huelse,"%*.*s",L_DKKTU_KTUTOUR,L_DKKTU_KTUTOUR,a->KTUTOUR);
	tourzeit = (atol(huelse)/100)*100;

	/* constimes auch für nicht aktive touren laden
	if ( tourtag == ALLG_SONNTAG	&& a->KTUSO[0] != 'J')	return OK;
	if ( tourtag == ALLG_MONTAG		&& a->KTUMO[0] != 'J')	return OK;
	if ( tourtag == ALLG_DIENSTAG	&& a->KTUDI[0] != 'J')	return OK;
	if ( tourtag == ALLG_MITTWOCH	&& a->KTUMI[0] != 'J')	return OK;
	if ( tourtag == ALLG_DONNERSTAG	&& a->KTUDO[0] != 'J')	return OK;
	if ( tourtag == ALLG_FREITAG	&& a->KTUFR[0] != 'J')	return OK;
	if ( tourtag == ALLG_SONNABEND	&& a->KTUSA[0] != 'J')	return OK;
	*/

	EXEC SQL EXECUTE del_tourconstime USING
							:a->KTUFIL,
							:a->KTUTOUR,
							:ldatum
							;
	ERROR_MSG2( "delete tourconstime" )

	if( strncmp(a->KTUAUFZFZ1,"000",3) )
   	{
		sprintf(huelse,"%*.*s",L_DKKTU_KTUAUFZFZ1,L_DKKTU_KTUAUFZFZ1,a->KTUAUFZFZ1);
		minuten = atol(huelse);
		conszeit = (((minuten/60)*100) + (minuten%60)) * (-100);
		AllgAddTime(tourzeit,conszeit,&lZeit);
		lZeit = lZeit/100;
		EXEC SQL EXECUTE ins_tourconstime USING
                                :a->KTUFIL,
								:a->KTUTOUR,
								:ldatum,
								:lZeit
								;
		if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
		{
			ERROR_MSG2( "insert tourconstime1" )
		}
	}
	if( strncmp(a->KTUAUFZFZ2,"000",3) )
   	{
		sprintf(huelse,"%*.*s",L_DKKTU_KTUAUFZFZ2,L_DKKTU_KTUAUFZFZ2,a->KTUAUFZFZ2);
		minuten = atol(huelse);
		conszeit = (((minuten/60)*100) + (minuten%60)) * (-100);
		AllgAddTime(tourzeit,conszeit,&lZeit);
		lZeit = lZeit/100;
		EXEC SQL EXECUTE ins_tourconstime USING
                                :a->KTUFIL,
								:a->KTUTOUR,
								:ldatum,
								:lZeit
								;
		if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
		{
			ERROR_MSG2( "insert tourconstime2" )
		}
	}
	if( strncmp(a->KTUAUFZFZ3,"000",3) )
   	{
		sprintf(huelse,"%*.*s",L_DKKTU_KTUAUFZFZ3,L_DKKTU_KTUAUFZFZ3,a->KTUAUFZFZ3);
		minuten = atol(huelse);
		conszeit = (((minuten/60)*100) + (minuten%60)) * (-100);
		AllgAddTime(tourzeit,conszeit,&lZeit);
		lZeit = lZeit/100;
		EXEC SQL EXECUTE ins_tourconstime USING
                                :a->KTUFIL,
								:a->KTUTOUR,
								:ldatum,
								:lZeit
								;
		if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
		{
			ERROR_MSG2( "insert tourconstime3" )
		}
	}

	return OK;
}

int LadeTourPlanConsTime(struct O_DKKTU *tour, int datum, int tourtag, char *error_msg)
{
	char *fun = "LadeTourPlanConsTime";
	long tourzeit,conszeit,minuten;
	char huelse[81];
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	long lZeit;
	long ldatum;
	EXEC SQL END DECLARE SECTION;

	a= tour;

	if(olddate != actdate)
	{
		if ( (rc = LadeTourPlanConsTimeDatum(a, olddate, oldwd, error_msg)) < 0) return rc;
	}
	if ( (rc = LadeTourPlanConsTimeDatum(a, actdate, actwd, error_msg)) < 0) return rc;
	if ( (rc = LadeTourPlanConsTimeDatum(a, futurdate, futurwd, error_msg)) < 0) return rc;
	return OK;
}

int LadeTourPlanConsTimeDatum(struct O_DKKTU *tour, int datum, int tourtag, char *error_msg)
{
	char *fun = "LadeTourPlanConsTimeDatum";
	long tourzeit,conszeit,minuten;
	char huelse[81];

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	long lZeit;
	long ldatum;
	EXEC SQL END DECLARE SECTION;

	a= tour;
	ldatum = datum;

	sprintf(huelse,"%*.*s",L_DKKTU_KTUTOUR,L_DKKTU_KTUTOUR,a->KTUTOUR);
	tourzeit = (atol(huelse)/100)*100;

	/* constimes auch für nicht aktive touren laden
	if ( tourtag == ALLG_SONNTAG	&& a->KTUSO[0] != 'J')	return OK;
	if ( tourtag == ALLG_MONTAG		&& a->KTUMO[0] != 'J')	return OK;
	if ( tourtag == ALLG_DIENSTAG	&& a->KTUDI[0] != 'J')	return OK;
	if ( tourtag == ALLG_MITTWOCH	&& a->KTUMI[0] != 'J')	return OK;
	if ( tourtag == ALLG_DONNERSTAG	&& a->KTUDO[0] != 'J')	return OK;
	if ( tourtag == ALLG_FREITAG	&& a->KTUFR[0] != 'J')	return OK;
	if ( tourtag == ALLG_SONNABEND	&& a->KTUSA[0] != 'J')	return OK;
	*/

	EXEC SQL EXECUTE del_tourplantime USING
							:a->KTUFIL,
							:a->KTUIDF,
							:a->KTUTOUR,
							:ldatum
							;
	ERROR_MSG2( "delete tourplanconstime" )

	if( strncmp(a->KTUAUFZFZ1,"000",3) )
   	{
		sprintf(huelse,"%*.*s",L_DKKTU_KTUAUFZFZ1,L_DKKTU_KTUAUFZFZ1,a->KTUAUFZFZ1);
		minuten = atol(huelse);
		conszeit = (((minuten/60)*100) + (minuten%60)) * (-100);
		AllgAddTime(tourzeit,conszeit,&lZeit);
		lZeit = lZeit/100;
		EXEC SQL EXECUTE ins_tourplantime USING
                                :a->KTUFIL,
                                :a->KTUIDF,
								:a->KTUTOUR,
								:ldatum,
								:lZeit
								;
		if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
		{
			ERROR_MSG2( "insert ins_tourplantime1" )
		}
	}
	if( strncmp(a->KTUAUFZFZ2,"000",3) )
   	{
		sprintf(huelse,"%*.*s",L_DKKTU_KTUAUFZFZ2,L_DKKTU_KTUAUFZFZ2,a->KTUAUFZFZ2);
		minuten = atol(huelse);
		conszeit = (((minuten/60)*100) + (minuten%60)) * (-100);
		AllgAddTime(tourzeit,conszeit,&lZeit);
		lZeit = lZeit/100;
		EXEC SQL EXECUTE ins_tourplantime USING
                                :a->KTUFIL,
                                :a->KTUIDF,
								:a->KTUTOUR,
								:ldatum,
								:lZeit
								;
		if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
		{
			ERROR_MSG2( "insert ins_tourplantime2" )
		}
	}
	if( strncmp(a->KTUAUFZFZ3,"000",3) )
   	{
		sprintf(huelse,"%*.*s",L_DKKTU_KTUAUFZFZ3,L_DKKTU_KTUAUFZFZ3,a->KTUAUFZFZ3);
		minuten = atol(huelse);
		conszeit = (((minuten/60)*100) + (minuten%60)) * (-100);
		AllgAddTime(tourzeit,conszeit,&lZeit);
		lZeit = lZeit/100;
		EXEC SQL EXECUTE ins_tourplantime USING
                                :a->KTUFIL,
                                :a->KTUIDF,
								:a->KTUTOUR,
								:ldatum,
								:lZeit
								;
		if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
		{
			ERROR_MSG2( "insert ins_tourplantime3" )
		}
	}

	return OK;
}

int LadePotentialTours(struct O_DKKTU *tour, char *error_msg)
{
	char *fun = "LadePotentialTours";
	char huelse[81];

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	EXEC SQL END DECLARE SECTION;

	a = tour;

	sprintf(huelse,"%*.*s",L_DKKTU_KTUTOUR,L_DKKTU_KTUTOUR,a->KTUTOUR);

	EXEC SQL EXECUTE upd_potentialtours USING
								:a->KTUFIL,
                                :a->KTUIDF,
								:a->KTUTOUR;
	ERROR_MSG2( "update potentialtours" )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		EXEC SQL EXECUTE ins_potentialtours USING
                                :a->KTUFIL,
                                :a->KTUIDF,
								:a->KTUTOUR
								;
		if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
		{
			ERROR_MSG2( "insert potentialtours" )
		}
	}

	return OK;
}

int AfterLoadTouren   ( char *error_msg)
{
	return OK;
}

int AfterLoadTourWoche   ( char *error_msg)
{
	return OK;
}

int AfterLoadTourPlan   ( char *error_msg)
{
	int rc = 0;

	if( (rc = DelNotUpdatedTourPlan(error_msg)) != 0) return rc; 

	return OK;
}

int AfterLoadTourPlanWoche   ( char *error_msg)
{
	int rc = 0;

	if( (rc = DelNotUpdatedTourPlanWoche(error_msg)) != 0) return rc; 

	return OK;
}

int AfterLoadTourConsTime   ( char *error_msg)
{
	int rc = 0;
	if( (rc = DeleteOldConsTime(error_msg)) != 0) return rc; 
	return OK;
}

int AfterLoadTourPlanConsTime   ( char *error_msg)
{
	int rc = 0;
	if( (rc = DeleteOldPlanConsTime(error_msg)) != 0) return rc; 
	return OK;
}

int AfterLoadPotentialTours   ( char *error_msg)
{
	int rc = 0;

	if( (rc = DelNotUpdatedPotentialTours(error_msg)) != 0) return rc; 

	return OK;
}


/*** GET-DAY ******************************************************************/

static int GetDay( char *spDay )
{
	int retDay = -1;
	*spDay = *spDay >= 'a' && *spDay <= 'z' ? *spDay + 'A' - 'a' : *spDay;
    *(spDay+1) = *(spDay+1) >= 'a' && *(spDay+1) <= 'z' ?
		         *(spDay+1) + 'A' - 'a' : *(spDay+1);

	if ( !strcmp( spDay, "SO" ) || spDay[0] == '0' )
	   retDay = ALLG_SONNTAG;
	else if ( !strcmp( spDay, "MO" ) || spDay[0] == '1' )
	   retDay = ALLG_MONTAG;
	else if ( !strcmp( spDay, "DI" ) || spDay[0] == '2' )
	   retDay = ALLG_DIENSTAG;
    else if ( !strcmp( spDay, "MI" ) || spDay[0] == '3' )
	   retDay = ALLG_MITTWOCH;
    else if ( !strcmp( spDay, "DO" ) || spDay[0] == '4' )
	   retDay = ALLG_DONNERSTAG;
    else if ( !strcmp( spDay, "FR" ) || spDay[0] == '5' )
	   retDay = ALLG_FREITAG;
    else if ( !strcmp( spDay, "SA" ) || spDay[0] == '6' )
	   retDay = ALLG_SONNABEND;

	return retDay;
}

int SetNotUpdatedTourPlan( char *error_msg)
{
	char *fun = "SetNotUpdatedTourPlan";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select kzupd from tourplantag where vertriebszentrumnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_tourplan FROM :str;
	ERROR_MSG2( "prepare sel_tourplan" )
	exec sql declare CTour Cursor with hold for sel_tourplan;
	 
	strcpy( str, "update tourplantag set kzupd = '0' " );
	strcat( str, "where current of CTour " );
	
	exec sql prepare set_tour from :str;
	ERROR_MSG2( "prepare set_tour" )

	exec sql open CTour using :filialnr;
    ERROR_MSG2( "open CTour" )

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
		exec sql fetch CTour;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CTour" )
		
		exec sql execute set_tour;
		ERROR_MSG2( "execute set_tour" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close CTour ;
    ERROR_MSG2( "close CTour" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze gesetzt\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int SetNotUpdatedTourPlanWoche( char *error_msg)
{
	char *fun = "SetNotUpdatedTourPlanWoche";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select kzupd from tourplantagwoche where vertriebszentrumnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_tourwoche FROM :str;
	ERROR_MSG2( "prepare sel_tourwoche" )
	exec sql declare CTourWoche Cursor with hold for sel_tourwoche;
	 
	strcpy( str, "update tourplantagwoche set kzupd = '0' " );
	strcat( str, "where current of CTourWoche " );
	
	exec sql prepare set_tourwoche from :str;
	ERROR_MSG2( "prepare set_tourwoche" )

	exec sql open CTourWoche using :filialnr;
    ERROR_MSG2( "open CTourWoche" )

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
		exec sql fetch CTourWoche;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CTourWoche" )
		
		exec sql execute set_tourwoche;
		ERROR_MSG2( "execute set_tourwoche" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close CTourWoche ;
    ERROR_MSG2( "close CTourWoche" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze gesetzt\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int SetNotUpdatedPotentialTours( char *error_msg)
{
	char *fun = "SetNotUpdatedPotentialTours";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select updatesign from potentialcustomertours where branchno = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_potentialtours FROM :str;
	ERROR_MSG2( "prepare sel_potentialtours" )
	exec sql declare CPotentialTour Cursor with hold for sel_potentialtours;
	 
	strcpy( str, "update potentialcustomertours set updatesign = '0' " );
	strcat( str, "where current of CPotentialTour " );
	
	exec sql prepare set_potentialtours from :str;
	ERROR_MSG2( "prepare set_potentialtours" )

	exec sql open CPotentialTour using :filialnr;
    ERROR_MSG2( "open CPotentialTour" )

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
		exec sql fetch CPotentialTour;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CPotentialTour" )
		
		exec sql execute set_potentialtours;
		ERROR_MSG2( "execute set_potentialtours" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close CTourWoche ;
    ERROR_MSG2( "close CPotentialTour" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze gesetzt\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int DelNotUpdatedTourPlan( char *error_msg)
{
	char *fun = "DelNotUpdatedTourPlan";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select kzupd from tourplantag ");
	strcat(str," where kzupd = '0'");
	strcat(str," and vertriebszentrumnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_tour2 FROM :str;
	ERROR_MSG2( "prepare sel_tour2" )
	exec sql declare DelTour Cursor with hold for sel_tour2;
	 
	strcpy( str, "delete from tourplantag " );
	strcat( str, "where current of DelTour " );
	
	exec sql prepare del_tour from :str;
	ERROR_MSG2( "prepare del_tour" )

	exec sql open DelTour using :filialnr;
    ERROR_MSG2( "open DelTour" )

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
		exec sql fetch DelTour;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelTour" )
		
		exec sql execute del_tour;
		ERROR_MSG2( "execute del_tour" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close DelTour ;
    ERROR_MSG2( "close DelTour" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze geloescht\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int DelNotUpdatedTourPlanWoche( char *error_msg)
{
	char *fun = "DelNotUpdatedTourPlanWoche";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select kzupd from tourplantagwoche ");
	strcat(str," where kzupd = '0'");
	strcat(str," and vertriebszentrumnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_tourwoche2 FROM :str;
	ERROR_MSG2( "prepare sel_tourwoche2" )
	exec sql declare DelTourWoche Cursor with hold for sel_tourwoche2;
	 
	strcpy( str, "delete from tourplantagwoche " );
	strcat( str, "where current of DelTourWoche " );
	
	exec sql prepare del_tourwoche from :str;
	ERROR_MSG2( "prepare del_tourwoche" )

	exec sql open DelTourWoche using :filialnr;
    ERROR_MSG2( "open DelTourWoche" )

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
		exec sql fetch DelTourWoche;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelTourWoche" )
		
		exec sql execute del_tourwoche;
		ERROR_MSG2( "execute del_tourwoche" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close DelTourWoche ;
    ERROR_MSG2( "close DelTourWoche" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze geloescht\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int DelNotUpdatedPotentialTours( char *error_msg)
{
	char *fun = "DelNotUpdatedPotentialTours";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select updatesign from potentialcustomertours ");
	strcat(str," where updatesign = '0'");
	strcat(str," and branchno = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_potentialtours2 FROM :str;
	ERROR_MSG2( "prepare sel_potentialtours2" )
	exec sql declare DelPotentialTours Cursor with hold for sel_potentialtours2;
	 
	strcpy( str, "delete from potentialcustomertours " );
	strcat( str, "where current of DelPotentialTours " );
	
	exec sql prepare del_potentialtours from :str;
	ERROR_MSG2( "prepare del_potentialtours" )

	exec sql open DelPotentialTours using :filialnr;
    ERROR_MSG2( "open DelPotentialTours" )

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
		exec sql fetch DelPotentialTours;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelPotentialTours" )
		
		exec sql execute del_potentialtours;
		ERROR_MSG2( "execute del_potentialtours" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close DelPotentialTours ;
    ERROR_MSG2( "close DelPotentialTours" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze geloescht\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int PrepareSetKAtourplantag( char *error_msg)
{
	char *fun = "PrepareSetKAtourplantag";

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str,"select kundennr,tourid,koart from tourplantag ");
	strcat(str," where koart != ' '");
	strcat(str," and vertriebszentrumnr = " ); strcat(str, chaus);
	strcat( str, " and kundennr = ? " );
	strcat( str, " and tourid = ? " );
	strcat(str," for update");

	EXEC SQL PREPARE sel_tourka FROM :str;
	ERROR_MSG2( "prepare sel_tourka" )
	exec sql declare Seltourka Cursor with hold for sel_tourka;
	 
	strcpy( str, "update tourplantag " );
	strcat( str, "set koart = ?" );
	strcat( str, "where vertriebszentrumnr = " ); strcat(str, chaus);
	strcat( str, "and kundennr = ? " );
	strcat( str, "and tourid = ? " );
	strcat( str, "and datumkommi = ? " );
	
	exec sql prepare upd_tourka from :str;
	ERROR_MSG2( "prepare upd_tourka" )

	return OK;
}

int SetKAtourplantag( long Idf, long datum, char *cTourid, char *error_msg)
{
	char *fun = "SetKAtourplantag";

	exec sql begin declare section;
	char koart[2];
	long kundennr;
	char tourid[7];
	long IdfNr;
	long ldatum;
    exec sql end declare section;

	IdfNr = Idf;
	ldatum = datum;
	strncpy(tourid,cTourid,6);
	tourid[6] = '\0';

	exec sql open Seltourka  using :IdfNr,:tourid;
    ERROR_MSG2( "open Seltourka" )

	exec sql fetch Seltourka into :kundennr,:tourid,:koart;
	if ( sqlca.sqlcode == 100 ) return OK;
	ERROR_MSG2( "fetch Seltourka" )
	if(olddate != actdate)
	{
		ldatum = olddate;
		exec sql execute upd_tourka using :koart,:kundennr,:tourid,:ldatum;
		ERROR_MSG2( "execute upd_tourka old" )
	}
	ldatum = actdate;
	exec sql execute upd_tourka using :koart,:kundennr,:tourid,:ldatum;
	ERROR_MSG2( "execute upd_tourka act" )
	ldatum = futurdate;
	exec sql execute upd_tourka using :koart,:kundennr,:tourid,:ldatum;
	ERROR_MSG2( "execute upd_tourka futur" )

	exec sql close Seltourka ;
    ERROR_MSG2( "close Seltourka" )

	return OK;
}

int HolePseudoTour( char *error_msg)
{
	char *fun = "HolePseudoTour	";

	exec sql begin declare section;
	char koart[2];
	long kundennr;
	char tourid[7];
	char str[2048];
    exec sql end declare section;

	strcpy(str,"select tourid from sondertouren ");
	strcat(str," where kdauftragart = ' '");
	strcat(str," and filialnr = " ); strcat(str, chaus);

	EXEC SQL PREPARE sel_sondertour FROM :str;
	ERROR_MSG2( "prepare sel_sondertour" )
	exec sql declare Selsondertour Cursor with hold for sel_sondertour;

	exec sql open Selsondertour;
    ERROR_MSG2( "open Selsondertour" )

	exec sql fetch Selsondertour into :nachttour;	/* nur eine Tour */
	if ( sqlca.sqlcode == 100 )
	{
		strcpy(nachttour,"475901");
		return OK;
	}
	ERROR_MSG2( "fetch Selsondertour" )
	exec sql close Selsondertour ;
    ERROR_MSG2( "close Selsondertour" )

	return OK;
}

int TourPlanWoche( struct O_DKKTU *tour, char *tag, short weekday, char *error_msg)
{
	char *fun = "TourPlanWoche";

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	char tourtag[3];
	short sWeekday;
	short isBTM;
	short isKK;
	short isK08;
	short isK20;
	short isRT;
	short isPST;	// Transportausschluss für psychotrope Stoffe
	EXEC SQL END DECLARE SECTION;
	a= tour;
	strcpy(tourtag,tag);
	sWeekday = weekday;

	if ( a->KTUGPTOUR[0] != 'J' &&  a->KTUGPTOUR[0] != '1' )
		isBTM = 0;
	else
		isBTM = 1;

	if ( a->KTUKK[0] != 'J' &&  a->KTUKK[0] != '1' )
		isKK = 0;
	else
		isKK = 1;

	if ( a->KTUK08[0] != 'J' &&  a->KTUK08[0] != '1' )
		isK08 = 0;
	else
		isK08 = 1;

	if ( a->KTUK20[0] != 'J' &&  a->KTUK20[0] != '1' )
		isK20 = 0;
	else
		isK20 = 1;

	if (a->KTURETTOUR[0] != 'J' &&  a->KTURETTOUR[0] != '1')
		isRT = 0;
	else
		isRT = 1;

	if (a->KTUPST[0] != 'J' && a->KTUPST[0] != '1')
		isPST = 0;
	else
		isPST = 1;

	EXEC SQL EXECUTE upd_tourplanwoche USING
					:a->KTUVBTOUR,
                    :a->KTUAART,
					:a->KTUTDAUER2,
					:isBTM,
					:isKK,
					:isK08,
					:isK20,
					:isRT,
					:isPST,
					:a->KTUFIL,
					:a->KTUIDF,
					:sWeekday,
					:a->KTUTOUR
					;
	if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	{
		sprintf (error_msg, "update woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		PrintMsg( fun, error_msg, FEHL, ERROR );
		return ERROR;
	}
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		EXEC SQL EXECUTE ins_tourplanwoche USING
						:a->KTUFIL,
						:a->KTUIDF,
						:a->KTUTOUR,
						:tourtag,
						:sWeekday,
						:a->KTUVBTOUR,
	                    :a->KTUAART,
						:a->KTUTDAUER2,
						:isBTM,
						:isKK,
						:isK08,
						:isK20,
						:isRT,
						:isPST
						;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		{
			sprintf (error_msg, "insert woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
	}
	return OK;
}

int TourWoche( struct O_DKKTU *tour, char *tag, short weekday, char *error_msg)
{
	char *fun = "TourWoche";

	char huelse[80];

	EXEC SQL BEGIN DECLARE SECTION;
	struct O_DKKTU *a;
	char tourtag[3];
	short sWeekday;
	short karenz;
	EXEC SQL END DECLARE SECTION;
	a= tour;
	strcpy(tourtag,tag);
	sWeekday = weekday;

	sprintf(huelse,"%3.3s",a->KTUKARENZ);
	karenz = atoi(huelse);

	EXEC SQL EXECUTE upd_tourwoche USING
					:karenz,
					:a->KTUFIL,
					:a->KTUTOUR,
					:sWeekday
					;
	if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	{
		sprintf (error_msg, "update woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		PrintMsg( fun, error_msg, FEHL, ERROR );
		return ERROR;
	}
	return OK;
}

int DeleteOldConsTime( char *error_msg)
{
	char *fun = "DeleteOldConsTime";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select datumkommi from tourconstime ");
	strcat(str,"where filialnr = ");
	strcat(str, chaus);
	strcat(str," and datumkommi < ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_ct FROM :str;
	ERROR_MSG2( "prepare sel_ct" )
	exec sql declare DelConstime Cursor with hold for sel_ct;
	 
	strcpy( str, "delete from tourconstime " );
	strcat( str, "where current of DelConstime " );
	
	exec sql prepare del_ct from :str;
	ERROR_MSG2( "prepare del_ct" )

	exec sql open DelConstime using :olddate;
    ERROR_MSG2( "open DelConstime" )

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
		exec sql fetch DelConstime;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelConstime" )
		
		exec sql execute del_ct;
		ERROR_MSG2( "execute del_ct" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close DelConstime ;
    ERROR_MSG2( "close DelConstime" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze geloescht\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int DeleteOldPlanConsTime( char *error_msg)
{
	char *fun = "DeleteOldPlanConsTime";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select datumkommi from tourplanconstime ");
	strcat(str,"where vertriebszentrumnr = ");
	strcat(str, chaus);
	strcat(str," and datumkommi < ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_planct FROM :str;
	ERROR_MSG2( "prepare sel_planct" )
	exec sql declare DelPlanConstime Cursor with hold for sel_planct;
	 
	strcpy( str, "delete from tourplanconstime " );
	strcat( str, "where current of DelPlanConstime " );
	
	exec sql prepare del_planct from :str;
	ERROR_MSG2( "prepare del_planct" )

	exec sql open DelPlanConstime using :olddate;
    ERROR_MSG2( "open DelPlanConstime" )

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
		exec sql fetch DelPlanConstime;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelPlanConstime" )
		
		exec sql execute del_planct;
		ERROR_MSG2( "execute del_planct" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close DelPlanConstime ;
    ERROR_MSG2( "close DelPlanConstime" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze geloescht\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

/***** ENDE *****************************************************************/

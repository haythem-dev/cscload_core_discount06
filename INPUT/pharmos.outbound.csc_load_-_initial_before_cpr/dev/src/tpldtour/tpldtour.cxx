/* tpldtour.ecc */
#include "csc_load_version.h"

#define PROJECTNAME	 "tpldtour"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

//static char *SCCSID="@(#)PRZ GmbH Stand: 3.2.13 $Header: /prj/df/unix/tpldtour/tpldtour.cxx 142   7.09.05 11:22 66aeimsc $";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "tour.h"
#include "tourplanwoche.h"
#include "dktur.h"
#include "pplib/allg.h"
#include "libtpld/cobolbuf.h"
#include "libtpld/struct.h"
#include "errno.h"
#include <pplib/ppgeneric.h>
#include <libtpld/coboltoasci.h>
#include <callplan.h>
#include "callplanmaintenance.h"
#include "callplanundertake.h"
#include "libtpld/dadedb.h"
/*#include "rrds.h"*/
EXEC SQL include sqlca;

#undef NULL

#define P_DKTUR           "/phosix1/data/UCATPH1/DKTUR.P"
#define DEBUG_SECTION      if ( debug_enabled ) {
#define END_DEBUG_SECTION  fflush(stderr); }
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
                                        sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }


 /***** GLOBALE **************************************************************/

struct sondertour
{
	char Tourid[7];
	char Aart[3];
} tourtab[20]; 
 
 FILE *dkturdat;
 char log_file [300 + 1];
 int debug_enabled = NO;
 int DateiNr = 0;                 /* XVSAM */
 short haus = 0;
 static int ins_z = 0;
 static int upd_z = 0;
 static int fins_z = 0;
 static int fupd_z = 0;
 static int inswoche_z = 0;
 static int updwoche_z = 0;
 int Schweiz = NO;
 int Bulgarien = NO;
 int Frankreich = NO;
 int Kroatien = NO;
 int Austria = NO;
 int addoldday = 0;
 int addactday = 0;
 int addfuturday = 0;
 long farfuturdate;
 long helpdate;
	
	EXEC SQL BEGIN DECLARE SECTION;
	char datenbank[60];
	long olddate;
	long actdate;
	long futurdate;
	short oldwd;
	short actwd;
	short futurwd;
	EXEC SQL END DECLARE SECTION;

 
 /***** DECLARATION **********************************************************/
 int main( int, char ** );
 void PrintMsg( const char *fun, const char *error_msg, char mld, int rc );
// void WriteLogInfo( const char *error_msg, char mld, int rc );
 int StarteLoadTouren(int datum,int tourtag, char *error_msg );
 int PrepareLoadTouren(char *error_msg);
 int PrepareLoadTourenFolge(char *error_msg);
 int LadeTouren(struct S_DKTUR *tour, int datum,int tourtag, char *error_msg);
 int LadeTourenDatum(struct S_DKTUR *tour, int datum,int tourtag,int diffday, char *error_msg);
 int LadeTourenFolge(struct S_DKTUR *tour, int datum,int datum_folge,int tourtag_folge, char *error_msg);
 int AfterLoadTouren( char *error_msg);
 int AfterLoadTourenFolge( char *error_msg);
 int DelNotUpdatedTour( char *error_msg);
 int SetNotUpdatedTour( char *error_msg);
 int DelNotUpdatedTourFolge( char *error_msg);
 int SetNotUpdatedTourFolge( char *error_msg);
 int PrepareLoadTourWoche(char *error_msg);
 int LadeTourWoche(struct S_DKTUR *tour, char *error_msg);
 int AfterLoadTourWoche( char *error_msg);
 int DelNotUpdatedTourWoche( char *error_msg);
 int SetNotUpdatedTourWoche( char *error_msg);
 static int GetDay( char * );
 
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
       	else if ( !strcmp( schalter, "-bg" ) )
	   		Bulgarien = YES;
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
		else if ( !strcmp( schalter, "-lf" ) )
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
	      " [ -ld 19970314]\n\t"
	      " [ -la]\n\t"
	      "	[ -wd <(MO-SO)>]\n"
		  , argv[0] );
      return 2;
      }

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

   if ( StarteLoadTouren(datum, tourtag, error_msg) != 0 )
   {
	  PrintMsg( fun, "mit Fehler beendet", FEHL, 0 );
      return 1;
   }
 
   PrintMsg( fun, "ENDE", HINW, 0 );
   return OK;
 }


/***** WriteLogInfo nur zum Aufruf von PrintMsg ******************************/
/*
void WriteLogInfo( const char *error_msg, char mld, int rc )
{
	PrintMsg( "callplanday", error_msg, mld, rc );
}
*/

 /***** PRINT-MSG ************************************************************/

 void PrintMsg( const char *fun, const char *error_msg, char mld, int rc )
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
   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.8s %s",
	    mld,
	    haus,
		zeit->tm_mday,
        zeit->tm_mon + 1,
        (zeit->tm_year+1900)%100,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
	    pid,
	    "tpldtour",
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
	struct S_DKTUR   dktur, *a;
	short int filialnr;
	char cTourid[7];
	char cAart[3];
	char str[200];
	int iTourTag;
	EXEC SQL END DECLARE SECTION;

	char msg[80];
	int	datum_folge;
	int	datum_nachfolge;
	int tourtag_folge;
	char 	pfaddktur[81];
	char *XVSAM;
    tError stError;
	char szHaus[3];
	struct AUFB aufb[] = { DKTUR_SATZ };
	mcallplanloadS srvLoad;
	mholidayS holiday;
	char satz[1000];
    int len = 100;
	
    a = &dktur;

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
	
	olddate = AllgGetDate();
	
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
	oldwd = AllgGetWeekDay(olddate,error_msg);

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
	if (tourtag == -1) tourtag = GetDay(srvLoad.WOCHENTAG);
	actwd = tourtag;
	if(actdate < olddate) olddate = actdate;
	if(actdate == olddate) addoldday = 1;
	else
	{
		helpdate = olddate;
		for(addoldday = 1;;addoldday++)
		{
			helpdate = AllgAddDate(helpdate, 1, error_msg);
			if(helpdate == actdate) break;
		}
	}

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
	if(futurdate == actdate) addactday = 1;
	else
	{
		helpdate = actdate;
		for(addactday = 1;;addactday++)
		{
			helpdate = AllgAddDate(helpdate, 1, error_msg);
			if(helpdate == futurdate) break;
		}
	}

	/* nachfolge Tag */
	datum_nachfolge = ppGAddDate(datum_folge, 1, error_msg);
	for(;;)
	{
/*		if( AllgGetWeekDay(datum_nachfolge,error_msg) == ALLG_SONNTAG)
		{
			datum_nachfolge = AllgAddDate(datum_nachfolge, 1, error_msg);
		}
*/		holiday.ANTEIL = datum_nachfolge;
		if ( Mholiday_IsHoliday( &holiday, &stError, FALSE ) != IS_OK )
			break;
		datum_nachfolge = AllgAddDate(datum_nachfolge, 1, error_msg);
	}
	farfuturdate = datum_nachfolge;
	if(farfuturdate == futurdate) addfuturday = 1;
	else
	{
		helpdate = futurdate;
		for(addfuturday = 1;;addfuturday++)
		{
			helpdate = AllgAddDate(helpdate, 1, error_msg);
			if(helpdate == farfuturdate) break;
		}
	}

   DEBUG_SECTION
	fprintf(stderr,"Wochentag_folge: %d \n",tourtag_folge);
	fprintf(stderr,"Datum_folge: %d \n",datum_folge);
   END_DEBUG_SECTION



	/* nur wenn ich's selbst machen muss 
	holiday.FILIALNR = haus;
	if ( (rc=(retClient)Mholiday_StartBrowse(&holiday, &stError, FALSE)) == IS_ERROR )
		return rc;
	
	for(;;)
	{
		if( AllgGetWeekDay(datum_folge,error_msg) == ALLG_SONNTAG)
		{
			datum_folge = AllgAddDate(datum_folge, 1, error_msg);
		}
		holiday.ANTEIL = datum_folge;
		if ( Mholiday_IsHoliday( &holiday, &stError, FALSE ) != IS_OK )
			break;
		datum_folge = AllgAddDate(datum_folge, 1, error_msg);
	}
	tourtag_folge = AllgGetWeekDay(datum_folge,error_msg);
	*/

	filialnr = haus;

	strcpy(str,"select tourid,kdauftragart from sondertouren ");
	strcat(str," where kdauftragart != ' '");
	strcat(str," and filialnr = ?" );

	EXEC SQL PREPARE sel_sondertour FROM :str;
	ERROR_MSG2( "prepare sel_sondertour" )
	exec sql declare Selsondertour Cursor with hold for sel_sondertour;

	exec sql open Selsondertour using :filialnr;
    ERROR_MSG2( "open Selsondertour" )

	for(ind = 0; ind < 20; ind++)
	{
		strcpy(tourtab[ind].Tourid,"      ");
		strcpy(tourtab[ind].Aart,"  ");
	}
	for(ind = 0; ind < 20; ind++)
	{
		exec sql fetch Selsondertour into :cTourid,:cAart;
	    if (sqlca.sqlcode == -206 || sqlca.sqlcode == 100 ) break;
		else if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, "select sondertouren %ld", sqlca.sqlcode);
			PrintMsg( fun, error_msg, FEHL, -1 );
			return -1;
		}
		strcpy(tourtab[ind].Tourid,cTourid);
		strcpy(tourtab[ind].Aart,cAart);
	}
	exec sql close Selsondertour ;
    ERROR_MSG2( "close Selsondertour" )

	sprintf( msg, " started with %d (%d) / Folge %d (%d)", datum, tourtag, datum_folge, tourtag_folge );
	PrintMsg( "Main", msg, HINW, 0 );

	if( (rc = PrepareLoadTouren(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = PrepareLoadTourenFolge(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = PrepareLoadTourWoche(error_msg)) != 0 )
	{
		return rc;	
	}
	if ((XVSAM = getenv("XVSAM")) == (char *)0)
	{
		return -1;
	}
	else
	{
		sprintf(pfaddktur, "%s/UCATPH1/DKTUR.P.dat",XVSAM);
	}

	DEBUG_SECTION
	fprintf(stderr,"Pfad: %s \n",pfaddktur);
	END_DEBUG_SECTION

	if ( ( dkturdat = fopen( pfaddktur, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( "tpldtour ", pfaddktur, FEHL, 0 );
		PrintMsg( "tpldtour ", "DKTUR nicht vorhanden", FEHL, 0 );
		return -1;
	}

	EXEC SQL begin work;
    if (sqlca.sqlcode < 0 )
    {
    	sprintf(error_msg, "begin work1 %ld", sqlca.sqlcode);
 	  	PrintMsg( fun, error_msg, FEHL, -1 );
       	return -1;
    }

	iTourTag = tourtag;

	EXEC SQL update paraauftragbearb
	set tourweekday = :iTourTag
	where filialnr = :filialnr;

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

		rc = OK;
		if(fread( satz ,len, 1 , dkturdat ) != 0)
        {
	 	   if ( rc != OK )
		   {
   		       sprintf(error_msg, " XVSAM-Lesen DKTUR %ld", rc);
  			   PrintMsg( fun, error_msg, FEHL, -1 );
	    	   return -1;
		   }
	 	   memset( (char *)a, BLANC, sizeof( struct S_DKTUR ) );
	 	   WandelAsci( (char *)a, satz, aufb, SATZANZAHL( aufb ) );
	 	}
		else
		{
		   	DEBUG_SECTION
			fprintf(stderr,"%d Saetze gelesen\n",zaehler);
   			END_DEBUG_SECTION
			break;
		}
				
		/* neue Tabelle schreiben */
		
		sprintf( szHaus, "%02d", haus );
		if(strncmp(a->TURFIL,szHaus,L_DKTUR_TURFIL))
		{
			if(!strncmp(a->TURFIL,"48",L_DKTUR_TURFIL) 
				&& !strncmp(szHaus,"49",L_DKTUR_TURFIL))
			{
				strncpy(a->TURFIL,szHaus,L_DKTUR_TURFIL);
			}
			else
			{
				continue;
			}
		}

		
		if ( (rc = LadeTouren(a, datum, tourtag, error_msg)) < 0) return rc;
		if ( (rc = LadeTourenFolge(a, datum, datum_folge, tourtag_folge, error_msg)) < 0) return rc;
		if ( (rc = LadeTourWoche(a, error_msg)) < 0) return rc;
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

	sprintf(error_msg," tourfolgetag insert,update %d/%d",fins_z,fupd_z);
 	PrintMsg( fun, error_msg, HINW, -1 );

	sprintf(error_msg," tourplanwoche insert,update %d/%d",inswoche_z,updwoche_z);
 	PrintMsg( fun, error_msg, HINW, -1 );

	fclose( dkturdat);

	if( (rc = AfterLoadTouren(error_msg)) != 0 )
	{
		return rc;	
	}

	if( (rc = AfterLoadTourenFolge(error_msg)) != 0 )
	{
		return rc;	
	}

	if( (rc = AfterLoadTourWoche(error_msg)) != 0 )
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

	strcpy(str,"insert into tour (");
	strcat(str,"DATUMKOMMI,");          
	strcat(str,"TOURID,");          
	strcat(str,"ZEITKOENDE,");          
	strcat(str,"DATUMVERSAND,");          
	strcat(str,"ZEITVERSAND,");          
	strcat(str,"BAHNHOFVERSAND,");          
	strcat(str,"TOURSTAT,");          
	strcat(str,"VORABSCHEINDRUCKEN,");
	strcat(str,"FAHRTZEIT,");
	strcat(str,"TOURSTRECKE,");
	strcat(str,"BEZEICHNUNG,");
	strcat(str,"BEMERKUNGEN,");
	strcat(str,"DRUCKFACHNR,");
	strcat(str,"LAGRECHTOUR,");
	strcat(str,"KZUPD,");
	strcat(str,"FILIALNR,");
	strcat(str,"KDAUFTRAGART,");
	strcat(str,"SNIGHTTOUR");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,?,?,0,?,?,?,?,?,?,?,'1',?,?,? )");

	EXEC SQL PREPARE ins_tour FROM :str;
	ERROR_MSG2( "prepare ins_tour " );

	strcpy(str,"update tour set ");
	strcat(str,"KZUPD = '1',");          
	strcat(str,"KDAUFTRAGART = ?,");          
	strcat(str,"LAGRECHTOUR = ?,");          
	strcat(str,"SNIGHTTOUR = ?");          
	strcat(str," where");
	strcat(str," DATUMKOMMI = ?");          
	strcat(str," and FILIALNR = ?");          
	strcat(str," and TOURID = ?");          

	EXEC SQL PREPARE upd_tour FROM :str;
	ERROR_MSG2( "prepare upd_tour" )

	if( (rc = SetNotUpdatedTour(error_msg)) != 0) return rc; 
	 
	return 0;
}

int PrepareLoadTourenFolge(char *error_msg)
{
	char *fun = "PrepareLoadTourenFolge";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;
	

	strcpy(str,"insert into tourfolgetag (");
	strcat(str,"DATUMKOMMI,");          
	strcat(str,"TOURID,");          
	strcat(str,"DATUMVERSAND,");          
	strcat(str,"FILIALNR,");
	strcat(str,"KZUPD,");
	strcat(str,"LAGRECHTOUR");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,'1',? )");

	EXEC SQL PREPARE ins_tourfolge FROM :str;
	ERROR_MSG2( "prepare ins_tourfolge " );

	strcpy(str,"update tourfolgetag set ");
	strcat(str,"KZUPD = '1',");          
	strcat(str,"DATUMVERSAND = ?,");          
	strcat(str,"LAGRECHTOUR = ?");          
	strcat(str," where");
	strcat(str," DATUMKOMMI = ?");          
	strcat(str," and FILIALNR = ?");          
	strcat(str," and TOURID = ?");          

	EXEC SQL PREPARE upd_tourfolge FROM :str;
	ERROR_MSG2( "prepare upd_tourfolge" )

	if( (rc = SetNotUpdatedTourFolge(error_msg)) != 0) return rc; 
	 
	return 0;
}


int PrepareLoadTourWoche(char *error_msg)
{
	char *fun = "PrepareLoadTourWoche";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;
	

	strcpy(str,"insert into tourplanwoche (");
	strcat(str,"FILIALNR,");
	strcat(str,"TOURID,");          
	strcat(str,"TAGESTYP,");
	strcat(str,"KZUPD,");
	strcat(str,"WEEKDAY,");
	strcat(str,"LAGRECHTOUR");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,'1',?,? )");

	EXEC SQL PREPARE ins_tourwoche FROM :str;
	ERROR_MSG2( "prepare ins_tourwoche " );

	strcpy(str,"update tourplanwoche set ");
	strcat(str,"KZUPD = '1', ");          
	strcat(str,"LAGRECHTOUR = ?");
	strcat(str," where");
	strcat(str," FILIALNR = ?");          
	strcat(str," and TOURID = ?");          
	strcat(str," and WEEKDAY = ?");          

	EXEC SQL PREPARE upd_tourwoche FROM :str;
	ERROR_MSG2( "prepare upd_tourwoche" )

	if( (rc = SetNotUpdatedTourWoche(error_msg)) != 0) return rc; 
	 
	return 0;
}
 
int LadeTouren(struct S_DKTUR *tour, int datum,int tourtag, char *error_msg)
{
	char *fun = "LadeTouren";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DKTUR *a;
	EXEC SQL END DECLARE SECTION;
	a= tour;

	if(olddate != actdate)
	{
		if ( (rc = LadeTourenDatum(a, olddate, oldwd, addoldday, error_msg)) < 0) return rc;
	}
	if ( (rc = LadeTourenDatum(a, actdate, actwd, addactday, error_msg)) < 0) return rc;
	if ( (rc = LadeTourenDatum(a, futurdate, futurwd, addfuturday, error_msg)) < 0) return rc;

	return OK;
}
 
int LadeTourenDatum(struct S_DKTUR *tour, int datum,int tourtag,int diffday, char *error_msg)
{
	char *fun = "LadeTourenDatum";
	int zeit;
	int ind;
	short bhf;
	char sbhf[81], szeit[81];
	char huelse[81];

	EXEC SQL BEGIN DECLARE SECTION;
	struct TOUR   tournew, *i;
	struct S_DKTUR *a;
	EXEC SQL END DECLARE SECTION;
	i =	&tournew;
	a= tour;

   	DEBUG_SECTION
	fprintf(stderr,"TAGTAB:#%c%c%c%c%c%c%c#\n"
			,a->TURSO[0]
			,a->TURMO[0]
			,a->TURDI[0]
			,a->TURMI[0]
			,a->TURDO[0]
			,a->TURFR[0]
			,a->TURSA[0]);
	END_DEBUG_SECTION

	if ( tourtag == ALLG_SONNTAG    && a->TURSO[0] != 'J') return OK;
	if ( tourtag == ALLG_MONTAG     && a->TURMO[0] != 'J') return OK;
	if ( tourtag == ALLG_DIENSTAG   && a->TURDI[0] != 'J') return OK;
	if ( tourtag == ALLG_MITTWOCH   && a->TURMI[0] != 'J') return OK;
	if ( tourtag == ALLG_DONNERSTAG && a->TURDO[0] != 'J') return OK;
	if ( tourtag == ALLG_FREITAG    && a->TURFR[0] != 'J') return OK;
	if ( tourtag == ALLG_SONNABEND  && a->TURSA[0] != 'J') return OK;

	sprintf( huelse, "%*.*s",LS_DKTUR_TURDTOUR,LS_DKTUR_TURDTOUR,a->TURDTOUR );
	i->LAGRECHTOUR = atoi(huelse);

	memcpy(szeit,a->TURTOUR,4);
	szeit[4] = '\0';
	zeit = atol(szeit)*100L;

	memcpy(sbhf,a->TURTOUR+4,2);
	sbhf[2] = '\0';
	bhf = (short)atol(sbhf);

	i->DATUMKOMMI 		= datum;
	i->ZEITKOENDE 		= zeit >= 240000 ? 235900 : zeit;
	if(!strncmp(a->TURTOUR,"4759",4))
	{
		i->DATUMVERSAND = datum;
	}
	else
	{
		i->DATUMVERSAND   	= zeit >= 240000 ? AllgAddDateRetWorkDay(datum,diffday,error_msg) : datum;
	}
	if (i->DATUMVERSAND < 0)
   	{
 		PrintMsg( fun, error_msg, FEHL, ERROR );
   		return ERROR;
   	}
	i->ZEITVERSAND    	= zeit >= 240000 ? zeit - 240000 : zeit;
	i->BAHNHOFVERSAND 	= bhf;
	i->VORABSCHEINDRUCKEN[0] = a->TURVTKZ[0] == 'J' ? '1' : '0'; 
	i->VORABSCHEINDRUCKEN[1] = '\0';

	strcpy(i->KDAUFTRAGART,"  ");	/* mit blank vorbelegen */
	for(ind = 0; ind < 20 ; ind++ )
	{
		if( !strncmp(a->TURTOUR,tourtab[ind].Tourid,4) )
		{
			strcpy(i->KDAUFTRAGART,tourtab[ind].Aart);
			break;
		}
	}
	if(a->TURNTOUR[0] == 'J' || a->TURNTOUR[0] == '1') i->SNIGHTTOUR = 1;
	else i->SNIGHTTOUR = 0;

   	DEBUG_SECTION
	fprintf(stderr,"#%d#\n",i->DATUMKOMMI);
	fprintf(stderr,"#%*.*s#\n",LS_DKTUR_TURTOUR,LS_DKTUR_TURTOUR,a->TURTOUR);
	fprintf(stderr,"#%d#\n",i->ZEITKOENDE);
	fprintf(stderr,"#%d#\n",i->DATUMVERSAND);
	fprintf(stderr,"#%d#\n",i->ZEITVERSAND);
	fprintf(stderr,"#%d#\n",i->BAHNHOFVERSAND);
	fprintf(stderr,"#%*.*s#\n",LS_DKTUR_TURVTKZ,LS_DKTUR_TURVTKZ,a->TURVTKZ);
	fprintf(stderr,"#%s#\n",i->VORABSCHEINDRUCKEN);
	fprintf(stderr,"#%*.*s#\n",LS_DKTUR_TURZEIT,LS_DKTUR_TURZEIT,a->TURZEIT);
	fprintf(stderr,"#%*.*s#\n",LS_DKTUR_TURKM,LS_DKTUR_TURKM,a->TURKM);
	fprintf(stderr,"#%*.*s#\n",LS_DKTUR_TURBEZ,LS_DKTUR_TURBEZ,a->TURBEZ);
	fprintf(stderr,"#%*.*s#\n",LS_DKTUR_TURREF,LS_DKTUR_TURREF,a->TURREF);
	fprintf(stderr,"#%*.*s#\n",LS_DKTUR_TURSATOUR,LS_DKTUR_TURSATOUR,a->TURSATOUR);
	END_DEBUG_SECTION

	EXEC SQL EXECUTE ins_tour USING
			  			:i->DATUMKOMMI,
						:a->TURTOUR,
						:i->ZEITKOENDE,
						:i->DATUMVERSAND,
						:i->ZEITVERSAND,
						:i->BAHNHOFVERSAND,
						:i->VORABSCHEINDRUCKEN,
						:a->TURZEIT,
						:a->TURKM,
						:a->TURBEZ,
						:a->TURREF,
						:a->TURSATOUR,
						:i->LAGRECHTOUR,
						:a->TURFIL,
						:i->KDAUFTRAGART,
						:i->SNIGHTTOUR
						;
	if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268)
	{
		EXEC SQL EXECUTE upd_tour USING
						:i->KDAUFTRAGART,
						:i->LAGRECHTOUR,
						:i->SNIGHTTOUR,
			  			:i->DATUMKOMMI,
						:a->TURFIL,
						:a->TURTOUR
						;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
	   		sprintf (error_msg, "update: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 		PrintMsg( fun, error_msg, FEHL, ERROR );
	   		return ERROR;
	   	}
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] != 0 )  /* Satz geändert */
			upd_z++;
		return OK;  /* Satz bereits vorhanden */
	}
	if (sqlca.sqlcode != 0)  /* Datenbankfehler */
   	{
   		sprintf (error_msg, "insert: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 		PrintMsg( fun, error_msg, FEHL, ERROR );
   		return ERROR;
   	}
	ins_z++;
	return OK;
}
 
int LadeTourenFolge(struct S_DKTUR *tour, int datum, int datum_folge,int tourtag_folge, char *error_msg)
{
	char *fun = "LadeTourenFolge";
	char huelse[81];

	EXEC SQL BEGIN DECLARE SECTION;
	struct TOUR   tournew, *i;
	struct S_DKTUR *a;
	EXEC SQL END DECLARE SECTION;
	i =	&tournew;
	a= tour;

	if ( tourtag_folge == ALLG_SONNTAG    && a->TURSO[0] != 'J') return OK;
	if ( tourtag_folge == ALLG_MONTAG     && a->TURMO[0] != 'J') return OK;
	if ( tourtag_folge == ALLG_DIENSTAG   && a->TURDI[0] != 'J') return OK;
	if ( tourtag_folge == ALLG_MITTWOCH   && a->TURMI[0] != 'J') return OK;
	if ( tourtag_folge == ALLG_DONNERSTAG && a->TURDO[0] != 'J') return OK;
	if ( tourtag_folge == ALLG_FREITAG    && a->TURFR[0] != 'J') return OK;
	if ( tourtag_folge == ALLG_SONNABEND  && a->TURSA[0] != 'J') return OK;

	sprintf( huelse, "%*.*s",LS_DKTUR_TURDTOUR,LS_DKTUR_TURDTOUR,a->TURDTOUR );
	i->LAGRECHTOUR = atoi(huelse);

	i->DATUMKOMMI 		= datum;
	i->DATUMVERSAND   	= datum_folge;

   	DEBUG_SECTION
	fprintf(stderr,"#%d#\n",i->DATUMKOMMI);
	fprintf(stderr,"#%*.*s#\n",LS_DKTUR_TURTOUR,LS_DKTUR_TURTOUR,a->TURTOUR);
	fprintf(stderr,"#%d#\n",i->DATUMVERSAND);
	END_DEBUG_SECTION

	EXEC SQL EXECUTE ins_tourfolge USING
			  			:i->DATUMKOMMI,
						:a->TURTOUR,
						:i->DATUMVERSAND,
						:a->TURFIL,
						:i->LAGRECHTOUR
						;
	if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268)
	{
		EXEC SQL EXECUTE upd_tourfolge USING
						:i->DATUMVERSAND,
						:i->LAGRECHTOUR,
			  			:i->DATUMKOMMI,
						:a->TURFIL,
						:a->TURTOUR
						;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
	   		sprintf (error_msg, "update: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 		PrintMsg( fun, error_msg, FEHL, ERROR );
	   		return ERROR;
	   	}
		fupd_z++;
		return OK;  /* Satz bereits vorhanden */
	}
	if (sqlca.sqlcode != 0)  /* Datenbankfehler */
   	{
   		sprintf (error_msg, "insert: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
 		PrintMsg( fun, error_msg, FEHL, ERROR );
   		return ERROR;
   	}
	fins_z++;
	return OK;
}
 
int LadeTourWoche(struct S_DKTUR *tour, char *error_msg)
{
	char *fun = "LadeTourWoche";
	char huelse[81];

	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DKTUR *a;
	char tourtag[3];
	short sWeekday;
	long lLAGRECHTOUR;
	EXEC SQL END DECLARE SECTION;
	a= tour;

	sprintf( huelse, "%*.*s",LS_DKTUR_TURDTOUR,LS_DKTUR_TURDTOUR,a->TURDTOUR );
	lLAGRECHTOUR = atoi(huelse);

	if ( a->TURSO[0] == 'J')
	{
		strcpy(tourtag,"SO");
		sWeekday = 0;
		EXEC SQL EXECUTE upd_tourwoche USING
					:lLAGRECHTOUR,
					:a->TURFIL,
					:a->TURTOUR,
					:sWeekday
						;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
	   		sprintf (error_msg, "update woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 		PrintMsg( fun, error_msg, FEHL, ERROR );
	   		return ERROR;
	   	}
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_tourwoche USING
						:a->TURFIL,
						:a->TURTOUR,
						:tourtag,
						:sWeekday,
						:lLAGRECHTOUR
						;
			if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		   	{
		   		sprintf (error_msg, "insert woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		 		PrintMsg( fun, error_msg, FEHL, ERROR );
		   		return ERROR;
		   	}
			inswoche_z++;
		}
		else
		{
			updwoche_z++;
		}
	}

	if ( a->TURMO[0] == 'J')
	{
		strcpy(tourtag,"MO"); 
		sWeekday = 1;
		EXEC SQL EXECUTE upd_tourwoche USING
					:lLAGRECHTOUR,
					:a->TURFIL,
					:a->TURTOUR,
					:sWeekday
						;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
	   		sprintf (error_msg, "update woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 		PrintMsg( fun, error_msg, FEHL, ERROR );
	   		return ERROR;
	   	}
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_tourwoche USING
						:a->TURFIL,
						:a->TURTOUR,
						:tourtag,
						:sWeekday,
						:lLAGRECHTOUR
						;
			if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		   	{
		   		sprintf (error_msg, "insert woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		 		PrintMsg( fun, error_msg, FEHL, ERROR );
		   		return ERROR;
		   	}
			inswoche_z++;
		}
		else
		{
			updwoche_z++;
		}
	}

	if ( a->TURDI[0] == 'J')
	{
		strcpy(tourtag,"DI"); 
		sWeekday = 2;
		EXEC SQL EXECUTE upd_tourwoche USING
					:lLAGRECHTOUR,
					:a->TURFIL,
					:a->TURTOUR,
					:sWeekday
						;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
	   		sprintf (error_msg, "update woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 		PrintMsg( fun, error_msg, FEHL, ERROR );
	   		return ERROR;
	   	}
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_tourwoche USING
						:a->TURFIL,
						:a->TURTOUR,
						:tourtag,
						:sWeekday,
						:lLAGRECHTOUR
						;
			if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		   	{
		   		sprintf (error_msg, "insert woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		 		PrintMsg( fun, error_msg, FEHL, ERROR );
		   		return ERROR;
		   	}
			inswoche_z++;
		}
		else
		{
			updwoche_z++;
		}
	}

	if ( a->TURMI[0] == 'J')
	{
		strcpy(tourtag,"MI"); 
		sWeekday = 3;
		EXEC SQL EXECUTE upd_tourwoche USING
					:lLAGRECHTOUR,
					:a->TURFIL,
					:a->TURTOUR,
					:sWeekday
						;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
	   		sprintf (error_msg, "update woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 		PrintMsg( fun, error_msg, FEHL, ERROR );
	   		return ERROR;
	   	}
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_tourwoche USING
						:a->TURFIL,
						:a->TURTOUR,
						:tourtag,
						:sWeekday,
						:lLAGRECHTOUR
						;
			if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		   	{
		   		sprintf (error_msg, "insert woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		 		PrintMsg( fun, error_msg, FEHL, ERROR );
		   		return ERROR;
		   	}
			inswoche_z++;
		}
		else
		{
			updwoche_z++;
		}
	}

	if ( a->TURDO[0] == 'J')
	{
		strcpy(tourtag,"DO"); 
		sWeekday = 4;
		EXEC SQL EXECUTE upd_tourwoche USING
					:lLAGRECHTOUR,
					:a->TURFIL,
					:a->TURTOUR,
					:sWeekday
						;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
	   		sprintf (error_msg, "update woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 		PrintMsg( fun, error_msg, FEHL, ERROR );
	   		return ERROR;
	   	}
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_tourwoche USING
						:a->TURFIL,
						:a->TURTOUR,
						:tourtag,
						:sWeekday,
						:lLAGRECHTOUR
						;
			if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		   	{
		   		sprintf (error_msg, "insert woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		 		PrintMsg( fun, error_msg, FEHL, ERROR );
		   		return ERROR;
		   	}
			inswoche_z++;
		}
		else
		{
			updwoche_z++;
		}
	}

	if ( a->TURFR[0] == 'J')
	{
		strcpy(tourtag,"FR"); 
		sWeekday = 5;
		EXEC SQL EXECUTE upd_tourwoche USING
					:lLAGRECHTOUR,
					:a->TURFIL,
					:a->TURTOUR,
					:sWeekday
						;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
	   		sprintf (error_msg, "update woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 		PrintMsg( fun, error_msg, FEHL, ERROR );
	   		return ERROR;
	   	}
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_tourwoche USING
						:a->TURFIL,
						:a->TURTOUR,
						:tourtag,
						:sWeekday,
						:lLAGRECHTOUR
						;
			if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		   	{
		   		sprintf (error_msg, "insert woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		 		PrintMsg( fun, error_msg, FEHL, ERROR );
		   		return ERROR;
		   	}
			inswoche_z++;
		}
		else
		{
			updwoche_z++;
		}
	}

	if ( a->TURSA[0] == 'J')
	{
		strcpy(tourtag,"SA"); 
		sWeekday = 6;
		EXEC SQL EXECUTE upd_tourwoche USING
					:lLAGRECHTOUR,
					:a->TURFIL,
					:a->TURTOUR,
					:sWeekday
						;
		if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	   	{
	   		sprintf (error_msg, "update woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
	 		PrintMsg( fun, error_msg, FEHL, ERROR );
	   		return ERROR;
	   	}
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_tourwoche USING
						:a->TURFIL,
						:a->TURTOUR,
						:tourtag,
						:sWeekday,
						:lLAGRECHTOUR
						;
			if (sqlca.sqlcode != 0)  /* Datenbankfehler */
		   	{
		   		sprintf (error_msg, "insert woche: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		 		PrintMsg( fun, error_msg, FEHL, ERROR );
		   		return ERROR;
		   	}
			inswoche_z++;
		}
		else
		{
			updwoche_z++;
		}
	}
	return OK;
}

int AfterLoadTouren   ( char *error_msg)
{
	int rc = 0;

	if( (rc = DelNotUpdatedTour(error_msg)) != 0) return rc; 

	return OK;
}

int AfterLoadTourenFolge   ( char *error_msg)
{
	int rc = 0;

	if( (rc = DelNotUpdatedTourFolge(error_msg)) != 0) return rc; 

	return OK;
}

int AfterLoadTourWoche   ( char *error_msg)
{
	int rc = 0;

	if( (rc = DelNotUpdatedTourWoche(error_msg)) != 0) return rc; 

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

int SetNotUpdatedTour( char *error_msg)
{
	char *fun = "SetNotUpdatedTour";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select kzupd from tour where filialnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_tour FROM :str;
	ERROR_MSG2( "prepare sel_tour" )
	exec sql declare CTour Cursor with hold for sel_tour;
	 
	strcpy( str, "update tour set kzupd = '0' " );
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

int SetNotUpdatedTourFolge( char *error_msg)
{
	char *fun = "SetNotUpdatedTourFolge";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select kzupd from tourfolgetag where filialnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_tourfolge FROM :str;
	ERROR_MSG2( "prepare sel_tourfolge" )
	exec sql declare CTourfolge Cursor with hold for sel_tourfolge;
	 
	strcpy( str, "update tourfolgetag set kzupd = '0' " );
	strcat( str, "where current of CTourfolge " );
	
	exec sql prepare set_tourfolge from :str;
	ERROR_MSG2( "prepare set_tourfolge" )

	exec sql open CTourfolge using :filialnr;
    ERROR_MSG2( "open CTourfolge" )

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
		exec sql fetch CTourfolge;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CTourfolge" )
		
		exec sql execute set_tourfolge;
		ERROR_MSG2( "execute set_tourfolge" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close CTourfolge ;
    ERROR_MSG2( "close CTourfolge" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze gesetzt\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int SetNotUpdatedTourWoche( char *error_msg)
{
	char *fun = "SetNotUpdatedTourWoche";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select kzupd from tourplanwoche where filialnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_tourwoche FROM :str;
	ERROR_MSG2( "prepare sel_tourwoche" )
	exec sql declare CTourWoche Cursor with hold for sel_tourwoche;
	 
	strcpy( str, "update tourplanwoche set kzupd = '0' " );
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

int DelNotUpdatedTour( char *error_msg)
{
	char *fun = "DelNotUpdatedTour";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select kzupd from tour ");
	strcat(str," where kzupd = '0'");
	strcat(str," and filialnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_tour2 FROM :str;
	ERROR_MSG2( "prepare sel_tour2" )
	exec sql declare DelTour Cursor with hold for sel_tour2;
	 
	strcpy( str, "delete from tour " );
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

int DelNotUpdatedTourFolge( char *error_msg)
{
	char *fun = "DelNotUpdatedTourFolge";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select kzupd from tourfolgetag ");
	strcat(str," where kzupd = '0'");
	strcat(str," and filialnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_tourfolge2 FROM :str;
	ERROR_MSG2( "prepare sel_tourfolge2" )
	exec sql declare DelTourfolge Cursor with hold for sel_tourfolge2;
	 
	strcpy( str, "delete from tourfolgetag " );
	strcat( str, "where current of DelTourfolge " );
	
	exec sql prepare del_tourfolge from :str;
	ERROR_MSG2( "prepare del_tourfolge" )

	exec sql open DelTourfolge using :filialnr;
    ERROR_MSG2( "open DelTourfolge" )

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
		exec sql fetch DelTourfolge;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelTourfolge" )
		
		exec sql execute del_tourfolge;
		ERROR_MSG2( "execute del_tourfolge" )
	}

	exec sql commit work;
	ERROR_MSG2( "Commit Work:" )
	exec sql close DelTourfolge ;
    ERROR_MSG2( "close DelTourfolge" )

	DEBUG_SECTION
	sprintf(error_msg," %d Saetze geloescht\n",comz);
 	PrintMsg( fun, error_msg, HINW, -1 );
	END_DEBUG_SECTION

	return OK;
}

int DelNotUpdatedTourWoche( char *error_msg)
{
	char *fun = "DelNotUpdatedTourWoche";
	int comz;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	short filialnr;
	EXEC SQL END DECLARE SECTION;

	filialnr = haus;

	strcpy(str,"select kzupd from tourplanwoche ");
	strcat(str," where kzupd = '0'");
	strcat(str," and filialnr = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_tourwoche2 FROM :str;
	ERROR_MSG2( "prepare sel_tourwoche2" )
	exec sql declare DelTourWoche Cursor with hold for sel_tourwoche2;
	 
	strcpy( str, "delete from tourplanwoche " );
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

/***** ENDE *****************************************************************/

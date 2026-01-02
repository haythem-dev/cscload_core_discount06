/* loadroutecheck.cxx */

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadroutecheck"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/********************************** INCLUDE *****************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "pplib/allg.h"
#include "errno.h"
#include "libtpld/dadedb.h"
#include "callplanmaintenance.h"

#include "customer.h"
#include "controlling.h"

EXEC SQL include sqlca;



/********************************** DEFINE ****************************/
#undef	NULL

#define DEBUG_SECTION		if (sDebuggingActive == YES) {
#define END_DEBUG_SECTION	}

#define OK				    0
#define YES				    1
#define INSERT			    1
#define ERROR			   -1
#define WARNING			   -2
#define HINWEIS            'H'
#define FEHLER             'F'

#define LOG_FILE			"wws.log"

#define ERROR_MSG_OUT       sprintf( spBuffer, "%s %d/%d",\
                                        pmyError->spError, \
										pmyError->lSqlcode,\
										pmyError->lUpdateNo ); \
                            PrintMsg( fun, spBuffer, chLogFile, sVZ, FEHLER, -1 ); \


EXEC SQL BEGIN DECLARE SECTION;
 typedef struct N_KNDTOUREN {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
} kndtourenS;
 long	lDatumkommi;		//Datum zum Lesen der Toureninformationen
 long	lDate = 0;
 long	lWeekDay;
 int	iZaehler;				//Zähler
 int	iDuplicateZaehler=0;	//Zähler

 EXEC SQL END DECLARE SECTION;



 /***** GLOBAL ***************************************************************/
static char		chLogFile[256];			//Log-File-Pfad
static long		lEndTime = -1;
static short	sVZ = 0;				//Startparameter
 
 /***** DECLARATION **********************************************************/
 int main( int, char ** );
 void PrintMsg( char *fun, char *error_msg, char* log_file, short haus, char mld, int rc );
 void WriteLogInfo( char *error_msg, char mld, int rc );
 bool datenbankVerbinden(tError* myError, char* spDbName);
 bool datenbankSchliessen(tError* myError);
 bool rollbackWork(tError* myError);
 bool StartFillRouteCheckTable( tError* myError, short sVZ, short sDebuggingActive, char* spBuffer );
 bool PrepareFillRouteCheckTable( tError* myError, short sVZ, short sDebuggingActive, char* spBuffer  );
 bool DeleteRouteCheckTable( tError* myError, short sVZ, short sDebuggingActive, char* spBuffer  );
 long Set2HHMM(long lMinuten);

 /***** MAIN *****************************************************************/
 int main( int argc, char **argv  )
 {

	char*		spParameter;			//Startparameter
	short		sDebuggingActive = 0;	//Startparameter
	char		chdatenbank[60] = "";	//Startparameter
	short		sErrorFlag = OK;		//Startparameter

	char*		fun = "Main";			//Log-File

	tError		myError;				//Error-Struktur
	tError*		pmyError = &myError;	//Error-Struktur

	char*		spBuffer = 0;			//BufferString
	mcallplanloadS srvLoad;
    tError stError;



	/**** Startparameter lesen ********/
	for ( int i = 1; i < argc; i++ )
	{
       	spParameter = argv[i];
       	if ( !strcmp( spParameter, "-dg" ) )		//Parameter -dg
	   		sDebuggingActive = YES;
		else if ( !strcmp( spParameter, "-db" ) )	//Parameter -db
		{
			i++;
			sprintf( chdatenbank, "%s", argv[i] );
		}
		else if ( !strcmp( spParameter, "-vz" ) )	//Parameter -vz
		{
			i++;
			sVZ = atoi(argv[i]);
		}
		else if ( !strcmp( spParameter, "-end" ) )	//Parameter endezeit pruefung
		{
			i++;
			lEndTime = (atol(argv[i])) * 100;
		}
		else if ( !strcmp( spParameter, "-ld" ) )
		{
			i++;
			lDate = atol(argv[i]);
		}
 		else if ( !strcmp( spParameter, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
       else
	  	{
	  		sErrorFlag = ERROR;
	  		break;
	  	}
  	}                                            

	if ( sVZ == 0 || !strcmp( chdatenbank, "") || sErrorFlag == ERROR )
	{
      printf( "  usage: %s\n\t"
	      " { -dg <Debugging> }\n\t"
		  " { -db datenbankname <Datenbankname> }\n\t"
	      " [ -ld 19970314]\n\t"
		  " { -vz 05 <Filialnr> }\n"
		  , argv[0] );
      return ERROR;
	}

	DEBUG_SECTION
		fprintf(stderr,"Input VZ: %d \n", sVZ);
		fprintf(stderr,"Input Datenbank: %s \n", chdatenbank);
	END_DEBUG_SECTION
	/****************************/


	/**** Logfile und Pfad ********/
	if ((spBuffer = getenv("LOG_PATH")) == (char *)0)
		spBuffer = ".";

	sprintf(chLogFile, "%s/%s", spBuffer, LOG_FILE );
    	
	DEBUG_SECTION
		fprintf(stderr,"Input Logfile: %s \n", chLogFile);
	END_DEBUG_SECTION

	/****************************/


	/**** Verbindung zur DB aufbauen ***************/
	if(!(datenbankVerbinden(pmyError, chdatenbank))) 
	{
		ERROR_MSG_OUT 
		return ERROR;
	}
	/**********************************************/

	if (lDate == 0) /* wenn keine Datumseingabe dann errechnen Datum */
	{
		srvLoad.VERTRIEBSZENTRUMNR = sVZ;
		srvLoad.LADEDATUM = 0;
		srvLoad.LADEKIPPZEIT = 120000;
		if ( Mcallplanload_GetInitializeData( &srvLoad, &stError, FALSE ) == IS_ERROR )
		{
			return CheckSql( fun, &stError, "%s", stError.spError );
		}
		lDate = srvLoad.LADEDATUM;
	}
	lDatumkommi = lDate;

	char start_msg[40];
	sprintf(start_msg,"Start Datum: %d",lDate);
	PrintMsg( fun, start_msg, chLogFile, sVZ, HINWEIS, 0 );

	/**** Tabelle customerroutecheck befüllen ******/
	if (!(StartFillRouteCheckTable( pmyError, sVZ, sDebuggingActive, spBuffer )))
	{
		ERROR_MSG_OUT 

		rollbackWork(pmyError);
		datenbankSchliessen(pmyError);

		return ERROR;
	}
	/**********************************************/

	/**** Verbindung zur DB trennen ***************/
	if(!(datenbankSchliessen(pmyError))) 
	{
		ERROR_MSG_OUT 
		return ERROR;
	}
	/**********************************************/


	sprintf(start_msg,"ENDE: %d Saetze geladen",(iZaehler-iDuplicateZaehler));
	PrintMsg( fun, start_msg, chLogFile, sVZ, HINWEIS, 0 );

	return OK;
}

/***** ENDE MAIN ************************************************************/

/***** WriteLogInfo nur zum Aufruf von PrintMsg ******************************/

void WriteLogInfo( char *error_msg, char mld, int rc )
{
	PrintMsg( "loadroutecheck", error_msg, chLogFile, sVZ, mld, rc );
}

 /***** PRINT-MSG ************************************************************/
 void PrintMsg( char *fun, char *error_msg, char* log_file, short haus, char mld, int rc )
 {	//Standard-Funktion zur Ausgabe von Meldungen ins definierte LOGFILE
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
	    "loadroutecheck",
	    fun );

   fprintf(fp," %s\n", error_msg );
   fclose(fp);
}
/**********************************************************************************/
 
/*************** datenbankVerbinden ***********************************************/
bool datenbankVerbinden(tError* myError, char* spDbName)
{	//Connected zur DB
  if ( OpenDb( spDbName, myError ) != IS_OK )
      return FALSE;
  
  if ( SetIsolation( DIRTY_READ, myError ) != IS_OK )
	  return FALSE;
  
  if ( SetLockMode( 20, myError ) != IS_OK )
	  return FALSE;
  
  return TRUE;
}
/**********************************************************************************/


/*************** datenbankSchliessen **********************************************/
bool datenbankSchliessen(tError* myError)
{	//Disconnected von der DB
//  if ( CloseDb( myError ) != IS_OK )
//      return FALSE;
   
  return TRUE;
}
/**********************************************************************************/


/*************** rollbackWork *****************************************************/
bool rollbackWork(tError* myError)
{	//Führt einen Rollback auf der Datenbank durch
	if ( Rollback( "loadrtchk", myError ))
	    return FALSE;
	 
	return TRUE;
}
/**********************************************************************************/


/*************** FillRouteCheckTable **********************************************/
bool StartFillRouteCheckTable( tError* myError, short sVZ, short sDebuggingActive, char* spBuffer )
{	//Befüllen der Tabelle customerroutecheck
	EXEC SQL BEGIN DECLARE SECTION;
	int				iLagerDurchlaufZeit;//Parameter der Auftragserfassung, spezifiziert die Lagerdurchlaufzeit
	int				iLagerDurchlaufEil; //Parameter der Auftragserfassung, spezifiziert die Eildurchlaufzeit
	long			lLagerDurchlaufZeit;//Parameter der Auftragserfassung, spezifiziert die Lagerdurchlaufzeit
	long			lLagerDurchlaufEil; //Parameter der Auftragserfassung, spezifiziert die Eildurchlaufzeit
	int				iTourCheckTime;		//Parameter der Auftragserfassung, spezifiziert, wie viele Minuten vor der Tourabfahrt die Prüfung, "Existiert ein Auftrag des Kunden?" erfolgen soll
	int				iZeitversand;		//Versandzeit der Tour
	long			lZeitBegin=0;		//Startzeit fuer Pruefung
	long			lZeitEnde=0;		//Endezeit fuer Pruefung
	long			lTimefrom;			//Startzeit Routing
	long			lTimeto;			//Endezeit Routing
	long			lCheckTime;			//Errechnete Zeit, bei der eine Prüfung "Existiert ein Auftrag des Kunden?" erfolgen soll
	short			smyVZ;				//Nummer des VZs
	short			OrgVZ;				//Nummer des Orginalfiliale
	short			sDestVZ;			//Nummer des Orginalfiliale
	short			iZero=0;			//Dummy
	short			iCheckTimeToClose=0;//Pruefzeit vor Betriebsende (Apo)
	long			lzeitbeginam;		//Oeffnungszeit morgens
	long			lzeitendeam;		//Schliesszeit morgens
	long			lzeitbeginpm;		//Oeffnungszeit abends
	long			lzeitendepm;		//Schliesszeit abends
	long			lzeit2tour;			//Checktime vor Tour
	long			lzeit2tourplan;		//Checktime vor Kunden-Tour
	long			lzeittourcheck;		//Checktime vor Tour
	long			lHHMM;				//Hilfsfeld zur Uebergabe der Minuten im HHMM-Format
	bool			bOhneSchliesszeit;  //Keine Mittagsschliesszeit beachten
	long			lTourZeit;			//Zeit der Tour

	kndtourenS*		pkndtourenS;		//Struktur für das Ergebnis der DB-Abfrage 
	EXEC SQL END DECLARE SECTION;

	kndtourenS		skndtourenS;			//Struktur für das Ergebnis der DB-Abfrage 


	pkndtourenS = &skndtourenS;
	smyVZ = sVZ;	

	//Prepare: sel_KndTouren und ins_cordercheck
	if(!(PrepareFillRouteCheckTable(myError, sVZ, sDebuggingActive, spBuffer )))
		 return FALSE;
	
	//Parameter TourCheckTime aus paraauftragbearb des VZs lesen
	EXEC SQL 	select tourchecktime, durchlaufnormal, durchlaufeilbote, CheckTimeToClose
				into :iTourCheckTime, :iLagerDurchlaufZeit, :iLagerDurchlaufEil, :iCheckTimeToClose
				from paraauftragbearb
				where paraauftragbearb.filialnr = :smyVZ;
	if( ! ((bool)(CheckSql( "StartFillRouteCheckTable: select tourchecktime", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
		return FALSE;
	
	//Endezeit aus zeitarten lesen
	EXEC SQL 	execute sel_zeitart into :lZeitBegin,:lZeitEnde;
	if (sqlca.sqlcode == 100)
	{
		lZeitEnde = 0;
	}
	else if( ! ((bool)(CheckSql( "StartFillRouteCheckTable: sel_zeitart", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
		return FALSE;

	if (!(iTourCheckTime) && !(iLagerDurchlaufZeit)) //Ist keiner der Parameter Lagerdurchlaufzeit und Prüfzeit Tour gesetzt, stoppt das Programm
	{
		DEBUG_SECTION
			fprintf(stderr,"VZ: %d \n", sVZ);
			fprintf(stderr,"Tourchecktime und Lagerdurchlaufzeit für VZ nicht gesetzt\n");
		END_DEBUG_SECTION
	}
	else if (!(iTourCheckTime))	//Ist der Parameter Prüfzeit Tour nicht gesetzt, wird die Lagerdurchlaufzeit + 5 Minuten verwendet
	{	
		iTourCheckTime = iLagerDurchlaufZeit + 5;

		DEBUG_SECTION
			fprintf(stderr,"VZ: %d \n", sVZ);
			fprintf(stderr,"Lagerdurchlaufzeit: %d \n", iLagerDurchlaufZeit);
			fprintf(stderr,"Tourchecktime: %d \n", iTourCheckTime);
		END_DEBUG_SECTION

	}
	else
	{
		DEBUG_SECTION
			fprintf(stderr,"VZ: %d \n", sVZ);
			fprintf(stderr,"Tourchecktime: %d \n", iTourCheckTime);
		END_DEBUG_SECTION
	}

	EXEC SQL begin work;
	if( ! ((bool)(CheckSql( "StartFillRouteCheckTable: begin work initial", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
		return FALSE;

	EXEC SQL open CselKndTouren; //Open Cursor über TOURPLANTAGWOCHE join TOURPLANWOCHE
	if( ! ((bool)(CheckSql( "StartFillRouteCheckTable: open cursor CselKndTouren", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
		return FALSE;
	

	for(iZaehler=0 ;;iZaehler++ )
	{
		if (iZaehler%500 == 0) //Commit nach 500 Inserts
		{
			EXEC SQL commit work;
			sprintf(spBuffer, "StartFillRouteCheckTable: commit work %d", iZaehler );
			if( ! ((bool)(CheckSql( spBuffer, myError, "%s", "")== IS_OK ? TRUE :FALSE)))
			{
				EXEC SQL close CselKndTouren;
				EXEC SQL free CselKndTouren;
				return FALSE;
			}

			EXEC SQL begin work;
			sprintf(spBuffer, "StartFillRouteCheckTable: begin work %d", iZaehler );
			if( ! ((bool)(CheckSql( spBuffer, myError, "%s", "")== IS_OK ? TRUE :FALSE)))
			{
				EXEC SQL close CselKndTouren;
				EXEC SQL free CselKndTouren;
				return FALSE;
			}
		}

		//FETCH Cursor über TOURPLANTAGWOCHE join TOURPLANWOCHE
		EXEC SQL fetch CselKndTouren into 
			:pkndtourenS->VERTRIEBSZENTRUMNR,
			:pkndtourenS->KUNDENNR,
			:pkndtourenS->TOURID,
			:OrgVZ,
			:lzeit2tour,
			:lzeit2tourplan;

		if (sqlca.sqlcode == 100)
			break;

		lTourZeit = atol(pkndtourenS->TOURID)/100;
		AllgAddTime (lTourZeit*100, (iLagerDurchlaufEil*(-100)), &lTourZeit);
		lTourZeit = lTourZeit/100;
		EXEC SQL open CselKundeurlaub using //Open Cursor über KUNDEURLAUB
			:pkndtourenS->KUNDENNR;
		if( ! ((bool)(CheckSql( "StartFillRouteCheckTable: open cursor CselKundeurlaub", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
			return FALSE;

		//FETCH Cursor über KUNDEURLAUB
		EXEC SQL fetch CselKundeurlaub;
		if (sqlca.sqlcode == 0)	//wenn Urlaub, dann keine Ueberwachung
			continue;
		if (sqlca.sqlcode < 0)		
		{
			sprintf( spBuffer, "%ld/%ld", sqlca.sqlcode, sqlca.sqlerrd[1] );
			PrintMsg( "StartFillRouteCheckTable FETCH: CselKndTouren ", spBuffer, chLogFile, sVZ, FEHLER, -1);

			EXEC SQL close CselKndTouren;
			EXEC SQL free CselKndTouren;

			strcpy(myError->spError, spBuffer);

			return FALSE;
		}


		//VersandZeit der Tour lesen
		EXEC SQL 	select zeitversand into :iZeitversand  
					from tour
					where tour.filialnr = :smyVZ
					and tour.tourid = :pkndtourenS->TOURID
						and tour.datumkommi = :lDatumkommi;
		if( ! ((bool)(CheckSql( "StartFillRouteCheckTable select zeitversand", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
		{
			EXEC SQL close CselKndTouren;
			EXEC SQL free CselKndTouren;
			return FALSE;
		}

		lzeittourcheck = iZeitversand;	//Wert initialisieren
		if(lzeit2tourplan > lzeit2tour)
		{
			lHHMM = Set2HHMM(lzeit2tourplan);
			AllgAddTime (iZeitversand, (lHHMM*(-100)), &lzeittourcheck);
		}
		else if(lzeit2tour > 0)
		{
			lHHMM = Set2HHMM(lzeit2tour);
			AllgAddTime (iZeitversand, (lHHMM*(-100)), &lzeittourcheck);
		}

		if(atol(pkndtourenS->TOURID) > 235999) lzeittourcheck += 240000;

		EXEC SQL open CselBetriebsende using :pkndtourenS->KUNDENNR; //Open Cursor über KDBETRIEBSENDE
		if( ! ((bool)(CheckSql( "StartFillRouteCheckTable: open cursor CselBetriebsende", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
			return FALSE;

		//FETCH Cursor über KDBETRIEBSENDE
		EXEC SQL fetch CselBetriebsende into 
			:lzeitbeginam,
			:lzeitendeam,
			:lzeitbeginpm,
			:lzeitendepm;
		if (sqlca.sqlcode == 100)	//kein Eintrag vorhanden
		{
			lzeitbeginam = 80000;
			lzeitendeam = 200000;
			lzeitbeginpm = 0;
			lzeitendepm = 0;
		}
		else if (lzeitbeginam == 0		//oder leer
				&& lzeitendeam == 0
				&& lzeitbeginpm == 0
				&& lzeitendepm == 0)
		{
			lzeitbeginam = 80000;
			lzeitendeam = 200000;
			lzeitbeginpm = 0;
			lzeitendepm = 0;
		}
		lHHMM = Set2HHMM((long)iCheckTimeToClose);
		AllgAddTime (lzeitendeam,(lHHMM*(-100)), &lzeitendeam);
		AllgAddTime (lzeitendepm,(lHHMM*(-100)), &lzeitendepm);
		if(OrgVZ == smyVZ || OrgVZ == 0)
		{
			EXEC SQL execute sel_routinghome into :sDestVZ,:lTimefrom,:lTimeto using :pkndtourenS->KUNDENNR,:lTourZeit;
			if (sqlca.sqlcode == 100)
			{
//				EXEC SQL 	select durchlaufnormal,durchlaufeilbote 
//						into :lLagerDurchlaufZeit,:lLagerDurchlaufEil
//						from paraauftragbearb
//						where paraauftragbearb.filialnr = :sDestVZ;
//				AllgAddTime(lTimefrom*100,(iLagerDurchlaufEil+1)*100,&lTimefrom);
//				AllgAddTime(lTimeto*100,(lLagerDurchlaufZeit+1)*100,&lTimeto);
//				if(iZeitversand > lTimefrom && iZeitversand <= lTimeto) continue;
			}
			else if( ! ((bool)(CheckSql( "StartFillRouteCheckTable: sel_routinghome", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
			{
				return FALSE;
			}
			else
			{
				EXEC SQL 	select durchlaufnormal,durchlaufeilbote 
						into :lLagerDurchlaufZeit,:lLagerDurchlaufEil
						from paraauftragbearb
						where paraauftragbearb.filialnr = :sDestVZ;
				lHHMM = Set2HHMM(iLagerDurchlaufEil+1);
				AllgAddTime(lTimefrom*100,(lHHMM)*(-100),&lTimefrom);
				lHHMM = Set2HHMM(lLagerDurchlaufZeit+1);
				AllgAddTime(lTimeto*100,(lHHMM)*(-100),&lTimeto);
				if(iZeitversand > lTimefrom && iZeitversand <= lTimeto) continue;
			}
		}
		else
		{
			EXEC SQL execute sel_routing into :lTimefrom,:lTimeto using :OrgVZ,:pkndtourenS->KUNDENNR,:lTourZeit;
			if (sqlca.sqlcode == 100)
			{
				continue;
			}
			else if( ! ((bool)(CheckSql( "StartFillRouteCheckTable: sel_routing", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
			{
				return FALSE;
			}
			else
			{
				EXEC SQL 	select durchlaufnormal,durchlaufeilbote 
						into :lLagerDurchlaufZeit,:lLagerDurchlaufEil
						from paraauftragbearb
						where paraauftragbearb.filialnr = :OrgVZ;
				lHHMM = Set2HHMM(lLagerDurchlaufEil+1);
				AllgAddTime(lTimefrom*100,(lHHMM)*(-100),&lTimefrom);
				lHHMM = Set2HHMM(lLagerDurchlaufZeit+1);
				AllgAddTime(lTimeto*100,(lHHMM)*(-100),&lTimeto);
			}
		}

		//Zeit für Prüfung berechnen
		lHHMM = Set2HHMM((long)iTourCheckTime);
		AllgAddTime (iZeitversand, lHHMM*(-100), &lCheckTime);
		if(atol(pkndtourenS->TOURID) > 235999) lCheckTime += 240000;
		DEBUG_SECTION
				fprintf(stderr,"VZ:%d / KDNR:%d / TID:%s / TCT: %d / ZVS: %d -> PT: %d \n", 
				pkndtourenS->VERTRIEBSZENTRUMNR,
				pkndtourenS->KUNDENNR,
				pkndtourenS->TOURID,
				iTourCheckTime,
				iZeitversand,
				lCheckTime
				);
		END_DEBUG_SECTION

		EXEC SQL open CselKundenotdienst using //Open Cursor über KUNDENOTDIENST
			:pkndtourenS->KUNDENNR;
		if( ! ((bool)(CheckSql( "StartFillRouteCheckTable: open cursor CselKundenotdienst", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
			return FALSE;

		//FETCH Cursor über KUNDENOTDIENST
		bOhneSchliesszeit = false;
		EXEC SQL fetch CselKundenotdienst;
		if (sqlca.sqlcode == 0)	//wenn Notdienst, dann ignorieren Schliesszeit
		{
			bOhneSchliesszeit = true;
		}
		if (sqlca.sqlcode < 0)	
		{
			sprintf( spBuffer, "%ld/%ld", sqlca.sqlcode, sqlca.sqlerrd[1] );
			PrintMsg( "StartFillRouteCheckTable FETCH: CselKundenotdienst ", spBuffer, chLogFile, sVZ, FEHLER, -1);

			EXEC SQL close CselKndTouren;
			EXEC SQL free CselKndTouren;

			strcpy(myError->spError, spBuffer);

			return FALSE;
		}

		//Bis max. eingetragene Endezeit
		if (lZeitEnde > 0)
		{
			if (lCheckTime > lZeitEnde) lCheckTime = lZeitEnde;
		}
		// Nicht vor Startzeit
		if (lZeitBegin > lCheckTime) continue;
		if (!bOhneSchliesszeit)
		{
			if (lCheckTime > lzeitendeam &&
				lzeitendeam > 0 &&
				(lCheckTime < lzeitbeginpm ||
				lzeitbeginpm == 0) )
			{
				lCheckTime = lzeitendeam;
			}
			if (lzeitendepm > 0)
			{
				if (lCheckTime > lzeitendepm) lCheckTime = lzeitendepm;
			}
		}
		if (lCheckTime > lzeittourcheck) lCheckTime = lzeittourcheck;
		//Insert des Satzes in customerordercheck
		EXEC SQL EXECUTE ins_cordercheck USING
					:pkndtourenS->VERTRIEBSZENTRUMNR,
					:pkndtourenS->KUNDENNR,
					:lCheckTime,
					:iZero,
					:pkndtourenS->TOURID;
		if( ! ((bool)(CheckSql( "StartFillRouteCheckTable execute ins_cordercheck", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
		{
			if (myError->lSqlcode == -239)	
			{	
				DEBUG_SECTION
					fprintf(stderr,"Duplette, wird ignoriert\n");
   				END_DEBUG_SECTION

				iDuplicateZaehler++;
				continue;
			}

			EXEC SQL close CselKndTouren;
			EXEC SQL free CselKndTouren;
			return FALSE;
		}
	}

	EXEC SQL commit work;
	if( ! ((bool)(CheckSql( "StartFillRouteCheckTable commit work final", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
	{
		EXEC SQL close CselKndTouren;
		EXEC SQL free CselKndTouren;
		return FALSE;
	}

	DEBUG_SECTION
		fprintf(stderr,"LOAD: %d Saetze geladen\n",(iZaehler-iDuplicateZaehler));
	END_DEBUG_SECTION

	EXEC SQL  close CselKndTouren ;
	if( ! ((bool)(CheckSql( "StartFillRouteCheckTable close CselKndTouren ", myError, "%s", "")== IS_OK ? TRUE :FALSE)))
	{
		EXEC SQL free CselKndTouren;
		return FALSE;
	}

	EXEC SQL  free CselKndTouren ;
	if( ! ((bool)(CheckSql("StartFillRouteCheckTable: free CselKndTouren ", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/

	return TRUE;
}
/**********************************************************************************/



/*************** PrepareFillRouteCheckTable ************************************/
bool PrepareFillRouteCheckTable( tError* myError, short sVZ, short sDebuggingActive, char* spBuffer  )
{	//Bereitet die SQL-Statements gegen die Datenbak vor
	EXEC SQL BEGIN DECLARE SECTION;
	char chSelectStr[2048]; //String für Select-Statements
	EXEC SQL END DECLARE SECTION;

	long	lBuffer;
	char	error_msg[81];

	/******* Select Cursor über TOURPLANTAGWOCHE, TOURPLANWOCHE **************/
	strcpy(chSelectStr,"select ");
	strcat(chSelectStr," Tour.filialnr, "); 
	strcat(chSelectStr," Tourplantag.idfnr, "); 
	strcat(chSelectStr," Tourplantag.tourid, "); 
	strcat(chSelectStr," Kunde.originalfilialnr, "); 
	strcat(chSelectStr," Tourplantag.checktimetotour, "); 
	strcat(chSelectStr," Tour.checktimetotour "); 
	strcat(chSelectStr," from Tour, Tourplantag, Kundeschalter, Kunde ");
	strcat(chSelectStr," where ");          
	strcat(chSelectStr," Tour.filialnr = Tourplantag.vertriebszentrumnr and ");
	strcat(chSelectStr," Tour.datumkommi = Tourplantag.datumkommi and ");
	strcat(chSelectStr," Tour.tourid = Tourplantag.tourid and ");
	strcat(chSelectStr," Tour.tourid not like '4759%' and");
	strcat(chSelectStr," (Tourplantag.scheckorder = '1' or");
	strcat(chSelectStr," Tour.scheckorder = '1') and");
	
	//nur Kunden des übergebenen  VZ 
	strcat(chSelectStr," Tourplantag.vertriebszentrumnr = ");
	sprintf(spBuffer, "%d and ", sVZ);  
	strcat(chSelectStr, spBuffer);

	//nur Kundengruppen 1 - 6 des VZs	
	strcat(chSelectStr," Tourplantag.idfnr = Kunde.kundennr and ");		
	strcat(chSelectStr," Tourplantag.vertriebszentrumnr = Kunde.vertriebszentrumnr and ");		
	strcat(chSelectStr," Kunde.kdgruppe in ('01', '02', '03', '04', '05', '06' ) and ");
//	strcat(chSelectStr," Tourplantag.idfnr in ");		
//	strcat(chSelectStr," ( select distinct kundennr from kunde where VertriebszentrumNr = ");
//	sprintf(spBuffer, "%d and ", sVZ);  
//	strcat(chSelectStr, spBuffer);
//	strcat(chSelectStr," kdgruppe in ('01', '02', '03', '04', '05', '06' ) ) and ");

	//keine gesperrten Kunden des VZs	
	strcat(chSelectStr," Tourplantag.idfnr = Kundeschalter.kundennr and ");		
	strcat(chSelectStr," Tourplantag.vertriebszentrumnr = Kundeschalter.vertriebszentrumnr and ");		
	strcat(chSelectStr," Kundeschalter.skdkundeaegesperrt != '1' and ");
	strcat(chSelectStr," Kundeschalter.skdwatchorder = '1' and ");
//	strcat(chSelectStr," Tourplantag.idfnr not in ");	
//	strcat(chSelectStr," ( select distinct idfnr from kundeschalter where VertriebszentrumNr =  ");
//	sprintf(spBuffer, "%d and ", sVZ);  
//	strcat(chSelectStr, spBuffer);
//	strcat(chSelectStr," skdkundeaegesperrt = '1' ) and ");

	//keine gesperrten Touren	
	strcat(chSelectStr," Tourplantag.tourinaktiv != '1' and ");	

	//keine Sonder-Touren	
	strcat(chSelectStr," Tourplantag.kzautozuord = '1' and ");	

	//heutiges Datum
	strcat(chSelectStr,"Tourplantag.datumkommi = ");  
	sprintf(spBuffer, "%d ", lDate);
	strcat(chSelectStr, spBuffer);


	strcat(chSelectStr," order by Tourplantag.tourid, Tourplantag.idfnr " );

	DEBUG_SECTION
		fprintf(stderr,"\nPREPARE sel_KndTouren: %s \n\n", chSelectStr); 
	END_DEBUG_SECTION

	EXEC SQL PREPARE sel_KndTouren FROM :chSelectStr;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: prepare sel_KndTouren", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	
	exec sql declare CselKndTouren cursor with hold for sel_KndTouren;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: declare CselKndTouren", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/

	/******* Prepare Insert into customerordercheck **************************/
	strcpy(chSelectStr,"insert into customerordercheck (");
	strcat(chSelectStr,"BranchNo, ");          
	strcat(chSelectStr,"CustomerNo, ");          
	strcat(chSelectStr,"checkordertime, ");          
	strcat(chSelectStr,"orderstatus, ");          
	strcat(chSelectStr,"tourid");          
	strcat(chSelectStr," ) values ");
	strcat(chSelectStr,"( ?,?,?,?,?)");

	EXEC SQL PREPARE ins_cordercheck FROM :chSelectStr;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: prepare ins_cordercheck", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/

	/******* Prepare Holen Zeitarten **************************/
	strcpy(chSelectStr,"select zeitbegin,zeitende from zeitarten ");
	strcat(chSelectStr,"where zeitart = 10 ");
	strcat(chSelectStr,"and vertriebszentrumnr = ");          
	sprintf(spBuffer, "%d ", sVZ);  
	strcat(chSelectStr, spBuffer);
	strcat(chSelectStr,"and weekday = ");          
	lWeekDay = AllgGetWeekDay(lDate,error_msg);
	sprintf(spBuffer, "%d ", lWeekDay);
	strcat(chSelectStr, spBuffer);

	EXEC SQL PREPARE sel_zeitart FROM :chSelectStr;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: prepare sel_zeitart", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/

	/******* Prepare Holen Betriebsendezeiten **************************/
	strcpy(chSelectStr,"select zeitbeginam,zeitendeam,zeitbeginpm,zeitendepm from kdbetriebsende ");
	strcat(chSelectStr,"where kundennr = ? ");          
	strcat(chSelectStr,"and vertriebszentrumnr = ");          
	sprintf(spBuffer, "%d ", sVZ);  
	strcat(chSelectStr, spBuffer);
	strcat(chSelectStr,"and weekday = ");          
	lWeekDay = AllgGetWeekDay(lDate,error_msg);
	sprintf(spBuffer, "%d ", lWeekDay);
	strcat(chSelectStr, spBuffer);

	EXEC SQL PREPARE sel_kdbetriebsende FROM :chSelectStr;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: prepare sel_kdbetriebsende", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	exec sql declare CselBetriebsende cursor with hold for sel_kdbetriebsende;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: declare CselBetriebsende", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/

	/******* Prepare Pruefen Urlaubszeiten **************************/
	strcpy(chSelectStr,"select 1 from kundeurlaub ");
	strcat(chSelectStr,"where kundennr = ? ");          
	strcat(chSelectStr,"and vertriebszentrumnr = ");          
	sprintf(spBuffer, "%d ", sVZ);  
	strcat(chSelectStr, spBuffer);
	sprintf(spBuffer, "%d ", lDate);
	strcat(chSelectStr,"and datumgueltigab <= ");          
	strcat(chSelectStr, spBuffer);
	strcat(chSelectStr,"and datumgueltigbis >= ");          
	strcat(chSelectStr, spBuffer);

	EXEC SQL PREPARE sel_kundeurlaub FROM :chSelectStr;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: prepare sel_kundeurlaub", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	exec sql declare CselKundeurlaub cursor with hold for sel_kundeurlaub;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: declare CselKundeurlaub", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/

	/******* Prepare Pruefen Notdienst **************************/
	strcpy(chSelectStr,"select 1 from kundenotdienstplan ");
	strcat(chSelectStr,"where kundennr = ? ");          
	strcat(chSelectStr,"and vertriebszentrumnr = ");          
	sprintf(spBuffer, "%d ", sVZ);  
	strcat(chSelectStr, spBuffer);
	sprintf(spBuffer, "%d ", lDate);
	strcat(chSelectStr,"and datum = ");
	strcat(chSelectStr, spBuffer);

	EXEC SQL PREPARE sel_kundenotdienst FROM :chSelectStr;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: prepare sel_kundenotdienst", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	exec sql declare CselKundenotdienst cursor with hold for sel_kundenotdienst;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: declare CselKundenotdienst", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/

	/******* Prepare Holen Routing **************************/
	//bei gerouteten Kunden in Zielfiliale nur innerhalb Routingzeiten	
	strcpy(chSelectStr,"select ");
	strcat(chSelectStr," Customerrouting.timefrom, "); 
	strcat(chSelectStr," Customerrouting.timeto "); 
	strcat(chSelectStr," from Customerrouting ");
	strcat(chSelectStr," where ");          
	strcat(chSelectStr," Customerrouting.branchno = ?");		
	strcat(chSelectStr," and Customerrouting.customerno = ?");		
	strcat(chSelectStr," and Customerrouting.destbranchno = ");
	sprintf(spBuffer, "%d ", sVZ);  
	strcat(chSelectStr, spBuffer);
	strcat(chSelectStr," and Customerrouting.timefrom < ? ");
//	strcat(chSelectStr," and Customerrouting.timeto > ? ");
	strcat(chSelectStr,"and weekday = ");          
	sprintf(spBuffer, "%d ", lWeekDay);
	strcat(chSelectStr, spBuffer);

	EXEC SQL PREPARE sel_routing FROM :chSelectStr;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: prepare sel_routing", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/
	//bei gerouteten Kunden in Herkunftsfiliale nur ausserhalb Routingzeiten	
	strcpy(chSelectStr,"select ");
	strcat(chSelectStr," Customerrouting.destbranchno,");		
	strcat(chSelectStr," Customerrouting.timefrom, "); 
	strcat(chSelectStr," Customerrouting.timeto "); 
	strcat(chSelectStr," from Customerrouting ");
	strcat(chSelectStr," where ");          
	strcat(chSelectStr," Customerrouting.branchno = ");		
	sprintf(spBuffer, "%d ", sVZ);  
	strcat(chSelectStr, spBuffer);
	strcat(chSelectStr," and Customerrouting.customerno = ?");		
	strcat(chSelectStr," and Customerrouting.timefrom > ? ");
//	strcat(chSelectStr," and Customerrouting.timeto < ? ");
	strcat(chSelectStr," and weekday = ");          
	sprintf(spBuffer, "%d ", lWeekDay);
	strcat(chSelectStr, spBuffer);

	EXEC SQL PREPARE sel_routinghome FROM :chSelectStr;
	if( ! ((bool)(CheckSql("PrepareFillRouteCheckTable: prepare sel_routinghome", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/


	//************* Löschen aller alten Einträge aus customerordercheck ***/
	if(!(DeleteRouteCheckTable(myError, sVZ, sDebuggingActive, spBuffer )))
		 return FALSE;
	/**********************************************************************/

	return TRUE;
}
	/**********************************************************************/

	/*************** DeleteRouteCheckTable ************************************/
bool DeleteRouteCheckTable( tError* myError, short sVZ, short sDebuggingActive, char* spBuffer  )
{	//Löschen aller alten Einträge aus customerordercheck
	EXEC SQL BEGIN DECLARE SECTION;
	char chSelectStr[2048];	//String für Select-Statements
	EXEC SQL END DECLARE SECTION;

	int iZaehler=0;			//Zähler

	sprintf(spBuffer, "%d", sVZ);

	/******* Select Cursor und Delete-Statement über customerordercheck  *****/
	strcpy(chSelectStr, "select branchno, customerno, checkordertime, orderstatus, tourid " );
	strcat(chSelectStr, " from customerordercheck ");
	strcat(chSelectStr, "where CUSTOMERORDERCHECK.BRANCHNO = ");
	strcat(chSelectStr, spBuffer);
	strcat(chSelectStr, " for update");

	EXEC SQL PREPARE sel_del_cordercheck FROM :chSelectStr;
	if( ! ((bool)(CheckSql("DeleteRouteCheckTable: prepare sel_del_cordercheck", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;

	EXEC SQL declare DelCordercheck Cursor with hold for sel_del_cordercheck;
	if( ! ((bool)(CheckSql("DeleteRouteCheckTable: declare DelCordercheck", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	
	strcpy( chSelectStr, "delete from customerordercheck " );
	strcat( chSelectStr, "where current of DelCordercheck " );
	EXEC SQL prepare exec_del_cordercheck from :chSelectStr;
	if( ! ((bool)(CheckSql("DeleteRouteCheckTable: prepare exec_del_corderchek ", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/


	/******* Löschen aller alten Einträge ********************************/
	EXEC SQL open DelCordercheck;	//Open Cursor
	if( ! ((bool)(CheckSql("DeleteRouteCheckTable: open DelCordercheck ", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;

    EXEC SQL begin work;
	if( ! ((bool)(CheckSql("DeleteRouteCheckTable: begin work initial ", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
	{
		EXEC SQL close DelCordercheck ;
		EXEC SQL free DelCordercheck;
		return FALSE;
	}

	for(iZaehler=0 ;;iZaehler++ )
	{
		if (iZaehler%200 == 0)
		{	//Commit nach 200 Deletes
			EXEC SQL commit work;	
			sprintf(spBuffer, "DeleteRouteCheckTable: commit work %d", iZaehler );
			if( ! ((bool)(CheckSql( spBuffer, myError, "%s", "")== IS_OK ? TRUE :FALSE)))
			{
				EXEC SQL close DelCordercheck ;
				EXEC SQL free DelCordercheck;
				return FALSE;
			}

			EXEC SQL begin work;
			sprintf(spBuffer, "DeleteRouteCheckTable: begin work %d", iZaehler );
			if( ! ((bool)(CheckSql( spBuffer, myError, "%s", "")== IS_OK ? TRUE :FALSE)))
			{
				EXEC SQL close DelCordercheck ;
				EXEC SQL free DelCordercheck;
				return FALSE;
			}
		}

		EXEC SQL  fetch DelCordercheck;  //FETCH DelCordercheck
		if (sqlca.sqlcode == 100)	
			break;
		if (sqlca.sqlcode != 0)		
		{
			sprintf( spBuffer, "%ld/%ld", sqlca.sqlcode, sqlca.sqlerrd[1] );
			PrintMsg( "DeleteRouteCheckTable fetch DelCordercheck ", spBuffer, chLogFile, sVZ, FEHLER, -1);

			EXEC SQL close DelCordercheck ;
			EXEC SQL free DelCordercheck;

			strcpy(myError->spError, spBuffer);
			return FALSE;
		}
		
		EXEC SQL execute exec_del_cordercheck;  //DELETE des Satzes ausführen 
		if( ! ((bool)(CheckSql("DeleteRouteCheckTable execute exec_del_cordercheck ", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		{
			EXEC SQL close DelCordercheck ;
			EXEC SQL free DelCordercheck;

			return FALSE;
		}
	}

	EXEC SQL commit work;
	if( ! ((bool)(CheckSql("DeleteRouteCheckTable commit work final", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
	{
		EXEC SQL close DelCordercheck ;
		EXEC SQL free DelCordercheck;
		return FALSE;
	}

	DEBUG_SECTION
		fprintf(stderr,"START: %d Saetze gelöscht aus customerordercheck\n",iZaehler);
   	END_DEBUG_SECTION

	EXEC SQL  close DelCordercheck ;
	if( ! ((bool)(CheckSql("DeleteRouteCheckTable commit work final", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
	{
		EXEC SQL free DelCordercheck;

		return FALSE;
	}

	EXEC SQL  free DelCordercheck ;
	if( ! ((bool)(CheckSql(" ", myError, "%s", "") == IS_OK ? TRUE : FALSE )))
		return FALSE;
	/**********************************************************************/

	return TRUE;
}

 long Set2HHMM(long lMinuten)
 {
	 return ( (lMinuten/60*100) + (lMinuten%60) );
 }

/**********************************************************************************/

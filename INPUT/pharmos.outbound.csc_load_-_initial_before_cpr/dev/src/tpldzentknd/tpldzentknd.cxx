/*****************************************************************************/
/*                                                                           */
/*   Wichtig:                                                                */
/*            Es wird mit zwei unterschiedlichen Xvsam-File-Systemen ge-     */
/*            arbeitet.                                                      */
/*            Hierfür müssen (leider) zwei verschiedene Funktionstypen an-   */
/*            gezogen werden.                                                */
/*            Altes Xvsamsystem: ...Xvsam()                                  */
/*            Neues Xvsamsystem: ...Ivsam()  (Dateinr wird mit uebergeben!)  */
/*                                                                           */
/*   Unterscheidung:                                                         */
/*            Die Funktionen werden ueber den Binder angezogen.              */                                                
/*            #ifdef VSAM_MU -> neue Xvsam-Umgebung                          */
/*                                                                           */
/*   Librarys/Objekte/Include:                                               */
/*            xindex.h                                                       */
/*            liblibxvsam6.a                                                 */
/*            Liblcvsam.a                                                    */
/*            xvsamapi.o                                                     */
/*                                                                           */
/*****************************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tpldzentknd"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/*****************************************************************************/
/* Einfuegen neuer Tabellen in das Kundenladeprogramm                       */
/*****************************************************************************/
/* 1 Tabelle im Incudefile definieren und ANZ_TABELLEN aktualisieren         */
/* 2 Eintrag in Funktion SetzeSchalterTabelle erzeugen                       */
/* 3 Implementierung und Aufruf der Initialisierungsfunktion (create table..)*/
/* 4 Implementierung und Aufruf der Ladefunktionfunktion (in Bezug auf DKKUL)*/
/* 5 Implementierung und Aufruf der Endefunktion (drop/create index, rename )*/
/* 6 Update Statistics Eintrag hinzufuegen                                   */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>				  
#include <time.h>
#include <signal.h>
#include <string.h>         /* hajo */
#include <memory.h>         /* hajo */
#include <unistd.h>         /* hajo */

#include "kndlang.h"
#include "kundelagerinfo.h"
#include "kdbetriebsende.h"
#include "kdkonditionsgruppe.h"
#include "kunde.h"
#include "kundekondi.h"
#include "kundeschalter.h"
#include "cstdisccont.h"
#include "kndausku.h"
#include "zeitarten.h"
#include "tpldzentknd.h"
#include "pplib/allg.h"
#include "libtpld/struct.h"
#include "libtpld/define.h"
#include "zeitstempel.h"
#include "callplanmaintenance.h"
#include "customerrouting.h"
#include "payterm.h"
#include "cstpaymentterms.h"
#include "cstprint.h"
#include "libtpld/vtcodum.h"
#include "debtlimit.h"
#include "libtpld/dadedb.h"
#include <libtpld/coboltoasci.h>    /* hajo */
#include "dkkul_perl.h"

/* #include "callplanmaint.h" */ /* hajo */

exec sql include sqlca;

#undef NULL  

#define INSERT             1
#define FILE_NOT_FOUND     1
#define HINW             'H'
#define FEHL             'F'
#define RIO_EOF          110
#define RIO_NOFIND       111
#define VB				 "VB"
#define BLANC            ' '
#define SQLUPD            sqlca.sqlerrd[2]         /* Anzahl erfolgeter Upd  */
#define ERROR_MSG2(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define ERROR_MSG3(x,y)     if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s %s %7.7s",\
								x,\
                                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm,\
								"IDF:",\
								 y ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
							if ( sqlca.sqlcode == -1213 ) return 0; \
							if ( sqlca.sqlcode == -1226 ) return 0; \
                               return -1; }


/*** DECLARATION * EXETRN *************************************************************/

 
#define DATABASE "phosix"

exec sql begin declare section;
	struct SCHALTER {
		int natra;
	    int netto;
		int banr;
		int monat;
		int valuta;
		int verbund;
		int dd;
	};

	long lZeitVon = 0;
	long lZeitBis = 235900;
	short sDestBranch = 0;
	short sSrcBranch = 0;
	short isCrema = 0;
	char cCrema[2];
	char str[2048];
	char datenbank[60];
	long lDeldate;
exec sql end declare section;
 
 /***** GLOBALE **************************************************************/
 
FILE *dkkuldat;
char  dateiname[L_TEXT];

 char log_file [300 + 1];
 int debug_enabled  = NO;
 int othervz = NO;
 int explain = NO;
 int Schweiz = NO;
 int Kroatien = NO;
 int Frankreich = NO;
 int Germany = NO;
 int Bulgarien = NO;
 int Serbia = NO;
 int Austria = NO;
 int extended = NO;
 int idelete = NO;
 int timetest = NO;
 int load_all = NO;
 int haus = 0;
 int count = 0;
 char chaus[3];
 char bundesland[16][6+1] = {
	"SH",
	"HH",
	"NS",
	"HB",
	"NRW",
	"HE",
	"RP",
	"BW",
	"BY",
	"SL",
	"B",
	"BB",
	"MV",
	"S",
	"SA",
	"TH"
	};

 exec sql begin declare section;
 long IdfNr;
 long datum;
 long dbzeit;
 char nachttour[7] = {"475901"};
 exec sql end declare section;

 /***** DECLARATION **********************************************************/
 
 int main( int, char ** );
 void PrintMsg( char *fun, char *error_msg, char mld, int rc );
 void WriteLogInfo( char *error_msg, char mld, int rc );
 int StarteLadenderKundeRelationen( char *error_msg, int *schtab );
 int SetzeSchalterTabelle( char *tabelle, int *schtab );
 int EtKdMerkmal1( struct S_DKKUL * );
 int EtKdMerkmal2( struct S_DKKUL * );
 int EtArtKlasse1( struct S_DKKUL * );
 int HolePseudoTour( char *error_msg);

 int PrepareLoadTables(int *schtab, char *error_msg);
 int LoadTables(struct S_DKKUL *kun, int *schtab, char *error_msg);
 int AfterLoadTables(int *schtab, char *error_msg);
 int PrepareCheckQuota( char *error_msg);
 int CheckQuota(char *KUNDE, char *error_msg);

 int PrepareLoadKunde( char *error_msg);
 int PrepareLoadCustomerrouting( char *error_msg);
 int PrepareLoadKundeSchalter( char *error_msg);
 int PrepareLoadKundeKondi( char *error_msg);
 int PrepareLoadKdBetriebsEnde( char *error_msg);
 int PrepareLoadKdKonditionGruppe( char *error_msg);
 int PrepareLoadCstDiscountCont( char *error_msg);
 int PrepareLoadKndausku( char *error_msg);
 int PrepareLoadKundeLagerInfo( char *error_msg);
 int PrepareLoadZeitarten( char *error_msg);
 int PrepareLoadTelnr( char *error_msg);
 int PrepareLoadDistress( char *error_msg);
 int PrepareLoadPayterm( char *error_msg);
 int PrepareLoadPrint( char *error_msg);
 int PrepareLoadDebtlimit( char *error_msg);

 int LadeKunde(struct S_DKKUL *, char *);
 int LadeCustomerrouting(struct S_DKKUL *, char *);
 int LadeKundeSchalter( struct S_DKKUL *, char *);
 int LadeKundeKondi( struct S_DKKUL *, char *);
 int LadeKdBetriebsEnde( struct S_DKKUL *, char *);
 int LadeKonditionGruppe( struct S_DKKUL *, char *);
 int LadeKndausku(struct S_DKKUL *knd, char *error_msg); /* hajo */
 int LadeKdKonditionGruppe( struct S_DKKUL *kun, char *error_msg); /* hajo */
 int LadeCstDiscountCont( struct S_DKKUL *kun, char *error_msg);
 int LadeKundeLagerInfo( struct S_DKKUL *, char *);
 int LadeZeitarten( struct S_DKKUL *, char *);
 int LadeTelnr( struct S_DKKUL *, char *);
 int LadeDistress( struct S_DKKUL *, char *);
 int LadePayterm( struct S_DKKUL *, char *);
 int LadePrint( struct S_DKKUL *, char *);
 int LadeDebtlimit(struct S_DKKUL *, char *);

 int AfterLoadKunde( char *error_msg);
 int AfterLoadCustomerrouting( char *error_msg);
 int AfterLoadKundeSchalter( char *error_msg);
 int AfterLoadKundeKondi( char *error_msg);
 int AfterLoadKdBetriebsEnde( char *error_msg);
 int AfterLoadKdKonditionGruppe( char *error_msg);
 int AfterLoadCstDiscountCont( char *error_msg);
 int AfterLoadKndausku( char *error_msg);
 int AfterLoadKundeLagerInfo( char *error_msg);
 int AfterLoadZeitarten( char *error_msg);
 int AfterLoadTelnr( char *error_msg);
 int AfterLoadDistress( char *error_msg);
 int AfterLoadPayterm( char *error_msg);
 int AfterLoadPrint( char *error_msg);
 int AfterLoadDebtlimit( char *error_msg);

 int SetNotUpdatedkunde( char *error_msg);
 int DelNotUpdatedkunde( char *error_msg);
 int SetNotUpdatedkundeschalter( char *error_msg);
 int DelNotUpdatedkundeschalter( char *error_msg);
 int SetNotUpdatedkundekondi( char *error_msg);
 int DelNotUpdatedkundekondi( char *error_msg);
 int SetNotUpdatedkdbetriebsende( char *error_msg);
 int DelNotUpdatedkdbetriebsende( char *error_msg);
 int SetNotUpdatedkdkonditiongruppe( char *error_msg);
 int DelNotUpdatedkdkonditiongruppe( char *error_msg);
 int SetNotUpdatedCstDiscountCont( char *error_msg);
 int DelNotUpdatedCstDiscountCont( char *error_msg);
 int SetNotUpdatedkndausku( char *error_msg);
 int DelNotUpdatedkndausku( char *error_msg);
 int SetNotUpdatedKundeLagerInfo( char *error_msg);
 int DelNotUpdatedKundeLagerInfo( char *error_msg);
 int SetNotUpdatedzeitarten( char *error_msg);
 int DelNotUpdatedzeitarten( char *error_msg);
 int SetNotUpdatedDistress( char *error_msg);
 int DelNotUpdatedDistress( char *error_msg);
 int SetNotUpdatedPayterm( char *error_msg);
 int DelNotUpdatedPayterm( char *error_msg);
 int SetNotUpdatedPrint( char *error_msg);
 int DelNotUpdatedPrint( char *error_msg);

 int PrepareSetNotUpdatedkunde( char *error_msg);
 int PrepareDelNotUpdatedkunde( char *error_msg);
 int PrepareSetNotUpdatedkundeschalter( char *error_msg);
 int PrepareDelNotUpdatedkundeschalter( char *error_msg);
 int PrepareSetNotUpdatedkundekondi( char *error_msg);
 int PrepareDelNotUpdatedkundekondi( char *error_msg);
 int PrepareSetNotUpdatedkdbetriebsende( char *error_msg);
 int PrepareDelNotUpdatedkdbetriebsende( char *error_msg);
 int PrepareSetNotUpdatedkdkonditiongruppe( char *error_msg);
 int PrepareDelNotUpdatedkdkonditiongruppe( char *error_msg);
 int PrepareSetNotUpdatedCstDiscountCont( char *error_msg);
 int PrepareDelNotUpdatedCstDiscountCont( char *error_msg);
 int PrepareSetNotUpdatedkndausku( char *error_msg);
 int PrepareDelNotUpdatedkndausku( char *error_msg);
 int PrepareSetNotUpdatedKundeLagerInfo( char *error_msg);
 int PrepareDelNotUpdatedKundeLagerInfo( char *error_msg);
 int PrepareSetNotUpdatedzeitarten( char *error_msg);
 int PrepareDelNotUpdatedzeitarten( char *error_msg);
 int PrepareSetNotUpdatedDistress( char *error_msg);
 int PrepareDelNotUpdatedDistress( char *error_msg);
 int PrepareSetNotUpdatedPayterm( char *error_msg);
 int PrepareDelNotUpdatedPayterm( char *error_msg);
 int PrepareSetNotUpdatedPrint( char *error_msg);
 int PrepareDelNotUpdatedPrint( char *error_msg);

 int PrepareDelOldEntriesEmergency( char *error_msg);
 int PrepareDelOldEntriesVacation( char *error_msg);
 int DelOldEntriesEmergency( char *error_msg);
 int DelOldEntriesVacation( char *error_msg);


/***** MAIN *****************************************************************/

 int main( int argc, char **argv  )
 {
   char 	error_msg[81];
   char 	*tabelle;
   char 	*schalter;
   int 		schtab[ANZ_TABELLEN];
   int 		i;
   int 		skip;
   char 	*fun = "Main";
   char *LOG_FILE = "wws.log";
   char *LOG_PATH;
   char logpath[256+1];

   datum = 0;
   for ( i = 0; i < ANZ_TABELLEN; i++ )
       schtab[i] = NO;
  
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
       else if ( !strcmp( schalter, "-ex" ) )
	      explain = YES;
       else if ( !strcmp( schalter, "-allvz" ) )
	      othervz = YES;
       else if ( !strcmp( schalter, "-ch" ) )
	      Schweiz = YES;
       else if ( !strcmp( schalter, "-de" ) )
	      Germany = YES;
       else if ( !strcmp( schalter, "-g" ) )
	      Schweiz = NO;
       else if ( !strcmp( schalter, "-bg" ) )
	   {
	      Bulgarien = YES;
		  setExtendedCharSet(1);
	   }
       else if ( !strcmp( schalter, "-au" ) )
	      Schweiz = NO;
       else if ( !strcmp( schalter, "-hr" ) )
	      Kroatien = YES;
       else if ( !strcmp( schalter, "-fr" ) )
	      Frankreich = YES;
       else if ( !strcmp( schalter, "-rs" ) )
	      Serbia = YES;
       else if ( !strcmp( schalter, "-t" ) )
	      timetest = YES;
       else if ( !strcmp( schalter, "-la" ) )
	      load_all = YES;
       else if ( !strcmp( schalter, "-del" ) )
	      idelete = YES;
       else if ( !strcmp( schalter, "-lf" ) )
	   {
		  haus = atoi(argv[i + 1]);
  	  	  skip = YES;
	
	   }
       else if ( !strcmp( schalter, "-dest" ) )
	   {
		  sDestBranch = atoi(argv[i + 1]);
  	  	  skip = YES;
	
	   }
       else if ( !strcmp( schalter, "-von" ) )
	   {
		  lZeitVon = atol(argv[i + 1]);
  	  	  skip = YES;
	
	   }
       else if ( !strcmp( schalter, "-bis" ) )
	   {
		  lZeitBis = atol(argv[i + 1]);
  	  	  skip = YES;
	
	   }
       else if ( !strcmp( schalter, "-db" ) )
	   {
			i++;
			sprintf( datenbank, "%s", argv[i] );
	   }
	   else if ( !strcmp( schalter, "-ld" ) )
	   {
	      datum = atol(argv[i + 1]);
   	  	  skip = YES;
	   }
   else if ( !strcmp( schalter, "-lt" ) )
	      {
	  	  tabelle = argv[i + 1];
	  	  if ( SetzeSchalterTabelle( tabelle, schtab ) != OK )
	         {
	         skip = ERROR;
	     	 sprintf( error_msg, "%s wurde in Funktion nicht gefunden", tabelle );
	     	 PrintMsg( fun, error_msg, FEHL, skip );
	     	 break;
	      	 }
	  		skip = YES;
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
   
   if ( argc == 1 || skip == ERROR )
      {
      printf( "  usage: %s\n\t"
	      " { -dg <Debugging> }\n\t"
	      " [ -ld 19970314]\n\t"
	      " [ -lt <Tabelle> ... | -la]\n\t", argv[0] );
      exit ( 2 );
      }
	if(haus == 43)
	{
		sSrcBranch = 48;
		sDestBranch = 43;
		lZeitVon = 0;
		lZeitBis = 1;
	}
	else if(sDestBranch != 0)
	{
		sSrcBranch = haus;
	}
   
   DEBUG_SECTION
   setbuf( stderr, 0 );
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
  		
   if ( StarteLadenderKundeRelationen(error_msg, schtab) != 0 ) return 1;
   PrintMsg( fun, "Ende", HINW, 0 );
  
  return OK;
 }

 /***** SETZE-SCHALTER-TABELLE ***********************************************/

 int SetzeSchalterTabelle( char *tabelle, int *schtab )
 {
 /*  char *fun = "SetzeSchalterTabelle";   */

   if ( !strcmp( tabelle, TAB_KUNDE ) )
      schtab[ KZ_KUNDE ] = YES;
   else if ( !strcmp( tabelle, TAB_KUNDESCHALTER ) )
      schtab[ KZ_KUNDESCHALTER ] = YES;
   else if ( !strcmp( tabelle, TAB_KUNDEKONDI ) )
      schtab[ KZ_KUNDEKONDI ] = YES;
   else if ( !strcmp( tabelle, TAB_KDBETRIEBSENDE ) )
      schtab[ KZ_KDBETRIEBSENDE ] = YES;
   else if ( !strcmp( tabelle, TAB_KDKONDITIONGRUPPE ) )
      schtab[ KZ_KDKONDITIONGRUPPE ] = YES;
   else if ( !strcmp( tabelle, TAB_DISCOUNTCOND ) )
      schtab[ KZ_DISCOUNTCOND ] = YES;
   else if ( !strcmp( tabelle, TAB_KNDAUSKU ) )
      schtab[ KZ_KNDAUSKU ] = YES;
   else if ( !strcmp( tabelle, TAB_KUNDELAGERINFO ) )
      schtab[ KZ_KUNDELAGERINFO ] = YES;
   else if ( !strcmp( tabelle, TAB_ZEITARTEN ) )
      schtab[ KZ_ZEITARTEN ] = YES;
   else if ( !strcmp( tabelle, TAB_TELNR ) )
      schtab[ KZ_TELNR ] = YES;
   else
      return ERROR;

   return OK;
 }

/***** WriteLogInfo nur zum Aufruf von PrintMsg ******************************/

void WriteLogInfo( char *error_msg, char mld, int rc )
{
	PrintMsg( "callplanday", error_msg, mld, rc );
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

   
   DEBUG_PRINT( fun, error_msg, SQLCODE, rc )
   
   if ( rc > INSERT )
      return;

   pid = getpid();
   hour1 = time( &hour1 );
   zeit  = localtime( &hour1 );
   fp = fopen( log_file, "a" );
   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.11s %s",
	    mld,
	    haus,
	    zeit->tm_mday,
        zeit->tm_mon + 1,
        (zeit->tm_year+1900)%100,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
	    pid,
	    "tpldzentknd",
	    fun );

   fprintf(fp,"%s\n", error_msg );
   fclose(fp);
}

/***** STARTE DAS LADEN DER Kunde-TABELLEN **************************************/

/* prototyp from linetoolong.c  */
//#ifndef LINE_NOT_TOO_LONG   /* hajo */
//struct AUFB* GetDkkulSatz();
//int GetDkkulSatzanzahl();
//#endif


 int StarteLadenderKundeRelationen( char *error_msg, int *schtab )
{
	int zaehler, rc;
	char *fun = "StarteLadenderKundeRelationen";
	char *XVSAM;
	char datpath[256+1];
	char huelse[20];
	
	exec sql begin declare section;
	struct S_DKKUL  kunlang;
	struct S_DKKUL  *kun;
	short int filialnr;
	exec sql end declare section;

	mcallplanloadS srvLoad;
    tError stError;

/* Error  -33020  on esqlc-compiling tpldzentknd.ec */
//#ifdef LINE_NOT_TOO_LONG   /* hajo */
//  struct AUFB aufb[] = { DKKUL_SATZ };
//#else
//  struct AUFB* aufb  = GetDkkulSatz();
//#endif

	char satz[4000];
    int len = 1300;	/* dkkul = 1300!!!!!! */
	
    kun = &kunlang;
   	
   	exec sql database :datenbank;
   	if (SQLCODE != 0)  /* Datenbankfehler */
    {
      	ERROR_MSG2( "database:" )
 	  	PrintMsg( fun, error_msg, FEHL, ERROR );
      	return ERROR;
    }
   	exec sql set lock mode to wait 20;
   	if (sqlca.sqlcode != 0)  /* Datenbankfehler */
    {
      	ERROR_MSG2( "Lock Mode:" )
 	  	PrintMsg( fun, error_msg, FEHL, ERROR );
		return ERROR;
    }
   	exec sql set isolation to dirty read;
   	if ((SQLCODE != 0) && (SQLCODE != -256))  /* Datenbankfehler */
    {
      	ERROR_MSG2( "Set Isolation:" )
 	  	PrintMsg( fun, error_msg, FEHL, -1 );
      	return ERROR;
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

	filialnr = haus;
	exec sql select screma into :cCrema from paraauftragbearb where filialnr = :filialnr;
	if (sqlca.sqlcode != 0)  /* Datenbankfehler */
	{
		sprintf (error_msg, "select paraauftragbearb: %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
		PrintMsg( fun, error_msg, FEHL, -1 );
	}
	else
	{
		if(cCrema[0] == '1') isCrema = 1;
	}

	if (datum == 0) /* wenn keine Datumseingabe dann errechnen Datum */
	{
		srvLoad.VERTRIEBSZENTRUMNR = haus;
		srvLoad.LADEDATUM = 0;
		srvLoad.LADEKIPPZEIT = 120000;
		if ( Mcallplanload_GetInitializeData( &srvLoad, &stError, FALSE ) == IS_ERROR )
		{
			return CheckSql( fun, &stError, "%s", stError.spError );
		}
		datum = srvLoad.LADEDATUM;
	}
	lDeldate = AllgAddDate(datum, -30, error_msg);

	sprintf(chaus,"%02d",haus);

	if (explain == YES)	exec sql set explain on;

	PrintMsg( "Main", "Start", HINW, 0 );

	if( (rc = PrepareCheckQuota(error_msg)) != 0 )
	{
		return rc;	
	}
	if( (rc = PrepareLoadTables(schtab, error_msg)) != 0 )
	{
		return rc;	
	}
	if ((XVSAM = getenv("XVSAM")) == (char *)0)
	{
		strcpy(datpath, ".");
	}
	else
	{
		strcpy(datpath, XVSAM);
	}

	sprintf( dateiname, "%s/UCATPH4/DKKUL.P.dat", datpath );
	if ( ( dkkuldat = fopen( dateiname, "r" ) ) == (FILE *)0 )  /* hajo */
	{
		PrintMsg( "tpldzentknd ", dateiname, FEHL, 0 );
		PrintMsg( "tpldzentknd ", "DKKUL nicht vorhanden", FEHL, 0 );
		return -1;
	}
    
    exec sql begin work;
    if (SQLCODE < 0 )
    {
    	ERROR_MSG2( "begin Work:" )
 	  	PrintMsg( fun, error_msg, FEHL, ERROR );
       	return ERROR;
    }
	for(zaehler=0 ;;zaehler++ )
	{
		if (zaehler%50 == 0)
		{
			exec sql commit work;
            if (SQLCODE < 0 )
    		{
    			ERROR_MSG2( "Commit Work:" )
 	  			PrintMsg( fun, error_msg, FEHL, -1 );
       			return -1;
    		}
			exec sql begin work;
    		if (SQLCODE < 0 )
    		{
    			ERROR_MSG2( "begin Work:" )
 	  			PrintMsg( fun, error_msg, FEHL, ERROR );
       			return -1;
    		}
		}
		
		if (zaehler%50 == 0)
		{
		   	DEBUG_SECTION
			sprintf(error_msg," %d Saetze geladen",zaehler);
 	  		PrintMsg( fun, error_msg, HINW, -1 );
			END_DEBUG_SECTION
		}
		if (timetest == YES && zaehler == 200)	break;	/* für Test nur 200 Sätze */ 
		
		if(fread( satz ,len, 1 , dkkuldat ) == 0)
			break;
	 	memset( (char *)kun, BLANC, sizeof( struct S_DKKUL ) );

//#ifdef LINE_NOT_TOO_LONG   /* hajo */
    WandelAsci( (char *)kun, satz, aufb_DKKUL, satzanzahl_DKKUL );
//    WandelAsci( (char *)kun, satz, aufb, SATZANZAHL( aufb ) );
//#else
//    WandelAsci( (char *)kun, satz, aufb, GetDkkulSatzanzahl() );
//#endif

		sprintf(huelse,"%*.*s",L_DKKUL_KULIDF,L_DKKUL_KULIDF,kun->KULIDF);
/*		PrintMsg( "tpldzentknd ", huelse, FEHL, 0 );	*/
		IdfNr = atol(huelse);
/*		if(kun->KULLOE[0] != 'J' && kun->KULAESPER[0] != 'J')	*/
/*		if(kun->KULLOE[0] != 'J')	*/ /*	auch gesperrte Kunden uebernehmen	*/
		{
			if(!strncmp(kun->KULFIL1,chaus,L_DKKUL_KULFIL1))
			{
				if( (rc = LoadTables(kun, schtab, error_msg)) != 0 )
				{
					return rc;	
				}	
			}
			else if(!strncmp(kun->KULFIL1,"48",L_DKKUL_KULFIL1) 
				&& !strncmp(chaus,"49",L_DKKUL_KULFIL1))
			{
				strncpy(kun->KULFIL1,chaus,L_DKKUL_KULFIL1);
				if( (rc = LoadTables(kun, schtab, error_msg)) != 0 )
				{
					return rc;	
				}	
			}
		}
	
	}

	EXEC SQL commit work;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, "commit work2 %ld", sqlca.sqlcode);
		PrintMsg( fun, error_msg, FEHL, -1 );
		return -1;
	}
	
	fclose( dkkuldat);
    sprintf(error_msg," %d Saetze geladen",zaehler);
	PrintMsg( " ", error_msg, HINW, -1 );

	if ( (rc = DelOldEntriesEmergency( error_msg)) < 0) return rc;
	if ( (rc = DelOldEntriesVacation( error_msg)) < 0) return rc;
	
	if (timetest == YES) return OK;

	if( (rc = AfterLoadTables(schtab, error_msg)) != 0 )
	{
		return rc;	
	}
	return OK;
}

int PrepareLoadTables(int *schtab, char *error_msg)
{
	int rc;
	if( load_all || schtab[ KZ_KUNDE ] == YES ) 
	{
		if ( (rc = PrepareLoadKunde( error_msg)) < 0) return rc;
		if ( sDestBranch > 0 )
		{
			if ( (rc = PrepareLoadCustomerrouting( error_msg)) < 0) return rc;
		}
	}
	if( load_all || schtab[ KZ_KUNDESCHALTER ] == YES ) 
	{
		if ( (rc = PrepareLoadKundeSchalter( error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_KUNDEKONDI ] == YES ) 
	{
		if ( (rc = PrepareLoadKundeKondi( error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_KDBETRIEBSENDE ] == YES ) 
	{
		if ( (rc = PrepareLoadKdBetriebsEnde( error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_KDKONDITIONGRUPPE] == YES ) 
	{
		if ( (rc = PrepareLoadKdKonditionGruppe( error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_DISCOUNTCOND] == YES ) 
	{
		if(Frankreich)
		{
			if ( (rc = PrepareLoadCstDiscountCont( error_msg)) < 0) return rc;
		}
	}
	if( load_all || schtab[ KZ_KNDAUSKU] == YES ) 
	{
		if ( (rc = PrepareLoadKndausku( error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_KUNDELAGERINFO] == YES ) 
	{
		if ( (rc = PrepareLoadKundeLagerInfo( error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_ZEITARTEN] == YES ) 
	{
		if ( (rc = PrepareLoadZeitarten( error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_TELNR] == YES ) 
	{
		if ( (rc = PrepareLoadTelnr( error_msg)) < 0) return rc;
	}
	if ( (rc = PrepareDelOldEntriesEmergency( error_msg)) < 0) return rc;
	if ( (rc = PrepareDelOldEntriesVacation( error_msg)) < 0) return rc;
	return 0;
}

int LoadTables(struct S_DKKUL *kun, int *schtab, char *error_msg)
{
	int rc;
	if( load_all || schtab[ KZ_KUNDE ] == YES ) 
	{
		if ( (rc = LadeKunde(kun, error_msg)) < 0) return rc;
		if ( sDestBranch > 0 )
		{
			if(sSrcBranch == 48)
			{
				if ( (rc = LadeCustomerrouting(kun, error_msg)) < 0) return rc;
			}
		}
	}
	if( load_all || schtab[ KZ_KUNDESCHALTER ] == YES ) 
	{
		if ( (rc = LadeKundeSchalter(kun, error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_KUNDEKONDI ] == YES ) 
	{
		if ( (rc = LadeKundeKondi(kun, error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_KDBETRIEBSENDE ] == YES ) 
	{
		if ( (rc = LadeKdBetriebsEnde(kun, error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_KDKONDITIONGRUPPE] == YES ) 
	{
		if ( (rc = LadeKdKonditionGruppe(kun, error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_DISCOUNTCOND] == YES ) 
	{
		if(Frankreich)
		{
			if ( (rc = LadeCstDiscountCont(kun, error_msg)) < 0) return rc;
		}
	}
	if( load_all || schtab[ KZ_KNDAUSKU] == YES ) 
	{
		if ( (rc = LadeKndausku(kun, error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_KUNDELAGERINFO] == YES ) 
	{
		if ( (rc = LadeKundeLagerInfo(kun, error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_ZEITARTEN] == YES ) 
	{
		if ( (rc = LadeZeitarten(kun, error_msg)) < 0) return rc;
	}
	if( load_all || schtab[ KZ_TELNR] == YES ) 
	{
		if ( (rc = LadeTelnr(kun, error_msg)) < 0) return rc;
	}
	return 0;
}

int AfterLoadTables(int *schtab, char *error_msg)
{
	int rc;
	int rcode = 0;
	if( load_all || schtab[ KZ_KUNDE ] == YES ) 
	{
		if ( (rc = AfterLoadKunde( error_msg)) < 0) rcode = rc;
		if ( sDestBranch > 0 )
		{
			if ( (rc = AfterLoadCustomerrouting( error_msg)) < 0) return rc;
		}
	}
	if( load_all || schtab[ KZ_KUNDESCHALTER ] == YES ) 
	{
		if ( (rc = AfterLoadKundeSchalter( error_msg)) < 0) rcode = rc;
	}
	if( load_all || schtab[ KZ_KUNDEKONDI ] == YES ) 
	{
		if ( (rc = AfterLoadKundeKondi( error_msg)) < 0) rcode = rc;
	}
	if( load_all || schtab[ KZ_KDBETRIEBSENDE ] == YES ) 
	{
		if ( (rc = AfterLoadKdBetriebsEnde( error_msg)) < 0) rcode = rc;
	}
	if( load_all || schtab[ KZ_KDKONDITIONGRUPPE] == YES ) 
	{
		if ( (rc = AfterLoadKdKonditionGruppe( error_msg)) < 0) rcode = rc;
	}
	if( load_all || schtab[ KZ_DISCOUNTCOND] == YES ) 
	{
		if(Frankreich)
		{
			if ( (rc = AfterLoadCstDiscountCont( error_msg)) < 0) rcode = rc;
		}
	}
	if( load_all || schtab[ KZ_KNDAUSKU] == YES ) 
	{
		if ( (rc = AfterLoadKndausku( error_msg)) < 0) rcode = rc;
	}
	if( load_all || schtab[ KZ_KUNDELAGERINFO] == YES ) 
	{
		if ( (rc = AfterLoadKundeLagerInfo( error_msg)) < 0) rcode = rc;
	}
	if( load_all || schtab[ KZ_ZEITARTEN] == YES ) 
	{
		if ( (rc = AfterLoadZeitarten( error_msg)) < 0) rcode = rc;
	}
	if( load_all || schtab[ KZ_TELNR] == YES ) 
	{
		if ( (rc = AfterLoadTelnr( error_msg)) < 0) rcode = rc;
	}
	return rcode;
}

int PrepareLoadKunde( char *error_msg)
{
	char *fun = "PrepareLoadKunde";
	int rc;

	if((rc = PrepareLoadDistress( error_msg )) != 0) return rc;
	if(Bulgarien == YES)
	{
		if((rc = PrepareLoadPayterm( error_msg )) != 0) return rc;
		if((rc = PrepareLoadPrint( error_msg )) != 0) return rc;
	}
	else
	{
		if(!isCrema)
		{
			if((rc = PrepareLoadDebtlimit( error_msg )) != 0) return rc;
		}
	}

	if((rc = PrepareSetNotUpdatedkunde( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedkunde( error_msg )) != 0) return rc;

	strcpy(str,"update kunde set ");
	strcat(str,KUNDE_UPDLISTE);          
	strcat(str,",nachliefertyp = ?");
	strcat(str,",kzsprache = ?");
	strcat(str,",phonepriority = ?");
	strcat(str,",kzpsychostoffe = ?");
	strcat(str,",softwarehouse = ?");
	strcat(str,",prewholetyp = ?");
	strcat(str,",anzaufclose = ?");
	strcat(str,",payment_term = ?");
	strcat(str,",krankenkassennr = ?");
	strcat(str,",calculationtype = ?");
	strcat(str,",apolizens = ?");
	strcat(str,",btmlizens = ?");
	strcat(str,",surcharge_basic = ?");
	strcat(str,",deduction_basic = ?");
	strcat(str,",surchargepct = ?");
	strcat(str,",deductionpct = ?");
	strcat(str,",vatregistered = ?");
	strcat(str,",rebatemethfreesale = ?");
	strcat(str,",rebatemethhealthf = ?");
	strcat(str,",maincstno = ?");
	strcat(str,",mastercstno = ?");
	strcat(str,",surcharge_basic_kk = ?");
	strcat(str,",deduction_basic_kk = ?");
	strcat(str,",surchargepctkk = ?");
	strcat(str,",deductionpctkk = ?");
	strcat(str,",manufacturerno = ?");
	strcat(str,",msv3cfgchangedate = ?");
	strcat(str,",partnernr = ?");
	strcat(str,",minlogaddbehavior = ?");
	strcat(str,",SendCollectivinvoice = ?");
	strcat(str," where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"KUNDENNR = ?");          

	EXEC SQL PREPARE upd_kunde FROM :str;
	ERROR_MSG2( "prepare upd_kunde" )

	strcpy(str, "update kunde set ");
	strcat(str, KUNDE_UPDLISTE);
	strcat(str, ",nachliefertyp = ?");
	strcat(str, ",kzsprache = ?");
	strcat(str, ",phonepriority = ?");
	strcat(str, ",kzpsychostoffe = ?");
	strcat(str, ",softwarehouse = ?");
	strcat(str, ",prewholetyp = ?");
	strcat(str, ",anzaufclose = ?");
	strcat(str, ",payment_term = ?");
	strcat(str, ",krankenkassennr = ?");
	strcat(str, ",calculationtype = ?");
	strcat(str, ",apolizens = ?");
	strcat(str, ",btmlizens = ?");
	strcat(str, ",surcharge_basic = ?");
	strcat(str, ",deduction_basic = ?");
	strcat(str, ",vatregistered = ?");
	strcat(str, ",rebatemethfreesale = ?");
	strcat(str, ",rebatemethhealthf = ?");
	strcat(str, ",maincstno = ?");
	strcat(str, ",mastercstno = ?");
	strcat(str, ",surcharge_basic_kk = ?");
	strcat(str, ",deduction_basic_kk = ?");
	strcat(str, ",surchargepctkk = ?");
	strcat(str, ",deductionpctkk = ?");
	strcat(str, ",manufacturerno = ?");
	strcat(str, ",msv3cfgchangedate = ?");
	strcat(str, ",partnernr = ?");
	strcat(str, ",minlogaddbehavior = ?");
	strcat(str, ",SendCollectivinvoice = ?");
	strcat(str, ",linefee = ?");
	strcat(str, ",packagefee = ?");
	strcat(str, " where ");
	strcat(str, "VERTRIEBSZENTRUMNR = ?");
	strcat(str, " and ");
	strcat(str, "KUNDENNR = ?");

	EXEC SQL PREPARE upd_kunde_ch FROM : str;
	ERROR_MSG2("prepare upd_kunde_ch")

	if((rc = SetNotUpdatedkunde( error_msg )) != 0) return rc;

	return OK;
}

int PrepareLoadDebtlimit( char *error_msg)
{
	char *fun = "PrepareLoadDebtlimit";
	int rc;

	strcpy(str,"select limit from debtlimit ");
	strcat(str,"where PARTNERNO = ? ");

	EXEC SQL PREPARE sel_limit FROM :str;
	ERROR_MSG2( "prepare sel_limit" )
	exec sql declare SelLimit Cursor with hold for sel_limit;

	strcpy(str,"select NAMEAPO,MASTERCSTNO from kunde ");
	strcat(str,"where vertriebszentrumnr = ? ");
	strcat(str,"and kundennr = ? ");

	EXEC SQL PREPARE sel_kundelimit FROM :str;
	ERROR_MSG2( "prepare sel_kundelimit" )
	exec sql declare SelKunde Cursor with hold for sel_kundelimit;
	 
	strcpy(str,"insert into debtlimit (");
	strcat(str,DEBTLIMIT_PELISTE);          
	strcat(str,") values ");          
	strcat(str,"( ?, ?, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 )");          

	EXEC SQL PREPARE ins_limit FROM :str;
	ERROR_MSG2( "prepare ins_limit" )

	return OK;
}

int PrepareLoadDistress( char *error_msg)
{
	char *fun = "PrepareLoadDistress";
	int rc;

	if((rc = PrepareSetNotUpdatedDistress( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedDistress( error_msg )) != 0) return rc;

	strcpy(str,"update distressrouting set ");
	strcat(str,"upd_flag = '1'");
	strcat(str," where ");
	strcat(str,"BRANCHNO = ?");          
	strcat(str," and ");          
	strcat(str,"CUSTOMERNO = ?");          

	EXEC SQL PREPARE upd_distress FROM :str;
	ERROR_MSG2( "prepare upd_distress" )

	strcpy(str,"insert into distressrouting (");
	strcat(str,"BRANCHNO,");          
	strcat(str,"CUSTOMERNO,");          
	strcat(str,"DESTBRANCHNO,");          
	strcat(str,"UPD_FLAG");          
	strcat(str," ) values ( ");
	strcat(str," ?, ?, '0', '1' )");          

	EXEC SQL PREPARE ins_distress FROM :str;
	ERROR_MSG2( "prepare ins_distress" )

	if((rc = SetNotUpdatedDistress( error_msg )) != 0) return rc;

	return OK;
}

int PrepareLoadPayterm( char *error_msg)
{
	char *fun = "PrepareLoadPayterm";
	int rc;

	if((rc = PrepareSetNotUpdatedPayterm( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedPayterm( error_msg )) != 0) return rc;

	strcpy(str,"select ");
	strcat(str,PAYTERM_PELISTE);
	strcat(str," from paymentterms ");
	strcat(str," where ");
	strcat(str,"PAYMENT_TERM = ?");          

	EXEC SQL PREPARE sel_payterm FROM :str;
	ERROR_MSG2( "prepare sel_payterm" )

	strcpy(str,"update cstpaymentterms set ");
	strcat(str,"upd_flag = '1'");
	strcat(str," where ");
	strcat(str,"BRANCHNO = ?");          
	strcat(str," and ");
	strcat(str,"CUSTOMERNO = ?");
	strcat(str," and ");
	strcat(str,"PREIS_TYP = ?");
	strcat(str," and ");
	strcat(str,"PAYMENTARGET = ?");

	EXEC SQL PREPARE upd_payterm FROM :str;
	ERROR_MSG2( "prepare upd_payterm" )

	strcpy(str,"insert into cstpaymentterms (");
	strcat(str,"BRANCHNO,");          
	strcat(str,"CUSTOMERNO,");          
	strcat(str,"PREIS_TYP,");          
	strcat(str,"PAYMENTARGET,");          
	strcat(str,"UPD_FLAG");          
	strcat(str," ) values ( ");
	strcat(str," ?, ?, ?, ?, '1' )");          

	EXEC SQL PREPARE ins_payterm FROM :str;
	ERROR_MSG2( "prepare ins_payterm" )

	if((rc = SetNotUpdatedPayterm( error_msg )) != 0) return rc;

	return OK;
}

int PrepareLoadPrint( char *error_msg)
{
	char *fun = "PrepareLoadPrint";
	int rc;

	if((rc = PrepareSetNotUpdatedPrint( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedPrint( error_msg )) != 0) return rc;

	strcpy(str,"update cstprint set ");
	strcat(str,CSTPRINT_UPDLISTE);
	strcat(str," where ");
	strcat(str,"BRANCHNO = ?");          
	strcat(str," and ");
	strcat(str,"CUSTOMERNO = ?");          
	strcat(str," and ");
	strcat(str,"PREIS_TYP = ?");          

	EXEC SQL PREPARE upd_print FROM :str;
	ERROR_MSG2( "prepare upd_print" )

	strcpy(str,"insert into cstprint ( ");
	strcat(str,CSTPRINT_PELISTE);
	strcat(str," ) values ( ");
	strcat(str," ?, ?, ?, ?, ?, ? )");          

	EXEC SQL PREPARE ins_print FROM :str;
	ERROR_MSG2( "prepare ins_print" )

	if((rc = SetNotUpdatedPrint( error_msg )) != 0) return rc;

	return OK;
}

int PrepareLoadCustomerrouting( char *error_msg)
{
	char *fun = "PrepareLoadCustomerrouting";
	int rc;

	strcpy(str,"update customerrouting set ");
	strcat(str,CUSTOMERROUTING_UPDLISTE);          
	strcat(str," where ");
	strcat(str,"BRANCHNO = ?");          
	strcat(str," and ");          
	strcat(str,"CUSTOMERNO = ?");          
	strcat(str," and ");          
	strcat(str,"WEEKDAY = ?");          
	strcat(str," and ");          
	strcat(str,"TIMEFROM = ?");          

	EXEC SQL PREPARE upd_customerrouting FROM :str;
	ERROR_MSG2( "prepare upd_customerrouting" )

	strcpy(str,"insert into customerrouting ");
	strcat(str,"( ");
	strcat(str,CUSTOMERROUTING_PELISTE);          
	strcat(str," ) values ( ");
	strcat(str," ?, ?, ?, ?, ?, ?, ?) ");

	EXEC SQL PREPARE ins_customerrouting FROM :str;
	ERROR_MSG2( "prepare ins_customerrouting" )

	return OK;
}

int PrepareLoadKundeSchalter( char *error_msg)
{
	char *fun = "PrepareLoadKundeSchalter";
	int rc;

	if((rc = PrepareSetNotUpdatedkundeschalter( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedkundeschalter( error_msg )) != 0) return rc;

	strcpy(str,"update kundeschalter set ");
	strcat(str,KUNDESCHALTER_UPDLISTE);          
	strcat(str,",skdtrenndefekt = ?");
	strcat(str,",skdparternariat = ?");
	strcat(str,",skdbaauftrag = ?");
	strcat(str,",skdwatchorder = ?");
	strcat(str,",skdhalfmargin = ?");
	strcat(str,",skddiscountexcept = ?");
	strcat(str,",skdliste5 = ?");
	strcat(str,",skdinvoicedisc = ?");
	strcat(str,",skdinvoiceemail = ?");
	strcat(str,",skdnoexpiryinfo = ?");
	strcat(str,",medprod_abg_verord = ?");
	strcat(str,",skdnoclosedefvb = ? ");
	strcat(str,",skdnosub = ?");
	strcat(str,",skdnoshortreport = ?");
	strcat(str,",skdgiveprodquota = ?");
	strcat(str,",skdavoiddefectclearing = ?");
	strcat(str,",noorderconsaftermot = ?");
	strcat(str,",skdmailinvoice = ?");
	strcat(str,",skdmailbatchchangeadvice = ?");
	strcat(str,",skdfaxinvoice = ?");
	strcat(str,",skdfaxbatchchangeadvice = ?");
	strcat(str,",skdfmd = ?");
	strcat(str," where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"KUNDENNR = ?");          

	EXEC SQL PREPARE upd_kundeschalter FROM :str;
	ERROR_MSG2( "prepare upd_kundeschalter" )

	strcpy(str,"update kundeschalter set ");
	strcat(str,KUNDESCHALTER_UPDLISTE);
	strcat(str,",skdmehrfachbestell = ?");
	strcat(str,",skdomgkunde = ?");
	strcat(str,",skdkeinnl = ?");
	strcat(str,",skdtrenndefekt = ?");
	strcat(str,",skdparternariat = ?");
	strcat(str,",skdbaauftrag = ?");
	strcat(str,",skdwatchorder = ?");
	strcat(str,",skdhalfmargin = ?");
	strcat(str,",skddiscountexcept = ?");
	strcat(str,",skdliste5 = ?");
	strcat(str,",skdinvoicedisc = ?");
	strcat(str,",skdinvoiceemail = ?");
	strcat(str,",skdnoexpiryinfo = ?");
	strcat(str,",medprod_abg_verord = ?");
	strcat(str,",skdnoclosedefvb = ? ");
	strcat(str,",skdnosub = ?");
	strcat(str,",skdnoshortreport = ?");
	strcat(str,",skdgiveprodquota = ?");
	strcat(str,",skdavoiddefectclearing = ?");
	strcat(str,",noorderconsaftermot = ?");
	strcat(str,",skdmailinvoice = ?");
	strcat(str,",skdmailbatchchangeadvice = ?");
	strcat(str,",skdfaxinvoice = ?");
	strcat(str,",skdfaxbatchchangeadvice = ?");
	strcat(str,",skdfmd = ?");
	strcat(str," where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");
	strcat(str," and ");
	strcat(str,"KUNDENNR = ?");

	EXEC SQL PREPARE upd_kundeschalterch FROM :str;
	ERROR_MSG2( "prepare upd_kundeschalterch" )

	if((rc = SetNotUpdatedkundeschalter( error_msg )) != 0) return rc;

	return OK;
}

int PrepareLoadKundeKondi( char *error_msg)
{
	char *fun = "PrepareLoadKundeKondi";
	int rc;

	if((rc = PrepareSetNotUpdatedkundekondi( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedkundekondi( error_msg )) != 0) return rc;

	strcpy(str,"update kundekondi set ");
	strcat(str,KUNDEKONDI_UPDLISTE);          
	strcat(str,",TAGAUTOVALUTA=? ");          
	strcat(str,",VALUTATAGEMAX=? ");          
	strcat(str,",PAYMENTINTERVAL=? ");          
	strcat(str," where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"KUNDENNR = ?");          

	EXEC SQL PREPARE upd_kundekondi FROM :str;
	ERROR_MSG2( "prepare upd_kundekondi" )

	if((rc = SetNotUpdatedkundekondi( error_msg )) != 0) return rc;

	return OK;
}

int PrepareLoadKdBetriebsEnde( char *error_msg)
{
	char *fun = "PrepareLoadKdBetriebsEnde";
	int rc;

	if((rc = PrepareSetNotUpdatedkdbetriebsende( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedkdbetriebsende( error_msg )) != 0) return rc;

	strcpy(str,"update kdbetriebsende set ");
	strcat(str,KDBETRIEBSENDE_UPDLISTE);
	strcat(str," where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"KUNDENNR = ?");          
	strcat(str," and ");          
	strcat(str,"WEEKDAY = ?");          

	EXEC SQL PREPARE upd_kdbetriebsende FROM :str;
	ERROR_MSG2( "prepare upd_kdbetriebsende" )

	if((rc = SetNotUpdatedkdbetriebsende( error_msg )) != 0) return rc;

	return OK;
}

int PrepareLoadKdKonditionGruppe( char *error_msg)
{
	char *fun = "PrepareLoadKdKonditionGruppe";
	int rc;

	if((rc = PrepareSetNotUpdatedkdkonditiongruppe( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedkdkonditiongruppe( error_msg )) != 0) return rc;

	strcpy(str,"update kdkonditiongruppe set ");
	strcat(str,KDKONDITIONGRUPPE_UPDLISTE);          
	strcat(str," where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"KUNDENNR = ?");          
	strcat(str," and ");          
	strcat(str,"KONDGRUPPENNR = ?");          

	EXEC SQL PREPARE upd_kdkondgruppe FROM :str;
	ERROR_MSG2( "prepare upd_kdkondgruppe" )

	if((rc = SetNotUpdatedkdkonditiongruppe( error_msg )) != 0) return rc;

	return OK;
}

int PrepareLoadCstDiscountCont(char *error_msg)
{
	char *fun = "PrepareLoadCstDiscountCont";
	int rc;

	if((rc = PrepareSetNotUpdatedCstDiscountCont( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedCstDiscountCont( error_msg )) != 0) return rc;

	strcpy(str,"update cstdiscountcont set ");
	strcat(str,"UPD_FLAG='1'");
	strcat(str," where ");
	strcat(str,"BRANCHNO = ?");          
	strcat(str," and ");          
	strcat(str,"CUSTOMERNO = ?");          
	strcat(str," and ");          
	strcat(str,"ORDER_TYPE = 'PM'");          
	strcat(str," and ");          
	strcat(str,"SUB_ORDER_TYPE = '010'");          

	EXEC SQL PREPARE upd_cstdiscountcont FROM :str;
	ERROR_MSG2( "prepare upd_cstdiscountcont" )

	strcpy(str,"insert into cstdiscountcont (");
	strcat(str,"BRANCHNO,");
	strcat(str,"CUSTOMERNO,");
	strcat(str,"ORDER_TYPE,");
	strcat(str,"SUB_ORDER_TYPE,");
	strcat(str,"UPD_FLAG");
	strcat(str," ) values ");
	strcat(str,"( ?,?,\"PM\",\"010\",\"1\" )");

	EXEC SQL PREPARE ins_cstdiscountcont FROM :str;
    if (sqlca.sqlcode < 0 )
    {
       	sprintf(error_msg, "prepare ins_cstdiscountcont %ld / %s", sqlca.sqlcode,sqlca.sqlerrm);
  		PrintMsg( fun, error_msg, FEHL, -1 );
       	return -1;
    }
	 
	if((rc = SetNotUpdatedCstDiscountCont( error_msg )) != 0) return rc;

	return OK;	 
}

int PrepareLoadKndausku(char *error_msg)
{
	char *fun = "PrepareLoadKndausku";
	int rc;

	if((rc = PrepareSetNotUpdatedkndausku( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedkndausku( error_msg )) != 0) return rc;

	strcpy(str,"update kndausku set ");
	strcat(str,KNDAUSKU_UPDLISTE);          
	strcat(str," where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ?");          
	strcat(str," and ");          
	strcat(str,"KUNDENNR = ?");          

	EXEC SQL PREPARE upd_kndausku FROM :str;
	ERROR_MSG2( "prepare upd_kndausku" )

	strcpy(str,"insert into kndausku (");
	strcat(str,"IDFNR,");          
	strcat(str,"EILBOTENZUSCHLAG,");          
	strcat(str,"MONATSUMSATZ,");          
	strcat(str,"MALUSFREI_PROZ,");          
	strcat(str,"VERTRETER_2,");          
	strcat(str,"VERSAND_KOSTEN,");          
	strcat(str,"KUNDE_SEIT,");          
	strcat(str,"URLAUB_VON,");          
	strcat(str,"URLAUB_BIS,");          
	strcat(str,"KZUPD,");          
	strcat(str,"KUNDENNR,");          
	strcat(str,"VERTRIEBSZENTRUMNR,");          
	strcat(str,"DISPOGEBUEHR,");          
	strcat(str,"BTMGEBUEHR,");          
	strcat(str,"DOKUGEBUEHR,");          
	strcat(str,"LOGISTIKAUFSCHLAG,");
	strcat(str,"LOGISTIKAUFSCHLAGMIN");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,?,?,0,0,0,\"1\",?,?,?,?,?,?,? )");

	EXEC SQL PREPARE ins_ausku FROM :str;
    if (sqlca.sqlcode < 0 )
    {
       	sprintf(error_msg, "prepare ins_ausku %ld", sqlca.sqlcode);
  		PrintMsg( fun, error_msg, FEHL, -1 );
       	return -1;
    }
	 
	if((rc = SetNotUpdatedkndausku( error_msg )) != 0) return rc;

	return OK;	 
}

int PrepareLoadKundeLagerInfo(char *error_msg)
{
	char *fun = "PrepareLoadKundeLagerInfo";
	int rc;

	if((rc = PrepareSetNotUpdatedKundeLagerInfo( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedKundeLagerInfo( error_msg )) != 0) return rc;

	strcpy(str,"update kundelagerinfo set ");
	strcat(str,KUNDELAGERINFO_UPDLISTE);          
	strcat(str," where ");
	strcat(str,"FILIALNR = ? ");          
	strcat(str," and ");
	strcat(str,"VERTRIEBSZENTRUMNR = ? ");          
	strcat(str," and ");
	strcat(str,"KUNDENNR = ?");          

	EXEC SQL PREPARE upd_klagerinf FROM :str;
	ERROR_MSG2( "prepare upd_klagerinf" )

	strcpy(str,"insert into kundelagerinfo (");
	strcat(str,"FILIALNR,");          
	strcat(str,"VERTRIEBSZENTRUMNR,");          
	strcat(str,"KUNDENNR,");          
	strcat(str,"ENTFERNUNGINKM,");          
	strcat(str,"KZUPD");          
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,\"1\" )");

	EXEC SQL PREPARE ins_klagerinf FROM :str;
    if (sqlca.sqlcode < 0 )
    {
       	sprintf(error_msg, "prepare ins_klagerinf %ld", sqlca.sqlcode);
  		PrintMsg( fun, error_msg, FEHL, -1 );
       	return -1;
    }

	if((rc = SetNotUpdatedKundeLagerInfo( error_msg )) != 0) return rc;

	return OK;	 
}

int PrepareLoadZeitarten(char *error_msg)
{
	char *fun = "PrepareLoadZeitarten";
	int rc;

	if((rc = PrepareSetNotUpdatedzeitarten( error_msg )) != 0) return rc;
	if((rc = PrepareDelNotUpdatedzeitarten( error_msg )) != 0) return rc;

	/*	strcpy(str,"select kzupd from zeitarten ");
 	strcat(str,"where ZEITART = ? ");
 	strcat(str,"and ZEITSCHLUESSEL = ? ");
 	strcat(str,"and TAGESTYP = ? ");
 	strcat(str,"and ZEITBEGIN = ? ");
 	strcat(str,"for update");

	EXEC SQL PREPARE sel_zeit FROM :str;
	ERROR_MSG2( "prepare sel_zeit" )
	exec sql declare Cselzeit cursor for sel_zeit;

	strcpy(str,"update zeitarten set ");
 	strcat(str,"KZUPD = \"1\" ");
 	strcat(str,",ZEITENDE = ? ");
 	strcat(str,"where current of Cselzeit");
*/
	strcpy(str,"update zeitarten set ");
 	strcat(str,"KZUPD = \"1\" ");
 	strcat(str,"where ZEITART = ? ");
 	strcat(str,"and ZEITSCHLUESSEL = ? ");
 	strcat(str,"and WEEKDAY = ? ");
 	strcat(str,"and ZEITBEGIN = ? ");
 	strcat(str,"and ZEITENDE = ? ");
 	strcat(str,"and VERTRIEBSZENTRUMNR = ");
	strcat(str, chaus );

	EXEC SQL PREPARE upd_zeitarten FROM :str;
	ERROR_MSG2( "prepare upd_zeitarten" )

	strcpy(str,"insert into zeitarten (");
 	strcat(str,"LFDNR,");
 	strcat(str,"ZEITART,");
 	strcat(str,"ZEITSCHLUESSEL,");
 	strcat(str,"TAGESTYP,");
 	strcat(str,"ZEITBEGIN,");
 	strcat(str,"ZEITENDE,");
 	strcat(str,"KZUPD,");
  	strcat(str,"VERTRIEBSZENTRUMNR,");
  	strcat(str,"WEEKDAY ");
	strcat(str," ) values ");
	strcat(str,"( 0,?,?,?,?,?,\"1\", ");
	strcat(str, chaus );
	strcat(str, ",?)" );

	EXEC SQL PREPARE ins_zeitart FROM :str;
    if (sqlca.sqlcode < 0 )
    {
       	sprintf(error_msg, "prepare ins_zeitart %ld", sqlca.sqlcode);
  		PrintMsg( fun, error_msg, FEHL, -1 );
       	return -1;
    }
	 
	return OK;	 
}

int PrepareLoadTelnr(char *error_msg)
{
	char *fun = "PrepareLoadTelnr";
	int rc;

	strcpy(str,"insert into customerphoneno (");
  	strcat(str,"VERTRIEBSZENTRUMNR, ");
  	strcat(str,"KUNDENNR, ");
  	strcat(str,"TELNR, ");
  	strcat(str,"DATUM ");
	strcat(str," ) values (");
	strcat(str, chaus );
	strcat(str," ,?,?,? ");
	strcat(str, ")" );

	EXEC SQL PREPARE ins_telnr FROM :str;
    if (sqlca.sqlcode < 0 )
    {
       	sprintf(error_msg, "prepare ins_telnr %ld", sqlca.sqlcode);
  		PrintMsg( fun, error_msg, FEHL, -1 );
       	return -1;
    }

	strcpy(str,"select KUNDENNR,DATUM from customerphoneno ");
	strcat(str,"where VERTRIEBSZENTRUMNR = ");
	strcat(str, chaus );
	strcat(str," and TELNR = ? ");
	strcat(str," for update");

	EXEC SQL PREPARE sel_telnr FROM :str;
    if (sqlca.sqlcode < 0 )
    {
       	sprintf(error_msg, "prepare ins_telnr %ld", sqlca.sqlcode);
  		PrintMsg( fun, error_msg, FEHL, -1 );
       	return -1;
    }
	exec sql declare CSeltelnr cursor for sel_telnr;
	 
	strcpy( str, "update customerphoneno " );
	strcat( str, "set KUNDENNR = ?, " );
	strcat( str, "datum = ? " );
	strcat( str, "where current of CSeltelnr " );
	
	exec sql prepare upd_telnr from :str;
	ERROR_MSG2( "prepare upd_telnr" )
	 
	return OK;	 
}

int LadeKunde( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadeKunde";
	char huelse[20];
	int index;
	int rc;
	int errd;

	exec sql begin declare section;
	struct S_DKKUL *d;
	int etkdmerkmal1;
	int etkdmerkmal2;
    int etartklasse1;
    int etartklasse2;
	long imsbez;
    char dafuekz[3];
	int verbund;
	char vertriebsfiliale[3];
	char kundenklasse[4];
	char bl[6+1];
	char sprache[2+1];
	char vzkk1[1 + 1];
	char cMinLog[1+1];
	double surcharge;
	double deduction;
	int msv3cfgchangedate;
	long lPartner;
    exec sql end declare section;
	d = kun;

	cMinLog[0] = '0';
	cMinLog[1] = '\0';

    etkdmerkmal1 = EtKdMerkmal1( d );
    etkdmerkmal2 = EtKdMerkmal2( d );
    etartklasse1 = EtArtKlasse1( d );
    etartklasse2 = 0;

	strcpy(sprache,"  ");
	if(Schweiz)
	{
		if(d->KULWIDRO[0] == 'F')
			strcpy(sprache,"FR");
		else if(d->KULWIDRO[0] == 'I')
			strcpy(sprache,"I");
		else
			strcpy(sprache,"DE");
	}
	else if(Kroatien)
	{
		strcpy(sprache,"HR");
	}
	else if(Frankreich)
	{
		strcpy(sprache,"FR");
	}
	else if (Bulgarien && isCrema)
	{
		strcpy(sprache, "BG");
	}
	else
	{
		strcpy(sprache,"DE");
	}
	
	if ( d->KULVZKK1[0] != 'J' &&   d->KULVZKK1[0] != '1' )
		d->KULVZKK1[0] = '0';
	else
		d->KULVZKK1[0] = '1';
	if ( d->KULVZKK2[0] != 'J' &&   d->KULVZKK2[0] != '1' )
		d->KULVZKK2[0] = '0';
	else
		d->KULVZKK2[0] = '1';
	if ( d->KULVZKK3[0] != 'J' &&   d->KULVZKK3[0] != '1' )
		d->KULVZKK3[0] = '0';
	else
		d->KULVZKK3[0] = '1';
	if ( d->KULVZKK4[0] != 'J' &&   d->KULVZKK4[0] != '1' )
		d->KULVZKK4[0] = '0';
	else
		d->KULVZKK4[0] = '1';
	if ( d->KULVZKK5[0] != 'J' &&   d->KULVZKK5[0] != '1' )
		d->KULVZKK5[0] = '0';
	else
		d->KULVZKK5[0] = '1';

	if ( d->KULPHKK1[0] != 'J' &&   d->KULPHKK1[0] != '1' )
		d->KULPHKK1[0] = '0';
	else
		d->KULPHKK1[0] = '1';


	if ( d->KULPHKK2[0] == 'J' ||   d->KULPHKK2[0] == '1' )
		d->KULPHKK2[0] = '1';
	else if ( d->KULPHKK2[0] == '2')
		d->KULPHKK2[0] = '2';
	else
		d->KULPHKK2[0] = '0';

	if ( d->KULPHKK3[0] != 'J' &&   d->KULPHKK3[0] != '1' )
		d->KULPHKK3[0] = '0';
	else
		d->KULPHKK3[0] = '1';

	if ( d->KULPHKK4[0] == 'J' ||   d->KULPHKK4[0] == '1' )
		d->KULPHKK4[0] = '1';
	else if ( d->KULPHKK4[0] == '2')
		d->KULPHKK4[0] = '2';
	else
		d->KULPHKK4[0] = '0';

	if ( d->KULPHKK5[0] != 'J' &&   d->KULPHKK5[0] != '1' )
		d->KULPHKK5[0] = '0';
	else
		d->KULPHKK5[0] = '1';
/*	if ( d->KULVAPR[0] != 'J' &&   d->KULVAPR[0] != '1' )
		d->KULVAPR[0] = '0';
	else
		d->KULVAPR[0] = '1';
	if ( d->KULEP[0] != 'J' &&   d->KULEP[0] != '1' )
		d->KULEP[0] = '0';
	else
		d->KULEP[0] = '1';
*/	if ( d->KULMWST[0] != 'J' &&   d->KULMWST[0] != '1' )
		d->KULMWST[0] = '0';
	else
		d->KULMWST[0] = '1';
	if ( d->KULAUSSR[0] != 'J' &&   d->KULAUSSR[0] != '1' )
		d->KULAUSSR[0] = '0';
	else
		d->KULAUSSR[0] = '1';
	if ( d->KULHBAART[0] != 'J' &&   d->KULHBAART[0] != '1' )
		d->KULHBAART[0] = '0';
	else
		d->KULHBAART[0] = '1';


	if ( (rc = LadeDistress(kun, error_msg)) < 0) return rc;
	if(Bulgarien == YES)
	{
		if ( (rc = LadePayterm(kun, error_msg)) < 0) return rc;
		if ( (rc = LadePrint(kun, error_msg)) < 0) return rc;
	}
	else
	{
		if(!isCrema)
		{
			if((rc = LadeDebtlimit(kun, error_msg )) != 0) return rc;
		}
	}

	if ( d->KULKBOX[0] != '0' 
		&& d->KULKBOX[0] != '1'
		&& d->KULKBOX[0] != '2'
		&& d->KULKBOX[0] != '3')
	d->KULKBOX[0] = '1';

	if ( d->KULPLZ[0] == '+' )		 /* plz ist char und nicht int auf DB */
		{
		strncpy(d->KULPLZ, d->KULPLZ+1, LS_DKKUL_KULPLZ);
		d->KULPLZ[5] = '\0';
		}
	if ( d->KULDAFK[0] == '+' )		 /* kuldaffk ist P2 also P3 entpack aber c4 */ 
	   {  							 /* somit muessen die letzten beiden stellen */
       dafuekz[0] = d->KULDAFK[2];	 /* zugeordnete werden !!! */
       dafuekz[1] = d->KULDAFK[3];
       dafuekz[2] = '\0';
	   }
    /* :d->KULGRP,
	:dafuekz, */

	sprintf(huelse,"%*.*s",LS_DKKUL_KULKAADAT,LS_DKKUL_KULKAADAT,d->KULKAADAT);	//
	msv3cfgchangedate = atol(huelse);
	if((msv3cfgchangedate/100%100) == 0 || (msv3cfgchangedate/100%100) > 12)  msv3cfgchangedate = 0;	//kein gültiger Monat
	else if((msv3cfgchangedate%10000) == 0 || (msv3cfgchangedate%10000) > 31)  msv3cfgchangedate = 0;	//kein gültiger Tag
	else msv3cfgchangedate += 20000000;	//in Pharmos ohne Jahrhundert

	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEZI,LS_DKKUL_KULBEZI,d->KULBEZI);
    imsbez = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEZI2,LS_DKKUL_KULBEZI2,d->KULBEZI2);
    imsbez = imsbez + atol(huelse);
	if(d->KULVBS[0] == 'N') verbund = 0;
	else if(d->KULVBS[0] == 'J') verbund = 1;
	else if(d->KULVBS[0] == 'G') verbund = 2;
	else if(d->KULVBS[0] == 'S') verbund = 3;
	else if(d->KULVBS[0] == 'D') verbund = 4;
	else if(d->KULVBS[0] == 'M') verbund = 5;
	else verbund = 0;

    if ( d->KULBZPSY[0] != 'J' &&   d->KULBZPSY[0] != '1' )
	 d->KULBZPSY[0] = '0';
	 else
	 d->KULBZPSY[0] = '1';

	 vzkk1[0] = d->KULVZKK1[0];
    if ( d->KULBLPDISK[0] == '0')
	 d->KULBLPDISK[0] = '0';
    else if ( d->KULBLPDISK[0] == '3')
	 d->KULBLPDISK[0] = '1';
    else if ( d->KULBLPDISK[0] == '5')
	 d->KULBLPDISK[0] = '2';
	 else
	 vzkk1[0] = '3';

	if(d->KULVFIL[0] < '0' || d->KULVFIL[0] > '9') d->KULVFIL[0] = '0'; 
	if(d->KULVFIL[1] < '0' || d->KULVFIL[1] > '9') d->KULVFIL[1] = '0'; 
	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,d->KULFIL1);


	if(d->KULAFIL[0] < '0' || d->KULAFIL[0] > '9') d->KULAFIL[0] = '0'; 
	if(d->KULAFIL[1] < '0' || d->KULAFIL[1] > '9') d->KULAFIL[1] = '0'; 

	sprintf(kundenklasse,"%1.1s%2.2s",d->KULABC,d->KULABC2);
	if(!strcmp(kundenklasse,"   ")) strcpy(kundenklasse,"ZZZ");

	sprintf(huelse,"%*.*s",LS_DKKUL_KULPIIC,LS_DKKUL_KULPIIC,d->KULPIIC);
	index = (atol(huelse) / 100000) - 1;
	if(index < 0 || index > 15) strcpy(bl," ");
	else strcpy(bl,bundesland[index]);

	if(Bulgarien == YES)
	{
		sprintf(huelse,"%*.*s",LS_DKKUL_KULDOKGEB,LS_DKKUL_KULDOKGEB,d->KULDOKGEB);
		surcharge = (atof(huelse) / 100);
		sprintf(huelse,"%*.*s",LS_DKKUL_KULLIEFGEB,LS_DKKUL_KULLIEFGEB,d->KULLIEFGEB);
		deduction = (atof(huelse) / 100);
	}
	else
	{
		surcharge = 0.0;
		deduction = 0.0;
	}

	if(Bulgarien == YES)
	{
		long lCustomerno;
		sprintf(huelse,"%*.*s",L_DKKUL_KULIDF,L_DKKUL_KULIDF,d->KULIDF);
		lCustomerno = atol(huelse);
		lPartner = atol(vertriebsfiliale)*10000000 + lCustomerno;
	}
	else
	{
		sprintf(huelse,"%*.*s",LS_DKKUL_KULPARTNR,LS_DKKUL_KULPARTNR,d->KULPARTNR);
		lPartner = atol(huelse);
	}

	if (Schweiz == YES)
	{
		cMinLog[0] = d->KULZYTOH[0];
	}

	DEBUG_SECTION
	    printf("#%*.*s#\n",L_DKKUL_KULIDF,L_DKKUL_KULIDF,d->KULIDF);
		printf("#%*.*s#\n",L_DKKUL_KULKUBZ,L_DKKUL_KULKUBZ,d->KULKUBZ);
		printf("#%s#\n",vertriebsfiliale);
		printf("#%*.*s#\n",L_DKKUL_KULIKNR,L_DKKUL_KULIKNR,d->KULIKNR);
		printf("#%d#\n",etartklasse1);
		printf("#%d#\n",etartklasse2);
		printf("#%d#\n",etkdmerkmal1);
		printf("#%d#\n",etkdmerkmal2);
		printf("#%*.*s#\n",L_DKKUL_KULANRK,L_DKKUL_KULANRK,d->KULANRK);
		printf("#%*.*s#\n",L_DKKUL_KULNAM1,L_DKKUL_KULNAM1,d->KULNAM1);
		printf("#%*.*s#\n",L_DKKUL_KULNAM2,L_DKKUL_KULNAM2,d->KULNAM2);
		printf("#%*.*s#\n",L_DKKUL_KULSTR,L_DKKUL_KULSTR,d->KULSTR);
		printf("#%*.*s#\n",L_DKKUL_KULORT,L_DKKUL_KULORT,d->KULORT);
		printf("#%*.*s#\n",L_DKKUL_KULPLZ,L_DKKUL_KULPLZ,d->KULPLZ);
		printf("#%*.*s#\n",L_DKKUL_KULTELRF,L_DKKUL_KULTELRF,d->KULTELRF);
		printf("#%*.*s#\n",L_DKKUL_KULTEL,L_DKKUL_KULTEL,d->KULTEL);
		printf("#%*.*s#\n",L_DKKUL_KULFAX,L_DKKUL_KULFAX,d->KULFAX);
		printf("#%*.*s#\n",L_DKKUL_KULTELKW,L_DKKUL_KULTELKW,d->KULTELKW);
		printf("#%d#\n",imsbez);
		printf("#%*.*s#\n",L_DKKUL_KULGRP,L_DKKUL_KULGRP,d->KULGRP);
		printf("#%*.*s#\n",L_DKKUL_KULVER1,L_DKKUL_KULVER1,d->KULVER1);
		printf("#%s#\n",dafuekz);
		printf("#%*.*s#\n",L_DKKUL_KULDOPPKONT,L_DKKUL_KULDOPPKONT,d->KULDOPPKONT);
		printf("#%*.*s#\n",L_DKKUL_KULRELA,L_DKKUL_KULRELA,d->KULRELA);
		printf("#%*.*s#\n",L_DKKUL_KULPORE,L_DKKUL_KULPORE,d->KULPORE);
		printf("#%*.*s#\n",L_DKKUL_KULPOASO,L_DKKUL_KULPOASO,d->KULPOASO);
		printf("#%s#\n",kundenklasse);
		printf("#%*.*s#\n",L_DKKUL_KULAFIL,L_DKKUL_KULAFIL,d->KULAFIL);
		printf("#%*.*s#\n",L_DKKUL_KULVFIL,L_DKKUL_KULVFIL,d->KULVFIL);
		printf("#%*.*s#\n",L_DKKUL_KULDAFU,L_DKKUL_KULDAFU,d->KULDAFU);
		printf("#%*.*s#\n",L_DKKUL_KULTOURE,L_DKKUL_KULTOURE,d->KULTOURE);
		printf("#%d#\n",verbund);
		printf("#%*.*s#\n",L_DKKUL_KULSOAART,L_DKKUL_KULSOAART,d->KULSOAART);
		printf("#%*.*s#\n",L_DKKUL_KULPWDR,L_DKKUL_KULPWDR,d->KULPWDR);
		printf("#%*.*s#\n",L_DKKUL_KULVZKK1,L_DKKUL_KULVZKK1,d->KULVZKK1);
		printf("#%*.*s#\n",L_DKKUL_KULKBOX,L_DKKUL_KULKBOX,d->KULKBOX);
		printf("#%*.*s#\n",L_DKKUL_KULKIPPZ,L_DKKUL_KULKIPPZ,d->KULKIPPZ);
		printf("#%*.*s#\n",L_DKKUL_KULIMS3000,L_DKKUL_KULIMS3000,d->KULIMS3000);
		printf("#%*.*s#\n",L_DKKUL_KULLKZ,L_DKKUL_KULLKZ,d->KULLKZ);
		printf("#%*.*s#\n",L_DKKUL_KULDRREI,L_DKKUL_KULDRREI,d->KULDRREI);
		printf("#%*.*s#\n",L_DKKUL_KULBLPDISK,L_DKKUL_KULBLPDISK,d->KULBLPDISK);
		printf("#%*.*s#\n",L_DKKUL_KULAZYX,L_DKKUL_KULAZYX,d->KULAZYX);
		printf("#%*.*s#\n",L_DKKUL_KULPIIC,L_DKKUL_KULPIIC,d->KULPIIC);
		printf("#%*.*s#\n",L_DKKUL_KULUIN,L_DKKUL_KULUIN,d->KULUIN);
		printf("#%*.*s#\n",L_DKKUL_KULIMSAPO,L_DKKUL_KULIMSAPO,d->KULIMSAPO);
		printf("#%*.*s#\n",L_DKKUL_KULKUART,L_DKKUL_KULKUART,d->KULKUART);
		printf("#%s#\n",bl);
		printf("#%d#\n",datum);
		printf("#%d#\n",dbzeit);
	END_DEBUG_SECTION

		count++;

	if (Schweiz == YES)
	{
		EXEC SQL EXECUTE upd_kunde_ch USING :d->KULIDF,
			:d->KULKUBZ,
			:d->KULFIL1,
			:d->KULIKNR,
			:etartklasse1,
			:etartklasse2,
			:etkdmerkmal1,
			:etkdmerkmal2,
			:d->KULANRK,
			:d->KULNAM1,
			:d->KULNAM2,
			:d->KULSTR,
			:d->KULORT,
			:d->KULPLZ,
			:d->KULTELRF,
			:d->KULTEL,
			:d->KULFAX,
			:d->KULTELKW,
			:imsbez,
			:d->KULGRP,
			:d->KULVER1,
			:dafuekz,
			:d->KULDOPPKONT,
			:d->KULRELA,
			:d->KULPORE,
			:d->KULPOASO,
			:kundenklasse,
			:d->KULVFIL,
			:d->KULAFIL,
			:d->KULDAFU,
			:d->KULTOURE,
			:verbund,
			:d->KULSOAART,
			:d->KULPWDR,
			:vzkk1,
			:d->KULKBOX,
			:d->KULKIPPZ,
			'1',
			:d->KULIMS3000,
			:d->KULLKZ,
			:d->KULDRREI,
			:d->KULBLPDISK,
			:d->KULAZYX,
			:d->KULPIIC,
			:d->KULUIN,
			:d->KULIMSAPO,
			:d->KULKUART,
			:vertriebsfiliale,
			:d->KULIDF,
			:bl,
			:datum,
			:dbzeit,
			'1',
			'I',
			:d->KULWAFO,
			:sprache,
			:d->KULVIP,
			:d->KULBZPSY,
			:d->KULDAFID,
			:d->KULABSAG,
			:d->KULANZAUF,
			:d->KULBEDI,
			:d->KULKRNUM,
			:d->KULKZBER,
			:d->KULLZNUM,
			:d->KULLZNBTM,
			:d->KULPHKK3,
			:d->KULPHKK1,
			:d->KULMWST,
			:d->KULAUSSR,
			:d->KULHBAART,
			:d->KULLIEF,
			:d->KULHPTIDF,
			'0',
			:d->KULPHKK5,
			:d->KULDOKGEB,
			:d->KULLIEFGEB,
			:d->KULLIEF,
			:msv3cfgchangedate,
			:lPartner,
			:cMinLog,
			:d->KULVERS,
			:d->KULVAPR,
			:d->KULPP,
			:vertriebsfiliale,
			:d->KULIDF
			;
		ERROR_MSG3("upd kunde_ch:", d->KULIDF)
			errd = sqlca.sqlerrd[2];
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0)  /* NotFound */
		{
			exec sql insert into kunde(KUNDE_LISTE, emailadresse, nachliefertyp, kzsprache
				, phonepriority, kzpsychostoffe, softwarehouse
				, prewholetyp, anzaufclose, payment_term
				, krankenkassennr, calculationtype, apolizens
				, btmlizens, surcharge_basic, deduction_basic
				, vatregistered
				, rebatemethfreesale, rebatemethhealthf
				, maincstno, mastercstno
				, surcharge_basic_kk, deduction_basic_kk
				, surchargepctkk, deductionpctkk
				, manufacturerno, msv3cfgchangedate, partnernr, minlogaddbehavior
				, sendcollectivinvoice, linefee, packagefee)
				values(:d->KULIDF,
					:d->KULKUBZ,
					:d->KULFIL1,
					:d->KULIKNR,
					:etartklasse1,
					:etartklasse2,
					:etkdmerkmal1,
					:etkdmerkmal2,
					:d->KULANRK,
					:d->KULNAM1,
					:d->KULNAM2,
					:d->KULSTR,
					:d->KULORT,
					:d->KULPLZ,
					:d->KULTELRF,
					:d->KULTEL,
					:d->KULFAX,
					:d->KULTELKW,
					:imsbez,
					:d->KULGRP,
					:d->KULVER1,
					:dafuekz,
					:d->KULDOPPKONT,
					:d->KULRELA,
					:d->KULPORE,
					:d->KULPOASO,
					:kundenklasse,
					:d->KULVFIL,
					:d->KULAFIL,
					:d->KULDAFU,
					:d->KULTOURE,
					:verbund,
					:d->KULSOAART,
					:d->KULPWDR,
					:vzkk1,
					:d->KULKBOX,
					:d->KULKIPPZ,
					'1',
					:d->KULIMS3000,
					:d->KULLKZ,
					:d->KULDRREI,
					:d->KULBLPDISK,
					:d->KULAZYX,
					:d->KULPIIC,
					:d->KULUIN,
					:d->KULIMSAPO,
					:d->KULKUART,
					:vertriebsfiliale,
					:d->KULIDF,
					:bl,
					:datum,
					:dbzeit,
					'1',
					'I',
					' ',
					:d->KULWAFO,
					:sprache,
					:d->KULVIP,
					:d->KULBZPSY,
					:d->KULDAFID,
					:d->KULABSAG,
					:d->KULANZAUF,
					:d->KULBEDI,
					:d->KULKRNUM,
					:d->KULKZBER,
					:d->KULLZNUM,
					:d->KULLZNBTM,
					:d->KULPHKK3,
					:d->KULPHKK1,
					:d->KULMWST,
					:d->KULAUSSR,
					:d->KULHBAART,
					:d->KULLIEF,
					:d->KULHPTIDF,
					'0',
					:d->KULPHKK5,
					:d->KULDOKGEB,
					:d->KULLIEFGEB,
					:d->KULLIEF,
					:msv3cfgchangedate,
					:lPartner,
					:cMinLog,
					:d->KULVERS,
					:d->KULVAPR,
					:d->KULPP
					);
			ERROR_MSG3("insert kunde ch:", d->KULIDF)
			CheckQuota(d->KULIDF, error_msg);
		}
	}
	else
	{
		EXEC SQL EXECUTE upd_kunde USING :d->KULIDF,
			:d->KULKUBZ,
			:d->KULFIL1,
			:d->KULIKNR,
			:etartklasse1,
			:etartklasse2,
			:etkdmerkmal1,
			:etkdmerkmal2,
			:d->KULANRK,
			:d->KULNAM1,
			:d->KULNAM2,
			:d->KULSTR,
			:d->KULORT,
			:d->KULPLZ,
			:d->KULTELRF,
			:d->KULTEL,
			:d->KULFAX,
			:d->KULTELKW,
			:imsbez,
			:d->KULGRP,
			:d->KULVER1,
			:dafuekz,
			:d->KULDOPPKONT,
			:d->KULRELA,
			:d->KULPORE,
			:d->KULPOASO,
			:kundenklasse,
			:d->KULVFIL,
			:d->KULAFIL,
			:d->KULDAFU,
			:d->KULTOURE,
			:verbund,
			:d->KULSOAART,
			:d->KULPWDR,
			:vzkk1,
			:d->KULKBOX,
			:d->KULKIPPZ,
			'1',
			:d->KULIMS3000,
			:d->KULLKZ,
			:d->KULDRREI,
			:d->KULBLPDISK,
			:d->KULAZYX,
			:d->KULPIIC,
			:d->KULUIN,
			:d->KULIMSAPO,
			:d->KULKUART,
			:vertriebsfiliale,
			:d->KULIDF,
			:bl,
			:datum,
			:dbzeit,
			'1',
			'I',
			:d->KULWAFO,
			:sprache,
			:d->KULVIP,
			:d->KULBZPSY,
			:d->KULDAFID,
			:d->KULABSAG,
			:d->KULANZAUF,
			:d->KULBEDI,
			:d->KULKRNUM,
			:d->KULKZBER,
			:d->KULLZNUM,
			:d->KULLZNBTM,
			:d->KULPHKK3,
			:d->KULPHKK1,
			:d->KULVAPR,
			:d->KULEP,
			:d->KULMWST,
			:d->KULAUSSR,
			:d->KULHBAART,
			:d->KULLIEF,
			:d->KULHPTIDF,
			'0',
			:d->KULPHKK5,
			:d->KULDOKGEB,
			:d->KULLIEFGEB,
			:d->KULLIEF,
			:msv3cfgchangedate,
			:lPartner,
			:cMinLog,
			:d->KULVERS,
			:vertriebsfiliale,
			:d->KULIDF
			;
		ERROR_MSG3("upd kunde:", d->KULIDF)
			errd = sqlca.sqlerrd[2];
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0)  /* NotFound */
		{
			exec sql insert into kunde(KUNDE_LISTE, emailadresse, nachliefertyp, kzsprache
				, phonepriority, kzpsychostoffe, softwarehouse
				, prewholetyp, anzaufclose, payment_term
				, krankenkassennr, calculationtype, apolizens
				, btmlizens, surcharge_basic, deduction_basic
				, surchargepct, deductionpct, vatregistered
				, rebatemethfreesale, rebatemethhealthf
				, maincstno, mastercstno
				, surcharge_basic_kk, deduction_basic_kk
				, surchargepctkk, deductionpctkk
				, manufacturerno, msv3cfgchangedate, partnernr, minlogaddbehavior
				, sendcollectivinvoice)
				values(:d->KULIDF,
					:d->KULKUBZ,
					:d->KULFIL1,
					:d->KULIKNR,
					:etartklasse1,
					:etartklasse2,
					:etkdmerkmal1,
					:etkdmerkmal2,
					:d->KULANRK,
					:d->KULNAM1,
					:d->KULNAM2,
					:d->KULSTR,
					:d->KULORT,
					:d->KULPLZ,
					:d->KULTELRF,
					:d->KULTEL,
					:d->KULFAX,
					:d->KULTELKW,
					:imsbez,
					:d->KULGRP,
					:d->KULVER1,
					:dafuekz,
					:d->KULDOPPKONT,
					:d->KULRELA,
					:d->KULPORE,
					:d->KULPOASO,
					:kundenklasse,
					:d->KULVFIL,
					:d->KULAFIL,
					:d->KULDAFU,
					:d->KULTOURE,
					:verbund,
					:d->KULSOAART,
					:d->KULPWDR,
					:vzkk1,
					:d->KULKBOX,
					:d->KULKIPPZ,
					'1',
					:d->KULIMS3000,
					:d->KULLKZ,
					:d->KULDRREI,
					:d->KULBLPDISK,
					:d->KULAZYX,
					:d->KULPIIC,
					:d->KULUIN,
					:d->KULIMSAPO,
					:d->KULKUART,
					:vertriebsfiliale,
					:d->KULIDF,
					:bl,
					:datum,
					:dbzeit,
					'1',
					'I',
					' ',
					:d->KULWAFO,
					:sprache,
					:d->KULVIP,
					:d->KULBZPSY,
					:d->KULDAFID,
					:d->KULABSAG,
					:d->KULANZAUF,
					:d->KULBEDI,
					:d->KULKRNUM,
					:d->KULKZBER,
					:d->KULLZNUM,
					:d->KULLZNBTM,
					:d->KULPHKK3,
					:d->KULPHKK1,
					:d->KULVAPR,
					:d->KULEP,
					:d->KULMWST,
					:d->KULAUSSR,
					:d->KULHBAART,
					:d->KULLIEF,
					:d->KULHPTIDF,
					'0',
					:d->KULPHKK5,
					:d->KULDOKGEB,
					:d->KULLIEFGEB,
					:d->KULLIEF,
					:msv3cfgchangedate,
					:lPartner,
					:cMinLog,
					:d->KULVERS
				);
			ERROR_MSG3("insert kunde:", d->KULIDF)
			CheckQuota(d->KULIDF, error_msg);
		}
	}
	return OK;
}

int LadeDebtlimit( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadeDebtlimit";
	char huelse[20];
	long limit;
	int upd = 0;

	exec sql begin declare section;
	struct S_DKKUL *d;
	long partnernr;
	char name[31];
	char mainname[31];
	long mainno;
	char vertriebsfiliale[3];
    exec sql end declare section;

	d = kun;

	sprintf(huelse,"%*.*s",LS_DKKUL_KULPARTNR,LS_DKKUL_KULPARTNR,kun->KULPARTNR);
	partnernr = atol(huelse);

	if(partnernr == 0) return OK;

	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,d->KULFIL1);

	EXEC SQL open SelLimit using :partnernr;
	ERROR_MSG3( "open SelLimit:",d->KULPARTNR )
	EXEC SQL fetch SelLimit;
	ERROR_MSG2( "fetch SelLimit" )
	if ( sqlca.sqlcode == 100 )
	{
		EXEC SQL open SelKunde using
	                         :vertriebsfiliale,
							 :d->KULIDF;
		ERROR_MSG3( "open SelKunde:",d->KULIDF )
		EXEC SQL fetch SelKunde into :name,:mainno;
		ERROR_MSG2( "fetch SelKunde" )
		if ( sqlca.sqlcode == 100 )
		{
			strcpy(mainname," ");
		}
		else if(mainno > 0)
		{
			EXEC SQL open SelKunde using
	                         :vertriebsfiliale,
							 :mainno;
			ERROR_MSG2( "open SelKunde main" )
			EXEC SQL fetch SelKunde into :mainname,:mainno;
			ERROR_MSG2( "fetch SelKunde main" )
			if ( sqlca.sqlcode == 100 )
			{
				strcpy(mainname,name);
			}
		}
		else
		{
			strcpy(mainname,name);
		}
		EXEC SQL EXECUTE ins_limit using
				:partnernr,
				:mainname
			;
		ERROR_MSG2( "ins_limit" )
	}
	return OK;
}

int LadeDistress( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadeDistress";
	char huelse[20];
	int index;

	exec sql begin declare section;
	struct S_DKKUL *d;
	char vertriebsfiliale[3];
	char orgfiliale[3];
    exec sql end declare section;
	d = kun;

    if ( d->KULAESPER[0] == 'J' ||  d->KULAESPER[0] == '1' )
		return OK;
    if ( d->KULLOE[0] == 'J' ||  d->KULLOE[0] == '1' )
		return OK;
	if ( !strncmp(d->KULGRP,"04",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"05",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"06",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"07",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"08",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"09",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"10",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"11",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"12",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"13",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"14",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"15",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"16",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"17",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"18",2) )
		return OK;
	if(d->KULVFIL[0] < '0' || d->KULVFIL[0] > '9') d->KULVFIL[0] = '0'; 
	if(d->KULVFIL[1] < '0' || d->KULVFIL[1] > '9') d->KULVFIL[1] = '0'; 
	sprintf(orgfiliale,"%*.*s",L_DKKUL_KULVFIL,L_DKKUL_KULVFIL,d->KULVFIL);

	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,d->KULFIL1);

	if( (atoi(orgfiliale)) != 0)
	{
		if( (atoi(orgfiliale)) != (atoi(vertriebsfiliale)))
			return OK;
	}

	EXEC SQL EXECUTE upd_distress USING :vertriebsfiliale,
										:d->KULIDF;
	ERROR_MSG3( "upd distress:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		EXEC SQL EXECUTE ins_distress USING :vertriebsfiliale,
											:d->KULIDF;
		ERROR_MSG3( "uns distress:",d->KULIDF )
	}
	return OK;
}

int LadePayterm( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadePayterm";
	char huelse[20];
	int index;

	exec sql begin declare section;
	struct S_DKKUL *d;
	paytermS payterm;
	paytermS *ppayterm;
	char vertriebsfiliale[3];
    exec sql end declare section;
	d = kun;
	ppayterm = &payterm;

	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,d->KULFIL1);
	if(strncmp(d->KULBEDI,"    ",L_DKKUL_KULBEDI))
	{
		EXEC SQL EXECUTE sel_payterm into :ppayterm
									using :d->KULBEDI;
		ERROR_MSG3( "sel_payterm:",d->KULIDF )
		if(sqlca.sqlcode != 100)
		{
			EXEC SQL EXECUTE upd_payterm USING	:vertriebsfiliale,
												:d->KULIDF,
												'0',
												:ppayterm->PAYMENTARGET;
			ERROR_MSG3( "upd_payterm:",d->KULIDF )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
			{
				EXEC SQL EXECUTE ins_payterm USING	:vertriebsfiliale,
													:d->KULIDF,
													'0',
													:ppayterm->PAYMENTARGET;
				ERROR_MSG3( "ins_payterm:",d->KULIDF )
			}
		}
	}

	if(strncmp(d->KULBEDI2,"    ",L_DKKUL_KULBEDI2))
	{
		EXEC SQL EXECUTE sel_payterm into :ppayterm
									using :d->KULBEDI2;
		ERROR_MSG3( "sel_payterm2:",d->KULIDF )
		if(sqlca.sqlcode != 100)
		{
			EXEC SQL EXECUTE upd_payterm USING	:vertriebsfiliale,
												:d->KULIDF,
												'1',
												:ppayterm->PAYMENTARGET;
			ERROR_MSG3( "upd_payterm2:",d->KULIDF )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
			{
				EXEC SQL EXECUTE ins_payterm USING	:vertriebsfiliale,
													:d->KULIDF,
													'1',
													:ppayterm->PAYMENTARGET;
				ERROR_MSG3( "ins_payterm2:",d->KULIDF )
			}
		}
	}

	if(strncmp(d->KULBEDI3,"    ",L_DKKUL_KULBEDI3))
	{
		EXEC SQL EXECUTE sel_payterm into :ppayterm
									using :d->KULBEDI3;
		ERROR_MSG3( "sel_payterm3:",d->KULIDF )
		if(sqlca.sqlcode != 100)
		{
			EXEC SQL EXECUTE upd_payterm USING	:vertriebsfiliale,
												:d->KULIDF,
												'5',
												:ppayterm->PAYMENTARGET;
			ERROR_MSG3( "upd_payterm3:",d->KULIDF )
			if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
			{
				EXEC SQL EXECUTE ins_payterm USING	:vertriebsfiliale,
													:d->KULIDF,
													'5',
													:ppayterm->PAYMENTARGET;
				ERROR_MSG3( "ins_payterm3:",d->KULIDF )
			}
		}
	}

	return OK;
}

int LadePrint( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadePrint";
	char huelse[20];
	int index;

	exec sql begin declare section;
	struct S_DKKUL *d;
	cstprintS cstprint;
	cstprintS *pcstprint;
	char vertriebsfiliale[3];
    exec sql end declare section;

	d = kun;
	pcstprint = &cstprint;

	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,d->KULFIL1);
	EXEC SQL EXECUTE upd_print using
								:vertriebsfiliale,
								:d->KULIDF,
								'0',
								:d->KULVZKK3,
								:d->KULVZKK4,
								:d->KULPHKK2,
								:vertriebsfiliale,
								:d->KULIDF,
								'0';

	ERROR_MSG3( "upd_print FV:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		EXEC SQL EXECUTE ins_print USING
								:vertriebsfiliale,
								:d->KULIDF,
								'0',
								:d->KULVZKK3,
								:d->KULVZKK4,
								:d->KULPHKK2;
			ERROR_MSG3( "ins_print FV:",d->KULIDF )
	}
	EXEC SQL EXECUTE upd_print using
								:vertriebsfiliale,
								:d->KULIDF,
								'1',
								:d->KULVZKK1,
								:d->KULVZKK2,
								:d->KULPHKK4,
								:vertriebsfiliale,
								:d->KULIDF,
								'1';

	ERROR_MSG3( "upd_print KK:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		EXEC SQL EXECUTE ins_print USING
								:vertriebsfiliale,
								:d->KULIDF,
								'1',
								:d->KULVZKK1,
								:d->KULVZKK2,
								:d->KULPHKK4;
			ERROR_MSG3( "ins_print KK:",d->KULIDF )
	}

	return OK;
}

int LadeCustomerrouting( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadeCustomerrouting";
	int iAnzTage;

	exec sql begin declare section;
	struct S_DKKUL *d;
	short sWeekDay;
    exec sql end declare section;

	d = kun;

	if ( !strncmp(d->KULGRP,"04",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"05",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"07",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"08",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"09",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"10",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"11",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"12",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"13",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"14",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"15",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"16",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"17",2) )
		return OK;
	if ( !strncmp(d->KULGRP,"18",2) )
		return OK;
	/* gesperrte Kunden nicht routen */
    if ( d->KULAESPER[0] == 'J' || d->KULAESPER[0] == '1' )
		return OK;
    if ( d->KULLOE[0] == 'J' ||  d->KULLOE[0] == '1' ) /* mit LOEKZ als gesperrt übernehmen */
		return OK;

/*	if(Frankreich)
	{
		iAnzTage = 5;
		sWeekDay = 1;
	}
	else	*/
	{
		iAnzTage = 7;
		sWeekDay = 0;
	}

	for( ; sWeekDay < iAnzTage ; sWeekDay++ )
	{
		EXEC SQL EXECUTE upd_customerrouting USING :d->KULIDF,
	                                      :sSrcBranch,
										  :lZeitVon,
										  :lZeitBis,
										  :sDestBranch,
										  ' ',
										  :sWeekDay,
	                                      :sSrcBranch,
	                                      :d->KULIDF,
										  :sWeekDay,
										  :lZeitVon;

		ERROR_MSG3( "upd_customerrouting:",d->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
			EXEC SQL EXECUTE ins_customerrouting USING :d->KULIDF,
	                                      :sSrcBranch,
										  :lZeitVon,
										  :lZeitBis,
										  :sDestBranch,
										  ' ',
										  :sWeekDay;
			ERROR_MSG3( "ins_customerrouting:",d->KULIDF )
		}
	}
	return OK;
}

int LadeKundeSchalter( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadeKundeSchalter";

	exec sql begin declare section;
	struct S_DKKUL *d;
	char musskopf[1];
	char sepauft[1];
	char zurueck[1];
	char rrab[1];
	char eilab[1];
	char trennalpha[1];
	char rr0800[1];
	char trennalphaurr[1];
	char trenndefekt[1];
	char sa06meld[1];
	char sa04meld[1];
	char vertriebsfiliale[3];
	char    SKDBLICKPUNKTABO[1 + 1];
	char    SKDBUECHER[1 + 1];
	char    SKDVERTRIEBBINDUNG[1 + 1];
	char    SKDPOOL[1 + 1];
	char    SKDBOUHON[1 + 1];
	char    SKDROCHE[1 + 1];
	char    SKDVICHY[1 + 1];
	char    SKDVBFILIALEMELD[1 + 1];
	char    SKDORIGINALMELD[1 + 1];
	char    SKDKEINNL[1 + 1];
	char    SPERRKZ[1 + 1];
	char    ABSAG[1 + 1];
	char    HALFMARGIN[1 + 1];
	char    DISCOUNTEXCEPT[1 + 1];
	char    SKDLISTE5[1 + 1];
	char    SKDINVOICEDISC[1 + 1];
	char    SKDINVOICEEMAIL[1 + 1];
	char    SKDNOEXPIRYINFO[1 + 1];
	short	sskdmailinvoice = 0;
	short	sskdmailbatchchangeadvice = 0;
	short	sskdfaxinvoice = 0;
	short	sskdfaxbatchchangeadvice = 0;
	short	sskdfmd = 0;
	exec sql end declare section;

	d = kun;

//	if(d->KULNLNOTA[0] == 'J' || d->KULNLNOTA[0] == '1')   strcpy(SKDKEINNL,"1");
//	else strcpy(SKDKEINNL,"0");
	if(d->KULAWDEF[0] == 'J')   strcpy(SKDORIGINALMELD,"1");
	else strcpy(SKDORIGINALMELD,"0");
	if(d->KULVBED[0] == 'J')   strcpy(SKDVERTRIEBBINDUNG,"1");
	else strcpy(SKDVERTRIEBBINDUNG,"0");
	if(d->KULVBA[0] == 'J')    strcpy(SKDROCHE,"1");
	else strcpy(SKDROCHE,"0");
	if(d->KULVB1[0] == 'J')    strcpy(SKDVICHY,"1");
	else strcpy(SKDVICHY,"0");
	if(d->KULVB2[0] == 'J')    strcpy(SKDBOUHON,"1");
	else strcpy(SKDBOUHON,"0");
	if(d->KULVB3[0] == 'J')    strcpy(SKDPOOL,"1");
	else strcpy(SKDPOOL,"0");
	if(d->KULVB4[0] == 'J')    strcpy(SKDBUECHER,"1");
	else strcpy(SKDBUECHER,"0");
	if(d->KULDFVBRU[0] == 'J') strcpy(SKDVBFILIALEMELD,"1");
	else strcpy(SKDVBFILIALEMELD,"0");
	if(d->KULBLP[0] == 'J') strcpy(SKDBLICKPUNKTABO,"1");
	else strcpy(SKDBLICKPUNKTABO,"0");
	if(Schweiz == YES)
	{
		if(d->KULVRMAIL[0] == ' ')
			SKDNOEXPIRYINFO[0] = '0';
		else
			SKDNOEXPIRYINFO[0] = d->KULVRMAIL[0];
	}
	else
	{
		SKDNOEXPIRYINFO[0] = '0';
	}
	if(Bulgarien == YES)
	{
		if ( d->KULSPKT5[0] != 'J' &&   d->KULSPKT5[0] != '1' )
			HALFMARGIN[0] = '0';
		else
			HALFMARGIN[0] = '1';
	}
	else
	{
		HALFMARGIN[0] = '0';
		if ( d->KULSPKT5[0] != 'J' &&   d->KULSPKT5[0] != '1' )
			d->KULSPKT5[0] = '0';
		else
			d->KULSPKT5[0] = '1';
	}
	if ( d->KULBONVER[0] != 'J' &&   d->KULBONVER[0] != '1' )
		DISCOUNTEXCEPT[0] = '0';
	else
		DISCOUNTEXCEPT[0] = '1';

	if(Schweiz == YES)
	{
	    if ( d->KULFACH[0] == 'J' )
			d->KULFACH[0] = '1';
	    else if ( d->KULFACH[0] == 'F' && d->KULWIDRO[0] == 'F' )
			d->KULFACH[0] = '1';
	    else if ( d->KULFACH[0] == 'I' && d->KULWIDRO[0] == 'I' )
			d->KULFACH[0] = '1';
	    else if ( d->KULFACH[0] == 'D' && d->KULWIDRO[0] == 'D' )
			d->KULFACH[0] = '1';
		else
			d->KULFACH[0] = '0';
	}
	else
	{
	    if ( d->KULFACH[0] != 'J' &&   d->KULFACH[0] != '1' )
			d->KULFACH[0] = '0';
		else
			d->KULFACH[0] = '1';
	}
    if ( d->KULKUFA[0] != 'J' &&  d->KULKUFA[0] != '1' )
	 d->KULKUFA[0] = '0';
	 else
	 d->KULKUFA[0] = '1';
    if ( d->KULNRRE[0] != 'J' &&   d->KULNRRE[0] != '1' )
	 d->KULNRRE[0] = '0';
	 else
	 d->KULNRRE[0] = '1';
    if ( d->KULNEAK[0] != 'J' &&   d->KULNEAK[0] != '1' )
	 d->KULNEAK[0] = '0';
	 else
	 d->KULNEAK[0] = '1';
    if ( d->KULNALI[0] != 'J' &&   d->KULNALI[0] != '1' )
	 d->KULNALI[0] = '0';
	 else
	 d->KULNALI[0] = '1';
    if ( d->KULABSAG[0] != 'J' &&   d->KULABSAG[0] != '1' )
	 d->KULABSAG[0] = '0' ;
	 else
	 d->KULABSAG[0] = '1' ;
	ABSAG[0] = d->KULABSAG[0];
	ABSAG[1] = '\0';
    if ( d->KULDSDAF[0] != 'J' &&   d->KULDSDAF[0] != '1' )
	 d->KULDSDAF[0] = '0';
	 else
	 d->KULDSDAF[0] = '1';
    if ( d->KULAES[0] != 'J' &&   d->KULAES[0] != '1' )
	 d->KULAES[0] = '0';
	 else
	 d->KULAES[0] = '1';
    if ( d->KULMEER[0] != 'J' &&   d->KULMEER[0] != '1' )
	 d->KULMEER[0] = '0';
	 else
	 d->KULMEER[0] = '1';
    if ( d->KULAWDEF[0] != 'J' &&   d->KULAWDEF[0] != '1' )
	 d->KULAWDEF[0] = '0';
	 else
	 d->KULAWDEF[0] = '1';
    if ( d->KULDRKOMMI[0] != 'J' &&   d->KULDRKOMMI[0] != '1' )
	 d->KULDRKOMMI[0] = '0';
	 else
	 d->KULDRKOMMI[0] = '1';
    if ( d->KULAUFZU[0] != 'J' &&   d->KULAUFZU[0] != '1' )
	 d->KULAUFZU[0] = '0';
	 else
	 d->KULAUFZU[0] = '1';
    if ( d->KULMWST[0] != 'J' &&   d->KULMWST[0] != '1' )
	 d->KULMWST[0] = '0';
	 else
	 d->KULMWST[0] = '1';
    if ( d->KULSTKUN[0] != 'J' &&   d->KULSTKUN[0] != '1' )
	 d->KULSTKUN[0] = '0';
	 else
	 d->KULSTKUN[0] = '1';
    if ( d->KULVALSP[0] != 'J' &&   d->KULVALSP[0] != '1' )
	 d->KULVALSP[0] = '0';
	 else
	 d->KULVALSP[0] = '1';
    if ( d->KULSPKT1[0] != 'J' &&   d->KULSPKT1[0] != '1' )
	 d->KULSPKT1[0] = '0';
	 else
	 d->KULSPKT1[0] = '1';
    if ( d->KULSPKT2[0] != 'J' &&   d->KULSPKT2[0] != '1' )
	 d->KULSPKT2[0] = '0';
	 else
	 d->KULSPKT2[0] = '1';
    if ( d->KULSPKT3[0] != 'J' &&   d->KULSPKT3[0] != '1' )
	 d->KULSPKT3[0] = '0';
	 else
	 d->KULSPKT3[0] = '1';
    if ( d->KULSPKT4[0] != 'J' &&   d->KULSPKT4[0] != 'M' &&   d->KULSPKT4[0] != '1' )
	 d->KULSPKT4[0] = '0';
	 else
	 d->KULSPKT4[0] = '1';
    if ( d->KULSPKT5[0] != 'J' &&   d->KULSPKT5[0] != '1' )
	 d->KULSPKT5[0] = '0';
	 else
	 d->KULSPKT5[0] = '1';
    if ( d->KULVBSG[0] != 'J' &&   d->KULVBSG[0] != '1' )
	 d->KULVBSG[0] = '0';
	 else
	 d->KULVBSG[0] = '1';
    if ( d->KULVBS[0] != 'J' &&   d->KULVBS[0] != '1' )
	 d->KULVBS[0] = '0';
	 else
	 d->KULVBS[0] = '1';
    if ( d->KULKRK[0] != 'J' &&   d->KULKRK[0] != '1' )
	 d->KULKRK[0] = '0';
	 else
	 d->KULKRK[0] = '1';
    if ( d->KULKZEILS[0] != 'J' &&   d->KULKZEILS[0] != '1' )
	 d->KULKZEILS[0] = '0';
	 else
	 d->KULKZEILS[0] = '1';
    if ( d->KULVIP[0] != 'V' &&   d->KULVIP[0] != '1' )
	 d->KULVIP[0] = '0';
	 else
	 d->KULVIP[0] = '1';
    if ( d->KULMVDAER[0] != 'J' &&  d->KULMVDAER[0] != '1' )
	 d->KULMVDAER[0] = '0';
	 else
	 d->KULMVDAER[0] = '1';
    if ( d->KULAS[0] != 'J' &&  d->KULAS[0] != '1' )
	 d->KULAS[0] = '0';
	 else
	 d->KULAS[0] = '1';
    if ( d->KULRIS[0] != 'J' &&  d->KULRIS[0] != '1' )
	 d->KULRIS[0] = '0';
	 else
	 d->KULRIS[0] = '1';
    if ( d->KULAUFEINPR[0] != 'J' &&  d->KULAUFEINPR[0] != '1' )
	 d->KULAUFEINPR[0] = '0';
	 else
	 d->KULAUFEINPR[0] = '1';
    if (strncmp(d->KULKUBZ,VB,2))
	 musskopf[0] = '0';
	 else
	 musskopf[0] = '1';
	 /*
	 if ( d->KULKAH[0] != 'J' &&  d->KULKAH[0] != '1' )
	 sepauft[0] = '0';
	 else
	 sepauft[0] = '1';
	 */

     zurueck[0] = '0';
     sepauft[0] = '0';	/* auftrag zusammenführen */
     rrab[0] = '0';
     eilab[0] = '0';
     trennalpha[0] = '0';
     trenndefekt[0] = '0';
	rr0800[0] = '0';
	trennalphaurr[0] = '0';
     if ( d->KULKAH[0] == 'J' || d->KULKAH[0] == '1' )
	    sepauft[0] = '1';
	 else if ( d->KULKAH[0] == '2' )
	 {
        zurueck[0] = '1';
        sepauft[0] = '0';	/* auftrag zusammenführen */
	 }
	 else if ( d->KULKAH[0] == '3' ) 
	 {
	    zurueck[0] = '1';
		sepauft[0] = '1';	/* auftrag nicht anhängen */
	 }
	 else if ( d->KULKAH[0] == '4' ) 
	 {
		rr0800[0] = '1';
	 }
	 else if ( d->KULKAH[0] == '5' ) 
	 {
	    rrab[0] = '1';
	 }
	 else if ( d->KULKAH[0] == '6' ) 
	 {
	    rrab[0] = '1';
	    eilab[0] = '1';
	 }
	 else if ( d->KULKAH[0] == '7' ) 
	 {
	    trennalpha[0] = '1';
	 }
	 else if ( d->KULKAH[0] == '8' ) 
	 {
	    trennalphaurr[0] = '1';
	 }
	 else if ( d->KULKAH[0] == '9' ) 
	 {
	    trenndefekt[0] = '1';
	 }
	 if ( d->KULKZDARU[0] == '1' )
	 {
		 sa06meld[0] = '1';
		 sa04meld[0] = '0';
	 }
	 else if ( d->KULKZDARU[0] == '2' )
	 {
		 sa06meld[0] = '0';
		 sa04meld[0] = '1';
	 }
	 else if ( d->KULKZDARU[0] == '3' )
	 {
		 sa06meld[0] = '1';
		 sa04meld[0] = '1';
	 }
	 else
	 {
		 sa06meld[0] = '0';
		 sa04meld[0] = '0';
	 }
    if ( d->KULWAFO[0] != 'J' &&  d->KULWAFO[0] != '1' )
	 d->KULWAFO[0] = '0';
	 else
	 d->KULWAFO[0] = '1';
    if ( d->KULPIN[0] != 'J' &&  d->KULPIN[0] != '1' )
	 d->KULPIN[0] = '0';
	 else
	 d->KULPIN[0] = '1';
    if ( d->KULADG[0] != 'J' &&  d->KULADG[0] != '1' )
	 d->KULADG[0] = '0';
	 else
	 d->KULADG[0] = '1';
    if ( d->KULDRBETA[0] == 'D')
	 d->KULDRBETA[0] = '1';
    else if ( d->KULDRBETA[0] != 'A')
	 d->KULDRBETA[0] = '2';
	 else
	 d->KULDRBETA[0] = '0';
    if ( d->KULFAX400[0] != 'J' &&  d->KULFAX400[0] != '1' )
	 d->KULFAX400[0] = '0';
	 else
	 d->KULFAX400[0] = '1';
    if ( d->KULAESPER[0] != 'J' &&  d->KULAESPER[0] != '1' )
	 d->KULAESPER[0] = '0';
	 else
	 d->KULAESPER[0] = '1';
    if ( d->KULLOE[0] == 'J' ||  d->KULLOE[0] == '1' ) /* mit LOEKZ als gesperrt übernehmen */
	 d->KULAESPER[0] = '1';
	if(haus == 49)	/* in prewhole FR immer aktiv */
	{
		ABSAG[0] = d->KULAESPER[0];
		ABSAG[1] = '\0';
		SPERRKZ[0] = '0';
	    if ( d->KULLOE[0] == 'J' ||  d->KULLOE[0] == '1' ) /* mit LOEKZ als gesperrt übernehmen */
			SPERRKZ[0] = '1';
		SPERRKZ[1] = '\0';
	}
	else
	{
		SPERRKZ[0] = d->KULAESPER[0];
		SPERRKZ[1] = '\0';
	}

    if ( d->KULBLPV[0] != 'J' &&  d->KULBLPV[0] != '1' )
	 d->KULBLPV[0] = '0';
	 else
	 d->KULBLPV[0] = '1';
    if ( d->KULDRTIER[0] != 'J' &&  d->KULDRTIER[0] != '1' )
	 d->KULDRTIER[0] = '0';
	 else
	 d->KULDRTIER[0] = '1';
    if ( d->KULDRKAUF[0] != 'J' &&  d->KULDRKAUF[0] != '1' )
	 d->KULDRKAUF[0] = '0';
	 else
	 d->KULDRKAUF[0] = '1';
    if ( d->KULDRNRGD[0] != 'J' &&  d->KULDRNRGD[0] != '1' )
	 d->KULDRNRGD[0] = '0';
	 else
	 d->KULDRNRGD[0] = '1';
    if ( d->KULMRAB[0] != 'J' &&  d->KULMRAB[0] != '1' )
	 d->KULMRAB[0] = '0';
	 else
	 d->KULMRAB[0] = '1';
    if ( d->KULDRUMHO[0] != 'J' &&  d->KULDRUMHO[0] != '1' )
	 d->KULDRUMHO[0] = '0';
	 else
	 d->KULDRUMHO[0] = '1';
    if ( d->KULPRODSA[0] != 'J' &&   d->KULPRODSA[0] != '1' )
	{
		d->KULPRODSA[0] = '0';
	}
	else
		d->KULPRODSA[0] = '1';
    if ( d->KULAUFZVS[0] != 'J' &&   d->KULAUFZVS[0] != '1' )
	{
		d->KULAUFZVS[0] = '0';
	}
	else
		d->KULAUFZVS[0] = '1';
    if ( d->KULELAC[0] != 'J' &&   d->KULELAC[0] != '1' )
	{
		d->KULELAC[0] = '0';
	}
	else
		d->KULELAC[0] = '1';
    if ( d->KULDRBRAB[0] != 'J' &&   d->KULDRBRAB[0] != '1' )
		SKDLISTE5[0] = '0';
	else
		SKDLISTE5[0] = '1';
    if ( d->KULBLPDISK[0] == 'D')
		SKDINVOICEDISC[0] = '1';
	else
		SKDINVOICEDISC[0] = '0';
    if ( d->KULBLPDISK[0] == 'E')
		SKDINVOICEEMAIL[0] = '1';
	else
		SKDINVOICEEMAIL[0] = '0';

    if ( d->KULDFKZ[0] != 'J' &&   d->KULDFKZ[0] != '1' )
	{
		d->KULDFKZ[0] = '0';
	}
	else
		d->KULDFKZ[0] = '1';

    if ( d->KULSUBST[0] != 'J' &&   d->KULSUBST[0] != '1' )
	{
		d->KULSUBST[0] = '1';
	}
	else
		d->KULSUBST[0] = '0';

    if ( d->KULKNTG[0] != 'J' &&   d->KULKNTG[0] != '1' )
	{
		d->KULKNTG[0] = '0';
	}
	else
		d->KULKNTG[0] = '1';

    if ( d->KULDEFBER[0] != 'J' &&   d->KULDEFBER[0] != '1' )
	{
		d->KULDEFBER[0] = '0';
	}
	else
		d->KULDEFBER[0] = '1';

	if (d->KULGTRLS[0] != 'J' &&   d->KULGTRLS[0] != '1')
	{
		sskdfmd = 0;
	}
	else
	{
		sskdfmd = 1;
	}

	if(d->KULVFIL[0] < '0' || d->KULVFIL[0] > '9') d->KULVFIL[0] = '0'; 
	if(d->KULVFIL[1] < '0' || d->KULVFIL[1] > '9') d->KULVFIL[1] = '0'; 
	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,d->KULFIL1);
	if(othervz == NO)
	{
		if(strncmp(d->KULVFIL,"00",L_DKKUL_KULVFIL)
			&& strncmp(d->KULVFIL,vertriebsfiliale,L_DKKUL_KULVFIL))
		{
			if(!strncmp(d->KULVFIL,"08",L_DKKUL_KULVFIL)
				&& !strncmp(vertriebsfiliale,"09",L_DKKUL_KULVFIL))
			{
			}
			else
			{
				SPERRKZ[0] = '1';
			}
		}
	}

	if(Schweiz == YES)
	{
		EXEC SQL EXECUTE upd_kundeschalterch USING :d->KULIDF,
                                                  :d->KULFACH,        
                                                  :d->KULKUFA,        
                                                  :d->KULNRRE,        
                                                  :d->KULNEAK,        
                                                  ' ',            
                                                  :d->KULNALI,        
                                                  :ABSAG,       
                                                  :d->KULDSDAF,       
                                                  :d->KULAES,         
                                                  :d->KULMEER,        
                                                  :d->KULAWDEF,       
                                                  :d->KULDRKOMMI,     
                                                  :d->KULAUFZU,       
                                                  :d->KULMWST,        
                                                  :d->KULSTKUN,       
                                                  :d->KULVALSP,       
                                                  :d->KULSPKT1,       
                                                  :d->KULSPKT2, 
                                                  :d->KULSPKT3, 
                                                  :d->KULSPKT4, 
                                                  :d->KULSPKT5, 
                                                  :d->KULVBSG,  
                                                  '0',  
                                                  :d->KULKRK,
                                                  :d->KULKZEILS,
												  ' ',
                                                  :d->KULVIP,
												  :d->KULAS,
												  :musskopf,
												  :sepauft,
												  :zurueck,
												  :sa06meld,
												  :sa04meld,
												  '1',
                                                  :d->KULRIS,
												  :d->KULWAFO,
												  :d->KULPIN,
												  :d->KULADG,
												  :d->KULDRBETA,
												  :d->KULFAX400,
												  :SPERRKZ,
												  :d->KULBLPV,
												  :d->KULDRTIER,
												  :d->KULDRKAUF,
												  :d->KULDRNRGD,
												  :d->KULMRAB,
												  :d->KULDRUMHO,
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  :SKDBLICKPUNKTABO,
												  :SKDBUECHER,
												  :SKDVERTRIEBBINDUNG,
												  :SKDPOOL,
												  :SKDBOUHON,
												  :SKDROCHE,
												  :SKDVICHY,
												  :SKDVBFILIALEMELD,
												  :rrab,
												  :eilab,
												  :trennalpha,
												  :rr0800,
												  :trennalphaurr,
												  :SKDORIGINALMELD,
												  '0',
                                                  :d->KULSPKT4, /*entfremdet für Mehrfachbestellungen Schweiz */
                                                  :d->KULSPKT3, /*entfremdet für OMG-Rabatt Schweiz */
//												  :SKDKEINNL,
												  :d->KULNLNOTA,
												  :trenndefekt,
												  :d->KULPRODSA,
												  :d->KULAUFZVS,
												  :d->KULAUFEINPR,
												  :HALFMARGIN,
												  :DISCOUNTEXCEPT,
												  :SKDLISTE5,
												  :SKDINVOICEDISC,
												  :SKDINVOICEEMAIL,
												  :SKDNOEXPIRYINFO,
												  :d->KULELAC,
												  :d->KULDFKZ,
												  :d->KULSUBST,
												  :d->KULDEFMSV3,
												  :d->KULKNTG,
												  :d->KULDEFBER,
												  :d->KULANHBZ,
												  :d->KULMAILBZS,
									 			  :d->KULMAILCDB,
												  :d->KULFAXBZS,
												  :d->KULFAXCDB,
												  :sskdfmd,
												  :vertriebsfiliale,
												  :d->KULIDF
												  ;

		ERROR_MSG3( "upd kundeschalter schweiz:",d->KULIDF )
	}
	else
	{
		EXEC SQL EXECUTE upd_kundeschalter USING :d->KULIDF,
                                                  :d->KULFACH,        
                                                  :d->KULKUFA,        
                                                  :d->KULNRRE,        
                                                  :d->KULNEAK,        
                                                  ' ',            
                                                  :d->KULNALI,        
                                                  :ABSAG,       
                                                  :d->KULDSDAF,       
                                                  :d->KULAES,         
                                                  :d->KULMEER,        
                                                  :d->KULAWDEF,       
                                                  :d->KULDRKOMMI,     
                                                  :d->KULAUFZU,       
                                                  :d->KULMWST,        
                                                  :d->KULSTKUN,       
                                                  :d->KULVALSP,       
                                                  :d->KULSPKT1,       
                                                  :d->KULSPKT2, 
                                                  :d->KULSPKT3, 
                                                  :d->KULSPKT4, 
                                                  :d->KULSPKT5, 
                                                  :d->KULVBSG,  
                                                  '0',  
                                                  :d->KULKRK,
                                                  :d->KULKZEILS,
												  ' ',
                                                  :d->KULVIP,
												  :d->KULAS,
												  :musskopf,
												  :sepauft,
												  :zurueck,
												  :sa06meld,
												  :sa04meld,
												  '1',
                                                  :d->KULRIS,
												  :d->KULWAFO,
												  :d->KULPIN,
												  :d->KULADG,
												  :d->KULDRBETA,
												  :d->KULFAX400,
												  :SPERRKZ,
												  :d->KULBLPV,
												  :d->KULDRTIER,
												  :d->KULDRKAUF,
												  :d->KULDRNRGD,
												  :d->KULMRAB,
												  :d->KULDRUMHO,
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  :SKDBLICKPUNKTABO,
												  :SKDBUECHER,
												  :SKDVERTRIEBBINDUNG,
												  :SKDPOOL,
												  :SKDBOUHON,
												  :SKDROCHE,
												  :SKDVICHY,
												  :SKDVBFILIALEMELD,	
												  :rrab,
												  :eilab,
												  :trennalpha,
												  :rr0800,
												  :trennalphaurr,
												  :SKDORIGINALMELD,
												  '0',
												  :trenndefekt,
												  :d->KULPRODSA,
												  :d->KULAUFZVS,
												  :d->KULAUFEINPR,
												  :HALFMARGIN,
												  :DISCOUNTEXCEPT,
												  :SKDLISTE5,
												  :SKDINVOICEDISC,
												  :SKDINVOICEEMAIL,
												  :SKDNOEXPIRYINFO,
												  :d->KULELAC,
												  :d->KULDFKZ,
												  :d->KULSUBST,
												  :d->KULDEFMSV3,
												  :d->KULKNTG,
												  :d->KULDEFBER,
												  :d->KULANHBZ,
												  :d->KULMAILBZS,
												  :d->KULMAILCDB,
												  :d->KULFAXBZS,
												  :d->KULFAXCDB,
												  :sskdfmd,
												  :vertriebsfiliale,
												  :d->KULIDF
												  ;
		ERROR_MSG3( "upd kundeschalter:",d->KULIDF )
	}
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		if(Schweiz == YES)
		{
			exec sql insert into kundeschalter (KUNDESCHALTER_LISTE
												,skdmehrfachbestell
												,skdomgkunde
												,skdkeinnl
												,skdtrenndefekt
												,skdparternariat
												,skdbaauftrag
												,skdwatchorder
												,skdhalfmargin
												,skddiscountexcept
												,SKDLISTE5
												,SKDINVOICEDISC
												,SKDINVOICEEMAIL
												,SKDNOEXPIRYINFO
												,MEDPROD_ABG_VERORD
												,skdnoclosedefvb
												,skdnosub
												,skdnoshortreport
												,skdgiveprodquota
												,skdavoiddefectclearing
												,noorderconsaftermot
												,skdmailinvoice
												,skdmailbatchchangeadvice
												,skdfaxinvoice
												,skdfaxbatchchangeadvice
												,skdfmd
				)
				values (						:d->KULIDF,
                                                  :d->KULFACH,        
                                                  :d->KULKUFA,        
                                                  :d->KULNRRE,        
                                                  :d->KULNEAK,        
                                                  ' ',            
                                                  :d->KULNALI,        
                                                  :ABSAG,       
                                                  :d->KULDSDAF,       
                                                  :d->KULAES,         
                                                  :d->KULMEER,        
                                                  :d->KULAWDEF,       
                                                  :d->KULDRKOMMI,     
                                                  :d->KULAUFZU,       
                                                  :d->KULMWST,        
                                                  :d->KULSTKUN,       
                                                  :d->KULVALSP,       
                                                  :d->KULSPKT1,       
                                                  :d->KULSPKT2, 
                                                  :d->KULSPKT3, 
                                                  :d->KULSPKT4, 
                                                  :d->KULSPKT5, 
                                                  :d->KULVBSG,
												  '0',
                                                  :d->KULKRK,
                                                  :d->KULKZEILS,
												  ' ',
                                                  :d->KULVIP,
												  :d->KULAS,
												  :musskopf,
												  :sepauft,
												  :zurueck,
												  :sa06meld,
												  :sa04meld,
												  '1',
                                                  :d->KULRIS,
												  :d->KULWAFO,
												  :d->KULPIN,
												  :d->KULADG,
												  :d->KULDRBETA,
												  :d->KULFAX400,
												  :SPERRKZ,
												  :d->KULBLPV,
												  :d->KULDRTIER,
												  :d->KULDRKAUF,
												  :d->KULDRNRGD,
												  :d->KULMRAB,
												  :d->KULDRUMHO,
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  :SKDBLICKPUNKTABO,
												  :SKDBUECHER,
												  :SKDVERTRIEBBINDUNG,
												  :SKDPOOL,
												  :SKDBOUHON,
												  :SKDROCHE,
												  :SKDVICHY,
												  :SKDVBFILIALEMELD,
												  :rrab,
												  :eilab,
												  :trennalpha,
												  :rr0800,
												  :trennalphaurr,
												  :SKDORIGINALMELD,
												  '0',
                                                  :d->KULSPKT4, /*entfremdet für Mehrfachbestellungen Schweiz */
                                                  :d->KULSPKT3, /*entfremdet für OMG-Rabatt Schweiz */
//												  :SKDKEINNL,
												  :d->KULNLNOTA,
												  :trenndefekt,
												  :d->KULPRODSA,
												  :d->KULAUFZVS,
												  :d->KULAUFEINPR,
												  :HALFMARGIN,
												  :DISCOUNTEXCEPT,
												  :SKDLISTE5,
												  :SKDINVOICEDISC,
												  :SKDINVOICEEMAIL,
												  :SKDNOEXPIRYINFO,
												  :d->KULELAC,
												  :d->KULDFKZ,
												  :d->KULSUBST,
												  :d->KULDEFMSV3,
												  :d->KULKNTG,
												  :d->KULDEFBER,
												  :d->KULANHBZ,
												  :d->KULMAILBZS,
												  :d->KULMAILCDB,
												  :d->KULFAXBZS,
												  :d->KULFAXCDB,
												  :sskdfmd
												);
			ERROR_MSG3( "insert kundeschalter schweiz:",d->KULIDF )
		}
		else
		{
			exec sql insert into kundeschalter (KUNDESCHALTER_LISTE
												,skdtrenndefekt
												,skdparternariat
												,skdbaauftrag
												,skdwatchorder
												,skdhalfmargin
												,skddiscountexcept
												,SKDLISTE5
												,SKDINVOICEDISC
												,SKDINVOICEEMAIL
												,SKDNOEXPIRYINFO
												,MEDPROD_ABG_VERORD
												,skdnoclosedefvb
												,skdnosub
												,skdnoshortreport
												,skdgiveprodquota
												,skdavoiddefectclearing
												,noorderconsaftermot
												,skdmailinvoice
												,skdmailbatchchangeadvice
												,skdfaxinvoice
												,skdfaxbatchchangeadvice
												,skdfmd
			)
				values (						:d->KULIDF,
                                                :d->KULFACH,        
                                                :d->KULKUFA,        
                                                :d->KULNRRE,        
                                                :d->KULNEAK,        
                                                ' ',            
                                                :d->KULNALI,        
                                                :ABSAG,       
                                                :d->KULDSDAF,       
                                                :d->KULAES,         
                                                :d->KULMEER,        
                                                :d->KULAWDEF,       
                                                :d->KULDRKOMMI,     
                                                :d->KULAUFZU,       
                                                :d->KULMWST,        
                                                :d->KULSTKUN,       
                                                :d->KULVALSP,       
                                                :d->KULSPKT1,       
                                                :d->KULSPKT2, 
                                                :d->KULSPKT3, 
                                                :d->KULSPKT4, 
                                                :d->KULSPKT5, 
                                                :d->KULVBSG,
												'0',
                                                :d->KULKRK,
                                                :d->KULKZEILS,
												' ',
                                                :d->KULVIP,
												:d->KULAS,
												:musskopf,
												:sepauft,
												:zurueck,
												:sa06meld,
												:sa04meld,
												'1',
                                                :d->KULRIS,
												:d->KULWAFO,
												:d->KULPIN,
												:d->KULADG,
												:d->KULDRBETA,
												:d->KULFAX400,
												:SPERRKZ,
												:d->KULBLPV,
												:d->KULDRTIER,
												:d->KULDRKAUF,
												:d->KULDRNRGD,
												:d->KULMRAB,
												:d->KULDRUMHO,
			                                    :vertriebsfiliale,
												:d->KULIDF,
												:datum,
												:dbzeit,
												'1',
												'I',
												:SKDBLICKPUNKTABO,
												:SKDBUECHER,
												:SKDVERTRIEBBINDUNG,
												:SKDPOOL,
												:SKDBOUHON,
												:SKDROCHE,
												:SKDVICHY,
												:SKDVBFILIALEMELD,
												:rrab,
												:eilab,
												:trennalpha,
												:rr0800,
												:trennalphaurr,
												:SKDORIGINALMELD,
												'0',
												:trenndefekt,
												:d->KULPRODSA,
												:d->KULAUFZVS,
												:d->KULAUFEINPR,
												:HALFMARGIN,
												:DISCOUNTEXCEPT,
												:SKDLISTE5,
												:SKDINVOICEDISC,
												:SKDINVOICEEMAIL,
												:SKDNOEXPIRYINFO,
												:d->KULELAC,
												:d->KULDFKZ,
												:d->KULSUBST,
												:d->KULDEFMSV3,
												:d->KULKNTG,
												:d->KULDEFBER,
												:d->KULANHBZ,
												:d->KULMAILBZS,
												:d->KULMAILCDB,
												:d->KULFAXBZS,
												:d->KULFAXCDB,
												:sskdfmd
												);
			ERROR_MSG3( "insert kundeschalter:",d->KULIDF )
		}
	}
	return OK;
}


int LadeKundeKondi( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadeKundeKondi";
	char huelse[20];

	exec sql begin declare section;
	struct S_DKKUL *d;
	char vertriebsfiliale[3];
	short stagautovaluta;
	short svalutatagemax;
    exec sql end declare section;

	d = kun;

	sprintf(huelse,"%*.*s",LS_DKKUL_KULVTAG,LS_DKKUL_KULVTAG,d->KULVTAG);
	if(Kroatien)
	{
		stagautovaluta = 0;
		svalutatagemax = atoi(huelse);
	}
	else
	{
		stagautovaluta = atoi(huelse);
		svalutatagemax = 0;
	}

	if(d->KULVFIL[0] < '0' || d->KULVFIL[0] > '9') d->KULVFIL[0] = '0'; 
	if(d->KULVFIL[1] < '0' || d->KULVFIL[1] > '9') d->KULVFIL[1] = '0'; 
	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,d->KULFIL1);
    
	EXEC SQL EXECUTE upd_kundekondi USING :d->KULIDF,
                                               :d->KULRUND,    
                                               :d->KULMENG,    
                                               :d->KULNRMG,    
                                               :d->KULRR04,
											   '1',
			                                   :vertriebsfiliale,
											   :d->KULIDF,
											   :datum,
											   :dbzeit,
												'1',
												'I',
											  :stagautovaluta,
											  :svalutatagemax,
                                               :d->KULAUSZ,
		                                      :vertriebsfiliale,
											  :d->KULIDF
											  ;
	ERROR_MSG3( "upd kundekondi:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
	    exec sql insert into kundekondi (KUNDEKONDI_LISTE,tagautovaluta,valutatagemax,paymentinterval)
										values ( :d->KULIDF,
                                               :d->KULRUND,    
                                               :d->KULMENG,    
                                               :d->KULNRMG,    
                                               :d->KULRR04,
											   '1',
		                                      :vertriebsfiliale,
											  :d->KULIDF,
											  :datum,
											  :dbzeit,
											  '1',
											  'I',
											  :stagautovaluta,
											  :svalutatagemax,
                                               :d->KULAUSZ
											   );   

		ERROR_MSG3( "insert kundekondi:",d->KULIDF )
	}
	return OK;
}

int LadeKdBetriebsEnde( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadeKdBetriebsEnde";

	char huelse[20];
	int rc;

	exec sql begin declare section;
	struct S_DKKUL *d;
	long KULBEMO1;
	long KULBEMO2;
	long KULBEMO3;
	long KULBEMO4;
	long KULBEMO5;
	long KULBEMO6;
	long KULBEMO7;
	long KULENMO1;
	long KULENMO2;
	long KULENMO3;
	long KULENMO4;
	long KULENMO5;
	long KULENMO6;
	long KULENMO7;
	long KULBEAB1;
	long KULBEAB2;
	long KULBEAB3;
	long KULBEAB4;
	long KULBEAB5;
	long KULBEAB6;
	long KULBEAB7;
	long KULENAB1;
	long KULENAB2;
	long KULENAB3;
	long KULENAB4;
	long KULENAB5;
	long KULENAB6;
	long KULENAB7;
	char vertriebsfiliale[3];
    exec sql end declare section;

	d = kun;
/*	if((rc = SetNotUpdatedkdbetriebsende( error_msg )) != 0) return rc;
*/
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO1,LS_DKKUL_KULBEMO1,d->KULBEMO1);    
    KULBEMO1 = atol(huelse) * 100;
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO1,LS_DKKUL_KULENMO1,d->KULENMO1);    
    KULENMO1 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB1,LS_DKKUL_KULBEAB1,d->KULBEAB1);    
    KULBEAB1 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB1,LS_DKKUL_KULENAB1,d->KULENAB1);    
    KULENAB1 = atol(huelse) * 100;     
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO2,LS_DKKUL_KULBEMO2,d->KULBEMO2);    
    KULBEMO2 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO2,LS_DKKUL_KULENMO2,d->KULENMO2);    
    KULENMO2 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB2,LS_DKKUL_KULBEAB2,d->KULBEAB2);    
    KULBEAB2 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB2,LS_DKKUL_KULENAB2,d->KULENAB2);    
    KULENAB2 = atol(huelse) * 100;     
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO3,LS_DKKUL_KULBEMO3,d->KULBEMO3);    
    KULBEMO3 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO3,LS_DKKUL_KULENMO3,d->KULENMO3);    
    KULENMO3 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB3,LS_DKKUL_KULBEAB3,d->KULBEAB3);    
    KULBEAB3 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB3,LS_DKKUL_KULENAB3,d->KULENAB3);    
    KULENAB3 = atol(huelse) * 100;     
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO4,LS_DKKUL_KULBEMO4,d->KULBEMO4);    
    KULBEMO4 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO4,LS_DKKUL_KULENMO4,d->KULENMO4);    
    KULENMO4 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB4,LS_DKKUL_KULBEAB4,d->KULBEAB4);    
    KULBEAB4 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB4,LS_DKKUL_KULENAB4,d->KULENAB4);    
    KULENAB4 = atol(huelse) * 100;     
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO5,LS_DKKUL_KULBEMO5,d->KULBEMO5);    
    KULBEMO5 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO5,LS_DKKUL_KULENMO5,d->KULENMO5);    
    KULENMO5 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB5,LS_DKKUL_KULBEAB5,d->KULBEAB5);    
    KULBEAB5 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB5,LS_DKKUL_KULENAB5,d->KULENAB5);    
    KULENAB5 = atol(huelse) * 100;     
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO6,LS_DKKUL_KULBEMO6,d->KULBEMO6);    
    KULBEMO6 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO6,LS_DKKUL_KULENMO6,d->KULENMO6);    
    KULENMO6 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB6,LS_DKKUL_KULBEAB6,d->KULBEAB6);    
    KULBEAB6 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB6,LS_DKKUL_KULENAB6,d->KULENAB6);    
    KULENAB6 = atol(huelse) * 100;     
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO7,LS_DKKUL_KULBEMO7,d->KULBEMO7);    
    KULBEMO7 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO7,LS_DKKUL_KULENMO7,d->KULENMO7);    
    KULENMO7 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB7,LS_DKKUL_KULBEAB7,d->KULBEAB7);    
    KULBEAB7 = atol(huelse) * 100;    
 	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB7,LS_DKKUL_KULENAB7,d->KULENAB7);    
    KULENAB7 = atol(huelse) * 100;     

	if(d->KULVFIL[0] < '0' || d->KULVFIL[0] > '9') d->KULVFIL[0] = '0'; 
	if(d->KULVFIL[1] < '0' || d->KULVFIL[1] > '9') d->KULVFIL[1] = '0'; 
	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,d->KULFIL1);
    
	EXEC SQL EXECUTE upd_kdbetriebsende USING :d->KULIDF,
                                                   'MO',    
                                                   :KULBEMO1,    
                                                   :KULENMO1,    
                                                   :KULBEAB1,    
                                                   :KULENAB1,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												   '1',
		                                      :vertriebsfiliale,
											  :d->KULIDF,
                                                   '1';    
	ERROR_MSG3( "upd kdbetriebsende1:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
	    exec sql insert into kdbetriebsende (KDBETRIEBSENDE_LISTE) values ( :d->KULIDF,
                                                   'MO',    
                                                   :KULBEMO1,    
                                                   :KULENMO1,    
                                                   :KULBEAB1,    
                                                   :KULENAB1,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '1'
												 );
		ERROR_MSG3( "insert kdbetriebsende1:",d->KULIDF )
	}
	
	EXEC SQL EXECUTE upd_kdbetriebsende USING :d->KULIDF,
                                                   'DI',    
                                                   :KULBEMO2,    
                                                   :KULENMO2,    
                                                   :KULBEAB2,    
                                                   :KULENAB2,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '2',
		                                      :vertriebsfiliale,
											  :d->KULIDF,
                                                   '2';    
	ERROR_MSG3( "upd kdbetriebsende2:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
	    exec sql insert into kdbetriebsende (KDBETRIEBSENDE_LISTE) values ( :d->KULIDF,
                                                   'DI',    
                                                   :KULBEMO2,    
                                                   :KULENMO2,    
                                                   :KULBEAB2,    
                                                   :KULENAB2,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '2'
												 );
		ERROR_MSG3( "insert kdbetriebsende2:",d->KULIDF )
	}
	
	EXEC SQL EXECUTE upd_kdbetriebsende USING :d->KULIDF,
                                                   'MI',    
                                                   :KULBEMO3,    
                                                   :KULENMO3,    
                                                   :KULBEAB3,    
                                                   :KULENAB3,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '3',
			                                      :vertriebsfiliale,
												   :d->KULIDF,
                                                   '3';    
	ERROR_MSG3( "upd kdbetriebsende3:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
	    exec sql insert into kdbetriebsende (KDBETRIEBSENDE_LISTE) values ( :d->KULIDF,
                                                   'MI',    
                                                   :KULBEMO3,    
                                                   :KULENMO3,    
                                                   :KULBEAB3,    
                                                   :KULENAB3,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '3'
												 );
		ERROR_MSG3( "insert kdbetriebsende3:",d->KULIDF )
	}
	
	EXEC SQL EXECUTE upd_kdbetriebsende USING :d->KULIDF,
                                                   'DO',    
                                                   :KULBEMO4,    
                                                   :KULENMO4,    
                                                   :KULBEAB4,    
                                                   :KULENAB4,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '4',
			                                      :vertriebsfiliale,
												   :d->KULIDF,
                                                   '4';    
	ERROR_MSG3( "upd kdbetriebsende4:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
	    exec sql insert into kdbetriebsende (KDBETRIEBSENDE_LISTE) values ( :d->KULIDF,
                                                   'DO',    
                                                   :KULBEMO4,    
                                                   :KULENMO4,    
                                                   :KULBEAB4,    
                                                   :KULENAB4,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '4'
												 );
		ERROR_MSG3( "insert kdbetriebsende4:",d->KULIDF )
	}
	
	EXEC SQL EXECUTE upd_kdbetriebsende USING :d->KULIDF,
                                                   'FR',    
                                                   :KULBEMO5,    
                                                   :KULENMO5,    
                                                   :KULBEAB5,    
                                                   :KULENAB5,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '5',
			                                      :vertriebsfiliale,
												   :d->KULIDF,
                                                   '5';    
	ERROR_MSG3( "upd kdbetriebsende5:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
	    exec sql insert into kdbetriebsende (KDBETRIEBSENDE_LISTE) values ( :d->KULIDF,
                                                   'FR',    
                                                   :KULBEMO5,    
                                                   :KULENMO5,    
                                                   :KULBEAB5,    
                                                   :KULENAB5,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '5'
												 );
		ERROR_MSG3( "insert kdbetriebsende5:",d->KULIDF )
	}
	
	EXEC SQL EXECUTE upd_kdbetriebsende USING :d->KULIDF,
                                                   'SA',    
                                                   :KULBEMO6,    
                                                   :KULENMO6,    
                                                   :KULBEAB6,    
                                                   :KULENAB6,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '6',
			                                      :vertriebsfiliale,
												   :d->KULIDF,
                                                   '6';    
	ERROR_MSG3( "upd kdbetriebsende6:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
	    exec sql insert into kdbetriebsende (KDBETRIEBSENDE_LISTE) values ( :d->KULIDF,
                                                   'SA',    
                                                   :KULBEMO6,    
                                                   :KULENMO6,    
                                                   :KULBEAB6,    
                                                   :KULENAB6,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '6'
												 );
		ERROR_MSG3( "insert kdbetriebsende6:",d->KULIDF )
	}
	
	EXEC SQL EXECUTE upd_kdbetriebsende USING :d->KULIDF,
                                                   'SO',    
                                                   :KULBEMO7,    
                                                   :KULENMO7,    
                                                   :KULBEAB7,    
                                                   :KULENAB7,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '0',
			                                      :vertriebsfiliale,
												   :d->KULIDF,
                                                   '0';    
	ERROR_MSG3( "upd kdbetriebsende7:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
	    exec sql insert into kdbetriebsende (KDBETRIEBSENDE_LISTE) values ( :d->KULIDF,
                                                   'SO',    
                                                   :KULBEMO7,    
                                                   :KULENMO7,    
                                                   :KULBEAB7,    
                                                   :KULENAB7,
												   '1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
												  '0'
												 );
		ERROR_MSG3( "insert kdbetriebsende7:",d->KULIDF )
	}
/*	if((rc = DelNotUpdatedkdbetriebsende( error_msg )) != 0) return rc;
*/	
	return OK;
}




int LadeKdKonditionGruppe( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadeKonditionGruppe";
	int rc;

	exec sql begin declare section;
	struct S_DKKUL *d;
	char vertriebsfiliale[3];
    exec sql end declare section;

	d = kun;

/*	if((rc = SetNotUpdatedkdkonditiongruppe( error_msg )) != 0) return rc;
*/
	if(d->KULVFIL[0] < '0' || d->KULVFIL[0] > '9') d->KULVFIL[0] = '0'; 
	if(d->KULVFIL[1] < '0' || d->KULVFIL[1] > '9') d->KULVFIL[1] = '0'; 
	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,d->KULFIL1);
    
	EXEC SQL EXECUTE upd_kdkondgruppe USING :d->KULIDF,
												'1',
												'1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
			                                      :vertriebsfiliale,
												:d->KULIDF,												
                                                '1';
	ERROR_MSG3( "upd kdkonditiongruppe1:",d->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
	    exec sql insert into kdkonditiongruppe (KDKONDITIONGRUPPE_LISTE) values ( :d->KULIDF,
												'1',
												'1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I'
												);
		ERROR_MSG3( "inskdkonditiongruppe1:",d->KULIDF )
	}
	
	if ( d->KULSPKT3[0] == 'J' || d->KULSPKT3[0] == '1')
	{
		EXEC SQL EXECUTE upd_kdkondgruppe USING :d->KULIDF,
												'2',
												'1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
			                                      :vertriebsfiliale,
												:d->KULIDF,												
                                                '2';
		ERROR_MSG3( "upd kdkonditiongruppe2:",d->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
		    exec sql insert into kdkonditiongruppe (KDKONDITIONGRUPPE_LISTE) values ( :d->KULIDF,
												'2',
												'1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I'
												);
			ERROR_MSG3( "inskdkonditiongruppe2:",d->KULIDF )
		}
	}

	if ( d->KULSPKT5[0] == 'J' || d->KULSPKT5[0] == '1')
	{
		EXEC SQL EXECUTE upd_kdkondgruppe USING :d->KULIDF,
												'3',
												'1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I',
			                                      :vertriebsfiliale,
												:d->KULIDF,												
                                                '3';
		ERROR_MSG3( "upd kdkonditiongruppe3:",d->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
		{
		    exec sql insert into kdkonditiongruppe (KDKONDITIONGRUPPE_LISTE) values ( :d->KULIDF,
												'3',
												'1',
			                                      :vertriebsfiliale,
												  :d->KULIDF,
												  :datum,
												  :dbzeit,
												  '1',
												  'I'
												);
			ERROR_MSG3( "inskdkonditiongruppe3:",d->KULIDF )
		}
	}
/*	if((rc = DelNotUpdatedkdkonditiongruppe( error_msg )) != 0) return rc;
*/
	return OK;
}

int EtArtKlasse1( struct S_DKKUL *art )
{
	int bitleiste = 0;
	if(art->KULGIFT1[0] == 'J')  bitleiste += 32768;
	if(art->KULGIFT2[0] == 'J')  bitleiste += 16384;
	if(art->KULGIFT3[0] == 'J')  bitleiste += 8192;
	if(art->KULREZ[0] == 'J')    bitleiste += 4096;
	if(art->KULAPO[0] == 'J')    bitleiste += 2048;
	if(art->KULTAX[0] == 'J')    bitleiste += 1024;
	if(art->KULOPI[0] == 'J')    bitleiste += 512;
	if(art->KULTIER[0] == 'J')   bitleiste += 256;
	if(art->KULVBED[0] == 'J')   bitleiste += 128;
	if(art->KULVBA[0] == 'J')    bitleiste += 64;
	if(art->KULVBB[0] == 'J')    bitleiste += 32;
	if(art->KULVBC[0] == 'J')	 bitleiste += 16;
	if(art->KULVB1[0] == 'J')    bitleiste += 8;
	if(art->KULVB2[0] == 'J')    bitleiste += 4;
	if(art->KULVB3[0] == 'J')    bitleiste += 2;
	if(art->KULVB4[0] == 'J')    bitleiste += 1;
	
	return bitleiste;
}		  

int EtKdMerkmal1( struct S_DKKUL *art )
{
	int bitleiste = 0;
	
	if(art->KULGIFT1[0] == 'J') bitleiste += 32768;
	if(art->KULGIFT2[0] == 'J') bitleiste += 16384;
	if(art->KULGIFT3[0] == 'J') bitleiste += 8192;
	if(art->KULREZ[0] == 'J')   bitleiste += 4096;
	if(art->KULAPO[0] == 'J')   bitleiste += 2048;
	if(art->KULTAX[0] == 'J')   bitleiste += 1024;
	if(art->KULOPI[0] == 'J')   bitleiste += 512;
	if(art->KULTIER[0] == 'J')  bitleiste += 256;
	if(art->KULVBED[0] == 'J')  bitleiste += 128;
	if(art->KULVBA[0] == 'J')   bitleiste += 64;
	if(art->KULVBB[0] == 'J')   bitleiste += 32;
	if(art->KULVBC[0] == 'J')   bitleiste += 16;
	if(art->KULVB1[0] == 'J')   bitleiste += 8;
	if(art->KULVB2[0] == 'J')   bitleiste += 4;
	if(art->KULVB3[0] == 'J')   bitleiste += 2;
	if(art->KULVB4[0] == 'J')   bitleiste += 1;

	return bitleiste;
}

int EtKdMerkmal2( struct S_DKKUL *art )
{
	int bitleiste = 0;
	
	if(art->KULFACH[0] == 'J')  bitleiste += 32768;
	if(art->KULKUFA[0] == 'J')  bitleiste += 16384;
	if(art->KULNRRE[0] == 'J')  bitleiste += 8192;
	if(art->KULNEAK[0] == 'J')  bitleiste += 4096;
	if(art->KULBLP[0] == 'J')   bitleiste += 2048;
	if(art->KULNALI[0] == 'J')  bitleiste += 1024;
	if(art->KULABSAG[0] == 'J') bitleiste += 512;
	if(art->KULDSDAF[0] == 'J') bitleiste += 256;
	if(art->KULDSGES[0] == 'J') bitleiste += 128;
	if(art->KULAES[0] == 'J')   bitleiste += 64;
	if(art->KULMEER[0] == 'J')  bitleiste += 32;

	return bitleiste;
}

int LadeCstDiscountCont(struct S_DKKUL *knd, char *error_msg)
{
	char *fun = "LadeCstDiscountCont";
	char huelse[20];
	int x;
	int rc;

	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DKKUL   *a;
	char vertriebsfiliale[3];
	EXEC SQL END DECLARE SECTION;
	a = knd;

	if(a->KULVFIL[0] < '0' || a->KULVFIL[0] > '9') a->KULVFIL[0] = '0'; 
	if(a->KULVFIL[1] < '0' || a->KULVFIL[1] > '9') a->KULVFIL[1] = '0'; 
	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,a->KULFIL1);
	EXEC SQL EXECUTE upd_cstdiscountcont USING
		:vertriebsfiliale,
		:a->KULIDF;
	ERROR_MSG3( "upd cstdiscountcont:",a->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		EXEC SQL EXECUTE ins_cstdiscountcont USING
		:vertriebsfiliale,
		:a->KULIDF;
		ERROR_MSG3( "insert cstdiscountcont:",a->KULIDF )
	}

	return OK;
}

int LadeKndausku(struct S_DKKUL *knd, char *error_msg)
{
	char *fun = "LadeKndausku";

	char huelse[20];
	int code,count;

	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DKKUL   *a;
	short vertriebsfiliale;
	short orgfiliale;
	double dMonums;
	EXEC SQL END DECLARE SECTION;
	a = knd;

	/* Monatsumsatz ist nur in Stammfiliale korrekt */
	sprintf(huelse,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,a->KULFIL1);
	vertriebsfiliale = atoi(huelse);
	sprintf(huelse,"%*.*s",L_DKKUL_KULVFIL,L_DKKUL_KULVFIL,a->KULVFIL);
	orgfiliale = atoi(huelse);
	sprintf(huelse,"%*.*s",LS_DKKUL_KULMOUMS,LS_DKKUL_KULMOUMS,a->KULMOUMS);
	dMonums = atof(huelse);
	if(orgfiliale > 0)
	{
		if(orgfiliale != vertriebsfiliale)
		{
			dMonums = 0.0;
		}
	}


	EXEC SQL EXECUTE upd_kndausku USING
							:a->KULEILZ,
							:dMonums,
							:a->KULIDF,
							:a->KULMALFRPR,
							:a->KULVER2,
							'0',			/* :a->KULKUSEIT	*/
							'0',			/* :a->KULURLV		*/
							'0',			/* :a->KULURLB		*/
							:a->KULRAPR,
							'1',
							:a->KULIDF,
							:vertriebsfiliale,
							:a->KULDISPO,
							:a->KULBTMGEB,
							:a->KULDOKGEB,
							:a->KULEP,
							:a->KULLOGAUF,
                            :vertriebsfiliale,
							:a->KULIDF;
	ERROR_MSG3( "upd kndausku:",a->KULIDF )

	code = sqlca.sqlcode;
	count = sqlca.sqlerrd[2];

	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		EXEC SQL EXECUTE ins_ausku USING                                                
				  			:a->KULIDF,                                                   
							:a->KULEILZ,                                                  
							:a->KULMOUMS,                                                  
							:a->KULMALFRPR,                                         
							:a->KULVER2,
							:a->KULRAPR,     /* :a->KULKUSEIT,:a->KULURLV,:a->KULURLB; */
							:a->KULIDF,
							:vertriebsfiliale,
							:a->KULDISPO,
							:a->KULBTMGEB,
							:a->KULDOKGEB,
							:a->KULEP,
							:a->KULLOGAUF
							;
		ERROR_MSG3( "insert kndausku:",a->KULIDF )
	}
	return OK;
}

int LadeKundeLagerInfo(struct S_DKKUL *knd, char *error_msg)
{
	char *fun = "LadeKundeLagerInfo";

	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DKKUL   *a;
	char vertriebsfiliale[3];
	EXEC SQL END DECLARE SECTION;
	a = knd;

	if(a->KULVFIL[0] < '0' || a->KULVFIL[0] > '9') a->KULVFIL[0] = '0'; 
	if(a->KULVFIL[1] < '0' || a->KULVFIL[1] > '9') a->KULVFIL[1] = '0'; 
	sprintf(vertriebsfiliale,"%*.*s",L_DKKUL_KULFIL1,L_DKKUL_KULFIL1,a->KULFIL1);


	EXEC SQL EXECUTE upd_klagerinf USING
							:a->KULFIL1,
							:vertriebsfiliale,
							:a->KULIDF,
							:a->KULENTF,
							'1',
							:a->KULFIL1,
                            :vertriebsfiliale,
							:a->KULIDF;
	ERROR_MSG3( "upd kundelagerinfo:",a->KULIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		EXEC SQL EXECUTE ins_klagerinf USING                                                
							:a->KULFIL1,
							:vertriebsfiliale,
							:a->KULIDF,
							:a->KULENTF
							;
		ERROR_MSG3( "insert kundelagerinfo:",a->KULIDF )
	}
	return OK;
}

int LadeZeitarten(struct S_DKKUL *knd, char *error_msg)
{
	char *fun = "LadeZeitarten";
	char huelse[20];
	int rc;

	EXEC SQL BEGIN DECLARE SECTION;
	struct S_DKKUL   *a;
	struct ZEITARTEN b;
	/*long idf*/;
	char idf[17];       /* WEGEN SCHLUESSEL, FELD AUF DB IST AUCH CHAR(16)!!! */
	long KULBEMO1;
	long KULBEMO2;
	long KULBEMO3;
	long KULBEMO4;
	long KULBEMO5;
	long KULBEMO6;
	long KULENMO1;
	long KULENMO2;
	long KULENMO3;
	long KULENMO4;
	long KULENMO5;
	long KULENMO6;
	long KULBEAB1;
	long KULBEAB2;
	long KULBEAB3;
	long KULBEAB4;
	long KULBEAB5;
	long KULBEAB6;
	long KULENAB1;
	long KULENAB2;
	long KULENAB3;
	long KULENAB4;
	long KULENAB5;
	long KULENAB6;
	long KULVSF1;
	long KULVSF2;
	long KULVSF3;
	long KULVSF4;
	EXEC SQL END DECLARE SECTION;
	a = knd;

	if((rc = SetNotUpdatedzeitarten( error_msg )) != 0) return rc;

	sprintf(huelse,"%*.*s",LS_DKKUL_KULIDF,LS_DKKUL_KULIDF,a->KULIDF);
    /*idf = atol(huelse);*/
	sprintf( idf, "%ld", atol(huelse));
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO1,LS_DKKUL_KULBEMO1,a->KULBEMO1);
    KULBEMO1 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO2,LS_DKKUL_KULBEMO2,a->KULBEMO2);
    KULBEMO2 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO3,LS_DKKUL_KULBEMO3,a->KULBEMO3);
    KULBEMO3 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO4,LS_DKKUL_KULBEMO4,a->KULBEMO4);
    KULBEMO4 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO5,LS_DKKUL_KULBEMO5,a->KULBEMO5);
    KULBEMO5 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEMO6,LS_DKKUL_KULBEMO6,a->KULBEMO6);
    KULBEMO6 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO1,LS_DKKUL_KULENMO1,a->KULENMO1);
    KULENMO1 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO2,LS_DKKUL_KULENMO2,a->KULENMO2);
    KULENMO2 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO3,LS_DKKUL_KULENMO3,a->KULENMO3);
    KULENMO3 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO4,LS_DKKUL_KULENMO4,a->KULENMO4);
    KULENMO4 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO5,LS_DKKUL_KULENMO5,a->KULENMO5);
    KULENMO5 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENMO6,LS_DKKUL_KULENMO6,a->KULENMO6);
    KULENMO6 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB1,LS_DKKUL_KULBEAB1,a->KULBEAB1);
    KULBEAB1 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB2,LS_DKKUL_KULBEAB2,a->KULBEAB2);
    KULBEAB2 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB3,LS_DKKUL_KULBEAB3,a->KULBEAB3);
    KULBEAB3 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB4,LS_DKKUL_KULBEAB4,a->KULBEAB4);
    KULBEAB4 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB5,LS_DKKUL_KULBEAB5,a->KULBEAB5);
    KULBEAB5 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULBEAB6,LS_DKKUL_KULBEAB6,a->KULBEAB6);
    KULBEAB6 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB1,LS_DKKUL_KULENAB1,a->KULENAB1);
    KULENAB1 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB2,LS_DKKUL_KULENAB2,a->KULENAB2);
    KULENAB2 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB3,LS_DKKUL_KULENAB3,a->KULENAB3);
    KULENAB3 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB4,LS_DKKUL_KULENAB4,a->KULENAB4);
    KULENAB4 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB5,LS_DKKUL_KULENAB5,a->KULENAB5);
    KULENAB5 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULENAB6,LS_DKKUL_KULENAB6,a->KULENAB6);
    KULENAB6 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULVSF1,LS_DKKUL_KULVSF1,a->KULVSF1);
    KULVSF1 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULVSF2,LS_DKKUL_KULVSF2,a->KULVSF2);
    KULVSF2 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULVSF3,LS_DKKUL_KULVSF3,a->KULVSF3);
    KULVSF3 = atol(huelse) * 100;
	sprintf(huelse,"%*.*s",LS_DKKUL_KULVSF4,LS_DKKUL_KULVSF4,a->KULVSF4);
    KULVSF4 = atol(huelse) * 100;

	/* Änderung 02.07.97 Verbundfenster unabhängig von Ladenschluss zeiten */
    strcpy(b.TAGESTYP,TYP_MONTAG);
	b.WEEKDAY = 1;
	if (KULBEMO1 != 0)
	{
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULBEMO1,
									:KULENMO1;
		ERROR_MSG3( "upd zeitarten2:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULBEMO1,
									:KULENMO1,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten2",a->KULIDF )
		}
	}
	
    if (KULVSF1 != 0)
	{
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF1,
									:KULVSF2;
		ERROR_MSG3( "upd zeitarten2:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF1,
									:KULVSF2,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten2",a->KULIDF )
		}
	}
	
    if (KULBEAB1 != 0)
    {
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,
								:b.WEEKDAY,
								:KULBEAB1,
								:KULENAB1;
		ERROR_MSG3( "upd zeitarten3:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEAB1,
								:KULENAB1,
								:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten3",a->KULIDF )
       }
	}
	if (KULVSF3 != 0)
	{
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF3,                                                  
									:KULVSF4;                                         
		ERROR_MSG3( "upd zeitarten4:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF3,
									:KULVSF4,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten4",a->KULIDF )
		}
	}
	
	strcpy(b.TAGESTYP,TYP_DIENSTAG);
	b.WEEKDAY = 2;
	if (KULBEMO2 != 0)
	{
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,                                                   
								:b.WEEKDAY,
								:KULBEMO2,                                                  
								:KULENMO2;                                         
		ERROR_MSG3( "upd zeitarten5:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEMO2,
								:KULENMO2,
								:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten5",a->KULIDF )
	    }	
	}
    if (KULVSF1 != 0)
	{
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,                                                   
									:b.WEEKDAY,
									:KULVSF1,
									:KULVSF2;
		ERROR_MSG3( "upd zeitarten6:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,                                                   
									:b.TAGESTYP,                                                  
									:KULVSF1,
									:KULVSF2,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten6",a->KULIDF )
		}
	}

	if (KULBEAB2 != 0)
	{
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,
								:b.WEEKDAY,
								:KULBEAB2,
								:KULENAB2;
		ERROR_MSG3( "upd zeitarten7:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEAB2,
								:KULENAB2,
								:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten7",a->KULIDF )
        }
	}
	if (KULVSF3 != 0)
	{
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF3,
									:KULVSF4;
		ERROR_MSG3( "upd zeitarten8:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF3,
									:KULVSF4,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten8",a->KULIDF )
		}
	}

	strcpy(b.TAGESTYP,TYP_MITTWOCH);
	b.WEEKDAY = 3;
	if (KULBEMO3 != 0)
    {
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,
								:b.WEEKDAY,
								:KULBEMO3,
								:KULENMO3;
		ERROR_MSG3( "upd zeitarten9:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEMO3,
								:KULENMO3,
								:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten9",a->KULIDF )
        }
	}
	if (KULVSF1 != 0)
	{
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF1,
									:KULVSF2;
		ERROR_MSG3( "upd zeitarten10:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF1,
									:KULVSF2,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten10",a->KULIDF )
		}
	}
	if (KULBEAB3 != 0)
    {
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,
								:b.WEEKDAY,
								:KULBEAB3,
								:KULENAB3;
		ERROR_MSG3( "upd zeitarten11:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
		EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEAB3,
								:KULENAB3,
								:b.WEEKDAY;
		ERROR_MSG3( "insert zeitarten11",a->KULIDF )
        }
	}
    if (KULVSF3 != 0)
    {
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF3,
									:KULVSF4;
		ERROR_MSG3( "upd zeitarten12:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF3,
									:KULVSF4,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten12",a->KULIDF )
		}
	}
	
	strcpy(b.TAGESTYP,TYP_DONNERSTAG);
	b.WEEKDAY = 4;
	if (KULBEMO4 != 0)
	{
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,
								:b.WEEKDAY,
								:KULBEMO4,
								:KULENMO4;
		ERROR_MSG3( "upd zeitarten13:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEMO4,
								:KULENMO4,
								:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten13",a->KULIDF )
        }
	}
    if (KULVSF1 != 0)
	{
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF1,
									:KULVSF2;
		ERROR_MSG3( "upd zeitarten14:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF1,
									:KULVSF2,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten14",a->KULIDF )
		}
	}
	if (KULBEAB4 != 0)
    {
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,
								:b.WEEKDAY,
								:KULBEAB4,
								:KULENAB4;
		ERROR_MSG3( "upd zeitarten15:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEAB4,
								:KULENAB4,
								:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten15",a->KULIDF )
        }
	}
    if (KULVSF3 != 0)
	{
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF3,
									:KULVSF4;
		ERROR_MSG3( "upd zeitarten16:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF3,
									:KULVSF4,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten16",a->KULIDF )
		}
	}
	
	strcpy(b.TAGESTYP,TYP_FREITAG);
	b.WEEKDAY = 5;
	if (KULBEMO5 != 0)
    {
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,
								:b.WEEKDAY,
								:KULBEMO5,
								:KULENMO5;
		ERROR_MSG3( "upd zeitarten17:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEMO5,
								:KULENMO5,
								:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten17",a->KULIDF )
        }
	}
    if (KULVSF1 != 0)
    {
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF1,
									:KULVSF2;
		ERROR_MSG3( "upd zeitarten18:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF1,
									:KULVSF2,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten18",a->KULIDF )
		}
	}
	if (KULBEAB5 != 0)
    {
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,
								:b.WEEKDAY,
								:KULBEAB5,
								:KULENAB5;
		ERROR_MSG3( "upd zeitarten19:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEAB5,
								:KULENAB5,
								:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten19",a->KULIDF )
        }
	}
    if (KULVSF3 != 0)
	{
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF3,
									:KULVSF4;
		ERROR_MSG3( "upd zeitarten20:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF3,
									:KULVSF4,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten20",a->KULIDF )
		}
	}

	strcpy(b.TAGESTYP,TYP_SAMSTAG);
	b.WEEKDAY = 6;
	if (KULBEMO6 != 0)
    {
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,
								:b.WEEKDAY,
								:KULBEMO6,
								:KULENMO6;
		ERROR_MSG3( "upd zeitarten21:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEMO6,
								:KULENMO6,
								:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten21",a->KULIDF )
        }
	}
    if (KULVSF1 != 0)
	{
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF1,
									:KULVSF2;
		ERROR_MSG3( "upd zeitarten22:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF1,
									:KULVSF2,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten22",a->KULIDF )
		}
	}
	if (KULBEAB6 != 0)
    {
	 	b.ZEITART = 99;
		EXEC SQL EXECUTE upd_zeitarten USING
								:b.ZEITART,
					  			:idf,
								:b.WEEKDAY,
								:KULBEAB6,
								:KULENAB6;
		ERROR_MSG3( "upd zeitarten23:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
								:b.ZEITART,
					  			:idf,
								:b.TAGESTYP,
								:KULBEAB6,
								:KULENAB6,
								:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten23",a->KULIDF )
        }
	}
    if (KULVSF3 != 0)
	{
	 	b.ZEITART = 1;
		EXEC SQL EXECUTE upd_zeitarten USING
									:b.ZEITART,
						  			:idf,
									:b.WEEKDAY,
									:KULVSF3,
									:KULVSF4;
		ERROR_MSG3( "upd zeitarten24:",a->KULIDF )
		if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )
		{
			EXEC SQL EXECUTE ins_zeitart USING
									:b.ZEITART,
						  			:idf,
									:b.TAGESTYP,
									:KULVSF3,
									:KULVSF4,
									:b.WEEKDAY;
			ERROR_MSG3( "insert zeitarten24",a->KULIDF )

		}
	}
	if((rc = DelNotUpdatedzeitarten( error_msg )) != 0) return rc;
	return OK;
}

int LadeTelnr( struct S_DKKUL *kun, char *error_msg)
{
	char *fun = "LadeTelnr";
	char huelse[20];
	int index;
	int upd;
	long kdnr;

	exec sql begin declare section;
	struct S_DKKUL *d;
	long lIDF;
	long lDate;
    exec sql end declare section;
	d = kun;

	if(d->KULTELRF[0] == ' ') return OK;
	if(!strncmp(d->KULIDF,"0021887",7))
	{
		printf("KULLOE: #%1.1s#",d->KULLOE);fflush(stdout);
		printf("KULAESPER: #%1.1s#",d->KULAESPER);fflush(stdout);
	}
	if(d->KULLOE[0] != 'J' && d->KULAESPER[0] != 'J' &&d->KULLOE[0] != '1' && d->KULAESPER[0] != '1')
	{
		exec sql open CSeltelnr using :d->KULTELRF;
	    ERROR_MSG2( "open CSeltelnr" )

		upd = 0;
		for(;;)
		{
			exec sql fetch CSeltelnr into :lIDF,:lDate;
			if ( sqlca.sqlcode == 100 ) break;
			ERROR_MSG2( "fetch CSeltelnr" )

			sprintf(huelse,"%*.*s",L_DKKUL_KULIDF,L_DKKUL_KULIDF,d->KULIDF);
			kdnr = atol(huelse);

			upd++;
			if(lDate != datum)
			{
				exec sql execute upd_telnr using :d->KULIDF,:datum;
				ERROR_MSG2( "execute upd_telnr" )
			}
			else if(lIDF > kdnr)
			{
				exec sql execute upd_telnr using :d->KULIDF,:datum;
				ERROR_MSG2( "execute upd_telnr" )
			}
		}

		if(upd == 0)
		{
			EXEC SQL EXECUTE ins_telnr USING :d->KULIDF,:d->KULTELRF,:datum;
			if (sqlca.sqlcode == -239)
			return OK;
			ERROR_MSG3( "insert customerphoneno:",d->KULIDF )
		}
	}
	return OK;
}

int AfterLoadKunde( char *error_msg)
{
	char *fun = "AfterLoadKunde";
	int rc = 0;
	if((rc = DelNotUpdatedkunde( error_msg )) != 0) return rc;
	if((rc = AfterLoadDistress( error_msg )) != 0) return rc;
	if(Bulgarien == YES)
	{
		if((rc = AfterLoadPayterm( error_msg )) != 0) return rc;
	}
	else
	{
		if(!isCrema)
		{
			if((rc = AfterLoadDebtlimit( error_msg )) != 0) return rc;
		}
	}
/*	sprintf(error_msg,"%s%d",fun,rc);	*/ /* damit kompiler nicht motzt */
	return OK;
}

int AfterLoadDebtlimit( char *error_msg)
{
	char *fun = "AfterLoadDebtlimit";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	return OK;
}

int AfterLoadDistress( char *error_msg)
{
	char *fun = "AfterLoadDistress";
	int rc = 0;
	if((rc = DelNotUpdatedDistress( error_msg )) != 0) return rc;
	return OK;
}

int AfterLoadPayterm( char *error_msg)
{
	char *fun = "AfterLoadPayterm";
	int rc = 0;
	if((rc = DelNotUpdatedPayterm( error_msg )) != 0) return rc;
	return OK;
}

int AfterLoadPrint( char *error_msg)
{
	char *fun = "AfterLoadPrint";
	int rc = 0;
	if((rc = DelNotUpdatedPrint( error_msg )) != 0) return rc;
	return OK;
}

int AfterLoadCustomerrouting( char *error_msg)
{
	char *fun = "AfterLoadCustomerrouting";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	return OK;
}

int AfterLoadKundeSchalter( char *error_msg)
{
	char *fun = "AfterLoadKundeSchalter";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	if((rc = DelNotUpdatedkundeschalter( error_msg )) != 0) return rc;
	
	return OK;
}

int AfterLoadKundeKondi( char *error_msg)
{
	char *fun = "AfterLoadKundeKondi";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	if((rc = DelNotUpdatedkundekondi( error_msg )) != 0) return rc;
	
	return OK;
}

int AfterLoadKdBetriebsEnde( char *error_msg)
{
	char *fun = "AfterLoadKdBetriebsEnde";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	if((rc = DelNotUpdatedkdbetriebsende( error_msg )) != 0) return rc;
	
	return OK;
}

int AfterLoadKdKonditionGruppe( char *error_msg)
{
	char *fun = "AfterLoadKdKonditionGruppe";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	if((rc = DelNotUpdatedkdkonditiongruppe( error_msg )) != 0) return rc;
	
	return OK;
}

int AfterLoadCstDiscountCont( char *error_msg)
{
	char *fun = "AfterLoadCstDiscountCont";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	if((rc = DelNotUpdatedCstDiscountCont( error_msg )) != 0) return rc;
	
	return OK;
}

int AfterLoadKndausku( char *error_msg)
{
	char *fun = "AfterLoadKndausku";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	if((rc = DelNotUpdatedkndausku( error_msg )) != 0) return rc;
	
	return OK;
}

int AfterLoadKundeLagerInfo( char *error_msg)
{
	char *fun = "AfterLoadKundeLagerInfo";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	if((rc = DelNotUpdatedKundeLagerInfo( error_msg )) != 0) return rc;
	
	return OK;
}

int AfterLoadZeitarten( char *error_msg)
{
	char *fun = "AfterLoadZeitarten";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	
	return OK;
}

int AfterLoadTelnr( char *error_msg)
{
	char *fun = "AfterLoadTelnr";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	
	return OK;
}

int PrepareSetNotUpdatedkunde( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedkunde";

	strcpy(str,"select kzupd from kunde ");
	strcat(str," where vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kunde FROM :str;
	ERROR_MSG2( "prepare sel_kunde" )
	exec sql declare CKunde Cursor with hold for sel_kunde;
	 
	strcpy( str, "update kunde set kzupd = '0' " );
	strcat( str, "where current of CKunde " );
	
	exec sql prepare set_kunde from :str;
	ERROR_MSG2( "prepare set_kunde" )

	return OK;
}

int PrepareDelNotUpdatedkunde( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedkunde";

	strcpy(str,"select kzupd from kunde ");
	strcat(str," where kzupd = '0'");
	strcat(str," and vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kunde2 FROM :str;
	ERROR_MSG2( "prepare sel_kunde2" )
	exec sql declare DelKunde Cursor with hold for sel_kunde2;
	 
	strcpy( str, "delete from kunde " );
	strcat( str, "where current of DelKunde " );
	
	exec sql prepare del_kunde from :str;
	ERROR_MSG2( "prepare del_kunde" )

	return OK;
}

int PrepareSetNotUpdatedDistress( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedDistress";

	strcpy(str,"select upd_flag from distressrouting ");
	strcat(str," where branchno = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_distress FROM :str;
	ERROR_MSG2( "prepare sel_distress" )
	exec sql declare CDistress Cursor with hold for sel_distress;
	 
	strcpy( str, "update distressrouting set upd_flag = '0' " );
	strcat( str, "where current of CDistress " );
	
	exec sql prepare set_distress from :str;
	ERROR_MSG2( "prepare set_distress" )

	return OK;
}

int PrepareDelNotUpdatedDistress( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedDistress";

	strcpy(str,"select upd_flag from distressrouting ");
	strcat(str," where upd_flag = '0'");
	strcat(str," and branchno = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_distress2 FROM :str;
	ERROR_MSG2( "prepare sel_distress2" )
	exec sql declare DelDistress Cursor with hold for sel_distress2;
	 
	strcpy( str, "delete from distressrouting " );
	strcat( str, "where current of DelDistress " );
	
	exec sql prepare del_distress from :str;
	ERROR_MSG2( "prepare del_distress" )

	return OK;
}

int PrepareSetNotUpdatedPayterm( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedPayterm";

	strcpy(str,"select upd_flag from cstpaymentterms ");
	strcat(str," where branchno = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_paymentterms FROM :str;
	ERROR_MSG2( "prepare sel_paymentterms" )
	exec sql declare CPaymentterms Cursor with hold for sel_paymentterms;
	 
	strcpy( str, "update cstpaymentterms set upd_flag = '0' " );
	strcat( str, "where current of CPaymentterms " );
	
	exec sql prepare set_paymentterms from :str;
	ERROR_MSG2( "prepare set_paymentterms" )

	return OK;
}

int PrepareDelNotUpdatedPayterm( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedPayterm";

	strcpy(str,"select upd_flag from cstpaymentterms ");
	strcat(str," where upd_flag = '0'");
	strcat(str," and branchno = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_paymentterms2 FROM :str;
	ERROR_MSG2( "prepare sel_paymentterms2" )
	exec sql declare DelPaymentterms Cursor with hold for sel_paymentterms2;
	 
	strcpy( str, "delete from cstpaymentterms " );
	strcat( str, "where current of DelPaymentterms " );
	
	exec sql prepare del_paymentterms from :str;
	ERROR_MSG2( "prepare del_paymentterms" )

	return OK;
}

int PrepareSetNotUpdatedPrint( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedPrint";

	strcpy(str,"select print from cstprint ");
	strcat(str," where branchno = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_print FROM :str;
	ERROR_MSG2( "prepare sel_print" )
	exec sql declare CPrint Cursor with hold for sel_print;
	 
	strcpy( str, "update cstprint set print = '-1' " );
	strcat( str, "where current of CPrint " );
	
	exec sql prepare set_print from :str;
	ERROR_MSG2( "prepare set_print" )

	return OK;
}

int PrepareDelNotUpdatedPrint( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedPrint";

	strcpy(str,"select print from cstprint ");
	strcat(str," where print = '-1'");
	strcat(str," and branchno = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_print2 FROM :str;
	ERROR_MSG2( "prepare sel_print2" )
	exec sql declare DelPrint Cursor with hold for sel_print2;
	 
	strcpy( str, "delete from cstprint " );
	strcat( str, "where current of DelPrint " );
	
	exec sql prepare del_print from :str;
	ERROR_MSG2( "prepare del_print" )

	return OK;
}

int PrepareSetNotUpdatedkundeschalter( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedkundeschalter";

	strcpy(str,"select kzupd from kundeschalter ");
	strcat(str," where vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kundeschalter FROM :str;
	ERROR_MSG2( "prepare sel_kundeschalter" )
	exec sql declare CKundeschalter Cursor with hold for sel_kundeschalter;
	 
	strcpy( str, "update kundeschalter set kzupd = '0' " );
	strcat( str, "where current of CKundeschalter " );
	
	exec sql prepare set_kundeschalter from :str;
	ERROR_MSG2( "prepare set_kundeschalter" )

	return OK;
}

int PrepareDelNotUpdatedkundeschalter( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedkundeschalter";

	strcpy(str,"select kzupd from kundeschalter ");
	strcat(str," where kzupd = '0'");
	strcat(str," and vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kundeschalter2 FROM :str;
	ERROR_MSG2( "prepare sel_kundeschalter2" )
	exec sql declare DelKundeschalter Cursor with hold for sel_kundeschalter2;
	 
	strcpy( str, "delete from kundeschalter " );
	strcat( str, "where current of DelKundeschalter " );
	
	exec sql prepare del_kundeschalter from :str;
	ERROR_MSG2( "prepare del_kundeschalter" )

	return OK;
}

int PrepareSetNotUpdatedkundekondi( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedkundekondi";

	strcpy(str,"select kzupd from kundekondi ");
	strcat(str," where vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kundekondi FROM :str;
	ERROR_MSG2( "prepare sel_kundekondi" )
	exec sql declare Ckundekondi Cursor with hold for sel_kundekondi;
	 
	strcpy( str, "update kundekondi set kzupd = '0' " );
	strcat( str, "where current of Ckundekondi " );
	
	exec sql prepare set_kundekondi from :str;
	ERROR_MSG2( "prepare set_kundekondi" )

	return OK;
}

int PrepareDelNotUpdatedkundekondi( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedkundekondi";

	strcpy(str,"select kzupd from kundekondi ");
	strcat(str," where kzupd = '0'");
	strcat(str," and vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kundekondi2 FROM :str;
	ERROR_MSG2( "prepare sel_kundekondi2" )
	exec sql declare Delkundekondi Cursor with hold for sel_kundekondi2;
	 
	strcpy( str, "delete from kundekondi " );
	strcat( str, "where current of Delkundekondi " );
	
	exec sql prepare del_kundekondi from :str;
	ERROR_MSG2( "prepare del_kundekondi" )

	return OK;
}

int PrepareSetNotUpdatedkdbetriebsende( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedkdbetriebsende";

	strcpy(str,"select kzupd from kdbetriebsende ");
	strcat(str," where vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kdbetriebsende FROM :str;
	ERROR_MSG2( "prepare sel_kdbetriebsende" )
	exec sql declare Ckdbetriebsende Cursor with hold for sel_kdbetriebsende;
	 
	strcpy( str, "update kdbetriebsende set kzupd = '0' " );
	strcat( str, "where current of Ckdbetriebsende " );
	
	exec sql prepare set_kdbetriebsende from :str;
	ERROR_MSG2( "prepare set_kdbetriebsende" )

	return OK;
}

int PrepareDelNotUpdatedkdbetriebsende( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedkdbetriebsende";

	strcpy(str,"select kzupd from kdbetriebsende ");
	strcat(str," where kzupd = '0'");
	strcat(str," and vertriebszentrumnr = " ); strcat(str, chaus);
    strcat(str," for update");

	EXEC SQL PREPARE sel_kdbetriebsend2 FROM :str;
	ERROR_MSG2( "prepare sel_kdbetriebsend2" )
	exec sql declare Delkdbetriebsende Cursor with hold for sel_kdbetriebsend2;
	 
	strcpy( str, "delete from kdbetriebsende " );
	strcat( str, "where current of Delkdbetriebsende " );
	
	exec sql prepare del_kdbetriebsende from :str;
	ERROR_MSG2( "prepare del_kdbetriebsende" )

	return OK;
}

int PrepareSetNotUpdatedkdkonditiongruppe( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedkdkonditiongruppe";

	strcpy(str,"select kzupd from kdkonditiongruppe ");
	strcat(str," where vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kdkondgruppe FROM :str;
	ERROR_MSG2( "prepare sel_kdkondgruppe" )
	exec sql declare Ckdkonditiongruppe Cursor with hold for sel_kdkondgruppe;
	 
	strcpy( str, "update kdkonditiongruppe set kzupd = '0' " );
	strcat( str, "where current of Ckdkonditiongruppe " );
	
	exec sql prepare set_kdkondgruppe from :str;
	ERROR_MSG2( "prepare set_kdkondgruppe" )

	return OK;
}

int PrepareDelNotUpdatedkdkonditiongruppe( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedkdkonditiongruppe";

	strcpy(str,"select kzupd from kdkonditiongruppe ");
	strcat(str," where kzupd = '0'");
	strcat(str," and vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kdkondgruppe2 FROM :str;
	ERROR_MSG2( "prepare sel_kdkondgruppe2" )
	exec sql declare Delkdkondgruppe Cursor with hold for sel_kdkondgruppe2;
	 
	strcpy( str, "delete from kdkonditiongruppe " );
	strcat( str, "where current of Delkdkondgruppe " );
	
	exec sql prepare del_kdkondgruppe from :str;
	ERROR_MSG2( "prepare del_kdkondgruppe" )

	return OK;
}

int PrepareSetNotUpdatedCstDiscountCont( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedCstDiscountCont";

	strcpy(str,"select upd_flag from cstdiscountcont ");
	strcat(str," where branchno = " ); strcat(str, chaus);
	strcat(str," and order_type = 'PM'");
	strcat(str," for update");

	EXEC SQL PREPARE sel_cstdiscountcont FROM :str;
	ERROR_MSG2( "prepare sel_cstdiscountcont" )
	exec sql declare Ccstdiscountcont Cursor with hold for sel_cstdiscountcont;
	 
	strcpy( str, "update cstdiscountcont set upd_flag = '0' " );
	strcat( str, "where current of Ccstdiscountcont " );
	
	exec sql prepare set_cstdiscountcont from :str;
	ERROR_MSG2( "prepare set_cstdiscountcont" )

	return OK;
}

int PrepareDelNotUpdatedCstDiscountCont( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedCstDiscountCont";

	strcpy(str,"select upd_flag from cstdiscountcont ");
	strcat(str," where upd_flag = '0'");
	strcat(str," and branchno = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_cstdiscountcont2 FROM :str;
	ERROR_MSG2( "prepare sel_cstdiscountcont2" )
	exec sql declare Delcstdiscountcont Cursor with hold for sel_cstdiscountcont2;
	 
	strcpy( str, "delete from cstdiscountcont " );
	strcat( str, "where current of Delcstdiscountcont " );
	
	exec sql prepare del_cstdiscountcont from :str;
	ERROR_MSG2( "prepare del_cstdiscountcont" )

	return OK;
}

int PrepareSetNotUpdatedkndausku( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedkndausku";

	strcpy(str,"select kzupd from kndausku ");
	strcat(str," where vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kndausku FROM :str;
	ERROR_MSG2( "prepare sel_kndausku" )
	exec sql declare Ckndausku Cursor with hold for sel_kndausku;
	 
	strcpy( str, "update kndausku set kzupd = '0' " );
	strcat( str, "where current of Ckndausku " );
	
	exec sql prepare set_kndausku from :str;
	ERROR_MSG2( "prepare set_kndausku" )

	return OK;
}

int PrepareDelNotUpdatedkndausku( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedkndausku";

	strcpy(str,"select kzupd from kndausku ");
	strcat(str," where kzupd = '0'");
	strcat(str," and vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_kndausku2 FROM :str;
	ERROR_MSG2( "prepare sel_kndausku2" )
	exec sql declare Delkndausku Cursor with hold for sel_kndausku2;
	 
	strcpy( str, "delete from kndausku " );
	strcat( str, "where current of Delkndausku " );
	
	exec sql prepare del_kndausku from :str;
	ERROR_MSG2( "prepare del_kndausku" )

	return OK;
}

int PrepareSetNotUpdatedKundeLagerInfo( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedKundeLagerInfo";

	strcpy(str,"select kzupd from kundelagerinfo ");
	strcat(str," where vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_klagerinf FROM :str;
	ERROR_MSG2( "prepare sel_klagerinf" )
	exec sql declare Cklagerinf Cursor with hold for sel_klagerinf;
	 
	strcpy( str, "update kundelagerinfo set kzupd = '0' " );
	strcat( str, "where current of Cklagerinf " );
	
	exec sql prepare set_klagerinf from :str;
	ERROR_MSG2( "prepare set_klagerinf" )

	return OK;
}

int PrepareDelNotUpdatedKundeLagerInfo( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedKundeLagerInfo";

	strcpy(str,"select kzupd from kundelagerinfo ");
	strcat(str," where kzupd = '0'");
	strcat(str," and vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," for update");

	EXEC SQL PREPARE sel_klagerinf2 FROM :str;
	ERROR_MSG2( "prepare sel_klagerinf2" )
	exec sql declare Delklagerinf Cursor with hold for sel_klagerinf2;
	 
	strcpy( str, "delete from kundelagerinfo " );
	strcat( str, "where current of Delklagerinf " );
	
	exec sql prepare del_klagerinf from :str;
	ERROR_MSG2( "prepare del_klagerinf" )

	return OK;
}

int PrepareSetNotUpdatedzeitarten( char *error_msg)
{
	char *fun = "PrepareSetNotUpdatedzeitarten";

	strcpy(str,"select kzupd from zeitarten ");
	strcat(str,"where vertriebszentrumnr=");
	strcat(str,chaus);
  	strcat(str," and ZEITSCHLUESSEL = ?");
  	strcat(str,"and (ZEITART = 1 ");
	strcat(str,"or		ZEITART = 99) ");
	strcat(str,"for update");

	EXEC SQL PREPARE sel_zeitarten FROM :str;
	ERROR_MSG2( "prepare sel_zeitarten" )
	exec sql declare Czeitarten Cursor with hold for sel_zeitarten;
	 
	strcpy( str, "update zeitarten set kzupd = '0' " );
	strcat( str, "where current of Czeitarten " );
	
	exec sql prepare set_zeitarten from :str;
	ERROR_MSG2( "prepare set_zeitarten" )

	return OK;
}

int PrepareDelNotUpdatedzeitarten( char *error_msg)
{
	char *fun = "PrepareDelNotUpdatedzeitarten";

	strcpy(str,"select kzupd from zeitarten ");
	strcat(str,"where kzupd = '0' ");
	strcat(str,"and vertriebszentrumnr=");
	strcat(str, chaus );
  	strcat(str," and ZEITSCHLUESSEL = ?");
  	strcat(str," and (ZEITART = 1 ");
	strcat(str,"or ZEITART = 99) ");
	strcat(str,"for update");

	EXEC SQL PREPARE sel_zeitarten2 FROM :str;
	ERROR_MSG2( "prepare sel_zeitarten2" )
	exec sql declare Delzeitarten Cursor with hold for sel_zeitarten2;
	 
	strcpy( str, "delete from zeitarten " );
	strcat( str, "where current of Delzeitarten " );
	
	exec sql prepare del_zeitarten from :str;
	ERROR_MSG2( "prepare del_zeitarten" )

	return OK;
}


int SetNotUpdatedkunde( char *error_msg)
{
	char *fun = "SetNotUpdatedkunde";

	exec sql open CKunde;
    ERROR_MSG2( "open CKunde" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch CKunde;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CKunde" )
		
		exec sql execute set_kunde;
		ERROR_MSG2( "execute set_kunde" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close CKunde;
    ERROR_MSG2( "close CKunde" )

	return OK;
}

int DelNotUpdatedkunde( char *error_msg)
{
	char *fun = "DelNotUpdatedkunde";

	exec sql open DelKunde;
    ERROR_MSG2( "open DelKunde" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch DelKunde;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelKunde" )
		
		exec sql execute del_kunde;
		ERROR_MSG2( "execute del_kunde" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close DelKunde;
    ERROR_MSG2( "close DelKunde" )

	return OK;
}

int SetNotUpdatedDistress( char *error_msg)
{
	char *fun = "SetNotUpdatedDistress";

	exec sql open CDistress;
    ERROR_MSG2( "open CDistress" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch CDistress;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CDistress" )
		
		exec sql execute set_distress;
		ERROR_MSG2( "execute set_distress" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close CDistress;
    ERROR_MSG2( "close CDistress" )

	return OK;
}

int DelNotUpdatedDistress( char *error_msg)
{
	char *fun = "DelNotUpdatedDistress";

	exec sql open DelDistress;
    ERROR_MSG2( "open DelDistress" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch DelDistress;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelDistress" )
		
		exec sql execute del_distress;
		ERROR_MSG2( "execute del_distress" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close DelDistress;
    ERROR_MSG2( "close DelDistress" )

	return OK;
}

int SetNotUpdatedPayterm( char *error_msg)
{
	char *fun = "SetNotUpdatedPayterm";

	exec sql open CPaymentterms;
    ERROR_MSG2( "open CPaymentterms" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch CPaymentterms;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CPaymentterms" )
		
		exec sql execute set_paymentterms;
		ERROR_MSG2( "execute set_paymentterms" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close CPaymentterms;
    ERROR_MSG2( "close CPaymentterms" )

	return OK;
}

int DelNotUpdatedPayterm( char *error_msg)
{
	char *fun = "DelNotUpdatedPayterm";

	exec sql open DelPaymentterms;
    ERROR_MSG2( "open DelPaymentterms" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch DelPaymentterms;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelPaymentterms" )
		
		exec sql execute del_paymentterms;
		ERROR_MSG2( "execute del_paymentterms" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close DelPaymentterms;
    ERROR_MSG2( "close DelPaymentterms" )

	return OK;
}

int SetNotUpdatedPrint( char *error_msg)
{
	char *fun = "SetNotUpdatedPrint";

	exec sql open CPrint;
    ERROR_MSG2( "open CPrint" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch CPrint;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CPrint" )
		
		exec sql execute set_print;
		ERROR_MSG2( "execute set_print" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close CPrint;
    ERROR_MSG2( "close CPrint" )

	return OK;
}

int DelNotUpdatedPrint( char *error_msg)
{
	char *fun = "DelNotUpdatedPrint";

	exec sql open DelPrint;
    ERROR_MSG2( "open DelPrint" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch DelPrint;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelPrint" )
		
		exec sql execute del_print;
		ERROR_MSG2( "execute del_print" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close DelPrint;
    ERROR_MSG2( "close DelPrint" )

	return OK;
}

int SetNotUpdatedkundeschalter( char *error_msg)
{
	char *fun = "SetNotUpdatedkundeschalter";

	exec sql open CKundeschalter;
    ERROR_MSG2( "open CKundeschalter" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch CKundeschalter;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CKundeschalter" )
		
		exec sql execute set_kundeschalter;
		ERROR_MSG2( "execute set_kundeschalter" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close CKundeschalter;
    ERROR_MSG2( "close CKundeschalter" )

	return OK;
}

int DelNotUpdatedkundeschalter( char *error_msg)
{
	char *fun = "DelNotUpdatedkundeschalter";

	exec sql open DelKundeschalter;
    ERROR_MSG2( "open DelKundeschalter" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch DelKundeschalter;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelKundeschalter" )
		
		exec sql execute del_kundeschalter;
		ERROR_MSG2( "execute del_kundeschalter" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close DelKundeschalter;
    ERROR_MSG2( "close DelKundeschalter" )

	return OK;
}

int SetNotUpdatedkundekondi( char *error_msg)
{
	char *fun = "SetNotUpdatedkundekondi";

	exec sql open Ckundekondi;
    ERROR_MSG2( "open Ckundekondi" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Ckundekondi;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Ckundekondi" )
		
		exec sql execute set_kundekondi;
		ERROR_MSG2( "execute set_kundekondi" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Ckundekondi;
    ERROR_MSG2( "close Ckundekondi" )

	return OK;
}

int DelNotUpdatedkundekondi( char *error_msg)
{
	char *fun = "DelNotUpdatedkundekondi";

	exec sql open Delkundekondi;
    ERROR_MSG2( "open Delkundekondi" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Delkundekondi;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Delkundekondi" )
		
		exec sql execute del_kundekondi;
		ERROR_MSG2( "execute del_kundekondi" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Delkundekondi;
    ERROR_MSG2( "close Delkundekondi" )

	return OK;
}

int SetNotUpdatedkdbetriebsende( char *error_msg)
{
	char *fun = "SetNotUpdatedkdbetriebsende";

	exec sql open Ckdbetriebsende;
    ERROR_MSG2( "open Ckdbetriebsende" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Ckdbetriebsende;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Ckdbetriebsende" )
		
		exec sql execute set_kdbetriebsende;
		ERROR_MSG2( "execute set_kdbetriebsende" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Ckdbetriebsende;
    ERROR_MSG2( "close Ckdbetriebsende" )

	return OK;
}

int DelNotUpdatedkdbetriebsende( char *error_msg)
{
	char *fun = "DelNotUpdatedkdbetriebsende";

	exec sql open Delkdbetriebsende;
    ERROR_MSG2( "open Delkdbetriebsende" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Delkdbetriebsende;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Delkdbetriebsende" )
		
		exec sql execute del_kdbetriebsende;
		ERROR_MSG2( "execute del_kdbetriebsende" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Delkdbetriebsende;
    ERROR_MSG2( "close Delkdbetriebsende" )

	return OK;
}

int SetNotUpdatedkdkonditiongruppe( char *error_msg)
{
	char *fun = "SetNotUpdatedkdkonditiongruppe";

	exec sql open Ckdkonditiongruppe;
    ERROR_MSG2( "open Ckdkonditiongruppe" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Ckdkonditiongruppe;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Ckdkonditiongruppe" )
		
		exec sql execute set_kdkondgruppe;
		ERROR_MSG2( "execute set_kdkondgruppe" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Ckdkonditiongruppe;
    ERROR_MSG2( "close Ckdkonditiongruppe" )

	return OK;
}

int DelNotUpdatedkdkonditiongruppe( char *error_msg)
{
	char *fun = "DelNotUpdatedkdkonditiongruppe";

	exec sql open Delkdkondgruppe;
    ERROR_MSG2( "open Delkdkondgruppe" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Delkdkondgruppe;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Delkdkondgruppe" )
		
		exec sql execute del_kdkondgruppe;
		ERROR_MSG2( "execute del_kdkondgruppe" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Delkdkondgruppe;
    ERROR_MSG2( "close Delkdkondgruppe" )

	return OK;
}

int SetNotUpdatedCstDiscountCont( char *error_msg)
{
	char *fun = "SetNotUpdatedCstDiscountCont";

	exec sql open Ccstdiscountcont;
    ERROR_MSG2( "open Ccstdiscountcont" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Ccstdiscountcont;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Ccstdiscountcont" )
		
		exec sql execute set_cstdiscountcont;
		ERROR_MSG2( "execute set_cstdiscountcont" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Ccstdiscountcont;
    ERROR_MSG2( "close Ccstdiscountcont" )

	return OK;
}

int DelNotUpdatedCstDiscountCont( char *error_msg)
{
	char *fun = "DelNotUpdatedCstDiscountCont";

	exec sql open Delcstdiscountcont;
    ERROR_MSG2( "open Delcstdiscountcont" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Delcstdiscountcont;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Delcstdiscountcont" )
		
		exec sql execute del_cstdiscountcont;
		ERROR_MSG2( "execute del_cstdiscountcont" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Delcstdiscountcont;
    ERROR_MSG2( "close Delcstdiscountcont" )

	return OK;
}

int SetNotUpdatedkndausku( char *error_msg)
{
	char *fun = "SetNotUpdatedkndausku";

	exec sql open Ckndausku;
    ERROR_MSG2( "open Ckndausku" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Ckndausku;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Ckndausku" )
		
		exec sql execute set_kndausku;
		ERROR_MSG2( "execute set_kndausku" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Ckndausku ;
    ERROR_MSG2( "close Ckndausku" )

	return OK;
}

int DelNotUpdatedkndausku( char *error_msg)
{
	char *fun = "DelNotUpdatedkndausku";

	exec sql open Delkndausku;
    ERROR_MSG2( "open Delkndausku" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Delkndausku;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Delkndausku" )
		
		exec sql execute del_kndausku;
		ERROR_MSG2( "execute del_kndausku" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Delkndausku;
    ERROR_MSG2( "close Delkndausku" )

	return OK;
}

int SetNotUpdatedKundeLagerInfo( char *error_msg)
{
	char *fun = "SetNotUpdatedKundeLagerInfo";

	exec sql open Cklagerinf;
    ERROR_MSG2( "open Cklagerinf" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Cklagerinf;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Cklagerinf" )
		
		exec sql execute set_klagerinf;
		ERROR_MSG2( "execute set_klagerinf" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Cklagerinf ;
    ERROR_MSG2( "close Cklagerinf" )

	return OK;
}

int DelNotUpdatedKundeLagerInfo( char *error_msg)
{
	char *fun = "DelNotUpdatedKundeLagerInfo";

	exec sql open Delklagerinf;
    ERROR_MSG2( "open Delklagerinf" )
	EXEC SQL begin work;
	ERROR_MSG2( "Begin Work0:" )

	for(int i=1;;i++)
	{
		if (i%50 == 0)
		{
			exec sql commit work;
   			ERROR_MSG2( "Commit Work:" )
			exec sql begin work;
   			ERROR_MSG2( "begin Work:" )
		}
		exec sql fetch Delklagerinf;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Delklagerinf" )
		
		exec sql execute del_klagerinf;
		ERROR_MSG2( "execute del_klagerinf" )
	}
	EXEC SQL commit work;
	ERROR_MSG2( "Commit Work0:" )

	exec sql close Delklagerinf ;
    ERROR_MSG2( "close Delklagerinf" )

	return OK;
}

int SetNotUpdatedzeitarten( char *error_msg)
{
	char *fun = "SetNotUpdatedzeitarten";

	EXEC SQL BEGIN DECLARE SECTION;
	char zeitschluessel[17];
	EXEC SQL END DECLARE SECTION;

	sprintf(zeitschluessel,"%-16d",IdfNr);

	exec sql open Czeitarten using :zeitschluessel;
    ERROR_MSG2( "open Czeitarten" )

	for(;;)
	{
		exec sql fetch Czeitarten;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Czeitarten" )
		
		exec sql execute set_zeitarten;
		ERROR_MSG2( "execute set_zeitarten" )
	}

	exec sql close Czeitarten ;
    ERROR_MSG2( "close Czeitarten" )

	return OK;
}

int DelNotUpdatedzeitarten( char *error_msg)
{
	char *fun = "DelNotUpdatedzeitarten";

	EXEC SQL BEGIN DECLARE SECTION;
	char zeitschluessel[17];
	EXEC SQL END DECLARE SECTION;

	sprintf(zeitschluessel,"%-16d",IdfNr);

	exec sql open Delzeitarten using :zeitschluessel;
    ERROR_MSG2( "open Delzeitarten" )

	for(;;)
	{
		exec sql fetch Delzeitarten;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch Delzeitarten" )
		
		exec sql execute del_zeitarten;
		ERROR_MSG2( "execute del_zeitarten" )
	}

	exec sql close Delzeitarten ;
    ERROR_MSG2( "close Delzeitarten" )

	return OK;
}

int PrepareSetKAtourplantag( char *error_msg)
{
	char *fun = "PrepareSetKAtourplantag";

	strcpy(str,"select kundennr,tourid,koart from tourplantag ");
	strcat(str," where koart != ' '");
	strcat(str," and vertriebszentrumnr = " ); strcat(str, chaus);
	strcat( str, " and kundennr = ? " );
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

int PrepareCheckQuota( char *error_msg)
{
	char *fun = "PrepareCheckQuota";

	exec sql begin declare section;
	char koart[2];
	long kundennr;
	char tourid[7];
    exec sql end declare section;

	strcpy(str,"select count(*) from ArticleQuota ");
	strcat(str," where branchno = " ); strcat(str, chaus);
	strcat(str," and customerno = ?");

	EXEC SQL PREPARE sel_Quota FROM :str;
	ERROR_MSG2( "prepare sel_Quota" )
	exec sql declare CSelQuota Cursor with hold for sel_Quota;

	strcpy(str,"select articleno,maxquota from maxArticleQuota ");

	EXEC SQL PREPARE sel_MaxQuota FROM :str;
	ERROR_MSG2( "prepare sel_MaxQuota" )
	exec sql declare CSelMaxQuota Cursor with hold for sel_MaxQuota;

	strcpy(str,"insert into ArticleQuota (");
	strcat(str," branchno, ");
	strcat(str," customerno, ");
	strcat(str," articleno, ");
	strcat(str," quota, ");
	strcat(str," kumqty, ");
	strcat(str," validity, ");
	strcat(str," dateupdate, ");
	strcat(str," uid_anlage ");
	strcat(str," ) values ");
	strcat(str,"( ?,?,?,?,0,\"M\",?,0 )");

	EXEC SQL PREPARE ins_Quota FROM :str;
	ERROR_MSG2( "prepare ins_Quota" )

	return OK;
}

int CheckQuota( char *KUNDE, char *error_msg)
{
	char *fun = "CheckQuota";
	char huelse[20];

	exec sql begin declare section;
	long lKundennr;
	long lArtNr;
	long lQuota;
	short sFiliale;
    exec sql end declare section;

	sFiliale = haus;
	sprintf(huelse,"%*.*s",L_DKKUL_KULIDF,L_DKKUL_KULIDF,KUNDE);
	lKundennr = atol(huelse);

	exec sql open CSelMaxQuota;
	ERROR_MSG2( "open CSelMaxQuota" )

	for(;;)
	{
		exec sql fetch CSelMaxQuota into :lArtNr,:lQuota;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CSelMaxQuota" )

		EXEC SQL EXECUTE ins_Quota USING
		:sFiliale,
		:lKundennr,
		:lArtNr,
		:lQuota,
		:datum;
		if ( sqlca.sqlcode == -239 ) continue;
		ERROR_MSG2( "EXECUTE ins_Quota" )
	}

	return OK;
}

int PrepareDelOldEntriesEmergency( char *error_msg)
{
	char *fun = "PrepareDelOldEntriesEmergency";

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;


	strcpy(str,"select 1 from kundenotdienstplan");
	strcat(str," where vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," and datum <= ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_Emergency FROM :str;
	ERROR_MSG2( "prepare sel_Emergency" )
	exec sql declare CSelEmergency Cursor with hold for sel_Emergency;
	 
	strcpy( str, "delete from kundenotdienstplan " );
	strcat( str, "where current of CSelEmergency " );
	
	exec sql prepare del_Emergency from :str;
	ERROR_MSG2( "prepare del_Emergency" )

	return OK;
}

int DelOldEntriesEmergency( char *error_msg)
{
	char *fun = "DelOldEntriesEmergency";
	int delcount;

	EXEC SQL BEGIN DECLARE SECTION;
	int Filialnr;
	EXEC SQL END DECLARE SECTION;

	exec sql begin work;
    if (SQLCODE < 0 )
    {
		ERROR_MSG2( "begin Work1:" )
		PrintMsg( fun, error_msg, FEHL, ERROR );
		return -1;
	}

	exec sql open CSelEmergency using :lDeldate;
    ERROR_MSG2( "open CSelEmergency" )

	for(delcount=0 ;;delcount++ )
	{
		if (delcount%50 == 0)
		{
			exec sql commit work;
            if (SQLCODE < 0 )
    		{
    			ERROR_MSG2( "Commit Work:" )
 	  			PrintMsg( fun, error_msg, FEHL, -1 );
       			return -1;
    		}
			exec sql begin work;
    		if (SQLCODE < 0 )
    		{
    			ERROR_MSG2( "begin Work:" )
 	  			PrintMsg( fun, error_msg, FEHL, ERROR );
       			return -1;
    		}
		}
		exec sql fetch CSelEmergency;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CSelEmergency" )
		
		exec sql execute del_Emergency;
		ERROR_MSG2( "execute del_Emergency" )
	}
	exec sql close CSelEmergency ;
    ERROR_MSG2( "close CSelEmergency" )

	exec sql commit work;
	if (SQLCODE < 0 )
	{
		ERROR_MSG2( "Commit Work2:" )
		PrintMsg( fun, error_msg, FEHL, -1 );
		return -1;
	}

    sprintf(error_msg," %d alte Notdienstplansaetze geloescht",delcount);
	PrintMsg( " ", error_msg, HINW, -1 );

	return OK;
}

int PrepareDelOldEntriesVacation( char *error_msg)
{
	char *fun = "PrepareDelOldEntriesVacation";

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;


	strcpy(str,"select 1 from kundeurlaub");
	strcat(str," where vertriebszentrumnr = " ); strcat(str, chaus);
	strcat(str," and datumgueltigbis <= ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_Vacation FROM :str;
	ERROR_MSG2( "prepare sel_Vacation" )
	exec sql declare CSelVacation Cursor with hold for sel_Vacation;
	 
	strcpy( str, "delete from kundeurlaub " );
	strcat( str, "where current of CSelVacation " );
	
	exec sql prepare del_Vacation from :str;
	ERROR_MSG2( "prepare del_Vacation" )

	return OK;
}

int DelOldEntriesVacation( char *error_msg)
{
	char *fun = "DelOldEntriesVacation";
	int delcount;

	EXEC SQL BEGIN DECLARE SECTION;
	int Filialnr;
	EXEC SQL END DECLARE SECTION;

	exec sql begin work;
    if (SQLCODE < 0 )
    {
		ERROR_MSG2( "begin Work1:" )
		PrintMsg( fun, error_msg, FEHL, ERROR );
		return -1;
	}

	exec sql open CSelVacation using :lDeldate;
    ERROR_MSG2( "open CSelVacation" )

	for(delcount=0 ;;delcount++ )
	{
		if (delcount%50 == 0)
		{
			exec sql commit work;
            if (SQLCODE < 0 )
    		{
    			ERROR_MSG2( "Commit Work:" )
 	  			PrintMsg( fun, error_msg, FEHL, -1 );
       			return -1;
    		}
			exec sql begin work;
    		if (SQLCODE < 0 )
    		{
    			ERROR_MSG2( "begin Work:" )
 	  			PrintMsg( fun, error_msg, FEHL, ERROR );
       			return -1;
    		}
		}
		exec sql fetch CSelVacation;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch CSelVacation" )
		
		exec sql execute del_Vacation;
		ERROR_MSG2( "execute del_Vacation" )
	}
	exec sql close CSelVacation ;
    ERROR_MSG2( "close CSelVacation" )

	exec sql commit work;
	if (SQLCODE < 0 )
	{
		ERROR_MSG2( "Commit Work2:" )
		PrintMsg( fun, error_msg, FEHL, -1 );
		return -1;
	}

    sprintf(error_msg," %d alte Urlaubssaetze geloescht",delcount);
	PrintMsg( " ", error_msg, HINW, -1 );

	return OK;
}

/***** Ende *****************************************************************/

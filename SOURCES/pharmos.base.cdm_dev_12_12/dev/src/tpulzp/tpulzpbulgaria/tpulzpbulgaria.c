/******************************************************************************/
/*     Hauptmodul: tpulzpbulgaria                                             */
/*         Source: tpulzpbulgariapp                                           */
/*          Autor: R. Raab                                                    */
/*       Erstellt: 03.03.2009                                                 */
/*        Sprache: C/Esql-C                                                   */
/*        Erzeugt: basierend auf tpulzentpfl                                  */
/*        Aufgabe: entladen ZDP-Änderungen für Altsystem Bulgarien            */
/*                                                                            */
/******************************************************************************/

/*** VERSION ******************************************************************/
#include "../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.1.4 : tpulzpbulgaria : 10.05.2021 ";
static char *VERSION = "1.1.4 (10.05.2021)";

/*!
\page page39 tpulzpbulgaria
___________________________________________________________________________
\version	1.1.4
\date		10.05.2021
\internal
- RR: INN aus cregisters in dezbg aufgenommen 
\endinternal
___________________________________________________________________________
\version	1.1.3
\date		24.06.2020
\internal
- RR: zartpreis.ke_mwst in depbg aufgenommen 
\endinternal
___________________________________________________________________________
\version	1.1.2
\date		16.01.2019
\internal
- RR: zartikel.fmd_relevant in dezbg aufgenommen 
\endinternal
___________________________________________________________________________
\version	1.1.1
\date		17.09.2013
\internal
- RR: Abfrage auf zpps2bg rausgenommen (Pgm. läuft eh nur in Bulgarien) 
\endinternal
_______________

\version	1.1.0
\date		19.03.2013
\internal
- RR: AIX build
\endinternal
_______________
*/

/* 1.0.1   27.10.2009 : Neuanlagedatum einstellen, wenn Änderungsdatum = 0 */
/* 1.0.2   02.02.2010 : neues Feld Preistyp mitliefern */
/* 1.0.3   10.06.2010 : Preistabelle auf Überlauf abgefragt */
/* 1.0.4   19.08.2010 : diverse zusätzliche Felder */
/* 1.0.5   19.01.2011 : neues Feld ean_nichtvorhanden */
/* 1.0.6   03.02.2011 : 3 neue Felder aus zartbulgaria */
/* 1.0.7   29.12.2011 : 2 neue Felder aus zartbulgaria */
/* 1.1.0   19.03.2013 : AIX build */
/* 1.1.1   17.09.2013 : Abfrage auf zpps2bg rausgenommen (Pgm. läuft eh nur in Bulgarien) */

/*** INCLUDE ******************************************************************/

 #include <stdio.h>
 #include <time.h>
 #include <sys/time.h>
 #include <string.h>
 #include <malloc.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <libgen.h>

 #include "tpulzpbulgaria.h"

 #include "struct.h"
 #include "cdb.h"
 #include "logfile.h"
 #include "zeitstempel.h"
 #include "qtime.h"
 #include "tpulconvbulgaria.h"
 #include "ascitocobol.h"
 #include "tpuldbbulgaria.h"

 #include <voodoo_table_header/zartwg.h>
 #include <voodoo_table_header/zartsekb.h>
 #include <voodoo_table_header/zartprei.h>
 #include <voodoo_table_header/zartikel.h>
 #include <voodoo_table_header/zartbulgaria.h>
 #include <voodoo_table_header/artve.h>
 #include <voodoo_table_header/ean.h>
 #include <voodoo_table_header/carticlelang.h>
 #include <voodoo_table_header/zdkwir.h>
 #include <voodoo_table_header/cregisters.h>

/*** weil 'include ""cdb.h" zu kompliziert ist !!!!!!!!!!!!!!!!!!!!!!!! */
  bool SetLockMode( int iSec );
/*** !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/*** GLOBALE ******************************************************************/

 int debug_enabled = 0;           /* not used here but needed in some modules */
 int test_enabled = FALSE;        /* for test without transmission */

/*** DEFINE *******************************************************************/

 #define L_DEZAP_BYTE   500
 #define DATABASE "ibg21 "			
 #define LOGFILE  "tpulzpbulgaria.log"
 #define OUTPUT_FILE "dezbg.dat"
 #define OUTPUT_FILE2 "depbg.dat"
 #define DESTINATION_FILE "/transfer/dezap"
 #define DESTINATION_HOST "denu1zdev"
 #define OUTPUT_USER "devuser"
 #define PASSWORD "phoenix"
 #define MAX_DAY     7
 #define MAX_ANZ_ZARTWG		12
 #define MAX_ANZ_ZARTPREIS	10

 typedef struct timeval timeval_t;

/*** DECLARATION ***************************************************************/

 static int  CheckProcess( char *progname, int *ipPid );
 static bool OpenLogfile( char *spProg );
 static bool CloseLogfile( void );
 static bool OpenDatabase( char *db );
 static bool CloseDatabase( void );
 static bool GetParameter( parameter *d, char **argv, int argc );
 static bool OpenOutput( char *spFile, const long lDate, FILE **fp, char *spDatabase );
 static bool CloseOutput( FILE *fp );
 // static long DeleteZapflege( void );    
 static long Processing( FILE *fp, FILE *fp2, parameter *p );
 static long GetDeleteDate( int iDay );
 static rterror WriteToDezap( char *spBuf, FILE *fp, int iSize ); 

/*** MAIN *********************************************************************/

 rterror main( int argc, char **argv )
 {
   char *fun = "main";
   long lCountSet = 0;
   FILE *fp;
   FILE *fp2;
   parameter sPara;
   int iPid = -1;

   if ( !CheckProcess( "tpulzpbulgaria", &iPid ) )
   {
          printf( "process is currently active (%d)\n", iPid );
          return is_activ;
   }
   else if ( !GetParameter( &sPara, argv, argc )        )
   {
     printf( "usage:\n" );
     printf( "tpulzpbulgaria [ -file <FILE> -db <database> -dm <DestinationHost> "  \
	      "-dd <DestinationDir> -df <DestinationFile> ]\n" );

     return call_error;
   }

/* printf("\n%d",sPara.lDate);
   printf("\n%d",sPara.lDateTo);
   printf("\n%d",sPara.lDay);
   printf("\n%s",sPara.spFile);
   printf("\n%s",sPara.spDestinationHost);
   printf("\n%s",sPara.spDestinationFile);
   printf("\n%s",sPara.spUser);
   printf("\n%s",sPara.spPassword);
   printf("\n%s",sPara.spDatabase); */

   if ( !OpenLogfile( argv[0] ) )
   {
		printf( "can't open the specified logfile\n" );
        return log_error;
   }
   else if ( !WriteLog( fun, 0, "--------------------------------------------------" ) || 
			 !WriteLog( fun, 0, "Programm gestartet, DB = %s", sPara.spDatabase ) || 
	         !WriteLog( fun, 0, "Datumsbereich: %ld - %ld", sPara.lDate, sPara.lDateTo ) || 
			 !WriteLog( fun, 0, "Versionsnummer: %s", VERSION ) )    
   {
		printf( "Schreiben in Logfile nicht moeglich!\n" );
        return log_error;
   }
   else if ( !OpenDatabase( sPara.spDatabase ) )
   {
		printf( "Datenbank konnte nicht geoeffnet werden!\n" );
        WriteLog( fun, -1, "Programm-Abbruch" );
        return db_error;
   }
   else if ( (rterror)startBrowse( sPara.lDate, sPara.lDateTo, sPara.lDay, sPara.spDatabase ) != no_error )
   {
		WriteLog( fun, -1, "Programm-Abbruch" );
        return db_error;
   }
   else if ( !OpenOutput( sPara.spFile, sPara.lDateTo, &fp, sPara.spDatabase ) )
   {
		printf( "Ausgabedatei %s nicht geöffnet", sPara.spFile );
		WriteLog( fun, -1, "Ausgabedatei %s nicht geöffnet", sPara.spFile );
        return open_error;
   }
   else if ( !OpenOutput( sPara.spFile2, sPara.lDateTo, &fp2, sPara.spDatabase ) )
   {
		printf( "Ausgabedatei %s nicht geöffnet", sPara.spFile2 );
		WriteLog( fun, -1, "Ausgabedatei %s nicht geöffnet", sPara.spFile2 );
        return open_error;
   }

   if ( ( lCountSet = Processing( fp, fp2, &sPara ) ) < 0 )
   {
		WriteLog( fun, -1, "Programm mit Fehler beendet!" );
   } 

   WriteLog( fun, 0, "%ld Saetze geschrieben.", lCountSet );

   endBrowse( lCountSet ? TRUE : FALSE );

   CloseOutput( fp );
   CloseOutput( fp2 );
   CloseDatabase();
   CloseLogfile();

   return no_error;
 }

/***GET-PARAMETER *************************************************************/

static int CheckProcess( char *progname, int *ipPid )
{
   FILE *infile;
   char buf[512];
   int  i;
   int  n;
   int  pos;
   int  lng;
   char *process;

   *ipPid = 0;

   i = strlen(progname) - 1;
   while ( i >= 0 && progname[i] != '/' ) i--;
   process = &progname[i+1];
   if ( ( lng = strlen(process) ) == 0 ) return 0;

   strcpy( buf, "ps -ef|grep -v grep|grep " );
   strcat( buf, process );

   if ( ( infile = (FILE *)popen( buf, "r") ) == NULL )
      return 0;

   for( i = 0; i < 512; i++ )
   {
     if ( ( buf[i] = (char)getc(infile) ) == EOF )
        break;
     else if ( buf[i] == '\n' )
     {
        int pid;
        buf[i] = '\0';

        /* skip leading blanks */
        n = 0;
        while ( buf[n] && buf[n] == ' ' ) n++;
        /* pos second field -> pid */
        while ( buf[n] && buf[n] != ' ' ) n++;
        while ( buf[n] && buf[n] == ' ' ) n++;
        pid = atol( &buf[n] );
        
        /* pos 8th field -> processname */
        pos = 0;
        while ( pos++ < 6 )
        {
            while ( buf[n] && buf[n] != ' ' ) n++;
            while ( buf[n] && buf[n] == ' ' ) n++;
        }

        /* scan processname without path */
        while ( buf[n] && buf[n] != ' ' ) n++;
        n--;
        while ( buf[n] != '/' && buf[n] != ' ' ) n--;
        n++;
        if ( strncmp( &buf[n], process, lng ) == 0 )
        {
            if ( getpid() != pid )
            {
               *ipPid = pid;
               pclose( infile );
               return 0;
            }
            *ipPid = pid;
        }

        i = 0;
      }
   }
   pclose (infile);
   return 1;
}

/***GET-PARAMETER *************************************************************/

 static bool GetParameter( parameter *p, char **argv, int argc )
 {
   bool bSkip;
   bool bUntil = FALSE;
   int  iCount;
   char *szpArgv;

/* memset( (char *)p, (char *)0, sizeof( parameter ) ); */ /* initialize para */
   memset( (char *)p, '\0', sizeof( parameter ) );    /* initialize para */

   /* initialize here all datas you need for parameter! */
   p->spFile = OUTPUT_FILE;
   p->spFile2 = OUTPUT_FILE2;
   p->spDestinationFile = DESTINATION_FILE;
   p->spDestinationHost = DESTINATION_HOST;
   p->spUser = OUTPUT_USER;
   p->spPassword = PASSWORD;
   p->spDatabase = DATABASE;
   p->lDate = GetCurrentDate();
   p->lDateTo = GetCurrentDate();
   p->lDay = GetDeleteDate( MAX_DAY );
   /* end-initializing */

   bSkip = FALSE;
   for ( iCount = 1; iCount < argc; iCount++ )
   {
      if ( bSkip )
          {
         bSkip = FALSE;
         continue;
          }

          szpArgv = argv[iCount];
      if ( !strcmp( szpArgv, "-file" ) )
          {
             p->spFile = argv[iCount + 1];
             bSkip = TRUE;
          }
      else if ( !strcmp( szpArgv, "-db" ) )
          {
	     p->spDatabase = argv[iCount + 1];
         bSkip = TRUE;
          }
      else if ( !strcmp( szpArgv, "-dm" ) )
          {
             p->spDestinationHost = argv[iCount + 1];
         bSkip = TRUE;
          }
          else if ( !strcmp( szpArgv, "-dd" ) )
          {
             p->spDestinationDir = argv[iCount + 1];
         bSkip = TRUE;
      }
          else if ( !strcmp( szpArgv, "-df" ) )
          {
             p->spDestinationFile = argv[iCount + 1];
         bSkip = TRUE;
      }
          else if ( !strcmp( szpArgv, "-ld" ) )
          {
             p->lDate = atol( argv[iCount + 1] );
                 if ( !bUntil )
                        p->lDateTo = p->lDate;
                 bSkip = TRUE;
      }
          else if ( !strcmp( szpArgv, "-to" ) )
          {
             p->lDateTo = atol( argv[iCount + 1] );
         bUntil = TRUE;
                 bSkip = TRUE;
      }
          else if ( !strcmp( szpArgv, "-user" ) )
          {
             p->spUser = argv[iCount + 1];
         bSkip = TRUE;
      }
          else if ( !strcmp( szpArgv, "-pw" ) )
          {
             p->spPassword = argv[iCount + 1];
         bSkip = TRUE;
      }
          else if ( !strcmp( szpArgv, "-day" ) )
          {
                 p->lDay = GetDeleteDate( atoi( argv[iCount + 1] ) );
         bSkip = TRUE;
      }
          else if ( !strcmp( szpArgv, "-test" ) )
          {
                test_enabled = TRUE;
      }
      else
             return FALSE;
   } /* end for */

   return TRUE;
 }

/*** OPEN-LOGFILE *************************************************************/

 static bool OpenLogfile( char *spProg )
 {
   /* beim Programmlauf auf den Datenbanken pps1cch und pps1chr kam es zu einem Abbruch im	*/
   /* CloseLogfile. Da die tatsächlichen Aktivitäten außerhalb des tpulzpbulgaria passieren,*/
   /* konnte die Ursache leider nicht genau nachvollzogen werden. Wir vermuten, dass in der */
   /* Funktion SetDirName (logfile.c) kein Speicher allokiert wird, wenn sie so wie bisher  */
   /* aufgerufen wird, aber beim EndLog ein free versucht wird und das zum Abbruch führt.   */
   /* Warum das nur auf diesen beiden Datenbanken passiert, ist schleierhaft.               */

	char pfad1[255];
	char *pfad2;

/*	strcpy (pfad1, getexecname());
	pfad2 = dirname (pfad1); */

	pfad2 = getcwd(pfad1, 255);

	strcpy (pfad1, pfad2); 
	strcat (pfad1, "/../log"); 

/*	char *LogPath = getenv ( "LOG_PATH" ); */

	SetProgramName( spProg );

/*	if ( SetDirName( LogPath ) == (char *)0 || */
	if ( SetDirName( pfad1 ) == (char *)0 || 
	     SetFileName( LOGFILE ) == (char *)0 )
	{
		return FALSE;
	}

	return TRUE;
 }

/*** OPEN-LOGFILE *************************************************************/

 static bool CloseLogfile( void )
 {
   EndLog();
   return TRUE;
 }

/*** OPEN-DATABASE ************************************************************/

 static bool OpenDatabase( char *db )
 {
   int iBranchNo = 0;
   char *fun = "OpenDatabase";

   if ( !OpenDb( db ) )
   {
      char meld[100];
      sprintf( meld, "Datenbank %s konnte nicht geoeffnet werden", db );
      WriteLog( fun, -1, meld );
      return FALSE;
   }
   else if ( !SetIsolation( DIRTY_READ ) )
   {
      WriteLog( fun, -1, "Set Isolation konnte nicht gesetzt werden" );
      return FALSE;
   }
   else if ( !SetLockMode( 20 ) )
   {
      WriteLog( fun, -1, "Set Lock Mode To Wait konnte nicht gesetzt werden" );
      return FALSE;
   }
   else if ( !GetNumberOfBranch( &iBranchNo, D_INT ) )
   {
      WriteLog( fun, 1, "FilialNr nicht lokalisiert" );
   }

   SetNumberOfBranch( iBranchNo );            /* set branche for logging     */

   return TRUE;
 }

/*** OPEN-DATABASE ************************************************************/

 static bool CloseDatabase( void )
 {
   return CloseDb();
 }

/*** OPEN-OUTPUT **************************************************************/

 static bool OpenOutput( char *spFile, const long lDate, FILE **fp, char *spDatabase )
 {
    bool bReturn;
    char *spPtr;

    if ( ( spPtr = (char *)malloc( (strlen(spFile) + 1) * sizeof(char) ) ) == (char *)0)
        return FALSE;

    strcpy( spPtr, spFile );

	bReturn = (bool)(( *fp = fopen( spPtr, "w" ) ) == (FILE *)0 ? FALSE : TRUE);
    free( spPtr );
    return bReturn;
 }

/*** CLOSE-OUTPUT *************************************************************/

 static bool CloseOutput( FILE *fp )
 {
   fclose( fp );
   return TRUE;
 }

/*** WRITE-TO-DEZAP ***********************************************************/

 static rterror WriteToDezap( char *spBuf, FILE *fp, int iSize)
 {
   spBuf[iSize] = '\n';
   if ( !fwrite( (char *)spBuf, iSize, 1, fp ) )
         return write_error;

   /* zu Testzwecken: keine gepufferte Ausgabe mehr */
   /* fflush ( fp ); */

   return no_error;
 }

/*** GET-DELETE-DATE ***********************************************************/

 static long GetDeleteDate( int iDay )
 {
        timeval_t timev_s;
    timeStr   *time_d;
    char      szBuf[9];

    iDay = iDay<=0 ? 1 : iDay;

	gettimeofday( &timev_s, NULL  );    /* NULL added by hajo */
    timev_s.tv_sec = timev_s.tv_sec - ( 24 * 60 * 60 * iDay );
    time_d = (timeStr *)TimeOfDay( timev_s.tv_sec );
    sprintf( szBuf, "%04d%02d%02d", time_d->year, time_d->mon, time_d->day );
        return atol( szBuf );
 }

static char TestYesNo( char *c )
{
	if (atoi(c))
	{
		return 'O';
	}
	else
	{
		return 'N';
	}
}

/*** PROCESSING ***************************************************************/

 static long Processing( FILE *fp, FILE *fp2, parameter *p )
 {
   /* Strukturen zum Einlesen in die Datenbank */
   dezapzartikelSTR			article;
   dezapzartpreisSTR		price;
   dezapzartsekbezSTR		secondary;
   dezapartveSTR			artve;
   dezapzartwgSTR			goodsgroup;
   dezapzartbulgariaSTR		bulgaria;
   dezapeanSTR				ean;
   dezapcarticlelangSTR		secondname;
   dezapzdkwirSTR			zdkwir;
   dezapcregistersSTR		cregisters;

   dezapzartpreisSTR		price_tab [MAX_ANZ_ZARTPREIS];
   dezapzartwgSTR			goodsgroup_tab [MAX_ANZ_ZARTWG];

/* char                szBuf[L_DEZAP_BYTE + 1];		<-- weil Puffer sonst überläuft, seit INN dazugekommen ist*/
   char				   szBuf[1024];

   rterror             rc;
   long                lCountSet = 0;
   long                lDate;
   int                 iSize;
   int				   iPos;
   int				   iIndZartwg;
   int				   iMaxZartwg;
   int				   iIndZartpreis;
   int				   iMaxZartpreis;
   bool                bChronometer;
   char                *fun = "Processing";
   char				   datum[11];

   iSize = L_DEZAP_BYTE;

   lDate = p->lDateTo > GetCurrentDate() ? p->lDateTo : GetCurrentDate();
   bChronometer = (bool)((char *)getenv( "TIMER" ) == (char *)0 ? FALSE : TRUE);

   /* Beginn Verarbeitung aus zapflege */ 
   while( ( rc = (rterror)GetNextArticle( &article ) ) == no_error )
   {
		 memset( (char *)&szBuf, ' ', sizeof( szBuf ) );
         price.ARTIKEL_NR = article.ARTIKEL_NR;
		 price.DATUMGUELTIGAB = lDate;
         
		 secondary.ARTIKEL_NR	= article.ARTIKEL_NR;
		 artve.ARTIKEL_NR		= article.ARTIKEL_NR;
		 ean.ARTIKEL_NR			= article.ARTIKEL_NR;
		 goodsgroup.ARTIKEL_NR	= article.ARTIKEL_NR;
		 bulgaria.ARTICLENO		= article.ARTIKEL_NR;
		 secondname.ARTICLENO	= article.ARTIKEL_NR;

         if ( bChronometer )
                SETSTART();

         if ( ( rc = (rterror)GetSecondaryOfArticle( &secondary ) ) == db_error )
                break;

         if ( bChronometer )
         {
            SETEND( "GetSecondaryOfArticle" );
            SETSTART();
         }

		 if ( ( rc = (rterror)GetVeOfArticle( &artve ) ) == db_error )
                break;

		 if ( rc == eof )
		 {
			 artve.VERPACKEINHEIT1 = 0;
			 artve.VERPACKEINHEIT2 = 0;
			 artve.VERPACKEINHEIT3 = 0;
			 artve.VERPACKEINHEIT4 = 0;
		 }

         if ( bChronometer )
         {
            SETEND( "GetVeOfArticle" );
            SETSTART();
         }

		 if ( ( rc = (rterror)GetEanOfArticle( &ean ) ) == db_error )
                break;

		 if ( rc == eof )
		 {
			 strcpy (ean.EAN_NR, "");
		 }

         if ( bChronometer )
         {
            SETEND( "GetEanOfArticle" );
            SETSTART();
         }

		 /* Wirkstoffnamen dazulesen, wenn Wirkstoff gefüllt */
		 if (strncmp (article.WIRKSTOFF_NR, "   ", L_ZARTIKEL_WIRKSTOFF_NR) != 0)
		 {
			strncpy (zdkwir.WIR_BEREICH, article.WIRKSTOFF_NR, L_ZARTIKEL_WIRKSTOFF_NR);

			if ( ( rc = (rterror)GetSubstanceName( &zdkwir ) ) == db_error )
					break;

			if ( rc == eof )
				strncpy (zdkwir.WIR_BEZ, " ", L_ZDKWIR_WIR_BEZ);
		 }
		 else
			strncpy (zdkwir.WIR_BEZ, " ", L_ZDKWIR_WIR_BEZ);

		 /* INN dazulesen (artve wird nur verwendet, um die Artikel_nr durchzuschleusen) */
		 strncpy (cregisters.INTERNONPROPNAME, " ", L_CREGISTERS_INTERNONPROPNAME);

		 rc = (rterror) GetINN( &cregisters, &artve);

		 /* keine RC-Abfrage; wenn was nicht geklappt hat, ist INN eben nicht gefüllt

		/* in Bulgarien (und nur dort) zusätzlich zartbulgaria lesen */
		if ( ( rc = (rterror)GetBulgarianFields( &bulgaria ) ) == db_error )
				break;

		if ( bChronometer )
		{
			SETEND( "GetBulgarianFields" );
			SETSTART();
		}

         if ( ( rc = (rterror)GetSecondNameOfArticle( &secondname ) ) == db_error )
                break;

         if ( bChronometer )
         {
            SETEND( "GetSecondNameOfArticle" );
            SETSTART();
         }

		 iIndZartwg = 0;
		 InitGoodsgroupOfArticle( &goodsgroup );     

		 /* alle zartwgs lesen und im Array zwischenspeichern */
         while( ( rc = (rterror)GetGoodsgroupOfArticle( &goodsgroup ) ) == no_error )
         {
			 goodsgroup_tab[iIndZartwg] = goodsgroup;

			 /* Test 
			 printf("\n%d - %d - %s - %s", iIndZartwg, goodsgroup_tab[iIndZartwg].ARTIKEL_NR, goodsgroup_tab[iIndZartwg].ART, goodsgroup_tab[iIndZartwg].WARENGRUPPE); */

			 iIndZartwg++;
			 if (iIndZartwg == MAX_ANZ_ZARTWG)
			 {
				 break;
			 }
         }

		 iMaxZartwg = iIndZartwg;

         if ( rc == db_error )
                break;

         if ( bChronometer )
         {
             SETEND( "GetGoodsgroupOfArticle" );
             SETSTART();
         }

		 iIndZartpreis = 0;

		 if ( (rterror)startBrowseZartpreis( article.ARTIKEL_NR ) != no_error )
		 {
			WriteLog( fun, -1, "Programm-Abbruch" );
			return db_error;
		 }
	
		 /* alle zartpreise lesen und im Array zwischenspeichern */
         while( ( rc = (rterror)GetNextZartpreis( &price ) ) == no_error )
         {
			 price_tab[iIndZartpreis] = price;
			 iIndZartpreis++;

			 if (iIndZartpreis == MAX_ANZ_ZARTPREIS)
			 {
				 break;
			 } 
         }

		 iMaxZartpreis = iIndZartpreis;

         if ( rc == db_error )
                break;

         if ( bChronometer )
         {
             SETEND( "GetNextZartpreis" );
             SETSTART();
         }

		 /* falls Änderungsdatum = 0, soll Neuanlagedatum geliefert werden */
		 if (article.DATUM_AENDER == 0)
			 article.DATUM_AENDER = article.DATUM_ANLAGE;

		 /* Beginn Aufbereitung Ausgabezeile */
		 iPos =sprintf(szBuf, "%d|%.30s|%.9s|", article.ARTIKEL_NR, article.ARTIKEL_NAME, article.EINHEIT);
		 iPos+=sprintf(szBuf+iPos, "%.3s|%.30s|%.9s|", article.DARREICHFORM, secondname.ARTICLENAME, secondname.PACKAGINGUNIT);
		 iPos+=sprintf(szBuf+iPos, "%.3s|%d|%d|", secondname.PHARMAFORM, article.ERSATZ_NR, article.LAENGE);
		 iPos+=sprintf(szBuf+iPos, "%d|%d|%d|", article.BREITE, article.HOEHE, article.GEWICHT);
		 iPos+=sprintf(szBuf+iPos, "%d|%d|%c|", article.LAUFZEITMONATE, article.DATUM_AENDER, article.BESTANDSBUCHUNG[0]);
		 iPos+=sprintf(szBuf+iPos, "%c|%c|%c|", article.PREIS0ARTIKEL[0], article.ARTIKEL_GESPERRT[0], article.REZEPTPFL[0]);
		 iPos+=sprintf(szBuf+iPos, "%c|%c|%c|", article.APOTHEKENPFL[0], article.BTM[0], article.KUEHLARTIKEL[0]);
		 iPos+=sprintf(szBuf+iPos, "%.15s|%c|%c|", article.ARTIKEL_NR_HERST, article.NAHRUNGSTEST[0], article.ARZNEIMITTEL[0]);
		 iPos+=sprintf(szBuf+iPos, "%.50s|%c|", article.ARTIKEL_LANGNAME, article.STELLER[0]);

		 /* zartwg-Array durchsuchen nach art = 'B' (Krankenkassencode) */
		 for (iIndZartwg = 0; iIndZartwg < iMaxZartwg; iIndZartwg++)
		 {
			 if (goodsgroup_tab[iIndZartwg].ART[0] == 'B')
			 {
				 iPos+=sprintf(szBuf+iPos, "%s", goodsgroup_tab[iIndZartwg].WARENGRUPPE);
				 break;
			 }
		 }

		 iPos+=sprintf(szBuf+iPos, "|%f|%f|", bulgaria.INVOICE_REBATE_PCT, bulgaria.REBATE_IN_KIND_PCT);
		 iPos+=sprintf(szBuf+iPos, "%f|%f|", bulgaria.ANNUAL_INV_REB_PCT, bulgaria.ANNUAL_REB_I_K_PCT);
		 iPos+=sprintf(szBuf+iPos, "%f|%d|", bulgaria.CUST_REB_RED_PCT, artve.VERPACKEINHEIT1);

		 /* zartwg-Array durchsuchen nach art = '4' (Artikelgruppe) */
		 for (iIndZartwg = 0; iIndZartwg < iMaxZartwg; iIndZartwg++)
		 {
			 if (goodsgroup_tab[iIndZartwg].ART[0] == '4')
			 {
				 iPos+=sprintf(szBuf+iPos, "%s", goodsgroup_tab[iIndZartwg].WARENGRUPPE);
				 break;
			 }
		 }

		 iPos+=sprintf(szBuf+iPos, "|");

		 /* zartwg-Array durchsuchen nach art = '2' (Lagergruppe) */
		 for (iIndZartwg = 0; iIndZartwg < iMaxZartwg; iIndZartwg++)
		 {
			 if (goodsgroup_tab[iIndZartwg].ART[0] == '2')
			 {
				 iPos+=sprintf(szBuf+iPos, "%s", goodsgroup_tab[iIndZartwg].WARENGRUPPE);
				 break;
			 }
		 }

		 iPos+=sprintf(szBuf+iPos, "|%f|%.13s|", bulgaria.HI_REIMBURSEMENT, ean.EAN_NR);
		 iPos+=sprintf(szBuf+iPos, "%c|%d|%d|", article.CHARGENARTIKEL[0], article.HERSTELLER_NR, bulgaria.PRICE_GROUP);
		 iPos+=sprintf(szBuf+iPos, "%d|%d|%d|", artve.VERPACKEINHEIT2, artve.VERPACKEINHEIT3, artve.VERPACKEINHEIT4);
		 iPos+=sprintf(szBuf+iPos, "%c|%d|%d|", article.SORTIMENT_1[0], bulgaria.CENTRAL_WAREHOUSE, bulgaria.HI_STICKER);
		 iPos+=sprintf(szBuf+iPos, "%s|%c|", zdkwir.WIR_BEZ, article.EAN_NICHTVORHANDEN[0]);
		 iPos+=sprintf(szBuf+iPos, "%f|%f|%f|", bulgaria.SUPPL_HI_REIMB, bulgaria.SUPPL_FS_REIMB, bulgaria.SUPPL_DISCOUNT_PCT);
		 iPos+=sprintf(szBuf+iPos, "%f|%f|", bulgaria.OTHER_REBATES_PCT, bulgaria.YEARLY_BONUS_PCT);
		 iPos+=sprintf(szBuf+iPos, "%d|%.498s|\n", article.FMD_RELEVANT, cregisters.INTERNONPROPNAME);

/*		 ConvertDate(article.DATUM_AH, datum);
		 iPos+=sprintf(szBuf+iPos, "|%s|%c", datum, TestYesNo(article.ARTIKEL_GESPERRT)); */

         if ( ( rc = (rterror)WriteToDezap( szBuf, fp, iPos ) ) != no_error )
         {
			 WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                              szBuf, p->spFile );
			 break;
         }

         if ( bChronometer )
         {
                 SETEND( "WriteToDezap" );
         }

		 /* zartpreis-Array sequentiell abarbeiten */
		 if (iMaxZartpreis > 0)
		 {
			for (iIndZartpreis = 0; iIndZartpreis < iMaxZartpreis; iIndZartpreis++)
			{
				memset( (char *)&szBuf, ' ', sizeof( szBuf ) );
				iPos =sprintf(szBuf, "%ld|%ld|", price_tab[iIndZartpreis].ARTIKEL_NR, price_tab[iIndZartpreis].DATUMGUELTIGAB);
				iPos+=sprintf(szBuf+iPos, "%.2f|%.2f|", price_tab[iIndZartpreis].GROSSO, price_tab[iIndZartpreis].AEP);
				iPos+=sprintf(szBuf+iPos, "%.2f|%d|%.2f|", price_tab[iIndZartpreis].AVP, price_tab[iIndZartpreis].PREIS_TYP, price_tab[iIndZartpreis].MAXAVP);
				iPos+=sprintf(szBuf+iPos, "%c|\n", price_tab[iIndZartpreis].KE_MWST[0]);

				if ( ( rc = (rterror)WriteToDezap( szBuf, fp2, iPos ) ) != no_error )
				{
					WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
									szBuf, p->spFile2 );
					break;
				}

				if ( bChronometer )
				{
						SETEND( "WriteToDezap(2)" );
				}
			}
		 } 

         if ( (lCountSet++) % 100 == 0)
		 {
                fflush( fp );
                fflush( fp2 );
		 }
	}

    return (rc == db_error || rc == write_error) ? be_impaired : lCountSet;
 }

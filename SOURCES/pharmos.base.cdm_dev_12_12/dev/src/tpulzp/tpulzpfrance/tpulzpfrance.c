/******************************************************************************/
/*     Hauptmodul: tpulzpfrance                                               */
/*         Source: tpulzpfrance.cpp                                           */
/*          Autor: R. Raab                                                    */
/*       Erstellt: 05.05.2006                                                 */
/*        Sprache: C/Esql-C                                                   */
/*        Erzeugt: basierend auf tpulzentpfl                                  */
/*        Aufgabe: entladen ZDP-Änderungen für Altsystem Frankreich           */
/*                                                                            */
/******************************************************************************/

/*** VERSION ******************************************************************/
#include "../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.2.0 : tpulzpfrance : 19.03.2013 ";
static char *VERSION = "1.2.0 (19.03.2013)";

/*!
\page page38 tpulzpfrance
___________________________________________________________________________
\version	1.2.0
\date		19.03.2013
\internal
- RR: AIX build
\endinternal
_______________
*/

/* 1.0.1   10.05.2006 : Datum ins Format TT/MM/JHJJ umwandeln */
/* 1.0.2   11.05.2006 : Verpackungseinheiten geändert (von 1-3 auf 2-4) */
/* 1.0.3   22.05.2006 : Handling, wenn keine artve gefunden */
/* 1.0.4   16.06.2006 : Korrektur Mwst- und Preisausgabe */
/* 1.0.5   05.07.2006 : neues Feld Kuehlartikel */
/* 1.0.6   21.09.2006 : wandeln mit neuer zartfrance-Struktur (Vergrößerung code_lppr von 8 auf 15 Stellen) */
/* 1.0.7   26.03.2007 : sortiment_4 nicht mehr liefern, hat zukünftig andere Bedeutung */
/* 1.0.8   25.06.2007 : Umbenennung distr_restr_hosp ---> reserve_hosp */
/* 1.0.9   28.06.2007 : zartikel.artikel_langname statt zartsekbez.artikel_name ausgeben */
/* 1.1.0   07.09.2007 : neues Feld EAN (Tabelle ean lesen)*/
/* 1.1.1   08.07.2008 : Änderungen in Log-Ausgabe wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, */
/* 1.1.2   22.09.2008 : Abfragen auf DBs pps1fr, pps1pfr, pps1iv und pps1piv durch zpps2fr, zpps2pfr, zpps2iv und zpps2piv ersetzt */
/* 1.2.0   19.03.2013 : AIX build */


/*** INCLUDE ******************************************************************/


 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include "tpulzpfrance.h"
 #include "cdb.h"
 #include "logfile.h"
 #include "zeitstempel.h"
 #include "qtime.h"
 #include "tpulconvfrance.h"
 #include "tpuldbfrance.h"
 #include <voodoo_table_header/zartwg.h>
 #include <voodoo_table_header/zartsekb.h>
 #include <voodoo_table_header/zartprei.h>
 #include <voodoo_table_header/zartikel.h>
 #include <voodoo_table_header/zartfrance.h>
 #include <voodoo_table_header/artve.h>
 #include <voodoo_table_header/ean.h>

/*** weil 'include ""cdb.h" zu kompliziert ist !!!!!!!!!!!!!!!!!!!!!!!! */
  bool SetLockMode( int iSec );
/*** !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/*** GLOBALE ******************************************************************/

 int debug_enabled = 0;           /* not used here but needed in some modules */
 int test_enabled = FALSE;        /* for test without transmission */

/*** DEFINE *******************************************************************/

 #define L_DEZAP_BYTE   500
 #define DATABASE "zpps2fr "			
 #define LOGFILE  "tpulzpfrance.log"
 #define OUTPUT_FILE "dezfr.dat"
 #define DESTINATION_FILE "/transfer/dezap"
 #define DESTINATION_HOST "denu1zdev"
 #define OUTPUT_USER "devuser"
 #define PASSWORD "phoenix"
 #define MAX_DAY     7
 #define MAX_ANZ_ZARTWG		12
 #define MAX_ANZ_ZARTPREIS	5

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
 static long DeleteZapflege( void );    
 static long Processing( FILE *fp, parameter *p );
 static long GetDeleteDate( int iDay );
 static rterror WriteToDezap( char *spBuf, FILE *fp, int iSize ); 

/*** MAIN *********************************************************************/

 rterror main( int argc, char **argv )
 {
   char *fun = "main";
   long lCountSet = 0;
   FILE *fp;
   parameter sPara;
   int iPid = -1;

   if ( !CheckProcess( "tpulzpfrance", &iPid ) )
   {
          printf( "process is currently active (%d)\n", iPid );
          return is_activ;
   }
   else if ( !GetParameter( &sPara, argv, argc )        )
   {
     printf( "usage:\n" );
     printf( "tpulzpfrance [ -file <FILE> -db <database> -dm <DestinationHost> "  \
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

   if ( ( lCountSet = Processing( fp, &sPara ) ) < 0 )
   {
		WriteLog( fun, -1, "Programm mit Fehler beendet!" );
   } 

   WriteLog( fun, 0, "%ld Saetze geschrieben.", lCountSet );

   endBrowse( lCountSet ? TRUE : FALSE );

   CloseOutput( fp ); 
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
   /* beim Programmlauf auf den Datenbanken pps1cch und pps1chr kam es zu einem Abbruch im */
   /* CloseLogfile. Da die tatsächlichen Aktivitäten außerhalb des tpulzpfrance passieren,  */
   /* konnte die Ursache leider nicht genau nachvollzogen werden. Wir vermuten, dass in der*/
   /* Funktion SetDirName (logfile.c) kein Speicher allokiert wird, wenn sie so wie bisher */
   /* aufgerufen wird, aber beim EndLog ein free versucht wird und das zum Abbruch führt.  */
   /* Warum das nur auf diesen beiden Datenbanken passiert, ist schleierhaft.              */

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

 static long Processing( FILE *fp, parameter *p )
 {
   /* Strukturen zum Einlesen in die Datenbank */
   dezapzartikelSTR			article;
   dezapzartpreisSTR		price;
   dezapzartsekbezSTR		secondary;
   dezapartveSTR			artve;
   dezapzartwgSTR			goodsgroup;
   dezapzartfranceSTR		france;
   dezapeanSTR				ean;

   dezapzartpreisSTR		price_tab [MAX_ANZ_ZARTPREIS];
   dezapzartwgSTR			goodsgroup_tab [MAX_ANZ_ZARTWG];

   char                szBuf[L_DEZAP_BYTE + 1];

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
         
		 secondary.ARTIKEL_NR = article.ARTIKEL_NR;
		 artve.ARTIKEL_NR = article.ARTIKEL_NR;
		 ean.ARTIKEL_NR = article.ARTIKEL_NR;
		 goodsgroup.ARTIKEL_NR = article.ARTIKEL_NR;
		 france.ARTICLENO = article.ARTIKEL_NR;

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

		 /* in Frankreich (und nur dort) zusätzlich zartfrance lesen */
		 if (strcmp(p->spDatabase, "zpps2fr") == 0 || strcmp(p->spDatabase, "zpps2pfr") == 0 ||
		 	 strcmp(p->spDatabase, "zpps2iv") == 0 || strcmp(p->spDatabase, "zpps2piv") == 0)
		 {
			if ( ( rc = (rterror)GetFrenchFields( &france ) ) == db_error )
					break;

			if ( bChronometer )
			{
				SETEND( "GetFrenchFields" );
				SETSTART();
			}
		 }

		 iIndZartwg = 0;
		 InitGoodsgroupOfArticle( &goodsgroup );     

		 /* alle zartwgs lesen und im Array zwischenspeichern */
         while( ( rc = (rterror)GetGoodsgroupOfArticle( &goodsgroup ) ) == no_error )
         {
			 goodsgroup_tab[iIndZartwg] = goodsgroup;
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

			 if ((iIndZartpreis == MAX_ANZ_ZARTPREIS) || (price.DATUMGUELTIGAB < p->lDate))
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

		 /* Beginn Aufbereitung Ausgabezeile */
		 /* iPos = sprintf(szBuf, "%d|%.30s|", article.ARTIKEL_NR, secondary.ARTIKEL_NAME); */
		 iPos = sprintf(szBuf, "%d|%.30s|", article.ARTIKEL_NR, article.ARTIKEL_LANGNAME);

		 /* zartwg-Array durchsuchen nach art = '2' (Warengruppe) */
		 for (iIndZartwg = 0; iIndZartwg <= iMaxZartwg; iIndZartwg++)
		 {
			 if (goodsgroup_tab[iIndZartwg].ART[0] == '2')
			 {
				 iPos+=sprintf(szBuf+iPos, "%s", goodsgroup_tab[iIndZartwg].WARENGRUPPE);
				 break;
			 }
		 }

		 iPos+=sprintf(szBuf+iPos, "|%d|", article.HERSTELLER_NR);

		 /* zartwg-Array durchsuchen nach art = '9' (Rabattgruppe) */
		 for (iIndZartwg = 0; iIndZartwg <= iMaxZartwg; iIndZartwg++)
		 {
			 if (goodsgroup_tab[iIndZartwg].ART[0] == '9')
			 {
				 iPos+=sprintf(szBuf+iPos, "%s", goodsgroup_tab[iIndZartwg].WARENGRUPPE);
				 break;
			 }
		 }

         /* iPos+=sprintf(szBuf+iPos, "|%.30s", secondary.ARTIKEL_NAME); */
		 iPos+=sprintf(szBuf+iPos, "|%.30s", article.ARTIKEL_LANGNAME);

		 if (iMaxZartpreis > 0)
		 {
			iPos+=sprintf(szBuf+iPos, "|%c", price_tab[0].KE_MWST[0]);
		 }
		 else
		 {
			iPos+=sprintf(szBuf+iPos, "|-");
		 }
		
		 iPos+=sprintf(szBuf+iPos, "|%d|%d|%d|%d", article.LAENGE, article.BREITE, article.HOEHE, article.GEWICHT);
		 iPos+=sprintf(szBuf+iPos, "|%c|%c|%.2f|%c", TestYesNo(france.RESERVE_HOSP), TestYesNo(article.BTM), france.REIMBURSEMENT_VAL, france.REIMBURSEMENT_TYPE[0]);
		 iPos+=sprintf(szBuf+iPos, "|%d|%s|%d|", france.QTY_SUBMULTIPLE, france.UNIT_MULTIPLE, article.AWL1);

		 /* zartpreis-Array sequentiell abarbeiten */

		 if (iMaxZartpreis > 0)
		 {
			for (iIndZartpreis = 0; iIndZartpreis < iMaxZartpreis; iIndZartpreis++)
			{
				ConvertDate(price_tab[iIndZartpreis].DATUMGUELTIGAB, datum);
				iPos+=sprintf(szBuf+iPos, "%s-%.2f-%.2f-%.2f", datum, price_tab[iIndZartpreis].GROSSO, price_tab[iIndZartpreis].AEP, price_tab[iIndZartpreis].AVP);

				/* Trennzeichen, falls noch ein Preis folgt */
				if ((iIndZartpreis + 1) < iMaxZartpreis)
				{
					iPos+=sprintf(szBuf+iPos, "@");
				}
			}
		 }

		 /* Daten aus artve */
		 iPos+=sprintf(szBuf+iPos, "|%d|%d|%d", artve.VERPACKEINHEIT4, artve.VERPACKEINHEIT3, artve.VERPACKEINHEIT2);

		 iPos+=sprintf(szBuf+iPos, "|%c|%d|%d", TestYesNo(article.ZENTR_EKSPERRE), article.MINDESTBEZUG, atoi (article.EINHEIT));

		 ConvertDate(article.DATUM_AH, datum);
		 iPos+=sprintf(szBuf+iPos, "|%s|%c", datum, TestYesNo(article.ARTIKEL_GESPERRT));

		 ConvertDate(article.DATUM_ANLAGE, datum);
		 iPos+=sprintf(szBuf+iPos, "|%s", datum);

		 ConvertDate(article.DATUM_AENDER, datum);
		 iPos+=sprintf(szBuf+iPos, "|%s|%c", datum, TestYesNo(article.SORTIMENT_1));

		 if (article.PRODUKTART[0] == '2')
		 {
			 iPos+=sprintf(szBuf+iPos, "|O");
		 }
		 else
		 {
			 iPos+=sprintf(szBuf+iPos, "|N");
		 }

		 iPos+=sprintf(szBuf+iPos, "|%c|%c|%c", TestYesNo(article.SORTIMENT_2), TestYesNo(article.KUEHLARTIKEL), TestYesNo(france.NOT_VIA_EDI));
		 iPos+=sprintf(szBuf+iPos, "|%s|%s|%c", article.EINHEIT, article.DARREICHFORM, article.PSYCHOTROP[0]);
		 iPos+=sprintf(szBuf+iPos, "|%s|%c| |", article.ARTIKEL_NR_HERST, TestYesNo(article.SORTIMENT_3));

		 /* zartwg-Array durchsuchen nach art = '5' (Saisonart) */
		 for (iIndZartwg = 0; iIndZartwg <= iMaxZartwg; iIndZartwg++)
		 {
			 if (goodsgroup_tab[iIndZartwg].ART[0] == '5')
			 {
				 iPos+=sprintf(szBuf+iPos, "%s", goodsgroup_tab[iIndZartwg].WARENGRUPPE);
				 break;
			 }
		 }

		 iPos+=sprintf(szBuf+iPos, "|%s|%d|%.2f", france.CODE_LPPR, article.ERSATZ_NR, france.REIMBURSEMENT_PERC);
		 iPos+=sprintf(szBuf+iPos, "|%s|\n", ean.EAN_NR);

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

         if ( (lCountSet++) % 100 == 0)
                fflush( fp );
	}

    return (rc == db_error || rc == write_error) ? be_impaired : lCountSet;
 }

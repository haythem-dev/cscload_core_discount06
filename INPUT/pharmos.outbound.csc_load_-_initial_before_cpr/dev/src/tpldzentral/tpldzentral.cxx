/*###########################################################################*/
/*#                                                                         #*/
/*# BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#                                                                         #*/
/*###########################################################################*/

#include "csc_load_version.h"

#define PROJECTNAME  "tpldzentral"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/*****************************************************************************/
/* Einfuegen neuer Tabellen in das Artikelladeprogramm                       */
/*****************************************************************************/
/* 1 Tabelle im Incudefile definieren und ANZ_TABELLEN aktualisieren         */
/* 2 Eintrag in Funktion SetzeSchalterTabelle erzeugen                       */
/* 3 Implementierung und Aufruf der Initialisierungsfunktion (create table..)*/
/* 4 Implementierung und Aufruf der Ladefunktionfunktion (in Bezug auf DKART)*/
/* 5 Implementierung und Aufruf der Endefunktion (drop/create index, rename )*/
/*****************************************************************************/

#include <stdio.h>
#include <math.h>
#include "pplib/allg.h"
#include "zartikel.h"
#include "zartpreis.h"
#include "zartsekbez.h"
#include "zartwg.h"
#include "zapflege.h"
#include "artikelzentral.h"
#include "artikellppr.h"
#include "artpreis.h"
#include "artsel.h"
#include "artspecialcond.h"
#include "libtpld/define.h"
#include "articlecodes.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "versioninfo.h"

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*#undef NULL */

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1],\
                                        sqlca.sqlerrm); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define NOTFOUND           sqlca.sqlcode == SQLNOTFOUND

#define OK                   0
#define NO                   0
#define YES                  1
#define ERROR               -1
#define INSERT               1
#define FILE_NOT_FOUND       1
#define WARNING             -2
#define HINW               'H'
#define FEHL               'F'
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */
#define MAX_CH_ARTIKELNAME 26
#define MAX_CH_ARTIKELLANGNAME 50

int debug_enabled  = NO;
int urladen  = NO;
int explain = NO;
int Frankreich = NO;
int swFrance = 1;
int swAustria = 1;
int swSwiss = 1;
int swSerbia = 1;
int swCroatia = 1;
int swBulgaria = 1;
long m_lngArtikelNummerUpdates = 0;
long m_lngArtikelNummerInserts = 0;
long m_lngArtikelZentralUpdates = 0;
long m_lngArtikelZentralInserts = 0;
long m_lngArtikelPreisUpdates = 0;
long m_lngArtikelPreisInserts = 0;
long m_lngArtikelCodeUpdates = 0;
long m_lngArtikelCodeInserts = 0;
long m_lngArtikelCodeDeletes = 0;

exec sql begin declare section;
double dAEP;
double dAVP;
double dAGP;
char cKE_MWST[2];
char LPPRType[2];
char LPPRCode[16];
double LPPRProz;
double LPPRWert;
double TFRBasePrice;
long datum;
long datumvon;
long datumbis;
long datumpreis;
long artikel_nr ;
char indatenbank[60];
char outdatenbank[60];
struct N_ZARTIKEL   a;
struct N_ZARTWG     w;
struct N_ZARTSEKBEZ s;
struct N_ARTSPECIALCOND cond;
char WARENGRUPPE[6];
char WARENGRUPPEEIGEN[6];
char THERAPIEGRUPPE[6];
char ABDACODE[6];
char KRANKENHAUSCODE[6];
char TEXTSCHLUESSEL[6];
long ETARTKLASSE1;
long ETARTSCHALTER1;
long ETARTSCHALTER2;
long ETARTSCHALTER3;
long ETARTSCHALTER4;
long ETARTSCHALTER5;
long PACKGROESSE;
char NORMPACKUNG[3];
char HOSPITAL[2];
char CODEBLOCAGE[2];
char LEGALL[2];
char BREIZH[2];
char EXPORT[2];
char PLPL[2];
char S1S5[2];
char VPL[2];
char SP[2];
char COMPTANT[2];
short DEUTSCHLANDBESORGER;
char NEUFORM[2];
char BDORF[2];
char MEDPROD[2];
char VERTBINDNURAPO[2];
char VERTBINDNURSPIT[2];
char VERTBINDKUENZLE[2];
char VERTBINDINLAND[2];
char VERTBINDKANTONAL[2];
char VERTBINDPREWHOLE[2];
char VERTBINDLISTEC[2];
char VERTBINDLISTED[2];
char IKS_CODE[2];
char FRMC[13];
char FRNAME[31];
char FRPACK[10];
char FRDF[4];
char REFUNDTYPE[2];
short PRICEGROUP;
char DISTR_RESTR_MED2A[2];
char DISTR_RESTR_MED2B3[2];
char DISTR_RESTR_HUDRUG[2];
char DISTR_RESTR_BRDRUG[2];
char DISTR_RESTR_ALCOH[2];
char DISTR_RESTR_VETMED[2];
char DISTR_RESTR_VEDRUG[2];
char DISTR_RESTR_HUDRVE[2];
char str[4096];
short sList5;
short DISTR_RESTR_NODRST;
short DISTR_RESTR_NOWHS;
short sMedizin;
char DISTR_RESTR_TEND[2];
char DISTR_RESTR_BETY[2];
char DISTR_RESTR_BENU[2];
char DISTR_RESTR_ALRG[2];
char DISTR_RESTR_CAUD[2];
char DISTR_RESTR_HEM[2];
char DISTR_RESTR_GR7[2];
char DISTR_RESTR_GR8[2];
char cATC_Code[26];
char cMINISTRYPRODUCTCODE[26];
char cHEALTHFUNDCODEHOSPITAL[26];
short sCode_Type;
exec sql end declare section;


/***** DECLARATION **********************************************************/

int main( int, char ** );
void PrintMsg( char *fun, char *error_msg, char mld, int rc );
int StarteLadenDerArtikelRelationen( const int, char *error_msg);
int PrepareLoadTables         ( const int,char *error_msg);
int LoadTables                ( const int, char *error_msg);
int AfterLoadTables           ( const int,char *error_msg);
int SetNotUpdated             ( char *error_msg );
int DelNotUpdated             ( char *error_msg );
int PrepareHoleArtikelNummern ( char *error_msg );
int PrepareLadeArtikelZentral ( char *error_msg);
int PrepareLadeArtikelIndex   ( char *error_msg);
int PrepareLadeArtikelIndexFR ( char *error_msg);
int PrepareLadeArtikelpreis   ( char *error_msg);
int PrepareLadeArtikelnummern ( char *error_msg);
int PrepareLadeArtselect      ( char *error_msg);
int PrepareLadeLPPR           ( char *error_msg);
int PrepareLadeArtSpecial     ( char *error_msg);
int PrepareLadeArticlecodes   ( char *error_msg);
int HoleArtikelNummern        ( char *error_msg );
int LadeArtikelZentral        ( char *error_msg);
int LadeArtikelIndex          ( long, char *, char *);
int LadeArtikelIndexFR        ( long, char *, char *);
int LadeArtikelsekbez         ( char *error_msg);
int LadeArtikelpreis          ( char *error_msg);
int LadeArtikelnummern        ( char *error_msg);
int LadeArtselect             ( char *error_msg);
int LadeLPPR                  ( char *error_msg);
int LadeArtSpecial            ( char *error_msg);
int LadeArticlecodes          ( char *error_msg);
int CloseDatabase( void );
int zaehler = 0;
void Runden( double *wert, int stellen );

/***** Entferne1Blanc *******************************************************/

void Entferne1Blanc(char *spStr)
{
   int i;
   int iEnd = strlen(spStr);
   for ( i = 0; i < iEnd; i++ )
   {
       if ( spStr[i] == ' ' )
       {
         for ( ; i < iEnd - 1; i++ )
         {
             spStr[i] = spStr[i+1];
         }
         spStr[iEnd-1] = '\0';
         break;
       }
   }
}

/***** IsBlancInStr *********************************************************/

int IsBlancInStr(const char* spStr, const int iMax)
{
   int i;
   int iIsBlanc = 0;
   for ( i = 0; i < iMax || spStr[i] == '\0'; i++ )
   {
       if ( spStr[i] == ' ' )
       {
          iIsBlanc = 1;
          break;
       }
   }

   return iIsBlanc;
}

/***** ArtikelSpezial *******************************************************/

void ArtikelSpezial(char* spName)
{
   int i;
   char* spPtr;
   char szBuf[32];
   char szCopy[32];

   if ( memcmp( spName, "REGENAPLEX ", 11 ) != 0 )
      return;

   memcpy( szBuf, spName, 11 );
   spPtr = spName + 11;
   for ( i = 11; i < 26; i++, spPtr++ )
   {
       if ( *spPtr >= '0' && *spPtr <= '9' )
       {
          szBuf[i] = *spPtr;
          szBuf[i+1] = '\0';
          continue;
       }

       if ( !IsBlancInStr( spPtr, 26 -i ) )
          break;

       strcpy( szCopy, spPtr );
       Entferne1Blanc( szCopy);

       szBuf[i] = ' ';
       szBuf[i+1] = '\0';
       memcpy( &szBuf[0] + i + 1, szCopy, strlen(szCopy));
       szBuf[30] = '\0';
       strcpy( spName, szBuf);
       break;
   }
}

/***** MAIN *****************************************************************/

int main( int argc, char **argv  )
{
    char  error_msg[181];
    char  *schalter;
    int   i;
    char  *fun = "Main";
    char  *LOG_FILE = "wws.log";
    char  *LOG_PATH;
    char  logpath[256 + 1];
    int   rc;
    int   status = 0;
    char  start_msg[81];
    char  datum_msg[81];
    int   iTable = -1;
    long  ltag;

    datum = AllgGetDate();
    if (AllgGetTime() < 120000)
    {
        datum = AllgAddDate(datum, -1, error_msg);
    }
    datumvon = AllgAddDate(datum, -1, error_msg);
    datumbis = AllgAddDate(datum, 4, error_msg);

    ltag = AllgGetWeekDay(datum,error_msg);
    if( ltag == 6 )     /* Samstag */
        datumpreis = AllgAddDate(datum,2,error_msg);
    else
        datumpreis = AllgAddDate(datum,1,error_msg);

    strcpy(start_msg, "gestartet mit:");
    for ( i = 1; i < argc; i++ )
    {
        schalter = argv[i];
        if ( !strcmp( schalter, "-dg" ) )
        {
            strcat(start_msg, " -dg");
            debug_enabled = YES;
        }
        else if ( !strcmp( schalter, "-all" ) )
        {
            strcat(start_msg, " -all");
            urladen = YES;
        }
        else if ( !strcmp( schalter, "-ld" ) )
        {
            i++;
            datum = atol( argv[i] );
            sprintf(start_msg, "%s -ld %d",start_msg,datum);
        }
        else if ( !strcmp( schalter, "-dbin" ) )
        {
            strcat(start_msg, " -dbin");
            i++;
            sprintf( indatenbank, "%s", argv[i] );
            sprintf(start_msg,"%s %s",start_msg,argv[i]);
        }
        else if ( !strcmp( schalter, "-dbout" ) )
        {
            strcat(start_msg, " -dbout");
            i++;
            sprintf( outdatenbank, "%s", argv[i] );
            sprintf(start_msg,"%s %s",start_msg,argv[i]);
        }
        else if ( !strcmp( schalter, "-ex" ) )
        {
            strcat(start_msg, " -ex");
            explain = YES;
        }
        else if ( !strcmp( schalter, "-FR" ) )
        {
            strcat(start_msg, " -FR");
            Frankreich = YES;
        }
        else if ( !strcmp( schalter, "-version" ) )
        {
            printVersion(versioninfo);
            return 0;
        }
        else
        {
            printf( "  usage: %s\n\t"
                " { -dbin datenbankname <Datenbankname Eingabe> }\n\t"
                " { -dbout datenbankname <Datenbankname Ausgabe> }\n\t"
                " { -dg <Debugging> }\n\t"
                " [ -ex <Explain> ]\n\t",
                argv[0] );
            return 1;
        }
    }

    exec sql database :outdatenbank;
    ERROR_MSG( "Fehler oeffnen DB" )

    exec sql set lock mode to wait 20;
    ERROR_MSG( "Set LockMode to Wait" )

    exec sql set isolation to dirty read;
    ERROR_MSG( "Set Isolation to Dirty Read" )

    if (explain == YES)
    {
        exec sql set explain on;
        ERROR_MSG( "Set Explain On" )
    }

    PrintMsg( "tpldzentral ", start_msg, HINW, 0 );
    sprintf(datum_msg,"Datum: %d, Preisdatum: %d",datum, datumpreis);
    PrintMsg( "tpldzentral ", datum_msg, HINW, 0 );
    if ( PrepareLoadTables( iTable, error_msg ) != OK )
        return 8;

    if ( ( rc = StarteLadenDerArtikelRelationen( iTable, error_msg ) ) != 0 )
    {
        PrintMsg( "tpldzentral ", "mit Fehler beendet", FEHL, rc );
        return 9;
    }
    PrintMsg( "tpldzentral ", "korrekt beendet", HINW, rc );
    return 0;
}

 /***** STARTE DAS LADEN DER ARTIKEL-TABELLEN ************************************/

int StarteLadenDerArtikelRelationen( const int iTable, char *error_msg)
{
    int  rc = OK;
    int  ende = NO;
    char *fun = "StarteLadenDerArtikelRelationen";

    EXEC SQL begin work;
    ERROR_MSG( "Begin Work" )

    for ( ;; )
    {
        if (urladen == YES)
        {
            exec sql fetch Cselzartikelall into :a;
            ERROR_MSG( "fetch Cselzartikelall" )
            if(NOTFOUND) break;
            artikel_nr = a.ARTIKEL_NR;
        }
        else
        {
            exec sql fetch Cselzapflege into :artikel_nr;
            ERROR_MSG( "fetch Cselzapflege" )
            if(NOTFOUND) break;
        }

        if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )

           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }
        if ( zaehler % 1000 == 0 )
        {
           DEBUG_SECTION
           sprintf( error_msg, "%d Saetze geladen", zaehler );
           PrintMsg( fun, error_msg, HINW, OK );
           END_DEBUG_SECTION
        }

        if ( ( rc = LoadTables( iTable, error_msg ) ) < 0 )
        {
            PrintMsg( fun, error_msg, FEHL, ERROR );
            return ERROR;
        }
        else if ( explain == YES )
           if ( zaehler > 5000 ) break;   /* Nur 5000 Saetze verarbeiten */

    }      /* ende for */

    EXEC SQL commit work;
    ERROR_MSG( "Commit Work" )

    sprintf( error_msg, "%d Saetze geladen", zaehler );
    PrintMsg( fun, error_msg, HINW, OK );

    printf("tpldzentral: %d Saetze geladen\n", zaehler);
    printf("-->artikelnummer: %ld Update Saetze, %ld Insert Saetze\n", m_lngArtikelNummerUpdates, m_lngArtikelNummerInserts);
    printf("-->artikelzentral: %ld Update Saetze, %ld Insert Saetze\n", m_lngArtikelZentralUpdates, m_lngArtikelZentralInserts);
    printf("-->artikelpreis: %ld Update Saetze, %ld Insert Saetze\n", m_lngArtikelPreisUpdates, m_lngArtikelPreisInserts);
    printf("-->artikelcodes: %ld Update Saetze, %ld Insert Saetze, %ld Delete Saetze\n", m_lngArtikelCodeUpdates, m_lngArtikelCodeInserts, m_lngArtikelCodeDeletes);
    fflush(stdout);

    if ( explain == YES ) return OK;
    rc = OK;
    rc = AfterLoadTables( iTable, error_msg );

    return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( const int iTable, char *error_msg )
{
    int rc = OK;
    if (urladen == YES)
    {
        if ( ( rc = SetNotUpdated( error_msg ) ) < 0 ) return rc;
    }
    if ( ( rc = PrepareHoleArtikelNummern( error_msg ) ) < 0 ) return rc;
    if ( ( rc = PrepareLadeArtikelZentral( error_msg ) ) < 0 ) return rc;
    if ( ( rc = PrepareLadeArtikelnummern( error_msg ) ) < 0 ) return rc;
    PrepareLadeArtikelIndex( error_msg );       /* kein Abbruch bei Fehler! */
    if(swSwiss)
    {
        PrepareLadeArtikelIndexFR( error_msg );     /* kein Abbruch bei Fehler! */
    }
    if(swBulgaria)
    {
        PrepareLadeArticlecodes( error_msg );       /* kein Abbruch bei Fehler! */
    }
    if ( ( rc = PrepareLadeArtikelpreis( error_msg ) ) < 0 ) return rc;
    if ( ( rc = PrepareLadeArtselect( error_msg ) ) < 0 ) return rc;
    if ( ( rc = PrepareLadeLPPR( error_msg ) ) < 0 ) return rc;
    if ( ( rc = PrepareLadeArtSpecial( error_msg ) ) < 0 ) return rc;

   return OK;
}

/***** LOAD-TABLES ***************************************************************/

int LoadTables(const int iTable, char *error_msg)
{
    char *fun = "LoadTables";
    int rc = OK;
    /* neue Tabellen schreiben */

    if (urladen == NO)
    {
        exec sql open Cselzartikel using :artikel_nr;
        ERROR_MSG( "open Cselzartikel" )

        exec sql fetch Cselzartikel into :a;
        ERROR_MSG( "fetch Cselzartikel" )
        if(NOTFOUND) return rc;
    }

    strcpy(LEGALL, "0" );
    strcpy(BREIZH, "0" );
    strcpy(HOSPITAL, "0" );
    strcpy(LPPRType, "0" );
    strcpy(LPPRCode, " " );
    strcpy(EXPORT, "0");

    LPPRProz = 0;
    LPPRWert = 0;
    TFRBasePrice = 0;
    strcpy(REFUNDTYPE, "0" );
    DEUTSCHLANDBESORGER = 0;

    if(swFrance)
    {
        exec sql open Cselzartfr using :artikel_nr;
        ERROR_MSG( "open Cselzartfr" )
            exec sql fetch Cselzartfr into :CODEBLOCAGE,:LPPRType,:LPPRProz,:LPPRWert,:LPPRCode,:LEGALL,:BREIZH,:TFRBasePrice,:EXPORT;
        ERROR_MSG( "fetch Cselzartfr" )
        if(NOTFOUND)
        {
            strcpy(LEGALL, "0" );
            strcpy(BREIZH, "0" );
            strcpy(HOSPITAL, "0" );
            strcpy(LPPRType, "0");
            strcpy(EXPORT, "0" );
            LPPRProz = 0;
            LPPRWert = 0;
            TFRBasePrice = 0;
        }
        else if(CODEBLOCAGE[0] == 'H')
        {
            strcpy(HOSPITAL, "1" );
        }
        if(LPPRType[0] == '1')
        {
            LPPRWert = TFRBasePrice;
        }

        if(LPPRProz > 0)
        {
            exec sql open Cselreimb using :LPPRProz;
            ERROR_MSG( "open Cselreimb" )
            exec sql fetch Cselreimb into :LPPRProz;
            ERROR_MSG( "fetch Cselreimb" )
            if(!NOTFOUND && LPPRType[0] != '1')
            {
                LPPRWert = LPPRWert * LPPRProz / 100;
            }
        }
    }
    strcpy(MEDPROD, "0" );
    if(swAustria)
    {
        exec sql open Cselzartaustria using :artikel_nr;
        ERROR_MSG( "open Cselzartaustria" )
            exec sql fetch Cselzartaustria into :PLPL,:S1S5,:VPL,:SP,:COMPTANT,:NEUFORM,:BDORF,:MEDPROD,:DEUTSCHLANDBESORGER;

        ERROR_MSG( "fetch Cselzartaustria" )
        if(NOTFOUND)
        {
            strcpy(PLPL, "0" );
            strcpy(S1S5, "0" );
            strcpy(VPL, "0" );
            strcpy(SP, "0" );
            strcpy(COMPTANT, "0" );
            strcpy(NEUFORM, "0" );
            strcpy(BDORF, "0" );
            strcpy(MEDPROD, "0" );
            DEUTSCHLANDBESORGER = 0;
        }
    }
    strcpy(IKS_CODE, " " ); //bei allen anderen Ländern auf blank
    if(swSwiss)
    {
        exec sql open Cselzartswiss using :artikel_nr;
        ERROR_MSG( "open Cselzartswiss" )
        exec sql fetch Cselzartswiss into :VERTBINDNURAPO,:VERTBINDNURSPIT,:VERTBINDKUENZLE,:VERTBINDINLAND,:VERTBINDKANTONAL,:VERTBINDPREWHOLE,:VERTBINDLISTEC,:VERTBINDLISTED,:IKS_CODE;

        ERROR_MSG( "fetch Cselzartswiss" )
        if(NOTFOUND)
        {
            strcpy(VERTBINDNURAPO, "0" );
            strcpy(VERTBINDNURSPIT, "0" );
            strcpy(VERTBINDKUENZLE, "0" );
            strcpy(VERTBINDINLAND, "0" );
            strcpy(VERTBINDKANTONAL, "0" );
            strcpy(VERTBINDPREWHOLE, "0" );
            strcpy(VERTBINDLISTEC, "0" );
            strcpy(VERTBINDLISTED, "0" );
            strcpy(IKS_CODE, " " );
        }
        exec sql open Cselzartlang using :artikel_nr;
        ERROR_MSG( "open Cselzartlang" )
        exec sql fetch Cselzartlang into
                :FRMC,
                :FRNAME,
                :FRPACK,
                :FRDF;

        ERROR_MSG( "fetch Cselzartlang" )
        if(NOTFOUND)
        {
            strcpy(FRMC, "\0" );
            strcpy(FRNAME, "\0" );
            strcpy(FRPACK, "\0" );
            strcpy(FRDF, "\0" );
        }
    }

    if(swCroatia)
    {
        exec sql open Cselzartcroatia using :artikel_nr;
        ERROR_MSG( "open Cselzartcroatia" )
        exec sql fetch Cselzartcroatia into :DISTR_RESTR_MED2A,
                                            :DISTR_RESTR_MED2B3,
                                            :DISTR_RESTR_HUDRUG,
                                            :DISTR_RESTR_BRDRUG,
                                            :DISTR_RESTR_ALCOH,
                                            :DISTR_RESTR_VETMED,
                                            :DISTR_RESTR_VEDRUG,
                                            :DISTR_RESTR_HUDRVE;

        ERROR_MSG( "fetch Cselzartcroatia" )
        if(NOTFOUND)
        {
            strcpy(DISTR_RESTR_MED2A, "0" );
            strcpy(DISTR_RESTR_MED2B3, "0" );
            strcpy(DISTR_RESTR_HUDRUG, "0" );
            strcpy(DISTR_RESTR_BRDRUG, "0" );
            strcpy(DISTR_RESTR_ALCOH, "0" );
            strcpy(DISTR_RESTR_VETMED, "0" );
            strcpy(DISTR_RESTR_VEDRUG, "0" );
            strcpy(DISTR_RESTR_HUDRVE, "0" );
        }
    }

    if(swSerbia)
    {
        exec sql open Cselzartserbia using :artikel_nr;
        ERROR_MSG( "open Cselzartserbia" )
        exec sql fetch Cselzartserbia into :REFUNDTYPE,
                                        :DISTR_RESTR_TEND,
                                        :DISTR_RESTR_BETY,
                                        :DISTR_RESTR_BENU,
                                        :DISTR_RESTR_ALRG,
                                        :DISTR_RESTR_CAUD,
                                        :DISTR_RESTR_HEM,
                                        :DISTR_RESTR_GR7,
                                        :DISTR_RESTR_GR8;

        ERROR_MSG( "fetch Cselzartserbia" )
        if(NOTFOUND)
        {
            strcpy(REFUNDTYPE, "0" );
            strcpy(DISTR_RESTR_TEND, "0" );
            strcpy(DISTR_RESTR_BETY, "0" );
            strcpy(DISTR_RESTR_BENU, "0" );
            strcpy(DISTR_RESTR_ALRG, "0" );
            strcpy(DISTR_RESTR_CAUD, "0" );
            strcpy(DISTR_RESTR_HEM, "0" );
            strcpy(DISTR_RESTR_GR7, "0" );
            strcpy(DISTR_RESTR_GR8, "0" );
        }
    }
    PRICEGROUP = 0;
    sList5 = 0;
    if(swBulgaria)
    {
        exec sql open Cselzartbulgaria using :artikel_nr;
        ERROR_MSG( "open Cselzartbulgaria" )
        exec sql fetch Cselzartbulgaria into
            :cond.ARTICLENO,
            :cond.INVOICE_REBATE_PCT,
            :cond.REBATE_IN_KIND_PCT,
            :cond.ANNUAL_INV_REB_PCT,
            :cond.ANNUAL_REB_I_K_PCT,
            :cond.CUST_REB_RED_PCT,
            :cond.HI_REIMBURSEMENT,
            :cond.SUPPL_HI_REIMB,
            :cond.SUPPL_FS_REIMB,
            :cond.SUPPL_DISCOUNT_PCT,
            :cond.YEARLY_BONUS_PCT,
            :cond.OTHER_REBATES_PCT,
            :PRICEGROUP,
            :sList5,
            :DISTR_RESTR_NODRST,
            :DISTR_RESTR_NOWHS;

        ERROR_MSG( "fetch Cselzartbulgaria" )
        if(NOTFOUND)
        {
            cond.ARTICLENO = artikel_nr;
            cond.INVOICE_REBATE_PCT = 0;
            cond.REBATE_IN_KIND_PCT = 0;
            cond.ANNUAL_INV_REB_PCT = 0;
            cond.ANNUAL_REB_I_K_PCT = 0;
            cond.CUST_REB_RED_PCT = 0;
            cond.HI_REIMBURSEMENT = 0;
            cond.SUPPL_HI_REIMB = 0.0;
            cond.SUPPL_FS_REIMB = 0.0;
            cond.SUPPL_DISCOUNT_PCT = 0.0;
            cond.YEARLY_BONUS_PCT = 0.0;
            cond.OTHER_REBATES_PCT = 0.0;
        }
    }

    exec sql open Cselzartsekbez using :artikel_nr;
    ERROR_MSG( "open Cselzartsekbez" )

    exec sql fetch Cselzartsekbez into :s;
    ERROR_MSG( "fetch Cselzartsekbez" )
    if(NOTFOUND || Frankreich)
    {
        strcpy(s.ARTIKEL_MC, " " );
        strcpy(s.ARTIKEL_NAME, " " );
        strcpy(s.BEMERKUNGEN, " " );
    }

    exec sql open Cselzartwg using :artikel_nr;
    ERROR_MSG( "open Cselzartwg" )

    strcpy(WARENGRUPPE, " " );
    strcpy(WARENGRUPPEEIGEN, " " );
    strcpy(THERAPIEGRUPPE, " " );
    strcpy(ABDACODE, " " );
    strcpy(KRANKENHAUSCODE, " " );
    strcpy(TEXTSCHLUESSEL, "0" );
    strcpy(cHEALTHFUNDCODEHOSPITAL, " ");


    for(;;)
    {
        exec sql fetch Cselzartwg into :w;
        ERROR_MSG( "fetch Cselzartwg" )
        if(NOTFOUND) break;
        else if(w.ART[0] == '1')
        {
            strncpy(WARENGRUPPE,w.WARENGRUPPE,5);
        }
        else if(w.ART[0] == '2')
        {
            strncpy(WARENGRUPPEEIGEN,w.WARENGRUPPE,5);
        }
        else if(w.ART[0] == '3')
        {
            strncpy(THERAPIEGRUPPE,w.WARENGRUPPE,5);
        }
        else if(w.ART[0] == '4')
        {
            strncpy(ABDACODE,w.WARENGRUPPE,5);
        }
        else if(w.ART[0] == '7')
        {
            strncpy(TEXTSCHLUESSEL,w.WARENGRUPPE,5);
        }
        else if(w.ART[0] == 'B')
        {
            strncpy(KRANKENHAUSCODE,w.WARENGRUPPE,5);
        }
        else if (w.ART[0] == 'H')
        {
            strncpy(cHEALTHFUNDCODEHOSPITAL, w.WARENGRUPPE, 5);
        }
        //      else if(w.ART[0] == '4') artikel.WARENGRUPPE;
//      else if(w.ART[0] == '5') artikel.WARENGRUPPE;
//      else artikel.WARENGRUPPE;
    }

    //  ATC-Code
    sCode_Type = 2;
    exec sql open Cselcarticlecodes using :artikel_nr,:sCode_Type;
    ERROR_MSG("open Cselcarticlecodes")

    exec sql fetch Cselcarticlecodes into :cATC_Code;
    ERROR_MSG("fetch Cselcarticlecodes")
    if (NOTFOUND)
    {
        strcpy(cATC_Code, " ");
    }
    else
    {
        AllgEntfSpaces(cATC_Code);
    }

    //  MINISTRYPRODUCTCODE
    sCode_Type = 23;
    exec sql open Cselcarticlecodes using :artikel_nr, :sCode_Type;
    ERROR_MSG("open Cselcarticlecodes")

    exec sql fetch Cselcarticlecodes into :cMINISTRYPRODUCTCODE;
    ERROR_MSG("fetch Cselcarticlecodes")
    if (NOTFOUND)
    {
        strcpy(cMINISTRYPRODUCTCODE, " ");
    }
    else
    {
        AllgEntfSpaces(cMINISTRYPRODUCTCODE);
    }

    rc = LadeArtikelpreis(error_msg);
    rc = LadeArtikelZentral(error_msg);
    rc = LadeArtselect(error_msg);
    if(swFrance)
    {
        LadeLPPR(error_msg);
    }
    if(swBulgaria)
    {
        LadeArticlecodes( error_msg );
        LadeArtSpecial(error_msg);
    }

    return rc;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( const int iTable, char *error_msg)
{
    int rc = OK;
    if (urladen == YES)
    {
        if ( ( rc = DelNotUpdated( error_msg ) ) < 0 ) return rc;
    }
    return OK;
}

/*** PREPARE-HOLE-ARTIKEL-NUMMERN ************************************************/

int PrepareHoleArtikelNummern( char *error_msg )
{
    char *fun = "PrepareHoleArtikelNummern";

    exec sql begin declare section;
    exec sql end declare section;

    strcpy(str, "select artikel_nr from ");
    strcat(str, indatenbank);
    strcat(str, ":zapflege ");
    strcat(str, "where datum between ? and ? ");
    strcat(str, "union ");
    strcat(str, "select artikel_nr from ");
    strcat(str, indatenbank);
    strcat(str, ":zpznpflege ");
    strcat(str, "where datum between ? and ? ");

    exec sql prepare sel_zapflege from :str;
    ERROR_MSG( "prepare sel_zapflege" )

    exec sql declare Cselzapflege cursor with hold for sel_zapflege;
    ERROR_MSG("declare Cselzapflege")

    strcpy(str, "select ");
    strcat(str, ZARTIKEL_PELISTE);
    strcat(str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartikel " );
    strcat( str, "where artikel_geloescht != '1'" );

    exec sql prepare sel_zartikelall from :str;
    ERROR_MSG( "prepare sel_zartikelall" )

    exec sql declare Cselzartikelall cursor with hold for sel_zartikelall;

    if (urladen == NO)
    {
        exec sql open Cselzapflege using :datumvon, :datumbis, :datumvon, :datumbis;
        ERROR_MSG( "open Cselzapflege" )
    }
    else
    {
        exec sql open Cselzartikelall;
        ERROR_MSG( "open Cselzartikelall" )
    }

    strcpy( str, "select " );
    strcat( str, ZARTIKEL_PELISTE );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartikel " );
    strcat( str, "where artikel_nr = ?" );

    exec sql prepare sel_zartikel from :str;
    ERROR_MSG( "prepare sel_zartikel" )

    exec sql declare Cselzartikel cursor for sel_zartikel;

    strcpy( str, "select " );
    strcat( str, ZARTWG_PELISTE );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartwg " );
    strcat( str, "where artikel_nr = ?" );

    exec sql prepare sel_zartwg from :str;
    ERROR_MSG( "prepare sel_zartwg" )

    exec sql declare Cselzartwg cursor for sel_zartwg;

    strcpy( str, "select " );
    strcat( str, ZARTSEKBEZ_PELISTE );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartsekbez " );
    strcat( str, "where artikel_nr = ?" );

    exec sql prepare sel_zartsekbez from :str;
    ERROR_MSG( "prepare sel_zartsekbez" )

    exec sql declare Cselzartsekbez cursor for sel_zartsekbez;

    strcpy( str, "select " );
    strcat( str, ZARTPREIS_PELISTE );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartpreis " );
    strcat( str, "where artikel_nr = ? " );
    strcat( str, "and datumgueltigab <= ? " );
    strcat( str, "order by preis_typ,datumgueltigab desc" );

    exec sql prepare sel_zartpreis from :str;
    ERROR_MSG( "prepare sel_zartpreis" )

    exec sql declare Cselzartpreis cursor for sel_zartpreis;

/*  Frankreich spezial */

    strcpy( str, "select " );
    strcat( str, " code_bloquage," );
    strcat( str, " reimbursement_type," );
    strcat( str, " reimbursement_perc," );
    strcat( str, " reimbursement_val," );
    strcat( str, " code_lppr," );
    strcat( str, " distr_restr_legall," );
    strcat( str, " distr_restr_breizh," );
    strcat( str, " tfr_base_price,");
    strcat( str, " distr_restr_export" );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartfrance " );
    strcat( str, "where articleno = ? " );

    exec sql prepare sel_zartfr from :str;
    if ( sqlca.sqlcode == -206 )    /* Tabelle nicht vorhanden */
    {
        swFrance = 0;               /* also auch in Zukunft nicht mehr lesen */
    }
    else
    {
        ERROR_MSG( "prepare sel_zartfr" )
        exec sql declare Cselzartfr cursor for sel_zartfr;
    }
    strcpy( str, "select " );
    strcat( str, " reimbursement_pct" );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":creimbursement_pct " );
    strcat( str, "where reimbursement_pct_id = ? " );

    exec sql prepare sel_reimb from :str;
    if ( sqlca.sqlcode == -206 )    /* Tabelle nicht vorhanden */
    {
    }
    else
    {
        ERROR_MSG( "prepare sel_reimb" )
        exec sql declare Cselreimb cursor for sel_reimb;
    }

/*  Austria spezial */

    strcpy( str, "select " );
    strcat( str, " vertrbind_plpl," );
    strcat( str, " vertrbind_s1s5," );
    strcat( str, " vertrbind_vpl," );
    strcat( str, " vertrbind_sp," );
    strcat( str, " vertrbind_comptant," );
    strcat( str, " vertrbind_neuform," );
    strcat( str, " vertrbind_bdorf," );
    strcat( str, " medprod_abg_verord,");
    strcat( str, " deutschlandbesorger" );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartaustria " );
    strcat( str, "where artikel_nr = ? " );

    exec sql prepare sel_zartaustria from :str;
    if ( sqlca.sqlcode == -206 )    /* Tabelle nicht vorhanden */
    {
        swAustria = 0;              /* also auch in Zukunft nicht mehr lesen */
    }
    else
    {
        ERROR_MSG( "prepare sel_zartaustria" )
        exec sql declare Cselzartaustria cursor for sel_zartaustria;
    }

/*  Croatia spezial */

    strcpy( str, "select " );
    strcat( str, " DISTR_RESTR_MED2A," );
    strcat( str, " DISTR_RESTR_MED2B3," );
    strcat( str, " DISTR_RESTR_HUDRUG," );
    strcat( str, " DISTR_RESTR_BRDRUG," );
    strcat( str, " DISTR_RESTR_ALCOH," );
    strcat( str, " DISTR_RESTR_VETMED," );
    strcat( str, " DISTR_RESTR_VEDRUG," );
    strcat( str, " DISTR_RESTR_HUDRVE" );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartcroatia " );
    strcat( str, "where articleno = ? " );

    exec sql prepare sel_zartcroatia from :str;
    if ( sqlca.sqlcode == -206 )    /* Tabelle nicht vorhanden */
    {
        swCroatia = 0;              /* also auch in Zukunft nicht mehr lesen */
    }
    else
    {
        ERROR_MSG( "prepare sel_zartcroatia" )
        exec sql declare Cselzartcroatia cursor for sel_zartcroatia;
    }

/*  Schweiz spezial */

    strcpy( str, "select " );
    strcat( str, " vertrbind_nur_apo," );
    strcat( str, " vertrbind_nur_spit," );
    strcat( str, " vertrbind_kuenzle," );
    strcat( str, " vertrbind_inland," );
    strcat( str, " vertrbind_kantonal," );
    strcat( str, " vertrbind_prewhole," );
    strcat( str, " vertrbind_liste_c," );
    strcat( str, " vertrbind_liste_d," );
    strcat( str, " iks_code" );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartswitzerland " );
    strcat( str, "where artikel_nr = ? " );

    exec sql prepare sel_zartswiss from :str;
    if ( sqlca.sqlcode == -206 )    /* Tabelle nicht vorhanden */
    {
        swSwiss = 0;                /* also auch in Zukunft nicht mehr lesen */
    }
    else
    {
        ERROR_MSG( "prepare sel_zartswiss" )
        exec sql declare Cselzartswiss cursor for sel_zartswiss;
        ERROR_MSG( "declare Cselzartswiss" )

        strcpy(str, "select " );
        strcat( str, " articlemc," );
        strcat( str, " articlename," );
        strcat( str, " packagingunit," );
        strcat( str, " pharmaform" );
        strcat( str, " from " );
        strcat( str, indatenbank );
        strcat( str, ":carticlelang " );
        strcat( str, "where articleno = ? " );

        exec sql prepare sel_zartlang from :str;
        ERROR_MSG( "prepare sel_zartlang" )
        exec sql declare Cselzartlang cursor for sel_zartlang;
        ERROR_MSG( "declare Cselzartlang" )

    }

/*  Serbia spezial */

    strcpy( str, "select " );
    strcat( str, " refundtype" );
    strcat( str, ",distr_restr_tend" );
    strcat( str, ",distr_restr_bety" );
    strcat( str, ",distr_restr_benu" );
    strcat( str, ",distr_restr_alrg" );
    strcat( str, ",distr_restr_caud" );
    strcat( str, ",distr_restr_hem" );
    strcat( str, ",distr_restr_gr7" );
    strcat( str, ",distr_restr_gr8" );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartserbia " );
    strcat( str, "where articleno = ? " );

    exec sql prepare sel_zartserbia from :str;
    if ( sqlca.sqlcode == -206 )    /* Tabelle nicht vorhanden */
    {
        swSerbia = 0;               /* also auch in Zukunft nicht mehr lesen */
    }
    else
    {
        ERROR_MSG( "prepare sel_zartserbia" )
        exec sql declare Cselzartserbia cursor for sel_zartserbia;
    }

/*  Bulgaria spezial */

    strcpy( str, "select " );
    strcat( str, ARTSPECIALCOND_PELISTE );
    strcat( str, ",PRICE_GROUP" );
    strcat( str, ",LIST_5" );
    strcat( str, ",DISTR_RESTR_NODRST" );
    strcat( str, ",DISTR_RESTR_NOWHS" );
    strcat( str, " from " );
    strcat( str, indatenbank );
    strcat( str, ":zartbulgaria " );
    strcat( str, "where articleno = ? " );

    exec sql prepare sel_zartbulgaria from :str;
    if ( sqlca.sqlcode == -206 )    /* Tabelle nicht vorhanden */
    {
        swBulgaria = 0;             /* also auch in Zukunft nicht mehr lesen */
    }
    else
    {
        ERROR_MSG( "prepare sel_zartbulgaria" )
        exec sql declare Cselzartbulgaria cursor for sel_zartbulgaria;
    }

    strcpy(str, "select ");
    strcat(str, "rr.dateto_custreturns");
    strcat(str, " from ");
    strcat(str, indatenbank);
    strcat(str, ":zchargenrueckruf rr ");
    strcat(str, "where rr.artikel_nr = ? ");
    strcat(str, "and rr.rueckruf_kz='A' ");
    strcat(str, "and rr.einschraenkungen='00' ");
    strcat(str, "and to_char(current,'%Y%m%d')<=rr.dateto_custreturns ");

    /*  Articlecodes */

    strcpy(str, "select ");
    strcat(str, "ARTICLE_CODE");
    strcat(str, " from ");
    strcat(str, indatenbank);
    strcat(str, ":carticlecodes ");
    strcat(str, "where articleno = ? ");
    strcat(str, "and code_type = ? ");

    exec sql prepare sel_carticlecodes from :str;
    ERROR_MSG("prepare sel_carticlecodes")
    exec sql declare Cselcarticlecodes cursor for sel_carticlecodes;

    strcpy(str, "select ");
    strcat(str, "rr.dateto_custreturns");
    strcat(str, " from ");
    strcat(str, indatenbank);
    strcat(str, ":zchargenrueckruf rr ");
    strcat(str, "where rr.artikel_nr = ? ");
    strcat(str, "and rr.rueckruf_kz='A' ");
    strcat(str, "and rr.einschraenkungen='00' ");
    strcat(str, "and to_char(current,'%Y%m%d')<=rr.dateto_custreturns ");

    exec sql prepare sel_zcharge from : str;
    ERROR_MSG("prepare sel_zcharge")

    return OK;
}

/*** PREPARE-LADE-ARTIKEL-ZENTRAL ************************************************/

int PrepareLadeArtikelZentral( char *error_msg )
{
    char *fun = "PrepareLadeArtikelZentral";

    exec sql begin declare section;
    exec sql end declare section;

    strcpy(str, "insert into artikelzentral (" );
    strcat( str, ARTIKELZENTRAL_PELISTE );
    strcat( str, " ) values " );
    strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?," );
    strcat( str,  " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?," );
    strcat( str,  " ?, '0', ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?," );
    strcat( str,  " ?, ?, ?, '1', ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,");
    strcat( str,  " ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )" );

    exec sql prepare ins_artikelzent from :str;
    ERROR_MSG( "prepare ins_artikelzent" )

    strcpy( str, "select " );
    strcat( str, ARTIKELZENTRAL_PELISTE );
    strcat( str, " from artikelzentral where artikel_nr = ? for update " );

    exec sql prepare dec_artikelzent from :str;
    ERROR_MSG( "prepare dec_artikelzent" )
    exec sql declare Cupdartikelzent cursor for dec_artikelzent;

    strcpy( str, "update artikelzentral set " );
    strcat( str, "ARTIKEL_MC = ?," );
    strcat( str, "PACKGROESSE = ?," );
    strcat( str, "DARREICHFORM = ?," );
    strcat( str, "NORMPACKUNG = ?," );
    strcat( str, "EINHEIT = ?," );
    strcat( str, "ARTIKEL_NAME = ?," );
    strcat( str, "ETARTKLASSE1 = ?," );
    strcat( str, "ETARTSCHALTER1 = ?," );
    strcat( str, "ETARTSCHALTER2 = ?," );
    strcat( str, "ETARTSCHALTER3 = ?," );
    strcat( str, "ETARTSCHALTER4 = ?," );
    strcat( str, "ETARTSCHALTER5 = ?," );
    strcat( str, "HERSTELLER_NR = ?," );
    strcat( str, "WARENGRUPPE = ?," );
    strcat( str, "THERAPIEGRUPPE = ?," );
    strcat( str, "LAENGE = ?," );
    strcat( str, "HOEHE = ?," );
    strcat( str, "BREITE = ?," );
    strcat( str, "GEWICHT = ?," );
    strcat( str, "LAUFZEITMONATE = ?," );
    strcat( str, "WARENGRUPPEEIGEN = ?," );
    strcat( str, "KZPSYCHOSTOFFE = ?," );
    strcat( str, "TAXLEVEL = ?," );
    strcat( str, "TEXTKEY_HOSPITAL = ?," );
    strcat( str, "KZRESERVEHOSPITAL = ?, " );
    strcat( str, "STD_MENGE = ?, " );
    strcat( str, "RUNDUNG_STD_MGE = ?, " );
    strcat( str, "NICHT_UEBER_DAFUE = ?, " );
    strcat( str, "NICHT_UEBER_XML = ?, " );
    strcat( str, "WIRKSTOFF_NR = ?, " );
    strcat( str, "HEALTHFUNDCODE = ?, " );
    strcat( str, "STELLER = ?, " );
    strcat( str, "POSITIVLISTE = ?, " );
    strcat( str, "ABDACODE = ?, " );
    strcat( str, "KONSIG_PARTNER_NR = ?, " );
    strcat( str, "ARTIKEL_LANGNAME = ?, " );
    strcat( str, "PRICE_GROUP = ?, " );
    strcat( str, "SORTIMENT_1 = ?, " );
    strcat( str, "SORTIMENT_2 = ?, " );
    strcat( str, "SORTIMENT_3 = ?, " );
    strcat( str, "SORTIMENT_4 = ?, " );
    strcat( str, "SORTIMENT_5 = ?, " );
    strcat( str, "DATUM_ANLAGE = ?, " );
    strcat( str, "BUSINESSTYPENO = ?, " );
    strcat( str, "LISTE_5 = ?, " );
    strcat( str, "UPD_FLAG = '1', " );
    strcat( str, "ARTIKEL_NR_HERST = ?, " );
    strcat( str, "MEDPROD_ABG_VERORD = ?, " );
    strcat( str, "PRODUSERQUOTA = ?, " );
    strcat( str, "MEDICALPRODUCT = ?," );
    strcat( str, "DATEOUTOFTRADE = ?," );
    strcat( str, "ARTIKEL_GESPERRT = ?," );
    strcat( str, "IKS_CODE = ?,");
    strcat( str, "BATCHRECALLDATERETURNS = ?,");
    strcat( str, "IMPORTARTICLE = ?, ");
    strcat( str, "BTM_FAKTOR = ?, ");
    strcat( str, "TFG = ?, ");
    strcat( str, "KONTINGENT_PPE = ?, ");
    strcat( str, "DATUM_LIEFERBAR_AB = ?, ");
    strcat( str, "MEDIZINPRODUKT = ?, ");
    strcat( str, "FROZEN = ?, ");
    strcat( str, "DATUM_AENDER = ?, ");
    strcat( str, "ATC_CODE = ?, ");
    strcat( str, "MINISTRYPRODUCTCODE = ?, ");
    strcat( str, "HEALTHFUNDCODEHOSPITAL = ?, ");
    strcat( str, "CMI_FLAG = ?, ");
    strcat( str, "TAXPFL = ? ");
    strcat( str, "where current of Cupdartikelzent" );
    exec sql prepare upd_artikelzent from :str;
    ERROR_MSG( "prepare upd_artikelzent" )

    return OK;
}

/*** PREPARE-LADE-ARTIKEL-INDEX *************************************************/

int PrepareLadeArtikelIndex( char *error_msg )
{
    char *fun = "PrepareLadeArtikelIndex";

    exec sql begin declare section;
    exec sql end declare section;

    strcpy( str, "delete from artikelindex where current of CupdartikelIdx" );
    exec sql prepare DupdartikelIdx from :str;
    ERROR_MSG( "prepare DupdartikelIdx" );

    strcpy( str, "insert into artikelindex ( artikel_nr, suchbezeichner ) " );
    strcat( str, "values ( ?, ? )" );

    exec sql prepare ins_artikel_idx from :str;
    ERROR_MSG( "prepare ins_artikel_idx" )

    strcpy( str, "select " );
    strcat( str, "artikel_nr " );
    strcat( str, "from artikelindex where artikel_nr = ? for update" );

    exec sql prepare dec_artikel_idx from :str;
    ERROR_MSG( "prepare dec_artikel_idx" )
    exec sql declare CupdartikelIdx cursor for dec_artikel_idx;

    return OK;
}

/*** PREPARE-LADE-ARTIKEL-INDEX-FR *************************************************/

int PrepareLadeArtikelIndexFR( char *error_msg )
{
    char *fun = "PrepareLadeArtikelIndexFR";

    exec sql begin declare section;
    exec sql end declare section;

    strcpy( str, "delete from artikelindexfr where current of CupdartikelIdxFR" );
    exec sql prepare DupdartikelIdxFR from :str;
    ERROR_MSG( "prepare DupdartikelIdxFR" );

    strcpy( str, "insert into artikelindexfr ( artikel_nr, suchbezeichner ) " );
    strcat( str, "values ( ?, ? )" );

    exec sql prepare ins_artikel_idx_FR from :str;
    ERROR_MSG( "prepare ins_artikel_idx_FR" )

    strcpy( str, "select " );
    strcat( str, "artikel_nr " );
    strcat( str, "from artikelindexfr where artikel_nr = ? for update" );

    exec sql prepare dec_artikel_idx_FR from :str;
    ERROR_MSG( "prepare dec_artikel_idx_FR" )
    exec sql declare CupdartikelIdxFR cursor for dec_artikel_idx_FR;

    return OK;
}

/*** PREPARE-LADE-ARTIKEL-CODES ***********************************************/

int PrepareLadeArticlecodes( char *error_msg )
{
    char *fun = "PrepareLadeArticlecodes";

    exec sql begin declare section;
    exec sql end declare section;

    strcpy( str, "insert into articlecodes ( articleno, code_type, article_code, preferred_flag ) " );
    strcat( str, "values ( ?, '15', ?, '0' )" );

    exec sql prepare ins_articlecodes from :str;
    ERROR_MSG( "prepare ins_articlecodes" )

    strcpy( str, "select " );
    strcat( str, "articleno " );
    strcat( str, "from articlecodes " );
    strcat( str, "where articleno = ? " );
    strcat( str, "and code_type = '15' " );
    strcat( str, "for update " );

    exec sql prepare dec_articlecodes from :str;
    ERROR_MSG( "prepare dec_articlecodes" )
    exec sql declare Cupdarticlecodes cursor for dec_articlecodes;

    strcpy( str, "update articlecodes set " );
    strcat( str, "article_code = ? " );
    strcat( str, "where current of Cupdarticlecodes" );

    exec sql prepare upd_articlecodes from :str;
    ERROR_MSG( "prepare upd_articlecodes" )

    strcpy( str, "delete from articlecodes " );
    strcat( str, "where current of Cupdarticlecodes" );

    exec sql prepare del_articlecodes from :str;
    ERROR_MSG( "prepare del_articlecodes" )

    return OK;
}

/*** PREPARE-LADE-ARTIKEL-NUMMERN ***********************************************/

int PrepareLadeArtikelnummern( char *error_msg )
{
    char *fun = "PrepareLadeArtikelnummern";

    exec sql begin declare section;
    exec sql end declare section;

    strcpy( str, "insert into artikelnummern ( pzn , ean , artikel_nr ) " );
    strcat( str, "values ( ?, ?, ? )" );

    exec sql prepare ins_artikelno from :str;
    ERROR_MSG( "prepare ins_artikelno" )

    strcpy( str, "select " );
    strcat( str, "artikel_nr " );
    strcat( str, "from artikelnummern " );
    strcat( str, "where pzn = ? " );
    strcat( str, "and ean = ? " );
    strcat( str, "for update " );

    exec sql prepare dec_artikelno from :str;
    ERROR_MSG( "prepare dec_artikelno" )
    exec sql declare CupdartikelNo cursor for dec_artikelno;

    strcpy( str, "update artikelnummern set " );
    strcat( str, "artikel_nr = ? " );
    strcat( str, ",ean = ? " );
    strcat( str, "where current of CupdartikelNo" );

    exec sql prepare upd_artikelno from :str;
    ERROR_MSG( "prepare upd_artikelno" )

    return OK;
}

/*** PREPARE-LADE-ARTIKELPREIS **************************************************/

int PrepareLadeArtikelpreis( char *error_msg )
{
    char *fun = "PrepareLadeArtikelpreis";

    exec sql begin declare section;
    exec sql end declare section;

    strcpy( str, "insert into artikelpreis (" );
    strcat( str, ARTPREIS_PELISTE );
    strcat( str, " ) values " );
    strcat( str, "( ?, 19950906, 20950906, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )" );

    exec sql prepare ins_artpreis from :str;
    ERROR_MSG( "prepare ins_artpreis" )

    strcpy( str, "select " );
    strcat( str, ARTPREIS_PELISTE );
    strcat( str, " from artikelpreis where artikel_nr = ?   " );
    strcat( str, "and datumgueltigab = ? " );
    strcat( str, "and preis_typ = ? for update " );

    exec sql prepare dec_artikelpreis from :str;
    ERROR_MSG( "prepare dec_artikelpreis" )
    exec sql declare Cupdartikelpreis cursor for dec_artikelpreis;

    strcpy( str, "update artikelpreis set " );
    strcat( str, "PREISEKAPO = ?," );
    strcat( str, "PREISEKGROSSO = ?," );
    strcat( str, "PREISEKGROSSONA = ?," );
    strcat( str, "PREISVKAPO = ?," );
    strcat( str, "RABATTFEST = ?," );
    strcat( str, "RABATTFESTDM = ?," );
    strcat( str, "PREISFEST = ?," );
    strcat( str, "PREISPROZENT = ?," );
    strcat( str, "PREISAGP = ?,");
    strcat( str, "PREIS_TYP = ?, " );
    strcat( str, "MAXAVP = ? " );
    strcat( str, "where current of Cupdartikelpreis" );

    exec sql prepare upd_artpreis from :str;
    ERROR_MSG( "prepare upd_artpreis" )

    return OK;
}

/*** PREPARE-LADE-ARTSELECT *****************************************************/

int PrepareLadeArtselect( char *error_msg )
{
    char *fun = "PrepareLadeArtselect";

    exec sql begin declare section;
    exec sql end declare section;

    strcpy(str,"insert into artselect (");
    strcat( str, ARTSELECT_PELISTE );
    strcat( str, " ) values " );
    strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )" );

    exec sql prepare ins_artselect from :str;
    ERROR_MSG( "prepare ins_artselect" )

    strcpy( str, "select " );
    strcat( str, ARTSELECT_PELISTE );
    strcat( str, " from artselect where ARTIKEL_NR = ? for update " );

    exec sql prepare dec_artselect from :str;
    ERROR_MSG( "prepare dec_artselect" )
    exec sql declare Cupdartselect cursor for dec_artselect;

    strcpy( str, "delete from artselect " );
    strcat( str, "where current of Cupdartselect" );

    exec sql prepare del_artselect from :str;
    ERROR_MSG( "prepare del_artselect" )

    return OK;
}

/*** PREPARE-LADE-ARTIKEL-LPPR *****************************************************/

int PrepareLadeLPPR( char *error_msg )
{
    char *fun = "PrepareLadeLPPR";

    exec sql begin declare section;
    exec sql end declare section;

    strcpy(str,"insert into articlelppr (");
    strcat( str, ARTIKELLPPR_PELISTE );
    strcat( str, " ) values " );
    strcat( str, "( ?, ?, ?, ?, ? )" );

    exec sql prepare ins_artlppr from :str;
    ERROR_MSG( "prepare ins_artlppr" )

    strcpy( str, "select " );
    strcat( str, ARTIKELLPPR_PELISTE );
    strcat( str, " from articlelppr where ARTICLENO = ? for update " );

    exec sql prepare dec_artlppr from :str;
    ERROR_MSG( "prepare dec_artlppr" )
    exec sql declare Cupdartlppr cursor for dec_artlppr;

    strcpy( str, "delete from articlelppr " );
    strcat( str, "where current of Cupdartlppr" );

    exec sql prepare del_artlppr from :str;
    ERROR_MSG( "prepare del_artlppr" )

    return OK;
}

/*** PREPARE-LADE-ARTSPECIAL *****************************************************/

int PrepareLadeArtSpecial( char *error_msg )
{
    char *fun = "PrepareLadeArtSpecial";

    exec sql begin declare section;
    exec sql end declare section;

    strcpy(str,"insert into artspecialcond (");
    strcat( str, ARTSPECIALCOND_PELISTE );
    strcat( str, " ) values " );
    strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )" );

    exec sql prepare ins_artspecial from :str;
    ERROR_MSG( "prepare ins_artspecial" )

    strcpy( str, "select " );
    strcat( str, ARTSPECIALCOND_PELISTE );
    strcat( str, " from artspecialcond where ARTICLENO = ? for update " );

    exec sql prepare dec_artspecial from :str;
    ERROR_MSG( "prepare dec_artspecial" )
    exec sql declare Cupdartspecial cursor for dec_artspecial;

    strcpy( str, "update artspecialcond set " );
    strcat( str, "INVOICE_REBATE_PCT = ?," );
    strcat( str, "REBATE_IN_KIND_PCT = ?," );
    strcat( str, "ANNUAL_INV_REB_PCT = ?," );
    strcat( str, "ANNUAL_REB_I_K_PCT = ?," );
    strcat( str, "CUST_REB_RED_PCT = ?," );
    strcat( str, "HI_REIMBURSEMENT = ?, " );
    strcat( str, "SUPPL_HI_REIMB = ?, " );
    strcat( str, "SUPPL_FS_REIMB = ?, " );
    strcat( str, "SUPPL_DISCOUNT_PCT = ?, " );
    strcat( str, "YEARLY_BONUS_PCT = ?, " );
    strcat( str, "OTHER_REBATES_PCT = ? " );
    strcat( str, "where current of Cupdartspecial" );

    exec sql prepare upd_artspecial from :str;
    ERROR_MSG( "prepare upd_artspecial" )

    return OK;
}

/*** LADE-ARTIKEL-ZENTRAL *********************************************************/

int LadeArtikelZentral(char *error_msg)
{
    int rc;
    char huelse[20];
    int notfound = 0;
    int helpsql;
    char *fun = "LadeArtikelZentral";

    if(a.ARTIKEL_GELOESCHT[0] == '1') return 0; /* Artikel mit Loeschkennzeichen nicht laden */

    exec sql begin declare section;
    struct N_ARTIKELZENTRAL   artikel;                           /* wegen vergleich     */
    long BATCHRECALLDATERETURNS;
    short FROZEN;
    exec sql end declare section;

    if ( ( rc = LadeArtikelnummern( error_msg ) ) < 0 ) return rc;
    /* Es wird bei REGENAPLEX ein BLANC eingebaut! */

    exec sql open Cupdartikelzent using :artikel_nr;
    ERROR_MSG( "open Cupdartikelzent" )

    exec sql fetch Cupdartikelzent into :artikel;
    ERROR_MSG( "fetch Cupdartikelzent" )
    if ( sqlca.sqlcode == 0 )
    {
        notfound = 1;
    }
    else
    {
        notfound = 0;
    }

    a.ARTIKEL_NAME[30] = '\0';
    ArtikelSpezial(a.ARTIKEL_NAME);

    PACKGROESSE = atol(a.EINHEIT);
    if ( a.ARTIKEL_NAME[28] == 'N' )
    {
        strncpy( NORMPACKUNG, ( a.ARTIKEL_NAME ) + 28, 2 );
        NORMPACKUNG[2] = '\0';
    }
    else
    {
        strncpy( NORMPACKUNG, "  ", 2 );
        NORMPACKUNG[2] = '\0';
    }
    ETARTKLASSE1 = 0;
    if ( a.GS_GESUNDHSCH[0] == '1' )    ETARTKLASSE1 += 32768;
    if ( a.GS_GIFTIG[0] == '1' )        ETARTKLASSE1 += 16384;
    if ( a.GS_SEHRGIFTIG[0] == '1' )    ETARTKLASSE1 += 8192;
    if ( a.REZEPTPFL[0] == '1' )        ETARTKLASSE1 += 4096;
    if ( a.APOTHEKENPFL[0] == '1' )     ETARTKLASSE1 += 2048;
    if ( a.TAXPFL[0] == '1' )           ETARTKLASSE1 += 1024;
    if ( a.BTM[0] == '1' )              ETARTKLASSE1 += 512;
    if ( a.TIERARZNEI[0] == '1' )       ETARTKLASSE1 += 256;
    if(swFrance)
    {
        if ( LEGALL[0] == '1' )             ETARTKLASSE1 += 128;
        if ( BREIZH[0] == '1')              ETARTKLASSE1 += 64;
        if ( EXPORT[0] == '1' )             ETARTKLASSE1 += 16;
        if ( a.VERTRBIND[0] == 'B' )        ETARTKLASSE1 += 8;
        if ( a.VERTRBIND[0] == 'C' )        ETARTKLASSE1 += 4;
        if ( a.VERTRBIND[0] == 'D' )        ETARTKLASSE1 += 2;
        if ( a.VERTRBIND[0] == 'E' )        ETARTKLASSE1 += 1;
    }
    else if(swBulgaria)
    {
        if ( PRICEGROUP != 4 )              ETARTKLASSE1 += 128;
        if ( DISTR_RESTR_NODRST == 1 )      ETARTKLASSE1 += 64;
        if ( DISTR_RESTR_NOWHS == 1 )       ETARTKLASSE1 += 32;
        if ( a.VERTRBIND[0] == 'B' )        ETARTKLASSE1 += 8;
        if ( a.VERTRBIND[0] == 'C' )        ETARTKLASSE1 += 4;
        if ( a.VERTRBIND[0] == 'D' )        ETARTKLASSE1 += 2;
        if ( a.VERTRBIND[0] == 'E' )        ETARTKLASSE1 += 1;
    }
    else if(swAustria)
    {
        if ( PLPL[0] == '1' )           ETARTKLASSE1 += 128;
        if ( S1S5[0] == '1' )           ETARTKLASSE1 += 64;
        if ( VPL[0] == '1' )            ETARTKLASSE1 += 32;
        if ( SP[0] == '1' )             ETARTKLASSE1 += 16;
        if ( BDORF[0] == '1' )          ETARTKLASSE1 += 8;
        if ( COMPTANT[0] == 'A' )       ETARTKLASSE1 += 4;
        if ( COMPTANT[0] == 'B' )       ETARTKLASSE1 += 2;
        if ( NEUFORM[0] == '1' )        ETARTKLASSE1 += 1;
    }
    else if(swCroatia)
    {
        if ( DISTR_RESTR_MED2A[0] == '1' )  ETARTKLASSE1 += 128;
        if ( DISTR_RESTR_MED2B3[0] == '1' ) ETARTKLASSE1 += 64;
        if ( DISTR_RESTR_HUDRUG[0] == '1' ) ETARTKLASSE1 += 32;
        if ( DISTR_RESTR_BRDRUG[0] == '1' ) ETARTKLASSE1 += 16;
        if ( DISTR_RESTR_ALCOH[0] == '1' )  ETARTKLASSE1 += 8;
        if ( DISTR_RESTR_VETMED[0] == '1' ) ETARTKLASSE1 += 4;
        if ( DISTR_RESTR_VEDRUG[0] == '1' ) ETARTKLASSE1 += 2;
        if ( DISTR_RESTR_HUDRVE[0] == '1' ) ETARTKLASSE1 += 1;
    }
    else if(swSerbia)
    {
        if ( DISTR_RESTR_TEND[0] == '1' )   ETARTKLASSE1 += 128;
        if ( DISTR_RESTR_BETY[0] == '1' )   ETARTKLASSE1 += 64;
        if ( DISTR_RESTR_BENU[0] == '1' )   ETARTKLASSE1 += 32;
        if ( DISTR_RESTR_ALRG[0] == '1' )   ETARTKLASSE1 += 16;
        if ( DISTR_RESTR_CAUD[0] == '1' )   ETARTKLASSE1 += 8;
        if ( DISTR_RESTR_HEM[0] == '1' )    ETARTKLASSE1 += 4;
        if ( DISTR_RESTR_GR7[0] == '1' )    ETARTKLASSE1 += 2;
        if ( DISTR_RESTR_GR8[0] == '1' )    ETARTKLASSE1 += 1;
    }
    else if(swSwiss)
    {
        if ( VERTBINDNURAPO[0] == '1' )     ETARTKLASSE1 += 128;
        if ( VERTBINDNURSPIT[0] == '1' )    ETARTKLASSE1 += 64;
        if ( VERTBINDKUENZLE[0] == '1' )    ETARTKLASSE1 += 32;
        if ( VERTBINDINLAND[0] == '1' )     ETARTKLASSE1 += 16;
        if ( VERTBINDKANTONAL[0] == '1' )   ETARTKLASSE1 += 8;
        if ( VERTBINDPREWHOLE[0] == '1' )   ETARTKLASSE1 += 4;
        if ( VERTBINDLISTEC[0] == '1' )     ETARTKLASSE1 += 2;
        if ( VERTBINDLISTED[0] == '1' )     ETARTKLASSE1 += 1;
        if ( FRNAME[0] != '\0' )
        {
            exec sql update artikelzentralfr set
                ARTIKEL_MC = :FRMC,
                DARREICHFORM = :FRDF,
                EINHEIT = :FRPACK,
                ARTIKEL_NAME = :FRNAME
            where artikel_nr = :artikel_nr;
            if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
            {
                exec sql insert into artikelzentralfr
                        (ARTIKEL_NR,
                        ARTIKEL_MC,
                        DARREICHFORM,
                        EINHEIT,
                        ARTIKEL_NAME)
                values
                        (:artikel_nr,
                        :FRMC,
                        :FRDF,
                        :FRPACK,
                        :FRNAME);
                ERROR_MSG( "insert artikelzentralfr" )
            }
            else
            {
                ERROR_MSG( "update artikelzentralfr" )
            }
            LadeArtikelIndexFR( artikel.ARTIKEL_NR, FRNAME, error_msg );
        }
    }
    else
    {
        if ( a.VERTRBIND_IFA[0] == '1' )    ETARTKLASSE1 += 128;
        if ( a.VERTRBIND[0] == 'A' )        ETARTKLASSE1 += 64;
        if ( a.VERTRBIND[0] == 'F' )        ETARTKLASSE1 += 32;
        if ( a.VERTRBIND[0] == 'G' )        ETARTKLASSE1 += 16;
        if ( a.VERTRBIND[0] == 'B' )        ETARTKLASSE1 += 8;
        if ( a.VERTRBIND[0] == 'C' )        ETARTKLASSE1 += 4;
        if ( a.VERTRBIND[0] == 'D' )        ETARTKLASSE1 += 2;
        if ( a.VERTRBIND[0] == 'E' )        ETARTKLASSE1 += 1;
    }
//  if ( a.ARTVBB[0] == 'J' )           ETARTKLASSE1 += 32;
//  if ( a.ARTVBC[0] == 'J' )           ETARTKLASSE1 += 16;

    ETARTSCHALTER1 = 0;
//  if ( a.ARTSEBK[0] == 'J' )          ETARTSCHALTER1 += 32768;
//  if ( a.ERSATZ_NR_AKTIV[0] == '1' )  ETARTSCHALTER1 += 16384;
    if ( a.DATUM_AH != 0 )              ETARTSCHALTER1 += 4096;
//  if ( a.ARTAUSL[0] == 'J' )          ETARTSCHALTER1 += 2048;
    if ( a.DATUM_RR != 0 )              ETARTSCHALTER1 += 1024;
/*  if ( a.KUEHLARTIKEL[0] == '1' ) ETARTSCHALTER1 += 128;  */  /* kuehl08 */
/*  if ( a.KUEHLARTIKEL[0] == '2' ) ETARTSCHALTER1 += 64;   */  /* kuehl20 */
/*  if ( a.KUEHLARTIKEL[0] == '4' ) ETARTSCHALTER1 += 32;   */  /* Kuehlkette */
//  if ( a.ARTNLH[0] == 'J' )           ETARTSCHALTER1 += 16;   nase
    if ( a.NICHTUEBERGH[0] == '1' ) ETARTSCHALTER1 += 4;
    if ( a.KLINIKPACKUNG[0] == '1' )    ETARTSCHALTER1 += 2;  /* geaendert 26.05.97*/

    ETARTSCHALTER2 = 0;
    if ( a.MELDEPFL[0] == '1' )     ETARTSCHALTER2 += 32768;
    if ( a.VERFALL[0] == '2' )          ETARTSCHALTER2 += 16384;
    if ( a.VERFALL[0] == '1' )          ETARTSCHALTER2 += 8192;
    if ( cKE_MWST[0] == '1' )           ETARTSCHALTER2 += 2048;
    if ( a.GS_BRAND[0] == '1' ||
        a.GS_EXPLOSION[0] == '1' ||
        a.GS_HOCHENTZ[0] == '1' ||
        a.GS_LEICHTENTZ[0] == '1' ||
        a.GS_AETZEND[0] == '1' )        ETARTSCHALTER2 += 128;

    ETARTSCHALTER3 = 0;
//  if ( a.ARTAFEPR[0] == 'J' )     ETARTSCHALTER3 += 4096; nase
    if ( a.NEGATIVLISTE[0] == '1' ) ETARTSCHALTER3 += 2048;
//  if ( a.ARTPOOL[0] == 'J' )          ETARTSCHALTER3 += 1024; nase
//  if ( a.ARTHOME[0] == 'J' )          ETARTSCHALTER3 += 512;  nase

    if ( a.NURKVA[0] == '1')            ETARTSCHALTER3 += 64;
//  if ( a.ARTPRISMA[0] == 'J')     ETARTSCHALTER3 += 2;

    ETARTSCHALTER4 = 0;
    if ( a.PRODUKTART[0] == '3' )           ETARTSCHALTER4 += 16384;
    if ( a.NAHRUNGSERGAENZUNG[0] == 'G')    ETARTSCHALTER4 += 2;
//  if ( a.ARTGEGU[0] == 'J')               ETARTSCHALTER4 += 1;

    ETARTSCHALTER5 = 0;
    if ( a.ZENTR_EKSPERRE[0] == '1' )   ETARTSCHALTER5 += 32768;
    if ( a.ZYTOSTATIKA[0] == '1')       ETARTSCHALTER5 += 16384;
//  if ( a.ARTSOKO[0] == 'J')           ETARTSCHALTER5 += 8192; nase
    if ( a.BSSICHG[0] == '1')           ETARTSCHALTER5 += 1024;
//  if ( a.ARTZBSP[0] == 'J')           ETARTSCHALTER5 += 512;  nase
//  if ( a.ARTVRIS[0] == 'J')           ETARTSCHALTER5 += 256;  nase

    FROZEN = 0;
    if ( a.KUEHLARTIKEL[0] == '5' ) FROZEN = 1;         /* kuehl -15 / -39 */
    else if ( a.KUEHLARTIKEL[0] == '6') FROZEN = 2;     /* kuehl -40 / -80 */


    sprintf(huelse,"%*.*s",LS_ZARTIKEL_ARZNEIMITTEL,LS_ZARTIKEL_ARZNEIMITTEL,a.ARZNEIMITTEL);
    sMedizin = atoi(huelse);

    exec sql execute sel_zcharge into :BATCHRECALLDATERETURNS using :artikel_nr;
    ERROR_MSG("execute sel_zcharge");
    if (NOTFOUND)
    {
        BATCHRECALLDATERETURNS = 0;
    }

DEBUG_SECTION
END_DEBUG_SECTION

    if ( notfound == 1 )
    {
        if(swBulgaria)
        {
            if ( memcmp( a.ARTIKEL_NAME, artikel.ARTIKEL_NAME, MAX_CH_ARTIKELLANGNAME ) )
            {
                LadeArtikelIndex( artikel.ARTIKEL_NR, a.ARTIKEL_LANGNAME, error_msg );
            }
        }
        else
        {
            if ( memcmp( a.ARTIKEL_LANGNAME, artikel.ARTIKEL_LANGNAME, MAX_CH_ARTIKELNAME ) )
            {
                LadeArtikelIndex( artikel.ARTIKEL_NR, a.ARTIKEL_NAME, error_msg );
            }
        }
        exec sql execute upd_artikelzent using
            :a.ARTIKEL_MC,
            :PACKGROESSE,
            :a.DARREICHFORM,
            :NORMPACKUNG,
            :a.EINHEIT,
            :a.ARTIKEL_NAME,
            :ETARTKLASSE1,
            :ETARTSCHALTER1,
            :ETARTSCHALTER2,
            :ETARTSCHALTER3,
            :ETARTSCHALTER4,
            :ETARTSCHALTER5,
            :a.HERSTELLER_NR,
            :WARENGRUPPE,
            :THERAPIEGRUPPE,
            :a.LAENGE,
            :a.BREITE,
            :a.HOEHE,
            :a.GEWICHT,
            :a.LAUFZEITMONATE,
            :WARENGRUPPEEIGEN,
            :a.PSYCHOTROP,
            :cKE_MWST,
            :TEXTSCHLUESSEL,
            :HOSPITAL,
            :a.STD_MENGE,
            :a.RUNDUNG_STD_MGE,
            :a.NICHT_UEBER_DAFUE,
            :a.NICHT_UEBER_XML,
            :a.WIRKSTOFF_NR,
            :KRANKENHAUSCODE,
            :a.STELLER,
            :REFUNDTYPE,
            :ABDACODE,
            :a.KONSIG_PARTNER_NR,
            :a.ARTIKEL_LANGNAME,
            :PRICEGROUP,
            :a.SORTIMENT_1,
            :a.SORTIMENT_2,
            :a.SORTIMENT_3,
            :a.SORTIMENT_4,
            :a.SORTIMENT_5,
            :a.DATUM_ANLAGE,
            :a.BUSINESSTYPENO,
            :sList5,
            :a.ARTIKEL_NR_HERST,
            :MEDPROD,
            :a.HERST_KONTINGENT,
            :sMedizin,
            :a.DATUM_AH,
            :a.ARTIKEL_GESPERRT,
            :IKS_CODE,
            :BATCHRECALLDATERETURNS,
            :DEUTSCHLANDBESORGER,
            :a.BTM_FAKTOR,
            :a.TFG,
            :a.KONTINGENT_PPE,
            :a.DATUM_LIEFERBAR_AB,
            :a.MEDIZINPRODUKT,
            :FROZEN,
            :a.DATUM_AENDER,
            :cATC_Code,
            :cMINISTRYPRODUCTCODE,
            :cHEALTHFUNDCODEHOSPITAL,
            :a.CMI_FLAG,
            :a.TAXPFL
        ;

        ERROR_MSG( "execute upd_artikelzent" )
        m_lngArtikelZentralUpdates++;
        return 0;
    }

    if(swBulgaria)
    {
        LadeArtikelIndex( artikel.ARTIKEL_NR, a.ARTIKEL_LANGNAME, error_msg );
    }
    else
    {
        LadeArtikelIndex( a.ARTIKEL_NR, a.ARTIKEL_NAME, error_msg );
    }
    EXEC SQL EXECUTE ins_artikelzent USING
            :artikel_nr,
            :a.ARTIKEL_MC,
            :PACKGROESSE,
            :a.DARREICHFORM,
            :NORMPACKUNG,
            :a.EINHEIT,
            :a.ARTIKEL_NAME,
            :ETARTKLASSE1,
            :ETARTSCHALTER1,
            :ETARTSCHALTER2,
            :ETARTSCHALTER3,
            :ETARTSCHALTER4,
            :ETARTSCHALTER5,
            :a.HERSTELLER_NR,
            :WARENGRUPPE,
            :THERAPIEGRUPPE,
            :a.LAENGE,
            :a.BREITE,
            :a.HOEHE,
            :a.GEWICHT,
            :a.LAUFZEITMONATE,
            :WARENGRUPPEEIGEN,
            ' ',
            :a.PSYCHOTROP,
            :cKE_MWST,
            :TEXTSCHLUESSEL,
            :HOSPITAL,
            :a.STD_MENGE,
            :a.RUNDUNG_STD_MGE,
            :a.NICHT_UEBER_DAFUE,
            :a.NICHT_UEBER_XML,
            :a.WIRKSTOFF_NR,
            :KRANKENHAUSCODE,
            :a.STELLER,
            :REFUNDTYPE,
            :ABDACODE,
            :a.KONSIG_PARTNER_NR,
            :a.ARTIKEL_LANGNAME,
            :PRICEGROUP,
            :a.SORTIMENT_1,
            :a.SORTIMENT_2,
            :a.SORTIMENT_3,
            :a.SORTIMENT_4,
            :a.SORTIMENT_5,
            :a.DATUM_ANLAGE,
            :a.BUSINESSTYPENO,
            :sList5,
            :a.ARTIKEL_NR_HERST,
            :MEDPROD,
            :a.HERST_KONTINGENT,
            :sMedizin,
            :a.DATUM_AH,
            :a.ARTIKEL_GESPERRT,
            :IKS_CODE,
            :BATCHRECALLDATERETURNS,
            :DEUTSCHLANDBESORGER,
            :a.BTM_FAKTOR,
            :a.TFG,
            :a.KONTINGENT_PPE,
            :a.DATUM_LIEFERBAR_AB,
            :a.MEDIZINPRODUKT,
            :FROZEN,
            :a.DATUM_AENDER,
            :cATC_Code,
            :cMINISTRYPRODUCTCODE,
            :cHEALTHFUNDCODEHOSPITAL,
            :a.CMI_FLAG,
            :a.TAXPFL
        ;

    if ( SQLCODE == -391 )
    {
        helpsql = SQLCODE;
    }

    ERROR_MSG( "insert Artikelzentral" );
    m_lngArtikelZentralInserts++;

    return 0;
}

/*** LADE-ARTIKEL-INDEX ******************************************************/

int LadeArtikelIndex( long artikelnr, char *ARTBEZ, char *error_msg )
{
    exec sql begin declare section;
    long ArtikelNr;
    char *MatchCode;
    char artbez[51];
    exec sql end declare section;
    int i;
    int len;
    static int maxerror;

    char *fun = "LadeArtikelIndex";

    ArtikelNr = artikelnr;
    strcpy(artbez,ARTBEZ);

    exec sql open CupdartikelIdx using :ArtikelNr;

    while ( SQLCODE == OK )
    {
        exec sql fetch CupdartikelIdx;
        if ( SQLCODE == 0 )
            exec sql execute DupdartikelIdx;   /* delete */
    }

    if ( SQLCODE < 0 )
    {
        if ( maxerror++ > 5 )
            return -1;
        ERROR_MSG( "delete artikelindex" )
    }

    exec sql close CupdartikelIdx;
    ERROR_MSG( "close CupdartikelIdx" )

    if(swBulgaria)
    {
        artbez[MAX_CH_ARTIKELLANGNAME] = '\0';
    }
    else
    {
        artbez[MAX_CH_ARTIKELNAME] = '\0';
    }
    for( i = strlen(artbez) - 1; i >= 0; i-- )
    {
        if ( artbez[i] != ' '   )
        {
            artbez[i+1] = '\0';
            break;
        }
    }

    if ( i < 0 )
        return 0;       /* Kein Name eingetragen */

    len = i + 1 - 2;    /* bis 3 bst             */
    for ( i = 0; i < len && SQLCODE == OK; i++ )
    {
        MatchCode = artbez + i;
        exec sql execute ins_artikel_idx using :ArtikelNr, :MatchCode;
    }

    ERROR_MSG( "insert artikelindex" )

    return OK;
}

/*** LADE-ARTIKEL-INDEX-FR ******************************************************/

int LadeArtikelIndexFR( long artikelnr, char *ARTBEZ, char *error_msg )
{
    exec sql begin declare section;
    long ArtikelNr;
    char *MatchCode;
    char artbez[31];
    exec sql end declare section;
    int i;
    int len;
    static int maxerror;

    char *fun = "LadeArtikelIndexFR";

    ArtikelNr = artikelnr;
    strcpy(artbez,ARTBEZ);

    exec sql open CupdartikelIdxFR using :ArtikelNr;

    while ( SQLCODE == OK )
    {
        exec sql fetch CupdartikelIdxFR;
        if ( SQLCODE == 0 )
            exec sql execute DupdartikelIdxFR;   /* delete */
    }

    if ( SQLCODE < 0 )
    {
        if ( maxerror++ > 5 )
            return -1;
        ERROR_MSG( "delete artikelindexFR" )
    }

    exec sql close CupdartikelIdxFR;
    ERROR_MSG( "close CupdartikelIdxFR" )

    artbez[MAX_CH_ARTIKELNAME] = '\0';
    for( i = strlen(artbez) - 1; i >= 0; i-- )
    {
        if ( artbez[i] != ' '   )
        {
            artbez[i+1] = '\0';
            break;
        }
    }

    if ( i < 0 )
        return 0;       /* Kein Name eingetragen */

    len = i + 1 - 2;    /* bis 3 bst             */
    for ( i = 0; i < len && SQLCODE == OK; i++ )
    {
        MatchCode = artbez + i;
        exec sql execute ins_artikel_idx_FR using :ArtikelNr, :MatchCode;
    }

    ERROR_MSG( "insert artikelindexFR" )

    return OK;
}

/*** LADE-ARTIKEL-CODES ****************************************************/

int LadeArticlecodes( char *error_msg)
{
    char *fun = "LadeArticlecodes";

    exec sql begin declare section;
    long articleno;
    exec sql end declare section;

    exec sql open Cupdarticlecodes using :artikel_nr;
    ERROR_MSG( "open Cupdarticlecodes" )

    exec sql fetch Cupdarticlecodes into :articleno;
    ERROR_MSG( "fetch Cupdarticlecodes" )

    AllgEntfSpaces(KRANKENHAUSCODE);

    if ( SQLCODE != 0 )
    {
        if(strlen(KRANKENHAUSCODE) < 2) return OK;

        EXEC SQL EXECUTE ins_articlecodes USING
                  :artikel_nr,
                  :KRANKENHAUSCODE;
        ERROR_MSG("insert articlecodes")
        m_lngArtikelCodeInserts++;
    }
    else
    {
        if(strlen(KRANKENHAUSCODE) < 2)
        {
            EXEC SQL EXECUTE del_articlecodes;
            ERROR_MSG( "delete articlecodes" )
            m_lngArtikelCodeDeletes++;
        }
        else
        {
            EXEC SQL EXECUTE upd_articlecodes USING
                  :KRANKENHAUSCODE;
            ERROR_MSG( "update articlecodes" )
            m_lngArtikelCodeUpdates++;
        }
    }

    return OK;
}

/*** LADE-ARTIKEL-NUMMERN ****************************************************/

int LadeArtikelnummern( char *error_msg)
{
    char *fun = "LadeArtikelnummern";

    exec sql begin declare section;
    long artikelnr;
    char EAN[14];
    exec sql end declare section;

    sprintf(EAN,"%07d",artikel_nr);

    exec sql open CupdartikelNo using :artikel_nr,:EAN;
    ERROR_MSG( "open CupdartikelNo" )

    exec sql fetch CupdartikelNo into :artikelnr;
    ERROR_MSG( "fetch CupdartikelNo" )

    if ( SQLCODE != 0 )
    {
        EXEC SQL EXECUTE ins_artikelno USING
                  :artikel_nr,
                  :EAN,
                  :artikel_nr;
        ERROR_MSG( "insert artikelnummern" )
        m_lngArtikelNummerInserts++;
    }
    else
    {
        if(artikelnr != a.ARTIKEL_NR)
        {
            EXEC SQL EXECUTE upd_artikelno USING
                  :artikel_nr,
                  :EAN;
            ERROR_MSG( "update artikelnummern" )
            m_lngArtikelNummerUpdates++;
        }
    }

    return OK;

}

/*** LADE-ARTIKEL-SEKBEZ ********************************************************/

int LadeArtikelsekbez( char *error_msg )
{
    char *fun = "LadeArtikelsekbez";

    exec sql open Cupdartikelsek using :artikel_nr;
    ERROR_MSG( "open Cupdartikelsek" )

    for(;;)
    {
        exec sql fetch Cupdartikelsek;
        ERROR_MSG( "fetch Cupdartikelsek" )

        if ( sqlca.sqlcode == 0 )
        {
            EXEC SQL EXECUTE del_artsek;
            ERROR_MSG( "execute upd_artsek" )
        }
        if ( sqlca.sqlcode == 100 ) break;
    }

    if ( strncmp(a.ARTIKEL_MC, "             ", 12 ) != 0 )
    {
        EXEC SQL EXECUTE ins_artsek USING
            :s.ARTIKEL_MC,
            :artikel_nr,
            :s.ARTIKEL_NAME;
        ERROR_MSG( "insert artikelsekbez" )
    }

    return OK;
}

/*** LADE-ARTIKEL-PREIS *********************************************************/

int LadeArtikelpreis( char *error_msg)
{
    char *fun = "LadeArtikelpreis";
    short preistyp;

    exec sql begin declare section;
    struct N_ZARTPREIS  p;
    char *FestDatum = "19950906";          /* ist immer geschrieben in Step1 */
    double grosso;
    double grossona;
    exec sql end declare section;

    dAEP = dAVP = dAGP = 0;
    strcpy(cKE_MWST, "0" );

    preistyp = -1;

    exec sql open Cselzartpreis using :artikel_nr,:datumpreis;
    ERROR_MSG( "open Cselzartpreis" )

    for(;;)
    {
        exec sql fetch Cselzartpreis into :p;
        ERROR_MSG( "fetch Cselzartpreis" )
        if(NOTFOUND) break;
        if(preistyp == p.PREIS_TYP) continue;
        preistyp = p.PREIS_TYP;
        if(p.KE_MWST[0] == '\0') strcpy(p.KE_MWST, "0" );
        else if(p.KE_MWST[0] == ' ') strcpy(p.KE_MWST, "0" );
        strcpy(cKE_MWST,p.KE_MWST);

        if (p.AVP == 0 && p.EAVP > 0) p.AVP = p.EAVP;
        if (dAEP == 0) dAEP = p.AEP;
        if (dAVP == 0) dAVP = p.AVP;
        if (dAGP == 0) dAGP = p.AGP;

        grossona = 0.00;
        if(swBulgaria)
        {
            grossona = (p.GROSSO * ((1 - cond.INVOICE_REBATE_PCT/100)/(1+cond.REBATE_IN_KIND_PCT/100))) + 0.0001;
            Runden(&grossona,2);
        }

        exec sql open Cupdartikelpreis using :artikel_nr, :FestDatum, :p.PREIS_TYP;
        ERROR_MSG( "open Cupdartikelpreis" )

        exec sql fetch Cupdartikelpreis;
        ERROR_MSG( "fetch Cupdartikelpreis" )

        if ( sqlca.sqlcode == 0 )
        {
            EXEC SQL EXECUTE upd_artpreis USING
                :p.AEP,
                :p.GROSSO,
                :grossona,
                :p.AVP,
                '0',                /*:a.RABATTFEST,  nase  */
                :a.FESTBETRAG1,
                '0',                /*:a.PREISFEST, nase    */
                :a.PERSONALRABATT,
                :p.AGP,
                :p.PREIS_TYP,
                :p.MAXAVP;
            ERROR_MSG("execute upd_artpreis")
            m_lngArtikelPreisUpdates++;
            continue;
        }

        EXEC SQL EXECUTE ins_artpreis USING
            :a.ARTIKEL_NR,
            :p.AEP,
            :p.GROSSO,
            :grossona,
            :p.AVP,
            '0',                /*:a.RABATTFEST,  nase  */
            :a.FESTBETRAG1,
            '0',                /*:a.PREISFEST, nase    */
            :a.PERSONALRABATT,
            :p.AGP,
            :p.PREIS_TYP,
            :p.MAXAVP;
        ERROR_MSG( "insert artikelpreis" )
        m_lngArtikelPreisInserts++;
    }

    return OK;
}

/*** LADE-ARTSELECT *************************************************************/

int LadeArtselect( char *error_msg )
{
    char *fun = "LadeArtselect";

    exec sql begin declare section;
    long etarschalter1;
    exec sql end declare section;

    exec sql open Cupdartselect using :artikel_nr;
    ERROR_MSG( "open Cupdartselect" )

    for( ;; )
    {

        exec sql fetch Cupdartselect;
        ERROR_MSG( "fetch Cupdartselect" )

        if ( sqlca.sqlcode == 0 )
        {

            EXEC SQL EXECUTE del_artselect;
            ERROR_MSG( "execute del_artselect" )
        }
        else
            break;
    }


    EXEC SQL EXECUTE ins_artselect USING
            :artikel_nr,
            :a.ARTIKEL_MC,
            :PACKGROESSE,
            :a.DARREICHFORM,
            :a.EINHEIT,
            :a.ARTIKEL_NAME,
            :ETARTSCHALTER1,
            :ETARTSCHALTER2,
            :ETARTSCHALTER3,
            :ETARTSCHALTER4,
            '0',
            '0',
            '0',
            :dAEP
          ;

    ERROR_MSG( "insert artselect" )
    if ( strncmp( s.ARTIKEL_MC, " ", 1 ) != 0 )
    {
        etarschalter1 = ETARTSCHALTER1;
        etarschalter1 += 32768;

        DEBUG_SECTION
        printf( "artikelnr: *%d*\n", artikel_nr );
        printf( "ARTIKEL_MC: *%s*\n", s.ARTIKEL_MC );
        printf( "packgroesse: *%d*\n", PACKGROESSE );
        printf( "DARREICHFORM: *%s*\n", a.DARREICHFORM );
        printf( "EINHEIT: *%s*\n", a.EINHEIT );
        printf( "ARTIKEL_NAME: *%s*\n", a.ARTIKEL_NAME );
        printf( "packgroesse: *%lf*\n", dAEP );
        END_DEBUG_SECTION

        EXEC SQL EXECUTE ins_artselect USING
            :artikel_nr,
            :s.ARTIKEL_MC,
            :PACKGROESSE,
            :a.DARREICHFORM,
            :a.EINHEIT,
            :s.ARTIKEL_NAME,
            :etarschalter1,
            :ETARTSCHALTER2,
            :ETARTSCHALTER3,
            :ETARTSCHALTER4,
            '0',
            '0',
            '0',
            :dAEP
          ;
     ERROR_MSG( "insert artselect2" );
    }
    if(swSwiss)
    {
        if ( FRNAME[0] != '\0' )
        {
            exec sql update artselectfr set
                ARTIKEL_MC = :FRMC,
                DARREICHFORM = :FRDF,
                EINHEIT = :FRPACK,
                ARTIKEL_NAME = :FRNAME,
                ETARTSCHALTER1 = :ETARTSCHALTER1
            where artikel_nr = :artikel_nr;
            if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
            {
                exec sql insert into artselectfr
                        (ARTIKEL_NR,
                        ARTIKEL_MC,
                        DARREICHFORM,
                        EINHEIT,
                        ARTIKEL_NAME,
                        ETARTSCHALTER1)
                values
                        (:artikel_nr,
                        :FRMC,
                        :FRDF,
                        :FRPACK,
                        :FRNAME,
                        :ETARTSCHALTER1);
                ERROR_MSG( "insert artselectfr" )
            }
            else
            {
                ERROR_MSG( "update artselectfr" )
            }
        }
    }

   return OK;
}

/*** LADE-ARTIKEL-LPPR *************************************************************/

int LadeLPPR( char *error_msg )
{
    char *fun = "LadeLPPR";

    exec sql begin declare section;
    long etarschalter1;
    exec sql end declare section;

    if(LPPRType[0] == '2')  return OK;  /* neue Tabellen */

    exec sql open Cupdartlppr using :artikel_nr;
    ERROR_MSG( "open Cupdartlppr" )

    for( ;; )
    {

        exec sql fetch Cupdartlppr;
        ERROR_MSG( "fetch Cupdartlppr" )

        if ( sqlca.sqlcode == 0 )
        {

            EXEC SQL EXECUTE del_artlppr;
            ERROR_MSG( "execute del_artlppr" )
        }
        else
            break;
    }

    if(LPPRType[0] == '0') return OK;
    else if(LPPRType[0] == '1')
    {
        if(LPPRWert == 0)
        {
            if(LPPRProz == 0)
            {
                return OK;
            }
            LPPRWert = (dAVP * LPPRProz) / 100;
        }
    }
    else if(LPPRType[0] == '2')
    {   /*  Werte stehen in lpprcode-tabelle
        if(LPPRWert == 0)
        {
            if(LPPRProz == 0)
            {
                return OK;
            }
            LPPRWert = (dAVP * LPPRProz) / 100;
        }
*/  }
    else if(LPPRType[0] == '3')
    {
        if(LPPRWert == 0)
        {
            if(LPPRProz == 0)
            {
                return OK;
            }
            LPPRWert = (dAVP * LPPRProz) / 100;
        }
    }
    else
    {
        return OK;
    }

    EXEC SQL EXECUTE ins_artlppr USING
            :artikel_nr,
            :LPPRType,
            :LPPRWert,
            :LPPRCode,
            :LPPRProz
          ;

    ERROR_MSG( "insert articlelppr" )
    return OK;
}

/*** LADE-ARTIKEL-ARTSPECIALCOND *************************************************************/

int LadeArtSpecial( char *error_msg )
{
    char *fun = "LadeArtSpecial";

    exec sql open Cupdartspecial using :artikel_nr;
    ERROR_MSG( "open Cupdartspecial" )

    exec sql fetch Cupdartspecial;
    ERROR_MSG( "fetch Cupdartspecial" )

    if ( sqlca.sqlcode == 0 )
    {
        EXEC SQL EXECUTE upd_artspecial USING
            :cond.INVOICE_REBATE_PCT,
            :cond.REBATE_IN_KIND_PCT,
            :cond.ANNUAL_INV_REB_PCT,
            :cond.ANNUAL_REB_I_K_PCT,
            :cond.CUST_REB_RED_PCT,
            :cond.HI_REIMBURSEMENT,
            :cond.SUPPL_HI_REIMB,
            :cond.SUPPL_FS_REIMB,
            :cond.SUPPL_DISCOUNT_PCT,
            :cond.YEARLY_BONUS_PCT,
            :cond.OTHER_REBATES_PCT;
        ERROR_MSG( "execute upd_artspecial" )
    }
    else
    {
        EXEC SQL EXECUTE ins_artspecial USING
            :cond.ARTICLENO,
            :cond.INVOICE_REBATE_PCT,
            :cond.REBATE_IN_KIND_PCT,
            :cond.ANNUAL_INV_REB_PCT,
            :cond.ANNUAL_REB_I_K_PCT,
            :cond.CUST_REB_RED_PCT,
            :cond.HI_REIMBURSEMENT,
            :cond.SUPPL_HI_REIMB,
            :cond.SUPPL_FS_REIMB,
            :cond.SUPPL_DISCOUNT_PCT,
            :cond.YEARLY_BONUS_PCT,
            :cond.OTHER_REBATES_PCT;
        ERROR_MSG( "execute ins_artspecial" )
    }
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
    char logFile[L_TEXT];
    char *env;

    if ( rc > INSERT )
        return;

    pid = getpid();
    hour1 = time( &hour1 );
    zeit  = localtime( &hour1 );

/*  sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) ); */
    env = getenv( "LOG_PATH" );
    if ( env == NULL )
        env = ".";
    sprintf( logFile, "%s/wws.log", env );

    if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
        return;

    fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.11s %s %s\n",
        mld,
        99,
        zeit->tm_mday,
        zeit->tm_mon + 1,
        (zeit->tm_year+1900)%100,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
        pid,
        "tpldzentral",
        fun,
        error_msg );

    fclose(fp);
}

/***** CLOSE-DATABASE *******************************************************/

int CloseDatabase( void )
{
    char error_msg[L_TEXT];
    char *fun = "CloseDatabase";

    exec sql close database;
    ERROR_MSG( "Close DB" )

    return OK;
}

void Runden( double *wert, int stellen )
{
    if ( stellen >= 0 )
    {
        int i;
        double rund;
        double result;
        double rest;

        rund = 1.0;
        for ( i = 0; i < stellen; i++ ) rund *= 10.0;

        i = 1;
        result = *wert;
        if ( result < 0.0 )
        {
            result = -result;
            i = -1;
        }

        rest = modf( result*rund + 0.5, &result );

        if ( rest >= 0.99999999 )
            result += 1.0;

        result /= rund;
        if ( i == 1 )
            *wert = result;
        else
            *wert = -result;
    }
}

/*** KENNZEICHNEN-ARTIKELZENTRAL-NICHT-GEAENDERT ***********************************************/

int SetNotUpdated( char *error_msg )
{
    char *fun = "SetNotUpdated";

    exec sql begin declare section;
    long lArtNr;
    exec sql end declare section;

    strcpy( str, "select " );
    strcat( str, "artikel_nr " );
    strcat( str, "from artikelzentral " );
    strcat( str, "where upd_flag != '0' " );
    strcat( str, "for update " );

    exec sql prepare dec_setnot from :str;
    ERROR_MSG( "prepare dec_setnot" )
    exec sql declare CSetNot cursor with hold for dec_setnot;

    strcpy( str, "update artikelzentral set " );
    strcat( str, "upd_flag = '0' " );
    strcat( str, "where current of CSetNot" );

    exec sql prepare upd_setnot from :str;
    ERROR_MSG( "prepare upd_setnot" )

    EXEC SQL BEGIN WORK;
    ERROR_MSG( "begin work" )

    EXEC SQL OPEN CSetNot;
    ERROR_MSG( "open CSetNot" )

    for(int count = 0;;)
    {
        EXEC SQL FETCH CSetNot into :lArtNr;
        ERROR_MSG( "fetch CSetNot" )
        if(NOTFOUND) break;

        EXEC SQL EXECUTE upd_setnot;
        ERROR_MSG( "execute upd_setnot" )
        if ( count++ % M_DURCHLAUF_COMMIT == 0)
        {
            EXEC SQL COMMIT WORK;
            ERROR_MSG( "commit work between" )

            EXEC SQL BEGIN WORK;
            ERROR_MSG( "begin work between" )
        }
    }

    EXEC SQL COMMIT WORK;
    ERROR_MSG( "commit work" )

    return OK;
}

/*** LOESCHEN-ARTIKELZENTRAL-NICHT-GEAENDERT ***********************************************/

int DelNotUpdated( char *error_msg )
{
    char *fun = "DelNotUpdated";
    char del_msg[80];

    exec sql begin declare section;
    long lArtNr;
    exec sql end declare section;

    strcpy( str, "select " );
    strcat( str, "artikel_nr " );
    strcat( str, "from artikelzentral " );
    strcat( str, "where upd_flag != '1' " );
    strcat( str, "for update " );

    exec sql prepare dec_delnot from :str;
    ERROR_MSG( "prepare dec_delnot" )
    exec sql declare CDelNot cursor with hold for dec_delnot;

    strcpy( str, "delete from artikelzentral " );
    strcat( str, "where current of CDelNot" );

    exec sql prepare del_setnot from :str;
    ERROR_MSG( "prepare del_setnot" )

    EXEC SQL BEGIN WORK;
    ERROR_MSG( "begin work" )

    EXEC SQL OPEN CDelNot;
    ERROR_MSG( "open CDelNot" )

    for(int count = 0;;)
    {
        EXEC SQL FETCH CDelNot into :lArtNr;
        ERROR_MSG( "fetch CDelNot" )
        if(NOTFOUND)
        {
            sprintf(del_msg,"%d",count);
            PrintMsg( "Saetze geloescht: ", del_msg, HINW, 0 );
            break;
        }

        EXEC SQL EXECUTE del_setnot;
        ERROR_MSG( "execute del_setnot" )
        if ( count++ % M_DURCHLAUF_COMMIT == 0)
        {
            EXEC SQL COMMIT WORK;
            ERROR_MSG( "commit work between" )

            EXEC SQL BEGIN WORK;
            ERROR_MSG( "begin work between" )
        }
    }

    EXEC SQL COMMIT WORK;
    ERROR_MSG( "commit work" )

    return OK;
}

/***** ENDE *****************************************************************/

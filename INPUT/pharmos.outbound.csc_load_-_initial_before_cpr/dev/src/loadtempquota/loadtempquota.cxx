/********************************************************************************/
/*     Hauptmodul: loadtempquota.ecc                                            */
/*         Source:                                                              */
/*          Autor: Ronald Imschweiler                                           */
/*       Erstellt: 21.01.2009                                                   */
/*        Sprache: C                                                            */
/*        Erzeugt: manuell                                                      */
/*        Aufgabe: Übernehmen und Löschen temporäre Kontingente                 */
/*         Aufruf: loadtempquota                                                */
/*                                                                              */
/********************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME  "loadtempquota"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/********************************************************************************/
/* INCLUDE */
/********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "pplib/allg.h"
#include "quotatemp.h"
EXEC SQL include sqlca;

/********************************************************************************/
/* DEFINE */
/********************************************************************************/
#define MAX_TRANSAKTION 300
typedef struct timeval timeval_t;
#define SQLNOTFOUND 100
#define SQLEXISTS -239
#define SQLCODE sqlca.sqlcode            /* Sql-Fehler */
/********************************************************************************/
/* MACROS */
/********************************************************************************/
#define ERROR_MSG( x )      if( SQLCODE < 0 ){                                          \
                                sprintf( error_msg, "%s %d/%d %s", x,                   \
                                    sqlca.sqlcode, sqlca.sqlerrd[1],sqlca.sqlerrm );    \
                                PrintMsg( fun, error_msg, 'F' );                        \
                                return -1;                                              \
                            }

/********************************************************************************/
/* MODUL-GLOBALE VARIABLEN */
/********************************************************************************/
static int iNumberOfDay = 0;
static long delcount    = 0;
static long reakcount   = 0;
static long inscount    = 0;
static long savecount   = 0;

static int  bVersion    = FALSE;

char error_msg[512];
exec sql begin declare section;
int lDatum;
quotatempS TempQuota;
char* spDatabase;
exec sql end declare section;

struct TempVector
{
    quotatempS Temp;
    struct TempVector* nextpos;
};
struct TempVector* startpos;
struct TempVector* actpos;
struct TempVector* newpos;


/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
int main( int, char** );
static int  KommandoZeileEinlesen( int argc, char** argv );
static int  oeffneDB();
static int  schliesseDB();
static int  PrepareLoadTemp();
static int  PrepareDeleteTemp();
static int  LoadTemp();
static int  DeleteTemp();
static void PrintMsg(char* fun, char* error_msg, char mld );


/********************************************************************************/
/* int main( int argc, char** argv ) */
/********************************************************************************/
int main( int argc, char* argv[] )
{
    char *fun = "main";

    setbuf(stdout, 0);

    /*****************************************************/
    /* Aufrufparameter werden ausgelesen */
    /*****************************************************/
    if( !KommandoZeileEinlesen( argc, argv ) == 0 )
    {
        printf( "Aufruf: loadtempquota -db Datenbank\n" );
        return 1;
    }
    if(bVersion) return 0;

    sprintf( error_msg, "gestartet fuer DB: %s", spDatabase );
    PrintMsg( fun, error_msg, 'H' );


    /*****************************************************/
    /* Datenbank oeffnen */
    /*****************************************************/
    if( !oeffneDB() == 0 )
    {
        PrintMsg( fun, "Fehler beim Öffnen der Datenbank!", 'F' );
        return 2;
    }

    lDatum = AllgGetDate();

    /*****************************************************/
    /* Prepare für Laden der Datensaetze */
    /*****************************************************/
    if( !PrepareLoadTemp() == 0 )
    {
        PrintMsg( fun, "Prepare für Laden temporaere Kontingente hat NICHT geklappt!", 'F' );
        return 3;
    }

    /*****************************************************/
    /* Prepare für Laden der Datensaetze */
    /*****************************************************/
    if( !PrepareDeleteTemp() == 0 )
    {
        PrintMsg( fun, "Prepare für Loeschen temporaere Kontingente hat NICHT geklappt!", 'F' );
        return 3;
    }

    /*****************************************************/
    /* Loeschen der Datensaetze */
    /*****************************************************/

    if( !DeleteTemp() == 0 )
    {
        printf("Loeschen temporaere Kontingente hat NICHT geklappt!");
        PrintMsg( fun,error_msg, 'F' );
        return 30;
    }
    sprintf( error_msg, "Anzahl geloescheter Datensaetze (articlequota): %d", delcount );
    PrintMsg( fun, error_msg, 'H' );
    sprintf( error_msg, "Anzahl reaktivierte Datensaetze (articlequota): %d", reakcount );
    PrintMsg( fun, error_msg, 'H' );

    /*****************************************************/
    /* Laden der Datensaetze */
    /*****************************************************/

    if( !LoadTemp() == 0 )
    {
        printf("Laden temporaere Kontingente hat NICHT geklappt!");
        PrintMsg( fun,error_msg, 'F' );
        return 30;
    }
    sprintf( error_msg, "Anzahl geladener Datensaetze (articlequota): %d", inscount );
    PrintMsg( fun, error_msg, 'H' );
    sprintf( error_msg, "Anzahl gesicherter Datensaetze (articlequota): %d", savecount );
    PrintMsg( fun, error_msg, 'H' );

    /*****************************************************/
    /* Datenbank schliessen */
    /*****************************************************/
    if( !schliesseDB() == 0 )
    {
        PrintMsg( fun, "Fehler beim Schließen der Datenbank!", 'F' );
        return 4;
    }

    PrintMsg( fun, "beendet", 'H' );

    return 0;
}
/*********************************************************************************/
/* static int KommandoZeileEinlesen( char** argv ) */
/*********************************************************************************/
static int KommandoZeileEinlesen( int argc, char* argv[] )
{
    char error_msg[512];
    int i;
    int skip = 0;
    char* schalter;
    char* fun = "KommandoZeileEinlesen()";

    for( i = 1; i < argc; i++ )
    {
        if( skip )
        {
            skip = 0;
            continue;
        }
        schalter = argv[i];

        if ( !strcmp( schalter, "-db" ) )
        {
            i++;
            spDatabase = argv[i];
        }
        else if ( !strcmp( schalter, "-version" ) )
        {
            printVersion(versioninfo);
            bVersion = TRUE;
            return 0;
        }
        else
        {
            skip = -1;
            break;
        }
    } /* ENDR FOR */

    if( argc == 1 || skip == -1 )
    {
        PrintMsg( fun, "Fehlerhafte Programmparameter", 'H' );
        return -1; /* Fehlerhafte KommandoZeile */
    }

    return 0;
}

/*********************************************************************************/
/* static int oeffneDB() */
/*********************************************************************************/
static int oeffneDB()
{
    char *fun = "oeffneDatenBank()";

    exec sql database :spDatabase;

    ERROR_MSG( "database" );

    exec sql set lock mode to wait 20;
    ERROR_MSG( "set lock mode" );

    exec sql set isolation to dirty read;
    ERROR_MSG( "set isolation" );

    return 0;
}

/****************************************************************************/
/* static int schliesseDB()                                                 */
/****************************************************************************/
static int schliesseDB()
{
    char *fun = "schliessen DB";
    exec sql close database;
    ERROR_MSG( "close database" );

    return 0;
}

/****************************************************************************/
/* static int PrepareLoadTemp()                                                     */
/****************************************************************************/
static int PrepareLoadTemp()
{
    /*************************/
    /* Variablen-Deklaration */
    /*************************/
    char*   fun = "PrepareLoadTemp";

    exec sql begin declare section;
        char    str[2048];
    exec sql end declare section;

    /* SELECT-Cursor tempquota vorbereiten */
    strcpy( str, "SELECT " );
    strcat( str, "articleno, " );
    strcat( str, "quota, " );
    strcat( str, "datefrom, " );
    strcat( str, "dateto " );
    strcat( str, "FROM articlequotatemp " );
    strcat( str, "where " );
    strcat( str, "datefrom <= ? " );
    strcat( str, "and dateto >= ? " );
    strcat( str, "FOR UPDATE " );
    EXEC SQL PREPARE preSelQuotaTemp from :str;
    ERROR_MSG( "PREPARE preSelQuotaTemp" );
    EXEC SQL DECLARE curSelQuotaTemp cursor with hold for preSelQuotaTemp;
    ERROR_MSG( "DECLARE curSelQuotaTemp" );
    exec sql free preSelQuotaTemp;

    /* SELECT-Cursor articlecodes vorbereiten */
    strcpy( str, "SELECT " );
    strcat( str, "articleno " );
    strcat( str, "FROM articlecodes " );
    strcat( str, "where " );
    strcat( str, "article_code = ? " );
    strcat( str, "FOR UPDATE " );
    EXEC SQL PREPARE preSelArticleCode from :str;
    ERROR_MSG( "PREPARE preSelArticleCode" );
    EXEC SQL DECLARE curSelArticleCode cursor with hold for preSelArticleCode;
    ERROR_MSG( "DECLARE curSelArticleCode" );
    exec sql free preSelArticleCode;

    /* delete tempquota vorbereiten */
    strcpy( str, "DELETE from articlequotatemp " );
    strcat( str, "where current of curSelQuotaTemp " );
    EXEC SQL PREPARE preDelQuotaTemp from :str;
    ERROR_MSG( "PREPARE preDelQuotaTemp" );

    /* SELECT-Cursor kunde vorbereiten */
    strcpy( str, "SELECT " );
    strcat( str, "kunde.vertriebszentrumnr, " );
    strcat( str, "kunde.kundennr " );
    strcat( str, "FROM kunde,kundeschalter,rechner " );
    strcat( str, "where " );
    strcat( str, "kunde.vertriebszentrumnr = kundeschalter.vertriebszentrumnr " );
    strcat( str, "and kunde.kundennr = kundeschalter.kundennr " );
//  strcat(str, "and kunde.kdgruppe not in ('13','18') ");
//  strcat( str, "and kunde.kdgruppe in ('01','02','03','06','14') " );
    strcat( str, "and kunde.kdgruppe in ('01','02','03','06','07','08','09','14','16','17') " );
    strcat( str, "and kunde.vertriebszentrumnr not in (27) ");
    strcat( str, "and kundeschalter.skdkundeaegesperrt = '0' " );
    strcat( str, "and kundeschalter.vertriebszentrumnr = rechner.filialnr " );
    strcat( str, "and rechner.datenbank_name = ? " );
    EXEC SQL PREPARE preSelKunde from :str;
    ERROR_MSG( "PREPARE preSelKunde" );
    EXEC SQL DECLARE curSelKunde cursor with hold for preSelKunde;
    ERROR_MSG( "DECLARE curSelKunde" );
    exec sql free preSelKunde;

    /* SELECT-Cursor quota vorbereiten */
    strcpy( str, "SELECT " );
    strcat( str, "BranchNo, " );
    strcat( str, "CustomerNo, " );
    strcat( str, "ArticleNo, " );
    strcat( str, "Quota, " );
    strcat( str, "KumQty, " );
    strcat( str, "Validity, " );
    strcat( str, "DateUpdate, " );
    strcat( str, "uid_anlage, " );
    strcat( str, "sDafueQuota " );
    strcat( str, "FROM articlequota " );
    strcat( str, "where " );
    strcat( str, "datefrom = 0 " );
    strcat( str, "and branchno = ? " );
    strcat( str, "and customerno = ? " );
    strcat( str, "and articleno = ? " );
    strcat( str, "FOR UPDATE " );
    EXEC SQL PREPARE preSelQuota from :str;
    ERROR_MSG( "PREPARE preSelQuota" );
    EXEC SQL DECLARE curSelQuota cursor for preSelQuota;
    ERROR_MSG( "DECLARE curSelQuota" );
    exec sql free preSelQuota;

    /* insert quotasave vorbereiten */
    strcpy( str, "INSERT into articlequotasave " );
    strcat( str, "(BranchNo, " );
    strcat( str, "CustomerNo, " );
    strcat( str, "ArticleNo, " );
    strcat( str, "Quota, " );
    strcat( str, "KumQty, " );
    strcat( str, "Validity, " );
    strcat( str, "DateUpdate, " );
    strcat( str, "uid_anlage, " );
    strcat( str, "sDafueQuota) " );
    strcat( str, "VALUES " );
    strcat( str, "( ?,?,?,?,?,?,?,?,? ) " );
    EXEC SQL PREPARE preInsQuotaSave from :str;
    ERROR_MSG( "PREPARE preInsQuotaSave" );

    /* delete quota vorbereiten */
    strcpy( str, "DELETE from articlequota " );
    strcat( str, "where current of curSelQuota " );
    EXEC SQL PREPARE preDelQuota from :str;
    ERROR_MSG( "PREPARE preDelQuota" );

    /* insert quota vorbereiten */
    strcpy( str, "INSERT into articlequota " );
    strcat( str, "(BranchNo, " );
    strcat( str, "CustomerNo, " );
    strcat( str, "ArticleNo, " );
    strcat( str, "Quota, " );
    strcat( str, "KumQty, " );
    strcat( str, "Validity, " );
    strcat( str, "DateUpdate, " );
    strcat( str, "uid_anlage, " );
    strcat( str, "sDafueQuota, " );
    strcat( str, "DateFrom, " );
    strcat( str, "DateTo) " );
    strcat( str, "VALUES " );
    strcat( str, "( ?,?,?,?,?,?,?,?,?,?,? ) " );
    EXEC SQL PREPARE preInsQuota from :str;
    ERROR_MSG( "PREPARE preInsQuota" );

    return 0;
}

/****************************************************************************/
/* static int PrepareDeleteTemp()                                           */
/****************************************************************************/
static int PrepareDeleteTemp()
{
    /*************************/
    /* Variablen-Deklaration */
    /*************************/
    char* fun = "PrepareDeleteTemp";

    exec sql begin declare section;
        char str[2048];
    exec sql end declare section;

    /* SELECT-Cursor quota vorbereiten */
    strcpy( str, "SELECT " );
    strcat( str, "branchno, " );
    strcat( str, "customerno, " );
    strcat( str, "articleno " );
    strcat( str, "FROM articlequota " );
    strcat( str, "where " );
    strcat( str, "dateto != 0 " );
    strcat( str, "and dateto < ? " );
    strcat( str, "FOR UPDATE " );
    EXEC SQL PREPARE preSelQuotaDel from :str;
    ERROR_MSG( "PREPARE preSelQuotaDel" );
    EXEC SQL DECLARE curSelQuotaDel cursor with hold for preSelQuotaDel;
    ERROR_MSG( "DECLARE curSelQuotaDel" );
    exec sql free preSelQuotaDel;

    /* delete quota vorbereiten */
    strcpy( str, "DELETE from articlequota " );
    strcat( str, "where current of curSelQuotaDel " );
    EXEC SQL PREPARE preDelQuotaDel from :str;
    ERROR_MSG( "PREPARE preDelQuotaDel" );

    /* SELECT-Cursor quotasave vorbereiten */
    strcpy( str, "SELECT " );
    strcat( str, "BranchNo, " );
    strcat( str, "CustomerNo, " );
    strcat( str, "ArticleNo, " );
    strcat( str, "Quota, " );
    strcat( str, "KumQty, " );
    strcat( str, "Validity, " );
    strcat( str, "DateUpdate, " );
    strcat( str, "uid_anlage, " );
    strcat( str, "sDafueQuota " );
    strcat( str, "FROM articlequotasave " );
    strcat( str, "where " );
    strcat( str, "branchno = ? " );
    strcat( str, "and customerno = ? " );
    strcat( str, "and articleno = ? " );
    strcat( str, "FOR UPDATE " );
    EXEC SQL PREPARE preSelQuotaSave from :str;
    ERROR_MSG( "PREPARE preSelQuotaSave" );
    EXEC SQL DECLARE curSelQuotaSave cursor for preSelQuotaSave;
    ERROR_MSG( "DECLARE curSelQuotaSave" );
    exec sql free preSelQuotaSave;

    /* insert quota vorbereiten */
    strcpy( str, "INSERT into articlequota " );
    strcat( str, "(BranchNo, " );
    strcat( str, "CustomerNo, " );
    strcat( str, "ArticleNo, " );
    strcat( str, "Quota, " );
    strcat( str, "KumQty, " );
    strcat( str, "Validity, " );
    strcat( str, "DateUpdate, " );
    strcat( str, "uid_anlage, " );
    strcat( str, "sDafueQuota) " );
    strcat( str, "VALUES " );
    strcat( str, "( ?,?,?,?,?,?,?,?,? ) " );
    EXEC SQL PREPARE preInsQuotaDel from :str;
    ERROR_MSG( "PREPARE preInsQuotaDel" );

    /* delete quotasave vorbereiten */
    strcpy( str, "DELETE from articlequotasave " );
    strcat( str, "where current of curSelQuotaSave " );
    EXEC SQL PREPARE preDelQuotaSave from :str;
    ERROR_MSG( "PREPARE preDelQuotaSave" );

    return 0;
}

/************************************************************************************************************/
/* static void PrintMsg(char* fun, char* error_msg, char mld )                                              */
/************************************************************************************************************/
static void PrintMsg( char* fun, char* error_msg, char mld )
{
    FILE* fp;
    struct tm* localtime();
    struct tm* zeit;
    long hour1;
    pid_t pid;
    long time();
    char logFile[256];
    char* env;

    pid = getpid();
    hour1 = time( &hour1 );
    zeit  = localtime( &hour1 );

    env = getenv( "LOG_PATH" );
    if ( env == NULL )
        env = ".";
    sprintf( logFile, "%s/wws.log", env );

    if ( ( fp = fopen( logFile, "a" ) ) == (FILE*)0 )
        return;

    if( zeit->tm_year > 99 ) zeit->tm_year -= 100;

    fprintf( fp, "%c %02d.%02d.%02d %02d:%02d:%02d "
            "pid=%05ld %s %s %s\n",
            mld,
            zeit->tm_mday,
            zeit->tm_mon + 1,
            zeit->tm_year,
            zeit->tm_hour,
            zeit->tm_min,
            zeit->tm_sec,
            pid,
            "loadtempquota",
            fun,
            error_msg );

    fclose(fp);
}

/****************************************************************************/
/* int DeleteTemp()                                                         */
/****************************************************************************/
int DeleteTemp()
{
    /*************************/
    /* Variablen-Deklaration */
    /*************************/
    char*   fun = "DeleteTemp";
    unsigned int uiTransactions = 0;

    exec sql begin declare section;
    short BranchNo;
    int CustomerNo;
    int ArticleNo;
    int Quota;
    int KumQty;
    char Validity[2];
    int DateUpdate;
    int uid_anlage;
    char sDafueQuota[2];
    exec sql end declare section;

    /* SELECT ausfuehren */
    EXEC SQL OPEN curSelQuotaDel using :lDatum;
    ERROR_MSG( "OPEN curSelQuotaDel" );

    EXEC SQL BEGIN WORK;
    ERROR_MSG( "BEGIN WORK1" );
    for(;;)
    {
        uiTransactions++;
        /* Max. Transaktionen sind erreicht --> Commit setzen */
        if( (uiTransactions % MAX_TRANSAKTION) == 0 )
        {
            EXEC SQL COMMIT WORK;
            ERROR_MSG( "COMMIT WORK1" );
            EXEC SQL BEGIN WORK;
            ERROR_MSG( "BEGIN WORK2" );
        }

        EXEC SQL FETCH curSelQuotaDel into
            :BranchNo,
            :CustomerNo,
            :ArticleNo;
        ERROR_MSG( "EXEC SQL FETCH curSelQuotaDel!" );

        /* Keine weiteren Datensaetze im Cursor */
        if( SQLCODE == SQLNOTFOUND )
        {
            break;
        }
        exec sql execute preDelQuotaDel;
        ERROR_MSG( "execute preDelQuotaDel" )
        delcount++;

        /* SELECT ausfuehren */
        EXEC SQL OPEN curSelQuotaSave using
            :BranchNo,
            :CustomerNo,
            :ArticleNo;
        ERROR_MSG( "OPEN curSelQuotaSave" );

        EXEC SQL FETCH curSelQuotaSave into
            :BranchNo,
            :CustomerNo,
            :ArticleNo,
            :Quota,
            :KumQty,
            :Validity,
            :DateUpdate,
            :uid_anlage,
            :sDafueQuota;
        ERROR_MSG( "EXEC SQL FETCH curSelQuotaSave!" );

        /* Keine weiteren Datensaetze im Cursor */
        if( SQLCODE == SQLNOTFOUND )
        {
            continue;
        }

        EXEC SQL EXECUTE preInsQuotaDel using
            :BranchNo,
            :CustomerNo,
            :ArticleNo,
            :Quota,
            :KumQty,
            :Validity,
            :DateUpdate,
            :uid_anlage,
            :sDafueQuota;
        ERROR_MSG( "EXEC SQL EXECUTE preInsQuotaDel!" );
        EXEC SQL EXECUTE preDelQuotaSave;
        ERROR_MSG( "EXEC SQL EXECUTE preDelQuotaSave!" );
        reakcount++;
    }

    EXEC SQL COMMIT WORK;
    ERROR_MSG( "COMMIT WORK2" );
    EXEC SQL CLOSE curSelQuota;
    ERROR_MSG( "EXEC SQL CLOSE curSelQuota!" );
    EXEC SQL CLOSE curSelQuotaDel;
    ERROR_MSG( "EXEC SQL CLOSE curSelQuota!" );
    return 0;
}

/****************************************************************************/
/* int LoadTemp()                                                           */
/****************************************************************************/
int LoadTemp()
{
    /*************************/
    /* Variablen-Deklaration */
    /*************************/
    char* fun = "LoadTemp";
    int count;

    exec sql begin declare section;
    short BranchNo;
    int CustomerNo;
    int ArticleNo;
    int Quota;
    int KumQty;
    char Validity[2];
    int DateUpdate;
    int uid_anlage;
    char sDafueQuota[2];
    int DateFrom;
    int DateTo;
    char cArtCode[26];
    exec sql end declare section;

    /* Vorgaben einlesen */
    EXEC SQL OPEN curSelQuotaTemp using :lDatum,:lDatum;
    ERROR_MSG( "OPEN curSelQuotaTemp" );
    startpos = NULL;
    actpos = NULL;
    for(;;)
    {
        EXEC SQL FETCH curSelQuotaTemp into
            :TempQuota;
        ERROR_MSG( "EXEC SQL FETCH curSelQuotaTemp!" );

        /* Keine weiteren Datensaetze im Cursor */
        if( SQLCODE == SQLNOTFOUND )
        {
            break;
        }

        sprintf(cArtCode,"%d", TempQuota.ARTICLENO);
        EXEC SQL OPEN curSelArticleCode using :cArtCode;
        ERROR_MSG( "OPEN curSelArticleCode" );

        EXEC SQL FETCH curSelArticleCode into
            :TempQuota.ARTICLENO;
        ERROR_MSG( "EXEC SQL FETCH curSelArticleCode!" );

        newpos = (struct TempVector*)malloc(sizeof(struct TempVector));
        newpos->Temp.ARTICLENO  = TempQuota.ARTICLENO;
        newpos->Temp.QUOTA      = TempQuota.QUOTA;
        newpos->Temp.DATEFROM   = TempQuota.DATEFROM;
        newpos->Temp.DATETO     = TempQuota.DATETO;
        newpos->nextpos         = NULL;
        if(startpos == NULL)
        {
            startpos = newpos;
        }
        else
        {
            actpos->nextpos = newpos;
        }
        actpos = newpos;
    }
    EXEC SQL CLOSE curSelQuotaTemp;
    ERROR_MSG( "EXEC SQL CLOSE curSelQuotaTemp!" );
    /* Keine Datensaetze vorhanden */
    if(startpos == NULL) return 0;

    EXEC SQL OPEN curSelKunde using :spDatabase;
    ERROR_MSG( "OPEN curSelKunde" );

    for(;;)
    {
        EXEC SQL BEGIN WORK;
        ERROR_MSG( "BEGIN WORK1" );

        EXEC SQL FETCH curSelKunde into
            :BranchNo,
            :CustomerNo;
        ERROR_MSG( "EXEC SQL FETCH curSelKunde!" );
        if( SQLCODE == SQLNOTFOUND )
        {
            break;
        }

        for(actpos = startpos;actpos != NULL;actpos = actpos->nextpos)
        {
            TempQuota.ARTICLENO = actpos->Temp.ARTICLENO;
            TempQuota.QUOTA     = actpos->Temp.QUOTA;
            TempQuota.DATEFROM  = actpos->Temp.DATEFROM;
            TempQuota.DATETO    = actpos->Temp.DATETO;

            /* SELECT ausfuehren */
            EXEC SQL OPEN curSelQuota using
                :BranchNo,
                :CustomerNo,
                :TempQuota.ARTICLENO;
            ERROR_MSG( "OPEN curSelQuota" );

            EXEC SQL FETCH curSelQuota into
                :BranchNo,
                :CustomerNo,
                :ArticleNo,
                :Quota,
                :KumQty,
                :Validity,
                :DateUpdate,
                :uid_anlage,
                :sDafueQuota;
            ERROR_MSG( "EXEC SQL FETCH curSelQuota!" );

            /* quota vorhanden */
            if( SQLCODE != SQLNOTFOUND )
            {
                continue; //kein Eintrag wenn quota schon vorhanden
                /* bisherigen Eintrag sichern und loeschen */
                EXEC SQL EXECUTE preInsQuotaSave using
                :BranchNo,
                :CustomerNo,
                :ArticleNo,
                :Quota,
                :KumQty,
                :Validity,
                :DateUpdate,
                :uid_anlage,
                :sDafueQuota;
                ERROR_MSG( "EXEC SQL EXECUTE preInsQuotaSave!" );

                EXEC SQL EXECUTE preDelQuota;
                ERROR_MSG( "EXEC SQL EXECUTE preDelQuota!" );
                savecount++;
            }

            EXEC SQL EXECUTE preInsQuota using
                :BranchNo,
                :CustomerNo,
                :TempQuota.ARTICLENO,
                :TempQuota.QUOTA,
                '0',
                'M',
                :lDatum,
                '999',
                ' ',
                :TempQuota.DATEFROM,
                :TempQuota.DATETO;
            if( SQLCODE != SQLEXISTS )
            {
                ERROR_MSG( "EXEC SQL EXECUTE preInsQuota!" );
                inscount++;
            }
        }
        EXEC SQL COMMIT WORK;
        ERROR_MSG( "COMMIT WORK1" );
    }

    EXEC SQL COMMIT WORK;
    ERROR_MSG( "COMMIT WORK2" );
    EXEC SQL CLOSE curSelKunde;
    ERROR_MSG( "EXEC SQL CLOSE curSelQuota!" );

    /* Vorgaben löschen */
    EXEC SQL BEGIN WORK;
    ERROR_MSG( "BEGIN WORK2" );
    EXEC SQL OPEN curSelQuotaTemp using :lDatum,:lDatum;
    ERROR_MSG( "OPEN curSelQuotaTemp" );
    for(;;)
    {
        EXEC SQL FETCH curSelQuotaTemp into
            :TempQuota;
        ERROR_MSG( "EXEC SQL FETCH curSelQuotaTemp!" );

        /* Keine weiteren Datensaetze im Cursor */
        if( SQLCODE == SQLNOTFOUND )
        {
            break;
        }
        EXEC SQL EXECUTE preDelQuotaTemp;
        ERROR_MSG( "EXEC SQL EXECUTE preDelQuotaTemp!" );
    }
    EXEC SQL CLOSE curSelQuotaTemp;
    ERROR_MSG( "EXEC SQL CLOSE curSelQuotaTemp!" );
    EXEC SQL COMMIT WORK;
    ERROR_MSG( "COMMIT WORK3" );
    return 0;
}

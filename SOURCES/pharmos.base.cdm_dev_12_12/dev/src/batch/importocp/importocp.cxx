/******************************************************************************************************/
/*    main module: importocp.ecc                                                                      */
/*         Source: importocp.cxx                                                                      */
/*          Autor: Fakhri Feki                                                                        */
/*        Created: 02.05.2023                                                                         */
/*  Last Modified: 12.03.2024                                                                         */
/*       language: C                                                                                  */
/*        Erzeugt: manual                                                                             */
/*           Task: import input ocp csv file into cocp_stagein_xxx database tables                    */
/*                 fill cocp_stageout_xxx database tables either from pharmos or stagein tables       */
/*                 transfer cocp_stageout_xxx database tables to pharmos database tables              */
/*          Usage: importocp.bin [-inputcsv filename][-outpharmos yyyymmddhhmmss][-db dbname]         */
/*                 [-datetime yyyymmddhhmmss][-inexdb][-version][-log][-keepcsv][-username username]  */
/*                                                                                                    */
/******************************************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/
#include "../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.0.2 : importocp : 12.03.2024 ";
static char *VERSION = "1.0.2 (12.03.2024)";

/********************************************************************************/
/* INCLUDE */
/********************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <libgen.h>
#include <stdarg.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include "define.h"
#include "csvparser.h"
#include "ocp_pharmos.h"
#include "sql_reqs.h"

exec sql begin declare section;

// clone of CsvRow struct to allow access to ESQL
typedef struct ESQLRow {
    char **fields;
    int numOfFields;
    int numOfAllocatedFields;
} sqlRow;
    mint               db_exception_count;
    mint               db_row_count;
    long               lArtikel_nr;
    char               lArtikelcode[128] = "";
    char               FileName[2048] = "";
    char               TmpOutCSVName[2048] = "";
    char               ImportStatusCSVName[2048] = "";
    char               ImportStatusLogCSVName[2048] = "";
    char               str[4096];
    long               curDate = 0;
    long               curTime = 0;
    long               transfDate = 0;
    long               transfTime = 0;
    char               tDate[12] = "";
    char               tTime[8] = "";
    char               sUsername[64] = "default";
    short              codetype = 0;
    char               *strSql = NULL;
    char               *str2Sql = NULL;
    extern char       esqlRows[128][256];
exec sql end declare section;


/********************************************************************************/
/* DEFINE */
/********************************************************************************/
typedef struct timeval timeval_t;


// module return ERRORS CODE
#define CSVERR_RET_OK                                   0
#define CSVERR_MISSING_OR_WRONG_PARAMETERS              1
#define CSVERR_ERROR_OPENING_DATA_BASE                  2
#define CSVERR_ERROR_CLOSING_DATA_BASE                  3
#define CSVERR_IO_ERROR                                 4
#define CSVERR_INVALID_INPUT_DATA                       5
#define CSVERR_DATABASE_FAILED_INSERT                   6
#define CSVERR_DATABASE_SQL_ERROR                       7
#define CSVERR_NO_VALID_OCP_NO                          8
#define CSVERR_FAILED_CSV_CONVERT                       9


/********************************************************************************/
/* GLOBAL VARIABLES */
/********************************************************************************/
static  char*    spDatabase              = NULL;
static  char*    csvFileName             = NULL;
static  long     failedInsertItems       = 0;
static  long     notloadItems            = 0;
static  long     CountNumbers            = 0;
static  bool     bVersion                = false;
static  bool     bLog                    = false;
static  bool     bTransfPharmos          = false;
static  bool     bKeepCSV                = false;
static  bool     bForcedDateTime         = false;
static  bool     bExcludeIOCPNo          = false;
static  char     InCSVFileName[2048]     = "";
static  int      rargc                   = 0;
static  char**   rargv                   = NULL;

/********************************************************************************/
/* INPUT CSV struct and defines */
/********************************************************************************/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

#define CSV_STRUCTS_COUNT 4
char *rowsID[] = { "CART", "ZART", "ZPREIS", "ZFRAN" };

#define ROWID_ARTICLE_CODES     0
#define ROWID_ARTICLE           1
#define ROWID_ARTICLE_PRICE     2
#define ROWID_ARTICLE_FRANCE    3


// article codes struct /////////////////////////////////////////////

CSvFieldFormat *articleCodesStruct[ARTICLE_CODES_FIELDS_COUNT] =
    { &CSvFormat_NumericString, &CSvFormat_NumericString, &CSvFormat_NumericString, &CSvFormat_int32, &CSvFormat_date };

char *articleCodesDefaults[ARTICLE_CODES_FIELDS_COUNT] = { "0", "0", "", "0", "0" };
CsvRow *articleCodesDefaultRow = NULL;

// article struct //////////////////////////////////////////////////

CSvFieldFormat *articleStruct[ARTICLE_FIELDS_COUNT] =
    { &CSvFormat_NumericString, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_NumericString, &CSvFormat_NumericString, &CSvFormat_any, &CSvFormat_any,
      &CSvFormat_any, &CSvFormat_any, &CSvFormat_date, &CSvFormat_any, &CSvFormat_any, &CSvFormat_NumericString, &CSvFormat_any, &CSvFormat_date, &CSvFormat_date, &CSvFormat_any,
      &CSvFormat_any, &CSvFormat_date, &CSvFormat_NumericString, &CSvFormat_NumericString, &CSvFormat_NumericString, &CSvFormat_NumericString, &CSvFormat_any, &CSvFormat_any, &CSvFormat_NumericString, &CSvFormat_any,
      &CSvFormat_NumericString, &CSvFormat_NumericString, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any
    };

char *articleDefaults[ARTICLE_FIELDS_COUNT] =
    {   "0", "", "", "", "", "", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
        "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N"
    };
CsvRow *articleDefaultRow = NULL;

// article price struct //////////////////////////////////////////////

CSvFieldFormat *articlePriceStruct[ARTICLE_PRICE_FIELDS_COUNT] =
    {   &CSvFormat_NumericString, &CSvFormat_date, &CSvFormat_float, &CSvFormat_float, &CSvFormat_float, &CSvFormat_any, &CSvFormat_float, &CSvFormat_float,
        &CSvFormat_float, &CSvFormat_NumericString, &CSvFormat_float, &CSvFormat_float, &CSvFormat_float, &CSvFormat_NumericString, &CSvFormat_float, &CSvFormat_any, &CSvFormat_NumericString
    };

char *articlePriceDefaults[ARTICLE_PRICE_FIELDS_COUNT] =
    { "0", "0", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "", "0", "0", "0", "" };
CsvRow *articlePriceDefaultRow = NULL;

// article france struct ////////////////////////////////////////////////

CSvFieldFormat *articleFranceStruct[ARTICLE_FRANCE_FIELDS_COUNT] =
    {   &CSvFormat_NumericString, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any,
        &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any, &CSvFormat_any
    };

char *articleFranceDefaults[ARTICLE_FRANCE_FIELDS_COUNT] =
    { "0", "0.0", "0.0", "", "0", "", "", "", "", "", "0.0", "0", "", "", "", ""  };
CsvRow *articleFranceDefaultRow = NULL;

// Multi RowStruct array definition
RowStruct rowsStruct[] =
    {   { ARTICLE_CODES_FIELDS_COUNT, articleCodesStruct },
        { ARTICLE_FIELDS_COUNT, articleStruct },
        { ARTICLE_PRICE_FIELDS_COUNT, articlePriceStruct },
        { ARTICLE_FRANCE_FIELDS_COUNT, articleFranceStruct }
    };

// default rows Value definition
CsvRow *RowsDefaultValues[CSV_STRUCTS_COUNT] = { NULL, NULL, NULL, NULL };

// key definition ////////////////////////////////

int articleCodesKeys[] = { OCP_ARTICLE_NO_IDX, ARTICLE_CODES_CODE_TYPE_IDX};
int articleKeys[] = { OCP_ARTICLE_NO_IDX };
int articlePriceKeys[] = { OCP_ARTICLE_NO_IDX, ARTICLE_PRICE_VALID_FROM_DATE_IDX };
int articleFranceKeys[] = { OCP_ARTICLE_NO_IDX };

int *keysIndexes[CSV_STRUCTS_COUNT] = { articleCodesKeys, articleKeys, articlePriceKeys, articleFranceKeys };
int keysCount[CSV_STRUCTS_COUNT] = { 2, 1, 2, 1 };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/********************************************************************************/
/* MACROS */
/********************************************************************************/
#define ERROR_MSG(x, sqlError)    if(SQLCODE < 0) { PrintMsg( fun, FEHLER, x ); sqlError = true; }

/********************************************************************************/
/* FUNCTIONS-DECLARATION */
/********************************************************************************/
static int  CommandLineImport(int argc, char** argv);
static int  openDB();
static int  closeDB();
static int  StartOCPImport(char *error_msg);
void PrintMsg(char *fun, char mld , char *error_msg, ...);
static void GenFilesNames();
static long GetCurDate();
static long GetCurTime();
static void ReplaceLineEndBySpace(char *str);
static char **RemapInCSVToImportOrder(CsvRow *inRow, int rowID);
static void FreeRemappedRow(char **remapRow, int rowID);

/********************************************************************************/
/* int main( int argc, char **argv ) */
/********************************************************************************/
int main(int argc, char* argv[])
{
    char error_msg[512] = "";
    char *fun = "main()";
    int retStartCSVConvert = CSVERR_RET_OK;
    rargc = argc;
    rargv = (char**)argv;
    /*****************************************************/
    /* initialization*/
    /*****************************************************/
    setbuf(stdout, 0);

    /*****************************************************/
    /* handle parameters*/
    /*****************************************************/
    if (CommandLineImport( argc, argv ) != OK)
    {
        printf( "Usage: ocp_import_stagein [-inputcsv filename][-db dbname][-outpharmos yyyymmddhhmmss][-datetime yyyymmddhhmmss][-inexdb][-version][-log][-keepcsv][-username username]\n"
                "Example:  %s -inputcsv in.csv -db ifr21@zdev21_shm \n", argv[0] );
        PrintMsg(fun, HINWEIS, "finished" );
        return CSVERR_MISSING_OR_WRONG_PARAMETERS;
    }
    if (bVersion)
    {
        return CSVERR_RET_OK;
    }

    /*****************************************************/
    /* Generate required filenames                       */
    /*****************************************************/
    GenFilesNames();

    /*****************************************************/
    /* Open database */
    /*****************************************************/
    if (openDB() != OK)
    {
        PrintMsg(fun, FEHLER, "Error opening database! error code <%i>",  CSVERR_ERROR_OPENING_DATA_BASE);
        PrintMsg(fun, HINWEIS, "finished" );
        return CSVERR_ERROR_OPENING_DATA_BASE;
    }

    /*****************************************************/
    /* init OCPNo exclude list if provided               */
    /*****************************************************/
    if (bExcludeIOCPNo)
    {
        if (!InitOCPNoExclusionMap(curDate, curTime))
        {
            PrintMsg(fun, FEHLER, "Fatal: failed to extract OCPNo Exclusion list for date/time %i/%i", curDate, curTime);
            closeDB();
            PrintMsg(fun, HINWEIS, "finished" );
            return CSVERR_INVALID_INPUT_DATA;
        }
    }

    /*****************************************************/
    /* Delete any possible exisiting status file         */
    /*****************************************************/
    remove(ImportStatusCSVName);
    remove(ImportStatusLogCSVName);

    /*****************************************************/
    /* Load of data */
    /*****************************************************/
    if (csvFileName!= NULL && !ConvPINTToCSV(csvFileName, TmpOutCSVName))
    {
        PrintMsg(fun, FEHLER, "Fatal: failed csv convert");
        closeDB();
        PrintMsg(fun, HINWEIS, "finished" );
        return CSVERR_FAILED_CSV_CONVERT;
    }

    /*****************************************************/
    /* Load of data */
    /*****************************************************/
    if ((retStartCSVConvert = StartOCPImport(error_msg)) != CSVERR_RET_OK)
    {
        PrintMsg(fun, FEHLER, "OCP import failed! error code <%i>",  retStartCSVConvert);
        closeDB();
        if (!bKeepCSV)
        {
            remove(TmpOutCSVName);
        }
        PrintMsg(fun, HINWEIS, "finished" );
        return retStartCSVConvert;
    }

    /*****************************************************/
    /* Close database */
    /*****************************************************/
    if (!bKeepCSV)
    {
        remove(TmpOutCSVName);
    }
    if (closeDB() != OK)
    {
        PrintMsg(fun, FEHLER, "Error closing database! error code <%i>",  CSVERR_ERROR_CLOSING_DATA_BASE);
        PrintMsg(fun, HINWEIS, "finished" );
        return CSVERR_ERROR_CLOSING_DATA_BASE;
    }

    PrintMsg(fun, HINWEIS, "finished" );

    return CSVERR_RET_OK;
}

/*********************************************************************************/
/* static int CommandLineImport( char** argv ) */
/*********************************************************************************/
static int CommandLineImport( int argc, char* argv[] )
{
    char error_msg[512] = "";
    char tmpFileName[2048] = "";
    char pointStr[2] = ".";
    char *tmpBaseFileName = NULL;
    int i;
    int skip = NO;
    char *curParam;
    char *fun = "CommandLineImport()";
    timeval_t timev_s;

    for( i = 1; i < argc; i++ )
    {
        if(skip)
        {
            skip = NO;
            continue;
        }
        curParam = argv[i];

        if (!strcmp(curParam, "-inputcsv") && i < (argc-1))
        {
            i++;
            csvFileName = argv[i];
            strcpy(InCSVFileName, csvFileName);
            strcpy(FileName, basename(InCSVFileName)); // only filename and extension
        } else if (!strcmp(curParam, "-inexdb"))
        {
            bExcludeIOCPNo = true;
        }
        else if (!strcmp(curParam,  "-outpharmos") && i < (argc-1))
        {
            i++;
            if (strlen(argv[i]) != 14)
            {
                PrintMsg( fun, HINWEIS, "Incorrect [-outpharmos] datetime parameters '%s', should be in YYYYMMDDHHMMSS format", argv[i]);
                skip = ERROR;
            }
            else
            {
                strncpy(tDate, argv[i], 8);
                tDate[8] = 0;
                strncpy(tTime, &argv[i][8], 6);
                tTime[6] = 0;
                transfDate = atoi(tDate);
                transfTime = atoi(tTime);
                bTransfPharmos = true;
            }
        }
        else if (!strcmp(curParam,  "-datetime") && i < (argc-1)) {
            i++;
            if (strlen(argv[i]) != 14)
            {
                PrintMsg( fun, HINWEIS, "Incorrect [-datetime] datetime parameters '%s', should be in YYYYMMDDHHMMSS format", argv[i]);
                skip = ERROR;
            }
            else
            {
                strncpy(tDate, argv[i], 8);
                tDate[8] = 0;
                strncpy(tTime, &argv[i][8], 6);
                tTime[6] = 0;
                curDate = atoi(tDate);
                curTime = atoi(tTime);
                bForcedDateTime = true;
            }
        }
        else if (!strcmp( curParam, "-db" ) && i < (argc-1))
        {
            i++;
            spDatabase = argv[i];
        }
        else if (!strcmp( curParam, "-version" ))
        {
            printf("\n%s\n", SCCSID);
            bVersion = true;
        }
        else if(!strcmp(curParam, "-log"))
        {
            bLog = true;
        }
        else if(!strcmp(curParam, "-keepcsv"))
        {
            bKeepCSV = true;
        }
        else if (!strcmp(curParam,  "-username") && i < (argc-1))
        {
            i++;
            strcpy(sUsername, argv[i]);
        }
        else
        {
            skip = ERROR;
            break;
        }
    } /* ENDR FOR */

    if( argc == 1 || skip == ERROR || (csvFileName == NULL && bTransfPharmos == false) || spDatabase == NULL)
    {
        PrintMsg( fun, HINWEIS, "Incorrect program parameters" );
        return ERROR; /* Incorrect program parameters */
    }
    if (!bForcedDateTime)
    {
        curDate = GetCurDate();
        curTime = GetCurTime();
    }

    return OK;
}

/*********************************************************************************/
/* static int openDB()                                                           */
/*********************************************************************************/
static int openDB()
{
    bool bDbSqlError     = false;

    exec sql begin declare section;
    char* spDB = spDatabase;
    exec sql end declare section;

    char *fun = "openDB()";

    if (spDB == NULL)
    {
        exec sql database DATABASE;
        spDatabase = DATABASE;
    }
    else
    {
        exec sql database :spDB;
    }
    ERROR_MSG("database", bDbSqlError);

    exec sql set lock mode to wait 20;
    ERROR_MSG("set lock mode", bDbSqlError);

    exec sql set isolation to dirty read;
    ERROR_MSG("set isolation", bDbSqlError);
    if (bDbSqlError)
    {
        return ERROR;
    }

    return OK;
}

/****************************************************************************/
/* static int closeDB()                                                     */
/****************************************************************************/
static int closeDB()
{
    char *fun = "closeDB()";
    bool bDbSqlError = false;

    exec sql close database;
    ERROR_MSG( "close database", bDbSqlError);
    if (bDbSqlError)
    {
        return ERROR;
    }

    return OK;
}

/****************************************************************************/
/* static int StartOCPImport()                                             */
/****************************************************************************/
static int StartOCPImport(char *error_msg)
{
    /*************************/
    /* Variables-Declaration */
    /*************************/
    char    *fun = "StartOCPImport()";
    char *trimStr = NULL;
    unsigned int uiTransactions = 0;
    bool bDbSqlError = false;
    bool bDbTransact = false;

    exec sql begin declare section;
    sqlRow *csvRow = NULL;
    sqlRow *outRow = NULL;
    char **curRow;
    char sqlErrMsg[2048] = "";
    char ErrMsgFormat[2048] = "";
    char artNo[32]="";
    char cocp_no[32] = "";
    char validFrom[32]="";
    char codeType[32]="";
    char emptyField[32]=" ";
    char *field1 = NULL;
    char *field2 = NULL;
    int sqlErrMsgSize = 0;
    int sqlErrMsgBuffSize = 2048;
    int countTotalInCode = 0;
    int countTotalInArticle = 0;
    int countTotalInPrice = 0;
    int countTotalInFrance = 0;
    int countFailedInCode = 0;
    int countFailedInArticle = 0;
    int countFailedInPrice = 0;
    int countFailedInFrance = 0;
    int countExcludedInCode = 0;
    int countExcludedInArticle = 0;
    int countExcludedInPrice = 0;
    int countExcludedInFrance = 0;
    int countExcludedRow = 0;

    int countInsCode = 0;
    int countInsArticle = 0;
    int countInsPrice = 0;
    int countInsFrance = 0;
    int countInsExCode = 0;
    int countInsExArticle = 0;
    int countInsExPrice = 0;
    int countInsExFrance = 0;
    exec sql end declare section;

    #define ForceNotEmpty(str) (strlen((char*)str) == 0) ? emptyField : str;
    curRow = NULL;

    /****************************************************************************************************/
    /* SQL statements required for ocp import */
    /****************************************************************************************************/

    /* Prepare Insert/delete/update in cocp_stagein_articlecode *************************************/
    PSQL_STR_INS_COCP_STAGEIN_ARTICLECODE(str);
    EXEC SQL PREPARE insCocp_stagein_articlecode from :str;
    ERROR_MSG("prepare insCocp_stagein_articlecode", bDbSqlError);

    PSQL_STR_DEL_CLEAN_COCP_STAGEIN_ARTICLECODE(str);
    EXEC SQL PREPARE delCleanCocp_stagein_articlecode from :str;
    ERROR_MSG("prepare delCocp_stagein_articlecode", bDbSqlError);

    PSQL_STR_DEL_DATETIME_COCP_STAGEIN_ARTICLECODE(str);
    EXEC SQL PREPARE delDateTimeCocp_stagein_articlecode from :str;
    ERROR_MSG("prepare delDateTimeCocp_stagein_articlecode", bDbSqlError);

    /* Prepare Insert/delete/update in cocp_stagein_article ******************************************/
    PSQL_STR_INS_COCP_STAGEIN_ARTICLE(str);
    EXEC SQL PREPARE insCocp_stagein_article from :str;
    ERROR_MSG("prepare insCocp_stagein_article", bDbSqlError);

    PSQL_STR_DEL_CLEAN_COCP_STAGEIN_ARTICLE(str);
    EXEC SQL PREPARE delCleanCocp_stagein_article from :str;
    ERROR_MSG("prepare delCocp_stagein_article", bDbSqlError);

    PSQL_STR_DEL_DATETIME_COCP_STAGEIN_ARTICLE(str);
    EXEC SQL PREPARE delDateTimeCocp_stagein_article from :str;
    ERROR_MSG("prepare delDateTimeCocp_stagein_article", bDbSqlError);

    /* Prepare Insert/delete/update in cocp_stagein_articleprice *************************************/
    PSQL_STR_INS_COCP_STAGEIN_ARTICLE_PRICE(str);
    EXEC SQL PREPARE insCocp_stagein_articleprice from :str;
    ERROR_MSG("prepare insCocp_stagein_articleprice", bDbSqlError);

    PSQL_STR_DEL_CLEAN_COCP_STAGEIN_ARTICLE_PRICE(str);
    EXEC SQL PREPARE delCleanCocp_stagein_articleprice from :str;
    ERROR_MSG("prepare delCocp_stagein_articleprice", bDbSqlError);

    PSQL_STR_DEL_DATETIME_COCP_STAGEIN_ARTICLE_PRICE(str);
    EXEC SQL PREPARE delDateTimeCocp_stagein_articleprice from :str;
    ERROR_MSG("prepare delDateTimeCocp_stagein_articleprice", bDbSqlError);

    /* Prepare Insert/delete/update in cocp_stagein_article_france **********************************/
    PSQL_STR_INS_COCP_STAGEIN_ARTICLE_FRANCE(str);
    EXEC SQL PREPARE insCocp_stagein_article_france from :str;
    ERROR_MSG("prepare insCocp_stagein_article_france", bDbSqlError);

    PSQL_STR_DEL_CLEAN_COCP_STAGEIN_ARTICLE_FRANCE(str);
    EXEC SQL PREPARE delCleanCocp_stagein_article_france from :str;
    ERROR_MSG("prepare delCleanCocp_stagein_article_france", bDbSqlError);

    PSQL_STR_DEL_DATETIME_COCP_STAGEIN_ARTICLE_FRANCE(str);
    EXEC SQL PREPARE delDateTimeCocp_stagein_article_france from :str;
    ERROR_MSG("prepare delDateTimeCocp_stagein_article_france", bDbSqlError);

    /* Prepare Insert/delete/update in cocp_stagein_status *****************************************/
    PSQL_STR_INS_COCP_STAGEIN_STATUS(str);
    EXEC SQL PREPARE insCocp_stagein_status from : str;
    ERROR_MSG("prepare insCocp_stagein_status", bDbSqlError);

    PSQL_STR_UPDATE_COCP_STAGEIN_STATUS(str);
    EXEC SQL PREPARE updateCocp_stagein_status from : str;
    ERROR_MSG("prepare updateCocp_stagein_status", bDbSqlError);

    /* Prepare Insert in cocp_stageout_article *****************************************************/
    PSQL_STR_INS_COCP_STAGEOUT_ARTICLE(str);
    EXEC SQL PREPARE insCocp_stageout_article from : str;
    ERROR_MSG("prepare insCocp_stageout_article", bDbSqlError);

    PSQL_STR_UPDATE_COCP_STAGEOUT_ARTICLE(str);
    EXEC SQL PREPARE updateCocp_stageout_article from : str;
    ERROR_MSG("prepare updateCocp_stageout_article", bDbSqlError);

    PSQL_STR_UPDATE_COCP_STAGEOUT_ARTICLE2(str);
    EXEC SQL PREPARE updateCocp_stageout_article2 from : str;
    ERROR_MSG("prepare updateCocp_stageout_article2", bDbSqlError);

    PSQL_STR_SELECT_DATETIME_COCP_STAGEOUT_ARTICLE(str);
    EXEC SQL PREPARE preSelectDatetimeCocp_stageout_article from :str;
    ERROR_MSG("prepare preSelectDatetimeCocp_stageout_article", bDbSqlError);
    EXEC SQL DECLARE selectDatetimeCocp_stageout_article cursor with hold for preSelectDatetimeCocp_stageout_article;
    ERROR_MSG("prepare selectDatetimeCocp_stageout_article", bDbSqlError);
    EXEC SQL FREE preSelectDatetimeCocp_stageout_article;

    PSQL_STR_DEL_DATETIME_COCP_STAGEOUT_ARTICLE(str);
    EXEC SQL PREPARE delDateTimeCocp_stageout_article from : str;

    /* Prepare Insert in cocp_stageout_articlecode *************************************************/
    PSQL_STR_INS_COCP_STAGEOUT_ARTICLE_CODE(str);
    EXEC SQL PREPARE insCocp_stageout_articlecode from :str;
    ERROR_MSG("prepare insCocp_stageout_articlecode", bDbSqlError);

    PSQL_STR_UPDATE_COCP_STAGEOUT_ARTICLE_CODE(str);
    EXEC SQL PREPARE updateCocp_stageout_article_code from : str;
    ERROR_MSG("prepare updateCocp_stageout_article_code", bDbSqlError);

    PSQL_STR_SELECT_DATETIME_COCP_STAGEOUT_ARTICLE_CODE(str);
    EXEC SQL PREPARE preSelectDatetimeCocp_stageout_article_code from :str;
    ERROR_MSG("prepare preSelectDatetimeCocp_stageout_article_code", bDbSqlError);
    EXEC SQL DECLARE selectDatetimeCocp_stageout_article_code cursor with hold for preSelectDatetimeCocp_stageout_article_code;
    ERROR_MSG("prepare selectDatetimeCocp_stageout_article_code", bDbSqlError);
    EXEC SQL FREE preSelectDatetimeCocp_stageout_article_code;

    PSQL_STR_DEL_DATETIME_COCP_STAGEOUT_ARTICLE_CODE(str);
    EXEC SQL PREPARE delDateTimeCocp_stageout_article_code from : str;

    /* Prepare Insert in cocp_stageout_articleprice ************************************************/
    PSQL_STR_INS_COCP_STAGEOUT_ARTICLE_PRICE(str);
    EXEC SQL PREPARE insCocp_stageout_articleprice from :str;
    ERROR_MSG("prepare insCocp_stageout_articleprice", bDbSqlError);

    PSQL_STR_UPDATE_COCP_STAGEOUT_ARTICLE_PRICE(str);
    EXEC SQL PREPARE updateCocp_stageout_article_price from : str;
    ERROR_MSG("prepare updateCocp_stageout_article_price", bDbSqlError);

    PSQL_STR_SELECT_DATETIME_COCP_STAGEOUT_ARTICLE_PRICE(str);
    EXEC SQL PREPARE preSelectDatetimeCocp_stageout_article_price from :str;
    ERROR_MSG("prepare preSelectDatetimeCocp_stageout_article_price", bDbSqlError);
    EXEC SQL DECLARE selectDatetimeCocp_stageout_article_price cursor with hold for preSelectDatetimeCocp_stageout_article_price;
    ERROR_MSG("prepare selectDatetimeCocp_stageout_article_price", bDbSqlError);
    EXEC SQL FREE preSelectDatetimeCocp_stageout_article_price;

    PSQL_STR_SELECT_ALL_DATEVALIDFROM_COCP_STAGEOUT_ARTICLE_PRICE(str);
    EXEC SQL PREPARE preSelectAllDatevalidfromCocp_stageout_article_price from :str;
    ERROR_MSG("prepare preSelectAllDatevalidfromCocp_stageout_article_price", bDbSqlError);
    EXEC SQL DECLARE selectAllDatevalidfromCocp_stageout_article_price cursor with hold for preSelectAllDatevalidfromCocp_stageout_article_price;
    ERROR_MSG("prepare selectAllDatevalidfromCocp_stageout_article_price", bDbSqlError);
    EXEC SQL FREE preSelectAllDatevalidfromCocp_stageout_article_price;

    PSQL_STR_DEL_DATETIME_COCP_STAGEOUT_ARTICLE_PRICE(str);
    EXEC SQL PREPARE delDateTimeCocp_stageout_article_price from : str;

    /* Prepare Insert in cocp_stageout_article_france **********************************************/
    PSQL_STR_INS_COCP_STAGEOUT_ARTICLE_FRANCE(str);
    EXEC SQL PREPARE insCocp_stageout_article_france from :str;
    ERROR_MSG("prepare insCocp_stageout_article_france", bDbSqlError);

    PSQL_STR_UPDATE_COCP_STAGEOUT_ARTICLE_FRANCE(str);
    EXEC SQL PREPARE updateCocp_stageout_article_france from : str;
    ERROR_MSG("prepare updateCocp_stageout_article_france", bDbSqlError);

    PSQL_STR_SELECT_DATETIME_COCP_STAGEOUT_ARTICLE_FRANCE(str);
    EXEC SQL PREPARE preSelectDatetimeCocp_stageout_article_france from :str;
    ERROR_MSG("prepare preSelectDatetimeCocp_stageout_article_france", bDbSqlError);
    EXEC SQL DECLARE selectDatetimeCocp_stageout_article_france cursor with hold for preSelectDatetimeCocp_stageout_article_france;
    ERROR_MSG("prepare selectDatetimeCocp_stageout_article_france", bDbSqlError);
    EXEC SQL FREE preSelectDatetimeCocp_stageout_article_france;

    PSQL_STR_DEL_DATETIME_COCP_STAGEOUT_ARTICLE_FRANCE(str);
    EXEC SQL PREPARE delDateTimeCocp_stageout_article_france from : str;

    /* master data zartpreis **************************************************************************/
    PSQL_STR_SELECT_ALL_DATAVALID_ARTTIKEL_NR_ZARTPREIS(str);
    EXEC SQL PREPARE preSelectDateValidFromZartpreis from :str;
    ERROR_MSG("prepare preSelectDateValidFromZartpreis", bDbSqlError);
    EXEC SQL DECLARE SelectDateValidFromZartpreis cursor with hold for preSelectDateValidFromZartpreis;
    ERROR_MSG("prepare SelectDateValidFromZartpreis", bDbSqlError);
    EXEC SQL FREE preSelectDateValidFromZartpreis;

    /* master data carticlecodes **********************************************************************/
    PSQL_STR_SELECT_ALL_CODETYPE_ARTICLECODES(str);
    EXEC SQL PREPARE preSelectCodeTypeFromCarticleCodes from :str;
    ERROR_MSG("prepare preSelectCodeTypeFromCarticleCodes", bDbSqlError);
    EXEC SQL DECLARE SelectCodeTypeFromCarticleCodes cursor with hold for preSelectCodeTypeFromCarticleCodes;
    ERROR_MSG("prepare SelectCodeTypeFromCarticleCodes", bDbSqlError);
    EXEC SQL FREE preSelectCodeTypeFromCarticleCodes;

    /* master data zpznpflege **********************************************************************/
    PSQL_STR_INS_ARTICLE_UPDATE_ZPZNPFLEGE(str);
    EXEC SQL PREPARE insArticle_update_zpznpflege from :str;
    ERROR_MSG("prepare insArticle_update_zpznpflege", bDbSqlError);

    /* ******************************************************************************************************/
    /* STAGEOUT to PHARMOS **********************************************************************************/
    /* ******************************************************************************************************/
    if (bTransfPharmos)
    {
        int countTransfOCPNo = 0;
        int countTransfNotReadyOCPNo = 0;
        int countTransfValidOCPNo = 0;
        int countTransfFailedOCPNo = 0;
        int countTransfArticle = 0;
        int countTransfArticleCode = 0;
        int countTransfArticlePrice = 0;
        int countTransfArticleFrance = 0;
        int countTransfFailedArticle = 0;
        int countTransfFailedArticleCode = 0;
        int countTransfFailedArticlePrice = 0;
        int countTransfFailedArticleFrance = 0;
        int countTransfSkipArticle = 0;
        int countTransfSkipArticleCode = 0;
        int countTransfSkipArticlePrice = 0;
        int countTransfSkipArticleFrance = 0;

        PrintMsg( fun, HINWEIS, "User '%s' Started transfer stageout to pharmos for date/time %08i/%06i", sUsername, transfDate, transfTime);
        // transfer/delete Cocp_stageout_article ///////////////////////////////////////////////
        EXEC SQL OPEN selectDatetimeCocp_stageout_article using :transfDate, :transfTime;
        EXEC SQL FETCH selectDatetimeCocp_stageout_article into ESQL_ROWS_INTO;

        while(SQLCODE==0)
        {
            countTransfOCPNo++;

            bool bDbTransfError = false;
            bool bDbTransSqlErr = false;
            int countLArticle = 0;
            int countLArticleCode = 0;
            int countLArticlePrice = 0;
            int countLArticleFrance = 0;

            // save trimmed ocp_no and article_no
            TrimStr(esqlRows[OARTICLE_OCP_NO_IDX]);
            strcpy(cocp_no, esqlRows[OARTICLE_OCP_NO_IDX]);
            TrimStr(esqlRows[OARTICLE_NO_IDX]);
            strcpy(artNo, esqlRows[OARTICLE_NO_IDX]);

            if (GetTransferReadyOCPNo(cocp_no, transfDate, transfTime))
            {
                /* Start SQL transaction*/
                EXEC SQL BEGIN;
                ERROR_MSG("BEGIN", bDbTransSqlErr);

                // transfer/delete Cocp_stageout_article ////////////////////////////////////////////
                if (esqlRows[OARTICLE_SUM_STATE_FLAG_IDX][0]=='8' || esqlRows[OARTICLE_SUM_STATE_FLAG_IDX][0]=='9')
                {
                    bDbTransfError = !PutStageoutArticle();
                    if (bDbTransfError)
                    {
                        PrintMsg(fun, FEHLER, "Failed article tranfer, ocp_no: '%s'", cocp_no);
                    }
                    else
                    {
                        exec sql execute delDateTimeCocp_stageout_article using
                                    :cocp_no, :transfDate, :transfTime;
                        ERROR_MSG("failed delDateTimeCocp_stageout_article", bDbTransSqlErr);
                    }
                    countLArticle++;
                }
                else
                {
                    countTransfSkipArticle++;
                }
                if (!bDbTransSqlErr)
                {
                    exec sql execute delDateTimeCocp_stagein_article using
                                :cocp_no, :transfDate, :transfTime;
                    ERROR_MSG("failed delDateTimeCocp_stagein_article", bDbTransSqlErr);
                }
                // transfer/delete Cocp list Cocp_stageout_article_code /////////////////////////////////////////
                if (!bDbTransfError && !bDbTransSqlErr)
                {
                    EXEC SQL OPEN selectDatetimeCocp_stageout_article_code using :cocp_no, :transfDate, :transfTime;
                    EXEC SQL FETCH selectDatetimeCocp_stageout_article_code into ESQL_ROWS_INTO;

                    while(SQLCODE==0 && !bDbTransfError && !bDbTransSqlErr)
                    {
                        if (esqlRows[OARTICLE_CODES_SUM_STATE_FLAG_IDX][0]=='8' || esqlRows[OARTICLE_CODES_SUM_STATE_FLAG_IDX][0]=='9')
                        {
                            bDbTransfError = !PutStageoutArticleCode();
                            if (bDbTransfError)
                            {
                                PrintMsg(fun, FEHLER, "Failed article_code tranfer, ocp_no: '%s'", cocp_no);
                            }
                            countLArticleCode++;
                        } else
                        {
                            countTransfSkipArticleCode++;
                        }

                        EXEC SQL FETCH selectDatetimeCocp_stageout_article_code into ESQL_ROWS_INTO;
                    }
                    // delete all related article code
                    if (!bDbTransfError && !bDbTransSqlErr)
                    {
                        exec sql execute delDateTimeCocp_stageout_article_code using
                                    :cocp_no, :transfDate, :transfTime;
                        ERROR_MSG("failed delDateTimeCocp_stageout_article_code", bDbTransSqlErr);
                    }
                    if (!bDbTransfError && !bDbTransSqlErr)
                    {
                        exec sql execute delDateTimeCocp_stagein_articlecode using
                                    :cocp_no, :transfDate, :transfTime;
                        ERROR_MSG("failed delDateTimeCocp_stagein_articlecode", bDbTransSqlErr);
                    }
                }
                // transfer/delete Cocp_stageout_article_price /////////////////////////////////////////
                if (!bDbTransfError && !bDbTransSqlErr)
                {
                    EXEC SQL OPEN selectAllDatevalidfromCocp_stageout_article_price using :cocp_no, :transfDate, :transfTime;
                    EXEC SQL FETCH selectAllDatevalidfromCocp_stageout_article_price into :validFrom;

                    while(SQLCODE==0 && !bDbTransfError && !bDbTransSqlErr)
                    {
                        EXEC SQL OPEN selectDatetimeCocp_stageout_article_price using :cocp_no, :validFrom, :transfDate, :transfTime;
                        EXEC SQL FETCH selectDatetimeCocp_stageout_article_price into ESQL_ROWS_INTO;
                        while(SQLCODE==0 && !bDbTransfError && !bDbTransSqlErr)
                        {
                            if (esqlRows[OARTICLE_PRICE_SUM_STATE_FLAG_IDX][0]=='8' || esqlRows[OARTICLE_PRICE_SUM_STATE_FLAG_IDX][0]=='9')
                            {
                                bDbTransfError = !PutStageoutArticlePrice();
                                if (bDbTransfError)
                                {
                                    PrintMsg(fun, FEHLER, "Failed article_price tranfer, ocp_no: '%s'", cocp_no);
                                }
                                countLArticlePrice++;
                            } else
                            {
                                countTransfSkipArticlePrice++;
                            }

                            EXEC SQL FETCH selectDatetimeCocp_stageout_article_price into ESQL_ROWS_INTO;
                        }
                        EXEC SQL FETCH selectAllDatevalidfromCocp_stageout_article_price into :validFrom;
                    }
                    // delete all related article price
                    if (!bDbTransfError && !bDbTransSqlErr)
                    {
                        exec sql execute delDateTimeCocp_stageout_article_price using
                                    :cocp_no, :transfDate, :transfTime;
                        ERROR_MSG("failed delDateTimeCocp_stageout_article_price", bDbTransSqlErr);
                    }
                    if (!bDbTransfError && !bDbTransSqlErr)
                    {
                        exec sql execute delDateTimeCocp_stagein_articleprice using
                                    :cocp_no, :transfDate, :transfTime;
                        ERROR_MSG("failed delDateTimeCocp_stagein_articleprice", bDbTransSqlErr);
                    }
                }
                // transfer/delete Cocp_stageout_article_france /////////////////////////////////////////
                if (!bDbTransfError && !bDbTransSqlErr)
                {
                    EXEC SQL OPEN selectDatetimeCocp_stageout_article_france using :cocp_no, :transfDate, :transfTime;
                    EXEC SQL FETCH selectDatetimeCocp_stageout_article_france into ESQL_ROWS_INTO;

                    if(SQLCODE==0)
                    {
                        if (esqlRows[OARTICLE_FRANCE_SUM_STATE_FLAG_IDX][0]=='8' || esqlRows[OARTICLE_FRANCE_SUM_STATE_FLAG_IDX][0]=='9')
                        {
                            bDbTransfError = !PutStageoutArticleFrance();
                            if (bDbTransfError)
                            {
                                PrintMsg(fun, FEHLER, "Failed article_france tranfer, ocp_no: '%s'", cocp_no);
                            }
                            else
                            {
                                exec sql execute delDateTimeCocp_stageout_article_france using
                                            :cocp_no, :transfDate, :transfTime;
                                ERROR_MSG("failed delDateTimeCocp_stageout_article_france", bDbTransSqlErr);
                            }
                            countLArticleFrance++;
                        } else
                        {
                            countTransfSkipArticleFrance++;
                        }
                        if (!bDbTransSqlErr)
                        {
                            exec sql execute delDateTimeCocp_stagein_article_france using
                                        :cocp_no, :transfDate, :transfTime;
                            ERROR_MSG("failed delDateTimeCocp_stagein_article_france", bDbTransSqlErr);
                        }

                        EXEC SQL FETCH selectDatetimeCocp_stageout_article_france into ESQL_ROWS_INTO;
                    }
                }

                // commit if no errors occured else rollback
                if (!bDbTransfError && !bDbTransSqlErr)
                {
                    exec sql execute insArticle_update_zpznpflege using :artNo, :curDate;
                    EXEC SQL COMMIT;
                    ERROR_MSG("COMMIT", bDbSqlError);
                    countTransfValidOCPNo++;
                    countTransfArticleCode += countLArticleCode;
                    countTransfArticle += countLArticle;
                    countTransfArticlePrice += countLArticlePrice;
                    countTransfArticleFrance += countLArticleFrance;
                }
                else
                {
                    PrintMsg(fun, FEHLER, "Fatal transfer failure for ocp_no: '%s', ROLLING BACK", cocp_no);
                    EXEC SQL ROLLBACK;
                    countTransfFailedOCPNo++;
                    countTransfFailedArticleCode += countLArticleCode;
                    countTransfFailedArticle += countLArticle;
                    countTransfFailedArticlePrice += countLArticlePrice;
                    countTransfFailedArticleFrance += countLArticleFrance;
                }
                }
            else
            {
                countTransfNotReadyOCPNo++;
            }

            EXEC SQL FETCH selectDatetimeCocp_stageout_article into ESQL_ROWS_INTO;
        }

        PrintMsg(fun, HINWEIS, "Tranfer summary:");
        PrintMsg(fun, HINWEIS, "%i total handled OCPNo: %i transferred, %i failed, %i not ready for transfer",
                 countTransfOCPNo, (countTransfOCPNo - countTransfNotReadyOCPNo - countTransfFailedOCPNo), countTransfFailedOCPNo, countTransfNotReadyOCPNo);
        PrintMsg(fun, HINWEIS, "%i total successfull transferred rows:", countTransfArticle + countTransfArticleFrance + countTransfArticlePrice + countTransfArticleCode);
        PrintMsg(fun, HINWEIS, "   %i transferred article:", countTransfArticle);
        PrintMsg(fun, HINWEIS, "   %i transferred article france", countTransfArticleFrance);
        PrintMsg(fun, HINWEIS, "   %i transferred article price", countTransfArticlePrice);
        PrintMsg(fun, HINWEIS, "   %i transferred article code,", countTransfArticleCode);
        PrintMsg(fun, HINWEIS, "%i total skipped rows:", countTransfSkipArticle + countTransfSkipArticleFrance + countTransfSkipArticlePrice + countTransfSkipArticleCode);
        PrintMsg(fun, HINWEIS, "   %i skipped article,", countTransfSkipArticle);
        PrintMsg(fun, HINWEIS, "   %i skipped article france", countTransfSkipArticleFrance);
        PrintMsg(fun, HINWEIS, "   %i skipped article price", countTransfSkipArticlePrice);
        PrintMsg(fun, HINWEIS, "   %i skipped article code,", countTransfSkipArticleCode);
        PrintMsg(fun, HINWEIS, "%i total failed rows:", countTransfFailedArticle + countTransfFailedArticleFrance + countTransfFailedArticlePrice + countTransfFailedArticleCode);
        PrintMsg(fun, HINWEIS, "   %i failed article,", countTransfFailedArticle);
        PrintMsg(fun, HINWEIS, "   %i failed article france", countTransfFailedArticleFrance);
        PrintMsg(fun, HINWEIS, "   %i failed article price", countTransfFailedArticlePrice);
        PrintMsg(fun, HINWEIS, "   %i failed article code,", countTransfFailedArticleCode);
        PrintMsg( fun, HINWEIS, "Transfer finished ********************************************************************");
    }

    /*******************************************************************************************/
    /* Handle input CSV                                                                        */
    /*******************************************************************************************/

    /* Start SQL transaction*/
    EXEC SQL BEGIN WORK;
    ERROR_MSG("BEGIN WORK", bDbTransact);

    if(bDbSqlError || bDbTransact)
    {

        if (!bDbTransact)
        {
            EXEC SQL ROLLBACK WORK;
        }
        return CSVERR_DATABASE_SQL_ERROR;
    }

    if (csvFileName != NULL)
    {
        PrintMsg( fun, HINWEIS, "Start Import of '%s' csv file into cocp_stagein/cocp_stageout for date/time %08i/%06i", csvFileName, curDate, curTime);
        /**********************************************************/
        /* Parse input CSV and store/colect all ocp_no with flags */
        /**********************************************************/
        CsvParser *csvParser = CsvParser_CreateMultiRows(TmpOutCSVName, ';', rowsStruct, rowsID, CSV_STRUCTS_COUNT);
        int i = 0;
        char *errMsg = NULL;
        int lineErr = 0;
        int errID = 0;
        int fatalExit = 0;
        int countValidInOCP = 0;
        int countRows = 0;
        int countInvalidRows = 0;
        int countUnkownRows = 0;
        int countDuplicateKeys = 0;
        int countNotFoundArticleNo = 0;
        int countErrors = 0;
        int countWarnings = 0;
        int countSkippedRowsOCPNo = 0;
        int curRowCountErrors = 0;
        int curRowCountWarnings = 0;
        int retRes = CSVERR_RET_OK;
        int* ptrCountIns = NULL;
        if (csvParser != NULL)
        {
            // check for fatale errors while opening and parsing header of csv file
            if((errID = CsvParser_getLastErrorID(csvParser)) != CSVERR_NO_ERROR && (errMsg = CsvParser_getLastErrorMessage(csvParser)) != NULL)
            {
                switch(errID)
                {
                    case CSVERR_FILENAME_NULL_PTR:
                    case CSVERR_NOT_SUPPORTED_DELIMITER:
                        retRes = CSVERR_MISSING_OR_WRONG_PARAMETERS;
                        PrintMsg(fun, FEHLER, "Fatal missing or wrong parameters: '%s'", errMsg);
                        CSV_SAFE_FREE(errMsg);
                        break;
                    case CSVERR_FAILED_OPEN_CSV_FILE:
                        retRes = CSVERR_IO_ERROR;
                        PrintMsg(fun, FEHLER, "Fatal i/o error: '%s'", errMsg);
                        CSV_SAFE_FREE(errMsg);
                        break;
                };
            }
            if (retRes != CSVERR_RET_OK)
            {
                CsvParser_DestroyMultiRows(csvParser);
                EXEC SQL ROLLBACK WORK;
                return retRes;
            }
            while (CsvParser_isFinished(csvParser) == 0)
            {
                // getting next row
                csvRow = (sqlRow*)CsvParser_getNextRowMultiRows(csvParser);
                if (csvRow != NULL)
                {
                    int init_ocp_flag = 0;

                    /***** handle encountred errors *******/
                    bool validRow = true;
                    while((errMsg = CsvParser_getErrorMessage(csvParser, &errID, &lineErr)) != NULL)
                    {
                        switch(errID)
                        {
                            // generic errors
                            case CSVERR_REACHED_EOF:
                            case CSVERR_ROW_INSUFFICIENT_COLUMNS_COUNT:
                            case CSVERR_ROW_CROSSED_EXPECTED_COLUMNS_COUNT:
                            case CSVERR_ROW_CROSSED_MAXIMUM_COLUMN_SIZE:
                            //case CSVERR_ROW_FAILED_TO_VALIDATE_COLUMN:
                            //case CSVERR_KEY_CROSSED_MAXIMUM_ALLOCATED_SIZE:
                                validRow = false;
                                break;
                        }
                        CSV_SAFE_FREE(errMsg);
                    }
                    if (validRow)
                    {
                        int nocp_no = atoi(csvRow->fields[OCP_ARTICLE_NO_IDX]);
                        InOCPNoFLAGS* curOCPFLAG = GetInOCPNoFLAGS(nocp_no);
                        switch (csvParser->curRowStructIdx)
                        {
                        case ROWID_ARTICLE_CODES: // articleCodes
                            init_ocp_flag |= IN_OCPNO_HAS_IN_ART_CODE;
                            countTotalInCode ++;
                            break;
                        case ROWID_ARTICLE: // article
                            init_ocp_flag |= IN_OCPNO_HAS_IN_ART;
                            countTotalInArticle ++;
                            break;
                        case ROWID_ARTICLE_PRICE: // articlePrice
                            init_ocp_flag |= IN_OCPNO_HAS_IN_ART_PRICE;
                            countTotalInPrice ++;
                            break;
                        case ROWID_ARTICLE_FRANCE: // articleFrance
                            init_ocp_flag |= IN_OCPNO_HAS_IN_ART_FRANCE;
                            countTotalInFrance ++;
                            break;
                        case -1: // unknown !
                            break;
                        }
                        // new ocp_no
                        if (curOCPFLAG == NULL) {
                            curOCPFLAG = InsertInOCPNo(nocp_no, init_ocp_flag);
                        }
                        else
                        {
                            curOCPFLAG->FLAGS |= init_ocp_flag;
                        }
                        // handle case of updating/adding articleCode codeType 27 mapping
                        if (csvParser->curRowStructIdx == ROWID_ARTICLE_CODES)
                        {
                            curRow = RemapInCSVToImportOrder((CsvRow*)csvRow, csvParser->curRowStructIdx);
                            if (curRow != NULL)
                            {
                                // take infile codetype 27 mapping only if there is no existing mapping
                                if (atoi(curRow[ARTICLE_CODES_CODE_TYPE_IDX]) == 27 && (curOCPFLAG->FLAGS & IN_OCPNO_HAS_ART_NO) == 0)
                                {
                                    TrimStr(curRow[ARTICLE_CODES_ARTICLE_CODE_IDX]);
                                    curOCPFLAG->art_no = atoi(curRow[ARTICLE_CODES_ARTICLE_CODE_IDX]);
                                    if (curOCPFLAG->art_no != 0)
                                    {
                                        curOCPFLAG->FLAGS |= (IN_OCPNO_HAS_ART_NO | IN_OCPNO_HAS_INCSV_ART_NO);
                                        UpdateMasterDATA_FLAGS(curRow[ARTICLE_CODES_ARTICLE_CODE_IDX], &InOCPNoList[InOCPNoCount].FLAGS);
                                        // delete the mapping if no existing pharmos article detected
                                        if ((InOCPNoList[InOCPNoCount].FLAGS & IN_OCPNO_HAS_PH_ART) == 0)
                                        {
                                            InOCPNoList[InOCPNoCount].FLAGS &= IN_OCPNO_MDATA_FLAGS_DELETE;
                                        }
                                    }
                                }

                                FreeRemappedRow(curRow, csvParser->curRowStructIdx);
                                curRow = NULL;
                            }
                        }
                    }
                }

                CsvRow_destroy((CsvRow*)csvRow);
            }

            CsvParser_DestroyMultiRows(csvParser);
            csvParser = NULL;
        }

        /*******************************************************************************************/
        /* create/set defaults rows value for each stagein_xxx and stageout_xxx database table     */
        /*******************************************************************************************/

        articleCodesDefaultRow = CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
        if (articleCodesDefaultRow != NULL) {
            CsvRow_setValues(articleCodesDefaultRow, ARTICLE_CODES_FIELDS_COUNT, articleCodesDefaults);
            RowsDefaultValues[0] = articleCodesDefaultRow;
        }
        articleDefaultRow = CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
        if (articleDefaultRow != NULL) {
            CsvRow_setValues(articleDefaultRow, ARTICLE_FIELDS_COUNT, articleDefaults);
            RowsDefaultValues[1] = articleDefaultRow;
        }
        articlePriceDefaultRow = CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
        if (articlePriceDefaultRow != NULL) {
            CsvRow_setValues(articlePriceDefaultRow, ARTICLE_PRICE_FIELDS_COUNT, articlePriceDefaults);
            RowsDefaultValues[2] = articlePriceDefaultRow;
        }
        articleFranceDefaultRow = CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
        if (articleFranceDefaultRow != NULL) {
            CsvRow_setValues(articleFranceDefaultRow, ARTICLE_FRANCE_FIELDS_COUNT, articleFranceDefaults);
            RowsDefaultValues[3] = articleFranceDefaultRow;
        }
        CreateStageoutDefaultRows();

        /*******************************************************************************************/
        /* Import Into Stageout the Master DATA of all valid input OCP_No                          */
        /*******************************************************************************************/
        PrintMsg( fun, HINWEIS, "Start Import of STAGEOUT from received valid OCPNo");

        // compute count of valid Input OCPNo
        for (int i=0; i < InOCPNoCount; i++)
        {
            if (ImportReadyOCPNo(InOCPNoList[i].ocp_art_no, NULL))
            {
                countValidInOCP++;
            }
        }

        FILE *statusFILE = NULL;
        // generate import status csv if log enabled and we have some invalid OCPNo
        if (bLog && countValidInOCP < InOCPNoCount)
        {
            statusFILE = fopen(ImportStatusCSVName, "wt");
        }
        if (statusFILE != NULL)
        {
            fprintf(statusFILE, "OCP_Article_no;Status;FLAGS;comment\n"); // header
            for (int i=0; i < InOCPNoCount; i++)
            {
                if (ImportReadyOCPNo(InOCPNoList[i].ocp_art_no, NULL))
                {
                    fprintf(statusFILE, "%i;Ok;%x;\n", InOCPNoList[i].ocp_art_no, InOCPNoList[i].FLAGS);
                }
                else
                {
                    fprintf(statusFILE, "%i;Failed;%x;", InOCPNoList[i].ocp_art_no, InOCPNoList[i].FLAGS);
                    if ((InOCPNoList[i].FLAGS&IN_OCPNO_HAS_ART_NO) == 0)
                    {
                        fprintf(statusFILE,"Missing OCP_no to Artile_nr mapping\n");
                    }
                    else if ((InOCPNoList[i].FLAGS&IN_OCPNO_HAS_IN_ART) == 0 && (InOCPNoList[i].FLAGS&IN_OCPNO_HAS_PH_ART) == 0)
                    {
                        fprintf(statusFILE,"New Article missing required article row\n");
                    }
                    else
                    {
                        fprintf(statusFILE,"\n");
                    }
                }
            }
            fclose(statusFILE);
        }

        // if no valid OCPNo found just log the warning an exit succefully
        if (countValidInOCP <= 0)
        {
            PrintMsg(fun, FEHLER, "Warning! No valid OCP_no dectected for %i received.", InOCPNoCount);
        }
        else
        {
            /*////////////////////////////////////*/
            /* handle import of valid OCPNo found */
            /*////////////////////////////////////*/
            bool dbStageOutErr = false;
            bool dbStageOutInsErr = false;
            bool dbStageOutUpdErr = false;
            int IOCPNO_FLAG = 0;
            outRow = (sqlRow*)CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
            for (int i=0; i < InOCPNoCount; i++)
            {
                // skip excluded OCPNo
                if (bExcludeIOCPNo && IsExcludedOCPNo((long)InOCPNoList[i].ocp_art_no))
                {
                    continue;
                }
                sprintf(cocp_no,"%i",InOCPNoList[i].ocp_art_no);
                sprintf(artNo,"%i",InOCPNoList[i].art_no);
                if (ImportReadyCharOCPNo(cocp_no, &IOCPNO_FLAG))
                {
                    if (GetStageoutArticle((CsvRow*)outRow, artNo))
                    {
                        EnsureNotNullRowValues((CsvRow*)outRow);
                        dbStageOutInsErr = false;
                        dbStageOutUpdErr = false;
                        exec sql execute updateCocp_stageout_article using
                            :cocp_no,
                            :artNo,
                            :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                            :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                            :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16],
                            :outRow->fields[17], :outRow->fields[18], :outRow->fields[19], :outRow->fields[20], :outRow->fields[21],
                            :outRow->fields[22], :outRow->fields[23], :outRow->fields[24], :outRow->fields[25], :outRow->fields[26],
                            :outRow->fields[27], :outRow->fields[28], :outRow->fields[29], :outRow->fields[30], :outRow->fields[31],
                            :outRow->fields[32], :outRow->fields[33], :outRow->fields[34], :outRow->fields[35], :outRow->fields[36],
                            :outRow->fields[37], :outRow->fields[38], :outRow->fields[39], :outRow->fields[40], :outRow->fields[41],
                            :outRow->fields[42], :outRow->fields[43], :outRow->fields[44], :outRow->fields[45],
                            :outRow->fields[46], :outRow->fields[47], :curDate, :curTime, :cocp_no;
                        EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
                        dbStageOutUpdErr = (db_exception_count > 1 || db_row_count <= 0);
                        if (dbStageOutUpdErr)
                        {
                            exec sql execute insCocp_stageout_article using \
                                :cocp_no,
                                :artNo,
                                :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                                :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                                :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16],
                                :outRow->fields[17], :outRow->fields[18], :outRow->fields[19], :outRow->fields[20], :outRow->fields[21],
                                :outRow->fields[22], :outRow->fields[23], :outRow->fields[24], :outRow->fields[25], :outRow->fields[26],
                                :outRow->fields[27], :outRow->fields[28], :outRow->fields[29], :outRow->fields[30], :outRow->fields[31],
                                :outRow->fields[32], :outRow->fields[33], :outRow->fields[34], :outRow->fields[35], :outRow->fields[36],
                                :outRow->fields[37], :outRow->fields[38], :outRow->fields[39], :outRow->fields[40], :outRow->fields[41],
                                :outRow->fields[42], :outRow->fields[43], :outRow->fields[44], :outRow->fields[45],
                                :outRow->fields[46], :outRow->fields[47], :curDate, :curTime;
                            dbStageOutInsErr = (SQLCODE<0);
                        }

                        if (dbStageOutInsErr && dbStageOutUpdErr)
                        {
                            PrintMsg( fun, FEHLER, "Skipping ocp_no: '%s', Failed to insert/update cocp_stageout_article", cocp_no);
                            failedInsertItems++;
                            countErrors++;
                            continue;
                        }
                    }
                    else
                    {
                        PrintMsg( fun, HINWEIS, "Warning ocp_no: '%s', No Article master data found!", cocp_no);
                    }


                    // get all article codes of artNo
                    EXEC SQL OPEN SelectCodeTypeFromCarticleCodes using :artNo;
                    EXEC SQL FETCH SelectCodeTypeFromCarticleCodes into :codeType;

                    while(SQLCODE==0)
                    {
                        if (GetStageoutArticleCode((CsvRow*)outRow, artNo, codeType))
                        {
                            EnsureNotNullRowValues((CsvRow*)outRow);
                            dbStageOutInsErr = false;
                            dbStageOutUpdErr = false;
                            exec sql execute updateCocp_stageout_article_code using
                                :cocp_no,
                                :artNo,
                                :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5],
                                :outRow->fields[6], :outRow->fields[7], :outRow->fields[8], :curDate, :curTime, :cocp_no, :artNo, :outRow->fields[OARTICLE_CODES_CODE_TYPE_IDX];
                            EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
                            dbStageOutUpdErr = (db_exception_count > 1 || db_row_count <= 0);
                            // update failed, try to insert
                            if (dbStageOutUpdErr)
                            {
                                exec sql execute insCocp_stageout_articlecode using
                                    :cocp_no,
                                    :artNo,
                                    :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5],
                                    :outRow->fields[6], :outRow->fields[7], :outRow->fields[8], :curDate, :curTime;
                                dbStageOutInsErr = (SQLCODE<0);
                            }

                            if (dbStageOutInsErr && dbStageOutUpdErr)
                            {
                                PrintMsg( fun, FEHLER, "ocp_no: '%s', Failed to insert/update cocp_stageout_article_code", cocp_no);
                                failedInsertItems++;
                                countErrors++;
                            }
                        }
                        else
                        {
                            PrintMsg( fun, HINWEIS, "Warning ocp_no: '%s' codeType '%s', Failed to retrieve master data!", cocp_no, codeType);
                        }
                        EXEC SQL FETCH SelectCodeTypeFromCarticleCodes into :codeType;
                    }

                    if (GetStageoutArticleFrance((CsvRow*)outRow, artNo))
                    {
                        EnsureNotNullRowValues((CsvRow*)outRow);
                        dbStageOutInsErr = false;
                        dbStageOutUpdErr = false;
                        exec sql execute updateCocp_stageout_article_france using
                            :cocp_no,
                            :artNo,
                            :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                            :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                            :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16],
                            :outRow->fields[17], :outRow->fields[18], :outRow->fields[19], :curDate, :curTime, :cocp_no;
                        EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
                        dbStageOutUpdErr = (db_exception_count > 1 || db_row_count <= 0);
                        // update failed, try to insert
                        if (dbStageOutUpdErr)
                        {
                            exec sql execute insCocp_stageout_article_france using
                                :cocp_no,
                                :artNo,
                                :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                                :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                                :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16],
                                :outRow->fields[17], :outRow->fields[18], :outRow->fields[19], :curDate, :curTime;
                            dbStageOutInsErr = (SQLCODE<0);
                        }
                        if (dbStageOutInsErr && dbStageOutUpdErr)
                        {
                            PrintMsg( fun, FEHLER, "ocp_no: '%s', Failed to insert/update cocp_stageout_article_france", cocp_no);
                            failedInsertItems++;
                            countErrors++;
                        }
                    }
                    else
                    {
                        PrintMsg( fun, HINWEIS, "Warning ocp_no: '%s', No Article_france master data found!", cocp_no);
                    }

                    // get all prices for this articleNo
                    EXEC SQL OPEN SelectDateValidFromZartpreis using :artNo;
                    EXEC SQL FETCH SelectDateValidFromZartpreis into :validFrom;

                    while(SQLCODE==0)
                    {
                        GetStageoutArticlePrice((CsvRow*)outRow, validFrom, artNo);
                        EnsureNotNullRowValues((CsvRow*)outRow);
                        dbStageOutInsErr = false;
                        dbStageOutUpdErr = false;
                        exec sql execute updateCocp_stageout_article_price using
                            :cocp_no,
                            :artNo,
                            :validFrom, :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                            :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                            :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16], :outRow->fields[17],
                            :outRow->fields[18], :outRow->fields[19], :outRow->fields[20], :curDate, :curTime, :cocp_no, :validFrom;
                        EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
                        dbStageOutUpdErr = (db_exception_count > 1 || db_row_count <= 0);
                        // update failed, try to insert
                        if (dbStageOutUpdErr)
                        {
                            exec sql execute insCocp_stageout_articleprice using
                                :cocp_no,
                                :artNo,
                                :validFrom, :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                                :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                                :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16], :outRow->fields[17],
                                :outRow->fields[18], :outRow->fields[19], :outRow->fields[20], :curDate, :curTime;
                            dbStageOutInsErr = (SQLCODE<0);
                        }

                        if (dbStageOutInsErr && dbStageOutUpdErr)
                        {
                            PrintMsg( fun, FEHLER, "ocp_no: '%s' data_valid_from '%s', Failed to insert/update cocp_stageout_article_price", cocp_no, validFrom);
                            failedInsertItems++;
                            countErrors++;
                        }

                        EXEC SQL FETCH SelectDateValidFromZartpreis into :validFrom;
                    }

                }
                else
                {
                    PrintMsg(fun, FEHLER, "Skipping ocp_no: '%s', FLAG 0x%x", cocp_no, IOCPNO_FLAG);
                }
            }
            CsvRow_destroy((CsvRow*)outRow);


            /*******************************************************************************************/
            /* Parse input CSV & export/update each row to its cocp_stagein_xxxx database table        */
            /* Create/update cocp_stageout_xxx database rows either stagein or Pharmos database tables */
            /*******************************************************************************************/
            PrintMsg( fun, HINWEIS, "Start Import of STAGEIN input CSV and update of stageout");

            csvParser = CsvParser_CreateMultiRows(TmpOutCSVName, ';', rowsStruct, rowsID, CSV_STRUCTS_COUNT);
            if (csvParser != NULL)
            {
                // check for fatale errors while opening and parsing header of csv file
                if((errID = CsvParser_getLastErrorID(csvParser)) != CSVERR_NO_ERROR && (errMsg = CsvParser_getLastErrorMessage(csvParser)) != NULL)
                {
                    switch(errID)
                    {
                        case CSVERR_FILENAME_NULL_PTR:
                        case CSVERR_NOT_SUPPORTED_DELIMITER:
                            retRes = CSVERR_MISSING_OR_WRONG_PARAMETERS;
                            PrintMsg(fun, FEHLER, "Fatal missing or wrong parameters: '%s'", errMsg);
                            CSV_SAFE_FREE(errMsg);
                            break;
                        case CSVERR_FAILED_OPEN_CSV_FILE:
                            retRes = CSVERR_IO_ERROR;
                            PrintMsg(fun, FEHLER, "Fatal i/o error: '%s'", errMsg);
                            CSV_SAFE_FREE(errMsg);
                            break;
                    };
                }

                // set key
                if (CsvParser_isFinished(csvParser) == 0)
                {
                    // enable key duplicates checking
                    CsvParser_EnableKeyMultiRows(csvParser, keysIndexes, keysCount);

                    // check for fatale errors while setting Key - for now ignored
                    while((errMsg = CsvParser_getErrorMessage(csvParser, &errID, &lineErr)) != NULL)
                    {
                        switch(errID)
                        {
                            case CSVERR_KEY_INVALID_COLUMNS_COUNT_OR_PTR:
                            break;
                            case CSVERR_KEY_INVALID_COLUMN_INDEX:
                            break;
                            case CSVERR_KEY_CROSSED_MAXIMUM_COLUMNS_COUNT:
                            break;
                        }
                        CSV_SAFE_FREE(errMsg);
                    }
                }

                CsvParser_SetDefaultRowMultiRows(csvParser, RowsDefaultValues);

                // extract/export all the rows on the input csv file
                while (CsvParser_isFinished(csvParser) == 0)
                {
                    // getting next row
                    csvRow = (sqlRow*)CsvParser_getNextRowMultiRows(csvParser);
                    if (csvRow != NULL)
                    {
                        curRowCountErrors = 0;
                        curRowCountWarnings = 0;

                        countRows ++;
                        /** validations erros are just displayed on the log(if enabled), all data exported as is, except for unknown RowID */
                        if ( CsvParser_getCurRowErrorsCount(csvParser) > 0)
                        {

                            /***** handle encountred errors *******/
                            while((errMsg = CsvParser_getErrorMessage(csvParser, &errID, &lineErr)) != NULL)
                            {
                                switch(errID)
                                {
                                    // generic errors
                                    case CSVERR_REACHED_EOF:
                                        break;
                                    case CSVERR_ROW_INSUFFICIENT_COLUMNS_COUNT:
                                    case CSVERR_ROW_CROSSED_EXPECTED_COLUMNS_COUNT:
                                    case CSVERR_ROW_CROSSED_MAXIMUM_COLUMN_SIZE:
                                    case CSVERR_ROW_FAILED_TO_VALIDATE_COLUMN:
                                    case CSVERR_KEY_CROSSED_MAXIMUM_KEYS_COUNT:
                                    case CSVERR_KEY_FAILED_TO_BUILD_KEY:
                                    case CSVERR_KEY_CROSSED_MAXIMUM_ALLOCATED_SIZE:
                                    case CSVERR_KEY_DUPLICATED:
                                        if (errID == CSVERR_KEY_DUPLICATED) {
                                            PrintMsg(fun, FEHLER, "error line %i: '%s'", csvParser->lineCount -1, errMsg);
                                            countDuplicateKeys++;
                                            curRowCountErrors++;
                                        }
                                        else
                                        {
                                            PrintMsg(fun, HINWEIS, "Warning line %i: '%s'", csvParser->lineCount -1, errMsg);
                                            curRowCountWarnings++;
                                        }
                                        break;
                                }
                                CSV_SAFE_FREE(errMsg);
                            }
                        }
                        // check if this row ocp_no is valid for stagein
                        if (csvParser->curRowStructIdx == -1)
                        {
                            PrintMsg(fun, FEHLER, "Warning: Skipping row %i: invalid contents", csvParser->lineCount -1);
                            curRowCountWarnings++;
                            countSkippedRowsOCPNo++;
                            countUnkownRows++;
                            CsvRow_destroy((CsvRow*)csvRow);
                            countErrors += curRowCountErrors;
                            countWarnings += curRowCountWarnings;
                            continue;
                        }
                        TrimStr(csvRow->fields[OCP_ARTICLE_NO_IDX]);
                        if (!ImportReadyCharOCPNo(csvRow->fields[OCP_ARTICLE_NO_IDX], NULL))
                        {
                            PrintMsg(fun, FEHLER, "Warning: Skipping row %i: OCPNo '%s' not ready for import", csvParser->lineCount -1, csvRow->fields[OCP_ARTICLE_NO_IDX]);
                            curRowCountWarnings++;
                            countSkippedRowsOCPNo++;
                            countInvalidRows++;
                            CsvRow_destroy((CsvRow*)csvRow);
                            countErrors += curRowCountErrors;
                            countWarnings += curRowCountWarnings;
                            continue;
                        }

                        // check if ocpno is in exclude list
                        if (bExcludeIOCPNo && IsExcludedOCPNo((long)atoi(csvRow->fields[OCP_ARTICLE_NO_IDX])))
                        {
                            CsvRow_destroy((CsvRow*)csvRow);

                            switch (csvParser->curRowStructIdx)
                            {
                            case ROWID_ARTICLE_CODES: // articleCodes
                                countExcludedInCode ++;
                                countExcludedRow ++;
                                break;
                            case ROWID_ARTICLE: // article
                                countExcludedInArticle ++;
                                countExcludedRow ++;
                                break;
                            case ROWID_ARTICLE_PRICE: // articlePrice
                                countExcludedInPrice ++;
                                countExcludedRow ++;
                                break;
                            case ROWID_ARTICLE_FRANCE: // articleFrance
                                countExcludedInFrance ++;
                                countExcludedRow ++;
                                break;
                            case -1: // unknown !
                                break;

                            }

                            continue;
                        }

                        // remap csvRow to curRow as fields order isn't the same between input csv and ocp_stagein_xxx database tables
                        curRow = RemapInCSVToImportOrder((CsvRow*)csvRow, csvParser->curRowStructIdx);
                        if (curRow == NULL)
                        {
                            PrintMsg(fun, FEHLER, "Failed remapping of rowID %i", csvParser->curRowStructIdx);
                            CsvRow_destroy((CsvRow*)csvRow);
                            continue;
                        }


                        // insert row data in it's cocp_stagein_xxx database table
                        ptrCountIns = NULL;

                        switch(csvParser->curRowStructIdx)
                        {
                        case ROWID_ARTICLE_CODES: // articleCodes
                            // insert row data into database table 'insCocp_stagein_articlecode'
                            CleanArticleCodeStageinRow(curRow);
                            exec sql execute insCocp_stagein_articlecode using
                                :curDate,
                                :curTime,
                                :curRow[OCP_ARTICLE_NO_IDX],
                                :curRow[ARTICLE_CODES_CODE_TYPE_IDX],
                                :curRow[ARTICLE_CODES_ARTICLE_CODE_IDX],
                                :curRow[ARTICLE_CODES_PREFERRED_FLAG_IDX],
                                :curRow[ARTICLE_CODES_CHANGED_DATE_IDX];
                            ptrCountIns = &countInsCode;

                            break;
                        case ROWID_ARTICLE: // article
                            CleanArticleStageinRow(curRow);
                            strcpy(cocp_no, curRow[OCP_ARTICLE_NO_IDX]);
                            exec sql execute insCocp_stagein_article using
                                :curDate,
                                :curTime,
                                :curRow[OCP_ARTICLE_NO_IDX],
                                :curRow[ARTICLE_LONG_NAME_IDX],
                                :curRow[ARTICLE_UNIT_IDX],
                                :curRow[ARTICLE_DOSAGE_FORM_IDX],
                                :curRow[ARTICLE_PRODUCT_GROUP_IDX],
                                :curRow[ARTICLE_PRODUCT_TYPE_IDX],
                                :curRow[ARTICLE_MANUFACTURER_NO_IDX],
                                :curRow[ARTICLE_SUPPLIER_NO_IDX],
                                :curRow[ARTICLE_LENGTH_IDX],
                                :curRow[ARTICLE_WIDTH_IDX],
                                :curRow[ARTICLE_HEIGHT_IDX],
                                :curRow[ARTICLE_WEIGHT_IDX],
                                :curRow[ARTICLE_PACKAGE_UNIT_1_IDX],
                                :curRow[ARTICLE_PACKAGE_UNIT_2_IDX],
                                :curRow[ARTICLE_PACKAGE_UNIT_3_IDX],
                                :curRow[ARTICLE_PACKAGE_UNIT_4_IDX],
                                :curRow[ARTICLE_CREATION_DATE_IDX],
                                :curRow[ARTICLE_MODIFICATION_DATE_IDX],
                                :curRow[ARTICLE_EXPIRY_DATE_IDX],
                                :curRow[ARTICLE_OUT_OF_MARKET_DATE_IDX],
                                :curRow[ARTICLE_DURATION_MONTHS_IDX],
                                :curRow[ARTICLE_NEGATIVE_LIST_IDX],
                                :curRow[ARTICLE_BATCH_ARTICLE_IDX],
                                :curRow[ARTICLE_COOLING_ARTICLE_IDX],
                                :curRow[ARTICLE_NARCOTICS_IDX],
                                :curRow[ARTICLE_FMD_RELEVANT_IDX],
                                :curRow[ARTICLE_VETERINARY_IDX],
                                :curRow[ARTICLE_PRESCRIPTION_NEEDED_IDX],
                                :curRow[ARTICLE_PSYCHOTROPE_IDX],
                                :curRow[ARTICLE_ZYTOSTATIC_IDX],
                                :curRow[ARTICLE_BLOCKED_IDX],
                                :curRow[ARTICLE_NOT_ALLOWED_IDX],
                                :curRow[ARTICLE_TAX_IDX],
                                :curRow[ARTICLE_PHARMACY_ONLY_IDX],
                                :curRow[ARTICLE_MEDICATION_IDX],
                                :curRow[ARTICLE_TOXIC_IDX],
                                :curRow[ARTICLE_VERY_TOXIC_IDX],
                                :curRow[ARTICLE_HARMFUL_IDX],
                                :curRow[ARTICLE_HOMEOPATHY_IDX],
                                :curRow[ARTICLE_MEDICAL_GASES_IDX];
                            ptrCountIns = &countInsArticle;

                            break;
                        case ROWID_ARTICLE_PRICE: // articlePrice
                            CleanArticlePriceStageinRow(curRow);
                            exec sql execute insCocp_stagein_articleprice using
                                :curDate,
                                :curTime,
                                :curRow[OCP_ARTICLE_NO_IDX],
                                :curRow[ARTICLE_PRICE_VALID_FROM_DATE_IDX],
                                :curRow[ARTICLE_PRICE_MANUFACTURER_BASE_PRICE_IDX],
                                :curRow[ARTICLE_PRICE_SUPPLIER_BASE_PRICE_IDX],
                                :curRow[ARTICLE_PRICE_PHARMACY_BASE_PRICE_IDX],
                                :curRow[ARTICLE_PRICE_PHARMACY_BUY_PRICE_IDX],
                                :curRow[ARTICLE_PRICE_MAX_PHARMACY_BUY_PRICE_IDX],
                                :curRow[ARTICLE_PRICE_PHARMACY_SELL_PRICE_IDX],
                                :curRow[ARTICLE_PRICE_RECOM_PHARMACY_SELL_PRICE_IDX],
                                :curRow[ARTICLE_PRICE_MAX_PHARMACY_SELL_PRICE_IDX],
                                :curRow[ARTICLE_PRICE_MANUFACTURER_PERCENTAGE_IDX],
                                :curRow[ARTICLE_PRICE_REFUND_AMOUNT],
                                :curRow[ARTICLE_PRICE_VAT_CODE_IDX],
                                :curRow[ARTICLE_PRICE_PRICE_TYPE_IDX],
                                :curRow[ARTICLE_PRICE_PRICE_MODEL_IDX],
                                :curRow[ARTICLE_PRICE_DISCOUNT_DEDUCED_YET_IDX],
                                :curRow[ARTICLE_PRICE_PUBLICATION_NUMBER_IDX];
                            ptrCountIns = &countInsPrice;

                            break;
                        case ROWID_ARTICLE_FRANCE: // articleFrance
                            CleanArticleFranceStageinRow(curRow);
                            exec sql execute insCocp_stagein_article_france using
                                :curDate,
                                :curTime,
                                :curRow[OCP_ARTICLE_NO_IDX],
                                :curRow[ARTICLE_FRANCE_REIMBURSEMENT_PERC_IDX],
                                :curRow[ARTICLE_FRANCE_REIMBURSEMENT_VAL_IDX],
                                :curRow[ARTICLE_FRANCE_UNIT_MULTIPLE_IDX],
                                :curRow[ARTICLE_FRANCE_QTY_SUBMULTIPLE_IDX],
                                :curRow[ARTICLE_FRANCE_RESERVE_HOSP_IDX],
                                :curRow[ARTICLE_FRANCE_REIMBURSEMENT_TYPE_IDX],
                                :curRow[ARTICLE_FRANCE_NOT_VIA_EDI_IDX],
                                :curRow[ARTICLE_FRANCE_CODE_BLOCAGE_IDX],
                                :curRow[ARTICLE_FRANCE_CODE_LPPR_IDX],
                                :curRow[ARTICLE_FRANCE_TFR_BASE_PRICE_IDX],
                                :curRow[ARTICLE_FRANCE_DISTR_RESTR_EXPORT_IDX],
                                :curRow[ARTICLE_FRANCE_DISTR_RESTR_LEGAL_IDX],
                                :curRow[ARTICLE_FRANCE_DISTR_RESTR_BREIZH_IDX],
                                :curRow[ARTICLE_FRANCE_DISTR_RESTR_HOSP_IDX],
                                :curRow[ARTICLE_FRANCE_REBATE_GROUP_SPEC_IDX];
                            ptrCountIns = &countInsFrance;

                            break;
                        case -1: // unknown !
                            ptrCountIns = NULL;
                            break;

                        }

                        // Failed to insert ?
                        if (SQLCODE < 0 && SQLCODE != SQLNOTFOUND)
                        {
                            rgetmsg((short)SQLCODE, sqlErrMsg, sizeof(sqlErrMsg));
                            ReplaceLineEndBySpace(sqlErrMsg);
                            strcpy(ErrMsgFormat, "Database failed to insert row '%s' OCPNo '%s', in line %i: ");
                            strcat(ErrMsgFormat, sqlErrMsg);
                            PrintMsg(fun, FEHLER, ErrMsgFormat, rowsID[csvParser->curRowStructIdx], curRow[OCP_ARTICLE_NO_IDX], csvParser->lineCount - 1, SQLERRM);
                            failedInsertItems++;
                            countErrors++;
                        }
                        else if (ptrCountIns != NULL)
                        {

                            // increment count of inserted rows
                            (*ptrCountIns)++;

                            // delete any stagein_xxx row deprecated after the successfull insert
                            switch(csvParser->curRowStructIdx)
                            {
                            case ROWID_ARTICLE_CODES: // articleCodes
                                exec sql execute delCleanCocp_stagein_articlecode using
                                    :curRow[OCP_ARTICLE_NO_IDX], :curDate, :curDate, :curTime;
                                ERROR_MSG("failed delCleanCocp_stagein_articlecode", bDbSqlError);
                                break;
                            case ROWID_ARTICLE: // article
                                // article -----------
                                exec sql execute delCleanCocp_stagein_article using
                                    :curRow[OCP_ARTICLE_NO_IDX], :curDate, :curDate, :curTime;
                                    ERROR_MSG("failed delCleanCocp_stagein_article", bDbSqlError);
                                break;
                            case ROWID_ARTICLE_PRICE: // articlePrice
                                exec sql execute delCleanCocp_stagein_articleprice using
                                    :curRow[OCP_ARTICLE_NO_IDX], :curDate, :curTime, :curRow[ARTICLE_PRICE_VALID_FROM_DATE_IDX];
                                ERROR_MSG("failed delCleanCocp_stagein_articleprice", bDbSqlError);
                                break;
                            case ROWID_ARTICLE_FRANCE: // articleFrance
                                exec sql execute delCleanCocp_stagein_article_france using
                                    :curRow[OCP_ARTICLE_NO_IDX], :curDate, :curDate, :curTime;
                                ERROR_MSG("failed delCleanCocp_stagein_article_france", bDbSqlError);
                                break;
                            }

                            bool foundArtNo = false;

                            // insert/update cocp_stageout_xxxx tables
                            InOCPNoFLAGS *ocpInfo = GetInCharOCPNoFLAGS(curRow[OCP_ARTICLE_NO_IDX]);
                            foundArtNo = (ocpInfo != NULL);
                            if (!foundArtNo)
                            {
                                strcpy(artNo, "");
                            }
                            else
                            {
                                sprintf(artNo,"%i", ocpInfo->art_no);
                            }

                            bool bDbInsSqlError = false;
                            switch(csvParser->curRowStructIdx)
                            {
                            case ROWID_ARTICLE_CODES: // articleCodes

                                outRow = (sqlRow*)CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
                                GetStageoutArticleCodeFromStagein((CsvRow*)outRow, curRow, artNo);
                                TrimStr(outRow->fields[OARTICLE_CODES_OCP_NO_IDX]);
                                EnsureNotNullRowValues((CsvRow*)outRow);
                                dbStageOutInsErr = false;
                                dbStageOutUpdErr = false;
                                exec sql execute updateCocp_stageout_article_code using
                                    :outRow->fields[OARTICLE_CODES_OCP_NO_IDX],
                                    :artNo,
                                    :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5],
                                    :outRow->fields[6], :outRow->fields[7], :outRow->fields[8], :curDate, :curTime, :outRow->fields[OARTICLE_CODES_OCP_NO_IDX], :artNo, :outRow->fields[OARTICLE_CODES_CODE_TYPE_IDX];

                                EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
                                dbStageOutUpdErr = (db_exception_count > 1 || db_row_count <= 0);
                                // update failed, try to insert
                                if (dbStageOutUpdErr)
                                {
                                    exec sql execute insCocp_stageout_articlecode using
                                        :outRow->fields[OARTICLE_CODES_OCP_NO_IDX],
                                        :artNo,
                                        :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5],
                                        :outRow->fields[6], :outRow->fields[7], :outRow->fields[8], :curDate, :curTime;
                                    dbStageOutInsErr = (SQLCODE<0);
                                }
                                if (dbStageOutInsErr && dbStageOutUpdErr)
                                {
                                    PrintMsg( fun, FEHLER, "ocp_no: '%s', Failed to insert/update cocp_stageout_article_code", outRow->fields[OARTICLE_CODES_OCP_NO_IDX]);
                                    failedInsertItems++;
                                    countErrors++;
                                }
                                CsvRow_destroy((CsvRow*)outRow);

                                break;
                            case ROWID_ARTICLE: // article
                                // article -----------
                                outRow = (sqlRow*)CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
                                GetStageoutArticleFromStagein((CsvRow*)outRow, curRow, artNo);
                                TrimStr(outRow->fields[OARTICLE_OCP_NO_IDX]);
                                EnsureNotNullRowValues((CsvRow*)outRow);
                                dbStageOutInsErr = false;
                                dbStageOutUpdErr = false;
                                // update Cocp_stageout_article with stagein values except for fields [manufacturer, supplier, productType, DosageForm and Unit]
                                // which keep having pharmos value, else 0
                                exec sql execute updateCocp_stageout_article2 using
                                    :outRow->fields[OARTICLE_OCP_NO_IDX],
                                    :artNo,
                                    :outRow->fields[2], /*:outRow->fields[3], :outRow->fields[4],*/ :outRow->fields[5], /*:outRow->fields[6],*/
                                    /*:outRow->fields[7], :outRow->fields[8],*/ :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                                    :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16],
                                    :outRow->fields[17], :outRow->fields[18], :outRow->fields[19], :outRow->fields[20], :outRow->fields[21],
                                    :outRow->fields[22], :outRow->fields[23], :outRow->fields[24], :outRow->fields[25], :outRow->fields[26],
                                    :outRow->fields[27], :outRow->fields[28], :outRow->fields[29], :outRow->fields[30], :outRow->fields[31],
                                    :outRow->fields[32], :outRow->fields[33], :outRow->fields[34], :outRow->fields[35], :outRow->fields[36],
                                    :outRow->fields[37], :outRow->fields[38], :outRow->fields[39], :outRow->fields[40], :outRow->fields[41],
                                    :outRow->fields[42], :outRow->fields[43], :outRow->fields[44], :outRow->fields[45],
                                    :outRow->fields[46], :outRow->fields[47], :curDate, :curTime, :outRow->fields[OARTICLE_OCP_NO_IDX];

                                EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
                                dbStageOutUpdErr = (db_exception_count > 1 || db_row_count <= 0);
                                // update failed, try to insert
                                if (dbStageOutUpdErr)
                                {
                                    exec sql execute insCocp_stageout_article using
                                        :outRow->fields[OARTICLE_OCP_NO_IDX],
                                        :artNo,
                                        :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                                        :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                                        :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16],
                                        :outRow->fields[17], :outRow->fields[18], :outRow->fields[19], :outRow->fields[20], :outRow->fields[21],
                                        :outRow->fields[22], :outRow->fields[23], :outRow->fields[24], :outRow->fields[25], :outRow->fields[26],
                                        :outRow->fields[27], :outRow->fields[28], :outRow->fields[29], :outRow->fields[30], :outRow->fields[31],
                                        :outRow->fields[32], :outRow->fields[33], :outRow->fields[34], :outRow->fields[35], :outRow->fields[36],
                                        :outRow->fields[37], :outRow->fields[38], :outRow->fields[39], :outRow->fields[40], :outRow->fields[41],
                                        :outRow->fields[42], :outRow->fields[43], :outRow->fields[44], :outRow->fields[45],
                                        :outRow->fields[46], :outRow->fields[47], :curDate, :curTime;
                                    dbStageOutInsErr = (SQLCODE<0);
                                }
                                if (dbStageOutInsErr && dbStageOutUpdErr)
                                {
                                    PrintMsg( fun, FEHLER, "ocp_no: '%s', Failed to insert/update cocp_stageout_article", outRow->fields[OARTICLE_OCP_NO_IDX]);
                                    failedInsertItems++;
                                    countErrors++;
                                }
                                CsvRow_destroy((CsvRow*)outRow);

                                break;
                            case ROWID_ARTICLE_PRICE: // articlePrice
                                TrimStr(curRow[ARTICLE_PRICE_VALID_FROM_DATE_IDX]);
                                strcpy(validFrom, curRow[ARTICLE_PRICE_VALID_FROM_DATE_IDX]);
                                outRow = (sqlRow*)CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
                                GetStageoutArticlePriceFromStagein((CsvRow*)outRow, curRow, artNo);
                                TrimStr(outRow->fields[OARTICLE_PRICE_OCP_NO_IDX]);
                                EnsureNotNullRowValues((CsvRow *)outRow);
                                dbStageOutInsErr = false;
                                dbStageOutUpdErr = false;
                                exec sql execute updateCocp_stageout_article_price using
                                    :outRow->fields[OARTICLE_PRICE_OCP_NO_IDX],
                                    :artNo,
                                    :validFrom, :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                                    :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                                    :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16], :outRow->fields[17],
                                    :outRow->fields[18], :outRow->fields[19], :outRow->fields[20], :curDate, :curTime, :outRow->fields[OARTICLE_PRICE_OCP_NO_IDX], :validFrom;

                                EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
                                dbStageOutUpdErr = (db_exception_count > 1 || db_row_count <= 0);
                                // update failed, try to insert
                                if (dbStageOutUpdErr)
                                {
                                    exec sql execute insCocp_stageout_articleprice using
                                        :outRow->fields[OARTICLE_PRICE_OCP_NO_IDX],
                                        :artNo,
                                        :validFrom, :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                                        :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                                        :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16], :outRow->fields[17],
                                        :outRow->fields[18], :outRow->fields[19], :outRow->fields[20], :curDate, :curTime;
                                    dbStageOutInsErr = (SQLCODE<0);
                                }

                                if (dbStageOutInsErr && dbStageOutUpdErr)
                                {
                                    PrintMsg( fun, FEHLER, "ocp_no: '%s', data_valid_from '%s', Failed to insert/update cocp_stageout_article_price", outRow->fields[OARTICLE_PRICE_OCP_NO_IDX], validFrom);
                                    failedInsertItems++;
                                    countErrors++;
                                }
                                CsvRow_destroy((CsvRow*)outRow);

                                break;
                            case ROWID_ARTICLE_FRANCE: // articleFrance
                                outRow = (sqlRow*)CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
                                GetStageoutArticleFranceFromStagein((CsvRow*)outRow, curRow, artNo);
                                TrimStr(outRow->fields[OARTICLE_FRANCE_OCP_NO_IDX]);
                                EnsureNotNullRowValues((CsvRow *)outRow);
                                dbStageOutInsErr = false;
                                dbStageOutUpdErr = false;
                                exec sql execute updateCocp_stageout_article_france using
                                    :outRow->fields[OARTICLE_FRANCE_OCP_NO_IDX],
                                    :artNo,
                                    :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                                    :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                                    :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16],
                                    :outRow->fields[17], :outRow->fields[18], :outRow->fields[19], :curDate, :curTime, :outRow->fields[OARTICLE_FRANCE_OCP_NO_IDX];

                                EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
                                dbStageOutUpdErr = (db_exception_count > 1 || db_row_count <= 0);
                                // update failed, try to insert
                                if (dbStageOutUpdErr)
                                {
                                    exec sql execute insCocp_stageout_article_france using
                                        :outRow->fields[OARTICLE_FRANCE_OCP_NO_IDX],
                                        :artNo,
                                        :outRow->fields[2], :outRow->fields[3], :outRow->fields[4], :outRow->fields[5], :outRow->fields[6],
                                        :outRow->fields[7], :outRow->fields[8], :outRow->fields[9], :outRow->fields[10], :outRow->fields[11],
                                        :outRow->fields[12], :outRow->fields[13], :outRow->fields[14], :outRow->fields[15], :outRow->fields[16],
                                        :outRow->fields[17], :outRow->fields[18], :outRow->fields[19], :curDate, :curTime;
                                    dbStageOutInsErr = (SQLCODE<0);
                                }

                                if (dbStageOutInsErr && dbStageOutUpdErr)
                                {
                                    PrintMsg( fun, FEHLER, "ocp_no: '%s', Failed to insert/update cocp_stageout_article_france", outRow->fields[OARTICLE_FRANCE_OCP_NO_IDX]);
                                    failedInsertItems++;
                                    countErrors++;
                                }
                                CsvRow_destroy((CsvRow*)outRow);
                                break;
                            }
                        }
                        if (curRow != NULL)
                        {
                            FreeRemappedRow(curRow, csvParser->curRowStructIdx);
                            curRow = NULL;
                        }
                    }

                    /** count total errors/warning */
                    countErrors += curRowCountErrors;
                    countWarnings += curRowCountWarnings;
                    CsvRow_destroy((CsvRow*)csvRow);
                }
                CsvParser_DestroyMultiRows(csvParser);
                csvParser = NULL;

            }
            /*///////////////////////////////////////////////*/
            /* END OF - handling import of valid OCPNo found */
            /*///////////////////////////////////////////////*/
        }

        /*****Insert Status data  **********/

        countFailedInCode = countTotalInCode - countInsCode - countExcludedInCode;
        countFailedInArticle = countTotalInArticle - countInsArticle - countExcludedInArticle;
        countFailedInPrice = countTotalInPrice - countInsPrice - countExcludedInPrice;
        countFailedInFrance = countTotalInFrance - countInsFrance - countExcludedInFrance;
        countInsExCode = countInsCode + countExcludedInCode;
        countInsExArticle = countInsArticle + countExcludedInArticle;
        countInsExPrice = countInsPrice + countExcludedInPrice;
        countInsExFrance = countInsFrance + countExcludedInFrance;

        exec sql execute updateCocp_stagein_status using
            : curDate,
            : curTime,
            : FileName,
            : countInsExCode,
            : countInsExArticle,
            : countInsExPrice,
            : countInsExFrance,
            : countFailedInCode,
            : countFailedInArticle,
            : countFailedInPrice,
            : countFailedInFrance,
            : curDate,
            : curTime;

        EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
        if (db_exception_count > 1 || db_row_count <= 0)
        {
            exec sql execute insCocp_stagein_status using
                : curDate,
                : curTime,
                : FileName,
                : countInsExCode,
                : countInsExArticle,
                : countInsExPrice,
                : countInsExFrance,
                : countFailedInCode,
                : countFailedInArticle,
                : countFailedInPrice,
                : countFailedInFrance;

            if (SQLCODE < 0 && SQLCODE != SQLNOTFOUND)
            {
                strcpy(ErrMsgFormat, "Database failed to update/insert cocp_stagein_status '%08i/%06i': FileName '%s'");
                PrintMsg(fun, FEHLER, ErrMsgFormat, curDate, curTime, FileName);
            }
        }

        /**** handle errors count **********/
        PrintMsg(fun, HINWEIS, "%i error(s) detected", countErrors);
        PrintMsg(fun, HINWEIS, "%i warnings(s) detected", countWarnings);
        PrintMsg(fun, HINWEIS, "%i duplicated keys", countDuplicateKeys);
        PrintMsg(fun, HINWEIS, "%i unknown rows", countUnkownRows);
        PrintMsg(fun, HINWEIS, "%i failed article rows / total %i,", countFailedInArticle, countTotalInArticle);
        PrintMsg(fun, HINWEIS, "%i failed article france / total %i,", countFailedInFrance, countTotalInFrance);
        PrintMsg(fun, HINWEIS, "%i failed article price / total %i,", countFailedInPrice, countTotalInPrice);
        PrintMsg(fun, HINWEIS, "%i failed article code / total %i,", countFailedInCode, countTotalInCode);
        PrintMsg(fun, HINWEIS, "%i total database failed to insert/update rows", failedInsertItems);
        PrintMsg(fun, HINWEIS, "%i total input OCPNo: %i not ready for import, %i valid, %i excluded", InOCPNoCount, InOCPNoCount- countValidInOCP, countValidInOCP, countExcludedOCPNo);
        PrintMsg(fun, HINWEIS, "%i skipped rows", countSkippedRowsOCPNo);
        PrintMsg(fun, HINWEIS, "%i excluded rows", countExcludedRow);
        PrintMsg(fun, HINWEIS, "%i total row(s): %i with errors/warning, %i valid", countRows, countSkippedRowsOCPNo+failedInsertItems, countRows-countSkippedRowsOCPNo-failedInsertItems);
        PrintMsg(fun, HINWEIS, "%i ocp row(s) exported to stagein successfully", countRows - (failedInsertItems+countSkippedRowsOCPNo+countExcludedRow));
    }
    EXEC SQL COMMIT WORK;
    ERROR_MSG("COMMIT WORK", bDbSqlError);

    return CSVERR_RET_OK;
}

static void GenFilesNames()
{
    char *env;
    va_list arg_ptr;
    char dstDir[256] = "";

    // gen tmp csv file name
    env = getenv( "DATA_PATH" );
    if (env == NULL)
    {
        env = ".";
    }
    sprintf(dstDir, "%s/ocp", env);
    mkdir(dstDir, 0777); // try create if not exising directory
    sprintf(TmpOutCSVName, "%s/COCP-%08i-%06i.csv", dstDir, curDate, curTime);

    // gen status import file name
    env = getenv( "LOG_PATH" );
    if (env == NULL)
    {
        env = ".";
    }
    sprintf(ImportStatusCSVName, "%s/importocp-status-%08i-%06i.csv", env, curDate, curTime);
    sprintf(ImportStatusLogCSVName, "%s/importocp-status-%08i-%06i.csv.log", env, curDate, curTime);
}


/************************************************************************************************************/
/* static void PrintMsg(char *fun, char mld, char *error_msgFormat, ... )                                   */
/************************************************************************************************************/
void PrintMsg( char *fun, char mld, char *error_msgFormat, ... )
{
    // log enabled ?
    if (!bLog)
    {
        return;
    }
    FILE *fp;
    struct tm *stime;
    long shour;
    pid_t pid;
    char logFile[L_TEXT];
    char *env;
    va_list arg_ptr;

    pid = getpid();
    shour = time( &shour );
    stime  = localtime( &shour );

    env = getenv( "LOG_PATH" );
    if (env == NULL)
    {
        env = ".";
    }
    sprintf(logFile, "%s/importocp.log", env);

    if ((fp = fopen( logFile, "a" )) == NULL)
    {
        return;
    }

    if (stime->tm_year > 99)
    {
        stime->tm_year -= 100;
    }

    fprintf(fp, "%c %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s ",
        mld,
        stime->tm_mday, stime->tm_mon + 1, stime->tm_year,
        stime->tm_hour, stime->tm_min, stime->tm_sec,
        pid,
        "ocp_import_stagein",
        fun);

    va_start(arg_ptr, error_msgFormat);
    vfprintf(fp, error_msgFormat, arg_ptr);
    va_end(arg_ptr);

    fprintf(fp, "\n");
    fclose(fp);
}

/************************************************************************************************************/
/* static long GetCurDate() : return long containing current date in YYYYMMDD format                        */
/************************************************************************************************************/
long GetCurDate()
{
    struct tm *stime;
    long shour;

    shour = time( &shour );
    stime  = localtime( &shour );

    return ((stime->tm_year+1900) * 10000) + ((stime->tm_mon + 1) * 100) + stime->tm_mday;
}

/************************************************************************************************************/
/* static long GetCurTime() : return long containing current time in HHMMSS format                        */
/************************************************************************************************************/
long GetCurTime()
{
    struct tm *stime;
    long shour;

    shour = time( &shour );
    stime  = localtime( &shour );

    return ((stime->tm_hour) * 10000) + ((stime->tm_min) * 100) + stime->tm_sec;
}

/************************************************************************************************************/
/* static void ReplaceLineEndBySpace(char *str) : replace any \n or \r found on the string by space         */
/************************************************************************************************************/
void ReplaceLineEndBySpace(char *str)
{
    char c = 0;
    if (str == NULL)
    {
        return;
    }
    while((c = *str) != 0)
    {
        if (c =='\n' || c =='\r')
        {
            *str = ' ';
        }
        str++;
    }
}

/**************************************************************************************************************/
/* remap fields from input CSV order to expected order and store result in char **array                       */
/**************************************************************************************************************/
char **RemapInCSVToImportOrder(CsvRow *inRow, int rowID)
{
    char **resRow = NULL;
    int* map_csvToOCPin = NULL;
    int sizeMap_csvToOCPin = 0;
    char *fun = "RemapInCSVToImportOrder";

    switch (rowID)
    {
    case ROWID_ARTICLE_CODES: // articleCodes
        map_csvToOCPin = article_code_incsv_map;
        sizeMap_csvToOCPin = ARTICLE_CODES_FIELDS_COUNT;
        break;
    case ROWID_ARTICLE: // article
        map_csvToOCPin = article_incsv_map;
        sizeMap_csvToOCPin = ARTICLE_FIELDS_COUNT;
        break;
    case ROWID_ARTICLE_PRICE: // articlePrice
        map_csvToOCPin = article_price_incsv_map;
        sizeMap_csvToOCPin = ARTICLE_PRICE_FIELDS_COUNT;
        break;
    case ROWID_ARTICLE_FRANCE: // articleFrance
        map_csvToOCPin = article_france_incsv_map;
        sizeMap_csvToOCPin = ARTICLE_FRANCE_FIELDS_COUNT;
        break;
    default: // unknown !
        PrintMsg(fun, FEHLER, "Uknown row ID");
        return NULL;
    }

    if (map_csvToOCPin != NULL && sizeMap_csvToOCPin > 0) {
        resRow = (char**)malloc(sizeof(char*) * sizeMap_csvToOCPin);
        for (int f =0; f < sizeMap_csvToOCPin; f++)
        {
          resRow[f] = (char*)malloc(CSVFORMAT_MAX_COLUMN_SIZE*sizeof(char));
        }

        if (resRow != NULL)
        {
            for (int mi = 0; mi < sizeMap_csvToOCPin; mi++) {
                strcpy(resRow[map_csvToOCPin[mi]], inRow->fields[mi]);
            }
        }
        else
        {
            PrintMsg(fun, FEHLER, "Out of memory!");
        }
    }
    return resRow;
}

/**************************************************************************************************************/
/* free memory allocated by a remapped row                                                                    */
/**************************************************************************************************************/
void FreeRemappedRow(char **remapRow, int rowID)
{
    int sizeMap_csvToOCPin = 0;

    if (remapRow == NULL)
    {
        return;
    }

    switch (rowID)
    {
    case ROWID_ARTICLE_CODES: // articleCodes
        sizeMap_csvToOCPin = ARTICLE_CODES_FIELDS_COUNT;
        break;
    case ROWID_ARTICLE: // article
        sizeMap_csvToOCPin = ARTICLE_FIELDS_COUNT;
        break;
    case ROWID_ARTICLE_PRICE: // articlePrice
        sizeMap_csvToOCPin = ARTICLE_PRICE_FIELDS_COUNT;
        break;
    case ROWID_ARTICLE_FRANCE: // articleFrance
        sizeMap_csvToOCPin = ARTICLE_FRANCE_FIELDS_COUNT;
        break;
    default:
        return;
    }

    for (int f =0; f < sizeMap_csvToOCPin; f++)
    {
      free(remapRow[f]);
      remapRow[f] = NULL;
    }
    free(remapRow);
}

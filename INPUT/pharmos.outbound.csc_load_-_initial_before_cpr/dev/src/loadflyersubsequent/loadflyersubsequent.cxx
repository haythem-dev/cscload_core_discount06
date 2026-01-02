/************************************************************************************************/
/*    main module: loadflyersubsequent.ecc                                                      */
/*         Source: loadflyersubsequent.cxx                                                      */
/*          Autor: Ronald Imschweiler / Fakhri Feki                                             */
/*        Created: 18.08.2021                                                                   */
/*  Last Modified: 24.11.2022                                                                   */
/*       language: C                                                                            */
/*        Erzeugt: manual                                                                       */
/*           Task: validate and import csv file into nachlieferpos database Table               */
/*          Usage: loadflyersubsequent.sh [-inputcsv csvfilename][-db dbname][-version]         */
/*                                                                                              */
/************************************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/
#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME  "loadflyersubsequent"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/********************************************************************************/
/* INCLUDE */
/********************************************************************************/
#include "libtpld/define.h"
#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <stdarg.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include "pplib/allg.h"
#include "csvparser.h"

/********************************************************************************/
/* STRUCTS */
/********************************************************************************/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

typedef struct N_FLYER {
    short BRANCHNO;
    long CUSTOMERNO;
    char ARTICLE_CODE[26];
    long MENGE;
} flyerS;

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/********************************************************************************/
/* DEFINE */
/********************************************************************************/
typedef struct timeval timeval_t;

#define CSV_COLUMNS_COUNT 5
CSvFieldFormat *csvStruct[CSV_COLUMNS_COUNT] = { &CSvFormat_NumericString, &CSvFormat_NumericString, &CSvFormat_NumericString, &CSvFormat_int32, &CSvFormat_any };
char *columnsNames[CSV_COLUMNS_COUNT] = { "Filiale", "Kundennummer", "Artikelcode", "Bestellmenge", "Bemerkungen" };

// columns Index
#define IDX_FILIALE             0
#define IDX_KUNDEN_NUMMER       1
#define IDX_ARTIKLE_CODE        2
#define IDX_BESTELL_MENGE       3
#define IDX_BEMERKUNGEN         4

// key definition ** "Filiale", "Kundennummer", "Artikle code" **
int keysCount = 3;
int keys[] = { IDX_FILIALE, IDX_KUNDEN_NUMMER, IDX_ARTIKLE_CODE };

// internal module errors ID
#define CSVERR_BRANCH_NOT_FOUND                         CSVERR_MAX_ID+1
#define CSVERR_CUSTOMER_NOT_FOUND                       CSVERR_MAX_ID+2
#define CSVERR_ARTICLE_NOT_FOUND                        CSVERR_MAX_ID+3
#define CSVERR_CUSTOMER_BRANCH_COMBINATION_INVALID      CSVERR_MAX_ID+4
#define CSVERR_BESTELL_MENGE_OUT_OF_RANGE               CSVERR_MAX_ID+5
#define CSVERR_FAILED_CREATE_REPORT_CSV_FILE            CSVERR_MAX_ID+6
#define CSVERR_FAILED_INSERT_NACHLIFERPOS               CSVERR_MAX_ID+7

// module return ERRORS CODE
#define CSVERR_RET_OK                                   0
#define CSVERR_MISSING_OR_WRONG_PARAMETERS              1
#define CSVERR_ERROR_OPENING_DATA_BASE                  2
#define CSVERR_ERROR_CLOSING_DATA_BASE                  3
#define CSVERR_IO_ERROR                                 4
#define CSVERR_INVALID_INPUT_DATA                       5
#define CSVERR_DATABASE_FAILED_INSERT                   6
#define CSVERR_DATABASE_SQL_ERROR                       7

/********************************************************************************/
/* GLOBAL VARIABLES */
/********************************************************************************/
static  char*   spDatabase          = NULL;
static  char*   csvFileName         = NULL;
static  long    failedInsertItems   = 0;
static  long    notloadItems        = 0;
static  long    CountNumbers        = 0;
static  bool    bVersion            = false;
static  char    nameReportCSVFile[2048] = "";
static  char    csvBaseFileName[2048] = "";
static  int     rargc               = 0;
static  char**   rargv              = NULL;


exec sql begin declare section;
    struct N_FLYER     flyer;
    long               lArtikel_nr;
    char               str[2048];
    long               curDate;
    short              codetype = 0;
    short              sPosnr = 0;
    char               *strSql = NULL;
    char               *str2Sql = NULL;
exec sql end declare section;

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
static int  LoadNachlieferpos(char *error_msg);
static void PrintMsg(char *fun, char mld , char *error_msg, ...);
static void GetReportCSVName(char *reportCSVName);
static void RenameOrGenErrorReportCSVFile(int errorCode);

/********************************************************************************/
/* int main( int argc, char **argv ) */
/********************************************************************************/
int main(int argc, char* argv[])
{
    char error_msg[512] = "";
    char *fun = "main()";
    int retLoadNachlieferpos = CSVERR_RET_OK;
    rargc = argc;
    rargv = (char**)argv;
    /*****************************************************/
    /* initialization*/
    /*****************************************************/
    GetReportCSVName(nameReportCSVFile);
    setbuf(stdout, 0);

    /*****************************************************/
    /* handle parameters*/
    /*****************************************************/
    if (CommandLineImport( argc, argv ) != OK)
    {
        printf( "Usage: loadflyersubsequent.sh [-inputcsv csvfilename] [-db dbname] [-version]\n"
                "Example:  %s -inputcsv flyer21.csv -db ode21 \n", argv[0] );
        RenameOrGenErrorReportCSVFile(CSVERR_MISSING_OR_WRONG_PARAMETERS);
        PrintMsg(fun, HINWEIS, "finished" );
        return CSVERR_MISSING_OR_WRONG_PARAMETERS;
    }
    if (bVersion)
    {
        return CSVERR_RET_OK;
    }

    PrintMsg(fun, HINWEIS, "Started importing '%s' into nachlieferpos", csvFileName);

    /*****************************************************/
    /* Open database */
    /*****************************************************/
    if (openDB() != OK)
    {
        PrintMsg(fun, FEHLER, "Error opening database! error code <%i>",  CSVERR_ERROR_OPENING_DATA_BASE);
        RenameOrGenErrorReportCSVFile(CSVERR_ERROR_OPENING_DATA_BASE);
        PrintMsg(fun, HINWEIS, "finished" );
        return CSVERR_ERROR_OPENING_DATA_BASE;
    }

    /*****************************************************/
    /* Load of data */
    /*****************************************************/
    if ((retLoadNachlieferpos = LoadNachlieferpos(error_msg)) != CSVERR_RET_OK)
    {
        PrintMsg(fun, FEHLER, "Insertion of subsequent flyers items failed! error code <%i>",  retLoadNachlieferpos);
        closeDB();
        RenameOrGenErrorReportCSVFile(retLoadNachlieferpos);
        PrintMsg(fun, HINWEIS, "finished" );
        return retLoadNachlieferpos;
    }

    /*****************************************************/
    /* Close database */
    /*****************************************************/
    if (closeDB() != OK)
    {
        PrintMsg(fun, FEHLER, "Error closing database! error code <%i>",  CSVERR_ERROR_CLOSING_DATA_BASE);
        RenameOrGenErrorReportCSVFile(CSVERR_ERROR_CLOSING_DATA_BASE);
        PrintMsg(fun, HINWEIS, "finished" );
        return CSVERR_ERROR_CLOSING_DATA_BASE;
    }

    PrintMsg(fun, HINWEIS, "finished" );
    RenameOrGenErrorReportCSVFile(0);

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

        if(!strcmp(curParam, "-inputcsv"))
        {
            i++;
            csvFileName = argv[i];
            strcpy(tmpFileName, basename(csvFileName)); // take basefile name with extension
            // remove extension is found
            if ((tmpBaseFileName = strtok(tmpFileName, pointStr)) != NULL)
            {
                strcpy(csvBaseFileName, tmpBaseFileName);
            }
            else
            {
                strcpy(csvBaseFileName, tmpFileName);
            }
        }
        else if (!strcmp( curParam, "-db" ))
        {
            i++;
            spDatabase = argv[i];
        }
        else if (!strcmp( curParam, "-version" ))
        {
            printVersion(versioninfo);
            bVersion = true;
        }
        else
        {
            skip = ERROR;
            break;
        }
    } /* ENDR FOR */

    if( argc == 1 || skip == ERROR || csvFileName == NULL || spDatabase == NULL)
    {
        PrintMsg( fun, HINWEIS, "Incorrect program parameters" );
        return ERROR; /* Incorrect program parameters */
    }

    curDate = AllgGetDate();

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
/* static int LoadNachlieferpos()                                           */
/****************************************************************************/
static int LoadNachlieferpos(char *error_msg)
{
    /*************************/
    /* Variables-Declaration */
    /*************************/
    char    *fun = "LoadNachlieferpos()";
    unsigned int uiTransactions = 0;
    bool bDbSqlError = false;
    bool bDbTransact = false;

    exec sql begin declare section;
    struct  N_FLYER *pflyer;
    CsvRow *curRow;
    exec sql end declare section;

    pflyer = &flyer;
    curRow = NULL;

    /****************************************************************************************************/
    /* SQL statements to search for existing customer/article/branch and insert into nachlieferpos table*/
    /****************************************************************************************************/

    /* Prepare SELECT-Cursor articlecodes */
    strcpy(str, "SELECT articleno,code_type FROM articlecodes ");
    strcat(str, "where article_code = ? ");
    EXEC SQL PREPARE preSelArticle from :str;
    EXEC SQL DECLARE curSelArticle cursor with hold for preSelArticle;
    ERROR_MSG("DECLARE curSelArticle", bDbSqlError);
    exec sql free preSelArticle;

    /* Prepare SELECT-Cursor customer number */
    strcpy(str, "SELECT * FROM kunde ");
    strcat(str, "where kundennr = ? ");
    EXEC SQL PREPARE preSelCustomer from :str;
    EXEC SQL DECLARE curSelCustomer cursor with hold for preSelCustomer;
    ERROR_MSG("DECLARE curSelCustomer", bDbSqlError);
    exec sql free preSelCustomer;

    /* Prepare SELECT-Cursor branch/filiale number */
    strcpy(str, "SELECT * FROM filiale ");
    strcat(str, "where filialnr = ? ");
    EXEC SQL PREPARE preSelBranch from :str;
    EXEC SQL DECLARE curSelBranch cursor with hold for preSelBranch;
    ERROR_MSG("DECLARE curSelBranch", bDbSqlError);
    exec sql free preSelBranch;

    /* Prepare SELECT-Cursor customer/filiale numbers */
    strcpy(str, "SELECT * FROM kunde ");
    strcat(str, "where kundennr = ? and filialnr = ?");
    EXEC SQL PREPARE preSelCustomerFilial from :str;
    EXEC SQL DECLARE curSelCustomerFilial cursor with hold for preSelCustomerFilial;
    ERROR_MSG("DECLARE curSelCustomerFilial", bDbSqlError);
    exec sql free preSelCustomerFilial;

    /* Prepare SELECT-Cursor nachlieferpos.POSNR */
    strcpy(str, "SELECT NVL(max(posnr),0) from nachlieferpos ");
    strcat(str, "where kdauftragnr=0 and postyp=3 and datum=?");
    EXEC SQL PREPARE preSelPosnr from :str;
    EXEC SQL DECLARE curSelPosnr cursor with hold for preSelPosnr;
    ERROR_MSG("DECLARE curSelPosnr", bDbSqlError);
    exec sql free preSelPosnr;

    /* Prepare Insert in Nachlieferpos */
    strcpy(str, "INSERT into nachlieferpos (");
    strcat(str, " KDAUFTRAGNR");
    strcat(str, ",POSNR");
    strcat(str, ",DATUM");
    strcat(str, ",POSTYP");
    strcat(str, ",IDFNR");
    strcat(str, ",ARTIKEL_NR");
    strcat(str, ",MENGE");
    strcat(str, ",KUNDENNR");
    strcat(str, ",VERTRIEBSZENTRUMNR");
    strcat(str, ",KDAUFTRAGART");
    strcat(str, ",POSART");
    strcat(str, ",BEMERKUNGEN");
    strcat(str, ",CODE_TYPE");
    strcat(str, ",ARTICLE_CODE");
    strcat(str, ",MENGEBESTELLT");
    strcat(str, ") values ");
    strcat(str, "( '0', ?, ?, '3', ?, ?, ?, ?, ?, 'NO', 'D', 'FLYER', ?, ?, ? )");
    EXEC SQL PREPARE insNachlieferpos from :str;
    ERROR_MSG("prepare insNachlieferpos", bDbSqlError);

    /* Start SQL transaction of inserts in nachlieferpos */
    EXEC SQL BEGIN WORK;
    ERROR_MSG("BEGIN WORK", bDbTransact);

    if(bDbSqlError || bDbTransact)
    {
        PrintMsg(fun, FEHLER, "Fatal Database Sql error");
        if (!bDbTransact)
        {
            EXEC SQL ROLLBACK WORK;
        }
        return CSVERR_DATABASE_SQL_ERROR;
    }

    /**********************************************************************************/
    /* gets the starting nachlieferpos.POSNR value to avoid conflict when inserting   */
    /**********************************************************************************/
    EXEC SQL OPEN curSelPosnr using :curDate;
    EXEC SQL FETCH curSelPosnr into :sPosnr;
    if (NOT_FOUND)
    {
        PrintMsg(fun, FEHLER, "Database SQL Error: Failed to initialize Posnr");
        EXEC SQL ROLLBACK WORK;
        return CSVERR_DATABASE_SQL_ERROR;
    }

    /********************************************************************/
    /* Parse input CSV & Insert validated DATA into nachlieferpos table */
    /********************************************************************/

    CsvParser *csvParser = CsvParser_Create(csvFileName, ';', csvStruct, columnsNames, CSV_COLUMNS_COUNT);
    int i = 0;
    char *errMsg = NULL;
    int lineErr = 0;
    int errID = 0;
    int fatalExit = 0;
    int countRows = 0;
    int countValidRows = 0;
    int countInvalidRows = 0;
    int countErrors = 0;
    int curRowCountErrors = 0;
    int retRes = CSVERR_RET_OK;
    FILE *outCSV = NULL;

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
                // in header case we could have several errors, so we need a loop to get all parsed errors
                case CSVERR_HEADER_WRONG_COLUMNS_COUNT:
                case CSVERR_HEADER_WRONG_COLUMN_NAME:
                case CSVERR_HEADER_CROSSED_MAX_COLUMNS_COUNT:
                    // generate error report CSV
                    outCSV = fopen(nameReportCSVFile, "wt");
                    retRes = CSVERR_INVALID_INPUT_DATA;
                    // error report csv header and first error
                    if (outCSV != NULL)
                    {
                        fprintf(outCSV, "Error;Description\n");
                    }
                    while((errMsg = CsvParser_getErrorMessage(csvParser, &errID, &lineErr)) != NULL)
                    {
                        PrintMsg(fun, FEHLER, "Fatal error wrong Header: '%s'", errMsg);
                        if (outCSV != NULL)
                        {
                            fprintf(outCSV, "wrong Header;%s(%i)\n", errMsg,errID);
                        }
                        CSV_SAFE_FREE(errMsg);
                    }
                    if (outCSV != NULL)
                    {
                        fclose(outCSV);
                        outCSV = NULL;
                    }
                    break;
            };
        }
        if (retRes != CSVERR_RET_OK)
        {
            CsvParser_Destroy(csvParser);
            EXEC SQL ROLLBACK WORK;
            return retRes;
        }

        // create report CSV file
        outCSV = fopen(nameReportCSVFile, "wt");

        if(outCSV == NULL)
        {
            CsvParser_Destroy(csvParser);
            PrintMsg(fun, FEHLER, "Fatal i/o error: 'Failed to create/open '%s' report CSV file'", nameReportCSVFile);
            fclose(outCSV);
            EXEC SQL ROLLBACK WORK;
            return CSVERR_IO_ERROR;
        }

        // write header of the report CSV
        CsvParser_fwriteHeaderWithErrorsColumns(csvParser, outCSV);

        if (CsvParser_isFinished(csvParser) == 0)
        {
            // enable key duplicates checking
            CsvParser_EnableKey(csvParser, keys, keysCount);
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

        // Checking of all rows on the csv file
        while (CsvParser_isFinished(csvParser) == 0)
        {
            // getting next row
            curRow = CsvParser_getNextRow(csvParser, 0);
            if (curRow != NULL)
            {
                curRowCountErrors = 0;
                countRows ++;
                /***** database checking *******/

                // flyer article exist ?
                if (curRow->numOfFields > IDX_ARTIKLE_CODE)
                {
                    strSql = curRow->fields[IDX_ARTIKLE_CODE];
                    EXEC SQL OPEN curSelArticle using :strSql;
                    EXEC SQL FETCH curSelArticle;

                    if (NOT_FOUND)
                    {
                        PrintMsg(fun, FEHLER, "Article '%s' not found", curRow->fields[IDX_ARTIKLE_CODE]);
                        CsvParser_setErrorMessage(csvParser, -1, CSVERR_ARTICLE_NOT_FOUND, "Article '%s' not found", curRow->fields[IDX_ARTIKLE_CODE]);
                    }
                }

                // customer id exist ?
                if (curRow->numOfFields > IDX_KUNDEN_NUMMER)
                {
                    strSql = curRow->fields[IDX_KUNDEN_NUMMER];
                    EXEC SQL OPEN curSelCustomer using :strSql;
                    EXEC SQL FETCH curSelCustomer;

                    if (NOT_FOUND)
                    {
                        PrintMsg(fun, FEHLER, "Customer '%s' not found", curRow->fields[IDX_KUNDEN_NUMMER]);
                        CsvParser_setErrorMessage(csvParser, -1, CSVERR_CUSTOMER_NOT_FOUND, "Customer '%s' not found", curRow->fields[IDX_KUNDEN_NUMMER]);
                    }
                }

                // branch/filiale id exist ?
                if (curRow->numOfFields > IDX_FILIALE)
                {
                    strSql = curRow->fields[IDX_FILIALE];
                    EXEC SQL OPEN curSelBranch using :strSql;
                    EXEC SQL FETCH curSelBranch;
                    if (NOT_FOUND)
                    {
                        PrintMsg(fun, FEHLER, "Branch/Filiale '%s' not found", curRow->fields[IDX_FILIALE]);
                        CsvParser_setErrorMessage(csvParser, -1, CSVERR_BRANCH_NOT_FOUND, "Branch/Filiale '%s' not found", curRow->fields[IDX_FILIALE]);
                    }
                }

                // valid combination of customer and branch/filiale ?
                if (curRow->numOfFields > IDX_KUNDEN_NUMMER && curRow->numOfFields > IDX_FILIALE)
                {
                    strSql = curRow->fields[IDX_KUNDEN_NUMMER];
                    str2Sql = curRow->fields[IDX_FILIALE];
                    EXEC SQL OPEN curSelCustomerFilial using :strSql, :str2Sql;
                    EXEC SQL FETCH curSelCustomerFilial;
                    if (NOT_FOUND)
                    {
                        PrintMsg(fun, FEHLER, "Customer and Branch/Filiale combination not valid, ['%s', '%s']", curRow->fields[IDX_KUNDEN_NUMMER], curRow->fields[IDX_FILIALE]);
                        CsvParser_setErrorMessage(csvParser, -1, CSVERR_CUSTOMER_BRANCH_COMBINATION_INVALID, "Customer and Branch/Filiale combination invalid, ['%s', '%s']", curRow->fields[IDX_KUNDEN_NUMMER], curRow->fields[IDX_FILIALE]);
                    }
                }

                /***** data integrity checking *******/
                // Check "Bestellmenge" should be on the range [1, 999]
                if (curRow->numOfFields > IDX_BESTELL_MENGE)
                {
                    int vBestellmenge = atoi(curRow->fields[IDX_BESTELL_MENGE]);
                    if (vBestellmenge < 1 || vBestellmenge > 999)
                    {
                        PrintMsg(fun, FEHLER, "Bestellmenge out of range, should be between [1, 999], current value '%i'", vBestellmenge);
                        CsvParser_setErrorMessage(csvParser, -1, CSVERR_BESTELL_MENGE_OUT_OF_RANGE, "Bestellmenge out of range, should be between [1, 999], current value '%i'", vBestellmenge);
                    }
                }

                /***** in case we have some validations errors no insert in database occur */
                if (CsvParser_getCurRowErrorsCount(csvParser) > 0)
                {
                    /***** Write row to report csv file ***/
                    CsvParser_fwriteCurRowWithErrors(csvParser, outCSV);

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
                                curRowCountErrors++;
                                break;
                            // module errors
                            case CSVERR_ARTICLE_NOT_FOUND:
                            case CSVERR_CUSTOMER_NOT_FOUND:
                            case CSVERR_BRANCH_NOT_FOUND:
                            case CSVERR_CUSTOMER_BRANCH_COMBINATION_INVALID:
                            case CSVERR_BESTELL_MENGE_OUT_OF_RANGE:
                                curRowCountErrors++;
                                break;
                        }
                        CSV_SAFE_FREE(errMsg);
                    }
                }
                /** no validation errors - insert into nachlieferpos datatable */
                else
                {
                    // Get Article_nr and codeType of the flyer
                    strSql = curRow->fields[IDX_ARTIKLE_CODE];
                    EXEC SQL OPEN curSelArticle using :strSql;
                    EXEC SQL FETCH curSelArticle into :lArtikel_nr, :codetype;

                    // fill flyer struct with current row data
                    flyer.CUSTOMERNO = (long)atoi(curRow->fields[IDX_KUNDEN_NUMMER]);
                    flyer.BRANCHNO = (long)atoi(curRow->fields[IDX_FILIALE]);
                    flyer.MENGE = (long)atoi(curRow->fields[IDX_BESTELL_MENGE]);
                    strcpy(flyer.ARTICLE_CODE, curRow->fields[IDX_ARTIKLE_CODE]);

                    // update position
                    sPosnr++;
                    // insert row data into database table 'nachlieferpos'
                    exec sql execute insNachlieferpos using
                        :sPosnr,
                        :curDate,
                        :flyer.CUSTOMERNO,
                        :lArtikel_nr,
                        :flyer.MENGE,
                        :flyer.CUSTOMERNO,
                        :flyer.BRANCHNO,
                        :codetype,
                        :flyer.ARTICLE_CODE,
                        :flyer.MENGE;

                    // Failed to insert ?
                    if(SQLCODE < 0)
                    {
                        CsvParser_setErrorMessage(csvParser, -1, CSVERR_FAILED_INSERT_NACHLIFERPOS, "Database failed to insert values [branch, customer, article] ['%s', '%s', '%s']",
                            curRow->fields[IDX_FILIALE], curRow->fields[IDX_KUNDEN_NUMMER], curRow->fields[IDX_ARTIKLE_CODE]);
                        PrintMsg(fun, FEHLER, "Database failed to insert values [branch, customer, article] ['%s', '%s', '%s']",
                            curRow->fields[IDX_FILIALE], curRow->fields[IDX_KUNDEN_NUMMER], curRow->fields[IDX_ARTIKLE_CODE]);
                        failedInsertItems++;
                    }
                    /***** Write row to report csv file ***/
                    CsvParser_fwriteCurRowWithErrors(csvParser, outCSV);

                    /***** handle encountred errors *******/
                    while((errMsg = CsvParser_getErrorMessage(csvParser, &errID, &lineErr)) != NULL)
                    {
                        switch(errID)
                        {
                            case CSVERR_FAILED_INSERT_NACHLIFERPOS:
                                curRowCountErrors++;
                                break;
                        }
                        CSV_SAFE_FREE(errMsg);
                    }
                }

                /** count total errors */
                if (curRowCountErrors > 0)
                {
                    countErrors += curRowCountErrors;
                    countInvalidRows ++;
                }
                else
                {
                    countValidRows ++;
                }
                CsvRow_destroy(curRow);
            }
        }
        fclose(outCSV);
        CsvParser_Destroy(csvParser);
        csvParser = NULL;
    }

    /**** handle errors count **********/
    if (countErrors > 0)
    {
        PrintMsg(fun, FEHLER, "Fatal: %i error(s) detected", countErrors);
        if (failedInsertItems > 0)
        {
            PrintMsg(fun, FEHLER, "Fatal: failed to insert %i row(s)", failedInsertItems);
        }
        PrintMsg(fun, FEHLER, "%i total row(s): %i invalid, %i valid", countRows, countInvalidRows, countValidRows);
        PrintMsg(fun, FEHLER, "Import to Nachlieferpos canceled");
        // if all errors are failed insert to nachliferpos return [CSVERR_DATABASE_FAILED_INSERT] else return [CSVERR_INVALID_INPUT_DATA]
        if (countErrors == failedInsertItems)
        {
            return CSVERR_DATABASE_FAILED_INSERT;
        }
        else
        {
            return CSVERR_INVALID_INPUT_DATA;
        }
    }
    PrintMsg( fun, HINWEIS, "%i row(s) inserted successfully", countRows);
    EXEC SQL COMMIT WORK;
    ERROR_MSG("COMMIT WORK", bDbSqlError);

    return CSVERR_RET_OK;
}

/************************************************************************************************************/
/* static void PrintMsg(char *fun, char mld, char *error_msgFormat, ... )                                   */
/************************************************************************************************************/
static void PrintMsg( char *fun, char mld, char *error_msgFormat, ... )
{
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
    sprintf(logFile, "%s/wws.log", env);

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
        "loadflyersubsequent",
        fun);

    va_start(arg_ptr, error_msgFormat);
    vfprintf(fp, error_msgFormat, arg_ptr);
    va_end(arg_ptr);

    fprintf(fp, "->%d/%d\n", SQLCODE, SQLISAM );
    fclose(fp);
}

/****************************************************************************/
/* generate report CSV filename                                             */
/****************************************************************************/
void GetReportCSVName(char *reportCSVName)
{
    char *env;
    struct tm *curTime;
    long curHour;

    curHour = time(&curHour);
    curTime  = localtime(&curHour);

    env = getenv( "DATA_PATH" );
    if (env == NULL)
    {
        env = ".";
    }

    if(curTime->tm_year > 99)
    {
        curTime->tm_year -= 100;
    }
    sprintf(reportCSVName, "%s/flyer/report/%02d-%02d-%02d-%02d-%02d-%02d.csv", env,
            curTime->tm_year, curTime->tm_mon + 1, curTime->tm_mday,
            curTime->tm_hour, curTime->tm_min, curTime->tm_sec);
    sprintf(csvBaseFileName, "%02d-%02d-%02d-%02d-%02d-%02d",
            curTime->tm_year, curTime->tm_mon + 1, curTime->tm_mday,
            curTime->tm_hour, curTime->tm_min, curTime->tm_sec);
}

/****************************************************************************/
/* rename or create report CSV file according to errorCode                  */
/****************************************************************************/
static void RenameOrGenErrorReportCSVFile(int errorCode) {
    char newName[2048];
    char *fun = "RenameOrGenErrorReportCSVFile()";
    char *env;
    FILE *fReportCSV = NULL;
    int i = 0;

    env = getenv( "DATA_PATH" );
    if (env == NULL)
    {
        env = ".";
    }
    switch(errorCode) {
        case CSVERR_RET_OK: // no error
            sprintf(newName, "%s/flyer/report/%s_SUCCESS_report.csv", env, csvBaseFileName);
            rename(nameReportCSVFile, newName);
            break;
        case CSVERR_MISSING_OR_WRONG_PARAMETERS:
            sprintf(newName, "%s/flyer/report/%s_ERROR_report.csv", env, csvBaseFileName);
            if ((fReportCSV = fopen(newName, "wt")) != NULL)
            {
                fprintf(fReportCSV, "Error;Description\n");
                fprintf(fReportCSV, "Missing or wrong parameters;received (%i) parameter(s): ", rargc);
                for (i = 0; i < rargc; i++)
                {
                    fprintf(fReportCSV, "parameters(%i) = '%s'", i, rargv[i]);
                    if (i < rargc - 1)
                    {
                        fprintf(fReportCSV, ", ");
                    }
                }
                fclose(fReportCSV);
            }
            // put received parameters on log file
            PrintMsg(fun, HINWEIS, "received (%i) parameter(s): ", rargc);
            for (i = 0; i < rargc; i++)
            {
                PrintMsg(fun, HINWEIS, "    parameters(%i) = '%s'", i, rargv[i]);
            }
            break;
        case CSVERR_IO_ERROR:
            sprintf(newName, "%s/flyer/report/%s_ERROR_report.csv", env, csvBaseFileName);
            if ((fReportCSV = fopen(newName, "wt")) != NULL)
            {
                fprintf(fReportCSV, "Error;Description\n");
                if (csvFileName != NULL)
                {
                    fprintf(fReportCSV, "i/o error;Failed to open input csv file for reading or not existing file '%s'", csvFileName);
                }
                else
                {
                    fprintf(fReportCSV, "i/o error;Failed to open input csv file for reading or not existing file");
                }
                fclose(fReportCSV);
            }
            break;
        case CSVERR_ERROR_OPENING_DATA_BASE:
            sprintf(newName, "%s/flyer/report/%s_ERROR_report.csv", env, csvBaseFileName);
            if ((fReportCSV = fopen(newName, "wt")) != NULL)
            {
                fprintf(fReportCSV, "Error;Description\n");
                if (spDatabase != NULL)
                {
                    fprintf(fReportCSV, "Failed to open database;Failed to open database '%s'", spDatabase);
                }
                else
                {
                    fprintf(fReportCSV, "Failed to open database;Failed to open database");
                }
                fclose(fReportCSV);
            }
            break;
        case CSVERR_DATABASE_SQL_ERROR:
            sprintf(newName, "%s/flyer/report/%s_ERROR_report.csv", env, csvBaseFileName);
            if ((fReportCSV = fopen(newName, "wt")) != NULL)
            {
                fprintf(fReportCSV, "Error;Description\n");
                fprintf(fReportCSV, "Database SQL Error;Failed to initialize instructions to validate and insert data, check database tables/structure");
                fclose(fReportCSV);
            }
            break;
        case CSVERR_INVALID_INPUT_DATA:
            sprintf(newName, "%s/flyer/report/%s_ERROR_report.csv", env, csvBaseFileName);
            rename(nameReportCSVFile, newName);
            break;
        case CSVERR_DATABASE_FAILED_INSERT:
            sprintf(newName, "%s/flyer/report/%s_ERROR_report.csv", env, csvBaseFileName);
            rename(nameReportCSVFile, newName);
            break;
        case CSVERR_ERROR_CLOSING_DATA_BASE:
            sprintf(newName, "%s/flyer/report/%s_ERROR_report.csv", env, csvBaseFileName);
            rename(nameReportCSVFile, newName);
            break;
    }
}

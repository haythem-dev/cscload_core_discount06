/************************************************************************************************/
/*         module: loadnewquota.ecc                                                             */
/*         Source: loadnewquota.cxx                                                             */
/*          Autor: Karsten Obst / Juri Skuratovski / Wajdi Feki                                 */
/*        Created: 16.04.2024                                                                   */
/*  Last Modified: 05.12.2024                                                                   */
/************************************************************************************************/

// module return ERRORS CODE
#define CSVERR_RET_OK                                   0
#define CSVERR_MISSING_OR_WRONG_PARAMETERS              1
#define CSVERR_ERROR_OPENING_DATA_BASE                  2
#define CSVERR_ERROR_CLOSING_DATA_BASE                  3
#define CSVERR_IO_ERROR                                 4
#define CSVERR_INVALID_INPUT_DATA                       5
#define CSVERR_DATABASE_FAILED_INSERT                   6
#define CSVERR_DATABASE_FAILED_UPDATE                   7
#define CSVERR_DATABASE_FAILED_DELETE                   8
#define CSVERR_DATABASE_SQL_ERROR                       9
#define CSVERR_ARTICLECODETOARTICLENUMBERMAP_SQL_ERROR  10
#define CSVERR_INI_FILE_MISSING_OR_WRONG_PARAMETERS     11
#define CSVERR_PHARMACYGROUPTOCUSTOMERNOMAP_SQL_ERROR   12
#define CSVERR_ERROR_FILENAME_PATTERN                   13
#define CSVERR_ARTICLE_NOT_FOUND			            14

/********************************************************************************/
/* VERSION                                                                      */
/********************************************************************************/
#include "csc_load_version.h"
#define PROJECTNAME  "loadnewquota"
static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/********************************************************************************/
/* INCLUDE */
/********************************************************************************/
#include <cstdlib> 
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <stdarg.h>
#include <signal.h>
#include <time.h>
#include <algorithm> 
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>

#ifndef _WIN32
#include <sys/time.h>
#include <libgen.h>
#include <unistd.h>
#endif

#include "define.h"
#include "utils.h"
#include "inputdata.h"

/********************************************************************************/
/* STRUCTS */
/********************************************************************************/
#define L_ARTICLE_CODE 25

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif
typedef struct
{
    long BRANCHNO;
    long CUSTOMERNO;
    char ARTICLE_CODE[L_ARTICLE_CODE + 1];
    long QUOTA;
    char VALIDITY;
    long DATEFROM;
    long DATETO;
    long PHARMACYGROUPID;
} QuotaS;

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

void ConvertQuotaStructs(QuotaS& quotaS, QUOTA_INTERN quota_Intern)
{
    quotaS.BRANCHNO = quota_Intern.BRANCHNO;
    quotaS.CUSTOMERNO = quota_Intern.CUSTOMERNO;
    quotaS.QUOTA = quota_Intern.QUOTA;
    std::strcpy(quotaS.ARTICLE_CODE, quota_Intern.ARTICLE_CODE.c_str());
    quotaS.VALIDITY = quota_Intern.VALIDITY;
    quotaS.DATEFROM = quota_Intern.DATEFROM;
    quotaS.DATETO = quota_Intern.DATETO;
    quotaS.PHARMACYGROUPID = quota_Intern.PHARMACYGROUPID;
}

typedef struct CounterS
{
    long countUpdateOk;
    long countUpdateBad;
    long countInsertOk;
    long countInsertBad;
    long countDeletedOk;
    long countDeletedBad;
    long countSkipped;
    long counterForCommit;

    CounterS()
        : countUpdateOk(0), countUpdateBad(0), countInsertOk(0),
          countInsertBad(0), countDeletedOk(0), countDeletedBad(0),
          countSkipped(0), counterForCommit(0) {}
} CounterS;

/********************************************************************************/
/* GLOBAL VARIABLES                                                             */
/********************************************************************************/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif
QuotaS          g_CurrentQuota;
long            g_lArticleNo;
long            g_lCustomerNo;
long            g_lPharmacyGroup;
short           g_branchNo;
char            g_selectStmt[2048];
long            g_lCurrentDate;
char            g_articleCode[25 + 1];
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

std::string g_strDatabase = "";
long        g_lCommitAfter = 1;
long        g_lCommitPause = 0; 
char        g_cDelimiter = ';';
std::string g_strCSVFile = "";
std::string g_strIniFile = "";
bool        g_blnVersion = false;
bool        g_bNoDelete = false;
long        g_lGroupCustomerCount = 0;
bool        g_bDeleteNegativeQuotas = false;
std::string g_strArticleNumberFilter = "";
std::string g_strCSVFilePatternPrefix = "quota_";
std::string g_strCSVFilePatternDelta = "delta_";
std::string g_strCSVFilePatternBranch = "_branchno_";

std::map<std::string, long>        g_articleCodeToArticleNumberMap;
std::map<long, std::vector<long>*> g_pharmacyGroupToCustomerNumbersMap;

/********************************************************************************/
/* FUNCTIONS-DECLARATION */
/********************************************************************************/
static int openDB();
static int closeDB();
int FillArticleCodeToArticleNumberMap();
int FillPharmacyGroupToCustomerNumbersMap();
int CleanupMaps();
std::vector<long>* GetCustomersFromPharmacyGroupID(long pharmacyGroup);
int UpdateOrInsertInDBQuotas(const InputData& quotasFromCSV);
int DeleteOLDDBQuotas();

void ShowUsage(std::string prog)
{
    printf("Usage: %s -inputcsv filename -db database [-nodelete] [-version]\n", prog.c_str());
}

/*********************************************************************************/
/* static int openDB()                                                           */
/*********************************************************************************/
static int openDB()
{
    bool bDbSqlError = false;
#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif
    const char* spDB = g_strDatabase.c_str();

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


    PrintMsg(__func__, HINWEIS, "open db:%s", spDB);

#ifdef ESQL_C
    if (spDB == NULL)
    {
        exec sql database DATABASE;
        g_strDatabase = DATABASE;
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
#endif

    return OK;
}

/****************************************************************************/
/* static int closeDB()                                                     */
/****************************************************************************/
static int closeDB()
{
#ifdef ESQL_C

    bool bDbSqlError = false;

    exec sql close database;
    ERROR_MSG( "close database", bDbSqlError);
    if (bDbSqlError)
    {
        return ERROR;
    }
#endif

    return OK;
}

/****************************************************************************/
/* int FillArticleCodeToArticleNumberMap()                                  */
/****************************************************************************/
int FillArticleCodeToArticleNumberMap()
{
    bool bDbSqlError = false;
    long resultsetnumber = 0;
#ifdef ESQL_C

    /* Prepare SELECT-Cursor articlecodes */
    EXEC SQL DECLARE curSelArticleCodes cursor for
      SELECT articleno, article_code into :g_lArticleNo, :g_articleCode
        from articlecodes where preferred_flag = 1;

    EXEC SQL OPEN curSelArticleCodes;
    for(;;)
    {
        EXEC SQL FETCH curSelArticleCodes;
        if(strncmp(SQLSTATE, "00", 2) != 0)
        {
            break;
        }
        std::string ac(g_articleCode);
        trim(ac);
        g_articleCodeToArticleNumberMap[ac]=g_lArticleNo;
        resultsetnumber++;
    }
    EXEC SQL close curSelArticleCodes;
    EXEC SQL free curSelArticleCodes;

    if(strncmp(SQLSTATE, "02", 2) > 0)
    {
        return CSVERR_ARTICLECODETOARTICLENUMBERMAP_SQL_ERROR;
    }
#endif

    return OK;
}

/****************************************************************************/
/* int FillPharmacyGroupToCustomerNumbersMap()                              */
/****************************************************************************/
int FillPharmacyGroupToCustomerNumbersMap()
{
    bool bDbSqlError = false;
    long resultsetnumber = 0;
#ifdef ESQL_C

    /* Prepare SELECT-Cursor pharmacygroups */
    EXEC SQL DECLARE curSelCustomerNos cursor for
        SELECT customerno, pharmacygroupid into :g_lCustomerNo, :g_lPharmacyGroup
        FROM customerpharmacygr
        LEFT JOIN kundeschalter ON kundeschalter.idfnr = customerpharmacygr.customerno
                                AND  kundeschalter.vertriebszentrumnr =customerpharmacygr.branchno
        WHERE customerpharmacygr.branchno = :g_branchNo
        AND(kundeschalter.skdkundeaegesperrt IS NULL OR kundeschalter.skdkundeaegesperrt <> 1);

    EXEC SQL OPEN curSelCustomerNos;
    for (;;)
    {
        EXEC SQL FETCH curSelCustomerNos;
        if (strncmp(SQLSTATE, "00", 2) != 0)
        {
            break;
        }
        std::map<long, std::vector<long>*>::iterator mapit;
        std::vector<long>* vecdata = NULL;
        mapit = g_pharmacyGroupToCustomerNumbersMap.find(g_lPharmacyGroup);
        if (mapit == g_pharmacyGroupToCustomerNumbersMap.end())
        {
            vecdata = new std::vector<long>();
            g_pharmacyGroupToCustomerNumbersMap[g_lPharmacyGroup] = vecdata;
        }
        else
        {
            vecdata = mapit->second;
        }
        vecdata->push_back(g_lCustomerNo);
        g_lGroupCustomerCount++;
        resultsetnumber++;
    }
    EXEC SQL close curSelCustomerNos;
    EXEC SQL free curSelCustomerNos;

    if (strncmp(SQLSTATE, "02", 2) > 0)
    {
        return CSVERR_PHARMACYGROUPTOCUSTOMERNOMAP_SQL_ERROR;
    }
#endif

    return OK;
}

/****************************************************************************/
/* int CleanupMaps()                                                        */
/****************************************************************************/
int CleanupMaps()
{
    std::map<long, std::vector<long>*>::iterator mapit;
    std::vector<long>* vecdata = NULL;

    mapit = g_pharmacyGroupToCustomerNumbersMap.begin();
    while (mapit != g_pharmacyGroupToCustomerNumbersMap.end())
    {
        vecdata = mapit->second;
        if (vecdata != NULL)
        {
            delete vecdata;
            vecdata = NULL;
        }
        g_pharmacyGroupToCustomerNumbersMap.erase(mapit);
        mapit = g_pharmacyGroupToCustomerNumbersMap.begin();
    }
    g_pharmacyGroupToCustomerNumbersMap.clear();

    return OK;
}

/****************************************************************************/
/* int UpdateOrInsertInDBCurrentQuota(CounterS &counterData, bool bDBCOmmit)*/
/****************************************************************************/
int UpdateOrInsertInDBCurrentQuota(CounterS &counterData, bool bDBCommit)
{
    bool bDbSqlError = false;

#ifdef ESQL_C
        EXEC SQL BEGIN DECLARE SECTION;
        long lCustomerNo = 0;
        EXEC SQL END DECLARE SECTION;

        // this prepare should be moved before the quotas loop starts to increase performance
        EXEC SQL PREPARE preSelQuotaDB from :g_selectStmt; 

        // SELECT articlequota to check if quota exists in DB
        EXEC SQL execute preSelQuotaDB into :lCustomerNo using :g_CurrentQuota.BRANCHNO, :g_CurrentQuota.CUSTOMERNO, :g_lArticleNo;
        // this free should be moved after the quotas loop end to increase performance
        EXEC SQL free preSelQuotaDB; 
        
        if (0 != lCustomerNo)
        {
            // quota exists, prepare Update or remove of this quota in Articlequota
            if (g_CurrentQuota.QUOTA < 0)
            {
                // remove quota (only in case its enabled and in delta mode)
                if (g_bNoDelete && g_bDeleteNegativeQuotas && g_CurrentQuota.QUOTA == -1)
                {
                    EXEC SQL delete from articlequota
                    where branchno = :g_CurrentQuota.BRANCHNO and customerno = :g_CurrentQuota.CUSTOMERNO and articleno = :g_lArticleNo;

                    bDbSqlError = (strcmp(SQLSTATE, "00000") != 0);
                    if (!bDbSqlError)
                    {
                        ++counterData.countDeletedOk;
                    }
                    else
                    {
                        ++counterData.countDeletedBad;
                        LogError("CSVERR_DATABASE_FAILED_DELETE: branch:%d, customer %ld, article:%ld, SQLSTATE: %s",
                            g_CurrentQuota.BRANCHNO, g_CurrentQuota.CUSTOMERNO, g_lArticleNo, SQLSTATE);
                        return CSVERR_DATABASE_FAILED_DELETE;
                    }
                }
                else
                {
                    ++counterData.countSkipped;
                    return CSVERR_RET_OK;
                }
            }
            else // g_CurrentQuota.QUOTA >= 0
            {
                std::string strUpdateMode;
                // update quota
                if (g_bNoDelete)
                {
                    // delta mode will not reset kumqty
                    EXEC SQL update articlequota
                        set QUOTA = :g_CurrentQuota.QUOTA, VALIDITY = :g_CurrentQuota.VALIDITY, DATEUPDATE = :g_lCurrentDate, DATEFROM = :g_CurrentQuota.DATEFROM, DATETO = :g_CurrentQuota.DATETO
                    where branchno = :g_CurrentQuota.BRANCHNO and customerno = :g_CurrentQuota.CUSTOMERNO and articleno = :g_lArticleNo;

                    strUpdateMode = "delta";
                }
                else
                {
                    // full mode will reset kumqty
                    EXEC SQL update articlequota
                        set QUOTA = :g_CurrentQuota.QUOTA, VALIDITY = :g_CurrentQuota.VALIDITY, DATEUPDATE = :g_lCurrentDate, DATEFROM = :g_CurrentQuota.DATEFROM, DATETO = :g_CurrentQuota.DATETO, KUMQTY = 0
                    where branchno = :g_CurrentQuota.BRANCHNO and customerno = :g_CurrentQuota.CUSTOMERNO and articleno = :g_lArticleNo;

                    strUpdateMode = "full";
                }

                bDbSqlError = (strcmp(SQLSTATE, "00000") != 0);
                LogSqlResult("UPDATE articlequota: branch:%d, customer:%ld, article:%ld in %s mode, SQLSTATE: %s",
                    bDbSqlError, g_CurrentQuota.BRANCHNO, g_CurrentQuota.CUSTOMERNO, g_lArticleNo, strUpdateMode.c_str(), SQLSTATE);
                if (!bDbSqlError)
                {
                    ++counterData.countUpdateOk;
                }
                else
                {
                    ++counterData.countUpdateBad;
                    LogError("CSVERR_DATABASE_FAILED_UPDATE, SQLSTATE: %s", SQLSTATE);
                    return CSVERR_DATABASE_FAILED_UPDATE;
                }
            }
        }
        else // insert
        {
            //Insert quota in table articlequota

            // do not INSERT any negative quota values!
            if (g_CurrentQuota.QUOTA < 0)
            {
                ++counterData.countSkipped;
                return CSVERR_RET_OK;
            }

            // Prepare insert of this quota in Articlequota
            EXEC SQL insert into articlequota(BRANCHNO, CUSTOMERNO, ARTICLENO, QUOTA, KUMQTY, VALIDITY, DATEUPDATE, UID_ANLAGE, SDAFUEQUOTA, DATEFROM, DATETO, PHARMACYGROUPID, SNOBATCHCHANGE)
                values(:g_CurrentQuota.BRANCHNO, :g_CurrentQuota.CUSTOMERNO, :g_lArticleNo, :g_CurrentQuota.QUOTA, 0, :g_CurrentQuota.VALIDITY, :g_lCurrentDate, 0, '', :g_CurrentQuota.DATEFROM, :g_CurrentQuota.DATETO, '', '');

            bDbSqlError = (strcmp(SQLSTATE, "00000") != 0);
            LogSqlResult("INSERT articlequota: branch:%d, customer:%ld, article:%ld, SQLSTATE: %s",
                bDbSqlError, g_CurrentQuota.BRANCHNO, g_CurrentQuota.CUSTOMERNO, g_lArticleNo, SQLSTATE);
            if (!bDbSqlError)
            {
                ++counterData.countInsertOk;
            }
            else
            {
                ++counterData.countInsertBad;
                LogError("CSVERR_DATABASE_FAILED_INSERT, SQLSTATE: %s", SQLSTATE);
                return CSVERR_DATABASE_FAILED_INSERT;
            }
        }

        counterData.counterForCommit++;
        if (counterData.counterForCommit >= g_lCommitAfter || bDBCommit)
        {
            EXEC SQL COMMIT WORK;

            bDbSqlError = (strcmp(SQLSTATE, "00000") != 0);
            LogSqlResult("COMMIT WORK, SQLSTATE: %s", bDbSqlError, SQLSTATE); 

            if (bDbSqlError)
            {
                return CSVERR_DATABASE_SQL_ERROR;
            }
            LogDebug("Commit %ld", counterData.counterForCommit);

            counterData.counterForCommit = 0;
            // commit was done before, so check for pause
            if (g_lCommitPause > 0)
            {
                LogDebug("Pausing after commit:%ld msec", g_lCommitPause);
                usleep(g_lCommitPause * 1000);
            }
        }
 
#endif
    return CSVERR_RET_OK;
}

/****************************************************************************/
/* int UpdateOrInsertInDBQuotas(const InputData& quotasFromCSV)             */
/****************************************************************************/
int UpdateOrInsertInDBQuotas(const InputData& quotasFromCSV)
{
    LogDebug0("Start >>>");

    bool bDbSqlError = false;
    bool bArticleCodeNotExisting = false;
    CounterS counterData;
    int result = OK;

    strcpy(g_selectStmt, "SELECT customerno FROM articlequota ");
    strcat(g_selectStmt, "where branchno = ? and customerno = ? and articleno = ?");

    LogDebug("Records being processed: %ld", quotasFromCSV.RecCount());

    for (unsigned int csvIndex = 0; csvIndex < quotasFromCSV.RecCount(); csvIndex++)
    {
        bDbSqlError = false;

        ConvertQuotaStructs(g_CurrentQuota, quotasFromCSV[csvIndex]);
        // Look for the ArticleNo corrsponding current ArticleCode
        std::map<std::string, long>::iterator mapit;
        mapit = g_articleCodeToArticleNumberMap.find(g_CurrentQuota.ARTICLE_CODE);
        if (mapit == g_articleCodeToArticleNumberMap.end())
        {
            LogError("ArticleCode[%s] is not existing in articlecodes table, error code <% i>", g_CurrentQuota.ARTICLE_CODE, CSVERR_ARTICLE_NOT_FOUND);
            bArticleCodeNotExisting = true;
            continue;
        }
        g_lArticleNo = mapit->second;

        // Update DB for current quota
        bool bCommit = false;
        if (g_CurrentQuota.CUSTOMERNO > 0)
        {
            // dedicated per customer
            bCommit = (csvIndex == (quotasFromCSV.RecCount() - 1)); // commit anyway if it's the last row in the csv
            result = UpdateOrInsertInDBCurrentQuota(counterData, bCommit);
        }
        else if (g_CurrentQuota.CUSTOMERNO == -1 && g_CurrentQuota.PHARMACYGROUPID > 0)
        {
            // per pharmacygroup all customers, which were found
            std::vector<long>* vecCustomersNo = GetCustomersFromPharmacyGroupID(g_CurrentQuota.PHARMACYGROUPID);
            if (vecCustomersNo != NULL)
            {
                for (int i = 0; i < vecCustomersNo->size(); i++)
                {
                    g_CurrentQuota.CUSTOMERNO = vecCustomersNo->at(i);
                    bCommit = ((csvIndex == (quotasFromCSV.RecCount() - 1)) && (i == vecCustomersNo->size())); // commit anyway if it's the last row in the csv and last customer in the group
                    result = UpdateOrInsertInDBCurrentQuota(counterData, bCommit);
                }
            }
            else
            {
                LogWarning("No customers for pharmacyGroup (%ld) found, so no quotas will be inserted or updated for this group", g_CurrentQuota.PHARMACYGROUPID);
            }
        }
    }

    LogDebug0("records updated:");
    LogDebug("\twith Ok:       %ld", counterData.countUpdateOk);
    LogDebug("\twith Not Ok:   %ld", counterData.countUpdateBad);

    LogDebug0("records inserted:");
    LogDebug("\twith Ok:       %ld", counterData.countInsertOk);
    LogDebug("\twith Not Ok:   %ld", counterData.countInsertBad);

    LogDebug0("records deleted:");
    LogDebug("\twith Ok:       %ld", counterData.countDeletedOk);
    LogDebug("\twith Not Ok:   %ld", counterData.countDeletedBad);

    LogDebug("records skipped: %ld", counterData.countSkipped);

    LogDebug0("Finish <<<");
	
    return OK;
}

/****************************************************************************/
/* int DeleteOLDDBQuotas()                                                  */
/****************************************************************************/
int DeleteOLDDBQuotas()
{
    LogDebug0("Start >>>");

    bool bDbSqlError = false;

    LogDebug("Currentdate=%ld, delete older ones", g_lCurrentDate);

#ifdef ESQL_C
    /* remove old records/quota */
    EXEC SQL delete from articlequota 
      where branchno = :g_CurrentQuota.BRANCHNO and dateupdate < :g_lCurrentDate;

    if(strncmp(SQLSTATE, "02", 2) > 0)
    {
        return CSVERR_DATABASE_FAILED_DELETE;
    }

    EXEC SQL COMMIT WORK;
    ERROR_MSG("COMMIT WORK", bDbSqlError);
#endif

    LogDebug0("Finish <<<");
    return OK;
}

/****************************************************************************/
/* int GetCustomersFromPharmacyGroupID(std::vector<long> &vecCustomersNo)   */
/****************************************************************************/
std::vector<long>* GetCustomersFromPharmacyGroupID(long pharmacyGroup)
{
    std::map<long, std::vector<long>*>::iterator mapit;
    std::vector<long>* vecdata = NULL;

    mapit = g_pharmacyGroupToCustomerNumbersMap.find(pharmacyGroup);
    if (mapit != g_pharmacyGroupToCustomerNumbersMap.end())
    {
        vecdata = mapit->second;
    }
    return vecdata;
}

/****************************************************************************/
/* long GetActualDate()                                                     */
/****************************************************************************/
long GetActualDate()
{
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer[80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer, 80, "%Y%m%d", timeinfo);

    std::string dateString(buffer);
    long actualDate = std::stoi(dateString);
    return actualDate;
}

/*********************************************************************************/
/* static int ReadCommandLineParams( char** argv )                               */
/*********************************************************************************/
static bool ReadCommandLineParams(int argc, char* argv[])
{
    int i;
    char* param;
    bool skip = false;

    for (i = 1; i < argc; i++)
    {
        param = argv[i];

        if (strcmp(param, "-db") == 0)
        {
            i++;
            g_strDatabase = argv[i];
        }
        else if (strcmp(param, "-inputcsv") == 0)
        {
            i++;
            g_strCSVFile = argv[i];
        }
        else if (strcmp(param, "-nodelete") == 0)
        {
            g_bNoDelete = true;
        }
        else if (strcmp(param, "-version") == 0)
        {
            std::cout << versioninfo << std::endl;
            g_blnVersion = TRUE;
            return true;
        }
        else
        {
            skip = true;
        }
    }

    if (argc == 1 || skip == true)
    {
        PrintMsg(__func__, HINWEIS, "Incorrect program parameters!");
        return false;
    }

    return true;
}

/*********************************************************************************/
/* static bool ReadIniFileParams()                                               */
/*********************************************************************************/
static bool ReadIniFileParams()
{
    std::string line;
    std::string param;
    std::string value;

    std::ifstream filestream(g_strIniFile);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            trim(line);
            if ((line.empty() == false) && (line.substr(0, 1).compare("[") != 0) &&
                (line.substr(0, 1).compare("#") != 0) && (line.substr(0, 1).compare(";") != 0))
            {
                std::string::size_type pos = line.find("=");
                if (pos != std::string::npos)
                {
                    param = line.substr(0, pos);
                    value = line.substr(pos + 1);
                    trim(param);
                    trim(value);
                    if (param.compare("delimiter") == 0)
                    {
                        if (value.size() != 0)  g_cDelimiter = value.at(0);
                        LogDebug("delimiter: [%c]", g_cDelimiter);
                    }
                    else if (param.compare("commiteach") == 0)
                    {
                        convertStringToLong(value, g_lCommitAfter, 1);
                        LogDebug("commit after: [%ld]", g_lCommitAfter);
                    }
                    else if (param.compare("commitpause") == 0)
                    {
                        convertStringToLong(value, g_lCommitPause, 0);
                        LogDebug("commit pause: [%ld]", g_lCommitPause);
                    }
                    else if (param.compare("deletenegativequotas") == 0)
                    {
                        if (value.compare("true") == 0)
                        {
                            g_bDeleteNegativeQuotas = true;
                        }
                        else
                        {
                            g_bDeleteNegativeQuotas = false;
                        }
                        LogDebug("DeleteNegativeQuotas: [%s]", value.c_str());
                    }
                    else if (param.compare("ArticleNumber") == 0)
                    {
                        g_strArticleNumberFilter = value;
                        LogDebug("Article Number Filter: [%s]", g_strArticleNumberFilter.c_str());
                    }
                    else if ((param.compare("CSVFilePatternPrefix") == 0) && (value.length() > 0))
                    {
                        g_strCSVFilePatternPrefix = value;
                    }
                    else if ((param.compare("CSVFilePatternDelta") == 0) && (value.length() > 0))
                    {
                        g_strCSVFilePatternDelta = value;
                    }
                    else if ((param.compare("CSVFilePatternBranch") == 0) && (value.length() > 0))
                    {
                        g_strCSVFilePatternBranch = value;
                    }
                }
            }
        }
        filestream.close();
    }
    else
    {
        return false;
    }
    return true;
}

/********************************************************************************/
/* int main( int argc, char **argv )                                            */
/********************************************************************************/
int main(int argc, char* argv[])
{
    char error_msg[512] = "";
    const char* env = NULL;

    g_lCurrentDate = GetActualDate();
    g_strDatabase = "";
    g_strCSVFile = "";
    g_strLogFile = "";
    g_strIniFile = "";
    g_bNoDelete = false;
    g_blnVersion = false;

    /*****************************************************/
    /* scan and validate command line parameters         */
    /*****************************************************/
    if (ReadCommandLineParams(argc, argv) == false)
    {
        ShowUsage(argv[0]);
        return CSVERR_MISSING_OR_WRONG_PARAMETERS;
    }
    if (g_blnVersion == true)
    {
        ShowUsage(argv[0]);
        return CSVERR_RET_OK;
    }
    if ((g_strDatabase.empty() == true) || (g_strCSVFile.empty() == true))
    {
        ShowUsage(argv[0]);
        return CSVERR_MISSING_OR_WRONG_PARAMETERS;
    }

    /*****************************************************/
    /* initialization log and ini file                   */
    /*****************************************************/
    setbuf(stdout, 0);

    // base file
    std::string strAppName = argv[0];
    std::string strBaseFile = strAppName.substr(strAppName.find_last_of("/\\") + 1);
    std::string strBaseName = strBaseFile.substr(0, strBaseFile.find_last_of("."));

    // log file
    g_strLogFile = strBaseName + std::to_string(GetActualDate()) + ".log";
    env = getenv("LOG_PATH");
    if (env == NULL)
    {
        env = ".";
    }
    g_strLogFile = std::string(env) + g_strPathDel + g_strLogFile;
    LogDebug("log file: %s", g_strLogFile.c_str());

    // ini file
    g_strIniFile = strBaseName + ".ini";
    env = getenv("INI_PATH");
    if (env == NULL)
    {
        env = ".";
    }
    g_strIniFile = std::string(env) + g_strPathDel + g_strIniFile;
    LogDebug("ini file: %s", g_strIniFile.c_str());
    // read the ini file settings
    if (ReadIniFileParams() == false)
    {
        return CSVERR_INI_FILE_MISSING_OR_WRONG_PARAMETERS;
    }

    // get file name
    std::string strFileName, strPath;
    GetFilePathAndName(g_strCSVFile, strPath, strFileName);

    // get info from csv input file based on ini file settings for CSV File pattern
    // standard file pattern for full imports: quota_YYYYMMDD_branchno_XX.csv
    // standard file pattern for delta imports: quota_delta_YYYYMMDD_branchno_XX.csv
    long lFileProcessDate = 0;
    long lFileBranchNo = 0;
    bool blnFileDelta = false;
    bool blnFilePattern = false;
    if (strFileName.substr(0, g_strCSVFilePatternPrefix.length()) == g_strCSVFilePatternPrefix)
    {
        std::string::size_type pos = g_strCSVFilePatternPrefix.length();
        if (strFileName.substr(pos, g_strCSVFilePatternDelta.length()) == g_strCSVFilePatternDelta)
        {
            blnFileDelta = true;
            pos += g_strCSVFilePatternDelta.length();
        }
        std::string strDate = strFileName.substr(pos, 8); // always 8 digits as YYYYMMDD
        convertStringToLong(strDate, lFileProcessDate, g_lCurrentDate);
        pos = strFileName.find(g_strCSVFilePatternBranch);
        if (pos != std::string::npos)
        {
            std::string strBranch = strFileName.substr(pos + g_strCSVFilePatternBranch.length(), 2); // always 2 digits
            convertStringToLong(strBranch, lFileBranchNo, 0);
        }
        if (blnFileDelta == true)
        {
            LogDebug("CSV Input File (%s) identified as delta file with process date '%ld' and branch no '%ld'", g_strCSVFile.c_str(), lFileProcessDate, lFileBranchNo);
        }
        else
        {
            LogDebug("CSV Input File (%s) identified as full file with process date '%ld' and branch no '%ld'", g_strCSVFile.c_str(), lFileProcessDate, lFileBranchNo);
        }
        if (lFileBranchNo > 0)
        {
            blnFilePattern = true;
            g_branchNo = (short)lFileBranchNo;
        }
    }
    if (blnFilePattern == false)
    {
        LogDebug("CSV Input File (%s) does not have expected file pattern (quota_<delta>_<YYYYMMDD>_branchno_<xx>.csv), imported aborted!", g_strCSVFile.c_str());
        return CSVERR_ERROR_FILENAME_PATTERN;
    }
    if (blnFileDelta != g_bNoDelete)
    {
        std::string appmode = "full";
        if (g_bNoDelete == true) { appmode = "delta"; }
        std::string filemode = "full";
        if (blnFileDelta == true) { filemode = "delta"; }
        LogDebug("Import was started in %s mode, but the file pattern is %s mode (file %s), imported aborted!", appmode.c_str(), filemode.c_str(), g_strCSVFile.c_str());
        return CSVERR_ERROR_FILENAME_PATTERN;
    }
    /*****************************************************/
    /* Open database                                     */
    /*****************************************************/
    if (openDB() != OK)
    {
        LogError("Error opening database! error code <%i>", CSVERR_ERROR_OPENING_DATA_BASE);
        LogDebug0("finished");
        return CSVERR_ERROR_OPENING_DATA_BASE;
    }

    //Fill the map for articlecode to articlenumber mapping
    LogDebug0("loading articlecode mappings...");
    if (OK != FillArticleCodeToArticleNumberMap())
    {
        PrintMsg(__func__, FEHLER, "Error creating map articleCode to articleNumber error code <%i>", CSVERR_ARTICLECODETOARTICLENUMBERMAP_SQL_ERROR);
        PrintMsg(__func__, HINWEIS, "Aborting");
        return CSVERR_ARTICLECODETOARTICLENUMBERMAP_SQL_ERROR;
    }
    LogDebug("articleCode mappings successfully loaded (%ld rows)", g_articleCodeToArticleNumberMap.size());

    //Fill the map for pharmacygroups to customer numbers for branch
    if (OK != FillPharmacyGroupToCustomerNumbersMap())
    {
        PrintMsg(__func__, FEHLER, "Error creating map pharmacyGroup to customerNumbers error code <%i>", CSVERR_ARTICLECODETOARTICLENUMBERMAP_SQL_ERROR);
        PrintMsg(__func__, HINWEIS, "Aborting");
        return CSVERR_PHARMACYGROUPTOCUSTOMERNOMAP_SQL_ERROR;
    }
    LogDebug("pharmacyGroup mappings successfully loaded (%ld rows)", g_lGroupCustomerCount);

    /*****************************************************/
    /* Load of quota data from CSV                       */
    /*****************************************************/
    LogDebug("processing file: %s", g_strCSVFile.c_str());

    InputData readQuotas;
    readQuotas.LoadFromFile(g_strCSVFile, g_strArticleNumberFilter);
    LogDebug("rec count:%ld", readQuotas.RecCount());

    /*****************************************************/
    /* UpdateOrInsertInDBQuotas from CSV file content    */
    /*****************************************************/
    UpdateOrInsertInDBQuotas(readQuotas);

    /*****************************************************/
    /* Delete in case of full import for older data      */
    /*****************************************************/
    if (g_bNoDelete == false)
    {
        //Delete the articlequota entries for this branch older than current start date 
        if (OK != DeleteOLDDBQuotas())
        {
            LogError("Error deleting old articlequotas for branch (%d) error code <%i>", g_branchNo, CSVERR_DATABASE_FAILED_DELETE);
            LogDebug0("Aborting");
            return CSVERR_DATABASE_FAILED_DELETE;
        }
    }
    else
    {
        LogDebug0("Deletion disabled by command line option");
    }

    /*****************************************************/
    /* Cleanup                                           */
    /*****************************************************/
    CleanupMaps();

    /*****************************************************/
    /* Close database                                    */
    /*****************************************************/
    if (closeDB() != OK)
    {
        LogError("Error closing database! error code <%i>", CSVERR_ERROR_CLOSING_DATA_BASE);
        LogDebug0("Finished");
        return CSVERR_ERROR_CLOSING_DATA_BASE;
    }

    LogDebug0("Finish <<<\n");

    return CSVERR_RET_OK;
}
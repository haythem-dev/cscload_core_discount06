// zpexpensv.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <libscsvoodoo/libscsvoodoo.h>
#include <chrono>
#include <algorithm>
#include <utility>
#include "zpexpensv.h"

#define RET_SUCCESS             0
#define RET_ERR_DB_CONNECTION   1
#define RET_ERR_SQL             2
#define RET_ERR_APP_ARGUMENTS   9

#define LOG_TYPE_INFO  0
#define LOG_TYPE_WARN  1
#define LOG_TYPE_ERROR 2

CZPExpensive::CZPExpensive()
{
    // constructor
    m_pipConnection = NULL;
    m_strAppName = "";
    m_strDBName = "";
    m_strServerName = "";
    m_strServiceName = "";
    m_intPort = 0;
    m_strLogFile = "";
}

CZPExpensive::~CZPExpensive()
{
    Reset();
}

void CZPExpensive::Reset()
{
}

bool CZPExpensive::Init(int argc, char* argv[])
{
    // cnt = 0 is the application name only
    int cnt = 1;
    std::string param = "";
    std::string value = "";
    // get the app name 
    m_strAppName = argv[0];
    // windows
    size_t pos = m_strAppName.find_last_of('\\');
    if (pos != std::string::npos)
    {
        m_strAppName = m_strAppName.substr(pos + 1);
    }
    //unix
    pos = m_strAppName.find_last_of('/');
    if (pos != std::string::npos)
    {
        m_strAppName = m_strAppName.substr(pos + 1);
    }
    // remove extension(s)
    pos = m_strAppName.find(".");
    if (pos != std::string::npos)
    {
        m_strAppName = m_strAppName.substr(0, pos);
    }
    // check other params
    while (cnt < argc)
    {
        param = argv[cnt];
        cnt++;
        value = "";
        if (cnt < argc)
        {
            value = argv[cnt];
            cnt++;
        }
        if (param.compare("-db") == 0)
        {
            m_strDBName = value;
        }
    }
    if (m_strDBName.empty() == true)
    {
        // mandatory parameters missing
        return false;
    }

    // set logfile settings
    char* logPath = std::getenv("LOG_PATH");
    if (logPath != NULL)
    {
        // absolute path
        m_strLogFile = std::string(logPath) + "/" + m_strAppName + ".log";
    }
    else
    {
        // relative path
        m_strLogFile = m_strAppName + ".log";
    }

    return true;
}

void CZPExpensive::Usage()
{
    // print out the usage parameters for the app
    printf("Usage: %s -db <db> \n", m_strAppName.c_str());
    printf("  -db <db>         -> the database name to connect to\n");
    printf("  -oepr <file>     -> optional parameter. CSC Order Entry Permission Report CSV file to merge (only for mode 0)\n");
}

bool CZPExpensive::WriteLogFile(int logtype, std::string log)
{
    FILE* pFile = fopen(m_strLogFile.c_str(), "a");
    struct tm* stime;
    time_t now;

    if (pFile == NULL)
        return false;

    now = time(&now);
    stime = localtime(&now);

    std::string fullline = "";
    //add timestamp
    char timebuf[100];
    sprintf(timebuf,"%02d.%02d.%04d %02d:%02d:%02d ", stime->tm_mday, stime->tm_mon + 1, 1900 + stime->tm_year, stime->tm_hour, stime->tm_min, stime->tm_sec);
    fullline += std::string(timebuf);
    //add logtype
    if (logtype == LOG_TYPE_WARN)
    {
        fullline += "[WARNING]: ";
    }
    else if (logtype == LOG_TYPE_ERROR)
    {
        fullline += "[ERROR]: ";
    }
    else
    {
        fullline += "[INFO]: ";
    }
    fullline += log;
    fputs(fullline.c_str(), pFile);
    fputc('\n', pFile);

    fclose(pFile);

    printf("%s\n", log.c_str());

    return true;
}

bool CZPExpensive::OpenDatabase()
{
    long lngStatus = 0;
    std::string strError = "";

#if defined(WIN32)
    //for test connect to voodoo server pipe via server, service and port
    //from etc/services: cdm_zdp_bg		60391/tcp	# CDM Server BG
    //refer as well to the dbasefkt.cpp::OpenServerIntern

    m_strServerName = "zdev21";
    m_strServiceName = "zdpuiserv_bg.bin";
    m_intPort = 60391;
    lngStatus = ViaEshuOpenEx(&m_pipConnection, m_strServerName.c_str(), m_strServiceName.c_str(), m_intPort);
    if (lngStatus != 0)
    {
        strError = "pipe " + m_strServiceName+ "@" + m_strServerName + ": " + std::string(DynErrmld());
        WriteLogFile(LOG_TYPE_ERROR, strError);
        return false;
    }
#else
#endif

    // connect to defined database
    std::string strConn = "database " + m_strDBName;

    lngStatus = SqlExecuteImm(strConn.c_str());
    if (lngStatus != 0)
    {
        strError = strConn + ": " + std::string(DynErrmld());
        WriteLogFile(LOG_TYPE_ERROR, strError);
        return false;
    }

    lngStatus = SqlExecuteImm("set isolation to dirty read");
    if (lngStatus == SQL_SETISOLA_ERROR)
        lngStatus = 0; // ignore set isola error
    if (lngStatus != 0)
    {
        strError = "set isolation: " + std::string(DynErrmld());
        WriteLogFile(LOG_TYPE_ERROR, strError);
        CloseDatabase();
        return false;
    }

    lngStatus = SqlExecuteImm("SET LOCK MODE TO WAIT 10");
    if (lngStatus == SQL_SETISOLA_ERROR)
        lngStatus = 0; // ignore set isola error
    if (lngStatus != 0)
    {
        strError = "set lock mode: " + std::string(DynErrmld());
        WriteLogFile(LOG_TYPE_ERROR, strError);
        CloseDatabase();
        return false;
    }
    return true;
}

bool CZPExpensive::CloseDatabase()
{
    SqlExecuteImm("close database");
#if defined(WIN32)
    // for test, close pipe
    NmpCloseHandle(m_pipConnection);
#else
#endif
    return true;
}

void CZPExpensive::Round_ModF(double* value, int digits)
{
    // the round is defined as round(value,digits)
    // round function : rest = modf(value * 10 ^ digits + 0.5, &value); if rest > 0.9999 then result += 1.0; value = value / 10 ^ digits;
    if (digits >= 0)
    {
        int i;
        int    sign = 1;
        double rdigit = 1.0;
        double result;
        double rest;

        for (i = 0; i < digits; i++) rdigit *= 10.0;

        result = *value;
        // in case of negative
        if (result < 0.0)
        {
            result = -result;
            sign = -1;
        }
        // round up
        rest = modf(result * rdigit + 0.5, &result);
        if (rest >= 0.99999999)
            result += 1.0;

        result /= rdigit;
        *value = result * sign;
    }
}

int CZPExpensive::getExpensiveTreshholdValue(double &expthreshholdval, char* errMsg)
{
    int          ret = RET_SUCCESS;
    long         sqlStatus = 0;
    std::string  sqlQuery;
    char*        value[241];

    // read the values from parameter table for zpexpnsv, which is maintained by EkZDP ExpensiveParamView and ExpensiveParamDoc
    sqlQuery = "select auspraeg from parameterkd where filialnr=0 and programmname='zpexpnsv' and parametername='ExpensiveValue'";
    sqlStatus = SqlRead(sqlQuery.c_str(), value, NULL);
    if (sqlStatus == SQL_SUCCESS)
    {
        expthreshholdval = atof((const char*)value);
        Round_ModF(&expthreshholdval, 2);
    }
    else
    {
        strcat(errMsg, DynErrmld());
        ret = RET_ERR_SQL;
    }
    return ret;
}

int CZPExpensive::updateExpensiveFlag(double expthreshholdval, char* errMsg)
{
    // update the expensive flag based on the article's GEPNA (must be calculated) and the expensive threshold value
    int          ret = RET_SUCCESS;
    long         sqlStatus = 0;
    int          sqlHandle;
    std::string  sqlQuery;
    std::vector<ARTICLEDATA*> vecArticles;

    // first step is to get all needed informations per article
    sqlQuery = "SELECT b.articleno, p.grosso, b.invoice_rebate_pct, b.rebate_in_kind_pct, b.expensive FROM zartbulgaria b, zartpreis p ";
    sqlQuery += "WHERE b.articleno = p.artikel_nr AND p.datumgueltigab = (SELECT MAX(z.datumgueltigab) FROM zartpreis z WHERE z.artikel_nr = p.artikel_nr ";
    sqlQuery += "AND z.datumgueltigab <= to_char(sysdate,'%Y%m%d')) ORDER BY b.articleno";

    ARTICLEDATA* pPrevArticle = NULL;
    sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery.c_str());
    if (sqlStatus == SQL_SUCCESS)
    {
        do  // loop result
        {
            ARTICLEDATA* pArticle = new ARTICLEDATA();
            memset(pArticle, 0, sizeof(ARTICLEDATA));
            sqlStatus = SqlFetch(sqlHandle, 1, &pArticle->ARTICLENO, &pArticle->GROSSO, &pArticle->INVOICE_REBATE_PCT, &pArticle->REBATE_IN_KIND_PCT, &pArticle->EXPENSIVE, NULL);
            if (sqlStatus == SQL_SUCCESS)
            {
                // there might be duplicates in db because of pricing with same datumgueltigab, prevent adding them for next steps
                if ((pPrevArticle != NULL) && (pArticle != NULL))
                {
                    if (pPrevArticle->ARTICLENO != pArticle->ARTICLENO)
                    {
                        // no duplicate, so add it to list
                        vecArticles.push_back(pArticle);
                        pPrevArticle = pArticle;
                    }
                    else
                    {
                        // duplicate, ignore it
                        delete pArticle;
                    }
                }
                else
                {
                    // first one, so add it to list
                    vecArticles.push_back(pArticle);
                    pPrevArticle = pArticle;
                }
            }
            else
            {
                delete pArticle;
            }
        } 
        while (sqlStatus == SQL_SUCCESS);
        WriteLogFile(LOG_TYPE_INFO, "Found " + std::to_string(vecArticles.size()) + " articles");
    }
    else
    {
        strcat(errMsg, DynErrmld());
        ret = RET_ERR_SQL;
    }
    SqlCloseCs(sqlHandle);

    // to update the expensive flag, the GEPNA must be calculated before
    // the GEPNA is defined as 
    // GEPNA = round(zartpreis.grosso * (100 - (zartbulgaria.invoice_rebate_pct + ((zartbulgaria.rebate_in_kind_pct / (100 + zartbulgaria.rebate_in_kind_pct)) * 100))) / 100, 2)
    int cnt_exp_set_unchanged = 0;
    int cnt_exp_unset_unchanged = 0;
    int cnt_exp_set_changed = 0;
    int cnt_exp_unset_changed = 0;
    int cnt_exp_error = 0;
    std::vector<ARTICLEDATA*>::iterator it;
    for (it = vecArticles.begin(); it != vecArticles.end(); it++)
    {
        ARTICLEDATA* pArticle = *it;
        //calculate gepna
        pArticle->GEPNA = pArticle->GROSSO * (100 - (pArticle->INVOICE_REBATE_PCT + ((pArticle->REBATE_IN_KIND_PCT / (100 + pArticle->REBATE_IN_KIND_PCT)) * 100))) / 100;
        //round
        Round_ModF(&pArticle->GEPNA, 2);
        bool expchange = false;
        //compare with threshhold if expensive needs to be updated
        if ((pArticle->GEPNA >= expthreshholdval) && (pArticle->EXPENSIVE == 0))
        {
            // set expensive flag
            pArticle->EXPENSIVE = 1;
            expchange = true;
            cnt_exp_set_changed++;
        }
        else if ((pArticle->GEPNA < expthreshholdval) && (pArticle->EXPENSIVE != 0))
        {
            // unset expensive flag
            pArticle->EXPENSIVE = 0;
            expchange = true;
            cnt_exp_unset_changed++;
        }
        else if (pArticle->EXPENSIVE != 0)
        {
            // no change, stays flagged
            cnt_exp_set_unchanged++;
        }
        else if (pArticle->EXPENSIVE == 0)
        {
            // no change, stays unflagged
            cnt_exp_unset_unchanged++;
        }
        // update db if changed
        if (expchange == true)
        {
            sqlQuery  = "UPDATE zartbulgaria SET expensive = " + std::to_string(pArticle->EXPENSIVE);
            sqlQuery += " WHERE articleno = " + std::to_string(pArticle->ARTICLENO);
            sqlStatus = SqlExecuteImm(sqlQuery.c_str());
            if (sqlStatus != SQL_SUCCESS)
            {
                cnt_exp_error++;
            }
        }
    }
    WriteLogFile(LOG_TYPE_INFO, "Expensive Flag=1, unchanged for "+ std::to_string(cnt_exp_set_unchanged) + " articles");
    WriteLogFile(LOG_TYPE_INFO, "Expensive Flag=0, unchanged for " + std::to_string(cnt_exp_unset_unchanged) + " articles");
    WriteLogFile(LOG_TYPE_INFO, "Expensive changed to Flag=1 for " + std::to_string(cnt_exp_set_changed) + " articles");
    WriteLogFile(LOG_TYPE_INFO, "Expensive changed to Flag=0 for " + std::to_string(cnt_exp_unset_changed) + " articles");
    WriteLogFile(LOG_TYPE_INFO, "Expensive Flag change errors for " + std::to_string(cnt_exp_error) + " articles");
    return ret;
}

int CZPExpensive::Run()
{
    int          ret = RET_SUCCESS;
    char         errMsg[1000];

    // Open DB connection
    if (OpenDatabase() == false)
    {
        WriteLogFile(LOG_TYPE_ERROR, "No DB Connection established, abort program.");
        return RET_ERR_DB_CONNECTION;
    }
    WriteLogFile(LOG_TYPE_INFO, "DB Connection to " + m_strDBName + "@" + m_strServerName + " successful");

    #ifdef _DEBUG
    auto startTime = std::chrono::high_resolution_clock::now();
    #endif

    // get expensive threshhold value
    double expthreshholdval = 0.0;
    ret = getExpensiveTreshholdValue(expthreshholdval, errMsg);
    
    if (ret == RET_SUCCESS)
    {
        // update expensive flag for bulgaria based on threshhold (yes >= threshhold, no < threshhold)
        ret = updateExpensiveFlag(expthreshholdval, errMsg);
    }
    // Close the db connection
    CloseDatabase();

    if (ret != RET_SUCCESS)
    {
        // any error must be logged
        WriteLogFile(LOG_TYPE_ERROR, "Error in zpexpensv, abort program.");
    }

    #ifdef _DEBUG
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    WriteLogFile(LOG_TYPE_INFO, "Execution duration: " + std::to_string(duration / 1000 ) + " s");
    #endif

    WriteLogFile(LOG_TYPE_INFO, "DB closed, process successfully completed");
    return ret;
}

///////////////////////////////////////// Main /////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    CZPExpensive theApp;

    if (theApp.Init(argc, argv) == false)
    {
        theApp.Usage();
        return RET_ERR_APP_ARGUMENTS; // exit with return code of missing/wrong parameters
    }
    return theApp.Run();
}

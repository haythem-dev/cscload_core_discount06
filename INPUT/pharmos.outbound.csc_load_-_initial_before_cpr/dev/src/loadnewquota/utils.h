#ifndef _UTILS_H
#   define _UTILS_H

#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <cstring>
#include <iomanip>

#ifndef __GNUC__
#include <regex>
#else
#include <regex.h>
#endif

/********************************************************************************/
/* OS specifics */
/********************************************************************************/
#ifdef _WIN32
static std::string g_strPathDel = "\\";
#else
static std::string g_strPathDel = "/";
#endif
std::string g_strLogFile = "";

#ifndef __GNUC__
static bool ApplyFilter(const std::string& s, const std::regex& reFilter)
{
    return std::regex_search(s, reFilter);
}
#else
static bool ApplyFilter(const std::string& s, const regex_t& reFilter)
{
    return regexec(&reFilter, s.c_str(), 0, NULL, 0) == 0;
}
#endif

/********************************************************************************/
/* MACROS and LOG definitions */
/********************************************************************************/
#define LogDebug0(msg) PrintMsg(__func__, HINWEIS, msg);
#define LogDebug(fmt, ...) PrintMsg(__func__, HINWEIS, fmt, __VA_ARGS__);

#define LogWarning0(msg) PrintMsg( __func__, WARNUNG, msg );
#define LogWarning(fmt, ...) PrintMsg( __func__, WARNUNG, fmt, __VA_ARGS__);

#define LogError0(msg) PrintMsg( __func__, FEHLER, msg );
#define LogError(fmt, ...) PrintMsg( __func__, FEHLER, fmt, __VA_ARGS__);

// message only
#define LogSqlResult0(msg) if(SQLCODE < 0) { LogError(msg); }

// format message
#define LogSqlResult1(fmt, ...) if(SQLCODE < 0) { PrintMsg( __func__, FEHLER, fmt, __VA_ARGS__ ); }

#define LogSqlResult2(msg, sqlError) if(SQLCODE < 0) { PrintMsg( __func__, FEHLER, msg); sqlError = true; }

// message full data
#define LogSqlResult(fmt, sqlError, ...) if(SQLCODE < 0) { PrintMsg( __func__, FEHLER, fmt, __VA_ARGS__ ); sqlError = true; }

#define ERROR_MSG(x, sqlError) if(SQLCODE < 0) { PrintMsg( __func__, FEHLER, x ); sqlError = true; }

/************************************************************************************************************/
/* static void PrintMsg(char *__func__, char mld, char *error_msgFormat, ... )                              */
/************************************************************************************************************/
static void PrintMsg(const char* func, const char mld, const char* error_msgFormat, ...)
{
    struct tm* stime;
#ifndef _WIN32
    pid_t pid;
    long shour;
#else
    long pid;
    time_t shour;
#endif
    char tbuf[1000];
    va_list arg_ptr;

    memset(&tbuf, 0, 1000);

#ifndef _WIN32
    pid = getpid();
    shour = time(&shour);
    stime = localtime(&shour);
#else
    pid = 0;
    shour = time(&shour);
    stime = localtime(&shour);
#endif

    std::ofstream log;
    log.open(g_strLogFile, std::ofstream::out | std::ofstream::app);

    if (stime->tm_year > 99)
    {
        stime->tm_year -= 100;
    }

    sprintf(tbuf, "%c %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s ",
        mld,
        stime->tm_mday, stime->tm_mon + 1, stime->tm_year,
        stime->tm_hour, stime->tm_min, stime->tm_sec,
        pid,
        "loadnewquota",
        func);

    log << tbuf;

    memset(&tbuf, 0, 1000);

    va_start(arg_ptr, error_msgFormat);
    vsprintf(tbuf, error_msgFormat, arg_ptr);
    va_end(arg_ptr);

    log << tbuf;
    std::cout << tbuf << std::endl;

    memset(&tbuf, 0, 1000);
//#ifdef ESQL_C
//    sprintf(tbuf, " | SQL: %d/%d", SQLCODE, SQLISAM);
//#endif

//    std::cout << tbuf;
//    log << tbuf << std::endl;
    log << std::endl;
    log.close();
}

/****************************************************************************/
// --- inline functions
/****************************************************************************/
// trim from start (in place)
inline void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim start and end
inline void trim(std::string& s)
{
    rtrim(s);
    ltrim(s);
}

inline int convertStringToLong(std::string s, long& value, long def = 0)
{
    value = def;
    if (s.length() > 0)
    {
        try
        {
            value = std::stoi(s);
            return true;
        }
        catch (...)
        {
        }
    }
    return false;
}

void GetFilePathAndName(const std::string& strFullFileName, std::string& strPath, std::string& strFileName)
{
    // Find the last occurrence of the path separator
    size_t found = strFullFileName.find_last_of(g_strPathDel);
    if (found != std::string::npos)
    {
        strPath = strFullFileName.substr(0, found);
        strFileName = strFullFileName.substr(found + 1);
    }
    else  // No path separator found
    {
        strPath = "";
        strFileName = strFullFileName;
    }
}
#endif

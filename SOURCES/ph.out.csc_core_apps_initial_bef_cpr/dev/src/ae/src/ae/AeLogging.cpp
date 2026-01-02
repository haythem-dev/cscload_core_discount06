#include "stdafx.h"
#include "AeLogging.h"

CAeLogging::CAeLogging()
: m_PID(0)
{
    m_LoggingLevel = 0;
}

CAeLogging::~CAeLogging()
{
}

int CAeLogging::WriteLine(short traceLevel, const char* clazz, const char* method, const CString& line)
{
    if (traceLevel > GetLoggingLevel())
        return 0;
    assert(clazz);
    assert(method);

    CTime t = CTime::GetCurrentTime();

    CString l = line;
    CString logText;
    logText.Format("%02d:%02d:%02d %-2d %-10u %-45s %s\r\n"
        , t.GetHour()
        , t.GetMinute()
        , t.GetSecond()
        , traceLevel
        , getProcessID()
        , (CString(clazz) + "::" + method).GetString()
        , l.TrimRight().GetString()
    );

    CFile aelog;
    CFileException e;
    if (!aelog.Open(getFileName(), CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite, &e))
    {
        return e.m_cause;
    }
    aelog.SeekToEnd();
    aelog.Write(logText, logText.GetLength());
    aelog.Close();

    return 0;
}

const CString& CAeLogging::getFileName()
{
    if (m_FileName.IsEmpty())
    {
        CString logsDir;
        char* env = getenv("MARATHON_LOG_LOGSDIR");
        if (0 != env)
        {
            logsDir = env;
        }

        CString userName;
        env = getenv("USERNAME");
        if (0 != env)
        {
            userName = env;
        }

        CTime t = CTime::GetCurrentTime();
        m_FileName.Format("%s\\aa\\logging\\aelog.%04d%02d%02d.%s.%u.log",
            logsDir.GetString(),
            t.GetYear(),
            t.GetMonth(),
            t.GetDay(),
            userName.GetString(),
            getProcessID()
        );
    }

    return m_FileName;
}

DWORD CAeLogging::getProcessID()
{
    if (0 == m_PID)
    {
        m_PID = GetCurrentProcessId();
    }

    return m_PID;
}

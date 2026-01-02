#pragma once

/**
 *  @brief Klasse zum Loggen der CTI Commands.
 */

static enum TraceLevel
{
    Error = 1,
    Warning = 2, // includes Errors
    Info = 3, // includes Errors and Warnings
    Debug = 4 // includes Info Errors and Warnings
};

class CAeLogging
{
public:
    CAeLogging();
    virtual ~CAeLogging();

    void SetLoggingLevel(short s)   { m_LoggingLevel = s; };
    short GetLoggingLevel()         { return m_LoggingLevel; };
    virtual int WriteLine(short traceLevel, const char* clazz, const char* method, const CString& line);

protected:
    short m_LoggingLevel;

private:
    const CString& getFileName();
    DWORD getProcessID();

private:
    CString m_FileName;
    DWORD m_PID;
};

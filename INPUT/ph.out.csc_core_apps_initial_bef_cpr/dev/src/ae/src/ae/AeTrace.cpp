#include "stdafx.h"
#include "AeTrace.h"

extern "C"
{
    #include "allg.h"
}

CAeTrace::CAeTrace()
{
}

int CAeTrace::WriteTrace(const CString& urprog, const char* rufprog, const char* telegramm)
{
    CString msgText;
    CString tgm(telegramm);
    msgText.Format("WriteTrace: %s %s %s\n", urprog.GetString(), rufprog, tgm.TrimRight().GetString());
    TRACE(msgText);

#ifdef _DEBUG
    // TODO: remove debugging code
    if (AeGetApp()->m_ProCenter.GetAgentID().IsEmpty())
    {
        AeGetApp()->m_ProCenter.SetAgentID("2222");
    }
#endif

    if (!AeGetApp()->IsLogging())
        return 0;
    long datum = AllgGetDate();
    long uhrzeit = AllgGetTime();
    char filename[81];
    sprintf(filename, "D:\\Apps\\Marathon\\Logging\\logs\\PROD\\OE\\aetrace.%s.%s.%08d.log",
        AeGetApp()->m_ProCenter.GetNST().GetString(),
        AeGetApp()->m_ProCenter.GetAgentID().GetString(),
        datum);

    CString CAusgabe;
    CAusgabe.Format("%s %-30s %-30s %s\r\n",
        HHmmSSStringFromTimeLong(uhrzeit),
        urprog.GetString(),
        rufprog,
        tgm.TrimRight().GetString());

    CFile aelog;
    CFileException e;
    if (!aelog.Open(filename, CFile::modeNoTruncate|CFile::modeCreate|CFile::modeWrite, &e))
    {
        return e.m_cause;
    }

    aelog.SeekToEnd();
    aelog.Write(CAusgabe,CAusgabe.GetLength());
    aelog.Close();

    return 0;
}

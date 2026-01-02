// ppPCTime.cpp

#include "stdafx.h"
#include "ppTime.h"

//----- Function:GetCurrentTime ----------------------------------------------/

    ppString ppPCTime::GetCurrentDateTime(int iTime)
    {
        if (iTime == (TIME | DATE))
            return pGetTimeDate();
        if (iTime == TIME)
            return pGetTime();
        if (iTime == DATE)
            return pGetDate();

        return pGetTimeDate();
    }

//----- Private --------------------------------------------------------------/
//----- Function:GetTimeDate -------------------------------------------------/

    ppString ppPCTime::pGetTimeDate()
    {
        time_t ltime;
        _tzset();

        time(&ltime);
        ppString strTime = ctime(&ltime);
        return strTime.area(strTime.length() - 1);
    }

//----- Function:GetDate -----------------------------------------------------/

    ppString ppPCTime::pGetDate()
    {
        char tmpbuf[128];
        _tzset();

        ppString strTime = _strdate(tmpbuf);
        return strTime.area(strTime.length() - 1);
    }

//----- Function:GetTime -----------------------------------------------------/

    ppString ppPCTime::pGetTime()
    {
        char tmpbuf[128];
        _tzset();

        ppString strTime = _strtime(tmpbuf);
        return strTime.area(strTime.length() - 1);
    }

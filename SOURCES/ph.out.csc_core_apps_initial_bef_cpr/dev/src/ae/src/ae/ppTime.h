#pragma once

// ppTime.h

//!! don't use with ppDataTypes.h !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <ctime>

class ppPCTime
{
public:
    enum
    {
        TIME = 0x01,
        DATE = 0x02
    };
    ppString GetCurrentDateTime(int iTime = TIME | DATE);

private:
    ppString pGetTimeDate();
    ppString pGetDate();
    ppString pGetTime();
};

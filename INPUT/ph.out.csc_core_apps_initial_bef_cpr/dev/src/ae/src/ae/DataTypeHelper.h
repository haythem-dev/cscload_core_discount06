#pragma once

#include <sstream>
#include <iomanip>
#include <time.h>
#include <ctime>

class DataTypeHelper
{
public:
    DataTypeHelper();
    ~DataTypeHelper();

    /* Converting functions */
    static std::string toString(int value);
    static bool tryParse(const std::string value, long& result);
    static bool isNumber(const std::string value);
    static CString convertTimeToString(CTime timeCheck);
    static CString padString(CString data, int length, char filler);

    /* Checks if the input date is valid and in the correct format */
    static bool CheckDate(const CString txtCreaDate);

    /* Calculation functions */
    static CTime AddMinutesToTime(long hour, long minute, long addMinutes);
};

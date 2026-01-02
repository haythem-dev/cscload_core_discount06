#include "stdafx.h"
#include "DataTypeHelper.h"

DataTypeHelper::DataTypeHelper()
{
}

DataTypeHelper::~DataTypeHelper()
{
}

std::string DataTypeHelper::toString(int value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

bool DataTypeHelper::tryParse(const std::string value, long& result)
{
    std::istringstream ss(value);
    if ((ss>>result).fail())
    {
        return false;
    }
    return true;
}

bool DataTypeHelper::isNumber(const std::string value)
{
    long result = 0;
    std::istringstream ss(value);
    if ((ss >> result).fail())
    {
        return false;
    }
    return true;
}

bool DataTypeHelper::CheckDate(const CString txtCreaDate)
{
    std::string sub = txtCreaDate;
    long date = -1;
    if (sub.length() <= 0)
    {
        return true;    //use default '%'
    }
    else if (!DataTypeHelper::tryParse(sub, date) || sub.length() != 8)
    {
        return false;
    }

    int year = atoi(sub.substr(0, 4).c_str());
    int month = atoi(sub.substr(4, 2).c_str());
    int day = atoi(sub.substr(6, 2).c_str());

    struct tm timeinfo;
    memset(&timeinfo, 0, sizeof(timeinfo));
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;

    time_t res = mktime(&timeinfo);
    if (res == -1)
    {
        return false;
    }
    else
    {
        if (timeinfo.tm_year == year - 1900 &&
            timeinfo.tm_mon ==  month - 1 &&
            timeinfo.tm_mday == day)    //to prevent (Eg) 20120230 to be correct. mktime autoamtically corrects such dates.
        {
            return true;
        }
        return false;
    }
}

CTime DataTypeHelper::AddMinutesToTime(long hour, long minute, long addMinutes)
{
    CTime consTime(2013, 9, 18, hour, minute, 0); //we only use hour and minute, the rest doesnt concern us
    CTimeSpan kippTime(0, 0, addMinutes, 0);
    CTime timeCheck = consTime + kippTime;

    return timeCheck;
}

CString DataTypeHelper::convertTimeToString(CTime timeCheck)
{
    CString strTimeCheck;
    strTimeCheck.Format("%0.2ld%0.2ld", timeCheck.GetHour(), timeCheck.GetMinute());
    return strTimeCheck;
}

CString DataTypeHelper::padString(CString data, int length, char filler)
{
    CString strTimeCheck;
    std::stringstream oss;
    oss << std::setw(length) << std::setfill(filler) << data;
    strTimeCheck = oss.str().c_str();
    return strTimeCheck;
}

#pragma once

class OrderPeriodData
{
public:
    OrderPeriodData();
    ~OrderPeriodData();
    OrderPeriodData(const OrderPeriodData& data);
    OrderPeriodData& operator=(const OrderPeriodData& data);

    void addConsTime(CString consTime_);
    void setIdfNo(CString idfNo_);
    void setTourID(CString tourID_);
    void setWeekDay(CString weekday_);
    void setWeekDayAsInt(int weekday_);
    void setOrderPeriodTimeID(int id);
    void setFromTime(CString fromTime_);
    void setToTime(CString toTime_);
    void setBranchNo(short branchNo_);
    void setMainTime(CString mainTime_);
    void setID(int ID);

    CString getConsTime(int index);
    CString getIdfNo();
    CString getTourID();
    CString getWeekDay();
    int getWeekDayAsInt();
    int getOrderPeriodTimeID();
    CString getFromTime();
    CString getToTime();
    int getConsTimeCount();
    short getBranchNo();
    CString getMainTime();
    int getID();

private:
    int ID;
    int orderPeriodTimeID;
    CString idfNo;
    CString tourID;
    CString weekDay;
    int weekDayAsInt;
    CStringArray consTime;
    CString fromTime;
    CString toTime;
    short branchNo;
    CString mainTime;
};

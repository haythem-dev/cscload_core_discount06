#include "stdafx.h"
#include "orderperioddata.h"

OrderPeriodData::OrderPeriodData()
{
}

OrderPeriodData::~OrderPeriodData()
{
}

OrderPeriodData::OrderPeriodData(const OrderPeriodData& data)
{
    this->orderPeriodTimeID = data.orderPeriodTimeID;
    this->idfNo = data.idfNo;
    this->tourID = data.tourID;
    this->weekDay = data.weekDay;
    this->weekDayAsInt = data.weekDayAsInt;
    this->fromTime = data.fromTime;
    this->toTime = data.toTime;
    this->branchNo = data.branchNo;
    this->mainTime = data.mainTime;
    this->ID = data.ID;

    for (int i = 0; i < data.consTime.GetSize(); i++)
    {
        consTime.Add(data.consTime.GetAt(i));
    }
}

OrderPeriodData& OrderPeriodData::operator=(const OrderPeriodData& data)
{
    this->orderPeriodTimeID = data.orderPeriodTimeID;
    this->idfNo = data.idfNo;
    this->tourID = data.tourID;
    this->weekDay = data.weekDay;
    this->weekDayAsInt = data.weekDayAsInt;
    this->fromTime = data.fromTime;
    this->toTime = data.toTime;
    this->branchNo = data.branchNo;
    this->mainTime = data.mainTime;
    this->ID = data.ID;

    for (int i = 0; i < data.consTime.GetSize(); i++)
    {
        consTime.Add(data.consTime.GetAt(i));
    }

    return *this;
}

void OrderPeriodData::addConsTime(CString consTime_)
{
    this->consTime.Add(consTime_);
}

void OrderPeriodData::setIdfNo(CString idfNo_)
{
    this->idfNo = idfNo_;
}

void OrderPeriodData::setTourID(CString tourID_)
{
    this->tourID = tourID_;
}

void OrderPeriodData::setWeekDay(CString weekDay_)
{
    this->weekDay = weekDay_;
}

void OrderPeriodData::setWeekDayAsInt(int weekDay_)
{
    this->weekDayAsInt = weekDay_;
}

void OrderPeriodData::setOrderPeriodTimeID(int id)
{
    this->orderPeriodTimeID=id;
}

void OrderPeriodData::setFromTime(CString fromTime_)
{
    this->fromTime = fromTime_;
}
void OrderPeriodData::setToTime(CString toTime_)
{
    this->toTime = toTime_;
}

void OrderPeriodData::setBranchNo(short branchNo_)
{
    this->branchNo = branchNo_;
}

void OrderPeriodData::setMainTime(CString mainTime_)
{
    this->mainTime = mainTime_;
}

void OrderPeriodData::setID(int mainID)
{
    this->ID = mainID;
}

CString OrderPeriodData::getConsTime(int index)
{
    return this->consTime[index];
}

CString OrderPeriodData::getIdfNo()
{
    return this->idfNo;
}

CString OrderPeriodData::getTourID()
{
    return this->tourID;
}

CString OrderPeriodData::getWeekDay()
{
    return this->weekDay;
}

int OrderPeriodData::getWeekDayAsInt()
{
    return this->weekDayAsInt;
}

int OrderPeriodData::getOrderPeriodTimeID()
{
    return this->orderPeriodTimeID;
}

CString OrderPeriodData::getFromTime()
{
    return this->fromTime;
}

CString OrderPeriodData::getToTime()
{
    return this->toTime;
}

int OrderPeriodData::getConsTimeCount()
{
    return this->consTime.GetCount();
}

short OrderPeriodData::getBranchNo()
{
    return this->branchNo;
}

CString OrderPeriodData::getMainTime()
{
    return this->mainTime;
}

int OrderPeriodData::getID()
{
    return this->ID;
}

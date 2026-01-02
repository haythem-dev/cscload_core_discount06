#include "stdafx.h"
#include "weekday.h"

Weekday::Weekday()
{
}

Weekday::Weekday(WEEKDAYS weekday, bool active, int ID)
{
    this->weekday = weekday;
    this->active = active;
    this->ID = ID;
}

Weekday::~Weekday()
{
}

const bool Weekday::operator==(const Weekday& wd) const
{
    return ((weekday == wd.weekday) && (active == wd.active));
}

const bool Weekday::operator!=(const Weekday& wd) const
{
    return !(*this == wd);
}

Weekday::WEEKDAYS Weekday::GetWeekday()
{
    return this->weekday;
}

bool Weekday::IsActive()
{
    return this->active;
}

int Weekday::GetID()
{
    return this->ID;
}

void Weekday::SetWeekday(WEEKDAYS weekday_)
{
    this->weekday = weekday_;
}

void Weekday::SetActive(bool active_)
{
    this->active = active_;
}

void Weekday::SetID(int id)
{
    this->ID = id;
}
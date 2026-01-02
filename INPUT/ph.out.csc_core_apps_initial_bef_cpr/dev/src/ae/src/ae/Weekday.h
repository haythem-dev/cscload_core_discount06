#pragma once

class Weekday
{
public:
    enum WEEKDAYS { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };

    Weekday();
    Weekday(WEEKDAYS weekday, bool active, int ID);
    ~Weekday();
    const bool operator==(const Weekday& wd) const;
    const bool operator!=(const Weekday& wd) const;

    WEEKDAYS GetWeekday();
    bool IsActive();
    int GetID();

    void SetWeekday(WEEKDAYS weekday_);
    void SetActive(bool active_);
    void SetID(int id);

private:
    WEEKDAYS weekday;
    bool active;
    int ID;
};

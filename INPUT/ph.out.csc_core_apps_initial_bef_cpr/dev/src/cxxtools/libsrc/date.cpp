/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

A date class with range from 1.1.1 to ?.

REVISION HISTORY

18 Sep 1995 V1.00 REV 00 written by Carsten Krabiell.

*/
/*  $History: DATE.CPP $ */
/*  */
/* *****************  Version 7  ***************** */
/* User: Ck           Date: 6.02.97    Time: 15:32 */
/* Updated in $/cxxtools/src */
/* We only add  months to this, if months > 0. */
/*  */
/* *****************  Version 6  ***************** */
/* User: Ck           Date: 6.02.97    Time: 14:59 */
/* Updated in $/cxxtools/src */
/* Changed AddMonth : when we add one month to 31.3.1997 the resulting day */
/* must be 30.4.1997. */
/*  */
/* *****************  Version 5  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:05 */
/* Updated in $/cxxtools/src */
/* Final release. */
/* *********************************************** */

#include "date.hpp"

const long cDAYSINMONTH[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const long cDAYSINYEAR[]  = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

// Following constants in days.
const long c400YEARS = 146097;
const long c100YEARS =  36524;
const long c4YEARS   =   1461;
const long c1YEARS   =    365;


// ---------------------------------------------------------------------
// Init nDate and nTime. nTime with midnight.
// ---------------------------------------------------------------------
nDate::nDate(int year, int mon, int day) : nTime(year, mon, day, 0, 0, 0)
{
   absday = CalcAbsday((long)year, (long)mon, (long)day);
}


// ---------------------------------------------------------------------
// Init nDate and nTime. nTime with midnight.
// ---------------------------------------------------------------------
nDate::nDate(long year, long mon, long day)
      : nTime((int)year, (int)mon, (int)day, 0, 0, 0)
{
   absday = CalcAbsday(year, mon, day);
}


// ---------------------------------------------------------------------
// Init nDate and nTime from long. nTime with midnight.
// ---------------------------------------------------------------------
nDate::nDate(long yyyymmdd)
 : nTime((int)(yyyymmdd/10000),(int)((yyyymmdd%10000)/100),(int)(yyyymmdd%100),0,0,0)
{
   absday = CalcAbsday(yyyymmdd / 10000,
                       (yyyymmdd % 10000)/100,
                       yyyymmdd % 100         );
}


// ---------------------------------------------------------------------
// Type conversion.
// ---------------------------------------------------------------------
nDate::nDate(const nTime& tim) : nTime(tim.GetSecs())
{
   if (tim.IsValid())
      InitDate();

   else
      absday = -1;
}


// ---------------------------------------------------------------------
// Calc. 'absday' from 'struct tm'. nTime is init., so 'secs' is valid.
// ---------------------------------------------------------------------
void nDate::InitDate(struct tm* tmsecs)
{
   if (tmsecs == 0)
   {
      // get local time
      tmsecs = localtime(&secs);
   }

   // convert into absday
   absday = CalcAbsday((long)(1900 + tmsecs->tm_year),
                       (long)(tmsecs->tm_mon+1),
                       (long)(tmsecs->tm_mday)        );
}


// ---------------------------------------------------------------------
// The values are converted to one long containing the days since 1.1.1.
// Because the leap days, 'year'-1 must divide into 400years and
// 100years, and into 4years and 1year pieces.
// The rest of 'year' is the day since 1.1.'year'.
// ---------------------------------------------------------------------
long nDate::CalcAbsday(long year, long mon, long day) const
{
   if (!DateIsCorrect(year, mon, day))
      return -1;

   else
   {
      long century = year / 100;
      long rest = year % 100 - 1;
      long days = 0;
      days += (century/4)     * c400YEARS;
      days += (century%4)     * c100YEARS;
      days += (rest/4)        * c4YEARS;
      days += (rest%4)        * c1YEARS;
      days += DayOfYear(year, mon, day) - 1;

      return days;
   }
}


// ---------------------------------------------------------------------
// Convert back from 'absday' into date.
// Same procedure as in CalcAbsday.
// ---------------------------------------------------------------------
void nDate::CalcDate(long& year, long& month, long& day) const
{
   if (absday < 0)
   {
      year = 0;
      month = 0;
      day = 0;
   }
   else if (nTime::IsValid())
   {
      struct tm tim = *localtime(&secs);

      year  = (long)tim.tm_year + 1900;
      month = (long)tim.tm_mon + 1;
      day   = (long)tim.tm_mday;
   }
   else
   {
      // Get 400years and ... pieces.
      long c1 = absday / c400YEARS,
           c2 = (absday % c400YEARS) / c100YEARS;
      long days = (absday - c1) % c100YEARS;
      long d1 = days / c4YEARS,
           d2 = (days % c4YEARS) / c1YEARS;

      // Calculate the year.
      year = c1 * 400 + c2 * 100 + d1 * 4 + d2 + 1;

      // Get days within year.
      days -= d1*c4YEARS + d2*c1YEARS - 1;

      assert(days <= 365);

      // Corrects the date if leap year and days >= 28.feb
      long correct = YearIsLeapYear((int)year) && days >= cDAYSINYEAR[2] + 1 ?
                     1L : 0L;

      // Find month and begin with january.
      month = 1;
      while (days > cDAYSINYEAR[month] + correct)
         ++month;

      // Get day in month.
      day = days - cDAYSINYEAR[month-1];
   }
}


// ---------------------------------------------------------------------
// Get the year. But the whole date must be calculated.
// ---------------------------------------------------------------------
long nDate::GetYear() const
{
   long year, month, day;
   CalcDate(year, month, day);

   return year;
}


// ---------------------------------------------------------------------
// Get the month. But the whole date must be calculated.
// ---------------------------------------------------------------------
long nDate::GetMonth() const
{
   long year, month, day;
   CalcDate(year, month, day);

   return month;
}


// ---------------------------------------------------------------------
// Get the day. But the whole date must be calculated.
// ---------------------------------------------------------------------
long nDate::GetDay() const
{
   long year, month, day;
   CalcDate(year, month, day);

   return day;
}


// ---------------------------------------------------------------------
// Get the day of year. But the whole date must be calculated.
// ---------------------------------------------------------------------
long nDate::GetDayOfYear() const
{
   long year, month, day;
   CalcDate(year, month, day);

   return DayOfYear(year, month, day);
}


// ---------------------------------------------------------------------
// The date is correct, if year > 0 and the day is valid for the month.
// ---------------------------------------------------------------------
bool nDate::DateIsCorrect(long year, long mon, long day) const
{
   // Is 'month' and 'year' valid ?
   if (mon < 1 || mon > 12 || year <= 0)
      return false;

   else
   {
      // Is 'day' valid ?
      if (day <= cDAYSINMONTH[mon-1])
         return true;

      // Or is it 29.2 and is leap day.
      else if (mon == 2 && day == 29 && YearIsLeapYear((int)year))
         return true;

      else
         return false;
   }
}
// ---------------------------------------------------------------------
// The date is correct, if year > 0 and the day is valid for the month.
// ---------------------------------------------------------------------
long nDate::GetDaysOfMonth(long mon) const
{
    long days = 0;
   // Is 'month'  valid ?
   if (mon < 1 || mon > 12 )
      return days;

   days = cDAYSINMONTH[mon-1];
   return days;
}


// ---------------------------------------------------------------------
// Calculate the day within 'year'
// ---------------------------------------------------------------------
long nDate::DayOfYear(long year, long month, long day) const
{
   long sum = 0;  // days within year

   // leap day ?
   if (month > 2 && YearIsLeapYear((int)year))
      ++sum;

   // From 1.1 to 1.month.
   sum += cDAYSINYEAR[month-1];

   //
   sum += day;

   return sum;
}


// ---------------------------------------------------------------------
// Assignment from nDate.
// ---------------------------------------------------------------------
nDate& nDate::operator=(const nDate& da)
{
   absday = da.absday;
   secs = da.secs;

   return *this;
}


// ---------------------------------------------------------------------
// Assignment from nTime.
// Copy 'time_t sec' and init. 'this'.
// ---------------------------------------------------------------------
nDate& nDate::operator=(const nTime& tim)
{
   secs = tim.GetSecs();

   if (tim.IsValid())
      InitDate();

   else
      absday = -1;

   return *this;
}


// ---------------------------------------------------------------------
// Increment 'this' by 'days'.
// Remark : nTime has smaller range than nDate. So if 'absday' is into
//          the range of nTime, it can be new calculated.
// ---------------------------------------------------------------------
nDate& nDate::operator+=(long days)
{
   if (days != 0)
   {
      absday += days;

      // Is 'secs' valid ?
      if (nTime::IsValid())
      {
         time_t newsecs = secs + (time_t)days * 86400;

         // Is the new value valid ?
         if ((days > 0 && secs < newsecs) ||
             (days < 0 && 0 <= newsecs && newsecs < secs) )
            secs = newsecs;

         else
            secs = -1;
      }
      else
      {
         // Recalc. date.
         long year, month, day;
         CalcDate(year, month, day);

         // Is nDate within range of nTime ?
         if (ProofTime((int)year, (int)month, (int)day,0,0,0))
            secs = CalcSeconds((int)year,(int)month,(int)day,0,0,0);

         else
            secs = -1;
      }
   }

   return *this;
}


// ---------------------------------------------------------------------
// Convert date into long.
// ---------------------------------------------------------------------
long nDate::GetYYYYMMDD() const
{
   long year, month, day;

   CalcDate(year, month, day);

   return year * 10000 + month * 100 + day;
}


// ---------------------------------------------------------------------
// Interface to call nTime::GetTimeWithFormat with correct values.
// If 'absday' is out of range of nTime, 'struct tm' must be filled with
// date of 'this'.
// ---------------------------------------------------------------------
void nDate::GetTimeWithFormat(nString& format, const nZone& zone) const
{
   struct tm tim;

   if (nTime::IsValid())
   {
      tim = *localtime(&secs);

      nTime::GetTimeWithFormat(format, tim, zone);
   }
   else
   {
      FillTM(tim);

      nTime::GetTimeWithFormat(format, tim, zone);
   }
}

// ---------------------------------------------------------------------
// Fill 'tim' with date from 'absday'.
// This procedure is called if 'secs' isn't valid and GetTimeWithFormat
// should be called. So 'tim' is filled like 'localtime' would do it :
// month - 1, year - 1900, and so on.
// ---------------------------------------------------------------------
void nDate::FillTM(struct tm& tim) const
{
   long year, month, day, yday;
   CalcDate(year, month, day);
   yday = DayOfYear(year, month, day);

   tim.tm_year  = (int)(year - 1900);
   tim.tm_mon   = (int)(month - 1);
   tim.tm_mday  = (int)day;
   tim.tm_yday  = (int)(yday - 1);
   tim.tm_wday  = (int)GetDayOfWeek();
   tim.tm_hour  = 0;
   tim.tm_min   = 0;
   tim.tm_sec   = 0;
   tim.tm_isdst = 1;
}

/*----------------------------------------------------------------------------*/
/*  Add 'n' months to self.                                                   */
/*----------------------------------------------------------------------------*/
const nDate&
nDate :: AddMonth
(
    const int   months
)
{
    if (months > 0)
    {
        int   n = months;
        long  day = GetDay()-1;
        long  old_month = GetMonth();
        *(this) -= (day);

        for (int i = (int)GetMonth()-1; n > 0; n--, i++)
        {
           if ( i > 11 )
              i = 0;
           *(this) += ( i == 1 && IsLeapYear() ) ? (cDAYSINMONTH[i]) +1
                                                 : cDAYSINMONTH[i];
        }

        *(this) += (day);

        // Make correction if month overflow
        if (old_month + months - ((old_month + months - 1) / 12) * 12 < GetMonth())
        {
            long current_month = GetMonth();

            do
            {
                // Increment one day may change the month
                --(*this);
            }
            while (current_month == GetMonth());
        }
    }

    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Get the difference between two dates.                                     */
/* Like a gready algorithm the dates are subtracted and corrected if an under-*/
/* flow occurs (for month and/or day).                                        */
/*----------------------------------------------------------------------------*/
void nDate::GetDiff(const nDate& date, long& year, long& month, long& day) const
{
    if (IsValid() && date.IsValid())
    {
        if (*this > date)
        {
            date.GetDiff(*this, year, month, day);
        }
        else
        {
            date.CalcDate(year, month, day);
            bool leapy = YearIsLeapYear((int) year);

            long tyear, tmon, tday;
            CalcDate(tyear, tmon, tday);

            year -= tyear;
            month -= tmon;
            day -= tday;

            if (month < 0)
            {
                --year;
                month += 12;
            }
            if (day < 0)
            {
                --month;
                day += cDAYSINMONTH[(month+tmon-1)%12];
                if (((month+tmon)%12) == 2 && leapy)
                    ++day;
            }
        }
    }
}


/*----------------------------------------------------------------------------*/
/*  Calculates the date (YYYYMMDD) of Easter Sunday in the specified year.    */
/*  For further informations see to the used algorithm see:                   */
/*  Knuth: The art of computer programming, vol. 1, p. 155.                   */
/*----------------------------------------------------------------------------*/
long
nDate :: GetEasterYYYYMMDD
(
    long year
)
{
    long day, month;
    long g, c, x, z, d, e, n;

    g = year % 19 + 1;                  // Golden number
    c = year / 100 + 1;                 // Century
    x = (3*c) / 4 - 12;                 // Corrections
    z = (8*c+5)/25 -5;
    d = (5*year)/4 -x -10;              // Find Sunday
    e = (11*g +20 + z -x) % 30;         // Epact
    if (e < 0)   // Modulus correction
        e += 30;
    if ( (25 == e && g > 11) || 24 == e)
        ++e;
    n = 44 - e;                         // Find full moon
    if (n < 21)
        n = n + 30;
    n = n + 7 - ((d+n) % 7);            // Advance to Sunday

    if (n > 31)                         // Easter sunday in April
    {
        month = 4;
        day = n - 31;
    }
    else                                // Easter sunday in March
    {
        month = 3;
        day = n;
    }

    return year*10000 + month*100 + day;
}


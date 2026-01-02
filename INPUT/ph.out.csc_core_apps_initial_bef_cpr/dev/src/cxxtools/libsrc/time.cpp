#include "time.hpp"
#ifdef unix
#include <sys/time.h>
#else
#include <sys/timeb.h>
#endif

const int cDAYSINMONTH[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int cDAYSINYEAR[]  = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

// -------------------------------------------------------------------------------
// Init. the data member 'sec' and 'msecs' with ftime function or with 'struct tm* timesec'.
// The values of 'timesec' are converted to 'time_t secs' (like mktime ?).
// -------------------------------------------------------------------------------
//#ifdef unix
//    extern "C" int gettimeofday(struct timeval*);
//#endif
void nTime::InitTime(struct tm* timesec)
{
   if (timesec == 0)
   {
      // get the current time

#ifdef unix

      struct timeval now;
      gettimeofday(&now,NULL);

      secs = now.tv_sec;         // get the time in seconds
      msecs = now.tv_usec/1000;  // and fraction of a second in milliseconds

#else

      struct timeb now;
      ftime(&now);

      secs = now.time;        // get the time in seconds
      msecs = now.millitm;    // and fraction of a second in milliseconds

#endif

   }
   else
   {
      // convert back
      struct   tm savtime;
      savtime = *timesec;        // save tm structure. because localtime use a single statically
                           // allocated tm structure for the conversion.
                           // Each call destroys the result of the previous call!

      if (!ProofTime(timesec->tm_year + 1900, timesec->tm_mon + 1, timesec->tm_mday,
                     timesec->tm_hour, timesec->tm_min, timesec->tm_sec))
         secs = -1;
      else
      {
         *timesec = savtime;     // restore tm structure

         secs = CalcSeconds(timesec->tm_year + 1900, timesec->tm_mon + 1, timesec->tm_mday,
                     timesec->tm_hour, timesec->tm_min, timesec->tm_sec);
         msecs = 0;
      }
   }
}


// -------------------------------------------------------------------------------
// The values are converted to 'time_t secs'.
// -------------------------------------------------------------------------------
nTime::nTime(int year, int month, int day, int hour, int min, int sec)
{
   if (!ProofTime(year, month, day, hour, min, sec))
      secs = msecs = -1;
   else
   {
      secs = CalcSeconds(year, month, day, hour, min, sec);
      msecs = 0;
   }
}


// -------------------------------------------------------------------------------
// The values are converted to 'time_t secs'.
// -------------------------------------------------------------------------------
nTime::nTime(int year, int month, int day, int hour, int min, int sec, int msec)
{
   if (!ProofTime(year, month, day, hour, min, sec, msec))
      secs = msecs = -1;
   else
   {
      secs = CalcSeconds(year, month, day, hour, min, sec);
      msecs = msec;
   }
}


// -------------------------------------------------------------------------------
// Assignment
// -------------------------------------------------------------------------------
nTime& nTime::operator= (const nTime& tim)
{
   secs = tim.secs;
   msecs = tim.msecs;

   return *this;
}


// -------------------------------------------------------------------------------
// Assignment with 'seconds' (from previous time function call ?).
// -------------------------------------------------------------------------------
nTime& nTime::operator= (time_t seconds)
{
   secs = seconds;
   msecs = 0;

   return *this;
}


// -------------------------------------------------------------------------------
// Add seconds to this.
// -------------------------------------------------------------------------------
nTime& nTime::operator+= (time_t seconds)
{
   secs += seconds;

   return *this;
}


// -------------------------------------------------------------------------------
// Add seconds to temporary nTime.
// -------------------------------------------------------------------------------
const nTime nTime::add (long seconds) const
{
   nTime temp = *this;

   temp.operator+= (seconds);

   return temp;
}


// -------------------------------------------------------------------------------
// Proof if all values are in guilty ranges.
// -------------------------------------------------------------------------------
bool nTime::ProofTime(int year, int month, int day,
                       int hour, int min,   int sec , int msec) const
{
   if ( month < 1 || month > 12 ||
      !IsValidDay(year, month, day) ||
      hour < 0 || hour > 23 ||
      min < 0 || min > 59 ||
      sec < 0 || sec > 59 ||
      msec < 0 || msec > 999 )
   {
      return false;
   }
   else
   {
     return true;
   }
}


// -------------------------------------------------------------------------------
// Proof if 'tim1' <= 'tim2'.
// -------------------------------------------------------------------------------
bool nTime::LessOrEqual(const struct tm& tim1, const struct tm& tim2) const
{
   if (tim1.tm_year < tim2.tm_year)
      return true;

   else if (tim1.tm_year > tim2.tm_year)
      return false;

   // tim1.tm_year == tim2.tm_year
   else if (tim1.tm_mon + 1 < tim2.tm_mon)
      return true;

   else if (tim1.tm_mon + 1 > tim2.tm_mon)
      return false;

   // tim1.tm_mon == tim2.tm_mon
   else if (tim1.tm_mday < tim2.tm_mday)
      return true;

   else if (tim1.tm_mday > tim2.tm_mday)
      return false;

   // tim1.tm_mday == tim2.tm_mday
   else if (tim1.tm_hour < tim2.tm_hour)
      return true;

   else if (tim1.tm_hour > tim2.tm_hour)
      return false;

   // tim1.tm_hour == tim2.tm_hour
   else if (tim1.tm_min < tim2.tm_min)
      return true;

   else if (tim1.tm_min > tim2.tm_min)
      return false;

   // tim1.tm_min == tim2.tm_min
   else if (tim1.tm_sec < tim2.tm_sec)
      return true;

   else if (tim1.tm_sec > tim2.tm_sec)
      return false;

   else
      return true;
}


// -------------------------------------------------------------------------------
// Proof if 'day' is in guilty range.
// -------------------------------------------------------------------------------
bool nTime::IsValidDay(int year, int mon, int day) const
{
   if (mon < 1 || mon > 12)
      return false;

   else
   {
      if (day <= cDAYSINMONTH[mon-1])
         return true;

      else if (mon == 2 && day == 29 && YearIsLeapYear(year))
         return true;

      else
         return false;
   }
}


// -------------------------------------------------------------------------------
// Calculate the seconds since time zero (from localtime).
//    - Get the leap days from time zero to 'year'
//    - and the difference 'delta'.
//    - Get the difference of the two dates in days (without leap days).
//    - Get (time since midnight) minus (time since midnight of time zero)
//    - Correct the values if one is negativ.
//    - Calculate the seconds with the days and the time.
//    - Correct seconds if daylight saving time is observed.
// -------------------------------------------------------------------------------
time_t nTime::CalcSeconds(int year, int month, int day,
                          int hour, int min,   int sec) const
{
#ifdef WIN32
	struct tm tim;
	tim.tm_year=year-1900;
	tim.tm_mon=month;
	tim.tm_mday=day;
	tim.tm_hour=hour;
	tim.tm_min=min;
	tim.tm_sec=sec;
	return mktime(&tim);
#else // so gehts natürlich auch
   time_t seconds = 0,
          sum = 0;                  // Seconds since zero.
   tm tim = *localtime(&seconds);   // Reference time zero.
   int delta;                       // Difference of the years.

   // Calculate the leapdays
   for (delta = 0; 1900 + tim.tm_year + delta < year; ++delta)
   {
      if (YearIsLeapYear(1900 + tim.tm_year + delta))
         sum += 86400;
   }

   // Is there a leapday in 'year' ?
   if (month > 2 && YearIsLeapYear(year))
      sum += 86400;

   // Days since time zero.
   long sumdays = delta*365 +
                  cDAYSINYEAR[month-1] + day - (tim.tm_yday+1);

   // Get time minus reference time.
   hour -= tim.tm_hour;
   min -= tim.tm_min;
   sec -= tim.tm_sec;

   // Correct the values if one is negativ.
   if (sec < 0)
   {
      sec += 60;
      --min;
   }
   if (min < 0)
   {
      min += 60;
      --hour;
   }
   if (hour < 0)
   {
      hour += 24;
      --sumdays;
   }

   // Get final result.
   sum += (((sumdays)*24+hour)*60+min)*60+sec;

   // Assume if dst is set difference is 1 hour
   assert(localtime(&sum) != 0);
   if (localtime(&sum)->tm_isdst > 0)
      sum -= 3600;

   return sum;
#endif
}


// -------------------------------------------------------------------------------
// Convert 'format'. (see header file)
// -------------------------------------------------------------------------------
void nTime::GetTimeWithFormat(nString& format, struct tm& tim, const nZone& zone) const
{
   if (&tim != 0)
   {
      // 'format' contains '%' ?
      size_t pos = format.FindChar('%');

      // Replace '%.'
      while (pos < format.Length())
      {
         switch (format[pos+1])
         {
            // abbreviated week day name
            case 'a' : format(pos,2) = zone.GetAbbrWeekdayName(tim.tm_wday);
                       break;

            // full week day name
            case 'A' : format(pos,2) = zone.GetWeekdayName(tim.tm_wday);
                       break;

            // abbreviated month name
            case 'b' : format(pos,2) = zone.GetAbbrMonthName(tim.tm_mon+1);
                       break;

            // full month name
            case 'B' : format(pos,2) = zone.GetMonthName(tim.tm_mon+1);
                       break;

            // day of month with leading blanks
            case 'e' : {
                          int day = tim.tm_mday;
                          format[pos] = day/10 > 0 ? (char)(day/10+'0') : ' ';
                          format[pos+1] = (char)(day%10+'0');
                          break;
                       }

            // day of month with leading zero
            case 'd' : {
                          int day = tim.tm_mday;
                          format[pos] = (char)(day/10+'0');
                          format[pos+1] = (char)(day%10+'0');
                          break;
                       }

            // hours (0-23) with leading zero
            case 'H' : {
                          int hour = tim.tm_hour;
                          format[pos] = (char)(hour/10+'0');
                          format[pos+1] = (char)(hour%10+'0');
                          break;
                       }

            // hours (0-12) with leading zero
            case 'I' : {
                          int hour = tim.tm_hour;
                          hour -= hour > 12 ? 12 : 0;
                          format[pos] = (char)(hour/10+'0');
                          format[pos+1] = (char)(hour%10+'0');
                          break;
                       }

            // day of year (1-366) with leading zero
            case 'j' : {
                          int day = tim.tm_yday + 1;
                          format(pos,2) = "000";
                          format[pos] = (char)(day/100+'0');
                          format[pos+1] = (char)((day%100)/10+'0');
                          format[pos+2] = (char)(day%10+'0');
                          break;
                       }

            // month (1-12) with leading zero
            case 'm' : {
                          int month = tim.tm_mon + 1;
                          format[pos] = (char)(month/10+'0');
                          format[pos+1] = (char)(month%10+'0');
                          break;
                       }

            // minutes (0-59) with leading zero
            case 'M' : {
                          int min = tim.tm_min;
                          format[pos] = (char)(min/10+'0');
                          format[pos+1] = (char)(min%10+'0');
                          break;
                       }

            // AM/PM indicator
            case 'p' : {
                          format(pos,2) = tim.tm_hour < 12 ? "AM" : "PM";
                          break;
                       }

            // seconds (0-59) with leading zero
            case 'S' : {
                          int sec = tim.tm_sec;
                          format[pos] = (char)(sec/10+'0');
                          format[pos+1] = (char)(sec%10+'0');
                          break;
                       }

            // milliseconds (0-999) with leading zero
            case 's' : {
                          format(pos,2) = "000";
                          format[pos] = (char)(msecs/100+'0');
                          format[pos+1] = (char)((msecs%100)/10+'0');
                          format[pos+2] = (char)(msecs%10+'0');
                          break;
                  }

            // weekday as number (0-6, 0 : sunday, ...)
            case 'w' : {
                          format(pos,2) = (char)(tim.tm_wday + '0');
                          break;
                       }

            // years without century (0-99) with leading zero
            case 'y' : {
                          int year = (tim.tm_year + 1900)%100;
                          format[pos] = (char)(year/10+'0');
                          format[pos+1] = (char)(year%10+'0');
                          break;
                       }

            // week of year start with sunday
            case 'U' : {
                          int week = tim.tm_yday + 1 - tim.tm_wday;
                          week = (week + 7) / 7;
                          format[pos] = (char)(week/10+'0');
                          format[pos+1] = (char)(week%10+'0');
                          break;
                       }

            // week of year start with monday
            case 'W' : {
                          int week = (tim.tm_yday + 1 - ((tim.tm_wday + 6) % 7) + 7) / 7;
                          format[pos] = (char)(week/10+'0');
                          format[pos+1] = (char)(week%10+'0');
                          break;
                       }

            // years with leading zero and four digits
            case 'Y' : {
                          int year = tim.tm_year + 1900;
                          format(pos,2) = "0000";
                          format[pos] = (char)(year/1000 + '0');
                          format[pos+1] = (char)((year%1000)/100 + '0');
                          format[pos+2] = (char)((year%100)/10 + '0');
                          format[pos+3] = (char)(year%10 + '0');
                          break;
                       }

            // %%
            case '%' : format(pos,2) = "%";
                       break;

            // short for "%a %b %e %H:%M:%S %Y"
            case 'C' : {
                          nString str = "%a %b %e %H:%M:%S %Y";
                          GetTimeWithFormat(str, tim, zone);
                          format(pos,2) = str;
                          break;
                       }

            // short for "%x %X"
            case 'c' : {
                          nString str = "%x %X";
                          GetTimeWithFormat(str, tim, zone);
                          format(pos,2) = str;
                          break;
                       }

            // short for zone.local[21]
            case 'x' : {
                          nString str = zone.GetLocalDateFormat();
                          GetTimeWithFormat(str, tim, zone);
                          format(pos,2) = str;
                          break;
                       }

            // short for "%H:%M:%S"
            case 'X' : {
                          nString str = "%H:%M:%S";
                          GetTimeWithFormat(str, tim, zone);
                          format(pos,2) = str;
                          break;
                       }

            default  : ++pos;
                       break;
         }

         // Next format.
         pos = format.FindChar('%', pos);
      }
   }
}

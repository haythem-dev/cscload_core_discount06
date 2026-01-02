#ifndef NTIME_INC
#define NTIME_INC
#ifndef NZONE_INC
    #include "zone.hpp"
#endif
#include <time.h>

/*@DS --------------------------------------------------------------------------
NAME
   nTime - A time class depending on c-functions ftime and localtime.

SYNOPSIS
   include "time.hpp"
   nTime time;

DESCRIPTION
   Class nTime has the functionality of localtime and a few other functions.
   Because of localtime the range of this class is constrained to the
   definition of type time_t. (At this moment, day light saving time isn't
   implemented.)

   'localtime' is the basic function to get the time, because it has least bugs
   in it and is ANSI/UNIX standard.

   You can get the time as a nString by function GetTimeWithFormat.
   This function has 2 parameters : 'nString format' and 'const nZone& zone'.

      'zone' can be GERMANLOCALS (defined in zone.hpp).

      'format' is an in/out parameter. It contains formats like in printf and
      strftime. The formats are :

       * %a : abbreviated week day name
       * %A : full week day name
       * %b : abbreviated month name
       * %B : full month name
         %e : day of month (as decimal) with leading blanks
         %d : day of month (as decimal) with leading zero
         %H : hours (0-23) with leading zero
         %I : hours (0-12) with leading zero
         %j : day of year (1-366) with leading zero
         %m : month (1-12) with leading zero
         %M : minutes (0-59) with leading zero
         %p : AM/PM indicator
         %S : seconds (0-59) with leading zero
         %s : milliseconds (0-999) with leading zero
         %w : weekday as number (0-6, 0 : sunday, ...)
         %y : years without century (0-99) with leading zero
         %Y : years with leading zero (four digits)
         %U : week of year, with first week defined by first sunday
         %W : week of year, with first week defined by first monday
         %% : sign %

       * %x : short for zone.local[21] (Ex.: "%m/%d/%y")
         %X : short for "%H:%M:%S"
       * %C : short for "%a %b %e %H:%M:%S %Y"
       * %c : short for "%x %X"

       * These formats depends on 'zone'.


@DE*/


class nTime {

protected:

   time_t secs;		// seconds and 
   long msecs;		// milliseconds from function ftime

   // Init. 'secs' with/without 'timesec'.
   void InitTime(struct tm* timesec = 0);

   // Proof if 'day' is valid in 'month' of 'year'.
   bool IsValidDay(int year, int month, int day) const;

   // Proof if given values are valid.
   bool ProofTime(int year, int month, int day, int hour, int min, int sec, int msec=0) const;

   // Proof if 'tim1' <= 'tim2'.
   bool LessOrEqual(const struct tm& tim1, const struct tm& tim2) const;

   // Calculate seconds since zero ('localtime(0)').
   time_t CalcSeconds(int year, int month, int day, int hour, int min, int sec) const;

   //
   void GetTimeWithFormat(nString&, struct tm&, const nZone&) const;

public:

/*@DS
PUBLIC CONSTRUCTORS
*/

   ~nTime() {;}
   // Do nothing destructor.

   nTime()
   // Set to current time.
//@DE
      {InitTime();}
//@DS

   nTime(const nTime& time)
   // Copy constr.
//@DE
      : secs(time.secs), msecs(time.msecs)  {;}
//@DS

   nTime(struct tm* tim)
   // With 'struct tm*' from 'localtime' function.
//@DE
      {InitTime(tim);}
//@DS

   nTime(time_t seconds)
   // With seconds from 'time' function.
//@DE
      : secs(seconds) {msecs = 0;}
//@DS

   nTime(int year, int month, int day, int hour, int min, int sec);
   nTime(int year, int month, int day, int hour, int min, int sec, int msec);
   // Values must be in the range of struct tm (and time_t).


/*
PUBLIC MEMBER FUNCTIONS
*/

   static bool YearIsLeapYear(int year)
   // Proof, if given year has a leap day
//@DE
      { return ((year%4) == 0 && ((year%100) == 0 ? (year%400) == 0 : true));}
//@DS

   bool IsLeapYear()
   // Proof, if given year has a leap day
//@DE
      { return YearIsLeapYear(GetYear());}
//@DS

   bool IsValid() const
   // Proof, if 'this' is valid.
//@DE
      { return secs >= 0;}
//@DS

   void SetNow()
   // Set to current time.
//@DE
      { InitTime();}
//@DS

   time_t GetSecs() const
   // Get the stored (time_t) value.
//@DE
       { return secs;}
//@DS

   long GetMsecs() const
   // Get the stored (long) value of milliseconds.
//@DE
       { return msecs;}
//@DS

   int GetYear() const
   // 1970 (or 1900?) - 2037(?)
//@DE
       { return IsValid() ? localtime(&secs)->tm_year + 1900 : 0;}
//@DS

   int GetMonth() const
   // 1 - 12 (jan == 1, ...)
//@DE
       { return IsValid() ? localtime(&secs)->tm_mon + 1 : 0;}
//@DS

   int GetDay() const
   // 1 - 31
//@DE
       { return IsValid() ? localtime(&secs)->tm_mday : 0;}
//@DS

   int GetDayOfWeek() const
   // 0 - 6 (sunday == 0, ...)
//@DE
       { return IsValid() ? localtime(&secs)->tm_wday : 0;}
//@DS

   int GetDayOfYear() const
   // 1 - 366 (1.jan. == 1)
//@DE
       { return IsValid() ? localtime(&secs)->tm_yday + 1 : 0;}
//@DS

   int GetHours() const
   // 0 - 23
//@DE
       { return IsValid() ? localtime(&secs)->tm_hour : 0;}
//@DS

   int GetMinutes() const
   // 0 - 59
//@DE
       { return IsValid() ? localtime(&secs)->tm_min : 0;}
//@DS

   int GetSeconds() const
   // 0 - 59
//@DE
       { return IsValid() ? localtime(&secs)->tm_sec : 0;}
//@DS

   void GetTimeWithFormat(nString& format,
                          const nZone& zone = (nZone)GERMANLOCALS) const
   // Get time as string as given in 'format' and return the entire string
   // in it. (See at the beginning for details of 'format'.)
//@DE
        {
           struct tm tim = *localtime(&secs);
           GetTimeWithFormat(format, tim, zone);
        }
//@DS
    nString AsString(const nString& format,
                     const nZone& zone = (nZone)GERMANLOCALS) const
   // Formats date/time according the formatting rules specified in 'format'
   // and returns it as a string. Same as GetTimeWithFormat, but does not
   // destroy the format string contents.
//@DE
        {
           nString s(format);
           struct tm tim = *localtime(&secs);
           GetTimeWithFormat(s, tim, zone);
           return s;
        }
//@DS

/*
PUBLIC MEMBER OPERATORS
*/

   // Assignments
   nTime& operator=  (const nTime&);
   nTime& operator=  (time_t seconds);
   nTime& operator+= (time_t seconds);
   nTime& operator-= (time_t seconds)
//@DE
      {return operator+= (-seconds);}
//@DS

   time_t Compare(const nTime& tim) const
   // Compare 'this' and 'tim' : (<,==,>) null, if 'this' (<,==,>) 'tim'
//@DE
      { return secs - tim.secs;}
//@DS

   const nTime add(long seconds) const;
   // Add long in seconds to temporary nTime.
//@DE
};
//@DS


/*
GLOBAL OPERATORS
*/

// Compare 2 nTime
inline bool operator== (const nTime& tim1, const nTime& tim2)
//@DE
   { return tim1.Compare(tim2) == 0;}
//@DS

inline bool operator!= (const nTime& tim1, const nTime& tim2)
//@DE
   { return tim1.Compare(tim2) != 0;}
//@DS

inline bool operator<  (const nTime& tim1, const nTime& tim2)
//@DE
   { return tim1.Compare(tim2) <  0;}
//@DS

inline bool operator<= (const nTime& tim1, const nTime& tim2)
//@DE
   { return tim1.Compare(tim2) <= 0;}
//@DS

inline bool operator>  (const nTime& tim1, const nTime& tim2)
//@DE
   { return tim1.Compare(tim2) >  0;}
//@DS

inline bool operator>= (const nTime& tim1, const nTime& tim2)
//@DE
   { return tim1.Compare(tim2) >= 0;}
//@DS



// Add/Sub nTime and long (in seconds)
inline const nTime operator+ (const nTime& tim, long seconds)
//@DE
   { return tim.add(seconds);}
//@DS

inline const nTime operator+ (long seconds, const nTime& tim)
//@DE
   { return tim.add(seconds);}
//@DS

inline const nTime operator- (const nTime& tim, long seconds)
//@DE
            { return tim.add(-seconds);}
//@DS

// Add/Sub nTime and nTime
inline const nTime operator+ (const nTime& tim1, const nTime& tim2)
//@DE
   { return nTime(tim1.GetSecs() + tim2.GetSecs() );}
//@DS

inline const nTime operator- (const nTime& tim1, const nTime& tim2)
//@DE
   { return nTime(tim1.GetSecs() - tim2.GetSecs() );}

#endif

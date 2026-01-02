#ifndef DATE_INC
#define DATE_INC

#include "time.hpp"

/*@DS --------------------------------------------------------------------------
NAME
   nDate - A date class with range from 1.1.1 to ?.

SYNOPSIS
   include "date.hpp"
   nDate date;

DESCRIPTION
   Class nDate hasn't the limitation of nTime (type time_t). It only contains
   the date since 1.1.1 as an absolute day (and no seconds). So it has a
   greater range as nTime. But you can get nTime informations like GetHours and
   so on. In most cases you get midnight as return values.



@DE*/

class nDate : public nTime {

   long absday;      // since 1.1.1

protected:

   // Calculate days since 1.1.1
   long CalcAbsday(long year, long mon, long day) const;

   // Calculate year, month and day from 'absday'.
   void CalcDate(long& year, long& month, long& day) const;

   //Init. nDate and nTime.
   void InitDate(struct tm* tmsecs = 0);

   // Proof, if given date is correct (year > 0, day < day in month)
   bool DateIsCorrect(long year, long mon, long day) const;

   // Calculate the day in the year (1-366)
   long DayOfYear(long year, long mon, long day) const;

   // Fill struct tm with date belong to 'absday'.
   void FillTM(struct tm&) const;

public:

/*@DS
PUBLIC CONSTRUCTORS
*/

   ~nDate() {;}
   // Do nothing destructor.

   nDate()
   // Set to current time.
//@DE
      : nTime() { InitDate(); }
//@DS

   nDate(const nDate& da)
   // Copy constructor.
//@DE
      : nTime(da.secs), absday(da.absday){;}
//@DS

   nDate(struct tm* time)
   // Constructor for given 'struct tm'.
//@DE
      : nTime(time) { InitDate(time); }
//@DS

   nDate(int year, int mon, int day);
   nDate(long year, long mon, long day);
   // Constructor for ...

   nDate(long yyyymmdd);
   // Constructor for long = y*10000+m*100+d

   nDate(const nTime&);
   // Type conversion.


/*
PUBLIC METHODS
*/
   const nDate& AddMonth(const int n);
// Add 'n' months to self if n > 0.

   void SetNow()
   // Set to current date
//@DE
      { InitTime(); InitDate();}
//@DS

   bool IsValid() const
   // Returns true, if date is valid (not before 1.1.1).
//@DE
      { return absday >= 0;}
//@DS

   long GetAbsday() const
   // Get the absolute days since 1.1.1 (== 0, 2.1.1 == 1).
//@DE
        { return absday;}
//@DS

   // Get day, month, year.
   long GetDay()   const;  // 1 - 31
   long GetMonth() const;  // 1 - 12
   long GetYear()  const;  // 1 - ??

   long GetDaysOfMonth(long mon) const;
   // get count of days in the given mon

   short GetDayOfWeek() const
   // Get the day of the week. (sunday == 0, monday == 1, ...)
//@DE
        { return static_cast<short>((absday+1) % 7);}
//@DS

   long GetDayOfYear() const;
   // Get day of the year. (1-366)

   long GetYYYYMMDD() const;
   // Get date as long = y*10000+m*100+d

   void GetTimeWithFormat(nString& format,
                          const nZone& zone = (nZone)GERMANLOCALS) const;
   // Get date as string with given format.
   // (look about format in class nTime / time.hpp)

   void GetDiff(const nDate& date,
        long& year, long& month, long& day) const;
   // Get the difference between two dates in year, month and day.
   // The resulting values are allways positiv.
   // If one of the dates is unguilty, the result is undefined.

   bool IsLeapYear() const
   // Has this year a leap day ?
//@DE
      { return YearIsLeapYear((int)GetYear()); }
//@DS

   static long GetEasterYYYYMMDD(long year);
   // Returns the date (YYYYMMDD) of Easter sunday in the specified year

   long GetEasterYYYYMMDD()   const
   // Returns the date (YYYYMMDD) of Easter sunday
   // in the year of the stored date
   {return GetEasterYYYYMMDD(GetYear() ); }

   // Assignments
   nDate& operator=  (const nDate&);
   nDate& operator=  (const nTime&);
   nDate& operator+= (long days);
   nDate& operator-= (long days)
//@DE
      { return operator+=(-days);}
//@DS

   const nDate add(long days) const
   // For temporary addition.
//@DE
      {
         nDate temp = *this;
         temp += days;
         return temp;
      }
//@DS

   long Compare(const nDate& date) const
   // returns ( <0,==0,>0 ), if 'this' ( <,==,> ) 'date'
//@DE
        { return absday - date.absday;}
//@DS

   // Increment / Decrement nDate one day
   const nDate& operator++()        // Prefix : ++d,
//@DE
      { return operator+=(1);}
//@DS
   const nDate& operator--()        //          --d
//@DE
      { return operator+=(-1);}
//@DS

   const nDate  operator++(int)     // Postfix : d++,
//@DE
      {
         nDate temp = *this;
         operator+=(1);
         return temp;
      }
//@DS
   const nDate  operator--(int)     //           d--
//@DE
      {
         nDate temp = *this;
         operator+=(-1);
         return temp;
      }

};
/*@DS


GLOBAL OPERATORS
*/


// Addition/Subtraction between nDate and days.
inline nDate operator+ (const nDate& date, long days)
//@DE
   { return date.add(days);}
//@DS
inline nDate operator+ (long days,         const nDate& date)
//@DE
   { return date.add(days);}
//@DS
inline nDate operator- (const nDate& date, long days)
//@DE
   { return date.add(-days);}
//@DS

// Get difference in days of 2 nDates.
inline long  operator- (const nDate& date1, const nDate& date2)
//@DE
   { return date1.GetAbsday() - date2.GetAbsday();}
//@DS

// Compare 2 nDates
inline bool operator== (const nDate& date1, const nDate& date2)
//@DE
   { return date1.Compare(date2) == 0;}
//@DS

inline bool operator!= (const nDate& date1, const nDate& date2)
//@DE
   { return date1.Compare(date2) != 0;}
//@DS

inline bool operator<  (const nDate& date1, const nDate& date2)
//@DE
   { return date1.Compare(date2) <  0;}
//@DS

inline bool operator<= (const nDate& date1, const nDate& date2)
//@DE
   { return date1.Compare(date2) <= 0;}
//@DS

inline bool operator>  (const nDate& date1, const nDate& date2)
//@DE
   { return date1.Compare(date2) >  0;}
//@DS

inline bool operator>= (const nDate& date1, const nDate& date2)
//@DE
   { return date1.Compare(date2) >= 0;}

#endif

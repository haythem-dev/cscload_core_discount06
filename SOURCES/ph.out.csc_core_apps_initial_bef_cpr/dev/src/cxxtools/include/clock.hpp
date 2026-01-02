#ifndef CLOCK_INC
#define CLOCK_INC

#include "time.hpp"

/*@DS --------------------------------------------------------------------------
NAME
   nClock - A clock class containing seconds since midnight.

SYNOPSIS
   include "clock.hpp"
   nClock cl;

DESCRIPTION
   Basically nClock is a class that contains the seconds since midnight. But
   you can add/sub seconds to make an overflow/underflow over midnight. Thus
   midnight can be some days ago. To normalize nClock you can call 'Correction'
   which returns the over-/underflow in days. Then nClock is between 00:00:00
   and 23:59:59.

   You can also calculate with nClock. You make an instance with 12 minutes and
   multiply it with 4 to get the absolute play time for an american football
   match.

   Class nClock is a derived class from class nTime. So it inherites some
   methods from nTime like GetYear(), GetMonth(), GetDay(), etc. These methods
   return the current year, month, day, etc.



GLOBAL CONSTANT
*/

const long cSECONDSPERDAY = 86400;
// Global constant containing the seconds of one day.


//@DE

class nClock : public nTime {

   long daysecs;    // seconds since midnight

protected:

   // Init. 'daysecs'.
   void InitClock(struct tm* tmsecs = 0);

   // Proof if 'min' and 'sec' are in valid ranges.
   bool ProofClock(long min, long sec) const;

   // Calculate seconds since midnight.
   long CalcDaysecs(long hour, long min, long sec) const;

public:

/*@DS
PUBLIC CONSTRUCTORS
*/

   ~nClock() {;}
   // Do nothing destructor.

   nClock()
   // Set to current time.
//@DE
      : nTime() { InitClock(); }
//@DS

   nClock(const nClock& cl)
   // Copy constructor.
//@DE
      : nTime(cl.secs), daysecs(cl.daysecs) {;}
//@DS

   nClock(struct tm* time)
   // Const. with struct tm.
//@DE
      : nTime(time) { InitClock(time); }
//@DS

   nClock(int hour, int min, int sec);
   nClock(long hour, long min, long sec);
   // With hours, minutes and seconds.

   nClock(long hhmmss, long msec = 0);
   // With long = hour*10000+minute*100+second.

   nClock(const nTime&);
   // Type conversion from nTime.


/*
PUBLIC METHODS
*/

   bool IsValid() const
   // Proof, if 0 <= 'this' < 1 day
//@DE
      { return 0 <= daysecs && daysecs < cSECONDSPERDAY;}
//@DS

   long Correction(void);
   // Set 'this' between midnight and 23:59:59 and returns
   // the over-/underflow in days.

   void SetNow()
   // Set to current localtime.
//@DE
      { InitTime(); InitClock();}
//@DS

   long GetDaySeconds() const    // 0 - ?
//@DE
      { return daysecs;}
//@DS
   long GetSeconds() const       // 0 - 59
//@DE
      { return daysecs % 60;}
//@DS
   long GetMinutes() const       // 0 - 59
//@DE
      { return (daysecs % 3600) / 60;}
//@DS
   long GetHours() const         // 0 - ?
//@DE
      { return daysecs / 3600;}
//@DS
   long GetHHMMSS() const
   // Get long = hours*10000+minutes*100+seconds.
//@DE
      { return GetHours() * 10000 +
               GetMinutes() * 100 +
               GetSeconds();        }
//@DS
   long GetHHMMSSD() const
   // Get long = hours*100000+minutes*1000+seconds*10+deciseconds.
		{ return	GetHHMMSS() * 10 +
					GetMsecs() /100;	}

   long GetHHMMSSmmm() const
   // Get long = hours*10000000+minutes*100000+seconds*1000+milliseconds.
		{ return	GetHHMMSS() * 1000 +
					GetMsecs();			}

   static long HHMMSS2Seconds(long hhmmss);
   static long Seconds2HHMMSS(long seconds);
   // Conversion from hhmmss into seconds and vice versa.
   // You can call it like :
   //    long l = nClock::HHMMSS2Seconds(123456);

   // Assignments
   nClock& operator= (const nClock&);
   nClock& operator= (const nTime&);
   nClock& operator= (long hhmmss);
   nClock& operator+= (long seconds);
   nClock& operator-= (long seconds)
//@DE
      {return operator+= (-seconds);}
//@DS
   nClock& operator*= (long factor);
   nClock& operator/= (long divisor);
   nClock& operator%= (const nClock&);

   // Operations
   const nClock add (long seconds) const;
   const nClock mul (long factor ) const;
   const nClock div (long divisor) const;
         long   sub (const nClock&) const;

   long Compare(const nClock& cl) const
   // Comparision : (<,==,>) null, if this (<,==,>) cl
//@DE
      { return daysecs - cl.daysecs;}
};
/*@DS


GLOBAL OPERATORS
*/

// Addition between nClock and long.
inline const nClock operator+ (const nClock& cl1, const nClock& cl2)
//@DE
   { return cl1.add(cl2.GetDaySeconds());}
//@DS
inline const nClock operator+ (const nClock& cl, long seconds)
//@DE
   { return cl.add(seconds);}
//@DS
inline const nClock operator+ (long seconds, const nClock& cl)
//@DE
   { return cl.add(seconds);}
//@DS

// Get difference of 2 nClock.
inline       long   operator- (const nClock& cl1, const nClock& cl2)
//@DE
   { return cl1.sub(cl2);}
//@DS

// Subtraction between nClock and long.
inline const nClock operator- (const nClock& cl, long seconds)
//@DE
   { return cl.add(-seconds);}
//@DS

// Multiply nClock with long.
inline const nClock operator* (const nClock& cl, long factor)
//@DE
   { return cl.mul(factor);}
//@DS
inline const nClock operator* (long factor, const nClock& cl)
//@DE
   { return cl.mul(factor);}
//@DS

// Division ...
inline const nClock operator/ (const nClock& cl, long divisor)
//@DE
   { return cl.div(divisor);}
//@DS
inline       long   operator/ (const nClock& cl1, const nClock& cl2)
//@DE
   { return cl1.GetDaySeconds()/cl2.GetDaySeconds();}
//@DS

// Modulo between 2 nClocks.
inline long operator% (const nClock& cl1, const nClock& cl2)
//@DE
   { return cl1.GetDaySeconds()%cl2.GetDaySeconds();}
//@DS

// Compare 2 nClocks
inline bool operator== (const nClock& cl1, const nClock& cl2)
//@DE
   { return cl1.Compare(cl2) == 0;}
//@DS

inline bool operator!= (const nClock& cl1, const nClock& cl2)
//@DE
   { return cl1.Compare(cl2) != 0;}
//@DS

inline bool operator<  (const nClock& cl1, const nClock& cl2)
//@DE
   { return cl1.Compare(cl2) < 0;}
//@DS

inline bool operator<= (const nClock& cl1, const nClock& cl2)
//@DE
   { return cl1.Compare(cl2) <= 0;}
//@DS

inline bool operator>  (const nClock& cl1, const nClock& cl2)
//@DE
   { return cl1.Compare(cl2) > 0;}
//@DS

inline bool operator>= (const nClock& cl1, const nClock& cl2)
//@DE
   { return cl1.Compare(cl2) >= 0;}

//@DE

#endif

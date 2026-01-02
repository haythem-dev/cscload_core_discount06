#include "clock.hpp"

// ---------------------------------------------------------------------
// Constr. with hour, minutes and seconds.
// Because 'secs' is set to current time, it must be corrected.
// ---------------------------------------------------------------------
nClock::nClock(int hour, int min, int sec) : nTime()
{
   daysecs = CalcDaysecs((long)hour, (long)min, (long)sec);

   struct tm tim = *localtime(&secs);

   long tmsecs = CalcDaysecs((long)tim.tm_hour, (long)tim.tm_min, (long)tim.tm_sec);

   secs += (time_t) daysecs - tmsecs;
}


// ---------------------------------------------------------------------
// Constr. with hour, minutes and seconds.
// Because 'secs' is set to current time, it must be corrected.
// ---------------------------------------------------------------------
nClock::nClock(long hour, long min, long sec) : nTime()
{
   daysecs = CalcDaysecs(hour, min, sec);

   struct tm tim = *localtime(&secs);

   long tmsecs = CalcDaysecs((long)tim.tm_hour, (long)tim.tm_min, (long)tim.tm_sec);

   secs += (time_t) daysecs - tmsecs;
}


// ---------------------------------------------------------------------
// Constr. with hour, minutes and seconds.
// Because 'secs' is set to current time, it must be corrected.
// ---------------------------------------------------------------------
nClock::nClock(long hhmmss, long msec) : nTime()
{
   long hour = hhmmss/10000,
        min = (hhmmss%10000)/100,
        sec = hhmmss%100;

   daysecs = CalcDaysecs(hour, min, sec);

   struct tm tim = *localtime(&secs);

   long tmsecs = CalcDaysecs((long)tim.tm_hour, (long)tim.tm_min, (long)tim.tm_sec);

   secs += (time_t) daysecs - tmsecs;
   msecs = msec;
}


// ---------------------------------------------------------------------
// Type conversion from nTime.
// Copy 'secs', 'msecs' and init. 'daysecs'.
// ---------------------------------------------------------------------
nClock::nClock(const nTime& tim) : nTime(tim)
{
   if (tim.IsValid())
      InitClock();

   else
      daysecs = 0;
}


// ---------------------------------------------------------------------
// Static function to convert long into seconds.
// ---------------------------------------------------------------------
long nClock::HHMMSS2Seconds(long hhmmss)
{
   return (hhmmss/10000)*3600 +
          ((hhmmss%10000)/100)*60 +
          hhmmss%100;
}


// ---------------------------------------------------------------------
// Static function to convert seconds into long.
// ---------------------------------------------------------------------
long nClock::Seconds2HHMMSS(long seconds)
{
   return (seconds/3600)*10000 +
          ((seconds%3600)/60)*100 +
          seconds%60;
}


// ---------------------------------------------------------------------
// Init. 'daysec'.
// ---------------------------------------------------------------------
void nClock::InitClock(struct tm* tmsecs)
{
   if (tmsecs == 0)
   {
      // get local time since midnight
      tmsecs = localtime(&secs);
   }

   // convert to seconds since midnight
   daysecs = CalcDaysecs((long)(tmsecs->tm_hour),
                         (long)(tmsecs->tm_min),
                         (long)(tmsecs->tm_sec)  );
}


// ---------------------------------------------------------------------
// Calculate seconds since midnight.
// ---------------------------------------------------------------------
long nClock::CalcDaysecs(long hour, long min, long sec) const
{
   if (!ProofClock(min, sec))
      return 0;
   else
      return hour * 3600 +
             min  *   60 +
             sec;
}


// ---------------------------------------------------------------------
// Proof if 'min' and 'sec' are in guilty ranges.
// Because nClock can be negativ, the absolute values were proofed.
// ---------------------------------------------------------------------
bool nClock::ProofClock(long min, long sec) const
{
   return 0 <= labs(min)  && labs(min) < 60 &&
          0 <= labs(sec)  && labs(sec) < 60;
}


// ---------------------------------------------------------------------
// Assignment.
// ---------------------------------------------------------------------
nClock& nClock::operator= (const nClock& cl)
{
   daysecs = cl.daysecs;
   secs = cl.secs;

   return *this;
}


// ---------------------------------------------------------------------
// Assignment from nTime.
// Copy 'secs' and init. 'daysec'.
// ---------------------------------------------------------------------
nClock& nClock::operator= (const nTime& tim)
{
   secs = tim.GetSecs();
   if (tim.IsValid())
      InitClock();

   else
      daysecs = 0;

   return *this;
}


// ---------------------------------------------------------------------
// Assignment from long.
// ---------------------------------------------------------------------
nClock& nClock::operator= (long hhmmss)
{
   InitTime();

   long hour = hhmmss/10000,
        min = (hhmmss%10000)/100,
        sec = hhmmss%100;

   daysecs = CalcDaysecs(hour, min, sec);

   struct tm tim = *localtime(&secs);

   long tmsecs = CalcDaysecs((long)tim.tm_hour, (long)tim.tm_min, (long)tim.tm_sec);

   secs += (time_t) daysecs - tmsecs;

   return *this;
}


// ---------------------------------------------------------------------
// Increment 'daysecs' and 'secs' by 'seconds'.
// ('secs' : hope that no over-/underflow occur.)
// ---------------------------------------------------------------------
nClock& nClock::operator+= (long seconds)
{
   daysecs += seconds;
   secs += (time_t)seconds;

   return *this;
}


// ---------------------------------------------------------------------
nClock& nClock::operator*= (long factor)
{
   long olddaysecs = daysecs;
   daysecs *= factor;
   secs += (time_t) (daysecs - olddaysecs);

   return *this;
}


// ---------------------------------------------------------------------
nClock& nClock::operator/= (long divisor)
{
   long olddaysecs = daysecs;
   daysecs /= divisor;
   secs += (time_t) (daysecs - olddaysecs);

   return *this;
}


// ---------------------------------------------------------------------
nClock& nClock::operator%= (const nClock& cl)
{
   long olddaysecs = daysecs;
   daysecs %= cl.daysecs;
   secs += (time_t) (daysecs - olddaysecs);

   return *this;
}


// ---------------------------------------------------------------------
// Return temporary nClock add by 'seconds'.
// Do it with defined function.
// ---------------------------------------------------------------------
const nClock nClock::add (long seconds) const
{
   nClock temp = *this;

   temp += seconds;

   return temp;
}


// ---------------------------------------------------------------------
// Return temporary nClock multiplyed by 'factor'.
// ---------------------------------------------------------------------
const nClock nClock::mul (long factor) const
{
   nClock temp = *this;

   temp *= factor;

   return temp;
}


// ---------------------------------------------------------------------
const nClock nClock::div (long divisor) const
{
   nClock temp = *this;

   temp /= divisor;

   return temp;
}


// ---------------------------------------------------------------------
long nClock::sub (const nClock& cl) const
{
   return daysecs - cl.daysecs;
}



// ---------------------------------------------------------------------
// Because nClock has not the restriction to be valid, this function
// corrects it and returns the over-/underflow in days.
// ---------------------------------------------------------------------
long nClock::Correction(void)
{
   long overflow = 0;

   if (daysecs >= 0)
   {
      while (daysecs >= cSECONDSPERDAY)
      {
         daysecs -= cSECONDSPERDAY;
         ++overflow;
      }
   }
   else // daysecs < 0
   {
      while (daysecs <= 0)
      {
         daysecs += cSECONDSPERDAY;
         --overflow;
      }
   }

   // Return the days.
   return overflow;
}

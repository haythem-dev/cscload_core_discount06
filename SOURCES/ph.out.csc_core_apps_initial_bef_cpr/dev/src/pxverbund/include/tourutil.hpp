#ifndef TOURUTIL_HPP
#define TOURUTIL_HPP

/***************************************************************************************************************************/
/* includes */
/***************************************************************************************************************************/
#include <date.hpp>

class pxHoliDayList;

/***************************************************************************************************************************/

class TourUtil
{
public:
    enum WeekDayEnum { UnknownWeekDay = -1, Sunday = 0, Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, Friday = 5, Saturday = 6 };

    static const long HoursPerDay      = 24;
    static const long MinutesPerHour   = 60;
    static const long SecondsPerMinute = 60;
    static const long SecondsPerHour   = MinutesPerHour * SecondsPerMinute;
    static const long SecondsPerDay    = HoursPerDay * MinutesPerHour * SecondsPerMinute;

    static bool                         isPseudoTour( const nString& tourid );

    static bool                         isNullOrCurrentDate( const nDate& date );
    static bool                         isDateInTheFuture( const nDate& date );
    static nDate                        getNullDate();
    static long                         getLongDate(const nDate& date);
    static nDate                        getTomorrowsDate();
    static nDate                        getCurrentDate();
    static short                        getCurrentWeekday();
    static short                        getNextWeekday(short weekday = -1);
    static nDate                        getDateForNextWeekdayOccurrence( short weekday );
    static nDate                        getDateForSubsequentWeekdayOccurrence( short weekday );
    static nDate                        getDateForSubsequentWeekday( short weekday );
    static nDate                        getDateOfNextWorkingDay( pxHoliDayList* holidaylist, const short branchno, const nDate& datetocheck = nDate() );
    static nDate                        getDateTime( const long& yyyyMMdd, const long& hhmm, const bool normalizeDate = false );
    static short                        getWeekdayForDate(const long& yyyyMMdd);

    static TourUtil::WeekDayEnum        getWeekDay(const short& wd);
    static short                        getWeekDay(const TourUtil::WeekDayEnum wd);

    static nTime                        getNullTime();
    static long                         getLongTime(const nTime& time);
    static nTime                        getCurrentTime();

    static long                         getTourIdInSeconds(const nString& tourid);
    static long                         getHoursFromTourId( const nString& tourid );
    static long                         getMinutesFromTourId( const nString& tourid );
    static long                         getTourIdAsHHMM(const nString& tourid);
    static nString                      getTourIdAsReadableHHMM(const nString& tourid);
    static long                         getTimeInSeconds(const nTime& time);

    static long                         getReadableDateTime( const nDate& d );

    static void                         writeLog( std::stringstream& s, bool clean = true );
    static void                         writeLogINFO(std::stringstream& s, bool clean = false );
    static void                         writeLogDEBUG(std::stringstream& s, bool clean = false );
};

#endif // TOURUTIL_HPP

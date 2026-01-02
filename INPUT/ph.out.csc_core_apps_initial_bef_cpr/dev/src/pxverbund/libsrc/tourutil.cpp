#include "tourutil.hpp"
#include "pxholiday.hpp"
#include <pxbase/pxconstants.hpp>
#include <libbasarcmnutil_bstring.h>
#include <logger/loggerpool.h>
#include <sstream>
extern bool pxGlobalNoDatabaseWrite;

/***************************************************************************************************************************/
/* static */ void TourUtil::writeLog( std::stringstream& s, bool clean /*= false*/ )
{
	if( !pxGlobalNoDatabaseWrite ) BLOG_INFO( libcsc::LoggerPool::getLoggerTourManager(), s.str() );
	if( clean ) s.str(std::string());
}

/***************************************************************************************************************************/
/* static */ void TourUtil::writeLogINFO(std::stringstream& s, bool clean /*= false*/ )
{
	if( !pxGlobalNoDatabaseWrite ) BLOG_DEBUG( libcsc::LoggerPool::getLoggerTourManager(), s.str() );
	if( clean ) s.str(std::string());
}

/***************************************************************************************************************************/
/* static */ void TourUtil::writeLogDEBUG(std::stringstream& s, bool clean /*= false*/ )
{
	if( !pxGlobalNoDatabaseWrite ) BLOG_TRACE( libcsc::LoggerPool::getLoggerTourManager(), s.str() );
	if( clean ) s.str(std::string());
}

/***************************************************************************************************************************/
/* static */ bool TourUtil::isPseudoTour( const nString& tourid )
{
	basar::VarString tourId( tourid );
	tourId.trim( basar::cmnutil::BString::FIRST_END );
	if( 6 != tourId.length() )
	{
		return false;
	}
	static const basar::VarString pseudoTour( "4759" );
	if( pseudoTour == tourId.substr( 0, 4 ) )
	{
		return true;
	}
	return false;
}

/***************************************************************************************************************************/
/* static */ bool TourUtil::isDateInTheFuture( const nDate& date )
{
	if( TourUtil::isNullOrCurrentDate(date) ) { return false; }
	if( date.GetYYYYMMDD() > TourUtil::getCurrentDate().GetYYYYMMDD() ) { return true; }
	return false;
}

/***************************************************************************************************************************/
/* static */ bool TourUtil::isNullOrCurrentDate( const nDate& date )
{
	if( date == TourUtil::getNullDate() )
	{
		return true;
	}
	if( date <= TourUtil::getCurrentDate() )
	{
		return true;
	}
	return false;
}

/***************************************************************************************************************************/
/* static */ nDate TourUtil::getNullDate()
{
	return nDate(0L);
}

/***************************************************************************************************************************/
/* static */ long TourUtil::getLongDate(const nDate& date)
{
	return date.GetYYYYMMDD();
}

/***************************************************************************************************************************/
/* static */ nDate TourUtil::getTomorrowsDate()
{
    return TourUtil::getCurrentDate().add(1);
}

/***************************************************************************************************************************/
/* static */ nDate TourUtil::getCurrentDate()
{
	return nDate();
}

/***************************************************************************************************************************/
/* static */ short TourUtil::getCurrentWeekday()
{
	return TourUtil::getCurrentDate().GetDayOfWeek();
}

/***************************************************************************************************************************/
/* static */ short TourUtil::getNextWeekday(short weekday)
{
	if( weekday < 0 ) weekday = TourUtil::getCurrentDate().GetDayOfWeek();
	weekday++;
	if( weekday > 6 )
	{
		weekday = 0;
	}
	return weekday;
}

/***************************************************************************************************************************/
/* static */ nDate TourUtil::getDateForNextWeekdayOccurrence( short weekday )
{
	nDate date = TourUtil::getCurrentDate();
	if( weekday >= 0 && weekday <= 6 )
	{
		while( date.GetDayOfWeek() != weekday )
		{
			date = date.add(1);
		}
	}
	return date;
}

/***************************************************************************************************************************/
/* static */ nDate TourUtil::getDateForSubsequentWeekdayOccurrence( short weekday )
{
	nDate date = TourUtil::getCurrentDate().add(1);
	if( weekday >= 0 && weekday <= 6 )
	{
		while( date.GetDayOfWeek() != weekday )
		{
			date = date.add(1);
		}
	}
	return date;
}

/***************************************************************************************************************************/
/* static */ nDate TourUtil::getDateForSubsequentWeekday(short weekday)
{
	nDate date = TourUtil::getCurrentDate();
	short currentDay = date.GetDayOfWeek();
	if( weekday < 0 || weekday > 6 )
	{
		weekday = currentDay;
	}

	if( currentDay >= weekday )
	{
		date += ( 7 - (currentDay - weekday) );
	}
	else
	{
		date += ( weekday - currentDay );
	}
	return date;
}

/***************************************************************************************************************************/
/* static */ nDate TourUtil::getDateOfNextWorkingDay( pxHoliDayList* holidaylist, const short branchno, const nDate& datetocheck /*= nDate()*/ )
{
	nDate retval = datetocheck.add(1);
	if( holidaylist->CheckDateForHoliday( retval, branchno ) )
	{
		retval = nDate(holidaylist->CalculateNextWorkDay( datetocheck, branchno ));
	}
	return retval;
}

/***************************************************************************************************************************/
/* static */ short TourUtil::getWeekdayForDate(const long& yyyyMMdd)
{
	nDate tempdate( yyyyMMdd );
	return tempdate.GetDayOfWeek();
}

/***************************************************************************************************************************/
/* static */ nDate TourUtil::getDateTime( const long& yyyyMMdd, const long& hhmm, const bool normalizeDate /* = false */ )
{
	nDate tempdate( yyyyMMdd );
	int hours = hhmm / 100;
	int minutes = hhmm % 100;
	if (true == normalizeDate)
	{
		while( hours >= 24 )
		{
			++tempdate;
			hours -= 24;
		}
	}
	nTime temptime( tempdate.GetYear(), tempdate.GetMonth(), tempdate.GetDay(), hours, minutes, 0 );
	nDate retval(temptime);
	return retval;
}

/***************************************************************************************************************************/
/* static */ TourUtil::WeekDayEnum TourUtil::getWeekDay(const short& wd)
{
	switch( wd )
	{
		case 0:
			return Sunday;
		case 1:
			return Monday;
		case 2:
			return Tuesday;
		case 3:
			return Wednesday;
		case 4:
			return Thursday;
		case 5:
			return Friday;
		case 6:
			return Saturday;
		default:
			return UnknownWeekDay;
	}
}

/***************************************************************************************************************************/
/* static */ short TourUtil::getWeekDay(const TourUtil::WeekDayEnum wd)
{
	switch( wd )
	{
		case Sunday:
			return 0;
		case Monday:
			return 1;
		case Tuesday:
			return 2;
		case Wednesday:
			return 3;
		case Thursday:
			return 4;
		case Friday:
			return 5;
		case Saturday:
			return 6;
		case UnknownWeekDay:
		default:
			return -1;
	}
}

/***************************************************************************************************************************/
/* static */ nTime TourUtil::getNullTime()
{
	return pxConstants::NullTime;
}

/***************************************************************************************************************************/
/* static */ long TourUtil::getLongTime(const nTime& time)
{
	return ((time.GetHours() * 100) + time.GetMinutes());
}

/***************************************************************************************************************************/
/* static */ nTime TourUtil::getCurrentTime()
{
	return nTime();
}

/***************************************************************************************************************************/
/* static */ long TourUtil::getTourIdInSeconds(const nString& tourid)
{
	long hours = TourUtil::getHoursFromTourId(tourid);
	long minutes = TourUtil::getMinutesFromTourId(tourid);
	return (hours * TourUtil::SecondsPerHour) + (minutes * TourUtil::SecondsPerMinute);
}

/***************************************************************************************************************************/
/* static */ long TourUtil::getMinutesFromTourId( const nString& tourid )
{
	nString tour(tourid);
	tour.Strip();
	long retval = 0;
	if( 6 != tour.Length() )
	{
		return retval;
	}
	return atol( (char*)(nString)(tour(2,2) ) );
}

/***************************************************************************************************************************/
/* static */ long TourUtil::getHoursFromTourId( const nString& tourid )
{
	long retval = 0;
	nString tour = tourid;
	tour.Strip();
	if( 6 != tour.Length() )
	{
		return retval;
	}
	return atol( (char*)(nString)(tour(0,2) ) );
}

/***************************************************************************************************************************/
/* static */ long TourUtil::getTourIdAsHHMM(const nString& tourid)
{
	long retval = 0;
	nString tour = tourid;
	tour.Strip();
	if( 6 != tour.Length() )
	{
		return retval;
	}
	retval = (atol( (char*)(nString)(tour(0,2)) ) * 100) + ( atol( (char*)(nString)(tour(2,2)) ) );
	return retval;
}

/***************************************************************************************************************************/
/* static */ nString TourUtil::getTourIdAsReadableHHMM(const nString& tourid)
{
	nString retval(tourid);
	retval.Strip();
	if( 6 == retval.Length() )
	{
		retval = (nString)(retval(0,2)) + ":" + (nString)(retval(2,2));
	}
	else
	{
		retval = "";
	}
	return retval;
}

/***************************************************************************************************************************/
/* static */ long TourUtil::getTimeInSeconds(const nTime& time)
{
	long retval = 0;
	retval += time.GetHours() * 3600; // hours in seconds
	retval += time.GetMinutes() * 60; // minutes in seconds
	retval += time.GetSeconds();
	return retval;
}

/***************************************************************************************************************************/
/* static */ long TourUtil::getReadableDateTime( const nDate& d )
{
	if( TourUtil::getNullDate() == d ) return 0;
	long retval = d.GetYYYYMMDD();
	retval = retval * 10000;
	retval += d.GetHours() * 100;
	retval += d.GetMinutes();
	return retval;
}

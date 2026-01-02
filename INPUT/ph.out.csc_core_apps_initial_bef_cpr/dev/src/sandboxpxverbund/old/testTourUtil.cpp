#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

using namespace std;

// ------------------------------------------------------------------------------------------- //
void testTourUtil()
{	
	SessionUtil session(33);
	pxOrderTransmit* xmit = session.get();

	nDate nulldate = TourUtil::getNullDate();
	nDate currentdate = TourUtil::getCurrentDate();
	nTime currenttime = TourUtil::getCurrentTime();
	pxHoliDayList* holidaylist = new pxHoliDayList( xmit->Session() );
	nString tourid = "133402";

	cout << "\t Date as Long            : " << TourUtil::getLongDate(TourUtil::getCurrentDate()) << endl;
	cout << "\t Current Weekday         : " << TourUtil::getCurrentWeekday() << endl;
	cout << "\t Next Weekday            : " << TourUtil::getNextWeekday(TourUtil::getCurrentWeekday()) << endl;
	cout << "\t Current Time            : " << TourUtil::getLongTime( currenttime ) << endl;
	cout << "\t Current Time in Secs    : " << TourUtil::getTimeInSeconds( currenttime ) << endl;
	cout << "\t Next Weekday like Today : " << TourUtil::getLongDate( TourUtil::getDateForSubsequentWeekdayOccurrence( TourUtil::getCurrentWeekday() ) ) << endl;
	cout << "\t Subsequent Day          : " << TourUtil::getLongDate( TourUtil::getDateForSubsequentWeekday( TourUtil::getCurrentWeekday() ) ) << endl;
	cout << "\t Next Workday            : " << TourUtil::getLongDate( TourUtil::getDateOfNextWorkingDay( holidaylist, 33 ) ) << endl;
	cout << "\n" << endl;
	cout << "\t TourId                  : " << tourid << endl;
	cout << "\t    Readable             : " << TourUtil::getTourIdAsReadableHHMM(tourid) << endl;
	cout << "\t    HHMM                 : " << TourUtil::getTourIdAsHHMM(tourid) << endl;
	cout << "\t    Hours                : " << TourUtil::getHoursFromTourId( tourid ) << endl;				
	cout << "\t    Minutes              : " << TourUtil::getMinutesFromTourId( tourid ) << endl;
	cout << "\t    In Seconds           : " << TourUtil::getTourIdInSeconds(tourid) << endl;		
	cout << "\n" << endl;

	nDate temp = TourUtil::getDateTime( currentdate.GetYYYYMMDD(), 1430 );
	if( !temp.GetYYYYMMDD() )
	{
		cout << "\t FAILED Test getDateTime failed for current date! -> " << TourUtil::getLongDate( temp )  << endl;
	}
	else
	{
		cout << "\t OK Test getDateTime OK for date! -> " << TourUtil::getLongDate( temp )  << endl;
	}

	if( TourUtil::getLongTime( (nTime)temp ) != 1430 )
	{
		cout << "\t FAILED Test getDateTime failed for time 1430! -> " << TourUtil::getLongTime( (nTime)temp ) << endl;
	}
	else
	{
		cout << "\t OK Test getDateTime OK for time 1430! -> " << TourUtil::getLongTime( (nTime)temp ) << endl;
	}
	
	if( !TourUtil::isNullOrCurrentDate(nulldate) )
	{			
		cout << "\t FAILED Test isNullOrCurrentDate failed for NullDate!" << endl;
	}
	else
	{
		cout << "\t OK Test isNullOrCurrentDate OK for NullDate!" << endl;
	}

	if( !TourUtil::isNullOrCurrentDate(currentdate) )
	{			
		cout << "\t FAILED Test isNullOrCurrentDate failed for CurrentDate!" << endl;
	}
	else
	{
		cout << "\t OK Test isNullOrCurrentDate OK for CurrentDate!" << endl;
	}	

	

}

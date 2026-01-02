#include <libbasarcmnutil_datetime.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_datetimetools.h>

extern "C"
{	
	long basardatetime_getCurrentDateYYYYMMDD()
	{
		return basar::cmnutil::Date::getCurrent().getDate();
	}

	short basardatetime_getCurrentWeekday()
	{
		return static_cast<short>(basar::cmnutil::Date::getCurrent().getDayOfWeek());
	}
}

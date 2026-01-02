#ifndef GUARD_WEEKDAY_ENUM_H
#define GUARD_WEEKDAY_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

enum WeekDayEnum
{
	UnknownWeekDay = -1,
	Sunday = 0,
	Monday = 1,
	Tuesday = 2,
	Wednesday = 3,
	Thursday = 4,
	Friday = 5,
	Saturday = 6
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_WEEKDAY_ENUM_H

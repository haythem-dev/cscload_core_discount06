#ifndef GUARD_XMLINFOLEVEL_ENUM_H
#define GUARD_XMLINFOLEVEL_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

enum XMLInfoLevelEnum
{
	NoPermission = 0,		// usage of productavailability not allowed
	Unspecific = 1,			// unspecific product availability data
	Specific = 2,			// specific product availability data
	Reservation = 3,		// specific product availability data with additional reservation of requested quantities
	SpecificNoLimits = 4	// specific product availability data without quantity limits
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_XMLINFOLEVEL_ENUM_H

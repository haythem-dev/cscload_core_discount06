#ifndef RESERVATIONTYPEENUM_INC
#define RESERVATIONTYPEENUM_INC

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Define reservation types                                                  */
/*----------------------------------------------------------------------------*/

enum ReservationTypeEnum
{
	RESTYPE_UNKNOWN					= -1,

	// reservations in articlereservation
	RESTYPE_PHARMACYGROUP			= 0,	// 0 reservation on pharmacygroup level
	RESTYPE_NO_SALES_EFFECTIVE		= 2,	// 2 reservation on pharmacygroup level, but not sales effectiv
	RESTYPE_NO_CERTIFICATE			= 3,	// 3 no certificate available
	RESTYPE_NO_PACKAGE_INSERT		= 4,	// 4 no package insert(beipack)
	RESTYPE_BATCH_RECALL			= 5,	// 5 batch recall (SH,2012-05-25)
	RESTYPE_TENDER					= 13,	// 13 tender
	RESTYPE_BLOCKED_AUTOMAT			= 14,	// 14 Automat (ROWA) blocked
	RESTYPE_FMD_QUARANTINE			= 15,	// 15 FMD verification failed/missing

	// reservations in custstockreserved
	RESTYPE_INFOORDER_FREE			= 1,
	RESTYPE_INFOORDER_RESERVED		= 6,
	RESTYPE_RESTDELIVERY_FREE		= 7,
	RESTYPE_RESTDELIVERY_RESERVED	= 8,
	RESTYPE_IBT_FREE				= 9,
	RESTYPE_IBT_RESERVED			= 10,
	RESTYPE_OPENORDER_FREE			= 11,
	RESTYPE_OPENORDER_RESERVED		= 12
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // RESERVATIONTYPEENUM_INC

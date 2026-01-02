#ifndef GUARD_BATCHSTATUS_ENUM_H
#define GUARD_BATCHSTATUS_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumeration for batch status codes.                                       */
/*----------------------------------------------------------------------------*/
enum BatchStatusEnum
{
	BATCHSTATUS_NOT_YET_BOOKED			= 1,	// 1 = WE / noch nicht aktiv
	BATCHSTATUS_SALEABLE				= 2,	// 2 = Abverkauf möglich
	BATCHSTATUS_MISSING_PACKAGE_INSERT	= 3,	// 3 = Quarantäne (Beipack fehlt)
	BATCHSTATUS_SOLD					= 4,	// 4 = Artikel ist abverkauft
	BATCHSTATUS_BATCH_RECALL			= 5,	// 5 = Quarantäne (Chargenrückruf) 
	BATCHSTATUS_TENDER					= 7,	// 7 = Quarantäne (reserviert für Tender)
	BATCHSTATUS_MISSING_CERTIFICATE		= 8,	// 8 = Quarantäne (Zertifikat fehlt)
	BATCHSTATUS_OVERSTOCK				= 9,	// 9 = Übervorrat
	BATCHSTATUS_BLOCKED_AUTOMAT			= 10,	// 'S' = Quarantäne (Automat defekt)
												// ab hier Prewhole (dynamisch!), z.B.
	BATCHSTATUS_PREWHOLE_QUARANTINE		= 11	// D = Quarantäne Prewhole
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_BATCHSTATUS_ENUM_H

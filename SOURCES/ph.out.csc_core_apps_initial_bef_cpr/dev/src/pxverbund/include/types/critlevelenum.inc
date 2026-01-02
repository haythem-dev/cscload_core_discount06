#ifndef GUARD_CRITLEVEL_ENUM_INC
#define GUARD_CRITLEVEL_ENUM_INC

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumerate the crit level types.                                           */
/*----------------------------------------------------------------------------*/
enum CritLevelEnum
{
	Info      = 0,
	Important = 1,
	Warning   = 2,
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_CRITLEVEL_ENUM_INC

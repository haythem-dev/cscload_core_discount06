#ifndef GUARD_RETURNTYPE_ENUM_H
#define GUARD_RETURNTYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

enum ReturnTypeEnum
{
	ReturnRequest		= 0,	// 0 = RetourenavisAnfrage
	ReturnAnnouncement	= 1	    // 1 = RetourenavisAnkündigung
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"


#endif // GUARD_RETURNTYPE_ENUM_H

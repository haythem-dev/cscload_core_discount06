#ifndef GUARD_POSITIONTYPE_ENUM_H
#define GUARD_POSITIONTYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif


enum PositionTypeEnum				// order item type definition
{
	TypeProductStocked		= 0,	// known product, found in ArtBase table
	TypeProductNotStocked	= 1,	// known product, but not in ArtBase table
	TypeProductUnknown		= 2,	// unknown product id
	TypeTextOnly			= 3,	// Text item
	TypeDispoItem			= 4,	// Dispo item
	TypeDispoItemValued 	= 5 	// Valued dispo item
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"


#endif // GUARD_POSITIONTYPE_ENUM_H

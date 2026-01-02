#ifndef GUARD_SPLITTORIGINTYPE_ENUM_H
#define GUARD_SPLITTORIGINTYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

enum SplittOriginTypeEnum		// splitt origin type definition
{
	SplittPosition	 = 0,		
	OriginalPosition = 1		
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"


#endif // GUARD_SPLITTORIGINTYPE_ENUM_H

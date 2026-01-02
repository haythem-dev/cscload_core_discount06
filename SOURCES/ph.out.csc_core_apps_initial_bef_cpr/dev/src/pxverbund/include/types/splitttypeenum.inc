#ifndef GUARD_SPLITTTYPE_ENUM_H
#define GUARD_SPLITTTYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

enum SplittTypeEnum		// splitt type definition
{
	SplittType_Unknown		= 0,	// unknown splitt type (should not appear)
	SplittType_IBT			= 1,	// IBT Splitt "ANNA"
	SplittType_Priso		= 2,	// IBT Splitt Private Assortment
	SplittType_Narcotics	= 3,    // Splitt _Narcotics
	SplittType_ResHospital	= 4,	// Splitt _ResHospital
	SplittType_Cooler		= 5,	// Splitt Cooler	
	SplittType_Zytostatic	= 6,	// Splitt Zytostatic
	SplittType_Psychotrop	= 7,	// Splitt Psychotrop
	SplittType_Auxpositions	= 8		// Splitt Auxpositions
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"


#endif // GUARD_SPLITTTYPE_ENUM_H

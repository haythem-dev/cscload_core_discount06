#ifndef GUARD_PRICETYPE_ENUM_H
#define GUARD_PRICETYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

enum PriceTypeEnum
{
	FREESALE_PRICE		= 0,	// 0 = FF(FreiVerkauf) = default
	HEALTHFUND_PRICE	= 1,	// 1 = KK(KrankenKasse)
	RETAIL_PRICE		= 2,	// 2 = EV(EinzelHandelsVerkauf)
	LISTFIVE_PRICE		= 5 	// 5 = Liste 5 Bulgarian apllication
} 


// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"


#endif // GUARD_PRICETYPE_ENUM_H

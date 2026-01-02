#ifndef GUARD_RETURNREASON_ENUM_H
#define GUARD_RETURNREASON_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

enum ReturnReasonEnum
{
	OrderingError			= 0,	// BF = Bestellfehler
	InvoicedNotDelivered	= 1,	// BN = BerechnetNichtGeliefert
	Damaged					= 2,	// BE = Beschaedigt
	ShortExpiry				= 3,	// VK = VerfallZuKurz
	TooMuchDelivered		= 4		// ZG = ZuvielGeliefert
}


// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"


#endif // GUARD_RETURNREASON_ENUM_H

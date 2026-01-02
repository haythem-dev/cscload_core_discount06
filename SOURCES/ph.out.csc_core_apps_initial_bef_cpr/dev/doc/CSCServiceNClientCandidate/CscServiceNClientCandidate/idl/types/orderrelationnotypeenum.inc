#ifndef GUARD_ORDER_RELATIONNO_TYPE_ENUM_H
#define GUARD_ORDER_RELATIONNO_TYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumeration of orderrelationnotypes                                       */
/*----------------------------------------------------------------------------*/

enum OrderRelationNoTypeEnum
{
	eUndefinedOrderRelationNo = 0,
	ePurchaseOrderNo = 1,
	eIVCVoucherNo = 2,
	eOriginalInvoiceNo = 3
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_ORDER_RELATIONNO_TYPE_ENUM_H

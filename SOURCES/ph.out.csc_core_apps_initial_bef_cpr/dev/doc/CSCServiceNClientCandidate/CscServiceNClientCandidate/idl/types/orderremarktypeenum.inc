#ifndef GUARD_ORDER_REMARK_TYPE_ENUM_H
#define GUARD_ORDER_REMARK_TYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumeration of orderremarks                                               */
/*----------------------------------------------------------------------------*/

enum OrderRemarkTypeEnum
{
	eUndefinedOrderRemarkType = 0,
	eTenderContractId = 1,
	eOrderReferenceXML = 2,
	eOrderLineReferenceXML = 3,
	eInvoiceNo = 4,
	eTenderNo = 5,
	eMSV3RequestId = 10,
	eMSV3RequestSupportId = 11,
	eMSV3OrderId = 12,
	eMSV3OrderSupportID = 13,
    eWholesalerAuthorisation = 14,
	eErrorLogging = 99
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_ORDER_REMARK_TYPE_ENUM_H

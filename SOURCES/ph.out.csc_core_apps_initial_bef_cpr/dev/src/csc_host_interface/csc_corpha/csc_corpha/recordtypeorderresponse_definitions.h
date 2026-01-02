//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions for RecordTypeOrderResponse
 *  \author		Steffen Heinlein
 *  \date		06.09.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERRESPONSE_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERRESPONSE_DEFINITIONS_H

#include <libbasarcmnutil_bstring.h>

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	enum RecordType
	{
		UNKNOWN	= -1,
		A1		= 0,
		S1		= 1,
		P1		= 2
	};

	struct OrderResponseValues
	{				
		RecordType				Type;
		basar::VarString		RecType;
		basar::Long64			CSCOrderNo;
		basar::Long64			CSCOrderLineNo;				
		basar::Long64			PharmosOrderNo;
		basar::Long64			Status;															
		basar::Long64 			DeliveryQty;

		OrderResponseValues()
		{
			init();
		}

		void init()
		{
			Type = UNKNOWN;
			CSCOrderNo = 0;
			CSCOrderLineNo = 0;
			PharmosOrderNo = 0;
			Status = 0;
			DeliveryQty = 0;
		}
	};

	struct OrderResponseFormat
	{	
		static const size_t LENGTH_RECORDTYPE = 2;
		static const size_t LENGTH_CSCORDERNO = 7;
		static const size_t LENGTH_PHARMOSORDERNO = 7;
		static const size_t LENGTH_STATUS = 2;		
	};

	struct OrderLineResponseFormat
	{				
		static const size_t LENGTH_RECORDTYPE = 2;
		static const size_t LENGTH_ORDERNO = 7;
		static const size_t LENGTH_ORDERLINENO = 7;			
		static const size_t LENGTH_STATUS = 2;			
		static const size_t LENGTH_DELIVERYQTY = 5;			
	};
	
} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERRESPONSE_DEFINITIONS_H

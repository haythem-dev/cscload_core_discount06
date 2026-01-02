//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions for RecordTypeOrderInfo
 *  \author		Steffen Heinlein
 *  \date		06.09.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERINFO_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERINFO_DEFINITIONS_H

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	struct OrderInfoValues
	{
		basar::VarString 			RecordType; 
		basar::Long64				CustomerOrderNo;
		basar::VarString			PharmacyOrderNo;
		basar::Long64				InternalCustomerNo;
		basar::VarString			PharmacyTour;
		basar::VarString			ShipmentType;
		basar::Long64				ProcessNo;
		basar::VarString			EDIDeliveryNote;
		basar::Long64				BatchOrderNo;

		OrderInfoValues()
		{
			init();
		}

		void init()
		{
			CustomerOrderNo = 0;
			InternalCustomerNo = 0;
			ProcessNo = 0;
			BatchOrderNo = 0;			
			RecordType = "AI";
		}
	};

	namespace OrderInfoFormat
	{
		static const size_t LENGTH_RECORDTYPE = 2;						
		static const size_t LENGTH_CUSTOMERORDERNO = 7;
		static const size_t LENGTH_PHARMACYORDERNO_LEGACY = 8;
		static const size_t LENGTH_INTERNALCUSTOMERNO = 7;
		static const size_t LENGTH_PHARMACYTOUR = 10;					
		static const size_t LENGTH_SHIPMENTTYPE = 2;					
		static const size_t LENGTH_PROCESSNO = 7;						
		static const size_t LENGTH_EDIDELIVERYNOTE = 1;				
		static const size_t LENGTH_BATCHORDERNO = 5;	
		static const size_t LENGTH_PHARMACYORDERNO = 9;
	}
	
} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERINFO_DEFINITIONS_H

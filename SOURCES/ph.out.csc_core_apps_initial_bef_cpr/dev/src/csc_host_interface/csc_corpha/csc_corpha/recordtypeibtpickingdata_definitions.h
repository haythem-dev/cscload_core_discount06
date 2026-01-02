//----------------------------------------------------------------------------
/*! \file
 *  \brief		definitions for RecordTypeIBTPickingData
 *  \author		Steffen Heinlein
 *  \date		12.11.2018
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEIBTPICKINGDATA_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEIBTPICKINGDATA_DEFINITIONS_H

namespace domMod
{
namespace corpha
{
namespace recordtypes
{
	struct IBTPickingDataValues                         // DX04VK
	{
		basar::VarString		RecordType;             // KVK-NAME "VK"
		basar::Long64		    CSCOrderNo;             // KVK-KSCAUFNR
        basar::Long64           CSCOrderPosNo;          // KVK-KSCPOSNR
        basar::Long64           DeliveryPosNo;          // KVK-DELPOSNR
        basar::Long64			DeliveryQty;            // KVK-QUANTITY
        basar::VarString        Batch;                  // KVK-BATCH
        basar::Long64           ExpiryDate;             // KVK-EXPIRY (JHJJMMTT)
        basar::Int32			IBTBranchNo;            // KVK-IBTBRANCHNO

        IBTPickingDataValues()
		{
			init();
		}

		void init()
		{
            RecordType = "VK";
            CSCOrderNo = 0;
            CSCOrderPosNo = 0;
            DeliveryPosNo = 0;
            DeliveryQty = 0;
            Batch = "";
            ExpiryDate = 0;
            IBTBranchNo = 0;
		}
	};

	namespace IBTPickingDataFormat
	{
		static const size_t LENGTH_RECORDTYPE = 2;
		static const size_t LENGTH_CSCORDERNO = 7;
        static const size_t LENGTH_CSCORDERPOSNO = 7;
        static const size_t LENGTH_DELIVERYPOSNO = 7;
        static const size_t LENGTH_DELIVERYQTY = 7;
        static const size_t LENGTH_BATCH = 25;
        static const size_t LENGTH_EXPIRYDATE = 8;
        static const size_t LENGTH_IBTBRANCHNO = 2;
	}

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEIBTPICKINGDATA_DEFINITIONS_H

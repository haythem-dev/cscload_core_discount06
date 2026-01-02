//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Heinlein Steffen
 *  \date       12.11.2018
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEIBTPICKINGDATA_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEIBTPICKINGDATA_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include "recordtypebase.h"
#include "recordtypeibtpickingdata_definitions.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{
	class RecordTypeIBTPickingData : public RecordTypeBase
	{
		private:
            RecordTypeIBTPickingData( const RecordTypeIBTPickingData& );
            RecordTypeIBTPickingData& operator= ( const RecordTypeIBTPickingData& );

		public:
            RecordTypeIBTPickingData( libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeIBTPickingData();

		private:
			IBTPickingDataValues		m_Values;

		public:

			const basar::VarString		doSerialize() const;

            void                        setCSCOrderNo(const basar::Long64&);
            void                        setCSCOrderPosNo(const basar::Long64&);
            void                        setDeliveryPosNo(const basar::Long64&);
            void                        setDeliveryQty(const basar::Long64&);
            void                        setBatch(const basar::VarString&);
            void                        setExpiryDate(const basar::Long64&);
            void                        setIBTBranchNo(const basar::Int32&);
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEIBTPICKINGDATA_H

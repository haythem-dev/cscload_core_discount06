//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       04.09.2012
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERINFO_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERINFO_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include "recordtypebase.h"
#include "recordtypeorderinfo_definitions.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{		
	class RecordTypeOrderInfo : public RecordTypeBase
	{
		private:
			RecordTypeOrderInfo( const RecordTypeOrderInfo& );
			RecordTypeOrderInfo& operator= ( const RecordTypeOrderInfo& );

		public:
			RecordTypeOrderInfo( libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeOrderInfo();

		private:
			OrderInfoValues				m_Values;
			
		public:
			const basar::VarString		doSerialize() const;
			
			void						setCustomerOrderNo( const basar::Long64& );
			void						setPharmacyOrderNo( const basar::VarString& );
			void						setInternalCustomerNo( const basar::Long64& );
			void						setPharmacyTour( const basar::VarString& );
			void						setShipmentType( const basar::VarString& );
			void						setProcessNo( const basar::Long64& );
			void						setEDIDeliveryNote( const basar::VarString& );
			void						setBatchOrderNo( const basar::Long64& );
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERINFO_H

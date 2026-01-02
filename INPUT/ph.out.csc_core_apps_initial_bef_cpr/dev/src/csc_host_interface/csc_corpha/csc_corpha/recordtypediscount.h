//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       10.09.2014
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEDISCOUNT_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEDISCOUNT_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include "recordtypebase.h"
#include "recordtypediscount_definitions.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	

	class RecordTypeDiscount : public RecordTypeBase
	{		
		private:
			RecordTypeDiscount( const RecordTypeDiscount& );
			RecordTypeDiscount& operator= ( const RecordTypeDiscount& );

		public:
			RecordTypeDiscount( libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeDiscount();						

		private:						
			DiscountValues				m_Values;

		public:
			const basar::VarString		doSerialize() const;

			void						setBranchNo( const basar::Int16 );
			void						setOrderPosNo( const basar::Long64& );
			void						setDiscountMode( const basar::Int32 );
			void						setOrderNo( const basar::Long64& );
			void						setDiscount( const basar::Decimal& );
			void						setInternalRebate( const basar::Int16 );
			void						setRefundPercent(const basar::Decimal& );
			void						setDiscountBase( const basar::Int16 );
			void						setPharmacyGroup( const basar::VarString& );
			void						setDiscountCalcFrom( const basar::Int16 );
			void						setDiscountApplyTo( const basar::Int16 );
			void						setDiscountSortBase( const basar::Int16 );
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEDISCOUNT_H

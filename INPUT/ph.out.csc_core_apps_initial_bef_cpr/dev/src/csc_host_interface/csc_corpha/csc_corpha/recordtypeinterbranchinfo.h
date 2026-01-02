//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Heinlein Steffen
 *  \date       04.09.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEINTERBRANCHINFO_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEINTERBRANCHINFO_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include "recordtypebase.h"
#include "recordtypeinterbranchinfo_definitions.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{
	class RecordTypeInterBranchInfo : public RecordTypeBase
	{
		private:
			RecordTypeInterBranchInfo( const RecordTypeInterBranchInfo& );
			RecordTypeInterBranchInfo& operator= ( const RecordTypeInterBranchInfo& );

		public:
			RecordTypeInterBranchInfo( libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeInterBranchInfo();

		private:
			InterBranchInfoValues		m_Values;

		public:
			const basar::VarString		doSerialize() const;

			void						setBranchNo( const basar::Int32 );
			void						setOriginBranchNo( const basar::Int32 );
			void						setCustomerNo( const basar::Long64& );
			void						setPharmacyName( const basar::VarString& );
			void						setOwnerName( const basar::VarString& );
			void						setStreet( const basar::VarString& );
			void						setPostalCode( const basar::Int32 );
			void						setCity( const basar::VarString& );
			void						setPhoneNo( const basar::VarString& );
			void						setTourId( const basar::Int32 );
			void						setDecTourId( const basar::Long64& );
			void						setDialUpPhoneNo( const basar::VarString& );
			void						setFax( const basar::VarString& );
			void						setSalutationId( const basar::VarString& );
			void						setSalesRepNo( const basar::Long64& );
			void						setDistrictNo( const basar::Long64& );
			void						setDistrictNo2( const basar::Long64& );
			void						setCustomerGroup( const basar::VarString& );
			void						setWeekdayId( const basar::Int32 );
			void						setWebShopFlag( const basar::VarString& );
			void						setLanguage( const basar::VarString& );
			void						setOrderChannel(const basar::Int32);
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEINTERBRANCHINFO_H

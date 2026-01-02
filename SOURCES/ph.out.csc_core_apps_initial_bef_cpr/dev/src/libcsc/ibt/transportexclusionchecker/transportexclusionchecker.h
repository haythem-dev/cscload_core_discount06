#ifndef GUARD_LIBCSC_IBT_TRANSPORT_EXCLUSION_CHECKER_H
#define GUARD_LIBCSC_IBT_TRANSPORT_EXCLUSION_CHECKER_H

#include <ibt/transportexclusionchecker/itransportexclusionchecker.h>
#include <persistence/iaccessorptr.h>

namespace libcsc
{
	namespace ibt
	{

		class TransportExclusionChecker : public ITransportExclusionChecker
		{

		public:
			TransportExclusionChecker();
			virtual ~TransportExclusionChecker();

			void injectSelectAccessor( persistence::IAccessorPtr accessor );		
			
			virtual bool isTransportPossible( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo ) const;
			virtual bool isTransportPossibleForSameDayDelivery( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo ) const;
			virtual bool isTransportPossibleForOvernightDelivery( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo ) const;

			virtual bool isTransportPossibleForCustomer( const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 articleNo ) const;

		private:

			enum DeliveryType{ OverNightDelivery = 0, SameDayDelivery = 1, GeneralDelivery = 2 };			

			bool isTransportPossibleByDeliveryType( const basar::Int16 branchNo, 
													const basar::Int16 ibtBranchNo, 
													const basar::Int32 articleNo, 
													const DeliveryType type = TransportExclusionChecker::GeneralDelivery ) const;

			basar::VarString getRemoteDbIfNecessary( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo ) const;

			persistence::IAccessorPtr			m_SelectAccessor;
		};

	} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_TRANSPORT_EXCLUSION_CHECKER_H

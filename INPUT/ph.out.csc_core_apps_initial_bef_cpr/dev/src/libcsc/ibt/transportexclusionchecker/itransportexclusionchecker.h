#ifndef GUARD_LIBCSC_IBT_I_TRANSPORT_EXCLUSION_CHECKER_H
#define GUARD_LIBCSC_IBT_I_TRANSPORT_EXCLUSION_CHECKER_H

#include <libbasar_definitions.h>

namespace libcsc
{
	namespace ibt
	{
		class ITransportExclusionChecker
		{
			public:
				virtual ~ITransportExclusionChecker() {}	

				virtual bool isTransportPossible( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo ) const = 0;

				virtual bool isTransportPossibleForSameDayDelivery( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo ) const = 0;

				virtual bool isTransportPossibleForOvernightDelivery( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo ) const = 0;

				virtual bool isTransportPossibleForCustomer( const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 articleNo ) const = 0;
		};
	} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_TRANSPORT_EXCLUSION_CHECKER_H

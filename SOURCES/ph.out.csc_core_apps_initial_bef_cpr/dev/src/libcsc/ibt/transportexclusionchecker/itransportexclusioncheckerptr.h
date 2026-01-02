#ifndef GUARD_LIBCSC_IBT_I_TRANSPORT_EXCLUSION_CHECKER_PTR_H
#define GUARD_LIBCSC_IBT_I_TRANSPORT_EXCLUSION_CHECKER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
	namespace ibt
	{
		class ITransportExclusionChecker;
		typedef boost::shared_ptr<libcsc::ibt::ITransportExclusionChecker> ITransportExclusionCheckerPtr;
	} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_TRANSPORT_EXCLUSION_CHECKER_PTR_H

#ifndef GUARD_LIBCSC_IBT_TRANSPORT_EXCLUSION_CHECKER_PTR_H
#define GUARD_LIBCSC_IBT_TRANSPORT_EXCLUSION_CHECKER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
	namespace ibt
	{
		class TransportExclusionChecker;
		typedef boost::shared_ptr<libcsc::ibt::TransportExclusionChecker> TransportExclusionCheckerPtr;

	} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_TRANSPORT_EXCLUSION_CHECKER_PTR_H

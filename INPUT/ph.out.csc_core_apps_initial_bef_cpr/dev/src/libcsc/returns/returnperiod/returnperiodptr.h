#ifndef GUARD_LIBCSC_RETURNS_RETURNPERIODPTR_H
#define GUARD_LIBCSC_RETURNS_RETURNPERIODPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace returns {

	class ReturnPeriod;
	typedef boost::shared_ptr<ReturnPeriod> ReturnPeriodPtr;

	typedef std::list<ReturnPeriodPtr> ReturnPeriodCollection;

	typedef boost::shared_ptr<ReturnPeriodCollection> ReturnPeriodCollectionPtr;

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNPERIODPTR_H

#ifndef GUARD_LIBCSC_RETURNS_IRETURNPERIODREPOSITORYPTR_H
#define GUARD_LIBCSC_RETURNS_IRETURNPERIODREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace returns {

	class IReturnPeriodRepository;
	typedef boost::shared_ptr<IReturnPeriodRepository> IReturnPeriodRepositoryPtr;

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_IRETURNPERIODREPOSITORYPTR_H

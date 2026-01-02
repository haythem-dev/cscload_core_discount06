#ifndef GUARD_LIBCSC_RETURNS_IRETURNRULEBOOKREPOSITORYPTR_H
#define GUARD_LIBCSC_RETURNS_IRETURNRULEBOOKREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace returns {

	class IReturnRuleBookRepository;

	typedef boost::shared_ptr<IReturnRuleBookRepository> IReturnRuleBookRepositoryPtr;

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_IRETURNRULEBOOKREPOSITORYPTR_H

#ifndef GUARD_LIBCSC_RETURNS_RETURNRULEBOOKREPOSITORYPTR_H
#define GUARD_LIBCSC_RETURNS_RETURNRULEBOOKREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace returns {

	class ReturnRuleBookRepository;
	typedef boost::shared_ptr<ReturnRuleBookRepository> ReturnRuleBookRepositoryPtr;

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNRULEBOOKREPOSITORYPTR_H

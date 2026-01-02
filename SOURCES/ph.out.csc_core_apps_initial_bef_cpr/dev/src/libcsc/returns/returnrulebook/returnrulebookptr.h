#ifndef GUARD_LIBCSC_RETURNS_RETURNRULEBOOKPTR_H
#define GUARD_LIBCSC_RETURNS_RETURNRULEBOOKPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace returns {

	class ReturnRuleBook;
	typedef boost::shared_ptr<ReturnRuleBook> ReturnRuleBookPtr;

	typedef std::list<ReturnRuleBookPtr> ReturnRuleBookCollection;

	typedef boost::shared_ptr<ReturnRuleBookCollection> ReturnRuleBookCollectionPtr;


} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNRULEBOOKPTR_H

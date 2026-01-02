#ifndef GUARD_DOMMOD_IBULK_INSERTER_PTR_H
#define GUARD_DOMMOD_IBULK_INSERTER_PTR_H

#include <boost/shared_ptr.hpp>

namespace domMod 
{		
namespace util
{
	class IBulkInserter;
	typedef boost::shared_ptr<domMod::util::IBulkInserter> IBulkInserterPtr;

} // namespace util
} // namespace domMod

#endif // GUARD_DOMMOD_IBULK_INSERTER_PTR_H


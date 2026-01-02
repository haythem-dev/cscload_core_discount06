#ifndef GUARD_LIBCSC_DOMMOD_CSCORDER_CSCCALLPLANPTR_H
#define GUARD_LIBCSC_DOMMOD_CSCORDER_CSCCALLPLANPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace cscorder {
namespace domMod {

class CSCCallplan;
typedef boost::shared_ptr<CSCCallplan> CSCCallplanPtr;

} // namespace domMod
} // namespace cscorder
} // namespace libcsc

#endif // GUARD_LIBCSC_DOMMOD_CSCORDER_CSCCALLPLANPTR_H

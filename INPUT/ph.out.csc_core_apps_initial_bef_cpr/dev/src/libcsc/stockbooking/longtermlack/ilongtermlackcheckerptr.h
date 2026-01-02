#ifndef GUARD_LIBCSC_STOCKBOOKING_ILONGTERMLACK_CHECKER_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_ILONGTERMLACK_CHECKER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace stockbooking {

class ILongTermLackChecker;
typedef boost::shared_ptr<ILongTermLackChecker> ILongTermLackCheckerPtr;

} // namespace stockbooking
} // namespace libcsc

#endif


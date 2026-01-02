#ifndef GUARD_LIBCSC_STOCKBOOKING_ILONGTERMLACK_DELETER_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_ILONGTERMLACK_DELETER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace stockbooking {

class ILongTermLackDeleter;
typedef boost::shared_ptr<ILongTermLackDeleter> ILongTermLackDeleterPtr;

} // namespace stockbooking
} // namespace libcsc

#endif

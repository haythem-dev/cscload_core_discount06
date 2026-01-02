#ifndef GUARD_LIBCSC_STOCKBOOKING_LONGTERMLACK_REPOSITORY_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_LONGTERMLACK_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace stockbooking {

class LongTermLackRepository;
typedef boost::shared_ptr<LongTermLackRepository> LongTermLackRepositoryPtr;

} // namespace stockbooking
} // namespace libcsc

#endif


#ifndef GUARD_LIBCSC_STOCKBOOKING_I_ARTICLERESERVATION_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_I_ARTICLERESERVATION_PTR_H

#include <boost/shared_ptr.hpp>
#include <vector>

namespace libcsc {
namespace stockbooking {

class IArticleReservation;
typedef boost::shared_ptr<IArticleReservation> IArticleReservationPtr;

typedef std::vector<IArticleReservationPtr> IArticleReservationCollection;

typedef boost::shared_ptr<IArticleReservationCollection> IArticleReservationCollectionPtr;

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_ARTICLERESERVATION_PTR_H

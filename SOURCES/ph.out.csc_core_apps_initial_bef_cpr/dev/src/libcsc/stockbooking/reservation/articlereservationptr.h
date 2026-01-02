#ifndef GUARD_LIBCSC_STOCKBOOKING_ARTICLERESERVATION_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_ARTICLERESERVATION_PTR_H

#include <boost/shared_ptr.hpp>
#include <vector>

namespace libcsc {
namespace stockbooking {

class ArticleReservation;
typedef boost::shared_ptr<ArticleReservation> ArticleReservationPtr;

//typedef std::vector<ArticleReservationPtr> ArticleReservationCollection;

//typedef boost::shared_ptr<ArticleReservationCollection> ArticleReservationCollectionPtr;

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_ARTICLERESERVATION_PTR_H

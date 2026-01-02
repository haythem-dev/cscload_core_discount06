#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALSPTR_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALSPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace document {

class DeliveryAdviceVatTotals;
typedef boost::shared_ptr<DeliveryAdviceVatTotals> DeliveryAdviceVatTotalsPtr;

typedef std::list<DeliveryAdviceVatTotalsPtr> DeliveryAdviceVatTotalsCollection;

typedef boost::shared_ptr<DeliveryAdviceVatTotalsCollection> DeliveryAdviceVatTotalsCollectionPtr;



} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALSPTR_H

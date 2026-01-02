#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DETAILSPTR_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DETAILSPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace document {

class DeliveryAdviceLineDetails;
typedef boost::shared_ptr<DeliveryAdviceLineDetails> DeliveryAdviceLineDetailsPtr;

typedef std::list<DeliveryAdviceLineDetailsPtr> DeliveryAdviceLineDetailsCollection;

typedef boost::shared_ptr<DeliveryAdviceLineDetailsCollection> DeliveryAdviceLineDetailsCollectionPtr;

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DETAILSPTR_H

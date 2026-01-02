#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEPTR_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace document {

class DeliveryAdviceLine;
typedef boost::shared_ptr<DeliveryAdviceLine> DeliveryAdviceLinePtr;

typedef std::vector<DeliveryAdviceLinePtr> DeliveryAdviceLineCollection;

typedef boost::shared_ptr<DeliveryAdviceLineCollection> DeliveryAdviceLineCollectionPtr;


} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEPTR_H

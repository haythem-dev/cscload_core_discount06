#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_EXTRAS_AT_PTR_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_EXTRAS_AT_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace document {

class DeliveryAdviceLineExtrasAT;
typedef boost::shared_ptr<DeliveryAdviceLineExtrasAT> DeliveryAdviceLineExtrasATPtr;

typedef std::list<DeliveryAdviceLineExtrasATPtr> DeliveryAdviceLineExtrasATCollection;

typedef boost::shared_ptr<DeliveryAdviceLineExtrasATCollection> DeliveryAdviceLineExtrasATCollectionPtr;

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_EXTRAS_AT_PTR_H

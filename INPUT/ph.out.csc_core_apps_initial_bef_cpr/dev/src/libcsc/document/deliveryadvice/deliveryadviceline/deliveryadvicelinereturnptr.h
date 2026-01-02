#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_RETURNPTR_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_RETURNPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace document {

class DeliveryAdviceLineReturn;
typedef boost::shared_ptr<DeliveryAdviceLineReturn> DeliveryAdviceLineReturnPtr;

typedef std::list<DeliveryAdviceLineReturnPtr> DeliveryAdviceLineReturnCollection;

typedef boost::shared_ptr<DeliveryAdviceLineReturnCollection> DeliveryAdviceLineReturnCollectionPtr;

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_RETURNPTR_H

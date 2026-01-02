#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DISCOUNTPTR_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DISCOUNTPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace document {

class DeliveryAdviceLineDiscount;
typedef boost::shared_ptr<DeliveryAdviceLineDiscount> DeliveryAdviceLineDiscountPtr;

typedef std::list<DeliveryAdviceLineDiscountPtr> DeliveryAdviceLineDiscountCollection;

typedef boost::shared_ptr<DeliveryAdviceLineDiscountCollection> DeliveryAdviceLineDiscountCollectionPtr;

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DISCOUNTPTR_H

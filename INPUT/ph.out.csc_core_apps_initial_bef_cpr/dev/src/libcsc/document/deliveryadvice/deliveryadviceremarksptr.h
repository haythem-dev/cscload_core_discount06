#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKSPTR_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKSPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace document {

class DeliveryAdviceRemarks;

typedef boost::shared_ptr<DeliveryAdviceRemarks> DeliveryAdviceRemarksPtr;

typedef std::list<DeliveryAdviceRemarksPtr> DeliveryAdviceRemarksCollection;

typedef boost::shared_ptr<DeliveryAdviceRemarksCollection> DeliveryAdviceRemarksCollectionPtr;


} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKSPTR_H

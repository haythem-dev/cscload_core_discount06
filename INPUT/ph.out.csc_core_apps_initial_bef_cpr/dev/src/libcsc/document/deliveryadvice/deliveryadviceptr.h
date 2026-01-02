#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEPTR_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace document {

enum ConfirmationStatusEnum
{
	CONFIRMATION_STATUS_ALL_UNCONFIRMED = 0,	// 0 = all unconfirmed delivery advices
	CONFIRMATION_STATUS_ALL = 1					// 1 = all delivery advices
};

class DeliveryAdvice;
typedef boost::shared_ptr<DeliveryAdvice> DeliveryAdvicePtr;

typedef std::list<DeliveryAdvicePtr> DeliveryAdviceCollection;

typedef boost::shared_ptr<DeliveryAdviceCollection> DeliveryAdviceCollectionPtr;

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEPTR_H

#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REPOSITORY_PTR_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace document {

class DeliveryAdviceRepository;
typedef boost::shared_ptr<DeliveryAdviceRepository> DeliveryAdviceRepositoryPtr;

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REPOSITORY_PTR_H
